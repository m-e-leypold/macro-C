/* Macro-C -- Preprocessor based language extensions to C99.    -*- mode: c -*-
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

#ifndef H_INCLUDED_LSD_MACRO_C_LID_MACHINERY
#define H_INCLUDED_LSD_MACRO_C_LID_MACHINERY

#define LID_APPLY(M,...)          M(__VA_ARGS__)
#define LID_PASTE_STRAIGHT(x,y)   x##_##y
#define LID_DECORATE(x)           LID_APPLY(LID_PASTE,x,__LINE__)

#ifndef LID_PASTE
#  define LID_PASTE               LID_PASTE_STRAIGHT
#endif

#ifndef NEW_LID
#  define NEW_LID(x)              LID_DECORATE(_local_##x)
#endif

#endif


