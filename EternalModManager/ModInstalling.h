#pragma once
#include "ui_ModInstalling.h"
#include "ModManager.h"
#include "KeyWords.h"
#include <QtWidgets>

class ModInstalling : public QWidget
{
	Q_OBJECT
public:
	explicit ModInstalling(QString modName, QWidget *parent = nullptr);
	~ModInstalling();
private:
	Ui::ModInstallingForm ui;
	QString modName_;
};

