<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Linux perक्रमmance counter support क्रम ARC CPUs.
// This code is inspired by the perf support of various other architectures.
//
// Copyright (C) 2013-2018 Synopsys, Inc. (www.synopsys.com)

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <यंत्र/arcregs.h>
#समावेश <यंत्र/stacktrace.h>

/* HW holds 8 symbols + one क्रम null terminator */
#घोषणा ARCPMU_EVENT_NAME_LEN	9

क्रमागत arc_pmu_attr_groups अणु
	ARCPMU_ATTR_GR_EVENTS,
	ARCPMU_ATTR_GR_FORMATS,
	ARCPMU_NR_ATTR_GR
पूर्ण;

काष्ठा arc_pmu_raw_event_entry अणु
	अक्षर name[ARCPMU_EVENT_NAME_LEN];
पूर्ण;

काष्ठा arc_pmu अणु
	काष्ठा pmu	pmu;
	अचिन्हित पूर्णांक	irq;
	पूर्णांक		n_counters;
	पूर्णांक		n_events;
	u64		max_period;
	पूर्णांक		ev_hw_idx[PERF_COUNT_ARC_HW_MAX];

	काष्ठा arc_pmu_raw_event_entry	*raw_entry;
	काष्ठा attribute		**attrs;
	काष्ठा perf_pmu_events_attr	*attr;
	स्थिर काष्ठा attribute_group	*attr_groups[ARCPMU_NR_ATTR_GR + 1];
पूर्ण;

काष्ठा arc_pmu_cpu अणु
	/*
	 * A 1 bit क्रम an index indicates that the counter is being used क्रम
	 * an event. A 0 means that the counter can be used.
	 */
	अचिन्हित दीर्घ	used_mask[BITS_TO_LONGS(ARC_PERF_MAX_COUNTERS)];

	/*
	 * The events that are active on the PMU क्रम the given index.
	 */
	काष्ठा perf_event *act_counter[ARC_PERF_MAX_COUNTERS];
पूर्ण;

काष्ठा arc_callchain_trace अणु
	पूर्णांक depth;
	व्योम *perf_stuff;
पूर्ण;

अटल पूर्णांक callchain_trace(अचिन्हित पूर्णांक addr, व्योम *data)
अणु
	काष्ठा arc_callchain_trace *ctrl = data;
	काष्ठा perf_callchain_entry_ctx *entry = ctrl->perf_stuff;

	perf_callchain_store(entry, addr);

	अगर (ctrl->depth++ < 3)
		वापस 0;

	वापस -1;
पूर्ण

व्योम perf_callchain_kernel(काष्ठा perf_callchain_entry_ctx *entry,
			   काष्ठा pt_regs *regs)
अणु
	काष्ठा arc_callchain_trace ctrl = अणु
		.depth = 0,
		.perf_stuff = entry,
	पूर्ण;

	arc_unwind_core(शून्य, regs, callchain_trace, &ctrl);
पूर्ण

व्योम perf_callchain_user(काष्ठा perf_callchain_entry_ctx *entry,
			 काष्ठा pt_regs *regs)
अणु
	/*
	 * User stack can't be unwound trivially with kernel dwarf unwinder
	 * So क्रम now just record the user PC
	 */
	perf_callchain_store(entry, inकाष्ठाion_poपूर्णांकer(regs));
पूर्ण

अटल काष्ठा arc_pmu *arc_pmu;
अटल DEFINE_PER_CPU(काष्ठा arc_pmu_cpu, arc_pmu_cpu);

/* पढ़ो counter #idx; note that counter# != event# on ARC! */
अटल u64 arc_pmu_पढ़ो_counter(पूर्णांक idx)
अणु
	u32 पंचांगp;
	u64 result;

	/*
	 * ARC supports making 'snapshots' of the counters, so we don't
	 * need to care about counters wrapping to 0 underneath our feet
	 */
	ग_लिखो_aux_reg(ARC_REG_PCT_INDEX, idx);
	पंचांगp = पढ़ो_aux_reg(ARC_REG_PCT_CONTROL);
	ग_लिखो_aux_reg(ARC_REG_PCT_CONTROL, पंचांगp | ARC_REG_PCT_CONTROL_SN);
	result = (u64) (पढ़ो_aux_reg(ARC_REG_PCT_SNAPH)) << 32;
	result |= पढ़ो_aux_reg(ARC_REG_PCT_SNAPL);

	वापस result;
पूर्ण

अटल व्योम arc_perf_event_update(काष्ठा perf_event *event,
				  काष्ठा hw_perf_event *hwc, पूर्णांक idx)
अणु
	u64 prev_raw_count = local64_पढ़ो(&hwc->prev_count);
	u64 new_raw_count = arc_pmu_पढ़ो_counter(idx);
	s64 delta = new_raw_count - prev_raw_count;

	/*
	 * We aren't afraid of hwc->prev_count changing beneath our feet
	 * because there's no way क्रम us to re-enter this function anyसमय.
	 */
	local64_set(&hwc->prev_count, new_raw_count);
	local64_add(delta, &event->count);
	local64_sub(delta, &hwc->period_left);
पूर्ण

अटल व्योम arc_pmu_पढ़ो(काष्ठा perf_event *event)
अणु
	arc_perf_event_update(event, &event->hw, event->hw.idx);
पूर्ण

अटल पूर्णांक arc_pmu_cache_event(u64 config)
अणु
	अचिन्हित पूर्णांक cache_type, cache_op, cache_result;
	पूर्णांक ret;

	cache_type	= (config >>  0) & 0xff;
	cache_op	= (config >>  8) & 0xff;
	cache_result	= (config >> 16) & 0xff;
	अगर (cache_type >= PERF_COUNT_HW_CACHE_MAX)
		वापस -EINVAL;
	अगर (cache_op >= PERF_COUNT_HW_CACHE_OP_MAX)
		वापस -EINVAL;
	अगर (cache_result >= PERF_COUNT_HW_CACHE_RESULT_MAX)
		वापस -EINVAL;

	ret = arc_pmu_cache_map[cache_type][cache_op][cache_result];

	अगर (ret == CACHE_OP_UNSUPPORTED)
		वापस -ENOENT;

	pr_debug("init cache event: type/op/result %d/%d/%d with h/w %d \'%s\'\n",
		 cache_type, cache_op, cache_result, ret,
		 arc_pmu_ev_hw_map[ret]);

	वापस ret;
पूर्ण

/* initializes hw_perf_event काष्ठाure अगर event is supported */
अटल पूर्णांक arc_pmu_event_init(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक ret;

	अगर (!is_sampling_event(event)) अणु
		hwc->sample_period = arc_pmu->max_period;
		hwc->last_period = hwc->sample_period;
		local64_set(&hwc->period_left, hwc->sample_period);
	पूर्ण

	hwc->config = 0;

	अगर (is_isa_arcv2()) अणु
		/* "exclude user" means "count only kernel" */
		अगर (event->attr.exclude_user)
			hwc->config |= ARC_REG_PCT_CONFIG_KERN;

		/* "exclude kernel" means "count only user" */
		अगर (event->attr.exclude_kernel)
			hwc->config |= ARC_REG_PCT_CONFIG_USER;
	पूर्ण

	चयन (event->attr.type) अणु
	हाल PERF_TYPE_HARDWARE:
		अगर (event->attr.config >= PERF_COUNT_HW_MAX)
			वापस -ENOENT;
		अगर (arc_pmu->ev_hw_idx[event->attr.config] < 0)
			वापस -ENOENT;
		hwc->config |= arc_pmu->ev_hw_idx[event->attr.config];
		pr_debug("init event %d with h/w %08x \'%s\'\n",
			 (पूर्णांक)event->attr.config, (पूर्णांक)hwc->config,
			 arc_pmu_ev_hw_map[event->attr.config]);
		वापस 0;

	हाल PERF_TYPE_HW_CACHE:
		ret = arc_pmu_cache_event(event->attr.config);
		अगर (ret < 0)
			वापस ret;
		hwc->config |= arc_pmu->ev_hw_idx[ret];
		pr_debug("init cache event with h/w %08x \'%s\'\n",
			 (पूर्णांक)hwc->config, arc_pmu_ev_hw_map[ret]);
		वापस 0;

	हाल PERF_TYPE_RAW:
		अगर (event->attr.config >= arc_pmu->n_events)
			वापस -ENOENT;

		hwc->config |= event->attr.config;
		pr_debug("init raw event with idx %lld \'%s\'\n",
			 event->attr.config,
			 arc_pmu->raw_entry[event->attr.config].name);

		वापस 0;

	शेष:
		वापस -ENOENT;
	पूर्ण
पूर्ण

/* starts all counters */
अटल व्योम arc_pmu_enable(काष्ठा pmu *pmu)
अणु
	u32 पंचांगp;
	पंचांगp = पढ़ो_aux_reg(ARC_REG_PCT_CONTROL);
	ग_लिखो_aux_reg(ARC_REG_PCT_CONTROL, (पंचांगp & 0xffff0000) | 0x1);
पूर्ण

/* stops all counters */
अटल व्योम arc_pmu_disable(काष्ठा pmu *pmu)
अणु
	u32 पंचांगp;
	पंचांगp = पढ़ो_aux_reg(ARC_REG_PCT_CONTROL);
	ग_लिखो_aux_reg(ARC_REG_PCT_CONTROL, (पंचांगp & 0xffff0000) | 0x0);
पूर्ण

अटल पूर्णांक arc_pmu_event_set_period(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	s64 left = local64_पढ़ो(&hwc->period_left);
	s64 period = hwc->sample_period;
	पूर्णांक idx = hwc->idx;
	पूर्णांक overflow = 0;
	u64 value;

	अगर (unlikely(left <= -period)) अणु
		/* left underflowed by more than period. */
		left = period;
		local64_set(&hwc->period_left, left);
		hwc->last_period = period;
		overflow = 1;
	पूर्ण अन्यथा अगर (unlikely(left <= 0)) अणु
		/* left underflowed by less than period. */
		left += period;
		local64_set(&hwc->period_left, left);
		hwc->last_period = period;
		overflow = 1;
	पूर्ण

	अगर (left > arc_pmu->max_period)
		left = arc_pmu->max_period;

	value = arc_pmu->max_period - left;
	local64_set(&hwc->prev_count, value);

	/* Select counter */
	ग_लिखो_aux_reg(ARC_REG_PCT_INDEX, idx);

	/* Write value */
	ग_लिखो_aux_reg(ARC_REG_PCT_COUNTL, lower_32_bits(value));
	ग_लिखो_aux_reg(ARC_REG_PCT_COUNTH, upper_32_bits(value));

	perf_event_update_userpage(event);

	वापस overflow;
पूर्ण

/*
 * Assigns hardware counter to hardware condition.
 * Note that there is no separate start/stop mechanism;
 * stopping is achieved by assigning the 'never' condition
 */
अटल व्योम arc_pmu_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	अगर (WARN_ON_ONCE(idx == -1))
		वापस;

	अगर (flags & PERF_EF_RELOAD)
		WARN_ON_ONCE(!(hwc->state & PERF_HES_UPTODATE));

	hwc->state = 0;

	arc_pmu_event_set_period(event);

	/* Enable पूर्णांकerrupt क्रम this counter */
	अगर (is_sampling_event(event))
		ग_लिखो_aux_reg(ARC_REG_PCT_INT_CTRL,
			      पढ़ो_aux_reg(ARC_REG_PCT_INT_CTRL) | BIT(idx));

	/* enable ARC pmu here */
	ग_लिखो_aux_reg(ARC_REG_PCT_INDEX, idx);		/* counter # */
	ग_लिखो_aux_reg(ARC_REG_PCT_CONFIG, hwc->config);	/* condition */
पूर्ण

अटल व्योम arc_pmu_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	/* Disable पूर्णांकerrupt क्रम this counter */
	अगर (is_sampling_event(event)) अणु
		/*
		 * Reset पूर्णांकerrupt flag by writing of 1. This is required
		 * to make sure pending पूर्णांकerrupt was not left.
		 */
		ग_लिखो_aux_reg(ARC_REG_PCT_INT_ACT, BIT(idx));
		ग_लिखो_aux_reg(ARC_REG_PCT_INT_CTRL,
			      पढ़ो_aux_reg(ARC_REG_PCT_INT_CTRL) & ~BIT(idx));
	पूर्ण

	अगर (!(event->hw.state & PERF_HES_STOPPED)) अणु
		/* stop ARC pmu here */
		ग_लिखो_aux_reg(ARC_REG_PCT_INDEX, idx);

		/* condition code #0 is always "never" */
		ग_लिखो_aux_reg(ARC_REG_PCT_CONFIG, 0);

		event->hw.state |= PERF_HES_STOPPED;
	पूर्ण

	अगर ((flags & PERF_EF_UPDATE) &&
	    !(event->hw.state & PERF_HES_UPTODATE)) अणु
		arc_perf_event_update(event, &event->hw, idx);
		event->hw.state |= PERF_HES_UPTODATE;
	पूर्ण
पूर्ण

अटल व्योम arc_pmu_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा arc_pmu_cpu *pmu_cpu = this_cpu_ptr(&arc_pmu_cpu);

	arc_pmu_stop(event, PERF_EF_UPDATE);
	__clear_bit(event->hw.idx, pmu_cpu->used_mask);

	pmu_cpu->act_counter[event->hw.idx] = 0;

	perf_event_update_userpage(event);
पूर्ण

/* allocate hardware counter and optionally start counting */
अटल पूर्णांक arc_pmu_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा arc_pmu_cpu *pmu_cpu = this_cpu_ptr(&arc_pmu_cpu);
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक idx = hwc->idx;

	idx = ffz(pmu_cpu->used_mask[0]);
	अगर (idx == arc_pmu->n_counters)
		वापस -EAGAIN;

	__set_bit(idx, pmu_cpu->used_mask);
	hwc->idx = idx;

	ग_लिखो_aux_reg(ARC_REG_PCT_INDEX, idx);

	pmu_cpu->act_counter[idx] = event;

	अगर (is_sampling_event(event)) अणु
		/* Mimic full counter overflow as other arches करो */
		ग_लिखो_aux_reg(ARC_REG_PCT_INT_CNTL,
			      lower_32_bits(arc_pmu->max_period));
		ग_लिखो_aux_reg(ARC_REG_PCT_INT_CNTH,
			      upper_32_bits(arc_pmu->max_period));
	पूर्ण

	ग_लिखो_aux_reg(ARC_REG_PCT_CONFIG, 0);
	ग_लिखो_aux_reg(ARC_REG_PCT_COUNTL, 0);
	ग_लिखो_aux_reg(ARC_REG_PCT_COUNTH, 0);
	local64_set(&hwc->prev_count, 0);

	hwc->state = PERF_HES_UPTODATE | PERF_HES_STOPPED;
	अगर (flags & PERF_EF_START)
		arc_pmu_start(event, PERF_EF_RELOAD);

	perf_event_update_userpage(event);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ISA_ARCV2
अटल irqवापस_t arc_pmu_पूर्णांकr(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा perf_sample_data data;
	काष्ठा arc_pmu_cpu *pmu_cpu = this_cpu_ptr(&arc_pmu_cpu);
	काष्ठा pt_regs *regs;
	अचिन्हित पूर्णांक active_पूर्णांकs;
	पूर्णांक idx;

	arc_pmu_disable(&arc_pmu->pmu);

	active_पूर्णांकs = पढ़ो_aux_reg(ARC_REG_PCT_INT_ACT);
	अगर (!active_पूर्णांकs)
		जाओ करोne;

	regs = get_irq_regs();

	करो अणु
		काष्ठा perf_event *event;
		काष्ठा hw_perf_event *hwc;

		idx = __ffs(active_पूर्णांकs);

		/* Reset पूर्णांकerrupt flag by writing of 1 */
		ग_लिखो_aux_reg(ARC_REG_PCT_INT_ACT, BIT(idx));

		/*
		 * On reset of "interrupt active" bit corresponding
		 * "interrupt enable" bit माला_लो स्वतःmatically reset as well.
		 * Now we need to re-enable पूर्णांकerrupt क्रम the counter.
		 */
		ग_लिखो_aux_reg(ARC_REG_PCT_INT_CTRL,
			पढ़ो_aux_reg(ARC_REG_PCT_INT_CTRL) | BIT(idx));

		event = pmu_cpu->act_counter[idx];
		hwc = &event->hw;

		WARN_ON_ONCE(hwc->idx != idx);

		arc_perf_event_update(event, &event->hw, event->hw.idx);
		perf_sample_data_init(&data, 0, hwc->last_period);
		अगर (arc_pmu_event_set_period(event)) अणु
			अगर (perf_event_overflow(event, &data, regs))
				arc_pmu_stop(event, 0);
		पूर्ण

		active_पूर्णांकs &= ~BIT(idx);
	पूर्ण जबतक (active_पूर्णांकs);

करोne:
	arc_pmu_enable(&arc_pmu->pmu);

	वापस IRQ_HANDLED;
पूर्ण
#अन्यथा

अटल irqवापस_t arc_pmu_पूर्णांकr(पूर्णांक irq, व्योम *dev)
अणु
	वापस IRQ_NONE;
पूर्ण

#पूर्ण_अगर /* CONFIG_ISA_ARCV2 */

अटल व्योम arc_cpu_pmu_irq_init(व्योम *data)
अणु
	पूर्णांक irq = *(पूर्णांक *)data;

	enable_percpu_irq(irq, IRQ_TYPE_NONE);

	/* Clear all pending पूर्णांकerrupt flags */
	ग_लिखो_aux_reg(ARC_REG_PCT_INT_ACT, 0xffffffff);
पूर्ण

/* Event field occupies the bottom 15 bits of our config field */
PMU_FORMAT_ATTR(event, "config:0-14");
अटल काष्ठा attribute *arc_pmu_क्रमmat_attrs[] = अणु
	&क्रमmat_attr_event.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group arc_pmu_क्रमmat_attr_gr = अणु
	.name = "format",
	.attrs = arc_pmu_क्रमmat_attrs,
पूर्ण;

अटल sमाप_प्रकार arc_pmu_events_sysfs_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *page)
अणु
	काष्ठा perf_pmu_events_attr *pmu_attr;

	pmu_attr = container_of(attr, काष्ठा perf_pmu_events_attr, attr);
	वापस प्र_लिखो(page, "event=0x%04llx\n", pmu_attr->id);
पूर्ण

/*
 * We करोn't add attrs here as we don't have pre-defined list of perf events.
 * We will generate and add attrs dynamically in probe() after we पढ़ो HW
 * configuration.
 */
अटल काष्ठा attribute_group arc_pmu_events_attr_gr = अणु
	.name = "events",
पूर्ण;

अटल व्योम arc_pmu_add_raw_event_attr(पूर्णांक j, अक्षर *str)
अणु
	स_हटाओ(arc_pmu->raw_entry[j].name, str, ARCPMU_EVENT_NAME_LEN - 1);
	arc_pmu->attr[j].attr.attr.name = arc_pmu->raw_entry[j].name;
	arc_pmu->attr[j].attr.attr.mode = VERIFY_OCTAL_PERMISSIONS(0444);
	arc_pmu->attr[j].attr.show = arc_pmu_events_sysfs_show;
	arc_pmu->attr[j].id = j;
	arc_pmu->attrs[j] = &(arc_pmu->attr[j].attr.attr);
पूर्ण

अटल पूर्णांक arc_pmu_raw_alloc(काष्ठा device *dev)
अणु
	arc_pmu->attr = devm_kदो_स्मृति_array(dev, arc_pmu->n_events + 1,
		माप(*arc_pmu->attr), GFP_KERNEL | __GFP_ZERO);
	अगर (!arc_pmu->attr)
		वापस -ENOMEM;

	arc_pmu->attrs = devm_kदो_स्मृति_array(dev, arc_pmu->n_events + 1,
		माप(*arc_pmu->attrs), GFP_KERNEL | __GFP_ZERO);
	अगर (!arc_pmu->attrs)
		वापस -ENOMEM;

	arc_pmu->raw_entry = devm_kदो_स्मृति_array(dev, arc_pmu->n_events,
		माप(*arc_pmu->raw_entry), GFP_KERNEL | __GFP_ZERO);
	अगर (!arc_pmu->raw_entry)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल अंतरभूत bool event_in_hw_event_map(पूर्णांक i, अक्षर *name)
अणु
	अगर (!arc_pmu_ev_hw_map[i])
		वापस false;

	अगर (!म_माप(arc_pmu_ev_hw_map[i]))
		वापस false;

	अगर (म_भेद(arc_pmu_ev_hw_map[i], name))
		वापस false;

	वापस true;
पूर्ण

अटल व्योम arc_pmu_map_hw_event(पूर्णांक j, अक्षर *str)
अणु
	पूर्णांक i;

	/* See अगर HW condition has been mapped to a perf event_id */
	क्रम (i = 0; i < ARRAY_SIZE(arc_pmu_ev_hw_map); i++) अणु
		अगर (event_in_hw_event_map(i, str)) अणु
			pr_debug("mapping perf event %2d to h/w event \'%8s\' (idx %d)\n",
				 i, str, j);
			arc_pmu->ev_hw_idx[i] = j;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक arc_pmu_device_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा arc_reg_pct_build pct_bcr;
	काष्ठा arc_reg_cc_build cc_bcr;
	पूर्णांक i, has_पूर्णांकerrupts, irq = -1;
	पूर्णांक counter_size;	/* in bits */

	जोड़ cc_name अणु
		काष्ठा अणु
			u32 word0, word1;
			अक्षर sentinel;
		पूर्ण inभाग;
		अक्षर str[ARCPMU_EVENT_NAME_LEN];
	पूर्ण cc_name;


	READ_BCR(ARC_REG_PCT_BUILD, pct_bcr);
	अगर (!pct_bcr.v) अणु
		pr_err("This core does not have performance counters!\n");
		वापस -ENODEV;
	पूर्ण
	BUILD_BUG_ON(ARC_PERF_MAX_COUNTERS > 32);
	अगर (WARN_ON(pct_bcr.c > ARC_PERF_MAX_COUNTERS))
		वापस -EINVAL;

	READ_BCR(ARC_REG_CC_BUILD, cc_bcr);
	अगर (WARN(!cc_bcr.v, "Counters exist but No countable conditions?"))
		वापस -EINVAL;

	arc_pmu = devm_kzalloc(&pdev->dev, माप(काष्ठा arc_pmu), GFP_KERNEL);
	अगर (!arc_pmu)
		वापस -ENOMEM;

	arc_pmu->n_events = cc_bcr.c;

	अगर (arc_pmu_raw_alloc(&pdev->dev))
		वापस -ENOMEM;

	has_पूर्णांकerrupts = is_isa_arcv2() ? pct_bcr.i : 0;

	arc_pmu->n_counters = pct_bcr.c;
	counter_size = 32 + (pct_bcr.s << 4);

	arc_pmu->max_period = (1ULL << counter_size) / 2 - 1ULL;

	pr_info("ARC perf\t: %d counters (%d bits), %d conditions%s\n",
		arc_pmu->n_counters, counter_size, cc_bcr.c,
		has_पूर्णांकerrupts ? ", [overflow IRQ support]" : "");

	cc_name.str[ARCPMU_EVENT_NAME_LEN - 1] = 0;
	क्रम (i = 0; i < PERF_COUNT_ARC_HW_MAX; i++)
		arc_pmu->ev_hw_idx[i] = -1;

	/* loop thru all available h/w condition indexes */
	क्रम (i = 0; i < cc_bcr.c; i++) अणु
		ग_लिखो_aux_reg(ARC_REG_CC_INDEX, i);
		cc_name.inभाग.word0 = le32_to_cpu(पढ़ो_aux_reg(ARC_REG_CC_NAME0));
		cc_name.inभाग.word1 = le32_to_cpu(पढ़ो_aux_reg(ARC_REG_CC_NAME1));

		arc_pmu_map_hw_event(i, cc_name.str);
		arc_pmu_add_raw_event_attr(i, cc_name.str);
	पूर्ण

	arc_pmu_events_attr_gr.attrs = arc_pmu->attrs;
	arc_pmu->attr_groups[ARCPMU_ATTR_GR_EVENTS] = &arc_pmu_events_attr_gr;
	arc_pmu->attr_groups[ARCPMU_ATTR_GR_FORMATS] = &arc_pmu_क्रमmat_attr_gr;

	arc_pmu->pmu = (काष्ठा pmu) अणु
		.pmu_enable	= arc_pmu_enable,
		.pmu_disable	= arc_pmu_disable,
		.event_init	= arc_pmu_event_init,
		.add		= arc_pmu_add,
		.del		= arc_pmu_del,
		.start		= arc_pmu_start,
		.stop		= arc_pmu_stop,
		.पढ़ो		= arc_pmu_पढ़ो,
		.attr_groups	= arc_pmu->attr_groups,
	पूर्ण;

	अगर (has_पूर्णांकerrupts) अणु
		irq = platक्रमm_get_irq(pdev, 0);
		अगर (irq >= 0) अणु
			पूर्णांक ret;

			arc_pmu->irq = irq;

			/* पूर्णांकc map function ensures irq_set_percpu_devid() called */
			ret = request_percpu_irq(irq, arc_pmu_पूर्णांकr, "ARC perf counters",
						 this_cpu_ptr(&arc_pmu_cpu));

			अगर (!ret)
				on_each_cpu(arc_cpu_pmu_irq_init, &irq, 1);
			अन्यथा
				irq = -1;
		पूर्ण

	पूर्ण

	अगर (irq == -1)
		arc_pmu->pmu.capabilities |= PERF_PMU_CAP_NO_INTERRUPT;

	/*
	 * perf parser करोesn't really like '-' symbol in events name, so let's
	 * use '_' in arc pct name as it goes to kernel PMU event prefix.
	 */
	वापस perf_pmu_रेजिस्टर(&arc_pmu->pmu, "arc_pct", PERF_TYPE_RAW);
पूर्ण

अटल स्थिर काष्ठा of_device_id arc_pmu_match[] = अणु
	अणु .compatible = "snps,arc700-pct" पूर्ण,
	अणु .compatible = "snps,archs-pct" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, arc_pmu_match);

अटल काष्ठा platक्रमm_driver arc_pmu_driver = अणु
	.driver	= अणु
		.name		= "arc-pct",
		.of_match_table = of_match_ptr(arc_pmu_match),
	पूर्ण,
	.probe		= arc_pmu_device_probe,
पूर्ण;

module_platक्रमm_driver(arc_pmu_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mischa Jonker <mjonker@synopsys.com>");
MODULE_DESCRIPTION("ARC PMU driver");
