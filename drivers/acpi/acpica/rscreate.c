<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: rscreate - Create resource lists/tables
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acresrc.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_RESOURCES
ACPI_MODULE_NAME("rscreate")

/*******************************************************************************
 *
 * FUNCTION:    acpi_buffer_to_resource
 *
 * PARAMETERS:  aml_buffer          - Poपूर्णांकer to the resource byte stream
 *              aml_buffer_length   - Length of the aml_buffer
 *              resource_ptr        - Where the converted resource is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert a raw AML buffer to a resource list
 *
 ******************************************************************************/
acpi_status
acpi_buffer_to_resource(u8 *aml_buffer,
			u16 aml_buffer_length,
			काष्ठा acpi_resource **resource_ptr)
अणु
	acpi_status status;
	acpi_size list_size_needed;
	व्योम *resource;
	व्योम *current_resource_ptr;

	ACPI_FUNCTION_TRACE(acpi_buffer_to_resource);

	/*
	 * Note: we allow AE_AML_NO_RESOURCE_END_TAG, since an end tag
	 * is not required here.
	 */

	/* Get the required length क्रम the converted resource */

	status =
	    acpi_rs_get_list_length(aml_buffer, aml_buffer_length,
				    &list_size_needed);
	अगर (status == AE_AML_NO_RESOURCE_END_TAG) अणु
		status = AE_OK;
	पूर्ण
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Allocate a buffer क्रम the converted resource */

	resource = ACPI_ALLOCATE_ZEROED(list_size_needed);
	current_resource_ptr = resource;
	अगर (!resource) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/* Perक्रमm the AML-to-Resource conversion */

	status = acpi_ut_walk_aml_resources(शून्य, aml_buffer, aml_buffer_length,
					    acpi_rs_convert_aml_to_resources,
					    &current_resource_ptr);
	अगर (status == AE_AML_NO_RESOURCE_END_TAG) अणु
		status = AE_OK;
	पूर्ण
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_FREE(resource);
	पूर्ण अन्यथा अणु
		*resource_ptr = resource;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_buffer_to_resource)

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_create_resource_list
 *
 * PARAMETERS:  aml_buffer          - Poपूर्णांकer to the resource byte stream
 *              output_buffer       - Poपूर्णांकer to the user's buffer
 *
 * RETURN:      Status: AE_OK अगर okay, अन्यथा a valid acpi_status code
 *              If output_buffer is not large enough, output_buffer_length
 *              indicates how large output_buffer should be, अन्यथा it
 *              indicates how may u8 elements of output_buffer are valid.
 *
 * DESCRIPTION: Takes the byte stream वापसed from a _CRS, _PRS control method
 *              execution and parses the stream to create a linked list
 *              of device resources.
 *
 ******************************************************************************/
acpi_status
acpi_rs_create_resource_list(जोड़ acpi_opeअक्रम_object *aml_buffer,
			     काष्ठा acpi_buffer *output_buffer)
अणु

	acpi_status status;
	u8 *aml_start;
	acpi_size list_size_needed = 0;
	u32 aml_buffer_length;
	व्योम *resource;

	ACPI_FUNCTION_TRACE(rs_create_resource_list);

	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "AmlBuffer = %p\n", aml_buffer));

	/* Params alपढ़ोy validated, so we करोn't re-validate here */

	aml_buffer_length = aml_buffer->buffer.length;
	aml_start = aml_buffer->buffer.poपूर्णांकer;

	/*
	 * Pass the aml_buffer पूर्णांकo a module that can calculate
	 * the buffer size needed क्रम the linked list
	 */
	status = acpi_rs_get_list_length(aml_start, aml_buffer_length,
					 &list_size_needed);

	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "Status=%X ListSizeNeeded=%X\n",
			  status, (u32) list_size_needed));
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Validate/Allocate/Clear caller buffer */

	status = acpi_ut_initialize_buffer(output_buffer, list_size_needed);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Do the conversion */

	resource = output_buffer->poपूर्णांकer;
	status = acpi_ut_walk_aml_resources(शून्य, aml_start, aml_buffer_length,
					    acpi_rs_convert_aml_to_resources,
					    &resource);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "OutputBuffer %p Length %X\n",
			  output_buffer->poपूर्णांकer, (u32) output_buffer->length));
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_create_pci_routing_table
 *
 * PARAMETERS:  package_object          - Poपूर्णांकer to a package containing one
 *                                        of more ACPI_OPERAND_OBJECTs
 *              output_buffer           - Poपूर्णांकer to the user's buffer
 *
 * RETURN:      Status  AE_OK अगर okay, अन्यथा a valid acpi_status code.
 *              If the output_buffer is too small, the error will be
 *              AE_BUFFER_OVERFLOW and output_buffer->Length will poपूर्णांक
 *              to the size buffer needed.
 *
 * DESCRIPTION: Takes the जोड़ acpi_opeअक्रम_object package and creates a
 *              linked list of PCI पूर्णांकerrupt descriptions
 *
 * NOTE: It is the caller's responsibility to ensure that the start of the
 * output buffer is aligned properly (अगर necessary).
 *
 ******************************************************************************/

acpi_status
acpi_rs_create_pci_routing_table(जोड़ acpi_opeअक्रम_object *package_object,
				 काष्ठा acpi_buffer *output_buffer)
अणु
	u8 *buffer;
	जोड़ acpi_opeअक्रम_object **top_object_list;
	जोड़ acpi_opeअक्रम_object **sub_object_list;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	acpi_size buffer_size_needed = 0;
	u32 number_of_elements;
	u32 index;
	काष्ठा acpi_pci_routing_table *user_prt;
	काष्ठा acpi_namespace_node *node;
	acpi_status status;
	काष्ठा acpi_buffer path_buffer;

	ACPI_FUNCTION_TRACE(rs_create_pci_routing_table);

	/* Params alपढ़ोy validated, so we करोn't re-validate here */

	/* Get the required buffer length */

	status =
	    acpi_rs_get_pci_routing_table_length(package_object,
						 &buffer_size_needed);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "BufferSizeNeeded = %X\n",
			  (u32) buffer_size_needed));

	/* Validate/Allocate/Clear caller buffer */

	status = acpi_ut_initialize_buffer(output_buffer, buffer_size_needed);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Loop through the ACPI_INTERNAL_OBJECTS - Each object should be a
	 * package that in turn contains an u64 Address, a u8 Pin,
	 * a Name, and a u8 source_index.
	 */
	top_object_list = package_object->package.elements;
	number_of_elements = package_object->package.count;
	buffer = output_buffer->poपूर्णांकer;
	user_prt = ACPI_CAST_PTR(काष्ठा acpi_pci_routing_table, buffer);

	क्रम (index = 0; index < number_of_elements; index++) अणु

		/*
		 * Poपूर्णांक user_prt past this current काष्ठाure
		 *
		 * NOTE: On the first iteration, user_prt->Length will
		 * be zero because we cleared the वापस buffer earlier
		 */
		buffer += user_prt->length;
		user_prt = ACPI_CAST_PTR(काष्ठा acpi_pci_routing_table, buffer);

		/*
		 * Fill in the Length field with the inक्रमmation we have at this
		 * poपूर्णांक. The minus four is to subtract the size of the u8
		 * Source[4] member because it is added below.
		 */
		user_prt->length = (माप(काष्ठा acpi_pci_routing_table) - 4);

		/* Each subpackage must be of length 4 */

		अगर ((*top_object_list)->package.count != 4) अणु
			ACPI_ERROR((AE_INFO,
				    "(PRT[%u]) Need package of length 4, found length %u",
				    index, (*top_object_list)->package.count));
			वापस_ACPI_STATUS(AE_AML_PACKAGE_LIMIT);
		पूर्ण

		/*
		 * Dereference the subpackage.
		 * The sub_object_list will now poपूर्णांक to an array of the four IRQ
		 * elements: [Address, Pin, Source, source_index]
		 */
		sub_object_list = (*top_object_list)->package.elements;

		/* 1) First subobject: Dereference the PRT.Address */

		obj_desc = sub_object_list[0];
		अगर (!obj_desc || obj_desc->common.type != ACPI_TYPE_INTEGER) अणु
			ACPI_ERROR((AE_INFO,
				    "(PRT[%u].Address) Need Integer, found %s",
				    index,
				    acpi_ut_get_object_type_name(obj_desc)));
			वापस_ACPI_STATUS(AE_BAD_DATA);
		पूर्ण

		user_prt->address = obj_desc->पूर्णांकeger.value;

		/* 2) Second subobject: Dereference the PRT.Pin */

		obj_desc = sub_object_list[1];
		अगर (!obj_desc || obj_desc->common.type != ACPI_TYPE_INTEGER) अणु
			ACPI_ERROR((AE_INFO,
				    "(PRT[%u].Pin) Need Integer, found %s",
				    index,
				    acpi_ut_get_object_type_name(obj_desc)));
			वापस_ACPI_STATUS(AE_BAD_DATA);
		पूर्ण

		user_prt->pin = (u32) obj_desc->पूर्णांकeger.value;

		/*
		 * 3) Third subobject: Dereference the PRT.source_name
		 * The name may be unresolved (slack mode), so allow a null object
		 */
		obj_desc = sub_object_list[2];
		अगर (obj_desc) अणु
			चयन (obj_desc->common.type) अणु
			हाल ACPI_TYPE_LOCAL_REFERENCE:

				अगर (obj_desc->reference.class !=
				    ACPI_REFCLASS_NAME) अणु
					ACPI_ERROR((AE_INFO,
						    "(PRT[%u].Source) Need name, found Reference Class 0x%X",
						    index,
						    obj_desc->reference.class));
					वापस_ACPI_STATUS(AE_BAD_DATA);
				पूर्ण

				node = obj_desc->reference.node;

				/* Use *reमुख्यing* length of the buffer as max क्रम pathname */

				path_buffer.length = output_buffer->length -
				    (u32) ((u8 *) user_prt->source -
					   (u8 *) output_buffer->poपूर्णांकer);
				path_buffer.poपूर्णांकer = user_prt->source;

				status = acpi_ns_handle_to_pathname((acpi_handle)node, &path_buffer, FALSE);
				अगर (ACPI_FAILURE(status)) अणु
					वापस_ACPI_STATUS(status);
				पूर्ण

				/* +1 to include null terminator */

				user_prt->length +=
				    (u32)म_माप(user_prt->source) + 1;
				अवरोध;

			हाल ACPI_TYPE_STRING:

				म_नकल(user_prt->source,
				       obj_desc->string.poपूर्णांकer);

				/*
				 * Add to the Length field the length of the string
				 * (add 1 क्रम terminator)
				 */
				user_prt->length += obj_desc->string.length + 1;
				अवरोध;

			हाल ACPI_TYPE_INTEGER:
				/*
				 * If this is a number, then the Source Name is शून्य, since
				 * the entire buffer was zeroed out, we can leave this alone.
				 *
				 * Add to the Length field the length of the u32 शून्य
				 */
				user_prt->length += माप(u32);
				अवरोध;

			शेष:

				ACPI_ERROR((AE_INFO,
					    "(PRT[%u].Source) Need Ref/String/Integer, found %s",
					    index,
					    acpi_ut_get_object_type_name
					    (obj_desc)));
				वापस_ACPI_STATUS(AE_BAD_DATA);
			पूर्ण
		पूर्ण

		/* Now align the current length */

		user_prt->length =
		    (u32) ACPI_ROUND_UP_TO_64BIT(user_prt->length);

		/* 4) Fourth subobject: Dereference the PRT.source_index */

		obj_desc = sub_object_list[3];
		अगर (!obj_desc || obj_desc->common.type != ACPI_TYPE_INTEGER) अणु
			ACPI_ERROR((AE_INFO,
				    "(PRT[%u].SourceIndex) Need Integer, found %s",
				    index,
				    acpi_ut_get_object_type_name(obj_desc)));
			वापस_ACPI_STATUS(AE_BAD_DATA);
		पूर्ण

		user_prt->source_index = (u32) obj_desc->पूर्णांकeger.value;

		/* Poपूर्णांक to the next जोड़ acpi_opeअक्रम_object in the top level package */

		top_object_list++;
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "OutputBuffer %p Length %X\n",
			  output_buffer->poपूर्णांकer, (u32) output_buffer->length));
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_create_aml_resources
 *
 * PARAMETERS:  resource_list           - Poपूर्णांकer to the resource list buffer
 *              output_buffer           - Where the AML buffer is वापसed
 *
 * RETURN:      Status  AE_OK अगर okay, अन्यथा a valid acpi_status code.
 *              If the output_buffer is too small, the error will be
 *              AE_BUFFER_OVERFLOW and output_buffer->Length will poपूर्णांक
 *              to the size buffer needed.
 *
 * DESCRIPTION: Converts a list of device resources to an AML bytestream
 *              to be used as input क्रम the _SRS control method.
 *
 ******************************************************************************/

acpi_status
acpi_rs_create_aml_resources(काष्ठा acpi_buffer *resource_list,
			     काष्ठा acpi_buffer *output_buffer)
अणु
	acpi_status status;
	acpi_size aml_size_needed = 0;

	ACPI_FUNCTION_TRACE(rs_create_aml_resources);

	/* Params alपढ़ोy validated, no need to re-validate here */

	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "ResourceList Buffer = %p\n",
			  resource_list->poपूर्णांकer));

	/* Get the buffer size needed क्रम the AML byte stream */

	status =
	    acpi_rs_get_aml_length(resource_list->poपूर्णांकer,
				   resource_list->length, &aml_size_needed);

	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "AmlSizeNeeded=%X, %s\n",
			  (u32)aml_size_needed, acpi_क्रमmat_exception(status)));
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Validate/Allocate/Clear caller buffer */

	status = acpi_ut_initialize_buffer(output_buffer, aml_size_needed);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Do the conversion */

	status = acpi_rs_convert_resources_to_aml(resource_list->poपूर्णांकer,
						  aml_size_needed,
						  output_buffer->poपूर्णांकer);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "OutputBuffer %p Length %X\n",
			  output_buffer->poपूर्णांकer, (u32) output_buffer->length));
	वापस_ACPI_STATUS(AE_OK);
पूर्ण
