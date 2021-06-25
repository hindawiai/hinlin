<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 * Copyright (C) 2017 SiFive
 * Copyright (C) 2021 Western Digital Corporation or its affiliates.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/mm.h>
#समावेश <linux/percpu.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/अटल_key.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/mmu_context.h>

#अगर_घोषित CONFIG_MMU

अटल DEFINE_STATIC_KEY_FALSE(use_asid_allocator);

अटल अचिन्हित दीर्घ asid_bits;
अटल अचिन्हित दीर्घ num_asids;
अटल अचिन्हित दीर्घ asid_mask;

अटल atomic_दीर्घ_t current_version;

अटल DEFINE_RAW_SPINLOCK(context_lock);
अटल cpumask_t context_tlb_flush_pending;
अटल अचिन्हित दीर्घ *context_asid_map;

अटल DEFINE_PER_CPU(atomic_दीर्घ_t, active_context);
अटल DEFINE_PER_CPU(अचिन्हित दीर्घ, reserved_context);

अटल bool check_update_reserved_context(अचिन्हित दीर्घ cntx,
					  अचिन्हित दीर्घ newcntx)
अणु
	पूर्णांक cpu;
	bool hit = false;

	/*
	 * Iterate over the set of reserved CONTEXT looking क्रम a match.
	 * If we find one, then we can update our mm to use new CONTEXT
	 * (i.e. the same CONTEXT in the current_version) but we can't
	 * निकास the loop early, since we need to ensure that all copies
	 * of the old CONTEXT are updated to reflect the mm. Failure to करो
	 * so could result in us missing the reserved CONTEXT in a future
	 * version.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		अगर (per_cpu(reserved_context, cpu) == cntx) अणु
			hit = true;
			per_cpu(reserved_context, cpu) = newcntx;
		पूर्ण
	पूर्ण

	वापस hit;
पूर्ण

अटल व्योम __flush_context(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ cntx;

	/* Must be called with context_lock held */
	lockdep_निश्चित_held(&context_lock);

	/* Update the list of reserved ASIDs and the ASID biपंचांगap. */
	biपंचांगap_clear(context_asid_map, 0, num_asids);

	/* Mark alपढ़ोy active ASIDs as used */
	क्रम_each_possible_cpu(i) अणु
		cntx = atomic_दीर्घ_xchg_relaxed(&per_cpu(active_context, i), 0);
		/*
		 * If this CPU has alपढ़ोy been through a rollover, but
		 * hasn't run another task in the meanसमय, we must preserve
		 * its reserved CONTEXT, as this is the only trace we have of
		 * the process it is still running.
		 */
		अगर (cntx == 0)
			cntx = per_cpu(reserved_context, i);

		__set_bit(cntx & asid_mask, context_asid_map);
		per_cpu(reserved_context, i) = cntx;
	पूर्ण

	/* Mark ASID #0 as used because it is used at boot-समय */
	__set_bit(0, context_asid_map);

	/* Queue a TLB invalidation क्रम each CPU on next context-चयन */
	cpumask_setall(&context_tlb_flush_pending);
पूर्ण

अटल अचिन्हित दीर्घ __new_context(काष्ठा mm_काष्ठा *mm)
अणु
	अटल u32 cur_idx = 1;
	अचिन्हित दीर्घ cntx = atomic_दीर्घ_पढ़ो(&mm->context.id);
	अचिन्हित दीर्घ asid, ver = atomic_दीर्घ_पढ़ो(&current_version);

	/* Must be called with context_lock held */
	lockdep_निश्चित_held(&context_lock);

	अगर (cntx != 0) अणु
		अचिन्हित दीर्घ newcntx = ver | (cntx & asid_mask);

		/*
		 * If our current CONTEXT was active during a rollover, we
		 * can जारी to use it and this was just a false alarm.
		 */
		अगर (check_update_reserved_context(cntx, newcntx))
			वापस newcntx;

		/*
		 * We had a valid CONTEXT in a previous lअगरe, so try to
		 * re-use it अगर possible.
		 */
		अगर (!__test_and_set_bit(cntx & asid_mask, context_asid_map))
			वापस newcntx;
	पूर्ण

	/*
	 * Allocate a मुक्त ASID. If we can't find one then increment
	 * current_version and flush all ASIDs.
	 */
	asid = find_next_zero_bit(context_asid_map, num_asids, cur_idx);
	अगर (asid != num_asids)
		जाओ set_asid;

	/* We're out of ASIDs, so increment current_version */
	ver = atomic_दीर्घ_add_वापस_relaxed(num_asids, &current_version);

	/* Flush everything  */
	__flush_context();

	/* We have more ASIDs than CPUs, so this will always succeed */
	asid = find_next_zero_bit(context_asid_map, num_asids, 1);

set_asid:
	__set_bit(asid, context_asid_map);
	cur_idx = asid;
	वापस asid | ver;
पूर्ण

अटल व्योम set_mm_asid(काष्ठा mm_काष्ठा *mm, अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ flags;
	bool need_flush_tlb = false;
	अचिन्हित दीर्घ cntx, old_active_cntx;

	cntx = atomic_दीर्घ_पढ़ो(&mm->context.id);

	/*
	 * If our active_context is non-zero and the context matches the
	 * current_version, then we update the active_context entry with a
	 * relaxed cmpxchg.
	 *
	 * Following is how we handle racing with a concurrent rollover:
	 *
	 * - We get a zero back from the cmpxchg and end up रुकोing on the
	 *   lock. Taking the lock synchronises with the rollover and so
	 *   we are क्रमced to see the updated verion.
	 *
	 * - We get a valid context back from the cmpxchg then we जारी
	 *   using old ASID because __flush_context() would have marked ASID
	 *   of active_context as used and next context चयन we will
	 *   allocate new context.
	 */
	old_active_cntx = atomic_दीर्घ_पढ़ो(&per_cpu(active_context, cpu));
	अगर (old_active_cntx &&
	    ((cntx & ~asid_mask) == atomic_दीर्घ_पढ़ो(&current_version)) &&
	    atomic_दीर्घ_cmpxchg_relaxed(&per_cpu(active_context, cpu),
					old_active_cntx, cntx))
		जाओ चयन_mm_fast;

	raw_spin_lock_irqsave(&context_lock, flags);

	/* Check that our ASID beदीर्घs to the current_version. */
	cntx = atomic_दीर्घ_पढ़ो(&mm->context.id);
	अगर ((cntx & ~asid_mask) != atomic_दीर्घ_पढ़ो(&current_version)) अणु
		cntx = __new_context(mm);
		atomic_दीर्घ_set(&mm->context.id, cntx);
	पूर्ण

	अगर (cpumask_test_and_clear_cpu(cpu, &context_tlb_flush_pending))
		need_flush_tlb = true;

	atomic_दीर्घ_set(&per_cpu(active_context, cpu), cntx);

	raw_spin_unlock_irqrestore(&context_lock, flags);

चयन_mm_fast:
	csr_ग_लिखो(CSR_SATP, virt_to_pfn(mm->pgd) |
		  ((cntx & asid_mask) << SATP_ASID_SHIFT) |
		  SATP_MODE);

	अगर (need_flush_tlb)
		local_flush_tlb_all();
पूर्ण

अटल व्योम set_mm_noasid(काष्ठा mm_काष्ठा *mm)
अणु
	/* Switch the page table and blindly nuke entire local TLB */
	csr_ग_लिखो(CSR_SATP, virt_to_pfn(mm->pgd) | SATP_MODE);
	local_flush_tlb_all();
पूर्ण

अटल अंतरभूत व्योम set_mm(काष्ठा mm_काष्ठा *mm, अचिन्हित पूर्णांक cpu)
अणु
	अगर (अटल_branch_unlikely(&use_asid_allocator))
		set_mm_asid(mm, cpu);
	अन्यथा
		set_mm_noasid(mm);
पूर्ण

अटल पूर्णांक asids_init(व्योम)
अणु
	अचिन्हित दीर्घ old;

	/* Figure-out number of ASID bits in HW */
	old = csr_पढ़ो(CSR_SATP);
	asid_bits = old | (SATP_ASID_MASK << SATP_ASID_SHIFT);
	csr_ग_लिखो(CSR_SATP, asid_bits);
	asid_bits = (csr_पढ़ो(CSR_SATP) >> SATP_ASID_SHIFT)  & SATP_ASID_MASK;
	asid_bits = fls_दीर्घ(asid_bits);
	csr_ग_लिखो(CSR_SATP, old);

	/*
	 * In the process of determining number of ASID bits (above)
	 * we polluted the TLB of current HART so let's करो TLB flushed
	 * to हटाओ unwanted TLB enteries.
	 */
	local_flush_tlb_all();

	/* Pre-compute ASID details */
	num_asids = 1 << asid_bits;
	asid_mask = num_asids - 1;

	/*
	 * Use ASID allocator only अगर number of HW ASIDs are
	 * at-least twice more than CPUs
	 */
	अगर (num_asids > (2 * num_possible_cpus())) अणु
		atomic_दीर्घ_set(&current_version, num_asids);

		context_asid_map = kसुस्मृति(BITS_TO_LONGS(num_asids),
				   माप(*context_asid_map), GFP_KERNEL);
		अगर (!context_asid_map)
			panic("Failed to allocate bitmap for %lu ASIDs\n",
			      num_asids);

		__set_bit(0, context_asid_map);

		अटल_branch_enable(&use_asid_allocator);

		pr_info("ASID allocator using %lu bits (%lu entries)\n",
			asid_bits, num_asids);
	पूर्ण अन्यथा अणु
		pr_info("ASID allocator disabled\n");
	पूर्ण

	वापस 0;
पूर्ण
early_initcall(asids_init);
#अन्यथा
अटल अंतरभूत व्योम set_mm(काष्ठा mm_काष्ठा *mm, अचिन्हित पूर्णांक cpu)
अणु
	/* Nothing to करो here when there is no MMU */
पूर्ण
#पूर्ण_अगर

/*
 * When necessary, perक्रमms a deferred icache flush क्रम the given MM context,
 * on the local CPU.  RISC-V has no direct mechanism क्रम inकाष्ठाion cache
 * shoot करोwns, so instead we send an IPI that inक्रमms the remote harts they
 * need to flush their local inकाष्ठाion caches.  To aव्योम pathologically slow
 * behavior in a common हाल (a bunch of single-hart processes on a many-hart
 * machine, ie 'make -j') we aव्योम the IPIs क्रम harts that are not currently
 * executing a MM context and instead schedule a deferred local inकाष्ठाion
 * cache flush to be perक्रमmed beक्रमe execution resumes on each hart.  This
 * actually perक्रमms that local inकाष्ठाion cache flush, which implicitly only
 * refers to the current hart.
 */
अटल अंतरभूत व्योम flush_icache_deferred(काष्ठा mm_काष्ठा *mm)
अणु
#अगर_घोषित CONFIG_SMP
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	cpumask_t *mask = &mm->context.icache_stale_mask;

	अगर (cpumask_test_cpu(cpu, mask)) अणु
		cpumask_clear_cpu(cpu, mask);
		/*
		 * Ensure the remote hart's ग_लिखोs are visible to this hart.
		 * This pairs with a barrier in flush_icache_mm.
		 */
		smp_mb();
		local_flush_icache_all();
	पूर्ण

#पूर्ण_अगर
पूर्ण

व्योम चयन_mm(काष्ठा mm_काष्ठा *prev, काष्ठा mm_काष्ठा *next,
	काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित पूर्णांक cpu;

	अगर (unlikely(prev == next))
		वापस;

	/*
	 * Mark the current MM context as inactive, and the next as
	 * active.  This is at least used by the icache flushing
	 * routines in order to determine who should be flushed.
	 */
	cpu = smp_processor_id();

	cpumask_clear_cpu(cpu, mm_cpumask(prev));
	cpumask_set_cpu(cpu, mm_cpumask(next));

	set_mm(next, cpu);

	flush_icache_deferred(next);
पूर्ण
