#include <stdio.h>
#include "origin.h"
#include "origin-print.h"



int main(){
  
  static_Origin(tag);          // create a named origin tag
  
  origin_print(ORIGIN_HERE);   // capture and print origin info
  printf("\n");
  origin_print(ORIGIN_HERE);
  printf("\n");

  origin_print(tag);
  printf("\n");
  
  return 0;
}

