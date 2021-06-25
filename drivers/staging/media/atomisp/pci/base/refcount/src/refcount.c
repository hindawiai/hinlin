<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#समावेश "hmm.h"

#समावेश "ia_css_refcount.h"
#समावेश "sh_css_defs.h"

#समावेश "platform_support.h"

#समावेश "assert_support.h"

#समावेश "ia_css_debug.h"

/* TODO: enable क्रम other memory aswell
	 now only क्रम ia_css_ptr */
काष्ठा ia_css_refcount_entry अणु
	u32 count;
	ia_css_ptr data;
	s32 id;
पूर्ण;

काष्ठा ia_css_refcount_list अणु
	u32 size;
	काष्ठा ia_css_refcount_entry *items;
पूर्ण;

अटल काष्ठा ia_css_refcount_list myrefcount;

अटल काष्ठा ia_css_refcount_entry *refcount_find_entry(ia_css_ptr ptr,
	bool firstमुक्त)
अणु
	u32 i;

	अगर (ptr == 0)
		वापस शून्य;
	अगर (!myrefcount.items) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_ERROR,
				    "%s(): Ref count not initialized!\n", __func__);
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < myrefcount.size; i++) अणु
		अगर ((&myrefcount.items[i])->data == 0) अणु
			अगर (firstमुक्त) अणु
				/* क्रम new entry */
				वापस &myrefcount.items[i];
			पूर्ण
		पूर्ण
		अगर ((&myrefcount.items[i])->data == ptr) अणु
			/* found entry */
			वापस &myrefcount.items[i];
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक ia_css_refcount_init(uपूर्णांक32_t size)
अणु
	पूर्णांक err = 0;

	अगर (size == 0) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "%s(): Size of 0 for Ref count init!\n", __func__);
		वापस -EINVAL;
	पूर्ण
	अगर (myrefcount.items) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
				    "%s(): Ref count is already initialized\n", __func__);
		वापस -EINVAL;
	पूर्ण
	myrefcount.items =
	    kvदो_स्मृति(माप(काष्ठा ia_css_refcount_entry) * size, GFP_KERNEL);
	अगर (!myrefcount.items)
		err = -ENOMEM;
	अगर (!err) अणु
		स_रखो(myrefcount.items, 0,
		       माप(काष्ठा ia_css_refcount_entry) * size);
		myrefcount.size = size;
	पूर्ण
	वापस err;
पूर्ण

व्योम ia_css_refcount_uninit(व्योम)
अणु
	काष्ठा ia_css_refcount_entry *entry;
	u32 i;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "%s() entry\n", __func__);
	क्रम (i = 0; i < myrefcount.size; i++) अणु
		/* driver verअगरier tool has issues with &arr[i]
		   and prefers arr + i; as these are actually equivalent
		   the line below uses + i
		*/
		entry = myrefcount.items + i;
		अगर (entry->data != mmgr_शून्य) अणु
			/*	ia_css_debug_dtrace(IA_CSS_DBG_TRACE,
				"ia_css_refcount_uninit: freeing (%x)\n",
				entry->data);*/
			hmm_मुक्त(entry->data);
			entry->data = mmgr_शून्य;
			entry->count = 0;
			entry->id = 0;
		पूर्ण
	पूर्ण
	kvमुक्त(myrefcount.items);
	myrefcount.items = शून्य;
	myrefcount.size = 0;
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "%s() leave\n", __func__);
पूर्ण

ia_css_ptr ia_css_refcount_increment(s32 id, ia_css_ptr ptr)
अणु
	काष्ठा ia_css_refcount_entry *entry;

	अगर (ptr == mmgr_शून्य)
		वापस ptr;

	entry = refcount_find_entry(ptr, false);

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "%s(%x) 0x%x\n", __func__, id, ptr);

	अगर (!entry) अणु
		entry = refcount_find_entry(ptr, true);
		निश्चित(entry);
		अगर (!entry)
			वापस mmgr_शून्य;
		entry->id = id;
	पूर्ण

	अगर (entry->id != id) अणु
		ia_css_debug_dtrace(IA_CSS_DEBUG_ERROR,
				    "%s(): Ref count IDS do not match!\n", __func__);
		वापस mmgr_शून्य;
	पूर्ण

	अगर (entry->data == ptr)
		entry->count += 1;
	अन्यथा अगर (entry->data == mmgr_शून्य) अणु
		entry->data = ptr;
		entry->count = 1;
	पूर्ण अन्यथा
		वापस mmgr_शून्य;

	वापस ptr;
पूर्ण

bool ia_css_refcount_decrement(s32 id, ia_css_ptr ptr)
अणु
	काष्ठा ia_css_refcount_entry *entry;

	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "%s(%x) 0x%x\n", __func__, id, ptr);

	अगर (ptr == mmgr_शून्य)
		वापस false;

	entry = refcount_find_entry(ptr, false);

	अगर (entry) अणु
		अगर (entry->id != id) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_ERROR,
					    "%s(): Ref count IDS do not match!\n", __func__);
			वापस false;
		पूर्ण
		अगर (entry->count > 0) अणु
			entry->count -= 1;
			अगर (entry->count == 0) अणु
				/* ia_css_debug_dtrace(IA_CSS_DBEUG_TRACE,
				   "ia_css_refcount_decrement: freeing\n");*/
				hmm_मुक्त(ptr);
				entry->data = mmgr_शून्य;
				entry->id = 0;
			पूर्ण
			वापस true;
		पूर्ण
	पूर्ण

	/* SHOULD NOT HAPPEN: ptr not managed by refcount, or not
	   valid anymore */
	अगर (entry)
		IA_CSS_ERROR("id %x, ptr 0x%x entry %p entry->id %x entry->count %d\n",
			     id, ptr, entry, entry->id, entry->count);
	अन्यथा
		IA_CSS_ERROR("entry NULL\n");
	निश्चित(false);

	वापस false;
पूर्ण

bool ia_css_refcount_is_single(ia_css_ptr ptr)
अणु
	काष्ठा ia_css_refcount_entry *entry;

	अगर (ptr == mmgr_शून्य)
		वापस false;

	entry = refcount_find_entry(ptr, false);

	अगर (entry)
		वापस (entry->count == 1);

	वापस true;
पूर्ण

व्योम ia_css_refcount_clear(s32 id, clear_func clear_func_ptr)
अणु
	काष्ठा ia_css_refcount_entry *entry;
	u32 i;
	u32 count = 0;

	निश्चित(clear_func_ptr);
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE, "%s(%x)\n",
			    __func__, id);

	क्रम (i = 0; i < myrefcount.size; i++) अणु
		/* driver verअगरier tool has issues with &arr[i]
		   and prefers arr + i; as these are actually equivalent
		   the line below uses + i
		*/
		entry = myrefcount.items + i;
		अगर ((entry->data != mmgr_शून्य) && (entry->id == id)) अणु
			ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
					    "%s: %x: 0x%x\n", __func__,
					    id, entry->data);
			अगर (clear_func_ptr) अणु
				/* clear using provided function */
				clear_func_ptr(entry->data);
			पूर्ण अन्यथा अणु
				ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
						    "%s: using hmm_free: no clear_func\n", __func__);
				hmm_मुक्त(entry->data);
			पूर्ण

			अगर (entry->count != 0) अणु
				IA_CSS_WARNING("Ref count for entry %x is not zero!", entry->id);
			पूर्ण

			निश्चित(entry->count == 0);

			entry->data = mmgr_शून्य;
			entry->count = 0;
			entry->id = 0;
			count++;
		पूर्ण
	पूर्ण
	ia_css_debug_dtrace(IA_CSS_DEBUG_TRACE,
			    "%s(%x): cleared %d\n", __func__, id,
			    count);
पूर्ण

bool ia_css_refcount_is_valid(ia_css_ptr ptr)
अणु
	काष्ठा ia_css_refcount_entry *entry;

	अगर (ptr == mmgr_शून्य)
		वापस false;

	entry = refcount_find_entry(ptr, false);

	वापस entry;
पूर्ण
