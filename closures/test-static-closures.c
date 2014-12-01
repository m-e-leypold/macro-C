/* Macro-C -- Preprocessor based language extensions to C99.
 * Copyright (C) 2014 -- M E Leypold
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * --------------------------------------------------------------------
 *
 * This file demonstrates the use of closures.h.
 */

#include <malloc.h>
#include <stdio.h>
#include "typedef-machinery.h"
#include "closures.h"

typedef int Closure_type(IntListener, int);  

structdef(IntSum) {                     // a type over which we want to close
  int sum;
};

declare_Closure_implementation(Accumulator, IntListener, IntSum, int num); 

define_Closure_implementation(Accumulator, IntListener, IntSum, int num){
  IntSum->sum = IntSum->sum + num;
  printf("Sum: %d\n",IntSum->sum);
  return IntSum->sum;
}

declare_Closure_constructor(accumulator,Accumulator,int startval);

define_Closure_constructor(accumulator,Accumulator,int startval)
{
  printf("Constructing!\n");
  DATA->sum = startval;
  return_Closure(Accumulator);
}

int foo(){

  IntListener static_Closure( c,  accumulator, 10);

  printf("Tracing!\n");
  int n = call_Closure(c,15);
  return 0;
}


int main(){
  foo();
  foo();
  foo();
  return 0;
}
