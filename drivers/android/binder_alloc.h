<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2017 Google, Inc.
 */

#अगर_अघोषित _LINUX_BINDER_ALLOC_H
#घोषणा _LINUX_BINDER_ALLOC_H

#समावेश <linux/rbtree.h>
#समावेश <linux/list.h>
#समावेश <linux/mm.h>
#समावेश <linux/rपंचांगutex.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/list_lru.h>
#समावेश <uapi/linux/android/binder.h>

बाह्य काष्ठा list_lru binder_alloc_lru;
काष्ठा binder_transaction;

/**
 * काष्ठा binder_buffer - buffer used क्रम binder transactions
 * @entry:              entry alloc->buffers
 * @rb_node:            node क्रम allocated_buffers/मुक्त_buffers rb trees
 * @मुक्त:               %true अगर buffer is मुक्त
 * @clear_on_मुक्त:      %true अगर buffer must be zeroed after use
 * @allow_user_मुक्त:    %true अगर user is allowed to मुक्त buffer
 * @async_transaction:  %true अगर buffer is in use क्रम an async txn
 * @oneway_spam_suspect: %true अगर total async allocate size just exceed
 * spamming detect threshold
 * @debug_id:           unique ID क्रम debugging
 * @transaction:        poपूर्णांकer to associated काष्ठा binder_transaction
 * @target_node:        काष्ठा binder_node associated with this buffer
 * @data_size:          size of @transaction data
 * @offsets_size:       size of array of offsets
 * @extra_buffers_size: size of space क्रम other objects (like sg lists)
 * @user_data:          user poपूर्णांकer to base of buffer space
 * @pid:                pid to attribute the buffer to (caller)
 *
 * Bookkeeping काष्ठाure क्रम binder transaction buffers
 */
काष्ठा binder_buffer अणु
	काष्ठा list_head entry; /* मुक्त and allocated entries by address */
	काष्ठा rb_node rb_node; /* मुक्त entry by size or allocated entry */
				/* by address */
	अचिन्हित मुक्त:1;
	अचिन्हित clear_on_मुक्त:1;
	अचिन्हित allow_user_मुक्त:1;
	अचिन्हित async_transaction:1;
	अचिन्हित oneway_spam_suspect:1;
	अचिन्हित debug_id:27;

	काष्ठा binder_transaction *transaction;

	काष्ठा binder_node *target_node;
	माप_प्रकार data_size;
	माप_प्रकार offsets_size;
	माप_प्रकार extra_buffers_size;
	व्योम __user *user_data;
	पूर्णांक    pid;
पूर्ण;

/**
 * काष्ठा binder_lru_page - page object used क्रम binder shrinker
 * @page_ptr: poपूर्णांकer to physical page in mmap'd space
 * @lru:      entry in binder_alloc_lru
 * @alloc:    binder_alloc क्रम a proc
 */
काष्ठा binder_lru_page अणु
	काष्ठा list_head lru;
	काष्ठा page *page_ptr;
	काष्ठा binder_alloc *alloc;
पूर्ण;

/**
 * काष्ठा binder_alloc - per-binder proc state क्रम binder allocator
 * @vma:                vm_area_काष्ठा passed to mmap_handler
 *                      (invarient after mmap)
 * @tsk:                tid क्रम task that called init क्रम this proc
 *                      (invariant after init)
 * @vma_vm_mm:          copy of vma->vm_mm (invarient after mmap)
 * @buffer:             base of per-proc address space mapped via mmap
 * @buffers:            list of all buffers क्रम this proc
 * @मुक्त_buffers:       rb tree of buffers available क्रम allocation
 *                      sorted by size
 * @allocated_buffers:  rb tree of allocated buffers sorted by address
 * @मुक्त_async_space:   VA space available क्रम async buffers. This is
 *                      initialized at mmap समय to 1/2 the full VA space
 * @pages:              array of binder_lru_page
 * @buffer_size:        size of address space specअगरied via mmap
 * @pid:                pid क्रम associated binder_proc (invariant after init)
 * @pages_high:         high watermark of offset in @pages
 * @oneway_spam_detected: %true अगर oneway spam detection fired, clear that
 * flag once the async buffer has वापसed to a healthy state
 *
 * Bookkeeping काष्ठाure क्रम per-proc address space management क्रम binder
 * buffers. It is normally initialized during binder_init() and binder_mmap()
 * calls. The address space is used क्रम both user-visible buffers and क्रम
 * काष्ठा binder_buffer objects used to track the user buffers
 */
काष्ठा binder_alloc अणु
	काष्ठा mutex mutex;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा mm_काष्ठा *vma_vm_mm;
	व्योम __user *buffer;
	काष्ठा list_head buffers;
	काष्ठा rb_root मुक्त_buffers;
	काष्ठा rb_root allocated_buffers;
	माप_प्रकार मुक्त_async_space;
	काष्ठा binder_lru_page *pages;
	माप_प्रकार buffer_size;
	uपूर्णांक32_t buffer_मुक्त;
	पूर्णांक pid;
	माप_प्रकार pages_high;
	bool oneway_spam_detected;
पूर्ण;

#अगर_घोषित CONFIG_ANDROID_BINDER_IPC_SELFTEST
व्योम binder_selftest_alloc(काष्ठा binder_alloc *alloc);
#अन्यथा
अटल अंतरभूत व्योम binder_selftest_alloc(काष्ठा binder_alloc *alloc) अणुपूर्ण
#पूर्ण_अगर
क्रमागत lru_status binder_alloc_मुक्त_page(काष्ठा list_head *item,
				       काष्ठा list_lru_one *lru,
				       spinlock_t *lock, व्योम *cb_arg);
बाह्य काष्ठा binder_buffer *binder_alloc_new_buf(काष्ठा binder_alloc *alloc,
						  माप_प्रकार data_size,
						  माप_प्रकार offsets_size,
						  माप_प्रकार extra_buffers_size,
						  पूर्णांक is_async,
						  पूर्णांक pid);
बाह्य व्योम binder_alloc_init(काष्ठा binder_alloc *alloc);
बाह्य पूर्णांक binder_alloc_shrinker_init(व्योम);
बाह्य व्योम binder_alloc_vma_बंद(काष्ठा binder_alloc *alloc);
बाह्य काष्ठा binder_buffer *
binder_alloc_prepare_to_मुक्त(काष्ठा binder_alloc *alloc,
			     uपूर्णांकptr_t user_ptr);
बाह्य व्योम binder_alloc_मुक्त_buf(काष्ठा binder_alloc *alloc,
				  काष्ठा binder_buffer *buffer);
बाह्य पूर्णांक binder_alloc_mmap_handler(काष्ठा binder_alloc *alloc,
				     काष्ठा vm_area_काष्ठा *vma);
बाह्य व्योम binder_alloc_deferred_release(काष्ठा binder_alloc *alloc);
बाह्य पूर्णांक binder_alloc_get_allocated_count(काष्ठा binder_alloc *alloc);
बाह्य व्योम binder_alloc_prपूर्णांक_allocated(काष्ठा seq_file *m,
					 काष्ठा binder_alloc *alloc);
व्योम binder_alloc_prपूर्णांक_pages(काष्ठा seq_file *m,
			      काष्ठा binder_alloc *alloc);

/**
 * binder_alloc_get_मुक्त_async_space() - get मुक्त space available क्रम async
 * @alloc:	binder_alloc क्रम this proc
 *
 * Return:	the bytes reमुख्यing in the address-space क्रम async transactions
 */
अटल अंतरभूत माप_प्रकार
binder_alloc_get_मुक्त_async_space(काष्ठा binder_alloc *alloc)
अणु
	माप_प्रकार मुक्त_async_space;

	mutex_lock(&alloc->mutex);
	मुक्त_async_space = alloc->मुक्त_async_space;
	mutex_unlock(&alloc->mutex);
	वापस मुक्त_async_space;
पूर्ण

अचिन्हित दीर्घ
binder_alloc_copy_user_to_buffer(काष्ठा binder_alloc *alloc,
				 काष्ठा binder_buffer *buffer,
				 binder_माप_प्रकार buffer_offset,
				 स्थिर व्योम __user *from,
				 माप_प्रकार bytes);

पूर्णांक binder_alloc_copy_to_buffer(काष्ठा binder_alloc *alloc,
				काष्ठा binder_buffer *buffer,
				binder_माप_प्रकार buffer_offset,
				व्योम *src,
				माप_प्रकार bytes);

पूर्णांक binder_alloc_copy_from_buffer(काष्ठा binder_alloc *alloc,
				  व्योम *dest,
				  काष्ठा binder_buffer *buffer,
				  binder_माप_प्रकार buffer_offset,
				  माप_प्रकार bytes);

#पूर्ण_अगर /* _LINUX_BINDER_ALLOC_H */

