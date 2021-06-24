<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: dsobject - Dispatcher object management routines
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acparser.h"
#समावेश "amlcode.h"
#समावेश "acdispat.h"
#समावेश "acnamesp.h"
#समावेश "acinterp.h"

#घोषणा _COMPONENT          ACPI_DISPATCHER
ACPI_MODULE_NAME("dsobject")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_build_पूर्णांकernal_object
 *
 * PARAMETERS:  walk_state      - Current walk state
 *              op              - Parser object to be translated
 *              obj_desc_ptr    - Where the ACPI पूर्णांकernal object is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Translate a parser Op object to the equivalent namespace object
 *              Simple objects are any objects other than a package object!
 *
 ******************************************************************************/
acpi_status
acpi_ds_build_पूर्णांकernal_object(काष्ठा acpi_walk_state *walk_state,
			      जोड़ acpi_parse_object *op,
			      जोड़ acpi_opeअक्रम_object **obj_desc_ptr)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ds_build_पूर्णांकernal_object);

	*obj_desc_ptr = शून्य;
	अगर (op->common.aml_opcode == AML_INT_NAMEPATH_OP) अणु
		/*
		 * This is a named object reference. If this name was
		 * previously looked up in the namespace, it was stored in
		 * this op. Otherwise, go ahead and look it up now
		 */
		अगर (!op->common.node) अणु

			/* Check अगर we are resolving a named reference within a package */

			अगर ((op->common.parent->common.aml_opcode ==
			     AML_PACKAGE_OP)
			    || (op->common.parent->common.aml_opcode ==
				AML_VARIABLE_PACKAGE_OP)) अणु
				/*
				 * We won't resolve package elements here, we will करो this
				 * after all ACPI tables are loaded पूर्णांकo the namespace. This
				 * behavior supports both क्रमward references to named objects
				 * and बाह्यal references to objects in other tables.
				 */
				जाओ create_new_object;
			पूर्ण अन्यथा अणु
				status = acpi_ns_lookup(walk_state->scope_info,
							op->common.value.string,
							ACPI_TYPE_ANY,
							ACPI_IMODE_EXECUTE,
							ACPI_NS_SEARCH_PARENT |
							ACPI_NS_DONT_OPEN_SCOPE,
							शून्य,
							ACPI_CAST_INसूचीECT_PTR
							(काष्ठा
							 acpi_namespace_node,
							 &(op->common.node)));
				अगर (ACPI_FAILURE(status)) अणु
					ACPI_ERROR_NAMESPACE(walk_state->
							     scope_info,
							     op->common.value.
							     string, status);
					वापस_ACPI_STATUS(status);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

create_new_object:

	/* Create and init a new पूर्णांकernal ACPI object */

	obj_desc = acpi_ut_create_पूर्णांकernal_object((acpi_ps_get_opcode_info
						   (op->common.aml_opcode))->
						  object_type);
	अगर (!obj_desc) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	status =
	    acpi_ds_init_object_from_op(walk_state, op, op->common.aml_opcode,
					&obj_desc);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_ut_हटाओ_reference(obj_desc);
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Handling क्रम unresolved package reference elements.
	 * These are elements that are namepaths.
	 */
	अगर ((op->common.parent->common.aml_opcode == AML_PACKAGE_OP) ||
	    (op->common.parent->common.aml_opcode == AML_VARIABLE_PACKAGE_OP)) अणु
		obj_desc->reference.resolved = TRUE;

		अगर ((op->common.aml_opcode == AML_INT_NAMEPATH_OP) &&
		    !obj_desc->reference.node) अणु
			/*
			 * Name was unresolved above.
			 * Get the prefix node क्रम later lookup
			 */
			obj_desc->reference.node =
			    walk_state->scope_info->scope.node;
			obj_desc->reference.aml = op->common.aml;
			obj_desc->reference.resolved = FALSE;
		पूर्ण
	पूर्ण

	*obj_desc_ptr = obj_desc;
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_build_पूर्णांकernal_buffer_obj
 *
 * PARAMETERS:  walk_state      - Current walk state
 *              op              - Parser object to be translated
 *              buffer_length   - Length of the buffer
 *              obj_desc_ptr    - Where the ACPI पूर्णांकernal object is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Translate a parser Op package object to the equivalent
 *              namespace object
 *
 ******************************************************************************/

acpi_status
acpi_ds_build_पूर्णांकernal_buffer_obj(काष्ठा acpi_walk_state *walk_state,
				  जोड़ acpi_parse_object *op,
				  u32 buffer_length,
				  जोड़ acpi_opeअक्रम_object **obj_desc_ptr)
अणु
	जोड़ acpi_parse_object *arg;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_parse_object *byte_list;
	u32 byte_list_length = 0;

	ACPI_FUNCTION_TRACE(ds_build_पूर्णांकernal_buffer_obj);

	/*
	 * If we are evaluating a Named buffer object "Name (xxxx, Buffer)".
	 * The buffer object alपढ़ोy exists (from the NS node), otherwise it must
	 * be created.
	 */
	obj_desc = *obj_desc_ptr;
	अगर (!obj_desc) अणु

		/* Create a new buffer object */

		obj_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_BUFFER);
		*obj_desc_ptr = obj_desc;
		अगर (!obj_desc) अणु
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण
	पूर्ण

	/*
	 * Second arg is the buffer data (optional) byte_list can be either
	 * inभागidual bytes or a string initializer. In either हाल, a
	 * byte_list appears in the AML.
	 */
	arg = op->common.value.arg;	/* skip first arg */

	byte_list = arg->named.next;
	अगर (byte_list) अणु
		अगर (byte_list->common.aml_opcode != AML_INT_BYTELIST_OP) अणु
			ACPI_ERROR((AE_INFO,
				    "Expecting bytelist, found AML opcode 0x%X in op %p",
				    byte_list->common.aml_opcode, byte_list));

			acpi_ut_हटाओ_reference(obj_desc);
			वापस (AE_TYPE);
		पूर्ण

		byte_list_length = (u32) byte_list->common.value.पूर्णांकeger;
	पूर्ण

	/*
	 * The buffer length (number of bytes) will be the larger of:
	 * 1) The specअगरied buffer length and
	 * 2) The length of the initializer byte list
	 */
	obj_desc->buffer.length = buffer_length;
	अगर (byte_list_length > buffer_length) अणु
		obj_desc->buffer.length = byte_list_length;
	पूर्ण

	/* Allocate the buffer */

	अगर (obj_desc->buffer.length == 0) अणु
		obj_desc->buffer.poपूर्णांकer = शून्य;
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "Buffer defined with zero length in AML, creating\n"));
	पूर्ण अन्यथा अणु
		obj_desc->buffer.poपूर्णांकer =
		    ACPI_ALLOCATE_ZEROED(obj_desc->buffer.length);
		अगर (!obj_desc->buffer.poपूर्णांकer) अणु
			acpi_ut_delete_object_desc(obj_desc);
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण

		/* Initialize buffer from the byte_list (अगर present) */

		अगर (byte_list) अणु
			स_नकल(obj_desc->buffer.poपूर्णांकer, byte_list->named.data,
			       byte_list_length);
		पूर्ण
	पूर्ण

	obj_desc->buffer.flags |= AOPOBJ_DATA_VALID;
	op->common.node = ACPI_CAST_PTR(काष्ठा acpi_namespace_node, obj_desc);
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_create_node
 *
 * PARAMETERS:  walk_state      - Current walk state
 *              node            - NS Node to be initialized
 *              op              - Parser object to be translated
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create the object to be associated with a namespace node
 *
 ******************************************************************************/

acpi_status
acpi_ds_create_node(काष्ठा acpi_walk_state *walk_state,
		    काष्ठा acpi_namespace_node *node,
		    जोड़ acpi_parse_object *op)
अणु
	acpi_status status;
	जोड़ acpi_opeअक्रम_object *obj_desc;

	ACPI_FUNCTION_TRACE_PTR(ds_create_node, op);

	/*
	 * Because of the execution pass through the non-control-method
	 * parts of the table, we can arrive here twice. Only init
	 * the named object node the first समय through
	 */
	अगर (acpi_ns_get_attached_object(node)) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	अगर (!op->common.value.arg) अणु

		/* No arguments, there is nothing to करो */

		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Build an पूर्णांकernal object क्रम the argument(s) */

	status =
	    acpi_ds_build_पूर्णांकernal_object(walk_state, op->common.value.arg,
					  &obj_desc);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Re-type the object according to its argument */

	node->type = obj_desc->common.type;

	/* Attach obj to node */

	status = acpi_ns_attach_object(node, obj_desc, node->type);

	/* Remove local reference to the object */

	acpi_ut_हटाओ_reference(obj_desc);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_init_object_from_op
 *
 * PARAMETERS:  walk_state      - Current walk state
 *              op              - Parser op used to init the पूर्णांकernal object
 *              opcode          - AML opcode associated with the object
 *              ret_obj_desc    - Namespace object to be initialized
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initialize a namespace object from a parser Op and its
 *              associated arguments. The namespace object is a more compact
 *              representation of the Op and its arguments.
 *
 ******************************************************************************/

acpi_status
acpi_ds_init_object_from_op(काष्ठा acpi_walk_state *walk_state,
			    जोड़ acpi_parse_object *op,
			    u16 opcode,
			    जोड़ acpi_opeअक्रम_object **ret_obj_desc)
अणु
	स्थिर काष्ठा acpi_opcode_info *op_info;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ds_init_object_from_op);

	obj_desc = *ret_obj_desc;
	op_info = acpi_ps_get_opcode_info(opcode);
	अगर (op_info->class == AML_CLASS_UNKNOWN) अणु

		/* Unknown opcode */

		वापस_ACPI_STATUS(AE_TYPE);
	पूर्ण

	/* Perक्रमm per-object initialization */

	चयन (obj_desc->common.type) अणु
	हाल ACPI_TYPE_BUFFER:
		/*
		 * Defer evaluation of Buffer term_arg opeअक्रम
		 */
		obj_desc->buffer.node =
		    ACPI_CAST_PTR(काष्ठा acpi_namespace_node,
				  walk_state->opeअक्रमs[0]);
		obj_desc->buffer.aml_start = op->named.data;
		obj_desc->buffer.aml_length = op->named.length;
		अवरोध;

	हाल ACPI_TYPE_PACKAGE:
		/*
		 * Defer evaluation of Package term_arg opeअक्रम and all
		 * package elements. (01/2017): We defer the element
		 * resolution to allow क्रमward references from the package
		 * in order to provide compatibility with other ACPI
		 * implementations.
		 */
		obj_desc->package.node =
		    ACPI_CAST_PTR(काष्ठा acpi_namespace_node,
				  walk_state->opeअक्रमs[0]);

		अगर (!op->named.data) अणु
			वापस_ACPI_STATUS(AE_OK);
		पूर्ण

		obj_desc->package.aml_start = op->named.data;
		obj_desc->package.aml_length = op->named.length;
		अवरोध;

	हाल ACPI_TYPE_INTEGER:

		चयन (op_info->type) अणु
		हाल AML_TYPE_CONSTANT:
			/*
			 * Resolve AML Constants here - AND ONLY HERE!
			 * All स्थिरants are पूर्णांकegers.
			 * We mark the पूर्णांकeger with a flag that indicates that it started
			 * lअगरe as a स्थिरant -- so that stores to स्थिरants will perक्रमm
			 * as expected (noop). zero_op is used as a placeholder क्रम optional
			 * target opeअक्रमs.
			 */
			obj_desc->common.flags = AOPOBJ_AML_CONSTANT;

			चयन (opcode) अणु
			हाल AML_ZERO_OP:

				obj_desc->पूर्णांकeger.value = 0;
				अवरोध;

			हाल AML_ONE_OP:

				obj_desc->पूर्णांकeger.value = 1;
				अवरोध;

			हाल AML_ONES_OP:

				obj_desc->पूर्णांकeger.value = ACPI_UINT64_MAX;

				/* Truncate value अगर we are executing from a 32-bit ACPI table */

				(व्योम)acpi_ex_truncate_क्रम32bit_table(obj_desc);
				अवरोध;

			हाल AML_REVISION_OP:

				obj_desc->पूर्णांकeger.value = ACPI_CA_VERSION;
				अवरोध;

			शेष:

				ACPI_ERROR((AE_INFO,
					    "Unknown constant opcode 0x%X",
					    opcode));
				status = AE_AML_OPERAND_TYPE;
				अवरोध;
			पूर्ण
			अवरोध;

		हाल AML_TYPE_LITERAL:

			obj_desc->पूर्णांकeger.value = op->common.value.पूर्णांकeger;

			अगर (acpi_ex_truncate_क्रम32bit_table(obj_desc)) अणु

				/* Warn अगर we found a 64-bit स्थिरant in a 32-bit table */

				ACPI_WARNING((AE_INFO,
					      "Truncated 64-bit constant found in 32-bit table: %8.8X%8.8X => %8.8X",
					      ACPI_FORMAT_UINT64(op->common.
								 value.पूर्णांकeger),
					      (u32)obj_desc->पूर्णांकeger.value));
			पूर्ण
			अवरोध;

		शेष:

			ACPI_ERROR((AE_INFO, "Unknown Integer type 0x%X",
				    op_info->type));
			status = AE_AML_OPERAND_TYPE;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_STRING:

		obj_desc->string.poपूर्णांकer = op->common.value.string;
		obj_desc->string.length = (u32)म_माप(op->common.value.string);

		/*
		 * The string is contained in the ACPI table, करोn't ever try
		 * to delete it
		 */
		obj_desc->common.flags |= AOPOBJ_STATIC_POINTER;
		अवरोध;

	हाल ACPI_TYPE_METHOD:
		अवरोध;

	हाल ACPI_TYPE_LOCAL_REFERENCE:

		चयन (op_info->type) अणु
		हाल AML_TYPE_LOCAL_VARIABLE:

			/* Local ID (0-7) is (AML opcode - base AML_FIRST_LOCAL_OP) */

			obj_desc->reference.value =
			    ((u32)opcode) - AML_FIRST_LOCAL_OP;
			obj_desc->reference.class = ACPI_REFCLASS_LOCAL;

			status =
			    acpi_ds_method_data_get_node(ACPI_REFCLASS_LOCAL,
							 obj_desc->reference.
							 value, walk_state,
							 ACPI_CAST_INसूचीECT_PTR
							 (काष्ठा
							  acpi_namespace_node,
							  &obj_desc->reference.
							  object));
			अवरोध;

		हाल AML_TYPE_METHOD_ARGUMENT:

			/* Arg ID (0-6) is (AML opcode - base AML_FIRST_ARG_OP) */

			obj_desc->reference.value =
			    ((u32)opcode) - AML_FIRST_ARG_OP;
			obj_desc->reference.class = ACPI_REFCLASS_ARG;

			status = acpi_ds_method_data_get_node(ACPI_REFCLASS_ARG,
							      obj_desc->
							      reference.value,
							      walk_state,
							      ACPI_CAST_INसूचीECT_PTR
							      (काष्ठा
							       acpi_namespace_node,
							       &obj_desc->
							       reference.
							       object));
			अवरोध;

		शेष:	/* Object name or Debug object */

			चयन (op->common.aml_opcode) अणु
			हाल AML_INT_NAMEPATH_OP:

				/* Node was saved in Op */

				obj_desc->reference.node = op->common.node;
				obj_desc->reference.class = ACPI_REFCLASS_NAME;
				अगर (op->common.node) अणु
					obj_desc->reference.object =
					    op->common.node->object;
				पूर्ण
				अवरोध;

			हाल AML_DEBUG_OP:

				obj_desc->reference.class = ACPI_REFCLASS_DEBUG;
				अवरोध;

			शेष:

				ACPI_ERROR((AE_INFO,
					    "Unimplemented reference type for AML opcode: 0x%4.4X",
					    opcode));
				वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:

		ACPI_ERROR((AE_INFO, "Unimplemented data type: 0x%X",
			    obj_desc->common.type));

		status = AE_AML_OPERAND_TYPE;
		अवरोध;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण
