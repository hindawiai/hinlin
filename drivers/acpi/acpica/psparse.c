<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: psparse - Parser top level AML parse routines
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

/*
 * Parse the AML and build an operation tree as most पूर्णांकerpreters,
 * like Perl, करो. Parsing is करोne by hand rather than with a YACC
 * generated parser to tightly स्थिरrain stack and dynamic memory
 * usage. At the same समय, parsing is kept flexible and the code
 * fairly compact by parsing based on a list of AML opcode
 * ढाँचाs in aml_op_info[]
 */

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acparser.h"
#समावेश "acdispat.h"
#समावेश "amlcode.h"
#समावेश "acinterp.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_PARSER
ACPI_MODULE_NAME("psparse")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_opcode_size
 *
 * PARAMETERS:  opcode          - An AML opcode
 *
 * RETURN:      Size of the opcode, in bytes (1 or 2)
 *
 * DESCRIPTION: Get the size of the current opcode.
 *
 ******************************************************************************/
u32 acpi_ps_get_opcode_size(u32 opcode)
अणु

	/* Extended (2-byte) opcode अगर > 255 */

	अगर (opcode > 0x00FF) अणु
		वापस (2);
	पूर्ण

	/* Otherwise, just a single byte opcode */

	वापस (1);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_peek_opcode
 *
 * PARAMETERS:  parser_state        - A parser state object
 *
 * RETURN:      Next AML opcode
 *
 * DESCRIPTION: Get next AML opcode (without incrementing AML poपूर्णांकer)
 *
 ******************************************************************************/

u16 acpi_ps_peek_opcode(काष्ठा acpi_parse_state * parser_state)
अणु
	u8 *aml;
	u16 opcode;

	aml = parser_state->aml;
	opcode = (u16) ACPI_GET8(aml);

	अगर (opcode == AML_EXTENDED_PREFIX) अणु

		/* Extended opcode, get the second opcode byte */

		aml++;
		opcode = (u16) ((opcode << 8) | ACPI_GET8(aml));
	पूर्ण

	वापस (opcode);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_complete_this_op
 *
 * PARAMETERS:  walk_state      - Current State
 *              op              - Op to complete
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Perक्रमm any cleanup at the completion of an Op.
 *
 ******************************************************************************/

acpi_status
acpi_ps_complete_this_op(काष्ठा acpi_walk_state *walk_state,
			 जोड़ acpi_parse_object *op)
अणु
	जोड़ acpi_parse_object *prev;
	जोड़ acpi_parse_object *next;
	स्थिर काष्ठा acpi_opcode_info *parent_info;
	जोड़ acpi_parse_object *replacement_op = शून्य;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE_PTR(ps_complete_this_op, op);

	/* Check क्रम null Op, can happen अगर AML code is corrupt */

	अगर (!op) अणु
		वापस_ACPI_STATUS(AE_OK);	/* OK क्रम now */
	पूर्ण

	acpi_ex_stop_trace_opcode(op, walk_state);

	/* Delete this op and the subtree below it अगर asked to */

	अगर (((walk_state->parse_flags & ACPI_PARSE_TREE_MASK) !=
	     ACPI_PARSE_DELETE_TREE)
	    || (walk_state->op_info->class == AML_CLASS_ARGUMENT)) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Make sure that we only delete this subtree */

	अगर (op->common.parent) अणु
		prev = op->common.parent->common.value.arg;
		अगर (!prev) अणु

			/* Nothing more to करो */

			जाओ cleanup;
		पूर्ण

		/*
		 * Check अगर we need to replace the चालक and its subtree
		 * with a वापस value op (placeholder op)
		 */
		parent_info =
		    acpi_ps_get_opcode_info(op->common.parent->common.
					    aml_opcode);

		चयन (parent_info->class) अणु
		हाल AML_CLASS_CONTROL:

			अवरोध;

		हाल AML_CLASS_CREATE:
			/*
			 * These opcodes contain term_arg opeअक्रमs. The current
			 * op must be replaced by a placeholder वापस op
			 */
			replacement_op =
			    acpi_ps_alloc_op(AML_INT_RETURN_VALUE_OP,
					     op->common.aml);
			अगर (!replacement_op) अणु
				status = AE_NO_MEMORY;
			पूर्ण
			अवरोध;

		हाल AML_CLASS_NAMED_OBJECT:
			/*
			 * These opcodes contain term_arg opeअक्रमs. The current
			 * op must be replaced by a placeholder वापस op
			 */
			अगर ((op->common.parent->common.aml_opcode ==
			     AML_REGION_OP)
			    || (op->common.parent->common.aml_opcode ==
				AML_DATA_REGION_OP)
			    || (op->common.parent->common.aml_opcode ==
				AML_BUFFER_OP)
			    || (op->common.parent->common.aml_opcode ==
				AML_PACKAGE_OP)
			    || (op->common.parent->common.aml_opcode ==
				AML_BANK_FIELD_OP)
			    || (op->common.parent->common.aml_opcode ==
				AML_VARIABLE_PACKAGE_OP)) अणु
				replacement_op =
				    acpi_ps_alloc_op(AML_INT_RETURN_VALUE_OP,
						     op->common.aml);
				अगर (!replacement_op) अणु
					status = AE_NO_MEMORY;
				पूर्ण
			पूर्ण अन्यथा
			    अगर ((op->common.parent->common.aml_opcode ==
				 AML_NAME_OP)
				&& (walk_state->pass_number <=
				    ACPI_IMODE_LOAD_PASS2)) अणु
				अगर ((op->common.aml_opcode == AML_BUFFER_OP)
				    || (op->common.aml_opcode == AML_PACKAGE_OP)
				    || (op->common.aml_opcode ==
					AML_VARIABLE_PACKAGE_OP)) अणु
					replacement_op =
					    acpi_ps_alloc_op(op->common.
							     aml_opcode,
							     op->common.aml);
					अगर (!replacement_op) अणु
						status = AE_NO_MEMORY;
					पूर्ण अन्यथा अणु
						replacement_op->named.data =
						    op->named.data;
						replacement_op->named.length =
						    op->named.length;
					पूर्ण
				पूर्ण
			पूर्ण
			अवरोध;

		शेष:

			replacement_op =
			    acpi_ps_alloc_op(AML_INT_RETURN_VALUE_OP,
					     op->common.aml);
			अगर (!replacement_op) अणु
				status = AE_NO_MEMORY;
			पूर्ण
		पूर्ण

		/* We must unlink this op from the parent tree */

		अगर (prev == op) अणु

			/* This op is the first in the list */

			अगर (replacement_op) अणु
				replacement_op->common.parent =
				    op->common.parent;
				replacement_op->common.value.arg = शून्य;
				replacement_op->common.node = op->common.node;
				op->common.parent->common.value.arg =
				    replacement_op;
				replacement_op->common.next = op->common.next;
			पूर्ण अन्यथा अणु
				op->common.parent->common.value.arg =
				    op->common.next;
			पूर्ण
		पूर्ण

		/* Search the parent list */

		अन्यथा
			जबतक (prev) अणु

				/* Traverse all siblings in the parent's argument list */

				next = prev->common.next;
				अगर (next == op) अणु
					अगर (replacement_op) अणु
						replacement_op->common.parent =
						    op->common.parent;
						replacement_op->common.value.
						    arg = शून्य;
						replacement_op->common.node =
						    op->common.node;
						prev->common.next =
						    replacement_op;
						replacement_op->common.next =
						    op->common.next;
						next = शून्य;
					पूर्ण अन्यथा अणु
						prev->common.next =
						    op->common.next;
						next = शून्य;
					पूर्ण
				पूर्ण
				prev = next;
			पूर्ण
	पूर्ण

cleanup:

	/* Now we can actually delete the subtree rooted at Op */

	acpi_ps_delete_parse_tree(op);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_next_parse_state
 *
 * PARAMETERS:  walk_state          - Current state
 *              op                  - Current parse op
 *              callback_status     - Status from previous operation
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Update the parser state based upon the वापस exception from
 *              the parser callback.
 *
 ******************************************************************************/

acpi_status
acpi_ps_next_parse_state(काष्ठा acpi_walk_state *walk_state,
			 जोड़ acpi_parse_object *op,
			 acpi_status callback_status)
अणु
	काष्ठा acpi_parse_state *parser_state = &walk_state->parser_state;
	acpi_status status = AE_CTRL_PENDING;

	ACPI_FUNCTION_TRACE_PTR(ps_next_parse_state, op);

	चयन (callback_status) अणु
	हाल AE_CTRL_TERMINATE:
		/*
		 * A control method was terminated via a RETURN statement.
		 * The walk of this method is complete.
		 */
		parser_state->aml = parser_state->aml_end;
		status = AE_CTRL_TERMINATE;
		अवरोध;

	हाल AE_CTRL_BREAK:

		parser_state->aml = walk_state->aml_last_जबतक;
		walk_state->control_state->common.value = FALSE;
		status = AE_CTRL_BREAK;
		अवरोध;

	हाल AE_CTRL_CONTINUE:

		parser_state->aml = walk_state->aml_last_जबतक;
		status = AE_CTRL_CONTINUE;
		अवरोध;

	हाल AE_CTRL_PENDING:

		parser_state->aml = walk_state->aml_last_जबतक;
		अवरोध;

#अगर 0
	हाल AE_CTRL_SKIP:

		parser_state->aml = parser_state->scope->parse_scope.pkg_end;
		status = AE_OK;
		अवरोध;
#पूर्ण_अगर

	हाल AE_CTRL_TRUE:
		/*
		 * Predicate of an IF was true, and we are at the matching ELSE.
		 * Just बंद out this package
		 */
		parser_state->aml = acpi_ps_get_next_package_end(parser_state);
		status = AE_CTRL_PENDING;
		अवरोध;

	हाल AE_CTRL_FALSE:
		/*
		 * Either an IF/WHILE Predicate was false or we encountered a BREAK
		 * opcode. In both हालs, we करो not execute the rest of the
		 * package;  We simply बंद out the parent (finishing the walk of
		 * this branch of the tree) and जारी execution at the parent
		 * level.
		 */
		parser_state->aml = parser_state->scope->parse_scope.pkg_end;

		/* In the हाल of a BREAK, just क्रमce a predicate (अगर any) to FALSE */

		walk_state->control_state->common.value = FALSE;
		status = AE_CTRL_END;
		अवरोध;

	हाल AE_CTRL_TRANSFER:

		/* A method call (invocation) -- transfer control */

		status = AE_CTRL_TRANSFER;
		walk_state->prev_op = op;
		walk_state->method_call_op = op;
		walk_state->method_call_node =
		    (op->common.value.arg)->common.node;

		/* Will वापस value (अगर any) be used by the caller? */

		walk_state->वापस_used =
		    acpi_ds_is_result_used(op, walk_state);
		अवरोध;

	शेष:

		status = callback_status;
		अगर (ACPI_CNTL_EXCEPTION(callback_status)) अणु
			status = AE_OK;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_parse_aml
 *
 * PARAMETERS:  walk_state      - Current state
 *
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Parse raw AML and वापस a tree of ops
 *
 ******************************************************************************/

acpi_status acpi_ps_parse_aml(काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status;
	काष्ठा acpi_thपढ़ो_state *thपढ़ो;
	काष्ठा acpi_thपढ़ो_state *prev_walk_list = acpi_gbl_current_walk_list;
	काष्ठा acpi_walk_state *previous_walk_state;

	ACPI_FUNCTION_TRACE(ps_parse_aml);

	ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
			  "Entered with WalkState=%p Aml=%p size=%X\n",
			  walk_state, walk_state->parser_state.aml,
			  walk_state->parser_state.aml_size));

	अगर (!walk_state->parser_state.aml) अणु
		वापस_ACPI_STATUS(AE_BAD_ADDRESS);
	पूर्ण

	/* Create and initialize a new thपढ़ो state */

	thपढ़ो = acpi_ut_create_thपढ़ो_state();
	अगर (!thपढ़ो) अणु
		अगर (walk_state->method_desc) अणु

			/* Executing a control method - additional cleanup */

			acpi_ds_terminate_control_method(walk_state->
							 method_desc,
							 walk_state);
		पूर्ण

		acpi_ds_delete_walk_state(walk_state);
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	walk_state->thपढ़ो = thपढ़ो;

	/*
	 * If executing a method, the starting sync_level is this method's
	 * sync_level
	 */
	अगर (walk_state->method_desc) अणु
		walk_state->thपढ़ो->current_sync_level =
		    walk_state->method_desc->method.sync_level;
	पूर्ण

	acpi_ds_push_walk_state(walk_state, thपढ़ो);

	/*
	 * This global allows the AML debugger to get a handle to the currently
	 * executing control method.
	 */
	acpi_gbl_current_walk_list = thपढ़ो;

	/*
	 * Execute the walk loop as दीर्घ as there is a valid Walk State. This
	 * handles nested control method invocations without recursion.
	 */
	ACPI_DEBUG_PRINT((ACPI_DB_PARSE, "State=%p\n", walk_state));

	status = AE_OK;
	जबतक (walk_state) अणु
		अगर (ACPI_SUCCESS(status)) अणु
			/*
			 * The parse_loop executes AML until the method terminates
			 * or calls another method.
			 */
			status = acpi_ps_parse_loop(walk_state);
		पूर्ण

		ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
				  "Completed one call to walk loop, %s State=%p\n",
				  acpi_क्रमmat_exception(status), walk_state));

		अगर (walk_state->method_pathname && walk_state->method_is_nested) अणु

			/* Optional object evaluation log */

			ACPI_DEBUG_PRINT_RAW((ACPI_DB_EVALUATION,
					      "%-26s:  %*s%s\n",
					      "   Exit nested method",
					      (walk_state->
					       method_nesting_depth + 1) * 3,
					      " ",
					      &walk_state->method_pathname[1]));

			ACPI_FREE(walk_state->method_pathname);
			walk_state->method_is_nested = FALSE;
		पूर्ण
		अगर (status == AE_CTRL_TRANSFER) अणु
			/*
			 * A method call was detected.
			 * Transfer control to the called control method
			 */
			status =
			    acpi_ds_call_control_method(thपढ़ो, walk_state,
							शून्य);
			अगर (ACPI_FAILURE(status)) अणु
				status =
				    acpi_ds_method_error(status, walk_state);
			पूर्ण

			/*
			 * If the transfer to the new method method call worked,
			 * a new walk state was created -- get it
			 */
			walk_state = acpi_ds_get_current_walk_state(thपढ़ो);
			जारी;
		पूर्ण अन्यथा अगर (status == AE_CTRL_TERMINATE) अणु
			status = AE_OK;
		पूर्ण अन्यथा अगर ((status != AE_OK) && (walk_state->method_desc)) अणु

			/* Either the method parse or actual execution failed */

			acpi_ex_निकास_पूर्णांकerpreter();
			अगर (status == AE_ABORT_METHOD) अणु
				acpi_ns_prपूर्णांक_node_pathname(walk_state->
							    method_node,
							    "Aborting method");
				acpi_os_म_लिखो("\n");
			पूर्ण अन्यथा अणु
				ACPI_ERROR_METHOD("Aborting method",
						  walk_state->method_node, शून्य,
						  status);
			पूर्ण
			acpi_ex_enter_पूर्णांकerpreter();

			/* Check क्रम possible multi-thपढ़ो reentrancy problem */

			अगर ((status == AE_ALREADY_EXISTS) &&
			    (!(walk_state->method_desc->method.info_flags &
			       ACPI_METHOD_SERIALIZED))) अणु
				/*
				 * Method is not serialized and tried to create an object
				 * twice. The probable cause is that the method cannot
				 * handle reentrancy. Mark as "pending serialized" now, and
				 * then mark "serialized" when the last thपढ़ो निकासs.
				 */
				walk_state->method_desc->method.info_flags |=
				    ACPI_METHOD_SERIALIZED_PENDING;
			पूर्ण
		पूर्ण

		/* We are करोne with this walk, move on to the parent अगर any */

		walk_state = acpi_ds_pop_walk_state(thपढ़ो);

		/* Reset the current scope to the beginning of scope stack */

		acpi_ds_scope_stack_clear(walk_state);

		/*
		 * If we just वापसed from the execution of a control method or अगर we
		 * encountered an error during the method parse phase, there's lots of
		 * cleanup to करो
		 */
		अगर (((walk_state->parse_flags & ACPI_PARSE_MODE_MASK) ==
		     ACPI_PARSE_EXECUTE &&
		     !(walk_state->parse_flags & ACPI_PARSE_MODULE_LEVEL)) ||
		    (ACPI_FAILURE(status))) अणु
			acpi_ds_terminate_control_method(walk_state->
							 method_desc,
							 walk_state);
		पूर्ण

		/* Delete this walk state and all linked control states */

		acpi_ps_cleanup_scope(&walk_state->parser_state);
		previous_walk_state = walk_state;

		ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
				  "ReturnValue=%p, ImplicitValue=%p State=%p\n",
				  walk_state->वापस_desc,
				  walk_state->implicit_वापस_obj, walk_state));

		/* Check अगर we have restarted a preempted walk */

		walk_state = acpi_ds_get_current_walk_state(thपढ़ो);
		अगर (walk_state) अणु
			अगर (ACPI_SUCCESS(status)) अणु
				/*
				 * There is another walk state, restart it.
				 * If the method वापस value is not used by the parent,
				 * The object is deleted
				 */
				अगर (!previous_walk_state->वापस_desc) अणु
					/*
					 * In slack mode execution, अगर there is no वापस value
					 * we should implicitly वापस zero (0) as a शेष value.
					 */
					अगर (acpi_gbl_enable_पूर्णांकerpreter_slack &&
					    !previous_walk_state->
					    implicit_वापस_obj) अणु
						previous_walk_state->
						    implicit_वापस_obj =
						    acpi_ut_create_पूर्णांकeger_object
						    ((u64) 0);
						अगर (!previous_walk_state->
						    implicit_वापस_obj) अणु
							वापस_ACPI_STATUS
							    (AE_NO_MEMORY);
						पूर्ण
					पूर्ण

					/* Restart the calling control method */

					status =
					    acpi_ds_restart_control_method
					    (walk_state,
					     previous_walk_state->
					     implicit_वापस_obj);
				पूर्ण अन्यथा अणु
					/*
					 * We have a valid वापस value, delete any implicit
					 * वापस value.
					 */
					acpi_ds_clear_implicit_वापस
					    (previous_walk_state);

					status =
					    acpi_ds_restart_control_method
					    (walk_state,
					     previous_walk_state->वापस_desc);
				पूर्ण
				अगर (ACPI_SUCCESS(status)) अणु
					walk_state->walk_type |=
					    ACPI_WALK_METHOD_RESTART;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* On error, delete any वापस object or implicit वापस */

				acpi_ut_हटाओ_reference(previous_walk_state->
							 वापस_desc);
				acpi_ds_clear_implicit_वापस
				    (previous_walk_state);
			पूर्ण
		पूर्ण

		/*
		 * Just completed a 1st-level method, save the final पूर्णांकernal वापस
		 * value (अगर any)
		 */
		अन्यथा अगर (previous_walk_state->caller_वापस_desc) अणु
			अगर (previous_walk_state->implicit_वापस_obj) अणु
				*(previous_walk_state->caller_वापस_desc) =
				    previous_walk_state->implicit_वापस_obj;
			पूर्ण अन्यथा अणु
				/* शून्य अगर no वापस value */

				*(previous_walk_state->caller_वापस_desc) =
				    previous_walk_state->वापस_desc;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (previous_walk_state->वापस_desc) अणु

				/* Caller करोesn't want it, must delete it */

				acpi_ut_हटाओ_reference(previous_walk_state->
							 वापस_desc);
			पूर्ण
			अगर (previous_walk_state->implicit_वापस_obj) अणु

				/* Caller करोesn't want it, must delete it */

				acpi_ut_हटाओ_reference(previous_walk_state->
							 implicit_वापस_obj);
			पूर्ण
		पूर्ण

		acpi_ds_delete_walk_state(previous_walk_state);
	पूर्ण

	/* Normal निकास */

	acpi_ex_release_all_mutexes(thपढ़ो);
	acpi_ut_delete_generic_state(ACPI_CAST_PTR
				     (जोड़ acpi_generic_state, thपढ़ो));
	acpi_gbl_current_walk_list = prev_walk_list;
	वापस_ACPI_STATUS(status);
पूर्ण
