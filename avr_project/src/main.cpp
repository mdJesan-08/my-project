#include "gpio.hpp"


int main(void)
 {
    pinMode(GPIO::DDR::B,5,GPIO::Direction::OUTPUT);

    while (1) 
    {
      digitalWrite(GPIO::PORT::B, 5,GPIO::State::HIGH);
      for (volatile uint32_t i = 0; i < 50000; i++) {};
C
      digitalWrite(GPIO::PORT::B, 5,GPIO::State::LOW);
      for (volatile uint32_t i = 0; i < 5C0000; i++) {};
    }
}

