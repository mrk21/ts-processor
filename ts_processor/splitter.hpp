#ifndef __INCLUDED_TS_PROCESSOR_SPLITTER_HPP__
#define __INCLUDED_TS_PROCESSOR_SPLITTER_HPP__

#include <ts_processor/ts/data.hpp>
#include <ts_processor/ts/pid.hpp>
#include <ts_processor/ts/stream_type.hpp>
#include <ts_processor/reader.hpp>
#include <ts_processor/writer.hpp>
#include <iostream>
#include <fstream>
#include <functional>
#include <map>
#include <memory>

namespace ts_processor {
    class splitter {
        using self = splitter;
        
    public:
        class context;
        class state;
        class pat_state;
        class pmt_state;
        
        class context {
        public:
            using outside = self;
            using self = context;
            using elementary_pid_pair = std::pair<uint32_t, uint32_t>; // (video_pid, audio_pid)
            
        private:
            outside::state * current_state{nullptr};
            uint32_t pmt_pid{0};
            elementary_pid_pair elementary_pid{0,0};
            std::function<void()> on_elementary_pid_change;
            
        public:
            context(std::function<void()> on_elementary_pid_change = []{}) :
                on_elementary_pid_change(on_elementary_pid_change) {}
            
            outside::state * get_current_state();
            
            template<class State>
            void transition() {
                this->transition(outside::state::get_instance<State>());
            }
            
            void transition(outside::state * next_state);
            void call(ts::packet & packet);
            
            void set_elementary_pid(elementary_pid_pair elementary_pid);
            elementary_pid_pair get_elementary_pid() const;
            
            void set_pmt_pid(uint32_t pid);
            uint32_t get_pmt_pid() const;
        };
        
        class state {
        protected:
            using outside = self;
            using self = state;
            outside::context * context{nullptr};
            
        public:
            template<class State>
            static state * get_instance() {
                static State instance;
                return &instance;
            }
            
            void initialize(outside::context * context);
            virtual void setup() = 0;
            virtual void call(ts::packet & packet) = 0;
        };
        
        class pat_state: public self::state {
            ts::data data;
            
        public:
            virtual void setup();
            virtual void call(ts::packet & packet);
        };
        
        class pmt_state: public self::state {
            ts::data data;
            
        public:
            virtual void setup();
            virtual void call(ts::packet & packet);
        };
        
    private:
        static constexpr std::size_t BUFSIZE = 1024*1024; // 1 MB
        
        self::context context_{[this]{
            this->on_elementary_pid_change();
        }};
        std::ifstream ifs;
        std::ofstream ofs;
        std::string base_opath;
        std::size_t split_count{0};
        std::shared_ptr<char> ibuf{new char[BUFSIZE]};
        std::shared_ptr<char> obuf{new char[BUFSIZE]};
        
    public:
        splitter() {
            this->ifs.rdbuf()->pubsetbuf(this->ibuf.get(), BUFSIZE);
            this->ofs.rdbuf()->pubsetbuf(this->obuf.get(), BUFSIZE);
        }
        
        int execute(int /*argc*/, char * argv[]);
        
    private:
        void on_elementary_pid_change();
    };
}

#endif // __INCLUDED_TS_PROCESSOR_SPLITTER_HPP__
