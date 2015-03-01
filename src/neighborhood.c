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
  struct neighborhood *n = NULL;
  n = malloc(sizeof(*n));
  if(n == NULL){
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  
  n->size = 1;
  for(unsigned i = 0; i < K; ++i)
    n->size *= s->sizes[i];
  
  n->neighbors = malloc(n->size * sizeof(*n->neighbors));
  if(n->neighbors == NULL){
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  
  unsigned nb_neighbors = 0;
  unsigned permutation[K] = {0};
  while(nb_neighbors != n->size){
    struct solution *new_solution = solution_copy(s);
    unsigned tmp;
    unsigned previous = new_solution->partitions[K-1][permutation[K-1]];
    for(unsigned i = 0; i < K; ++i){
      tmp = new_solution->partitions[i][permutation[i]];
      new_solution->partitions[i][permutation[i]] = previous;
      previous = tmp;
    }
    n->neighbors[nb_neighbors] = new_solution;
    
    for(unsigned i = 0; i < K; ++i){
      if(permutation[i] == new_solution->sizes[i] - 1){
	permutation[i] = 0;
      }
      else{
	++permutation[i];
	break;
      }
    }
    ++nb_neighbors;
  }

  return n;
}

struct neighborhood *pick_n_drop(struct solution *s){
  struct neighborhood *n = NULL;
  n = malloc(sizeof(*n));
  if(n == NULL){
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  
  n->size = 0;
  for(unsigned i = 0; i < K; ++i)
    n->size += s->sizes[i] * (K-1);
  
  n->neighbors = malloc(n->size * sizeof(*n->neighbors));
  if(n->neighbors == NULL){
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  
  unsigned nb_neighbors = 0;
  for(unsigned p1 = 0; p1 < K; ++p1)
    for(unsigned v = 0; v < s->sizes[p1]; ++v)
      for(unsigned p2 = 0; p2 < K; ++p2)
	if(p1 != p2){
	  struct solution *new_solution = solution_copy(s);
	  
	  new_solution->partitions[p2] = realloc(new_solution->partitions[p2],
						 (new_solution->sizes[p2] + 1) * 
						 sizeof(*new_solution->partitions[p2]));
	  new_solution->partitions[p2][new_solution->sizes[p2]] = new_solution->partitions[p1][v];
	  ++new_solution->sizes[p2];
	  
	  for(unsigned i = v + 1; i < new_solution->sizes[p1]; ++i)
	    new_solution->partitions[p1][i-1] = new_solution->partitions[p1][i];
	  --new_solution->sizes[p1];
	  
	  n->neighbors[nb_neighbors] = new_solution;
	  ++nb_neighbors;
	}
  return n;
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
