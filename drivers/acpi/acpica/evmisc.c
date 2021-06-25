<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: evmisc - Miscellaneous event manager support functions
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acevents.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_EVENTS
ACPI_MODULE_NAME("evmisc")

/* Local prototypes */
अटल व्योम ACPI_SYSTEM_XFACE acpi_ev_notअगरy_dispatch(व्योम *context);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_is_notअगरy_object
 *
 * PARAMETERS:  node            - Node to check
 *
 * RETURN:      TRUE अगर notअगरies allowed on this object
 *
 * DESCRIPTION: Check type of node क्रम a object that supports notअगरies.
 *
 *              TBD: This could be replaced by a flag bit in the node.
 *
 ******************************************************************************/

u8 acpi_ev_is_notअगरy_object(काष्ठा acpi_namespace_node *node)
अणु

	चयन (node->type) अणु
	हाल ACPI_TYPE_DEVICE:
	हाल ACPI_TYPE_PROCESSOR:
	हाल ACPI_TYPE_THERMAL:
		/*
		 * These are the ONLY objects that can receive ACPI notअगरications
		 */
		वापस (TRUE);

	शेष:

		वापस (FALSE);
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_queue_notअगरy_request
 *
 * PARAMETERS:  node            - NS node क्रम the notअगरied object
 *              notअगरy_value    - Value from the Notअगरy() request
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Dispatch a device notअगरication event to a previously
 *              installed handler.
 *
 ******************************************************************************/

acpi_status
acpi_ev_queue_notअगरy_request(काष्ठा acpi_namespace_node *node, u32 notअगरy_value)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_opeअक्रम_object *handler_list_head = शून्य;
	जोड़ acpi_generic_state *info;
	u8 handler_list_id = 0;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_NAME(ev_queue_notअगरy_request);

	/* Are Notअगरies allowed on this object? */

	अगर (!acpi_ev_is_notअगरy_object(node)) अणु
		वापस (AE_TYPE);
	पूर्ण

	/* Get the correct notअगरy list type (System or Device) */

	अगर (notअगरy_value <= ACPI_MAX_SYS_NOTIFY) अणु
		handler_list_id = ACPI_SYSTEM_HANDLER_LIST;
	पूर्ण अन्यथा अणु
		handler_list_id = ACPI_DEVICE_HANDLER_LIST;
	पूर्ण

	/* Get the notअगरy object attached to the namespace Node */

	obj_desc = acpi_ns_get_attached_object(node);
	अगर (obj_desc) अणु

		/* We have an attached object, Get the correct handler list */

		handler_list_head =
		    obj_desc->common_notअगरy.notअगरy_list[handler_list_id];
	पूर्ण

	/*
	 * If there is no notअगरy handler (Global or Local)
	 * क्रम this object, just ignore the notअगरy
	 */
	अगर (!acpi_gbl_global_notअगरy[handler_list_id].handler
	    && !handler_list_head) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "No notify handler for Notify, ignoring (%4.4s, %X) node %p\n",
				  acpi_ut_get_node_name(node), notअगरy_value,
				  node));

		वापस (AE_OK);
	पूर्ण

	/* Setup notअगरy info and schedule the notअगरy dispatcher */

	info = acpi_ut_create_generic_state();
	अगर (!info) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	info->common.descriptor_type = ACPI_DESC_TYPE_STATE_NOTIFY;

	info->notअगरy.node = node;
	info->notअगरy.value = (u16)notअगरy_value;
	info->notअगरy.handler_list_id = handler_list_id;
	info->notअगरy.handler_list_head = handler_list_head;
	info->notअगरy.global = &acpi_gbl_global_notअगरy[handler_list_id];

	ACPI_DEBUG_PRINT((ACPI_DB_INFO,
			  "Dispatching Notify on [%4.4s] (%s) Value 0x%2.2X (%s) Node %p\n",
			  acpi_ut_get_node_name(node),
			  acpi_ut_get_type_name(node->type), notअगरy_value,
			  acpi_ut_get_notअगरy_name(notअगरy_value, ACPI_TYPE_ANY),
			  node));

	status = acpi_os_execute(OSL_NOTIFY_HANDLER,
				 acpi_ev_notअगरy_dispatch, info);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_ut_delete_generic_state(info);
	पूर्ण

	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_notअगरy_dispatch
 *
 * PARAMETERS:  context         - To be passed to the notअगरy handler
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Dispatch a device notअगरication event to a previously
 *              installed handler.
 *
 ******************************************************************************/

अटल व्योम ACPI_SYSTEM_XFACE acpi_ev_notअगरy_dispatch(व्योम *context)
अणु
	जोड़ acpi_generic_state *info = (जोड़ acpi_generic_state *)context;
	जोड़ acpi_opeअक्रम_object *handler_obj;

	ACPI_FUNCTION_ENTRY();

	/* Invoke a global notअगरy handler अगर installed */

	अगर (info->notअगरy.global->handler) अणु
		info->notअगरy.global->handler(info->notअगरy.node,
					     info->notअगरy.value,
					     info->notअगरy.global->context);
	पूर्ण

	/* Now invoke the local notअगरy handler(s) अगर any are installed */

	handler_obj = info->notअगरy.handler_list_head;
	जबतक (handler_obj) अणु
		handler_obj->notअगरy.handler(info->notअगरy.node,
					    info->notअगरy.value,
					    handler_obj->notअगरy.context);

		handler_obj =
		    handler_obj->notअगरy.next[info->notअगरy.handler_list_id];
	पूर्ण

	/* All करोne with the info object */

	acpi_ut_delete_generic_state(info);
पूर्ण

#अगर (!ACPI_REDUCED_HARDWARE)
/******************************************************************************
 *
 * FUNCTION:    acpi_ev_terminate
 *
 * PARAMETERS:  none
 *
 * RETURN:      none
 *
 * DESCRIPTION: Disable events and मुक्त memory allocated क्रम table storage.
 *
 ******************************************************************************/

व्योम acpi_ev_terminate(व्योम)
अणु
	u32 i;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ev_terminate);

	अगर (acpi_gbl_events_initialized) अणु
		/*
		 * Disable all event-related functionality. In all हालs, on error,
		 * prपूर्णांक a message but obviously we करोn't पात.
		 */

		/* Disable all fixed events */

		क्रम (i = 0; i < ACPI_NUM_FIXED_EVENTS; i++) अणु
			status = acpi_disable_event(i, 0);
			अगर (ACPI_FAILURE(status)) अणु
				ACPI_ERROR((AE_INFO,
					    "Could not disable fixed event %u",
					    (u32) i));
			पूर्ण
		पूर्ण

		/* Disable all GPEs in all GPE blocks */

		status = acpi_ev_walk_gpe_list(acpi_hw_disable_gpe_block, शून्य);
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_EXCEPTION((AE_INFO, status,
					"Could not disable GPEs in GPE block"));
		पूर्ण

		status = acpi_ev_हटाओ_global_lock_handler();
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_EXCEPTION((AE_INFO, status,
					"Could not remove Global Lock handler"));
		पूर्ण

		acpi_gbl_events_initialized = FALSE;
	पूर्ण

	/* Remove SCI handlers */

	status = acpi_ev_हटाओ_all_sci_handlers();
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_ERROR((AE_INFO, "Could not remove SCI handler"));
	पूर्ण

	/* Deallocate all handler objects installed within GPE info काष्ठाs */

	status = acpi_ev_walk_gpe_list(acpi_ev_delete_gpe_handlers, शून्य);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_EXCEPTION((AE_INFO, status,
				"Could not delete GPE handlers"));
	पूर्ण

	/* Return to original mode अगर necessary */

	अगर (acpi_gbl_original_mode == ACPI_SYS_MODE_LEGACY) अणु
		status = acpi_disable();
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_WARNING((AE_INFO, "AcpiDisable failed"));
		पूर्ण
	पूर्ण
	वापस_VOID;
पूर्ण

#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */
