#include "src/execute.h"

#include <stdint.h>

namespace riscv_sim {
namespace instr_set {
struct add {
    constexpr static const uint32_t mask = 0x00000033;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.registers[instr.rd] = currentContext.registers[instr.rs1] + currentContext.registers[instr.rs2];
        currentContext.pc += 4;
    }
};

struct sub {
    constexpr static const uint32_t mask = 0x40000033;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.registers[instr.rd] = currentContext.registers[instr.rs1] - currentContext.registers[instr.rs2];
        currentContext.pc += 4;
    }
};

struct sll {
    constexpr static const uint32_t mask = 0x00001033;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.registers[instr.rd] = currentContext.registers[instr.rs1] << currentContext.registers[instr.rs2];
        currentContext.pc += 4;
    }
};

struct slt {
    constexpr static const uint32_t mask = 0x00002033;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.registers[instr.rd] = ((int32_t)currentContext.registers[instr.rs1]) < ((int32_t)currentContext.registers[instr.rs2]);
        currentContext.pc += 4;
    }
};

struct sltu {
    constexpr static const uint32_t mask = 0x00003033;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.registers[instr.rd] = currentContext.registers[instr.rs1] < currentContext.registers[instr.rs2];
        currentContext.pc += 4;
    }
};

struct xor_ {
    constexpr static const uint32_t mask = 0x00004033;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.registers[instr.rd] = currentContext.registers[instr.rs1] ^ currentContext.registers[instr.rs2];
        currentContext.pc += 4;
    }
};

struct srl {
    constexpr static const uint32_t mask = 0x00005033;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.registers[instr.rd] = currentContext.registers[instr.rs1] >> currentContext.registers[instr.rs2];
        currentContext.pc += 4;
    }
};

struct sra {
    constexpr static const uint32_t mask = 0x40005033;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.registers[instr.rd] = ((int32_t)currentContext.registers[instr.rs1]) >> ((int32_t)currentContext.registers[instr.rs2]);
        currentContext.pc += 4;
    }
};

struct or_ {
    constexpr static const uint32_t mask = 0x00006033;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.registers[instr.rd] = currentContext.registers[instr.rs1] | currentContext.registers[instr.rs2];
        currentContext.pc += 4;
    }
};

struct and_ {
    constexpr static const uint32_t mask = 0x00007033;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.registers[instr.rd] = currentContext.registers[instr.rs1] & currentContext.registers[instr.rs2];
        currentContext.pc += 4;
    }
};

struct addi {
    constexpr static const uint32_t mask = 0x00000013;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.registers[instr.rd] = currentContext.registers[instr.rs1] + instr.immediate;
        currentContext.pc += 4;
    }
};

struct slti {
    constexpr static const uint32_t mask = 0x00002013;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.registers[instr.rd] = ((int32_t)currentContext.registers[instr.rs1]) < ((int32_t)instr.immediate);
        currentContext.pc += 4;
    }
};

struct sltiu {
    constexpr static const uint32_t mask = 0x00003013;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.registers[instr.rd] = currentContext.registers[instr.rs1] < instr.immediate;
        currentContext.pc += 4;
    }
};

struct xori {
    constexpr static const uint32_t mask = 0x00004013;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.registers[instr.rd] = currentContext.registers[instr.rs1] ^ instr.immediate;
        currentContext.pc += 4;
    }
};

struct ori {
    constexpr static const uint32_t mask = 0x00006013;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.registers[instr.rd] = currentContext.registers[instr.rs1] | instr.immediate;
        currentContext.pc += 4;
    }
};

struct andi {
    constexpr static const uint32_t mask = 0x00007013;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.registers[instr.rd] = currentContext.registers[instr.rs1] & instr.immediate;
        currentContext.pc += 4;
    }
};

struct sb {
    constexpr static const uint32_t mask = 0x00000023;
    static void execute(context& currentContext, decoded_instr& instr) {
        uint32_t addr = currentContext.registers[instr.rs2] + instr.immediate;
        
        if (currentContext.RAM.set<uint8_t>(addr, currentContext.registers[instr.rs1])) {
            currentContext.pc += 4;
        } else {
            currentContext.status = exceptions::memory_violation;
        }      
    }
};

struct sh {
    constexpr static const uint32_t mask = 0x00001023;
    static void execute(context& currentContext, decoded_instr& instr) {
        uint32_t addr = currentContext.registers[instr.rs2] + instr.immediate;
        if (currentContext.RAM.set<uint16_t>(addr, currentContext.registers[instr.rs1])) {
            currentContext.pc += 4;
        } else {
            currentContext.status = exceptions::memory_violation;
        }
    }
};

struct sw {
    constexpr static const uint32_t mask = 0x00002023;
    static void execute(context& currentContext, decoded_instr& instr) {
        uint32_t addr = currentContext.registers[instr.rs2] + instr.immediate;
        if (currentContext.RAM.set<uint32_t>(addr, currentContext.registers[instr.rs1])) {
            currentContext.pc += 4;
        } else {
            currentContext.status = exceptions::memory_violation;
        }
    }
};

struct lb {
    constexpr static const uint32_t mask = 0x00000003;
    static void execute(context& currentContext, decoded_instr& instr) {
        uint32_t addr = currentContext.registers[instr.rs1] + instr.immediate;
        auto resultROM = currentContext.ROM.get<int8_t>(addr);
        auto resultRAM = currentContext.RAM.get<int8_t>(addr);
        
        if (resultROM) {
            currentContext.registers[instr.rd] = *resultROM;
            currentContext.pc += 4;
        } else if (resultRAM) {
            currentContext.registers[instr.rd] = *resultRAM;
            currentContext.pc += 4;
        } else {
            currentContext.status = exceptions::memory_violation;            
        }
    }
};

struct lh {
    constexpr static const uint32_t mask = 0x00001003;
    static void execute(context& currentContext, decoded_instr& instr) {
        uint32_t addr = currentContext.registers[instr.rs1] + instr.immediate;
        auto resultROM = currentContext.ROM.get<int16_t>(addr);
        auto resultRAM = currentContext.RAM.get<int16_t>(addr);
        
        if (resultROM) {
            currentContext.registers[instr.rd] = *resultROM;
            currentContext.pc += 4;
        } else if (resultRAM) {
            currentContext.registers[instr.rd] = *resultRAM;
            currentContext.pc += 4;
        } else {
            currentContext.status = exceptions::memory_violation;            
        }
    }
};

struct lw {
    constexpr static const uint32_t mask = 0x00002003;
    static void execute(context& currentContext, decoded_instr& instr) {
        uint32_t addr = currentContext.registers[instr.rs1] + instr.immediate;        
        auto resultROM = currentContext.ROM.get<int32_t>(addr);
        auto resultRAM = currentContext.RAM.get<int32_t>(addr);
        
        if (resultROM) {
            currentContext.registers[instr.rd] = *resultROM;
            currentContext.pc += 4;
        } else if (resultRAM) {
            currentContext.registers[instr.rd] = *resultRAM;
            currentContext.pc += 4;
        } else {
            currentContext.status = exceptions::memory_violation;            
        }
    }
};

struct lbu {
    constexpr static const uint32_t mask = 0x00004003;
    static void execute(context& currentContext, decoded_instr& instr) {
        uint32_t addr = currentContext.registers[instr.rs1] + instr.immediate;        
        auto resultROM = currentContext.ROM.get<uint8_t>(addr);
        auto resultRAM = currentContext.RAM.get<uint8_t>(addr);
        
        if (resultROM) {
            currentContext.registers[instr.rd] = *resultROM;
            currentContext.pc += 4;
        } else if (resultRAM) {
            currentContext.registers[instr.rd] = *resultRAM;
            currentContext.pc += 4;
        } else {
            currentContext.status = exceptions::memory_violation;            
        }
    }
};

struct lhu {
    constexpr static const uint32_t mask = 0x00005003;
    static void execute(context& currentContext, decoded_instr& instr) {
        uint32_t addr = currentContext.registers[instr.rs1] + instr.immediate;
        auto resultROM = currentContext.ROM.get<uint16_t>(addr);
        auto resultRAM = currentContext.RAM.get<uint16_t>(addr);
        
        if (resultROM) {
            currentContext.registers[instr.rd] = *resultROM;
            currentContext.pc += 4;
        } else if (resultRAM) {
            currentContext.registers[instr.rd] = *resultRAM;
            currentContext.pc += 4;
        } else {
            currentContext.status = exceptions::memory_violation;            
        }
    }
};

struct beq {
    constexpr static const uint32_t mask = 0x00000063;
    static void execute(context& currentContext, decoded_instr& instr) {
        if (currentContext.registers[instr.rs1] == currentContext.registers[instr.rs2]) {
            currentContext.pc += instr.immediate;
        } else {
            currentContext.pc += 4;
        }
    }
};

struct bne {
    constexpr static const uint32_t mask = 0x00001063;
    static void execute(context& currentContext, decoded_instr& instr) {
        if (currentContext.registers[instr.rs1] != currentContext.registers[instr.rs2]) {
            currentContext.pc += instr.immediate;
        } else {
            currentContext.pc += 4;
        }
    }
};

struct blt {
    constexpr static const uint32_t mask = 0x00004063;
    static void execute(context& currentContext, decoded_instr& instr) {
        if (((int32_t)currentContext.registers[instr.rs1]) < ((int32_t)currentContext.registers[instr.rs2])) {
            currentContext.pc += instr.immediate;
        } else {
            currentContext.pc += 4;
        }
    }
};

struct bge {
    constexpr static const uint32_t mask = 0x00005063;
    static void execute(context& currentContext, decoded_instr& instr) {
        if (((int32_t)currentContext.registers[instr.rs1]) >= ((int32_t)currentContext.registers[instr.rs2])) {
            currentContext.pc += instr.immediate;
        } else {
            currentContext.pc += 4;
        }
    }
};

struct bltu {
    constexpr static const uint32_t mask = 0x00006063;
    static void execute(context& currentContext, decoded_instr& instr) {
        if (currentContext.registers[instr.rs1] < currentContext.registers[instr.rs2]) {
            currentContext.pc += instr.immediate;
        } else {
            currentContext.pc += 4;
        }
    }
};

struct bgeu {
    constexpr static const uint32_t mask = 0x00007063;
    static void execute(context& currentContext, decoded_instr& instr) {
        if (currentContext.registers[instr.rs1] >= currentContext.registers[instr.rs2]) {
            currentContext.pc += instr.immediate;
        } else {
            currentContext.pc += 4;
        }
    }
};

struct jalr {
    constexpr static const uint32_t mask = 0x00000067;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.registers[instr.rd] = currentContext.pc + 4;
        currentContext.pc = currentContext.registers[instr.rs1] + instr.immediate;
    }
};

struct jal {
    constexpr static const uint32_t mask = 0x0000006F;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.registers[instr.rd] = currentContext.pc + 4;
        currentContext.pc += instr.immediate;
    }
};

struct lui {
    constexpr static const uint32_t mask = 0x00000037;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.registers[instr.rd] = instr.immediate;
        currentContext.pc += 4;
    }
};

struct auipc {
    constexpr static const uint32_t mask = 0x00000017;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.pc += instr.immediate;
    }
};

struct fence {
    constexpr static const uint32_t mask = 0x0000000F;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.pc += 4;
    }
};

struct ecall {
    constexpr static const uint32_t mask = 0x00000073;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.status = exceptions::interrupt;
    }
};

struct ebreak {
    constexpr static const uint32_t mask = 0x00100073;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.pc += 4;
    }
};

struct csrrw {
    constexpr static const uint32_t mask = 0x00001073;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.pc += 4;
    }
};

struct csrrs {
    constexpr static const uint32_t mask = 0x00002073;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.pc += 4;
    }
};

struct csrrc {
    constexpr static const uint32_t mask = 0x00003073;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.pc += 4;
    }
};

struct csrrwi {
    constexpr static const uint32_t mask = 0x00005073;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.pc += 4;
    }
};

struct csrrsi {
    constexpr static const uint32_t mask = 0x00006073;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.pc += 4;
    }
};

struct csrrci {
    constexpr static const uint32_t mask = 0x00007073;
    static void execute(context& currentContext, decoded_instr& instr) {
        currentContext.pc += 4;
    }
};

template <typename T>
void register_instr(std::unordered_map<std::uint32_t, std::function<void(context&, decoded_instr&)>>& set) {
    set[T::mask] = T::execute;
}

}
}
std::unordered_map<uint32_t, std::function<void(riscv_sim::context&, riscv_sim::decoded_instr&)>> riscv_sim::execute_factory() {
    std::unordered_map<std::uint32_t, std::function<void(context&, decoded_instr&)>> result;

    instr_set::register_instr<instr_set::add>(result);
    instr_set::register_instr<instr_set::sub>(result);
    instr_set::register_instr<instr_set::sll>(result);
    instr_set::register_instr<instr_set::slt>(result);
    instr_set::register_instr<instr_set::sltu>(result);
    instr_set::register_instr<instr_set::xor_>(result);
    instr_set::register_instr<instr_set::srl>(result);
    instr_set::register_instr<instr_set::sra>(result);
    instr_set::register_instr<instr_set::or_>(result);
    instr_set::register_instr<instr_set::and_>(result);

    instr_set::register_instr<instr_set::addi>(result);
    instr_set::register_instr<instr_set::slti>(result);
    instr_set::register_instr<instr_set::sltiu>(result);
    instr_set::register_instr<instr_set::xori>(result);
    instr_set::register_instr<instr_set::ori>(result);
    instr_set::register_instr<instr_set::andi>(result);

    instr_set::register_instr<instr_set::sb>(result);
    instr_set::register_instr<instr_set::sh>(result);
    instr_set::register_instr<instr_set::sw>(result);

    instr_set::register_instr<instr_set::lb>(result);
    instr_set::register_instr<instr_set::lh>(result);
    instr_set::register_instr<instr_set::lw>(result);
    instr_set::register_instr<instr_set::lbu>(result);
    instr_set::register_instr<instr_set::lhu>(result);

    instr_set::register_instr<instr_set::beq>(result);
    instr_set::register_instr<instr_set::bne>(result);
    instr_set::register_instr<instr_set::blt>(result);
    instr_set::register_instr<instr_set::bge>(result);
    instr_set::register_instr<instr_set::bltu>(result);
    instr_set::register_instr<instr_set::bgeu>(result);

    instr_set::register_instr<instr_set::jalr>(result);
    instr_set::register_instr<instr_set::jal>(result);

    instr_set::register_instr<instr_set::lui>(result);
    instr_set::register_instr<instr_set::auipc>(result);
    
    instr_set::register_instr<instr_set::fence>(result);
    instr_set::register_instr<instr_set::ecall>(result);
    instr_set::register_instr<instr_set::ebreak>(result);
    instr_set::register_instr<instr_set::csrrw>(result);
    instr_set::register_instr<instr_set::csrrs>(result);
    instr_set::register_instr<instr_set::csrrc>(result);
    instr_set::register_instr<instr_set::csrrwi>(result);
    instr_set::register_instr<instr_set::csrrsi>(result);
    instr_set::register_instr<instr_set::csrrci>(result);
    
    return result;
}
