#include "LineCounterForCpp.h"

LineCounterForCpp::LineCounterForCpp(const string& filename):
	LineCounterBase(filename),
	mIsStillBlockComment(false),
	mIsStillLineComment(false)
{
}

bool LineCounterForCpp::isEmptyLine(const string& line)
{
	if (true == mIsStillLineComment || true == mIsStillBlockComment)
	{
		//对于使用行分隔符的情况，
		//我认为这个还是注释行，而不是空白行
		return false;
	}

	for(int i = 0 ; i < line.size() ; i ++)
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		{
			return false;
		}
	}
	return false;
}

bool LineCounterForCpp::isCommentLine(const string& line)
{
	if (true == mIsStillLineComment )
	{
		//对于使用行分隔符的情况，
		//我认为这个还是注释行，而不是空白行
		return true;
	}
	bool ret = false;
	for(int i = 0 ; i < line.size() ; i ++)
	{

	}
	return ret;	
}
