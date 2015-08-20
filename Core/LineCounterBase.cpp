#include "LineCounterBase.h"
#include "LineNumberCollector.h"
#include <sstream>
#include <fstream>
#include "Log.h"
using namespace std;

LineCounterBase::LineCounterBase(const string& fileName):
	mFileName(fileName),
	mSumLineNum(0),
	mEmptyLineNum(0),
	mCommentLineNum(0),
	mUsefulLineNum(0)
{
}

LineCounterBase::~LineCounterBase ()
{}

void LineCounterBase::countLine()
{
	ifstream inFile(mFileName);
	string lineString;
	while(getline(inFile,lineString))
	{
		printf("line:%s\n",lineString.c_str());
		if (true == isCommentLine(lineString))
		{
			LOG("is comment");
			addLineNum(eLineTypeCommentLine);
		}
		if(true == isEmptyLine(lineString))
		{
			LOG("is empty");
			addLineNum(eLineTypeEmptyLine);	
		}
		if(true == isCodeLine(lineString))
		{
			LOG("is code");
			addLineNum(eLineTypeUsefuleLine);	
		}
		addLineNum(eLineTypeSumLine);
	}

	LineNumberCollector::getInstance()->addLineNum(eLineTypeCommentLine, getCommentLineNum());
	LineNumberCollector::getInstance()->addLineNum(eLineTypeEmptyLine, getEmptyLineNum());
	LineNumberCollector::getInstance()->addLineNum(eLineTypeUsefuleLine, getCodeLineNum());
	LineNumberCollector::getInstance()->addLineNum(eLineTypeSumLine, getTotalLineNum());

}

unsigned int LineCounterBase::getTotalLineNum()
{
	return mSumLineNum;
}

unsigned int LineCounterBase::getEmptyLineNum()
{
	return mEmptyLineNum;
}

unsigned int LineCounterBase::getCommentLineNum()
{
	return mCommentLineNum;
}

unsigned int LineCounterBase::getCodeLineNum()
{
	return mUsefulLineNum;
}

void LineCounterBase::addLineNum(LineType lineType)
{
	switch(lineType)
	{
		case eLineTypeEmptyLine:
			mEmptyLineNum++;
			break;
		case eLineTypeCommentLine:
			mCommentLineNum++;
			break;
		case eLineTypeUsefuleLine:
			mUsefulLineNum++;
			break;
		case eLineTypeSumLine:
			mSumLineNum ++;
			break;
		default:
			return;	
	}
}

bool LineCounterBase::isEmptyChar(const char input)
{
	switch(input)
	{
		case '\t':
		case ' ':
		case '\n':
			return true;
		default:
			return false;	
	}
}
