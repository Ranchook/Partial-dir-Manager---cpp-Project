#include "ADFile.h"
#define LOST throw "bad input!"

ADFile::ADFile(string name)
{
	setFileName(name);
	setTime();
}

void ADFile::setFileName(const string name)
{ 	
	if (name == "") LOST;
	fileName = new char[name.length() + 1];
	fileName = name;
}

string ADFile::getFileName()
{
	return fileName;
}

void ADFile::setTime()
{
	// current date/time based on current system  
	time_t now = time(0);
	lastUpdateTime = localtime(&now);
}

string ADFile::getTime() const
{
	char buf[80];
	strftime(buf, sizeof(buf), "%d/%m/%Y %X", lastUpdateTime);
	return buf;
}

//compare files by name
bool ADFile::operator==(ADFile* other)
{
	if(this->fileName == other->fileName)
		return true;
	return false;
}