#include <QFile>
#include <QTextStream>

#include "Corrector.h"

Corrector* Corrector::instance()
{
	static Corrector uniqueInstance;
	return &uniqueInstance;
}

Corrector::Corrector()
{
	QFile f(":/dictionaries/ita.txt");
	if (!f.open(QFile::ReadOnly))
		throw("Cannot Open Dictionary");
	QTextStream in(&f);
	while (!in.atEnd())
	{
		QString line = in.readLine();
		dictionary.insert(line.toStdString());
	}
	f.close();
}

int Corrector::distance(std::string X, std::string Y)
{
	int m = X.size();
	int n = Y.size();
	//allocation of distance matrix
	int** D = new int* [m + 1];
	for(int i = 0; i < m + 1; i++)
	{
		D[i] = new int [n + 1];
	}

	//initialization
	for (int i = 0; i < m + 1; i++)
		D[i][0] = i;

	for (int j = 0; j < n + 1; j++)
		D[0][j] = j;

	//dynamic programming
	for (int i = 1; i < m + 1; i++)
	{
		for (int j = 1; j < n + 1; j++)
		{
			if (X[i] != Y[j])
				D[i][j] = 1 +std::min({ D[i][j - 1], D[i - 1][j], D[i - 1][j - 1] });
			else
				D[i][j] = D[i - 1][j - 1];
		}
	}
	return D[m][n];
}

std::list<std::string> Corrector::suggest(std::string word, int n)
{
	std::list<std::string> suggestions;
	int minDist = std::numeric_limits<int>::max();
	std::string closestWord;
	for (auto& w : dictionary)
	{
		if (w[0] != word[0])
			continue;

		int d = distance(w, word.c_str());
		if(d < minDist)
		{
			minDist = d;
			closestWord = w;
		}
	}
	suggestions.push_front(closestWord);
	return suggestions;
}