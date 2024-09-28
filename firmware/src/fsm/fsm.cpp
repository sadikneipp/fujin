#include "fsm/fsm.hpp"
#include "bsp/ble.hpp"
#include "bsp/buttons.hpp"
#include "utils/soft_timer.hpp"

#include <variant>

namespace fsm {

FSM::FSM() {
    current_state = &State::get<Idle>();
}

void FSM::start() {
    // TODO: Most of these will probably move to their respective services when needed
    bsp::buttons::register_callback_button1([this](auto type) {
        dispatch(ButtonPressed{
            .button = type == bsp::buttons::PressType::SHORT ? ButtonPressed::SHORT1 : ButtonPressed::LONG1,
        });
    });

    bsp::buttons::register_callback_button2([this](auto type) {
        dispatch(ButtonPressed{
            .button = type == bsp::buttons::PressType::SHORT ? ButtonPressed::SHORT2 : ButtonPressed::LONG2,
        });
    });

    bsp::ble::register_callback([this](bsp::ble::BleHeader packet) {
        switch (packet) {
        case bsp::ble::BLE_BUTTON_1_SHORT:
            dispatch(ButtonPressed{.button = ButtonPressed::SHORT1});
            break;
        case bsp::ble::BLE_BUTTON_2_SHORT:
            dispatch(ButtonPressed{.button = ButtonPressed::SHORT2});
            break;
        case bsp::ble::BLE_BUTTON_1_LONG:
            dispatch(ButtonPressed{.button = ButtonPressed::LONG1});
            break;
        case bsp::ble::BLE_BUTTON_2_LONG:
            dispatch(ButtonPressed{.button = ButtonPressed::LONG2});
            break;
        default:
            break;
        }
    });

    soft_timer::register_callback([this]() { dispatch(Timeout()); });

    current_state->enter();
}

void FSM::spin() {
    Event event;
    if (!event_queue.get(&event)) {
        return;
    }

    auto state = std::visit([this](auto&& evt) { return current_state->react(evt); }, event);

    if (state != nullptr) {
        current_state->exit();
        current_state = state;
        current_state->enter();
    }
}

void FSM::dispatch(Event const& event) {
    event_queue.put(event);
}

}
