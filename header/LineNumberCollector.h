#ifndef LINENUMBERCOLLECTOR_H
#define LINENUMBERCOLLECTOR_H

#include "LineCounterBase.h"
#include <vector>
#include <pthread.h>
using namespace std;

void* ThreadCalculateAFile(void* fileName);

#define MAX_THREAD_NUM 10
class LineNumberCollector {
public:
	virtual ~LineNumberCollector ();

	static LineNumberCollector* getInstance();
	void addLineNum(LineType lineType,unsigned int number);
	void calculateLineNum(const string& projcetDir);
	//number can be postive or negative
	void changeCalculatingFileNum(int number);

private:
	LineNumberCollector ();
	void scanFile(const string& dir);

private:

	vector<string> mProjectFileList;

	pthread_mutex_t mSumNumMutex;
	volatile unsigned int mSumLineNum;

	pthread_mutex_t mEmptyLineNumMutex;
	volatile unsigned int mEmptyLineNum;

	pthread_mutex_t mCommentLineNumMutex;
	volatile unsigned int mCommentLineNum;

	pthread_mutex_t mUsefuleLineNumMutex;
	volatile unsigned int mUsefulLineNum;

	pthread_mutex_t mCalculatingFileNumMutex;
	volatile unsigned int mCalculatingFileNum;
};

#endif /* end of include guard: LINENUMBERCOLLECTOR_H */
