<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: rsxface - Public पूर्णांकerfaces to the resource manager
 *
 ******************************************************************************/

#घोषणा EXPORT_ACPI_INTERFACES

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acresrc.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_RESOURCES
ACPI_MODULE_NAME("rsxface")

/* Local macros क्रम 16,32-bit to 64-bit conversion */
#घोषणा ACPI_COPY_FIELD(out, in, field)  ((out)->field = (in)->field)
#घोषणा ACPI_COPY_ADDRESS(out, in)                       \
	ACPI_COPY_FIELD(out, in, resource_type);             \
	ACPI_COPY_FIELD(out, in, producer_consumer);         \
	ACPI_COPY_FIELD(out, in, decode);                    \
	ACPI_COPY_FIELD(out, in, min_address_fixed);         \
	ACPI_COPY_FIELD(out, in, max_address_fixed);         \
	ACPI_COPY_FIELD(out, in, info);                      \
	ACPI_COPY_FIELD(out, in, address.granularity);       \
	ACPI_COPY_FIELD(out, in, address.minimum);           \
	ACPI_COPY_FIELD(out, in, address.maximum);           \
	ACPI_COPY_FIELD(out, in, address.translation_offset); \
	ACPI_COPY_FIELD(out, in, address.address_length);    \
	ACPI_COPY_FIELD(out, in, resource_source);
/* Local prototypes */
अटल acpi_status
acpi_rs_match_venकरोr_resource(काष्ठा acpi_resource *resource, व्योम *context);

अटल acpi_status
acpi_rs_validate_parameters(acpi_handle device_handle,
			    काष्ठा acpi_buffer *buffer,
			    काष्ठा acpi_namespace_node **वापस_node);

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_validate_parameters
 *
 * PARAMETERS:  device_handle   - Handle to a device
 *              buffer          - Poपूर्णांकer to a data buffer
 *              वापस_node     - Poपूर्णांकer to where the device node is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Common parameter validation क्रम resource पूर्णांकerfaces
 *
 ******************************************************************************/

अटल acpi_status
acpi_rs_validate_parameters(acpi_handle device_handle,
			    काष्ठा acpi_buffer *buffer,
			    काष्ठा acpi_namespace_node **वापस_node)
अणु
	acpi_status status;
	काष्ठा acpi_namespace_node *node;

	ACPI_FUNCTION_TRACE(rs_validate_parameters);

	/*
	 * Must have a valid handle to an ACPI device
	 */
	अगर (!device_handle) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	node = acpi_ns_validate_handle(device_handle);
	अगर (!node) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	अगर (node->type != ACPI_TYPE_DEVICE) अणु
		वापस_ACPI_STATUS(AE_TYPE);
	पूर्ण

	/*
	 * Validate the user buffer object
	 *
	 * अगर there is a non-zero buffer length we also need a valid poपूर्णांकer in
	 * the buffer. If it's a zero buffer length, we'll be वापसing the
	 * needed buffer size (later), so keep going.
	 */
	status = acpi_ut_validate_buffer(buffer);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	*वापस_node = node;
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_irq_routing_table
 *
 * PARAMETERS:  device_handle   - Handle to the Bus device we are querying
 *              ret_buffer      - Poपूर्णांकer to a buffer to receive the
 *                                current resources क्रम the device
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to get the IRQ routing table क्रम a
 *              specअगरic bus. The caller must first acquire a handle क्रम the
 *              desired bus. The routine table is placed in the buffer poपूर्णांकed
 *              to by the ret_buffer variable parameter.
 *
 *              If the function fails an appropriate status will be वापसed
 *              and the value of ret_buffer is undefined.
 *
 *              This function attempts to execute the _PRT method contained in
 *              the object indicated by the passed device_handle.
 *
 ******************************************************************************/

acpi_status
acpi_get_irq_routing_table(acpi_handle device_handle,
			   काष्ठा acpi_buffer *ret_buffer)
अणु
	acpi_status status;
	काष्ठा acpi_namespace_node *node;

	ACPI_FUNCTION_TRACE(acpi_get_irq_routing_table);

	/* Validate parameters then dispatch to पूर्णांकernal routine */

	status = acpi_rs_validate_parameters(device_handle, ret_buffer, &node);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	status = acpi_rs_get_prt_method_data(node, ret_buffer);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_irq_routing_table)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_current_resources
 *
 * PARAMETERS:  device_handle   - Handle to the device object क्रम the
 *                                device we are querying
 *              ret_buffer      - Poपूर्णांकer to a buffer to receive the
 *                                current resources क्रम the device
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to get the current resources क्रम a
 *              specअगरic device. The caller must first acquire a handle क्रम
 *              the desired device. The resource data is placed in the buffer
 *              poपूर्णांकed to by the ret_buffer variable parameter.
 *
 *              If the function fails an appropriate status will be वापसed
 *              and the value of ret_buffer is undefined.
 *
 *              This function attempts to execute the _CRS method contained in
 *              the object indicated by the passed device_handle.
 *
 ******************************************************************************/
acpi_status
acpi_get_current_resources(acpi_handle device_handle,
			   काष्ठा acpi_buffer *ret_buffer)
अणु
	acpi_status status;
	काष्ठा acpi_namespace_node *node;

	ACPI_FUNCTION_TRACE(acpi_get_current_resources);

	/* Validate parameters then dispatch to पूर्णांकernal routine */

	status = acpi_rs_validate_parameters(device_handle, ret_buffer, &node);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	status = acpi_rs_get_crs_method_data(node, ret_buffer);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_current_resources)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_possible_resources
 *
 * PARAMETERS:  device_handle   - Handle to the device object क्रम the
 *                                device we are querying
 *              ret_buffer      - Poपूर्णांकer to a buffer to receive the
 *                                resources क्रम the device
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to get a list of the possible resources
 *              क्रम a specअगरic device. The caller must first acquire a handle
 *              क्रम the desired device. The resource data is placed in the
 *              buffer poपूर्णांकed to by the ret_buffer variable.
 *
 *              If the function fails an appropriate status will be वापसed
 *              and the value of ret_buffer is undefined.
 *
 ******************************************************************************/
acpi_status
acpi_get_possible_resources(acpi_handle device_handle,
			    काष्ठा acpi_buffer *ret_buffer)
अणु
	acpi_status status;
	काष्ठा acpi_namespace_node *node;

	ACPI_FUNCTION_TRACE(acpi_get_possible_resources);

	/* Validate parameters then dispatch to पूर्णांकernal routine */

	status = acpi_rs_validate_parameters(device_handle, ret_buffer, &node);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	status = acpi_rs_get_prs_method_data(node, ret_buffer);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_possible_resources)

/*******************************************************************************
 *
 * FUNCTION:    acpi_set_current_resources
 *
 * PARAMETERS:  device_handle   - Handle to the device object क्रम the
 *                                device we are setting resources
 *              in_buffer       - Poपूर्णांकer to a buffer containing the
 *                                resources to be set क्रम the device
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to set the current resources क्रम a
 *              specअगरic device. The caller must first acquire a handle क्रम
 *              the desired device. The resource data is passed to the routine
 *              the buffer poपूर्णांकed to by the in_buffer variable.
 *
 ******************************************************************************/
acpi_status
acpi_set_current_resources(acpi_handle device_handle,
			   काष्ठा acpi_buffer *in_buffer)
अणु
	acpi_status status;
	काष्ठा acpi_namespace_node *node;

	ACPI_FUNCTION_TRACE(acpi_set_current_resources);

	/* Validate the buffer, करोn't allow zero length */

	अगर ((!in_buffer) || (!in_buffer->poपूर्णांकer) || (!in_buffer->length)) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Validate parameters then dispatch to पूर्णांकernal routine */

	status = acpi_rs_validate_parameters(device_handle, in_buffer, &node);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	status = acpi_rs_set_srs_method_data(node, in_buffer);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_set_current_resources)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_event_resources
 *
 * PARAMETERS:  device_handle   - Handle to the device object क्रम the
 *                                device we are getting resources
 *              in_buffer       - Poपूर्णांकer to a buffer containing the
 *                                resources to be set क्रम the device
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to get the event resources क्रम a
 *              specअगरic device. The caller must first acquire a handle क्रम
 *              the desired device. The resource data is passed to the routine
 *              the buffer poपूर्णांकed to by the in_buffer variable. Uses the
 *              _AEI method.
 *
 ******************************************************************************/
acpi_status
acpi_get_event_resources(acpi_handle device_handle,
			 काष्ठा acpi_buffer *ret_buffer)
अणु
	acpi_status status;
	काष्ठा acpi_namespace_node *node;

	ACPI_FUNCTION_TRACE(acpi_get_event_resources);

	/* Validate parameters then dispatch to पूर्णांकernal routine */

	status = acpi_rs_validate_parameters(device_handle, ret_buffer, &node);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	status = acpi_rs_get_aei_method_data(node, ret_buffer);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_event_resources)

/******************************************************************************
 *
 * FUNCTION:    acpi_resource_to_address64
 *
 * PARAMETERS:  resource        - Poपूर्णांकer to a resource
 *              out             - Poपूर्णांकer to the users's वापस buffer
 *                                (a काष्ठा acpi_resource_address64)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: If the resource is an address16, address32, or address64,
 *              copy it to the address64 वापस buffer. This saves the
 *              caller from having to duplicate code क्रम dअगरferent-sized
 *              addresses.
 *
 ******************************************************************************/
acpi_status
acpi_resource_to_address64(काष्ठा acpi_resource *resource,
			   काष्ठा acpi_resource_address64 *out)
अणु
	काष्ठा acpi_resource_address16 *address16;
	काष्ठा acpi_resource_address32 *address32;

	अगर (!resource || !out) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	/* Convert 16 or 32 address descriptor to 64 */

	चयन (resource->type) अणु
	हाल ACPI_RESOURCE_TYPE_ADDRESS16:

		address16 =
		    ACPI_CAST_PTR(काष्ठा acpi_resource_address16,
				  &resource->data);
		ACPI_COPY_ADDRESS(out, address16);
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_ADDRESS32:

		address32 =
		    ACPI_CAST_PTR(काष्ठा acpi_resource_address32,
				  &resource->data);
		ACPI_COPY_ADDRESS(out, address32);
		अवरोध;

	हाल ACPI_RESOURCE_TYPE_ADDRESS64:

		/* Simple copy क्रम 64 bit source */

		स_नकल(out, &resource->data,
		       माप(काष्ठा acpi_resource_address64));
		अवरोध;

	शेष:

		वापस (AE_BAD_PARAMETER);
	पूर्ण

	वापस (AE_OK);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_resource_to_address64)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_venकरोr_resource
 *
 * PARAMETERS:  device_handle   - Handle क्रम the parent device object
 *              name            - Method name क्रम the parent resource
 *                                (METHOD_NAME__CRS or METHOD_NAME__PRS)
 *              uuid            - Poपूर्णांकer to the UUID to be matched.
 *                                includes both subtype and 16-byte UUID
 *              ret_buffer      - Where the venकरोr resource is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Walk a resource ढाँचा क्रम the specअगरied device to find a
 *              venकरोr-defined resource that matches the supplied UUID and
 *              UUID subtype. Returns a काष्ठा acpi_resource of type Venकरोr.
 *
 ******************************************************************************/
acpi_status
acpi_get_venकरोr_resource(acpi_handle device_handle,
			 अक्षर *name,
			 काष्ठा acpi_venकरोr_uuid *uuid,
			 काष्ठा acpi_buffer *ret_buffer)
अणु
	काष्ठा acpi_venकरोr_walk_info info;
	acpi_status status;

	/* Other parameters are validated by acpi_walk_resources */

	अगर (!uuid || !ret_buffer) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	info.uuid = uuid;
	info.buffer = ret_buffer;
	info.status = AE_NOT_EXIST;

	/* Walk the _CRS or _PRS resource list क्रम this device */

	status =
	    acpi_walk_resources(device_handle, name,
				acpi_rs_match_venकरोr_resource, &info);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	वापस (info.status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_venकरोr_resource)

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_match_venकरोr_resource
 *
 * PARAMETERS:  acpi_walk_resource_callback
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Match a venकरोr resource via the ACPI 3.0 UUID
 *
 ******************************************************************************/
अटल acpi_status
acpi_rs_match_venकरोr_resource(काष्ठा acpi_resource *resource, व्योम *context)
अणु
	काष्ठा acpi_venकरोr_walk_info *info = context;
	काष्ठा acpi_resource_venकरोr_typed *venकरोr;
	काष्ठा acpi_buffer *buffer;
	acpi_status status;

	/* Ignore all descriptors except Venकरोr */

	अगर (resource->type != ACPI_RESOURCE_TYPE_VENDOR) अणु
		वापस (AE_OK);
	पूर्ण

	venकरोr = &resource->data.venकरोr_typed;

	/*
	 * For a valid match, these conditions must hold:
	 *
	 * 1) Length of descriptor data must be at least as दीर्घ as a UUID काष्ठा
	 * 2) The UUID subtypes must match
	 * 3) The UUID data must match
	 */
	अगर ((venकरोr->byte_length < (ACPI_UUID_LENGTH + 1)) ||
	    (venकरोr->uuid_subtype != info->uuid->subtype) ||
	    (स_भेद(venकरोr->uuid, info->uuid->data, ACPI_UUID_LENGTH))) अणु
		वापस (AE_OK);
	पूर्ण

	/* Validate/Allocate/Clear caller buffer */

	buffer = info->buffer;
	status = acpi_ut_initialize_buffer(buffer, resource->length);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Found the correct resource, copy and वापस it */

	स_नकल(buffer->poपूर्णांकer, resource, resource->length);
	buffer->length = resource->length;

	/* Found the desired descriptor, terminate resource walk */

	info->status = AE_OK;
	वापस (AE_CTRL_TERMINATE);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_walk_resource_buffer
 *
 * PARAMETERS:  buffer          - Formatted buffer वापसed by one of the
 *                                various Get*Resource functions
 *              user_function   - Called क्रम each resource
 *              context         - Passed to user_function
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Walks the input resource ढाँचा. The user_function is called
 *              once क्रम each resource in the list.
 *
 ******************************************************************************/

acpi_status
acpi_walk_resource_buffer(काष्ठा acpi_buffer *buffer,
			  acpi_walk_resource_callback user_function,
			  व्योम *context)
अणु
	acpi_status status = AE_OK;
	काष्ठा acpi_resource *resource;
	काष्ठा acpi_resource *resource_end;

	ACPI_FUNCTION_TRACE(acpi_walk_resource_buffer);

	/* Parameter validation */

	अगर (!buffer || !buffer->poपूर्णांकer || !user_function) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Buffer contains the resource list and length */

	resource = ACPI_CAST_PTR(काष्ठा acpi_resource, buffer->poपूर्णांकer);
	resource_end =
	    ACPI_ADD_PTR(काष्ठा acpi_resource, buffer->poपूर्णांकer, buffer->length);

	/* Walk the resource list until the end_tag is found (or buffer end) */

	जबतक (resource < resource_end) अणु

		/* Sanity check the resource type */

		अगर (resource->type > ACPI_RESOURCE_TYPE_MAX) अणु
			status = AE_AML_INVALID_RESOURCE_TYPE;
			अवरोध;
		पूर्ण

		/* Sanity check the length. It must not be zero, or we loop क्रमever */

		अगर (!resource->length) अणु
			वापस_ACPI_STATUS(AE_AML_BAD_RESOURCE_LENGTH);
		पूर्ण

		/* Invoke the user function, पात on any error वापसed */

		status = user_function(resource, context);
		अगर (ACPI_FAILURE(status)) अणु
			अगर (status == AE_CTRL_TERMINATE) अणु

				/* This is an OK termination by the user function */

				status = AE_OK;
			पूर्ण
			अवरोध;
		पूर्ण

		/* end_tag indicates end-of-list */

		अगर (resource->type == ACPI_RESOURCE_TYPE_END_TAG) अणु
			अवरोध;
		पूर्ण

		/* Get the next resource descriptor */

		resource = ACPI_NEXT_RESOURCE(resource);
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_walk_resource_buffer)

/*******************************************************************************
 *
 * FUNCTION:    acpi_walk_resources
 *
 * PARAMETERS:  device_handle   - Handle to the device object क्रम the
 *                                device we are querying
 *              name            - Method name of the resources we want.
 *                                (METHOD_NAME__CRS, METHOD_NAME__PRS, or
 *                                METHOD_NAME__AEI or METHOD_NAME__DMA)
 *              user_function   - Called क्रम each resource
 *              context         - Passed to user_function
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Retrieves the current or possible resource list क्रम the
 *              specअगरied device. The user_function is called once क्रम
 *              each resource in the list.
 *
 ******************************************************************************/
acpi_status
acpi_walk_resources(acpi_handle device_handle,
		    अक्षर *name,
		    acpi_walk_resource_callback user_function, व्योम *context)
अणु
	acpi_status status;
	काष्ठा acpi_buffer buffer;

	ACPI_FUNCTION_TRACE(acpi_walk_resources);

	/* Parameter validation */

	अगर (!device_handle || !user_function || !name ||
	    (!ACPI_COMPARE_NAMESEG(name, METHOD_NAME__CRS) &&
	     !ACPI_COMPARE_NAMESEG(name, METHOD_NAME__PRS) &&
	     !ACPI_COMPARE_NAMESEG(name, METHOD_NAME__AEI) &&
	     !ACPI_COMPARE_NAMESEG(name, METHOD_NAME__DMA))) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Get the _CRS/_PRS/_AEI/_DMA resource list */

	buffer.length = ACPI_ALLOCATE_LOCAL_BUFFER;
	status = acpi_rs_get_method_data(device_handle, name, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Walk the resource list and cleanup */

	status = acpi_walk_resource_buffer(&buffer, user_function, context);
	ACPI_FREE(buffer.poपूर्णांकer);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_walk_resources)
