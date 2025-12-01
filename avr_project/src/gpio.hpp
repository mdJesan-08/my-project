#pragma once

#include <stdint.h>

namespace GPIO
{
    enum class DDR : uint16_t
    {
        B = 0x24
    };

    enum class PORT : uint16_t
    {
      B = 0x25
    };

    enum class Direction : uint8_t
    {
        INPUT, OUTPUT
    };

    enum class State : uint8_t
    {
      LOW, HIGH
    };

    void pinMode(DDR ddr, uint8_t pinNo, Direction dir)
    {
        volatile uint8_t* ddrReg = reinterpret_cast<volatile uint8_t*>(static_cast<uint8_t>(ddr));
        if(dir == Direction::OUTPUT) *ddrReg |= (1<<pinNo);
    }
    

    void digitalWrite(PORT port, uint8_t pinNo, State state)
    {
       volatile uint8_t* portReg = reinterpret_cast<volatile uint8_t*>(static_cast<uint8_t>(port));
       if(state == State::HIGH) *portReg |= (1<<pinNo);
       else *portReg &= (0<<pinNo);
    }

}
