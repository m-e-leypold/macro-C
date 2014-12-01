m4_divert(-1)
# this is the bootstrap

m4_define(`M5_RBRACE',`}')m4_define(`M5_LBRACE',`{')
m4_define(`M5_QRBRACE',`{}}')m4_define(`M5_QLBRACE',`{{}')
m4_changequote(`{',`}')

# we're in definition mode now (see below)

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

