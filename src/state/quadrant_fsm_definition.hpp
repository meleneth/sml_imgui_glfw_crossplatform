#pragma once

#include <boost/sml.hpp>
#include <string>

class TickEvent {};
class ToggleEvent {};

class FsmContext {
public:
    int counter = 0;
    std::string state = "Idle";
};

class QuadrantFsmDefinition {
public:
    QuadrantFsmDefinition(FsmContext& context) : ctx(context) {}

    auto operator()() const {
        using namespace boost::sml;

        return make_transition_table(
            *state<class Idle> + event<ToggleEvent> / [this] { ctx.state = "Running"; } = state<class Running>,
             state<class Running> + event<ToggleEvent> / [this] { ctx.state = "Idle"; } = state<class Idle>,
             state<class Running> + event<TickEvent> / [this] { ctx.counter++; } = state<class Running>
        );
    }

private:
    FsmContext& ctx;
};
