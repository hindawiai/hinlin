<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: uपंचांगutex - local mutex support
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utmutex")

/* Local prototypes */
अटल acpi_status acpi_ut_create_mutex(acpi_mutex_handle mutex_id);

अटल व्योम acpi_ut_delete_mutex(acpi_mutex_handle mutex_id);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_mutex_initialize
 *
 * PARAMETERS:  None.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create the प्रणाली mutex objects. This includes mutexes,
 *              spin locks, and पढ़ोer/ग_लिखोr locks.
 *
 ******************************************************************************/

acpi_status acpi_ut_mutex_initialize(व्योम)
अणु
	u32 i;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ut_mutex_initialize);

	/* Create each of the predefined mutex objects */

	क्रम (i = 0; i < ACPI_NUM_MUTEX; i++) अणु
		status = acpi_ut_create_mutex(i);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण

	/* Create the spinlocks क्रम use at पूर्णांकerrupt level or क्रम speed */

	status = acpi_os_create_lock (&acpi_gbl_gpe_lock);
	अगर (ACPI_FAILURE (status)) अणु
		वापस_ACPI_STATUS (status);
	पूर्ण

	status = acpi_os_create_raw_lock(&acpi_gbl_hardware_lock);
	अगर (ACPI_FAILURE (status)) अणु
		वापस_ACPI_STATUS (status);
	पूर्ण

	status = acpi_os_create_lock(&acpi_gbl_reference_count_lock);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Mutex क्रम _OSI support */

	status = acpi_os_create_mutex(&acpi_gbl_osi_mutex);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Create the पढ़ोer/ग_लिखोr lock क्रम namespace access */

	status = acpi_ut_create_rw_lock(&acpi_gbl_namespace_rw_lock);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_mutex_terminate
 *
 * PARAMETERS:  None.
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Delete all of the प्रणाली mutex objects. This includes mutexes,
 *              spin locks, and पढ़ोer/ग_लिखोr locks.
 *
 ******************************************************************************/

व्योम acpi_ut_mutex_terminate(व्योम)
अणु
	u32 i;

	ACPI_FUNCTION_TRACE(ut_mutex_terminate);

	/* Delete each predefined mutex object */

	क्रम (i = 0; i < ACPI_NUM_MUTEX; i++) अणु
		acpi_ut_delete_mutex(i);
	पूर्ण

	acpi_os_delete_mutex(acpi_gbl_osi_mutex);

	/* Delete the spinlocks */

	acpi_os_delete_lock(acpi_gbl_gpe_lock);
	acpi_os_delete_raw_lock(acpi_gbl_hardware_lock);
	acpi_os_delete_lock(acpi_gbl_reference_count_lock);

	/* Delete the पढ़ोer/ग_लिखोr lock */

	acpi_ut_delete_rw_lock(&acpi_gbl_namespace_rw_lock);
	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_create_mutex
 *
 * PARAMETERS:  mutex_ID        - ID of the mutex to be created
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a mutex object.
 *
 ******************************************************************************/

अटल acpi_status acpi_ut_create_mutex(acpi_mutex_handle mutex_id)
अणु
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE_U32(ut_create_mutex, mutex_id);

	अगर (!acpi_gbl_mutex_info[mutex_id].mutex) अणु
		status =
		    acpi_os_create_mutex(&acpi_gbl_mutex_info[mutex_id].mutex);
		acpi_gbl_mutex_info[mutex_id].thपढ़ो_id =
		    ACPI_MUTEX_NOT_ACQUIRED;
		acpi_gbl_mutex_info[mutex_id].use_count = 0;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_delete_mutex
 *
 * PARAMETERS:  mutex_ID        - ID of the mutex to be deleted
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Delete a mutex object.
 *
 ******************************************************************************/

अटल व्योम acpi_ut_delete_mutex(acpi_mutex_handle mutex_id)
अणु

	ACPI_FUNCTION_TRACE_U32(ut_delete_mutex, mutex_id);

	acpi_os_delete_mutex(acpi_gbl_mutex_info[mutex_id].mutex);

	acpi_gbl_mutex_info[mutex_id].mutex = शून्य;
	acpi_gbl_mutex_info[mutex_id].thपढ़ो_id = ACPI_MUTEX_NOT_ACQUIRED;

	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_acquire_mutex
 *
 * PARAMETERS:  mutex_ID        - ID of the mutex to be acquired
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Acquire a mutex object.
 *
 ******************************************************************************/

acpi_status acpi_ut_acquire_mutex(acpi_mutex_handle mutex_id)
अणु
	acpi_status status;
	acpi_thपढ़ो_id this_thपढ़ो_id;

	ACPI_FUNCTION_NAME(ut_acquire_mutex);

	अगर (mutex_id > ACPI_MAX_MUTEX) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	this_thपढ़ो_id = acpi_os_get_thपढ़ो_id();

#अगर_घोषित ACPI_MUTEX_DEBUG
	अणु
		u32 i;
		/*
		 * Mutex debug code, क्रम पूर्णांकernal debugging only.
		 *
		 * Deadlock prevention. Check अगर this thपढ़ो owns any mutexes of value
		 * greater than or equal to this one. If so, the thपढ़ो has violated
		 * the mutex ordering rule. This indicates a coding error somewhere in
		 * the ACPI subप्रणाली code.
		 */
		क्रम (i = mutex_id; i < ACPI_NUM_MUTEX; i++) अणु
			अगर (acpi_gbl_mutex_info[i].thपढ़ो_id == this_thपढ़ो_id) अणु
				अगर (i == mutex_id) अणु
					ACPI_ERROR((AE_INFO,
						    "Mutex [%s] already acquired by this thread [%u]",
						    acpi_ut_get_mutex_name
						    (mutex_id),
						    (u32)this_thपढ़ो_id));

					वापस (AE_ALREADY_ACQUIRED);
				पूर्ण

				ACPI_ERROR((AE_INFO,
					    "Invalid acquire order: Thread %u owns [%s], wants [%s]",
					    (u32)this_thपढ़ो_id,
					    acpi_ut_get_mutex_name(i),
					    acpi_ut_get_mutex_name(mutex_id)));

				वापस (AE_ACQUIRE_DEADLOCK);
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	ACPI_DEBUG_PRINT((ACPI_DB_MUTEX,
			  "Thread %u attempting to acquire Mutex [%s]\n",
			  (u32)this_thपढ़ो_id,
			  acpi_ut_get_mutex_name(mutex_id)));

	status =
	    acpi_os_acquire_mutex(acpi_gbl_mutex_info[mutex_id].mutex,
				  ACPI_WAIT_FOREVER);
	अगर (ACPI_SUCCESS(status)) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_MUTEX,
				  "Thread %u acquired Mutex [%s]\n",
				  (u32)this_thपढ़ो_id,
				  acpi_ut_get_mutex_name(mutex_id)));

		acpi_gbl_mutex_info[mutex_id].use_count++;
		acpi_gbl_mutex_info[mutex_id].thपढ़ो_id = this_thपढ़ो_id;
	पूर्ण अन्यथा अणु
		ACPI_EXCEPTION((AE_INFO, status,
				"Thread %u could not acquire Mutex [%s] (0x%X)",
				(u32)this_thपढ़ो_id,
				acpi_ut_get_mutex_name(mutex_id), mutex_id));
	पूर्ण

	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_release_mutex
 *
 * PARAMETERS:  mutex_ID        - ID of the mutex to be released
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Release a mutex object.
 *
 ******************************************************************************/

acpi_status acpi_ut_release_mutex(acpi_mutex_handle mutex_id)
अणु
	ACPI_FUNCTION_NAME(ut_release_mutex);

	ACPI_DEBUG_PRINT((ACPI_DB_MUTEX, "Thread %u releasing Mutex [%s]\n",
			  (u32)acpi_os_get_thपढ़ो_id(),
			  acpi_ut_get_mutex_name(mutex_id)));

	अगर (mutex_id > ACPI_MAX_MUTEX) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	/*
	 * Mutex must be acquired in order to release it!
	 */
	अगर (acpi_gbl_mutex_info[mutex_id].thपढ़ो_id == ACPI_MUTEX_NOT_ACQUIRED) अणु
		ACPI_ERROR((AE_INFO,
			    "Mutex [%s] (0x%X) is not acquired, cannot release",
			    acpi_ut_get_mutex_name(mutex_id), mutex_id));

		वापस (AE_NOT_ACQUIRED);
	पूर्ण
#अगर_घोषित ACPI_MUTEX_DEBUG
	अणु
		u32 i;
		/*
		 * Mutex debug code, क्रम पूर्णांकernal debugging only.
		 *
		 * Deadlock prevention. Check अगर this thपढ़ो owns any mutexes of value
		 * greater than this one. If so, the thपढ़ो has violated the mutex
		 * ordering rule. This indicates a coding error somewhere in
		 * the ACPI subप्रणाली code.
		 */
		क्रम (i = mutex_id; i < ACPI_NUM_MUTEX; i++) अणु
			अगर (acpi_gbl_mutex_info[i].thपढ़ो_id ==
			    acpi_os_get_thपढ़ो_id()) अणु
				अगर (i == mutex_id) अणु
					जारी;
				पूर्ण

				ACPI_ERROR((AE_INFO,
					    "Invalid release order: owns [%s], releasing [%s]",
					    acpi_ut_get_mutex_name(i),
					    acpi_ut_get_mutex_name(mutex_id)));

				वापस (AE_RELEASE_DEADLOCK);
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* Mark unlocked FIRST */

	acpi_gbl_mutex_info[mutex_id].thपढ़ो_id = ACPI_MUTEX_NOT_ACQUIRED;

	acpi_os_release_mutex(acpi_gbl_mutex_info[mutex_id].mutex);
	वापस (AE_OK);
पूर्ण
