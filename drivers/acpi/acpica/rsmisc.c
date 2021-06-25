<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: rsmisc - Miscellaneous resource descriptors
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acresrc.h"

#घोषणा _COMPONENT          ACPI_RESOURCES
ACPI_MODULE_NAME("rsmisc")
#घोषणा INIT_RESOURCE_TYPE(i)       i->resource_offset
#घोषणा INIT_RESOURCE_LENGTH(i)     i->aml_offset
#घोषणा INIT_TABLE_LENGTH(i)        i->value
#घोषणा COMPARE_OPCODE(i)           i->resource_offset
#घोषणा COMPARE_TARGET(i)           i->aml_offset
#घोषणा COMPARE_VALUE(i)            i->value
/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_convert_aml_to_resource
 *
 * PARAMETERS:  resource            - Poपूर्णांकer to the resource descriptor
 *              aml                 - Where the AML descriptor is वापसed
 *              info                - Poपूर्णांकer to appropriate conversion table
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert an बाह्यal AML resource descriptor to the corresponding
 *              पूर्णांकernal resource descriptor
 *
 ******************************************************************************/
acpi_status
acpi_rs_convert_aml_to_resource(काष्ठा acpi_resource *resource,
				जोड़ aml_resource *aml,
				काष्ठा acpi_rsconvert_info *info)
अणु
	acpi_rs_length aml_resource_length;
	व्योम *source;
	व्योम *destination;
	अक्षर *target;
	u8 count;
	u8 flags_mode = FALSE;
	u16 item_count = 0;
	u16 temp16 = 0;

	ACPI_FUNCTION_TRACE(rs_convert_aml_to_resource);

	अगर (!info) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	अगर (((acpi_size)resource) & 0x3) अणु

		/* Each पूर्णांकernal resource काष्ठा is expected to be 32-bit aligned */

		ACPI_WARNING((AE_INFO,
			      "Misaligned resource pointer (get): %p Type 0x%2.2X Length %u",
			      resource, resource->type, resource->length));
	पूर्ण

	/* Extract the resource Length field (करोes not include header length) */

	aml_resource_length = acpi_ut_get_resource_length(aml);

	/*
	 * First table entry must be ACPI_RSC_INITxxx and must contain the
	 * table length (# of table entries)
	 */
	count = INIT_TABLE_LENGTH(info);
	जबतक (count) अणु
		target = शून्य;

		/*
		 * Source is the बाह्यal AML byte stream buffer,
		 * destination is the पूर्णांकernal resource descriptor
		 */
		source = ACPI_ADD_PTR(व्योम, aml, info->aml_offset);
		destination =
		    ACPI_ADD_PTR(व्योम, resource, info->resource_offset);

		चयन (info->opcode) अणु
		हाल ACPI_RSC_INITGET:
			/*
			 * Get the resource type and the initial (minimum) length
			 */
			स_रखो(resource, 0, INIT_RESOURCE_LENGTH(info));
			resource->type = INIT_RESOURCE_TYPE(info);
			resource->length = INIT_RESOURCE_LENGTH(info);
			अवरोध;

		हाल ACPI_RSC_INITSET:
			अवरोध;

		हाल ACPI_RSC_FLAGINIT:

			flags_mode = TRUE;
			अवरोध;

		हाल ACPI_RSC_1BITFLAG:
			/*
			 * Mask and shअगरt the flag bit
			 */
			ACPI_SET8(destination,
				  ((ACPI_GET8(source) >> info->value) & 0x01));
			अवरोध;

		हाल ACPI_RSC_2BITFLAG:
			/*
			 * Mask and shअगरt the flag bits
			 */
			ACPI_SET8(destination,
				  ((ACPI_GET8(source) >> info->value) & 0x03));
			अवरोध;

		हाल ACPI_RSC_3BITFLAG:
			/*
			 * Mask and shअगरt the flag bits
			 */
			ACPI_SET8(destination,
				  ((ACPI_GET8(source) >> info->value) & 0x07));
			अवरोध;

		हाल ACPI_RSC_6BITFLAG:
			/*
			 * Mask and shअगरt the flag bits
			 */
			ACPI_SET8(destination,
				  ((ACPI_GET8(source) >> info->value) & 0x3F));
			अवरोध;

		हाल ACPI_RSC_COUNT:

			item_count = ACPI_GET8(source);
			ACPI_SET8(destination, item_count);

			resource->length = resource->length +
			    (info->value * (item_count - 1));
			अवरोध;

		हाल ACPI_RSC_COUNT16:

			item_count = aml_resource_length;
			ACPI_SET16(destination, item_count);

			resource->length = resource->length +
			    (info->value * (item_count - 1));
			अवरोध;

		हाल ACPI_RSC_COUNT_GPIO_PIN:

			target = ACPI_ADD_PTR(व्योम, aml, info->value);
			item_count = ACPI_GET16(target) - ACPI_GET16(source);

			resource->length = resource->length + item_count;
			item_count = item_count / 2;
			ACPI_SET16(destination, item_count);
			अवरोध;

		हाल ACPI_RSC_COUNT_GPIO_VEN:

			item_count = ACPI_GET8(source);
			ACPI_SET8(destination, item_count);

			resource->length =
			    resource->length + (info->value * item_count);
			अवरोध;

		हाल ACPI_RSC_COUNT_GPIO_RES:
			/*
			 * Venकरोr data is optional (length/offset may both be zero)
			 * Examine venकरोr data length field first
			 */
			target = ACPI_ADD_PTR(व्योम, aml, (info->value + 2));
			अगर (ACPI_GET16(target)) अणु

				/* Use venकरोr offset to get resource source length */

				target = ACPI_ADD_PTR(व्योम, aml, info->value);
				item_count =
				    ACPI_GET16(target) - ACPI_GET16(source);
			पूर्ण अन्यथा अणु
				/* No venकरोr data to worry about */

				item_count = aml->large_header.resource_length +
				    माप(काष्ठा aml_resource_large_header) -
				    ACPI_GET16(source);
			पूर्ण

			resource->length = resource->length + item_count;
			ACPI_SET16(destination, item_count);
			अवरोध;

		हाल ACPI_RSC_COUNT_SERIAL_VEN:

			item_count = ACPI_GET16(source) - info->value;

			resource->length = resource->length + item_count;
			ACPI_SET16(destination, item_count);
			अवरोध;

		हाल ACPI_RSC_COUNT_SERIAL_RES:

			item_count = (aml_resource_length +
				      माप(काष्ठा aml_resource_large_header))
			    - ACPI_GET16(source) - info->value;

			resource->length = resource->length + item_count;
			ACPI_SET16(destination, item_count);
			अवरोध;

		हाल ACPI_RSC_LENGTH:

			resource->length = resource->length + info->value;
			अवरोध;

		हाल ACPI_RSC_MOVE8:
		हाल ACPI_RSC_MOVE16:
		हाल ACPI_RSC_MOVE32:
		हाल ACPI_RSC_MOVE64:
			/*
			 * Raw data move. Use the Info value field unless item_count has
			 * been previously initialized via a COUNT opcode
			 */
			अगर (info->value) अणु
				item_count = info->value;
			पूर्ण
			acpi_rs_move_data(destination, source, item_count,
					  info->opcode);
			अवरोध;

		हाल ACPI_RSC_MOVE_GPIO_PIN:

			/* Generate and set the PIN data poपूर्णांकer */

			target = (अक्षर *)ACPI_ADD_PTR(व्योम, resource,
						      (resource->length -
						       item_count * 2));
			*(u16 **)destination = ACPI_CAST_PTR(u16, target);

			/* Copy the PIN data */

			source = ACPI_ADD_PTR(व्योम, aml, ACPI_GET16(source));
			acpi_rs_move_data(target, source, item_count,
					  info->opcode);
			अवरोध;

		हाल ACPI_RSC_MOVE_GPIO_RES:

			/* Generate and set the resource_source string poपूर्णांकer */

			target = (अक्षर *)ACPI_ADD_PTR(व्योम, resource,
						      (resource->length -
						       item_count));
			*(u8 **)destination = ACPI_CAST_PTR(u8, target);

			/* Copy the resource_source string */

			source = ACPI_ADD_PTR(व्योम, aml, ACPI_GET16(source));
			acpi_rs_move_data(target, source, item_count,
					  info->opcode);
			अवरोध;

		हाल ACPI_RSC_MOVE_SERIAL_VEN:

			/* Generate and set the Venकरोr Data poपूर्णांकer */

			target = (अक्षर *)ACPI_ADD_PTR(व्योम, resource,
						      (resource->length -
						       item_count));
			*(u8 **)destination = ACPI_CAST_PTR(u8, target);

			/* Copy the Venकरोr Data */

			source = ACPI_ADD_PTR(व्योम, aml, info->value);
			acpi_rs_move_data(target, source, item_count,
					  info->opcode);
			अवरोध;

		हाल ACPI_RSC_MOVE_SERIAL_RES:

			/* Generate and set the resource_source string poपूर्णांकer */

			target = (अक्षर *)ACPI_ADD_PTR(व्योम, resource,
						      (resource->length -
						       item_count));
			*(u8 **)destination = ACPI_CAST_PTR(u8, target);

			/* Copy the resource_source string */

			source =
			    ACPI_ADD_PTR(व्योम, aml,
					 (ACPI_GET16(source) + info->value));
			acpi_rs_move_data(target, source, item_count,
					  info->opcode);
			अवरोध;

		हाल ACPI_RSC_SET8:

			स_रखो(destination, info->aml_offset, info->value);
			अवरोध;

		हाल ACPI_RSC_DATA8:

			target = ACPI_ADD_PTR(अक्षर, resource, info->value);
			स_नकल(destination, source, ACPI_GET16(target));
			अवरोध;

		हाल ACPI_RSC_ADDRESS:
			/*
			 * Common handler क्रम address descriptor flags
			 */
			अगर (!acpi_rs_get_address_common(resource, aml)) अणु
				वापस_ACPI_STATUS
				    (AE_AML_INVALID_RESOURCE_TYPE);
			पूर्ण
			अवरोध;

		हाल ACPI_RSC_SOURCE:
			/*
			 * Optional resource_source (Index and String)
			 */
			resource->length +=
			    acpi_rs_get_resource_source(aml_resource_length,
							info->value,
							destination, aml, शून्य);
			अवरोध;

		हाल ACPI_RSC_SOURCEX:
			/*
			 * Optional resource_source (Index and String). This is the more
			 * complicated हाल used by the Interrupt() macro
			 */
			target = ACPI_ADD_PTR(अक्षर, resource,
					      info->aml_offset +
					      (item_count * 4));

			resource->length +=
			    acpi_rs_get_resource_source(aml_resource_length,
							(acpi_rs_length)
							(((item_count -
							   1) * माप(u32)) +
							 info->value),
							destination, aml,
							target);
			अवरोध;

		हाल ACPI_RSC_BITMASK:
			/*
			 * 8-bit encoded biपंचांगask (DMA macro)
			 */
			item_count =
			    acpi_rs_decode_biपंचांगask(ACPI_GET8(source),
						   destination);
			अगर (item_count) अणु
				resource->length += (item_count - 1);
			पूर्ण

			target = ACPI_ADD_PTR(अक्षर, resource, info->value);
			ACPI_SET8(target, item_count);
			अवरोध;

		हाल ACPI_RSC_BITMASK16:
			/*
			 * 16-bit encoded biपंचांगask (IRQ macro)
			 */
			ACPI_MOVE_16_TO_16(&temp16, source);

			item_count =
			    acpi_rs_decode_biपंचांगask(temp16, destination);
			अगर (item_count) अणु
				resource->length += (item_count - 1);
			पूर्ण

			target = ACPI_ADD_PTR(अक्षर, resource, info->value);
			ACPI_SET8(target, item_count);
			अवरोध;

		हाल ACPI_RSC_EXIT_NE:
			/*
			 * control - Exit conversion अगर not equal
			 */
			चयन (info->resource_offset) अणु
			हाल ACPI_RSC_COMPARE_AML_LENGTH:

				अगर (aml_resource_length != info->value) अणु
					जाओ निकास;
				पूर्ण
				अवरोध;

			हाल ACPI_RSC_COMPARE_VALUE:

				अगर (ACPI_GET8(source) != info->value) अणु
					जाओ निकास;
				पूर्ण
				अवरोध;

			शेष:

				ACPI_ERROR((AE_INFO,
					    "Invalid conversion sub-opcode"));
				वापस_ACPI_STATUS(AE_BAD_PARAMETER);
			पूर्ण
			अवरोध;

		शेष:

			ACPI_ERROR((AE_INFO, "Invalid conversion opcode"));
			वापस_ACPI_STATUS(AE_BAD_PARAMETER);
		पूर्ण

		count--;
		info++;
	पूर्ण

निकास:
	अगर (!flags_mode) अणु

		/* Round the resource काष्ठा length up to the next boundary (32 or 64) */

		resource->length = (u32)
		    ACPI_ROUND_UP_TO_NATIVE_WORD(resource->length);
	पूर्ण
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_convert_resource_to_aml
 *
 * PARAMETERS:  resource            - Poपूर्णांकer to the resource descriptor
 *              aml                 - Where the AML descriptor is वापसed
 *              info                - Poपूर्णांकer to appropriate conversion table
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert an पूर्णांकernal resource descriptor to the corresponding
 *              बाह्यal AML resource descriptor.
 *
 ******************************************************************************/

acpi_status
acpi_rs_convert_resource_to_aml(काष्ठा acpi_resource *resource,
				जोड़ aml_resource *aml,
				काष्ठा acpi_rsconvert_info *info)
अणु
	व्योम *source = शून्य;
	व्योम *destination;
	अक्षर *target;
	acpi_rsdesc_size aml_length = 0;
	u8 count;
	u16 temp16 = 0;
	u16 item_count = 0;

	ACPI_FUNCTION_TRACE(rs_convert_resource_to_aml);

	अगर (!info) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/*
	 * First table entry must be ACPI_RSC_INITxxx and must contain the
	 * table length (# of table entries)
	 */
	count = INIT_TABLE_LENGTH(info);

	जबतक (count) अणु
		/*
		 * Source is the पूर्णांकernal resource descriptor,
		 * destination is the बाह्यal AML byte stream buffer
		 */
		source = ACPI_ADD_PTR(व्योम, resource, info->resource_offset);
		destination = ACPI_ADD_PTR(व्योम, aml, info->aml_offset);

		चयन (info->opcode) अणु
		हाल ACPI_RSC_INITSET:

			स_रखो(aml, 0, INIT_RESOURCE_LENGTH(info));
			aml_length = INIT_RESOURCE_LENGTH(info);
			acpi_rs_set_resource_header(INIT_RESOURCE_TYPE(info),
						    aml_length, aml);
			अवरोध;

		हाल ACPI_RSC_INITGET:
			अवरोध;

		हाल ACPI_RSC_FLAGINIT:
			/*
			 * Clear the flag byte
			 */
			ACPI_SET8(destination, 0);
			अवरोध;

		हाल ACPI_RSC_1BITFLAG:
			/*
			 * Mask and shअगरt the flag bit
			 */
			ACPI_SET_BIT(*ACPI_CAST8(destination), (u8)
				     ((ACPI_GET8(source) & 0x01) << info->
				      value));
			अवरोध;

		हाल ACPI_RSC_2BITFLAG:
			/*
			 * Mask and shअगरt the flag bits
			 */
			ACPI_SET_BIT(*ACPI_CAST8(destination), (u8)
				     ((ACPI_GET8(source) & 0x03) << info->
				      value));
			अवरोध;

		हाल ACPI_RSC_3BITFLAG:
			/*
			 * Mask and shअगरt the flag bits
			 */
			ACPI_SET_BIT(*ACPI_CAST8(destination), (u8)
				     ((ACPI_GET8(source) & 0x07) << info->
				      value));
			अवरोध;

		हाल ACPI_RSC_6BITFLAG:
			/*
			 * Mask and shअगरt the flag bits
			 */
			ACPI_SET_BIT(*ACPI_CAST8(destination), (u8)
				     ((ACPI_GET8(source) & 0x3F) << info->
				      value));
			अवरोध;

		हाल ACPI_RSC_COUNT:

			item_count = ACPI_GET8(source);
			ACPI_SET8(destination, item_count);

			aml_length = (u16)
			    (aml_length + (info->value * (item_count - 1)));
			अवरोध;

		हाल ACPI_RSC_COUNT16:

			item_count = ACPI_GET16(source);
			aml_length = (u16) (aml_length + item_count);
			acpi_rs_set_resource_length(aml_length, aml);
			अवरोध;

		हाल ACPI_RSC_COUNT_GPIO_PIN:

			item_count = ACPI_GET16(source);
			ACPI_SET16(destination, aml_length);

			aml_length = (u16)(aml_length + item_count * 2);
			target = ACPI_ADD_PTR(व्योम, aml, info->value);
			ACPI_SET16(target, aml_length);
			acpi_rs_set_resource_length(aml_length, aml);
			अवरोध;

		हाल ACPI_RSC_COUNT_GPIO_VEN:

			item_count = ACPI_GET16(source);
			ACPI_SET16(destination, item_count);

			aml_length =
			    (u16)(aml_length + (info->value * item_count));
			acpi_rs_set_resource_length(aml_length, aml);
			अवरोध;

		हाल ACPI_RSC_COUNT_GPIO_RES:

			/* Set resource source string length */

			item_count = ACPI_GET16(source);
			ACPI_SET16(destination, aml_length);

			/* Compute offset क्रम the Venकरोr Data */

			aml_length = (u16)(aml_length + item_count);
			target = ACPI_ADD_PTR(व्योम, aml, info->value);

			/* Set venकरोr offset only अगर there is venकरोr data */

			ACPI_SET16(target, aml_length);

			acpi_rs_set_resource_length(aml_length, aml);
			अवरोध;

		हाल ACPI_RSC_COUNT_SERIAL_VEN:

			item_count = ACPI_GET16(source);
			ACPI_SET16(destination, item_count + info->value);
			aml_length = (u16)(aml_length + item_count);
			acpi_rs_set_resource_length(aml_length, aml);
			अवरोध;

		हाल ACPI_RSC_COUNT_SERIAL_RES:

			item_count = ACPI_GET16(source);
			aml_length = (u16)(aml_length + item_count);
			acpi_rs_set_resource_length(aml_length, aml);
			अवरोध;

		हाल ACPI_RSC_LENGTH:

			acpi_rs_set_resource_length(info->value, aml);
			अवरोध;

		हाल ACPI_RSC_MOVE8:
		हाल ACPI_RSC_MOVE16:
		हाल ACPI_RSC_MOVE32:
		हाल ACPI_RSC_MOVE64:

			अगर (info->value) अणु
				item_count = info->value;
			पूर्ण
			acpi_rs_move_data(destination, source, item_count,
					  info->opcode);
			अवरोध;

		हाल ACPI_RSC_MOVE_GPIO_PIN:

			destination = (अक्षर *)ACPI_ADD_PTR(व्योम, aml,
							   ACPI_GET16
							   (destination));
			source = *(u16 **)source;
			acpi_rs_move_data(destination, source, item_count,
					  info->opcode);
			अवरोध;

		हाल ACPI_RSC_MOVE_GPIO_RES:

			/* Used क्रम both resource_source string and venकरोr_data */

			destination = (अक्षर *)ACPI_ADD_PTR(व्योम, aml,
							   ACPI_GET16
							   (destination));
			source = *(u8 **)source;
			acpi_rs_move_data(destination, source, item_count,
					  info->opcode);
			अवरोध;

		हाल ACPI_RSC_MOVE_SERIAL_VEN:

			destination = (अक्षर *)ACPI_ADD_PTR(व्योम, aml,
							   (aml_length -
							    item_count));
			source = *(u8 **)source;
			acpi_rs_move_data(destination, source, item_count,
					  info->opcode);
			अवरोध;

		हाल ACPI_RSC_MOVE_SERIAL_RES:

			destination = (अक्षर *)ACPI_ADD_PTR(व्योम, aml,
							   (aml_length -
							    item_count));
			source = *(u8 **)source;
			acpi_rs_move_data(destination, source, item_count,
					  info->opcode);
			अवरोध;

		हाल ACPI_RSC_ADDRESS:

			/* Set the Resource Type, General Flags, and Type-Specअगरic Flags */

			acpi_rs_set_address_common(aml, resource);
			अवरोध;

		हाल ACPI_RSC_SOURCEX:
			/*
			 * Optional resource_source (Index and String)
			 */
			aml_length =
			    acpi_rs_set_resource_source(aml,
							(acpi_rs_length)
							aml_length, source);
			acpi_rs_set_resource_length(aml_length, aml);
			अवरोध;

		हाल ACPI_RSC_SOURCE:
			/*
			 * Optional resource_source (Index and String). This is the more
			 * complicated हाल used by the Interrupt() macro
			 */
			aml_length =
			    acpi_rs_set_resource_source(aml, info->value,
							source);
			acpi_rs_set_resource_length(aml_length, aml);
			अवरोध;

		हाल ACPI_RSC_BITMASK:
			/*
			 * 8-bit encoded biपंचांगask (DMA macro)
			 */
			ACPI_SET8(destination,
				  acpi_rs_encode_biपंचांगask(source,
							 *ACPI_ADD_PTR(u8,
								       resource,
								       info->
								       value)));
			अवरोध;

		हाल ACPI_RSC_BITMASK16:
			/*
			 * 16-bit encoded biपंचांगask (IRQ macro)
			 */
			temp16 =
			    acpi_rs_encode_biपंचांगask(source,
						   *ACPI_ADD_PTR(u8, resource,
								 info->value));
			ACPI_MOVE_16_TO_16(destination, &temp16);
			अवरोध;

		हाल ACPI_RSC_EXIT_LE:
			/*
			 * control - Exit conversion अगर less than or equal
			 */
			अगर (item_count <= info->value) अणु
				जाओ निकास;
			पूर्ण
			अवरोध;

		हाल ACPI_RSC_EXIT_NE:
			/*
			 * control - Exit conversion अगर not equal
			 */
			चयन (COMPARE_OPCODE(info)) अणु
			हाल ACPI_RSC_COMPARE_VALUE:

				अगर (*ACPI_ADD_PTR(u8, resource,
						  COMPARE_TARGET(info)) !=
				    COMPARE_VALUE(info)) अणु
					जाओ निकास;
				पूर्ण
				अवरोध;

			शेष:

				ACPI_ERROR((AE_INFO,
					    "Invalid conversion sub-opcode"));
				वापस_ACPI_STATUS(AE_BAD_PARAMETER);
			पूर्ण
			अवरोध;

		हाल ACPI_RSC_EXIT_EQ:
			/*
			 * control - Exit conversion अगर equal
			 */
			अगर (*ACPI_ADD_PTR(u8, resource,
					  COMPARE_TARGET(info)) ==
			    COMPARE_VALUE(info)) अणु
				जाओ निकास;
			पूर्ण
			अवरोध;

		शेष:

			ACPI_ERROR((AE_INFO, "Invalid conversion opcode"));
			वापस_ACPI_STATUS(AE_BAD_PARAMETER);
		पूर्ण

		count--;
		info++;
	पूर्ण

निकास:
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

#अगर 0
/* Previous resource validations */

अगर (aml->ext_address64.revision_ID != AML_RESOURCE_EXTENDED_ADDRESS_REVISION) अणु
	वापस_ACPI_STATUS(AE_SUPPORT);
पूर्ण

अगर (resource->data.start_dpf.perक्रमmance_robustness >= 3) अणु
	वापस_ACPI_STATUS(AE_AML_BAD_RESOURCE_VALUE);
पूर्ण

अगर (((aml->irq.flags & 0x09) == 0x00) || ((aml->irq.flags & 0x09) == 0x09)) अणु
	/*
	 * Only [active_high, edge_sensitive] or [active_low, level_sensitive]
	 * polarity/trigger पूर्णांकerrupts are allowed (ACPI spec, section
	 * "IRQ Format"), so 0x00 and 0x09 are illegal.
	 */
	ACPI_ERROR((AE_INFO,
		    "Invalid interrupt polarity/trigger in resource list, 0x%X",
		    aml->irq.flags));
	वापस_ACPI_STATUS(AE_BAD_DATA);
पूर्ण

resource->data.extended_irq.पूर्णांकerrupt_count = temp8;
अगर (temp8 < 1) अणु

	/* Must have at least one IRQ */

	वापस_ACPI_STATUS(AE_AML_BAD_RESOURCE_LENGTH);
पूर्ण

अगर (resource->data.dma.transfer == 0x03) अणु
	ACPI_ERROR((AE_INFO, "Invalid DMA.Transfer preference (3)"));
	वापस_ACPI_STATUS(AE_BAD_DATA);
पूर्ण
#पूर्ण_अगर
