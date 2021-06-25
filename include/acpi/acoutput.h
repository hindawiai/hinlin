<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acoutput.h -- debug output
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACOUTPUT_H__
#घोषणा __ACOUTPUT_H__

/*
 * Debug levels and component IDs. These are used to control the
 * granularity of the output of the ACPI_DEBUG_PRINT macro -- on a
 * per-component basis and a per-exception-type basis.
 */

/* Component IDs are used in the global "DebugLayer" */

#घोषणा ACPI_UTILITIES              0x00000001
#घोषणा ACPI_HARDWARE               0x00000002
#घोषणा ACPI_EVENTS                 0x00000004
#घोषणा ACPI_TABLES                 0x00000008
#घोषणा ACPI_NAMESPACE              0x00000010
#घोषणा ACPI_PARSER                 0x00000020
#घोषणा ACPI_DISPATCHER             0x00000040
#घोषणा ACPI_EXECUTER               0x00000080
#घोषणा ACPI_RESOURCES              0x00000100
#घोषणा ACPI_CA_DEBUGGER            0x00000200
#घोषणा ACPI_OS_SERVICES            0x00000400
#घोषणा ACPI_CA_DISASSEMBLER        0x00000800

/* Component IDs क्रम ACPI tools and utilities */

#घोषणा ACPI_COMPILER               0x00001000
#घोषणा ACPI_TOOLS                  0x00002000
#घोषणा ACPI_EXAMPLE                0x00004000
#घोषणा ACPI_DRIVER                 0x00008000
#घोषणा DT_COMPILER                 0x00010000
#घोषणा ASL_PREPROCESSOR            0x00020000

#घोषणा ACPI_ALL_COMPONENTS         0x0001FFFF
#घोषणा ACPI_COMPONENT_DEFAULT      (ACPI_ALL_COMPONENTS)

/* Component IDs reserved क्रम ACPI drivers */

#घोषणा ACPI_ALL_DRIVERS            0xFFFF0000

/*
 * Raw debug output levels, करो not use these in the ACPI_DEBUG_PRINT macros
 */
#घोषणा ACPI_LV_INIT                0x00000001
#घोषणा ACPI_LV_DEBUG_OBJECT        0x00000002
#घोषणा ACPI_LV_INFO                0x00000004
#घोषणा ACPI_LV_REPAIR              0x00000008
#घोषणा ACPI_LV_TRACE_POINT         0x00000010
#घोषणा ACPI_LV_ALL_EXCEPTIONS      0x0000001F

/* Trace verbosity level 1 [Standard Trace Level] */

#घोषणा ACPI_LV_INIT_NAMES          0x00000020
#घोषणा ACPI_LV_PARSE               0x00000040
#घोषणा ACPI_LV_LOAD                0x00000080
#घोषणा ACPI_LV_DISPATCH            0x00000100
#घोषणा ACPI_LV_EXEC                0x00000200
#घोषणा ACPI_LV_NAMES               0x00000400
#घोषणा ACPI_LV_OPREGION            0x00000800
#घोषणा ACPI_LV_BFIELD              0x00001000
#घोषणा ACPI_LV_TABLES              0x00002000
#घोषणा ACPI_LV_VALUES              0x00004000
#घोषणा ACPI_LV_OBJECTS             0x00008000
#घोषणा ACPI_LV_RESOURCES           0x00010000
#घोषणा ACPI_LV_USER_REQUESTS       0x00020000
#घोषणा ACPI_LV_PACKAGE             0x00040000
#घोषणा ACPI_LV_EVALUATION          0x00080000
#घोषणा ACPI_LV_VERBOSITY1          0x000FFF40 | ACPI_LV_ALL_EXCEPTIONS

/* Trace verbosity level 2 [Function tracing and memory allocation] */

#घोषणा ACPI_LV_ALLOCATIONS         0x00100000
#घोषणा ACPI_LV_FUNCTIONS           0x00200000
#घोषणा ACPI_LV_OPTIMIZATIONS       0x00400000
#घोषणा ACPI_LV_PARSE_TREES         0x00800000
#घोषणा ACPI_LV_VERBOSITY2          0x00F00000 | ACPI_LV_VERBOSITY1
#घोषणा ACPI_LV_ALL                 ACPI_LV_VERBOSITY2

/* Trace verbosity level 3 [Thपढ़ोing, I/O, and Interrupts] */

#घोषणा ACPI_LV_MUTEX               0x01000000
#घोषणा ACPI_LV_THREADS             0x02000000
#घोषणा ACPI_LV_IO                  0x04000000
#घोषणा ACPI_LV_INTERRUPTS          0x08000000
#घोषणा ACPI_LV_VERBOSITY3          0x0F000000 | ACPI_LV_VERBOSITY2

/* Exceptionally verbose output -- also used in the global "DebugLevel"  */

#घोषणा ACPI_LV_AML_DISASSEMBLE     0x10000000
#घोषणा ACPI_LV_VERBOSE_INFO        0x20000000
#घोषणा ACPI_LV_FULL_TABLES         0x40000000
#घोषणा ACPI_LV_EVENTS              0x80000000
#घोषणा ACPI_LV_VERBOSE             0xF0000000

/*
 * Debug level macros that are used in the DEBUG_PRINT macros
 */
#घोषणा ACPI_DEBUG_LEVEL(dl)        (u32) dl,ACPI_DEBUG_PARAMETERS

/*
 * Exception level -- used in the global "DebugLevel"
 *
 * Note: For errors, use the ACPI_ERROR or ACPI_EXCEPTION पूर्णांकerfaces.
 * For warnings, use ACPI_WARNING.
 */
#घोषणा ACPI_DB_INIT                ACPI_DEBUG_LEVEL (ACPI_LV_INIT)
#घोषणा ACPI_DB_DEBUG_OBJECT        ACPI_DEBUG_LEVEL (ACPI_LV_DEBUG_OBJECT)
#घोषणा ACPI_DB_INFO                ACPI_DEBUG_LEVEL (ACPI_LV_INFO)
#घोषणा ACPI_DB_REPAIR              ACPI_DEBUG_LEVEL (ACPI_LV_REPAIR)
#घोषणा ACPI_DB_TRACE_POINT         ACPI_DEBUG_LEVEL (ACPI_LV_TRACE_POINT)
#घोषणा ACPI_DB_ALL_EXCEPTIONS      ACPI_DEBUG_LEVEL (ACPI_LV_ALL_EXCEPTIONS)

/* Trace level -- also used in the global "DebugLevel" */

#घोषणा ACPI_DB_INIT_NAMES          ACPI_DEBUG_LEVEL (ACPI_LV_INIT_NAMES)
#घोषणा ACPI_DB_THREADS             ACPI_DEBUG_LEVEL (ACPI_LV_THREADS)
#घोषणा ACPI_DB_PARSE               ACPI_DEBUG_LEVEL (ACPI_LV_PARSE)
#घोषणा ACPI_DB_DISPATCH            ACPI_DEBUG_LEVEL (ACPI_LV_DISPATCH)
#घोषणा ACPI_DB_LOAD                ACPI_DEBUG_LEVEL (ACPI_LV_LOAD)
#घोषणा ACPI_DB_EXEC                ACPI_DEBUG_LEVEL (ACPI_LV_EXEC)
#घोषणा ACPI_DB_NAMES               ACPI_DEBUG_LEVEL (ACPI_LV_NAMES)
#घोषणा ACPI_DB_OPREGION            ACPI_DEBUG_LEVEL (ACPI_LV_OPREGION)
#घोषणा ACPI_DB_BFIELD              ACPI_DEBUG_LEVEL (ACPI_LV_BFIELD)
#घोषणा ACPI_DB_TABLES              ACPI_DEBUG_LEVEL (ACPI_LV_TABLES)
#घोषणा ACPI_DB_FUNCTIONS           ACPI_DEBUG_LEVEL (ACPI_LV_FUNCTIONS)
#घोषणा ACPI_DB_OPTIMIZATIONS       ACPI_DEBUG_LEVEL (ACPI_LV_OPTIMIZATIONS)
#घोषणा ACPI_DB_PARSE_TREES         ACPI_DEBUG_LEVEL (ACPI_LV_PARSE_TREES)
#घोषणा ACPI_DB_VALUES              ACPI_DEBUG_LEVEL (ACPI_LV_VALUES)
#घोषणा ACPI_DB_OBJECTS             ACPI_DEBUG_LEVEL (ACPI_LV_OBJECTS)
#घोषणा ACPI_DB_ALLOCATIONS         ACPI_DEBUG_LEVEL (ACPI_LV_ALLOCATIONS)
#घोषणा ACPI_DB_RESOURCES           ACPI_DEBUG_LEVEL (ACPI_LV_RESOURCES)
#घोषणा ACPI_DB_IO                  ACPI_DEBUG_LEVEL (ACPI_LV_IO)
#घोषणा ACPI_DB_INTERRUPTS          ACPI_DEBUG_LEVEL (ACPI_LV_INTERRUPTS)
#घोषणा ACPI_DB_USER_REQUESTS       ACPI_DEBUG_LEVEL (ACPI_LV_USER_REQUESTS)
#घोषणा ACPI_DB_PACKAGE             ACPI_DEBUG_LEVEL (ACPI_LV_PACKAGE)
#घोषणा ACPI_DB_EVALUATION          ACPI_DEBUG_LEVEL (ACPI_LV_EVALUATION)
#घोषणा ACPI_DB_MUTEX               ACPI_DEBUG_LEVEL (ACPI_LV_MUTEX)
#घोषणा ACPI_DB_EVENTS              ACPI_DEBUG_LEVEL (ACPI_LV_EVENTS)

#घोषणा ACPI_DB_ALL                 ACPI_DEBUG_LEVEL (ACPI_LV_ALL)

/* Defaults क्रम debug_level, debug and normal */

#अगर_अघोषित ACPI_DEBUG_DEFAULT
#घोषणा ACPI_DEBUG_DEFAULT          (ACPI_LV_INIT | ACPI_LV_DEBUG_OBJECT | ACPI_LV_EVALUATION | ACPI_LV_REPAIR)
#पूर्ण_अगर

#घोषणा ACPI_NORMAL_DEFAULT         (ACPI_LV_INIT | ACPI_LV_DEBUG_OBJECT | ACPI_LV_REPAIR)
#घोषणा ACPI_DEBUG_ALL              (ACPI_LV_AML_DISASSEMBLE | ACPI_LV_ALL_EXCEPTIONS | ACPI_LV_ALL)

/*
 * Global trace flags
 */
#घोषणा ACPI_TRACE_ENABLED          ((u32) 4)
#घोषणा ACPI_TRACE_ONESHOT          ((u32) 2)
#घोषणा ACPI_TRACE_OPCODE           ((u32) 1)

/* Defaults क्रम trace debugging level/layer */

#घोषणा ACPI_TRACE_LEVEL_ALL        ACPI_LV_ALL
#घोषणा ACPI_TRACE_LAYER_ALL        0x000001FF
#घोषणा ACPI_TRACE_LEVEL_DEFAULT    ACPI_LV_TRACE_POINT
#घोषणा ACPI_TRACE_LAYER_DEFAULT    ACPI_EXECUTER

#अगर defined (ACPI_DEBUG_OUTPUT) || !defined (ACPI_NO_ERROR_MESSAGES)
/*
 * The module name is used primarily क्रम error and debug messages.
 * The __खाता__ macro is not very useful क्रम this, because it
 * usually includes the entire pathname to the module making the
 * debug output dअगरficult to पढ़ो.
 */
#घोषणा ACPI_MODULE_NAME(name)          अटल स्थिर अक्षर ACPI_UNUSED_VAR _acpi_module_name[] = name;
#अन्यथा
/*
 * For the no-debug and no-error-msg हालs, we must at least define
 * a null module name.
 */
#घोषणा ACPI_MODULE_NAME(name)
#घोषणा _acpi_module_name ""
#पूर्ण_अगर

/*
 * Ascii error messages can be configured out
 */
#अगर_अघोषित ACPI_NO_ERROR_MESSAGES
#घोषणा AE_INFO                         _acpi_module_name, __LINE__

/*
 * Error reporting. Callers module and line number are inserted by AE_INFO,
 * the plist contains a set of parens to allow variable-length lists.
 * These macros are used क्रम both the debug and non-debug versions of the code.
 */
#घोषणा ACPI_INFO(plist)                acpi_info plist
#घोषणा ACPI_WARNING(plist)             acpi_warning plist
#घोषणा ACPI_EXCEPTION(plist)           acpi_exception plist
#घोषणा ACPI_ERROR(plist)               acpi_error plist
#घोषणा ACPI_BIOS_WARNING(plist)        acpi_bios_warning plist
#घोषणा ACPI_BIOS_EXCEPTION(plist)      acpi_bios_exception plist
#घोषणा ACPI_BIOS_ERROR(plist)          acpi_bios_error plist
#घोषणा ACPI_DEBUG_OBJECT(obj,l,i)      acpi_ex_करो_debug_object(obj,l,i)

#अन्यथा

/* No error messages */

#घोषणा ACPI_INFO(plist)
#घोषणा ACPI_WARNING(plist)
#घोषणा ACPI_EXCEPTION(plist)
#घोषणा ACPI_ERROR(plist)
#घोषणा ACPI_BIOS_WARNING(plist)
#घोषणा ACPI_BIOS_EXCEPTION(plist)
#घोषणा ACPI_BIOS_ERROR(plist)
#घोषणा ACPI_DEBUG_OBJECT(obj,l,i)

#पूर्ण_अगर				/* ACPI_NO_ERROR_MESSAGES */

/*
 * Debug macros that are conditionally compiled
 */
#अगर_घोषित ACPI_DEBUG_OUTPUT

/*
 * If ACPI_GET_FUNCTION_NAME was not defined in the compiler-dependent header,
 * define it now. This is the हाल where there the compiler करोes not support
 * a __func__ macro or equivalent.
 */
#अगर_अघोषित ACPI_GET_FUNCTION_NAME
#घोषणा ACPI_GET_FUNCTION_NAME          _acpi_function_name

/*
 * The Name parameter should be the procedure name as a non-quoted string.
 * The function name is also used by the function निकास macros below.
 * Note: (स्थिर अक्षर) is used to be compatible with the debug पूर्णांकerfaces
 * and macros such as __func__.
 */
#घोषणा ACPI_FUNCTION_NAME(name)        अटल स्थिर अक्षर _acpi_function_name[] = #name;

#अन्यथा
/* Compiler supports __func__ (or equivalent) -- Ignore this macro */

#घोषणा ACPI_FUNCTION_NAME(name)
#पूर्ण_अगर				/* ACPI_GET_FUNCTION_NAME */

/*
 * Common parameters used क्रम debug output functions:
 * line number, function name, module(file) name, component ID
 */
#घोषणा ACPI_DEBUG_PARAMETERS \
	__LINE__, ACPI_GET_FUNCTION_NAME, _acpi_module_name, _COMPONENT

/* Check अगर debug output is currently dynamically enabled */

#घोषणा ACPI_IS_DEBUG_ENABLED(level, component) \
	((level & acpi_dbg_level) && (component & acpi_dbg_layer))

/*
 * Master debug prपूर्णांक macros
 * Prपूर्णांक message अगर and only अगर:
 *    1) Debug prपूर्णांक क्रम the current component is enabled
 *    2) Debug error level or trace level क्रम the prपूर्णांक statement is enabled
 *
 * November 2012: Moved the runसमय check क्रम whether to actually emit the
 * debug message outside of the prपूर्णांक function itself. This improves overall
 * perक्रमmance at a relatively small code cost. Implementation involves the
 * use of variadic macros supported by C99.
 *
 * Note: the ACPI_DO_WHILE0 macro is used to prevent some compilers from
 * complaining about these स्थिरructs. On other compilers the करो...जबतक
 * adds some extra code, so this feature is optional.
 */
#अगर_घोषित ACPI_USE_DO_WHILE_0
#घोषणा ACPI_DO_WHILE0(a)               करो a जबतक(0)
#अन्यथा
#घोषणा ACPI_DO_WHILE0(a)               a
#पूर्ण_अगर

/* DEBUG_PRINT functions */

#अगर_अघोषित COMPILER_VA_MACRO

#घोषणा ACPI_DEBUG_PRINT(plist)         acpi_debug_prपूर्णांक plist
#घोषणा ACPI_DEBUG_PRINT_RAW(plist)     acpi_debug_prपूर्णांक_raw plist

#अन्यथा

/* Helper macros क्रम DEBUG_PRINT */

#घोषणा ACPI_DO_DEBUG_PRINT(function, level, line, filename, modulename, component, ...) \
	ACPI_DO_WHILE0 (अणु \
		अगर (ACPI_IS_DEBUG_ENABLED (level, component)) \
		अणु \
			function (level, line, filename, modulename, component, __VA_ARGS__); \
		पूर्ण \
	पूर्ण)

#घोषणा ACPI_ACTUAL_DEBUG(level, line, filename, modulename, component, ...) \
	ACPI_DO_DEBUG_PRINT (acpi_debug_prपूर्णांक, level, line, \
		filename, modulename, component, __VA_ARGS__)

#घोषणा ACPI_ACTUAL_DEBUG_RAW(level, line, filename, modulename, component, ...) \
	ACPI_DO_DEBUG_PRINT (acpi_debug_prपूर्णांक_raw, level, line, \
		filename, modulename, component, __VA_ARGS__)

#घोषणा ACPI_DEBUG_PRINT(plist)         ACPI_ACTUAL_DEBUG plist
#घोषणा ACPI_DEBUG_PRINT_RAW(plist)     ACPI_ACTUAL_DEBUG_RAW plist

#पूर्ण_अगर

/*
 * Function entry tracing
 *
 * The name of the function is emitted as a local variable that is
 * पूर्णांकended to be used by both the entry trace and the निकास trace.
 */

/* Helper macro */

#घोषणा ACPI_TRACE_ENTRY(name, function, type, param) \
	ACPI_FUNCTION_NAME (name) \
	function (ACPI_DEBUG_PARAMETERS, (type) (param))

/* The actual entry trace macros */

#घोषणा ACPI_FUNCTION_TRACE(name) \
	ACPI_FUNCTION_NAME(name) \
	acpi_ut_trace (ACPI_DEBUG_PARAMETERS)

#घोषणा ACPI_FUNCTION_TRACE_PTR(name, poपूर्णांकer) \
	ACPI_TRACE_ENTRY (name, acpi_ut_trace_ptr, व्योम *, poपूर्णांकer)

#घोषणा ACPI_FUNCTION_TRACE_U32(name, value) \
	ACPI_TRACE_ENTRY (name, acpi_ut_trace_u32, u32, value)

#घोषणा ACPI_FUNCTION_TRACE_STR(name, string) \
	ACPI_TRACE_ENTRY (name, acpi_ut_trace_str, स्थिर अक्षर *, string)

#घोषणा ACPI_FUNCTION_ENTRY() \
	acpi_ut_track_stack_ptr()

/*
 * Function निकास tracing
 *
 * These macros include a वापस statement. This is usually considered
 * bad क्रमm, but having a separate निकास macro beक्रमe the actual वापस
 * is very ugly and dअगरficult to मुख्यtain.
 *
 * One of the FUNCTION_TRACE macros above must be used in conjunction
 * with these macros so that "_AcpiFunctionName" is defined.
 *
 * There are two versions of most of the वापस macros. The शेष version is
 * safer, since it aव्योमs side-effects by guaranteeing that the argument will
 * not be evaluated twice.
 *
 * A less-safe version of the macros is provided क्रम optional use अगर the
 * compiler uses excessive CPU stack (क्रम example, this may happen in the
 * debug हाल अगर code optimization is disabled.)
 */

/* Exit trace helper macro */

#अगर_अघोषित ACPI_SIMPLE_RETURN_MACROS

#घोषणा ACPI_TRACE_EXIT(function, type, param) \
	ACPI_DO_WHILE0 (अणु \
		रेजिस्टर type _param = (type) (param); \
		function (ACPI_DEBUG_PARAMETERS, _param); \
		वापस (_param); \
	पूर्ण)

#अन्यथा				/* Use original less-safe macros */

#घोषणा ACPI_TRACE_EXIT(function, type, param) \
	ACPI_DO_WHILE0 (अणु \
		function (ACPI_DEBUG_PARAMETERS, (type) (param)); \
		वापस (param); \
	पूर्ण)

#पूर्ण_अगर				/* ACPI_SIMPLE_RETURN_MACROS */

/* The actual निकास macros */

#घोषणा वापस_VOID \
	ACPI_DO_WHILE0 (अणु \
		acpi_ut_निकास (ACPI_DEBUG_PARAMETERS); \
		वापस; \
	पूर्ण)

#घोषणा वापस_ACPI_STATUS(status) \
	ACPI_TRACE_EXIT (acpi_ut_status_निकास, acpi_status, status)

#घोषणा वापस_PTR(poपूर्णांकer) \
	ACPI_TRACE_EXIT (acpi_ut_ptr_निकास, व्योम *, poपूर्णांकer)

#घोषणा वापस_STR(string) \
	ACPI_TRACE_EXIT (acpi_ut_str_निकास, स्थिर अक्षर *, string)

#घोषणा वापस_VALUE(value) \
	ACPI_TRACE_EXIT (acpi_ut_value_निकास, u64, value)

#घोषणा वापस_UINT32(value) \
	ACPI_TRACE_EXIT (acpi_ut_value_निकास, u32, value)

#घोषणा वापस_UINT8(value) \
	ACPI_TRACE_EXIT (acpi_ut_value_निकास, u8, value)

/* Conditional execution */

#घोषणा ACPI_DEBUG_EXEC(a)              a
#घोषणा ACPI_DEBUG_ONLY_MEMBERS(a)      a;
#घोषणा _VERBOSE_STRUCTURES

/* Various object display routines क्रम debug */

#घोषणा ACPI_DUMP_STACK_ENTRY(a)        acpi_ex_dump_opeअक्रम((a), 0)
#घोषणा ACPI_DUMP_OPERANDS(a, b ,c)     acpi_ex_dump_opeअक्रमs(a, b, c)
#घोषणा ACPI_DUMP_ENTRY(a, b)           acpi_ns_dump_entry (a, b)
#घोषणा ACPI_DUMP_PATHNAME(a, b, c, d)  acpi_ns_dump_pathname(a, b, c, d)
#घोषणा ACPI_DUMP_BUFFER(a, b)          acpi_ut_debug_dump_buffer((u8 *) a, b, DB_BYTE_DISPLAY, _COMPONENT)

#घोषणा ACPI_TRACE_POINT(a, b, c, d)    acpi_trace_poपूर्णांक (a, b, c, d)

#अन्यथा				/* ACPI_DEBUG_OUTPUT */
/*
 * This is the non-debug हाल -- make everything go away,
 * leaving no executable debug code!
 */
#घोषणा ACPI_DEBUG_PRINT(pl)
#घोषणा ACPI_DEBUG_PRINT_RAW(pl)
#घोषणा ACPI_DEBUG_EXEC(a)
#घोषणा ACPI_DEBUG_ONLY_MEMBERS(a)
#घोषणा ACPI_FUNCTION_NAME(a)
#घोषणा ACPI_FUNCTION_TRACE(a)
#घोषणा ACPI_FUNCTION_TRACE_PTR(a, b)
#घोषणा ACPI_FUNCTION_TRACE_U32(a, b)
#घोषणा ACPI_FUNCTION_TRACE_STR(a, b)
#घोषणा ACPI_FUNCTION_ENTRY()
#घोषणा ACPI_DUMP_STACK_ENTRY(a)
#घोषणा ACPI_DUMP_OPERANDS(a, b, c)
#घोषणा ACPI_DUMP_ENTRY(a, b)
#घोषणा ACPI_DUMP_PATHNAME(a, b, c, d)
#घोषणा ACPI_DUMP_BUFFER(a, b)
#घोषणा ACPI_IS_DEBUG_ENABLED(level, component) 0
#घोषणा ACPI_TRACE_POINT(a, b, c, d)

/* Return macros must have a वापस statement at the minimum */

#घोषणा वापस_VOID                     वापस
#घोषणा वापस_ACPI_STATUS(s)           वापस(s)
#घोषणा वापस_PTR(s)                   वापस(s)
#घोषणा वापस_STR(s)                   वापस(s)
#घोषणा वापस_VALUE(s)                 वापस(s)
#घोषणा वापस_UINT8(s)                 वापस(s)
#घोषणा वापस_UINT32(s)                वापस(s)

#पूर्ण_अगर				/* ACPI_DEBUG_OUTPUT */

#पूर्ण_अगर				/* __ACOUTPUT_H__ */
