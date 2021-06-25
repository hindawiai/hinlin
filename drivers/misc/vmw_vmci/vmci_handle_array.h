<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * VMware VMCI Driver
 *
 * Copyright (C) 2012 VMware, Inc. All rights reserved.
 */

#अगर_अघोषित _VMCI_HANDLE_ARRAY_H_
#घोषणा _VMCI_HANDLE_ARRAY_H_

#समावेश <linux/vmw_vmci_defs.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/types.h>

काष्ठा vmci_handle_arr अणु
	u32 capacity;
	u32 max_capacity;
	u32 size;
	u32 pad;
	काष्ठा vmci_handle entries[];
पूर्ण;

#घोषणा VMCI_HANDLE_ARRAY_HEADER_SIZE				\
	दुरत्व(काष्ठा vmci_handle_arr, entries)
/* Select a शेष capacity that results in a 64 byte sized array */
#घोषणा VMCI_HANDLE_ARRAY_DEFAULT_CAPACITY			6
/* Make sure that the max array size can be expressed by a u32 */
#घोषणा VMCI_HANDLE_ARRAY_MAX_CAPACITY				\
	((U32_MAX - VMCI_HANDLE_ARRAY_HEADER_SIZE - 1) /	\
	माप(काष्ठा vmci_handle))

काष्ठा vmci_handle_arr *vmci_handle_arr_create(u32 capacity, u32 max_capacity);
व्योम vmci_handle_arr_destroy(काष्ठा vmci_handle_arr *array);
पूर्णांक vmci_handle_arr_append_entry(काष्ठा vmci_handle_arr **array_ptr,
				 काष्ठा vmci_handle handle);
काष्ठा vmci_handle vmci_handle_arr_हटाओ_entry(काष्ठा vmci_handle_arr *array,
						काष्ठा vmci_handle
						entry_handle);
काष्ठा vmci_handle vmci_handle_arr_हटाओ_tail(काष्ठा vmci_handle_arr *array);
काष्ठा vmci_handle
vmci_handle_arr_get_entry(स्थिर काष्ठा vmci_handle_arr *array, u32 index);
bool vmci_handle_arr_has_entry(स्थिर काष्ठा vmci_handle_arr *array,
			       काष्ठा vmci_handle entry_handle);
काष्ठा vmci_handle *vmci_handle_arr_get_handles(काष्ठा vmci_handle_arr *array);

अटल अंतरभूत u32 vmci_handle_arr_get_size(
	स्थिर काष्ठा vmci_handle_arr *array)
अणु
	वापस array->size;
पूर्ण


#पूर्ण_अगर /* _VMCI_HANDLE_ARRAY_H_ */
