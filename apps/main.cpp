
#include <memory>

#include "aec.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"




int main()
{
    // Create and initialize logger sinks
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::debug);

    auto file_sink_max_size{1'048'576 * 2};
    auto file_sink_max_files{4};
    auto file_sink_truncate{true};
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        "logs/aec.log", 
        file_sink_max_size, 
        file_sink_max_files, 
        file_sink_truncate
    );
    file_sink->set_level(spdlog::level::trace);

    // Create and initialize a logger
    auto logger = std::make_shared<spdlog::logger>("multi_logger", spdlog::sinks_init_list{console_sink, file_sink});
    // logger->set_level(spdlog::level::debug);
    spdlog::register_logger(logger);
    spdlog::set_default_logger(logger);
    spdlog::flush_on(spdlog::level::critical);




    const std::string farend_out_filepath{"datasets/echo_fileid_0.wav"};
    const std::string farend_in_filepath{"datasets/farend_speech_fileid_0.wav"};
    const std::string nearend_out_filepath{"datasets/nearend_mic_fileid_0.wav"};
    const std::string nearend_in_filepath{"datasets/nearend_speech_fileid_0.wav"};



    aec::Aec aec{logger, farend_in_filepath, nearend_in_filepath};
    aec.run();
}

