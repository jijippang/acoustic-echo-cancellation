
#include <cstdint>





class Nlms
{
    public:
        Nlms() = default;


        void step(double input_sample);

    private:
        double error{};
        double step_size{};
};




