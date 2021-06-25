<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम the L3 cache PMUs in Qualcomm Technologies chips.
 *
 * The driver supports a distributed cache architecture where the overall
 * cache क्रम a socket is comprised of multiple slices each with its own PMU.
 * Access to each inभागidual PMU is provided even though all CPUs share all
 * the slices. User space needs to aggregate to inभागidual counts to provide
 * a global picture.
 *
 * See Documentation/admin-guide/perf/qcom_l3_pmu.rst क्रम more details.
 *
 * Copyright (c) 2015-2017, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/platक्रमm_device.h>

/*
 * General स्थिरants
 */

/* Number of counters on each PMU */
#घोषणा L3_NUM_COUNTERS  8
/* Mask क्रम the event type field within perf_event_attr.config and EVTYPE reg */
#घोषणा L3_EVTYPE_MASK   0xFF
/*
 * Bit position of the 'long counter' flag within perf_event_attr.config.
 * Reserve some space between the event type and this flag to allow expansion
 * in the event type field.
 */
#घोषणा L3_EVENT_LC_BIT  32

/*
 * Register offsets
 */

/* Perfmon रेजिस्टरs */
#घोषणा L3_HML3_PM_CR       0x000
#घोषणा L3_HML3_PM_EVCNTR(__cntr) (0x420 + ((__cntr) & 0x7) * 8)
#घोषणा L3_HML3_PM_CNTCTL(__cntr) (0x120 + ((__cntr) & 0x7) * 8)
#घोषणा L3_HML3_PM_EVTYPE(__cntr) (0x220 + ((__cntr) & 0x7) * 8)
#घोषणा L3_HML3_PM_FILTRA   0x300
#घोषणा L3_HML3_PM_FILTRB   0x308
#घोषणा L3_HML3_PM_FILTRC   0x310
#घोषणा L3_HML3_PM_FILTRAM  0x304
#घोषणा L3_HML3_PM_FILTRBM  0x30C
#घोषणा L3_HML3_PM_FILTRCM  0x314

/* Basic counter रेजिस्टरs */
#घोषणा L3_M_BC_CR         0x500
#घोषणा L3_M_BC_SATROLL_CR 0x504
#घोषणा L3_M_BC_CNTENSET   0x508
#घोषणा L3_M_BC_CNTENCLR   0x50C
#घोषणा L3_M_BC_INTENSET   0x510
#घोषणा L3_M_BC_INTENCLR   0x514
#घोषणा L3_M_BC_GANG       0x718
#घोषणा L3_M_BC_OVSR       0x740
#घोषणा L3_M_BC_IRQCTL     0x96C

/*
 * Bit field definitions
 */

/* L3_HML3_PM_CR */
#घोषणा PM_CR_RESET           (0)

/* L3_HML3_PM_XCNTCTL/L3_HML3_PM_CNTCTLx */
#घोषणा PMCNT_RESET           (0)

/* L3_HML3_PM_EVTYPEx */
#घोषणा EVSEL(__val)          ((__val) & L3_EVTYPE_MASK)

/* Reset value क्रम all the filter रेजिस्टरs */
#घोषणा PM_FLTR_RESET         (0)

/* L3_M_BC_CR */
#घोषणा BC_RESET              (1UL << 1)
#घोषणा BC_ENABLE             (1UL << 0)

/* L3_M_BC_SATROLL_CR */
#घोषणा BC_SATROLL_CR_RESET   (0)

/* L3_M_BC_CNTENSET */
#घोषणा PMCNTENSET(__cntr)    (1UL << ((__cntr) & 0x7))

/* L3_M_BC_CNTENCLR */
#घोषणा PMCNTENCLR(__cntr)    (1UL << ((__cntr) & 0x7))
#घोषणा BC_CNTENCLR_RESET     (0xFF)

/* L3_M_BC_INTENSET */
#घोषणा PMINTENSET(__cntr)    (1UL << ((__cntr) & 0x7))

/* L3_M_BC_INTENCLR */
#घोषणा PMINTENCLR(__cntr)    (1UL << ((__cntr) & 0x7))
#घोषणा BC_INTENCLR_RESET     (0xFF)

/* L3_M_BC_GANG */
#घोषणा GANG_EN(__cntr)       (1UL << ((__cntr) & 0x7))
#घोषणा BC_GANG_RESET         (0)

/* L3_M_BC_OVSR */
#घोषणा PMOVSRCLR(__cntr)     (1UL << ((__cntr) & 0x7))
#घोषणा PMOVSRCLR_RESET       (0xFF)

/* L3_M_BC_IRQCTL */
#घोषणा PMIRQONMSBEN(__cntr)  (1UL << ((__cntr) & 0x7))
#घोषणा BC_IRQCTL_RESET       (0x0)

/*
 * Events
 */

#घोषणा L3_EVENT_CYCLES		0x01
#घोषणा L3_EVENT_READ_HIT		0x20
#घोषणा L3_EVENT_READ_MISS		0x21
#घोषणा L3_EVENT_READ_HIT_D		0x22
#घोषणा L3_EVENT_READ_MISS_D		0x23
#घोषणा L3_EVENT_WRITE_HIT		0x24
#घोषणा L3_EVENT_WRITE_MISS		0x25

/*
 * Decoding of settings from perf_event_attr
 *
 * The config क्रमmat क्रम perf events is:
 * - config: bits 0-7: event type
 *           bit  32:  HW counter size requested, 0: 32 bits, 1: 64 bits
 */

अटल अंतरभूत u32 get_event_type(काष्ठा perf_event *event)
अणु
	वापस (event->attr.config) & L3_EVTYPE_MASK;
पूर्ण

अटल अंतरभूत bool event_uses_दीर्घ_counter(काष्ठा perf_event *event)
अणु
	वापस !!(event->attr.config & BIT_ULL(L3_EVENT_LC_BIT));
पूर्ण

अटल अंतरभूत पूर्णांक event_num_counters(काष्ठा perf_event *event)
अणु
	वापस event_uses_दीर्घ_counter(event) ? 2 : 1;
पूर्ण

/*
 * Main PMU, inherits from the core perf PMU type
 */
काष्ठा l3cache_pmu अणु
	काष्ठा pmu		pmu;
	काष्ठा hlist_node	node;
	व्योम __iomem		*regs;
	काष्ठा perf_event	*events[L3_NUM_COUNTERS];
	अचिन्हित दीर्घ		used_mask[BITS_TO_LONGS(L3_NUM_COUNTERS)];
	cpumask_t		cpumask;
पूर्ण;

#घोषणा to_l3cache_pmu(p) (container_of(p, काष्ठा l3cache_pmu, pmu))

/*
 * Type used to group hardware counter operations
 *
 * Used to implement two types of hardware counters, standard (32bits) and
 * दीर्घ (64bits). The hardware supports counter chaining which we use to
 * implement दीर्घ counters. This support is exposed via the 'lc' flag field
 * in perf_event_attr.config.
 */
काष्ठा l3cache_event_ops अणु
	/* Called to start event monitoring */
	व्योम (*start)(काष्ठा perf_event *event);
	/* Called to stop event monitoring */
	व्योम (*stop)(काष्ठा perf_event *event, पूर्णांक flags);
	/* Called to update the perf_event */
	व्योम (*update)(काष्ठा perf_event *event);
पूर्ण;

/*
 * Implementation of दीर्घ counter operations
 *
 * 64bit counters are implemented by chaining two of the 32bit physical
 * counters. The PMU only supports chaining of adjacent even/odd pairs
 * and क्रम simplicity the driver always configures the odd counter to
 * count the overflows of the lower-numbered even counter. Note that since
 * the resulting hardware counter is 64bits no IRQs are required to मुख्यtain
 * the software counter which is also 64bits.
 */

अटल व्योम qcom_l3_cache__64bit_counter_start(काष्ठा perf_event *event)
अणु
	काष्ठा l3cache_pmu *l3pmu = to_l3cache_pmu(event->pmu);
	पूर्णांक idx = event->hw.idx;
	u32 evsel = get_event_type(event);
	u32 gang;

	/* Set the odd counter to count the overflows of the even counter */
	gang = पढ़ोl_relaxed(l3pmu->regs + L3_M_BC_GANG);
	gang |= GANG_EN(idx + 1);
	ग_लिखोl_relaxed(gang, l3pmu->regs + L3_M_BC_GANG);

	/* Initialize the hardware counters and reset prev_count*/
	local64_set(&event->hw.prev_count, 0);
	ग_लिखोl_relaxed(0, l3pmu->regs + L3_HML3_PM_EVCNTR(idx + 1));
	ग_लिखोl_relaxed(0, l3pmu->regs + L3_HML3_PM_EVCNTR(idx));

	/*
	 * Set the event types, the upper half must use zero and the lower
	 * half the actual event type
	 */
	ग_लिखोl_relaxed(EVSEL(0), l3pmu->regs + L3_HML3_PM_EVTYPE(idx + 1));
	ग_लिखोl_relaxed(EVSEL(evsel), l3pmu->regs + L3_HML3_PM_EVTYPE(idx));

	/* Finally, enable the counters */
	ग_लिखोl_relaxed(PMCNT_RESET, l3pmu->regs + L3_HML3_PM_CNTCTL(idx + 1));
	ग_लिखोl_relaxed(PMCNTENSET(idx + 1), l3pmu->regs + L3_M_BC_CNTENSET);
	ग_लिखोl_relaxed(PMCNT_RESET, l3pmu->regs + L3_HML3_PM_CNTCTL(idx));
	ग_लिखोl_relaxed(PMCNTENSET(idx), l3pmu->regs + L3_M_BC_CNTENSET);
पूर्ण

अटल व्योम qcom_l3_cache__64bit_counter_stop(काष्ठा perf_event *event,
					      पूर्णांक flags)
अणु
	काष्ठा l3cache_pmu *l3pmu = to_l3cache_pmu(event->pmu);
	पूर्णांक idx = event->hw.idx;
	u32 gang = पढ़ोl_relaxed(l3pmu->regs + L3_M_BC_GANG);

	/* Disable the counters */
	ग_लिखोl_relaxed(PMCNTENCLR(idx), l3pmu->regs + L3_M_BC_CNTENCLR);
	ग_लिखोl_relaxed(PMCNTENCLR(idx + 1), l3pmu->regs + L3_M_BC_CNTENCLR);

	/* Disable chaining */
	ग_लिखोl_relaxed(gang & ~GANG_EN(idx + 1), l3pmu->regs + L3_M_BC_GANG);
पूर्ण

अटल व्योम qcom_l3_cache__64bit_counter_update(काष्ठा perf_event *event)
अणु
	काष्ठा l3cache_pmu *l3pmu = to_l3cache_pmu(event->pmu);
	पूर्णांक idx = event->hw.idx;
	u32 hi, lo;
	u64 prev, new;

	करो अणु
		prev = local64_पढ़ो(&event->hw.prev_count);
		करो अणु
			hi = पढ़ोl_relaxed(l3pmu->regs + L3_HML3_PM_EVCNTR(idx + 1));
			lo = पढ़ोl_relaxed(l3pmu->regs + L3_HML3_PM_EVCNTR(idx));
		पूर्ण जबतक (hi != पढ़ोl_relaxed(l3pmu->regs + L3_HML3_PM_EVCNTR(idx + 1)));
		new = ((u64)hi << 32) | lo;
	पूर्ण जबतक (local64_cmpxchg(&event->hw.prev_count, prev, new) != prev);

	local64_add(new - prev, &event->count);
पूर्ण

अटल स्थिर काष्ठा l3cache_event_ops event_ops_दीर्घ = अणु
	.start = qcom_l3_cache__64bit_counter_start,
	.stop = qcom_l3_cache__64bit_counter_stop,
	.update = qcom_l3_cache__64bit_counter_update,
पूर्ण;

/*
 * Implementation of standard counter operations
 *
 * 32bit counters use a single physical counter and a hardware feature that
 * निश्चितs the overflow IRQ on the toggling of the most signअगरicant bit in
 * the counter. This feature allows the counters to be left मुक्त-running
 * without needing the usual reprogramming required to properly handle races
 * during concurrent calls to update.
 */

अटल व्योम qcom_l3_cache__32bit_counter_start(काष्ठा perf_event *event)
अणु
	काष्ठा l3cache_pmu *l3pmu = to_l3cache_pmu(event->pmu);
	पूर्णांक idx = event->hw.idx;
	u32 evsel = get_event_type(event);
	u32 irqctl = पढ़ोl_relaxed(l3pmu->regs + L3_M_BC_IRQCTL);

	/* Set the counter to निश्चित the overflow IRQ on MSB toggling */
	ग_लिखोl_relaxed(irqctl | PMIRQONMSBEN(idx), l3pmu->regs + L3_M_BC_IRQCTL);

	/* Initialize the hardware counter and reset prev_count*/
	local64_set(&event->hw.prev_count, 0);
	ग_लिखोl_relaxed(0, l3pmu->regs + L3_HML3_PM_EVCNTR(idx));

	/* Set the event type */
	ग_लिखोl_relaxed(EVSEL(evsel), l3pmu->regs + L3_HML3_PM_EVTYPE(idx));

	/* Enable पूर्णांकerrupt generation by this counter */
	ग_लिखोl_relaxed(PMINTENSET(idx), l3pmu->regs + L3_M_BC_INTENSET);

	/* Finally, enable the counter */
	ग_लिखोl_relaxed(PMCNT_RESET, l3pmu->regs + L3_HML3_PM_CNTCTL(idx));
	ग_लिखोl_relaxed(PMCNTENSET(idx), l3pmu->regs + L3_M_BC_CNTENSET);
पूर्ण

अटल व्योम qcom_l3_cache__32bit_counter_stop(काष्ठा perf_event *event,
					      पूर्णांक flags)
अणु
	काष्ठा l3cache_pmu *l3pmu = to_l3cache_pmu(event->pmu);
	पूर्णांक idx = event->hw.idx;
	u32 irqctl = पढ़ोl_relaxed(l3pmu->regs + L3_M_BC_IRQCTL);

	/* Disable the counter */
	ग_लिखोl_relaxed(PMCNTENCLR(idx), l3pmu->regs + L3_M_BC_CNTENCLR);

	/* Disable पूर्णांकerrupt generation by this counter */
	ग_लिखोl_relaxed(PMINTENCLR(idx), l3pmu->regs + L3_M_BC_INTENCLR);

	/* Set the counter to not निश्चित the overflow IRQ on MSB toggling */
	ग_लिखोl_relaxed(irqctl & ~PMIRQONMSBEN(idx), l3pmu->regs + L3_M_BC_IRQCTL);
पूर्ण

अटल व्योम qcom_l3_cache__32bit_counter_update(काष्ठा perf_event *event)
अणु
	काष्ठा l3cache_pmu *l3pmu = to_l3cache_pmu(event->pmu);
	पूर्णांक idx = event->hw.idx;
	u32 prev, new;

	करो अणु
		prev = local64_पढ़ो(&event->hw.prev_count);
		new = पढ़ोl_relaxed(l3pmu->regs + L3_HML3_PM_EVCNTR(idx));
	पूर्ण जबतक (local64_cmpxchg(&event->hw.prev_count, prev, new) != prev);

	local64_add(new - prev, &event->count);
पूर्ण

अटल स्थिर काष्ठा l3cache_event_ops event_ops_std = अणु
	.start = qcom_l3_cache__32bit_counter_start,
	.stop = qcom_l3_cache__32bit_counter_stop,
	.update = qcom_l3_cache__32bit_counter_update,
पूर्ण;

/* Retrieve the appropriate operations क्रम the given event */
अटल
स्थिर काष्ठा l3cache_event_ops *l3cache_event_get_ops(काष्ठा perf_event *event)
अणु
	अगर (event_uses_दीर्घ_counter(event))
		वापस &event_ops_दीर्घ;
	अन्यथा
		वापस &event_ops_std;
पूर्ण

/*
 * Top level PMU functions.
 */

अटल अंतरभूत व्योम qcom_l3_cache__init(काष्ठा l3cache_pmu *l3pmu)
अणु
	पूर्णांक i;

	ग_लिखोl_relaxed(BC_RESET, l3pmu->regs + L3_M_BC_CR);

	/*
	 * Use ग_लिखोl क्रम the first programming command to ensure the basic
	 * counter unit is stopped beक्रमe proceeding
	 */
	ग_लिखोl(BC_SATROLL_CR_RESET, l3pmu->regs + L3_M_BC_SATROLL_CR);

	ग_लिखोl_relaxed(BC_CNTENCLR_RESET, l3pmu->regs + L3_M_BC_CNTENCLR);
	ग_लिखोl_relaxed(BC_INTENCLR_RESET, l3pmu->regs + L3_M_BC_INTENCLR);
	ग_लिखोl_relaxed(PMOVSRCLR_RESET, l3pmu->regs + L3_M_BC_OVSR);
	ग_लिखोl_relaxed(BC_GANG_RESET, l3pmu->regs + L3_M_BC_GANG);
	ग_लिखोl_relaxed(BC_IRQCTL_RESET, l3pmu->regs + L3_M_BC_IRQCTL);
	ग_लिखोl_relaxed(PM_CR_RESET, l3pmu->regs + L3_HML3_PM_CR);

	क्रम (i = 0; i < L3_NUM_COUNTERS; ++i) अणु
		ग_लिखोl_relaxed(PMCNT_RESET, l3pmu->regs + L3_HML3_PM_CNTCTL(i));
		ग_लिखोl_relaxed(EVSEL(0), l3pmu->regs + L3_HML3_PM_EVTYPE(i));
	पूर्ण

	ग_लिखोl_relaxed(PM_FLTR_RESET, l3pmu->regs + L3_HML3_PM_FILTRA);
	ग_लिखोl_relaxed(PM_FLTR_RESET, l3pmu->regs + L3_HML3_PM_FILTRAM);
	ग_लिखोl_relaxed(PM_FLTR_RESET, l3pmu->regs + L3_HML3_PM_FILTRB);
	ग_लिखोl_relaxed(PM_FLTR_RESET, l3pmu->regs + L3_HML3_PM_FILTRBM);
	ग_लिखोl_relaxed(PM_FLTR_RESET, l3pmu->regs + L3_HML3_PM_FILTRC);
	ग_लिखोl_relaxed(PM_FLTR_RESET, l3pmu->regs + L3_HML3_PM_FILTRCM);

	/*
	 * Use ग_लिखोl here to ensure all programming commands are करोne
	 *  beक्रमe proceeding
	 */
	ग_लिखोl(BC_ENABLE, l3pmu->regs + L3_M_BC_CR);
पूर्ण

अटल irqवापस_t qcom_l3_cache__handle_irq(पूर्णांक irq_num, व्योम *data)
अणु
	काष्ठा l3cache_pmu *l3pmu = data;
	/* Read the overflow status रेजिस्टर */
	दीर्घ status = पढ़ोl_relaxed(l3pmu->regs + L3_M_BC_OVSR);
	पूर्णांक idx;

	अगर (status == 0)
		वापस IRQ_NONE;

	/* Clear the bits we पढ़ो on the overflow status रेजिस्टर */
	ग_लिखोl_relaxed(status, l3pmu->regs + L3_M_BC_OVSR);

	क्रम_each_set_bit(idx, &status, L3_NUM_COUNTERS) अणु
		काष्ठा perf_event *event;
		स्थिर काष्ठा l3cache_event_ops *ops;

		event = l3pmu->events[idx];
		अगर (!event)
			जारी;

		/*
		 * Since the IRQ is not enabled क्रम events using दीर्घ counters
		 * we should never see one of those here, however, be consistent
		 * and use the ops indirections like in the other operations.
		 */

		ops = l3cache_event_get_ops(event);
		ops->update(event);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Implementation of असलtract pmu functionality required by
 * the core perf events code.
 */

अटल व्योम qcom_l3_cache__pmu_enable(काष्ठा pmu *pmu)
अणु
	काष्ठा l3cache_pmu *l3pmu = to_l3cache_pmu(pmu);

	/* Ensure the other programming commands are observed beक्रमe enabling */
	wmb();

	ग_लिखोl_relaxed(BC_ENABLE, l3pmu->regs + L3_M_BC_CR);
पूर्ण

अटल व्योम qcom_l3_cache__pmu_disable(काष्ठा pmu *pmu)
अणु
	काष्ठा l3cache_pmu *l3pmu = to_l3cache_pmu(pmu);

	ग_लिखोl_relaxed(0, l3pmu->regs + L3_M_BC_CR);

	/* Ensure the basic counter unit is stopped beक्रमe proceeding */
	wmb();
पूर्ण

/*
 * We must NOT create groups containing events from multiple hardware PMUs,
 * although mixing dअगरferent software and hardware PMUs is allowed.
 */
अटल bool qcom_l3_cache__validate_event_group(काष्ठा perf_event *event)
अणु
	काष्ठा perf_event *leader = event->group_leader;
	काष्ठा perf_event *sibling;
	पूर्णांक counters = 0;

	अगर (leader->pmu != event->pmu && !is_software_event(leader))
		वापस false;

	counters = event_num_counters(event);
	counters += event_num_counters(leader);

	क्रम_each_sibling_event(sibling, leader) अणु
		अगर (is_software_event(sibling))
			जारी;
		अगर (sibling->pmu != event->pmu)
			वापस false;
		counters += event_num_counters(sibling);
	पूर्ण

	/*
	 * If the group requires more counters than the HW has, it
	 * cannot ever be scheduled.
	 */
	वापस counters <= L3_NUM_COUNTERS;
पूर्ण

अटल पूर्णांक qcom_l3_cache__event_init(काष्ठा perf_event *event)
अणु
	काष्ठा l3cache_pmu *l3pmu = to_l3cache_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;

	/*
	 * Is the event क्रम this PMU?
	 */
	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	/*
	 * Sampling not supported since these events are not core-attributable.
	 */
	अगर (hwc->sample_period)
		वापस -EINVAL;

	/*
	 * Task mode not available, we run the counters as socket counters,
	 * not attributable to any CPU and thereक्रमe cannot attribute per-task.
	 */
	अगर (event->cpu < 0)
		वापस -EINVAL;

	/* Validate the group */
	अगर (!qcom_l3_cache__validate_event_group(event))
		वापस -EINVAL;

	hwc->idx = -1;

	/*
	 * Many perf core operations (eg. events rotation) operate on a
	 * single CPU context. This is obvious क्रम CPU PMUs, where one
	 * expects the same sets of events being observed on all CPUs,
	 * but can lead to issues क्रम off-core PMUs, like this one, where
	 * each event could be theoretically asचिन्हित to a dअगरferent CPU.
	 * To mitigate this, we enक्रमce CPU assignment to one designated
	 * processor (the one described in the "cpumask" attribute exported
	 * by the PMU device). perf user space tools honor this and aव्योम
	 * खोलोing more than one copy of the events.
	 */
	event->cpu = cpumask_first(&l3pmu->cpumask);

	वापस 0;
पूर्ण

अटल व्योम qcom_l3_cache__event_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	स्थिर काष्ठा l3cache_event_ops *ops = l3cache_event_get_ops(event);

	hwc->state = 0;
	ops->start(event);
पूर्ण

अटल व्योम qcom_l3_cache__event_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	स्थिर काष्ठा l3cache_event_ops *ops = l3cache_event_get_ops(event);

	अगर (hwc->state & PERF_HES_STOPPED)
		वापस;

	ops->stop(event, flags);
	अगर (flags & PERF_EF_UPDATE)
		ops->update(event);
	hwc->state |= PERF_HES_STOPPED | PERF_HES_UPTODATE;
पूर्ण

अटल पूर्णांक qcom_l3_cache__event_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा l3cache_pmu *l3pmu = to_l3cache_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक order = event_uses_दीर्घ_counter(event) ? 1 : 0;
	पूर्णांक idx;

	/*
	 * Try to allocate a counter.
	 */
	idx = biपंचांगap_find_मुक्त_region(l3pmu->used_mask, L3_NUM_COUNTERS, order);
	अगर (idx < 0)
		/* The counters are all in use. */
		वापस -EAGAIN;

	hwc->idx = idx;
	hwc->state = PERF_HES_STOPPED | PERF_HES_UPTODATE;
	l3pmu->events[idx] = event;

	अगर (flags & PERF_EF_START)
		qcom_l3_cache__event_start(event, 0);

	/* Propagate changes to the userspace mapping. */
	perf_event_update_userpage(event);

	वापस 0;
पूर्ण

अटल व्योम qcom_l3_cache__event_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा l3cache_pmu *l3pmu = to_l3cache_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक order = event_uses_दीर्घ_counter(event) ? 1 : 0;

	/* Stop and clean up */
	qcom_l3_cache__event_stop(event,  flags | PERF_EF_UPDATE);
	l3pmu->events[hwc->idx] = शून्य;
	biपंचांगap_release_region(l3pmu->used_mask, hwc->idx, order);

	/* Propagate changes to the userspace mapping. */
	perf_event_update_userpage(event);
पूर्ण

अटल व्योम qcom_l3_cache__event_पढ़ो(काष्ठा perf_event *event)
अणु
	स्थिर काष्ठा l3cache_event_ops *ops = l3cache_event_get_ops(event);

	ops->update(event);
पूर्ण

/*
 * Add sysfs attributes
 *
 * We export:
 * - क्रमmats, used by perf user space and other tools to configure events
 * - events, used by perf user space and other tools to create events
 *   symbolically, e.g.:
 *     perf stat -a -e l3cache_0_0/event=पढ़ो-miss/ ls
 *     perf stat -a -e l3cache_0_0/event=0x21/ ls
 * - cpumask, used by perf user space and other tools to know on which CPUs
 *   to खोलो the events
 */

/* क्रमmats */

अटल sमाप_प्रकार l3cache_pmu_क्रमmat_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा dev_ext_attribute *eattr;

	eattr = container_of(attr, काष्ठा dev_ext_attribute, attr);
	वापस sysfs_emit(buf, "%s\n", (अक्षर *) eattr->var);
पूर्ण

#घोषणा L3CACHE_PMU_FORMAT_ATTR(_name, _config)				      \
	(&((काष्ठा dev_ext_attribute[]) अणु				      \
		अणु .attr = __ATTR(_name, 0444, l3cache_pmu_क्रमmat_show, शून्य), \
		  .var = (व्योम *) _config, पूर्ण				      \
	पूर्ण)[0].attr.attr)

अटल काष्ठा attribute *qcom_l3_cache_pmu_क्रमmats[] = अणु
	L3CACHE_PMU_FORMAT_ATTR(event, "config:0-7"),
	L3CACHE_PMU_FORMAT_ATTR(lc, "config:" __stringअगरy(L3_EVENT_LC_BIT)),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group qcom_l3_cache_pmu_क्रमmat_group = अणु
	.name = "format",
	.attrs = qcom_l3_cache_pmu_क्रमmats,
पूर्ण;

/* events */

अटल sमाप_प्रकार l3cache_pmu_event_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *page)
अणु
	काष्ठा perf_pmu_events_attr *pmu_attr;

	pmu_attr = container_of(attr, काष्ठा perf_pmu_events_attr, attr);
	वापस sysfs_emit(page, "event=0x%02llx\n", pmu_attr->id);
पूर्ण

#घोषणा L3CACHE_EVENT_ATTR(_name, _id)					     \
	(&((काष्ठा perf_pmu_events_attr[]) अणु				     \
		अणु .attr = __ATTR(_name, 0444, l3cache_pmu_event_show, शून्य), \
		  .id = _id, पूर्ण						     \
	पूर्ण)[0].attr.attr)

अटल काष्ठा attribute *qcom_l3_cache_pmu_events[] = अणु
	L3CACHE_EVENT_ATTR(cycles, L3_EVENT_CYCLES),
	L3CACHE_EVENT_ATTR(पढ़ो-hit, L3_EVENT_READ_HIT),
	L3CACHE_EVENT_ATTR(पढ़ो-miss, L3_EVENT_READ_MISS),
	L3CACHE_EVENT_ATTR(पढ़ो-hit-d-side, L3_EVENT_READ_HIT_D),
	L3CACHE_EVENT_ATTR(पढ़ो-miss-d-side, L3_EVENT_READ_MISS_D),
	L3CACHE_EVENT_ATTR(ग_लिखो-hit, L3_EVENT_WRITE_HIT),
	L3CACHE_EVENT_ATTR(ग_लिखो-miss, L3_EVENT_WRITE_MISS),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group qcom_l3_cache_pmu_events_group = अणु
	.name = "events",
	.attrs = qcom_l3_cache_pmu_events,
पूर्ण;

/* cpumask */

अटल sमाप_प्रकार qcom_l3_cache_pmu_cpumask_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा l3cache_pmu *l3pmu = to_l3cache_pmu(dev_get_drvdata(dev));

	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, &l3pmu->cpumask);
पूर्ण

अटल DEVICE_ATTR(cpumask, 0444, qcom_l3_cache_pmu_cpumask_show, शून्य);

अटल काष्ठा attribute *qcom_l3_cache_pmu_cpumask_attrs[] = अणु
	&dev_attr_cpumask.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group qcom_l3_cache_pmu_cpumask_attr_group = अणु
	.attrs = qcom_l3_cache_pmu_cpumask_attrs,
पूर्ण;

/*
 * Per PMU device attribute groups
 */
अटल स्थिर काष्ठा attribute_group *qcom_l3_cache_pmu_attr_grps[] = अणु
	&qcom_l3_cache_pmu_क्रमmat_group,
	&qcom_l3_cache_pmu_events_group,
	&qcom_l3_cache_pmu_cpumask_attr_group,
	शून्य,
पूर्ण;

/*
 * Probing functions and data.
 */

अटल पूर्णांक qcom_l3_cache_pmu_online_cpu(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा l3cache_pmu *l3pmu = hlist_entry_safe(node, काष्ठा l3cache_pmu, node);

	/* If there is not a CPU/PMU association pick this CPU */
	अगर (cpumask_empty(&l3pmu->cpumask))
		cpumask_set_cpu(cpu, &l3pmu->cpumask);

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_l3_cache_pmu_offline_cpu(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा l3cache_pmu *l3pmu = hlist_entry_safe(node, काष्ठा l3cache_pmu, node);
	अचिन्हित पूर्णांक target;

	अगर (!cpumask_test_and_clear_cpu(cpu, &l3pmu->cpumask))
		वापस 0;
	target = cpumask_any_but(cpu_online_mask, cpu);
	अगर (target >= nr_cpu_ids)
		वापस 0;
	perf_pmu_migrate_context(&l3pmu->pmu, cpu, target);
	cpumask_set_cpu(target, &l3pmu->cpumask);
	वापस 0;
पूर्ण

अटल पूर्णांक qcom_l3_cache_pmu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा l3cache_pmu *l3pmu;
	काष्ठा acpi_device *acpi_dev;
	काष्ठा resource *memrc;
	पूर्णांक ret;
	अक्षर *name;

	/* Initialize the PMU data काष्ठाures */

	acpi_dev = ACPI_COMPANION(&pdev->dev);
	अगर (!acpi_dev)
		वापस -ENODEV;

	l3pmu = devm_kzalloc(&pdev->dev, माप(*l3pmu), GFP_KERNEL);
	name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL, "l3cache_%s_%s",
		      acpi_dev->parent->pnp.unique_id, acpi_dev->pnp.unique_id);
	अगर (!l3pmu || !name)
		वापस -ENOMEM;

	l3pmu->pmu = (काष्ठा pmu) अणु
		.task_ctx_nr	= perf_invalid_context,

		.pmu_enable	= qcom_l3_cache__pmu_enable,
		.pmu_disable	= qcom_l3_cache__pmu_disable,
		.event_init	= qcom_l3_cache__event_init,
		.add		= qcom_l3_cache__event_add,
		.del		= qcom_l3_cache__event_del,
		.start		= qcom_l3_cache__event_start,
		.stop		= qcom_l3_cache__event_stop,
		.पढ़ो		= qcom_l3_cache__event_पढ़ो,

		.attr_groups	= qcom_l3_cache_pmu_attr_grps,
		.capabilities	= PERF_PMU_CAP_NO_EXCLUDE,
	पूर्ण;

	memrc = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	l3pmu->regs = devm_ioremap_resource(&pdev->dev, memrc);
	अगर (IS_ERR(l3pmu->regs)) अणु
		dev_err(&pdev->dev, "Can't map PMU @%pa\n", &memrc->start);
		वापस PTR_ERR(l3pmu->regs);
	पूर्ण

	qcom_l3_cache__init(l3pmu);

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret <= 0)
		वापस ret;

	ret = devm_request_irq(&pdev->dev, ret, qcom_l3_cache__handle_irq, 0,
			       name, l3pmu);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Request for IRQ failed for slice @%pa\n",
			&memrc->start);
		वापस ret;
	पूर्ण

	/* Add this instance to the list used by the offline callback */
	ret = cpuhp_state_add_instance(CPUHP_AP_PERF_ARM_QCOM_L3_ONLINE, &l3pmu->node);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Error %d registering hotplug", ret);
		वापस ret;
	पूर्ण

	ret = perf_pmu_रेजिस्टर(&l3pmu->pmu, name, -1);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to register L3 cache PMU (%d)\n", ret);
		वापस ret;
	पूर्ण

	dev_info(&pdev->dev, "Registered %s, type: %d\n", name, l3pmu->pmu.type);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id qcom_l3_cache_pmu_acpi_match[] = अणु
	अणु "QCOM8081", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, qcom_l3_cache_pmu_acpi_match);

अटल काष्ठा platक्रमm_driver qcom_l3_cache_pmu_driver = अणु
	.driver = अणु
		.name = "qcom-l3cache-pmu",
		.acpi_match_table = ACPI_PTR(qcom_l3_cache_pmu_acpi_match),
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = qcom_l3_cache_pmu_probe,
पूर्ण;

अटल पूर्णांक __init रेजिस्टर_qcom_l3_cache_pmu_driver(व्योम)
अणु
	पूर्णांक ret;

	/* Install a hook to update the पढ़ोer CPU in हाल it goes offline */
	ret = cpuhp_setup_state_multi(CPUHP_AP_PERF_ARM_QCOM_L3_ONLINE,
				      "perf/qcom/l3cache:online",
				      qcom_l3_cache_pmu_online_cpu,
				      qcom_l3_cache_pmu_offline_cpu);
	अगर (ret)
		वापस ret;

	वापस platक्रमm_driver_रेजिस्टर(&qcom_l3_cache_pmu_driver);
पूर्ण
device_initcall(रेजिस्टर_qcom_l3_cache_pmu_driver);
