#ifndef FILETYPECHECK_H
#define FILETYPECHECK_H

#include <map>
#include <string>
using namespace std;

class LineCounterBase;

enum FileType
{
	eFileTypeUnknow = 0,		//put this type at the begining

	eFileTypeC,					//.c
	eFileTypeCPP,				//.cpp
	eFileTypeObjC,				//.m
	eFileTypeMixCppObjC,		//.mm
};

class LineCounterFactory {
public:
	static LineCounterFactory* getInstance();
	virtual ~LineCounterFactory ();

	LineCounterBase* getLineCounter(const string& fileName);	
private:
	LineCounterFactory ();
	FileType checkFileType(const string& fileName);

	void init();
	string getSuffix(const string& input);

private:
	map<string,FileType> mSuffixMap;	
};

#endif /* end of include guard: FILETYPECHECK_H */
