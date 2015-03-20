#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include <graph.h>
#include <partitioning.h>
#include <neighborhood.h>
#include <explicit_enumeration.h>
#include <gradient_descent.h>
#include <taboo.h>
#include <simulated_annealing.h>

typedef struct solution* (*heuristic_impl)(graph, get_neighborhood, valid);

struct heuristic_info{
  char *name;
  heuristic_impl function;
};

struct heuristic_info heuristics[] = {
  {"explicit_enum", explicit_enumeration},
  {"gradient_descent", gradient_descent},
  {"taboo", taboo},
  {"simulated_annealing", simulated_annealing}
};

#define NB_HEURISTICS (sizeof(heuristics)/sizeof(struct heuristic_info))

struct neighborhood_info{
  char *name;
  get_neighborhood function;
};

struct neighborhood_info neighborhoods[] = {
  {"swap", swap},
  {"sweep", sweep},
  {"pick_n_drop", pick_n_drop}
};

#define NB_NEIGHBORHOODS (sizeof(neighborhoods)/sizeof(struct neighborhood_info))

static void usage(const char *name){
  printf("Usage : %s <heuristic> <neighborhood> <filename>\n\nHeuristics available are :\n", 
	 name);
  for(unsigned i = 0; i < NB_HEURISTICS; ++i)
    printf("\t- %s\n", heuristics[i].name);
  printf("\nNeighborhoods available are :\n");
  for(unsigned i = 0; i < NB_NEIGHBORHOODS; ++i)
    printf("\t- %s\n", neighborhoods[i].name);
  exit(EXIT_FAILURE);
}

static heuristic_impl find_heuristic(const char *name){
  for(unsigned i = 0; i < NB_HEURISTICS; ++i)
    if(!strcmp(heuristics[i].name, name))
      return heuristics[i].function;
  return NULL;
}

static get_neighborhood find_neighborhood(const char *name){
  for(unsigned i = 0; i < NB_NEIGHBORHOODS; ++i)
    if(!strcmp(neighborhoods[i].name, name))
      return neighborhoods[i].function;
  return NULL;
}

int main(int argc, char **argv){
  if(argc != 4)
    usage(argv[0]);
  heuristic_impl h = NULL;
  graph g = NULL;
  get_neighborhood n = NULL;
  struct solution *s = NULL;
  
  h = find_heuristic(argv[1]);
  if(h == 0)
    usage(argv[0]);
  
  n = find_neighborhood(argv[2]);
  if(n == NULL)
    usage(argv[0]);
  
  g = graph_create(argv[3]);
  
  time_t start = time(NULL);
  s = h(g, n, one_percent_error);
  //solution_dump(s);
  printf("%f %ld\n", f_opt(g, s, one_percent_error), time(NULL) - start);
  
  solution_destruct(s);
  graph_destruct(g);
  return EXIT_SUCCESS;
}
