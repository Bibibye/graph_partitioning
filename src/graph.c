#include <graph.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define EDGE(i, j, nb_vertices) ((i-1) + (j-1) * (nb_vertices))

struct graph{
  unsigned nb_edges;
  unsigned nb_vertices;
  float *matrix;
};

graph graph_create(char *filename){
  FILE *f = NULL;
  graph g = NULL;
  
  f = fopen(filename, "r");
  if(f == NULL){
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  
  g = malloc(sizeof(*g));
  if(g == NULL){
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  
  char *buffer = NULL;
  size_t size_buffer = 0;
  bool header = false;
  unsigned int nb_edges_read = 0;
  
  while(getline(&buffer, &size_buffer, f) != -1){
    if(buffer[0] == '#')
      continue;
    
    if(!header){
      sscanf(buffer, "%u %u", &g->nb_vertices, &g->nb_edges);
      g->matrix = malloc(g->nb_vertices * g->nb_vertices * sizeof(*g->matrix));
      if(g->matrix == NULL){
	perror("fopen");
	exit(EXIT_FAILURE);
      }
      
      // We skip the 2nd header part
      do{
	getline(&buffer, &size_buffer, f);
      }while(buffer[0] == '#');
      header = true;
      continue;
    }
    
    unsigned i, j;
    float w;
    sscanf(buffer, "%u %u %f", &i, &j, &w);
    //printf("%d %d %f -> %d\n", i, j, w, EDGE(i,j,g->nb_vertices));
    g->matrix[EDGE(i,j,g->nb_vertices)] = w;
    g->matrix[EDGE(j,i,g->nb_vertices)] = w;
    
    // We skip the last block (vertices degree)
    ++nb_edges_read;
    if(nb_edges_read == g->nb_edges)
      break;
  }
  free(buffer);
  fclose(f);
  return g;
}

void graph_destruct(graph g){
  free(g->matrix);
  free(g);
}

float graph_adjacent(graph g, unsigned int i, unsigned int j){
  return g->matrix[EDGE(i, j, g->nb_vertices)];
}

void graph_dump(graph g){
  printf("nb_edges : %d\nnb_vertices : %d\n", g->nb_edges, g->nb_vertices);
  for(int i = 1; i <= g->nb_vertices; ++i){
    for(int j = 1; j < i; ++j)
      printf("%.1f ", g->matrix[EDGE(i,j,g->nb_vertices)]);
    printf("\n");
  }
}

unsigned graph_nb_vertices(graph g){
  return g->nb_vertices;
}
unsigned graph_nb_edges(graph g){
  return g->nb_edges;
}
