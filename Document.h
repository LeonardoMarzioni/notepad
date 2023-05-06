/**
* @brief class manages documents.
*
* @author Marzioni Leonardo
*
*/

#pragma once

#include <QTextEdit>
#include <QContextMenuEvent>
#include <QWidget>
#include <set>

#define MAX_NUM_FILES 250

class Document : public QTextEdit
{
	Q_OBJECT

	public:

		// constructor
		Document();
		Document(QString filePath);

		// destructor
		~Document();

		// getter
		int id() {return _id;}
		bool saved() {return _saved;}
		QString fileName() { return _fileName;}
		QString filePath() { return _filePath; }

		// setter
		void setFilePath(QString filePath);
		void setSaved(bool newSaved){_saved = newSaved;}

		void save();
		
		// @override
		void contextMenuEvent(QContextMenuEvent* event);
		QMenu* createStandardContextMenu(const QPoint& position);
		void wheelEvent(QWheelEvent *e);

	public slots:

		void suggestedWordClicked();
		void undoAvailable(bool available);
		void redoAvailable(bool available);

	private:
		int _id;								// doc id
		static std::set<int> _available_ids;
		QString _fileName;
		QString _filePath;
		bool _saved;							// is doc saved?
		QPoint _lastContextMenuPos;

		bool _isUndoAvailable;
		bool _isRedoAvailable;
};