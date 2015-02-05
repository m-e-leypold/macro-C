

#include "static-asserts.h"

typedef int bar;
STATIC_ASSERT( sizeof(bar)<4 ); /* This is expected to fail */

int main(){
  return 0;
}
