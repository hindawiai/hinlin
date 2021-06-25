<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: extrace - Support क्रम पूर्णांकerpreter execution tracing
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"
#समावेश "acinterp.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("extrace")

अटल जोड़ acpi_opeअक्रम_object *acpi_gbl_trace_method_object = शून्य;

/* Local prototypes */

#अगर_घोषित ACPI_DEBUG_OUTPUT
अटल स्थिर अक्षर *acpi_ex_get_trace_event_name(acpi_trace_event_type type);
#पूर्ण_अगर

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_पूर्णांकerpreter_trace_enabled
 *
 * PARAMETERS:  name                - Whether method name should be matched,
 *                                    this should be checked beक्रमe starting
 *                                    the tracer
 *
 * RETURN:      TRUE अगर पूर्णांकerpreter trace is enabled.
 *
 * DESCRIPTION: Check whether पूर्णांकerpreter trace is enabled
 *
 ******************************************************************************/

अटल u8 acpi_ex_पूर्णांकerpreter_trace_enabled(अक्षर *name)
अणु

	/* Check अगर tracing is enabled */

	अगर (!(acpi_gbl_trace_flags & ACPI_TRACE_ENABLED)) अणु
		वापस (FALSE);
	पूर्ण

	/*
	 * Check अगर tracing is filtered:
	 *
	 * 1. If the tracer is started, acpi_gbl_trace_method_object should have
	 *    been filled by the trace starter
	 * 2. If the tracer is not started, acpi_gbl_trace_method_name should be
	 *    matched अगर it is specअगरied
	 * 3. If the tracer is oneshot style, acpi_gbl_trace_method_name should
	 *    not be cleared by the trace stopper during the first match
	 */
	अगर (acpi_gbl_trace_method_object) अणु
		वापस (TRUE);
	पूर्ण

	अगर (name &&
	    (acpi_gbl_trace_method_name &&
	     म_भेद(acpi_gbl_trace_method_name, name))) अणु
		वापस (FALSE);
	पूर्ण

	अगर ((acpi_gbl_trace_flags & ACPI_TRACE_ONESHOT) &&
	    !acpi_gbl_trace_method_name) अणु
		वापस (FALSE);
	पूर्ण

	वापस (TRUE);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_get_trace_event_name
 *
 * PARAMETERS:  type            - Trace event type
 *
 * RETURN:      Trace event name.
 *
 * DESCRIPTION: Used to obtain the full trace event name.
 *
 ******************************************************************************/

#अगर_घोषित ACPI_DEBUG_OUTPUT

अटल स्थिर अक्षर *acpi_ex_get_trace_event_name(acpi_trace_event_type type)
अणु

	चयन (type) अणु
	हाल ACPI_TRACE_AML_METHOD:

		वापस "Method";

	हाल ACPI_TRACE_AML_OPCODE:

		वापस "Opcode";

	हाल ACPI_TRACE_AML_REGION:

		वापस "Region";

	शेष:

		वापस "";
	पूर्ण
पूर्ण

#पूर्ण_अगर

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_trace_poपूर्णांक
 *
 * PARAMETERS:  type                - Trace event type
 *              begin               - TRUE अगर beक्रमe execution
 *              aml                 - Executed AML address
 *              pathname            - Object path
 *
 * RETURN:      None
 *
 * DESCRIPTION: Internal पूर्णांकerpreter execution trace.
 *
 ******************************************************************************/

व्योम
acpi_ex_trace_poपूर्णांक(acpi_trace_event_type type,
		    u8 begin, u8 *aml, अक्षर *pathname)
अणु

	ACPI_FUNCTION_NAME(ex_trace_poपूर्णांक);

	अगर (pathname) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_TRACE_POINT,
				  "%s %s [0x%p:%s] execution.\n",
				  acpi_ex_get_trace_event_name(type),
				  begin ? "Begin" : "End", aml, pathname));
	पूर्ण अन्यथा अणु
		ACPI_DEBUG_PRINT((ACPI_DB_TRACE_POINT,
				  "%s %s [0x%p] execution.\n",
				  acpi_ex_get_trace_event_name(type),
				  begin ? "Begin" : "End", aml));
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_start_trace_method
 *
 * PARAMETERS:  method_node         - Node of the method
 *              obj_desc            - The method object
 *              walk_state          - current state, शून्य अगर not yet executing
 *                                    a method.
 *
 * RETURN:      None
 *
 * DESCRIPTION: Start control method execution trace
 *
 ******************************************************************************/

व्योम
acpi_ex_start_trace_method(काष्ठा acpi_namespace_node *method_node,
			   जोड़ acpi_opeअक्रम_object *obj_desc,
			   काष्ठा acpi_walk_state *walk_state)
अणु
	अक्षर *pathname = शून्य;
	u8 enabled = FALSE;

	ACPI_FUNCTION_NAME(ex_start_trace_method);

	अगर (method_node) अणु
		pathname = acpi_ns_get_normalized_pathname(method_node, TRUE);
	पूर्ण

	enabled = acpi_ex_पूर्णांकerpreter_trace_enabled(pathname);
	अगर (enabled && !acpi_gbl_trace_method_object) अणु
		acpi_gbl_trace_method_object = obj_desc;
		acpi_gbl_original_dbg_level = acpi_dbg_level;
		acpi_gbl_original_dbg_layer = acpi_dbg_layer;
		acpi_dbg_level = ACPI_TRACE_LEVEL_ALL;
		acpi_dbg_layer = ACPI_TRACE_LAYER_ALL;

		अगर (acpi_gbl_trace_dbg_level) अणु
			acpi_dbg_level = acpi_gbl_trace_dbg_level;
		पूर्ण

		अगर (acpi_gbl_trace_dbg_layer) अणु
			acpi_dbg_layer = acpi_gbl_trace_dbg_layer;
		पूर्ण
	पूर्ण

	अगर (enabled) अणु
		ACPI_TRACE_POINT(ACPI_TRACE_AML_METHOD, TRUE,
				 obj_desc ? obj_desc->method.aml_start : शून्य,
				 pathname);
	पूर्ण

	अगर (pathname) अणु
		ACPI_FREE(pathname);
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_stop_trace_method
 *
 * PARAMETERS:  method_node         - Node of the method
 *              obj_desc            - The method object
 *              walk_state          - current state, शून्य अगर not yet executing
 *                                    a method.
 *
 * RETURN:      None
 *
 * DESCRIPTION: Stop control method execution trace
 *
 ******************************************************************************/

व्योम
acpi_ex_stop_trace_method(काष्ठा acpi_namespace_node *method_node,
			  जोड़ acpi_opeअक्रम_object *obj_desc,
			  काष्ठा acpi_walk_state *walk_state)
अणु
	अक्षर *pathname = शून्य;
	u8 enabled;

	ACPI_FUNCTION_NAME(ex_stop_trace_method);

	अगर (method_node) अणु
		pathname = acpi_ns_get_normalized_pathname(method_node, TRUE);
	पूर्ण

	enabled = acpi_ex_पूर्णांकerpreter_trace_enabled(शून्य);

	अगर (enabled) अणु
		ACPI_TRACE_POINT(ACPI_TRACE_AML_METHOD, FALSE,
				 obj_desc ? obj_desc->method.aml_start : शून्य,
				 pathname);
	पूर्ण

	/* Check whether the tracer should be stopped */

	अगर (acpi_gbl_trace_method_object == obj_desc) अणु

		/* Disable further tracing अगर type is one-shot */

		अगर (acpi_gbl_trace_flags & ACPI_TRACE_ONESHOT) अणु
			acpi_gbl_trace_method_name = शून्य;
		पूर्ण

		acpi_dbg_level = acpi_gbl_original_dbg_level;
		acpi_dbg_layer = acpi_gbl_original_dbg_layer;
		acpi_gbl_trace_method_object = शून्य;
	पूर्ण

	अगर (pathname) अणु
		ACPI_FREE(pathname);
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_start_trace_opcode
 *
 * PARAMETERS:  op                  - The parser opcode object
 *              walk_state          - current state, शून्य अगर not yet executing
 *                                    a method.
 *
 * RETURN:      None
 *
 * DESCRIPTION: Start opcode execution trace
 *
 ******************************************************************************/

व्योम
acpi_ex_start_trace_opcode(जोड़ acpi_parse_object *op,
			   काष्ठा acpi_walk_state *walk_state)
अणु

	ACPI_FUNCTION_NAME(ex_start_trace_opcode);

	अगर (acpi_ex_पूर्णांकerpreter_trace_enabled(शून्य) &&
	    (acpi_gbl_trace_flags & ACPI_TRACE_OPCODE)) अणु
		ACPI_TRACE_POINT(ACPI_TRACE_AML_OPCODE, TRUE,
				 op->common.aml, op->common.aml_op_name);
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_stop_trace_opcode
 *
 * PARAMETERS:  op                  - The parser opcode object
 *              walk_state          - current state, शून्य अगर not yet executing
 *                                    a method.
 *
 * RETURN:      None
 *
 * DESCRIPTION: Stop opcode execution trace
 *
 ******************************************************************************/

व्योम
acpi_ex_stop_trace_opcode(जोड़ acpi_parse_object *op,
			  काष्ठा acpi_walk_state *walk_state)
अणु

	ACPI_FUNCTION_NAME(ex_stop_trace_opcode);

	अगर (acpi_ex_पूर्णांकerpreter_trace_enabled(शून्य) &&
	    (acpi_gbl_trace_flags & ACPI_TRACE_OPCODE)) अणु
		ACPI_TRACE_POINT(ACPI_TRACE_AML_OPCODE, FALSE,
				 op->common.aml, op->common.aml_op_name);
	पूर्ण
पूर्ण
