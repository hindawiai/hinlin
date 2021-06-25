<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: utinit - Common ACPI subप्रणाली initialization
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"
#समावेश "acevents.h"
#समावेश "actables.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utinit")

/* Local prototypes */
अटल व्योम acpi_ut_terminate(व्योम);

#अगर (!ACPI_REDUCED_HARDWARE)

अटल व्योम acpi_ut_मुक्त_gpe_lists(व्योम);

#अन्यथा

#घोषणा acpi_ut_मुक्त_gpe_lists()
#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */

#अगर (!ACPI_REDUCED_HARDWARE)
/******************************************************************************
 *
 * FUNCTION:    acpi_ut_मुक्त_gpe_lists
 *
 * PARAMETERS:  none
 *
 * RETURN:      none
 *
 * DESCRIPTION: Free global GPE lists
 *
 ******************************************************************************/

अटल व्योम acpi_ut_मुक्त_gpe_lists(व्योम)
अणु
	काष्ठा acpi_gpe_block_info *gpe_block;
	काष्ठा acpi_gpe_block_info *next_gpe_block;
	काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_info;
	काष्ठा acpi_gpe_xrupt_info *next_gpe_xrupt_info;

	/* Free global GPE blocks and related info काष्ठाures */

	gpe_xrupt_info = acpi_gbl_gpe_xrupt_list_head;
	जबतक (gpe_xrupt_info) अणु
		gpe_block = gpe_xrupt_info->gpe_block_list_head;
		जबतक (gpe_block) अणु
			next_gpe_block = gpe_block->next;
			ACPI_FREE(gpe_block->event_info);
			ACPI_FREE(gpe_block->रेजिस्टर_info);
			ACPI_FREE(gpe_block);

			gpe_block = next_gpe_block;
		पूर्ण
		next_gpe_xrupt_info = gpe_xrupt_info->next;
		ACPI_FREE(gpe_xrupt_info);
		gpe_xrupt_info = next_gpe_xrupt_info;
	पूर्ण
पूर्ण
#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_init_globals
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initialize ACPICA globals. All globals that require specअगरic
 *              initialization should be initialized here. This allows क्रम
 *              a warm restart.
 *
 ******************************************************************************/

acpi_status acpi_ut_init_globals(व्योम)
अणु
	acpi_status status;
	u32 i;

	ACPI_FUNCTION_TRACE(ut_init_globals);

	/* Create all memory caches */

	status = acpi_ut_create_caches();
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Address Range lists */

	क्रम (i = 0; i < ACPI_ADDRESS_RANGE_MAX; i++) अणु
		acpi_gbl_address_range_list[i] = शून्य;
	पूर्ण

	/* Mutex locked flags */

	क्रम (i = 0; i < ACPI_NUM_MUTEX; i++) अणु
		acpi_gbl_mutex_info[i].mutex = शून्य;
		acpi_gbl_mutex_info[i].thपढ़ो_id = ACPI_MUTEX_NOT_ACQUIRED;
		acpi_gbl_mutex_info[i].use_count = 0;
	पूर्ण

	क्रम (i = 0; i < ACPI_NUM_OWNERID_MASKS; i++) अणु
		acpi_gbl_owner_id_mask[i] = 0;
	पूर्ण

	/* Last owner_ID is never valid */

	acpi_gbl_owner_id_mask[ACPI_NUM_OWNERID_MASKS - 1] = 0x80000000;

	/* Event counters */

	acpi_method_count = 0;
	acpi_sci_count = 0;
	acpi_gpe_count = 0;

	क्रम (i = 0; i < ACPI_NUM_FIXED_EVENTS; i++) अणु
		acpi_fixed_event_count[i] = 0;
	पूर्ण

#अगर (!ACPI_REDUCED_HARDWARE)

	/* GPE/SCI support */

	acpi_gbl_all_gpes_initialized = FALSE;
	acpi_gbl_gpe_xrupt_list_head = शून्य;
	acpi_gbl_gpe_fadt_blocks[0] = शून्य;
	acpi_gbl_gpe_fadt_blocks[1] = शून्य;
	acpi_current_gpe_count = 0;

	acpi_gbl_global_event_handler = शून्य;
	acpi_gbl_sci_handler_list = शून्य;

#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */

	/* Global handlers */

	acpi_gbl_global_notअगरy[0].handler = शून्य;
	acpi_gbl_global_notअगरy[1].handler = शून्य;
	acpi_gbl_exception_handler = शून्य;
	acpi_gbl_init_handler = शून्य;
	acpi_gbl_table_handler = शून्य;
	acpi_gbl_पूर्णांकerface_handler = शून्य;

	/* Global Lock support */

	acpi_gbl_global_lock_semaphore = शून्य;
	acpi_gbl_global_lock_mutex = शून्य;
	acpi_gbl_global_lock_acquired = FALSE;
	acpi_gbl_global_lock_handle = 0;
	acpi_gbl_global_lock_present = FALSE;

	/* Miscellaneous variables */

	acpi_gbl_DSDT = शून्य;
	acpi_gbl_cm_single_step = FALSE;
	acpi_gbl_shutकरोwn = FALSE;
	acpi_gbl_ns_lookup_count = 0;
	acpi_gbl_ps_find_count = 0;
	acpi_gbl_acpi_hardware_present = TRUE;
	acpi_gbl_last_owner_id_index = 0;
	acpi_gbl_next_owner_id_offset = 0;
	acpi_gbl_debugger_configuration = DEBUGGER_THREADING;
	acpi_gbl_osi_mutex = शून्य;

	/* Hardware oriented */

	acpi_gbl_events_initialized = FALSE;
	acpi_gbl_प्रणाली_awake_and_running = TRUE;

	/* Namespace */

	acpi_gbl_root_node = शून्य;
	acpi_gbl_root_node_काष्ठा.name.पूर्णांकeger = ACPI_ROOT_NAME;
	acpi_gbl_root_node_काष्ठा.descriptor_type = ACPI_DESC_TYPE_NAMED;
	acpi_gbl_root_node_काष्ठा.type = ACPI_TYPE_DEVICE;
	acpi_gbl_root_node_काष्ठा.parent = शून्य;
	acpi_gbl_root_node_काष्ठा.child = शून्य;
	acpi_gbl_root_node_काष्ठा.peer = शून्य;
	acpi_gbl_root_node_काष्ठा.object = शून्य;

#अगर_घोषित ACPI_DISASSEMBLER
	acpi_gbl_बाह्यal_list = शून्य;
	acpi_gbl_num_बाह्यal_methods = 0;
	acpi_gbl_resolved_बाह्यal_methods = 0;
#पूर्ण_अगर

#अगर_घोषित ACPI_DEBUG_OUTPUT
	acpi_gbl_lowest_stack_poपूर्णांकer = ACPI_CAST_PTR(acpi_size, ACPI_SIZE_MAX);
#पूर्ण_अगर

#अगर_घोषित ACPI_DBG_TRACK_ALLOCATIONS
	acpi_gbl_display_final_mem_stats = FALSE;
	acpi_gbl_disable_mem_tracking = FALSE;
#पूर्ण_अगर

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_ut_terminate
 *
 * PARAMETERS:  none
 *
 * RETURN:      none
 *
 * DESCRIPTION: Free global memory
 *
 ******************************************************************************/

अटल व्योम acpi_ut_terminate(व्योम)
अणु
	ACPI_FUNCTION_TRACE(ut_terminate);

	acpi_ut_मुक्त_gpe_lists();
	acpi_ut_delete_address_lists();
	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_subप्रणाली_shutकरोwn
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Shutकरोwn the various components. Do not delete the mutex
 *              objects here, because the AML debugger may be still running.
 *
 ******************************************************************************/

व्योम acpi_ut_subप्रणाली_shutकरोwn(व्योम)
अणु
	ACPI_FUNCTION_TRACE(ut_subप्रणाली_shutकरोwn);

	/* Just निकास अगर subप्रणाली is alपढ़ोy shutकरोwn */

	अगर (acpi_gbl_shutकरोwn) अणु
		ACPI_ERROR((AE_INFO, "ACPI Subsystem is already terminated"));
		वापस_VOID;
	पूर्ण

	/* Subप्रणाली appears active, go ahead and shut it करोwn */

	acpi_gbl_shutकरोwn = TRUE;
	acpi_gbl_startup_flags = 0;
	ACPI_DEBUG_PRINT((ACPI_DB_INFO, "Shutting down ACPI Subsystem\n"));

#अगर_अघोषित ACPI_ASL_COMPILER

	/* Close the acpi_event Handling */

	acpi_ev_terminate();

	/* Delete any dynamic _OSI पूर्णांकerfaces */

	acpi_ut_पूर्णांकerface_terminate();
#पूर्ण_अगर

	/* Close the Namespace */

	acpi_ns_terminate();

	/* Delete the ACPI tables */

	acpi_tb_terminate();

	/* Close the globals */

	acpi_ut_terminate();

	/* Purge the local caches */

	(व्योम)acpi_ut_delete_caches();
	वापस_VOID;
पूर्ण
