#include <functional>
#include <random>
#include <time.h>   
class Rand_Entero
{
public:
	Rand_Entero(double low, double high)
				:r(
				   std::bind(
							 std::uniform_int_distribution<>(low,high),std::mt19937( ))){}
				
				double operator()(){ return r(); }
				
private:
								  std::function<double()> r;
};
