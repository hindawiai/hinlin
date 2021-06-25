<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Housekeeping management. Manage the tarमाला_लो क्रम routine code that can run on
 *  any CPU: unbound workqueues, समयrs, kthपढ़ोs and any offloadable work.
 *
 * Copyright (C) 2017 Red Hat, Inc., Frederic Weisbecker
 * Copyright (C) 2017-2018 SUSE, Frederic Weisbecker
 *
 */
#समावेश "sched.h"

DEFINE_STATIC_KEY_FALSE(housekeeping_overridden);
EXPORT_SYMBOL_GPL(housekeeping_overridden);
अटल cpumask_var_t housekeeping_mask;
अटल अचिन्हित पूर्णांक housekeeping_flags;

bool housekeeping_enabled(क्रमागत hk_flags flags)
अणु
	वापस !!(housekeeping_flags & flags);
पूर्ण
EXPORT_SYMBOL_GPL(housekeeping_enabled);

पूर्णांक housekeeping_any_cpu(क्रमागत hk_flags flags)
अणु
	पूर्णांक cpu;

	अगर (अटल_branch_unlikely(&housekeeping_overridden)) अणु
		अगर (housekeeping_flags & flags) अणु
			cpu = sched_numa_find_बंदst(housekeeping_mask, smp_processor_id());
			अगर (cpu < nr_cpu_ids)
				वापस cpu;

			वापस cpumask_any_and(housekeeping_mask, cpu_online_mask);
		पूर्ण
	पूर्ण
	वापस smp_processor_id();
पूर्ण
EXPORT_SYMBOL_GPL(housekeeping_any_cpu);

स्थिर काष्ठा cpumask *housekeeping_cpumask(क्रमागत hk_flags flags)
अणु
	अगर (अटल_branch_unlikely(&housekeeping_overridden))
		अगर (housekeeping_flags & flags)
			वापस housekeeping_mask;
	वापस cpu_possible_mask;
पूर्ण
EXPORT_SYMBOL_GPL(housekeeping_cpumask);

व्योम housekeeping_affine(काष्ठा task_काष्ठा *t, क्रमागत hk_flags flags)
अणु
	अगर (अटल_branch_unlikely(&housekeeping_overridden))
		अगर (housekeeping_flags & flags)
			set_cpus_allowed_ptr(t, housekeeping_mask);
पूर्ण
EXPORT_SYMBOL_GPL(housekeeping_affine);

bool housekeeping_test_cpu(पूर्णांक cpu, क्रमागत hk_flags flags)
अणु
	अगर (अटल_branch_unlikely(&housekeeping_overridden))
		अगर (housekeeping_flags & flags)
			वापस cpumask_test_cpu(cpu, housekeeping_mask);
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(housekeeping_test_cpu);

व्योम __init housekeeping_init(व्योम)
अणु
	अगर (!housekeeping_flags)
		वापस;

	अटल_branch_enable(&housekeeping_overridden);

	अगर (housekeeping_flags & HK_FLAG_TICK)
		sched_tick_offload_init();

	/* We need at least one CPU to handle housekeeping work */
	WARN_ON_ONCE(cpumask_empty(housekeeping_mask));
पूर्ण

अटल पूर्णांक __init housekeeping_setup(अक्षर *str, क्रमागत hk_flags flags)
अणु
	cpumask_var_t non_housekeeping_mask;
	cpumask_var_t पंचांगp;
	पूर्णांक err;

	alloc_booपंचांगem_cpumask_var(&non_housekeeping_mask);
	err = cpulist_parse(str, non_housekeeping_mask);
	अगर (err < 0 || cpumask_last(non_housekeeping_mask) >= nr_cpu_ids) अणु
		pr_warn("Housekeeping: nohz_full= or isolcpus= incorrect CPU range\n");
		मुक्त_booपंचांगem_cpumask_var(non_housekeeping_mask);
		वापस 0;
	पूर्ण

	alloc_booपंचांगem_cpumask_var(&पंचांगp);
	अगर (!housekeeping_flags) अणु
		alloc_booपंचांगem_cpumask_var(&housekeeping_mask);
		cpumask_andnot(housekeeping_mask,
			       cpu_possible_mask, non_housekeeping_mask);

		cpumask_andnot(पंचांगp, cpu_present_mask, non_housekeeping_mask);
		अगर (cpumask_empty(पंचांगp)) अणु
			pr_warn("Housekeeping: must include one present CPU, "
				"using boot CPU:%d\n", smp_processor_id());
			__cpumask_set_cpu(smp_processor_id(), housekeeping_mask);
			__cpumask_clear_cpu(smp_processor_id(), non_housekeeping_mask);
		पूर्ण
	पूर्ण अन्यथा अणु
		cpumask_andnot(पंचांगp, cpu_present_mask, non_housekeeping_mask);
		अगर (cpumask_empty(पंचांगp))
			__cpumask_clear_cpu(smp_processor_id(), non_housekeeping_mask);
		cpumask_andnot(पंचांगp, cpu_possible_mask, non_housekeeping_mask);
		अगर (!cpumask_equal(पंचांगp, housekeeping_mask)) अणु
			pr_warn("Housekeeping: nohz_full= must match isolcpus=\n");
			मुक्त_booपंचांगem_cpumask_var(पंचांगp);
			मुक्त_booपंचांगem_cpumask_var(non_housekeeping_mask);
			वापस 0;
		पूर्ण
	पूर्ण
	मुक्त_booपंचांगem_cpumask_var(पंचांगp);

	अगर ((flags & HK_FLAG_TICK) && !(housekeeping_flags & HK_FLAG_TICK)) अणु
		अगर (IS_ENABLED(CONFIG_NO_HZ_FULL)) अणु
			tick_nohz_full_setup(non_housekeeping_mask);
		पूर्ण अन्यथा अणु
			pr_warn("Housekeeping: nohz unsupported."
				" Build with CONFIG_NO_HZ_FULL\n");
			मुक्त_booपंचांगem_cpumask_var(non_housekeeping_mask);
			वापस 0;
		पूर्ण
	पूर्ण

	housekeeping_flags |= flags;

	मुक्त_booपंचांगem_cpumask_var(non_housekeeping_mask);

	वापस 1;
पूर्ण

अटल पूर्णांक __init housekeeping_nohz_full_setup(अक्षर *str)
अणु
	अचिन्हित पूर्णांक flags;

	flags = HK_FLAG_TICK | HK_FLAG_WQ | HK_FLAG_TIMER | HK_FLAG_RCU |
		HK_FLAG_MISC | HK_FLAG_KTHREAD;

	वापस housekeeping_setup(str, flags);
पूर्ण
__setup("nohz_full=", housekeeping_nohz_full_setup);

अटल पूर्णांक __init housekeeping_isolcpus_setup(अक्षर *str)
अणु
	अचिन्हित पूर्णांक flags = 0;
	bool illegal = false;
	अक्षर *par;
	पूर्णांक len;

	जबतक (है_अक्षर(*str)) अणु
		अगर (!म_भेदन(str, "nohz,", 5)) अणु
			str += 5;
			flags |= HK_FLAG_TICK;
			जारी;
		पूर्ण

		अगर (!म_भेदन(str, "domain,", 7)) अणु
			str += 7;
			flags |= HK_FLAG_DOMAIN;
			जारी;
		पूर्ण

		अगर (!म_भेदन(str, "managed_irq,", 12)) अणु
			str += 12;
			flags |= HK_FLAG_MANAGED_IRQ;
			जारी;
		पूर्ण

		/*
		 * Skip unknown sub-parameter and validate that it is not
		 * containing an invalid अक्षरacter.
		 */
		क्रम (par = str, len = 0; *str && *str != ','; str++, len++) अणु
			अगर (!है_अक्षर(*str) && *str != '_')
				illegal = true;
		पूर्ण

		अगर (illegal) अणु
			pr_warn("isolcpus: Invalid flag %.*s\n", len, par);
			वापस 0;
		पूर्ण

		pr_info("isolcpus: Skipped unknown flag %.*s\n", len, par);
		str++;
	पूर्ण

	/* Default behaviour क्रम isolcpus without flags */
	अगर (!flags)
		flags |= HK_FLAG_DOMAIN;

	वापस housekeeping_setup(str, flags);
पूर्ण
__setup("isolcpus=", housekeeping_isolcpus_setup);
