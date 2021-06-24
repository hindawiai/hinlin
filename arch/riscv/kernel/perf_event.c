<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2008 Thomas Gleixner <tglx@linutronix.de>
 * Copyright (C) 2008-2009 Red Hat, Inc., Ingo Molnar
 * Copyright (C) 2009 Jaswinder Singh Rajput
 * Copyright (C) 2009 Advanced Micro Devices, Inc., Robert Richter
 * Copyright (C) 2008-2009 Red Hat, Inc., Peter Zijlstra
 * Copyright (C) 2009 Intel Corporation, <markus.t.metzger@पूर्णांकel.com>
 * Copyright (C) 2009 Google, Inc., Stephane Eranian
 * Copyright 2014 Tilera Corporation. All Rights Reserved.
 * Copyright (C) 2018 Andes Technology Corporation
 *
 * Perf_events support क्रम RISC-V platक्रमms.
 *
 * Since the spec. (as of now, Priv-Spec 1.10) करोes not provide enough
 * functionality क्रम perf event to fully work, this file provides
 * the very basic framework only.
 *
 * For platक्रमm portings, please check Documentations/riscv/pmu.txt.
 *
 * The Copyright line includes x86 and tile ones.
 */

#समावेश <linux/kprobes.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/mutex.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/irq.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/atomic.h>
#समावेश <linux/of.h>
#समावेश <यंत्र/perf_event.h>

अटल स्थिर काष्ठा riscv_pmu *riscv_pmu __पढ़ो_mostly;
अटल DEFINE_PER_CPU(काष्ठा cpu_hw_events, cpu_hw_events);

/*
 * Hardware & cache maps and their methods
 */

अटल स्थिर पूर्णांक riscv_hw_event_map[] = अणु
	[PERF_COUNT_HW_CPU_CYCLES]		= RISCV_PMU_CYCLE,
	[PERF_COUNT_HW_INSTRUCTIONS]		= RISCV_PMU_INSTRET,
	[PERF_COUNT_HW_CACHE_REFERENCES]	= RISCV_OP_UNSUPP,
	[PERF_COUNT_HW_CACHE_MISSES]		= RISCV_OP_UNSUPP,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS]	= RISCV_OP_UNSUPP,
	[PERF_COUNT_HW_BRANCH_MISSES]		= RISCV_OP_UNSUPP,
	[PERF_COUNT_HW_BUS_CYCLES]		= RISCV_OP_UNSUPP,
पूर्ण;

#घोषणा C(x) PERF_COUNT_HW_CACHE_##x
अटल स्थिर पूर्णांक riscv_cache_event_map[PERF_COUNT_HW_CACHE_MAX]
[PERF_COUNT_HW_CACHE_OP_MAX]
[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
	[C(L1D)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)] = RISCV_OP_UNSUPP,
			[C(RESULT_MISS)] = RISCV_OP_UNSUPP,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)] = RISCV_OP_UNSUPP,
			[C(RESULT_MISS)] = RISCV_OP_UNSUPP,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)] = RISCV_OP_UNSUPP,
			[C(RESULT_MISS)] = RISCV_OP_UNSUPP,
		पूर्ण,
	पूर्ण,
	[C(L1I)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)] = RISCV_OP_UNSUPP,
			[C(RESULT_MISS)] = RISCV_OP_UNSUPP,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)] = RISCV_OP_UNSUPP,
			[C(RESULT_MISS)] = RISCV_OP_UNSUPP,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)] = RISCV_OP_UNSUPP,
			[C(RESULT_MISS)] = RISCV_OP_UNSUPP,
		पूर्ण,
	पूर्ण,
	[C(LL)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)] = RISCV_OP_UNSUPP,
			[C(RESULT_MISS)] = RISCV_OP_UNSUPP,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)] = RISCV_OP_UNSUPP,
			[C(RESULT_MISS)] = RISCV_OP_UNSUPP,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)] = RISCV_OP_UNSUPP,
			[C(RESULT_MISS)] = RISCV_OP_UNSUPP,
		पूर्ण,
	पूर्ण,
	[C(DTLB)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)] =  RISCV_OP_UNSUPP,
			[C(RESULT_MISS)] =  RISCV_OP_UNSUPP,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)] = RISCV_OP_UNSUPP,
			[C(RESULT_MISS)] = RISCV_OP_UNSUPP,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)] = RISCV_OP_UNSUPP,
			[C(RESULT_MISS)] = RISCV_OP_UNSUPP,
		पूर्ण,
	पूर्ण,
	[C(ITLB)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)] = RISCV_OP_UNSUPP,
			[C(RESULT_MISS)] = RISCV_OP_UNSUPP,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)] = RISCV_OP_UNSUPP,
			[C(RESULT_MISS)] = RISCV_OP_UNSUPP,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)] = RISCV_OP_UNSUPP,
			[C(RESULT_MISS)] = RISCV_OP_UNSUPP,
		पूर्ण,
	पूर्ण,
	[C(BPU)] = अणु
		[C(OP_READ)] = अणु
			[C(RESULT_ACCESS)] = RISCV_OP_UNSUPP,
			[C(RESULT_MISS)] = RISCV_OP_UNSUPP,
		पूर्ण,
		[C(OP_WRITE)] = अणु
			[C(RESULT_ACCESS)] = RISCV_OP_UNSUPP,
			[C(RESULT_MISS)] = RISCV_OP_UNSUPP,
		पूर्ण,
		[C(OP_PREFETCH)] = अणु
			[C(RESULT_ACCESS)] = RISCV_OP_UNSUPP,
			[C(RESULT_MISS)] = RISCV_OP_UNSUPP,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक riscv_map_hw_event(u64 config)
अणु
	अगर (config >= riscv_pmu->max_events)
		वापस -EINVAL;

	वापस riscv_pmu->hw_events[config];
पूर्ण

अटल पूर्णांक riscv_map_cache_decode(u64 config, अचिन्हित पूर्णांक *type,
			   अचिन्हित पूर्णांक *op, अचिन्हित पूर्णांक *result)
अणु
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक riscv_map_cache_event(u64 config)
अणु
	अचिन्हित पूर्णांक type, op, result;
	पूर्णांक err = -ENOENT;
		पूर्णांक code;

	err = riscv_map_cache_decode(config, &type, &op, &result);
	अगर (!riscv_pmu->cache_events || err)
		वापस err;

	अगर (type >= PERF_COUNT_HW_CACHE_MAX ||
	    op >= PERF_COUNT_HW_CACHE_OP_MAX ||
	    result >= PERF_COUNT_HW_CACHE_RESULT_MAX)
		वापस -EINVAL;

	code = (*riscv_pmu->cache_events)[type][op][result];
	अगर (code == RISCV_OP_UNSUPP)
		वापस -EINVAL;

	वापस code;
पूर्ण

/*
 * Low-level functions: पढ़ोing/writing counters
 */

अटल अंतरभूत u64 पढ़ो_counter(पूर्णांक idx)
अणु
	u64 val = 0;

	चयन (idx) अणु
	हाल RISCV_PMU_CYCLE:
		val = csr_पढ़ो(CSR_CYCLE);
		अवरोध;
	हाल RISCV_PMU_INSTRET:
		val = csr_पढ़ो(CSR_INSTRET);
		अवरोध;
	शेष:
		WARN_ON_ONCE(idx < 0 ||	idx > RISCV_MAX_COUNTERS);
		वापस -EINVAL;
	पूर्ण

	वापस val;
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_counter(पूर्णांक idx, u64 value)
अणु
	/* currently not supported */
	WARN_ON_ONCE(1);
पूर्ण

/*
 * pmu->पढ़ो: पढ़ो and update the counter
 *
 * Other architectures' implementation often have a xxx_perf_event_update
 * routine, which can वापस counter values when called in the IRQ, but
 * वापस व्योम when being called by the pmu->पढ़ो method.
 */
अटल व्योम riscv_pmu_पढ़ो(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 prev_raw_count, new_raw_count;
	u64 oldval;
	पूर्णांक idx = hwc->idx;
	u64 delta;

	करो अणु
		prev_raw_count = local64_पढ़ो(&hwc->prev_count);
		new_raw_count = पढ़ो_counter(idx);

		oldval = local64_cmpxchg(&hwc->prev_count, prev_raw_count,
					 new_raw_count);
	पूर्ण जबतक (oldval != prev_raw_count);

	/*
	 * delta is the value to update the counter we मुख्यtain in the kernel.
	 */
	delta = (new_raw_count - prev_raw_count) &
		((1ULL << riscv_pmu->counter_width) - 1);
	local64_add(delta, &event->count);
	/*
	 * Something like local64_sub(delta, &hwc->period_left) here is
	 * needed अगर there is an पूर्णांकerrupt क्रम perf.
	 */
पूर्ण

/*
 * State transition functions:
 *
 * stop()/start() & add()/del()
 */

/*
 * pmu->stop: stop the counter
 */
अटल व्योम riscv_pmu_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	WARN_ON_ONCE(hwc->state & PERF_HES_STOPPED);
	hwc->state |= PERF_HES_STOPPED;

	अगर ((flags & PERF_EF_UPDATE) && !(hwc->state & PERF_HES_UPTODATE)) अणु
		riscv_pmu->pmu->पढ़ो(event);
		hwc->state |= PERF_HES_UPTODATE;
	पूर्ण
पूर्ण

/*
 * pmu->start: start the event.
 */
अटल व्योम riscv_pmu_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (WARN_ON_ONCE(!(event->hw.state & PERF_HES_STOPPED)))
		वापस;

	अगर (flags & PERF_EF_RELOAD) अणु
		WARN_ON_ONCE(!(event->hw.state & PERF_HES_UPTODATE));

		/*
		 * Set the counter to the period to the next पूर्णांकerrupt here,
		 * अगर you have any.
		 */
	पूर्ण

	hwc->state = 0;
	perf_event_update_userpage(event);

	/*
	 * Since we cannot ग_लिखो to counters, this serves as an initialization
	 * to the delta-mechanism in pmu->पढ़ो(); otherwise, the delta would be
	 * wrong when pmu->पढ़ो is called क्रम the first समय.
	 */
	local64_set(&hwc->prev_count, पढ़ो_counter(hwc->idx));
पूर्ण

/*
 * pmu->add: add the event to PMU.
 */
अटल पूर्णांक riscv_pmu_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (cpuc->n_events == riscv_pmu->num_counters)
		वापस -ENOSPC;

	/*
	 * We करोn't have general conunters, so no binding-event-to-counter
	 * process here.
	 *
	 * Indexing using hwc->config generally not works, since config may
	 * contain extra inक्रमmation, but here the only info we have in
	 * hwc->config is the event index.
	 */
	hwc->idx = hwc->config;
	cpuc->events[hwc->idx] = event;
	cpuc->n_events++;

	hwc->state = PERF_HES_UPTODATE | PERF_HES_STOPPED;

	अगर (flags & PERF_EF_START)
		riscv_pmu->pmu->start(event, PERF_EF_RELOAD);

	वापस 0;
पूर्ण

/*
 * pmu->del: delete the event from PMU.
 */
अटल व्योम riscv_pmu_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा hw_perf_event *hwc = &event->hw;

	cpuc->events[hwc->idx] = शून्य;
	cpuc->n_events--;
	riscv_pmu->pmu->stop(event, PERF_EF_UPDATE);
	perf_event_update_userpage(event);
पूर्ण

/*
 * Interrupt: a skeletion क्रम reference.
 */

अटल DEFINE_MUTEX(pmc_reserve_mutex);

अटल irqवापस_t riscv_base_pmu_handle_irq(पूर्णांक irq_num, व्योम *dev)
अणु
	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक reserve_pmc_hardware(व्योम)
अणु
	पूर्णांक err = 0;

	mutex_lock(&pmc_reserve_mutex);
	अगर (riscv_pmu->irq >= 0 && riscv_pmu->handle_irq) अणु
		err = request_irq(riscv_pmu->irq, riscv_pmu->handle_irq,
				  IRQF_PERCPU, "riscv-base-perf", शून्य);
	पूर्ण
	mutex_unlock(&pmc_reserve_mutex);

	वापस err;
पूर्ण

अटल व्योम release_pmc_hardware(व्योम)
अणु
	mutex_lock(&pmc_reserve_mutex);
	अगर (riscv_pmu->irq >= 0)
		मुक्त_irq(riscv_pmu->irq, शून्य);
	mutex_unlock(&pmc_reserve_mutex);
पूर्ण

/*
 * Event Initialization/Finalization
 */

अटल atomic_t riscv_active_events = ATOMIC_INIT(0);

अटल व्योम riscv_event_destroy(काष्ठा perf_event *event)
अणु
	अगर (atomic_dec_वापस(&riscv_active_events) == 0)
		release_pmc_hardware();
पूर्ण

अटल पूर्णांक riscv_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_attr *attr = &event->attr;
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक err;
	पूर्णांक code;

	अगर (atomic_inc_वापस(&riscv_active_events) == 1) अणु
		err = reserve_pmc_hardware();

		अगर (err) अणु
			pr_warn("PMC hardware not available\n");
			atomic_dec(&riscv_active_events);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	चयन (event->attr.type) अणु
	हाल PERF_TYPE_HARDWARE:
		code = riscv_pmu->map_hw_event(attr->config);
		अवरोध;
	हाल PERF_TYPE_HW_CACHE:
		code = riscv_pmu->map_cache_event(attr->config);
		अवरोध;
	हाल PERF_TYPE_RAW:
		वापस -EOPNOTSUPP;
	शेष:
		वापस -ENOENT;
	पूर्ण

	event->destroy = riscv_event_destroy;
	अगर (code < 0) अणु
		event->destroy(event);
		वापस code;
	पूर्ण

	/*
	 * idx is set to -1 because the index of a general event should not be
	 * decided until binding to some counter in pmu->add().
	 *
	 * But since we करोn't have such support, later in pmu->add(), we just
	 * use hwc->config as the index instead.
	 */
	hwc->config = code;
	hwc->idx = -1;

	वापस 0;
पूर्ण

/*
 * Initialization
 */

अटल काष्ठा pmu min_pmu = अणु
	.name		= "riscv-base",
	.event_init	= riscv_event_init,
	.add		= riscv_pmu_add,
	.del		= riscv_pmu_del,
	.start		= riscv_pmu_start,
	.stop		= riscv_pmu_stop,
	.पढ़ो		= riscv_pmu_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा riscv_pmu riscv_base_pmu = अणु
	.pmu = &min_pmu,
	.max_events = ARRAY_SIZE(riscv_hw_event_map),
	.map_hw_event = riscv_map_hw_event,
	.hw_events = riscv_hw_event_map,
	.map_cache_event = riscv_map_cache_event,
	.cache_events = &riscv_cache_event_map,
	.counter_width = 63,
	.num_counters = RISCV_BASE_COUNTERS + 0,
	.handle_irq = &riscv_base_pmu_handle_irq,

	/* This means this PMU has no IRQ. */
	.irq = -1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id riscv_pmu_of_ids[] = अणु
	अणु.compatible = "riscv,base-pmu",	.data = &riscv_base_pmuपूर्ण,
	अणु /* sentinel value */ पूर्ण
पूर्ण;

अटल पूर्णांक __init init_hw_perf_events(व्योम)
अणु
	काष्ठा device_node *node = of_find_node_by_type(शून्य, "pmu");
	स्थिर काष्ठा of_device_id *of_id;

	riscv_pmu = &riscv_base_pmu;

	अगर (node) अणु
		of_id = of_match_node(riscv_pmu_of_ids, node);

		अगर (of_id)
			riscv_pmu = of_id->data;
		of_node_put(node);
	पूर्ण

	perf_pmu_रेजिस्टर(riscv_pmu->pmu, "cpu", PERF_TYPE_RAW);
	वापस 0;
पूर्ण
arch_initcall(init_hw_perf_events);
