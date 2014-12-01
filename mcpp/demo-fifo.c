#include "int_fifo.h"
#include "float_fifo.h"

#include <stdio.h>

int main(){
  int_fifo_T    f = FIFO_INIT;
  float_fifo_T  g = FIFO_INIT;

  for (int i = 0 ; i<10; i++ ){
    int_fifo_enqueue  ( &f ,i     );
    float_fifo_enqueue( &g ,0.7*i );
  }
  
  while ( int_fifo_size(&f) ){
    
    int   n = int_fifo_dequeue  (&f);
    float r = float_fifo_dequeue(&g);

    printf("%d * 0.7 = %0.2f\n",n,r);
  }

  return 0;
}
