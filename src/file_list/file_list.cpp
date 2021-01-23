#include <windows.h>
#include <file_list/file_list.h>

void CFileList::ClearList(){
	memset(CFileList::Path,0,sizeof(CFileList::Path));
	memset(CFileList::Address,0,sizeof(CFileList::Address));
	CFileList::Path_Pointer=0;
	CFileList::Address_Pointer=0;
}

void CFileList::ListUp_File(char Path[256],char Condition[8]){
	WIN32_FIND_DATA fd;
	HANDLE hFind;
	BOOL bRet=TRUE;
	char SubFile[256]={0};
	strcpy_s(SubFile,sizeof(SubFile),Path);
	strcat_s(SubFile,sizeof(SubFile),Condition);
	hFind= FindFirstFile(SubFile,&fd);
    while(hFind != INVALID_HANDLE_VALUE && bRet){
		if(strcmp(fd.cFileName,".")&&strcmp(fd.cFileName,"..")){
			if(!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)){
				strcat_s(CFileList::Path,sizeof(CFileList::Path),"\n");
				strcat_s(CFileList::Path,sizeof(CFileList::Path),Path);
				strcat_s(CFileList::Path,sizeof(CFileList::Path),"/");
				strcat_s(CFileList::Path,sizeof(CFileList::Path),fd.cFileName);
			}
		}
		bRet=FindNextFile(hFind,&fd);
	}
	FindClose(hFind);
	while(CFileList::Path[CFileList::Path_Pointer]!='\0'){
		if(CFileList::Path[CFileList::Path_Pointer]=='\n'){
			CFileList::Address[CFileList::Address_Pointer]=CFileList::Path_Pointer+1;
			CFileList::Address_Pointer++;
		}
		CFileList::Path_Pointer++;
	}
}

void CFileList::ListUp_Dir(char Path[256]){
	WIN32_FIND_DATA fd;
	HANDLE hFind;
	BOOL bRet=TRUE;
	char SubDir[256]={0};
	strcpy_s(SubDir,sizeof(SubDir),Path);
	strcat_s(SubDir,sizeof(SubDir),"/*.*");
	hFind= FindFirstFile(SubDir,&fd);
    while(hFind != INVALID_HANDLE_VALUE && bRet){
		if(strcmp(fd.cFileName,".")&&strcmp(fd.cFileName,"..")){
			if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
				char SubDir_2[256]={0};
				strcpy_s(SubDir_2,sizeof(SubDir_2),Path);
				strcat_s(SubDir_2,sizeof(SubDir_2),"/");
				strcat_s(SubDir_2,sizeof(SubDir_2),fd.cFileName);
				CFileList::ListUp(SubDir_2);
			}
		}
		bRet=FindNextFile(hFind,&fd);
	}
	FindClose(hFind);
}

void CFileList::ListUp(char Path[256]){
	CFileList::ListUp_File(Path,"/*.fldn");
	CFileList::ListUp_Dir(Path);
}

void CFileList::FilePath(int Source,char *Path){
	int EndPath=0;
	for(int i=0;i<256&&EndPath==0;i++){
		if(CFileList::Path[CFileList::Address[Source]+i]=='\n'){
			Path[i]='\0';
			EndPath=1;
		}
		else {
			Path[i]=CFileList::Path[CFileList::Address[Source]+i];
		}
	}
}

int CFileList::HowManyFiles(){
	return CFileList::Address_Pointer;
}