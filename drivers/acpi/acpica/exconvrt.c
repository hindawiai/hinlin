<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exconvrt - Object conversion routines
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acinterp.h"
#समावेश "amlcode.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exconvrt")

/* Local prototypes */
अटल u32
acpi_ex_convert_to_ascii(u64 पूर्णांकeger, u16 base, u8 *string, u8 max_length);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_convert_to_पूर्णांकeger
 *
 * PARAMETERS:  obj_desc            - Object to be converted. Must be an
 *                                    Integer, Buffer, or String
 *              result_desc         - Where the new Integer object is वापसed
 *              implicit_conversion - Used क्रम string conversion
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert an ACPI Object to an पूर्णांकeger.
 *
 ******************************************************************************/

acpi_status
acpi_ex_convert_to_पूर्णांकeger(जोड़ acpi_opeअक्रम_object *obj_desc,
			   जोड़ acpi_opeअक्रम_object **result_desc,
			   u32 implicit_conversion)
अणु
	जोड़ acpi_opeअक्रम_object *वापस_desc;
	u8 *poपूर्णांकer;
	u64 result;
	u32 i;
	u32 count;

	ACPI_FUNCTION_TRACE_PTR(ex_convert_to_पूर्णांकeger, obj_desc);

	चयन (obj_desc->common.type) अणु
	हाल ACPI_TYPE_INTEGER:

		/* No conversion necessary */

		*result_desc = obj_desc;
		वापस_ACPI_STATUS(AE_OK);

	हाल ACPI_TYPE_BUFFER:
	हाल ACPI_TYPE_STRING:

		/* Note: Takes advantage of common buffer/string fields */

		poपूर्णांकer = obj_desc->buffer.poपूर्णांकer;
		count = obj_desc->buffer.length;
		अवरोध;

	शेष:

		वापस_ACPI_STATUS(AE_TYPE);
	पूर्ण

	/*
	 * Convert the buffer/string to an पूर्णांकeger. Note that both buffers and
	 * strings are treated as raw data - we करोn't convert ascii to hex क्रम
	 * strings.
	 *
	 * There are two terminating conditions क्रम the loop:
	 * 1) The size of an पूर्णांकeger has been reached, or
	 * 2) The end of the buffer or string has been reached
	 */
	result = 0;

	/* String conversion is dअगरferent than Buffer conversion */

	चयन (obj_desc->common.type) अणु
	हाल ACPI_TYPE_STRING:
		/*
		 * Convert string to an पूर्णांकeger - क्रम most हालs, the string must be
		 * hexadecimal as per the ACPI specअगरication. The only exception (as
		 * of ACPI 3.0) is that the to_पूर्णांकeger() चालक allows both decimal
		 * and hexadecimal strings (hex prefixed with "0x").
		 *
		 * Explicit conversion is used only by to_पूर्णांकeger.
		 * All other string-to-पूर्णांकeger conversions are implicit conversions.
		 */
		अगर (implicit_conversion) अणु
			result =
			    acpi_ut_implicit_म_से_अदीर्घ64(ACPI_CAST_PTR
						       (अक्षर, poपूर्णांकer));
		पूर्ण अन्यथा अणु
			result =
			    acpi_ut_explicit_म_से_अदीर्घ64(ACPI_CAST_PTR
						       (अक्षर, poपूर्णांकer));
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		/* Check क्रम zero-length buffer */

		अगर (!count) अणु
			वापस_ACPI_STATUS(AE_AML_BUFFER_LIMIT);
		पूर्ण

		/* Transfer no more than an पूर्णांकeger's worth of data */

		अगर (count > acpi_gbl_पूर्णांकeger_byte_width) अणु
			count = acpi_gbl_पूर्णांकeger_byte_width;
		पूर्ण

		/*
		 * Convert buffer to an पूर्णांकeger - we simply grab enough raw data
		 * from the buffer to fill an पूर्णांकeger
		 */
		क्रम (i = 0; i < count; i++) अणु
			/*
			 * Get next byte and shअगरt it पूर्णांकo the Result.
			 * Little endian is used, meaning that the first byte of the buffer
			 * is the LSB of the पूर्णांकeger
			 */
			result |= (((u64) poपूर्णांकer[i]) << (i * 8));
		पूर्ण
		अवरोध;

	शेष:

		/* No other types can get here */

		अवरोध;
	पूर्ण

	/* Create a new पूर्णांकeger */

	वापस_desc = acpi_ut_create_पूर्णांकeger_object(result);
	अगर (!वापस_desc) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Converted value: %8.8X%8.8X\n",
			  ACPI_FORMAT_UINT64(result)));

	/* Save the Result */

	(व्योम)acpi_ex_truncate_क्रम32bit_table(वापस_desc);
	*result_desc = वापस_desc;
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_convert_to_buffer
 *
 * PARAMETERS:  obj_desc        - Object to be converted. Must be an
 *                                Integer, Buffer, or String
 *              result_desc     - Where the new buffer object is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert an ACPI Object to a Buffer
 *
 ******************************************************************************/

acpi_status
acpi_ex_convert_to_buffer(जोड़ acpi_opeअक्रम_object *obj_desc,
			  जोड़ acpi_opeअक्रम_object **result_desc)
अणु
	जोड़ acpi_opeअक्रम_object *वापस_desc;
	u8 *new_buf;

	ACPI_FUNCTION_TRACE_PTR(ex_convert_to_buffer, obj_desc);

	चयन (obj_desc->common.type) अणु
	हाल ACPI_TYPE_BUFFER:

		/* No conversion necessary */

		*result_desc = obj_desc;
		वापस_ACPI_STATUS(AE_OK);

	हाल ACPI_TYPE_INTEGER:
		/*
		 * Create a new Buffer object.
		 * Need enough space क्रम one पूर्णांकeger
		 */
		वापस_desc =
		    acpi_ut_create_buffer_object(acpi_gbl_पूर्णांकeger_byte_width);
		अगर (!वापस_desc) अणु
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण

		/* Copy the पूर्णांकeger to the buffer, LSB first */

		new_buf = वापस_desc->buffer.poपूर्णांकer;
		स_नकल(new_buf, &obj_desc->पूर्णांकeger.value,
		       acpi_gbl_पूर्णांकeger_byte_width);
		अवरोध;

	हाल ACPI_TYPE_STRING:
		/*
		 * Create a new Buffer object
		 * Size will be the string length
		 *
		 * NOTE: Add one to the string length to include the null terminator.
		 * The ACPI spec is unclear on this subject, but there is existing
		 * ASL/AML code that depends on the null being transferred to the new
		 * buffer.
		 */
		वापस_desc = acpi_ut_create_buffer_object((acpi_size)
							   obj_desc->string.
							   length + 1);
		अगर (!वापस_desc) अणु
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण

		/* Copy the string to the buffer */

		new_buf = वापस_desc->buffer.poपूर्णांकer;
		म_नकलन((अक्षर *)new_buf, (अक्षर *)obj_desc->string.poपूर्णांकer,
			obj_desc->string.length);
		अवरोध;

	शेष:

		वापस_ACPI_STATUS(AE_TYPE);
	पूर्ण

	/* Mark buffer initialized */

	वापस_desc->common.flags |= AOPOBJ_DATA_VALID;
	*result_desc = वापस_desc;
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_convert_to_ascii
 *
 * PARAMETERS:  पूर्णांकeger         - Value to be converted
 *              base            - ACPI_STRING_DECIMAL or ACPI_STRING_HEX
 *              string          - Where the string is वापसed
 *              data_width      - Size of data item to be converted, in bytes
 *
 * RETURN:      Actual string length
 *
 * DESCRIPTION: Convert an ACPI Integer to a hex or decimal string
 *
 ******************************************************************************/

अटल u32
acpi_ex_convert_to_ascii(u64 पूर्णांकeger, u16 base, u8 *string, u8 data_width)
अणु
	u64 digit;
	u32 i;
	u32 j;
	u32 k = 0;
	u32 hex_length;
	u32 decimal_length;
	u32 reमुख्यder;
	u8 supress_zeros;

	ACPI_FUNCTION_ENTRY();

	चयन (base) अणु
	हाल 10:

		/* Setup max length क्रम the decimal number */

		चयन (data_width) अणु
		हाल 1:

			decimal_length = ACPI_MAX8_DECIMAL_DIGITS;
			अवरोध;

		हाल 4:

			decimal_length = ACPI_MAX32_DECIMAL_DIGITS;
			अवरोध;

		हाल 8:
		शेष:

			decimal_length = ACPI_MAX64_DECIMAL_DIGITS;
			अवरोध;
		पूर्ण

		supress_zeros = TRUE;	/* No leading zeros */
		reमुख्यder = 0;

		क्रम (i = decimal_length; i > 0; i--) अणु

			/* Divide by nth factor of 10 */

			digit = पूर्णांकeger;
			क्रम (j = 0; j < i; j++) अणु
				(व्योम)acpi_ut_लघु_भागide(digit, 10, &digit,
							   &reमुख्यder);
			पूर्ण

			/* Handle leading zeros */

			अगर (reमुख्यder != 0) अणु
				supress_zeros = FALSE;
			पूर्ण

			अगर (!supress_zeros) अणु
				string[k] = (u8) (ACPI_ASCII_ZERO + reमुख्यder);
				k++;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल 16:

		/* hex_length: 2 ascii hex अक्षरs per data byte */

		hex_length = (data_width * 2);
		क्रम (i = 0, j = (hex_length - 1); i < hex_length; i++, j--) अणु

			/* Get one hex digit, most signअगरicant digits first */

			string[k] = (u8)
			    acpi_ut_hex_to_ascii_अक्षर(पूर्णांकeger, ACPI_MUL_4(j));
			k++;
		पूर्ण
		अवरोध;

	शेष:
		वापस (0);
	पूर्ण

	/*
	 * Since leading zeros are suppressed, we must check क्रम the हाल where
	 * the पूर्णांकeger equals 0
	 *
	 * Finally, null terminate the string and वापस the length
	 */
	अगर (!k) अणु
		string[0] = ACPI_ASCII_ZERO;
		k = 1;
	पूर्ण

	string[k] = 0;
	वापस ((u32) k);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_convert_to_string
 *
 * PARAMETERS:  obj_desc        - Object to be converted. Must be an
 *                                Integer, Buffer, or String
 *              result_desc     - Where the string object is वापसed
 *              type            - String flags (base and conversion type)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert an ACPI Object to a string. Supports both implicit
 *              and explicit conversions and related rules.
 *
 ******************************************************************************/

acpi_status
acpi_ex_convert_to_string(जोड़ acpi_opeअक्रम_object * obj_desc,
			  जोड़ acpi_opeअक्रम_object ** result_desc, u32 type)
अणु
	जोड़ acpi_opeअक्रम_object *वापस_desc;
	u8 *new_buf;
	u32 i;
	u32 string_length = 0;
	u16 base = 16;
	u8 separator = ',';

	ACPI_FUNCTION_TRACE_PTR(ex_convert_to_string, obj_desc);

	चयन (obj_desc->common.type) अणु
	हाल ACPI_TYPE_STRING:

		/* No conversion necessary */

		*result_desc = obj_desc;
		वापस_ACPI_STATUS(AE_OK);

	हाल ACPI_TYPE_INTEGER:

		चयन (type) अणु
		हाल ACPI_EXPLICIT_CONVERT_DECIMAL:
			/*
			 * From to_decimal_string, पूर्णांकeger source.
			 *
			 * Make room क्रम the maximum decimal number size
			 */
			string_length = ACPI_MAX_DECIMAL_DIGITS;
			base = 10;
			अवरोध;

		शेष:

			/* Two hex string अक्षरacters क्रम each पूर्णांकeger byte */

			string_length = ACPI_MUL_2(acpi_gbl_पूर्णांकeger_byte_width);
			अवरोध;
		पूर्ण

		/*
		 * Create a new String
		 * Need enough space क्रम one ASCII पूर्णांकeger (plus null terminator)
		 */
		वापस_desc =
		    acpi_ut_create_string_object((acpi_size)string_length);
		अगर (!वापस_desc) अणु
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण

		new_buf = वापस_desc->buffer.poपूर्णांकer;

		/* Convert पूर्णांकeger to string */

		string_length =
		    acpi_ex_convert_to_ascii(obj_desc->पूर्णांकeger.value, base,
					     new_buf,
					     acpi_gbl_पूर्णांकeger_byte_width);

		/* Null terminate at the correct place */

		वापस_desc->string.length = string_length;
		new_buf[string_length] = 0;
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		/* Setup string length, base, and separator */

		चयन (type) अणु
		हाल ACPI_EXPLICIT_CONVERT_DECIMAL:	/* Used by to_decimal_string */
			/*
			 * Explicit conversion from the to_decimal_string ASL चालक.
			 *
			 * From ACPI: "If the input is a buffer, it is converted to a
			 * a string of decimal values separated by commas."
			 */
			base = 10;

			/*
			 * Calculate the final string length. Inभागidual string values
			 * are variable length (include separator क्रम each)
			 */
			क्रम (i = 0; i < obj_desc->buffer.length; i++) अणु
				अगर (obj_desc->buffer.poपूर्णांकer[i] >= 100) अणु
					string_length += 4;
				पूर्ण अन्यथा अगर (obj_desc->buffer.poपूर्णांकer[i] >= 10) अणु
					string_length += 3;
				पूर्ण अन्यथा अणु
					string_length += 2;
				पूर्ण
			पूर्ण
			अवरोध;

		हाल ACPI_IMPLICIT_CONVERT_HEX:
			/*
			 * Implicit buffer-to-string conversion
			 *
			 * From the ACPI spec:
			 * "The entire contents of the buffer are converted to a string of
			 * two-अक्षरacter hexadecimal numbers, each separated by a space."
			 *
			 * Each hex number is prefixed with 0x (11/2018)
			 */
			separator = ' ';
			string_length = (obj_desc->buffer.length * 5);
			अवरोध;

		हाल ACPI_EXPLICIT_CONVERT_HEX:
			/*
			 * Explicit conversion from the to_hex_string ASL चालक.
			 *
			 * From ACPI: "If Data is a buffer, it is converted to a string of
			 * hexadecimal values separated by commas."
			 *
			 * Each hex number is prefixed with 0x (11/2018)
			 */
			separator = ',';
			string_length = (obj_desc->buffer.length * 5);
			अवरोध;

		शेष:
			वापस_ACPI_STATUS(AE_BAD_PARAMETER);
		पूर्ण

		/*
		 * Create a new string object and string buffer
		 * (-1 because of extra separator included in string_length from above)
		 * Allow creation of zero-length strings from zero-length buffers.
		 */
		अगर (string_length) अणु
			string_length--;
		पूर्ण

		वापस_desc =
		    acpi_ut_create_string_object((acpi_size)string_length);
		अगर (!वापस_desc) अणु
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण

		new_buf = वापस_desc->buffer.poपूर्णांकer;

		/*
		 * Convert buffer bytes to hex or decimal values
		 * (separated by commas or spaces)
		 */
		क्रम (i = 0; i < obj_desc->buffer.length; i++) अणु
			अगर (base == 16) अणु

				/* Emit 0x prefix क्रम explicit/implicit hex conversion */

				*new_buf++ = '0';
				*new_buf++ = 'x';
			पूर्ण

			new_buf += acpi_ex_convert_to_ascii((u64) obj_desc->
							    buffer.poपूर्णांकer[i],
							    base, new_buf, 1);

			/* Each digit is separated by either a comma or space */

			*new_buf++ = separator;
		पूर्ण

		/*
		 * Null terminate the string
		 * (overग_लिखोs final comma/space from above)
		 */
		अगर (obj_desc->buffer.length) अणु
			new_buf--;
		पूर्ण
		*new_buf = 0;
		अवरोध;

	शेष:

		वापस_ACPI_STATUS(AE_TYPE);
	पूर्ण

	*result_desc = वापस_desc;
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_convert_to_target_type
 *
 * PARAMETERS:  destination_type    - Current type of the destination
 *              source_desc         - Source object to be converted.
 *              result_desc         - Where the converted object is वापसed
 *              walk_state          - Current method state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Implements "implicit conversion" rules क्रम storing an object.
 *
 ******************************************************************************/

acpi_status
acpi_ex_convert_to_target_type(acpi_object_type destination_type,
			       जोड़ acpi_opeअक्रम_object *source_desc,
			       जोड़ acpi_opeअक्रम_object **result_desc,
			       काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ex_convert_to_target_type);

	/* Default behavior */

	*result_desc = source_desc;

	/*
	 * If required by the target,
	 * perक्रमm implicit conversion on the source beक्रमe we store it.
	 */
	चयन (GET_CURRENT_ARG_TYPE(walk_state->op_info->runसमय_args)) अणु
	हाल ARGI_SIMPLE_TARGET:
	हाल ARGI_FIXED_TARGET:
	हाल ARGI_INTEGER_REF:	/* Handles Increment, Decrement हालs */

		चयन (destination_type) अणु
		हाल ACPI_TYPE_LOCAL_REGION_FIELD:
			/*
			 * Named field can always handle conversions
			 */
			अवरोध;

		शेष:

			/* No conversion allowed क्रम these types */

			अगर (destination_type != source_desc->common.type) अणु
				ACPI_DEBUG_PRINT((ACPI_DB_INFO,
						  "Explicit operator, will store (%s) over existing type (%s)\n",
						  acpi_ut_get_object_type_name
						  (source_desc),
						  acpi_ut_get_type_name
						  (destination_type)));
				status = AE_TYPE;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल ARGI_TARGETREF:
	हाल ARGI_STORE_TARGET:

		चयन (destination_type) अणु
		हाल ACPI_TYPE_INTEGER:
		हाल ACPI_TYPE_BUFFER_FIELD:
		हाल ACPI_TYPE_LOCAL_BANK_FIELD:
		हाल ACPI_TYPE_LOCAL_INDEX_FIELD:
			/*
			 * These types require an Integer opeअक्रम. We can convert
			 * a Buffer or a String to an Integer अगर necessary.
			 */
			status =
			    acpi_ex_convert_to_पूर्णांकeger(source_desc, result_desc,
						       ACPI_IMPLICIT_CONVERSION);
			अवरोध;

		हाल ACPI_TYPE_STRING:
			/*
			 * The opeअक्रम must be a String. We can convert an
			 * Integer or Buffer अगर necessary
			 */
			status =
			    acpi_ex_convert_to_string(source_desc, result_desc,
						      ACPI_IMPLICIT_CONVERT_HEX);
			अवरोध;

		हाल ACPI_TYPE_BUFFER:
			/*
			 * The opeअक्रम must be a Buffer. We can convert an
			 * Integer or String अगर necessary
			 */
			status =
			    acpi_ex_convert_to_buffer(source_desc, result_desc);
			अवरोध;

		शेष:

			ACPI_ERROR((AE_INFO,
				    "Bad destination type during conversion: 0x%X",
				    destination_type));
			status = AE_AML_INTERNAL;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल ARGI_REFERENCE:
		/*
		 * create_xxxx_field हालs - we are storing the field object पूर्णांकo the name
		 */
		अवरोध;

	शेष:

		ACPI_ERROR((AE_INFO,
			    "Unknown Target type ID 0x%X AmlOpcode 0x%X DestType %s",
			    GET_CURRENT_ARG_TYPE(walk_state->op_info->
						 runसमय_args),
			    walk_state->opcode,
			    acpi_ut_get_type_name(destination_type)));
		status = AE_AML_INTERNAL;
	पूर्ण

	/*
	 * Source-to-Target conversion semantics:
	 *
	 * If conversion to the target type cannot be perक्रमmed, then simply
	 * overग_लिखो the target with the new object and type.
	 */
	अगर (status == AE_TYPE) अणु
		status = AE_OK;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण
