#include "Blackout.hpp"

void Blackout::changeSeparator(char newSeparator)
{
	configuration.separator = newSeparator;
}

void Blackout::setProbability(double newProbability)
{
	configuration.probability = newProbability;
}

void Blackout::setConfiguration(Configuration config)
{
	configuration = config;
}

void Blackout::setConfiguration(char sep, double p)
{
	configuration.probability = p;
	configuration.separator = sep;
}
