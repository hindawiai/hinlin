<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: dsutils - Dispatcher utilities
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acparser.h"
#समावेश "amlcode.h"
#समावेश "acdispat.h"
#समावेश "acinterp.h"
#समावेश "acnamesp.h"
#समावेश "acdebug.h"

#घोषणा _COMPONENT          ACPI_DISPATCHER
ACPI_MODULE_NAME("dsutils")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_clear_implicit_वापस
 *
 * PARAMETERS:  walk_state          - Current State
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Clear and हटाओ a reference on an implicit वापस value. Used
 *              to delete "stale" वापस values (अगर enabled, the वापस value
 *              from every चालक is saved at least momentarily, in हाल the
 *              parent method निकासs.)
 *
 ******************************************************************************/
व्योम acpi_ds_clear_implicit_वापस(काष्ठा acpi_walk_state *walk_state)
अणु
	ACPI_FUNCTION_NAME(ds_clear_implicit_वापस);

	/*
	 * Slack must be enabled क्रम this feature
	 */
	अगर (!acpi_gbl_enable_पूर्णांकerpreter_slack) अणु
		वापस;
	पूर्ण

	अगर (walk_state->implicit_वापस_obj) अणु
		/*
		 * Delete any "stale" implicit वापस. However, in
		 * complex statements, the implicit वापस value can be
		 * bubbled up several levels.
		 */
		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
				  "Removing reference on stale implicit return obj %p\n",
				  walk_state->implicit_वापस_obj));

		acpi_ut_हटाओ_reference(walk_state->implicit_वापस_obj);
		walk_state->implicit_वापस_obj = शून्य;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_करो_implicit_वापस
 *
 * PARAMETERS:  वापस_desc         - The वापस value
 *              walk_state          - Current State
 *              add_reference       - True अगर a reference should be added to the
 *                                    वापस object
 *
 * RETURN:      TRUE अगर implicit वापस enabled, FALSE otherwise
 *
 * DESCRIPTION: Implements the optional "implicit return".  We save the result
 *              of every ASL चालक and control method invocation in हाल the
 *              parent method निकास. Beक्रमe storing a new वापस value, we
 *              delete the previous वापस value.
 *
 ******************************************************************************/

u8
acpi_ds_करो_implicit_वापस(जोड़ acpi_opeअक्रम_object *वापस_desc,
			   काष्ठा acpi_walk_state *walk_state, u8 add_reference)
अणु
	ACPI_FUNCTION_NAME(ds_करो_implicit_वापस);

	/*
	 * Slack must be enabled क्रम this feature, and we must
	 * have a valid वापस object
	 */
	अगर ((!acpi_gbl_enable_पूर्णांकerpreter_slack) || (!वापस_desc)) अणु
		वापस (FALSE);
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "Result %p will be implicitly returned; Prev=%p\n",
			  वापस_desc, walk_state->implicit_वापस_obj));

	/*
	 * Delete any "stale" implicit वापस value first. However, in
	 * complex statements, the implicit वापस value can be
	 * bubbled up several levels, so we करोn't clear the value अगर it
	 * is the same as the वापस_desc.
	 */
	अगर (walk_state->implicit_वापस_obj) अणु
		अगर (walk_state->implicit_वापस_obj == वापस_desc) अणु
			वापस (TRUE);
		पूर्ण
		acpi_ds_clear_implicit_वापस(walk_state);
	पूर्ण

	/* Save the implicit वापस value, add a reference अगर requested */

	walk_state->implicit_वापस_obj = वापस_desc;
	अगर (add_reference) अणु
		acpi_ut_add_reference(वापस_desc);
	पूर्ण

	वापस (TRUE);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_is_result_used
 *
 * PARAMETERS:  op                  - Current Op
 *              walk_state          - Current State
 *
 * RETURN:      TRUE अगर result is used, FALSE otherwise
 *
 * DESCRIPTION: Check अगर a result object will be used by the parent
 *
 ******************************************************************************/

u8
acpi_ds_is_result_used(जोड़ acpi_parse_object * op,
		       काष्ठा acpi_walk_state * walk_state)
अणु
	स्थिर काष्ठा acpi_opcode_info *parent_info;

	ACPI_FUNCTION_TRACE_PTR(ds_is_result_used, op);

	/* Must have both an Op and a Result Object */

	अगर (!op) अणु
		ACPI_ERROR((AE_INFO, "Null Op"));
		वापस_UINT8(TRUE);
	पूर्ण

	/*
	 * We know that this चालक is not a
	 * Return() चालक (would not come here.) The following code is the
	 * optional support क्रम a so-called "implicit return". Some AML code
	 * assumes that the last value of the method is "implicitly" वापसed
	 * to the caller. Just save the last result as the वापस value.
	 * NOTE: this is optional because the ASL language करोes not actually
	 * support this behavior.
	 */
	(व्योम)acpi_ds_करो_implicit_वापस(walk_state->result_obj, walk_state,
					 TRUE);

	/*
	 * Now determine अगर the parent will use the result
	 *
	 * If there is no parent, or the parent is a scope_op, we are executing
	 * at the method level. An executing method typically has no parent,
	 * since each method is parsed separately. A method invoked बाह्यally
	 * via execute_control_method has a scope_op as the parent.
	 */
	अगर ((!op->common.parent) ||
	    (op->common.parent->common.aml_opcode == AML_SCOPE_OP)) अणु

		/* No parent, the वापस value cannot possibly be used */

		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
				  "At Method level, result of [%s] not used\n",
				  acpi_ps_get_opcode_name(op->common.
							  aml_opcode)));
		वापस_UINT8(FALSE);
	पूर्ण

	/* Get info on the parent. The root_op is AML_SCOPE */

	parent_info =
	    acpi_ps_get_opcode_info(op->common.parent->common.aml_opcode);
	अगर (parent_info->class == AML_CLASS_UNKNOWN) अणु
		ACPI_ERROR((AE_INFO, "Unknown parent opcode Op=%p", op));
		वापस_UINT8(FALSE);
	पूर्ण

	/*
	 * Decide what to करो with the result based on the parent. If
	 * the parent opcode will not use the result, delete the object.
	 * Otherwise leave it as is, it will be deleted when it is used
	 * as an opeअक्रम later.
	 */
	चयन (parent_info->class) अणु
	हाल AML_CLASS_CONTROL:

		चयन (op->common.parent->common.aml_opcode) अणु
		हाल AML_RETURN_OP:

			/* Never delete the वापस value associated with a वापस opcode */

			जाओ result_used;

		हाल AML_IF_OP:
		हाल AML_WHILE_OP:
			/*
			 * If we are executing the predicate AND this is the predicate op,
			 * we will use the वापस value
			 */
			अगर ((walk_state->control_state->common.state ==
			     ACPI_CONTROL_PREDICATE_EXECUTING) &&
			    (walk_state->control_state->control.predicate_op ==
			     op)) अणु
				जाओ result_used;
			पूर्ण
			अवरोध;

		शेष:

			/* Ignore other control opcodes */

			अवरोध;
		पूर्ण

		/* The general control opcode वापसs no result */

		जाओ result_not_used;

	हाल AML_CLASS_CREATE:
		/*
		 * These opcodes allow term_arg(s) as opeअक्रमs and thereक्रमe
		 * the opeअक्रमs can be method calls. The result is used.
		 */
		जाओ result_used;

	हाल AML_CLASS_NAMED_OBJECT:

		अगर ((op->common.parent->common.aml_opcode == AML_REGION_OP) ||
		    (op->common.parent->common.aml_opcode == AML_DATA_REGION_OP)
		    || (op->common.parent->common.aml_opcode == AML_PACKAGE_OP)
		    || (op->common.parent->common.aml_opcode == AML_BUFFER_OP)
		    || (op->common.parent->common.aml_opcode ==
			AML_VARIABLE_PACKAGE_OP)
		    || (op->common.parent->common.aml_opcode ==
			AML_INT_EVAL_SUBTREE_OP)
		    || (op->common.parent->common.aml_opcode ==
			AML_BANK_FIELD_OP)) अणु
			/*
			 * These opcodes allow term_arg(s) as opeअक्रमs and thereक्रमe
			 * the opeअक्रमs can be method calls. The result is used.
			 */
			जाओ result_used;
		पूर्ण

		जाओ result_not_used;

	शेष:
		/*
		 * In all other हालs. the parent will actually use the वापस
		 * object, so keep it.
		 */
		जाओ result_used;
	पूर्ण

result_used:
	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "Result of [%s] used by Parent [%s] Op=%p\n",
			  acpi_ps_get_opcode_name(op->common.aml_opcode),
			  acpi_ps_get_opcode_name(op->common.parent->common.
						  aml_opcode), op));

	वापस_UINT8(TRUE);

result_not_used:
	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "Result of [%s] not used by Parent [%s] Op=%p\n",
			  acpi_ps_get_opcode_name(op->common.aml_opcode),
			  acpi_ps_get_opcode_name(op->common.parent->common.
						  aml_opcode), op));

	वापस_UINT8(FALSE);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_delete_result_अगर_not_used
 *
 * PARAMETERS:  op              - Current parse Op
 *              result_obj      - Result of the operation
 *              walk_state      - Current state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Used after पूर्णांकerpretation of an opcode. If there is an पूर्णांकernal
 *              result descriptor, check अगर the parent opcode will actually use
 *              this result. If not, delete the result now so that it will
 *              not become orphaned.
 *
 ******************************************************************************/

व्योम
acpi_ds_delete_result_अगर_not_used(जोड़ acpi_parse_object *op,
				  जोड़ acpi_opeअक्रम_object *result_obj,
				  काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	acpi_status status;

	ACPI_FUNCTION_TRACE_PTR(ds_delete_result_अगर_not_used, result_obj);

	अगर (!op) अणु
		ACPI_ERROR((AE_INFO, "Null Op"));
		वापस_VOID;
	पूर्ण

	अगर (!result_obj) अणु
		वापस_VOID;
	पूर्ण

	अगर (!acpi_ds_is_result_used(op, walk_state)) अणु

		/* Must pop the result stack (obj_desc should be equal to result_obj) */

		status = acpi_ds_result_pop(&obj_desc, walk_state);
		अगर (ACPI_SUCCESS(status)) अणु
			acpi_ut_हटाओ_reference(result_obj);
		पूर्ण
	पूर्ण

	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_resolve_opeअक्रमs
 *
 * PARAMETERS:  walk_state          - Current walk state with opeअक्रमs on stack
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Resolve all opeअक्रमs to their values. Used to prepare
 *              arguments to a control method invocation (a call from one
 *              method to another.)
 *
 ******************************************************************************/

acpi_status acpi_ds_resolve_opeअक्रमs(काष्ठा acpi_walk_state *walk_state)
अणु
	u32 i;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE_PTR(ds_resolve_opeअक्रमs, walk_state);

	/*
	 * Attempt to resolve each of the valid opeअक्रमs
	 * Method arguments are passed by reference, not by value. This means
	 * that the actual objects are passed, not copies of the objects.
	 */
	क्रम (i = 0; i < walk_state->num_opeअक्रमs; i++) अणु
		status =
		    acpi_ex_resolve_to_value(&walk_state->opeअक्रमs[i],
					     walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_clear_opeअक्रमs
 *
 * PARAMETERS:  walk_state          - Current walk state with opeअक्रमs on stack
 *
 * RETURN:      None
 *
 * DESCRIPTION: Clear all opeअक्रमs on the current walk state opeअक्रम stack.
 *
 ******************************************************************************/

व्योम acpi_ds_clear_opeअक्रमs(काष्ठा acpi_walk_state *walk_state)
अणु
	u32 i;

	ACPI_FUNCTION_TRACE_PTR(ds_clear_opeअक्रमs, walk_state);

	/* Remove a reference on each opeअक्रम on the stack */

	क्रम (i = 0; i < walk_state->num_opeअक्रमs; i++) अणु
		/*
		 * Remove a reference to all opeअक्रमs, including both
		 * "Arguments" and "Targets".
		 */
		acpi_ut_हटाओ_reference(walk_state->opeअक्रमs[i]);
		walk_state->opeअक्रमs[i] = शून्य;
	पूर्ण

	walk_state->num_opeअक्रमs = 0;
	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_create_opeअक्रम
 *
 * PARAMETERS:  walk_state      - Current walk state
 *              arg             - Parse object क्रम the argument
 *              arg_index       - Which argument (zero based)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Translate a parse tree object that is an argument to an AML
 *              opcode to the equivalent पूर्णांकerpreter object. This may include
 *              looking up a name or entering a new name पूर्णांकo the पूर्णांकernal
 *              namespace.
 *
 ******************************************************************************/

acpi_status
acpi_ds_create_opeअक्रम(काष्ठा acpi_walk_state *walk_state,
		       जोड़ acpi_parse_object *arg, u32 arg_index)
अणु
	acpi_status status = AE_OK;
	अक्षर *name_string;
	u32 name_length;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_parse_object *parent_op;
	u16 opcode;
	acpi_पूर्णांकerpreter_mode पूर्णांकerpreter_mode;
	स्थिर काष्ठा acpi_opcode_info *op_info;

	ACPI_FUNCTION_TRACE_PTR(ds_create_opeअक्रम, arg);

	/* A valid name must be looked up in the namespace */

	अगर ((arg->common.aml_opcode == AML_INT_NAMEPATH_OP) &&
	    (arg->common.value.string) &&
	    !(arg->common.flags & ACPI_PARSEOP_IN_STACK)) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH, "Getting a name: Arg=%p\n",
				  arg));

		/* Get the entire name string from the AML stream */

		status = acpi_ex_get_name_string(ACPI_TYPE_ANY,
						 arg->common.value.buffer,
						 &name_string, &name_length);

		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		/* All prefixes have been handled, and the name is in name_string */

		/*
		 * Special handling क्रम buffer_field declarations. This is a deferred
		 * opcode that unक्रमtunately defines the field name as the last
		 * parameter instead of the first. We get here when we are perक्रमming
		 * the deferred execution, so the actual name of the field is alपढ़ोy
		 * in the namespace. We करोn't want to attempt to look it up again
		 * because we may be executing in a dअगरferent scope than where the
		 * actual opcode exists.
		 */
		अगर ((walk_state->deferred_node) &&
		    (walk_state->deferred_node->type == ACPI_TYPE_BUFFER_FIELD)
		    && (arg_index == (u32)
			((walk_state->opcode == AML_CREATE_FIELD_OP) ? 3 : 2))) अणु
			obj_desc =
			    ACPI_CAST_PTR(जोड़ acpi_opeअक्रम_object,
					  walk_state->deferred_node);
			status = AE_OK;
		पूर्ण अन्यथा अणु	/* All other opcodes */

			/*
			 * Dअगरferentiate between a namespace "create" operation
			 * versus a "lookup" operation (IMODE_LOAD_PASS2 vs.
			 * IMODE_EXECUTE) in order to support the creation of
			 * namespace objects during the execution of control methods.
			 */
			parent_op = arg->common.parent;
			op_info =
			    acpi_ps_get_opcode_info(parent_op->common.
						    aml_opcode);

			अगर ((op_info->flags & AML_NSNODE) &&
			    (parent_op->common.aml_opcode !=
			     AML_INT_METHODCALL_OP)
			    && (parent_op->common.aml_opcode != AML_REGION_OP)
			    && (parent_op->common.aml_opcode !=
				AML_INT_NAMEPATH_OP)) अणु

				/* Enter name पूर्णांकo namespace अगर not found */

				पूर्णांकerpreter_mode = ACPI_IMODE_LOAD_PASS2;
			पूर्ण अन्यथा अणु
				/* Return a failure अगर name not found */

				पूर्णांकerpreter_mode = ACPI_IMODE_EXECUTE;
			पूर्ण

			status =
			    acpi_ns_lookup(walk_state->scope_info, name_string,
					   ACPI_TYPE_ANY, पूर्णांकerpreter_mode,
					   ACPI_NS_SEARCH_PARENT |
					   ACPI_NS_DONT_OPEN_SCOPE, walk_state,
					   ACPI_CAST_INसूचीECT_PTR(काष्ठा
								  acpi_namespace_node,
								  &obj_desc));
			/*
			 * The only हाल where we pass through (ignore) a NOT_FOUND
			 * error is क्रम the cond_ref_of opcode.
			 */
			अगर (status == AE_NOT_FOUND) अणु
				अगर (parent_op->common.aml_opcode ==
				    AML_CONDITIONAL_REF_OF_OP) अणु
					/*
					 * For the Conditional Reference op, it's OK अगर
					 * the name is not found;  We just need a way to
					 * indicate this to the पूर्णांकerpreter, set the
					 * object to the root
					 */
					obj_desc =
					    ACPI_CAST_PTR(जोड़
								 acpi_opeअक्रम_object,
								 acpi_gbl_root_node);
					status = AE_OK;
				पूर्ण अन्यथा अगर (parent_op->common.aml_opcode ==
					   AML_EXTERNAL_OP) अणु
					/*
					 * This opcode should never appear here. It is used only
					 * by AML disassemblers and is surrounded by an If(0)
					 * by the ASL compiler.
					 *
					 * Thereक्रमe, अगर we see it here, it is a serious error.
					 */
					status = AE_AML_BAD_OPCODE;
				पूर्ण अन्यथा अणु
					/*
					 * We just plain didn't find it -- which is a
					 * very serious error at this poपूर्णांक
					 */
					status = AE_AML_NAME_NOT_FOUND;
				पूर्ण
			पूर्ण

			अगर (ACPI_FAILURE(status)) अणु
				ACPI_ERROR_NAMESPACE(walk_state->scope_info,
						     name_string, status);
			पूर्ण
		पूर्ण

		/* Free the namestring created above */

		ACPI_FREE(name_string);

		/* Check status from the lookup */

		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		/* Put the resulting object onto the current object stack */

		status = acpi_ds_obj_stack_push(obj_desc, walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		acpi_db_display_argument_object(obj_desc, walk_state);
	पूर्ण अन्यथा अणु
		/* Check क्रम null name हाल */

		अगर ((arg->common.aml_opcode == AML_INT_NAMEPATH_OP) &&
		    !(arg->common.flags & ACPI_PARSEOP_IN_STACK)) अणु
			/*
			 * If the name is null, this means that this is an
			 * optional result parameter that was not specअगरied
			 * in the original ASL. Create a Zero Constant क्रम a
			 * placeholder. (Store to a स्थिरant is a Noop.)
			 */
			opcode = AML_ZERO_OP;	/* Has no arguments! */

			ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
					  "Null namepath: Arg=%p\n", arg));
		पूर्ण अन्यथा अणु
			opcode = arg->common.aml_opcode;
		पूर्ण

		/* Get the object type of the argument */

		op_info = acpi_ps_get_opcode_info(opcode);
		अगर (op_info->object_type == ACPI_TYPE_INVALID) अणु
			वापस_ACPI_STATUS(AE_NOT_IMPLEMENTED);
		पूर्ण

		अगर ((op_info->flags & AML_HAS_RETVAL) ||
		    (arg->common.flags & ACPI_PARSEOP_IN_STACK)) अणु
			/*
			 * Use value that was alपढ़ोy previously वापसed
			 * by the evaluation of this argument
			 */
			status = acpi_ds_result_pop(&obj_desc, walk_state);
			अगर (ACPI_FAILURE(status)) अणु
				/*
				 * Only error is underflow, and this indicates
				 * a missing or null opeअक्रम!
				 */
				ACPI_EXCEPTION((AE_INFO, status,
						"Missing or null operand"));
				वापस_ACPI_STATUS(status);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Create an ACPI_INTERNAL_OBJECT क्रम the argument */

			obj_desc =
			    acpi_ut_create_पूर्णांकernal_object(op_info->
							   object_type);
			अगर (!obj_desc) अणु
				वापस_ACPI_STATUS(AE_NO_MEMORY);
			पूर्ण

			/* Initialize the new object */

			status =
			    acpi_ds_init_object_from_op(walk_state, arg, opcode,
							&obj_desc);
			अगर (ACPI_FAILURE(status)) अणु
				acpi_ut_delete_object_desc(obj_desc);
				वापस_ACPI_STATUS(status);
			पूर्ण
		पूर्ण

		/* Put the opeअक्रम object on the object stack */

		status = acpi_ds_obj_stack_push(obj_desc, walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		acpi_db_display_argument_object(obj_desc, walk_state);
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_create_opeअक्रमs
 *
 * PARAMETERS:  walk_state          - Current state
 *              first_arg           - First argument of a parser argument tree
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert an चालक's arguments from a parse tree क्रमmat to
 *              namespace objects and place those argument object on the object
 *              stack in preparation क्रम evaluation by the पूर्णांकerpreter.
 *
 ******************************************************************************/

acpi_status
acpi_ds_create_opeअक्रमs(काष्ठा acpi_walk_state *walk_state,
			जोड़ acpi_parse_object *first_arg)
अणु
	acpi_status status = AE_OK;
	जोड़ acpi_parse_object *arg;
	जोड़ acpi_parse_object *arguments[ACPI_OBJ_NUM_OPERANDS];
	u32 arg_count = 0;
	u32 index = walk_state->num_opeअक्रमs;
	u32 i;

	ACPI_FUNCTION_TRACE_PTR(ds_create_opeअक्रमs, first_arg);

	/* Get all arguments in the list */

	arg = first_arg;
	जबतक (arg) अणु
		अगर (index >= ACPI_OBJ_NUM_OPERANDS) अणु
			वापस_ACPI_STATUS(AE_BAD_DATA);
		पूर्ण

		arguments[index] = arg;
		walk_state->opeअक्रमs[index] = शून्य;

		/* Move on to next argument, अगर any */

		arg = arg->common.next;
		arg_count++;
		index++;
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "NumOperands %d, ArgCount %d, Index %d\n",
			  walk_state->num_opeअक्रमs, arg_count, index));

	/* Create the पूर्णांकerpreter arguments, in reverse order */

	index--;
	क्रम (i = 0; i < arg_count; i++) अणु
		arg = arguments[index];
		walk_state->opeअक्रम_index = (u8)index;

		status = acpi_ds_create_opeअक्रम(walk_state, arg, index);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ cleanup;
		पूर्ण

		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
				  "Created Arg #%u (%p) %u args total\n",
				  index, arg, arg_count));
		index--;
	पूर्ण

	वापस_ACPI_STATUS(status);

cleanup:
	/*
	 * We must unकरो everything करोne above; meaning that we must
	 * pop everything off of the opeअक्रम stack and delete those
	 * objects
	 */
	acpi_ds_obj_stack_pop_and_delete(arg_count, walk_state);

	ACPI_EXCEPTION((AE_INFO, status, "While creating Arg %u", index));
	वापस_ACPI_STATUS(status);
पूर्ण

/*****************************************************************************
 *
 * FUNCTION:    acpi_ds_evaluate_name_path
 *
 * PARAMETERS:  walk_state      - Current state of the parse tree walk,
 *                                the opcode of current operation should be
 *                                AML_INT_NAMEPATH_OP
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Translate the -name_path- parse tree object to the equivalent
 *              पूर्णांकerpreter object, convert it to value, अगर needed, duplicate
 *              it, अगर needed, and push it onto the current result stack.
 *
 ****************************************************************************/

acpi_status acpi_ds_evaluate_name_path(काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status = AE_OK;
	जोड़ acpi_parse_object *op = walk_state->op;
	जोड़ acpi_opeअक्रम_object **opeअक्रम = &walk_state->opeअक्रमs[0];
	जोड़ acpi_opeअक्रम_object *new_obj_desc;
	u8 type;

	ACPI_FUNCTION_TRACE_PTR(ds_evaluate_name_path, walk_state);

	अगर (!op->common.parent) अणु

		/* This happens after certain exception processing */

		जाओ निकास;
	पूर्ण

	अगर ((op->common.parent->common.aml_opcode == AML_PACKAGE_OP) ||
	    (op->common.parent->common.aml_opcode == AML_VARIABLE_PACKAGE_OP) ||
	    (op->common.parent->common.aml_opcode == AML_REF_OF_OP)) अणु

		/* TBD: Should we specअगरy this feature as a bit of op_info->Flags of these opcodes? */

		जाओ निकास;
	पूर्ण

	status = acpi_ds_create_opeअक्रम(walk_state, op, 0);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ निकास;
	पूर्ण

	अगर (op->common.flags & ACPI_PARSEOP_TARGET) अणु
		new_obj_desc = *opeअक्रम;
		जाओ push_result;
	पूर्ण

	type = (*opeअक्रम)->common.type;

	status = acpi_ex_resolve_to_value(opeअक्रम, walk_state);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ निकास;
	पूर्ण

	अगर (type == ACPI_TYPE_INTEGER) अणु

		/* It was incremented by acpi_ex_resolve_to_value */

		acpi_ut_हटाओ_reference(*opeअक्रम);

		status =
		    acpi_ut_copy_iobject_to_iobject(*opeअक्रम, &new_obj_desc,
						    walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ निकास;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * The object either was anew created or is
		 * a Namespace node - करोn't decrement it.
		 */
		new_obj_desc = *opeअक्रम;
	पूर्ण

	/* Cleanup क्रम name-path opeअक्रम */

	status = acpi_ds_obj_stack_pop(1, walk_state);
	अगर (ACPI_FAILURE(status)) अणु
		walk_state->result_obj = new_obj_desc;
		जाओ निकास;
	पूर्ण

push_result:

	walk_state->result_obj = new_obj_desc;

	status = acpi_ds_result_push(walk_state->result_obj, walk_state);
	अगर (ACPI_SUCCESS(status)) अणु

		/* Force to take it from stack */

		op->common.flags |= ACPI_PARSEOP_IN_STACK;
	पूर्ण

निकास:

	वापस_ACPI_STATUS(status);
पूर्ण
