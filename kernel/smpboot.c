<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Common SMP CPU bringup/tearकरोwn functions
 */
#समावेश <linux/cpu.h>
#समावेश <linux/err.h>
#समावेश <linux/smp.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/export.h>
#समावेश <linux/percpu.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/smpboot.h>

#समावेश "smpboot.h"

#अगर_घोषित CONFIG_SMP

#अगर_घोषित CONFIG_GENERIC_SMP_IDLE_THREAD
/*
 * For the hotplug हाल we keep the task काष्ठाs around and reuse
 * them.
 */
अटल DEFINE_PER_CPU(काष्ठा task_काष्ठा *, idle_thपढ़ोs);

काष्ठा task_काष्ठा *idle_thपढ़ो_get(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा task_काष्ठा *tsk = per_cpu(idle_thपढ़ोs, cpu);

	अगर (!tsk)
		वापस ERR_PTR(-ENOMEM);
	init_idle(tsk, cpu);
	वापस tsk;
पूर्ण

व्योम __init idle_thपढ़ो_set_boot_cpu(व्योम)
अणु
	per_cpu(idle_thपढ़ोs, smp_processor_id()) = current;
पूर्ण

/**
 * idle_init - Initialize the idle thपढ़ो क्रम a cpu
 * @cpu:	The cpu क्रम which the idle thपढ़ो should be initialized
 *
 * Creates the thपढ़ो अगर it करोes not exist.
 */
अटल अंतरभूत व्योम idle_init(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा task_काष्ठा *tsk = per_cpu(idle_thपढ़ोs, cpu);

	अगर (!tsk) अणु
		tsk = विभाजन_idle(cpu);
		अगर (IS_ERR(tsk))
			pr_err("SMP: fork_idle() failed for CPU %u\n", cpu);
		अन्यथा
			per_cpu(idle_thपढ़ोs, cpu) = tsk;
	पूर्ण
पूर्ण

/**
 * idle_thपढ़ोs_init - Initialize idle thपढ़ोs क्रम all cpus
 */
व्योम __init idle_thपढ़ोs_init(व्योम)
अणु
	अचिन्हित पूर्णांक cpu, boot_cpu;

	boot_cpu = smp_processor_id();

	क्रम_each_possible_cpu(cpu) अणु
		अगर (cpu != boot_cpu)
			idle_init(cpu);
	पूर्ण
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* #अगर_घोषित CONFIG_SMP */

अटल LIST_HEAD(hotplug_thपढ़ोs);
अटल DEFINE_MUTEX(smpboot_thपढ़ोs_lock);

काष्ठा smpboot_thपढ़ो_data अणु
	अचिन्हित पूर्णांक			cpu;
	अचिन्हित पूर्णांक			status;
	काष्ठा smp_hotplug_thपढ़ो	*ht;
पूर्ण;

क्रमागत अणु
	HP_THREAD_NONE = 0,
	HP_THREAD_ACTIVE,
	HP_THREAD_PARKED,
पूर्ण;

/**
 * smpboot_thपढ़ो_fn - percpu hotplug thपढ़ो loop function
 * @data:	thपढ़ो data poपूर्णांकer
 *
 * Checks क्रम thपढ़ो stop and park conditions. Calls the necessary
 * setup, cleanup, park and unpark functions क्रम the रेजिस्टरed
 * thपढ़ो.
 *
 * Returns 1 when the thपढ़ो should निकास, 0 otherwise.
 */
अटल पूर्णांक smpboot_thपढ़ो_fn(व्योम *data)
अणु
	काष्ठा smpboot_thपढ़ो_data *td = data;
	काष्ठा smp_hotplug_thपढ़ो *ht = td->ht;

	जबतक (1) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		preempt_disable();
		अगर (kthपढ़ो_should_stop()) अणु
			__set_current_state(TASK_RUNNING);
			preempt_enable();
			/* cleanup must mirror setup */
			अगर (ht->cleanup && td->status != HP_THREAD_NONE)
				ht->cleanup(td->cpu, cpu_online(td->cpu));
			kमुक्त(td);
			वापस 0;
		पूर्ण

		अगर (kthपढ़ो_should_park()) अणु
			__set_current_state(TASK_RUNNING);
			preempt_enable();
			अगर (ht->park && td->status == HP_THREAD_ACTIVE) अणु
				BUG_ON(td->cpu != smp_processor_id());
				ht->park(td->cpu);
				td->status = HP_THREAD_PARKED;
			पूर्ण
			kthपढ़ो_parkme();
			/* We might have been woken क्रम stop */
			जारी;
		पूर्ण

		BUG_ON(td->cpu != smp_processor_id());

		/* Check क्रम state change setup */
		चयन (td->status) अणु
		हाल HP_THREAD_NONE:
			__set_current_state(TASK_RUNNING);
			preempt_enable();
			अगर (ht->setup)
				ht->setup(td->cpu);
			td->status = HP_THREAD_ACTIVE;
			जारी;

		हाल HP_THREAD_PARKED:
			__set_current_state(TASK_RUNNING);
			preempt_enable();
			अगर (ht->unpark)
				ht->unpark(td->cpu);
			td->status = HP_THREAD_ACTIVE;
			जारी;
		पूर्ण

		अगर (!ht->thपढ़ो_should_run(td->cpu)) अणु
			preempt_enable_no_resched();
			schedule();
		पूर्ण अन्यथा अणु
			__set_current_state(TASK_RUNNING);
			preempt_enable();
			ht->thपढ़ो_fn(td->cpu);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
__smpboot_create_thपढ़ो(काष्ठा smp_hotplug_thपढ़ो *ht, अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा task_काष्ठा *tsk = *per_cpu_ptr(ht->store, cpu);
	काष्ठा smpboot_thपढ़ो_data *td;

	अगर (tsk)
		वापस 0;

	td = kzalloc_node(माप(*td), GFP_KERNEL, cpu_to_node(cpu));
	अगर (!td)
		वापस -ENOMEM;
	td->cpu = cpu;
	td->ht = ht;

	tsk = kthपढ़ो_create_on_cpu(smpboot_thपढ़ो_fn, td, cpu,
				    ht->thपढ़ो_comm);
	अगर (IS_ERR(tsk)) अणु
		kमुक्त(td);
		वापस PTR_ERR(tsk);
	पूर्ण
	kthपढ़ो_set_per_cpu(tsk, cpu);
	/*
	 * Park the thपढ़ो so that it could start right on the CPU
	 * when it is available.
	 */
	kthपढ़ो_park(tsk);
	get_task_काष्ठा(tsk);
	*per_cpu_ptr(ht->store, cpu) = tsk;
	अगर (ht->create) अणु
		/*
		 * Make sure that the task has actually scheduled out
		 * पूर्णांकo park position, beक्रमe calling the create
		 * callback. At least the migration thपढ़ो callback
		 * requires that the task is off the runqueue.
		 */
		अगर (!रुको_task_inactive(tsk, TASK_PARKED))
			WARN_ON(1);
		अन्यथा
			ht->create(cpu);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक smpboot_create_thपढ़ोs(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा smp_hotplug_thपढ़ो *cur;
	पूर्णांक ret = 0;

	mutex_lock(&smpboot_thपढ़ोs_lock);
	list_क्रम_each_entry(cur, &hotplug_thपढ़ोs, list) अणु
		ret = __smpboot_create_thपढ़ो(cur, cpu);
		अगर (ret)
			अवरोध;
	पूर्ण
	mutex_unlock(&smpboot_thपढ़ोs_lock);
	वापस ret;
पूर्ण

अटल व्योम smpboot_unpark_thपढ़ो(काष्ठा smp_hotplug_thपढ़ो *ht, अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा task_काष्ठा *tsk = *per_cpu_ptr(ht->store, cpu);

	अगर (!ht->selfparking)
		kthपढ़ो_unpark(tsk);
पूर्ण

पूर्णांक smpboot_unpark_thपढ़ोs(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा smp_hotplug_thपढ़ो *cur;

	mutex_lock(&smpboot_thपढ़ोs_lock);
	list_क्रम_each_entry(cur, &hotplug_thपढ़ोs, list)
		smpboot_unpark_thपढ़ो(cur, cpu);
	mutex_unlock(&smpboot_thपढ़ोs_lock);
	वापस 0;
पूर्ण

अटल व्योम smpboot_park_thपढ़ो(काष्ठा smp_hotplug_thपढ़ो *ht, अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा task_काष्ठा *tsk = *per_cpu_ptr(ht->store, cpu);

	अगर (tsk && !ht->selfparking)
		kthपढ़ो_park(tsk);
पूर्ण

पूर्णांक smpboot_park_thपढ़ोs(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा smp_hotplug_thपढ़ो *cur;

	mutex_lock(&smpboot_thपढ़ोs_lock);
	list_क्रम_each_entry_reverse(cur, &hotplug_thपढ़ोs, list)
		smpboot_park_thपढ़ो(cur, cpu);
	mutex_unlock(&smpboot_thपढ़ोs_lock);
	वापस 0;
पूर्ण

अटल व्योम smpboot_destroy_thपढ़ोs(काष्ठा smp_hotplug_thपढ़ो *ht)
अणु
	अचिन्हित पूर्णांक cpu;

	/* We need to destroy also the parked thपढ़ोs of offline cpus */
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा task_काष्ठा *tsk = *per_cpu_ptr(ht->store, cpu);

		अगर (tsk) अणु
			kthपढ़ो_stop(tsk);
			put_task_काष्ठा(tsk);
			*per_cpu_ptr(ht->store, cpu) = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * smpboot_रेजिस्टर_percpu_thपढ़ो - Register a per_cpu thपढ़ो related
 * 					    to hotplug
 * @plug_thपढ़ो:	Hotplug thपढ़ो descriptor
 *
 * Creates and starts the thपढ़ोs on all online cpus.
 */
पूर्णांक smpboot_रेजिस्टर_percpu_thपढ़ो(काष्ठा smp_hotplug_thपढ़ो *plug_thपढ़ो)
अणु
	अचिन्हित पूर्णांक cpu;
	पूर्णांक ret = 0;

	get_online_cpus();
	mutex_lock(&smpboot_thपढ़ोs_lock);
	क्रम_each_online_cpu(cpu) अणु
		ret = __smpboot_create_thपढ़ो(plug_thपढ़ो, cpu);
		अगर (ret) अणु
			smpboot_destroy_thपढ़ोs(plug_thपढ़ो);
			जाओ out;
		पूर्ण
		smpboot_unpark_thपढ़ो(plug_thपढ़ो, cpu);
	पूर्ण
	list_add(&plug_thपढ़ो->list, &hotplug_thपढ़ोs);
out:
	mutex_unlock(&smpboot_thपढ़ोs_lock);
	put_online_cpus();
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(smpboot_रेजिस्टर_percpu_thपढ़ो);

/**
 * smpboot_unरेजिस्टर_percpu_thपढ़ो - Unरेजिस्टर a per_cpu thपढ़ो related to hotplug
 * @plug_thपढ़ो:	Hotplug thपढ़ो descriptor
 *
 * Stops all thपढ़ोs on all possible cpus.
 */
व्योम smpboot_unरेजिस्टर_percpu_thपढ़ो(काष्ठा smp_hotplug_thपढ़ो *plug_thपढ़ो)
अणु
	get_online_cpus();
	mutex_lock(&smpboot_thपढ़ोs_lock);
	list_del(&plug_thपढ़ो->list);
	smpboot_destroy_thपढ़ोs(plug_thपढ़ो);
	mutex_unlock(&smpboot_thपढ़ोs_lock);
	put_online_cpus();
पूर्ण
EXPORT_SYMBOL_GPL(smpboot_unरेजिस्टर_percpu_thपढ़ो);

अटल DEFINE_PER_CPU(atomic_t, cpu_hotplug_state) = ATOMIC_INIT(CPU_POST_DEAD);

/*
 * Called to poll specअगरied CPU's state, क्रम example, when रुकोing क्रम
 * a CPU to come online.
 */
पूर्णांक cpu_report_state(पूर्णांक cpu)
अणु
	वापस atomic_पढ़ो(&per_cpu(cpu_hotplug_state, cpu));
पूर्ण

/*
 * If CPU has died properly, set its state to CPU_UP_PREPARE and
 * वापस success.  Otherwise, वापस -EBUSY अगर the CPU died after
 * cpu_रुको_death() समयd out.  And yet otherwise again, वापस -EAGAIN
 * अगर cpu_रुको_death() समयd out and the CPU still hasn't gotten around
 * to dying.  In the latter two हालs, the CPU might not be set up
 * properly, but it is up to the arch-specअगरic code to decide.
 * Finally, -EIO indicates an unanticipated problem.
 *
 * Note that it is permissible to omit this call entirely, as is
 * करोne in architectures that करो no CPU-hotplug error checking.
 */
पूर्णांक cpu_check_up_prepare(पूर्णांक cpu)
अणु
	अगर (!IS_ENABLED(CONFIG_HOTPLUG_CPU)) अणु
		atomic_set(&per_cpu(cpu_hotplug_state, cpu), CPU_UP_PREPARE);
		वापस 0;
	पूर्ण

	चयन (atomic_पढ़ो(&per_cpu(cpu_hotplug_state, cpu))) अणु

	हाल CPU_POST_DEAD:

		/* The CPU died properly, so just start it up again. */
		atomic_set(&per_cpu(cpu_hotplug_state, cpu), CPU_UP_PREPARE);
		वापस 0;

	हाल CPU_DEAD_FROZEN:

		/*
		 * Timeout during CPU death, so let caller know.
		 * The outgoing CPU completed its processing, but after
		 * cpu_रुको_death() समयd out and reported the error. The
		 * caller is मुक्त to proceed, in which हाल the state
		 * will be reset properly by cpu_set_state_online().
		 * Proceeding despite this -EBUSY वापस makes sense
		 * क्रम प्रणालीs where the outgoing CPUs take themselves
		 * offline, with no post-death manipulation required from
		 * a surviving CPU.
		 */
		वापस -EBUSY;

	हाल CPU_BROKEN:

		/*
		 * The most likely reason we got here is that there was
		 * a समयout during CPU death, and the outgoing CPU never
		 * did complete its processing.  This could happen on
		 * a भवized प्रणाली अगर the outgoing VCPU माला_लो preempted
		 * क्रम more than five seconds, and the user attempts to
		 * immediately online that same CPU.  Trying again later
		 * might वापस -EBUSY above, hence -EAGAIN.
		 */
		वापस -EAGAIN;

	शेष:

		/* Should not happen.  Famous last words. */
		वापस -EIO;
	पूर्ण
पूर्ण

/*
 * Mark the specअगरied CPU online.
 *
 * Note that it is permissible to omit this call entirely, as is
 * करोne in architectures that करो no CPU-hotplug error checking.
 */
व्योम cpu_set_state_online(पूर्णांक cpu)
अणु
	(व्योम)atomic_xchg(&per_cpu(cpu_hotplug_state, cpu), CPU_ONLINE);
पूर्ण

#अगर_घोषित CONFIG_HOTPLUG_CPU

/*
 * Wait क्रम the specअगरied CPU to निकास the idle loop and die.
 */
bool cpu_रुको_death(अचिन्हित पूर्णांक cpu, पूर्णांक seconds)
अणु
	पूर्णांक jf_left = seconds * HZ;
	पूर्णांक oldstate;
	bool ret = true;
	पूर्णांक sleep_jf = 1;

	might_sleep();

	/* The outgoing CPU will normally get करोne quite quickly. */
	अगर (atomic_पढ़ो(&per_cpu(cpu_hotplug_state, cpu)) == CPU_DEAD)
		जाओ update_state;
	udelay(5);

	/* But अगर the outgoing CPU dawdles, रुको increasingly दीर्घ बार. */
	जबतक (atomic_पढ़ो(&per_cpu(cpu_hotplug_state, cpu)) != CPU_DEAD) अणु
		schedule_समयout_unपूर्णांकerruptible(sleep_jf);
		jf_left -= sleep_jf;
		अगर (jf_left <= 0)
			अवरोध;
		sleep_jf = DIV_ROUND_UP(sleep_jf * 11, 10);
	पूर्ण
update_state:
	oldstate = atomic_पढ़ो(&per_cpu(cpu_hotplug_state, cpu));
	अगर (oldstate == CPU_DEAD) अणु
		/* Outgoing CPU died normally, update state. */
		smp_mb(); /* atomic_पढ़ो() beक्रमe update. */
		atomic_set(&per_cpu(cpu_hotplug_state, cpu), CPU_POST_DEAD);
	पूर्ण अन्यथा अणु
		/* Outgoing CPU still hasn't died, set state accordingly. */
		अगर (atomic_cmpxchg(&per_cpu(cpu_hotplug_state, cpu),
				   oldstate, CPU_BROKEN) != oldstate)
			जाओ update_state;
		ret = false;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Called by the outgoing CPU to report its successful death.  Return
 * false अगर this report follows the surviving CPU's timing out.
 *
 * A separate "CPU_DEAD_FROZEN" is used when the surviving CPU
 * समयd out.  This approach allows architectures to omit calls to
 * cpu_check_up_prepare() and cpu_set_state_online() without defeating
 * the next cpu_रुको_death()'s polling loop.
 */
bool cpu_report_death(व्योम)
अणु
	पूर्णांक oldstate;
	पूर्णांक newstate;
	पूर्णांक cpu = smp_processor_id();

	करो अणु
		oldstate = atomic_पढ़ो(&per_cpu(cpu_hotplug_state, cpu));
		अगर (oldstate != CPU_BROKEN)
			newstate = CPU_DEAD;
		अन्यथा
			newstate = CPU_DEAD_FROZEN;
	पूर्ण जबतक (atomic_cmpxchg(&per_cpu(cpu_hotplug_state, cpu),
				oldstate, newstate) != oldstate);
	वापस newstate == CPU_DEAD;
पूर्ण

#पूर्ण_अगर /* #अगर_घोषित CONFIG_HOTPLUG_CPU */
