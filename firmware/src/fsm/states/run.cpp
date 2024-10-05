#include <cstdio>
#include "bsp/debug.hpp"
#include "bsp/leds.hpp"
#include "bsp/motors.hpp"
#include "bsp/timers.hpp"
#include "fsm/state.hpp"
#include "services/maze.hpp"
#include "services/navigation.hpp"
#include "bsp/analog_sensors.hpp"
#include "bsp/ble.hpp"

namespace fsm {

void PreRun::enter() {
    using bsp::leds::Color;

    bsp::debug::print("state:PreRun");

    bsp::leds::stripe_set(0, Color::Green);
    bsp::leds::stripe_set(1, Color::Green);
    bsp::leds::stripe_send();

    bsp::motors::set(0, 0);
}

State* PreRun::react(BleCommand const&) {
    return nullptr;
}

State* PreRun::react(ButtonPressed const& event) {
    if (event.button == ButtonPressed::SHORT1) {
        return &State::get<PreSearch>();
    }

    if (event.button == ButtonPressed::SHORT2) {
        return &State::get<Idle>();
    }

    return nullptr;
}

}
