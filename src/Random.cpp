#include "Random.hpp"

void Random::initialize()
{
	std::random_device randomDevice;
	std::mt19937 twister(randomDevice());
	std::uniform_real_distribution<double> distribution(0, 1);

	mersenneTwister = twister;
	uniformDistribution = distribution;
}

double Random::get()
{
	return uniformDistribution(mersenneTwister);
}

bool Random::get(double value)
{
	return get() < value;
}
