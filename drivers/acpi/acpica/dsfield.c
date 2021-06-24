<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: dsfield - Dispatcher field routines
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "amlcode.h"
#समावेश "acdispat.h"
#समावेश "acinterp.h"
#समावेश "acnamesp.h"
#समावेश "acparser.h"

#अगर_घोषित ACPI_EXEC_APP
#समावेश "aecommon.h"
#पूर्ण_अगर

#घोषणा _COMPONENT          ACPI_DISPATCHER
ACPI_MODULE_NAME("dsfield")

/* Local prototypes */
#अगर_घोषित ACPI_ASL_COMPILER
#समावेश "acdisasm.h"
अटल acpi_status
acpi_ds_create_बाह्यal_region(acpi_status lookup_status,
			       जोड़ acpi_parse_object *op,
			       अक्षर *path,
			       काष्ठा acpi_walk_state *walk_state,
			       काष्ठा acpi_namespace_node **node);
#पूर्ण_अगर

अटल acpi_status
acpi_ds_get_field_names(काष्ठा acpi_create_field_info *info,
			काष्ठा acpi_walk_state *walk_state,
			जोड़ acpi_parse_object *arg);

#अगर_घोषित ACPI_ASL_COMPILER
/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_create_बाह्यal_region (iASL Disassembler only)
 *
 * PARAMETERS:  lookup_status   - Status from ns_lookup operation
 *              op              - Op containing the Field definition and args
 *              path            - Pathname of the region
 *  `           walk_state      - Current method state
 *              node            - Where the new region node is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Add region to the बाह्यal list अगर NOT_FOUND. Create a new
 *              region node/object.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ds_create_बाह्यal_region(acpi_status lookup_status,
			       जोड़ acpi_parse_object *op,
			       अक्षर *path,
			       काष्ठा acpi_walk_state *walk_state,
			       काष्ठा acpi_namespace_node **node)
अणु
	acpi_status status;
	जोड़ acpi_opeअक्रम_object *obj_desc;

	अगर (lookup_status != AE_NOT_FOUND) अणु
		वापस (lookup_status);
	पूर्ण

	/*
	 * Table disassembly:
	 * operation_region not found. Generate an External क्रम it, and
	 * insert the name पूर्णांकo the namespace.
	 */
	acpi_dm_add_op_to_बाह्यal_list(op, path, ACPI_TYPE_REGION, 0, 0);

	status = acpi_ns_lookup(walk_state->scope_info, path, ACPI_TYPE_REGION,
				ACPI_IMODE_LOAD_PASS1, ACPI_NS_SEARCH_PARENT,
				walk_state, node);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Must create and install a region object क्रम the new node */

	obj_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_REGION);
	अगर (!obj_desc) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	obj_desc->region.node = *node;
	status = acpi_ns_attach_object(*node, obj_desc, ACPI_TYPE_REGION);
	वापस (status);
पूर्ण
#पूर्ण_अगर

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_create_buffer_field
 *
 * PARAMETERS:  op                  - Current parse op (create_XXField)
 *              walk_state          - Current state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute the create_field चालकs:
 *              create_bit_field_op,
 *              create_byte_field_op,
 *              create_word_field_op,
 *              create_dword_field_op,
 *              create_qword_field_op,
 *              create_field_op     (all of which define a field in a buffer)
 *
 ******************************************************************************/

acpi_status
acpi_ds_create_buffer_field(जोड़ acpi_parse_object *op,
			    काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_parse_object *arg;
	काष्ठा acpi_namespace_node *node;
	acpi_status status;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_opeअक्रम_object *second_desc = शून्य;
	u32 flags;

	ACPI_FUNCTION_TRACE(ds_create_buffer_field);

	/*
	 * Get the name_string argument (name of the new buffer_field)
	 */
	अगर (op->common.aml_opcode == AML_CREATE_FIELD_OP) अणु

		/* For create_field, name is the 4th argument */

		arg = acpi_ps_get_arg(op, 3);
	पूर्ण अन्यथा अणु
		/* For all other create_XXXField चालकs, name is the 3rd argument */

		arg = acpi_ps_get_arg(op, 2);
	पूर्ण

	अगर (!arg) अणु
		वापस_ACPI_STATUS(AE_AML_NO_OPERAND);
	पूर्ण

	अगर (walk_state->deferred_node) अणु
		node = walk_state->deferred_node;
	पूर्ण अन्यथा अणु
		/* Execute flag should always be set when this function is entered */

		अगर (!(walk_state->parse_flags & ACPI_PARSE_EXECUTE)) अणु
			ACPI_ERROR((AE_INFO, "Parse execute mode is not set"));
			वापस_ACPI_STATUS(AE_AML_INTERNAL);
		पूर्ण

		/* Creating new namespace node, should not alपढ़ोy exist */

		flags = ACPI_NS_NO_UPSEARCH | ACPI_NS_DONT_OPEN_SCOPE |
		    ACPI_NS_ERROR_IF_FOUND;

		/*
		 * Mark node temporary अगर we are executing a normal control
		 * method. (Don't mark अगर this is a module-level code method)
		 */
		अगर (walk_state->method_node &&
		    !(walk_state->parse_flags & ACPI_PARSE_MODULE_LEVEL)) अणु
			flags |= ACPI_NS_TEMPORARY;
		पूर्ण

		/* Enter the name_string पूर्णांकo the namespace */

		status = acpi_ns_lookup(walk_state->scope_info,
					arg->common.value.string, ACPI_TYPE_ANY,
					ACPI_IMODE_LOAD_PASS1, flags,
					walk_state, &node);
		अगर ((walk_state->parse_flags & ACPI_PARSE_DISASSEMBLE)
		    && status == AE_ALREADY_EXISTS) अणु
			status = AE_OK;
		पूर्ण अन्यथा अगर (ACPI_FAILURE(status)) अणु
			ACPI_ERROR_NAMESPACE(walk_state->scope_info,
					     arg->common.value.string, status);
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण

	/*
	 * We could put the वापसed object (Node) on the object stack क्रम later,
	 * but क्रम now, we will put it in the "op" object that the parser uses,
	 * so we can get it again at the end of this scope.
	 */
	op->common.node = node;

	/*
	 * If there is no object attached to the node, this node was just created
	 * and we need to create the field object. Otherwise, this was a lookup
	 * of an existing node and we करोn't want to create the field object again.
	 */
	obj_desc = acpi_ns_get_attached_object(node);
	अगर (obj_desc) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/*
	 * The Field definition is not fully parsed at this समय.
	 * (We must save the address of the AML क्रम the buffer and index opeअक्रमs)
	 */

	/* Create the buffer field object */

	obj_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_BUFFER_FIELD);
	अगर (!obj_desc) अणु
		status = AE_NO_MEMORY;
		जाओ cleanup;
	पूर्ण

	/*
	 * Remember location in AML stream of the field unit opcode and opeअक्रमs
	 * -- since the buffer and index opeअक्रमs must be evaluated.
	 */
	second_desc = obj_desc->common.next_object;
	second_desc->extra.aml_start = op->named.data;
	second_desc->extra.aml_length = op->named.length;
	obj_desc->buffer_field.node = node;

	/* Attach स्थिरructed field descriptors to parent node */

	status = acpi_ns_attach_object(node, obj_desc, ACPI_TYPE_BUFFER_FIELD);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ cleanup;
	पूर्ण

cleanup:

	/* Remove local reference to the object */

	acpi_ut_हटाओ_reference(obj_desc);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_get_field_names
 *
 * PARAMETERS:  info            - create_field info काष्ठाure
 *              walk_state      - Current method state
 *              arg             - First parser arg क्रम the field name list
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Process all named fields in a field declaration. Names are
 *              entered पूर्णांकo the namespace.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ds_get_field_names(काष्ठा acpi_create_field_info *info,
			काष्ठा acpi_walk_state *walk_state,
			जोड़ acpi_parse_object *arg)
अणु
	acpi_status status;
	u64 position;
	जोड़ acpi_parse_object *child;

#अगर_घोषित ACPI_EXEC_APP
	जोड़ acpi_opeअक्रम_object *result_desc;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	अक्षर *name_path;
#पूर्ण_अगर

	ACPI_FUNCTION_TRACE_PTR(ds_get_field_names, info);

	/* First field starts at bit zero */

	info->field_bit_position = 0;

	/* Process all elements in the field list (of parse nodes) */

	जबतक (arg) अणु
		/*
		 * Four types of field elements are handled:
		 * 1) name - Enters a new named field पूर्णांकo the namespace
		 * 2) offset - specअगरies a bit offset
		 * 3) access_as - changes the access mode/attributes
		 * 4) connection - Associate a resource ढाँचा with the field
		 */
		चयन (arg->common.aml_opcode) अणु
		हाल AML_INT_RESERVEDFIELD_OP:

			position = (u64)info->field_bit_position +
			    (u64)arg->common.value.size;

			अगर (position > ACPI_UINT32_MAX) अणु
				ACPI_ERROR((AE_INFO,
					    "Bit offset within field too large (> 0xFFFFFFFF)"));
				वापस_ACPI_STATUS(AE_SUPPORT);
			पूर्ण

			info->field_bit_position = (u32) position;
			अवरोध;

		हाल AML_INT_ACCESSFIELD_OP:
		हाल AML_INT_EXTACCESSFIELD_OP:
			/*
			 * Get new access_type, access_attribute, and access_length fields
			 * -- to be used क्रम all field units that follow, until the
			 * end-of-field or another access_as keyword is encountered.
			 * NOTE. These three bytes are encoded in the पूर्णांकeger value
			 * of the parseop क्रम convenience.
			 *
			 * In field_flags, preserve the flag bits other than the
			 * ACCESS_TYPE bits.
			 */

			/* access_type (byte_acc, word_acc, etc.) */

			info->field_flags = (u8)
			    ((info->
			      field_flags & ~(AML_FIELD_ACCESS_TYPE_MASK)) |
			     ((u8)((u32)(arg->common.value.पूर्णांकeger & 0x07))));

			/* access_attribute (attrib_quick, attrib_byte, etc.) */

			info->attribute = (u8)
			    ((arg->common.value.पूर्णांकeger >> 8) & 0xFF);

			/* access_length (क्रम serial/buffer protocols) */

			info->access_length = (u8)
			    ((arg->common.value.पूर्णांकeger >> 16) & 0xFF);
			अवरोध;

		हाल AML_INT_CONNECTION_OP:
			/*
			 * Clear any previous connection. New connection is used क्रम all
			 * fields that follow, similar to access_as
			 */
			info->resource_buffer = शून्य;
			info->connection_node = शून्य;
			info->pin_number_index = 0;

			/*
			 * A Connection() is either an actual resource descriptor (buffer)
			 * or a named reference to a resource ढाँचा
			 */
			child = arg->common.value.arg;
			अगर (child->common.aml_opcode == AML_INT_BYTELIST_OP) अणु
				info->resource_buffer = child->named.data;
				info->resource_length =
				    (u16)child->named.value.पूर्णांकeger;
			पूर्ण अन्यथा अणु
				/* Lookup the Connection() namepath, it should alपढ़ोy exist */

				status = acpi_ns_lookup(walk_state->scope_info,
							child->common.value.
							name, ACPI_TYPE_ANY,
							ACPI_IMODE_EXECUTE,
							ACPI_NS_DONT_OPEN_SCOPE,
							walk_state,
							&info->connection_node);
				अगर (ACPI_FAILURE(status)) अणु
					ACPI_ERROR_NAMESPACE(walk_state->
							     scope_info,
							     child->common.
							     value.name,
							     status);
					वापस_ACPI_STATUS(status);
				पूर्ण
			पूर्ण
			अवरोध;

		हाल AML_INT_NAMEDFIELD_OP:

			/* Lookup the name, it should alपढ़ोy exist */

			status = acpi_ns_lookup(walk_state->scope_info,
						(अक्षर *)&arg->named.name,
						info->field_type,
						ACPI_IMODE_EXECUTE,
						ACPI_NS_DONT_OPEN_SCOPE,
						walk_state, &info->field_node);
			अगर (ACPI_FAILURE(status)) अणु
				ACPI_ERROR_NAMESPACE(walk_state->scope_info,
						     (अक्षर *)&arg->named.name,
						     status);
				वापस_ACPI_STATUS(status);
			पूर्ण अन्यथा अणु
				arg->common.node = info->field_node;
				info->field_bit_length = arg->common.value.size;

				/*
				 * If there is no object attached to the node, this node was
				 * just created and we need to create the field object.
				 * Otherwise, this was a lookup of an existing node and we
				 * करोn't want to create the field object again.
				 */
				अगर (!acpi_ns_get_attached_object
				    (info->field_node)) अणु
					status = acpi_ex_prep_field_value(info);
					अगर (ACPI_FAILURE(status)) अणु
						वापस_ACPI_STATUS(status);
					पूर्ण
#अगर_घोषित ACPI_EXEC_APP
					name_path =
					    acpi_ns_get_बाह्यal_pathname(info->
									  field_node);
					अगर (ACPI_SUCCESS
					    (ae_lookup_init_file_entry
					     (name_path, &obj_desc))) अणु
						acpi_ex_ग_लिखो_data_to_field
						    (obj_desc,
						     acpi_ns_get_attached_object
						     (info->field_node),
						     &result_desc);
						acpi_ut_हटाओ_reference
						    (obj_desc);
					पूर्ण
					ACPI_FREE(name_path);
#पूर्ण_अगर
				पूर्ण
			पूर्ण

			/* Keep track of bit position क्रम the next field */

			position = (u64)info->field_bit_position +
			    (u64)arg->common.value.size;

			अगर (position > ACPI_UINT32_MAX) अणु
				ACPI_ERROR((AE_INFO,
					    "Field [%4.4s] bit offset too large (> 0xFFFFFFFF)",
					    ACPI_CAST_PTR(अक्षर,
							  &info->field_node->
							  name)));
				वापस_ACPI_STATUS(AE_SUPPORT);
			पूर्ण

			info->field_bit_position += info->field_bit_length;
			info->pin_number_index++;	/* Index relative to previous Connection() */
			अवरोध;

		शेष:

			ACPI_ERROR((AE_INFO,
				    "Invalid opcode in field list: 0x%X",
				    arg->common.aml_opcode));
			वापस_ACPI_STATUS(AE_AML_BAD_OPCODE);
		पूर्ण

		arg = arg->common.next;
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_create_field
 *
 * PARAMETERS:  op              - Op containing the Field definition and args
 *              region_node     - Object क्रम the containing Operation Region
 *  `           walk_state      - Current method state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a new field in the specअगरied operation region
 *
 ******************************************************************************/

acpi_status
acpi_ds_create_field(जोड़ acpi_parse_object *op,
		     काष्ठा acpi_namespace_node *region_node,
		     काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status;
	जोड़ acpi_parse_object *arg;
	काष्ठा acpi_create_field_info info;

	ACPI_FUNCTION_TRACE_PTR(ds_create_field, op);

	/* First arg is the name of the parent op_region (must alपढ़ोy exist) */

	arg = op->common.value.arg;

	अगर (!region_node) अणु
		status =
		    acpi_ns_lookup(walk_state->scope_info,
				   arg->common.value.name, ACPI_TYPE_REGION,
				   ACPI_IMODE_EXECUTE, ACPI_NS_SEARCH_PARENT,
				   walk_state, &region_node);
#अगर_घोषित ACPI_ASL_COMPILER
		status = acpi_ds_create_बाह्यal_region(status, arg,
							arg->common.value.name,
							walk_state,
							&region_node);
#पूर्ण_अगर
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_ERROR_NAMESPACE(walk_state->scope_info,
					     arg->common.value.name, status);
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण

	स_रखो(&info, 0, माप(काष्ठा acpi_create_field_info));

	/* Second arg is the field flags */

	arg = arg->common.next;
	info.field_flags = (u8) arg->common.value.पूर्णांकeger;
	info.attribute = 0;

	/* Each reमुख्यing arg is a Named Field */

	info.field_type = ACPI_TYPE_LOCAL_REGION_FIELD;
	info.region_node = region_node;

	status = acpi_ds_get_field_names(&info, walk_state, arg->common.next);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	अगर (info.region_node->object->region.space_id ==
	    ACPI_ADR_SPACE_PLATFORM_COMM) अणु
		region_node->object->field.पूर्णांकernal_pcc_buffer =
		    ACPI_ALLOCATE_ZEROED(info.region_node->object->region.
					 length);
		अगर (!region_node->object->field.पूर्णांकernal_pcc_buffer) अणु
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_init_field_objects
 *
 * PARAMETERS:  op              - Op containing the Field definition and args
 *  `           walk_state      - Current method state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: For each "Field Unit" name in the argument list that is
 *              part of the field declaration, enter the name पूर्णांकo the
 *              namespace.
 *
 ******************************************************************************/

acpi_status
acpi_ds_init_field_objects(जोड़ acpi_parse_object *op,
			   काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status;
	जोड़ acpi_parse_object *arg = शून्य;
	काष्ठा acpi_namespace_node *node;
	u8 type = 0;
	u32 flags;

	ACPI_FUNCTION_TRACE_PTR(ds_init_field_objects, op);

	/* Execute flag should always be set when this function is entered */

	अगर (!(walk_state->parse_flags & ACPI_PARSE_EXECUTE)) अणु
		अगर (walk_state->parse_flags & ACPI_PARSE_DEFERRED_OP) अणु

			/* bank_field Op is deferred, just वापस OK */

			वापस_ACPI_STATUS(AE_OK);
		पूर्ण

		ACPI_ERROR((AE_INFO, "Parse deferred mode is not set"));
		वापस_ACPI_STATUS(AE_AML_INTERNAL);
	पूर्ण

	/*
	 * Get the field_list argument क्रम this opcode. This is the start of the
	 * list of field elements.
	 */
	चयन (walk_state->opcode) अणु
	हाल AML_FIELD_OP:

		arg = acpi_ps_get_arg(op, 2);
		type = ACPI_TYPE_LOCAL_REGION_FIELD;
		अवरोध;

	हाल AML_BANK_FIELD_OP:

		arg = acpi_ps_get_arg(op, 4);
		type = ACPI_TYPE_LOCAL_BANK_FIELD;
		अवरोध;

	हाल AML_INDEX_FIELD_OP:

		arg = acpi_ps_get_arg(op, 3);
		type = ACPI_TYPE_LOCAL_INDEX_FIELD;
		अवरोध;

	शेष:

		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Creating new namespace node(s), should not alपढ़ोy exist */

	flags = ACPI_NS_NO_UPSEARCH | ACPI_NS_DONT_OPEN_SCOPE |
	    ACPI_NS_ERROR_IF_FOUND;

	/*
	 * Mark node(s) temporary अगर we are executing a normal control
	 * method. (Don't mark अगर this is a module-level code method)
	 */
	अगर (walk_state->method_node &&
	    !(walk_state->parse_flags & ACPI_PARSE_MODULE_LEVEL)) अणु
		flags |= ACPI_NS_TEMPORARY;
	पूर्ण
#अगर_घोषित ACPI_EXEC_APP
	flags |= ACPI_NS_OVERRIDE_IF_FOUND;
#पूर्ण_अगर
	/*
	 * Walk the list of entries in the field_list
	 * Note: field_list can be of zero length. In this हाल, Arg will be शून्य.
	 */
	जबतक (arg) अणु
		/*
		 * Ignore OFFSET/ACCESSAS/CONNECTION terms here; we are only पूर्णांकerested
		 * in the field names in order to enter them पूर्णांकo the namespace.
		 */
		अगर (arg->common.aml_opcode == AML_INT_NAMEDFIELD_OP) अणु
			status = acpi_ns_lookup(walk_state->scope_info,
						(अक्षर *)&arg->named.name, type,
						ACPI_IMODE_LOAD_PASS1, flags,
						walk_state, &node);
			अगर (ACPI_FAILURE(status)) अणु
				ACPI_ERROR_NAMESPACE(walk_state->scope_info,
						     (अक्षर *)&arg->named.name,
						     status);
				अगर (status != AE_ALREADY_EXISTS) अणु
					वापस_ACPI_STATUS(status);
				पूर्ण

				/* Name alपढ़ोy exists, just ignore this error */
			पूर्ण

			arg->common.node = node;
		पूर्ण

		/* Get the next field element in the list */

		arg = arg->common.next;
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_create_bank_field
 *
 * PARAMETERS:  op              - Op containing the Field definition and args
 *              region_node     - Object क्रम the containing Operation Region
 *              walk_state      - Current method state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a new bank field in the specअगरied operation region
 *
 ******************************************************************************/

acpi_status
acpi_ds_create_bank_field(जोड़ acpi_parse_object *op,
			  काष्ठा acpi_namespace_node *region_node,
			  काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status;
	जोड़ acpi_parse_object *arg;
	काष्ठा acpi_create_field_info info;

	ACPI_FUNCTION_TRACE_PTR(ds_create_bank_field, op);

	/* First arg is the name of the parent op_region (must alपढ़ोy exist) */

	arg = op->common.value.arg;
	अगर (!region_node) अणु
		status =
		    acpi_ns_lookup(walk_state->scope_info,
				   arg->common.value.name, ACPI_TYPE_REGION,
				   ACPI_IMODE_EXECUTE, ACPI_NS_SEARCH_PARENT,
				   walk_state, &region_node);
#अगर_घोषित ACPI_ASL_COMPILER
		status = acpi_ds_create_बाह्यal_region(status, arg,
							arg->common.value.name,
							walk_state,
							&region_node);
#पूर्ण_अगर
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_ERROR_NAMESPACE(walk_state->scope_info,
					     arg->common.value.name, status);
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण

	/* Second arg is the Bank Register (Field) (must alपढ़ोy exist) */

	arg = arg->common.next;
	status =
	    acpi_ns_lookup(walk_state->scope_info, arg->common.value.string,
			   ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
			   ACPI_NS_SEARCH_PARENT, walk_state,
			   &info.रेजिस्टर_node);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_ERROR_NAMESPACE(walk_state->scope_info,
				     arg->common.value.string, status);
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Third arg is the bank_value
	 * This arg is a term_arg, not a स्थिरant
	 * It will be evaluated later, by acpi_ds_eval_bank_field_opeअक्रमs
	 */
	arg = arg->common.next;

	/* Fourth arg is the field flags */

	arg = arg->common.next;
	info.field_flags = (u8) arg->common.value.पूर्णांकeger;

	/* Each reमुख्यing arg is a Named Field */

	info.field_type = ACPI_TYPE_LOCAL_BANK_FIELD;
	info.region_node = region_node;

	/*
	 * Use Info.data_रेजिस्टर_node to store bank_field Op
	 * It's safe because data_रेजिस्टर_node will never be used when create
	 * bank field \we store aml_start and aml_length in the bank_field Op क्रम
	 * late evaluation. Used in acpi_ex_prep_field_value(Info)
	 *
	 * TBD: Or, should we add a field in काष्ठा acpi_create_field_info, like
	 * "void *ParentOp"?
	 */
	info.data_रेजिस्टर_node = (काष्ठा acpi_namespace_node *)op;

	status = acpi_ds_get_field_names(&info, walk_state, arg->common.next);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_create_index_field
 *
 * PARAMETERS:  op              - Op containing the Field definition and args
 *              region_node     - Object क्रम the containing Operation Region
 *  `           walk_state      - Current method state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a new index field in the specअगरied operation region
 *
 ******************************************************************************/

acpi_status
acpi_ds_create_index_field(जोड़ acpi_parse_object *op,
			   काष्ठा acpi_namespace_node *region_node,
			   काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status;
	जोड़ acpi_parse_object *arg;
	काष्ठा acpi_create_field_info info;

	ACPI_FUNCTION_TRACE_PTR(ds_create_index_field, op);

	/* First arg is the name of the Index रेजिस्टर (must alपढ़ोy exist) */

	arg = op->common.value.arg;
	status =
	    acpi_ns_lookup(walk_state->scope_info, arg->common.value.string,
			   ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
			   ACPI_NS_SEARCH_PARENT, walk_state,
			   &info.रेजिस्टर_node);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_ERROR_NAMESPACE(walk_state->scope_info,
				     arg->common.value.string, status);
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Second arg is the data रेजिस्टर (must alपढ़ोy exist) */

	arg = arg->common.next;
	status =
	    acpi_ns_lookup(walk_state->scope_info, arg->common.value.string,
			   ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
			   ACPI_NS_SEARCH_PARENT, walk_state,
			   &info.data_रेजिस्टर_node);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_ERROR_NAMESPACE(walk_state->scope_info,
				     arg->common.value.string, status);
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Next arg is the field flags */

	arg = arg->common.next;
	info.field_flags = (u8) arg->common.value.पूर्णांकeger;

	/* Each reमुख्यing arg is a Named Field */

	info.field_type = ACPI_TYPE_LOCAL_INDEX_FIELD;
	info.region_node = region_node;

	status = acpi_ds_get_field_names(&info, walk_state, arg->common.next);
	वापस_ACPI_STATUS(status);
पूर्ण
