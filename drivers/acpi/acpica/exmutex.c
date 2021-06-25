<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exmutex - ASL Mutex Acquire/Release functions
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acinterp.h"
#समावेश "acevents.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exmutex")

/* Local prototypes */
अटल व्योम
acpi_ex_link_mutex(जोड़ acpi_opeअक्रम_object *obj_desc,
		   काष्ठा acpi_thपढ़ो_state *thपढ़ो);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_unlink_mutex
 *
 * PARAMETERS:  obj_desc            - The mutex to be unlinked
 *
 * RETURN:      None
 *
 * DESCRIPTION: Remove a mutex from the "AcquiredMutex" list
 *
 ******************************************************************************/

व्योम acpi_ex_unlink_mutex(जोड़ acpi_opeअक्रम_object *obj_desc)
अणु
	काष्ठा acpi_thपढ़ो_state *thपढ़ो = obj_desc->mutex.owner_thपढ़ो;

	अगर (!thपढ़ो) अणु
		वापस;
	पूर्ण

	/* Doubly linked list */

	अगर (obj_desc->mutex.next) अणु
		(obj_desc->mutex.next)->mutex.prev = obj_desc->mutex.prev;
	पूर्ण

	अगर (obj_desc->mutex.prev) अणु
		(obj_desc->mutex.prev)->mutex.next = obj_desc->mutex.next;

		/*
		 * Migrate the previous sync level associated with this mutex to
		 * the previous mutex on the list so that it may be preserved.
		 * This handles the हाल where several mutexes have been acquired
		 * at the same level, but are not released in opposite order.
		 */
		(obj_desc->mutex.prev)->mutex.original_sync_level =
		    obj_desc->mutex.original_sync_level;
	पूर्ण अन्यथा अणु
		thपढ़ो->acquired_mutex_list = obj_desc->mutex.next;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_link_mutex
 *
 * PARAMETERS:  obj_desc            - The mutex to be linked
 *              thपढ़ो              - Current executing thपढ़ो object
 *
 * RETURN:      None
 *
 * DESCRIPTION: Add a mutex to the "AcquiredMutex" list क्रम this walk
 *
 ******************************************************************************/

अटल व्योम
acpi_ex_link_mutex(जोड़ acpi_opeअक्रम_object *obj_desc,
		   काष्ठा acpi_thपढ़ो_state *thपढ़ो)
अणु
	जोड़ acpi_opeअक्रम_object *list_head;

	list_head = thपढ़ो->acquired_mutex_list;

	/* This object will be the first object in the list */

	obj_desc->mutex.prev = शून्य;
	obj_desc->mutex.next = list_head;

	/* Update old first object to poपूर्णांक back to this object */

	अगर (list_head) अणु
		list_head->mutex.prev = obj_desc;
	पूर्ण

	/* Update list head */

	thपढ़ो->acquired_mutex_list = obj_desc;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_acquire_mutex_object
 *
 * PARAMETERS:  समयout             - Timeout in milliseconds
 *              obj_desc            - Mutex object
 *              thपढ़ो_id           - Current thपढ़ो state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Acquire an AML mutex, low-level पूर्णांकerface. Provides a common
 *              path that supports multiple acquires by the same thपढ़ो.
 *
 * MUTEX:       Interpreter must be locked
 *
 * NOTE: This पूर्णांकerface is called from three places:
 * 1) From acpi_ex_acquire_mutex, via an AML Acquire() चालक
 * 2) From acpi_ex_acquire_global_lock when an AML Field access requires the
 *    global lock
 * 3) From the बाह्यal पूर्णांकerface, acpi_acquire_global_lock
 *
 ******************************************************************************/

acpi_status
acpi_ex_acquire_mutex_object(u16 समयout,
			     जोड़ acpi_opeअक्रम_object *obj_desc,
			     acpi_thपढ़ो_id thपढ़ो_id)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE_PTR(ex_acquire_mutex_object, obj_desc);

	अगर (!obj_desc) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Support क्रम multiple acquires by the owning thपढ़ो */

	अगर (obj_desc->mutex.thपढ़ो_id == thपढ़ो_id) अणु
		/*
		 * The mutex is alपढ़ोy owned by this thपढ़ो, just increment the
		 * acquisition depth
		 */
		obj_desc->mutex.acquisition_depth++;
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Acquire the mutex, रुको अगर necessary. Special हाल क्रम Global Lock */

	अगर (obj_desc == acpi_gbl_global_lock_mutex) अणु
		status = acpi_ev_acquire_global_lock(समयout);
	पूर्ण अन्यथा अणु
		status =
		    acpi_ex_प्रणाली_रुको_mutex(obj_desc->mutex.os_mutex,
					      समयout);
	पूर्ण

	अगर (ACPI_FAILURE(status)) अणु

		/* Includes failure from a समयout on समय_desc */

		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Acquired the mutex: update mutex object */

	obj_desc->mutex.thपढ़ो_id = thपढ़ो_id;
	obj_desc->mutex.acquisition_depth = 1;
	obj_desc->mutex.original_sync_level = 0;
	obj_desc->mutex.owner_thपढ़ो = शून्य;	/* Used only क्रम AML Acquire() */

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_acquire_mutex
 *
 * PARAMETERS:  समय_desc           - Timeout पूर्णांकeger
 *              obj_desc            - Mutex object
 *              walk_state          - Current method execution state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Acquire an AML mutex
 *
 ******************************************************************************/

acpi_status
acpi_ex_acquire_mutex(जोड़ acpi_opeअक्रम_object *समय_desc,
		      जोड़ acpi_opeअक्रम_object *obj_desc,
		      काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE_PTR(ex_acquire_mutex, obj_desc);

	अगर (!obj_desc) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Must have a valid thपढ़ो state काष्ठा */

	अगर (!walk_state->thपढ़ो) अणु
		ACPI_ERROR((AE_INFO,
			    "Cannot acquire Mutex [%4.4s], null thread info",
			    acpi_ut_get_node_name(obj_desc->mutex.node)));
		वापस_ACPI_STATUS(AE_AML_INTERNAL);
	पूर्ण

	/*
	 * Current sync level must be less than or equal to the sync level
	 * of the mutex. This mechanism provides some deadlock prevention.
	 */
	अगर (walk_state->thपढ़ो->current_sync_level > obj_desc->mutex.sync_level) अणु
		ACPI_ERROR((AE_INFO,
			    "Cannot acquire Mutex [%4.4s], "
			    "current SyncLevel is too large (%u)",
			    acpi_ut_get_node_name(obj_desc->mutex.node),
			    walk_state->thपढ़ो->current_sync_level));
		वापस_ACPI_STATUS(AE_AML_MUTEX_ORDER);
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "Acquiring: Mutex SyncLevel %u, Thread SyncLevel %u, "
			  "Depth %u TID %p\n",
			  obj_desc->mutex.sync_level,
			  walk_state->thपढ़ो->current_sync_level,
			  obj_desc->mutex.acquisition_depth,
			  walk_state->thपढ़ो));

	status = acpi_ex_acquire_mutex_object((u16)समय_desc->पूर्णांकeger.value,
					      obj_desc,
					      walk_state->thपढ़ो->thपढ़ो_id);

	अगर (ACPI_SUCCESS(status) && obj_desc->mutex.acquisition_depth == 1) अणु

		/* Save Thपढ़ो object, original/current sync levels */

		obj_desc->mutex.owner_thपढ़ो = walk_state->thपढ़ो;
		obj_desc->mutex.original_sync_level =
		    walk_state->thपढ़ो->current_sync_level;
		walk_state->thपढ़ो->current_sync_level =
		    obj_desc->mutex.sync_level;

		/* Link the mutex to the current thपढ़ो क्रम क्रमce-unlock at method निकास */

		acpi_ex_link_mutex(obj_desc, walk_state->thपढ़ो);
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "Acquired: Mutex SyncLevel %u, Thread SyncLevel %u, Depth %u\n",
			  obj_desc->mutex.sync_level,
			  walk_state->thपढ़ो->current_sync_level,
			  obj_desc->mutex.acquisition_depth));

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_release_mutex_object
 *
 * PARAMETERS:  obj_desc            - The object descriptor क्रम this op
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Release a previously acquired Mutex, low level पूर्णांकerface.
 *              Provides a common path that supports multiple releases (after
 *              previous multiple acquires) by the same thपढ़ो.
 *
 * MUTEX:       Interpreter must be locked
 *
 * NOTE: This पूर्णांकerface is called from three places:
 * 1) From acpi_ex_release_mutex, via an AML Acquire() चालक
 * 2) From acpi_ex_release_global_lock when an AML Field access requires the
 *    global lock
 * 3) From the बाह्यal पूर्णांकerface, acpi_release_global_lock
 *
 ******************************************************************************/

acpi_status acpi_ex_release_mutex_object(जोड़ acpi_opeअक्रम_object *obj_desc)
अणु
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ex_release_mutex_object);

	अगर (obj_desc->mutex.acquisition_depth == 0) अणु
		वापस_ACPI_STATUS(AE_NOT_ACQUIRED);
	पूर्ण

	/* Match multiple Acquires with multiple Releases */

	obj_desc->mutex.acquisition_depth--;
	अगर (obj_desc->mutex.acquisition_depth != 0) अणु

		/* Just decrement the depth and वापस */

		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	अगर (obj_desc->mutex.owner_thपढ़ो) अणु

		/* Unlink the mutex from the owner's list */

		acpi_ex_unlink_mutex(obj_desc);
		obj_desc->mutex.owner_thपढ़ो = शून्य;
	पूर्ण

	/* Release the mutex, special हाल क्रम Global Lock */

	अगर (obj_desc == acpi_gbl_global_lock_mutex) अणु
		status = acpi_ev_release_global_lock();
	पूर्ण अन्यथा अणु
		acpi_os_release_mutex(obj_desc->mutex.os_mutex);
	पूर्ण

	/* Clear mutex info */

	obj_desc->mutex.thपढ़ो_id = 0;
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_release_mutex
 *
 * PARAMETERS:  obj_desc            - The object descriptor क्रम this op
 *              walk_state          - Current method execution state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Release a previously acquired Mutex.
 *
 ******************************************************************************/

acpi_status
acpi_ex_release_mutex(जोड़ acpi_opeअक्रम_object *obj_desc,
		      काष्ठा acpi_walk_state *walk_state)
अणु
	u8 previous_sync_level;
	काष्ठा acpi_thपढ़ो_state *owner_thपढ़ो;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(ex_release_mutex);

	अगर (!obj_desc) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	owner_thपढ़ो = obj_desc->mutex.owner_thपढ़ो;

	/* The mutex must have been previously acquired in order to release it */

	अगर (!owner_thपढ़ो) अणु
		ACPI_ERROR((AE_INFO,
			    "Cannot release Mutex [%4.4s], not acquired",
			    acpi_ut_get_node_name(obj_desc->mutex.node)));
		वापस_ACPI_STATUS(AE_AML_MUTEX_NOT_ACQUIRED);
	पूर्ण

	/* Must have a valid thपढ़ो ID */

	अगर (!walk_state->thपढ़ो) अणु
		ACPI_ERROR((AE_INFO,
			    "Cannot release Mutex [%4.4s], null thread info",
			    acpi_ut_get_node_name(obj_desc->mutex.node)));
		वापस_ACPI_STATUS(AE_AML_INTERNAL);
	पूर्ण

	/*
	 * The Mutex is owned, but this thपढ़ो must be the owner.
	 * Special हाल क्रम Global Lock, any thपढ़ो can release
	 */
	अगर ((owner_thपढ़ो->thपढ़ो_id != walk_state->thपढ़ो->thपढ़ो_id) &&
	    (obj_desc != acpi_gbl_global_lock_mutex)) अणु
		ACPI_ERROR((AE_INFO,
			    "Thread %u cannot release Mutex [%4.4s] acquired by thread %u",
			    (u32)walk_state->thपढ़ो->thपढ़ो_id,
			    acpi_ut_get_node_name(obj_desc->mutex.node),
			    (u32)owner_thपढ़ो->thपढ़ो_id));
		वापस_ACPI_STATUS(AE_AML_NOT_OWNER);
	पूर्ण

	/*
	 * The sync level of the mutex must be equal to the current sync level. In
	 * other words, the current level means that at least one mutex at that
	 * level is currently being held. Attempting to release a mutex of a
	 * dअगरferent level can only mean that the mutex ordering rule is being
	 * violated. This behavior is clarअगरied in ACPI 4.0 specअगरication.
	 */
	अगर (obj_desc->mutex.sync_level != owner_thपढ़ो->current_sync_level) अणु
		ACPI_ERROR((AE_INFO,
			    "Cannot release Mutex [%4.4s], SyncLevel mismatch: "
			    "mutex %u current %u",
			    acpi_ut_get_node_name(obj_desc->mutex.node),
			    obj_desc->mutex.sync_level,
			    walk_state->thपढ़ो->current_sync_level));
		वापस_ACPI_STATUS(AE_AML_MUTEX_ORDER);
	पूर्ण

	/*
	 * Get the previous sync_level from the head of the acquired mutex list.
	 * This handles the हाल where several mutexes at the same level have been
	 * acquired, but are not released in reverse order.
	 */
	previous_sync_level =
	    owner_thपढ़ो->acquired_mutex_list->mutex.original_sync_level;

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "Releasing: Object SyncLevel %u, Thread SyncLevel %u, "
			  "Prev SyncLevel %u, Depth %u TID %p\n",
			  obj_desc->mutex.sync_level,
			  walk_state->thपढ़ो->current_sync_level,
			  previous_sync_level,
			  obj_desc->mutex.acquisition_depth,
			  walk_state->thपढ़ो));

	status = acpi_ex_release_mutex_object(obj_desc);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	अगर (obj_desc->mutex.acquisition_depth == 0) अणु

		/* Restore the previous sync_level */

		owner_thपढ़ो->current_sync_level = previous_sync_level;
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "Released: Object SyncLevel %u, Thread SyncLevel, %u, "
			  "Prev SyncLevel %u, Depth %u\n",
			  obj_desc->mutex.sync_level,
			  walk_state->thपढ़ो->current_sync_level,
			  previous_sync_level,
			  obj_desc->mutex.acquisition_depth));

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_release_all_mutexes
 *
 * PARAMETERS:  thपढ़ो              - Current executing thपढ़ो object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Release all mutexes held by this thपढ़ो
 *
 * NOTE: This function is called as the thपढ़ो is निकासing the पूर्णांकerpreter.
 * Mutexes are not released when an inभागidual control method is निकासed, but
 * only when the parent thपढ़ो actually निकासs the पूर्णांकerpreter. This allows one
 * method to acquire a mutex, and a dअगरferent method to release it, as दीर्घ as
 * this is perक्रमmed underneath a single parent control method.
 *
 ******************************************************************************/

व्योम acpi_ex_release_all_mutexes(काष्ठा acpi_thपढ़ो_state *thपढ़ो)
अणु
	जोड़ acpi_opeअक्रम_object *next = thपढ़ो->acquired_mutex_list;
	जोड़ acpi_opeअक्रम_object *obj_desc;

	ACPI_FUNCTION_TRACE(ex_release_all_mutexes);

	/* Traverse the list of owned mutexes, releasing each one */

	जबतक (next) अणु
		obj_desc = next;
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "Mutex [%4.4s] force-release, SyncLevel %u Depth %u\n",
				  obj_desc->mutex.node->name.ascii,
				  obj_desc->mutex.sync_level,
				  obj_desc->mutex.acquisition_depth));

		/* Release the mutex, special हाल क्रम Global Lock */

		अगर (obj_desc == acpi_gbl_global_lock_mutex) अणु

			/* Ignore errors */

			(व्योम)acpi_ev_release_global_lock();
		पूर्ण अन्यथा अणु
			acpi_os_release_mutex(obj_desc->mutex.os_mutex);
		पूर्ण

		/* Update Thपढ़ो sync_level (Last mutex is the important one) */

		thपढ़ो->current_sync_level =
		    obj_desc->mutex.original_sync_level;

		/* Mark mutex unowned */

		next = obj_desc->mutex.next;

		obj_desc->mutex.prev = शून्य;
		obj_desc->mutex.next = शून्य;
		obj_desc->mutex.acquisition_depth = 0;
		obj_desc->mutex.owner_thपढ़ो = शून्य;
		obj_desc->mutex.thपढ़ो_id = 0;
	पूर्ण

	वापस_VOID;
पूर्ण
