#include <stdlib.h>
#include <stdio.h>
#include <float.h>

#include <debug.h>
#include <explicit_enumeration.h>

static struct solution *create_solution(unsigned *vertex_to_partition, unsigned nb_vertices){
  struct solution *s = NULL;
  s = calloc(1, sizeof(*s));
  if(s == NULL){
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  
  for(unsigned i = 0; i < nb_vertices; ++i)
    ++s->sizes[vertex_to_partition[i]];
  
  for(unsigned i = 0; i < K; ++i){
    s->partitions[i] = malloc(s->sizes[i] * sizeof(*s->partitions[i]));
    if(s->partitions[i] == NULL){
      perror("malloc");
      exit(EXIT_FAILURE);
    }
  }
  
  unsigned free_position[K] = {0};
  for(unsigned i = 0; i < nb_vertices; ++i){
    unsigned partition = vertex_to_partition[i];
    s->partitions[partition][free_position[partition]] = i + 1;
    ++free_position[partition];
  }

  #ifdef DEBUG_MODE
  solution_dump(s);
  #endif

  return s;
}

struct solution* explicit_enumeration(graph g, get_neighborhood f, valid v){
  unsigned *vertex_to_partition = NULL;
  unsigned nb_vertices = graph_nb_vertices(g);
  vertex_to_partition = calloc(nb_vertices, sizeof(*vertex_to_partition));
  if(vertex_to_partition == NULL){
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  
  bool end = false;
  struct solution *best_solution = NULL;
  float best_f_opt = FLT_MAX;
  struct solution *current_solution = NULL;
  float current_f_opt = 0;
  while(!end){
    current_solution = create_solution(vertex_to_partition, nb_vertices);
    current_f_opt = f_opt(g, current_solution, v);
    DEBUG("f_opt : %f\n", current_f_opt);
    if(current_f_opt < best_f_opt){
      if(best_solution) solution_destruct(best_solution);
      best_solution = current_solution;
      best_f_opt = current_f_opt;
      DEBUG("Better\n");
    }
    else{
      solution_destruct(current_solution);
    }
    
    for(unsigned i = 0; i < nb_vertices; ++i){
      if(vertex_to_partition[i] == K - 1){
	if(i == nb_vertices - 1){
	  end = true;
	  DEBUG("END\n");
	  break;
	}
	vertex_to_partition[i] = 0;
      }
      else{
	++vertex_to_partition[i];
	break;
      }
    }
  }
  
  return best_solution;
}
