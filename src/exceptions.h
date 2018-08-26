#pragma once

namespace riscv_sim {
    enum exceptions {
        none,
        illegal_instruction,
        memory_violation,
        interrupt
    };
}
