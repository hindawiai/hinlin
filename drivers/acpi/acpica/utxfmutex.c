<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: utxfmutex - बाह्यal AML mutex access functions
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utxfmutex")

/* Local prototypes */
अटल acpi_status
acpi_ut_get_mutex_object(acpi_handle handle,
			 acpi_string pathname,
			 जोड़ acpi_opeअक्रम_object **ret_obj);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_mutex_object
 *
 * PARAMETERS:  handle              - Mutex or prefix handle (optional)
 *              pathname            - Mutex pathname (optional)
 *              ret_obj             - Where the mutex object is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get an AML mutex object. The mutex node is poपूर्णांकed to by
 *              Handle:Pathname. Either Handle or Pathname can be शून्य, but
 *              not both.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ut_get_mutex_object(acpi_handle handle,
			 acpi_string pathname,
			 जोड़ acpi_opeअक्रम_object **ret_obj)
अणु
	काष्ठा acpi_namespace_node *mutex_node;
	जोड़ acpi_opeअक्रम_object *mutex_obj;
	acpi_status status;

	/* Parameter validation */

	अगर (!ret_obj || (!handle && !pathname)) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	/* Get a the namespace node क्रम the mutex */

	mutex_node = handle;
	अगर (pathname != शून्य) अणु
		status =
		    acpi_get_handle(handle, pathname,
				    ACPI_CAST_PTR(acpi_handle, &mutex_node));
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण
	पूर्ण

	/* Ensure that we actually have a Mutex object */

	अगर (!mutex_node || (mutex_node->type != ACPI_TYPE_MUTEX)) अणु
		वापस (AE_TYPE);
	पूर्ण

	/* Get the low-level mutex object */

	mutex_obj = acpi_ns_get_attached_object(mutex_node);
	अगर (!mutex_obj) अणु
		वापस (AE_शून्य_OBJECT);
	पूर्ण

	*ret_obj = mutex_obj;
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_acquire_mutex
 *
 * PARAMETERS:  handle              - Mutex or prefix handle (optional)
 *              pathname            - Mutex pathname (optional)
 *              समयout             - Max समय to रुको क्रम the lock (millisec)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Acquire an AML mutex. This is a device driver पूर्णांकerface to
 *              AML mutex objects, and allows क्रम transaction locking between
 *              drivers and AML code. The mutex node is poपूर्णांकed to by
 *              Handle:Pathname. Either Handle or Pathname can be शून्य, but
 *              not both.
 *
 ******************************************************************************/

acpi_status
acpi_acquire_mutex(acpi_handle handle, acpi_string pathname, u16 समयout)
अणु
	acpi_status status;
	जोड़ acpi_opeअक्रम_object *mutex_obj;

	/* Get the low-level mutex associated with Handle:Pathname */

	status = acpi_ut_get_mutex_object(handle, pathname, &mutex_obj);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Acquire the OS mutex */

	status = acpi_os_acquire_mutex(mutex_obj->mutex.os_mutex, समयout);
	वापस (status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_acquire_mutex)

/*******************************************************************************
 *
 * FUNCTION:    acpi_release_mutex
 *
 * PARAMETERS:  handle              - Mutex or prefix handle (optional)
 *              pathname            - Mutex pathname (optional)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Release an AML mutex. This is a device driver पूर्णांकerface to
 *              AML mutex objects, and allows क्रम transaction locking between
 *              drivers and AML code. The mutex node is poपूर्णांकed to by
 *              Handle:Pathname. Either Handle or Pathname can be शून्य, but
 *              not both.
 *
 ******************************************************************************/
acpi_status acpi_release_mutex(acpi_handle handle, acpi_string pathname)
अणु
	acpi_status status;
	जोड़ acpi_opeअक्रम_object *mutex_obj;

	/* Get the low-level mutex associated with Handle:Pathname */

	status = acpi_ut_get_mutex_object(handle, pathname, &mutex_obj);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Release the OS mutex */

	acpi_os_release_mutex(mutex_obj->mutex.os_mutex);
	वापस (AE_OK);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_release_mutex)
