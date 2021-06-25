<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Common functions क्रम in-kernel torture tests.
 *
 * Copyright (C) IBM Corporation, 2014
 *
 * Author: Paul E. McKenney <paulmck@linux.ibm.com>
 *	Based on kernel/rcu/torture.c.
 */

#घोषणा pr_fmt(fmt) fmt

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/err.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/smp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/atomic.h>
#समावेश <linux/bitops.h>
#समावेश <linux/completion.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/percpu.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/reboot.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/cpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/slab.h>
#समावेश <linux/trace_घड़ी.h>
#समावेश <linux/kसमय.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/torture.h>
#समावेश "rcu/rcu.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Paul E. McKenney <paulmck@linux.ibm.com>");

अटल bool disable_onoff_at_boot;
module_param(disable_onoff_at_boot, bool, 0444);

अटल bool ftrace_dump_at_shutकरोwn;
module_param(ftrace_dump_at_shutकरोwn, bool, 0444);

अटल पूर्णांक verbose_sleep_frequency;
module_param(verbose_sleep_frequency, पूर्णांक, 0444);

अटल पूर्णांक verbose_sleep_duration = 1;
module_param(verbose_sleep_duration, पूर्णांक, 0444);

अटल अक्षर *torture_type;
अटल पूर्णांक verbose;

/* Mediate rmmod and प्रणाली shutकरोwn.  Concurrent rmmod & shutकरोwn illegal! */
#घोषणा FULLSTOP_DONTSTOP 0	/* Normal operation. */
#घोषणा FULLSTOP_SHUTDOWN 1	/* System shutकरोwn with torture running. */
#घोषणा FULLSTOP_RMMOD    2	/* Normal rmmod of torture. */
अटल पूर्णांक fullstop = FULLSTOP_RMMOD;
अटल DEFINE_MUTEX(fullstop_mutex);

अटल atomic_t verbose_sleep_counter;

/*
 * Sleep अगर needed from VERBOSE_TOROUT*().
 */
व्योम verbose_torout_sleep(व्योम)
अणु
	अगर (verbose_sleep_frequency > 0 &&
	    verbose_sleep_duration > 0 &&
	    !(atomic_inc_वापस(&verbose_sleep_counter) % verbose_sleep_frequency))
		schedule_समयout_unपूर्णांकerruptible(verbose_sleep_duration);
पूर्ण
EXPORT_SYMBOL_GPL(verbose_torout_sleep);

/*
 * Schedule a high-resolution-समयr sleep in nanoseconds, with a 32-bit
 * nanosecond अक्रमom fuzz.  This function and its मित्रs desynchronize
 * testing from the समयr wheel.
 */
पूर्णांक torture_hrसमयout_ns(kसमय_प्रकार baset_ns, u32 fuzzt_ns, काष्ठा torture_अक्रमom_state *trsp)
अणु
	kसमय_प्रकार hto = baset_ns;

	अगर (trsp)
		hto += (torture_अक्रमom(trsp) >> 3) % fuzzt_ns;
	set_current_state(TASK_UNINTERRUPTIBLE);
	वापस schedule_hrसमयout(&hto, HRTIMER_MODE_REL);
पूर्ण
EXPORT_SYMBOL_GPL(torture_hrसमयout_ns);

/*
 * Schedule a high-resolution-समयr sleep in microseconds, with a 32-bit
 * nanosecond (not microsecond!) अक्रमom fuzz.
 */
पूर्णांक torture_hrसमयout_us(u32 baset_us, u32 fuzzt_ns, काष्ठा torture_अक्रमom_state *trsp)
अणु
	kसमय_प्रकार baset_ns = baset_us * NSEC_PER_USEC;

	वापस torture_hrसमयout_ns(baset_ns, fuzzt_ns, trsp);
पूर्ण
EXPORT_SYMBOL_GPL(torture_hrसमयout_us);

/*
 * Schedule a high-resolution-समयr sleep in milliseconds, with a 32-bit
 * microsecond (not millisecond!) अक्रमom fuzz.
 */
पूर्णांक torture_hrसमयout_ms(u32 baset_ms, u32 fuzzt_us, काष्ठा torture_अक्रमom_state *trsp)
अणु
	kसमय_प्रकार baset_ns = baset_ms * NSEC_PER_MSEC;
	u32 fuzzt_ns;

	अगर ((u32)~0U / NSEC_PER_USEC < fuzzt_us)
		fuzzt_ns = (u32)~0U;
	अन्यथा
		fuzzt_ns = fuzzt_us * NSEC_PER_USEC;
	वापस torture_hrसमयout_ns(baset_ns, fuzzt_ns, trsp);
पूर्ण
EXPORT_SYMBOL_GPL(torture_hrसमयout_ms);

/*
 * Schedule a high-resolution-समयr sleep in jअगरfies, with an
 * implied one-jअगरfy अक्रमom fuzz.  This is पूर्णांकended to replace calls to
 * schedule_समयout_पूर्णांकerruptible() and मित्रs.
 */
पूर्णांक torture_hrसमयout_jअगरfies(u32 baset_j, काष्ठा torture_अक्रमom_state *trsp)
अणु
	kसमय_प्रकार baset_ns = jअगरfies_to_nsecs(baset_j);

	वापस torture_hrसमयout_ns(baset_ns, jअगरfies_to_nsecs(1), trsp);
पूर्ण
EXPORT_SYMBOL_GPL(torture_hrसमयout_jअगरfies);

/*
 * Schedule a high-resolution-समयr sleep in milliseconds, with a 32-bit
 * millisecond (not second!) अक्रमom fuzz.
 */
पूर्णांक torture_hrसमयout_s(u32 baset_s, u32 fuzzt_ms, काष्ठा torture_अक्रमom_state *trsp)
अणु
	kसमय_प्रकार baset_ns = baset_s * NSEC_PER_SEC;
	u32 fuzzt_ns;

	अगर ((u32)~0U / NSEC_PER_MSEC < fuzzt_ms)
		fuzzt_ns = (u32)~0U;
	अन्यथा
		fuzzt_ns = fuzzt_ms * NSEC_PER_MSEC;
	वापस torture_hrसमयout_ns(baset_ns, fuzzt_ns, trsp);
पूर्ण
EXPORT_SYMBOL_GPL(torture_hrसमयout_s);

#अगर_घोषित CONFIG_HOTPLUG_CPU

/*
 * Variables क्रम online-offline handling.  Only present अगर CPU hotplug
 * is enabled, otherwise करोes nothing.
 */

अटल काष्ठा task_काष्ठा *onoff_task;
अटल दीर्घ onoff_holकरोff;
अटल दीर्घ onoff_पूर्णांकerval;
अटल torture_ofl_func *onoff_f;
अटल दीर्घ n_offline_attempts;
अटल दीर्घ n_offline_successes;
अटल अचिन्हित दीर्घ sum_offline;
अटल पूर्णांक min_offline = -1;
अटल पूर्णांक max_offline;
अटल दीर्घ n_online_attempts;
अटल दीर्घ n_online_successes;
अटल अचिन्हित दीर्घ sum_online;
अटल पूर्णांक min_online = -1;
अटल पूर्णांक max_online;

अटल पूर्णांक torture_online_cpus = NR_CPUS;

/*
 * Some torture testing leverages confusion as to the number of online
 * CPUs.  This function वापसs the torture-testing view of this number,
 * which allows torture tests to load-balance appropriately.
 */
पूर्णांक torture_num_online_cpus(व्योम)
अणु
	वापस READ_ONCE(torture_online_cpus);
पूर्ण
EXPORT_SYMBOL_GPL(torture_num_online_cpus);

/*
 * Attempt to take a CPU offline.  Return false अगर the CPU is alपढ़ोy
 * offline or अगर it is not subject to CPU-hotplug operations.  The
 * caller can detect other failures by looking at the statistics.
 */
bool torture_offline(पूर्णांक cpu, दीर्घ *n_offl_attempts, दीर्घ *n_offl_successes,
		     अचिन्हित दीर्घ *sum_offl, पूर्णांक *min_offl, पूर्णांक *max_offl)
अणु
	अचिन्हित दीर्घ delta;
	पूर्णांक ret;
	अक्षर *s;
	अचिन्हित दीर्घ startसमय;

	अगर (!cpu_online(cpu) || !cpu_is_hotpluggable(cpu))
		वापस false;
	अगर (num_online_cpus() <= 1)
		वापस false;  /* Can't offline the last CPU. */

	अगर (verbose > 1)
		pr_alert("%s" TORTURE_FLAG
			 "torture_onoff task: offlining %d\n",
			 torture_type, cpu);
	startसमय = jअगरfies;
	(*n_offl_attempts)++;
	ret = हटाओ_cpu(cpu);
	अगर (ret) अणु
		s = "";
		अगर (!rcu_inkernel_boot_has_ended() && ret == -EBUSY) अणु
			// PCI probe frequently disables hotplug during boot.
			(*n_offl_attempts)--;
			s = " (-EBUSY forgiven during boot)";
		पूर्ण
		अगर (verbose)
			pr_alert("%s" TORTURE_FLAG
				 "torture_onoff task: offline %d failed%s: errno %d\n",
				 torture_type, cpu, s, ret);
	पूर्ण अन्यथा अणु
		अगर (verbose > 1)
			pr_alert("%s" TORTURE_FLAG
				 "torture_onoff task: offlined %d\n",
				 torture_type, cpu);
		अगर (onoff_f)
			onoff_f();
		(*n_offl_successes)++;
		delta = jअगरfies - startसमय;
		*sum_offl += delta;
		अगर (*min_offl < 0) अणु
			*min_offl = delta;
			*max_offl = delta;
		पूर्ण
		अगर (*min_offl > delta)
			*min_offl = delta;
		अगर (*max_offl < delta)
			*max_offl = delta;
		WRITE_ONCE(torture_online_cpus, torture_online_cpus - 1);
		WARN_ON_ONCE(torture_online_cpus <= 0);
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(torture_offline);

/*
 * Attempt to bring a CPU online.  Return false अगर the CPU is alपढ़ोy
 * online or अगर it is not subject to CPU-hotplug operations.  The
 * caller can detect other failures by looking at the statistics.
 */
bool torture_online(पूर्णांक cpu, दीर्घ *n_onl_attempts, दीर्घ *n_onl_successes,
		    अचिन्हित दीर्घ *sum_onl, पूर्णांक *min_onl, पूर्णांक *max_onl)
अणु
	अचिन्हित दीर्घ delta;
	पूर्णांक ret;
	अक्षर *s;
	अचिन्हित दीर्घ startसमय;

	अगर (cpu_online(cpu) || !cpu_is_hotpluggable(cpu))
		वापस false;

	अगर (verbose > 1)
		pr_alert("%s" TORTURE_FLAG
			 "torture_onoff task: onlining %d\n",
			 torture_type, cpu);
	startसमय = jअगरfies;
	(*n_onl_attempts)++;
	ret = add_cpu(cpu);
	अगर (ret) अणु
		s = "";
		अगर (!rcu_inkernel_boot_has_ended() && ret == -EBUSY) अणु
			// PCI probe frequently disables hotplug during boot.
			(*n_onl_attempts)--;
			s = " (-EBUSY forgiven during boot)";
		पूर्ण
		अगर (verbose)
			pr_alert("%s" TORTURE_FLAG
				 "torture_onoff task: online %d failed%s: errno %d\n",
				 torture_type, cpu, s, ret);
	पूर्ण अन्यथा अणु
		अगर (verbose > 1)
			pr_alert("%s" TORTURE_FLAG
				 "torture_onoff task: onlined %d\n",
				 torture_type, cpu);
		(*n_onl_successes)++;
		delta = jअगरfies - startसमय;
		*sum_onl += delta;
		अगर (*min_onl < 0) अणु
			*min_onl = delta;
			*max_onl = delta;
		पूर्ण
		अगर (*min_onl > delta)
			*min_onl = delta;
		अगर (*max_onl < delta)
			*max_onl = delta;
		WRITE_ONCE(torture_online_cpus, torture_online_cpus + 1);
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(torture_online);

/*
 * Get everything online at the beginning and ends of tests.
 */
अटल व्योम torture_online_all(अक्षर *phase)
अणु
	पूर्णांक cpu;
	पूर्णांक ret;

	क्रम_each_possible_cpu(cpu) अणु
		अगर (cpu_online(cpu))
			जारी;
		ret = add_cpu(cpu);
		अगर (ret && verbose) अणु
			pr_alert("%s" TORTURE_FLAG
				 "%s: %s online %d: errno %d\n",
				 __func__, phase, torture_type, cpu, ret);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Execute अक्रमom CPU-hotplug operations at the पूर्णांकerval specअगरied
 * by the onoff_पूर्णांकerval.
 */
अटल पूर्णांक
torture_onoff(व्योम *arg)
अणु
	पूर्णांक cpu;
	पूर्णांक maxcpu = -1;
	DEFINE_TORTURE_RANDOM(अक्रम);

	VERBOSE_TOROUT_STRING("torture_onoff task started");
	क्रम_each_online_cpu(cpu)
		maxcpu = cpu;
	WARN_ON(maxcpu < 0);
	torture_online_all("Initial");
	अगर (maxcpu == 0) अणु
		VERBOSE_TOROUT_STRING("Only one CPU, so CPU-hotplug testing is disabled");
		जाओ stop;
	पूर्ण

	अगर (onoff_holकरोff > 0) अणु
		VERBOSE_TOROUT_STRING("torture_onoff begin holdoff");
		schedule_समयout_पूर्णांकerruptible(onoff_holकरोff);
		VERBOSE_TOROUT_STRING("torture_onoff end holdoff");
	पूर्ण
	जबतक (!torture_must_stop()) अणु
		अगर (disable_onoff_at_boot && !rcu_inkernel_boot_has_ended()) अणु
			schedule_समयout_पूर्णांकerruptible(HZ / 10);
			जारी;
		पूर्ण
		cpu = (torture_अक्रमom(&अक्रम) >> 4) % (maxcpu + 1);
		अगर (!torture_offline(cpu,
				     &n_offline_attempts, &n_offline_successes,
				     &sum_offline, &min_offline, &max_offline))
			torture_online(cpu,
				       &n_online_attempts, &n_online_successes,
				       &sum_online, &min_online, &max_online);
		schedule_समयout_पूर्णांकerruptible(onoff_पूर्णांकerval);
	पूर्ण

stop:
	torture_kthपढ़ो_stopping("torture_onoff");
	torture_online_all("Final");
	वापस 0;
पूर्ण

#पूर्ण_अगर /* #अगर_घोषित CONFIG_HOTPLUG_CPU */

/*
 * Initiate online-offline handling.
 */
पूर्णांक torture_onoff_init(दीर्घ ooholकरोff, दीर्घ ooपूर्णांकerval, torture_ofl_func *f)
अणु
#अगर_घोषित CONFIG_HOTPLUG_CPU
	onoff_holकरोff = ooholकरोff;
	onoff_पूर्णांकerval = ooपूर्णांकerval;
	onoff_f = f;
	अगर (onoff_पूर्णांकerval <= 0)
		वापस 0;
	वापस torture_create_kthपढ़ो(torture_onoff, शून्य, onoff_task);
#अन्यथा /* #अगर_घोषित CONFIG_HOTPLUG_CPU */
	वापस 0;
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_HOTPLUG_CPU */
पूर्ण
EXPORT_SYMBOL_GPL(torture_onoff_init);

/*
 * Clean up after online/offline testing.
 */
अटल व्योम torture_onoff_cleanup(व्योम)
अणु
#अगर_घोषित CONFIG_HOTPLUG_CPU
	अगर (onoff_task == शून्य)
		वापस;
	VERBOSE_TOROUT_STRING("Stopping torture_onoff task");
	kthपढ़ो_stop(onoff_task);
	onoff_task = शून्य;
#पूर्ण_अगर /* #अगर_घोषित CONFIG_HOTPLUG_CPU */
पूर्ण

/*
 * Prपूर्णांक online/offline testing statistics.
 */
व्योम torture_onoff_stats(व्योम)
अणु
#अगर_घोषित CONFIG_HOTPLUG_CPU
	pr_cont("onoff: %ld/%ld:%ld/%ld %d,%d:%d,%d %lu:%lu (HZ=%d) ",
		n_online_successes, n_online_attempts,
		n_offline_successes, n_offline_attempts,
		min_online, max_online,
		min_offline, max_offline,
		sum_online, sum_offline, HZ);
#पूर्ण_अगर /* #अगर_घोषित CONFIG_HOTPLUG_CPU */
पूर्ण
EXPORT_SYMBOL_GPL(torture_onoff_stats);

/*
 * Were all the online/offline operations successful?
 */
bool torture_onoff_failures(व्योम)
अणु
#अगर_घोषित CONFIG_HOTPLUG_CPU
	वापस n_online_successes != n_online_attempts ||
	       n_offline_successes != n_offline_attempts;
#अन्यथा /* #अगर_घोषित CONFIG_HOTPLUG_CPU */
	वापस false;
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_HOTPLUG_CPU */
पूर्ण
EXPORT_SYMBOL_GPL(torture_onoff_failures);

#घोषणा TORTURE_RANDOM_MULT	39916801  /* prime */
#घोषणा TORTURE_RANDOM_ADD	479001701 /* prime */
#घोषणा TORTURE_RANDOM_REFRESH	10000

/*
 * Crude but fast अक्रमom-number generator.  Uses a linear congruential
 * generator, with occasional help from cpu_घड़ी().
 */
अचिन्हित दीर्घ
torture_अक्रमom(काष्ठा torture_अक्रमom_state *trsp)
अणु
	अगर (--trsp->trs_count < 0) अणु
		trsp->trs_state += (अचिन्हित दीर्घ)local_घड़ी();
		trsp->trs_count = TORTURE_RANDOM_REFRESH;
	पूर्ण
	trsp->trs_state = trsp->trs_state * TORTURE_RANDOM_MULT +
		TORTURE_RANDOM_ADD;
	वापस swahw32(trsp->trs_state);
पूर्ण
EXPORT_SYMBOL_GPL(torture_अक्रमom);

/*
 * Variables क्रम shuffling.  The idea is to ensure that each CPU stays
 * idle क्रम an extended period to test पूर्णांकeractions with dyntick idle,
 * as well as पूर्णांकeractions with any per-CPU variables.
 */
काष्ठा shuffle_task अणु
	काष्ठा list_head st_l;
	काष्ठा task_काष्ठा *st_t;
पूर्ण;

अटल दीर्घ shuffle_पूर्णांकerval;	/* In jअगरfies. */
अटल काष्ठा task_काष्ठा *shuffler_task;
अटल cpumask_var_t shuffle_पंचांगp_mask;
अटल पूर्णांक shuffle_idle_cpu;	/* Force all torture tasks off this CPU */
अटल काष्ठा list_head shuffle_task_list = LIST_HEAD_INIT(shuffle_task_list);
अटल DEFINE_MUTEX(shuffle_task_mutex);

/*
 * Register a task to be shuffled.  If there is no memory, just splat
 * and करोn't bother रेजिस्टरing.
 */
व्योम torture_shuffle_task_रेजिस्टर(काष्ठा task_काष्ठा *tp)
अणु
	काष्ठा shuffle_task *stp;

	अगर (WARN_ON_ONCE(tp == शून्य))
		वापस;
	stp = kदो_स्मृति(माप(*stp), GFP_KERNEL);
	अगर (WARN_ON_ONCE(stp == शून्य))
		वापस;
	stp->st_t = tp;
	mutex_lock(&shuffle_task_mutex);
	list_add(&stp->st_l, &shuffle_task_list);
	mutex_unlock(&shuffle_task_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(torture_shuffle_task_रेजिस्टर);

/*
 * Unरेजिस्टर all tasks, क्रम example, at the end of the torture run.
 */
अटल व्योम torture_shuffle_task_unरेजिस्टर_all(व्योम)
अणु
	काष्ठा shuffle_task *stp;
	काष्ठा shuffle_task *p;

	mutex_lock(&shuffle_task_mutex);
	list_क्रम_each_entry_safe(stp, p, &shuffle_task_list, st_l) अणु
		list_del(&stp->st_l);
		kमुक्त(stp);
	पूर्ण
	mutex_unlock(&shuffle_task_mutex);
पूर्ण

/* Shuffle tasks such that we allow shuffle_idle_cpu to become idle.
 * A special हाल is when shuffle_idle_cpu = -1, in which हाल we allow
 * the tasks to run on all CPUs.
 */
अटल व्योम torture_shuffle_tasks(व्योम)
अणु
	काष्ठा shuffle_task *stp;

	cpumask_setall(shuffle_पंचांगp_mask);
	get_online_cpus();

	/* No poपूर्णांक in shuffling अगर there is only one online CPU (ex: UP) */
	अगर (num_online_cpus() == 1) अणु
		put_online_cpus();
		वापस;
	पूर्ण

	/* Advance to the next CPU.  Upon overflow, करोn't idle any CPUs. */
	shuffle_idle_cpu = cpumask_next(shuffle_idle_cpu, shuffle_पंचांगp_mask);
	अगर (shuffle_idle_cpu >= nr_cpu_ids)
		shuffle_idle_cpu = -1;
	अन्यथा
		cpumask_clear_cpu(shuffle_idle_cpu, shuffle_पंचांगp_mask);

	mutex_lock(&shuffle_task_mutex);
	list_क्रम_each_entry(stp, &shuffle_task_list, st_l)
		set_cpus_allowed_ptr(stp->st_t, shuffle_पंचांगp_mask);
	mutex_unlock(&shuffle_task_mutex);

	put_online_cpus();
पूर्ण

/* Shuffle tasks across CPUs, with the पूर्णांकent of allowing each CPU in the
 * प्रणाली to become idle at a समय and cut off its समयr ticks. This is meant
 * to test the support क्रम such tickless idle CPU in RCU.
 */
अटल पूर्णांक torture_shuffle(व्योम *arg)
अणु
	VERBOSE_TOROUT_STRING("torture_shuffle task started");
	करो अणु
		schedule_समयout_पूर्णांकerruptible(shuffle_पूर्णांकerval);
		torture_shuffle_tasks();
		torture_shutकरोwn_असलorb("torture_shuffle");
	पूर्ण जबतक (!torture_must_stop());
	torture_kthपढ़ो_stopping("torture_shuffle");
	वापस 0;
पूर्ण

/*
 * Start the shuffler, with shuffपूर्णांक in jअगरfies.
 */
पूर्णांक torture_shuffle_init(दीर्घ shuffपूर्णांक)
अणु
	shuffle_पूर्णांकerval = shuffपूर्णांक;

	shuffle_idle_cpu = -1;

	अगर (!alloc_cpumask_var(&shuffle_पंचांगp_mask, GFP_KERNEL)) अणु
		VERBOSE_TOROUT_ERRSTRING("Failed to alloc mask");
		वापस -ENOMEM;
	पूर्ण

	/* Create the shuffler thपढ़ो */
	वापस torture_create_kthपढ़ो(torture_shuffle, शून्य, shuffler_task);
पूर्ण
EXPORT_SYMBOL_GPL(torture_shuffle_init);

/*
 * Stop the shuffling.
 */
अटल व्योम torture_shuffle_cleanup(व्योम)
अणु
	torture_shuffle_task_unरेजिस्टर_all();
	अगर (shuffler_task) अणु
		VERBOSE_TOROUT_STRING("Stopping torture_shuffle task");
		kthपढ़ो_stop(shuffler_task);
		मुक्त_cpumask_var(shuffle_पंचांगp_mask);
	पूर्ण
	shuffler_task = शून्य;
पूर्ण

/*
 * Variables क्रम स्वतः-shutकरोwn.  This allows "lights out" torture runs
 * to be fully scripted.
 */
अटल काष्ठा task_काष्ठा *shutकरोwn_task;
अटल kसमय_प्रकार shutकरोwn_समय;		/* समय to प्रणाली shutकरोwn. */
अटल व्योम (*torture_shutकरोwn_hook)(व्योम);

/*
 * Absorb kthपढ़ोs पूर्णांकo a kernel function that won't वापस, so that
 * they won't ever access module text or data again.
 */
व्योम torture_shutकरोwn_असलorb(स्थिर अक्षर *title)
अणु
	जबतक (READ_ONCE(fullstop) == FULLSTOP_SHUTDOWN) अणु
		pr_notice("torture thread %s parking due to system shutdown\n",
			  title);
		schedule_समयout_unपूर्णांकerruptible(MAX_SCHEDULE_TIMEOUT);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(torture_shutकरोwn_असलorb);

/*
 * Cause the torture test to shutकरोwn the प्रणाली after the test has
 * run क्रम the समय specअगरied by the shutकरोwn_secs parameter.
 */
अटल पूर्णांक torture_shutकरोwn(व्योम *arg)
अणु
	kसमय_प्रकार kसमय_snap;

	VERBOSE_TOROUT_STRING("torture_shutdown task started");
	kसमय_snap = kसमय_get();
	जबतक (kसमय_beक्रमe(kसमय_snap, shutकरोwn_समय) &&
	       !torture_must_stop()) अणु
		अगर (verbose)
			pr_alert("%s" TORTURE_FLAG
				 "torture_shutdown task: %llu ms remaining\n",
				 torture_type,
				 kसमय_ms_delta(shutकरोwn_समय, kसमय_snap));
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_hrसमयout(&shutकरोwn_समय, HRTIMER_MODE_ABS);
		kसमय_snap = kसमय_get();
	पूर्ण
	अगर (torture_must_stop()) अणु
		torture_kthपढ़ो_stopping("torture_shutdown");
		वापस 0;
	पूर्ण

	/* OK, shut करोwn the प्रणाली. */

	VERBOSE_TOROUT_STRING("torture_shutdown task shutting down system");
	shutकरोwn_task = शून्य;	/* Aव्योम self-समाप्त deadlock. */
	अगर (torture_shutकरोwn_hook)
		torture_shutकरोwn_hook();
	अन्यथा
		VERBOSE_TOROUT_STRING("No torture_shutdown_hook(), skipping.");
	अगर (ftrace_dump_at_shutकरोwn)
		rcu_ftrace_dump(DUMP_ALL);
	kernel_घातer_off();	/* Shut करोwn the प्रणाली. */
	वापस 0;
पूर्ण

/*
 * Start up the shutकरोwn task.
 */
पूर्णांक torture_shutकरोwn_init(पूर्णांक ssecs, व्योम (*cleanup)(व्योम))
अणु
	torture_shutकरोwn_hook = cleanup;
	अगर (ssecs > 0) अणु
		shutकरोwn_समय = kसमय_add(kसमय_get(), kसमय_set(ssecs, 0));
		वापस torture_create_kthपढ़ो(torture_shutकरोwn, शून्य,
					     shutकरोwn_task);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(torture_shutकरोwn_init);

/*
 * Detect and respond to a प्रणाली shutकरोwn.
 */
अटल पूर्णांक torture_shutकरोwn_notअगरy(काष्ठा notअगरier_block *unused1,
				   अचिन्हित दीर्घ unused2, व्योम *unused3)
अणु
	mutex_lock(&fullstop_mutex);
	अगर (READ_ONCE(fullstop) == FULLSTOP_DONTSTOP) अणु
		VERBOSE_TOROUT_STRING("Unscheduled system shutdown detected");
		WRITE_ONCE(fullstop, FULLSTOP_SHUTDOWN);
	पूर्ण अन्यथा अणु
		pr_warn("Concurrent rmmod and shutdown illegal!\n");
	पूर्ण
	mutex_unlock(&fullstop_mutex);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block torture_shutकरोwn_nb = अणु
	.notअगरier_call = torture_shutकरोwn_notअगरy,
पूर्ण;

/*
 * Shut करोwn the shutकरोwn task.  Say what???  Heh!  This can happen अगर
 * the torture module माला_लो an rmmod beक्रमe the shutकरोwn समय arrives.  ;-)
 */
अटल व्योम torture_shutकरोwn_cleanup(व्योम)
अणु
	unरेजिस्टर_reboot_notअगरier(&torture_shutकरोwn_nb);
	अगर (shutकरोwn_task != शून्य) अणु
		VERBOSE_TOROUT_STRING("Stopping torture_shutdown task");
		kthपढ़ो_stop(shutकरोwn_task);
	पूर्ण
	shutकरोwn_task = शून्य;
पूर्ण

/*
 * Variables क्रम stuttering, which means to periodically छोड़ो and
 * restart testing in order to catch bugs that appear when load is
 * suddenly applied to or हटाओd from the प्रणाली.
 */
अटल काष्ठा task_काष्ठा *stutter_task;
अटल पूर्णांक stutter_छोड़ो_test;
अटल पूर्णांक stutter;
अटल पूर्णांक stutter_gap;

/*
 * Block until the stutter पूर्णांकerval ends.  This must be called periodically
 * by all running kthपढ़ोs that need to be subject to stuttering.
 */
bool stutter_रुको(स्थिर अक्षर *title)
अणु
	अचिन्हित पूर्णांक i = 0;
	bool ret = false;
	पूर्णांक spt;

	cond_resched_tasks_rcu_qs();
	spt = READ_ONCE(stutter_छोड़ो_test);
	क्रम (; spt; spt = READ_ONCE(stutter_छोड़ो_test)) अणु
		अगर (!ret) अणु
			sched_set_normal(current, MAX_NICE);
			ret = true;
		पूर्ण
		अगर (spt == 1) अणु
			schedule_समयout_पूर्णांकerruptible(1);
		पूर्ण अन्यथा अगर (spt == 2) अणु
			जबतक (READ_ONCE(stutter_छोड़ो_test)) अणु
				अगर (!(i++ & 0xffff))
					torture_hrसमयout_us(10, 0, शून्य);
				cond_resched();
			पूर्ण
		पूर्ण अन्यथा अणु
			schedule_समयout_पूर्णांकerruptible(round_jअगरfies_relative(HZ));
		पूर्ण
		torture_shutकरोwn_असलorb(title);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(stutter_रुको);

/*
 * Cause the torture test to "stutter", starting and stopping all
 * thपढ़ोs periodically.
 */
अटल पूर्णांक torture_stutter(व्योम *arg)
अणु
	DEFINE_TORTURE_RANDOM(अक्रम);
	पूर्णांक wसमय;

	VERBOSE_TOROUT_STRING("torture_stutter task started");
	करो अणु
		अगर (!torture_must_stop() && stutter > 1) अणु
			wसमय = stutter;
			अगर (stutter > 2) अणु
				WRITE_ONCE(stutter_छोड़ो_test, 1);
				wसमय = stutter - 3;
				torture_hrसमयout_jअगरfies(wसमय, &अक्रम);
				wसमय = 2;
			पूर्ण
			WRITE_ONCE(stutter_छोड़ो_test, 2);
			torture_hrसमयout_jअगरfies(wसमय, शून्य);
		पूर्ण
		WRITE_ONCE(stutter_छोड़ो_test, 0);
		अगर (!torture_must_stop())
			torture_hrसमयout_jअगरfies(stutter_gap, शून्य);
		torture_shutकरोwn_असलorb("torture_stutter");
	पूर्ण जबतक (!torture_must_stop());
	torture_kthपढ़ो_stopping("torture_stutter");
	वापस 0;
पूर्ण

/*
 * Initialize and kick off the torture_stutter kthपढ़ो.
 */
पूर्णांक torture_stutter_init(स्थिर पूर्णांक s, स्थिर पूर्णांक sgap)
अणु
	stutter = s;
	stutter_gap = sgap;
	वापस torture_create_kthपढ़ो(torture_stutter, शून्य, stutter_task);
पूर्ण
EXPORT_SYMBOL_GPL(torture_stutter_init);

/*
 * Cleanup after the torture_stutter kthपढ़ो.
 */
अटल व्योम torture_stutter_cleanup(व्योम)
अणु
	अगर (!stutter_task)
		वापस;
	VERBOSE_TOROUT_STRING("Stopping torture_stutter task");
	kthपढ़ो_stop(stutter_task);
	stutter_task = शून्य;
पूर्ण

/*
 * Initialize torture module.  Please note that this is -not- invoked via
 * the usual module_init() mechanism, but rather by an explicit call from
 * the client torture module.  This call must be paired with a later
 * torture_init_end().
 *
 * The runnable parameter poपूर्णांकs to a flag that controls whether or not
 * the test is currently runnable.  If there is no such flag, pass in शून्य.
 */
bool torture_init_begin(अक्षर *ttype, पूर्णांक v)
अणु
	mutex_lock(&fullstop_mutex);
	अगर (torture_type != शून्य) अणु
		pr_alert("%s: Refusing %s init: %s running.\n",
			  __func__, ttype, torture_type);
		pr_alert("%s: One torture test at a time!\n", __func__);
		mutex_unlock(&fullstop_mutex);
		वापस false;
	पूर्ण
	torture_type = ttype;
	verbose = v;
	fullstop = FULLSTOP_DONTSTOP;
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(torture_init_begin);

/*
 * Tell the torture module that initialization is complete.
 */
व्योम torture_init_end(व्योम)
अणु
	mutex_unlock(&fullstop_mutex);
	रेजिस्टर_reboot_notअगरier(&torture_shutकरोwn_nb);
पूर्ण
EXPORT_SYMBOL_GPL(torture_init_end);

/*
 * Clean up torture module.  Please note that this is -not- invoked via
 * the usual module_निकास() mechanism, but rather by an explicit call from
 * the client torture module.  Returns true अगर a race with प्रणाली shutकरोwn
 * is detected, otherwise, all kthपढ़ोs started by functions in this file
 * will be shut करोwn.
 *
 * This must be called beक्रमe the caller starts shutting करोwn its own
 * kthपढ़ोs.
 *
 * Both torture_cleanup_begin() and torture_cleanup_end() must be paired,
 * in order to correctly perक्रमm the cleanup. They are separated because
 * thपढ़ोs can still need to reference the torture_type type, thus nullअगरy
 * only after completing all other relevant calls.
 */
bool torture_cleanup_begin(व्योम)
अणु
	mutex_lock(&fullstop_mutex);
	अगर (READ_ONCE(fullstop) == FULLSTOP_SHUTDOWN) अणु
		pr_warn("Concurrent rmmod and shutdown illegal!\n");
		mutex_unlock(&fullstop_mutex);
		schedule_समयout_unपूर्णांकerruptible(10);
		वापस true;
	पूर्ण
	WRITE_ONCE(fullstop, FULLSTOP_RMMOD);
	mutex_unlock(&fullstop_mutex);
	torture_shutकरोwn_cleanup();
	torture_shuffle_cleanup();
	torture_stutter_cleanup();
	torture_onoff_cleanup();
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(torture_cleanup_begin);

व्योम torture_cleanup_end(व्योम)
अणु
	mutex_lock(&fullstop_mutex);
	torture_type = शून्य;
	mutex_unlock(&fullstop_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(torture_cleanup_end);

/*
 * Is it समय क्रम the current torture test to stop?
 */
bool torture_must_stop(व्योम)
अणु
	वापस torture_must_stop_irq() || kthपढ़ो_should_stop();
पूर्ण
EXPORT_SYMBOL_GPL(torture_must_stop);

/*
 * Is it समय क्रम the current torture test to stop?  This is the irq-safe
 * version, hence no check क्रम kthपढ़ो_should_stop().
 */
bool torture_must_stop_irq(व्योम)
अणु
	वापस READ_ONCE(fullstop) != FULLSTOP_DONTSTOP;
पूर्ण
EXPORT_SYMBOL_GPL(torture_must_stop_irq);

/*
 * Each kthपढ़ो must रुको क्रम kthपढ़ो_should_stop() beक्रमe वापसing from
 * its top-level function, otherwise segfaults ensue.  This function
 * prपूर्णांकs a "stopping" message and रुकोs क्रम kthपढ़ो_should_stop(), and
 * should be called from all torture kthपढ़ोs immediately prior to
 * वापसing.
 */
व्योम torture_kthपढ़ो_stopping(अक्षर *title)
अणु
	अक्षर buf[128];

	snम_लिखो(buf, माप(buf), "Stopping %s", title);
	VERBOSE_TOROUT_STRING(buf);
	जबतक (!kthपढ़ो_should_stop()) अणु
		torture_shutकरोwn_असलorb(title);
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(torture_kthपढ़ो_stopping);

/*
 * Create a generic torture kthपढ़ो that is immediately runnable.  If you
 * need the kthपढ़ो to be stopped so that you can करो something to it beक्रमe
 * it starts, you will need to खोलो-code your own.
 */
पूर्णांक _torture_create_kthपढ़ो(पूर्णांक (*fn)(व्योम *arg), व्योम *arg, अक्षर *s, अक्षर *m,
			    अक्षर *f, काष्ठा task_काष्ठा **tp)
अणु
	पूर्णांक ret = 0;

	VERBOSE_TOROUT_STRING(m);
	*tp = kthपढ़ो_run(fn, arg, "%s", s);
	अगर (IS_ERR(*tp)) अणु
		ret = PTR_ERR(*tp);
		VERBOSE_TOROUT_ERRSTRING(f);
		*tp = शून्य;
	पूर्ण
	torture_shuffle_task_रेजिस्टर(*tp);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(_torture_create_kthपढ़ो);

/*
 * Stop a generic kthपढ़ो, emitting a message.
 */
व्योम _torture_stop_kthपढ़ो(अक्षर *m, काष्ठा task_काष्ठा **tp)
अणु
	अगर (*tp == शून्य)
		वापस;
	VERBOSE_TOROUT_STRING(m);
	kthपढ़ो_stop(*tp);
	*tp = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(_torture_stop_kthपढ़ो);
