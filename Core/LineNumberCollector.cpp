#include "LineNumberCollector.h"
#include <dirent.h>
#include "Log.h"
#include "LineCounterFactory.h"

LineNumberCollector::~LineNumberCollector()
{
	
}

LineNumberCollector* LineNumberCollector::getInstance()
{
	static LineNumberCollector* instance = NULL;
	if (NULL == instance)
	{
		//need thread safe guard
		instance = new LineNumberCollector();
	}
	return instance;
}

LineNumberCollector::LineNumberCollector():
	mSumLineNum(0),
	mEmptyLineNum(0),
	mCommentLineNum(0),
	mUsefulLineNum(0),
	mCalculatingFileNum(0)
{
	pthread_mutex_init(&mSumNumMutex,NULL);
	pthread_mutex_init(&mEmptyLineNumMutex,NULL);
	pthread_mutex_init(&mCommentLineNumMutex,NULL);
	pthread_mutex_init(&mUsefuleLineNumMutex,NULL);
	pthread_mutex_init(&mCalculatingFileNumMutex,NULL);
}

void LineNumberCollector::calculateLineNum(const string& projcetDir)
{
	scanFile(projcetDir);
	for(int i = 0 ; i < mProjectFileList.size(); i++)
	{
		while(mCalculatingFileNum >= MAX_THREAD_NUM)
		{
		}
		this->changeCalculatingFileNum(1);
		pthread_t calculateThread;
		pthread_create(&calculateThread,NULL, ThreadCalculateAFile,(void*) mProjectFileList[i].c_str());
	}
	while(mCalculatingFileNum !=0 ){}
	printLineNum();
}

void LineNumberCollector::printLineNum()
{
	printf("Sum line num:		%d\n",mSumLineNum);
	printf("Empty line num:		%d\n",mEmptyLineNum);
	printf("Comment line nue:	%d\n",mCommentLineNum);
	printf("Code line num:		%d\n",mUsefulLineNum);
}

void LineNumberCollector::addLineNum(LineType lineType,unsigned int number)
{
	bool addToSumLine = true;
	switch(lineType)
	{
		case eLineTypeEmptyLine:
		   pthread_mutex_lock(&mEmptyLineNumMutex);
		   mEmptyLineNum += number;	  
		   pthread_mutex_unlock(&mEmptyLineNumMutex);
		   break;
		case eLineTypeCommentLine:
			pthread_mutex_lock(&mCommentLineNumMutex);
			mCommentLineNum += number;
			pthread_mutex_unlock(&mCommentLineNumMutex);
			break;
		case eLineTypeUsefuleLine:
			pthread_mutex_lock(&mUsefuleLineNumMutex);
			mUsefulLineNum += number;
			pthread_mutex_unlock(&mUsefuleLineNumMutex);
			break;
		case eLineTypeSumLine:
			pthread_mutex_lock(&mSumNumMutex);
			mSumLineNum += number;
			pthread_mutex_unlock(&mSumNumMutex);
			break;
		default:
			addToSumLine = false;
			ERROR("unknow line type");
			break;
	}
}

void LineNumberCollector::changeCalculatingFileNum(int number)
{
	pthread_mutex_lock(&mCalculatingFileNumMutex);
	mCalculatingFileNum += number;
	pthread_mutex_unlock(&mCalculatingFileNumMutex);
}

void LineNumberCollector::scanFile(const string& dir)
{
	DIR *fileDirPtr = opendir(dir.c_str());
	struct dirent *direntPtr = NULL;
	if (NULL == fileDirPtr)
	{
		ERROR("can not open dir:%s", dir.c_str());
		return ;
	}
	while ((direntPtr = readdir(fileDirPtr)) != NULL)
	{
		if (strcmp(direntPtr->d_name,"..") == 0)
		{
			continue;
		}
		if (strcmp(direntPtr->d_name,".") == 0)
		{
			continue;
		}
		if(direntPtr->d_type == DT_DIR)
		{
			scanFile(dir + direntPtr->d_name);	
		}
		else
		{
			mProjectFileList.push_back(dir + direntPtr->d_name);		
		}
	}
	closedir(fileDirPtr);
	fileDirPtr = NULL;
}

void* ThreadCalculateAFile(void *fileName)
{
	if (NULL == fileName)
	{
		ERROR("null file name");
		return NULL;
	}
	char* input = (char*)fileName;
	LOG("file name is :%s",input);
	LineCounterBase *counter = LineCounterFactory::getInstance()->getLineCounter(input);
	if (NULL == counter)
	{
		ERROR("can not find line counter for file:%s",input);
	}
	else
	{
		counter->countLine();
	}
	LineNumberCollector::getInstance()->changeCalculatingFileNum(-1);
	pthread_exit(NULL); 
}
