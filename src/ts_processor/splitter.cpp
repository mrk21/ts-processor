#include <ts_processor/splitter.hpp>
#include <sstream>
#include <regex>
#include <algorithm>
#include <numeric>

namespace ts_processor {
    namespace {
        template<typename T>
        std::string create_filename_(const std::string & filename, const T & suffix) {
            std::regex reg("[^.]+");
            std::vector<std::string> v{
                std::sregex_token_iterator(filename.begin(), filename.end(), reg),
                std::sregex_token_iterator()
            };
            std::string result = std::accumulate(v.begin()+1, v.end(), std::string(),
                [](const std::string & a, const std::string & b){
                    return a + "." + b;
                }
            );
            return (std::ostringstream() << v[0] << suffix << result).str();
        }
    }
    
    int splitter::execute(int, char * argv[]) {
        this->ifs.open(argv[1], std::ios::binary);
        if (!this->ifs) {
            std::cerr << "invalid input file!" << std::endl;
            return 1;
        }
        
        this->ofs.open(argv[2], std::ios::binary);
        if (!this->ofs) {
            this->ifs.close();
            std::cerr << "invalid output file!" << std::endl;
            return 2;
        }
        
        ts_processor::reader reader(ifs);
        ts_processor::writer writer(ofs);
        this->split_count = 0;
        this->base_opath = argv[2];
        this->context_.transition<self::pat_state>();
        
        reader.each([this, &writer](ts::packet & packet){
            this->context_.call(packet);
            writer.write(packet);
            return true;
        });
        
        this->ifs.close();
        this->ofs.close();
        
        return 0;
    }
    
    void splitter::on_elementary_pid_change() {
        std::string path = create_filename_(this->base_opath, ++this->split_count);
        this->ofs.close();
        this->ofs.open(path, std::ios::binary);
    }
}

// splitter::context
namespace ts_processor {
    splitter::state * splitter::context::get_current_state() {
        return this->current_state;
    }
    
    void splitter::context::transition(outside::state * next_state) {
        this->current_state = next_state;
        this->current_state->initialize(this);
    }
    
    void splitter::context::call(ts::packet & packet) {
        if (this->current_state != nullptr) this->current_state->call(packet);
    }
    
    void splitter::context::set_elementary_pid(elementary_pid_pair elementary_pid) {
        static elementary_pid_pair const default_value{0,0};
        auto previous_value = this->elementary_pid;
        
        if (this->elementary_pid != elementary_pid) {
            this->elementary_pid = elementary_pid;
            if (previous_value != default_value) this->on_elementary_pid_change();
        }
    }
    
    splitter::context::elementary_pid_pair splitter::context::get_elementary_pid() const {
        return this->elementary_pid;
    }
    
    void splitter::context::set_pmt_pid(uint32_t pid) {
        this->pmt_pid = pid;
    }
    
    uint32_t splitter::context::get_pmt_pid() const {
        return this->pmt_pid;
    }
}

// splitter::state
namespace ts_processor {
    void splitter::state::initialize(outside::context * context) {
        this->context = context;
        this->setup();
    }
}

// splitter::pat_state
namespace ts_processor {
    void splitter::pat_state::setup() {
        this->data.reset(ts::pid::id::pat);
    }
    
    void splitter::pat_state::call(ts::packet & packet) {
        if (this->data.push(packet).test(ts::data::push_state::ready)) {
            for (auto & section: this->data->pat.sections) {
                if (section.type() == ts::psi::pat::pid_type::pmt) {
                    this->context->set_pmt_pid(section.pid);
                    this->context->transition<outside::pmt_state>();
                    return;
                }
            }
        }
    }
}

// splitter::pmt_state
namespace ts_processor {
    void splitter::pmt_state::setup() {
        this->data.reset(this->context->get_pmt_pid());
    }
    
    void splitter::pmt_state::call(ts::packet & packet) {
        if (this->data.push(packet).test(ts::data::push_state::ready)) {
            uint32_t audio_pid = 0;
            uint32_t video_pid = 0;
            
            for (auto & section: this->data->pmt.sections) {
                switch (ts::stream_type::type_of(section.stream_type)) {
                case ts::stream_type::type::audio:
                    if (audio_pid == 0) audio_pid = section.elementary_pid;
                    break;
                case ts::stream_type::type::video:
                    if (video_pid == 0) video_pid = section.elementary_pid;
                    break;
                default:
                    ;
                }
            }
            this->context->set_elementary_pid({video_pid, audio_pid});
            this->context->transition<outside::pmt_state>();
        }
    }
}
