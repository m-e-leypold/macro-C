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
 * ------------------------------------------------------------------
 *
 * Usage:
 * 
 *   EXCEPTIONS {
 *       ... local variables;
 *     TRY {
 *       ... statements;
 *     }
 *     CATCH(exception, ...) {
 *       ... statements;
 *     }
 *     ELSE {
 *       ... statements;
 *     }
 *     FINALLY {
 *       ... statements;
 *     }
 *   }
 * 
 *
 * where
 *
 *   EXCEPTIONS -- establishes an exception handling context
 *   TRY        -- execute statements
 *   CATCH      -- handle named exceptions, don't reraise exeception
 *   ELSE       -- execute, if other exceptions have been thrown, exceptions will be reraised
 *   FINALLY    -- executed in any case (normal block exit, stack unwind)
 */

#ifndef H_INCLUDED_LSD_MACRO_C_EXCN
#define H_INCLUDED_LSD_MACRO_C_EXCN

#include <setjmp.h>

struct  exception_descriptor;
typedef struct exception_descriptor exception_descriptor;
typedef exception_descriptor* exception;

#define EXCEPTION(x) \
           exception_descriptor x##_excn_descriptor = {.tag = 0 }; \
           exception x = &(x##_excn_descriptor)

struct  excn_handler;
typedef struct excn_handler excn_handler;

#define EXCEPTIONS \
          for (                                                        \
            excn_handler __excn_handler__ = { .tried = 0, .tag = 0, .handled = 0 };  \
  	    !excn_propagate_or_pop(&__excn_handler__);                             \
          ) 

int 
excn_propagate_or_pop(excn_handler* eh);

#define TRY  \
  excn_push_handler(&__excn_handler__); \
  if(!EXCN_TRY_RAISED(__excn_handler__)) 

#define EXCN_TRY_RAISED(buf) \
  ((buf.tag=setjmp(buf.env)))

void 
excn_push_handler (excn_handler* __excn_handler__);

#define CATCH(...)							\
  exception catch_list[] = { __VA_ARGS__ };				\
  int catch_list_size = sizeof(catch_list)/sizeof(exception);	        \
  if( excn_in_catchlist(&__excn_handler__,catch_list,catch_list_size) )

exception 
excn_in_catchlist( excn_handler* eh, exception* catchlist, int catchlist_size);

#define ELSE if(!excn_handled(&__excn_handler__))

int 
excn_handled ( excn_handler* eh );

#define FINALLY if(1)

#define RAISE(x)  excn_raise(x)
void 
excn_raise(exception ex);

typedef void (*excn_panic_handler)(int);

void 
excn_install_panic_handler(excn_panic_handler handler);

/* 
 * ------------------------------------------------------------------------
 * Everything below this line is strictly internal to the exception module.
 * ------------------------------------------------------------------------
 */

typedef struct exception_descriptor {
  int   tag;
  const char* message;
} exception_descriptor;

struct excn_handler {
  int        tried;  // actually: done
  int        tag;  
  exception  handled;
  exception  caught;
  jmp_buf env;

  struct excn_handler* prev_handler;
};

#endif /* H_INCLUDED_LSD_MACRO_C_EXCN */
