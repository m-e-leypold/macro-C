m4_dnl
m4_dnl   Macro-C -- Preprocessor based language extensions to C99.
m4_dnl   Copyright (C) 2014 -- M E Leypold
m4_dnl   
m4_dnl   This program is free software: you can redistribute it and/or modify
m4_dnl   it under the terms of the GNU General Public License as published by
m4_dnl   the Free Software Foundation, either version 3 of the License, or
m4_dnl   (at your option) any later version.
m4_dnl   
m4_dnl   This program is distributed in the hope that it will be useful,
m4_dnl   but WITHOUT ANY WARRANTY; without even the implied warranty of
m4_dnl   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
m4_dnl   GNU General Public License for more details.
m4_dnl   
m4_dnl   You should have received a copy of the GNU General Public License
m4_dnl   along with this program.  If not, see <http://www.gnu.org/licenses/>.
m4_dnl   
m4_divert(-1)
# this is the bootstrap

m4_define(`M5_RBRACE',`}')m4_define(`M5_LBRACE',`{')
m4_define(`M5_QRBRACE',`{}}')m4_define(`M5_QLBRACE',`{{}')
m4_changequote(`{',`}')

# we're basically in definition mode now (see below)

# Some basic stuff
m4_define({M5_PROTECT},{$@})
m4_define({M5_EVAL},{$*})
m4_define({M5_QUOTE},{{$@}})

# now we're defining the different modes

m4_define({M5_DEFINITION_MODE},{m4_changequote()m4_changequote({,})m4_divert(-1)})
	#
	# "definition mode" is used to define commands. No output is
	# produced in definition mode, braces are quotes.

m4_define({M5_OUTPUT_MODE},{m4_changequote()m4_divert(0)})
	#
	# "output mode" copies stuff to output. There are no quotes active.
	# This is the mode we use for straight forward expansion.

m4_define({M5_INTERNAL_MODE},{m4_changequote()m4_changequote({,})m4_divert(0)})
	#
	# "internal mode" still produces output, but braces are active
	# as quotes. We're using this in cases were we still want to
	# produce output but need some quoting to control expansion.

m4_define({M5_STRING_MODE},{m4_changequote()m4_changequote(",")m4_divert(0)})
	#
	# We use "string mode" as an ad hoc way to read string
	# arguments and remove their quotes. String mode is not very
	# smart, so we use it rarely.


# now switch to definition mode

m4_define({M5_CURRENT_MODE},{{M5_DEFINITION}})
m4_define({M5_CURRENT_DIVERSION},{divnum})

# push/pop mode mechanics

m4_define({M5_PUSH_MODE},{M5_DEFINITION_MODE
	m4_pushdef({M5_CURRENT_MODE},{$1})
	$1_MODE()})

m4_define({M5_POP_MODE},{M5_DEFINITION_MODE
	m4_popdef({M5_CURRENT_MODE})
	M5_EVAL(M5_CURRENT_MODE{}_MODE())})

