#include "ModInstalling.h"

ModInstalling::ModInstalling(QString modName, QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);

	modName_ = modName;

	ModManager* manager = new ModManager;

	ui.descriptionLabel->setText(manager->getModDescription(modName_));
	ui.modulNameLabel->hide();
	ui.modNameLabel->setText(modName_ + " " + manager->getModVersion(modName_));
	ui.imageLabel->setPixmap(QPixmap(manager->getModImagePath(modName_)));
	this->setWindowTitle(modName_);
	this->setWindowIcon(QIcon(":/EternalModManager/Resources/eternal.png"));
	this->setFixedSize(QSize(this->width(), this->height()));
}


ModInstalling::~ModInstalling()
{
}
