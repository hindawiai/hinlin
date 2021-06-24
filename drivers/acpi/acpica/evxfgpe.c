<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: evxfgpe - External Interfaces क्रम General Purpose Events (GPEs)
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#घोषणा EXPORT_ACPI_INTERFACES

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acevents.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_EVENTS
ACPI_MODULE_NAME("evxfgpe")

#अगर (!ACPI_REDUCED_HARDWARE)	/* Entire module */
/*******************************************************************************
 *
 * FUNCTION:    acpi_update_all_gpes
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Complete GPE initialization and enable all GPEs that have
 *              associated _Lxx or _Exx methods and are not poपूर्णांकed to by any
 *              device _PRW methods (this indicates that these GPEs are
 *              generally पूर्णांकended क्रम प्रणाली or device wakeup. Such GPEs
 *              have to be enabled directly when the devices whose _PRW
 *              methods poपूर्णांक to them are set up क्रम wakeup संकेतing.)
 *
 * NOTE: Should be called after any GPEs are added to the प्रणाली. Primarily,
 * after the प्रणाली _PRW methods have been run, but also after a GPE Block
 * Device has been added or अगर any new GPE methods have been added via a
 * dynamic table load.
 *
 ******************************************************************************/

acpi_status acpi_update_all_gpes(व्योम)
अणु
	acpi_status status;
	u8 is_polling_needed = FALSE;

	ACPI_FUNCTION_TRACE(acpi_update_all_gpes);

	status = acpi_ut_acquire_mutex(ACPI_MTX_EVENTS);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	अगर (acpi_gbl_all_gpes_initialized) अणु
		जाओ unlock_and_निकास;
	पूर्ण

	status = acpi_ev_walk_gpe_list(acpi_ev_initialize_gpe_block,
				       &is_polling_needed);
	अगर (ACPI_SUCCESS(status)) अणु
		acpi_gbl_all_gpes_initialized = TRUE;
	पूर्ण

unlock_and_निकास:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_EVENTS);

	अगर (is_polling_needed && acpi_gbl_all_gpes_initialized) अणु

		/* Poll GPEs to handle alपढ़ोy triggered events */

		acpi_ev_gpe_detect(acpi_gbl_gpe_xrupt_list_head);
	पूर्ण
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_update_all_gpes)

/*******************************************************************************
 *
 * FUNCTION:    acpi_enable_gpe
 *
 * PARAMETERS:  gpe_device          - Parent GPE Device. शून्य क्रम GPE0/GPE1
 *              gpe_number          - GPE level within the GPE block
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Add a reference to a GPE. On the first reference, the GPE is
 *              hardware-enabled.
 *
 ******************************************************************************/
acpi_status acpi_enable_gpe(acpi_handle gpe_device, u32 gpe_number)
अणु
	acpi_status status = AE_BAD_PARAMETER;
	काष्ठा acpi_gpe_event_info *gpe_event_info;
	acpi_cpu_flags flags;

	ACPI_FUNCTION_TRACE(acpi_enable_gpe);

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);

	/*
	 * Ensure that we have a valid GPE number and that there is some way
	 * of handling the GPE (handler or a GPE method). In other words, we
	 * won't allow a valid GPE to be enabled अगर there is no way to handle it.
	 */
	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_number);
	अगर (gpe_event_info) अणु
		अगर (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->flags) !=
		    ACPI_GPE_DISPATCH_NONE) अणु
			status = acpi_ev_add_gpe_reference(gpe_event_info, TRUE);
			अगर (ACPI_SUCCESS(status) &&
			    ACPI_GPE_IS_POLLING_NEEDED(gpe_event_info)) अणु

				/* Poll edge-triggered GPEs to handle existing events */

				acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
				(व्योम)acpi_ev_detect_gpe(gpe_device,
							 gpe_event_info,
							 gpe_number);
				flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);
			पूर्ण
		पूर्ण अन्यथा अणु
			status = AE_NO_HANDLER;
		पूर्ण
	पूर्ण

	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
	वापस_ACPI_STATUS(status);
पूर्ण
ACPI_EXPORT_SYMBOL(acpi_enable_gpe)

/*******************************************************************************
 *
 * FUNCTION:    acpi_disable_gpe
 *
 * PARAMETERS:  gpe_device      - Parent GPE Device. शून्य क्रम GPE0/GPE1
 *              gpe_number      - GPE level within the GPE block
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Remove a reference to a GPE. When the last reference is
 *              हटाओd, only then is the GPE disabled (क्रम runसमय GPEs), or
 *              the GPE mask bit disabled (क्रम wake GPEs)
 *
 ******************************************************************************/

acpi_status acpi_disable_gpe(acpi_handle gpe_device, u32 gpe_number)
अणु
	acpi_status status = AE_BAD_PARAMETER;
	काष्ठा acpi_gpe_event_info *gpe_event_info;
	acpi_cpu_flags flags;

	ACPI_FUNCTION_TRACE(acpi_disable_gpe);

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);

	/* Ensure that we have a valid GPE number */

	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_number);
	अगर (gpe_event_info) अणु
		status = acpi_ev_हटाओ_gpe_reference(gpe_event_info) ;
	पूर्ण

	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_disable_gpe)

/*******************************************************************************
 *
 * FUNCTION:    acpi_set_gpe
 *
 * PARAMETERS:  gpe_device          - Parent GPE Device. शून्य क्रम GPE0/GPE1
 *              gpe_number          - GPE level within the GPE block
 *              action              - ACPI_GPE_ENABLE or ACPI_GPE_DISABLE
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Enable or disable an inभागidual GPE. This function bypasses
 *              the reference count mechanism used in the acpi_enable_gpe(),
 *              acpi_disable_gpe() पूर्णांकerfaces.
 *              This API is typically used by the GPE raw handler mode driver
 *              to चयन between the polling mode and the पूर्णांकerrupt mode after
 *              the driver has enabled the GPE.
 *              The APIs should be invoked in this order:
 *               acpi_enable_gpe()            <- Ensure the reference count > 0
 *               acpi_set_gpe(ACPI_GPE_DISABLE) <- Enter polling mode
 *               acpi_set_gpe(ACPI_GPE_ENABLE) <- Leave polling mode
 *               acpi_disable_gpe()           <- Decrease the reference count
 *
 * Note: If a GPE is shared by 2 silicon components, then both the drivers
 *       should support GPE polling mode or disabling the GPE क्रम दीर्घ period
 *       क्रम one driver may अवरोध the other. So use it with care since all
 *       firmware _Lxx/_Exx handlers currently rely on the GPE पूर्णांकerrupt mode.
 *
 ******************************************************************************/
acpi_status acpi_set_gpe(acpi_handle gpe_device, u32 gpe_number, u8 action)
अणु
	काष्ठा acpi_gpe_event_info *gpe_event_info;
	acpi_status status;
	acpi_cpu_flags flags;

	ACPI_FUNCTION_TRACE(acpi_set_gpe);

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);

	/* Ensure that we have a valid GPE number */

	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_number);
	अगर (!gpe_event_info) अणु
		status = AE_BAD_PARAMETER;
		जाओ unlock_and_निकास;
	पूर्ण

	/* Perक्रमm the action */

	चयन (action) अणु
	हाल ACPI_GPE_ENABLE:

		status = acpi_hw_low_set_gpe(gpe_event_info, ACPI_GPE_ENABLE);
		gpe_event_info->disable_क्रम_dispatch = FALSE;
		अवरोध;

	हाल ACPI_GPE_DISABLE:

		status = acpi_hw_low_set_gpe(gpe_event_info, ACPI_GPE_DISABLE);
		gpe_event_info->disable_क्रम_dispatch = TRUE;
		अवरोध;

	शेष:

		status = AE_BAD_PARAMETER;
		अवरोध;
	पूर्ण

unlock_and_निकास:
	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_set_gpe)

/*******************************************************************************
 *
 * FUNCTION:    acpi_mask_gpe
 *
 * PARAMETERS:  gpe_device          - Parent GPE Device. शून्य क्रम GPE0/GPE1
 *              gpe_number          - GPE level within the GPE block
 *              is_masked           - Whether the GPE is masked or not
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Unconditionally mask/unmask the an inभागidual GPE, ex., to
 *              prevent a GPE flooding.
 *
 ******************************************************************************/
acpi_status acpi_mask_gpe(acpi_handle gpe_device, u32 gpe_number, u8 is_masked)
अणु
	काष्ठा acpi_gpe_event_info *gpe_event_info;
	acpi_status status;
	acpi_cpu_flags flags;

	ACPI_FUNCTION_TRACE(acpi_mask_gpe);

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);

	/* Ensure that we have a valid GPE number */

	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_number);
	अगर (!gpe_event_info) अणु
		status = AE_BAD_PARAMETER;
		जाओ unlock_and_निकास;
	पूर्ण

	status = acpi_ev_mask_gpe(gpe_event_info, is_masked);

unlock_and_निकास:
	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_mask_gpe)

/*******************************************************************************
 *
 * FUNCTION:    acpi_mark_gpe_क्रम_wake
 *
 * PARAMETERS:  gpe_device          - Parent GPE Device. शून्य क्रम GPE0/GPE1
 *              gpe_number          - GPE level within the GPE block
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Mark a GPE as having the ability to wake the प्रणाली. Simply
 *              sets the ACPI_GPE_CAN_WAKE flag.
 *
 * Some potential callers of acpi_setup_gpe_क्रम_wake may know in advance that
 * there won't be any notअगरy handlers installed क्रम device wake notअगरications
 * from the given GPE (one example is a button GPE in Linux). For these हालs,
 * acpi_mark_gpe_क्रम_wake should be used instead of acpi_setup_gpe_क्रम_wake.
 * This will set the ACPI_GPE_CAN_WAKE flag क्रम the GPE without trying to
 * setup implicit wake notअगरication क्रम it (since there's no handler method).
 *
 ******************************************************************************/
acpi_status acpi_mark_gpe_क्रम_wake(acpi_handle gpe_device, u32 gpe_number)
अणु
	काष्ठा acpi_gpe_event_info *gpe_event_info;
	acpi_status status = AE_BAD_PARAMETER;
	acpi_cpu_flags flags;

	ACPI_FUNCTION_TRACE(acpi_mark_gpe_क्रम_wake);

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);

	/* Ensure that we have a valid GPE number */

	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_number);
	अगर (gpe_event_info) अणु

		/* Mark the GPE as a possible wake event */

		gpe_event_info->flags |= ACPI_GPE_CAN_WAKE;
		status = AE_OK;
	पूर्ण

	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_mark_gpe_क्रम_wake)

/*******************************************************************************
 *
 * FUNCTION:    acpi_setup_gpe_क्रम_wake
 *
 * PARAMETERS:  wake_device         - Device associated with the GPE (via _PRW)
 *              gpe_device          - Parent GPE Device. शून्य क्रम GPE0/GPE1
 *              gpe_number          - GPE level within the GPE block
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Mark a GPE as having the ability to wake the प्रणाली. This
 *              पूर्णांकerface is पूर्णांकended to be used as the host executes the
 *              _PRW methods (Power Resources क्रम Wake) in the प्रणाली tables.
 *              Each _PRW appears under a Device Object (The wake_device), and
 *              contains the info क्रम the wake GPE associated with the
 *              wake_device.
 *
 ******************************************************************************/
acpi_status
acpi_setup_gpe_क्रम_wake(acpi_handle wake_device,
			acpi_handle gpe_device, u32 gpe_number)
अणु
	acpi_status status;
	काष्ठा acpi_gpe_event_info *gpe_event_info;
	काष्ठा acpi_namespace_node *device_node;
	काष्ठा acpi_gpe_notअगरy_info *notअगरy;
	काष्ठा acpi_gpe_notअगरy_info *new_notअगरy;
	acpi_cpu_flags flags;

	ACPI_FUNCTION_TRACE(acpi_setup_gpe_क्रम_wake);

	/* Parameter Validation */

	अगर (!wake_device) अणु
		/*
		 * By क्रमcing wake_device to be valid, we स्वतःmatically enable the
		 * implicit notअगरy feature on all hosts.
		 */
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Handle root object हाल */

	अगर (wake_device == ACPI_ROOT_OBJECT) अणु
		device_node = acpi_gbl_root_node;
	पूर्ण अन्यथा अणु
		device_node =
		    ACPI_CAST_PTR(काष्ठा acpi_namespace_node, wake_device);
	पूर्ण

	/* Validate wake_device is of type Device */

	अगर (device_node->type != ACPI_TYPE_DEVICE) अणु
		वापस_ACPI_STATUS (AE_BAD_PARAMETER);
	पूर्ण

	/*
	 * Allocate a new notअगरy object up front, in हाल it is needed.
	 * Memory allocation जबतक holding a spinlock is a big no-no
	 * on some hosts.
	 */
	new_notअगरy = ACPI_ALLOCATE_ZEROED(माप(काष्ठा acpi_gpe_notअगरy_info));
	अगर (!new_notअगरy) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);

	/* Ensure that we have a valid GPE number */

	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_number);
	अगर (!gpe_event_info) अणु
		status = AE_BAD_PARAMETER;
		जाओ unlock_and_निकास;
	पूर्ण

	/*
	 * If there is no method or handler क्रम this GPE, then the
	 * wake_device will be notअगरied whenever this GPE fires. This is
	 * known as an "implicit notify". Note: The GPE is assumed to be
	 * level-triggered (क्रम winकरोws compatibility).
	 */
	अगर (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->flags) ==
	    ACPI_GPE_DISPATCH_NONE) अणु
		/*
		 * This is the first device क्रम implicit notअगरy on this GPE.
		 * Just set the flags here, and enter the NOTIFY block below.
		 */
		gpe_event_info->flags =
		    (ACPI_GPE_DISPATCH_NOTIFY | ACPI_GPE_LEVEL_TRIGGERED);
	पूर्ण अन्यथा अगर (gpe_event_info->flags & ACPI_GPE_AUTO_ENABLED) अणु
		/*
		 * A reference to this GPE has been added during the GPE block
		 * initialization, so drop it now to prevent the GPE from being
		 * permanently enabled and clear its ACPI_GPE_AUTO_ENABLED flag.
		 */
		(व्योम)acpi_ev_हटाओ_gpe_reference(gpe_event_info);
		gpe_event_info->flags &= ~ACPI_GPE_AUTO_ENABLED;
	पूर्ण

	/*
	 * If we alपढ़ोy have an implicit notअगरy on this GPE, add
	 * this device to the notअगरy list.
	 */
	अगर (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->flags) ==
	    ACPI_GPE_DISPATCH_NOTIFY) अणु

		/* Ensure that the device is not alपढ़ोy in the list */

		notअगरy = gpe_event_info->dispatch.notअगरy_list;
		जबतक (notअगरy) अणु
			अगर (notअगरy->device_node == device_node) अणु
				status = AE_ALREADY_EXISTS;
				जाओ unlock_and_निकास;
			पूर्ण
			notअगरy = notअगरy->next;
		पूर्ण

		/* Add this device to the notअगरy list क्रम this GPE */

		new_notअगरy->device_node = device_node;
		new_notअगरy->next = gpe_event_info->dispatch.notअगरy_list;
		gpe_event_info->dispatch.notअगरy_list = new_notअगरy;
		new_notअगरy = शून्य;
	पूर्ण

	/* Mark the GPE as a possible wake event */

	gpe_event_info->flags |= ACPI_GPE_CAN_WAKE;
	status = AE_OK;

unlock_and_निकास:
	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);

	/* Delete the notअगरy object अगर it was not used above */

	अगर (new_notअगरy) अणु
		ACPI_FREE(new_notअगरy);
	पूर्ण
	वापस_ACPI_STATUS(status);
पूर्ण
ACPI_EXPORT_SYMBOL(acpi_setup_gpe_क्रम_wake)

/*******************************************************************************
 *
 * FUNCTION:    acpi_set_gpe_wake_mask
 *
 * PARAMETERS:  gpe_device      - Parent GPE Device. शून्य क्रम GPE0/GPE1
 *              gpe_number      - GPE level within the GPE block
 *              action              - Enable or Disable
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Set or clear the GPE's wakeup enable mask bit. The GPE must
 *              alपढ़ोy be marked as a WAKE GPE.
 *
 ******************************************************************************/

acpi_status
acpi_set_gpe_wake_mask(acpi_handle gpe_device, u32 gpe_number, u8 action)
अणु
	acpi_status status = AE_OK;
	काष्ठा acpi_gpe_event_info *gpe_event_info;
	काष्ठा acpi_gpe_रेजिस्टर_info *gpe_रेजिस्टर_info;
	acpi_cpu_flags flags;
	u32 रेजिस्टर_bit;

	ACPI_FUNCTION_TRACE(acpi_set_gpe_wake_mask);

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);

	/*
	 * Ensure that we have a valid GPE number and that this GPE is in
	 * fact a wake GPE
	 */
	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_number);
	अगर (!gpe_event_info) अणु
		status = AE_BAD_PARAMETER;
		जाओ unlock_and_निकास;
	पूर्ण

	अगर (!(gpe_event_info->flags & ACPI_GPE_CAN_WAKE)) अणु
		status = AE_TYPE;
		जाओ unlock_and_निकास;
	पूर्ण

	gpe_रेजिस्टर_info = gpe_event_info->रेजिस्टर_info;
	अगर (!gpe_रेजिस्टर_info) अणु
		status = AE_NOT_EXIST;
		जाओ unlock_and_निकास;
	पूर्ण

	रेजिस्टर_bit = acpi_hw_get_gpe_रेजिस्टर_bit(gpe_event_info);

	/* Perक्रमm the action */

	चयन (action) अणु
	हाल ACPI_GPE_ENABLE:

		ACPI_SET_BIT(gpe_रेजिस्टर_info->enable_क्रम_wake,
			     (u8)रेजिस्टर_bit);
		अवरोध;

	हाल ACPI_GPE_DISABLE:

		ACPI_CLEAR_BIT(gpe_रेजिस्टर_info->enable_क्रम_wake,
			       (u8)रेजिस्टर_bit);
		अवरोध;

	शेष:

		ACPI_ERROR((AE_INFO, "%u, Invalid action", action));
		status = AE_BAD_PARAMETER;
		अवरोध;
	पूर्ण

unlock_and_निकास:
	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_set_gpe_wake_mask)

/*******************************************************************************
 *
 * FUNCTION:    acpi_clear_gpe
 *
 * PARAMETERS:  gpe_device      - Parent GPE Device. शून्य क्रम GPE0/GPE1
 *              gpe_number      - GPE level within the GPE block
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Clear an ACPI event (general purpose)
 *
 ******************************************************************************/
acpi_status acpi_clear_gpe(acpi_handle gpe_device, u32 gpe_number)
अणु
	acpi_status status = AE_OK;
	काष्ठा acpi_gpe_event_info *gpe_event_info;
	acpi_cpu_flags flags;

	ACPI_FUNCTION_TRACE(acpi_clear_gpe);

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);

	/* Ensure that we have a valid GPE number */

	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_number);
	अगर (!gpe_event_info) अणु
		status = AE_BAD_PARAMETER;
		जाओ unlock_and_निकास;
	पूर्ण

	status = acpi_hw_clear_gpe(gpe_event_info);

      unlock_and_निकास:
	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_clear_gpe)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_gpe_status
 *
 * PARAMETERS:  gpe_device          - Parent GPE Device. शून्य क्रम GPE0/GPE1
 *              gpe_number          - GPE level within the GPE block
 *              event_status        - Where the current status of the event
 *                                    will be वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get the current status of a GPE (संकेतled/not_संकेतled)
 *
 ******************************************************************************/
acpi_status
acpi_get_gpe_status(acpi_handle gpe_device,
		    u32 gpe_number, acpi_event_status *event_status)
अणु
	acpi_status status = AE_OK;
	काष्ठा acpi_gpe_event_info *gpe_event_info;
	acpi_cpu_flags flags;

	ACPI_FUNCTION_TRACE(acpi_get_gpe_status);

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);

	/* Ensure that we have a valid GPE number */

	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_number);
	अगर (!gpe_event_info) अणु
		status = AE_BAD_PARAMETER;
		जाओ unlock_and_निकास;
	पूर्ण

	/* Obtain status on the requested GPE number */

	status = acpi_hw_get_gpe_status(gpe_event_info, event_status);

unlock_and_निकास:
	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_gpe_status)

/*******************************************************************************
 *
 * FUNCTION:    acpi_gispatch_gpe
 *
 * PARAMETERS:  gpe_device          - Parent GPE Device. शून्य क्रम GPE0/GPE1
 *              gpe_number          - GPE level within the GPE block
 *
 * RETURN:      INTERRUPT_HANDLED or INTERRUPT_NOT_HANDLED
 *
 * DESCRIPTION: Detect and dispatch a General Purpose Event to either a function
 *              (e.g. EC) or method (e.g. _Lxx/_Exx) handler.
 *
 ******************************************************************************/
u32 acpi_dispatch_gpe(acpi_handle gpe_device, u32 gpe_number)
अणु
	ACPI_FUNCTION_TRACE(acpi_dispatch_gpe);

	वापस acpi_ev_detect_gpe(gpe_device, शून्य, gpe_number);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_dispatch_gpe)

/*******************************************************************************
 *
 * FUNCTION:    acpi_finish_gpe
 *
 * PARAMETERS:  gpe_device          - Namespace node क्रम the GPE Block
 *                                    (शून्य क्रम FADT defined GPEs)
 *              gpe_number          - GPE level within the GPE block
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Clear and conditionally re-enable a GPE. This completes the GPE
 *              processing. Intended क्रम use by asynchronous host-installed
 *              GPE handlers. The GPE is only re-enabled अगर the enable_क्रम_run bit
 *              is set in the GPE info.
 *
 ******************************************************************************/
acpi_status acpi_finish_gpe(acpi_handle gpe_device, u32 gpe_number)
अणु
	काष्ठा acpi_gpe_event_info *gpe_event_info;
	acpi_status status;
	acpi_cpu_flags flags;

	ACPI_FUNCTION_TRACE(acpi_finish_gpe);

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);

	/* Ensure that we have a valid GPE number */

	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_number);
	अगर (!gpe_event_info) अणु
		status = AE_BAD_PARAMETER;
		जाओ unlock_and_निकास;
	पूर्ण

	status = acpi_ev_finish_gpe(gpe_event_info);

unlock_and_निकास:
	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_finish_gpe)

/******************************************************************************
 *
 * FUNCTION:    acpi_disable_all_gpes
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Disable and clear all GPEs in all GPE blocks
 *
 ******************************************************************************/

acpi_status acpi_disable_all_gpes(व्योम)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_disable_all_gpes);

	status = acpi_ut_acquire_mutex(ACPI_MTX_EVENTS);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	status = acpi_hw_disable_all_gpes();
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_EVENTS);

	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_disable_all_gpes)

/******************************************************************************
 *
 * FUNCTION:    acpi_enable_all_runसमय_gpes
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Enable all "runtime" GPEs, in all GPE blocks
 *
 ******************************************************************************/

acpi_status acpi_enable_all_runसमय_gpes(व्योम)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_enable_all_runसमय_gpes);

	status = acpi_ut_acquire_mutex(ACPI_MTX_EVENTS);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	status = acpi_hw_enable_all_runसमय_gpes();
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_EVENTS);

	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_enable_all_runसमय_gpes)

/******************************************************************************
 *
 * FUNCTION:    acpi_enable_all_wakeup_gpes
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Enable all "wakeup" GPEs and disable all of the other GPEs, in
 *              all GPE blocks.
 *
 ******************************************************************************/
acpi_status acpi_enable_all_wakeup_gpes(व्योम)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_enable_all_wakeup_gpes);

	status = acpi_ut_acquire_mutex(ACPI_MTX_EVENTS);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	status = acpi_hw_enable_all_wakeup_gpes();
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_EVENTS);

	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_enable_all_wakeup_gpes)

/******************************************************************************
 *
 * FUNCTION:    acpi_any_gpe_status_set
 *
 * PARAMETERS:  gpe_skip_number      - Number of the GPE to skip
 *
 * RETURN:      Whether or not the status bit is set क्रम any GPE
 *
 * DESCRIPTION: Check the status bits of all enabled GPEs, except क्रम the one
 *              represented by the "skip" argument, and वापस TRUE अगर any of
 *              them is set or FALSE otherwise.
 *
 ******************************************************************************/
u32 acpi_any_gpe_status_set(u32 gpe_skip_number)
अणु
	acpi_status status;
	acpi_handle gpe_device;
	u8 ret;

	ACPI_FUNCTION_TRACE(acpi_any_gpe_status_set);

	status = acpi_ut_acquire_mutex(ACPI_MTX_EVENTS);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (FALSE);
	पूर्ण

	status = acpi_get_gpe_device(gpe_skip_number, &gpe_device);
	अगर (ACPI_FAILURE(status)) अणु
		gpe_device = शून्य;
	पूर्ण

	ret = acpi_hw_check_all_gpes(gpe_device, gpe_skip_number);
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_EVENTS);

	वापस (ret);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_any_gpe_status_set)

/*******************************************************************************
 *
 * FUNCTION:    acpi_install_gpe_block
 *
 * PARAMETERS:  gpe_device          - Handle to the parent GPE Block Device
 *              gpe_block_address   - Address and space_ID
 *              रेजिस्टर_count      - Number of GPE रेजिस्टर pairs in the block
 *              पूर्णांकerrupt_number    - H/W पूर्णांकerrupt क्रम the block
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create and Install a block of GPE रेजिस्टरs. The GPEs are not
 *              enabled here.
 *
 ******************************************************************************/
acpi_status
acpi_install_gpe_block(acpi_handle gpe_device,
		       काष्ठा acpi_generic_address *gpe_block_address,
		       u32 रेजिस्टर_count, u32 पूर्णांकerrupt_number)
अणु
	acpi_status status;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	काष्ठा acpi_namespace_node *node;
	काष्ठा acpi_gpe_block_info *gpe_block;

	ACPI_FUNCTION_TRACE(acpi_install_gpe_block);

	अगर ((!gpe_device) || (!gpe_block_address) || (!रेजिस्टर_count)) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	node = acpi_ns_validate_handle(gpe_device);
	अगर (!node) अणु
		status = AE_BAD_PARAMETER;
		जाओ unlock_and_निकास;
	पूर्ण

	/* Validate the parent device */

	अगर (node->type != ACPI_TYPE_DEVICE) अणु
		status = AE_TYPE;
		जाओ unlock_and_निकास;
	पूर्ण

	अगर (node->object) अणु
		status = AE_ALREADY_EXISTS;
		जाओ unlock_and_निकास;
	पूर्ण

	/*
	 * For user-installed GPE Block Devices, the gpe_block_base_number
	 * is always zero
	 */
	status = acpi_ev_create_gpe_block(node, gpe_block_address->address,
					  gpe_block_address->space_id,
					  रेजिस्टर_count, 0, पूर्णांकerrupt_number,
					  &gpe_block);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ unlock_and_निकास;
	पूर्ण

	/* Install block in the device_object attached to the node */

	obj_desc = acpi_ns_get_attached_object(node);
	अगर (!obj_desc) अणु

		/*
		 * No object, create a new one (Device nodes करो not always have
		 * an attached object)
		 */
		obj_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_DEVICE);
		अगर (!obj_desc) अणु
			status = AE_NO_MEMORY;
			जाओ unlock_and_निकास;
		पूर्ण

		status =
		    acpi_ns_attach_object(node, obj_desc, ACPI_TYPE_DEVICE);

		/* Remove local reference to the object */

		acpi_ut_हटाओ_reference(obj_desc);

		अगर (ACPI_FAILURE(status)) अणु
			जाओ unlock_and_निकास;
		पूर्ण
	पूर्ण

	/* Now install the GPE block in the device_object */

	obj_desc->device.gpe_block = gpe_block;

unlock_and_निकास:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_install_gpe_block)

/*******************************************************************************
 *
 * FUNCTION:    acpi_हटाओ_gpe_block
 *
 * PARAMETERS:  gpe_device          - Handle to the parent GPE Block Device
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Remove a previously installed block of GPE रेजिस्टरs
 *
 ******************************************************************************/
acpi_status acpi_हटाओ_gpe_block(acpi_handle gpe_device)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	acpi_status status;
	काष्ठा acpi_namespace_node *node;

	ACPI_FUNCTION_TRACE(acpi_हटाओ_gpe_block);

	अगर (!gpe_device) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	node = acpi_ns_validate_handle(gpe_device);
	अगर (!node) अणु
		status = AE_BAD_PARAMETER;
		जाओ unlock_and_निकास;
	पूर्ण

	/* Validate the parent device */

	अगर (node->type != ACPI_TYPE_DEVICE) अणु
		status = AE_TYPE;
		जाओ unlock_and_निकास;
	पूर्ण

	/* Get the device_object attached to the node */

	obj_desc = acpi_ns_get_attached_object(node);
	अगर (!obj_desc || !obj_desc->device.gpe_block) अणु
		वापस_ACPI_STATUS(AE_शून्य_OBJECT);
	पूर्ण

	/* Delete the GPE block (but not the device_object) */

	status = acpi_ev_delete_gpe_block(obj_desc->device.gpe_block);
	अगर (ACPI_SUCCESS(status)) अणु
		obj_desc->device.gpe_block = शून्य;
	पूर्ण

unlock_and_निकास:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_हटाओ_gpe_block)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_gpe_device
 *
 * PARAMETERS:  index               - System GPE index (0-current_gpe_count)
 *              gpe_device          - Where the parent GPE Device is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Obtain the GPE device associated with the input index. A शून्य
 *              gpe device indicates that the gpe number is contained in one of
 *              the FADT-defined gpe blocks. Otherwise, the GPE block device.
 *
 ******************************************************************************/
acpi_status acpi_get_gpe_device(u32 index, acpi_handle *gpe_device)
अणु
	काष्ठा acpi_gpe_device_info info;
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_get_gpe_device);

	अगर (!gpe_device) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	अगर (index >= acpi_current_gpe_count) अणु
		वापस_ACPI_STATUS(AE_NOT_EXIST);
	पूर्ण

	/* Setup and walk the GPE list */

	info.index = index;
	info.status = AE_NOT_EXIST;
	info.gpe_device = शून्य;
	info.next_block_base_index = 0;

	status = acpi_ev_walk_gpe_list(acpi_ev_get_gpe_device, &info);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	*gpe_device = ACPI_CAST_PTR(acpi_handle, info.gpe_device);
	वापस_ACPI_STATUS(info.status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_gpe_device)
#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */
