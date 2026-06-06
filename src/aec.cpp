
#include <print>

#include "aec.hpp"






namespace aec
{


    Aec::Aec(
        const std::shared_ptr<spdlog::logger>& logger, 
        const fs::path& farend_in_filepath, 
        const fs::path& nearend_in_filepath
    ) : logger_{logger}
    {
        // Initialize the internal AudioFiles
        init_audiofile(farend_in_audiofile_, farend_in_filepath);
        init_audiofile(nearend_in_audiofile_, nearend_in_filepath);
    }

    void Aec::run()
    {
        logger_->info("Running AEC algorithm");

    }


    void Aec::init_audiofile(AudioFile<double>& audiofile, const fs::path& filepath)
    {
        if (audiofile.load(filepath))
        {
            logger_->info("Loaded audio file: {}", filepath.filename().string());
            logger_->debug(
                "\n"
                "File Name: {}\n"
                "Sample Rate [Hz]: {}\n"
                "BitDepth: {}\n"
                "Num Channels: {}\n"
                "Num Samples per Channel: {}",
                filepath.filename().string(),
                audiofile.getSampleRate(),
                audiofile.getBitDepth(),
                audiofile.getNumChannels(),
                audiofile.getNumSamplesPerChannel()
            );
        }
        else
        {
            logger_->critical("Error reading file: {}", filepath.string());
        }
    }





} // namespace aec



