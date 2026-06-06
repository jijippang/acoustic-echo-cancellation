
#include "nlms.hpp"



namespace nlms
{


    Nlms::Nlms(
        std::size_t order, 
        std::size_t max_iter_cnt 
    ) : max_iter_cnt_{max_iter_cnt},
        weights_(order, 0.0)
    {

    }

    void Nlms::run(const Eigen::VectorXd& input_samples)
    {
        while (iter_cnt_ <= max_iter_cnt_)
        {
            step();
        }
    }

    void Nlms::step(double input_sample)
    {
        iter_cnt_++;

    }

    void Nlms::reset()
    {
        iter_cnt_ = 0;
    }


} // namespace nlms






