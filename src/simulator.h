#pragma once

#include "src/decode.h"
#include "src/execute.h"

namespace riscv_sim {
    class simulator {
    public:
        void set_system(const std::function<void(context&, uint32_t)> system);
        void run_cycle(context& proc);
    private:
        uint32_t get_next_instr(context& proc);
        
        std::unordered_map<uint32_t, std::function<void(context&, decoded_instr&)>> m_executeTable = execute_factory();
        std::function<void(context&, uint32_t)> m_system = nullptr;
    };
}
