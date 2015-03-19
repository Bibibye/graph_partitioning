#ifndef _SIMULATED_ANNEALING_H_
#define _SIMULATED_ANNEALING_H_

#include <neighborhood.h>
#include <partitioning.h>

#define SIMULATED_ANNEALING_T_0 1000

/* Will be multiplicated by the number of vertices */
#define SIMULATED_ANNEALING_NB_FAIL_MAX 10

#define SIMULATED_ANNEALING_ACCEPTATION_PROBA 100

#define SIMULATED_ANNEALING_T_MIN 0.1

struct solution* simulated_annealing(graph g, get_neighborhood f, valid v);

#endif /* _SIMULATED_ANNEALING_H_ */
