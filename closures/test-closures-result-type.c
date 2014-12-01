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

typedef float Closure_type(Transformation, float);  

structdef(Factor) {                     // a type over which we want to close
  float factor;
};

define_Closure_implementation(Multiplier, Transformation, Factor, float num){   // An implementation of Transformation, named Multiplier
  return num * Factor->factor;
}

define_Closure_constructor  (multiplier,Multiplier,float factor)   // this is how we init closure data
{
  DATA->factor = factor;
  return_Closure(Multiplier);
}

int main(){

  Factor d;
  Transformation c3 = multiplier_create(&d,3.2);                    

  Transformation c2 = new_Closure( multiplier, 7.4 );
  
  Transformation local_Closure( c,  multiplier, 5.5);
  
  int n = call_Closure(c,15.1);
  printf("n = %d\n",n);

  n = call_Closure(c2,20.1);
  printf("n = %d\n",n);

  n = call_Closure(c3,27.1);
  printf("n = %d\n",n);
  
  free_Closure(c2); 

  return 0;
}
