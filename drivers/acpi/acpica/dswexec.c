<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: dswexec - Dispatcher method execution callbacks;
 *                        dispatch to पूर्णांकerpreter.
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acparser.h"
#समावेश "amlcode.h"
#समावेश "acdispat.h"
#समावेश "acinterp.h"
#समावेश "acnamesp.h"
#समावेश "acdebug.h"
#अगर_घोषित ACPI_EXEC_APP
#समावेश "aecommon.h"
#पूर्ण_अगर

#घोषणा _COMPONENT          ACPI_DISPATCHER
ACPI_MODULE_NAME("dswexec")

/*
 * Dispatch table क्रम opcode classes
 */
अटल acpi_execute_op acpi_gbl_op_type_dispatch[] = अणु
	acpi_ex_opcode_0A_0T_1R,
	acpi_ex_opcode_1A_0T_0R,
	acpi_ex_opcode_1A_0T_1R,
	acpi_ex_opcode_1A_1T_0R,
	acpi_ex_opcode_1A_1T_1R,
	acpi_ex_opcode_2A_0T_0R,
	acpi_ex_opcode_2A_0T_1R,
	acpi_ex_opcode_2A_1T_1R,
	acpi_ex_opcode_2A_2T_1R,
	acpi_ex_opcode_3A_0T_0R,
	acpi_ex_opcode_3A_1T_1R,
	acpi_ex_opcode_6A_0T_1R
पूर्ण;

/*****************************************************************************
 *
 * FUNCTION:    acpi_ds_get_predicate_value
 *
 * PARAMETERS:  walk_state      - Current state of the parse tree walk
 *              result_obj      - अगर non-zero, pop result from result stack
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get the result of a predicate evaluation
 *
 ****************************************************************************/

acpi_status
acpi_ds_get_predicate_value(काष्ठा acpi_walk_state *walk_state,
			    जोड़ acpi_opeअक्रम_object *result_obj)
अणु
	acpi_status status = AE_OK;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_opeअक्रम_object *local_obj_desc = शून्य;

	ACPI_FUNCTION_TRACE_PTR(ds_get_predicate_value, walk_state);

	walk_state->control_state->common.state = 0;

	अगर (result_obj) अणु
		status = acpi_ds_result_pop(&obj_desc, walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_EXCEPTION((AE_INFO, status,
					"Could not get result from predicate evaluation"));

			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण अन्यथा अणु
		status = acpi_ds_create_opeअक्रम(walk_state, walk_state->op, 0);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		status =
		    acpi_ex_resolve_to_value(&walk_state->opeअक्रमs[0],
					     walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		obj_desc = walk_state->opeअक्रमs[0];
	पूर्ण

	अगर (!obj_desc) अणु
		ACPI_ERROR((AE_INFO,
			    "No predicate ObjDesc=%p State=%p",
			    obj_desc, walk_state));

		वापस_ACPI_STATUS(AE_AML_NO_OPERAND);
	पूर्ण

	/*
	 * Result of predicate evaluation must be an Integer
	 * object. Implicitly convert the argument अगर necessary.
	 */
	status = acpi_ex_convert_to_पूर्णांकeger(obj_desc, &local_obj_desc,
					    ACPI_IMPLICIT_CONVERSION);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ cleanup;
	पूर्ण

	अगर (local_obj_desc->common.type != ACPI_TYPE_INTEGER) अणु
		ACPI_ERROR((AE_INFO,
			    "Bad predicate (not an integer) ObjDesc=%p State=%p Type=0x%X",
			    obj_desc, walk_state, obj_desc->common.type));

		status = AE_AML_OPERAND_TYPE;
		जाओ cleanup;
	पूर्ण

	/* Truncate the predicate to 32-bits अगर necessary */

	(व्योम)acpi_ex_truncate_क्रम32bit_table(local_obj_desc);

	/*
	 * Save the result of the predicate evaluation on
	 * the control stack
	 */
	अगर (local_obj_desc->पूर्णांकeger.value) अणु
		walk_state->control_state->common.value = TRUE;
	पूर्ण अन्यथा अणु
		/*
		 * Predicate is FALSE, we will just toss the
		 * rest of the package
		 */
		walk_state->control_state->common.value = FALSE;
		status = AE_CTRL_FALSE;
	पूर्ण

	/* Predicate can be used क्रम an implicit वापस value */

	(व्योम)acpi_ds_करो_implicit_वापस(local_obj_desc, walk_state, TRUE);

cleanup:

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "Completed a predicate eval=%X Op=%p\n",
			  walk_state->control_state->common.value,
			  walk_state->op));

	/* Break to debugger to display result */

	acpi_db_display_result_object(local_obj_desc, walk_state);

	/*
	 * Delete the predicate result object (we know that
	 * we करोn't need it anymore)
	 */
	अगर (local_obj_desc != obj_desc) अणु
		acpi_ut_हटाओ_reference(local_obj_desc);
	पूर्ण
	acpi_ut_हटाओ_reference(obj_desc);

	walk_state->control_state->common.state = ACPI_CONTROL_NORMAL;
	वापस_ACPI_STATUS(status);
पूर्ण

/*****************************************************************************
 *
 * FUNCTION:    acpi_ds_exec_begin_op
 *
 * PARAMETERS:  walk_state      - Current state of the parse tree walk
 *              out_op          - Where to वापस op अगर a new one is created
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Descending callback used during the execution of control
 *              methods. This is where most चालकs and opeअक्रमs are
 *              dispatched to the पूर्णांकerpreter.
 *
 ****************************************************************************/

acpi_status
acpi_ds_exec_begin_op(काष्ठा acpi_walk_state *walk_state,
		      जोड़ acpi_parse_object **out_op)
अणु
	जोड़ acpi_parse_object *op;
	acpi_status status = AE_OK;
	u32 opcode_class;

	ACPI_FUNCTION_TRACE_PTR(ds_exec_begin_op, walk_state);

	op = walk_state->op;
	अगर (!op) अणु
		status = acpi_ds_load2_begin_op(walk_state, out_op);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ error_निकास;
		पूर्ण

		op = *out_op;
		walk_state->op = op;
		walk_state->opcode = op->common.aml_opcode;
		walk_state->op_info =
		    acpi_ps_get_opcode_info(op->common.aml_opcode);

		अगर (acpi_ns_खोलोs_scope(walk_state->op_info->object_type)) अणु
			ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
					  "(%s) Popping scope for Op %p\n",
					  acpi_ut_get_type_name(walk_state->
								op_info->
								object_type),
					  op));

			status = acpi_ds_scope_stack_pop(walk_state);
			अगर (ACPI_FAILURE(status)) अणु
				जाओ error_निकास;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (op == walk_state->origin) अणु
		अगर (out_op) अणु
			*out_op = op;
		पूर्ण

		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/*
	 * If the previous opcode was a conditional, this opcode
	 * must be the beginning of the associated predicate.
	 * Save this knowledge in the current scope descriptor
	 */
	अगर ((walk_state->control_state) &&
	    (walk_state->control_state->common.state ==
	     ACPI_CONTROL_CONDITIONAL_EXECUTING)) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "Exec predicate Op=%p State=%p\n",
				  op, walk_state));

		walk_state->control_state->common.state =
		    ACPI_CONTROL_PREDICATE_EXECUTING;

		/* Save start of predicate */

		walk_state->control_state->control.predicate_op = op;
	पूर्ण

	opcode_class = walk_state->op_info->class;

	/* We want to send namepaths to the load code */

	अगर (op->common.aml_opcode == AML_INT_NAMEPATH_OP) अणु
		opcode_class = AML_CLASS_NAMED_OBJECT;
	पूर्ण

	/*
	 * Handle the opcode based upon the opcode type
	 */
	चयन (opcode_class) अणु
	हाल AML_CLASS_CONTROL:

		status = acpi_ds_exec_begin_control_op(walk_state, op);
		अवरोध;

	हाल AML_CLASS_NAMED_OBJECT:

		अगर (walk_state->walk_type & ACPI_WALK_METHOD) अणु
			/*
			 * Found a named object declaration during method execution;
			 * we must enter this object पूर्णांकo the namespace. The created
			 * object is temporary and will be deleted upon completion of
			 * the execution of this method.
			 *
			 * Note 10/2010: Except क्रम the Scope() op. This opcode करोes
			 * not actually create a new object, it refers to an existing
			 * object. However, क्रम Scope(), we want to indeed खोलो a
			 * new scope.
			 */
			अगर (op->common.aml_opcode != AML_SCOPE_OP) अणु
				status =
				    acpi_ds_load2_begin_op(walk_state, शून्य);
			पूर्ण अन्यथा अणु
				status =
				    acpi_ds_scope_stack_push(op->named.node,
							     op->named.node->
							     type, walk_state);
				अगर (ACPI_FAILURE(status)) अणु
					वापस_ACPI_STATUS(status);
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;

	हाल AML_CLASS_EXECUTE:
	हाल AML_CLASS_CREATE:

		अवरोध;

	शेष:

		अवरोध;
	पूर्ण

	/* Nothing to करो here during method execution */

	वापस_ACPI_STATUS(status);

error_निकास:
	status = acpi_ds_method_error(status, walk_state);
	वापस_ACPI_STATUS(status);
पूर्ण

/*****************************************************************************
 *
 * FUNCTION:    acpi_ds_exec_end_op
 *
 * PARAMETERS:  walk_state      - Current state of the parse tree walk
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Ascending callback used during the execution of control
 *              methods. The only thing we really need to करो here is to
 *              notice the beginning of IF, ELSE, and WHILE blocks.
 *
 ****************************************************************************/

acpi_status acpi_ds_exec_end_op(काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_parse_object *op;
	acpi_status status = AE_OK;
	u32 op_type;
	u32 op_class;
	जोड़ acpi_parse_object *next_op;
	जोड़ acpi_parse_object *first_arg;
#अगर_घोषित ACPI_EXEC_APP
	अक्षर *namepath;
	जोड़ acpi_opeअक्रम_object *obj_desc;
#पूर्ण_अगर

	ACPI_FUNCTION_TRACE_PTR(ds_exec_end_op, walk_state);

	op = walk_state->op;
	op_type = walk_state->op_info->type;
	op_class = walk_state->op_info->class;

	अगर (op_class == AML_CLASS_UNKNOWN) अणु
		ACPI_ERROR((AE_INFO, "Unknown opcode 0x%X",
			    op->common.aml_opcode));
		वापस_ACPI_STATUS(AE_NOT_IMPLEMENTED);
	पूर्ण

	first_arg = op->common.value.arg;

	/* Init the walk state */

	walk_state->num_opeअक्रमs = 0;
	walk_state->opeअक्रम_index = 0;
	walk_state->वापस_desc = शून्य;
	walk_state->result_obj = शून्य;

	/* Call debugger क्रम single step support (DEBUG build only) */

	status = acpi_db_single_step(walk_state, op, op_class);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Decode the Opcode Class */

	चयन (op_class) अणु
	हाल AML_CLASS_ARGUMENT:	/* Constants, literals, etc. */

		अगर (walk_state->opcode == AML_INT_NAMEPATH_OP) अणु
			status = acpi_ds_evaluate_name_path(walk_state);
			अगर (ACPI_FAILURE(status)) अणु
				जाओ cleanup;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल AML_CLASS_EXECUTE:	/* Most चालकs with arguments */

		/* Build resolved opeअक्रम stack */

		status = acpi_ds_create_opeअक्रमs(walk_state, first_arg);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ cleanup;
		पूर्ण

		/*
		 * All opcodes require opeअक्रम resolution, with the only exceptions
		 * being the object_type and size_of चालकs.
		 */
		अगर (!(walk_state->op_info->flags & AML_NO_OPERAND_RESOLVE)) अणु

			/* Resolve all opeअक्रमs */

			status = acpi_ex_resolve_opeअक्रमs(walk_state->opcode,
							  &(walk_state->
							    opeअक्रमs
							    [walk_state->
							     num_opeअक्रमs - 1]),
							  walk_state);
		पूर्ण

		अगर (ACPI_SUCCESS(status)) अणु
			/*
			 * Dispatch the request to the appropriate पूर्णांकerpreter handler
			 * routine. There is one routine per opcode "type" based upon the
			 * number of opcode arguments and वापस type.
			 */
			status =
			    acpi_gbl_op_type_dispatch[op_type] (walk_state);
		पूर्ण अन्यथा अणु
			/*
			 * Treat स्थिरructs of the क्रमm "Store(LocalX,LocalX)" as noops when the
			 * Local is uninitialized.
			 */
			अगर ((status == AE_AML_UNINITIALIZED_LOCAL) &&
			    (walk_state->opcode == AML_STORE_OP) &&
			    (walk_state->opeअक्रमs[0]->common.type ==
			     ACPI_TYPE_LOCAL_REFERENCE)
			    && (walk_state->opeअक्रमs[1]->common.type ==
				ACPI_TYPE_LOCAL_REFERENCE)
			    && (walk_state->opeअक्रमs[0]->reference.class ==
				walk_state->opeअक्रमs[1]->reference.class)
			    && (walk_state->opeअक्रमs[0]->reference.value ==
				walk_state->opeअक्रमs[1]->reference.value)) अणु
				status = AE_OK;
			पूर्ण अन्यथा अणु
				ACPI_EXCEPTION((AE_INFO, status,
						"While resolving operands for [%s]",
						acpi_ps_get_opcode_name
						(walk_state->opcode)));
			पूर्ण
		पूर्ण

		/* Always delete the argument objects and clear the opeअक्रम stack */

		acpi_ds_clear_opeअक्रमs(walk_state);

		/*
		 * If a result object was वापसed from above, push it on the
		 * current result stack
		 */
		अगर (ACPI_SUCCESS(status) && walk_state->result_obj) अणु
			status =
			    acpi_ds_result_push(walk_state->result_obj,
						walk_state);
		पूर्ण
		अवरोध;

	शेष:

		चयन (op_type) अणु
		हाल AML_TYPE_CONTROL:	/* Type 1 opcode, IF/ELSE/WHILE/NOOP */

			/* 1 Opeअक्रम, 0 बाह्यal_result, 0 पूर्णांकernal_result */

			status = acpi_ds_exec_end_control_op(walk_state, op);

			अवरोध;

		हाल AML_TYPE_METHOD_CALL:
			/*
			 * If the method is referenced from within a package
			 * declaration, it is not a invocation of the method, just
			 * a reference to it.
			 */
			अगर ((op->asl.parent) &&
			    ((op->asl.parent->asl.aml_opcode == AML_PACKAGE_OP)
			     || (op->asl.parent->asl.aml_opcode ==
				 AML_VARIABLE_PACKAGE_OP))) अणु
				ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
						  "Method Reference in a Package, Op=%p\n",
						  op));

				op->common.node = (काष्ठा acpi_namespace_node *)
				    op->asl.value.arg->asl.node;
				acpi_ut_add_reference(op->asl.value.arg->asl.
						      node->object);
				वापस_ACPI_STATUS(AE_OK);
			पूर्ण

			ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
					  "Method invocation, Op=%p\n", op));

			/*
			 * (AML_METHODCALL) Op->Asl.Value.Arg->Asl.Node contains
			 * the method Node poपूर्णांकer
			 */
			/* next_op poपूर्णांकs to the op that holds the method name */

			next_op = first_arg;

			/* next_op poपूर्णांकs to first argument op */

			next_op = next_op->common.next;

			/*
			 * Get the method's arguments and put them on the opeअक्रम stack
			 */
			status = acpi_ds_create_opeअक्रमs(walk_state, next_op);
			अगर (ACPI_FAILURE(status)) अणु
				अवरोध;
			पूर्ण

			/*
			 * Since the opeअक्रमs will be passed to another control method,
			 * we must resolve all local references here (Local variables,
			 * arguments to *this* method, etc.)
			 */
			status = acpi_ds_resolve_opeअक्रमs(walk_state);
			अगर (ACPI_FAILURE(status)) अणु

				/* On error, clear all resolved opeअक्रमs */

				acpi_ds_clear_opeअक्रमs(walk_state);
				अवरोध;
			पूर्ण

			/*
			 * Tell the walk loop to preempt this running method and
			 * execute the new method
			 */
			status = AE_CTRL_TRANSFER;

			/*
			 * Return now; we करोn't want to disturb anything,
			 * especially the opeअक्रम count!
			 */
			वापस_ACPI_STATUS(status);

		हाल AML_TYPE_CREATE_FIELD:

			ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
					  "Executing CreateField Buffer/Index Op=%p\n",
					  op));

			status = acpi_ds_load2_end_op(walk_state);
			अगर (ACPI_FAILURE(status)) अणु
				अवरोध;
			पूर्ण

			status =
			    acpi_ds_eval_buffer_field_opeअक्रमs(walk_state, op);
			अगर (ACPI_FAILURE(status)) अणु
				अवरोध;
			पूर्ण
#अगर_घोषित ACPI_EXEC_APP
			/*
			 * acpi_exec support क्रम namespace initialization file (initialize
			 * buffer_fields in this code.)
			 */
			namepath =
			    acpi_ns_get_बाह्यal_pathname(op->common.node);
			status = ae_lookup_init_file_entry(namepath, &obj_desc);
			अगर (ACPI_SUCCESS(status)) अणु
				status =
				    acpi_ex_ग_लिखो_data_to_field(obj_desc,
								op->common.
								node->object,
								शून्य);
				अगर ACPI_FAILURE
					(status) अणु
					ACPI_EXCEPTION((AE_INFO, status,
							"While writing to buffer field"));
					पूर्ण
			पूर्ण
			ACPI_FREE(namepath);
			status = AE_OK;
#पूर्ण_अगर
			अवरोध;

		हाल AML_TYPE_CREATE_OBJECT:

			ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
					  "Executing CreateObject (Buffer/Package) Op=%p Child=%p ParentOpcode=%4.4X\n",
					  op, op->named.value.arg,
					  op->common.parent->common.
					  aml_opcode));

			चयन (op->common.parent->common.aml_opcode) अणु
			हाल AML_NAME_OP:
				/*
				 * Put the Node on the object stack (Contains the ACPI Name
				 * of this object)
				 */
				walk_state->opeअक्रमs[0] = (व्योम *)
				    op->common.parent->common.node;
				walk_state->num_opeअक्रमs = 1;

				status = acpi_ds_create_node(walk_state,
							     op->common.parent->
							     common.node,
							     op->common.parent);
				अगर (ACPI_FAILURE(status)) अणु
					अवरोध;
				पूर्ण

				ACPI_FALLTHROUGH;

			हाल AML_INT_EVAL_SUBTREE_OP:

				status =
				    acpi_ds_eval_data_object_opeअक्रमs
				    (walk_state, op,
				     acpi_ns_get_attached_object(op->common.
								 parent->common.
								 node));
				अवरोध;

			शेष:

				status =
				    acpi_ds_eval_data_object_opeअक्रमs
				    (walk_state, op, शून्य);
				अवरोध;
			पूर्ण

			/*
			 * If a result object was वापसed from above, push it on the
			 * current result stack
			 */
			अगर (walk_state->result_obj) अणु
				status =
				    acpi_ds_result_push(walk_state->result_obj,
							walk_state);
			पूर्ण
			अवरोध;

		हाल AML_TYPE_NAMED_FIELD:
		हाल AML_TYPE_NAMED_COMPLEX:
		हाल AML_TYPE_NAMED_SIMPLE:
		हाल AML_TYPE_NAMED_NO_OBJ:

			status = acpi_ds_load2_end_op(walk_state);
			अगर (ACPI_FAILURE(status)) अणु
				अवरोध;
			पूर्ण

			अगर (op->common.aml_opcode == AML_REGION_OP) अणु
				ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
						  "Executing OpRegion Address/Length Op=%p\n",
						  op));

				status =
				    acpi_ds_eval_region_opeअक्रमs(walk_state,
								 op);
				अगर (ACPI_FAILURE(status)) अणु
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अगर (op->common.aml_opcode == AML_DATA_REGION_OP) अणु
				ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
						  "Executing DataTableRegion Strings Op=%p\n",
						  op));

				status =
				    acpi_ds_eval_table_region_opeअक्रमs
				    (walk_state, op);
				अगर (ACPI_FAILURE(status)) अणु
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अगर (op->common.aml_opcode == AML_BANK_FIELD_OP) अणु
				ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
						  "Executing BankField Op=%p\n",
						  op));

				status =
				    acpi_ds_eval_bank_field_opeअक्रमs(walk_state,
								     op);
				अगर (ACPI_FAILURE(status)) अणु
					अवरोध;
				पूर्ण
			पूर्ण
			अवरोध;

		हाल AML_TYPE_UNDEFINED:

			ACPI_ERROR((AE_INFO,
				    "Undefined opcode type Op=%p", op));
			वापस_ACPI_STATUS(AE_NOT_IMPLEMENTED);

		हाल AML_TYPE_BOGUS:

			ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
					  "Internal opcode=%X type Op=%p\n",
					  walk_state->opcode, op));
			अवरोध;

		शेष:

			ACPI_ERROR((AE_INFO,
				    "Unimplemented opcode, class=0x%X "
				    "type=0x%X Opcode=0x%X Op=%p",
				    op_class, op_type, op->common.aml_opcode,
				    op));

			status = AE_NOT_IMPLEMENTED;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * ACPI 2.0 support क्रम 64-bit पूर्णांकegers: Truncate numeric
	 * result value अगर we are executing from a 32-bit ACPI table
	 */
	(व्योम)acpi_ex_truncate_क्रम32bit_table(walk_state->result_obj);

	/*
	 * Check अगर we just completed the evaluation of a
	 * conditional predicate
	 */
	अगर ((ACPI_SUCCESS(status)) &&
	    (walk_state->control_state) &&
	    (walk_state->control_state->common.state ==
	     ACPI_CONTROL_PREDICATE_EXECUTING) &&
	    (walk_state->control_state->control.predicate_op == op)) अणु
		status =
		    acpi_ds_get_predicate_value(walk_state,
						walk_state->result_obj);
		walk_state->result_obj = शून्य;
	पूर्ण

cleanup:

	अगर (walk_state->result_obj) अणु

		/* Break to debugger to display result */

		acpi_db_display_result_object(walk_state->result_obj,
					      walk_state);

		/*
		 * Delete the result op अगर and only अगर:
		 * Parent will not use the result -- such as any
		 * non-nested type2 op in a method (parent will be method)
		 */
		acpi_ds_delete_result_अगर_not_used(op, walk_state->result_obj,
						  walk_state);
	पूर्ण
#अगर_घोषित _UNDER_DEVELOPMENT

	अगर (walk_state->parser_state.aml == walk_state->parser_state.aml_end) अणु
		acpi_db_method_end(walk_state);
	पूर्ण
#पूर्ण_अगर

	/* Invoke exception handler on error */

	अगर (ACPI_FAILURE(status)) अणु
		status = acpi_ds_method_error(status, walk_state);
	पूर्ण

	/* Always clear the object stack */

	walk_state->num_opeअक्रमs = 0;
	वापस_ACPI_STATUS(status);
पूर्ण
