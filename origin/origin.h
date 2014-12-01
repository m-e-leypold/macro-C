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

#ifndef H_INCLUDED_LSD_MACRO_C_ORIGIN
#define H_INCLUDED_LSD_MACRO_C_ORIGIN

typedef struct origin {
  const char* source_file;
  int         source_line;
} origin;

static inline origin origin_make( const char* file , int line ){
  origin o = {file,line} ;
  return o;
}

#define ORIGIN_HERE      origin_make(__FILE__,__LINE__)
#define ORIGIN_VALUES(o) o.source_file, o.source_line
#define ORIGIN_FIELDS    const char* source_file, int source_line
#define static_Origin(o) static origin o = { __FILE__, __LINE__ }

#endif
