#ifndef _NEIGHBORHOOD_H_
#define _NEIGHBORHOOD_H_

#include <partitioning.h>

struct neighborhood{
  size_t size;
  struct solution **neighbors;
};

typedef struct neighborhood *(*get_neighborhood)(struct solution *);

struct neighborhood *swap(struct solution *s);
struct neighborhood *sweep(struct solution *s);
struct neighborhood *pick_n_drop(struct solution *s);

void neighborhood_destruct(struct neighborhood *n);
void neighborhood_dump(struct neighborhood *n);

#endif /* _NEIGHBORHOOD_H_ */
