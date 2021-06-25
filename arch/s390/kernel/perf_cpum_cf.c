<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Perक्रमmance event support क्रम s390x - CPU-measurement Counter Facility
 *
 *  Copyright IBM Corp. 2012, 2019
 *  Author(s): Hendrik Brueckner <brueckner@linux.ibm.com>
 */
#घोषणा KMSG_COMPONENT	"cpum_cf"
#घोषणा pr_fmt(fmt)	KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/percpu.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/cpu_mcf.h>

अटल क्रमागत cpumf_ctr_set get_counter_set(u64 event)
अणु
	पूर्णांक set = CPUMF_CTR_SET_MAX;

	अगर (event < 32)
		set = CPUMF_CTR_SET_BASIC;
	अन्यथा अगर (event < 64)
		set = CPUMF_CTR_SET_USER;
	अन्यथा अगर (event < 128)
		set = CPUMF_CTR_SET_CRYPTO;
	अन्यथा अगर (event < 288)
		set = CPUMF_CTR_SET_EXT;
	अन्यथा अगर (event >= 448 && event < 496)
		set = CPUMF_CTR_SET_MT_DIAG;

	वापस set;
पूर्ण

अटल पूर्णांक validate_ctr_version(स्थिर काष्ठा hw_perf_event *hwc)
अणु
	काष्ठा cpu_cf_events *cpuhw;
	पूर्णांक err = 0;
	u16 mtdiag_ctl;

	cpuhw = &get_cpu_var(cpu_cf_events);

	/* check required version क्रम counter sets */
	चयन (hwc->config_base) अणु
	हाल CPUMF_CTR_SET_BASIC:
	हाल CPUMF_CTR_SET_USER:
		अगर (cpuhw->info.cfvn < 1)
			err = -EOPNOTSUPP;
		अवरोध;
	हाल CPUMF_CTR_SET_CRYPTO:
		अगर ((cpuhw->info.csvn >= 1 && cpuhw->info.csvn <= 5 &&
		     hwc->config > 79) ||
		    (cpuhw->info.csvn >= 6 && hwc->config > 83))
			err = -EOPNOTSUPP;
		अवरोध;
	हाल CPUMF_CTR_SET_EXT:
		अगर (cpuhw->info.csvn < 1)
			err = -EOPNOTSUPP;
		अगर ((cpuhw->info.csvn == 1 && hwc->config > 159) ||
		    (cpuhw->info.csvn == 2 && hwc->config > 175) ||
		    (cpuhw->info.csvn >= 3 && cpuhw->info.csvn <= 5
		     && hwc->config > 255) ||
		    (cpuhw->info.csvn >= 6 && hwc->config > 287))
			err = -EOPNOTSUPP;
		अवरोध;
	हाल CPUMF_CTR_SET_MT_DIAG:
		अगर (cpuhw->info.csvn <= 3)
			err = -EOPNOTSUPP;
		/*
		 * MT-diagnostic counters are पढ़ो-only.  The counter set
		 * is स्वतःmatically enabled and activated on all CPUs with
		 * multithपढ़ोing (SMT).  Deactivation of multithपढ़ोing
		 * also disables the counter set.  State changes are ignored
		 * by lcctl().	Because Linux controls SMT enablement through
		 * a kernel parameter only, the counter set is either disabled
		 * or enabled and active.
		 *
		 * Thus, the counters can only be used अगर SMT is on and the
		 * counter set is enabled and active.
		 */
		mtdiag_ctl = cpumf_ctr_ctl[CPUMF_CTR_SET_MT_DIAG];
		अगर (!((cpuhw->info.auth_ctl & mtdiag_ctl) &&
		      (cpuhw->info.enable_ctl & mtdiag_ctl) &&
		      (cpuhw->info.act_ctl & mtdiag_ctl)))
			err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	put_cpu_var(cpu_cf_events);
	वापस err;
पूर्ण

अटल पूर्णांक validate_ctr_auth(स्थिर काष्ठा hw_perf_event *hwc)
अणु
	काष्ठा cpu_cf_events *cpuhw;
	u64 ctrs_state;
	पूर्णांक err = 0;

	cpuhw = &get_cpu_var(cpu_cf_events);

	/* Check authorization क्रम cpu counter sets.
	 * If the particular CPU counter set is not authorized,
	 * वापस with -ENOENT in order to fall back to other
	 * PMUs that might suffice the event request.
	 */
	ctrs_state = cpumf_ctr_ctl[hwc->config_base];
	अगर (!(ctrs_state & cpuhw->info.auth_ctl))
		err = -ENOENT;

	put_cpu_var(cpu_cf_events);
	वापस err;
पूर्ण

/*
 * Change the CPUMF state to active.
 * Enable and activate the CPU-counter sets according
 * to the per-cpu control state.
 */
अटल व्योम cpumf_pmu_enable(काष्ठा pmu *pmu)
अणु
	काष्ठा cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);
	पूर्णांक err;

	अगर (cpuhw->flags & PMU_F_ENABLED)
		वापस;

	err = lcctl(cpuhw->state);
	अगर (err) अणु
		pr_err("Enabling the performance measuring unit "
		       "failed with rc=%x\n", err);
		वापस;
	पूर्ण

	cpuhw->flags |= PMU_F_ENABLED;
पूर्ण

/*
 * Change the CPUMF state to inactive.
 * Disable and enable (inactive) the CPU-counter sets according
 * to the per-cpu control state.
 */
अटल व्योम cpumf_pmu_disable(काष्ठा pmu *pmu)
अणु
	काष्ठा cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);
	पूर्णांक err;
	u64 inactive;

	अगर (!(cpuhw->flags & PMU_F_ENABLED))
		वापस;

	inactive = cpuhw->state & ~((1 << CPUMF_LCCTL_ENABLE_SHIFT) - 1);
	err = lcctl(inactive);
	अगर (err) अणु
		pr_err("Disabling the performance measuring unit "
		       "failed with rc=%x\n", err);
		वापस;
	पूर्ण

	cpuhw->flags &= ~PMU_F_ENABLED;
पूर्ण


/* Number of perf events counting hardware events */
अटल atomic_t num_events = ATOMIC_INIT(0);
/* Used to aव्योम races in calling reserve/release_cpumf_hardware */
अटल DEFINE_MUTEX(pmc_reserve_mutex);

/* Release the PMU अगर event is the last perf event */
अटल व्योम hw_perf_event_destroy(काष्ठा perf_event *event)
अणु
	अगर (!atomic_add_unless(&num_events, -1, 1)) अणु
		mutex_lock(&pmc_reserve_mutex);
		अगर (atomic_dec_वापस(&num_events) == 0)
			__kernel_cpumcf_end();
		mutex_unlock(&pmc_reserve_mutex);
	पूर्ण
पूर्ण

/* CPUMF <-> perf event mappings क्रम kernel+userspace (basic set) */
अटल स्थिर पूर्णांक cpumf_generic_events_basic[] = अणु
	[PERF_COUNT_HW_CPU_CYCLES]	    = 0,
	[PERF_COUNT_HW_INSTRUCTIONS]	    = 1,
	[PERF_COUNT_HW_CACHE_REFERENCES]    = -1,
	[PERF_COUNT_HW_CACHE_MISSES]	    = -1,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] = -1,
	[PERF_COUNT_HW_BRANCH_MISSES]	    = -1,
	[PERF_COUNT_HW_BUS_CYCLES]	    = -1,
पूर्ण;
/* CPUMF <-> perf event mappings क्रम userspace (problem-state set) */
अटल स्थिर पूर्णांक cpumf_generic_events_user[] = अणु
	[PERF_COUNT_HW_CPU_CYCLES]	    = 32,
	[PERF_COUNT_HW_INSTRUCTIONS]	    = 33,
	[PERF_COUNT_HW_CACHE_REFERENCES]    = -1,
	[PERF_COUNT_HW_CACHE_MISSES]	    = -1,
	[PERF_COUNT_HW_BRANCH_INSTRUCTIONS] = -1,
	[PERF_COUNT_HW_BRANCH_MISSES]	    = -1,
	[PERF_COUNT_HW_BUS_CYCLES]	    = -1,
पूर्ण;

अटल पूर्णांक __hw_perf_event_init(काष्ठा perf_event *event, अचिन्हित पूर्णांक type)
अणु
	काष्ठा perf_event_attr *attr = &event->attr;
	काष्ठा hw_perf_event *hwc = &event->hw;
	क्रमागत cpumf_ctr_set set;
	पूर्णांक err = 0;
	u64 ev;

	चयन (type) अणु
	हाल PERF_TYPE_RAW:
		/* Raw events are used to access counters directly,
		 * hence करो not permit excludes */
		अगर (attr->exclude_kernel || attr->exclude_user ||
		    attr->exclude_hv)
			वापस -EOPNOTSUPP;
		ev = attr->config;
		अवरोध;

	हाल PERF_TYPE_HARDWARE:
		अगर (is_sampling_event(event))	/* No sampling support */
			वापस -ENOENT;
		ev = attr->config;
		/* Count user space (problem-state) only */
		अगर (!attr->exclude_user && attr->exclude_kernel) अणु
			अगर (ev >= ARRAY_SIZE(cpumf_generic_events_user))
				वापस -EOPNOTSUPP;
			ev = cpumf_generic_events_user[ev];

		/* No support क्रम kernel space counters only */
		पूर्ण अन्यथा अगर (!attr->exclude_kernel && attr->exclude_user) अणु
			वापस -EOPNOTSUPP;
		पूर्ण अन्यथा अणु	/* Count user and kernel space */
			अगर (ev >= ARRAY_SIZE(cpumf_generic_events_basic))
				वापस -EOPNOTSUPP;
			ev = cpumf_generic_events_basic[ev];
		पूर्ण
		अवरोध;

	शेष:
		वापस -ENOENT;
	पूर्ण

	अगर (ev == -1)
		वापस -ENOENT;

	अगर (ev > PERF_CPUM_CF_MAX_CTR)
		वापस -ENOENT;

	/* Obtain the counter set to which the specअगरied counter beदीर्घs */
	set = get_counter_set(ev);
	चयन (set) अणु
	हाल CPUMF_CTR_SET_BASIC:
	हाल CPUMF_CTR_SET_USER:
	हाल CPUMF_CTR_SET_CRYPTO:
	हाल CPUMF_CTR_SET_EXT:
	हाल CPUMF_CTR_SET_MT_DIAG:
		/*
		 * Use the hardware perf event काष्ठाure to store the
		 * counter number in the 'config' member and the counter
		 * set number in the 'config_base'.  The counter set number
		 * is then later used to enable/disable the counter(s).
		 */
		hwc->config = ev;
		hwc->config_base = set;
		अवरोध;
	हाल CPUMF_CTR_SET_MAX:
		/* The counter could not be associated to a counter set */
		वापस -EINVAL;
	पूर्ण

	/* Initialize क्रम using the CPU-measurement counter facility */
	अगर (!atomic_inc_not_zero(&num_events)) अणु
		mutex_lock(&pmc_reserve_mutex);
		अगर (atomic_पढ़ो(&num_events) == 0 && __kernel_cpumcf_begin())
			err = -EBUSY;
		अन्यथा
			atomic_inc(&num_events);
		mutex_unlock(&pmc_reserve_mutex);
	पूर्ण
	अगर (err)
		वापस err;
	event->destroy = hw_perf_event_destroy;

	/* Finally, validate version and authorization of the counter set */
	err = validate_ctr_auth(hwc);
	अगर (!err)
		err = validate_ctr_version(hwc);

	वापस err;
पूर्ण

अटल पूर्णांक cpumf_pmu_event_init(काष्ठा perf_event *event)
अणु
	अचिन्हित पूर्णांक type = event->attr.type;
	पूर्णांक err;

	अगर (type == PERF_TYPE_HARDWARE || type == PERF_TYPE_RAW)
		err = __hw_perf_event_init(event, type);
	अन्यथा अगर (event->pmu->type == type)
		/* Registered as unknown PMU */
		err = __hw_perf_event_init(event, PERF_TYPE_RAW);
	अन्यथा
		वापस -ENOENT;

	अगर (unlikely(err) && event->destroy)
		event->destroy(event);

	वापस err;
पूर्ण

अटल पूर्णांक hw_perf_event_reset(काष्ठा perf_event *event)
अणु
	u64 prev, new;
	पूर्णांक err;

	करो अणु
		prev = local64_पढ़ो(&event->hw.prev_count);
		err = ecctr(event->hw.config, &new);
		अगर (err) अणु
			अगर (err != 3)
				अवरोध;
			/* The counter is not (yet) available. This
			 * might happen अगर the counter set to which
			 * this counter beदीर्घs is in the disabled
			 * state.
			 */
			new = 0;
		पूर्ण
	पूर्ण जबतक (local64_cmpxchg(&event->hw.prev_count, prev, new) != prev);

	वापस err;
पूर्ण

अटल व्योम hw_perf_event_update(काष्ठा perf_event *event)
अणु
	u64 prev, new, delta;
	पूर्णांक err;

	करो अणु
		prev = local64_पढ़ो(&event->hw.prev_count);
		err = ecctr(event->hw.config, &new);
		अगर (err)
			वापस;
	पूर्ण जबतक (local64_cmpxchg(&event->hw.prev_count, prev, new) != prev);

	delta = (prev <= new) ? new - prev
			      : (-1ULL - prev) + new + 1;	 /* overflow */
	local64_add(delta, &event->count);
पूर्ण

अटल व्योम cpumf_pmu_पढ़ो(काष्ठा perf_event *event)
अणु
	अगर (event->hw.state & PERF_HES_STOPPED)
		वापस;

	hw_perf_event_update(event);
पूर्ण

अटल व्योम cpumf_pmu_start(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (WARN_ON_ONCE(!(hwc->state & PERF_HES_STOPPED)))
		वापस;

	अगर (WARN_ON_ONCE(hwc->config == -1))
		वापस;

	अगर (flags & PERF_EF_RELOAD)
		WARN_ON_ONCE(!(hwc->state & PERF_HES_UPTODATE));

	hwc->state = 0;

	/* (Re-)enable and activate the counter set */
	ctr_set_enable(&cpuhw->state, hwc->config_base);
	ctr_set_start(&cpuhw->state, hwc->config_base);

	/* The counter set to which this counter beदीर्घs can be alपढ़ोy active.
	 * Because all counters in a set are active, the event->hw.prev_count
	 * needs to be synchronized.  At this poपूर्णांक, the counter set can be in
	 * the inactive or disabled state.
	 */
	hw_perf_event_reset(event);

	/* increment refcount क्रम this counter set */
	atomic_inc(&cpuhw->ctr_set[hwc->config_base]);
पूर्ण

अटल व्योम cpumf_pmu_stop(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);
	काष्ठा hw_perf_event *hwc = &event->hw;

	अगर (!(hwc->state & PERF_HES_STOPPED)) अणु
		/* Decrement reference count क्रम this counter set and अगर this
		 * is the last used counter in the set, clear activation
		 * control and set the counter set state to inactive.
		 */
		अगर (!atomic_dec_वापस(&cpuhw->ctr_set[hwc->config_base]))
			ctr_set_stop(&cpuhw->state, hwc->config_base);
		hwc->state |= PERF_HES_STOPPED;
	पूर्ण

	अगर ((flags & PERF_EF_UPDATE) && !(hwc->state & PERF_HES_UPTODATE)) अणु
		hw_perf_event_update(event);
		hwc->state |= PERF_HES_UPTODATE;
	पूर्ण
पूर्ण

अटल पूर्णांक cpumf_pmu_add(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);

	/* Check authorization क्रम the counter set to which this
	 * counter beदीर्घs.
	 * For group events transaction, the authorization check is
	 * करोne in cpumf_pmu_commit_txn().
	 */
	अगर (!(cpuhw->txn_flags & PERF_PMU_TXN_ADD))
		अगर (validate_ctr_auth(&event->hw))
			वापस -ENOENT;

	ctr_set_enable(&cpuhw->state, event->hw.config_base);
	event->hw.state = PERF_HES_UPTODATE | PERF_HES_STOPPED;

	अगर (flags & PERF_EF_START)
		cpumf_pmu_start(event, PERF_EF_RELOAD);

	वापस 0;
पूर्ण

अटल व्योम cpumf_pmu_del(काष्ठा perf_event *event, पूर्णांक flags)
अणु
	काष्ठा cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);

	cpumf_pmu_stop(event, PERF_EF_UPDATE);

	/* Check अगर any counter in the counter set is still used.  If not used,
	 * change the counter set to the disabled state.  This also clears the
	 * content of all counters in the set.
	 *
	 * When a new perf event has been added but not yet started, this can
	 * clear enable control and resets all counters in a set.  Thereक्रमe,
	 * cpumf_pmu_start() always has to reenable a counter set.
	 */
	अगर (!atomic_पढ़ो(&cpuhw->ctr_set[event->hw.config_base]))
		ctr_set_disable(&cpuhw->state, event->hw.config_base);
पूर्ण

/*
 * Start group events scheduling transaction.
 * Set flags to perक्रमm a single test at commit समय.
 *
 * We only support PERF_PMU_TXN_ADD transactions. Save the
 * transaction flags but otherwise ignore non-PERF_PMU_TXN_ADD
 * transactions.
 */
अटल व्योम cpumf_pmu_start_txn(काष्ठा pmu *pmu, अचिन्हित पूर्णांक txn_flags)
अणु
	काष्ठा cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);

	WARN_ON_ONCE(cpuhw->txn_flags);		/* txn alपढ़ोy in flight */

	cpuhw->txn_flags = txn_flags;
	अगर (txn_flags & ~PERF_PMU_TXN_ADD)
		वापस;

	perf_pmu_disable(pmu);
	cpuhw->tx_state = cpuhw->state;
पूर्ण

/*
 * Stop and cancel a group events scheduling tranctions.
 * Assumes cpumf_pmu_del() is called क्रम each successful added
 * cpumf_pmu_add() during the transaction.
 */
अटल व्योम cpumf_pmu_cancel_txn(काष्ठा pmu *pmu)
अणु
	अचिन्हित पूर्णांक txn_flags;
	काष्ठा cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);

	WARN_ON_ONCE(!cpuhw->txn_flags);	/* no txn in flight */

	txn_flags = cpuhw->txn_flags;
	cpuhw->txn_flags = 0;
	अगर (txn_flags & ~PERF_PMU_TXN_ADD)
		वापस;

	WARN_ON(cpuhw->tx_state != cpuhw->state);

	perf_pmu_enable(pmu);
पूर्ण

/*
 * Commit the group events scheduling transaction.  On success, the
 * transaction is बंदd.   On error, the transaction is kept खोलो
 * until cpumf_pmu_cancel_txn() is called.
 */
अटल पूर्णांक cpumf_pmu_commit_txn(काष्ठा pmu *pmu)
अणु
	काष्ठा cpu_cf_events *cpuhw = this_cpu_ptr(&cpu_cf_events);
	u64 state;

	WARN_ON_ONCE(!cpuhw->txn_flags);	/* no txn in flight */

	अगर (cpuhw->txn_flags & ~PERF_PMU_TXN_ADD) अणु
		cpuhw->txn_flags = 0;
		वापस 0;
	पूर्ण

	/* check अगर the updated state can be scheduled */
	state = cpuhw->state & ~((1 << CPUMF_LCCTL_ENABLE_SHIFT) - 1);
	state >>= CPUMF_LCCTL_ENABLE_SHIFT;
	अगर ((state & cpuhw->info.auth_ctl) != state)
		वापस -ENOENT;

	cpuhw->txn_flags = 0;
	perf_pmu_enable(pmu);
	वापस 0;
पूर्ण

/* Perक्रमmance monitoring unit क्रम s390x */
अटल काष्ठा pmu cpumf_pmu = अणु
	.task_ctx_nr  = perf_sw_context,
	.capabilities = PERF_PMU_CAP_NO_INTERRUPT,
	.pmu_enable   = cpumf_pmu_enable,
	.pmu_disable  = cpumf_pmu_disable,
	.event_init   = cpumf_pmu_event_init,
	.add	      = cpumf_pmu_add,
	.del	      = cpumf_pmu_del,
	.start	      = cpumf_pmu_start,
	.stop	      = cpumf_pmu_stop,
	.पढ़ो	      = cpumf_pmu_पढ़ो,
	.start_txn    = cpumf_pmu_start_txn,
	.commit_txn   = cpumf_pmu_commit_txn,
	.cancel_txn   = cpumf_pmu_cancel_txn,
पूर्ण;

अटल पूर्णांक __init cpumf_pmu_init(व्योम)
अणु
	पूर्णांक rc;

	अगर (!kernel_cpumcf_avail())
		वापस -ENODEV;

	cpumf_pmu.attr_groups = cpumf_cf_event_group();
	rc = perf_pmu_रेजिस्टर(&cpumf_pmu, "cpum_cf", -1);
	अगर (rc)
		pr_err("Registering the cpum_cf PMU failed with rc=%i\n", rc);
	वापस rc;
पूर्ण
subsys_initcall(cpumf_pmu_init);
