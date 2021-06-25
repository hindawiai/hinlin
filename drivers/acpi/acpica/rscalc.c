<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: rscalc - Calculate stream and list lengths
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acresrc.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_RESOURCES
ACPI_MODULE_NAME("rscalc")

/* Local prototypes */
अटल u8 acpi_rs_count_set_bits(u16 bit_field);

अटल acpi_rs_length
acpi_rs_काष्ठा_option_length(काष्ठा acpi_resource_source *resource_source);

अटल u32
acpi_rs_stream_option_length(u32 resource_length, u32 minimum_total_length);

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_count_set_bits
 *
 * PARAMETERS:  bit_field       - Field in which to count bits
 *
 * RETURN:      Number of bits set within the field
 *
 * DESCRIPTION: Count the number of bits set in a resource field. Used क्रम
 *              (Short descriptor) पूर्णांकerrupt and DMA lists.
 *
 ******************************************************************************/

अटल u8 acpi_rs_count_set_bits(u16 bit_field)
अणु
	u8 bits_set;

	ACPI_FUNCTION_ENTRY();

	क्रम (bits_set = 0; bit_field; bits_set++) अणु

		/* Zero the least signअगरicant bit that is set */

		bit_field &= (u16) (bit_field - 1);
	पूर्ण

	वापस (bits_set);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_काष्ठा_option_length
 *
 * PARAMETERS:  resource_source     - Poपूर्णांकer to optional descriptor field
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Common code to handle optional resource_source_index and
 *              resource_source fields in some Large descriptors. Used during
 *              list-to-stream conversion
 *
 ******************************************************************************/

अटल acpi_rs_length
acpi_rs_काष्ठा_option_length(काष्ठा acpi_resource_source *resource_source)
अणु
	ACPI_FUNCTION_ENTRY();

	/*
	 * If the resource_source string is valid, वापस the size of the string
	 * (string_length includes the शून्य terminator) plus the size of the
	 * resource_source_index (1).
	 */
	अगर (resource_source->string_ptr) अणु
		वापस ((acpi_rs_length)(resource_source->string_length + 1));
	पूर्ण

	वापस (0);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_stream_option_length
 *
 * PARAMETERS:  resource_length     - Length from the resource header
 *              minimum_total_length - Minimum length of this resource, beक्रमe
 *                                    any optional fields. Includes header size
 *
 * RETURN:      Length of optional string (0 अगर no string present)
 *
 * DESCRIPTION: Common code to handle optional resource_source_index and
 *              resource_source fields in some Large descriptors. Used during
 *              stream-to-list conversion
 *
 ******************************************************************************/

अटल u32
acpi_rs_stream_option_length(u32 resource_length,
			     u32 minimum_aml_resource_length)
अणु
	u32 string_length = 0;

	ACPI_FUNCTION_ENTRY();

	/*
	 * The resource_source_index and resource_source are optional elements of
	 * some Large-type resource descriptors.
	 */

	/*
	 * If the length of the actual resource descriptor is greater than the
	 * ACPI spec-defined minimum length, it means that a resource_source_index
	 * exists and is followed by a (required) null terminated string. The
	 * string length (including the null terminator) is the resource length
	 * minus the minimum length, minus one byte क्रम the resource_source_index
	 * itself.
	 */
	अगर (resource_length > minimum_aml_resource_length) अणु

		/* Compute the length of the optional string */

		string_length =
		    resource_length - minimum_aml_resource_length - 1;
	पूर्ण

	/*
	 * Round the length up to a multiple of the native word in order to
	 * guarantee that the entire resource descriptor is native word aligned
	 */
	वापस ((u32) ACPI_ROUND_UP_TO_NATIVE_WORD(string_length));
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_get_aml_length
 *
 * PARAMETERS:  resource            - Poपूर्णांकer to the resource linked list
 *              resource_list_size  - Size of the resource linked list
 *              size_needed         - Where the required size is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Takes a linked list of पूर्णांकernal resource descriptors and
 *              calculates the size buffer needed to hold the corresponding
 *              बाह्यal resource byte stream.
 *
 ******************************************************************************/

acpi_status
acpi_rs_get_aml_length(काष्ठा acpi_resource *resource,
		       acpi_size resource_list_size, acpi_size *size_needed)
अणु
	acpi_size aml_size_needed = 0;
	काष्ठा acpi_resource *resource_end;
	acpi_rs_length total_size;

	ACPI_FUNCTION_TRACE(rs_get_aml_length);

	/* Traverse entire list of पूर्णांकernal resource descriptors */

	resource_end =
	    ACPI_ADD_PTR(काष्ठा acpi_resource, resource, resource_list_size);
	जबतक (resource < resource_end) अणु

		/* Validate the descriptor type */

		अगर (resource->type > ACPI_RESOURCE_TYPE_MAX) अणु
			वापस_ACPI_STATUS(AE_AML_INVALID_RESOURCE_TYPE);
		पूर्ण

		/* Sanity check the length. It must not be zero, or we loop क्रमever */

		अगर (!resource->length) अणु
			वापस_ACPI_STATUS(AE_AML_BAD_RESOURCE_LENGTH);
		पूर्ण

		/* Get the base size of the (बाह्यal stream) resource descriptor */

		total_size = acpi_gbl_aml_resource_sizes[resource->type];

		/*
		 * Augment the base size क्रम descriptors with optional and/or
		 * variable-length fields
		 */
		चयन (resource->type) अणु
		हाल ACPI_RESOURCE_TYPE_IRQ:

			/* Length can be 3 or 2 */

			अगर (resource->data.irq.descriptor_length == 2) अणु
				total_size--;
			पूर्ण
			अवरोध;

		हाल ACPI_RESOURCE_TYPE_START_DEPENDENT:

			/* Length can be 1 or 0 */

			अगर (resource->data.irq.descriptor_length == 0) अणु
				total_size--;
			पूर्ण
			अवरोध;

		हाल ACPI_RESOURCE_TYPE_VENDOR:
			/*
			 * Venकरोr Defined Resource:
			 * For a Venकरोr Specअगरic resource, अगर the Length is between 1 and 7
			 * it will be created as a Small Resource data type, otherwise it
			 * is a Large Resource data type.
			 */
			अगर (resource->data.venकरोr.byte_length > 7) अणु

				/* Base size of a Large resource descriptor */

				total_size =
				    माप(काष्ठा aml_resource_large_header);
			पूर्ण

			/* Add the size of the venकरोr-specअगरic data */

			total_size = (acpi_rs_length)
			    (total_size + resource->data.venकरोr.byte_length);
			अवरोध;

		हाल ACPI_RESOURCE_TYPE_END_TAG:
			/*
			 * End Tag:
			 * We are करोne -- वापस the accumulated total size.
			 */
			*size_needed = aml_size_needed + total_size;

			/* Normal निकास */

			वापस_ACPI_STATUS(AE_OK);

		हाल ACPI_RESOURCE_TYPE_ADDRESS16:
			/*
			 * 16-Bit Address Resource:
			 * Add the size of the optional resource_source info
			 */
			total_size = (acpi_rs_length)(total_size +
						      acpi_rs_काष्ठा_option_length
						      (&resource->data.
						       address16.
						       resource_source));
			अवरोध;

		हाल ACPI_RESOURCE_TYPE_ADDRESS32:
			/*
			 * 32-Bit Address Resource:
			 * Add the size of the optional resource_source info
			 */
			total_size = (acpi_rs_length)(total_size +
						      acpi_rs_काष्ठा_option_length
						      (&resource->data.
						       address32.
						       resource_source));
			अवरोध;

		हाल ACPI_RESOURCE_TYPE_ADDRESS64:
			/*
			 * 64-Bit Address Resource:
			 * Add the size of the optional resource_source info
			 */
			total_size = (acpi_rs_length)(total_size +
						      acpi_rs_काष्ठा_option_length
						      (&resource->data.
						       address64.
						       resource_source));
			अवरोध;

		हाल ACPI_RESOURCE_TYPE_EXTENDED_IRQ:
			/*
			 * Extended IRQ Resource:
			 * Add the size of each additional optional पूर्णांकerrupt beyond the
			 * required 1 (4 bytes क्रम each u32 पूर्णांकerrupt number)
			 */
			total_size = (acpi_rs_length)(total_size +
						      ((resource->data.
							extended_irq.
							पूर्णांकerrupt_count -
							1) * 4) +
						      /* Add the size of the optional resource_source info */
						      acpi_rs_काष्ठा_option_length
						      (&resource->data.
						       extended_irq.
						       resource_source));
			अवरोध;

		हाल ACPI_RESOURCE_TYPE_GPIO:

			total_size = (acpi_rs_length)(total_size +
						      (resource->data.gpio.
						       pin_table_length * 2) +
						      resource->data.gpio.
						      resource_source.
						      string_length +
						      resource->data.gpio.
						      venकरोr_length);

			अवरोध;

		हाल ACPI_RESOURCE_TYPE_PIN_FUNCTION:

			total_size = (acpi_rs_length)(total_size +
						      (resource->data.
						       pin_function.
						       pin_table_length * 2) +
						      resource->data.
						      pin_function.
						      resource_source.
						      string_length +
						      resource->data.
						      pin_function.
						      venकरोr_length);

			अवरोध;

		हाल ACPI_RESOURCE_TYPE_SERIAL_BUS:

			total_size =
			    acpi_gbl_aml_resource_serial_bus_sizes[resource->
								   data.
								   common_serial_bus.
								   type];

			total_size = (acpi_rs_length)(total_size +
						      resource->data.
						      i2c_serial_bus.
						      resource_source.
						      string_length +
						      resource->data.
						      i2c_serial_bus.
						      venकरोr_length);

			अवरोध;

		हाल ACPI_RESOURCE_TYPE_PIN_CONFIG:

			total_size = (acpi_rs_length)(total_size +
						      (resource->data.
						       pin_config.
						       pin_table_length * 2) +
						      resource->data.pin_config.
						      resource_source.
						      string_length +
						      resource->data.pin_config.
						      venकरोr_length);

			अवरोध;

		हाल ACPI_RESOURCE_TYPE_PIN_GROUP:

			total_size = (acpi_rs_length)(total_size +
						      (resource->data.pin_group.
						       pin_table_length * 2) +
						      resource->data.pin_group.
						      resource_label.
						      string_length +
						      resource->data.pin_group.
						      venकरोr_length);

			अवरोध;

		हाल ACPI_RESOURCE_TYPE_PIN_GROUP_FUNCTION:

			total_size = (acpi_rs_length)(total_size +
						      resource->data.
						      pin_group_function.
						      resource_source.
						      string_length +
						      resource->data.
						      pin_group_function.
						      resource_source_label.
						      string_length +
						      resource->data.
						      pin_group_function.
						      venकरोr_length);

			अवरोध;

		हाल ACPI_RESOURCE_TYPE_PIN_GROUP_CONFIG:

			total_size = (acpi_rs_length)(total_size +
						      resource->data.
						      pin_group_config.
						      resource_source.
						      string_length +
						      resource->data.
						      pin_group_config.
						      resource_source_label.
						      string_length +
						      resource->data.
						      pin_group_config.
						      venकरोr_length);

			अवरोध;

		शेष:

			अवरोध;
		पूर्ण

		/* Update the total */

		aml_size_needed += total_size;

		/* Poपूर्णांक to the next object */

		resource =
		    ACPI_ADD_PTR(काष्ठा acpi_resource, resource,
				 resource->length);
	पूर्ण

	/* Did not find an end_tag resource descriptor */

	वापस_ACPI_STATUS(AE_AML_NO_RESOURCE_END_TAG);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_get_list_length
 *
 * PARAMETERS:  aml_buffer          - Poपूर्णांकer to the resource byte stream
 *              aml_buffer_length   - Size of aml_buffer
 *              size_needed         - Where the size needed is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Takes an बाह्यal resource byte stream and calculates the size
 *              buffer needed to hold the corresponding पूर्णांकernal resource
 *              descriptor linked list.
 *
 ******************************************************************************/

acpi_status
acpi_rs_get_list_length(u8 *aml_buffer,
			u32 aml_buffer_length, acpi_size *size_needed)
अणु
	acpi_status status;
	u8 *end_aml;
	u8 *buffer;
	u32 buffer_size;
	u16 temp16;
	u16 resource_length;
	u32 extra_काष्ठा_bytes;
	u8 resource_index;
	u8 minimum_aml_resource_length;
	जोड़ aml_resource *aml_resource;

	ACPI_FUNCTION_TRACE(rs_get_list_length);

	*size_needed = ACPI_RS_SIZE_MIN;	/* Minimum size is one end_tag */
	end_aml = aml_buffer + aml_buffer_length;

	/* Walk the list of AML resource descriptors */

	जबतक (aml_buffer < end_aml) अणु

		/* Validate the Resource Type and Resource Length */

		status =
		    acpi_ut_validate_resource(शून्य, aml_buffer,
					      &resource_index);
		अगर (ACPI_FAILURE(status)) अणु
			/*
			 * Exit on failure. Cannot जारी because the descriptor length
			 * may be bogus also.
			 */
			वापस_ACPI_STATUS(status);
		पूर्ण

		aml_resource = (व्योम *)aml_buffer;

		/* Get the resource length and base (minimum) AML size */

		resource_length = acpi_ut_get_resource_length(aml_buffer);
		minimum_aml_resource_length =
		    acpi_gbl_resource_aml_sizes[resource_index];

		/*
		 * Augment the size क्रम descriptors with optional
		 * and/or variable length fields
		 */
		extra_काष्ठा_bytes = 0;
		buffer =
		    aml_buffer + acpi_ut_get_resource_header_length(aml_buffer);

		चयन (acpi_ut_get_resource_type(aml_buffer)) अणु
		हाल ACPI_RESOURCE_NAME_IRQ:
			/*
			 * IRQ Resource:
			 * Get the number of bits set in the 16-bit IRQ mask
			 */
			ACPI_MOVE_16_TO_16(&temp16, buffer);
			extra_काष्ठा_bytes = acpi_rs_count_set_bits(temp16);
			अवरोध;

		हाल ACPI_RESOURCE_NAME_DMA:
			/*
			 * DMA Resource:
			 * Get the number of bits set in the 8-bit DMA mask
			 */
			extra_काष्ठा_bytes = acpi_rs_count_set_bits(*buffer);
			अवरोध;

		हाल ACPI_RESOURCE_NAME_VENDOR_SMALL:
		हाल ACPI_RESOURCE_NAME_VENDOR_LARGE:
			/*
			 * Venकरोr Resource:
			 * Get the number of venकरोr data bytes
			 */
			extra_काष्ठा_bytes = resource_length;

			/*
			 * There is alपढ़ोy one byte included in the minimum
			 * descriptor size. If there are extra काष्ठा bytes,
			 * subtract one from the count.
			 */
			अगर (extra_काष्ठा_bytes) अणु
				extra_काष्ठा_bytes--;
			पूर्ण
			अवरोध;

		हाल ACPI_RESOURCE_NAME_END_TAG:
			/*
			 * End Tag: This is the normal निकास
			 */
			वापस_ACPI_STATUS(AE_OK);

		हाल ACPI_RESOURCE_NAME_ADDRESS32:
		हाल ACPI_RESOURCE_NAME_ADDRESS16:
		हाल ACPI_RESOURCE_NAME_ADDRESS64:
			/*
			 * Address Resource:
			 * Add the size of the optional resource_source
			 */
			extra_काष्ठा_bytes =
			    acpi_rs_stream_option_length(resource_length,
							 minimum_aml_resource_length);
			अवरोध;

		हाल ACPI_RESOURCE_NAME_EXTENDED_IRQ:
			/*
			 * Extended IRQ Resource:
			 * Using the पूर्णांकerrupt_table_length, add 4 bytes क्रम each additional
			 * पूर्णांकerrupt. Note: at least one पूर्णांकerrupt is required and is
			 * included in the minimum descriptor size (reason क्रम the -1)
			 */
			extra_काष्ठा_bytes = (buffer[1] - 1) * माप(u32);

			/* Add the size of the optional resource_source */

			extra_काष्ठा_bytes +=
			    acpi_rs_stream_option_length(resource_length -
							 extra_काष्ठा_bytes,
							 minimum_aml_resource_length);
			अवरोध;

		हाल ACPI_RESOURCE_NAME_GPIO:

			/* Venकरोr data is optional */

			अगर (aml_resource->gpio.venकरोr_length) अणु
				extra_काष्ठा_bytes +=
				    aml_resource->gpio.venकरोr_offset -
				    aml_resource->gpio.pin_table_offset +
				    aml_resource->gpio.venकरोr_length;
			पूर्ण अन्यथा अणु
				extra_काष्ठा_bytes +=
				    aml_resource->large_header.resource_length +
				    माप(काष्ठा aml_resource_large_header) -
				    aml_resource->gpio.pin_table_offset;
			पूर्ण
			अवरोध;

		हाल ACPI_RESOURCE_NAME_PIN_FUNCTION:

			/* Venकरोr data is optional */

			अगर (aml_resource->pin_function.venकरोr_length) अणु
				extra_काष्ठा_bytes +=
				    aml_resource->pin_function.venकरोr_offset -
				    aml_resource->pin_function.
				    pin_table_offset +
				    aml_resource->pin_function.venकरोr_length;
			पूर्ण अन्यथा अणु
				extra_काष्ठा_bytes +=
				    aml_resource->large_header.resource_length +
				    माप(काष्ठा aml_resource_large_header) -
				    aml_resource->pin_function.pin_table_offset;
			पूर्ण
			अवरोध;

		हाल ACPI_RESOURCE_NAME_SERIAL_BUS:

			minimum_aml_resource_length =
			    acpi_gbl_resource_aml_serial_bus_sizes
			    [aml_resource->common_serial_bus.type];
			extra_काष्ठा_bytes +=
			    aml_resource->common_serial_bus.resource_length -
			    minimum_aml_resource_length;
			अवरोध;

		हाल ACPI_RESOURCE_NAME_PIN_CONFIG:

			/* Venकरोr data is optional */

			अगर (aml_resource->pin_config.venकरोr_length) अणु
				extra_काष्ठा_bytes +=
				    aml_resource->pin_config.venकरोr_offset -
				    aml_resource->pin_config.pin_table_offset +
				    aml_resource->pin_config.venकरोr_length;
			पूर्ण अन्यथा अणु
				extra_काष्ठा_bytes +=
				    aml_resource->large_header.resource_length +
				    माप(काष्ठा aml_resource_large_header) -
				    aml_resource->pin_config.pin_table_offset;
			पूर्ण
			अवरोध;

		हाल ACPI_RESOURCE_NAME_PIN_GROUP:

			extra_काष्ठा_bytes +=
			    aml_resource->pin_group.venकरोr_offset -
			    aml_resource->pin_group.pin_table_offset +
			    aml_resource->pin_group.venकरोr_length;

			अवरोध;

		हाल ACPI_RESOURCE_NAME_PIN_GROUP_FUNCTION:

			extra_काष्ठा_bytes +=
			    aml_resource->pin_group_function.venकरोr_offset -
			    aml_resource->pin_group_function.res_source_offset +
			    aml_resource->pin_group_function.venकरोr_length;

			अवरोध;

		हाल ACPI_RESOURCE_NAME_PIN_GROUP_CONFIG:

			extra_काष्ठा_bytes +=
			    aml_resource->pin_group_config.venकरोr_offset -
			    aml_resource->pin_group_config.res_source_offset +
			    aml_resource->pin_group_config.venकरोr_length;

			अवरोध;

		शेष:

			अवरोध;
		पूर्ण

		/*
		 * Update the required buffer size क्रम the पूर्णांकernal descriptor काष्ठाs
		 *
		 * Important: Round the size up क्रम the appropriate alignment. This
		 * is a requirement on IA64.
		 */
		अगर (acpi_ut_get_resource_type(aml_buffer) ==
		    ACPI_RESOURCE_NAME_SERIAL_BUS) अणु
			buffer_size =
			    acpi_gbl_resource_काष्ठा_serial_bus_sizes
			    [aml_resource->common_serial_bus.type] +
			    extra_काष्ठा_bytes;
		पूर्ण अन्यथा अणु
			buffer_size =
			    acpi_gbl_resource_काष्ठा_sizes[resource_index] +
			    extra_काष्ठा_bytes;
		पूर्ण

		buffer_size = (u32)ACPI_ROUND_UP_TO_NATIVE_WORD(buffer_size);
		*size_needed += buffer_size;

		ACPI_DEBUG_PRINT((ACPI_DB_RESOURCES,
				  "Type %.2X, AmlLength %.2X InternalLength %.2X%8X\n",
				  acpi_ut_get_resource_type(aml_buffer),
				  acpi_ut_get_descriptor_length(aml_buffer),
				  ACPI_FORMAT_UINT64(*size_needed)));

		/*
		 * Poपूर्णांक to the next resource within the AML stream using the length
		 * contained in the resource descriptor header
		 */
		aml_buffer += acpi_ut_get_descriptor_length(aml_buffer);
	पूर्ण

	/* Did not find an end_tag resource descriptor */

	वापस_ACPI_STATUS(AE_AML_NO_RESOURCE_END_TAG);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_get_pci_routing_table_length
 *
 * PARAMETERS:  package_object          - Poपूर्णांकer to the package object
 *              buffer_size_needed      - u32 poपूर्णांकer of the size buffer
 *                                        needed to properly वापस the
 *                                        parsed data
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Given a package representing a PCI routing table, this
 *              calculates the size of the corresponding linked list of
 *              descriptions.
 *
 ******************************************************************************/

acpi_status
acpi_rs_get_pci_routing_table_length(जोड़ acpi_opeअक्रम_object *package_object,
				     acpi_size *buffer_size_needed)
अणु
	u32 number_of_elements;
	acpi_size temp_size_needed = 0;
	जोड़ acpi_opeअक्रम_object **top_object_list;
	u32 index;
	जोड़ acpi_opeअक्रम_object *package_element;
	जोड़ acpi_opeअक्रम_object **sub_object_list;
	u8 name_found;
	u32 table_index;

	ACPI_FUNCTION_TRACE(rs_get_pci_routing_table_length);

	number_of_elements = package_object->package.count;

	/*
	 * Calculate the size of the वापस buffer.
	 * The base size is the number of elements * the sizes of the
	 * काष्ठाures. Additional space क्रम the strings is added below.
	 * The minus one is to subtract the size of the u8 Source[1]
	 * member because it is added below.
	 *
	 * But each PRT_ENTRY काष्ठाure has a poपूर्णांकer to a string and
	 * the size of that string must be found.
	 */
	top_object_list = package_object->package.elements;

	क्रम (index = 0; index < number_of_elements; index++) अणु

		/* Dereference the subpackage */

		package_element = *top_object_list;

		/* We must have a valid Package object */

		अगर (!package_element ||
		    (package_element->common.type != ACPI_TYPE_PACKAGE)) अणु
			वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		पूर्ण

		/*
		 * The sub_object_list will now poपूर्णांक to an array of the
		 * four IRQ elements: Address, Pin, Source and source_index
		 */
		sub_object_list = package_element->package.elements;

		/* Scan the irq_table_elements क्रम the Source Name String */

		name_found = FALSE;

		क्रम (table_index = 0;
		     table_index < package_element->package.count
		     && !name_found; table_index++) अणु
			अगर (*sub_object_list &&	/* Null object allowed */
			    ((ACPI_TYPE_STRING ==
			      (*sub_object_list)->common.type) ||
			     ((ACPI_TYPE_LOCAL_REFERENCE ==
			       (*sub_object_list)->common.type) &&
			      ((*sub_object_list)->reference.class ==
			       ACPI_REFCLASS_NAME)))) अणु
				name_found = TRUE;
			पूर्ण अन्यथा अणु
				/* Look at the next element */

				sub_object_list++;
			पूर्ण
		पूर्ण

		temp_size_needed += (माप(काष्ठा acpi_pci_routing_table) - 4);

		/* Was a String type found? */

		अगर (name_found) अणु
			अगर ((*sub_object_list)->common.type == ACPI_TYPE_STRING) अणु
				/*
				 * The length String.Length field करोes not include the
				 * terminating शून्य, add 1
				 */
				temp_size_needed += ((acpi_size)
						     (*sub_object_list)->string.
						     length + 1);
			पूर्ण अन्यथा अणु
				temp_size_needed += acpi_ns_get_pathname_length((*sub_object_list)->reference.node);
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * If no name was found, then this is a शून्य, which is
			 * translated as a u32 zero.
			 */
			temp_size_needed += माप(u32);
		पूर्ण

		/* Round up the size since each element must be aligned */

		temp_size_needed = ACPI_ROUND_UP_TO_64BIT(temp_size_needed);

		/* Poपूर्णांक to the next जोड़ acpi_opeअक्रम_object */

		top_object_list++;
	पूर्ण

	/*
	 * Add an extra element to the end of the list, essentially a
	 * शून्य terminator
	 */
	*buffer_size_needed =
	    temp_size_needed + माप(काष्ठा acpi_pci_routing_table);
	वापस_ACPI_STATUS(AE_OK);
पूर्ण
