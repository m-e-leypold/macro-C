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
m4_include(`m5.m4')
m4_define({MCPP_START},{M5_DEFINITION_MODE{}m4_changecom()M5_PUSH_MODE(M5_OUTPUT)m4_dnl})

m4_define({MCPP_PREFIX},{ok_ok_})
m4_define({MCPP_DEF_SYMBOL},{m4_define({_}{$1}{_},MCPP_PREFIX{$1})})

m4_define({MCPP_NEW_SYMBOL},{M5_PUSH_MODE(M5_INTERNAL)MCPP_PREFIX{$1}MCPP_DEF_SYMBOL({$1})M5_POP_MODE()})

m4_define({MCPP_INSTANCE_BEGIN},{M5_PUSH_MODE(M5_DEFINITION)
	m4_pushdef({MCPP_TEMPLATE_FILE},{$2})
	m4_pushdef({MCPP_MODULE_NAME},{$1})
	m4_pushdef({MCPP_PREFIX},{$1}{{_}})
	m4_pushdef({end},{MCPP_INSTANCE_END()m4_dnl})
	M5_POP_MODE()})

m4_define({MCPP_INSTANCE_END},{M5_DEFINITION_MODE()
	m4_popdef({end})
	M5_OUTPUT_MODE()m4_include(MCPP_TEMPLATE_FILE)
	M5_DEFINITION_MODE()
	m4_popdef({MCPP_TEMPLATE_FILE})
	M5_OUTPUT_MODE()})

m4_define({MCPP_INSTANCE_IMPLEMENTATION_BEGIN},{M5_DEFINITION_MODE()
	m4_pushdef({MCPP_TEMPLATE_FILE},{$2})
	m4_pushdef({MCPP_INTERFACE_FILE},{$1})
	m4_pushdef({end},{MCPP_INSTANCE_IMPLEMENTATION_END()m4_dnl})
	M5_OUTPUT_MODE()m4_include(MCPP_INTERFACE_FILE)})


m4_define({MCPP_INSTANCE_IMPLEMENTATION_END},{M5_DEFINITION_MODE()
	m4_popdef({end})
        M5_OUTPUT_MODE()m4_include(MCPP_TEMPLATE_FILE)
	M5_DEFINITION_MODE()
	m4_popdef({MCPP_TEMPLATE_FILE})
	M5_OUTPUT_MODE()})


// XXX don't want OUTPUT here, instead INPUT_MODE (read only ...)

m4_define({_},{MCPP_NEW_SYMBOL($1)})
m4_define({instance},{M5_STRING_MODE()MCPP_INSTANCE_BEGIN($*)})
m4_define({instance_implementation},{M5_STRING_MODE()MCPP_INSTANCE_IMPLEMENTATION_BEGIN($*)})


m4_changequote()

MCPP_START



