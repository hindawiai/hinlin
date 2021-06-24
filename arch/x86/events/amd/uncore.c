<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Advanced Micro Devices, Inc.
 *
 * Author: Jacob Shin <jacob.shin@amd.com>
 */

#समावेश <linux/perf_event.h>
#समावेश <linux/percpu.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpumask.h>

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/perf_event.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/smp.h>

#घोषणा NUM_COUNTERS_NB		4
#घोषणा NUM_COUNTERS_L2		4
#घोषणा NUM_COUNTERS_L3		6
#घोषणा MAX_COUNTERS		6

#घोषणा RDPMC_BASE_NB		6
#घोषणा RDPMC_BASE_LLC		10

#घोषणा COUNTER_SHIFT		16

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt)	"amd_uncore: " fmt

अटल पूर्णांक num_counters_llc;
अटल पूर्णांक num_counters_nb;
अटल bool l3_mask;

अटल HLIST_HEAD(uncore_unused_list);

काष्ठा amd_uncore अणु
	पूर्णांक id;
	पूर्णांक refcnt;
	पूर्णांक cpu;
	पूर्णांक num_counters;
	पूर्णांक rdpmc_base;
	u32 msr_base;
	cpumask_t *active_mask;
	काष्ठा pmu *pmu;
	काष्ठा perf_event *events[MAX_COUNTERS];
	काष्ठा hlist_node node;
पूर्ण;

अटल काष्ठा amd_uncore * __percpu *amd_uncore_nb;
अटल काष्ठा amd_uncore * __percpu *amd_uncore_llc;

अटल काष्ठा pmu amd_nb_pmu;
अटल काष्ठा pmu amd_llc_pmu;

अटल cpumask_t amd_nb_active_mask;
अटल cpumask_t amd_llc_active_mask;

अटल bool is_nb_event(काष्ठा perf_event *event)
अणु
	वापस event->pmu->type == amd_nb_pmu.type;
पूर्ण

अटल bool is_llc_event(काष्ठा perf_event *event)
अणु
	वापस event->pmu->type == amd_llc_pmu.type;
पूर्ण

अटल काष्ठा amd_uncore *event_to_amd_uncore(काष्ठा perf_event *event)
अणु
	अगर (is_nb_event(event) && amd_uncore_nb)
		वापस *per_cpu_ptr(amd_uncore_nb, event->cpu);
	अन्यथा अगर (is_llc_event(event) && amd_uncore_llc)
		वापस *per_cpu_ptr(amd_uncore_llc, event->cpu);

	वापस शून्य;
पूर्ण

अटल व्योम amd_uncore_पढ़ो(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	u64 prev, new;
	s64 delta;

	/*
	 * since we करो not enable counter overflow पूर्णांकerrupts,
	 * we करो not have to worry about prev_count changing on us
	 */

	prev = local64_पढ़ो(&hwc->prev_count);
	rdpmcl(hwc->event_base_rdpmc, new);
	local64_set(&hwc->prev_count, new);
	delta = (new << COUNTER_SHIFT) - (prev << COUNTER_SHIFT);
	delta >>= COUNTER_SHIFT;
	local64_add(delta, &event->count);
पूर्ण

अटल व्योम amd_uncore_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (flags & PERF_EF_RELOAD)
		wrmsrl(hwc->event_base, (u64)local64_पढ़ो(&hwc->prev_count));

	hwc->state = 0;
	wrmsrl(hwc->config_base, (hwc->config | ARCH_PERFMON_EVENTSEL_ENABLE));
	perf_event_update_userpage(event);
पूर्ण

अटल व्योम amd_uncore_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;

	wrmsrl(hwc->config_base, hwc->config);
	hwc->state |= PERF_HES_STOPPED;

	अगर ((flags & PERF_EF_UPDATE) && !(hwc->state & PERF_HES_UPTODATE)) अणु
		amd_uncore_पढ़ो(event);
		hwc->state |= PERF_HES_UPTODATE;
	पूर्ण
पूर्ण

अटल पूर्णांक amd_uncore_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	पूर्णांक i;
	काष्ठा amd_uncore *uncore = event_to_amd_uncore(event);
	काष्ठा hw_perf_event *hwc = &event->hw;

	/* are we alपढ़ोy asचिन्हित? */
	अगर (hwc->idx != -1 && uncore->events[hwc->idx] == event)
		जाओ out;

	क्रम (i = 0; i < uncore->num_counters; i++) अणु
		अगर (uncore->events[i] == event) अणु
			hwc->idx = i;
			जाओ out;
		पूर्ण
	पूर्ण

	/* अगर not, take the first available counter */
	hwc->idx = -1;
	क्रम (i = 0; i < uncore->num_counters; i++) अणु
		अगर (cmpxchg(&uncore->events[i], शून्य, event) == शून्य) अणु
			hwc->idx = i;
			अवरोध;
		पूर्ण
	पूर्ण

out:
	अगर (hwc->idx == -1)
		वापस -EBUSY;

	hwc->config_base = uncore->msr_base + (2 * hwc->idx);
	hwc->event_base = uncore->msr_base + 1 + (2 * hwc->idx);
	hwc->event_base_rdpmc = uncore->rdpmc_base + hwc->idx;
	hwc->state = PERF_HES_UPTODATE | PERF_HES_STOPPED;

	अगर (flags & PERF_EF_START)
		amd_uncore_start(event, PERF_EF_RELOAD);

	वापस 0;
पूर्ण

अटल व्योम amd_uncore_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	पूर्णांक i;
	काष्ठा amd_uncore *uncore = event_to_amd_uncore(event);
	काष्ठा hw_perf_event *hwc = &event->hw;

	amd_uncore_stop(event, PERF_EF_UPDATE);

	क्रम (i = 0; i < uncore->num_counters; i++) अणु
		अगर (cmpxchg(&uncore->events[i], event, शून्य) == event)
			अवरोध;
	पूर्ण

	hwc->idx = -1;
पूर्ण

/*
 * Return a full thपढ़ो and slice mask unless user
 * has provided them
 */
अटल u64 l3_thपढ़ो_slice_mask(u64 config)
अणु
	अगर (boot_cpu_data.x86 <= 0x18)
		वापस ((config & AMD64_L3_SLICE_MASK) ? : AMD64_L3_SLICE_MASK) |
		       ((config & AMD64_L3_THREAD_MASK) ? : AMD64_L3_THREAD_MASK);

	/*
	 * If the user करोesn't specify a threadmask, they're not trying to
	 * count core 0, so we enable all cores & thपढ़ोs.
	 * We'll also assume that they want to count slice 0 अगर they specअगरy
	 * a thपढ़ोmask and leave sliceid and enallslices unpopulated.
	 */
	अगर (!(config & AMD64_L3_F19H_THREAD_MASK))
		वापस AMD64_L3_F19H_THREAD_MASK | AMD64_L3_EN_ALL_SLICES |
		       AMD64_L3_EN_ALL_CORES;

	वापस config & (AMD64_L3_F19H_THREAD_MASK | AMD64_L3_SLICEID_MASK |
			 AMD64_L3_EN_ALL_CORES | AMD64_L3_EN_ALL_SLICES |
			 AMD64_L3_COREID_MASK);
पूर्ण

अटल पूर्णांक amd_uncore_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा amd_uncore *uncore;
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	/*
	 * NB and Last level cache counters (MSRs) are shared across all cores
	 * that share the same NB / Last level cache.  On family 16h and below,
	 * Interrupts can be directed to a single target core, however, event
	 * counts generated by processes running on other cores cannot be masked
	 * out. So we करो not support sampling and per-thपढ़ो events via
	 * CAP_NO_INTERRUPT, and we करो not enable counter overflow पूर्णांकerrupts:
	 */
	hwc->config = event->attr.config & AMD64_RAW_EVENT_MASK_NB;
	hwc->idx = -1;

	अगर (event->cpu < 0)
		वापस -EINVAL;

	/*
	 * SliceMask and Thपढ़ोMask need to be set क्रम certain L3 events.
	 * For other events, the two fields करो not affect the count.
	 */
	अगर (l3_mask && is_llc_event(event))
		hwc->config |= l3_thपढ़ो_slice_mask(event->attr.config);

	uncore = event_to_amd_uncore(event);
	अगर (!uncore)
		वापस -ENODEV;

	/*
	 * since request can come in to any of the shared cores, we will remap
	 * to a single common cpu.
	 */
	event->cpu = uncore->cpu;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार amd_uncore_attr_show_cpumask(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	cpumask_t *active_mask;
	काष्ठा pmu *pmu = dev_get_drvdata(dev);

	अगर (pmu->type == amd_nb_pmu.type)
		active_mask = &amd_nb_active_mask;
	अन्यथा अगर (pmu->type == amd_llc_pmu.type)
		active_mask = &amd_llc_active_mask;
	अन्यथा
		वापस 0;

	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, active_mask);
पूर्ण
अटल DEVICE_ATTR(cpumask, S_IRUGO, amd_uncore_attr_show_cpumask, शून्य);

अटल काष्ठा attribute *amd_uncore_attrs[] = अणु
	&dev_attr_cpumask.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group amd_uncore_attr_group = अणु
	.attrs = amd_uncore_attrs,
पूर्ण;

#घोषणा DEFINE_UNCORE_FORMAT_ATTR(_var, _name, _क्रमmat)			\
अटल sमाप_प्रकार __uncore_##_var##_show(काष्ठा device *dev,		\
				काष्ठा device_attribute *attr,		\
				अक्षर *page)				\
अणु									\
	BUILD_BUG_ON(माप(_क्रमmat) >= PAGE_SIZE);			\
	वापस प्र_लिखो(page, _क्रमmat "\n");				\
पूर्ण									\
अटल काष्ठा device_attribute क्रमmat_attr_##_var =			\
	__ATTR(_name, 0444, __uncore_##_var##_show, शून्य)

DEFINE_UNCORE_FORMAT_ATTR(event12,	event,		"config:0-7,32-35");
DEFINE_UNCORE_FORMAT_ATTR(event14,	event,		"config:0-7,32-35,59-60"); /* F17h+ DF */
DEFINE_UNCORE_FORMAT_ATTR(event8,	event,		"config:0-7");		   /* F17h+ L3 */
DEFINE_UNCORE_FORMAT_ATTR(umask,	umask,		"config:8-15");
DEFINE_UNCORE_FORMAT_ATTR(coreid,	coreid,		"config:42-44");	   /* F19h L3 */
DEFINE_UNCORE_FORMAT_ATTR(slicemask,	slicemask,	"config:48-51");	   /* F17h L3 */
DEFINE_UNCORE_FORMAT_ATTR(thपढ़ोmask8,	thपढ़ोmask,	"config:56-63");	   /* F17h L3 */
DEFINE_UNCORE_FORMAT_ATTR(thपढ़ोmask2,	thपढ़ोmask,	"config:56-57");	   /* F19h L3 */
DEFINE_UNCORE_FORMAT_ATTR(enallslices,	enallslices,	"config:46");		   /* F19h L3 */
DEFINE_UNCORE_FORMAT_ATTR(enallcores,	enallcores,	"config:47");		   /* F19h L3 */
DEFINE_UNCORE_FORMAT_ATTR(sliceid,	sliceid,	"config:48-50");	   /* F19h L3 */

अटल काष्ठा attribute *amd_uncore_df_क्रमmat_attr[] = अणु
	&क्रमmat_attr_event12.attr, /* event14 अगर F17h+ */
	&क्रमmat_attr_umask.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *amd_uncore_l3_क्रमmat_attr[] = अणु
	&क्रमmat_attr_event12.attr, /* event8 अगर F17h+ */
	&क्रमmat_attr_umask.attr,
	शून्य, /* slicemask अगर F17h,	coreid अगर F19h */
	शून्य, /* thपढ़ोmask8 अगर F17h,	enallslices अगर F19h */
	शून्य, /*			enallcores अगर F19h */
	शून्य, /*			sliceid अगर F19h */
	शून्य, /*			thपढ़ोmask2 अगर F19h */
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group amd_uncore_df_क्रमmat_group = अणु
	.name = "format",
	.attrs = amd_uncore_df_क्रमmat_attr,
पूर्ण;

अटल काष्ठा attribute_group amd_uncore_l3_क्रमmat_group = अणु
	.name = "format",
	.attrs = amd_uncore_l3_क्रमmat_attr,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *amd_uncore_df_attr_groups[] = अणु
	&amd_uncore_attr_group,
	&amd_uncore_df_क्रमmat_group,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *amd_uncore_l3_attr_groups[] = अणु
	&amd_uncore_attr_group,
	&amd_uncore_l3_क्रमmat_group,
	शून्य,
पूर्ण;

अटल काष्ठा pmu amd_nb_pmu = अणु
	.task_ctx_nr	= perf_invalid_context,
	.attr_groups	= amd_uncore_df_attr_groups,
	.name		= "amd_nb",
	.event_init	= amd_uncore_event_init,
	.add		= amd_uncore_add,
	.del		= amd_uncore_del,
	.start		= amd_uncore_start,
	.stop		= amd_uncore_stop,
	.पढ़ो		= amd_uncore_पढ़ो,
	.capabilities	= PERF_PMU_CAP_NO_EXCLUDE | PERF_PMU_CAP_NO_INTERRUPT,
पूर्ण;

अटल काष्ठा pmu amd_llc_pmu = अणु
	.task_ctx_nr	= perf_invalid_context,
	.attr_groups	= amd_uncore_l3_attr_groups,
	.name		= "amd_l2",
	.event_init	= amd_uncore_event_init,
	.add		= amd_uncore_add,
	.del		= amd_uncore_del,
	.start		= amd_uncore_start,
	.stop		= amd_uncore_stop,
	.पढ़ो		= amd_uncore_पढ़ो,
	.capabilities	= PERF_PMU_CAP_NO_EXCLUDE | PERF_PMU_CAP_NO_INTERRUPT,
पूर्ण;

अटल काष्ठा amd_uncore *amd_uncore_alloc(अचिन्हित पूर्णांक cpu)
अणु
	वापस kzalloc_node(माप(काष्ठा amd_uncore), GFP_KERNEL,
			cpu_to_node(cpu));
पूर्ण

अटल पूर्णांक amd_uncore_cpu_up_prepare(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा amd_uncore *uncore_nb = शून्य, *uncore_llc;

	अगर (amd_uncore_nb) अणु
		uncore_nb = amd_uncore_alloc(cpu);
		अगर (!uncore_nb)
			जाओ fail;
		uncore_nb->cpu = cpu;
		uncore_nb->num_counters = num_counters_nb;
		uncore_nb->rdpmc_base = RDPMC_BASE_NB;
		uncore_nb->msr_base = MSR_F15H_NB_PERF_CTL;
		uncore_nb->active_mask = &amd_nb_active_mask;
		uncore_nb->pmu = &amd_nb_pmu;
		uncore_nb->id = -1;
		*per_cpu_ptr(amd_uncore_nb, cpu) = uncore_nb;
	पूर्ण

	अगर (amd_uncore_llc) अणु
		uncore_llc = amd_uncore_alloc(cpu);
		अगर (!uncore_llc)
			जाओ fail;
		uncore_llc->cpu = cpu;
		uncore_llc->num_counters = num_counters_llc;
		uncore_llc->rdpmc_base = RDPMC_BASE_LLC;
		uncore_llc->msr_base = MSR_F16H_L2I_PERF_CTL;
		uncore_llc->active_mask = &amd_llc_active_mask;
		uncore_llc->pmu = &amd_llc_pmu;
		uncore_llc->id = -1;
		*per_cpu_ptr(amd_uncore_llc, cpu) = uncore_llc;
	पूर्ण

	वापस 0;

fail:
	अगर (amd_uncore_nb)
		*per_cpu_ptr(amd_uncore_nb, cpu) = शून्य;
	kमुक्त(uncore_nb);
	वापस -ENOMEM;
पूर्ण

अटल काष्ठा amd_uncore *
amd_uncore_find_online_sibling(काष्ठा amd_uncore *this,
			       काष्ठा amd_uncore * __percpu *uncores)
अणु
	अचिन्हित पूर्णांक cpu;
	काष्ठा amd_uncore *that;

	क्रम_each_online_cpu(cpu) अणु
		that = *per_cpu_ptr(uncores, cpu);

		अगर (!that)
			जारी;

		अगर (this == that)
			जारी;

		अगर (this->id == that->id) अणु
			hlist_add_head(&this->node, &uncore_unused_list);
			this = that;
			अवरोध;
		पूर्ण
	पूर्ण

	this->refcnt++;
	वापस this;
पूर्ण

अटल पूर्णांक amd_uncore_cpu_starting(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक eax, ebx, ecx, edx;
	काष्ठा amd_uncore *uncore;

	अगर (amd_uncore_nb) अणु
		uncore = *per_cpu_ptr(amd_uncore_nb, cpu);
		cpuid(0x8000001e, &eax, &ebx, &ecx, &edx);
		uncore->id = ecx & 0xff;

		uncore = amd_uncore_find_online_sibling(uncore, amd_uncore_nb);
		*per_cpu_ptr(amd_uncore_nb, cpu) = uncore;
	पूर्ण

	अगर (amd_uncore_llc) अणु
		uncore = *per_cpu_ptr(amd_uncore_llc, cpu);
		uncore->id = per_cpu(cpu_llc_id, cpu);

		uncore = amd_uncore_find_online_sibling(uncore, amd_uncore_llc);
		*per_cpu_ptr(amd_uncore_llc, cpu) = uncore;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम uncore_clean_online(व्योम)
अणु
	काष्ठा amd_uncore *uncore;
	काष्ठा hlist_node *n;

	hlist_क्रम_each_entry_safe(uncore, n, &uncore_unused_list, node) अणु
		hlist_del(&uncore->node);
		kमुक्त(uncore);
	पूर्ण
पूर्ण

अटल व्योम uncore_online(अचिन्हित पूर्णांक cpu,
			  काष्ठा amd_uncore * __percpu *uncores)
अणु
	काष्ठा amd_uncore *uncore = *per_cpu_ptr(uncores, cpu);

	uncore_clean_online();

	अगर (cpu == uncore->cpu)
		cpumask_set_cpu(cpu, uncore->active_mask);
पूर्ण

अटल पूर्णांक amd_uncore_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	अगर (amd_uncore_nb)
		uncore_online(cpu, amd_uncore_nb);

	अगर (amd_uncore_llc)
		uncore_online(cpu, amd_uncore_llc);

	वापस 0;
पूर्ण

अटल व्योम uncore_करोwn_prepare(अचिन्हित पूर्णांक cpu,
				काष्ठा amd_uncore * __percpu *uncores)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा amd_uncore *this = *per_cpu_ptr(uncores, cpu);

	अगर (this->cpu != cpu)
		वापस;

	/* this cpu is going करोwn, migrate to a shared sibling अगर possible */
	क्रम_each_online_cpu(i) अणु
		काष्ठा amd_uncore *that = *per_cpu_ptr(uncores, i);

		अगर (cpu == i)
			जारी;

		अगर (this == that) अणु
			perf_pmu_migrate_context(this->pmu, cpu, i);
			cpumask_clear_cpu(cpu, that->active_mask);
			cpumask_set_cpu(i, that->active_mask);
			that->cpu = i;
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक amd_uncore_cpu_करोwn_prepare(अचिन्हित पूर्णांक cpu)
अणु
	अगर (amd_uncore_nb)
		uncore_करोwn_prepare(cpu, amd_uncore_nb);

	अगर (amd_uncore_llc)
		uncore_करोwn_prepare(cpu, amd_uncore_llc);

	वापस 0;
पूर्ण

अटल व्योम uncore_dead(अचिन्हित पूर्णांक cpu, काष्ठा amd_uncore * __percpu *uncores)
अणु
	काष्ठा amd_uncore *uncore = *per_cpu_ptr(uncores, cpu);

	अगर (cpu == uncore->cpu)
		cpumask_clear_cpu(cpu, uncore->active_mask);

	अगर (!--uncore->refcnt)
		kमुक्त(uncore);
	*per_cpu_ptr(uncores, cpu) = शून्य;
पूर्ण

अटल पूर्णांक amd_uncore_cpu_dead(अचिन्हित पूर्णांक cpu)
अणु
	अगर (amd_uncore_nb)
		uncore_dead(cpu, amd_uncore_nb);

	अगर (amd_uncore_llc)
		uncore_dead(cpu, amd_uncore_llc);

	वापस 0;
पूर्ण

अटल पूर्णांक __init amd_uncore_init(व्योम)
अणु
	काष्ठा attribute **df_attr = amd_uncore_df_क्रमmat_attr;
	काष्ठा attribute **l3_attr = amd_uncore_l3_क्रमmat_attr;
	पूर्णांक ret = -ENODEV;

	अगर (boot_cpu_data.x86_venकरोr != X86_VENDOR_AMD &&
	    boot_cpu_data.x86_venकरोr != X86_VENDOR_HYGON)
		वापस -ENODEV;

	अगर (!boot_cpu_has(X86_FEATURE_TOPOEXT))
		वापस -ENODEV;

	num_counters_nb	= NUM_COUNTERS_NB;
	num_counters_llc = NUM_COUNTERS_L2;
	अगर (boot_cpu_data.x86 >= 0x17) अणु
		/*
		 * For F17h and above, the Northbridge counters are
		 * repurposed as Data Fabric counters. Also, L3
		 * counters are supported too. The PMUs are exported
		 * based on family as either L2 or L3 and NB or DF.
		 */
		num_counters_llc	  = NUM_COUNTERS_L3;
		amd_nb_pmu.name		  = "amd_df";
		amd_llc_pmu.name	  = "amd_l3";
		l3_mask			  = true;
	पूर्ण

	अगर (boot_cpu_has(X86_FEATURE_PERFCTR_NB)) अणु
		अगर (boot_cpu_data.x86 >= 0x17)
			*df_attr = &क्रमmat_attr_event14.attr;

		amd_uncore_nb = alloc_percpu(काष्ठा amd_uncore *);
		अगर (!amd_uncore_nb) अणु
			ret = -ENOMEM;
			जाओ fail_nb;
		पूर्ण
		ret = perf_pmu_रेजिस्टर(&amd_nb_pmu, amd_nb_pmu.name, -1);
		अगर (ret)
			जाओ fail_nb;

		pr_info("%d %s %s counters detected\n", num_counters_nb,
			boot_cpu_data.x86_venकरोr == X86_VENDOR_HYGON ?  "HYGON" : "",
			amd_nb_pmu.name);

		ret = 0;
	पूर्ण

	अगर (boot_cpu_has(X86_FEATURE_PERFCTR_LLC)) अणु
		अगर (boot_cpu_data.x86 >= 0x19) अणु
			*l3_attr++ = &क्रमmat_attr_event8.attr;
			*l3_attr++ = &क्रमmat_attr_umask.attr;
			*l3_attr++ = &क्रमmat_attr_coreid.attr;
			*l3_attr++ = &क्रमmat_attr_enallslices.attr;
			*l3_attr++ = &क्रमmat_attr_enallcores.attr;
			*l3_attr++ = &क्रमmat_attr_sliceid.attr;
			*l3_attr++ = &क्रमmat_attr_thपढ़ोmask2.attr;
		पूर्ण अन्यथा अगर (boot_cpu_data.x86 >= 0x17) अणु
			*l3_attr++ = &क्रमmat_attr_event8.attr;
			*l3_attr++ = &क्रमmat_attr_umask.attr;
			*l3_attr++ = &क्रमmat_attr_slicemask.attr;
			*l3_attr++ = &क्रमmat_attr_thपढ़ोmask8.attr;
		पूर्ण

		amd_uncore_llc = alloc_percpu(काष्ठा amd_uncore *);
		अगर (!amd_uncore_llc) अणु
			ret = -ENOMEM;
			जाओ fail_llc;
		पूर्ण
		ret = perf_pmu_रेजिस्टर(&amd_llc_pmu, amd_llc_pmu.name, -1);
		अगर (ret)
			जाओ fail_llc;

		pr_info("%d %s %s counters detected\n", num_counters_llc,
			boot_cpu_data.x86_venकरोr == X86_VENDOR_HYGON ?  "HYGON" : "",
			amd_llc_pmu.name);
		ret = 0;
	पूर्ण

	/*
	 * Install callbacks. Core will call them क्रम each online cpu.
	 */
	अगर (cpuhp_setup_state(CPUHP_PERF_X86_AMD_UNCORE_PREP,
			      "perf/x86/amd/uncore:prepare",
			      amd_uncore_cpu_up_prepare, amd_uncore_cpu_dead))
		जाओ fail_llc;

	अगर (cpuhp_setup_state(CPUHP_AP_PERF_X86_AMD_UNCORE_STARTING,
			      "perf/x86/amd/uncore:starting",
			      amd_uncore_cpu_starting, शून्य))
		जाओ fail_prep;
	अगर (cpuhp_setup_state(CPUHP_AP_PERF_X86_AMD_UNCORE_ONLINE,
			      "perf/x86/amd/uncore:online",
			      amd_uncore_cpu_online,
			      amd_uncore_cpu_करोwn_prepare))
		जाओ fail_start;
	वापस 0;

fail_start:
	cpuhp_हटाओ_state(CPUHP_AP_PERF_X86_AMD_UNCORE_STARTING);
fail_prep:
	cpuhp_हटाओ_state(CPUHP_PERF_X86_AMD_UNCORE_PREP);
fail_llc:
	अगर (boot_cpu_has(X86_FEATURE_PERFCTR_NB))
		perf_pmu_unरेजिस्टर(&amd_nb_pmu);
	अगर (amd_uncore_llc)
		मुक्त_percpu(amd_uncore_llc);
fail_nb:
	अगर (amd_uncore_nb)
		मुक्त_percpu(amd_uncore_nb);

	वापस ret;
पूर्ण
device_initcall(amd_uncore_init);
