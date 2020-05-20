#pragma once
#include <QtWidgets>
#include <QMessageBox>
#include "ui_ModInfo.h"
#include "Mod.h"
#include "KeyWords.h"
#include "SSettings.h"

class ModInfo : public QWidget
{
	Q_OBJECT
public:
	explicit ModInfo(QString modName, QWidget *parent = nullptr);
	~ModInfo();
private:
	Ui::ModInfoForm ui;
	QString pathToMods_;
	QString modName_;
private slots:
	void propertyClose();
};

