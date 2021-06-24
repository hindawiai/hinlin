<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exfield - AML execution - field_unit पढ़ो/ग_लिखो
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acdispat.h"
#समावेश "acinterp.h"
#समावेश "amlcode.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exfield")

/*
 * This table maps the various Attrib protocols to the byte transfer
 * length. Used क्रम the generic serial bus.
 */
#घोषणा ACPI_INVALID_PROTOCOL_ID        0x80
#घोषणा ACPI_MAX_PROTOCOL_ID            0x0F
अटल स्थिर u8 acpi_protocol_lengths[] = अणु
	ACPI_INVALID_PROTOCOL_ID,	/* 0 - reserved */
	ACPI_INVALID_PROTOCOL_ID,	/* 1 - reserved */
	0x00,			/* 2 - ATTRIB_QUICK */
	ACPI_INVALID_PROTOCOL_ID,	/* 3 - reserved */
	0x01,			/* 4 - ATTRIB_SEND_RECEIVE */
	ACPI_INVALID_PROTOCOL_ID,	/* 5 - reserved */
	0x01,			/* 6 - ATTRIB_BYTE */
	ACPI_INVALID_PROTOCOL_ID,	/* 7 - reserved */
	0x02,			/* 8 - ATTRIB_WORD */
	ACPI_INVALID_PROTOCOL_ID,	/* 9 - reserved */
	0xFF,			/* A - ATTRIB_BLOCK  */
	0xFF,			/* B - ATTRIB_BYTES */
	0x02,			/* C - ATTRIB_PROCESS_CALL */
	0xFF,			/* D - ATTRIB_BLOCK_PROCESS_CALL */
	0xFF,			/* E - ATTRIB_RAW_BYTES */
	0xFF			/* F - ATTRIB_RAW_PROCESS_BYTES */
पूर्ण;

#घोषणा PCC_MASTER_SUBSPACE     3

/*
 * The following macros determine a given offset is a COMD field.
 * According to the specअगरication, generic subspaces (types 0-2) contains a
 * 2-byte COMD field at offset 4 and master subspaces (type 3) contains a 4-byte
 * COMD field starting at offset 12.
 */
#घोषणा GENERIC_SUBSPACE_COMMAND(a)     (4 == a || a == 5)
#घोषणा MASTER_SUBSPACE_COMMAND(a)      (12 <= a && a <= 15)

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_get_protocol_buffer_length
 *
 * PARAMETERS:  protocol_id     - The type of the protocol indicated by region
 *                                field access attributes
 *              वापस_length   - Where the protocol byte transfer length is
 *                                वापसed
 *
 * RETURN:      Status and decoded byte transfer length
 *
 * DESCRIPTION: This routine वापसs the length of the generic_serial_bus
 *              protocol bytes
 *
 ******************************************************************************/

acpi_status
acpi_ex_get_protocol_buffer_length(u32 protocol_id, u32 *वापस_length)
अणु

	अगर ((protocol_id > ACPI_MAX_PROTOCOL_ID) ||
	    (acpi_protocol_lengths[protocol_id] == ACPI_INVALID_PROTOCOL_ID)) अणु
		ACPI_ERROR((AE_INFO,
			    "Invalid Field/AccessAs protocol ID: 0x%4.4X",
			    protocol_id));

		वापस (AE_AML_PROTOCOL);
	पूर्ण

	*वापस_length = acpi_protocol_lengths[protocol_id];
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_पढ़ो_data_from_field
 *
 * PARAMETERS:  walk_state          - Current execution state
 *              obj_desc            - The named field
 *              ret_buffer_desc     - Where the वापस data object is stored
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Read from a named field. Returns either an Integer or a
 *              Buffer, depending on the size of the field and whether अगर a
 *              field is created by the create_field() चालक.
 *
 ******************************************************************************/

acpi_status
acpi_ex_पढ़ो_data_from_field(काष्ठा acpi_walk_state *walk_state,
			     जोड़ acpi_opeअक्रम_object *obj_desc,
			     जोड़ acpi_opeअक्रम_object **ret_buffer_desc)
अणु
	acpi_status status;
	जोड़ acpi_opeअक्रम_object *buffer_desc;
	व्योम *buffer;
	u32 buffer_length;

	ACPI_FUNCTION_TRACE_PTR(ex_पढ़ो_data_from_field, obj_desc);

	/* Parameter validation */

	अगर (!obj_desc) अणु
		वापस_ACPI_STATUS(AE_AML_NO_OPERAND);
	पूर्ण
	अगर (!ret_buffer_desc) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	अगर (obj_desc->common.type == ACPI_TYPE_BUFFER_FIELD) अणु
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
	पूर्ण अन्यथा अगर ((obj_desc->common.type == ACPI_TYPE_LOCAL_REGION_FIELD) &&
		   (obj_desc->field.region_obj->region.space_id ==
		    ACPI_ADR_SPACE_SMBUS
		    || obj_desc->field.region_obj->region.space_id ==
		    ACPI_ADR_SPACE_GSBUS
		    || obj_desc->field.region_obj->region.space_id ==
		    ACPI_ADR_SPACE_IPMI)) अणु

		/* SMBus, GSBus, IPMI serial */

		status = acpi_ex_पढ़ो_serial_bus(obj_desc, ret_buffer_desc);
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Allocate a buffer क्रम the contents of the field.
	 *
	 * If the field is larger than the current पूर्णांकeger width, create
	 * a BUFFER to hold it. Otherwise, use an INTEGER. This allows
	 * the use of arithmetic चालकs on the वापसed value अगर the
	 * field size is equal or smaller than an Integer.
	 *
	 * However, all buffer fields created by create_field चालक needs to
	 * reमुख्य as a buffer to match other AML पूर्णांकerpreter implementations.
	 *
	 * Note: Field.length is in bits.
	 */
	buffer_length =
	    (acpi_size)ACPI_ROUND_BITS_UP_TO_BYTES(obj_desc->field.bit_length);

	अगर (buffer_length > acpi_gbl_पूर्णांकeger_byte_width ||
	    (obj_desc->common.type == ACPI_TYPE_BUFFER_FIELD &&
	     obj_desc->buffer_field.is_create_field)) अणु

		/* Field is too large क्रम an Integer, create a Buffer instead */

		buffer_desc = acpi_ut_create_buffer_object(buffer_length);
		अगर (!buffer_desc) अणु
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण
		buffer = buffer_desc->buffer.poपूर्णांकer;
	पूर्ण अन्यथा अणु
		/* Field will fit within an Integer (normal हाल) */

		buffer_desc = acpi_ut_create_पूर्णांकeger_object((u64) 0);
		अगर (!buffer_desc) अणु
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण

		buffer_length = acpi_gbl_पूर्णांकeger_byte_width;
		buffer = &buffer_desc->पूर्णांकeger.value;
	पूर्ण

	अगर ((obj_desc->common.type == ACPI_TYPE_LOCAL_REGION_FIELD) &&
	    (obj_desc->field.region_obj->region.space_id ==
	     ACPI_ADR_SPACE_GPIO)) अणु

		/* General Purpose I/O */

		status = acpi_ex_पढ़ो_gpio(obj_desc, buffer);
		जाओ निकास;
	पूर्ण अन्यथा अगर ((obj_desc->common.type == ACPI_TYPE_LOCAL_REGION_FIELD) &&
		   (obj_desc->field.region_obj->region.space_id ==
		    ACPI_ADR_SPACE_PLATFORM_COMM)) अणु
		/*
		 * Reading from a PCC field unit करोes not require the handler because
		 * it only requires पढ़ोing from the पूर्णांकernal_pcc_buffer.
		 */
		ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
				  "PCC FieldRead bits %u\n",
				  obj_desc->field.bit_length));

		स_नकल(buffer,
		       obj_desc->field.region_obj->field.पूर्णांकernal_pcc_buffer +
		       obj_desc->field.base_byte_offset,
		       (acpi_size)ACPI_ROUND_BITS_UP_TO_BYTES(obj_desc->field.
							      bit_length));

		*ret_buffer_desc = buffer_desc;
		वापस AE_OK;
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
			  "FieldRead [TO]:   Obj %p, Type %X, Buf %p, ByteLen %X\n",
			  obj_desc, obj_desc->common.type, buffer,
			  buffer_length));
	ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
			  "FieldRead [FROM]: BitLen %X, BitOff %X, ByteOff %X\n",
			  obj_desc->common_field.bit_length,
			  obj_desc->common_field.start_field_bit_offset,
			  obj_desc->common_field.base_byte_offset));

	/* Lock entire transaction अगर requested */

	acpi_ex_acquire_global_lock(obj_desc->common_field.field_flags);

	/* Read from the field */

	status = acpi_ex_extract_from_field(obj_desc, buffer, buffer_length);
	acpi_ex_release_global_lock(obj_desc->common_field.field_flags);

निकास:
	अगर (ACPI_FAILURE(status)) अणु
		acpi_ut_हटाओ_reference(buffer_desc);
	पूर्ण अन्यथा अणु
		*ret_buffer_desc = buffer_desc;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_ग_लिखो_data_to_field
 *
 * PARAMETERS:  source_desc         - Contains data to ग_लिखो
 *              obj_desc            - The named field
 *              result_desc         - Where the वापस value is वापसed, अगर any
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Write to a named field
 *
 ******************************************************************************/

acpi_status
acpi_ex_ग_लिखो_data_to_field(जोड़ acpi_opeअक्रम_object *source_desc,
			    जोड़ acpi_opeअक्रम_object *obj_desc,
			    जोड़ acpi_opeअक्रम_object **result_desc)
अणु
	acpi_status status;
	u32 buffer_length;
	u32 data_length;
	व्योम *buffer;

	ACPI_FUNCTION_TRACE_PTR(ex_ग_लिखो_data_to_field, obj_desc);

	/* Parameter validation */

	अगर (!source_desc || !obj_desc) अणु
		वापस_ACPI_STATUS(AE_AML_NO_OPERAND);
	पूर्ण

	अगर (obj_desc->common.type == ACPI_TYPE_BUFFER_FIELD) अणु
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
	पूर्ण अन्यथा अगर ((obj_desc->common.type == ACPI_TYPE_LOCAL_REGION_FIELD) &&
		   (obj_desc->field.region_obj->region.space_id ==
		    ACPI_ADR_SPACE_GPIO)) अणु

		/* General Purpose I/O */

		status = acpi_ex_ग_लिखो_gpio(source_desc, obj_desc, result_desc);
		वापस_ACPI_STATUS(status);
	पूर्ण अन्यथा अगर ((obj_desc->common.type == ACPI_TYPE_LOCAL_REGION_FIELD) &&
		   (obj_desc->field.region_obj->region.space_id ==
		    ACPI_ADR_SPACE_SMBUS
		    || obj_desc->field.region_obj->region.space_id ==
		    ACPI_ADR_SPACE_GSBUS
		    || obj_desc->field.region_obj->region.space_id ==
		    ACPI_ADR_SPACE_IPMI)) अणु

		/* SMBus, GSBus, IPMI serial */

		status =
		    acpi_ex_ग_लिखो_serial_bus(source_desc, obj_desc,
					     result_desc);
		वापस_ACPI_STATUS(status);
	पूर्ण अन्यथा अगर ((obj_desc->common.type == ACPI_TYPE_LOCAL_REGION_FIELD) &&
		   (obj_desc->field.region_obj->region.space_id ==
		    ACPI_ADR_SPACE_PLATFORM_COMM)) अणु
		/*
		 * According to the spec a ग_लिखो to the COMD field will invoke the
		 * region handler. Otherwise, ग_लिखो to the pcc_पूर्णांकernal buffer. This
		 * implementation will use the offsets specअगरied rather than the name
		 * of the field. This is considered safer because some firmware tools
		 * are known to obfiscate named objects.
		 */
		data_length =
		    (acpi_size)ACPI_ROUND_BITS_UP_TO_BYTES(obj_desc->field.
							   bit_length);
		स_नकल(obj_desc->field.region_obj->field.पूर्णांकernal_pcc_buffer +
		       obj_desc->field.base_byte_offset,
		       source_desc->buffer.poपूर्णांकer, data_length);

		अगर ((obj_desc->field.region_obj->region.address ==
		     PCC_MASTER_SUBSPACE
		     && MASTER_SUBSPACE_COMMAND(obj_desc->field.
						base_byte_offset))
		    || GENERIC_SUBSPACE_COMMAND(obj_desc->field.
						base_byte_offset)) अणु

			/* Perक्रमm the ग_लिखो */

			ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
					  "PCC COMD field has been written. Invoking PCC handler now.\n"));

			status =
			    acpi_ex_access_region(obj_desc, 0,
						  (u64 *)obj_desc->field.
						  region_obj->field.
						  पूर्णांकernal_pcc_buffer,
						  ACPI_WRITE);
			वापस_ACPI_STATUS(status);
		पूर्ण
		वापस (AE_OK);
	पूर्ण

	/* Get a poपूर्णांकer to the data to be written */

	चयन (source_desc->common.type) अणु
	हाल ACPI_TYPE_INTEGER:

		buffer = &source_desc->पूर्णांकeger.value;
		buffer_length = माप(source_desc->पूर्णांकeger.value);
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		buffer = source_desc->buffer.poपूर्णांकer;
		buffer_length = source_desc->buffer.length;
		अवरोध;

	हाल ACPI_TYPE_STRING:

		buffer = source_desc->string.poपूर्णांकer;
		buffer_length = source_desc->string.length;
		अवरोध;

	शेष:
		वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
			  "FieldWrite [FROM]: Obj %p (%s:%X), Buf %p, ByteLen %X\n",
			  source_desc,
			  acpi_ut_get_type_name(source_desc->common.type),
			  source_desc->common.type, buffer, buffer_length));

	ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
			  "FieldWrite [TO]:   Obj %p (%s:%X), BitLen %X, BitOff %X, ByteOff %X\n",
			  obj_desc,
			  acpi_ut_get_type_name(obj_desc->common.type),
			  obj_desc->common.type,
			  obj_desc->common_field.bit_length,
			  obj_desc->common_field.start_field_bit_offset,
			  obj_desc->common_field.base_byte_offset));

	/* Lock entire transaction अगर requested */

	acpi_ex_acquire_global_lock(obj_desc->common_field.field_flags);

	/* Write to the field */

	status = acpi_ex_insert_पूर्णांकo_field(obj_desc, buffer, buffer_length);
	acpi_ex_release_global_lock(obj_desc->common_field.field_flags);
	वापस_ACPI_STATUS(status);
पूर्ण
