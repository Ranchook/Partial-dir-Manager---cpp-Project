# partial-dir-manager---cpp-Project
The 5th class project in cpp course: Partial realization that simulates a directory manager in the command line.

This realization supports the following commands:

1. cd [folderName] - change directory.
2. mkdir [newFolderName] - create new folder in the current location (no need to give the full path).
3. echo [some text] > [dataFileName] - create a new data file in the current folder that contains the text given in [some text] (no need to give the full path).
4. dir - display every file and folder in the current folder.
5. FC [path_to_file] [path_to_file] - compare the content of two files (folder or data files). Needs a either full path or a partial path.
   A partial path starts with '\' and will place the folder relatively to the current folder. 
