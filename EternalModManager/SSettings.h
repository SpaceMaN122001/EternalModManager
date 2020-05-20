#pragma once
#include <QWidget>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QDebug>

class SSettings
{
public:
	SSettings(QString folderName);
	~SSettings();
	void setValue(QString keyName, int value);
	void setValue(QString keyName, QString value);
	int getValue(QString keyName);
	void changeValue(QString keyName, int value);
	void changeValue(QString keyName, QString value);
	bool isExist(QString keyName);
	static int getKeyValue(QString programName, QString keyName);
	static QString getKeyValueS(QString programName, QString keyName);
	static bool isExistKey(QString programName, QString keyName);
	static void setKeyValue(QString programName, QString keyName, QString value);
	static QString getPathToAppData();
private:
	QString folderName_;
};

