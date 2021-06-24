<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic ASID allocator.
 *
 * Based on arch/arm/mm/context.c
 *
 * Copyright (C) 2002-2003 Deep Blue Solutions Ltd, all rights reserved.
 * Copyright (C) 2012 ARM Ltd.
 */

#समावेश <linux/slab.h>
#समावेश <linux/mm_types.h>

#समावेश <यंत्र/asid.h>

#घोषणा reserved_asid(info, cpu) *per_cpu_ptr((info)->reserved, cpu)

#घोषणा ASID_MASK(info)			(~GENMASK((info)->bits - 1, 0))
#घोषणा ASID_FIRST_VERSION(info)	(1UL << ((info)->bits))

#घोषणा asid2idx(info, asid)		(((asid) & ~ASID_MASK(info)) >> (info)->ctxt_shअगरt)
#घोषणा idx2asid(info, idx)		(((idx) << (info)->ctxt_shअगरt) & ~ASID_MASK(info))

अटल व्योम flush_context(काष्ठा asid_info *info)
अणु
	पूर्णांक i;
	u64 asid;

	/* Update the list of reserved ASIDs and the ASID biपंचांगap. */
	biपंचांगap_clear(info->map, 0, NUM_CTXT_ASIDS(info));

	क्रम_each_possible_cpu(i) अणु
		asid = atomic64_xchg_relaxed(&active_asid(info, i), 0);
		/*
		 * If this CPU has alपढ़ोy been through a
		 * rollover, but hasn't run another task in
		 * the meanसमय, we must preserve its reserved
		 * ASID, as this is the only trace we have of
		 * the process it is still running.
		 */
		अगर (asid == 0)
			asid = reserved_asid(info, i);
		__set_bit(asid2idx(info, asid), info->map);
		reserved_asid(info, i) = asid;
	पूर्ण

	/*
	 * Queue a TLB invalidation क्रम each CPU to perक्रमm on next
	 * context-चयन
	 */
	cpumask_setall(&info->flush_pending);
पूर्ण

अटल bool check_update_reserved_asid(काष्ठा asid_info *info, u64 asid,
				       u64 newasid)
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
		अगर (reserved_asid(info, cpu) == asid) अणु
			hit = true;
			reserved_asid(info, cpu) = newasid;
		पूर्ण
	पूर्ण

	वापस hit;
पूर्ण

अटल u64 new_context(काष्ठा asid_info *info, atomic64_t *pasid,
		       काष्ठा mm_काष्ठा *mm)
अणु
	अटल u32 cur_idx = 1;
	u64 asid = atomic64_पढ़ो(pasid);
	u64 generation = atomic64_पढ़ो(&info->generation);

	अगर (asid != 0) अणु
		u64 newasid = generation | (asid & ~ASID_MASK(info));

		/*
		 * If our current ASID was active during a rollover, we
		 * can जारी to use it and this was just a false alarm.
		 */
		अगर (check_update_reserved_asid(info, asid, newasid))
			वापस newasid;

		/*
		 * We had a valid ASID in a previous lअगरe, so try to re-use
		 * it अगर possible.
		 */
		अगर (!__test_and_set_bit(asid2idx(info, asid), info->map))
			वापस newasid;
	पूर्ण

	/*
	 * Allocate a मुक्त ASID. If we can't find one, take a note of the
	 * currently active ASIDs and mark the TLBs as requiring flushes.  We
	 * always count from ASID #2 (index 1), as we use ASID #0 when setting
	 * a reserved TTBR0 क्रम the init_mm and we allocate ASIDs in even/odd
	 * pairs.
	 */
	asid = find_next_zero_bit(info->map, NUM_CTXT_ASIDS(info), cur_idx);
	अगर (asid != NUM_CTXT_ASIDS(info))
		जाओ set_asid;

	/* We're out of ASIDs, so increment the global generation count */
	generation = atomic64_add_वापस_relaxed(ASID_FIRST_VERSION(info),
						 &info->generation);
	flush_context(info);

	/* We have more ASIDs than CPUs, so this will always succeed */
	asid = find_next_zero_bit(info->map, NUM_CTXT_ASIDS(info), 1);

set_asid:
	__set_bit(asid, info->map);
	cur_idx = asid;
	cpumask_clear(mm_cpumask(mm));
	वापस idx2asid(info, asid) | generation;
पूर्ण

/*
 * Generate a new ASID क्रम the context.
 *
 * @pasid: Poपूर्णांकer to the current ASID batch allocated. It will be updated
 * with the new ASID batch.
 * @cpu: current CPU ID. Must have been acquired through get_cpu()
 */
व्योम asid_new_context(काष्ठा asid_info *info, atomic64_t *pasid,
		      अचिन्हित पूर्णांक cpu, काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ flags;
	u64 asid;

	raw_spin_lock_irqsave(&info->lock, flags);
	/* Check that our ASID beदीर्घs to the current generation. */
	asid = atomic64_पढ़ो(pasid);
	अगर ((asid ^ atomic64_पढ़ो(&info->generation)) >> info->bits) अणु
		asid = new_context(info, pasid, mm);
		atomic64_set(pasid, asid);
	पूर्ण

	अगर (cpumask_test_and_clear_cpu(cpu, &info->flush_pending))
		info->flush_cpu_ctxt_cb();

	atomic64_set(&active_asid(info, cpu), asid);
	cpumask_set_cpu(cpu, mm_cpumask(mm));
	raw_spin_unlock_irqrestore(&info->lock, flags);
पूर्ण

/*
 * Initialize the ASID allocator
 *
 * @info: Poपूर्णांकer to the asid allocator काष्ठाure
 * @bits: Number of ASIDs available
 * @asid_per_ctxt: Number of ASIDs to allocate per-context. ASIDs are
 * allocated contiguously क्रम a given context. This value should be a घातer of
 * 2.
 */
पूर्णांक asid_allocator_init(काष्ठा asid_info *info,
			u32 bits, अचिन्हित पूर्णांक asid_per_ctxt,
			व्योम (*flush_cpu_ctxt_cb)(व्योम))
अणु
	info->bits = bits;
	info->ctxt_shअगरt = ilog2(asid_per_ctxt);
	info->flush_cpu_ctxt_cb = flush_cpu_ctxt_cb;
	/*
	 * Expect allocation after rollover to fail अगर we करोn't have at least
	 * one more ASID than CPUs. ASID #0 is always reserved.
	 */
	WARN_ON(NUM_CTXT_ASIDS(info) - 1 <= num_possible_cpus());
	atomic64_set(&info->generation, ASID_FIRST_VERSION(info));
	info->map = kसुस्मृति(BITS_TO_LONGS(NUM_CTXT_ASIDS(info)),
			    माप(*info->map), GFP_KERNEL);
	अगर (!info->map)
		वापस -ENOMEM;

	raw_spin_lock_init(&info->lock);

	वापस 0;
पूर्ण
