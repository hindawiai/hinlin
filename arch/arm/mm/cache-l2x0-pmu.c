<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * L220/L310 cache controller support
 *
 * Copyright (C) 2016 ARM Limited
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/hardware/cache-l2x0.h>

#घोषणा PMU_NR_COUNTERS 2

अटल व्योम __iomem *l2x0_base;
अटल काष्ठा pmu *l2x0_pmu;
अटल cpumask_t pmu_cpu;

अटल स्थिर अक्षर *l2x0_name;

अटल kसमय_प्रकार l2x0_pmu_poll_period;
अटल काष्ठा hrसमयr l2x0_pmu_hrसमयr;

/*
 * The L220/PL310 PMU has two equivalent counters, Counter1 and Counter0.
 * Registers controlling these are laid out in pairs, in descending order, i.e.
 * the रेजिस्टर क्रम Counter1 comes first, followed by the रेजिस्टर क्रम
 * Counter0.
 * We ensure that idx 0 -> Counter0, and idx1 -> Counter1.
 */
अटल काष्ठा perf_event *events[PMU_NR_COUNTERS];

/* Find an unused counter */
अटल पूर्णांक l2x0_pmu_find_idx(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PMU_NR_COUNTERS; i++) अणु
		अगर (!events[i])
			वापस i;
	पूर्ण

	वापस -1;
पूर्ण

/* How many counters are allocated? */
अटल पूर्णांक l2x0_pmu_num_active_counters(व्योम)
अणु
	पूर्णांक i, cnt = 0;

	क्रम (i = 0; i < PMU_NR_COUNTERS; i++) अणु
		अगर (events[i])
			cnt++;
	पूर्ण

	वापस cnt;
पूर्ण

अटल व्योम l2x0_pmu_counter_config_ग_लिखो(पूर्णांक idx, u32 val)
अणु
	ग_लिखोl_relaxed(val, l2x0_base + L2X0_EVENT_CNT0_CFG - 4 * idx);
पूर्ण

अटल u32 l2x0_pmu_counter_पढ़ो(पूर्णांक idx)
अणु
	वापस पढ़ोl_relaxed(l2x0_base + L2X0_EVENT_CNT0_VAL - 4 * idx);
पूर्ण

अटल व्योम l2x0_pmu_counter_ग_लिखो(पूर्णांक idx, u32 val)
अणु
	ग_लिखोl_relaxed(val, l2x0_base + L2X0_EVENT_CNT0_VAL - 4 * idx);
पूर्ण

अटल व्योम __l2x0_pmu_enable(व्योम)
अणु
	u32 val = पढ़ोl_relaxed(l2x0_base + L2X0_EVENT_CNT_CTRL);
	val |= L2X0_EVENT_CNT_CTRL_ENABLE;
	ग_लिखोl_relaxed(val, l2x0_base + L2X0_EVENT_CNT_CTRL);
पूर्ण

अटल व्योम __l2x0_pmu_disable(व्योम)
अणु
	u32 val = पढ़ोl_relaxed(l2x0_base + L2X0_EVENT_CNT_CTRL);
	val &= ~L2X0_EVENT_CNT_CTRL_ENABLE;
	ग_लिखोl_relaxed(val, l2x0_base + L2X0_EVENT_CNT_CTRL);
पूर्ण

अटल व्योम l2x0_pmu_enable(काष्ठा pmu *pmu)
अणु
	अगर (l2x0_pmu_num_active_counters() == 0)
		वापस;

	__l2x0_pmu_enable();
पूर्ण

अटल व्योम l2x0_pmu_disable(काष्ठा pmu *pmu)
अणु
	अगर (l2x0_pmu_num_active_counters() == 0)
		वापस;

	__l2x0_pmu_disable();
पूर्ण

अटल व्योम warn_अगर_saturated(u32 count)
अणु
	अगर (count != 0xffffffff)
		वापस;

	pr_warn_ratelimited("L2X0 counter saturated. Poll period too long\n");
पूर्ण

अटल व्योम l2x0_pmu_event_पढ़ो(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hw = &event->hw;
	u64 prev_count, new_count, mask;

	करो अणु
		 prev_count = local64_पढ़ो(&hw->prev_count);
		 new_count = l2x0_pmu_counter_पढ़ो(hw->idx);
	पूर्ण जबतक (local64_xchg(&hw->prev_count, new_count) != prev_count);

	mask = GENMASK_ULL(31, 0);
	local64_add((new_count - prev_count) & mask, &event->count);

	warn_अगर_saturated(new_count);
पूर्ण

अटल व्योम l2x0_pmu_event_configure(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hw = &event->hw;

	/*
	 * The L2X0 counters saturate at 0xffffffff rather than wrapping, so we
	 * will *always* lose some number of events when a counter saturates,
	 * and have no way of detecting how many were lost.
	 *
	 * To minimize the impact of this, we try to maximize the period by
	 * always starting counters at zero. To ensure that group ratios are
	 * representative, we poll periodically to aव्योम counters saturating.
	 * See l2x0_pmu_poll().
	 */
	local64_set(&hw->prev_count, 0);
	l2x0_pmu_counter_ग_लिखो(hw->idx, 0);
पूर्ण

अटल क्रमागत hrसमयr_restart l2x0_pmu_poll(काष्ठा hrसमयr *hrसमयr)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	local_irq_save(flags);
	__l2x0_pmu_disable();

	क्रम (i = 0; i < PMU_NR_COUNTERS; i++) अणु
		काष्ठा perf_event *event = events[i];

		अगर (!event)
			जारी;

		l2x0_pmu_event_पढ़ो(event);
		l2x0_pmu_event_configure(event);
	पूर्ण

	__l2x0_pmu_enable();
	local_irq_restore(flags);

	hrसमयr_क्रमward_now(hrसमयr, l2x0_pmu_poll_period);
	वापस HRTIMER_RESTART;
पूर्ण


अटल व्योम __l2x0_pmu_event_enable(पूर्णांक idx, u32 event)
अणु
	u32 val;

	val = event << L2X0_EVENT_CNT_CFG_SRC_SHIFT;
	val |= L2X0_EVENT_CNT_CFG_INT_DISABLED;
	l2x0_pmu_counter_config_ग_लिखो(idx, val);
पूर्ण

अटल व्योम l2x0_pmu_event_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hw = &event->hw;

	अगर (WARN_ON_ONCE(!(event->hw.state & PERF_HES_STOPPED)))
		वापस;

	अगर (flags & PERF_EF_RELOAD) अणु
		WARN_ON_ONCE(!(hw->state & PERF_HES_UPTODATE));
		l2x0_pmu_event_configure(event);
	पूर्ण

	hw->state = 0;

	__l2x0_pmu_event_enable(hw->idx, hw->config_base);
पूर्ण

अटल व्योम __l2x0_pmu_event_disable(पूर्णांक idx)
अणु
	u32 val;

	val = L2X0_EVENT_CNT_CFG_SRC_DISABLED << L2X0_EVENT_CNT_CFG_SRC_SHIFT;
	val |= L2X0_EVENT_CNT_CFG_INT_DISABLED;
	l2x0_pmu_counter_config_ग_लिखो(idx, val);
पूर्ण

अटल व्योम l2x0_pmu_event_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hw = &event->hw;

	अगर (WARN_ON_ONCE(event->hw.state & PERF_HES_STOPPED))
		वापस;

	__l2x0_pmu_event_disable(hw->idx);

	hw->state |= PERF_HES_STOPPED;

	अगर (flags & PERF_EF_UPDATE) अणु
		l2x0_pmu_event_पढ़ो(event);
		hw->state |= PERF_HES_UPTODATE;
	पूर्ण
पूर्ण

अटल पूर्णांक l2x0_pmu_event_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hw = &event->hw;
	पूर्णांक idx = l2x0_pmu_find_idx();

	अगर (idx == -1)
		वापस -EAGAIN;

	/*
	 * Pin the समयr, so that the overflows are handled by the chosen
	 * event->cpu (this is the same one as presented in "cpumask"
	 * attribute).
	 */
	अगर (l2x0_pmu_num_active_counters() == 0)
		hrसमयr_start(&l2x0_pmu_hrसमयr, l2x0_pmu_poll_period,
			      HRTIMER_MODE_REL_PINNED);

	events[idx] = event;
	hw->idx = idx;

	l2x0_pmu_event_configure(event);

	hw->state = PERF_HES_STOPPED | PERF_HES_UPTODATE;

	अगर (flags & PERF_EF_START)
		l2x0_pmu_event_start(event, 0);

	वापस 0;
पूर्ण

अटल व्योम l2x0_pmu_event_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hw = &event->hw;

	l2x0_pmu_event_stop(event, PERF_EF_UPDATE);

	events[hw->idx] = शून्य;
	hw->idx = -1;

	अगर (l2x0_pmu_num_active_counters() == 0)
		hrसमयr_cancel(&l2x0_pmu_hrसमयr);
पूर्ण

अटल bool l2x0_pmu_group_is_valid(काष्ठा perf_event *event)
अणु
	काष्ठा pmu *pmu = event->pmu;
	काष्ठा perf_event *leader = event->group_leader;
	काष्ठा perf_event *sibling;
	पूर्णांक num_hw = 0;

	अगर (leader->pmu == pmu)
		num_hw++;
	अन्यथा अगर (!is_software_event(leader))
		वापस false;

	क्रम_each_sibling_event(sibling, leader) अणु
		अगर (sibling->pmu == pmu)
			num_hw++;
		अन्यथा अगर (!is_software_event(sibling))
			वापस false;
	पूर्ण

	वापस num_hw <= PMU_NR_COUNTERS;
पूर्ण

अटल पूर्णांक l2x0_pmu_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hw = &event->hw;

	अगर (event->attr.type != l2x0_pmu->type)
		वापस -ENOENT;

	अगर (is_sampling_event(event) ||
	    event->attach_state & PERF_ATTACH_TASK)
		वापस -EINVAL;

	अगर (event->cpu < 0)
		वापस -EINVAL;

	अगर (event->attr.config & ~L2X0_EVENT_CNT_CFG_SRC_MASK)
		वापस -EINVAL;

	hw->config_base = event->attr.config;

	अगर (!l2x0_pmu_group_is_valid(event))
		वापस -EINVAL;

	event->cpu = cpumask_first(&pmu_cpu);

	वापस 0;
पूर्ण

काष्ठा l2x0_event_attribute अणु
	काष्ठा device_attribute attr;
	अचिन्हित पूर्णांक config;
	bool pl310_only;
पूर्ण;

#घोषणा L2X0_EVENT_ATTR(_name, _config, _pl310_only)				\
	(&((काष्ठा l2x0_event_attribute[]) अणुअणु					\
		.attr = __ATTR(_name, S_IRUGO, l2x0_pmu_event_show, शून्य),	\
		.config = _config,						\
		.pl310_only = _pl310_only,					\
	पूर्णपूर्ण)[0].attr.attr)

#घोषणा L220_PLUS_EVENT_ATTR(_name, _config)					\
	L2X0_EVENT_ATTR(_name, _config, false)

#घोषणा PL310_EVENT_ATTR(_name, _config)					\
	L2X0_EVENT_ATTR(_name, _config, true)

अटल sमाप_प्रकार l2x0_pmu_event_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा l2x0_event_attribute *lattr;

	lattr = container_of(attr, typeof(*lattr), attr);
	वापस snम_लिखो(buf, PAGE_SIZE, "config=0x%x\n", lattr->config);
पूर्ण

अटल umode_t l2x0_pmu_event_attr_is_visible(काष्ठा kobject *kobj,
					      काष्ठा attribute *attr,
					      पूर्णांक unused)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा pmu *pmu = dev_get_drvdata(dev);
	काष्ठा l2x0_event_attribute *lattr;

	lattr = container_of(attr, typeof(*lattr), attr.attr);

	अगर (!lattr->pl310_only || म_भेद("l2c_310", pmu->name) == 0)
		वापस attr->mode;

	वापस 0;
पूर्ण

अटल काष्ठा attribute *l2x0_pmu_event_attrs[] = अणु
	L220_PLUS_EVENT_ATTR(co,	0x1),
	L220_PLUS_EVENT_ATTR(drhit,	0x2),
	L220_PLUS_EVENT_ATTR(drreq,	0x3),
	L220_PLUS_EVENT_ATTR(dwhit,	0x4),
	L220_PLUS_EVENT_ATTR(dwreq,	0x5),
	L220_PLUS_EVENT_ATTR(dwtreq,	0x6),
	L220_PLUS_EVENT_ATTR(irhit,	0x7),
	L220_PLUS_EVENT_ATTR(irreq,	0x8),
	L220_PLUS_EVENT_ATTR(wa,	0x9),
	PL310_EVENT_ATTR(ipfalloc,	0xa),
	PL310_EVENT_ATTR(epfhit,	0xb),
	PL310_EVENT_ATTR(epfalloc,	0xc),
	PL310_EVENT_ATTR(srrcvd,	0xd),
	PL310_EVENT_ATTR(srconf,	0xe),
	PL310_EVENT_ATTR(epfrcvd,	0xf),
	शून्य
पूर्ण;

अटल काष्ठा attribute_group l2x0_pmu_event_attrs_group = अणु
	.name = "events",
	.attrs = l2x0_pmu_event_attrs,
	.is_visible = l2x0_pmu_event_attr_is_visible,
पूर्ण;

अटल sमाप_प्रकार l2x0_pmu_cpumask_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस cpumap_prपूर्णांक_to_pagebuf(true, buf, &pmu_cpu);
पूर्ण

अटल काष्ठा device_attribute l2x0_pmu_cpumask_attr =
		__ATTR(cpumask, S_IRUGO, l2x0_pmu_cpumask_show, शून्य);

अटल काष्ठा attribute *l2x0_pmu_cpumask_attrs[] = अणु
	&l2x0_pmu_cpumask_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group l2x0_pmu_cpumask_attr_group = अणु
	.attrs = l2x0_pmu_cpumask_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *l2x0_pmu_attr_groups[] = अणु
	&l2x0_pmu_event_attrs_group,
	&l2x0_pmu_cpumask_attr_group,
	शून्य,
पूर्ण;

अटल व्योम l2x0_pmu_reset(व्योम)
अणु
	पूर्णांक i;

	__l2x0_pmu_disable();

	क्रम (i = 0; i < PMU_NR_COUNTERS; i++)
		__l2x0_pmu_event_disable(i);
पूर्ण

अटल पूर्णांक l2x0_pmu_offline_cpu(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक target;

	अगर (!cpumask_test_and_clear_cpu(cpu, &pmu_cpu))
		वापस 0;

	target = cpumask_any_but(cpu_online_mask, cpu);
	अगर (target >= nr_cpu_ids)
		वापस 0;

	perf_pmu_migrate_context(l2x0_pmu, cpu, target);
	cpumask_set_cpu(target, &pmu_cpu);

	वापस 0;
पूर्ण

व्योम l2x0_pmu_suspend(व्योम)
अणु
	पूर्णांक i;

	अगर (!l2x0_pmu)
		वापस;

	l2x0_pmu_disable(l2x0_pmu);

	क्रम (i = 0; i < PMU_NR_COUNTERS; i++) अणु
		अगर (events[i])
			l2x0_pmu_event_stop(events[i], PERF_EF_UPDATE);
	पूर्ण

पूर्ण

व्योम l2x0_pmu_resume(व्योम)
अणु
	पूर्णांक i;

	अगर (!l2x0_pmu)
		वापस;

	l2x0_pmu_reset();

	क्रम (i = 0; i < PMU_NR_COUNTERS; i++) अणु
		अगर (events[i])
			l2x0_pmu_event_start(events[i], PERF_EF_RELOAD);
	पूर्ण

	l2x0_pmu_enable(l2x0_pmu);
पूर्ण

व्योम __init l2x0_pmu_रेजिस्टर(व्योम __iomem *base, u32 part)
अणु
	/*
	 * Determine whether we support the PMU, and choose the name क्रम sysfs.
	 * This is also used by l2x0_pmu_event_attr_is_visible to determine
	 * which events to display, as the PL310 PMU supports a superset of
	 * L220 events.
	 *
	 * The L210 PMU has a dअगरferent programmer's पूर्णांकerface, and is not
	 * supported by this driver.
	 *
	 * We must defer रेजिस्टरing the PMU until the perf subप्रणाली is up and
	 * running, so just stash the name and base, and leave that to another
	 * initcall.
	 */
	चयन (part & L2X0_CACHE_ID_PART_MASK) अणु
	हाल L2X0_CACHE_ID_PART_L220:
		l2x0_name = "l2c_220";
		अवरोध;
	हाल L2X0_CACHE_ID_PART_L310:
		l2x0_name = "l2c_310";
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	l2x0_base = base;
पूर्ण

अटल __init पूर्णांक l2x0_pmu_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!l2x0_base)
		वापस 0;

	l2x0_pmu = kzalloc(माप(*l2x0_pmu), GFP_KERNEL);
	अगर (!l2x0_pmu) अणु
		pr_warn("Unable to allocate L2x0 PMU\n");
		वापस -ENOMEM;
	पूर्ण

	*l2x0_pmu = (काष्ठा pmu) अणु
		.task_ctx_nr = perf_invalid_context,
		.pmu_enable = l2x0_pmu_enable,
		.pmu_disable = l2x0_pmu_disable,
		.पढ़ो = l2x0_pmu_event_पढ़ो,
		.start = l2x0_pmu_event_start,
		.stop = l2x0_pmu_event_stop,
		.add = l2x0_pmu_event_add,
		.del = l2x0_pmu_event_del,
		.event_init = l2x0_pmu_event_init,
		.attr_groups = l2x0_pmu_attr_groups,
		.capabilities = PERF_PMU_CAP_NO_EXCLUDE,
	पूर्ण;

	l2x0_pmu_reset();

	/*
	 * We always use a hrसमयr rather than an पूर्णांकerrupt.
	 * See comments in l2x0_pmu_event_configure and l2x0_pmu_poll.
	 *
	 * Polling once a second allows the counters to fill up to 1/128th on a
	 * quad-core test chip with cores घड़ीed at 400MHz. Hopefully this
	 * leaves sufficient headroom to aव्योम overflow on production silicon
	 * at higher frequencies.
	 */
	l2x0_pmu_poll_period = ms_to_kसमय(1000);
	hrसमयr_init(&l2x0_pmu_hrसमयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	l2x0_pmu_hrसमयr.function = l2x0_pmu_poll;

	cpumask_set_cpu(0, &pmu_cpu);
	ret = cpuhp_setup_state_nocalls(CPUHP_AP_PERF_ARM_L2X0_ONLINE,
					"perf/arm/l2x0:online", शून्य,
					l2x0_pmu_offline_cpu);
	अगर (ret)
		जाओ out_pmu;

	ret = perf_pmu_रेजिस्टर(l2x0_pmu, l2x0_name, -1);
	अगर (ret)
		जाओ out_cpuhp;

	वापस 0;

out_cpuhp:
	cpuhp_हटाओ_state_nocalls(CPUHP_AP_PERF_ARM_L2X0_ONLINE);
out_pmu:
	kमुक्त(l2x0_pmu);
	l2x0_pmu = शून्य;
	वापस ret;
पूर्ण
device_initcall(l2x0_pmu_init);
