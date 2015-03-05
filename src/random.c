#include <random.h>

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

static bool init = false;

unsigned random_get_unsigned(unsigned max){
  if(!init){
    srand(time(NULL));
    init = true;
  }
  return rand() % max;
}
