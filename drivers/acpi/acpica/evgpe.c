<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: evgpe - General Purpose Event handling and dispatch
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acevents.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_EVENTS
ACPI_MODULE_NAME("evgpe")
#अगर (!ACPI_REDUCED_HARDWARE)	/* Entire module */
/* Local prototypes */
अटल व्योम ACPI_SYSTEM_XFACE acpi_ev_asynch_execute_gpe_method(व्योम *context);

अटल व्योम ACPI_SYSTEM_XFACE acpi_ev_asynch_enable_gpe(व्योम *context);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_update_gpe_enable_mask
 *
 * PARAMETERS:  gpe_event_info          - GPE to update
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Updates GPE रेजिस्टर enable mask based upon whether there are
 *              runसमय references to this GPE
 *
 ******************************************************************************/

acpi_status
acpi_ev_update_gpe_enable_mask(काष्ठा acpi_gpe_event_info *gpe_event_info)
अणु
	काष्ठा acpi_gpe_रेजिस्टर_info *gpe_रेजिस्टर_info;
	u32 रेजिस्टर_bit;

	ACPI_FUNCTION_TRACE(ev_update_gpe_enable_mask);

	gpe_रेजिस्टर_info = gpe_event_info->रेजिस्टर_info;
	अगर (!gpe_रेजिस्टर_info) अणु
		वापस_ACPI_STATUS(AE_NOT_EXIST);
	पूर्ण

	रेजिस्टर_bit = acpi_hw_get_gpe_रेजिस्टर_bit(gpe_event_info);

	/* Clear the run bit up front */

	ACPI_CLEAR_BIT(gpe_रेजिस्टर_info->enable_क्रम_run, रेजिस्टर_bit);

	/* Set the mask bit only अगर there are references to this GPE */

	अगर (gpe_event_info->runसमय_count) अणु
		ACPI_SET_BIT(gpe_रेजिस्टर_info->enable_क्रम_run,
			     (u8)रेजिस्टर_bit);
	पूर्ण

	gpe_रेजिस्टर_info->enable_mask = gpe_रेजिस्टर_info->enable_क्रम_run;
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_enable_gpe
 *
 * PARAMETERS:  gpe_event_info          - GPE to enable
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Enable a GPE.
 *
 ******************************************************************************/

acpi_status acpi_ev_enable_gpe(काष्ठा acpi_gpe_event_info *gpe_event_info)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(ev_enable_gpe);

	/* Enable the requested GPE */

	status = acpi_hw_low_set_gpe(gpe_event_info, ACPI_GPE_ENABLE);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_mask_gpe
 *
 * PARAMETERS:  gpe_event_info          - GPE to be blocked/unblocked
 *              is_masked               - Whether the GPE is masked or not
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Unconditionally mask/unmask a GPE during runसमय.
 *
 ******************************************************************************/

acpi_status
acpi_ev_mask_gpe(काष्ठा acpi_gpe_event_info *gpe_event_info, u8 is_masked)
अणु
	काष्ठा acpi_gpe_रेजिस्टर_info *gpe_रेजिस्टर_info;
	u32 रेजिस्टर_bit;

	ACPI_FUNCTION_TRACE(ev_mask_gpe);

	gpe_रेजिस्टर_info = gpe_event_info->रेजिस्टर_info;
	अगर (!gpe_रेजिस्टर_info) अणु
		वापस_ACPI_STATUS(AE_NOT_EXIST);
	पूर्ण

	रेजिस्टर_bit = acpi_hw_get_gpe_रेजिस्टर_bit(gpe_event_info);

	/* Perक्रमm the action */

	अगर (is_masked) अणु
		अगर (रेजिस्टर_bit & gpe_रेजिस्टर_info->mask_क्रम_run) अणु
			वापस_ACPI_STATUS(AE_BAD_PARAMETER);
		पूर्ण

		(व्योम)acpi_hw_low_set_gpe(gpe_event_info, ACPI_GPE_DISABLE);
		ACPI_SET_BIT(gpe_रेजिस्टर_info->mask_क्रम_run, (u8)रेजिस्टर_bit);
	पूर्ण अन्यथा अणु
		अगर (!(रेजिस्टर_bit & gpe_रेजिस्टर_info->mask_क्रम_run)) अणु
			वापस_ACPI_STATUS(AE_BAD_PARAMETER);
		पूर्ण

		ACPI_CLEAR_BIT(gpe_रेजिस्टर_info->mask_क्रम_run,
			       (u8)रेजिस्टर_bit);
		अगर (gpe_event_info->runसमय_count
		    && !gpe_event_info->disable_क्रम_dispatch) अणु
			(व्योम)acpi_hw_low_set_gpe(gpe_event_info,
						  ACPI_GPE_ENABLE);
		पूर्ण
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_add_gpe_reference
 *
 * PARAMETERS:  gpe_event_info          - Add a reference to this GPE
 *              clear_on_enable         - Clear GPE status beक्रमe enabling it
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Add a reference to a GPE. On the first reference, the GPE is
 *              hardware-enabled.
 *
 ******************************************************************************/

acpi_status
acpi_ev_add_gpe_reference(काष्ठा acpi_gpe_event_info *gpe_event_info,
			  u8 clear_on_enable)
अणु
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ev_add_gpe_reference);

	अगर (gpe_event_info->runसमय_count == ACPI_UINT8_MAX) अणु
		वापस_ACPI_STATUS(AE_LIMIT);
	पूर्ण

	gpe_event_info->runसमय_count++;
	अगर (gpe_event_info->runसमय_count == 1) अणु

		/* Enable on first reference */

		अगर (clear_on_enable) अणु
			(व्योम)acpi_hw_clear_gpe(gpe_event_info);
		पूर्ण

		status = acpi_ev_update_gpe_enable_mask(gpe_event_info);
		अगर (ACPI_SUCCESS(status)) अणु
			status = acpi_ev_enable_gpe(gpe_event_info);
		पूर्ण

		अगर (ACPI_FAILURE(status)) अणु
			gpe_event_info->runसमय_count--;
		पूर्ण
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_हटाओ_gpe_reference
 *
 * PARAMETERS:  gpe_event_info          - Remove a reference to this GPE
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Remove a reference to a GPE. When the last reference is
 *              हटाओd, the GPE is hardware-disabled.
 *
 ******************************************************************************/

acpi_status
acpi_ev_हटाओ_gpe_reference(काष्ठा acpi_gpe_event_info *gpe_event_info)
अणु
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ev_हटाओ_gpe_reference);

	अगर (!gpe_event_info->runसमय_count) अणु
		वापस_ACPI_STATUS(AE_LIMIT);
	पूर्ण

	gpe_event_info->runसमय_count--;
	अगर (!gpe_event_info->runसमय_count) अणु

		/* Disable on last reference */

		status = acpi_ev_update_gpe_enable_mask(gpe_event_info);
		अगर (ACPI_SUCCESS(status)) अणु
			status =
			    acpi_hw_low_set_gpe(gpe_event_info,
						ACPI_GPE_DISABLE);
		पूर्ण

		अगर (ACPI_FAILURE(status)) अणु
			gpe_event_info->runसमय_count++;
		पूर्ण
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_low_get_gpe_info
 *
 * PARAMETERS:  gpe_number          - Raw GPE number
 *              gpe_block           - A GPE info block
 *
 * RETURN:      A GPE event_info काष्ठा. शून्य अगर not a valid GPE (The gpe_number
 *              is not within the specअगरied GPE block)
 *
 * DESCRIPTION: Returns the event_info काष्ठा associated with this GPE. This is
 *              the low-level implementation of ev_get_gpe_event_info.
 *
 ******************************************************************************/

काष्ठा acpi_gpe_event_info *acpi_ev_low_get_gpe_info(u32 gpe_number,
						     काष्ठा acpi_gpe_block_info
						     *gpe_block)
अणु
	u32 gpe_index;

	/*
	 * Validate that the gpe_number is within the specअगरied gpe_block.
	 * (Two steps)
	 */
	अगर (!gpe_block || (gpe_number < gpe_block->block_base_number)) अणु
		वापस (शून्य);
	पूर्ण

	gpe_index = gpe_number - gpe_block->block_base_number;
	अगर (gpe_index >= gpe_block->gpe_count) अणु
		वापस (शून्य);
	पूर्ण

	वापस (&gpe_block->event_info[gpe_index]);
पूर्ण


/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_get_gpe_event_info
 *
 * PARAMETERS:  gpe_device          - Device node. शून्य क्रम GPE0/GPE1
 *              gpe_number          - Raw GPE number
 *
 * RETURN:      A GPE event_info काष्ठा. शून्य अगर not a valid GPE
 *
 * DESCRIPTION: Returns the event_info काष्ठा associated with this GPE.
 *              Validates the gpe_block and the gpe_number
 *
 *              Should be called only when the GPE lists are semaphore locked
 *              and not subject to change.
 *
 ******************************************************************************/

काष्ठा acpi_gpe_event_info *acpi_ev_get_gpe_event_info(acpi_handle gpe_device,
						       u32 gpe_number)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	काष्ठा acpi_gpe_event_info *gpe_info;
	u32 i;

	ACPI_FUNCTION_ENTRY();

	/* A शून्य gpe_device means use the FADT-defined GPE block(s) */

	अगर (!gpe_device) अणु

		/* Examine GPE Block 0 and 1 (These blocks are permanent) */

		क्रम (i = 0; i < ACPI_MAX_GPE_BLOCKS; i++) अणु
			gpe_info = acpi_ev_low_get_gpe_info(gpe_number,
							    acpi_gbl_gpe_fadt_blocks
							    [i]);
			अगर (gpe_info) अणु
				वापस (gpe_info);
			पूर्ण
		पूर्ण

		/* The gpe_number was not in the range of either FADT GPE block */

		वापस (शून्य);
	पूर्ण

	/* A Non-शून्य gpe_device means this is a GPE Block Device */

	obj_desc =
	    acpi_ns_get_attached_object((काष्ठा acpi_namespace_node *)
					       gpe_device);
	अगर (!obj_desc || !obj_desc->device.gpe_block) अणु
		वापस (शून्य);
	पूर्ण

	वापस (acpi_ev_low_get_gpe_info
		(gpe_number, obj_desc->device.gpe_block));
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_gpe_detect
 *
 * PARAMETERS:  gpe_xrupt_list      - Interrupt block क्रम this पूर्णांकerrupt.
 *                                    Can have multiple GPE blocks attached.
 *
 * RETURN:      INTERRUPT_HANDLED or INTERRUPT_NOT_HANDLED
 *
 * DESCRIPTION: Detect अगर any GP events have occurred. This function is
 *              executed at पूर्णांकerrupt level.
 *
 ******************************************************************************/

u32 acpi_ev_gpe_detect(काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_list)
अणु
	काष्ठा acpi_gpe_block_info *gpe_block;
	काष्ठा acpi_namespace_node *gpe_device;
	काष्ठा acpi_gpe_रेजिस्टर_info *gpe_रेजिस्टर_info;
	काष्ठा acpi_gpe_event_info *gpe_event_info;
	u32 gpe_number;
	u32 पूर्णांक_status = ACPI_INTERRUPT_NOT_HANDLED;
	acpi_cpu_flags flags;
	u32 i;
	u32 j;

	ACPI_FUNCTION_NAME(ev_gpe_detect);

	/* Check क्रम the हाल where there are no GPEs */

	अगर (!gpe_xrupt_list) अणु
		वापस (पूर्णांक_status);
	पूर्ण

	/*
	 * We need to obtain the GPE lock क्रम both the data काष्ठाs and रेजिस्टरs
	 * Note: Not necessary to obtain the hardware lock, since the GPE
	 * रेजिस्टरs are owned by the gpe_lock.
	 */
	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);

	/* Examine all GPE blocks attached to this पूर्णांकerrupt level */

	gpe_block = gpe_xrupt_list->gpe_block_list_head;
	जबतक (gpe_block) अणु
		gpe_device = gpe_block->node;

		/*
		 * Read all of the 8-bit GPE status and enable रेजिस्टरs in this GPE
		 * block, saving all of them. Find all currently active GP events.
		 */
		क्रम (i = 0; i < gpe_block->रेजिस्टर_count; i++) अणु

			/* Get the next status/enable pair */

			gpe_रेजिस्टर_info = &gpe_block->रेजिस्टर_info[i];

			/*
			 * Optimization: If there are no GPEs enabled within this
			 * रेजिस्टर, we can safely ignore the entire रेजिस्टर.
			 */
			अगर (!(gpe_रेजिस्टर_info->enable_क्रम_run |
			      gpe_रेजिस्टर_info->enable_क्रम_wake)) अणु
				ACPI_DEBUG_PRINT((ACPI_DB_INTERRUPTS,
						  "Ignore disabled registers for GPE %02X-%02X: "
						  "RunEnable=%02X, WakeEnable=%02X\n",
						  gpe_रेजिस्टर_info->
						  base_gpe_number,
						  gpe_रेजिस्टर_info->
						  base_gpe_number +
						  (ACPI_GPE_REGISTER_WIDTH - 1),
						  gpe_रेजिस्टर_info->
						  enable_क्रम_run,
						  gpe_रेजिस्टर_info->
						  enable_क्रम_wake));
				जारी;
			पूर्ण

			/* Now look at the inभागidual GPEs in this byte रेजिस्टर */

			क्रम (j = 0; j < ACPI_GPE_REGISTER_WIDTH; j++) अणु

				/* Detect and dispatch one GPE bit */

				gpe_event_info =
				    &gpe_block->
				    event_info[((acpi_size)i *
						ACPI_GPE_REGISTER_WIDTH) + j];
				gpe_number =
				    j + gpe_रेजिस्टर_info->base_gpe_number;
				acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
				पूर्णांक_status |=
				    acpi_ev_detect_gpe(gpe_device,
						       gpe_event_info,
						       gpe_number);
				flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);
			पूर्ण
		पूर्ण

		gpe_block = gpe_block->next;
	पूर्ण

	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
	वापस (पूर्णांक_status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_asynch_execute_gpe_method
 *
 * PARAMETERS:  Context (gpe_event_info) - Info क्रम this GPE
 *
 * RETURN:      None
 *
 * DESCRIPTION: Perक्रमm the actual execution of a GPE control method. This
 *              function is called from an invocation of acpi_os_execute and
 *              thereक्रमe करोes NOT execute at पूर्णांकerrupt level - so that
 *              the control method itself is not executed in the context of
 *              an पूर्णांकerrupt handler.
 *
 ******************************************************************************/

अटल व्योम ACPI_SYSTEM_XFACE acpi_ev_asynch_execute_gpe_method(व्योम *context)
अणु
	काष्ठा acpi_gpe_event_info *gpe_event_info = context;
	acpi_status status = AE_OK;
	काष्ठा acpi_evaluate_info *info;
	काष्ठा acpi_gpe_notअगरy_info *notअगरy;

	ACPI_FUNCTION_TRACE(ev_asynch_execute_gpe_method);

	/* Do the correct dispatch - normal method or implicit notअगरy */

	चयन (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->flags)) अणु
	हाल ACPI_GPE_DISPATCH_NOTIFY:
		/*
		 * Implicit notअगरy.
		 * Dispatch a DEVICE_WAKE notअगरy to the appropriate handler.
		 * NOTE: the request is queued क्रम execution after this method
		 * completes. The notअगरy handlers are NOT invoked synchronously
		 * from this thपढ़ो -- because handlers may in turn run other
		 * control methods.
		 *
		 * June 2012: Expand implicit notअगरy mechanism to support
		 * notअगरies on multiple device objects.
		 */
		notअगरy = gpe_event_info->dispatch.notअगरy_list;
		जबतक (ACPI_SUCCESS(status) && notअगरy) अणु
			status =
			    acpi_ev_queue_notअगरy_request(notअगरy->device_node,
							 ACPI_NOTIFY_DEVICE_WAKE);

			notअगरy = notअगरy->next;
		पूर्ण

		अवरोध;

	हाल ACPI_GPE_DISPATCH_METHOD:

		/* Allocate the evaluation inक्रमmation block */

		info = ACPI_ALLOCATE_ZEROED(माप(काष्ठा acpi_evaluate_info));
		अगर (!info) अणु
			status = AE_NO_MEMORY;
		पूर्ण अन्यथा अणु
			/*
			 * Invoke the GPE Method (_Lxx, _Exx) i.e., evaluate the
			 * _Lxx/_Exx control method that corresponds to this GPE
			 */
			info->prefix_node =
			    gpe_event_info->dispatch.method_node;
			info->flags = ACPI_IGNORE_RETURN_VALUE;

			status = acpi_ns_evaluate(info);
			ACPI_FREE(info);
		पूर्ण

		अगर (ACPI_FAILURE(status)) अणु
			ACPI_EXCEPTION((AE_INFO, status,
					"while evaluating GPE method [%4.4s]",
					acpi_ut_get_node_name(gpe_event_info->
							      dispatch.
							      method_node)));
		पूर्ण
		अवरोध;

	शेष:

		जाओ error_निकास;	/* Should never happen */
	पूर्ण

	/* Defer enabling of GPE until all notअगरy handlers are करोne */

	status = acpi_os_execute(OSL_NOTIFY_HANDLER,
				 acpi_ev_asynch_enable_gpe, gpe_event_info);
	अगर (ACPI_SUCCESS(status)) अणु
		वापस_VOID;
	पूर्ण

error_निकास:
	acpi_ev_asynch_enable_gpe(gpe_event_info);
	वापस_VOID;
पूर्ण


/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_asynch_enable_gpe
 *
 * PARAMETERS:  Context (gpe_event_info) - Info क्रम this GPE
 *              Callback from acpi_os_execute
 *
 * RETURN:      None
 *
 * DESCRIPTION: Asynchronous clear/enable क्रम GPE. This allows the GPE to
 *              complete (i.e., finish execution of Notअगरy)
 *
 ******************************************************************************/

अटल व्योम ACPI_SYSTEM_XFACE acpi_ev_asynch_enable_gpe(व्योम *context)
अणु
	काष्ठा acpi_gpe_event_info *gpe_event_info = context;
	acpi_cpu_flags flags;

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);
	(व्योम)acpi_ev_finish_gpe(gpe_event_info);
	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);

	वापस;
पूर्ण


/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_finish_gpe
 *
 * PARAMETERS:  gpe_event_info      - Info क्रम this GPE
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Clear/Enable a GPE. Common code that is used after execution
 *              of a GPE method or a synchronous or asynchronous GPE handler.
 *
 ******************************************************************************/

acpi_status acpi_ev_finish_gpe(काष्ठा acpi_gpe_event_info *gpe_event_info)
अणु
	acpi_status status;

	अगर ((gpe_event_info->flags & ACPI_GPE_XRUPT_TYPE_MASK) ==
	    ACPI_GPE_LEVEL_TRIGGERED) अणु
		/*
		 * GPE is level-triggered, we clear the GPE status bit after
		 * handling the event.
		 */
		status = acpi_hw_clear_gpe(gpe_event_info);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण
	पूर्ण

	/*
	 * Enable this GPE, conditionally. This means that the GPE will
	 * only be physically enabled अगर the enable_mask bit is set
	 * in the event_info.
	 */
	(व्योम)acpi_hw_low_set_gpe(gpe_event_info, ACPI_GPE_CONDITIONAL_ENABLE);
	gpe_event_info->disable_क्रम_dispatch = FALSE;
	वापस (AE_OK);
पूर्ण


/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_detect_gpe
 *
 * PARAMETERS:  gpe_device          - Device node. शून्य क्रम GPE0/GPE1
 *              gpe_event_info      - Info क्रम this GPE
 *              gpe_number          - Number relative to the parent GPE block
 *
 * RETURN:      INTERRUPT_HANDLED or INTERRUPT_NOT_HANDLED
 *
 * DESCRIPTION: Detect and dispatch a General Purpose Event to either a function
 *              (e.g. EC) or method (e.g. _Lxx/_Exx) handler.
 * NOTE:        GPE is W1C, so it is possible to handle a single GPE from both
 *              task and irq context in parallel as दीर्घ as the process to
 *              detect and mask the GPE is atomic.
 *              However the atomicity of ACPI_GPE_DISPATCH_RAW_HANDLER is
 *              dependent on the raw handler itself.
 *
 ******************************************************************************/

u32
acpi_ev_detect_gpe(काष्ठा acpi_namespace_node *gpe_device,
		   काष्ठा acpi_gpe_event_info *gpe_event_info, u32 gpe_number)
अणु
	u32 पूर्णांक_status = ACPI_INTERRUPT_NOT_HANDLED;
	u8 enabled_status_byte;
	u64 status_reg;
	u64 enable_reg;
	u32 रेजिस्टर_bit;
	काष्ठा acpi_gpe_रेजिस्टर_info *gpe_रेजिस्टर_info;
	काष्ठा acpi_gpe_handler_info *gpe_handler_info;
	acpi_cpu_flags flags;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ev_gpe_detect);

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);

	अगर (!gpe_event_info) अणु
		gpe_event_info = acpi_ev_get_gpe_event_info(gpe_device, gpe_number);
		अगर (!gpe_event_info)
			जाओ error_निकास;
	पूर्ण

	/* Get the info block क्रम the entire GPE रेजिस्टर */

	gpe_रेजिस्टर_info = gpe_event_info->रेजिस्टर_info;

	/* Get the रेजिस्टर biपंचांगask क्रम this GPE */

	रेजिस्टर_bit = acpi_hw_get_gpe_रेजिस्टर_bit(gpe_event_info);

	/* GPE currently enabled (enable bit == 1)? */

	status = acpi_hw_gpe_पढ़ो(&enable_reg, &gpe_रेजिस्टर_info->enable_address);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ error_निकास;
	पूर्ण

	/* GPE currently active (status bit == 1)? */

	status = acpi_hw_gpe_पढ़ो(&status_reg, &gpe_रेजिस्टर_info->status_address);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ error_निकास;
	पूर्ण

	/* Check अगर there is anything active at all in this GPE */

	ACPI_DEBUG_PRINT((ACPI_DB_INTERRUPTS,
			  "Read registers for GPE %02X: Status=%02X, Enable=%02X, "
			  "RunEnable=%02X, WakeEnable=%02X\n",
			  gpe_number,
			  (u32)(status_reg & रेजिस्टर_bit),
			  (u32)(enable_reg & रेजिस्टर_bit),
			  gpe_रेजिस्टर_info->enable_क्रम_run,
			  gpe_रेजिस्टर_info->enable_क्रम_wake));

	enabled_status_byte = (u8)(status_reg & enable_reg);
	अगर (!(enabled_status_byte & रेजिस्टर_bit)) अणु
		जाओ error_निकास;
	पूर्ण

	/* Invoke global event handler अगर present */

	acpi_gpe_count++;
	अगर (acpi_gbl_global_event_handler) अणु
		acpi_gbl_global_event_handler(ACPI_EVENT_TYPE_GPE,
					      gpe_device, gpe_number,
					      acpi_gbl_global_event_handler_context);
	पूर्ण

	/* Found an active GPE */

	अगर (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->flags) ==
	    ACPI_GPE_DISPATCH_RAW_HANDLER) अणु

		/* Dispatch the event to a raw handler */

		gpe_handler_info = gpe_event_info->dispatch.handler;

		/*
		 * There is no protection around the namespace node
		 * and the GPE handler to ensure a safe deकाष्ठाion
		 * because:
		 * 1. The namespace node is expected to always
		 *    exist after loading a table.
		 * 2. The GPE handler is expected to be flushed by
		 *    acpi_os_रुको_events_complete() beक्रमe the
		 *    deकाष्ठाion.
		 */
		acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
		पूर्णांक_status |=
		    gpe_handler_info->address(gpe_device, gpe_number,
					      gpe_handler_info->context);
		flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);
	पूर्ण अन्यथा अणु
		/* Dispatch the event to a standard handler or method. */

		पूर्णांक_status |= acpi_ev_gpe_dispatch(gpe_device,
						   gpe_event_info, gpe_number);
	पूर्ण

error_निकास:
	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
	वापस (पूर्णांक_status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_gpe_dispatch
 *
 * PARAMETERS:  gpe_device          - Device node. शून्य क्रम GPE0/GPE1
 *              gpe_event_info      - Info क्रम this GPE
 *              gpe_number          - Number relative to the parent GPE block
 *
 * RETURN:      INTERRUPT_HANDLED or INTERRUPT_NOT_HANDLED
 *
 * DESCRIPTION: Dispatch a General Purpose Event to either a function (e.g. EC)
 *              or method (e.g. _Lxx/_Exx) handler.
 *
 ******************************************************************************/

u32
acpi_ev_gpe_dispatch(काष्ठा acpi_namespace_node *gpe_device,
		     काष्ठा acpi_gpe_event_info *gpe_event_info, u32 gpe_number)
अणु
	acpi_status status;
	u32 वापस_value;

	ACPI_FUNCTION_TRACE(ev_gpe_dispatch);

	/*
	 * Always disable the GPE so that it करोes not keep firing beक्रमe
	 * any asynchronous activity completes (either from the execution
	 * of a GPE method or an asynchronous GPE handler.)
	 *
	 * If there is no handler or method to run, just disable the
	 * GPE and leave it disabled permanently to prevent further such
	 * poपूर्णांकless events from firing.
	 */
	status = acpi_hw_low_set_gpe(gpe_event_info, ACPI_GPE_DISABLE);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_EXCEPTION((AE_INFO, status,
				"Unable to disable GPE %02X", gpe_number));
		वापस_UINT32(ACPI_INTERRUPT_NOT_HANDLED);
	पूर्ण

	/*
	 * If edge-triggered, clear the GPE status bit now. Note that
	 * level-triggered events are cleared after the GPE is serviced.
	 */
	अगर ((gpe_event_info->flags & ACPI_GPE_XRUPT_TYPE_MASK) ==
	    ACPI_GPE_EDGE_TRIGGERED) अणु
		status = acpi_hw_clear_gpe(gpe_event_info);
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_EXCEPTION((AE_INFO, status,
					"Unable to clear GPE %02X",
					gpe_number));
			(व्योम)acpi_hw_low_set_gpe(gpe_event_info,
						  ACPI_GPE_CONDITIONAL_ENABLE);
			वापस_UINT32(ACPI_INTERRUPT_NOT_HANDLED);
		पूर्ण
	पूर्ण

	gpe_event_info->disable_क्रम_dispatch = TRUE;

	/*
	 * Dispatch the GPE to either an installed handler or the control
	 * method associated with this GPE (_Lxx or _Exx). If a handler
	 * exists, we invoke it and करो not attempt to run the method.
	 * If there is neither a handler nor a method, leave the GPE
	 * disabled.
	 */
	चयन (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->flags)) अणु
	हाल ACPI_GPE_DISPATCH_HANDLER:

		/* Invoke the installed handler (at पूर्णांकerrupt level) */

		वापस_value =
		    gpe_event_info->dispatch.handler->address(gpe_device,
							      gpe_number,
							      gpe_event_info->
							      dispatch.handler->
							      context);

		/* If requested, clear (अगर level-triggered) and re-enable the GPE */

		अगर (वापस_value & ACPI_REENABLE_GPE) अणु
			(व्योम)acpi_ev_finish_gpe(gpe_event_info);
		पूर्ण
		अवरोध;

	हाल ACPI_GPE_DISPATCH_METHOD:
	हाल ACPI_GPE_DISPATCH_NOTIFY:
		/*
		 * Execute the method associated with the GPE
		 * NOTE: Level-triggered GPEs are cleared after the method completes.
		 */
		status = acpi_os_execute(OSL_GPE_HANDLER,
					 acpi_ev_asynch_execute_gpe_method,
					 gpe_event_info);
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_EXCEPTION((AE_INFO, status,
					"Unable to queue handler for GPE %02X - event disabled",
					gpe_number));
		पूर्ण
		अवरोध;

	शेष:
		/*
		 * No handler or method to run!
		 * 03/2010: This हाल should no दीर्घer be possible. We will not allow
		 * a GPE to be enabled अगर it has no handler or method.
		 */
		ACPI_ERROR((AE_INFO,
			    "No handler or method for GPE %02X, disabling event",
			    gpe_number));

		अवरोध;
	पूर्ण

	वापस_UINT32(ACPI_INTERRUPT_HANDLED);
पूर्ण

#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */
