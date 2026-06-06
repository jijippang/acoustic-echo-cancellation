
#include <cstdint>
#include <vector>

#include "Eigen/Dense"



namespace nlms
{


class Nlms
{
    public:
        Nlms(
            std::size_t order, 
            std::size_t max_iter_cnt = 100
        );

        void run(const Eigen::VectorXd& input_samples);
        void step(double input_sample);


    private:
        double error_{};
        double step_size_{};
        std::size_t order_{};
        std::size_t iter_cnt_{};
        std::size_t max_iter_cnt_{};
        std::vector<double> weights_;


        void reset();
};


} // namespace nlms


