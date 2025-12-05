#pragma once
#include <stdint.h>

namespace GPIO
{
    #define REG(r) getReg(r)

    enum class Register : uint8_t
    {
        // Memory-mapped addresses (I/O address + 0x20)
        PINB  = 0x23,    // Port B Input Pins (I/O: 0x03)
        DDRB  = 0x24,    // Port B Data Direction Register (I/O: 0x04)
        PORTB = 0x25,    // Port B Data Register (I/O: 0x05)

        PINC  = 0x26,    // Port C Input Pins (I/O: 0x06)
        DDRC  = 0x27,    // Port C Data Direction Register (I/O: 0x07)
        PORTC = 0x28,    // Port C Data Register (I/O: 0x08)

        PIND  = 0x29,    // Port D Input Pins (I/O: 0x09)
        DDRD  = 0x2A,    // Port D Data Direction Register (I/O: 0x0A)
        PORTD = 0x2B     // Port D Data Register (I/O: 0x0B)
    };

    namespace Pins
    {
        // Pin bit positions (0-7)
        constexpr uint8_t PIN0 = 0;
        constexpr uint8_t PIN1 = 1;
        constexpr uint8_t PIN2 = 2;
        constexpr uint8_t PIN3 = 3;
        constexpr uint8_t PIN4 = 4;
        constexpr uint8_t PIN5 = 5;
        constexpr uint8_t PIN6 = 6;
        constexpr uint8_t PIN7 = 7;
    }

    enum class Direction : uint8_t
    {
        INPUT  = 0,
        OUTPUT = 1
    };

    enum class State : uint8_t
    {
        LOW  = 0,
        HIGH = 1
    };


    volatile uint8_t& getReg(Register reg)
    {
        return *reinterpret_cast<volatile uint8_t*>(static_cast<uint8_t>(reg));
    }


    void pinMode(Register ddr, uint8_t pinNo, Direction dir)
    {
        if (dir == Direction::OUTPUT)
        {
            REG(ddr) |= (1 << pinNo);   // Set bit for OUTPUT
        }
        else
        {
             REG(ddr) &= ~(1 << pinNo);  // Clear bit for INPUT
        }
    }


    void digitalWrite(Register port, uint8_t pinNo, State state)
    {
        if (state == State::HIGH)
        {
            REG(port) |= (1 << pinNo);   // Set bit HIGH
        }
        else
        {
             REG(port) &= ~(1 << pinNo);  // Clear bit LOW
        }
    }


    State digitalRead(Register pin, uint8_t pinNo)
    {

        return ( REG(pin) & (1 << pinNo))? State::HIGH : State::LOW;
    }


    void toggle(Register port, uint8_t pinNo)
    {
        REG(port) ^= (1 << pinNo);  // XOR to toggle
    }

}
