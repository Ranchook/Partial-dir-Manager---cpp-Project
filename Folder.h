#pragma once
#include "ADFile.h"
#include "DataFile.h"
#include <iostream>
#include <typeinfo>
#include <cassert>

class Folder : public ADFile
{
	ADFile** files;
	int arrSize;
	string filePath;
public:
	
	~Folder();
	static Folder *root;
	Folder(string, string path = "root");
	string getFullPath() const;
	void addFileToArray(ADFile *);
	Folder(Folder &, const string); //copy constructor
	void mkFile(string, string);
	void mkDir(string);
	void dir();
	static Folder* cd(string);
	virtual bool operator ==(Folder &);
	friend bool fc(Folder&, const string, const string);
	bool check(ADFile*, ADFile*);
	ADFile* searchFolder(Folder*, const string);
	virtual void show();
	ADFile* findFile(string, Folder*);
};