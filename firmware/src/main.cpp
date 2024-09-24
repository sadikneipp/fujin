#include "bsp/buzzer.hpp"
#include "bsp/core.hpp"
#include "bsp/leds.hpp"
#include "bsp/timers.hpp"
#include "fsm/fsm.hpp"
#include "fsm/state.hpp"
#include "bsp/analog_sensors.hpp"

void startup() {
    bsp::buzzer::set_frequency(2500);
    bsp::buzzer::set_volume(25);
    bsp::buzzer::start();

    for (int i = 0; i < 10; i++) {
        bsp::leds::indication_toggle();
        bsp::delay_ms(100);
    }

    bsp::leds::indication_off();
    bsp::buzzer::stop();
    bsp::analog_sensors::start();
}

int main() {
    bsp::init();

    startup();

    fsm::FSM fsm;

    fsm.start();

    for (;;) {
        fsm.spin();
    }
}
