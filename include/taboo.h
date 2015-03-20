#ifndef TABOO_H
#define TABOO_H

#include <neighborhood.h>
#include <partitioning.h>

#define TABOO_SIZE 10
#define TABOO_ITERMAX 100

struct solution* taboo(graph g, get_neighborhood f, valid v);

#endif 
