#include "taboo.h"
#include <assert.h>
#include <stdio.h>

struct fifo {
	struct solution* e;
	struct fifo *nxt, *prv;
};
typedef struct fifo fifo;
static fifo *in, *out;
size_t fifo_size;

static bool fifo_in(struct solution* s);
static struct solution* fifo_popfree();
static void fifo_push(struct solution* s);
static void fifo_del();
static void fifo_init() { in = NULL; out = NULL; fifo_size = 0; }
static bool fifo_full() { return fifo_size == TABOO_SIZE; }

struct solution* taboo(graph g, get_neighborhood f, valid v) {
	fifo_init();
	struct solution* best_s = solution_random(g);
	float best_f = f_opt(g, best_s, v);
	for(size_t iter = 0; iter < TABOO_ITERMAX; iter++) {
		struct neighborhood *n = f(best_s);

		for(size_t i = 0; i < n->size; i++) {
			float current_f = f_opt(g, n->neighbors[i], v);
			if(!fifo_in(n->neighbors[i])) {
				if(current_f < best_f) {
					solution_destruct(best_s);
					best_f = current_f;
					best_s = solution_copy(n->neighbors[i]);
				}
				if(fifo_full())
					solution_destruct(fifo_popfree());
				fifo_push(solution_copy(n->neighbors[i]));
			}
		}

		neighborhood_destruct(n);
	}

	fifo_del();
	return best_s;
}

static bool fifo_in(struct solution* s) {
	if(in == NULL) return false;
	fifo* it = in;
	while(it != NULL) {
		if(solution_eq(s, it->e))
			return true;
		it = it->nxt;
	}
	return false;
}

static struct solution* fifo_popfree() {
	assert(out != NULL);
	struct solution* s = out->e;
	fifo *bflst = out->prv;
	if(bflst != NULL)
		bflst->nxt = NULL;
	free(out);
	fifo_size--;
	out = bflst;
	return s;
}

static void fifo_push(struct solution *s) {
	fifo *newin = malloc(sizeof(fifo));
	assert(newin != NULL);
	newin->e = s;
	newin->prv = NULL;
	newin->nxt = in;
	if(in != NULL) {
		in->prv = newin;
	} else
		out = newin;
	in = newin;
	fifo_size++;
}

static void fifo_del() {
	while(out != NULL) {
		struct solution* s = fifo_popfree();
		solution_destruct(s);
	}
}
