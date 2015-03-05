#include <neighborhood.h>
#include <partitioning.h>
#include <gradient_descent.h>

struct solution* gradient_descent(graph g, get_neighborhood f, valid v){
  struct solution* best_s = solution_create(g);
  float current_f = f_opt(g, best_s, v);
  float best_f = current_f;
  bool end = false;
  while(!end){
    struct neighborhood *n = f(best_s);
    end = true;
    for(unsigned i = 0; i < n->size; ++i){
      current_f = f_opt(g, n->neighbors[i], v);
      if(current_f < best_f){
	end=false;
	best_f = current_f;
	solution_destruct(best_s);
	best_s = solution_copy(n->neighbors[i]);
      }
    }
    neighborhood_destruct(n);
  }
  return best_s;
}
