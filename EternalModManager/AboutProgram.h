#pragma once
#include <QtWidgets>
#include "ui_AboutProgram.h"
#include "KeyWords.h"
#include "SSettings.h"

class AboutProgram : public QWidget
{
	Q_OBJECT
public:
	explicit AboutProgram(QWidget *parent = nullptr);
	~AboutProgram();
private:
	Ui::AboutProgramForm ui;

private slots:
	void closeAboutProgram();
};

