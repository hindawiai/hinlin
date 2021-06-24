<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exprep - ACPI AML field prep utilities
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acinterp.h"
#समावेश "amlcode.h"
#समावेश "acnamesp.h"
#समावेश "acdispat.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exprep")

/* Local prototypes */
अटल u32
acpi_ex_decode_field_access(जोड़ acpi_opeअक्रम_object *obj_desc,
			    u8 field_flags, u32 * वापस_byte_alignment);

#अगर_घोषित ACPI_UNDER_DEVELOPMENT

अटल u32
acpi_ex_generate_access(u32 field_bit_offset,
			u32 field_bit_length, u32 region_length);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_generate_access
 *
 * PARAMETERS:  field_bit_offset    - Start of field within parent region/buffer
 *              field_bit_length    - Length of field in bits
 *              region_length       - Length of parent in bytes
 *
 * RETURN:      Field granularity (8, 16, 32 or 64) and
 *              byte_alignment (1, 2, 3, or 4)
 *
 * DESCRIPTION: Generate an optimal access width क्रम fields defined with the
 *              any_acc keyword.
 *
 * NOTE: Need to have the region_length in order to check क्रम boundary
 *       conditions (end-of-region). However, the region_length is a deferred
 *       operation. Thereक्रमe, to complete this implementation, the generation
 *       of this access width must be deferred until the region length has
 *       been evaluated.
 *
 ******************************************************************************/

अटल u32
acpi_ex_generate_access(u32 field_bit_offset,
			u32 field_bit_length, u32 region_length)
अणु
	u32 field_byte_length;
	u32 field_byte_offset;
	u32 field_byte_end_offset;
	u32 access_byte_width;
	u32 field_start_offset;
	u32 field_end_offset;
	u32 minimum_access_width = 0xFFFFFFFF;
	u32 minimum_accesses = 0xFFFFFFFF;
	u32 accesses;

	ACPI_FUNCTION_TRACE(ex_generate_access);

	/* Round Field start offset and length to "minimal" byte boundaries */

	field_byte_offset = ACPI_DIV_8(ACPI_ROUND_DOWN(field_bit_offset, 8));

	field_byte_end_offset =
	    ACPI_DIV_8(ACPI_ROUND_UP(field_bit_length + field_bit_offset, 8));

	field_byte_length = field_byte_end_offset - field_byte_offset;

	ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
			  "Bit length %u, Bit offset %u\n",
			  field_bit_length, field_bit_offset));

	ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
			  "Byte Length %u, Byte Offset %u, End Offset %u\n",
			  field_byte_length, field_byte_offset,
			  field_byte_end_offset));

	/*
	 * Iterative search क्रम the maximum access width that is both aligned
	 * and करोes not go beyond the end of the region
	 *
	 * Start at byte_acc and work upwards to qword_acc max. (1,2,4,8 bytes)
	 */
	क्रम (access_byte_width = 1; access_byte_width <= 8;
	     access_byte_width <<= 1) अणु
		/*
		 * 1) Round end offset up to next access boundary and make sure that
		 *    this करोes not go beyond the end of the parent region.
		 * 2) When the Access width is greater than the field_byte_length, we
		 *    are करोne. (This करोes not optimize क्रम the perfectly aligned
		 *    हाल yet).
		 */
		अगर (ACPI_ROUND_UP(field_byte_end_offset, access_byte_width) <=
		    region_length) अणु
			field_start_offset =
			    ACPI_ROUND_DOWN(field_byte_offset,
					    access_byte_width) /
			    access_byte_width;

			field_end_offset =
			    ACPI_ROUND_UP((field_byte_length +
					   field_byte_offset),
					  access_byte_width) /
			    access_byte_width;

			accesses = field_end_offset - field_start_offset;

			ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
					  "AccessWidth %u end is within region\n",
					  access_byte_width));

			ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
					  "Field Start %u, Field End %u -- requires %u accesses\n",
					  field_start_offset, field_end_offset,
					  accesses));

			/* Single access is optimal */

			अगर (accesses <= 1) अणु
				ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
						  "Entire field can be accessed "
						  "with one operation of size %u\n",
						  access_byte_width));
				वापस_VALUE(access_byte_width);
			पूर्ण

			/*
			 * Fits in the region, but requires more than one पढ़ो/ग_लिखो.
			 * try the next wider access on next iteration
			 */
			अगर (accesses < minimum_accesses) अणु
				minimum_accesses = accesses;
				minimum_access_width = access_byte_width;
			पूर्ण
		पूर्ण अन्यथा अणु
			ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
					  "AccessWidth %u end is NOT within region\n",
					  access_byte_width));
			अगर (access_byte_width == 1) अणु
				ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
						  "Field goes beyond end-of-region!\n"));

				/* Field करोes not fit in the region at all */

				वापस_VALUE(0);
			पूर्ण

			/*
			 * This width goes beyond the end-of-region, back off to
			 * previous access
			 */
			ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
					  "Backing off to previous optimal access width of %u\n",
					  minimum_access_width));
			वापस_VALUE(minimum_access_width);
		पूर्ण
	पूर्ण

	/*
	 * Could not पढ़ो/ग_लिखो field with one operation,
	 * just use max access width
	 */
	ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
			  "Cannot access field in one operation, using width 8\n"));

	वापस_VALUE(8);
पूर्ण
#पूर्ण_अगर				/* ACPI_UNDER_DEVELOPMENT */

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_decode_field_access
 *
 * PARAMETERS:  obj_desc            - Field object
 *              field_flags         - Encoded fieldflags (contains access bits)
 *              वापस_byte_alignment - Where the byte alignment is वापसed
 *
 * RETURN:      Field granularity (8, 16, 32 or 64) and
 *              byte_alignment (1, 2, 3, or 4)
 *
 * DESCRIPTION: Decode the access_type bits of a field definition.
 *
 ******************************************************************************/

अटल u32
acpi_ex_decode_field_access(जोड़ acpi_opeअक्रम_object *obj_desc,
			    u8 field_flags, u32 * वापस_byte_alignment)
अणु
	u32 access;
	u32 byte_alignment;
	u32 bit_length;

	ACPI_FUNCTION_TRACE(ex_decode_field_access);

	access = (field_flags & AML_FIELD_ACCESS_TYPE_MASK);

	चयन (access) अणु
	हाल AML_FIELD_ACCESS_ANY:

#अगर_घोषित ACPI_UNDER_DEVELOPMENT
		byte_alignment =
		    acpi_ex_generate_access(obj_desc->common_field.
					    start_field_bit_offset,
					    obj_desc->common_field.bit_length,
					    0xFFFFFFFF
					    /* Temp until we pass region_length as parameter */
		    );
		bit_length = byte_alignment * 8;
#पूर्ण_अगर

		byte_alignment = 1;
		bit_length = 8;
		अवरोध;

	हाल AML_FIELD_ACCESS_BYTE:
	हाल AML_FIELD_ACCESS_BUFFER:	/* ACPI 2.0 (SMBus Buffer) */

		byte_alignment = 1;
		bit_length = 8;
		अवरोध;

	हाल AML_FIELD_ACCESS_WORD:

		byte_alignment = 2;
		bit_length = 16;
		अवरोध;

	हाल AML_FIELD_ACCESS_DWORD:

		byte_alignment = 4;
		bit_length = 32;
		अवरोध;

	हाल AML_FIELD_ACCESS_QWORD:	/* ACPI 2.0 */

		byte_alignment = 8;
		bit_length = 64;
		अवरोध;

	शेष:

		/* Invalid field access type */

		ACPI_ERROR((AE_INFO, "Unknown field access type 0x%X", access));

		वापस_UINT32(0);
	पूर्ण

	अगर (obj_desc->common.type == ACPI_TYPE_BUFFER_FIELD) अणु
		/*
		 * buffer_field access can be on any byte boundary, so the
		 * byte_alignment is always 1 byte -- regardless of any byte_alignment
		 * implied by the field access type.
		 */
		byte_alignment = 1;
	पूर्ण

	*वापस_byte_alignment = byte_alignment;
	वापस_UINT32(bit_length);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_prep_common_field_object
 *
 * PARAMETERS:  obj_desc            - The field object
 *              field_flags         - Access, lock_rule, and update_rule.
 *                                    The क्रमmat of a field_flag is described
 *                                    in the ACPI specअगरication
 *              field_attribute     - Special attributes (not used)
 *              field_bit_position  - Field start position
 *              field_bit_length    - Field length in number of bits
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initialize the areas of the field object that are common
 *              to the various types of fields. Note: This is very "sensitive"
 *              code because we are solving the general हाल क्रम field
 *              alignment.
 *
 ******************************************************************************/

acpi_status
acpi_ex_prep_common_field_object(जोड़ acpi_opeअक्रम_object *obj_desc,
				 u8 field_flags,
				 u8 field_attribute,
				 u32 field_bit_position, u32 field_bit_length)
अणु
	u32 access_bit_width;
	u32 byte_alignment;
	u32 nearest_byte_address;

	ACPI_FUNCTION_TRACE(ex_prep_common_field_object);

	/*
	 * Note: the काष्ठाure being initialized is the
	 * ACPI_COMMON_FIELD_INFO;  No काष्ठाure fields outside of the common
	 * area are initialized by this procedure.
	 */
	obj_desc->common_field.field_flags = field_flags;
	obj_desc->common_field.attribute = field_attribute;
	obj_desc->common_field.bit_length = field_bit_length;

	/*
	 * Decode the access type so we can compute offsets. The access type gives
	 * two pieces of inक्रमmation - the width of each field access and the
	 * necessary byte_alignment (address granularity) of the access.
	 *
	 * For any_acc, the access_bit_width is the largest width that is both
	 * necessary and possible in an attempt to access the whole field in one
	 * I/O operation. However, क्रम any_acc, the byte_alignment is always one
	 * byte.
	 *
	 * For all Buffer Fields, the byte_alignment is always one byte.
	 *
	 * For all other access types (Byte, Word, Dword, Qword), the Bitwidth is
	 * the same (equivalent) as the byte_alignment.
	 */
	access_bit_width =
	    acpi_ex_decode_field_access(obj_desc, field_flags, &byte_alignment);
	अगर (!access_bit_width) अणु
		वापस_ACPI_STATUS(AE_AML_OPERAND_VALUE);
	पूर्ण

	/* Setup width (access granularity) fields (values are: 1, 2, 4, 8) */

	obj_desc->common_field.access_byte_width = (u8)
	    ACPI_DIV_8(access_bit_width);

	/*
	 * base_byte_offset is the address of the start of the field within the
	 * region. It is the byte address of the first *datum* (field-width data
	 * unit) of the field. (i.e., the first datum that contains at least the
	 * first *bit* of the field.)
	 *
	 * Note: byte_alignment is always either equal to the access_bit_width or 8
	 * (Byte access), and it defines the addressing granularity of the parent
	 * region or buffer.
	 */
	nearest_byte_address =
	    ACPI_ROUND_BITS_DOWN_TO_BYTES(field_bit_position);
	obj_desc->common_field.base_byte_offset = (u32)
	    ACPI_ROUND_DOWN(nearest_byte_address, byte_alignment);

	/*
	 * start_field_bit_offset is the offset of the first bit of the field within
	 * a field datum.
	 */
	obj_desc->common_field.start_field_bit_offset = (u8)
	    (field_bit_position -
	     ACPI_MUL_8(obj_desc->common_field.base_byte_offset));

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_prep_field_value
 *
 * PARAMETERS:  info    - Contains all field creation info
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Conकाष्ठा an object of type जोड़ acpi_opeअक्रम_object with a
 *              subtype of def_field and connect it to the parent Node.
 *
 ******************************************************************************/

acpi_status acpi_ex_prep_field_value(काष्ठा acpi_create_field_info *info)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_opeअक्रम_object *second_desc = शून्य;
	acpi_status status;
	u32 access_byte_width;
	u32 type;

	ACPI_FUNCTION_TRACE(ex_prep_field_value);

	/* Parameter validation */

	अगर (info->field_type != ACPI_TYPE_LOCAL_INDEX_FIELD) अणु
		अगर (!info->region_node) अणु
			ACPI_ERROR((AE_INFO, "Null RegionNode"));
			वापस_ACPI_STATUS(AE_AML_NO_OPERAND);
		पूर्ण

		type = acpi_ns_get_type(info->region_node);
		अगर (type != ACPI_TYPE_REGION) अणु
			ACPI_ERROR((AE_INFO,
				    "Needed Region, found type 0x%X (%s)", type,
				    acpi_ut_get_type_name(type)));

			वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		पूर्ण
	पूर्ण

	/* Allocate a new field object */

	obj_desc = acpi_ut_create_पूर्णांकernal_object(info->field_type);
	अगर (!obj_desc) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/* Initialize areas of the object that are common to all fields */

	obj_desc->common_field.node = info->field_node;
	status = acpi_ex_prep_common_field_object(obj_desc,
						  info->field_flags,
						  info->attribute,
						  info->field_bit_position,
						  info->field_bit_length);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_ut_delete_object_desc(obj_desc);
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Initialize areas of the object that are specअगरic to the field type */

	चयन (info->field_type) अणु
	हाल ACPI_TYPE_LOCAL_REGION_FIELD:

		obj_desc->field.region_obj =
		    acpi_ns_get_attached_object(info->region_node);

		/* Fields specअगरic to generic_serial_bus fields */

		obj_desc->field.access_length = info->access_length;

		अगर (info->connection_node) अणु
			second_desc = info->connection_node->object;
			अगर (!(second_desc->common.flags & AOPOBJ_DATA_VALID)) अणु
				status =
				    acpi_ds_get_buffer_arguments(second_desc);
				अगर (ACPI_FAILURE(status)) अणु
					acpi_ut_delete_object_desc(obj_desc);
					वापस_ACPI_STATUS(status);
				पूर्ण
			पूर्ण

			obj_desc->field.resource_buffer =
			    second_desc->buffer.poपूर्णांकer;
			obj_desc->field.resource_length =
			    (u16)second_desc->buffer.length;
		पूर्ण अन्यथा अगर (info->resource_buffer) अणु
			obj_desc->field.resource_buffer = info->resource_buffer;
			obj_desc->field.resource_length = info->resource_length;
		पूर्ण

		obj_desc->field.pin_number_index = info->pin_number_index;

		/* Allow full data पढ़ो from EC address space */

		अगर ((obj_desc->field.region_obj->region.space_id ==
		     ACPI_ADR_SPACE_EC)
		    && (obj_desc->common_field.bit_length > 8)) अणु
			access_byte_width =
			    ACPI_ROUND_BITS_UP_TO_BYTES(obj_desc->common_field.
							bit_length);

			/* Maximum byte width supported is 255 */

			अगर (access_byte_width < 256) अणु
				obj_desc->common_field.access_byte_width =
				    (u8)access_byte_width;
			पूर्ण
		पूर्ण
		ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
				  "RegionField: BitOff %X, Off %X, Gran %X, Region %p\n",
				  obj_desc->field.start_field_bit_offset,
				  obj_desc->field.base_byte_offset,
				  obj_desc->field.access_byte_width,
				  obj_desc->field.region_obj));
		अवरोध;

	हाल ACPI_TYPE_LOCAL_BANK_FIELD:

		obj_desc->bank_field.value = info->bank_value;
		obj_desc->bank_field.region_obj =
		    acpi_ns_get_attached_object(info->region_node);
		obj_desc->bank_field.bank_obj =
		    acpi_ns_get_attached_object(info->रेजिस्टर_node);

		/* An additional reference क्रम the attached objects */

		acpi_ut_add_reference(obj_desc->bank_field.region_obj);
		acpi_ut_add_reference(obj_desc->bank_field.bank_obj);

		ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
				  "Bank Field: BitOff %X, Off %X, Gran %X, Region %p, BankReg %p\n",
				  obj_desc->bank_field.start_field_bit_offset,
				  obj_desc->bank_field.base_byte_offset,
				  obj_desc->field.access_byte_width,
				  obj_desc->bank_field.region_obj,
				  obj_desc->bank_field.bank_obj));

		/*
		 * Remember location in AML stream of the field unit
		 * opcode and opeअक्रमs -- since the bank_value
		 * opeअक्रमs must be evaluated.
		 */
		second_desc = obj_desc->common.next_object;
		second_desc->extra.aml_start =
		    ACPI_CAST_PTR(जोड़ acpi_parse_object,
				  info->data_रेजिस्टर_node)->named.data;
		second_desc->extra.aml_length =
		    ACPI_CAST_PTR(जोड़ acpi_parse_object,
				  info->data_रेजिस्टर_node)->named.length;

		अवरोध;

	हाल ACPI_TYPE_LOCAL_INDEX_FIELD:

		/* Get the Index and Data रेजिस्टरs */

		obj_desc->index_field.index_obj =
		    acpi_ns_get_attached_object(info->रेजिस्टर_node);
		obj_desc->index_field.data_obj =
		    acpi_ns_get_attached_object(info->data_रेजिस्टर_node);

		अगर (!obj_desc->index_field.data_obj
		    || !obj_desc->index_field.index_obj) अणु
			ACPI_ERROR((AE_INFO,
				    "Null Index Object during field prep"));
			acpi_ut_delete_object_desc(obj_desc);
			वापस_ACPI_STATUS(AE_AML_INTERNAL);
		पूर्ण

		/* An additional reference क्रम the attached objects */

		acpi_ut_add_reference(obj_desc->index_field.data_obj);
		acpi_ut_add_reference(obj_desc->index_field.index_obj);

		/*
		 * April 2006: Changed to match MS behavior
		 *
		 * The value written to the Index रेजिस्टर is the byte offset of the
		 * target field in units of the granularity of the index_field
		 *
		 * Previously, the value was calculated as an index in terms of the
		 * width of the Data रेजिस्टर, as below:
		 *
		 *      obj_desc->index_field.Value = (u32)
		 *          (Info->field_bit_position / ACPI_MUL_8 (
		 *              obj_desc->Field.access_byte_width));
		 *
		 * February 2006: Tried value as a byte offset:
		 *      obj_desc->index_field.Value = (u32)
		 *          ACPI_DIV_8 (Info->field_bit_position);
		 */
		obj_desc->index_field.value =
		    (u32) ACPI_ROUND_DOWN(ACPI_DIV_8(info->field_bit_position),
					  obj_desc->index_field.
					  access_byte_width);

		ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
				  "IndexField: BitOff %X, Off %X, Value %X, "
				  "Gran %X, Index %p, Data %p\n",
				  obj_desc->index_field.start_field_bit_offset,
				  obj_desc->index_field.base_byte_offset,
				  obj_desc->index_field.value,
				  obj_desc->field.access_byte_width,
				  obj_desc->index_field.index_obj,
				  obj_desc->index_field.data_obj));
		अवरोध;

	शेष:

		/* No other types should get here */

		अवरोध;
	पूर्ण

	/*
	 * Store the स्थिरructed descriptor (obj_desc) पूर्णांकo the parent Node,
	 * preserving the current type of that named_obj.
	 */
	status =
	    acpi_ns_attach_object(info->field_node, obj_desc,
				  acpi_ns_get_type(info->field_node));

	ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
			  "Set NamedObj %p [%4.4s], ObjDesc %p\n",
			  info->field_node,
			  acpi_ut_get_node_name(info->field_node), obj_desc));

	/* Remove local reference to the object */

	acpi_ut_हटाओ_reference(obj_desc);
	वापस_ACPI_STATUS(status);
पूर्ण
