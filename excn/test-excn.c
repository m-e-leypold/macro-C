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

#define ASSERT_GETS_EXECUTED
#define NOT_REACHED (!"REACHED")
#define ASSERT_NOT_REACHED assert(NOT_REACHED)

// --- the program follows

EXCEPTION(ex1);
EXCEPTION(ex2);
EXCEPTION(ex3);

void do_something(exception ex){
  printf("doing something -- an error happens\n");
  RAISE(ex);
  assert(NOT_REACHED);
}

void uncaught_exception(int tag){
  printf("uncaught exception: %d - exiting gracefully\n",tag);
  exit(0);
}

int main(){
  
  printf("Testcase: No Exception (TRYING,FINALLY)\n");

  EXCEPTIONS{
    TRY {
      printf("TRYING\n");
    }
    CATCH(ex1){
      printf("CATCHING\n");
      assert(NOT_REACHED);
    }
    ELSE {
      printf("ELSE\n");
      assert(NOT_REACHED);
    }
    FINALLY {
      printf("FINALLY\n");
    }    
  }

  printf("Testcase: Caught Exception (TRYING,CAUGHT,FINALLY)\n");

  EXCEPTIONS{
    TRY {
      printf("TRYING\n");
      do_something(ex3);
    }
    CATCH(ex1,ex3){
      printf("CATCHING\n");
    }
    ELSE {
      printf("ELSE\n");
      assert(NOT_REACHED);
    }
    FINALLY {
      printf("FINALLY\n");
    }    
  }

  printf("Testcase: Nested handlers\n");

  EXCEPTIONS{
    TRY {
      printf("TRYING\n");
      do_something(ex2);
    }

    CATCH(ex1,ex2){
      printf("CATCHING\n");

      EXCEPTIONS{
	TRY { printf("TRYING2\n");
	  do_something(ex2); 
	}
	CATCH(ex2){
	  printf("CATCHING\2n");
	} ELSE {
	  printf("ELSE2\n");
	  assert(NOT_REACHED);
	}
	FINALLY {
	  printf("FINALLY2\n");
	}
      }

    }
    ELSE {
      printf("ELSE\n");
      assert(NOT_REACHED);
    }
    FINALLY {
      printf("FINALLY\n");
    }    
  }

  excn_install_panic_handler(uncaught_exception);

  printf("Testcase: Uncaught Exception (TRYING,ELSE,FINALLY)\n");

  EXCEPTIONS{
    TRY {
      printf("TRYING\n");
      do_something(ex3);
    }
    CATCH(ex1,ex2){
      printf("CATCHING\n");
      assert(NOT_REACHED);
    }
    ELSE {
      printf("ELSE\n");
    }
    FINALLY {
      printf("FINALLY\n");
    }    
  }

  assert(NOT_REACHED);
}


