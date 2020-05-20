#include "SDir.h"

SDir::SDir()
{
}


SDir::~SDir()
{
}

void SDir::copyFolder(QString from, QString to)
{
	QDir dir(from);
	if (!dir.exists())
		return;

	foreach(QString folderName, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
	{
		QString dst_path = to + QDir::separator() + folderName;
		dir.mkpath(dst_path);
		copyFolder(from + QDir::separator() + folderName, dst_path);
	}

	foreach(QString fileName, dir.entryList(QDir::Files))
	{
		QFile::copy(from + QDir::separator() + fileName, to + QDir::separator() + fileName);
	}
}
