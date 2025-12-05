#include "gpio.hpp"
#include "delay.hpp"

int main(void)
{
   
    GPIO::pinMode(GPIO::Register::DDRB, GPIO::Pins::PIN5, GPIO::Direction::OUTPUT);

    while (1) 
    {
        GPIO::digitalWrite(GPIO::Register::PORTB, GPIO::Pins::PIN5, GPIO::State::HIGH);
        // DELAY::delayMsOverFlow(500);
        DELAY::delayms(500);

        GPIO::digitalWrite(GPIO::Register::PORTB, GPIO::Pins::PIN5, GPIO::State::LOW);
        DELAY::delayMsOverFlow(500);
         DELAY::delayms(500);
    }
}




