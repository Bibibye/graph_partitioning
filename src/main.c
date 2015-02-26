#include <stdio.h>
#include <stdlib.h>

#include <graph.h>

void usage(char *name){
  printf("Usage : %s filename\n", name);
  exit(EXIT_FAILURE);
}

int main(int argc, char **argv){
  if(argc != 2)
    usage(argv[0]);
  graph g;
  g = graph_create(argv[1]);
  graph_dump(g);
  graph_destruct(g);
  return EXIT_SUCCESS;
}
