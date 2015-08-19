#include "LineCounterBase.h"
#include "LineNumberCollector.h"
#include <sstream>
#include <fstream>
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
		if (true == isCommentLine(lineString))
		{
			addLineNum(eLineTypeCommentLine);
		}
		else if(true == isEmptyLine(lineString))
		{
			addLineNum(eLineTypeEmptyLine);	
		}
		else
		{
			addLineNum(eLineTypeUsefuleLine);	
		}
	}

	LineNumberCollector::getInstance()->addLineNum(eLineTypeCommentLine, getCodeLineNum());
	LineNumberCollector::getInstance()->addLineNum(eLineTypeEmptyLine, getEmptyLineNum());
	LineNumberCollector::getInstance()->addLineNum(eLineTypeUsefuleLine, getCodeLineNum());
	LineNumberCollector::getInstance()->changeCalculatingFileNum(-1);

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
		default:
			return;	
	}
	mSumLineNum ++;
}
