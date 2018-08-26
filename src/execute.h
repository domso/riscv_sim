#pragma once

#include <unordered_map>
#include <functional>
#include <stdint.h>
#include "src/context.h"
#include "src/decode.h"

namespace riscv_sim {
    std::unordered_map<uint32_t, std::function<void(context&, decoded_instr&)>> execute_factory();
}
