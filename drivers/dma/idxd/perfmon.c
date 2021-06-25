<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2020 Intel Corporation. All rights rsvd. */

#समावेश <linux/sched/task.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश "idxd.h"
#समावेश "perfmon.h"

अटल sमाप_प्रकार cpumask_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf);

अटल cpumask_t		perfmon_dsa_cpu_mask;
अटल bool			cpuhp_set_up;
अटल क्रमागत cpuhp_state		cpuhp_slot;

/*
 * perf userspace पढ़ोs this attribute to determine which cpus to खोलो
 * counters on.  It's connected to perfmon_dsa_cpu_mask, which is
 * मुख्यtained by the cpu hotplug handlers.
 */
अटल DEVICE_ATTR_RO(cpumask);

अटल काष्ठा attribute *perfmon_cpumask_attrs[] = अणु
	&dev_attr_cpumask.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group cpumask_attr_group = अणु
	.attrs = perfmon_cpumask_attrs,
पूर्ण;

/*
 * These attributes specअगरy the bits in the config word that the perf
 * syscall uses to pass the event ids and categories to perfmon.
 */
DEFINE_PERFMON_FORMAT_ATTR(event_category, "config:0-3");
DEFINE_PERFMON_FORMAT_ATTR(event, "config:4-31");

/*
 * These attributes specअगरy the bits in the config1 word that the perf
 * syscall uses to pass filter data to perfmon.
 */
DEFINE_PERFMON_FORMAT_ATTR(filter_wq, "config1:0-31");
DEFINE_PERFMON_FORMAT_ATTR(filter_tc, "config1:32-39");
DEFINE_PERFMON_FORMAT_ATTR(filter_pgsz, "config1:40-43");
DEFINE_PERFMON_FORMAT_ATTR(filter_sz, "config1:44-51");
DEFINE_PERFMON_FORMAT_ATTR(filter_eng, "config1:52-59");

#घोषणा PERFMON_FILTERS_START	2
#घोषणा PERFMON_FILTERS_MAX	5

अटल काष्ठा attribute *perfmon_क्रमmat_attrs[] = अणु
	&क्रमmat_attr_idxd_event_category.attr,
	&क्रमmat_attr_idxd_event.attr,
	&क्रमmat_attr_idxd_filter_wq.attr,
	&क्रमmat_attr_idxd_filter_tc.attr,
	&क्रमmat_attr_idxd_filter_pgsz.attr,
	&क्रमmat_attr_idxd_filter_sz.attr,
	&क्रमmat_attr_idxd_filter_eng.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group perfmon_क्रमmat_attr_group = अणु
	.name = "format",
	.attrs = perfmon_क्रमmat_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *perfmon_attr_groups[] = अणु
	&perfmon_क्रमmat_attr_group,
	&cpumask_attr_group,
	शून्य,
पूर्ण;

अटल sमाप_प्रकार cpumask_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			    अक्षर *buf)
अणु
	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, &perfmon_dsa_cpu_mask);
पूर्ण

अटल bool is_idxd_event(काष्ठा idxd_pmu *idxd_pmu, काष्ठा perf_event *event)
अणु
	वापस &idxd_pmu->pmu == event->pmu;
पूर्ण

अटल पूर्णांक perfmon_collect_events(काष्ठा idxd_pmu *idxd_pmu,
				  काष्ठा perf_event *leader,
				  bool करो_grp)
अणु
	काष्ठा perf_event *event;
	पूर्णांक n, max_count;

	max_count = idxd_pmu->n_counters;
	n = idxd_pmu->n_events;

	अगर (n >= max_count)
		वापस -EINVAL;

	अगर (is_idxd_event(idxd_pmu, leader)) अणु
		idxd_pmu->event_list[n] = leader;
		idxd_pmu->event_list[n]->hw.idx = n;
		n++;
	पूर्ण

	अगर (!करो_grp)
		वापस n;

	क्रम_each_sibling_event(event, leader) अणु
		अगर (!is_idxd_event(idxd_pmu, event) ||
		    event->state <= PERF_EVENT_STATE_OFF)
			जारी;

		अगर (n >= max_count)
			वापस -EINVAL;

		idxd_pmu->event_list[n] = event;
		idxd_pmu->event_list[n]->hw.idx = n;
		n++;
	पूर्ण

	वापस n;
पूर्ण

अटल व्योम perfmon_assign_hw_event(काष्ठा idxd_pmu *idxd_pmu,
				    काष्ठा perf_event *event, पूर्णांक idx)
अणु
	काष्ठा idxd_device *idxd = idxd_pmu->idxd;
	काष्ठा hw_perf_event *hwc = &event->hw;

	hwc->idx = idx;
	hwc->config_base = ioपढ़ो64(CNTRCFG_REG(idxd, idx));
	hwc->event_base = ioपढ़ो64(CNTRCFG_REG(idxd, idx));
पूर्ण

अटल पूर्णांक perfmon_assign_event(काष्ठा idxd_pmu *idxd_pmu,
				काष्ठा perf_event *event)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < IDXD_PMU_EVENT_MAX; i++)
		अगर (!test_and_set_bit(i, idxd_pmu->used_mask))
			वापस i;

	वापस -EINVAL;
पूर्ण

/*
 * Check whether there are enough counters to satisfy that all the
 * events in the group can actually be scheduled at the same समय.
 *
 * To करो this, create a fake idxd_pmu object so the event collection
 * and assignment functions can be used without affecting the पूर्णांकernal
 * state of the real idxd_pmu object.
 */
अटल पूर्णांक perfmon_validate_group(काष्ठा idxd_pmu *pmu,
				  काष्ठा perf_event *event)
अणु
	काष्ठा perf_event *leader = event->group_leader;
	काष्ठा idxd_pmu *fake_pmu;
	पूर्णांक i, ret = 0, n, idx;

	fake_pmu = kzalloc(माप(*fake_pmu), GFP_KERNEL);
	अगर (!fake_pmu)
		वापस -ENOMEM;

	fake_pmu->pmu.name = pmu->pmu.name;
	fake_pmu->n_counters = pmu->n_counters;

	n = perfmon_collect_events(fake_pmu, leader, true);
	अगर (n < 0) अणु
		ret = n;
		जाओ out;
	पूर्ण

	fake_pmu->n_events = n;
	n = perfmon_collect_events(fake_pmu, event, false);
	अगर (n < 0) अणु
		ret = n;
		जाओ out;
	पूर्ण

	fake_pmu->n_events = n;

	क्रम (i = 0; i < n; i++) अणु
		event = fake_pmu->event_list[i];

		idx = perfmon_assign_event(fake_pmu, event);
		अगर (idx < 0) अणु
			ret = idx;
			जाओ out;
		पूर्ण
	पूर्ण
out:
	kमुक्त(fake_pmu);

	वापस ret;
पूर्ण

अटल पूर्णांक perfmon_pmu_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा idxd_device *idxd;
	पूर्णांक ret = 0;

	idxd = event_to_idxd(event);
	event->hw.idx = -1;

	अगर (event->attr.type != event->pmu->type)
		वापस -ENOENT;

	/* sampling not supported */
	अगर (event->attr.sample_period)
		वापस -EINVAL;

	अगर (event->cpu < 0)
		वापस -EINVAL;

	अगर (event->pmu != &idxd->idxd_pmu->pmu)
		वापस -EINVAL;

	event->hw.event_base = ioपढ़ो64(PERFMON_TABLE_OFFSET(idxd));
	event->cpu = idxd->idxd_pmu->cpu;
	event->hw.config = event->attr.config;

	अगर (event->group_leader != event)
		 /* non-group events have themselves as leader */
		ret = perfmon_validate_group(idxd->idxd_pmu, event);

	वापस ret;
पूर्ण

अटल अंतरभूत u64 perfmon_pmu_पढ़ो_counter(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा idxd_device *idxd;
	पूर्णांक cntr = hwc->idx;

	idxd = event_to_idxd(event);

	वापस ioपढ़ो64(CNTRDATA_REG(idxd, cntr));
पूर्ण

अटल व्योम perfmon_pmu_event_update(काष्ठा perf_event *event)
अणु
	काष्ठा idxd_device *idxd = event_to_idxd(event);
	u64 prev_raw_count, new_raw_count, delta, p, n;
	पूर्णांक shअगरt = 64 - idxd->idxd_pmu->counter_width;
	काष्ठा hw_perf_event *hwc = &event->hw;

	करो अणु
		prev_raw_count = local64_पढ़ो(&hwc->prev_count);
		new_raw_count = perfmon_pmu_पढ़ो_counter(event);
	पूर्ण जबतक (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
			new_raw_count) != prev_raw_count);

	n = (new_raw_count << shअगरt);
	p = (prev_raw_count << shअगरt);

	delta = ((n - p) >> shअगरt);

	local64_add(delta, &event->count);
पूर्ण

व्योम perfmon_counter_overflow(काष्ठा idxd_device *idxd)
अणु
	पूर्णांक i, n_counters, max_loop = OVERFLOW_SIZE;
	काष्ठा perf_event *event;
	अचिन्हित दीर्घ ovख_स्थितिus;

	n_counters = min(idxd->idxd_pmu->n_counters, OVERFLOW_SIZE);

	ovख_स्थितिus = ioपढ़ो32(OVFSTATUS_REG(idxd));

	/*
	 * While updating overflowed counters, other counters behind
	 * them could overflow and be missed in a given pass.
	 * Normally this could happen at most n_counters बार, but in
	 * theory a tiny counter width could result in continual
	 * overflows and endless looping.  max_loop provides a
	 * failsafe in that highly unlikely हाल.
	 */
	जबतक (ovख_स्थितिus && max_loop--) अणु
		/* Figure out which counter(s) overflowed */
		क्रम_each_set_bit(i, &ovख_स्थितिus, n_counters) अणु
			अचिन्हित दीर्घ ovख_स्थितिus_clear = 0;

			/* Update event->count क्रम overflowed counter */
			event = idxd->idxd_pmu->event_list[i];
			perfmon_pmu_event_update(event);
			/* Writing 1 to OVFSTATUS bit clears it */
			set_bit(i, &ovख_स्थितिus_clear);
			ioग_लिखो32(ovख_स्थितिus_clear, OVFSTATUS_REG(idxd));
		पूर्ण

		ovख_स्थितिus = ioपढ़ो32(OVFSTATUS_REG(idxd));
	पूर्ण

	/*
	 * Should never happen.  If so, it means a counter(s) looped
	 * around twice जबतक this handler was running.
	 */
	WARN_ON_ONCE(ovख_स्थितिus);
पूर्ण

अटल अंतरभूत व्योम perfmon_reset_config(काष्ठा idxd_device *idxd)
अणु
	ioग_लिखो32(CONFIG_RESET, PERFRST_REG(idxd));
	ioग_लिखो32(0, OVFSTATUS_REG(idxd));
	ioग_लिखो32(0, PERFFRZ_REG(idxd));
पूर्ण

अटल अंतरभूत व्योम perfmon_reset_counters(काष्ठा idxd_device *idxd)
अणु
	ioग_लिखो32(CNTR_RESET, PERFRST_REG(idxd));
पूर्ण

अटल अंतरभूत व्योम perfmon_reset(काष्ठा idxd_device *idxd)
अणु
	perfmon_reset_config(idxd);
	perfmon_reset_counters(idxd);
पूर्ण

अटल व्योम perfmon_pmu_event_start(काष्ठा perf_event *event, पूर्णांक mode)
अणु
	u32 flt_wq, flt_tc, flt_pg_sz, flt_xfer_sz, flt_eng = 0;
	u64 cntr_cfg, cntrdata, event_enc, event_cat = 0;
	काष्ठा hw_perf_event *hwc = &event->hw;
	जोड़ filter_cfg flt_cfg;
	जोड़ event_cfg event_cfg;
	काष्ठा idxd_device *idxd;
	पूर्णांक cntr;

	idxd = event_to_idxd(event);

	event->hw.idx = hwc->idx;
	cntr = hwc->idx;

	/* Obtain event category and event value from user space */
	event_cfg.val = event->attr.config;
	flt_cfg.val = event->attr.config1;
	event_cat = event_cfg.event_cat;
	event_enc = event_cfg.event_enc;

	/* Obtain filter configuration from user space */
	flt_wq = flt_cfg.wq;
	flt_tc = flt_cfg.tc;
	flt_pg_sz = flt_cfg.pg_sz;
	flt_xfer_sz = flt_cfg.xfer_sz;
	flt_eng = flt_cfg.eng;

	अगर (flt_wq && test_bit(FLT_WQ, &idxd->idxd_pmu->supported_filters))
		ioग_लिखो32(flt_wq, FLTCFG_REG(idxd, cntr, FLT_WQ));
	अगर (flt_tc && test_bit(FLT_TC, &idxd->idxd_pmu->supported_filters))
		ioग_लिखो32(flt_tc, FLTCFG_REG(idxd, cntr, FLT_TC));
	अगर (flt_pg_sz && test_bit(FLT_PG_SZ, &idxd->idxd_pmu->supported_filters))
		ioग_लिखो32(flt_pg_sz, FLTCFG_REG(idxd, cntr, FLT_PG_SZ));
	अगर (flt_xfer_sz && test_bit(FLT_XFER_SZ, &idxd->idxd_pmu->supported_filters))
		ioग_लिखो32(flt_xfer_sz, FLTCFG_REG(idxd, cntr, FLT_XFER_SZ));
	अगर (flt_eng && test_bit(FLT_ENG, &idxd->idxd_pmu->supported_filters))
		ioग_लिखो32(flt_eng, FLTCFG_REG(idxd, cntr, FLT_ENG));

	/* Read the start value */
	cntrdata = ioपढ़ो64(CNTRDATA_REG(idxd, cntr));
	local64_set(&event->hw.prev_count, cntrdata);

	/* Set counter to event/category */
	cntr_cfg = event_cat << CNTRCFG_CATEGORY_SHIFT;
	cntr_cfg |= event_enc << CNTRCFG_EVENT_SHIFT;
	/* Set पूर्णांकerrupt on overflow and counter enable bits */
	cntr_cfg |= (CNTRCFG_IRQ_OVERFLOW | CNTRCFG_ENABLE);

	ioग_लिखो64(cntr_cfg, CNTRCFG_REG(idxd, cntr));
पूर्ण

अटल व्योम perfmon_pmu_event_stop(काष्ठा perf_event *event, पूर्णांक mode)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा idxd_device *idxd;
	पूर्णांक i, cntr = hwc->idx;
	u64 cntr_cfg;

	idxd = event_to_idxd(event);

	/* हटाओ this event from event list */
	क्रम (i = 0; i < idxd->idxd_pmu->n_events; i++) अणु
		अगर (event != idxd->idxd_pmu->event_list[i])
			जारी;

		क्रम (++i; i < idxd->idxd_pmu->n_events; i++)
			idxd->idxd_pmu->event_list[i - 1] = idxd->idxd_pmu->event_list[i];
		--idxd->idxd_pmu->n_events;
		अवरोध;
	पूर्ण

	cntr_cfg = ioपढ़ो64(CNTRCFG_REG(idxd, cntr));
	cntr_cfg &= ~CNTRCFG_ENABLE;
	ioग_लिखो64(cntr_cfg, CNTRCFG_REG(idxd, cntr));

	अगर (mode == PERF_EF_UPDATE)
		perfmon_pmu_event_update(event);

	event->hw.idx = -1;
	clear_bit(cntr, idxd->idxd_pmu->used_mask);
पूर्ण

अटल व्योम perfmon_pmu_event_del(काष्ठा perf_event *event, पूर्णांक mode)
अणु
	perfmon_pmu_event_stop(event, PERF_EF_UPDATE);
पूर्ण

अटल पूर्णांक perfmon_pmu_event_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा idxd_device *idxd = event_to_idxd(event);
	काष्ठा idxd_pmu *idxd_pmu = idxd->idxd_pmu;
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx, n;

	n = perfmon_collect_events(idxd_pmu, event, false);
	अगर (n < 0)
		वापस n;

	hwc->state = PERF_HES_UPTODATE | PERF_HES_STOPPED;
	अगर (!(flags & PERF_EF_START))
		hwc->state |= PERF_HES_ARCH;

	idx = perfmon_assign_event(idxd_pmu, event);
	अगर (idx < 0)
		वापस idx;

	perfmon_assign_hw_event(idxd_pmu, event, idx);

	अगर (flags & PERF_EF_START)
		perfmon_pmu_event_start(event, 0);

	idxd_pmu->n_events = n;

	वापस 0;
पूर्ण

अटल व्योम enable_perfmon_pmu(काष्ठा idxd_device *idxd)
अणु
	ioग_लिखो32(COUNTER_UNFREEZE, PERFFRZ_REG(idxd));
पूर्ण

अटल व्योम disable_perfmon_pmu(काष्ठा idxd_device *idxd)
अणु
	ioग_लिखो32(COUNTER_FREEZE, PERFFRZ_REG(idxd));
पूर्ण

अटल व्योम perfmon_pmu_enable(काष्ठा pmu *pmu)
अणु
	काष्ठा idxd_device *idxd = pmu_to_idxd(pmu);

	enable_perfmon_pmu(idxd);
पूर्ण

अटल व्योम perfmon_pmu_disable(काष्ठा pmu *pmu)
अणु
	काष्ठा idxd_device *idxd = pmu_to_idxd(pmu);

	disable_perfmon_pmu(idxd);
पूर्ण

अटल व्योम skip_filter(पूर्णांक i)
अणु
	पूर्णांक j;

	क्रम (j = i; j < PERFMON_FILTERS_MAX; j++)
		perfmon_क्रमmat_attrs[PERFMON_FILTERS_START + j] =
			perfmon_क्रमmat_attrs[PERFMON_FILTERS_START + j + 1];
पूर्ण

अटल व्योम idxd_pmu_init(काष्ठा idxd_pmu *idxd_pmu)
अणु
	पूर्णांक i;

	क्रम (i = 0 ; i < PERFMON_FILTERS_MAX; i++) अणु
		अगर (!test_bit(i, &idxd_pmu->supported_filters))
			skip_filter(i);
	पूर्ण

	idxd_pmu->pmu.name		= idxd_pmu->name;
	idxd_pmu->pmu.attr_groups	= perfmon_attr_groups;
	idxd_pmu->pmu.task_ctx_nr	= perf_invalid_context;
	idxd_pmu->pmu.event_init	= perfmon_pmu_event_init;
	idxd_pmu->pmu.pmu_enable	= perfmon_pmu_enable,
	idxd_pmu->pmu.pmu_disable	= perfmon_pmu_disable,
	idxd_pmu->pmu.add		= perfmon_pmu_event_add;
	idxd_pmu->pmu.del		= perfmon_pmu_event_del;
	idxd_pmu->pmu.start		= perfmon_pmu_event_start;
	idxd_pmu->pmu.stop		= perfmon_pmu_event_stop;
	idxd_pmu->pmu.पढ़ो		= perfmon_pmu_event_update;
	idxd_pmu->pmu.capabilities	= PERF_PMU_CAP_NO_EXCLUDE;
	idxd_pmu->pmu.module		= THIS_MODULE;
पूर्ण

व्योम perfmon_pmu_हटाओ(काष्ठा idxd_device *idxd)
अणु
	अगर (!idxd->idxd_pmu)
		वापस;

	cpuhp_state_हटाओ_instance(cpuhp_slot, &idxd->idxd_pmu->cpuhp_node);
	perf_pmu_unरेजिस्टर(&idxd->idxd_pmu->pmu);
	kमुक्त(idxd->idxd_pmu);
	idxd->idxd_pmu = शून्य;
पूर्ण

अटल पूर्णांक perf_event_cpu_online(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा idxd_pmu *idxd_pmu;

	idxd_pmu = hlist_entry_safe(node, typeof(*idxd_pmu), cpuhp_node);

	/* select the first online CPU as the designated पढ़ोer */
	अगर (cpumask_empty(&perfmon_dsa_cpu_mask)) अणु
		cpumask_set_cpu(cpu, &perfmon_dsa_cpu_mask);
		idxd_pmu->cpu = cpu;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक perf_event_cpu_offline(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा idxd_pmu *idxd_pmu;
	अचिन्हित पूर्णांक target;

	idxd_pmu = hlist_entry_safe(node, typeof(*idxd_pmu), cpuhp_node);

	अगर (!cpumask_test_and_clear_cpu(cpu, &perfmon_dsa_cpu_mask))
		वापस 0;

	target = cpumask_any_but(cpu_online_mask, cpu);

	/* migrate events अगर there is a valid target */
	अगर (target < nr_cpu_ids)
		cpumask_set_cpu(target, &perfmon_dsa_cpu_mask);
	अन्यथा
		target = -1;

	perf_pmu_migrate_context(&idxd_pmu->pmu, cpu, target);

	वापस 0;
पूर्ण

पूर्णांक perfmon_pmu_init(काष्ठा idxd_device *idxd)
अणु
	जोड़ idxd_perfcap perfcap;
	काष्ठा idxd_pmu *idxd_pmu;
	पूर्णांक rc = -ENODEV;

	/*
	 * perfmon module initialization failed, nothing to करो
	 */
	अगर (!cpuhp_set_up)
		वापस -ENODEV;

	/*
	 * If perfmon_offset or num_counters is 0, it means perfmon is
	 * not supported on this hardware.
	 */
	अगर (idxd->perfmon_offset == 0)
		वापस -ENODEV;

	idxd_pmu = kzalloc(माप(*idxd_pmu), GFP_KERNEL);
	अगर (!idxd_pmu)
		वापस -ENOMEM;

	idxd_pmu->idxd = idxd;
	idxd->idxd_pmu = idxd_pmu;

	अगर (idxd->data->type == IDXD_TYPE_DSA) अणु
		rc = प्र_लिखो(idxd_pmu->name, "dsa%d", idxd->id);
		अगर (rc < 0)
			जाओ मुक्त;
	पूर्ण अन्यथा अगर (idxd->data->type == IDXD_TYPE_IAX) अणु
		rc = प्र_लिखो(idxd_pmu->name, "iax%d", idxd->id);
		अगर (rc < 0)
			जाओ मुक्त;
	पूर्ण अन्यथा अणु
		जाओ मुक्त;
	पूर्ण

	perfmon_reset(idxd);

	perfcap.bits = ioपढ़ो64(PERFCAP_REG(idxd));

	/*
	 * If total perf counter is 0, stop further registration.
	 * This is necessary in order to support driver running on
	 * guest which करोes not have pmon support.
	 */
	अगर (perfcap.num_perf_counter == 0)
		जाओ मुक्त;

	/* A counter width of 0 means it can't count */
	अगर (perfcap.counter_width == 0)
		जाओ मुक्त;

	/* Overflow पूर्णांकerrupt and counter मुक्तze support must be available */
	अगर (!perfcap.overflow_पूर्णांकerrupt || !perfcap.counter_मुक्तze)
		जाओ मुक्त;

	/* Number of event categories cannot be 0 */
	अगर (perfcap.num_event_category == 0)
		जाओ मुक्त;

	/*
	 * We करोn't support per-counter capabilities क्रम now.
	 */
	अगर (perfcap.cap_per_counter)
		जाओ मुक्त;

	idxd_pmu->n_event_categories = perfcap.num_event_category;
	idxd_pmu->supported_event_categories = perfcap.global_event_category;
	idxd_pmu->per_counter_caps_supported = perfcap.cap_per_counter;

	/* check filter capability.  If 0, then filters are not supported */
	idxd_pmu->supported_filters = perfcap.filter;
	अगर (perfcap.filter)
		idxd_pmu->n_filters = hweight8(perfcap.filter);

	/* Store the total number of counters categories, and counter width */
	idxd_pmu->n_counters = perfcap.num_perf_counter;
	idxd_pmu->counter_width = perfcap.counter_width;

	idxd_pmu_init(idxd_pmu);

	rc = perf_pmu_रेजिस्टर(&idxd_pmu->pmu, idxd_pmu->name, -1);
	अगर (rc)
		जाओ मुक्त;

	rc = cpuhp_state_add_instance(cpuhp_slot, &idxd_pmu->cpuhp_node);
	अगर (rc) अणु
		perf_pmu_unरेजिस्टर(&idxd->idxd_pmu->pmu);
		जाओ मुक्त;
	पूर्ण
out:
	वापस rc;
मुक्त:
	kमुक्त(idxd_pmu);
	idxd->idxd_pmu = शून्य;

	जाओ out;
पूर्ण

व्योम __init perfmon_init(व्योम)
अणु
	पूर्णांक rc = cpuhp_setup_state_multi(CPUHP_AP_ONLINE_DYN,
					 "driver/dma/idxd/perf:online",
					 perf_event_cpu_online,
					 perf_event_cpu_offline);
	अगर (WARN_ON(rc < 0))
		वापस;

	cpuhp_slot = rc;
	cpuhp_set_up = true;
पूर्ण

व्योम __निकास perfmon_निकास(व्योम)
अणु
	अगर (cpuhp_set_up)
		cpuhp_हटाओ_multi_state(cpuhp_slot);
पूर्ण
