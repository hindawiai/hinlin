<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2015-2017 The Linux Foundation. All rights reserved.
 */
#समावेश <linux/acpi.h>
#समावेश <linux/bitops.h>
#समावेश <linux/bug.h>
#समावेश <linux/cpuhotplug.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/percpu.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/barrier.h>
#समावेश <यंत्र/local64.h>
#समावेश <यंत्र/sysreg.h>
#समावेश <soc/qcom/kryo-l2-accessors.h>

#घोषणा MAX_L2_CTRS             9

#घोषणा L2PMCR_NUM_EV_SHIFT     11
#घोषणा L2PMCR_NUM_EV_MASK      0x1F

#घोषणा L2PMCR                  0x400
#घोषणा L2PMCNTENCLR            0x403
#घोषणा L2PMCNTENSET            0x404
#घोषणा L2PMINTENCLR            0x405
#घोषणा L2PMINTENSET            0x406
#घोषणा L2PMOVSCLR              0x407
#घोषणा L2PMOVSSET              0x408
#घोषणा L2PMCCNTCR              0x409
#घोषणा L2PMCCNTR               0x40A
#घोषणा L2PMCCNTSR              0x40C
#घोषणा L2PMRESR                0x410
#घोषणा IA_L2PMXEVCNTCR_BASE    0x420
#घोषणा IA_L2PMXEVCNTR_BASE     0x421
#घोषणा IA_L2PMXEVFILTER_BASE   0x423
#घोषणा IA_L2PMXEVTYPER_BASE    0x424

#घोषणा IA_L2_REG_OFFSET        0x10

#घोषणा L2PMXEVFILTER_SUFILTER_ALL      0x000E0000
#घोषणा L2PMXEVFILTER_ORGFILTER_IDINDEP 0x00000004
#घोषणा L2PMXEVFILTER_ORGFILTER_ALL     0x00000003

#घोषणा L2EVTYPER_REG_SHIFT     3

#घोषणा L2PMRESR_GROUP_BITS     8
#घोषणा L2PMRESR_GROUP_MASK     GENMASK(7, 0)

#घोषणा L2CYCLE_CTR_BIT         31
#घोषणा L2CYCLE_CTR_RAW_CODE    0xFE

#घोषणा L2PMCR_RESET_ALL        0x6
#घोषणा L2PMCR_COUNTERS_ENABLE  0x1
#घोषणा L2PMCR_COUNTERS_DISABLE 0x0

#घोषणा L2PMRESR_EN             BIT_ULL(63)

#घोषणा L2_EVT_MASK             0x00000FFF
#घोषणा L2_EVT_CODE_MASK        0x00000FF0
#घोषणा L2_EVT_GRP_MASK         0x0000000F
#घोषणा L2_EVT_CODE_SHIFT       4
#घोषणा L2_EVT_GRP_SHIFT        0

#घोषणा L2_EVT_CODE(event)   (((event) & L2_EVT_CODE_MASK) >> L2_EVT_CODE_SHIFT)
#घोषणा L2_EVT_GROUP(event)  (((event) & L2_EVT_GRP_MASK) >> L2_EVT_GRP_SHIFT)

#घोषणा L2_EVT_GROUP_MAX        7

#घोषणा L2_COUNTER_RELOAD       BIT_ULL(31)
#घोषणा L2_CYCLE_COUNTER_RELOAD BIT_ULL(63)


#घोषणा reg_idx(reg, i)         (((i) * IA_L2_REG_OFFSET) + reg##_BASE)

/*
 * Events
 */
#घोषणा L2_EVENT_CYCLES                    0xfe
#घोषणा L2_EVENT_DCACHE_OPS                0x400
#घोषणा L2_EVENT_ICACHE_OPS                0x401
#घोषणा L2_EVENT_TLBI                      0x402
#घोषणा L2_EVENT_BARRIERS                  0x403
#घोषणा L2_EVENT_TOTAL_READS               0x405
#घोषणा L2_EVENT_TOTAL_WRITES              0x406
#घोषणा L2_EVENT_TOTAL_REQUESTS            0x407
#घोषणा L2_EVENT_LDREX                     0x420
#घोषणा L2_EVENT_STREX                     0x421
#घोषणा L2_EVENT_CLREX                     0x422



काष्ठा cluster_pmu;

/*
 * Aggregate PMU. Implements the core pmu functions and manages
 * the hardware PMUs.
 */
काष्ठा l2cache_pmu अणु
	काष्ठा hlist_node node;
	u32 num_pmus;
	काष्ठा pmu pmu;
	पूर्णांक num_counters;
	cpumask_t cpumask;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा cluster_pmu * __percpu *pmu_cluster;
	काष्ठा list_head clusters;
पूर्ण;

/*
 * The cache is made up of one or more clusters, each cluster has its own PMU.
 * Each cluster is associated with one or more CPUs.
 * This काष्ठाure represents one of the hardware PMUs.
 *
 * Events can be envisioned as a 2-dimensional array. Each column represents
 * a group of events. There are 8 groups. Only one entry from each
 * group can be in use at a समय.
 *
 * Events are specअगरied as 0xCCG, where CC is 2 hex digits specअगरying
 * the code (array row) and G specअगरies the group (column).
 *
 * In addition there is a cycle counter event specअगरied by L2CYCLE_CTR_RAW_CODE
 * which is outside the above scheme.
 */
काष्ठा cluster_pmu अणु
	काष्ठा list_head next;
	काष्ठा perf_event *events[MAX_L2_CTRS];
	काष्ठा l2cache_pmu *l2cache_pmu;
	DECLARE_BITMAP(used_counters, MAX_L2_CTRS);
	DECLARE_BITMAP(used_groups, L2_EVT_GROUP_MAX + 1);
	पूर्णांक irq;
	पूर्णांक cluster_id;
	/* The CPU that is used क्रम collecting events on this cluster */
	पूर्णांक on_cpu;
	/* All the CPUs associated with this cluster */
	cpumask_t cluster_cpus;
	spinlock_t pmu_lock;
पूर्ण;

#घोषणा to_l2cache_pmu(p) (container_of(p, काष्ठा l2cache_pmu, pmu))

अटल u32 l2_cycle_ctr_idx;
अटल u32 l2_counter_present_mask;

अटल अंतरभूत u32 idx_to_reg_bit(u32 idx)
अणु
	अगर (idx == l2_cycle_ctr_idx)
		वापस BIT(L2CYCLE_CTR_BIT);

	वापस BIT(idx);
पूर्ण

अटल अंतरभूत काष्ठा cluster_pmu *get_cluster_pmu(
	काष्ठा l2cache_pmu *l2cache_pmu, पूर्णांक cpu)
अणु
	वापस *per_cpu_ptr(l2cache_pmu->pmu_cluster, cpu);
पूर्ण

अटल व्योम cluster_pmu_reset(व्योम)
अणु
	/* Reset all counters */
	kryo_l2_set_indirect_reg(L2PMCR, L2PMCR_RESET_ALL);
	kryo_l2_set_indirect_reg(L2PMCNTENCLR, l2_counter_present_mask);
	kryo_l2_set_indirect_reg(L2PMINTENCLR, l2_counter_present_mask);
	kryo_l2_set_indirect_reg(L2PMOVSCLR, l2_counter_present_mask);
पूर्ण

अटल अंतरभूत व्योम cluster_pmu_enable(व्योम)
अणु
	kryo_l2_set_indirect_reg(L2PMCR, L2PMCR_COUNTERS_ENABLE);
पूर्ण

अटल अंतरभूत व्योम cluster_pmu_disable(व्योम)
अणु
	kryo_l2_set_indirect_reg(L2PMCR, L2PMCR_COUNTERS_DISABLE);
पूर्ण

अटल अंतरभूत व्योम cluster_pmu_counter_set_value(u32 idx, u64 value)
अणु
	अगर (idx == l2_cycle_ctr_idx)
		kryo_l2_set_indirect_reg(L2PMCCNTR, value);
	अन्यथा
		kryo_l2_set_indirect_reg(reg_idx(IA_L2PMXEVCNTR, idx), value);
पूर्ण

अटल अंतरभूत u64 cluster_pmu_counter_get_value(u32 idx)
अणु
	u64 value;

	अगर (idx == l2_cycle_ctr_idx)
		value = kryo_l2_get_indirect_reg(L2PMCCNTR);
	अन्यथा
		value = kryo_l2_get_indirect_reg(reg_idx(IA_L2PMXEVCNTR, idx));

	वापस value;
पूर्ण

अटल अंतरभूत व्योम cluster_pmu_counter_enable(u32 idx)
अणु
	kryo_l2_set_indirect_reg(L2PMCNTENSET, idx_to_reg_bit(idx));
पूर्ण

अटल अंतरभूत व्योम cluster_pmu_counter_disable(u32 idx)
अणु
	kryo_l2_set_indirect_reg(L2PMCNTENCLR, idx_to_reg_bit(idx));
पूर्ण

अटल अंतरभूत व्योम cluster_pmu_counter_enable_पूर्णांकerrupt(u32 idx)
अणु
	kryo_l2_set_indirect_reg(L2PMINTENSET, idx_to_reg_bit(idx));
पूर्ण

अटल अंतरभूत व्योम cluster_pmu_counter_disable_पूर्णांकerrupt(u32 idx)
अणु
	kryo_l2_set_indirect_reg(L2PMINTENCLR, idx_to_reg_bit(idx));
पूर्ण

अटल अंतरभूत व्योम cluster_pmu_set_evccntcr(u32 val)
अणु
	kryo_l2_set_indirect_reg(L2PMCCNTCR, val);
पूर्ण

अटल अंतरभूत व्योम cluster_pmu_set_evcntcr(u32 ctr, u32 val)
अणु
	kryo_l2_set_indirect_reg(reg_idx(IA_L2PMXEVCNTCR, ctr), val);
पूर्ण

अटल अंतरभूत व्योम cluster_pmu_set_evtyper(u32 ctr, u32 val)
अणु
	kryo_l2_set_indirect_reg(reg_idx(IA_L2PMXEVTYPER, ctr), val);
पूर्ण

अटल व्योम cluster_pmu_set_resr(काष्ठा cluster_pmu *cluster,
			       u32 event_group, u32 event_cc)
अणु
	u64 field;
	u64 resr_val;
	u32 shअगरt;
	अचिन्हित दीर्घ flags;

	shअगरt = L2PMRESR_GROUP_BITS * event_group;
	field = ((u64)(event_cc & L2PMRESR_GROUP_MASK) << shअगरt);

	spin_lock_irqsave(&cluster->pmu_lock, flags);

	resr_val = kryo_l2_get_indirect_reg(L2PMRESR);
	resr_val &= ~(L2PMRESR_GROUP_MASK << shअगरt);
	resr_val |= field;
	resr_val |= L2PMRESR_EN;
	kryo_l2_set_indirect_reg(L2PMRESR, resr_val);

	spin_unlock_irqrestore(&cluster->pmu_lock, flags);
पूर्ण

/*
 * Hardware allows filtering of events based on the originating
 * CPU. Turn this off by setting filter bits to allow events from
 * all CPUS, subunits and ID independent events in this cluster.
 */
अटल अंतरभूत व्योम cluster_pmu_set_evfilter_sys_mode(u32 ctr)
अणु
	u32 val =  L2PMXEVFILTER_SUFILTER_ALL |
		   L2PMXEVFILTER_ORGFILTER_IDINDEP |
		   L2PMXEVFILTER_ORGFILTER_ALL;

	kryo_l2_set_indirect_reg(reg_idx(IA_L2PMXEVFILTER, ctr), val);
पूर्ण

अटल अंतरभूत u32 cluster_pmu_getreset_ovsr(व्योम)
अणु
	u32 result = kryo_l2_get_indirect_reg(L2PMOVSSET);

	kryo_l2_set_indirect_reg(L2PMOVSCLR, result);
	वापस result;
पूर्ण

अटल अंतरभूत bool cluster_pmu_has_overflowed(u32 ovsr)
अणु
	वापस !!(ovsr & l2_counter_present_mask);
पूर्ण

अटल अंतरभूत bool cluster_pmu_counter_has_overflowed(u32 ovsr, u32 idx)
अणु
	वापस !!(ovsr & idx_to_reg_bit(idx));
पूर्ण

अटल व्योम l2_cache_event_update(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 delta, prev, now;
	u32 idx = hwc->idx;

	करो अणु
		prev = local64_पढ़ो(&hwc->prev_count);
		now = cluster_pmu_counter_get_value(idx);
	पूर्ण जबतक (local64_cmpxchg(&hwc->prev_count, prev, now) != prev);

	/*
	 * The cycle counter is 64-bit, but all other counters are
	 * 32-bit, and we must handle 32-bit overflow explicitly.
	 */
	delta = now - prev;
	अगर (idx != l2_cycle_ctr_idx)
		delta &= 0xffffffff;

	local64_add(delta, &event->count);
पूर्ण

अटल व्योम l2_cache_cluster_set_period(काष्ठा cluster_pmu *cluster,
				       काष्ठा hw_perf_event *hwc)
अणु
	u32 idx = hwc->idx;
	u64 new;

	/*
	 * We limit the max period to half the max counter value so
	 * that even in the हाल of extreme पूर्णांकerrupt latency the
	 * counter will (hopefully) not wrap past its initial value.
	 */
	अगर (idx == l2_cycle_ctr_idx)
		new = L2_CYCLE_COUNTER_RELOAD;
	अन्यथा
		new = L2_COUNTER_RELOAD;

	local64_set(&hwc->prev_count, new);
	cluster_pmu_counter_set_value(idx, new);
पूर्ण

अटल पूर्णांक l2_cache_get_event_idx(काष्ठा cluster_pmu *cluster,
				   काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx;
	पूर्णांक num_ctrs = cluster->l2cache_pmu->num_counters - 1;
	अचिन्हित पूर्णांक group;

	अगर (hwc->config_base == L2CYCLE_CTR_RAW_CODE) अणु
		अगर (test_and_set_bit(l2_cycle_ctr_idx, cluster->used_counters))
			वापस -EAGAIN;

		वापस l2_cycle_ctr_idx;
	पूर्ण

	idx = find_first_zero_bit(cluster->used_counters, num_ctrs);
	अगर (idx == num_ctrs)
		/* The counters are all in use. */
		वापस -EAGAIN;

	/*
	 * Check क्रम column exclusion: event column alपढ़ोy in use by another
	 * event. This is क्रम events which are not in the same group.
	 * Conflicting events in the same group are detected in event_init.
	 */
	group = L2_EVT_GROUP(hwc->config_base);
	अगर (test_bit(group, cluster->used_groups))
		वापस -EAGAIN;

	set_bit(idx, cluster->used_counters);
	set_bit(group, cluster->used_groups);

	वापस idx;
पूर्ण

अटल व्योम l2_cache_clear_event_idx(काष्ठा cluster_pmu *cluster,
				      काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	clear_bit(idx, cluster->used_counters);
	अगर (hwc->config_base != L2CYCLE_CTR_RAW_CODE)
		clear_bit(L2_EVT_GROUP(hwc->config_base), cluster->used_groups);
पूर्ण

अटल irqवापस_t l2_cache_handle_irq(पूर्णांक irq_num, व्योम *data)
अणु
	काष्ठा cluster_pmu *cluster = data;
	पूर्णांक num_counters = cluster->l2cache_pmu->num_counters;
	u32 ovsr;
	पूर्णांक idx;

	ovsr = cluster_pmu_getreset_ovsr();
	अगर (!cluster_pmu_has_overflowed(ovsr))
		वापस IRQ_NONE;

	क्रम_each_set_bit(idx, cluster->used_counters, num_counters) अणु
		काष्ठा perf_event *event = cluster->events[idx];
		काष्ठा hw_perf_event *hwc;

		अगर (WARN_ON_ONCE(!event))
			जारी;

		अगर (!cluster_pmu_counter_has_overflowed(ovsr, idx))
			जारी;

		l2_cache_event_update(event);
		hwc = &event->hw;

		l2_cache_cluster_set_period(cluster, hwc);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Implementation of असलtract pmu functionality required by
 * the core perf events code.
 */

अटल व्योम l2_cache_pmu_enable(काष्ठा pmu *pmu)
अणु
	/*
	 * Although there is only one PMU (per socket) controlling multiple
	 * physical PMUs (per cluster), because we करो not support per-task mode
	 * each event is associated with a CPU. Each event has pmu_enable
	 * called on its CPU, so here it is only necessary to enable the
	 * counters क्रम the current CPU.
	 */

	cluster_pmu_enable();
पूर्ण

अटल व्योम l2_cache_pmu_disable(काष्ठा pmu *pmu)
अणु
	cluster_pmu_disable();
पूर्ण

अटल पूर्णांक l2_cache_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा cluster_pmu *cluster;
	काष्ठा perf_event *sibling;
	काष्ठा l2cache_pmu *l2cache_pmu;

	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	l2cache_pmu = to_l2cache_pmu(event->pmu);

	अगर (hwc->sample_period) अणु
		dev_dbg_ratelimited(&l2cache_pmu->pdev->dev,
				    "Sampling not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (event->cpu < 0) अणु
		dev_dbg_ratelimited(&l2cache_pmu->pdev->dev,
				    "Per-task mode not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (((L2_EVT_GROUP(event->attr.config) > L2_EVT_GROUP_MAX) ||
	     ((event->attr.config & ~L2_EVT_MASK) != 0)) &&
	    (event->attr.config != L2CYCLE_CTR_RAW_CODE)) अणु
		dev_dbg_ratelimited(&l2cache_pmu->pdev->dev,
				    "Invalid config %llx\n",
				    event->attr.config);
		वापस -EINVAL;
	पूर्ण

	/* Don't allow groups with mixed PMUs, except क्रम s/w events */
	अगर (event->group_leader->pmu != event->pmu &&
	    !is_software_event(event->group_leader)) अणु
		dev_dbg_ratelimited(&l2cache_pmu->pdev->dev,
			 "Can't create mixed PMU group\n");
		वापस -EINVAL;
	पूर्ण

	क्रम_each_sibling_event(sibling, event->group_leader) अणु
		अगर (sibling->pmu != event->pmu &&
		    !is_software_event(sibling)) अणु
			dev_dbg_ratelimited(&l2cache_pmu->pdev->dev,
				 "Can't create mixed PMU group\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	cluster = get_cluster_pmu(l2cache_pmu, event->cpu);
	अगर (!cluster) अणु
		/* CPU has not been initialised */
		dev_dbg_ratelimited(&l2cache_pmu->pdev->dev,
			"CPU%d not associated with L2 cluster\n", event->cpu);
		वापस -EINVAL;
	पूर्ण

	/* Ensure all events in a group are on the same cpu */
	अगर ((event->group_leader != event) &&
	    (cluster->on_cpu != event->group_leader->cpu)) अणु
		dev_dbg_ratelimited(&l2cache_pmu->pdev->dev,
			 "Can't create group on CPUs %d and %d",
			 event->cpu, event->group_leader->cpu);
		वापस -EINVAL;
	पूर्ण

	अगर ((event != event->group_leader) &&
	    !is_software_event(event->group_leader) &&
	    (L2_EVT_GROUP(event->group_leader->attr.config) ==
	     L2_EVT_GROUP(event->attr.config))) अणु
		dev_dbg_ratelimited(&l2cache_pmu->pdev->dev,
			 "Column exclusion: conflicting events %llx %llx\n",
		       event->group_leader->attr.config,
		       event->attr.config);
		वापस -EINVAL;
	पूर्ण

	क्रम_each_sibling_event(sibling, event->group_leader) अणु
		अगर ((sibling != event) &&
		    !is_software_event(sibling) &&
		    (L2_EVT_GROUP(sibling->attr.config) ==
		     L2_EVT_GROUP(event->attr.config))) अणु
			dev_dbg_ratelimited(&l2cache_pmu->pdev->dev,
			     "Column exclusion: conflicting events %llx %llx\n",
					    sibling->attr.config,
					    event->attr.config);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	hwc->idx = -1;
	hwc->config_base = event->attr.config;

	/*
	 * Ensure all events are on the same cpu so all events are in the
	 * same cpu context, to aव्योम races on pmu_enable etc.
	 */
	event->cpu = cluster->on_cpu;

	वापस 0;
पूर्ण

अटल व्योम l2_cache_event_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cluster_pmu *cluster;
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;
	u32 config;
	u32 event_cc, event_group;

	hwc->state = 0;

	cluster = get_cluster_pmu(to_l2cache_pmu(event->pmu), event->cpu);

	l2_cache_cluster_set_period(cluster, hwc);

	अगर (hwc->config_base == L2CYCLE_CTR_RAW_CODE) अणु
		cluster_pmu_set_evccntcr(0);
	पूर्ण अन्यथा अणु
		config = hwc->config_base;
		event_cc    = L2_EVT_CODE(config);
		event_group = L2_EVT_GROUP(config);

		cluster_pmu_set_evcntcr(idx, 0);
		cluster_pmu_set_evtyper(idx, event_group);
		cluster_pmu_set_resr(cluster, event_group, event_cc);
		cluster_pmu_set_evfilter_sys_mode(idx);
	पूर्ण

	cluster_pmu_counter_enable_पूर्णांकerrupt(idx);
	cluster_pmu_counter_enable(idx);
पूर्ण

अटल व्योम l2_cache_event_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	अगर (hwc->state & PERF_HES_STOPPED)
		वापस;

	cluster_pmu_counter_disable_पूर्णांकerrupt(idx);
	cluster_pmu_counter_disable(idx);

	अगर (flags & PERF_EF_UPDATE)
		l2_cache_event_update(event);
	hwc->state |= PERF_HES_STOPPED | PERF_HES_UPTODATE;
पूर्ण

अटल पूर्णांक l2_cache_event_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx;
	पूर्णांक err = 0;
	काष्ठा cluster_pmu *cluster;

	cluster = get_cluster_pmu(to_l2cache_pmu(event->pmu), event->cpu);

	idx = l2_cache_get_event_idx(cluster, event);
	अगर (idx < 0)
		वापस idx;

	hwc->idx = idx;
	hwc->state = PERF_HES_STOPPED | PERF_HES_UPTODATE;
	cluster->events[idx] = event;
	local64_set(&hwc->prev_count, 0);

	अगर (flags & PERF_EF_START)
		l2_cache_event_start(event, flags);

	/* Propagate changes to the userspace mapping. */
	perf_event_update_userpage(event);

	वापस err;
पूर्ण

अटल व्योम l2_cache_event_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा cluster_pmu *cluster;
	पूर्णांक idx = hwc->idx;

	cluster = get_cluster_pmu(to_l2cache_pmu(event->pmu), event->cpu);

	l2_cache_event_stop(event, flags | PERF_EF_UPDATE);
	cluster->events[idx] = शून्य;
	l2_cache_clear_event_idx(cluster, event);

	perf_event_update_userpage(event);
पूर्ण

अटल व्योम l2_cache_event_पढ़ो(काष्ठा perf_event *event)
अणु
	l2_cache_event_update(event);
पूर्ण

अटल sमाप_प्रकार l2_cache_pmu_cpumask_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा l2cache_pmu *l2cache_pmu = to_l2cache_pmu(dev_get_drvdata(dev));

	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, &l2cache_pmu->cpumask);
पूर्ण

अटल काष्ठा device_attribute l2_cache_pmu_cpumask_attr =
		__ATTR(cpumask, S_IRUGO, l2_cache_pmu_cpumask_show, शून्य);

अटल काष्ठा attribute *l2_cache_pmu_cpumask_attrs[] = अणु
	&l2_cache_pmu_cpumask_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group l2_cache_pmu_cpumask_group = अणु
	.attrs = l2_cache_pmu_cpumask_attrs,
पूर्ण;

/* CCG क्रमmat क्रम perf RAW codes. */
PMU_FORMAT_ATTR(l2_code,   "config:4-11");
PMU_FORMAT_ATTR(l2_group,  "config:0-3");
PMU_FORMAT_ATTR(event,     "config:0-11");

अटल काष्ठा attribute *l2_cache_pmu_क्रमmats[] = अणु
	&क्रमmat_attr_l2_code.attr,
	&क्रमmat_attr_l2_group.attr,
	&क्रमmat_attr_event.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group l2_cache_pmu_क्रमmat_group = अणु
	.name = "format",
	.attrs = l2_cache_pmu_क्रमmats,
पूर्ण;

अटल sमाप_प्रकार l2cache_pmu_event_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *page)
अणु
	काष्ठा perf_pmu_events_attr *pmu_attr;

	pmu_attr = container_of(attr, काष्ठा perf_pmu_events_attr, attr);
	वापस sysfs_emit(page, "event=0x%02llx\n", pmu_attr->id);
पूर्ण

#घोषणा L2CACHE_EVENT_ATTR(_name, _id)					     \
	(&((काष्ठा perf_pmu_events_attr[]) अणु				     \
		अणु .attr = __ATTR(_name, 0444, l2cache_pmu_event_show, शून्य), \
		  .id = _id, पूर्ण						     \
	पूर्ण)[0].attr.attr)

अटल काष्ठा attribute *l2_cache_pmu_events[] = अणु
	L2CACHE_EVENT_ATTR(cycles, L2_EVENT_CYCLES),
	L2CACHE_EVENT_ATTR(dcache-ops, L2_EVENT_DCACHE_OPS),
	L2CACHE_EVENT_ATTR(icache-ops, L2_EVENT_ICACHE_OPS),
	L2CACHE_EVENT_ATTR(tlbi, L2_EVENT_TLBI),
	L2CACHE_EVENT_ATTR(barriers, L2_EVENT_BARRIERS),
	L2CACHE_EVENT_ATTR(total-पढ़ोs, L2_EVENT_TOTAL_READS),
	L2CACHE_EVENT_ATTR(total-ग_लिखोs, L2_EVENT_TOTAL_WRITES),
	L2CACHE_EVENT_ATTR(total-requests, L2_EVENT_TOTAL_REQUESTS),
	L2CACHE_EVENT_ATTR(ldrex, L2_EVENT_LDREX),
	L2CACHE_EVENT_ATTR(strex, L2_EVENT_STREX),
	L2CACHE_EVENT_ATTR(clrex, L2_EVENT_CLREX),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group l2_cache_pmu_events_group = अणु
	.name = "events",
	.attrs = l2_cache_pmu_events,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *l2_cache_pmu_attr_grps[] = अणु
	&l2_cache_pmu_क्रमmat_group,
	&l2_cache_pmu_cpumask_group,
	&l2_cache_pmu_events_group,
	शून्य,
पूर्ण;

/*
 * Generic device handlers
 */

अटल स्थिर काष्ठा acpi_device_id l2_cache_pmu_acpi_match[] = अणु
	अणु "QCOM8130", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक get_num_counters(व्योम)
अणु
	पूर्णांक val;

	val = kryo_l2_get_indirect_reg(L2PMCR);

	/*
	 * Read number of counters from L2PMCR and add 1
	 * क्रम the cycle counter.
	 */
	वापस ((val >> L2PMCR_NUM_EV_SHIFT) & L2PMCR_NUM_EV_MASK) + 1;
पूर्ण

अटल काष्ठा cluster_pmu *l2_cache_associate_cpu_with_cluster(
	काष्ठा l2cache_pmu *l2cache_pmu, पूर्णांक cpu)
अणु
	u64 mpidr;
	पूर्णांक cpu_cluster_id;
	काष्ठा cluster_pmu *cluster = शून्य;

	/*
	 * This assumes that the cluster_id is in MPIDR[aff1] क्रम
	 * single-thपढ़ोed cores, and MPIDR[aff2] क्रम multi-thपढ़ोed
	 * cores. This logic will have to be updated अगर this changes.
	 */
	mpidr = पढ़ो_cpuid_mpidr();
	अगर (mpidr & MPIDR_MT_BITMASK)
		cpu_cluster_id = MPIDR_AFFINITY_LEVEL(mpidr, 2);
	अन्यथा
		cpu_cluster_id = MPIDR_AFFINITY_LEVEL(mpidr, 1);

	list_क्रम_each_entry(cluster, &l2cache_pmu->clusters, next) अणु
		अगर (cluster->cluster_id != cpu_cluster_id)
			जारी;

		dev_info(&l2cache_pmu->pdev->dev,
			 "CPU%d associated with cluster %d\n", cpu,
			 cluster->cluster_id);
		cpumask_set_cpu(cpu, &cluster->cluster_cpus);
		*per_cpu_ptr(l2cache_pmu->pmu_cluster, cpu) = cluster;
		अवरोध;
	पूर्ण

	वापस cluster;
पूर्ण

अटल पूर्णांक l2cache_pmu_online_cpu(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा cluster_pmu *cluster;
	काष्ठा l2cache_pmu *l2cache_pmu;

	l2cache_pmu = hlist_entry_safe(node, काष्ठा l2cache_pmu, node);
	cluster = get_cluster_pmu(l2cache_pmu, cpu);
	अगर (!cluster) अणु
		/* First समय this CPU has come online */
		cluster = l2_cache_associate_cpu_with_cluster(l2cache_pmu, cpu);
		अगर (!cluster) अणु
			/* Only अगर broken firmware करोesn't list every cluster */
			WARN_ONCE(1, "No L2 cache cluster for CPU%d\n", cpu);
			वापस 0;
		पूर्ण
	पूर्ण

	/* If another CPU is managing this cluster, we're करोne */
	अगर (cluster->on_cpu != -1)
		वापस 0;

	/*
	 * All CPUs on this cluster were करोwn, use this one.
	 * Reset to put it पूर्णांकo sane state.
	 */
	cluster->on_cpu = cpu;
	cpumask_set_cpu(cpu, &l2cache_pmu->cpumask);
	cluster_pmu_reset();

	WARN_ON(irq_set_affinity(cluster->irq, cpumask_of(cpu)));
	enable_irq(cluster->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक l2cache_pmu_offline_cpu(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा cluster_pmu *cluster;
	काष्ठा l2cache_pmu *l2cache_pmu;
	cpumask_t cluster_online_cpus;
	अचिन्हित पूर्णांक target;

	l2cache_pmu = hlist_entry_safe(node, काष्ठा l2cache_pmu, node);
	cluster = get_cluster_pmu(l2cache_pmu, cpu);
	अगर (!cluster)
		वापस 0;

	/* If this CPU is not managing the cluster, we're करोne */
	अगर (cluster->on_cpu != cpu)
		वापस 0;

	/* Give up ownership of cluster */
	cpumask_clear_cpu(cpu, &l2cache_pmu->cpumask);
	cluster->on_cpu = -1;

	/* Any other CPU क्रम this cluster which is still online */
	cpumask_and(&cluster_online_cpus, &cluster->cluster_cpus,
		    cpu_online_mask);
	target = cpumask_any_but(&cluster_online_cpus, cpu);
	अगर (target >= nr_cpu_ids) अणु
		disable_irq(cluster->irq);
		वापस 0;
	पूर्ण

	perf_pmu_migrate_context(&l2cache_pmu->pmu, cpu, target);
	cluster->on_cpu = target;
	cpumask_set_cpu(target, &l2cache_pmu->cpumask);
	WARN_ON(irq_set_affinity(cluster->irq, cpumask_of(target)));

	वापस 0;
पूर्ण

अटल पूर्णांक l2_cache_pmu_probe_cluster(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev->parent);
	काष्ठा platक्रमm_device *sdev = to_platक्रमm_device(dev);
	काष्ठा l2cache_pmu *l2cache_pmu = data;
	काष्ठा cluster_pmu *cluster;
	काष्ठा acpi_device *device;
	अचिन्हित दीर्घ fw_cluster_id;
	पूर्णांक err;
	पूर्णांक irq;

	अगर (acpi_bus_get_device(ACPI_HANDLE(dev), &device))
		वापस -ENODEV;

	अगर (kम_से_अदीर्घ(device->pnp.unique_id, 10, &fw_cluster_id) < 0) अणु
		dev_err(&pdev->dev, "unable to read ACPI uid\n");
		वापस -ENODEV;
	पूर्ण

	cluster = devm_kzalloc(&pdev->dev, माप(*cluster), GFP_KERNEL);
	अगर (!cluster)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&cluster->next);
	list_add(&cluster->next, &l2cache_pmu->clusters);
	cluster->cluster_id = fw_cluster_id;

	irq = platक्रमm_get_irq(sdev, 0);
	अगर (irq < 0)
		वापस irq;
	irq_set_status_flags(irq, IRQ_NOAUTOEN);
	cluster->irq = irq;

	cluster->l2cache_pmu = l2cache_pmu;
	cluster->on_cpu = -1;

	err = devm_request_irq(&pdev->dev, irq, l2_cache_handle_irq,
			       IRQF_NOBALANCING | IRQF_NO_THREAD,
			       "l2-cache-pmu", cluster);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"Unable to request IRQ%d for L2 PMU counters\n", irq);
		वापस err;
	पूर्ण

	dev_info(&pdev->dev,
		"Registered L2 cache PMU cluster %ld\n", fw_cluster_id);

	spin_lock_init(&cluster->pmu_lock);

	l2cache_pmu->num_pmus++;

	वापस 0;
पूर्ण

अटल पूर्णांक l2_cache_pmu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक err;
	काष्ठा l2cache_pmu *l2cache_pmu;

	l2cache_pmu =
		devm_kzalloc(&pdev->dev, माप(*l2cache_pmu), GFP_KERNEL);
	अगर (!l2cache_pmu)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&l2cache_pmu->clusters);

	platक्रमm_set_drvdata(pdev, l2cache_pmu);
	l2cache_pmu->pmu = (काष्ठा pmu) अणु
		/* suffix is instance id क्रम future use with multiple sockets */
		.name		= "l2cache_0",
		.task_ctx_nr    = perf_invalid_context,
		.pmu_enable	= l2_cache_pmu_enable,
		.pmu_disable	= l2_cache_pmu_disable,
		.event_init	= l2_cache_event_init,
		.add		= l2_cache_event_add,
		.del		= l2_cache_event_del,
		.start		= l2_cache_event_start,
		.stop		= l2_cache_event_stop,
		.पढ़ो		= l2_cache_event_पढ़ो,
		.attr_groups	= l2_cache_pmu_attr_grps,
		.capabilities	= PERF_PMU_CAP_NO_EXCLUDE,
	पूर्ण;

	l2cache_pmu->num_counters = get_num_counters();
	l2cache_pmu->pdev = pdev;
	l2cache_pmu->pmu_cluster = devm_alloc_percpu(&pdev->dev,
						     काष्ठा cluster_pmu *);
	अगर (!l2cache_pmu->pmu_cluster)
		वापस -ENOMEM;

	l2_cycle_ctr_idx = l2cache_pmu->num_counters - 1;
	l2_counter_present_mask = GENMASK(l2cache_pmu->num_counters - 2, 0) |
		BIT(L2CYCLE_CTR_BIT);

	cpumask_clear(&l2cache_pmu->cpumask);

	/* Read cluster info and initialize each cluster */
	err = device_क्रम_each_child(&pdev->dev, l2cache_pmu,
				    l2_cache_pmu_probe_cluster);
	अगर (err)
		वापस err;

	अगर (l2cache_pmu->num_pmus == 0) अणु
		dev_err(&pdev->dev, "No hardware L2 cache PMUs found\n");
		वापस -ENODEV;
	पूर्ण

	err = cpuhp_state_add_instance(CPUHP_AP_PERF_ARM_QCOM_L2_ONLINE,
				       &l2cache_pmu->node);
	अगर (err) अणु
		dev_err(&pdev->dev, "Error %d registering hotplug", err);
		वापस err;
	पूर्ण

	err = perf_pmu_रेजिस्टर(&l2cache_pmu->pmu, l2cache_pmu->pmu.name, -1);
	अगर (err) अणु
		dev_err(&pdev->dev, "Error %d registering L2 cache PMU\n", err);
		जाओ out_unरेजिस्टर;
	पूर्ण

	dev_info(&pdev->dev, "Registered L2 cache PMU using %d HW PMUs\n",
		 l2cache_pmu->num_pmus);

	वापस err;

out_unरेजिस्टर:
	cpuhp_state_हटाओ_instance(CPUHP_AP_PERF_ARM_QCOM_L2_ONLINE,
				    &l2cache_pmu->node);
	वापस err;
पूर्ण

अटल पूर्णांक l2_cache_pmu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा l2cache_pmu *l2cache_pmu =
		to_l2cache_pmu(platक्रमm_get_drvdata(pdev));

	perf_pmu_unरेजिस्टर(&l2cache_pmu->pmu);
	cpuhp_state_हटाओ_instance(CPUHP_AP_PERF_ARM_QCOM_L2_ONLINE,
				    &l2cache_pmu->node);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver l2_cache_pmu_driver = अणु
	.driver = अणु
		.name = "qcom-l2cache-pmu",
		.acpi_match_table = ACPI_PTR(l2_cache_pmu_acpi_match),
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe = l2_cache_pmu_probe,
	.हटाओ = l2_cache_pmu_हटाओ,
पूर्ण;

अटल पूर्णांक __init रेजिस्टर_l2_cache_pmu_driver(व्योम)
अणु
	पूर्णांक err;

	err = cpuhp_setup_state_multi(CPUHP_AP_PERF_ARM_QCOM_L2_ONLINE,
				      "AP_PERF_ARM_QCOM_L2_ONLINE",
				      l2cache_pmu_online_cpu,
				      l2cache_pmu_offline_cpu);
	अगर (err)
		वापस err;

	वापस platक्रमm_driver_रेजिस्टर(&l2_cache_pmu_driver);
पूर्ण
device_initcall(रेजिस्टर_l2_cache_pmu_driver);
