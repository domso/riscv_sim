#include "src/decode.h"

uint32_t riscv_sim::extend_if_match(const uint32_t x, const uint32_t mask, const uint32_t ext) {
    if ((x & mask) != 0) {
        return ext | x;
    } else {
        return x;
    }
}

riscv_sim::decoded_instr riscv_sim::decode_R_type(const uint32_t instr) {
    return {0, instr & 0xF700707F, (instr >> 7) & 0x1F, (instr >> 15) & 0x1F, (instr >> 20) & 0x1F};
}

riscv_sim::decoded_instr riscv_sim::decode_I_type(const uint32_t instr) {
    return {
        extend_if_match((instr >> 20) & 0xFFF,0x800, 0xFFFFF000),
        instr & 0x0000707F,
        (instr >> 7) & 0x1F,
        (instr >> 15) & 0x1F,
        0        
    };
}

riscv_sim::decoded_instr riscv_sim::decode_S_type(const uint32_t instr) {
    return {
        extend_if_match((((instr >> 25) & 0x7F) << 5) | ((instr >> 7) & 0x1F),0x800, 0xFFFFF000),
        instr & 0x0000707F,
        0,
        (instr >> 15) & 0x1F,
        (instr >> 20) & 0x1F        
    };
}

riscv_sim::decoded_instr riscv_sim::decode_B_type(const uint32_t instr) {    
    return {
        extend_if_match(
        (((instr >> 25) & 0x40) << 6) | 
        (((instr >> 7) & 0x1) << 11) |
        (((instr >> 25) & 0x3F) << 5) |
        (((instr >> 7) & 0x1E))
            
        ,0x1000, 0xFFFFE000),
        
        instr & 0x0000707F, 0, (instr >> 15) & 0x1F, (instr >> 20) & 0x1F};
}

riscv_sim::decoded_instr riscv_sim::decode_U_type(const uint32_t instr) {
    return {instr & 0xFFFFF000, instr & 0x0000007F, (instr >> 7) & 0x1F, 0, 0};
}

riscv_sim::decoded_instr riscv_sim::decode_J_type(const uint32_t instr) {
    return {
        extend_if_match(
        (instr & 0x80000000) >> 11 | 
        (instr & 0x7FE00000) >> 20 |
        (instr & 0x00100000) >> 8  |
        (instr & 0xFF000),
        0x100000, 0xFFE00000),
        instr & 0x0000007F, (instr >> 7) & 0x1F, 0, 0};
}

riscv_sim::decoded_instr riscv_sim::decode(const uint32_t instr) {
    switch (instr & 0x7F) {
        case 0x33: return decode_R_type(instr);
        case 0x13: return decode_I_type(instr);
        case 0x23: return decode_S_type(instr);
        case 0x03: return decode_I_type(instr);
        case 0x63: return decode_B_type(instr);
        case 0x67: return decode_I_type(instr);
        case 0x6F: return decode_J_type(instr);
        case 0x37: return decode_U_type(instr);
        case 0x17: return decode_U_type(instr);
        
        default: return {0, 0, 0, 0, 0};
    }
}
