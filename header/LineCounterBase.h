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
	virtual bool isEmptyLine(const string& line) = 0;
	virtual bool isCommentLine(const string& line) = 0;

	void addLineNum(LineType lineType);

private:
	string mFileName;
	unsigned int mSumLineNum;
	unsigned int mEmptyLineNum;
	unsigned int mCommentLineNum;
	unsigned int mUsefulLineNum;
};

#endif /* end of include guard: LINECOUNTERBASE_H */
