[]{
    using packet_set = std::vector<ts::packet *>;
    using split_group = std::vector<packet_set>;
    
    auto make_pes_packet = [](uint32_t length){
        ts::packet * packet = new ts::packet{
            #include <fixture/ts/pes/minimum.cpp>
        };
        packet->payload->pes.pes_packet_length = length;
        return packet;
    };
    
    auto make_pat_packet = []{
        ts::packet * packet = new ts::packet{
            #include <fixture/ts/psi/pat/single_packet.cpp>
        };
        ts::data data(ts::pid::id::pat); data.push(*packet);
        
        auto it = data->psi.get<ts::psi::pat>()->sections.begin();
        (++it)->pid = ts::packet{
            #include <fixture/ts/psi/pmt/single_packet.cpp>
        }.pid;
        
        std::copy(
            data.container().begin(),
            data.container().end(),
            packet->payload->psi.begin()
        );
        return packet;
    };
    
    auto make_pmt_packet = [](uint32_t type){
        ts::packet * packet = new ts::packet{
            #include <fixture/ts/psi/pmt/single_packet.cpp>
        };
        ts::data data(packet->pid); data.push(*packet);
        
        auto it = data->psi.get<ts::psi::pmt>()->sections.begin();
        (it++)->elementary_pid = type == 0 ? 0x013 : 0x0015;
        (it++)->elementary_pid = type == 0 ? 0x014 : 0x0016;
        
        std::copy(
            data.container().begin(),
            data.container().end(),
            packet->payload->psi.begin()
        );
        return packet;
    };
    
    auto make_packet_set = [&](uint32_t no, uint32_t pmt_type){
        auto n = no * 0x10;
        return packet_set{
            make_pmt_packet(pmt_type),
            make_pes_packet(n++),
            make_pes_packet(n++),
            make_pat_packet(),
            make_pes_packet(n++),
            make_pes_packet(n++),
            make_pmt_packet(pmt_type),
            make_pes_packet(n++),
            make_pes_packet(n++),
            make_pat_packet(),
            make_pes_packet(n++),
            make_pes_packet(n++),
            make_pmt_packet(pmt_type),
            make_pes_packet(n++),
            make_pes_packet(n++),
        };
    };
    
    split_group group;
    
    for (auto i=0; i<3; ++i) {
        group.push_back(make_packet_set(i,i%2));
    }
    {
        std::ofstream ofs("tmp/split_group.ts", std::ios::binary);
        ts_processor::writer writer(ofs);
        
        for (auto & packet_set: group) {
            for (auto packet: packet_set) {
                writer.write(*packet);
            }
        }
    }
    return group;
}()
