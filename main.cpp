#include "src/Blackout.hpp"

#include "boost/program_options.hpp"
namespace bpo = boost::program_options;

#define PRINT(string) std::cout << string << DEFAULT_NEWLINE
#define HELP "An easy program for BLACKOUT poetry. Usage:\n./Blackout [input] [output]\nOutput is optional. Example:\n./Blackout lorem.txt lorem_output.txt --probability 0.8\n\nOptions"
#define VERSION "0.0.2"

int main(int argc, char *argv[])
{
	bpo::options_description description(HELP);
	description.add_options()

	("help,h",                              "Shows the help message")
	("version,v",                           "Shows the version of the program")
	("show-input,s",                        "Shows the input file")
	("dictionary,d",  bpo::value<String>(), "A path to the dictionary file")
	("input,i",       bpo::value<String>(), "A path to the input file")
	("output,o",      bpo::value<String>(), "A path to the output file")
	("probability,p", bpo::value<double>(), "The probability of a BLACKOUT of words");

	bpo::variables_map variablesMap;
	bpo::positional_options_description positionalOptionsDescription;
	positionalOptionsDescription.add("input", 1);
	positionalOptionsDescription.add("output", 1);

	try {
		bpo::store(bpo::command_line_parser(argc, argv).options(description).positional(positionalOptionsDescription).run(), variablesMap);
		bpo::notify(variablesMap);
	} catch (std::exception &exception) {
		PRINT("Command option error: " << exception.what());
		return -2;
	} catch (...) {
		PRINT("Unknown error");
		return -2;
	}

	bool exit = false;
	if (variablesMap.count("help")) {
		PRINT(description);
		exit = true;
	}

	if (variablesMap.count("version")) {
		PRINT("Version: " << VERSION);
		exit = true;
	}

	if (exit) {
		return 1;
	}

	bool showInput = variablesMap.count("show-input");
	std::string inputPath, outputPath, dictionaryPath;
	Blackout blackout;

	if (variablesMap.count("input")) {
		inputPath = variablesMap["input"].as<String>();
		if (!blackout.loadText(inputPath)) {
			PRINT("Failed to load the input file!");
			return -1;
		}

		double probability = DEFAULT_PROBABILITY;
		char separator = DEFAULT_SEPARATOR;
		if (variablesMap.count("probability")) {
			probability = variablesMap["probability"].as<double>();
		}

		blackout.setConfiguration(separator, probability);

		blackout.loadDictionaryFromText();
		if (variablesMap.count("dictionary")) {
			dictionaryPath = variablesMap["dictionary"].as<String>();
			if (!dictionaryPath.empty() and !blackout.loadDictionary(dictionaryPath)) {
				PRINT("Failed to load the dictionary!");
			}
		}

		blackout.blackout();

		if (showInput) {
			PRINT(blackout.getText(true));
		}

		PRINT(blackout.getText());
		PRINT("Blackout statistics:" <<
			  DEFAULT_NEWLINE << "Paragraphs: " << blackout.statistics.paragraphs <<
			  DEFAULT_NEWLINE << "Words: " << blackout.statistics.blackedOutWords << " / " << blackout.statistics.words <<
			  " (" << (double)(blackout.statistics.blackedOutWords) / blackout.statistics.words << "%)");

		if (variablesMap.count("output")) {
			outputPath = variablesMap["output"].as<String>();
			if (inputPath == outputPath) {
				PRINT("Output path has to be different than input path!");
			} else if (!outputPath.empty() and !blackout.saveText(outputPath)) {
				PRINT("Failed to save the output!");
			}
		}
	} else {
		PRINT(description << DEFAULT_NEWLINE << "Version: " << VERSION);
		return 1;
	}

	return 0;
}
