<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exfldio - Aml Field I/O
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acinterp.h"
#समावेश "amlcode.h"
#समावेश "acevents.h"
#समावेश "acdispat.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exfldio")

/* Local prototypes */
अटल acpi_status
acpi_ex_field_datum_io(जोड़ acpi_opeअक्रम_object *obj_desc,
		       u32 field_datum_byte_offset, u64 *value, u32 पढ़ो_ग_लिखो);

अटल u8
acpi_ex_रेजिस्टर_overflow(जोड़ acpi_opeअक्रम_object *obj_desc, u64 value);

अटल acpi_status
acpi_ex_setup_region(जोड़ acpi_opeअक्रम_object *obj_desc,
		     u32 field_datum_byte_offset);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_setup_region
 *
 * PARAMETERS:  obj_desc                - Field to be पढ़ो or written
 *              field_datum_byte_offset - Byte offset of this datum within the
 *                                        parent field
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Common processing क्रम acpi_ex_extract_from_field and
 *              acpi_ex_insert_पूर्णांकo_field. Initialize the Region अगर necessary and
 *              validate the request.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ex_setup_region(जोड़ acpi_opeअक्रम_object *obj_desc,
		     u32 field_datum_byte_offset)
अणु
	acpi_status status = AE_OK;
	जोड़ acpi_opeअक्रम_object *rgn_desc;
	u8 space_id;

	ACPI_FUNCTION_TRACE_U32(ex_setup_region, field_datum_byte_offset);

	rgn_desc = obj_desc->common_field.region_obj;

	/* We must have a valid region */

	अगर (rgn_desc->common.type != ACPI_TYPE_REGION) अणु
		ACPI_ERROR((AE_INFO, "Needed Region, found type 0x%X (%s)",
			    rgn_desc->common.type,
			    acpi_ut_get_object_type_name(rgn_desc)));

		वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
	पूर्ण

	space_id = rgn_desc->region.space_id;

	/* Validate the Space ID */

	अगर (!acpi_is_valid_space_id(space_id)) अणु
		ACPI_ERROR((AE_INFO,
			    "Invalid/unknown Address Space ID: 0x%2.2X",
			    space_id));
		वापस_ACPI_STATUS(AE_AML_INVALID_SPACE_ID);
	पूर्ण

	/*
	 * If the Region Address and Length have not been previously evaluated,
	 * evaluate them now and save the results.
	 */
	अगर (!(rgn_desc->common.flags & AOPOBJ_DATA_VALID)) अणु
		status = acpi_ds_get_region_arguments(rgn_desc);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण

	/*
	 * Exit now क्रम SMBus, GSBus or IPMI address space, it has a non-linear
	 * address space and the request cannot be directly validated
	 */
	अगर (space_id == ACPI_ADR_SPACE_SMBUS ||
	    space_id == ACPI_ADR_SPACE_GSBUS ||
	    space_id == ACPI_ADR_SPACE_IPMI) अणु

		/* SMBus or IPMI has a non-linear address space */

		वापस_ACPI_STATUS(AE_OK);
	पूर्ण
#अगर_घोषित ACPI_UNDER_DEVELOPMENT
	/*
	 * If the Field access is any_acc, we can now compute the optimal
	 * access (because we know know the length of the parent region)
	 */
	अगर (!(obj_desc->common.flags & AOPOBJ_DATA_VALID)) अणु
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/*
	 * Validate the request. The entire request from the byte offset क्रम a
	 * length of one field datum (access width) must fit within the region.
	 * (Region length is specअगरied in bytes)
	 */
	अगर (rgn_desc->region.length <
	    (obj_desc->common_field.base_byte_offset + field_datum_byte_offset +
	     obj_desc->common_field.access_byte_width)) अणु
		अगर (acpi_gbl_enable_पूर्णांकerpreter_slack) अणु
			/*
			 * Slack mode only:  We will go ahead and allow access to this
			 * field अगर it is within the region length rounded up to the next
			 * access width boundary. acpi_size cast क्रम 64-bit compile.
			 */
			अगर (ACPI_ROUND_UP(rgn_desc->region.length,
					  obj_desc->common_field.
					  access_byte_width) >=
			    ((acpi_size)obj_desc->common_field.
			     base_byte_offset +
			     obj_desc->common_field.access_byte_width +
			     field_datum_byte_offset)) अणु
				वापस_ACPI_STATUS(AE_OK);
			पूर्ण
		पूर्ण

		अगर (rgn_desc->region.length <
		    obj_desc->common_field.access_byte_width) अणु
			/*
			 * This is the हाल where the access_type (acc_word, etc.) is wider
			 * than the region itself. For example, a region of length one
			 * byte, and a field with Dword access specअगरied.
			 */
			ACPI_ERROR((AE_INFO,
				    "Field [%4.4s] access width (%u bytes) "
				    "too large for region [%4.4s] (length %u)",
				    acpi_ut_get_node_name(obj_desc->
							  common_field.node),
				    obj_desc->common_field.access_byte_width,
				    acpi_ut_get_node_name(rgn_desc->region.
							  node),
				    rgn_desc->region.length));
		पूर्ण

		/*
		 * Offset rounded up to next multiple of field width
		 * exceeds region length, indicate an error
		 */
		ACPI_ERROR((AE_INFO,
			    "Field [%4.4s] Base+Offset+Width %u+%u+%u "
			    "is beyond end of region [%4.4s] (length %u)",
			    acpi_ut_get_node_name(obj_desc->common_field.node),
			    obj_desc->common_field.base_byte_offset,
			    field_datum_byte_offset,
			    obj_desc->common_field.access_byte_width,
			    acpi_ut_get_node_name(rgn_desc->region.node),
			    rgn_desc->region.length));

		वापस_ACPI_STATUS(AE_AML_REGION_LIMIT);
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_access_region
 *
 * PARAMETERS:  obj_desc                - Field to be पढ़ो
 *              field_datum_byte_offset - Byte offset of this datum within the
 *                                        parent field
 *              value                   - Where to store value (must at least
 *                                        64 bits)
 *              function                - Read or Write flag plus other region-
 *                                        dependent flags
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Read or Write a single field datum to an Operation Region.
 *
 ******************************************************************************/

acpi_status
acpi_ex_access_region(जोड़ acpi_opeअक्रम_object *obj_desc,
		      u32 field_datum_byte_offset, u64 *value, u32 function)
अणु
	acpi_status status;
	जोड़ acpi_opeअक्रम_object *rgn_desc;
	u32 region_offset;

	ACPI_FUNCTION_TRACE(ex_access_region);

	/*
	 * Ensure that the region opeअक्रमs are fully evaluated and verअगरy
	 * the validity of the request
	 */
	status = acpi_ex_setup_region(obj_desc, field_datum_byte_offset);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * The physical address of this field datum is:
	 *
	 * 1) The base of the region, plus
	 * 2) The base offset of the field, plus
	 * 3) The current offset पूर्णांकo the field
	 */
	rgn_desc = obj_desc->common_field.region_obj;
	region_offset =
	    obj_desc->common_field.base_byte_offset + field_datum_byte_offset;

	अगर ((function & ACPI_IO_MASK) == ACPI_READ) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_BFIELD, "[READ]"));
	पूर्ण अन्यथा अणु
		ACPI_DEBUG_PRINT((ACPI_DB_BFIELD, "[WRITE]"));
	पूर्ण

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_BFIELD,
			      " Region [%s:%X], Width %X, ByteBase %X, Offset %X at %8.8X%8.8X\n",
			      acpi_ut_get_region_name(rgn_desc->region.
						      space_id),
			      rgn_desc->region.space_id,
			      obj_desc->common_field.access_byte_width,
			      obj_desc->common_field.base_byte_offset,
			      field_datum_byte_offset,
			      ACPI_FORMAT_UINT64(rgn_desc->region.address +
						 region_offset)));

	/* Invoke the appropriate address_space/op_region handler */

	status = acpi_ev_address_space_dispatch(rgn_desc, obj_desc,
						function, region_offset,
						ACPI_MUL_8(obj_desc->
							   common_field.
							   access_byte_width),
						value);

	अगर (ACPI_FAILURE(status)) अणु
		अगर (status == AE_NOT_IMPLEMENTED) अणु
			ACPI_ERROR((AE_INFO,
				    "Region %s (ID=%u) not implemented",
				    acpi_ut_get_region_name(rgn_desc->region.
							    space_id),
				    rgn_desc->region.space_id));
		पूर्ण अन्यथा अगर (status == AE_NOT_EXIST) अणु
			ACPI_ERROR((AE_INFO,
				    "Region %s (ID=%u) has no handler",
				    acpi_ut_get_region_name(rgn_desc->region.
							    space_id),
				    rgn_desc->region.space_id));
		पूर्ण
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_रेजिस्टर_overflow
 *
 * PARAMETERS:  obj_desc                - Register(Field) to be written
 *              value                   - Value to be stored
 *
 * RETURN:      TRUE अगर value overflows the field, FALSE otherwise
 *
 * DESCRIPTION: Check अगर a value is out of range of the field being written.
 *              Used to check अगर the values written to Index and Bank रेजिस्टरs
 *              are out of range. Normally, the value is simply truncated
 *              to fit the field, but this हाल is most likely a serious
 *              coding error in the ASL.
 *
 ******************************************************************************/

अटल u8
acpi_ex_रेजिस्टर_overflow(जोड़ acpi_opeअक्रम_object *obj_desc, u64 value)
अणु

	अगर (obj_desc->common_field.bit_length >= ACPI_INTEGER_BIT_SIZE) अणु
		/*
		 * The field is large enough to hold the maximum पूर्णांकeger, so we can
		 * never overflow it.
		 */
		वापस (FALSE);
	पूर्ण

	अगर (value >= ((u64) 1 << obj_desc->common_field.bit_length)) अणु
		/*
		 * The Value is larger than the maximum value that can fit पूर्णांकo
		 * the रेजिस्टर.
		 */
		ACPI_ERROR((AE_INFO,
			    "Index value 0x%8.8X%8.8X overflows field width 0x%X",
			    ACPI_FORMAT_UINT64(value),
			    obj_desc->common_field.bit_length));

		वापस (TRUE);
	पूर्ण

	/* The Value will fit पूर्णांकo the field with no truncation */

	वापस (FALSE);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_field_datum_io
 *
 * PARAMETERS:  obj_desc                - Field to be पढ़ो
 *              field_datum_byte_offset - Byte offset of this datum within the
 *                                        parent field
 *              value                   - Where to store value (must be 64 bits)
 *              पढ़ो_ग_लिखो              - Read or Write flag
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Read or Write a single datum of a field. The field_type is
 *              demultiplexed here to handle the dअगरferent types of fields
 *              (buffer_field, region_field, index_field, bank_field)
 *
 ******************************************************************************/

अटल acpi_status
acpi_ex_field_datum_io(जोड़ acpi_opeअक्रम_object *obj_desc,
		       u32 field_datum_byte_offset, u64 *value, u32 पढ़ो_ग_लिखो)
अणु
	acpi_status status;
	u64 local_value;

	ACPI_FUNCTION_TRACE_U32(ex_field_datum_io, field_datum_byte_offset);

	अगर (पढ़ो_ग_लिखो == ACPI_READ) अणु
		अगर (!value) अणु
			local_value = 0;

			/* To support पढ़ोs without saving वापस value */
			value = &local_value;
		पूर्ण

		/* Clear the entire वापस buffer first, [Very Important!] */

		*value = 0;
	पूर्ण

	/*
	 * The four types of fields are:
	 *
	 * buffer_field - Read/ग_लिखो from/to a Buffer
	 * region_field - Read/ग_लिखो from/to a Operation Region.
	 * bank_field  - Write to a Bank Register, then पढ़ो/ग_लिखो from/to an
	 *               operation_region
	 * index_field - Write to an Index Register, then पढ़ो/ग_लिखो from/to a
	 *               Data Register
	 */
	चयन (obj_desc->common.type) अणु
	हाल ACPI_TYPE_BUFFER_FIELD:
		/*
		 * If the buffer_field arguments have not been previously evaluated,
		 * evaluate them now and save the results.
		 */
		अगर (!(obj_desc->common.flags & AOPOBJ_DATA_VALID)) अणु
			status = acpi_ds_get_buffer_field_arguments(obj_desc);
			अगर (ACPI_FAILURE(status)) अणु
				वापस_ACPI_STATUS(status);
			पूर्ण
		पूर्ण

		अगर (पढ़ो_ग_लिखो == ACPI_READ) अणु
			/*
			 * Copy the data from the source buffer.
			 * Length is the field width in bytes.
			 */
			स_नकल(value,
			       (obj_desc->buffer_field.buffer_obj)->buffer.
			       poपूर्णांकer +
			       obj_desc->buffer_field.base_byte_offset +
			       field_datum_byte_offset,
			       obj_desc->common_field.access_byte_width);
		पूर्ण अन्यथा अणु
			/*
			 * Copy the data to the target buffer.
			 * Length is the field width in bytes.
			 */
			स_नकल((obj_desc->buffer_field.buffer_obj)->buffer.
			       poपूर्णांकer +
			       obj_desc->buffer_field.base_byte_offset +
			       field_datum_byte_offset, value,
			       obj_desc->common_field.access_byte_width);
		पूर्ण

		status = AE_OK;
		अवरोध;

	हाल ACPI_TYPE_LOCAL_BANK_FIELD:
		/*
		 * Ensure that the bank_value is not beyond the capacity of
		 * the रेजिस्टर
		 */
		अगर (acpi_ex_रेजिस्टर_overflow(obj_desc->bank_field.bank_obj,
					      (u64) obj_desc->bank_field.
					      value)) अणु
			वापस_ACPI_STATUS(AE_AML_REGISTER_LIMIT);
		पूर्ण

		/*
		 * For bank_fields, we must ग_लिखो the bank_value to the bank_रेजिस्टर
		 * (itself a region_field) beक्रमe we can access the data.
		 */
		status =
		    acpi_ex_insert_पूर्णांकo_field(obj_desc->bank_field.bank_obj,
					      &obj_desc->bank_field.value,
					      माप(obj_desc->bank_field.
						     value));
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		/*
		 * Now that the Bank has been selected, fall through to the
		 * region_field हाल and ग_लिखो the datum to the Operation Region
		 */

		ACPI_FALLTHROUGH;

	हाल ACPI_TYPE_LOCAL_REGION_FIELD:
		/*
		 * For simple region_fields, we just directly access the owning
		 * Operation Region.
		 */
		status =
		    acpi_ex_access_region(obj_desc, field_datum_byte_offset,
					  value, पढ़ो_ग_लिखो);
		अवरोध;

	हाल ACPI_TYPE_LOCAL_INDEX_FIELD:
		/*
		 * Ensure that the index_value is not beyond the capacity of
		 * the रेजिस्टर
		 */
		अगर (acpi_ex_रेजिस्टर_overflow(obj_desc->index_field.index_obj,
					      (u64) obj_desc->index_field.
					      value)) अणु
			वापस_ACPI_STATUS(AE_AML_REGISTER_LIMIT);
		पूर्ण

		/* Write the index value to the index_रेजिस्टर (itself a region_field) */

		field_datum_byte_offset += obj_desc->index_field.value;

		ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
				  "Write to Index Register: Value %8.8X\n",
				  field_datum_byte_offset));

		status =
		    acpi_ex_insert_पूर्णांकo_field(obj_desc->index_field.index_obj,
					      &field_datum_byte_offset,
					      माप(field_datum_byte_offset));
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		अगर (पढ़ो_ग_लिखो == ACPI_READ) अणु

			/* Read the datum from the data_रेजिस्टर */

			ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
					  "Read from Data Register\n"));

			status =
			    acpi_ex_extract_from_field(obj_desc->index_field.
						       data_obj, value,
						       माप(u64));
		पूर्ण अन्यथा अणु
			/* Write the datum to the data_रेजिस्टर */

			ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
					  "Write to Data Register: Value %8.8X%8.8X\n",
					  ACPI_FORMAT_UINT64(*value)));

			status =
			    acpi_ex_insert_पूर्णांकo_field(obj_desc->index_field.
						      data_obj, value,
						      माप(u64));
		पूर्ण
		अवरोध;

	शेष:

		ACPI_ERROR((AE_INFO, "Wrong object type in field I/O %u",
			    obj_desc->common.type));
		status = AE_AML_INTERNAL;
		अवरोध;
	पूर्ण

	अगर (ACPI_SUCCESS(status)) अणु
		अगर (पढ़ो_ग_लिखो == ACPI_READ) अणु
			ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
					  "Value Read %8.8X%8.8X, Width %u\n",
					  ACPI_FORMAT_UINT64(*value),
					  obj_desc->common_field.
					  access_byte_width));
		पूर्ण अन्यथा अणु
			ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
					  "Value Written %8.8X%8.8X, Width %u\n",
					  ACPI_FORMAT_UINT64(*value),
					  obj_desc->common_field.
					  access_byte_width));
		पूर्ण
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_ग_लिखो_with_update_rule
 *
 * PARAMETERS:  obj_desc                - Field to be written
 *              mask                    - biपंचांगask within field datum
 *              field_value             - Value to ग_लिखो
 *              field_datum_byte_offset - Offset of datum within field
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Apply the field update rule to a field ग_लिखो
 *
 ******************************************************************************/

acpi_status
acpi_ex_ग_लिखो_with_update_rule(जोड़ acpi_opeअक्रम_object *obj_desc,
			       u64 mask,
			       u64 field_value, u32 field_datum_byte_offset)
अणु
	acpi_status status = AE_OK;
	u64 merged_value;
	u64 current_value;

	ACPI_FUNCTION_TRACE_U32(ex_ग_लिखो_with_update_rule, mask);

	/* Start with the new bits  */

	merged_value = field_value;

	/* If the mask is all ones, we करोn't need to worry about the update rule */

	अगर (mask != ACPI_UINT64_MAX) अणु

		/* Decode the update rule */

		चयन (obj_desc->common_field.
			field_flags & AML_FIELD_UPDATE_RULE_MASK) अणु
		हाल AML_FIELD_UPDATE_PRESERVE:
			/*
			 * Check अगर update rule needs to be applied (not अगर mask is all
			 * ones)  The left shअगरt drops the bits we want to ignore.
			 */
			अगर ((~mask << (ACPI_MUL_8(माप(mask)) -
				       ACPI_MUL_8(obj_desc->common_field.
						  access_byte_width))) != 0) अणु
				/*
				 * Read the current contents of the byte/word/dword containing
				 * the field, and merge with the new field value.
				 */
				status =
				    acpi_ex_field_datum_io(obj_desc,
							   field_datum_byte_offset,
							   &current_value,
							   ACPI_READ);
				अगर (ACPI_FAILURE(status)) अणु
					वापस_ACPI_STATUS(status);
				पूर्ण

				merged_value |= (current_value & ~mask);
			पूर्ण
			अवरोध;

		हाल AML_FIELD_UPDATE_WRITE_AS_ONES:

			/* Set positions outside the field to all ones */

			merged_value |= ~mask;
			अवरोध;

		हाल AML_FIELD_UPDATE_WRITE_AS_ZEROS:

			/* Set positions outside the field to all zeros */

			merged_value &= mask;
			अवरोध;

		शेष:

			ACPI_ERROR((AE_INFO,
				    "Unknown UpdateRule value: 0x%X",
				    (obj_desc->common_field.field_flags &
				     AML_FIELD_UPDATE_RULE_MASK)));
			वापस_ACPI_STATUS(AE_AML_OPERAND_VALUE);
		पूर्ण
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
			  "Mask %8.8X%8.8X, DatumOffset %X, Width %X, "
			  "Value %8.8X%8.8X, MergedValue %8.8X%8.8X\n",
			  ACPI_FORMAT_UINT64(mask),
			  field_datum_byte_offset,
			  obj_desc->common_field.access_byte_width,
			  ACPI_FORMAT_UINT64(field_value),
			  ACPI_FORMAT_UINT64(merged_value)));

	/* Write the merged value */

	status =
	    acpi_ex_field_datum_io(obj_desc, field_datum_byte_offset,
				   &merged_value, ACPI_WRITE);

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_extract_from_field
 *
 * PARAMETERS:  obj_desc            - Field to be पढ़ो
 *              buffer              - Where to store the field data
 *              buffer_length       - Length of Buffer
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Retrieve the current value of the given field
 *
 ******************************************************************************/

acpi_status
acpi_ex_extract_from_field(जोड़ acpi_opeअक्रम_object *obj_desc,
			   व्योम *buffer, u32 buffer_length)
अणु
	acpi_status status;
	u64 raw_datum;
	u64 merged_datum;
	u32 field_offset = 0;
	u32 buffer_offset = 0;
	u32 buffer_tail_bits;
	u32 datum_count;
	u32 field_datum_count;
	u32 access_bit_width;
	u32 i;

	ACPI_FUNCTION_TRACE(ex_extract_from_field);

	/* Validate target buffer and clear it */

	अगर (buffer_length <
	    ACPI_ROUND_BITS_UP_TO_BYTES(obj_desc->common_field.bit_length)) अणु
		ACPI_ERROR((AE_INFO,
			    "Field size %u (bits) is too large for buffer (%u)",
			    obj_desc->common_field.bit_length, buffer_length));

		वापस_ACPI_STATUS(AE_BUFFER_OVERFLOW);
	पूर्ण

	स_रखो(buffer, 0, buffer_length);
	access_bit_width = ACPI_MUL_8(obj_desc->common_field.access_byte_width);

	/* Handle the simple हाल here */

	अगर ((obj_desc->common_field.start_field_bit_offset == 0) &&
	    (obj_desc->common_field.bit_length == access_bit_width)) अणु
		अगर (buffer_length >= माप(u64)) अणु
			status =
			    acpi_ex_field_datum_io(obj_desc, 0, buffer,
						   ACPI_READ);
		पूर्ण अन्यथा अणु
			/* Use raw_datum (u64) to handle buffers < 64 bits */

			status =
			    acpi_ex_field_datum_io(obj_desc, 0, &raw_datum,
						   ACPI_READ);
			स_नकल(buffer, &raw_datum, buffer_length);
		पूर्ण

		वापस_ACPI_STATUS(status);
	पूर्ण

/* TBD: Move to common setup code */

	/* Field algorithm is limited to माप(u64), truncate अगर needed */

	अगर (obj_desc->common_field.access_byte_width > माप(u64)) अणु
		obj_desc->common_field.access_byte_width = माप(u64);
		access_bit_width = माप(u64) * 8;
	पूर्ण

	/* Compute the number of datums (access width data items) */

	datum_count =
	    ACPI_ROUND_UP_TO(obj_desc->common_field.bit_length,
			     access_bit_width);

	field_datum_count = ACPI_ROUND_UP_TO(obj_desc->common_field.bit_length +
					     obj_desc->common_field.
					     start_field_bit_offset,
					     access_bit_width);

	/* Priming पढ़ो from the field */

	status =
	    acpi_ex_field_datum_io(obj_desc, field_offset, &raw_datum,
				   ACPI_READ);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण
	merged_datum =
	    raw_datum >> obj_desc->common_field.start_field_bit_offset;

	/* Read the rest of the field */

	क्रम (i = 1; i < field_datum_count; i++) अणु

		/* Get next input datum from the field */

		field_offset += obj_desc->common_field.access_byte_width;
		status =
		    acpi_ex_field_datum_io(obj_desc, field_offset, &raw_datum,
					   ACPI_READ);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		/*
		 * Merge with previous datum अगर necessary.
		 *
		 * Note: Beक्रमe the shअगरt, check अगर the shअगरt value will be larger than
		 * the पूर्णांकeger size. If so, there is no need to perक्रमm the operation.
		 * This aव्योमs the dअगरferences in behavior between dअगरferent compilers
		 * concerning shअगरt values larger than the target data width.
		 */
		अगर (access_bit_width -
		    obj_desc->common_field.start_field_bit_offset <
		    ACPI_INTEGER_BIT_SIZE) अणु
			merged_datum |=
			    raw_datum << (access_bit_width -
					  obj_desc->common_field.
					  start_field_bit_offset);
		पूर्ण

		अगर (i == datum_count) अणु
			अवरोध;
		पूर्ण

		/* Write merged datum to target buffer */

		स_नकल(((अक्षर *)buffer) + buffer_offset, &merged_datum,
		       ACPI_MIN(obj_desc->common_field.access_byte_width,
				buffer_length - buffer_offset));

		buffer_offset += obj_desc->common_field.access_byte_width;
		merged_datum =
		    raw_datum >> obj_desc->common_field.start_field_bit_offset;
	पूर्ण

	/* Mask off any extra bits in the last datum */

	buffer_tail_bits = obj_desc->common_field.bit_length % access_bit_width;
	अगर (buffer_tail_bits) अणु
		merged_datum &= ACPI_MASK_BITS_ABOVE(buffer_tail_bits);
	पूर्ण

	/* Write the last datum to the buffer */

	स_नकल(((अक्षर *)buffer) + buffer_offset, &merged_datum,
	       ACPI_MIN(obj_desc->common_field.access_byte_width,
			buffer_length - buffer_offset));

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_insert_पूर्णांकo_field
 *
 * PARAMETERS:  obj_desc            - Field to be written
 *              buffer              - Data to be written
 *              buffer_length       - Length of Buffer
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Store the Buffer contents पूर्णांकo the given field
 *
 ******************************************************************************/

acpi_status
acpi_ex_insert_पूर्णांकo_field(जोड़ acpi_opeअक्रम_object *obj_desc,
			  व्योम *buffer, u32 buffer_length)
अणु
	व्योम *new_buffer;
	acpi_status status;
	u64 mask;
	u64 width_mask;
	u64 merged_datum;
	u64 raw_datum = 0;
	u32 field_offset = 0;
	u32 buffer_offset = 0;
	u32 buffer_tail_bits;
	u32 datum_count;
	u32 field_datum_count;
	u32 access_bit_width;
	u32 required_length;
	u32 i;

	ACPI_FUNCTION_TRACE(ex_insert_पूर्णांकo_field);

	/* Validate input buffer */

	new_buffer = शून्य;
	required_length =
	    ACPI_ROUND_BITS_UP_TO_BYTES(obj_desc->common_field.bit_length);

	/*
	 * We must have a buffer that is at least as दीर्घ as the field
	 * we are writing to. This is because inभागidual fields are
	 * inभागisible and partial ग_लिखोs are not supported -- as per
	 * the ACPI specअगरication.
	 */
	अगर (buffer_length < required_length) अणु

		/* We need to create a new buffer */

		new_buffer = ACPI_ALLOCATE_ZEROED(required_length);
		अगर (!new_buffer) अणु
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण

		/*
		 * Copy the original data to the new buffer, starting
		 * at Byte zero. All unused (upper) bytes of the
		 * buffer will be 0.
		 */
		स_नकल((अक्षर *)new_buffer, (अक्षर *)buffer, buffer_length);
		buffer = new_buffer;
		buffer_length = required_length;
	पूर्ण

/* TBD: Move to common setup code */

	/* Algo is limited to माप(u64), so cut the access_byte_width */
	अगर (obj_desc->common_field.access_byte_width > माप(u64)) अणु
		obj_desc->common_field.access_byte_width = माप(u64);
	पूर्ण

	access_bit_width = ACPI_MUL_8(obj_desc->common_field.access_byte_width);

	/* Create the biपंचांगasks used क्रम bit insertion */

	width_mask = ACPI_MASK_BITS_ABOVE_64(access_bit_width);
	mask = width_mask &
	    ACPI_MASK_BITS_BELOW(obj_desc->common_field.start_field_bit_offset);

	/* Compute the number of datums (access width data items) */

	datum_count = ACPI_ROUND_UP_TO(obj_desc->common_field.bit_length,
				       access_bit_width);

	field_datum_count = ACPI_ROUND_UP_TO(obj_desc->common_field.bit_length +
					     obj_desc->common_field.
					     start_field_bit_offset,
					     access_bit_width);

	/* Get initial Datum from the input buffer */

	स_नकल(&raw_datum, buffer,
	       ACPI_MIN(obj_desc->common_field.access_byte_width,
			buffer_length - buffer_offset));

	merged_datum =
	    raw_datum << obj_desc->common_field.start_field_bit_offset;

	/* Write the entire field */

	क्रम (i = 1; i < field_datum_count; i++) अणु

		/* Write merged datum to the target field */

		merged_datum &= mask;
		status =
		    acpi_ex_ग_लिखो_with_update_rule(obj_desc, mask, merged_datum,
						   field_offset);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ निकास;
		पूर्ण

		field_offset += obj_desc->common_field.access_byte_width;

		/*
		 * Start new output datum by merging with previous input datum
		 * अगर necessary.
		 *
		 * Note: Beक्रमe the shअगरt, check अगर the shअगरt value will be larger than
		 * the पूर्णांकeger size. If so, there is no need to perक्रमm the operation.
		 * This aव्योमs the dअगरferences in behavior between dअगरferent compilers
		 * concerning shअगरt values larger than the target data width.
		 */
		अगर ((access_bit_width -
		     obj_desc->common_field.start_field_bit_offset) <
		    ACPI_INTEGER_BIT_SIZE) अणु
			merged_datum =
			    raw_datum >> (access_bit_width -
					  obj_desc->common_field.
					  start_field_bit_offset);
		पूर्ण अन्यथा अणु
			merged_datum = 0;
		पूर्ण

		mask = width_mask;

		अगर (i == datum_count) अणु
			अवरोध;
		पूर्ण

		/* Get the next input datum from the buffer */

		buffer_offset += obj_desc->common_field.access_byte_width;
		स_नकल(&raw_datum, ((अक्षर *)buffer) + buffer_offset,
		       ACPI_MIN(obj_desc->common_field.access_byte_width,
				buffer_length - buffer_offset));

		merged_datum |=
		    raw_datum << obj_desc->common_field.start_field_bit_offset;
	पूर्ण

	/* Mask off any extra bits in the last datum */

	buffer_tail_bits = (obj_desc->common_field.bit_length +
			    obj_desc->common_field.start_field_bit_offset) %
	    access_bit_width;
	अगर (buffer_tail_bits) अणु
		mask &= ACPI_MASK_BITS_ABOVE(buffer_tail_bits);
	पूर्ण

	/* Write the last datum to the field */

	merged_datum &= mask;
	status =
	    acpi_ex_ग_लिखो_with_update_rule(obj_desc, mask, merged_datum,
					   field_offset);

निकास:
	/* Free temporary buffer अगर we used one */

	अगर (new_buffer) अणु
		ACPI_FREE(new_buffer);
	पूर्ण
	वापस_ACPI_STATUS(status);
पूर्ण
