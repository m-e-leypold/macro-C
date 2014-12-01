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

#ifndef H_INCLUDED_LSD_MACRO_C_ORIGIN_PRINT
#define H_INCLUDED_LSD_MACRO_C_ORIGIN_PRINT

#include "origin.h"
#include <stdio.h>

#define ORIGIN_FMT "%s: %d: "
#define ORIGIN_FMT_EXTENDED "file `%s', line %d"

int origin_fprintf(FILE* file, const char* fmt,origin o);
int origin_fprint(FILE* file, origin o);
int origin_print(origin o);

#endif
