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

default: help

-include $(shell mklib build-everything-now.mklib)
EXTRA-IGNORE-DIRECTORIES = labnet Release experiments mcpp static-asserts/checks
CFLAGS = -std=c99 -O3 
$(BUILD-EVERYTHING-NOW)

USAGE = \
|                                                                 \
|  Building $(NAME): Run 'make <target>', where targets are       \
|                                                                 \
|  help     -- to get this help text                              \
|                                                                 \
|  all      => examples.                                          \
|  clean    -- remove editor backups.                             \
|                                                                 \
|  Note, that there is no way to install code (currently). See    \
|  README for details on using this library.                      \
|                                                                 \

examples:
	if ! test -d example ; then exit 0; fi 
	cd example && make 

help:
	@set -e
	@echo
	@echo "$(USAGE)" | sed 's/ |/\n/g' | tail -n +2 | sed 's|[ \t]*$$||'
	@echo


# The following rule set is not useful outside the authors network.
#
-include labnet/Labnet.mk



