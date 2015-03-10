#ifndef TABOO_H
#define TABOO_H

#include <neighborhood.h>
#include <partitioning.h>

struct solution* taboo(graph g, get_neighborhood f, valid v);

#endif 
