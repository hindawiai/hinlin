<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This driver enables Trace Buffer Extension (TRBE) as a per-cpu coresight
 * sink device could then pair with an appropriate per-cpu coresight source
 * device (ETE) thus generating required trace data. Trace can be enabled
 * via the perf framework.
 *
 * The AUX buffer handling is inspired from Arm SPE PMU driver.
 *
 * Copyright (C) 2020 ARM Ltd.
 *
 * Author: Anshuman Khandual <anshuman.khandual@arm.com>
 */
#घोषणा DRVNAME "arm_trbe"

#घोषणा pr_fmt(fmt) DRVNAME ": " fmt

#समावेश <यंत्र/barrier.h>
#समावेश "coresight-trbe.h"

#घोषणा PERF_IDX2OFF(idx, buf) ((idx) % ((buf)->nr_pages << PAGE_SHIFT))

/*
 * A padding packet that will help the user space tools
 * in skipping relevant sections in the captured trace
 * data which could not be decoded. TRBE करोesn't support
 * क्रमmatting the trace data, unlike the legacy CoreSight
 * sinks and thus we use ETE trace packets to pad the
 * sections of the buffer.
 */
#घोषणा ETE_IGNORE_PACKET		0x70

/*
 * Minimum amount of meaningful trace will contain:
 * A-Sync, Trace Info, Trace On, Address, Atom.
 * This is about 44bytes of ETE trace. To be on
 * the safer side, we assume 64bytes is the minimum
 * space required क्रम a meaningful session, beक्रमe
 * we hit a "WRAP" event.
 */
#घोषणा TRBE_TRACE_MIN_BUF_SIZE		64

क्रमागत trbe_fault_action अणु
	TRBE_FAULT_ACT_WRAP,
	TRBE_FAULT_ACT_SPURIOUS,
	TRBE_FAULT_ACT_FATAL,
पूर्ण;

काष्ठा trbe_buf अणु
	/*
	 * Even though trbe_base represents vmap()
	 * mapped allocated buffer's start address,
	 * it's being as अचिन्हित दीर्घ क्रम various
	 * arithmetic and comparision operations &
	 * also to be consistent with trbe_ग_लिखो &
	 * trbe_limit sibling poपूर्णांकers.
	 */
	अचिन्हित दीर्घ trbe_base;
	अचिन्हित दीर्घ trbe_limit;
	अचिन्हित दीर्घ trbe_ग_लिखो;
	पूर्णांक nr_pages;
	व्योम **pages;
	bool snapshot;
	काष्ठा trbe_cpudata *cpudata;
पूर्ण;

काष्ठा trbe_cpudata अणु
	bool trbe_flag;
	u64 trbe_align;
	पूर्णांक cpu;
	क्रमागत cs_mode mode;
	काष्ठा trbe_buf *buf;
	काष्ठा trbe_drvdata *drvdata;
पूर्ण;

काष्ठा trbe_drvdata अणु
	काष्ठा trbe_cpudata __percpu *cpudata;
	काष्ठा perf_output_handle * __percpu *handle;
	काष्ठा hlist_node hotplug_node;
	पूर्णांक irq;
	cpumask_t supported_cpus;
	क्रमागत cpuhp_state trbe_online;
	काष्ठा platक्रमm_device *pdev;
पूर्ण;

अटल पूर्णांक trbe_alloc_node(काष्ठा perf_event *event)
अणु
	अगर (event->cpu == -1)
		वापस NUMA_NO_NODE;
	वापस cpu_to_node(event->cpu);
पूर्ण

अटल व्योम trbe_drain_buffer(व्योम)
अणु
	tsb_csync();
	dsb(nsh);
पूर्ण

अटल व्योम trbe_drain_and_disable_local(व्योम)
अणु
	u64 trblimitr = पढ़ो_sysreg_s(SYS_TRBLIMITR_EL1);

	trbe_drain_buffer();

	/*
	 * Disable the TRBE without clearing LIMITPTR which
	 * might be required क्रम fetching the buffer limits.
	 */
	trblimitr &= ~TRBLIMITR_ENABLE;
	ग_लिखो_sysreg_s(trblimitr, SYS_TRBLIMITR_EL1);
	isb();
पूर्ण

अटल व्योम trbe_reset_local(व्योम)
अणु
	trbe_drain_and_disable_local();
	ग_लिखो_sysreg_s(0, SYS_TRBLIMITR_EL1);
	ग_लिखो_sysreg_s(0, SYS_TRBPTR_EL1);
	ग_लिखो_sysreg_s(0, SYS_TRBBASER_EL1);
	ग_लिखो_sysreg_s(0, SYS_TRBSR_EL1);
पूर्ण

अटल व्योम trbe_stop_and_truncate_event(काष्ठा perf_output_handle *handle)
अणु
	काष्ठा trbe_buf *buf = eपंचांग_perf_sink_config(handle);

	/*
	 * We cannot proceed with the buffer collection and we
	 * करो not have any data क्रम the current session. The
	 * eपंचांग_perf driver expects to बंद out the aux_buffer
	 * at event_stop(). So disable the TRBE here and leave
	 * the update_buffer() to वापस a 0 size.
	 */
	trbe_drain_and_disable_local();
	perf_aux_output_flag(handle, PERF_AUX_FLAG_TRUNCATED);
	*this_cpu_ptr(buf->cpudata->drvdata->handle) = शून्य;
पूर्ण

/*
 * TRBE Buffer Management
 *
 * The TRBE buffer spans from the base poपूर्णांकer till the limit poपूर्णांकer. When enabled,
 * it starts writing trace data from the ग_लिखो poपूर्णांकer onward till the limit poपूर्णांकer.
 * When the ग_लिखो poपूर्णांकer reaches the address just beक्रमe the limit poपूर्णांकer, it माला_लो
 * wrapped around again to the base poपूर्णांकer. This is called a TRBE wrap event, which
 * generates a मुख्यtenance पूर्णांकerrupt when operated in WRAP or FILL mode. This driver
 * uses FILL mode, where the TRBE stops the trace collection at wrap event. The IRQ
 * handler updates the AUX buffer and re-enables the TRBE with updated WRITE and
 * LIMIT poपूर्णांकers.
 *
 *	Wrap around with an IRQ
 *	------ < ------ < ------- < ----- < -----
 *	|					|
 *	------ > ------ > ------- > ----- > -----
 *
 *	+---------------+-----------------------+
 *	|		|			|
 *	+---------------+-----------------------+
 *	Base Poपूर्णांकer	Write Poपूर्णांकer		Limit Poपूर्णांकer
 *
 * The base and limit poपूर्णांकers always needs to be PAGE_SIZE aligned. But the ग_लिखो
 * poपूर्णांकer can be aligned to the implementation defined TRBE trace buffer alignment
 * as captured in trbe_cpudata->trbe_align.
 *
 *
 *		head		tail		wakeup
 *	+---------------------------------------+----- ~ ~ ------
 *	|$$$$$$$|################|$$$$$$$$$$$$$$|		|
 *	+---------------------------------------+----- ~ ~ ------
 *	Base Poपूर्णांकer	Write Poपूर्णांकer		Limit Poपूर्णांकer
 *
 * The perf_output_handle indices (head, tail, wakeup) are monotonically increasing
 * values which tracks all the driver ग_लिखोs and user पढ़ोs from the perf auxiliary
 * buffer. Generally [head..tail] is the area where the driver can ग_लिखो पूर्णांकo unless
 * the wakeup is behind the tail. Enabled TRBE buffer span needs to be adjusted and
 * configured depending on the perf_output_handle indices, so that the driver करोes
 * not override पूर्णांकo areas in the perf auxiliary buffer which is being or yet to be
 * consumed from the user space. The enabled TRBE buffer area is a moving subset of
 * the allocated perf auxiliary buffer.
 */
अटल व्योम trbe_pad_buf(काष्ठा perf_output_handle *handle, पूर्णांक len)
अणु
	काष्ठा trbe_buf *buf = eपंचांग_perf_sink_config(handle);
	u64 head = PERF_IDX2OFF(handle->head, buf);

	स_रखो((व्योम *)buf->trbe_base + head, ETE_IGNORE_PACKET, len);
	अगर (!buf->snapshot)
		perf_aux_output_skip(handle, len);
पूर्ण

अटल अचिन्हित दीर्घ trbe_snapshot_offset(काष्ठा perf_output_handle *handle)
अणु
	काष्ठा trbe_buf *buf = eपंचांग_perf_sink_config(handle);

	/*
	 * The ETE trace has alignment synchronization packets allowing
	 * the decoder to reset in हाल of an overflow or corruption.
	 * So we can use the entire buffer क्रम the snapshot mode.
	 */
	वापस buf->nr_pages * PAGE_SIZE;
पूर्ण

/*
 * TRBE Limit Calculation
 *
 * The following markers are used to illustrate various TRBE buffer situations.
 *
 * $$$$ - Data area, unconsumed captured trace data, not to be overridden
 * #### - Free area, enabled, trace will be written
 * %%%% - Free area, disabled, trace will not be written
 * ==== - Free area, padded with ETE_IGNORE_PACKET, trace will be skipped
 */
अटल अचिन्हित दीर्घ __trbe_normal_offset(काष्ठा perf_output_handle *handle)
अणु
	काष्ठा trbe_buf *buf = eपंचांग_perf_sink_config(handle);
	काष्ठा trbe_cpudata *cpudata = buf->cpudata;
	स्थिर u64 bufsize = buf->nr_pages * PAGE_SIZE;
	u64 limit = bufsize;
	u64 head, tail, wakeup;

	head = PERF_IDX2OFF(handle->head, buf);

	/*
	 *		head
	 *	------->|
	 *	|
	 *	head	TRBE align	tail
	 * +----|-------|---------------|-------+
	 * |$$$$|=======|###############|$$$$$$$|
	 * +----|-------|---------------|-------+
	 * trbe_base				trbe_base + nr_pages
	 *
	 * Perf aux buffer output head position can be misaligned depending on
	 * various factors including user space पढ़ोs. In हाल misaligned, head
	 * needs to be aligned beक्रमe TRBE can be configured. Pad the alignment
	 * gap with ETE_IGNORE_PACKET bytes that will be ignored by user tools
	 * and skip this section thus advancing the head.
	 */
	अगर (!IS_ALIGNED(head, cpudata->trbe_align)) अणु
		अचिन्हित दीर्घ delta = roundup(head, cpudata->trbe_align) - head;

		delta = min(delta, handle->size);
		trbe_pad_buf(handle, delta);
		head = PERF_IDX2OFF(handle->head, buf);
	पूर्ण

	/*
	 *	head = tail (size = 0)
	 * +----|-------------------------------+
	 * |$$$$|$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$	|
	 * +----|-------------------------------+
	 * trbe_base				trbe_base + nr_pages
	 *
	 * Perf aux buffer करोes not have any space क्रम the driver to ग_लिखो पूर्णांकo.
	 * Just communicate trace truncation event to the user space by marking
	 * it with PERF_AUX_FLAG_TRUNCATED.
	 */
	अगर (!handle->size) अणु
		perf_aux_output_flag(handle, PERF_AUX_FLAG_TRUNCATED);
		वापस 0;
	पूर्ण

	/* Compute the tail and wakeup indices now that we've aligned head */
	tail = PERF_IDX2OFF(handle->head + handle->size, buf);
	wakeup = PERF_IDX2OFF(handle->wakeup, buf);

	/*
	 * Lets calculate the buffer area which TRBE could ग_लिखो पूर्णांकo. There
	 * are three possible scenarios here. Limit needs to be aligned with
	 * PAGE_SIZE per the TRBE requirement. Always aव्योम clobbering the
	 * unconsumed data.
	 *
	 * 1) head < tail
	 *
	 *	head			tail
	 * +----|-----------------------|-------+
	 * |$$$$|#######################|$$$$$$$|
	 * +----|-----------------------|-------+
	 * trbe_base			limit	trbe_base + nr_pages
	 *
	 * TRBE could ग_लिखो पूर्णांकo [head..tail] area. Unless the tail is right at
	 * the end of the buffer, neither an wrap around nor an IRQ is expected
	 * जबतक being enabled.
	 *
	 * 2) head == tail
	 *
	 *	head = tail (size > 0)
	 * +----|-------------------------------+
	 * |%%%%|###############################|
	 * +----|-------------------------------+
	 * trbe_base				limit = trbe_base + nr_pages
	 *
	 * TRBE should just ग_लिखो पूर्णांकo [head..base + nr_pages] area even though
	 * the entire buffer is empty. Reason being, when the trace reaches the
	 * end of the buffer, it will just wrap around with an IRQ giving an
	 * opportunity to reconfigure the buffer.
	 *
	 * 3) tail < head
	 *
	 *	tail			head
	 * +----|-----------------------|-------+
	 * |%%%%|$$$$$$$$$$$$$$$$$$$$$$$|#######|
	 * +----|-----------------------|-------+
	 * trbe_base				limit = trbe_base + nr_pages
	 *
	 * TRBE should just ग_लिखो पूर्णांकo [head..base + nr_pages] area even though
	 * the [trbe_base..tail] is also empty. Reason being, when the trace
	 * reaches the end of the buffer, it will just wrap around with an IRQ
	 * giving an opportunity to reconfigure the buffer.
	 */
	अगर (head < tail)
		limit = round_करोwn(tail, PAGE_SIZE);

	/*
	 * Wakeup may be arbitrarily far पूर्णांकo the future. If it's not in the
	 * current generation, either we'll wrap before hitting it, or it's
	 * in the past and has been handled alपढ़ोy.
	 *
	 * If there's a wakeup beक्रमe we wrap, arrange to be woken up by the
	 * page boundary following it. Keep the tail boundary अगर that's lower.
	 *
	 *	head		wakeup	tail
	 * +----|---------------|-------|-------+
	 * |$$$$|###############|%%%%%%%|$$$$$$$|
	 * +----|---------------|-------|-------+
	 * trbe_base		limit		trbe_base + nr_pages
	 */
	अगर (handle->wakeup < (handle->head + handle->size) && head <= wakeup)
		limit = min(limit, round_up(wakeup, PAGE_SIZE));

	/*
	 * There are two situation when this can happen i.e limit is beक्रमe
	 * the head and hence TRBE cannot be configured.
	 *
	 * 1) head < tail (aligned करोwn with PAGE_SIZE) and also they are both
	 * within the same PAGE size range.
	 *
	 *			PAGE_SIZE
	 *		|----------------------|
	 *
	 *		limit	head	tail
	 * +------------|------|--------|-------+
	 * |$$$$$$$$$$$$$$$$$$$|========|$$$$$$$|
	 * +------------|------|--------|-------+
	 * trbe_base				trbe_base + nr_pages
	 *
	 * 2) head < wakeup (aligned up with PAGE_SIZE) < tail and also both
	 * head and wakeup are within same PAGE size range.
	 *
	 *		PAGE_SIZE
	 *	|----------------------|
	 *
	 *	limit	head	wakeup  tail
	 * +----|------|-------|--------|-------+
	 * |$$$$$$$$$$$|=======|========|$$$$$$$|
	 * +----|------|-------|--------|-------+
	 * trbe_base				trbe_base + nr_pages
	 */
	अगर (limit > head)
		वापस limit;

	trbe_pad_buf(handle, handle->size);
	perf_aux_output_flag(handle, PERF_AUX_FLAG_TRUNCATED);
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ trbe_normal_offset(काष्ठा perf_output_handle *handle)
अणु
	काष्ठा trbe_buf *buf = perf_get_aux(handle);
	u64 limit = __trbe_normal_offset(handle);
	u64 head = PERF_IDX2OFF(handle->head, buf);

	/*
	 * If the head is too बंद to the limit and we करोn't
	 * have space क्रम a meaningful run, we rather pad it
	 * and start fresh.
	 */
	अगर (limit && (limit - head < TRBE_TRACE_MIN_BUF_SIZE)) अणु
		trbe_pad_buf(handle, limit - head);
		limit = __trbe_normal_offset(handle);
	पूर्ण
	वापस limit;
पूर्ण

अटल अचिन्हित दीर्घ compute_trbe_buffer_limit(काष्ठा perf_output_handle *handle)
अणु
	काष्ठा trbe_buf *buf = eपंचांग_perf_sink_config(handle);
	अचिन्हित दीर्घ offset;

	अगर (buf->snapshot)
		offset = trbe_snapshot_offset(handle);
	अन्यथा
		offset = trbe_normal_offset(handle);
	वापस buf->trbe_base + offset;
पूर्ण

अटल व्योम clr_trbe_status(व्योम)
अणु
	u64 trbsr = पढ़ो_sysreg_s(SYS_TRBSR_EL1);

	WARN_ON(is_trbe_enabled());
	trbsr &= ~TRBSR_IRQ;
	trbsr &= ~TRBSR_TRG;
	trbsr &= ~TRBSR_WRAP;
	trbsr &= ~(TRBSR_EC_MASK << TRBSR_EC_SHIFT);
	trbsr &= ~(TRBSR_BSC_MASK << TRBSR_BSC_SHIFT);
	trbsr &= ~TRBSR_STOP;
	ग_लिखो_sysreg_s(trbsr, SYS_TRBSR_EL1);
पूर्ण

अटल व्योम set_trbe_limit_poपूर्णांकer_enabled(अचिन्हित दीर्घ addr)
अणु
	u64 trblimitr = पढ़ो_sysreg_s(SYS_TRBLIMITR_EL1);

	WARN_ON(!IS_ALIGNED(addr, (1UL << TRBLIMITR_LIMIT_SHIFT)));
	WARN_ON(!IS_ALIGNED(addr, PAGE_SIZE));

	trblimitr &= ~TRBLIMITR_NVM;
	trblimitr &= ~(TRBLIMITR_FILL_MODE_MASK << TRBLIMITR_FILL_MODE_SHIFT);
	trblimitr &= ~(TRBLIMITR_TRIG_MODE_MASK << TRBLIMITR_TRIG_MODE_SHIFT);
	trblimitr &= ~(TRBLIMITR_LIMIT_MASK << TRBLIMITR_LIMIT_SHIFT);

	/*
	 * Fill trace buffer mode is used here जबतक configuring the
	 * TRBE क्रम trace capture. In this particular mode, the trace
	 * collection is stopped and a मुख्यtenance पूर्णांकerrupt is उठाओd
	 * when the current ग_लिखो poपूर्णांकer wraps. This छोड़ो in trace
	 * collection gives the software an opportunity to capture the
	 * trace data in the पूर्णांकerrupt handler, beक्रमe reconfiguring
	 * the TRBE.
	 */
	trblimitr |= (TRBE_FILL_MODE_FILL & TRBLIMITR_FILL_MODE_MASK) << TRBLIMITR_FILL_MODE_SHIFT;

	/*
	 * Trigger mode is not used here जबतक configuring the TRBE क्रम
	 * the trace capture. Hence just keep this in the ignore mode.
	 */
	trblimitr |= (TRBE_TRIG_MODE_IGNORE & TRBLIMITR_TRIG_MODE_MASK) <<
		      TRBLIMITR_TRIG_MODE_SHIFT;
	trblimitr |= (addr & PAGE_MASK);

	trblimitr |= TRBLIMITR_ENABLE;
	ग_लिखो_sysreg_s(trblimitr, SYS_TRBLIMITR_EL1);

	/* Synchronize the TRBE enable event */
	isb();
पूर्ण

अटल व्योम trbe_enable_hw(काष्ठा trbe_buf *buf)
अणु
	WARN_ON(buf->trbe_ग_लिखो < buf->trbe_base);
	WARN_ON(buf->trbe_ग_लिखो >= buf->trbe_limit);
	set_trbe_disabled();
	isb();
	clr_trbe_status();
	set_trbe_base_poपूर्णांकer(buf->trbe_base);
	set_trbe_ग_लिखो_poपूर्णांकer(buf->trbe_ग_लिखो);

	/*
	 * Synchronize all the रेजिस्टर updates
	 * till now beक्रमe enabling the TRBE.
	 */
	isb();
	set_trbe_limit_poपूर्णांकer_enabled(buf->trbe_limit);
पूर्ण

अटल क्रमागत trbe_fault_action trbe_get_fault_act(u64 trbsr)
अणु
	पूर्णांक ec = get_trbe_ec(trbsr);
	पूर्णांक bsc = get_trbe_bsc(trbsr);

	WARN_ON(is_trbe_running(trbsr));
	अगर (is_trbe_trg(trbsr) || is_trbe_पात(trbsr))
		वापस TRBE_FAULT_ACT_FATAL;

	अगर ((ec == TRBE_EC_STAGE1_ABORT) || (ec == TRBE_EC_STAGE2_ABORT))
		वापस TRBE_FAULT_ACT_FATAL;

	अगर (is_trbe_wrap(trbsr) && (ec == TRBE_EC_OTHERS) && (bsc == TRBE_BSC_FILLED)) अणु
		अगर (get_trbe_ग_लिखो_poपूर्णांकer() == get_trbe_base_poपूर्णांकer())
			वापस TRBE_FAULT_ACT_WRAP;
	पूर्ण
	वापस TRBE_FAULT_ACT_SPURIOUS;
पूर्ण

अटल व्योम *arm_trbe_alloc_buffer(काष्ठा coresight_device *csdev,
				   काष्ठा perf_event *event, व्योम **pages,
				   पूर्णांक nr_pages, bool snapshot)
अणु
	काष्ठा trbe_buf *buf;
	काष्ठा page **pglist;
	पूर्णांक i;

	/*
	 * TRBE LIMIT and TRBE WRITE poपूर्णांकers must be page aligned. But with
	 * just a single page, there would not be any room left जबतक writing
	 * पूर्णांकo a partially filled TRBE buffer after the page size alignment.
	 * Hence restrict the minimum buffer size as two pages.
	 */
	अगर (nr_pages < 2)
		वापस शून्य;

	buf = kzalloc_node(माप(*buf), GFP_KERNEL, trbe_alloc_node(event));
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	pglist = kसुस्मृति(nr_pages, माप(*pglist), GFP_KERNEL);
	अगर (!pglist) अणु
		kमुक्त(buf);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	क्रम (i = 0; i < nr_pages; i++)
		pglist[i] = virt_to_page(pages[i]);

	buf->trbe_base = (अचिन्हित दीर्घ)vmap(pglist, nr_pages, VM_MAP, PAGE_KERNEL);
	अगर (!buf->trbe_base) अणु
		kमुक्त(pglist);
		kमुक्त(buf);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	buf->trbe_limit = buf->trbe_base + nr_pages * PAGE_SIZE;
	buf->trbe_ग_लिखो = buf->trbe_base;
	buf->snapshot = snapshot;
	buf->nr_pages = nr_pages;
	buf->pages = pages;
	kमुक्त(pglist);
	वापस buf;
पूर्ण

अटल व्योम arm_trbe_मुक्त_buffer(व्योम *config)
अणु
	काष्ठा trbe_buf *buf = config;

	vunmap((व्योम *)buf->trbe_base);
	kमुक्त(buf);
पूर्ण

अटल अचिन्हित दीर्घ arm_trbe_update_buffer(काष्ठा coresight_device *csdev,
					    काष्ठा perf_output_handle *handle,
					    व्योम *config)
अणु
	काष्ठा trbe_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	काष्ठा trbe_cpudata *cpudata = dev_get_drvdata(&csdev->dev);
	काष्ठा trbe_buf *buf = config;
	क्रमागत trbe_fault_action act;
	अचिन्हित दीर्घ size, offset;
	अचिन्हित दीर्घ ग_लिखो, base, status;
	अचिन्हित दीर्घ flags;

	WARN_ON(buf->cpudata != cpudata);
	WARN_ON(cpudata->cpu != smp_processor_id());
	WARN_ON(cpudata->drvdata != drvdata);
	अगर (cpudata->mode != CS_MODE_PERF)
		वापस 0;

	perf_aux_output_flag(handle, PERF_AUX_FLAG_CORESIGHT_FORMAT_RAW);

	/*
	 * We are about to disable the TRBE. And this could in turn
	 * fill up the buffer triggering, an IRQ. This could be consumed
	 * by the PE asynchronously, causing a race here against
	 * the IRQ handler in closing out the handle. So, let us
	 * make sure the IRQ can't trigger जबतक we are collecting
	 * the buffer. We also make sure that a WRAP event is handled
	 * accordingly.
	 */
	local_irq_save(flags);

	/*
	 * If the TRBE was disabled due to lack of space in the AUX buffer or a
	 * spurious fault, the driver leaves it disabled, truncating the buffer.
	 * Since the eपंचांग_perf driver expects to बंद out the AUX buffer, the
	 * driver skips it. Thus, just pass in 0 size here to indicate that the
	 * buffer was truncated.
	 */
	अगर (!is_trbe_enabled()) अणु
		size = 0;
		जाओ करोne;
	पूर्ण
	/*
	 * perf handle काष्ठाure needs to be shared with the TRBE IRQ handler क्रम
	 * capturing trace data and restarting the handle. There is a probability
	 * of an undefined reference based crash when eपंचांग event is being stopped
	 * जबतक a TRBE IRQ also getting processed. This happens due the release
	 * of perf handle via perf_aux_output_end() in eपंचांग_event_stop(). Stopping
	 * the TRBE here will ensure that no IRQ could be generated when the perf
	 * handle माला_लो मुक्तd in eपंचांग_event_stop().
	 */
	trbe_drain_and_disable_local();
	ग_लिखो = get_trbe_ग_लिखो_poपूर्णांकer();
	base = get_trbe_base_poपूर्णांकer();

	/* Check अगर there is a pending पूर्णांकerrupt and handle it here */
	status = पढ़ो_sysreg_s(SYS_TRBSR_EL1);
	अगर (is_trbe_irq(status)) अणु

		/*
		 * Now that we are handling the IRQ here, clear the IRQ
		 * from the status, to let the irq handler know that it
		 * is taken care of.
		 */
		clr_trbe_irq();
		isb();

		act = trbe_get_fault_act(status);
		/*
		 * If this was not due to a WRAP event, we have some
		 * errors and as such buffer is empty.
		 */
		अगर (act != TRBE_FAULT_ACT_WRAP) अणु
			size = 0;
			जाओ करोne;
		पूर्ण

		/*
		 * Otherwise, the buffer is full and the ग_लिखो poपूर्णांकer
		 * has reached base. Adjust this back to the Limit poपूर्णांकer
		 * क्रम correct size. Also, mark the buffer truncated.
		 */
		ग_लिखो = get_trbe_limit_poपूर्णांकer();
		perf_aux_output_flag(handle, PERF_AUX_FLAG_TRUNCATED);
	पूर्ण

	offset = ग_लिखो - base;
	अगर (WARN_ON_ONCE(offset < PERF_IDX2OFF(handle->head, buf)))
		size = 0;
	अन्यथा
		size = offset - PERF_IDX2OFF(handle->head, buf);

करोne:
	local_irq_restore(flags);

	अगर (buf->snapshot)
		handle->head += size;
	वापस size;
पूर्ण

अटल पूर्णांक arm_trbe_enable(काष्ठा coresight_device *csdev, u32 mode, व्योम *data)
अणु
	काष्ठा trbe_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	काष्ठा trbe_cpudata *cpudata = dev_get_drvdata(&csdev->dev);
	काष्ठा perf_output_handle *handle = data;
	काष्ठा trbe_buf *buf = eपंचांग_perf_sink_config(handle);

	WARN_ON(cpudata->cpu != smp_processor_id());
	WARN_ON(cpudata->drvdata != drvdata);
	अगर (mode != CS_MODE_PERF)
		वापस -EINVAL;

	*this_cpu_ptr(drvdata->handle) = handle;
	cpudata->buf = buf;
	cpudata->mode = mode;
	buf->cpudata = cpudata;
	buf->trbe_limit = compute_trbe_buffer_limit(handle);
	buf->trbe_ग_लिखो = buf->trbe_base + PERF_IDX2OFF(handle->head, buf);
	अगर (buf->trbe_limit == buf->trbe_base) अणु
		trbe_stop_and_truncate_event(handle);
		वापस 0;
	पूर्ण
	trbe_enable_hw(buf);
	वापस 0;
पूर्ण

अटल पूर्णांक arm_trbe_disable(काष्ठा coresight_device *csdev)
अणु
	काष्ठा trbe_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	काष्ठा trbe_cpudata *cpudata = dev_get_drvdata(&csdev->dev);
	काष्ठा trbe_buf *buf = cpudata->buf;

	WARN_ON(buf->cpudata != cpudata);
	WARN_ON(cpudata->cpu != smp_processor_id());
	WARN_ON(cpudata->drvdata != drvdata);
	अगर (cpudata->mode != CS_MODE_PERF)
		वापस -EINVAL;

	trbe_drain_and_disable_local();
	buf->cpudata = शून्य;
	cpudata->buf = शून्य;
	cpudata->mode = CS_MODE_DISABLED;
	वापस 0;
पूर्ण

अटल व्योम trbe_handle_spurious(काष्ठा perf_output_handle *handle)
अणु
	काष्ठा trbe_buf *buf = eपंचांग_perf_sink_config(handle);

	buf->trbe_limit = compute_trbe_buffer_limit(handle);
	buf->trbe_ग_लिखो = buf->trbe_base + PERF_IDX2OFF(handle->head, buf);
	अगर (buf->trbe_limit == buf->trbe_base) अणु
		trbe_drain_and_disable_local();
		वापस;
	पूर्ण
	trbe_enable_hw(buf);
पूर्ण

अटल व्योम trbe_handle_overflow(काष्ठा perf_output_handle *handle)
अणु
	काष्ठा perf_event *event = handle->event;
	काष्ठा trbe_buf *buf = eपंचांग_perf_sink_config(handle);
	अचिन्हित दीर्घ offset, size;
	काष्ठा eपंचांग_event_data *event_data;

	offset = get_trbe_limit_poपूर्णांकer() - get_trbe_base_poपूर्णांकer();
	size = offset - PERF_IDX2OFF(handle->head, buf);
	अगर (buf->snapshot)
		handle->head += size;

	/*
	 * Mark the buffer as truncated, as we have stopped the trace
	 * collection upon the WRAP event, without stopping the source.
	 */
	perf_aux_output_flag(handle, PERF_AUX_FLAG_CORESIGHT_FORMAT_RAW |
				     PERF_AUX_FLAG_TRUNCATED);
	perf_aux_output_end(handle, size);
	event_data = perf_aux_output_begin(handle, event);
	अगर (!event_data) अणु
		/*
		 * We are unable to restart the trace collection,
		 * thus leave the TRBE disabled. The eपंचांग-perf driver
		 * is able to detect this with a disconnected handle
		 * (handle->event = शून्य).
		 */
		trbe_drain_and_disable_local();
		*this_cpu_ptr(buf->cpudata->drvdata->handle) = शून्य;
		वापस;
	पूर्ण
	buf->trbe_limit = compute_trbe_buffer_limit(handle);
	buf->trbe_ग_लिखो = buf->trbe_base + PERF_IDX2OFF(handle->head, buf);
	अगर (buf->trbe_limit == buf->trbe_base) अणु
		trbe_stop_and_truncate_event(handle);
		वापस;
	पूर्ण
	*this_cpu_ptr(buf->cpudata->drvdata->handle) = handle;
	trbe_enable_hw(buf);
पूर्ण

अटल bool is_perf_trbe(काष्ठा perf_output_handle *handle)
अणु
	काष्ठा trbe_buf *buf = eपंचांग_perf_sink_config(handle);
	काष्ठा trbe_cpudata *cpudata = buf->cpudata;
	काष्ठा trbe_drvdata *drvdata = cpudata->drvdata;
	पूर्णांक cpu = smp_processor_id();

	WARN_ON(buf->trbe_base != get_trbe_base_poपूर्णांकer());
	WARN_ON(buf->trbe_limit != get_trbe_limit_poपूर्णांकer());

	अगर (cpudata->mode != CS_MODE_PERF)
		वापस false;

	अगर (cpudata->cpu != cpu)
		वापस false;

	अगर (!cpumask_test_cpu(cpu, &drvdata->supported_cpus))
		वापस false;

	वापस true;
पूर्ण

अटल irqवापस_t arm_trbe_irq_handler(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा perf_output_handle **handle_ptr = dev;
	काष्ठा perf_output_handle *handle = *handle_ptr;
	क्रमागत trbe_fault_action act;
	u64 status;

	/*
	 * Ensure the trace is visible to the CPUs and
	 * any बाह्यal पातs have been resolved.
	 */
	trbe_drain_and_disable_local();

	status = पढ़ो_sysreg_s(SYS_TRBSR_EL1);
	/*
	 * If the pending IRQ was handled by update_buffer callback
	 * we have nothing to करो here.
	 */
	अगर (!is_trbe_irq(status))
		वापस IRQ_NONE;

	clr_trbe_irq();
	isb();

	अगर (WARN_ON_ONCE(!handle) || !perf_get_aux(handle))
		वापस IRQ_NONE;

	अगर (!is_perf_trbe(handle))
		वापस IRQ_NONE;

	/*
	 * Ensure perf callbacks have completed, which may disable
	 * the trace buffer in response to a TRUNCATION flag.
	 */
	irq_work_run();

	act = trbe_get_fault_act(status);
	चयन (act) अणु
	हाल TRBE_FAULT_ACT_WRAP:
		trbe_handle_overflow(handle);
		अवरोध;
	हाल TRBE_FAULT_ACT_SPURIOUS:
		trbe_handle_spurious(handle);
		अवरोध;
	हाल TRBE_FAULT_ACT_FATAL:
		trbe_stop_and_truncate_event(handle);
		अवरोध;
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा coresight_ops_sink arm_trbe_sink_ops = अणु
	.enable		= arm_trbe_enable,
	.disable	= arm_trbe_disable,
	.alloc_buffer	= arm_trbe_alloc_buffer,
	.मुक्त_buffer	= arm_trbe_मुक्त_buffer,
	.update_buffer	= arm_trbe_update_buffer,
पूर्ण;

अटल स्थिर काष्ठा coresight_ops arm_trbe_cs_ops = अणु
	.sink_ops	= &arm_trbe_sink_ops,
पूर्ण;

अटल sमाप_प्रकार align_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा trbe_cpudata *cpudata = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%llx\n", cpudata->trbe_align);
पूर्ण
अटल DEVICE_ATTR_RO(align);

अटल sमाप_प्रकार flag_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा trbe_cpudata *cpudata = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", cpudata->trbe_flag);
पूर्ण
अटल DEVICE_ATTR_RO(flag);

अटल काष्ठा attribute *arm_trbe_attrs[] = अणु
	&dev_attr_align.attr,
	&dev_attr_flag.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group arm_trbe_group = अणु
	.attrs = arm_trbe_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *arm_trbe_groups[] = अणु
	&arm_trbe_group,
	शून्य,
पूर्ण;

अटल व्योम arm_trbe_enable_cpu(व्योम *info)
अणु
	काष्ठा trbe_drvdata *drvdata = info;

	trbe_reset_local();
	enable_percpu_irq(drvdata->irq, IRQ_TYPE_NONE);
पूर्ण

अटल व्योम arm_trbe_रेजिस्टर_coresight_cpu(काष्ठा trbe_drvdata *drvdata, पूर्णांक cpu)
अणु
	काष्ठा trbe_cpudata *cpudata = per_cpu_ptr(drvdata->cpudata, cpu);
	काष्ठा coresight_device *trbe_csdev = coresight_get_percpu_sink(cpu);
	काष्ठा coresight_desc desc = अणु 0 पूर्ण;
	काष्ठा device *dev;

	अगर (WARN_ON(trbe_csdev))
		वापस;

	dev = &cpudata->drvdata->pdev->dev;
	desc.name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "trbe%d", cpu);
	अगर (!desc.name)
		जाओ cpu_clear;

	desc.type = CORESIGHT_DEV_TYPE_SINK;
	desc.subtype.sink_subtype = CORESIGHT_DEV_SUBTYPE_SINK_PERCPU_SYSMEM;
	desc.ops = &arm_trbe_cs_ops;
	desc.pdata = dev_get_platdata(dev);
	desc.groups = arm_trbe_groups;
	desc.dev = dev;
	trbe_csdev = coresight_रेजिस्टर(&desc);
	अगर (IS_ERR(trbe_csdev))
		जाओ cpu_clear;

	dev_set_drvdata(&trbe_csdev->dev, cpudata);
	coresight_set_percpu_sink(cpu, trbe_csdev);
	वापस;
cpu_clear:
	cpumask_clear_cpu(cpu, &drvdata->supported_cpus);
पूर्ण

अटल व्योम arm_trbe_probe_cpu(व्योम *info)
अणु
	काष्ठा trbe_drvdata *drvdata = info;
	पूर्णांक cpu = smp_processor_id();
	काष्ठा trbe_cpudata *cpudata = per_cpu_ptr(drvdata->cpudata, cpu);
	u64 trbidr;

	अगर (WARN_ON(!cpudata))
		जाओ cpu_clear;

	अगर (!is_trbe_available()) अणु
		pr_err("TRBE is not implemented on cpu %d\n", cpu);
		जाओ cpu_clear;
	पूर्ण

	trbidr = पढ़ो_sysreg_s(SYS_TRBIDR_EL1);
	अगर (!is_trbe_programmable(trbidr)) अणु
		pr_err("TRBE is owned in higher exception level on cpu %d\n", cpu);
		जाओ cpu_clear;
	पूर्ण

	cpudata->trbe_align = 1ULL << get_trbe_address_align(trbidr);
	अगर (cpudata->trbe_align > SZ_2K) अणु
		pr_err("Unsupported alignment on cpu %d\n", cpu);
		जाओ cpu_clear;
	पूर्ण
	cpudata->trbe_flag = get_trbe_flag_update(trbidr);
	cpudata->cpu = cpu;
	cpudata->drvdata = drvdata;
	वापस;
cpu_clear:
	cpumask_clear_cpu(cpu, &drvdata->supported_cpus);
पूर्ण

अटल व्योम arm_trbe_हटाओ_coresight_cpu(व्योम *info)
अणु
	पूर्णांक cpu = smp_processor_id();
	काष्ठा trbe_drvdata *drvdata = info;
	काष्ठा trbe_cpudata *cpudata = per_cpu_ptr(drvdata->cpudata, cpu);
	काष्ठा coresight_device *trbe_csdev = coresight_get_percpu_sink(cpu);

	disable_percpu_irq(drvdata->irq);
	trbe_reset_local();
	अगर (trbe_csdev) अणु
		coresight_unरेजिस्टर(trbe_csdev);
		cpudata->drvdata = शून्य;
		coresight_set_percpu_sink(cpu, शून्य);
	पूर्ण
पूर्ण

अटल पूर्णांक arm_trbe_probe_coresight(काष्ठा trbe_drvdata *drvdata)
अणु
	पूर्णांक cpu;

	drvdata->cpudata = alloc_percpu(typeof(*drvdata->cpudata));
	अगर (!drvdata->cpudata)
		वापस -ENOMEM;

	क्रम_each_cpu(cpu, &drvdata->supported_cpus) अणु
		smp_call_function_single(cpu, arm_trbe_probe_cpu, drvdata, 1);
		अगर (cpumask_test_cpu(cpu, &drvdata->supported_cpus))
			arm_trbe_रेजिस्टर_coresight_cpu(drvdata, cpu);
		अगर (cpumask_test_cpu(cpu, &drvdata->supported_cpus))
			smp_call_function_single(cpu, arm_trbe_enable_cpu, drvdata, 1);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक arm_trbe_हटाओ_coresight(काष्ठा trbe_drvdata *drvdata)
अणु
	पूर्णांक cpu;

	क्रम_each_cpu(cpu, &drvdata->supported_cpus)
		smp_call_function_single(cpu, arm_trbe_हटाओ_coresight_cpu, drvdata, 1);
	मुक्त_percpu(drvdata->cpudata);
	वापस 0;
पूर्ण

अटल पूर्णांक arm_trbe_cpu_startup(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा trbe_drvdata *drvdata = hlist_entry_safe(node, काष्ठा trbe_drvdata, hotplug_node);

	अगर (cpumask_test_cpu(cpu, &drvdata->supported_cpus)) अणु

		/*
		 * If this CPU was not probed क्रम TRBE,
		 * initialize it now.
		 */
		अगर (!coresight_get_percpu_sink(cpu)) अणु
			arm_trbe_probe_cpu(drvdata);
			अगर (cpumask_test_cpu(cpu, &drvdata->supported_cpus))
				arm_trbe_रेजिस्टर_coresight_cpu(drvdata, cpu);
			अगर (cpumask_test_cpu(cpu, &drvdata->supported_cpus))
				arm_trbe_enable_cpu(drvdata);
		पूर्ण अन्यथा अणु
			arm_trbe_enable_cpu(drvdata);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक arm_trbe_cpu_tearकरोwn(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा trbe_drvdata *drvdata = hlist_entry_safe(node, काष्ठा trbe_drvdata, hotplug_node);

	अगर (cpumask_test_cpu(cpu, &drvdata->supported_cpus)) अणु
		disable_percpu_irq(drvdata->irq);
		trbe_reset_local();
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक arm_trbe_probe_cpuhp(काष्ठा trbe_drvdata *drvdata)
अणु
	क्रमागत cpuhp_state trbe_online;
	पूर्णांक ret;

	trbe_online = cpuhp_setup_state_multi(CPUHP_AP_ONLINE_DYN, DRVNAME,
					      arm_trbe_cpu_startup, arm_trbe_cpu_tearकरोwn);
	अगर (trbe_online < 0)
		वापस trbe_online;

	ret = cpuhp_state_add_instance(trbe_online, &drvdata->hotplug_node);
	अगर (ret) अणु
		cpuhp_हटाओ_multi_state(trbe_online);
		वापस ret;
	पूर्ण
	drvdata->trbe_online = trbe_online;
	वापस 0;
पूर्ण

अटल व्योम arm_trbe_हटाओ_cpuhp(काष्ठा trbe_drvdata *drvdata)
अणु
	cpuhp_हटाओ_multi_state(drvdata->trbe_online);
पूर्ण

अटल पूर्णांक arm_trbe_probe_irq(काष्ठा platक्रमm_device *pdev,
			      काष्ठा trbe_drvdata *drvdata)
अणु
	पूर्णांक ret;

	drvdata->irq = platक्रमm_get_irq(pdev, 0);
	अगर (drvdata->irq < 0) अणु
		pr_err("IRQ not found for the platform device\n");
		वापस drvdata->irq;
	पूर्ण

	अगर (!irq_is_percpu(drvdata->irq)) अणु
		pr_err("IRQ is not a PPI\n");
		वापस -EINVAL;
	पूर्ण

	अगर (irq_get_percpu_devid_partition(drvdata->irq, &drvdata->supported_cpus))
		वापस -EINVAL;

	drvdata->handle = alloc_percpu(काष्ठा perf_output_handle *);
	अगर (!drvdata->handle)
		वापस -ENOMEM;

	ret = request_percpu_irq(drvdata->irq, arm_trbe_irq_handler, DRVNAME, drvdata->handle);
	अगर (ret) अणु
		मुक्त_percpu(drvdata->handle);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम arm_trbe_हटाओ_irq(काष्ठा trbe_drvdata *drvdata)
अणु
	मुक्त_percpu_irq(drvdata->irq, drvdata->handle);
	मुक्त_percpu(drvdata->handle);
पूर्ण

अटल पूर्णांक arm_trbe_device_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा coresight_platक्रमm_data *pdata;
	काष्ठा trbe_drvdata *drvdata;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	drvdata = devm_kzalloc(dev, माप(*drvdata), GFP_KERNEL);
	अगर (!drvdata)
		वापस -ENOMEM;

	pdata = coresight_get_platक्रमm_data(dev);
	अगर (IS_ERR(pdata))
		वापस PTR_ERR(pdata);

	dev_set_drvdata(dev, drvdata);
	dev->platक्रमm_data = pdata;
	drvdata->pdev = pdev;
	ret = arm_trbe_probe_irq(pdev, drvdata);
	अगर (ret)
		वापस ret;

	ret = arm_trbe_probe_coresight(drvdata);
	अगर (ret)
		जाओ probe_failed;

	ret = arm_trbe_probe_cpuhp(drvdata);
	अगर (ret)
		जाओ cpuhp_failed;

	वापस 0;
cpuhp_failed:
	arm_trbe_हटाओ_coresight(drvdata);
probe_failed:
	arm_trbe_हटाओ_irq(drvdata);
	वापस ret;
पूर्ण

अटल पूर्णांक arm_trbe_device_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा trbe_drvdata *drvdata = platक्रमm_get_drvdata(pdev);

	arm_trbe_हटाओ_cpuhp(drvdata);
	arm_trbe_हटाओ_coresight(drvdata);
	arm_trbe_हटाओ_irq(drvdata);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id arm_trbe_of_match[] = अणु
	अणु .compatible = "arm,trace-buffer-extension"पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, arm_trbe_of_match);

अटल काष्ठा platक्रमm_driver arm_trbe_driver = अणु
	.driver	= अणु
		.name = DRVNAME,
		.of_match_table = of_match_ptr(arm_trbe_of_match),
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe	= arm_trbe_device_probe,
	.हटाओ	= arm_trbe_device_हटाओ,
पूर्ण;

अटल पूर्णांक __init arm_trbe_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (arm64_kernel_unmapped_at_el0()) अणु
		pr_err("TRBE wouldn't work if kernel gets unmapped at EL0\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&arm_trbe_driver);
	अगर (!ret)
		वापस 0;

	pr_err("Error registering %s platform driver\n", DRVNAME);
	वापस ret;
पूर्ण

अटल व्योम __निकास arm_trbe_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&arm_trbe_driver);
पूर्ण
module_init(arm_trbe_init);
module_निकास(arm_trbe_निकास);

MODULE_AUTHOR("Anshuman Khandual <anshuman.khandual@arm.com>");
MODULE_DESCRIPTION("Arm Trace Buffer Extension (TRBE) driver");
MODULE_LICENSE("GPL v2");
