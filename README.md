# LineCounter
面试题目，统计各种行数
编译：进入本目录直接make即可。用的接口都是标准接口，应该没有多大问题。
使用：./counter [projcect dir]即可。

架构说明:
1、main函数调用LineNumberCollector的calculateLineNum方法进行工程目录所有文件的扫描
2、calculateLineNum方法开启MAX_THREAD_NUM数量的线程，进行文件行数的统计，每个文件一条线程。
3、每条线程根据文件后缀名确定文件类型，然后拿到相应的对象，进行代码行数统计

关于其他类型文件的扩展：
继承LineCounterBase类，实现他的纯虚方法即可。
