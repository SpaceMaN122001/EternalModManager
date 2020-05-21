#pragma once
#include "ui_ModInstalling.h"
#include <QtWidgets>

class ModInstalling : public QWidget
{
	Q_OBJECT
public:
	explicit ModInstalling(QWidget *parent = nullptr);
	~ModInstalling();
private:
	Ui::ModInstallingForm ui;
};

