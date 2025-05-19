#include "quadrant_fsm.hpp"

QuadrantFsm::QuadrantFsm() : sm(QuadrantFsmDefinition{context}) {}

void QuadrantFsm::tick() { sm.process_event(TickEvent{}); }

void QuadrantFsm::toggle() { sm.process_event(ToggleEvent{}); }

std::string QuadrantFsm::label_name() const { return context.label; }

int QuadrantFsm::counter() const { return context.counter; }
