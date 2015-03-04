#ifndef _GRADIENT_DESCENT_H_
#define _GRADIENT_DESCENT_H_

#include <neighborhood.h>
#include <partitioning.h>

struct solution* gradient_descent(graph g, get_neighborhood f, valid v);

#endif /* _GRADIENT_DESCENT_H_ */
