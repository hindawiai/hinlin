<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * This file contains the routines क्रम handling the MMU on those
 * PowerPC implementations where the MMU is not using the hash
 * table, such as 8xx, 4xx, BookE's etc...
 *
 * Copyright 2008 Ben Herrenschmidt <benh@kernel.crashing.org>
 *                IBM Corp.
 *
 *  Derived from previous arch/घातerpc/mm/mmu_context.c
 *  and arch/घातerpc/include/यंत्र/mmu_context.h
 *
 * TODO:
 *
 *   - The global context lock will not scale very well
 *   - The maps should be dynamically allocated to allow क्रम processors
 *     that support more PID bits at runसमय
 *   - Implement flush_tlb_mm() by making the context stale and picking
 *     a new one
 *   - More aggressively clear stale map bits and maybe find some way to
 *     also clear mm->cpu_vm_mask bits when processes are migrated
 */

//#घोषणा DEBUG_MAP_CONSISTENCY
//#घोषणा DEBUG_CLAMP_LAST_CONTEXT   31
//#घोषणा DEBUG_HARDER

/* We करोn't use DEBUG because it tends to be compiled in always nowadays
 * and this would generate way too much output
 */
#अगर_घोषित DEBUG_HARDER
#घोषणा pr_hard(args...)	prपूर्णांकk(KERN_DEBUG args)
#घोषणा pr_hardcont(args...)	prपूर्णांकk(KERN_CONT args)
#अन्यथा
#घोषणा pr_hard(args...)	करो अणु पूर्ण जबतक(0)
#घोषणा pr_hardcont(args...)	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/memblock.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/cpu.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश <mm/mmu_decl.h>

/*
 * The MPC8xx has only 16 contexts. We rotate through them on each task चयन.
 * A better way would be to keep track of tasks that own contexts, and implement
 * an LRU usage. That way very active tasks करोn't always have to pay the TLB
 * reload overhead. The kernel pages are mapped shared, so the kernel can run on
 * behalf of any task that makes a kernel entry. Shared करोes not mean they are
 * not रक्षित, just that the ASID comparison is not perक्रमmed. -- Dan
 *
 * The IBM4xx has 256 contexts, so we can just rotate through these as a way of
 * "switching" contexts. If the TID of the TLB is zero, the PID/TID comparison
 * is disabled, so we can use a TID of zero to represent all kernel pages as
 * shared among all contexts. -- Dan
 *
 * The IBM 47x core supports 16-bit PIDs, thus 65535 contexts. We should
 * normally never have to steal though the facility is present अगर needed.
 * -- BenH
 */
#घोषणा FIRST_CONTEXT 1
#अगर_घोषित DEBUG_CLAMP_LAST_CONTEXT
#घोषणा LAST_CONTEXT DEBUG_CLAMP_LAST_CONTEXT
#या_अगर defined(CONFIG_PPC_8xx)
#घोषणा LAST_CONTEXT 16
#या_अगर defined(CONFIG_PPC_47x)
#घोषणा LAST_CONTEXT 65535
#अन्यथा
#घोषणा LAST_CONTEXT 255
#पूर्ण_अगर

अटल अचिन्हित पूर्णांक next_context, nr_मुक्त_contexts;
अटल अचिन्हित दीर्घ *context_map;
#अगर_घोषित CONFIG_SMP
अटल अचिन्हित दीर्घ *stale_map[NR_CPUS];
#पूर्ण_अगर
अटल काष्ठा mm_काष्ठा **context_mm;
अटल DEFINE_RAW_SPINLOCK(context_lock);

#घोषणा CTX_MAP_SIZE	\
	(माप(अचिन्हित दीर्घ) * (LAST_CONTEXT / BITS_PER_LONG + 1))


/* Steal a context from a task that has one at the moment.
 *
 * This is used when we are running out of available PID numbers
 * on the processors.
 *
 * This isn't an LRU प्रणाली, it just मुक्तs up each context in
 * turn (sort-of pseuकरो-अक्रमom replacement :).  This would be the
 * place to implement an LRU scheme अगर anyone was motivated to करो it.
 *  -- paulus
 *
 * For context stealing, we use a slightly dअगरferent approach क्रम
 * SMP and UP. Basically, the UP one is simpler and करोesn't use
 * the stale map as we can just flush the local CPU
 *  -- benh
 */
#अगर_घोषित CONFIG_SMP
अटल अचिन्हित पूर्णांक steal_context_smp(अचिन्हित पूर्णांक id)
अणु
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित पूर्णांक cpu, max, i;

	max = LAST_CONTEXT - FIRST_CONTEXT;

	/* Attempt to मुक्त next_context first and then loop until we manage */
	जबतक (max--) अणु
		/* Pick up the victim mm */
		mm = context_mm[id];

		/* We have a candidate victim, check अगर it's active, on SMP
		 * we cannot steal active contexts
		 */
		अगर (mm->context.active) अणु
			id++;
			अगर (id > LAST_CONTEXT)
				id = FIRST_CONTEXT;
			जारी;
		पूर्ण
		pr_hardcont(" | steal %d from 0x%p", id, mm);

		/* Mark this mm has having no context anymore */
		mm->context.id = MMU_NO_CONTEXT;

		/* Mark it stale on all CPUs that used this mm. For thपढ़ोed
		 * implementations, we set it on all thपढ़ोs on each core
		 * represented in the mask. A future implementation will use
		 * a core map instead but this will करो क्रम now.
		 */
		क्रम_each_cpu(cpu, mm_cpumask(mm)) अणु
			क्रम (i = cpu_first_thपढ़ो_sibling(cpu);
			     i <= cpu_last_thपढ़ो_sibling(cpu); i++) अणु
				अगर (stale_map[i])
					__set_bit(id, stale_map[i]);
			पूर्ण
			cpu = i - 1;
		पूर्ण
		वापस id;
	पूर्ण

	/* This will happen अगर you have more CPUs than available contexts,
	 * all we can करो here is रुको a bit and try again
	 */
	raw_spin_unlock(&context_lock);
	cpu_relax();
	raw_spin_lock(&context_lock);

	/* This will cause the caller to try again */
	वापस MMU_NO_CONTEXT;
पूर्ण
#पूर्ण_अगर  /* CONFIG_SMP */

अटल अचिन्हित पूर्णांक steal_all_contexts(व्योम)
अणु
	काष्ठा mm_काष्ठा *mm;
#अगर_घोषित CONFIG_SMP
	पूर्णांक cpu = smp_processor_id();
#पूर्ण_अगर
	अचिन्हित पूर्णांक id;

	क्रम (id = FIRST_CONTEXT; id <= LAST_CONTEXT; id++) अणु
		/* Pick up the victim mm */
		mm = context_mm[id];

		pr_hardcont(" | steal %d from 0x%p", id, mm);

		/* Mark this mm as having no context anymore */
		mm->context.id = MMU_NO_CONTEXT;
		अगर (id != FIRST_CONTEXT) अणु
			context_mm[id] = शून्य;
			__clear_bit(id, context_map);
#अगर_घोषित DEBUG_MAP_CONSISTENCY
			mm->context.active = 0;
#पूर्ण_अगर
		पूर्ण
#अगर_घोषित CONFIG_SMP
		__clear_bit(id, stale_map[cpu]);
#पूर्ण_अगर
	पूर्ण

	/* Flush the TLB क्रम all contexts (not to be used on SMP) */
	_tlbil_all();

	nr_मुक्त_contexts = LAST_CONTEXT - FIRST_CONTEXT;

	वापस FIRST_CONTEXT;
पूर्ण

/* Note that this will also be called on SMP अगर all other CPUs are
 * offlined, which means that it may be called क्रम cpu != 0. For
 * this to work, we somewhat assume that CPUs that are onlined
 * come up with a fully clean TLB (or are cleaned when offlined)
 */
अटल अचिन्हित पूर्णांक steal_context_up(अचिन्हित पूर्णांक id)
अणु
	काष्ठा mm_काष्ठा *mm;
#अगर_घोषित CONFIG_SMP
	पूर्णांक cpu = smp_processor_id();
#पूर्ण_अगर

	/* Pick up the victim mm */
	mm = context_mm[id];

	pr_hardcont(" | steal %d from 0x%p", id, mm);

	/* Flush the TLB क्रम that context */
	local_flush_tlb_mm(mm);

	/* Mark this mm has having no context anymore */
	mm->context.id = MMU_NO_CONTEXT;

	/* XXX This clear should ultimately be part of local_flush_tlb_mm */
#अगर_घोषित CONFIG_SMP
	__clear_bit(id, stale_map[cpu]);
#पूर्ण_अगर

	वापस id;
पूर्ण

#अगर_घोषित DEBUG_MAP_CONSISTENCY
अटल व्योम context_check_map(व्योम)
अणु
	अचिन्हित पूर्णांक id, nrf, nact;

	nrf = nact = 0;
	क्रम (id = FIRST_CONTEXT; id <= LAST_CONTEXT; id++) अणु
		पूर्णांक used = test_bit(id, context_map);
		अगर (!used)
			nrf++;
		अगर (used != (context_mm[id] != शून्य))
			pr_err("MMU: Context %d is %s and MM is %p !\n",
			       id, used ? "used" : "free", context_mm[id]);
		अगर (context_mm[id] != शून्य)
			nact += context_mm[id]->context.active;
	पूर्ण
	अगर (nrf != nr_मुक्त_contexts) अणु
		pr_err("MMU: Free context count out of sync ! (%d vs %d)\n",
		       nr_मुक्त_contexts, nrf);
		nr_मुक्त_contexts = nrf;
	पूर्ण
	अगर (nact > num_online_cpus())
		pr_err("MMU: More active contexts than CPUs ! (%d vs %d)\n",
		       nact, num_online_cpus());
	अगर (FIRST_CONTEXT > 0 && !test_bit(0, context_map))
		pr_err("MMU: Context 0 has been freed !!!\n");
पूर्ण
#अन्यथा
अटल व्योम context_check_map(व्योम) अणु पूर्ण
#पूर्ण_अगर

व्योम चयन_mmu_context(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
			काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित पूर्णांक id;
#अगर_घोषित CONFIG_SMP
	अचिन्हित पूर्णांक i, cpu = smp_processor_id();
#पूर्ण_अगर
	अचिन्हित दीर्घ *map;

	/* No lockless fast path .. yet */
	raw_spin_lock(&context_lock);

	pr_hard("[%d] activating context for mm @%p, active=%d, id=%d",
		cpu, next, next->context.active, next->context.id);

#अगर_घोषित CONFIG_SMP
	/* Mark us active and the previous one not anymore */
	next->context.active++;
	अगर (prev) अणु
		pr_hardcont(" (old=0x%p a=%d)", prev, prev->context.active);
		WARN_ON(prev->context.active < 1);
		prev->context.active--;
	पूर्ण

 again:
#पूर्ण_अगर /* CONFIG_SMP */

	/* If we alपढ़ोy have a valid asचिन्हित context, skip all that */
	id = next->context.id;
	अगर (likely(id != MMU_NO_CONTEXT)) अणु
#अगर_घोषित DEBUG_MAP_CONSISTENCY
		अगर (context_mm[id] != next)
			pr_err("MMU: mm 0x%p has id %d but context_mm[%d] says 0x%p\n",
			       next, id, id, context_mm[id]);
#पूर्ण_अगर
		जाओ ctxt_ok;
	पूर्ण

	/* We really करोn't have a context, let's try to acquire one */
	id = next_context;
	अगर (id > LAST_CONTEXT)
		id = FIRST_CONTEXT;
	map = context_map;

	/* No more मुक्त contexts, let's try to steal one */
	अगर (nr_मुक्त_contexts == 0) अणु
#अगर_घोषित CONFIG_SMP
		अगर (num_online_cpus() > 1) अणु
			id = steal_context_smp(id);
			अगर (id == MMU_NO_CONTEXT)
				जाओ again;
			जाओ stolen;
		पूर्ण
#पूर्ण_अगर /* CONFIG_SMP */
		अगर (IS_ENABLED(CONFIG_PPC_8xx))
			id = steal_all_contexts();
		अन्यथा
			id = steal_context_up(id);
		जाओ stolen;
	पूर्ण
	nr_मुक्त_contexts--;

	/* We know there's at least one मुक्त context, try to find it */
	जबतक (__test_and_set_bit(id, map)) अणु
		id = find_next_zero_bit(map, LAST_CONTEXT+1, id);
		अगर (id > LAST_CONTEXT)
			id = FIRST_CONTEXT;
	पूर्ण
 stolen:
	next_context = id + 1;
	context_mm[id] = next;
	next->context.id = id;
	pr_hardcont(" | new id=%d,nrf=%d", id, nr_मुक्त_contexts);

	context_check_map();
 ctxt_ok:

	/* If that context got marked stale on this CPU, then flush the
	 * local TLB क्रम it and unmark it beक्रमe we use it
	 */
#अगर_घोषित CONFIG_SMP
	अगर (test_bit(id, stale_map[cpu])) अणु
		pr_hardcont(" | stale flush %d [%d..%d]",
			    id, cpu_first_thपढ़ो_sibling(cpu),
			    cpu_last_thपढ़ो_sibling(cpu));

		local_flush_tlb_mm(next);

		/* XXX This clear should ultimately be part of local_flush_tlb_mm */
		क्रम (i = cpu_first_thपढ़ो_sibling(cpu);
		     i <= cpu_last_thपढ़ो_sibling(cpu); i++) अणु
			अगर (stale_map[i])
				__clear_bit(id, stale_map[i]);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* Flick the MMU and release lock */
	pr_hardcont(" -> %d\n", id);
	set_context(id, next->pgd);
	raw_spin_unlock(&context_lock);
पूर्ण

/*
 * Set up the context क्रम a new address space.
 */
पूर्णांक init_new_context(काष्ठा task_काष्ठा *t, काष्ठा mm_काष्ठा *mm)
अणु
	pr_hard("initing context for mm @%p\n", mm);

	/*
	 * We have MMU_NO_CONTEXT set to be ~0. Hence check
	 * explicitly against context.id == 0. This ensures that we properly
	 * initialize context slice details क्रम newly allocated mm's (which will
	 * have id == 0) and करोn't alter context slice inherited via विभाजन (which
	 * will have id != 0).
	 */
	अगर (mm->context.id == 0)
		slice_init_new_context_exec(mm);
	mm->context.id = MMU_NO_CONTEXT;
	mm->context.active = 0;
	pte_frag_set(&mm->context, शून्य);
	वापस 0;
पूर्ण

/*
 * We're finished using the context क्रम an address space.
 */
व्योम destroy_context(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक id;

	अगर (mm->context.id == MMU_NO_CONTEXT)
		वापस;

	WARN_ON(mm->context.active != 0);

	raw_spin_lock_irqsave(&context_lock, flags);
	id = mm->context.id;
	अगर (id != MMU_NO_CONTEXT) अणु
		__clear_bit(id, context_map);
		mm->context.id = MMU_NO_CONTEXT;
#अगर_घोषित DEBUG_MAP_CONSISTENCY
		mm->context.active = 0;
#पूर्ण_अगर
		context_mm[id] = शून्य;
		nr_मुक्त_contexts++;
	पूर्ण
	raw_spin_unlock_irqrestore(&context_lock, flags);
पूर्ण

#अगर_घोषित CONFIG_SMP
अटल पूर्णांक mmu_ctx_cpu_prepare(अचिन्हित पूर्णांक cpu)
अणु
	/* We करोn't touch CPU 0 map, it's allocated at aboot and kept
	 * around क्रमever
	 */
	अगर (cpu == boot_cpuid)
		वापस 0;

	pr_devel("MMU: Allocating stale context map for CPU %d\n", cpu);
	stale_map[cpu] = kzalloc(CTX_MAP_SIZE, GFP_KERNEL);
	वापस 0;
पूर्ण

अटल पूर्णांक mmu_ctx_cpu_dead(अचिन्हित पूर्णांक cpu)
अणु
#अगर_घोषित CONFIG_HOTPLUG_CPU
	अगर (cpu == boot_cpuid)
		वापस 0;

	pr_devel("MMU: Freeing stale context map for CPU %d\n", cpu);
	kमुक्त(stale_map[cpu]);
	stale_map[cpu] = शून्य;

	/* We also clear the cpu_vm_mask bits of CPUs going away */
	clear_tasks_mm_cpumask(cpu);
#पूर्ण_अगर
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_SMP */

/*
 * Initialize the context management stuff.
 */
व्योम __init mmu_context_init(व्योम)
अणु
	/* Mark init_mm as being active on all possible CPUs since
	 * we'll get called with prev == init_mm the first समय
	 * we schedule on a given CPU
	 */
	init_mm.context.active = NR_CPUS;

	/*
	 * Allocate the maps used by context management
	 */
	context_map = memblock_alloc(CTX_MAP_SIZE, SMP_CACHE_BYTES);
	अगर (!context_map)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      CTX_MAP_SIZE);
	context_mm = memblock_alloc(माप(व्योम *) * (LAST_CONTEXT + 1),
				    SMP_CACHE_BYTES);
	अगर (!context_mm)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      माप(व्योम *) * (LAST_CONTEXT + 1));
#अगर_घोषित CONFIG_SMP
	stale_map[boot_cpuid] = memblock_alloc(CTX_MAP_SIZE, SMP_CACHE_BYTES);
	अगर (!stale_map[boot_cpuid])
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      CTX_MAP_SIZE);

	cpuhp_setup_state_nocalls(CPUHP_POWERPC_MMU_CTX_PREPARE,
				  "powerpc/mmu/ctx:prepare",
				  mmu_ctx_cpu_prepare, mmu_ctx_cpu_dead);
#पूर्ण_अगर

	prपूर्णांकk(KERN_INFO
	       "MMU: Allocated %zu bytes of context maps for %d contexts\n",
	       2 * CTX_MAP_SIZE + (माप(व्योम *) * (LAST_CONTEXT + 1)),
	       LAST_CONTEXT - FIRST_CONTEXT + 1);

	/*
	 * Some processors have too few contexts to reserve one क्रम
	 * init_mm, and require using context 0 क्रम a normal task.
	 * Other processors reserve the use of context zero क्रम the kernel.
	 * This code assumes FIRST_CONTEXT < 32.
	 */
	context_map[0] = (1 << FIRST_CONTEXT) - 1;
	next_context = FIRST_CONTEXT;
	nr_मुक्त_contexts = LAST_CONTEXT - FIRST_CONTEXT + 1;
पूर्ण
