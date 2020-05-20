#include "Mod.h"

Mod::Mod(QListWidget* widget)
{
	QDir dir(SSettings::getPathToAppData() + "Eternal mod manager");
	dir.mkdir("Mods");
	pathToMods_ = SSettings::getPathToAppData() + "Eternal mod manager\\" + "Mods\\";
	modsWidget_ = widget;
	this->showMods();
}

QString Mod::getPathToMods()
{
	return SSettings::getPathToAppData() + "Eternal mod manager\\" + "Mods\\";
}

void Mod::showModFiles(QString modName)
{
	modsWidget_->clear();

	QDirIterator it(pathToMods_ + modName + SLASH + modName, QDirIterator::Subdirectories);

	while (it.hasNext()) {

		QFileInfo info(it.next());

		if (info.suffix() != nullptr && info.fileName() != ".." && info.fileName() != '.') {

			modsWidget_->addItem(new QListWidgetItem(QIcon(":/EternalModManager/Resources/file.png"), info.fileName()));
		}
	}
}

float Mod::getModSize(QString modName)
{
	QDirIterator it(pathToMods_ + modName + SLASH + modName, QDirIterator::Subdirectories);

	float size = NULL;

	while (it.hasNext()) {

		QFileInfo info(it.next());

		if (info.suffix() != nullptr && info.fileName() != ".." && info.fileName() != '.') {

			size += info.size();
		}
	}

	return size / 1024 / 1024;
}

int Mod::getNumberOfFiles(QString modName)
{
	QDirIterator it(pathToMods_ + modName + SLASH + modName, QDirIterator::Subdirectories);

	float i = NULL;

	while (it.hasNext()) {

		QFileInfo info(it.next());

		if (info.suffix() != nullptr && info.fileName() != ".." && info.fileName() != '.') {

			i++;
		}
	}

	return i;
}

void Mod::addMod(QString pathToMod)
{
	QFileInfo info(pathToMod);
	QFileInfo qFileInfo(info.fileName());

	QString modName = info.fileName();

	modName = modName.remove(qFileInfo.suffix());
	modName = modName.remove('.');

	QDir dir(pathToMods_);
	dir.mkdir(modName);

	QString pathToCurrentMod = pathToMods_ + modName;

	QDir qDir(pathToCurrentMod);
	qDir.mkdir(modName);

	QFile file;
	file.setFileName(pathToCurrentMod + "\\" + "filelist.txt");
	file.open(QIODevice::WriteOnly);
	file.close();

	file.setFileName(pathToCurrentMod + "\\" + "state.txt");
	file.open(QIODevice::WriteOnly);
	file.write("0");
	file.close();

	file.setFileName(pathToCurrentMod + "\\" + "addtime.txt");
	file.open(QIODevice::WriteOnly);
	file.write(QTime::currentTime().toString(Qt::ISODate).toUtf8());
	file.close();

	file.setFileName(pathToCurrentMod + "\\" + "dateadded.txt");
	file.open(QIODevice::WriteOnly);
	file.write(QDate::currentDate().toString(Qt::ISODate).toUtf8());
	file.close();

	this->unzippingArchive(pathToMod, pathToCurrentMod + "\\" + modName);
	this->writeAllModFilesTofile(pathToCurrentMod, modName);
	this->showMods();
}

void Mod::unzippingArchive(QString pathToArchive, QString pathToExtract)
{
	QString app = "UnpackingArchive.exe";

	QProcess* process = new QProcess;

	QStringList arg;

	arg << pathToArchive << pathToExtract;

	process->startDetached(app, arg);

	while (true) {

		qDebug() << "go" << endl;

		if (!Process::isProcessRun(L"UnpackingArchive.exe")) break;
	}
}

void Mod::writeAllModFilesTofile(QString pathToMod, QString modName)
{
	QDirIterator it(pathToMod + "\\" + modName, QDirIterator::Subdirectories);

	QFile file(pathToMod + "\\" + "filelist.txt");
	file.open(QIODevice::WriteOnly);

	while (it.hasNext()) {

		QFileInfo info(it.next());
		QFileInfo fileName(info.fileName());

		if (fileName.suffix() != nullptr && info.fileName() != ".." && info.fileName() != '.') {

			file.write(info.fileName().toUtf8() + "\n");

			qDebug() << info.absoluteFilePath() << endl;
		}
	}

	file.close();
}

void Mod::writeAllPathsToModFiles(QString pathToMod, QString modName)
{
	QDirIterator it(pathToMod + "\\" + modName, QDirIterator::Subdirectories);

	QFile file(pathToMod + "\\" + "filepathlist.txt");
	file.open(QIODevice::WriteOnly);

	while (it.hasNext()) {

		QFileInfo info(it.next());
		QFileInfo fileName(info.fileName());

		if (fileName.suffix() != nullptr && info.fileName() != ".." && info.fileName() != '.') {

			file.write(info.absoluteFilePath().toUtf8() + "\n");
		}
	}

	file.close();
}

void Mod::showMods()
{
	modsWidget_->clear();

	QDir dir(pathToMods_);

	QFileInfoList modList = dir.entryInfoList();

	foreach(QFileInfo mod, modList)
	{
		if (mod.suffix() == nullptr && mod.fileName() != ".." && mod.fileName() != '.') {

			if (this->getModState(mod.fileName()) == DISABLE) {

				modsWidget_->addItem(new QListWidgetItem(QIcon(":/EternalModManager/Resources/disableMod.png"), mod.fileName()));

				modsWidget_->item(this->getItemIndex(*modsWidget_, mod.fileName()))->setForeground(Qt::gray);

			} else if (this->getModState(mod.fileName()) == ENABLE) {

				modsWidget_->addItem(new QListWidgetItem(QIcon(":/EternalModManager/Resources/ok.png"), mod.fileName()));
			}
		}
	}
}

int Mod::getModState(QString modName)
{
	QFile file(pathToMods_ + modName + "\\" + "state.txt");

	QString state = "";

	if ((file.exists()) && (file.open(QIODevice::ReadOnly))) {

		while (!file.atEnd()) {

			state = file.readLine();
		}
		file.close();
	}

	return state.toInt();
}

void Mod::disableMod(QString modName)
{
	QFile qfile(pathToMods_+ modName + "\\" + "state.txt");
	qfile.open(QIODevice::WriteOnly);
	qfile.write("0");
	qfile.close();

	QDirIterator it(pathToGame_ + SLASH + "Data", QDirIterator::Subdirectories);
	while (it.hasNext()) {

		QFileInfo info(it.next());

		if (info.fileName() != ".." && info.fileName() != '.' && info.suffix() != nullptr) {
			
			QFile file(pathToMods_ + modName + SLASH + "filelist.txt");
			
			if ((file.exists()) && (file.open(QIODevice::ReadOnly))) {

				QString str = "";

				while (!file.atEnd()) {

					str = file.readLine();
					str.remove("\n");

					if (info.fileName() == str) {
				
						QFile::remove(info.absoluteFilePath());
					}
				}

				file.close();
			}
		}
	}
}

void Mod::enableMod(QString modName)
{
	QFile qfile(pathToMods_ + modName + "\\" + "state.txt");
	qfile.open(QIODevice::WriteOnly);
	qfile.write("1");
	qfile.close();

	QString pathToMod = pathToMods_ + modName + SLASH + modName;
	QDir dir(pathToMod);

	QFileInfoList modList = dir.entryInfoList();

	foreach(QFileInfo mod, modList)
	{
		if (mod.fileName() != ".." && mod.fileName() != '.') {

			if (mod.suffix() != nullptr) {

				QFile::copy(mod.absoluteFilePath(), pathToGame_ + SLASH + "Data" + SLASH + mod.fileName());

				if (mod.suffix() == "esp" || mod.suffix() == "esm") {

					Plugin::addPlugin(mod.fileName());
				}

			} else if (mod.suffix() == nullptr) {

				if (mod.fileName() == "Data") {

					this->copyFileFromData(pathToMod + SLASH + "Data");
					return;
				}

				if (mod.fileName() == "data") {

					this->copyFileFromData(pathToMod + SLASH + "data");
					return;
				}

				if (modName == modName) {

					this->copyFileFromData(pathToMod + SLASH + modName);
					return;
				}

				SDir::copyFolder(mod.filePath(), pathToGame_ + SLASH + "Data" + SLASH + mod.fileName());
			}
		}
	}
}

void Mod::copyFileFromData(QString pathToMod)
{
	QDir dir(pathToMod);

	QFileInfoList modList = dir.entryInfoList();

	foreach(QFileInfo mod, modList)
	{
		if (mod.fileName() != ".." && mod.fileName() != '.') {

			if (mod.suffix() != nullptr) {

				QFile::copy(mod.absoluteFilePath(), pathToGame_ + SLASH + "Data" + SLASH + mod.fileName());

				if (mod.suffix() == "esp" || mod.suffix() == "esm") {

					Plugin::addPlugin(mod.fileName());
				}

			}
			else if (mod.suffix() == nullptr) {

				if (mod.fileName() == "Data") {

					this->copyFileFromData(pathToMod + SLASH + "Data");
					return;
				}

				if (mod.fileName() == "data") {

					this->copyFileFromData(pathToMod + SLASH + "data");
					return;
				}

				SDir::copyFolder(mod.filePath(), pathToGame_ + SLASH + "Data" + SLASH + mod.fileName());
			}
		}
	}
}

void Mod::removeMod(QString modName)
{
	QDir dir(pathToMods_ + modName);
	dir.removeRecursively();
}

int Mod::getItemIndex(QListWidget& widget, QString itemName)
{
	for (int i = 0; i < widget.count(); i++) {

		if (widget.item(i)->text() == itemName) return i;
	}
}

bool Mod::isExist(QString pathToMod)
{
	QDir dir(pathToMods_);

	QFileInfo qFileInfo(pathToMod);
	QFileInfo info(qFileInfo.fileName());

	QString modName = qFileInfo.fileName();

	modName.remove(".zip");

	QFileInfoList modList = dir.entryInfoList();

	foreach(QFileInfo mod, modList)
	{
		if (mod.fileName() == modName) return true;
	}

	return false;
}

int Mod::getTotalNumberOfMods()
{
	QDir dir(pathToMods_);

	QFileInfoList modList = dir.entryInfoList();

	int i = 0;

	foreach(QFileInfo mod, modList)
	{
		if (mod.fileName() != ".." && mod.fileName() != '.' && mod.suffix() == nullptr) i++;
	}

	return i;
}

int Mod::getNumberOfEnabledMods()
{
	QDir dir(pathToMods_);

	QFileInfoList modList = dir.entryInfoList();

	int i = 0;

	foreach(QFileInfo mod, modList)
	{
		if (mod.fileName() != ".." && mod.fileName() != '.' && mod.suffix() == nullptr) {

			QFile file(pathToMods_ + mod.fileName() + "\\" + "state.txt");

			if ((file.exists()) && (file.open(QIODevice::ReadOnly))) {

				QString modState = "";

				while (!file.atEnd()) {

					modState = file.readLine();

				}

				if (modState.toInt() == ENABLE) i++;

				file.close();
			}
		}
	}

	return i;
}

int Mod::getNumberOfDisabledods()
{
	QDir dir(pathToMods_);

	QFileInfoList modList = dir.entryInfoList();

	int i = 0;

	foreach(QFileInfo mod, modList)
	{
		if (mod.fileName() != ".." && mod.fileName() != '.' && mod.suffix() == nullptr) {

			QFile file(pathToMods_ + mod.fileName() + "\\" + "state.txt");

			if ((file.exists()) && (file.open(QIODevice::ReadOnly))) {

				QString modState = "";

				while (!file.atEnd()) {

					modState = file.readLine();

				}

				if (modState.toInt() == DISABLE) i++;

				file.close();
			}
		}
	}

	return i;
}

QString Mod::getNameEspFileMod(QString modName)
{
	QDir dir(pathToMods_ + modName + SLASH + modName);

	QFileInfoList modList = dir.entryInfoList();

	foreach(QFileInfo mod, modList)
	{
		if (mod.suffix() == "esp" || mod.suffix() == "esm") return mod.fileName();

		if (mod.fileName() == "Data") {

			return this->getNameEspFileModFromData(pathToMods_ + modName + SLASH + modName + SLASH + "Data");
		}

		if (mod.fileName() == "data") {

			return this->getNameEspFileModFromData(pathToMods_ + modName + SLASH + modName + SLASH + "data");
		}
	}

	return "SNULL";
}

QString Mod::getNameEspFileModFromData(QString pathToMod)
{
	QDir dir(pathToMod);

	QFileInfoList modList = dir.entryInfoList();

	foreach(QFileInfo mod, modList)
	{
		if (mod.suffix() == "esp" || mod.suffix() == "esm") return mod.fileName();
	}

	return "SNULL";
}

void Mod::setPathToGame(QString pathToGame)
{
	pathToGame_ = pathToGame;
}

QString Mod::getAddTime(QString modName)
{
	QFile file(pathToMods_ + modName + "\\" + "addtime.txt");

	QString time = "";

	if ((file.exists()) && (file.open(QIODevice::ReadOnly))) {

		while (!file.atEnd()) {

			time = file.readLine();
		}
		file.close();
	}

	return time;
}

QString Mod::getDateAdded(QString modName)
{
	QFile file(pathToMods_ + modName + "\\" + "dateadded.txt");

	QString data = "";

	if ((file.exists()) && (file.open(QIODevice::ReadOnly))) {

		while (!file.atEnd()) {

			data = file.readLine();
		}
		file.close();
	}

	return data;
}


Mod::~Mod()
{
}
