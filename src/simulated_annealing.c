#include <math.h>

#include <simulated_annealing.h>
#include <partitioning.h>
#include <neighborhood.h>
#include <random.h>
#include <debug.h>

static struct solution *choose_neighbor(struct neighborhood *n){
  return solution_copy(n->neighbors[random_get_unsigned(n->size)]);
}

static float temperature_variation(float t){
  return t * SIMULATED_ANNEALING_RATIO;
}

static unsigned proba(float delta_f, unsigned t){
  return (unsigned) ((expf(-delta_f / t)) * 1000);
}

struct solution* simulated_annealing(graph g, get_neighborhood f, valid v){
  struct solution *X = solution_random(g);
  struct solution *best_X = X;
  float best_f = f_opt(g, best_X, v);
  int time = 0;
  float temperature = SIMULATED_ANNEALING_T_0;
  
#ifdef DEBUG_MODE
  unsigned nb_iter = 0;
#endif
    
#ifdef SIMULATED_ANNEALING_RANDOM_ACCEPTATION
  while(random_get_unsigned(SIMULATED_ANNEALING_ACCEPTATION_PROBA) != 0){
#else
  while(temperature > SIMULATED_ANNEALING_T_MIN){
#endif
    
    unsigned nb_fail = 0;
    unsigned max_fail = SIMULATED_ANNEALING_NB_FAIL_MAX * graph_nb_vertices(g);
    
#ifdef DEBUG_MODE
    ++nb_iter;
#endif
    
    while(nb_fail < max_fail){
      struct neighborhood *n = f(X);
      struct solution *X_plus_1 = choose_neighbor(n);
      neighborhood_destruct(n);
      float f_X = f_opt(g, X, v);
      float f_X_plus_1 = f_opt(g, X_plus_1, v);
      float delta_f = f_X_plus_1 - f_X;
      if(delta_f < 0) {
	if(X != best_X) solution_destruct(X);
	X = X_plus_1;
	if(f_X_plus_1 < best_f){
	  if(X != best_X) solution_destruct(best_X);
	  best_X = X_plus_1;
	  best_f = f_X_plus_1;
	}
	else{
	  ++nb_fail;
	}
      }
      else { // delta_f >= 0
	unsigned p = random_get_unsigned(1000);
	if(p < proba(delta_f, time)){
	  if(X != best_X) solution_destruct(X);
	  X = X_plus_1;
	}
	else{
	  solution_destruct(X_plus_1);
	}
      }
      ++time;
    }
    temperature = temperature_variation(temperature);
  }
  
  DEBUG("nb_iter : %d\n", nb_iter);
  return best_X;
}
