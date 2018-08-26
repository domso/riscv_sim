#include "src/simulator.h"

void riscv_sim::simulator::set_system(const std::function<void (context&, uint32_t)> system) {
    m_system = system;
}


void riscv_sim::simulator::run_cycle(riscv_sim::context& proc) {
    uint32_t currentInstr = get_next_instr(proc);
    auto dec = decode(currentInstr);
    auto callback = m_executeTable.find(dec.opcode & currentInstr);
    if (callback != m_executeTable.end()) {
        callback->second(proc, dec);
    } else {
        proc.status = exceptions::illegal_instruction;
    }

    if (proc.status != exceptions::none) {
        if (m_system) {
            m_system(proc, currentInstr);
        }
    }
}



uint32_t riscv_sim::simulator::get_next_instr(riscv_sim::context& proc) {
     auto result = proc.ROM.get<uint32_t>(proc.pc);
     if (result) {
         return *result;
    }
    
    return 0;
}
