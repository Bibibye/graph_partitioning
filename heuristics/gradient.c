#include <gradient.h>

struct solution* gradient(graph g, get_neighborhood f, valid v) {
	struct solution* ret = solution_create(g);
	float cur = f_opt(g, ret, v);
	float init;
	do {
		init = cur;
		struct neighborhood* n = f(ret);
		cur = f_opt(g, ret, v);
		neighborhood_destruct(n);
	} while(cur < init);
	return ret;
}
