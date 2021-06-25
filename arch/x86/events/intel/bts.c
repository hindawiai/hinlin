<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * BTS PMU driver क्रम perf
 * Copyright (c) 2013-2014, Intel Corporation.
 */

#अघोषित DEBUG

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/bitops.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>
#समावेश <linux/coredump.h>

#समावेश <linux/sizes.h>
#समावेश <यंत्र/perf_event.h>

#समावेश "../perf_event.h"

काष्ठा bts_ctx अणु
	काष्ठा perf_output_handle	handle;
	काष्ठा debug_store		ds_back;
	पूर्णांक				state;
पूर्ण;

/* BTS context states: */
क्रमागत अणु
	/* no ongoing AUX transactions */
	BTS_STATE_STOPPED = 0,
	/* AUX transaction is on, BTS tracing is disabled */
	BTS_STATE_INACTIVE,
	/* AUX transaction is on, BTS tracing is running */
	BTS_STATE_ACTIVE,
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा bts_ctx, bts_ctx);

#घोषणा BTS_RECORD_SIZE		24
#घोषणा BTS_SAFETY_MARGIN	4080

काष्ठा bts_phys अणु
	काष्ठा page	*page;
	अचिन्हित दीर्घ	size;
	अचिन्हित दीर्घ	offset;
	अचिन्हित दीर्घ	displacement;
पूर्ण;

काष्ठा bts_buffer अणु
	माप_प्रकार		real_size;	/* multiple of BTS_RECORD_SIZE */
	अचिन्हित पूर्णांक	nr_pages;
	अचिन्हित पूर्णांक	nr_bufs;
	अचिन्हित पूर्णांक	cur_buf;
	bool		snapshot;
	local_t		data_size;
	local_t		head;
	अचिन्हित दीर्घ	end;
	व्योम		**data_pages;
	काष्ठा bts_phys	buf[];
पूर्ण;

अटल काष्ठा pmu bts_pmu;

अटल पूर्णांक buf_nr_pages(काष्ठा page *page)
अणु
	अगर (!PagePrivate(page))
		वापस 1;

	वापस 1 << page_निजी(page);
पूर्ण

अटल माप_प्रकार buf_size(काष्ठा page *page)
अणु
	वापस buf_nr_pages(page) * PAGE_SIZE;
पूर्ण

अटल व्योम *
bts_buffer_setup_aux(काष्ठा perf_event *event, व्योम **pages,
		     पूर्णांक nr_pages, bool overग_लिखो)
अणु
	काष्ठा bts_buffer *buf;
	काष्ठा page *page;
	पूर्णांक cpu = event->cpu;
	पूर्णांक node = (cpu == -1) ? cpu : cpu_to_node(cpu);
	अचिन्हित दीर्घ offset;
	माप_प्रकार size = nr_pages << PAGE_SHIFT;
	पूर्णांक pg, nbuf, pad;

	/* count all the high order buffers */
	क्रम (pg = 0, nbuf = 0; pg < nr_pages;) अणु
		page = virt_to_page(pages[pg]);
		pg += buf_nr_pages(page);
		nbuf++;
	पूर्ण

	/*
	 * to aव्योम पूर्णांकerrupts in overग_लिखो mode, only allow one physical
	 */
	अगर (overग_लिखो && nbuf > 1)
		वापस शून्य;

	buf = kzalloc_node(दुरत्व(काष्ठा bts_buffer, buf[nbuf]), GFP_KERNEL, node);
	अगर (!buf)
		वापस शून्य;

	buf->nr_pages = nr_pages;
	buf->nr_bufs = nbuf;
	buf->snapshot = overग_लिखो;
	buf->data_pages = pages;
	buf->real_size = size - size % BTS_RECORD_SIZE;

	क्रम (pg = 0, nbuf = 0, offset = 0, pad = 0; nbuf < buf->nr_bufs; nbuf++) अणु
		अचिन्हित पूर्णांक __nr_pages;

		page = virt_to_page(pages[pg]);
		__nr_pages = buf_nr_pages(page);
		buf->buf[nbuf].page = page;
		buf->buf[nbuf].offset = offset;
		buf->buf[nbuf].displacement = (pad ? BTS_RECORD_SIZE - pad : 0);
		buf->buf[nbuf].size = buf_size(page) - buf->buf[nbuf].displacement;
		pad = buf->buf[nbuf].size % BTS_RECORD_SIZE;
		buf->buf[nbuf].size -= pad;

		pg += __nr_pages;
		offset += __nr_pages << PAGE_SHIFT;
	पूर्ण

	वापस buf;
पूर्ण

अटल व्योम bts_buffer_मुक्त_aux(व्योम *data)
अणु
	kमुक्त(data);
पूर्ण

अटल अचिन्हित दीर्घ bts_buffer_offset(काष्ठा bts_buffer *buf, अचिन्हित पूर्णांक idx)
अणु
	वापस buf->buf[idx].offset + buf->buf[idx].displacement;
पूर्ण

अटल व्योम
bts_config_buffer(काष्ठा bts_buffer *buf)
अणु
	पूर्णांक cpu = raw_smp_processor_id();
	काष्ठा debug_store *ds = per_cpu(cpu_hw_events, cpu).ds;
	काष्ठा bts_phys *phys = &buf->buf[buf->cur_buf];
	अचिन्हित दीर्घ index, thresh = 0, end = phys->size;
	काष्ठा page *page = phys->page;

	index = local_पढ़ो(&buf->head);

	अगर (!buf->snapshot) अणु
		अगर (buf->end < phys->offset + buf_size(page))
			end = buf->end - phys->offset - phys->displacement;

		index -= phys->offset + phys->displacement;

		अगर (end - index > BTS_SAFETY_MARGIN)
			thresh = end - BTS_SAFETY_MARGIN;
		अन्यथा अगर (end - index > BTS_RECORD_SIZE)
			thresh = end - BTS_RECORD_SIZE;
		अन्यथा
			thresh = end;
	पूर्ण

	ds->bts_buffer_base = (u64)(दीर्घ)page_address(page) + phys->displacement;
	ds->bts_index = ds->bts_buffer_base + index;
	ds->bts_असलolute_maximum = ds->bts_buffer_base + end;
	ds->bts_पूर्णांकerrupt_threshold = !buf->snapshot
		? ds->bts_buffer_base + thresh
		: ds->bts_असलolute_maximum + BTS_RECORD_SIZE;
पूर्ण

अटल व्योम bts_buffer_pad_out(काष्ठा bts_phys *phys, अचिन्हित दीर्घ head)
अणु
	अचिन्हित दीर्घ index = head - phys->offset;

	स_रखो(page_address(phys->page) + index, 0, phys->size - index);
पूर्ण

अटल व्योम bts_update(काष्ठा bts_ctx *bts)
अणु
	पूर्णांक cpu = raw_smp_processor_id();
	काष्ठा debug_store *ds = per_cpu(cpu_hw_events, cpu).ds;
	काष्ठा bts_buffer *buf = perf_get_aux(&bts->handle);
	अचिन्हित दीर्घ index = ds->bts_index - ds->bts_buffer_base, old, head;

	अगर (!buf)
		वापस;

	head = index + bts_buffer_offset(buf, buf->cur_buf);
	old = local_xchg(&buf->head, head);

	अगर (!buf->snapshot) अणु
		अगर (old == head)
			वापस;

		अगर (ds->bts_index >= ds->bts_असलolute_maximum)
			perf_aux_output_flag(&bts->handle,
			                     PERF_AUX_FLAG_TRUNCATED);

		/*
		 * old and head are always in the same physical buffer, so we
		 * can subtract them to get the data size.
		 */
		local_add(head - old, &buf->data_size);
	पूर्ण अन्यथा अणु
		local_set(&buf->data_size, head);
	पूर्ण
पूर्ण

अटल पूर्णांक
bts_buffer_reset(काष्ठा bts_buffer *buf, काष्ठा perf_output_handle *handle);

/*
 * Ordering PMU callbacks wrt themselves and the PMI is करोne by means
 * of bts::state, which:
 *  - is set when bts::handle::event is valid, that is, between
 *    perf_aux_output_begin() and perf_aux_output_end();
 *  - is zero otherwise;
 *  - is ordered against bts::handle::event with a compiler barrier.
 */

अटल व्योम __bts_event_start(काष्ठा perf_event *event)
अणु
	काष्ठा bts_ctx *bts = this_cpu_ptr(&bts_ctx);
	काष्ठा bts_buffer *buf = perf_get_aux(&bts->handle);
	u64 config = 0;

	अगर (!buf->snapshot)
		config |= ARCH_PERFMON_EVENTSEL_INT;
	अगर (!event->attr.exclude_kernel)
		config |= ARCH_PERFMON_EVENTSEL_OS;
	अगर (!event->attr.exclude_user)
		config |= ARCH_PERFMON_EVENTSEL_USR;

	bts_config_buffer(buf);

	/*
	 * local barrier to make sure that ds configuration made it
	 * beक्रमe we enable BTS and bts::state goes ACTIVE
	 */
	wmb();

	/* INACTIVE/STOPPED -> ACTIVE */
	WRITE_ONCE(bts->state, BTS_STATE_ACTIVE);

	पूर्णांकel_pmu_enable_bts(config);

पूर्ण

अटल व्योम bts_event_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा bts_ctx *bts = this_cpu_ptr(&bts_ctx);
	काष्ठा bts_buffer *buf;

	buf = perf_aux_output_begin(&bts->handle, event);
	अगर (!buf)
		जाओ fail_stop;

	अगर (bts_buffer_reset(buf, &bts->handle))
		जाओ fail_end_stop;

	bts->ds_back.bts_buffer_base = cpuc->ds->bts_buffer_base;
	bts->ds_back.bts_असलolute_maximum = cpuc->ds->bts_असलolute_maximum;
	bts->ds_back.bts_पूर्णांकerrupt_threshold = cpuc->ds->bts_पूर्णांकerrupt_threshold;

	perf_event_itrace_started(event);
	event->hw.state = 0;

	__bts_event_start(event);

	वापस;

fail_end_stop:
	perf_aux_output_end(&bts->handle, 0);

fail_stop:
	event->hw.state = PERF_HES_STOPPED;
पूर्ण

अटल व्योम __bts_event_stop(काष्ठा perf_event *event, पूर्णांक state)
अणु
	काष्ठा bts_ctx *bts = this_cpu_ptr(&bts_ctx);

	/* ACTIVE -> INACTIVE(PMI)/STOPPED(->stop()) */
	WRITE_ONCE(bts->state, state);

	/*
	 * No extra synchronization is mandated by the करोcumentation to have
	 * BTS data stores globally visible.
	 */
	पूर्णांकel_pmu_disable_bts();
पूर्ण

अटल व्योम bts_event_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा bts_ctx *bts = this_cpu_ptr(&bts_ctx);
	काष्ठा bts_buffer *buf = शून्य;
	पूर्णांक state = READ_ONCE(bts->state);

	अगर (state == BTS_STATE_ACTIVE)
		__bts_event_stop(event, BTS_STATE_STOPPED);

	अगर (state != BTS_STATE_STOPPED)
		buf = perf_get_aux(&bts->handle);

	event->hw.state |= PERF_HES_STOPPED;

	अगर (flags & PERF_EF_UPDATE) अणु
		bts_update(bts);

		अगर (buf) अणु
			अगर (buf->snapshot)
				bts->handle.head =
					local_xchg(&buf->data_size,
						   buf->nr_pages << PAGE_SHIFT);
			perf_aux_output_end(&bts->handle,
			                    local_xchg(&buf->data_size, 0));
		पूर्ण

		cpuc->ds->bts_index = bts->ds_back.bts_buffer_base;
		cpuc->ds->bts_buffer_base = bts->ds_back.bts_buffer_base;
		cpuc->ds->bts_असलolute_maximum = bts->ds_back.bts_असलolute_maximum;
		cpuc->ds->bts_पूर्णांकerrupt_threshold = bts->ds_back.bts_पूर्णांकerrupt_threshold;
	पूर्ण
पूर्ण

व्योम पूर्णांकel_bts_enable_local(व्योम)
अणु
	काष्ठा bts_ctx *bts = this_cpu_ptr(&bts_ctx);
	पूर्णांक state = READ_ONCE(bts->state);

	/*
	 * Here we transition from INACTIVE to ACTIVE;
	 * अगर we instead are STOPPED from the पूर्णांकerrupt handler,
	 * stay that way. Can't be ACTIVE here though.
	 */
	अगर (WARN_ON_ONCE(state == BTS_STATE_ACTIVE))
		वापस;

	अगर (state == BTS_STATE_STOPPED)
		वापस;

	अगर (bts->handle.event)
		__bts_event_start(bts->handle.event);
पूर्ण

व्योम पूर्णांकel_bts_disable_local(व्योम)
अणु
	काष्ठा bts_ctx *bts = this_cpu_ptr(&bts_ctx);

	/*
	 * Here we transition from ACTIVE to INACTIVE;
	 * करो nothing क्रम STOPPED or INACTIVE.
	 */
	अगर (READ_ONCE(bts->state) != BTS_STATE_ACTIVE)
		वापस;

	अगर (bts->handle.event)
		__bts_event_stop(bts->handle.event, BTS_STATE_INACTIVE);
पूर्ण

अटल पूर्णांक
bts_buffer_reset(काष्ठा bts_buffer *buf, काष्ठा perf_output_handle *handle)
अणु
	अचिन्हित दीर्घ head, space, next_space, pad, gap, skip, wakeup;
	अचिन्हित पूर्णांक next_buf;
	काष्ठा bts_phys *phys, *next_phys;
	पूर्णांक ret;

	अगर (buf->snapshot)
		वापस 0;

	head = handle->head & ((buf->nr_pages << PAGE_SHIFT) - 1);

	phys = &buf->buf[buf->cur_buf];
	space = phys->offset + phys->displacement + phys->size - head;
	pad = space;
	अगर (space > handle->size) अणु
		space = handle->size;
		space -= space % BTS_RECORD_SIZE;
	पूर्ण
	अगर (space <= BTS_SAFETY_MARGIN) अणु
		/* See अगर next phys buffer has more space */
		next_buf = buf->cur_buf + 1;
		अगर (next_buf >= buf->nr_bufs)
			next_buf = 0;
		next_phys = &buf->buf[next_buf];
		gap = buf_size(phys->page) - phys->displacement - phys->size +
		      next_phys->displacement;
		skip = pad + gap;
		अगर (handle->size >= skip) अणु
			next_space = next_phys->size;
			अगर (next_space + skip > handle->size) अणु
				next_space = handle->size - skip;
				next_space -= next_space % BTS_RECORD_SIZE;
			पूर्ण
			अगर (next_space > space || !space) अणु
				अगर (pad)
					bts_buffer_pad_out(phys, head);
				ret = perf_aux_output_skip(handle, skip);
				अगर (ret)
					वापस ret;
				/* Advance to next phys buffer */
				phys = next_phys;
				space = next_space;
				head = phys->offset + phys->displacement;
				/*
				 * After this, cur_buf and head won't match ds
				 * anymore, so we must not be racing with
				 * bts_update().
				 */
				buf->cur_buf = next_buf;
				local_set(&buf->head, head);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Don't go far beyond wakeup watermark */
	wakeup = BTS_SAFETY_MARGIN + BTS_RECORD_SIZE + handle->wakeup -
		 handle->head;
	अगर (space > wakeup) अणु
		space = wakeup;
		space -= space % BTS_RECORD_SIZE;
	पूर्ण

	buf->end = head + space;

	/*
	 * If we have no space, the lost notअगरication would have been sent when
	 * we hit असलolute_maximum - see bts_update()
	 */
	अगर (!space)
		वापस -ENOSPC;

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_bts_पूर्णांकerrupt(व्योम)
अणु
	काष्ठा debug_store *ds = this_cpu_ptr(&cpu_hw_events)->ds;
	काष्ठा bts_ctx *bts = this_cpu_ptr(&bts_ctx);
	काष्ठा perf_event *event = bts->handle.event;
	काष्ठा bts_buffer *buf;
	s64 old_head;
	पूर्णांक err = -ENOSPC, handled = 0;

	/*
	 * The only surefire way of knowing अगर this NMI is ours is by checking
	 * the ग_लिखो ptr against the PMI threshold.
	 */
	अगर (ds && (ds->bts_index >= ds->bts_पूर्णांकerrupt_threshold))
		handled = 1;

	/*
	 * this is wrapped in पूर्णांकel_bts_enable_local/पूर्णांकel_bts_disable_local,
	 * so we can only be INACTIVE or STOPPED
	 */
	अगर (READ_ONCE(bts->state) == BTS_STATE_STOPPED)
		वापस handled;

	buf = perf_get_aux(&bts->handle);
	अगर (!buf)
		वापस handled;

	/*
	 * Skip snapshot counters: they करोn't use the पूर्णांकerrupt, but
	 * there's no other way of telling, because the poपूर्णांकer will
	 * keep moving
	 */
	अगर (buf->snapshot)
		वापस 0;

	old_head = local_पढ़ो(&buf->head);
	bts_update(bts);

	/* no new data */
	अगर (old_head == local_पढ़ो(&buf->head))
		वापस handled;

	perf_aux_output_end(&bts->handle, local_xchg(&buf->data_size, 0));

	buf = perf_aux_output_begin(&bts->handle, event);
	अगर (buf)
		err = bts_buffer_reset(buf, &bts->handle);

	अगर (err) अणु
		WRITE_ONCE(bts->state, BTS_STATE_STOPPED);

		अगर (buf) अणु
			/*
			 * BTS_STATE_STOPPED should be visible beक्रमe
			 * cleared handle::event
			 */
			barrier();
			perf_aux_output_end(&bts->handle, 0);
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम bts_event_del(काष्ठा perf_event *event, पूर्णांक mode)
अणु
	bts_event_stop(event, PERF_EF_UPDATE);
पूर्ण

अटल पूर्णांक bts_event_add(काष्ठा perf_event *event, पूर्णांक mode)
अणु
	काष्ठा bts_ctx *bts = this_cpu_ptr(&bts_ctx);
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा hw_perf_event *hwc = &event->hw;

	event->hw.state = PERF_HES_STOPPED;

	अगर (test_bit(INTEL_PMC_IDX_FIXED_BTS, cpuc->active_mask))
		वापस -EBUSY;

	अगर (bts->handle.event)
		वापस -EBUSY;

	अगर (mode & PERF_EF_START) अणु
		bts_event_start(event, 0);
		अगर (hwc->state & PERF_HES_STOPPED)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bts_event_destroy(काष्ठा perf_event *event)
अणु
	x86_release_hardware();
	x86_del_exclusive(x86_lbr_exclusive_bts);
पूर्ण

अटल पूर्णांक bts_event_init(काष्ठा perf_event *event)
अणु
	पूर्णांक ret;

	अगर (event->attr.type != bts_pmu.type)
		वापस -ENOENT;

	/*
	 * BTS leaks kernel addresses even when CPL0 tracing is
	 * disabled, so disallow पूर्णांकel_bts driver क्रम unprivileged
	 * users on paranoid प्रणालीs since it provides trace data
	 * to the user in a zero-copy fashion.
	 *
	 * Note that the शेष paranoia setting permits unprivileged
	 * users to profile the kernel.
	 */
	अगर (event->attr.exclude_kernel) अणु
		ret = perf_allow_kernel(&event->attr);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (x86_add_exclusive(x86_lbr_exclusive_bts))
		वापस -EBUSY;

	ret = x86_reserve_hardware();
	अगर (ret) अणु
		x86_del_exclusive(x86_lbr_exclusive_bts);
		वापस ret;
	पूर्ण

	event->destroy = bts_event_destroy;

	वापस 0;
पूर्ण

अटल व्योम bts_event_पढ़ो(काष्ठा perf_event *event)
अणु
पूर्ण

अटल __init पूर्णांक bts_init(व्योम)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_DTES64) || !x86_pmu.bts)
		वापस -ENODEV;

	अगर (boot_cpu_has(X86_FEATURE_PTI)) अणु
		/*
		 * BTS hardware ग_लिखोs through a भव memory map we must
		 * either use the kernel physical map, or the user mapping of
		 * the AUX buffer.
		 *
		 * However, since this driver supports per-CPU and per-task inherit
		 * we cannot use the user mapping since it will not be available
		 * अगर we're not running the owning process.
		 *
		 * With PTI we can't use the kernel map either, because its not
		 * there when we run userspace.
		 *
		 * For now, disable this driver when using PTI.
		 */
		वापस -ENODEV;
	पूर्ण

	bts_pmu.capabilities	= PERF_PMU_CAP_AUX_NO_SG | PERF_PMU_CAP_ITRACE |
				  PERF_PMU_CAP_EXCLUSIVE;
	bts_pmu.task_ctx_nr	= perf_sw_context;
	bts_pmu.event_init	= bts_event_init;
	bts_pmu.add		= bts_event_add;
	bts_pmu.del		= bts_event_del;
	bts_pmu.start		= bts_event_start;
	bts_pmu.stop		= bts_event_stop;
	bts_pmu.पढ़ो		= bts_event_पढ़ो;
	bts_pmu.setup_aux	= bts_buffer_setup_aux;
	bts_pmu.मुक्त_aux	= bts_buffer_मुक्त_aux;

	वापस perf_pmu_रेजिस्टर(&bts_pmu, "intel_bts", -1);
पूर्ण
arch_initcall(bts_init);
