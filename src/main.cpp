#include "brine/brine_types.hpp"
#include "brine/context.hpp"
#include "brine/run_loop.hpp"

class MyLoop : public brine::RunLoop {
public:
    void run() override {
        ImGui::Begin("RAII!");
        ImGui::Text("run() from MyLoop");
        ImGui::End();
    }
};

int main() {
    brine::Context context;
    MyLoop loop;
    context.run_main_loop(loop);
    return 0;
}
