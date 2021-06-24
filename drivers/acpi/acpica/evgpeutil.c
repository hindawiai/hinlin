<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: evgpeutil - GPE utilities
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acevents.h"

#घोषणा _COMPONENT          ACPI_EVENTS
ACPI_MODULE_NAME("evgpeutil")

#अगर (!ACPI_REDUCED_HARDWARE)	/* Entire module */
/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_walk_gpe_list
 *
 * PARAMETERS:  gpe_walk_callback   - Routine called क्रम each GPE block
 *              context             - Value passed to callback
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Walk the GPE lists.
 *
 ******************************************************************************/
acpi_status
acpi_ev_walk_gpe_list(acpi_gpe_callback gpe_walk_callback, व्योम *context)
अणु
	काष्ठा acpi_gpe_block_info *gpe_block;
	काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_info;
	acpi_status status = AE_OK;
	acpi_cpu_flags flags;

	ACPI_FUNCTION_TRACE(ev_walk_gpe_list);

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);

	/* Walk the पूर्णांकerrupt level descriptor list */

	gpe_xrupt_info = acpi_gbl_gpe_xrupt_list_head;
	जबतक (gpe_xrupt_info) अणु

		/* Walk all Gpe Blocks attached to this पूर्णांकerrupt level */

		gpe_block = gpe_xrupt_info->gpe_block_list_head;
		जबतक (gpe_block) अणु

			/* One callback per GPE block */

			status =
			    gpe_walk_callback(gpe_xrupt_info, gpe_block,
					      context);
			अगर (ACPI_FAILURE(status)) अणु
				अगर (status == AE_CTRL_END) अणु	/* Callback पात */
					status = AE_OK;
				पूर्ण
				जाओ unlock_and_निकास;
			पूर्ण

			gpe_block = gpe_block->next;
		पूर्ण

		gpe_xrupt_info = gpe_xrupt_info->next;
	पूर्ण

unlock_and_निकास:
	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_get_gpe_device
 *
 * PARAMETERS:  GPE_WALK_CALLBACK
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Matches the input GPE index (0-current_gpe_count) with a GPE
 *              block device. शून्य अगर the GPE is one of the FADT-defined GPEs.
 *
 ******************************************************************************/

acpi_status
acpi_ev_get_gpe_device(काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_info,
		       काष्ठा acpi_gpe_block_info *gpe_block, व्योम *context)
अणु
	काष्ठा acpi_gpe_device_info *info = context;

	/* Increment Index by the number of GPEs in this block */

	info->next_block_base_index += gpe_block->gpe_count;

	अगर (info->index < info->next_block_base_index) अणु
		/*
		 * The GPE index is within this block, get the node. Leave the node
		 * शून्य क्रम the FADT-defined GPEs
		 */
		अगर ((gpe_block->node)->type == ACPI_TYPE_DEVICE) अणु
			info->gpe_device = gpe_block->node;
		पूर्ण

		info->status = AE_OK;
		वापस (AE_CTRL_END);
	पूर्ण

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_get_gpe_xrupt_block
 *
 * PARAMETERS:  पूर्णांकerrupt_number            - Interrupt क्रम a GPE block
 *              gpe_xrupt_block             - Where the block is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get or Create a GPE पूर्णांकerrupt block. There is one पूर्णांकerrupt
 *              block per unique पूर्णांकerrupt level used क्रम GPEs. Should be
 *              called only when the GPE lists are semaphore locked and not
 *              subject to change.
 *
 ******************************************************************************/

acpi_status
acpi_ev_get_gpe_xrupt_block(u32 पूर्णांकerrupt_number,
			    काष्ठा acpi_gpe_xrupt_info **gpe_xrupt_block)
अणु
	काष्ठा acpi_gpe_xrupt_info *next_gpe_xrupt;
	काष्ठा acpi_gpe_xrupt_info *gpe_xrupt;
	acpi_status status;
	acpi_cpu_flags flags;

	ACPI_FUNCTION_TRACE(ev_get_gpe_xrupt_block);

	/* No need क्रम lock since we are not changing any list elements here */

	next_gpe_xrupt = acpi_gbl_gpe_xrupt_list_head;
	जबतक (next_gpe_xrupt) अणु
		अगर (next_gpe_xrupt->पूर्णांकerrupt_number == पूर्णांकerrupt_number) अणु
			*gpe_xrupt_block = next_gpe_xrupt;
			वापस_ACPI_STATUS(AE_OK);
		पूर्ण

		next_gpe_xrupt = next_gpe_xrupt->next;
	पूर्ण

	/* Not found, must allocate a new xrupt descriptor */

	gpe_xrupt = ACPI_ALLOCATE_ZEROED(माप(काष्ठा acpi_gpe_xrupt_info));
	अगर (!gpe_xrupt) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	gpe_xrupt->पूर्णांकerrupt_number = पूर्णांकerrupt_number;

	/* Install new पूर्णांकerrupt descriptor with spin lock */

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);
	अगर (acpi_gbl_gpe_xrupt_list_head) अणु
		next_gpe_xrupt = acpi_gbl_gpe_xrupt_list_head;
		जबतक (next_gpe_xrupt->next) अणु
			next_gpe_xrupt = next_gpe_xrupt->next;
		पूर्ण

		next_gpe_xrupt->next = gpe_xrupt;
		gpe_xrupt->previous = next_gpe_xrupt;
	पूर्ण अन्यथा अणु
		acpi_gbl_gpe_xrupt_list_head = gpe_xrupt;
	पूर्ण

	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);

	/* Install new पूर्णांकerrupt handler अगर not SCI_INT */

	अगर (पूर्णांकerrupt_number != acpi_gbl_FADT.sci_पूर्णांकerrupt) अणु
		status = acpi_os_install_पूर्णांकerrupt_handler(पूर्णांकerrupt_number,
							   acpi_ev_gpe_xrupt_handler,
							   gpe_xrupt);
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_EXCEPTION((AE_INFO, status,
					"Could not install GPE interrupt handler at level 0x%X",
					पूर्णांकerrupt_number));
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण

	*gpe_xrupt_block = gpe_xrupt;
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_delete_gpe_xrupt
 *
 * PARAMETERS:  gpe_xrupt       - A GPE पूर्णांकerrupt info block
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Remove and मुक्त a gpe_xrupt block. Remove an associated
 *              पूर्णांकerrupt handler अगर not the SCI पूर्णांकerrupt.
 *
 ******************************************************************************/

acpi_status acpi_ev_delete_gpe_xrupt(काष्ठा acpi_gpe_xrupt_info *gpe_xrupt)
अणु
	acpi_status status;
	acpi_cpu_flags flags;

	ACPI_FUNCTION_TRACE(ev_delete_gpe_xrupt);

	/* We never want to हटाओ the SCI पूर्णांकerrupt handler */

	अगर (gpe_xrupt->पूर्णांकerrupt_number == acpi_gbl_FADT.sci_पूर्णांकerrupt) अणु
		gpe_xrupt->gpe_block_list_head = शून्य;
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Disable this पूर्णांकerrupt */

	status =
	    acpi_os_हटाओ_पूर्णांकerrupt_handler(gpe_xrupt->पूर्णांकerrupt_number,
					     acpi_ev_gpe_xrupt_handler);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Unlink the पूर्णांकerrupt block with lock */

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);
	अगर (gpe_xrupt->previous) अणु
		gpe_xrupt->previous->next = gpe_xrupt->next;
	पूर्ण अन्यथा अणु
		/* No previous, update list head */

		acpi_gbl_gpe_xrupt_list_head = gpe_xrupt->next;
	पूर्ण

	अगर (gpe_xrupt->next) अणु
		gpe_xrupt->next->previous = gpe_xrupt->previous;
	पूर्ण
	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);

	/* Free the block */

	ACPI_FREE(gpe_xrupt);
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_delete_gpe_handlers
 *
 * PARAMETERS:  gpe_xrupt_info      - GPE Interrupt info
 *              gpe_block           - Gpe Block info
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Delete all Handler objects found in the GPE data काष्ठाs.
 *              Used only prior to termination.
 *
 ******************************************************************************/

acpi_status
acpi_ev_delete_gpe_handlers(काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_info,
			    काष्ठा acpi_gpe_block_info *gpe_block,
			    व्योम *context)
अणु
	काष्ठा acpi_gpe_event_info *gpe_event_info;
	काष्ठा acpi_gpe_notअगरy_info *notअगरy;
	काष्ठा acpi_gpe_notअगरy_info *next;
	u32 i;
	u32 j;

	ACPI_FUNCTION_TRACE(ev_delete_gpe_handlers);

	/* Examine each GPE Register within the block */

	क्रम (i = 0; i < gpe_block->रेजिस्टर_count; i++) अणु

		/* Now look at the inभागidual GPEs in this byte रेजिस्टर */

		क्रम (j = 0; j < ACPI_GPE_REGISTER_WIDTH; j++) अणु
			gpe_event_info = &gpe_block->event_info[((acpi_size)i *
								 ACPI_GPE_REGISTER_WIDTH)
								+ j];

			अगर ((ACPI_GPE_DISPATCH_TYPE(gpe_event_info->flags) ==
			     ACPI_GPE_DISPATCH_HANDLER) ||
			    (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->flags) ==
			     ACPI_GPE_DISPATCH_RAW_HANDLER)) अणु

				/* Delete an installed handler block */

				ACPI_FREE(gpe_event_info->dispatch.handler);
				gpe_event_info->dispatch.handler = शून्य;
				gpe_event_info->flags &=
				    ~ACPI_GPE_DISPATCH_MASK;
			पूर्ण अन्यथा अगर (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->flags)
				   == ACPI_GPE_DISPATCH_NOTIFY) अणु

				/* Delete the implicit notअगरication device list */

				notअगरy = gpe_event_info->dispatch.notअगरy_list;
				जबतक (notअगरy) अणु
					next = notअगरy->next;
					ACPI_FREE(notअगरy);
					notअगरy = next;
				पूर्ण

				gpe_event_info->dispatch.notअगरy_list = शून्य;
				gpe_event_info->flags &=
				    ~ACPI_GPE_DISPATCH_MASK;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */
