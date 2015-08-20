#include "LineCounterForCpp.h"
#include "Log.h"

LineCounterForCpp::LineCounterForCpp(const string& filename):
	LineCounterBase(filename),
	mState(eCppBegin)
{
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

void LineCounterForCpp::checkAline(const string& line, bool &isEmpty,bool &isCode, bool &isComment)
{
	isEmpty = true;
	isCode = false;
	isComment = (mState == eCppCommentBlock) || (mState == eCppCommentLine);

	bool isEscapeBackSlant = false;
	for(int i = 0;i<line.size(); i++)
	{
		if (false == isEmptyChar(line[i]))
		{
			isEmpty = false;
		}
		else
		{
			setEscapeBackSlant(line[i],isEscapeBackSlant);
			continue;	
		}
		switch(mState)
		{
			case eCppBegin:
			case eCppCode:
			{
				if(false == isEscapeBackSlant && '/' == line[i] && i + 1 < line.size() && '/' == line[i+1])
				{
					setEscapeBackSlant(line[i],isEscapeBackSlant);
					i++;
					mState = eCppCommentLine;	
					isComment = true;
					break;
				}
				if(false == isEscapeBackSlant && '/' == line[i] && i + 1 < line.size() && '*' == line[i+1])
				{
					setEscapeBackSlant(line[i],isEscapeBackSlant);
					i++;
					mState = eCppCommentBlock;	
					isComment = true;
					break;
				}
				isCode = true;
				if (false == isEscapeBackSlant && '"' == line[i])
				{
					mState = eCppString;
				}
				if ('\'' == line[i])
				{
					mState = eCppChar;
				}
				break;
			}
			case eCppCommentLine:
			{
				//do nothing
				isComment = true;
				break;
			}
			case eCppString:
			{
				isCode = true;
				if ('"' == line[i] && false == isEscapeBackSlant)
				{
					mState = eCppCode;
				}
				break;
			}
			case eCppChar:
			{
				isCode = true;
				if ('\'' == line[i] && false == isEscapeBackSlant)
				{
					mState = eCppCode;
				}
				break;
			}
			case eCppCommentBlock:
			{
				isComment = true;
				if('*' == line[i] && i+1 < line.size() && '/' == line[i+1] )
				{
					setEscapeBackSlant(line[i], isEscapeBackSlant);	
					i++;
					mState = eCppCode;
				}
				break;
			}
			default:
			{
				ERROR("unknow state:%d",mState);
				break;
			}
		}
		setEscapeBackSlant(line[i],isEscapeBackSlant);
	}
	if (false == isEscapeBackSlant && eCppCommentBlock != mState)
	{
		mState = eCppCode;
	}
}

