<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * native hashtable management.
 *
 * SMP scalability work:
 *    Copyright (C) 2001 Anton Blanअक्षरd <anton@au.ibm.com>, IBM
 */

#अघोषित DEBUG_LOW

#समावेश <linux/spinlock.h>
#समावेश <linux/bitops.h>
#समावेश <linux/of.h>
#समावेश <linux/processor.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/smp.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/trace.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/kexec.h>
#समावेश <यंत्र/ppc-opcode.h>
#समावेश <यंत्र/feature-fixups.h>

#समावेश <misc/cxl-base.h>

#अगर_घोषित DEBUG_LOW
#घोषणा DBG_LOW(fmt...) udbg_म_लिखो(fmt)
#अन्यथा
#घोषणा DBG_LOW(fmt...)
#पूर्ण_अगर

#अगर_घोषित __BIG_ENDIAN__
#घोषणा HPTE_LOCK_BIT 3
#अन्यथा
#घोषणा HPTE_LOCK_BIT (56+3)
#पूर्ण_अगर

अटल DEFINE_RAW_SPINLOCK(native_tlbie_lock);

अटल अंतरभूत व्योम tlbiel_hash_set_isa206(अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक is)
अणु
	अचिन्हित दीर्घ rb;

	rb = (set << PPC_BITLSHIFT(51)) | (is << PPC_BITLSHIFT(53));

	यंत्र अस्थिर("tlbiel %0" : : "r" (rb));
पूर्ण

/*
 * tlbiel inकाष्ठाion क्रम hash, set invalidation
 * i.e., r=1 and is=01 or is=10 or is=11
 */
अटल __always_अंतरभूत व्योम tlbiel_hash_set_isa300(अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक is,
					अचिन्हित पूर्णांक pid,
					अचिन्हित पूर्णांक ric, अचिन्हित पूर्णांक prs)
अणु
	अचिन्हित दीर्घ rb;
	अचिन्हित दीर्घ rs;
	अचिन्हित पूर्णांक r = 0; /* hash क्रमmat */

	rb = (set << PPC_BITLSHIFT(51)) | (is << PPC_BITLSHIFT(53));
	rs = ((अचिन्हित दीर्घ)pid << PPC_BITLSHIFT(31));

	यंत्र अस्थिर(PPC_TLBIEL(%0, %1, %2, %3, %4)
		     : : "r"(rb), "r"(rs), "i"(ric), "i"(prs), "i"(r)
		     : "memory");
पूर्ण


अटल व्योम tlbiel_all_isa206(अचिन्हित पूर्णांक num_sets, अचिन्हित पूर्णांक is)
अणु
	अचिन्हित पूर्णांक set;

	यंत्र अस्थिर("ptesync": : :"memory");

	क्रम (set = 0; set < num_sets; set++)
		tlbiel_hash_set_isa206(set, is);

	ppc_after_tlbiel_barrier();
पूर्ण

अटल व्योम tlbiel_all_isa300(अचिन्हित पूर्णांक num_sets, अचिन्हित पूर्णांक is)
अणु
	अचिन्हित पूर्णांक set;

	यंत्र अस्थिर("ptesync": : :"memory");

	/*
	 * Flush the partition table cache अगर this is HV mode.
	 */
	अगर (early_cpu_has_feature(CPU_FTR_HVMODE))
		tlbiel_hash_set_isa300(0, is, 0, 2, 0);

	/*
	 * Now invalidate the process table cache. UPRT=0 HPT modes (what
	 * current hardware implements) करो not use the process table, but
	 * add the flushes anyway.
	 *
	 * From ISA v3.0B p. 1078:
	 *     The following क्रमms are invalid.
	 *      * PRS=1, R=0, and RIC!=2 (The only process-scoped
	 *        HPT caching is of the Process Table.)
	 */
	tlbiel_hash_set_isa300(0, is, 0, 2, 1);

	/*
	 * Then flush the sets of the TLB proper. Hash mode uses
	 * partition scoped TLB translations, which may be flushed
	 * in !HV mode.
	 */
	क्रम (set = 0; set < num_sets; set++)
		tlbiel_hash_set_isa300(set, is, 0, 0, 0);

	ppc_after_tlbiel_barrier();

	यंत्र अस्थिर(PPC_ISA_3_0_INVALIDATE_ERAT "; isync" : : :"memory");
पूर्ण

व्योम hash__tlbiel_all(अचिन्हित पूर्णांक action)
अणु
	अचिन्हित पूर्णांक is;

	चयन (action) अणु
	हाल TLB_INVAL_SCOPE_GLOBAL:
		is = 3;
		अवरोध;
	हाल TLB_INVAL_SCOPE_LPID:
		is = 2;
		अवरोध;
	शेष:
		BUG();
	पूर्ण

	अगर (early_cpu_has_feature(CPU_FTR_ARCH_300))
		tlbiel_all_isa300(POWER9_TLB_SETS_HASH, is);
	अन्यथा अगर (early_cpu_has_feature(CPU_FTR_ARCH_207S))
		tlbiel_all_isa206(POWER8_TLB_SETS, is);
	अन्यथा अगर (early_cpu_has_feature(CPU_FTR_ARCH_206))
		tlbiel_all_isa206(POWER7_TLB_SETS, is);
	अन्यथा
		WARN(1, "%s called on pre-POWER7 CPU\n", __func__);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ  ___tlbie(अचिन्हित दीर्घ vpn, पूर्णांक psize,
						पूर्णांक apsize, पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ va;
	अचिन्हित पूर्णांक penc;
	अचिन्हित दीर्घ sllp;

	/*
	 * We need 14 to 65 bits of va क्रम a tlibe of 4K page
	 * With vpn we ignore the lower VPN_SHIFT bits alपढ़ोy.
	 * And top two bits are alपढ़ोy ignored because we can
	 * only accomodate 76 bits in a 64 bit vpn with a VPN_SHIFT
	 * of 12.
	 */
	va = vpn << VPN_SHIFT;
	/*
	 * clear top 16 bits of 64bit va, non SLS segment
	 * Older versions of the architecture (2.02 and earler) require the
	 * masking of the top 16 bits.
	 */
	अगर (mmu_has_feature(MMU_FTR_TLBIE_CROP_VA))
		va &= ~(0xffffULL << 48);

	चयन (psize) अणु
	हाल MMU_PAGE_4K:
		/* clear out bits after (52) [0....52.....63] */
		va &= ~((1ul << (64 - 52)) - 1);
		va |= ssize << 8;
		sllp = get_sllp_encoding(apsize);
		va |= sllp << 5;
		यंत्र अस्थिर(ASM_FTR_IFCLR("tlbie %0,0", PPC_TLBIE(%1,%0), %2)
			     : : "r" (va), "r"(0), "i" (CPU_FTR_ARCH_206)
			     : "memory");
		अवरोध;
	शेष:
		/* We need 14 to 14 + i bits of va */
		penc = mmu_psize_defs[psize].penc[apsize];
		va &= ~((1ul << mmu_psize_defs[apsize].shअगरt) - 1);
		va |= penc << 12;
		va |= ssize << 8;
		/*
		 * AVAL bits:
		 * We करोn't need all the bits, but rest of the bits
		 * must be ignored by the processor.
		 * vpn cover upto 65 bits of va. (0...65) and we need
		 * 58..64 bits of va.
		 */
		va |= (vpn & 0xfe); /* AVAL */
		va |= 1; /* L */
		यंत्र अस्थिर(ASM_FTR_IFCLR("tlbie %0,1", PPC_TLBIE(%1,%0), %2)
			     : : "r" (va), "r"(0), "i" (CPU_FTR_ARCH_206)
			     : "memory");
		अवरोध;
	पूर्ण
	वापस va;
पूर्ण

अटल अंतरभूत व्योम fixup_tlbie_vpn(अचिन्हित दीर्घ vpn, पूर्णांक psize,
				   पूर्णांक apsize, पूर्णांक ssize)
अणु
	अगर (cpu_has_feature(CPU_FTR_P9_TLBIE_ERAT_BUG)) अणु
		/* Radix flush क्रम a hash guest */

		अचिन्हित दीर्घ rb,rs,prs,r,ric;

		rb = PPC_BIT(52); /* IS = 2 */
		rs = 0;  /* lpid = 0 */
		prs = 0; /* partition scoped */
		r = 1;   /* radix क्रमmat */
		ric = 0; /* RIC_FLSUH_TLB */

		/*
		 * Need the extra ptesync to make sure we करोn't
		 * re-order the tlbie
		 */
		यंत्र अस्थिर("ptesync": : :"memory");
		यंत्र अस्थिर(PPC_TLBIE_5(%0, %4, %3, %2, %1)
			     : : "r"(rb), "i"(r), "i"(prs),
			       "i"(ric), "r"(rs) : "memory");
	पूर्ण


	अगर (cpu_has_feature(CPU_FTR_P9_TLBIE_STQ_BUG)) अणु
		/* Need the extra ptesync to ensure we करोn't reorder tlbie*/
		यंत्र अस्थिर("ptesync": : :"memory");
		___tlbie(vpn, psize, apsize, ssize);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम __tlbie(अचिन्हित दीर्घ vpn, पूर्णांक psize, पूर्णांक apsize, पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ rb;

	rb = ___tlbie(vpn, psize, apsize, ssize);
	trace_tlbie(0, 0, rb, 0, 0, 0, 0);
पूर्ण

अटल अंतरभूत व्योम __tlbiel(अचिन्हित दीर्घ vpn, पूर्णांक psize, पूर्णांक apsize, पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ va;
	अचिन्हित पूर्णांक penc;
	अचिन्हित दीर्घ sllp;

	/* VPN_SHIFT can be aपंचांगost 12 */
	va = vpn << VPN_SHIFT;
	/*
	 * clear top 16 bits of 64 bit va, non SLS segment
	 * Older versions of the architecture (2.02 and earler) require the
	 * masking of the top 16 bits.
	 */
	अगर (mmu_has_feature(MMU_FTR_TLBIE_CROP_VA))
		va &= ~(0xffffULL << 48);

	चयन (psize) अणु
	हाल MMU_PAGE_4K:
		/* clear out bits after(52) [0....52.....63] */
		va &= ~((1ul << (64 - 52)) - 1);
		va |= ssize << 8;
		sllp = get_sllp_encoding(apsize);
		va |= sllp << 5;
		यंत्र अस्थिर(ASM_FTR_IFSET("tlbiel %0", "tlbiel %0,0", %1)
			     : : "r" (va), "i" (CPU_FTR_ARCH_206)
			     : "memory");
		अवरोध;
	शेष:
		/* We need 14 to 14 + i bits of va */
		penc = mmu_psize_defs[psize].penc[apsize];
		va &= ~((1ul << mmu_psize_defs[apsize].shअगरt) - 1);
		va |= penc << 12;
		va |= ssize << 8;
		/*
		 * AVAL bits:
		 * We करोn't need all the bits, but rest of the bits
		 * must be ignored by the processor.
		 * vpn cover upto 65 bits of va. (0...65) and we need
		 * 58..64 bits of va.
		 */
		va |= (vpn & 0xfe);
		va |= 1; /* L */
		यंत्र अस्थिर(ASM_FTR_IFSET("tlbiel %0", "tlbiel %0,1", %1)
			     : : "r" (va), "i" (CPU_FTR_ARCH_206)
			     : "memory");
		अवरोध;
	पूर्ण
	trace_tlbie(0, 1, va, 0, 0, 0, 0);

पूर्ण

अटल अंतरभूत व्योम tlbie(अचिन्हित दीर्घ vpn, पूर्णांक psize, पूर्णांक apsize,
			 पूर्णांक ssize, पूर्णांक local)
अणु
	अचिन्हित पूर्णांक use_local;
	पूर्णांक lock_tlbie = !mmu_has_feature(MMU_FTR_LOCKLESS_TLBIE);

	use_local = local && mmu_has_feature(MMU_FTR_TLBIEL) && !cxl_ctx_in_use();

	अगर (use_local)
		use_local = mmu_psize_defs[psize].tlbiel;
	अगर (lock_tlbie && !use_local)
		raw_spin_lock(&native_tlbie_lock);
	यंत्र अस्थिर("ptesync": : :"memory");
	अगर (use_local) अणु
		__tlbiel(vpn, psize, apsize, ssize);
		ppc_after_tlbiel_barrier();
	पूर्ण अन्यथा अणु
		__tlbie(vpn, psize, apsize, ssize);
		fixup_tlbie_vpn(vpn, psize, apsize, ssize);
		यंत्र अस्थिर("eieio; tlbsync; ptesync": : :"memory");
	पूर्ण
	अगर (lock_tlbie && !use_local)
		raw_spin_unlock(&native_tlbie_lock);
पूर्ण

अटल अंतरभूत व्योम native_lock_hpte(काष्ठा hash_pte *hptep)
अणु
	अचिन्हित दीर्घ *word = (अचिन्हित दीर्घ *)&hptep->v;

	जबतक (1) अणु
		अगर (!test_and_set_bit_lock(HPTE_LOCK_BIT, word))
			अवरोध;
		spin_begin();
		जबतक(test_bit(HPTE_LOCK_BIT, word))
			spin_cpu_relax();
		spin_end();
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम native_unlock_hpte(काष्ठा hash_pte *hptep)
अणु
	अचिन्हित दीर्घ *word = (अचिन्हित दीर्घ *)&hptep->v;

	clear_bit_unlock(HPTE_LOCK_BIT, word);
पूर्ण

अटल दीर्घ native_hpte_insert(अचिन्हित दीर्घ hpte_group, अचिन्हित दीर्घ vpn,
			अचिन्हित दीर्घ pa, अचिन्हित दीर्घ rflags,
			अचिन्हित दीर्घ vflags, पूर्णांक psize, पूर्णांक apsize, पूर्णांक ssize)
अणु
	काष्ठा hash_pte *hptep = htab_address + hpte_group;
	अचिन्हित दीर्घ hpte_v, hpte_r;
	पूर्णांक i;

	अगर (!(vflags & HPTE_V_BOLTED)) अणु
		DBG_LOW("    insert(group=%lx, vpn=%016lx, pa=%016lx,"
			" rflags=%lx, vflags=%lx, psize=%d)\n",
			hpte_group, vpn, pa, rflags, vflags, psize);
	पूर्ण

	क्रम (i = 0; i < HPTES_PER_GROUP; i++) अणु
		अगर (! (be64_to_cpu(hptep->v) & HPTE_V_VALID)) अणु
			/* retry with lock held */
			native_lock_hpte(hptep);
			अगर (! (be64_to_cpu(hptep->v) & HPTE_V_VALID))
				अवरोध;
			native_unlock_hpte(hptep);
		पूर्ण

		hptep++;
	पूर्ण

	अगर (i == HPTES_PER_GROUP)
		वापस -1;

	hpte_v = hpte_encode_v(vpn, psize, apsize, ssize) | vflags | HPTE_V_VALID;
	hpte_r = hpte_encode_r(pa, psize, apsize) | rflags;

	अगर (!(vflags & HPTE_V_BOLTED)) अणु
		DBG_LOW(" i=%x hpte_v=%016lx, hpte_r=%016lx\n",
			i, hpte_v, hpte_r);
	पूर्ण

	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		hpte_r = hpte_old_to_new_r(hpte_v, hpte_r);
		hpte_v = hpte_old_to_new_v(hpte_v);
	पूर्ण

	hptep->r = cpu_to_be64(hpte_r);
	/* Guarantee the second dword is visible beक्रमe the valid bit */
	eieio();
	/*
	 * Now set the first dword including the valid bit
	 * NOTE: this also unlocks the hpte
	 */
	hptep->v = cpu_to_be64(hpte_v);

	__यंत्र__ __अस्थिर__ ("ptesync" : : : "memory");

	वापस i | (!!(vflags & HPTE_V_SECONDARY) << 3);
पूर्ण

अटल दीर्घ native_hpte_हटाओ(अचिन्हित दीर्घ hpte_group)
अणु
	काष्ठा hash_pte *hptep;
	पूर्णांक i;
	पूर्णांक slot_offset;
	अचिन्हित दीर्घ hpte_v;

	DBG_LOW("    remove(group=%lx)\n", hpte_group);

	/* pick a अक्रमom entry to start at */
	slot_offset = mftb() & 0x7;

	क्रम (i = 0; i < HPTES_PER_GROUP; i++) अणु
		hptep = htab_address + hpte_group + slot_offset;
		hpte_v = be64_to_cpu(hptep->v);

		अगर ((hpte_v & HPTE_V_VALID) && !(hpte_v & HPTE_V_BOLTED)) अणु
			/* retry with lock held */
			native_lock_hpte(hptep);
			hpte_v = be64_to_cpu(hptep->v);
			अगर ((hpte_v & HPTE_V_VALID)
			    && !(hpte_v & HPTE_V_BOLTED))
				अवरोध;
			native_unlock_hpte(hptep);
		पूर्ण

		slot_offset++;
		slot_offset &= 0x7;
	पूर्ण

	अगर (i == HPTES_PER_GROUP)
		वापस -1;

	/* Invalidate the hpte. NOTE: this also unlocks it */
	hptep->v = 0;

	वापस i;
पूर्ण

अटल दीर्घ native_hpte_updatepp(अचिन्हित दीर्घ slot, अचिन्हित दीर्घ newpp,
				 अचिन्हित दीर्घ vpn, पूर्णांक bpsize,
				 पूर्णांक apsize, पूर्णांक ssize, अचिन्हित दीर्घ flags)
अणु
	काष्ठा hash_pte *hptep = htab_address + slot;
	अचिन्हित दीर्घ hpte_v, want_v;
	पूर्णांक ret = 0, local = 0;

	want_v = hpte_encode_avpn(vpn, bpsize, ssize);

	DBG_LOW("    update(vpn=%016lx, avpnv=%016lx, group=%lx, newpp=%lx)",
		vpn, want_v & HPTE_V_AVPN, slot, newpp);

	hpte_v = hpte_get_old_v(hptep);
	/*
	 * We need to invalidate the TLB always because hpte_हटाओ करोesn't करो
	 * a tlb invalidate. If a hash bucket माला_लो full, we "evict" a more/less
	 * अक्रमom entry from it. When we करो that we करोn't invalidate the TLB
	 * (hpte_हटाओ) because we assume the old translation is still
	 * technically "valid".
	 */
	अगर (!HPTE_V_COMPARE(hpte_v, want_v) || !(hpte_v & HPTE_V_VALID)) अणु
		DBG_LOW(" -> miss\n");
		ret = -1;
	पूर्ण अन्यथा अणु
		native_lock_hpte(hptep);
		/* recheck with locks held */
		hpte_v = hpte_get_old_v(hptep);
		अगर (unlikely(!HPTE_V_COMPARE(hpte_v, want_v) ||
			     !(hpte_v & HPTE_V_VALID))) अणु
			ret = -1;
		पूर्ण अन्यथा अणु
			DBG_LOW(" -> hit\n");
			/* Update the HPTE */
			hptep->r = cpu_to_be64((be64_to_cpu(hptep->r) &
						~(HPTE_R_PPP | HPTE_R_N)) |
					       (newpp & (HPTE_R_PPP | HPTE_R_N |
							 HPTE_R_C)));
		पूर्ण
		native_unlock_hpte(hptep);
	पूर्ण

	अगर (flags & HPTE_LOCAL_UPDATE)
		local = 1;
	/*
	 * Ensure it is out of the tlb too अगर it is not a nohpte fault
	 */
	अगर (!(flags & HPTE_NOHPTE_UPDATE))
		tlbie(vpn, bpsize, apsize, ssize, local);

	वापस ret;
पूर्ण

अटल दीर्घ __native_hpte_find(अचिन्हित दीर्घ want_v, अचिन्हित दीर्घ slot)
अणु
	काष्ठा hash_pte *hptep;
	अचिन्हित दीर्घ hpte_v;
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < HPTES_PER_GROUP; i++) अणु

		hptep = htab_address + slot;
		hpte_v = hpte_get_old_v(hptep);
		अगर (HPTE_V_COMPARE(hpte_v, want_v) && (hpte_v & HPTE_V_VALID))
			/* HPTE matches */
			वापस slot;
		++slot;
	पूर्ण

	वापस -1;
पूर्ण

अटल दीर्घ native_hpte_find(अचिन्हित दीर्घ vpn, पूर्णांक psize, पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ hpte_group;
	अचिन्हित दीर्घ want_v;
	अचिन्हित दीर्घ hash;
	दीर्घ slot;

	hash = hpt_hash(vpn, mmu_psize_defs[psize].shअगरt, ssize);
	want_v = hpte_encode_avpn(vpn, psize, ssize);

	/*
	 * We try to keep bolted entries always in primary hash
	 * But in some हाल we can find them in secondary too.
	 */
	hpte_group = (hash & htab_hash_mask) * HPTES_PER_GROUP;
	slot = __native_hpte_find(want_v, hpte_group);
	अगर (slot < 0) अणु
		/* Try in secondary */
		hpte_group = (~hash & htab_hash_mask) * HPTES_PER_GROUP;
		slot = __native_hpte_find(want_v, hpte_group);
		अगर (slot < 0)
			वापस -1;
	पूर्ण

	वापस slot;
पूर्ण

/*
 * Update the page protection bits. Intended to be used to create
 * guard pages क्रम kernel data काष्ठाures on pages which are bolted
 * in the HPT. Assumes pages being operated on will not be stolen.
 *
 * No need to lock here because we should be the only user.
 */
अटल व्योम native_hpte_updateboltedpp(अचिन्हित दीर्घ newpp, अचिन्हित दीर्घ ea,
				       पूर्णांक psize, पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ vpn;
	अचिन्हित दीर्घ vsid;
	दीर्घ slot;
	काष्ठा hash_pte *hptep;

	vsid = get_kernel_vsid(ea, ssize);
	vpn = hpt_vpn(ea, vsid, ssize);

	slot = native_hpte_find(vpn, psize, ssize);
	अगर (slot == -1)
		panic("could not find page to bolt\n");
	hptep = htab_address + slot;

	/* Update the HPTE */
	hptep->r = cpu_to_be64((be64_to_cpu(hptep->r) &
				~(HPTE_R_PPP | HPTE_R_N)) |
			       (newpp & (HPTE_R_PPP | HPTE_R_N)));
	/*
	 * Ensure it is out of the tlb too. Bolted entries base and
	 * actual page size will be same.
	 */
	tlbie(vpn, psize, psize, ssize, 0);
पूर्ण

/*
 * Remove a bolted kernel entry. Memory hotplug uses this.
 *
 * No need to lock here because we should be the only user.
 */
अटल पूर्णांक native_hpte_हटाओbolted(अचिन्हित दीर्घ ea, पूर्णांक psize, पूर्णांक ssize)
अणु
	अचिन्हित दीर्घ vpn;
	अचिन्हित दीर्घ vsid;
	दीर्घ slot;
	काष्ठा hash_pte *hptep;

	vsid = get_kernel_vsid(ea, ssize);
	vpn = hpt_vpn(ea, vsid, ssize);

	slot = native_hpte_find(vpn, psize, ssize);
	अगर (slot == -1)
		वापस -ENOENT;

	hptep = htab_address + slot;

	VM_WARN_ON(!(be64_to_cpu(hptep->v) & HPTE_V_BOLTED));

	/* Invalidate the hpte */
	hptep->v = 0;

	/* Invalidate the TLB */
	tlbie(vpn, psize, psize, ssize, 0);
	वापस 0;
पूर्ण


अटल व्योम native_hpte_invalidate(अचिन्हित दीर्घ slot, अचिन्हित दीर्घ vpn,
				   पूर्णांक bpsize, पूर्णांक apsize, पूर्णांक ssize, पूर्णांक local)
अणु
	काष्ठा hash_pte *hptep = htab_address + slot;
	अचिन्हित दीर्घ hpte_v;
	अचिन्हित दीर्घ want_v;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	DBG_LOW("    invalidate(vpn=%016lx, hash: %lx)\n", vpn, slot);

	want_v = hpte_encode_avpn(vpn, bpsize, ssize);
	hpte_v = hpte_get_old_v(hptep);

	अगर (HPTE_V_COMPARE(hpte_v, want_v) && (hpte_v & HPTE_V_VALID)) अणु
		native_lock_hpte(hptep);
		/* recheck with locks held */
		hpte_v = hpte_get_old_v(hptep);

		अगर (HPTE_V_COMPARE(hpte_v, want_v) && (hpte_v & HPTE_V_VALID))
			/* Invalidate the hpte. NOTE: this also unlocks it */
			hptep->v = 0;
		अन्यथा
			native_unlock_hpte(hptep);
	पूर्ण
	/*
	 * We need to invalidate the TLB always because hpte_हटाओ करोesn't करो
	 * a tlb invalidate. If a hash bucket माला_लो full, we "evict" a more/less
	 * अक्रमom entry from it. When we करो that we करोn't invalidate the TLB
	 * (hpte_हटाओ) because we assume the old translation is still
	 * technically "valid".
	 */
	tlbie(vpn, bpsize, apsize, ssize, local);

	local_irq_restore(flags);
पूर्ण

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
अटल व्योम native_hugepage_invalidate(अचिन्हित दीर्घ vsid,
				       अचिन्हित दीर्घ addr,
				       अचिन्हित अक्षर *hpte_slot_array,
				       पूर्णांक psize, पूर्णांक ssize, पूर्णांक local)
अणु
	पूर्णांक i;
	काष्ठा hash_pte *hptep;
	पूर्णांक actual_psize = MMU_PAGE_16M;
	अचिन्हित पूर्णांक max_hpte_count, valid;
	अचिन्हित दीर्घ flags, s_addr = addr;
	अचिन्हित दीर्घ hpte_v, want_v, shअगरt;
	अचिन्हित दीर्घ hidx, vpn = 0, hash, slot;

	shअगरt = mmu_psize_defs[psize].shअगरt;
	max_hpte_count = 1U << (PMD_SHIFT - shअगरt);

	local_irq_save(flags);
	क्रम (i = 0; i < max_hpte_count; i++) अणु
		valid = hpte_valid(hpte_slot_array, i);
		अगर (!valid)
			जारी;
		hidx =  hpte_hash_index(hpte_slot_array, i);

		/* get the vpn */
		addr = s_addr + (i * (1ul << shअगरt));
		vpn = hpt_vpn(addr, vsid, ssize);
		hash = hpt_hash(vpn, shअगरt, ssize);
		अगर (hidx & _PTEIDX_SECONDARY)
			hash = ~hash;

		slot = (hash & htab_hash_mask) * HPTES_PER_GROUP;
		slot += hidx & _PTEIDX_GROUP_IX;

		hptep = htab_address + slot;
		want_v = hpte_encode_avpn(vpn, psize, ssize);
		hpte_v = hpte_get_old_v(hptep);

		/* Even अगर we miss, we need to invalidate the TLB */
		अगर (HPTE_V_COMPARE(hpte_v, want_v) && (hpte_v & HPTE_V_VALID)) अणु
			/* recheck with locks held */
			native_lock_hpte(hptep);
			hpte_v = hpte_get_old_v(hptep);

			अगर (HPTE_V_COMPARE(hpte_v, want_v) && (hpte_v & HPTE_V_VALID)) अणु
				/*
				 * Invalidate the hpte. NOTE: this also unlocks it
				 */

				hptep->v = 0;
			पूर्ण अन्यथा
				native_unlock_hpte(hptep);
		पूर्ण
		/*
		 * We need to करो tlb invalidate क्रम all the address, tlbie
		 * inकाष्ठाion compares entry_VA in tlb with the VA specअगरied
		 * here
		 */
		tlbie(vpn, psize, actual_psize, ssize, local);
	पूर्ण
	local_irq_restore(flags);
पूर्ण
#अन्यथा
अटल व्योम native_hugepage_invalidate(अचिन्हित दीर्घ vsid,
				       अचिन्हित दीर्घ addr,
				       अचिन्हित अक्षर *hpte_slot_array,
				       पूर्णांक psize, पूर्णांक ssize, पूर्णांक local)
अणु
	WARN(1, "%s called without THP support\n", __func__);
पूर्ण
#पूर्ण_अगर

अटल व्योम hpte_decode(काष्ठा hash_pte *hpte, अचिन्हित दीर्घ slot,
			पूर्णांक *psize, पूर्णांक *apsize, पूर्णांक *ssize, अचिन्हित दीर्घ *vpn)
अणु
	अचिन्हित दीर्घ avpn, pteg, vpi;
	अचिन्हित दीर्घ hpte_v = be64_to_cpu(hpte->v);
	अचिन्हित दीर्घ hpte_r = be64_to_cpu(hpte->r);
	अचिन्हित दीर्घ vsid, seg_off;
	पूर्णांक size, a_size, shअगरt;
	/* Look at the 8 bit LP value */
	अचिन्हित पूर्णांक lp = (hpte_r >> LP_SHIFT) & ((1 << LP_BITS) - 1);

	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		hpte_v = hpte_new_to_old_v(hpte_v, hpte_r);
		hpte_r = hpte_new_to_old_r(hpte_r);
	पूर्ण
	अगर (!(hpte_v & HPTE_V_LARGE)) अणु
		size   = MMU_PAGE_4K;
		a_size = MMU_PAGE_4K;
	पूर्ण अन्यथा अणु
		size = hpte_page_sizes[lp] & 0xf;
		a_size = hpte_page_sizes[lp] >> 4;
	पूर्ण
	/* This works क्रम all page sizes, and क्रम 256M and 1T segments */
	*ssize = hpte_v >> HPTE_V_SSIZE_SHIFT;
	shअगरt = mmu_psize_defs[size].shअगरt;

	avpn = (HPTE_V_AVPN_VAL(hpte_v) & ~mmu_psize_defs[size].avpnm);
	pteg = slot / HPTES_PER_GROUP;
	अगर (hpte_v & HPTE_V_SECONDARY)
		pteg = ~pteg;

	चयन (*ssize) अणु
	हाल MMU_SEGSIZE_256M:
		/* We only have 28 - 23 bits of seg_off in avpn */
		seg_off = (avpn & 0x1f) << 23;
		vsid    =  avpn >> 5;
		/* We can find more bits from the pteg value */
		अगर (shअगरt < 23) अणु
			vpi = (vsid ^ pteg) & htab_hash_mask;
			seg_off |= vpi << shअगरt;
		पूर्ण
		*vpn = vsid << (SID_SHIFT - VPN_SHIFT) | seg_off >> VPN_SHIFT;
		अवरोध;
	हाल MMU_SEGSIZE_1T:
		/* We only have 40 - 23 bits of seg_off in avpn */
		seg_off = (avpn & 0x1ffff) << 23;
		vsid    = avpn >> 17;
		अगर (shअगरt < 23) अणु
			vpi = (vsid ^ (vsid << 25) ^ pteg) & htab_hash_mask;
			seg_off |= vpi << shअगरt;
		पूर्ण
		*vpn = vsid << (SID_SHIFT_1T - VPN_SHIFT) | seg_off >> VPN_SHIFT;
		अवरोध;
	शेष:
		*vpn = size = 0;
	पूर्ण
	*psize  = size;
	*apsize = a_size;
पूर्ण

/*
 * clear all mappings on kexec.  All cpus are in real mode (or they will
 * be when they isi), and we are the only one left.  We rely on our kernel
 * mapping being 0xC0's and the hardware ignoring those two real bits.
 *
 * This must be called with पूर्णांकerrupts disabled.
 *
 * Taking the native_tlbie_lock is unsafe here due to the possibility of
 * lockdep being on. On pre POWER5 hardware, not taking the lock could
 * cause deadlock. POWER5 and newer not taking the lock is fine. This only
 * माला_लो called during boot beक्रमe secondary CPUs have come up and during
 * crashdump and all bets are off anyway.
 *
 * TODO: add batching support when enabled.  remember, no dynamic memory here,
 * although there is the control page available...
 */
अटल व्योम native_hpte_clear(व्योम)
अणु
	अचिन्हित दीर्घ vpn = 0;
	अचिन्हित दीर्घ slot, slots;
	काष्ठा hash_pte *hptep = htab_address;
	अचिन्हित दीर्घ hpte_v;
	अचिन्हित दीर्घ pteg_count;
	पूर्णांक psize, apsize, ssize;

	pteg_count = htab_hash_mask + 1;

	slots = pteg_count * HPTES_PER_GROUP;

	क्रम (slot = 0; slot < slots; slot++, hptep++) अणु
		/*
		 * we could lock the pte here, but we are the only cpu
		 * running,  right?  and क्रम crash dump, we probably
		 * करोn't want to रुको क्रम a maybe bad cpu.
		 */
		hpte_v = be64_to_cpu(hptep->v);

		/*
		 * Call __tlbie() here rather than tlbie() since we can't take the
		 * native_tlbie_lock.
		 */
		अगर (hpte_v & HPTE_V_VALID) अणु
			hpte_decode(hptep, slot, &psize, &apsize, &ssize, &vpn);
			hptep->v = 0;
			___tlbie(vpn, psize, apsize, ssize);
		पूर्ण
	पूर्ण

	यंत्र अस्थिर("eieio; tlbsync; ptesync":::"memory");
पूर्ण

/*
 * Batched hash table flush, we batch the tlbie's to aव्योम taking/releasing
 * the lock all the समय
 */
अटल व्योम native_flush_hash_range(अचिन्हित दीर्घ number, पूर्णांक local)
अणु
	अचिन्हित दीर्घ vpn = 0;
	अचिन्हित दीर्घ hash, index, hidx, shअगरt, slot;
	काष्ठा hash_pte *hptep;
	अचिन्हित दीर्घ hpte_v;
	अचिन्हित दीर्घ want_v;
	अचिन्हित दीर्घ flags;
	real_pte_t pte;
	काष्ठा ppc64_tlb_batch *batch = this_cpu_ptr(&ppc64_tlb_batch);
	अचिन्हित दीर्घ psize = batch->psize;
	पूर्णांक ssize = batch->ssize;
	पूर्णांक i;
	अचिन्हित पूर्णांक use_local;

	use_local = local && mmu_has_feature(MMU_FTR_TLBIEL) &&
		mmu_psize_defs[psize].tlbiel && !cxl_ctx_in_use();

	local_irq_save(flags);

	क्रम (i = 0; i < number; i++) अणु
		vpn = batch->vpn[i];
		pte = batch->pte[i];

		pte_iterate_hashed_subpages(pte, psize, vpn, index, shअगरt) अणु
			hash = hpt_hash(vpn, shअगरt, ssize);
			hidx = __rpte_to_hidx(pte, index);
			अगर (hidx & _PTEIDX_SECONDARY)
				hash = ~hash;
			slot = (hash & htab_hash_mask) * HPTES_PER_GROUP;
			slot += hidx & _PTEIDX_GROUP_IX;
			hptep = htab_address + slot;
			want_v = hpte_encode_avpn(vpn, psize, ssize);
			hpte_v = hpte_get_old_v(hptep);

			अगर (!HPTE_V_COMPARE(hpte_v, want_v) || !(hpte_v & HPTE_V_VALID))
				जारी;
			/* lock and try again */
			native_lock_hpte(hptep);
			hpte_v = hpte_get_old_v(hptep);

			अगर (!HPTE_V_COMPARE(hpte_v, want_v) || !(hpte_v & HPTE_V_VALID))
				native_unlock_hpte(hptep);
			अन्यथा
				hptep->v = 0;

		पूर्ण pte_iterate_hashed_end();
	पूर्ण

	अगर (use_local) अणु
		यंत्र अस्थिर("ptesync":::"memory");
		क्रम (i = 0; i < number; i++) अणु
			vpn = batch->vpn[i];
			pte = batch->pte[i];

			pte_iterate_hashed_subpages(pte, psize,
						    vpn, index, shअगरt) अणु
				__tlbiel(vpn, psize, psize, ssize);
			पूर्ण pte_iterate_hashed_end();
		पूर्ण
		ppc_after_tlbiel_barrier();
	पूर्ण अन्यथा अणु
		पूर्णांक lock_tlbie = !mmu_has_feature(MMU_FTR_LOCKLESS_TLBIE);

		अगर (lock_tlbie)
			raw_spin_lock(&native_tlbie_lock);

		यंत्र अस्थिर("ptesync":::"memory");
		क्रम (i = 0; i < number; i++) अणु
			vpn = batch->vpn[i];
			pte = batch->pte[i];

			pte_iterate_hashed_subpages(pte, psize,
						    vpn, index, shअगरt) अणु
				__tlbie(vpn, psize, psize, ssize);
			पूर्ण pte_iterate_hashed_end();
		पूर्ण
		/*
		 * Just करो one more with the last used values.
		 */
		fixup_tlbie_vpn(vpn, psize, psize, ssize);
		यंत्र अस्थिर("eieio; tlbsync; ptesync":::"memory");

		अगर (lock_tlbie)
			raw_spin_unlock(&native_tlbie_lock);
	पूर्ण

	local_irq_restore(flags);
पूर्ण

व्योम __init hpte_init_native(व्योम)
अणु
	mmu_hash_ops.hpte_invalidate	= native_hpte_invalidate;
	mmu_hash_ops.hpte_updatepp	= native_hpte_updatepp;
	mmu_hash_ops.hpte_updateboltedpp = native_hpte_updateboltedpp;
	mmu_hash_ops.hpte_हटाओbolted = native_hpte_हटाओbolted;
	mmu_hash_ops.hpte_insert	= native_hpte_insert;
	mmu_hash_ops.hpte_हटाओ	= native_hpte_हटाओ;
	mmu_hash_ops.hpte_clear_all	= native_hpte_clear;
	mmu_hash_ops.flush_hash_range = native_flush_hash_range;
	mmu_hash_ops.hugepage_invalidate   = native_hugepage_invalidate;
पूर्ण
