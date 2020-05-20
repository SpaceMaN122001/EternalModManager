#include "Plugin.h"

Plugin::Plugin(QListWidget* widget)
{
	widget_ = widget;

	this->showPluginList();
}


Plugin::~Plugin()
{
}

QString Plugin::getPathToPluginListSkyrimSe()
{
	QString userName = QDir::home().dirName();

	QString skyrimSeDirectory = "C:\\Users\\" + userName + "\\" + "AppData\\Local\\Skyrim Special Edition\\";

	return skyrimSeDirectory;
}

QString Plugin::getPluginListFileName()
{
	return "plugins.txt";
}

void Plugin::showPluginList()
{
	QFile file(Plugin::getPathToPluginListSkyrimSe() + Plugin::getPluginListFileName());

	int i = 0;

	widget_->clear();

	if ((file.exists()) && (file.open(QIODevice::ReadOnly))) {

		QString pluginName = "";

		while (!file.atEnd()) {

			pluginName = file.readLine();

			if (i >= 2) {

				if (pluginName.contains('*')) {

					pluginName.remove('*');

					widget_->addItem(new QListWidgetItem(QIcon(":/EternalModManager/Resources/enableAllPlugins.png"), pluginName));

				} else {

					widget_->addItem(new QListWidgetItem(QIcon(":/EternalModManager/Resources/disableAllPlugins.png"), pluginName));
				}
			}

			i++;
		}

		file.close();
	}
}

void Plugin::disableAllPlugins()
{
	QFile file(Plugin::getPathToPluginListSkyrimSe() + Plugin::getPluginListFileName());

	QString* pluginArray = NULL;
	pluginArray = this->getPluginList();

	int size = Plugin::getNumberOfPlugins();

	if (file.open(QIODevice::WriteOnly)) {

		file.write("# This file is used by Skyrim to keep track of your downloaded content.\n");
		file.write("# Please do not modify this file.\n");;

		for (int i = 0; i < size; i++) {

			pluginArray[i].remove('*');

			file.write(pluginArray[i].toUtf8());

			//qDebug() << pluginArray[i] << endl;
		}

		file.close();

		this->showPluginList();

		delete[] pluginArray;
	}
}

void Plugin::enableAllPlugins()
{
	QFile file(Plugin::getPathToPluginListSkyrimSe() + Plugin::getPluginListFileName());

	QString* pluginArray = NULL;
	pluginArray = this->getPluginList();

	int size = Plugin::getNumberOfPlugins();

	if (file.open(QIODevice::WriteOnly)) {

		file.write("# This file is used by Skyrim to keep track of your downloaded content.\n");
		file.write("# Please do not modify this file.\n");;

		for (int i = 0; i < size; i++) {

			if (pluginArray[i].contains('*')) {

				pluginArray[i].remove('*');

				pluginArray[i] = '*' + pluginArray[i];
				file.write(pluginArray[i].toUtf8());

			} else {

				pluginArray[i] = '*' + pluginArray[i];
				file.write(pluginArray[i].toUtf8());

				//qDebug() << pluginArray[i] << endl;
			}

		}

		file.close();

		this->showPluginList();

		delete[] pluginArray;
	}
}

void Plugin::disablePlugin(QString pluginName)
{
	QFile file(Plugin::getPathToPluginListSkyrimSe() + Plugin::getPluginListFileName());

	QString* pluginArray = NULL;
	pluginArray = this->getPluginList();

	int size = Plugin::getNumberOfPlugins();

	if (file.open(QIODevice::WriteOnly)) {

		file.write("# This file is used by Skyrim to keep track of your downloaded content.\n");
		file.write("# Please do not modify this file.\n");

		for (int i = 0; i < size; i++) {

			QString plgName = pluginArray[i];

			if (plgName.remove('*') == pluginName) {

				pluginArray[i].remove('*');

				file.write(pluginArray[i].toUtf8());

			} else {

				file.write(pluginArray[i].toUtf8());
			}

		}

		file.close();

		this->showPluginList();

		delete[] pluginArray;
	}
}

void Plugin::enablePlugin(QString pluginName)
{
	QFile file(Plugin::getPathToPluginListSkyrimSe() + Plugin::getPluginListFileName());

	QString* pluginArray = NULL;
	pluginArray = this->getPluginList();

	int size = Plugin::getNumberOfPlugins();

	if (file.open(QIODevice::WriteOnly)) {

		file.write("# This file is used by Skyrim to keep track of your downloaded content.\n");
		file.write("# Please do not modify this file.\n");

		for (int i = 0; i < size; i++) {

			//QString plgName = pluginArray[i];

			if (pluginArray[i] == pluginName) {

				pluginArray[i] = '*' + pluginArray[i];

				file.write(pluginArray[i].toUtf8());

			}
			else {

				file.write(pluginArray[i].toUtf8());
			}

		}

		file.close();

		this->showPluginList();

		delete[] pluginArray;
	}
}

void Plugin::movePluginUp(QString pluginName)
{
	if (this->getPluginState(pluginName)) pluginName = '*' + pluginName;

	QFile file(Plugin::getPathToPluginListSkyrimSe() + Plugin::getPluginListFileName());

	QString* pluginArray = NULL;
	pluginArray = this->getPluginList();

	int size = Plugin::getNumberOfPlugins();

	QString plgName = pluginName;
	plgName.remove('*');
	plgName.remove("\n");

	for (int i = 0; i < size; i++) {
		
		QString plg = pluginArray[i];
		plg.remove('*');
		plg.remove("\n");

		if (plg == plgName) {

			if (i == 0) return;

			pluginArray[i] = pluginArray[i - 1];
			pluginArray[i - 1] = pluginName;
			break;
		}
	}

	this->writingPluginsTofile(pluginArray);
}

void Plugin::movePluginDown(QString pluginName)
{
	if (this->getPluginState(pluginName)) pluginName = '*' + pluginName;

	QFile file(Plugin::getPathToPluginListSkyrimSe() + Plugin::getPluginListFileName());

	QString* pluginArray = NULL;
	pluginArray = this->getPluginList();

	int size = Plugin::getNumberOfPlugins();

	QString plgName = pluginName;
	plgName.remove('*');
	plgName.remove("\n");

	for (int i = 0; i < size; i++) {

		QString plg = pluginArray[i];
		plg.remove('*');
		plg.remove("\n");

		if (plg == plgName) {

			if (i == size - 1) return;

			pluginArray[i] = pluginArray[i + 1];
			pluginArray[i + 1] = pluginName;
			break;
		}
	}

	this->writingPluginsTofile(pluginArray);
}

void Plugin::writingPluginsTofile(QString* pluginArray)
{
	QFile file(Plugin::getPathToPluginListSkyrimSe() + Plugin::getPluginListFileName());

	int size = Plugin::getNumberOfPlugins();

	if (file.open(QIODevice::WriteOnly)) {

		file.write("# This file is used by Skyrim to keep track of your downloaded content.\n");
		file.write("# Please do not modify this file.\n");;

		for (int i = 0; i < size; i++) {

			file.write(pluginArray[i].toUtf8());
		}

		file.close();

		this->showPluginList();

		delete[] pluginArray;
	}
}

int Plugin::getNumberOfPlugins()
{
	QFile file(Plugin::getPathToPluginListSkyrimSe() + Plugin::getPluginListFileName());

	int i = 0;

	int numberOfPlugins = 0;

	if ((file.exists()) && (file.open(QIODevice::ReadOnly))) {

		QString pluginName = "";

		while (!file.atEnd()) {

			pluginName = file.readLine();

			if (i >= 2) {

				numberOfPlugins++;
			}

			i++;
		}

		file.close();
	}

	return numberOfPlugins;
}

int Plugin::getNumberOfPluginsDisabled()
{
	QFile file(Plugin::getPathToPluginListSkyrimSe() + Plugin::getPluginListFileName());

	int i = 0;

	int numberOfPlugins = 0;

	if ((file.exists()) && (file.open(QIODevice::ReadOnly))) {

		QString pluginName = "";

		while (!file.atEnd()) {

			pluginName = file.readLine();

			if (i >= 2) {

				if (pluginName.contains('*')) {

				} else {

					numberOfPlugins++;
				}
			}

			i++;
		}

		file.close();
	}

	return numberOfPlugins;
}

int Plugin::getNumberOfPluginsIncluded()
{
	QFile file(Plugin::getPathToPluginListSkyrimSe() + Plugin::getPluginListFileName());

	int i = 0;

	int numberOfPlugins = 0;

	if ((file.exists()) && (file.open(QIODevice::ReadOnly))) {

		QString pluginName = "";

		while (!file.atEnd()) {

			pluginName = file.readLine();

			if (i >= 2) {

				if (pluginName.contains('*')) {

					numberOfPlugins++;
				}
			}

			i++;
		}

		file.close();
	}

	return numberOfPlugins;
}

QString* Plugin::getPluginList()
{
	int i = 0;

	int j = 0;

	QString* pluginArray = new QString[Plugin::getNumberOfPlugins()];

	QFile file(Plugin::getPathToPluginListSkyrimSe() + Plugin::getPluginListFileName());

	if ((file.exists()) && (file.open(QIODevice::ReadOnly))) {

		QString pluginName = "";

		while (!file.atEnd()) {

			pluginName = file.readLine();

			if (i >= 2) {

				pluginArray[j] = pluginName;

				j++;
			}

			i++;
		}

		file.close();
	}

	return pluginArray;
}

bool Plugin::getPluginState(QString pluginName)
{
	QString* pluginArray = NULL;
	pluginArray = this->getPluginList();

	for (int i = 0; i < Plugin::getNumberOfPlugins(); i++) {

		QString plgName = pluginArray[i];

		if (plgName.remove('*') == pluginName) {

			if (pluginArray[i].contains('*')) {

				return true;

			} else {

				return false;
			}
		}
	}
}

void Plugin::uploadFileDownloadOrder(QString pathToFile)
{
	QFile::remove(Plugin::getPathToPluginListSkyrimSe() + Plugin::getPluginListFileName());

	QFileInfo fileInfo(pathToFile);

	QFile::copy(pathToFile, Plugin::getPathToPluginListSkyrimSe() + fileInfo.fileName());

	this->showPluginList();
}

void Plugin::saveBootOrderFile(QString pathToFile)
{
	QFileInfo fileInfo(pathToFile);
	QFile::copy(Plugin::getPathToPluginListSkyrimSe() + Plugin::getPluginListFileName(), fileInfo.path() + "\\" + Plugin::getPluginListFileName());

	QFile::rename(fileInfo.path() + "\\" + Plugin::getPluginListFileName(), fileInfo.path() + "\\" + fileInfo.fileName());
}

void Plugin::addPlugin(QString pluginName)
{
	QFile file(getPathToPluginListSkyrimSe() + getPluginListFileName());

	file.open(QIODevice::Append | QIODevice::Text);
	file.write(pluginName.toUtf8() + "\n");

	file.close();
}

void Plugin::removePlugin(QString pluginName)
{
	if (pluginName == "SNULL") return;

	QFile file(Plugin::getPathToPluginListSkyrimSe() + Plugin::getPluginListFileName());

	QString* pluginArray = NULL;
	pluginArray = this->getPluginList();

	int size = Plugin::getNumberOfPlugins();

	if (file.open(QIODevice::WriteOnly)) {

		file.write("# This file is used by Skyrim to keep track of your downloaded content.\n");
		file.write("# Please do not modify this file.\n");

		for (int i = 0; i < size; i++) {

			QString plgName = pluginArray[i];
			plgName.remove("\r");
			plgName.remove("\n");

			if (plgName != pluginName && plgName.remove('*') != pluginName) {
				qDebug() << plgName.remove("\r");
				file.write(pluginArray[i].toUtf8());
			}
		}

		file.close();

		this->showPluginList();

		delete[] pluginArray;
	}
}