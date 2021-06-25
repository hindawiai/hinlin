<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * check TSC synchronization.
 *
 * Copyright (C) 2006, Red Hat, Inc., Ingo Molnar
 *
 * We check whether all boot CPUs have their TSC's synchronized,
 * prपूर्णांक a warning अगर not and turn off the TSC घड़ी-source.
 *
 * The warp-check is poपूर्णांक-to-poपूर्णांक between two CPUs, the CPU
 * initiating the bootup is the 'source CPU', the freshly booting
 * CPU is the 'target CPU'.
 *
 * Only two CPUs may participate - they can enter in any order.
 * ( The serial nature of the boot logic and the CPU hotplug lock
 *   protects against more than 2 CPUs entering this code. )
 */
#समावेश <linux/topology.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kernel.h>
#समावेश <linux/smp.h>
#समावेश <linux/nmi.h>
#समावेश <यंत्र/tsc.h>

काष्ठा tsc_adjust अणु
	s64		bootval;
	s64		adjusted;
	अचिन्हित दीर्घ	nextcheck;
	bool		warned;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा tsc_adjust, tsc_adjust);

/*
 * TSC's on dअगरferent sockets may be reset asynchronously.
 * This may cause the TSC ADJUST value on socket 0 to be NOT 0.
 */
bool __पढ़ो_mostly tsc_async_resets;

व्योम mark_tsc_async_resets(अक्षर *reason)
अणु
	अगर (tsc_async_resets)
		वापस;
	tsc_async_resets = true;
	pr_info("tsc: Marking TSC async resets true due to %s\n", reason);
पूर्ण

व्योम tsc_verअगरy_tsc_adjust(bool resume)
अणु
	काष्ठा tsc_adjust *adj = this_cpu_ptr(&tsc_adjust);
	s64 curval;

	अगर (!boot_cpu_has(X86_FEATURE_TSC_ADJUST))
		वापस;

	/* Skip unnecessary error messages अगर TSC alपढ़ोy unstable */
	अगर (check_tsc_unstable())
		वापस;

	/* Rate limit the MSR check */
	अगर (!resume && समय_beक्रमe(jअगरfies, adj->nextcheck))
		वापस;

	adj->nextcheck = jअगरfies + HZ;

	rdmsrl(MSR_IA32_TSC_ADJUST, curval);
	अगर (adj->adjusted == curval)
		वापस;

	/* Restore the original value */
	wrmsrl(MSR_IA32_TSC_ADJUST, adj->adjusted);

	अगर (!adj->warned || resume) अणु
		pr_warn(FW_BUG "TSC ADJUST differs: CPU%u %lld --> %lld. Restoring\n",
			smp_processor_id(), adj->adjusted, curval);
		adj->warned = true;
	पूर्ण
पूर्ण

अटल व्योम tsc_sanitize_first_cpu(काष्ठा tsc_adjust *cur, s64 bootval,
				   अचिन्हित पूर्णांक cpu, bool bootcpu)
अणु
	/*
	 * First online CPU in a package stores the boot value in the
	 * adjusपंचांगent value. This value might change later via the sync
	 * mechanism. If that fails we still can yell about boot values not
	 * being consistent.
	 *
	 * On the boot cpu we just क्रमce set the ADJUST value to 0 अगर it's
	 * non zero. We करोn't करो that on non boot cpus because physical
	 * hotplug should have set the ADJUST रेजिस्टर to a value > 0 so
	 * the TSC is in sync with the alपढ़ोy running cpus.
	 *
	 * Also करोn't क्रमce the ADJUST value to zero अगर that is a valid value
	 * क्रम socket 0 as determined by the प्रणाली arch.  This is required
	 * when multiple sockets are reset asynchronously with each other
	 * and socket 0 may not have an TSC ADJUST value of 0.
	 */
	अगर (bootcpu && bootval != 0) अणु
		अगर (likely(!tsc_async_resets)) अणु
			pr_warn(FW_BUG "TSC ADJUST: CPU%u: %lld force to 0\n",
				cpu, bootval);
			wrmsrl(MSR_IA32_TSC_ADJUST, 0);
			bootval = 0;
		पूर्ण अन्यथा अणु
			pr_info("TSC ADJUST: CPU%u: %lld NOT forced to 0\n",
				cpu, bootval);
		पूर्ण
	पूर्ण
	cur->adjusted = bootval;
पूर्ण

#अगर_अघोषित CONFIG_SMP
bool __init tsc_store_and_check_tsc_adjust(bool bootcpu)
अणु
	काष्ठा tsc_adjust *cur = this_cpu_ptr(&tsc_adjust);
	s64 bootval;

	अगर (!boot_cpu_has(X86_FEATURE_TSC_ADJUST))
		वापस false;

	/* Skip unnecessary error messages अगर TSC alपढ़ोy unstable */
	अगर (check_tsc_unstable())
		वापस false;

	rdmsrl(MSR_IA32_TSC_ADJUST, bootval);
	cur->bootval = bootval;
	cur->nextcheck = jअगरfies + HZ;
	tsc_sanitize_first_cpu(cur, bootval, smp_processor_id(), bootcpu);
	वापस false;
पूर्ण

#अन्यथा /* !CONFIG_SMP */

/*
 * Store and check the TSC ADJUST MSR अगर available
 */
bool tsc_store_and_check_tsc_adjust(bool bootcpu)
अणु
	काष्ठा tsc_adjust *ref, *cur = this_cpu_ptr(&tsc_adjust);
	अचिन्हित पूर्णांक refcpu, cpu = smp_processor_id();
	काष्ठा cpumask *mask;
	s64 bootval;

	अगर (!boot_cpu_has(X86_FEATURE_TSC_ADJUST))
		वापस false;

	rdmsrl(MSR_IA32_TSC_ADJUST, bootval);
	cur->bootval = bootval;
	cur->nextcheck = jअगरfies + HZ;
	cur->warned = false;

	/*
	 * If a non-zero TSC value क्रम socket 0 may be valid then the शेष
	 * adjusted value cannot assumed to be zero either.
	 */
	अगर (tsc_async_resets)
		cur->adjusted = bootval;

	/*
	 * Check whether this CPU is the first in a package to come up. In
	 * this हाल करो not check the boot value against another package
	 * because the new package might have been physically hotplugged,
	 * where TSC_ADJUST is expected to be dअगरferent. When called on the
	 * boot CPU topology_core_cpumask() might not be available yet.
	 */
	mask = topology_core_cpumask(cpu);
	refcpu = mask ? cpumask_any_but(mask, cpu) : nr_cpu_ids;

	अगर (refcpu >= nr_cpu_ids) अणु
		tsc_sanitize_first_cpu(cur, bootval, smp_processor_id(),
				       bootcpu);
		वापस false;
	पूर्ण

	ref = per_cpu_ptr(&tsc_adjust, refcpu);
	/*
	 * Compare the boot value and complain अगर it dअगरfers in the
	 * package.
	 */
	अगर (bootval != ref->bootval)
		prपूर्णांकk_once(FW_BUG "TSC ADJUST differs within socket(s), fixing all errors\n");

	/*
	 * The TSC_ADJUST values in a package must be the same. If the boot
	 * value on this newly upcoming CPU dअगरfers from the adjusपंचांगent
	 * value of the alपढ़ोy online CPU in this package, set it to that
	 * adjusted value.
	 */
	अगर (bootval != ref->adjusted) अणु
		cur->adjusted = ref->adjusted;
		wrmsrl(MSR_IA32_TSC_ADJUST, ref->adjusted);
	पूर्ण
	/*
	 * We have the TSCs क्रमced to be in sync on this package. Skip sync
	 * test:
	 */
	वापस true;
पूर्ण

/*
 * Entry/निकास counters that make sure that both CPUs
 * run the measurement code at once:
 */
अटल atomic_t start_count;
अटल atomic_t stop_count;
अटल atomic_t skip_test;
अटल atomic_t test_runs;

/*
 * We use a raw spinlock in this exceptional हाल, because
 * we want to have the fastest, अंतरभूतd, non-debug version
 * of a critical section, to be able to prove TSC समय-warps:
 */
अटल arch_spinlock_t sync_lock = __ARCH_SPIN_LOCK_UNLOCKED;

अटल cycles_t last_tsc;
अटल cycles_t max_warp;
अटल पूर्णांक nr_warps;
अटल पूर्णांक अक्रमom_warps;

/*
 * TSC-warp measurement loop running on both CPUs.  This is not called
 * अगर there is no TSC.
 */
अटल cycles_t check_tsc_warp(अचिन्हित पूर्णांक समयout)
अणु
	cycles_t start, now, prev, end, cur_max_warp = 0;
	पूर्णांक i, cur_warps = 0;

	start = rdtsc_ordered();
	/*
	 * The measurement runs क्रम 'timeout' msecs:
	 */
	end = start + (cycles_t) tsc_khz * समयout;

	क्रम (i = 0; ; i++) अणु
		/*
		 * We take the global lock, measure TSC, save the
		 * previous TSC that was measured (possibly on
		 * another CPU) and update the previous TSC बारtamp.
		 */
		arch_spin_lock(&sync_lock);
		prev = last_tsc;
		now = rdtsc_ordered();
		last_tsc = now;
		arch_spin_unlock(&sync_lock);

		/*
		 * Be nice every now and then (and also check whether
		 * measurement is करोne [we also insert a 10 million
		 * loops safety निकास, so we करोnt lock up in हाल the
		 * TSC पढ़ोout is totally broken]):
		 */
		अगर (unlikely(!(i & 7))) अणु
			अगर (now > end || i > 10000000)
				अवरोध;
			cpu_relax();
			touch_nmi_watchकरोg();
		पूर्ण
		/*
		 * Outside the critical section we can now see whether
		 * we saw a समय-warp of the TSC going backwards:
		 */
		अगर (unlikely(prev > now)) अणु
			arch_spin_lock(&sync_lock);
			max_warp = max(max_warp, prev - now);
			cur_max_warp = max_warp;
			/*
			 * Check whether this bounces back and क्रमth. Only
			 * one CPU should observe समय going backwards.
			 */
			अगर (cur_warps != nr_warps)
				अक्रमom_warps++;
			nr_warps++;
			cur_warps = nr_warps;
			arch_spin_unlock(&sync_lock);
		पूर्ण
	पूर्ण
	WARN(!(now-start),
		"Warning: zero tsc calibration delta: %Ld [max: %Ld]\n",
			now-start, end-start);
	वापस cur_max_warp;
पूर्ण

/*
 * If the target CPU coming online करोesn't have any of its core-siblings
 * online, a समयout of 20msec will be used क्रम the TSC-warp measurement
 * loop. Otherwise a smaller समयout of 2msec will be used, as we have some
 * inक्रमmation about this socket alपढ़ोy (and this inक्रमmation grows as we
 * have more and more logical-siblings in that socket).
 *
 * Ideally we should be able to skip the TSC sync check on the other
 * core-siblings, अगर the first logical CPU in a socket passed the sync test.
 * But as the TSC is per-logical CPU and can potentially be modअगरied wrongly
 * by the bios, TSC sync test क्रम smaller duration should be able
 * to catch such errors. Also this will catch the condition where all the
 * cores in the socket करोn't get reset at the same समय.
 */
अटल अंतरभूत अचिन्हित पूर्णांक loop_समयout(पूर्णांक cpu)
अणु
	वापस (cpumask_weight(topology_core_cpumask(cpu)) > 1) ? 2 : 20;
पूर्ण

/*
 * Source CPU calls पूर्णांकo this - it रुकोs क्रम the freshly booted
 * target CPU to arrive and then starts the measurement:
 */
व्योम check_tsc_sync_source(पूर्णांक cpu)
अणु
	पूर्णांक cpus = 2;

	/*
	 * No need to check अगर we alपढ़ोy know that the TSC is not
	 * synchronized or अगर we have no TSC.
	 */
	अगर (unsynchronized_tsc())
		वापस;

	/*
	 * Set the maximum number of test runs to
	 *  1 अगर the CPU करोes not provide the TSC_ADJUST MSR
	 *  3 अगर the MSR is available, so the target can try to adjust
	 */
	अगर (!boot_cpu_has(X86_FEATURE_TSC_ADJUST))
		atomic_set(&test_runs, 1);
	अन्यथा
		atomic_set(&test_runs, 3);
retry:
	/*
	 * Wait क्रम the target to start or to skip the test:
	 */
	जबतक (atomic_पढ़ो(&start_count) != cpus - 1) अणु
		अगर (atomic_पढ़ो(&skip_test) > 0) अणु
			atomic_set(&skip_test, 0);
			वापस;
		पूर्ण
		cpu_relax();
	पूर्ण

	/*
	 * Trigger the target to जारी पूर्णांकo the measurement too:
	 */
	atomic_inc(&start_count);

	check_tsc_warp(loop_समयout(cpu));

	जबतक (atomic_पढ़ो(&stop_count) != cpus-1)
		cpu_relax();

	/*
	 * If the test was successful set the number of runs to zero and
	 * stop. If not, decrement the number of runs an check अगर we can
	 * retry. In हाल of अक्रमom warps no retry is attempted.
	 */
	अगर (!nr_warps) अणु
		atomic_set(&test_runs, 0);

		pr_debug("TSC synchronization [CPU#%d -> CPU#%d]: passed\n",
			smp_processor_id(), cpu);

	पूर्ण अन्यथा अगर (atomic_dec_and_test(&test_runs) || अक्रमom_warps) अणु
		/* Force it to 0 अगर अक्रमom warps brought us here */
		atomic_set(&test_runs, 0);

		pr_warn("TSC synchronization [CPU#%d -> CPU#%d]:\n",
			smp_processor_id(), cpu);
		pr_warn("Measured %Ld cycles TSC warp between CPUs, "
			"turning off TSC clock.\n", max_warp);
		अगर (अक्रमom_warps)
			pr_warn("TSC warped randomly between CPUs\n");
		mark_tsc_unstable("check_tsc_sync_source failed");
	पूर्ण

	/*
	 * Reset it - just in हाल we boot another CPU later:
	 */
	atomic_set(&start_count, 0);
	अक्रमom_warps = 0;
	nr_warps = 0;
	max_warp = 0;
	last_tsc = 0;

	/*
	 * Let the target जारी with the bootup:
	 */
	atomic_inc(&stop_count);

	/*
	 * Retry, अगर there is a chance to करो so.
	 */
	अगर (atomic_पढ़ो(&test_runs) > 0)
		जाओ retry;
पूर्ण

/*
 * Freshly booted CPUs call पूर्णांकo this:
 */
व्योम check_tsc_sync_target(व्योम)
अणु
	काष्ठा tsc_adjust *cur = this_cpu_ptr(&tsc_adjust);
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	cycles_t cur_max_warp, gbl_max_warp;
	पूर्णांक cpus = 2;

	/* Also पातs अगर there is no TSC. */
	अगर (unsynchronized_tsc())
		वापस;

	/*
	 * Store, verअगरy and sanitize the TSC adjust रेजिस्टर. If
	 * successful skip the test.
	 *
	 * The test is also skipped when the TSC is marked reliable. This
	 * is true क्रम SoCs which have no fallback घड़ीsource. On these
	 * SoCs the TSC is frequency synchronized, but still the TSC ADJUST
	 * रेजिस्टर might have been wreckaged by the BIOS..
	 */
	अगर (tsc_store_and_check_tsc_adjust(false) || tsc_घड़ीsource_reliable) अणु
		atomic_inc(&skip_test);
		वापस;
	पूर्ण

retry:
	/*
	 * Register this CPU's participation and रुको क्रम the
	 * source CPU to start the measurement:
	 */
	atomic_inc(&start_count);
	जबतक (atomic_पढ़ो(&start_count) != cpus)
		cpu_relax();

	cur_max_warp = check_tsc_warp(loop_समयout(cpu));

	/*
	 * Store the maximum observed warp value क्रम a potential retry:
	 */
	gbl_max_warp = max_warp;

	/*
	 * Ok, we are करोne:
	 */
	atomic_inc(&stop_count);

	/*
	 * Wait क्रम the source CPU to prपूर्णांक stuff:
	 */
	जबतक (atomic_पढ़ो(&stop_count) != cpus)
		cpu_relax();

	/*
	 * Reset it क्रम the next sync test:
	 */
	atomic_set(&stop_count, 0);

	/*
	 * Check the number of reमुख्यing test runs. If not zero, the test
	 * failed and a retry with adjusted TSC is possible. If zero the
	 * test was either successful or failed terminally.
	 */
	अगर (!atomic_पढ़ो(&test_runs))
		वापस;

	/*
	 * If the warp value of this CPU is 0, then the other CPU
	 * observed समय going backwards so this TSC was ahead and
	 * needs to move backwards.
	 */
	अगर (!cur_max_warp)
		cur_max_warp = -gbl_max_warp;

	/*
	 * Add the result to the previous adjusपंचांगent value.
	 *
	 * The adjusपंचांगent value is slightly off by the overhead of the
	 * sync mechanism (observed values are ~200 TSC cycles), but this
	 * really depends on CPU, node distance and frequency. So
	 * compensating क्रम this is hard to get right. Experiments show
	 * that the warp is not दीर्घer detectable when the observed warp
	 * value is used. In the worst हाल the adjusपंचांगent needs to go
	 * through a 3rd run क्रम fine tuning.
	 */
	cur->adjusted += cur_max_warp;

	pr_warn("TSC ADJUST compensate: CPU%u observed %lld warp. Adjust: %lld\n",
		cpu, cur_max_warp, cur->adjusted);

	wrmsrl(MSR_IA32_TSC_ADJUST, cur->adjusted);
	जाओ retry;

पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */
