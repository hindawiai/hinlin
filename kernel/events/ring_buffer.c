<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Perक्रमmance events ring-buffer code:
 *
 *  Copyright (C) 2008 Thomas Gleixner <tglx@linutronix.de>
 *  Copyright (C) 2008-2011 Red Hat, Inc., Ingo Molnar
 *  Copyright (C) 2008-2011 Red Hat, Inc., Peter Zijlstra
 *  Copyright  तऊ  2009 Paul Mackerras, IBM Corp. <paulus@au1.ibm.com>
 */

#समावेश <linux/perf_event.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/poll.h>
#समावेश <linux/nospec.h>

#समावेश "internal.h"

अटल व्योम perf_output_wakeup(काष्ठा perf_output_handle *handle)
अणु
	atomic_set(&handle->rb->poll, EPOLLIN);

	handle->event->pending_wakeup = 1;
	irq_work_queue(&handle->event->pending);
पूर्ण

/*
 * We need to ensure a later event_id करोesn't publish a head when a क्रमmer
 * event isn't करोne writing. However since we need to deal with NMIs we
 * cannot fully serialize things.
 *
 * We only publish the head (and generate a wakeup) when the outer-most
 * event completes.
 */
अटल व्योम perf_output_get_handle(काष्ठा perf_output_handle *handle)
अणु
	काष्ठा perf_buffer *rb = handle->rb;

	preempt_disable();

	/*
	 * Aव्योम an explicit LOAD/STORE such that architectures with memops
	 * can use them.
	 */
	(*(अस्थिर अचिन्हित पूर्णांक *)&rb->nest)++;
	handle->wakeup = local_पढ़ो(&rb->wakeup);
पूर्ण

अटल व्योम perf_output_put_handle(काष्ठा perf_output_handle *handle)
अणु
	काष्ठा perf_buffer *rb = handle->rb;
	अचिन्हित दीर्घ head;
	अचिन्हित पूर्णांक nest;

	/*
	 * If this isn't the outermost nesting, we don't have to update
	 * @rb->user_page->data_head.
	 */
	nest = READ_ONCE(rb->nest);
	अगर (nest > 1) अणु
		WRITE_ONCE(rb->nest, nest - 1);
		जाओ out;
	पूर्ण

again:
	/*
	 * In order to aव्योम publishing a head value that goes backwards,
	 * we must ensure the load of @rb->head happens after we've
	 * incremented @rb->nest.
	 *
	 * Otherwise we can observe a @rb->head value beक्रमe one published
	 * by an IRQ/NMI happening between the load and the increment.
	 */
	barrier();
	head = local_पढ़ो(&rb->head);

	/*
	 * IRQ/NMI can happen here and advance @rb->head, causing our
	 * load above to be stale.
	 */

	/*
	 * Since the mmap() consumer (userspace) can run on a dअगरferent CPU:
	 *
	 *   kernel				user
	 *
	 *   अगर (LOAD ->data_tail) अणु		LOAD ->data_head
	 *			(A)		smp_rmb()	(C)
	 *	STORE $data			LOAD $data
	 *	smp_wmb()	(B)		smp_mb()	(D)
	 *	STORE ->data_head		STORE ->data_tail
	 *   पूर्ण
	 *
	 * Where A pairs with D, and B pairs with C.
	 *
	 * In our हाल (A) is a control dependency that separates the load of
	 * the ->data_tail and the stores of $data. In हाल ->data_tail
	 * indicates there is no room in the buffer to store $data we करो not.
	 *
	 * D needs to be a full barrier since it separates the data READ
	 * from the tail WRITE.
	 *
	 * For B a WMB is sufficient since it separates two WRITEs, and क्रम C
	 * an RMB is sufficient since it separates two READs.
	 *
	 * See perf_output_begin().
	 */
	smp_wmb(); /* B, matches C */
	WRITE_ONCE(rb->user_page->data_head, head);

	/*
	 * We must publish the head beक्रमe decrementing the nest count,
	 * otherwise an IRQ/NMI can publish a more recent head value and our
	 * ग_लिखो will (temporarily) publish a stale value.
	 */
	barrier();
	WRITE_ONCE(rb->nest, 0);

	/*
	 * Ensure we decrement @rb->nest beक्रमe we validate the @rb->head.
	 * Otherwise we cannot be sure we caught the 'last' nested update.
	 */
	barrier();
	अगर (unlikely(head != local_पढ़ो(&rb->head))) अणु
		WRITE_ONCE(rb->nest, 1);
		जाओ again;
	पूर्ण

	अगर (handle->wakeup != local_पढ़ो(&rb->wakeup))
		perf_output_wakeup(handle);

out:
	preempt_enable();
पूर्ण

अटल __always_अंतरभूत bool
ring_buffer_has_space(अचिन्हित दीर्घ head, अचिन्हित दीर्घ tail,
		      अचिन्हित दीर्घ data_size, अचिन्हित पूर्णांक size,
		      bool backward)
अणु
	अगर (!backward)
		वापस CIRC_SPACE(head, tail, data_size) >= size;
	अन्यथा
		वापस CIRC_SPACE(tail, head, data_size) >= size;
पूर्ण

अटल __always_अंतरभूत पूर्णांक
__perf_output_begin(काष्ठा perf_output_handle *handle,
		    काष्ठा perf_sample_data *data,
		    काष्ठा perf_event *event, अचिन्हित पूर्णांक size,
		    bool backward)
अणु
	काष्ठा perf_buffer *rb;
	अचिन्हित दीर्घ tail, offset, head;
	पूर्णांक have_lost, page_shअगरt;
	काष्ठा अणु
		काष्ठा perf_event_header header;
		u64			 id;
		u64			 lost;
	पूर्ण lost_event;

	rcu_पढ़ो_lock();
	/*
	 * For inherited events we send all the output towards the parent.
	 */
	अगर (event->parent)
		event = event->parent;

	rb = rcu_dereference(event->rb);
	अगर (unlikely(!rb))
		जाओ out;

	अगर (unlikely(rb->छोड़ोd)) अणु
		अगर (rb->nr_pages)
			local_inc(&rb->lost);
		जाओ out;
	पूर्ण

	handle->rb    = rb;
	handle->event = event;

	have_lost = local_पढ़ो(&rb->lost);
	अगर (unlikely(have_lost)) अणु
		size += माप(lost_event);
		अगर (event->attr.sample_id_all)
			size += event->id_header_size;
	पूर्ण

	perf_output_get_handle(handle);

	करो अणु
		tail = READ_ONCE(rb->user_page->data_tail);
		offset = head = local_पढ़ो(&rb->head);
		अगर (!rb->overग_लिखो) अणु
			अगर (unlikely(!ring_buffer_has_space(head, tail,
							    perf_data_size(rb),
							    size, backward)))
				जाओ fail;
		पूर्ण

		/*
		 * The above क्रमms a control dependency barrier separating the
		 * @tail load above from the data stores below. Since the @tail
		 * load is required to compute the branch to fail below.
		 *
		 * A, matches D; the full memory barrier userspace SHOULD issue
		 * after पढ़ोing the data and beक्रमe storing the new tail
		 * position.
		 *
		 * See perf_output_put_handle().
		 */

		अगर (!backward)
			head += size;
		अन्यथा
			head -= size;
	पूर्ण जबतक (local_cmpxchg(&rb->head, offset, head) != offset);

	अगर (backward) अणु
		offset = head;
		head = (u64)(-head);
	पूर्ण

	/*
	 * We rely on the implied barrier() by local_cmpxchg() to ensure
	 * none of the data stores below can be lअगरted up by the compiler.
	 */

	अगर (unlikely(head - local_पढ़ो(&rb->wakeup) > rb->watermark))
		local_add(rb->watermark, &rb->wakeup);

	page_shअगरt = PAGE_SHIFT + page_order(rb);

	handle->page = (offset >> page_shअगरt) & (rb->nr_pages - 1);
	offset &= (1UL << page_shअगरt) - 1;
	handle->addr = rb->data_pages[handle->page] + offset;
	handle->size = (1UL << page_shअगरt) - offset;

	अगर (unlikely(have_lost)) अणु
		lost_event.header.size = माप(lost_event);
		lost_event.header.type = PERF_RECORD_LOST;
		lost_event.header.misc = 0;
		lost_event.id          = event->id;
		lost_event.lost        = local_xchg(&rb->lost, 0);

		/* XXX mostly redundant; @data is alपढ़ोy fully initializes */
		perf_event_header__init_id(&lost_event.header, data, event);
		perf_output_put(handle, lost_event);
		perf_event__output_id_sample(event, handle, data);
	पूर्ण

	वापस 0;

fail:
	local_inc(&rb->lost);
	perf_output_put_handle(handle);
out:
	rcu_पढ़ो_unlock();

	वापस -ENOSPC;
पूर्ण

पूर्णांक perf_output_begin_क्रमward(काष्ठा perf_output_handle *handle,
			      काष्ठा perf_sample_data *data,
			      काष्ठा perf_event *event, अचिन्हित पूर्णांक size)
अणु
	वापस __perf_output_begin(handle, data, event, size, false);
पूर्ण

पूर्णांक perf_output_begin_backward(काष्ठा perf_output_handle *handle,
			       काष्ठा perf_sample_data *data,
			       काष्ठा perf_event *event, अचिन्हित पूर्णांक size)
अणु
	वापस __perf_output_begin(handle, data, event, size, true);
पूर्ण

पूर्णांक perf_output_begin(काष्ठा perf_output_handle *handle,
		      काष्ठा perf_sample_data *data,
		      काष्ठा perf_event *event, अचिन्हित पूर्णांक size)
अणु

	वापस __perf_output_begin(handle, data, event, size,
				   unlikely(is_ग_लिखो_backward(event)));
पूर्ण

अचिन्हित पूर्णांक perf_output_copy(काष्ठा perf_output_handle *handle,
		      स्थिर व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	वापस __output_copy(handle, buf, len);
पूर्ण

अचिन्हित पूर्णांक perf_output_skip(काष्ठा perf_output_handle *handle,
			      अचिन्हित पूर्णांक len)
अणु
	वापस __output_skip(handle, शून्य, len);
पूर्ण

व्योम perf_output_end(काष्ठा perf_output_handle *handle)
अणु
	perf_output_put_handle(handle);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम
ring_buffer_init(काष्ठा perf_buffer *rb, दीर्घ watermark, पूर्णांक flags)
अणु
	दीर्घ max_size = perf_data_size(rb);

	अगर (watermark)
		rb->watermark = min(max_size, watermark);

	अगर (!rb->watermark)
		rb->watermark = max_size / 2;

	अगर (flags & RING_BUFFER_WRITABLE)
		rb->overग_लिखो = 0;
	अन्यथा
		rb->overग_लिखो = 1;

	refcount_set(&rb->refcount, 1);

	INIT_LIST_HEAD(&rb->event_list);
	spin_lock_init(&rb->event_lock);

	/*
	 * perf_output_begin() only checks rb->छोड़ोd, thereक्रमe
	 * rb->छोड़ोd must be true अगर we have no pages क्रम output.
	 */
	अगर (!rb->nr_pages)
		rb->छोड़ोd = 1;
पूर्ण

व्योम perf_aux_output_flag(काष्ठा perf_output_handle *handle, u64 flags)
अणु
	/*
	 * OVERWRITE is determined by perf_aux_output_end() and can't
	 * be passed in directly.
	 */
	अगर (WARN_ON_ONCE(flags & PERF_AUX_FLAG_OVERWRITE))
		वापस;

	handle->aux_flags |= flags;
पूर्ण
EXPORT_SYMBOL_GPL(perf_aux_output_flag);

/*
 * This is called beक्रमe hardware starts writing to the AUX area to
 * obtain an output handle and make sure there's room in the buffer.
 * When the capture completes, call perf_aux_output_end() to commit
 * the recorded data to the buffer.
 *
 * The ordering is similar to that of perf_output_अणुbegin,endपूर्ण, with
 * the exception of (B), which should be taken care of by the pmu
 * driver, since ordering rules will dअगरfer depending on hardware.
 *
 * Call this from pmu::start(); see the comment in perf_aux_output_end()
 * about its use in pmu callbacks. Both can also be called from the PMI
 * handler अगर needed.
 */
व्योम *perf_aux_output_begin(काष्ठा perf_output_handle *handle,
			    काष्ठा perf_event *event)
अणु
	काष्ठा perf_event *output_event = event;
	अचिन्हित दीर्घ aux_head, aux_tail;
	काष्ठा perf_buffer *rb;
	अचिन्हित पूर्णांक nest;

	अगर (output_event->parent)
		output_event = output_event->parent;

	/*
	 * Since this will typically be खोलो across pmu::add/pmu::del, we
	 * grab ring_buffer's refcount instead of holding rcu पढ़ो lock
	 * to make sure it करोesn't disappear under us.
	 */
	rb = ring_buffer_get(output_event);
	अगर (!rb)
		वापस शून्य;

	अगर (!rb_has_aux(rb))
		जाओ err;

	/*
	 * If aux_mmap_count is zero, the aux buffer is in perf_mmap_बंद(),
	 * about to get मुक्तd, so we leave immediately.
	 *
	 * Checking rb::aux_mmap_count and rb::refcount has to be करोne in
	 * the same order, see perf_mmap_बंद. Otherwise we end up मुक्तing
	 * aux pages in this path, which is a bug, because in_atomic().
	 */
	अगर (!atomic_पढ़ो(&rb->aux_mmap_count))
		जाओ err;

	अगर (!refcount_inc_not_zero(&rb->aux_refcount))
		जाओ err;

	nest = READ_ONCE(rb->aux_nest);
	/*
	 * Nesting is not supported क्रम AUX area, make sure nested
	 * ग_लिखोrs are caught early
	 */
	अगर (WARN_ON_ONCE(nest))
		जाओ err_put;

	WRITE_ONCE(rb->aux_nest, nest + 1);

	aux_head = rb->aux_head;

	handle->rb = rb;
	handle->event = event;
	handle->head = aux_head;
	handle->size = 0;
	handle->aux_flags = 0;

	/*
	 * In overग_लिखो mode, AUX data stores करो not depend on aux_tail,
	 * thereक्रमe (A) control dependency barrier करोes not exist. The
	 * (B) <-> (C) ordering is still observed by the pmu driver.
	 */
	अगर (!rb->aux_overग_लिखो) अणु
		aux_tail = READ_ONCE(rb->user_page->aux_tail);
		handle->wakeup = rb->aux_wakeup + rb->aux_watermark;
		अगर (aux_head - aux_tail < perf_aux_size(rb))
			handle->size = CIRC_SPACE(aux_head, aux_tail, perf_aux_size(rb));

		/*
		 * handle->size computation depends on aux_tail load; this क्रमms a
		 * control dependency barrier separating aux_tail load from aux data
		 * store that will be enabled on successful वापस
		 */
		अगर (!handle->size) अणु /* A, matches D */
			event->pending_disable = smp_processor_id();
			perf_output_wakeup(handle);
			WRITE_ONCE(rb->aux_nest, 0);
			जाओ err_put;
		पूर्ण
	पूर्ण

	वापस handle->rb->aux_priv;

err_put:
	/* can't be last */
	rb_मुक्त_aux(rb);

err:
	ring_buffer_put(rb);
	handle->event = शून्य;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(perf_aux_output_begin);

अटल __always_अंतरभूत bool rb_need_aux_wakeup(काष्ठा perf_buffer *rb)
अणु
	अगर (rb->aux_overग_लिखो)
		वापस false;

	अगर (rb->aux_head - rb->aux_wakeup >= rb->aux_watermark) अणु
		rb->aux_wakeup = roundकरोwn(rb->aux_head, rb->aux_watermark);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Commit the data written by hardware पूर्णांकo the ring buffer by adjusting
 * aux_head and posting a PERF_RECORD_AUX पूर्णांकo the perf buffer. It is the
 * pmu driver's responsibility to observe ordering rules of the hardware,
 * so that all the data is बाह्यally visible beक्रमe this is called.
 *
 * Note: this has to be called from pmu::stop() callback, as the assumption
 * of the AUX buffer management code is that after pmu::stop(), the AUX
 * transaction must be stopped and thereक्रमe drop the AUX reference count.
 */
व्योम perf_aux_output_end(काष्ठा perf_output_handle *handle, अचिन्हित दीर्घ size)
अणु
	bool wakeup = !!(handle->aux_flags & PERF_AUX_FLAG_TRUNCATED);
	काष्ठा perf_buffer *rb = handle->rb;
	अचिन्हित दीर्घ aux_head;

	/* in overग_लिखो mode, driver provides aux_head via handle */
	अगर (rb->aux_overग_लिखो) अणु
		handle->aux_flags |= PERF_AUX_FLAG_OVERWRITE;

		aux_head = handle->head;
		rb->aux_head = aux_head;
	पूर्ण अन्यथा अणु
		handle->aux_flags &= ~PERF_AUX_FLAG_OVERWRITE;

		aux_head = rb->aux_head;
		rb->aux_head += size;
	पूर्ण

	/*
	 * Only send RECORD_AUX अगर we have something useful to communicate
	 *
	 * Note: the OVERWRITE records by themselves are not considered
	 * useful, as they करोn't communicate any *new* inक्रमmation,
	 * aside from the लघु-lived offset, that becomes history at
	 * the next event sched-in and thereक्रमe isn't useful.
	 * The userspace that needs to copy out AUX data in overग_लिखो
	 * mode should know to use user_page::aux_head क्रम the actual
	 * offset. So, from now on we करोn't output AUX records that
	 * have *only* OVERWRITE flag set.
	 */
	अगर (size || (handle->aux_flags & ~(u64)PERF_AUX_FLAG_OVERWRITE))
		perf_event_aux_event(handle->event, aux_head, size,
				     handle->aux_flags);

	WRITE_ONCE(rb->user_page->aux_head, rb->aux_head);
	अगर (rb_need_aux_wakeup(rb))
		wakeup = true;

	अगर (wakeup) अणु
		अगर (handle->aux_flags & PERF_AUX_FLAG_TRUNCATED)
			handle->event->pending_disable = smp_processor_id();
		perf_output_wakeup(handle);
	पूर्ण

	handle->event = शून्य;

	WRITE_ONCE(rb->aux_nest, 0);
	/* can't be last */
	rb_मुक्त_aux(rb);
	ring_buffer_put(rb);
पूर्ण
EXPORT_SYMBOL_GPL(perf_aux_output_end);

/*
 * Skip over a given number of bytes in the AUX buffer, due to, क्रम example,
 * hardware's alignment स्थिरraपूर्णांकs.
 */
पूर्णांक perf_aux_output_skip(काष्ठा perf_output_handle *handle, अचिन्हित दीर्घ size)
अणु
	काष्ठा perf_buffer *rb = handle->rb;

	अगर (size > handle->size)
		वापस -ENOSPC;

	rb->aux_head += size;

	WRITE_ONCE(rb->user_page->aux_head, rb->aux_head);
	अगर (rb_need_aux_wakeup(rb)) अणु
		perf_output_wakeup(handle);
		handle->wakeup = rb->aux_wakeup + rb->aux_watermark;
	पूर्ण

	handle->head = rb->aux_head;
	handle->size -= size;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(perf_aux_output_skip);

व्योम *perf_get_aux(काष्ठा perf_output_handle *handle)
अणु
	/* this is only valid between perf_aux_output_begin and *_end */
	अगर (!handle->event)
		वापस शून्य;

	वापस handle->rb->aux_priv;
पूर्ण
EXPORT_SYMBOL_GPL(perf_get_aux);

/*
 * Copy out AUX data from an AUX handle.
 */
दीर्घ perf_output_copy_aux(काष्ठा perf_output_handle *aux_handle,
			  काष्ठा perf_output_handle *handle,
			  अचिन्हित दीर्घ from, अचिन्हित दीर्घ to)
अणु
	काष्ठा perf_buffer *rb = aux_handle->rb;
	अचिन्हित दीर्घ tocopy, reमुख्यder, len = 0;
	व्योम *addr;

	from &= (rb->aux_nr_pages << PAGE_SHIFT) - 1;
	to &= (rb->aux_nr_pages << PAGE_SHIFT) - 1;

	करो अणु
		tocopy = PAGE_SIZE - offset_in_page(from);
		अगर (to > from)
			tocopy = min(tocopy, to - from);
		अगर (!tocopy)
			अवरोध;

		addr = rb->aux_pages[from >> PAGE_SHIFT];
		addr += offset_in_page(from);

		reमुख्यder = perf_output_copy(handle, addr, tocopy);
		अगर (reमुख्यder)
			वापस -EFAULT;

		len += tocopy;
		from += tocopy;
		from &= (rb->aux_nr_pages << PAGE_SHIFT) - 1;
	पूर्ण जबतक (to != from);

	वापस len;
पूर्ण

#घोषणा PERF_AUX_GFP	(GFP_KERNEL | __GFP_ZERO | __GFP_NOWARN | __GFP_NORETRY)

अटल काष्ठा page *rb_alloc_aux_page(पूर्णांक node, पूर्णांक order)
अणु
	काष्ठा page *page;

	अगर (order > MAX_ORDER)
		order = MAX_ORDER;

	करो अणु
		page = alloc_pages_node(node, PERF_AUX_GFP, order);
	पूर्ण जबतक (!page && order--);

	अगर (page && order) अणु
		/*
		 * Communicate the allocation size to the driver:
		 * अगर we managed to secure a high-order allocation,
		 * set its first page's निजी to this order;
		 * !PagePrivate(page) means it's just a normal page.
		 */
		split_page(page, order);
		SetPagePrivate(page);
		set_page_निजी(page, order);
	पूर्ण

	वापस page;
पूर्ण

अटल व्योम rb_मुक्त_aux_page(काष्ठा perf_buffer *rb, पूर्णांक idx)
अणु
	काष्ठा page *page = virt_to_page(rb->aux_pages[idx]);

	ClearPagePrivate(page);
	page->mapping = शून्य;
	__मुक्त_page(page);
पूर्ण

अटल व्योम __rb_मुक्त_aux(काष्ठा perf_buffer *rb)
अणु
	पूर्णांक pg;

	/*
	 * Should never happen, the last reference should be dropped from
	 * perf_mmap_बंद() path, which first stops aux transactions (which
	 * in turn are the atomic holders of aux_refcount) and then करोes the
	 * last rb_मुक्त_aux().
	 */
	WARN_ON_ONCE(in_atomic());

	अगर (rb->aux_priv) अणु
		rb->मुक्त_aux(rb->aux_priv);
		rb->मुक्त_aux = शून्य;
		rb->aux_priv = शून्य;
	पूर्ण

	अगर (rb->aux_nr_pages) अणु
		क्रम (pg = 0; pg < rb->aux_nr_pages; pg++)
			rb_मुक्त_aux_page(rb, pg);

		kमुक्त(rb->aux_pages);
		rb->aux_nr_pages = 0;
	पूर्ण
पूर्ण

पूर्णांक rb_alloc_aux(काष्ठा perf_buffer *rb, काष्ठा perf_event *event,
		 pgoff_t pgoff, पूर्णांक nr_pages, दीर्घ watermark, पूर्णांक flags)
अणु
	bool overग_लिखो = !(flags & RING_BUFFER_WRITABLE);
	पूर्णांक node = (event->cpu == -1) ? -1 : cpu_to_node(event->cpu);
	पूर्णांक ret = -ENOMEM, max_order;

	अगर (!has_aux(event))
		वापस -EOPNOTSUPP;

	अगर (!overग_लिखो) अणु
		/*
		 * Watermark शेषs to half the buffer, and so करोes the
		 * max_order, to aid PMU drivers in द्विगुन buffering.
		 */
		अगर (!watermark)
			watermark = nr_pages << (PAGE_SHIFT - 1);

		/*
		 * Use aux_watermark as the basis क्रम chunking to
		 * help PMU drivers honor the watermark.
		 */
		max_order = get_order(watermark);
	पूर्ण अन्यथा अणु
		/*
		 * We need to start with the max_order that fits in nr_pages,
		 * not the other way around, hence ilog2() and not get_order.
		 */
		max_order = ilog2(nr_pages);
		watermark = 0;
	पूर्ण

	rb->aux_pages = kसुस्मृति_node(nr_pages, माप(व्योम *), GFP_KERNEL,
				     node);
	अगर (!rb->aux_pages)
		वापस -ENOMEM;

	rb->मुक्त_aux = event->pmu->मुक्त_aux;
	क्रम (rb->aux_nr_pages = 0; rb->aux_nr_pages < nr_pages;) अणु
		काष्ठा page *page;
		पूर्णांक last, order;

		order = min(max_order, ilog2(nr_pages - rb->aux_nr_pages));
		page = rb_alloc_aux_page(node, order);
		अगर (!page)
			जाओ out;

		क्रम (last = rb->aux_nr_pages + (1 << page_निजी(page));
		     last > rb->aux_nr_pages; rb->aux_nr_pages++)
			rb->aux_pages[rb->aux_nr_pages] = page_address(page++);
	पूर्ण

	/*
	 * In overग_लिखो mode, PMUs that करोn't support SG may not handle more
	 * than one contiguous allocation, since they rely on PMI to करो द्विगुन
	 * buffering. In this हाल, the entire buffer has to be one contiguous
	 * chunk.
	 */
	अगर ((event->pmu->capabilities & PERF_PMU_CAP_AUX_NO_SG) &&
	    overग_लिखो) अणु
		काष्ठा page *page = virt_to_page(rb->aux_pages[0]);

		अगर (page_निजी(page) != max_order)
			जाओ out;
	पूर्ण

	rb->aux_priv = event->pmu->setup_aux(event, rb->aux_pages, nr_pages,
					     overग_लिखो);
	अगर (!rb->aux_priv)
		जाओ out;

	ret = 0;

	/*
	 * aux_pages (and pmu driver's निजी data, aux_priv) will be
	 * referenced in both producer's and consumer's contexts, thus
	 * we keep a refcount here to make sure either of the two can
	 * reference them safely.
	 */
	refcount_set(&rb->aux_refcount, 1);

	rb->aux_overग_लिखो = overग_लिखो;
	rb->aux_watermark = watermark;

out:
	अगर (!ret)
		rb->aux_pgoff = pgoff;
	अन्यथा
		__rb_मुक्त_aux(rb);

	वापस ret;
पूर्ण

व्योम rb_मुक्त_aux(काष्ठा perf_buffer *rb)
अणु
	अगर (refcount_dec_and_test(&rb->aux_refcount))
		__rb_मुक्त_aux(rb);
पूर्ण

#अगर_अघोषित CONFIG_PERF_USE_VMALLOC

/*
 * Back perf_mmap() with regular GFP_KERNEL-0 pages.
 */

अटल काष्ठा page *
__perf_mmap_to_page(काष्ठा perf_buffer *rb, अचिन्हित दीर्घ pgoff)
अणु
	अगर (pgoff > rb->nr_pages)
		वापस शून्य;

	अगर (pgoff == 0)
		वापस virt_to_page(rb->user_page);

	वापस virt_to_page(rb->data_pages[pgoff - 1]);
पूर्ण

अटल व्योम *perf_mmap_alloc_page(पूर्णांक cpu)
अणु
	काष्ठा page *page;
	पूर्णांक node;

	node = (cpu == -1) ? cpu : cpu_to_node(cpu);
	page = alloc_pages_node(node, GFP_KERNEL | __GFP_ZERO, 0);
	अगर (!page)
		वापस शून्य;

	वापस page_address(page);
पूर्ण

अटल व्योम perf_mmap_मुक्त_page(व्योम *addr)
अणु
	काष्ठा page *page = virt_to_page(addr);

	page->mapping = शून्य;
	__मुक्त_page(page);
पूर्ण

काष्ठा perf_buffer *rb_alloc(पूर्णांक nr_pages, दीर्घ watermark, पूर्णांक cpu, पूर्णांक flags)
अणु
	काष्ठा perf_buffer *rb;
	अचिन्हित दीर्घ size;
	पूर्णांक i, node;

	size = माप(काष्ठा perf_buffer);
	size += nr_pages * माप(व्योम *);

	अगर (order_base_2(size) >= PAGE_SHIFT+MAX_ORDER)
		जाओ fail;

	node = (cpu == -1) ? cpu : cpu_to_node(cpu);
	rb = kzalloc_node(size, GFP_KERNEL, node);
	अगर (!rb)
		जाओ fail;

	rb->user_page = perf_mmap_alloc_page(cpu);
	अगर (!rb->user_page)
		जाओ fail_user_page;

	क्रम (i = 0; i < nr_pages; i++) अणु
		rb->data_pages[i] = perf_mmap_alloc_page(cpu);
		अगर (!rb->data_pages[i])
			जाओ fail_data_pages;
	पूर्ण

	rb->nr_pages = nr_pages;

	ring_buffer_init(rb, watermark, flags);

	वापस rb;

fail_data_pages:
	क्रम (i--; i >= 0; i--)
		perf_mmap_मुक्त_page(rb->data_pages[i]);

	perf_mmap_मुक्त_page(rb->user_page);

fail_user_page:
	kमुक्त(rb);

fail:
	वापस शून्य;
पूर्ण

व्योम rb_मुक्त(काष्ठा perf_buffer *rb)
अणु
	पूर्णांक i;

	perf_mmap_मुक्त_page(rb->user_page);
	क्रम (i = 0; i < rb->nr_pages; i++)
		perf_mmap_मुक्त_page(rb->data_pages[i]);
	kमुक्त(rb);
पूर्ण

#अन्यथा
अटल पूर्णांक data_page_nr(काष्ठा perf_buffer *rb)
अणु
	वापस rb->nr_pages << page_order(rb);
पूर्ण

अटल काष्ठा page *
__perf_mmap_to_page(काष्ठा perf_buffer *rb, अचिन्हित दीर्घ pgoff)
अणु
	/* The '>' counts in the user page. */
	अगर (pgoff > data_page_nr(rb))
		वापस शून्य;

	वापस vदो_स्मृति_to_page((व्योम *)rb->user_page + pgoff * PAGE_SIZE);
पूर्ण

अटल व्योम perf_mmap_unmark_page(व्योम *addr)
अणु
	काष्ठा page *page = vदो_स्मृति_to_page(addr);

	page->mapping = शून्य;
पूर्ण

अटल व्योम rb_मुक्त_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा perf_buffer *rb;
	व्योम *base;
	पूर्णांक i, nr;

	rb = container_of(work, काष्ठा perf_buffer, work);
	nr = data_page_nr(rb);

	base = rb->user_page;
	/* The '<=' counts in the user page. */
	क्रम (i = 0; i <= nr; i++)
		perf_mmap_unmark_page(base + (i * PAGE_SIZE));

	vमुक्त(base);
	kमुक्त(rb);
पूर्ण

व्योम rb_मुक्त(काष्ठा perf_buffer *rb)
अणु
	schedule_work(&rb->work);
पूर्ण

काष्ठा perf_buffer *rb_alloc(पूर्णांक nr_pages, दीर्घ watermark, पूर्णांक cpu, पूर्णांक flags)
अणु
	काष्ठा perf_buffer *rb;
	अचिन्हित दीर्घ size;
	व्योम *all_buf;
	पूर्णांक node;

	size = माप(काष्ठा perf_buffer);
	size += माप(व्योम *);

	node = (cpu == -1) ? cpu : cpu_to_node(cpu);
	rb = kzalloc_node(size, GFP_KERNEL, node);
	अगर (!rb)
		जाओ fail;

	INIT_WORK(&rb->work, rb_मुक्त_work);

	all_buf = vदो_स्मृति_user((nr_pages + 1) * PAGE_SIZE);
	अगर (!all_buf)
		जाओ fail_all_buf;

	rb->user_page = all_buf;
	rb->data_pages[0] = all_buf + PAGE_SIZE;
	अगर (nr_pages) अणु
		rb->nr_pages = 1;
		rb->page_order = ilog2(nr_pages);
	पूर्ण

	ring_buffer_init(rb, watermark, flags);

	वापस rb;

fail_all_buf:
	kमुक्त(rb);

fail:
	वापस शून्य;
पूर्ण

#पूर्ण_अगर

काष्ठा page *
perf_mmap_to_page(काष्ठा perf_buffer *rb, अचिन्हित दीर्घ pgoff)
अणु
	अगर (rb->aux_nr_pages) अणु
		/* above AUX space */
		अगर (pgoff > rb->aux_pgoff + rb->aux_nr_pages)
			वापस शून्य;

		/* AUX space */
		अगर (pgoff >= rb->aux_pgoff) अणु
			पूर्णांक aux_pgoff = array_index_nospec(pgoff - rb->aux_pgoff, rb->aux_nr_pages);
			वापस virt_to_page(rb->aux_pages[aux_pgoff]);
		पूर्ण
	पूर्ण

	वापस __perf_mmap_to_page(rb, pgoff);
पूर्ण
