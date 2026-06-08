
#include <cstdint>
#include <memory>

#include "Eigen/Dense"
#include "spdlog/spdlog.h"
#include "sliding_window.hpp"



namespace nlms
{


class Nlms
{
    public:
        explicit Nlms(
            const std::shared_ptr<spdlog::logger>& logger, 
            std::size_t order,
            double step_size,
            double regularization
        );

        void run(const std::vector<double>& input_signal, const std::vector<double>& desired_signal);
        void step(double input_sample, double desired_sample);


    private:
        void reset();
        double calculate_power(const Eigen::VectorXd& signal);


        std::shared_ptr<spdlog::logger> logger_{};
        sliding_window::SlidingWindow<double> input_;
        Eigen::VectorXd weights_;
        double step_size_{};
        double regularization_{};
};


} // namespace nlms


