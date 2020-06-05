#include "Blackout.hpp"

void Blackout::Statistics::resetStatistics()
{
	blackedOutWords = words = 0;
}

Pair Blackout::Statistics::getStatistics()
{
	return std::make_pair(words, blackedOutWords);
}

void Blackout::Statistics::add(bool blackedOut)
{
	words++;

	if (blackedOut) {
		blackedOutWords++;
	}
}
