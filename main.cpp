#include <iostream>

#include <stdint.h>
#include "src/simulator.h"
#include "src/context.h"

void interrupt(riscv_sim::context& proc, uint32_t instr) {
    switch (proc.status) {
        case riscv_sim::exceptions::illegal_instruction: {
            std::cout << "Illegal Instruction ";
            std::cout << std::hex << "0x" << instr;
            std::cout << " at " << "0x" << proc.pc << std::endl;
            break;
        }
            
        case riscv_sim::exceptions::memory_violation:{
            std::cout << "Memory violation ";
            std::cout << std::hex << "0x" << instr;
            std::cout << " at " << "0x" << proc.pc << std::endl;
            break;
        }
            
        case riscv_sim::exceptions::interrupt:{
            std::cout << "Interrupt ";
            std::cout << std::hex << "0x" << instr;
            std::cout << " at " << "0x" << proc.pc << std::endl;
            proc.pc += 4;
            break;
        }
            
        default: break;
    }
    
    proc.status = riscv_sim::exceptions::none;
}

int main(int argc, char **argv) {
    riscv_sim::context currentContext;
    riscv_sim::simulator simulator;
    simulator.set_system(interrupt);
    
    //small test program directly loaded into memory
    currentContext.ROM.set<uint32_t>(0, 0xb3);
    currentContext.ROM.set<uint32_t>(4, 0xa00113);
    currentContext.ROM.set<uint32_t>(8, 0x108093);
    currentContext.ROM.set<uint32_t>(12, 0xfe20cee3);
    currentContext.ROM.set<uint32_t>(16, 0x20337);
    currentContext.ROM.set<uint32_t>(20, 0xff00093);
    currentContext.ROM.set<uint32_t>(24, 0xfe60ae23);
    currentContext.ROM.set<uint32_t>(28, 0xffc32183);
    currentContext.ROM.set<uint32_t>(32, 0xffc31203);
    currentContext.ROM.set<uint32_t>(36, 0xffc30283);
    currentContext.ROM.set<uint32_t>(40, 0x6f);
    
    for (int i = 0; i < 100; i++) {
        simulator.run_cycle(currentContext);
    }
    
    for (int i = 0; i < 33; i++) {
        std::cout << currentContext.registers[i] << std::endl;
    }
     
    return 0;
}
