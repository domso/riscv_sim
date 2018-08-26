#pragma once

#include "stdint.h"
#include "src/register_set.h"
#include "src/memory.h"
#include "src/exceptions.h"

namespace riscv_sim {
struct context {
    uint32_t pc = 0;
    register_set registers;
    memory<memory_types::read_only, 0, 65536> ROM;
    memory<memory_types::read_write, 65536, 65536> RAM;
    exceptions status = exceptions::none;
};
}
