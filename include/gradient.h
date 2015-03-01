#ifndef _GRADIENT_H_
#define _GRADIENT_H_

#include <neighborhood.h>
#include <partitioning.h>

struct solution* gradient(graph g, get_neighborhood f, valid v);

#endif /* _GRADIENT_H_ */
