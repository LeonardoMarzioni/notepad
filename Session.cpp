#include "Session.h"

Session::Session(std::string org, std::string appName) : settings(org.c_str(), appName.c_str())
{
	initDefault();
	read();
}

Session::~Session()
{
	write();
}

void Session::initDefault()
{
	_wordWrap = false;
	_canBeOpaque = false;
	_font = QFont("Calibri", 14);
}

void Session::addRecentFile(const QString& filePath)
{
	if (std::find(_recentFiles.begin(), _recentFiles.end(), filePath) != _recentFiles.end())
		_recentFiles.remove(filePath);
	_recentFiles.push_front(filePath);
	if (_recentFiles.size() > 10)
		_recentFiles.pop_back();
}

void Session::read()
{
	if(settings.contains("wordWrap"))
		_wordWrap = settings.value("wordWrap").toBool();

	if (settings.contains("canBeOpaque"))
		_canBeOpaque = settings.value("canBeOpaque").toBool();

	if (settings.contains("fontFamily"))
		_font.setFamily(settings.value("fontFamily").toString());
	if (settings.contains("fontSize"))
		_font.setPointSize(settings.value("fontSize").toInt());
	if (settings.contains("fontWeight"))
		_font.setWeight(settings.value("fontWeight").toInt());
	if (settings.contains("fontItalic"))
		_font.setItalic(settings.value("fontItalic").toBool());

	size_t dim = settings.beginReadArray("recentFiles");

	for (int i = 0; i < dim; i++)
	{
		settings.setArrayIndex(i);
		_recentFiles.push_back(settings.value("path").toString());
	}
	settings.endArray();
}

void Session::write()
{
	settings.setValue("wordWrap", _wordWrap);
	settings.setValue("fontFamily", _font.family());
	settings.setValue("fontSize", _font.pointSize());
	settings.setValue("fontWeight", _font.weight());
	settings.setValue("fontItalic", _font.italic());
	settings.setValue("canBeOpaque", _canBeOpaque);

	settings.beginWriteArray("recentFiles");
	int i = 0;
	for(auto& f : _recentFiles)
	{
		settings.setArrayIndex(i++);
		settings.setValue("path", f);
	}
	settings.endArray();

}