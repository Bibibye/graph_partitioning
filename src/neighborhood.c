#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <neighborhood.h>
#include <partitioning.h>

struct neighborhood *swap(struct solution *s){
  struct neighborhood *n = NULL;
  n = malloc(sizeof(*n));
  if(n == NULL){
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  
  n->size = 0;
  for(unsigned i = 0; i < K - 1; ++i)
    for(unsigned j = i + 1; j < K; ++j)
      n->size += s->sizes[i] * s->sizes[j];
  
  n->neighbors = malloc(n->size * sizeof(*n->neighbors));
  if(n->neighbors == NULL){
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  
  unsigned nb_neighbors = 0;
  for(unsigned i = 0; i < K - 1; ++i)
    for(unsigned v1 = 0; v1 < s->sizes[i]; ++v1)
      for(unsigned j = i + 1; j < K; ++j)
	for(unsigned v2 = 0; v2 < s->sizes[j]; ++v2){
	  struct solution *new_solution = solution_copy(s);
	  unsigned tmp = new_solution->partitions[i][v1];
	  new_solution->partitions[i][v1] = new_solution->partitions[j][v2];
	  new_solution->partitions[j][v2] = tmp;
	  n->neighbors[nb_neighbors] = new_solution;
	  ++nb_neighbors;
	}
  
  return n;
}

struct neighborhood *sweep(struct solution *s){
  return NULL;
}

struct neighborhood *pick_n_drop(struct solution *s){
  return NULL;
}

void neighborhood_destruct(struct neighborhood *n){
  for(unsigned i = 0; i < n->size; ++i)
    solution_destruct(n->neighbors[i]);
  free(n->neighbors);
  free(n);
}

void neighborhood_dump(struct neighborhood *n){
  for(unsigned i = 0; i < n->size; ++i){
    solution_dump(n->neighbors[i]);
    printf("\n");
  }
}
