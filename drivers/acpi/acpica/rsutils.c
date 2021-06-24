<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: rsutils - Utilities क्रम the resource manager
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"
#समावेश "acresrc.h"

#घोषणा _COMPONENT          ACPI_RESOURCES
ACPI_MODULE_NAME("rsutils")

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_decode_biपंचांगask
 *
 * PARAMETERS:  mask            - Biपंचांगask to decode
 *              list            - Where the converted list is वापसed
 *
 * RETURN:      Count of bits set (length of list)
 *
 * DESCRIPTION: Convert a bit mask पूर्णांकo a list of values
 *
 ******************************************************************************/
u8 acpi_rs_decode_biपंचांगask(u16 mask, u8 * list)
अणु
	u8 i;
	u8 bit_count;

	ACPI_FUNCTION_ENTRY();

	/* Decode the mask bits */

	क्रम (i = 0, bit_count = 0; mask; i++) अणु
		अगर (mask & 0x0001) अणु
			list[bit_count] = i;
			bit_count++;
		पूर्ण

		mask >>= 1;
	पूर्ण

	वापस (bit_count);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_encode_biपंचांगask
 *
 * PARAMETERS:  list            - List of values to encode
 *              count           - Length of list
 *
 * RETURN:      Encoded biपंचांगask
 *
 * DESCRIPTION: Convert a list of values to an encoded biपंचांगask
 *
 ******************************************************************************/

u16 acpi_rs_encode_biपंचांगask(u8 * list, u8 count)
अणु
	u32 i;
	u16 mask;

	ACPI_FUNCTION_ENTRY();

	/* Encode the list पूर्णांकo a single biपंचांगask */

	क्रम (i = 0, mask = 0; i < count; i++) अणु
		mask |= (0x1 << list[i]);
	पूर्ण

	वापस (mask);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_move_data
 *
 * PARAMETERS:  destination         - Poपूर्णांकer to the destination descriptor
 *              source              - Poपूर्णांकer to the source descriptor
 *              item_count          - How many items to move
 *              move_type           - Byte width
 *
 * RETURN:      None
 *
 * DESCRIPTION: Move multiple data items from one descriptor to another. Handles
 *              alignment issues and endian issues अगर necessary, as configured
 *              via the ACPI_MOVE_* macros. (This is why a स_नकल is not used)
 *
 ******************************************************************************/

व्योम
acpi_rs_move_data(व्योम *destination, व्योम *source, u16 item_count, u8 move_type)
अणु
	u32 i;

	ACPI_FUNCTION_ENTRY();

	/* One move per item */

	क्रम (i = 0; i < item_count; i++) अणु
		चयन (move_type) अणु
			/*
			 * For the 8-bit हाल, we can perक्रमm the move all at once
			 * since there are no alignment or endian issues
			 */
		हाल ACPI_RSC_MOVE8:
		हाल ACPI_RSC_MOVE_GPIO_RES:
		हाल ACPI_RSC_MOVE_SERIAL_VEN:
		हाल ACPI_RSC_MOVE_SERIAL_RES:

			स_नकल(destination, source, item_count);
			वापस;

			/*
			 * 16-, 32-, and 64-bit हालs must use the move macros that perक्रमm
			 * endian conversion and/or accommodate hardware that cannot perक्रमm
			 * misaligned memory transfers
			 */
		हाल ACPI_RSC_MOVE16:
		हाल ACPI_RSC_MOVE_GPIO_PIN:

			ACPI_MOVE_16_TO_16(&ACPI_CAST_PTR(u16, destination)[i],
					   &ACPI_CAST_PTR(u16, source)[i]);
			अवरोध;

		हाल ACPI_RSC_MOVE32:

			ACPI_MOVE_32_TO_32(&ACPI_CAST_PTR(u32, destination)[i],
					   &ACPI_CAST_PTR(u32, source)[i]);
			अवरोध;

		हाल ACPI_RSC_MOVE64:

			ACPI_MOVE_64_TO_64(&ACPI_CAST_PTR(u64, destination)[i],
					   &ACPI_CAST_PTR(u64, source)[i]);
			अवरोध;

		शेष:

			वापस;
		पूर्ण
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_set_resource_length
 *
 * PARAMETERS:  total_length        - Length of the AML descriptor, including
 *                                    the header and length fields.
 *              aml                 - Poपूर्णांकer to the raw AML descriptor
 *
 * RETURN:      None
 *
 * DESCRIPTION: Set the resource_length field of an AML
 *              resource descriptor, both Large and Small descriptors are
 *              supported स्वतःmatically. Note: Descriptor Type field must
 *              be valid.
 *
 ******************************************************************************/

व्योम
acpi_rs_set_resource_length(acpi_rsdesc_size total_length,
			    जोड़ aml_resource *aml)
अणु
	acpi_rs_length resource_length;

	ACPI_FUNCTION_ENTRY();

	/* Length is the total descriptor length minus the header length */

	resource_length = (acpi_rs_length)
	    (total_length - acpi_ut_get_resource_header_length(aml));

	/* Length is stored dअगरferently क्रम large and small descriptors */

	अगर (aml->small_header.descriptor_type & ACPI_RESOURCE_NAME_LARGE) अणु

		/* Large descriptor -- bytes 1-2 contain the 16-bit length */

		ACPI_MOVE_16_TO_16(&aml->large_header.resource_length,
				   &resource_length);
	पूर्ण अन्यथा अणु
		/*
		 * Small descriptor -- bits 2:0 of byte 0 contain the length
		 * Clear any existing length, preserving descriptor type bits
		 */
		aml->small_header.descriptor_type = (u8)
		    ((aml->small_header.descriptor_type &
		      ~ACPI_RESOURCE_NAME_SMALL_LENGTH_MASK)
		     | resource_length);
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_set_resource_header
 *
 * PARAMETERS:  descriptor_type     - Byte to be inserted as the type
 *              total_length        - Length of the AML descriptor, including
 *                                    the header and length fields.
 *              aml                 - Poपूर्णांकer to the raw AML descriptor
 *
 * RETURN:      None
 *
 * DESCRIPTION: Set the descriptor_type and resource_length fields of an AML
 *              resource descriptor, both Large and Small descriptors are
 *              supported स्वतःmatically
 *
 ******************************************************************************/

व्योम
acpi_rs_set_resource_header(u8 descriptor_type,
			    acpi_rsdesc_size total_length,
			    जोड़ aml_resource *aml)
अणु
	ACPI_FUNCTION_ENTRY();

	/* Set the Resource Type */

	aml->small_header.descriptor_type = descriptor_type;

	/* Set the Resource Length */

	acpi_rs_set_resource_length(total_length, aml);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_म_नकल
 *
 * PARAMETERS:  destination         - Poपूर्णांकer to the destination string
 *              source              - Poपूर्णांकer to the source string
 *
 * RETURN:      String length, including शून्य terminator
 *
 * DESCRIPTION: Local string copy that वापसs the string length, saving a
 *              म_नकल followed by a म_माप.
 *
 ******************************************************************************/

अटल u16 acpi_rs_म_नकल(अक्षर *destination, अक्षर *source)
अणु
	u16 i;

	ACPI_FUNCTION_ENTRY();

	क्रम (i = 0; source[i]; i++) अणु
		destination[i] = source[i];
	पूर्ण

	destination[i] = 0;

	/* Return string length including the शून्य terminator */

	वापस ((u16) (i + 1));
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_get_resource_source
 *
 * PARAMETERS:  resource_length     - Length field of the descriptor
 *              minimum_length      - Minimum length of the descriptor (minus
 *                                    any optional fields)
 *              resource_source     - Where the resource_source is वापसed
 *              aml                 - Poपूर्णांकer to the raw AML descriptor
 *              string_ptr          - (optional) where to store the actual
 *                                    resource_source string
 *
 * RETURN:      Length of the string plus शून्य terminator, rounded up to native
 *              word boundary
 *
 * DESCRIPTION: Copy the optional resource_source data from a raw AML descriptor
 *              to an पूर्णांकernal resource descriptor
 *
 ******************************************************************************/

acpi_rs_length
acpi_rs_get_resource_source(acpi_rs_length resource_length,
			    acpi_rs_length minimum_length,
			    काष्ठा acpi_resource_source * resource_source,
			    जोड़ aml_resource * aml, अक्षर *string_ptr)
अणु
	acpi_rsdesc_size total_length;
	u8 *aml_resource_source;

	ACPI_FUNCTION_ENTRY();

	total_length =
	    resource_length + माप(काष्ठा aml_resource_large_header);
	aml_resource_source = ACPI_ADD_PTR(u8, aml, minimum_length);

	/*
	 * resource_source is present अगर the length of the descriptor is दीर्घer
	 * than the minimum length.
	 *
	 * Note: Some resource descriptors will have an additional null, so
	 * we add 1 to the minimum length.
	 */
	अगर (total_length > (acpi_rsdesc_size)(minimum_length + 1)) अणु

		/* Get the resource_source_index */

		resource_source->index = aml_resource_source[0];

		resource_source->string_ptr = string_ptr;
		अगर (!string_ptr) अणु
			/*
			 * String destination poपूर्णांकer is not specअगरied; Set the String
			 * poपूर्णांकer to the end of the current resource_source काष्ठाure.
			 */
			resource_source->string_ptr =
			    ACPI_ADD_PTR(अक्षर, resource_source,
					 माप(काष्ठा acpi_resource_source));
		पूर्ण

		/*
		 * In order क्रम the Resource length to be a multiple of the native
		 * word, calculate the length of the string (+1 क्रम शून्य terminator)
		 * and expand to the next word multiple.
		 *
		 * Zero the entire area of the buffer.
		 */
		total_length =
		    (u32)म_माप(ACPI_CAST_PTR(अक्षर, &aml_resource_source[1])) +
		    1;

		total_length = (u32)ACPI_ROUND_UP_TO_NATIVE_WORD(total_length);

		स_रखो(resource_source->string_ptr, 0, total_length);

		/* Copy the resource_source string to the destination */

		resource_source->string_length =
		    acpi_rs_म_नकल(resource_source->string_ptr,
				   ACPI_CAST_PTR(अक्षर,
						 &aml_resource_source[1]));

		वापस ((acpi_rs_length)total_length);
	पूर्ण

	/* resource_source is not present */

	resource_source->index = 0;
	resource_source->string_length = 0;
	resource_source->string_ptr = शून्य;
	वापस (0);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_set_resource_source
 *
 * PARAMETERS:  aml                 - Poपूर्णांकer to the raw AML descriptor
 *              minimum_length      - Minimum length of the descriptor (minus
 *                                    any optional fields)
 *              resource_source     - Internal resource_source

 *
 * RETURN:      Total length of the AML descriptor
 *
 * DESCRIPTION: Convert an optional resource_source from पूर्णांकernal क्रमmat to a
 *              raw AML resource descriptor
 *
 ******************************************************************************/

acpi_rsdesc_size
acpi_rs_set_resource_source(जोड़ aml_resource *aml,
			    acpi_rs_length minimum_length,
			    काष्ठा acpi_resource_source *resource_source)
अणु
	u8 *aml_resource_source;
	acpi_rsdesc_size descriptor_length;

	ACPI_FUNCTION_ENTRY();

	descriptor_length = minimum_length;

	/* Non-zero string length indicates presence of a resource_source */

	अगर (resource_source->string_length) अणु

		/* Poपूर्णांक to the end of the AML descriptor */

		aml_resource_source = ACPI_ADD_PTR(u8, aml, minimum_length);

		/* Copy the resource_source_index */

		aml_resource_source[0] = (u8) resource_source->index;

		/* Copy the resource_source string */

		म_नकल(ACPI_CAST_PTR(अक्षर, &aml_resource_source[1]),
		       resource_source->string_ptr);

		/*
		 * Add the length of the string (+ 1 क्रम null terminator) to the
		 * final descriptor length
		 */
		descriptor_length += ((acpi_rsdesc_size)
				      resource_source->string_length + 1);
	पूर्ण

	/* Return the new total length of the AML descriptor */

	वापस (descriptor_length);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_get_prt_method_data
 *
 * PARAMETERS:  node            - Device node
 *              ret_buffer      - Poपूर्णांकer to a buffer काष्ठाure क्रम the
 *                                results
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to get the _PRT value of an object
 *              contained in an object specअगरied by the handle passed in
 *
 *              If the function fails an appropriate status will be वापसed
 *              and the contents of the callers buffer is undefined.
 *
 ******************************************************************************/

acpi_status
acpi_rs_get_prt_method_data(काष्ठा acpi_namespace_node *node,
			    काष्ठा acpi_buffer *ret_buffer)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	acpi_status status;

	ACPI_FUNCTION_TRACE(rs_get_prt_method_data);

	/* Parameters guaranteed valid by caller */

	/* Execute the method, no parameters */

	status =
	    acpi_ut_evaluate_object(node, METHOD_NAME__PRT, ACPI_BTYPE_PACKAGE,
				    &obj_desc);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Create a resource linked list from the byte stream buffer that comes
	 * back from the _CRS method execution.
	 */
	status = acpi_rs_create_pci_routing_table(obj_desc, ret_buffer);

	/* On निकास, we must delete the object वापसed by evaluate_object */

	acpi_ut_हटाओ_reference(obj_desc);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_get_crs_method_data
 *
 * PARAMETERS:  node            - Device node
 *              ret_buffer      - Poपूर्णांकer to a buffer काष्ठाure क्रम the
 *                                results
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to get the _CRS value of an object
 *              contained in an object specअगरied by the handle passed in
 *
 *              If the function fails an appropriate status will be वापसed
 *              and the contents of the callers buffer is undefined.
 *
 ******************************************************************************/

acpi_status
acpi_rs_get_crs_method_data(काष्ठा acpi_namespace_node *node,
			    काष्ठा acpi_buffer *ret_buffer)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	acpi_status status;

	ACPI_FUNCTION_TRACE(rs_get_crs_method_data);

	/* Parameters guaranteed valid by caller */

	/* Execute the method, no parameters */

	status =
	    acpi_ut_evaluate_object(node, METHOD_NAME__CRS, ACPI_BTYPE_BUFFER,
				    &obj_desc);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Make the call to create a resource linked list from the
	 * byte stream buffer that comes back from the _CRS method
	 * execution.
	 */
	status = acpi_rs_create_resource_list(obj_desc, ret_buffer);

	/* On निकास, we must delete the object वापसed by evaluateObject */

	acpi_ut_हटाओ_reference(obj_desc);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_get_prs_method_data
 *
 * PARAMETERS:  node            - Device node
 *              ret_buffer      - Poपूर्णांकer to a buffer काष्ठाure क्रम the
 *                                results
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to get the _PRS value of an object
 *              contained in an object specअगरied by the handle passed in
 *
 *              If the function fails an appropriate status will be वापसed
 *              and the contents of the callers buffer is undefined.
 *
 ******************************************************************************/

acpi_status
acpi_rs_get_prs_method_data(काष्ठा acpi_namespace_node *node,
			    काष्ठा acpi_buffer *ret_buffer)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	acpi_status status;

	ACPI_FUNCTION_TRACE(rs_get_prs_method_data);

	/* Parameters guaranteed valid by caller */

	/* Execute the method, no parameters */

	status =
	    acpi_ut_evaluate_object(node, METHOD_NAME__PRS, ACPI_BTYPE_BUFFER,
				    &obj_desc);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Make the call to create a resource linked list from the
	 * byte stream buffer that comes back from the _CRS method
	 * execution.
	 */
	status = acpi_rs_create_resource_list(obj_desc, ret_buffer);

	/* On निकास, we must delete the object वापसed by evaluateObject */

	acpi_ut_हटाओ_reference(obj_desc);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_get_aei_method_data
 *
 * PARAMETERS:  node            - Device node
 *              ret_buffer      - Poपूर्णांकer to a buffer काष्ठाure क्रम the
 *                                results
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to get the _AEI value of an object
 *              contained in an object specअगरied by the handle passed in
 *
 *              If the function fails an appropriate status will be वापसed
 *              and the contents of the callers buffer is undefined.
 *
 ******************************************************************************/

acpi_status
acpi_rs_get_aei_method_data(काष्ठा acpi_namespace_node *node,
			    काष्ठा acpi_buffer *ret_buffer)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	acpi_status status;

	ACPI_FUNCTION_TRACE(rs_get_aei_method_data);

	/* Parameters guaranteed valid by caller */

	/* Execute the method, no parameters */

	status =
	    acpi_ut_evaluate_object(node, METHOD_NAME__AEI, ACPI_BTYPE_BUFFER,
				    &obj_desc);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Make the call to create a resource linked list from the
	 * byte stream buffer that comes back from the _CRS method
	 * execution.
	 */
	status = acpi_rs_create_resource_list(obj_desc, ret_buffer);

	/* On निकास, we must delete the object वापसed by evaluateObject */

	acpi_ut_हटाओ_reference(obj_desc);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_get_method_data
 *
 * PARAMETERS:  handle          - Handle to the containing object
 *              path            - Path to method, relative to Handle
 *              ret_buffer      - Poपूर्णांकer to a buffer काष्ठाure क्रम the
 *                                results
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to get the _CRS or _PRS value of an
 *              object contained in an object specअगरied by the handle passed in
 *
 *              If the function fails an appropriate status will be वापसed
 *              and the contents of the callers buffer is undefined.
 *
 ******************************************************************************/

acpi_status
acpi_rs_get_method_data(acpi_handle handle,
			स्थिर अक्षर *path, काष्ठा acpi_buffer *ret_buffer)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	acpi_status status;

	ACPI_FUNCTION_TRACE(rs_get_method_data);

	/* Parameters guaranteed valid by caller */

	/* Execute the method, no parameters */

	status =
	    acpi_ut_evaluate_object(ACPI_CAST_PTR
				    (काष्ठा acpi_namespace_node, handle), path,
				    ACPI_BTYPE_BUFFER, &obj_desc);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Make the call to create a resource linked list from the
	 * byte stream buffer that comes back from the method
	 * execution.
	 */
	status = acpi_rs_create_resource_list(obj_desc, ret_buffer);

	/* On निकास, we must delete the object वापसed by evaluate_object */

	acpi_ut_हटाओ_reference(obj_desc);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_set_srs_method_data
 *
 * PARAMETERS:  node            - Device node
 *              in_buffer       - Poपूर्णांकer to a buffer काष्ठाure of the
 *                                parameter
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to set the _SRS of an object contained
 *              in an object specअगरied by the handle passed in
 *
 *              If the function fails an appropriate status will be वापसed
 *              and the contents of the callers buffer is undefined.
 *
 * Note: Parameters guaranteed valid by caller
 *
 ******************************************************************************/

acpi_status
acpi_rs_set_srs_method_data(काष्ठा acpi_namespace_node *node,
			    काष्ठा acpi_buffer *in_buffer)
अणु
	काष्ठा acpi_evaluate_info *info;
	जोड़ acpi_opeअक्रम_object *args[2];
	acpi_status status;
	काष्ठा acpi_buffer buffer;

	ACPI_FUNCTION_TRACE(rs_set_srs_method_data);

	/* Allocate and initialize the evaluation inक्रमmation block */

	info = ACPI_ALLOCATE_ZEROED(माप(काष्ठा acpi_evaluate_info));
	अगर (!info) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	info->prefix_node = node;
	info->relative_pathname = METHOD_NAME__SRS;
	info->parameters = args;
	info->flags = ACPI_IGNORE_RETURN_VALUE;

	/*
	 * The in_buffer parameter will poपूर्णांक to a linked list of
	 * resource parameters. It needs to be क्रमmatted पूर्णांकo a
	 * byte stream to be sent in as an input parameter to _SRS
	 *
	 * Convert the linked list पूर्णांकo a byte stream
	 */
	buffer.length = ACPI_ALLOCATE_LOCAL_BUFFER;
	status = acpi_rs_create_aml_resources(in_buffer, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ cleanup;
	पूर्ण

	/* Create and initialize the method parameter object */

	args[0] = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_BUFFER);
	अगर (!args[0]) अणु
		/*
		 * Must मुक्त the buffer allocated above (otherwise it is मुक्तd
		 * later)
		 */
		ACPI_FREE(buffer.poपूर्णांकer);
		status = AE_NO_MEMORY;
		जाओ cleanup;
	पूर्ण

	args[0]->buffer.length = (u32) buffer.length;
	args[0]->buffer.poपूर्णांकer = buffer.poपूर्णांकer;
	args[0]->common.flags = AOPOBJ_DATA_VALID;
	args[1] = शून्य;

	/* Execute the method, no वापस value is expected */

	status = acpi_ns_evaluate(info);

	/* Clean up and वापस the status from acpi_ns_evaluate */

	acpi_ut_हटाओ_reference(args[0]);

cleanup:
	ACPI_FREE(info);
	वापस_ACPI_STATUS(status);
पूर्ण
