#include "LineNumberCollector.h"

int main(int argc, const char *argv[])
{
	if (argc != 2)
	{
		printf("usage:%s [project dir]",argv[0]);
		return -1;
	}
	LineNumberCollector::getInstance()->calculateLineNum(argv[1]);	

	return 0;
}
