#ifndef _PARTITIONING_H_
#define _PARTITIONING_H_

#include <stdbool.h>
#include <stdlib.h>
#include <float.h>

#include <graph.h>

// number of partitions
#ifndef K
#define K 2
#endif /* K */

#define INVALID_SOLUTION FLT_MAX

struct solution{
  size_t sizes[K];
  unsigned int *partitions[K];
};

// Defines if a solution is valid or not
typedef bool (*valid)(struct solution*);

struct solution *solution_create(graph g);
struct solution *solution_copy(struct solution *s);
void solution_destruct(struct solution *s);
void solution_dump(struct solution *s);

/*
 * We want this function to be minimal.
 * return : sum of inter-classes edges' weight
 */
float f_opt(graph g, struct solution *s, valid v);

bool one_percent_error(struct solution* s);

#endif /* _PARTITIONING_H_ */
