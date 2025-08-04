#ifndef __TEST_SFML3_ASYNC_LOG_CONTROLLER_HPP__
#define __TEST_SFML3_ASYNC_LOG_CONTROLLER_HPP__

#include <spdlog/async_logger.h>
#include <spdlog/common.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <spdlog/async.h>

namespace Test::Sprite {

// Follows the Model–view–controller pattern:
//
// 1 Internal Model: 
// - `spdlog::async_logger`
//
// 2 External Views: 
// - `spdlog::sinks::stdout_color_sink_mt` 
// - `spdlog::sinks::basic_file_sink_mt`
class AsyncLogController {
public:
    AsyncLogController() {
        spdlog::init_thread_pool(8192, 1); // queue with 8k items and 1 backing thread.
        m_console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        m_file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(m_log_path, true);
   
        m_async_logger = std::make_shared<spdlog::async_logger>(
            m_log_name, 
            spdlog::sinks_init_list{m_console_sink, m_file_sink},
            spdlog::thread_pool(), 
            spdlog::async_overflow_policy::overrun_oldest
        );
        
        spdlog::register_logger(m_async_logger);
        spdlog::set_default_logger(m_async_logger);
        spdlog::flush_on(spdlog::level::trace); 
    }
private:
    std::string m_log_path{ "logs/log.txt" };
    std::string m_log_name{ "sprite_test" };
    std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> m_console_sink;
    std::shared_ptr<spdlog::sinks::basic_file_sink_mt> m_file_sink;
    std::shared_ptr<spdlog::async_logger> m_async_logger;
    
};

} // namespace Test::Sprite

#endif // __TEST_SFML3_ASYNC_LOG_CONTROLLER_HPP__