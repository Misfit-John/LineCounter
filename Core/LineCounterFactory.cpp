#include "LineCounterFactory.h"
#include "LineCounterForCpp.h"

LineCounterFactory::LineCounterFactory ()
{
}

LineCounterFactory::~LineCounterFactory ()
{
}

void LineCounterFactory::init()
{
	mSuffixMap["cpp"] = eFileTypeCPP;
	mSuffixMap["c"] = eFileTypeC;
	mSuffixMap["m"] = eFileTypeObjC;
	mSuffixMap["mm"] = eFileTypeMixCppObjC;
}

LineCounterFactory* LineCounterFactory::getInstance()
{
	LineCounterFactory* instance = NULL;
	if (NULL == instance)
	{
		instance = new LineCounterFactory();
		instance->init();
	}
	return instance;
}
LineCounterBase* LineCounterFactory::getLineCounter(const string& fileName)
{
	FileType fileType = checkFileType(fileName);
	LineCounterBase* ret = NULL;
	switch(fileType)
	{
		case eFileTypeC:
		case eFileTypeCPP:
		case eFileTypeMixCppObjC:
		case eFileTypeObjC:
			ret = new LineCounterForCpp(fileName);
			break;
		default:
			break;
	}
	return ret;
}

FileType LineCounterFactory::checkFileType(const string& fileName)
{
	string sufix = getSuffix(fileName);
	auto it = mSuffixMap.find(sufix);
	if (mSuffixMap.end() != it)
	{
		return it->second;
	}
	return eFileTypeUnknow;
}

string LineCounterFactory::getSuffix(const string& input)
{
	string sufix = "";
	int i = 0;
	for(i = input.size() - 1 ; i >= 0; i-- )
	{
		if (input[i] == '.')
		{
			break;
		}
	}
	for(i = i+1; i < input.size(); i++)
	{
		sufix += input[i];	
	}
	return sufix;
}
