<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: evxface - External पूर्णांकerfaces क्रम ACPI events
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#घोषणा EXPORT_ACPI_INTERFACES

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"
#समावेश "acevents.h"
#समावेश "acinterp.h"

#घोषणा _COMPONENT          ACPI_EVENTS
ACPI_MODULE_NAME("evxface")
#अगर (!ACPI_REDUCED_HARDWARE)
/* Local prototypes */
अटल acpi_status
acpi_ev_install_gpe_handler(acpi_handle gpe_device,
			    u32 gpe_number,
			    u32 type,
			    u8 is_raw_handler,
			    acpi_gpe_handler address, व्योम *context);

#पूर्ण_अगर


/*******************************************************************************
 *
 * FUNCTION:    acpi_install_notअगरy_handler
 *
 * PARAMETERS:  device          - The device क्रम which notअगरies will be handled
 *              handler_type    - The type of handler:
 *                                  ACPI_SYSTEM_NOTIFY: System Handler (00-7F)
 *                                  ACPI_DEVICE_NOTIFY: Device Handler (80-FF)
 *                                  ACPI_ALL_NOTIFY:    Both System and Device
 *              handler         - Address of the handler
 *              context         - Value passed to the handler on each GPE
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install a handler क्रम notअगरications on an ACPI Device,
 *              thermal_zone, or Processor object.
 *
 * NOTES:       The Root namespace object may have only one handler क्रम each
 *              type of notअगरy (System/Device). Device/Thermal/Processor objects
 *              may have one device notअगरy handler, and multiple प्रणाली notअगरy
 *              handlers.
 *
 ******************************************************************************/

acpi_status
acpi_install_notअगरy_handler(acpi_handle device,
			    u32 handler_type,
			    acpi_notअगरy_handler handler, व्योम *context)
अणु
	काष्ठा acpi_namespace_node *node =
	    ACPI_CAST_PTR(काष्ठा acpi_namespace_node, device);
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_opeअक्रम_object *handler_obj;
	acpi_status status;
	u32 i;

	ACPI_FUNCTION_TRACE(acpi_install_notअगरy_handler);

	/* Parameter validation */

	अगर ((!device) || (!handler) || (!handler_type) ||
	    (handler_type > ACPI_MAX_NOTIFY_HANDLER_TYPE)) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Root Object:
	 * Registering a notअगरy handler on the root object indicates that the
	 * caller wishes to receive notअगरications क्रम all objects. Note that
	 * only one global handler can be रेजिस्टरed per notअगरy type.
	 * Ensure that a handler is not alपढ़ोy installed.
	 */
	अगर (device == ACPI_ROOT_OBJECT) अणु
		क्रम (i = 0; i < ACPI_NUM_NOTIFY_TYPES; i++) अणु
			अगर (handler_type & (i + 1)) अणु
				अगर (acpi_gbl_global_notअगरy[i].handler) अणु
					status = AE_ALREADY_EXISTS;
					जाओ unlock_and_निकास;
				पूर्ण

				acpi_gbl_global_notअगरy[i].handler = handler;
				acpi_gbl_global_notअगरy[i].context = context;
			पूर्ण
		पूर्ण

		जाओ unlock_and_निकास;	/* Global notअगरy handler installed, all करोne */
	पूर्ण

	/*
	 * All Other Objects:
	 * Caller will only receive notअगरications specअगरic to the target
	 * object. Note that only certain object types are allowed to
	 * receive notअगरications.
	 */

	/* Are Notअगरies allowed on this object? */

	अगर (!acpi_ev_is_notअगरy_object(node)) अणु
		status = AE_TYPE;
		जाओ unlock_and_निकास;
	पूर्ण

	/* Check क्रम an existing पूर्णांकernal object, might not exist */

	obj_desc = acpi_ns_get_attached_object(node);
	अगर (!obj_desc) अणु

		/* Create a new object */

		obj_desc = acpi_ut_create_पूर्णांकernal_object(node->type);
		अगर (!obj_desc) अणु
			status = AE_NO_MEMORY;
			जाओ unlock_and_निकास;
		पूर्ण

		/* Attach new object to the Node, हटाओ local reference */

		status = acpi_ns_attach_object(device, obj_desc, node->type);
		acpi_ut_हटाओ_reference(obj_desc);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ unlock_and_निकास;
		पूर्ण
	पूर्ण

	/* Ensure that the handler is not alपढ़ोy installed in the lists */

	क्रम (i = 0; i < ACPI_NUM_NOTIFY_TYPES; i++) अणु
		अगर (handler_type & (i + 1)) अणु
			handler_obj = obj_desc->common_notअगरy.notअगरy_list[i];
			जबतक (handler_obj) अणु
				अगर (handler_obj->notअगरy.handler == handler) अणु
					status = AE_ALREADY_EXISTS;
					जाओ unlock_and_निकास;
				पूर्ण

				handler_obj = handler_obj->notअगरy.next[i];
			पूर्ण
		पूर्ण
	पूर्ण

	/* Create and populate a new notअगरy handler object */

	handler_obj = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_LOCAL_NOTIFY);
	अगर (!handler_obj) अणु
		status = AE_NO_MEMORY;
		जाओ unlock_and_निकास;
	पूर्ण

	handler_obj->notअगरy.node = node;
	handler_obj->notअगरy.handler_type = handler_type;
	handler_obj->notअगरy.handler = handler;
	handler_obj->notअगरy.context = context;

	/* Install the handler at the list head(s) */

	क्रम (i = 0; i < ACPI_NUM_NOTIFY_TYPES; i++) अणु
		अगर (handler_type & (i + 1)) अणु
			handler_obj->notअगरy.next[i] =
			    obj_desc->common_notअगरy.notअगरy_list[i];

			obj_desc->common_notअगरy.notअगरy_list[i] = handler_obj;
		पूर्ण
	पूर्ण

	/* Add an extra reference अगर handler was installed in both lists */

	अगर (handler_type == ACPI_ALL_NOTIFY) अणु
		acpi_ut_add_reference(handler_obj);
	पूर्ण

unlock_and_निकास:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_install_notअगरy_handler)

/*******************************************************************************
 *
 * FUNCTION:    acpi_हटाओ_notअगरy_handler
 *
 * PARAMETERS:  device          - The device क्रम which the handler is installed
 *              handler_type    - The type of handler:
 *                                  ACPI_SYSTEM_NOTIFY: System Handler (00-7F)
 *                                  ACPI_DEVICE_NOTIFY: Device Handler (80-FF)
 *                                  ACPI_ALL_NOTIFY:    Both System and Device
 *              handler         - Address of the handler
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Remove a handler क्रम notअगरies on an ACPI device
 *
 ******************************************************************************/
acpi_status
acpi_हटाओ_notअगरy_handler(acpi_handle device,
			   u32 handler_type, acpi_notअगरy_handler handler)
अणु
	काष्ठा acpi_namespace_node *node =
	    ACPI_CAST_PTR(काष्ठा acpi_namespace_node, device);
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_opeअक्रम_object *handler_obj;
	जोड़ acpi_opeअक्रम_object *previous_handler_obj;
	acpi_status status = AE_OK;
	u32 i;

	ACPI_FUNCTION_TRACE(acpi_हटाओ_notअगरy_handler);

	/* Parameter validation */

	अगर ((!device) || (!handler) || (!handler_type) ||
	    (handler_type > ACPI_MAX_NOTIFY_HANDLER_TYPE)) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Root Object. Global handlers are हटाओd here */

	अगर (device == ACPI_ROOT_OBJECT) अणु
		क्रम (i = 0; i < ACPI_NUM_NOTIFY_TYPES; i++) अणु
			अगर (handler_type & (i + 1)) अणु
				status =
				    acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
				अगर (ACPI_FAILURE(status)) अणु
					वापस_ACPI_STATUS(status);
				पूर्ण

				अगर (!acpi_gbl_global_notअगरy[i].handler ||
				    (acpi_gbl_global_notअगरy[i].handler !=
				     handler)) अणु
					status = AE_NOT_EXIST;
					जाओ unlock_and_निकास;
				पूर्ण

				ACPI_DEBUG_PRINT((ACPI_DB_INFO,
						  "Removing global notify handler\n"));

				acpi_gbl_global_notअगरy[i].handler = शून्य;
				acpi_gbl_global_notअगरy[i].context = शून्य;

				(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);

				/* Make sure all deferred notअगरy tasks are completed */

				acpi_os_रुको_events_complete();
			पूर्ण
		पूर्ण

		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* All other objects: Are Notअगरies allowed on this object? */

	अगर (!acpi_ev_is_notअगरy_object(node)) अणु
		वापस_ACPI_STATUS(AE_TYPE);
	पूर्ण

	/* Must have an existing पूर्णांकernal object */

	obj_desc = acpi_ns_get_attached_object(node);
	अगर (!obj_desc) अणु
		वापस_ACPI_STATUS(AE_NOT_EXIST);
	पूर्ण

	/* Internal object exists. Find the handler and हटाओ it */

	क्रम (i = 0; i < ACPI_NUM_NOTIFY_TYPES; i++) अणु
		अगर (handler_type & (i + 1)) अणु
			status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
			अगर (ACPI_FAILURE(status)) अणु
				वापस_ACPI_STATUS(status);
			पूर्ण

			handler_obj = obj_desc->common_notअगरy.notअगरy_list[i];
			previous_handler_obj = शून्य;

			/* Attempt to find the handler in the handler list */

			जबतक (handler_obj &&
			       (handler_obj->notअगरy.handler != handler)) अणु
				previous_handler_obj = handler_obj;
				handler_obj = handler_obj->notअगरy.next[i];
			पूर्ण

			अगर (!handler_obj) अणु
				status = AE_NOT_EXIST;
				जाओ unlock_and_निकास;
			पूर्ण

			/* Remove the handler object from the list */

			अगर (previous_handler_obj) अणु	/* Handler is not at the list head */
				previous_handler_obj->notअगरy.next[i] =
				    handler_obj->notअगरy.next[i];
			पूर्ण अन्यथा अणु	/* Handler is at the list head */

				obj_desc->common_notअगरy.notअगरy_list[i] =
				    handler_obj->notअगरy.next[i];
			पूर्ण

			(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);

			/* Make sure all deferred notअगरy tasks are completed */

			acpi_os_रुको_events_complete();
			acpi_ut_हटाओ_reference(handler_obj);
		पूर्ण
	पूर्ण

	वापस_ACPI_STATUS(status);

unlock_and_निकास:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_हटाओ_notअगरy_handler)

/*******************************************************************************
 *
 * FUNCTION:    acpi_install_exception_handler
 *
 * PARAMETERS:  handler         - Poपूर्णांकer to the handler function क्रम the
 *                                event
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Saves the poपूर्णांकer to the handler function
 *
 ******************************************************************************/
#अगर_घोषित ACPI_FUTURE_USAGE
acpi_status acpi_install_exception_handler(acpi_exception_handler handler)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_install_exception_handler);

	status = acpi_ut_acquire_mutex(ACPI_MTX_EVENTS);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Don't allow two handlers. */

	अगर (acpi_gbl_exception_handler) अणु
		status = AE_ALREADY_EXISTS;
		जाओ cleanup;
	पूर्ण

	/* Install the handler */

	acpi_gbl_exception_handler = handler;

cleanup:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_EVENTS);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_install_exception_handler)
#पूर्ण_अगर

#अगर (!ACPI_REDUCED_HARDWARE)
/*******************************************************************************
 *
 * FUNCTION:    acpi_install_sci_handler
 *
 * PARAMETERS:  address             - Address of the handler
 *              context             - Value passed to the handler on each SCI
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install a handler क्रम a System Control Interrupt.
 *
 ******************************************************************************/
acpi_status acpi_install_sci_handler(acpi_sci_handler address, व्योम *context)
अणु
	काष्ठा acpi_sci_handler_info *new_sci_handler;
	काष्ठा acpi_sci_handler_info *sci_handler;
	acpi_cpu_flags flags;
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_install_sci_handler);

	अगर (!address) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Allocate and init a handler object */

	new_sci_handler = ACPI_ALLOCATE(माप(काष्ठा acpi_sci_handler_info));
	अगर (!new_sci_handler) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	new_sci_handler->address = address;
	new_sci_handler->context = context;

	status = acpi_ut_acquire_mutex(ACPI_MTX_EVENTS);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ निकास;
	पूर्ण

	/* Lock list during installation */

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);
	sci_handler = acpi_gbl_sci_handler_list;

	/* Ensure handler करोes not alपढ़ोy exist */

	जबतक (sci_handler) अणु
		अगर (address == sci_handler->address) अणु
			status = AE_ALREADY_EXISTS;
			जाओ unlock_and_निकास;
		पूर्ण

		sci_handler = sci_handler->next;
	पूर्ण

	/* Install the new handler पूर्णांकo the global list (at head) */

	new_sci_handler->next = acpi_gbl_sci_handler_list;
	acpi_gbl_sci_handler_list = new_sci_handler;

unlock_and_निकास:

	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_EVENTS);

निकास:
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_FREE(new_sci_handler);
	पूर्ण
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_install_sci_handler)

/*******************************************************************************
 *
 * FUNCTION:    acpi_हटाओ_sci_handler
 *
 * PARAMETERS:  address             - Address of the handler
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Remove a handler क्रम a System Control Interrupt.
 *
 ******************************************************************************/
acpi_status acpi_हटाओ_sci_handler(acpi_sci_handler address)
अणु
	काष्ठा acpi_sci_handler_info *prev_sci_handler;
	काष्ठा acpi_sci_handler_info *next_sci_handler;
	acpi_cpu_flags flags;
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_हटाओ_sci_handler);

	अगर (!address) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	status = acpi_ut_acquire_mutex(ACPI_MTX_EVENTS);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Remove the SCI handler with lock */

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);

	prev_sci_handler = शून्य;
	next_sci_handler = acpi_gbl_sci_handler_list;
	जबतक (next_sci_handler) अणु
		अगर (next_sci_handler->address == address) अणु

			/* Unlink and मुक्त the SCI handler info block */

			अगर (prev_sci_handler) अणु
				prev_sci_handler->next = next_sci_handler->next;
			पूर्ण अन्यथा अणु
				acpi_gbl_sci_handler_list =
				    next_sci_handler->next;
			पूर्ण

			acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
			ACPI_FREE(next_sci_handler);
			जाओ unlock_and_निकास;
		पूर्ण

		prev_sci_handler = next_sci_handler;
		next_sci_handler = next_sci_handler->next;
	पूर्ण

	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
	status = AE_NOT_EXIST;

unlock_and_निकास:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_EVENTS);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_हटाओ_sci_handler)

/*******************************************************************************
 *
 * FUNCTION:    acpi_install_global_event_handler
 *
 * PARAMETERS:  handler         - Poपूर्णांकer to the global event handler function
 *              context         - Value passed to the handler on each event
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Saves the poपूर्णांकer to the handler function. The global handler
 *              is invoked upon each incoming GPE and Fixed Event. It is
 *              invoked at पूर्णांकerrupt level at the समय of the event dispatch.
 *              Can be used to update event counters, etc.
 *
 ******************************************************************************/
acpi_status
acpi_install_global_event_handler(acpi_gbl_event_handler handler, व्योम *context)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_install_global_event_handler);

	/* Parameter validation */

	अगर (!handler) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	status = acpi_ut_acquire_mutex(ACPI_MTX_EVENTS);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Don't allow two handlers. */

	अगर (acpi_gbl_global_event_handler) अणु
		status = AE_ALREADY_EXISTS;
		जाओ cleanup;
	पूर्ण

	acpi_gbl_global_event_handler = handler;
	acpi_gbl_global_event_handler_context = context;

cleanup:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_EVENTS);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_install_global_event_handler)

/*******************************************************************************
 *
 * FUNCTION:    acpi_install_fixed_event_handler
 *
 * PARAMETERS:  event           - Event type to enable.
 *              handler         - Poपूर्णांकer to the handler function क्रम the
 *                                event
 *              context         - Value passed to the handler on each GPE
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Saves the poपूर्णांकer to the handler function and then enables the
 *              event.
 *
 ******************************************************************************/
acpi_status
acpi_install_fixed_event_handler(u32 event,
				 acpi_event_handler handler, व्योम *context)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_install_fixed_event_handler);

	/* Parameter validation */

	अगर (event > ACPI_EVENT_MAX) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	status = acpi_ut_acquire_mutex(ACPI_MTX_EVENTS);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Do not allow multiple handlers */

	अगर (acpi_gbl_fixed_event_handlers[event].handler) अणु
		status = AE_ALREADY_EXISTS;
		जाओ cleanup;
	पूर्ण

	/* Install the handler beक्रमe enabling the event */

	acpi_gbl_fixed_event_handlers[event].handler = handler;
	acpi_gbl_fixed_event_handlers[event].context = context;

	status = acpi_clear_event(event);
	अगर (ACPI_SUCCESS(status))
		status = acpi_enable_event(event, 0);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_WARNING((AE_INFO,
			      "Could not enable fixed event - %s (%u)",
			      acpi_ut_get_event_name(event), event));

		/* Remove the handler */

		acpi_gbl_fixed_event_handlers[event].handler = शून्य;
		acpi_gbl_fixed_event_handlers[event].context = शून्य;
	पूर्ण अन्यथा अणु
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "Enabled fixed event %s (%X), Handler=%p\n",
				  acpi_ut_get_event_name(event), event,
				  handler));
	पूर्ण

cleanup:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_EVENTS);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_install_fixed_event_handler)

/*******************************************************************************
 *
 * FUNCTION:    acpi_हटाओ_fixed_event_handler
 *
 * PARAMETERS:  event           - Event type to disable.
 *              handler         - Address of the handler
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Disables the event and unरेजिस्टरs the event handler.
 *
 ******************************************************************************/
acpi_status
acpi_हटाओ_fixed_event_handler(u32 event, acpi_event_handler handler)
अणु
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(acpi_हटाओ_fixed_event_handler);

	/* Parameter validation */

	अगर (event > ACPI_EVENT_MAX) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	status = acpi_ut_acquire_mutex(ACPI_MTX_EVENTS);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Disable the event beक्रमe removing the handler */

	status = acpi_disable_event(event, 0);

	/* Always Remove the handler */

	acpi_gbl_fixed_event_handlers[event].handler = शून्य;
	acpi_gbl_fixed_event_handlers[event].context = शून्य;

	अगर (ACPI_FAILURE(status)) अणु
		ACPI_WARNING((AE_INFO,
			      "Could not disable fixed event - %s (%u)",
			      acpi_ut_get_event_name(event), event));
	पूर्ण अन्यथा अणु
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "Disabled fixed event - %s (%X)\n",
				  acpi_ut_get_event_name(event), event));
	पूर्ण

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_EVENTS);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_हटाओ_fixed_event_handler)

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_install_gpe_handler
 *
 * PARAMETERS:  gpe_device      - Namespace node क्रम the GPE (शून्य क्रम FADT
 *                                defined GPEs)
 *              gpe_number      - The GPE number within the GPE block
 *              type            - Whether this GPE should be treated as an
 *                                edge- or level-triggered पूर्णांकerrupt.
 *              is_raw_handler  - Whether this GPE should be handled using
 *                                the special GPE handler mode.
 *              address         - Address of the handler
 *              context         - Value passed to the handler on each GPE
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Internal function to install a handler क्रम a General Purpose
 *              Event.
 *
 ******************************************************************************/
अटल acpi_status
acpi_ev_install_gpe_handler(acpi_handle gpe_device,
			    u32 gpe_number,
			    u32 type,
			    u8 is_raw_handler,
			    acpi_gpe_handler address, व्योम *context)
अणु
	काष्ठा acpi_gpe_event_info *gpe_event_info;
	काष्ठा acpi_gpe_handler_info *handler;
	acpi_status status;
	acpi_cpu_flags flags;

	ACPI_FUNCTION_TRACE(ev_install_gpe_handler);

	/* Parameter validation */

	अगर ((!address) || (type & ~ACPI_GPE_XRUPT_TYPE_MASK)) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	status = acpi_ut_acquire_mutex(ACPI_MTX_EVENTS);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Allocate and init handler object (beक्रमe lock) */

	handler = ACPI_ALLOCATE_ZEROED(माप(काष्ठा acpi_gpe_handler_info));
	अगर (!handler) अणु
		status = AE_NO_MEMORY;
		जाओ unlock_and_निकास;
	पूर्ण

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);

	/* Ensure that we have a valid GPE number */

	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_number);
	अगर (!gpe_event_info) अणु
		status = AE_BAD_PARAMETER;
		जाओ मुक्त_and_निकास;
	पूर्ण

	/* Make sure that there isn't a handler there alपढ़ोy */

	अगर ((ACPI_GPE_DISPATCH_TYPE(gpe_event_info->flags) ==
	     ACPI_GPE_DISPATCH_HANDLER) ||
	    (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->flags) ==
	     ACPI_GPE_DISPATCH_RAW_HANDLER)) अणु
		status = AE_ALREADY_EXISTS;
		जाओ मुक्त_and_निकास;
	पूर्ण

	handler->address = address;
	handler->context = context;
	handler->method_node = gpe_event_info->dispatch.method_node;
	handler->original_flags = (u8)(gpe_event_info->flags &
				       (ACPI_GPE_XRUPT_TYPE_MASK |
					ACPI_GPE_DISPATCH_MASK));

	/*
	 * If the GPE is associated with a method, it may have been enabled
	 * स्वतःmatically during initialization, in which हाल it has to be
	 * disabled now to aव्योम spurious execution of the handler.
	 */
	अगर (((ACPI_GPE_DISPATCH_TYPE(handler->original_flags) ==
	      ACPI_GPE_DISPATCH_METHOD) ||
	     (ACPI_GPE_DISPATCH_TYPE(handler->original_flags) ==
	      ACPI_GPE_DISPATCH_NOTIFY)) && gpe_event_info->runसमय_count) अणु
		handler->originally_enabled = TRUE;
		(व्योम)acpi_ev_हटाओ_gpe_reference(gpe_event_info);

		/* Sanity check of original type against new type */

		अगर (type !=
		    (u32)(gpe_event_info->flags & ACPI_GPE_XRUPT_TYPE_MASK)) अणु
			ACPI_WARNING((AE_INFO,
				      "GPE type mismatch (level/edge)"));
		पूर्ण
	पूर्ण

	/* Install the handler */

	gpe_event_info->dispatch.handler = handler;

	/* Setup up dispatch flags to indicate handler (vs. method/notअगरy) */

	gpe_event_info->flags &=
	    ~(ACPI_GPE_XRUPT_TYPE_MASK | ACPI_GPE_DISPATCH_MASK);
	gpe_event_info->flags |=
	    (u8)(type |
		 (is_raw_handler ? ACPI_GPE_DISPATCH_RAW_HANDLER :
		  ACPI_GPE_DISPATCH_HANDLER));

	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);

unlock_and_निकास:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_EVENTS);
	वापस_ACPI_STATUS(status);

मुक्त_and_निकास:
	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
	ACPI_FREE(handler);
	जाओ unlock_and_निकास;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_install_gpe_handler
 *
 * PARAMETERS:  gpe_device      - Namespace node क्रम the GPE (शून्य क्रम FADT
 *                                defined GPEs)
 *              gpe_number      - The GPE number within the GPE block
 *              type            - Whether this GPE should be treated as an
 *                                edge- or level-triggered पूर्णांकerrupt.
 *              address         - Address of the handler
 *              context         - Value passed to the handler on each GPE
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install a handler क्रम a General Purpose Event.
 *
 ******************************************************************************/

acpi_status
acpi_install_gpe_handler(acpi_handle gpe_device,
			 u32 gpe_number,
			 u32 type, acpi_gpe_handler address, व्योम *context)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_install_gpe_handler);

	status = acpi_ev_install_gpe_handler(gpe_device, gpe_number, type,
					     FALSE, address, context);

	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_install_gpe_handler)

/*******************************************************************************
 *
 * FUNCTION:    acpi_install_gpe_raw_handler
 *
 * PARAMETERS:  gpe_device      - Namespace node क्रम the GPE (शून्य क्रम FADT
 *                                defined GPEs)
 *              gpe_number      - The GPE number within the GPE block
 *              type            - Whether this GPE should be treated as an
 *                                edge- or level-triggered पूर्णांकerrupt.
 *              address         - Address of the handler
 *              context         - Value passed to the handler on each GPE
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install a handler क्रम a General Purpose Event.
 *
 ******************************************************************************/
acpi_status
acpi_install_gpe_raw_handler(acpi_handle gpe_device,
			     u32 gpe_number,
			     u32 type, acpi_gpe_handler address, व्योम *context)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_install_gpe_raw_handler);

	status = acpi_ev_install_gpe_handler(gpe_device, gpe_number, type,
					     TRUE, address, context);

	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_install_gpe_raw_handler)

/*******************************************************************************
 *
 * FUNCTION:    acpi_हटाओ_gpe_handler
 *
 * PARAMETERS:  gpe_device      - Namespace node क्रम the GPE (शून्य क्रम FADT
 *                                defined GPEs)
 *              gpe_number      - The event to हटाओ a handler
 *              address         - Address of the handler
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Remove a handler क्रम a General Purpose acpi_event.
 *
 ******************************************************************************/
acpi_status
acpi_हटाओ_gpe_handler(acpi_handle gpe_device,
			u32 gpe_number, acpi_gpe_handler address)
अणु
	काष्ठा acpi_gpe_event_info *gpe_event_info;
	काष्ठा acpi_gpe_handler_info *handler;
	acpi_status status;
	acpi_cpu_flags flags;

	ACPI_FUNCTION_TRACE(acpi_हटाओ_gpe_handler);

	/* Parameter validation */

	अगर (!address) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	status = acpi_ut_acquire_mutex(ACPI_MTX_EVENTS);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);

	/* Ensure that we have a valid GPE number */

	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_number);
	अगर (!gpe_event_info) अणु
		status = AE_BAD_PARAMETER;
		जाओ unlock_and_निकास;
	पूर्ण

	/* Make sure that a handler is indeed installed */

	अगर ((ACPI_GPE_DISPATCH_TYPE(gpe_event_info->flags) !=
	     ACPI_GPE_DISPATCH_HANDLER) &&
	    (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->flags) !=
	     ACPI_GPE_DISPATCH_RAW_HANDLER)) अणु
		status = AE_NOT_EXIST;
		जाओ unlock_and_निकास;
	पूर्ण

	/* Make sure that the installed handler is the same */

	अगर (gpe_event_info->dispatch.handler->address != address) अणु
		status = AE_BAD_PARAMETER;
		जाओ unlock_and_निकास;
	पूर्ण

	/* Remove the handler */

	handler = gpe_event_info->dispatch.handler;
	gpe_event_info->dispatch.handler = शून्य;

	/* Restore Method node (अगर any), set dispatch flags */

	gpe_event_info->dispatch.method_node = handler->method_node;
	gpe_event_info->flags &=
	    ~(ACPI_GPE_XRUPT_TYPE_MASK | ACPI_GPE_DISPATCH_MASK);
	gpe_event_info->flags |= handler->original_flags;

	/*
	 * If the GPE was previously associated with a method and it was
	 * enabled, it should be enabled at this poपूर्णांक to restore the
	 * post-initialization configuration.
	 */
	अगर (((ACPI_GPE_DISPATCH_TYPE(handler->original_flags) ==
	      ACPI_GPE_DISPATCH_METHOD) ||
	     (ACPI_GPE_DISPATCH_TYPE(handler->original_flags) ==
	      ACPI_GPE_DISPATCH_NOTIFY)) && handler->originally_enabled) अणु
		(व्योम)acpi_ev_add_gpe_reference(gpe_event_info, FALSE);
		अगर (ACPI_GPE_IS_POLLING_NEEDED(gpe_event_info)) अणु

			/* Poll edge triggered GPEs to handle existing events */

			acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
			(व्योम)acpi_ev_detect_gpe(gpe_device, gpe_event_info,
						 gpe_number);
			flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);
		पूर्ण
	पूर्ण

	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_EVENTS);

	/* Make sure all deferred GPE tasks are completed */

	acpi_os_रुको_events_complete();

	/* Now we can मुक्त the handler object */

	ACPI_FREE(handler);
	वापस_ACPI_STATUS(status);

unlock_and_निकास:
	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_EVENTS);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_हटाओ_gpe_handler)

/*******************************************************************************
 *
 * FUNCTION:    acpi_acquire_global_lock
 *
 * PARAMETERS:  समयout         - How दीर्घ the caller is willing to रुको
 *              handle          - Where the handle to the lock is वापसed
 *                                (अगर acquired)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Acquire the ACPI Global Lock
 *
 * Note: Allows callers with the same thपढ़ो ID to acquire the global lock
 * multiple बार. In other words, बाह्यally, the behavior of the global lock
 * is identical to an AML mutex. On the first acquire, a new handle is
 * वापसed. On any subsequent calls to acquire by the same thपढ़ो, the same
 * handle is वापसed.
 *
 ******************************************************************************/
acpi_status acpi_acquire_global_lock(u16 समयout, u32 *handle)
अणु
	acpi_status status;

	अगर (!handle) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	/* Must lock पूर्णांकerpreter to prevent race conditions */

	acpi_ex_enter_पूर्णांकerpreter();

	status = acpi_ex_acquire_mutex_object(समयout,
					      acpi_gbl_global_lock_mutex,
					      acpi_os_get_thपढ़ो_id());

	अगर (ACPI_SUCCESS(status)) अणु

		/* Return the global lock handle (updated in acpi_ev_acquire_global_lock) */

		*handle = acpi_gbl_global_lock_handle;
	पूर्ण

	acpi_ex_निकास_पूर्णांकerpreter();
	वापस (status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_acquire_global_lock)

/*******************************************************************************
 *
 * FUNCTION:    acpi_release_global_lock
 *
 * PARAMETERS:  handle      - Returned from acpi_acquire_global_lock
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Release the ACPI Global Lock. The handle must be valid.
 *
 ******************************************************************************/
acpi_status acpi_release_global_lock(u32 handle)
अणु
	acpi_status status;

	अगर (!handle || (handle != acpi_gbl_global_lock_handle)) अणु
		वापस (AE_NOT_ACQUIRED);
	पूर्ण

	status = acpi_ex_release_mutex_object(acpi_gbl_global_lock_mutex);
	वापस (status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_release_global_lock)
#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */
