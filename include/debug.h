#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <stdio.h>

#ifdef DEBUG_MODE
#define DEBUG(format, ...) do{						\
    printf("[%s:%d]\n\t" format,					\
	   __FILE__, __LINE__, ##__VA_ARGS__);				\
  }while(0)
#else
#define DEBUG(format, ...) do{			\
  }while(0)
#endif /* DEBUG_MODE */

#endif /* _DEBUG_H_ */
