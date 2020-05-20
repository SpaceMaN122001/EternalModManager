#include "ModInfo.h"

ModInfo::ModInfo(QString modName, QWidget *parent) : QWidget(parent)
{
	modName_ = modName;

	ui.setupUi(this);
	ui.modImageLabel->setPixmap(QPixmap(":/EternalModManager/Resources/mod.png"));
	this->setWindowTitle("Mod property");
	this->setWindowIcon(QIcon(":/EternalModManager/Resources/eternity.png"));
	ui.modNameLabel->setText(modName_);

	Mod mod(ui.modFilesListWidget);
	mod.showModFiles(modName_);

	ui.modSizeValueLabel->setText(QString::number(mod.getModSize(modName_)));
	ui.numberOfFilesValueLabel->setText(QString::number(mod.getNumberOfFiles(modName_)));

	ui.addTimeValueLabel->setText(mod.getAddTime(modName_));
	ui.dateAddedValueLabel->setText(mod.getDateAdded(modName_));

	connect(ui.OkPushButton, SIGNAL(clicked()), this, SLOT(propertyClose()));

	if (SSettings::getKeyValue("Eternal mod manager", "language") == RU) {

		this->setWindowTitle(RUS("Свойства мода"));
		ui.modSizeLabel->setText(RUS("Размер мода"));
		ui.numberOfFilesLabel->setText(RUS("Количество файлов"));
		ui.addTimeLabel->setText(RUS("Время добавления"));
		ui.dateAddedLabel->setText(RUS("Дата добавления"));
	}
}

void ModInfo::propertyClose()
{
	this->close();
}


ModInfo::~ModInfo()
{
}
