<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  kernel/sched/cpupri.c
 *
 *  CPU priority management
 *
 *  Copyright (C) 2007-2008 Novell
 *
 *  Author: Gregory Haskins <ghaskins@novell.com>
 *
 *  This code tracks the priority of each CPU so that global migration
 *  decisions are easy to calculate.  Each CPU can be in a state as follows:
 *
 *                 (INVALID), NORMAL, RT1, ... RT99, HIGHER
 *
 *  going from the lowest priority to the highest.  CPUs in the INVALID state
 *  are not eligible क्रम routing.  The प्रणाली मुख्यtains this state with
 *  a 2 dimensional biपंचांगap (the first क्रम priority class, the second क्रम CPUs
 *  in that class).  Thereक्रमe a typical application without affinity
 *  restrictions can find a suitable CPU with O(1) complनिकासy (e.g. two bit
 *  searches).  For tasks with affinity restrictions, the algorithm has a
 *  worst हाल complनिकासy of O(min(101, nr_करोmcpus)), though the scenario that
 *  yields the worst हाल search is fairly contrived.
 */
#समावेश "sched.h"

/*
 * p->rt_priority   p->prio   newpri   cpupri
 *
 *				  -1       -1 (CPUPRI_INVALID)
 *
 *				  99        0 (CPUPRI_NORMAL)
 *
 *		1        98       98        1
 *	      ...
 *	       49        50       50       49
 *	       50        49       49       50
 *	      ...
 *	       99         0        0       99
 *
 *				 100	  100 (CPUPRI_HIGHER)
 */
अटल पूर्णांक convert_prio(पूर्णांक prio)
अणु
	पूर्णांक cpupri;

	चयन (prio) अणु
	हाल CPUPRI_INVALID:
		cpupri = CPUPRI_INVALID;	/* -1 */
		अवरोध;

	हाल 0 ... 98:
		cpupri = MAX_RT_PRIO-1 - prio;	/* 1 ... 99 */
		अवरोध;

	हाल MAX_RT_PRIO-1:
		cpupri = CPUPRI_NORMAL;		/*  0 */
		अवरोध;

	हाल MAX_RT_PRIO:
		cpupri = CPUPRI_HIGHER;		/* 100 */
		अवरोध;
	पूर्ण

	वापस cpupri;
पूर्ण

अटल अंतरभूत पूर्णांक __cpupri_find(काष्ठा cpupri *cp, काष्ठा task_काष्ठा *p,
				काष्ठा cpumask *lowest_mask, पूर्णांक idx)
अणु
	काष्ठा cpupri_vec *vec  = &cp->pri_to_cpu[idx];
	पूर्णांक skip = 0;

	अगर (!atomic_पढ़ो(&(vec)->count))
		skip = 1;
	/*
	 * When looking at the vector, we need to पढ़ो the counter,
	 * करो a memory barrier, then पढ़ो the mask.
	 *
	 * Note: This is still all racy, but we can deal with it.
	 *  Ideally, we only want to look at masks that are set.
	 *
	 *  If a mask is not set, then the only thing wrong is that we
	 *  did a little more work than necessary.
	 *
	 *  If we पढ़ो a zero count but the mask is set, because of the
	 *  memory barriers, that can only happen when the highest prio
	 *  task क्रम a run queue has left the run queue, in which हाल,
	 *  it will be followed by a pull. If the task we are processing
	 *  fails to find a proper place to go, that pull request will
	 *  pull this task अगर the run queue is running at a lower
	 *  priority.
	 */
	smp_rmb();

	/* Need to करो the rmb क्रम every iteration */
	अगर (skip)
		वापस 0;

	अगर (cpumask_any_and(&p->cpus_mask, vec->mask) >= nr_cpu_ids)
		वापस 0;

	अगर (lowest_mask) अणु
		cpumask_and(lowest_mask, &p->cpus_mask, vec->mask);

		/*
		 * We have to ensure that we have at least one bit
		 * still set in the array, since the map could have
		 * been concurrently emptied between the first and
		 * second पढ़ोs of vec->mask.  If we hit this
		 * condition, simply act as though we never hit this
		 * priority level and जारी on.
		 */
		अगर (cpumask_empty(lowest_mask))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

पूर्णांक cpupri_find(काष्ठा cpupri *cp, काष्ठा task_काष्ठा *p,
		काष्ठा cpumask *lowest_mask)
अणु
	वापस cpupri_find_fitness(cp, p, lowest_mask, शून्य);
पूर्ण

/**
 * cpupri_find_fitness - find the best (lowest-pri) CPU in the प्रणाली
 * @cp: The cpupri context
 * @p: The task
 * @lowest_mask: A mask to fill in with selected CPUs (or शून्य)
 * @fitness_fn: A poपूर्णांकer to a function to करो custom checks whether the CPU
 *              fits a specअगरic criteria so that we only वापस those CPUs.
 *
 * Note: This function वापसs the recommended CPUs as calculated during the
 * current invocation.  By the समय the call वापसs, the CPUs may have in
 * fact changed priorities any number of बार.  While not ideal, it is not
 * an issue of correctness since the normal rebalancer logic will correct
 * any discrepancies created by racing against the uncertaपूर्णांकy of the current
 * priority configuration.
 *
 * Return: (पूर्णांक)bool - CPUs were found
 */
पूर्णांक cpupri_find_fitness(काष्ठा cpupri *cp, काष्ठा task_काष्ठा *p,
		काष्ठा cpumask *lowest_mask,
		bool (*fitness_fn)(काष्ठा task_काष्ठा *p, पूर्णांक cpu))
अणु
	पूर्णांक task_pri = convert_prio(p->prio);
	पूर्णांक idx, cpu;

	BUG_ON(task_pri >= CPUPRI_NR_PRIORITIES);

	क्रम (idx = 0; idx < task_pri; idx++) अणु

		अगर (!__cpupri_find(cp, p, lowest_mask, idx))
			जारी;

		अगर (!lowest_mask || !fitness_fn)
			वापस 1;

		/* Ensure the capacity of the CPUs fit the task */
		क्रम_each_cpu(cpu, lowest_mask) अणु
			अगर (!fitness_fn(p, cpu))
				cpumask_clear_cpu(cpu, lowest_mask);
		पूर्ण

		/*
		 * If no CPU at the current priority can fit the task
		 * जारी looking
		 */
		अगर (cpumask_empty(lowest_mask))
			जारी;

		वापस 1;
	पूर्ण

	/*
	 * If we failed to find a fitting lowest_mask, kick off a new search
	 * but without taking पूर्णांकo account any fitness criteria this समय.
	 *
	 * This rule favours honouring priority over fitting the task in the
	 * correct CPU (Capacity Awareness being the only user now).
	 * The idea is that अगर a higher priority task can run, then it should
	 * run even अगर this ends up being on unfitting CPU.
	 *
	 * The cost of this trade-off is not entirely clear and will probably
	 * be good क्रम some workloads and bad क्रम others.
	 *
	 * The मुख्य idea here is that अगर some CPUs were over-committed, we try
	 * to spपढ़ो which is what the scheduler traditionally did. Sys admins
	 * must करो proper RT planning to aव्योम overloading the प्रणाली अगर they
	 * really care.
	 */
	अगर (fitness_fn)
		वापस cpupri_find(cp, p, lowest_mask);

	वापस 0;
पूर्ण

/**
 * cpupri_set - update the CPU priority setting
 * @cp: The cpupri context
 * @cpu: The target CPU
 * @newpri: The priority (INVALID,NORMAL,RT1-RT99,HIGHER) to assign to this CPU
 *
 * Note: Assumes cpu_rq(cpu)->lock is locked
 *
 * Returns: (व्योम)
 */
व्योम cpupri_set(काष्ठा cpupri *cp, पूर्णांक cpu, पूर्णांक newpri)
अणु
	पूर्णांक *currpri = &cp->cpu_to_pri[cpu];
	पूर्णांक oldpri = *currpri;
	पूर्णांक करो_mb = 0;

	newpri = convert_prio(newpri);

	BUG_ON(newpri >= CPUPRI_NR_PRIORITIES);

	अगर (newpri == oldpri)
		वापस;

	/*
	 * If the CPU was currently mapped to a dअगरferent value, we
	 * need to map it to the new value then हटाओ the old value.
	 * Note, we must add the new value first, otherwise we risk the
	 * cpu being missed by the priority loop in cpupri_find.
	 */
	अगर (likely(newpri != CPUPRI_INVALID)) अणु
		काष्ठा cpupri_vec *vec = &cp->pri_to_cpu[newpri];

		cpumask_set_cpu(cpu, vec->mask);
		/*
		 * When adding a new vector, we update the mask first,
		 * करो a ग_लिखो memory barrier, and then update the count, to
		 * make sure the vector is visible when count is set.
		 */
		smp_mb__beक्रमe_atomic();
		atomic_inc(&(vec)->count);
		करो_mb = 1;
	पूर्ण
	अगर (likely(oldpri != CPUPRI_INVALID)) अणु
		काष्ठा cpupri_vec *vec  = &cp->pri_to_cpu[oldpri];

		/*
		 * Because the order of modअगरication of the vec->count
		 * is important, we must make sure that the update
		 * of the new prio is seen beक्रमe we decrement the
		 * old prio. This makes sure that the loop sees
		 * one or the other when we उठाओ the priority of
		 * the run queue. We करोn't care about when we lower the
		 * priority, as that will trigger an rt pull anyway.
		 *
		 * We only need to करो a memory barrier अगर we updated
		 * the new priority vec.
		 */
		अगर (करो_mb)
			smp_mb__after_atomic();

		/*
		 * When removing from the vector, we decrement the counter first
		 * करो a memory barrier and then clear the mask.
		 */
		atomic_dec(&(vec)->count);
		smp_mb__after_atomic();
		cpumask_clear_cpu(cpu, vec->mask);
	पूर्ण

	*currpri = newpri;
पूर्ण

/**
 * cpupri_init - initialize the cpupri काष्ठाure
 * @cp: The cpupri context
 *
 * Return: -ENOMEM on memory allocation failure.
 */
पूर्णांक cpupri_init(काष्ठा cpupri *cp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CPUPRI_NR_PRIORITIES; i++) अणु
		काष्ठा cpupri_vec *vec = &cp->pri_to_cpu[i];

		atomic_set(&vec->count, 0);
		अगर (!zalloc_cpumask_var(&vec->mask, GFP_KERNEL))
			जाओ cleanup;
	पूर्ण

	cp->cpu_to_pri = kसुस्मृति(nr_cpu_ids, माप(पूर्णांक), GFP_KERNEL);
	अगर (!cp->cpu_to_pri)
		जाओ cleanup;

	क्रम_each_possible_cpu(i)
		cp->cpu_to_pri[i] = CPUPRI_INVALID;

	वापस 0;

cleanup:
	क्रम (i--; i >= 0; i--)
		मुक्त_cpumask_var(cp->pri_to_cpu[i].mask);
	वापस -ENOMEM;
पूर्ण

/**
 * cpupri_cleanup - clean up the cpupri काष्ठाure
 * @cp: The cpupri context
 */
व्योम cpupri_cleanup(काष्ठा cpupri *cp)
अणु
	पूर्णांक i;

	kमुक्त(cp->cpu_to_pri);
	क्रम (i = 0; i < CPUPRI_NR_PRIORITIES; i++)
		मुक्त_cpumask_var(cp->pri_to_cpu[i].mask);
पूर्ण
