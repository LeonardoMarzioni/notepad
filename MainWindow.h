/**
* @brief class manages main window events.
*
* @author Marzioni Leonardo
*
*/

#pragma once

#include <QWidget.h>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QTabWidget>
#include <QSpinBox>
#include <QLabel>

#include "Document.h"
#include "Session.h"

class MainWindow : public QWidget
{

	Q_OBJECT

	public:

		// constructor
		MainWindow();
		Document* currentDocument() {
			return dynamic_cast<Document*>(_tabs->currentWidget());
		}

		// override
		void closeEvent(QCloseEvent* evt);
		void leaveEvent(QEvent* evt);
		void enterEvent(QEvent* evt);

	public slots:

		void saveActionTriggered();
		void openActionTriggered();
		void alignLeftToggled(bool);
		void alignRightToggled(bool);
		void alignCenterToggled(bool);
		void alignJustifyToggled(bool);
		void newActionTriggered();
		void highlighterActionTriggered();
		void colorActionTriggered();
		void fontActionTriggered();
		void wordWrapToggled(bool);
		void opacityToggled(bool);
		void undoActionTriggered();
		void redoActionTriggered();
		void printActionTriggered();
		void aboutActionTriggered();
		void aboutQtActionTriggered();
		void documentChanged();
		void tabCloseClicked(int);
		void tabChanged(int);
		void textChanged();

		void showCursorPos();

	private:
		QMenuBar* _menuBar;
			QMenu* _fileMenu;
				QAction* _newAction;
				QAction* _openAction;
				QMenu* _openRecentMenu;
				QAction* _saveAction;
				QAction* _saveAsAction;
				QAction* _printAction;
				QAction* _exitAction;
			QMenu* _editMenu;
				QAction* _undoAction;
				QAction* _redoAction;
			QMenu* _formatMenu;
				QAction* _wordWrapAction;
				QAction* _alignLeftAction;
				QAction* _alignRightAction;
				QAction* _alignCenterAction;
				QAction* _alignJustifyAction;
				QAction* _fontAction;
				QAction* _colorAction;
				QAction* _highlighterAction;
				QSpinBox* _fontSizeSpinAction;
			QMenu* _viewMenu;
				QAction* _opaqueAction;
			QMenu* _aboutMenu;
				QAction* _aboutQtAction;
				QAction* _aboutAction;

		QToolBar* _toolBar;
		//azioni condivise con quelle del men�

		QTabWidget* _tabs;

		QStatusBar* _statuBar;
	
		Session _session;

		QLabel* _coordinatesLabel;

		void initDocument();
		void updateRecentFiles();
};