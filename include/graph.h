#ifndef _GRAPH_H_
#define _GRAPH_H_

#define EDGE(i, j, nb_vertices) ((i-1) + (j-1) * (nb_vertices))

typedef struct graph *graph;

graph graph_create(char *filename);
float graph_adjacent(graph g, unsigned int i, unsigned int j);
void graph_destruct(graph g);
void graph_dump(graph g);

#endif /* _GRAPH_H_ */
