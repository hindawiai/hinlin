<शैली गुरु>
/*
 * Xen event channels (FIFO-based ABI)
 *
 * Copyright (C) 2013 Citrix Systems R&D ltd.
 *
 * This source code is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * Or, when distributed separately from the Linux kernel or
 * incorporated पूर्णांकo other software packages, subject to the following
 * license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#घोषणा pr_fmt(fmt) "xen:" KBUILD_MODNAME ": " fmt

#समावेश <linux/linkage.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/smp.h>
#समावेश <linux/percpu.h>
#समावेश <linux/cpu.h>

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/sync_bitops.h>
#समावेश <यंत्र/xen/hypercall.h>
#समावेश <यंत्र/xen/hypervisor.h>

#समावेश <xen/xen.h>
#समावेश <xen/xen-ops.h>
#समावेश <xen/events.h>
#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/पूर्णांकerface/event_channel.h>
#समावेश <xen/page.h>

#समावेश "events_internal.h"

#घोषणा EVENT_WORDS_PER_PAGE (XEN_PAGE_SIZE / माप(event_word_t))
#घोषणा MAX_EVENT_ARRAY_PAGES (EVTCHN_FIFO_NR_CHANNELS / EVENT_WORDS_PER_PAGE)

काष्ठा evtchn_fअगरo_queue अणु
	uपूर्णांक32_t head[EVTCHN_FIFO_MAX_QUEUES];
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा evtchn_fअगरo_control_block *, cpu_control_block);
अटल DEFINE_PER_CPU(काष्ठा evtchn_fअगरo_queue, cpu_queue);
अटल event_word_t *event_array[MAX_EVENT_ARRAY_PAGES] __पढ़ो_mostly;
अटल अचिन्हित event_array_pages __पढ़ो_mostly;

/*
 * sync_set_bit() and मित्रs must be अचिन्हित दीर्घ aligned.
 */
#अगर BITS_PER_LONG > 32

#घोषणा BM(w) (अचिन्हित दीर्घ *)((अचिन्हित दीर्घ)w & ~0x7UL)
#घोषणा EVTCHN_FIFO_BIT(b, w) \
    (((अचिन्हित दीर्घ)w & 0x4UL) ? (EVTCHN_FIFO_ ##b + 32) : EVTCHN_FIFO_ ##b)

#अन्यथा

#घोषणा BM(w) ((अचिन्हित दीर्घ *)(w))
#घोषणा EVTCHN_FIFO_BIT(b, w) EVTCHN_FIFO_ ##b

#पूर्ण_अगर

अटल अंतरभूत event_word_t *event_word_from_port(evtchn_port_t port)
अणु
	अचिन्हित i = port / EVENT_WORDS_PER_PAGE;

	वापस event_array[i] + port % EVENT_WORDS_PER_PAGE;
पूर्ण

अटल अचिन्हित evtchn_fअगरo_max_channels(व्योम)
अणु
	वापस EVTCHN_FIFO_NR_CHANNELS;
पूर्ण

अटल अचिन्हित evtchn_fअगरo_nr_channels(व्योम)
अणु
	वापस event_array_pages * EVENT_WORDS_PER_PAGE;
पूर्ण

अटल पूर्णांक init_control_block(पूर्णांक cpu,
                              काष्ठा evtchn_fअगरo_control_block *control_block)
अणु
	काष्ठा evtchn_fअगरo_queue *q = &per_cpu(cpu_queue, cpu);
	काष्ठा evtchn_init_control init_control;
	अचिन्हित पूर्णांक i;

	/* Reset the control block and the local HEADs. */
	clear_page(control_block);
	क्रम (i = 0; i < EVTCHN_FIFO_MAX_QUEUES; i++)
		q->head[i] = 0;

	init_control.control_gfn = virt_to_gfn(control_block);
	init_control.offset      = 0;
	init_control.vcpu        = xen_vcpu_nr(cpu);

	वापस HYPERVISOR_event_channel_op(EVTCHNOP_init_control, &init_control);
पूर्ण

अटल व्योम मुक्त_unused_array_pages(व्योम)
अणु
	अचिन्हित i;

	क्रम (i = event_array_pages; i < MAX_EVENT_ARRAY_PAGES; i++) अणु
		अगर (!event_array[i])
			अवरोध;
		मुक्त_page((अचिन्हित दीर्घ)event_array[i]);
		event_array[i] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम init_array_page(event_word_t *array_page)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < EVENT_WORDS_PER_PAGE; i++)
		array_page[i] = 1 << EVTCHN_FIFO_MASKED;
पूर्ण

अटल पूर्णांक evtchn_fअगरo_setup(evtchn_port_t port)
अणु
	अचिन्हित new_array_pages;
	पूर्णांक ret;

	new_array_pages = port / EVENT_WORDS_PER_PAGE + 1;

	अगर (new_array_pages > MAX_EVENT_ARRAY_PAGES)
		वापस -EINVAL;

	जबतक (event_array_pages < new_array_pages) अणु
		व्योम *array_page;
		काष्ठा evtchn_expand_array expand_array;

		/* Might alपढ़ोy have a page अगर we've resumed. */
		array_page = event_array[event_array_pages];
		अगर (!array_page) अणु
			array_page = (व्योम *)__get_मुक्त_page(GFP_KERNEL);
			अगर (array_page == शून्य) अणु
				ret = -ENOMEM;
				जाओ error;
			पूर्ण
			event_array[event_array_pages] = array_page;
		पूर्ण

		/* Mask all events in this page beक्रमe adding it. */
		init_array_page(array_page);

		expand_array.array_gfn = virt_to_gfn(array_page);

		ret = HYPERVISOR_event_channel_op(EVTCHNOP_expand_array, &expand_array);
		अगर (ret < 0)
			जाओ error;

		event_array_pages++;
	पूर्ण
	वापस 0;

  error:
	अगर (event_array_pages == 0)
		panic("xen: unable to expand event array with initial page (%d)\n", ret);
	अन्यथा
		pr_err("unable to expand event array (%d)\n", ret);
	मुक्त_unused_array_pages();
	वापस ret;
पूर्ण

अटल व्योम evtchn_fअगरo_bind_to_cpu(evtchn_port_t evtchn, अचिन्हित पूर्णांक cpu, 
				    अचिन्हित पूर्णांक old_cpu)
अणु
	/* no-op */
पूर्ण

अटल व्योम evtchn_fअगरo_clear_pending(evtchn_port_t port)
अणु
	event_word_t *word = event_word_from_port(port);
	sync_clear_bit(EVTCHN_FIFO_BIT(PENDING, word), BM(word));
पूर्ण

अटल व्योम evtchn_fअगरo_set_pending(evtchn_port_t port)
अणु
	event_word_t *word = event_word_from_port(port);
	sync_set_bit(EVTCHN_FIFO_BIT(PENDING, word), BM(word));
पूर्ण

अटल bool evtchn_fअगरo_is_pending(evtchn_port_t port)
अणु
	event_word_t *word = event_word_from_port(port);
	वापस sync_test_bit(EVTCHN_FIFO_BIT(PENDING, word), BM(word));
पूर्ण

अटल व्योम evtchn_fअगरo_mask(evtchn_port_t port)
अणु
	event_word_t *word = event_word_from_port(port);
	sync_set_bit(EVTCHN_FIFO_BIT(MASKED, word), BM(word));
पूर्ण

अटल bool evtchn_fअगरo_is_masked(evtchn_port_t port)
अणु
	event_word_t *word = event_word_from_port(port);
	वापस sync_test_bit(EVTCHN_FIFO_BIT(MASKED, word), BM(word));
पूर्ण
/*
 * Clear MASKED अगर not PENDING, spinning अगर BUSY is set.
 * Return true अगर mask was cleared.
 */
अटल bool clear_masked_cond(अस्थिर event_word_t *word)
अणु
	event_word_t new, old, w;

	w = *word;

	करो अणु
		अगर (!(w & (1 << EVTCHN_FIFO_MASKED)))
			वापस true;

		अगर (w & (1 << EVTCHN_FIFO_PENDING))
			वापस false;

		old = w & ~(1 << EVTCHN_FIFO_BUSY);
		new = old & ~(1 << EVTCHN_FIFO_MASKED);
		w = sync_cmpxchg(word, old, new);
	पूर्ण जबतक (w != old);

	वापस true;
पूर्ण

अटल व्योम evtchn_fअगरo_unmask(evtchn_port_t port)
अणु
	event_word_t *word = event_word_from_port(port);

	BUG_ON(!irqs_disabled());

	अगर (!clear_masked_cond(word)) अणु
		काष्ठा evtchn_unmask unmask = अणु .port = port पूर्ण;
		(व्योम)HYPERVISOR_event_channel_op(EVTCHNOP_unmask, &unmask);
	पूर्ण
पूर्ण

अटल uपूर्णांक32_t clear_linked(अस्थिर event_word_t *word)
अणु
	event_word_t new, old, w;

	w = *word;

	करो अणु
		old = w;
		new = (w & ~((1 << EVTCHN_FIFO_LINKED)
			     | EVTCHN_FIFO_LINK_MASK));
	पूर्ण जबतक ((w = sync_cmpxchg(word, old, new)) != old);

	वापस w & EVTCHN_FIFO_LINK_MASK;
पूर्ण

अटल व्योम consume_one_event(अचिन्हित cpu, काष्ठा evtchn_loop_ctrl *ctrl,
			      काष्ठा evtchn_fअगरo_control_block *control_block,
			      अचिन्हित priority, अचिन्हित दीर्घ *पढ़ोy)
अणु
	काष्ठा evtchn_fअगरo_queue *q = &per_cpu(cpu_queue, cpu);
	uपूर्णांक32_t head;
	evtchn_port_t port;
	event_word_t *word;

	head = q->head[priority];

	/*
	 * Reached the tail last समय?  Read the new HEAD from the
	 * control block.
	 */
	अगर (head == 0) अणु
		virt_rmb(); /* Ensure word is up-to-date beक्रमe पढ़ोing head. */
		head = control_block->head[priority];
	पूर्ण

	port = head;
	word = event_word_from_port(port);
	head = clear_linked(word);

	/*
	 * If the link is non-zero, there are more events in the
	 * queue, otherwise the queue is empty.
	 *
	 * If the queue is empty, clear this priority from our local
	 * copy of the पढ़ोy word.
	 */
	अगर (head == 0)
		clear_bit(priority, पढ़ोy);

	अगर (evtchn_fअगरo_is_pending(port) && !evtchn_fअगरo_is_masked(port)) अणु
		अगर (unlikely(!ctrl))
			pr_warn("Dropping pending event for port %u\n", port);
		अन्यथा
			handle_irq_क्रम_port(port, ctrl);
	पूर्ण

	q->head[priority] = head;
पूर्ण

अटल व्योम __evtchn_fअगरo_handle_events(अचिन्हित cpu,
					काष्ठा evtchn_loop_ctrl *ctrl)
अणु
	काष्ठा evtchn_fअगरo_control_block *control_block;
	अचिन्हित दीर्घ पढ़ोy;
	अचिन्हित q;

	control_block = per_cpu(cpu_control_block, cpu);

	पढ़ोy = xchg(&control_block->पढ़ोy, 0);

	जबतक (पढ़ोy) अणु
		q = find_first_bit(&पढ़ोy, EVTCHN_FIFO_MAX_QUEUES);
		consume_one_event(cpu, ctrl, control_block, q, &पढ़ोy);
		पढ़ोy |= xchg(&control_block->पढ़ोy, 0);
	पूर्ण
पूर्ण

अटल व्योम evtchn_fअगरo_handle_events(अचिन्हित cpu,
				      काष्ठा evtchn_loop_ctrl *ctrl)
अणु
	__evtchn_fअगरo_handle_events(cpu, ctrl);
पूर्ण

अटल व्योम evtchn_fअगरo_resume(व्योम)
अणु
	अचिन्हित cpu;

	क्रम_each_possible_cpu(cpu) अणु
		व्योम *control_block = per_cpu(cpu_control_block, cpu);
		पूर्णांक ret;

		अगर (!control_block)
			जारी;

		/*
		 * If this CPU is offline, take the opportunity to
		 * मुक्त the control block जबतक it is not being
		 * used.
		 */
		अगर (!cpu_online(cpu)) अणु
			मुक्त_page((अचिन्हित दीर्घ)control_block);
			per_cpu(cpu_control_block, cpu) = शून्य;
			जारी;
		पूर्ण

		ret = init_control_block(cpu, control_block);
		BUG_ON(ret < 0);
	पूर्ण

	/*
	 * The event array starts out as empty again and is extended
	 * as normal when events are bound.  The existing pages will
	 * be reused.
	 */
	event_array_pages = 0;
पूर्ण

अटल पूर्णांक evtchn_fअगरo_alloc_control_block(अचिन्हित cpu)
अणु
	व्योम *control_block = शून्य;
	पूर्णांक ret = -ENOMEM;

	control_block = (व्योम *)__get_मुक्त_page(GFP_KERNEL);
	अगर (control_block == शून्य)
		जाओ error;

	ret = init_control_block(cpu, control_block);
	अगर (ret < 0)
		जाओ error;

	per_cpu(cpu_control_block, cpu) = control_block;

	वापस 0;

  error:
	मुक्त_page((अचिन्हित दीर्घ)control_block);
	वापस ret;
पूर्ण

अटल पूर्णांक evtchn_fअगरo_percpu_init(अचिन्हित पूर्णांक cpu)
अणु
	अगर (!per_cpu(cpu_control_block, cpu))
		वापस evtchn_fअगरo_alloc_control_block(cpu);
	वापस 0;
पूर्ण

अटल पूर्णांक evtchn_fअगरo_percpu_deinit(अचिन्हित पूर्णांक cpu)
अणु
	__evtchn_fअगरo_handle_events(cpu, शून्य);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा evtchn_ops evtchn_ops_fअगरo = अणु
	.max_channels      = evtchn_fअगरo_max_channels,
	.nr_channels       = evtchn_fअगरo_nr_channels,
	.setup             = evtchn_fअगरo_setup,
	.bind_to_cpu       = evtchn_fअगरo_bind_to_cpu,
	.clear_pending     = evtchn_fअगरo_clear_pending,
	.set_pending       = evtchn_fअगरo_set_pending,
	.is_pending        = evtchn_fअगरo_is_pending,
	.mask              = evtchn_fअगरo_mask,
	.unmask            = evtchn_fअगरo_unmask,
	.handle_events     = evtchn_fअगरo_handle_events,
	.resume            = evtchn_fअगरo_resume,
	.percpu_init       = evtchn_fअगरo_percpu_init,
	.percpu_deinit     = evtchn_fअगरo_percpu_deinit,
पूर्ण;

पूर्णांक __init xen_evtchn_fअगरo_init(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();
	पूर्णांक ret;

	ret = evtchn_fअगरo_alloc_control_block(cpu);
	अगर (ret < 0)
		वापस ret;

	pr_info("Using FIFO-based ABI\n");

	evtchn_ops = &evtchn_ops_fअगरo;

	वापस ret;
पूर्ण
