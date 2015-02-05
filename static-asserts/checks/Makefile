# Macro-C -- Preprocessor based language extensions to C99.
# Copyright (C) 2014 -- M E Leypold
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

check: check1 check2 check3 check4

CPPFLAGS = -I ../../macro-machinery -I ..
CFLAGS   = -Wall -Werror -pedantic -std=c99

check1: fail.c ../static-asserts.h 
	! $(CC) $(CPPFLAGS) $(CFLAGS) -o fail fail.c 2>/dev/null

check2: ok.c ../static-asserts.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -o ok ok.c

check3: CPPFLAGS+=-DNO_STATIC_ASSERTS
check3: ok.c ../static-asserts.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -o fail fail.c 

check4: CPPFLAGS+=-DNO_STATIC_ASSERTS
check4: ok.c ../static-asserts.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -o ok ok.c


clean:
	rm -f fail ok *~ fail.log
