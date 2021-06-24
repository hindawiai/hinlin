<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  kernel/sched/cpudl.c
 *
 *  Global CPU deadline management
 *
 *  Author: Juri Lelli <j.lelli@sssup.it>
 */
#समावेश "sched.h"

अटल अंतरभूत पूर्णांक parent(पूर्णांक i)
अणु
	वापस (i - 1) >> 1;
पूर्ण

अटल अंतरभूत पूर्णांक left_child(पूर्णांक i)
अणु
	वापस (i << 1) + 1;
पूर्ण

अटल अंतरभूत पूर्णांक right_child(पूर्णांक i)
अणु
	वापस (i << 1) + 2;
पूर्ण

अटल व्योम cpudl_heapअगरy_करोwn(काष्ठा cpudl *cp, पूर्णांक idx)
अणु
	पूर्णांक l, r, largest;

	पूर्णांक orig_cpu = cp->elements[idx].cpu;
	u64 orig_dl = cp->elements[idx].dl;

	अगर (left_child(idx) >= cp->size)
		वापस;

	/* adapted from lib/prio_heap.c */
	जबतक (1) अणु
		u64 largest_dl;

		l = left_child(idx);
		r = right_child(idx);
		largest = idx;
		largest_dl = orig_dl;

		अगर ((l < cp->size) && dl_समय_beक्रमe(orig_dl,
						cp->elements[l].dl)) अणु
			largest = l;
			largest_dl = cp->elements[l].dl;
		पूर्ण
		अगर ((r < cp->size) && dl_समय_beक्रमe(largest_dl,
						cp->elements[r].dl))
			largest = r;

		अगर (largest == idx)
			अवरोध;

		/* pull largest child onto idx */
		cp->elements[idx].cpu = cp->elements[largest].cpu;
		cp->elements[idx].dl = cp->elements[largest].dl;
		cp->elements[cp->elements[idx].cpu].idx = idx;
		idx = largest;
	पूर्ण
	/* actual push करोwn of saved original values orig_* */
	cp->elements[idx].cpu = orig_cpu;
	cp->elements[idx].dl = orig_dl;
	cp->elements[cp->elements[idx].cpu].idx = idx;
पूर्ण

अटल व्योम cpudl_heapअगरy_up(काष्ठा cpudl *cp, पूर्णांक idx)
अणु
	पूर्णांक p;

	पूर्णांक orig_cpu = cp->elements[idx].cpu;
	u64 orig_dl = cp->elements[idx].dl;

	अगर (idx == 0)
		वापस;

	करो अणु
		p = parent(idx);
		अगर (dl_समय_beक्रमe(orig_dl, cp->elements[p].dl))
			अवरोध;
		/* pull parent onto idx */
		cp->elements[idx].cpu = cp->elements[p].cpu;
		cp->elements[idx].dl = cp->elements[p].dl;
		cp->elements[cp->elements[idx].cpu].idx = idx;
		idx = p;
	पूर्ण जबतक (idx != 0);
	/* actual push up of saved original values orig_* */
	cp->elements[idx].cpu = orig_cpu;
	cp->elements[idx].dl = orig_dl;
	cp->elements[cp->elements[idx].cpu].idx = idx;
पूर्ण

अटल व्योम cpudl_heapअगरy(काष्ठा cpudl *cp, पूर्णांक idx)
अणु
	अगर (idx > 0 && dl_समय_beक्रमe(cp->elements[parent(idx)].dl,
				cp->elements[idx].dl))
		cpudl_heapअगरy_up(cp, idx);
	अन्यथा
		cpudl_heapअगरy_करोwn(cp, idx);
पूर्ण

अटल अंतरभूत पूर्णांक cpudl_maximum(काष्ठा cpudl *cp)
अणु
	वापस cp->elements[0].cpu;
पूर्ण

/*
 * cpudl_find - find the best (later-dl) CPU in the प्रणाली
 * @cp: the cpudl max-heap context
 * @p: the task
 * @later_mask: a mask to fill in with the selected CPUs (or शून्य)
 *
 * Returns: पूर्णांक - CPUs were found
 */
पूर्णांक cpudl_find(काष्ठा cpudl *cp, काष्ठा task_काष्ठा *p,
	       काष्ठा cpumask *later_mask)
अणु
	स्थिर काष्ठा sched_dl_entity *dl_se = &p->dl;

	अगर (later_mask &&
	    cpumask_and(later_mask, cp->मुक्त_cpus, &p->cpus_mask)) अणु
		अचिन्हित दीर्घ cap, max_cap = 0;
		पूर्णांक cpu, max_cpu = -1;

		अगर (!अटल_branch_unlikely(&sched_asym_cpucapacity))
			वापस 1;

		/* Ensure the capacity of the CPUs fits the task. */
		क्रम_each_cpu(cpu, later_mask) अणु
			अगर (!dl_task_fits_capacity(p, cpu)) अणु
				cpumask_clear_cpu(cpu, later_mask);

				cap = capacity_orig_of(cpu);

				अगर (cap > max_cap ||
				    (cpu == task_cpu(p) && cap == max_cap)) अणु
					max_cap = cap;
					max_cpu = cpu;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (cpumask_empty(later_mask))
			cpumask_set_cpu(max_cpu, later_mask);

		वापस 1;
	पूर्ण अन्यथा अणु
		पूर्णांक best_cpu = cpudl_maximum(cp);

		WARN_ON(best_cpu != -1 && !cpu_present(best_cpu));

		अगर (cpumask_test_cpu(best_cpu, &p->cpus_mask) &&
		    dl_समय_beक्रमe(dl_se->deadline, cp->elements[0].dl)) अणु
			अगर (later_mask)
				cpumask_set_cpu(best_cpu, later_mask);

			वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * cpudl_clear - हटाओ a CPU from the cpudl max-heap
 * @cp: the cpudl max-heap context
 * @cpu: the target CPU
 *
 * Notes: assumes cpu_rq(cpu)->lock is locked
 *
 * Returns: (व्योम)
 */
व्योम cpudl_clear(काष्ठा cpudl *cp, पूर्णांक cpu)
अणु
	पूर्णांक old_idx, new_cpu;
	अचिन्हित दीर्घ flags;

	WARN_ON(!cpu_present(cpu));

	raw_spin_lock_irqsave(&cp->lock, flags);

	old_idx = cp->elements[cpu].idx;
	अगर (old_idx == IDX_INVALID) अणु
		/*
		 * Nothing to हटाओ अगर old_idx was invalid.
		 * This could happen अगर a rq_offline_dl is
		 * called क्रम a CPU without -dl tasks running.
		 */
	पूर्ण अन्यथा अणु
		new_cpu = cp->elements[cp->size - 1].cpu;
		cp->elements[old_idx].dl = cp->elements[cp->size - 1].dl;
		cp->elements[old_idx].cpu = new_cpu;
		cp->size--;
		cp->elements[new_cpu].idx = old_idx;
		cp->elements[cpu].idx = IDX_INVALID;
		cpudl_heapअगरy(cp, old_idx);

		cpumask_set_cpu(cpu, cp->मुक्त_cpus);
	पूर्ण
	raw_spin_unlock_irqrestore(&cp->lock, flags);
पूर्ण

/*
 * cpudl_set - update the cpudl max-heap
 * @cp: the cpudl max-heap context
 * @cpu: the target CPU
 * @dl: the new earliest deadline क्रम this CPU
 *
 * Notes: assumes cpu_rq(cpu)->lock is locked
 *
 * Returns: (व्योम)
 */
व्योम cpudl_set(काष्ठा cpudl *cp, पूर्णांक cpu, u64 dl)
अणु
	पूर्णांक old_idx;
	अचिन्हित दीर्घ flags;

	WARN_ON(!cpu_present(cpu));

	raw_spin_lock_irqsave(&cp->lock, flags);

	old_idx = cp->elements[cpu].idx;
	अगर (old_idx == IDX_INVALID) अणु
		पूर्णांक new_idx = cp->size++;

		cp->elements[new_idx].dl = dl;
		cp->elements[new_idx].cpu = cpu;
		cp->elements[cpu].idx = new_idx;
		cpudl_heapअगरy_up(cp, new_idx);
		cpumask_clear_cpu(cpu, cp->मुक्त_cpus);
	पूर्ण अन्यथा अणु
		cp->elements[old_idx].dl = dl;
		cpudl_heapअगरy(cp, old_idx);
	पूर्ण

	raw_spin_unlock_irqrestore(&cp->lock, flags);
पूर्ण

/*
 * cpudl_set_मुक्तcpu - Set the cpudl.मुक्त_cpus
 * @cp: the cpudl max-heap context
 * @cpu: rd attached CPU
 */
व्योम cpudl_set_मुक्तcpu(काष्ठा cpudl *cp, पूर्णांक cpu)
अणु
	cpumask_set_cpu(cpu, cp->मुक्त_cpus);
पूर्ण

/*
 * cpudl_clear_मुक्तcpu - Clear the cpudl.मुक्त_cpus
 * @cp: the cpudl max-heap context
 * @cpu: rd attached CPU
 */
व्योम cpudl_clear_मुक्तcpu(काष्ठा cpudl *cp, पूर्णांक cpu)
अणु
	cpumask_clear_cpu(cpu, cp->मुक्त_cpus);
पूर्ण

/*
 * cpudl_init - initialize the cpudl काष्ठाure
 * @cp: the cpudl max-heap context
 */
पूर्णांक cpudl_init(काष्ठा cpudl *cp)
अणु
	पूर्णांक i;

	raw_spin_lock_init(&cp->lock);
	cp->size = 0;

	cp->elements = kसुस्मृति(nr_cpu_ids,
			       माप(काष्ठा cpudl_item),
			       GFP_KERNEL);
	अगर (!cp->elements)
		वापस -ENOMEM;

	अगर (!zalloc_cpumask_var(&cp->मुक्त_cpus, GFP_KERNEL)) अणु
		kमुक्त(cp->elements);
		वापस -ENOMEM;
	पूर्ण

	क्रम_each_possible_cpu(i)
		cp->elements[i].idx = IDX_INVALID;

	वापस 0;
पूर्ण

/*
 * cpudl_cleanup - clean up the cpudl काष्ठाure
 * @cp: the cpudl max-heap context
 */
व्योम cpudl_cleanup(काष्ठा cpudl *cp)
अणु
	मुक्त_cpumask_var(cp->मुक्त_cpus);
	kमुक्त(cp->elements);
पूर्ण
