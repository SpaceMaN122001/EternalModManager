#pragma once
#include <QtWidgets/QMainWindow>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QDirIterator>
#include <QFileDialog>
#include "ui_GameDefinition.h"
#include "SSettings.h"
#include "GameSelection.h"
#include "KeyWords.h"

class GameDefinition : public QWidget
{
	Q_OBJECT
public:
	explicit GameDefinition(QWidget *parent = nullptr);
	~GameDefinition();
private:
	Ui::GameDefinitionForm ui;
	void setCustomButtonStyle(QToolButton& button, QString imagePath, QString toolTip);
	QString getPathToGame(QLabel& line, QString parameter1, QString parameter2, QString parameter3, QString parameter4);
private slots:
	void ScanGame();
	void savePathToGame();
	void selectPathToSkyrimSE();
	void programQuit();
private:
	QString pathToSkyrimSe_;
	QString pathToSkyrimLe_;
	QString pathToF4_;
	SSettings* settings;
};

