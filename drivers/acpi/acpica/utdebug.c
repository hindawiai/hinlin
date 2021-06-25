<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: utdebug - Debug prपूर्णांक/trace routines
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#घोषणा EXPORT_ACPI_INTERFACES

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acinterp.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utdebug")

#अगर_घोषित ACPI_DEBUG_OUTPUT
अटल acpi_thपढ़ो_id acpi_gbl_previous_thपढ़ो_id = (acpi_thपढ़ो_id) 0xFFFFFFFF;
अटल स्थिर अक्षर *acpi_gbl_function_entry_prefix = "----Entry";
अटल स्थिर अक्षर *acpi_gbl_function_निकास_prefix = "----Exit-";

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_init_stack_ptr_trace
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Save the current CPU stack poपूर्णांकer at subप्रणाली startup
 *
 ******************************************************************************/

व्योम acpi_ut_init_stack_ptr_trace(व्योम)
अणु
	acpi_size current_sp;

	acpi_gbl_entry_stack_poपूर्णांकer = &current_sp;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_track_stack_ptr
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Save the current CPU stack poपूर्णांकer
 *
 ******************************************************************************/

व्योम acpi_ut_track_stack_ptr(व्योम)
अणु
	acpi_size current_sp;

	अगर (&current_sp < acpi_gbl_lowest_stack_poपूर्णांकer) अणु
		acpi_gbl_lowest_stack_poपूर्णांकer = &current_sp;
	पूर्ण

	अगर (acpi_gbl_nesting_level > acpi_gbl_deepest_nesting) अणु
		acpi_gbl_deepest_nesting = acpi_gbl_nesting_level;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_trim_function_name
 *
 * PARAMETERS:  function_name       - Ascii string containing a procedure name
 *
 * RETURN:      Updated poपूर्णांकer to the function name
 *
 * DESCRIPTION: Remove the "Acpi" prefix from the function name, अगर present.
 *              This allows compiler macros such as __func__ to be used
 *              with no change to the debug output.
 *
 ******************************************************************************/

अटल स्थिर अक्षर *acpi_ut_trim_function_name(स्थिर अक्षर *function_name)
अणु

	/* All Function names are दीर्घer than 4 अक्षरs, check is safe */

	अगर (*(ACPI_CAST_PTR(u32, function_name)) == ACPI_PREFIX_MIXED) अणु

		/* This is the हाल where the original source has not been modअगरied */

		वापस (function_name + 4);
	पूर्ण

	अगर (*(ACPI_CAST_PTR(u32, function_name)) == ACPI_PREFIX_LOWER) अणु

		/* This is the हाल where the source has been 'linuxized' */

		वापस (function_name + 5);
	पूर्ण

	वापस (function_name);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_debug_prपूर्णांक
 *
 * PARAMETERS:  requested_debug_level - Requested debug prपूर्णांक level
 *              line_number         - Caller's line number (क्रम error output)
 *              function_name       - Caller's procedure name
 *              module_name         - Caller's module name
 *              component_id        - Caller's component ID
 *              क्रमmat              - Prपूर्णांकf क्रमmat field
 *              ...                 - Optional म_लिखो arguments
 *
 * RETURN:      None
 *
 * DESCRIPTION: Prपूर्णांक error message with prefix consisting of the module name,
 *              line number, and component ID.
 *
 ******************************************************************************/

व्योम ACPI_INTERNAL_VAR_XFACE
acpi_debug_prपूर्णांक(u32 requested_debug_level,
		 u32 line_number,
		 स्थिर अक्षर *function_name,
		 स्थिर अक्षर *module_name,
		 u32 component_id, स्थिर अक्षर *क्रमmat, ...)
अणु
	acpi_thपढ़ो_id thपढ़ो_id;
	बहु_सूची args;
#अगर_घोषित ACPI_APPLICATION
	पूर्णांक fill_count;
#पूर्ण_अगर

	/* Check अगर debug output enabled */

	अगर (!ACPI_IS_DEBUG_ENABLED(requested_debug_level, component_id)) अणु
		वापस;
	पूर्ण

	/*
	 * Thपढ़ो tracking and context चयन notअगरication
	 */
	thपढ़ो_id = acpi_os_get_thपढ़ो_id();
	अगर (thपढ़ो_id != acpi_gbl_previous_thपढ़ो_id) अणु
		अगर (ACPI_LV_THREADS & acpi_dbg_level) अणु
			acpi_os_म_लिखो
			    ("\n**** Context Switch from TID %u to TID %u ****\n\n",
			     (u32)acpi_gbl_previous_thपढ़ो_id, (u32)thपढ़ो_id);
		पूर्ण

		acpi_gbl_previous_thपढ़ो_id = thपढ़ो_id;
		acpi_gbl_nesting_level = 0;
	पूर्ण

	/*
	 * Display the module name, current line number, thपढ़ो ID (अगर requested),
	 * current procedure nesting level, and the current procedure name
	 */
	acpi_os_म_लिखो("%9s-%04d ", module_name, line_number);

#अगर_घोषित ACPI_APPLICATION
	/*
	 * For acpi_exec/iASL only, emit the thपढ़ो ID and nesting level.
	 * Note: nesting level is really only useful during a single-thपढ़ो
	 * execution. Otherwise, multiple thपढ़ोs will keep resetting the
	 * level.
	 */
	अगर (ACPI_LV_THREADS & acpi_dbg_level) अणु
		acpi_os_म_लिखो("[%u] ", (u32)thपढ़ो_id);
	पूर्ण

	fill_count = 48 - acpi_gbl_nesting_level -
	    म_माप(acpi_ut_trim_function_name(function_name));
	अगर (fill_count < 0) अणु
		fill_count = 0;
	पूर्ण

	acpi_os_म_लिखो("[%02d] %*s",
		       acpi_gbl_nesting_level, acpi_gbl_nesting_level + 1, " ");
	acpi_os_म_लिखो("%s%*s: ",
		       acpi_ut_trim_function_name(function_name), fill_count,
		       " ");

#अन्यथा
	acpi_os_म_लिखो("%-22.22s: ", acpi_ut_trim_function_name(function_name));
#पूर्ण_अगर

	बहु_शुरू(args, क्रमmat);
	acpi_os_भ_लिखो(क्रमmat, args);
	बहु_पूर्ण(args);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_debug_prपूर्णांक)

/*******************************************************************************
 *
 * FUNCTION:    acpi_debug_prपूर्णांक_raw
 *
 * PARAMETERS:  requested_debug_level - Requested debug prपूर्णांक level
 *              line_number         - Caller's line number
 *              function_name       - Caller's procedure name
 *              module_name         - Caller's module name
 *              component_id        - Caller's component ID
 *              क्रमmat              - Prपूर्णांकf क्रमmat field
 *              ...                 - Optional म_लिखो arguments
 *
 * RETURN:      None
 *
 * DESCRIPTION: Prपूर्णांक message with no headers. Has same पूर्णांकerface as
 *              debug_prपूर्णांक so that the same macros can be used.
 *
 ******************************************************************************/
व्योम ACPI_INTERNAL_VAR_XFACE
acpi_debug_prपूर्णांक_raw(u32 requested_debug_level,
		     u32 line_number,
		     स्थिर अक्षर *function_name,
		     स्थिर अक्षर *module_name,
		     u32 component_id, स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची args;

	/* Check अगर debug output enabled */

	अगर (!ACPI_IS_DEBUG_ENABLED(requested_debug_level, component_id)) अणु
		वापस;
	पूर्ण

	बहु_शुरू(args, क्रमmat);
	acpi_os_भ_लिखो(क्रमmat, args);
	बहु_पूर्ण(args);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_debug_prपूर्णांक_raw)

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_trace
 *
 * PARAMETERS:  line_number         - Caller's line number
 *              function_name       - Caller's procedure name
 *              module_name         - Caller's module name
 *              component_id        - Caller's component ID
 *
 * RETURN:      None
 *
 * DESCRIPTION: Function entry trace. Prपूर्णांकs only अगर TRACE_FUNCTIONS bit is
 *              set in debug_level
 *
 ******************************************************************************/
व्योम
acpi_ut_trace(u32 line_number,
	      स्थिर अक्षर *function_name,
	      स्थिर अक्षर *module_name, u32 component_id)
अणु

	acpi_gbl_nesting_level++;
	acpi_ut_track_stack_ptr();

	/* Check अगर enabled up-front क्रम perक्रमmance */

	अगर (ACPI_IS_DEBUG_ENABLED(ACPI_LV_FUNCTIONS, component_id)) अणु
		acpi_debug_prपूर्णांक(ACPI_LV_FUNCTIONS,
				 line_number, function_name, module_name,
				 component_id, "%s\n",
				 acpi_gbl_function_entry_prefix);
	पूर्ण
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_ut_trace)

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_trace_ptr
 *
 * PARAMETERS:  line_number         - Caller's line number
 *              function_name       - Caller's procedure name
 *              module_name         - Caller's module name
 *              component_id        - Caller's component ID
 *              poपूर्णांकer             - Poपूर्णांकer to display
 *
 * RETURN:      None
 *
 * DESCRIPTION: Function entry trace. Prपूर्णांकs only अगर TRACE_FUNCTIONS bit is
 *              set in debug_level
 *
 ******************************************************************************/
व्योम
acpi_ut_trace_ptr(u32 line_number,
		  स्थिर अक्षर *function_name,
		  स्थिर अक्षर *module_name,
		  u32 component_id, स्थिर व्योम *poपूर्णांकer)
अणु

	acpi_gbl_nesting_level++;
	acpi_ut_track_stack_ptr();

	/* Check अगर enabled up-front क्रम perक्रमmance */

	अगर (ACPI_IS_DEBUG_ENABLED(ACPI_LV_FUNCTIONS, component_id)) अणु
		acpi_debug_prपूर्णांक(ACPI_LV_FUNCTIONS,
				 line_number, function_name, module_name,
				 component_id, "%s %p\n",
				 acpi_gbl_function_entry_prefix, poपूर्णांकer);
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_trace_str
 *
 * PARAMETERS:  line_number         - Caller's line number
 *              function_name       - Caller's procedure name
 *              module_name         - Caller's module name
 *              component_id        - Caller's component ID
 *              string              - Additional string to display
 *
 * RETURN:      None
 *
 * DESCRIPTION: Function entry trace. Prपूर्णांकs only अगर TRACE_FUNCTIONS bit is
 *              set in debug_level
 *
 ******************************************************************************/

व्योम
acpi_ut_trace_str(u32 line_number,
		  स्थिर अक्षर *function_name,
		  स्थिर अक्षर *module_name, u32 component_id, स्थिर अक्षर *string)
अणु

	acpi_gbl_nesting_level++;
	acpi_ut_track_stack_ptr();

	/* Check अगर enabled up-front क्रम perक्रमmance */

	अगर (ACPI_IS_DEBUG_ENABLED(ACPI_LV_FUNCTIONS, component_id)) अणु
		acpi_debug_prपूर्णांक(ACPI_LV_FUNCTIONS,
				 line_number, function_name, module_name,
				 component_id, "%s %s\n",
				 acpi_gbl_function_entry_prefix, string);
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_trace_u32
 *
 * PARAMETERS:  line_number         - Caller's line number
 *              function_name       - Caller's procedure name
 *              module_name         - Caller's module name
 *              component_id        - Caller's component ID
 *              पूर्णांकeger             - Integer to display
 *
 * RETURN:      None
 *
 * DESCRIPTION: Function entry trace. Prपूर्णांकs only अगर TRACE_FUNCTIONS bit is
 *              set in debug_level
 *
 ******************************************************************************/

व्योम
acpi_ut_trace_u32(u32 line_number,
		  स्थिर अक्षर *function_name,
		  स्थिर अक्षर *module_name, u32 component_id, u32 पूर्णांकeger)
अणु

	acpi_gbl_nesting_level++;
	acpi_ut_track_stack_ptr();

	/* Check अगर enabled up-front क्रम perक्रमmance */

	अगर (ACPI_IS_DEBUG_ENABLED(ACPI_LV_FUNCTIONS, component_id)) अणु
		acpi_debug_prपूर्णांक(ACPI_LV_FUNCTIONS,
				 line_number, function_name, module_name,
				 component_id, "%s %08X\n",
				 acpi_gbl_function_entry_prefix, पूर्णांकeger);
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_निकास
 *
 * PARAMETERS:  line_number         - Caller's line number
 *              function_name       - Caller's procedure name
 *              module_name         - Caller's module name
 *              component_id        - Caller's component ID
 *
 * RETURN:      None
 *
 * DESCRIPTION: Function निकास trace. Prपूर्णांकs only अगर TRACE_FUNCTIONS bit is
 *              set in debug_level
 *
 ******************************************************************************/

व्योम
acpi_ut_निकास(u32 line_number,
	     स्थिर अक्षर *function_name,
	     स्थिर अक्षर *module_name, u32 component_id)
अणु

	/* Check अगर enabled up-front क्रम perक्रमmance */

	अगर (ACPI_IS_DEBUG_ENABLED(ACPI_LV_FUNCTIONS, component_id)) अणु
		acpi_debug_prपूर्णांक(ACPI_LV_FUNCTIONS,
				 line_number, function_name, module_name,
				 component_id, "%s\n",
				 acpi_gbl_function_निकास_prefix);
	पूर्ण

	अगर (acpi_gbl_nesting_level) अणु
		acpi_gbl_nesting_level--;
	पूर्ण
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_ut_निकास)

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_status_निकास
 *
 * PARAMETERS:  line_number         - Caller's line number
 *              function_name       - Caller's procedure name
 *              module_name         - Caller's module name
 *              component_id        - Caller's component ID
 *              status              - Exit status code
 *
 * RETURN:      None
 *
 * DESCRIPTION: Function निकास trace. Prपूर्णांकs only अगर TRACE_FUNCTIONS bit is
 *              set in debug_level. Prपूर्णांकs निकास status also.
 *
 ******************************************************************************/
व्योम
acpi_ut_status_निकास(u32 line_number,
		    स्थिर अक्षर *function_name,
		    स्थिर अक्षर *module_name,
		    u32 component_id, acpi_status status)
अणु

	/* Check अगर enabled up-front क्रम perक्रमmance */

	अगर (ACPI_IS_DEBUG_ENABLED(ACPI_LV_FUNCTIONS, component_id)) अणु
		अगर (ACPI_SUCCESS(status)) अणु
			acpi_debug_prपूर्णांक(ACPI_LV_FUNCTIONS,
					 line_number, function_name,
					 module_name, component_id, "%s %s\n",
					 acpi_gbl_function_निकास_prefix,
					 acpi_क्रमmat_exception(status));
		पूर्ण अन्यथा अणु
			acpi_debug_prपूर्णांक(ACPI_LV_FUNCTIONS,
					 line_number, function_name,
					 module_name, component_id,
					 "%s ****Exception****: %s\n",
					 acpi_gbl_function_निकास_prefix,
					 acpi_क्रमmat_exception(status));
		पूर्ण
	पूर्ण

	अगर (acpi_gbl_nesting_level) अणु
		acpi_gbl_nesting_level--;
	पूर्ण
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_ut_status_निकास)

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_value_निकास
 *
 * PARAMETERS:  line_number         - Caller's line number
 *              function_name       - Caller's procedure name
 *              module_name         - Caller's module name
 *              component_id        - Caller's component ID
 *              value               - Value to be prपूर्णांकed with निकास msg
 *
 * RETURN:      None
 *
 * DESCRIPTION: Function निकास trace. Prपूर्णांकs only अगर TRACE_FUNCTIONS bit is
 *              set in debug_level. Prपूर्णांकs निकास value also.
 *
 ******************************************************************************/
व्योम
acpi_ut_value_निकास(u32 line_number,
		   स्थिर अक्षर *function_name,
		   स्थिर अक्षर *module_name, u32 component_id, u64 value)
अणु

	/* Check अगर enabled up-front क्रम perक्रमmance */

	अगर (ACPI_IS_DEBUG_ENABLED(ACPI_LV_FUNCTIONS, component_id)) अणु
		acpi_debug_prपूर्णांक(ACPI_LV_FUNCTIONS,
				 line_number, function_name, module_name,
				 component_id, "%s %8.8X%8.8X\n",
				 acpi_gbl_function_निकास_prefix,
				 ACPI_FORMAT_UINT64(value));
	पूर्ण

	अगर (acpi_gbl_nesting_level) अणु
		acpi_gbl_nesting_level--;
	पूर्ण
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_ut_value_निकास)

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_ptr_निकास
 *
 * PARAMETERS:  line_number         - Caller's line number
 *              function_name       - Caller's procedure name
 *              module_name         - Caller's module name
 *              component_id        - Caller's component ID
 *              ptr                 - Poपूर्णांकer to display
 *
 * RETURN:      None
 *
 * DESCRIPTION: Function निकास trace. Prपूर्णांकs only अगर TRACE_FUNCTIONS bit is
 *              set in debug_level. Prपूर्णांकs निकास value also.
 *
 ******************************************************************************/
व्योम
acpi_ut_ptr_निकास(u32 line_number,
		 स्थिर अक्षर *function_name,
		 स्थिर अक्षर *module_name, u32 component_id, u8 *ptr)
अणु

	/* Check अगर enabled up-front क्रम perक्रमmance */

	अगर (ACPI_IS_DEBUG_ENABLED(ACPI_LV_FUNCTIONS, component_id)) अणु
		acpi_debug_prपूर्णांक(ACPI_LV_FUNCTIONS,
				 line_number, function_name, module_name,
				 component_id, "%s %p\n",
				 acpi_gbl_function_निकास_prefix, ptr);
	पूर्ण

	अगर (acpi_gbl_nesting_level) अणु
		acpi_gbl_nesting_level--;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_str_निकास
 *
 * PARAMETERS:  line_number         - Caller's line number
 *              function_name       - Caller's procedure name
 *              module_name         - Caller's module name
 *              component_id        - Caller's component ID
 *              string              - String to display
 *
 * RETURN:      None
 *
 * DESCRIPTION: Function निकास trace. Prपूर्णांकs only अगर TRACE_FUNCTIONS bit is
 *              set in debug_level. Prपूर्णांकs निकास value also.
 *
 ******************************************************************************/

व्योम
acpi_ut_str_निकास(u32 line_number,
		 स्थिर अक्षर *function_name,
		 स्थिर अक्षर *module_name, u32 component_id, स्थिर अक्षर *string)
अणु

	/* Check अगर enabled up-front क्रम perक्रमmance */

	अगर (ACPI_IS_DEBUG_ENABLED(ACPI_LV_FUNCTIONS, component_id)) अणु
		acpi_debug_prपूर्णांक(ACPI_LV_FUNCTIONS,
				 line_number, function_name, module_name,
				 component_id, "%s %s\n",
				 acpi_gbl_function_निकास_prefix, string);
	पूर्ण

	अगर (acpi_gbl_nesting_level) अणु
		acpi_gbl_nesting_level--;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_trace_poपूर्णांक
 *
 * PARAMETERS:  type                - Trace event type
 *              begin               - TRUE अगर beक्रमe execution
 *              aml                 - Executed AML address
 *              pathname            - Object path
 *              poपूर्णांकer             - Poपूर्णांकer to the related object
 *
 * RETURN:      None
 *
 * DESCRIPTION: Interpreter execution trace.
 *
 ******************************************************************************/

व्योम
acpi_trace_poपूर्णांक(acpi_trace_event_type type, u8 begin, u8 *aml, अक्षर *pathname)
अणु

	ACPI_FUNCTION_ENTRY();

	acpi_ex_trace_poपूर्णांक(type, begin, aml, pathname);

#अगर_घोषित ACPI_USE_SYSTEM_TRACER
	acpi_os_trace_poपूर्णांक(type, begin, aml, pathname);
#पूर्ण_अगर
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_trace_poपूर्णांक)

#पूर्ण_अगर
