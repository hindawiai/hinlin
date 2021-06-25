<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: dsdebug - Parser/Interpreter पूर्णांकerface - debugging
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acdispat.h"
#समावेश "acnamesp.h"
#अगर_घोषित ACPI_DISASSEMBLER
#समावेश "acdisasm.h"
#पूर्ण_अगर
#समावेश "acinterp.h"

#घोषणा _COMPONENT          ACPI_DISPATCHER
ACPI_MODULE_NAME("dsdebug")

#अगर defined(ACPI_DEBUG_OUTPUT) || defined(ACPI_DEBUGGER)
/* Local prototypes */
अटल व्योम
acpi_ds_prपूर्णांक_node_pathname(काष्ठा acpi_namespace_node *node,
			    स्थिर अक्षर *message);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_prपूर्णांक_node_pathname
 *
 * PARAMETERS:  node            - Object
 *              message         - Prefix message
 *
 * DESCRIPTION: Prपूर्णांक an object's full namespace pathname
 *              Manages allocation/मुक्तing of a pathname buffer
 *
 ******************************************************************************/

अटल व्योम
acpi_ds_prपूर्णांक_node_pathname(काष्ठा acpi_namespace_node *node,
			    स्थिर अक्षर *message)
अणु
	काष्ठा acpi_buffer buffer;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ds_prपूर्णांक_node_pathname);

	अगर (!node) अणु
		ACPI_DEBUG_PRINT_RAW((ACPI_DB_DISPATCH, "[NULL NAME]"));
		वापस_VOID;
	पूर्ण

	/* Convert handle to full pathname and prपूर्णांक it (with supplied message) */

	buffer.length = ACPI_ALLOCATE_LOCAL_BUFFER;

	status = acpi_ns_handle_to_pathname(node, &buffer, TRUE);
	अगर (ACPI_SUCCESS(status)) अणु
		अगर (message) अणु
			ACPI_DEBUG_PRINT_RAW((ACPI_DB_DISPATCH, "%s ",
					      message));
		पूर्ण

		ACPI_DEBUG_PRINT_RAW((ACPI_DB_DISPATCH, "[%s] (Node %p)",
				      (अक्षर *)buffer.poपूर्णांकer, node));
		ACPI_FREE(buffer.poपूर्णांकer);
	पूर्ण

	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_dump_method_stack
 *
 * PARAMETERS:  status          - Method execution status
 *              walk_state      - Current state of the parse tree walk
 *              op              - Executing parse op
 *
 * RETURN:      None
 *
 * DESCRIPTION: Called when a method has been पातed because of an error.
 *              Dumps the method execution stack.
 *
 ******************************************************************************/

व्योम
acpi_ds_dump_method_stack(acpi_status status,
			  काष्ठा acpi_walk_state *walk_state,
			  जोड़ acpi_parse_object *op)
अणु
	जोड़ acpi_parse_object *next;
	काष्ठा acpi_thपढ़ो_state *thपढ़ो;
	काष्ठा acpi_walk_state *next_walk_state;
	काष्ठा acpi_namespace_node *previous_method = शून्य;
	जोड़ acpi_opeअक्रम_object *method_desc;

	ACPI_FUNCTION_TRACE(ds_dump_method_stack);

	/* Ignore control codes, they are not errors */

	अगर (ACPI_CNTL_EXCEPTION(status)) अणु
		वापस_VOID;
	पूर्ण

	/* We may be executing a deferred opcode */

	अगर (walk_state->deferred_node) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
				  "Executing subtree for Buffer/Package/Region\n"));
		वापस_VOID;
	पूर्ण

	/*
	 * If there is no Thपढ़ो, we are not actually executing a method.
	 * This can happen when the iASL compiler calls the पूर्णांकerpreter
	 * to perक्रमm स्थिरant folding.
	 */
	thपढ़ो = walk_state->thपढ़ो;
	अगर (!thपढ़ो) अणु
		वापस_VOID;
	पूर्ण

	/* Display exception and method name */

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "\n**** Exception %s during execution of method ",
			  acpi_क्रमmat_exception(status)));

	acpi_ds_prपूर्णांक_node_pathname(walk_state->method_node, शून्य);

	/* Display stack of executing methods */

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_DISPATCH,
			      "\n\nMethod Execution Stack:\n"));
	next_walk_state = thपढ़ो->walk_state_list;

	/* Walk list of linked walk states */

	जबतक (next_walk_state) अणु
		method_desc = next_walk_state->method_desc;
		अगर (method_desc) अणु
			acpi_ex_stop_trace_method((काष्ठा acpi_namespace_node *)
						  method_desc->method.node,
						  method_desc, walk_state);
		पूर्ण

		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
				  "    Method [%4.4s] executing: ",
				  acpi_ut_get_node_name(next_walk_state->
							method_node)));

		/* First method is the currently executing method */

		अगर (next_walk_state == walk_state) अणु
			अगर (op) अणु

				/* Display currently executing ASL statement */

				next = op->common.next;
				op->common.next = शून्य;

#अगर_घोषित ACPI_DISASSEMBLER
				अगर (walk_state->method_node !=
				    acpi_gbl_root_node) अणु

					/* More verbose अगर not module-level code */

					acpi_os_म_लिखो("Failed at ");
					acpi_dm_disassemble(next_walk_state, op,
							    ACPI_UINT32_MAX);
				पूर्ण
#पूर्ण_अगर
				op->common.next = next;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * This method has called another method
			 * NOTE: the method call parse subtree is alपढ़ोy deleted at
			 * this poपूर्णांक, so we cannot disassemble the method invocation.
			 */
			ACPI_DEBUG_PRINT_RAW((ACPI_DB_DISPATCH,
					      "Call to method "));
			acpi_ds_prपूर्णांक_node_pathname(previous_method, शून्य);
		पूर्ण

		previous_method = next_walk_state->method_node;
		next_walk_state = next_walk_state->next;
		ACPI_DEBUG_PRINT_RAW((ACPI_DB_DISPATCH, "\n"));
	पूर्ण

	वापस_VOID;
पूर्ण

#अन्यथा
व्योम
acpi_ds_dump_method_stack(acpi_status status,
			  काष्ठा acpi_walk_state *walk_state,
			  जोड़ acpi_parse_object *op)
अणु
	वापस;
पूर्ण

#पूर्ण_अगर
