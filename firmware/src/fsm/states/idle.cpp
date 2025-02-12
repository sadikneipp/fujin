#include "bsp/analog_sensors.hpp"
#include "bsp/debug.hpp"
#include "bsp/leds.hpp"
#include "bsp/motors.hpp"
#include "fsm/state.hpp"
#include "utils/soft_timer.hpp"
#include "bsp/buzzer.hpp"
#include "bsp/timers.hpp"
#include "bsp/ble.hpp"

namespace fsm {

void Idle::enter() {
    using bsp::leds::Color;

    bsp::debug::print("state:Idle");

    if (bsp::analog_sensors::battery_low()) {
        bsp::leds::stripe_set(Color::Red);
    } else {
        bsp::leds::stripe_set(Color::Black);
    }

    bsp::motors::set(0, 0);
    bsp::ble::unlock_config_rcv();
}

State* Idle::react(BleCommand const&) {
    bsp::buzzer::start();
    bsp::delay_ms(300);
    bsp::buzzer::stop();

    return nullptr;
}

State* Idle::react(ButtonPressed const& event) {
    if (event.button == ButtonPressed::SHORT1) {
        return &State::get<PreRun>();
    }

    if (event.button == ButtonPressed::SHORT2) {
        return &State::get<PreCalib>();
    }

    return nullptr;
}

State* Idle::react(Timeout const&) {
    return nullptr;
}

void Idle::exit() {
    bsp::ble::lock_config_rcv();
}

}
