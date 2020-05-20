#include "SSettings.h"

SSettings::SSettings(QString folderName)
{
	folderName_ = folderName;

	QDir dir(SSettings::getPathToAppData());
	dir.mkdir(folderName_);
}


SSettings::~SSettings()
{
}

QString SSettings::getPathToAppData()
{
	QString userName = QDir::home().dirName();

	QString pathToAppData = "C:\\Users\\" + userName + "\\" + "AppData\\Local\\";

	return pathToAppData;
}

void SSettings::setValue(QString keyName, int value)
{
	QFile file(SSettings::getPathToAppData() + folderName_ + "\\" + keyName + ".txt");

	if (file.exists()) return;

	if (!file.exists()) {

		file.open(QIODevice::WriteOnly);
		file.close();

		if (file.open(QIODevice::WriteOnly)) {

			file.write(QString::number(value).toUtf8());

			file.close();
		}
	}
}

void SSettings::setValue(QString keyName, QString value)
{
	QFile file(SSettings::getPathToAppData() + folderName_ + "\\" + keyName + ".txt");

	if (file.exists()) return;

	if (!file.exists()) {

		file.open(QIODevice::WriteOnly);
		file.close();

		if (file.open(QIODevice::WriteOnly)) {

			file.write(value.toUtf8());

			file.close();
		}
	}
}

int SSettings::getValue(QString keyName)
{
	QFile file(SSettings::getPathToAppData() + folderName_ + "\\" + keyName + ".txt");

	QString sValue = "";

	if ((file.exists()) && (file.open(QIODevice::ReadOnly))) {
		
		while (!file.atEnd()) {

			sValue = file.readLine();
		}

		file.close();
	}

	return sValue.toInt();
}

void SSettings::changeValue(QString keyName, int value)
{
	QFile file(SSettings::getPathToAppData() + folderName_ + "\\" + keyName + ".txt");

	file.open(QIODevice::WriteOnly);
	file.close();

	if (file.open(QIODevice::WriteOnly)) {

		file.write(QString::number(value).toUtf8());

		file.close();
	}
}

void SSettings::changeValue(QString keyName, QString value)
{
	QFile file(SSettings::getPathToAppData() + folderName_ + "\\" + keyName + ".txt");

	file.open(QIODevice::WriteOnly);
	file.close();

	if (file.open(QIODevice::WriteOnly)) {

		file.write(value.toUtf8());

		file.close();
	}
}

bool SSettings::isExist(QString keyName)
{
	keyName += ".txt";

	QDir dir(SSettings::getPathToAppData() + folderName_);

	QFileInfoList fileList = dir.entryInfoList();

	foreach(QFileInfo file, fileList)
	{
		QString fileName = file.fileName();

		if (fileName == keyName) {

			return true;
		}
	}

	return false;
}

int SSettings::getKeyValue(QString programName, QString keyName)
{
	QDir dir(SSettings::getPathToAppData() + programName);

	if (!dir.exists()) return -1;

	QFile file(SSettings::getPathToAppData() + programName + "\\" + keyName + ".txt");

	if (!file.exists()) return -1;

	QString sValue = "";

	if ((file.exists()) && (file.open(QIODevice::ReadOnly))) {

		while (!file.atEnd()) {

			sValue = file.readLine();
		}

		file.close();
	}

	if (sValue == nullptr) return NULL;

	return sValue.toInt();
}

bool SSettings::isExistKey(QString programName, QString keyName)
{
	keyName = keyName + ".txt";

	QDir dir(SSettings::getPathToAppData() + programName);

	if (!dir.exists()) return false;

	QFileInfoList fileList = dir.entryInfoList();

	foreach(QFileInfo file, fileList)
	{
		QString fileName = file.fileName();

		if (fileName == keyName) {

			return true;
		}
	}

	return false;
}

void SSettings::setKeyValue(QString programName, QString keyName, QString value)
{
	QFile file(SSettings::getPathToAppData() + programName + "\\" + keyName + ".txt");

	if (file.exists()) return;

	if (!file.exists()) {

		file.open(QIODevice::WriteOnly);
		file.close();

		if (file.open(QIODevice::WriteOnly)) {

			file.write(value.toUtf8());

			file.close();
		}
	}
}

QString SSettings::getKeyValueS(QString programName, QString keyName)
{
	QDir dir(SSettings::getPathToAppData() + programName);

	if (!dir.exists()) return -1;

	QFile file(SSettings::getPathToAppData() + programName + "\\" + keyName + ".txt");

	if (!file.exists()) return -1;

	QString sValue = "";

	if ((file.exists()) && (file.open(QIODevice::ReadOnly))) {

		while (!file.atEnd()) {

			sValue = file.readLine();
		}

		file.close();
	}

	if (sValue == nullptr) return NULL;

	return sValue;
}