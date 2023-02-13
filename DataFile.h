#pragma once
#include <iostream>
#include "ADFile.h"


class DataFile : public ADFile
{
	string data;
	

public:
	DataFile(string, string);
	virtual bool operator == (const DataFile );
	float getSize();
	virtual void show();
};

