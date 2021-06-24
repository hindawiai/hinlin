<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * padata.c - generic पूर्णांकerface to process data streams in parallel
 *
 * See Documentation/core-api/padata.rst क्रम more inक्रमmation.
 *
 * Copyright (C) 2008, 2009 secunet Security Networks AG
 * Copyright (C) 2008, 2009 Steffen Klनिश्चित <steffen.klनिश्चित@secunet.com>
 *
 * Copyright (c) 2020 Oracle and/or its affiliates.
 * Author: Daniel Jordan <daniel.m.jordan@oracle.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 *
 * You should have received a copy of the GNU General Public License aदीर्घ with
 * this program; अगर not, ग_लिखो to the Free Software Foundation, Inc.,
 * 51 Franklin St - Fअगरth Floor, Boston, MA 02110-1301 USA.
 */

#समावेश <linux/completion.h>
#समावेश <linux/export.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/err.h>
#समावेश <linux/cpu.h>
#समावेश <linux/padata.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/rcupdate.h>

#घोषणा	PADATA_WORK_ONSTACK	1	/* Work's memory is on stack */

काष्ठा padata_work अणु
	काष्ठा work_काष्ठा	pw_work;
	काष्ठा list_head	pw_list;  /* padata_मुक्त_works linkage */
	व्योम			*pw_data;
पूर्ण;

अटल DEFINE_SPINLOCK(padata_works_lock);
अटल काष्ठा padata_work *padata_works;
अटल LIST_HEAD(padata_मुक्त_works);

काष्ठा padata_mt_job_state अणु
	spinlock_t		lock;
	काष्ठा completion	completion;
	काष्ठा padata_mt_job	*job;
	पूर्णांक			nworks;
	पूर्णांक			nworks_fini;
	अचिन्हित दीर्घ		chunk_size;
पूर्ण;

अटल व्योम padata_मुक्त_pd(काष्ठा parallel_data *pd);
अटल व्योम __init padata_mt_helper(काष्ठा work_काष्ठा *work);

अटल पूर्णांक padata_index_to_cpu(काष्ठा parallel_data *pd, पूर्णांक cpu_index)
अणु
	पूर्णांक cpu, target_cpu;

	target_cpu = cpumask_first(pd->cpumask.pcpu);
	क्रम (cpu = 0; cpu < cpu_index; cpu++)
		target_cpu = cpumask_next(target_cpu, pd->cpumask.pcpu);

	वापस target_cpu;
पूर्ण

अटल पूर्णांक padata_cpu_hash(काष्ठा parallel_data *pd, अचिन्हित पूर्णांक seq_nr)
अणु
	/*
	 * Hash the sequence numbers to the cpus by taking
	 * seq_nr mod. number of cpus in use.
	 */
	पूर्णांक cpu_index = seq_nr % cpumask_weight(pd->cpumask.pcpu);

	वापस padata_index_to_cpu(pd, cpu_index);
पूर्ण

अटल काष्ठा padata_work *padata_work_alloc(व्योम)
अणु
	काष्ठा padata_work *pw;

	lockdep_निश्चित_held(&padata_works_lock);

	अगर (list_empty(&padata_मुक्त_works))
		वापस शून्य;	/* No more work items allowed to be queued. */

	pw = list_first_entry(&padata_मुक्त_works, काष्ठा padata_work, pw_list);
	list_del(&pw->pw_list);
	वापस pw;
पूर्ण

अटल व्योम padata_work_init(काष्ठा padata_work *pw, work_func_t work_fn,
			     व्योम *data, पूर्णांक flags)
अणु
	अगर (flags & PADATA_WORK_ONSTACK)
		INIT_WORK_ONSTACK(&pw->pw_work, work_fn);
	अन्यथा
		INIT_WORK(&pw->pw_work, work_fn);
	pw->pw_data = data;
पूर्ण

अटल पूर्णांक __init padata_work_alloc_mt(पूर्णांक nworks, व्योम *data,
				       काष्ठा list_head *head)
अणु
	पूर्णांक i;

	spin_lock(&padata_works_lock);
	/* Start at 1 because the current task participates in the job. */
	क्रम (i = 1; i < nworks; ++i) अणु
		काष्ठा padata_work *pw = padata_work_alloc();

		अगर (!pw)
			अवरोध;
		padata_work_init(pw, padata_mt_helper, data, 0);
		list_add(&pw->pw_list, head);
	पूर्ण
	spin_unlock(&padata_works_lock);

	वापस i;
पूर्ण

अटल व्योम padata_work_मुक्त(काष्ठा padata_work *pw)
अणु
	lockdep_निश्चित_held(&padata_works_lock);
	list_add(&pw->pw_list, &padata_मुक्त_works);
पूर्ण

अटल व्योम __init padata_works_मुक्त(काष्ठा list_head *works)
अणु
	काष्ठा padata_work *cur, *next;

	अगर (list_empty(works))
		वापस;

	spin_lock(&padata_works_lock);
	list_क्रम_each_entry_safe(cur, next, works, pw_list) अणु
		list_del(&cur->pw_list);
		padata_work_मुक्त(cur);
	पूर्ण
	spin_unlock(&padata_works_lock);
पूर्ण

अटल व्योम padata_parallel_worker(काष्ठा work_काष्ठा *parallel_work)
अणु
	काष्ठा padata_work *pw = container_of(parallel_work, काष्ठा padata_work,
					      pw_work);
	काष्ठा padata_priv *padata = pw->pw_data;

	local_bh_disable();
	padata->parallel(padata);
	spin_lock(&padata_works_lock);
	padata_work_मुक्त(pw);
	spin_unlock(&padata_works_lock);
	local_bh_enable();
पूर्ण

/**
 * padata_करो_parallel - padata parallelization function
 *
 * @ps: padatashell
 * @padata: object to be parallelized
 * @cb_cpu: poपूर्णांकer to the CPU that the serialization callback function should
 *          run on.  If it's not in the serial cpumask of @pinst
 *          (i.e. cpumask.cbcpu), this function selects a fallback CPU and अगर
 *          none found, वापसs -EINVAL.
 *
 * The parallelization callback function will run with BHs off.
 * Note: Every object which is parallelized by padata_करो_parallel
 * must be seen by padata_करो_serial.
 *
 * Return: 0 on success or अन्यथा negative error code.
 */
पूर्णांक padata_करो_parallel(काष्ठा padata_shell *ps,
		       काष्ठा padata_priv *padata, पूर्णांक *cb_cpu)
अणु
	काष्ठा padata_instance *pinst = ps->pinst;
	पूर्णांक i, cpu, cpu_index, err;
	काष्ठा parallel_data *pd;
	काष्ठा padata_work *pw;

	rcu_पढ़ो_lock_bh();

	pd = rcu_dereference_bh(ps->pd);

	err = -EINVAL;
	अगर (!(pinst->flags & PADATA_INIT) || pinst->flags & PADATA_INVALID)
		जाओ out;

	अगर (!cpumask_test_cpu(*cb_cpu, pd->cpumask.cbcpu)) अणु
		अगर (!cpumask_weight(pd->cpumask.cbcpu))
			जाओ out;

		/* Select an alternate fallback CPU and notअगरy the caller. */
		cpu_index = *cb_cpu % cpumask_weight(pd->cpumask.cbcpu);

		cpu = cpumask_first(pd->cpumask.cbcpu);
		क्रम (i = 0; i < cpu_index; i++)
			cpu = cpumask_next(cpu, pd->cpumask.cbcpu);

		*cb_cpu = cpu;
	पूर्ण

	err =  -EBUSY;
	अगर ((pinst->flags & PADATA_RESET))
		जाओ out;

	atomic_inc(&pd->refcnt);
	padata->pd = pd;
	padata->cb_cpu = *cb_cpu;

	spin_lock(&padata_works_lock);
	padata->seq_nr = ++pd->seq_nr;
	pw = padata_work_alloc();
	spin_unlock(&padata_works_lock);

	rcu_पढ़ो_unlock_bh();

	अगर (pw) अणु
		padata_work_init(pw, padata_parallel_worker, padata, 0);
		queue_work(pinst->parallel_wq, &pw->pw_work);
	पूर्ण अन्यथा अणु
		/* Maximum works limit exceeded, run in the current task. */
		padata->parallel(padata);
	पूर्ण

	वापस 0;
out:
	rcu_पढ़ो_unlock_bh();

	वापस err;
पूर्ण
EXPORT_SYMBOL(padata_करो_parallel);

/*
 * padata_find_next - Find the next object that needs serialization.
 *
 * Return:
 * * A poपूर्णांकer to the control काष्ठा of the next object that needs
 *   serialization, अगर present in one of the percpu reorder queues.
 * * शून्य, अगर the next object that needs serialization will
 *   be parallel processed by another cpu and is not yet present in
 *   the cpu's reorder queue.
 */
अटल काष्ठा padata_priv *padata_find_next(काष्ठा parallel_data *pd,
					    bool हटाओ_object)
अणु
	काष्ठा padata_priv *padata;
	काष्ठा padata_list *reorder;
	पूर्णांक cpu = pd->cpu;

	reorder = per_cpu_ptr(pd->reorder_list, cpu);

	spin_lock(&reorder->lock);
	अगर (list_empty(&reorder->list)) अणु
		spin_unlock(&reorder->lock);
		वापस शून्य;
	पूर्ण

	padata = list_entry(reorder->list.next, काष्ठा padata_priv, list);

	/*
	 * Checks the rare हाल where two or more parallel jobs have hashed to
	 * the same CPU and one of the later ones finishes first.
	 */
	अगर (padata->seq_nr != pd->processed) अणु
		spin_unlock(&reorder->lock);
		वापस शून्य;
	पूर्ण

	अगर (हटाओ_object) अणु
		list_del_init(&padata->list);
		++pd->processed;
		pd->cpu = cpumask_next_wrap(cpu, pd->cpumask.pcpu, -1, false);
	पूर्ण

	spin_unlock(&reorder->lock);
	वापस padata;
पूर्ण

अटल व्योम padata_reorder(काष्ठा parallel_data *pd)
अणु
	काष्ठा padata_instance *pinst = pd->ps->pinst;
	पूर्णांक cb_cpu;
	काष्ठा padata_priv *padata;
	काष्ठा padata_serial_queue *squeue;
	काष्ठा padata_list *reorder;

	/*
	 * We need to ensure that only one cpu can work on dequeueing of
	 * the reorder queue the समय. Calculating in which percpu reorder
	 * queue the next object will arrive takes some समय. A spinlock
	 * would be highly contended. Also it is not clear in which order
	 * the objects arrive to the reorder queues. So a cpu could रुको to
	 * get the lock just to notice that there is nothing to करो at the
	 * moment. Thereक्रमe we use a trylock and let the holder of the lock
	 * care क्रम all the objects enqueued during the holdसमय of the lock.
	 */
	अगर (!spin_trylock_bh(&pd->lock))
		वापस;

	जबतक (1) अणु
		padata = padata_find_next(pd, true);

		/*
		 * If the next object that needs serialization is parallel
		 * processed by another cpu and is still on it's way to the
		 * cpu's reorder queue, nothing to करो क्रम now.
		 */
		अगर (!padata)
			अवरोध;

		cb_cpu = padata->cb_cpu;
		squeue = per_cpu_ptr(pd->squeue, cb_cpu);

		spin_lock(&squeue->serial.lock);
		list_add_tail(&padata->list, &squeue->serial.list);
		spin_unlock(&squeue->serial.lock);

		queue_work_on(cb_cpu, pinst->serial_wq, &squeue->work);
	पूर्ण

	spin_unlock_bh(&pd->lock);

	/*
	 * The next object that needs serialization might have arrived to
	 * the reorder queues in the meanसमय.
	 *
	 * Ensure reorder queue is पढ़ो after pd->lock is dropped so we see
	 * new objects from another task in padata_करो_serial.  Pairs with
	 * smp_mb in padata_करो_serial.
	 */
	smp_mb();

	reorder = per_cpu_ptr(pd->reorder_list, pd->cpu);
	अगर (!list_empty(&reorder->list) && padata_find_next(pd, false))
		queue_work(pinst->serial_wq, &pd->reorder_work);
पूर्ण

अटल व्योम invoke_padata_reorder(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा parallel_data *pd;

	local_bh_disable();
	pd = container_of(work, काष्ठा parallel_data, reorder_work);
	padata_reorder(pd);
	local_bh_enable();
पूर्ण

अटल व्योम padata_serial_worker(काष्ठा work_काष्ठा *serial_work)
अणु
	काष्ठा padata_serial_queue *squeue;
	काष्ठा parallel_data *pd;
	LIST_HEAD(local_list);
	पूर्णांक cnt;

	local_bh_disable();
	squeue = container_of(serial_work, काष्ठा padata_serial_queue, work);
	pd = squeue->pd;

	spin_lock(&squeue->serial.lock);
	list_replace_init(&squeue->serial.list, &local_list);
	spin_unlock(&squeue->serial.lock);

	cnt = 0;

	जबतक (!list_empty(&local_list)) अणु
		काष्ठा padata_priv *padata;

		padata = list_entry(local_list.next,
				    काष्ठा padata_priv, list);

		list_del_init(&padata->list);

		padata->serial(padata);
		cnt++;
	पूर्ण
	local_bh_enable();

	अगर (atomic_sub_and_test(cnt, &pd->refcnt))
		padata_मुक्त_pd(pd);
पूर्ण

/**
 * padata_करो_serial - padata serialization function
 *
 * @padata: object to be serialized.
 *
 * padata_करो_serial must be called क्रम every parallelized object.
 * The serialization callback function will run with BHs off.
 */
व्योम padata_करो_serial(काष्ठा padata_priv *padata)
अणु
	काष्ठा parallel_data *pd = padata->pd;
	पूर्णांक hashed_cpu = padata_cpu_hash(pd, padata->seq_nr);
	काष्ठा padata_list *reorder = per_cpu_ptr(pd->reorder_list, hashed_cpu);
	काष्ठा padata_priv *cur;

	spin_lock(&reorder->lock);
	/* Sort in ascending order of sequence number. */
	list_क्रम_each_entry_reverse(cur, &reorder->list, list)
		अगर (cur->seq_nr < padata->seq_nr)
			अवरोध;
	list_add(&padata->list, &cur->list);
	spin_unlock(&reorder->lock);

	/*
	 * Ensure the addition to the reorder list is ordered correctly
	 * with the trylock of pd->lock in padata_reorder.  Pairs with smp_mb
	 * in padata_reorder.
	 */
	smp_mb();

	padata_reorder(pd);
पूर्ण
EXPORT_SYMBOL(padata_करो_serial);

अटल पूर्णांक padata_setup_cpumasks(काष्ठा padata_instance *pinst)
अणु
	काष्ठा workqueue_attrs *attrs;
	पूर्णांक err;

	attrs = alloc_workqueue_attrs();
	अगर (!attrs)
		वापस -ENOMEM;

	/* Restrict parallel_wq workers to pd->cpumask.pcpu. */
	cpumask_copy(attrs->cpumask, pinst->cpumask.pcpu);
	err = apply_workqueue_attrs(pinst->parallel_wq, attrs);
	मुक्त_workqueue_attrs(attrs);

	वापस err;
पूर्ण

अटल व्योम __init padata_mt_helper(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा padata_work *pw = container_of(w, काष्ठा padata_work, pw_work);
	काष्ठा padata_mt_job_state *ps = pw->pw_data;
	काष्ठा padata_mt_job *job = ps->job;
	bool करोne;

	spin_lock(&ps->lock);

	जबतक (job->size > 0) अणु
		अचिन्हित दीर्घ start, size, end;

		start = job->start;
		/* So end is chunk size aligned अगर enough work reमुख्यs. */
		size = roundup(start + 1, ps->chunk_size) - start;
		size = min(size, job->size);
		end = start + size;

		job->start = end;
		job->size -= size;

		spin_unlock(&ps->lock);
		job->thपढ़ो_fn(start, end, job->fn_arg);
		spin_lock(&ps->lock);
	पूर्ण

	++ps->nworks_fini;
	करोne = (ps->nworks_fini == ps->nworks);
	spin_unlock(&ps->lock);

	अगर (करोne)
		complete(&ps->completion);
पूर्ण

/**
 * padata_करो_multithपढ़ोed - run a multithपढ़ोed job
 * @job: Description of the job.
 *
 * See the definition of काष्ठा padata_mt_job क्रम more details.
 */
व्योम __init padata_करो_multithपढ़ोed(काष्ठा padata_mt_job *job)
अणु
	/* In हाल thपढ़ोs finish at dअगरferent बार. */
	अटल स्थिर अचिन्हित दीर्घ load_balance_factor = 4;
	काष्ठा padata_work my_work, *pw;
	काष्ठा padata_mt_job_state ps;
	LIST_HEAD(works);
	पूर्णांक nworks;

	अगर (job->size == 0)
		वापस;

	/* Ensure at least one thपढ़ो when size < min_chunk. */
	nworks = max(job->size / job->min_chunk, 1ul);
	nworks = min(nworks, job->max_thपढ़ोs);

	अगर (nworks == 1) अणु
		/* Single thपढ़ो, no coordination needed, cut to the chase. */
		job->thपढ़ो_fn(job->start, job->start + job->size, job->fn_arg);
		वापस;
	पूर्ण

	spin_lock_init(&ps.lock);
	init_completion(&ps.completion);
	ps.job	       = job;
	ps.nworks      = padata_work_alloc_mt(nworks, &ps, &works);
	ps.nworks_fini = 0;

	/*
	 * Chunk size is the amount of work a helper करोes per call to the
	 * thपढ़ो function.  Load balance large jobs between thपढ़ोs by
	 * increasing the number of chunks, guarantee at least the minimum
	 * chunk size from the caller, and honor the caller's alignment.
	 */
	ps.chunk_size = job->size / (ps.nworks * load_balance_factor);
	ps.chunk_size = max(ps.chunk_size, job->min_chunk);
	ps.chunk_size = roundup(ps.chunk_size, job->align);

	list_क्रम_each_entry(pw, &works, pw_list)
		queue_work(प्रणाली_unbound_wq, &pw->pw_work);

	/* Use the current thपढ़ो, which saves starting a workqueue worker. */
	padata_work_init(&my_work, padata_mt_helper, &ps, PADATA_WORK_ONSTACK);
	padata_mt_helper(&my_work.pw_work);

	/* Wait क्रम all the helpers to finish. */
	रुको_क्रम_completion(&ps.completion);

	destroy_work_on_stack(&my_work.pw_work);
	padata_works_मुक्त(&works);
पूर्ण

अटल व्योम __padata_list_init(काष्ठा padata_list *pd_list)
अणु
	INIT_LIST_HEAD(&pd_list->list);
	spin_lock_init(&pd_list->lock);
पूर्ण

/* Initialize all percpu queues used by serial workers */
अटल व्योम padata_init_squeues(काष्ठा parallel_data *pd)
अणु
	पूर्णांक cpu;
	काष्ठा padata_serial_queue *squeue;

	क्रम_each_cpu(cpu, pd->cpumask.cbcpu) अणु
		squeue = per_cpu_ptr(pd->squeue, cpu);
		squeue->pd = pd;
		__padata_list_init(&squeue->serial);
		INIT_WORK(&squeue->work, padata_serial_worker);
	पूर्ण
पूर्ण

/* Initialize per-CPU reorder lists */
अटल व्योम padata_init_reorder_list(काष्ठा parallel_data *pd)
अणु
	पूर्णांक cpu;
	काष्ठा padata_list *list;

	क्रम_each_cpu(cpu, pd->cpumask.pcpu) अणु
		list = per_cpu_ptr(pd->reorder_list, cpu);
		__padata_list_init(list);
	पूर्ण
पूर्ण

/* Allocate and initialize the पूर्णांकernal cpumask dependend resources. */
अटल काष्ठा parallel_data *padata_alloc_pd(काष्ठा padata_shell *ps)
अणु
	काष्ठा padata_instance *pinst = ps->pinst;
	काष्ठा parallel_data *pd;

	pd = kzalloc(माप(काष्ठा parallel_data), GFP_KERNEL);
	अगर (!pd)
		जाओ err;

	pd->reorder_list = alloc_percpu(काष्ठा padata_list);
	अगर (!pd->reorder_list)
		जाओ err_मुक्त_pd;

	pd->squeue = alloc_percpu(काष्ठा padata_serial_queue);
	अगर (!pd->squeue)
		जाओ err_मुक्त_reorder_list;

	pd->ps = ps;

	अगर (!alloc_cpumask_var(&pd->cpumask.pcpu, GFP_KERNEL))
		जाओ err_मुक्त_squeue;
	अगर (!alloc_cpumask_var(&pd->cpumask.cbcpu, GFP_KERNEL))
		जाओ err_मुक्त_pcpu;

	cpumask_and(pd->cpumask.pcpu, pinst->cpumask.pcpu, cpu_online_mask);
	cpumask_and(pd->cpumask.cbcpu, pinst->cpumask.cbcpu, cpu_online_mask);

	padata_init_reorder_list(pd);
	padata_init_squeues(pd);
	pd->seq_nr = -1;
	atomic_set(&pd->refcnt, 1);
	spin_lock_init(&pd->lock);
	pd->cpu = cpumask_first(pd->cpumask.pcpu);
	INIT_WORK(&pd->reorder_work, invoke_padata_reorder);

	वापस pd;

err_मुक्त_pcpu:
	मुक्त_cpumask_var(pd->cpumask.pcpu);
err_मुक्त_squeue:
	मुक्त_percpu(pd->squeue);
err_मुक्त_reorder_list:
	मुक्त_percpu(pd->reorder_list);
err_मुक्त_pd:
	kमुक्त(pd);
err:
	वापस शून्य;
पूर्ण

अटल व्योम padata_मुक्त_pd(काष्ठा parallel_data *pd)
अणु
	मुक्त_cpumask_var(pd->cpumask.pcpu);
	मुक्त_cpumask_var(pd->cpumask.cbcpu);
	मुक्त_percpu(pd->reorder_list);
	मुक्त_percpu(pd->squeue);
	kमुक्त(pd);
पूर्ण

अटल व्योम __padata_start(काष्ठा padata_instance *pinst)
अणु
	pinst->flags |= PADATA_INIT;
पूर्ण

अटल व्योम __padata_stop(काष्ठा padata_instance *pinst)
अणु
	अगर (!(pinst->flags & PADATA_INIT))
		वापस;

	pinst->flags &= ~PADATA_INIT;

	synchronize_rcu();
पूर्ण

/* Replace the पूर्णांकernal control काष्ठाure with a new one. */
अटल पूर्णांक padata_replace_one(काष्ठा padata_shell *ps)
अणु
	काष्ठा parallel_data *pd_new;

	pd_new = padata_alloc_pd(ps);
	अगर (!pd_new)
		वापस -ENOMEM;

	ps->opd = rcu_dereference_रक्षित(ps->pd, 1);
	rcu_assign_poपूर्णांकer(ps->pd, pd_new);

	वापस 0;
पूर्ण

अटल पूर्णांक padata_replace(काष्ठा padata_instance *pinst)
अणु
	काष्ठा padata_shell *ps;
	पूर्णांक err = 0;

	pinst->flags |= PADATA_RESET;

	list_क्रम_each_entry(ps, &pinst->pslist, list) अणु
		err = padata_replace_one(ps);
		अगर (err)
			अवरोध;
	पूर्ण

	synchronize_rcu();

	list_क्रम_each_entry_जारी_reverse(ps, &pinst->pslist, list)
		अगर (atomic_dec_and_test(&ps->opd->refcnt))
			padata_मुक्त_pd(ps->opd);

	pinst->flags &= ~PADATA_RESET;

	वापस err;
पूर्ण

/* If cpumask contains no active cpu, we mark the instance as invalid. */
अटल bool padata_validate_cpumask(काष्ठा padata_instance *pinst,
				    स्थिर काष्ठा cpumask *cpumask)
अणु
	अगर (!cpumask_पूर्णांकersects(cpumask, cpu_online_mask)) अणु
		pinst->flags |= PADATA_INVALID;
		वापस false;
	पूर्ण

	pinst->flags &= ~PADATA_INVALID;
	वापस true;
पूर्ण

अटल पूर्णांक __padata_set_cpumasks(काष्ठा padata_instance *pinst,
				 cpumask_var_t pcpumask,
				 cpumask_var_t cbcpumask)
अणु
	पूर्णांक valid;
	पूर्णांक err;

	valid = padata_validate_cpumask(pinst, pcpumask);
	अगर (!valid) अणु
		__padata_stop(pinst);
		जाओ out_replace;
	पूर्ण

	valid = padata_validate_cpumask(pinst, cbcpumask);
	अगर (!valid)
		__padata_stop(pinst);

out_replace:
	cpumask_copy(pinst->cpumask.pcpu, pcpumask);
	cpumask_copy(pinst->cpumask.cbcpu, cbcpumask);

	err = padata_setup_cpumasks(pinst) ?: padata_replace(pinst);

	अगर (valid)
		__padata_start(pinst);

	वापस err;
पूर्ण

/**
 * padata_set_cpumask - Sets specअगरied by @cpumask_type cpumask to the value
 *                      equivalent to @cpumask.
 * @pinst: padata instance
 * @cpumask_type: PADATA_CPU_SERIAL or PADATA_CPU_PARALLEL corresponding
 *                to parallel and serial cpumasks respectively.
 * @cpumask: the cpumask to use
 *
 * Return: 0 on success or negative error code
 */
पूर्णांक padata_set_cpumask(काष्ठा padata_instance *pinst, पूर्णांक cpumask_type,
		       cpumask_var_t cpumask)
अणु
	काष्ठा cpumask *serial_mask, *parallel_mask;
	पूर्णांक err = -EINVAL;

	get_online_cpus();
	mutex_lock(&pinst->lock);

	चयन (cpumask_type) अणु
	हाल PADATA_CPU_PARALLEL:
		serial_mask = pinst->cpumask.cbcpu;
		parallel_mask = cpumask;
		अवरोध;
	हाल PADATA_CPU_SERIAL:
		parallel_mask = pinst->cpumask.pcpu;
		serial_mask = cpumask;
		अवरोध;
	शेष:
		 जाओ out;
	पूर्ण

	err =  __padata_set_cpumasks(pinst, parallel_mask, serial_mask);

out:
	mutex_unlock(&pinst->lock);
	put_online_cpus();

	वापस err;
पूर्ण
EXPORT_SYMBOL(padata_set_cpumask);

#अगर_घोषित CONFIG_HOTPLUG_CPU

अटल पूर्णांक __padata_add_cpu(काष्ठा padata_instance *pinst, पूर्णांक cpu)
अणु
	पूर्णांक err = 0;

	अगर (cpumask_test_cpu(cpu, cpu_online_mask)) अणु
		err = padata_replace(pinst);

		अगर (padata_validate_cpumask(pinst, pinst->cpumask.pcpu) &&
		    padata_validate_cpumask(pinst, pinst->cpumask.cbcpu))
			__padata_start(pinst);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक __padata_हटाओ_cpu(काष्ठा padata_instance *pinst, पूर्णांक cpu)
अणु
	पूर्णांक err = 0;

	अगर (!cpumask_test_cpu(cpu, cpu_online_mask)) अणु
		अगर (!padata_validate_cpumask(pinst, pinst->cpumask.pcpu) ||
		    !padata_validate_cpumask(pinst, pinst->cpumask.cbcpu))
			__padata_stop(pinst);

		err = padata_replace(pinst);
	पूर्ण

	वापस err;
पूर्ण

अटल अंतरभूत पूर्णांक pinst_has_cpu(काष्ठा padata_instance *pinst, पूर्णांक cpu)
अणु
	वापस cpumask_test_cpu(cpu, pinst->cpumask.pcpu) ||
		cpumask_test_cpu(cpu, pinst->cpumask.cbcpu);
पूर्ण

अटल पूर्णांक padata_cpu_online(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा padata_instance *pinst;
	पूर्णांक ret;

	pinst = hlist_entry_safe(node, काष्ठा padata_instance, cpu_online_node);
	अगर (!pinst_has_cpu(pinst, cpu))
		वापस 0;

	mutex_lock(&pinst->lock);
	ret = __padata_add_cpu(pinst, cpu);
	mutex_unlock(&pinst->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक padata_cpu_dead(अचिन्हित पूर्णांक cpu, काष्ठा hlist_node *node)
अणु
	काष्ठा padata_instance *pinst;
	पूर्णांक ret;

	pinst = hlist_entry_safe(node, काष्ठा padata_instance, cpu_dead_node);
	अगर (!pinst_has_cpu(pinst, cpu))
		वापस 0;

	mutex_lock(&pinst->lock);
	ret = __padata_हटाओ_cpu(pinst, cpu);
	mutex_unlock(&pinst->lock);
	वापस ret;
पूर्ण

अटल क्रमागत cpuhp_state hp_online;
#पूर्ण_अगर

अटल व्योम __padata_मुक्त(काष्ठा padata_instance *pinst)
अणु
#अगर_घोषित CONFIG_HOTPLUG_CPU
	cpuhp_state_हटाओ_instance_nocalls(CPUHP_PADATA_DEAD,
					    &pinst->cpu_dead_node);
	cpuhp_state_हटाओ_instance_nocalls(hp_online, &pinst->cpu_online_node);
#पूर्ण_अगर

	WARN_ON(!list_empty(&pinst->pslist));

	मुक्त_cpumask_var(pinst->cpumask.pcpu);
	मुक्त_cpumask_var(pinst->cpumask.cbcpu);
	destroy_workqueue(pinst->serial_wq);
	destroy_workqueue(pinst->parallel_wq);
	kमुक्त(pinst);
पूर्ण

#घोषणा kobj2pinst(_kobj)					\
	container_of(_kobj, काष्ठा padata_instance, kobj)
#घोषणा attr2pentry(_attr)					\
	container_of(_attr, काष्ठा padata_sysfs_entry, attr)

अटल व्योम padata_sysfs_release(काष्ठा kobject *kobj)
अणु
	काष्ठा padata_instance *pinst = kobj2pinst(kobj);
	__padata_मुक्त(pinst);
पूर्ण

काष्ठा padata_sysfs_entry अणु
	काष्ठा attribute attr;
	sमाप_प्रकार (*show)(काष्ठा padata_instance *, काष्ठा attribute *, अक्षर *);
	sमाप_प्रकार (*store)(काष्ठा padata_instance *, काष्ठा attribute *,
			 स्थिर अक्षर *, माप_प्रकार);
पूर्ण;

अटल sमाप_प्रकार show_cpumask(काष्ठा padata_instance *pinst,
			    काष्ठा attribute *attr,  अक्षर *buf)
अणु
	काष्ठा cpumask *cpumask;
	sमाप_प्रकार len;

	mutex_lock(&pinst->lock);
	अगर (!म_भेद(attr->name, "serial_cpumask"))
		cpumask = pinst->cpumask.cbcpu;
	अन्यथा
		cpumask = pinst->cpumask.pcpu;

	len = snम_लिखो(buf, PAGE_SIZE, "%*pb\n",
		       nr_cpu_ids, cpumask_bits(cpumask));
	mutex_unlock(&pinst->lock);
	वापस len < PAGE_SIZE ? len : -EINVAL;
पूर्ण

अटल sमाप_प्रकार store_cpumask(काष्ठा padata_instance *pinst,
			     काष्ठा attribute *attr,
			     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	cpumask_var_t new_cpumask;
	sमाप_प्रकार ret;
	पूर्णांक mask_type;

	अगर (!alloc_cpumask_var(&new_cpumask, GFP_KERNEL))
		वापस -ENOMEM;

	ret = biपंचांगap_parse(buf, count, cpumask_bits(new_cpumask),
			   nr_cpumask_bits);
	अगर (ret < 0)
		जाओ out;

	mask_type = !म_भेद(attr->name, "serial_cpumask") ?
		PADATA_CPU_SERIAL : PADATA_CPU_PARALLEL;
	ret = padata_set_cpumask(pinst, mask_type, new_cpumask);
	अगर (!ret)
		ret = count;

out:
	मुक्त_cpumask_var(new_cpumask);
	वापस ret;
पूर्ण

#घोषणा PADATA_ATTR_RW(_name, _show_name, _store_name)		\
	अटल काष्ठा padata_sysfs_entry _name##_attr =		\
		__ATTR(_name, 0644, _show_name, _store_name)
#घोषणा PADATA_ATTR_RO(_name, _show_name)		\
	अटल काष्ठा padata_sysfs_entry _name##_attr = \
		__ATTR(_name, 0400, _show_name, शून्य)

PADATA_ATTR_RW(serial_cpumask, show_cpumask, store_cpumask);
PADATA_ATTR_RW(parallel_cpumask, show_cpumask, store_cpumask);

/*
 * Padata sysfs provides the following objects:
 * serial_cpumask   [RW] - cpumask क्रम serial workers
 * parallel_cpumask [RW] - cpumask क्रम parallel workers
 */
अटल काष्ठा attribute *padata_शेष_attrs[] = अणु
	&serial_cpumask_attr.attr,
	&parallel_cpumask_attr.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(padata_शेष);

अटल sमाप_प्रकार padata_sysfs_show(काष्ठा kobject *kobj,
				 काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा padata_instance *pinst;
	काष्ठा padata_sysfs_entry *pentry;
	sमाप_प्रकार ret = -EIO;

	pinst = kobj2pinst(kobj);
	pentry = attr2pentry(attr);
	अगर (pentry->show)
		ret = pentry->show(pinst, attr, buf);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार padata_sysfs_store(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा padata_instance *pinst;
	काष्ठा padata_sysfs_entry *pentry;
	sमाप_प्रकार ret = -EIO;

	pinst = kobj2pinst(kobj);
	pentry = attr2pentry(attr);
	अगर (pentry->show)
		ret = pentry->store(pinst, attr, buf, count);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा sysfs_ops padata_sysfs_ops = अणु
	.show = padata_sysfs_show,
	.store = padata_sysfs_store,
पूर्ण;

अटल काष्ठा kobj_type padata_attr_type = अणु
	.sysfs_ops = &padata_sysfs_ops,
	.शेष_groups = padata_शेष_groups,
	.release = padata_sysfs_release,
पूर्ण;

/**
 * padata_alloc - allocate and initialize a padata instance
 * @name: used to identअगरy the instance
 *
 * Return: new instance on success, शून्य on error
 */
काष्ठा padata_instance *padata_alloc(स्थिर अक्षर *name)
अणु
	काष्ठा padata_instance *pinst;

	pinst = kzalloc(माप(काष्ठा padata_instance), GFP_KERNEL);
	अगर (!pinst)
		जाओ err;

	pinst->parallel_wq = alloc_workqueue("%s_parallel", WQ_UNBOUND, 0,
					     name);
	अगर (!pinst->parallel_wq)
		जाओ err_मुक्त_inst;

	get_online_cpus();

	pinst->serial_wq = alloc_workqueue("%s_serial", WQ_MEM_RECLAIM |
					   WQ_CPU_INTENSIVE, 1, name);
	अगर (!pinst->serial_wq)
		जाओ err_put_cpus;

	अगर (!alloc_cpumask_var(&pinst->cpumask.pcpu, GFP_KERNEL))
		जाओ err_मुक्त_serial_wq;
	अगर (!alloc_cpumask_var(&pinst->cpumask.cbcpu, GFP_KERNEL)) अणु
		मुक्त_cpumask_var(pinst->cpumask.pcpu);
		जाओ err_मुक्त_serial_wq;
	पूर्ण

	INIT_LIST_HEAD(&pinst->pslist);

	cpumask_copy(pinst->cpumask.pcpu, cpu_possible_mask);
	cpumask_copy(pinst->cpumask.cbcpu, cpu_possible_mask);

	अगर (padata_setup_cpumasks(pinst))
		जाओ err_मुक्त_masks;

	__padata_start(pinst);

	kobject_init(&pinst->kobj, &padata_attr_type);
	mutex_init(&pinst->lock);

#अगर_घोषित CONFIG_HOTPLUG_CPU
	cpuhp_state_add_instance_nocalls_cpuslocked(hp_online,
						    &pinst->cpu_online_node);
	cpuhp_state_add_instance_nocalls_cpuslocked(CPUHP_PADATA_DEAD,
						    &pinst->cpu_dead_node);
#पूर्ण_अगर

	put_online_cpus();

	वापस pinst;

err_मुक्त_masks:
	मुक्त_cpumask_var(pinst->cpumask.pcpu);
	मुक्त_cpumask_var(pinst->cpumask.cbcpu);
err_मुक्त_serial_wq:
	destroy_workqueue(pinst->serial_wq);
err_put_cpus:
	put_online_cpus();
	destroy_workqueue(pinst->parallel_wq);
err_मुक्त_inst:
	kमुक्त(pinst);
err:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(padata_alloc);

/**
 * padata_मुक्त - मुक्त a padata instance
 *
 * @pinst: padata instance to मुक्त
 */
व्योम padata_मुक्त(काष्ठा padata_instance *pinst)
अणु
	kobject_put(&pinst->kobj);
पूर्ण
EXPORT_SYMBOL(padata_मुक्त);

/**
 * padata_alloc_shell - Allocate and initialize padata shell.
 *
 * @pinst: Parent padata_instance object.
 *
 * Return: new shell on success, शून्य on error
 */
काष्ठा padata_shell *padata_alloc_shell(काष्ठा padata_instance *pinst)
अणु
	काष्ठा parallel_data *pd;
	काष्ठा padata_shell *ps;

	ps = kzalloc(माप(*ps), GFP_KERNEL);
	अगर (!ps)
		जाओ out;

	ps->pinst = pinst;

	get_online_cpus();
	pd = padata_alloc_pd(ps);
	put_online_cpus();

	अगर (!pd)
		जाओ out_मुक्त_ps;

	mutex_lock(&pinst->lock);
	RCU_INIT_POINTER(ps->pd, pd);
	list_add(&ps->list, &pinst->pslist);
	mutex_unlock(&pinst->lock);

	वापस ps;

out_मुक्त_ps:
	kमुक्त(ps);
out:
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(padata_alloc_shell);

/**
 * padata_मुक्त_shell - मुक्त a padata shell
 *
 * @ps: padata shell to मुक्त
 */
व्योम padata_मुक्त_shell(काष्ठा padata_shell *ps)
अणु
	अगर (!ps)
		वापस;

	mutex_lock(&ps->pinst->lock);
	list_del(&ps->list);
	padata_मुक्त_pd(rcu_dereference_रक्षित(ps->pd, 1));
	mutex_unlock(&ps->pinst->lock);

	kमुक्त(ps);
पूर्ण
EXPORT_SYMBOL(padata_मुक्त_shell);

व्योम __init padata_init(व्योम)
अणु
	अचिन्हित पूर्णांक i, possible_cpus;
#अगर_घोषित CONFIG_HOTPLUG_CPU
	पूर्णांक ret;

	ret = cpuhp_setup_state_multi(CPUHP_AP_ONLINE_DYN, "padata:online",
				      padata_cpu_online, शून्य);
	अगर (ret < 0)
		जाओ err;
	hp_online = ret;

	ret = cpuhp_setup_state_multi(CPUHP_PADATA_DEAD, "padata:dead",
				      शून्य, padata_cpu_dead);
	अगर (ret < 0)
		जाओ हटाओ_online_state;
#पूर्ण_अगर

	possible_cpus = num_possible_cpus();
	padata_works = kदो_स्मृति_array(possible_cpus, माप(काष्ठा padata_work),
				     GFP_KERNEL);
	अगर (!padata_works)
		जाओ हटाओ_dead_state;

	क्रम (i = 0; i < possible_cpus; ++i)
		list_add(&padata_works[i].pw_list, &padata_मुक्त_works);

	वापस;

हटाओ_dead_state:
#अगर_घोषित CONFIG_HOTPLUG_CPU
	cpuhp_हटाओ_multi_state(CPUHP_PADATA_DEAD);
हटाओ_online_state:
	cpuhp_हटाओ_multi_state(hp_online);
err:
#पूर्ण_अगर
	pr_warn("padata: initialization failed\n");
पूर्ण
