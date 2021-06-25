<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2016 ARM Limited
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/atomic.h>
#समावेश <linux/completion.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <uapi/linux/sched/types.h>
#समावेश <linux/module.h>
#समावेश <linux/preempt.h>
#समावेश <linux/psci.h>
#समावेश <linux/slab.h>
#समावेश <linux/tick.h>
#समावेश <linux/topology.h>

#समावेश <यंत्र/cpuidle.h>

#समावेश <uapi/linux/psci.h>

#घोषणा NUM_SUSPEND_CYCLE (10)

अटल अचिन्हित पूर्णांक nb_available_cpus;
अटल पूर्णांक tos_resident_cpu = -1;

अटल atomic_t nb_active_thपढ़ोs;
अटल काष्ठा completion suspend_thपढ़ोs_started =
	COMPLETION_INITIALIZER(suspend_thपढ़ोs_started);
अटल काष्ठा completion suspend_thपढ़ोs_करोne =
	COMPLETION_INITIALIZER(suspend_thपढ़ोs_करोne);

/*
 * We assume that PSCI operations are used अगर they are available. This is not
 * necessarily true on arm64, since the decision is based on the
 * "enable-method" property of each CPU in the DT, but given that there is no
 * arch-specअगरic way to check this, we assume that the DT is sensible.
 */
अटल पूर्णांक psci_ops_check(व्योम)
अणु
	पूर्णांक migrate_type = -1;
	पूर्णांक cpu;

	अगर (!(psci_ops.cpu_off && psci_ops.cpu_on && psci_ops.cpu_suspend)) अणु
		pr_warn("Missing PSCI operations, aborting tests\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (psci_ops.migrate_info_type)
		migrate_type = psci_ops.migrate_info_type();

	अगर (migrate_type == PSCI_0_2_TOS_UP_MIGRATE ||
	    migrate_type == PSCI_0_2_TOS_UP_NO_MIGRATE) अणु
		/* There is a UP Trusted OS, find on which core it resides. */
		क्रम_each_online_cpu(cpu)
			अगर (psci_tos_resident_on(cpu)) अणु
				tos_resident_cpu = cpu;
				अवरोध;
			पूर्ण
		अगर (tos_resident_cpu == -1)
			pr_warn("UP Trusted OS resides on no online CPU\n");
	पूर्ण

	वापस 0;
पूर्ण

/*
 * offlined_cpus is a temporary array but passing it as an argument aव्योमs
 * multiple allocations.
 */
अटल अचिन्हित पूर्णांक करोwn_and_up_cpus(स्थिर काष्ठा cpumask *cpus,
				     काष्ठा cpumask *offlined_cpus)
अणु
	पूर्णांक cpu;
	पूर्णांक err = 0;

	cpumask_clear(offlined_cpus);

	/* Try to घातer करोwn all CPUs in the mask. */
	क्रम_each_cpu(cpu, cpus) अणु
		पूर्णांक ret = हटाओ_cpu(cpu);

		/*
		 * cpu_करोwn() checks the number of online CPUs beक्रमe the TOS
		 * resident CPU.
		 */
		अगर (cpumask_weight(offlined_cpus) + 1 == nb_available_cpus) अणु
			अगर (ret != -EBUSY) अणु
				pr_err("Unexpected return code %d while trying "
				       "to power down last online CPU %d\n",
				       ret, cpu);
				++err;
			पूर्ण
		पूर्ण अन्यथा अगर (cpu == tos_resident_cpu) अणु
			अगर (ret != -EPERM) अणु
				pr_err("Unexpected return code %d while trying "
				       "to power down TOS resident CPU %d\n",
				       ret, cpu);
				++err;
			पूर्ण
		पूर्ण अन्यथा अगर (ret != 0) अणु
			pr_err("Error occurred (%d) while trying "
			       "to power down CPU %d\n", ret, cpu);
			++err;
		पूर्ण

		अगर (ret == 0)
			cpumask_set_cpu(cpu, offlined_cpus);
	पूर्ण

	/* Try to घातer up all the CPUs that have been offlined. */
	क्रम_each_cpu(cpu, offlined_cpus) अणु
		पूर्णांक ret = add_cpu(cpu);

		अगर (ret != 0) अणु
			pr_err("Error occurred (%d) while trying "
			       "to power up CPU %d\n", ret, cpu);
			++err;
		पूर्ण अन्यथा अणु
			cpumask_clear_cpu(cpu, offlined_cpus);
		पूर्ण
	पूर्ण

	/*
	 * Something went bad at some poपूर्णांक and some CPUs could not be turned
	 * back on.
	 */
	WARN_ON(!cpumask_empty(offlined_cpus) ||
		num_online_cpus() != nb_available_cpus);

	वापस err;
पूर्ण

अटल व्योम मुक्त_cpu_groups(पूर्णांक num, cpumask_var_t **pcpu_groups)
अणु
	पूर्णांक i;
	cpumask_var_t *cpu_groups = *pcpu_groups;

	क्रम (i = 0; i < num; ++i)
		मुक्त_cpumask_var(cpu_groups[i]);
	kमुक्त(cpu_groups);
पूर्ण

अटल पूर्णांक alloc_init_cpu_groups(cpumask_var_t **pcpu_groups)
अणु
	पूर्णांक num_groups = 0;
	cpumask_var_t पंचांगp, *cpu_groups;

	अगर (!alloc_cpumask_var(&पंचांगp, GFP_KERNEL))
		वापस -ENOMEM;

	cpu_groups = kसुस्मृति(nb_available_cpus, माप(cpu_groups),
			     GFP_KERNEL);
	अगर (!cpu_groups) अणु
		मुक्त_cpumask_var(पंचांगp);
		वापस -ENOMEM;
	पूर्ण

	cpumask_copy(पंचांगp, cpu_online_mask);

	जबतक (!cpumask_empty(पंचांगp)) अणु
		स्थिर काष्ठा cpumask *cpu_group =
			topology_core_cpumask(cpumask_any(पंचांगp));

		अगर (!alloc_cpumask_var(&cpu_groups[num_groups], GFP_KERNEL)) अणु
			मुक्त_cpumask_var(पंचांगp);
			मुक्त_cpu_groups(num_groups, &cpu_groups);
			वापस -ENOMEM;
		पूर्ण
		cpumask_copy(cpu_groups[num_groups++], cpu_group);
		cpumask_andnot(पंचांगp, पंचांगp, cpu_group);
	पूर्ण

	मुक्त_cpumask_var(पंचांगp);
	*pcpu_groups = cpu_groups;

	वापस num_groups;
पूर्ण

अटल पूर्णांक hotplug_tests(व्योम)
अणु
	पूर्णांक i, nb_cpu_group, err = -ENOMEM;
	cpumask_var_t offlined_cpus, *cpu_groups;
	अक्षर *page_buf;

	अगर (!alloc_cpumask_var(&offlined_cpus, GFP_KERNEL))
		वापस err;

	nb_cpu_group = alloc_init_cpu_groups(&cpu_groups);
	अगर (nb_cpu_group < 0)
		जाओ out_मुक्त_cpus;
	page_buf = (अक्षर *)__get_मुक्त_page(GFP_KERNEL);
	अगर (!page_buf)
		जाओ out_मुक्त_cpu_groups;

	/*
	 * Of course the last CPU cannot be घातered करोwn and cpu_करोwn() should
	 * refuse करोing that.
	 */
	pr_info("Trying to turn off and on again all CPUs\n");
	err = करोwn_and_up_cpus(cpu_online_mask, offlined_cpus);

	/*
	 * Take करोwn CPUs by cpu group this समय. When the last CPU is turned
	 * off, the cpu group itself should shut करोwn.
	 */
	क्रम (i = 0; i < nb_cpu_group; ++i) अणु
		sमाप_प्रकार len = cpumap_prपूर्णांक_to_pagebuf(true, page_buf,
						      cpu_groups[i]);
		/* Remove trailing newline. */
		page_buf[len - 1] = '\0';
		pr_info("Trying to turn off and on again group %d (CPUs %s)\n",
			i, page_buf);
		err += करोwn_and_up_cpus(cpu_groups[i], offlined_cpus);
	पूर्ण

	मुक्त_page((अचिन्हित दीर्घ)page_buf);
out_मुक्त_cpu_groups:
	मुक्त_cpu_groups(nb_cpu_group, &cpu_groups);
out_मुक्त_cpus:
	मुक्त_cpumask_var(offlined_cpus);
	वापस err;
पूर्ण

अटल व्योम dummy_callback(काष्ठा समयr_list *unused) अणुपूर्ण

अटल पूर्णांक suspend_cpu(काष्ठा cpuidle_device *dev,
		       काष्ठा cpuidle_driver *drv, पूर्णांक index)
अणु
	काष्ठा cpuidle_state *state = &drv->states[index];
	bool broadcast = state->flags & CPUIDLE_FLAG_TIMER_STOP;
	पूर्णांक ret;

	arch_cpu_idle_enter();

	अगर (broadcast) अणु
		/*
		 * The local समयr will be shut करोwn, we need to enter tick
		 * broadcast.
		 */
		ret = tick_broadcast_enter();
		अगर (ret) अणु
			/*
			 * In the असलence of hardware broadcast mechanism,
			 * this CPU might be used to broadcast wakeups, which
			 * may be why entering tick broadcast has failed.
			 * There is little the kernel can करो to work around
			 * that, so enter WFI instead (idle state 0).
			 */
			cpu_करो_idle();
			ret = 0;
			जाओ out_arch_निकास;
		पूर्ण
	पूर्ण

	ret = state->enter(dev, drv, index);

	अगर (broadcast)
		tick_broadcast_निकास();

out_arch_निकास:
	arch_cpu_idle_निकास();

	वापस ret;
पूर्ण

अटल पूर्णांक suspend_test_thपढ़ो(व्योम *arg)
अणु
	पूर्णांक cpu = (दीर्घ)arg;
	पूर्णांक i, nb_suspend = 0, nb_shallow_sleep = 0, nb_err = 0;
	काष्ठा cpuidle_device *dev;
	काष्ठा cpuidle_driver *drv;
	/* No need क्रम an actual callback, we just want to wake up the CPU. */
	काष्ठा समयr_list wakeup_समयr;

	/* Wait क्रम the मुख्य thपढ़ो to give the start संकेत. */
	रुको_क्रम_completion(&suspend_thपढ़ोs_started);

	/* Set maximum priority to preempt all other thपढ़ोs on this CPU. */
	sched_set_fअगरo(current);

	dev = this_cpu_पढ़ो(cpuidle_devices);
	drv = cpuidle_get_cpu_driver(dev);

	pr_info("CPU %d entering suspend cycles, states 1 through %d\n",
		cpu, drv->state_count - 1);

	समयr_setup_on_stack(&wakeup_समयr, dummy_callback, 0);
	क्रम (i = 0; i < NUM_SUSPEND_CYCLE; ++i) अणु
		पूर्णांक index;
		/*
		 * Test all possible states, except 0 (which is usually WFI and
		 * करोesn't use PSCI).
		 */
		क्रम (index = 1; index < drv->state_count; ++index) अणु
			पूर्णांक ret;
			काष्ठा cpuidle_state *state = &drv->states[index];

			/*
			 * Set the समयr to wake this CPU up in some समय (which
			 * should be largely sufficient क्रम entering suspend).
			 * If the local tick is disabled when entering suspend,
			 * suspend_cpu() takes care of चयनing to a broadcast
			 * tick, so the समयr will still wake us up.
			 */
			mod_समयr(&wakeup_समयr, jअगरfies +
				  usecs_to_jअगरfies(state->target_residency));

			/* IRQs must be disabled during suspend operations. */
			local_irq_disable();

			ret = suspend_cpu(dev, drv, index);

			/*
			 * We have woken up. Re-enable IRQs to handle any
			 * pending पूर्णांकerrupt, करो not रुको until the end of the
			 * loop.
			 */
			local_irq_enable();

			अगर (ret == index) अणु
				++nb_suspend;
			पूर्ण अन्यथा अगर (ret >= 0) अणु
				/* We did not enter the expected state. */
				++nb_shallow_sleep;
			पूर्ण अन्यथा अणु
				pr_err("Failed to suspend CPU %d: error %d "
				       "(requested state %d, cycle %d)\n",
				       cpu, ret, index, i);
				++nb_err;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Disable the समयr to make sure that the समयr will not trigger
	 * later.
	 */
	del_समयr(&wakeup_समयr);
	destroy_समयr_on_stack(&wakeup_समयr);

	अगर (atomic_dec_वापस_relaxed(&nb_active_thपढ़ोs) == 0)
		complete(&suspend_thपढ़ोs_करोne);

	क्रम (;;) अणु
		/* Needs to be set first to aव्योम missing a wakeup. */
		set_current_state(TASK_INTERRUPTIBLE);
		अगर (kthपढ़ो_should_park())
			अवरोध;
		schedule();
	पूर्ण

	pr_info("CPU %d suspend test results: success %d, shallow states %d, errors %d\n",
		cpu, nb_suspend, nb_shallow_sleep, nb_err);

	kthपढ़ो_parkme();

	वापस nb_err;
पूर्ण

अटल पूर्णांक suspend_tests(व्योम)
अणु
	पूर्णांक i, cpu, err = 0;
	काष्ठा task_काष्ठा **thपढ़ोs;
	पूर्णांक nb_thपढ़ोs = 0;

	thपढ़ोs = kदो_स्मृति_array(nb_available_cpus, माप(*thपढ़ोs),
				GFP_KERNEL);
	अगर (!thपढ़ोs)
		वापस -ENOMEM;

	/*
	 * Stop cpuidle to prevent the idle tasks from entering a deep sleep
	 * mode, as it might पूर्णांकerfere with the suspend thपढ़ोs on other CPUs.
	 * This करोes not prevent the suspend thपढ़ोs from using cpuidle (only
	 * the idle tasks check this status). Take the idle lock so that
	 * the cpuidle driver and device look-up can be carried out safely.
	 */
	cpuidle_छोड़ो_and_lock();

	क्रम_each_online_cpu(cpu) अणु
		काष्ठा task_काष्ठा *thपढ़ो;
		/* Check that cpuidle is available on that CPU. */
		काष्ठा cpuidle_device *dev = per_cpu(cpuidle_devices, cpu);
		काष्ठा cpuidle_driver *drv = cpuidle_get_cpu_driver(dev);

		अगर (!dev || !drv) अणु
			pr_warn("cpuidle not available on CPU %d, ignoring\n",
				cpu);
			जारी;
		पूर्ण

		thपढ़ो = kthपढ़ो_create_on_cpu(suspend_test_thपढ़ो,
					       (व्योम *)(दीर्घ)cpu, cpu,
					       "psci_suspend_test");
		अगर (IS_ERR(thपढ़ो))
			pr_err("Failed to create kthread on CPU %d\n", cpu);
		अन्यथा
			thपढ़ोs[nb_thपढ़ोs++] = thपढ़ो;
	पूर्ण

	अगर (nb_thपढ़ोs < 1) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	atomic_set(&nb_active_thपढ़ोs, nb_thपढ़ोs);

	/*
	 * Wake up the suspend thपढ़ोs. To aव्योम the मुख्य thपढ़ो being preempted
	 * beक्रमe all the thपढ़ोs have been unparked, the suspend thपढ़ोs will
	 * रुको क्रम the completion of suspend_thपढ़ोs_started.
	 */
	क्रम (i = 0; i < nb_thपढ़ोs; ++i)
		wake_up_process(thपढ़ोs[i]);
	complete_all(&suspend_thपढ़ोs_started);

	रुको_क्रम_completion(&suspend_thपढ़ोs_करोne);


	/* Stop and destroy all thपढ़ोs, get वापस status. */
	क्रम (i = 0; i < nb_thपढ़ोs; ++i) अणु
		err += kthपढ़ो_park(thपढ़ोs[i]);
		err += kthपढ़ो_stop(thपढ़ोs[i]);
	पूर्ण
 out:
	cpuidle_resume_and_unlock();
	kमुक्त(thपढ़ोs);
	वापस err;
पूर्ण

अटल पूर्णांक __init psci_checker(व्योम)
अणु
	पूर्णांक ret;

	/*
	 * Since we're in an initcall, we assume that all the CPUs that all
	 * CPUs that can be onlined have been onlined.
	 *
	 * The tests assume that hotplug is enabled but nobody अन्यथा is using it,
	 * otherwise the results will be unpredictable. However, since there
	 * is no userspace yet in initcalls, that should be fine, as दीर्घ as
	 * no torture test is running at the same समय (see Kconfig).
	 */
	nb_available_cpus = num_online_cpus();

	/* Check PSCI operations are set up and working. */
	ret = psci_ops_check();
	अगर (ret)
		वापस ret;

	pr_info("PSCI checker started using %u CPUs\n", nb_available_cpus);

	pr_info("Starting hotplug tests\n");
	ret = hotplug_tests();
	अगर (ret == 0)
		pr_info("Hotplug tests passed OK\n");
	अन्यथा अगर (ret > 0)
		pr_err("%d error(s) encountered in hotplug tests\n", ret);
	अन्यथा अणु
		pr_err("Out of memory\n");
		वापस ret;
	पूर्ण

	pr_info("Starting suspend tests (%d cycles per state)\n",
		NUM_SUSPEND_CYCLE);
	ret = suspend_tests();
	अगर (ret == 0)
		pr_info("Suspend tests passed OK\n");
	अन्यथा अगर (ret > 0)
		pr_err("%d error(s) encountered in suspend tests\n", ret);
	अन्यथा अणु
		चयन (ret) अणु
		हाल -ENOMEM:
			pr_err("Out of memory\n");
			अवरोध;
		हाल -ENODEV:
			pr_warn("Could not start suspend tests on any CPU\n");
			अवरोध;
		पूर्ण
	पूर्ण

	pr_info("PSCI checker completed\n");
	वापस ret < 0 ? ret : 0;
पूर्ण
late_initcall(psci_checker);
