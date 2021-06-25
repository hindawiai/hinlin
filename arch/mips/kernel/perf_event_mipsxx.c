<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Linux perक्रमmance counter support क्रम MIPS.
 *
 * Copyright (C) 2010 MIPS Technologies, Inc.
 * Copyright (C) 2011 Cavium Networks, Inc.
 * Author: Deng-Cheng Zhu
 *
 * This code is based on the implementation क्रम ARM, which is in turn
 * based on the sparc64 perf event code and the x86 code. Perक्रमmance
 * counter access is based on the MIPS Oprofile code. And the callchain
 * support references the code of MIPS stacktrace.c.
 */

#समावेश <linux/cpumask.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/smp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/irq_regs.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/समय.स> /* For perf_irq */

#घोषणा MIPS_MAX_HWEVENTS 4
#घोषणा MIPS_TCS_PER_COUNTER 2
#घोषणा MIPS_CPUID_TO_COUNTER_MASK (MIPS_TCS_PER_COUNTER - 1)

काष्ठा cpu_hw_events अणु
	/* Array of events on this cpu. */
	काष्ठा perf_event	*events[MIPS_MAX_HWEVENTS];

	/*
	 * Set the bit (indexed by the counter number) when the counter
	 * is used क्रम an event.
	 */
	अचिन्हित दीर्घ		used_mask[BITS_TO_LONGS(MIPS_MAX_HWEVENTS)];

	/*
	 * Software copy of the control रेजिस्टर क्रम each perक्रमmance counter.
	 * MIPS CPUs vary in perक्रमmance counters. They use this dअगरferently,
	 * and even may not use it.
	 */
	अचिन्हित पूर्णांक		saved_ctrl[MIPS_MAX_HWEVENTS];
पूर्ण;
DEFINE_PER_CPU(काष्ठा cpu_hw_events, cpu_hw_events) = अणु
	.saved_ctrl = अणु0पूर्ण,
पूर्ण;

/* The description of MIPS perक्रमmance events. */
काष्ठा mips_perf_event अणु
	अचिन्हित पूर्णांक event_id;
	/*
	 * MIPS perक्रमmance counters are indexed starting from 0.
	 * CNTR_EVEN indicates the indexes of the counters to be used are
	 * even numbers.
	 */
	अचिन्हित पूर्णांक cntr_mask;
	#घोषणा CNTR_EVEN	0x55555555
	#घोषणा CNTR_ODD	0xaaaaaaaa
	#घोषणा CNTR_ALL	0xffffffff
	क्रमागत अणु
		T  = 0,
		V  = 1,
		P  = 2,
	पूर्ण range;
पूर्ण;

अटल काष्ठा mips_perf_event raw_event;
अटल DEFINE_MUTEX(raw_event_mutex);

#घोषणा C(x) PERF_COUNT_HW_CACHE_##x

काष्ठा mips_pmu अणु
	u64		max_period;
	u64		valid_count;
	u64		overflow;
	स्थिर अक्षर	*name;
	पूर्णांक		irq;
	u64		(*पढ़ो_counter)(अचिन्हित पूर्णांक idx);
	व्योम		(*ग_लिखो_counter)(अचिन्हित पूर्णांक idx, u64 val);
	स्थिर काष्ठा mips_perf_event *(*map_raw_event)(u64 config);
	स्थिर काष्ठा mips_perf_event (*general_event_map)[PERF_COUNT_HW_MAX];
	स्थिर काष्ठा mips_perf_event (*cache_event_map)
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX];
	अचिन्हित पूर्णांक	num_counters;
पूर्ण;

अटल पूर्णांक counter_bits;
अटल काष्ठा mips_pmu mipspmu;

#घोषणा M_PERFCTL_EVENT(event)		(((event) << MIPS_PERFCTRL_EVENT_S) & \
					 MIPS_PERFCTRL_EVENT)
#घोषणा M_PERFCTL_VPEID(vpe)		((vpe)	  << MIPS_PERFCTRL_VPEID_S)

#अगर_घोषित CONFIG_CPU_BMIPS5000
#घोषणा M_PERFCTL_MT_EN(filter)		0
#अन्यथा /* !CONFIG_CPU_BMIPS5000 */
#घोषणा M_PERFCTL_MT_EN(filter)		(filter)
#पूर्ण_अगर /* CONFIG_CPU_BMIPS5000 */

#घोषणा	   M_TC_EN_ALL			M_PERFCTL_MT_EN(MIPS_PERFCTRL_MT_EN_ALL)
#घोषणा	   M_TC_EN_VPE			M_PERFCTL_MT_EN(MIPS_PERFCTRL_MT_EN_VPE)
#घोषणा	   M_TC_EN_TC			M_PERFCTL_MT_EN(MIPS_PERFCTRL_MT_EN_TC)

#घोषणा M_PERFCTL_COUNT_EVENT_WHENEVER	(MIPS_PERFCTRL_EXL |		\
					 MIPS_PERFCTRL_K |		\
					 MIPS_PERFCTRL_U |		\
					 MIPS_PERFCTRL_S |		\
					 MIPS_PERFCTRL_IE)

#अगर_घोषित CONFIG_MIPS_MT_SMP
#घोषणा M_PERFCTL_CONFIG_MASK		0x3fff801f
#अन्यथा
#घोषणा M_PERFCTL_CONFIG_MASK		0x1f
#पूर्ण_अगर

#घोषणा CNTR_BIT_MASK(n)	(((n) == 64) ? ~0ULL : ((1ULL<<(n))-1))

#अगर_घोषित CONFIG_MIPS_PERF_SHARED_TC_COUNTERS
अटल DEFINE_RWLOCK(pmuपूर्णांक_rwlock);

#अगर defined(CONFIG_CPU_BMIPS5000)
#घोषणा vpe_id()	(cpu_has_mipsmt_pertccounters ? \
			 0 : (smp_processor_id() & MIPS_CPUID_TO_COUNTER_MASK))
#अन्यथा
#घोषणा vpe_id()	(cpu_has_mipsmt_pertccounters ? \
			 0 : cpu_vpe_id(&current_cpu_data))
#पूर्ण_अगर

/* Copied from op_model_mipsxx.c */
अटल अचिन्हित पूर्णांक vpe_shअगरt(व्योम)
अणु
	अगर (num_possible_cpus() > 1)
		वापस 1;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक counters_total_to_per_cpu(अचिन्हित पूर्णांक counters)
अणु
	वापस counters >> vpe_shअगरt();
पूर्ण

#अन्यथा /* !CONFIG_MIPS_PERF_SHARED_TC_COUNTERS */
#घोषणा vpe_id()	0

#पूर्ण_अगर /* CONFIG_MIPS_PERF_SHARED_TC_COUNTERS */

अटल व्योम resume_local_counters(व्योम);
अटल व्योम छोड़ो_local_counters(व्योम);
अटल irqवापस_t mipsxx_pmu_handle_irq(पूर्णांक, व्योम *);
अटल पूर्णांक mipsxx_pmu_handle_shared_irq(व्योम);

/* 0: Not Loongson-3
 * 1: Loongson-3A1000/3B1000/3B1500
 * 2: Loongson-3A2000/3A3000
 * 3: Loongson-3A4000+
 */

#घोषणा LOONGSON_PMU_TYPE0 0
#घोषणा LOONGSON_PMU_TYPE1 1
#घोषणा LOONGSON_PMU_TYPE2 2
#घोषणा LOONGSON_PMU_TYPE3 3

अटल अंतरभूत पूर्णांक get_loongson3_pmu_type(व्योम)
अणु
	अगर (boot_cpu_type() != CPU_LOONGSON64)
		वापस LOONGSON_PMU_TYPE0;
	अगर ((boot_cpu_data.processor_id & PRID_COMP_MASK) == PRID_COMP_LEGACY)
		वापस LOONGSON_PMU_TYPE1;
	अगर ((boot_cpu_data.processor_id & PRID_IMP_MASK) == PRID_IMP_LOONGSON_64C)
		वापस LOONGSON_PMU_TYPE2;
	अगर ((boot_cpu_data.processor_id & PRID_IMP_MASK) == PRID_IMP_LOONGSON_64G)
		वापस LOONGSON_PMU_TYPE3;

	वापस LOONGSON_PMU_TYPE0;
पूर्ण

अटल अचिन्हित पूर्णांक mipsxx_pmu_swizzle_perf_idx(अचिन्हित पूर्णांक idx)
अणु
	अगर (vpe_id() == 1)
		idx = (idx + 2) & 3;
	वापस idx;
पूर्ण

अटल u64 mipsxx_pmu_पढ़ो_counter(अचिन्हित पूर्णांक idx)
अणु
	idx = mipsxx_pmu_swizzle_perf_idx(idx);

	चयन (idx) अणु
	हाल 0:
		/*
		 * The counters are अचिन्हित, we must cast to truncate
		 * off the high bits.
		 */
		वापस (u32)पढ़ो_c0_perfcntr0();
	हाल 1:
		वापस (u32)पढ़ो_c0_perfcntr1();
	हाल 2:
		वापस (u32)पढ़ो_c0_perfcntr2();
	हाल 3:
		वापस (u32)पढ़ो_c0_perfcntr3();
	शेष:
		WARN_ONCE(1, "Invalid performance counter number (%d)\n", idx);
		वापस 0;
	पूर्ण
पूर्ण

अटल u64 mipsxx_pmu_पढ़ो_counter_64(अचिन्हित पूर्णांक idx)
अणु
	u64 mask = CNTR_BIT_MASK(counter_bits);
	idx = mipsxx_pmu_swizzle_perf_idx(idx);

	चयन (idx) अणु
	हाल 0:
		वापस पढ़ो_c0_perfcntr0_64() & mask;
	हाल 1:
		वापस पढ़ो_c0_perfcntr1_64() & mask;
	हाल 2:
		वापस पढ़ो_c0_perfcntr2_64() & mask;
	हाल 3:
		वापस पढ़ो_c0_perfcntr3_64() & mask;
	शेष:
		WARN_ONCE(1, "Invalid performance counter number (%d)\n", idx);
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम mipsxx_pmu_ग_लिखो_counter(अचिन्हित पूर्णांक idx, u64 val)
अणु
	idx = mipsxx_pmu_swizzle_perf_idx(idx);

	चयन (idx) अणु
	हाल 0:
		ग_लिखो_c0_perfcntr0(val);
		वापस;
	हाल 1:
		ग_लिखो_c0_perfcntr1(val);
		वापस;
	हाल 2:
		ग_लिखो_c0_perfcntr2(val);
		वापस;
	हाल 3:
		ग_लिखो_c0_perfcntr3(val);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम mipsxx_pmu_ग_लिखो_counter_64(अचिन्हित पूर्णांक idx, u64 val)
अणु
	val &= CNTR_BIT_MASK(counter_bits);
	idx = mipsxx_pmu_swizzle_perf_idx(idx);

	चयन (idx) अणु
	हाल 0:
		ग_लिखो_c0_perfcntr0_64(val);
		वापस;
	हाल 1:
		ग_लिखो_c0_perfcntr1_64(val);
		वापस;
	हाल 2:
		ग_लिखो_c0_perfcntr2_64(val);
		वापस;
	हाल 3:
		ग_लिखो_c0_perfcntr3_64(val);
		वापस;
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक mipsxx_pmu_पढ़ो_control(अचिन्हित पूर्णांक idx)
अणु
	idx = mipsxx_pmu_swizzle_perf_idx(idx);

	चयन (idx) अणु
	हाल 0:
		वापस पढ़ो_c0_perfctrl0();
	हाल 1:
		वापस पढ़ो_c0_perfctrl1();
	हाल 2:
		वापस पढ़ो_c0_perfctrl2();
	हाल 3:
		वापस पढ़ो_c0_perfctrl3();
	शेष:
		WARN_ONCE(1, "Invalid performance counter number (%d)\n", idx);
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम mipsxx_pmu_ग_लिखो_control(अचिन्हित पूर्णांक idx, अचिन्हित पूर्णांक val)
अणु
	idx = mipsxx_pmu_swizzle_perf_idx(idx);

	चयन (idx) अणु
	हाल 0:
		ग_लिखो_c0_perfctrl0(val);
		वापस;
	हाल 1:
		ग_लिखो_c0_perfctrl1(val);
		वापस;
	हाल 2:
		ग_लिखो_c0_perfctrl2(val);
		वापस;
	हाल 3:
		ग_लिखो_c0_perfctrl3(val);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक mipsxx_pmu_alloc_counter(काष्ठा cpu_hw_events *cpuc,
				    काष्ठा hw_perf_event *hwc)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ cntr_mask;

	/*
	 * We only need to care the counter mask. The range has been
	 * checked definitely.
	 */
	अगर (get_loongson3_pmu_type() == LOONGSON_PMU_TYPE2)
		cntr_mask = (hwc->event_base >> 10) & 0xffff;
	अन्यथा
		cntr_mask = (hwc->event_base >> 8) & 0xffff;

	क्रम (i = mipspmu.num_counters - 1; i >= 0; i--) अणु
		/*
		 * Note that some MIPS perf events can be counted by both
		 * even and odd counters, wheresas many other are only by
		 * even _or_ odd counters. This पूर्णांकroduces an issue that
		 * when the क्रमmer kind of event takes the counter the
		 * latter kind of event wants to use, then the "counter
		 * allocation" क्रम the latter event will fail. In fact अगर
		 * they can be dynamically swapped, they both feel happy.
		 * But here we leave this issue alone क्रम now.
		 */
		अगर (test_bit(i, &cntr_mask) &&
			!test_and_set_bit(i, cpuc->used_mask))
			वापस i;
	पूर्ण

	वापस -EAGAIN;
पूर्ण

अटल व्योम mipsxx_pmu_enable_event(काष्ठा hw_perf_event *evt, पूर्णांक idx)
अणु
	काष्ठा perf_event *event = container_of(evt, काष्ठा perf_event, hw);
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	अचिन्हित पूर्णांक range = evt->event_base >> 24;

	WARN_ON(idx < 0 || idx >= mipspmu.num_counters);

	अगर (get_loongson3_pmu_type() == LOONGSON_PMU_TYPE2)
		cpuc->saved_ctrl[idx] = M_PERFCTL_EVENT(evt->event_base & 0x3ff) |
			(evt->config_base & M_PERFCTL_CONFIG_MASK) |
			/* Make sure पूर्णांकerrupt enabled. */
			MIPS_PERFCTRL_IE;
	अन्यथा
		cpuc->saved_ctrl[idx] = M_PERFCTL_EVENT(evt->event_base & 0xff) |
			(evt->config_base & M_PERFCTL_CONFIG_MASK) |
			/* Make sure पूर्णांकerrupt enabled. */
			MIPS_PERFCTRL_IE;

	अगर (IS_ENABLED(CONFIG_CPU_BMIPS5000)) अणु
		/* enable the counter क्रम the calling thपढ़ो */
		cpuc->saved_ctrl[idx] |=
			(1 << (12 + vpe_id())) | BRCM_PERFCTRL_TC;
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_MIPS_MT_SMP) && range > V) अणु
		/* The counter is processor wide. Set it up to count all TCs. */
		pr_debug("Enabling perf counter for all TCs\n");
		cpuc->saved_ctrl[idx] |= M_TC_EN_ALL;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक cpu, ctrl;

		/*
		 * Set up the counter क्रम a particular CPU when event->cpu is
		 * a valid CPU number. Otherwise set up the counter क्रम the CPU
		 * scheduling this thपढ़ो.
		 */
		cpu = (event->cpu >= 0) ? event->cpu : smp_processor_id();

		ctrl = M_PERFCTL_VPEID(cpu_vpe_id(&cpu_data[cpu]));
		ctrl |= M_TC_EN_VPE;
		cpuc->saved_ctrl[idx] |= ctrl;
		pr_debug("Enabling perf counter for CPU%d\n", cpu);
	पूर्ण
	/*
	 * We करो not actually let the counter run. Leave it until start().
	 */
पूर्ण

अटल व्योम mipsxx_pmu_disable_event(पूर्णांक idx)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	अचिन्हित दीर्घ flags;

	WARN_ON(idx < 0 || idx >= mipspmu.num_counters);

	local_irq_save(flags);
	cpuc->saved_ctrl[idx] = mipsxx_pmu_पढ़ो_control(idx) &
		~M_PERFCTL_COUNT_EVENT_WHENEVER;
	mipsxx_pmu_ग_लिखो_control(idx, cpuc->saved_ctrl[idx]);
	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक mipspmu_event_set_period(काष्ठा perf_event *event,
				    काष्ठा hw_perf_event *hwc,
				    पूर्णांक idx)
अणु
	u64 left = local64_पढ़ो(&hwc->period_left);
	u64 period = hwc->sample_period;
	पूर्णांक ret = 0;

	अगर (unlikely((left + period) & (1ULL << 63))) अणु
		/* left underflowed by more than period. */
		left = period;
		local64_set(&hwc->period_left, left);
		hwc->last_period = period;
		ret = 1;
	पूर्ण अन्यथा	अगर (unlikely((left + period) <= period)) अणु
		/* left underflowed by less than period. */
		left += period;
		local64_set(&hwc->period_left, left);
		hwc->last_period = period;
		ret = 1;
	पूर्ण

	अगर (left > mipspmu.max_period) अणु
		left = mipspmu.max_period;
		local64_set(&hwc->period_left, left);
	पूर्ण

	local64_set(&hwc->prev_count, mipspmu.overflow - left);

	अगर (get_loongson3_pmu_type() == LOONGSON_PMU_TYPE2)
		mipsxx_pmu_ग_लिखो_control(idx,
				M_PERFCTL_EVENT(hwc->event_base & 0x3ff));

	mipspmu.ग_लिखो_counter(idx, mipspmu.overflow - left);

	perf_event_update_userpage(event);

	वापस ret;
पूर्ण

अटल व्योम mipspmu_event_update(काष्ठा perf_event *event,
				 काष्ठा hw_perf_event *hwc,
				 पूर्णांक idx)
अणु
	u64 prev_raw_count, new_raw_count;
	u64 delta;

again:
	prev_raw_count = local64_पढ़ो(&hwc->prev_count);
	new_raw_count = mipspmu.पढ़ो_counter(idx);

	अगर (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
				new_raw_count) != prev_raw_count)
		जाओ again;

	delta = new_raw_count - prev_raw_count;

	local64_add(delta, &event->count);
	local64_sub(delta, &hwc->period_left);
पूर्ण

अटल व्योम mipspmu_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (flags & PERF_EF_RELOAD)
		WARN_ON_ONCE(!(hwc->state & PERF_HES_UPTODATE));

	hwc->state = 0;

	/* Set the period क्रम the event. */
	mipspmu_event_set_period(event, hwc, hwc->idx);

	/* Enable the event. */
	mipsxx_pmu_enable_event(hwc, hwc->idx);
पूर्ण

अटल व्योम mipspmu_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (!(hwc->state & PERF_HES_STOPPED)) अणु
		/* We are working on a local event. */
		mipsxx_pmu_disable_event(hwc->idx);
		barrier();
		mipspmu_event_update(event, hwc, hwc->idx);
		hwc->state |= PERF_HES_STOPPED | PERF_HES_UPTODATE;
	पूर्ण
पूर्ण

अटल पूर्णांक mipspmu_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx;
	पूर्णांक err = 0;

	perf_pmu_disable(event->pmu);

	/* To look क्रम a मुक्त counter क्रम this event. */
	idx = mipsxx_pmu_alloc_counter(cpuc, hwc);
	अगर (idx < 0) अणु
		err = idx;
		जाओ out;
	पूर्ण

	/*
	 * If there is an event in the counter we are going to use then
	 * make sure it is disabled.
	 */
	event->hw.idx = idx;
	mipsxx_pmu_disable_event(idx);
	cpuc->events[idx] = event;

	hwc->state = PERF_HES_STOPPED | PERF_HES_UPTODATE;
	अगर (flags & PERF_EF_START)
		mipspmu_start(event, PERF_EF_RELOAD);

	/* Propagate our changes to the userspace mapping. */
	perf_event_update_userpage(event);

out:
	perf_pmu_enable(event->pmu);
	वापस err;
पूर्ण

अटल व्योम mipspmu_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	WARN_ON(idx < 0 || idx >= mipspmu.num_counters);

	mipspmu_stop(event, PERF_EF_UPDATE);
	cpuc->events[idx] = शून्य;
	clear_bit(idx, cpuc->used_mask);

	perf_event_update_userpage(event);
पूर्ण

अटल व्योम mipspmu_पढ़ो(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	/* Don't पढ़ो disabled counters! */
	अगर (hwc->idx < 0)
		वापस;

	mipspmu_event_update(event, hwc, hwc->idx);
पूर्ण

अटल व्योम mipspmu_enable(काष्ठा pmu *pmu)
अणु
#अगर_घोषित CONFIG_MIPS_PERF_SHARED_TC_COUNTERS
	ग_लिखो_unlock(&pmuपूर्णांक_rwlock);
#पूर्ण_अगर
	resume_local_counters();
पूर्ण

/*
 * MIPS perक्रमmance counters can be per-TC. The control रेजिस्टरs can
 * not be directly accessed across CPUs. Hence अगर we want to करो global
 * control, we need cross CPU calls. on_each_cpu() can help us, but we
 * can not make sure this function is called with पूर्णांकerrupts enabled. So
 * here we छोड़ो local counters and then grab a rwlock and leave the
 * counters on other CPUs alone. If any counter पूर्णांकerrupt उठाओs जबतक
 * we own the ग_लिखो lock, simply छोड़ो local counters on that CPU and
 * spin in the handler. Also we know we won't be चयनed to another
 * CPU after pausing local counters and beक्रमe grabbing the lock.
 */
अटल व्योम mipspmu_disable(काष्ठा pmu *pmu)
अणु
	छोड़ो_local_counters();
#अगर_घोषित CONFIG_MIPS_PERF_SHARED_TC_COUNTERS
	ग_लिखो_lock(&pmuपूर्णांक_rwlock);
#पूर्ण_अगर
पूर्ण

अटल atomic_t active_events = ATOMIC_INIT(0);
अटल DEFINE_MUTEX(pmu_reserve_mutex);
अटल पूर्णांक (*save_perf_irq)(व्योम);

अटल पूर्णांक mipspmu_get_irq(व्योम)
अणु
	पूर्णांक err;

	अगर (mipspmu.irq >= 0) अणु
		/* Request my own irq handler. */
		err = request_irq(mipspmu.irq, mipsxx_pmu_handle_irq,
				  IRQF_PERCPU | IRQF_NOBALANCING |
				  IRQF_NO_THREAD | IRQF_NO_SUSPEND |
				  IRQF_SHARED,
				  "mips_perf_pmu", &mipspmu);
		अगर (err) अणु
			pr_warn("Unable to request IRQ%d for MIPS performance counters!\n",
				mipspmu.irq);
		पूर्ण
	पूर्ण अन्यथा अगर (cp0_perfcount_irq < 0) अणु
		/*
		 * We are sharing the irq number with the समयr पूर्णांकerrupt.
		 */
		save_perf_irq = perf_irq;
		perf_irq = mipsxx_pmu_handle_shared_irq;
		err = 0;
	पूर्ण अन्यथा अणु
		pr_warn("The platform hasn't properly defined its interrupt controller\n");
		err = -ENOENT;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम mipspmu_मुक्त_irq(व्योम)
अणु
	अगर (mipspmu.irq >= 0)
		मुक्त_irq(mipspmu.irq, &mipspmu);
	अन्यथा अगर (cp0_perfcount_irq < 0)
		perf_irq = save_perf_irq;
पूर्ण

/*
 * mipsxx/rm9000/loongson2 have dअगरferent perक्रमmance counters, they have
 * specअगरic low-level init routines.
 */
अटल व्योम reset_counters(व्योम *arg);
अटल पूर्णांक __hw_perf_event_init(काष्ठा perf_event *event);

अटल व्योम hw_perf_event_destroy(काष्ठा perf_event *event)
अणु
	अगर (atomic_dec_and_mutex_lock(&active_events,
				&pmu_reserve_mutex)) अणु
		/*
		 * We must not call the destroy function with पूर्णांकerrupts
		 * disabled.
		 */
		on_each_cpu(reset_counters,
			(व्योम *)(दीर्घ)mipspmu.num_counters, 1);
		mipspmu_मुक्त_irq();
		mutex_unlock(&pmu_reserve_mutex);
	पूर्ण
पूर्ण

अटल पूर्णांक mipspmu_event_init(काष्ठा perf_event *event)
अणु
	पूर्णांक err = 0;

	/* करोes not support taken branch sampling */
	अगर (has_branch_stack(event))
		वापस -EOPNOTSUPP;

	चयन (event->attr.type) अणु
	हाल PERF_TYPE_RAW:
	हाल PERF_TYPE_HARDWARE:
	हाल PERF_TYPE_HW_CACHE:
		अवरोध;

	शेष:
		वापस -ENOENT;
	पूर्ण

	अगर (event->cpu >= 0 && !cpu_online(event->cpu))
		वापस -ENODEV;

	अगर (!atomic_inc_not_zero(&active_events)) अणु
		mutex_lock(&pmu_reserve_mutex);
		अगर (atomic_पढ़ो(&active_events) == 0)
			err = mipspmu_get_irq();

		अगर (!err)
			atomic_inc(&active_events);
		mutex_unlock(&pmu_reserve_mutex);
	पूर्ण

	अगर (err)
		वापस err;

	वापस __hw_perf_event_init(event);
पूर्ण

अटल काष्ठा pmu pmu = अणु
	.pmu_enable	= mipspmu_enable,
	.pmu_disable	= mipspmu_disable,
	.event_init	= mipspmu_event_init,
	.add		= mipspmu_add,
	.del		= mipspmu_del,
	.start		= mipspmu_start,
	.stop		= mipspmu_stop,
	.पढ़ो		= mipspmu_पढ़ो,
पूर्ण;

अटल अचिन्हित पूर्णांक mipspmu_perf_event_encode(स्थिर काष्ठा mips_perf_event *pev)
अणु
/*
 * Top 8 bits क्रम range, next 16 bits क्रम cntr_mask, lowest 8 bits क्रम
 * event_id.
 */
#अगर_घोषित CONFIG_MIPS_MT_SMP
	अगर (num_possible_cpus() > 1)
		वापस ((अचिन्हित पूर्णांक)pev->range << 24) |
			(pev->cntr_mask & 0xffff00) |
			(pev->event_id & 0xff);
	अन्यथा
#पूर्ण_अगर /* CONFIG_MIPS_MT_SMP */
	अणु
		अगर (get_loongson3_pmu_type() == LOONGSON_PMU_TYPE2)
			वापस (pev->cntr_mask & 0xfffc00) |
				(pev->event_id & 0x3ff);
		अन्यथा
			वापस (pev->cntr_mask & 0xffff00) |
				(pev->event_id & 0xff);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा mips_perf_event *mipspmu_map_general_event(पूर्णांक idx)
अणु

	अगर ((*mipspmu.general_event_map)[idx].cntr_mask == 0)
		वापस ERR_PTR(-EOPNOTSUPP);
	वापस &(*mipspmu.general_event_map)[idx];
पूर्ण

अटल स्थिर काष्ठा mips_perf_event *mipspmu_map_cache_event(u64 config)
अणु
	अचिन्हित पूर्णांक cache_type, cache_op, cache_result;
	स्थिर काष्ठा mips_perf_event *pev;

	cache_type = (config >> 0) & 0xff;
	अगर (cache_type >= PERF_COUNT_HW_CACHE_MAX)
		वापस ERR_PTR(-EINVAL);

	cache_op = (config >> 8) & 0xff;
	अगर (cache_op >= PERF_COUNT_HW_CACHE_OP_MAX)
		वापस ERR_PTR(-EINVAL);

	cache_result = (config >> 16) & 0xff;
	अगर (cache_result >= PERF_COUNT_HW_CACHE_RESULT_MAX)
		वापस ERR_PTR(-EINVAL);

	pev = &((*mipspmu.cache_event_map)
					[cache_type]
					[cache_op]
					[cache_result]);

	अगर (pev->cntr_mask == 0)
		वापस ERR_PTR(-EOPNOTSUPP);

	वापस pev;

पूर्ण

अटल पूर्णांक validate_group(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event *sibling, *leader = event->group_leader;
	काष्ठा cpu_hw_events fake_cpuc;

	स_रखो(&fake_cpuc, 0, माप(fake_cpuc));

	अगर (mipsxx_pmu_alloc_counter(&fake_cpuc, &leader->hw) < 0)
		वापस -EINVAL;

	क्रम_each_sibling_event(sibling, leader) अणु
		अगर (mipsxx_pmu_alloc_counter(&fake_cpuc, &sibling->hw) < 0)
			वापस -EINVAL;
	पूर्ण

	अगर (mipsxx_pmu_alloc_counter(&fake_cpuc, &event->hw) < 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* This is needed by specअगरic irq handlers in perf_event_*.c */
अटल व्योम handle_associated_event(काष्ठा cpu_hw_events *cpuc,
				    पूर्णांक idx, काष्ठा perf_sample_data *data,
				    काष्ठा pt_regs *regs)
अणु
	काष्ठा perf_event *event = cpuc->events[idx];
	काष्ठा hw_perf_event *hwc = &event->hw;

	mipspmu_event_update(event, hwc, idx);
	data->period = event->hw.last_period;
	अगर (!mipspmu_event_set_period(event, hwc, idx))
		वापस;

	अगर (perf_event_overflow(event, data, regs))
		mipsxx_pmu_disable_event(idx);
पूर्ण


अटल पूर्णांक __n_counters(व्योम)
अणु
	अगर (!cpu_has_perf)
		वापस 0;
	अगर (!(पढ़ो_c0_perfctrl0() & MIPS_PERFCTRL_M))
		वापस 1;
	अगर (!(पढ़ो_c0_perfctrl1() & MIPS_PERFCTRL_M))
		वापस 2;
	अगर (!(पढ़ो_c0_perfctrl2() & MIPS_PERFCTRL_M))
		वापस 3;

	वापस 4;
पूर्ण

अटल पूर्णांक n_counters(व्योम)
अणु
	पूर्णांक counters;

	चयन (current_cpu_type()) अणु
	हाल CPU_R10000:
		counters = 2;
		अवरोध;

	हाल CPU_R12000:
	हाल CPU_R14000:
	हाल CPU_R16000:
		counters = 4;
		अवरोध;

	शेष:
		counters = __n_counters();
	पूर्ण

	वापस counters;
पूर्ण

अटल व्योम loongson3_reset_counters(व्योम *arg)
अणु
	पूर्णांक counters = (पूर्णांक)(दीर्घ)arg;

	चयन (counters) अणु
	हाल 4:
		mipsxx_pmu_ग_लिखो_control(3, 0);
		mipspmu.ग_लिखो_counter(3, 0);
		mipsxx_pmu_ग_लिखो_control(3, 127<<5);
		mipspmu.ग_लिखो_counter(3, 0);
		mipsxx_pmu_ग_लिखो_control(3, 191<<5);
		mipspmu.ग_लिखो_counter(3, 0);
		mipsxx_pmu_ग_लिखो_control(3, 255<<5);
		mipspmu.ग_लिखो_counter(3, 0);
		mipsxx_pmu_ग_लिखो_control(3, 319<<5);
		mipspmu.ग_लिखो_counter(3, 0);
		mipsxx_pmu_ग_लिखो_control(3, 383<<5);
		mipspmu.ग_लिखो_counter(3, 0);
		mipsxx_pmu_ग_लिखो_control(3, 575<<5);
		mipspmu.ग_लिखो_counter(3, 0);
		fallthrough;
	हाल 3:
		mipsxx_pmu_ग_लिखो_control(2, 0);
		mipspmu.ग_लिखो_counter(2, 0);
		mipsxx_pmu_ग_लिखो_control(2, 127<<5);
		mipspmu.ग_लिखो_counter(2, 0);
		mipsxx_pmu_ग_लिखो_control(2, 191<<5);
		mipspmu.ग_लिखो_counter(2, 0);
		mipsxx_pmu_ग_लिखो_control(2, 255<<5);
		mipspmu.ग_लिखो_counter(2, 0);
		mipsxx_pmu_ग_लिखो_control(2, 319<<5);
		mipspmu.ग_लिखो_counter(2, 0);
		mipsxx_pmu_ग_लिखो_control(2, 383<<5);
		mipspmu.ग_लिखो_counter(2, 0);
		mipsxx_pmu_ग_लिखो_control(2, 575<<5);
		mipspmu.ग_लिखो_counter(2, 0);
		fallthrough;
	हाल 2:
		mipsxx_pmu_ग_लिखो_control(1, 0);
		mipspmu.ग_लिखो_counter(1, 0);
		mipsxx_pmu_ग_लिखो_control(1, 127<<5);
		mipspmu.ग_लिखो_counter(1, 0);
		mipsxx_pmu_ग_लिखो_control(1, 191<<5);
		mipspmu.ग_लिखो_counter(1, 0);
		mipsxx_pmu_ग_लिखो_control(1, 255<<5);
		mipspmu.ग_लिखो_counter(1, 0);
		mipsxx_pmu_ग_लिखो_control(1, 319<<5);
		mipspmu.ग_लिखो_counter(1, 0);
		mipsxx_pmu_ग_लिखो_control(1, 383<<5);
		mipspmu.ग_लिखो_counter(1, 0);
		mipsxx_pmu_ग_लिखो_control(1, 575<<5);
		mipspmu.ग_लिखो_counter(1, 0);
		fallthrough;
	हाल 1:
		mipsxx_pmu_ग_लिखो_control(0, 0);
		mipspmu.ग_लिखो_counter(0, 0);
		mipsxx_pmu_ग_लिखो_control(0, 127<<5);
		mipspmu.ग_लिखो_counter(0, 0);
		mipsxx_pmu_ग_लिखो_control(0, 191<<5);
		mipspmu.ग_लिखो_counter(0, 0);
		mipsxx_pmu_ग_लिखो_control(0, 255<<5);
		mipspmu.ग_लिखो_counter(0, 0);
		mipsxx_pmu_ग_लिखो_control(0, 319<<5);
		mipspmu.ग_लिखो_counter(0, 0);
		mipsxx_pmu_ग_लिखो_control(0, 383<<5);
		mipspmu.ग_लिखो_counter(0, 0);
		mipsxx_pmu_ग_लिखो_control(0, 575<<5);
		mipspmu.ग_लिखो_counter(0, 0);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम reset_counters(व्योम *arg)
अणु
	पूर्णांक counters = (पूर्णांक)(दीर्घ)arg;

	अगर (get_loongson3_pmu_type() == LOONGSON_PMU_TYPE2) अणु
		loongson3_reset_counters(arg);
		वापस;
	पूर्ण

	चयन (counters) अणु
	हाल 4:
		mipsxx_pmu_ग_लिखो_control(3, 0);
		mipspmu.ग_लिखो_counter(3, 0);
		fallthrough;
	हाल 3:
		mipsxx_pmu_ग_लिखो_control(2, 0);
		mipspmu.ग_लिखो_counter(2, 0);
		fallthrough;
	हाल 2:
		mipsxx_pmu_ग_लिखो_control(1, 0);
		mipspmu.ग_लिखो_counter(1, 0);
		fallthrough;
	हाल 1:
		mipsxx_pmu_ग_लिखो_control(0, 0);
		mipspmu.ग_लिखो_counter(0, 0);
		अवरोध;
	पूर्ण
पूर्ण

/* 24K/34K/1004K/पूर्णांकerAptiv/loongson1 cores share the same event map. */
अटल स्थिर काष्ठा mips_perf_event mipsxxcore_event_map
				[PERF_COUNT_HW_MAX] = अणु
	[PERF_COUNT_HW_CPU_CYCLES] = अणु 0x00, CNTR_EVEN | CNTR_ODD, P पूर्ण,
	[PERF_COUNT_HW_INSTRUCTIONS] = अणु 0x01, CNTR_EVEN | CNTR_ODD, T पूर्ण,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] = अणु 0x02, CNTR_EVEN, T पूर्ण,
	[PERF_COUNT_HW_BRANCH_MISSES] = अणु 0x02, CNTR_ODD, T पूर्ण,
पूर्ण;

/* 74K/proAptiv core has dअगरferent branch event code. */
अटल स्थिर काष्ठा mips_perf_event mipsxxcore_event_map2
				[PERF_COUNT_HW_MAX] = अणु
	[PERF_COUNT_HW_CPU_CYCLES] = अणु 0x00, CNTR_EVEN | CNTR_ODD, P पूर्ण,
	[PERF_COUNT_HW_INSTRUCTIONS] = अणु 0x01, CNTR_EVEN | CNTR_ODD, T पूर्ण,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] = अणु 0x27, CNTR_EVEN, T पूर्ण,
	[PERF_COUNT_HW_BRANCH_MISSES] = अणु 0x27, CNTR_ODD, T पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mips_perf_event i6x00_event_map[PERF_COUNT_HW_MAX] = अणु
	[PERF_COUNT_HW_CPU_CYCLES]          = अणु 0x00, CNTR_EVEN | CNTR_ODD पूर्ण,
	[PERF_COUNT_HW_INSTRUCTIONS]        = अणु 0x01, CNTR_EVEN | CNTR_ODD पूर्ण,
	/* These only count dcache, not icache */
	[PERF_COUNT_HW_CACHE_REFERENCES]    = अणु 0x45, CNTR_EVEN | CNTR_ODD पूर्ण,
	[PERF_COUNT_HW_CACHE_MISSES]        = अणु 0x48, CNTR_EVEN | CNTR_ODD पूर्ण,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] = अणु 0x15, CNTR_EVEN | CNTR_ODD पूर्ण,
	[PERF_COUNT_HW_BRANCH_MISSES]       = अणु 0x16, CNTR_EVEN | CNTR_ODD पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mips_perf_event loongson3_event_map1[PERF_COUNT_HW_MAX] = अणु
	[PERF_COUNT_HW_CPU_CYCLES] = अणु 0x00, CNTR_EVEN पूर्ण,
	[PERF_COUNT_HW_INSTRUCTIONS] = अणु 0x00, CNTR_ODD पूर्ण,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] = अणु 0x01, CNTR_EVEN पूर्ण,
	[PERF_COUNT_HW_BRANCH_MISSES] = अणु 0x01, CNTR_ODD पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mips_perf_event loongson3_event_map2[PERF_COUNT_HW_MAX] = अणु
	[PERF_COUNT_HW_CPU_CYCLES] = अणु 0x80, CNTR_ALL पूर्ण,
	[PERF_COUNT_HW_INSTRUCTIONS] = अणु 0x81, CNTR_ALL पूर्ण,
	[PERF_COUNT_HW_CACHE_MISSES] = अणु 0x18, CNTR_ALL पूर्ण,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] = अणु 0x94, CNTR_ALL पूर्ण,
	[PERF_COUNT_HW_BRANCH_MISSES] = अणु 0x9c, CNTR_ALL पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mips_perf_event loongson3_event_map3[PERF_COUNT_HW_MAX] = अणु
	[PERF_COUNT_HW_CPU_CYCLES] = अणु 0x00, CNTR_ALL पूर्ण,
	[PERF_COUNT_HW_INSTRUCTIONS] = अणु 0x01, CNTR_ALL पूर्ण,
	[PERF_COUNT_HW_CACHE_REFERENCES] = अणु 0x1c, CNTR_ALL पूर्ण,
	[PERF_COUNT_HW_CACHE_MISSES] = अणु 0x1d, CNTR_ALL पूर्ण,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] = अणु 0x02, CNTR_ALL पूर्ण,
	[PERF_COUNT_HW_BRANCH_MISSES] = अणु 0x08, CNTR_ALL पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mips_perf_event octeon_event_map[PERF_COUNT_HW_MAX] = अणु
	[PERF_COUNT_HW_CPU_CYCLES] = अणु 0x01, CNTR_ALL पूर्ण,
	[PERF_COUNT_HW_INSTRUCTIONS] = अणु 0x03, CNTR_ALL पूर्ण,
	[PERF_COUNT_HW_CACHE_REFERENCES] = अणु 0x2b, CNTR_ALL पूर्ण,
	[PERF_COUNT_HW_CACHE_MISSES] = अणु 0x2e, CNTR_ALL	 पूर्ण,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] = अणु 0x08, CNTR_ALL पूर्ण,
	[PERF_COUNT_HW_BRANCH_MISSES] = अणु 0x09, CNTR_ALL पूर्ण,
	[PERF_COUNT_HW_BUS_CYCLES] = अणु 0x25, CNTR_ALL पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mips_perf_event bmips5000_event_map
				[PERF_COUNT_HW_MAX] = अणु
	[PERF_COUNT_HW_CPU_CYCLES] = अणु 0x00, CNTR_EVEN | CNTR_ODD, T पूर्ण,
	[PERF_COUNT_HW_INSTRUCTIONS] = अणु 0x01, CNTR_EVEN | CNTR_ODD, T पूर्ण,
	[PERF_COUNT_HW_BRANCH_MISSES] = अणु 0x02, CNTR_ODD, T पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mips_perf_event xlp_event_map[PERF_COUNT_HW_MAX] = अणु
	[PERF_COUNT_HW_CPU_CYCLES] = अणु 0x01, CNTR_ALL पूर्ण,
	[PERF_COUNT_HW_INSTRUCTIONS] = अणु 0x18, CNTR_ALL पूर्ण, /* PAPI_TOT_INS */
	[PERF_COUNT_HW_CACHE_REFERENCES] = अणु 0x04, CNTR_ALL पूर्ण, /* PAPI_L1_ICA */
	[PERF_COUNT_HW_CACHE_MISSES] = अणु 0x07, CNTR_ALL पूर्ण, /* PAPI_L1_ICM */
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] = अणु 0x1b, CNTR_ALL पूर्ण, /* PAPI_BR_CN */
	[PERF_COUNT_HW_BRANCH_MISSES] = अणु 0x1c, CNTR_ALL पूर्ण, /* PAPI_BR_MSP */
पूर्ण;

/* 24K/34K/1004K/पूर्णांकerAptiv/loongson1 cores share the same cache event map. */
अटल स्थिर काष्ठा mips_perf_event mipsxxcore_cache_map
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
[C(L1D)] = अणु
	/*
	 * Like some other architectures (e.g. ARM), the perक्रमmance
	 * counters करोn't dअगरferentiate between पढ़ो and ग_लिखो
	 * accesses/misses, so this isn't strictly correct, but it's the
	 * best we can करो. Writes and पढ़ोs get combined.
	 */
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x0a, CNTR_EVEN, T पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x0b, CNTR_EVEN | CNTR_ODD, T पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x0a, CNTR_EVEN, T पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x0b, CNTR_EVEN | CNTR_ODD, T पूर्ण,
	पूर्ण,
पूर्ण,
[C(L1I)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x09, CNTR_EVEN, T पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x09, CNTR_ODD, T पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x09, CNTR_EVEN, T पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x09, CNTR_ODD, T पूर्ण,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x14, CNTR_EVEN, T पूर्ण,
		/*
		 * Note that MIPS has only "hit" events countable क्रम
		 * the prefetch operation.
		 */
	पूर्ण,
पूर्ण,
[C(LL)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x15, CNTR_ODD, P पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x16, CNTR_EVEN, P पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x15, CNTR_ODD, P पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x16, CNTR_EVEN, P पूर्ण,
	पूर्ण,
पूर्ण,
[C(DTLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x06, CNTR_EVEN, T पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x06, CNTR_ODD, T पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x06, CNTR_EVEN, T पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x06, CNTR_ODD, T पूर्ण,
	पूर्ण,
पूर्ण,
[C(ITLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x05, CNTR_EVEN, T पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x05, CNTR_ODD, T पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x05, CNTR_EVEN, T पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x05, CNTR_ODD, T पूर्ण,
	पूर्ण,
पूर्ण,
[C(BPU)] = अणु
	/* Using the same code क्रम *HW_BRANCH* */
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x02, CNTR_EVEN, T पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x02, CNTR_ODD, T पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x02, CNTR_EVEN, T पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x02, CNTR_ODD, T पूर्ण,
	पूर्ण,
पूर्ण,
पूर्ण;

/* 74K/proAptiv core has completely dअगरferent cache event map. */
अटल स्थिर काष्ठा mips_perf_event mipsxxcore_cache_map2
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
[C(L1D)] = अणु
	/*
	 * Like some other architectures (e.g. ARM), the perक्रमmance
	 * counters करोn't dअगरferentiate between पढ़ो and ग_लिखो
	 * accesses/misses, so this isn't strictly correct, but it's the
	 * best we can करो. Writes and पढ़ोs get combined.
	 */
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x17, CNTR_ODD, T पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x18, CNTR_ODD, T पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x17, CNTR_ODD, T पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x18, CNTR_ODD, T पूर्ण,
	पूर्ण,
पूर्ण,
[C(L1I)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x06, CNTR_EVEN, T पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x06, CNTR_ODD, T पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x06, CNTR_EVEN, T पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x06, CNTR_ODD, T पूर्ण,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x34, CNTR_EVEN, T पूर्ण,
		/*
		 * Note that MIPS has only "hit" events countable क्रम
		 * the prefetch operation.
		 */
	पूर्ण,
पूर्ण,
[C(LL)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x1c, CNTR_ODD, P पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x1d, CNTR_EVEN, P पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x1c, CNTR_ODD, P पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x1d, CNTR_EVEN, P पूर्ण,
	पूर्ण,
पूर्ण,
/*
 * 74K core करोes not have specअगरic DTLB events. proAptiv core has
 * "speculative" DTLB events which are numbered 0x63 (even/odd) and
 * not included here. One can use raw events अगर really needed.
 */
[C(ITLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x04, CNTR_EVEN, T पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x04, CNTR_ODD, T पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x04, CNTR_EVEN, T पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x04, CNTR_ODD, T पूर्ण,
	पूर्ण,
पूर्ण,
[C(BPU)] = अणु
	/* Using the same code क्रम *HW_BRANCH* */
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x27, CNTR_EVEN, T पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x27, CNTR_ODD, T पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x27, CNTR_EVEN, T पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x27, CNTR_ODD, T पूर्ण,
	पूर्ण,
पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mips_perf_event i6x00_cache_map
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
[C(L1D)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x46, CNTR_EVEN | CNTR_ODD पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x49, CNTR_EVEN | CNTR_ODD पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x47, CNTR_EVEN | CNTR_ODD पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x4a, CNTR_EVEN | CNTR_ODD पूर्ण,
	पूर्ण,
पूर्ण,
[C(L1I)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x84, CNTR_EVEN | CNTR_ODD पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x85, CNTR_EVEN | CNTR_ODD पूर्ण,
	पूर्ण,
पूर्ण,
[C(DTLB)] = अणु
	/* Can't distinguish पढ़ो & ग_लिखो */
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x40, CNTR_EVEN | CNTR_ODD पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x41, CNTR_EVEN | CNTR_ODD पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x40, CNTR_EVEN | CNTR_ODD पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x41, CNTR_EVEN | CNTR_ODD पूर्ण,
	पूर्ण,
पूर्ण,
[C(BPU)] = अणु
	/* Conditional branches / mispredicted */
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x15, CNTR_EVEN | CNTR_ODD पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x16, CNTR_EVEN | CNTR_ODD पूर्ण,
	पूर्ण,
पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mips_perf_event loongson3_cache_map1
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
[C(L1D)] = अणु
	/*
	 * Like some other architectures (e.g. ARM), the perक्रमmance
	 * counters करोn't dअगरferentiate between पढ़ो and ग_लिखो
	 * accesses/misses, so this isn't strictly correct, but it's the
	 * best we can करो. Writes and पढ़ोs get combined.
	 */
	[C(OP_READ)] = अणु
		[C(RESULT_MISS)]        = अणु 0x04, CNTR_ODD पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_MISS)]        = अणु 0x04, CNTR_ODD पूर्ण,
	पूर्ण,
पूर्ण,
[C(L1I)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_MISS)]        = अणु 0x04, CNTR_EVEN पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_MISS)]        = अणु 0x04, CNTR_EVEN पूर्ण,
	पूर्ण,
पूर्ण,
[C(DTLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_MISS)]        = अणु 0x09, CNTR_ODD पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_MISS)]        = अणु 0x09, CNTR_ODD पूर्ण,
	पूर्ण,
पूर्ण,
[C(ITLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_MISS)]        = अणु 0x0c, CNTR_ODD पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_MISS)]        = अणु 0x0c, CNTR_ODD पूर्ण,
	पूर्ण,
पूर्ण,
[C(BPU)] = अणु
	/* Using the same code क्रम *HW_BRANCH* */
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]      = अणु 0x01, CNTR_EVEN पूर्ण,
		[C(RESULT_MISS)]        = अणु 0x01, CNTR_ODD पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)]      = अणु 0x01, CNTR_EVEN पूर्ण,
		[C(RESULT_MISS)]        = अणु 0x01, CNTR_ODD पूर्ण,
	पूर्ण,
पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mips_perf_event loongson3_cache_map2
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
[C(L1D)] = अणु
	/*
	 * Like some other architectures (e.g. ARM), the perक्रमmance
	 * counters करोn't dअगरferentiate between पढ़ो and ग_लिखो
	 * accesses/misses, so this isn't strictly correct, but it's the
	 * best we can करो. Writes and पढ़ोs get combined.
	 */
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x156, CNTR_ALL पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x155, CNTR_ALL पूर्ण,
		[C(RESULT_MISS)]        = अणु 0x153, CNTR_ALL पूर्ण,
	पूर्ण,
पूर्ण,
[C(L1I)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_MISS)]	= अणु 0x18, CNTR_ALL पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_MISS)]        = अणु 0x18, CNTR_ALL पूर्ण,
	पूर्ण,
पूर्ण,
[C(LL)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x1b6, CNTR_ALL पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x1b7, CNTR_ALL पूर्ण,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x1bf, CNTR_ALL पूर्ण,
	पूर्ण,
पूर्ण,
[C(DTLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_MISS)]        = अणु 0x92, CNTR_ALL पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_MISS)]        = अणु 0x92, CNTR_ALL पूर्ण,
	पूर्ण,
पूर्ण,
[C(ITLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_MISS)]	= अणु 0x1a, CNTR_ALL पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_MISS)]	= अणु 0x1a, CNTR_ALL पूर्ण,
	पूर्ण,
पूर्ण,
[C(BPU)] = अणु
	/* Using the same code क्रम *HW_BRANCH* */
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]      = अणु 0x94, CNTR_ALL पूर्ण,
		[C(RESULT_MISS)]        = अणु 0x9c, CNTR_ALL पूर्ण,
	पूर्ण,
पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mips_perf_event loongson3_cache_map3
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
[C(L1D)] = अणु
	/*
	 * Like some other architectures (e.g. ARM), the perक्रमmance
	 * counters करोn't dअगरferentiate between पढ़ो and ग_लिखो
	 * accesses/misses, so this isn't strictly correct, but it's the
	 * best we can करो. Writes and पढ़ोs get combined.
	 */
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]      = अणु 0x1e, CNTR_ALL पूर्ण,
		[C(RESULT_MISS)]        = अणु 0x1f, CNTR_ALL पूर्ण,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0xaa, CNTR_ALL पूर्ण,
		[C(RESULT_MISS)]	= अणु 0xa9, CNTR_ALL पूर्ण,
	पूर्ण,
पूर्ण,
[C(L1I)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x1c, CNTR_ALL पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x1d, CNTR_ALL पूर्ण,
	पूर्ण,
पूर्ण,
[C(LL)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x2e, CNTR_ALL पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x2f, CNTR_ALL पूर्ण,
	पूर्ण,
पूर्ण,
[C(DTLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]      = अणु 0x14, CNTR_ALL पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x1b, CNTR_ALL पूर्ण,
	पूर्ण,
पूर्ण,
[C(ITLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_MISS)]	= अणु 0x1a, CNTR_ALL पूर्ण,
	पूर्ण,
पूर्ण,
[C(BPU)] = अणु
	/* Using the same code क्रम *HW_BRANCH* */
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]      = अणु 0x02, CNTR_ALL पूर्ण,
		[C(RESULT_MISS)]        = अणु 0x08, CNTR_ALL पूर्ण,
	पूर्ण,
पूर्ण,
पूर्ण;

/* BMIPS5000 */
अटल स्थिर काष्ठा mips_perf_event bmips5000_cache_map
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
[C(L1D)] = अणु
	/*
	 * Like some other architectures (e.g. ARM), the perक्रमmance
	 * counters करोn't dअगरferentiate between पढ़ो and ग_लिखो
	 * accesses/misses, so this isn't strictly correct, but it's the
	 * best we can करो. Writes and पढ़ोs get combined.
	 */
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 12, CNTR_EVEN, T पूर्ण,
		[C(RESULT_MISS)]	= अणु 12, CNTR_ODD, T पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)]	= अणु 12, CNTR_EVEN, T पूर्ण,
		[C(RESULT_MISS)]	= अणु 12, CNTR_ODD, T पूर्ण,
	पूर्ण,
पूर्ण,
[C(L1I)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 10, CNTR_EVEN, T पूर्ण,
		[C(RESULT_MISS)]	= अणु 10, CNTR_ODD, T पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)]	= अणु 10, CNTR_EVEN, T पूर्ण,
		[C(RESULT_MISS)]	= अणु 10, CNTR_ODD, T पूर्ण,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)]	= अणु 23, CNTR_EVEN, T पूर्ण,
		/*
		 * Note that MIPS has only "hit" events countable क्रम
		 * the prefetch operation.
		 */
	पूर्ण,
पूर्ण,
[C(LL)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 28, CNTR_EVEN, P पूर्ण,
		[C(RESULT_MISS)]	= अणु 28, CNTR_ODD, P पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)]	= अणु 28, CNTR_EVEN, P पूर्ण,
		[C(RESULT_MISS)]	= अणु 28, CNTR_ODD, P पूर्ण,
	पूर्ण,
पूर्ण,
[C(BPU)] = अणु
	/* Using the same code क्रम *HW_BRANCH* */
	[C(OP_READ)] = अणु
		[C(RESULT_MISS)]	= अणु 0x02, CNTR_ODD, T पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_MISS)]	= अणु 0x02, CNTR_ODD, T पूर्ण,
	पूर्ण,
पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mips_perf_event octeon_cache_map
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
[C(L1D)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x2b, CNTR_ALL पूर्ण,
		[C(RESULT_MISS)]	= अणु 0x2e, CNTR_ALL पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x30, CNTR_ALL पूर्ण,
	पूर्ण,
पूर्ण,
[C(L1I)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x18, CNTR_ALL पूर्ण,
	पूर्ण,
	[C(OP_PREFETCH)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x19, CNTR_ALL पूर्ण,
	पूर्ण,
पूर्ण,
[C(DTLB)] = अणु
	/*
	 * Only general DTLB misses are counted use the same event क्रम
	 * पढ़ो and ग_लिखो.
	 */
	[C(OP_READ)] = अणु
		[C(RESULT_MISS)]	= अणु 0x35, CNTR_ALL पूर्ण,
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_MISS)]	= अणु 0x35, CNTR_ALL पूर्ण,
	पूर्ण,
पूर्ण,
[C(ITLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_MISS)]	= अणु 0x37, CNTR_ALL पूर्ण,
	पूर्ण,
पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mips_perf_event xlp_cache_map
				[PERF_COUNT_HW_CACHE_MAX]
				[PERF_COUNT_HW_CACHE_OP_MAX]
				[PERF_COUNT_HW_CACHE_RESULT_MAX] = अणु
[C(L1D)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x31, CNTR_ALL पूर्ण, /* PAPI_L1_DCR */
		[C(RESULT_MISS)]	= अणु 0x30, CNTR_ALL पूर्ण, /* PAPI_L1_LDM */
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x2f, CNTR_ALL पूर्ण, /* PAPI_L1_DCW */
		[C(RESULT_MISS)]	= अणु 0x2e, CNTR_ALL पूर्ण, /* PAPI_L1_STM */
	पूर्ण,
पूर्ण,
[C(L1I)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x04, CNTR_ALL पूर्ण, /* PAPI_L1_ICA */
		[C(RESULT_MISS)]	= अणु 0x07, CNTR_ALL पूर्ण, /* PAPI_L1_ICM */
	पूर्ण,
पूर्ण,
[C(LL)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x35, CNTR_ALL पूर्ण, /* PAPI_L2_DCR */
		[C(RESULT_MISS)]	= अणु 0x37, CNTR_ALL पूर्ण, /* PAPI_L2_LDM */
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_ACCESS)]	= अणु 0x34, CNTR_ALL पूर्ण, /* PAPI_L2_DCA */
		[C(RESULT_MISS)]	= अणु 0x36, CNTR_ALL पूर्ण, /* PAPI_L2_DCM */
	पूर्ण,
पूर्ण,
[C(DTLB)] = अणु
	/*
	 * Only general DTLB misses are counted use the same event क्रम
	 * पढ़ो and ग_लिखो.
	 */
	[C(OP_READ)] = अणु
		[C(RESULT_MISS)]	= अणु 0x2d, CNTR_ALL पूर्ण, /* PAPI_TLB_DM */
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_MISS)]	= अणु 0x2d, CNTR_ALL पूर्ण, /* PAPI_TLB_DM */
	पूर्ण,
पूर्ण,
[C(ITLB)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_MISS)]	= अणु 0x08, CNTR_ALL पूर्ण, /* PAPI_TLB_IM */
	पूर्ण,
	[C(OP_WRITE)] = अणु
		[C(RESULT_MISS)]	= अणु 0x08, CNTR_ALL पूर्ण, /* PAPI_TLB_IM */
	पूर्ण,
पूर्ण,
[C(BPU)] = अणु
	[C(OP_READ)] = अणु
		[C(RESULT_MISS)]	= अणु 0x25, CNTR_ALL पूर्ण,
	पूर्ण,
पूर्ण,
पूर्ण;

अटल पूर्णांक __hw_perf_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event_attr *attr = &event->attr;
	काष्ठा hw_perf_event *hwc = &event->hw;
	स्थिर काष्ठा mips_perf_event *pev;
	पूर्णांक err;

	/* Returning MIPS event descriptor क्रम generic perf event. */
	अगर (PERF_TYPE_HARDWARE == event->attr.type) अणु
		अगर (event->attr.config >= PERF_COUNT_HW_MAX)
			वापस -EINVAL;
		pev = mipspmu_map_general_event(event->attr.config);
	पूर्ण अन्यथा अगर (PERF_TYPE_HW_CACHE == event->attr.type) अणु
		pev = mipspmu_map_cache_event(event->attr.config);
	पूर्ण अन्यथा अगर (PERF_TYPE_RAW == event->attr.type) अणु
		/* We are working on the global raw event. */
		mutex_lock(&raw_event_mutex);
		pev = mipspmu.map_raw_event(event->attr.config);
	पूर्ण अन्यथा अणु
		/* The event type is not (yet) supported. */
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (IS_ERR(pev)) अणु
		अगर (PERF_TYPE_RAW == event->attr.type)
			mutex_unlock(&raw_event_mutex);
		वापस PTR_ERR(pev);
	पूर्ण

	/*
	 * We allow max flexibility on how each inभागidual counter shared
	 * by the single CPU operates (the mode exclusion and the range).
	 */
	hwc->config_base = MIPS_PERFCTRL_IE;

	hwc->event_base = mipspmu_perf_event_encode(pev);
	अगर (PERF_TYPE_RAW == event->attr.type)
		mutex_unlock(&raw_event_mutex);

	अगर (!attr->exclude_user)
		hwc->config_base |= MIPS_PERFCTRL_U;
	अगर (!attr->exclude_kernel) अणु
		hwc->config_base |= MIPS_PERFCTRL_K;
		/* MIPS kernel mode: KSU == 00b || EXL == 1 || ERL == 1 */
		hwc->config_base |= MIPS_PERFCTRL_EXL;
	पूर्ण
	अगर (!attr->exclude_hv)
		hwc->config_base |= MIPS_PERFCTRL_S;

	hwc->config_base &= M_PERFCTL_CONFIG_MASK;
	/*
	 * The event can beदीर्घ to another cpu. We करो not assign a local
	 * counter क्रम it क्रम now.
	 */
	hwc->idx = -1;
	hwc->config = 0;

	अगर (!hwc->sample_period) अणु
		hwc->sample_period  = mipspmu.max_period;
		hwc->last_period    = hwc->sample_period;
		local64_set(&hwc->period_left, hwc->sample_period);
	पूर्ण

	err = 0;
	अगर (event->group_leader != event)
		err = validate_group(event);

	event->destroy = hw_perf_event_destroy;

	अगर (err)
		event->destroy(event);

	वापस err;
पूर्ण

अटल व्योम छोड़ो_local_counters(व्योम)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	पूर्णांक ctr = mipspmu.num_counters;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	करो अणु
		ctr--;
		cpuc->saved_ctrl[ctr] = mipsxx_pmu_पढ़ो_control(ctr);
		mipsxx_pmu_ग_लिखो_control(ctr, cpuc->saved_ctrl[ctr] &
					 ~M_PERFCTL_COUNT_EVENT_WHENEVER);
	पूर्ण जबतक (ctr > 0);
	local_irq_restore(flags);
पूर्ण

अटल व्योम resume_local_counters(व्योम)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	पूर्णांक ctr = mipspmu.num_counters;

	करो अणु
		ctr--;
		mipsxx_pmu_ग_लिखो_control(ctr, cpuc->saved_ctrl[ctr]);
	पूर्ण जबतक (ctr > 0);
पूर्ण

अटल पूर्णांक mipsxx_pmu_handle_shared_irq(व्योम)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा perf_sample_data data;
	अचिन्हित पूर्णांक counters = mipspmu.num_counters;
	u64 counter;
	पूर्णांक n, handled = IRQ_NONE;
	काष्ठा pt_regs *regs;

	अगर (cpu_has_perf_cntr_पूर्णांकr_bit && !(पढ़ो_c0_cause() & CAUSEF_PCI))
		वापस handled;
	/*
	 * First we छोड़ो the local counters, so that when we are locked
	 * here, the counters are all छोड़ोd. When it माला_लो locked due to
	 * perf_disable(), the समयr पूर्णांकerrupt handler will be delayed.
	 *
	 * See also mipsxx_pmu_start().
	 */
	छोड़ो_local_counters();
#अगर_घोषित CONFIG_MIPS_PERF_SHARED_TC_COUNTERS
	पढ़ो_lock(&pmuपूर्णांक_rwlock);
#पूर्ण_अगर

	regs = get_irq_regs();

	perf_sample_data_init(&data, 0, 0);

	क्रम (n = counters - 1; n >= 0; n--) अणु
		अगर (!test_bit(n, cpuc->used_mask))
			जारी;

		counter = mipspmu.पढ़ो_counter(n);
		अगर (!(counter & mipspmu.overflow))
			जारी;

		handle_associated_event(cpuc, n, &data, regs);
		handled = IRQ_HANDLED;
	पूर्ण

#अगर_घोषित CONFIG_MIPS_PERF_SHARED_TC_COUNTERS
	पढ़ो_unlock(&pmuपूर्णांक_rwlock);
#पूर्ण_अगर
	resume_local_counters();

	/*
	 * Do all the work क्रम the pending perf events. We can करो this
	 * in here because the perक्रमmance counter पूर्णांकerrupt is a regular
	 * पूर्णांकerrupt, not NMI.
	 */
	अगर (handled == IRQ_HANDLED)
		irq_work_run();

	वापस handled;
पूर्ण

अटल irqवापस_t mipsxx_pmu_handle_irq(पूर्णांक irq, व्योम *dev)
अणु
	वापस mipsxx_pmu_handle_shared_irq();
पूर्ण

/* 24K */
#घोषणा IS_BOTH_COUNTERS_24K_EVENT(b)					\
	((b) == 0 || (b) == 1 || (b) == 11)

/* 34K */
#घोषणा IS_BOTH_COUNTERS_34K_EVENT(b)					\
	((b) == 0 || (b) == 1 || (b) == 11)
#अगर_घोषित CONFIG_MIPS_MT_SMP
#घोषणा IS_RANGE_P_34K_EVENT(r, b)					\
	((b) == 0 || (r) == 18 || (b) == 21 || (b) == 22 ||		\
	 (b) == 25 || (b) == 39 || (r) == 44 || (r) == 174 ||		\
	 (r) == 176 || ((b) >= 50 && (b) <= 55) ||			\
	 ((b) >= 64 && (b) <= 67))
#घोषणा IS_RANGE_V_34K_EVENT(r) ((r) == 47)
#पूर्ण_अगर

/* 74K */
#घोषणा IS_BOTH_COUNTERS_74K_EVENT(b)					\
	((b) == 0 || (b) == 1)

/* proAptiv */
#घोषणा IS_BOTH_COUNTERS_PROAPTIV_EVENT(b)				\
	((b) == 0 || (b) == 1)
/* P5600 */
#घोषणा IS_BOTH_COUNTERS_P5600_EVENT(b)					\
	((b) == 0 || (b) == 1)

/* 1004K */
#घोषणा IS_BOTH_COUNTERS_1004K_EVENT(b)					\
	((b) == 0 || (b) == 1 || (b) == 11)
#अगर_घोषित CONFIG_MIPS_MT_SMP
#घोषणा IS_RANGE_P_1004K_EVENT(r, b)					\
	((b) == 0 || (r) == 18 || (b) == 21 || (b) == 22 ||		\
	 (b) == 25 || (b) == 36 || (b) == 39 || (r) == 44 ||		\
	 (r) == 174 || (r) == 176 || ((b) >= 50 && (b) <= 59) ||	\
	 (r) == 188 || (b) == 61 || (b) == 62 ||			\
	 ((b) >= 64 && (b) <= 67))
#घोषणा IS_RANGE_V_1004K_EVENT(r)	((r) == 47)
#पूर्ण_अगर

/* पूर्णांकerAptiv */
#घोषणा IS_BOTH_COUNTERS_INTERAPTIV_EVENT(b)				\
	((b) == 0 || (b) == 1 || (b) == 11)
#अगर_घोषित CONFIG_MIPS_MT_SMP
/* The P/V/T info is not provided क्रम "(b) == 38" in SUM, assume P. */
#घोषणा IS_RANGE_P_INTERAPTIV_EVENT(r, b)				\
	((b) == 0 || (r) == 18 || (b) == 21 || (b) == 22 ||		\
	 (b) == 25 || (b) == 36 || (b) == 38 || (b) == 39 ||		\
	 (r) == 44 || (r) == 174 || (r) == 176 || ((b) >= 50 &&		\
	 (b) <= 59) || (r) == 188 || (b) == 61 || (b) == 62 ||		\
	 ((b) >= 64 && (b) <= 67))
#घोषणा IS_RANGE_V_INTERAPTIV_EVENT(r)	((r) == 47 || (r) == 175)
#पूर्ण_अगर

/* BMIPS5000 */
#घोषणा IS_BOTH_COUNTERS_BMIPS5000_EVENT(b)				\
	((b) == 0 || (b) == 1)


/*
 * For most cores the user can use 0-255 raw events, where 0-127 क्रम the events
 * of even counters, and 128-255 क्रम odd counters. Note that bit 7 is used to
 * indicate the even/odd bank selector. So, क्रम example, when user wants to take
 * the Event Num of 15 क्रम odd counters (by referring to the user manual), then
 * 128 needs to be added to 15 as the input क्रम the event config, i.e., 143 (0x8F)
 * to be used.
 *
 * Some newer cores have even more events, in which हाल the user can use raw
 * events 0-511, where 0-255 are क्रम the events of even counters, and 256-511
 * are क्रम odd counters, so bit 8 is used to indicate the even/odd bank selector.
 */
अटल स्थिर काष्ठा mips_perf_event *mipsxx_pmu_map_raw_event(u64 config)
अणु
	/* currently most cores have 7-bit event numbers */
	पूर्णांक pmu_type;
	अचिन्हित पूर्णांक raw_id = config & 0xff;
	अचिन्हित पूर्णांक base_id = raw_id & 0x7f;

	चयन (current_cpu_type()) अणु
	हाल CPU_24K:
		अगर (IS_BOTH_COUNTERS_24K_EVENT(base_id))
			raw_event.cntr_mask = CNTR_EVEN | CNTR_ODD;
		अन्यथा
			raw_event.cntr_mask =
				raw_id > 127 ? CNTR_ODD : CNTR_EVEN;
#अगर_घोषित CONFIG_MIPS_MT_SMP
		/*
		 * This is actually करोing nothing. Non-multithपढ़ोing
		 * CPUs will not check and calculate the range.
		 */
		raw_event.range = P;
#पूर्ण_अगर
		अवरोध;
	हाल CPU_34K:
		अगर (IS_BOTH_COUNTERS_34K_EVENT(base_id))
			raw_event.cntr_mask = CNTR_EVEN | CNTR_ODD;
		अन्यथा
			raw_event.cntr_mask =
				raw_id > 127 ? CNTR_ODD : CNTR_EVEN;
#अगर_घोषित CONFIG_MIPS_MT_SMP
		अगर (IS_RANGE_P_34K_EVENT(raw_id, base_id))
			raw_event.range = P;
		अन्यथा अगर (unlikely(IS_RANGE_V_34K_EVENT(raw_id)))
			raw_event.range = V;
		अन्यथा
			raw_event.range = T;
#पूर्ण_अगर
		अवरोध;
	हाल CPU_74K:
	हाल CPU_1074K:
		अगर (IS_BOTH_COUNTERS_74K_EVENT(base_id))
			raw_event.cntr_mask = CNTR_EVEN | CNTR_ODD;
		अन्यथा
			raw_event.cntr_mask =
				raw_id > 127 ? CNTR_ODD : CNTR_EVEN;
#अगर_घोषित CONFIG_MIPS_MT_SMP
		raw_event.range = P;
#पूर्ण_अगर
		अवरोध;
	हाल CPU_PROAPTIV:
		अगर (IS_BOTH_COUNTERS_PROAPTIV_EVENT(base_id))
			raw_event.cntr_mask = CNTR_EVEN | CNTR_ODD;
		अन्यथा
			raw_event.cntr_mask =
				raw_id > 127 ? CNTR_ODD : CNTR_EVEN;
#अगर_घोषित CONFIG_MIPS_MT_SMP
		raw_event.range = P;
#पूर्ण_अगर
		अवरोध;
	हाल CPU_P5600:
	हाल CPU_P6600:
		/* 8-bit event numbers */
		raw_id = config & 0x1ff;
		base_id = raw_id & 0xff;
		अगर (IS_BOTH_COUNTERS_P5600_EVENT(base_id))
			raw_event.cntr_mask = CNTR_EVEN | CNTR_ODD;
		अन्यथा
			raw_event.cntr_mask =
				raw_id > 255 ? CNTR_ODD : CNTR_EVEN;
#अगर_घोषित CONFIG_MIPS_MT_SMP
		raw_event.range = P;
#पूर्ण_अगर
		अवरोध;
	हाल CPU_I6400:
	हाल CPU_I6500:
		/* 8-bit event numbers */
		base_id = config & 0xff;
		raw_event.cntr_mask = CNTR_EVEN | CNTR_ODD;
		अवरोध;
	हाल CPU_1004K:
		अगर (IS_BOTH_COUNTERS_1004K_EVENT(base_id))
			raw_event.cntr_mask = CNTR_EVEN | CNTR_ODD;
		अन्यथा
			raw_event.cntr_mask =
				raw_id > 127 ? CNTR_ODD : CNTR_EVEN;
#अगर_घोषित CONFIG_MIPS_MT_SMP
		अगर (IS_RANGE_P_1004K_EVENT(raw_id, base_id))
			raw_event.range = P;
		अन्यथा अगर (unlikely(IS_RANGE_V_1004K_EVENT(raw_id)))
			raw_event.range = V;
		अन्यथा
			raw_event.range = T;
#पूर्ण_अगर
		अवरोध;
	हाल CPU_INTERAPTIV:
		अगर (IS_BOTH_COUNTERS_INTERAPTIV_EVENT(base_id))
			raw_event.cntr_mask = CNTR_EVEN | CNTR_ODD;
		अन्यथा
			raw_event.cntr_mask =
				raw_id > 127 ? CNTR_ODD : CNTR_EVEN;
#अगर_घोषित CONFIG_MIPS_MT_SMP
		अगर (IS_RANGE_P_INTERAPTIV_EVENT(raw_id, base_id))
			raw_event.range = P;
		अन्यथा अगर (unlikely(IS_RANGE_V_INTERAPTIV_EVENT(raw_id)))
			raw_event.range = V;
		अन्यथा
			raw_event.range = T;
#पूर्ण_अगर
		अवरोध;
	हाल CPU_BMIPS5000:
		अगर (IS_BOTH_COUNTERS_BMIPS5000_EVENT(base_id))
			raw_event.cntr_mask = CNTR_EVEN | CNTR_ODD;
		अन्यथा
			raw_event.cntr_mask =
				raw_id > 127 ? CNTR_ODD : CNTR_EVEN;
		अवरोध;
	हाल CPU_LOONGSON64:
		pmu_type = get_loongson3_pmu_type();

		चयन (pmu_type) अणु
		हाल LOONGSON_PMU_TYPE1:
			raw_event.cntr_mask =
				raw_id > 127 ? CNTR_ODD : CNTR_EVEN;
			अवरोध;
		हाल LOONGSON_PMU_TYPE2:
			base_id = config & 0x3ff;
			raw_event.cntr_mask = CNTR_ALL;

			अगर ((base_id >= 1 && base_id < 28) ||
				(base_id >= 64 && base_id < 90) ||
				(base_id >= 128 && base_id < 164) ||
				(base_id >= 192 && base_id < 200) ||
				(base_id >= 256 && base_id < 275) ||
				(base_id >= 320 && base_id < 361) ||
				(base_id >= 384 && base_id < 574))
				अवरोध;

			वापस ERR_PTR(-EOPNOTSUPP);
		हाल LOONGSON_PMU_TYPE3:
			base_id = raw_id;
			raw_event.cntr_mask = CNTR_ALL;
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण

	raw_event.event_id = base_id;

	वापस &raw_event;
पूर्ण

अटल स्थिर काष्ठा mips_perf_event *octeon_pmu_map_raw_event(u64 config)
अणु
	अचिन्हित पूर्णांक base_id = config & 0x7f;
	अचिन्हित पूर्णांक event_max;


	raw_event.cntr_mask = CNTR_ALL;
	raw_event.event_id = base_id;

	अगर (current_cpu_type() == CPU_CAVIUM_OCTEON3)
		event_max = 0x5f;
	अन्यथा अगर (current_cpu_type() == CPU_CAVIUM_OCTEON2)
		event_max = 0x42;
	अन्यथा
		event_max = 0x3a;

	अगर (base_id > event_max) अणु
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण

	चयन (base_id) अणु
	हाल 0x00:
	हाल 0x0f:
	हाल 0x1e:
	हाल 0x1f:
	हाल 0x2f:
	हाल 0x34:
	हाल 0x3e ... 0x3f:
		वापस ERR_PTR(-EOPNOTSUPP);
	शेष:
		अवरोध;
	पूर्ण

	वापस &raw_event;
पूर्ण

अटल स्थिर काष्ठा mips_perf_event *xlp_pmu_map_raw_event(u64 config)
अणु
	अचिन्हित पूर्णांक raw_id = config & 0xff;

	/* Only 1-63 are defined */
	अगर ((raw_id < 0x01) || (raw_id > 0x3f))
		वापस ERR_PTR(-EOPNOTSUPP);

	raw_event.cntr_mask = CNTR_ALL;
	raw_event.event_id = raw_id;

	वापस &raw_event;
पूर्ण

अटल पूर्णांक __init
init_hw_perf_events(व्योम)
अणु
	पूर्णांक counters, irq, pmu_type;

	pr_info("Performance counters: ");

	counters = n_counters();
	अगर (counters == 0) अणु
		pr_cont("No available PMU.\n");
		वापस -ENODEV;
	पूर्ण

#अगर_घोषित CONFIG_MIPS_PERF_SHARED_TC_COUNTERS
	अगर (!cpu_has_mipsmt_pertccounters)
		counters = counters_total_to_per_cpu(counters);
#पूर्ण_अगर

	अगर (get_c0_perfcount_पूर्णांक)
		irq = get_c0_perfcount_पूर्णांक();
	अन्यथा अगर (cp0_perfcount_irq >= 0)
		irq = MIPS_CPU_IRQ_BASE + cp0_perfcount_irq;
	अन्यथा
		irq = -1;

	mipspmu.map_raw_event = mipsxx_pmu_map_raw_event;

	चयन (current_cpu_type()) अणु
	हाल CPU_24K:
		mipspmu.name = "mips/24K";
		mipspmu.general_event_map = &mipsxxcore_event_map;
		mipspmu.cache_event_map = &mipsxxcore_cache_map;
		अवरोध;
	हाल CPU_34K:
		mipspmu.name = "mips/34K";
		mipspmu.general_event_map = &mipsxxcore_event_map;
		mipspmu.cache_event_map = &mipsxxcore_cache_map;
		अवरोध;
	हाल CPU_74K:
		mipspmu.name = "mips/74K";
		mipspmu.general_event_map = &mipsxxcore_event_map2;
		mipspmu.cache_event_map = &mipsxxcore_cache_map2;
		अवरोध;
	हाल CPU_PROAPTIV:
		mipspmu.name = "mips/proAptiv";
		mipspmu.general_event_map = &mipsxxcore_event_map2;
		mipspmu.cache_event_map = &mipsxxcore_cache_map2;
		अवरोध;
	हाल CPU_P5600:
		mipspmu.name = "mips/P5600";
		mipspmu.general_event_map = &mipsxxcore_event_map2;
		mipspmu.cache_event_map = &mipsxxcore_cache_map2;
		अवरोध;
	हाल CPU_P6600:
		mipspmu.name = "mips/P6600";
		mipspmu.general_event_map = &mipsxxcore_event_map2;
		mipspmu.cache_event_map = &mipsxxcore_cache_map2;
		अवरोध;
	हाल CPU_I6400:
		mipspmu.name = "mips/I6400";
		mipspmu.general_event_map = &i6x00_event_map;
		mipspmu.cache_event_map = &i6x00_cache_map;
		अवरोध;
	हाल CPU_I6500:
		mipspmu.name = "mips/I6500";
		mipspmu.general_event_map = &i6x00_event_map;
		mipspmu.cache_event_map = &i6x00_cache_map;
		अवरोध;
	हाल CPU_1004K:
		mipspmu.name = "mips/1004K";
		mipspmu.general_event_map = &mipsxxcore_event_map;
		mipspmu.cache_event_map = &mipsxxcore_cache_map;
		अवरोध;
	हाल CPU_1074K:
		mipspmu.name = "mips/1074K";
		mipspmu.general_event_map = &mipsxxcore_event_map;
		mipspmu.cache_event_map = &mipsxxcore_cache_map;
		अवरोध;
	हाल CPU_INTERAPTIV:
		mipspmu.name = "mips/interAptiv";
		mipspmu.general_event_map = &mipsxxcore_event_map;
		mipspmu.cache_event_map = &mipsxxcore_cache_map;
		अवरोध;
	हाल CPU_LOONGSON32:
		mipspmu.name = "mips/loongson1";
		mipspmu.general_event_map = &mipsxxcore_event_map;
		mipspmu.cache_event_map = &mipsxxcore_cache_map;
		अवरोध;
	हाल CPU_LOONGSON64:
		mipspmu.name = "mips/loongson3";
		pmu_type = get_loongson3_pmu_type();

		चयन (pmu_type) अणु
		हाल LOONGSON_PMU_TYPE1:
			counters = 2;
			mipspmu.general_event_map = &loongson3_event_map1;
			mipspmu.cache_event_map = &loongson3_cache_map1;
			अवरोध;
		हाल LOONGSON_PMU_TYPE2:
			counters = 4;
			mipspmu.general_event_map = &loongson3_event_map2;
			mipspmu.cache_event_map = &loongson3_cache_map2;
			अवरोध;
		हाल LOONGSON_PMU_TYPE3:
			counters = 4;
			mipspmu.general_event_map = &loongson3_event_map3;
			mipspmu.cache_event_map = &loongson3_cache_map3;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल CPU_CAVIUM_OCTEON:
	हाल CPU_CAVIUM_OCTEON_PLUS:
	हाल CPU_CAVIUM_OCTEON2:
	हाल CPU_CAVIUM_OCTEON3:
		mipspmu.name = "octeon";
		mipspmu.general_event_map = &octeon_event_map;
		mipspmu.cache_event_map = &octeon_cache_map;
		mipspmu.map_raw_event = octeon_pmu_map_raw_event;
		अवरोध;
	हाल CPU_BMIPS5000:
		mipspmu.name = "BMIPS5000";
		mipspmu.general_event_map = &bmips5000_event_map;
		mipspmu.cache_event_map = &bmips5000_cache_map;
		अवरोध;
	हाल CPU_XLP:
		mipspmu.name = "xlp";
		mipspmu.general_event_map = &xlp_event_map;
		mipspmu.cache_event_map = &xlp_cache_map;
		mipspmu.map_raw_event = xlp_pmu_map_raw_event;
		अवरोध;
	शेष:
		pr_cont("Either hardware does not support performance "
			"counters, or not yet implemented.\n");
		वापस -ENODEV;
	पूर्ण

	mipspmu.num_counters = counters;
	mipspmu.irq = irq;

	अगर (पढ़ो_c0_perfctrl0() & MIPS_PERFCTRL_W) अणु
		अगर (get_loongson3_pmu_type() == LOONGSON_PMU_TYPE2) अणु
			counter_bits = 48;
			mipspmu.max_period = (1ULL << 47) - 1;
			mipspmu.valid_count = (1ULL << 47) - 1;
			mipspmu.overflow = 1ULL << 47;
		पूर्ण अन्यथा अणु
			counter_bits = 64;
			mipspmu.max_period = (1ULL << 63) - 1;
			mipspmu.valid_count = (1ULL << 63) - 1;
			mipspmu.overflow = 1ULL << 63;
		पूर्ण
		mipspmu.पढ़ो_counter = mipsxx_pmu_पढ़ो_counter_64;
		mipspmu.ग_लिखो_counter = mipsxx_pmu_ग_लिखो_counter_64;
	पूर्ण अन्यथा अणु
		counter_bits = 32;
		mipspmu.max_period = (1ULL << 31) - 1;
		mipspmu.valid_count = (1ULL << 31) - 1;
		mipspmu.overflow = 1ULL << 31;
		mipspmu.पढ़ो_counter = mipsxx_pmu_पढ़ो_counter;
		mipspmu.ग_लिखो_counter = mipsxx_pmu_ग_लिखो_counter;
	पूर्ण

	on_each_cpu(reset_counters, (व्योम *)(दीर्घ)counters, 1);

	pr_cont("%s PMU enabled, %d %d-bit counters available to each "
		"CPU, irq %d%s\n", mipspmu.name, counters, counter_bits, irq,
		irq < 0 ? " (share with timer interrupt)" : "");

	perf_pmu_रेजिस्टर(&pmu, "cpu", PERF_TYPE_RAW);

	वापस 0;
पूर्ण
early_initcall(init_hw_perf_events);
