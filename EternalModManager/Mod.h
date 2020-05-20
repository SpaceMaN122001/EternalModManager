#pragma once
#include <QDir>
#include <QFile>
#include <QProcess>
#include <QWidget>
#include <QCoreApplication>
#include <QDirIterator>
#include <QDebug>
#include <QListWidget>
#include <QDate>
#include <QTime>
#include "SSettings.h"
#include "Process.h"
#include "SDir.h"
#include "Plugin.h"
#define DISABLE 0
#define ENABLE 1
#define SLASH "\\"

class Mod
{
public:
	Mod(QListWidget* widget);
	~Mod();
	void addMod(QString pathToMod);
	int getModState(QString modName);
	void showMods();
	void disableMod(QString modName);
	void enableMod(QString modName);
	void removeMod(QString modName);
	bool isExist(QString pathToMod);
	int getTotalNumberOfMods();
	int getNumberOfEnabledMods();
	int getNumberOfDisabledods();
	void setPathToGame(QString pathToGame);
	QString getNameEspFileMod(QString modName);
	static QString getPathToMods();
	void showModFiles(QString modName);
	float getModSize(QString modName);
	int getNumberOfFiles(QString modName);
	QString getAddTime(QString modName);
	QString getDateAdded(QString modName);
private:
	QString pathToMods_;
	QListWidget* modsWidget_;
	QString pathToGame_;
private:
	void unzippingArchive(QString pathToArchive, QString pathToExtract);
	void writeAllModFilesTofile(QString pathToMod, QString modName);
	void writeAllPathsToModFiles(QString pathToMod, QString modName);
	int getItemIndex(QListWidget& widget, QString itemName);
	void copyFileFromData(QString pathToMod);
	QString getNameEspFileModFromData(QString pathToMod);
};

