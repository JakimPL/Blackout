#include "Blackout.hpp"

bool Blackout::loadDictionary(const String &path)
{
	std::fstream file(path);
	bool good = file.good();

	String line;
	while (getline(file, line)) {
		dictionary[line] = pow(random.get(), 1 / configuration.probability - 1);
	}

	file.close();

	return good;
}

void Blackout::loadDictionaryFromParagraph(const Paragraph &paragraph)
{
	for (auto &word : paragraph) {
		if (dictionary[word] == 0) {
			dictionary[word] = pow(random.get(), 1 / configuration.probability - 1);
			std::cout << word << ": " << dictionary[word] << DEFAULT_NEWLINE;
		}
	}
}

void Blackout::loadDictionaryFromText(const Text &text)
{
	for (auto &paragraph : text) {
		loadDictionaryFromParagraph(paragraph);
	}
}

void Blackout::loadDictionaryFromText()
{
	std::cout << sourceText.size() << "\n";
	for (auto &paragraph : sourceText) {
		loadDictionaryFromParagraph(paragraph);
	}
}
