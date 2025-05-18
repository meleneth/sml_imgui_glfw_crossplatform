#pragma once
#include "brine_types.hpp" // forward decl only

namespace brine {

class Context {
public:
    Context();
    ~Context();

    GLFWwindow* get_window() const;
    void run_main_loop(RunLoop& loop);

private:
    GLFWwindow* window = nullptr;
};

} // namespace brine

