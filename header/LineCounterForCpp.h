#ifndef LINECOUNTERFORCPP_H
#define LINECOUNTERFORCPP_H

#include "LineCounterBase.h"

class LineCounterForCpp:public LineCounterBase{
public:
	LineCounterForCpp(const string& filename);

private:
	virtual bool isEmptyLine(const string& line);
	virtual bool isCommentLine(const string& line);
	virtual bool isCodeLine(const string& line);
	void setEscapeBackSlant(const char input,bool &flag);
private:
	//line seperator will make "//"comment affect next line
	bool mIsStillBlockCommentForCode;
	bool mIsStillBlockCommentForComment;
	bool mIsStillLineCommentForCode;
	bool mIsStillLineCommentForComment;
};

#endif /* end of include guard: LINECOUNTERFORCPP_H */
