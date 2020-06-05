#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <math.h>

class Random
{
private:
	std::uniform_real_distribution<double> uniformDistribution;
	std::mt19937 mersenneTwister;
public:
	void initialize();

	double get();
	bool get(double value);
};

#endif
