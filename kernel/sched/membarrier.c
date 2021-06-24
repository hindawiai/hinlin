<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2010-2017 Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 *
 * membarrier प्रणाली call
 */
#समावेश "sched.h"

/*
 * For करोcumentation purposes, here are some membarrier ordering
 * scenarios to keep in mind:
 *
 * A) Userspace thपढ़ो execution after IPI vs membarrier's memory
 *    barrier beक्रमe sending the IPI
 *
 * Userspace variables:
 *
 * पूर्णांक x = 0, y = 0;
 *
 * The memory barrier at the start of membarrier() on CPU0 is necessary in
 * order to enक्रमce the guarantee that any ग_लिखोs occurring on CPU0 beक्रमe
 * the membarrier() is executed will be visible to any code executing on
 * CPU1 after the IPI-induced memory barrier:
 *
 *         CPU0                              CPU1
 *
 *         x = 1
 *         membarrier():
 *           a: smp_mb()
 *           b: send IPI                       IPI-induced mb
 *           c: smp_mb()
 *         r2 = y
 *                                           y = 1
 *                                           barrier()
 *                                           r1 = x
 *
 *                     BUG_ON(r1 == 0 && r2 == 0)
 *
 * The ग_लिखो to y and load from x by CPU1 are unordered by the hardware,
 * so it's possible to have "r1 = x" reordered beक्रमe "y = 1" at any
 * poपूर्णांक after (b).  If the memory barrier at (a) is omitted, then "x = 1"
 * can be reordered after (a) (although not after (c)), so we get r1 == 0
 * and r2 == 0.  This violates the guarantee that membarrier() is
 * supposed by provide.
 *
 * The timing of the memory barrier at (a) has to ensure that it executes
 * beक्रमe the IPI-induced memory barrier on CPU1.
 *
 * B) Userspace thपढ़ो execution beक्रमe IPI vs membarrier's memory
 *    barrier after completing the IPI
 *
 * Userspace variables:
 *
 * पूर्णांक x = 0, y = 0;
 *
 * The memory barrier at the end of membarrier() on CPU0 is necessary in
 * order to enक्रमce the guarantee that any ग_लिखोs occurring on CPU1 beक्रमe
 * the membarrier() is executed will be visible to any code executing on
 * CPU0 after the membarrier():
 *
 *         CPU0                              CPU1
 *
 *                                           x = 1
 *                                           barrier()
 *                                           y = 1
 *         r2 = y
 *         membarrier():
 *           a: smp_mb()
 *           b: send IPI                       IPI-induced mb
 *           c: smp_mb()
 *         r1 = x
 *         BUG_ON(r1 == 0 && r2 == 1)
 *
 * The ग_लिखोs to x and y are unordered by the hardware, so it's possible to
 * have "r2 = 1" even though the ग_लिखो to x करोesn't execute until (b).  If
 * the memory barrier at (c) is omitted then "r1 = x" can be reordered
 * beक्रमe (b) (although not beक्रमe (a)), so we get "r1 = 0".  This violates
 * the guarantee that membarrier() is supposed to provide.
 *
 * The timing of the memory barrier at (c) has to ensure that it executes
 * after the IPI-induced memory barrier on CPU1.
 *
 * C) Scheduling userspace thपढ़ो -> kthपढ़ो -> userspace thपढ़ो vs membarrier
 *
 *           CPU0                            CPU1
 *
 *           membarrier():
 *           a: smp_mb()
 *                                           d: चयन to kthपढ़ो (includes mb)
 *           b: पढ़ो rq->curr->mm == शून्य
 *                                           e: चयन to user (includes mb)
 *           c: smp_mb()
 *
 * Using the scenario from (A), we can show that (a) needs to be paired
 * with (e). Using the scenario from (B), we can show that (c) needs to
 * be paired with (d).
 *
 * D) निकास_mm vs membarrier
 *
 * Two thपढ़ो groups are created, A and B.  Thपढ़ो group B is created by
 * issuing clone from group A with flag CLONE_VM set, but not CLONE_THREAD.
 * Let's assume we have a single thपढ़ो within each thपढ़ो group (Thपढ़ो A
 * and Thपढ़ो B).  Thपढ़ो A runs on CPU0, Thपढ़ो B runs on CPU1.
 *
 *           CPU0                            CPU1
 *
 *           membarrier():
 *             a: smp_mb()
 *                                           निकास_mm():
 *                                             d: smp_mb()
 *                                             e: current->mm = शून्य
 *             b: पढ़ो rq->curr->mm == शून्य
 *             c: smp_mb()
 *
 * Using scenario (B), we can show that (c) needs to be paired with (d).
 *
 * E) kthपढ़ो_अणुuse,unuseपूर्ण_mm vs membarrier
 *
 *           CPU0                            CPU1
 *
 *           membarrier():
 *           a: smp_mb()
 *                                           kthपढ़ो_unuse_mm()
 *                                             d: smp_mb()
 *                                             e: current->mm = शून्य
 *           b: पढ़ो rq->curr->mm == शून्य
 *                                           kthपढ़ो_use_mm()
 *                                             f: current->mm = mm
 *                                             g: smp_mb()
 *           c: smp_mb()
 *
 * Using the scenario from (A), we can show that (a) needs to be paired
 * with (g). Using the scenario from (B), we can show that (c) needs to
 * be paired with (d).
 */

/*
 * Biपंचांगask made from a "or" of all commands within क्रमागत membarrier_cmd,
 * except MEMBARRIER_CMD_QUERY.
 */
#अगर_घोषित CONFIG_ARCH_HAS_MEMBARRIER_SYNC_CORE
#घोषणा MEMBARRIER_PRIVATE_EXPEDITED_SYNC_CORE_BITMASK			\
	(MEMBARRIER_CMD_PRIVATE_EXPEDITED_SYNC_CORE			\
	| MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED_SYNC_CORE)
#अन्यथा
#घोषणा MEMBARRIER_PRIVATE_EXPEDITED_SYNC_CORE_BITMASK	0
#पूर्ण_अगर

#अगर_घोषित CONFIG_RSEQ
#घोषणा MEMBARRIER_CMD_PRIVATE_EXPEDITED_RSEQ_BITMASK		\
	(MEMBARRIER_CMD_PRIVATE_EXPEDITED_RSEQ			\
	| MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED_RSEQ_BITMASK)
#अन्यथा
#घोषणा MEMBARRIER_CMD_PRIVATE_EXPEDITED_RSEQ_BITMASK	0
#पूर्ण_अगर

#घोषणा MEMBARRIER_CMD_BITMASK						\
	(MEMBARRIER_CMD_GLOBAL | MEMBARRIER_CMD_GLOBAL_EXPEDITED	\
	| MEMBARRIER_CMD_REGISTER_GLOBAL_EXPEDITED			\
	| MEMBARRIER_CMD_PRIVATE_EXPEDITED				\
	| MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED			\
	| MEMBARRIER_PRIVATE_EXPEDITED_SYNC_CORE_BITMASK)

अटल व्योम ipi_mb(व्योम *info)
अणु
	smp_mb();	/* IPIs should be serializing but paranoid. */
पूर्ण

अटल व्योम ipi_sync_core(व्योम *info)
अणु
	/*
	 * The smp_mb() in membarrier after all the IPIs is supposed to
	 * ensure that memory on remote CPUs that occur beक्रमe the IPI
	 * become visible to membarrier()'s caller -- see scenario B in
	 * the big comment at the top of this file.
	 *
	 * A sync_core() would provide this guarantee, but
	 * sync_core_beक्रमe_usermode() might end up being deferred until
	 * after membarrier()'s smp_mb().
	 */
	smp_mb();	/* IPIs should be serializing but paranoid. */

	sync_core_beक्रमe_usermode();
पूर्ण

अटल व्योम ipi_rseq(व्योम *info)
अणु
	/*
	 * Ensure that all stores करोne by the calling thपढ़ो are visible
	 * to the current task beक्रमe the current task resumes.  We could
	 * probably optimize this away on most architectures, but by the
	 * समय we've alपढ़ोy sent an IPI, the cost of the extra smp_mb()
	 * is negligible.
	 */
	smp_mb();
	rseq_preempt(current);
पूर्ण

अटल व्योम ipi_sync_rq_state(व्योम *info)
अणु
	काष्ठा mm_काष्ठा *mm = (काष्ठा mm_काष्ठा *) info;

	अगर (current->mm != mm)
		वापस;
	this_cpu_ग_लिखो(runqueues.membarrier_state,
		       atomic_पढ़ो(&mm->membarrier_state));
	/*
	 * Issue a memory barrier after setting
	 * MEMBARRIER_STATE_GLOBAL_EXPEDITED in the current runqueue to
	 * guarantee that no memory access following registration is reordered
	 * beक्रमe registration.
	 */
	smp_mb();
पूर्ण

व्योम membarrier_exec_mmap(काष्ठा mm_काष्ठा *mm)
अणु
	/*
	 * Issue a memory barrier beक्रमe clearing membarrier_state to
	 * guarantee that no memory access prior to exec is reordered after
	 * clearing this state.
	 */
	smp_mb();
	atomic_set(&mm->membarrier_state, 0);
	/*
	 * Keep the runqueue membarrier_state in sync with this mm
	 * membarrier_state.
	 */
	this_cpu_ग_लिखो(runqueues.membarrier_state, 0);
पूर्ण

व्योम membarrier_update_current_mm(काष्ठा mm_काष्ठा *next_mm)
अणु
	काष्ठा rq *rq = this_rq();
	पूर्णांक membarrier_state = 0;

	अगर (next_mm)
		membarrier_state = atomic_पढ़ो(&next_mm->membarrier_state);
	अगर (READ_ONCE(rq->membarrier_state) == membarrier_state)
		वापस;
	WRITE_ONCE(rq->membarrier_state, membarrier_state);
पूर्ण

अटल पूर्णांक membarrier_global_expedited(व्योम)
अणु
	पूर्णांक cpu;
	cpumask_var_t पंचांगpmask;

	अगर (num_online_cpus() == 1)
		वापस 0;

	/*
	 * Matches memory barriers around rq->curr modअगरication in
	 * scheduler.
	 */
	smp_mb();	/* प्रणाली call entry is not a mb. */

	अगर (!zalloc_cpumask_var(&पंचांगpmask, GFP_KERNEL))
		वापस -ENOMEM;

	cpus_पढ़ो_lock();
	rcu_पढ़ो_lock();
	क्रम_each_online_cpu(cpu) अणु
		काष्ठा task_काष्ठा *p;

		/*
		 * Skipping the current CPU is OK even through we can be
		 * migrated at any poपूर्णांक. The current CPU, at the poपूर्णांक
		 * where we पढ़ो raw_smp_processor_id(), is ensured to
		 * be in program order with respect to the caller
		 * thपढ़ो. Thereक्रमe, we can skip this CPU from the
		 * iteration.
		 */
		अगर (cpu == raw_smp_processor_id())
			जारी;

		अगर (!(READ_ONCE(cpu_rq(cpu)->membarrier_state) &
		    MEMBARRIER_STATE_GLOBAL_EXPEDITED))
			जारी;

		/*
		 * Skip the CPU अगर it runs a kernel thपढ़ो which is not using
		 * a task mm.
		 */
		p = rcu_dereference(cpu_rq(cpu)->curr);
		अगर (!p->mm)
			जारी;

		__cpumask_set_cpu(cpu, पंचांगpmask);
	पूर्ण
	rcu_पढ़ो_unlock();

	preempt_disable();
	smp_call_function_many(पंचांगpmask, ipi_mb, शून्य, 1);
	preempt_enable();

	मुक्त_cpumask_var(पंचांगpmask);
	cpus_पढ़ो_unlock();

	/*
	 * Memory barrier on the caller thपढ़ो _after_ we finished
	 * रुकोing क्रम the last IPI. Matches memory barriers around
	 * rq->curr modअगरication in scheduler.
	 */
	smp_mb();	/* निकास from प्रणाली call is not a mb */
	वापस 0;
पूर्ण

अटल पूर्णांक membarrier_निजी_expedited(पूर्णांक flags, पूर्णांक cpu_id)
अणु
	cpumask_var_t पंचांगpmask;
	काष्ठा mm_काष्ठा *mm = current->mm;
	smp_call_func_t ipi_func = ipi_mb;

	अगर (flags == MEMBARRIER_FLAG_SYNC_CORE) अणु
		अगर (!IS_ENABLED(CONFIG_ARCH_HAS_MEMBARRIER_SYNC_CORE))
			वापस -EINVAL;
		अगर (!(atomic_पढ़ो(&mm->membarrier_state) &
		      MEMBARRIER_STATE_PRIVATE_EXPEDITED_SYNC_CORE_READY))
			वापस -EPERM;
		ipi_func = ipi_sync_core;
	पूर्ण अन्यथा अगर (flags == MEMBARRIER_FLAG_RSEQ) अणु
		अगर (!IS_ENABLED(CONFIG_RSEQ))
			वापस -EINVAL;
		अगर (!(atomic_पढ़ो(&mm->membarrier_state) &
		      MEMBARRIER_STATE_PRIVATE_EXPEDITED_RSEQ_READY))
			वापस -EPERM;
		ipi_func = ipi_rseq;
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(flags);
		अगर (!(atomic_पढ़ो(&mm->membarrier_state) &
		      MEMBARRIER_STATE_PRIVATE_EXPEDITED_READY))
			वापस -EPERM;
	पूर्ण

	अगर (flags != MEMBARRIER_FLAG_SYNC_CORE &&
	    (atomic_पढ़ो(&mm->mm_users) == 1 || num_online_cpus() == 1))
		वापस 0;

	/*
	 * Matches memory barriers around rq->curr modअगरication in
	 * scheduler.
	 */
	smp_mb();	/* प्रणाली call entry is not a mb. */

	अगर (cpu_id < 0 && !zalloc_cpumask_var(&पंचांगpmask, GFP_KERNEL))
		वापस -ENOMEM;

	cpus_पढ़ो_lock();

	अगर (cpu_id >= 0) अणु
		काष्ठा task_काष्ठा *p;

		अगर (cpu_id >= nr_cpu_ids || !cpu_online(cpu_id))
			जाओ out;
		rcu_पढ़ो_lock();
		p = rcu_dereference(cpu_rq(cpu_id)->curr);
		अगर (!p || p->mm != mm) अणु
			rcu_पढ़ो_unlock();
			जाओ out;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण अन्यथा अणु
		पूर्णांक cpu;

		rcu_पढ़ो_lock();
		क्रम_each_online_cpu(cpu) अणु
			काष्ठा task_काष्ठा *p;

			p = rcu_dereference(cpu_rq(cpu)->curr);
			अगर (p && p->mm == mm)
				__cpumask_set_cpu(cpu, पंचांगpmask);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	अगर (cpu_id >= 0) अणु
		/*
		 * smp_call_function_single() will call ipi_func() अगर cpu_id
		 * is the calling CPU.
		 */
		smp_call_function_single(cpu_id, ipi_func, शून्य, 1);
	पूर्ण अन्यथा अणु
		/*
		 * For regular membarrier, we can save a few cycles by
		 * skipping the current cpu -- we're about to करो smp_mb()
		 * below, and अगर we migrate to a dअगरferent cpu, this cpu
		 * and the new cpu will execute a full barrier in the
		 * scheduler.
		 *
		 * For SYNC_CORE, we करो need a barrier on the current cpu --
		 * otherwise, अगर we are migrated and replaced by a dअगरferent
		 * task in the same mm just beक्रमe, during, or after
		 * membarrier, we will end up with some thपढ़ो in the mm
		 * running without a core sync.
		 *
		 * For RSEQ, करोn't rseq_preempt() the caller.  User code
		 * is not supposed to issue syscalls at all from inside an
		 * rseq critical section.
		 */
		अगर (flags != MEMBARRIER_FLAG_SYNC_CORE) अणु
			preempt_disable();
			smp_call_function_many(पंचांगpmask, ipi_func, शून्य, true);
			preempt_enable();
		पूर्ण अन्यथा अणु
			on_each_cpu_mask(पंचांगpmask, ipi_func, शून्य, true);
		पूर्ण
	पूर्ण

out:
	अगर (cpu_id < 0)
		मुक्त_cpumask_var(पंचांगpmask);
	cpus_पढ़ो_unlock();

	/*
	 * Memory barrier on the caller thपढ़ो _after_ we finished
	 * रुकोing क्रम the last IPI. Matches memory barriers around
	 * rq->curr modअगरication in scheduler.
	 */
	smp_mb();	/* निकास from प्रणाली call is not a mb */

	वापस 0;
पूर्ण

अटल पूर्णांक sync_runqueues_membarrier_state(काष्ठा mm_काष्ठा *mm)
अणु
	पूर्णांक membarrier_state = atomic_पढ़ो(&mm->membarrier_state);
	cpumask_var_t पंचांगpmask;
	पूर्णांक cpu;

	अगर (atomic_पढ़ो(&mm->mm_users) == 1 || num_online_cpus() == 1) अणु
		this_cpu_ग_लिखो(runqueues.membarrier_state, membarrier_state);

		/*
		 * For single mm user, we can simply issue a memory barrier
		 * after setting MEMBARRIER_STATE_GLOBAL_EXPEDITED in the
		 * mm and in the current runqueue to guarantee that no memory
		 * access following registration is reordered beक्रमe
		 * registration.
		 */
		smp_mb();
		वापस 0;
	पूर्ण

	अगर (!zalloc_cpumask_var(&पंचांगpmask, GFP_KERNEL))
		वापस -ENOMEM;

	/*
	 * For mm with multiple users, we need to ensure all future
	 * scheduler executions will observe @mm's new membarrier
	 * state.
	 */
	synchronize_rcu();

	/*
	 * For each cpu runqueue, अगर the task's mm match @mm, ensure that all
	 * @mm's membarrier state set bits are also set in the runqueue's
	 * membarrier state. This ensures that a runqueue scheduling
	 * between thपढ़ोs which are users of @mm has its membarrier state
	 * updated.
	 */
	cpus_पढ़ो_lock();
	rcu_पढ़ो_lock();
	क्रम_each_online_cpu(cpu) अणु
		काष्ठा rq *rq = cpu_rq(cpu);
		काष्ठा task_काष्ठा *p;

		p = rcu_dereference(rq->curr);
		अगर (p && p->mm == mm)
			__cpumask_set_cpu(cpu, पंचांगpmask);
	पूर्ण
	rcu_पढ़ो_unlock();

	on_each_cpu_mask(पंचांगpmask, ipi_sync_rq_state, mm, true);

	मुक्त_cpumask_var(पंचांगpmask);
	cpus_पढ़ो_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक membarrier_रेजिस्टर_global_expedited(व्योम)
अणु
	काष्ठा task_काष्ठा *p = current;
	काष्ठा mm_काष्ठा *mm = p->mm;
	पूर्णांक ret;

	अगर (atomic_पढ़ो(&mm->membarrier_state) &
	    MEMBARRIER_STATE_GLOBAL_EXPEDITED_READY)
		वापस 0;
	atomic_or(MEMBARRIER_STATE_GLOBAL_EXPEDITED, &mm->membarrier_state);
	ret = sync_runqueues_membarrier_state(mm);
	अगर (ret)
		वापस ret;
	atomic_or(MEMBARRIER_STATE_GLOBAL_EXPEDITED_READY,
		  &mm->membarrier_state);

	वापस 0;
पूर्ण

अटल पूर्णांक membarrier_रेजिस्टर_निजी_expedited(पूर्णांक flags)
अणु
	काष्ठा task_काष्ठा *p = current;
	काष्ठा mm_काष्ठा *mm = p->mm;
	पूर्णांक पढ़ोy_state = MEMBARRIER_STATE_PRIVATE_EXPEDITED_READY,
	    set_state = MEMBARRIER_STATE_PRIVATE_EXPEDITED,
	    ret;

	अगर (flags == MEMBARRIER_FLAG_SYNC_CORE) अणु
		अगर (!IS_ENABLED(CONFIG_ARCH_HAS_MEMBARRIER_SYNC_CORE))
			वापस -EINVAL;
		पढ़ोy_state =
			MEMBARRIER_STATE_PRIVATE_EXPEDITED_SYNC_CORE_READY;
	पूर्ण अन्यथा अगर (flags == MEMBARRIER_FLAG_RSEQ) अणु
		अगर (!IS_ENABLED(CONFIG_RSEQ))
			वापस -EINVAL;
		पढ़ोy_state =
			MEMBARRIER_STATE_PRIVATE_EXPEDITED_RSEQ_READY;
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(flags);
	पूर्ण

	/*
	 * We need to consider thपढ़ोs beदीर्घing to dअगरferent thपढ़ो
	 * groups, which use the same mm. (CLONE_VM but not
	 * CLONE_THREAD).
	 */
	अगर ((atomic_पढ़ो(&mm->membarrier_state) & पढ़ोy_state) == पढ़ोy_state)
		वापस 0;
	अगर (flags & MEMBARRIER_FLAG_SYNC_CORE)
		set_state |= MEMBARRIER_STATE_PRIVATE_EXPEDITED_SYNC_CORE;
	अगर (flags & MEMBARRIER_FLAG_RSEQ)
		set_state |= MEMBARRIER_STATE_PRIVATE_EXPEDITED_RSEQ;
	atomic_or(set_state, &mm->membarrier_state);
	ret = sync_runqueues_membarrier_state(mm);
	अगर (ret)
		वापस ret;
	atomic_or(पढ़ोy_state, &mm->membarrier_state);

	वापस 0;
पूर्ण

/**
 * sys_membarrier - issue memory barriers on a set of thपढ़ोs
 * @cmd:    Takes command values defined in क्रमागत membarrier_cmd.
 * @flags:  Currently needs to be 0 क्रम all commands other than
 *          MEMBARRIER_CMD_PRIVATE_EXPEDITED_RSEQ: in the latter
 *          हाल it can be MEMBARRIER_CMD_FLAG_CPU, indicating that @cpu_id
 *          contains the CPU on which to पूर्णांकerrupt (= restart)
 *          the RSEQ critical section.
 * @cpu_id: अगर @flags == MEMBARRIER_CMD_FLAG_CPU, indicates the cpu on which
 *          RSEQ CS should be पूर्णांकerrupted (@cmd must be
 *          MEMBARRIER_CMD_PRIVATE_EXPEDITED_RSEQ).
 *
 * If this प्रणाली call is not implemented, -ENOSYS is वापसed. If the
 * command specअगरied करोes not exist, not available on the running
 * kernel, or अगर the command argument is invalid, this प्रणाली call
 * वापसs -EINVAL. For a given command, with flags argument set to 0,
 * अगर this प्रणाली call वापसs -ENOSYS or -EINVAL, it is guaranteed to
 * always वापस the same value until reboot. In addition, it can वापस
 * -ENOMEM अगर there is not enough memory available to perक्रमm the प्रणाली
 * call.
 *
 * All memory accesses perक्रमmed in program order from each targeted thपढ़ो
 * is guaranteed to be ordered with respect to sys_membarrier(). If we use
 * the semantic "barrier()" to represent a compiler barrier क्रमcing memory
 * accesses to be perक्रमmed in program order across the barrier, and
 * smp_mb() to represent explicit memory barriers क्रमcing full memory
 * ordering across the barrier, we have the following ordering table क्रम
 * each pair of barrier(), sys_membarrier() and smp_mb():
 *
 * The pair ordering is detailed as (O: ordered, X: not ordered):
 *
 *                        barrier()   smp_mb() sys_membarrier()
 *        barrier()          X           X            O
 *        smp_mb()           X           O            O
 *        sys_membarrier()   O           O            O
 */
SYSCALL_DEFINE3(membarrier, पूर्णांक, cmd, अचिन्हित पूर्णांक, flags, पूर्णांक, cpu_id)
अणु
	चयन (cmd) अणु
	हाल MEMBARRIER_CMD_PRIVATE_EXPEDITED_RSEQ:
		अगर (unlikely(flags && flags != MEMBARRIER_CMD_FLAG_CPU))
			वापस -EINVAL;
		अवरोध;
	शेष:
		अगर (unlikely(flags))
			वापस -EINVAL;
	पूर्ण

	अगर (!(flags & MEMBARRIER_CMD_FLAG_CPU))
		cpu_id = -1;

	चयन (cmd) अणु
	हाल MEMBARRIER_CMD_QUERY:
	अणु
		पूर्णांक cmd_mask = MEMBARRIER_CMD_BITMASK;

		अगर (tick_nohz_full_enabled())
			cmd_mask &= ~MEMBARRIER_CMD_GLOBAL;
		वापस cmd_mask;
	पूर्ण
	हाल MEMBARRIER_CMD_GLOBAL:
		/* MEMBARRIER_CMD_GLOBAL is not compatible with nohz_full. */
		अगर (tick_nohz_full_enabled())
			वापस -EINVAL;
		अगर (num_online_cpus() > 1)
			synchronize_rcu();
		वापस 0;
	हाल MEMBARRIER_CMD_GLOBAL_EXPEDITED:
		वापस membarrier_global_expedited();
	हाल MEMBARRIER_CMD_REGISTER_GLOBAL_EXPEDITED:
		वापस membarrier_रेजिस्टर_global_expedited();
	हाल MEMBARRIER_CMD_PRIVATE_EXPEDITED:
		वापस membarrier_निजी_expedited(0, cpu_id);
	हाल MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED:
		वापस membarrier_रेजिस्टर_निजी_expedited(0);
	हाल MEMBARRIER_CMD_PRIVATE_EXPEDITED_SYNC_CORE:
		वापस membarrier_निजी_expedited(MEMBARRIER_FLAG_SYNC_CORE, cpu_id);
	हाल MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED_SYNC_CORE:
		वापस membarrier_रेजिस्टर_निजी_expedited(MEMBARRIER_FLAG_SYNC_CORE);
	हाल MEMBARRIER_CMD_PRIVATE_EXPEDITED_RSEQ:
		वापस membarrier_निजी_expedited(MEMBARRIER_FLAG_RSEQ, cpu_id);
	हाल MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED_RSEQ:
		वापस membarrier_रेजिस्टर_निजी_expedited(MEMBARRIER_FLAG_RSEQ);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
