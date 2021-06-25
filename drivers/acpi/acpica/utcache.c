<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: utcache - local cache allocation routines
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utcache")

#अगर_घोषित ACPI_USE_LOCAL_CACHE
/*******************************************************************************
 *
 * FUNCTION:    acpi_os_create_cache
 *
 * PARAMETERS:  cache_name      - Ascii name क्रम the cache
 *              object_size     - Size of each cached object
 *              max_depth       - Maximum depth of the cache (in objects)
 *              वापस_cache    - Where the new cache object is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a cache object
 *
 ******************************************************************************/
acpi_status
acpi_os_create_cache(अक्षर *cache_name,
		     u16 object_size,
		     u16 max_depth, काष्ठा acpi_memory_list **वापस_cache)
अणु
	काष्ठा acpi_memory_list *cache;

	ACPI_FUNCTION_ENTRY();

	अगर (!cache_name || !वापस_cache || !object_size) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	/* Create the cache object */

	cache = acpi_os_allocate(माप(काष्ठा acpi_memory_list));
	अगर (!cache) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	/* Populate the cache object and वापस it */

	स_रखो(cache, 0, माप(काष्ठा acpi_memory_list));
	cache->list_name = cache_name;
	cache->object_size = object_size;
	cache->max_depth = max_depth;

	*वापस_cache = cache;
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_purge_cache
 *
 * PARAMETERS:  cache           - Handle to cache object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Free all objects within the requested cache.
 *
 ******************************************************************************/

acpi_status acpi_os_purge_cache(काष्ठा acpi_memory_list *cache)
अणु
	व्योम *next;
	acpi_status status;

	ACPI_FUNCTION_ENTRY();

	अगर (!cache) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	status = acpi_ut_acquire_mutex(ACPI_MTX_CACHES);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Walk the list of objects in this cache */

	जबतक (cache->list_head) अणु

		/* Delete and unlink one cached state object */

		next = ACPI_GET_DESCRIPTOR_PTR(cache->list_head);
		ACPI_FREE(cache->list_head);

		cache->list_head = next;
		cache->current_depth--;
	पूर्ण

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_CACHES);
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_delete_cache
 *
 * PARAMETERS:  cache           - Handle to cache object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Free all objects within the requested cache and delete the
 *              cache object.
 *
 ******************************************************************************/

acpi_status acpi_os_delete_cache(काष्ठा acpi_memory_list *cache)
अणु
	acpi_status status;

	ACPI_FUNCTION_ENTRY();

	/* Purge all objects in the cache */

	status = acpi_os_purge_cache(cache);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Now we can delete the cache object */

	acpi_os_मुक्त(cache);
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_release_object
 *
 * PARAMETERS:  cache       - Handle to cache object
 *              object      - The object to be released
 *
 * RETURN:      None
 *
 * DESCRIPTION: Release an object to the specअगरied cache. If cache is full,
 *              the object is deleted.
 *
 ******************************************************************************/

acpi_status acpi_os_release_object(काष्ठा acpi_memory_list *cache, व्योम *object)
अणु
	acpi_status status;

	ACPI_FUNCTION_ENTRY();

	अगर (!cache || !object) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	/* If cache is full, just मुक्त this object */

	अगर (cache->current_depth >= cache->max_depth) अणु
		ACPI_FREE(object);
		ACPI_MEM_TRACKING(cache->total_मुक्तd++);
	पूर्ण

	/* Otherwise put this object back पूर्णांकo the cache */

	अन्यथा अणु
		status = acpi_ut_acquire_mutex(ACPI_MTX_CACHES);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण

		/* Mark the object as cached */

		स_रखो(object, 0xCA, cache->object_size);
		ACPI_SET_DESCRIPTOR_TYPE(object, ACPI_DESC_TYPE_CACHED);

		/* Put the object at the head of the cache list */

		ACPI_SET_DESCRIPTOR_PTR(object, cache->list_head);
		cache->list_head = object;
		cache->current_depth++;

		(व्योम)acpi_ut_release_mutex(ACPI_MTX_CACHES);
	पूर्ण

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_acquire_object
 *
 * PARAMETERS:  cache           - Handle to cache object
 *
 * RETURN:      the acquired object. शून्य on error
 *
 * DESCRIPTION: Get an object from the specअगरied cache. If cache is empty,
 *              the object is allocated.
 *
 ******************************************************************************/

व्योम *acpi_os_acquire_object(काष्ठा acpi_memory_list *cache)
अणु
	acpi_status status;
	व्योम *object;

	ACPI_FUNCTION_TRACE(os_acquire_object);

	अगर (!cache) अणु
		वापस_PTR(शून्य);
	पूर्ण

	status = acpi_ut_acquire_mutex(ACPI_MTX_CACHES);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_PTR(शून्य);
	पूर्ण

	ACPI_MEM_TRACKING(cache->requests++);

	/* Check the cache first */

	अगर (cache->list_head) अणु

		/* There is an object available, use it */

		object = cache->list_head;
		cache->list_head = ACPI_GET_DESCRIPTOR_PTR(object);

		cache->current_depth--;

		ACPI_MEM_TRACKING(cache->hits++);
		ACPI_DEBUG_PRINT_RAW((ACPI_DB_EXEC,
				      "%s: Object %p from %s cache\n",
				      ACPI_GET_FUNCTION_NAME, object,
				      cache->list_name));

		status = acpi_ut_release_mutex(ACPI_MTX_CACHES);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_PTR(शून्य);
		पूर्ण

		/* Clear (zero) the previously used Object */

		स_रखो(object, 0, cache->object_size);
	पूर्ण अन्यथा अणु
		/* The cache is empty, create a new object */

		ACPI_MEM_TRACKING(cache->total_allocated++);

#अगर_घोषित ACPI_DBG_TRACK_ALLOCATIONS
		अगर ((cache->total_allocated - cache->total_मुक्तd) >
		    cache->max_occupied) अणु
			cache->max_occupied =
			    cache->total_allocated - cache->total_मुक्तd;
		पूर्ण
#पूर्ण_अगर

		/* Aव्योम deadlock with ACPI_ALLOCATE_ZEROED */

		status = acpi_ut_release_mutex(ACPI_MTX_CACHES);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_PTR(शून्य);
		पूर्ण

		object = ACPI_ALLOCATE_ZEROED(cache->object_size);
		अगर (!object) अणु
			वापस_PTR(शून्य);
		पूर्ण
	पूर्ण

	वापस_PTR(object);
पूर्ण
#पूर्ण_अगर				/* ACPI_USE_LOCAL_CACHE */
