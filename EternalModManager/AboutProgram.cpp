#include "AboutProgram.h"

AboutProgram::AboutProgram(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);

	this->setWindowTitle("About program");
	this->setWindowIcon(QIcon(":/EternalModManager/Resources/eternal.png"));
	this->setFixedSize(QSize(this->width(), this->height()));

	ui.linkToDeveloperVkLabel->setText("<a href=\"https://vk.com/spaceman1210\">SpaceMaN</a>");
	ui.linkToDeveloperVkLabel->setTextFormat(Qt::RichText);
	ui.linkToDeveloperVkLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
	ui.linkToDeveloperVkLabel->setOpenExternalLinks(true);

	ui.linkToGithubLabel->setText("<a href=\"https://github.com/SpaceMaN122001/EternalModManager\">Eternal mod manager</a>");
	ui.linkToGithubLabel->setTextFormat(Qt::RichText);
	ui.linkToGithubLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
	ui.linkToGithubLabel->setOpenExternalLinks(true);

	ui.linkToGithubDeveloperAccountLabel->setText("<a href=\"https://github.com/SpaceMaN122001\">SpaceMaN122001</a>");
	ui.linkToGithubDeveloperAccountLabel->setTextFormat(Qt::RichText);
	ui.linkToGithubDeveloperAccountLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
	ui.linkToGithubDeveloperAccountLabel->setOpenExternalLinks(true);

	ui.eternalModManagerLogoLabel->setPixmap(QPixmap(":/EternalModManager/Resources/eternallogo.png"));

	connect(ui.quitPushButton, SIGNAL(clicked()), this, SLOT(closeAboutProgram()));

	if (SSettings::getKeyValue("Eternal mod manager", "language") == RU) {

		ui.versionLabel->setText(RUS("Версия: 0.1"));
		ui.developerLabel->setText(RUS("Разработчик:"));
		ui.gitHubSourceLabel->setText(RUS("Исходный код на Github:"));
		ui.githubDeveloperAccountLabel->setText(RUS("Аккаунт разработчика на gitHub:"));

		this->setWindowTitle(RUS("О программе"));
	}

	if (SSettings::getKeyValue("Eternal mod manager", "theme") == DARK) {

		this->setStyleSheet("color: rgb(255, 255, 255);\nbackground-color: rgb(46, 47, 48);");

	}
}

void AboutProgram::closeAboutProgram()
{
	this->close();
}


AboutProgram::~AboutProgram()
{
}
