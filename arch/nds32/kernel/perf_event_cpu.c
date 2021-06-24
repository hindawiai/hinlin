<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2008-2017 Andes Technology Corporation
 *
 * Reference ARMv7: Jean Pihet <jpihet@mvista.com>
 * 2010 (c) MontaVista Software, LLC.
 */

#समावेश <linux/perf_event.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/ftrace.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/percpu-defs.h>

#समावेश <यंत्र/pmu.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/nds32.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/perf_event.h>
#समावेश <nds32_पूर्णांकrinsic.h>

/* Set at runसमय when we know what CPU type we are. */
अटल काष्ठा nds32_pmu *cpu_pmu;

अटल DEFINE_PER_CPU(काष्ठा pmu_hw_events, cpu_hw_events);
अटल व्योम nds32_pmu_start(काष्ठा nds32_pmu *cpu_pmu);
अटल व्योम nds32_pmu_stop(काष्ठा nds32_pmu *cpu_pmu);
अटल काष्ठा platक्रमm_device_id cpu_pmu_plat_device_ids[] = अणु
	अणु.name = "nds32-pfm"पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक nds32_pmu_map_cache_event(स्थिर अचिन्हित पूर्णांक (*cache_map)
				  [PERF_COUNT_HW_CACHE_MAX]
				  [PERF_COUNT_HW_CACHE_OP_MAX]
				  [PERF_COUNT_HW_CACHE_RESULT_MAX], u64 config)
अणु
	अचिन्हित पूर्णांक cache_type, cache_op, cache_result, ret;

	cache_type = (config >> 0) & 0xff;
	अगर (cache_type >= PERF_COUNT_HW_CACHE_MAX)
		वापस -EINVAL;

	cache_op = (config >> 8) & 0xff;
	अगर (cache_op >= PERF_COUNT_HW_CACHE_OP_MAX)
		वापस -EINVAL;

	cache_result = (config >> 16) & 0xff;
	अगर (cache_result >= PERF_COUNT_HW_CACHE_RESULT_MAX)
		वापस -EINVAL;

	ret = (पूर्णांक)(*cache_map)[cache_type][cache_op][cache_result];

	अगर (ret == CACHE_OP_UNSUPPORTED)
		वापस -ENOENT;

	वापस ret;
पूर्ण

अटल पूर्णांक
nds32_pmu_map_hw_event(स्थिर अचिन्हित पूर्णांक (*event_map)[PERF_COUNT_HW_MAX],
		       u64 config)
अणु
	पूर्णांक mapping;

	अगर (config >= PERF_COUNT_HW_MAX)
		वापस -ENOENT;

	mapping = (*event_map)[config];
	वापस mapping == HW_OP_UNSUPPORTED ? -ENOENT : mapping;
पूर्ण

अटल पूर्णांक nds32_pmu_map_raw_event(u32 raw_event_mask, u64 config)
अणु
	पूर्णांक ev_type = (पूर्णांक)(config & raw_event_mask);
	पूर्णांक idx = config >> 8;

	चयन (idx) अणु
	हाल 0:
		ev_type = PFM_OFFSET_MAGIC_0 + ev_type;
		अगर (ev_type >= SPAV3_0_SEL_LAST || ev_type <= SPAV3_0_SEL_BASE)
			वापस -ENOENT;
		अवरोध;
	हाल 1:
		ev_type = PFM_OFFSET_MAGIC_1 + ev_type;
		अगर (ev_type >= SPAV3_1_SEL_LAST || ev_type <= SPAV3_1_SEL_BASE)
			वापस -ENOENT;
		अवरोध;
	हाल 2:
		ev_type = PFM_OFFSET_MAGIC_2 + ev_type;
		अगर (ev_type >= SPAV3_2_SEL_LAST || ev_type <= SPAV3_2_SEL_BASE)
			वापस -ENOENT;
		अवरोध;
	शेष:
		वापस -ENOENT;
	पूर्ण

	वापस ev_type;
पूर्ण

पूर्णांक
nds32_pmu_map_event(काष्ठा perf_event *event,
		    स्थिर अचिन्हित पूर्णांक (*event_map)[PERF_COUNT_HW_MAX],
		    स्थिर अचिन्हित पूर्णांक (*cache_map)
		    [PERF_COUNT_HW_CACHE_MAX]
		    [PERF_COUNT_HW_CACHE_OP_MAX]
		    [PERF_COUNT_HW_CACHE_RESULT_MAX], u32 raw_event_mask)
अणु
	u64 config = event->attr.config;

	चयन (event->attr.type) अणु
	हाल PERF_TYPE_HARDWARE:
		वापस nds32_pmu_map_hw_event(event_map, config);
	हाल PERF_TYPE_HW_CACHE:
		वापस nds32_pmu_map_cache_event(cache_map, config);
	हाल PERF_TYPE_RAW:
		वापस nds32_pmu_map_raw_event(raw_event_mask, config);
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक nds32_spav3_map_event(काष्ठा perf_event *event)
अणु
	वापस nds32_pmu_map_event(event, &nds32_pfm_perf_map,
				&nds32_pfm_perf_cache_map, SOFTWARE_EVENT_MASK);
पूर्ण

अटल अंतरभूत u32 nds32_pfm_getreset_flags(व्योम)
अणु
	/* Read overflow status */
	u32 val = __nds32__mfsr(NDS32_SR_PFM_CTL);
	u32 old_val = val;

	/* Write overflow bit to clear status, and others keep it 0 */
	u32 ov_flag = PFM_CTL_OVF[0] | PFM_CTL_OVF[1] | PFM_CTL_OVF[2];

	__nds32__mtsr(val | ov_flag, NDS32_SR_PFM_CTL);

	वापस old_val;
पूर्ण

अटल अंतरभूत पूर्णांक nds32_pfm_has_overflowed(u32 pfm)
अणु
	u32 ov_flag = PFM_CTL_OVF[0] | PFM_CTL_OVF[1] | PFM_CTL_OVF[2];

	वापस pfm & ov_flag;
पूर्ण

अटल अंतरभूत पूर्णांक nds32_pfm_counter_has_overflowed(u32 pfm, पूर्णांक idx)
अणु
	u32 mask = 0;

	चयन (idx) अणु
	हाल 0:
		mask = PFM_CTL_OVF[0];
		अवरोध;
	हाल 1:
		mask = PFM_CTL_OVF[1];
		अवरोध;
	हाल 2:
		mask = PFM_CTL_OVF[2];
		अवरोध;
	शेष:
		pr_err("%s index wrong\n", __func__);
		अवरोध;
	पूर्ण
	वापस pfm & mask;
पूर्ण

/*
 * Set the next IRQ period, based on the hwc->period_left value.
 * To be called with the event disabled in hw:
 */
पूर्णांक nds32_pmu_event_set_period(काष्ठा perf_event *event)
अणु
	काष्ठा nds32_pmu *nds32_pmu = to_nds32_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	s64 left = local64_पढ़ो(&hwc->period_left);
	s64 period = hwc->sample_period;
	पूर्णांक ret = 0;

	/* The period may have been changed by PERF_EVENT_IOC_PERIOD */
	अगर (unlikely(period != hwc->last_period))
		left = period - (hwc->last_period - left);

	अगर (unlikely(left <= -period)) अणु
		left = period;
		local64_set(&hwc->period_left, left);
		hwc->last_period = period;
		ret = 1;
	पूर्ण

	अगर (unlikely(left <= 0)) अणु
		left += period;
		local64_set(&hwc->period_left, left);
		hwc->last_period = period;
		ret = 1;
	पूर्ण

	अगर (left > (s64)nds32_pmu->max_period)
		left = nds32_pmu->max_period;

	/*
	 * The hw event starts counting from this event offset,
	 * mark it to be able to extract future "deltas":
	 */
	local64_set(&hwc->prev_count, (u64)(-left));

	nds32_pmu->ग_लिखो_counter(event, (u64)(-left) & nds32_pmu->max_period);

	perf_event_update_userpage(event);

	वापस ret;
पूर्ण

अटल irqवापस_t nds32_pmu_handle_irq(पूर्णांक irq_num, व्योम *dev)
अणु
	u32 pfm;
	काष्ठा perf_sample_data data;
	काष्ठा nds32_pmu *cpu_pmu = (काष्ठा nds32_pmu *)dev;
	काष्ठा pmu_hw_events *cpuc = cpu_pmu->get_hw_events();
	काष्ठा pt_regs *regs;
	पूर्णांक idx;
	/*
	 * Get and reset the IRQ flags
	 */
	pfm = nds32_pfm_getreset_flags();

	/*
	 * Did an overflow occur?
	 */
	अगर (!nds32_pfm_has_overflowed(pfm))
		वापस IRQ_NONE;

	/*
	 * Handle the counter(s) overflow(s)
	 */
	regs = get_irq_regs();

	nds32_pmu_stop(cpu_pmu);
	क्रम (idx = 0; idx < cpu_pmu->num_events; ++idx) अणु
		काष्ठा perf_event *event = cpuc->events[idx];
		काष्ठा hw_perf_event *hwc;

		/* Ignore अगर we करोn't have an event. */
		अगर (!event)
			जारी;

		/*
		 * We have a single पूर्णांकerrupt क्रम all counters. Check that
		 * each counter has overflowed beक्रमe we process it.
		 */
		अगर (!nds32_pfm_counter_has_overflowed(pfm, idx))
			जारी;

		hwc = &event->hw;
		nds32_pmu_event_update(event);
		perf_sample_data_init(&data, 0, hwc->last_period);
		अगर (!nds32_pmu_event_set_period(event))
			जारी;

		अगर (perf_event_overflow(event, &data, regs))
			cpu_pmu->disable(event);
	पूर्ण
	nds32_pmu_start(cpu_pmu);
	/*
	 * Handle the pending perf events.
	 *
	 * Note: this call *must* be run with पूर्णांकerrupts disabled. For
	 * platक्रमms that can have the PMU पूर्णांकerrupts उठाओd as an NMI, this
	 * will not work.
	 */
	irq_work_run();

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत पूर्णांक nds32_pfm_counter_valid(काष्ठा nds32_pmu *cpu_pmu, पूर्णांक idx)
अणु
	वापस ((idx >= 0) && (idx < cpu_pmu->num_events));
पूर्ण

अटल अंतरभूत पूर्णांक nds32_pfm_disable_counter(पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक val = __nds32__mfsr(NDS32_SR_PFM_CTL);
	u32 mask = 0;

	mask = PFM_CTL_EN[idx];
	val &= ~mask;
	val &= ~(PFM_CTL_OVF[0] | PFM_CTL_OVF[1] | PFM_CTL_OVF[2]);
	__nds32__mtsr_isb(val, NDS32_SR_PFM_CTL);
	वापस idx;
पूर्ण

/*
 * Add an event filter to a given event.
 */
अटल पूर्णांक nds32_pmu_set_event_filter(काष्ठा hw_perf_event *event,
				      काष्ठा perf_event_attr *attr)
अणु
	अचिन्हित दीर्घ config_base = 0;
	पूर्णांक idx = event->idx;
	अचिन्हित दीर्घ no_kernel_tracing = 0;
	अचिन्हित दीर्घ no_user_tracing = 0;
	/* If index is -1, करो not करो anything */
	अगर (idx == -1)
		वापस 0;

	no_kernel_tracing = PFM_CTL_KS[idx];
	no_user_tracing = PFM_CTL_KU[idx];
	/*
	 * Default: enable both kernel and user mode tracing.
	 */
	अगर (attr->exclude_user)
		config_base |= no_user_tracing;

	अगर (attr->exclude_kernel)
		config_base |= no_kernel_tracing;

	/*
	 * Install the filter पूर्णांकo config_base as this is used to
	 * स्थिरruct the event type.
	 */
	event->config_base |= config_base;
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम nds32_pfm_ग_लिखो_evtsel(पूर्णांक idx, u32 evnum)
अणु
	u32 offset = 0;
	u32 ori_val = __nds32__mfsr(NDS32_SR_PFM_CTL);
	u32 ev_mask = 0;
	u32 no_kernel_mask = 0;
	u32 no_user_mask = 0;
	u32 val;

	offset = PFM_CTL_OFFSEL[idx];
	/* Clear previous mode selection, and ग_लिखो new one */
	no_kernel_mask = PFM_CTL_KS[idx];
	no_user_mask = PFM_CTL_KU[idx];
	ori_val &= ~no_kernel_mask;
	ori_val &= ~no_user_mask;
	अगर (evnum & no_kernel_mask)
		ori_val |= no_kernel_mask;

	अगर (evnum & no_user_mask)
		ori_val |= no_user_mask;

	/* Clear previous event selection */
	ev_mask = PFM_CTL_SEL[idx];
	ori_val &= ~ev_mask;
	evnum &= SOFTWARE_EVENT_MASK;

	/* unकरो the linear mapping */
	evnum = get_converted_evet_hw_num(evnum);
	val = ori_val | (evnum << offset);
	val &= ~(PFM_CTL_OVF[0] | PFM_CTL_OVF[1] | PFM_CTL_OVF[2]);
	__nds32__mtsr_isb(val, NDS32_SR_PFM_CTL);
पूर्ण

अटल अंतरभूत पूर्णांक nds32_pfm_enable_counter(पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक val = __nds32__mfsr(NDS32_SR_PFM_CTL);
	u32 mask = 0;

	mask = PFM_CTL_EN[idx];
	val |= mask;
	val &= ~(PFM_CTL_OVF[0] | PFM_CTL_OVF[1] | PFM_CTL_OVF[2]);
	__nds32__mtsr_isb(val, NDS32_SR_PFM_CTL);
	वापस idx;
पूर्ण

अटल अंतरभूत पूर्णांक nds32_pfm_enable_पूर्णांकens(पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक val = __nds32__mfsr(NDS32_SR_PFM_CTL);
	u32 mask = 0;

	mask = PFM_CTL_IE[idx];
	val |= mask;
	val &= ~(PFM_CTL_OVF[0] | PFM_CTL_OVF[1] | PFM_CTL_OVF[2]);
	__nds32__mtsr_isb(val, NDS32_SR_PFM_CTL);
	वापस idx;
पूर्ण

अटल अंतरभूत पूर्णांक nds32_pfm_disable_पूर्णांकens(पूर्णांक idx)
अणु
	अचिन्हित पूर्णांक val = __nds32__mfsr(NDS32_SR_PFM_CTL);
	u32 mask = 0;

	mask = PFM_CTL_IE[idx];
	val &= ~mask;
	val &= ~(PFM_CTL_OVF[0] | PFM_CTL_OVF[1] | PFM_CTL_OVF[2]);
	__nds32__mtsr_isb(val, NDS32_SR_PFM_CTL);
	वापस idx;
पूर्ण

अटल पूर्णांक event_requires_mode_exclusion(काष्ठा perf_event_attr *attr)
अणु
	/* Other modes NDS32 करोes not support */
	वापस attr->exclude_user || attr->exclude_kernel;
पूर्ण

अटल व्योम nds32_pmu_enable_event(काष्ठा perf_event *event)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक evnum = 0;
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा nds32_pmu *cpu_pmu = to_nds32_pmu(event->pmu);
	काष्ठा pmu_hw_events *events = cpu_pmu->get_hw_events();
	पूर्णांक idx = hwc->idx;

	अगर (!nds32_pfm_counter_valid(cpu_pmu, idx)) अणु
		pr_err("CPU enabling wrong pfm counter IRQ enable\n");
		वापस;
	पूर्ण

	/*
	 * Enable counter and पूर्णांकerrupt, and set the counter to count
	 * the event that we're पूर्णांकerested in.
	 */
	raw_spin_lock_irqsave(&events->pmu_lock, flags);

	/*
	 * Disable counter
	 */
	nds32_pfm_disable_counter(idx);

	/*
	 * Check whether we need to exclude the counter from certain modes.
	 */
	अगर ((!cpu_pmu->set_event_filter ||
	     cpu_pmu->set_event_filter(hwc, &event->attr)) &&
	     event_requires_mode_exclusion(&event->attr)) अणु
		pr_notice
		("NDS32 performance counters do not support mode exclusion\n");
		hwc->config_base = 0;
	पूर्ण
	/* Write event */
	evnum = hwc->config_base;
	nds32_pfm_ग_लिखो_evtsel(idx, evnum);

	/*
	 * Enable पूर्णांकerrupt क्रम this counter
	 */
	nds32_pfm_enable_पूर्णांकens(idx);

	/*
	 * Enable counter
	 */
	nds32_pfm_enable_counter(idx);

	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल व्योम nds32_pmu_disable_event(काष्ठा perf_event *event)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा nds32_pmu *cpu_pmu = to_nds32_pmu(event->pmu);
	काष्ठा pmu_hw_events *events = cpu_pmu->get_hw_events();
	पूर्णांक idx = hwc->idx;

	अगर (!nds32_pfm_counter_valid(cpu_pmu, idx)) अणु
		pr_err("CPU disabling wrong pfm counter IRQ enable %d\n", idx);
		वापस;
	पूर्ण

	/*
	 * Disable counter and पूर्णांकerrupt
	 */
	raw_spin_lock_irqsave(&events->pmu_lock, flags);

	/*
	 * Disable counter
	 */
	nds32_pfm_disable_counter(idx);

	/*
	 * Disable पूर्णांकerrupt क्रम this counter
	 */
	nds32_pfm_disable_पूर्णांकens(idx);

	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल अंतरभूत u32 nds32_pmu_पढ़ो_counter(काष्ठा perf_event *event)
अणु
	काष्ठा nds32_pmu *cpu_pmu = to_nds32_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;
	u32 count = 0;

	अगर (!nds32_pfm_counter_valid(cpu_pmu, idx)) अणु
		pr_err("CPU reading wrong counter %d\n", idx);
	पूर्ण अन्यथा अणु
		चयन (idx) अणु
		हाल PFMC0:
			count = __nds32__mfsr(NDS32_SR_PFMC0);
			अवरोध;
		हाल PFMC1:
			count = __nds32__mfsr(NDS32_SR_PFMC1);
			अवरोध;
		हाल PFMC2:
			count = __nds32__mfsr(NDS32_SR_PFMC2);
			अवरोध;
		शेष:
			pr_err
			    ("%s: CPU has no performance counters %d\n",
			     __func__, idx);
		पूर्ण
	पूर्ण
	वापस count;
पूर्ण

अटल अंतरभूत व्योम nds32_pmu_ग_लिखो_counter(काष्ठा perf_event *event, u32 value)
अणु
	काष्ठा nds32_pmu *cpu_pmu = to_nds32_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	अगर (!nds32_pfm_counter_valid(cpu_pmu, idx)) अणु
		pr_err("CPU writing wrong counter %d\n", idx);
	पूर्ण अन्यथा अणु
		चयन (idx) अणु
		हाल PFMC0:
			__nds32__mtsr_isb(value, NDS32_SR_PFMC0);
			अवरोध;
		हाल PFMC1:
			__nds32__mtsr_isb(value, NDS32_SR_PFMC1);
			अवरोध;
		हाल PFMC2:
			__nds32__mtsr_isb(value, NDS32_SR_PFMC2);
			अवरोध;
		शेष:
			pr_err
			    ("%s: CPU has no performance counters %d\n",
			     __func__, idx);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक nds32_pmu_get_event_idx(काष्ठा pmu_hw_events *cpuc,
				   काष्ठा perf_event *event)
अणु
	पूर्णांक idx;
	काष्ठा hw_perf_event *hwc = &event->hw;
	/*
	 * Current implementation maps cycles, inकाष्ठाion count and cache-miss
	 * to specअगरic counter.
	 * However, multiple of the 3 counters are able to count these events.
	 *
	 *
	 * SOFTWARE_EVENT_MASK mask क्रम getting event num ,
	 * This is defined by Jia-Rung, you can change the polocies.
	 * However, करो not exceed 8 bits. This is hardware specअगरic.
	 * The last number is SPAv3_2_SEL_LAST.
	 */
	अचिन्हित दीर्घ evtype = hwc->config_base & SOFTWARE_EVENT_MASK;

	idx = get_converted_event_idx(evtype);
	/*
	 * Try to get the counter क्रम correpsonding event
	 */
	अगर (evtype == SPAV3_0_SEL_TOTAL_CYCLES) अणु
		अगर (!test_and_set_bit(idx, cpuc->used_mask))
			वापस idx;
		अगर (!test_and_set_bit(NDS32_IDX_COUNTER0, cpuc->used_mask))
			वापस NDS32_IDX_COUNTER0;
		अगर (!test_and_set_bit(NDS32_IDX_COUNTER1, cpuc->used_mask))
			वापस NDS32_IDX_COUNTER1;
	पूर्ण अन्यथा अगर (evtype == SPAV3_1_SEL_COMPLETED_INSTRUCTION) अणु
		अगर (!test_and_set_bit(idx, cpuc->used_mask))
			वापस idx;
		अन्यथा अगर (!test_and_set_bit(NDS32_IDX_COUNTER1, cpuc->used_mask))
			वापस NDS32_IDX_COUNTER1;
		अन्यथा अगर (!test_and_set_bit
			 (NDS32_IDX_CYCLE_COUNTER, cpuc->used_mask))
			वापस NDS32_IDX_CYCLE_COUNTER;
	पूर्ण अन्यथा अणु
		अगर (!test_and_set_bit(idx, cpuc->used_mask))
			वापस idx;
	पूर्ण
	वापस -EAGAIN;
पूर्ण

अटल व्योम nds32_pmu_start(काष्ठा nds32_pmu *cpu_pmu)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;
	काष्ठा pmu_hw_events *events = cpu_pmu->get_hw_events();

	raw_spin_lock_irqsave(&events->pmu_lock, flags);

	/* Enable all counters , NDS PFM has 3 counters */
	val = __nds32__mfsr(NDS32_SR_PFM_CTL);
	val |= (PFM_CTL_EN[0] | PFM_CTL_EN[1] | PFM_CTL_EN[2]);
	val &= ~(PFM_CTL_OVF[0] | PFM_CTL_OVF[1] | PFM_CTL_OVF[2]);
	__nds32__mtsr_isb(val, NDS32_SR_PFM_CTL);

	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल व्योम nds32_pmu_stop(काष्ठा nds32_pmu *cpu_pmu)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;
	काष्ठा pmu_hw_events *events = cpu_pmu->get_hw_events();

	raw_spin_lock_irqsave(&events->pmu_lock, flags);

	/* Disable all counters , NDS PFM has 3 counters */
	val = __nds32__mfsr(NDS32_SR_PFM_CTL);
	val &= ~(PFM_CTL_EN[0] | PFM_CTL_EN[1] | PFM_CTL_EN[2]);
	val &= ~(PFM_CTL_OVF[0] | PFM_CTL_OVF[1] | PFM_CTL_OVF[2]);
	__nds32__mtsr_isb(val, NDS32_SR_PFM_CTL);

	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
पूर्ण

अटल व्योम nds32_pmu_reset(व्योम *info)
अणु
	u32 val = 0;

	val |= (PFM_CTL_OVF[0] | PFM_CTL_OVF[1] | PFM_CTL_OVF[2]);
	__nds32__mtsr(val, NDS32_SR_PFM_CTL);
	__nds32__mtsr(0, NDS32_SR_PFM_CTL);
	__nds32__mtsr(0, NDS32_SR_PFMC0);
	__nds32__mtsr(0, NDS32_SR_PFMC1);
	__nds32__mtsr(0, NDS32_SR_PFMC2);
पूर्ण

अटल व्योम nds32_pmu_init(काष्ठा nds32_pmu *cpu_pmu)
अणु
	cpu_pmu->handle_irq = nds32_pmu_handle_irq;
	cpu_pmu->enable = nds32_pmu_enable_event;
	cpu_pmu->disable = nds32_pmu_disable_event;
	cpu_pmu->पढ़ो_counter = nds32_pmu_पढ़ो_counter;
	cpu_pmu->ग_लिखो_counter = nds32_pmu_ग_लिखो_counter;
	cpu_pmu->get_event_idx = nds32_pmu_get_event_idx;
	cpu_pmu->start = nds32_pmu_start;
	cpu_pmu->stop = nds32_pmu_stop;
	cpu_pmu->reset = nds32_pmu_reset;
	cpu_pmu->max_period = 0xFFFFFFFF;	/* Maximum counts */
पूर्ण;

अटल u32 nds32_पढ़ो_num_pfm_events(व्योम)
अणु
	/* NDS32 SPAv3 PMU support 3 counter */
	वापस 3;
पूर्ण

अटल पूर्णांक device_pmu_init(काष्ठा nds32_pmu *cpu_pmu)
अणु
	nds32_pmu_init(cpu_pmu);
	/*
	 * This name should be devive-specअगरic name, whatever you like :)
	 * I think "PMU" will be a good generic name.
	 */
	cpu_pmu->name = "nds32v3-pmu";
	cpu_pmu->map_event = nds32_spav3_map_event;
	cpu_pmu->num_events = nds32_पढ़ो_num_pfm_events();
	cpu_pmu->set_event_filter = nds32_pmu_set_event_filter;
	वापस 0;
पूर्ण

/*
 * CPU PMU identअगरication and probing.
 */
अटल पूर्णांक probe_current_pmu(काष्ठा nds32_pmu *pmu)
अणु
	पूर्णांक ret;

	get_cpu();
	ret = -ENODEV;
	/*
	 * If ther are various CPU types with its own PMU, initialize with
	 *
	 * the corresponding one
	 */
	device_pmu_init(pmu);
	put_cpu();
	वापस ret;
पूर्ण

अटल व्योम nds32_pmu_enable(काष्ठा pmu *pmu)
अणु
	काष्ठा nds32_pmu *nds32_pmu = to_nds32_pmu(pmu);
	काष्ठा pmu_hw_events *hw_events = nds32_pmu->get_hw_events();
	पूर्णांक enabled = biपंचांगap_weight(hw_events->used_mask,
				    nds32_pmu->num_events);

	अगर (enabled)
		nds32_pmu->start(nds32_pmu);
पूर्ण

अटल व्योम nds32_pmu_disable(काष्ठा pmu *pmu)
अणु
	काष्ठा nds32_pmu *nds32_pmu = to_nds32_pmu(pmu);

	nds32_pmu->stop(nds32_pmu);
पूर्ण

अटल व्योम nds32_pmu_release_hardware(काष्ठा nds32_pmu *nds32_pmu)
अणु
	nds32_pmu->मुक्त_irq(nds32_pmu);
	pm_runसमय_put_sync(&nds32_pmu->plat_device->dev);
पूर्ण

अटल irqवापस_t nds32_pmu_dispatch_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा nds32_pmu *nds32_pmu = (काष्ठा nds32_pmu *)dev;
	पूर्णांक ret;
	u64 start_घड़ी, finish_घड़ी;

	start_घड़ी = local_घड़ी();
	ret = nds32_pmu->handle_irq(irq, dev);
	finish_घड़ी = local_घड़ी();

	perf_sample_event_took(finish_घड़ी - start_घड़ी);
	वापस ret;
पूर्ण

अटल पूर्णांक nds32_pmu_reserve_hardware(काष्ठा nds32_pmu *nds32_pmu)
अणु
	पूर्णांक err;
	काष्ठा platक्रमm_device *pmu_device = nds32_pmu->plat_device;

	अगर (!pmu_device)
		वापस -ENODEV;

	pm_runसमय_get_sync(&pmu_device->dev);
	err = nds32_pmu->request_irq(nds32_pmu, nds32_pmu_dispatch_irq);
	अगर (err) अणु
		nds32_pmu_release_hardware(nds32_pmu);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
validate_event(काष्ठा pmu *pmu, काष्ठा pmu_hw_events *hw_events,
	       काष्ठा perf_event *event)
अणु
	काष्ठा nds32_pmu *nds32_pmu = to_nds32_pmu(event->pmu);

	अगर (is_software_event(event))
		वापस 1;

	अगर (event->pmu != pmu)
		वापस 0;

	अगर (event->state < PERF_EVENT_STATE_OFF)
		वापस 1;

	अगर (event->state == PERF_EVENT_STATE_OFF && !event->attr.enable_on_exec)
		वापस 1;

	वापस nds32_pmu->get_event_idx(hw_events, event) >= 0;
पूर्ण

अटल पूर्णांक validate_group(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event *sibling, *leader = event->group_leader;
	काष्ठा pmu_hw_events fake_pmu;
	DECLARE_BITMAP(fake_used_mask, MAX_COUNTERS);
	/*
	 * Initialize the fake PMU. We only need to populate the
	 * used_mask क्रम the purposes of validation.
	 */
	स_रखो(fake_used_mask, 0, माप(fake_used_mask));

	अगर (!validate_event(event->pmu, &fake_pmu, leader))
		वापस -EINVAL;

	क्रम_each_sibling_event(sibling, leader) अणु
		अगर (!validate_event(event->pmu, &fake_pmu, sibling))
			वापस -EINVAL;
	पूर्ण

	अगर (!validate_event(event->pmu, &fake_pmu, event))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक __hw_perf_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा nds32_pmu *nds32_pmu = to_nds32_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक mapping;

	mapping = nds32_pmu->map_event(event);

	अगर (mapping < 0) अणु
		pr_debug("event %x:%llx not supported\n", event->attr.type,
			 event->attr.config);
		वापस mapping;
	पूर्ण

	/*
	 * We करोn't assign an index until we actually place the event onto
	 * hardware. Use -1 to signअगरy that we haven't decided where to put it
	 * yet. For SMP प्रणालीs, each core has it's own PMU so we can't करो any
	 * clever allocation or स्थिरraपूर्णांकs checking at this poपूर्णांक.
	 */
	hwc->idx = -1;
	hwc->config_base = 0;
	hwc->config = 0;
	hwc->event_base = 0;

	/*
	 * Check whether we need to exclude the counter from certain modes.
	 */
	अगर ((!nds32_pmu->set_event_filter ||
	     nds32_pmu->set_event_filter(hwc, &event->attr)) &&
	    event_requires_mode_exclusion(&event->attr)) अणु
		pr_debug
			("NDS performance counters do not support mode exclusion\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/*
	 * Store the event encoding पूर्णांकo the config_base field.
	 */
	hwc->config_base |= (अचिन्हित दीर्घ)mapping;

	अगर (!hwc->sample_period) अणु
		/*
		 * For non-sampling runs, limit the sample_period to half
		 * of the counter width. That way, the new counter value
		 * is far less likely to overtake the previous one unless
		 * you have some serious IRQ latency issues.
		 */
		hwc->sample_period = nds32_pmu->max_period >> 1;
		hwc->last_period = hwc->sample_period;
		local64_set(&hwc->period_left, hwc->sample_period);
	पूर्ण

	अगर (event->group_leader != event) अणु
		अगर (validate_group(event) != 0)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nds32_pmu_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा nds32_pmu *nds32_pmu = to_nds32_pmu(event->pmu);
	पूर्णांक err = 0;
	atomic_t *active_events = &nds32_pmu->active_events;

	/* करोes not support taken branch sampling */
	अगर (has_branch_stack(event))
		वापस -EOPNOTSUPP;

	अगर (nds32_pmu->map_event(event) == -ENOENT)
		वापस -ENOENT;

	अगर (!atomic_inc_not_zero(active_events)) अणु
		अगर (atomic_पढ़ो(active_events) == 0) अणु
			/* Register irq handler */
			err = nds32_pmu_reserve_hardware(nds32_pmu);
		पूर्ण

		अगर (!err)
			atomic_inc(active_events);
	पूर्ण

	अगर (err)
		वापस err;

	err = __hw_perf_event_init(event);

	वापस err;
पूर्ण

अटल व्योम nds32_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा nds32_pmu *nds32_pmu = to_nds32_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	/*
	 * NDS pmu always has to reprogram the period, so ignore
	 * PERF_EF_RELOAD, see the comment below.
	 */
	अगर (flags & PERF_EF_RELOAD)
		WARN_ON_ONCE(!(hwc->state & PERF_HES_UPTODATE));

	hwc->state = 0;
	/* Set the period क्रम the event. */
	nds32_pmu_event_set_period(event);

	nds32_pmu->enable(event);
पूर्ण

अटल पूर्णांक nds32_pmu_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा nds32_pmu *nds32_pmu = to_nds32_pmu(event->pmu);
	काष्ठा pmu_hw_events *hw_events = nds32_pmu->get_hw_events();
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx;
	पूर्णांक err = 0;

	perf_pmu_disable(event->pmu);

	/* If we करोn't have a space क्रम the counter then finish early. */
	idx = nds32_pmu->get_event_idx(hw_events, event);
	अगर (idx < 0) अणु
		err = idx;
		जाओ out;
	पूर्ण

	/*
	 * If there is an event in the counter we are going to use then make
	 * sure it is disabled.
	 */
	event->hw.idx = idx;
	nds32_pmu->disable(event);
	hw_events->events[idx] = event;

	hwc->state = PERF_HES_STOPPED | PERF_HES_UPTODATE;
	अगर (flags & PERF_EF_START)
		nds32_start(event, PERF_EF_RELOAD);

	/* Propagate our changes to the userspace mapping. */
	perf_event_update_userpage(event);

out:
	perf_pmu_enable(event->pmu);
	वापस err;
पूर्ण

u64 nds32_pmu_event_update(काष्ठा perf_event *event)
अणु
	काष्ठा nds32_pmu *nds32_pmu = to_nds32_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 delta, prev_raw_count, new_raw_count;

again:
	prev_raw_count = local64_पढ़ो(&hwc->prev_count);
	new_raw_count = nds32_pmu->पढ़ो_counter(event);

	अगर (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
			    new_raw_count) != prev_raw_count) अणु
		जाओ again;
	पूर्ण
	/*
	 * Whether overflow or not, "unsigned substraction"
	 * will always get their delta
	 */
	delta = (new_raw_count - prev_raw_count) & nds32_pmu->max_period;

	local64_add(delta, &event->count);
	local64_sub(delta, &hwc->period_left);

	वापस new_raw_count;
पूर्ण

अटल व्योम nds32_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा nds32_pmu *nds32_pmu = to_nds32_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	/*
	 * NDS pmu always has to update the counter, so ignore
	 * PERF_EF_UPDATE, see comments in nds32_start().
	 */
	अगर (!(hwc->state & PERF_HES_STOPPED)) अणु
		nds32_pmu->disable(event);
		nds32_pmu_event_update(event);
		hwc->state |= PERF_HES_STOPPED | PERF_HES_UPTODATE;
	पूर्ण
पूर्ण

अटल व्योम nds32_pmu_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा nds32_pmu *nds32_pmu = to_nds32_pmu(event->pmu);
	काष्ठा pmu_hw_events *hw_events = nds32_pmu->get_hw_events();
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	nds32_stop(event, PERF_EF_UPDATE);
	hw_events->events[idx] = शून्य;
	clear_bit(idx, hw_events->used_mask);

	perf_event_update_userpage(event);
पूर्ण

अटल व्योम nds32_pmu_पढ़ो(काष्ठा perf_event *event)
अणु
	nds32_pmu_event_update(event);
पूर्ण

/* Please refer to SPAv3 क्रम more hardware specअगरic details */
PMU_FORMAT_ATTR(event, "config:0-63");

अटल काष्ठा attribute *nds32_arch_क्रमmats_attr[] = अणु
	&क्रमmat_attr_event.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group nds32_pmu_क्रमmat_group = अणु
	.name = "format",
	.attrs = nds32_arch_क्रमmats_attr,
पूर्ण;

अटल sमाप_प्रकार nds32_pmu_cpumask_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	वापस 0;
पूर्ण

अटल DEVICE_ATTR(cpus, 0444, nds32_pmu_cpumask_show, शून्य);

अटल काष्ठा attribute *nds32_pmu_common_attrs[] = अणु
	&dev_attr_cpus.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group nds32_pmu_common_group = अणु
	.attrs = nds32_pmu_common_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *nds32_pmu_attr_groups[] = अणु
	&nds32_pmu_क्रमmat_group,
	&nds32_pmu_common_group,
	शून्य,
पूर्ण;

अटल व्योम nds32_init(काष्ठा nds32_pmu *nds32_pmu)
अणु
	atomic_set(&nds32_pmu->active_events, 0);

	nds32_pmu->pmu = (काष्ठा pmu) अणु
		.pmu_enable = nds32_pmu_enable,
		.pmu_disable = nds32_pmu_disable,
		.attr_groups = nds32_pmu_attr_groups,
		.event_init = nds32_pmu_event_init,
		.add = nds32_pmu_add,
		.del = nds32_pmu_del,
		.start = nds32_start,
		.stop = nds32_stop,
		.पढ़ो = nds32_pmu_पढ़ो,
	पूर्ण;
पूर्ण

पूर्णांक nds32_pmu_रेजिस्टर(काष्ठा nds32_pmu *nds32_pmu, पूर्णांक type)
अणु
	nds32_init(nds32_pmu);
	pm_runसमय_enable(&nds32_pmu->plat_device->dev);
	pr_info("enabled with %s PMU driver, %d counters available\n",
		nds32_pmu->name, nds32_pmu->num_events);
	वापस perf_pmu_रेजिस्टर(&nds32_pmu->pmu, nds32_pmu->name, type);
पूर्ण

अटल काष्ठा pmu_hw_events *cpu_pmu_get_cpu_events(व्योम)
अणु
	वापस this_cpu_ptr(&cpu_hw_events);
पूर्ण

अटल पूर्णांक cpu_pmu_request_irq(काष्ठा nds32_pmu *cpu_pmu, irq_handler_t handler)
अणु
	पूर्णांक err, irq, irqs;
	काष्ठा platक्रमm_device *pmu_device = cpu_pmu->plat_device;

	अगर (!pmu_device)
		वापस -ENODEV;

	irqs = min(pmu_device->num_resources, num_possible_cpus());
	अगर (irqs < 1) अणु
		pr_err("no irqs for PMUs defined\n");
		वापस -ENODEV;
	पूर्ण

	irq = platक्रमm_get_irq(pmu_device, 0);
	err = request_irq(irq, handler, IRQF_NOBALANCING, "nds32-pfm",
			  cpu_pmu);
	अगर (err) अणु
		pr_err("unable to request IRQ%d for NDS PMU counters\n",
		       irq);
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम cpu_pmu_मुक्त_irq(काष्ठा nds32_pmu *cpu_pmu)
अणु
	पूर्णांक irq;
	काष्ठा platक्रमm_device *pmu_device = cpu_pmu->plat_device;

	irq = platक्रमm_get_irq(pmu_device, 0);
	अगर (irq >= 0)
		मुक्त_irq(irq, cpu_pmu);
पूर्ण

अटल व्योम cpu_pmu_init(काष्ठा nds32_pmu *cpu_pmu)
अणु
	पूर्णांक cpu;
	काष्ठा pmu_hw_events *events = &per_cpu(cpu_hw_events, cpu);

	raw_spin_lock_init(&events->pmu_lock);

	cpu_pmu->get_hw_events = cpu_pmu_get_cpu_events;
	cpu_pmu->request_irq = cpu_pmu_request_irq;
	cpu_pmu->मुक्त_irq = cpu_pmu_मुक्त_irq;

	/* Ensure the PMU has sane values out of reset. */
	अगर (cpu_pmu->reset)
		on_each_cpu(cpu_pmu->reset, cpu_pmu, 1);
पूर्ण

अटल स्थिर काष्ठा of_device_id cpu_pmu_of_device_ids[] = अणु
	अणु.compatible = "andestech,nds32v3-pmu",
	 .data = device_pmu_initपूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक cpu_pmu_device_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *of_id;
	पूर्णांक (*init_fn)(काष्ठा nds32_pmu *nds32_pmu);
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा nds32_pmu *pmu;
	पूर्णांक ret = -ENODEV;

	अगर (cpu_pmu) अणु
		pr_notice("[perf] attempt to register multiple PMU devices!\n");
		वापस -ENOSPC;
	पूर्ण

	pmu = kzalloc(माप(*pmu), GFP_KERNEL);
	अगर (!pmu)
		वापस -ENOMEM;

	of_id = of_match_node(cpu_pmu_of_device_ids, pdev->dev.of_node);
	अगर (node && of_id) अणु
		init_fn = of_id->data;
		ret = init_fn(pmu);
	पूर्ण अन्यथा अणु
		ret = probe_current_pmu(pmu);
	पूर्ण

	अगर (ret) अणु
		pr_notice("[perf] failed to probe PMU!\n");
		जाओ out_मुक्त;
	पूर्ण

	cpu_pmu = pmu;
	cpu_pmu->plat_device = pdev;
	cpu_pmu_init(cpu_pmu);
	ret = nds32_pmu_रेजिस्टर(cpu_pmu, PERF_TYPE_RAW);

	अगर (!ret)
		वापस 0;

out_मुक्त:
	pr_notice("[perf] failed to register PMU devices!\n");
	kमुक्त(pmu);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver cpu_pmu_driver = अणु
	.driver = अणु
		   .name = "nds32-pfm",
		   .of_match_table = cpu_pmu_of_device_ids,
		   पूर्ण,
	.probe = cpu_pmu_device_probe,
	.id_table = cpu_pmu_plat_device_ids,
पूर्ण;

अटल पूर्णांक __init रेजिस्टर_pmu_driver(व्योम)
अणु
	पूर्णांक err = 0;

	err = platक्रमm_driver_रेजिस्टर(&cpu_pmu_driver);
	अगर (err)
		pr_notice("[perf] PMU initialization failed\n");
	अन्यथा
		pr_notice("[perf] PMU initialization done\n");

	वापस err;
पूर्ण

device_initcall(रेजिस्टर_pmu_driver);

/*
 * References: arch/nds32/kernel/traps.c:__dump()
 * You will need to know the NDS ABI first.
 */
अटल पूर्णांक unwind_frame_kernel(काष्ठा stackframe *frame)
अणु
	पूर्णांक graph = 0;
#अगर_घोषित CONFIG_FRAME_POINTER
	/* 0x3 means misalignment */
	अगर (!kstack_end((व्योम *)frame->fp) &&
	    !((अचिन्हित दीर्घ)frame->fp & 0x3) &&
	    ((अचिन्हित दीर्घ)frame->fp >= TASK_SIZE)) अणु
		/*
		 *	The array index is based on the ABI, the below graph
		 *	illustrate the reasons.
		 *	Function call procedure: "smw" and "lmw" will always
		 *	update SP and FP क्रम you स्वतःmatically.
		 *
		 *	Stack                                 Relative Address
		 *	|  |                                          0
		 *	----
		 *	|LP| <-- SP(beक्रमe smw)  <-- FP(after smw)   -1
		 *	----
		 *	|FP|                                         -2
		 *	----
		 *	|  | <-- SP(after smw)                       -3
		 */
		frame->lp = ((अचिन्हित दीर्घ *)frame->fp)[-1];
		frame->fp = ((अचिन्हित दीर्घ *)frame->fp)[FP_OFFSET];
		/* make sure CONFIG_FUNCTION_GRAPH_TRACER is turned on */
		अगर (__kernel_text_address(frame->lp))
			frame->lp = ftrace_graph_ret_addr
						(शून्य, &graph, frame->lp, शून्य);

		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -EPERM;
	पूर्ण
#अन्यथा
	/*
	 * You can refer to arch/nds32/kernel/traps.c:__dump()
	 * Treat "sp" as "fp", but the "sp" is one frame ahead of "fp".
	 * And, the "sp" is not always correct.
	 *
	 *   Stack                                 Relative Address
	 *   |  |                                          0
	 *   ----
	 *   |LP| <-- SP(beक्रमe smw)                      -1
	 *   ----
	 *   |  | <-- SP(after smw)                       -2
	 *   ----
	 */
	अगर (!kstack_end((व्योम *)frame->sp)) अणु
		frame->lp = ((अचिन्हित दीर्घ *)frame->sp)[1];
		/* TODO: How to deal with the value in first
		 * "sp" is not correct?
		 */
		अगर (__kernel_text_address(frame->lp))
			frame->lp = ftrace_graph_ret_addr
						(tsk, &graph, frame->lp, शून्य);

		frame->sp = ((अचिन्हित दीर्घ *)frame->sp) + 1;

		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -EPERM;
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल व्योम notrace
walk_stackframe(काष्ठा stackframe *frame,
		पूर्णांक (*fn_record)(काष्ठा stackframe *, व्योम *),
		व्योम *data)
अणु
	जबतक (1) अणु
		पूर्णांक ret;

		अगर (fn_record(frame, data))
			अवरोध;

		ret = unwind_frame_kernel(frame);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
पूर्ण

/*
 * Gets called by walk_stackframe() क्रम every stackframe. This will be called
 * whist unwinding the stackframe and is like a subroutine वापस so we use
 * the PC.
 */
अटल पूर्णांक callchain_trace(काष्ठा stackframe *fr, व्योम *data)
अणु
	काष्ठा perf_callchain_entry_ctx *entry = data;

	perf_callchain_store(entry, fr->lp);
	वापस 0;
पूर्ण

/*
 * Get the वापस address क्रम a single stackframe and वापस a poपूर्णांकer to the
 * next frame tail.
 */
अटल अचिन्हित दीर्घ
user_backtrace(काष्ठा perf_callchain_entry_ctx *entry, अचिन्हित दीर्घ fp)
अणु
	काष्ठा frame_tail buftail;
	अचिन्हित दीर्घ lp = 0;
	अचिन्हित दीर्घ *user_frame_tail =
		(अचिन्हित दीर्घ *)(fp - (अचिन्हित दीर्घ)माप(buftail));

	/* Check accessibility of one काष्ठा frame_tail beyond */
	अगर (!access_ok(user_frame_tail, माप(buftail)))
		वापस 0;
	अगर (__copy_from_user_inatomic
		(&buftail, user_frame_tail, माप(buftail)))
		वापस 0;

	/*
	 * Refer to unwind_frame_kernel() क्रम more illurstration
	 */
	lp = buftail.stack_lp;  /* ((अचिन्हित दीर्घ *)fp)[-1] */
	fp = buftail.stack_fp;  /* ((अचिन्हित दीर्घ *)fp)[FP_OFFSET] */
	perf_callchain_store(entry, lp);
	वापस fp;
पूर्ण

अटल अचिन्हित दीर्घ
user_backtrace_opt_size(काष्ठा perf_callchain_entry_ctx *entry,
			अचिन्हित दीर्घ fp)
अणु
	काष्ठा frame_tail_opt_size buftail;
	अचिन्हित दीर्घ lp = 0;

	अचिन्हित दीर्घ *user_frame_tail =
		(अचिन्हित दीर्घ *)(fp - (अचिन्हित दीर्घ)माप(buftail));

	/* Check accessibility of one काष्ठा frame_tail beyond */
	अगर (!access_ok(user_frame_tail, माप(buftail)))
		वापस 0;
	अगर (__copy_from_user_inatomic
		(&buftail, user_frame_tail, माप(buftail)))
		वापस 0;

	/*
	 * Refer to unwind_frame_kernel() क्रम more illurstration
	 */
	lp = buftail.stack_lp;  /* ((अचिन्हित दीर्घ *)fp)[-1] */
	fp = buftail.stack_fp;  /* ((अचिन्हित दीर्घ *)fp)[FP_OFFSET] */

	perf_callchain_store(entry, lp);
	वापस fp;
पूर्ण

/*
 * This will be called when the target is in user mode
 * This function will only be called when we use
 * "PERF_SAMPLE_CALLCHAIN" in
 * kernel/events/core.c:perf_prepare_sample()
 *
 * How to trigger perf_callchain_[user/kernel] :
 * $ perf record -e cpu-घड़ी --call-graph fp ./program
 * $ perf report --call-graph
 */
अचिन्हित दीर्घ leaf_fp;
व्योम
perf_callchain_user(काष्ठा perf_callchain_entry_ctx *entry,
		    काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ fp = 0;
	अचिन्हित दीर्घ gp = 0;
	अचिन्हित दीर्घ lp = 0;
	अचिन्हित दीर्घ sp = 0;
	अचिन्हित दीर्घ *user_frame_tail;

	leaf_fp = 0;

	अगर (perf_guest_cbs && perf_guest_cbs->is_in_guest()) अणु
		/* We करोn't support guest os callchain now */
		वापस;
	पूर्ण

	perf_callchain_store(entry, regs->ipc);
	fp = regs->fp;
	gp = regs->gp;
	lp = regs->lp;
	sp = regs->sp;
	अगर (entry->nr < PERF_MAX_STACK_DEPTH &&
	    (अचिन्हित दीर्घ)fp && !((अचिन्हित दीर्घ)fp & 0x7) && fp > sp) अणु
		user_frame_tail =
			(अचिन्हित दीर्घ *)(fp - (अचिन्हित दीर्घ)माप(fp));

		अगर (!access_ok(user_frame_tail, माप(fp)))
			वापस;

		अगर (__copy_from_user_inatomic
			(&leaf_fp, user_frame_tail, माप(fp)))
			वापस;

		अगर (leaf_fp == lp) अणु
			/*
			 * Maybe this is non leaf function
			 * with optimize क्रम size,
			 * or maybe this is the function
			 * with optimize क्रम size
			 */
			काष्ठा frame_tail buftail;

			user_frame_tail =
				(अचिन्हित दीर्घ *)(fp -
					(अचिन्हित दीर्घ)माप(buftail));

			अगर (!access_ok(user_frame_tail, माप(buftail)))
				वापस;

			अगर (__copy_from_user_inatomic
				(&buftail, user_frame_tail, माप(buftail)))
				वापस;

			अगर (buftail.stack_fp == gp) अणु
				/* non leaf function with optimize
				 * क्रम size condition
				 */
				काष्ठा frame_tail_opt_size buftail_opt_size;

				user_frame_tail =
					(अचिन्हित दीर्घ *)(fp - (अचिन्हित दीर्घ)
						माप(buftail_opt_size));

				अगर (!access_ok(user_frame_tail,
					       माप(buftail_opt_size)))
					वापस;

				अगर (__copy_from_user_inatomic
				   (&buftail_opt_size, user_frame_tail,
				   माप(buftail_opt_size)))
					वापस;

				perf_callchain_store(entry, lp);
				fp = buftail_opt_size.stack_fp;

				जबतक ((entry->nr < PERF_MAX_STACK_DEPTH) &&
				       (अचिन्हित दीर्घ)fp &&
						!((अचिन्हित दीर्घ)fp & 0x7) &&
						fp > sp) अणु
					sp = fp;
					fp = user_backtrace_opt_size(entry, fp);
				पूर्ण

			पूर्ण अन्यथा अणु
				/* this is the function
				 * without optimize क्रम size
				 */
				fp = buftail.stack_fp;
				perf_callchain_store(entry, lp);
				जबतक ((entry->nr < PERF_MAX_STACK_DEPTH) &&
				       (अचिन्हित दीर्घ)fp &&
						!((अचिन्हित दीर्घ)fp & 0x7) &&
						fp > sp) अणु
					sp = fp;
					fp = user_backtrace(entry, fp);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/* this is leaf function */
			fp = leaf_fp;
			perf_callchain_store(entry, lp);

			/* previous function callcahin  */
			जबतक ((entry->nr < PERF_MAX_STACK_DEPTH) &&
			       (अचिन्हित दीर्घ)fp &&
				   !((अचिन्हित दीर्घ)fp & 0x7) && fp > sp) अणु
				sp = fp;
				fp = user_backtrace(entry, fp);
			पूर्ण
		पूर्ण
		वापस;
	पूर्ण
पूर्ण

/* This will be called when the target is in kernel mode */
व्योम
perf_callchain_kernel(काष्ठा perf_callchain_entry_ctx *entry,
		      काष्ठा pt_regs *regs)
अणु
	काष्ठा stackframe fr;

	अगर (perf_guest_cbs && perf_guest_cbs->is_in_guest()) अणु
		/* We करोn't support guest os callchain now */
		वापस;
	पूर्ण
	fr.fp = regs->fp;
	fr.lp = regs->lp;
	fr.sp = regs->sp;
	walk_stackframe(&fr, callchain_trace, entry);
पूर्ण

अचिन्हित दीर्घ perf_inकाष्ठाion_poपूर्णांकer(काष्ठा pt_regs *regs)
अणु
	/* However, NDS32 करोes not support भवization */
	अगर (perf_guest_cbs && perf_guest_cbs->is_in_guest())
		वापस perf_guest_cbs->get_guest_ip();

	वापस inकाष्ठाion_poपूर्णांकer(regs);
पूर्ण

अचिन्हित दीर्घ perf_misc_flags(काष्ठा pt_regs *regs)
अणु
	पूर्णांक misc = 0;

	/* However, NDS32 करोes not support भवization */
	अगर (perf_guest_cbs && perf_guest_cbs->is_in_guest()) अणु
		अगर (perf_guest_cbs->is_user_mode())
			misc |= PERF_RECORD_MISC_GUEST_USER;
		अन्यथा
			misc |= PERF_RECORD_MISC_GUEST_KERNEL;
	पूर्ण अन्यथा अणु
		अगर (user_mode(regs))
			misc |= PERF_RECORD_MISC_USER;
		अन्यथा
			misc |= PERF_RECORD_MISC_KERNEL;
	पूर्ण

	वापस misc;
पूर्ण
