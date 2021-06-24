<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright 2010-2011 Paul Mackerras, IBM Corp. <paulus@au1.ibm.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/module.h>
#समावेश <linux/log2.h>
#समावेश <linux/sizes.h>

#समावेश <यंत्र/trace.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/book3s/64/mmu-hash.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/synch.h>
#समावेश <यंत्र/ppc-opcode.h>
#समावेश <यंत्र/pte-walk.h>

/* Translate address of a vदो_स्मृति'd thing to a linear map address */
अटल व्योम *real_vदो_स्मृति_addr(व्योम *addr)
अणु
	वापस __va(ppc_find_vmap_phys((अचिन्हित दीर्घ)addr));
पूर्ण

/* Return 1 अगर we need to करो a global tlbie, 0 अगर we can use tlbiel */
अटल पूर्णांक global_invalidates(काष्ठा kvm *kvm)
अणु
	पूर्णांक global;
	पूर्णांक cpu;

	/*
	 * If there is only one vcore, and it's currently running,
	 * as indicated by local_paca->kvm_hstate.kvm_vcpu being set,
	 * we can use tlbiel as दीर्घ as we mark all other physical
	 * cores as potentially having stale TLB entries क्रम this lpid.
	 * Otherwise, करोn't use tlbiel.
	 */
	अगर (kvm->arch.online_vcores == 1 && local_paca->kvm_hstate.kvm_vcpu)
		global = 0;
	अन्यथा
		global = 1;

	अगर (!global) अणु
		/* any other core might now have stale TLB entries... */
		smp_wmb();
		cpumask_setall(&kvm->arch.need_tlb_flush);
		cpu = local_paca->kvm_hstate.kvm_vcore->pcpu;
		/*
		 * On POWER9, thपढ़ोs are independent but the TLB is shared,
		 * so use the bit क्रम the first thपढ़ो to represent the core.
		 */
		अगर (cpu_has_feature(CPU_FTR_ARCH_300))
			cpu = cpu_first_thपढ़ो_sibling(cpu);
		cpumask_clear_cpu(cpu, &kvm->arch.need_tlb_flush);
	पूर्ण

	वापस global;
पूर्ण

/*
 * Add this HPTE पूर्णांकo the chain क्रम the real page.
 * Must be called with the chain locked; it unlocks the chain.
 */
व्योम kvmppc_add_revmap_chain(काष्ठा kvm *kvm, काष्ठा revmap_entry *rev,
			     अचिन्हित दीर्घ *rmap, दीर्घ pte_index, पूर्णांक realmode)
अणु
	काष्ठा revmap_entry *head, *tail;
	अचिन्हित दीर्घ i;

	अगर (*rmap & KVMPPC_RMAP_PRESENT) अणु
		i = *rmap & KVMPPC_RMAP_INDEX;
		head = &kvm->arch.hpt.rev[i];
		अगर (realmode)
			head = real_vदो_स्मृति_addr(head);
		tail = &kvm->arch.hpt.rev[head->back];
		अगर (realmode)
			tail = real_vदो_स्मृति_addr(tail);
		rev->क्रमw = i;
		rev->back = head->back;
		tail->क्रमw = pte_index;
		head->back = pte_index;
	पूर्ण अन्यथा अणु
		rev->क्रमw = rev->back = pte_index;
		*rmap = (*rmap & ~KVMPPC_RMAP_INDEX) |
			pte_index | KVMPPC_RMAP_PRESENT | KVMPPC_RMAP_HPT;
	पूर्ण
	unlock_rmap(rmap);
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_add_revmap_chain);

/* Update the dirty biपंचांगap of a memslot */
व्योम kvmppc_update_dirty_map(स्थिर काष्ठा kvm_memory_slot *memslot,
			     अचिन्हित दीर्घ gfn, अचिन्हित दीर्घ psize)
अणु
	अचिन्हित दीर्घ npages;

	अगर (!psize || !memslot->dirty_biपंचांगap)
		वापस;
	npages = (psize + PAGE_SIZE - 1) / PAGE_SIZE;
	gfn -= memslot->base_gfn;
	set_dirty_bits_atomic(memslot->dirty_biपंचांगap, gfn, npages);
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_update_dirty_map);

अटल व्योम kvmppc_set_dirty_from_hpte(काष्ठा kvm *kvm,
				अचिन्हित दीर्घ hpte_v, अचिन्हित दीर्घ hpte_gr)
अणु
	काष्ठा kvm_memory_slot *memslot;
	अचिन्हित दीर्घ gfn;
	अचिन्हित दीर्घ psize;

	psize = kvmppc_actual_pgsz(hpte_v, hpte_gr);
	gfn = hpte_rpn(hpte_gr, psize);
	memslot = __gfn_to_memslot(kvm_memslots_raw(kvm), gfn);
	अगर (memslot && memslot->dirty_biपंचांगap)
		kvmppc_update_dirty_map(memslot, gfn, psize);
पूर्ण

/* Returns a poपूर्णांकer to the revmap entry क्रम the page mapped by a HPTE */
अटल अचिन्हित दीर्घ *revmap_क्रम_hpte(काष्ठा kvm *kvm, अचिन्हित दीर्घ hpte_v,
				      अचिन्हित दीर्घ hpte_gr,
				      काष्ठा kvm_memory_slot **memslotp,
				      अचिन्हित दीर्घ *gfnp)
अणु
	काष्ठा kvm_memory_slot *memslot;
	अचिन्हित दीर्घ *rmap;
	अचिन्हित दीर्घ gfn;

	gfn = hpte_rpn(hpte_gr, kvmppc_actual_pgsz(hpte_v, hpte_gr));
	memslot = __gfn_to_memslot(kvm_memslots_raw(kvm), gfn);
	अगर (memslotp)
		*memslotp = memslot;
	अगर (gfnp)
		*gfnp = gfn;
	अगर (!memslot)
		वापस शून्य;

	rmap = real_vदो_स्मृति_addr(&memslot->arch.rmap[gfn - memslot->base_gfn]);
	वापस rmap;
पूर्ण

/* Remove this HPTE from the chain क्रम a real page */
अटल व्योम हटाओ_revmap_chain(काष्ठा kvm *kvm, दीर्घ pte_index,
				काष्ठा revmap_entry *rev,
				अचिन्हित दीर्घ hpte_v, अचिन्हित दीर्घ hpte_r)
अणु
	काष्ठा revmap_entry *next, *prev;
	अचिन्हित दीर्घ ptel, head;
	अचिन्हित दीर्घ *rmap;
	अचिन्हित दीर्घ rcbits;
	काष्ठा kvm_memory_slot *memslot;
	अचिन्हित दीर्घ gfn;

	rcbits = hpte_r & (HPTE_R_R | HPTE_R_C);
	ptel = rev->guest_rpte |= rcbits;
	rmap = revmap_क्रम_hpte(kvm, hpte_v, ptel, &memslot, &gfn);
	अगर (!rmap)
		वापस;
	lock_rmap(rmap);

	head = *rmap & KVMPPC_RMAP_INDEX;
	next = real_vदो_स्मृति_addr(&kvm->arch.hpt.rev[rev->क्रमw]);
	prev = real_vदो_स्मृति_addr(&kvm->arch.hpt.rev[rev->back]);
	next->back = rev->back;
	prev->क्रमw = rev->क्रमw;
	अगर (head == pte_index) अणु
		head = rev->क्रमw;
		अगर (head == pte_index)
			*rmap &= ~(KVMPPC_RMAP_PRESENT | KVMPPC_RMAP_INDEX);
		अन्यथा
			*rmap = (*rmap & ~KVMPPC_RMAP_INDEX) | head;
	पूर्ण
	*rmap |= rcbits << KVMPPC_RMAP_RC_SHIFT;
	अगर (rcbits & HPTE_R_C)
		kvmppc_update_dirty_map(memslot, gfn,
					kvmppc_actual_pgsz(hpte_v, hpte_r));
	unlock_rmap(rmap);
पूर्ण

दीर्घ kvmppc_करो_h_enter(काष्ठा kvm *kvm, अचिन्हित दीर्घ flags,
		       दीर्घ pte_index, अचिन्हित दीर्घ pteh, अचिन्हित दीर्घ ptel,
		       pgd_t *pgdir, bool realmode, अचिन्हित दीर्घ *pte_idx_ret)
अणु
	अचिन्हित दीर्घ i, pa, gpa, gfn, psize;
	अचिन्हित दीर्घ slot_fn, hva;
	__be64 *hpte;
	काष्ठा revmap_entry *rev;
	अचिन्हित दीर्घ g_ptel;
	काष्ठा kvm_memory_slot *memslot;
	अचिन्हित hpage_shअगरt;
	bool is_ci;
	अचिन्हित दीर्घ *rmap;
	pte_t *ptep;
	अचिन्हित पूर्णांक writing;
	अचिन्हित दीर्घ mmu_seq;
	अचिन्हित दीर्घ rcbits;

	अगर (kvm_is_radix(kvm))
		वापस H_FUNCTION;
	psize = kvmppc_actual_pgsz(pteh, ptel);
	अगर (!psize)
		वापस H_PARAMETER;
	writing = hpte_is_writable(ptel);
	pteh &= ~(HPTE_V_HVLOCK | HPTE_V_ABSENT | HPTE_V_VALID);
	ptel &= ~HPTE_GR_RESERVED;
	g_ptel = ptel;

	/* used later to detect अगर we might have been invalidated */
	mmu_seq = kvm->mmu_notअगरier_seq;
	smp_rmb();

	/* Find the memslot (अगर any) क्रम this address */
	gpa = (ptel & HPTE_R_RPN) & ~(psize - 1);
	gfn = gpa >> PAGE_SHIFT;
	memslot = __gfn_to_memslot(kvm_memslots_raw(kvm), gfn);
	pa = 0;
	is_ci = false;
	rmap = शून्य;
	अगर (!(memslot && !(memslot->flags & KVM_MEMSLOT_INVALID))) अणु
		/* Emulated MMIO - mark this with key=31 */
		pteh |= HPTE_V_ABSENT;
		ptel |= HPTE_R_KEY_HI | HPTE_R_KEY_LO;
		जाओ करो_insert;
	पूर्ण

	/* Check अगर the requested page fits entirely in the memslot. */
	अगर (!slot_is_aligned(memslot, psize))
		वापस H_PARAMETER;
	slot_fn = gfn - memslot->base_gfn;
	rmap = &memslot->arch.rmap[slot_fn];

	/* Translate to host भव address */
	hva = __gfn_to_hva_memslot(memslot, gfn);

	arch_spin_lock(&kvm->mmu_lock.rlock.raw_lock);
	ptep = find_kvm_host_pte(kvm, mmu_seq, hva, &hpage_shअगरt);
	अगर (ptep) अणु
		pte_t pte;
		अचिन्हित पूर्णांक host_pte_size;

		अगर (hpage_shअगरt)
			host_pte_size = 1ul << hpage_shअगरt;
		अन्यथा
			host_pte_size = PAGE_SIZE;
		/*
		 * We should always find the guest page size
		 * to <= host page size, अगर host is using hugepage
		 */
		अगर (host_pte_size < psize) अणु
			arch_spin_unlock(&kvm->mmu_lock.rlock.raw_lock);
			वापस H_PARAMETER;
		पूर्ण
		pte = kvmppc_पढ़ो_update_linux_pte(ptep, writing);
		अगर (pte_present(pte) && !pte_protnone(pte)) अणु
			अगर (writing && !__pte_ग_लिखो(pte))
				/* make the actual HPTE be पढ़ो-only */
				ptel = hpte_make_पढ़ोonly(ptel);
			is_ci = pte_ci(pte);
			pa = pte_pfn(pte) << PAGE_SHIFT;
			pa |= hva & (host_pte_size - 1);
			pa |= gpa & ~PAGE_MASK;
		पूर्ण
	पूर्ण
	arch_spin_unlock(&kvm->mmu_lock.rlock.raw_lock);

	ptel &= HPTE_R_KEY | HPTE_R_PP0 | (psize-1);
	ptel |= pa;

	अगर (pa)
		pteh |= HPTE_V_VALID;
	अन्यथा अणु
		pteh |= HPTE_V_ABSENT;
		ptel &= ~(HPTE_R_KEY_HI | HPTE_R_KEY_LO);
	पूर्ण

	/*If we had host pte mapping then  Check WIMG */
	अगर (ptep && !hpte_cache_flags_ok(ptel, is_ci)) अणु
		अगर (is_ci)
			वापस H_PARAMETER;
		/*
		 * Allow guest to map emulated device memory as
		 * uncacheable, but actually make it cacheable.
		 */
		ptel &= ~(HPTE_R_W|HPTE_R_I|HPTE_R_G);
		ptel |= HPTE_R_M;
	पूर्ण

	/* Find and lock the HPTEG slot to use */
 करो_insert:
	अगर (pte_index >= kvmppc_hpt_npte(&kvm->arch.hpt))
		वापस H_PARAMETER;
	अगर (likely((flags & H_EXACT) == 0)) अणु
		pte_index &= ~7UL;
		hpte = (__be64 *)(kvm->arch.hpt.virt + (pte_index << 4));
		क्रम (i = 0; i < 8; ++i) अणु
			अगर ((be64_to_cpu(*hpte) & HPTE_V_VALID) == 0 &&
			    try_lock_hpte(hpte, HPTE_V_HVLOCK | HPTE_V_VALID |
					  HPTE_V_ABSENT))
				अवरोध;
			hpte += 2;
		पूर्ण
		अगर (i == 8) अणु
			/*
			 * Since try_lock_hpte करोesn't retry (not even stdcx.
			 * failures), it could be that there is a मुक्त slot
			 * but we transiently failed to lock it.  Try again,
			 * actually locking each slot and checking it.
			 */
			hpte -= 16;
			क्रम (i = 0; i < 8; ++i) अणु
				u64 pte;
				जबतक (!try_lock_hpte(hpte, HPTE_V_HVLOCK))
					cpu_relax();
				pte = be64_to_cpu(hpte[0]);
				अगर (!(pte & (HPTE_V_VALID | HPTE_V_ABSENT)))
					अवरोध;
				__unlock_hpte(hpte, pte);
				hpte += 2;
			पूर्ण
			अगर (i == 8)
				वापस H_PTEG_FULL;
		पूर्ण
		pte_index += i;
	पूर्ण अन्यथा अणु
		hpte = (__be64 *)(kvm->arch.hpt.virt + (pte_index << 4));
		अगर (!try_lock_hpte(hpte, HPTE_V_HVLOCK | HPTE_V_VALID |
				   HPTE_V_ABSENT)) अणु
			/* Lock the slot and check again */
			u64 pte;

			जबतक (!try_lock_hpte(hpte, HPTE_V_HVLOCK))
				cpu_relax();
			pte = be64_to_cpu(hpte[0]);
			अगर (pte & (HPTE_V_VALID | HPTE_V_ABSENT)) अणु
				__unlock_hpte(hpte, pte);
				वापस H_PTEG_FULL;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Save away the guest's idea of the second HPTE dword */
	rev = &kvm->arch.hpt.rev[pte_index];
	अगर (realmode)
		rev = real_vदो_स्मृति_addr(rev);
	अगर (rev) अणु
		rev->guest_rpte = g_ptel;
		note_hpte_modअगरication(kvm, rev);
	पूर्ण

	/* Link HPTE पूर्णांकo reverse-map chain */
	अगर (pteh & HPTE_V_VALID) अणु
		अगर (realmode)
			rmap = real_vदो_स्मृति_addr(rmap);
		lock_rmap(rmap);
		/* Check क्रम pending invalidations under the rmap chain lock */
		अगर (mmu_notअगरier_retry(kvm, mmu_seq)) अणु
			/* inval in progress, ग_लिखो a non-present HPTE */
			pteh |= HPTE_V_ABSENT;
			pteh &= ~HPTE_V_VALID;
			ptel &= ~(HPTE_R_KEY_HI | HPTE_R_KEY_LO);
			unlock_rmap(rmap);
		पूर्ण अन्यथा अणु
			kvmppc_add_revmap_chain(kvm, rev, rmap, pte_index,
						realmode);
			/* Only set R/C in real HPTE अगर alपढ़ोy set in *rmap */
			rcbits = *rmap >> KVMPPC_RMAP_RC_SHIFT;
			ptel &= rcbits | ~(HPTE_R_R | HPTE_R_C);
		पूर्ण
	पूर्ण

	/* Convert to new क्रमmat on P9 */
	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		ptel = hpte_old_to_new_r(pteh, ptel);
		pteh = hpte_old_to_new_v(pteh);
	पूर्ण
	hpte[1] = cpu_to_be64(ptel);

	/* Write the first HPTE dword, unlocking the HPTE and making it valid */
	eieio();
	__unlock_hpte(hpte, pteh);
	यंत्र अस्थिर("ptesync" : : : "memory");

	*pte_idx_ret = pte_index;
	वापस H_SUCCESS;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_करो_h_enter);

दीर्घ kvmppc_h_enter(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ flags,
		    दीर्घ pte_index, अचिन्हित दीर्घ pteh, अचिन्हित दीर्घ ptel)
अणु
	वापस kvmppc_करो_h_enter(vcpu->kvm, flags, pte_index, pteh, ptel,
				 vcpu->arch.pgdir, true,
				 &vcpu->arch.regs.gpr[4]);
पूर्ण

#अगर_घोषित __BIG_ENDIAN__
#घोषणा LOCK_TOKEN	(*(u32 *)(&get_paca()->lock_token))
#अन्यथा
#घोषणा LOCK_TOKEN	(*(u32 *)(&get_paca()->paca_index))
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक is_mmio_hpte(अचिन्हित दीर्घ v, अचिन्हित दीर्घ r)
अणु
	वापस ((v & HPTE_V_ABSENT) &&
		(r & (HPTE_R_KEY_HI | HPTE_R_KEY_LO)) ==
		(HPTE_R_KEY_HI | HPTE_R_KEY_LO));
पूर्ण

अटल अंतरभूत व्योम fixup_tlbie_lpid(अचिन्हित दीर्घ rb_value, अचिन्हित दीर्घ lpid)
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
		यंत्र अस्थिर("ptesync": : :"memory");
		यंत्र अस्थिर(PPC_TLBIE_5(%0,%1,0,0,0) : :
			     "r" (rb_value), "r" (lpid));
	पूर्ण
पूर्ण

अटल व्योम करो_tlbies(काष्ठा kvm *kvm, अचिन्हित दीर्घ *rbvalues,
		      दीर्घ npages, पूर्णांक global, bool need_sync)
अणु
	दीर्घ i;

	/*
	 * We use the POWER9 5-opeअक्रम versions of tlbie and tlbiel here.
	 * Since we are using RIC=0 PRS=0 R=0, and P7/P8 tlbiel ignores
	 * the RS field, this is backwards-compatible with P7 and P8.
	 */
	अगर (global) अणु
		अगर (need_sync)
			यंत्र अस्थिर("ptesync" : : : "memory");
		क्रम (i = 0; i < npages; ++i) अणु
			यंत्र अस्थिर(PPC_TLBIE_5(%0,%1,0,0,0) : :
				     "r" (rbvalues[i]), "r" (kvm->arch.lpid));
		पूर्ण

		fixup_tlbie_lpid(rbvalues[i - 1], kvm->arch.lpid);
		यंत्र अस्थिर("eieio; tlbsync; ptesync" : : : "memory");
	पूर्ण अन्यथा अणु
		अगर (need_sync)
			यंत्र अस्थिर("ptesync" : : : "memory");
		क्रम (i = 0; i < npages; ++i) अणु
			यंत्र अस्थिर(PPC_TLBIEL(%0,%1,0,0,0) : :
				     "r" (rbvalues[i]), "r" (0));
		पूर्ण
		यंत्र अस्थिर("ptesync" : : : "memory");
	पूर्ण
पूर्ण

दीर्घ kvmppc_करो_h_हटाओ(काष्ठा kvm *kvm, अचिन्हित दीर्घ flags,
			अचिन्हित दीर्घ pte_index, अचिन्हित दीर्घ avpn,
			अचिन्हित दीर्घ *hpret)
अणु
	__be64 *hpte;
	अचिन्हित दीर्घ v, r, rb;
	काष्ठा revmap_entry *rev;
	u64 pte, orig_pte, pte_r;

	अगर (kvm_is_radix(kvm))
		वापस H_FUNCTION;
	अगर (pte_index >= kvmppc_hpt_npte(&kvm->arch.hpt))
		वापस H_PARAMETER;
	hpte = (__be64 *)(kvm->arch.hpt.virt + (pte_index << 4));
	जबतक (!try_lock_hpte(hpte, HPTE_V_HVLOCK))
		cpu_relax();
	pte = orig_pte = be64_to_cpu(hpte[0]);
	pte_r = be64_to_cpu(hpte[1]);
	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		pte = hpte_new_to_old_v(pte, pte_r);
		pte_r = hpte_new_to_old_r(pte_r);
	पूर्ण
	अगर ((pte & (HPTE_V_ABSENT | HPTE_V_VALID)) == 0 ||
	    ((flags & H_AVPN) && (pte & ~0x7fUL) != avpn) ||
	    ((flags & H_ANDCOND) && (pte & avpn) != 0)) अणु
		__unlock_hpte(hpte, orig_pte);
		वापस H_NOT_FOUND;
	पूर्ण

	rev = real_vदो_स्मृति_addr(&kvm->arch.hpt.rev[pte_index]);
	v = pte & ~HPTE_V_HVLOCK;
	अगर (v & HPTE_V_VALID) अणु
		hpte[0] &= ~cpu_to_be64(HPTE_V_VALID);
		rb = compute_tlbie_rb(v, pte_r, pte_index);
		करो_tlbies(kvm, &rb, 1, global_invalidates(kvm), true);
		/*
		 * The reference (R) and change (C) bits in a HPT
		 * entry can be set by hardware at any समय up until
		 * the HPTE is invalidated and the TLB invalidation
		 * sequence has completed.  This means that when
		 * removing a HPTE, we need to re-पढ़ो the HPTE after
		 * the invalidation sequence has completed in order to
		 * obtain reliable values of R and C.
		 */
		हटाओ_revmap_chain(kvm, pte_index, rev, v,
				    be64_to_cpu(hpte[1]));
	पूर्ण
	r = rev->guest_rpte & ~HPTE_GR_RESERVED;
	note_hpte_modअगरication(kvm, rev);
	unlock_hpte(hpte, 0);

	अगर (is_mmio_hpte(v, pte_r))
		atomic64_inc(&kvm->arch.mmio_update);

	अगर (v & HPTE_V_ABSENT)
		v = (v & ~HPTE_V_ABSENT) | HPTE_V_VALID;
	hpret[0] = v;
	hpret[1] = r;
	वापस H_SUCCESS;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_करो_h_हटाओ);

दीर्घ kvmppc_h_हटाओ(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ flags,
		     अचिन्हित दीर्घ pte_index, अचिन्हित दीर्घ avpn)
अणु
	वापस kvmppc_करो_h_हटाओ(vcpu->kvm, flags, pte_index, avpn,
				  &vcpu->arch.regs.gpr[4]);
पूर्ण

दीर्घ kvmppc_h_bulk_हटाओ(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	अचिन्हित दीर्घ *args = &vcpu->arch.regs.gpr[4];
	__be64 *hp, *hptes[4];
	अचिन्हित दीर्घ tlbrb[4];
	दीर्घ पूर्णांक i, j, k, n, found, indexes[4];
	अचिन्हित दीर्घ flags, req, pte_index, rcbits;
	पूर्णांक global;
	दीर्घ पूर्णांक ret = H_SUCCESS;
	काष्ठा revmap_entry *rev, *revs[4];
	u64 hp0, hp1;

	अगर (kvm_is_radix(kvm))
		वापस H_FUNCTION;
	global = global_invalidates(kvm);
	क्रम (i = 0; i < 4 && ret == H_SUCCESS; ) अणु
		n = 0;
		क्रम (; i < 4; ++i) अणु
			j = i * 2;
			pte_index = args[j];
			flags = pte_index >> 56;
			pte_index &= ((1ul << 56) - 1);
			req = flags >> 6;
			flags &= 3;
			अगर (req == 3) अणु		/* no more requests */
				i = 4;
				अवरोध;
			पूर्ण
			अगर (req != 1 || flags == 3 ||
			    pte_index >= kvmppc_hpt_npte(&kvm->arch.hpt)) अणु
				/* parameter error */
				args[j] = ((0xa0 | flags) << 56) + pte_index;
				ret = H_PARAMETER;
				अवरोध;
			पूर्ण
			hp = (__be64 *) (kvm->arch.hpt.virt + (pte_index << 4));
			/* to aव्योम deadlock, करोn't spin except क्रम first */
			अगर (!try_lock_hpte(hp, HPTE_V_HVLOCK)) अणु
				अगर (n)
					अवरोध;
				जबतक (!try_lock_hpte(hp, HPTE_V_HVLOCK))
					cpu_relax();
			पूर्ण
			found = 0;
			hp0 = be64_to_cpu(hp[0]);
			hp1 = be64_to_cpu(hp[1]);
			अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
				hp0 = hpte_new_to_old_v(hp0, hp1);
				hp1 = hpte_new_to_old_r(hp1);
			पूर्ण
			अगर (hp0 & (HPTE_V_ABSENT | HPTE_V_VALID)) अणु
				चयन (flags & 3) अणु
				हाल 0:		/* असलolute */
					found = 1;
					अवरोध;
				हाल 1:		/* andcond */
					अगर (!(hp0 & args[j + 1]))
						found = 1;
					अवरोध;
				हाल 2:		/* AVPN */
					अगर ((hp0 & ~0x7fUL) == args[j + 1])
						found = 1;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (!found) अणु
				hp[0] &= ~cpu_to_be64(HPTE_V_HVLOCK);
				args[j] = ((0x90 | flags) << 56) + pte_index;
				जारी;
			पूर्ण

			args[j] = ((0x80 | flags) << 56) + pte_index;
			rev = real_vदो_स्मृति_addr(&kvm->arch.hpt.rev[pte_index]);
			note_hpte_modअगरication(kvm, rev);

			अगर (!(hp0 & HPTE_V_VALID)) अणु
				/* insert R and C bits from PTE */
				rcbits = rev->guest_rpte & (HPTE_R_R|HPTE_R_C);
				args[j] |= rcbits << (56 - 5);
				hp[0] = 0;
				अगर (is_mmio_hpte(hp0, hp1))
					atomic64_inc(&kvm->arch.mmio_update);
				जारी;
			पूर्ण

			/* leave it locked */
			hp[0] &= ~cpu_to_be64(HPTE_V_VALID);
			tlbrb[n] = compute_tlbie_rb(hp0, hp1, pte_index);
			indexes[n] = j;
			hptes[n] = hp;
			revs[n] = rev;
			++n;
		पूर्ण

		अगर (!n)
			अवरोध;

		/* Now that we've collected a batch, करो the tlbies */
		करो_tlbies(kvm, tlbrb, n, global, true);

		/* Read PTE low words after tlbie to get final R/C values */
		क्रम (k = 0; k < n; ++k) अणु
			j = indexes[k];
			pte_index = args[j] & ((1ul << 56) - 1);
			hp = hptes[k];
			rev = revs[k];
			हटाओ_revmap_chain(kvm, pte_index, rev,
				be64_to_cpu(hp[0]), be64_to_cpu(hp[1]));
			rcbits = rev->guest_rpte & (HPTE_R_R|HPTE_R_C);
			args[j] |= rcbits << (56 - 5);
			__unlock_hpte(hp, 0);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

दीर्घ kvmppc_h_protect(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ flags,
		      अचिन्हित दीर्घ pte_index, अचिन्हित दीर्घ avpn)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	__be64 *hpte;
	काष्ठा revmap_entry *rev;
	अचिन्हित दीर्घ v, r, rb, mask, bits;
	u64 pte_v, pte_r;

	अगर (kvm_is_radix(kvm))
		वापस H_FUNCTION;
	अगर (pte_index >= kvmppc_hpt_npte(&kvm->arch.hpt))
		वापस H_PARAMETER;

	hpte = (__be64 *)(kvm->arch.hpt.virt + (pte_index << 4));
	जबतक (!try_lock_hpte(hpte, HPTE_V_HVLOCK))
		cpu_relax();
	v = pte_v = be64_to_cpu(hpte[0]);
	अगर (cpu_has_feature(CPU_FTR_ARCH_300))
		v = hpte_new_to_old_v(v, be64_to_cpu(hpte[1]));
	अगर ((v & (HPTE_V_ABSENT | HPTE_V_VALID)) == 0 ||
	    ((flags & H_AVPN) && (v & ~0x7fUL) != avpn)) अणु
		__unlock_hpte(hpte, pte_v);
		वापस H_NOT_FOUND;
	पूर्ण

	pte_r = be64_to_cpu(hpte[1]);
	bits = (flags << 55) & HPTE_R_PP0;
	bits |= (flags << 48) & HPTE_R_KEY_HI;
	bits |= flags & (HPTE_R_PP | HPTE_R_N | HPTE_R_KEY_LO);

	/* Update guest view of 2nd HPTE dword */
	mask = HPTE_R_PP0 | HPTE_R_PP | HPTE_R_N |
		HPTE_R_KEY_HI | HPTE_R_KEY_LO;
	rev = real_vदो_स्मृति_addr(&kvm->arch.hpt.rev[pte_index]);
	अगर (rev) अणु
		r = (rev->guest_rpte & ~mask) | bits;
		rev->guest_rpte = r;
		note_hpte_modअगरication(kvm, rev);
	पूर्ण

	/* Update HPTE */
	अगर (v & HPTE_V_VALID) अणु
		/*
		 * If the page is valid, करोn't let it transition from
		 * पढ़ोonly to writable.  If it should be writable, we'll
		 * take a trap and let the page fault code sort it out.
		 */
		r = (pte_r & ~mask) | bits;
		अगर (hpte_is_writable(r) && !hpte_is_writable(pte_r))
			r = hpte_make_पढ़ोonly(r);
		/* If the PTE is changing, invalidate it first */
		अगर (r != pte_r) अणु
			rb = compute_tlbie_rb(v, r, pte_index);
			hpte[0] = cpu_to_be64((pte_v & ~HPTE_V_VALID) |
					      HPTE_V_ABSENT);
			करो_tlbies(kvm, &rb, 1, global_invalidates(kvm), true);
			/* Don't lose R/C bit updates करोne by hardware */
			r |= be64_to_cpu(hpte[1]) & (HPTE_R_R | HPTE_R_C);
			hpte[1] = cpu_to_be64(r);
		पूर्ण
	पूर्ण
	unlock_hpte(hpte, pte_v & ~HPTE_V_HVLOCK);
	यंत्र अस्थिर("ptesync" : : : "memory");
	अगर (is_mmio_hpte(v, pte_r))
		atomic64_inc(&kvm->arch.mmio_update);

	वापस H_SUCCESS;
पूर्ण

दीर्घ kvmppc_h_पढ़ो(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ flags,
		   अचिन्हित दीर्घ pte_index)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	__be64 *hpte;
	अचिन्हित दीर्घ v, r;
	पूर्णांक i, n = 1;
	काष्ठा revmap_entry *rev = शून्य;

	अगर (kvm_is_radix(kvm))
		वापस H_FUNCTION;
	अगर (pte_index >= kvmppc_hpt_npte(&kvm->arch.hpt))
		वापस H_PARAMETER;
	अगर (flags & H_READ_4) अणु
		pte_index &= ~3;
		n = 4;
	पूर्ण
	rev = real_vदो_स्मृति_addr(&kvm->arch.hpt.rev[pte_index]);
	क्रम (i = 0; i < n; ++i, ++pte_index) अणु
		hpte = (__be64 *)(kvm->arch.hpt.virt + (pte_index << 4));
		v = be64_to_cpu(hpte[0]) & ~HPTE_V_HVLOCK;
		r = be64_to_cpu(hpte[1]);
		अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
			v = hpte_new_to_old_v(v, r);
			r = hpte_new_to_old_r(r);
		पूर्ण
		अगर (v & HPTE_V_ABSENT) अणु
			v &= ~HPTE_V_ABSENT;
			v |= HPTE_V_VALID;
		पूर्ण
		अगर (v & HPTE_V_VALID) अणु
			r = rev[i].guest_rpte | (r & (HPTE_R_R | HPTE_R_C));
			r &= ~HPTE_GR_RESERVED;
		पूर्ण
		vcpu->arch.regs.gpr[4 + i * 2] = v;
		vcpu->arch.regs.gpr[5 + i * 2] = r;
	पूर्ण
	वापस H_SUCCESS;
पूर्ण

दीर्घ kvmppc_h_clear_ref(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ flags,
			अचिन्हित दीर्घ pte_index)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	__be64 *hpte;
	अचिन्हित दीर्घ v, r, gr;
	काष्ठा revmap_entry *rev;
	अचिन्हित दीर्घ *rmap;
	दीर्घ ret = H_NOT_FOUND;

	अगर (kvm_is_radix(kvm))
		वापस H_FUNCTION;
	अगर (pte_index >= kvmppc_hpt_npte(&kvm->arch.hpt))
		वापस H_PARAMETER;

	rev = real_vदो_स्मृति_addr(&kvm->arch.hpt.rev[pte_index]);
	hpte = (__be64 *)(kvm->arch.hpt.virt + (pte_index << 4));
	जबतक (!try_lock_hpte(hpte, HPTE_V_HVLOCK))
		cpu_relax();
	v = be64_to_cpu(hpte[0]);
	r = be64_to_cpu(hpte[1]);
	अगर (!(v & (HPTE_V_VALID | HPTE_V_ABSENT)))
		जाओ out;

	gr = rev->guest_rpte;
	अगर (rev->guest_rpte & HPTE_R_R) अणु
		rev->guest_rpte &= ~HPTE_R_R;
		note_hpte_modअगरication(kvm, rev);
	पूर्ण
	अगर (v & HPTE_V_VALID) अणु
		gr |= r & (HPTE_R_R | HPTE_R_C);
		अगर (r & HPTE_R_R) अणु
			kvmppc_clear_ref_hpte(kvm, hpte, pte_index);
			rmap = revmap_क्रम_hpte(kvm, v, gr, शून्य, शून्य);
			अगर (rmap) अणु
				lock_rmap(rmap);
				*rmap |= KVMPPC_RMAP_REFERENCED;
				unlock_rmap(rmap);
			पूर्ण
		पूर्ण
	पूर्ण
	vcpu->arch.regs.gpr[4] = gr;
	ret = H_SUCCESS;
 out:
	unlock_hpte(hpte, v & ~HPTE_V_HVLOCK);
	वापस ret;
पूर्ण

दीर्घ kvmppc_h_clear_mod(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ flags,
			अचिन्हित दीर्घ pte_index)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	__be64 *hpte;
	अचिन्हित दीर्घ v, r, gr;
	काष्ठा revmap_entry *rev;
	दीर्घ ret = H_NOT_FOUND;

	अगर (kvm_is_radix(kvm))
		वापस H_FUNCTION;
	अगर (pte_index >= kvmppc_hpt_npte(&kvm->arch.hpt))
		वापस H_PARAMETER;

	rev = real_vदो_स्मृति_addr(&kvm->arch.hpt.rev[pte_index]);
	hpte = (__be64 *)(kvm->arch.hpt.virt + (pte_index << 4));
	जबतक (!try_lock_hpte(hpte, HPTE_V_HVLOCK))
		cpu_relax();
	v = be64_to_cpu(hpte[0]);
	r = be64_to_cpu(hpte[1]);
	अगर (!(v & (HPTE_V_VALID | HPTE_V_ABSENT)))
		जाओ out;

	gr = rev->guest_rpte;
	अगर (gr & HPTE_R_C) अणु
		rev->guest_rpte &= ~HPTE_R_C;
		note_hpte_modअगरication(kvm, rev);
	पूर्ण
	अगर (v & HPTE_V_VALID) अणु
		/* need to make it temporarily असलent so C is stable */
		hpte[0] |= cpu_to_be64(HPTE_V_ABSENT);
		kvmppc_invalidate_hpte(kvm, hpte, pte_index);
		r = be64_to_cpu(hpte[1]);
		gr |= r & (HPTE_R_R | HPTE_R_C);
		अगर (r & HPTE_R_C) अणु
			hpte[1] = cpu_to_be64(r & ~HPTE_R_C);
			eieio();
			kvmppc_set_dirty_from_hpte(kvm, v, gr);
		पूर्ण
	पूर्ण
	vcpu->arch.regs.gpr[4] = gr;
	ret = H_SUCCESS;
 out:
	unlock_hpte(hpte, v & ~HPTE_V_HVLOCK);
	वापस ret;
पूर्ण

अटल पूर्णांक kvmppc_get_hpa(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ mmu_seq,
			  अचिन्हित दीर्घ gpa, पूर्णांक writing, अचिन्हित दीर्घ *hpa,
			  काष्ठा kvm_memory_slot **memslot_p)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा kvm_memory_slot *memslot;
	अचिन्हित दीर्घ gfn, hva, pa, psize = PAGE_SHIFT;
	अचिन्हित पूर्णांक shअगरt;
	pte_t *ptep, pte;

	/* Find the memslot क्रम this address */
	gfn = gpa >> PAGE_SHIFT;
	memslot = __gfn_to_memslot(kvm_memslots_raw(kvm), gfn);
	अगर (!memslot || (memslot->flags & KVM_MEMSLOT_INVALID))
		वापस H_PARAMETER;

	/* Translate to host भव address */
	hva = __gfn_to_hva_memslot(memslot, gfn);

	/* Try to find the host pte क्रम that भव address */
	ptep = find_kvm_host_pte(kvm, mmu_seq, hva, &shअगरt);
	अगर (!ptep)
		वापस H_TOO_HARD;
	pte = kvmppc_पढ़ो_update_linux_pte(ptep, writing);
	अगर (!pte_present(pte))
		वापस H_TOO_HARD;

	/* Convert to a physical address */
	अगर (shअगरt)
		psize = 1UL << shअगरt;
	pa = pte_pfn(pte) << PAGE_SHIFT;
	pa |= hva & (psize - 1);
	pa |= gpa & ~PAGE_MASK;

	अगर (hpa)
		*hpa = pa;
	अगर (memslot_p)
		*memslot_p = memslot;

	वापस H_SUCCESS;
पूर्ण

अटल दीर्घ kvmppc_करो_h_page_init_zero(काष्ठा kvm_vcpu *vcpu,
				       अचिन्हित दीर्घ dest)
अणु
	काष्ठा kvm_memory_slot *memslot;
	काष्ठा kvm *kvm = vcpu->kvm;
	अचिन्हित दीर्घ pa, mmu_seq;
	दीर्घ ret = H_SUCCESS;
	पूर्णांक i;

	/* Used later to detect अगर we might have been invalidated */
	mmu_seq = kvm->mmu_notअगरier_seq;
	smp_rmb();

	arch_spin_lock(&kvm->mmu_lock.rlock.raw_lock);

	ret = kvmppc_get_hpa(vcpu, mmu_seq, dest, 1, &pa, &memslot);
	अगर (ret != H_SUCCESS)
		जाओ out_unlock;

	/* Zero the page */
	क्रम (i = 0; i < SZ_4K; i += L1_CACHE_BYTES, pa += L1_CACHE_BYTES)
		dcbz((व्योम *)pa);
	kvmppc_update_dirty_map(memslot, dest >> PAGE_SHIFT, PAGE_SIZE);

out_unlock:
	arch_spin_unlock(&kvm->mmu_lock.rlock.raw_lock);
	वापस ret;
पूर्ण

अटल दीर्घ kvmppc_करो_h_page_init_copy(काष्ठा kvm_vcpu *vcpu,
				       अचिन्हित दीर्घ dest, अचिन्हित दीर्घ src)
अणु
	अचिन्हित दीर्घ dest_pa, src_pa, mmu_seq;
	काष्ठा kvm_memory_slot *dest_memslot;
	काष्ठा kvm *kvm = vcpu->kvm;
	दीर्घ ret = H_SUCCESS;

	/* Used later to detect अगर we might have been invalidated */
	mmu_seq = kvm->mmu_notअगरier_seq;
	smp_rmb();

	arch_spin_lock(&kvm->mmu_lock.rlock.raw_lock);
	ret = kvmppc_get_hpa(vcpu, mmu_seq, dest, 1, &dest_pa, &dest_memslot);
	अगर (ret != H_SUCCESS)
		जाओ out_unlock;

	ret = kvmppc_get_hpa(vcpu, mmu_seq, src, 0, &src_pa, शून्य);
	अगर (ret != H_SUCCESS)
		जाओ out_unlock;

	/* Copy the page */
	स_नकल((व्योम *)dest_pa, (व्योम *)src_pa, SZ_4K);

	kvmppc_update_dirty_map(dest_memslot, dest >> PAGE_SHIFT, PAGE_SIZE);

out_unlock:
	arch_spin_unlock(&kvm->mmu_lock.rlock.raw_lock);
	वापस ret;
पूर्ण

दीर्घ kvmppc_rm_h_page_init(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ flags,
			   अचिन्हित दीर्घ dest, अचिन्हित दीर्घ src)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	u64 pg_mask = SZ_4K - 1;	/* 4K page size */
	दीर्घ ret = H_SUCCESS;

	/* Don't handle radix mode here, go up to the भव mode handler */
	अगर (kvm_is_radix(kvm))
		वापस H_TOO_HARD;

	/* Check क्रम invalid flags (H_PAGE_SET_LOANED covers all CMO flags) */
	अगर (flags & ~(H_ICACHE_INVALIDATE | H_ICACHE_SYNCHRONIZE |
		      H_ZERO_PAGE | H_COPY_PAGE | H_PAGE_SET_LOANED))
		वापस H_PARAMETER;

	/* dest (and src अगर copy_page flag set) must be page aligned */
	अगर ((dest & pg_mask) || ((flags & H_COPY_PAGE) && (src & pg_mask)))
		वापस H_PARAMETER;

	/* zero and/or copy the page as determined by the flags */
	अगर (flags & H_COPY_PAGE)
		ret = kvmppc_करो_h_page_init_copy(vcpu, dest, src);
	अन्यथा अगर (flags & H_ZERO_PAGE)
		ret = kvmppc_करो_h_page_init_zero(vcpu, dest);

	/* We can ignore the other flags */

	वापस ret;
पूर्ण

व्योम kvmppc_invalidate_hpte(काष्ठा kvm *kvm, __be64 *hptep,
			अचिन्हित दीर्घ pte_index)
अणु
	अचिन्हित दीर्घ rb;
	u64 hp0, hp1;

	hptep[0] &= ~cpu_to_be64(HPTE_V_VALID);
	hp0 = be64_to_cpu(hptep[0]);
	hp1 = be64_to_cpu(hptep[1]);
	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		hp0 = hpte_new_to_old_v(hp0, hp1);
		hp1 = hpte_new_to_old_r(hp1);
	पूर्ण
	rb = compute_tlbie_rb(hp0, hp1, pte_index);
	करो_tlbies(kvm, &rb, 1, 1, true);
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_invalidate_hpte);

व्योम kvmppc_clear_ref_hpte(काष्ठा kvm *kvm, __be64 *hptep,
			   अचिन्हित दीर्घ pte_index)
अणु
	अचिन्हित दीर्घ rb;
	अचिन्हित अक्षर rbyte;
	u64 hp0, hp1;

	hp0 = be64_to_cpu(hptep[0]);
	hp1 = be64_to_cpu(hptep[1]);
	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		hp0 = hpte_new_to_old_v(hp0, hp1);
		hp1 = hpte_new_to_old_r(hp1);
	पूर्ण
	rb = compute_tlbie_rb(hp0, hp1, pte_index);
	rbyte = (be64_to_cpu(hptep[1]) & ~HPTE_R_R) >> 8;
	/* modअगरy only the second-last byte, which contains the ref bit */
	*((अक्षर *)hptep + 14) = rbyte;
	करो_tlbies(kvm, &rb, 1, 1, false);
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_clear_ref_hpte);

अटल पूर्णांक slb_base_page_shअगरt[4] = अणु
	24,	/* 16M */
	16,	/* 64k */
	34,	/* 16G */
	20,	/* 1M, unsupported */
पूर्ण;

अटल काष्ठा mmio_hpte_cache_entry *mmio_cache_search(काष्ठा kvm_vcpu *vcpu,
		अचिन्हित दीर्घ eaddr, अचिन्हित दीर्घ slb_v, दीर्घ mmio_update)
अणु
	काष्ठा mmio_hpte_cache_entry *entry = शून्य;
	अचिन्हित पूर्णांक pshअगरt;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < MMIO_HPTE_CACHE_SIZE; i++) अणु
		entry = &vcpu->arch.mmio_cache.entry[i];
		अगर (entry->mmio_update == mmio_update) अणु
			pshअगरt = entry->slb_base_pshअगरt;
			अगर ((entry->eaddr >> pshअगरt) == (eaddr >> pshअगरt) &&
			    entry->slb_v == slb_v)
				वापस entry;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा mmio_hpte_cache_entry *
			next_mmio_cache_entry(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित पूर्णांक index = vcpu->arch.mmio_cache.index;

	vcpu->arch.mmio_cache.index++;
	अगर (vcpu->arch.mmio_cache.index == MMIO_HPTE_CACHE_SIZE)
		vcpu->arch.mmio_cache.index = 0;

	वापस &vcpu->arch.mmio_cache.entry[index];
पूर्ण

/* When called from virपंचांगode, this func should be रक्षित by
 * preempt_disable(), otherwise, the holding of HPTE_V_HVLOCK
 * can trigger deadlock issue.
 */
दीर्घ kvmppc_hv_find_lock_hpte(काष्ठा kvm *kvm, gva_t eaddr, अचिन्हित दीर्घ slb_v,
			      अचिन्हित दीर्घ valid)
अणु
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक pshअगरt;
	अचिन्हित दीर्घ somask;
	अचिन्हित दीर्घ vsid, hash;
	अचिन्हित दीर्घ avpn;
	__be64 *hpte;
	अचिन्हित दीर्घ mask, val;
	अचिन्हित दीर्घ v, r, orig_v;

	/* Get page shअगरt, work out hash and AVPN etc. */
	mask = SLB_VSID_B | HPTE_V_AVPN | HPTE_V_SECONDARY;
	val = 0;
	pshअगरt = 12;
	अगर (slb_v & SLB_VSID_L) अणु
		mask |= HPTE_V_LARGE;
		val |= HPTE_V_LARGE;
		pshअगरt = slb_base_page_shअगरt[(slb_v & SLB_VSID_LP) >> 4];
	पूर्ण
	अगर (slb_v & SLB_VSID_B_1T) अणु
		somask = (1UL << 40) - 1;
		vsid = (slb_v & ~SLB_VSID_B) >> SLB_VSID_SHIFT_1T;
		vsid ^= vsid << 25;
	पूर्ण अन्यथा अणु
		somask = (1UL << 28) - 1;
		vsid = (slb_v & ~SLB_VSID_B) >> SLB_VSID_SHIFT;
	पूर्ण
	hash = (vsid ^ ((eaddr & somask) >> pshअगरt)) & kvmppc_hpt_mask(&kvm->arch.hpt);
	avpn = slb_v & ~(somask >> 16);	/* also includes B */
	avpn |= (eaddr & somask) >> 16;

	अगर (pshअगरt >= 24)
		avpn &= ~((1UL << (pshअगरt - 16)) - 1);
	अन्यथा
		avpn &= ~0x7fUL;
	val |= avpn;

	क्रम (;;) अणु
		hpte = (__be64 *)(kvm->arch.hpt.virt + (hash << 7));

		क्रम (i = 0; i < 16; i += 2) अणु
			/* Read the PTE racily */
			v = be64_to_cpu(hpte[i]) & ~HPTE_V_HVLOCK;
			अगर (cpu_has_feature(CPU_FTR_ARCH_300))
				v = hpte_new_to_old_v(v, be64_to_cpu(hpte[i+1]));

			/* Check valid/असलent, hash, segment size and AVPN */
			अगर (!(v & valid) || (v & mask) != val)
				जारी;

			/* Lock the PTE and पढ़ो it under the lock */
			जबतक (!try_lock_hpte(&hpte[i], HPTE_V_HVLOCK))
				cpu_relax();
			v = orig_v = be64_to_cpu(hpte[i]) & ~HPTE_V_HVLOCK;
			r = be64_to_cpu(hpte[i+1]);
			अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
				v = hpte_new_to_old_v(v, r);
				r = hpte_new_to_old_r(r);
			पूर्ण

			/*
			 * Check the HPTE again, including base page size
			 */
			अगर ((v & valid) && (v & mask) == val &&
			    kvmppc_hpte_base_page_shअगरt(v, r) == pshअगरt)
				/* Return with the HPTE still locked */
				वापस (hash << 3) + (i >> 1);

			__unlock_hpte(&hpte[i], orig_v);
		पूर्ण

		अगर (val & HPTE_V_SECONDARY)
			अवरोध;
		val |= HPTE_V_SECONDARY;
		hash = hash ^ kvmppc_hpt_mask(&kvm->arch.hpt);
	पूर्ण
	वापस -1;
पूर्ण
EXPORT_SYMBOL(kvmppc_hv_find_lock_hpte);

/*
 * Called in real mode to check whether an HPTE not found fault
 * is due to accessing a paged-out page or an emulated MMIO page,
 * or अगर a protection fault is due to accessing a page that the
 * guest wanted पढ़ो/ग_लिखो access to but which we made पढ़ो-only.
 * Returns a possibly modअगरied status (DSISR) value अगर not
 * (i.e. pass the पूर्णांकerrupt to the guest),
 * -1 to pass the fault up to host kernel mode code, -2 to करो that
 * and also load the inकाष्ठाion word (क्रम MMIO emulation),
 * or 0 अगर we should make the guest retry the access.
 */
दीर्घ kvmppc_hpte_hv_fault(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ addr,
			  अचिन्हित दीर्घ slb_v, अचिन्हित पूर्णांक status, bool data)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	दीर्घ पूर्णांक index;
	अचिन्हित दीर्घ v, r, gr, orig_v;
	__be64 *hpte;
	अचिन्हित दीर्घ valid;
	काष्ठा revmap_entry *rev;
	अचिन्हित दीर्घ pp, key;
	काष्ठा mmio_hpte_cache_entry *cache_entry = शून्य;
	दीर्घ mmio_update = 0;

	/* For protection fault, expect to find a valid HPTE */
	valid = HPTE_V_VALID;
	अगर (status & DSISR_NOHPTE) अणु
		valid |= HPTE_V_ABSENT;
		mmio_update = atomic64_पढ़ो(&kvm->arch.mmio_update);
		cache_entry = mmio_cache_search(vcpu, addr, slb_v, mmio_update);
	पूर्ण
	अगर (cache_entry) अणु
		index = cache_entry->pte_index;
		v = cache_entry->hpte_v;
		r = cache_entry->hpte_r;
		gr = cache_entry->rpte;
	पूर्ण अन्यथा अणु
		index = kvmppc_hv_find_lock_hpte(kvm, addr, slb_v, valid);
		अगर (index < 0) अणु
			अगर (status & DSISR_NOHPTE)
				वापस status;	/* there really was no HPTE */
			वापस 0;	/* क्रम prot fault, HPTE disappeared */
		पूर्ण
		hpte = (__be64 *)(kvm->arch.hpt.virt + (index << 4));
		v = orig_v = be64_to_cpu(hpte[0]) & ~HPTE_V_HVLOCK;
		r = be64_to_cpu(hpte[1]);
		अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
			v = hpte_new_to_old_v(v, r);
			r = hpte_new_to_old_r(r);
		पूर्ण
		rev = real_vदो_स्मृति_addr(&kvm->arch.hpt.rev[index]);
		gr = rev->guest_rpte;

		unlock_hpte(hpte, orig_v);
	पूर्ण

	/* For not found, अगर the HPTE is valid by now, retry the inकाष्ठाion */
	अगर ((status & DSISR_NOHPTE) && (v & HPTE_V_VALID))
		वापस 0;

	/* Check access permissions to the page */
	pp = gr & (HPTE_R_PP0 | HPTE_R_PP);
	key = (vcpu->arch.shregs.msr & MSR_PR) ? SLB_VSID_KP : SLB_VSID_KS;
	status &= ~DSISR_NOHPTE;	/* DSISR_NOHPTE == SRR1_ISI_NOPT */
	अगर (!data) अणु
		अगर (gr & (HPTE_R_N | HPTE_R_G))
			वापस status | SRR1_ISI_N_G_OR_CIP;
		अगर (!hpte_पढ़ो_permission(pp, slb_v & key))
			वापस status | SRR1_ISI_PROT;
	पूर्ण अन्यथा अगर (status & DSISR_ISSTORE) अणु
		/* check ग_लिखो permission */
		अगर (!hpte_ग_लिखो_permission(pp, slb_v & key))
			वापस status | DSISR_PROTFAULT;
	पूर्ण अन्यथा अणु
		अगर (!hpte_पढ़ो_permission(pp, slb_v & key))
			वापस status | DSISR_PROTFAULT;
	पूर्ण

	/* Check storage key, अगर applicable */
	अगर (data && (vcpu->arch.shregs.msr & MSR_DR)) अणु
		अचिन्हित पूर्णांक perm = hpte_get_skey_perm(gr, vcpu->arch.amr);
		अगर (status & DSISR_ISSTORE)
			perm >>= 1;
		अगर (perm & 1)
			वापस status | DSISR_KEYFAULT;
	पूर्ण

	/* Save HPTE info क्रम भव-mode handler */
	vcpu->arch.pgfault_addr = addr;
	vcpu->arch.pgfault_index = index;
	vcpu->arch.pgfault_hpte[0] = v;
	vcpu->arch.pgfault_hpte[1] = r;
	vcpu->arch.pgfault_cache = cache_entry;

	/* Check the storage key to see अगर it is possibly emulated MMIO */
	अगर ((r & (HPTE_R_KEY_HI | HPTE_R_KEY_LO)) ==
	    (HPTE_R_KEY_HI | HPTE_R_KEY_LO)) अणु
		अगर (!cache_entry) अणु
			अचिन्हित पूर्णांक pshअगरt = 12;
			अचिन्हित पूर्णांक pshअगरt_index;

			अगर (slb_v & SLB_VSID_L) अणु
				pshअगरt_index = ((slb_v & SLB_VSID_LP) >> 4);
				pshअगरt = slb_base_page_shअगरt[pshअगरt_index];
			पूर्ण
			cache_entry = next_mmio_cache_entry(vcpu);
			cache_entry->eaddr = addr;
			cache_entry->slb_base_pshअगरt = pshअगरt;
			cache_entry->pte_index = index;
			cache_entry->hpte_v = v;
			cache_entry->hpte_r = r;
			cache_entry->rpte = gr;
			cache_entry->slb_v = slb_v;
			cache_entry->mmio_update = mmio_update;
		पूर्ण
		अगर (data && (vcpu->arch.shregs.msr & MSR_IR))
			वापस -2;	/* MMIO emulation - load instr word */
	पूर्ण

	वापस -1;		/* send fault up to host kernel mode */
पूर्ण
