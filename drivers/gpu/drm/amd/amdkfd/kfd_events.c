<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/mm_types.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/mm.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mman.h>
#समावेश <linux/memory.h>
#समावेश "kfd_priv.h"
#समावेश "kfd_events.h"
#समावेश "kfd_iommu.h"
#समावेश <linux/device.h>

/*
 * Wrapper around रुको_queue_entry_t
 */
काष्ठा kfd_event_रुकोer अणु
	रुको_queue_entry_t रुको;
	काष्ठा kfd_event *event; /* Event to रुको क्रम */
	bool activated;		 /* Becomes true when event is संकेतed */
पूर्ण;

/*
 * Each संकेत event needs a 64-bit संकेत slot where the संकेतer will ग_लिखो
 * a 1 beक्रमe sending an पूर्णांकerrupt. (This is needed because some पूर्णांकerrupts
 * करो not contain enough spare data bits to identअगरy an event.)
 * We get whole pages and map them to the process VA.
 * Inभागidual संकेत events use their event_id as slot index.
 */
काष्ठा kfd_संकेत_page अणु
	uपूर्णांक64_t *kernel_address;
	uपूर्णांक64_t __user *user_address;
	bool need_to_मुक्त_pages;
पूर्ण;


अटल uपूर्णांक64_t *page_slots(काष्ठा kfd_संकेत_page *page)
अणु
	वापस page->kernel_address;
पूर्ण

अटल काष्ठा kfd_संकेत_page *allocate_संकेत_page(काष्ठा kfd_process *p)
अणु
	व्योम *backing_store;
	काष्ठा kfd_संकेत_page *page;

	page = kzalloc(माप(*page), GFP_KERNEL);
	अगर (!page)
		वापस शून्य;

	backing_store = (व्योम *) __get_मुक्त_pages(GFP_KERNEL,
					get_order(KFD_SIGNAL_EVENT_LIMIT * 8));
	अगर (!backing_store)
		जाओ fail_alloc_संकेत_store;

	/* Initialize all events to unसंकेतed */
	स_रखो(backing_store, (uपूर्णांक8_t) UNSIGNALED_EVENT_SLOT,
	       KFD_SIGNAL_EVENT_LIMIT * 8);

	page->kernel_address = backing_store;
	page->need_to_मुक्त_pages = true;
	pr_debug("Allocated new event signal page at %p, for process %p\n",
			page, p);

	वापस page;

fail_alloc_संकेत_store:
	kमुक्त(page);
	वापस शून्य;
पूर्ण

अटल पूर्णांक allocate_event_notअगरication_slot(काष्ठा kfd_process *p,
					    काष्ठा kfd_event *ev)
अणु
	पूर्णांक id;

	अगर (!p->संकेत_page) अणु
		p->संकेत_page = allocate_संकेत_page(p);
		अगर (!p->संकेत_page)
			वापस -ENOMEM;
		/* Oldest user mode expects 256 event slots */
		p->संकेत_mapped_size = 256*8;
	पूर्ण

	/*
	 * Compatibility with old user mode: Only use संकेत slots
	 * user mode has mapped, may be less than
	 * KFD_SIGNAL_EVENT_LIMIT. This also allows future increase
	 * of the event limit without अवरोधing user mode.
	 */
	id = idr_alloc(&p->event_idr, ev, 0, p->संकेत_mapped_size / 8,
		       GFP_KERNEL);
	अगर (id < 0)
		वापस id;

	ev->event_id = id;
	page_slots(p->संकेत_page)[id] = UNSIGNALED_EVENT_SLOT;

	वापस 0;
पूर्ण

/*
 * Assumes that p->event_mutex is held and of course that p is not going
 * away (current or locked).
 */
अटल काष्ठा kfd_event *lookup_event_by_id(काष्ठा kfd_process *p, uपूर्णांक32_t id)
अणु
	वापस idr_find(&p->event_idr, id);
पूर्ण

/**
 * lookup_संकेतed_event_by_partial_id - Lookup संकेतed event from partial ID
 * @p:     Poपूर्णांकer to काष्ठा kfd_process
 * @id:    ID to look up
 * @bits:  Number of valid bits in @id
 *
 * Finds the first संकेतed event with a matching partial ID. If no
 * matching संकेतed event is found, वापसs शून्य. In that हाल the
 * caller should assume that the partial ID is invalid and करो an
 * exhaustive search of all siglaned events.
 *
 * If multiple events with the same partial ID संकेत at the same
 * समय, they will be found one पूर्णांकerrupt at a समय, not necessarily
 * in the same order the पूर्णांकerrupts occurred. As दीर्घ as the number of
 * पूर्णांकerrupts is correct, all संकेतed events will be seen by the
 * driver.
 */
अटल काष्ठा kfd_event *lookup_संकेतed_event_by_partial_id(
	काष्ठा kfd_process *p, uपूर्णांक32_t id, uपूर्णांक32_t bits)
अणु
	काष्ठा kfd_event *ev;

	अगर (!p->संकेत_page || id >= KFD_SIGNAL_EVENT_LIMIT)
		वापस शून्य;

	/* Fast path क्रम the common हाल that @id is not a partial ID
	 * and we only need a single lookup.
	 */
	अगर (bits > 31 || (1U << bits) >= KFD_SIGNAL_EVENT_LIMIT) अणु
		अगर (page_slots(p->संकेत_page)[id] == UNSIGNALED_EVENT_SLOT)
			वापस शून्य;

		वापस idr_find(&p->event_idr, id);
	पूर्ण

	/* General हाल क्रम partial IDs: Iterate over all matching IDs
	 * and find the first one that has संकेतed.
	 */
	क्रम (ev = शून्य; id < KFD_SIGNAL_EVENT_LIMIT && !ev; id += 1U << bits) अणु
		अगर (page_slots(p->संकेत_page)[id] == UNSIGNALED_EVENT_SLOT)
			जारी;

		ev = idr_find(&p->event_idr, id);
	पूर्ण

	वापस ev;
पूर्ण

अटल पूर्णांक create_संकेत_event(काष्ठा file *devkfd,
				काष्ठा kfd_process *p,
				काष्ठा kfd_event *ev)
अणु
	पूर्णांक ret;

	अगर (p->संकेत_mapped_size &&
	    p->संकेत_event_count == p->संकेत_mapped_size / 8) अणु
		अगर (!p->संकेत_event_limit_reached) अणु
			pr_debug("Signal event wasn't created because limit was reached\n");
			p->संकेत_event_limit_reached = true;
		पूर्ण
		वापस -ENOSPC;
	पूर्ण

	ret = allocate_event_notअगरication_slot(p, ev);
	अगर (ret) अणु
		pr_warn("Signal event wasn't created because out of kernel memory\n");
		वापस ret;
	पूर्ण

	p->संकेत_event_count++;

	ev->user_संकेत_address = &p->संकेत_page->user_address[ev->event_id];
	pr_debug("Signal event number %zu created with id %d, address %p\n",
			p->संकेत_event_count, ev->event_id,
			ev->user_संकेत_address);

	वापस 0;
पूर्ण

अटल पूर्णांक create_other_event(काष्ठा kfd_process *p, काष्ठा kfd_event *ev)
अणु
	/* Cast KFD_LAST_NONSIGNAL_EVENT to uपूर्णांक32_t. This allows an
	 * पूर्णांकentional पूर्णांकeger overflow to -1 without a compiler
	 * warning. idr_alloc treats a negative value as "maximum
	 * चिन्हित पूर्णांकeger".
	 */
	पूर्णांक id = idr_alloc(&p->event_idr, ev, KFD_FIRST_NONSIGNAL_EVENT_ID,
			   (uपूर्णांक32_t)KFD_LAST_NONSIGNAL_EVENT_ID + 1,
			   GFP_KERNEL);

	अगर (id < 0)
		वापस id;
	ev->event_id = id;

	वापस 0;
पूर्ण

व्योम kfd_event_init_process(काष्ठा kfd_process *p)
अणु
	mutex_init(&p->event_mutex);
	idr_init(&p->event_idr);
	p->संकेत_page = शून्य;
	p->संकेत_event_count = 0;
पूर्ण

अटल व्योम destroy_event(काष्ठा kfd_process *p, काष्ठा kfd_event *ev)
अणु
	काष्ठा kfd_event_रुकोer *रुकोer;

	/* Wake up pending रुकोers. They will वापस failure */
	list_क्रम_each_entry(रुकोer, &ev->wq.head, रुको.entry)
		रुकोer->event = शून्य;
	wake_up_all(&ev->wq);

	अगर (ev->type == KFD_EVENT_TYPE_SIGNAL ||
	    ev->type == KFD_EVENT_TYPE_DEBUG)
		p->संकेत_event_count--;

	idr_हटाओ(&p->event_idr, ev->event_id);
	kमुक्त(ev);
पूर्ण

अटल व्योम destroy_events(काष्ठा kfd_process *p)
अणु
	काष्ठा kfd_event *ev;
	uपूर्णांक32_t id;

	idr_क्रम_each_entry(&p->event_idr, ev, id)
		destroy_event(p, ev);
	idr_destroy(&p->event_idr);
पूर्ण

/*
 * We assume that the process is being destroyed and there is no need to
 * unmap the pages or keep bookkeeping data in order.
 */
अटल व्योम shutकरोwn_संकेत_page(काष्ठा kfd_process *p)
अणु
	काष्ठा kfd_संकेत_page *page = p->संकेत_page;

	अगर (page) अणु
		अगर (page->need_to_मुक्त_pages)
			मुक्त_pages((अचिन्हित दीर्घ)page->kernel_address,
				   get_order(KFD_SIGNAL_EVENT_LIMIT * 8));
		kमुक्त(page);
	पूर्ण
पूर्ण

व्योम kfd_event_मुक्त_process(काष्ठा kfd_process *p)
अणु
	destroy_events(p);
	shutकरोwn_संकेत_page(p);
पूर्ण

अटल bool event_can_be_gpu_संकेतed(स्थिर काष्ठा kfd_event *ev)
अणु
	वापस ev->type == KFD_EVENT_TYPE_SIGNAL ||
					ev->type == KFD_EVENT_TYPE_DEBUG;
पूर्ण

अटल bool event_can_be_cpu_संकेतed(स्थिर काष्ठा kfd_event *ev)
अणु
	वापस ev->type == KFD_EVENT_TYPE_SIGNAL;
पूर्ण

पूर्णांक kfd_event_page_set(काष्ठा kfd_process *p, व्योम *kernel_address,
		       uपूर्णांक64_t size)
अणु
	काष्ठा kfd_संकेत_page *page;

	अगर (p->संकेत_page)
		वापस -EBUSY;

	page = kzalloc(माप(*page), GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	/* Initialize all events to unसंकेतed */
	स_रखो(kernel_address, (uपूर्णांक8_t) UNSIGNALED_EVENT_SLOT,
	       KFD_SIGNAL_EVENT_LIMIT * 8);

	page->kernel_address = kernel_address;

	p->संकेत_page = page;
	p->संकेत_mapped_size = size;

	वापस 0;
पूर्ण

पूर्णांक kfd_event_create(काष्ठा file *devkfd, काष्ठा kfd_process *p,
		     uपूर्णांक32_t event_type, bool स्वतः_reset, uपूर्णांक32_t node_id,
		     uपूर्णांक32_t *event_id, uपूर्णांक32_t *event_trigger_data,
		     uपूर्णांक64_t *event_page_offset, uपूर्णांक32_t *event_slot_index)
अणु
	पूर्णांक ret = 0;
	काष्ठा kfd_event *ev = kzalloc(माप(*ev), GFP_KERNEL);

	अगर (!ev)
		वापस -ENOMEM;

	ev->type = event_type;
	ev->स्वतः_reset = स्वतः_reset;
	ev->संकेतed = false;

	init_रुकोqueue_head(&ev->wq);

	*event_page_offset = 0;

	mutex_lock(&p->event_mutex);

	चयन (event_type) अणु
	हाल KFD_EVENT_TYPE_SIGNAL:
	हाल KFD_EVENT_TYPE_DEBUG:
		ret = create_संकेत_event(devkfd, p, ev);
		अगर (!ret) अणु
			*event_page_offset = KFD_MMAP_TYPE_EVENTS;
			*event_slot_index = ev->event_id;
		पूर्ण
		अवरोध;
	शेष:
		ret = create_other_event(p, ev);
		अवरोध;
	पूर्ण

	अगर (!ret) अणु
		*event_id = ev->event_id;
		*event_trigger_data = ev->event_id;
	पूर्ण अन्यथा अणु
		kमुक्त(ev);
	पूर्ण

	mutex_unlock(&p->event_mutex);

	वापस ret;
पूर्ण

/* Assumes that p is current. */
पूर्णांक kfd_event_destroy(काष्ठा kfd_process *p, uपूर्णांक32_t event_id)
अणु
	काष्ठा kfd_event *ev;
	पूर्णांक ret = 0;

	mutex_lock(&p->event_mutex);

	ev = lookup_event_by_id(p, event_id);

	अगर (ev)
		destroy_event(p, ev);
	अन्यथा
		ret = -EINVAL;

	mutex_unlock(&p->event_mutex);
	वापस ret;
पूर्ण

अटल व्योम set_event(काष्ठा kfd_event *ev)
अणु
	काष्ठा kfd_event_रुकोer *रुकोer;

	/* Auto reset अगर the list is non-empty and we're waking
	 * someone. रुकोqueue_active is safe here because we're
	 * रक्षित by the p->event_mutex, which is also held when
	 * updating the रुको queues in kfd_रुको_on_events.
	 */
	ev->संकेतed = !ev->स्वतः_reset || !रुकोqueue_active(&ev->wq);

	list_क्रम_each_entry(रुकोer, &ev->wq.head, रुको.entry)
		रुकोer->activated = true;

	wake_up_all(&ev->wq);
पूर्ण

/* Assumes that p is current. */
पूर्णांक kfd_set_event(काष्ठा kfd_process *p, uपूर्णांक32_t event_id)
अणु
	पूर्णांक ret = 0;
	काष्ठा kfd_event *ev;

	mutex_lock(&p->event_mutex);

	ev = lookup_event_by_id(p, event_id);

	अगर (ev && event_can_be_cpu_संकेतed(ev))
		set_event(ev);
	अन्यथा
		ret = -EINVAL;

	mutex_unlock(&p->event_mutex);
	वापस ret;
पूर्ण

अटल व्योम reset_event(काष्ठा kfd_event *ev)
अणु
	ev->संकेतed = false;
पूर्ण

/* Assumes that p is current. */
पूर्णांक kfd_reset_event(काष्ठा kfd_process *p, uपूर्णांक32_t event_id)
अणु
	पूर्णांक ret = 0;
	काष्ठा kfd_event *ev;

	mutex_lock(&p->event_mutex);

	ev = lookup_event_by_id(p, event_id);

	अगर (ev && event_can_be_cpu_संकेतed(ev))
		reset_event(ev);
	अन्यथा
		ret = -EINVAL;

	mutex_unlock(&p->event_mutex);
	वापस ret;

पूर्ण

अटल व्योम acknowledge_संकेत(काष्ठा kfd_process *p, काष्ठा kfd_event *ev)
अणु
	page_slots(p->संकेत_page)[ev->event_id] = UNSIGNALED_EVENT_SLOT;
पूर्ण

अटल व्योम set_event_from_पूर्णांकerrupt(काष्ठा kfd_process *p,
					काष्ठा kfd_event *ev)
अणु
	अगर (ev && event_can_be_gpu_संकेतed(ev)) अणु
		acknowledge_संकेत(p, ev);
		set_event(ev);
	पूर्ण
पूर्ण

व्योम kfd_संकेत_event_पूर्णांकerrupt(u32 pasid, uपूर्णांक32_t partial_id,
				uपूर्णांक32_t valid_id_bits)
अणु
	काष्ठा kfd_event *ev = शून्य;

	/*
	 * Because we are called from arbitrary context (workqueue) as opposed
	 * to process context, kfd_process could attempt to निकास जबतक we are
	 * running so the lookup function increments the process ref count.
	 */
	काष्ठा kfd_process *p = kfd_lookup_process_by_pasid(pasid);

	अगर (!p)
		वापस; /* Presumably process निकासed. */

	mutex_lock(&p->event_mutex);

	अगर (valid_id_bits)
		ev = lookup_संकेतed_event_by_partial_id(p, partial_id,
							 valid_id_bits);
	अगर (ev) अणु
		set_event_from_पूर्णांकerrupt(p, ev);
	पूर्ण अन्यथा अगर (p->संकेत_page) अणु
		/*
		 * Partial ID lookup failed. Assume that the event ID
		 * in the पूर्णांकerrupt payload was invalid and करो an
		 * exhaustive search of संकेतed events.
		 */
		uपूर्णांक64_t *slots = page_slots(p->संकेत_page);
		uपूर्णांक32_t id;

		अगर (valid_id_bits)
			pr_debug_ratelimited("Partial ID invalid: %u (%u valid bits)\n",
					     partial_id, valid_id_bits);

		अगर (p->संकेत_event_count < KFD_SIGNAL_EVENT_LIMIT / 64) अणु
			/* With relatively few events, it's faster to
			 * iterate over the event IDR
			 */
			idr_क्रम_each_entry(&p->event_idr, ev, id) अणु
				अगर (id >= KFD_SIGNAL_EVENT_LIMIT)
					अवरोध;

				अगर (slots[id] != UNSIGNALED_EVENT_SLOT)
					set_event_from_पूर्णांकerrupt(p, ev);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* With relatively many events, it's faster to
			 * iterate over the संकेत slots and lookup
			 * only संकेतed events from the IDR.
			 */
			क्रम (id = 0; id < KFD_SIGNAL_EVENT_LIMIT; id++)
				अगर (slots[id] != UNSIGNALED_EVENT_SLOT) अणु
					ev = lookup_event_by_id(p, id);
					set_event_from_पूर्णांकerrupt(p, ev);
				पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&p->event_mutex);
	kfd_unref_process(p);
पूर्ण

अटल काष्ठा kfd_event_रुकोer *alloc_event_रुकोers(uपूर्णांक32_t num_events)
अणु
	काष्ठा kfd_event_रुकोer *event_रुकोers;
	uपूर्णांक32_t i;

	event_रुकोers = kदो_स्मृति_array(num_events,
					माप(काष्ठा kfd_event_रुकोer),
					GFP_KERNEL);

	क्रम (i = 0; (event_रुकोers) && (i < num_events) ; i++) अणु
		init_रुको(&event_रुकोers[i].रुको);
		event_रुकोers[i].activated = false;
	पूर्ण

	वापस event_रुकोers;
पूर्ण

अटल पूर्णांक init_event_रुकोer_get_status(काष्ठा kfd_process *p,
		काष्ठा kfd_event_रुकोer *रुकोer,
		uपूर्णांक32_t event_id)
अणु
	काष्ठा kfd_event *ev = lookup_event_by_id(p, event_id);

	अगर (!ev)
		वापस -EINVAL;

	रुकोer->event = ev;
	रुकोer->activated = ev->संकेतed;
	ev->संकेतed = ev->संकेतed && !ev->स्वतः_reset;

	वापस 0;
पूर्ण

अटल व्योम init_event_रुकोer_add_to_रुकोlist(काष्ठा kfd_event_रुकोer *रुकोer)
अणु
	काष्ठा kfd_event *ev = रुकोer->event;

	/* Only add to the रुको list अगर we actually need to
	 * रुको on this event.
	 */
	अगर (!रुकोer->activated)
		add_रुको_queue(&ev->wq, &रुकोer->रुको);
पूर्ण

/* test_event_condition - Test condition of events being रुकोed क्रम
 * @all:           Return completion only अगर all events have संकेतed
 * @num_events:    Number of events to रुको क्रम
 * @event_रुकोers: Array of event रुकोers, one per event
 *
 * Returns KFD_IOC_WAIT_RESULT_COMPLETE अगर all (or one) event(s) have
 * संकेतed. Returns KFD_IOC_WAIT_RESULT_TIMEOUT अगर no (or not all)
 * events have संकेतed. Returns KFD_IOC_WAIT_RESULT_FAIL अगर any of
 * the events have been destroyed.
 */
अटल uपूर्णांक32_t test_event_condition(bool all, uपूर्णांक32_t num_events,
				काष्ठा kfd_event_रुकोer *event_रुकोers)
अणु
	uपूर्णांक32_t i;
	uपूर्णांक32_t activated_count = 0;

	क्रम (i = 0; i < num_events; i++) अणु
		अगर (!event_रुकोers[i].event)
			वापस KFD_IOC_WAIT_RESULT_FAIL;

		अगर (event_रुकोers[i].activated) अणु
			अगर (!all)
				वापस KFD_IOC_WAIT_RESULT_COMPLETE;

			activated_count++;
		पूर्ण
	पूर्ण

	वापस activated_count == num_events ?
		KFD_IOC_WAIT_RESULT_COMPLETE : KFD_IOC_WAIT_RESULT_TIMEOUT;
पूर्ण

/*
 * Copy event specअगरic data, अगर defined.
 * Currently only memory exception events have additional data to copy to user
 */
अटल पूर्णांक copy_संकेतed_event_data(uपूर्णांक32_t num_events,
		काष्ठा kfd_event_रुकोer *event_रुकोers,
		काष्ठा kfd_event_data __user *data)
अणु
	काष्ठा kfd_hsa_memory_exception_data *src;
	काष्ठा kfd_hsa_memory_exception_data __user *dst;
	काष्ठा kfd_event_रुकोer *रुकोer;
	काष्ठा kfd_event *event;
	uपूर्णांक32_t i;

	क्रम (i = 0; i < num_events; i++) अणु
		रुकोer = &event_रुकोers[i];
		event = रुकोer->event;
		अगर (रुकोer->activated && event->type == KFD_EVENT_TYPE_MEMORY) अणु
			dst = &data[i].memory_exception_data;
			src = &event->memory_exception_data;
			अगर (copy_to_user(dst, src,
				माप(काष्ठा kfd_hsa_memory_exception_data)))
				वापस -EFAULT;
		पूर्ण
	पूर्ण

	वापस 0;

पूर्ण



अटल दीर्घ user_समयout_to_jअगरfies(uपूर्णांक32_t user_समयout_ms)
अणु
	अगर (user_समयout_ms == KFD_EVENT_TIMEOUT_IMMEDIATE)
		वापस 0;

	अगर (user_समयout_ms == KFD_EVENT_TIMEOUT_INFINITE)
		वापस MAX_SCHEDULE_TIMEOUT;

	/*
	 * msecs_to_jअगरfies पूर्णांकerprets all values above 2^31-1 as infinite,
	 * but we consider them finite.
	 * This hack is wrong, but nobody is likely to notice.
	 */
	user_समयout_ms = min_t(uपूर्णांक32_t, user_समयout_ms, 0x7FFFFFFF);

	वापस msecs_to_jअगरfies(user_समयout_ms) + 1;
पूर्ण

अटल व्योम मुक्त_रुकोers(uपूर्णांक32_t num_events, काष्ठा kfd_event_रुकोer *रुकोers)
अणु
	uपूर्णांक32_t i;

	क्रम (i = 0; i < num_events; i++)
		अगर (रुकोers[i].event)
			हटाओ_रुको_queue(&रुकोers[i].event->wq,
					  &रुकोers[i].रुको);

	kमुक्त(रुकोers);
पूर्ण

पूर्णांक kfd_रुको_on_events(काष्ठा kfd_process *p,
		       uपूर्णांक32_t num_events, व्योम __user *data,
		       bool all, uपूर्णांक32_t user_समयout_ms,
		       uपूर्णांक32_t *रुको_result)
अणु
	काष्ठा kfd_event_data __user *events =
			(काष्ठा kfd_event_data __user *) data;
	uपूर्णांक32_t i;
	पूर्णांक ret = 0;

	काष्ठा kfd_event_रुकोer *event_रुकोers = शून्य;
	दीर्घ समयout = user_समयout_to_jअगरfies(user_समयout_ms);

	event_रुकोers = alloc_event_रुकोers(num_events);
	अगर (!event_रुकोers) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	mutex_lock(&p->event_mutex);

	क्रम (i = 0; i < num_events; i++) अणु
		काष्ठा kfd_event_data event_data;

		अगर (copy_from_user(&event_data, &events[i],
				माप(काष्ठा kfd_event_data))) अणु
			ret = -EFAULT;
			जाओ out_unlock;
		पूर्ण

		ret = init_event_रुकोer_get_status(p, &event_रुकोers[i],
				event_data.event_id);
		अगर (ret)
			जाओ out_unlock;
	पूर्ण

	/* Check condition once. */
	*रुको_result = test_event_condition(all, num_events, event_रुकोers);
	अगर (*रुको_result == KFD_IOC_WAIT_RESULT_COMPLETE) अणु
		ret = copy_संकेतed_event_data(num_events,
					       event_रुकोers, events);
		जाओ out_unlock;
	पूर्ण अन्यथा अगर (WARN_ON(*रुको_result == KFD_IOC_WAIT_RESULT_FAIL)) अणु
		/* This should not happen. Events shouldn't be
		 * destroyed जबतक we're holding the event_mutex
		 */
		जाओ out_unlock;
	पूर्ण

	/* Add to रुको lists अगर we need to रुको. */
	क्रम (i = 0; i < num_events; i++)
		init_event_रुकोer_add_to_रुकोlist(&event_रुकोers[i]);

	mutex_unlock(&p->event_mutex);

	जबतक (true) अणु
		अगर (fatal_संकेत_pending(current)) अणु
			ret = -EINTR;
			अवरोध;
		पूर्ण

		अगर (संकेत_pending(current)) अणु
			/*
			 * This is wrong when a nonzero, non-infinite समयout
			 * is specअगरied. We need to use
			 * ERESTARTSYS_RESTARTBLOCK, but काष्ठा restart_block
			 * contains a जोड़ with data क्रम each user and it's
			 * in generic kernel code that I करोn't want to
			 * touch yet.
			 */
			ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण

		/* Set task state to पूर्णांकerruptible sleep beक्रमe
		 * checking wake-up conditions. A concurrent wake-up
		 * will put the task back पूर्णांकo runnable state. In that
		 * हाल schedule_समयout will not put the task to
		 * sleep and we'll get a chance to re-check the
		 * updated conditions almost immediately. Otherwise,
		 * this race condition would lead to a soft hang or a
		 * very दीर्घ sleep.
		 */
		set_current_state(TASK_INTERRUPTIBLE);

		*रुको_result = test_event_condition(all, num_events,
						    event_रुकोers);
		अगर (*रुको_result != KFD_IOC_WAIT_RESULT_TIMEOUT)
			अवरोध;

		अगर (समयout <= 0)
			अवरोध;

		समयout = schedule_समयout(समयout);
	पूर्ण
	__set_current_state(TASK_RUNNING);

	/* copy_संकेतed_event_data may sleep. So this has to happen
	 * after the task state is set back to RUNNING.
	 */
	अगर (!ret && *रुको_result == KFD_IOC_WAIT_RESULT_COMPLETE)
		ret = copy_संकेतed_event_data(num_events,
					       event_रुकोers, events);

	mutex_lock(&p->event_mutex);
out_unlock:
	मुक्त_रुकोers(num_events, event_रुकोers);
	mutex_unlock(&p->event_mutex);
out:
	अगर (ret)
		*रुको_result = KFD_IOC_WAIT_RESULT_FAIL;
	अन्यथा अगर (*रुको_result == KFD_IOC_WAIT_RESULT_FAIL)
		ret = -EIO;

	वापस ret;
पूर्ण

पूर्णांक kfd_event_mmap(काष्ठा kfd_process *p, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ pfn;
	काष्ठा kfd_संकेत_page *page;
	पूर्णांक ret;

	/* check required size करोesn't exceed the allocated size */
	अगर (get_order(KFD_SIGNAL_EVENT_LIMIT * 8) <
			get_order(vma->vm_end - vma->vm_start)) अणु
		pr_err("Event page mmap requested illegal size\n");
		वापस -EINVAL;
	पूर्ण

	page = p->संकेत_page;
	अगर (!page) अणु
		/* Probably KFD bug, but mmap is user-accessible. */
		pr_debug("Signal page could not be found\n");
		वापस -EINVAL;
	पूर्ण

	pfn = __pa(page->kernel_address);
	pfn >>= PAGE_SHIFT;

	vma->vm_flags |= VM_IO | VM_DONTCOPY | VM_DONTEXPAND | VM_NORESERVE
		       | VM_DONTDUMP | VM_PFNMAP;

	pr_debug("Mapping signal page\n");
	pr_debug("     start user address  == 0x%08lx\n", vma->vm_start);
	pr_debug("     end user address    == 0x%08lx\n", vma->vm_end);
	pr_debug("     pfn                 == 0x%016lX\n", pfn);
	pr_debug("     vm_flags            == 0x%08lX\n", vma->vm_flags);
	pr_debug("     size                == 0x%08lX\n",
			vma->vm_end - vma->vm_start);

	page->user_address = (uपूर्णांक64_t __user *)vma->vm_start;

	/* mapping the page to user process */
	ret = remap_pfn_range(vma, vma->vm_start, pfn,
			vma->vm_end - vma->vm_start, vma->vm_page_prot);
	अगर (!ret)
		p->संकेत_mapped_size = vma->vm_end - vma->vm_start;

	वापस ret;
पूर्ण

/*
 * Assumes that p->event_mutex is held and of course
 * that p is not going away (current or locked).
 */
अटल व्योम lookup_events_by_type_and_संकेत(काष्ठा kfd_process *p,
		पूर्णांक type, व्योम *event_data)
अणु
	काष्ठा kfd_hsa_memory_exception_data *ev_data;
	काष्ठा kfd_event *ev;
	uपूर्णांक32_t id;
	bool send_संकेत = true;

	ev_data = (काष्ठा kfd_hsa_memory_exception_data *) event_data;

	id = KFD_FIRST_NONSIGNAL_EVENT_ID;
	idr_क्रम_each_entry_जारी(&p->event_idr, ev, id)
		अगर (ev->type == type) अणु
			send_संकेत = false;
			dev_dbg(kfd_device,
					"Event found: id %X type %d",
					ev->event_id, ev->type);
			set_event(ev);
			अगर (ev->type == KFD_EVENT_TYPE_MEMORY && ev_data)
				ev->memory_exception_data = *ev_data;
		पूर्ण

	अगर (type == KFD_EVENT_TYPE_MEMORY) अणु
		dev_warn(kfd_device,
			"Sending SIGSEGV to process %d (pasid 0x%x)",
				p->lead_thपढ़ो->pid, p->pasid);
		send_sig(संक_अंश, p->lead_thपढ़ो, 0);
	पूर्ण

	/* Send संक_इति no event of type "type" has been found*/
	अगर (send_संकेत) अणु
		अगर (send_sigterm) अणु
			dev_warn(kfd_device,
				"Sending SIGTERM to process %d (pasid 0x%x)",
					p->lead_thपढ़ो->pid, p->pasid);
			send_sig(संक_इति, p->lead_thपढ़ो, 0);
		पूर्ण अन्यथा अणु
			dev_err(kfd_device,
				"Process %d (pasid 0x%x) got unhandled exception",
				p->lead_thपढ़ो->pid, p->pasid);
		पूर्ण
	पूर्ण
पूर्ण

#अगर_घोषित KFD_SUPPORT_IOMMU_V2
व्योम kfd_संकेत_iommu_event(काष्ठा kfd_dev *dev, u32 pasid,
		अचिन्हित दीर्घ address, bool is_ग_लिखो_requested,
		bool is_execute_requested)
अणु
	काष्ठा kfd_hsa_memory_exception_data memory_exception_data;
	काष्ठा vm_area_काष्ठा *vma;

	/*
	 * Because we are called from arbitrary context (workqueue) as opposed
	 * to process context, kfd_process could attempt to निकास जबतक we are
	 * running so the lookup function increments the process ref count.
	 */
	काष्ठा kfd_process *p = kfd_lookup_process_by_pasid(pasid);
	काष्ठा mm_काष्ठा *mm;

	अगर (!p)
		वापस; /* Presumably process निकासed. */

	/* Take a safe reference to the mm_काष्ठा, which may otherwise
	 * disappear even जबतक the kfd_process is still referenced.
	 */
	mm = get_task_mm(p->lead_thपढ़ो);
	अगर (!mm) अणु
		kfd_unref_process(p);
		वापस; /* Process is निकासing */
	पूर्ण

	स_रखो(&memory_exception_data, 0, माप(memory_exception_data));

	mmap_पढ़ो_lock(mm);
	vma = find_vma(mm, address);

	memory_exception_data.gpu_id = dev->id;
	memory_exception_data.va = address;
	/* Set failure reason */
	memory_exception_data.failure.NotPresent = 1;
	memory_exception_data.failure.NoExecute = 0;
	memory_exception_data.failure.ReadOnly = 0;
	अगर (vma && address >= vma->vm_start) अणु
		memory_exception_data.failure.NotPresent = 0;

		अगर (is_ग_लिखो_requested && !(vma->vm_flags & VM_WRITE))
			memory_exception_data.failure.ReadOnly = 1;
		अन्यथा
			memory_exception_data.failure.ReadOnly = 0;

		अगर (is_execute_requested && !(vma->vm_flags & VM_EXEC))
			memory_exception_data.failure.NoExecute = 1;
		अन्यथा
			memory_exception_data.failure.NoExecute = 0;
	पूर्ण

	mmap_पढ़ो_unlock(mm);
	mmput(mm);

	pr_debug("notpresent %d, noexecute %d, readonly %d\n",
			memory_exception_data.failure.NotPresent,
			memory_exception_data.failure.NoExecute,
			memory_exception_data.failure.ReadOnly);

	/* Workaround on Raven to not समाप्त the process when memory is मुक्तd
	 * beक्रमe IOMMU is able to finish processing all the excessive PPRs
	 */
	अगर (dev->device_info->asic_family != CHIP_RAVEN &&
	    dev->device_info->asic_family != CHIP_RENOIR) अणु
		mutex_lock(&p->event_mutex);

		/* Lookup events by type and संकेत them */
		lookup_events_by_type_and_संकेत(p, KFD_EVENT_TYPE_MEMORY,
				&memory_exception_data);

		mutex_unlock(&p->event_mutex);
	पूर्ण

	kfd_unref_process(p);
पूर्ण
#पूर्ण_अगर /* KFD_SUPPORT_IOMMU_V2 */

व्योम kfd_संकेत_hw_exception_event(u32 pasid)
अणु
	/*
	 * Because we are called from arbitrary context (workqueue) as opposed
	 * to process context, kfd_process could attempt to निकास जबतक we are
	 * running so the lookup function increments the process ref count.
	 */
	काष्ठा kfd_process *p = kfd_lookup_process_by_pasid(pasid);

	अगर (!p)
		वापस; /* Presumably process निकासed. */

	mutex_lock(&p->event_mutex);

	/* Lookup events by type and संकेत them */
	lookup_events_by_type_and_संकेत(p, KFD_EVENT_TYPE_HW_EXCEPTION, शून्य);

	mutex_unlock(&p->event_mutex);
	kfd_unref_process(p);
पूर्ण

व्योम kfd_संकेत_vm_fault_event(काष्ठा kfd_dev *dev, u32 pasid,
				काष्ठा kfd_vm_fault_info *info)
अणु
	काष्ठा kfd_event *ev;
	uपूर्णांक32_t id;
	काष्ठा kfd_process *p = kfd_lookup_process_by_pasid(pasid);
	काष्ठा kfd_hsa_memory_exception_data memory_exception_data;

	अगर (!p)
		वापस; /* Presumably process निकासed. */
	स_रखो(&memory_exception_data, 0, माप(memory_exception_data));
	memory_exception_data.gpu_id = dev->id;
	memory_exception_data.failure.imprecise = true;
	/* Set failure reason */
	अगर (info) अणु
		memory_exception_data.va = (info->page_addr) << PAGE_SHIFT;
		memory_exception_data.failure.NotPresent =
			info->prot_valid ? 1 : 0;
		memory_exception_data.failure.NoExecute =
			info->prot_exec ? 1 : 0;
		memory_exception_data.failure.ReadOnly =
			info->prot_ग_लिखो ? 1 : 0;
		memory_exception_data.failure.imprecise = 0;
	पूर्ण
	mutex_lock(&p->event_mutex);

	id = KFD_FIRST_NONSIGNAL_EVENT_ID;
	idr_क्रम_each_entry_जारी(&p->event_idr, ev, id)
		अगर (ev->type == KFD_EVENT_TYPE_MEMORY) अणु
			ev->memory_exception_data = memory_exception_data;
			set_event(ev);
		पूर्ण

	mutex_unlock(&p->event_mutex);
	kfd_unref_process(p);
पूर्ण

व्योम kfd_संकेत_reset_event(काष्ठा kfd_dev *dev)
अणु
	काष्ठा kfd_hsa_hw_exception_data hw_exception_data;
	काष्ठा kfd_hsa_memory_exception_data memory_exception_data;
	काष्ठा kfd_process *p;
	काष्ठा kfd_event *ev;
	अचिन्हित पूर्णांक temp;
	uपूर्णांक32_t id, idx;
	पूर्णांक reset_cause = atomic_पढ़ो(&dev->sram_ecc_flag) ?
			KFD_HW_EXCEPTION_ECC :
			KFD_HW_EXCEPTION_GPU_HANG;

	/* Whole gpu reset caused by GPU hang and memory is lost */
	स_रखो(&hw_exception_data, 0, माप(hw_exception_data));
	hw_exception_data.gpu_id = dev->id;
	hw_exception_data.memory_lost = 1;
	hw_exception_data.reset_cause = reset_cause;

	स_रखो(&memory_exception_data, 0, माप(memory_exception_data));
	memory_exception_data.ErrorType = KFD_MEM_ERR_SRAM_ECC;
	memory_exception_data.gpu_id = dev->id;
	memory_exception_data.failure.imprecise = true;

	idx = srcu_पढ़ो_lock(&kfd_processes_srcu);
	hash_क्रम_each_rcu(kfd_processes_table, temp, p, kfd_processes) अणु
		mutex_lock(&p->event_mutex);
		id = KFD_FIRST_NONSIGNAL_EVENT_ID;
		idr_क्रम_each_entry_जारी(&p->event_idr, ev, id) अणु
			अगर (ev->type == KFD_EVENT_TYPE_HW_EXCEPTION) अणु
				ev->hw_exception_data = hw_exception_data;
				set_event(ev);
			पूर्ण
			अगर (ev->type == KFD_EVENT_TYPE_MEMORY &&
			    reset_cause == KFD_HW_EXCEPTION_ECC) अणु
				ev->memory_exception_data = memory_exception_data;
				set_event(ev);
			पूर्ण
		पूर्ण
		mutex_unlock(&p->event_mutex);
	पूर्ण
	srcu_पढ़ो_unlock(&kfd_processes_srcu, idx);
पूर्ण
