#include <functional>
#include <random>

class Rand_double
{
public:
	Rand_double(double low, double high)
				:r(std::bind(std::uniform_real_distribution<>(low,high),std::mt19937())){}
				
				double operator()(){ return r(); }
				
private:
								  std::function<double()> r;
};
