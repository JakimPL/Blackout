#include "Blackout.hpp"

Blackout::Blackout()
{
	random.initialize();
}

Blackout::Blackout(const String &path)
{
	Blackout();
	importText(path);
}

void Blackout::blackout()
{
	statistics.resetStatistics();
	for (auto &paragraph : actualText) {
		for (auto &word : paragraph) {
			const double probability = (dictionary[word] == 0 ? configuration.probability : dictionary[word]);
			bool blackedOut = random.get(probability);
			if (blackedOut) {
				size_t size = word.size();
				String blackWord;
				for (size_t symbol = 0; symbol < size; ++symbol) {
					blackWord += configuration.blackSymbol;
				}

				word = blackWord;
			}

			statistics.add(blackedOut);
		}

		if (!paragraph.empty() and !paragraph[0].empty()) {
			statistics.addParagraph();
		}
	}
}

String Blackout::getText(bool original)
{
	String output;
	Text text = (original ? sourceText : actualText);
	size_t paragraphs = text.size();
	for (size_t paragraphId = 0; paragraphId < paragraphs; ++paragraphId) {
		size_t paragraphSize = text[paragraphId].size();
		for (size_t wordId = 0; wordId < paragraphSize; ++wordId) {
			output += text[paragraphId][wordId];
			if (wordId < paragraphSize - 1) {
				output += configuration.separator;
			}
		}

		output += configuration.newLine;
	}

	return output;
}

bool Blackout::exportText(const String &path)
{
	std::ofstream file;

	file.open(path);
	file << getText() << configuration.newLine;
	file.close();

	bool good = file.good();
	return good;
}

bool Blackout::importText(const String &path)
{
	std::fstream file(path);
	bool good = file.good();

	statistics.resetStatistics();
	sourceText.clear();
	actualText.clear();

	String line, word;
	while (getline(file, line)) {
		Paragraph paragraph;
		for (auto x : line + " ") {
			if (x == configuration.separator) {
				paragraph.push_back(word);
				word = "";
			} else {
				word = word + x;
			}
		}

		sourceText.push_back(paragraph);
		actualText.push_back(paragraph);
	}

	file.close();

	return good;
}

bool Blackout::loadText(const String &path)
{
	return importText(path);
}

bool Blackout::saveText(const String &path)
{
	return exportText(path);
}
