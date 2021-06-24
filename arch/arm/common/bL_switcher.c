<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/common/bL_चयनer.c -- big.LITTLE cluster चयनer core driver
 *
 * Created by:	Nicolas Pitre, March 2012
 * Copyright:	(C) 2012-2013  Linaro Limited
 */

#समावेश <linux/atomic.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <uapi/linux/sched/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/cpu_pm.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/रुको.h>
#समावेश <linux/समय.स>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/tick.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/mm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/smp.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/sysfs.h>
#समावेश <linux/irqchip/arm-gic.h>
#समावेश <linux/moduleparam.h>

#समावेश <यंत्र/smp_plat.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/suspend.h>
#समावेश <यंत्र/mcpm.h>
#समावेश <यंत्र/bL_चयनer.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/घातer_cpu_migrate.h>


/*
 * Use our own MPIDR accessors as the generic ones in यंत्र/cputype.h have
 * __attribute_स्थिर__ and we करोn't want the compiler to assume any
 * स्थिरness here as the value _करोes_ change aदीर्घ some code paths.
 */

अटल पूर्णांक पढ़ो_mpidr(व्योम)
अणु
	अचिन्हित पूर्णांक id;
	यंत्र अस्थिर ("mrc p15, 0, %0, c0, c0, 5" : "=r" (id));
	वापस id & MPIDR_HWID_BITMASK;
पूर्ण

/*
 * bL चयनer core code.
 */

अटल व्योम bL_करो_चयन(व्योम *_arg)
अणु
	अचिन्हित ib_mpidr, ib_cpu, ib_cluster;
	दीर्घ अस्थिर handshake, **handshake_ptr = _arg;

	pr_debug("%s\n", __func__);

	ib_mpidr = cpu_logical_map(smp_processor_id());
	ib_cpu = MPIDR_AFFINITY_LEVEL(ib_mpidr, 0);
	ib_cluster = MPIDR_AFFINITY_LEVEL(ib_mpidr, 1);

	/* Advertise our handshake location */
	अगर (handshake_ptr) अणु
		handshake = 0;
		*handshake_ptr = &handshake;
	पूर्ण अन्यथा
		handshake = -1;

	/*
	 * Our state has been saved at this poपूर्णांक.  Let's release our
	 * inbound CPU.
	 */
	mcpm_set_entry_vector(ib_cpu, ib_cluster, cpu_resume);
	sev();

	/*
	 * From this poपूर्णांक, we must assume that our counterpart CPU might
	 * have taken over in its parallel world alपढ़ोy, as अगर execution
	 * just वापसed from cpu_suspend().  It is thereक्रमe important to
	 * be very careful not to make any change the other guy is not
	 * expecting.  This is why we need stack isolation.
	 *
	 * Fancy under cover tasks could be perक्रमmed here.  For now
	 * we have none.
	 */

	/*
	 * Let's रुको until our inbound is alive.
	 */
	जबतक (!handshake) अणु
		wfe();
		smp_mb();
	पूर्ण

	/* Let's put ourself करोwn. */
	mcpm_cpu_घातer_करोwn();

	/* should never get here */
	BUG();
पूर्ण

/*
 * Stack isolation.  To ensure 'current' reमुख्यs valid, we just use another
 * piece of our thपढ़ो's stack space which should be fairly lightly used.
 * The selected area starts just above the thपढ़ो_info काष्ठाure located
 * at the very bottom of the stack, aligned to a cache line, and indexed
 * with the cluster number.
 */
#घोषणा STACK_SIZE 512
बाह्य व्योम call_with_stack(व्योम (*fn)(व्योम *), व्योम *arg, व्योम *sp);
अटल पूर्णांक bL_चयनpoपूर्णांक(अचिन्हित दीर्घ _arg)
अणु
	अचिन्हित पूर्णांक mpidr = पढ़ो_mpidr();
	अचिन्हित पूर्णांक clusterid = MPIDR_AFFINITY_LEVEL(mpidr, 1);
	व्योम *stack = current_thपढ़ो_info() + 1;
	stack = PTR_ALIGN(stack, L1_CACHE_BYTES);
	stack += clusterid * STACK_SIZE + STACK_SIZE;
	call_with_stack(bL_करो_चयन, (व्योम *)_arg, stack);
	BUG();
पूर्ण

/*
 * Generic चयनer पूर्णांकerface
 */

अटल अचिन्हित पूर्णांक bL_gic_id[MAX_CPUS_PER_CLUSTER][MAX_NR_CLUSTERS];
अटल पूर्णांक bL_चयनer_cpu_pairing[NR_CPUS];

/*
 * bL_चयन_to - Switch to a specअगरic cluster क्रम the current CPU
 * @new_cluster_id: the ID of the cluster to चयन to.
 *
 * This function must be called on the CPU to be चयनed.
 * Returns 0 on success, अन्यथा a negative status code.
 */
अटल पूर्णांक bL_चयन_to(अचिन्हित पूर्णांक new_cluster_id)
अणु
	अचिन्हित पूर्णांक mpidr, this_cpu, that_cpu;
	अचिन्हित पूर्णांक ob_mpidr, ob_cpu, ob_cluster, ib_mpidr, ib_cpu, ib_cluster;
	काष्ठा completion inbound_alive;
	दीर्घ अस्थिर *handshake_ptr;
	पूर्णांक ipi_nr, ret;

	this_cpu = smp_processor_id();
	ob_mpidr = पढ़ो_mpidr();
	ob_cpu = MPIDR_AFFINITY_LEVEL(ob_mpidr, 0);
	ob_cluster = MPIDR_AFFINITY_LEVEL(ob_mpidr, 1);
	BUG_ON(cpu_logical_map(this_cpu) != ob_mpidr);

	अगर (new_cluster_id == ob_cluster)
		वापस 0;

	that_cpu = bL_चयनer_cpu_pairing[this_cpu];
	ib_mpidr = cpu_logical_map(that_cpu);
	ib_cpu = MPIDR_AFFINITY_LEVEL(ib_mpidr, 0);
	ib_cluster = MPIDR_AFFINITY_LEVEL(ib_mpidr, 1);

	pr_debug("before switch: CPU %d MPIDR %#x -> %#x\n",
		 this_cpu, ob_mpidr, ib_mpidr);

	this_cpu = smp_processor_id();

	/* Close the gate क्रम our entry vectors */
	mcpm_set_entry_vector(ob_cpu, ob_cluster, शून्य);
	mcpm_set_entry_vector(ib_cpu, ib_cluster, शून्य);

	/* Install our "inbound alive" notअगरier. */
	init_completion(&inbound_alive);
	ipi_nr = रेजिस्टर_ipi_completion(&inbound_alive, this_cpu);
	ipi_nr |= ((1 << 16) << bL_gic_id[ob_cpu][ob_cluster]);
	mcpm_set_early_poke(ib_cpu, ib_cluster, gic_get_sgir_physaddr(), ipi_nr);

	/*
	 * Let's wake up the inbound CPU now in हाल it requires some delay
	 * to come online, but leave it gated in our entry vector code.
	 */
	ret = mcpm_cpu_घातer_up(ib_cpu, ib_cluster);
	अगर (ret) अणु
		pr_err("%s: mcpm_cpu_power_up() returned %d\n", __func__, ret);
		वापस ret;
	पूर्ण

	/*
	 * Raise a SGI on the inbound CPU to make sure it करोesn't stall
	 * in a possible WFI, such as in bL_घातer_करोwn().
	 */
	gic_send_sgi(bL_gic_id[ib_cpu][ib_cluster], 0);

	/*
	 * Wait क्रम the inbound to come up.  This allows क्रम other
	 * tasks to be scheduled in the mean समय.
	 */
	रुको_क्रम_completion(&inbound_alive);
	mcpm_set_early_poke(ib_cpu, ib_cluster, 0, 0);

	/*
	 * From this poपूर्णांक we are entering the चयन critical zone
	 * and can't take any पूर्णांकerrupts anymore.
	 */
	local_irq_disable();
	local_fiq_disable();
	trace_cpu_migrate_begin(kसमय_get_real_ns(), ob_mpidr);

	/* redirect GIC's SGIs to our counterpart */
	gic_migrate_target(bL_gic_id[ib_cpu][ib_cluster]);

	tick_suspend_local();

	ret = cpu_pm_enter();

	/* we can not tolerate errors at this poपूर्णांक */
	अगर (ret)
		panic("%s: cpu_pm_enter() returned %d\n", __func__, ret);

	/* Swap the physical CPUs in the logical map क्रम this logical CPU. */
	cpu_logical_map(this_cpu) = ib_mpidr;
	cpu_logical_map(that_cpu) = ob_mpidr;

	/* Let's करो the actual CPU चयन. */
	ret = cpu_suspend((अचिन्हित दीर्घ)&handshake_ptr, bL_चयनpoपूर्णांक);
	अगर (ret > 0)
		panic("%s: cpu_suspend() returned %d\n", __func__, ret);

	/* We are executing on the inbound CPU at this poपूर्णांक */
	mpidr = पढ़ो_mpidr();
	pr_debug("after switch: CPU %d MPIDR %#x\n", this_cpu, mpidr);
	BUG_ON(mpidr != ib_mpidr);

	mcpm_cpu_घातered_up();

	ret = cpu_pm_निकास();

	tick_resume_local();

	trace_cpu_migrate_finish(kसमय_get_real_ns(), ib_mpidr);
	local_fiq_enable();
	local_irq_enable();

	*handshake_ptr = 1;
	dsb_sev();

	अगर (ret)
		pr_err("%s exiting with error %d\n", __func__, ret);
	वापस ret;
पूर्ण

काष्ठा bL_thपढ़ो अणु
	spinlock_t lock;
	काष्ठा task_काष्ठा *task;
	रुको_queue_head_t wq;
	पूर्णांक wanted_cluster;
	काष्ठा completion started;
	bL_चयन_completion_handler completer;
	व्योम *completer_cookie;
पूर्ण;

अटल काष्ठा bL_thपढ़ो bL_thपढ़ोs[NR_CPUS];

अटल पूर्णांक bL_चयनer_thपढ़ो(व्योम *arg)
अणु
	काष्ठा bL_thपढ़ो *t = arg;
	पूर्णांक cluster;
	bL_चयन_completion_handler completer;
	व्योम *completer_cookie;

	sched_set_fअगरo_low(current);
	complete(&t->started);

	करो अणु
		अगर (संकेत_pending(current))
			flush_संकेतs(current);
		रुको_event_पूर्णांकerruptible(t->wq,
				t->wanted_cluster != -1 ||
				kthपढ़ो_should_stop());

		spin_lock(&t->lock);
		cluster = t->wanted_cluster;
		completer = t->completer;
		completer_cookie = t->completer_cookie;
		t->wanted_cluster = -1;
		t->completer = शून्य;
		spin_unlock(&t->lock);

		अगर (cluster != -1) अणु
			bL_चयन_to(cluster);

			अगर (completer)
				completer(completer_cookie);
		पूर्ण
	पूर्ण जबतक (!kthपढ़ो_should_stop());

	वापस 0;
पूर्ण

अटल काष्ठा task_काष्ठा *bL_चयनer_thपढ़ो_create(पूर्णांक cpu, व्योम *arg)
अणु
	काष्ठा task_काष्ठा *task;

	task = kthपढ़ो_create_on_node(bL_चयनer_thपढ़ो, arg,
				      cpu_to_node(cpu), "kswitcher_%d", cpu);
	अगर (!IS_ERR(task)) अणु
		kthपढ़ो_bind(task, cpu);
		wake_up_process(task);
	पूर्ण अन्यथा
		pr_err("%s failed for CPU %d\n", __func__, cpu);
	वापस task;
पूर्ण

/*
 * bL_चयन_request_cb - Switch to a specअगरic cluster क्रम the given CPU,
 *      with completion notअगरication via a callback
 *
 * @cpu: the CPU to चयन
 * @new_cluster_id: the ID of the cluster to चयन to.
 * @completer: चयन completion callback.  अगर non-शून्य,
 *	@completer(@completer_cookie) will be called on completion of
 *	the चयन, in non-atomic context.
 * @completer_cookie: opaque context argument क्रम @completer.
 *
 * This function causes a cluster चयन on the given CPU by waking up
 * the appropriate चयनer thपढ़ो.  This function may or may not वापस
 * beक्रमe the चयन has occurred.
 *
 * If a @completer callback function is supplied, it will be called when
 * the चयन is complete.  This can be used to determine asynchronously
 * when the चयन is complete, regardless of when bL_चयन_request()
 * वापसs.  When @completer is supplied, no new चयन request is permitted
 * क्रम the affected CPU until after the चयन is complete, and @completer
 * has वापसed.
 */
पूर्णांक bL_चयन_request_cb(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक new_cluster_id,
			 bL_चयन_completion_handler completer,
			 व्योम *completer_cookie)
अणु
	काष्ठा bL_thपढ़ो *t;

	अगर (cpu >= ARRAY_SIZE(bL_thपढ़ोs)) अणु
		pr_err("%s: cpu %d out of bounds\n", __func__, cpu);
		वापस -EINVAL;
	पूर्ण

	t = &bL_thपढ़ोs[cpu];

	अगर (IS_ERR(t->task))
		वापस PTR_ERR(t->task);
	अगर (!t->task)
		वापस -ESRCH;

	spin_lock(&t->lock);
	अगर (t->completer) अणु
		spin_unlock(&t->lock);
		वापस -EBUSY;
	पूर्ण
	t->completer = completer;
	t->completer_cookie = completer_cookie;
	t->wanted_cluster = new_cluster_id;
	spin_unlock(&t->lock);
	wake_up(&t->wq);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bL_चयन_request_cb);

/*
 * Activation and configuration code.
 */

अटल DEFINE_MUTEX(bL_चयनer_activation_lock);
अटल BLOCKING_NOTIFIER_HEAD(bL_activation_notअगरier);
अटल अचिन्हित पूर्णांक bL_चयनer_active;
अटल अचिन्हित पूर्णांक bL_चयनer_cpu_original_cluster[NR_CPUS];
अटल cpumask_t bL_चयनer_हटाओd_logical_cpus;

पूर्णांक bL_चयनer_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&bL_activation_notअगरier, nb);
पूर्ण
EXPORT_SYMBOL_GPL(bL_चयनer_रेजिस्टर_notअगरier);

पूर्णांक bL_चयनer_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_unरेजिस्टर(&bL_activation_notअगरier, nb);
पूर्ण
EXPORT_SYMBOL_GPL(bL_चयनer_unरेजिस्टर_notअगरier);

अटल पूर्णांक bL_activation_notअगरy(अचिन्हित दीर्घ val)
अणु
	पूर्णांक ret;

	ret = blocking_notअगरier_call_chain(&bL_activation_notअगरier, val, शून्य);
	अगर (ret & NOTIFY_STOP_MASK)
		pr_err("%s: notifier chain failed with status 0x%x\n",
			__func__, ret);
	वापस notअगरier_to_त्रुटि_सं(ret);
पूर्ण

अटल व्योम bL_चयनer_restore_cpus(व्योम)
अणु
	पूर्णांक i;

	क्रम_each_cpu(i, &bL_चयनer_हटाओd_logical_cpus) अणु
		काष्ठा device *cpu_dev = get_cpu_device(i);
		पूर्णांक ret = device_online(cpu_dev);
		अगर (ret)
			dev_err(cpu_dev, "switcher: unable to restore CPU\n");
	पूर्ण
पूर्ण

अटल पूर्णांक bL_चयनer_halve_cpus(व्योम)
अणु
	पूर्णांक i, j, cluster_0, gic_id, ret;
	अचिन्हित पूर्णांक cpu, cluster, mask;
	cpumask_t available_cpus;

	/* First pass to validate what we have */
	mask = 0;
	क्रम_each_online_cpu(i) अणु
		cpu = MPIDR_AFFINITY_LEVEL(cpu_logical_map(i), 0);
		cluster = MPIDR_AFFINITY_LEVEL(cpu_logical_map(i), 1);
		अगर (cluster >= 2) अणु
			pr_err("%s: only dual cluster systems are supported\n", __func__);
			वापस -EINVAL;
		पूर्ण
		अगर (WARN_ON(cpu >= MAX_CPUS_PER_CLUSTER))
			वापस -EINVAL;
		mask |= (1 << cluster);
	पूर्ण
	अगर (mask != 3) अणु
		pr_err("%s: no CPU pairing possible\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Now let's करो the pairing.  We match each CPU with another CPU
	 * from a dअगरferent cluster.  To get a unअगरorm scheduling behavior
	 * without fiddling with CPU topology and compute capacity data,
	 * we'll use logical CPUs initially beदीर्घing to the same cluster.
	 */
	स_रखो(bL_चयनer_cpu_pairing, -1, माप(bL_चयनer_cpu_pairing));
	cpumask_copy(&available_cpus, cpu_online_mask);
	cluster_0 = -1;
	क्रम_each_cpu(i, &available_cpus) अणु
		पूर्णांक match = -1;
		cluster = MPIDR_AFFINITY_LEVEL(cpu_logical_map(i), 1);
		अगर (cluster_0 == -1)
			cluster_0 = cluster;
		अगर (cluster != cluster_0)
			जारी;
		cpumask_clear_cpu(i, &available_cpus);
		क्रम_each_cpu(j, &available_cpus) अणु
			cluster = MPIDR_AFFINITY_LEVEL(cpu_logical_map(j), 1);
			/*
			 * Let's remember the last match to create "odd"
			 * pairings on purpose in order क्रम other code not
			 * to assume any relation between physical and
			 * logical CPU numbers.
			 */
			अगर (cluster != cluster_0)
				match = j;
		पूर्ण
		अगर (match != -1) अणु
			bL_चयनer_cpu_pairing[i] = match;
			cpumask_clear_cpu(match, &available_cpus);
			pr_info("CPU%d paired with CPU%d\n", i, match);
		पूर्ण
	पूर्ण

	/*
	 * Now we disable the unwanted CPUs i.e. everything that has no
	 * pairing inक्रमmation (that includes the pairing counterparts).
	 */
	cpumask_clear(&bL_चयनer_हटाओd_logical_cpus);
	क्रम_each_online_cpu(i) अणु
		cpu = MPIDR_AFFINITY_LEVEL(cpu_logical_map(i), 0);
		cluster = MPIDR_AFFINITY_LEVEL(cpu_logical_map(i), 1);

		/* Let's take note of the GIC ID क्रम this CPU */
		gic_id = gic_get_cpu_id(i);
		अगर (gic_id < 0) अणु
			pr_err("%s: bad GIC ID for CPU %d\n", __func__, i);
			bL_चयनer_restore_cpus();
			वापस -EINVAL;
		पूर्ण
		bL_gic_id[cpu][cluster] = gic_id;
		pr_info("GIC ID for CPU %u cluster %u is %u\n",
			cpu, cluster, gic_id);

		अगर (bL_चयनer_cpu_pairing[i] != -1) अणु
			bL_चयनer_cpu_original_cluster[i] = cluster;
			जारी;
		पूर्ण

		ret = device_offline(get_cpu_device(i));
		अगर (ret) अणु
			bL_चयनer_restore_cpus();
			वापस ret;
		पूर्ण
		cpumask_set_cpu(i, &bL_चयनer_हटाओd_logical_cpus);
	पूर्ण

	वापस 0;
पूर्ण

/* Determine the logical CPU a given physical CPU is grouped on. */
पूर्णांक bL_चयनer_get_logical_index(u32 mpidr)
अणु
	पूर्णांक cpu;

	अगर (!bL_चयनer_active)
		वापस -EUNATCH;

	mpidr &= MPIDR_HWID_BITMASK;
	क्रम_each_online_cpu(cpu) अणु
		पूर्णांक pairing = bL_चयनer_cpu_pairing[cpu];
		अगर (pairing == -1)
			जारी;
		अगर ((mpidr == cpu_logical_map(cpu)) ||
		    (mpidr == cpu_logical_map(pairing)))
			वापस cpu;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल व्योम bL_चयनer_trace_trigger_cpu(व्योम *__always_unused info)
अणु
	trace_cpu_migrate_current(kसमय_get_real_ns(), पढ़ो_mpidr());
पूर्ण

पूर्णांक bL_चयनer_trace_trigger(व्योम)
अणु
	preempt_disable();

	bL_चयनer_trace_trigger_cpu(शून्य);
	smp_call_function(bL_चयनer_trace_trigger_cpu, शून्य, true);

	preempt_enable();

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bL_चयनer_trace_trigger);

अटल पूर्णांक bL_चयनer_enable(व्योम)
अणु
	पूर्णांक cpu, ret;

	mutex_lock(&bL_चयनer_activation_lock);
	lock_device_hotplug();
	अगर (bL_चयनer_active) अणु
		unlock_device_hotplug();
		mutex_unlock(&bL_चयनer_activation_lock);
		वापस 0;
	पूर्ण

	pr_info("big.LITTLE switcher initializing\n");

	ret = bL_activation_notअगरy(BL_NOTIFY_PRE_ENABLE);
	अगर (ret)
		जाओ error;

	ret = bL_चयनer_halve_cpus();
	अगर (ret)
		जाओ error;

	bL_चयनer_trace_trigger();

	क्रम_each_online_cpu(cpu) अणु
		काष्ठा bL_thपढ़ो *t = &bL_thपढ़ोs[cpu];
		spin_lock_init(&t->lock);
		init_रुकोqueue_head(&t->wq);
		init_completion(&t->started);
		t->wanted_cluster = -1;
		t->task = bL_चयनer_thपढ़ो_create(cpu, t);
	पूर्ण

	bL_चयनer_active = 1;
	bL_activation_notअगरy(BL_NOTIFY_POST_ENABLE);
	pr_info("big.LITTLE switcher initialized\n");
	जाओ out;

error:
	pr_warn("big.LITTLE switcher initialization failed\n");
	bL_activation_notअगरy(BL_NOTIFY_POST_DISABLE);

out:
	unlock_device_hotplug();
	mutex_unlock(&bL_चयनer_activation_lock);
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_SYSFS

अटल व्योम bL_चयनer_disable(व्योम)
अणु
	अचिन्हित पूर्णांक cpu, cluster;
	काष्ठा bL_thपढ़ो *t;
	काष्ठा task_काष्ठा *task;

	mutex_lock(&bL_चयनer_activation_lock);
	lock_device_hotplug();

	अगर (!bL_चयनer_active)
		जाओ out;

	अगर (bL_activation_notअगरy(BL_NOTIFY_PRE_DISABLE) != 0) अणु
		bL_activation_notअगरy(BL_NOTIFY_POST_ENABLE);
		जाओ out;
	पूर्ण

	bL_चयनer_active = 0;

	/*
	 * To deactivate the चयनer, we must shut करोwn the चयनer
	 * thपढ़ोs to prevent any other requests from being accepted.
	 * Then, अगर the final cluster क्रम given logical CPU is not the
	 * same as the original one, we'll recreate a चयनer thपढ़ो
	 * just क्रम the purpose of चयनing the CPU back without any
	 * possibility क्रम पूर्णांकerference from बाह्यal requests.
	 */
	क्रम_each_online_cpu(cpu) अणु
		t = &bL_thपढ़ोs[cpu];
		task = t->task;
		t->task = शून्य;
		अगर (!task || IS_ERR(task))
			जारी;
		kthपढ़ो_stop(task);
		/* no more चयन may happen on this CPU at this poपूर्णांक */
		cluster = MPIDR_AFFINITY_LEVEL(cpu_logical_map(cpu), 1);
		अगर (cluster == bL_चयनer_cpu_original_cluster[cpu])
			जारी;
		init_completion(&t->started);
		t->wanted_cluster = bL_चयनer_cpu_original_cluster[cpu];
		task = bL_चयनer_thपढ़ो_create(cpu, t);
		अगर (!IS_ERR(task)) अणु
			रुको_क्रम_completion(&t->started);
			kthपढ़ो_stop(task);
			cluster = MPIDR_AFFINITY_LEVEL(cpu_logical_map(cpu), 1);
			अगर (cluster == bL_चयनer_cpu_original_cluster[cpu])
				जारी;
		पूर्ण
		/* If execution माला_लो here, we're in trouble. */
		pr_crit("%s: unable to restore original cluster for CPU %d\n",
			__func__, cpu);
		pr_crit("%s: CPU %d can't be restored\n",
			__func__, bL_चयनer_cpu_pairing[cpu]);
		cpumask_clear_cpu(bL_चयनer_cpu_pairing[cpu],
				  &bL_चयनer_हटाओd_logical_cpus);
	पूर्ण

	bL_चयनer_restore_cpus();
	bL_चयनer_trace_trigger();

	bL_activation_notअगरy(BL_NOTIFY_POST_DISABLE);

out:
	unlock_device_hotplug();
	mutex_unlock(&bL_चयनer_activation_lock);
पूर्ण

अटल sमाप_प्रकार bL_चयनer_active_show(काष्ठा kobject *kobj,
		काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%u\n", bL_चयनer_active);
पूर्ण

अटल sमाप_प्रकार bL_चयनer_active_store(काष्ठा kobject *kobj,
		काष्ठा kobj_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret;

	चयन (buf[0]) अणु
	हाल '0':
		bL_चयनer_disable();
		ret = 0;
		अवरोध;
	हाल '1':
		ret = bL_चयनer_enable();
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस (ret >= 0) ? count : ret;
पूर्ण

अटल sमाप_प्रकार bL_चयनer_trace_trigger_store(काष्ठा kobject *kobj,
		काष्ठा kobj_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ret = bL_चयनer_trace_trigger();

	वापस ret ? ret : count;
पूर्ण

अटल काष्ठा kobj_attribute bL_चयनer_active_attr =
	__ATTR(active, 0644, bL_चयनer_active_show, bL_चयनer_active_store);

अटल काष्ठा kobj_attribute bL_चयनer_trace_trigger_attr =
	__ATTR(trace_trigger, 0200, शून्य, bL_चयनer_trace_trigger_store);

अटल काष्ठा attribute *bL_चयनer_attrs[] = अणु
	&bL_चयनer_active_attr.attr,
	&bL_चयनer_trace_trigger_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group bL_चयनer_attr_group = अणु
	.attrs = bL_चयनer_attrs,
पूर्ण;

अटल काष्ठा kobject *bL_चयनer_kobj;

अटल पूर्णांक __init bL_चयनer_sysfs_init(व्योम)
अणु
	पूर्णांक ret;

	bL_चयनer_kobj = kobject_create_and_add("bL_switcher", kernel_kobj);
	अगर (!bL_चयनer_kobj)
		वापस -ENOMEM;
	ret = sysfs_create_group(bL_चयनer_kobj, &bL_चयनer_attr_group);
	अगर (ret)
		kobject_put(bL_चयनer_kobj);
	वापस ret;
पूर्ण

#पूर्ण_अगर  /* CONFIG_SYSFS */

bool bL_चयनer_get_enabled(व्योम)
अणु
	mutex_lock(&bL_चयनer_activation_lock);

	वापस bL_चयनer_active;
पूर्ण
EXPORT_SYMBOL_GPL(bL_चयनer_get_enabled);

व्योम bL_चयनer_put_enabled(व्योम)
अणु
	mutex_unlock(&bL_चयनer_activation_lock);
पूर्ण
EXPORT_SYMBOL_GPL(bL_चयनer_put_enabled);

/*
 * Veto any CPU hotplug operation on those CPUs we've हटाओd
 * जबतक the चयनer is active.
 * We're just not पढ़ोy to deal with that given the trickery involved.
 */
अटल पूर्णांक bL_चयनer_cpu_pre(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक pairing;

	अगर (!bL_चयनer_active)
		वापस 0;

	pairing = bL_चयनer_cpu_pairing[cpu];

	अगर (pairing == -1)
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल bool no_bL_चयनer;
core_param(no_bL_चयनer, no_bL_चयनer, bool, 0644);

अटल पूर्णांक __init bL_चयनer_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!mcpm_is_available())
		वापस -ENODEV;

	cpuhp_setup_state_nocalls(CPUHP_ARM_BL_PREPARE, "arm/bl:prepare",
				  bL_चयनer_cpu_pre, शून्य);
	ret = cpuhp_setup_state_nocalls(CPUHP_AP_ONLINE_DYN, "arm/bl:predown",
					शून्य, bL_चयनer_cpu_pre);
	अगर (ret < 0) अणु
		cpuhp_हटाओ_state_nocalls(CPUHP_ARM_BL_PREPARE);
		pr_err("bL_switcher: Failed to allocate a hotplug state\n");
		वापस ret;
	पूर्ण
	अगर (!no_bL_चयनer) अणु
		ret = bL_चयनer_enable();
		अगर (ret)
			वापस ret;
	पूर्ण

#अगर_घोषित CONFIG_SYSFS
	ret = bL_चयनer_sysfs_init();
	अगर (ret)
		pr_err("%s: unable to create sysfs entry\n", __func__);
#पूर्ण_अगर

	वापस 0;
पूर्ण

late_initcall(bL_चयनer_init);
