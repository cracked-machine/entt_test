
#include <SFML/System/Vector2.hpp>
#include <basic_log_controller.hpp>
#include <engine1.hpp>
#include <engine2.hpp>
#include <reactive_engine1.hpp>
#include <entt/entity/registry.hpp>
#include <spdlog/spdlog.h>

int main()
{
    // logging
    std::unique_ptr<Test::Logging::BasicLogController> logger{
        std::make_unique<Test::Logging::BasicLogController>("logger", "log.txt")
    };
    SPDLOG_INFO("Initialised");

    Test::ReactiveEngine1 eng; // use registry.emplace
    // Test::Engine2 eng;  // use registry.insert

    return 0;
}