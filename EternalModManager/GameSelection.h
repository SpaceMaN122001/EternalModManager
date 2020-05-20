#pragma once
#include <QtWidgets>
#include <QMessageBox>
#include <QMouseEvent>
#include "ui_GameSelection.h"
#include "SSettings.h"
#include "GameDefinition.h"
#include "EternalModManager.h"
#include "SSettings.h"
#include "KeyWords.h"

class GameSelection : public QWidget
{
	Q_OBJECT
public:
	explicit GameSelection(QWidget *parent = nullptr);
	~GameSelection();
private:
	Ui::GameSelectionForm ui;
	QString selectedGame_;
	int dx;
	int dy;
private slots:
	void gameSelect();
	void saveSelecteditem();
	void mouseMoveEvent(QMouseEvent* e);
	void mousePressEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void programQuit();
};

