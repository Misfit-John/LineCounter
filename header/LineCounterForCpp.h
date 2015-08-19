#ifndef LINECOUNTERFORCPP_H
#define LINECOUNTERFORCPP_H

#include "LineCounterBase.h"

class LineCounterForCpp:public LineCounterBase{
public:
	LineCounterForCpp(const string& filename);

private:
	virtual bool isEmptyLine(const string& line);
	virtual bool isCommentLine(const string& line);
private:
	//line seperator will make "//"comment affect next line
	bool mIsStillBlockComment;
	bool mIsStillLineComment;
};

#endif /* end of include guard: LINECOUNTERFORCPP_H */
