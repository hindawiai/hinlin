<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on arch/arm/mm/context.c
 *
 * Copyright (C) 2002-2003 Deep Blue Solutions Ltd, all rights reserved.
 * Copyright (C) 2012 ARM Ltd.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/tlbflush.h>

अटल u32 asid_bits;
अटल DEFINE_RAW_SPINLOCK(cpu_asid_lock);

अटल atomic64_t asid_generation;
अटल अचिन्हित दीर्घ *asid_map;

अटल DEFINE_PER_CPU(atomic64_t, active_asids);
अटल DEFINE_PER_CPU(u64, reserved_asids);
अटल cpumask_t tlb_flush_pending;

अटल अचिन्हित दीर्घ max_pinned_asids;
अटल अचिन्हित दीर्घ nr_pinned_asids;
अटल अचिन्हित दीर्घ *pinned_asid_map;

#घोषणा ASID_MASK		(~GENMASK(asid_bits - 1, 0))
#घोषणा ASID_FIRST_VERSION	(1UL << asid_bits)

#घोषणा NUM_USER_ASIDS		ASID_FIRST_VERSION
#घोषणा asid2idx(asid)		((asid) & ~ASID_MASK)
#घोषणा idx2asid(idx)		asid2idx(idx)

/* Get the ASIDBits supported by the current CPU */
अटल u32 get_cpu_asid_bits(व्योम)
अणु
	u32 asid;
	पूर्णांक fld = cpuid_feature_extract_अचिन्हित_field(पढ़ो_cpuid(ID_AA64MMFR0_EL1),
						ID_AA64MMFR0_ASID_SHIFT);

	चयन (fld) अणु
	शेष:
		pr_warn("CPU%d: Unknown ASID size (%d); assuming 8-bit\n",
					smp_processor_id(),  fld);
		fallthrough;
	हाल 0:
		asid = 8;
		अवरोध;
	हाल 2:
		asid = 16;
	पूर्ण

	वापस asid;
पूर्ण

/* Check अगर the current cpu's ASIDBits is compatible with asid_bits */
व्योम verअगरy_cpu_asid_bits(व्योम)
अणु
	u32 asid = get_cpu_asid_bits();

	अगर (asid < asid_bits) अणु
		/*
		 * We cannot decrease the ASID size at runसमय, so panic अगर we support
		 * fewer ASID bits than the boot CPU.
		 */
		pr_crit("CPU%d: smaller ASID size(%u) than boot CPU (%u)\n",
				smp_processor_id(), asid, asid_bits);
		cpu_panic_kernel();
	पूर्ण
पूर्ण

अटल व्योम set_kpti_asid_bits(अचिन्हित दीर्घ *map)
अणु
	अचिन्हित पूर्णांक len = BITS_TO_LONGS(NUM_USER_ASIDS) * माप(अचिन्हित दीर्घ);
	/*
	 * In हाल of KPTI kernel/user ASIDs are allocated in
	 * pairs, the bottom bit distinguishes the two: अगर it
	 * is set, then the ASID will map only userspace. Thus
	 * mark even as reserved क्रम kernel.
	 */
	स_रखो(map, 0xaa, len);
पूर्ण

अटल व्योम set_reserved_asid_bits(व्योम)
अणु
	अगर (pinned_asid_map)
		biपंचांगap_copy(asid_map, pinned_asid_map, NUM_USER_ASIDS);
	अन्यथा अगर (arm64_kernel_unmapped_at_el0())
		set_kpti_asid_bits(asid_map);
	अन्यथा
		biपंचांगap_clear(asid_map, 0, NUM_USER_ASIDS);
पूर्ण

#घोषणा asid_gen_match(asid) \
	(!(((asid) ^ atomic64_पढ़ो(&asid_generation)) >> asid_bits))

अटल व्योम flush_context(व्योम)
अणु
	पूर्णांक i;
	u64 asid;

	/* Update the list of reserved ASIDs and the ASID biपंचांगap. */
	set_reserved_asid_bits();

	क्रम_each_possible_cpu(i) अणु
		asid = atomic64_xchg_relaxed(&per_cpu(active_asids, i), 0);
		/*
		 * If this CPU has alपढ़ोy been through a
		 * rollover, but hasn't run another task in
		 * the meanसमय, we must preserve its reserved
		 * ASID, as this is the only trace we have of
		 * the process it is still running.
		 */
		अगर (asid == 0)
			asid = per_cpu(reserved_asids, i);
		__set_bit(asid2idx(asid), asid_map);
		per_cpu(reserved_asids, i) = asid;
	पूर्ण

	/*
	 * Queue a TLB invalidation क्रम each CPU to perक्रमm on next
	 * context-चयन
	 */
	cpumask_setall(&tlb_flush_pending);
पूर्ण

अटल bool check_update_reserved_asid(u64 asid, u64 newasid)
अणु
	पूर्णांक cpu;
	bool hit = false;

	/*
	 * Iterate over the set of reserved ASIDs looking क्रम a match.
	 * If we find one, then we can update our mm to use newasid
	 * (i.e. the same ASID in the current generation) but we can't
	 * निकास the loop early, since we need to ensure that all copies
	 * of the old ASID are updated to reflect the mm. Failure to करो
	 * so could result in us missing the reserved ASID in a future
	 * generation.
	 */
	क्रम_each_possible_cpu(cpu) अणु
		अगर (per_cpu(reserved_asids, cpu) == asid) अणु
			hit = true;
			per_cpu(reserved_asids, cpu) = newasid;
		पूर्ण
	पूर्ण

	वापस hit;
पूर्ण

अटल u64 new_context(काष्ठा mm_काष्ठा *mm)
अणु
	अटल u32 cur_idx = 1;
	u64 asid = atomic64_पढ़ो(&mm->context.id);
	u64 generation = atomic64_पढ़ो(&asid_generation);

	अगर (asid != 0) अणु
		u64 newasid = generation | (asid & ~ASID_MASK);

		/*
		 * If our current ASID was active during a rollover, we
		 * can जारी to use it and this was just a false alarm.
		 */
		अगर (check_update_reserved_asid(asid, newasid))
			वापस newasid;

		/*
		 * If it is pinned, we can keep using it. Note that reserved
		 * takes priority, because even अगर it is also pinned, we need to
		 * update the generation पूर्णांकo the reserved_asids.
		 */
		अगर (refcount_पढ़ो(&mm->context.pinned))
			वापस newasid;

		/*
		 * We had a valid ASID in a previous lअगरe, so try to re-use
		 * it अगर possible.
		 */
		अगर (!__test_and_set_bit(asid2idx(asid), asid_map))
			वापस newasid;
	पूर्ण

	/*
	 * Allocate a मुक्त ASID. If we can't find one, take a note of the
	 * currently active ASIDs and mark the TLBs as requiring flushes.  We
	 * always count from ASID #2 (index 1), as we use ASID #0 when setting
	 * a reserved TTBR0 क्रम the init_mm and we allocate ASIDs in even/odd
	 * pairs.
	 */
	asid = find_next_zero_bit(asid_map, NUM_USER_ASIDS, cur_idx);
	अगर (asid != NUM_USER_ASIDS)
		जाओ set_asid;

	/* We're out of ASIDs, so increment the global generation count */
	generation = atomic64_add_वापस_relaxed(ASID_FIRST_VERSION,
						 &asid_generation);
	flush_context();

	/* We have more ASIDs than CPUs, so this will always succeed */
	asid = find_next_zero_bit(asid_map, NUM_USER_ASIDS, 1);

set_asid:
	__set_bit(asid, asid_map);
	cur_idx = asid;
	वापस idx2asid(asid) | generation;
पूर्ण

व्योम check_and_चयन_context(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक cpu;
	u64 asid, old_active_asid;

	अगर (प्रणाली_supports_cnp())
		cpu_set_reserved_ttbr0();

	asid = atomic64_पढ़ो(&mm->context.id);

	/*
	 * The memory ordering here is subtle.
	 * If our active_asids is non-zero and the ASID matches the current
	 * generation, then we update the active_asids entry with a relaxed
	 * cmpxchg. Racing with a concurrent rollover means that either:
	 *
	 * - We get a zero back from the cmpxchg and end up रुकोing on the
	 *   lock. Taking the lock synchronises with the rollover and so
	 *   we are क्रमced to see the updated generation.
	 *
	 * - We get a valid ASID back from the cmpxchg, which means the
	 *   relaxed xchg in flush_context will treat us as reserved
	 *   because atomic RmWs are totally ordered क्रम a given location.
	 */
	old_active_asid = atomic64_पढ़ो(this_cpu_ptr(&active_asids));
	अगर (old_active_asid && asid_gen_match(asid) &&
	    atomic64_cmpxchg_relaxed(this_cpu_ptr(&active_asids),
				     old_active_asid, asid))
		जाओ चयन_mm_fastpath;

	raw_spin_lock_irqsave(&cpu_asid_lock, flags);
	/* Check that our ASID beदीर्घs to the current generation. */
	asid = atomic64_पढ़ो(&mm->context.id);
	अगर (!asid_gen_match(asid)) अणु
		asid = new_context(mm);
		atomic64_set(&mm->context.id, asid);
	पूर्ण

	cpu = smp_processor_id();
	अगर (cpumask_test_and_clear_cpu(cpu, &tlb_flush_pending))
		local_flush_tlb_all();

	atomic64_set(this_cpu_ptr(&active_asids), asid);
	raw_spin_unlock_irqrestore(&cpu_asid_lock, flags);

चयन_mm_fastpath:

	arm64_apply_bp_hardening();

	/*
	 * Defer TTBR0_EL1 setting क्रम user thपढ़ोs to uaccess_enable() when
	 * emulating PAN.
	 */
	अगर (!प्रणाली_uses_ttbr0_pan())
		cpu_चयन_mm(mm->pgd, mm);
पूर्ण

अचिन्हित दीर्घ arm64_mm_context_get(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ flags;
	u64 asid;

	अगर (!pinned_asid_map)
		वापस 0;

	raw_spin_lock_irqsave(&cpu_asid_lock, flags);

	asid = atomic64_पढ़ो(&mm->context.id);

	अगर (refcount_inc_not_zero(&mm->context.pinned))
		जाओ out_unlock;

	अगर (nr_pinned_asids >= max_pinned_asids) अणु
		asid = 0;
		जाओ out_unlock;
	पूर्ण

	अगर (!asid_gen_match(asid)) अणु
		/*
		 * We went through one or more rollover since that ASID was
		 * used. Ensure that it is still valid, or generate a new one.
		 */
		asid = new_context(mm);
		atomic64_set(&mm->context.id, asid);
	पूर्ण

	nr_pinned_asids++;
	__set_bit(asid2idx(asid), pinned_asid_map);
	refcount_set(&mm->context.pinned, 1);

out_unlock:
	raw_spin_unlock_irqrestore(&cpu_asid_lock, flags);

	asid &= ~ASID_MASK;

	/* Set the equivalent of USER_ASID_BIT */
	अगर (asid && arm64_kernel_unmapped_at_el0())
		asid |= 1;

	वापस asid;
पूर्ण
EXPORT_SYMBOL_GPL(arm64_mm_context_get);

व्योम arm64_mm_context_put(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ flags;
	u64 asid = atomic64_पढ़ो(&mm->context.id);

	अगर (!pinned_asid_map)
		वापस;

	raw_spin_lock_irqsave(&cpu_asid_lock, flags);

	अगर (refcount_dec_and_test(&mm->context.pinned)) अणु
		__clear_bit(asid2idx(asid), pinned_asid_map);
		nr_pinned_asids--;
	पूर्ण

	raw_spin_unlock_irqrestore(&cpu_asid_lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(arm64_mm_context_put);

/* Errata workaround post TTBRx_EL1 update. */
यंत्रlinkage व्योम post_ttbr_update_workaround(व्योम)
अणु
	अगर (!IS_ENABLED(CONFIG_CAVIUM_ERRATUM_27456))
		वापस;

	यंत्र(ALTERNATIVE("nop; nop; nop",
			"ic iallu; dsb nsh; isb",
			ARM64_WORKAROUND_CAVIUM_27456));
पूर्ण

व्योम cpu_करो_चयन_mm(phys_addr_t pgd_phys, काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ ttbr1 = पढ़ो_sysreg(ttbr1_el1);
	अचिन्हित दीर्घ asid = ASID(mm);
	अचिन्हित दीर्घ ttbr0 = phys_to_ttbr(pgd_phys);

	/* Skip CNP क्रम the reserved ASID */
	अगर (प्रणाली_supports_cnp() && asid)
		ttbr0 |= TTBR_CNP_BIT;

	/* SW PAN needs a copy of the ASID in TTBR0 क्रम entry */
	अगर (IS_ENABLED(CONFIG_ARM64_SW_TTBR0_PAN))
		ttbr0 |= FIELD_PREP(TTBR_ASID_MASK, asid);

	/* Set ASID in TTBR1 since TCR.A1 is set */
	ttbr1 &= ~TTBR_ASID_MASK;
	ttbr1 |= FIELD_PREP(TTBR_ASID_MASK, asid);

	ग_लिखो_sysreg(ttbr1, ttbr1_el1);
	isb();
	ग_लिखो_sysreg(ttbr0, ttbr0_el1);
	isb();
	post_ttbr_update_workaround();
पूर्ण

अटल पूर्णांक asids_update_limit(व्योम)
अणु
	अचिन्हित दीर्घ num_available_asids = NUM_USER_ASIDS;

	अगर (arm64_kernel_unmapped_at_el0()) अणु
		num_available_asids /= 2;
		अगर (pinned_asid_map)
			set_kpti_asid_bits(pinned_asid_map);
	पूर्ण
	/*
	 * Expect allocation after rollover to fail अगर we करोn't have at least
	 * one more ASID than CPUs. ASID #0 is reserved क्रम init_mm.
	 */
	WARN_ON(num_available_asids - 1 <= num_possible_cpus());
	pr_info("ASID allocator initialised with %lu entries\n",
		num_available_asids);

	/*
	 * There must always be an ASID available after rollover. Ensure that,
	 * even अगर all CPUs have a reserved ASID and the maximum number of ASIDs
	 * are pinned, there still is at least one empty slot in the ASID map.
	 */
	max_pinned_asids = num_available_asids - num_possible_cpus() - 2;
	वापस 0;
पूर्ण
arch_initcall(asids_update_limit);

अटल पूर्णांक asids_init(व्योम)
अणु
	asid_bits = get_cpu_asid_bits();
	atomic64_set(&asid_generation, ASID_FIRST_VERSION);
	asid_map = kसुस्मृति(BITS_TO_LONGS(NUM_USER_ASIDS), माप(*asid_map),
			   GFP_KERNEL);
	अगर (!asid_map)
		panic("Failed to allocate bitmap for %lu ASIDs\n",
		      NUM_USER_ASIDS);

	pinned_asid_map = kसुस्मृति(BITS_TO_LONGS(NUM_USER_ASIDS),
				  माप(*pinned_asid_map), GFP_KERNEL);
	nr_pinned_asids = 0;

	/*
	 * We cannot call set_reserved_asid_bits() here because CPU
	 * caps are not finalized yet, so it is safer to assume KPTI
	 * and reserve kernel ASID's from beginning.
	 */
	अगर (IS_ENABLED(CONFIG_UNMAP_KERNEL_AT_EL0))
		set_kpti_asid_bits(asid_map);
	वापस 0;
पूर्ण
early_initcall(asids_init);
