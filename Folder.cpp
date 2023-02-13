#include "Folder.h"

#define ERROR throw "file already exists!"
#define LOST throw "bad input!"
#define FOL dynamic_cast<Folder*> 
#define DAT dynamic_cast<DataFile*> 
#define SIGN char '\\'

Folder* Folder::root = new Folder("root", "root");

//destructor
Folder::~Folder()
{
	for (int i = 0; i < arrSize; ++i)
	{
		DataFile* tmp2 = dynamic_cast<DataFile*>(files[i]);
		if (tmp2) {
			delete tmp2;
			tmp2 = nullptr;
			continue;
		}

		Folder* tmp = dynamic_cast<Folder*>(files[i]);
		if (tmp) {
			delete tmp;
			tmp = nullptr;
		}
	}
	delete[] files;
	files = nullptr;
}

//constructor
Folder::Folder(string fileName, string path):ADFile(fileName)
{
	this->filePath = path;
	arrSize = 0;
}

string Folder::getFullPath()const
{
	return filePath;
}

void Folder::addFileToArray(ADFile *f)
{
	int i;
	if (arrSize == 0) //if folder empty
	{
		files = new ADFile*[1];
		files[0] = f;
		arrSize++;
	}
	else
	{
		ADFile** temp = new ADFile*[arrSize + 1]; // create new array of files
		for (i = 0; i < arrSize; i++)
			temp[i] = files[i];
		delete[] files; // delete old array
		temp[i] = f;
		files = temp;
		arrSize++;
	}
}

//copy constructor
Folder::Folder(Folder &f, const string path) : ADFile(f.getFileName())
{
	this->filePath = path;
	this->arrSize = 0;
	for (int i = 0; i < f.arrSize; i++) // copy file by file
		this->addFileToArray(f.files[i]);
}

void Folder::mkFile(string fname, string fdata)
{
	try {
		int i;
		for (i = 0; i < arrSize; i++) // checking if file already exists
			if (fname == files[i]->getFileName()) ERROR; // throw error
		DataFile *temp = new DataFile(fname, fdata);
		addFileToArray(temp);
	}
	catch (const char* eMsg)
	{cout << eMsg << endl;}
}

void Folder::mkDir(string fname)
{
	string nPath;
	try {
		int i;
		for (i = 0; i < arrSize; i++)// checking if file already exists
			if (fname == files[i]->getFileName()) ERROR;	// throw error
		nPath = this->getFullPath().append("\\").append(fname); // saving new file path
		Folder *temp = new Folder(fname, nPath);
		addFileToArray(temp);
	}
	catch (const char* eMsg)
	{cout << eMsg << endl;}
}

void Folder::dir()
{
	if (this->arrSize == 0)
	{
		cout << "this folder is empty!" << endl;
		return;
	}
	
	ADFile* temp;
	cout << "Files in directory " << this->getFileName() << ":" << endl;
	for (int i = 0; i < this->arrSize; i++)
	{
		if (temp = FOL (this->files[i])) // if file is folder
			temp->show();
		else if(temp = DAT(this->files[i])) // else file is data file
			temp->show();
	}
}

void Folder::show() // Folder print method
{
	cout << left << setw(20) << setfill(' ') << this->getTime();
	cout << left << setw(7) << setfill(' ') << "<DIR>";
	cout << left << setw(8) << setfill(' ') << " ";
	cout << left << setw(30) << this->getFileName() << endl;
}

Folder * Folder::cd(string path)
{
	Folder* rootTemp = root ,*temp1;
	
	char sign = '\\';
	int lastSlash = path.find_last_of(sign); // position of last slash
	string wantedFolder = path.substr(lastSlash + 1); // name of wanted folder
	int slashNo = count(path.begin(), path.end(), '\\'); // number of slashes in file path
	
	//finding and seperating folder names in path
	int pos = 0;
	string tempPath = path;
	string *fnames = new string[slashNo+1]; // array of folder names in path
	int i = 0;
	if (slashNo != 0) // if wanted folder is inside C: or D:
	{
		while ((pos = tempPath.find(sign)) != std::string::npos) // search while not in end of string
		{
			fnames[i] = tempPath.substr(0, pos); // adding name to folder names array
			tempPath.erase(0, pos + sizeof(sign));
			i++;
		}
		fnames[i] = wantedFolder; //adding wanted folder to last place of array
	}
	
	else // choosing between C: or D:
	{
		temp1 = FOL(rootTemp->searchFolder(rootTemp, wantedFolder));
		if (!temp1) LOST;
		return temp1;
	}
	
	//choosing C: or D: to search in
	if (fnames[0] == "C:")
		temp1 = FOL(rootTemp->files[0]);
	else if(fnames[1] == "D:")
		temp1 = FOL(rootTemp->files[1]);
	else LOST;
	
	//choosing sub-folder
	for (i = 1; i <= slashNo; i++)
	{
		for (int j = 0; j < temp1->arrSize; j++)
		{
			if (temp1->files[j]->getFileName() == fnames[i]) // comparing file names to names of folders in file path
				temp1 = FOL(temp1->files[j]);
		}
	}
	delete[] fnames; // delete names array
	return temp1;
}

bool Folder::operator==(Folder &f)
{
	ADFile *temp1, *temp2;

	if (this->arrSize != f.arrSize) return false; //if different size folders aren't equal
	for (int i = 0; i < arrSize; i++)
	{
		if (f.files[i]->operator==(this->files[i])) // compare by name
		{
			temp1 = f.files[i];
			temp2 = this->files[i];
			if (f.check(temp1, temp2)) continue; // if files are equal continue check
			else return false;
		}
	}
	return true;
}

bool Folder::check(ADFile *temp1, ADFile *temp2)
{
	if (FOL(temp1)) // if file#1 is folder
	{
		if (FOL(temp2))// check if file #2 is folder
			return (FOL(temp1)->operator==(*FOL(temp2))); //compare them
		
	}
	if (DAT(temp1))	//if file#1 is data file
	{
		if (DAT(temp2)) // check if file #2 is data file
			return(DAT(temp1)->operator==(*DAT(temp2))); // compare them
	}
	return false; // files are different types
}

ADFile * Folder::searchFolder(Folder *f, const string fname)
{
	for (int i = 0; i < f->arrSize; i++)
	{
		if (f->files[i]->getFileName() == fname)//search in folder by name
			return f->files[i];
	}
	return nullptr;
}

bool fc(Folder &currentDir, const string source, const string dest)
{
	if (source == dest) // if enterd same path
	{
		cout << "enterd same path";
		return true;
	}

	ADFile *temp1, *temp2;
	temp1 = currentDir.findFile(source, &currentDir); // find wanted file
	if (!temp1) LOST;
	temp2 = currentDir.findFile(dest, &currentDir); // find wanted file
	if (!temp2) LOST;
	return currentDir.check(temp1, temp2); //return result of comparison
}

ADFile* Folder::findFile(string str, Folder* curr)//search file by path
{
	if (str[0] == '\\') // if file starts with '\'
	{
		string temp = curr->getFullPath(); // add full path of file
		temp.append(str); // delete root name
		str = temp.substr(5);
	}
	
	Folder *tempF;
	char sign = '\\';
	string tempStr, tempName;
	int tempPos = str.find_last_of(sign);	// position of last \ in string (before the file)
	tempName = str.substr(tempPos + 1);	// name of file/folder in question
	tempStr = str.substr(0, tempPos);	// folder containing file/folder in question
	tempF = Folder::cd(tempStr);	// poiniting to folder containing file in question
	return (tempF->searchFolder(tempF, tempName)); //returning file in question
}