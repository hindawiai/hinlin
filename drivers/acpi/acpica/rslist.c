<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: rslist - Linked list utilities
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acresrc.h"

#घोषणा _COMPONENT          ACPI_RESOURCES
ACPI_MODULE_NAME("rslist")

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_convert_aml_to_resources
 *
 * PARAMETERS:  acpi_walk_aml_callback
 *              resource_ptr            - Poपूर्णांकer to the buffer that will
 *                                        contain the output काष्ठाures
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert an AML resource to an पूर्णांकernal representation of the
 *              resource that is aligned and easier to access.
 *
 ******************************************************************************/
acpi_status
acpi_rs_convert_aml_to_resources(u8 * aml,
				 u32 length,
				 u32 offset, u8 resource_index, व्योम **context)
अणु
	काष्ठा acpi_resource **resource_ptr =
	    ACPI_CAST_INसूचीECT_PTR(काष्ठा acpi_resource, context);
	काष्ठा acpi_resource *resource;
	जोड़ aml_resource *aml_resource;
	काष्ठा acpi_rsconvert_info *conversion_table;
	acpi_status status;

	ACPI_FUNCTION_TRACE(rs_convert_aml_to_resources);

	/*
	 * Check that the input buffer and all subsequent poपूर्णांकers पूर्णांकo it
	 * are aligned on a native word boundary. Most important on IA64
	 */
	resource = *resource_ptr;
	अगर (ACPI_IS_MISALIGNED(resource)) अणु
		ACPI_WARNING((AE_INFO,
			      "Misaligned resource pointer %p", resource));
	पूर्ण

	/* Get the appropriate conversion info table */

	aml_resource = ACPI_CAST_PTR(जोड़ aml_resource, aml);

	अगर (acpi_ut_get_resource_type(aml) == ACPI_RESOURCE_NAME_SERIAL_BUS) अणु
		अगर (aml_resource->common_serial_bus.type >
		    AML_RESOURCE_MAX_SERIALBUSTYPE) अणु
			conversion_table = शून्य;
		पूर्ण अन्यथा अणु
			/* This is an I2C, SPI, UART, or CSI2 serial_bus descriptor */

			conversion_table =
			    acpi_gbl_convert_resource_serial_bus_dispatch
			    [aml_resource->common_serial_bus.type];
		पूर्ण
	पूर्ण अन्यथा अणु
		conversion_table =
		    acpi_gbl_get_resource_dispatch[resource_index];
	पूर्ण

	अगर (!conversion_table) अणु
		ACPI_ERROR((AE_INFO,
			    "Invalid/unsupported resource descriptor: Type 0x%2.2X",
			    resource_index));
		वापस_ACPI_STATUS(AE_AML_INVALID_RESOURCE_TYPE);
	पूर्ण

	/* Convert the AML byte stream resource to a local resource काष्ठा */

	status =
	    acpi_rs_convert_aml_to_resource(resource, aml_resource,
					    conversion_table);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_EXCEPTION((AE_INFO, status,
				"Could not convert AML resource (Type 0x%X)",
				*aml));
		वापस_ACPI_STATUS(status);
	पूर्ण

	अगर (!resource->length) अणु
		ACPI_EXCEPTION((AE_INFO, status,
				"Zero-length resource returned from RsConvertAmlToResource"));
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_RESOURCES,
			  "Type %.2X, AmlLength %.2X InternalLength %.2X\n",
			  acpi_ut_get_resource_type(aml), length,
			  resource->length));

	/* Poपूर्णांक to the next काष्ठाure in the output buffer */

	*resource_ptr = ACPI_NEXT_RESOURCE(resource);
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_convert_resources_to_aml
 *
 * PARAMETERS:  resource            - Poपूर्णांकer to the resource linked list
 *              aml_size_needed     - Calculated size of the byte stream
 *                                    needed from calling acpi_rs_get_aml_length()
 *                                    The size of the output_buffer is
 *                                    guaranteed to be >= aml_size_needed
 *              output_buffer       - Poपूर्णांकer to the buffer that will
 *                                    contain the byte stream
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Takes the resource linked list and parses it, creating a
 *              byte stream of resources in the caller's output buffer
 *
 ******************************************************************************/

acpi_status
acpi_rs_convert_resources_to_aml(काष्ठा acpi_resource *resource,
				 acpi_size aml_size_needed, u8 * output_buffer)
अणु
	u8 *aml = output_buffer;
	u8 *end_aml = output_buffer + aml_size_needed;
	काष्ठा acpi_rsconvert_info *conversion_table;
	acpi_status status;

	ACPI_FUNCTION_TRACE(rs_convert_resources_to_aml);

	/* Walk the resource descriptor list, convert each descriptor */

	जबतक (aml < end_aml) अणु

		/* Validate the (पूर्णांकernal) Resource Type */

		अगर (resource->type > ACPI_RESOURCE_TYPE_MAX) अणु
			ACPI_ERROR((AE_INFO,
				    "Invalid descriptor type (0x%X) in resource list",
				    resource->type));
			वापस_ACPI_STATUS(AE_BAD_DATA);
		पूर्ण

		/* Sanity check the length. It must not be zero, or we loop क्रमever */

		अगर (!resource->length) अणु
			ACPI_ERROR((AE_INFO,
				    "Invalid zero length descriptor in resource list\n"));
			वापस_ACPI_STATUS(AE_AML_BAD_RESOURCE_LENGTH);
		पूर्ण

		/* Perक्रमm the conversion */

		अगर (resource->type == ACPI_RESOURCE_TYPE_SERIAL_BUS) अणु
			अगर (resource->data.common_serial_bus.type >
			    AML_RESOURCE_MAX_SERIALBUSTYPE) अणु
				conversion_table = शून्य;
			पूर्ण अन्यथा अणु
				/* This is an I2C, SPI, UART or CSI2 serial_bus descriptor */

				conversion_table =
				    acpi_gbl_convert_resource_serial_bus_dispatch
				    [resource->data.common_serial_bus.type];
			पूर्ण
		पूर्ण अन्यथा अणु
			conversion_table =
			    acpi_gbl_set_resource_dispatch[resource->type];
		पूर्ण

		अगर (!conversion_table) अणु
			ACPI_ERROR((AE_INFO,
				    "Invalid/unsupported resource descriptor: Type 0x%2.2X",
				    resource->type));
			वापस_ACPI_STATUS(AE_AML_INVALID_RESOURCE_TYPE);
		पूर्ण

		status = acpi_rs_convert_resource_to_aml(resource,
						         ACPI_CAST_PTR(जोड़
								       aml_resource,
								       aml),
							 conversion_table);
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_EXCEPTION((AE_INFO, status,
					"Could not convert resource (type 0x%X) to AML",
					resource->type));
			वापस_ACPI_STATUS(status);
		पूर्ण

		/* Perक्रमm final sanity check on the new AML resource descriptor */

		status =
		    acpi_ut_validate_resource(शून्य,
					      ACPI_CAST_PTR(जोड़ aml_resource,
							    aml), शून्य);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		/* Check क्रम end-of-list, normal निकास */

		अगर (resource->type == ACPI_RESOURCE_TYPE_END_TAG) अणु

			/* An End Tag indicates the end of the input Resource Template */

			वापस_ACPI_STATUS(AE_OK);
		पूर्ण

		/*
		 * Extract the total length of the new descriptor and set the
		 * Aml to poपूर्णांक to the next (output) resource descriptor
		 */
		aml += acpi_ut_get_descriptor_length(aml);

		/* Poपूर्णांक to the next input resource descriptor */

		resource = ACPI_NEXT_RESOURCE(resource);
	पूर्ण

	/* Completed buffer, but did not find an end_tag resource descriptor */

	वापस_ACPI_STATUS(AE_AML_NO_RESOURCE_END_TAG);
पूर्ण
