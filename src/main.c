#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <graph.h>
#include <partitioning.h>

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
  graph g;
  g = graph_create(argv[1]);
  graph_dump(g);
  struct solution *s;
  s = solution_create(g);
  printf("\n");
  solution_dump(s);
  
  struct solution *s2 = solution_copy(s);
  solution_dump(s2);
  solution_destruct(s2);
  printf("\nf_opt(s) = %f\n", f_opt(g, s, my_valid));
  solution_destruct(s);
  graph_destruct(g);
  return EXIT_SUCCESS;
}
