#pragma once
#include <ctime>
#include <string>
#include <iomanip>
using namespace std;
 
class ADFile
{

protected:
	string fileName;
	tm *lastUpdateTime;

public:
	ADFile(string);
	void setFileName(const string);
	string getFileName();
	void setTime();
	string getTime() const;
	virtual bool operator == (ADFile *);
	virtual void show() {};
};