#include "brine/brine_types.hpp"
#include "brine/context.hpp"
#include "brine/run_loop.hpp"
#include "state/quadrant_fsm.hpp"

#include <array>

class MyLoop : public brine::RunLoop {
public:
  void run() override {
    ImGui::Begin("Quadrant Demo");
    ImGui::Columns(2, nullptr, false);

    for (int i = 0; i < 4; ++i) {
      machines[i].tick();

      ImGui::PushID(i);
      ImGui::Text("FSM #%d", i + 1);
      ImGui::Text("State: %s", machines[i].state_name().c_str());
      ImGui::Text("Counter: %d", machines[i].counter());
      if (ImGui::Button("Toggle State")) {
        machines[i].toggle();
      }
      ImGui::PopID();

      if (i % 2 == 1)
        ImGui::NextColumn();
    }

    ImGui::Columns(1);
    ImGui::End();
  }

private:
  std::array<QuadrantFsm, 4> machines;
};

int main() {
  brine::Context context;
  MyLoop loop;
  context.run_main_loop(loop);
  return 0;
}
