#pragma once
#include <QDir>

class SDir : public QDir
{
public:
	SDir();
	~SDir();
	static void copyFolder(QString from, QString to);
};

