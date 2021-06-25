<शैली गुरु>
/*
 * Perक्रमmance events - AMD IBS
 *
 *  Copyright (C) 2011 Advanced Micro Devices, Inc., Robert Richter
 *
 *  For licencing details see kernel-base/COPYING
 */

#समावेश <linux/perf_event.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/pci.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/sched/घड़ी.h>

#समावेश <यंत्र/apic.h>

#समावेश "../perf_event.h"

अटल u32 ibs_caps;

#अगर defined(CONFIG_PERF_EVENTS) && defined(CONFIG_CPU_SUP_AMD)

#समावेश <linux/kprobes.h>
#समावेश <linux/hardirq.h>

#समावेश <यंत्र/nmi.h>

#घोषणा IBS_FETCH_CONFIG_MASK	(IBS_FETCH_RAND_EN | IBS_FETCH_MAX_CNT)
#घोषणा IBS_OP_CONFIG_MASK	IBS_OP_MAX_CNT


/*
 * IBS states:
 *
 * ENABLED; tracks the pmu::add(), pmu::del() state, when set the counter is taken
 * and any further add()s must fail.
 *
 * STARTED/STOPPING/STOPPED; deal with pmu::start(), pmu::stop() state but are
 * complicated by the fact that the IBS hardware can send late NMIs (ie. after
 * we've cleared the EN bit).
 *
 * In order to consume these late NMIs we have the STOPPED state, any NMI that
 * happens after we've cleared the EN state will clear this bit and report the
 * NMI handled (this is fundamentally racy in the face or multiple NMI sources,
 * someone अन्यथा can consume our BIT and our NMI will go unhandled).
 *
 * And since we cannot set/clear this separate bit together with the EN bit,
 * there are races; अगर we cleared STARTED early, an NMI could land in
 * between clearing STARTED and clearing the EN bit (in fact multiple NMIs
 * could happen अगर the period is small enough), and consume our STOPPED bit
 * and trigger streams of unhandled NMIs.
 *
 * If, however, we clear STARTED late, an NMI can hit between clearing the
 * EN bit and clearing STARTED, still see STARTED set and process the event.
 * If this event will have the VALID bit clear, we bail properly, but this
 * is not a given. With VALID set we can end up calling pmu::stop() again
 * (the throttle logic) and trigger the WARNs in there.
 *
 * So what we करो is set STOPPING beक्रमe clearing EN to aव्योम the pmu::stop()
 * nesting, and clear STARTED late, so that we have a well defined state over
 * the clearing of the EN bit.
 *
 * XXX: we could probably be using !atomic bitops क्रम all this.
 */

क्रमागत ibs_states अणु
	IBS_ENABLED	= 0,
	IBS_STARTED	= 1,
	IBS_STOPPING	= 2,
	IBS_STOPPED	= 3,

	IBS_MAX_STATES,
पूर्ण;

काष्ठा cpu_perf_ibs अणु
	काष्ठा perf_event	*event;
	अचिन्हित दीर्घ		state[BITS_TO_LONGS(IBS_MAX_STATES)];
पूर्ण;

काष्ठा perf_ibs अणु
	काष्ठा pmu			pmu;
	अचिन्हित पूर्णांक			msr;
	u64				config_mask;
	u64				cnt_mask;
	u64				enable_mask;
	u64				valid_mask;
	u64				max_period;
	अचिन्हित दीर्घ			offset_mask[1];
	पूर्णांक				offset_max;
	अचिन्हित पूर्णांक			fetch_count_reset_broken : 1;
	काष्ठा cpu_perf_ibs __percpu	*pcpu;

	काष्ठा attribute		**क्रमmat_attrs;
	काष्ठा attribute_group		क्रमmat_group;
	स्थिर काष्ठा attribute_group	*attr_groups[2];

	u64				(*get_count)(u64 config);
पूर्ण;

काष्ठा perf_ibs_data अणु
	u32		size;
	जोड़ अणु
		u32	data[0];	/* data buffer starts here */
		u32	caps;
	पूर्ण;
	u64		regs[MSR_AMD64_IBS_REG_COUNT_MAX];
पूर्ण;

अटल पूर्णांक
perf_event_set_period(काष्ठा hw_perf_event *hwc, u64 min, u64 max, u64 *hw_period)
अणु
	s64 left = local64_पढ़ो(&hwc->period_left);
	s64 period = hwc->sample_period;
	पूर्णांक overflow = 0;

	/*
	 * If we are way outside a reasonable range then just skip क्रमward:
	 */
	अगर (unlikely(left <= -period)) अणु
		left = period;
		local64_set(&hwc->period_left, left);
		hwc->last_period = period;
		overflow = 1;
	पूर्ण

	अगर (unlikely(left < (s64)min)) अणु
		left += period;
		local64_set(&hwc->period_left, left);
		hwc->last_period = period;
		overflow = 1;
	पूर्ण

	/*
	 * If the hw period that triggers the sw overflow is too लघु
	 * we might hit the irq handler. This biases the results.
	 * Thus we लघुen the next-to-last period and set the last
	 * period to the max period.
	 */
	अगर (left > max) अणु
		left -= max;
		अगर (left > max)
			left = max;
		अन्यथा अगर (left < min)
			left = min;
	पूर्ण

	*hw_period = (u64)left;

	वापस overflow;
पूर्ण

अटल  पूर्णांक
perf_event_try_update(काष्ठा perf_event *event, u64 new_raw_count, पूर्णांक width)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	पूर्णांक shअगरt = 64 - width;
	u64 prev_raw_count;
	u64 delta;

	/*
	 * Careful: an NMI might modअगरy the previous event value.
	 *
	 * Our tactic to handle this is to first atomically पढ़ो and
	 * exchange a new raw count - then add that new-prev delta
	 * count to the generic event atomically:
	 */
	prev_raw_count = local64_पढ़ो(&hwc->prev_count);
	अगर (local64_cmpxchg(&hwc->prev_count, prev_raw_count,
					new_raw_count) != prev_raw_count)
		वापस 0;

	/*
	 * Now we have the new raw value and have updated the prev
	 * बारtamp alपढ़ोy. We can now calculate the elapsed delta
	 * (event-)समय and add that to the generic event.
	 *
	 * Careful, not all hw sign-extends above the physical width
	 * of the count.
	 */
	delta = (new_raw_count << shअगरt) - (prev_raw_count << shअगरt);
	delta >>= shअगरt;

	local64_add(delta, &event->count);
	local64_sub(delta, &hwc->period_left);

	वापस 1;
पूर्ण

अटल काष्ठा perf_ibs perf_ibs_fetch;
अटल काष्ठा perf_ibs perf_ibs_op;

अटल काष्ठा perf_ibs *get_ibs_pmu(पूर्णांक type)
अणु
	अगर (perf_ibs_fetch.pmu.type == type)
		वापस &perf_ibs_fetch;
	अगर (perf_ibs_op.pmu.type == type)
		वापस &perf_ibs_op;
	वापस शून्य;
पूर्ण

/*
 * Use IBS क्रम precise event sampling:
 *
 *  perf record -a -e cpu-cycles:p ...    # use ibs op counting cycle count
 *  perf record -a -e r076:p ...          # same as -e cpu-cycles:p
 *  perf record -a -e r0C1:p ...          # use ibs op counting micro-ops
 *
 * IbsOpCntCtl (bit 19) of IBS Execution Control Register (IbsOpCtl,
 * MSRC001_1033) is used to select either cycle or micro-ops counting
 * mode.
 *
 * The rip of IBS samples has skid 0. Thus, IBS supports precise
 * levels 1 and 2 and the PERF_EFLAGS_EXACT is set. In rare हालs the
 * rip is invalid when IBS was not able to record the rip correctly.
 * We clear PERF_EFLAGS_EXACT and take the rip from pt_regs then.
 *
 */
अटल पूर्णांक perf_ibs_precise_event(काष्ठा perf_event *event, u64 *config)
अणु
	चयन (event->attr.precise_ip) अणु
	हाल 0:
		वापस -ENOENT;
	हाल 1:
	हाल 2:
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (event->attr.type) अणु
	हाल PERF_TYPE_HARDWARE:
		चयन (event->attr.config) अणु
		हाल PERF_COUNT_HW_CPU_CYCLES:
			*config = 0;
			वापस 0;
		पूर्ण
		अवरोध;
	हाल PERF_TYPE_RAW:
		चयन (event->attr.config) अणु
		हाल 0x0076:
			*config = 0;
			वापस 0;
		हाल 0x00C1:
			*config = IBS_OP_CNT_CTL;
			वापस 0;
		पूर्ण
		अवरोध;
	शेष:
		वापस -ENOENT;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक perf_ibs_init(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा perf_ibs *perf_ibs;
	u64 max_cnt, config;
	पूर्णांक ret;

	perf_ibs = get_ibs_pmu(event->attr.type);
	अगर (perf_ibs) अणु
		config = event->attr.config;
	पूर्ण अन्यथा अणु
		perf_ibs = &perf_ibs_op;
		ret = perf_ibs_precise_event(event, &config);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (event->pmu != &perf_ibs->pmu)
		वापस -ENOENT;

	अगर (config & ~perf_ibs->config_mask)
		वापस -EINVAL;

	अगर (hwc->sample_period) अणु
		अगर (config & perf_ibs->cnt_mask)
			/* raw max_cnt may not be set */
			वापस -EINVAL;
		अगर (!event->attr.sample_freq && hwc->sample_period & 0x0f)
			/*
			 * lower 4 bits can not be set in ibs max cnt,
			 * but allowing it in हाल we adjust the
			 * sample period to set a frequency.
			 */
			वापस -EINVAL;
		hwc->sample_period &= ~0x0FULL;
		अगर (!hwc->sample_period)
			hwc->sample_period = 0x10;
	पूर्ण अन्यथा अणु
		max_cnt = config & perf_ibs->cnt_mask;
		config &= ~perf_ibs->cnt_mask;
		event->attr.sample_period = max_cnt << 4;
		hwc->sample_period = event->attr.sample_period;
	पूर्ण

	अगर (!hwc->sample_period)
		वापस -EINVAL;

	/*
	 * If we modअगरy hwc->sample_period, we also need to update
	 * hwc->last_period and hwc->period_left.
	 */
	hwc->last_period = hwc->sample_period;
	local64_set(&hwc->period_left, hwc->sample_period);

	hwc->config_base = perf_ibs->msr;
	hwc->config = config;

	वापस 0;
पूर्ण

अटल पूर्णांक perf_ibs_set_period(काष्ठा perf_ibs *perf_ibs,
			       काष्ठा hw_perf_event *hwc, u64 *period)
अणु
	पूर्णांक overflow;

	/* ignore lower 4 bits in min count: */
	overflow = perf_event_set_period(hwc, 1<<4, perf_ibs->max_period, period);
	local64_set(&hwc->prev_count, 0);

	वापस overflow;
पूर्ण

अटल u64 get_ibs_fetch_count(u64 config)
अणु
	वापस (config & IBS_FETCH_CNT) >> 12;
पूर्ण

अटल u64 get_ibs_op_count(u64 config)
अणु
	u64 count = 0;

	/*
	 * If the पूर्णांकernal 27-bit counter rolled over, the count is MaxCnt
	 * and the lower 7 bits of CurCnt are अक्रमomized.
	 * Otherwise CurCnt has the full 27-bit current counter value.
	 */
	अगर (config & IBS_OP_VAL) अणु
		count = (config & IBS_OP_MAX_CNT) << 4;
		अगर (ibs_caps & IBS_CAPS_OPCNTEXT)
			count += config & IBS_OP_MAX_CNT_EXT_MASK;
	पूर्ण अन्यथा अगर (ibs_caps & IBS_CAPS_RDWROPCNT) अणु
		count = (config & IBS_OP_CUR_CNT) >> 32;
	पूर्ण

	वापस count;
पूर्ण

अटल व्योम
perf_ibs_event_update(काष्ठा perf_ibs *perf_ibs, काष्ठा perf_event *event,
		      u64 *config)
अणु
	u64 count = perf_ibs->get_count(*config);

	/*
	 * Set width to 64 since we करो not overflow on max width but
	 * instead on max count. In perf_ibs_set_period() we clear
	 * prev count manually on overflow.
	 */
	जबतक (!perf_event_try_update(event, count, 64)) अणु
		rdmsrl(event->hw.config_base, *config);
		count = perf_ibs->get_count(*config);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम perf_ibs_enable_event(काष्ठा perf_ibs *perf_ibs,
					 काष्ठा hw_perf_event *hwc, u64 config)
अणु
	u64 पंचांगp = hwc->config | config;

	अगर (perf_ibs->fetch_count_reset_broken)
		wrmsrl(hwc->config_base, पंचांगp & ~perf_ibs->enable_mask);

	wrmsrl(hwc->config_base, पंचांगp | perf_ibs->enable_mask);
पूर्ण

/*
 * Erratum #420 Inकाष्ठाion-Based Sampling Engine May Generate
 * Interrupt that Cannot Be Cleared:
 *
 * Must clear counter mask first, then clear the enable bit. See
 * Revision Guide क्रम AMD Family 10h Processors, Publication #41322.
 */
अटल अंतरभूत व्योम perf_ibs_disable_event(काष्ठा perf_ibs *perf_ibs,
					  काष्ठा hw_perf_event *hwc, u64 config)
अणु
	config &= ~perf_ibs->cnt_mask;
	अगर (boot_cpu_data.x86 == 0x10)
		wrmsrl(hwc->config_base, config);
	config &= ~perf_ibs->enable_mask;
	wrmsrl(hwc->config_base, config);
पूर्ण

/*
 * We cannot restore the ibs pmu state, so we always needs to update
 * the event जबतक stopping it and then reset the state when starting
 * again. Thus, ignoring PERF_EF_RELOAD and PERF_EF_UPDATE flags in
 * perf_ibs_start()/perf_ibs_stop() and instead always करो it.
 */
अटल व्योम perf_ibs_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा perf_ibs *perf_ibs = container_of(event->pmu, काष्ठा perf_ibs, pmu);
	काष्ठा cpu_perf_ibs *pcpu = this_cpu_ptr(perf_ibs->pcpu);
	u64 period, config = 0;

	अगर (WARN_ON_ONCE(!(hwc->state & PERF_HES_STOPPED)))
		वापस;

	WARN_ON_ONCE(!(hwc->state & PERF_HES_UPTODATE));
	hwc->state = 0;

	perf_ibs_set_period(perf_ibs, hwc, &period);
	अगर (perf_ibs == &perf_ibs_op && (ibs_caps & IBS_CAPS_OPCNTEXT)) अणु
		config |= period & IBS_OP_MAX_CNT_EXT_MASK;
		period &= ~IBS_OP_MAX_CNT_EXT_MASK;
	पूर्ण
	config |= period >> 4;

	/*
	 * Set STARTED beक्रमe enabling the hardware, such that a subsequent NMI
	 * must observe it.
	 */
	set_bit(IBS_STARTED,    pcpu->state);
	clear_bit(IBS_STOPPING, pcpu->state);
	perf_ibs_enable_event(perf_ibs, hwc, config);

	perf_event_update_userpage(event);
पूर्ण

अटल व्योम perf_ibs_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा hw_perf_event *hwc = &event->hw;
	काष्ठा perf_ibs *perf_ibs = container_of(event->pmu, काष्ठा perf_ibs, pmu);
	काष्ठा cpu_perf_ibs *pcpu = this_cpu_ptr(perf_ibs->pcpu);
	u64 config;
	पूर्णांक stopping;

	अगर (test_and_set_bit(IBS_STOPPING, pcpu->state))
		वापस;

	stopping = test_bit(IBS_STARTED, pcpu->state);

	अगर (!stopping && (hwc->state & PERF_HES_UPTODATE))
		वापस;

	rdmsrl(hwc->config_base, config);

	अगर (stopping) अणु
		/*
		 * Set STOPPED beक्रमe disabling the hardware, such that it
		 * must be visible to NMIs the moment we clear the EN bit,
		 * at which poपूर्णांक we can generate an !VALID sample which
		 * we need to consume.
		 */
		set_bit(IBS_STOPPED, pcpu->state);
		perf_ibs_disable_event(perf_ibs, hwc, config);
		/*
		 * Clear STARTED after disabling the hardware; अगर it were
		 * cleared beक्रमe an NMI hitting after the clear but beक्रमe
		 * clearing the EN bit might think it a spurious NMI and not
		 * handle it.
		 *
		 * Clearing it after, however, creates the problem of the NMI
		 * handler seeing STARTED but not having a valid sample.
		 */
		clear_bit(IBS_STARTED, pcpu->state);
		WARN_ON_ONCE(hwc->state & PERF_HES_STOPPED);
		hwc->state |= PERF_HES_STOPPED;
	पूर्ण

	अगर (hwc->state & PERF_HES_UPTODATE)
		वापस;

	/*
	 * Clear valid bit to not count rollovers on update, rollovers
	 * are only updated in the irq handler.
	 */
	config &= ~perf_ibs->valid_mask;

	perf_ibs_event_update(perf_ibs, event, &config);
	hwc->state |= PERF_HES_UPTODATE;
पूर्ण

अटल पूर्णांक perf_ibs_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा perf_ibs *perf_ibs = container_of(event->pmu, काष्ठा perf_ibs, pmu);
	काष्ठा cpu_perf_ibs *pcpu = this_cpu_ptr(perf_ibs->pcpu);

	अगर (test_and_set_bit(IBS_ENABLED, pcpu->state))
		वापस -ENOSPC;

	event->hw.state = PERF_HES_UPTODATE | PERF_HES_STOPPED;

	pcpu->event = event;

	अगर (flags & PERF_EF_START)
		perf_ibs_start(event, PERF_EF_RELOAD);

	वापस 0;
पूर्ण

अटल व्योम perf_ibs_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा perf_ibs *perf_ibs = container_of(event->pmu, काष्ठा perf_ibs, pmu);
	काष्ठा cpu_perf_ibs *pcpu = this_cpu_ptr(perf_ibs->pcpu);

	अगर (!test_and_clear_bit(IBS_ENABLED, pcpu->state))
		वापस;

	perf_ibs_stop(event, PERF_EF_UPDATE);

	pcpu->event = शून्य;

	perf_event_update_userpage(event);
पूर्ण

अटल व्योम perf_ibs_पढ़ो(काष्ठा perf_event *event) अणु पूर्ण

PMU_FORMAT_ATTR(अक्रम_en,	"config:57");
PMU_FORMAT_ATTR(cnt_ctl,	"config:19");

अटल काष्ठा attribute *ibs_fetch_क्रमmat_attrs[] = अणु
	&क्रमmat_attr_अक्रम_en.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *ibs_op_क्रमmat_attrs[] = अणु
	शून्य,	/* &क्रमmat_attr_cnt_ctl.attr अगर IBS_CAPS_OPCNT */
	शून्य,
पूर्ण;

अटल काष्ठा perf_ibs perf_ibs_fetch = अणु
	.pmu = अणु
		.task_ctx_nr	= perf_invalid_context,

		.event_init	= perf_ibs_init,
		.add		= perf_ibs_add,
		.del		= perf_ibs_del,
		.start		= perf_ibs_start,
		.stop		= perf_ibs_stop,
		.पढ़ो		= perf_ibs_पढ़ो,
		.capabilities	= PERF_PMU_CAP_NO_EXCLUDE,
	पूर्ण,
	.msr			= MSR_AMD64_IBSFETCHCTL,
	.config_mask		= IBS_FETCH_CONFIG_MASK,
	.cnt_mask		= IBS_FETCH_MAX_CNT,
	.enable_mask		= IBS_FETCH_ENABLE,
	.valid_mask		= IBS_FETCH_VAL,
	.max_period		= IBS_FETCH_MAX_CNT << 4,
	.offset_mask		= अणु MSR_AMD64_IBSFETCH_REG_MASK पूर्ण,
	.offset_max		= MSR_AMD64_IBSFETCH_REG_COUNT,
	.क्रमmat_attrs		= ibs_fetch_क्रमmat_attrs,

	.get_count		= get_ibs_fetch_count,
पूर्ण;

अटल काष्ठा perf_ibs perf_ibs_op = अणु
	.pmu = अणु
		.task_ctx_nr	= perf_invalid_context,

		.event_init	= perf_ibs_init,
		.add		= perf_ibs_add,
		.del		= perf_ibs_del,
		.start		= perf_ibs_start,
		.stop		= perf_ibs_stop,
		.पढ़ो		= perf_ibs_पढ़ो,
	पूर्ण,
	.msr			= MSR_AMD64_IBSOPCTL,
	.config_mask		= IBS_OP_CONFIG_MASK,
	.cnt_mask		= IBS_OP_MAX_CNT | IBS_OP_CUR_CNT |
				  IBS_OP_CUR_CNT_RAND,
	.enable_mask		= IBS_OP_ENABLE,
	.valid_mask		= IBS_OP_VAL,
	.max_period		= IBS_OP_MAX_CNT << 4,
	.offset_mask		= अणु MSR_AMD64_IBSOP_REG_MASK पूर्ण,
	.offset_max		= MSR_AMD64_IBSOP_REG_COUNT,
	.क्रमmat_attrs		= ibs_op_क्रमmat_attrs,

	.get_count		= get_ibs_op_count,
पूर्ण;

अटल पूर्णांक perf_ibs_handle_irq(काष्ठा perf_ibs *perf_ibs, काष्ठा pt_regs *iregs)
अणु
	काष्ठा cpu_perf_ibs *pcpu = this_cpu_ptr(perf_ibs->pcpu);
	काष्ठा perf_event *event = pcpu->event;
	काष्ठा hw_perf_event *hwc;
	काष्ठा perf_sample_data data;
	काष्ठा perf_raw_record raw;
	काष्ठा pt_regs regs;
	काष्ठा perf_ibs_data ibs_data;
	पूर्णांक offset, size, check_rip, offset_max, throttle = 0;
	अचिन्हित पूर्णांक msr;
	u64 *buf, *config, period, new_config = 0;

	अगर (!test_bit(IBS_STARTED, pcpu->state)) अणु
fail:
		/*
		 * Catch spurious पूर्णांकerrupts after stopping IBS: After
		 * disabling IBS there could be still incoming NMIs
		 * with samples that even have the valid bit cleared.
		 * Mark all this NMIs as handled.
		 */
		अगर (test_and_clear_bit(IBS_STOPPED, pcpu->state))
			वापस 1;

		वापस 0;
	पूर्ण

	अगर (WARN_ON_ONCE(!event))
		जाओ fail;

	hwc = &event->hw;
	msr = hwc->config_base;
	buf = ibs_data.regs;
	rdmsrl(msr, *buf);
	अगर (!(*buf++ & perf_ibs->valid_mask))
		जाओ fail;

	config = &ibs_data.regs[0];
	perf_ibs_event_update(perf_ibs, event, config);
	perf_sample_data_init(&data, 0, hwc->last_period);
	अगर (!perf_ibs_set_period(perf_ibs, hwc, &period))
		जाओ out;	/* no sw counter overflow */

	ibs_data.caps = ibs_caps;
	size = 1;
	offset = 1;
	check_rip = (perf_ibs == &perf_ibs_op && (ibs_caps & IBS_CAPS_RIPINVALIDCHK));
	अगर (event->attr.sample_type & PERF_SAMPLE_RAW)
		offset_max = perf_ibs->offset_max;
	अन्यथा अगर (check_rip)
		offset_max = 3;
	अन्यथा
		offset_max = 1;
	करो अणु
		rdmsrl(msr + offset, *buf++);
		size++;
		offset = find_next_bit(perf_ibs->offset_mask,
				       perf_ibs->offset_max,
				       offset + 1);
	पूर्ण जबतक (offset < offset_max);
	/*
	 * Read IbsBrTarget, IbsOpData4, and IbsExtdCtl separately
	 * depending on their availability.
	 * Can't add to offset_max as they are staggered
	 */
	अगर (event->attr.sample_type & PERF_SAMPLE_RAW) अणु
		अगर (perf_ibs == &perf_ibs_op) अणु
			अगर (ibs_caps & IBS_CAPS_BRNTRGT) अणु
				rdmsrl(MSR_AMD64_IBSBRTARGET, *buf++);
				size++;
			पूर्ण
			अगर (ibs_caps & IBS_CAPS_OPDATA4) अणु
				rdmsrl(MSR_AMD64_IBSOPDATA4, *buf++);
				size++;
			पूर्ण
		पूर्ण
		अगर (perf_ibs == &perf_ibs_fetch && (ibs_caps & IBS_CAPS_FETCHCTLEXTD)) अणु
			rdmsrl(MSR_AMD64_ICIBSEXTDCTL, *buf++);
			size++;
		पूर्ण
	पूर्ण
	ibs_data.size = माप(u64) * size;

	regs = *iregs;
	अगर (check_rip && (ibs_data.regs[2] & IBS_RIP_INVALID)) अणु
		regs.flags &= ~PERF_EFLAGS_EXACT;
	पूर्ण अन्यथा अणु
		set_linear_ip(&regs, ibs_data.regs[1]);
		regs.flags |= PERF_EFLAGS_EXACT;
	पूर्ण

	अगर (event->attr.sample_type & PERF_SAMPLE_RAW) अणु
		raw = (काष्ठा perf_raw_record)अणु
			.frag = अणु
				.size = माप(u32) + ibs_data.size,
				.data = ibs_data.data,
			पूर्ण,
		पूर्ण;
		data.raw = &raw;
	पूर्ण

	throttle = perf_event_overflow(event, &data, &regs);
out:
	अगर (throttle) अणु
		perf_ibs_stop(event, 0);
	पूर्ण अन्यथा अणु
		अगर (perf_ibs == &perf_ibs_op) अणु
			अगर (ibs_caps & IBS_CAPS_OPCNTEXT) अणु
				new_config = period & IBS_OP_MAX_CNT_EXT_MASK;
				period &= ~IBS_OP_MAX_CNT_EXT_MASK;
			पूर्ण
			अगर ((ibs_caps & IBS_CAPS_RDWROPCNT) && (*config & IBS_OP_CNT_CTL))
				new_config |= *config & IBS_OP_CUR_CNT_RAND;
		पूर्ण
		new_config |= period >> 4;

		perf_ibs_enable_event(perf_ibs, hwc, new_config);
	पूर्ण

	perf_event_update_userpage(event);

	वापस 1;
पूर्ण

अटल पूर्णांक
perf_ibs_nmi_handler(अचिन्हित पूर्णांक cmd, काष्ठा pt_regs *regs)
अणु
	u64 stamp = sched_घड़ी();
	पूर्णांक handled = 0;

	handled += perf_ibs_handle_irq(&perf_ibs_fetch, regs);
	handled += perf_ibs_handle_irq(&perf_ibs_op, regs);

	अगर (handled)
		inc_irq_stat(apic_perf_irqs);

	perf_sample_event_took(sched_घड़ी() - stamp);

	वापस handled;
पूर्ण
NOKPROBE_SYMBOL(perf_ibs_nmi_handler);

अटल __init पूर्णांक perf_ibs_pmu_init(काष्ठा perf_ibs *perf_ibs, अक्षर *name)
अणु
	काष्ठा cpu_perf_ibs __percpu *pcpu;
	पूर्णांक ret;

	pcpu = alloc_percpu(काष्ठा cpu_perf_ibs);
	अगर (!pcpu)
		वापस -ENOMEM;

	perf_ibs->pcpu = pcpu;

	/* रेजिस्टर attributes */
	अगर (perf_ibs->क्रमmat_attrs[0]) अणु
		स_रखो(&perf_ibs->क्रमmat_group, 0, माप(perf_ibs->क्रमmat_group));
		perf_ibs->क्रमmat_group.name	= "format";
		perf_ibs->क्रमmat_group.attrs	= perf_ibs->क्रमmat_attrs;

		स_रखो(&perf_ibs->attr_groups, 0, माप(perf_ibs->attr_groups));
		perf_ibs->attr_groups[0]	= &perf_ibs->क्रमmat_group;
		perf_ibs->pmu.attr_groups	= perf_ibs->attr_groups;
	पूर्ण

	ret = perf_pmu_रेजिस्टर(&perf_ibs->pmu, name, -1);
	अगर (ret) अणु
		perf_ibs->pcpu = शून्य;
		मुक्त_percpu(pcpu);
	पूर्ण

	वापस ret;
पूर्ण

अटल __init व्योम perf_event_ibs_init(व्योम)
अणु
	काष्ठा attribute **attr = ibs_op_क्रमmat_attrs;

	/*
	 * Some chips fail to reset the fetch count when it is written; instead
	 * they need a 0-1 transition of IbsFetchEn.
	 */
	अगर (boot_cpu_data.x86 >= 0x16 && boot_cpu_data.x86 <= 0x18)
		perf_ibs_fetch.fetch_count_reset_broken = 1;

	perf_ibs_pmu_init(&perf_ibs_fetch, "ibs_fetch");

	अगर (ibs_caps & IBS_CAPS_OPCNT) अणु
		perf_ibs_op.config_mask |= IBS_OP_CNT_CTL;
		*attr++ = &क्रमmat_attr_cnt_ctl.attr;
	पूर्ण

	अगर (ibs_caps & IBS_CAPS_OPCNTEXT) अणु
		perf_ibs_op.max_period  |= IBS_OP_MAX_CNT_EXT_MASK;
		perf_ibs_op.config_mask	|= IBS_OP_MAX_CNT_EXT_MASK;
		perf_ibs_op.cnt_mask    |= IBS_OP_MAX_CNT_EXT_MASK;
	पूर्ण

	perf_ibs_pmu_init(&perf_ibs_op, "ibs_op");

	रेजिस्टर_nmi_handler(NMI_LOCAL, perf_ibs_nmi_handler, 0, "perf_ibs");
	pr_info("perf: AMD IBS detected (0x%08x)\n", ibs_caps);
पूर्ण

#अन्यथा /* defined(CONFIG_PERF_EVENTS) && defined(CONFIG_CPU_SUP_AMD) */

अटल __init व्योम perf_event_ibs_init(व्योम) अणु पूर्ण

#पूर्ण_अगर

/* IBS - apic initialization, क्रम perf and oprofile */

अटल __init u32 __get_ibs_caps(व्योम)
अणु
	u32 caps;
	अचिन्हित पूर्णांक max_level;

	अगर (!boot_cpu_has(X86_FEATURE_IBS))
		वापस 0;

	/* check IBS cpuid feature flags */
	max_level = cpuid_eax(0x80000000);
	अगर (max_level < IBS_CPUID_FEATURES)
		वापस IBS_CAPS_DEFAULT;

	caps = cpuid_eax(IBS_CPUID_FEATURES);
	अगर (!(caps & IBS_CAPS_AVAIL))
		/* cpuid flags not valid */
		वापस IBS_CAPS_DEFAULT;

	वापस caps;
पूर्ण

u32 get_ibs_caps(व्योम)
अणु
	वापस ibs_caps;
पूर्ण

EXPORT_SYMBOL(get_ibs_caps);

अटल अंतरभूत पूर्णांक get_eilvt(पूर्णांक offset)
अणु
	वापस !setup_APIC_eilvt(offset, 0, APIC_EILVT_MSG_NMI, 1);
पूर्ण

अटल अंतरभूत पूर्णांक put_eilvt(पूर्णांक offset)
अणु
	वापस !setup_APIC_eilvt(offset, 0, 0, 1);
पूर्ण

/*
 * Check and reserve APIC extended पूर्णांकerrupt LVT offset क्रम IBS अगर available.
 */
अटल अंतरभूत पूर्णांक ibs_eilvt_valid(व्योम)
अणु
	पूर्णांक offset;
	u64 val;
	पूर्णांक valid = 0;

	preempt_disable();

	rdmsrl(MSR_AMD64_IBSCTL, val);
	offset = val & IBSCTL_LVT_OFFSET_MASK;

	अगर (!(val & IBSCTL_LVT_OFFSET_VALID)) अणु
		pr_err(FW_BUG "cpu %d, invalid IBS interrupt offset %d (MSR%08X=0x%016llx)\n",
		       smp_processor_id(), offset, MSR_AMD64_IBSCTL, val);
		जाओ out;
	पूर्ण

	अगर (!get_eilvt(offset)) अणु
		pr_err(FW_BUG "cpu %d, IBS interrupt offset %d not available (MSR%08X=0x%016llx)\n",
		       smp_processor_id(), offset, MSR_AMD64_IBSCTL, val);
		जाओ out;
	पूर्ण

	valid = 1;
out:
	preempt_enable();

	वापस valid;
पूर्ण

अटल पूर्णांक setup_ibs_ctl(पूर्णांक ibs_eilvt_off)
अणु
	काष्ठा pci_dev *cpu_cfg;
	पूर्णांक nodes;
	u32 value = 0;

	nodes = 0;
	cpu_cfg = शून्य;
	करो अणु
		cpu_cfg = pci_get_device(PCI_VENDOR_ID_AMD,
					 PCI_DEVICE_ID_AMD_10H_NB_MISC,
					 cpu_cfg);
		अगर (!cpu_cfg)
			अवरोध;
		++nodes;
		pci_ग_लिखो_config_dword(cpu_cfg, IBSCTL, ibs_eilvt_off
				       | IBSCTL_LVT_OFFSET_VALID);
		pci_पढ़ो_config_dword(cpu_cfg, IBSCTL, &value);
		अगर (value != (ibs_eilvt_off | IBSCTL_LVT_OFFSET_VALID)) अणु
			pci_dev_put(cpu_cfg);
			pr_debug("Failed to setup IBS LVT offset, IBSCTL = 0x%08x\n",
				 value);
			वापस -EINVAL;
		पूर्ण
	पूर्ण जबतक (1);

	अगर (!nodes) अणु
		pr_debug("No CPU node configured for IBS\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This runs only on the current cpu. We try to find an LVT offset and
 * setup the local APIC. For this we must disable preemption. On
 * success we initialize all nodes with this offset. This updates then
 * the offset in the IBS_CTL per-node msr. The per-core APIC setup of
 * the IBS पूर्णांकerrupt vector is handled by perf_ibs_cpu_notअगरier that
 * is using the new offset.
 */
अटल व्योम क्रमce_ibs_eilvt_setup(व्योम)
अणु
	पूर्णांक offset;
	पूर्णांक ret;

	preempt_disable();
	/* find the next मुक्त available EILVT entry, skip offset 0 */
	क्रम (offset = 1; offset < APIC_EILVT_NR_MAX; offset++) अणु
		अगर (get_eilvt(offset))
			अवरोध;
	पूर्ण
	preempt_enable();

	अगर (offset == APIC_EILVT_NR_MAX) अणु
		pr_debug("No EILVT entry available\n");
		वापस;
	पूर्ण

	ret = setup_ibs_ctl(offset);
	अगर (ret)
		जाओ out;

	अगर (!ibs_eilvt_valid())
		जाओ out;

	pr_info("LVT offset %d assigned\n", offset);

	वापस;
out:
	preempt_disable();
	put_eilvt(offset);
	preempt_enable();
	वापस;
पूर्ण

अटल व्योम ibs_eilvt_setup(व्योम)
अणु
	/*
	 * Force LVT offset assignment क्रम family 10h: The offsets are
	 * not asचिन्हित by the BIOS क्रम this family, so the OS is
	 * responsible क्रम करोing it. If the OS assignment fails, fall
	 * back to BIOS settings and try to setup this.
	 */
	अगर (boot_cpu_data.x86 == 0x10)
		क्रमce_ibs_eilvt_setup();
पूर्ण

अटल अंतरभूत पूर्णांक get_ibs_lvt_offset(व्योम)
अणु
	u64 val;

	rdmsrl(MSR_AMD64_IBSCTL, val);
	अगर (!(val & IBSCTL_LVT_OFFSET_VALID))
		वापस -EINVAL;

	वापस val & IBSCTL_LVT_OFFSET_MASK;
पूर्ण

अटल व्योम setup_APIC_ibs(व्योम)
अणु
	पूर्णांक offset;

	offset = get_ibs_lvt_offset();
	अगर (offset < 0)
		जाओ failed;

	अगर (!setup_APIC_eilvt(offset, 0, APIC_EILVT_MSG_NMI, 0))
		वापस;
failed:
	pr_warn("perf: IBS APIC setup failed on cpu #%d\n",
		smp_processor_id());
पूर्ण

अटल व्योम clear_APIC_ibs(व्योम)
अणु
	पूर्णांक offset;

	offset = get_ibs_lvt_offset();
	अगर (offset >= 0)
		setup_APIC_eilvt(offset, 0, APIC_EILVT_MSG_FIX, 1);
पूर्ण

अटल पूर्णांक x86_pmu_amd_ibs_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	setup_APIC_ibs();
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक perf_ibs_suspend(व्योम)
अणु
	clear_APIC_ibs();
	वापस 0;
पूर्ण

अटल व्योम perf_ibs_resume(व्योम)
अणु
	ibs_eilvt_setup();
	setup_APIC_ibs();
पूर्ण

अटल काष्ठा syscore_ops perf_ibs_syscore_ops = अणु
	.resume		= perf_ibs_resume,
	.suspend	= perf_ibs_suspend,
पूर्ण;

अटल व्योम perf_ibs_pm_init(व्योम)
अणु
	रेजिस्टर_syscore_ops(&perf_ibs_syscore_ops);
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम perf_ibs_pm_init(व्योम) अणु पूर्ण

#पूर्ण_अगर

अटल पूर्णांक x86_pmu_amd_ibs_dying_cpu(अचिन्हित पूर्णांक cpu)
अणु
	clear_APIC_ibs();
	वापस 0;
पूर्ण

अटल __init पूर्णांक amd_ibs_init(व्योम)
अणु
	u32 caps;

	caps = __get_ibs_caps();
	अगर (!caps)
		वापस -ENODEV;	/* ibs not supported by the cpu */

	ibs_eilvt_setup();

	अगर (!ibs_eilvt_valid())
		वापस -EINVAL;

	perf_ibs_pm_init();

	ibs_caps = caps;
	/* make ibs_caps visible to other cpus: */
	smp_mb();
	/*
	 * x86_pmu_amd_ibs_starting_cpu will be called from core on
	 * all online cpus.
	 */
	cpuhp_setup_state(CPUHP_AP_PERF_X86_AMD_IBS_STARTING,
			  "perf/x86/amd/ibs:starting",
			  x86_pmu_amd_ibs_starting_cpu,
			  x86_pmu_amd_ibs_dying_cpu);

	perf_event_ibs_init();

	वापस 0;
पूर्ण

/* Since we need the pci subप्रणाली to init ibs we can't करो this earlier: */
device_initcall(amd_ibs_init);
