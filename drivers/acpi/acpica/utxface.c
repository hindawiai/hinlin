<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: utxface - External पूर्णांकerfaces, miscellaneous utility functions
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#घोषणा EXPORT_ACPI_INTERFACES

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acdebug.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utxface")

/*******************************************************************************
 *
 * FUNCTION:    acpi_terminate
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Shutकरोwn the ACPICA subप्रणाली and release all resources.
 *
 ******************************************************************************/
acpi_status ACPI_INIT_FUNCTION acpi_terminate(व्योम)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_terminate);

	/* Shutकरोwn and मुक्त all resources */

	acpi_ut_subप्रणाली_shutकरोwn();

	/* Free the mutex objects */

	acpi_ut_mutex_terminate();

	/* Now we can shutकरोwn the OS-dependent layer */

	status = acpi_os_terminate();
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL_INIT(acpi_terminate)

#अगर_अघोषित ACPI_ASL_COMPILER
#अगर_घोषित ACPI_FUTURE_USAGE
/*******************************************************************************
 *
 * FUNCTION:    acpi_subप्रणाली_status
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status of the ACPI subप्रणाली
 *
 * DESCRIPTION: Other drivers that use the ACPI subप्रणाली should call this
 *              beक्रमe making any other calls, to ensure the subप्रणाली
 *              initialized successfully.
 *
 ******************************************************************************/
acpi_status acpi_subप्रणाली_status(व्योम)
अणु

	अगर (acpi_gbl_startup_flags & ACPI_INITIALIZED_OK) अणु
		वापस (AE_OK);
	पूर्ण अन्यथा अणु
		वापस (AE_ERROR);
	पूर्ण
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_subप्रणाली_status)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_प्रणाली_info
 *
 * PARAMETERS:  out_buffer      - A buffer to receive the resources क्रम the
 *                                device
 *
 * RETURN:      status          - the status of the call
 *
 * DESCRIPTION: This function is called to get inक्रमmation about the current
 *              state of the ACPI subप्रणाली. It will वापस प्रणाली inक्रमmation
 *              in the out_buffer.
 *
 *              If the function fails an appropriate status will be वापसed
 *              and the value of out_buffer is undefined.
 *
 ******************************************************************************/
acpi_status acpi_get_प्रणाली_info(काष्ठा acpi_buffer *out_buffer)
अणु
	काष्ठा acpi_प्रणाली_info *info_ptr;
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_get_प्रणाली_info);

	/* Parameter validation */

	status = acpi_ut_validate_buffer(out_buffer);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Validate/Allocate/Clear caller buffer */

	status =
	    acpi_ut_initialize_buffer(out_buffer,
				      माप(काष्ठा acpi_प्रणाली_info));
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Populate the वापस buffer
	 */
	info_ptr = (काष्ठा acpi_प्रणाली_info *)out_buffer->poपूर्णांकer;
	info_ptr->acpi_ca_version = ACPI_CA_VERSION;

	/* System flags (ACPI capabilities) */

	info_ptr->flags = ACPI_SYS_MODE_ACPI;

	/* Timer resolution - 24 or 32 bits  */

	अगर (acpi_gbl_FADT.flags & ACPI_FADT_32BIT_TIMER) अणु
		info_ptr->समयr_resolution = 24;
	पूर्ण अन्यथा अणु
		info_ptr->समयr_resolution = 32;
	पूर्ण

	/* Clear the reserved fields */

	info_ptr->reserved1 = 0;
	info_ptr->reserved2 = 0;

	/* Current debug levels */

	info_ptr->debug_layer = acpi_dbg_layer;
	info_ptr->debug_level = acpi_dbg_level;

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_प्रणाली_info)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_statistics
 *
 * PARAMETERS:  stats           - Where the statistics are वापसed
 *
 * RETURN:      status          - the status of the call
 *
 * DESCRIPTION: Get the contents of the various प्रणाली counters
 *
 ******************************************************************************/
acpi_status acpi_get_statistics(काष्ठा acpi_statistics *stats)
अणु
	ACPI_FUNCTION_TRACE(acpi_get_statistics);

	/* Parameter validation */

	अगर (!stats) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Various पूर्णांकerrupt-based event counters */

	stats->sci_count = acpi_sci_count;
	stats->gpe_count = acpi_gpe_count;

	स_नकल(stats->fixed_event_count, acpi_fixed_event_count,
	       माप(acpi_fixed_event_count));

	/* Other counters */

	stats->method_count = acpi_method_count;
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_statistics)

/*****************************************************************************
 *
 * FUNCTION:    acpi_install_initialization_handler
 *
 * PARAMETERS:  handler             - Callback procedure
 *              function            - Not (currently) used, see below
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install an initialization handler
 *
 * TBD: When a second function is added, must save the Function also.
 *
 ****************************************************************************/
acpi_status
acpi_install_initialization_handler(acpi_init_handler handler, u32 function)
अणु

	अगर (!handler) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	अगर (acpi_gbl_init_handler) अणु
		वापस (AE_ALREADY_EXISTS);
	पूर्ण

	acpi_gbl_init_handler = handler;
	वापस (AE_OK);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_install_initialization_handler)
#पूर्ण_अगर

/*****************************************************************************
 *
 * FUNCTION:    acpi_purge_cached_objects
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Empty all caches (delete the cached objects)
 *
 ****************************************************************************/
acpi_status acpi_purge_cached_objects(व्योम)
अणु
	ACPI_FUNCTION_TRACE(acpi_purge_cached_objects);

	(व्योम)acpi_os_purge_cache(acpi_gbl_state_cache);
	(व्योम)acpi_os_purge_cache(acpi_gbl_opeअक्रम_cache);
	(व्योम)acpi_os_purge_cache(acpi_gbl_ps_node_cache);
	(व्योम)acpi_os_purge_cache(acpi_gbl_ps_node_ext_cache);

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_purge_cached_objects)

/*****************************************************************************
 *
 * FUNCTION:    acpi_install_पूर्णांकerface
 *
 * PARAMETERS:  पूर्णांकerface_name      - The पूर्णांकerface to install
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install an _OSI पूर्णांकerface to the global list
 *
 ****************************************************************************/
acpi_status acpi_install_पूर्णांकerface(acpi_string पूर्णांकerface_name)
अणु
	acpi_status status;
	काष्ठा acpi_पूर्णांकerface_info *पूर्णांकerface_info;

	/* Parameter validation */

	अगर (!पूर्णांकerface_name || (म_माप(पूर्णांकerface_name) == 0)) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	status = acpi_os_acquire_mutex(acpi_gbl_osi_mutex, ACPI_WAIT_FOREVER);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Check अगर the पूर्णांकerface name is alपढ़ोy in the global list */

	पूर्णांकerface_info = acpi_ut_get_पूर्णांकerface(पूर्णांकerface_name);
	अगर (पूर्णांकerface_info) अणु
		/*
		 * The पूर्णांकerface alपढ़ोy exists in the list. This is OK अगर the
		 * पूर्णांकerface has been marked invalid -- just clear the bit.
		 */
		अगर (पूर्णांकerface_info->flags & ACPI_OSI_INVALID) अणु
			पूर्णांकerface_info->flags &= ~ACPI_OSI_INVALID;
			status = AE_OK;
		पूर्ण अन्यथा अणु
			status = AE_ALREADY_EXISTS;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* New पूर्णांकerface name, install पूर्णांकo the global list */

		status = acpi_ut_install_पूर्णांकerface(पूर्णांकerface_name);
	पूर्ण

	acpi_os_release_mutex(acpi_gbl_osi_mutex);
	वापस (status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_install_पूर्णांकerface)

/*****************************************************************************
 *
 * FUNCTION:    acpi_हटाओ_पूर्णांकerface
 *
 * PARAMETERS:  पूर्णांकerface_name      - The पूर्णांकerface to हटाओ
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Remove an _OSI पूर्णांकerface from the global list
 *
 ****************************************************************************/
acpi_status acpi_हटाओ_पूर्णांकerface(acpi_string पूर्णांकerface_name)
अणु
	acpi_status status;

	/* Parameter validation */

	अगर (!पूर्णांकerface_name || (म_माप(पूर्णांकerface_name) == 0)) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	status = acpi_os_acquire_mutex(acpi_gbl_osi_mutex, ACPI_WAIT_FOREVER);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	status = acpi_ut_हटाओ_पूर्णांकerface(पूर्णांकerface_name);

	acpi_os_release_mutex(acpi_gbl_osi_mutex);
	वापस (status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_हटाओ_पूर्णांकerface)

/*****************************************************************************
 *
 * FUNCTION:    acpi_install_पूर्णांकerface_handler
 *
 * PARAMETERS:  handler             - The _OSI पूर्णांकerface handler to install
 *                                    शून्य means "remove existing handler"
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install a handler क्रम the predefined _OSI ACPI method.
 *              invoked during execution of the पूर्णांकernal implementation of
 *              _OSI. A शून्य handler simply हटाओs any existing handler.
 *
 ****************************************************************************/
acpi_status acpi_install_पूर्णांकerface_handler(acpi_पूर्णांकerface_handler handler)
अणु
	acpi_status status;

	status = acpi_os_acquire_mutex(acpi_gbl_osi_mutex, ACPI_WAIT_FOREVER);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	अगर (handler && acpi_gbl_पूर्णांकerface_handler) अणु
		status = AE_ALREADY_EXISTS;
	पूर्ण अन्यथा अणु
		acpi_gbl_पूर्णांकerface_handler = handler;
	पूर्ण

	acpi_os_release_mutex(acpi_gbl_osi_mutex);
	वापस (status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_install_पूर्णांकerface_handler)

/*****************************************************************************
 *
 * FUNCTION:    acpi_update_पूर्णांकerfaces
 *
 * PARAMETERS:  action              - Actions to be perक्रमmed during the
 *                                    update
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Update _OSI पूर्णांकerface strings, disabling or enabling OS venकरोr
 *              string or/and feature group strings.
 *
 ****************************************************************************/
acpi_status acpi_update_पूर्णांकerfaces(u8 action)
अणु
	acpi_status status;

	status = acpi_os_acquire_mutex(acpi_gbl_osi_mutex, ACPI_WAIT_FOREVER);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	status = acpi_ut_update_पूर्णांकerfaces(action);

	acpi_os_release_mutex(acpi_gbl_osi_mutex);
	वापस (status);
पूर्ण

/*****************************************************************************
 *
 * FUNCTION:    acpi_check_address_range
 *
 * PARAMETERS:  space_id            - Address space ID
 *              address             - Start address
 *              length              - Length
 *              warn                - TRUE अगर warning on overlap desired
 *
 * RETURN:      Count of the number of conflicts detected.
 *
 * DESCRIPTION: Check अगर the input address range overlaps any of the
 *              ASL operation region address ranges.
 *
 ****************************************************************************/

u32
acpi_check_address_range(acpi_adr_space_type space_id,
			 acpi_physical_address address,
			 acpi_size length, u8 warn)
अणु
	u32 overlaps;
	acpi_status status;

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (0);
	पूर्ण

	overlaps = acpi_ut_check_address_range(space_id, address,
					       (u32)length, warn);

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	वापस (overlaps);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_check_address_range)
#पूर्ण_अगर				/* !ACPI_ASL_COMPILER */
/*******************************************************************************
 *
 * FUNCTION:    acpi_decode_pld_buffer
 *
 * PARAMETERS:  in_buffer           - Buffer वापसed by _PLD method
 *              length              - Length of the in_buffer
 *              वापस_buffer       - Where the decode buffer is वापसed
 *
 * RETURN:      Status and the decoded _PLD buffer. User must deallocate
 *              the buffer via ACPI_FREE.
 *
 * DESCRIPTION: Decode the bit-packed buffer वापसed by the _PLD method पूर्णांकo
 *              a local काष्ठा that is much more useful to an ACPI driver.
 *
 ******************************************************************************/
acpi_status
acpi_decode_pld_buffer(u8 *in_buffer,
		       acpi_size length, काष्ठा acpi_pld_info **वापस_buffer)
अणु
	काष्ठा acpi_pld_info *pld_info;
	u32 *buffer = ACPI_CAST_PTR(u32, in_buffer);
	u32 dword;

	/* Parameter validation */

	अगर (!in_buffer || !वापस_buffer
	    || (length < ACPI_PLD_REV1_BUFFER_SIZE)) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	pld_info = ACPI_ALLOCATE_ZEROED(माप(काष्ठा acpi_pld_info));
	अगर (!pld_info) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	/* First 32-bit DWord */

	ACPI_MOVE_32_TO_32(&dword, &buffer[0]);
	pld_info->revision = ACPI_PLD_GET_REVISION(&dword);
	pld_info->ignore_color = ACPI_PLD_GET_IGNORE_COLOR(&dword);
	pld_info->red = ACPI_PLD_GET_RED(&dword);
	pld_info->green = ACPI_PLD_GET_GREEN(&dword);
	pld_info->blue = ACPI_PLD_GET_BLUE(&dword);

	/* Second 32-bit DWord */

	ACPI_MOVE_32_TO_32(&dword, &buffer[1]);
	pld_info->width = ACPI_PLD_GET_WIDTH(&dword);
	pld_info->height = ACPI_PLD_GET_HEIGHT(&dword);

	/* Third 32-bit DWord */

	ACPI_MOVE_32_TO_32(&dword, &buffer[2]);
	pld_info->user_visible = ACPI_PLD_GET_USER_VISIBLE(&dword);
	pld_info->करोck = ACPI_PLD_GET_DOCK(&dword);
	pld_info->lid = ACPI_PLD_GET_LID(&dword);
	pld_info->panel = ACPI_PLD_GET_PANEL(&dword);
	pld_info->vertical_position = ACPI_PLD_GET_VERTICAL(&dword);
	pld_info->horizontal_position = ACPI_PLD_GET_HORIZONTAL(&dword);
	pld_info->shape = ACPI_PLD_GET_SHAPE(&dword);
	pld_info->group_orientation = ACPI_PLD_GET_ORIENTATION(&dword);
	pld_info->group_token = ACPI_PLD_GET_TOKEN(&dword);
	pld_info->group_position = ACPI_PLD_GET_POSITION(&dword);
	pld_info->bay = ACPI_PLD_GET_BAY(&dword);

	/* Fourth 32-bit DWord */

	ACPI_MOVE_32_TO_32(&dword, &buffer[3]);
	pld_info->ejectable = ACPI_PLD_GET_EJECTABLE(&dword);
	pld_info->ospm_eject_required = ACPI_PLD_GET_OSPM_EJECT(&dword);
	pld_info->cabinet_number = ACPI_PLD_GET_CABINET(&dword);
	pld_info->card_cage_number = ACPI_PLD_GET_CARD_CAGE(&dword);
	pld_info->reference = ACPI_PLD_GET_REFERENCE(&dword);
	pld_info->rotation = ACPI_PLD_GET_ROTATION(&dword);
	pld_info->order = ACPI_PLD_GET_ORDER(&dword);

	अगर (length >= ACPI_PLD_REV2_BUFFER_SIZE) अणु

		/* Fअगरth 32-bit DWord (Revision 2 of _PLD) */

		ACPI_MOVE_32_TO_32(&dword, &buffer[4]);
		pld_info->vertical_offset = ACPI_PLD_GET_VERT_OFFSET(&dword);
		pld_info->horizontal_offset = ACPI_PLD_GET_HORIZ_OFFSET(&dword);
	पूर्ण

	*वापस_buffer = pld_info;
	वापस (AE_OK);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_decode_pld_buffer)
