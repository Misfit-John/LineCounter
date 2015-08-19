#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define ERROR(msg,...){printf("Error:[%s][%s:%d]:\n" msg "\n",__FILE__,__func__,__LINE__,##__VA_ARGS__);}
#ifdef DEBUG
#define LOG(msg,...) {printf("[%s][%s:%d]:" msg "\n" ,__FILE__,__func__,__LINE__,##__VA_ARGS__);}
#else
#define LOG(msg,...) do{}while(0);
#endif

#endif /* end of include guard: LOG_H */
