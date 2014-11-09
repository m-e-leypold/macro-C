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
 * ---------------------------------------------------------------------
 *
 */

#ifndef H_INCLUDED_LSD_MACRO_CLOSURES
#define H_INCLUDED_LSD_MACRO_CLOSURES

#include "lid-machinery.h"

// Types and generic operations

#define Closure_type(name,...)    name##_calltype(void*,int);  struct  name; typedef struct name name; \
  struct name {                   \
     name##_calltype* call;       \
     void* data;                  \
   }

#define call_Closure(c,...) c.call(c.data,__VA_ARGS__)
#define free_Closure(c,...) free(c.data)

// Implementations

#define declare_Closure_implementation(name, closuretype, datatype, ...)   \
  typedef     closuretype             name##_closuretype;                  \
  typedef     datatype                name##_datatype;                     \
  int         name##_evaluate         (datatype* datatype, __VA_ARGS__)    \

#define define_Closure_implementation(name, closuretype, datatype, ...)     \
  declare_Closure_implementation(name, closuretype, datatype, __VA_ARGS__); \
  int         name##_dispatch         (void* data,__VA_ARGS__)          { return name##_evaluate(data,num); }               \
  closuretype name##_create           (datatype* r)                     { closuretype c = {&name##_dispatch,r}; return c; } \
  int         name##_evaluate         (datatype* datatype, __VA_ARGS__)   /* ... { ... evaluation body ... } */  

// Constructors

#define declare_Closure_constructor define_Closure_constructor

#define define_Closure_constructor(name,implementation_name,...) \
   typedef implementation_name##_datatype name##_##datatype; \
   implementation_name##_closuretype name##_##create(name##_##datatype* DATA, __VA_ARGS__)

#define static_Closure_constructor(name,implementation_name,...) \
   typedef implementation_name##_datatype name##_##datatype; \
   inline static implementation_name##_closuretype name##_##create(name##_##datatype* DATA, __VA_ARGS__)

#define return_Closure(implementation) return implementation##_##create(DATA)

#define LOCAL_CLOSURE(name,constructor,lid,...)     name;  constructor##_##datatype   lid;  name = constructor##_##create(&(lid), __VA_ARGS__);
#define local_Closure(name,constructor,...) LOCAL_CLOSURE(name,constructor,NEW_LID(constructor),__VA_ARGS__)

#define NEW_CLOSURE(constructor,...)  constructor##_##create(malloc(sizeof(constructor##_##datatype)), __VA_ARGS__ );
#define new_Closure(constructor,...)  NEW_CLOSURE(constructor,__VA_ARGS__)

// TODO: Macros to define allocators like new_multiplier(...) 
// TODO: Sep declaration and definition.
// TODO: NULL argument variant.

#endif
