#include "static-asserts.h"

typedef int bar;

STATIC_ASSERT( sizeof(bar) >= 4 );

int main(){
  return 0;
}
