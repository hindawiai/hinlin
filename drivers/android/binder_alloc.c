<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* binder_alloc.c
 *
 * Android IPC Subप्रणाली
 *
 * Copyright (C) 2007-2017 Google, Inc.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/list.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/rपंचांगutex.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/list_lru.h>
#समावेश <linux/ratelimit.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/sizes.h>
#समावेश "binder_alloc.h"
#समावेश "binder_trace.h"

काष्ठा list_lru binder_alloc_lru;

अटल DEFINE_MUTEX(binder_alloc_mmap_lock);

क्रमागत अणु
	BINDER_DEBUG_USER_ERROR             = 1U << 0,
	BINDER_DEBUG_OPEN_CLOSE             = 1U << 1,
	BINDER_DEBUG_BUFFER_ALLOC           = 1U << 2,
	BINDER_DEBUG_BUFFER_ALLOC_ASYNC     = 1U << 3,
पूर्ण;
अटल uपूर्णांक32_t binder_alloc_debug_mask = BINDER_DEBUG_USER_ERROR;

module_param_named(debug_mask, binder_alloc_debug_mask,
		   uपूर्णांक, 0644);

#घोषणा binder_alloc_debug(mask, x...) \
	करो अणु \
		अगर (binder_alloc_debug_mask & mask) \
			pr_info_ratelimited(x); \
	पूर्ण जबतक (0)

अटल काष्ठा binder_buffer *binder_buffer_next(काष्ठा binder_buffer *buffer)
अणु
	वापस list_entry(buffer->entry.next, काष्ठा binder_buffer, entry);
पूर्ण

अटल काष्ठा binder_buffer *binder_buffer_prev(काष्ठा binder_buffer *buffer)
अणु
	वापस list_entry(buffer->entry.prev, काष्ठा binder_buffer, entry);
पूर्ण

अटल माप_प्रकार binder_alloc_buffer_size(काष्ठा binder_alloc *alloc,
				       काष्ठा binder_buffer *buffer)
अणु
	अगर (list_is_last(&buffer->entry, &alloc->buffers))
		वापस alloc->buffer + alloc->buffer_size - buffer->user_data;
	वापस binder_buffer_next(buffer)->user_data - buffer->user_data;
पूर्ण

अटल व्योम binder_insert_मुक्त_buffer(काष्ठा binder_alloc *alloc,
				      काष्ठा binder_buffer *new_buffer)
अणु
	काष्ठा rb_node **p = &alloc->मुक्त_buffers.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा binder_buffer *buffer;
	माप_प्रकार buffer_size;
	माप_प्रकार new_buffer_size;

	BUG_ON(!new_buffer->मुक्त);

	new_buffer_size = binder_alloc_buffer_size(alloc, new_buffer);

	binder_alloc_debug(BINDER_DEBUG_BUFFER_ALLOC,
		     "%d: add free buffer, size %zd, at %pK\n",
		      alloc->pid, new_buffer_size, new_buffer);

	जबतक (*p) अणु
		parent = *p;
		buffer = rb_entry(parent, काष्ठा binder_buffer, rb_node);
		BUG_ON(!buffer->मुक्त);

		buffer_size = binder_alloc_buffer_size(alloc, buffer);

		अगर (new_buffer_size < buffer_size)
			p = &parent->rb_left;
		अन्यथा
			p = &parent->rb_right;
	पूर्ण
	rb_link_node(&new_buffer->rb_node, parent, p);
	rb_insert_color(&new_buffer->rb_node, &alloc->मुक्त_buffers);
पूर्ण

अटल व्योम binder_insert_allocated_buffer_locked(
		काष्ठा binder_alloc *alloc, काष्ठा binder_buffer *new_buffer)
अणु
	काष्ठा rb_node **p = &alloc->allocated_buffers.rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा binder_buffer *buffer;

	BUG_ON(new_buffer->मुक्त);

	जबतक (*p) अणु
		parent = *p;
		buffer = rb_entry(parent, काष्ठा binder_buffer, rb_node);
		BUG_ON(buffer->मुक्त);

		अगर (new_buffer->user_data < buffer->user_data)
			p = &parent->rb_left;
		अन्यथा अगर (new_buffer->user_data > buffer->user_data)
			p = &parent->rb_right;
		अन्यथा
			BUG();
	पूर्ण
	rb_link_node(&new_buffer->rb_node, parent, p);
	rb_insert_color(&new_buffer->rb_node, &alloc->allocated_buffers);
पूर्ण

अटल काष्ठा binder_buffer *binder_alloc_prepare_to_मुक्त_locked(
		काष्ठा binder_alloc *alloc,
		uपूर्णांकptr_t user_ptr)
अणु
	काष्ठा rb_node *n = alloc->allocated_buffers.rb_node;
	काष्ठा binder_buffer *buffer;
	व्योम __user *uptr;

	uptr = (व्योम __user *)user_ptr;

	जबतक (n) अणु
		buffer = rb_entry(n, काष्ठा binder_buffer, rb_node);
		BUG_ON(buffer->मुक्त);

		अगर (uptr < buffer->user_data)
			n = n->rb_left;
		अन्यथा अगर (uptr > buffer->user_data)
			n = n->rb_right;
		अन्यथा अणु
			/*
			 * Guard against user thपढ़ोs attempting to
			 * मुक्त the buffer when in use by kernel or
			 * after it's alपढ़ोy been मुक्तd.
			 */
			अगर (!buffer->allow_user_मुक्त)
				वापस ERR_PTR(-EPERM);
			buffer->allow_user_मुक्त = 0;
			वापस buffer;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * binder_alloc_prepare_to_मुक्त() - get buffer given user ptr
 * @alloc:	binder_alloc क्रम this proc
 * @user_ptr:	User poपूर्णांकer to buffer data
 *
 * Validate userspace poपूर्णांकer to buffer data and वापस buffer corresponding to
 * that user poपूर्णांकer. Search the rb tree क्रम buffer that matches user data
 * poपूर्णांकer.
 *
 * Return:	Poपूर्णांकer to buffer or शून्य
 */
काष्ठा binder_buffer *binder_alloc_prepare_to_मुक्त(काष्ठा binder_alloc *alloc,
						   uपूर्णांकptr_t user_ptr)
अणु
	काष्ठा binder_buffer *buffer;

	mutex_lock(&alloc->mutex);
	buffer = binder_alloc_prepare_to_मुक्त_locked(alloc, user_ptr);
	mutex_unlock(&alloc->mutex);
	वापस buffer;
पूर्ण

अटल पूर्णांक binder_update_page_range(काष्ठा binder_alloc *alloc, पूर्णांक allocate,
				    व्योम __user *start, व्योम __user *end)
अणु
	व्योम __user *page_addr;
	अचिन्हित दीर्घ user_page_addr;
	काष्ठा binder_lru_page *page;
	काष्ठा vm_area_काष्ठा *vma = शून्य;
	काष्ठा mm_काष्ठा *mm = शून्य;
	bool need_mm = false;

	binder_alloc_debug(BINDER_DEBUG_BUFFER_ALLOC,
		     "%d: %s pages %pK-%pK\n", alloc->pid,
		     allocate ? "allocate" : "free", start, end);

	अगर (end <= start)
		वापस 0;

	trace_binder_update_page_range(alloc, allocate, start, end);

	अगर (allocate == 0)
		जाओ मुक्त_range;

	क्रम (page_addr = start; page_addr < end; page_addr += PAGE_SIZE) अणु
		page = &alloc->pages[(page_addr - alloc->buffer) / PAGE_SIZE];
		अगर (!page->page_ptr) अणु
			need_mm = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (need_mm && mmget_not_zero(alloc->vma_vm_mm))
		mm = alloc->vma_vm_mm;

	अगर (mm) अणु
		mmap_पढ़ो_lock(mm);
		vma = alloc->vma;
	पूर्ण

	अगर (!vma && need_mm) अणु
		binder_alloc_debug(BINDER_DEBUG_USER_ERROR,
				   "%d: binder_alloc_buf failed to map pages in userspace, no vma\n",
				   alloc->pid);
		जाओ err_no_vma;
	पूर्ण

	क्रम (page_addr = start; page_addr < end; page_addr += PAGE_SIZE) अणु
		पूर्णांक ret;
		bool on_lru;
		माप_प्रकार index;

		index = (page_addr - alloc->buffer) / PAGE_SIZE;
		page = &alloc->pages[index];

		अगर (page->page_ptr) अणु
			trace_binder_alloc_lru_start(alloc, index);

			on_lru = list_lru_del(&binder_alloc_lru, &page->lru);
			WARN_ON(!on_lru);

			trace_binder_alloc_lru_end(alloc, index);
			जारी;
		पूर्ण

		अगर (WARN_ON(!vma))
			जाओ err_page_ptr_cleared;

		trace_binder_alloc_page_start(alloc, index);
		page->page_ptr = alloc_page(GFP_KERNEL |
					    __GFP_HIGHMEM |
					    __GFP_ZERO);
		अगर (!page->page_ptr) अणु
			pr_err("%d: binder_alloc_buf failed for page at %pK\n",
				alloc->pid, page_addr);
			जाओ err_alloc_page_failed;
		पूर्ण
		page->alloc = alloc;
		INIT_LIST_HEAD(&page->lru);

		user_page_addr = (uपूर्णांकptr_t)page_addr;
		ret = vm_insert_page(vma, user_page_addr, page[0].page_ptr);
		अगर (ret) अणु
			pr_err("%d: binder_alloc_buf failed to map page at %lx in userspace\n",
			       alloc->pid, user_page_addr);
			जाओ err_vm_insert_page_failed;
		पूर्ण

		अगर (index + 1 > alloc->pages_high)
			alloc->pages_high = index + 1;

		trace_binder_alloc_page_end(alloc, index);
	पूर्ण
	अगर (mm) अणु
		mmap_पढ़ो_unlock(mm);
		mmput(mm);
	पूर्ण
	वापस 0;

मुक्त_range:
	क्रम (page_addr = end - PAGE_SIZE; 1; page_addr -= PAGE_SIZE) अणु
		bool ret;
		माप_प्रकार index;

		index = (page_addr - alloc->buffer) / PAGE_SIZE;
		page = &alloc->pages[index];

		trace_binder_मुक्त_lru_start(alloc, index);

		ret = list_lru_add(&binder_alloc_lru, &page->lru);
		WARN_ON(!ret);

		trace_binder_मुक्त_lru_end(alloc, index);
		अगर (page_addr == start)
			अवरोध;
		जारी;

err_vm_insert_page_failed:
		__मुक्त_page(page->page_ptr);
		page->page_ptr = शून्य;
err_alloc_page_failed:
err_page_ptr_cleared:
		अगर (page_addr == start)
			अवरोध;
	पूर्ण
err_no_vma:
	अगर (mm) अणु
		mmap_पढ़ो_unlock(mm);
		mmput(mm);
	पूर्ण
	वापस vma ? -ENOMEM : -ESRCH;
पूर्ण


अटल अंतरभूत व्योम binder_alloc_set_vma(काष्ठा binder_alloc *alloc,
		काष्ठा vm_area_काष्ठा *vma)
अणु
	अगर (vma)
		alloc->vma_vm_mm = vma->vm_mm;
	/*
	 * If we see alloc->vma is not शून्य, buffer data काष्ठाures set up
	 * completely. Look at smp_rmb side binder_alloc_get_vma.
	 * We also want to guarantee new alloc->vma_vm_mm is always visible
	 * अगर alloc->vma is set.
	 */
	smp_wmb();
	alloc->vma = vma;
पूर्ण

अटल अंतरभूत काष्ठा vm_area_काष्ठा *binder_alloc_get_vma(
		काष्ठा binder_alloc *alloc)
अणु
	काष्ठा vm_area_काष्ठा *vma = शून्य;

	अगर (alloc->vma) अणु
		/* Look at description in binder_alloc_set_vma */
		smp_rmb();
		vma = alloc->vma;
	पूर्ण
	वापस vma;
पूर्ण

अटल bool debug_low_async_space_locked(काष्ठा binder_alloc *alloc, पूर्णांक pid)
अणु
	/*
	 * Find the amount and size of buffers allocated by the current caller;
	 * The idea is that once we cross the threshold, whoever is responsible
	 * क्रम the low async space is likely to try to send another async txn,
	 * and at some poपूर्णांक we'll catch them in the act. This is more efficient
	 * than keeping a map per pid.
	 */
	काष्ठा rb_node *n;
	काष्ठा binder_buffer *buffer;
	माप_प्रकार total_alloc_size = 0;
	माप_प्रकार num_buffers = 0;

	क्रम (n = rb_first(&alloc->allocated_buffers); n != शून्य;
		 n = rb_next(n)) अणु
		buffer = rb_entry(n, काष्ठा binder_buffer, rb_node);
		अगर (buffer->pid != pid)
			जारी;
		अगर (!buffer->async_transaction)
			जारी;
		total_alloc_size += binder_alloc_buffer_size(alloc, buffer)
			+ माप(काष्ठा binder_buffer);
		num_buffers++;
	पूर्ण

	/*
	 * Warn अगर this pid has more than 50 transactions, or more than 50% of
	 * async space (which is 25% of total buffer size). Oneway spam is only
	 * detected when the threshold is exceeded.
	 */
	अगर (num_buffers > 50 || total_alloc_size > alloc->buffer_size / 4) अणु
		binder_alloc_debug(BINDER_DEBUG_USER_ERROR,
			     "%d: pid %d spamming oneway? %zd buffers allocated for a total size of %zd\n",
			      alloc->pid, pid, num_buffers, total_alloc_size);
		अगर (!alloc->oneway_spam_detected) अणु
			alloc->oneway_spam_detected = true;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल काष्ठा binder_buffer *binder_alloc_new_buf_locked(
				काष्ठा binder_alloc *alloc,
				माप_प्रकार data_size,
				माप_प्रकार offsets_size,
				माप_प्रकार extra_buffers_size,
				पूर्णांक is_async,
				पूर्णांक pid)
अणु
	काष्ठा rb_node *n = alloc->मुक्त_buffers.rb_node;
	काष्ठा binder_buffer *buffer;
	माप_प्रकार buffer_size;
	काष्ठा rb_node *best_fit = शून्य;
	व्योम __user *has_page_addr;
	व्योम __user *end_page_addr;
	माप_प्रकार size, data_offsets_size;
	पूर्णांक ret;

	अगर (!binder_alloc_get_vma(alloc)) अणु
		binder_alloc_debug(BINDER_DEBUG_USER_ERROR,
				   "%d: binder_alloc_buf, no vma\n",
				   alloc->pid);
		वापस ERR_PTR(-ESRCH);
	पूर्ण

	data_offsets_size = ALIGN(data_size, माप(व्योम *)) +
		ALIGN(offsets_size, माप(व्योम *));

	अगर (data_offsets_size < data_size || data_offsets_size < offsets_size) अणु
		binder_alloc_debug(BINDER_DEBUG_BUFFER_ALLOC,
				"%d: got transaction with invalid size %zd-%zd\n",
				alloc->pid, data_size, offsets_size);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	size = data_offsets_size + ALIGN(extra_buffers_size, माप(व्योम *));
	अगर (size < data_offsets_size || size < extra_buffers_size) अणु
		binder_alloc_debug(BINDER_DEBUG_BUFFER_ALLOC,
				"%d: got transaction with invalid extra_buffers_size %zd\n",
				alloc->pid, extra_buffers_size);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	अगर (is_async &&
	    alloc->मुक्त_async_space < size + माप(काष्ठा binder_buffer)) अणु
		binder_alloc_debug(BINDER_DEBUG_BUFFER_ALLOC,
			     "%d: binder_alloc_buf size %zd failed, no async space left\n",
			      alloc->pid, size);
		वापस ERR_PTR(-ENOSPC);
	पूर्ण

	/* Pad 0-size buffers so they get asचिन्हित unique addresses */
	size = max(size, माप(व्योम *));

	जबतक (n) अणु
		buffer = rb_entry(n, काष्ठा binder_buffer, rb_node);
		BUG_ON(!buffer->मुक्त);
		buffer_size = binder_alloc_buffer_size(alloc, buffer);

		अगर (size < buffer_size) अणु
			best_fit = n;
			n = n->rb_left;
		पूर्ण अन्यथा अगर (size > buffer_size)
			n = n->rb_right;
		अन्यथा अणु
			best_fit = n;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (best_fit == शून्य) अणु
		माप_प्रकार allocated_buffers = 0;
		माप_प्रकार largest_alloc_size = 0;
		माप_प्रकार total_alloc_size = 0;
		माप_प्रकार मुक्त_buffers = 0;
		माप_प्रकार largest_मुक्त_size = 0;
		माप_प्रकार total_मुक्त_size = 0;

		क्रम (n = rb_first(&alloc->allocated_buffers); n != शून्य;
		     n = rb_next(n)) अणु
			buffer = rb_entry(n, काष्ठा binder_buffer, rb_node);
			buffer_size = binder_alloc_buffer_size(alloc, buffer);
			allocated_buffers++;
			total_alloc_size += buffer_size;
			अगर (buffer_size > largest_alloc_size)
				largest_alloc_size = buffer_size;
		पूर्ण
		क्रम (n = rb_first(&alloc->मुक्त_buffers); n != शून्य;
		     n = rb_next(n)) अणु
			buffer = rb_entry(n, काष्ठा binder_buffer, rb_node);
			buffer_size = binder_alloc_buffer_size(alloc, buffer);
			मुक्त_buffers++;
			total_मुक्त_size += buffer_size;
			अगर (buffer_size > largest_मुक्त_size)
				largest_मुक्त_size = buffer_size;
		पूर्ण
		binder_alloc_debug(BINDER_DEBUG_USER_ERROR,
				   "%d: binder_alloc_buf size %zd failed, no address space\n",
				   alloc->pid, size);
		binder_alloc_debug(BINDER_DEBUG_USER_ERROR,
				   "allocated: %zd (num: %zd largest: %zd), free: %zd (num: %zd largest: %zd)\n",
				   total_alloc_size, allocated_buffers,
				   largest_alloc_size, total_मुक्त_size,
				   मुक्त_buffers, largest_मुक्त_size);
		वापस ERR_PTR(-ENOSPC);
	पूर्ण
	अगर (n == शून्य) अणु
		buffer = rb_entry(best_fit, काष्ठा binder_buffer, rb_node);
		buffer_size = binder_alloc_buffer_size(alloc, buffer);
	पूर्ण

	binder_alloc_debug(BINDER_DEBUG_BUFFER_ALLOC,
		     "%d: binder_alloc_buf size %zd got buffer %pK size %zd\n",
		      alloc->pid, size, buffer, buffer_size);

	has_page_addr = (व्योम __user *)
		(((uपूर्णांकptr_t)buffer->user_data + buffer_size) & PAGE_MASK);
	WARN_ON(n && buffer_size != size);
	end_page_addr =
		(व्योम __user *)PAGE_ALIGN((uपूर्णांकptr_t)buffer->user_data + size);
	अगर (end_page_addr > has_page_addr)
		end_page_addr = has_page_addr;
	ret = binder_update_page_range(alloc, 1, (व्योम __user *)
		PAGE_ALIGN((uपूर्णांकptr_t)buffer->user_data), end_page_addr);
	अगर (ret)
		वापस ERR_PTR(ret);

	अगर (buffer_size != size) अणु
		काष्ठा binder_buffer *new_buffer;

		new_buffer = kzalloc(माप(*buffer), GFP_KERNEL);
		अगर (!new_buffer) अणु
			pr_err("%s: %d failed to alloc new buffer struct\n",
			       __func__, alloc->pid);
			जाओ err_alloc_buf_काष्ठा_failed;
		पूर्ण
		new_buffer->user_data = (u8 __user *)buffer->user_data + size;
		list_add(&new_buffer->entry, &buffer->entry);
		new_buffer->मुक्त = 1;
		binder_insert_मुक्त_buffer(alloc, new_buffer);
	पूर्ण

	rb_erase(best_fit, &alloc->मुक्त_buffers);
	buffer->मुक्त = 0;
	buffer->allow_user_मुक्त = 0;
	binder_insert_allocated_buffer_locked(alloc, buffer);
	binder_alloc_debug(BINDER_DEBUG_BUFFER_ALLOC,
		     "%d: binder_alloc_buf size %zd got %pK\n",
		      alloc->pid, size, buffer);
	buffer->data_size = data_size;
	buffer->offsets_size = offsets_size;
	buffer->async_transaction = is_async;
	buffer->extra_buffers_size = extra_buffers_size;
	buffer->pid = pid;
	buffer->oneway_spam_suspect = false;
	अगर (is_async) अणु
		alloc->मुक्त_async_space -= size + माप(काष्ठा binder_buffer);
		binder_alloc_debug(BINDER_DEBUG_BUFFER_ALLOC_ASYNC,
			     "%d: binder_alloc_buf size %zd async free %zd\n",
			      alloc->pid, size, alloc->मुक्त_async_space);
		अगर (alloc->मुक्त_async_space < alloc->buffer_size / 10) अणु
			/*
			 * Start detecting spammers once we have less than 20%
			 * of async space left (which is less than 10% of total
			 * buffer size).
			 */
			buffer->oneway_spam_suspect = debug_low_async_space_locked(alloc, pid);
		पूर्ण अन्यथा अणु
			alloc->oneway_spam_detected = false;
		पूर्ण
	पूर्ण
	वापस buffer;

err_alloc_buf_काष्ठा_failed:
	binder_update_page_range(alloc, 0, (व्योम __user *)
				 PAGE_ALIGN((uपूर्णांकptr_t)buffer->user_data),
				 end_page_addr);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

/**
 * binder_alloc_new_buf() - Allocate a new binder buffer
 * @alloc:              binder_alloc क्रम this proc
 * @data_size:          size of user data buffer
 * @offsets_size:       user specअगरied buffer offset
 * @extra_buffers_size: size of extra space क्रम meta-data (eg, security context)
 * @is_async:           buffer क्रम async transaction
 * @pid:				pid to attribute allocation to (used क्रम debugging)
 *
 * Allocate a new buffer given the requested sizes. Returns
 * the kernel version of the buffer poपूर्णांकer. The size allocated
 * is the sum of the three given sizes (each rounded up to
 * poपूर्णांकer-sized boundary)
 *
 * Return:	The allocated buffer or %शून्य अगर error
 */
काष्ठा binder_buffer *binder_alloc_new_buf(काष्ठा binder_alloc *alloc,
					   माप_प्रकार data_size,
					   माप_प्रकार offsets_size,
					   माप_प्रकार extra_buffers_size,
					   पूर्णांक is_async,
					   पूर्णांक pid)
अणु
	काष्ठा binder_buffer *buffer;

	mutex_lock(&alloc->mutex);
	buffer = binder_alloc_new_buf_locked(alloc, data_size, offsets_size,
					     extra_buffers_size, is_async, pid);
	mutex_unlock(&alloc->mutex);
	वापस buffer;
पूर्ण

अटल व्योम __user *buffer_start_page(काष्ठा binder_buffer *buffer)
अणु
	वापस (व्योम __user *)((uपूर्णांकptr_t)buffer->user_data & PAGE_MASK);
पूर्ण

अटल व्योम __user *prev_buffer_end_page(काष्ठा binder_buffer *buffer)
अणु
	वापस (व्योम __user *)
		(((uपूर्णांकptr_t)(buffer->user_data) - 1) & PAGE_MASK);
पूर्ण

अटल व्योम binder_delete_मुक्त_buffer(काष्ठा binder_alloc *alloc,
				      काष्ठा binder_buffer *buffer)
अणु
	काष्ठा binder_buffer *prev, *next = शून्य;
	bool to_मुक्त = true;

	BUG_ON(alloc->buffers.next == &buffer->entry);
	prev = binder_buffer_prev(buffer);
	BUG_ON(!prev->मुक्त);
	अगर (prev_buffer_end_page(prev) == buffer_start_page(buffer)) अणु
		to_मुक्त = false;
		binder_alloc_debug(BINDER_DEBUG_BUFFER_ALLOC,
				   "%d: merge free, buffer %pK share page with %pK\n",
				   alloc->pid, buffer->user_data,
				   prev->user_data);
	पूर्ण

	अगर (!list_is_last(&buffer->entry, &alloc->buffers)) अणु
		next = binder_buffer_next(buffer);
		अगर (buffer_start_page(next) == buffer_start_page(buffer)) अणु
			to_मुक्त = false;
			binder_alloc_debug(BINDER_DEBUG_BUFFER_ALLOC,
					   "%d: merge free, buffer %pK share page with %pK\n",
					   alloc->pid,
					   buffer->user_data,
					   next->user_data);
		पूर्ण
	पूर्ण

	अगर (PAGE_ALIGNED(buffer->user_data)) अणु
		binder_alloc_debug(BINDER_DEBUG_BUFFER_ALLOC,
				   "%d: merge free, buffer start %pK is page aligned\n",
				   alloc->pid, buffer->user_data);
		to_मुक्त = false;
	पूर्ण

	अगर (to_मुक्त) अणु
		binder_alloc_debug(BINDER_DEBUG_BUFFER_ALLOC,
				   "%d: merge free, buffer %pK do not share page with %pK or %pK\n",
				   alloc->pid, buffer->user_data,
				   prev->user_data,
				   next ? next->user_data : शून्य);
		binder_update_page_range(alloc, 0, buffer_start_page(buffer),
					 buffer_start_page(buffer) + PAGE_SIZE);
	पूर्ण
	list_del(&buffer->entry);
	kमुक्त(buffer);
पूर्ण

अटल व्योम binder_मुक्त_buf_locked(काष्ठा binder_alloc *alloc,
				   काष्ठा binder_buffer *buffer)
अणु
	माप_प्रकार size, buffer_size;

	buffer_size = binder_alloc_buffer_size(alloc, buffer);

	size = ALIGN(buffer->data_size, माप(व्योम *)) +
		ALIGN(buffer->offsets_size, माप(व्योम *)) +
		ALIGN(buffer->extra_buffers_size, माप(व्योम *));

	binder_alloc_debug(BINDER_DEBUG_BUFFER_ALLOC,
		     "%d: binder_free_buf %pK size %zd buffer_size %zd\n",
		      alloc->pid, buffer, size, buffer_size);

	BUG_ON(buffer->मुक्त);
	BUG_ON(size > buffer_size);
	BUG_ON(buffer->transaction != शून्य);
	BUG_ON(buffer->user_data < alloc->buffer);
	BUG_ON(buffer->user_data > alloc->buffer + alloc->buffer_size);

	अगर (buffer->async_transaction) अणु
		alloc->मुक्त_async_space += size + माप(काष्ठा binder_buffer);

		binder_alloc_debug(BINDER_DEBUG_BUFFER_ALLOC_ASYNC,
			     "%d: binder_free_buf size %zd async free %zd\n",
			      alloc->pid, size, alloc->मुक्त_async_space);
	पूर्ण

	binder_update_page_range(alloc, 0,
		(व्योम __user *)PAGE_ALIGN((uपूर्णांकptr_t)buffer->user_data),
		(व्योम __user *)(((uपूर्णांकptr_t)
			  buffer->user_data + buffer_size) & PAGE_MASK));

	rb_erase(&buffer->rb_node, &alloc->allocated_buffers);
	buffer->मुक्त = 1;
	अगर (!list_is_last(&buffer->entry, &alloc->buffers)) अणु
		काष्ठा binder_buffer *next = binder_buffer_next(buffer);

		अगर (next->मुक्त) अणु
			rb_erase(&next->rb_node, &alloc->मुक्त_buffers);
			binder_delete_मुक्त_buffer(alloc, next);
		पूर्ण
	पूर्ण
	अगर (alloc->buffers.next != &buffer->entry) अणु
		काष्ठा binder_buffer *prev = binder_buffer_prev(buffer);

		अगर (prev->मुक्त) अणु
			binder_delete_मुक्त_buffer(alloc, buffer);
			rb_erase(&prev->rb_node, &alloc->मुक्त_buffers);
			buffer = prev;
		पूर्ण
	पूर्ण
	binder_insert_मुक्त_buffer(alloc, buffer);
पूर्ण

अटल व्योम binder_alloc_clear_buf(काष्ठा binder_alloc *alloc,
				   काष्ठा binder_buffer *buffer);
/**
 * binder_alloc_मुक्त_buf() - मुक्त a binder buffer
 * @alloc:	binder_alloc क्रम this proc
 * @buffer:	kernel poपूर्णांकer to buffer
 *
 * Free the buffer allocated via binder_alloc_new_buf()
 */
व्योम binder_alloc_मुक्त_buf(काष्ठा binder_alloc *alloc,
			    काष्ठा binder_buffer *buffer)
अणु
	/*
	 * We could eliminate the call to binder_alloc_clear_buf()
	 * from binder_alloc_deferred_release() by moving this to
	 * binder_alloc_मुक्त_buf_locked(). However, that could
	 * increase contention क्रम the alloc mutex अगर clear_on_मुक्त
	 * is used frequently क्रम large buffers. The mutex is not
	 * needed क्रम correctness here.
	 */
	अगर (buffer->clear_on_मुक्त) अणु
		binder_alloc_clear_buf(alloc, buffer);
		buffer->clear_on_मुक्त = false;
	पूर्ण
	mutex_lock(&alloc->mutex);
	binder_मुक्त_buf_locked(alloc, buffer);
	mutex_unlock(&alloc->mutex);
पूर्ण

/**
 * binder_alloc_mmap_handler() - map भव address space क्रम proc
 * @alloc:	alloc काष्ठाure क्रम this proc
 * @vma:	vma passed to mmap()
 *
 * Called by binder_mmap() to initialize the space specअगरied in
 * vma क्रम allocating binder buffers
 *
 * Return:
 *      0 = success
 *      -EBUSY = address space alपढ़ोy mapped
 *      -ENOMEM = failed to map memory to given address space
 */
पूर्णांक binder_alloc_mmap_handler(काष्ठा binder_alloc *alloc,
			      काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक ret;
	स्थिर अक्षर *failure_string;
	काष्ठा binder_buffer *buffer;

	mutex_lock(&binder_alloc_mmap_lock);
	अगर (alloc->buffer_size) अणु
		ret = -EBUSY;
		failure_string = "already mapped";
		जाओ err_alपढ़ोy_mapped;
	पूर्ण
	alloc->buffer_size = min_t(अचिन्हित दीर्घ, vma->vm_end - vma->vm_start,
				   SZ_4M);
	mutex_unlock(&binder_alloc_mmap_lock);

	alloc->buffer = (व्योम __user *)vma->vm_start;

	alloc->pages = kसुस्मृति(alloc->buffer_size / PAGE_SIZE,
			       माप(alloc->pages[0]),
			       GFP_KERNEL);
	अगर (alloc->pages == शून्य) अणु
		ret = -ENOMEM;
		failure_string = "alloc page array";
		जाओ err_alloc_pages_failed;
	पूर्ण

	buffer = kzalloc(माप(*buffer), GFP_KERNEL);
	अगर (!buffer) अणु
		ret = -ENOMEM;
		failure_string = "alloc buffer struct";
		जाओ err_alloc_buf_काष्ठा_failed;
	पूर्ण

	buffer->user_data = alloc->buffer;
	list_add(&buffer->entry, &alloc->buffers);
	buffer->मुक्त = 1;
	binder_insert_मुक्त_buffer(alloc, buffer);
	alloc->मुक्त_async_space = alloc->buffer_size / 2;
	binder_alloc_set_vma(alloc, vma);
	mmgrab(alloc->vma_vm_mm);

	वापस 0;

err_alloc_buf_काष्ठा_failed:
	kमुक्त(alloc->pages);
	alloc->pages = शून्य;
err_alloc_pages_failed:
	alloc->buffer = शून्य;
	mutex_lock(&binder_alloc_mmap_lock);
	alloc->buffer_size = 0;
err_alपढ़ोy_mapped:
	mutex_unlock(&binder_alloc_mmap_lock);
	binder_alloc_debug(BINDER_DEBUG_USER_ERROR,
			   "%s: %d %lx-%lx %s failed %d\n", __func__,
			   alloc->pid, vma->vm_start, vma->vm_end,
			   failure_string, ret);
	वापस ret;
पूर्ण


व्योम binder_alloc_deferred_release(काष्ठा binder_alloc *alloc)
अणु
	काष्ठा rb_node *n;
	पूर्णांक buffers, page_count;
	काष्ठा binder_buffer *buffer;

	buffers = 0;
	mutex_lock(&alloc->mutex);
	BUG_ON(alloc->vma);

	जबतक ((n = rb_first(&alloc->allocated_buffers))) अणु
		buffer = rb_entry(n, काष्ठा binder_buffer, rb_node);

		/* Transaction should alपढ़ोy have been मुक्तd */
		BUG_ON(buffer->transaction);

		अगर (buffer->clear_on_मुक्त) अणु
			binder_alloc_clear_buf(alloc, buffer);
			buffer->clear_on_मुक्त = false;
		पूर्ण
		binder_मुक्त_buf_locked(alloc, buffer);
		buffers++;
	पूर्ण

	जबतक (!list_empty(&alloc->buffers)) अणु
		buffer = list_first_entry(&alloc->buffers,
					  काष्ठा binder_buffer, entry);
		WARN_ON(!buffer->मुक्त);

		list_del(&buffer->entry);
		WARN_ON_ONCE(!list_empty(&alloc->buffers));
		kमुक्त(buffer);
	पूर्ण

	page_count = 0;
	अगर (alloc->pages) अणु
		पूर्णांक i;

		क्रम (i = 0; i < alloc->buffer_size / PAGE_SIZE; i++) अणु
			व्योम __user *page_addr;
			bool on_lru;

			अगर (!alloc->pages[i].page_ptr)
				जारी;

			on_lru = list_lru_del(&binder_alloc_lru,
					      &alloc->pages[i].lru);
			page_addr = alloc->buffer + i * PAGE_SIZE;
			binder_alloc_debug(BINDER_DEBUG_BUFFER_ALLOC,
				     "%s: %d: page %d at %pK %s\n",
				     __func__, alloc->pid, i, page_addr,
				     on_lru ? "on lru" : "active");
			__मुक्त_page(alloc->pages[i].page_ptr);
			page_count++;
		पूर्ण
		kमुक्त(alloc->pages);
	पूर्ण
	mutex_unlock(&alloc->mutex);
	अगर (alloc->vma_vm_mm)
		mmdrop(alloc->vma_vm_mm);

	binder_alloc_debug(BINDER_DEBUG_OPEN_CLOSE,
		     "%s: %d buffers %d, pages %d\n",
		     __func__, alloc->pid, buffers, page_count);
पूर्ण

अटल व्योम prपूर्णांक_binder_buffer(काष्ठा seq_file *m, स्थिर अक्षर *prefix,
				काष्ठा binder_buffer *buffer)
अणु
	seq_म_लिखो(m, "%s %d: %pK size %zd:%zd:%zd %s\n",
		   prefix, buffer->debug_id, buffer->user_data,
		   buffer->data_size, buffer->offsets_size,
		   buffer->extra_buffers_size,
		   buffer->transaction ? "active" : "delivered");
पूर्ण

/**
 * binder_alloc_prपूर्णांक_allocated() - prपूर्णांक buffer info
 * @m:     seq_file क्रम output via seq_म_लिखो()
 * @alloc: binder_alloc क्रम this proc
 *
 * Prपूर्णांकs inक्रमmation about every buffer associated with
 * the binder_alloc state to the given seq_file
 */
व्योम binder_alloc_prपूर्णांक_allocated(काष्ठा seq_file *m,
				  काष्ठा binder_alloc *alloc)
अणु
	काष्ठा rb_node *n;

	mutex_lock(&alloc->mutex);
	क्रम (n = rb_first(&alloc->allocated_buffers); n != शून्य; n = rb_next(n))
		prपूर्णांक_binder_buffer(m, "  buffer",
				    rb_entry(n, काष्ठा binder_buffer, rb_node));
	mutex_unlock(&alloc->mutex);
पूर्ण

/**
 * binder_alloc_prपूर्णांक_pages() - prपूर्णांक page usage
 * @m:     seq_file क्रम output via seq_म_लिखो()
 * @alloc: binder_alloc क्रम this proc
 */
व्योम binder_alloc_prपूर्णांक_pages(काष्ठा seq_file *m,
			      काष्ठा binder_alloc *alloc)
अणु
	काष्ठा binder_lru_page *page;
	पूर्णांक i;
	पूर्णांक active = 0;
	पूर्णांक lru = 0;
	पूर्णांक मुक्त = 0;

	mutex_lock(&alloc->mutex);
	/*
	 * Make sure the binder_alloc is fully initialized, otherwise we might
	 * पढ़ो inconsistent state.
	 */
	अगर (binder_alloc_get_vma(alloc) != शून्य) अणु
		क्रम (i = 0; i < alloc->buffer_size / PAGE_SIZE; i++) अणु
			page = &alloc->pages[i];
			अगर (!page->page_ptr)
				मुक्त++;
			अन्यथा अगर (list_empty(&page->lru))
				active++;
			अन्यथा
				lru++;
		पूर्ण
	पूर्ण
	mutex_unlock(&alloc->mutex);
	seq_म_लिखो(m, "  pages: %d:%d:%d\n", active, lru, मुक्त);
	seq_म_लिखो(m, "  pages high watermark: %zu\n", alloc->pages_high);
पूर्ण

/**
 * binder_alloc_get_allocated_count() - वापस count of buffers
 * @alloc: binder_alloc क्रम this proc
 *
 * Return: count of allocated buffers
 */
पूर्णांक binder_alloc_get_allocated_count(काष्ठा binder_alloc *alloc)
अणु
	काष्ठा rb_node *n;
	पूर्णांक count = 0;

	mutex_lock(&alloc->mutex);
	क्रम (n = rb_first(&alloc->allocated_buffers); n != शून्य; n = rb_next(n))
		count++;
	mutex_unlock(&alloc->mutex);
	वापस count;
पूर्ण


/**
 * binder_alloc_vma_बंद() - invalidate address space
 * @alloc: binder_alloc क्रम this proc
 *
 * Called from binder_vma_बंद() when releasing address space.
 * Clears alloc->vma to prevent new incoming transactions from
 * allocating more buffers.
 */
व्योम binder_alloc_vma_बंद(काष्ठा binder_alloc *alloc)
अणु
	binder_alloc_set_vma(alloc, शून्य);
पूर्ण

/**
 * binder_alloc_मुक्त_page() - shrinker callback to मुक्त pages
 * @item:   item to मुक्त
 * @lock:   lock protecting the item
 * @cb_arg: callback argument
 *
 * Called from list_lru_walk() in binder_shrink_scan() to मुक्त
 * up pages when the प्रणाली is under memory pressure.
 */
क्रमागत lru_status binder_alloc_मुक्त_page(काष्ठा list_head *item,
				       काष्ठा list_lru_one *lru,
				       spinlock_t *lock,
				       व्योम *cb_arg)
	__must_hold(lock)
अणु
	काष्ठा mm_काष्ठा *mm = शून्य;
	काष्ठा binder_lru_page *page = container_of(item,
						    काष्ठा binder_lru_page,
						    lru);
	काष्ठा binder_alloc *alloc;
	uपूर्णांकptr_t page_addr;
	माप_प्रकार index;
	काष्ठा vm_area_काष्ठा *vma;

	alloc = page->alloc;
	अगर (!mutex_trylock(&alloc->mutex))
		जाओ err_get_alloc_mutex_failed;

	अगर (!page->page_ptr)
		जाओ err_page_alपढ़ोy_मुक्तd;

	index = page - alloc->pages;
	page_addr = (uपूर्णांकptr_t)alloc->buffer + index * PAGE_SIZE;

	mm = alloc->vma_vm_mm;
	अगर (!mmget_not_zero(mm))
		जाओ err_mmget;
	अगर (!mmap_पढ़ो_trylock(mm))
		जाओ err_mmap_पढ़ो_lock_failed;
	vma = binder_alloc_get_vma(alloc);

	list_lru_isolate(lru, item);
	spin_unlock(lock);

	अगर (vma) अणु
		trace_binder_unmap_user_start(alloc, index);

		zap_page_range(vma, page_addr, PAGE_SIZE);

		trace_binder_unmap_user_end(alloc, index);
	पूर्ण
	mmap_पढ़ो_unlock(mm);
	mmput_async(mm);

	trace_binder_unmap_kernel_start(alloc, index);

	__मुक्त_page(page->page_ptr);
	page->page_ptr = शून्य;

	trace_binder_unmap_kernel_end(alloc, index);

	spin_lock(lock);
	mutex_unlock(&alloc->mutex);
	वापस LRU_REMOVED_RETRY;

err_mmap_पढ़ो_lock_failed:
	mmput_async(mm);
err_mmget:
err_page_alपढ़ोy_मुक्तd:
	mutex_unlock(&alloc->mutex);
err_get_alloc_mutex_failed:
	वापस LRU_SKIP;
पूर्ण

अटल अचिन्हित दीर्घ
binder_shrink_count(काष्ठा shrinker *shrink, काष्ठा shrink_control *sc)
अणु
	अचिन्हित दीर्घ ret = list_lru_count(&binder_alloc_lru);
	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ
binder_shrink_scan(काष्ठा shrinker *shrink, काष्ठा shrink_control *sc)
अणु
	अचिन्हित दीर्घ ret;

	ret = list_lru_walk(&binder_alloc_lru, binder_alloc_मुक्त_page,
			    शून्य, sc->nr_to_scan);
	वापस ret;
पूर्ण

अटल काष्ठा shrinker binder_shrinker = अणु
	.count_objects = binder_shrink_count,
	.scan_objects = binder_shrink_scan,
	.seeks = DEFAULT_SEEKS,
पूर्ण;

/**
 * binder_alloc_init() - called by binder_खोलो() क्रम per-proc initialization
 * @alloc: binder_alloc क्रम this proc
 *
 * Called from binder_खोलो() to initialize binder_alloc fields क्रम
 * new binder proc
 */
व्योम binder_alloc_init(काष्ठा binder_alloc *alloc)
अणु
	alloc->pid = current->group_leader->pid;
	mutex_init(&alloc->mutex);
	INIT_LIST_HEAD(&alloc->buffers);
पूर्ण

पूर्णांक binder_alloc_shrinker_init(व्योम)
अणु
	पूर्णांक ret = list_lru_init(&binder_alloc_lru);

	अगर (ret == 0) अणु
		ret = रेजिस्टर_shrinker(&binder_shrinker);
		अगर (ret)
			list_lru_destroy(&binder_alloc_lru);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * check_buffer() - verअगरy that buffer/offset is safe to access
 * @alloc: binder_alloc क्रम this proc
 * @buffer: binder buffer to be accessed
 * @offset: offset पूर्णांकo @buffer data
 * @bytes: bytes to access from offset
 *
 * Check that the @offset/@bytes are within the size of the given
 * @buffer and that the buffer is currently active and not मुक्तable.
 * Offsets must also be multiples of माप(u32). The kernel is
 * allowed to touch the buffer in two हालs:
 *
 * 1) when the buffer is being created:
 *     (buffer->मुक्त == 0 && buffer->allow_user_मुक्त == 0)
 * 2) when the buffer is being torn करोwn:
 *     (buffer->मुक्त == 0 && buffer->transaction == शून्य).
 *
 * Return: true अगर the buffer is safe to access
 */
अटल अंतरभूत bool check_buffer(काष्ठा binder_alloc *alloc,
				काष्ठा binder_buffer *buffer,
				binder_माप_प्रकार offset, माप_प्रकार bytes)
अणु
	माप_प्रकार buffer_size = binder_alloc_buffer_size(alloc, buffer);

	वापस buffer_size >= bytes &&
		offset <= buffer_size - bytes &&
		IS_ALIGNED(offset, माप(u32)) &&
		!buffer->मुक्त &&
		(!buffer->allow_user_मुक्त || !buffer->transaction);
पूर्ण

/**
 * binder_alloc_get_page() - get kernel poपूर्णांकer क्रम given buffer offset
 * @alloc: binder_alloc क्रम this proc
 * @buffer: binder buffer to be accessed
 * @buffer_offset: offset पूर्णांकo @buffer data
 * @pgoffp: address to copy final page offset to
 *
 * Lookup the काष्ठा page corresponding to the address
 * at @buffer_offset पूर्णांकo @buffer->user_data. If @pgoffp is not
 * शून्य, the byte-offset पूर्णांकo the page is written there.
 *
 * The caller is responsible to ensure that the offset poपूर्णांकs
 * to a valid address within the @buffer and that @buffer is
 * not मुक्तable by the user. Since it can't be मुक्तd, we are
 * guaranteed that the corresponding elements of @alloc->pages[]
 * cannot change.
 *
 * Return: काष्ठा page
 */
अटल काष्ठा page *binder_alloc_get_page(काष्ठा binder_alloc *alloc,
					  काष्ठा binder_buffer *buffer,
					  binder_माप_प्रकार buffer_offset,
					  pgoff_t *pgoffp)
अणु
	binder_माप_प्रकार buffer_space_offset = buffer_offset +
		(buffer->user_data - alloc->buffer);
	pgoff_t pgoff = buffer_space_offset & ~PAGE_MASK;
	माप_प्रकार index = buffer_space_offset >> PAGE_SHIFT;
	काष्ठा binder_lru_page *lru_page;

	lru_page = &alloc->pages[index];
	*pgoffp = pgoff;
	वापस lru_page->page_ptr;
पूर्ण

/**
 * binder_alloc_clear_buf() - zero out buffer
 * @alloc: binder_alloc क्रम this proc
 * @buffer: binder buffer to be cleared
 *
 * स_रखो the given buffer to 0
 */
अटल व्योम binder_alloc_clear_buf(काष्ठा binder_alloc *alloc,
				   काष्ठा binder_buffer *buffer)
अणु
	माप_प्रकार bytes = binder_alloc_buffer_size(alloc, buffer);
	binder_माप_प्रकार buffer_offset = 0;

	जबतक (bytes) अणु
		अचिन्हित दीर्घ size;
		काष्ठा page *page;
		pgoff_t pgoff;
		व्योम *kptr;

		page = binder_alloc_get_page(alloc, buffer,
					     buffer_offset, &pgoff);
		size = min_t(माप_प्रकार, bytes, PAGE_SIZE - pgoff);
		kptr = kmap(page) + pgoff;
		स_रखो(kptr, 0, size);
		kunmap(page);
		bytes -= size;
		buffer_offset += size;
	पूर्ण
पूर्ण

/**
 * binder_alloc_copy_user_to_buffer() - copy src user to tgt user
 * @alloc: binder_alloc क्रम this proc
 * @buffer: binder buffer to be accessed
 * @buffer_offset: offset पूर्णांकo @buffer data
 * @from: userspace poपूर्णांकer to source buffer
 * @bytes: bytes to copy
 *
 * Copy bytes from source userspace to target buffer.
 *
 * Return: bytes reमुख्यing to be copied
 */
अचिन्हित दीर्घ
binder_alloc_copy_user_to_buffer(काष्ठा binder_alloc *alloc,
				 काष्ठा binder_buffer *buffer,
				 binder_माप_प्रकार buffer_offset,
				 स्थिर व्योम __user *from,
				 माप_प्रकार bytes)
अणु
	अगर (!check_buffer(alloc, buffer, buffer_offset, bytes))
		वापस bytes;

	जबतक (bytes) अणु
		अचिन्हित दीर्घ size;
		अचिन्हित दीर्घ ret;
		काष्ठा page *page;
		pgoff_t pgoff;
		व्योम *kptr;

		page = binder_alloc_get_page(alloc, buffer,
					     buffer_offset, &pgoff);
		size = min_t(माप_प्रकार, bytes, PAGE_SIZE - pgoff);
		kptr = kmap(page) + pgoff;
		ret = copy_from_user(kptr, from, size);
		kunmap(page);
		अगर (ret)
			वापस bytes - size + ret;
		bytes -= size;
		from += size;
		buffer_offset += size;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक binder_alloc_करो_buffer_copy(काष्ठा binder_alloc *alloc,
				       bool to_buffer,
				       काष्ठा binder_buffer *buffer,
				       binder_माप_प्रकार buffer_offset,
				       व्योम *ptr,
				       माप_प्रकार bytes)
अणु
	/* All copies must be 32-bit aligned and 32-bit size */
	अगर (!check_buffer(alloc, buffer, buffer_offset, bytes))
		वापस -EINVAL;

	जबतक (bytes) अणु
		अचिन्हित दीर्घ size;
		काष्ठा page *page;
		pgoff_t pgoff;
		व्योम *पंचांगpptr;
		व्योम *base_ptr;

		page = binder_alloc_get_page(alloc, buffer,
					     buffer_offset, &pgoff);
		size = min_t(माप_प्रकार, bytes, PAGE_SIZE - pgoff);
		base_ptr = kmap_atomic(page);
		पंचांगpptr = base_ptr + pgoff;
		अगर (to_buffer)
			स_नकल(पंचांगpptr, ptr, size);
		अन्यथा
			स_नकल(ptr, पंचांगpptr, size);
		/*
		 * kunmap_atomic() takes care of flushing the cache
		 * अगर this device has VIVT cache arch
		 */
		kunmap_atomic(base_ptr);
		bytes -= size;
		pgoff = 0;
		ptr = ptr + size;
		buffer_offset += size;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक binder_alloc_copy_to_buffer(काष्ठा binder_alloc *alloc,
				काष्ठा binder_buffer *buffer,
				binder_माप_प्रकार buffer_offset,
				व्योम *src,
				माप_प्रकार bytes)
अणु
	वापस binder_alloc_करो_buffer_copy(alloc, true, buffer, buffer_offset,
					   src, bytes);
पूर्ण

पूर्णांक binder_alloc_copy_from_buffer(काष्ठा binder_alloc *alloc,
				  व्योम *dest,
				  काष्ठा binder_buffer *buffer,
				  binder_माप_प्रकार buffer_offset,
				  माप_प्रकार bytes)
अणु
	वापस binder_alloc_करो_buffer_copy(alloc, false, buffer, buffer_offset,
					   dest, bytes);
पूर्ण

