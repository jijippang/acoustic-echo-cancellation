
#include <cstdint>
#include <memory>
#include <filesystem>

#include "nlms.hpp"
#include "AudioFile.h"
#include "spdlog/spdlog.h"



namespace aec
{


namespace fs = std::filesystem;


class Aec
{
    public:
        Aec(
            const std::shared_ptr<spdlog::logger>& logger, 
            const fs::path& farend_in_filepath, 
            const fs::path& nearend_in_filepath
        );

        void run();

    private:
        void init_audiofile(AudioFile<double>& audiofile, const fs::path& filepath);


        Nlms nlms_{};
        AudioFile<double> farend_in_audiofile_{};
        AudioFile<double> nearend_in_audiofile_{};
        std::shared_ptr<spdlog::logger> logger_{};
};



} // namespace aec


