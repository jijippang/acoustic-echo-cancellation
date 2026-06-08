
#include <cstdint>
#include <memory>
#include <filesystem>

#include "AudioFile.h"
#include "spdlog/spdlog.h"
#include "nlms.hpp"



namespace aec
{


namespace fs = std::filesystem;


class Aec
{
    public:
        explicit Aec(
            const std::shared_ptr<spdlog::logger>& logger, 
            const fs::path& farend_in_filepath, 
            const fs::path& nearend_in_filepath
        );

        void run();

    private:
        void init_audiofile(AudioFile<double>& audiofile, const fs::path& filepath);


        std::shared_ptr<spdlog::logger> logger_{};
        nlms::Nlms nlms_{logger_, 9, 0.1, 1e-10};
        AudioFile<double> farend_in_audiofile_{};
        AudioFile<double> nearend_in_audiofile_{};
};



} // namespace aec


