<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/common/mcpm_entry.c -- entry poपूर्णांक क्रम multi-cluster PM
 *
 * Created by:  Nicolas Pitre, March 2012
 * Copyright:   (C) 2012-2013  Linaro Limited
 */

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/cpu_pm.h>

#समावेश <यंत्र/mcpm.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/idmap.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/suspend.h>

/*
 * The खुला API क्रम this code is करोcumented in arch/arm/include/यंत्र/mcpm.h.
 * For a comprehensive description of the मुख्य algorithm used here, please
 * see Documentation/arm/cluster-pm-race-aव्योमance.rst.
 */

काष्ठा sync_काष्ठा mcpm_sync;

/*
 * __mcpm_cpu_going_करोwn: Indicates that the cpu is being torn करोwn.
 *    This must be called at the poपूर्णांक of committing to tearकरोwn of a CPU.
 *    The CPU cache (SCTRL.C bit) is expected to still be active.
 */
अटल व्योम __mcpm_cpu_going_करोwn(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster)
अणु
	mcpm_sync.clusters[cluster].cpus[cpu].cpu = CPU_GOING_DOWN;
	sync_cache_w(&mcpm_sync.clusters[cluster].cpus[cpu].cpu);
पूर्ण

/*
 * __mcpm_cpu_करोwn: Indicates that cpu tearकरोwn is complete and that the
 *    cluster can be torn करोwn without disrupting this CPU.
 *    To aव्योम deadlocks, this must be called beक्रमe a CPU is घातered करोwn.
 *    The CPU cache (SCTRL.C bit) is expected to be off.
 *    However L2 cache might or might not be active.
 */
अटल व्योम __mcpm_cpu_करोwn(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster)
अणु
	dmb();
	mcpm_sync.clusters[cluster].cpus[cpu].cpu = CPU_DOWN;
	sync_cache_w(&mcpm_sync.clusters[cluster].cpus[cpu].cpu);
	sev();
पूर्ण

/*
 * __mcpm_outbound_leave_critical: Leave the cluster tearकरोwn critical section.
 * @state: the final state of the cluster:
 *     CLUSTER_UP: no deकाष्ठाive tearकरोwn was करोne and the cluster has been
 *         restored to the previous state (CPU cache still active); or
 *     CLUSTER_DOWN: the cluster has been torn-करोwn, पढ़ोy क्रम घातer-off
 *         (CPU cache disabled, L2 cache either enabled or disabled).
 */
अटल व्योम __mcpm_outbound_leave_critical(अचिन्हित पूर्णांक cluster, पूर्णांक state)
अणु
	dmb();
	mcpm_sync.clusters[cluster].cluster = state;
	sync_cache_w(&mcpm_sync.clusters[cluster].cluster);
	sev();
पूर्ण

/*
 * __mcpm_outbound_enter_critical: Enter the cluster tearकरोwn critical section.
 * This function should be called by the last man, after local CPU tearकरोwn
 * is complete.  CPU cache expected to be active.
 *
 * Returns:
 *     false: the critical section was not entered because an inbound CPU was
 *         observed, or the cluster is alपढ़ोy being set up;
 *     true: the critical section was entered: it is now safe to tear करोwn the
 *         cluster.
 */
अटल bool __mcpm_outbound_enter_critical(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster)
अणु
	अचिन्हित पूर्णांक i;
	काष्ठा mcpm_sync_काष्ठा *c = &mcpm_sync.clusters[cluster];

	/* Warn inbound CPUs that the cluster is being torn करोwn: */
	c->cluster = CLUSTER_GOING_DOWN;
	sync_cache_w(&c->cluster);

	/* Back out अगर the inbound cluster is alपढ़ोy in the critical region: */
	sync_cache_r(&c->inbound);
	अगर (c->inbound == INBOUND_COMING_UP)
		जाओ पात;

	/*
	 * Wait क्रम all CPUs to get out of the GOING_DOWN state, so that local
	 * tearकरोwn is complete on each CPU beक्रमe tearing करोwn the cluster.
	 *
	 * If any CPU has been woken up again from the DOWN state, then we
	 * shouldn't be taking the cluster करोwn at all: पात in that हाल.
	 */
	sync_cache_r(&c->cpus);
	क्रम (i = 0; i < MAX_CPUS_PER_CLUSTER; i++) अणु
		पूर्णांक cpustate;

		अगर (i == cpu)
			जारी;

		जबतक (1) अणु
			cpustate = c->cpus[i].cpu;
			अगर (cpustate != CPU_GOING_DOWN)
				अवरोध;

			wfe();
			sync_cache_r(&c->cpus[i].cpu);
		पूर्ण

		चयन (cpustate) अणु
		हाल CPU_DOWN:
			जारी;

		शेष:
			जाओ पात;
		पूर्ण
	पूर्ण

	वापस true;

पात:
	__mcpm_outbound_leave_critical(cluster, CLUSTER_UP);
	वापस false;
पूर्ण

अटल पूर्णांक __mcpm_cluster_state(अचिन्हित पूर्णांक cluster)
अणु
	sync_cache_r(&mcpm_sync.clusters[cluster].cluster);
	वापस mcpm_sync.clusters[cluster].cluster;
पूर्ण

बाह्य अचिन्हित दीर्घ mcpm_entry_vectors[MAX_NR_CLUSTERS][MAX_CPUS_PER_CLUSTER];

व्योम mcpm_set_entry_vector(अचिन्हित cpu, अचिन्हित cluster, व्योम *ptr)
अणु
	अचिन्हित दीर्घ val = ptr ? __pa_symbol(ptr) : 0;
	mcpm_entry_vectors[cluster][cpu] = val;
	sync_cache_w(&mcpm_entry_vectors[cluster][cpu]);
पूर्ण

बाह्य अचिन्हित दीर्घ mcpm_entry_early_pokes[MAX_NR_CLUSTERS][MAX_CPUS_PER_CLUSTER][2];

व्योम mcpm_set_early_poke(अचिन्हित cpu, अचिन्हित cluster,
			 अचिन्हित दीर्घ poke_phys_addr, अचिन्हित दीर्घ poke_val)
अणु
	अचिन्हित दीर्घ *poke = &mcpm_entry_early_pokes[cluster][cpu][0];
	poke[0] = poke_phys_addr;
	poke[1] = poke_val;
	__sync_cache_range_w(poke, 2 * माप(*poke));
पूर्ण

अटल स्थिर काष्ठा mcpm_platक्रमm_ops *platक्रमm_ops;

पूर्णांक __init mcpm_platक्रमm_रेजिस्टर(स्थिर काष्ठा mcpm_platक्रमm_ops *ops)
अणु
	अगर (platक्रमm_ops)
		वापस -EBUSY;
	platक्रमm_ops = ops;
	वापस 0;
पूर्ण

bool mcpm_is_available(व्योम)
अणु
	वापस (platक्रमm_ops) ? true : false;
पूर्ण
EXPORT_SYMBOL_GPL(mcpm_is_available);

/*
 * We can't use regular spinlocks. In the चयनer हाल, it is possible
 * क्रम an outbound CPU to call घातer_करोwn() after its inbound counterpart
 * is alपढ़ोy live using the same logical CPU number which trips lockdep
 * debugging.
 */
अटल arch_spinlock_t mcpm_lock = __ARCH_SPIN_LOCK_UNLOCKED;

अटल पूर्णांक mcpm_cpu_use_count[MAX_NR_CLUSTERS][MAX_CPUS_PER_CLUSTER];

अटल अंतरभूत bool mcpm_cluster_unused(अचिन्हित पूर्णांक cluster)
अणु
	पूर्णांक i, cnt;
	क्रम (i = 0, cnt = 0; i < MAX_CPUS_PER_CLUSTER; i++)
		cnt |= mcpm_cpu_use_count[cluster][i];
	वापस !cnt;
पूर्ण

पूर्णांक mcpm_cpu_घातer_up(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster)
अणु
	bool cpu_is_करोwn, cluster_is_करोwn;
	पूर्णांक ret = 0;

	pr_debug("%s: cpu %u cluster %u\n", __func__, cpu, cluster);
	अगर (!platक्रमm_ops)
		वापस -EUNATCH; /* try not to shaकरोw घातer_up errors */
	might_sleep();

	/*
	 * Since this is called with IRQs enabled, and no arch_spin_lock_irq
	 * variant exists, we need to disable IRQs manually here.
	 */
	local_irq_disable();
	arch_spin_lock(&mcpm_lock);

	cpu_is_करोwn = !mcpm_cpu_use_count[cluster][cpu];
	cluster_is_करोwn = mcpm_cluster_unused(cluster);

	mcpm_cpu_use_count[cluster][cpu]++;
	/*
	 * The only possible values are:
	 * 0 = CPU करोwn
	 * 1 = CPU (still) up
	 * 2 = CPU requested to be up beक्रमe it had a chance
	 *     to actually make itself करोwn.
	 * Any other value is a bug.
	 */
	BUG_ON(mcpm_cpu_use_count[cluster][cpu] != 1 &&
	       mcpm_cpu_use_count[cluster][cpu] != 2);

	अगर (cluster_is_करोwn)
		ret = platक्रमm_ops->cluster_घातerup(cluster);
	अगर (cpu_is_करोwn && !ret)
		ret = platक्रमm_ops->cpu_घातerup(cpu, cluster);

	arch_spin_unlock(&mcpm_lock);
	local_irq_enable();
	वापस ret;
पूर्ण

प्रकार typeof(cpu_reset) phys_reset_t;

व्योम mcpm_cpu_घातer_करोwn(व्योम)
अणु
	अचिन्हित पूर्णांक mpidr, cpu, cluster;
	bool cpu_going_करोwn, last_man;
	phys_reset_t phys_reset;

	mpidr = पढ़ो_cpuid_mpidr();
	cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);
	cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);
	pr_debug("%s: cpu %u cluster %u\n", __func__, cpu, cluster);
	अगर (WARN_ON_ONCE(!platक्रमm_ops))
	       वापस;
	BUG_ON(!irqs_disabled());

	setup_mm_क्रम_reboot();

	__mcpm_cpu_going_करोwn(cpu, cluster);
	arch_spin_lock(&mcpm_lock);
	BUG_ON(__mcpm_cluster_state(cluster) != CLUSTER_UP);

	mcpm_cpu_use_count[cluster][cpu]--;
	BUG_ON(mcpm_cpu_use_count[cluster][cpu] != 0 &&
	       mcpm_cpu_use_count[cluster][cpu] != 1);
	cpu_going_करोwn = !mcpm_cpu_use_count[cluster][cpu];
	last_man = mcpm_cluster_unused(cluster);

	अगर (last_man && __mcpm_outbound_enter_critical(cpu, cluster)) अणु
		platक्रमm_ops->cpu_घातerकरोwn_prepare(cpu, cluster);
		platक्रमm_ops->cluster_घातerकरोwn_prepare(cluster);
		arch_spin_unlock(&mcpm_lock);
		platक्रमm_ops->cluster_cache_disable();
		__mcpm_outbound_leave_critical(cluster, CLUSTER_DOWN);
	पूर्ण अन्यथा अणु
		अगर (cpu_going_करोwn)
			platक्रमm_ops->cpu_घातerकरोwn_prepare(cpu, cluster);
		arch_spin_unlock(&mcpm_lock);
		/*
		 * If cpu_going_करोwn is false here, that means a घातer_up
		 * request raced ahead of us.  Even अगर we करो not want to
		 * shut this CPU करोwn, the caller still expects execution
		 * to वापस through the प्रणाली resume entry path, like
		 * when the WFI is पातed due to a new IRQ or the like..
		 * So let's जारी with cache cleaning in all हालs.
		 */
		platक्रमm_ops->cpu_cache_disable();
	पूर्ण

	__mcpm_cpu_करोwn(cpu, cluster);

	/* Now we are prepared क्रम घातer-करोwn, करो it: */
	अगर (cpu_going_करोwn)
		wfi();

	/*
	 * It is possible क्रम a घातer_up request to happen concurrently
	 * with a घातer_करोwn request क्रम the same CPU. In this हाल the
	 * CPU might not be able to actually enter a घातered करोwn state
	 * with the WFI inकाष्ठाion अगर the घातer_up request has हटाओd
	 * the required reset condition.  We must perक्रमm a re-entry in
	 * the kernel as अगर the घातer_up method just had deनिश्चितed reset
	 * on the CPU.
	 */
	phys_reset = (phys_reset_t)(अचिन्हित दीर्घ)__pa_symbol(cpu_reset);
	phys_reset(__pa_symbol(mcpm_entry_poपूर्णांक), false);

	/* should never get here */
	BUG();
पूर्ण

पूर्णांक mcpm_रुको_क्रम_cpu_घातerकरोwn(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक cluster)
अणु
	पूर्णांक ret;

	अगर (WARN_ON_ONCE(!platक्रमm_ops || !platक्रमm_ops->रुको_क्रम_घातerकरोwn))
		वापस -EUNATCH;

	ret = platक्रमm_ops->रुको_क्रम_घातerकरोwn(cpu, cluster);
	अगर (ret)
		pr_warn("%s: cpu %u, cluster %u failed to power down (%d)\n",
			__func__, cpu, cluster, ret);

	वापस ret;
पूर्ण

व्योम mcpm_cpu_suspend(व्योम)
अणु
	अगर (WARN_ON_ONCE(!platक्रमm_ops))
		वापस;

	/* Some platक्रमms might have to enable special resume modes, etc. */
	अगर (platक्रमm_ops->cpu_suspend_prepare) अणु
		अचिन्हित पूर्णांक mpidr = पढ़ो_cpuid_mpidr();
		अचिन्हित पूर्णांक cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);
		अचिन्हित पूर्णांक cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1); 
		arch_spin_lock(&mcpm_lock);
		platक्रमm_ops->cpu_suspend_prepare(cpu, cluster);
		arch_spin_unlock(&mcpm_lock);
	पूर्ण
	mcpm_cpu_घातer_करोwn();
पूर्ण

पूर्णांक mcpm_cpu_घातered_up(व्योम)
अणु
	अचिन्हित पूर्णांक mpidr, cpu, cluster;
	bool cpu_was_करोwn, first_man;
	अचिन्हित दीर्घ flags;

	अगर (!platक्रमm_ops)
		वापस -EUNATCH;

	mpidr = पढ़ो_cpuid_mpidr();
	cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);
	cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);
	local_irq_save(flags);
	arch_spin_lock(&mcpm_lock);

	cpu_was_करोwn = !mcpm_cpu_use_count[cluster][cpu];
	first_man = mcpm_cluster_unused(cluster);

	अगर (first_man && platक्रमm_ops->cluster_is_up)
		platक्रमm_ops->cluster_is_up(cluster);
	अगर (cpu_was_करोwn)
		mcpm_cpu_use_count[cluster][cpu] = 1;
	अगर (platक्रमm_ops->cpu_is_up)
		platक्रमm_ops->cpu_is_up(cpu, cluster);

	arch_spin_unlock(&mcpm_lock);
	local_irq_restore(flags);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ARM_CPU_SUSPEND

अटल पूर्णांक __init nocache_trampoline(अचिन्हित दीर्घ _arg)
अणु
	व्योम (*cache_disable)(व्योम) = (व्योम *)_arg;
	अचिन्हित पूर्णांक mpidr = पढ़ो_cpuid_mpidr();
	अचिन्हित पूर्णांक cpu = MPIDR_AFFINITY_LEVEL(mpidr, 0);
	अचिन्हित पूर्णांक cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);
	phys_reset_t phys_reset;

	mcpm_set_entry_vector(cpu, cluster, cpu_resume_no_hyp);
	setup_mm_क्रम_reboot();

	__mcpm_cpu_going_करोwn(cpu, cluster);
	BUG_ON(!__mcpm_outbound_enter_critical(cpu, cluster));
	cache_disable();
	__mcpm_outbound_leave_critical(cluster, CLUSTER_DOWN);
	__mcpm_cpu_करोwn(cpu, cluster);

	phys_reset = (phys_reset_t)(अचिन्हित दीर्घ)__pa_symbol(cpu_reset);
	phys_reset(__pa_symbol(mcpm_entry_poपूर्णांक), false);
	BUG();
पूर्ण

पूर्णांक __init mcpm_loopback(व्योम (*cache_disable)(व्योम))
अणु
	पूर्णांक ret;

	/*
	 * We're going to soft-restart the current CPU through the
	 * low-level MCPM code by leveraging the suspend/resume
	 * infraकाष्ठाure. Let's play it safe by using cpu_pm_enter()
	 * in हाल the CPU init code path resets the VFP or similar.
	 */
	local_irq_disable();
	local_fiq_disable();
	ret = cpu_pm_enter();
	अगर (!ret) अणु
		ret = cpu_suspend((अचिन्हित दीर्घ)cache_disable, nocache_trampoline);
		cpu_pm_निकास();
	पूर्ण
	local_fiq_enable();
	local_irq_enable();
	अगर (ret)
		pr_err("%s returned %d\n", __func__, ret);
	वापस ret;
पूर्ण

#पूर्ण_अगर

बाह्य अचिन्हित दीर्घ mcpm_घातer_up_setup_phys;

पूर्णांक __init mcpm_sync_init(
	व्योम (*घातer_up_setup)(अचिन्हित पूर्णांक affinity_level))
अणु
	अचिन्हित पूर्णांक i, j, mpidr, this_cluster;

	BUILD_BUG_ON(MCPM_SYNC_CLUSTER_SIZE * MAX_NR_CLUSTERS != माप mcpm_sync);
	BUG_ON((अचिन्हित दीर्घ)&mcpm_sync & (__CACHE_WRITEBACK_GRANULE - 1));

	/*
	 * Set initial CPU and cluster states.
	 * Only one cluster is assumed to be active at this poपूर्णांक.
	 */
	क्रम (i = 0; i < MAX_NR_CLUSTERS; i++) अणु
		mcpm_sync.clusters[i].cluster = CLUSTER_DOWN;
		mcpm_sync.clusters[i].inbound = INBOUND_NOT_COMING_UP;
		क्रम (j = 0; j < MAX_CPUS_PER_CLUSTER; j++)
			mcpm_sync.clusters[i].cpus[j].cpu = CPU_DOWN;
	पूर्ण
	mpidr = पढ़ो_cpuid_mpidr();
	this_cluster = MPIDR_AFFINITY_LEVEL(mpidr, 1);
	क्रम_each_online_cpu(i) अणु
		mcpm_cpu_use_count[this_cluster][i] = 1;
		mcpm_sync.clusters[this_cluster].cpus[i].cpu = CPU_UP;
	पूर्ण
	mcpm_sync.clusters[this_cluster].cluster = CLUSTER_UP;
	sync_cache_w(&mcpm_sync);

	अगर (घातer_up_setup) अणु
		mcpm_घातer_up_setup_phys = __pa_symbol(घातer_up_setup);
		sync_cache_w(&mcpm_घातer_up_setup_phys);
	पूर्ण

	वापस 0;
पूर्ण
