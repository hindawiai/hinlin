<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exप्रणाली - Interface to OS services
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acinterp.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exsystem")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_प्रणाली_रुको_semaphore
 *
 * PARAMETERS:  semaphore       - Semaphore to रुको on
 *              समयout         - Max समय to रुको
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Implements a semaphore रुको with a check to see अगर the
 *              semaphore is available immediately. If it is not, the
 *              पूर्णांकerpreter is released beक्रमe रुकोing.
 *
 ******************************************************************************/
acpi_status acpi_ex_प्रणाली_रुको_semaphore(acpi_semaphore semaphore, u16 समयout)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(ex_प्रणाली_रुको_semaphore);

	status = acpi_os_रुको_semaphore(semaphore, 1, ACPI_DO_NOT_WAIT);
	अगर (ACPI_SUCCESS(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	अगर (status == AE_TIME) अणु

		/* We must रुको, so unlock the पूर्णांकerpreter */

		acpi_ex_निकास_पूर्णांकerpreter();
		status = acpi_os_रुको_semaphore(semaphore, 1, समयout);

		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "*** Thread awake after blocking, %s\n",
				  acpi_क्रमmat_exception(status)));

		/* Reacquire the पूर्णांकerpreter */

		acpi_ex_enter_पूर्णांकerpreter();
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_प्रणाली_रुको_mutex
 *
 * PARAMETERS:  mutex           - Mutex to रुको on
 *              समयout         - Max समय to रुको
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Implements a mutex रुको with a check to see अगर the
 *              mutex is available immediately. If it is not, the
 *              पूर्णांकerpreter is released beक्रमe रुकोing.
 *
 ******************************************************************************/

acpi_status acpi_ex_प्रणाली_रुको_mutex(acpi_mutex mutex, u16 समयout)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(ex_प्रणाली_रुको_mutex);

	status = acpi_os_acquire_mutex(mutex, ACPI_DO_NOT_WAIT);
	अगर (ACPI_SUCCESS(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	अगर (status == AE_TIME) अणु

		/* We must रुको, so unlock the पूर्णांकerpreter */

		acpi_ex_निकास_पूर्णांकerpreter();
		status = acpi_os_acquire_mutex(mutex, समयout);

		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "*** Thread awake after blocking, %s\n",
				  acpi_क्रमmat_exception(status)));

		/* Reacquire the पूर्णांकerpreter */

		acpi_ex_enter_पूर्णांकerpreter();
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_प्रणाली_करो_stall
 *
 * PARAMETERS:  how_दीर्घ        - The amount of समय to stall,
 *                                in microseconds
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Suspend running thपढ़ो क्रम specअगरied amount of समय.
 *              Note: ACPI specअगरication requires that Stall() करोes not
 *              relinquish the processor, and delays दीर्घer than 100 usec
 *              should use Sleep() instead. We allow stalls up to 255 usec
 *              क्रम compatibility with other पूर्णांकerpreters and existing BIOSs.
 *
 ******************************************************************************/

acpi_status acpi_ex_प्रणाली_करो_stall(u32 how_दीर्घ)
अणु
	acpi_status status = AE_OK;

	ACPI_FUNCTION_ENTRY();

	अगर (how_दीर्घ > 255) अणु	/* 255 microseconds */
		/*
		 * Longer than 255 usec, this is an error
		 *
		 * (ACPI specअगरies 100 usec as max, but this gives some slack in
		 * order to support existing BIOSs)
		 */
		ACPI_ERROR((AE_INFO,
			    "Time parameter is too large (%u)", how_दीर्घ));
		status = AE_AML_OPERAND_VALUE;
	पूर्ण अन्यथा अणु
		acpi_os_stall(how_दीर्घ);
	पूर्ण

	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_प्रणाली_करो_sleep
 *
 * PARAMETERS:  how_दीर्घ        - The amount of समय to sleep,
 *                                in milliseconds
 *
 * RETURN:      None
 *
 * DESCRIPTION: Sleep the running thपढ़ो क्रम specअगरied amount of समय.
 *
 ******************************************************************************/

acpi_status acpi_ex_प्रणाली_करो_sleep(u64 how_दीर्घ)
अणु
	ACPI_FUNCTION_ENTRY();

	/* Since this thपढ़ो will sleep, we must release the पूर्णांकerpreter */

	acpi_ex_निकास_पूर्णांकerpreter();

	/*
	 * For compatibility with other ACPI implementations and to prevent
	 * accidental deep sleeps, limit the sleep समय to something reasonable.
	 */
	अगर (how_दीर्घ > ACPI_MAX_SLEEP) अणु
		how_दीर्घ = ACPI_MAX_SLEEP;
	पूर्ण

	acpi_os_sleep(how_दीर्घ);

	/* And now we must get the पूर्णांकerpreter again */

	acpi_ex_enter_पूर्णांकerpreter();
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_प्रणाली_संकेत_event
 *
 * PARAMETERS:  obj_desc        - The object descriptor क्रम this op
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Provides an access poपूर्णांक to perक्रमm synchronization operations
 *              within the AML.
 *
 ******************************************************************************/

acpi_status acpi_ex_प्रणाली_संकेत_event(जोड़ acpi_opeअक्रम_object * obj_desc)
अणु
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ex_प्रणाली_संकेत_event);

	अगर (obj_desc) अणु
		status =
		    acpi_os_संकेत_semaphore(obj_desc->event.os_semaphore, 1);
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_प्रणाली_रुको_event
 *
 * PARAMETERS:  समय_desc       - The 'time to delay' object descriptor
 *              obj_desc        - The object descriptor क्रम this op
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Provides an access poपूर्णांक to perक्रमm synchronization operations
 *              within the AML. This operation is a request to रुको क्रम an
 *              event.
 *
 ******************************************************************************/

acpi_status
acpi_ex_प्रणाली_रुको_event(जोड़ acpi_opeअक्रम_object *समय_desc,
			  जोड़ acpi_opeअक्रम_object *obj_desc)
अणु
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ex_प्रणाली_रुको_event);

	अगर (obj_desc) अणु
		status =
		    acpi_ex_प्रणाली_रुको_semaphore(obj_desc->event.os_semaphore,
						  (u16) समय_desc->पूर्णांकeger.
						  value);
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_प्रणाली_reset_event
 *
 * PARAMETERS:  obj_desc        - The object descriptor क्रम this op
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Reset an event to a known state.
 *
 ******************************************************************************/

acpi_status acpi_ex_प्रणाली_reset_event(जोड़ acpi_opeअक्रम_object *obj_desc)
अणु
	acpi_status status = AE_OK;
	acpi_semaphore temp_semaphore;

	ACPI_FUNCTION_ENTRY();

	/*
	 * We are going to simply delete the existing semaphore and
	 * create a new one!
	 */
	status =
	    acpi_os_create_semaphore(ACPI_NO_UNIT_LIMIT, 0, &temp_semaphore);
	अगर (ACPI_SUCCESS(status)) अणु
		(व्योम)acpi_os_delete_semaphore(obj_desc->event.os_semaphore);
		obj_desc->event.os_semaphore = temp_semaphore;
	पूर्ण

	वापस (status);
पूर्ण
