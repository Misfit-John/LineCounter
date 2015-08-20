#ifndef LINECOUNTERBASE_H
#define LINECOUNTERBASE_H

#include <string>
using namespace std;

enum LineType
{
	eLineTypeUnknow = 0, //unlikely
	eLineTypeEmptyLine ,
	eLineTypeCommentLine,
	eLineTypeUsefuleLine,

	eLineTypeSumLine,
};

class LineCounterBase {
public:
	LineCounterBase(const string& fileName);
	virtual ~LineCounterBase ();

	void countLine();
	unsigned int getTotalLineNum();
	unsigned int getEmptyLineNum();
	unsigned int getCommentLineNum();
	unsigned int getCodeLineNum();

protected:
	LineCounterBase ();
	virtual void checkAline(const string& line, bool &isEmpty,bool &isCode, bool &isComment) = 0;
	void addLineNum(LineType lineType);
	bool isEmptyChar(const char input);
private:
	string mFileName;
	unsigned int mSumLineNum;
	unsigned int mEmptyLineNum;
	unsigned int mCommentLineNum;
	unsigned int mUsefulLineNum;
};

#endif /* end of include guard: LINECOUNTERBASE_H */
