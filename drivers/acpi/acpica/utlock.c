<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: utlock - Reader/Writer lock पूर्णांकerfaces
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utlock")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_create_rw_lock
 *              acpi_ut_delete_rw_lock
 *
 * PARAMETERS:  lock                - Poपूर्णांकer to a valid RW lock
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Reader/ग_लिखोr lock creation and deletion पूर्णांकerfaces.
 *
 ******************************************************************************/
acpi_status acpi_ut_create_rw_lock(काष्ठा acpi_rw_lock *lock)
अणु
	acpi_status status;

	lock->num_पढ़ोers = 0;
	status = acpi_os_create_mutex(&lock->पढ़ोer_mutex);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	status = acpi_os_create_mutex(&lock->ग_लिखोr_mutex);
	वापस (status);
पूर्ण

व्योम acpi_ut_delete_rw_lock(काष्ठा acpi_rw_lock *lock)
अणु

	acpi_os_delete_mutex(lock->पढ़ोer_mutex);
	acpi_os_delete_mutex(lock->ग_लिखोr_mutex);

	lock->num_पढ़ोers = 0;
	lock->पढ़ोer_mutex = शून्य;
	lock->ग_लिखोr_mutex = शून्य;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_acquire_पढ़ो_lock
 *              acpi_ut_release_पढ़ो_lock
 *
 * PARAMETERS:  lock                - Poपूर्णांकer to a valid RW lock
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Reader पूर्णांकerfaces क्रम पढ़ोer/ग_लिखोr locks. On acquisition,
 *              only the first पढ़ोer acquires the ग_लिखो mutex. On release,
 *              only the last पढ़ोer releases the ग_लिखो mutex. Although this
 *              algorithm can in theory starve ग_लिखोrs, this should not be a
 *              problem with ACPICA since the subप्रणाली is infrequently used
 *              in comparison to (क्रम example) an I/O प्रणाली.
 *
 ******************************************************************************/

acpi_status acpi_ut_acquire_पढ़ो_lock(काष्ठा acpi_rw_lock *lock)
अणु
	acpi_status status;

	status = acpi_os_acquire_mutex(lock->पढ़ोer_mutex, ACPI_WAIT_FOREVER);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Acquire the ग_लिखो lock only क्रम the first पढ़ोer */

	lock->num_पढ़ोers++;
	अगर (lock->num_पढ़ोers == 1) अणु
		status =
		    acpi_os_acquire_mutex(lock->ग_लिखोr_mutex,
					  ACPI_WAIT_FOREVER);
	पूर्ण

	acpi_os_release_mutex(lock->पढ़ोer_mutex);
	वापस (status);
पूर्ण

acpi_status acpi_ut_release_पढ़ो_lock(काष्ठा acpi_rw_lock *lock)
अणु
	acpi_status status;

	status = acpi_os_acquire_mutex(lock->पढ़ोer_mutex, ACPI_WAIT_FOREVER);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Release the ग_लिखो lock only क्रम the very last पढ़ोer */

	lock->num_पढ़ोers--;
	अगर (lock->num_पढ़ोers == 0) अणु
		acpi_os_release_mutex(lock->ग_लिखोr_mutex);
	पूर्ण

	acpi_os_release_mutex(lock->पढ़ोer_mutex);
	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_acquire_ग_लिखो_lock
 *              acpi_ut_release_ग_लिखो_lock
 *
 * PARAMETERS:  lock                - Poपूर्णांकer to a valid RW lock
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Writer पूर्णांकerfaces क्रम पढ़ोer/ग_लिखोr locks. Simply acquire or
 *              release the ग_लिखोr mutex associated with the lock. Acquisition
 *              of the lock is fully exclusive and will block all पढ़ोers and
 *              ग_लिखोrs until it is released.
 *
 ******************************************************************************/

acpi_status acpi_ut_acquire_ग_लिखो_lock(काष्ठा acpi_rw_lock *lock)
अणु
	acpi_status status;

	status = acpi_os_acquire_mutex(lock->ग_लिखोr_mutex, ACPI_WAIT_FOREVER);
	वापस (status);
पूर्ण

व्योम acpi_ut_release_ग_लिखो_lock(काष्ठा acpi_rw_lock *lock)
अणु

	acpi_os_release_mutex(lock->ग_लिखोr_mutex);
पूर्ण
