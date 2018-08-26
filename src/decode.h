#pragma once

#include <stdint.h>

namespace riscv_sim {
struct decoded_instr {
    uint32_t immediate;
    uint32_t opcode;
    uint32_t rd;
    uint32_t rs1;
    uint32_t rs2;    
};

uint32_t extend_if_match(const uint32_t x, const uint32_t mask, const uint32_t ext);
decoded_instr decode_R_type(const uint32_t instr);
decoded_instr decode_I_type(const uint32_t instr);
decoded_instr decode_S_type(const uint32_t instr);
decoded_instr decode_B_type(const uint32_t instr);
decoded_instr decode_U_type(const uint32_t instr);
decoded_instr decode_J_type(const uint32_t instr);
decoded_instr decode(const uint32_t instr);
}
