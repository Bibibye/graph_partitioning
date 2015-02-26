#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <graph.h>
#include <partitioning.h>
#include <neighborhood.h>

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
  printf("\n");
  
  struct solution *s = NULL;
  s = solution_create(g);
  solution_dump(s);  
  printf("\nf_opt(s) = %f\n", f_opt(g, s, my_valid));
  printf("\n");
  
  struct neighborhood *n = NULL;
  n = swap(s);
  neighborhood_dump(n);
  
  neighborhood_destruct(n);
  solution_destruct(s);
  graph_destruct(g);
  return EXIT_SUCCESS;
}
