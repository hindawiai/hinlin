<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: dsopcode - Dispatcher support क्रम regions and fields
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
#समावेश "actables.h"

#घोषणा _COMPONENT          ACPI_DISPATCHER
ACPI_MODULE_NAME("dsopcode")

/* Local prototypes */
अटल acpi_status
acpi_ds_init_buffer_field(u16 aml_opcode,
			  जोड़ acpi_opeअक्रम_object *obj_desc,
			  जोड़ acpi_opeअक्रम_object *buffer_desc,
			  जोड़ acpi_opeअक्रम_object *offset_desc,
			  जोड़ acpi_opeअक्रम_object *length_desc,
			  जोड़ acpi_opeअक्रम_object *result_desc);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_initialize_region
 *
 * PARAMETERS:  obj_handle      - Region namespace node
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Front end to ev_initialize_region
 *
 ******************************************************************************/

acpi_status acpi_ds_initialize_region(acpi_handle obj_handle)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	acpi_status status;

	obj_desc = acpi_ns_get_attached_object(obj_handle);

	/* Namespace is NOT locked */

	status = acpi_ev_initialize_region(obj_desc);
	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_init_buffer_field
 *
 * PARAMETERS:  aml_opcode      - create_xxx_field
 *              obj_desc        - buffer_field object
 *              buffer_desc     - Host Buffer
 *              offset_desc     - Offset पूर्णांकo buffer
 *              length_desc     - Length of field (CREATE_FIELD_OP only)
 *              result_desc     - Where to store the result
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Perक्रमm actual initialization of a buffer field
 *
 ******************************************************************************/

अटल acpi_status
acpi_ds_init_buffer_field(u16 aml_opcode,
			  जोड़ acpi_opeअक्रम_object *obj_desc,
			  जोड़ acpi_opeअक्रम_object *buffer_desc,
			  जोड़ acpi_opeअक्रम_object *offset_desc,
			  जोड़ acpi_opeअक्रम_object *length_desc,
			  जोड़ acpi_opeअक्रम_object *result_desc)
अणु
	u32 offset;
	u32 bit_offset;
	u32 bit_count;
	u8 field_flags;
	acpi_status status;

	ACPI_FUNCTION_TRACE_PTR(ds_init_buffer_field, obj_desc);

	/* Host object must be a Buffer */

	अगर (buffer_desc->common.type != ACPI_TYPE_BUFFER) अणु
		ACPI_ERROR((AE_INFO,
			    "Target of Create Field is not a Buffer object - %s",
			    acpi_ut_get_object_type_name(buffer_desc)));

		status = AE_AML_OPERAND_TYPE;
		जाओ cleanup;
	पूर्ण

	/*
	 * The last parameter to all of these opcodes (result_desc) started
	 * out as a name_string, and should thereक्रमe now be a NS node
	 * after resolution in acpi_ex_resolve_opeअक्रमs().
	 */
	अगर (ACPI_GET_DESCRIPTOR_TYPE(result_desc) != ACPI_DESC_TYPE_NAMED) अणु
		ACPI_ERROR((AE_INFO,
			    "(%s) destination not a NS Node [%s]",
			    acpi_ps_get_opcode_name(aml_opcode),
			    acpi_ut_get_descriptor_name(result_desc)));

		status = AE_AML_OPERAND_TYPE;
		जाओ cleanup;
	पूर्ण

	offset = (u32) offset_desc->पूर्णांकeger.value;

	/*
	 * Setup the Bit offsets and counts, according to the opcode
	 */
	चयन (aml_opcode) अणु
	हाल AML_CREATE_FIELD_OP:

		/* Offset is in bits, count is in bits */

		field_flags = AML_FIELD_ACCESS_BYTE;
		bit_offset = offset;
		bit_count = (u32) length_desc->पूर्णांकeger.value;

		/* Must have a valid (>0) bit count */

		अगर (bit_count == 0) अणु
			ACPI_BIOS_ERROR((AE_INFO,
					 "Attempt to CreateField of length zero"));
			status = AE_AML_OPERAND_VALUE;
			जाओ cleanup;
		पूर्ण
		अवरोध;

	हाल AML_CREATE_BIT_FIELD_OP:

		/* Offset is in bits, Field is one bit */

		bit_offset = offset;
		bit_count = 1;
		field_flags = AML_FIELD_ACCESS_BYTE;
		अवरोध;

	हाल AML_CREATE_BYTE_FIELD_OP:

		/* Offset is in bytes, field is one byte */

		bit_offset = 8 * offset;
		bit_count = 8;
		field_flags = AML_FIELD_ACCESS_BYTE;
		अवरोध;

	हाल AML_CREATE_WORD_FIELD_OP:

		/* Offset is in bytes, field is one word */

		bit_offset = 8 * offset;
		bit_count = 16;
		field_flags = AML_FIELD_ACCESS_WORD;
		अवरोध;

	हाल AML_CREATE_DWORD_FIELD_OP:

		/* Offset is in bytes, field is one dword */

		bit_offset = 8 * offset;
		bit_count = 32;
		field_flags = AML_FIELD_ACCESS_DWORD;
		अवरोध;

	हाल AML_CREATE_QWORD_FIELD_OP:

		/* Offset is in bytes, field is one qword */

		bit_offset = 8 * offset;
		bit_count = 64;
		field_flags = AML_FIELD_ACCESS_QWORD;
		अवरोध;

	शेष:

		ACPI_ERROR((AE_INFO,
			    "Unknown field creation opcode 0x%02X",
			    aml_opcode));
		status = AE_AML_BAD_OPCODE;
		जाओ cleanup;
	पूर्ण

	/* Entire field must fit within the current length of the buffer */

	अगर ((bit_offset + bit_count) > (8 * (u32)buffer_desc->buffer.length)) अणु
		status = AE_AML_BUFFER_LIMIT;
		ACPI_BIOS_EXCEPTION((AE_INFO, status,
				     "Field [%4.4s] at bit offset/length %u/%u "
				     "exceeds size of target Buffer (%u bits)",
				     acpi_ut_get_node_name(result_desc),
				     bit_offset, bit_count,
				     8 * (u32)buffer_desc->buffer.length));
		जाओ cleanup;
	पूर्ण

	/*
	 * Initialize areas of the field object that are common to all fields
	 * For field_flags, use LOCK_RULE = 0 (NO_LOCK),
	 * UPDATE_RULE = 0 (UPDATE_PRESERVE)
	 */
	status =
	    acpi_ex_prep_common_field_object(obj_desc, field_flags, 0,
					     bit_offset, bit_count);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ cleanup;
	पूर्ण

	obj_desc->buffer_field.buffer_obj = buffer_desc;
	obj_desc->buffer_field.is_create_field =
	    aml_opcode == AML_CREATE_FIELD_OP;

	/* Reference count क्रम buffer_desc inherits obj_desc count */

	buffer_desc->common.reference_count = (u16)
	    (buffer_desc->common.reference_count +
	     obj_desc->common.reference_count);

cleanup:

	/* Always delete the opeअक्रमs */

	acpi_ut_हटाओ_reference(offset_desc);
	acpi_ut_हटाओ_reference(buffer_desc);

	अगर (aml_opcode == AML_CREATE_FIELD_OP) अणु
		acpi_ut_हटाओ_reference(length_desc);
	पूर्ण

	/* On failure, delete the result descriptor */

	अगर (ACPI_FAILURE(status)) अणु
		acpi_ut_हटाओ_reference(result_desc);	/* Result descriptor */
	पूर्ण अन्यथा अणु
		/* Now the address and length are valid क्रम this buffer_field */

		obj_desc->buffer_field.flags |= AOPOBJ_DATA_VALID;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_eval_buffer_field_opeअक्रमs
 *
 * PARAMETERS:  walk_state      - Current walk
 *              op              - A valid buffer_field Op object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get buffer_field Buffer and Index
 *              Called from acpi_ds_exec_end_op during buffer_field parse tree walk
 *
 ******************************************************************************/

acpi_status
acpi_ds_eval_buffer_field_opeअक्रमs(काष्ठा acpi_walk_state *walk_state,
				   जोड़ acpi_parse_object *op)
अणु
	acpi_status status;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	काष्ठा acpi_namespace_node *node;
	जोड़ acpi_parse_object *next_op;

	ACPI_FUNCTION_TRACE_PTR(ds_eval_buffer_field_opeअक्रमs, op);

	/*
	 * This is where we evaluate the address and length fields of the
	 * create_xxx_field declaration
	 */
	node = op->common.node;

	/* next_op poपूर्णांकs to the op that holds the Buffer */

	next_op = op->common.value.arg;

	/* Evaluate/create the address and length opeअक्रमs */

	status = acpi_ds_create_opeअक्रमs(walk_state, next_op);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	obj_desc = acpi_ns_get_attached_object(node);
	अगर (!obj_desc) अणु
		वापस_ACPI_STATUS(AE_NOT_EXIST);
	पूर्ण

	/* Resolve the opeअक्रमs */

	status =
	    acpi_ex_resolve_opeअक्रमs(op->common.aml_opcode, ACPI_WALK_OPERANDS,
				     walk_state);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_ERROR((AE_INFO, "(%s) bad operand(s), status 0x%X",
			    acpi_ps_get_opcode_name(op->common.aml_opcode),
			    status));

		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Initialize the Buffer Field */

	अगर (op->common.aml_opcode == AML_CREATE_FIELD_OP) अणु

		/* NOTE: Slightly dअगरferent opeअक्रमs क्रम this opcode */

		status =
		    acpi_ds_init_buffer_field(op->common.aml_opcode, obj_desc,
					      walk_state->opeअक्रमs[0],
					      walk_state->opeअक्रमs[1],
					      walk_state->opeअक्रमs[2],
					      walk_state->opeअक्रमs[3]);
	पूर्ण अन्यथा अणु
		/* All other, create_xxx_field opcodes */

		status =
		    acpi_ds_init_buffer_field(op->common.aml_opcode, obj_desc,
					      walk_state->opeअक्रमs[0],
					      walk_state->opeअक्रमs[1], शून्य,
					      walk_state->opeअक्रमs[2]);
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_eval_region_opeअक्रमs
 *
 * PARAMETERS:  walk_state      - Current walk
 *              op              - A valid region Op object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get region address and length
 *              Called from acpi_ds_exec_end_op during op_region parse tree walk
 *
 ******************************************************************************/

acpi_status
acpi_ds_eval_region_opeअक्रमs(काष्ठा acpi_walk_state *walk_state,
			     जोड़ acpi_parse_object *op)
अणु
	acpi_status status;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_opeअक्रम_object *opeअक्रम_desc;
	काष्ठा acpi_namespace_node *node;
	जोड़ acpi_parse_object *next_op;
	acpi_adr_space_type space_id;

	ACPI_FUNCTION_TRACE_PTR(ds_eval_region_opeअक्रमs, op);

	/*
	 * This is where we evaluate the address and length fields of the
	 * op_region declaration
	 */
	node = op->common.node;

	/* next_op poपूर्णांकs to the op that holds the space_ID */

	next_op = op->common.value.arg;
	space_id = (acpi_adr_space_type)next_op->common.value.पूर्णांकeger;

	/* next_op poपूर्णांकs to address op */

	next_op = next_op->common.next;

	/* Evaluate/create the address and length opeअक्रमs */

	status = acpi_ds_create_opeअक्रमs(walk_state, next_op);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Resolve the length and address opeअक्रमs to numbers */

	status =
	    acpi_ex_resolve_opeअक्रमs(op->common.aml_opcode, ACPI_WALK_OPERANDS,
				     walk_state);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	obj_desc = acpi_ns_get_attached_object(node);
	अगर (!obj_desc) अणु
		वापस_ACPI_STATUS(AE_NOT_EXIST);
	पूर्ण

	/*
	 * Get the length opeअक्रम and save it
	 * (at Top of stack)
	 */
	opeअक्रम_desc = walk_state->opeअक्रमs[walk_state->num_opeअक्रमs - 1];

	obj_desc->region.length = (u32) opeअक्रम_desc->पूर्णांकeger.value;
	acpi_ut_हटाओ_reference(opeअक्रम_desc);

	/* A zero-length operation region is unusable. Just warn */

	अगर (!obj_desc->region.length
	    && (space_id < ACPI_NUM_PREDEFINED_REGIONS)) अणु
		ACPI_WARNING((AE_INFO,
			      "Operation Region [%4.4s] has zero length (SpaceId %X)",
			      node->name.ascii, space_id));
	पूर्ण

	/*
	 * Get the address and save it
	 * (at top of stack - 1)
	 */
	opeअक्रम_desc = walk_state->opeअक्रमs[walk_state->num_opeअक्रमs - 2];

	obj_desc->region.address = (acpi_physical_address)
	    opeअक्रम_desc->पूर्णांकeger.value;
	acpi_ut_हटाओ_reference(opeअक्रम_desc);

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "RgnObj %p Addr %8.8X%8.8X Len %X\n",
			  obj_desc,
			  ACPI_FORMAT_UINT64(obj_desc->region.address),
			  obj_desc->region.length));

	status = acpi_ut_add_address_range(obj_desc->region.space_id,
					   obj_desc->region.address,
					   obj_desc->region.length, node);

	/* Now the address and length are valid क्रम this opregion */

	obj_desc->region.flags |= AOPOBJ_DATA_VALID;
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_eval_table_region_opeअक्रमs
 *
 * PARAMETERS:  walk_state      - Current walk
 *              op              - A valid region Op object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get region address and length.
 *              Called from acpi_ds_exec_end_op during data_table_region parse
 *              tree walk.
 *
 ******************************************************************************/

acpi_status
acpi_ds_eval_table_region_opeअक्रमs(काष्ठा acpi_walk_state *walk_state,
				   जोड़ acpi_parse_object *op)
अणु
	acpi_status status;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_opeअक्रम_object **opeअक्रम;
	काष्ठा acpi_namespace_node *node;
	जोड़ acpi_parse_object *next_op;
	काष्ठा acpi_table_header *table;
	u32 table_index;

	ACPI_FUNCTION_TRACE_PTR(ds_eval_table_region_opeअक्रमs, op);

	/*
	 * This is where we evaluate the Signature string, oem_id string,
	 * and oem_table_id string of the Data Table Region declaration
	 */
	node = op->common.node;

	/* next_op poपूर्णांकs to Signature string op */

	next_op = op->common.value.arg;

	/*
	 * Evaluate/create the Signature string, oem_id string,
	 * and oem_table_id string opeअक्रमs
	 */
	status = acpi_ds_create_opeअक्रमs(walk_state, next_op);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	opeअक्रम = &walk_state->opeअक्रमs[0];

	/*
	 * Resolve the Signature string, oem_id string,
	 * and oem_table_id string opeअक्रमs
	 */
	status =
	    acpi_ex_resolve_opeअक्रमs(op->common.aml_opcode, ACPI_WALK_OPERANDS,
				     walk_state);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ cleanup;
	पूर्ण

	/* Find the ACPI table */

	status = acpi_tb_find_table(opeअक्रम[0]->string.poपूर्णांकer,
				    opeअक्रम[1]->string.poपूर्णांकer,
				    opeअक्रम[2]->string.poपूर्णांकer, &table_index);
	अगर (ACPI_FAILURE(status)) अणु
		अगर (status == AE_NOT_FOUND) अणु
			ACPI_ERROR((AE_INFO,
				    "ACPI Table [%4.4s] OEM:(%s, %s) not found in RSDT/XSDT",
				    opeअक्रम[0]->string.poपूर्णांकer,
				    opeअक्रम[1]->string.poपूर्णांकer,
				    opeअक्रम[2]->string.poपूर्णांकer));
		पूर्ण
		जाओ cleanup;
	पूर्ण

	status = acpi_get_table_by_index(table_index, &table);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ cleanup;
	पूर्ण

	obj_desc = acpi_ns_get_attached_object(node);
	अगर (!obj_desc) अणु
		status = AE_NOT_EXIST;
		जाओ cleanup;
	पूर्ण

	obj_desc->region.address = ACPI_PTR_TO_PHYSADDR(table);
	obj_desc->region.length = table->length;

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "RgnObj %p Addr %8.8X%8.8X Len %X\n",
			  obj_desc,
			  ACPI_FORMAT_UINT64(obj_desc->region.address),
			  obj_desc->region.length));

	/* Now the address and length are valid क्रम this opregion */

	obj_desc->region.flags |= AOPOBJ_DATA_VALID;

cleanup:
	acpi_ut_हटाओ_reference(opeअक्रम[0]);
	acpi_ut_हटाओ_reference(opeअक्रम[1]);
	acpi_ut_हटाओ_reference(opeअक्रम[2]);

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_eval_data_object_opeअक्रमs
 *
 * PARAMETERS:  walk_state      - Current walk
 *              op              - A valid data_object Op object
 *              obj_desc        - data_object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get the opeअक्रमs and complete the following data object types:
 *              Buffer, Package.
 *
 ******************************************************************************/

acpi_status
acpi_ds_eval_data_object_opeअक्रमs(काष्ठा acpi_walk_state *walk_state,
				  जोड़ acpi_parse_object *op,
				  जोड़ acpi_opeअक्रम_object *obj_desc)
अणु
	acpi_status status;
	जोड़ acpi_opeअक्रम_object *arg_desc;
	u32 length;

	ACPI_FUNCTION_TRACE(ds_eval_data_object_opeअक्रमs);

	/* The first opeअक्रम (क्रम all of these data objects) is the length */

	/*
	 * Set proper index पूर्णांकo opeअक्रम stack क्रम acpi_ds_obj_stack_push
	 * invoked inside acpi_ds_create_opeअक्रम.
	 */
	walk_state->opeअक्रम_index = walk_state->num_opeअक्रमs;

	/* Ignore अगर child is not valid */

	अगर (!op->common.value.arg) अणु
		ACPI_ERROR((AE_INFO,
			    "Missing child while evaluating opcode %4.4X, Op %p",
			    op->common.aml_opcode, op));
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	status = acpi_ds_create_opeअक्रम(walk_state, op->common.value.arg, 1);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	status = acpi_ex_resolve_opeअक्रमs(walk_state->opcode,
					  &(walk_state->
					    opeअक्रमs[walk_state->num_opeअक्रमs -
						     1]), walk_state);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Extract length opeअक्रम */

	arg_desc = walk_state->opeअक्रमs[walk_state->num_opeअक्रमs - 1];
	length = (u32) arg_desc->पूर्णांकeger.value;

	/* Cleanup क्रम length opeअक्रम */

	status = acpi_ds_obj_stack_pop(1, walk_state);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	acpi_ut_हटाओ_reference(arg_desc);

	/*
	 * Create the actual data object
	 */
	चयन (op->common.aml_opcode) अणु
	हाल AML_BUFFER_OP:

		status =
		    acpi_ds_build_पूर्णांकernal_buffer_obj(walk_state, op, length,
						      &obj_desc);
		अवरोध;

	हाल AML_PACKAGE_OP:
	हाल AML_VARIABLE_PACKAGE_OP:

		status =
		    acpi_ds_build_पूर्णांकernal_package_obj(walk_state, op, length,
						       &obj_desc);
		अवरोध;

	शेष:

		वापस_ACPI_STATUS(AE_AML_BAD_OPCODE);
	पूर्ण

	अगर (ACPI_SUCCESS(status)) अणु
		/*
		 * Return the object in the walk_state, unless the parent is a package -
		 * in this हाल, the वापस object will be stored in the parse tree
		 * क्रम the package.
		 */
		अगर ((!op->common.parent) ||
		    ((op->common.parent->common.aml_opcode != AML_PACKAGE_OP) &&
		     (op->common.parent->common.aml_opcode !=
		      AML_VARIABLE_PACKAGE_OP)
		     && (op->common.parent->common.aml_opcode !=
			 AML_NAME_OP))) अणु
			walk_state->result_obj = obj_desc;
		पूर्ण
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_eval_bank_field_opeअक्रमs
 *
 * PARAMETERS:  walk_state      - Current walk
 *              op              - A valid bank_field Op object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get bank_field bank_value
 *              Called from acpi_ds_exec_end_op during bank_field parse tree walk
 *
 ******************************************************************************/

acpi_status
acpi_ds_eval_bank_field_opeअक्रमs(काष्ठा acpi_walk_state *walk_state,
				 जोड़ acpi_parse_object *op)
अणु
	acpi_status status;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_opeअक्रम_object *opeअक्रम_desc;
	काष्ठा acpi_namespace_node *node;
	जोड़ acpi_parse_object *next_op;
	जोड़ acpi_parse_object *arg;

	ACPI_FUNCTION_TRACE_PTR(ds_eval_bank_field_opeअक्रमs, op);

	/*
	 * This is where we evaluate the bank_value field of the
	 * bank_field declaration
	 */

	/* next_op poपूर्णांकs to the op that holds the Region */

	next_op = op->common.value.arg;

	/* next_op poपूर्णांकs to the op that holds the Bank Register */

	next_op = next_op->common.next;

	/* next_op poपूर्णांकs to the op that holds the Bank Value */

	next_op = next_op->common.next;

	/*
	 * Set proper index पूर्णांकo opeअक्रम stack क्रम acpi_ds_obj_stack_push
	 * invoked inside acpi_ds_create_opeअक्रम.
	 *
	 * We use walk_state->Opeअक्रमs[0] to store the evaluated bank_value
	 */
	walk_state->opeअक्रम_index = 0;

	status = acpi_ds_create_opeअक्रम(walk_state, next_op, 0);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	status = acpi_ex_resolve_to_value(&walk_state->opeअक्रमs[0], walk_state);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	ACPI_DUMP_OPERANDS(ACPI_WALK_OPERANDS,
			   acpi_ps_get_opcode_name(op->common.aml_opcode), 1);
	/*
	 * Get the bank_value opeअक्रम and save it
	 * (at Top of stack)
	 */
	opeअक्रम_desc = walk_state->opeअक्रमs[0];

	/* Arg poपूर्णांकs to the start Bank Field */

	arg = acpi_ps_get_arg(op, 4);
	जबतक (arg) अणु

		/* Ignore OFFSET and ACCESSAS terms here */

		अगर (arg->common.aml_opcode == AML_INT_NAMEDFIELD_OP) अणु
			node = arg->common.node;

			obj_desc = acpi_ns_get_attached_object(node);
			अगर (!obj_desc) अणु
				वापस_ACPI_STATUS(AE_NOT_EXIST);
			पूर्ण

			obj_desc->bank_field.value =
			    (u32) opeअक्रम_desc->पूर्णांकeger.value;
		पूर्ण

		/* Move to next field in the list */

		arg = arg->common.next;
	पूर्ण

	acpi_ut_हटाओ_reference(opeअक्रम_desc);
	वापस_ACPI_STATUS(status);
पूर्ण
