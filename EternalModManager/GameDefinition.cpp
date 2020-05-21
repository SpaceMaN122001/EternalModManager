#include "GameDefinition.h"

GameDefinition::GameDefinition(QWidget *parent) : QWidget(parent)
{
	ui.setupUi(this);

	this->setWindowIcon(QIcon(":/EternalModManager/Resources/eternal.png"));
	this->setWindowTitle("Game definition");
	this->setFixedSize(QSize(673, 224));

	ui.applyPathSkyrimSeToolButton->hide();
	ui.applyPathSkyrimLeToolButton->hide();
	ui.applyPathF4ToolButton->hide();

	this->setCustomButtonStyle(*ui.applyPathSkyrimSeToolButton, ":/EternalModManager/Resources/ok.png", "Apply path to Skyrim SE");
	this->setCustomButtonStyle(*ui.applyPathSkyrimLeToolButton, ":/EternalModManager/Resources/ok.png", "Apply path to Skyrim LE");
	this->setCustomButtonStyle(*ui.applyPathF4ToolButton, ":/EternalModManager/Resources/ok.png", "Apply path to Fallout 4");

	this->setCustomButtonStyle(*ui.selectPathToSkyrimSeToolButton, ":/EternalModManager/Resources/folder.png", "Select path to Skyrim SE");
	this->setCustomButtonStyle(*ui.selectPathToSkyrimLeToolButton, ":/EternalModManager/Resources/folder.png", "Select path to Skyrim LE");
	this->setCustomButtonStyle(*ui.selectPathToF4ToolButton, ":/EternalModManager/Resources/folder.png", "Select path to Fallout 4");

	connect(ui.scanPushButton, SIGNAL(clicked()), this, SLOT(ScanGame()));
	connect(ui.okPushButton, SIGNAL(clicked()), this, SLOT(savePathToGame()));
	connect(ui.quitPushButton, SIGNAL(clicked()), this, SLOT(programQuit()));
	connect(ui.selectPathToSkyrimSeToolButton, SIGNAL(clicked()), this, SLOT(selectPathToSkyrimSE()));

	settings = new SSettings("Eternal mod manager");
	settings->setValue("skyrimse", pathToSkyrimSe_);
	settings->setValue("skyrimle", pathToSkyrimLe_);
	settings->setValue("f4", pathToF4_);

	pathToSkyrimSe_ = SSettings::getKeyValueS("Eternal mod manager", "skyrimse");

	ui.skyrimSeFilesLineLabel->setText(SSettings::getKeyValueS("Eternal mod manager", "skyrimse"));

	ui.skyrimLeLogoLabel->hide();
	ui.skyrimLeLabel->hide();
	ui.skyrimLeFilesLineLabel->hide();
	ui.selectPathToSkyrimLeToolButton->hide();
	ui.progressBarSkyrimLe->hide();

	ui.F4LogoLabel->hide();
	ui.F4Label->hide();
	ui.F4FilesLinelabel->hide();
	ui.progressBarF4->hide();
	ui.selectPathToF4ToolButton->hide();

	ui.selectScanGameComboBox->removeItem(1);
	ui.selectScanGameComboBox->removeItem(1);

	if (SSettings::getKeyValue("Eternal mod manager", "language") == RU) {

		ui.scanPushButton->setText(RUS("�����������"));
		ui.quitPushButton->setText(RUS("�����"));

		ui.applyPathSkyrimSeToolButton->setToolTip(RUS("��������� ���� �� Skyrim SE"));
		ui.selectPathToSkyrimSeToolButton->setToolTip(RUS("������� ���� �� Skyrim SE"));

		this->setWindowTitle(RUS("����������� ����"));
	}

	ui.skyrimSeLogoLabel->setPixmap(QPixmap(":/EternalModManager/Resources/skyrimse2.png"));
}

void GameDefinition::programQuit()
{
	this->close();
}

void GameDefinition::savePathToGame()
{
	settings->changeValue("skyrimse", pathToSkyrimSe_);
	settings->changeValue("skyrimle", pathToSkyrimLe_);
	settings->changeValue("f4", pathToF4_);

	this->close();

	GameSelection* game = new GameSelection;
	game->setAttribute(Qt::WA_DeleteOnClose);
	game->show();
}

void GameDefinition::selectPathToSkyrimSE()
{
	QString pathToSkyrimSe = QFileDialog::getExistingDirectory(this, tr("Select a folder"));
	if (pathToSkyrimSe == nullptr) return;

	if (!this->isGameExist(pathToSkyrimSe)) {

		if (SSettings::getKeyValue("Eternal mod manager", "language") == EN) QMessageBox::about(this, RUS("Attention"), RUS("The folder you selected is not Skyrim SE"));
		if (SSettings::getKeyValue("Eternal mod manager", "language") == RU) QMessageBox::about(this, RUS("��������!"), RUS("��������� ���� ����� �� �������� Skyrim SE"));

		return;
	}

	ui.okPushButton->setEnabled(true);

	ui.skyrimSeFilesLineLabel->setText(pathToSkyrimSe);
	pathToSkyrimSe_ = pathToSkyrimSe;
}

void GameDefinition::ScanGame()
{
	if (ui.selectScanGameComboBox->currentText() == SKYRIMSE) {

		pathToSkyrimSe_ = this->getPathToGame(*ui.skyrimSeFilesLineLabel, "Special Edition", "Skyrim", "SkyrimSELauncher.exe", "SkyrimSE.exe");
		ui.skyrimSeFilesLineLabel->setText(pathToSkyrimSe_);
		ui.okPushButton->setEnabled(true);
		if (pathToSkyrimSe_ == "Not found") { QMessageBox::about(this, "Atention", "Game not found"); pathToSkyrimSe_ = nullptr; return; }
	}
}

QString GameDefinition::getPathToGame(QLabel& line, QString parameter1, QString parameter2, QString parameter3, QString parameter4)
{
	QFileInfoList drives = QDir::drives();

	for each (QFileInfo info in drives)
	{

		//QDirIterator it(info.path(), QDirIterator::Subdirectories);
		QDirIterator it(info.filePath(), QDirIterator::Subdirectories);

		while (it.hasNext()) {

			QFileInfo info(it.next());
			QFileInfo infoFile(info.fileName());

			if (info.fileName() != ".." && info.fileName() != '.' && infoFile.suffix() == nullptr) {

				QString folder = info.absolutePath();
				QString folderName = info.fileName();

				if (folderName.contains(parameter1) || folderName.contains(parameter2)) {

					QDir dir(folder);

					QFileInfoList fileList = dir.entryInfoList();

					foreach(QFileInfo file, fileList)
					{
						if (file.fileName() == parameter3 || file.fileName() == parameter4) return folder;
					}
				}
			}

			line.setText(info.absolutePath());
			line.repaint();
			ui.progressBarSkyrimSe->repaint();
			this->repaint();
		}
	}

	return "Not found";
}

bool GameDefinition::isGameExist(QString pathToGame)
{
	QDir dir(pathToGame);

	QFileInfoList modList = dir.entryInfoList();

	int i = NULL;

	foreach(QFileInfo mod, modList)
	{
		if (mod.suffix() != nullptr && mod.fileName() != ".." && mod.fileName() != '.') {

			
			if (mod.fileName() == "SkyrimSELauncher.exe") {
				qDebug() << mod.fileName() << endl;
				i++;
			}

			if (mod.fileName() == "SkyrimSE.exe") {
				qDebug() << mod.fileName() << endl;
				i++;
			}

			if (mod.fileName() == "unins000.exe") {
				qDebug() << mod.fileName() << endl;
				i++;
			}

		}
	}

	qDebug() << i << endl;
	if (i >= 2) return true;

	return false;
}

void GameDefinition::setCustomButtonStyle(QToolButton& button, QString imagePath, QString toolTip)
{
	QSize iconSize(16, 16);
	QPixmap map(imagePath);
	QIcon icon(map);
	button.setIcon(icon);
	button.setIconSize(iconSize);
	button.setStyleSheet("QToolButton { background-color: transparent; }");
	button.setToolTip(toolTip);
}


GameDefinition::~GameDefinition()
{
}
