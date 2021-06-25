<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exserial - field_unit support क्रम serial address spaces
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
ACPI_MODULE_NAME("exserial")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_पढ़ो_gpio
 *
 * PARAMETERS:  obj_desc            - The named field to पढ़ो
 *              buffer              - Where the वापस data is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Read from a named field that references a Generic Serial Bus
 *              field
 *
 ******************************************************************************/
acpi_status acpi_ex_पढ़ो_gpio(जोड़ acpi_opeअक्रम_object *obj_desc, व्योम *buffer)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE_PTR(ex_पढ़ो_gpio, obj_desc);

	/*
	 * For GPIO (general_purpose_io), the Address will be the bit offset
	 * from the previous Connection() चालक, making it effectively a
	 * pin number index. The bit_length is the length of the field, which
	 * is thus the number of pins.
	 */
	ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
			  "GPIO FieldRead [FROM]:  Pin %u Bits %u\n",
			  obj_desc->field.pin_number_index,
			  obj_desc->field.bit_length));

	/* Lock entire transaction अगर requested */

	acpi_ex_acquire_global_lock(obj_desc->common_field.field_flags);

	/* Perक्रमm the पढ़ो */

	status = acpi_ex_access_region(obj_desc, 0, (u64 *)buffer, ACPI_READ);

	acpi_ex_release_global_lock(obj_desc->common_field.field_flags);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_ग_लिखो_gpio
 *
 * PARAMETERS:  source_desc         - Contains data to ग_लिखो. Expect to be
 *                                    an Integer object.
 *              obj_desc            - The named field
 *              result_desc         - Where the वापस value is वापसed, अगर any
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Write to a named field that references a General Purpose I/O
 *              field.
 *
 ******************************************************************************/

acpi_status
acpi_ex_ग_लिखो_gpio(जोड़ acpi_opeअक्रम_object *source_desc,
		   जोड़ acpi_opeअक्रम_object *obj_desc,
		   जोड़ acpi_opeअक्रम_object **वापस_buffer)
अणु
	acpi_status status;
	व्योम *buffer;

	ACPI_FUNCTION_TRACE_PTR(ex_ग_लिखो_gpio, obj_desc);

	/*
	 * For GPIO (general_purpose_io), we will bypass the entire field
	 * mechanism and hanकरोff the bit address and bit width directly to
	 * the handler. The Address will be the bit offset
	 * from the previous Connection() चालक, making it effectively a
	 * pin number index. The bit_length is the length of the field, which
	 * is thus the number of pins.
	 */
	अगर (source_desc->common.type != ACPI_TYPE_INTEGER) अणु
		वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_BFIELD,
			  "GPIO FieldWrite [FROM]: (%s:%X), Value %.8X  [TO]: Pin %u Bits %u\n",
			  acpi_ut_get_type_name(source_desc->common.type),
			  source_desc->common.type,
			  (u32)source_desc->पूर्णांकeger.value,
			  obj_desc->field.pin_number_index,
			  obj_desc->field.bit_length));

	buffer = &source_desc->पूर्णांकeger.value;

	/* Lock entire transaction अगर requested */

	acpi_ex_acquire_global_lock(obj_desc->common_field.field_flags);

	/* Perक्रमm the ग_लिखो */

	status = acpi_ex_access_region(obj_desc, 0, (u64 *)buffer, ACPI_WRITE);
	acpi_ex_release_global_lock(obj_desc->common_field.field_flags);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_पढ़ो_serial_bus
 *
 * PARAMETERS:  obj_desc            - The named field to पढ़ो
 *              वापस_buffer       - Where the वापस value is वापसed, अगर any
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Read from a named field that references a serial bus
 *              (SMBus, IPMI, or GSBus).
 *
 ******************************************************************************/

acpi_status
acpi_ex_पढ़ो_serial_bus(जोड़ acpi_opeअक्रम_object *obj_desc,
			जोड़ acpi_opeअक्रम_object **वापस_buffer)
अणु
	acpi_status status;
	u32 buffer_length;
	जोड़ acpi_opeअक्रम_object *buffer_desc;
	u32 function;
	u16 accessor_type;

	ACPI_FUNCTION_TRACE_PTR(ex_पढ़ो_serial_bus, obj_desc);

	/*
	 * This is an SMBus, GSBus or IPMI पढ़ो. We must create a buffer to
	 * hold the data and then directly access the region handler.
	 *
	 * Note: SMBus and GSBus protocol value is passed in upper 16-bits
	 * of Function
	 *
	 * Common buffer क्रमmat:
	 *     Status;    (Byte 0 of the data buffer)
	 *     Length;    (Byte 1 of the data buffer)
	 *     Data[x-1]: (Bytes 2-x of the arbitrary length data buffer)
	 */
	चयन (obj_desc->field.region_obj->region.space_id) अणु
	हाल ACPI_ADR_SPACE_SMBUS:

		buffer_length = ACPI_SMBUS_BUFFER_SIZE;
		function = ACPI_READ | (obj_desc->field.attribute << 16);
		अवरोध;

	हाल ACPI_ADR_SPACE_IPMI:

		buffer_length = ACPI_IPMI_BUFFER_SIZE;
		function = ACPI_READ;
		अवरोध;

	हाल ACPI_ADR_SPACE_GSBUS:

		accessor_type = obj_desc->field.attribute;
		अगर (accessor_type == AML_FIELD_ATTRIB_RAW_PROCESS_BYTES) अणु
			ACPI_ERROR((AE_INFO,
				    "Invalid direct read using bidirectional write-then-read protocol"));

			वापस_ACPI_STATUS(AE_AML_PROTOCOL);
		पूर्ण

		status =
		    acpi_ex_get_protocol_buffer_length(accessor_type,
						       &buffer_length);
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_ERROR((AE_INFO,
				    "Invalid protocol ID for GSBus: 0x%4.4X",
				    accessor_type));

			वापस_ACPI_STATUS(status);
		पूर्ण

		/* Add header length to get the full size of the buffer */

		buffer_length += ACPI_SERIAL_HEADER_SIZE;
		function = ACPI_READ | (accessor_type << 16);
		अवरोध;

	शेष:
		वापस_ACPI_STATUS(AE_AML_INVALID_SPACE_ID);
	पूर्ण

	/* Create the local transfer buffer that is वापसed to the caller */

	buffer_desc = acpi_ut_create_buffer_object(buffer_length);
	अगर (!buffer_desc) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/* Lock entire transaction अगर requested */

	acpi_ex_acquire_global_lock(obj_desc->common_field.field_flags);

	/* Call the region handler क्रम the ग_लिखो-then-पढ़ो */

	status = acpi_ex_access_region(obj_desc, 0,
				       ACPI_CAST_PTR(u64,
						     buffer_desc->buffer.
						     poपूर्णांकer), function);
	acpi_ex_release_global_lock(obj_desc->common_field.field_flags);

	*वापस_buffer = buffer_desc;
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_ग_लिखो_serial_bus
 *
 * PARAMETERS:  source_desc         - Contains data to ग_लिखो
 *              obj_desc            - The named field
 *              वापस_buffer       - Where the वापस value is वापसed, अगर any
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Write to a named field that references a serial bus
 *              (SMBus, IPMI, GSBus).
 *
 ******************************************************************************/

acpi_status
acpi_ex_ग_लिखो_serial_bus(जोड़ acpi_opeअक्रम_object *source_desc,
			 जोड़ acpi_opeअक्रम_object *obj_desc,
			 जोड़ acpi_opeअक्रम_object **वापस_buffer)
अणु
	acpi_status status;
	u32 buffer_length;
	u32 data_length;
	व्योम *buffer;
	जोड़ acpi_opeअक्रम_object *buffer_desc;
	u32 function;
	u16 accessor_type;

	ACPI_FUNCTION_TRACE_PTR(ex_ग_लिखो_serial_bus, obj_desc);

	/*
	 * This is an SMBus, GSBus or IPMI ग_लिखो. We will bypass the entire
	 * field mechanism and hanकरोff the buffer directly to the handler.
	 * For these address spaces, the buffer is bidirectional; on a
	 * ग_लिखो, वापस data is वापसed in the same buffer.
	 *
	 * Source must be a buffer of sufficient size, these are fixed size:
	 * ACPI_SMBUS_BUFFER_SIZE, or ACPI_IPMI_BUFFER_SIZE.
	 *
	 * Note: SMBus and GSBus protocol type is passed in upper 16-bits
	 * of Function
	 *
	 * Common buffer क्रमmat:
	 *     Status;    (Byte 0 of the data buffer)
	 *     Length;    (Byte 1 of the data buffer)
	 *     Data[x-1]: (Bytes 2-x of the arbitrary length data buffer)
	 */
	अगर (source_desc->common.type != ACPI_TYPE_BUFFER) अणु
		ACPI_ERROR((AE_INFO,
			    "SMBus/IPMI/GenericSerialBus write requires "
			    "Buffer, found type %s",
			    acpi_ut_get_object_type_name(source_desc)));

		वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
	पूर्ण

	चयन (obj_desc->field.region_obj->region.space_id) अणु
	हाल ACPI_ADR_SPACE_SMBUS:

		buffer_length = ACPI_SMBUS_BUFFER_SIZE;
		function = ACPI_WRITE | (obj_desc->field.attribute << 16);
		अवरोध;

	हाल ACPI_ADR_SPACE_IPMI:

		buffer_length = ACPI_IPMI_BUFFER_SIZE;
		function = ACPI_WRITE;
		अवरोध;

	हाल ACPI_ADR_SPACE_GSBUS:

		accessor_type = obj_desc->field.attribute;
		status =
		    acpi_ex_get_protocol_buffer_length(accessor_type,
						       &buffer_length);
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_ERROR((AE_INFO,
				    "Invalid protocol ID for GSBus: 0x%4.4X",
				    accessor_type));

			वापस_ACPI_STATUS(status);
		पूर्ण

		/* Add header length to get the full size of the buffer */

		buffer_length += ACPI_SERIAL_HEADER_SIZE;
		function = ACPI_WRITE | (accessor_type << 16);
		अवरोध;

	शेष:
		वापस_ACPI_STATUS(AE_AML_INVALID_SPACE_ID);
	पूर्ण

	/* Create the transfer/bidirectional/वापस buffer */

	buffer_desc = acpi_ut_create_buffer_object(buffer_length);
	अगर (!buffer_desc) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/* Copy the input buffer data to the transfer buffer */

	buffer = buffer_desc->buffer.poपूर्णांकer;
	data_length = (buffer_length < source_desc->buffer.length ?
		       buffer_length : source_desc->buffer.length);
	स_नकल(buffer, source_desc->buffer.poपूर्णांकer, data_length);

	/* Lock entire transaction अगर requested */

	acpi_ex_acquire_global_lock(obj_desc->common_field.field_flags);

	/*
	 * Perक्रमm the ग_लिखो (वापसs status and perhaps data in the
	 * same buffer)
	 */
	status = acpi_ex_access_region(obj_desc, 0, (u64 *)buffer, function);
	acpi_ex_release_global_lock(obj_desc->common_field.field_flags);

	*वापस_buffer = buffer_desc;
	वापस_ACPI_STATUS(status);
पूर्ण
