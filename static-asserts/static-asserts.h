#ifndef H_INCLUDED_LSD_MACRO_C_STATIC_ASSERTS
#define H_INCLUDED_LSD_MACRO_C_STATIC_ASSERTS

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
 */

#include <lid-machinery.h>

#ifndef NO_STATIC_ASSERTS
#  define STATIC_ASSERT_WITH(id,cond) unsigned char id = ((cond)?(0xFF):(0xFFF))
#  define STATIC_ASSERT(cond) STATIC_ASSERT_WITH(NEW_LID(STATIC_ASSERTS_VAR),cond)
#else
#  define STATIC_ASSERT(cond) void NEW_LID(STATIC_ASSERTS_VAR)()
#endif

#endif
