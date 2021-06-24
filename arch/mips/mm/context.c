<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/atomic.h>
#समावेश <linux/mmu_context.h>
#समावेश <linux/percpu.h>
#समावेश <linux/spinlock.h>

अटल DEFINE_RAW_SPINLOCK(cpu_mmid_lock);

अटल atomic64_t mmid_version;
अटल अचिन्हित पूर्णांक num_mmids;
अटल अचिन्हित दीर्घ *mmid_map;

अटल DEFINE_PER_CPU(u64, reserved_mmids);
अटल cpumask_t tlb_flush_pending;

अटल bool asid_versions_eq(पूर्णांक cpu, u64 a, u64 b)
अणु
	वापस ((a ^ b) & asid_version_mask(cpu)) == 0;
पूर्ण

व्योम get_new_mmu_context(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित पूर्णांक cpu;
	u64 asid;

	/*
	 * This function is specअगरic to ASIDs, and should not be called when
	 * MMIDs are in use.
	 */
	अगर (WARN_ON(IS_ENABLED(CONFIG_DEBUG_VM) && cpu_has_mmid))
		वापस;

	cpu = smp_processor_id();
	asid = asid_cache(cpu);

	अगर (!((asid += cpu_asid_inc()) & cpu_asid_mask(&cpu_data[cpu]))) अणु
		अगर (cpu_has_vtag_icache)
			flush_icache_all();
		local_flush_tlb_all();	/* start new asid cycle */
	पूर्ण

	set_cpu_context(cpu, mm, asid);
	asid_cache(cpu) = asid;
पूर्ण
EXPORT_SYMBOL_GPL(get_new_mmu_context);

व्योम check_mmu_context(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	/*
	 * This function is specअगरic to ASIDs, and should not be called when
	 * MMIDs are in use.
	 */
	अगर (WARN_ON(IS_ENABLED(CONFIG_DEBUG_VM) && cpu_has_mmid))
		वापस;

	/* Check अगर our ASID is of an older version and thus invalid */
	अगर (!asid_versions_eq(cpu, cpu_context(cpu, mm), asid_cache(cpu)))
		get_new_mmu_context(mm);
पूर्ण
EXPORT_SYMBOL_GPL(check_mmu_context);

अटल व्योम flush_context(व्योम)
अणु
	u64 mmid;
	पूर्णांक cpu;

	/* Update the list of reserved MMIDs and the MMID biपंचांगap */
	biपंचांगap_clear(mmid_map, 0, num_mmids);

	/* Reserve an MMID क्रम kmap/wired entries */
	__set_bit(MMID_KERNEL_WIRED, mmid_map);

	क्रम_each_possible_cpu(cpu) अणु
		mmid = xchg_relaxed(&cpu_data[cpu].asid_cache, 0);

		/*
		 * If this CPU has alपढ़ोy been through a
		 * rollover, but hasn't run another task in
		 * the meanसमय, we must preserve its reserved
		 * MMID, as this is the only trace we have of
		 * the process it is still running.
		 */
		अगर (mmid == 0)
			mmid = per_cpu(reserved_mmids, cpu);

		__set_bit(mmid & cpu_asid_mask(&cpu_data[cpu]), mmid_map);
		per_cpu(reserved_mmids, cpu) = mmid;
	पूर्ण

	/*
	 * Queue a TLB invalidation क्रम each CPU to perक्रमm on next
	 * context-चयन
	 */
	cpumask_setall(&tlb_flush_pending);
पूर्ण

अटल bool check_update_reserved_mmid(u64 mmid, u64 newmmid)
अणु
	bool hit;
	पूर्णांक cpu;

	/*
	 * Iterate over the set of reserved MMIDs looking क्रम a match.
	 * If we find one, then we can update our mm to use newmmid
	 * (i.e. the same MMID in the current generation) but we can't
	 * निकास the loop early, since we need to ensure that all copies
	 * of the old MMID are updated to reflect the mm. Failure to करो
	 * so could result in us missing the reserved MMID in a future
	 * generation.
	 */
	hit = false;
	क्रम_each_possible_cpu(cpu) अणु
		अगर (per_cpu(reserved_mmids, cpu) == mmid) अणु
			hit = true;
			per_cpu(reserved_mmids, cpu) = newmmid;
		पूर्ण
	पूर्ण

	वापस hit;
पूर्ण

अटल u64 get_new_mmid(काष्ठा mm_काष्ठा *mm)
अणु
	अटल u32 cur_idx = MMID_KERNEL_WIRED + 1;
	u64 mmid, version, mmid_mask;

	mmid = cpu_context(0, mm);
	version = atomic64_पढ़ो(&mmid_version);
	mmid_mask = cpu_asid_mask(&boot_cpu_data);

	अगर (!asid_versions_eq(0, mmid, 0)) अणु
		u64 newmmid = version | (mmid & mmid_mask);

		/*
		 * If our current MMID was active during a rollover, we
		 * can जारी to use it and this was just a false alarm.
		 */
		अगर (check_update_reserved_mmid(mmid, newmmid)) अणु
			mmid = newmmid;
			जाओ set_context;
		पूर्ण

		/*
		 * We had a valid MMID in a previous lअगरe, so try to re-use
		 * it अगर possible.
		 */
		अगर (!__test_and_set_bit(mmid & mmid_mask, mmid_map)) अणु
			mmid = newmmid;
			जाओ set_context;
		पूर्ण
	पूर्ण

	/* Allocate a मुक्त MMID */
	mmid = find_next_zero_bit(mmid_map, num_mmids, cur_idx);
	अगर (mmid != num_mmids)
		जाओ reserve_mmid;

	/* We're out of MMIDs, so increment the global version */
	version = atomic64_add_वापस_relaxed(asid_first_version(0),
					      &mmid_version);

	/* Note currently active MMIDs & mark TLBs as requiring flushes */
	flush_context();

	/* We have more MMIDs than CPUs, so this will always succeed */
	mmid = find_first_zero_bit(mmid_map, num_mmids);

reserve_mmid:
	__set_bit(mmid, mmid_map);
	cur_idx = mmid;
	mmid |= version;
set_context:
	set_cpu_context(0, mm, mmid);
	वापस mmid;
पूर्ण

व्योम check_चयन_mmu_context(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	u64 ctx, old_active_mmid;
	अचिन्हित दीर्घ flags;

	अगर (!cpu_has_mmid) अणु
		check_mmu_context(mm);
		ग_लिखो_c0_entryhi(cpu_asid(cpu, mm));
		जाओ setup_pgd;
	पूर्ण

	/*
	 * MMID चयन fast-path, to aव्योम acquiring cpu_mmid_lock when it's
	 * unnecessary.
	 *
	 * The memory ordering here is subtle. If our active_mmids is non-zero
	 * and the MMID matches the current version, then we update the CPU's
	 * asid_cache with a relaxed cmpxchg. Racing with a concurrent rollover
	 * means that either:
	 *
	 * - We get a zero back from the cmpxchg and end up रुकोing on
	 *   cpu_mmid_lock in check_mmu_context(). Taking the lock synchronises
	 *   with the rollover and so we are क्रमced to see the updated
	 *   generation.
	 *
	 * - We get a valid MMID back from the cmpxchg, which means the
	 *   relaxed xchg in flush_context will treat us as reserved
	 *   because atomic RmWs are totally ordered क्रम a given location.
	 */
	ctx = cpu_context(cpu, mm);
	old_active_mmid = READ_ONCE(cpu_data[cpu].asid_cache);
	अगर (!old_active_mmid ||
	    !asid_versions_eq(cpu, ctx, atomic64_पढ़ो(&mmid_version)) ||
	    !cmpxchg_relaxed(&cpu_data[cpu].asid_cache, old_active_mmid, ctx)) अणु
		raw_spin_lock_irqsave(&cpu_mmid_lock, flags);

		ctx = cpu_context(cpu, mm);
		अगर (!asid_versions_eq(cpu, ctx, atomic64_पढ़ो(&mmid_version)))
			ctx = get_new_mmid(mm);

		WRITE_ONCE(cpu_data[cpu].asid_cache, ctx);
		raw_spin_unlock_irqrestore(&cpu_mmid_lock, flags);
	पूर्ण

	/*
	 * Invalidate the local TLB अगर needed. Note that we must only clear our
	 * bit in tlb_flush_pending after this is complete, so that the
	 * cpu_has_shared_ftlb_entries हाल below isn't misled.
	 */
	अगर (cpumask_test_cpu(cpu, &tlb_flush_pending)) अणु
		अगर (cpu_has_vtag_icache)
			flush_icache_all();
		local_flush_tlb_all();
		cpumask_clear_cpu(cpu, &tlb_flush_pending);
	पूर्ण

	ग_लिखो_c0_memorymapid(ctx & cpu_asid_mask(&boot_cpu_data));

	/*
	 * If this CPU shares FTLB entries with its siblings and one or more of
	 * those siblings hasn't yet invalidated its TLB following a version
	 * increase then we need to invalidate any TLB entries क्रम our MMID
	 * that we might otherwise pick up from a sibling.
	 *
	 * We अगरdef on CONFIG_SMP because cpu_sibling_map isn't defined in
	 * CONFIG_SMP=n kernels.
	 */
#अगर_घोषित CONFIG_SMP
	अगर (cpu_has_shared_ftlb_entries &&
	    cpumask_पूर्णांकersects(&tlb_flush_pending, &cpu_sibling_map[cpu])) अणु
		/* Ensure we operate on the new MMID */
		mtc0_tlbw_hazard();

		/*
		 * Invalidate all TLB entries associated with the new
		 * MMID, and रुको क्रम the invalidation to complete.
		 */
		ginvt_mmid();
		sync_ginv();
	पूर्ण
#पूर्ण_अगर

setup_pgd:
	TLBMISS_HANDLER_SETUP_PGD(mm->pgd);
पूर्ण
EXPORT_SYMBOL_GPL(check_चयन_mmu_context);

अटल पूर्णांक mmid_init(व्योम)
अणु
	अगर (!cpu_has_mmid)
		वापस 0;

	/*
	 * Expect allocation after rollover to fail अगर we करोn't have at least
	 * one more MMID than CPUs.
	 */
	num_mmids = asid_first_version(0);
	WARN_ON(num_mmids <= num_possible_cpus());

	atomic64_set(&mmid_version, asid_first_version(0));
	mmid_map = kसुस्मृति(BITS_TO_LONGS(num_mmids), माप(*mmid_map),
			   GFP_KERNEL);
	अगर (!mmid_map)
		panic("Failed to allocate bitmap for %u MMIDs\n", num_mmids);

	/* Reserve an MMID क्रम kmap/wired entries */
	__set_bit(MMID_KERNEL_WIRED, mmid_map);

	pr_info("MMID allocator initialised with %u entries\n", num_mmids);
	वापस 0;
पूर्ण
early_initcall(mmid_init);
