<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  cpuidle-घातernv - idle state cpuidle driver.
 *  Adapted from drivers/cpuidle/cpuidle-pseries
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/cpu.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/runlatch.h>
#समावेश <यंत्र/cpuidle.h>

/*
 * Expose only those Hardware idle states via the cpuidle framework
 * that have latency value below POWERNV_THRESHOLD_LATENCY_NS.
 */
#घोषणा POWERNV_THRESHOLD_LATENCY_NS 200000

अटल काष्ठा cpuidle_driver घातernv_idle_driver = अणु
	.name             = "powernv_idle",
	.owner            = THIS_MODULE,
पूर्ण;

अटल पूर्णांक max_idle_state __पढ़ो_mostly;
अटल काष्ठा cpuidle_state *cpuidle_state_table __पढ़ो_mostly;

काष्ठा stop_psscr_table अणु
	u64 val;
	u64 mask;
पूर्ण;

अटल काष्ठा stop_psscr_table stop_psscr_table[CPUIDLE_STATE_MAX] __पढ़ो_mostly;

अटल u64 शेष_snooze_समयout __पढ़ो_mostly;
अटल bool snooze_समयout_en __पढ़ो_mostly;

अटल u64 get_snooze_समयout(काष्ठा cpuidle_device *dev,
			      काष्ठा cpuidle_driver *drv,
			      पूर्णांक index)
अणु
	पूर्णांक i;

	अगर (unlikely(!snooze_समयout_en))
		वापस शेष_snooze_समयout;

	क्रम (i = index + 1; i < drv->state_count; i++) अणु
		अगर (dev->states_usage[i].disable)
			जारी;

		वापस drv->states[i].target_residency * tb_ticks_per_usec;
	पूर्ण

	वापस शेष_snooze_समयout;
पूर्ण

अटल पूर्णांक snooze_loop(काष्ठा cpuidle_device *dev,
			काष्ठा cpuidle_driver *drv,
			पूर्णांक index)
अणु
	u64 snooze_निकास_समय;

	set_thपढ़ो_flag(TIF_POLLING_NRFLAG);

	local_irq_enable();

	snooze_निकास_समय = get_tb() + get_snooze_समयout(dev, drv, index);
	ppc64_runlatch_off();
	HMT_very_low();
	जबतक (!need_resched()) अणु
		अगर (likely(snooze_समयout_en) && get_tb() > snooze_निकास_समय) अणु
			/*
			 * Task has not woken up but we are निकासing the polling
			 * loop anyway. Require a barrier after polling is
			 * cleared to order subsequent test of need_resched().
			 */
			clear_thपढ़ो_flag(TIF_POLLING_NRFLAG);
			smp_mb();
			अवरोध;
		पूर्ण
	पूर्ण

	HMT_medium();
	ppc64_runlatch_on();
	clear_thपढ़ो_flag(TIF_POLLING_NRFLAG);

	local_irq_disable();

	वापस index;
पूर्ण

अटल पूर्णांक nap_loop(काष्ठा cpuidle_device *dev,
			काष्ठा cpuidle_driver *drv,
			पूर्णांक index)
अणु
	घातer7_idle_type(PNV_THREAD_NAP);

	वापस index;
पूर्ण

/* Register क्रम fastsleep only in oneshot mode of broadcast */
#अगर_घोषित CONFIG_TICK_ONESHOT
अटल पूर्णांक fastsleep_loop(काष्ठा cpuidle_device *dev,
				काष्ठा cpuidle_driver *drv,
				पूर्णांक index)
अणु
	अचिन्हित दीर्घ old_lpcr = mfspr(SPRN_LPCR);
	अचिन्हित दीर्घ new_lpcr;

	अगर (unlikely(प्रणाली_state < SYSTEM_RUNNING))
		वापस index;

	new_lpcr = old_lpcr;
	/* Do not निकास घातersave upon decrementer as we've setup the समयr
	 * offload.
	 */
	new_lpcr &= ~LPCR_PECE1;

	mtspr(SPRN_LPCR, new_lpcr);

	घातer7_idle_type(PNV_THREAD_SLEEP);

	mtspr(SPRN_LPCR, old_lpcr);

	वापस index;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक stop_loop(काष्ठा cpuidle_device *dev,
		     काष्ठा cpuidle_driver *drv,
		     पूर्णांक index)
अणु
	arch300_idle_type(stop_psscr_table[index].val,
			 stop_psscr_table[index].mask);
	वापस index;
पूर्ण

/*
 * States क्रम dedicated partition हाल.
 */
अटल काष्ठा cpuidle_state घातernv_states[CPUIDLE_STATE_MAX] = अणु
	अणु /* Snooze */
		.name = "snooze",
		.desc = "snooze",
		.निकास_latency = 0,
		.target_residency = 0,
		.enter = snooze_loop पूर्ण,
पूर्ण;

अटल पूर्णांक घातernv_cpuidle_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpuidle_device *dev = per_cpu(cpuidle_devices, cpu);

	अगर (dev && cpuidle_get_driver()) अणु
		cpuidle_छोड़ो_and_lock();
		cpuidle_enable_device(dev);
		cpuidle_resume_and_unlock();
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक घातernv_cpuidle_cpu_dead(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpuidle_device *dev = per_cpu(cpuidle_devices, cpu);

	अगर (dev && cpuidle_get_driver()) अणु
		cpuidle_छोड़ो_and_lock();
		cpuidle_disable_device(dev);
		cpuidle_resume_and_unlock();
	पूर्ण
	वापस 0;
पूर्ण

/*
 * घातernv_cpuidle_driver_init()
 */
अटल पूर्णांक घातernv_cpuidle_driver_init(व्योम)
अणु
	पूर्णांक idle_state;
	काष्ठा cpuidle_driver *drv = &घातernv_idle_driver;

	drv->state_count = 0;

	क्रम (idle_state = 0; idle_state < max_idle_state; ++idle_state) अणु
		/* Is the state not enabled? */
		अगर (cpuidle_state_table[idle_state].enter == शून्य)
			जारी;

		drv->states[drv->state_count] =	/* काष्ठाure copy */
			cpuidle_state_table[idle_state];

		drv->state_count += 1;
	पूर्ण

	/*
	 * On the PowerNV platक्रमm cpu_present may be less than cpu_possible in
	 * हालs when firmware detects the CPU, but it is not available to the
	 * OS.  If CONFIG_HOTPLUG_CPU=n, then such CPUs are not hotplugable at
	 * run समय and hence cpu_devices are not created क्रम those CPUs by the
	 * generic topology_init().
	 *
	 * drv->cpumask शेषs to cpu_possible_mask in
	 * __cpuidle_driver_init().  This अवरोधs cpuidle on PowerNV where
	 * cpu_devices are not created क्रम CPUs in cpu_possible_mask that
	 * cannot be hot-added later at run समय.
	 *
	 * Trying cpuidle_रेजिस्टर_device() on a CPU without a cpu_device is
	 * incorrect, so pass a correct CPU mask to the generic cpuidle driver.
	 */

	drv->cpumask = (काष्ठा cpumask *)cpu_present_mask;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम add_घातernv_state(पूर्णांक index, स्थिर अक्षर *name,
				     अचिन्हित पूर्णांक flags,
				     पूर्णांक (*idle_fn)(काष्ठा cpuidle_device *,
						    काष्ठा cpuidle_driver *,
						    पूर्णांक),
				     अचिन्हित पूर्णांक target_residency,
				     अचिन्हित पूर्णांक निकास_latency,
				     u64 psscr_val, u64 psscr_mask)
अणु
	strlcpy(घातernv_states[index].name, name, CPUIDLE_NAME_LEN);
	strlcpy(घातernv_states[index].desc, name, CPUIDLE_NAME_LEN);
	घातernv_states[index].flags = flags;
	घातernv_states[index].target_residency = target_residency;
	घातernv_states[index].निकास_latency = निकास_latency;
	घातernv_states[index].enter = idle_fn;
	/* For घातer8 and below psscr_* will be 0 */
	stop_psscr_table[index].val = psscr_val;
	stop_psscr_table[index].mask = psscr_mask;
पूर्ण

बाह्य u32 pnv_get_supported_cpuidle_states(व्योम);
अटल पूर्णांक घातernv_add_idle_states(व्योम)
अणु
	पूर्णांक nr_idle_states = 1; /* Snooze */
	पूर्णांक dt_idle_states;
	u32 has_stop_states = 0;
	पूर्णांक i;
	u32 supported_flags = pnv_get_supported_cpuidle_states();


	/* Currently we have snooze अटलally defined */
	अगर (nr_pnv_idle_states <= 0) अणु
		pr_warn("cpuidle-powernv : Only Snooze is available\n");
		जाओ out;
	पूर्ण

	/* TODO: Count only states which are eligible क्रम cpuidle */
	dt_idle_states = nr_pnv_idle_states;

	/*
	 * Since snooze is used as first idle state, max idle states allowed is
	 * CPUIDLE_STATE_MAX -1
	 */
	अगर (nr_pnv_idle_states > CPUIDLE_STATE_MAX - 1) अणु
		pr_warn("cpuidle-powernv: discovered idle states more than allowed");
		dt_idle_states = CPUIDLE_STATE_MAX - 1;
	पूर्ण

	/*
	 * If the idle states use stop inकाष्ठाion, probe क्रम psscr values
	 * and psscr mask which are necessary to specअगरy required stop level.
	 */
	has_stop_states = (pnv_idle_states[0].flags &
			   (OPAL_PM_STOP_INST_FAST | OPAL_PM_STOP_INST_DEEP));

	क्रम (i = 0; i < dt_idle_states; i++) अणु
		अचिन्हित पूर्णांक निकास_latency, target_residency;
		bool stops_समयbase = false;
		काष्ठा pnv_idle_states_t *state = &pnv_idle_states[i];

		/*
		 * Skip the platक्रमm idle state whose flag isn't in
		 * the supported_cpuidle_states flag mask.
		 */
		अगर ((state->flags & supported_flags) != state->flags)
			जारी;
		/*
		 * If an idle state has निकास latency beyond
		 * POWERNV_THRESHOLD_LATENCY_NS then करोn't use it
		 * in cpu-idle.
		 */
		अगर (state->latency_ns > POWERNV_THRESHOLD_LATENCY_NS)
			जारी;
		/*
		 * Firmware passes residency and latency values in ns.
		 * cpuidle expects it in us.
		 */
		निकास_latency = DIV_ROUND_UP(state->latency_ns, 1000);
		target_residency = DIV_ROUND_UP(state->residency_ns, 1000);

		अगर (has_stop_states && !(state->valid))
				जारी;

		अगर (state->flags & OPAL_PM_TIMEBASE_STOP)
			stops_समयbase = true;

		अगर (state->flags & OPAL_PM_NAP_ENABLED) अणु
			/* Add NAP state */
			add_घातernv_state(nr_idle_states, "Nap",
					  CPUIDLE_FLAG_NONE, nap_loop,
					  target_residency, निकास_latency, 0, 0);
		पूर्ण अन्यथा अगर (has_stop_states && !stops_समयbase) अणु
			add_घातernv_state(nr_idle_states, state->name,
					  CPUIDLE_FLAG_NONE, stop_loop,
					  target_residency, निकास_latency,
					  state->psscr_val,
					  state->psscr_mask);
		पूर्ण

		/*
		 * All cpuidle states with CPUIDLE_FLAG_TIMER_STOP set must come
		 * within this config dependency check.
		 */
#अगर_घोषित CONFIG_TICK_ONESHOT
		अन्यथा अगर (state->flags & OPAL_PM_SLEEP_ENABLED ||
			 state->flags & OPAL_PM_SLEEP_ENABLED_ER1) अणु
			/* Add FASTSLEEP state */
			add_घातernv_state(nr_idle_states, "FastSleep",
					  CPUIDLE_FLAG_TIMER_STOP,
					  fastsleep_loop,
					  target_residency, निकास_latency, 0, 0);
		पूर्ण अन्यथा अगर (has_stop_states && stops_समयbase) अणु
			add_घातernv_state(nr_idle_states, state->name,
					  CPUIDLE_FLAG_TIMER_STOP, stop_loop,
					  target_residency, निकास_latency,
					  state->psscr_val,
					  state->psscr_mask);
		पूर्ण
#पूर्ण_अगर
		अन्यथा
			जारी;
		nr_idle_states++;
	पूर्ण
out:
	वापस nr_idle_states;
पूर्ण

/*
 * घातernv_idle_probe()
 * Choose state table क्रम shared versus dedicated partition
 */
अटल पूर्णांक घातernv_idle_probe(व्योम)
अणु
	अगर (cpuidle_disable != IDLE_NO_OVERRIDE)
		वापस -ENODEV;

	अगर (firmware_has_feature(FW_FEATURE_OPAL)) अणु
		cpuidle_state_table = घातernv_states;
		/* Device tree can indicate more idle states */
		max_idle_state = घातernv_add_idle_states();
		शेष_snooze_समयout = TICK_USEC * tb_ticks_per_usec;
		अगर (max_idle_state > 1)
			snooze_समयout_en = true;
 	पूर्ण अन्यथा
 		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक __init घातernv_processor_idle_init(व्योम)
अणु
	पूर्णांक retval;

	retval = घातernv_idle_probe();
	अगर (retval)
		वापस retval;

	घातernv_cpuidle_driver_init();
	retval = cpuidle_रेजिस्टर(&घातernv_idle_driver, शून्य);
	अगर (retval) अणु
		prपूर्णांकk(KERN_DEBUG "Registration of powernv driver failed.\n");
		वापस retval;
	पूर्ण

	retval = cpuhp_setup_state_nocalls(CPUHP_AP_ONLINE_DYN,
					   "cpuidle/powernv:online",
					   घातernv_cpuidle_cpu_online, शून्य);
	WARN_ON(retval < 0);
	retval = cpuhp_setup_state_nocalls(CPUHP_CPUIDLE_DEAD,
					   "cpuidle/powernv:dead", शून्य,
					   घातernv_cpuidle_cpu_dead);
	WARN_ON(retval < 0);
	prपूर्णांकk(KERN_DEBUG "powernv_idle_driver registered\n");
	वापस 0;
पूर्ण

device_initcall(घातernv_processor_idle_init);
