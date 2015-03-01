#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include <partitioning.h>
#include <graph.h>

struct solution *solution_create(graph g){
  struct solution *s = NULL;
  s = malloc(sizeof(*s));
  if(s == NULL){
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  
  unsigned nb_vertices = graph_nb_vertices(g);
  
  for(int i = 0; i < K; ++i){
    s->sizes[i] = nb_vertices / K;
    if(i < nb_vertices % K)
      ++s->sizes[i];
    s->partitions[i] = malloc(s->sizes[i] * sizeof(*s->partitions));
    if(s->partitions[i] == NULL){
      perror("malloc");
      exit(EXIT_FAILURE);
    } 
  }
  
  unsigned vertex = 1;
  for(int partition = 0; partition < K; ++partition)
    for(int i = 0; i < s->sizes[partition]; ++i){
      s->partitions[partition][i] = vertex;
      ++vertex;
    }
  return s;
}
  
void solution_dump(struct solution *s){
  for(int i = 0; i < K; ++i){
    printf("{");
    for(int j = 0; j < s->sizes[i]; ++j){
      printf("%u", s->partitions[i][j]);
      if(j != s->sizes[i] - 1)
	printf(" ");
    }
    printf("}\n");
  }
}

void solution_destruct(struct solution *s){
  for(int i = 0; i < K; ++i)
    free(s->partitions[i]);
  free(s);
}

struct solution *solution_copy(struct solution *s){
  struct solution *new = NULL;
  new = malloc(sizeof(*new));
  if(new == NULL){
    perror("malloc");
    exit(EXIT_FAILURE);
  }

  for(int i = 0; i < K; ++i){
    new->sizes[i] = s->sizes[i];
    size_t size = new->sizes[i] * sizeof(*new->partitions);
    new->partitions[i] = malloc(size);
    if(new->partitions[i] == NULL){
      perror("malloc");
      exit(EXIT_FAILURE);
    }
    memcpy(new->partitions[i], s->partitions[i], size);
  }
  
  return new;
}

float f_opt(graph g, struct solution *s, valid v){
  float result = 0;
  if(!v(s))
    return INVALID_SOLUTION;
  for(unsigned i = 0; i < K - 1; ++i)
    for(unsigned v1 = 0; v1 < s->sizes[i]; ++v1)
      for(unsigned j = i + 1; j < K; ++j)
	for(unsigned v2 = 0; v2 < s->sizes[j]; ++v2)
	  result += graph_adjacent(g, s->partitions[i][v1], s->partitions[j][v2]);
  return result;
}
