#include <iostream>
#include <basic_log_controller.hpp>

int main()
{
    std::unique_ptr<Test::Logging::BasicLogController> logger{
        std::make_unique<Test::Logging::BasicLogController>("logger", "log.txt")
    };
    
    spdlog::info("Initialised");
    
    return 0;
}