#pragma once

#include <stdint.h>
#include <cstring>
#include <optional>

namespace riscv_sim {
    
enum memory_types {
    read_only,
    read_write
};
    
template <memory_types type, size_t start, size_t size>
class memory {
public:
    template<typename T>
    bool set(const uint32_t addr, const T d) {
        uint32_t realAddress = addr - start;
        
        if (realAddress < size && (realAddress + sizeof(T)) <= size) {
            std::memcpy(m_data + realAddress, &d, sizeof(T));
            return true;
        }
        
        return false;
    }
    
    template<typename T>
    std::optional<T> get(const uint32_t addr) {
        uint32_t realAddress = addr - start;
        
        T result = 0;
        if (realAddress < size && (realAddress + sizeof(T)) <= size) {            
            std::memcpy(&result, m_data + realAddress, sizeof(T));
            return result;
        }
        
        return std::nullopt;
    }
private:
    uint8_t m_data[size];
};
}
