#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <graph.h>
#include <partitioning.h>
#include <neighborhood.h>
#include <explicit_enumeration.h>

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
  
  struct solution *s1 = NULL;
  s1 = solution_create(g);
  solution_dump(s1);  
  printf("\nf_opt(s1) = %f\n", f_opt(g, s1, my_valid));
  
  printf(SEPARATOR);
  
  struct neighborhood *n1 = NULL;
  n1 = swap(s1);
  neighborhood_dump(n1);
  
  printf(SEPARATOR);
  
  struct neighborhood *n2 = NULL;
  n2 = pick_n_drop(s1);
  neighborhood_dump(n2);

  printf(SEPARATOR);
  
  struct neighborhood *n3 = NULL;
  n3 = sweep(s1);
  neighborhood_dump(n3);

  printf(SEPARATOR);
  
  struct solution *s2 = NULL;
  printf("Explicit enumeration : \n");
  s2 = explicit_enumeration(g, NULL, v_small);
  solution_dump(s2);
  printf("f_opt = %f\n", f_opt(g, s2, v_small));
  
  neighborhood_destruct(n1);  
  neighborhood_destruct(n2);
  neighborhood_destruct(n3);
  solution_destruct(s1);
  solution_destruct(s2);
  graph_destruct(g);
  return EXIT_SUCCESS;
}
