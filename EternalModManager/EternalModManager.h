#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_EternalModManager.h"
#include <QToolButton>
#include <QProcess>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QTextCodec>
#include <QTimer>
#include "Process.h"
#include "Plugin.h"
#include "SSettings.h"
#include "GameDefinition.h"
#include "Mod.h"
#include "ModInfo.h"
#include "KeyWords.h"
#include "GameSelection.h"
#include "AboutProgram.h"

class EternalModManager : public QMainWindow
{
	Q_OBJECT

public:
	EternalModManager(QWidget *parent = Q_NULLPTR);

private:
	Ui::EternalModManagerClass ui;
	void setCustomButtonStyle(QToolButton& button, QString imagePath, QString toolTip);
	Plugin* plg;
	QString selectedPlugin_;
	QString selectedMod_;
	SSettings* settings;
	QString pathToSkyrimSe_;
	Mod* mod;

private slots:
	void disableAllPluginsOnToolButtonCliked();
	void enableAllPluginsOnToolButtonCliked();
	void customContextMenu(const QPoint &pos);
	void disablePlugin();
	void selectItemWhenClick();
	void enablePlugin();
	void updatePluginsInfo();
	void uploadFileDownloadOrder();
	void saveBootOrderFile();
	void gameRun();
	void applySettings();
	void setRussianLanguage();
	void setDarkTheme();
	void rescanInstalledGames();
	void setDefaultSettings();
	void addMod();
	void modsContextMenu(const QPoint &pos);
	void selectMod();
	void updateModsInfo();
	void disableMod();
	void enableMod();
	void removeMod();
	void openModProperty();
	void movePluginUp();
	void movePluginDown();
	void selectLanguage();
	void launchType();
	void selectTheme();
	void closePorgramAfterLaunch();
	void gameSelect();
	void aboutProgram();
	void recountPlguins();
};
