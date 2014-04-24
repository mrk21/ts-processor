#include <bandit_with_gmock/bandit_with_gmock.hpp>
#include <ts_processor/reader.hpp>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

namespace ts_processor {
go_bandit([]{
    using namespace bandit;
    using namespace testing;
    
    describe("reader", [&]{
        using packet_data = std::vector<uint8_t>;
        using packet_list = std::vector<packet_data>;
        
        packet_list const PMT_PACKETS_{{
            #include <fixture/ts/psi/pmt/multi_packet_1.cpp>
        },{
            #include <fixture/ts/psi/pmt/multi_packet_2.cpp>
        }};
        packet_list const INVALID_PACKETS_{{
            #include <fixture/ts/packet/invalid_sync_byte.cpp>
        }};
        packet_list const INCOMPLETION_PACKETS_{{
            #include <fixture/ts/packet/incompletion.cpp>
        }};
        
        ts_processor::reader * reader;
        
        auto init_ = [&](const packet_list & packets){
            std::string data;
            
            for (auto & packet: packets) {
                for (auto v: packet) {
                    data.push_back(v);
                }
            }
            std::istringstream * iss = new std::istringstream(data);
            reader = new ts_processor::reader(*iss);
        };
        
        describe("#read(ts::packet & packet)", [&]{
            auto assert_packet_ = [&](const packet_data & expected_packet){
                ts::packet actual_packet;
                AssertThat(reader->read(actual_packet), Equals(true));
                AssertThat(std::equal(
                    actual_packet.container.begin(),
                    actual_packet.container.end(),
                    expected_packet.begin()
                ), Equals(true));
            };
            
            it("should read to the packet", [&]{
                init_(PMT_PACKETS_);
                assert_packet_(PMT_PACKETS_[0]);
            });
            
            describe("when the stream reaches the end", [&]{
                it("should return false", [&]{
                    init_(PMT_PACKETS_);
                    assert_packet_(PMT_PACKETS_[0]);
                    assert_packet_(PMT_PACKETS_[1]);
                    ts::packet packet;
                    AssertThat(reader->read(packet), Equals(false));
                });
            });
            
            describe("when the packet was invalid sync byte", [&]{
                it("should return false", [&]{
                    init_(INVALID_PACKETS_);
                    ts::packet packet;
                    AssertThat(reader->read(packet), Equals(false));
                });
            });
            
            describe("when a size of the reading was less than 188 bytes", [&]{
                it("should return false", [&]{
                    init_(INCOMPLETION_PACKETS_);
                    ts::packet packet;
                    AssertThat(reader->read(packet), Equals(false));
                });
            });
        });
        
        describe("#each(std::function<bool(ts::packet &)> callback)", [&]{
            struct callback_mock {
                MOCK_METHOD1(func, bool(ts::packet &));
            };
            auto call_each_ = [&](callback_mock & m){
                reader->each([&](ts::packet & p){ return m.func(p); });
            };
            
            it("should call the callback", [&]{
                init_(PMT_PACKETS_);
                callback_mock mock;
                EXPECT_CALL(mock, func(_)).Times(2).WillRepeatedly(Return(true));
                call_each_(mock);
            });
            
            describe("when the read was not successful", [&]{
                it("should not call the callback", [&]{
                    init_(INVALID_PACKETS_);
                    callback_mock mock;
                    EXPECT_CALL(mock, func(_)).Times(0);
                    call_each_(mock);
                });
            });
            
            describe("when the callback returns false", [&]{
                it("should abort reading", [&]{
                    init_(PMT_PACKETS_);
                    callback_mock mock;
                    EXPECT_CALL(mock, func(_)).Times(1).WillRepeatedly(Return(false));
                    call_each_(mock);
                });
            });
        });
    });
});
}
