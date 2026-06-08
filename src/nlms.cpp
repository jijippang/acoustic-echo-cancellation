
#include "nlms.hpp"



namespace nlms
{


    Nlms::Nlms(
        const std::shared_ptr<spdlog::logger>& logger, 
        std::size_t order,
        double step_size,
        double regularization
    ) : logger_{logger},
        input_(order, 0.0),
        weights_(Eigen::VectorXd::Zero(order)),
        step_size_{step_size},
        regularization_{regularization}
    {

    }

    void Nlms::run(const std::vector<double>& input_signal, const std::vector<double>& desired_signal)
    {
        if (input_signal.size() != desired_signal.size())
        {
            throw std::runtime_error("Input signal and desired signal must be the same length");
        }

        for (std::size_t i = 0; i < input_signal.size(); ++i)
        {
            step(input_signal[i], desired_signal[i]);
        }
    }

    void Nlms::step(double input_sample, double desired_sample)
    {
        // Insert the input_sample into the input window
        input_.push(input_sample);

        const auto normalization_factor = step_size_ / (calculate_power(input_.get_eigen_view()) + regularization_);
        const auto output_estimate = weights_.adjoint() * input_.get_eigen_view();
        const auto error = desired_sample - output_estimate;

        logger_->info("NLMS Error: {}", error);

        // Update the weight vector for the next iteration
        weights_ = weights_ + (normalization_factor * error * input_.get_eigen_view());
    }

    void Nlms::reset()
    {
        input_.fill(0.0);
        weights_.setZero();
    }

    double Nlms::calculate_power(const Eigen::VectorXd& signal)
    {
        return signal.adjoint() * signal;
    }


} // namespace nlms






