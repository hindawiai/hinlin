<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: psloop - Main AML parse loop
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

/*
 * Parse the AML and build an operation tree as most पूर्णांकerpreters, (such as
 * Perl) करो. Parsing is करोne by hand rather than with a YACC generated parser
 * to tightly स्थिरrain stack and dynamic memory usage. Parsing is kept
 * flexible and the code fairly compact by parsing based on a list of AML
 * opcode ढाँचाs in aml_op_info[].
 */

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acinterp.h"
#समावेश "acparser.h"
#समावेश "acdispat.h"
#समावेश "amlcode.h"
#समावेश "acconvert.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_PARSER
ACPI_MODULE_NAME("psloop")

/* Local prototypes */
अटल acpi_status
acpi_ps_get_arguments(काष्ठा acpi_walk_state *walk_state,
		      u8 * aml_op_start, जोड़ acpi_parse_object *op);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_arguments
 *
 * PARAMETERS:  walk_state          - Current state
 *              aml_op_start        - Op start in AML
 *              op                  - Current Op
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get arguments क्रम passed Op.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ps_get_arguments(काष्ठा acpi_walk_state *walk_state,
		      u8 * aml_op_start, जोड़ acpi_parse_object *op)
अणु
	acpi_status status = AE_OK;
	जोड़ acpi_parse_object *arg = शून्य;

	ACPI_FUNCTION_TRACE_PTR(ps_get_arguments, walk_state);

	ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
			  "Get arguments for opcode [%s]\n",
			  op->common.aml_op_name));

	चयन (op->common.aml_opcode) अणु
	हाल AML_BYTE_OP:	/* AML_BYTEDATA_ARG */
	हाल AML_WORD_OP:	/* AML_WORDDATA_ARG */
	हाल AML_DWORD_OP:	/* AML_DWORDATA_ARG */
	हाल AML_QWORD_OP:	/* AML_QWORDATA_ARG */
	हाल AML_STRING_OP:	/* AML_ASCIICHARLIST_ARG */

		/* Fill in स्थिरant or string argument directly */

		acpi_ps_get_next_simple_arg(&(walk_state->parser_state),
					    GET_CURRENT_ARG_TYPE(walk_state->
								 arg_types),
					    op);
		अवरोध;

	हाल AML_INT_NAMEPATH_OP:	/* AML_NAMESTRING_ARG */

		status = acpi_ps_get_next_namepath(walk_state,
						   &(walk_state->parser_state),
						   op,
						   ACPI_POSSIBLE_METHOD_CALL);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		walk_state->arg_types = 0;
		अवरोध;

	शेष:
		/*
		 * Op is not a स्थिरant or string, append each argument to the Op
		 */
		जबतक (GET_CURRENT_ARG_TYPE(walk_state->arg_types) &&
		       !walk_state->arg_count) अणु
			walk_state->aml = walk_state->parser_state.aml;

			चयन (op->common.aml_opcode) अणु
			हाल AML_METHOD_OP:
			हाल AML_BUFFER_OP:
			हाल AML_PACKAGE_OP:
			हाल AML_VARIABLE_PACKAGE_OP:
			हाल AML_WHILE_OP:

				अवरोध;

			शेष:

				ASL_CV_CAPTURE_COMMENTS(walk_state);
				अवरोध;
			पूर्ण

			status =
			    acpi_ps_get_next_arg(walk_state,
						 &(walk_state->parser_state),
						 GET_CURRENT_ARG_TYPE
						 (walk_state->arg_types), &arg);
			अगर (ACPI_FAILURE(status)) अणु
				वापस_ACPI_STATUS(status);
			पूर्ण

			अगर (arg) अणु
				acpi_ps_append_arg(op, arg);
			पूर्ण

			INCREMENT_ARG_LIST(walk_state->arg_types);
		पूर्ण

		ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
				  "Final argument count: %8.8X pass %u\n",
				  walk_state->arg_count,
				  walk_state->pass_number));

		/* Special processing क्रम certain opcodes */

		चयन (op->common.aml_opcode) अणु
		हाल AML_METHOD_OP:
			/*
			 * Skip parsing of control method because we करोn't have enough
			 * info in the first pass to parse it correctly.
			 *
			 * Save the length and address of the body
			 */
			op->named.data = walk_state->parser_state.aml;
			op->named.length = (u32)
			    (walk_state->parser_state.pkg_end -
			     walk_state->parser_state.aml);

			/* Skip body of method */

			walk_state->parser_state.aml =
			    walk_state->parser_state.pkg_end;
			walk_state->arg_count = 0;
			अवरोध;

		हाल AML_BUFFER_OP:
		हाल AML_PACKAGE_OP:
		हाल AML_VARIABLE_PACKAGE_OP:

			अगर ((op->common.parent) &&
			    (op->common.parent->common.aml_opcode ==
			     AML_NAME_OP)
			    && (walk_state->pass_number <=
				ACPI_IMODE_LOAD_PASS2)) अणु
				ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
						  "Setup Package/Buffer: Pass %u, AML Ptr: %p\n",
						  walk_state->pass_number,
						  aml_op_start));

				/*
				 * Skip parsing of Buffers and Packages because we करोn't have
				 * enough info in the first pass to parse them correctly.
				 */
				op->named.data = aml_op_start;
				op->named.length = (u32)
				    (walk_state->parser_state.pkg_end -
				     aml_op_start);

				/* Skip body */

				walk_state->parser_state.aml =
				    walk_state->parser_state.pkg_end;
				walk_state->arg_count = 0;
			पूर्ण
			अवरोध;

		हाल AML_WHILE_OP:

			अगर (walk_state->control_state) अणु
				walk_state->control_state->control.package_end =
				    walk_state->parser_state.pkg_end;
			पूर्ण
			अवरोध;

		शेष:

			/* No action क्रम all other opcodes */

			अवरोध;
		पूर्ण

		अवरोध;
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_parse_loop
 *
 * PARAMETERS:  walk_state          - Current state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Parse AML (poपूर्णांकed to by the current parser state) and वापस
 *              a tree of ops.
 *
 ******************************************************************************/

acpi_status acpi_ps_parse_loop(काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status = AE_OK;
	जोड़ acpi_parse_object *op = शून्य;	/* current op */
	काष्ठा acpi_parse_state *parser_state;
	u8 *aml_op_start = शून्य;
	u8 opcode_length;

	ACPI_FUNCTION_TRACE_PTR(ps_parse_loop, walk_state);

	अगर (walk_state->descending_callback == शून्य) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	parser_state = &walk_state->parser_state;
	walk_state->arg_types = 0;

#अगर_अघोषित ACPI_CONSTANT_EVAL_ONLY

	अगर (walk_state->walk_type & ACPI_WALK_METHOD_RESTART) अणु

		/* We are restarting a preempted control method */

		अगर (acpi_ps_has_completed_scope(parser_state)) अणु
			/*
			 * We must check अगर a predicate to an IF or WHILE statement
			 * was just completed
			 */
			अगर ((parser_state->scope->parse_scope.op) &&
			    ((parser_state->scope->parse_scope.op->common.
			      aml_opcode == AML_IF_OP)
			     || (parser_state->scope->parse_scope.op->common.
				 aml_opcode == AML_WHILE_OP))
			    && (walk_state->control_state)
			    && (walk_state->control_state->common.state ==
				ACPI_CONTROL_PREDICATE_EXECUTING)) अणु
				/*
				 * A predicate was just completed, get the value of the
				 * predicate and branch based on that value
				 */
				walk_state->op = शून्य;
				status =
				    acpi_ds_get_predicate_value(walk_state,
								ACPI_TO_POINTER
								(TRUE));
				अगर (ACPI_FAILURE(status)
				    && !ACPI_CNTL_EXCEPTION(status)) अणु
					अगर (status == AE_AML_NO_RETURN_VALUE) अणु
						ACPI_EXCEPTION((AE_INFO, status,
								"Invoked method did not return a value"));
					पूर्ण

					ACPI_EXCEPTION((AE_INFO, status,
							"GetPredicate Failed"));
					वापस_ACPI_STATUS(status);
				पूर्ण

				status =
				    acpi_ps_next_parse_state(walk_state, op,
							     status);
			पूर्ण

			acpi_ps_pop_scope(parser_state, &op,
					  &walk_state->arg_types,
					  &walk_state->arg_count);
			ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
					  "Popped scope, Op=%p\n", op));
		पूर्ण अन्यथा अगर (walk_state->prev_op) अणु

			/* We were in the middle of an op */

			op = walk_state->prev_op;
			walk_state->arg_types = walk_state->prev_arg_types;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* Iterative parsing loop, जबतक there is more AML to process: */

	जबतक ((parser_state->aml < parser_state->aml_end) || (op)) अणु
		ASL_CV_CAPTURE_COMMENTS(walk_state);

		aml_op_start = parser_state->aml;
		अगर (!op) अणु
			status =
			    acpi_ps_create_op(walk_state, aml_op_start, &op);
			अगर (ACPI_FAILURE(status)) अणु
				/*
				 * ACPI_PARSE_MODULE_LEVEL means that we are loading a table by
				 * executing it as a control method. However, अगर we encounter
				 * an error जबतक loading the table, we need to keep trying to
				 * load the table rather than पातing the table load. Set the
				 * status to AE_OK to proceed with the table load.
				 */
				अगर ((walk_state->
				     parse_flags & ACPI_PARSE_MODULE_LEVEL)
				    && ((status == AE_ALREADY_EXISTS)
					|| (status == AE_NOT_FOUND))) अणु
					status = AE_OK;
				पूर्ण
				अगर (status == AE_CTRL_PARSE_CONTINUE) अणु
					जारी;
				पूर्ण

				अगर (status == AE_CTRL_PARSE_PENDING) अणु
					status = AE_OK;
				पूर्ण

				अगर (status == AE_CTRL_TERMINATE) अणु
					वापस_ACPI_STATUS(status);
				पूर्ण

				status =
				    acpi_ps_complete_op(walk_state, &op,
							status);
				अगर (ACPI_FAILURE(status)) अणु
					वापस_ACPI_STATUS(status);
				पूर्ण
				अगर (acpi_ns_खोलोs_scope
				    (acpi_ps_get_opcode_info
				     (walk_state->opcode)->object_type)) अणु
					/*
					 * If the scope/device op fails to parse, skip the body of
					 * the scope op because the parse failure indicates that
					 * the device may not exist.
					 */
					ACPI_INFO(("Skipping parse of AML opcode: %s (0x%4.4X)", acpi_ps_get_opcode_name(walk_state->opcode), walk_state->opcode));

					/*
					 * Determine the opcode length beक्रमe skipping the opcode.
					 * An opcode can be 1 byte or 2 bytes in length.
					 */
					opcode_length = 1;
					अगर ((walk_state->opcode & 0xFF00) ==
					    AML_EXTENDED_OPCODE) अणु
						opcode_length = 2;
					पूर्ण
					walk_state->parser_state.aml =
					    walk_state->aml + opcode_length;

					walk_state->parser_state.aml =
					    acpi_ps_get_next_package_end
					    (&walk_state->parser_state);
					walk_state->aml =
					    walk_state->parser_state.aml;
				पूर्ण

				जारी;
			पूर्ण

			acpi_ex_start_trace_opcode(op, walk_state);
		पूर्ण

		/*
		 * Start arg_count at zero because we करोn't know अगर there are
		 * any args yet
		 */
		walk_state->arg_count = 0;

		चयन (op->common.aml_opcode) अणु
		हाल AML_BYTE_OP:
		हाल AML_WORD_OP:
		हाल AML_DWORD_OP:
		हाल AML_QWORD_OP:

			अवरोध;

		शेष:

			ASL_CV_CAPTURE_COMMENTS(walk_state);
			अवरोध;
		पूर्ण

		/* Are there any arguments that must be processed? */

		अगर (walk_state->arg_types) अणु

			/* Get arguments */

			status =
			    acpi_ps_get_arguments(walk_state, aml_op_start, op);
			अगर (ACPI_FAILURE(status)) अणु
				status =
				    acpi_ps_complete_op(walk_state, &op,
							status);
				अगर (ACPI_FAILURE(status)) अणु
					वापस_ACPI_STATUS(status);
				पूर्ण
				अगर ((walk_state->control_state) &&
				    ((walk_state->control_state->control.
				      opcode == AML_IF_OP)
				     || (walk_state->control_state->control.
					 opcode == AML_WHILE_OP))) अणु
					/*
					 * If the अगर/जबतक op fails to parse, we will skip parsing
					 * the body of the op.
					 */
					parser_state->aml =
					    walk_state->control_state->control.
					    aml_predicate_start + 1;
					parser_state->aml =
					    acpi_ps_get_next_package_end
					    (parser_state);
					walk_state->aml = parser_state->aml;

					ACPI_ERROR((AE_INFO,
						    "Skipping While/If block"));
					अगर (*walk_state->aml == AML_ELSE_OP) अणु
						ACPI_ERROR((AE_INFO,
							    "Skipping Else block"));
						walk_state->parser_state.aml =
						    walk_state->aml + 1;
						walk_state->parser_state.aml =
						    acpi_ps_get_next_package_end
						    (parser_state);
						walk_state->aml =
						    parser_state->aml;
					पूर्ण
					ACPI_FREE(acpi_ut_pop_generic_state
						  (&walk_state->control_state));
				पूर्ण
				op = शून्य;
				जारी;
			पूर्ण
		पूर्ण

		/* Check क्रम arguments that need to be processed */

		ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
				  "Parseloop: argument count: %8.8X\n",
				  walk_state->arg_count));

		अगर (walk_state->arg_count) अणु
			/*
			 * There are arguments (complex ones), push Op and
			 * prepare क्रम argument
			 */
			status = acpi_ps_push_scope(parser_state, op,
						    walk_state->arg_types,
						    walk_state->arg_count);
			अगर (ACPI_FAILURE(status)) अणु
				status =
				    acpi_ps_complete_op(walk_state, &op,
							status);
				अगर (ACPI_FAILURE(status)) अणु
					वापस_ACPI_STATUS(status);
				पूर्ण

				जारी;
			पूर्ण

			op = शून्य;
			जारी;
		पूर्ण

		/*
		 * All arguments have been processed -- Op is complete,
		 * prepare क्रम next
		 */
		walk_state->op_info =
		    acpi_ps_get_opcode_info(op->common.aml_opcode);
		अगर (walk_state->op_info->flags & AML_NAMED) अणु
			अगर (op->common.aml_opcode == AML_REGION_OP ||
			    op->common.aml_opcode == AML_DATA_REGION_OP) अणु
				/*
				 * Skip parsing of control method or opregion body,
				 * because we करोn't have enough info in the first pass
				 * to parse them correctly.
				 *
				 * Completed parsing an op_region declaration, we now
				 * know the length.
				 */
				op->named.length =
				    (u32) (parser_state->aml - op->named.data);
			पूर्ण
		पूर्ण

		अगर (walk_state->op_info->flags & AML_CREATE) अणु
			/*
			 * Backup to beginning of create_XXXfield declaration (1 क्रम
			 * Opcode)
			 *
			 * body_length is unknown until we parse the body
			 */
			op->named.length =
			    (u32) (parser_state->aml - op->named.data);
		पूर्ण

		अगर (op->common.aml_opcode == AML_BANK_FIELD_OP) अणु
			/*
			 * Backup to beginning of bank_field declaration
			 *
			 * body_length is unknown until we parse the body
			 */
			op->named.length =
			    (u32) (parser_state->aml - op->named.data);
		पूर्ण

		/* This op complete, notअगरy the dispatcher */

		अगर (walk_state->ascending_callback != शून्य) अणु
			walk_state->op = op;
			walk_state->opcode = op->common.aml_opcode;

			status = walk_state->ascending_callback(walk_state);
			status =
			    acpi_ps_next_parse_state(walk_state, op, status);
			अगर (status == AE_CTRL_PENDING) अणु
				status = AE_OK;
			पूर्ण अन्यथा
			    अगर ((walk_state->
				 parse_flags & ACPI_PARSE_MODULE_LEVEL)
				&& (ACPI_AML_EXCEPTION(status)
				    || status == AE_ALREADY_EXISTS
				    || status == AE_NOT_FOUND)) अणु
				/*
				 * ACPI_PARSE_MODULE_LEVEL flag means that we
				 * are currently loading a table by executing
				 * it as a control method. However, अगर we
				 * encounter an error जबतक loading the table,
				 * we need to keep trying to load the table
				 * rather than पातing the table load (setting
				 * the status to AE_OK जारीs the table
				 * load). If we get a failure at this poपूर्णांक, it
				 * means that the dispatcher got an error जबतक
				 * trying to execute the Op.
				 */
				status = AE_OK;
			पूर्ण
		पूर्ण

		status = acpi_ps_complete_op(walk_state, &op, status);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

	पूर्ण			/* जबतक parser_state->Aml */

	status = acpi_ps_complete_final_op(walk_state, op, status);
	वापस_ACPI_STATUS(status);
पूर्ण
