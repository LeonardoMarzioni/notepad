#include <fstream>
#include <QFileInfo>
#include <QMenu>

#include "Document.h"
#include "Corrector.h"
#include <iostream>

std::set<int> Document::_available_ids = std::set<int>();

Document::Document()
{
	if(_available_ids.empty())
	{
		for (int i = 1; i < MAX_NUM_FILES; i++)
		{
			_available_ids.insert(i);
		}
	}

	_id = *(_available_ids.begin());
	_available_ids.erase(_available_ids.begin());
	_saved = true;
}

Document::Document(QString filePath)
{
	_id = 0;
	_filePath = filePath;
	std::ifstream f(filePath.toStdString());
	if (!f.is_open())
	{
		// error exeption
	}

	std::string text;
	std::string line;
	while(std::getline(f, line))
	{
		text += line + "\n";
	}
	f.close();

	setText(text.c_str());

	QFileInfo info(filePath);
	_fileName = info.fileName();
	_saved = true;
}

Document::~Document()
{
	if(_id)
		_available_ids.insert(_id);
}

void Document::setFilePath(QString filePath)
{
	_filePath = filePath;
	QFileInfo info(filePath);
	_fileName = info.fileName();
}

void Document::save()
{
	std::ofstream f(_filePath.toStdString());
	if (!f.is_open())
	{
		return;
	}
	f << toHtml().toStdString();
	f.close();

	_saved = true;
}

void Document::contextMenuEvent(QContextMenuEvent* event)
{
	QMenu* menu = createStandardContextMenu(event->pos());
	menu->exec(event->globalPos());
	delete menu;
}

QMenu* Document::createStandardContextMenu(const QPoint& position)
{
	QMenu* stdMenu = QTextEdit::createStandardContextMenu();
	
	_lastContextMenuPos = position;

	QTextCursor tc = cursorForPosition(position);
	tc.select(QTextCursor::WordUnderCursor);
	QString word = tc.selectedText();
	tc.clearSelection();

	std::string wordStd = word.toLower().toStdString();

	if (Corrector::instance()->isCorrect(wordStd))
		return stdMenu;

	auto suggestions = Corrector::instance()->suggest(wordStd);
	stdMenu->insertSeparator(stdMenu->actions().first());
	for (auto& sug : suggestions)
	{
		//printf("sug: %s", sug.c_str());
		QAction* suggAction = new QAction(sug.c_str(), stdMenu);
		suggAction->setFont(QFont(suggAction->font().family(), suggAction->font().pointSize()));
		stdMenu->insertAction(stdMenu->actions().first(), suggAction);

		connect(suggAction, SIGNAL(triggered()), this, SLOT(suggestedWordClicked()));
	}

	return stdMenu;
}

void Document::suggestedWordClicked()
{
	QAction* suggAction = dynamic_cast<QAction*>(QObject::sender());

	if (suggAction)
	{
		QTextCursor tc = cursorForPosition(_lastContextMenuPos);
		tc.select(QTextCursor::WordUnderCursor);
		tc.deleteChar();
		tc.insertText(suggAction->text());
		tc.clearSelection();
	}

}

void Document::undoAvailable(bool available)
{
	_isUndoAvailable = available;
}

void Document::redoAvailable(bool available)
{
	_isRedoAvailable = available;
}

void Document::wheelEvent(QWheelEvent* e) {
	if (e->modifiers() == Qt::CTRL)
	{
		if (e->delta() > 0)
			this->zoomIn();
		else
			this->zoomOut();
	}
	else
	{
		QTextEdit::wheelEvent(e);
	}

}