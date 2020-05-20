#pragma once
#include <QWidget>
#include <QDir>
#include <QListWidget>
#include <QDebug>
#include <QSettings>

class Plugin
{
public:
	Plugin(QListWidget* widget);
	~Plugin();
	static QString getPathToPluginListSkyrimSe();
	static QString getPluginListFileName();
	void showPluginList();
    void disableAllPlugins();
	void enableAllPlugins();
	void disablePlugin(QString pluginName);
	void enablePlugin(QString pluginName);
	void movePluginUp(QString pluginName);
	void movePluginDown(QString pluginName);
	static int getNumberOfPlugins();
	static int getNumberOfPluginsDisabled();
	static int getNumberOfPluginsIncluded();
	bool getPluginState(QString pluginName);
	void uploadFileDownloadOrder(QString pathToFile);
	void saveBootOrderFile(QString pathToFile);
	static void addPlugin(QString pluginName);
	void removePlugin(QString pluginName);
private:
	QListWidget* widget_;
	QString* getPluginList();
	void writingPluginsTofile(QString* pluginArray);
};

