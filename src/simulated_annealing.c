#include <math.h>

#include <simulated_annealing.h>
#include <partitioning.h>
#include <neighborhood.h>
#include <random.h>

static struct solution *choose_neighbor(struct neighborhood *n){
  return solution_copy(n->neighbors[random_get_unsigned(n->size)]);
}

static float temperature_variation(float t){
  return t / 2;
}

static unsigned proba(float delta_f, float temperature){
  return (unsigned) ((expf(-delta_f / temperature)) * 1000);
}

struct solution* simulated_annealing(graph g, get_neighborhood f, valid v){
  struct solution *X = solution_random(g);
  struct solution *best_X = X;
  float best_f = f_opt(g, best_X, v);
  int time = 0;
  float temperature = SIMULATED_ANNEALING_T_0;
  while(random_get_unsigned(SIMULATED_ANNEALING_ACCEPTATION_PROBA) != 0){
    unsigned nb_fail = 0;
    while(nb_fail >= SIMULATED_ANNEALING_NB_FAIL_MAX){
      struct neighborhood *n = f(X);
      struct solution *X_plus_1 = choose_neighbor(n);
      neighborhood_destruct(n);
      float f_X = f_opt(g, X, v);
      float f_X_plus_1 = f_opt(g, X_plus_1, v);
      float delta_f = f_X_plus_1 - f_X;
      if(delta_f < 0){
	solution_destruct(X);
	X = X_plus_1;
	if(f_X_plus_1 < best_f){
	  solution_destruct(best_X);
	  best_X = X;
	  best_f = f_X_plus_1;
	}
	else{
	  ++nb_fail;
	}
      }
      else { // delta_f >= 0
	unsigned p = random_get_unsigned(1000);
	if(p < proba(delta_f, temperature)){
	  solution_destruct(X);
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
  return best_X;
}
