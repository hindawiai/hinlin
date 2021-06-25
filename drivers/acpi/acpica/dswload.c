<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: dswload - Dispatcher first pass namespace load callbacks
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
#अगर_घोषित ACPI_ASL_COMPILER
#समावेश "acdisasm.h"
#पूर्ण_अगर

#घोषणा _COMPONENT          ACPI_DISPATCHER
ACPI_MODULE_NAME("dswload")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_init_callbacks
 *
 * PARAMETERS:  walk_state      - Current state of the parse tree walk
 *              pass_number     - 1, 2, or 3
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Init walk state callbacks
 *
 ******************************************************************************/
acpi_status
acpi_ds_init_callbacks(काष्ठा acpi_walk_state *walk_state, u32 pass_number)
अणु

	चयन (pass_number) अणु
	हाल 0:

		/* Parse only - caller will setup callbacks */

		walk_state->parse_flags = ACPI_PARSE_LOAD_PASS1 |
		    ACPI_PARSE_DELETE_TREE | ACPI_PARSE_DISASSEMBLE;
		walk_state->descending_callback = शून्य;
		walk_state->ascending_callback = शून्य;
		अवरोध;

	हाल 1:

		/* Load pass 1 */

		walk_state->parse_flags = ACPI_PARSE_LOAD_PASS1 |
		    ACPI_PARSE_DELETE_TREE;
		walk_state->descending_callback = acpi_ds_load1_begin_op;
		walk_state->ascending_callback = acpi_ds_load1_end_op;
		अवरोध;

	हाल 2:

		/* Load pass 2 */

		walk_state->parse_flags = ACPI_PARSE_LOAD_PASS1 |
		    ACPI_PARSE_DELETE_TREE;
		walk_state->descending_callback = acpi_ds_load2_begin_op;
		walk_state->ascending_callback = acpi_ds_load2_end_op;
		अवरोध;

	हाल 3:

		/* Execution pass */

		walk_state->parse_flags |= ACPI_PARSE_EXECUTE |
		    ACPI_PARSE_DELETE_TREE;
		walk_state->descending_callback = acpi_ds_exec_begin_op;
		walk_state->ascending_callback = acpi_ds_exec_end_op;
		अवरोध;

	शेष:

		वापस (AE_BAD_PARAMETER);
	पूर्ण

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_load1_begin_op
 *
 * PARAMETERS:  walk_state      - Current state of the parse tree walk
 *              out_op          - Where to वापस op अगर a new one is created
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Descending callback used during the loading of ACPI tables.
 *
 ******************************************************************************/

acpi_status
acpi_ds_load1_begin_op(काष्ठा acpi_walk_state *walk_state,
		       जोड़ acpi_parse_object **out_op)
अणु
	जोड़ acpi_parse_object *op;
	काष्ठा acpi_namespace_node *node;
	acpi_status status;
	acpi_object_type object_type;
	अक्षर *path;
	u32 flags;

	ACPI_FUNCTION_TRACE_PTR(ds_load1_begin_op, walk_state->op);

	op = walk_state->op;
	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH, "Op=%p State=%p\n", op,
			  walk_state));

	/* We are only पूर्णांकerested in opcodes that have an associated name */

	अगर (op) अणु
		अगर (!(walk_state->op_info->flags & AML_NAMED)) अणु
			*out_op = op;
			वापस_ACPI_STATUS(AE_OK);
		पूर्ण

		/* Check अगर this object has alपढ़ोy been installed in the namespace */

		अगर (op->common.node) अणु
			*out_op = op;
			वापस_ACPI_STATUS(AE_OK);
		पूर्ण
	पूर्ण

	path = acpi_ps_get_next_namestring(&walk_state->parser_state);

	/* Map the raw opcode पूर्णांकo an पूर्णांकernal object type */

	object_type = walk_state->op_info->object_type;

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "State=%p Op=%p [%s]\n", walk_state, op,
			  acpi_ut_get_type_name(object_type)));

	चयन (walk_state->opcode) अणु
	हाल AML_SCOPE_OP:
		/*
		 * The target name of the Scope() चालक must exist at this poपूर्णांक so
		 * that we can actually खोलो the scope to enter new names underneath it.
		 * Allow search-to-root क्रम single namesegs.
		 */
		status =
		    acpi_ns_lookup(walk_state->scope_info, path, object_type,
				   ACPI_IMODE_EXECUTE, ACPI_NS_SEARCH_PARENT,
				   walk_state, &(node));
#अगर_घोषित ACPI_ASL_COMPILER
		अगर (status == AE_NOT_FOUND) अणु
			/*
			 * Table disassembly:
			 * Target of Scope() not found. Generate an External क्रम it, and
			 * insert the name पूर्णांकo the namespace.
			 */
			acpi_dm_add_op_to_बाह्यal_list(op, path,
							ACPI_TYPE_DEVICE, 0, 0);
			status =
			    acpi_ns_lookup(walk_state->scope_info, path,
					   object_type, ACPI_IMODE_LOAD_PASS1,
					   ACPI_NS_SEARCH_PARENT, walk_state,
					   &node);
		पूर्ण
#पूर्ण_अगर
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_ERROR_NAMESPACE(walk_state->scope_info, path,
					     status);
			वापस_ACPI_STATUS(status);
		पूर्ण

		/*
		 * Check to make sure that the target is
		 * one of the opcodes that actually खोलोs a scope
		 */
		चयन (node->type) अणु
		हाल ACPI_TYPE_ANY:
		हाल ACPI_TYPE_LOCAL_SCOPE:	/* Scope  */
		हाल ACPI_TYPE_DEVICE:
		हाल ACPI_TYPE_POWER:
		हाल ACPI_TYPE_PROCESSOR:
		हाल ACPI_TYPE_THERMAL:

			/* These are acceptable types */
			अवरोध;

		हाल ACPI_TYPE_INTEGER:
		हाल ACPI_TYPE_STRING:
		हाल ACPI_TYPE_BUFFER:
			/*
			 * These types we will allow, but we will change the type.
			 * This enables some existing code of the क्रमm:
			 *
			 *  Name (DEB, 0)
			 *  Scope (DEB) अणु ... पूर्ण
			 *
			 * Note: silently change the type here. On the second pass,
			 * we will report a warning
			 */
			ACPI_DEBUG_PRINT((ACPI_DB_INFO,
					  "Type override - [%4.4s] had invalid type (%s) "
					  "for Scope operator, changed to type ANY\n",
					  acpi_ut_get_node_name(node),
					  acpi_ut_get_type_name(node->type)));

			node->type = ACPI_TYPE_ANY;
			walk_state->scope_info->common.value = ACPI_TYPE_ANY;
			अवरोध;

		हाल ACPI_TYPE_METHOD:
			/*
			 * Allow scope change to root during execution of module-level
			 * code. Root is typed METHOD during this समय.
			 */
			अगर ((node == acpi_gbl_root_node) &&
			    (walk_state->
			     parse_flags & ACPI_PARSE_MODULE_LEVEL)) अणु
				अवरोध;
			पूर्ण

			ACPI_FALLTHROUGH;

		शेष:

			/* All other types are an error */

			ACPI_ERROR((AE_INFO,
				    "Invalid type (%s) for target of "
				    "Scope operator [%4.4s] (Cannot override)",
				    acpi_ut_get_type_name(node->type),
				    acpi_ut_get_node_name(node)));

			वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		पूर्ण
		अवरोध;

	शेष:
		/*
		 * For all other named opcodes, we will enter the name पूर्णांकo
		 * the namespace.
		 *
		 * Setup the search flags.
		 * Since we are entering a name पूर्णांकo the namespace, we करो not want to
		 * enable the search-to-root upsearch.
		 *
		 * There are only two conditions where it is acceptable that the name
		 * alपढ़ोy exists:
		 *    1) the Scope() चालक can reखोलो a scoping object that was
		 *       previously defined (Scope, Method, Device, etc.)
		 *    2) Whenever we are parsing a deferred opcode (op_region, Buffer,
		 *       buffer_field, or Package), the name of the object is alपढ़ोy
		 *       in the namespace.
		 */
		अगर (walk_state->deferred_node) अणु

			/* This name is alपढ़ोy in the namespace, get the node */

			node = walk_state->deferred_node;
			status = AE_OK;
			अवरोध;
		पूर्ण

		/*
		 * If we are executing a method, करो not create any namespace objects
		 * during the load phase, only during execution.
		 */
		अगर (walk_state->method_node) अणु
			node = शून्य;
			status = AE_OK;
			अवरोध;
		पूर्ण

		flags = ACPI_NS_NO_UPSEARCH;
		अगर ((walk_state->opcode != AML_SCOPE_OP) &&
		    (!(walk_state->parse_flags & ACPI_PARSE_DEFERRED_OP))) अणु
			अगर (walk_state->namespace_override) अणु
				flags |= ACPI_NS_OVERRIDE_IF_FOUND;
				ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
						  "[%s] Override allowed\n",
						  acpi_ut_get_type_name
						  (object_type)));
			पूर्ण अन्यथा अणु
				flags |= ACPI_NS_ERROR_IF_FOUND;
				ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
						  "[%s] Cannot already exist\n",
						  acpi_ut_get_type_name
						  (object_type)));
			पूर्ण
		पूर्ण अन्यथा अणु
			ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
					  "[%s] Both Find or Create allowed\n",
					  acpi_ut_get_type_name(object_type)));
		पूर्ण

		/*
		 * Enter the named type पूर्णांकo the पूर्णांकernal namespace. We enter the name
		 * as we go करोwnward in the parse tree. Any necessary subobjects that
		 * involve arguments to the opcode must be created as we go back up the
		 * parse tree later.
		 */
		status =
		    acpi_ns_lookup(walk_state->scope_info, path, object_type,
				   ACPI_IMODE_LOAD_PASS1, flags, walk_state,
				   &node);
		अगर (ACPI_FAILURE(status)) अणु
			अगर (status == AE_ALREADY_EXISTS) अणु

				/* The name alपढ़ोy exists in this scope */

				अगर (node->flags & ANOBJ_IS_EXTERNAL) अणु
					/*
					 * Allow one create on an object or segment that was
					 * previously declared External
					 */
					node->flags &= ~ANOBJ_IS_EXTERNAL;
					node->type = (u8) object_type;

					/* Just retyped a node, probably will need to खोलो a scope */

					अगर (acpi_ns_खोलोs_scope(object_type)) अणु
						status =
						    acpi_ds_scope_stack_push
						    (node, object_type,
						     walk_state);
						अगर (ACPI_FAILURE(status)) अणु
							वापस_ACPI_STATUS
							    (status);
						पूर्ण
					पूर्ण

					status = AE_OK;
				पूर्ण
			पूर्ण

			अगर (ACPI_FAILURE(status)) अणु
				ACPI_ERROR_NAMESPACE(walk_state->scope_info,
						     path, status);
				वापस_ACPI_STATUS(status);
			पूर्ण
		पूर्ण
		अवरोध;
	पूर्ण

	/* Common निकास */

	अगर (!op) अणु

		/* Create a new op */

		op = acpi_ps_alloc_op(walk_state->opcode, walk_state->aml);
		अगर (!op) अणु
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण
	पूर्ण

	/* Initialize the op */

#अगर_घोषित ACPI_CONSTANT_EVAL_ONLY
	op->named.path = path;
#पूर्ण_अगर

	अगर (node) अणु
		/*
		 * Put the Node in the "op" object that the parser uses, so we
		 * can get it again quickly when this scope is बंदd
		 */
		op->common.node = node;
		op->named.name = node->name.पूर्णांकeger;
	पूर्ण

	acpi_ps_append_arg(acpi_ps_get_parent_scope(&walk_state->parser_state),
			   op);
	*out_op = op;
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_load1_end_op
 *
 * PARAMETERS:  walk_state      - Current state of the parse tree walk
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Ascending callback used during the loading of the namespace,
 *              both control methods and everything अन्यथा.
 *
 ******************************************************************************/

acpi_status acpi_ds_load1_end_op(काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_parse_object *op;
	acpi_object_type object_type;
	acpi_status status = AE_OK;
#अगर_घोषित ACPI_ASL_COMPILER
	u8 param_count;
#पूर्ण_अगर

	ACPI_FUNCTION_TRACE(ds_load1_end_op);

	op = walk_state->op;
	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH, "Op=%p State=%p\n", op,
			  walk_state));

	/*
	 * Disassembler: handle create field चालकs here.
	 *
	 * create_buffer_field is a deferred op that is typically processed in load
	 * pass 2. However, disassembly of control method contents walk the parse
	 * tree with ACPI_PARSE_LOAD_PASS1 and AML_CREATE चालकs are processed
	 * in a later walk. This is a problem when there is a control method that
	 * has the same name as the AML_CREATE object. In this हाल, any use of the
	 * name segment will be detected as a method call rather than a reference
	 * to a buffer field.
	 *
	 * This earlier creation during disassembly solves this issue by inserting
	 * the named object in the ACPI namespace so that references to this name
	 * would be a name string rather than a method call.
	 */
	अगर ((walk_state->parse_flags & ACPI_PARSE_DISASSEMBLE) &&
	    (walk_state->op_info->flags & AML_CREATE)) अणु
		status = acpi_ds_create_buffer_field(op, walk_state);
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* We are only पूर्णांकerested in opcodes that have an associated name */

	अगर (!(walk_state->op_info->flags & (AML_NAMED | AML_FIELD))) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Get the object type to determine अगर we should pop the scope */

	object_type = walk_state->op_info->object_type;

	अगर (walk_state->op_info->flags & AML_FIELD) अणु
		/*
		 * If we are executing a method, करो not create any namespace objects
		 * during the load phase, only during execution.
		 */
		अगर (!walk_state->method_node) अणु
			अगर (walk_state->opcode == AML_FIELD_OP ||
			    walk_state->opcode == AML_BANK_FIELD_OP ||
			    walk_state->opcode == AML_INDEX_FIELD_OP) अणु
				status =
				    acpi_ds_init_field_objects(op, walk_state);
			पूर्ण
		पूर्ण
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * If we are executing a method, करो not create any namespace objects
	 * during the load phase, only during execution.
	 */
	अगर (!walk_state->method_node) अणु
		अगर (op->common.aml_opcode == AML_REGION_OP) अणु
			status =
			    acpi_ex_create_region(op->named.data,
						  op->named.length,
						  (acpi_adr_space_type)
						  ((op->common.value.arg)->
						   common.value.पूर्णांकeger),
						  walk_state);
			अगर (ACPI_FAILURE(status)) अणु
				वापस_ACPI_STATUS(status);
			पूर्ण
		पूर्ण अन्यथा अगर (op->common.aml_opcode == AML_DATA_REGION_OP) अणु
			status =
			    acpi_ex_create_region(op->named.data,
						  op->named.length,
						  ACPI_ADR_SPACE_DATA_TABLE,
						  walk_state);
			अगर (ACPI_FAILURE(status)) अणु
				वापस_ACPI_STATUS(status);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (op->common.aml_opcode == AML_NAME_OP) अणु

		/* For Name opcode, get the object type from the argument */

		अगर (op->common.value.arg) अणु
			object_type = (acpi_ps_get_opcode_info((op->common.
								value.arg)->
							       common.
							       aml_opcode))->
			    object_type;

			/* Set node type अगर we have a namespace node */

			अगर (op->common.node) अणु
				op->common.node->type = (u8) object_type;
			पूर्ण
		पूर्ण
	पूर्ण
#अगर_घोषित ACPI_ASL_COMPILER
	/*
	 * For बाह्यal opcode, get the object type from the argument and
	 * get the parameter count from the argument's next.
	 */
	अगर (acpi_gbl_disयंत्र_flag &&
	    op->common.node && op->common.aml_opcode == AML_EXTERNAL_OP) अणु
		/*
		 * Note, अगर this बाह्यal is not a method
		 * Op->Common.Value.Arg->Common.Next->Common.Value.Integer == 0
		 * Thereक्रमe, param_count will be 0.
		 */
		param_count =
		    (u8)op->common.value.arg->common.next->common.value.पूर्णांकeger;
		object_type = (u8)op->common.value.arg->common.value.पूर्णांकeger;
		op->common.node->flags |= ANOBJ_IS_EXTERNAL;
		op->common.node->type = (u8)object_type;

		acpi_dm_create_subobject_क्रम_बाह्यal((u8)object_type,
						      &op->common.node,
						      param_count);

		/*
		 * Add the बाह्यal to the बाह्यal list because we may be
		 * emitting code based off of the items within the बाह्यal list.
		 */
		acpi_dm_add_op_to_बाह्यal_list(op, op->named.path,
						(u8)object_type, param_count,
						ACPI_EXT_ORIGIN_FROM_OPCODE |
						ACPI_EXT_RESOLVED_REFERENCE);
	पूर्ण
#पूर्ण_अगर

	/*
	 * If we are executing a method, करो not create any namespace objects
	 * during the load phase, only during execution.
	 */
	अगर (!walk_state->method_node) अणु
		अगर (op->common.aml_opcode == AML_METHOD_OP) अणु
			/*
			 * method_op pkg_length name_string method_flags term_list
			 *
			 * Note: We must create the method node/object pair as soon as we
			 * see the method declaration. This allows later pass1 parsing
			 * of invocations of the method (need to know the number of
			 * arguments.)
			 */
			ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
					  "LOADING-Method: State=%p Op=%p NamedObj=%p\n",
					  walk_state, op, op->named.node));

			अगर (!acpi_ns_get_attached_object(op->named.node)) अणु
				walk_state->opeअक्रमs[0] =
				    ACPI_CAST_PTR(व्योम, op->named.node);
				walk_state->num_opeअक्रमs = 1;

				status =
				    acpi_ds_create_opeअक्रमs(walk_state,
							    op->common.value.
							    arg);
				अगर (ACPI_SUCCESS(status)) अणु
					status =
					    acpi_ex_create_method(op->named.
								  data,
								  op->named.
								  length,
								  walk_state);
				पूर्ण

				walk_state->opeअक्रमs[0] = शून्य;
				walk_state->num_opeअक्रमs = 0;

				अगर (ACPI_FAILURE(status)) अणु
					वापस_ACPI_STATUS(status);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* Pop the scope stack (only अगर loading a table) */

	अगर (!walk_state->method_node &&
	    op->common.aml_opcode != AML_EXTERNAL_OP &&
	    acpi_ns_खोलोs_scope(object_type)) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
				  "(%s): Popping scope for Op %p\n",
				  acpi_ut_get_type_name(object_type), op));

		status = acpi_ds_scope_stack_pop(walk_state);
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण
