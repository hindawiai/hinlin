<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: evgpeblk - GPE block creation and initialization.
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acevents.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_EVENTS
ACPI_MODULE_NAME("evgpeblk")
#अगर (!ACPI_REDUCED_HARDWARE)	/* Entire module */
/* Local prototypes */
अटल acpi_status
acpi_ev_install_gpe_block(काष्ठा acpi_gpe_block_info *gpe_block,
			  u32 पूर्णांकerrupt_number);

अटल acpi_status
acpi_ev_create_gpe_info_blocks(काष्ठा acpi_gpe_block_info *gpe_block);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_install_gpe_block
 *
 * PARAMETERS:  gpe_block               - New GPE block
 *              पूर्णांकerrupt_number        - Xrupt to be associated with this
 *                                        GPE block
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install new GPE block with mutex support
 *
 ******************************************************************************/

अटल acpi_status
acpi_ev_install_gpe_block(काष्ठा acpi_gpe_block_info *gpe_block,
			  u32 पूर्णांकerrupt_number)
अणु
	काष्ठा acpi_gpe_block_info *next_gpe_block;
	काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_block;
	acpi_status status;
	acpi_cpu_flags flags;

	ACPI_FUNCTION_TRACE(ev_install_gpe_block);

	status = acpi_ut_acquire_mutex(ACPI_MTX_EVENTS);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	status =
	    acpi_ev_get_gpe_xrupt_block(पूर्णांकerrupt_number, &gpe_xrupt_block);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ unlock_and_निकास;
	पूर्ण

	/* Install the new block at the end of the list with lock */

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);
	अगर (gpe_xrupt_block->gpe_block_list_head) अणु
		next_gpe_block = gpe_xrupt_block->gpe_block_list_head;
		जबतक (next_gpe_block->next) अणु
			next_gpe_block = next_gpe_block->next;
		पूर्ण

		next_gpe_block->next = gpe_block;
		gpe_block->previous = next_gpe_block;
	पूर्ण अन्यथा अणु
		gpe_xrupt_block->gpe_block_list_head = gpe_block;
	पूर्ण

	gpe_block->xrupt_block = gpe_xrupt_block;
	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);

unlock_and_निकास:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_EVENTS);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_delete_gpe_block
 *
 * PARAMETERS:  gpe_block           - Existing GPE block
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Remove a GPE block
 *
 ******************************************************************************/

acpi_status acpi_ev_delete_gpe_block(काष्ठा acpi_gpe_block_info *gpe_block)
अणु
	acpi_status status;
	acpi_cpu_flags flags;

	ACPI_FUNCTION_TRACE(ev_install_gpe_block);

	status = acpi_ut_acquire_mutex(ACPI_MTX_EVENTS);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Disable all GPEs in this block */

	status =
	    acpi_hw_disable_gpe_block(gpe_block->xrupt_block, gpe_block, शून्य);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	अगर (!gpe_block->previous && !gpe_block->next) अणु

		/* This is the last gpe_block on this पूर्णांकerrupt */

		status = acpi_ev_delete_gpe_xrupt(gpe_block->xrupt_block);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ unlock_and_निकास;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Remove the block on this पूर्णांकerrupt with lock */

		flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);
		अगर (gpe_block->previous) अणु
			gpe_block->previous->next = gpe_block->next;
		पूर्ण अन्यथा अणु
			gpe_block->xrupt_block->gpe_block_list_head =
			    gpe_block->next;
		पूर्ण

		अगर (gpe_block->next) अणु
			gpe_block->next->previous = gpe_block->previous;
		पूर्ण

		acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
	पूर्ण

	acpi_current_gpe_count -= gpe_block->gpe_count;

	/* Free the gpe_block */

	ACPI_FREE(gpe_block->रेजिस्टर_info);
	ACPI_FREE(gpe_block->event_info);
	ACPI_FREE(gpe_block);

unlock_and_निकास:
	status = acpi_ut_release_mutex(ACPI_MTX_EVENTS);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_create_gpe_info_blocks
 *
 * PARAMETERS:  gpe_block   - New GPE block
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create the रेजिस्टर_info and event_info blocks क्रम this GPE block
 *
 ******************************************************************************/

अटल acpi_status
acpi_ev_create_gpe_info_blocks(काष्ठा acpi_gpe_block_info *gpe_block)
अणु
	काष्ठा acpi_gpe_रेजिस्टर_info *gpe_रेजिस्टर_info = शून्य;
	काष्ठा acpi_gpe_event_info *gpe_event_info = शून्य;
	काष्ठा acpi_gpe_event_info *this_event;
	काष्ठा acpi_gpe_रेजिस्टर_info *this_रेजिस्टर;
	u32 i;
	u32 j;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ev_create_gpe_info_blocks);

	/* Allocate the GPE रेजिस्टर inक्रमmation block */

	gpe_रेजिस्टर_info = ACPI_ALLOCATE_ZEROED((acpi_size)gpe_block->
						 रेजिस्टर_count *
						 माप(काष्ठा
							acpi_gpe_रेजिस्टर_info));
	अगर (!gpe_रेजिस्टर_info) अणु
		ACPI_ERROR((AE_INFO,
			    "Could not allocate the GpeRegisterInfo table"));
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/*
	 * Allocate the GPE event_info block. There are eight distinct GPEs
	 * per रेजिस्टर. Initialization to zeros is sufficient.
	 */
	gpe_event_info = ACPI_ALLOCATE_ZEROED((acpi_size)gpe_block->gpe_count *
					      माप(काष्ठा
						     acpi_gpe_event_info));
	अगर (!gpe_event_info) अणु
		ACPI_ERROR((AE_INFO,
			    "Could not allocate the GpeEventInfo table"));
		status = AE_NO_MEMORY;
		जाओ error_निकास;
	पूर्ण

	/* Save the new Info arrays in the GPE block */

	gpe_block->रेजिस्टर_info = gpe_रेजिस्टर_info;
	gpe_block->event_info = gpe_event_info;

	/*
	 * Initialize the GPE Register and Event काष्ठाures. A goal of these
	 * tables is to hide the fact that there are two separate GPE रेजिस्टर
	 * sets in a given GPE hardware block, the status रेजिस्टरs occupy the
	 * first half, and the enable रेजिस्टरs occupy the second half.
	 */
	this_रेजिस्टर = gpe_रेजिस्टर_info;
	this_event = gpe_event_info;

	क्रम (i = 0; i < gpe_block->रेजिस्टर_count; i++) अणु

		/* Init the रेजिस्टर_info क्रम this GPE रेजिस्टर (8 GPEs) */

		this_रेजिस्टर->base_gpe_number = (u16)
		    (gpe_block->block_base_number +
		     (i * ACPI_GPE_REGISTER_WIDTH));

		this_रेजिस्टर->status_address.address = gpe_block->address + i;

		this_रेजिस्टर->enable_address.address =
		    gpe_block->address + i + gpe_block->रेजिस्टर_count;

		this_रेजिस्टर->status_address.space_id = gpe_block->space_id;
		this_रेजिस्टर->enable_address.space_id = gpe_block->space_id;

		/* Init the event_info क्रम each GPE within this रेजिस्टर */

		क्रम (j = 0; j < ACPI_GPE_REGISTER_WIDTH; j++) अणु
			this_event->gpe_number =
			    (u8) (this_रेजिस्टर->base_gpe_number + j);
			this_event->रेजिस्टर_info = this_रेजिस्टर;
			this_event++;
		पूर्ण

		/* Disable all GPEs within this रेजिस्टर */

		status = acpi_hw_gpe_ग_लिखो(0x00, &this_रेजिस्टर->enable_address);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ error_निकास;
		पूर्ण

		/* Clear any pending GPE events within this रेजिस्टर */

		status = acpi_hw_gpe_ग_लिखो(0xFF, &this_रेजिस्टर->status_address);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ error_निकास;
		पूर्ण

		this_रेजिस्टर++;
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);

error_निकास:
	अगर (gpe_रेजिस्टर_info) अणु
		ACPI_FREE(gpe_रेजिस्टर_info);
	पूर्ण
	अगर (gpe_event_info) अणु
		ACPI_FREE(gpe_event_info);
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_create_gpe_block
 *
 * PARAMETERS:  gpe_device          - Handle to the parent GPE block
 *              gpe_block_address   - Address and space_ID
 *              रेजिस्टर_count      - Number of GPE रेजिस्टर pairs in the block
 *              gpe_block_base_number - Starting GPE number क्रम the block
 *              पूर्णांकerrupt_number    - H/W पूर्णांकerrupt क्रम the block
 *              वापस_gpe_block    - Where the new block descriptor is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create and Install a block of GPE रेजिस्टरs. All GPEs within
 *              the block are disabled at निकास.
 *              Note: Assumes namespace is locked.
 *
 ******************************************************************************/

acpi_status
acpi_ev_create_gpe_block(काष्ठा acpi_namespace_node *gpe_device,
			 u64 address,
			 u8 space_id,
			 u32 रेजिस्टर_count,
			 u16 gpe_block_base_number,
			 u32 पूर्णांकerrupt_number,
			 काष्ठा acpi_gpe_block_info **वापस_gpe_block)
अणु
	acpi_status status;
	काष्ठा acpi_gpe_block_info *gpe_block;
	काष्ठा acpi_gpe_walk_info walk_info;

	ACPI_FUNCTION_TRACE(ev_create_gpe_block);

	अगर (!रेजिस्टर_count) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Validate the space_ID */

	अगर ((space_id != ACPI_ADR_SPACE_SYSTEM_MEMORY) &&
	    (space_id != ACPI_ADR_SPACE_SYSTEM_IO)) अणु
		ACPI_ERROR((AE_INFO,
			    "Unsupported address space: 0x%X", space_id));
		वापस_ACPI_STATUS(AE_SUPPORT);
	पूर्ण

	अगर (space_id == ACPI_ADR_SPACE_SYSTEM_IO) अणु
		status = acpi_hw_validate_io_block(address,
						   ACPI_GPE_REGISTER_WIDTH,
						   रेजिस्टर_count);
		अगर (ACPI_FAILURE(status))
			वापस_ACPI_STATUS(status);
	पूर्ण

	/* Allocate a new GPE block */

	gpe_block = ACPI_ALLOCATE_ZEROED(माप(काष्ठा acpi_gpe_block_info));
	अगर (!gpe_block) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/* Initialize the new GPE block */

	gpe_block->address = address;
	gpe_block->space_id = space_id;
	gpe_block->node = gpe_device;
	gpe_block->gpe_count = (u16)(रेजिस्टर_count * ACPI_GPE_REGISTER_WIDTH);
	gpe_block->initialized = FALSE;
	gpe_block->रेजिस्टर_count = रेजिस्टर_count;
	gpe_block->block_base_number = gpe_block_base_number;

	/*
	 * Create the रेजिस्टर_info and event_info sub-काष्ठाures
	 * Note: disables and clears all GPEs in the block
	 */
	status = acpi_ev_create_gpe_info_blocks(gpe_block);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_FREE(gpe_block);
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Install the new block in the global lists */

	status = acpi_ev_install_gpe_block(gpe_block, पूर्णांकerrupt_number);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_FREE(gpe_block->रेजिस्टर_info);
		ACPI_FREE(gpe_block->event_info);
		ACPI_FREE(gpe_block);
		वापस_ACPI_STATUS(status);
	पूर्ण

	acpi_gbl_all_gpes_initialized = FALSE;

	/* Find all GPE methods (_Lxx or_Exx) क्रम this block */

	walk_info.gpe_block = gpe_block;
	walk_info.gpe_device = gpe_device;
	walk_info.execute_by_owner_id = FALSE;

	(व्योम)acpi_ns_walk_namespace(ACPI_TYPE_METHOD, gpe_device,
				     ACPI_UINT32_MAX, ACPI_NS_WALK_NO_UNLOCK,
				     acpi_ev_match_gpe_method, शून्य, &walk_info,
				     शून्य);

	/* Return the new block */

	अगर (वापस_gpe_block) अणु
		(*वापस_gpe_block) = gpe_block;
	पूर्ण

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_INIT,
			      "    Initialized GPE %02X to %02X [%4.4s] %u regs on interrupt 0x%X%s\n",
			      (u32)gpe_block->block_base_number,
			      (u32)(gpe_block->block_base_number +
				    (gpe_block->gpe_count - 1)),
			      gpe_device->name.ascii, gpe_block->रेजिस्टर_count,
			      पूर्णांकerrupt_number,
			      पूर्णांकerrupt_number ==
			      acpi_gbl_FADT.sci_पूर्णांकerrupt ? " (SCI)" : ""));

	/* Update global count of currently available GPEs */

	acpi_current_gpe_count += gpe_block->gpe_count;
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_initialize_gpe_block
 *
 * PARAMETERS:  acpi_gpe_callback
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initialize and enable a GPE block. Enable GPEs that have
 *              associated methods.
 *              Note: Assumes namespace is locked.
 *
 ******************************************************************************/

acpi_status
acpi_ev_initialize_gpe_block(काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_info,
			     काष्ठा acpi_gpe_block_info *gpe_block,
			     व्योम *context)
अणु
	acpi_status status;
	काष्ठा acpi_gpe_event_info *gpe_event_info;
	u32 gpe_enabled_count;
	u32 gpe_index;
	u32 i;
	u32 j;
	u8 *is_polling_needed = context;
	ACPI_ERROR_ONLY(u32 gpe_number);

	ACPI_FUNCTION_TRACE(ev_initialize_gpe_block);

	/*
	 * Ignore a null GPE block (e.g., अगर no GPE block 1 exists), and
	 * any GPE blocks that have been initialized alपढ़ोy.
	 */
	अगर (!gpe_block || gpe_block->initialized) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/*
	 * Enable all GPEs that have a corresponding method and have the
	 * ACPI_GPE_CAN_WAKE flag unset. Any other GPEs within this block
	 * must be enabled via the acpi_enable_gpe() पूर्णांकerface.
	 */
	gpe_enabled_count = 0;

	क्रम (i = 0; i < gpe_block->रेजिस्टर_count; i++) अणु
		क्रम (j = 0; j < ACPI_GPE_REGISTER_WIDTH; j++) अणु

			/* Get the info block क्रम this particular GPE */

			gpe_index = (i * ACPI_GPE_REGISTER_WIDTH) + j;
			gpe_event_info = &gpe_block->event_info[gpe_index];
			ACPI_ERROR_ONLY(gpe_number =
					gpe_block->block_base_number +
					gpe_index);
			gpe_event_info->flags |= ACPI_GPE_INITIALIZED;

			/*
			 * Ignore GPEs that have no corresponding _Lxx/_Exx method
			 * and GPEs that are used क्रम wakeup
			 */
			अगर ((ACPI_GPE_DISPATCH_TYPE(gpe_event_info->flags) !=
			     ACPI_GPE_DISPATCH_METHOD)
			    || (gpe_event_info->flags & ACPI_GPE_CAN_WAKE)) अणु
				जारी;
			पूर्ण

			status = acpi_ev_add_gpe_reference(gpe_event_info, FALSE);
			अगर (ACPI_FAILURE(status)) अणु
				ACPI_EXCEPTION((AE_INFO, status,
					"Could not enable GPE 0x%02X",
					gpe_number));
				जारी;
			पूर्ण

			gpe_event_info->flags |= ACPI_GPE_AUTO_ENABLED;

			अगर (is_polling_needed &&
			    ACPI_GPE_IS_POLLING_NEEDED(gpe_event_info)) अणु
				*is_polling_needed = TRUE;
			पूर्ण

			gpe_enabled_count++;
		पूर्ण
	पूर्ण

	अगर (gpe_enabled_count) अणु
		ACPI_INFO(("Enabled %u GPEs in block %02X to %02X",
			   gpe_enabled_count, (u32)gpe_block->block_base_number,
			   (u32)(gpe_block->block_base_number +
				 (gpe_block->gpe_count - 1))));
	पूर्ण

	gpe_block->initialized = TRUE;

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */
