#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#ifdef DEBUG
#define LOG(msg) {printf("[%s][%s:%d]"#msg,__FILE__,__func__,__LINE__);}
#else
#define LOG(msg) do{}while(0);


#endif /* end of include guard: LOG_H */
