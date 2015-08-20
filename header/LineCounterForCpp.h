#ifndef LINECOUNTERFORCPP_H
#define LINECOUNTERFORCPP_H

#include "LineCounterBase.h"

enum CppCodeState
{
	eCppBegin = 0,
	eCppCode = 1,
	eCppString,
	eCppCommentLine,
	eCppCommentBlock,
	eCppChar,
};


class LineCounterForCpp:public LineCounterBase{
public:
	LineCounterForCpp(const string& filename);

private:
	void checkAline(const string& line, bool &isEmpty,bool &isCode, bool &isComment);
	void setEscapeBackSlant(const char input,bool &flag);
private:
	//line seperator will make "//"comment affect next line
	int mState;
};

#endif /* end of include guard: LINECOUNTERFORCPP_H */
