#ifndef LINENUMBERCOLLECTOR_H
#define LINENUMBERCOLLECTOR_H

class LineNumberCollector {
public:
	virtual ~LineNumberCollector ();

	static LineNumberCollector* getInstance()
	{
		static LineNumberCollector* instance = NULL;
		if (NULL == instance)
		{
			//need thread safe guard
			instance = new LineNumberCollector();
		}
		return instance;
	}
	void addLineNum(LineType lineType,unsigned int number);

private:
	LineNumberCollector ();
	unsigned int mSumLineNum;
	unsigned int mEmptyLineNum;
	unsigned int mCommentLineNum;
	unsigned int mUsefulLineNum;
};

#endif /* end of include guard: LINENUMBERCOLLECTOR_H */
