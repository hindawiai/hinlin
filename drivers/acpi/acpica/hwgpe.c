<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: hwgpe - Low level GPE enable/disable/clear functions
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acevents.h"

#घोषणा _COMPONENT          ACPI_HARDWARE
ACPI_MODULE_NAME("hwgpe")
#अगर (!ACPI_REDUCED_HARDWARE)	/* Entire module */
/* Local prototypes */
अटल acpi_status
acpi_hw_enable_wakeup_gpe_block(काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_info,
				काष्ठा acpi_gpe_block_info *gpe_block,
				व्योम *context);

अटल acpi_status
acpi_hw_gpe_enable_ग_लिखो(u8 enable_mask,
			 काष्ठा acpi_gpe_रेजिस्टर_info *gpe_रेजिस्टर_info);

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_gpe_पढ़ो
 *
 * PARAMETERS:  value               - Where the value is वापसed
 *              reg                 - GPE रेजिस्टर काष्ठाure
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Read from a GPE रेजिस्टर in either memory or IO space.
 *
 * LIMITATIONS: <These limitations also apply to acpi_hw_gpe_ग_लिखो>
 *      space_ID must be प्रणाली_memory or प्रणाली_IO.
 *
 ******************************************************************************/

acpi_status acpi_hw_gpe_पढ़ो(u64 *value, काष्ठा acpi_gpe_address *reg)
अणु
	acpi_status status;
	u32 value32;

	अगर (reg->space_id == ACPI_ADR_SPACE_SYSTEM_MEMORY) अणु
#अगर_घोषित ACPI_GPE_USE_LOGICAL_ADDRESSES
		*value = (u64)ACPI_GET8((अचिन्हित दीर्घ)reg->address);
		वापस_ACPI_STATUS(AE_OK);
#अन्यथा
		वापस acpi_os_पढ़ो_memory((acpi_physical_address)reg->address,
					    value, ACPI_GPE_REGISTER_WIDTH);
#पूर्ण_अगर
	पूर्ण

	status = acpi_os_पढ़ो_port((acpi_io_address)reg->address,
				   &value32, ACPI_GPE_REGISTER_WIDTH);
	अगर (ACPI_FAILURE(status))
		वापस_ACPI_STATUS(status);

	*value = (u64)value32;

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_gpe_ग_लिखो
 *
 * PARAMETERS:  value               - Value to be written
 *              reg                 - GPE रेजिस्टर काष्ठाure
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Write to a GPE रेजिस्टर in either memory or IO space.
 *
 ******************************************************************************/

acpi_status acpi_hw_gpe_ग_लिखो(u64 value, काष्ठा acpi_gpe_address *reg)
अणु
	अगर (reg->space_id == ACPI_ADR_SPACE_SYSTEM_MEMORY) अणु
#अगर_घोषित ACPI_GPE_USE_LOGICAL_ADDRESSES
		ACPI_SET8((अचिन्हित दीर्घ)reg->address, value);
		वापस_ACPI_STATUS(AE_OK);
#अन्यथा
		वापस acpi_os_ग_लिखो_memory((acpi_physical_address)reg->address,
					    value, ACPI_GPE_REGISTER_WIDTH);
#पूर्ण_अगर
	पूर्ण

	वापस acpi_os_ग_लिखो_port((acpi_io_address)reg->address, (u32)value,
				  ACPI_GPE_REGISTER_WIDTH);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:	acpi_hw_get_gpe_रेजिस्टर_bit
 *
 * PARAMETERS:	gpe_event_info	    - Info block क्रम the GPE
 *
 * RETURN:	Register mask with a one in the GPE bit position
 *
 * DESCRIPTION: Compute the रेजिस्टर mask क्रम this GPE. One bit is set in the
 *              correct position क्रम the input GPE.
 *
 ******************************************************************************/

u32 acpi_hw_get_gpe_रेजिस्टर_bit(काष्ठा acpi_gpe_event_info *gpe_event_info)
अणु

	वापस ((u32)1 <<
		(gpe_event_info->gpe_number -
		 gpe_event_info->रेजिस्टर_info->base_gpe_number));
पूर्ण

/******************************************************************************
 *
 * FUNCTION:	acpi_hw_low_set_gpe
 *
 * PARAMETERS:	gpe_event_info	    - Info block क्रम the GPE to be disabled
 *		action		    - Enable or disable
 *
 * RETURN:	Status
 *
 * DESCRIPTION: Enable or disable a single GPE in the parent enable रेजिस्टर.
 *              The enable_mask field of the involved GPE रेजिस्टर must be
 *              updated by the caller अगर necessary.
 *
 ******************************************************************************/

acpi_status
acpi_hw_low_set_gpe(काष्ठा acpi_gpe_event_info *gpe_event_info, u32 action)
अणु
	काष्ठा acpi_gpe_रेजिस्टर_info *gpe_रेजिस्टर_info;
	acpi_status status = AE_OK;
	u64 enable_mask;
	u32 रेजिस्टर_bit;

	ACPI_FUNCTION_ENTRY();

	/* Get the info block क्रम the entire GPE रेजिस्टर */

	gpe_रेजिस्टर_info = gpe_event_info->रेजिस्टर_info;
	अगर (!gpe_रेजिस्टर_info) अणु
		वापस (AE_NOT_EXIST);
	पूर्ण

	/* Get current value of the enable रेजिस्टर that contains this GPE */

	status = acpi_hw_gpe_पढ़ो(&enable_mask,
				  &gpe_रेजिस्टर_info->enable_address);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Set or clear just the bit that corresponds to this GPE */

	रेजिस्टर_bit = acpi_hw_get_gpe_रेजिस्टर_bit(gpe_event_info);
	चयन (action) अणु
	हाल ACPI_GPE_CONDITIONAL_ENABLE:

		/* Only enable अगर the corresponding enable_mask bit is set */

		अगर (!(रेजिस्टर_bit & gpe_रेजिस्टर_info->enable_mask)) अणु
			वापस (AE_BAD_PARAMETER);
		पूर्ण

		ACPI_FALLTHROUGH;

	हाल ACPI_GPE_ENABLE:

		ACPI_SET_BIT(enable_mask, रेजिस्टर_bit);
		अवरोध;

	हाल ACPI_GPE_DISABLE:

		ACPI_CLEAR_BIT(enable_mask, रेजिस्टर_bit);
		अवरोध;

	शेष:

		ACPI_ERROR((AE_INFO, "Invalid GPE Action, %u", action));
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	अगर (!(रेजिस्टर_bit & gpe_रेजिस्टर_info->mask_क्रम_run)) अणु

		/* Write the updated enable mask */

		status = acpi_hw_gpe_ग_लिखो(enable_mask,
					   &gpe_रेजिस्टर_info->enable_address);
	पूर्ण
	वापस (status);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_clear_gpe
 *
 * PARAMETERS:  gpe_event_info      - Info block क्रम the GPE to be cleared
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Clear the status bit क्रम a single GPE.
 *
 ******************************************************************************/

acpi_status acpi_hw_clear_gpe(काष्ठा acpi_gpe_event_info *gpe_event_info)
अणु
	काष्ठा acpi_gpe_रेजिस्टर_info *gpe_रेजिस्टर_info;
	acpi_status status;
	u32 रेजिस्टर_bit;

	ACPI_FUNCTION_ENTRY();

	/* Get the info block क्रम the entire GPE रेजिस्टर */

	gpe_रेजिस्टर_info = gpe_event_info->रेजिस्टर_info;
	अगर (!gpe_रेजिस्टर_info) अणु
		वापस (AE_NOT_EXIST);
	पूर्ण

	/*
	 * Write a one to the appropriate bit in the status रेजिस्टर to
	 * clear this GPE.
	 */
	रेजिस्टर_bit = acpi_hw_get_gpe_रेजिस्टर_bit(gpe_event_info);

	status = acpi_hw_gpe_ग_लिखो(रेजिस्टर_bit,
				   &gpe_रेजिस्टर_info->status_address);
	वापस (status);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_get_gpe_status
 *
 * PARAMETERS:  gpe_event_info      - Info block क्रम the GPE to queried
 *              event_status        - Where the GPE status is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Return the status of a single GPE.
 *
 ******************************************************************************/

acpi_status
acpi_hw_get_gpe_status(काष्ठा acpi_gpe_event_info *gpe_event_info,
		       acpi_event_status *event_status)
अणु
	u64 in_byte;
	u32 रेजिस्टर_bit;
	काष्ठा acpi_gpe_रेजिस्टर_info *gpe_रेजिस्टर_info;
	acpi_event_status local_event_status = 0;
	acpi_status status;

	ACPI_FUNCTION_ENTRY();

	अगर (!event_status) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	/* GPE currently handled? */

	अगर (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->flags) !=
	    ACPI_GPE_DISPATCH_NONE) अणु
		local_event_status |= ACPI_EVENT_FLAG_HAS_HANDLER;
	पूर्ण

	/* Get the info block क्रम the entire GPE रेजिस्टर */

	gpe_रेजिस्टर_info = gpe_event_info->रेजिस्टर_info;

	/* Get the रेजिस्टर biपंचांगask क्रम this GPE */

	रेजिस्टर_bit = acpi_hw_get_gpe_रेजिस्टर_bit(gpe_event_info);

	/* GPE currently enabled? (enabled क्रम runसमय?) */

	अगर (रेजिस्टर_bit & gpe_रेजिस्टर_info->enable_क्रम_run) अणु
		local_event_status |= ACPI_EVENT_FLAG_ENABLED;
	पूर्ण

	/* GPE currently masked? (masked क्रम runसमय?) */

	अगर (रेजिस्टर_bit & gpe_रेजिस्टर_info->mask_क्रम_run) अणु
		local_event_status |= ACPI_EVENT_FLAG_MASKED;
	पूर्ण

	/* GPE enabled क्रम wake? */

	अगर (रेजिस्टर_bit & gpe_रेजिस्टर_info->enable_क्रम_wake) अणु
		local_event_status |= ACPI_EVENT_FLAG_WAKE_ENABLED;
	पूर्ण

	/* GPE currently enabled (enable bit == 1)? */

	status = acpi_hw_gpe_पढ़ो(&in_byte, &gpe_रेजिस्टर_info->enable_address);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	अगर (रेजिस्टर_bit & in_byte) अणु
		local_event_status |= ACPI_EVENT_FLAG_ENABLE_SET;
	पूर्ण

	/* GPE currently active (status bit == 1)? */

	status = acpi_hw_gpe_पढ़ो(&in_byte, &gpe_रेजिस्टर_info->status_address);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	अगर (रेजिस्टर_bit & in_byte) अणु
		local_event_status |= ACPI_EVENT_FLAG_STATUS_SET;
	पूर्ण

	/* Set वापस value */

	(*event_status) = local_event_status;
	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_gpe_enable_ग_लिखो
 *
 * PARAMETERS:  enable_mask         - Bit mask to ग_लिखो to the GPE रेजिस्टर
 *              gpe_रेजिस्टर_info   - Gpe Register info
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Write the enable mask byte to the given GPE रेजिस्टर.
 *
 ******************************************************************************/

अटल acpi_status
acpi_hw_gpe_enable_ग_लिखो(u8 enable_mask,
			 काष्ठा acpi_gpe_रेजिस्टर_info *gpe_रेजिस्टर_info)
अणु
	acpi_status status;

	gpe_रेजिस्टर_info->enable_mask = enable_mask;

	status = acpi_hw_gpe_ग_लिखो(enable_mask,
				   &gpe_रेजिस्टर_info->enable_address);
	वापस (status);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_disable_gpe_block
 *
 * PARAMETERS:  gpe_xrupt_info      - GPE Interrupt info
 *              gpe_block           - Gpe Block info
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Disable all GPEs within a single GPE block
 *
 ******************************************************************************/

acpi_status
acpi_hw_disable_gpe_block(काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_info,
			  काष्ठा acpi_gpe_block_info *gpe_block, व्योम *context)
अणु
	u32 i;
	acpi_status status;

	/* Examine each GPE Register within the block */

	क्रम (i = 0; i < gpe_block->रेजिस्टर_count; i++) अणु

		/* Disable all GPEs in this रेजिस्टर */

		status =
		    acpi_hw_gpe_enable_ग_लिखो(0x00,
					     &gpe_block->रेजिस्टर_info[i]);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण
	पूर्ण

	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_clear_gpe_block
 *
 * PARAMETERS:  gpe_xrupt_info      - GPE Interrupt info
 *              gpe_block           - Gpe Block info
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Clear status bits क्रम all GPEs within a single GPE block
 *
 ******************************************************************************/

acpi_status
acpi_hw_clear_gpe_block(काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_info,
			काष्ठा acpi_gpe_block_info *gpe_block, व्योम *context)
अणु
	u32 i;
	acpi_status status;

	/* Examine each GPE Register within the block */

	क्रम (i = 0; i < gpe_block->रेजिस्टर_count; i++) अणु

		/* Clear status on all GPEs in this रेजिस्टर */

		status = acpi_hw_gpe_ग_लिखो(0xFF,
					   &gpe_block->रेजिस्टर_info[i].status_address);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण
	पूर्ण

	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_enable_runसमय_gpe_block
 *
 * PARAMETERS:  gpe_xrupt_info      - GPE Interrupt info
 *              gpe_block           - Gpe Block info
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Enable all "runtime" GPEs within a single GPE block. Includes
 *              combination wake/run GPEs.
 *
 ******************************************************************************/

acpi_status
acpi_hw_enable_runसमय_gpe_block(काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_info,
				 काष्ठा acpi_gpe_block_info *gpe_block,
				 व्योम *context)
अणु
	u32 i;
	acpi_status status;
	काष्ठा acpi_gpe_रेजिस्टर_info *gpe_रेजिस्टर_info;
	u8 enable_mask;

	/* NOTE: assumes that all GPEs are currently disabled */

	/* Examine each GPE Register within the block */

	क्रम (i = 0; i < gpe_block->रेजिस्टर_count; i++) अणु
		gpe_रेजिस्टर_info = &gpe_block->रेजिस्टर_info[i];
		अगर (!gpe_रेजिस्टर_info->enable_क्रम_run) अणु
			जारी;
		पूर्ण

		/* Enable all "runtime" GPEs in this रेजिस्टर */

		enable_mask = gpe_रेजिस्टर_info->enable_क्रम_run &
		    ~gpe_रेजिस्टर_info->mask_क्रम_run;
		status =
		    acpi_hw_gpe_enable_ग_लिखो(enable_mask, gpe_रेजिस्टर_info);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण
	पूर्ण

	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_enable_wakeup_gpe_block
 *
 * PARAMETERS:  gpe_xrupt_info      - GPE Interrupt info
 *              gpe_block           - Gpe Block info
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Enable all "wake" GPEs within a single GPE block. Includes
 *              combination wake/run GPEs.
 *
 ******************************************************************************/

अटल acpi_status
acpi_hw_enable_wakeup_gpe_block(काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_info,
				काष्ठा acpi_gpe_block_info *gpe_block,
				व्योम *context)
अणु
	u32 i;
	acpi_status status;
	काष्ठा acpi_gpe_रेजिस्टर_info *gpe_रेजिस्टर_info;

	/* Examine each GPE Register within the block */

	क्रम (i = 0; i < gpe_block->रेजिस्टर_count; i++) अणु
		gpe_रेजिस्टर_info = &gpe_block->रेजिस्टर_info[i];

		/*
		 * Enable all "wake" GPEs in this रेजिस्टर and disable the
		 * reमुख्यing ones.
		 */

		status =
		    acpi_hw_gpe_enable_ग_लिखो(gpe_रेजिस्टर_info->enable_क्रम_wake,
					     gpe_रेजिस्टर_info);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण
	पूर्ण

	वापस (AE_OK);
पूर्ण

काष्ठा acpi_gpe_block_status_context अणु
	काष्ठा acpi_gpe_रेजिस्टर_info *gpe_skip_रेजिस्टर_info;
	u8 gpe_skip_mask;
	u8 retval;
पूर्ण;

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_get_gpe_block_status
 *
 * PARAMETERS:  gpe_xrupt_info      - GPE Interrupt info
 *              gpe_block           - Gpe Block info
 *              context             - GPE list walk context data
 *
 * RETURN:      Success
 *
 * DESCRIPTION: Produce a combined GPE status bits mask क्रम the given block.
 *
 ******************************************************************************/

अटल acpi_status
acpi_hw_get_gpe_block_status(काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_info,
			     काष्ठा acpi_gpe_block_info *gpe_block,
			     व्योम *context)
अणु
	काष्ठा acpi_gpe_block_status_context *c = context;
	काष्ठा acpi_gpe_रेजिस्टर_info *gpe_रेजिस्टर_info;
	u64 in_enable, in_status;
	acpi_status status;
	u8 ret_mask;
	u32 i;

	/* Examine each GPE Register within the block */

	क्रम (i = 0; i < gpe_block->रेजिस्टर_count; i++) अणु
		gpe_रेजिस्टर_info = &gpe_block->रेजिस्टर_info[i];

		status = acpi_hw_gpe_पढ़ो(&in_enable,
					  &gpe_रेजिस्टर_info->enable_address);
		अगर (ACPI_FAILURE(status)) अणु
			जारी;
		पूर्ण

		status = acpi_hw_gpe_पढ़ो(&in_status,
					  &gpe_रेजिस्टर_info->status_address);
		अगर (ACPI_FAILURE(status)) अणु
			जारी;
		पूर्ण

		ret_mask = in_enable & in_status;
		अगर (ret_mask && c->gpe_skip_रेजिस्टर_info == gpe_रेजिस्टर_info) अणु
			ret_mask &= ~c->gpe_skip_mask;
		पूर्ण
		c->retval |= ret_mask;
	पूर्ण

	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_disable_all_gpes
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Disable and clear all GPEs in all GPE blocks
 *
 ******************************************************************************/

acpi_status acpi_hw_disable_all_gpes(व्योम)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(hw_disable_all_gpes);

	status = acpi_ev_walk_gpe_list(acpi_hw_disable_gpe_block, शून्य);
	वापस_ACPI_STATUS(status);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_enable_all_runसमय_gpes
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Enable all "runtime" GPEs, in all GPE blocks
 *
 ******************************************************************************/

acpi_status acpi_hw_enable_all_runसमय_gpes(व्योम)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(hw_enable_all_runसमय_gpes);

	status = acpi_ev_walk_gpe_list(acpi_hw_enable_runसमय_gpe_block, शून्य);
	वापस_ACPI_STATUS(status);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_enable_all_wakeup_gpes
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Enable all "wakeup" GPEs, in all GPE blocks
 *
 ******************************************************************************/

acpi_status acpi_hw_enable_all_wakeup_gpes(व्योम)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(hw_enable_all_wakeup_gpes);

	status = acpi_ev_walk_gpe_list(acpi_hw_enable_wakeup_gpe_block, शून्य);
	वापस_ACPI_STATUS(status);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_check_all_gpes
 *
 * PARAMETERS:  gpe_skip_device      - GPE devoce of the GPE to skip
 *              gpe_skip_number      - Number of the GPE to skip
 *
 * RETURN:      Combined status of all GPEs
 *
 * DESCRIPTION: Check all enabled GPEs in all GPE blocks, except क्रम the one
 *              represented by the "skip" arguments, and वापस TRUE अगर the
 *              status bit is set क्रम at least one of them of FALSE otherwise.
 *
 ******************************************************************************/

u8 acpi_hw_check_all_gpes(acpi_handle gpe_skip_device, u32 gpe_skip_number)
अणु
	काष्ठा acpi_gpe_block_status_context context = अणु
		.gpe_skip_रेजिस्टर_info = शून्य,
		.retval = 0,
	पूर्ण;
	काष्ठा acpi_gpe_event_info *gpe_event_info;
	acpi_cpu_flags flags;

	ACPI_FUNCTION_TRACE(acpi_hw_check_all_gpes);

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);

	gpe_event_info = acpi_ev_get_gpe_event_info(gpe_skip_device,
						    gpe_skip_number);
	अगर (gpe_event_info) अणु
		context.gpe_skip_रेजिस्टर_info = gpe_event_info->रेजिस्टर_info;
		context.gpe_skip_mask = acpi_hw_get_gpe_रेजिस्टर_bit(gpe_event_info);
	पूर्ण

	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);

	(व्योम)acpi_ev_walk_gpe_list(acpi_hw_get_gpe_block_status, &context);
	वापस (context.retval != 0);
पूर्ण

#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */
