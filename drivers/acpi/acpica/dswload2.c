<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: dswload2 - Dispatcher second pass namespace load callbacks
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
#समावेश "acevents.h"
#अगर_घोषित ACPI_EXEC_APP
#समावेश "aecommon.h"
#पूर्ण_अगर

#घोषणा _COMPONENT          ACPI_DISPATCHER
ACPI_MODULE_NAME("dswload2")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_load2_begin_op
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
acpi_ds_load2_begin_op(काष्ठा acpi_walk_state *walk_state,
		       जोड़ acpi_parse_object **out_op)
अणु
	जोड़ acpi_parse_object *op;
	काष्ठा acpi_namespace_node *node;
	acpi_status status;
	acpi_object_type object_type;
	अक्षर *buffer_ptr;
	u32 flags;

	ACPI_FUNCTION_TRACE(ds_load2_begin_op);

	op = walk_state->op;
	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH, "Op=%p State=%p\n", op,
			  walk_state));

	अगर (op) अणु
		अगर ((walk_state->control_state) &&
		    (walk_state->control_state->common.state ==
		     ACPI_CONTROL_CONDITIONAL_EXECUTING)) अणु

			/* We are executing a जबतक loop outside of a method */

			status = acpi_ds_exec_begin_op(walk_state, out_op);
			वापस_ACPI_STATUS(status);
		पूर्ण

		/* We only care about Namespace opcodes here */

		अगर ((!(walk_state->op_info->flags & AML_NSOPCODE) &&
		     (walk_state->opcode != AML_INT_NAMEPATH_OP)) ||
		    (!(walk_state->op_info->flags & AML_NAMED))) अणु
			वापस_ACPI_STATUS(AE_OK);
		पूर्ण

		/* Get the name we are going to enter or lookup in the namespace */

		अगर (walk_state->opcode == AML_INT_NAMEPATH_OP) अणु

			/* For Namepath op, get the path string */

			buffer_ptr = op->common.value.string;
			अगर (!buffer_ptr) अणु

				/* No name, just निकास */

				वापस_ACPI_STATUS(AE_OK);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Get name from the op */

			buffer_ptr = ACPI_CAST_PTR(अक्षर, &op->named.name);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Get the namestring from the raw AML */

		buffer_ptr =
		    acpi_ps_get_next_namestring(&walk_state->parser_state);
	पूर्ण

	/* Map the opcode पूर्णांकo an पूर्णांकernal object type */

	object_type = walk_state->op_info->object_type;

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "State=%p Op=%p Type=%X\n", walk_state, op,
			  object_type));

	चयन (walk_state->opcode) अणु
	हाल AML_FIELD_OP:
	हाल AML_BANK_FIELD_OP:
	हाल AML_INDEX_FIELD_OP:

		node = शून्य;
		status = AE_OK;
		अवरोध;

	हाल AML_INT_NAMEPATH_OP:
		/*
		 * The name_path is an object reference to an existing object.
		 * Don't enter the name पूर्णांकo the namespace, but look it up
		 * क्रम use later.
		 */
		status =
		    acpi_ns_lookup(walk_state->scope_info, buffer_ptr,
				   object_type, ACPI_IMODE_EXECUTE,
				   ACPI_NS_SEARCH_PARENT, walk_state, &(node));
		अवरोध;

	हाल AML_SCOPE_OP:

		/* Special हाल क्रम Scope(\) -> refers to the Root node */

		अगर (op && (op->named.node == acpi_gbl_root_node)) अणु
			node = op->named.node;

			status =
			    acpi_ds_scope_stack_push(node, object_type,
						     walk_state);
			अगर (ACPI_FAILURE(status)) अणु
				वापस_ACPI_STATUS(status);
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * The Path is an object reference to an existing object.
			 * Don't enter the name पूर्णांकo the namespace, but look it up
			 * क्रम use later.
			 */
			status =
			    acpi_ns_lookup(walk_state->scope_info, buffer_ptr,
					   object_type, ACPI_IMODE_EXECUTE,
					   ACPI_NS_SEARCH_PARENT, walk_state,
					   &(node));
			अगर (ACPI_FAILURE(status)) अणु
#अगर_घोषित ACPI_ASL_COMPILER
				अगर (status == AE_NOT_FOUND) अणु
					status = AE_OK;
				पूर्ण अन्यथा अणु
					ACPI_ERROR_NAMESPACE(walk_state->
							     scope_info,
							     buffer_ptr,
							     status);
				पूर्ण
#अन्यथा
				ACPI_ERROR_NAMESPACE(walk_state->scope_info,
						     buffer_ptr, status);
#पूर्ण_अगर
				वापस_ACPI_STATUS(status);
			पूर्ण
		पूर्ण

		/*
		 * We must check to make sure that the target is
		 * one of the opcodes that actually खोलोs a scope
		 */
		चयन (node->type) अणु
		हाल ACPI_TYPE_ANY:
		हाल ACPI_TYPE_LOCAL_SCOPE:	/* Scope */
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
			 */
			ACPI_WARNING((AE_INFO,
				      "Type override - [%4.4s] had invalid type (%s) "
				      "for Scope operator, changed to type ANY",
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

		/* All other opcodes */

		अगर (op && op->common.node) अणु

			/* This op/node was previously entered पूर्णांकo the namespace */

			node = op->common.node;

			अगर (acpi_ns_खोलोs_scope(object_type)) अणु
				status =
				    acpi_ds_scope_stack_push(node, object_type,
							     walk_state);
				अगर (ACPI_FAILURE(status)) अणु
					वापस_ACPI_STATUS(status);
				पूर्ण
			पूर्ण

			वापस_ACPI_STATUS(AE_OK);
		पूर्ण

		/*
		 * Enter the named type पूर्णांकo the पूर्णांकernal namespace. We enter the name
		 * as we go करोwnward in the parse tree. Any necessary subobjects that
		 * involve arguments to the opcode must be created as we go back up the
		 * parse tree later.
		 *
		 * Note: Name may alपढ़ोy exist अगर we are executing a deferred opcode.
		 */
		अगर (walk_state->deferred_node) अणु

			/* This name is alपढ़ोy in the namespace, get the node */

			node = walk_state->deferred_node;
			status = AE_OK;
			अवरोध;
		पूर्ण

		flags = ACPI_NS_NO_UPSEARCH;
		अगर (walk_state->pass_number == ACPI_IMODE_EXECUTE) अणु

			/* Execution mode, node cannot alपढ़ोy exist, node is temporary */

			flags |= ACPI_NS_ERROR_IF_FOUND;

			अगर (!
			    (walk_state->
			     parse_flags & ACPI_PARSE_MODULE_LEVEL)) अणु
				flags |= ACPI_NS_TEMPORARY;
			पूर्ण
		पूर्ण
#अगर_घोषित ACPI_ASL_COMPILER

		/*
		 * Do not खोलो a scope क्रम AML_EXTERNAL_OP
		 * acpi_ns_lookup can खोलो a new scope based on the object type
		 * of this op. AML_EXTERNAL_OP is a declaration rather than a
		 * definition. In the हाल that this बाह्यal is a method object,
		 * acpi_ns_lookup will खोलो a new scope. However, an AML_EXTERNAL_OP
		 * associated with the ACPI_TYPE_METHOD is a declaration, rather than
		 * a definition. Flags is set to aव्योम खोलोing a scope क्रम any
		 * AML_EXTERNAL_OP.
		 */
		अगर (walk_state->opcode == AML_EXTERNAL_OP) अणु
			flags |= ACPI_NS_DONT_OPEN_SCOPE;
		पूर्ण
#पूर्ण_अगर

		/*
		 * For name creation opcodes, the full namepath prefix must
		 * exist, except क्रम the final (new) nameseg.
		 */
		अगर (walk_state->op_info->flags & AML_NAMED) अणु
			flags |= ACPI_NS_PREFIX_MUST_EXIST;
		पूर्ण

		/* Add new entry or lookup existing entry */

		status =
		    acpi_ns_lookup(walk_state->scope_info, buffer_ptr,
				   object_type, ACPI_IMODE_LOAD_PASS2, flags,
				   walk_state, &node);

		अगर (ACPI_SUCCESS(status) && (flags & ACPI_NS_TEMPORARY)) अणु
			ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
					  "***New Node [%4.4s] %p is temporary\n",
					  acpi_ut_get_node_name(node), node));
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (ACPI_FAILURE(status)) अणु
		ACPI_ERROR_NAMESPACE(walk_state->scope_info,
				     buffer_ptr, status);
		वापस_ACPI_STATUS(status);
	पूर्ण

	अगर (!op) अणु

		/* Create a new op */

		op = acpi_ps_alloc_op(walk_state->opcode, walk_state->aml);
		अगर (!op) अणु
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण

		/* Initialize the new op */

		अगर (node) अणु
			op->named.name = node->name.पूर्णांकeger;
		पूर्ण
		*out_op = op;
	पूर्ण

	/*
	 * Put the Node in the "op" object that the parser uses, so we
	 * can get it again quickly when this scope is बंदd
	 */
	op->common.node = node;
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_load2_end_op
 *
 * PARAMETERS:  walk_state      - Current state of the parse tree walk
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Ascending callback used during the loading of the namespace,
 *              both control methods and everything अन्यथा.
 *
 ******************************************************************************/

acpi_status acpi_ds_load2_end_op(काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_parse_object *op;
	acpi_status status = AE_OK;
	acpi_object_type object_type;
	काष्ठा acpi_namespace_node *node;
	जोड़ acpi_parse_object *arg;
	काष्ठा acpi_namespace_node *new_node;
	u32 i;
	u8 region_space;
#अगर_घोषित ACPI_EXEC_APP
	जोड़ acpi_opeअक्रम_object *obj_desc;
	अक्षर *namepath;
#पूर्ण_अगर

	ACPI_FUNCTION_TRACE(ds_load2_end_op);

	op = walk_state->op;
	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH, "Opcode [%s] Op %p State %p\n",
			  walk_state->op_info->name, op, walk_state));

	/* Check अगर opcode had an associated namespace object */

	अगर (!(walk_state->op_info->flags & AML_NSOBJECT)) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	अगर (op->common.aml_opcode == AML_SCOPE_OP) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
				  "Ending scope Op=%p State=%p\n", op,
				  walk_state));
	पूर्ण

	object_type = walk_state->op_info->object_type;

	/*
	 * Get the Node/name from the earlier lookup
	 * (It was saved in the *op काष्ठाure)
	 */
	node = op->common.node;

	/*
	 * Put the Node on the object stack (Contains the ACPI Name of
	 * this object)
	 */
	walk_state->opeअक्रमs[0] = (व्योम *)node;
	walk_state->num_opeअक्रमs = 1;

	/* Pop the scope stack */

	अगर (acpi_ns_खोलोs_scope(object_type) &&
	    (op->common.aml_opcode != AML_INT_METHODCALL_OP)) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
				  "(%s) Popping scope for Op %p\n",
				  acpi_ut_get_type_name(object_type), op));

		status = acpi_ds_scope_stack_pop(walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ cleanup;
		पूर्ण
	पूर्ण

	/*
	 * Named operations are as follows:
	 *
	 * AML_ALIAS
	 * AML_BANKFIELD
	 * AML_CREATEBITFIELD
	 * AML_CREATEBYTEFIELD
	 * AML_CREATEDWORDFIELD
	 * AML_CREATEFIELD
	 * AML_CREATEQWORDFIELD
	 * AML_CREATEWORDFIELD
	 * AML_DATA_REGION
	 * AML_DEVICE
	 * AML_EVENT
	 * AML_FIELD
	 * AML_INDEXFIELD
	 * AML_METHOD
	 * AML_METHODCALL
	 * AML_MUTEX
	 * AML_NAME
	 * AML_NAMEDFIELD
	 * AML_OPREGION
	 * AML_POWERRES
	 * AML_PROCESSOR
	 * AML_SCOPE
	 * AML_THERMALZONE
	 */

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "Create-Load [%s] State=%p Op=%p NamedObj=%p\n",
			  acpi_ps_get_opcode_name(op->common.aml_opcode),
			  walk_state, op, node));

	/* Decode the opcode */

	arg = op->common.value.arg;

	चयन (walk_state->op_info->type) अणु

	हाल AML_TYPE_CREATE_FIELD:
		/*
		 * Create the field object, but the field buffer and index must
		 * be evaluated later during the execution phase
		 */
		status = acpi_ds_create_buffer_field(op, walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_EXCEPTION((AE_INFO, status,
					"CreateBufferField failure"));
			जाओ cleanup;
			पूर्ण
		अवरोध;

	हाल AML_TYPE_NAMED_FIELD:
		/*
		 * If we are executing a method, initialize the field
		 */
		अगर (walk_state->method_node) अणु
			status = acpi_ds_init_field_objects(op, walk_state);
		पूर्ण

		चयन (op->common.aml_opcode) अणु
		हाल AML_INDEX_FIELD_OP:

			status =
			    acpi_ds_create_index_field(op,
						       (acpi_handle)arg->common.
						       node, walk_state);
			अवरोध;

		हाल AML_BANK_FIELD_OP:

			status =
			    acpi_ds_create_bank_field(op, arg->common.node,
						      walk_state);
			अवरोध;

		हाल AML_FIELD_OP:

			status =
			    acpi_ds_create_field(op, arg->common.node,
						 walk_state);
			अवरोध;

		शेष:

			/* All NAMED_FIELD opcodes must be handled above */
			अवरोध;
		पूर्ण
		अवरोध;

	हाल AML_TYPE_NAMED_SIMPLE:

		status = acpi_ds_create_opeअक्रमs(walk_state, arg);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ cleanup;
		पूर्ण

		चयन (op->common.aml_opcode) अणु
		हाल AML_PROCESSOR_OP:

			status = acpi_ex_create_processor(walk_state);
			अवरोध;

		हाल AML_POWER_RESOURCE_OP:

			status = acpi_ex_create_घातer_resource(walk_state);
			अवरोध;

		हाल AML_MUTEX_OP:

			status = acpi_ex_create_mutex(walk_state);
			अवरोध;

		हाल AML_EVENT_OP:

			status = acpi_ex_create_event(walk_state);
			अवरोध;

		हाल AML_ALIAS_OP:

			status = acpi_ex_create_alias(walk_state);
			अवरोध;

		शेष:

			/* Unknown opcode */

			status = AE_OK;
			जाओ cleanup;
		पूर्ण

		/* Delete opeअक्रमs */

		क्रम (i = 1; i < walk_state->num_opeअक्रमs; i++) अणु
			acpi_ut_हटाओ_reference(walk_state->opeअक्रमs[i]);
			walk_state->opeअक्रमs[i] = शून्य;
		पूर्ण

		अवरोध;

	हाल AML_TYPE_NAMED_COMPLEX:

		चयन (op->common.aml_opcode) अणु
		हाल AML_REGION_OP:
		हाल AML_DATA_REGION_OP:

			अगर (op->common.aml_opcode == AML_REGION_OP) अणु
				region_space = (acpi_adr_space_type)
				    ((op->common.value.arg)->common.value.
				     पूर्णांकeger);
			पूर्ण अन्यथा अणु
				region_space = ACPI_ADR_SPACE_DATA_TABLE;
			पूर्ण

			/*
			 * The op_region is not fully parsed at this समय. The only valid
			 * argument is the space_id. (We must save the address of the
			 * AML of the address and length opeअक्रमs)
			 *
			 * If we have a valid region, initialize it. The namespace is
			 * unlocked at this poपूर्णांक.
			 *
			 * Need to unlock पूर्णांकerpreter अगर it is locked (अगर we are running
			 * a control method), in order to allow _REG methods to be run
			 * during acpi_ev_initialize_region.
			 */
			अगर (walk_state->method_node) अणु
				/*
				 * Executing a method: initialize the region and unlock
				 * the पूर्णांकerpreter
				 */
				status = acpi_ex_create_region(op->named.data,
							       op->named.length,
							       region_space,
							       walk_state);
				अगर (ACPI_FAILURE(status)) अणु
					वापस_ACPI_STATUS(status);
				पूर्ण
			पूर्ण

			status =
			    acpi_ev_initialize_region
			    (acpi_ns_get_attached_object(node));
			अवरोध;

		हाल AML_NAME_OP:

			status = acpi_ds_create_node(walk_state, node, op);
			अगर (ACPI_FAILURE(status)) अणु
				जाओ cleanup;
			पूर्ण
#अगर_घोषित ACPI_EXEC_APP
			/*
			 * acpi_exec support क्रम namespace initialization file (initialize
			 * Name opcodes in this code.)
			 */
			namepath = acpi_ns_get_बाह्यal_pathname(node);
			status = ae_lookup_init_file_entry(namepath, &obj_desc);
			अगर (ACPI_SUCCESS(status)) अणु

				/* Detach any existing object, attach new object */

				अगर (node->object) अणु
					acpi_ns_detach_object(node);
				पूर्ण
				acpi_ns_attach_object(node, obj_desc,
						      obj_desc->common.type);
			पूर्ण
			ACPI_FREE(namepath);
			status = AE_OK;
#पूर्ण_अगर
			अवरोध;

		हाल AML_METHOD_OP:
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
			अवरोध;

		शेष:

			/* All NAMED_COMPLEX opcodes must be handled above */
			अवरोध;
		पूर्ण
		अवरोध;

	हाल AML_CLASS_INTERNAL:

		/* हाल AML_INT_NAMEPATH_OP: */
		अवरोध;

	हाल AML_CLASS_METHOD_CALL:

		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
				  "RESOLVING-MethodCall: State=%p Op=%p NamedObj=%p\n",
				  walk_state, op, node));

		/*
		 * Lookup the method name and save the Node
		 */
		status =
		    acpi_ns_lookup(walk_state->scope_info,
				   arg->common.value.string, ACPI_TYPE_ANY,
				   ACPI_IMODE_LOAD_PASS2,
				   ACPI_NS_SEARCH_PARENT |
				   ACPI_NS_DONT_OPEN_SCOPE, walk_state,
				   &(new_node));
		अगर (ACPI_SUCCESS(status)) अणु
			/*
			 * Make sure that what we found is indeed a method
			 * We didn't search क्रम a method on purpose, to see अगर the name
			 * would resolve
			 */
			अगर (new_node->type != ACPI_TYPE_METHOD) अणु
				status = AE_AML_OPERAND_TYPE;
			पूर्ण

			/* We could put the वापसed object (Node) on the object stack क्रम
			 * later, but क्रम now, we will put it in the "op" object that the
			 * parser uses, so we can get it again at the end of this scope
			 */
			op->common.node = new_node;
		पूर्ण अन्यथा अणु
			ACPI_ERROR_NAMESPACE(walk_state->scope_info,
					     arg->common.value.string, status);
		पूर्ण
		अवरोध;

	शेष:

		अवरोध;
	पूर्ण

cleanup:

	/* Remove the Node pushed at the very beginning */

	walk_state->opeअक्रमs[0] = शून्य;
	walk_state->num_opeअक्रमs = 0;
	वापस_ACPI_STATUS(status);
पूर्ण
