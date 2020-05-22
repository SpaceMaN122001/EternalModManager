#pragma once
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QFile>
#include <QDir>
#include "SSettings.h"
#include "KeyWords.h"

class ModManager
{
public:
	ModManager();
	~ModManager();
	bool getStatusWhetherModIsAvailableForInstallation(QString modName);
	QString getModDescription(QString modName);
	QString getModVersion(QString modName);
	QString getModImagePath(QString modName);
private:
	QString pathToMods_;
};

