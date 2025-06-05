#include<boost/sml.hpp>
#include <deque>
#include <string>
#include <array>

#include "brine/brine_types.hpp"
#include "brine/context.hpp"
#include "brine/run_loop.hpp"

// Logging support
enum class LogLevel {
    Info,
    Warning,
    Error
};

struct LogEntry {
    LogLevel level;
    std::string message;
};

class LogBuffer {
public:
    void log(LogLevel level, const std::string& message) {
        if (entries.size() >= max_entries) {
            entries.pop_front();
        }
        entries.push_back({level, message});
    }

    const std::deque<LogEntry>& get_entries() const {
        return entries;
    }

    void clear() {
        entries.clear();
    }

private:
    static constexpr size_t max_entries = 10;
    std::deque<LogEntry> entries;
};

ImVec4 GetColorForLevel(LogLevel level) {
    switch (level) {
        case LogLevel::Info:    return ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // White
        case LogLevel::Warning: return ImVec4(1.0f, 1.0f, 0.0f, 1.0f); // Yellow
        case LogLevel::Error:   return ImVec4(1.0f, 0.4f, 0.4f, 1.0f); // Light Red
        default:                return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
}

void RenderLogWidget(const LogBuffer& log_buffer) {
    ImGui::Begin("Log");

    static bool auto_scroll = true;
    static bool show_info = true, show_warn = true, show_error = true;

    // Filter options
    ImGui::Checkbox("Info", &show_info); ImGui::SameLine();
    ImGui::Checkbox("Warn", &show_warn); ImGui::SameLine();
    ImGui::Checkbox("Error", &show_error);

    ImGui::Separator();

    ImGui::BeginChild("LogRegion", ImVec2(0, 150), true, ImGuiWindowFlags_HorizontalScrollbar);
    for (const auto& entry : log_buffer.get_entries()) {
        bool visible = 
            (entry.level == LogLevel::Info && show_info) ||
            (entry.level == LogLevel::Warning && show_warn) ||
            (entry.level == LogLevel::Error && show_error);

        if (!visible) continue;

        ImVec4 color = GetColorForLevel(entry.level);
        ImGui::PushStyleColor(ImGuiCol_Text, color);
        ImGui::TextUnformatted(entry.message.c_str());
        ImGui::PopStyleColor();
    }

    if (auto_scroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);
    ImGui::EndChild();

    ImGui::End();
}

// State Machine Events
class RenderEvent {};
class NextEvent {};

// State Machine States
class StartState {};
class State_01 {};
class State_02 {};
class State_MultipleChoice {};
class State_Loop_01 {};
class State_ContinuingOn {};
class State_CheckTheThings {};
class State_FinalizeStuff {};
class State_Final {};

struct FSMContext {
    bool chose_alternate_path = false;
    LogBuffer* log = nullptr;
};

namespace sml = boost::sml;
// Main State Machine
struct StateMachine {
    auto operator()() const {
        using namespace sml;

        // actions
        auto render = [](const auto& state_name) {
            return [state_name](const RenderEvent&) {
                ImGui::Text("Current state: %s", state_name);
            };
        };

        // guards
        auto chose_alt = [](const FSMContext& ctx) {
            return ctx.chose_alternate_path;
        };

        return make_transition_table(
            // Start
            *state<class StartState> + event<RenderEvent> / render("StartState"),
             state<class StartState> + event<NextEvent> = state<class State_01>,
             state<class StartState> + sml::on_entry<_> / [](FSMContext& ctx) {
                ctx.log->log(LogLevel::Warning, "→ Entered State_StartState");
             },

            // State_01
             state<class State_01> + event<RenderEvent> / render("State_01"),
             state<class State_01> + event<NextEvent> = state<class State_02>,

            // State_02
             state<class State_02> + event<RenderEvent> / render("State_02"),
             state<class State_02> + event<NextEvent> = state<class State_MultipleChoice>,

            // MultipleChoice
             state<class State_MultipleChoice> + event<RenderEvent> / render("MultipleChoice"),
             state<class State_MultipleChoice> + event<NextEvent>[chose_alt] = state<class State_ContinuingOn>,
             state<class State_MultipleChoice> + event<NextEvent> = state<State_Loop_01>,
             state<class State_MultipleChoice> + sml::on_entry<_> / [](FSMContext& ctx) {
                ctx.log->log(LogLevel::Warning, "→ Entered State_MultipleChoice");
             },

            // Loop_01
             state<class State_Loop_01> + event<RenderEvent> / render("Loop_01"),
             state<class State_Loop_01> + event<NextEvent> = state<class State_01>,
             state<class State_Loop_01> + sml::on_entry<_> / [](FSMContext& ctx) {
                ctx.log->log(LogLevel::Error, "→ Entered Loop_01");
             },

            // ContinuingOn
             state<class State_ContinuingOn> + event<RenderEvent> / render("ContinuingOn"),
             state<class State_ContinuingOn> + event<NextEvent> = state<class State_CheckTheThings>,
             state<class State_ContinuingOn> + sml::on_entry<_> / [](FSMContext& ctx) {
                ctx.log->log(LogLevel::Warning, "→ Entered State_ContinuingOn");
             },

            // CheckTheThings
             state<class State_CheckTheThings> + event<RenderEvent> / render("CheckTheThings"),
             state<class State_CheckTheThings> + event<NextEvent> = state<class State_FinalizeStuff>,

            // FinalizeStuff
             state<class State_FinalizeStuff> + event<RenderEvent> / render("FinalizeStuff"),
             state<class State_FinalizeStuff> + event<NextEvent> = state<class State_Final>,

            // Final
             state<class State_Final> + event<RenderEvent> / render("Final")
        );
    }
};



// Main Program Loop
class MyLoop : public brine::RunLoop {
public:
  MyLoop(FSMContext& ctx, sml::sm<StateMachine>& sm, LogBuffer& log)
    : ctx(ctx), sm(sm), log(log){}

  void run() override {
    ImGui::Begin("Standalone Complex Demo");
    sm.process_event(RenderEvent{});
    if (ImGui::Button("Next")) {
        log.log(LogLevel::Info, "Sending NextEvent");
        sm.process_event(NextEvent{});
    }

    if (ImGui::Button("Choose Alternate Path")) {
        log.log(LogLevel::Info, "Choosing AlternatePath");
        ctx.chose_alternate_path = true;
    }

    ImGui::End();
		RenderLogWidget(log);
  }
private:
  FSMContext& ctx;
  sml::sm<StateMachine>& sm;
  LogBuffer& log;
};

int main() {
  brine::Context context;
	LogBuffer log;
  FSMContext ctx;
  ctx.log = &log;

  sml::sm<StateMachine> sm{ctx};
  MyLoop loop(ctx, sm, log);

	log.log(LogLevel::Info, "Starting up!");
	log.log(LogLevel::Warning, "Low memory!");
	log.log(LogLevel::Error, "Crisis!");

  context.run_main_loop(loop);
  return 0;
}
