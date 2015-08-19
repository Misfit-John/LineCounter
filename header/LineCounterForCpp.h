#ifndef LINECOUNTERFORCPP_H
#define LINECOUNTERFORCPP_H

#include "LineCounterBase.h"

class LineCounterForCpp:public LineCounterBase{
public:
	virtual ~LineCounterForCpp ();

private:
	virtual bool isEmptyLine(const string& line);
	virtual bool isCommentLine(const string& line);
private:
	//line seperator will make "//"comment affect next line
	bool mIsBlockComment;
	bool mIsLineComment;
};

#endif /* end of include guard: LINECOUNTERFORCPP_H */
