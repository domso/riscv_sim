#pragma once

#include "stdint.h"

namespace riscv_sim {
class register_set {
public:
    register_set();
    const uint32_t& operator[](const uint32_t id) const;
    uint32_t& operator[](const uint32_t id);
    void set(const uint32_t id, const uint32_t d);
    uint32_t get(const uint32_t id) const;
private:
    uint32_t m_data[33];
    uint32_t m_overflow;
};
}
