#ifndef FILELIST_H
#define FILELIST_H

class CFileList{
public:
	static const int PATH_MAX=32767;
	static const int ADDRESS_MAX=1023;
	void ClearList();
	void ListUp_File(char Path[256],char Condition[15]);
	void ListUp_Dir(char Path[256]);
	void ListUp(char Path[256]);
	void FilePath(int Source,char *Path);
	int HowManyFiles();
private:
	char Path[PATH_MAX];
	int Address[ADDRESS_MAX];
	int Path_Pointer;
	int Address_Pointer;
};

extern CFileList FileList;

#endif
