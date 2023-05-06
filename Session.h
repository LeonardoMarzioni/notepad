/**
* @brief class manages user session and save data into os system registry.
*
* @author Marzioni Leonardo
*
*/

#pragma once

#include <QSettings>
#include <QFont>
#include <string>

#define MAX_DIM 10

class Session
{

	public:
		
		// constructor
		Session(std::string org, std::string appName);

		// destructor
		~Session();

		bool wordWrap(){return _wordWrap;}
		QFont font(){return _font;}
		bool canBeOpaque(){return _canBeOpaque;}
		std::list<QString> recentFiles(){return _recentFiles;}
		void setWordWrap(bool enabled){_wordWrap = enabled;}
		void setFont(QFont font){_font = font;}
		void setOpacity(bool canBeOpaque){_canBeOpaque = canBeOpaque;}
		void addRecentFile(const QString& filePath);

	private:
		QSettings settings;
		bool _wordWrap;
		QFont _font;
		bool _canBeOpaque;
		std::list<QString> _recentFiles;

		void initDefault();
		void read();
		void write();
};