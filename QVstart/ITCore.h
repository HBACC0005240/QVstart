#pragma once

#include <QObject>

class ITCore : public QObject
{
	Q_OBJECT

public:
	ITCore();
	~ITCore();
};

class ITTable
{
public:
	ITTable();
	~ITTable();
};
class ITRecord
{
public:
	ITRecord();
	~ITRecord();
};