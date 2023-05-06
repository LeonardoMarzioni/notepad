/**
* @brief class manages the correction of misspellings during writing.
*
* @author Marzioni Leonardo
*
*/

#pragma once

#include <string>
#include <list>
#include <set>

#define WORD_SUGG 5

class Corrector
{
	public:

		// Singleton design pattern
		static Corrector* instance();

		std::list<std::string> suggest(std::string word, int n = WORD_SUGG);

		bool isCorrect(std::string word) {
			return dictionary.find(word) != dictionary.end();
		}

		// compute the distance between words in dictionary
		// using Levenshtein algorithm.
		// [WORD_SUGG] no. words less distant will be recommended
		// to the user
		static int distance(std::string X, std::string Y);

	private:
		std::set<std::string> dictionary;

		//singleton design pattern
		Corrector();
};