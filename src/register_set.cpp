#include "src/register_set.h"

riscv_sim::register_set::register_set() {
    m_data[0] = 0;
}

uint32_t& riscv_sim::register_set::operator[](const uint32_t id) {
    if (id < 33) {
        return m_data[id];
    } else {
        return m_overflow;
    }
}

const uint32_t& riscv_sim::register_set::operator[](const uint32_t id) const {
    if (id < 33) {
        return m_data[id];
    } else {
        return m_overflow;
    }
}

void riscv_sim::register_set::set(const uint32_t id, const uint32_t d) {
    if (0 < id && id < 33) {
        m_data[id] = d;
    }
}
uint32_t riscv_sim::register_set::get(const uint32_t id) const {
    if (id < 33) {
        return m_data[id];
    } else {
        return 0;
    }
}
