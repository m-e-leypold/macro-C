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
 */

#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <assert.h>
#include "excn.h"

/* See excn.h: This is how the excn_handler structure looks like.

   struct excn_handler {
     int        tried;  // actually: done
     int        tag;  
     exception  handled;
     jmp_buf    env;

     struct excn_handler* prev_handler;
   };

   #define EXCEPTIONS \
          for ( excn_handler __excn_handler__ = ...;  !excn_propagate_or_pop(&__excn_handler__); ) 
*/

static inline 
int 
excn_pending ( excn_handler* eb ){
  return (eb->tag) && (!eb->handled);
}

int 
excn_handled ( excn_handler* eb ){
  return !eb->tag || eb->handled!=0;
}

static inline void 
raise_tag(int tag);

static inline void 
excn_pop_handler (excn_handler* eb);

int excn_propagate_or_pop(excn_handler* eb){ 
  if (!eb->tried){
    eb->tried = 1;
    return 0;
  } else {
    excn_pop_handler(eb);
    if (excn_pending (eb)){                
      raise_tag(eb->tag);
      
    }
    return 1;
  }
}

/* Per thread structures.  This version doesn't do PTS per thread,
   actually, but everything is already prepared. 

   - Replace 'control_block.' by get_control_block();
   - Base that on thread local data.
   - Protect excn_count (and the exception definition chain) by a mutex

   - Maybe cache the controlblock in the excn_handler => only have to
     get it once per EXCPETION[} block execution.
*/

static void 
default_panic_handler(int); 

typedef struct per_thread_structure {
  excn_handler*      last_handler ;
  excn_panic_handler panic_handler;
} per_thread_structure;

static per_thread_structure control_block = { 0, default_panic_handler };

static inline void
panic(int tag);

void excn_push_handler (excn_handler* eb){
  eb->prev_handler = control_block.last_handler; control_block.last_handler = eb;
}

static inline void 
excn_pop_handler (excn_handler* eb){
  assert(control_block.last_handler);
  control_block.last_handler = control_block.last_handler->prev_handler;
}

static void 
default_panic_handler(int tag)
{
  printf("Panic: Uncaught exception / no handler for: %d\n", tag);
  fflush(stderr);
  fflush(stdout);
  abort();
}

void 
excn_install_panic_handler(excn_panic_handler handler){
  control_block.panic_handler = handler;
}

static inline void 
panic(int tag){
  (*(control_block.panic_handler))(tag);
  abort();
}


/* 
 *   typedef struct exception_descriptor {
 *     int   tag;
 *     const char* message;
 *   } exception_descriptor;
 *   
 *   typedef exception_descriptor* exception;
 * 
 *  #define EXCEPTION(x)						\
 *         exception_descriptor x##_excn_descriptor = {.tag = 0 };	\
 *         exception x = &(x##_excn_descriptor)
 */

static int excn_count = 0; 

static inline
void init_excn(exception ex){
  if (ex->tag) return;
  excn_count++;
  ex->tag=excn_count;
}

/* #define RAISE(x)  excn_raise(x) 
 */

static inline void 
raise_tag(int tag){
  if (!control_block.last_handler) panic(tag);
  longjmp(control_block.last_handler->env,tag);
}

void excn_raise(exception ex){
  init_excn(ex);
  raise_tag(ex->tag);
}

/*   
 *   #define CATCH(...)	\
 *     exception catch_list[] = { __VA_ARGS__ }; *int catch_list_size = sizeof(catch_list)/sizeof(exception); \
 *     if( excn_in_catchlist( ... ) )
 */

exception 
excn_in_catchlist( excn_handler* eb, exception* catchlist, int catchlist_size)
{
  if (!eb->tag) return 0;
  for (int i=0; i<catchlist_size; i++){
    exception ex = catchlist[i];
    init_excn(ex);
    if (eb->tag == ex->tag){
      eb->handled =  ex;
      return ex;
    }   
  }
  return 0;
}


