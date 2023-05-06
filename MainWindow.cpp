#include <QVBoxLayout>
#include <QMessageBox.h>
#include <QFontDialog.h>
#include <QColorDialog>
#include <QFileDialog>
#include <QApplication>

#include "MainWindow.h"
#include <QtPrintSupport/qprinter.h>
#include <QtPrintSupport/qprintdialog.h>
#include <iostream>

MainWindow::MainWindow() : QWidget(0), _session("MyOrg", "MyPad")
{
	// menu bar
	_menuBar = new QMenuBar();
	_fileMenu = new QMenu("File");

	_newAction = new QAction(QIcon(":/icons/new.png"), "New", _fileMenu);
	_newAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
	_fileMenu->addAction(_newAction);

	_openAction = new QAction(QIcon(":/icons/open.png"), "Open", _fileMenu);
	_openAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
	_fileMenu->addAction(_openAction);

	_openRecentMenu = new QMenu("Open Recent");
	_fileMenu->addMenu(_openRecentMenu);

	_saveAction = new QAction(QIcon(":/icons/save.png"), "Save", _fileMenu);
	_saveAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
	_saveAction->setEnabled(false);
	_fileMenu->addAction(_saveAction);

	_saveAsAction = new QAction("Save As", _fileMenu);
	_saveAsAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_S));
	_fileMenu->addAction(_saveAsAction);

	_fileMenu->addSeparator();

	_printAction = new QAction(QIcon(":/icons/printer.png"), "Print", _fileMenu);
	_printAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_P));
	_fileMenu->addAction(_printAction);

	_fileMenu->addSeparator();

	_exitAction = new QAction("Exit", _fileMenu);
	_exitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
	_fileMenu->addAction(_exitAction);

	_editMenu = new QMenu("Edit");

	_undoAction = new QAction(QIcon(":/icons/undo.png"), "Undo", _editMenu);
	_undoAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
	_undoAction->setEnabled(false);
	_editMenu->addAction(_undoAction);

	_redoAction = new QAction(QIcon(":/icons/redo.png"), "Redo", _editMenu);
	_redoAction->setShortcut(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_Z));
	_redoAction->setEnabled(false);
	_editMenu->addAction(_redoAction);

	_formatMenu = new QMenu("Format");

	_wordWrapAction = new QAction(QIcon(":/icons/word-wrap.png"), "Word Wrap", _formatMenu);
	_wordWrapAction->setCheckable(true);
	_wordWrapAction->setChecked(_session.wordWrap());
	_formatMenu->addAction(_wordWrapAction);

	_alignLeftAction = new QAction(QIcon(":/icons/left-align.png"), "Align Left", _formatMenu);
	_alignLeftAction->setShortcut(Qt::CTRL + Qt::Key_T);
	_alignLeftAction->setCheckable(true);
	_alignLeftAction->setChecked(true);
	_formatMenu->addAction(_alignLeftAction);

	_alignRightAction = new QAction(QIcon(":/icons/right-align.png"),  "Align Right", _formatMenu);
	_alignRightAction->setShortcut(Qt::CTRL + Qt::Key_A);
	_alignRightAction->setCheckable(true);
	_formatMenu->addAction(_alignRightAction);

	_alignCenterAction = new QAction(QIcon(":/icons/center-align.png"), "Align Center", _formatMenu);
	_alignCenterAction->setShortcut(Qt::CTRL + Qt::Key_R);
	_alignCenterAction->setCheckable(true);
	_formatMenu->addAction(_alignCenterAction);

	_alignJustifyAction = new QAction(QIcon(":/icons/justification-align.png"), "Justify Text", _formatMenu);
	_alignJustifyAction->setShortcut(Qt::CTRL + Qt::Key_F);
	_alignJustifyAction->setCheckable(true);
	_formatMenu->addAction(_alignJustifyAction);


	_fontAction = new QAction(QIcon(":/icons/font.png"), "Font", _formatMenu);
	_formatMenu->addAction(_fontAction);

	_colorAction = new QAction(QIcon(":/icons/letter-color.png"), "Color", _formatMenu);
	_formatMenu->addAction(_colorAction);

	_highlighterAction = new QAction(QIcon(":/icons/highlighter.png"), "Highlighter", _formatMenu);
	_formatMenu->addAction(_highlighterAction);


	_viewMenu = new QMenu("View");

	_opaqueAction = new QAction(QIcon(":/icons/eye.png"), "Opaque", _viewMenu);
	_opaqueAction->setCheckable(true);
	_opaqueAction->setChecked(_session.canBeOpaque());
	_viewMenu->addAction(_opaqueAction);

	_aboutMenu = new QMenu("About");

	_aboutQtAction = new QAction("About Qt", _aboutMenu);
	_aboutMenu->addAction(_aboutQtAction);

	_aboutAction = new QAction(QIcon(":/icons/about.png"), "About MyPad", _aboutMenu);
	_aboutMenu->addAction(_aboutAction);
	
	_menuBar->addMenu(_fileMenu);
	_menuBar->addMenu(_editMenu);
	_menuBar->addMenu(_formatMenu);
	_menuBar->addMenu(_viewMenu);
	_menuBar->addMenu(_aboutMenu);

	_toolBar = new QToolBar();
	_toolBar->addAction(_newAction);
	_toolBar->addAction(_openAction);
	_toolBar->addAction(_saveAction);
	_toolBar->addAction(_printAction);
	_toolBar->addSeparator();
	_toolBar->addAction(_undoAction);
	_toolBar->addAction(_redoAction);
	_toolBar->addSeparator();
	_toolBar->addAction(_fontAction);
	_toolBar->addAction(_colorAction);
	_toolBar->addAction(_highlighterAction);
	_toolBar->addSeparator();
	_toolBar->addAction(_wordWrapAction);
	_toolBar->addSeparator();
	_toolBar->addAction(_alignLeftAction);
	_toolBar->addAction(_alignCenterAction);
	_toolBar->addAction(_alignRightAction);
	_toolBar->addAction(_alignJustifyAction);
	_toolBar->addSeparator();
	_toolBar->addAction(_opaqueAction);
	_toolBar->addSeparator();
	_toolBar->addAction(_aboutAction);

	// deocuments tab
	_tabs = new QTabWidget();
	_tabs->setTabsClosable(true);

	// status bar
	_statuBar = new QStatusBar();;
	_statuBar->addWidget(new QLabel(QString("MyPad")));

	QVBoxLayout* layout = new QVBoxLayout();
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(0);

	layout->addWidget(_menuBar);
	layout->addWidget(_toolBar);
	layout->addWidget(_tabs);
	layout->addWidget(_statuBar);

	this->setLayout(layout);

	setMinimumSize(640, 480);
	setWindowIcon(QIcon(":/icons/notepad"));

	// uncomment this if you want the app to start in full screen
	//setWindowState(Qt::WindowMaximized);

	// connect signal an slot in the window
	connect(_aboutAction, SIGNAL(triggered()), this, SLOT(aboutActionTriggered()));
	connect(_aboutQtAction, SIGNAL(triggered()), this, SLOT(aboutQtActionTriggered()));
	connect(_printAction, SIGNAL(triggered()), this, SLOT(printActionTriggered()));
	connect(_undoAction, SIGNAL(triggered()), this, SLOT(undoActionTriggered()));
	connect(_redoAction, SIGNAL(triggered()), this, SLOT(redoActionTriggered()));
	connect(_fontAction, SIGNAL(triggered()), this, SLOT(fontActionTriggered()));
	connect(_colorAction, SIGNAL(triggered()), this, SLOT(colorActionTriggered()));
	connect(_highlighterAction, SIGNAL(triggered()), this, SLOT(highlighterActionTriggered()));
	connect(_wordWrapAction, SIGNAL(toggled(bool)), this, SLOT(wordWrapToggled(bool)));
	connect(_opaqueAction, SIGNAL(toggled(bool)), this, SLOT(opacityToggled(bool)));
	connect(_newAction, SIGNAL(triggered()), this, SLOT(newActionTriggered()));
	connect(_tabs, SIGNAL(tabCloseRequested(int)), this, SLOT(tabCloseClicked(int)));
	connect(_tabs, SIGNAL(currentChanged(int)), this, SLOT(tabChanged(int)));
	connect(_openAction, SIGNAL(triggered()), this, SLOT(openActionTriggered()));
	connect(_saveAction, SIGNAL(triggered()), this, SLOT(saveActionTriggered()));
	connect(_saveAsAction, SIGNAL(triggered()), this, SLOT(saveActionTriggered()));
	connect(_exitAction, SIGNAL(triggered()), QApplication::instance(), SLOT(quit()));
	connect(_alignLeftAction, SIGNAL(toggled(bool)), this, SLOT(alignLeftToggled(bool)));
	connect(_alignRightAction, SIGNAL(toggled(bool)), this, SLOT(alignRightToggled(bool)));
	connect(_alignCenterAction, SIGNAL(toggled(bool)), this, SLOT(alignCenterToggled(bool)));
	connect(_alignJustifyAction, SIGNAL(toggled(bool)), this, SLOT(alignJustifyToggled(bool)));

	updateRecentFiles();
}

void MainWindow::aboutActionTriggered()
{
	QMessageBox::about(this, "About MyPad", "<html> <h3>About MyPad</h3> <br> <p> <b>Version 1.0.0</b> <br> Developed by <b>Marzioni Leonardo</b> </p> </html>");
}

void MainWindow::aboutQtActionTriggered()
{
	QMessageBox::aboutQt(this);
}

void MainWindow::printActionTriggered()
{
	if (currentDocument())
	{
		QPrinter printer;
		QPrintDialog printDialog(&printer, this);
		if (printDialog.exec() == QDialog::Accepted)
			currentDocument()->print(&printer);
	}
}

void MainWindow::undoActionTriggered()
{
	if (currentDocument()) {
		currentDocument()->undo();

		_undoAction->setEnabled(currentDocument()->document()->isUndoAvailable());
		_redoAction->setEnabled(currentDocument()->document()->isRedoAvailable());
	}
}

void MainWindow::redoActionTriggered()
{
	if (currentDocument()) {
		currentDocument()->redo();

		_undoAction->setEnabled(currentDocument()->document()->isUndoAvailable());
		_redoAction->setEnabled(currentDocument()->document()->isRedoAvailable());
	}

}

void MainWindow::wordWrapToggled(bool checked)
{
	_session.setWordWrap(checked);
	for (int i = 0; i < _tabs->count(); i++)
	{
		dynamic_cast<Document*>(_tabs->widget(i))->setWordWrapMode(checked ? QTextOption::WordWrap : QTextOption::NoWrap);
	}
}

void MainWindow::opacityToggled(bool checked)
{
	_session.setOpacity(checked);
}

void MainWindow::fontActionTriggered()
{
	if(!currentDocument())
	{
		return;
	}
	
	bool dialogAccepted;
	QFont font = QFontDialog::getFont(&dialogAccepted, currentDocument()->font());

	if (dialogAccepted)
	{
		currentDocument()->setFontPointSize(font.pointSizeF());
		QTextCursor cursor = currentDocument()->textCursor();
		if (cursor.hasSelection())
		{
			QTextCharFormat format;
			format.setFont(font);
			format.setFontPointSize(font.pointSizeF());
			cursor.insertText(cursor.selectedText(), format);
		}
		_session.setFont(font);
	}


}

void MainWindow::colorActionTriggered()
{
	if (!currentDocument())
	{
		return;
	}

	QColor color = QColorDialog::getColor(currentDocument()->textColor(), this);

	if (color.isValid())
	{
		currentDocument()->setTextColor(color);
	}
}

void MainWindow::highlighterActionTriggered()
{
	if (!currentDocument())
	{
		return;
	}


	QColor color = QColorDialog::getColor(currentDocument()->textColor(), this);

	if (color.isValid())
	{
		currentDocument()->setTextBackgroundColor(color);
	}
}

void MainWindow::newActionTriggered()
{
	Document* doc = new Document();
	_tabs->addTab(doc, QString("untitled") + QString::number(doc->id()));
	_tabs->setCurrentWidget(doc);
	initDocument();
}

void MainWindow::tabCloseClicked(int index)
{
	Document* doc = dynamic_cast<Document*>(_tabs->widget(index));
	if(!doc->saved())
	{
		QMessageBox::StandardButton choise = QMessageBox::question(this, "Save", QString("Save file \"") + _tabs->tabText(index) + "\"",
			QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		if(choise == QMessageBox::Yes)
		{
			saveActionTriggered();
		}
		else if (choise == QMessageBox::No)
		{
			;
		}
		else
		{
			//non chiudo la tab
			return;
		}
	}
	delete _tabs->widget(index);
}

void MainWindow::tabChanged(int index) {
	showCursorPos();
}

void MainWindow::textChanged()
{
}

void MainWindow::initDocument()
{
	Document* doc = currentDocument();
	if(doc)
	{
		_tabs->setTabIcon(_tabs->indexOf(doc), QIcon(":/icons/save.png"));

		connect(doc, SIGNAL(textChanged()), this, SLOT(documentChanged()));
		connect(doc, SIGNAL(cursorPositionChanged()), this, SLOT(showCursorPos()));

		wordWrapToggled(_wordWrapAction->isChecked());
		doc->setFont(_session.font());
	}
}

void MainWindow::alignLeftToggled(bool)
{
	_alignCenterAction->setChecked(false);
	_alignRightAction->setChecked(false);
	_alignJustifyAction->setChecked(false);

	if (currentDocument())
	{
		//_alignLeftAction->setChecked(true);
		currentDocument()->setAlignment(Qt::AlignLeft);
	}

}

void MainWindow::alignRightToggled(bool)
{
	_alignCenterAction->setChecked(false);
	_alignLeftAction->setChecked(false);
	_alignJustifyAction->setChecked(false);

	if (currentDocument())
	{
		//_alignRightAction->setChecked(true);
		currentDocument()->setAlignment(Qt::AlignRight);
	}
	
}

void MainWindow::alignCenterToggled(bool)
{
	_alignLeftAction->setChecked(false);
	_alignRightAction->setChecked(false);
	_alignJustifyAction->setChecked(false);

	if (currentDocument())
	{
		//_alignCenterAction->setChecked(true);
		currentDocument()->setAlignment(Qt::AlignCenter);
	}

}

void MainWindow::alignJustifyToggled(bool)
{
	_alignCenterAction->setChecked(false);
	_alignRightAction->setChecked(false);
	_alignCenterAction->setChecked(false);

	if (currentDocument())
	{
		//_alignJustifyAction->setChecked(true);
		currentDocument()->setAlignment(Qt::AlignJustify);
	}
	
}


void MainWindow::openActionTriggered()
{
	QString filePath;
	if (QObject::sender() == _openAction)
		filePath = QFileDialog::getOpenFileName(this, "Select File", QString(), "Note (*.note)");
	else
		filePath = dynamic_cast<QAction*>(QObject::sender())->text();

	if(!filePath.isEmpty())
	{
		//evito di aprire due volte lo stesso file e seleziona se gi� aperto
		int docIndex = -1;
		for(int i = 0; i < _tabs->count(); i++)
		{
			if (dynamic_cast<Document*>(_tabs->widget(i))->filePath() == filePath)
			{
				docIndex = i;
				break;
			}
		}

		if (docIndex >= 0)
			_tabs->setCurrentIndex(docIndex);
		else
		{
			Document* doc = new Document(filePath);
			_tabs->addTab(doc, doc->fileName());
			_tabs->setCurrentWidget(doc);
			initDocument();
			_session.addRecentFile(filePath);
			updateRecentFiles();
			showCursorPos();
		}
	}
}

void MainWindow::saveActionTriggered()
{
	if(!currentDocument())
	{
		return;
	}

	if(currentDocument()->filePath().isEmpty() || QObject::sender() == _saveAsAction)
	{
		QString filePath = QFileDialog::getSaveFileName(this, "Save File", QString(), "Note (*.note)");
		if (!filePath.isEmpty())
		{
			currentDocument()->setFilePath(filePath);
			_tabs->setTabText(_tabs->indexOf(currentDocument()), currentDocument()->fileName());
			currentDocument()->save();
			_session.addRecentFile(filePath);
			updateRecentFiles();
		}
	}
	else
	{
		currentDocument()->save();
	}

	if (currentDocument()->saved())
	{
		_tabs->setTabIcon(_tabs->indexOf(currentDocument()), QIcon(":/icons/save.png"));
		_saveAction->setEnabled(false);
	}
}

void MainWindow::documentChanged()
{
	//uso l' introspezione e chiedo chi ha mandato il segnale
	Document* docSender = dynamic_cast<Document*>(QObject::sender());
	if (docSender)
	{
		docSender->setSaved(false);
		_tabs->setTabIcon(_tabs->indexOf(docSender), QIcon(":/icons/unsaved.png"));
		_saveAction->setEnabled(true);
		_undoAction->setEnabled(true);
		_redoAction->setEnabled(true);
	}
}

void MainWindow::updateRecentFiles()
{
	_openRecentMenu->clear();
	for(auto & f : _session.recentFiles())
	{
		QAction* act = new QAction(f, _openRecentMenu);
		_openRecentMenu->addAction(act);
		connect(act, SIGNAL(triggered()), this, SLOT(openActionTriggered()));
	}
}


void MainWindow::closeEvent(QCloseEvent* evt)
{
	while(_tabs->currentIndex() >= 0)
	{
		Document* docBefore = currentDocument();
		tabCloseClicked(_tabs->currentIndex());
		Document* docAfter = currentDocument();

		//se � lo stesso non l ha chiuso e non chiudo l'app
		if (docAfter == docBefore)
		{
			evt->ignore();
			break;
		}

	}
}

void MainWindow::leaveEvent(QEvent* evt)
{
	if(_session.canBeOpaque())
		setWindowOpacity(0.3);
}

void MainWindow::enterEvent(QEvent* evt) 
{
	if (_session.canBeOpaque())
		setWindowOpacity(1);
}

void MainWindow::showCursorPos()
{
	if (currentDocument())
	{
		QString coordinates_str = QString("ri: %1 col: %2 \t par: %3 \t word: %4").arg(currentDocument()->textCursor().blockNumber() + 1).arg(currentDocument()->textCursor().columnNumber()).arg(currentDocument()->textCursor().blockNumber() + 1).arg(currentDocument()->toPlainText().split(QRegExp("(\\s|\\n|\\r)+"), QString::SkipEmptyParts).count());
		if (_coordinatesLabel)
		{
			_statuBar->removeWidget(_coordinatesLabel);
		}
		_coordinatesLabel = new QLabel(coordinates_str);
		_statuBar->addPermanentWidget(_coordinatesLabel);
	}
}