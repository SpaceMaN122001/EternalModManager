#include "ModManager.h"

ModManager::ModManager()
{
	pathToMods_ = SSettings::getPathToAppData() + "Eternal mod manager\\" + "Mods\\";
}

bool ModManager::getStatusWhetherModIsAvailableForInstallation(QString modName)
{
	QDir dir(pathToMods_ + modName + "\\" + modName);
	
	QFileInfoList modList = dir.entryInfoList();

	foreach(QFileInfo mod, modList)
	{

		if (mod.fileName() == "EMM") {

			return true;
		}
	}

	return false;
}

QString ModManager::getModDescription(QString modName)
{
	QFile file(pathToMods_ + modName + "\\" + modName + "\\" + "EMM" + "\\" + "Plugin.xml");

	if (!file.open(QFile::ReadOnly | QFile::Text)) {

		qDebug() << "Cannot read file" << file.errorString();

		exit(0);
	}

	QXmlStreamReader reader(&file);

	if (reader.readNextStartElement()) {

		if (reader.name() == "plugin") {

			while (reader.readNextStartElement()) {

				if (reader.name() == "description") {

					QString value = reader.readElementText();

					file.close();
					return value;
				}
				else
					reader.skipCurrentElement();
			}
		}
		else
			reader.raiseError(QObject::tr("Incorrect file"));
	}

	file.close();

	return SNULL;
}

QString ModManager::getModVersion(QString modName)
{
	QFile file(pathToMods_ + modName + "\\" + modName + "\\" + "EMM" + "\\" + "Plugin.xml");

	if (!file.open(QFile::ReadOnly | QFile::Text)) {

		qDebug() << "Cannot read file" << file.errorString();

		exit(0);
	}

	QXmlStreamReader reader(&file);

	if (reader.readNextStartElement()) {

		if (reader.name() == "plugin") {

			foreach(const QXmlStreamAttribute &attr, reader.attributes())
			{

				if (attr.name().toString() == "version") {

					QString version = attr.value().toString();

					file.close();

					return version;

				}
			}
		}
		else
			reader.raiseError(QObject::tr("Incorrect file"));
	}

	file.close();

	return SNULL;
}

QString ModManager::getModImagePath(QString modName)
{
	QFile file(pathToMods_ + modName + "\\" + modName + "\\" + "EMM" + "\\" + "Plugin.xml");

	if (!file.open(QFile::ReadOnly | QFile::Text)) {

		qDebug() << "Cannot read file" << file.errorString();

		exit(0);
	}

	QXmlStreamReader reader(&file);

	if (reader.readNextStartElement()) {

		if (reader.name() == "plugin") {

			foreach(const QXmlStreamAttribute &attr, reader.attributes())
			{

				if (attr.name().toString() == "image") {

					QString pathToImage = attr.value().toString();

					file.close();

					pathToImage = pathToMods_ + modName + "\\" + modName + "\\" + "EMM" + "\\" + pathToImage;

					QFile file(pathToImage);
					if(!file.exists()) return ":/EternalModManager/Resources/none.png";

					return pathToImage;

				}
			}
		}
		else
			reader.raiseError(QObject::tr("Incorrect file"));
	}

	file.close();

	return ":/EternalModManager/Resources/none.png";
}


ModManager::~ModManager()
{
}
