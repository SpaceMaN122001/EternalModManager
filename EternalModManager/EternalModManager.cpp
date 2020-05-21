#include "EternalModManager.h"
//QMessageBox::about(this, "", "");
EternalModManager::EternalModManager(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.applySettingsPushButton->setEnabled(false);
	ui.defaultSettingsPushButton->setEnabled(false);

	this->setWindowIcon(QIcon(":/EternalModManager/Resources/eternal.png"));

	ui.pluginListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	ui.modsListWidget->setContextMenuPolicy(Qt::CustomContextMenu);

	setCustomButtonStyle(*ui.movingPluginUpToolButton, ":/EternalModManager/Resources/up.png", "Move plugin up");
	setCustomButtonStyle(*ui.movingPluginDownToolButton, ":/EternalModManager/Resources/down.png", "Move plugin down");
	setCustomButtonStyle(*ui.disablingAllPluginsToolButton, ":/EternalModManager/Resources/disableAllPlugins.png", "Disable all plugins");
	setCustomButtonStyle(*ui.inclusionAllPluginsToolButton, ":/EternalModManager/Resources/enableAllPlugins.png", "Enable all plugins");
	setCustomButtonStyle(*ui.addingpluginToolButton, ":/EternalModManager/Resources/addplugin.png", "Add new plugin");
	setCustomButtonStyle(*ui.uploadFileDownloadOrderTtoolButton, ":/EternalModManager/Resources/load.png", "upload file download order");
	setCustomButtonStyle(*ui.saveLoadingOrderFileToolButton, ":/EternalModManager/Resources/save.png", "save file download order");
	setCustomButtonStyle(*ui.gameRunToolButton, ":/EternalModManager/Resources/skyrim.png", "Game run");
	setCustomButtonStyle(*ui.gameRunToolButton, ":/EternalModManager/Resources/skyrimse2.png", "Game run");
	setCustomButtonStyle(*ui.rescanGameToolButton, ":/EternalModManager/Resources/rescan.png", "Rescan installed games");
	setCustomButtonStyle(*ui.gameSelectToolButton, ":/EternalModManager/Resources/game.png", "Game select");
	setCustomButtonStyle(*ui.aboutToolButton, ":/EternalModManager/Resources/about.png", "About program");
	setCustomButtonStyle(*ui.recountPluginsToolButton, ":/EternalModManager/Resources/discharge.png", "Recount plugins (The list of plugins will be changed)");

	ui.mainTabWidget->setTabIcon(2, QIcon(":/EternalModManager/Resources/settings.png"));
	ui.mainTabWidget->setTabIcon(0, QIcon(":/EternalModManager/Resources/plugins.png"));
	ui.mainTabWidget->setTabIcon(1, QIcon(":/EternalModManager/Resources/mods.png"));
	ui.mainTabWidget->setIconSize(QSize(19, 19));

	ui.selectLanugageComboBox->setItemIcon(0, QIcon(":/EternalModManager/Resources/uk.png"));
	ui.selectLanugageComboBox->setItemIcon(1, QIcon(":/EternalModManager/Resources/rus.png"));

	ui.selectLaunchTypeComboBox->setItemIcon(0, QIcon(":/EternalModManager/Resources/skyrim.png"));
	ui.selectLaunchTypeComboBox->setItemIcon(1, QIcon(":/EternalModManager/Resources/skyrim.png"));
	ui.selectLaunchTypeComboBox->setItemIcon(2, QIcon(":/EternalModManager/Resources/skyrim.png"));

	ui.themeComboBox->setItemIcon(0, QIcon(":/EternalModManager/Resources/defaultTheme.png"));
	ui.themeComboBox->setItemIcon(1, QIcon(":/EternalModManager/Resources/darkTheme.png"));

	ui.closeProgramAfterLaunchGameCheckBox->setIcon(QIcon(":/EternalModManager/Resources/close.png"));

	ui.pluginListWidget->setIconSize(QSize(21, 21));
	ui.modsListWidget->setIconSize(QSize(21, 21));

	connect(ui.disablingAllPluginsToolButton, SIGNAL(clicked()), this, SLOT(disableAllPluginsOnToolButtonCliked()));
	connect(ui.inclusionAllPluginsToolButton, SIGNAL(clicked()), this, SLOT(enableAllPluginsOnToolButtonCliked()));
	connect(ui.uploadFileDownloadOrderTtoolButton, SIGNAL(clicked()), this, SLOT(uploadFileDownloadOrder()));
	connect(ui.saveLoadingOrderFileToolButton, SIGNAL(clicked()), this, SLOT(saveBootOrderFile()));
	connect(ui.gameRunToolButton, SIGNAL(clicked()), this, SLOT(gameRun()));
	connect(ui.pluginListWidget, SIGNAL(customContextMenuRequested(QPoint)), SLOT(customContextMenu(QPoint)));
	connect(ui.modsListWidget, SIGNAL(customContextMenuRequested(QPoint)), SLOT(modsContextMenu(QPoint)));
	connect(ui.pluginListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(selectItemWhenClick()));
	connect(ui.modsListWidget, SIGNAL(itemSelectionChanged()), this, SLOT(selectMod()));
	connect(ui.applySettingsPushButton, SIGNAL(clicked()), this, SLOT(applySettings()));
	connect(ui.rescanGameToolButton, SIGNAL(clicked()), this, SLOT(rescanInstalledGames()));
	connect(ui.defaultSettingsPushButton, SIGNAL(clicked()), this, SLOT(setDefaultSettings()));
	connect(ui.addingpluginToolButton, SIGNAL(clicked()), this, SLOT(addMod()));
	connect(ui.movingPluginUpToolButton, SIGNAL(clicked()), this, SLOT(movePluginUp()));
	connect(ui.movingPluginDownToolButton, SIGNAL(clicked()), this, SLOT(movePluginDown()));
	connect(ui.selectLanugageComboBox, SIGNAL(activated(QString)), this, SLOT(selectLanguage()));
	connect(ui.selectLaunchTypeComboBox, SIGNAL(activated(QString)), this, SLOT(launchType()));
	connect(ui.themeComboBox, SIGNAL(activated(QString)), this, SLOT(selectTheme()));
	connect(ui.closeProgramAfterLaunchGameCheckBox, SIGNAL(clicked()), this, SLOT(closePorgramAfterLaunch()));
	connect(ui.gameSelectToolButton, SIGNAL(clicked()), this, SLOT(gameSelect()));
	connect(ui.aboutToolButton, SIGNAL(clicked()), this, SLOT(aboutProgram()));
	connect(ui.recountPluginsToolButton, SIGNAL(clicked()), this, SLOT(recountPlguins()));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));

	plg = new Plugin(ui.pluginListWidget);
	updatePluginsInfo();

	settings = new SSettings("Eternal mod manager");
	settings->setValue("language", EN);
	settings->setValue("theme", WHITE);
	settings->setValue("launchtype", LAUNCHER);
	settings->setValue("closeprogramafterlaunch", OFF);

	if (settings->getValue("language") == RU) this->setRussianLanguage();
	if (settings->getValue("theme") == DARK) this->setDarkTheme();
	if (settings->getValue("launchtype") == EXE) ui.selectLaunchTypeComboBox->setCurrentIndex(1);
	if (settings->getValue("launchtype") == SKSE64) ui.selectLaunchTypeComboBox->setCurrentIndex(2);
	if (settings->getValue("closeprogramafterlaunch") == ON) ui.closeProgramAfterLaunchGameCheckBox->setCheckState(Qt::CheckState::Checked);

	pathToSkyrimSe_ = SSettings::getKeyValueS("Eternal mod manager", "skyrimse");

	mod = new Mod(ui.modsListWidget);
	mod->setPathToGame(pathToSkyrimSe_);

	this->updateModsInfo();
}

void EternalModManager::customContextMenu(const QPoint &pos)
{
	QModelIndex index = ui.pluginListWidget->indexAt(pos);

	QMenu* customQMenu = new QMenu(this);
	customQMenu->setAttribute(Qt::WA_DeleteOnClose);

	QAction* disablePlugin = new QAction(QPixmap(":/EternalModManager/Resources/disableAllPlugins.png"), "&Disable plugin", this);

	QAction* enablePlugin = new QAction(QPixmap(":/EternalModManager/Resources/enableAllPlugins.png"), "&Enable plugin", this);

	QAction* updatePlguinInfo = new QAction(QPixmap(":/EternalModManager/Resources/Update.ico"), "&Update", this);

	if (settings->getValue("language") == RU) {

		disablePlugin->setText(RUS("Отключить плагин"));
		enablePlugin->setText(RUS("Включить плагин"));
		updatePlguinInfo->setText(RUS("Обновить"));
	}


	if (!plg->getPluginState(selectedPlugin_)) {

		customQMenu->addAction(enablePlugin);

	} else if (plg->getPluginState(selectedPlugin_)) {

		customQMenu->addAction(disablePlugin);
	}

	customQMenu->addAction(updatePlguinInfo);

	customQMenu->popup(ui.pluginListWidget->viewport()->mapToGlobal(pos));

	connect(disablePlugin, &QAction::triggered, this, &EternalModManager::disablePlugin);
	connect(enablePlugin, &QAction::triggered, this, &EternalModManager::enablePlugin);
	connect(updatePlguinInfo, &QAction::triggered, this, &EternalModManager::updatePluginsInfo);
}

void EternalModManager::modsContextMenu(const QPoint &pos)
{
	if (ui.modsListWidget->count() == NULL) return;

	QModelIndex index = ui.modsListWidget->indexAt(pos);

	QMenu* customQMenu = new QMenu(this);
	customQMenu->setAttribute(Qt::WA_DeleteOnClose);

	QAction* disableMod = new QAction(QPixmap(":/EternalModManager/Resources/disableAllPlugins.png"), "&Disable mod", this);
	QAction* enableMod = new QAction(QPixmap(":/EternalModManager/Resources/enableAllPlugins.png"), "&Enable mod", this);
	QAction* removeMod = new QAction(QPixmap(":/EternalModManager/Resources/remove.png"), "&Remove mod", this);
	QAction* updateModsInfo = new QAction(QPixmap(":/EternalModManager/Resources/Update.ico"), "&Update", this);
	QAction* modProperty = new QAction(QPixmap(":/EternalModManager/Resources/property.ico"), "&Property", this);

	if (settings->getValue("language") == RU) {

		disableMod->setText(RUS("Отключить мод"));
		enableMod->setText(RUS("Включить мод"));
		removeMod->setText(RUS("Удалить мод"));
		updateModsInfo->setText(RUS("Обновить"));
		modProperty->setText(RUS("Свойства"));
	}

	if (mod->getModState(selectedMod_) == DISABLE) {

		customQMenu->addAction(enableMod);
		customQMenu->addAction(removeMod);

	} else if (mod->getModState(selectedMod_) == ENABLE) {

		customQMenu->addAction(disableMod);
	}

	customQMenu->addAction(updateModsInfo);
	customQMenu->addAction(modProperty);

	customQMenu->popup(ui.modsListWidget->viewport()->mapToGlobal(pos));

	connect(updateModsInfo, &QAction::triggered, this, &EternalModManager::updateModsInfo);
	connect(disableMod, &QAction::triggered, this, &EternalModManager::disableMod);
	connect(enableMod, &QAction::triggered, this, &EternalModManager::enableMod);
	connect(removeMod, &QAction::triggered, this, &EternalModManager::removeMod);
	connect(modProperty, &QAction::triggered, this, &EternalModManager::openModProperty);
}

void EternalModManager::disableMod()
{
	mod->disableMod(selectedMod_);
	plg->removePlugin(mod->getNameEspFileMod(selectedMod_));

	mod->showMods();

	this->updateModsInfo();
	plg->showPluginList();
}

void EternalModManager::enableMod()
{
	mod->enableMod(selectedMod_);
	mod->showMods();

	this->updateModsInfo();
	plg->showPluginList();
}

void EternalModManager::removeMod()
{
	mod->removeMod(selectedMod_);
	mod->showMods();

	this->updateModsInfo();
	plg->showPluginList();
}

void EternalModManager::updateModsInfo()
{
	mod->showMods();

	ui.totalModsAmountLabel->setText(QString::number(mod->getTotalNumberOfMods()));
	ui.installedModsAmountLabel->setText(QString::number(mod->getNumberOfEnabledMods()));
	ui.disabledModsAmountLabel->setText(QString::number(mod->getNumberOfDisabledods()));
}

void EternalModManager::selectMod()
{
	selectedMod_ = ui.modsListWidget->currentItem()->text();
}

void EternalModManager::openModProperty()
{
	ModInfo* inf = new ModInfo(selectedMod_);
	inf->setAttribute(Qt::WA_DeleteOnClose);
	inf->show();
}

void EternalModManager::disableAllPluginsOnToolButtonCliked()
{
	plg->disableAllPlugins();

	updatePluginsInfo();
}

void EternalModManager::enableAllPluginsOnToolButtonCliked()
{
	plg->enableAllPlugins();

	updatePluginsInfo();
}

void EternalModManager::disablePlugin()
{
	plg->disablePlugin(selectedPlugin_);

	updatePluginsInfo();
}

void EternalModManager::selectItemWhenClick()
{
	selectedPlugin_ = ui.pluginListWidget->currentItem()->text();
}

void EternalModManager::enablePlugin()
{
	plg->enablePlugin(selectedPlugin_);

	updatePluginsInfo();
}

void EternalModManager::updatePluginsInfo()
{
	ui.pluginsAmountLabel->setText(QString::number(Plugin::getNumberOfPlugins()));
	ui.disabledPluginsAmountLabel->setText(QString::number(Plugin::getNumberOfPluginsDisabled()));
	ui.activePlguinsAmountLabel->setText(QString::number(Plugin::getNumberOfPluginsIncluded()));

	plg->showPluginList();
}

void EternalModManager::uploadFileDownloadOrder()
{
	QString pathToFile = QFileDialog::getOpenFileName(this,tr("Select a file"), "", tr("Text Files (*.txt)"));

	QFileInfo fileInfo(pathToFile);

	if (pathToFile == nullptr) return;

	if (fileInfo.fileName() != "Plugins.txt") {

		if(settings->getValue("language") == EN) QMessageBox::about(this, "Error!", "The file must have a name Plugin.txt");
		if(settings->getValue("language") == RU) QMessageBox::about(this, "Ошибка!", "Выберите файл с именем Plugin.txt");

		return;
	}

	plg->uploadFileDownloadOrder(pathToFile);
}

void EternalModManager::saveBootOrderFile()
{
	QString pathToFile = QFileDialog::getSaveFileName(this, tr("Select file name"), "", tr("Text Files (*.txt)"));

	if (pathToFile == nullptr) return;

	plg->saveBootOrderFile(pathToFile);
}

void EternalModManager::gameRun()
{
	QString temp = pathToSkyrimSe_ + "\\";

	if (ui.selectLaunchTypeComboBox->currentText() == "Launcher")  temp += "SkyrimSELauncher.exe";
	if (ui.selectLaunchTypeComboBox->currentText() == "EXE")  temp += "SkyrimSE.exe";
	if (ui.selectLaunchTypeComboBox->currentText() == "SKSE")  temp += "skse_loader.exe";

	QProcess* process = new QProcess(this);
	process->startDetached(temp, QStringList());

	if (ui.closeProgramAfterLaunchGameCheckBox->isChecked()) QApplication::quit();
}

void EternalModManager::applySettings()
{
	ui.applySettingsPushButton->setEnabled(false);

	ui.mainTabWidget->setTabEnabled(0, true);
	ui.mainTabWidget->setTabEnabled(1, true);

	if (ui.selectLanugageComboBox->currentText() == "Russian") {

		settings->changeValue("language", RU);
	}

	if (ui.selectLanugageComboBox->currentText() == QString::fromLocal8Bit("Английский")) {

		settings->changeValue("language", EN);
	}

	if (ui.themeComboBox->currentText() == "Dark" || ui.themeComboBox->currentText() == QString::fromLocal8Bit("Темная")) {
		settings->changeValue("theme", DARK);
	}

	if (ui.themeComboBox->currentText() == "Default" || ui.themeComboBox->currentText() == RUS("По умолчанию")) {
		settings->changeValue("theme", WHITE);
	}

	if (ui.selectLaunchTypeComboBox->currentText() == "Launcher") {
		settings->changeValue("launchtype", LAUNCHER);
	}

	if (ui.selectLaunchTypeComboBox->currentText() == "EXE") {
		settings->changeValue("launchtype", EXE);
	}

	if (ui.selectLaunchTypeComboBox->currentText() == "SKSE") {
		settings->changeValue("launchtype", SKSE64);
	}

	if (ui.closeProgramAfterLaunchGameCheckBox->isChecked()) {
		settings->changeValue("closeprogramafterlaunch", ON);
	}

	if (ui.closeProgramAfterLaunchGameCheckBox->checkState() == false) {
		settings->changeValue("closeprogramafterlaunch", OFF);
	}

	QApplication::quit();
	QProcess::startDetached(QApplication::applicationFilePath(), QStringList(), QApplication::applicationDirPath());
}

void EternalModManager::rescanInstalledGames()
{
	this->close();
	GameDefinition* def = new GameDefinition;
	def->setAttribute(Qt::WA_DeleteOnClose);
	def->show();
}

void EternalModManager::setDefaultSettings()
{
	ui.selectLanugageComboBox->setCurrentIndex(0);
	ui.themeComboBox->setCurrentIndex(0);
	ui.selectLaunchTypeComboBox->setCurrentIndex(0);
	ui.closeProgramAfterLaunchGameCheckBox->setCheckState(Qt::CheckState::Unchecked);

	ui.defaultSettingsPushButton->setEnabled(false);
}

void EternalModManager::addMod()
{
	QString pathToMod = QFileDialog::getOpenFileName(this, tr("Select file"), "", tr("Archive Files (*.zip *.7z *.rar)"));

	if (pathToMod == nullptr) return;

	if (mod->isExist(pathToMod)) {

		int result = NULL;

		if(settings->getValue("language") == EN) result = QMessageBox::warning(this, RUS("Attention"), RUS("Do you want to replace mod files?"), QMessageBox::Yes | QMessageBox::Cancel);

		if(settings->getValue("language") == RU) result = QMessageBox::warning(this, RUS("Внимание!"), RUS("Вы хотите заменить файлы мода?"), QMessageBox::Yes | QMessageBox::Cancel);

		if (result == QMessageBox::Cancel) return;
		if (result == QMessageBox::Yes) mod->addMod(pathToMod);

		return;
	}

	mod->addMod(pathToMod);

	this->updateModsInfo();
}

void EternalModManager::movePluginUp()
{
	plg->movePluginUp(selectedPlugin_);
}

void EternalModManager::movePluginDown()
{
	plg->movePluginDown(selectedPlugin_);
}

void EternalModManager::selectLanguage()
{
	ui.applySettingsPushButton->setEnabled(true);
	ui.defaultSettingsPushButton->setEnabled(true);

	ui.mainTabWidget->setTabEnabled(0, false);
	ui.mainTabWidget->setTabEnabled(1, false);
}

void EternalModManager::launchType()
{
	ui.applySettingsPushButton->setEnabled(true);
	ui.defaultSettingsPushButton->setEnabled(true);

	ui.mainTabWidget->setTabEnabled(0, false);
	ui.mainTabWidget->setTabEnabled(1, false);
}

void EternalModManager::selectTheme()
{
	ui.applySettingsPushButton->setEnabled(true);
	ui.defaultSettingsPushButton->setEnabled(true);

	ui.mainTabWidget->setTabEnabled(0, false);
	ui.mainTabWidget->setTabEnabled(1, false);
}

void EternalModManager::closePorgramAfterLaunch()
{
	ui.applySettingsPushButton->setEnabled(true);
	ui.defaultSettingsPushButton->setEnabled(true);

	ui.mainTabWidget->setTabEnabled(0, false);
	ui.mainTabWidget->setTabEnabled(1, false);
}

void EternalModManager::gameSelect()
{
	this->close();

	GameSelection* game = new GameSelection;
	game->setAttribute(Qt::WA_DeleteOnClose);
	game->show();
}

void EternalModManager::aboutProgram()
{
	AboutProgram* about = new AboutProgram;
	about->setAttribute(Qt::WA_DeleteOnClose);
	about->show();
}

void EternalModManager::recountPlguins()
{
	int result = NULL;

	if (settings->getValue("language") == EN) result = QMessageBox::warning(this, RUS("Attention"), RUS("Download order can be changed"), QMessageBox::Yes | QMessageBox::Cancel);

	if (settings->getValue("language") == RU) result = QMessageBox::warning(this, RUS("Внимание!"), RUS("Порядок загрузки может быть изменен"), QMessageBox::Yes | QMessageBox::Cancel);

	if (result == QMessageBox::Cancel) return;
	if (result == QMessageBox::Yes) plg->recountPlguins(pathToSkyrimSe_);
}

void EternalModManager::setRussianLanguage()
{
	ui.selectLanugageGroupBox->setTitle(RUS("Язык"));
	ui.selectLanugageComboBox->setCurrentIndex(1);
	ui.selectLanugageComboBox->setItemText(0, RUS("Английский"));
	ui.selectLanugageComboBox->setItemText(1, RUS("Русский"));

	ui.launchTypeGroupBox->setTitle(RUS("Тип запуска"));

	ui.themeGroupBox->setTitle(RUS("Тема"));
	ui.themeComboBox->setItemText(0, RUS("По умолчанию"));
	ui.themeComboBox->setItemText(1, RUS("Темная"));

	ui.generalGroupBox->setTitle(RUS("Общие"));
	ui.closeProgramAfterLaunchGameCheckBox->setText(RUS("Закрывать программу после запуска игры"));

	ui.applySettingsPushButton->setText(RUS("Применить"));
	ui.defaultSettingsPushButton->setText(RUS("По умолчанию"));

	ui.totalPluginsLabel->setText(RUS("Общее количество плагинов"));
	ui.disabledPluginsLabel->setText(RUS("Отключенных плагинов"));
	ui.activePluginsLabel->setText(RUS("Включенных плагинов"));

	ui.mainTabWidget->setTabText(0, RUS("Плагины"));
	ui.mainTabWidget->setTabText(1, RUS("Моды"));
	ui.mainTabWidget->setTabText(2, RUS("Настройки"));

	ui.movingPluginUpToolButton->setToolTip(RUS("Переместить плагин вверх"));
	ui.movingPluginDownToolButton->setToolTip(RUS("Переместить плагин вниз"));
	ui.disablingAllPluginsToolButton->setToolTip(RUS("Отключить все плагины"));
	ui.inclusionAllPluginsToolButton->setToolTip(RUS("Включить все плагины"));
	ui.uploadFileDownloadOrderTtoolButton->setToolTip(RUS("Загрузить файл порядка загрузки"));
	ui.saveLoadingOrderFileToolButton->setToolTip(RUS("Сохранить файл порядка загрузки"));
	ui.gameRunToolButton->setToolTip(RUS("Запустить игру"));

	ui.rescanGameToolButton->setToolTip(RUS("Пересканировать установленные игры"));

	ui.totalModsLabel->setText(RUS("Общее количество модов"));
	ui.installedModsLabel->setText(RUS("Установленных модов"));
	ui.disabledModsLabel->setText(RUS("Отключенных модов"));
	ui.addingpluginToolButton->setToolTip(RUS("Добавить мод"));

	ui.gameSelectToolButton->setToolTip(RUS("Выбрать игру"));
	ui.aboutToolButton->setToolTip(RUS("О программе"));

	ui.recountPluginsToolButton->setToolTip(RUS("Пересчитать плагины (порядок загрузки может быть изменен)"));
}

void EternalModManager::setDarkTheme()
{
	ui.themeComboBox->setCurrentIndex(1);
	this->setStyleSheet("color: rgb(255, 255, 255);\nbackground-color: rgb(46, 47, 48);");
	ui.mainTabWidget->setStyleSheet("color: rgb(50, 0, 70)");
	ui.selectLanugageGroupBox->setStyleSheet("color: rgb(255, 255, 255)");
	ui.selectLanugageComboBox->setStyleSheet("color: rgb(255, 255, 255)");

	ui.launchTypeGroupBox->setStyleSheet("color: rgb(255, 255, 255)");
	ui.selectLaunchTypeComboBox->setStyleSheet("color: rgb(255, 255, 255)");

	ui.themeGroupBox->setStyleSheet("color: rgb(255, 255, 255)");
	ui.themeComboBox->setStyleSheet("color: rgb(255, 255, 255)");

	ui.generalGroupBox->setStyleSheet("color: rgb(255, 255, 255)");
	ui.closeProgramAfterLaunchGameCheckBox->setStyleSheet("color: rgb(255, 255, 255)");

	ui.applySettingsPushButton->setStyleSheet("color: rgb(255, 255, 255)");
	ui.defaultSettingsPushButton->setStyleSheet("color: rgb(255, 255, 255)");
}


void EternalModManager::setCustomButtonStyle(QToolButton& button, QString imagePath, QString toolTip)
{
	QSize iconSize(38, 38);
	QPixmap map(imagePath);
	QIcon icon(map);
	button.setIcon(icon);
	button.setIconSize(iconSize);
	button.setStyleSheet("QToolButton { background-color: transparent; }");
	button.setToolTip(toolTip);
}