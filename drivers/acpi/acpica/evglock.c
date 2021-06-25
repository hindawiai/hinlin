<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: evglock - Global Lock support
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acevents.h"
#समावेश "acinterp.h"

#घोषणा _COMPONENT          ACPI_EVENTS
ACPI_MODULE_NAME("evglock")
#अगर (!ACPI_REDUCED_HARDWARE)	/* Entire module */
/* Local prototypes */
अटल u32 acpi_ev_global_lock_handler(व्योम *context);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_init_global_lock_handler
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install a handler क्रम the global lock release event
 *
 ******************************************************************************/

acpi_status acpi_ev_init_global_lock_handler(व्योम)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(ev_init_global_lock_handler);

	/* If Hardware Reduced flag is set, there is no global lock */

	अगर (acpi_gbl_reduced_hardware) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Attempt installation of the global lock handler */

	status = acpi_install_fixed_event_handler(ACPI_EVENT_GLOBAL,
						  acpi_ev_global_lock_handler,
						  शून्य);

	/*
	 * If the global lock करोes not exist on this platक्रमm, the attempt to
	 * enable GBL_STATUS will fail (the GBL_ENABLE bit will not stick).
	 * Map to AE_OK, but mark global lock as not present. Any attempt to
	 * actually use the global lock will be flagged with an error.
	 */
	acpi_gbl_global_lock_present = FALSE;
	अगर (status == AE_NO_HARDWARE_RESPONSE) अणु
		ACPI_ERROR((AE_INFO,
			    "No response from Global Lock hardware, disabling lock"));

		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	status = acpi_os_create_lock(&acpi_gbl_global_lock_pending_lock);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	acpi_gbl_global_lock_pending = FALSE;
	acpi_gbl_global_lock_present = TRUE;
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_हटाओ_global_lock_handler
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Remove the handler क्रम the Global Lock
 *
 ******************************************************************************/

acpi_status acpi_ev_हटाओ_global_lock_handler(व्योम)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(ev_हटाओ_global_lock_handler);

	acpi_gbl_global_lock_present = FALSE;
	status = acpi_हटाओ_fixed_event_handler(ACPI_EVENT_GLOBAL,
						 acpi_ev_global_lock_handler);

	acpi_os_delete_lock(acpi_gbl_global_lock_pending_lock);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_global_lock_handler
 *
 * PARAMETERS:  context         - From thपढ़ो पूर्णांकerface, not used
 *
 * RETURN:      ACPI_INTERRUPT_HANDLED
 *
 * DESCRIPTION: Invoked directly from the SCI handler when a global lock
 *              release पूर्णांकerrupt occurs. If there is actually a pending
 *              request क्रम the lock, संकेत the रुकोing thपढ़ो.
 *
 ******************************************************************************/

अटल u32 acpi_ev_global_lock_handler(व्योम *context)
अणु
	acpi_status status;
	acpi_cpu_flags flags;

	flags = acpi_os_acquire_lock(acpi_gbl_global_lock_pending_lock);

	/*
	 * If a request क्रम the global lock is not actually pending,
	 * we are करोne. This handles "spurious" global lock पूर्णांकerrupts
	 * which are possible (and have been seen) with bad BIOSs.
	 */
	अगर (!acpi_gbl_global_lock_pending) अणु
		जाओ cleanup_and_निकास;
	पूर्ण

	/*
	 * Send a unit to the global lock semaphore. The actual acquisition
	 * of the global lock will be perक्रमmed by the रुकोing thपढ़ो.
	 */
	status = acpi_os_संकेत_semaphore(acpi_gbl_global_lock_semaphore, 1);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_ERROR((AE_INFO, "Could not signal Global Lock semaphore"));
	पूर्ण

	acpi_gbl_global_lock_pending = FALSE;

cleanup_and_निकास:

	acpi_os_release_lock(acpi_gbl_global_lock_pending_lock, flags);
	वापस (ACPI_INTERRUPT_HANDLED);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_ev_acquire_global_lock
 *
 * PARAMETERS:  समयout         - Max समय to रुको क्रम the lock, in millisec.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Attempt to gain ownership of the Global Lock.
 *
 * MUTEX:       Interpreter must be locked
 *
 * Note: The original implementation allowed multiple thपढ़ोs to "acquire" the
 * Global Lock, and the OS would hold the lock until the last thपढ़ो had
 * released it. However, this could potentially starve the BIOS out of the
 * lock, especially in the हाल where there is a tight handshake between the
 * Embedded Controller driver and the BIOS. Thereक्रमe, this implementation
 * allows only one thपढ़ो to acquire the HW Global Lock at a समय, and makes
 * the global lock appear as a standard mutex on the OS side.
 *
 *****************************************************************************/

acpi_status acpi_ev_acquire_global_lock(u16 समयout)
अणु
	acpi_cpu_flags flags;
	acpi_status status;
	u8 acquired = FALSE;

	ACPI_FUNCTION_TRACE(ev_acquire_global_lock);

	/*
	 * Only one thपढ़ो can acquire the GL at a समय, the global_lock_mutex
	 * enक्रमces this. This पूर्णांकerface releases the पूर्णांकerpreter अगर we must रुको.
	 */
	status =
	    acpi_ex_प्रणाली_रुको_mutex(acpi_gbl_global_lock_mutex->mutex.
				      os_mutex, समयout);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Update the global lock handle and check क्रम wraparound. The handle is
	 * only used क्रम the बाह्यal global lock पूर्णांकerfaces, but it is updated
	 * here to properly handle the हाल where a single thपढ़ो may acquire the
	 * lock via both the AML and the acpi_acquire_global_lock पूर्णांकerfaces. The
	 * handle is thereक्रमe updated on the first acquire from a given thपढ़ो
	 * regardless of where the acquisition request originated.
	 */
	acpi_gbl_global_lock_handle++;
	अगर (acpi_gbl_global_lock_handle == 0) अणु
		acpi_gbl_global_lock_handle = 1;
	पूर्ण

	/*
	 * Make sure that a global lock actually exists. If not, just
	 * treat the lock as a standard mutex.
	 */
	अगर (!acpi_gbl_global_lock_present) अणु
		acpi_gbl_global_lock_acquired = TRUE;
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	flags = acpi_os_acquire_lock(acpi_gbl_global_lock_pending_lock);

	करो अणु

		/* Attempt to acquire the actual hardware lock */

		ACPI_ACQUIRE_GLOBAL_LOCK(acpi_gbl_FACS, acquired);
		अगर (acquired) अणु
			acpi_gbl_global_lock_acquired = TRUE;
			ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
					  "Acquired hardware Global Lock\n"));
			अवरोध;
		पूर्ण

		/*
		 * Did not get the lock. The pending bit was set above, and
		 * we must now रुको until we receive the global lock
		 * released पूर्णांकerrupt.
		 */
		acpi_gbl_global_lock_pending = TRUE;
		acpi_os_release_lock(acpi_gbl_global_lock_pending_lock, flags);

		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "Waiting for hardware Global Lock\n"));

		/*
		 * Wait क्रम handshake with the global lock पूर्णांकerrupt handler.
		 * This पूर्णांकerface releases the पूर्णांकerpreter अगर we must रुको.
		 */
		status =
		    acpi_ex_प्रणाली_रुको_semaphore
		    (acpi_gbl_global_lock_semaphore, ACPI_WAIT_FOREVER);

		flags = acpi_os_acquire_lock(acpi_gbl_global_lock_pending_lock);

	पूर्ण जबतक (ACPI_SUCCESS(status));

	acpi_gbl_global_lock_pending = FALSE;
	acpi_os_release_lock(acpi_gbl_global_lock_pending_lock, flags);

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_release_global_lock
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Releases ownership of the Global Lock.
 *
 ******************************************************************************/

acpi_status acpi_ev_release_global_lock(व्योम)
अणु
	u8 pending = FALSE;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ev_release_global_lock);

	/* Lock must be alपढ़ोy acquired */

	अगर (!acpi_gbl_global_lock_acquired) अणु
		ACPI_WARNING((AE_INFO,
			      "Cannot release the ACPI Global Lock, it has not been acquired"));
		वापस_ACPI_STATUS(AE_NOT_ACQUIRED);
	पूर्ण

	अगर (acpi_gbl_global_lock_present) अणु

		/* Allow any thपढ़ो to release the lock */

		ACPI_RELEASE_GLOBAL_LOCK(acpi_gbl_FACS, pending);

		/*
		 * If the pending bit was set, we must ग_लिखो GBL_RLS to the control
		 * रेजिस्टर
		 */
		अगर (pending) अणु
			status =
			    acpi_ग_लिखो_bit_रेजिस्टर
			    (ACPI_BITREG_GLOBAL_LOCK_RELEASE,
			     ACPI_ENABLE_EVENT);
		पूर्ण

		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "Released hardware Global Lock\n"));
	पूर्ण

	acpi_gbl_global_lock_acquired = FALSE;

	/* Release the local GL mutex */

	acpi_os_release_mutex(acpi_gbl_global_lock_mutex->mutex.os_mutex);
	वापस_ACPI_STATUS(status);
पूर्ण

#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */
