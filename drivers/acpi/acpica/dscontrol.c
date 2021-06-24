<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: dscontrol - Support क्रम execution control opcodes -
 *                          अगर/अन्यथा/जबतक/वापस
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "amlcode.h"
#समावेश "acdispat.h"
#समावेश "acinterp.h"
#समावेश "acdebug.h"

#घोषणा _COMPONENT          ACPI_DISPATCHER
ACPI_MODULE_NAME("dscontrol")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_exec_begin_control_op
 *
 * PARAMETERS:  walk_list       - The list that owns the walk stack
 *              op              - The control Op
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Handles all control ops encountered during control method
 *              execution.
 *
 ******************************************************************************/
acpi_status
acpi_ds_exec_begin_control_op(काष्ठा acpi_walk_state *walk_state,
			      जोड़ acpi_parse_object *op)
अणु
	acpi_status status = AE_OK;
	जोड़ acpi_generic_state *control_state;

	ACPI_FUNCTION_NAME(ds_exec_begin_control_op);

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH, "Op=%p Opcode=%2.2X State=%p\n",
			  op, op->common.aml_opcode, walk_state));

	चयन (op->common.aml_opcode) अणु
	हाल AML_WHILE_OP:
		/*
		 * If this is an additional iteration of a जबतक loop, जारी.
		 * There is no need to allocate a new control state.
		 */
		अगर (walk_state->control_state) अणु
			अगर (walk_state->control_state->control.
			    aml_predicate_start ==
			    (walk_state->parser_state.aml - 1)) अणु

				/* Reset the state to start-of-loop */

				walk_state->control_state->common.state =
				    ACPI_CONTROL_CONDITIONAL_EXECUTING;
				अवरोध;
			पूर्ण
		पूर्ण

		ACPI_FALLTHROUGH;

	हाल AML_IF_OP:
		/*
		 * IF/WHILE: Create a new control state to manage these
		 * स्थिरructs. We need to manage these as a stack, in order
		 * to handle nesting.
		 */
		control_state = acpi_ut_create_control_state();
		अगर (!control_state) अणु
			status = AE_NO_MEMORY;
			अवरोध;
		पूर्ण
		/*
		 * Save a poपूर्णांकer to the predicate क्रम multiple executions
		 * of a loop
		 */
		control_state->control.aml_predicate_start =
		    walk_state->parser_state.aml - 1;
		control_state->control.package_end =
		    walk_state->parser_state.pkg_end;
		control_state->control.opcode = op->common.aml_opcode;
		control_state->control.loop_समयout = acpi_os_get_समयr() +
		    ((u64)acpi_gbl_max_loop_iterations * ACPI_100NSEC_PER_SEC);

		/* Push the control state on this walk's control stack */

		acpi_ut_push_generic_state(&walk_state->control_state,
					   control_state);
		अवरोध;

	हाल AML_ELSE_OP:

		/* Predicate is in the state object */
		/* If predicate is true, the IF was executed, ignore ELSE part */

		अगर (walk_state->last_predicate) अणु
			status = AE_CTRL_TRUE;
		पूर्ण

		अवरोध;

	हाल AML_RETURN_OP:

		अवरोध;

	शेष:

		अवरोध;
	पूर्ण

	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_exec_end_control_op
 *
 * PARAMETERS:  walk_list       - The list that owns the walk stack
 *              op              - The control Op
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Handles all control ops encountered during control method
 *              execution.
 *
 ******************************************************************************/

acpi_status
acpi_ds_exec_end_control_op(काष्ठा acpi_walk_state *walk_state,
			    जोड़ acpi_parse_object *op)
अणु
	acpi_status status = AE_OK;
	जोड़ acpi_generic_state *control_state;

	ACPI_FUNCTION_NAME(ds_exec_end_control_op);

	चयन (op->common.aml_opcode) अणु
	हाल AML_IF_OP:

		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH, "[IF_OP] Op=%p\n", op));

		/*
		 * Save the result of the predicate in हाल there is an
		 * ELSE to come
		 */
		walk_state->last_predicate =
		    (u8)walk_state->control_state->common.value;

		/*
		 * Pop the control state that was created at the start
		 * of the IF and मुक्त it
		 */
		control_state =
		    acpi_ut_pop_generic_state(&walk_state->control_state);
		acpi_ut_delete_generic_state(control_state);
		अवरोध;

	हाल AML_ELSE_OP:

		अवरोध;

	हाल AML_WHILE_OP:

		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH, "[WHILE_OP] Op=%p\n", op));

		control_state = walk_state->control_state;
		अगर (control_state->common.value) अणु

			/* Predicate was true, the body of the loop was just executed */

			/*
			 * This infinite loop detection mechanism allows the पूर्णांकerpreter
			 * to escape possibly infinite loops. This can occur in poorly
			 * written AML when the hardware करोes not respond within a जबतक
			 * loop and the loop करोes not implement a समयout.
			 */
			अगर (ACPI_TIME_AFTER(acpi_os_get_समयr(),
					    control_state->control.
					    loop_समयout)) अणु
				status = AE_AML_LOOP_TIMEOUT;
				अवरोध;
			पूर्ण

			/*
			 * Go back and evaluate the predicate and maybe execute the loop
			 * another समय
			 */
			status = AE_CTRL_PENDING;
			walk_state->aml_last_जबतक =
			    control_state->control.aml_predicate_start;
			अवरोध;
		पूर्ण

		/* Predicate was false, terminate this जबतक loop */

		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
				  "[WHILE_OP] termination! Op=%p\n", op));

		/* Pop this control state and मुक्त it */

		control_state =
		    acpi_ut_pop_generic_state(&walk_state->control_state);
		acpi_ut_delete_generic_state(control_state);
		अवरोध;

	हाल AML_RETURN_OP:

		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
				  "[RETURN_OP] Op=%p Arg=%p\n", op,
				  op->common.value.arg));

		/*
		 * One optional opeअक्रम -- the वापस value
		 * It can be either an immediate opeअक्रम or a result that
		 * has been bubbled up the tree
		 */
		अगर (op->common.value.arg) अणु

			/* Since we have a real Return(), delete any implicit वापस */

			acpi_ds_clear_implicit_वापस(walk_state);

			/* Return statement has an immediate opeअक्रम */

			status =
			    acpi_ds_create_opeअक्रमs(walk_state,
						    op->common.value.arg);
			अगर (ACPI_FAILURE(status)) अणु
				वापस (status);
			पूर्ण

			/*
			 * If value being वापसed is a Reference (such as
			 * an arg or local), resolve it now because it may
			 * cease to exist at the end of the method.
			 */
			status =
			    acpi_ex_resolve_to_value(&walk_state->opeअक्रमs[0],
						     walk_state);
			अगर (ACPI_FAILURE(status)) अणु
				वापस (status);
			पूर्ण

			/*
			 * Get the वापस value and save as the last result
			 * value. This is the only place where walk_state->वापस_desc
			 * is set to anything other than zero!
			 */
			walk_state->वापस_desc = walk_state->opeअक्रमs[0];
		पूर्ण अन्यथा अगर (walk_state->result_count) अणु

			/* Since we have a real Return(), delete any implicit वापस */

			acpi_ds_clear_implicit_वापस(walk_state);

			/*
			 * The वापस value has come from a previous calculation.
			 *
			 * If value being वापसed is a Reference (such as
			 * an arg or local), resolve it now because it may
			 * cease to exist at the end of the method.
			 *
			 * Allow references created by the Index चालक to वापस
			 * unchanged.
			 */
			अगर ((ACPI_GET_DESCRIPTOR_TYPE
			     (walk_state->results->results.obj_desc[0]) ==
			     ACPI_DESC_TYPE_OPERAND)
			    && ((walk_state->results->results.obj_desc[0])->
				common.type == ACPI_TYPE_LOCAL_REFERENCE)
			    && ((walk_state->results->results.obj_desc[0])->
				reference.class != ACPI_REFCLASS_INDEX)) अणु
				status =
				    acpi_ex_resolve_to_value(&walk_state->
							     results->results.
							     obj_desc[0],
							     walk_state);
				अगर (ACPI_FAILURE(status)) अणु
					वापस (status);
				पूर्ण
			पूर्ण

			walk_state->वापस_desc =
			    walk_state->results->results.obj_desc[0];
		पूर्ण अन्यथा अणु
			/* No वापस opeअक्रम */

			अगर (walk_state->num_opeअक्रमs) अणु
				acpi_ut_हटाओ_reference(walk_state->
							 opeअक्रमs[0]);
			पूर्ण

			walk_state->opeअक्रमs[0] = शून्य;
			walk_state->num_opeअक्रमs = 0;
			walk_state->वापस_desc = शून्य;
		पूर्ण

		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
				  "Completed RETURN_OP State=%p, RetVal=%p\n",
				  walk_state, walk_state->वापस_desc));

		/* End the control method execution right now */

		status = AE_CTRL_TERMINATE;
		अवरोध;

	हाल AML_NOOP_OP:

		/* Just करो nothing! */

		अवरोध;

	हाल AML_BREAKPOINT_OP:

		acpi_db_संकेत_अवरोध_poपूर्णांक(walk_state);

		/* Call to the OSL in हाल OS wants a piece of the action */

		status = acpi_os_संकेत(ACPI_SIGNAL_BREAKPOINT,
					"Executed AML Breakpoint opcode");
		अवरोध;

	हाल AML_BREAK_OP:
	हाल AML_CONTINUE_OP:	/* ACPI 2.0 */

		/* Pop and delete control states until we find a जबतक */

		जबतक (walk_state->control_state &&
		       (walk_state->control_state->control.opcode !=
			AML_WHILE_OP)) अणु
			control_state =
			    acpi_ut_pop_generic_state(&walk_state->
						      control_state);
			acpi_ut_delete_generic_state(control_state);
		पूर्ण

		/* No जबतक found? */

		अगर (!walk_state->control_state) अणु
			वापस (AE_AML_NO_WHILE);
		पूर्ण

		/* Was: walk_state->aml_last_जबतक = walk_state->control_state->Control.aml_predicate_start; */

		walk_state->aml_last_जबतक =
		    walk_state->control_state->control.package_end;

		/* Return status depending on opcode */

		अगर (op->common.aml_opcode == AML_BREAK_OP) अणु
			status = AE_CTRL_BREAK;
		पूर्ण अन्यथा अणु
			status = AE_CTRL_CONTINUE;
		पूर्ण
		अवरोध;

	शेष:

		ACPI_ERROR((AE_INFO, "Unknown control opcode=0x%X Op=%p",
			    op->common.aml_opcode, op));

		status = AE_AML_BAD_OPCODE;
		अवरोध;
	पूर्ण

	वापस (status);
पूर्ण
