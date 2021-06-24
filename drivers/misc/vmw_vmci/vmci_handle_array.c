<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VMware VMCI Driver
 *
 * Copyright (C) 2012 VMware, Inc. All rights reserved.
 */

#समावेश <linux/slab.h>
#समावेश "vmci_handle_array.h"

अटल माप_प्रकार handle_arr_calc_size(u32 capacity)
अणु
	वापस VMCI_HANDLE_ARRAY_HEADER_SIZE +
	    capacity * माप(काष्ठा vmci_handle);
पूर्ण

काष्ठा vmci_handle_arr *vmci_handle_arr_create(u32 capacity, u32 max_capacity)
अणु
	काष्ठा vmci_handle_arr *array;

	अगर (max_capacity == 0 || capacity > max_capacity)
		वापस शून्य;

	अगर (capacity == 0)
		capacity = min((u32)VMCI_HANDLE_ARRAY_DEFAULT_CAPACITY,
			       max_capacity);

	array = kदो_स्मृति(handle_arr_calc_size(capacity), GFP_ATOMIC);
	अगर (!array)
		वापस शून्य;

	array->capacity = capacity;
	array->max_capacity = max_capacity;
	array->size = 0;

	वापस array;
पूर्ण

व्योम vmci_handle_arr_destroy(काष्ठा vmci_handle_arr *array)
अणु
	kमुक्त(array);
पूर्ण

पूर्णांक vmci_handle_arr_append_entry(काष्ठा vmci_handle_arr **array_ptr,
				 काष्ठा vmci_handle handle)
अणु
	काष्ठा vmci_handle_arr *array = *array_ptr;

	अगर (unlikely(array->size >= array->capacity)) अणु
		/* पुनः_स्मृतिate. */
		काष्ठा vmci_handle_arr *new_array;
		u32 capacity_bump = min(array->max_capacity - array->capacity,
					array->capacity);
		माप_प्रकार new_size = handle_arr_calc_size(array->capacity +
						       capacity_bump);

		अगर (array->size >= array->max_capacity)
			वापस VMCI_ERROR_NO_MEM;

		new_array = kपुनः_स्मृति(array, new_size, GFP_ATOMIC);
		अगर (!new_array)
			वापस VMCI_ERROR_NO_MEM;

		new_array->capacity += capacity_bump;
		*array_ptr = array = new_array;
	पूर्ण

	array->entries[array->size] = handle;
	array->size++;

	वापस VMCI_SUCCESS;
पूर्ण

/*
 * Handle that was हटाओd, VMCI_INVALID_HANDLE अगर entry not found.
 */
काष्ठा vmci_handle vmci_handle_arr_हटाओ_entry(काष्ठा vmci_handle_arr *array,
						काष्ठा vmci_handle entry_handle)
अणु
	काष्ठा vmci_handle handle = VMCI_INVALID_HANDLE;
	u32 i;

	क्रम (i = 0; i < array->size; i++) अणु
		अगर (vmci_handle_is_equal(array->entries[i], entry_handle)) अणु
			handle = array->entries[i];
			array->size--;
			array->entries[i] = array->entries[array->size];
			array->entries[array->size] = VMCI_INVALID_HANDLE;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस handle;
पूर्ण

/*
 * Handle that was हटाओd, VMCI_INVALID_HANDLE अगर array was empty.
 */
काष्ठा vmci_handle vmci_handle_arr_हटाओ_tail(काष्ठा vmci_handle_arr *array)
अणु
	काष्ठा vmci_handle handle = VMCI_INVALID_HANDLE;

	अगर (array->size) अणु
		array->size--;
		handle = array->entries[array->size];
		array->entries[array->size] = VMCI_INVALID_HANDLE;
	पूर्ण

	वापस handle;
पूर्ण

/*
 * Handle at given index, VMCI_INVALID_HANDLE अगर invalid index.
 */
काष्ठा vmci_handle
vmci_handle_arr_get_entry(स्थिर काष्ठा vmci_handle_arr *array, u32 index)
अणु
	अगर (unlikely(index >= array->size))
		वापस VMCI_INVALID_HANDLE;

	वापस array->entries[index];
पूर्ण

bool vmci_handle_arr_has_entry(स्थिर काष्ठा vmci_handle_arr *array,
			       काष्ठा vmci_handle entry_handle)
अणु
	u32 i;

	क्रम (i = 0; i < array->size; i++)
		अगर (vmci_handle_is_equal(array->entries[i], entry_handle))
			वापस true;

	वापस false;
पूर्ण

/*
 * शून्य अगर the array is empty. Otherwise, a poपूर्णांकer to the array
 * of VMCI handles in the handle array.
 */
काष्ठा vmci_handle *vmci_handle_arr_get_handles(काष्ठा vmci_handle_arr *array)
अणु
	अगर (array->size)
		वापस array->entries;

	वापस शून्य;
पूर्ण
