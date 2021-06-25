<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: utxfinit - External पूर्णांकerfaces क्रम ACPICA initialization
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#घोषणा EXPORT_ACPI_INTERFACES

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acevents.h"
#समावेश "acnamesp.h"
#समावेश "acdebug.h"
#समावेश "actables.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utxfinit")

/* For acpi_exec only */
व्योम ae_करो_object_overrides(व्योम);

/*******************************************************************************
 *
 * FUNCTION:    acpi_initialize_subप्रणाली
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initializes all global variables. This is the first function
 *              called, so any early initialization beदीर्घs here.
 *
 ******************************************************************************/

acpi_status ACPI_INIT_FUNCTION acpi_initialize_subप्रणाली(व्योम)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_initialize_subप्रणाली);

	acpi_gbl_startup_flags = ACPI_SUBSYSTEM_INITIALIZE;
	ACPI_DEBUG_EXEC(acpi_ut_init_stack_ptr_trace());

	/* Initialize the OS-Dependent layer */

	status = acpi_os_initialize();
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_EXCEPTION((AE_INFO, status, "During OSL initialization"));
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Initialize all globals used by the subप्रणाली */

	status = acpi_ut_init_globals();
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_EXCEPTION((AE_INFO, status,
				"During initialization of globals"));
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Create the शेष mutex objects */

	status = acpi_ut_mutex_initialize();
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_EXCEPTION((AE_INFO, status,
				"During Global Mutex creation"));
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Initialize the namespace manager and
	 * the root of the namespace tree
	 */
	status = acpi_ns_root_initialize();
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_EXCEPTION((AE_INFO, status,
				"During Namespace initialization"));
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Initialize the global OSI पूर्णांकerfaces list with the अटल names */

	status = acpi_ut_initialize_पूर्णांकerfaces();
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_EXCEPTION((AE_INFO, status,
				"During OSI interfaces initialization"));
		वापस_ACPI_STATUS(status);
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

ACPI_EXPORT_SYMBOL_INIT(acpi_initialize_subप्रणाली)

/*******************************************************************************
 *
 * FUNCTION:    acpi_enable_subप्रणाली
 *
 * PARAMETERS:  flags               - Init/enable Options
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Completes the subप्रणाली initialization including hardware.
 *              Puts प्रणाली पूर्णांकo ACPI mode अगर it isn't alपढ़ोy.
 *
 ******************************************************************************/
acpi_status ACPI_INIT_FUNCTION acpi_enable_subप्रणाली(u32 flags)
अणु
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(acpi_enable_subप्रणाली);

	/*
	 * The early initialization phase is complete. The namespace is loaded,
	 * and we can now support address spaces other than Memory, I/O, and
	 * PCI_Config.
	 */
	acpi_gbl_early_initialization = FALSE;

#अगर (!ACPI_REDUCED_HARDWARE)

	/* Enable ACPI mode */

	अगर (!(flags & ACPI_NO_ACPI_ENABLE)) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "[Init] Going into ACPI mode\n"));

		acpi_gbl_original_mode = acpi_hw_get_mode();

		status = acpi_enable();
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_WARNING((AE_INFO, "AcpiEnable failed"));
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण

	/*
	 * Obtain a permanent mapping क्रम the FACS. This is required क्रम the
	 * Global Lock and the Firmware Waking Vector
	 */
	अगर (!(flags & ACPI_NO_FACS_INIT)) अणु
		status = acpi_tb_initialize_facs();
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_WARNING((AE_INFO, "Could not map the FACS table"));
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण

	/*
	 * Initialize ACPI Event handling (Fixed and General Purpose)
	 *
	 * Note1: We must have the hardware and events initialized beक्रमe we can
	 * execute any control methods safely. Any control method can require
	 * ACPI hardware support, so the hardware must be fully initialized beक्रमe
	 * any method execution!
	 *
	 * Note2: Fixed events are initialized and enabled here. GPEs are
	 * initialized, but cannot be enabled until after the hardware is
	 * completely initialized (SCI and global_lock activated) and the various
	 * initialization control methods are run (_REG, _STA, _INI) on the
	 * entire namespace.
	 */
	अगर (!(flags & ACPI_NO_EVENT_INIT)) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "[Init] Initializing ACPI events\n"));

		status = acpi_ev_initialize_events();
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण

	/*
	 * Install the SCI handler and Global Lock handler. This completes the
	 * hardware initialization.
	 */
	अगर (!(flags & ACPI_NO_HANDLER_INIT)) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "[Init] Installing SCI/GL handlers\n"));

		status = acpi_ev_install_xrupt_handlers();
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण
#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */

	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL_INIT(acpi_enable_subप्रणाली)

/*******************************************************************************
 *
 * FUNCTION:    acpi_initialize_objects
 *
 * PARAMETERS:  flags               - Init/enable Options
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Completes namespace initialization by initializing device
 *              objects and executing AML code क्रम Regions, buffers, etc.
 *
 ******************************************************************************/
acpi_status ACPI_INIT_FUNCTION acpi_initialize_objects(u32 flags)
अणु
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(acpi_initialize_objects);

#अगर_घोषित ACPI_OBSOLETE_BEHAVIOR
	/*
	 * 05/2019: Removed, initialization now happens at both object
	 * creation and table load समय
	 */

	/*
	 * Initialize the objects that reमुख्य uninitialized. This
	 * runs the executable AML that may be part of the
	 * declaration of these objects: operation_regions, buffer_fields,
	 * bank_fields, Buffers, and Packages.
	 */
	अगर (!(flags & ACPI_NO_OBJECT_INIT)) अणु
		status = acpi_ns_initialize_objects();
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/*
	 * Initialize all device/region objects in the namespace. This runs
	 * the device _STA and _INI methods and region _REG methods.
	 */
	अगर (!(flags & (ACPI_NO_DEVICE_INIT | ACPI_NO_ADDRESS_SPACE_INIT))) अणु
		status = acpi_ns_initialize_devices(flags);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण

	/*
	 * Empty the caches (delete the cached objects) on the assumption that
	 * the table load filled them up more than they will be at runसमय --
	 * thus wasting non-paged memory.
	 */
	status = acpi_purge_cached_objects();

	acpi_gbl_startup_flags |= ACPI_INITIALIZED_OK;
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL_INIT(acpi_initialize_objects)
