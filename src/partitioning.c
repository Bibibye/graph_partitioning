#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include <partitioning.h>
#include <graph.h>
#include <debug.h>
#include <random.h>

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

struct solution *solution_random(graph g){
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
  
  unsigned positions[K] = {0};
  unsigned non_full_partitions = K;
  for(unsigned vertex = 1; vertex <= nb_vertices; ++vertex){
    unsigned choice = random_get_unsigned(non_full_partitions);
    for(unsigned i = 0; i < K; ++i)
      if(positions[i] < s->sizes[i]){
	if(choice == 0) {
	  s->partitions[i][positions[i]] = vertex;
	  if(++positions[i] == s->sizes[i])
	    --non_full_partitions;
	  DEBUG("%d -> %d\n", vertex, i);
	  break;
	}
	else
	  --choice;
      }
  }
  return s;  
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
  if(!v(s) || s == NULL)
    return INVALID_SOLUTION;
  for(unsigned i = 0; i < K - 1; ++i)
    for(unsigned v1 = 0; v1 < s->sizes[i]; ++v1)
      for(unsigned j = i + 1; j < K; ++j)
	for(unsigned v2 = 0; v2 < s->sizes[j]; ++v2)
	  result += graph_adjacent(g, s->partitions[i][v1], s->partitions[j][v2]);
  return result;
}

bool one_percent_error(struct solution* s) {
  unsigned max_difference = 0;
  unsigned total_size = s->sizes[K-1];
  for(unsigned i = 0; i < K - 1; ++i){
    total_size += s->sizes[i];
    for(unsigned j = i + 1; j < K; ++j){
      unsigned difference = (s->sizes[i] > s ->sizes[j]) ?
	s->sizes[i] - s->sizes[j] :
	s->sizes[j] - s->sizes[i];
      if(difference > max_difference)
	max_difference = difference;
    }
  }
  unsigned max_error = (unsigned)ceil(total_size * (1./100.));
  DEBUG("max_error = %d difference = %d\n", max_error, max_difference);
  return max_difference <= max_error;
}
