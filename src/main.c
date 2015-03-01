#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <graph.h>
#include <partitioning.h>
#include <neighborhood.h>

#define SEPARATOR "------------------------------\n"

void usage(char *name){
  printf("Usage : %s filename\n", name);
  exit(EXIT_FAILURE);
}

bool my_valid(struct solution *s){
  return true;
}

int main(int argc, char **argv){
  if(argc != 2)
    usage(argv[0]);
  graph g = NULL;
  g = graph_create(argv[1]);
  graph_dump(g);
  
  printf(SEPARATOR);
  
  struct solution *s = NULL;
  s = solution_create(g);
  solution_dump(s);  
  printf("\nf_opt(s) = %f\n", f_opt(g, s, my_valid));
  
  printf(SEPARATOR);
  
  struct neighborhood *n1 = NULL;
  n1 = swap(s);
  neighborhood_dump(n1);
  
  printf(SEPARATOR);
  
  struct neighborhood *n2 = NULL;
  n2 = pick_n_drop(s);
  neighborhood_dump(n2);
  
  neighborhood_destruct(n1);
  neighborhood_destruct(n2);
  solution_destruct(s);
  graph_destruct(g);
  return EXIT_SUCCESS;
}
