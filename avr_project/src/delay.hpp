#pragma once
#include <stdint.h>
namespace DELAY
{

    #define REG(r) getReg(r)

    enum class Register : uint8_t
    {
        // Memory-mapped addresses (I/O address + 0x20)
        TCNT0  = 0x46,   // Timer/Counter0 (I/O: 0x26)
        TCCR0A = 0x44,   // Timer/Counter Control Register A (I/O: 0x24)
        TCCR0B = 0x45,   // Timer/Counter Control Register B (I/O: 0x25)
        TIFR0  = 0x35    // Timer Interrupt Flag Register (I/O: 0x15)
    };
    

    namespace Bits
    {
        // TCCR0A bits
        constexpr uint8_t WGM00  = 0;
        constexpr uint8_t WGM01  = 1;
        constexpr uint8_t COM0B0 = 4;
        constexpr uint8_t COM0B1 = 5;
        constexpr uint8_t COM0A0 = 6;
        constexpr uint8_t COM0A1 = 7;

        // TCCR0B bits
        constexpr uint8_t CS00  = 0;
        constexpr uint8_t CS01  = 1;
        constexpr uint8_t CS02  = 2;
        constexpr uint8_t WGM02 = 3;
        constexpr uint8_t FOC0B = 6;
        constexpr uint8_t FOC0A = 7;

        // TIFR0 bits
        constexpr uint8_t TOV0  = 0;
        constexpr uint8_t OCF0A = 1;
        constexpr uint8_t OCF0B = 2;
    } 



    volatile uint8_t & getReg(Register reg)
    {
        return  *reinterpret_cast<volatile uint8_t*>(static_cast<uint8_t>(reg));

    }   


    void delayms(uint16_t delay)
    {
        // Prescaler 64: CS01=1, CS00=1
        getReg(Register::TCCR0B) = (1 << Bits::CS00) | (1 << Bits::CS01);

        uint8_t cnt = 0;
        while(cnt < delay)
        {
            // Reset timer counter
            getReg(Register::TCNT0) = 0;

            while(getReg(Register::TCNT0) < 250)
            {
                // Wait
            }
            cnt++;
        }
    }

    void delayMsOverFlow(uint8_t delay)
    {
        // Prescaler 64: 16MHz / 64 = 250kHz
        // 1 tick = 4us
        // 256 ticks (overflow) = 1.024ms (~1ms)
        
        REG(Register::TCCR0B) = (1 << Bits::CS00) | (1 << Bits::CS01);
        
        uint8_t cnt = 0;
        while(cnt < delay)
        {
            // Reset counter and clear overflow flag BEFORE waiting
            REG(Register::TCNT0) = 0;
            REG(Register::TIFR0) |= (1 << Bits::TOV0);  // Clear flag by writing 1
            
            // Wait for overflow
            while((REG(Register::TIFR0) & (1 << Bits::TOV0)) == 0)
            {
                // Wait
            }
            
            cnt++;
        }
    }

}