#include "DataFile.h"

//constructor
DataFile::DataFile(string name, string fdata = '\0') : ADFile(name)
{
	data = fdata;
}

//comparea data
bool DataFile::operator==(const DataFile otherFile)
{
	if (!otherFile.data.compare(this->data))
		return true;
	return false;
}

float DataFile:: getSize()
{
	return data.length() + 1;
}

//print methhod
void DataFile::show()
{
	cout << left << setw(20) << setfill(' ') << this->getTime();
	cout << left << setw(7) << setfill(' ') << " ";
	cout << left << setw(4) << setfill(' ') << fixed << setprecision(2) << (this->getSize()) / 1000 << " KB ";
	cout << left << setw(32) << setfill(' ') << this->getFileName() << endl;
}