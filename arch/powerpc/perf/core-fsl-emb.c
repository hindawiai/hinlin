<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Perक्रमmance event support - Freescale Embedded Perक्रमmance Monitor
 *
 * Copyright 2008-2009 Paul Mackerras, IBM Corporation.
 * Copyright 2010 Freescale Semiconductor, Inc.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/percpu.h>
#समावेश <linux/hardirq.h>
#समावेश <यंत्र/reg_fsl_emb.h>
#समावेश <यंत्र/pmc.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/ptrace.h>

काष्ठा cpu_hw_events अणु
	पूर्णांक n_events;
	पूर्णांक disabled;
	u8  pmcs_enabled;
	काष्ठा perf_event *event[MAX_HWEVENTS];
पूर्ण;
अटल DEFINE_PER_CPU(काष्ठा cpu_hw_events, cpu_hw_events);

अटल काष्ठा fsl_emb_pmu *ppmu;

/* Number of perf_events counting hardware events */
अटल atomic_t num_events;
/* Used to aव्योम races in calling reserve/release_pmc_hardware */
अटल DEFINE_MUTEX(pmc_reserve_mutex);

अटल व्योम perf_event_पूर्णांकerrupt(काष्ठा pt_regs *regs);

/*
 * Read one perक्रमmance monitor counter (PMC).
 */
अटल अचिन्हित दीर्घ पढ़ो_pmc(पूर्णांक idx)
अणु
	अचिन्हित दीर्घ val;

	चयन (idx) अणु
	हाल 0:
		val = mfpmr(PMRN_PMC0);
		अवरोध;
	हाल 1:
		val = mfpmr(PMRN_PMC1);
		अवरोध;
	हाल 2:
		val = mfpmr(PMRN_PMC2);
		अवरोध;
	हाल 3:
		val = mfpmr(PMRN_PMC3);
		अवरोध;
	हाल 4:
		val = mfpmr(PMRN_PMC4);
		अवरोध;
	हाल 5:
		val = mfpmr(PMRN_PMC5);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "oops trying to read PMC%d\n", idx);
		val = 0;
	पूर्ण
	वापस val;
पूर्ण

/*
 * Write one PMC.
 */
अटल व्योम ग_लिखो_pmc(पूर्णांक idx, अचिन्हित दीर्घ val)
अणु
	चयन (idx) अणु
	हाल 0:
		mtpmr(PMRN_PMC0, val);
		अवरोध;
	हाल 1:
		mtpmr(PMRN_PMC1, val);
		अवरोध;
	हाल 2:
		mtpmr(PMRN_PMC2, val);
		अवरोध;
	हाल 3:
		mtpmr(PMRN_PMC3, val);
		अवरोध;
	हाल 4:
		mtpmr(PMRN_PMC4, val);
		अवरोध;
	हाल 5:
		mtpmr(PMRN_PMC5, val);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "oops trying to write PMC%d\n", idx);
	पूर्ण

	isync();
पूर्ण

/*
 * Write one local control A रेजिस्टर
 */
अटल व्योम ग_लिखो_pmlca(पूर्णांक idx, अचिन्हित दीर्घ val)
अणु
	चयन (idx) अणु
	हाल 0:
		mtpmr(PMRN_PMLCA0, val);
		अवरोध;
	हाल 1:
		mtpmr(PMRN_PMLCA1, val);
		अवरोध;
	हाल 2:
		mtpmr(PMRN_PMLCA2, val);
		अवरोध;
	हाल 3:
		mtpmr(PMRN_PMLCA3, val);
		अवरोध;
	हाल 4:
		mtpmr(PMRN_PMLCA4, val);
		अवरोध;
	हाल 5:
		mtpmr(PMRN_PMLCA5, val);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "oops trying to write PMLCA%d\n", idx);
	पूर्ण

	isync();
पूर्ण

/*
 * Write one local control B रेजिस्टर
 */
अटल व्योम ग_लिखो_pmlcb(पूर्णांक idx, अचिन्हित दीर्घ val)
अणु
	चयन (idx) अणु
	हाल 0:
		mtpmr(PMRN_PMLCB0, val);
		अवरोध;
	हाल 1:
		mtpmr(PMRN_PMLCB1, val);
		अवरोध;
	हाल 2:
		mtpmr(PMRN_PMLCB2, val);
		अवरोध;
	हाल 3:
		mtpmr(PMRN_PMLCB3, val);
		अवरोध;
	हाल 4:
		mtpmr(PMRN_PMLCB4, val);
		अवरोध;
	हाल 5:
		mtpmr(PMRN_PMLCB5, val);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "oops trying to write PMLCB%d\n", idx);
	पूर्ण

	isync();
पूर्ण

अटल व्योम fsl_emb_pmu_पढ़ो(काष्ठा perf_event *event)
अणु
	s64 val, delta, prev;

	अगर (event->hw.state & PERF_HES_STOPPED)
		वापस;

	/*
	 * Perक्रमmance monitor पूर्णांकerrupts come even when पूर्णांकerrupts
	 * are soft-disabled, as दीर्घ as पूर्णांकerrupts are hard-enabled.
	 * Thereक्रमe we treat them like NMIs.
	 */
	करो अणु
		prev = local64_पढ़ो(&event->hw.prev_count);
		barrier();
		val = पढ़ो_pmc(event->hw.idx);
	पूर्ण जबतक (local64_cmpxchg(&event->hw.prev_count, prev, val) != prev);

	/* The counters are only 32 bits wide */
	delta = (val - prev) & 0xfffffffful;
	local64_add(delta, &event->count);
	local64_sub(delta, &event->hw.period_left);
पूर्ण

/*
 * Disable all events to prevent PMU पूर्णांकerrupts and to allow
 * events to be added or हटाओd.
 */
अटल व्योम fsl_emb_pmu_disable(काष्ठा pmu *pmu)
अणु
	काष्ठा cpu_hw_events *cpuhw;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	cpuhw = this_cpu_ptr(&cpu_hw_events);

	अगर (!cpuhw->disabled) अणु
		cpuhw->disabled = 1;

		/*
		 * Check अगर we ever enabled the PMU on this cpu.
		 */
		अगर (!cpuhw->pmcs_enabled) अणु
			ppc_enable_pmcs();
			cpuhw->pmcs_enabled = 1;
		पूर्ण

		अगर (atomic_पढ़ो(&num_events)) अणु
			/*
			 * Set the 'freeze all counters' bit, and disable
			 * पूर्णांकerrupts.  The barrier is to make sure the
			 * mtpmr has been executed and the PMU has frozen
			 * the events beक्रमe we वापस.
			 */

			mtpmr(PMRN_PMGC0, PMGC0_FAC);
			isync();
		पूर्ण
	पूर्ण
	local_irq_restore(flags);
पूर्ण

/*
 * Re-enable all events अगर disable == 0.
 * If we were previously disabled and events were added, then
 * put the new config on the PMU.
 */
अटल व्योम fsl_emb_pmu_enable(काष्ठा pmu *pmu)
अणु
	काष्ठा cpu_hw_events *cpuhw;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	cpuhw = this_cpu_ptr(&cpu_hw_events);
	अगर (!cpuhw->disabled)
		जाओ out;

	cpuhw->disabled = 0;
	ppc_set_pmu_inuse(cpuhw->n_events != 0);

	अगर (cpuhw->n_events > 0) अणु
		mtpmr(PMRN_PMGC0, PMGC0_PMIE | PMGC0_FCECE);
		isync();
	पूर्ण

 out:
	local_irq_restore(flags);
पूर्ण

अटल पूर्णांक collect_events(काष्ठा perf_event *group, पूर्णांक max_count,
			  काष्ठा perf_event *ctrs[])
अणु
	पूर्णांक n = 0;
	काष्ठा perf_event *event;

	अगर (!is_software_event(group)) अणु
		अगर (n >= max_count)
			वापस -1;
		ctrs[n] = group;
		n++;
	पूर्ण
	क्रम_each_sibling_event(event, group) अणु
		अगर (!is_software_event(event) &&
		    event->state != PERF_EVENT_STATE_OFF) अणु
			अगर (n >= max_count)
				वापस -1;
			ctrs[n] = event;
			n++;
		पूर्ण
	पूर्ण
	वापस n;
पूर्ण

/* context locked on entry */
अटल पूर्णांक fsl_emb_pmu_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_events *cpuhw;
	पूर्णांक ret = -EAGAIN;
	पूर्णांक num_counters = ppmu->n_counter;
	u64 val;
	पूर्णांक i;

	perf_pmu_disable(event->pmu);
	cpuhw = &get_cpu_var(cpu_hw_events);

	अगर (event->hw.config & FSL_EMB_EVENT_RESTRICTED)
		num_counters = ppmu->n_restricted;

	/*
	 * Allocate counters from top-करोwn, so that restricted-capable
	 * counters are kept मुक्त as दीर्घ as possible.
	 */
	क्रम (i = num_counters - 1; i >= 0; i--) अणु
		अगर (cpuhw->event[i])
			जारी;

		अवरोध;
	पूर्ण

	अगर (i < 0)
		जाओ out;

	event->hw.idx = i;
	cpuhw->event[i] = event;
	++cpuhw->n_events;

	val = 0;
	अगर (event->hw.sample_period) अणु
		s64 left = local64_पढ़ो(&event->hw.period_left);
		अगर (left < 0x80000000L)
			val = 0x80000000L - left;
	पूर्ण
	local64_set(&event->hw.prev_count, val);

	अगर (unlikely(!(flags & PERF_EF_START))) अणु
		event->hw.state = PERF_HES_STOPPED | PERF_HES_UPTODATE;
		val = 0;
	पूर्ण अन्यथा अणु
		event->hw.state &= ~(PERF_HES_STOPPED | PERF_HES_UPTODATE);
	पूर्ण

	ग_लिखो_pmc(i, val);
	perf_event_update_userpage(event);

	ग_लिखो_pmlcb(i, event->hw.config >> 32);
	ग_लिखो_pmlca(i, event->hw.config_base);

	ret = 0;
 out:
	put_cpu_var(cpu_hw_events);
	perf_pmu_enable(event->pmu);
	वापस ret;
पूर्ण

/* context locked on entry */
अटल व्योम fsl_emb_pmu_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_hw_events *cpuhw;
	पूर्णांक i = event->hw.idx;

	perf_pmu_disable(event->pmu);
	अगर (i < 0)
		जाओ out;

	fsl_emb_pmu_पढ़ो(event);

	cpuhw = &get_cpu_var(cpu_hw_events);

	WARN_ON(event != cpuhw->event[event->hw.idx]);

	ग_लिखो_pmlca(i, 0);
	ग_लिखो_pmlcb(i, 0);
	ग_लिखो_pmc(i, 0);

	cpuhw->event[i] = शून्य;
	event->hw.idx = -1;

	/*
	 * TODO: अगर at least one restricted event exists, and we
	 * just मुक्तd up a non-restricted-capable counter, and
	 * there is a restricted-capable counter occupied by
	 * a non-restricted event, migrate that event to the
	 * vacated counter.
	 */

	cpuhw->n_events--;

 out:
	perf_pmu_enable(event->pmu);
	put_cpu_var(cpu_hw_events);
पूर्ण

अटल व्योम fsl_emb_pmu_start(काष्ठा perf_event *event, पूर्णांक ef_flags)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ val;
	s64 left;

	अगर (event->hw.idx < 0 || !event->hw.sample_period)
		वापस;

	अगर (!(event->hw.state & PERF_HES_STOPPED))
		वापस;

	अगर (ef_flags & PERF_EF_RELOAD)
		WARN_ON_ONCE(!(event->hw.state & PERF_HES_UPTODATE));

	local_irq_save(flags);
	perf_pmu_disable(event->pmu);

	event->hw.state = 0;
	left = local64_पढ़ो(&event->hw.period_left);
	val = 0;
	अगर (left < 0x80000000L)
		val = 0x80000000L - left;
	ग_लिखो_pmc(event->hw.idx, val);

	perf_event_update_userpage(event);
	perf_pmu_enable(event->pmu);
	local_irq_restore(flags);
पूर्ण

अटल व्योम fsl_emb_pmu_stop(काष्ठा perf_event *event, पूर्णांक ef_flags)
अणु
	अचिन्हित दीर्घ flags;

	अगर (event->hw.idx < 0 || !event->hw.sample_period)
		वापस;

	अगर (event->hw.state & PERF_HES_STOPPED)
		वापस;

	local_irq_save(flags);
	perf_pmu_disable(event->pmu);

	fsl_emb_pmu_पढ़ो(event);
	event->hw.state |= PERF_HES_STOPPED | PERF_HES_UPTODATE;
	ग_लिखो_pmc(event->hw.idx, 0);

	perf_event_update_userpage(event);
	perf_pmu_enable(event->pmu);
	local_irq_restore(flags);
पूर्ण

/*
 * Release the PMU अगर this is the last perf_event.
 */
अटल व्योम hw_perf_event_destroy(काष्ठा perf_event *event)
अणु
	अगर (!atomic_add_unless(&num_events, -1, 1)) अणु
		mutex_lock(&pmc_reserve_mutex);
		अगर (atomic_dec_वापस(&num_events) == 0)
			release_pmc_hardware();
		mutex_unlock(&pmc_reserve_mutex);
	पूर्ण
पूर्ण

/*
 * Translate a generic cache event_id config to a raw event_id code.
 */
अटल पूर्णांक hw_perf_cache_event(u64 config, u64 *eventp)
अणु
	अचिन्हित दीर्घ type, op, result;
	पूर्णांक ev;

	अगर (!ppmu->cache_events)
		वापस -EINVAL;

	/* unpack config */
	type = config & 0xff;
	op = (config >> 8) & 0xff;
	result = (config >> 16) & 0xff;

	अगर (type >= PERF_COUNT_HW_CACHE_MAX ||
	    op >= PERF_COUNT_HW_CACHE_OP_MAX ||
	    result >= PERF_COUNT_HW_CACHE_RESULT_MAX)
		वापस -EINVAL;

	ev = (*ppmu->cache_events)[type][op][result];
	अगर (ev == 0)
		वापस -EOPNOTSUPP;
	अगर (ev == -1)
		वापस -EINVAL;
	*eventp = ev;
	वापस 0;
पूर्ण

अटल पूर्णांक fsl_emb_pmu_event_init(काष्ठा perf_event *event)
अणु
	u64 ev;
	काष्ठा perf_event *events[MAX_HWEVENTS];
	पूर्णांक n;
	पूर्णांक err;
	पूर्णांक num_restricted;
	पूर्णांक i;

	अगर (ppmu->n_counter > MAX_HWEVENTS) अणु
		WARN(1, "No. of perf counters (%d) is higher than max array size(%d)\n",
			ppmu->n_counter, MAX_HWEVENTS);
		ppmu->n_counter = MAX_HWEVENTS;
	पूर्ण

	चयन (event->attr.type) अणु
	हाल PERF_TYPE_HARDWARE:
		ev = event->attr.config;
		अगर (ev >= ppmu->n_generic || ppmu->generic_events[ev] == 0)
			वापस -EOPNOTSUPP;
		ev = ppmu->generic_events[ev];
		अवरोध;

	हाल PERF_TYPE_HW_CACHE:
		err = hw_perf_cache_event(event->attr.config, &ev);
		अगर (err)
			वापस err;
		अवरोध;

	हाल PERF_TYPE_RAW:
		ev = event->attr.config;
		अवरोध;

	शेष:
		वापस -ENOENT;
	पूर्ण

	event->hw.config = ppmu->xlate_event(ev);
	अगर (!(event->hw.config & FSL_EMB_EVENT_VALID))
		वापस -EINVAL;

	/*
	 * If this is in a group, check अगर it can go on with all the
	 * other hardware events in the group.  We assume the event
	 * hasn't been linked into its leader's sibling list at this poपूर्णांक.
	 */
	n = 0;
	अगर (event->group_leader != event) अणु
		n = collect_events(event->group_leader,
		                   ppmu->n_counter - 1, events);
		अगर (n < 0)
			वापस -EINVAL;
	पूर्ण

	अगर (event->hw.config & FSL_EMB_EVENT_RESTRICTED) अणु
		num_restricted = 0;
		क्रम (i = 0; i < n; i++) अणु
			अगर (events[i]->hw.config & FSL_EMB_EVENT_RESTRICTED)
				num_restricted++;
		पूर्ण

		अगर (num_restricted >= ppmu->n_restricted)
			वापस -EINVAL;
	पूर्ण

	event->hw.idx = -1;

	event->hw.config_base = PMLCA_CE | PMLCA_FCM1 |
	                        (u32)((ev << 16) & PMLCA_EVENT_MASK);

	अगर (event->attr.exclude_user)
		event->hw.config_base |= PMLCA_FCU;
	अगर (event->attr.exclude_kernel)
		event->hw.config_base |= PMLCA_FCS;
	अगर (event->attr.exclude_idle)
		वापस -ENOTSUPP;

	event->hw.last_period = event->hw.sample_period;
	local64_set(&event->hw.period_left, event->hw.last_period);

	/*
	 * See अगर we need to reserve the PMU.
	 * If no events are currently in use, then we have to take a
	 * mutex to ensure that we करोn't race with another task करोing
	 * reserve_pmc_hardware or release_pmc_hardware.
	 */
	err = 0;
	अगर (!atomic_inc_not_zero(&num_events)) अणु
		mutex_lock(&pmc_reserve_mutex);
		अगर (atomic_पढ़ो(&num_events) == 0 &&
		    reserve_pmc_hardware(perf_event_पूर्णांकerrupt))
			err = -EBUSY;
		अन्यथा
			atomic_inc(&num_events);
		mutex_unlock(&pmc_reserve_mutex);

		mtpmr(PMRN_PMGC0, PMGC0_FAC);
		isync();
	पूर्ण
	event->destroy = hw_perf_event_destroy;

	वापस err;
पूर्ण

अटल काष्ठा pmu fsl_emb_pmu = अणु
	.pmu_enable	= fsl_emb_pmu_enable,
	.pmu_disable	= fsl_emb_pmu_disable,
	.event_init	= fsl_emb_pmu_event_init,
	.add		= fsl_emb_pmu_add,
	.del		= fsl_emb_pmu_del,
	.start		= fsl_emb_pmu_start,
	.stop		= fsl_emb_pmu_stop,
	.पढ़ो		= fsl_emb_pmu_पढ़ो,
पूर्ण;

/*
 * A counter has overflowed; update its count and record
 * things अगर requested.  Note that पूर्णांकerrupts are hard-disabled
 * here so there is no possibility of being पूर्णांकerrupted.
 */
अटल व्योम record_and_restart(काष्ठा perf_event *event, अचिन्हित दीर्घ val,
			       काष्ठा pt_regs *regs)
अणु
	u64 period = event->hw.sample_period;
	s64 prev, delta, left;
	पूर्णांक record = 0;

	अगर (event->hw.state & PERF_HES_STOPPED) अणु
		ग_लिखो_pmc(event->hw.idx, 0);
		वापस;
	पूर्ण

	/* we करोn't have to worry about पूर्णांकerrupts here */
	prev = local64_पढ़ो(&event->hw.prev_count);
	delta = (val - prev) & 0xfffffffful;
	local64_add(delta, &event->count);

	/*
	 * See अगर the total period क्रम this event has expired,
	 * and update क्रम the next period.
	 */
	val = 0;
	left = local64_पढ़ो(&event->hw.period_left) - delta;
	अगर (period) अणु
		अगर (left <= 0) अणु
			left += period;
			अगर (left <= 0)
				left = period;
			record = 1;
			event->hw.last_period = event->hw.sample_period;
		पूर्ण
		अगर (left < 0x80000000LL)
			val = 0x80000000LL - left;
	पूर्ण

	ग_लिखो_pmc(event->hw.idx, val);
	local64_set(&event->hw.prev_count, val);
	local64_set(&event->hw.period_left, left);
	perf_event_update_userpage(event);

	/*
	 * Finally record data अगर requested.
	 */
	अगर (record) अणु
		काष्ठा perf_sample_data data;

		perf_sample_data_init(&data, 0, event->hw.last_period);

		अगर (perf_event_overflow(event, &data, regs))
			fsl_emb_pmu_stop(event, 0);
	पूर्ण
पूर्ण

अटल व्योम perf_event_पूर्णांकerrupt(काष्ठा pt_regs *regs)
अणु
	पूर्णांक i;
	काष्ठा cpu_hw_events *cpuhw = this_cpu_ptr(&cpu_hw_events);
	काष्ठा perf_event *event;
	अचिन्हित दीर्घ val;
	पूर्णांक found = 0;

	क्रम (i = 0; i < ppmu->n_counter; ++i) अणु
		event = cpuhw->event[i];

		val = पढ़ो_pmc(i);
		अगर ((पूर्णांक)val < 0) अणु
			अगर (event) अणु
				/* event has overflowed */
				found = 1;
				record_and_restart(event, val, regs);
			पूर्ण अन्यथा अणु
				/*
				 * Disabled counter is negative,
				 * reset it just in हाल.
				 */
				ग_लिखो_pmc(i, 0);
			पूर्ण
		पूर्ण
	पूर्ण

	/* PMM will keep counters frozen until we वापस from the पूर्णांकerrupt. */
	mपंचांगsr(mfmsr() | MSR_PMM);
	mtpmr(PMRN_PMGC0, PMGC0_PMIE | PMGC0_FCECE);
	isync();
पूर्ण

व्योम hw_perf_event_setup(पूर्णांक cpu)
अणु
	काष्ठा cpu_hw_events *cpuhw = &per_cpu(cpu_hw_events, cpu);

	स_रखो(cpuhw, 0, माप(*cpuhw));
पूर्ण

पूर्णांक रेजिस्टर_fsl_emb_pmu(काष्ठा fsl_emb_pmu *pmu)
अणु
	अगर (ppmu)
		वापस -EBUSY;		/* something's alपढ़ोy रेजिस्टरed */

	ppmu = pmu;
	pr_info("%s performance monitor hardware support registered\n",
		pmu->name);

	perf_pmu_रेजिस्टर(&fsl_emb_pmu, "cpu", PERF_TYPE_RAW);

	वापस 0;
पूर्ण
