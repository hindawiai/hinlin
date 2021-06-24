<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * This driver adds support क्रम perf events to use the Perक्रमmance
 * Monitor Counter Groups (PMCG) associated with an SMMUv3 node
 * to monitor that node.
 *
 * SMMUv3 PMCG devices are named as smmuv3_pmcg_<phys_addr_page> where
 * <phys_addr_page> is the physical page address of the SMMU PMCG wrapped
 * to 4K boundary. For example, the PMCG at 0xff88840000 is named
 * smmuv3_pmcg_ff88840
 *
 * Filtering by stream id is करोne by specअगरying filtering parameters
 * with the event. options are:
 *   filter_enable    - 0 = no filtering, 1 = filtering enabled
 *   filter_span      - 0 = exact match, 1 = pattern match
 *   filter_stream_id - pattern to filter against
 *
 * To match a partial StreamID where the X most-signअगरicant bits must match
 * but the Y least-signअगरicant bits might dअगरfer, STREAMID is programmed
 * with a value that contains:
 *  STREAMID[Y - 1] == 0.
 *  STREAMID[Y - 2:0] == 1 (where Y > 1).
 * The reमुख्यder of implemented bits of STREAMID (X bits, from bit Y upwards)
 * contain a value to match from the corresponding bits of event StreamID.
 *
 * Example: perf stat -e smmuv3_pmcg_ff88840/transaction,filter_enable=1,
 *                    filter_span=1,filter_stream_id=0x42/ -a netperf
 * Applies filter pattern 0x42 to transaction events, which means events
 * matching stream ids 0x42 and 0x43 are counted. Further filtering
 * inक्रमmation is available in the SMMU करोcumentation.
 *
 * SMMU events are not attributable to a CPU, so task mode and sampling
 * are not supported.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/acpi_iort.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/msi.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/smp.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>

#घोषणा SMMU_PMCG_EVCNTR0               0x0
#घोषणा SMMU_PMCG_EVCNTR(n, stride)     (SMMU_PMCG_EVCNTR0 + (n) * (stride))
#घोषणा SMMU_PMCG_EVTYPER0              0x400
#घोषणा SMMU_PMCG_EVTYPER(n)            (SMMU_PMCG_EVTYPER0 + (n) * 4)
#घोषणा SMMU_PMCG_SID_SPAN_SHIFT        29
#घोषणा SMMU_PMCG_SMR0                  0xA00
#घोषणा SMMU_PMCG_SMR(n)                (SMMU_PMCG_SMR0 + (n) * 4)
#घोषणा SMMU_PMCG_CNTENSET0             0xC00
#घोषणा SMMU_PMCG_CNTENCLR0             0xC20
#घोषणा SMMU_PMCG_INTENSET0             0xC40
#घोषणा SMMU_PMCG_INTENCLR0             0xC60
#घोषणा SMMU_PMCG_OVSCLR0               0xC80
#घोषणा SMMU_PMCG_OVSSET0               0xCC0
#घोषणा SMMU_PMCG_CFGR                  0xE00
#घोषणा SMMU_PMCG_CFGR_SID_FILTER_TYPE  BIT(23)
#घोषणा SMMU_PMCG_CFGR_MSI              BIT(21)
#घोषणा SMMU_PMCG_CFGR_RELOC_CTRS       BIT(20)
#घोषणा SMMU_PMCG_CFGR_SIZE             GENMASK(13, 8)
#घोषणा SMMU_PMCG_CFGR_NCTR             GENMASK(5, 0)
#घोषणा SMMU_PMCG_CR                    0xE04
#घोषणा SMMU_PMCG_CR_ENABLE             BIT(0)
#घोषणा SMMU_PMCG_IIDR                  0xE08
#घोषणा SMMU_PMCG_CEID0                 0xE20
#घोषणा SMMU_PMCG_CEID1                 0xE28
#घोषणा SMMU_PMCG_IRQ_CTRL              0xE50
#घोषणा SMMU_PMCG_IRQ_CTRL_IRQEN        BIT(0)
#घोषणा SMMU_PMCG_IRQ_CFG0              0xE58
#घोषणा SMMU_PMCG_IRQ_CFG1              0xE60
#घोषणा SMMU_PMCG_IRQ_CFG2              0xE64

/* MSI config fields */
#घोषणा MSI_CFG0_ADDR_MASK              GENMASK_ULL(51, 2)
#घोषणा MSI_CFG2_MEMATTR_DEVICE_nGnRE   0x1

#घोषणा SMMU_PMCG_DEFAULT_FILTER_SPAN   1
#घोषणा SMMU_PMCG_DEFAULT_FILTER_SID    GENMASK(31, 0)

#घोषणा SMMU_PMCG_MAX_COUNTERS          64
#घोषणा SMMU_PMCG_ARCH_MAX_EVENTS       128

#घोषणा SMMU_PMCG_PA_SHIFT              12

#घोषणा SMMU_PMCG_EVCNTR_RDONLY         BIT(0)

अटल पूर्णांक cpuhp_state_num;

काष्ठा smmu_pmu अणु
	काष्ठा hlist_node node;
	काष्ठा perf_event *events[SMMU_PMCG_MAX_COUNTERS];
	DECLARE_BITMAP(used_counters, SMMU_PMCG_MAX_COUNTERS);
	DECLARE_BITMAP(supported_events, SMMU_PMCG_ARCH_MAX_EVENTS);
	अचिन्हित पूर्णांक irq;
	अचिन्हित पूर्णांक on_cpu;
	काष्ठा pmu pmu;
	अचिन्हित पूर्णांक num_counters;
	काष्ठा device *dev;
	व्योम __iomem *reg_base;
	व्योम __iomem *reloc_base;
	u64 counter_mask;
	u32 options;
	u32 iidr;
	bool global_filter;
पूर्ण;

#घोषणा to_smmu_pmu(p) (container_of(p, काष्ठा smmu_pmu, pmu))

#घोषणा SMMU_PMU_EVENT_ATTR_EXTRACTOR(_name, _config, _start, _end)        \
	अटल अंतरभूत u32 get_##_name(काष्ठा perf_event *event)            \
	अणु                                                                  \
		वापस FIELD_GET(GENMASK_ULL(_end, _start),                \
				 event->attr._config);                     \
	पूर्ण                                                                  \

SMMU_PMU_EVENT_ATTR_EXTRACTOR(event, config, 0, 15);
SMMU_PMU_EVENT_ATTR_EXTRACTOR(filter_stream_id, config1, 0, 31);
SMMU_PMU_EVENT_ATTR_EXTRACTOR(filter_span, config1, 32, 32);
SMMU_PMU_EVENT_ATTR_EXTRACTOR(filter_enable, config1, 33, 33);

अटल अंतरभूत व्योम smmu_pmu_enable(काष्ठा pmu *pmu)
अणु
	काष्ठा smmu_pmu *smmu_pmu = to_smmu_pmu(pmu);

	ग_लिखोl(SMMU_PMCG_IRQ_CTRL_IRQEN,
	       smmu_pmu->reg_base + SMMU_PMCG_IRQ_CTRL);
	ग_लिखोl(SMMU_PMCG_CR_ENABLE, smmu_pmu->reg_base + SMMU_PMCG_CR);
पूर्ण

अटल अंतरभूत व्योम smmu_pmu_disable(काष्ठा pmu *pmu)
अणु
	काष्ठा smmu_pmu *smmu_pmu = to_smmu_pmu(pmu);

	ग_लिखोl(0, smmu_pmu->reg_base + SMMU_PMCG_CR);
	ग_लिखोl(0, smmu_pmu->reg_base + SMMU_PMCG_IRQ_CTRL);
पूर्ण

अटल अंतरभूत व्योम smmu_pmu_counter_set_value(काष्ठा smmu_pmu *smmu_pmu,
					      u32 idx, u64 value)
अणु
	अगर (smmu_pmu->counter_mask & BIT(32))
		ग_लिखोq(value, smmu_pmu->reloc_base + SMMU_PMCG_EVCNTR(idx, 8));
	अन्यथा
		ग_लिखोl(value, smmu_pmu->reloc_base + SMMU_PMCG_EVCNTR(idx, 4));
पूर्ण

अटल अंतरभूत u64 smmu_pmu_counter_get_value(काष्ठा smmu_pmu *smmu_pmu, u32 idx)
अणु
	u64 value;

	अगर (smmu_pmu->counter_mask & BIT(32))
		value = पढ़ोq(smmu_pmu->reloc_base + SMMU_PMCG_EVCNTR(idx, 8));
	अन्यथा
		value = पढ़ोl(smmu_pmu->reloc_base + SMMU_PMCG_EVCNTR(idx, 4));

	वापस value;
पूर्ण

अटल अंतरभूत व्योम smmu_pmu_counter_enable(काष्ठा smmu_pmu *smmu_pmu, u32 idx)
अणु
	ग_लिखोq(BIT(idx), smmu_pmu->reg_base + SMMU_PMCG_CNTENSET0);
पूर्ण

अटल अंतरभूत व्योम smmu_pmu_counter_disable(काष्ठा smmu_pmu *smmu_pmu, u32 idx)
अणु
	ग_लिखोq(BIT(idx), smmu_pmu->reg_base + SMMU_PMCG_CNTENCLR0);
पूर्ण

अटल अंतरभूत व्योम smmu_pmu_पूर्णांकerrupt_enable(काष्ठा smmu_pmu *smmu_pmu, u32 idx)
अणु
	ग_लिखोq(BIT(idx), smmu_pmu->reg_base + SMMU_PMCG_INTENSET0);
पूर्ण

अटल अंतरभूत व्योम smmu_pmu_पूर्णांकerrupt_disable(काष्ठा smmu_pmu *smmu_pmu,
					      u32 idx)
अणु
	ग_लिखोq(BIT(idx), smmu_pmu->reg_base + SMMU_PMCG_INTENCLR0);
पूर्ण

अटल अंतरभूत व्योम smmu_pmu_set_evtyper(काष्ठा smmu_pmu *smmu_pmu, u32 idx,
					u32 val)
अणु
	ग_लिखोl(val, smmu_pmu->reg_base + SMMU_PMCG_EVTYPER(idx));
पूर्ण

अटल अंतरभूत व्योम smmu_pmu_set_smr(काष्ठा smmu_pmu *smmu_pmu, u32 idx, u32 val)
अणु
	ग_लिखोl(val, smmu_pmu->reg_base + SMMU_PMCG_SMR(idx));
पूर्ण

अटल व्योम smmu_pmu_event_update(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा smmu_pmu *smmu_pmu = to_smmu_pmu(event->pmu);
	u64 delta, prev, now;
	u32 idx = hwc->idx;

	करो अणु
		prev = local64_पढ़ो(&hwc->prev_count);
		now = smmu_pmu_counter_get_value(smmu_pmu, idx);
	पूर्ण जबतक (local64_cmpxchg(&hwc->prev_count, prev, now) != prev);

	/* handle overflow. */
	delta = now - prev;
	delta &= smmu_pmu->counter_mask;

	local64_add(delta, &event->count);
पूर्ण

अटल व्योम smmu_pmu_set_period(काष्ठा smmu_pmu *smmu_pmu,
				काष्ठा hw_perf_event *hwc)
अणु
	u32 idx = hwc->idx;
	u64 new;

	अगर (smmu_pmu->options & SMMU_PMCG_EVCNTR_RDONLY) अणु
		/*
		 * On platक्रमms that require this quirk, अगर the counter starts
		 * at < half_counter value and wraps, the current logic of
		 * handling the overflow may not work. It is expected that,
		 * those platक्रमms will have full 64 counter bits implemented
		 * so that such a possibility is remote(eg: HiSilicon HIP08).
		 */
		new = smmu_pmu_counter_get_value(smmu_pmu, idx);
	पूर्ण अन्यथा अणु
		/*
		 * We limit the max period to half the max counter value
		 * of the counter size, so that even in the हाल of extreme
		 * पूर्णांकerrupt latency the counter will (hopefully) not wrap
		 * past its initial value.
		 */
		new = smmu_pmu->counter_mask >> 1;
		smmu_pmu_counter_set_value(smmu_pmu, idx, new);
	पूर्ण

	local64_set(&hwc->prev_count, new);
पूर्ण

अटल व्योम smmu_pmu_set_event_filter(काष्ठा perf_event *event,
				      पूर्णांक idx, u32 span, u32 sid)
अणु
	काष्ठा smmu_pmu *smmu_pmu = to_smmu_pmu(event->pmu);
	u32 evtyper;

	evtyper = get_event(event) | span << SMMU_PMCG_SID_SPAN_SHIFT;
	smmu_pmu_set_evtyper(smmu_pmu, idx, evtyper);
	smmu_pmu_set_smr(smmu_pmu, idx, sid);
पूर्ण

अटल bool smmu_pmu_check_global_filter(काष्ठा perf_event *curr,
					 काष्ठा perf_event *new)
अणु
	अगर (get_filter_enable(new) != get_filter_enable(curr))
		वापस false;

	अगर (!get_filter_enable(new))
		वापस true;

	वापस get_filter_span(new) == get_filter_span(curr) &&
	       get_filter_stream_id(new) == get_filter_stream_id(curr);
पूर्ण

अटल पूर्णांक smmu_pmu_apply_event_filter(काष्ठा smmu_pmu *smmu_pmu,
				       काष्ठा perf_event *event, पूर्णांक idx)
अणु
	u32 span, sid;
	अचिन्हित पूर्णांक num_ctrs = smmu_pmu->num_counters;
	bool filter_en = !!get_filter_enable(event);

	span = filter_en ? get_filter_span(event) :
			   SMMU_PMCG_DEFAULT_FILTER_SPAN;
	sid = filter_en ? get_filter_stream_id(event) :
			   SMMU_PMCG_DEFAULT_FILTER_SID;

	/* Support inभागidual filter settings */
	अगर (!smmu_pmu->global_filter) अणु
		smmu_pmu_set_event_filter(event, idx, span, sid);
		वापस 0;
	पूर्ण

	/* Requested settings same as current global settings*/
	idx = find_first_bit(smmu_pmu->used_counters, num_ctrs);
	अगर (idx == num_ctrs ||
	    smmu_pmu_check_global_filter(smmu_pmu->events[idx], event)) अणु
		smmu_pmu_set_event_filter(event, 0, span, sid);
		वापस 0;
	पूर्ण

	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक smmu_pmu_get_event_idx(काष्ठा smmu_pmu *smmu_pmu,
				  काष्ठा perf_event *event)
अणु
	पूर्णांक idx, err;
	अचिन्हित पूर्णांक num_ctrs = smmu_pmu->num_counters;

	idx = find_first_zero_bit(smmu_pmu->used_counters, num_ctrs);
	अगर (idx == num_ctrs)
		/* The counters are all in use. */
		वापस -EAGAIN;

	err = smmu_pmu_apply_event_filter(smmu_pmu, event, idx);
	अगर (err)
		वापस err;

	set_bit(idx, smmu_pmu->used_counters);

	वापस idx;
पूर्ण

अटल bool smmu_pmu_events_compatible(काष्ठा perf_event *curr,
				       काष्ठा perf_event *new)
अणु
	अगर (new->pmu != curr->pmu)
		वापस false;

	अगर (to_smmu_pmu(new->pmu)->global_filter &&
	    !smmu_pmu_check_global_filter(curr, new))
		वापस false;

	वापस true;
पूर्ण

/*
 * Implementation of असलtract pmu functionality required by
 * the core perf events code.
 */

अटल पूर्णांक smmu_pmu_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा smmu_pmu *smmu_pmu = to_smmu_pmu(event->pmu);
	काष्ठा device *dev = smmu_pmu->dev;
	काष्ठा perf_event *sibling;
	पूर्णांक group_num_events = 1;
	u16 event_id;

	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	अगर (hwc->sample_period) अणु
		dev_dbg(dev, "Sampling not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (event->cpu < 0) अणु
		dev_dbg(dev, "Per-task mode not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Verअगरy specअगरied event is supported on this PMU */
	event_id = get_event(event);
	अगर (event_id < SMMU_PMCG_ARCH_MAX_EVENTS &&
	    (!test_bit(event_id, smmu_pmu->supported_events))) अणु
		dev_dbg(dev, "Invalid event %d for this PMU\n", event_id);
		वापस -EINVAL;
	पूर्ण

	/* Don't allow groups with mixed PMUs, except क्रम s/w events */
	अगर (!is_software_event(event->group_leader)) अणु
		अगर (!smmu_pmu_events_compatible(event->group_leader, event))
			वापस -EINVAL;

		अगर (++group_num_events > smmu_pmu->num_counters)
			वापस -EINVAL;
	पूर्ण

	क्रम_each_sibling_event(sibling, event->group_leader) अणु
		अगर (is_software_event(sibling))
			जारी;

		अगर (!smmu_pmu_events_compatible(sibling, event))
			वापस -EINVAL;

		अगर (++group_num_events > smmu_pmu->num_counters)
			वापस -EINVAL;
	पूर्ण

	hwc->idx = -1;

	/*
	 * Ensure all events are on the same cpu so all events are in the
	 * same cpu context, to aव्योम races on pmu_enable etc.
	 */
	event->cpu = smmu_pmu->on_cpu;

	वापस 0;
पूर्ण

अटल व्योम smmu_pmu_event_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा smmu_pmu *smmu_pmu = to_smmu_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	hwc->state = 0;

	smmu_pmu_set_period(smmu_pmu, hwc);

	smmu_pmu_counter_enable(smmu_pmu, idx);
पूर्ण

अटल व्योम smmu_pmu_event_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा smmu_pmu *smmu_pmu = to_smmu_pmu(event->pmu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	अगर (hwc->state & PERF_HES_STOPPED)
		वापस;

	smmu_pmu_counter_disable(smmu_pmu, idx);
	/* As the counter माला_लो updated on _start, ignore PERF_EF_UPDATE */
	smmu_pmu_event_update(event);
	hwc->state |= PERF_HES_STOPPED | PERF_HES_UPTODATE;
पूर्ण

अटल पूर्णांक smmu_pmu_event_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx;
	काष्ठा smmu_pmu *smmu_pmu = to_smmu_pmu(event->pmu);

	idx = smmu_pmu_get_event_idx(smmu_pmu, event);
	अगर (idx < 0)
		वापस idx;

	hwc->idx = idx;
	hwc->state = PERF_HES_STOPPED | PERF_HES_UPTODATE;
	smmu_pmu->events[idx] = event;
	local64_set(&hwc->prev_count, 0);

	smmu_pmu_पूर्णांकerrupt_enable(smmu_pmu, idx);

	अगर (flags & PERF_EF_START)
		smmu_pmu_event_start(event, flags);

	/* Propagate changes to the userspace mapping. */
	perf_event_update_userpage(event);

	वापस 0;
पूर्ण

अटल व्योम smmu_pmu_event_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा smmu_pmu *smmu_pmu = to_smmu_pmu(event->pmu);
	पूर्णांक idx = hwc->idx;

	smmu_pmu_event_stop(event, flags | PERF_EF_UPDATE);
	smmu_pmu_पूर्णांकerrupt_disable(smmu_pmu, idx);
	smmu_pmu->events[idx] = शून्य;
	clear_bit(idx, smmu_pmu->used_counters);

	perf_event_update_userpage(event);
पूर्ण

अटल व्योम smmu_pmu_event_पढ़ो(काष्ठा perf_event *event)
अणु
	smmu_pmu_event_update(event);
पूर्ण

/* cpumask */

अटल sमाप_प्रकार smmu_pmu_cpumask_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा smmu_pmu *smmu_pmu = to_smmu_pmu(dev_get_drvdata(dev));

	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, cpumask_of(smmu_pmu->on_cpu));
पूर्ण

अटल काष्ठा device_attribute smmu_pmu_cpumask_attr =
		__ATTR(cpumask, 0444, smmu_pmu_cpumask_show, शून्य);

अटल काष्ठा attribute *smmu_pmu_cpumask_attrs[] = अणु
	&smmu_pmu_cpumask_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group smmu_pmu_cpumask_group = अणु
	.attrs = smmu_pmu_cpumask_attrs,
पूर्ण;

/* Events */

अटल sमाप_प्रकार smmu_pmu_event_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *page)
अणु
	काष्ठा perf_pmu_events_attr *pmu_attr;

	pmu_attr = container_of(attr, काष्ठा perf_pmu_events_attr, attr);

	वापस sysfs_emit(page, "event=0x%02llx\n", pmu_attr->id);
पूर्ण

#घोषणा SMMU_EVENT_ATTR(name, config)					\
	(&((काष्ठा perf_pmu_events_attr) अणु				\
		.attr = __ATTR(name, 0444, smmu_pmu_event_show, शून्य),	\
		.id = config,						\
	पूर्ण).attr.attr)

अटल काष्ठा attribute *smmu_pmu_events[] = अणु
	SMMU_EVENT_ATTR(cycles, 0),
	SMMU_EVENT_ATTR(transaction, 1),
	SMMU_EVENT_ATTR(tlb_miss, 2),
	SMMU_EVENT_ATTR(config_cache_miss, 3),
	SMMU_EVENT_ATTR(trans_table_walk_access, 4),
	SMMU_EVENT_ATTR(config_काष्ठा_access, 5),
	SMMU_EVENT_ATTR(pcie_ats_trans_rq, 6),
	SMMU_EVENT_ATTR(pcie_ats_trans_passed, 7),
	शून्य
पूर्ण;

अटल umode_t smmu_pmu_event_is_visible(काष्ठा kobject *kobj,
					 काष्ठा attribute *attr, पूर्णांक unused)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा smmu_pmu *smmu_pmu = to_smmu_pmu(dev_get_drvdata(dev));
	काष्ठा perf_pmu_events_attr *pmu_attr;

	pmu_attr = container_of(attr, काष्ठा perf_pmu_events_attr, attr.attr);

	अगर (test_bit(pmu_attr->id, smmu_pmu->supported_events))
		वापस attr->mode;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा attribute_group smmu_pmu_events_group = अणु
	.name = "events",
	.attrs = smmu_pmu_events,
	.is_visible = smmu_pmu_event_is_visible,
पूर्ण;

अटल sमाप_प्रकार smmu_pmu_identअगरier_attr_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *page)
अणु
	काष्ठा smmu_pmu *smmu_pmu = to_smmu_pmu(dev_get_drvdata(dev));

	वापस sysfs_emit(page, "0x%08x\n", smmu_pmu->iidr);
पूर्ण

अटल umode_t smmu_pmu_identअगरier_attr_visible(काष्ठा kobject *kobj,
						काष्ठा attribute *attr,
						पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा smmu_pmu *smmu_pmu = to_smmu_pmu(dev_get_drvdata(dev));

	अगर (!smmu_pmu->iidr)
		वापस 0;
	वापस attr->mode;
पूर्ण

अटल काष्ठा device_attribute smmu_pmu_identअगरier_attr =
	__ATTR(identअगरier, 0444, smmu_pmu_identअगरier_attr_show, शून्य);

अटल काष्ठा attribute *smmu_pmu_identअगरier_attrs[] = अणु
	&smmu_pmu_identअगरier_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group smmu_pmu_identअगरier_group = अणु
	.attrs = smmu_pmu_identअगरier_attrs,
	.is_visible = smmu_pmu_identअगरier_attr_visible,
पूर्ण;

/* Formats */
PMU_FORMAT_ATTR(event,		   "config:0-15");
PMU_FORMAT_ATTR(filter_stream_id,  "config1:0-31");
PMU_FORMAT_ATTR(filter_span,	   "config1:32");
PMU_FORMAT_ATTR(filter_enable,	   "config1:33");

अटल काष्ठा attribute *smmu_pmu_क्रमmats[] = अणु
	&क्रमmat_attr_event.attr,
	&क्रमmat_attr_filter_stream_id.attr,
	&क्रमmat_attr_filter_span.attr,
	&क्रमmat_attr_filter_enable.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group smmu_pmu_क्रमmat_group = अणु
	.name = "format",
	.attrs = smmu_pmu_क्रमmats,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *smmu_pmu_attr_grps[] = अणु
	&smmu_pmu_cpumask_group,
	&smmu_pmu_events_group,
	&smmu_pmu_क्रमmat_group,
	&smmu_pmu_identअगरier_group,
	शून्य
पूर्ण;

/*
 * Generic device handlers
 */

अटल पूर्णांक smmu_pmu_offline_cpu(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा smmu_pmu *smmu_pmu;
	अचिन्हित पूर्णांक target;

	smmu_pmu = hlist_entry_safe(node, काष्ठा smmu_pmu, node);
	अगर (cpu != smmu_pmu->on_cpu)
		वापस 0;

	target = cpumask_any_but(cpu_online_mask, cpu);
	अगर (target >= nr_cpu_ids)
		वापस 0;

	perf_pmu_migrate_context(&smmu_pmu->pmu, cpu, target);
	smmu_pmu->on_cpu = target;
	WARN_ON(irq_set_affinity_hपूर्णांक(smmu_pmu->irq, cpumask_of(target)));

	वापस 0;
पूर्ण

अटल irqवापस_t smmu_pmu_handle_irq(पूर्णांक irq_num, व्योम *data)
अणु
	काष्ठा smmu_pmu *smmu_pmu = data;
	u64 ovsr;
	अचिन्हित पूर्णांक idx;

	ovsr = पढ़ोq(smmu_pmu->reloc_base + SMMU_PMCG_OVSSET0);
	अगर (!ovsr)
		वापस IRQ_NONE;

	ग_लिखोq(ovsr, smmu_pmu->reloc_base + SMMU_PMCG_OVSCLR0);

	क्रम_each_set_bit(idx, (अचिन्हित दीर्घ *)&ovsr, smmu_pmu->num_counters) अणु
		काष्ठा perf_event *event = smmu_pmu->events[idx];
		काष्ठा hw_perf_event *hwc;

		अगर (WARN_ON_ONCE(!event))
			जारी;

		smmu_pmu_event_update(event);
		hwc = &event->hw;

		smmu_pmu_set_period(smmu_pmu, hwc);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम smmu_pmu_मुक्त_msis(व्योम *data)
अणु
	काष्ठा device *dev = data;

	platक्रमm_msi_करोमुख्य_मुक्त_irqs(dev);
पूर्ण

अटल व्योम smmu_pmu_ग_लिखो_msi_msg(काष्ठा msi_desc *desc, काष्ठा msi_msg *msg)
अणु
	phys_addr_t करोorbell;
	काष्ठा device *dev = msi_desc_to_dev(desc);
	काष्ठा smmu_pmu *pmu = dev_get_drvdata(dev);

	करोorbell = (((u64)msg->address_hi) << 32) | msg->address_lo;
	करोorbell &= MSI_CFG0_ADDR_MASK;

	ग_लिखोq_relaxed(करोorbell, pmu->reg_base + SMMU_PMCG_IRQ_CFG0);
	ग_लिखोl_relaxed(msg->data, pmu->reg_base + SMMU_PMCG_IRQ_CFG1);
	ग_लिखोl_relaxed(MSI_CFG2_MEMATTR_DEVICE_nGnRE,
		       pmu->reg_base + SMMU_PMCG_IRQ_CFG2);
पूर्ण

अटल व्योम smmu_pmu_setup_msi(काष्ठा smmu_pmu *pmu)
अणु
	काष्ठा msi_desc *desc;
	काष्ठा device *dev = pmu->dev;
	पूर्णांक ret;

	/* Clear MSI address reg */
	ग_लिखोq_relaxed(0, pmu->reg_base + SMMU_PMCG_IRQ_CFG0);

	/* MSI supported or not */
	अगर (!(पढ़ोl(pmu->reg_base + SMMU_PMCG_CFGR) & SMMU_PMCG_CFGR_MSI))
		वापस;

	ret = platक्रमm_msi_करोमुख्य_alloc_irqs(dev, 1, smmu_pmu_ग_लिखो_msi_msg);
	अगर (ret) अणु
		dev_warn(dev, "failed to allocate MSIs\n");
		वापस;
	पूर्ण

	desc = first_msi_entry(dev);
	अगर (desc)
		pmu->irq = desc->irq;

	/* Add callback to मुक्त MSIs on tearकरोwn */
	devm_add_action(dev, smmu_pmu_मुक्त_msis, dev);
पूर्ण

अटल पूर्णांक smmu_pmu_setup_irq(काष्ठा smmu_pmu *pmu)
अणु
	अचिन्हित दीर्घ flags = IRQF_NOBALANCING | IRQF_SHARED | IRQF_NO_THREAD;
	पूर्णांक irq, ret = -ENXIO;

	smmu_pmu_setup_msi(pmu);

	irq = pmu->irq;
	अगर (irq)
		ret = devm_request_irq(pmu->dev, irq, smmu_pmu_handle_irq,
				       flags, "smmuv3-pmu", pmu);
	वापस ret;
पूर्ण

अटल व्योम smmu_pmu_reset(काष्ठा smmu_pmu *smmu_pmu)
अणु
	u64 counter_present_mask = GENMASK_ULL(smmu_pmu->num_counters - 1, 0);

	smmu_pmu_disable(&smmu_pmu->pmu);

	/* Disable counter and पूर्णांकerrupt */
	ग_लिखोq_relaxed(counter_present_mask,
		       smmu_pmu->reg_base + SMMU_PMCG_CNTENCLR0);
	ग_लिखोq_relaxed(counter_present_mask,
		       smmu_pmu->reg_base + SMMU_PMCG_INTENCLR0);
	ग_लिखोq_relaxed(counter_present_mask,
		       smmu_pmu->reloc_base + SMMU_PMCG_OVSCLR0);
पूर्ण

अटल व्योम smmu_pmu_get_acpi_options(काष्ठा smmu_pmu *smmu_pmu)
अणु
	u32 model;

	model = *(u32 *)dev_get_platdata(smmu_pmu->dev);

	चयन (model) अणु
	हाल IORT_SMMU_V3_PMCG_HISI_HIP08:
		/* HiSilicon Erratum 162001800 */
		smmu_pmu->options |= SMMU_PMCG_EVCNTR_RDONLY;
		अवरोध;
	पूर्ण

	dev_notice(smmu_pmu->dev, "option mask 0x%x\n", smmu_pmu->options);
पूर्ण

अटल पूर्णांक smmu_pmu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा smmu_pmu *smmu_pmu;
	काष्ठा resource *res_0;
	u32 cfgr, reg_size;
	u64 ceid_64[2];
	पूर्णांक irq, err;
	अक्षर *name;
	काष्ठा device *dev = &pdev->dev;

	smmu_pmu = devm_kzalloc(dev, माप(*smmu_pmu), GFP_KERNEL);
	अगर (!smmu_pmu)
		वापस -ENOMEM;

	smmu_pmu->dev = dev;
	platक्रमm_set_drvdata(pdev, smmu_pmu);

	smmu_pmu->pmu = (काष्ठा pmu) अणु
		.module		= THIS_MODULE,
		.task_ctx_nr    = perf_invalid_context,
		.pmu_enable	= smmu_pmu_enable,
		.pmu_disable	= smmu_pmu_disable,
		.event_init	= smmu_pmu_event_init,
		.add		= smmu_pmu_event_add,
		.del		= smmu_pmu_event_del,
		.start		= smmu_pmu_event_start,
		.stop		= smmu_pmu_event_stop,
		.पढ़ो		= smmu_pmu_event_पढ़ो,
		.attr_groups	= smmu_pmu_attr_grps,
		.capabilities	= PERF_PMU_CAP_NO_EXCLUDE,
	पूर्ण;

	smmu_pmu->reg_base = devm_platक्रमm_get_and_ioremap_resource(pdev, 0, &res_0);
	अगर (IS_ERR(smmu_pmu->reg_base))
		वापस PTR_ERR(smmu_pmu->reg_base);

	cfgr = पढ़ोl_relaxed(smmu_pmu->reg_base + SMMU_PMCG_CFGR);

	/* Determine अगर page 1 is present */
	अगर (cfgr & SMMU_PMCG_CFGR_RELOC_CTRS) अणु
		smmu_pmu->reloc_base = devm_platक्रमm_ioremap_resource(pdev, 1);
		अगर (IS_ERR(smmu_pmu->reloc_base))
			वापस PTR_ERR(smmu_pmu->reloc_base);
	पूर्ण अन्यथा अणु
		smmu_pmu->reloc_base = smmu_pmu->reg_base;
	पूर्ण

	irq = platक्रमm_get_irq_optional(pdev, 0);
	अगर (irq > 0)
		smmu_pmu->irq = irq;

	ceid_64[0] = पढ़ोq_relaxed(smmu_pmu->reg_base + SMMU_PMCG_CEID0);
	ceid_64[1] = पढ़ोq_relaxed(smmu_pmu->reg_base + SMMU_PMCG_CEID1);
	biपंचांगap_from_arr32(smmu_pmu->supported_events, (u32 *)ceid_64,
			  SMMU_PMCG_ARCH_MAX_EVENTS);

	smmu_pmu->num_counters = FIELD_GET(SMMU_PMCG_CFGR_NCTR, cfgr) + 1;

	smmu_pmu->global_filter = !!(cfgr & SMMU_PMCG_CFGR_SID_FILTER_TYPE);

	reg_size = FIELD_GET(SMMU_PMCG_CFGR_SIZE, cfgr);
	smmu_pmu->counter_mask = GENMASK_ULL(reg_size, 0);

	smmu_pmu_reset(smmu_pmu);

	err = smmu_pmu_setup_irq(smmu_pmu);
	अगर (err) अणु
		dev_err(dev, "Setup irq failed, PMU @%pa\n", &res_0->start);
		वापस err;
	पूर्ण

	smmu_pmu->iidr = पढ़ोl_relaxed(smmu_pmu->reg_base + SMMU_PMCG_IIDR);

	name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL, "smmuv3_pmcg_%llx",
			      (res_0->start) >> SMMU_PMCG_PA_SHIFT);
	अगर (!name) अणु
		dev_err(dev, "Create name failed, PMU @%pa\n", &res_0->start);
		वापस -EINVAL;
	पूर्ण

	smmu_pmu_get_acpi_options(smmu_pmu);

	/* Pick one CPU to be the preferred one to use */
	smmu_pmu->on_cpu = raw_smp_processor_id();
	WARN_ON(irq_set_affinity_hपूर्णांक(smmu_pmu->irq,
				      cpumask_of(smmu_pmu->on_cpu)));

	err = cpuhp_state_add_instance_nocalls(cpuhp_state_num,
					       &smmu_pmu->node);
	अगर (err) अणु
		dev_err(dev, "Error %d registering hotplug, PMU @%pa\n",
			err, &res_0->start);
		जाओ out_clear_affinity;
	पूर्ण

	err = perf_pmu_रेजिस्टर(&smmu_pmu->pmu, name, -1);
	अगर (err) अणु
		dev_err(dev, "Error %d registering PMU @%pa\n",
			err, &res_0->start);
		जाओ out_unरेजिस्टर;
	पूर्ण

	dev_info(dev, "Registered PMU @ %pa using %d counters with %s filter settings\n",
		 &res_0->start, smmu_pmu->num_counters,
		 smmu_pmu->global_filter ? "Global(Counter0)" :
		 "Individual");

	वापस 0;

out_unरेजिस्टर:
	cpuhp_state_हटाओ_instance_nocalls(cpuhp_state_num, &smmu_pmu->node);
out_clear_affinity:
	irq_set_affinity_hपूर्णांक(smmu_pmu->irq, शून्य);
	वापस err;
पूर्ण

अटल पूर्णांक smmu_pmu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा smmu_pmu *smmu_pmu = platक्रमm_get_drvdata(pdev);

	perf_pmu_unरेजिस्टर(&smmu_pmu->pmu);
	cpuhp_state_हटाओ_instance_nocalls(cpuhp_state_num, &smmu_pmu->node);
	irq_set_affinity_hपूर्णांक(smmu_pmu->irq, शून्य);

	वापस 0;
पूर्ण

अटल व्योम smmu_pmu_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा smmu_pmu *smmu_pmu = platक्रमm_get_drvdata(pdev);

	smmu_pmu_disable(&smmu_pmu->pmu);
पूर्ण

अटल काष्ठा platक्रमm_driver smmu_pmu_driver = अणु
	.driver = अणु
		.name = "arm-smmu-v3-pmcg",
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = smmu_pmu_probe,
	.हटाओ = smmu_pmu_हटाओ,
	.shutकरोwn = smmu_pmu_shutकरोwn,
पूर्ण;

अटल पूर्णांक __init arm_smmu_pmu_init(व्योम)
अणु
	cpuhp_state_num = cpuhp_setup_state_multi(CPUHP_AP_ONLINE_DYN,
						  "perf/arm/pmcg:online",
						  शून्य,
						  smmu_pmu_offline_cpu);
	अगर (cpuhp_state_num < 0)
		वापस cpuhp_state_num;

	वापस platक्रमm_driver_रेजिस्टर(&smmu_pmu_driver);
पूर्ण
module_init(arm_smmu_pmu_init);

अटल व्योम __निकास arm_smmu_pmu_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&smmu_pmu_driver);
	cpuhp_हटाओ_multi_state(cpuhp_state_num);
पूर्ण

module_निकास(arm_smmu_pmu_निकास);

MODULE_DESCRIPTION("PMU driver for ARM SMMUv3 Performance Monitors Extension");
MODULE_AUTHOR("Neil Leeder <nleeder@codeaurora.org>");
MODULE_AUTHOR("Shameer Kolothum <shameerali.kolothum.thodi@huawei.com>");
MODULE_LICENSE("GPL v2");
