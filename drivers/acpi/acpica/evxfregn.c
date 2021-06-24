<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: evxfregn - External Interfaces, ACPI Operation Regions and
 *                         Address Spaces.
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#घोषणा EXPORT_ACPI_INTERFACES

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"
#समावेश "acevents.h"

#घोषणा _COMPONENT          ACPI_EVENTS
ACPI_MODULE_NAME("evxfregn")

/*******************************************************************************
 *
 * FUNCTION:    acpi_install_address_space_handler
 *
 * PARAMETERS:  device          - Handle क्रम the device
 *              space_id        - The address space ID
 *              handler         - Address of the handler
 *              setup           - Address of the setup function
 *              context         - Value passed to the handler on each access
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install a handler क्रम all op_regions of a given space_id.
 *
 * NOTE: This function should only be called after acpi_enable_subप्रणाली has
 * been called. This is because any _REG methods associated with the Space ID
 * are executed here, and these methods can only be safely executed after
 * the शेष handlers have been installed and the hardware has been
 * initialized (via acpi_enable_subप्रणाली.)
 *
 ******************************************************************************/
acpi_status
acpi_install_address_space_handler(acpi_handle device,
				   acpi_adr_space_type space_id,
				   acpi_adr_space_handler handler,
				   acpi_adr_space_setup setup, व्योम *context)
अणु
	काष्ठा acpi_namespace_node *node;
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_install_address_space_handler);

	/* Parameter validation */

	अगर (!device) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Convert and validate the device handle */

	node = acpi_ns_validate_handle(device);
	अगर (!node) अणु
		status = AE_BAD_PARAMETER;
		जाओ unlock_and_निकास;
	पूर्ण

	/* Install the handler क्रम all Regions क्रम this Space ID */

	status =
	    acpi_ev_install_space_handler(node, space_id, handler, setup,
					  context);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ unlock_and_निकास;
	पूर्ण

	/* Run all _REG methods क्रम this address space */

	acpi_ev_execute_reg_methods(node, space_id, ACPI_REG_CONNECT);

unlock_and_निकास:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_install_address_space_handler)

/*******************************************************************************
 *
 * FUNCTION:    acpi_हटाओ_address_space_handler
 *
 * PARAMETERS:  device          - Handle क्रम the device
 *              space_id        - The address space ID
 *              handler         - Address of the handler
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Remove a previously installed handler.
 *
 ******************************************************************************/
acpi_status
acpi_हटाओ_address_space_handler(acpi_handle device,
				  acpi_adr_space_type space_id,
				  acpi_adr_space_handler handler)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_opeअक्रम_object *handler_obj;
	जोड़ acpi_opeअक्रम_object *region_obj;
	जोड़ acpi_opeअक्रम_object **last_obj_ptr;
	काष्ठा acpi_namespace_node *node;
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_हटाओ_address_space_handler);

	/* Parameter validation */

	अगर (!device) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Convert and validate the device handle */

	node = acpi_ns_validate_handle(device);
	अगर (!node ||
	    ((node->type != ACPI_TYPE_DEVICE) &&
	     (node->type != ACPI_TYPE_PROCESSOR) &&
	     (node->type != ACPI_TYPE_THERMAL) &&
	     (node != acpi_gbl_root_node))) अणु
		status = AE_BAD_PARAMETER;
		जाओ unlock_and_निकास;
	पूर्ण

	/* Make sure the पूर्णांकernal object exists */

	obj_desc = acpi_ns_get_attached_object(node);
	अगर (!obj_desc) अणु
		status = AE_NOT_EXIST;
		जाओ unlock_and_निकास;
	पूर्ण

	/* Find the address handler the user requested */

	handler_obj = obj_desc->common_notअगरy.handler;
	last_obj_ptr = &obj_desc->common_notअगरy.handler;
	जबतक (handler_obj) अणु

		/* We have a handler, see अगर user requested this one */

		अगर (handler_obj->address_space.space_id == space_id) अणु

			/* Handler must be the same as the installed handler */

			अगर (handler_obj->address_space.handler != handler) अणु
				status = AE_BAD_PARAMETER;
				जाओ unlock_and_निकास;
			पूर्ण

			/* Matched space_id, first dereference this in the Regions */

			ACPI_DEBUG_PRINT((ACPI_DB_OPREGION,
					  "Removing address handler %p(%p) for region %s "
					  "on Device %p(%p)\n",
					  handler_obj, handler,
					  acpi_ut_get_region_name(space_id),
					  node, obj_desc));

			region_obj = handler_obj->address_space.region_list;

			/* Walk the handler's region list */

			जबतक (region_obj) अणु
				/*
				 * First disassociate the handler from the region.
				 *
				 * NOTE: this करोesn't mean that the region goes away
				 * The region is just inaccessible as indicated to
				 * the _REG method
				 */
				acpi_ev_detach_region(region_obj, TRUE);

				/*
				 * Walk the list: Just grab the head because the
				 * detach_region हटाओd the previous head.
				 */
				region_obj =
				    handler_obj->address_space.region_list;
			पूर्ण

			/* Remove this Handler object from the list */

			*last_obj_ptr = handler_obj->address_space.next;

			/* Now we can delete the handler object */

			acpi_os_release_mutex(handler_obj->address_space.
					      context_mutex);
			acpi_ut_हटाओ_reference(handler_obj);
			जाओ unlock_and_निकास;
		पूर्ण

		/* Walk the linked list of handlers */

		last_obj_ptr = &handler_obj->address_space.next;
		handler_obj = handler_obj->address_space.next;
	पूर्ण

	/* The handler करोes not exist */

	ACPI_DEBUG_PRINT((ACPI_DB_OPREGION,
			  "Unable to remove address handler %p for %s(%X), DevNode %p, obj %p\n",
			  handler, acpi_ut_get_region_name(space_id), space_id,
			  node, obj_desc));

	status = AE_NOT_EXIST;

unlock_and_निकास:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_हटाओ_address_space_handler)
