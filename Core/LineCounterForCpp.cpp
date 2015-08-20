#include "LineCounterForCpp.h"
#include "Log.h"
LineCounterForCpp::LineCounterForCpp(const string& filename):
	LineCounterBase(filename),
	mIsStillBlockCommentForCode(false),
	mIsStillBlockCommentForComment(false),
	mIsStillLineCommentForCode(false),
	mIsStillLineCommentForComment(false)
{
}

bool LineCounterForCpp::isEmptyLine(const string& line)
{
	for(int i = 0 ; i < line.size() ; i ++)
	{
		if (false == isEmptyChar(line[i]))
		{
			return false;
		}
	}
	return true;
}

bool LineCounterForCpp::isCodeLine(const string& line)
{
	bool isEscapeBackSlant = false;
	if (true == mIsStillLineCommentForCode)
	{
		for(int i = 0 ; i < line.size() ; i++)
		{
			setEscapeBackSlant(line[i], isEscapeBackSlant);
		}
		if (false == isEscapeBackSlant)
		{
			mIsStillLineCommentForCode = false;
		}
		return false;
	}
	int i = 0;
	bool ret = false;
	while(i < line.size())
	{
		//try to jump out the block comment
		if (true == mIsStillBlockCommentForCode)
		{
			for(; i < line.size() ; i++)
			{
				setEscapeBackSlant(line[i],isEscapeBackSlant);
				if(i<line.size() - 1 && line[i] == '*' && line[i+1] == '/')
				{
					mIsStillBlockCommentForCode = false;
					i++;
					setEscapeBackSlant(line[i],isEscapeBackSlant);
					i++;
					break;
				}
			}
		}
		LOG("i is :%d,line size is :%lu",i,line.size());
		for(;i<line.size();i++)
		{
			setEscapeBackSlant(line[i],isEscapeBackSlant);
			if(i<line.size() - 1 && line[i] == '/' && line[i+1] == '*')
			{
				mIsStillBlockCommentForCode = true;
				i++;
				setEscapeBackSlant(line[i],isEscapeBackSlant);
				i++;
				break;	
			}
			if(i<line.size() - 1 && line[i] == '/' && line[i+1] == '/')
			{
				mIsStillLineCommentForCode = true;
				i++;
				setEscapeBackSlant(line[i],isEscapeBackSlant);
				i++;
				break;	
			}
			if (isEmptyChar(line[i]))
			{
				continue;
			}
			//don't return directly,there maybe some begin of /*
			ret = true;
		}
		if (true == mIsStillLineCommentForCode)
		{
			for(;i<line.size() ; i++)
			{
				setEscapeBackSlant(line[i], isEscapeBackSlant);	
			}
			if (true == isEscapeBackSlant)
			{
				mIsStillLineCommentForCode = true;
			}
			else
			{
				mIsStillLineCommentForCode = false;	
			}
		}
	}
	return ret;
}

bool LineCounterForCpp::isCommentLine(const string& line)
{
	bool isEscapeBackSlant = false;
	if (true == mIsStillLineCommentForComment )
	{
		for(int i = 0 ; i < line.size() ; i++)
		{
			setEscapeBackSlant(line[i], isEscapeBackSlant);
		}
		if (false == isEscapeBackSlant)
		{
			mIsStillLineCommentForComment = false;
		}
		return true;
	}
	bool ret = false;
	int i = 0;
	while(i < line.size())
	{
		//try to jump out the block comment
		if (true == mIsStillBlockCommentForComment)
		{
			ret = true;
			for(;i < line.size() ; i ++)
			{
				setEscapeBackSlant(line[i],isEscapeBackSlant);
				if(i<line.size() - 1 && line[i] == '*' && line[i+1] == '/')
				{
					mIsStillBlockCommentForComment= false;
					i++;
					setEscapeBackSlant(line[i],isEscapeBackSlant);
					i++;
					break;
				}	
			}
		}
		for(;i<line.size();i++)
		{
			setEscapeBackSlant(line[i],isEscapeBackSlant);
			if(i<line.size() - 1 && line[i] == '/' && line[i+1] == '*')
			{
				mIsStillBlockCommentForComment = true;
				i++;
				setEscapeBackSlant(line[i],isEscapeBackSlant);
				i++;
				ret = true;
				break;	
			}
			if(i<line.size() - 1 && line[i] == '/' && line[i+1] == '/')
			{
				mIsStillLineCommentForComment = true;
				i++;
				setEscapeBackSlant(line[i],isEscapeBackSlant);
				i++;
				ret = true;
				break;	
			}
		}
		if (true == mIsStillLineCommentForCode)
		{
			ret = true;
			for(;i<line.size() ; i++)
			{
				setEscapeBackSlant(line[i], isEscapeBackSlant);	
			}
			if (true == isEscapeBackSlant)
			{
				mIsStillLineCommentForComment = true;
			}
			else
			{
				mIsStillLineCommentForComment = false;	
			}
		}
	}
	return ret;	
}
void LineCounterForCpp::setEscapeBackSlant(const char input,bool &flag)
{
	if ('\\' == input)
	{
		flag = !flag;
		return;
	}
	if (false == isEmptyChar(input))
	{
		flag = false;
	}
}
