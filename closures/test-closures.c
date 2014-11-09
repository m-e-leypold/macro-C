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

typedef int Closure_type(Transformation, int);  

    // This defines a closure type. Closure types are characterized by
    // their arguments with which the closure can be called, and the
    // result they return. A closure type has a name (hier
    // Transformation), so it can be referenced by later definitions.
    //
    // The type I define here is called 'Transformation'. It takes an
    // 'int' and returns another int (actually boring).
    //
    // Typically it will be called with call_Closure() like this:
    //
    //     int result = call_Closure(c, 17);


structdef(Factor) {                     // a type over which we want to close
  int factor;
};

    // A closure encapsulates internal state or data which it uses to
    // calculate it's result. In principle you can take any type here
    // you need: We're using a fancy structdef() here to define a
    // structure for this purpose.

declare_Closure_implementation(Multiplier, Transformation, Factor, int num);  // typically done in a header file, here optional

define_Closure_implementation(Multiplier, Transformation, Factor, int num){   // An implementation of Transformation, named Multiplier
  return num * Factor->factor;
}

    // A closure implementation encapsulates State of a specific type
    // (hier Factor) to provide a closure of a specific type (here
    // Multiplier). The parameter list given corresponds to the
    // paremeters that are given when calling the closure: They must
    // correspond to what has been declared when defining the closure
    // type.
    //
    // The body contains the code to calculate the result from the
    // state and from the parameters. Note, that the state here is
    // referenced by the name of the state type (Factor).

declare_Closure_constructor (multiplier,Multiplier,int factor);  // typically done in a header file, here optional

define_Closure_constructor  (multiplier,Multiplier,int factor)   // this is how we init closure data
{
  DATA->factor = factor;
  return_Closure(Multiplier);
}
    // A constructor initializes the state record encapsulated in a
    // closure. You can have multiple constructors for a given state
    // record type and a given implementation type.

    // For technical reasons you've to explicitely return the closure
    // reference with return_Closure(closuretype). Contrary to the
    // Closure_implementation, the state record is here called DATA.


int main(){

  // After having defined a closure type, an implementation and a
  // constructor, there are thre methods to construct a closure.

  // The most explicit is, to allocate a state recorde and use
  // <<constructor>>_create() to package into a closure reference of
  // the associated type. 
  
  // This is the most verbose form also, but grants the most freedom,
  // e.g. in case you need to clean up the state record after use.
  
  Factor d;
  Transformation c3 = multiplier_create(&d,3);                     // explicitely assign data record.
     
  // Using new_Closure allocates the state record at the heap. This
  // works pretty well if you want to use / can use dynamic memory
  // management and do not need to clean up the state record
  // (de-allocation is enough cleanup). You have to use free_Closure
  // to free the closure state record.

  Transformation c2 = new_Closure( multiplier, 7 );                // allocate data record implicitely.

  // Most tricky, but very useful is local_Closure, which allocates a
  // state record of the appropriate type for the given constructor in
  // the local scope and constructs a closure over it. This only works
  // as a "downward closure" -- you cannot pass the closure reference
  // upwards, but downwards is no problem. Again no explicit cleanup
  // of the state record is possible, but this works without dynamic
  // memory allocation.

  Transformation local_Closure( c,  multiplier, 5);                // implicitely create data record as local variable.

  int n = call_Closure(c,15);
  printf("n = %d\n",n);

  n = call_Closure(c2,20);
  printf("n = %d\n",n);

  n = call_Closure(c3,27);
  printf("n = %d\n",n);
  
  free_Closure(c2);                                                // free a dynamically allocated closure

  return 0;
}
