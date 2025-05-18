#include "quadrant_fsm.hpp"

QuadrantFsm::QuadrantFsm()
    : sm(QuadrantFsmDefinition{context}) {}

void QuadrantFsm::tick() {
    sm.process_event(TickEvent{});
}

void QuadrantFsm::toggle() {
    sm.process_event(ToggleEvent{});
}

std::string QuadrantFsm::state_name() const {
    return context.state;
}

int QuadrantFsm::counter() const {
    return context.counter;
}
