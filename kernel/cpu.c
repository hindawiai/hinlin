<शैली गुरु>
/* CPU control.
 * (C) 2001, 2002, 2003, 2004 Rusty Russell
 *
 * This code is licenced under the GPL.
 */
#समावेश <linux/sched/mm.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/smp.h>
#समावेश <linux/init.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/hotplug.h>
#समावेश <linux/sched/isolation.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/smt.h>
#समावेश <linux/unistd.h>
#समावेश <linux/cpu.h>
#समावेश <linux/oom.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/export.h>
#समावेश <linux/bug.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/mutex.h>
#समावेश <linux/gfp.h>
#समावेश <linux/suspend.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/tick.h>
#समावेश <linux/irq.h>
#समावेश <linux/nmi.h>
#समावेश <linux/smpboot.h>
#समावेश <linux/relay.h>
#समावेश <linux/slab.h>
#समावेश <linux/percpu-rwsem.h>

#समावेश <trace/events/घातer.h>
#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/cpuhp.h>

#समावेश "smpboot.h"

/**
 * cpuhp_cpu_state - Per cpu hotplug state storage
 * @state:	The current cpu state
 * @target:	The target state
 * @thपढ़ो:	Poपूर्णांकer to the hotplug thपढ़ो
 * @should_run:	Thपढ़ो should execute
 * @rollback:	Perक्रमm a rollback
 * @single:	Single callback invocation
 * @bringup:	Single callback bringup or tearकरोwn selector
 * @cb_state:	The state क्रम a single callback (install/uninstall)
 * @result:	Result of the operation
 * @करोne_up:	Signal completion to the issuer of the task क्रम cpu-up
 * @करोne_करोwn:	Signal completion to the issuer of the task क्रम cpu-करोwn
 */
काष्ठा cpuhp_cpu_state अणु
	क्रमागत cpuhp_state	state;
	क्रमागत cpuhp_state	target;
	क्रमागत cpuhp_state	fail;
#अगर_घोषित CONFIG_SMP
	काष्ठा task_काष्ठा	*thपढ़ो;
	bool			should_run;
	bool			rollback;
	bool			single;
	bool			bringup;
	पूर्णांक			cpu;
	काष्ठा hlist_node	*node;
	काष्ठा hlist_node	*last;
	क्रमागत cpuhp_state	cb_state;
	पूर्णांक			result;
	काष्ठा completion	करोne_up;
	काष्ठा completion	करोne_करोwn;
#पूर्ण_अगर
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा cpuhp_cpu_state, cpuhp_state) = अणु
	.fail = CPUHP_INVALID,
पूर्ण;

#अगर_घोषित CONFIG_SMP
cpumask_t cpus_booted_once_mask;
#पूर्ण_अगर

#अगर defined(CONFIG_LOCKDEP) && defined(CONFIG_SMP)
अटल काष्ठा lockdep_map cpuhp_state_up_map =
	STATIC_LOCKDEP_MAP_INIT("cpuhp_state-up", &cpuhp_state_up_map);
अटल काष्ठा lockdep_map cpuhp_state_करोwn_map =
	STATIC_LOCKDEP_MAP_INIT("cpuhp_state-down", &cpuhp_state_करोwn_map);


अटल अंतरभूत व्योम cpuhp_lock_acquire(bool bringup)
अणु
	lock_map_acquire(bringup ? &cpuhp_state_up_map : &cpuhp_state_करोwn_map);
पूर्ण

अटल अंतरभूत व्योम cpuhp_lock_release(bool bringup)
अणु
	lock_map_release(bringup ? &cpuhp_state_up_map : &cpuhp_state_करोwn_map);
पूर्ण
#अन्यथा

अटल अंतरभूत व्योम cpuhp_lock_acquire(bool bringup) अणु पूर्ण
अटल अंतरभूत व्योम cpuhp_lock_release(bool bringup) अणु पूर्ण

#पूर्ण_अगर

/**
 * cpuhp_step - Hotplug state machine step
 * @name:	Name of the step
 * @startup:	Startup function of the step
 * @tearकरोwn:	Tearकरोwn function of the step
 * @cant_stop:	Bringup/tearकरोwn can't be stopped at this step
 */
काष्ठा cpuhp_step अणु
	स्थिर अक्षर		*name;
	जोड़ अणु
		पूर्णांक		(*single)(अचिन्हित पूर्णांक cpu);
		पूर्णांक		(*multi)(अचिन्हित पूर्णांक cpu,
					 काष्ठा hlist_node *node);
	पूर्ण startup;
	जोड़ अणु
		पूर्णांक		(*single)(अचिन्हित पूर्णांक cpu);
		पूर्णांक		(*multi)(अचिन्हित पूर्णांक cpu,
					 काष्ठा hlist_node *node);
	पूर्ण tearकरोwn;
	काष्ठा hlist_head	list;
	bool			cant_stop;
	bool			multi_instance;
पूर्ण;

अटल DEFINE_MUTEX(cpuhp_state_mutex);
अटल काष्ठा cpuhp_step cpuhp_hp_states[];

अटल काष्ठा cpuhp_step *cpuhp_get_step(क्रमागत cpuhp_state state)
अणु
	वापस cpuhp_hp_states + state;
पूर्ण

अटल bool cpuhp_step_empty(bool bringup, काष्ठा cpuhp_step *step)
अणु
	वापस bringup ? !step->startup.single : !step->tearकरोwn.single;
पूर्ण

/**
 * cpuhp_invoke_callback _ Invoke the callbacks क्रम a given state
 * @cpu:	The cpu क्रम which the callback should be invoked
 * @state:	The state to करो callbacks क्रम
 * @bringup:	True अगर the bringup callback should be invoked
 * @node:	For multi-instance, करो a single entry callback क्रम install/हटाओ
 * @lastp:	For multi-instance rollback, remember how far we got
 *
 * Called from cpu hotplug and from the state रेजिस्टर machinery.
 */
अटल पूर्णांक cpuhp_invoke_callback(अचिन्हित पूर्णांक cpu, क्रमागत cpuhp_state state,
				 bool bringup, काष्ठा hlist_node *node,
				 काष्ठा hlist_node **lastp)
अणु
	काष्ठा cpuhp_cpu_state *st = per_cpu_ptr(&cpuhp_state, cpu);
	काष्ठा cpuhp_step *step = cpuhp_get_step(state);
	पूर्णांक (*cbm)(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node);
	पूर्णांक (*cb)(अचिन्हित पूर्णांक cpu);
	पूर्णांक ret, cnt;

	अगर (st->fail == state) अणु
		st->fail = CPUHP_INVALID;
		वापस -EAGAIN;
	पूर्ण

	अगर (cpuhp_step_empty(bringup, step)) अणु
		WARN_ON_ONCE(1);
		वापस 0;
	पूर्ण

	अगर (!step->multi_instance) अणु
		WARN_ON_ONCE(lastp && *lastp);
		cb = bringup ? step->startup.single : step->tearकरोwn.single;

		trace_cpuhp_enter(cpu, st->target, state, cb);
		ret = cb(cpu);
		trace_cpuhp_निकास(cpu, st->state, state, ret);
		वापस ret;
	पूर्ण
	cbm = bringup ? step->startup.multi : step->tearकरोwn.multi;

	/* Single invocation क्रम instance add/हटाओ */
	अगर (node) अणु
		WARN_ON_ONCE(lastp && *lastp);
		trace_cpuhp_multi_enter(cpu, st->target, state, cbm, node);
		ret = cbm(cpu, node);
		trace_cpuhp_निकास(cpu, st->state, state, ret);
		वापस ret;
	पूर्ण

	/* State transition. Invoke on all instances */
	cnt = 0;
	hlist_क्रम_each(node, &step->list) अणु
		अगर (lastp && node == *lastp)
			अवरोध;

		trace_cpuhp_multi_enter(cpu, st->target, state, cbm, node);
		ret = cbm(cpu, node);
		trace_cpuhp_निकास(cpu, st->state, state, ret);
		अगर (ret) अणु
			अगर (!lastp)
				जाओ err;

			*lastp = node;
			वापस ret;
		पूर्ण
		cnt++;
	पूर्ण
	अगर (lastp)
		*lastp = शून्य;
	वापस 0;
err:
	/* Rollback the instances अगर one failed */
	cbm = !bringup ? step->startup.multi : step->tearकरोwn.multi;
	अगर (!cbm)
		वापस ret;

	hlist_क्रम_each(node, &step->list) अणु
		अगर (!cnt--)
			अवरोध;

		trace_cpuhp_multi_enter(cpu, st->target, state, cbm, node);
		ret = cbm(cpu, node);
		trace_cpuhp_निकास(cpu, st->state, state, ret);
		/*
		 * Rollback must not fail,
		 */
		WARN_ON_ONCE(ret);
	पूर्ण
	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल bool cpuhp_is_ap_state(क्रमागत cpuhp_state state)
अणु
	/*
	 * The extra check क्रम CPUHP_TEARDOWN_CPU is only क्रम करोcumentation
	 * purposes as that state is handled explicitly in cpu_करोwn.
	 */
	वापस state > CPUHP_BRINGUP_CPU && state != CPUHP_TEARDOWN_CPU;
पूर्ण

अटल अंतरभूत व्योम रुको_क्रम_ap_thपढ़ो(काष्ठा cpuhp_cpu_state *st, bool bringup)
अणु
	काष्ठा completion *करोne = bringup ? &st->करोne_up : &st->करोne_करोwn;
	रुको_क्रम_completion(करोne);
पूर्ण

अटल अंतरभूत व्योम complete_ap_thपढ़ो(काष्ठा cpuhp_cpu_state *st, bool bringup)
अणु
	काष्ठा completion *करोne = bringup ? &st->करोne_up : &st->करोne_करोwn;
	complete(करोne);
पूर्ण

/*
 * The क्रमmer STARTING/DYING states, ran with IRQs disabled and must not fail.
 */
अटल bool cpuhp_is_atomic_state(क्रमागत cpuhp_state state)
अणु
	वापस CPUHP_AP_IDLE_DEAD <= state && state < CPUHP_AP_ONLINE;
पूर्ण

/* Serializes the updates to cpu_online_mask, cpu_present_mask */
अटल DEFINE_MUTEX(cpu_add_हटाओ_lock);
bool cpuhp_tasks_frozen;
EXPORT_SYMBOL_GPL(cpuhp_tasks_frozen);

/*
 * The following two APIs (cpu_maps_update_begin/करोne) must be used when
 * attempting to serialize the updates to cpu_online_mask & cpu_present_mask.
 */
व्योम cpu_maps_update_begin(व्योम)
अणु
	mutex_lock(&cpu_add_हटाओ_lock);
पूर्ण

व्योम cpu_maps_update_करोne(व्योम)
अणु
	mutex_unlock(&cpu_add_हटाओ_lock);
पूर्ण

/*
 * If set, cpu_up and cpu_करोwn will वापस -EBUSY and करो nothing.
 * Should always be manipulated under cpu_add_हटाओ_lock
 */
अटल पूर्णांक cpu_hotplug_disabled;

#अगर_घोषित CONFIG_HOTPLUG_CPU

DEFINE_STATIC_PERCPU_RWSEM(cpu_hotplug_lock);

व्योम cpus_पढ़ो_lock(व्योम)
अणु
	percpu_करोwn_पढ़ो(&cpu_hotplug_lock);
पूर्ण
EXPORT_SYMBOL_GPL(cpus_पढ़ो_lock);

पूर्णांक cpus_पढ़ो_trylock(व्योम)
अणु
	वापस percpu_करोwn_पढ़ो_trylock(&cpu_hotplug_lock);
पूर्ण
EXPORT_SYMBOL_GPL(cpus_पढ़ो_trylock);

व्योम cpus_पढ़ो_unlock(व्योम)
अणु
	percpu_up_पढ़ो(&cpu_hotplug_lock);
पूर्ण
EXPORT_SYMBOL_GPL(cpus_पढ़ो_unlock);

व्योम cpus_ग_लिखो_lock(व्योम)
अणु
	percpu_करोwn_ग_लिखो(&cpu_hotplug_lock);
पूर्ण

व्योम cpus_ग_लिखो_unlock(व्योम)
अणु
	percpu_up_ग_लिखो(&cpu_hotplug_lock);
पूर्ण

व्योम lockdep_निश्चित_cpus_held(व्योम)
अणु
	/*
	 * We can't have hotplug operations beक्रमe userspace starts running,
	 * and some init codepaths will knowingly not take the hotplug lock.
	 * This is all valid, so mute lockdep until it makes sense to report
	 * unheld locks.
	 */
	अगर (प्रणाली_state < SYSTEM_RUNNING)
		वापस;

	percpu_rwsem_निश्चित_held(&cpu_hotplug_lock);
पूर्ण

#अगर_घोषित CONFIG_LOCKDEP
पूर्णांक lockdep_is_cpus_held(व्योम)
अणु
	वापस percpu_rwsem_is_held(&cpu_hotplug_lock);
पूर्ण
#पूर्ण_अगर

अटल व्योम lockdep_acquire_cpus_lock(व्योम)
अणु
	rwsem_acquire(&cpu_hotplug_lock.dep_map, 0, 0, _THIS_IP_);
पूर्ण

अटल व्योम lockdep_release_cpus_lock(व्योम)
अणु
	rwsem_release(&cpu_hotplug_lock.dep_map, _THIS_IP_);
पूर्ण

/*
 * Wait क्रम currently running CPU hotplug operations to complete (अगर any) and
 * disable future CPU hotplug (from sysfs). The 'cpu_add_remove_lock' protects
 * the 'cpu_hotplug_disabled' flag. The same lock is also acquired by the
 * hotplug path beक्रमe perक्रमming hotplug operations. So acquiring that lock
 * guarantees mutual exclusion from any currently running hotplug operations.
 */
व्योम cpu_hotplug_disable(व्योम)
अणु
	cpu_maps_update_begin();
	cpu_hotplug_disabled++;
	cpu_maps_update_करोne();
पूर्ण
EXPORT_SYMBOL_GPL(cpu_hotplug_disable);

अटल व्योम __cpu_hotplug_enable(व्योम)
अणु
	अगर (WARN_ONCE(!cpu_hotplug_disabled, "Unbalanced cpu hotplug enable\n"))
		वापस;
	cpu_hotplug_disabled--;
पूर्ण

व्योम cpu_hotplug_enable(व्योम)
अणु
	cpu_maps_update_begin();
	__cpu_hotplug_enable();
	cpu_maps_update_करोne();
पूर्ण
EXPORT_SYMBOL_GPL(cpu_hotplug_enable);

#अन्यथा

अटल व्योम lockdep_acquire_cpus_lock(व्योम)
अणु
पूर्ण

अटल व्योम lockdep_release_cpus_lock(व्योम)
अणु
पूर्ण

#पूर्ण_अगर	/* CONFIG_HOTPLUG_CPU */

/*
 * Architectures that need SMT-specअगरic errata handling during SMT hotplug
 * should override this.
 */
व्योम __weak arch_smt_update(व्योम) अणु पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_SMT
क्रमागत cpuhp_smt_control cpu_smt_control __पढ़ो_mostly = CPU_SMT_ENABLED;

व्योम __init cpu_smt_disable(bool क्रमce)
अणु
	अगर (!cpu_smt_possible())
		वापस;

	अगर (क्रमce) अणु
		pr_info("SMT: Force disabled\n");
		cpu_smt_control = CPU_SMT_FORCE_DISABLED;
	पूर्ण अन्यथा अणु
		pr_info("SMT: disabled\n");
		cpu_smt_control = CPU_SMT_DISABLED;
	पूर्ण
पूर्ण

/*
 * The decision whether SMT is supported can only be करोne after the full
 * CPU identअगरication. Called from architecture code.
 */
व्योम __init cpu_smt_check_topology(व्योम)
अणु
	अगर (!topology_smt_supported())
		cpu_smt_control = CPU_SMT_NOT_SUPPORTED;
पूर्ण

अटल पूर्णांक __init smt_cmdline_disable(अक्षर *str)
अणु
	cpu_smt_disable(str && !म_भेद(str, "force"));
	वापस 0;
पूर्ण
early_param("nosmt", smt_cmdline_disable);

अटल अंतरभूत bool cpu_smt_allowed(अचिन्हित पूर्णांक cpu)
अणु
	अगर (cpu_smt_control == CPU_SMT_ENABLED)
		वापस true;

	अगर (topology_is_primary_thपढ़ो(cpu))
		वापस true;

	/*
	 * On x86 it's required to boot all logical CPUs at least once so
	 * that the init code can get a chance to set CR4.MCE on each
	 * CPU. Otherwise, a broadcasted MCE observing CR4.MCE=0b on any
	 * core will shutकरोwn the machine.
	 */
	वापस !cpumask_test_cpu(cpu, &cpus_booted_once_mask);
पूर्ण

/* Returns true अगर SMT is not supported of क्रमcefully (irreversibly) disabled */
bool cpu_smt_possible(व्योम)
अणु
	वापस cpu_smt_control != CPU_SMT_FORCE_DISABLED &&
		cpu_smt_control != CPU_SMT_NOT_SUPPORTED;
पूर्ण
EXPORT_SYMBOL_GPL(cpu_smt_possible);
#अन्यथा
अटल अंतरभूत bool cpu_smt_allowed(अचिन्हित पूर्णांक cpu) अणु वापस true; पूर्ण
#पूर्ण_अगर

अटल अंतरभूत क्रमागत cpuhp_state
cpuhp_set_state(काष्ठा cpuhp_cpu_state *st, क्रमागत cpuhp_state target)
अणु
	क्रमागत cpuhp_state prev_state = st->state;
	bool bringup = st->state < target;

	st->rollback = false;
	st->last = शून्य;

	st->target = target;
	st->single = false;
	st->bringup = bringup;
	अगर (cpu_dying(st->cpu) != !bringup)
		set_cpu_dying(st->cpu, !bringup);

	वापस prev_state;
पूर्ण

अटल अंतरभूत व्योम
cpuhp_reset_state(काष्ठा cpuhp_cpu_state *st, क्रमागत cpuhp_state prev_state)
अणु
	bool bringup = !st->bringup;

	st->target = prev_state;

	/*
	 * Alपढ़ोy rolling back. No need invert the bringup value or to change
	 * the current state.
	 */
	अगर (st->rollback)
		वापस;

	st->rollback = true;

	/*
	 * If we have st->last we need to unकरो partial multi_instance of this
	 * state first. Otherwise start unकरो at the previous state.
	 */
	अगर (!st->last) अणु
		अगर (st->bringup)
			st->state--;
		अन्यथा
			st->state++;
	पूर्ण

	st->bringup = bringup;
	अगर (cpu_dying(st->cpu) != !bringup)
		set_cpu_dying(st->cpu, !bringup);
पूर्ण

/* Regular hotplug invocation of the AP hotplug thपढ़ो */
अटल व्योम __cpuhp_kick_ap(काष्ठा cpuhp_cpu_state *st)
अणु
	अगर (!st->single && st->state == st->target)
		वापस;

	st->result = 0;
	/*
	 * Make sure the above stores are visible beक्रमe should_run becomes
	 * true. Paired with the mb() above in cpuhp_thपढ़ो_fun()
	 */
	smp_mb();
	st->should_run = true;
	wake_up_process(st->thपढ़ो);
	रुको_क्रम_ap_thपढ़ो(st, st->bringup);
पूर्ण

अटल पूर्णांक cpuhp_kick_ap(काष्ठा cpuhp_cpu_state *st, क्रमागत cpuhp_state target)
अणु
	क्रमागत cpuhp_state prev_state;
	पूर्णांक ret;

	prev_state = cpuhp_set_state(st, target);
	__cpuhp_kick_ap(st);
	अगर ((ret = st->result)) अणु
		cpuhp_reset_state(st, prev_state);
		__cpuhp_kick_ap(st);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bringup_रुको_क्रम_ap(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpuhp_cpu_state *st = per_cpu_ptr(&cpuhp_state, cpu);

	/* Wait क्रम the CPU to reach CPUHP_AP_ONLINE_IDLE */
	रुको_क्रम_ap_thपढ़ो(st, true);
	अगर (WARN_ON_ONCE((!cpu_online(cpu))))
		वापस -ECANCELED;

	/* Unpark the hotplug thपढ़ो of the target cpu */
	kthपढ़ो_unpark(st->thपढ़ो);

	/*
	 * SMT soft disabling on X86 requires to bring the CPU out of the
	 * BIOS 'wait for SIPI' state in order to set the CR4.MCE bit.  The
	 * CPU marked itself as booted_once in notअगरy_cpu_starting() so the
	 * cpu_smt_allowed() check will now वापस false अगर this is not the
	 * primary sibling.
	 */
	अगर (!cpu_smt_allowed(cpu))
		वापस -ECANCELED;

	अगर (st->target <= CPUHP_AP_ONLINE_IDLE)
		वापस 0;

	वापस cpuhp_kick_ap(st, st->target);
पूर्ण

अटल पूर्णांक bringup_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा task_काष्ठा *idle = idle_thपढ़ो_get(cpu);
	पूर्णांक ret;

	/*
	 * Some architectures have to walk the irq descriptors to
	 * setup the vector space क्रम the cpu which comes online.
	 * Prevent irq alloc/मुक्त across the bringup.
	 */
	irq_lock_sparse();

	/* Arch-specअगरic enabling code. */
	ret = __cpu_up(cpu, idle);
	irq_unlock_sparse();
	अगर (ret)
		वापस ret;
	वापस bringup_रुको_क्रम_ap(cpu);
पूर्ण

अटल पूर्णांक finish_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा task_काष्ठा *idle = idle_thपढ़ो_get(cpu);
	काष्ठा mm_काष्ठा *mm = idle->active_mm;

	/*
	 * idle_task_निकास() will have चयनed to &init_mm, now
	 * clean up any reमुख्यing active_mm state.
	 */
	अगर (mm != &init_mm)
		idle->active_mm = &init_mm;
	mmdrop(mm);
	वापस 0;
पूर्ण

/*
 * Hotplug state machine related functions
 */

/*
 * Get the next state to run. Empty ones will be skipped. Returns true अगर a
 * state must be run.
 *
 * st->state will be modअगरied ahead of समय, to match state_to_run, as अगर it
 * has alपढ़ोy ran.
 */
अटल bool cpuhp_next_state(bool bringup,
			     क्रमागत cpuhp_state *state_to_run,
			     काष्ठा cpuhp_cpu_state *st,
			     क्रमागत cpuhp_state target)
अणु
	करो अणु
		अगर (bringup) अणु
			अगर (st->state >= target)
				वापस false;

			*state_to_run = ++st->state;
		पूर्ण अन्यथा अणु
			अगर (st->state <= target)
				वापस false;

			*state_to_run = st->state--;
		पूर्ण

		अगर (!cpuhp_step_empty(bringup, cpuhp_get_step(*state_to_run)))
			अवरोध;
	पूर्ण जबतक (true);

	वापस true;
पूर्ण

अटल पूर्णांक cpuhp_invoke_callback_range(bool bringup,
				       अचिन्हित पूर्णांक cpu,
				       काष्ठा cpuhp_cpu_state *st,
				       क्रमागत cpuhp_state target)
अणु
	क्रमागत cpuhp_state state;
	पूर्णांक err = 0;

	जबतक (cpuhp_next_state(bringup, &state, st, target)) अणु
		err = cpuhp_invoke_callback(cpu, state, bringup, शून्य, शून्य);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल अंतरभूत bool can_rollback_cpu(काष्ठा cpuhp_cpu_state *st)
अणु
	अगर (IS_ENABLED(CONFIG_HOTPLUG_CPU))
		वापस true;
	/*
	 * When CPU hotplug is disabled, then taking the CPU करोwn is not
	 * possible because takeकरोwn_cpu() and the architecture and
	 * subप्रणाली specअगरic mechanisms are not available. So the CPU
	 * which would be completely unplugged again needs to stay around
	 * in the current state.
	 */
	वापस st->state <= CPUHP_BRINGUP_CPU;
पूर्ण

अटल पूर्णांक cpuhp_up_callbacks(अचिन्हित पूर्णांक cpu, काष्ठा cpuhp_cpu_state *st,
			      क्रमागत cpuhp_state target)
अणु
	क्रमागत cpuhp_state prev_state = st->state;
	पूर्णांक ret = 0;

	ret = cpuhp_invoke_callback_range(true, cpu, st, target);
	अगर (ret) अणु
		cpuhp_reset_state(st, prev_state);
		अगर (can_rollback_cpu(st))
			WARN_ON(cpuhp_invoke_callback_range(false, cpu, st,
							    prev_state));
	पूर्ण
	वापस ret;
पूर्ण

/*
 * The cpu hotplug thपढ़ोs manage the bringup and tearकरोwn of the cpus
 */
अटल व्योम cpuhp_create(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpuhp_cpu_state *st = per_cpu_ptr(&cpuhp_state, cpu);

	init_completion(&st->करोne_up);
	init_completion(&st->करोne_करोwn);
	st->cpu = cpu;
पूर्ण

अटल पूर्णांक cpuhp_should_run(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpuhp_cpu_state *st = this_cpu_ptr(&cpuhp_state);

	वापस st->should_run;
पूर्ण

/*
 * Execute tearकरोwn/startup callbacks on the plugged cpu. Also used to invoke
 * callbacks when a state माला_लो [un]installed at runसमय.
 *
 * Each invocation of this function by the smpboot thपढ़ो करोes a single AP
 * state callback.
 *
 * It has 3 modes of operation:
 *  - single: runs st->cb_state
 *  - up:     runs ++st->state, जबतक st->state < st->target
 *  - करोwn:   runs st->state--, जबतक st->state > st->target
 *
 * When complete or on error, should_run is cleared and the completion is fired.
 */
अटल व्योम cpuhp_thपढ़ो_fun(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpuhp_cpu_state *st = this_cpu_ptr(&cpuhp_state);
	bool bringup = st->bringup;
	क्रमागत cpuhp_state state;

	अगर (WARN_ON_ONCE(!st->should_run))
		वापस;

	/*
	 * ACQUIRE क्रम the cpuhp_should_run() load of ->should_run. Ensures
	 * that अगर we see ->should_run we also see the rest of the state.
	 */
	smp_mb();

	/*
	 * The BP holds the hotplug lock, but we're now running on the AP,
	 * ensure that anybody निश्चितing the lock is held, will actually find
	 * it so.
	 */
	lockdep_acquire_cpus_lock();
	cpuhp_lock_acquire(bringup);

	अगर (st->single) अणु
		state = st->cb_state;
		st->should_run = false;
	पूर्ण अन्यथा अणु
		st->should_run = cpuhp_next_state(bringup, &state, st, st->target);
		अगर (!st->should_run)
			जाओ end;
	पूर्ण

	WARN_ON_ONCE(!cpuhp_is_ap_state(state));

	अगर (cpuhp_is_atomic_state(state)) अणु
		local_irq_disable();
		st->result = cpuhp_invoke_callback(cpu, state, bringup, st->node, &st->last);
		local_irq_enable();

		/*
		 * STARTING/DYING must not fail!
		 */
		WARN_ON_ONCE(st->result);
	पूर्ण अन्यथा अणु
		st->result = cpuhp_invoke_callback(cpu, state, bringup, st->node, &st->last);
	पूर्ण

	अगर (st->result) अणु
		/*
		 * If we fail on a rollback, we're up a creek without no
		 * paddle, no way क्रमward, no way back. We loose, thanks क्रम
		 * playing.
		 */
		WARN_ON_ONCE(st->rollback);
		st->should_run = false;
	पूर्ण

end:
	cpuhp_lock_release(bringup);
	lockdep_release_cpus_lock();

	अगर (!st->should_run)
		complete_ap_thपढ़ो(st, bringup);
पूर्ण

/* Invoke a single callback on a remote cpu */
अटल पूर्णांक
cpuhp_invoke_ap_callback(पूर्णांक cpu, क्रमागत cpuhp_state state, bool bringup,
			 काष्ठा hlist_node *node)
अणु
	काष्ठा cpuhp_cpu_state *st = per_cpu_ptr(&cpuhp_state, cpu);
	पूर्णांक ret;

	अगर (!cpu_online(cpu))
		वापस 0;

	cpuhp_lock_acquire(false);
	cpuhp_lock_release(false);

	cpuhp_lock_acquire(true);
	cpuhp_lock_release(true);

	/*
	 * If we are up and running, use the hotplug thपढ़ो. For early calls
	 * we invoke the thपढ़ो function directly.
	 */
	अगर (!st->thपढ़ो)
		वापस cpuhp_invoke_callback(cpu, state, bringup, node, शून्य);

	st->rollback = false;
	st->last = शून्य;

	st->node = node;
	st->bringup = bringup;
	st->cb_state = state;
	st->single = true;

	__cpuhp_kick_ap(st);

	/*
	 * If we failed and did a partial, करो a rollback.
	 */
	अगर ((ret = st->result) && st->last) अणु
		st->rollback = true;
		st->bringup = !bringup;

		__cpuhp_kick_ap(st);
	पूर्ण

	/*
	 * Clean up the leftovers so the next hotplug operation wont use stale
	 * data.
	 */
	st->node = st->last = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक cpuhp_kick_ap_work(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpuhp_cpu_state *st = per_cpu_ptr(&cpuhp_state, cpu);
	क्रमागत cpuhp_state prev_state = st->state;
	पूर्णांक ret;

	cpuhp_lock_acquire(false);
	cpuhp_lock_release(false);

	cpuhp_lock_acquire(true);
	cpuhp_lock_release(true);

	trace_cpuhp_enter(cpu, st->target, prev_state, cpuhp_kick_ap_work);
	ret = cpuhp_kick_ap(st, st->target);
	trace_cpuhp_निकास(cpu, st->state, prev_state, ret);

	वापस ret;
पूर्ण

अटल काष्ठा smp_hotplug_thपढ़ो cpuhp_thपढ़ोs = अणु
	.store			= &cpuhp_state.thपढ़ो,
	.create			= &cpuhp_create,
	.thपढ़ो_should_run	= cpuhp_should_run,
	.thपढ़ो_fn		= cpuhp_thपढ़ो_fun,
	.thपढ़ो_comm		= "cpuhp/%u",
	.selfparking		= true,
पूर्ण;

व्योम __init cpuhp_thपढ़ोs_init(व्योम)
अणु
	BUG_ON(smpboot_रेजिस्टर_percpu_thपढ़ो(&cpuhp_thपढ़ोs));
	kthपढ़ो_unpark(this_cpu_पढ़ो(cpuhp_state.thपढ़ो));
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU
#अगर_अघोषित arch_clear_mm_cpumask_cpu
#घोषणा arch_clear_mm_cpumask_cpu(cpu, mm) cpumask_clear_cpu(cpu, mm_cpumask(mm))
#पूर्ण_अगर

/**
 * clear_tasks_mm_cpumask - Safely clear tasks' mm_cpumask क्रम a CPU
 * @cpu: a CPU id
 *
 * This function walks all processes, finds a valid mm काष्ठा क्रम each one and
 * then clears a corresponding bit in mm's cpumask.  While this all sounds
 * trivial, there are various non-obvious corner हालs, which this function
 * tries to solve in a safe manner.
 *
 * Also note that the function uses a somewhat relaxed locking scheme, so it may
 * be called only क्रम an alपढ़ोy offlined CPU.
 */
व्योम clear_tasks_mm_cpumask(पूर्णांक cpu)
अणु
	काष्ठा task_काष्ठा *p;

	/*
	 * This function is called after the cpu is taken करोwn and marked
	 * offline, so its not like new tasks will ever get this cpu set in
	 * their mm mask. -- Peter Zijlstra
	 * Thus, we may use rcu_पढ़ो_lock() here, instead of grabbing
	 * full-fledged tasklist_lock.
	 */
	WARN_ON(cpu_online(cpu));
	rcu_पढ़ो_lock();
	क्रम_each_process(p) अणु
		काष्ठा task_काष्ठा *t;

		/*
		 * Main thपढ़ो might निकास, but other thपढ़ोs may still have
		 * a valid mm. Find one.
		 */
		t = find_lock_task_mm(p);
		अगर (!t)
			जारी;
		arch_clear_mm_cpumask_cpu(cpu, t->mm);
		task_unlock(t);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/* Take this CPU करोwn. */
अटल पूर्णांक take_cpu_करोwn(व्योम *_param)
अणु
	काष्ठा cpuhp_cpu_state *st = this_cpu_ptr(&cpuhp_state);
	क्रमागत cpuhp_state target = max((पूर्णांक)st->target, CPUHP_AP_OFFLINE);
	पूर्णांक err, cpu = smp_processor_id();
	पूर्णांक ret;

	/* Ensure this CPU करोesn't handle any more पूर्णांकerrupts. */
	err = __cpu_disable();
	अगर (err < 0)
		वापस err;

	/*
	 * Must be called from CPUHP_TEARDOWN_CPU, which means, as we are going
	 * करोwn, that the current state is CPUHP_TEARDOWN_CPU - 1.
	 */
	WARN_ON(st->state != (CPUHP_TEARDOWN_CPU - 1));

	/* Invoke the क्रमmer CPU_DYING callbacks */
	ret = cpuhp_invoke_callback_range(false, cpu, st, target);

	/*
	 * DYING must not fail!
	 */
	WARN_ON_ONCE(ret);

	/* Give up समयkeeping duties */
	tick_hanकरोver_करो_समयr();
	/* Remove CPU from समयr broadcasting */
	tick_offline_cpu(cpu);
	/* Park the stopper thपढ़ो */
	stop_machine_park(cpu);
	वापस 0;
पूर्ण

अटल पूर्णांक takeकरोwn_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpuhp_cpu_state *st = per_cpu_ptr(&cpuhp_state, cpu);
	पूर्णांक err;

	/* Park the smpboot thपढ़ोs */
	kthपढ़ो_park(per_cpu_ptr(&cpuhp_state, cpu)->thपढ़ो);

	/*
	 * Prevent irq alloc/मुक्त जबतक the dying cpu reorganizes the
	 * पूर्णांकerrupt affinities.
	 */
	irq_lock_sparse();

	/*
	 * So now all preempt/rcu users must observe !cpu_active().
	 */
	err = stop_machine_cpuslocked(take_cpu_करोwn, शून्य, cpumask_of(cpu));
	अगर (err) अणु
		/* CPU refused to die */
		irq_unlock_sparse();
		/* Unpark the hotplug thपढ़ो so we can rollback there */
		kthपढ़ो_unpark(per_cpu_ptr(&cpuhp_state, cpu)->thपढ़ो);
		वापस err;
	पूर्ण
	BUG_ON(cpu_online(cpu));

	/*
	 * The tearकरोwn callback क्रम CPUHP_AP_SCHED_STARTING will have हटाओd
	 * all runnable tasks from the CPU, there's only the idle task left now
	 * that the migration thपढ़ो is करोne करोing the stop_machine thing.
	 *
	 * Wait क्रम the stop thपढ़ो to go away.
	 */
	रुको_क्रम_ap_thपढ़ो(st, false);
	BUG_ON(st->state != CPUHP_AP_IDLE_DEAD);

	/* Interrupts are moved away from the dying cpu, reenable alloc/मुक्त */
	irq_unlock_sparse();

	hotplug_cpu__broadcast_tick_pull(cpu);
	/* This actually समाप्तs the CPU. */
	__cpu_die(cpu);

	tick_cleanup_dead_cpu(cpu);
	rcutree_migrate_callbacks(cpu);
	वापस 0;
पूर्ण

अटल व्योम cpuhp_complete_idle_dead(व्योम *arg)
अणु
	काष्ठा cpuhp_cpu_state *st = arg;

	complete_ap_thपढ़ो(st, false);
पूर्ण

व्योम cpuhp_report_idle_dead(व्योम)
अणु
	काष्ठा cpuhp_cpu_state *st = this_cpu_ptr(&cpuhp_state);

	BUG_ON(st->state != CPUHP_AP_OFFLINE);
	rcu_report_dead(smp_processor_id());
	st->state = CPUHP_AP_IDLE_DEAD;
	/*
	 * We cannot call complete after rcu_report_dead() so we delegate it
	 * to an online cpu.
	 */
	smp_call_function_single(cpumask_first(cpu_online_mask),
				 cpuhp_complete_idle_dead, st, 0);
पूर्ण

अटल पूर्णांक cpuhp_करोwn_callbacks(अचिन्हित पूर्णांक cpu, काष्ठा cpuhp_cpu_state *st,
				क्रमागत cpuhp_state target)
अणु
	क्रमागत cpuhp_state prev_state = st->state;
	पूर्णांक ret = 0;

	ret = cpuhp_invoke_callback_range(false, cpu, st, target);
	अगर (ret) अणु

		cpuhp_reset_state(st, prev_state);

		अगर (st->state < prev_state)
			WARN_ON(cpuhp_invoke_callback_range(true, cpu, st,
							    prev_state));
	पूर्ण

	वापस ret;
पूर्ण

/* Requires cpu_add_हटाओ_lock to be held */
अटल पूर्णांक __ref _cpu_करोwn(अचिन्हित पूर्णांक cpu, पूर्णांक tasks_frozen,
			   क्रमागत cpuhp_state target)
अणु
	काष्ठा cpuhp_cpu_state *st = per_cpu_ptr(&cpuhp_state, cpu);
	पूर्णांक prev_state, ret = 0;

	अगर (num_online_cpus() == 1)
		वापस -EBUSY;

	अगर (!cpu_present(cpu))
		वापस -EINVAL;

	cpus_ग_लिखो_lock();

	cpuhp_tasks_frozen = tasks_frozen;

	prev_state = cpuhp_set_state(st, target);
	/*
	 * If the current CPU state is in the range of the AP hotplug thपढ़ो,
	 * then we need to kick the thपढ़ो.
	 */
	अगर (st->state > CPUHP_TEARDOWN_CPU) अणु
		st->target = max((पूर्णांक)target, CPUHP_TEARDOWN_CPU);
		ret = cpuhp_kick_ap_work(cpu);
		/*
		 * The AP side has करोne the error rollback alपढ़ोy. Just
		 * वापस the error code..
		 */
		अगर (ret)
			जाओ out;

		/*
		 * We might have stopped still in the range of the AP hotplug
		 * thपढ़ो. Nothing to करो anymore.
		 */
		अगर (st->state > CPUHP_TEARDOWN_CPU)
			जाओ out;

		st->target = target;
	पूर्ण
	/*
	 * The AP brought itself करोwn to CPUHP_TEARDOWN_CPU. So we need
	 * to करो the further cleanups.
	 */
	ret = cpuhp_करोwn_callbacks(cpu, st, target);
	अगर (ret && st->state < prev_state) अणु
		अगर (st->state == CPUHP_TEARDOWN_CPU) अणु
			cpuhp_reset_state(st, prev_state);
			__cpuhp_kick_ap(st);
		पूर्ण अन्यथा अणु
			WARN(1, "DEAD callback error for CPU%d", cpu);
		पूर्ण
	पूर्ण

out:
	cpus_ग_लिखो_unlock();
	/*
	 * Do post unplug cleanup. This is still रक्षित against
	 * concurrent CPU hotplug via cpu_add_हटाओ_lock.
	 */
	lockup_detector_cleanup();
	arch_smt_update();
	वापस ret;
पूर्ण

अटल पूर्णांक cpu_करोwn_maps_locked(अचिन्हित पूर्णांक cpu, क्रमागत cpuhp_state target)
अणु
	अगर (cpu_hotplug_disabled)
		वापस -EBUSY;
	वापस _cpu_करोwn(cpu, 0, target);
पूर्ण

अटल पूर्णांक cpu_करोwn(अचिन्हित पूर्णांक cpu, क्रमागत cpuhp_state target)
अणु
	पूर्णांक err;

	cpu_maps_update_begin();
	err = cpu_करोwn_maps_locked(cpu, target);
	cpu_maps_update_करोne();
	वापस err;
पूर्ण

/**
 * cpu_device_करोwn - Bring करोwn a cpu device
 * @dev: Poपूर्णांकer to the cpu device to offline
 *
 * This function is meant to be used by device core cpu subप्रणाली only.
 *
 * Other subप्रणालीs should use हटाओ_cpu() instead.
 */
पूर्णांक cpu_device_करोwn(काष्ठा device *dev)
अणु
	वापस cpu_करोwn(dev->id, CPUHP_OFFLINE);
पूर्ण

पूर्णांक हटाओ_cpu(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक ret;

	lock_device_hotplug();
	ret = device_offline(get_cpu_device(cpu));
	unlock_device_hotplug();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(हटाओ_cpu);

व्योम smp_shutकरोwn_nonboot_cpus(अचिन्हित पूर्णांक primary_cpu)
अणु
	अचिन्हित पूर्णांक cpu;
	पूर्णांक error;

	cpu_maps_update_begin();

	/*
	 * Make certain the cpu I'm about to reboot on is online.
	 *
	 * This is अंतरभूत to what migrate_to_reboot_cpu() alपढ़ोy करो.
	 */
	अगर (!cpu_online(primary_cpu))
		primary_cpu = cpumask_first(cpu_online_mask);

	क्रम_each_online_cpu(cpu) अणु
		अगर (cpu == primary_cpu)
			जारी;

		error = cpu_करोwn_maps_locked(cpu, CPUHP_OFFLINE);
		अगर (error) अणु
			pr_err("Failed to offline CPU%d - error=%d",
				cpu, error);
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Ensure all but the reboot CPU are offline.
	 */
	BUG_ON(num_online_cpus() > 1);

	/*
	 * Make sure the CPUs won't be enabled by someone अन्यथा after this
	 * poपूर्णांक. Kexec will reboot to a new kernel लघुly resetting
	 * everything aदीर्घ the way.
	 */
	cpu_hotplug_disabled++;

	cpu_maps_update_करोne();
पूर्ण

#अन्यथा
#घोषणा takeकरोwn_cpu		शून्य
#पूर्ण_अगर /*CONFIG_HOTPLUG_CPU*/

/**
 * notअगरy_cpu_starting(cpu) - Invoke the callbacks on the starting CPU
 * @cpu: cpu that just started
 *
 * It must be called by the arch code on the new cpu, beक्रमe the new cpu
 * enables पूर्णांकerrupts and beक्रमe the "boot" cpu वापसs from __cpu_up().
 */
व्योम notअगरy_cpu_starting(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpuhp_cpu_state *st = per_cpu_ptr(&cpuhp_state, cpu);
	क्रमागत cpuhp_state target = min((पूर्णांक)st->target, CPUHP_AP_ONLINE);
	पूर्णांक ret;

	rcu_cpu_starting(cpu);	/* Enables RCU usage on this CPU. */
	cpumask_set_cpu(cpu, &cpus_booted_once_mask);
	ret = cpuhp_invoke_callback_range(true, cpu, st, target);

	/*
	 * STARTING must not fail!
	 */
	WARN_ON_ONCE(ret);
पूर्ण

/*
 * Called from the idle task. Wake up the controlling task which brings the
 * hotplug thपढ़ो of the upcoming CPU up and then delegates the rest of the
 * online bringup to the hotplug thपढ़ो.
 */
व्योम cpuhp_online_idle(क्रमागत cpuhp_state state)
अणु
	काष्ठा cpuhp_cpu_state *st = this_cpu_ptr(&cpuhp_state);

	/* Happens क्रम the boot cpu */
	अगर (state != CPUHP_AP_ONLINE_IDLE)
		वापस;

	/*
	 * Unpart the stopper thपढ़ो beक्रमe we start the idle loop (and start
	 * scheduling); this ensures the stopper task is always available.
	 */
	stop_machine_unpark(smp_processor_id());

	st->state = CPUHP_AP_ONLINE_IDLE;
	complete_ap_thपढ़ो(st, true);
पूर्ण

/* Requires cpu_add_हटाओ_lock to be held */
अटल पूर्णांक _cpu_up(अचिन्हित पूर्णांक cpu, पूर्णांक tasks_frozen, क्रमागत cpuhp_state target)
अणु
	काष्ठा cpuhp_cpu_state *st = per_cpu_ptr(&cpuhp_state, cpu);
	काष्ठा task_काष्ठा *idle;
	पूर्णांक ret = 0;

	cpus_ग_लिखो_lock();

	अगर (!cpu_present(cpu)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * The caller of cpu_up() might have raced with another
	 * caller. Nothing to करो.
	 */
	अगर (st->state >= target)
		जाओ out;

	अगर (st->state == CPUHP_OFFLINE) अणु
		/* Let it fail beक्रमe we try to bring the cpu up */
		idle = idle_thपढ़ो_get(cpu);
		अगर (IS_ERR(idle)) अणु
			ret = PTR_ERR(idle);
			जाओ out;
		पूर्ण
	पूर्ण

	cpuhp_tasks_frozen = tasks_frozen;

	cpuhp_set_state(st, target);
	/*
	 * If the current CPU state is in the range of the AP hotplug thपढ़ो,
	 * then we need to kick the thपढ़ो once more.
	 */
	अगर (st->state > CPUHP_BRINGUP_CPU) अणु
		ret = cpuhp_kick_ap_work(cpu);
		/*
		 * The AP side has करोne the error rollback alपढ़ोy. Just
		 * वापस the error code..
		 */
		अगर (ret)
			जाओ out;
	पूर्ण

	/*
	 * Try to reach the target state. We max out on the BP at
	 * CPUHP_BRINGUP_CPU. After that the AP hotplug thपढ़ो is
	 * responsible क्रम bringing it up to the target state.
	 */
	target = min((पूर्णांक)target, CPUHP_BRINGUP_CPU);
	ret = cpuhp_up_callbacks(cpu, st, target);
out:
	cpus_ग_लिखो_unlock();
	arch_smt_update();
	वापस ret;
पूर्ण

अटल पूर्णांक cpu_up(अचिन्हित पूर्णांक cpu, क्रमागत cpuhp_state target)
अणु
	पूर्णांक err = 0;

	अगर (!cpu_possible(cpu)) अणु
		pr_err("can't online cpu %d because it is not configured as may-hotadd at boot time\n",
		       cpu);
#अगर defined(CONFIG_IA64)
		pr_err("please check additional_cpus= boot parameter\n");
#पूर्ण_अगर
		वापस -EINVAL;
	पूर्ण

	err = try_online_node(cpu_to_node(cpu));
	अगर (err)
		वापस err;

	cpu_maps_update_begin();

	अगर (cpu_hotplug_disabled) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण
	अगर (!cpu_smt_allowed(cpu)) अणु
		err = -EPERM;
		जाओ out;
	पूर्ण

	err = _cpu_up(cpu, 0, target);
out:
	cpu_maps_update_करोne();
	वापस err;
पूर्ण

/**
 * cpu_device_up - Bring up a cpu device
 * @dev: Poपूर्णांकer to the cpu device to online
 *
 * This function is meant to be used by device core cpu subप्रणाली only.
 *
 * Other subप्रणालीs should use add_cpu() instead.
 */
पूर्णांक cpu_device_up(काष्ठा device *dev)
अणु
	वापस cpu_up(dev->id, CPUHP_ONLINE);
पूर्ण

पूर्णांक add_cpu(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक ret;

	lock_device_hotplug();
	ret = device_online(get_cpu_device(cpu));
	unlock_device_hotplug();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(add_cpu);

/**
 * bringup_hibernate_cpu - Bring up the CPU that we hibernated on
 * @sleep_cpu: The cpu we hibernated on and should be brought up.
 *
 * On some architectures like arm64, we can hibernate on any CPU, but on
 * wake up the CPU we hibernated on might be offline as a side effect of
 * using maxcpus= क्रम example.
 */
पूर्णांक bringup_hibernate_cpu(अचिन्हित पूर्णांक sleep_cpu)
अणु
	पूर्णांक ret;

	अगर (!cpu_online(sleep_cpu)) अणु
		pr_info("Hibernated on a CPU that is offline! Bringing CPU up.\n");
		ret = cpu_up(sleep_cpu, CPUHP_ONLINE);
		अगर (ret) अणु
			pr_err("Failed to bring hibernate-CPU up!\n");
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम bringup_nonboot_cpus(अचिन्हित पूर्णांक setup_max_cpus)
अणु
	अचिन्हित पूर्णांक cpu;

	क्रम_each_present_cpu(cpu) अणु
		अगर (num_online_cpus() >= setup_max_cpus)
			अवरोध;
		अगर (!cpu_online(cpu))
			cpu_up(cpu, CPUHP_ONLINE);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP_SMP
अटल cpumask_var_t frozen_cpus;

पूर्णांक मुक्तze_secondary_cpus(पूर्णांक primary)
अणु
	पूर्णांक cpu, error = 0;

	cpu_maps_update_begin();
	अगर (primary == -1) अणु
		primary = cpumask_first(cpu_online_mask);
		अगर (!housekeeping_cpu(primary, HK_FLAG_TIMER))
			primary = housekeeping_any_cpu(HK_FLAG_TIMER);
	पूर्ण अन्यथा अणु
		अगर (!cpu_online(primary))
			primary = cpumask_first(cpu_online_mask);
	पूर्ण

	/*
	 * We take करोwn all of the non-boot CPUs in one shot to aव्योम races
	 * with the userspace trying to use the CPU hotplug at the same समय
	 */
	cpumask_clear(frozen_cpus);

	pr_info("Disabling non-boot CPUs ...\n");
	क्रम_each_online_cpu(cpu) अणु
		अगर (cpu == primary)
			जारी;

		अगर (pm_wakeup_pending()) अणु
			pr_info("Wakeup pending. Abort CPU freeze\n");
			error = -EBUSY;
			अवरोध;
		पूर्ण

		trace_suspend_resume(TPS("CPU_OFF"), cpu, true);
		error = _cpu_करोwn(cpu, 1, CPUHP_OFFLINE);
		trace_suspend_resume(TPS("CPU_OFF"), cpu, false);
		अगर (!error)
			cpumask_set_cpu(cpu, frozen_cpus);
		अन्यथा अणु
			pr_err("Error taking CPU%d down: %d\n", cpu, error);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!error)
		BUG_ON(num_online_cpus() > 1);
	अन्यथा
		pr_err("Non-boot CPUs are not disabled\n");

	/*
	 * Make sure the CPUs won't be enabled by someone अन्यथा. We need to करो
	 * this even in हाल of failure as all मुक्तze_secondary_cpus() users are
	 * supposed to करो thaw_secondary_cpus() on the failure path.
	 */
	cpu_hotplug_disabled++;

	cpu_maps_update_करोne();
	वापस error;
पूर्ण

व्योम __weak arch_thaw_secondary_cpus_begin(व्योम)
अणु
पूर्ण

व्योम __weak arch_thaw_secondary_cpus_end(व्योम)
अणु
पूर्ण

व्योम thaw_secondary_cpus(व्योम)
अणु
	पूर्णांक cpu, error;

	/* Allow everyone to use the CPU hotplug again */
	cpu_maps_update_begin();
	__cpu_hotplug_enable();
	अगर (cpumask_empty(frozen_cpus))
		जाओ out;

	pr_info("Enabling non-boot CPUs ...\n");

	arch_thaw_secondary_cpus_begin();

	क्रम_each_cpu(cpu, frozen_cpus) अणु
		trace_suspend_resume(TPS("CPU_ON"), cpu, true);
		error = _cpu_up(cpu, 1, CPUHP_ONLINE);
		trace_suspend_resume(TPS("CPU_ON"), cpu, false);
		अगर (!error) अणु
			pr_info("CPU%d is up\n", cpu);
			जारी;
		पूर्ण
		pr_warn("Error taking CPU%d up: %d\n", cpu, error);
	पूर्ण

	arch_thaw_secondary_cpus_end();

	cpumask_clear(frozen_cpus);
out:
	cpu_maps_update_करोne();
पूर्ण

अटल पूर्णांक __init alloc_frozen_cpus(व्योम)
अणु
	अगर (!alloc_cpumask_var(&frozen_cpus, GFP_KERNEL|__GFP_ZERO))
		वापस -ENOMEM;
	वापस 0;
पूर्ण
core_initcall(alloc_frozen_cpus);

/*
 * When callbacks क्रम CPU hotplug notअगरications are being executed, we must
 * ensure that the state of the प्रणाली with respect to the tasks being frozen
 * or not, as reported by the notअगरication, reमुख्यs unchanged *throughout the
 * duration* of the execution of the callbacks.
 * Hence we need to prevent the मुक्तzer from racing with regular CPU hotplug.
 *
 * This synchronization is implemented by mutually excluding regular CPU
 * hotplug and Suspend/Hibernate call paths by hooking onto the Suspend/
 * Hibernate notअगरications.
 */
अटल पूर्णांक
cpu_hotplug_pm_callback(काष्ठा notअगरier_block *nb,
			अचिन्हित दीर्घ action, व्योम *ptr)
अणु
	चयन (action) अणु

	हाल PM_SUSPEND_PREPARE:
	हाल PM_HIBERNATION_PREPARE:
		cpu_hotplug_disable();
		अवरोध;

	हाल PM_POST_SUSPEND:
	हाल PM_POST_HIBERNATION:
		cpu_hotplug_enable();
		अवरोध;

	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण


अटल पूर्णांक __init cpu_hotplug_pm_sync_init(व्योम)
अणु
	/*
	 * cpu_hotplug_pm_callback has higher priority than x86
	 * bsp_pm_callback which depends on cpu_hotplug_pm_callback
	 * to disable cpu hotplug to aव्योम cpu hotplug race.
	 */
	pm_notअगरier(cpu_hotplug_pm_callback, 0);
	वापस 0;
पूर्ण
core_initcall(cpu_hotplug_pm_sync_init);

#पूर्ण_अगर /* CONFIG_PM_SLEEP_SMP */

पूर्णांक __boot_cpu_id;

#पूर्ण_अगर /* CONFIG_SMP */

/* Boot processor state steps */
अटल काष्ठा cpuhp_step cpuhp_hp_states[] = अणु
	[CPUHP_OFFLINE] = अणु
		.name			= "offline",
		.startup.single		= शून्य,
		.tearकरोwn.single	= शून्य,
	पूर्ण,
#अगर_घोषित CONFIG_SMP
	[CPUHP_CREATE_THREADS]= अणु
		.name			= "threads:prepare",
		.startup.single		= smpboot_create_thपढ़ोs,
		.tearकरोwn.single	= शून्य,
		.cant_stop		= true,
	पूर्ण,
	[CPUHP_PERF_PREPARE] = अणु
		.name			= "perf:prepare",
		.startup.single		= perf_event_init_cpu,
		.tearकरोwn.single	= perf_event_निकास_cpu,
	पूर्ण,
	[CPUHP_WORKQUEUE_PREP] = अणु
		.name			= "workqueue:prepare",
		.startup.single		= workqueue_prepare_cpu,
		.tearकरोwn.single	= शून्य,
	पूर्ण,
	[CPUHP_HRTIMERS_PREPARE] = अणु
		.name			= "hrtimers:prepare",
		.startup.single		= hrसमयrs_prepare_cpu,
		.tearकरोwn.single	= hrसमयrs_dead_cpu,
	पूर्ण,
	[CPUHP_SMPCFD_PREPARE] = अणु
		.name			= "smpcfd:prepare",
		.startup.single		= smpcfd_prepare_cpu,
		.tearकरोwn.single	= smpcfd_dead_cpu,
	पूर्ण,
	[CPUHP_RELAY_PREPARE] = अणु
		.name			= "relay:prepare",
		.startup.single		= relay_prepare_cpu,
		.tearकरोwn.single	= शून्य,
	पूर्ण,
	[CPUHP_SLAB_PREPARE] = अणु
		.name			= "slab:prepare",
		.startup.single		= slab_prepare_cpu,
		.tearकरोwn.single	= slab_dead_cpu,
	पूर्ण,
	[CPUHP_RCUTREE_PREP] = अणु
		.name			= "RCU/tree:prepare",
		.startup.single		= rcutree_prepare_cpu,
		.tearकरोwn.single	= rcutree_dead_cpu,
	पूर्ण,
	/*
	 * On the tear-करोwn path, समयrs_dead_cpu() must be invoked
	 * beक्रमe blk_mq_queue_reinit_notअगरy() from notअगरy_dead(),
	 * otherwise a RCU stall occurs.
	 */
	[CPUHP_TIMERS_PREPARE] = अणु
		.name			= "timers:prepare",
		.startup.single		= समयrs_prepare_cpu,
		.tearकरोwn.single	= समयrs_dead_cpu,
	पूर्ण,
	/* Kicks the plugged cpu पूर्णांकo lअगरe */
	[CPUHP_BRINGUP_CPU] = अणु
		.name			= "cpu:bringup",
		.startup.single		= bringup_cpu,
		.tearकरोwn.single	= finish_cpu,
		.cant_stop		= true,
	पूर्ण,
	/* Final state beक्रमe CPU समाप्तs itself */
	[CPUHP_AP_IDLE_DEAD] = अणु
		.name			= "idle:dead",
	पूर्ण,
	/*
	 * Last state beक्रमe CPU enters the idle loop to die. Transient state
	 * क्रम synchronization.
	 */
	[CPUHP_AP_OFFLINE] = अणु
		.name			= "ap:offline",
		.cant_stop		= true,
	पूर्ण,
	/* First state is scheduler control. Interrupts are disabled */
	[CPUHP_AP_SCHED_STARTING] = अणु
		.name			= "sched:starting",
		.startup.single		= sched_cpu_starting,
		.tearकरोwn.single	= sched_cpu_dying,
	पूर्ण,
	[CPUHP_AP_RCUTREE_DYING] = अणु
		.name			= "RCU/tree:dying",
		.startup.single		= शून्य,
		.tearकरोwn.single	= rcutree_dying_cpu,
	पूर्ण,
	[CPUHP_AP_SMPCFD_DYING] = अणु
		.name			= "smpcfd:dying",
		.startup.single		= शून्य,
		.tearकरोwn.single	= smpcfd_dying_cpu,
	पूर्ण,
	/* Entry state on starting. Interrupts enabled from here on. Transient
	 * state क्रम synchronsization */
	[CPUHP_AP_ONLINE] = अणु
		.name			= "ap:online",
	पूर्ण,
	/*
	 * Handled on control processor until the plugged processor manages
	 * this itself.
	 */
	[CPUHP_TEARDOWN_CPU] = अणु
		.name			= "cpu:teardown",
		.startup.single		= शून्य,
		.tearकरोwn.single	= takeकरोwn_cpu,
		.cant_stop		= true,
	पूर्ण,

	[CPUHP_AP_SCHED_WAIT_EMPTY] = अणु
		.name			= "sched:waitempty",
		.startup.single		= शून्य,
		.tearकरोwn.single	= sched_cpu_रुको_empty,
	पूर्ण,

	/* Handle smpboot thपढ़ोs park/unpark */
	[CPUHP_AP_SMPBOOT_THREADS] = अणु
		.name			= "smpboot/threads:online",
		.startup.single		= smpboot_unpark_thपढ़ोs,
		.tearकरोwn.single	= smpboot_park_thपढ़ोs,
	पूर्ण,
	[CPUHP_AP_IRQ_AFFINITY_ONLINE] = अणु
		.name			= "irq/affinity:online",
		.startup.single		= irq_affinity_online_cpu,
		.tearकरोwn.single	= शून्य,
	पूर्ण,
	[CPUHP_AP_PERF_ONLINE] = अणु
		.name			= "perf:online",
		.startup.single		= perf_event_init_cpu,
		.tearकरोwn.single	= perf_event_निकास_cpu,
	पूर्ण,
	[CPUHP_AP_WATCHDOG_ONLINE] = अणु
		.name			= "lockup_detector:online",
		.startup.single		= lockup_detector_online_cpu,
		.tearकरोwn.single	= lockup_detector_offline_cpu,
	पूर्ण,
	[CPUHP_AP_WORKQUEUE_ONLINE] = अणु
		.name			= "workqueue:online",
		.startup.single		= workqueue_online_cpu,
		.tearकरोwn.single	= workqueue_offline_cpu,
	पूर्ण,
	[CPUHP_AP_RCUTREE_ONLINE] = अणु
		.name			= "RCU/tree:online",
		.startup.single		= rcutree_online_cpu,
		.tearकरोwn.single	= rcutree_offline_cpu,
	पूर्ण,
#पूर्ण_अगर
	/*
	 * The dynamically रेजिस्टरed state space is here
	 */

#अगर_घोषित CONFIG_SMP
	/* Last state is scheduler control setting the cpu active */
	[CPUHP_AP_ACTIVE] = अणु
		.name			= "sched:active",
		.startup.single		= sched_cpu_activate,
		.tearकरोwn.single	= sched_cpu_deactivate,
	पूर्ण,
#पूर्ण_अगर

	/* CPU is fully up and running. */
	[CPUHP_ONLINE] = अणु
		.name			= "online",
		.startup.single		= शून्य,
		.tearकरोwn.single	= शून्य,
	पूर्ण,
पूर्ण;

/* Sanity check क्रम callbacks */
अटल पूर्णांक cpuhp_cb_check(क्रमागत cpuhp_state state)
अणु
	अगर (state <= CPUHP_OFFLINE || state >= CPUHP_ONLINE)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/*
 * Returns a मुक्त क्रम dynamic slot assignment of the Online state. The states
 * are रक्षित by the cpuhp_slot_states mutex and an empty slot is identअगरied
 * by having no name asचिन्हित.
 */
अटल पूर्णांक cpuhp_reserve_state(क्रमागत cpuhp_state state)
अणु
	क्रमागत cpuhp_state i, end;
	काष्ठा cpuhp_step *step;

	चयन (state) अणु
	हाल CPUHP_AP_ONLINE_DYN:
		step = cpuhp_hp_states + CPUHP_AP_ONLINE_DYN;
		end = CPUHP_AP_ONLINE_DYN_END;
		अवरोध;
	हाल CPUHP_BP_PREPARE_DYN:
		step = cpuhp_hp_states + CPUHP_BP_PREPARE_DYN;
		end = CPUHP_BP_PREPARE_DYN_END;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (i = state; i <= end; i++, step++) अणु
		अगर (!step->name)
			वापस i;
	पूर्ण
	WARN(1, "No more dynamic states available for CPU hotplug\n");
	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक cpuhp_store_callbacks(क्रमागत cpuhp_state state, स्थिर अक्षर *name,
				 पूर्णांक (*startup)(अचिन्हित पूर्णांक cpu),
				 पूर्णांक (*tearकरोwn)(अचिन्हित पूर्णांक cpu),
				 bool multi_instance)
अणु
	/* (Un)Install the callbacks क्रम further cpu hotplug operations */
	काष्ठा cpuhp_step *sp;
	पूर्णांक ret = 0;

	/*
	 * If name is शून्य, then the state माला_लो हटाओd.
	 *
	 * CPUHP_AP_ONLINE_DYN and CPUHP_BP_PREPARE_DYN are handed out on
	 * the first allocation from these dynamic ranges, so the removal
	 * would trigger a new allocation and clear the wrong (alपढ़ोy
	 * empty) state, leaving the callbacks of the to be cleared state
	 * dangling, which causes wreckage on the next hotplug operation.
	 */
	अगर (name && (state == CPUHP_AP_ONLINE_DYN ||
		     state == CPUHP_BP_PREPARE_DYN)) अणु
		ret = cpuhp_reserve_state(state);
		अगर (ret < 0)
			वापस ret;
		state = ret;
	पूर्ण
	sp = cpuhp_get_step(state);
	अगर (name && sp->name)
		वापस -EBUSY;

	sp->startup.single = startup;
	sp->tearकरोwn.single = tearकरोwn;
	sp->name = name;
	sp->multi_instance = multi_instance;
	INIT_HLIST_HEAD(&sp->list);
	वापस ret;
पूर्ण

अटल व्योम *cpuhp_get_tearकरोwn_cb(क्रमागत cpuhp_state state)
अणु
	वापस cpuhp_get_step(state)->tearकरोwn.single;
पूर्ण

/*
 * Call the startup/tearकरोwn function क्रम a step either on the AP or
 * on the current CPU.
 */
अटल पूर्णांक cpuhp_issue_call(पूर्णांक cpu, क्रमागत cpuhp_state state, bool bringup,
			    काष्ठा hlist_node *node)
अणु
	काष्ठा cpuhp_step *sp = cpuhp_get_step(state);
	पूर्णांक ret;

	/*
	 * If there's nothing to करो, we करोne.
	 * Relies on the जोड़ क्रम multi_instance.
	 */
	अगर (cpuhp_step_empty(bringup, sp))
		वापस 0;
	/*
	 * The non AP bound callbacks can fail on bringup. On tearकरोwn
	 * e.g. module removal we crash क्रम now.
	 */
#अगर_घोषित CONFIG_SMP
	अगर (cpuhp_is_ap_state(state))
		ret = cpuhp_invoke_ap_callback(cpu, state, bringup, node);
	अन्यथा
		ret = cpuhp_invoke_callback(cpu, state, bringup, node, शून्य);
#अन्यथा
	ret = cpuhp_invoke_callback(cpu, state, bringup, node, शून्य);
#पूर्ण_अगर
	BUG_ON(ret && !bringup);
	वापस ret;
पूर्ण

/*
 * Called from __cpuhp_setup_state on a recoverable failure.
 *
 * Note: The tearकरोwn callbacks क्रम rollback are not allowed to fail!
 */
अटल व्योम cpuhp_rollback_install(पूर्णांक failedcpu, क्रमागत cpuhp_state state,
				   काष्ठा hlist_node *node)
अणु
	पूर्णांक cpu;

	/* Roll back the alपढ़ोy executed steps on the other cpus */
	क्रम_each_present_cpu(cpu) अणु
		काष्ठा cpuhp_cpu_state *st = per_cpu_ptr(&cpuhp_state, cpu);
		पूर्णांक cpustate = st->state;

		अगर (cpu >= failedcpu)
			अवरोध;

		/* Did we invoke the startup call on that cpu ? */
		अगर (cpustate >= state)
			cpuhp_issue_call(cpu, state, false, node);
	पूर्ण
पूर्ण

पूर्णांक __cpuhp_state_add_instance_cpuslocked(क्रमागत cpuhp_state state,
					  काष्ठा hlist_node *node,
					  bool invoke)
अणु
	काष्ठा cpuhp_step *sp;
	पूर्णांक cpu;
	पूर्णांक ret;

	lockdep_निश्चित_cpus_held();

	sp = cpuhp_get_step(state);
	अगर (sp->multi_instance == false)
		वापस -EINVAL;

	mutex_lock(&cpuhp_state_mutex);

	अगर (!invoke || !sp->startup.multi)
		जाओ add_node;

	/*
	 * Try to call the startup callback क्रम each present cpu
	 * depending on the hotplug state of the cpu.
	 */
	क्रम_each_present_cpu(cpu) अणु
		काष्ठा cpuhp_cpu_state *st = per_cpu_ptr(&cpuhp_state, cpu);
		पूर्णांक cpustate = st->state;

		अगर (cpustate < state)
			जारी;

		ret = cpuhp_issue_call(cpu, state, true, node);
		अगर (ret) अणु
			अगर (sp->tearकरोwn.multi)
				cpuhp_rollback_install(cpu, state, node);
			जाओ unlock;
		पूर्ण
	पूर्ण
add_node:
	ret = 0;
	hlist_add_head(node, &sp->list);
unlock:
	mutex_unlock(&cpuhp_state_mutex);
	वापस ret;
पूर्ण

पूर्णांक __cpuhp_state_add_instance(क्रमागत cpuhp_state state, काष्ठा hlist_node *node,
			       bool invoke)
अणु
	पूर्णांक ret;

	cpus_पढ़ो_lock();
	ret = __cpuhp_state_add_instance_cpuslocked(state, node, invoke);
	cpus_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__cpuhp_state_add_instance);

/**
 * __cpuhp_setup_state_cpuslocked - Setup the callbacks क्रम an hotplug machine state
 * @state:		The state to setup
 * @invoke:		If true, the startup function is invoked क्रम cpus where
 *			cpu state >= @state
 * @startup:		startup callback function
 * @tearकरोwn:		tearकरोwn callback function
 * @multi_instance:	State is set up क्रम multiple instances which get
 *			added afterwards.
 *
 * The caller needs to hold cpus पढ़ो locked जबतक calling this function.
 * Returns:
 *   On success:
 *      Positive state number अगर @state is CPUHP_AP_ONLINE_DYN
 *      0 क्रम all other states
 *   On failure: proper (negative) error code
 */
पूर्णांक __cpuhp_setup_state_cpuslocked(क्रमागत cpuhp_state state,
				   स्थिर अक्षर *name, bool invoke,
				   पूर्णांक (*startup)(अचिन्हित पूर्णांक cpu),
				   पूर्णांक (*tearकरोwn)(अचिन्हित पूर्णांक cpu),
				   bool multi_instance)
अणु
	पूर्णांक cpu, ret = 0;
	bool dynstate;

	lockdep_निश्चित_cpus_held();

	अगर (cpuhp_cb_check(state) || !name)
		वापस -EINVAL;

	mutex_lock(&cpuhp_state_mutex);

	ret = cpuhp_store_callbacks(state, name, startup, tearकरोwn,
				    multi_instance);

	dynstate = state == CPUHP_AP_ONLINE_DYN;
	अगर (ret > 0 && dynstate) अणु
		state = ret;
		ret = 0;
	पूर्ण

	अगर (ret || !invoke || !startup)
		जाओ out;

	/*
	 * Try to call the startup callback क्रम each present cpu
	 * depending on the hotplug state of the cpu.
	 */
	क्रम_each_present_cpu(cpu) अणु
		काष्ठा cpuhp_cpu_state *st = per_cpu_ptr(&cpuhp_state, cpu);
		पूर्णांक cpustate = st->state;

		अगर (cpustate < state)
			जारी;

		ret = cpuhp_issue_call(cpu, state, true, शून्य);
		अगर (ret) अणु
			अगर (tearकरोwn)
				cpuhp_rollback_install(cpu, state, शून्य);
			cpuhp_store_callbacks(state, शून्य, शून्य, शून्य, false);
			जाओ out;
		पूर्ण
	पूर्ण
out:
	mutex_unlock(&cpuhp_state_mutex);
	/*
	 * If the requested state is CPUHP_AP_ONLINE_DYN, वापस the
	 * dynamically allocated state in हाल of success.
	 */
	अगर (!ret && dynstate)
		वापस state;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__cpuhp_setup_state_cpuslocked);

पूर्णांक __cpuhp_setup_state(क्रमागत cpuhp_state state,
			स्थिर अक्षर *name, bool invoke,
			पूर्णांक (*startup)(अचिन्हित पूर्णांक cpu),
			पूर्णांक (*tearकरोwn)(अचिन्हित पूर्णांक cpu),
			bool multi_instance)
अणु
	पूर्णांक ret;

	cpus_पढ़ो_lock();
	ret = __cpuhp_setup_state_cpuslocked(state, name, invoke, startup,
					     tearकरोwn, multi_instance);
	cpus_पढ़ो_unlock();
	वापस ret;
पूर्ण
EXPORT_SYMBOL(__cpuhp_setup_state);

पूर्णांक __cpuhp_state_हटाओ_instance(क्रमागत cpuhp_state state,
				  काष्ठा hlist_node *node, bool invoke)
अणु
	काष्ठा cpuhp_step *sp = cpuhp_get_step(state);
	पूर्णांक cpu;

	BUG_ON(cpuhp_cb_check(state));

	अगर (!sp->multi_instance)
		वापस -EINVAL;

	cpus_पढ़ो_lock();
	mutex_lock(&cpuhp_state_mutex);

	अगर (!invoke || !cpuhp_get_tearकरोwn_cb(state))
		जाओ हटाओ;
	/*
	 * Call the tearकरोwn callback क्रम each present cpu depending
	 * on the hotplug state of the cpu. This function is not
	 * allowed to fail currently!
	 */
	क्रम_each_present_cpu(cpu) अणु
		काष्ठा cpuhp_cpu_state *st = per_cpu_ptr(&cpuhp_state, cpu);
		पूर्णांक cpustate = st->state;

		अगर (cpustate >= state)
			cpuhp_issue_call(cpu, state, false, node);
	पूर्ण

हटाओ:
	hlist_del(node);
	mutex_unlock(&cpuhp_state_mutex);
	cpus_पढ़ो_unlock();

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__cpuhp_state_हटाओ_instance);

/**
 * __cpuhp_हटाओ_state_cpuslocked - Remove the callbacks क्रम an hotplug machine state
 * @state:	The state to हटाओ
 * @invoke:	If true, the tearकरोwn function is invoked क्रम cpus where
 *		cpu state >= @state
 *
 * The caller needs to hold cpus पढ़ो locked जबतक calling this function.
 * The tearकरोwn callback is currently not allowed to fail. Think
 * about module removal!
 */
व्योम __cpuhp_हटाओ_state_cpuslocked(क्रमागत cpuhp_state state, bool invoke)
अणु
	काष्ठा cpuhp_step *sp = cpuhp_get_step(state);
	पूर्णांक cpu;

	BUG_ON(cpuhp_cb_check(state));

	lockdep_निश्चित_cpus_held();

	mutex_lock(&cpuhp_state_mutex);
	अगर (sp->multi_instance) अणु
		WARN(!hlist_empty(&sp->list),
		     "Error: Removing state %d which has instances left.\n",
		     state);
		जाओ हटाओ;
	पूर्ण

	अगर (!invoke || !cpuhp_get_tearकरोwn_cb(state))
		जाओ हटाओ;

	/*
	 * Call the tearकरोwn callback क्रम each present cpu depending
	 * on the hotplug state of the cpu. This function is not
	 * allowed to fail currently!
	 */
	क्रम_each_present_cpu(cpu) अणु
		काष्ठा cpuhp_cpu_state *st = per_cpu_ptr(&cpuhp_state, cpu);
		पूर्णांक cpustate = st->state;

		अगर (cpustate >= state)
			cpuhp_issue_call(cpu, state, false, शून्य);
	पूर्ण
हटाओ:
	cpuhp_store_callbacks(state, शून्य, शून्य, शून्य, false);
	mutex_unlock(&cpuhp_state_mutex);
पूर्ण
EXPORT_SYMBOL(__cpuhp_हटाओ_state_cpuslocked);

व्योम __cpuhp_हटाओ_state(क्रमागत cpuhp_state state, bool invoke)
अणु
	cpus_पढ़ो_lock();
	__cpuhp_हटाओ_state_cpuslocked(state, invoke);
	cpus_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(__cpuhp_हटाओ_state);

#अगर_घोषित CONFIG_HOTPLUG_SMT
अटल व्योम cpuhp_offline_cpu_device(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device *dev = get_cpu_device(cpu);

	dev->offline = true;
	/* Tell user space about the state change */
	kobject_uevent(&dev->kobj, KOBJ_OFFLINE);
पूर्ण

अटल व्योम cpuhp_online_cpu_device(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा device *dev = get_cpu_device(cpu);

	dev->offline = false;
	/* Tell user space about the state change */
	kobject_uevent(&dev->kobj, KOBJ_ONLINE);
पूर्ण

पूर्णांक cpuhp_smt_disable(क्रमागत cpuhp_smt_control ctrlval)
अणु
	पूर्णांक cpu, ret = 0;

	cpu_maps_update_begin();
	क्रम_each_online_cpu(cpu) अणु
		अगर (topology_is_primary_thपढ़ो(cpu))
			जारी;
		ret = cpu_करोwn_maps_locked(cpu, CPUHP_OFFLINE);
		अगर (ret)
			अवरोध;
		/*
		 * As this needs to hold the cpu maps lock it's impossible
		 * to call device_offline() because that ends up calling
		 * cpu_करोwn() which takes cpu maps lock. cpu maps lock
		 * needs to be held as this might race against in kernel
		 * abusers of the hotplug machinery (thermal management).
		 *
		 * So nothing would update device:offline state. That would
		 * leave the sysfs entry stale and prevent onlining after
		 * smt control has been changed to 'off' again. This is
		 * called under the sysfs hotplug lock, so it is properly
		 * serialized against the regular offline usage.
		 */
		cpuhp_offline_cpu_device(cpu);
	पूर्ण
	अगर (!ret)
		cpu_smt_control = ctrlval;
	cpu_maps_update_करोne();
	वापस ret;
पूर्ण

पूर्णांक cpuhp_smt_enable(व्योम)
अणु
	पूर्णांक cpu, ret = 0;

	cpu_maps_update_begin();
	cpu_smt_control = CPU_SMT_ENABLED;
	क्रम_each_present_cpu(cpu) अणु
		/* Skip online CPUs and CPUs on offline nodes */
		अगर (cpu_online(cpu) || !node_online(cpu_to_node(cpu)))
			जारी;
		ret = _cpu_up(cpu, 0, CPUHP_ONLINE);
		अगर (ret)
			अवरोध;
		/* See comment in cpuhp_smt_disable() */
		cpuhp_online_cpu_device(cpu);
	पूर्ण
	cpu_maps_update_करोne();
	वापस ret;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_SYSFS) && defined(CONFIG_HOTPLUG_CPU)
अटल sमाप_प्रकार show_cpuhp_state(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cpuhp_cpu_state *st = per_cpu_ptr(&cpuhp_state, dev->id);

	वापस प्र_लिखो(buf, "%d\n", st->state);
पूर्ण
अटल DEVICE_ATTR(state, 0444, show_cpuhp_state, शून्य);

अटल sमाप_प्रकार ग_लिखो_cpuhp_target(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cpuhp_cpu_state *st = per_cpu_ptr(&cpuhp_state, dev->id);
	काष्ठा cpuhp_step *sp;
	पूर्णांक target, ret;

	ret = kstrtoपूर्णांक(buf, 10, &target);
	अगर (ret)
		वापस ret;

#अगर_घोषित CONFIG_CPU_HOTPLUG_STATE_CONTROL
	अगर (target < CPUHP_OFFLINE || target > CPUHP_ONLINE)
		वापस -EINVAL;
#अन्यथा
	अगर (target != CPUHP_OFFLINE && target != CPUHP_ONLINE)
		वापस -EINVAL;
#पूर्ण_अगर

	ret = lock_device_hotplug_sysfs();
	अगर (ret)
		वापस ret;

	mutex_lock(&cpuhp_state_mutex);
	sp = cpuhp_get_step(target);
	ret = !sp->name || sp->cant_stop ? -EINVAL : 0;
	mutex_unlock(&cpuhp_state_mutex);
	अगर (ret)
		जाओ out;

	अगर (st->state < target)
		ret = cpu_up(dev->id, target);
	अन्यथा
		ret = cpu_करोwn(dev->id, target);
out:
	unlock_device_hotplug();
	वापस ret ? ret : count;
पूर्ण

अटल sमाप_प्रकार show_cpuhp_target(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cpuhp_cpu_state *st = per_cpu_ptr(&cpuhp_state, dev->id);

	वापस प्र_लिखो(buf, "%d\n", st->target);
पूर्ण
अटल DEVICE_ATTR(target, 0644, show_cpuhp_target, ग_लिखो_cpuhp_target);


अटल sमाप_प्रकार ग_लिखो_cpuhp_fail(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा cpuhp_cpu_state *st = per_cpu_ptr(&cpuhp_state, dev->id);
	काष्ठा cpuhp_step *sp;
	पूर्णांक fail, ret;

	ret = kstrtoपूर्णांक(buf, 10, &fail);
	अगर (ret)
		वापस ret;

	अगर (fail == CPUHP_INVALID) अणु
		st->fail = fail;
		वापस count;
	पूर्ण

	अगर (fail < CPUHP_OFFLINE || fail > CPUHP_ONLINE)
		वापस -EINVAL;

	/*
	 * Cannot fail STARTING/DYING callbacks.
	 */
	अगर (cpuhp_is_atomic_state(fail))
		वापस -EINVAL;

	/*
	 * DEAD callbacks cannot fail...
	 * ... neither can CPUHP_BRINGUP_CPU during hotunplug. The latter
	 * triggering STARTING callbacks, a failure in this state would
	 * hinder rollback.
	 */
	अगर (fail <= CPUHP_BRINGUP_CPU && st->state > CPUHP_BRINGUP_CPU)
		वापस -EINVAL;

	/*
	 * Cannot fail anything that करोesn't have callbacks.
	 */
	mutex_lock(&cpuhp_state_mutex);
	sp = cpuhp_get_step(fail);
	अगर (!sp->startup.single && !sp->tearकरोwn.single)
		ret = -EINVAL;
	mutex_unlock(&cpuhp_state_mutex);
	अगर (ret)
		वापस ret;

	st->fail = fail;

	वापस count;
पूर्ण

अटल sमाप_प्रकार show_cpuhp_fail(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cpuhp_cpu_state *st = per_cpu_ptr(&cpuhp_state, dev->id);

	वापस प्र_लिखो(buf, "%d\n", st->fail);
पूर्ण

अटल DEVICE_ATTR(fail, 0644, show_cpuhp_fail, ग_लिखो_cpuhp_fail);

अटल काष्ठा attribute *cpuhp_cpu_attrs[] = अणु
	&dev_attr_state.attr,
	&dev_attr_target.attr,
	&dev_attr_fail.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group cpuhp_cpu_attr_group = अणु
	.attrs = cpuhp_cpu_attrs,
	.name = "hotplug",
	शून्य
पूर्ण;

अटल sमाप_प्रकार show_cpuhp_states(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	sमाप_प्रकार cur, res = 0;
	पूर्णांक i;

	mutex_lock(&cpuhp_state_mutex);
	क्रम (i = CPUHP_OFFLINE; i <= CPUHP_ONLINE; i++) अणु
		काष्ठा cpuhp_step *sp = cpuhp_get_step(i);

		अगर (sp->name) अणु
			cur = प्र_लिखो(buf, "%3d: %s\n", i, sp->name);
			buf += cur;
			res += cur;
		पूर्ण
	पूर्ण
	mutex_unlock(&cpuhp_state_mutex);
	वापस res;
पूर्ण
अटल DEVICE_ATTR(states, 0444, show_cpuhp_states, शून्य);

अटल काष्ठा attribute *cpuhp_cpu_root_attrs[] = अणु
	&dev_attr_states.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group cpuhp_cpu_root_attr_group = अणु
	.attrs = cpuhp_cpu_root_attrs,
	.name = "hotplug",
	शून्य
पूर्ण;

#अगर_घोषित CONFIG_HOTPLUG_SMT

अटल sमाप_प्रकार
__store_smt_control(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक ctrlval, ret;

	अगर (sysfs_streq(buf, "on"))
		ctrlval = CPU_SMT_ENABLED;
	अन्यथा अगर (sysfs_streq(buf, "off"))
		ctrlval = CPU_SMT_DISABLED;
	अन्यथा अगर (sysfs_streq(buf, "forceoff"))
		ctrlval = CPU_SMT_FORCE_DISABLED;
	अन्यथा
		वापस -EINVAL;

	अगर (cpu_smt_control == CPU_SMT_FORCE_DISABLED)
		वापस -EPERM;

	अगर (cpu_smt_control == CPU_SMT_NOT_SUPPORTED)
		वापस -ENODEV;

	ret = lock_device_hotplug_sysfs();
	अगर (ret)
		वापस ret;

	अगर (ctrlval != cpu_smt_control) अणु
		चयन (ctrlval) अणु
		हाल CPU_SMT_ENABLED:
			ret = cpuhp_smt_enable();
			अवरोध;
		हाल CPU_SMT_DISABLED:
		हाल CPU_SMT_FORCE_DISABLED:
			ret = cpuhp_smt_disable(ctrlval);
			अवरोध;
		पूर्ण
	पूर्ण

	unlock_device_hotplug();
	वापस ret ? ret : count;
पूर्ण

#अन्यथा /* !CONFIG_HOTPLUG_SMT */
अटल sमाप_प्रकार
__store_smt_control(काष्ठा device *dev, काष्ठा device_attribute *attr,
		    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर /* CONFIG_HOTPLUG_SMT */

अटल स्थिर अक्षर *smt_states[] = अणु
	[CPU_SMT_ENABLED]		= "on",
	[CPU_SMT_DISABLED]		= "off",
	[CPU_SMT_FORCE_DISABLED]	= "forceoff",
	[CPU_SMT_NOT_SUPPORTED]		= "notsupported",
	[CPU_SMT_NOT_IMPLEMENTED]	= "notimplemented",
पूर्ण;

अटल sमाप_प्रकार
show_smt_control(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	स्थिर अक्षर *state = smt_states[cpu_smt_control];

	वापस snम_लिखो(buf, PAGE_SIZE - 2, "%s\n", state);
पूर्ण

अटल sमाप_प्रकार
store_smt_control(काष्ठा device *dev, काष्ठा device_attribute *attr,
		  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस __store_smt_control(dev, attr, buf, count);
पूर्ण
अटल DEVICE_ATTR(control, 0644, show_smt_control, store_smt_control);

अटल sमाप_प्रकार
show_smt_active(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस snम_लिखो(buf, PAGE_SIZE - 2, "%d\n", sched_smt_active());
पूर्ण
अटल DEVICE_ATTR(active, 0444, show_smt_active, शून्य);

अटल काष्ठा attribute *cpuhp_smt_attrs[] = अणु
	&dev_attr_control.attr,
	&dev_attr_active.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group cpuhp_smt_attr_group = अणु
	.attrs = cpuhp_smt_attrs,
	.name = "smt",
	शून्य
पूर्ण;

अटल पूर्णांक __init cpu_smt_sysfs_init(व्योम)
अणु
	वापस sysfs_create_group(&cpu_subsys.dev_root->kobj,
				  &cpuhp_smt_attr_group);
पूर्ण

अटल पूर्णांक __init cpuhp_sysfs_init(व्योम)
अणु
	पूर्णांक cpu, ret;

	ret = cpu_smt_sysfs_init();
	अगर (ret)
		वापस ret;

	ret = sysfs_create_group(&cpu_subsys.dev_root->kobj,
				 &cpuhp_cpu_root_attr_group);
	अगर (ret)
		वापस ret;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा device *dev = get_cpu_device(cpu);

		अगर (!dev)
			जारी;
		ret = sysfs_create_group(&dev->kobj, &cpuhp_cpu_attr_group);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण
device_initcall(cpuhp_sysfs_init);
#पूर्ण_अगर /* CONFIG_SYSFS && CONFIG_HOTPLUG_CPU */

/*
 * cpu_bit_biपंचांगap[] is a special, "compressed" data काष्ठाure that
 * represents all NR_CPUS bits binary values of 1<<nr.
 *
 * It is used by cpumask_of() to get a स्थिरant address to a CPU
 * mask value that has a single bit set only.
 */

/* cpu_bit_biपंचांगap[0] is empty - so we can back पूर्णांकo it */
#घोषणा MASK_DECLARE_1(x)	[x+1][0] = (1UL << (x))
#घोषणा MASK_DECLARE_2(x)	MASK_DECLARE_1(x), MASK_DECLARE_1(x+1)
#घोषणा MASK_DECLARE_4(x)	MASK_DECLARE_2(x), MASK_DECLARE_2(x+2)
#घोषणा MASK_DECLARE_8(x)	MASK_DECLARE_4(x), MASK_DECLARE_4(x+4)

स्थिर अचिन्हित दीर्घ cpu_bit_biपंचांगap[BITS_PER_LONG+1][BITS_TO_LONGS(NR_CPUS)] = अणु

	MASK_DECLARE_8(0),	MASK_DECLARE_8(8),
	MASK_DECLARE_8(16),	MASK_DECLARE_8(24),
#अगर BITS_PER_LONG > 32
	MASK_DECLARE_8(32),	MASK_DECLARE_8(40),
	MASK_DECLARE_8(48),	MASK_DECLARE_8(56),
#पूर्ण_अगर
पूर्ण;
EXPORT_SYMBOL_GPL(cpu_bit_biपंचांगap);

स्थिर DECLARE_BITMAP(cpu_all_bits, NR_CPUS) = CPU_BITS_ALL;
EXPORT_SYMBOL(cpu_all_bits);

#अगर_घोषित CONFIG_INIT_ALL_POSSIBLE
काष्ठा cpumask __cpu_possible_mask __पढ़ो_mostly
	= अणुCPU_BITS_ALLपूर्ण;
#अन्यथा
काष्ठा cpumask __cpu_possible_mask __पढ़ो_mostly;
#पूर्ण_अगर
EXPORT_SYMBOL(__cpu_possible_mask);

काष्ठा cpumask __cpu_online_mask __पढ़ो_mostly;
EXPORT_SYMBOL(__cpu_online_mask);

काष्ठा cpumask __cpu_present_mask __पढ़ो_mostly;
EXPORT_SYMBOL(__cpu_present_mask);

काष्ठा cpumask __cpu_active_mask __पढ़ो_mostly;
EXPORT_SYMBOL(__cpu_active_mask);

काष्ठा cpumask __cpu_dying_mask __पढ़ो_mostly;
EXPORT_SYMBOL(__cpu_dying_mask);

atomic_t __num_online_cpus __पढ़ो_mostly;
EXPORT_SYMBOL(__num_online_cpus);

व्योम init_cpu_present(स्थिर काष्ठा cpumask *src)
अणु
	cpumask_copy(&__cpu_present_mask, src);
पूर्ण

व्योम init_cpu_possible(स्थिर काष्ठा cpumask *src)
अणु
	cpumask_copy(&__cpu_possible_mask, src);
पूर्ण

व्योम init_cpu_online(स्थिर काष्ठा cpumask *src)
अणु
	cpumask_copy(&__cpu_online_mask, src);
पूर्ण

व्योम set_cpu_online(अचिन्हित पूर्णांक cpu, bool online)
अणु
	/*
	 * atomic_inc/dec() is required to handle the horrid abuse of this
	 * function by the reboot and kexec code which invoke it from
	 * IPI/NMI broadcasts when shutting करोwn CPUs. Invocation from
	 * regular CPU hotplug is properly serialized.
	 *
	 * Note, that the fact that __num_online_cpus is of type atomic_t
	 * करोes not protect पढ़ोers which are not serialized against
	 * concurrent hotplug operations.
	 */
	अगर (online) अणु
		अगर (!cpumask_test_and_set_cpu(cpu, &__cpu_online_mask))
			atomic_inc(&__num_online_cpus);
	पूर्ण अन्यथा अणु
		अगर (cpumask_test_and_clear_cpu(cpu, &__cpu_online_mask))
			atomic_dec(&__num_online_cpus);
	पूर्ण
पूर्ण

/*
 * Activate the first processor.
 */
व्योम __init boot_cpu_init(व्योम)
अणु
	पूर्णांक cpu = smp_processor_id();

	/* Mark the boot cpu "present", "online" etc क्रम SMP and UP हाल */
	set_cpu_online(cpu, true);
	set_cpu_active(cpu, true);
	set_cpu_present(cpu, true);
	set_cpu_possible(cpu, true);

#अगर_घोषित CONFIG_SMP
	__boot_cpu_id = cpu;
#पूर्ण_अगर
पूर्ण

/*
 * Must be called _AFTER_ setting up the per_cpu areas
 */
व्योम __init boot_cpu_hotplug_init(व्योम)
अणु
#अगर_घोषित CONFIG_SMP
	cpumask_set_cpu(smp_processor_id(), &cpus_booted_once_mask);
#पूर्ण_अगर
	this_cpu_ग_लिखो(cpuhp_state.state, CPUHP_ONLINE);
पूर्ण

/*
 * These are used क्रम a global "mitigations=" cmdline option क्रम toggling
 * optional CPU mitigations.
 */
क्रमागत cpu_mitigations अणु
	CPU_MITIGATIONS_OFF,
	CPU_MITIGATIONS_AUTO,
	CPU_MITIGATIONS_AUTO_NOSMT,
पूर्ण;

अटल क्रमागत cpu_mitigations cpu_mitigations __ro_after_init =
	CPU_MITIGATIONS_AUTO;

अटल पूर्णांक __init mitigations_parse_cmdline(अक्षर *arg)
अणु
	अगर (!म_भेद(arg, "off"))
		cpu_mitigations = CPU_MITIGATIONS_OFF;
	अन्यथा अगर (!म_भेद(arg, "auto"))
		cpu_mitigations = CPU_MITIGATIONS_AUTO;
	अन्यथा अगर (!म_भेद(arg, "auto,nosmt"))
		cpu_mitigations = CPU_MITIGATIONS_AUTO_NOSMT;
	अन्यथा
		pr_crit("Unsupported mitigations=%s, system may still be vulnerable\n",
			arg);

	वापस 0;
पूर्ण
early_param("mitigations", mitigations_parse_cmdline);

/* mitigations=off */
bool cpu_mitigations_off(व्योम)
अणु
	वापस cpu_mitigations == CPU_MITIGATIONS_OFF;
पूर्ण
EXPORT_SYMBOL_GPL(cpu_mitigations_off);

/* mitigations=स्वतः,nosmt */
bool cpu_mitigations_स्वतः_nosmt(व्योम)
अणु
	वापस cpu_mitigations == CPU_MITIGATIONS_AUTO_NOSMT;
पूर्ण
EXPORT_SYMBOL_GPL(cpu_mitigations_स्वतः_nosmt);
