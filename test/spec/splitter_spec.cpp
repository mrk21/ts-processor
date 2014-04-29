#include <bandit_with_gmock/bandit_with_gmock.hpp>
#include <ts_processor/splitter.hpp>
#include <bitfield/util.hpp>
#include <algorithm>
#include <sstream>
#include <initializer_list>

namespace ts_processor {
go_bandit([]{
    using namespace bandit;
    using namespace testing;
    
    describe("splitter", [&]{
        auto const SPLIT_GROUP_ =
            #include <fixture/split_group.cpp>
        ;
        
        describe("when failed the input file opening", [&]{
            it("should return 1", [&]{
                char arg1[] = "test";
                char arg2[] = "tmp/split_group2.ts";
                char * argv[] = {arg1,arg2};
                
                AssertThat(ts_processor::splitter().execute(2,argv), Equals(1));
            });
        });
        
        describe("when failed the output file opening", [&]{
            it("should return 2", [&]{
                char arg1[] = "test";
                char arg2[] = "tmp/split_group.ts";
                char arg3[] = "tmp2/packet_set.ts";
                char * argv[] = {arg1,arg2,arg3};
                
                AssertThat(ts_processor::splitter().execute(3,argv), Equals(2));
            });
        });
        
        it("should split the Transport Stream, on top of that, return 0", [&]{
            char arg1[] = "test";
            char arg2[] = "tmp/split_group.ts";
            char arg3[] = "tmp/packet_set.ts";
            char * argv[] = {arg1,arg2,arg3};
            
            AssertThat(ts_processor::splitter().execute(3,argv), Equals(0));
            
            int i = -1;
            
            for (auto & packet_set: SPLIT_GROUP_) {
                std::string path = ++i > 0 ?
                    (std::ostringstream() << "tmp/packet_set" << i << ".ts").str() :
                    "tmp/packet_set.ts";
                std::ifstream ifs(path, std::ios::binary);
                ts_processor::reader reader(ifs);
                AssertThat(!ifs, Equals(false));
                
                for (auto expected_packet: packet_set) {
                    ts::packet actual_packet;
                    reader.read(actual_packet);
                    AssertThat(actual_packet, Equals(*expected_packet));
                }
            }
        });
    });
    
    describe("splitter::context", [&]{
        using context_t = splitter::context;
        using elementary_pid_pair = context_t::elementary_pid_pair;
        context_t * context;
        
        describe("#call(ts::packet & packet)", [&]{
            ts::packet packet_;
            
            before_each([&]{ context = new context_t; });
            
            it("should call the `state#call()`", [&]{
                struct state_mock: public splitter::state {
                    void setup() {}
                    MOCK_METHOD1(call, void(ts::packet &));
                } mock;
                
                EXPECT_CALL(mock, call(_)).Times(1);
                context->transition(&mock);
                context->call(packet_);
            });
            
            describe("when not transitioned even once", [&]{
                it("should not call the `state#call()`", [&]{
                    context->call(packet_);
                });
            });
        });
        
        describe("#set_elementary_pid(elementary_pid_pair elementary_pid)", [&]{
            auto assert_block_ = [&context](std::size_t call_count, std::function<void()> block){
                return [&context, call_count, block]{
                    struct {
                        MOCK_METHOD0(on_elementary_pid_change, void());
                    } mock;
                    
                    context = new context_t([&mock]{
                        mock.on_elementary_pid_change();
                    });
                    
                    EXPECT_CALL(mock, on_elementary_pid_change()).Times(call_count);
                    block();
                };
            };
            
            auto assert_ = [&](elementary_pid_pair setting_value){
                context->set_elementary_pid(setting_value);
                AssertThat(context->get_elementary_pid(), Equals(setting_value));
            };
            
            describe("when first set", [&]{
                it("should not call the handler", assert_block_(0,[&]{
                    assert_({1,1});
                }));
            });
            
            describe("when not changed the elementary_pid", [&]{
                it("should not call the handler", assert_block_(0,[&]{
                    assert_({1,1});
                    assert_({1,1});
                }));
            });
            
            describe("when changed the elementary_pid", [&]{
                it("should call the handler", assert_block_(1,[&]{
                    assert_({1,1});
                    assert_({2,2});
                }));
            });
            
            describe("when changed only the video pid of the elementary_pid", [&]{
                it("should call the handler", assert_block_(1,[&]{
                    assert_({1,1});
                    assert_({2,1});
                }));
            });
            
            describe("when changed only the audio pid of the elementary_pid", [&]{
                it("should call the handler", assert_block_(1,[&]{
                    assert_({1,1});
                    assert_({1,2});
                }));
            });
        });
    });
    
    describe("splitter::pat_state", [&]{
        splitter::context * context;
        ts::data data;
        const splitter::state * const PMT_STATE_ = splitter::state::get_instance<splitter::pmt_state>();
        
        describe("#call(ts::packet & packet)", [&]{
            describe("when completed the PAT packet parsing", [&]{
                before_each([&]{
                    ts::packet pat_packet{
                        #include <fixture/ts/psi/pat/single_packet.cpp>
                    };
                    context = new splitter::context;
                    context->transition<splitter::pat_state>();
                    
                    data.reset(ts::pid::id::pat);
                    data.push(pat_packet);
                    context->call(pat_packet);
                });
                
                it("s `context->get_pmt_pid()` should be the first PMT PID in the sections of the PAT packet", [&]{
                    auto it = data->pat.sections.begin();
                    ++it;
                    AssertThat(context->get_pmt_pid(), Equals(it->pid.get()));
                });
                
                it("s context should transition the pmt_state", [&]{
                    AssertThat(context->get_current_state(), Equals(PMT_STATE_));
                });
            });
        });
    });
    
    describe("splitter::pmt_state", [&]{
        splitter::context * context;
        ts::data data;
        const splitter::state * const PMT_STATE_ = splitter::state::get_instance<splitter::pmt_state>();
        
        struct pmt_state_for_test: public splitter::pmt_state {};
        
        describe("#call(ts::packet & packet)", [&]{
            describe("when completed the PAT packet parsing", [&]{
                before_each([&]{
                    ts::packet pmt_packet{
                        #include <fixture/ts/psi/pmt/single_packet.cpp>
                    };
                    context = new splitter::context;
                    context->set_pmt_pid(pmt_packet.pid);
                    context->transition<pmt_state_for_test>();
                    
                    data.reset(pmt_packet.pid);
                    data.push(pmt_packet);
                    context->call(pmt_packet);
                });
                
                it("s `context->get_elementary_pid()` should be the first audio PID and video PID in the sections of the PMT packet", [&]{
                    auto it = data->pmt.sections.begin();
                    uint32_t video_pid = it->elementary_pid;
                    ++it;
                    uint32_t audio_pid = it->elementary_pid;
                    splitter::context::elementary_pid_pair expected{video_pid, audio_pid};
                    AssertThat(context->get_elementary_pid(), Equals(expected));
                });
                
                it("s context should transition the pmt_state", [&]{
                    AssertThat(context->get_current_state(), Equals(PMT_STATE_));
                });
            });
        });
    });
});
}
