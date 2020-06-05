#ifndef BLACKOUT_HPP
#define BLACKOUT_HPP

#include <string>
#include <fstream>
#include <ostream>
#include <iostream>
#include <vector>
#include <map>

#include "Random.hpp"

typedef std::pair<unsigned long, unsigned long> Pair;
typedef std::string String;
typedef std::vector<String> Paragraph;
typedef std::vector<Paragraph> Text;
typedef std::map<String, double> Dictionary;

#define DEFAULT_PROBABILITY 0.75f
#define DEFAULT_SEPARATOR ' '
#define DEFAULT_NEWLINE "\n"
#define DEFAULT_BLACKSYMBOL "\u2588"

class Blackout
{
private:
	Random random;

	struct Configuration {
		double probability = DEFAULT_PROBABILITY;
		char separator = DEFAULT_SEPARATOR;
		String newLine = DEFAULT_NEWLINE;
		String blackSymbol = DEFAULT_BLACKSYMBOL;
	} configuration;

	struct Statistics {
		void add(bool blackedOut = false);
		Pair getStatistics();
		void resetStatistics();
	private:
		unsigned long words;
		unsigned long blackedOutWords;
	} statistics;

	Dictionary dictionary;
	Text actualText;
	Text sourceText;

	/* text */
	bool exportText(const std::string &path);
	bool importText(const std::string &path);

public:
	Blackout(const std::string &path);
	Blackout();

	void blackout();

	/* configuration */
	void changeSeparator(char newSeparator);
	void setProbability(double newProbability);

	void setConfiguration(Configuration config);
	void setConfiguration(char sep = DEFAULT_SEPARATOR, double p = DEFAULT_PROBABILITY);

	/* dictionary */
	bool loadDictionary(const String &path);
	void loadDictionaryFromParagraph(const Paragraph &paragraph);
	void loadDictionaryFromText(const Text &text);
	void loadDictionaryFromText();

	/* statistics */
	Pair getStatistics();

	/* text */
	String getText(bool original = false);
	bool loadText(const String &path);
	bool saveText(const String &path);
};

#endif
