#include "GameSelection.h"

GameSelection::GameSelection(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);

	this->setWindowFlags(Qt::CustomizeWindowHint);

	this->setWindowIcon(QIcon(":/EternalModManager/Resources/eternal.png"));
	this->setWindowTitle("Game selection");

	ui.gameSelectlistWidget->setIconSize(QSize(96, 96));

	ui.gameSelectlistWidget->addItem(new QListWidgetItem(QIcon(":/EternalModManager/Resources/skyrimse2.png"), "SKYRIM SE"));
	//ui.gameSelectlistWidget->addItem(new QListWidgetItem(QIcon(":/EternalModManager/Resources/skyrimle.png"), "SKYRIM LE"));
	//ui.gameSelectlistWidget->addItem(new QListWidgetItem(QIcon(":/EternalModManager/Resources/fallout4.png"), "FALLOUT 4"));

	ui.okPushButton->setEnabled(false);

	connect(ui.okPushButton, SIGNAL(clicked()), this, SLOT(gameSelect()));
	connect(ui.gameSelectlistWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(gameSelect()));
	connect(ui.gameSelectlistWidget, SIGNAL(itemSelectionChanged()), this, SLOT(saveSelecteditem()));
	connect(ui.quitPushButton, SIGNAL(clicked()), this, SLOT(programQuit()));

	if (SSettings::getKeyValue("Eternal mod manager", "language") == RU) {

		this->setWindowTitle(RUS("Выбор игры"));

		ui.quitPushButton->setText(RUS("Выход"));
	}
}

void GameSelection::gameSelect()
{
	if (selectedGame_ == "SKYRIM SE") {

		if (!SSettings::isExistKey("Eternal mod manager", "skyrimse") || SSettings::getKeyValueS("Eternal mod manager", "skyrimse") == nullptr) {

			if (SSettings::getKeyValue("Eternal mod manager", "language") == EN) QMessageBox::about(this, "Attention", "No way to game found");
			if (SSettings::getKeyValue("Eternal mod manager", "language") == RU) QMessageBox::about(this, RUS("Внимание"), RUS("Путь до игры не найден"));

			this->close();

			GameDefinition* def = new GameDefinition;
			def->setAttribute(Qt::WA_DeleteOnClose);
			def->show();
		}


		else {

			this->close();
			EternalModManager* m = new EternalModManager;
			m->setAttribute(Qt::WA_DeleteOnClose);
			m->show();
		}

	}
}

void GameSelection::saveSelecteditem()
{
	ui.okPushButton->setEnabled(true);
	selectedGame_ = ui.gameSelectlistWidget->currentItem()->text();
}

void GameSelection::mouseMoveEvent(QMouseEvent* e)
{
	if (e->buttons() | Qt::LeftButton) {
		setGeometry(
			pos().x() + (e->x() - dx),
			pos().y() + (e->y() - dy),
			width(),
			height());
	}
}

void GameSelection::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton) {
		dx = e->x();
		dy = e->y();
		setCursor(Qt::OpenHandCursor);
	}
}

void GameSelection::mouseReleaseEvent(QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton) {
		setCursor(Qt::ArrowCursor);
	}
}

void GameSelection::programQuit()
{
	this->close();
}

GameSelection::~GameSelection()
{
}
