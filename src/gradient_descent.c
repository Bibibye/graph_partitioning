#include <neighborhood.h>
#include <partitioning.h>
#include <gradient_descent.h>

static struct solution* _gradient_descent(graph g, get_neighborhood f, valid v, struct solution* best_s) {
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


struct solution* gradient_descent(graph g, get_neighborhood f, valid v) {
	const size_t seed_size = (int)DESC_SEED(graph_nb_vertices(g));
	struct solution* best_seed = NULL;
	float best_score = FLT_MAX;

	for(int i = 0; i < seed_size; i++) {
		struct solution* test = _gradient_descent(g, f, v, solution_random(g));
		float score = f_opt(g, test, v);
		if(score < best_score) {
			if(best_seed != NULL)
				solution_destruct(best_seed);
			best_seed = test;
			best_score = score;
		} else
			solution_destruct(test);
	}
	return best_seed;
}
