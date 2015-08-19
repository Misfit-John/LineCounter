#ifndef FILETYPECHECK_H
#define FILETYPECHECK_H

#include <map>
#include <string>
using namespace std;

enum FileType
{
	eFileTypeUnknow = 0,		//put this type at the begining

	eFileTypeC,					//.c
	eFileTypeCPP,				//.cpp
	eFileTypeObjC,				//.m
	eFileTypeMixCppObjC,		//.mm
};

class FileTypeCheck {
public:
	static FileTypeCheck* getInstance()
	{
		FileTypeCheck* instance = NULL;
		if (NULL == instance)
		{
			instance = new FileTypeCheck();
			instance->init();
		}
		return instance;
	}
	virtual ~FileTypeCheck ();

	FileType checkFileType(const string& fileName);

private:
	FileTypeCheck ();
	FileTypeCheck operator =(const FileTypeCheck& rhl);	

	void init();
	string getSuffix(const string& input);

private:
	map<string,int> mSuffixMap;	
};

#endif /* end of include guard: FILETYPECHECK_H */
