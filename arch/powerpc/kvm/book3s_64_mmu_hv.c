<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright 2010 Paul Mackerras, IBM Corp. <paulus@au1.ibm.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/gfp.h>
#समावेश <linux/slab.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/srcu.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/file.h>
#समावेश <linux/debugfs.h>

#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/book3s/64/mmu-hash.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/synch.h>
#समावेश <यंत्र/ppc-opcode.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/pte-walk.h>

#समावेश "book3s.h"
#समावेश "trace_hv.h"

//#घोषणा DEBUG_RESIZE_HPT	1

#अगर_घोषित DEBUG_RESIZE_HPT
#घोषणा resize_hpt_debug(resize, ...)				\
	करो अणु							\
		prपूर्णांकk(KERN_DEBUG "RESIZE HPT %p: ", resize);	\
		prपूर्णांकk(__VA_ARGS__);				\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा resize_hpt_debug(resize, ...)				\
	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल दीर्घ kvmppc_virपंचांगode_करो_h_enter(काष्ठा kvm *kvm, अचिन्हित दीर्घ flags,
				दीर्घ pte_index, अचिन्हित दीर्घ pteh,
				अचिन्हित दीर्घ ptel, अचिन्हित दीर्घ *pte_idx_ret);

काष्ठा kvm_resize_hpt अणु
	/* These fields पढ़ो-only after init */
	काष्ठा kvm *kvm;
	काष्ठा work_काष्ठा work;
	u32 order;

	/* These fields रक्षित by kvm->arch.mmu_setup_lock */

	/* Possible values and their usage:
	 *  <0     an error occurred during allocation,
	 *  -EBUSY allocation is in the progress,
	 *  0      allocation made successfuly.
	 */
	पूर्णांक error;

	/* Private to the work thपढ़ो, until error != -EBUSY,
	 * then रक्षित by kvm->arch.mmu_setup_lock.
	 */
	काष्ठा kvm_hpt_info hpt;
पूर्ण;

पूर्णांक kvmppc_allocate_hpt(काष्ठा kvm_hpt_info *info, u32 order)
अणु
	अचिन्हित दीर्घ hpt = 0;
	पूर्णांक cma = 0;
	काष्ठा page *page = शून्य;
	काष्ठा revmap_entry *rev;
	अचिन्हित दीर्घ npte;

	अगर ((order < PPC_MIN_HPT_ORDER) || (order > PPC_MAX_HPT_ORDER))
		वापस -EINVAL;

	page = kvm_alloc_hpt_cma(1ul << (order - PAGE_SHIFT));
	अगर (page) अणु
		hpt = (अचिन्हित दीर्घ)pfn_to_kaddr(page_to_pfn(page));
		स_रखो((व्योम *)hpt, 0, (1ul << order));
		cma = 1;
	पूर्ण

	अगर (!hpt)
		hpt = __get_मुक्त_pages(GFP_KERNEL|__GFP_ZERO|__GFP_RETRY_MAYFAIL
				       |__GFP_NOWARN, order - PAGE_SHIFT);

	अगर (!hpt)
		वापस -ENOMEM;

	/* HPTEs are 2**4 bytes दीर्घ */
	npte = 1ul << (order - 4);

	/* Allocate reverse map array */
	rev = vदो_स्मृति(array_size(npte, माप(काष्ठा revmap_entry)));
	अगर (!rev) अणु
		अगर (cma)
			kvm_मुक्त_hpt_cma(page, 1 << (order - PAGE_SHIFT));
		अन्यथा
			मुक्त_pages(hpt, order - PAGE_SHIFT);
		वापस -ENOMEM;
	पूर्ण

	info->order = order;
	info->virt = hpt;
	info->cma = cma;
	info->rev = rev;

	वापस 0;
पूर्ण

व्योम kvmppc_set_hpt(काष्ठा kvm *kvm, काष्ठा kvm_hpt_info *info)
अणु
	atomic64_set(&kvm->arch.mmio_update, 0);
	kvm->arch.hpt = *info;
	kvm->arch.sdr1 = __pa(info->virt) | (info->order - 18);

	pr_debug("KVM guest htab at %lx (order %ld), LPID %x\n",
		 info->virt, (दीर्घ)info->order, kvm->arch.lpid);
पूर्ण

दीर्घ kvmppc_alloc_reset_hpt(काष्ठा kvm *kvm, पूर्णांक order)
अणु
	दीर्घ err = -EBUSY;
	काष्ठा kvm_hpt_info info;

	mutex_lock(&kvm->arch.mmu_setup_lock);
	अगर (kvm->arch.mmu_पढ़ोy) अणु
		kvm->arch.mmu_पढ़ोy = 0;
		/* order mmu_पढ़ोy vs. vcpus_running */
		smp_mb();
		अगर (atomic_पढ़ो(&kvm->arch.vcpus_running)) अणु
			kvm->arch.mmu_पढ़ोy = 1;
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (kvm_is_radix(kvm)) अणु
		err = kvmppc_चयन_mmu_to_hpt(kvm);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (kvm->arch.hpt.order == order) अणु
		/* We alपढ़ोy have a suitable HPT */

		/* Set the entire HPT to 0, i.e. invalid HPTEs */
		स_रखो((व्योम *)kvm->arch.hpt.virt, 0, 1ul << order);
		/*
		 * Reset all the reverse-mapping chains क्रम all memslots
		 */
		kvmppc_rmap_reset(kvm);
		err = 0;
		जाओ out;
	पूर्ण

	अगर (kvm->arch.hpt.virt) अणु
		kvmppc_मुक्त_hpt(&kvm->arch.hpt);
		kvmppc_rmap_reset(kvm);
	पूर्ण

	err = kvmppc_allocate_hpt(&info, order);
	अगर (err < 0)
		जाओ out;
	kvmppc_set_hpt(kvm, &info);

out:
	अगर (err == 0)
		/* Ensure that each vcpu will flush its TLB on next entry. */
		cpumask_setall(&kvm->arch.need_tlb_flush);

	mutex_unlock(&kvm->arch.mmu_setup_lock);
	वापस err;
पूर्ण

व्योम kvmppc_मुक्त_hpt(काष्ठा kvm_hpt_info *info)
अणु
	vमुक्त(info->rev);
	info->rev = शून्य;
	अगर (info->cma)
		kvm_मुक्त_hpt_cma(virt_to_page(info->virt),
				 1 << (info->order - PAGE_SHIFT));
	अन्यथा अगर (info->virt)
		मुक्त_pages(info->virt, info->order - PAGE_SHIFT);
	info->virt = 0;
	info->order = 0;
पूर्ण

/* Bits in first HPTE dword क्रम pagesize 4k, 64k or 16M */
अटल अंतरभूत अचिन्हित दीर्घ hpte0_pgsize_encoding(अचिन्हित दीर्घ pgsize)
अणु
	वापस (pgsize > 0x1000) ? HPTE_V_LARGE : 0;
पूर्ण

/* Bits in second HPTE dword क्रम pagesize 4k, 64k or 16M */
अटल अंतरभूत अचिन्हित दीर्घ hpte1_pgsize_encoding(अचिन्हित दीर्घ pgsize)
अणु
	वापस (pgsize == 0x10000) ? 0x1000 : 0;
पूर्ण

व्योम kvmppc_map_vrma(काष्ठा kvm_vcpu *vcpu, काष्ठा kvm_memory_slot *memslot,
		     अचिन्हित दीर्घ porder)
अणु
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ npages;
	अचिन्हित दीर्घ hp_v, hp_r;
	अचिन्हित दीर्घ addr, hash;
	अचिन्हित दीर्घ psize;
	अचिन्हित दीर्घ hp0, hp1;
	अचिन्हित दीर्घ idx_ret;
	दीर्घ ret;
	काष्ठा kvm *kvm = vcpu->kvm;

	psize = 1ul << porder;
	npages = memslot->npages >> (porder - PAGE_SHIFT);

	/* VRMA can't be > 1TB */
	अगर (npages > 1ul << (40 - porder))
		npages = 1ul << (40 - porder);
	/* Can't use more than 1 HPTE per HPTEG */
	अगर (npages > kvmppc_hpt_mask(&kvm->arch.hpt) + 1)
		npages = kvmppc_hpt_mask(&kvm->arch.hpt) + 1;

	hp0 = HPTE_V_1TB_SEG | (VRMA_VSID << (40 - 16)) |
		HPTE_V_BOLTED | hpte0_pgsize_encoding(psize);
	hp1 = hpte1_pgsize_encoding(psize) |
		HPTE_R_R | HPTE_R_C | HPTE_R_M | PP_RWXX;

	क्रम (i = 0; i < npages; ++i) अणु
		addr = i << porder;
		/* can't use hpt_hash since va > 64 bits */
		hash = (i ^ (VRMA_VSID ^ (VRMA_VSID << 25)))
			& kvmppc_hpt_mask(&kvm->arch.hpt);
		/*
		 * We assume that the hash table is empty and no
		 * vcpus are using it at this stage.  Since we create
		 * at most one HPTE per HPTEG, we just assume entry 7
		 * is available and use it.
		 */
		hash = (hash << 3) + 7;
		hp_v = hp0 | ((addr >> 16) & ~0x7fUL);
		hp_r = hp1 | addr;
		ret = kvmppc_virपंचांगode_करो_h_enter(kvm, H_EXACT, hash, hp_v, hp_r,
						 &idx_ret);
		अगर (ret != H_SUCCESS) अणु
			pr_err("KVM: map_vrma at %lx failed, ret=%ld\n",
			       addr, ret);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक kvmppc_mmu_hv_init(व्योम)
अणु
	अचिन्हित दीर्घ host_lpid, rsvd_lpid;

	अगर (!mmu_has_feature(MMU_FTR_LOCKLESS_TLBIE))
		वापस -EINVAL;

	host_lpid = 0;
	अगर (cpu_has_feature(CPU_FTR_HVMODE))
		host_lpid = mfspr(SPRN_LPID);

	/* POWER8 and above have 12-bit LPIDs (10-bit in POWER7) */
	अगर (cpu_has_feature(CPU_FTR_ARCH_207S))
		rsvd_lpid = LPID_RSVD;
	अन्यथा
		rsvd_lpid = LPID_RSVD_POWER7;

	kvmppc_init_lpid(rsvd_lpid + 1);

	kvmppc_claim_lpid(host_lpid);
	/* rsvd_lpid is reserved क्रम use in partition चयनing */
	kvmppc_claim_lpid(rsvd_lpid);

	वापस 0;
पूर्ण

अटल दीर्घ kvmppc_virपंचांगode_करो_h_enter(काष्ठा kvm *kvm, अचिन्हित दीर्घ flags,
				दीर्घ pte_index, अचिन्हित दीर्घ pteh,
				अचिन्हित दीर्घ ptel, अचिन्हित दीर्घ *pte_idx_ret)
अणु
	दीर्घ ret;

	preempt_disable();
	ret = kvmppc_करो_h_enter(kvm, flags, pte_index, pteh, ptel,
				kvm->mm->pgd, false, pte_idx_ret);
	preempt_enable();
	अगर (ret == H_TOO_HARD) अणु
		/* this can't happen */
		pr_err("KVM: Oops, kvmppc_h_enter returned too hard!\n");
		ret = H_RESOURCE;	/* or something */
	पूर्ण
	वापस ret;

पूर्ण

अटल काष्ठा kvmppc_slb *kvmppc_mmu_book3s_hv_find_slbe(काष्ठा kvm_vcpu *vcpu,
							 gva_t eaddr)
अणु
	u64 mask;
	पूर्णांक i;

	क्रम (i = 0; i < vcpu->arch.slb_nr; i++) अणु
		अगर (!(vcpu->arch.slb[i].orige & SLB_ESID_V))
			जारी;

		अगर (vcpu->arch.slb[i].origv & SLB_VSID_B_1T)
			mask = ESID_MASK_1T;
		अन्यथा
			mask = ESID_MASK;

		अगर (((vcpu->arch.slb[i].orige ^ eaddr) & mask) == 0)
			वापस &vcpu->arch.slb[i];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल अचिन्हित दीर्घ kvmppc_mmu_get_real_addr(अचिन्हित दीर्घ v, अचिन्हित दीर्घ r,
			अचिन्हित दीर्घ ea)
अणु
	अचिन्हित दीर्घ ra_mask;

	ra_mask = kvmppc_actual_pgsz(v, r) - 1;
	वापस (r & HPTE_R_RPN & ~ra_mask) | (ea & ra_mask);
पूर्ण

अटल पूर्णांक kvmppc_mmu_book3s_64_hv_xlate(काष्ठा kvm_vcpu *vcpu, gva_t eaddr,
			काष्ठा kvmppc_pte *gpte, bool data, bool isग_लिखो)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा kvmppc_slb *slbe;
	अचिन्हित दीर्घ slb_v;
	अचिन्हित दीर्घ pp, key;
	अचिन्हित दीर्घ v, orig_v, gr;
	__be64 *hptep;
	दीर्घ पूर्णांक index;
	पूर्णांक virपंचांगode = vcpu->arch.shregs.msr & (data ? MSR_DR : MSR_IR);

	अगर (kvm_is_radix(vcpu->kvm))
		वापस kvmppc_mmu_radix_xlate(vcpu, eaddr, gpte, data, isग_लिखो);

	/* Get SLB entry */
	अगर (virपंचांगode) अणु
		slbe = kvmppc_mmu_book3s_hv_find_slbe(vcpu, eaddr);
		अगर (!slbe)
			वापस -EINVAL;
		slb_v = slbe->origv;
	पूर्ण अन्यथा अणु
		/* real mode access */
		slb_v = vcpu->kvm->arch.vrma_slb_v;
	पूर्ण

	preempt_disable();
	/* Find the HPTE in the hash table */
	index = kvmppc_hv_find_lock_hpte(kvm, eaddr, slb_v,
					 HPTE_V_VALID | HPTE_V_ABSENT);
	अगर (index < 0) अणु
		preempt_enable();
		वापस -ENOENT;
	पूर्ण
	hptep = (__be64 *)(kvm->arch.hpt.virt + (index << 4));
	v = orig_v = be64_to_cpu(hptep[0]) & ~HPTE_V_HVLOCK;
	अगर (cpu_has_feature(CPU_FTR_ARCH_300))
		v = hpte_new_to_old_v(v, be64_to_cpu(hptep[1]));
	gr = kvm->arch.hpt.rev[index].guest_rpte;

	unlock_hpte(hptep, orig_v);
	preempt_enable();

	gpte->eaddr = eaddr;
	gpte->vpage = ((v & HPTE_V_AVPN) << 4) | ((eaddr >> 12) & 0xfff);

	/* Get PP bits and key क्रम permission check */
	pp = gr & (HPTE_R_PP0 | HPTE_R_PP);
	key = (vcpu->arch.shregs.msr & MSR_PR) ? SLB_VSID_KP : SLB_VSID_KS;
	key &= slb_v;

	/* Calculate permissions */
	gpte->may_पढ़ो = hpte_पढ़ो_permission(pp, key);
	gpte->may_ग_लिखो = hpte_ग_लिखो_permission(pp, key);
	gpte->may_execute = gpte->may_पढ़ो && !(gr & (HPTE_R_N | HPTE_R_G));

	/* Storage key permission check क्रम POWER7 */
	अगर (data && virपंचांगode) अणु
		पूर्णांक amrfield = hpte_get_skey_perm(gr, vcpu->arch.amr);
		अगर (amrfield & 1)
			gpte->may_पढ़ो = 0;
		अगर (amrfield & 2)
			gpte->may_ग_लिखो = 0;
	पूर्ण

	/* Get the guest physical address */
	gpte->raddr = kvmppc_mmu_get_real_addr(v, gr, eaddr);
	वापस 0;
पूर्ण

/*
 * Quick test क्रम whether an inकाष्ठाion is a load or a store.
 * If the inकाष्ठाion is a load or a store, then this will indicate
 * which it is, at least on server processors.  (Embedded processors
 * have some बाह्यal PID inकाष्ठाions that करोn't follow the rule
 * embodied here.)  If the inकाष्ठाion isn't a load or store, then
 * this करोesn't वापस anything useful.
 */
अटल पूर्णांक inकाष्ठाion_is_store(अचिन्हित पूर्णांक instr)
अणु
	अचिन्हित पूर्णांक mask;

	mask = 0x10000000;
	अगर ((instr & 0xfc000000) == 0x7c000000)
		mask = 0x100;		/* major opcode 31 */
	वापस (instr & mask) != 0;
पूर्ण

पूर्णांक kvmppc_hv_emulate_mmio(काष्ठा kvm_vcpu *vcpu,
			   अचिन्हित दीर्घ gpa, gva_t ea, पूर्णांक is_store)
अणु
	u32 last_inst;

	/*
	 * Fast path - check अगर the guest physical address corresponds to a
	 * device on the FAST_MMIO_BUS, अगर so we can aव्योम loading the
	 * inकाष्ठाion all together, then we can just handle it and वापस.
	 */
	अगर (is_store) अणु
		पूर्णांक idx, ret;

		idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);
		ret = kvm_io_bus_ग_लिखो(vcpu, KVM_FAST_MMIO_BUS, (gpa_t) gpa, 0,
				       शून्य);
		srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);
		अगर (!ret) अणु
			kvmppc_set_pc(vcpu, kvmppc_get_pc(vcpu) + 4);
			वापस RESUME_GUEST;
		पूर्ण
	पूर्ण

	/*
	 * If we fail, we just वापस to the guest and try executing it again.
	 */
	अगर (kvmppc_get_last_inst(vcpu, INST_GENERIC, &last_inst) !=
		EMULATE_DONE)
		वापस RESUME_GUEST;

	/*
	 * WARNING: We करो not know क्रम sure whether the inकाष्ठाion we just
	 * पढ़ो from memory is the same that caused the fault in the first
	 * place.  If the inकाष्ठाion we पढ़ो is neither an load or a store,
	 * then it can't access memory, so we don't need to worry about
	 * enक्रमcing access permissions.  So, assuming it is a load or
	 * store, we just check that its direction (load or store) is
	 * consistent with the original fault, since that's what we
	 * checked the access permissions against.  If there is a mismatch
	 * we just वापस and retry the inकाष्ठाion.
	 */

	अगर (inकाष्ठाion_is_store(last_inst) != !!is_store)
		वापस RESUME_GUEST;

	/*
	 * Emulated accesses are emulated by looking at the hash क्रम
	 * translation once, then perक्रमming the access later. The
	 * translation could be invalidated in the meanसमय in which
	 * poपूर्णांक perक्रमming the subsequent memory access on the old
	 * physical address could possibly be a security hole क्रम the
	 * guest (but not the host).
	 *
	 * This is less of an issue क्रम MMIO stores since they aren't
	 * globally visible. It could be an issue क्रम MMIO loads to
	 * a certain extent but we'll ignore it क्रम now.
	 */

	vcpu->arch.paddr_accessed = gpa;
	vcpu->arch.vaddr_accessed = ea;
	वापस kvmppc_emulate_mmio(vcpu);
पूर्ण

पूर्णांक kvmppc_book3s_hv_page_fault(काष्ठा kvm_vcpu *vcpu,
				अचिन्हित दीर्घ ea, अचिन्हित दीर्घ dsisr)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	अचिन्हित दीर्घ hpte[3], r;
	अचिन्हित दीर्घ hnow_v, hnow_r;
	__be64 *hptep;
	अचिन्हित दीर्घ mmu_seq, psize, pte_size;
	अचिन्हित दीर्घ gpa_base, gfn_base;
	अचिन्हित दीर्घ gpa, gfn, hva, pfn, hpa;
	काष्ठा kvm_memory_slot *memslot;
	अचिन्हित दीर्घ *rmap;
	काष्ठा revmap_entry *rev;
	काष्ठा page *page;
	दीर्घ index, ret;
	bool is_ci;
	bool writing, ग_लिखो_ok;
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित दीर्घ rcbits;
	दीर्घ mmio_update;
	pte_t pte, *ptep;

	अगर (kvm_is_radix(kvm))
		वापस kvmppc_book3s_radix_page_fault(vcpu, ea, dsisr);

	/*
	 * Real-mode code has alपढ़ोy searched the HPT and found the
	 * entry we're पूर्णांकerested in.  Lock the entry and check that
	 * it hasn't changed.  If it has, just वापस and re-execute the
	 * inकाष्ठाion.
	 */
	अगर (ea != vcpu->arch.pgfault_addr)
		वापस RESUME_GUEST;

	अगर (vcpu->arch.pgfault_cache) अणु
		mmio_update = atomic64_पढ़ो(&kvm->arch.mmio_update);
		अगर (mmio_update == vcpu->arch.pgfault_cache->mmio_update) अणु
			r = vcpu->arch.pgfault_cache->rpte;
			psize = kvmppc_actual_pgsz(vcpu->arch.pgfault_hpte[0],
						   r);
			gpa_base = r & HPTE_R_RPN & ~(psize - 1);
			gfn_base = gpa_base >> PAGE_SHIFT;
			gpa = gpa_base | (ea & (psize - 1));
			वापस kvmppc_hv_emulate_mmio(vcpu, gpa, ea,
						dsisr & DSISR_ISSTORE);
		पूर्ण
	पूर्ण
	index = vcpu->arch.pgfault_index;
	hptep = (__be64 *)(kvm->arch.hpt.virt + (index << 4));
	rev = &kvm->arch.hpt.rev[index];
	preempt_disable();
	जबतक (!try_lock_hpte(hptep, HPTE_V_HVLOCK))
		cpu_relax();
	hpte[0] = be64_to_cpu(hptep[0]) & ~HPTE_V_HVLOCK;
	hpte[1] = be64_to_cpu(hptep[1]);
	hpte[2] = r = rev->guest_rpte;
	unlock_hpte(hptep, hpte[0]);
	preempt_enable();

	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		hpte[0] = hpte_new_to_old_v(hpte[0], hpte[1]);
		hpte[1] = hpte_new_to_old_r(hpte[1]);
	पूर्ण
	अगर (hpte[0] != vcpu->arch.pgfault_hpte[0] ||
	    hpte[1] != vcpu->arch.pgfault_hpte[1])
		वापस RESUME_GUEST;

	/* Translate the logical address and get the page */
	psize = kvmppc_actual_pgsz(hpte[0], r);
	gpa_base = r & HPTE_R_RPN & ~(psize - 1);
	gfn_base = gpa_base >> PAGE_SHIFT;
	gpa = gpa_base | (ea & (psize - 1));
	gfn = gpa >> PAGE_SHIFT;
	memslot = gfn_to_memslot(kvm, gfn);

	trace_kvm_page_fault_enter(vcpu, hpte, memslot, ea, dsisr);

	/* No memslot means it's an emulated MMIO region */
	अगर (!memslot || (memslot->flags & KVM_MEMSLOT_INVALID))
		वापस kvmppc_hv_emulate_mmio(vcpu, gpa, ea,
					      dsisr & DSISR_ISSTORE);

	/*
	 * This should never happen, because of the slot_is_aligned()
	 * check in kvmppc_करो_h_enter().
	 */
	अगर (gfn_base < memslot->base_gfn)
		वापस -EFAULT;

	/* used to check क्रम invalidations in progress */
	mmu_seq = kvm->mmu_notअगरier_seq;
	smp_rmb();

	ret = -EFAULT;
	page = शून्य;
	writing = (dsisr & DSISR_ISSTORE) != 0;
	/* If writing != 0, then the HPTE must allow writing, अगर we get here */
	ग_लिखो_ok = writing;
	hva = gfn_to_hva_memslot(memslot, gfn);

	/*
	 * Do a fast check first, since __gfn_to_pfn_memslot करोesn't
	 * करो it with !atomic && !async, which is how we call it.
	 * We always ask क्रम ग_लिखो permission since the common हाल
	 * is that the page is writable.
	 */
	अगर (get_user_page_fast_only(hva, FOLL_WRITE, &page)) अणु
		ग_लिखो_ok = true;
	पूर्ण अन्यथा अणु
		/* Call KVM generic code to करो the slow-path check */
		pfn = __gfn_to_pfn_memslot(memslot, gfn, false, शून्य,
					   writing, &ग_लिखो_ok, शून्य);
		अगर (is_error_noslot_pfn(pfn))
			वापस -EFAULT;
		page = शून्य;
		अगर (pfn_valid(pfn)) अणु
			page = pfn_to_page(pfn);
			अगर (PageReserved(page))
				page = शून्य;
		पूर्ण
	पूर्ण

	/*
	 * Read the PTE from the process' radix tree and use that
	 * so we get the shअगरt and attribute bits.
	 */
	spin_lock(&kvm->mmu_lock);
	ptep = find_kvm_host_pte(kvm, mmu_seq, hva, &shअगरt);
	pte = __pte(0);
	अगर (ptep)
		pte = READ_ONCE(*ptep);
	spin_unlock(&kvm->mmu_lock);
	/*
	 * If the PTE disappeared temporarily due to a THP
	 * collapse, just वापस and let the guest try again.
	 */
	अगर (!pte_present(pte)) अणु
		अगर (page)
			put_page(page);
		वापस RESUME_GUEST;
	पूर्ण
	hpa = pte_pfn(pte) << PAGE_SHIFT;
	pte_size = PAGE_SIZE;
	अगर (shअगरt)
		pte_size = 1ul << shअगरt;
	is_ci = pte_ci(pte);

	अगर (psize > pte_size)
		जाओ out_put;
	अगर (pte_size > psize)
		hpa |= hva & (pte_size - psize);

	/* Check WIMG vs. the actual page we're accessing */
	अगर (!hpte_cache_flags_ok(r, is_ci)) अणु
		अगर (is_ci)
			जाओ out_put;
		/*
		 * Allow guest to map emulated device memory as
		 * uncacheable, but actually make it cacheable.
		 */
		r = (r & ~(HPTE_R_W|HPTE_R_I|HPTE_R_G)) | HPTE_R_M;
	पूर्ण

	/*
	 * Set the HPTE to poपूर्णांक to hpa.
	 * Since the hpa is at PAGE_SIZE granularity, make sure we
	 * करोn't mask out lower-order bits अगर psize < PAGE_SIZE.
	 */
	अगर (psize < PAGE_SIZE)
		psize = PAGE_SIZE;
	r = (r & HPTE_R_KEY_HI) | (r & ~(HPTE_R_PP0 - psize)) | hpa;
	अगर (hpte_is_writable(r) && !ग_लिखो_ok)
		r = hpte_make_पढ़ोonly(r);
	ret = RESUME_GUEST;
	preempt_disable();
	जबतक (!try_lock_hpte(hptep, HPTE_V_HVLOCK))
		cpu_relax();
	hnow_v = be64_to_cpu(hptep[0]);
	hnow_r = be64_to_cpu(hptep[1]);
	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		hnow_v = hpte_new_to_old_v(hnow_v, hnow_r);
		hnow_r = hpte_new_to_old_r(hnow_r);
	पूर्ण

	/*
	 * If the HPT is being resized, करोn't update the HPTE,
	 * instead let the guest retry after the resize operation is complete.
	 * The synchronization क्रम mmu_पढ़ोy test vs. set is provided
	 * by the HPTE lock.
	 */
	अगर (!kvm->arch.mmu_पढ़ोy)
		जाओ out_unlock;

	अगर ((hnow_v & ~HPTE_V_HVLOCK) != hpte[0] || hnow_r != hpte[1] ||
	    rev->guest_rpte != hpte[2])
		/* HPTE has been changed under us; let the guest retry */
		जाओ out_unlock;
	hpte[0] = (hpte[0] & ~HPTE_V_ABSENT) | HPTE_V_VALID;

	/* Always put the HPTE in the rmap chain क्रम the page base address */
	rmap = &memslot->arch.rmap[gfn_base - memslot->base_gfn];
	lock_rmap(rmap);

	/* Check अगर we might have been invalidated; let the guest retry अगर so */
	ret = RESUME_GUEST;
	अगर (mmu_notअगरier_retry(vcpu->kvm, mmu_seq)) अणु
		unlock_rmap(rmap);
		जाओ out_unlock;
	पूर्ण

	/* Only set R/C in real HPTE अगर set in both *rmap and guest_rpte */
	rcbits = *rmap >> KVMPPC_RMAP_RC_SHIFT;
	r &= rcbits | ~(HPTE_R_R | HPTE_R_C);

	अगर (be64_to_cpu(hptep[0]) & HPTE_V_VALID) अणु
		/* HPTE was previously valid, so we need to invalidate it */
		unlock_rmap(rmap);
		hptep[0] |= cpu_to_be64(HPTE_V_ABSENT);
		kvmppc_invalidate_hpte(kvm, hptep, index);
		/* करोn't lose previous R and C bits */
		r |= be64_to_cpu(hptep[1]) & (HPTE_R_R | HPTE_R_C);
	पूर्ण अन्यथा अणु
		kvmppc_add_revmap_chain(kvm, rev, rmap, index, 0);
	पूर्ण

	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		r = hpte_old_to_new_r(hpte[0], r);
		hpte[0] = hpte_old_to_new_v(hpte[0]);
	पूर्ण
	hptep[1] = cpu_to_be64(r);
	eieio();
	__unlock_hpte(hptep, hpte[0]);
	यंत्र अस्थिर("ptesync" : : : "memory");
	preempt_enable();
	अगर (page && hpte_is_writable(r))
		set_page_dirty_lock(page);

 out_put:
	trace_kvm_page_fault_निकास(vcpu, hpte, ret);

	अगर (page)
		put_page(page);
	वापस ret;

 out_unlock:
	__unlock_hpte(hptep, be64_to_cpu(hptep[0]));
	preempt_enable();
	जाओ out_put;
पूर्ण

व्योम kvmppc_rmap_reset(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_memslots *slots;
	काष्ठा kvm_memory_slot *memslot;
	पूर्णांक srcu_idx;

	srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
	slots = kvm_memslots(kvm);
	kvm_क्रम_each_memslot(memslot, slots) अणु
		/* Mutual exclusion with kvm_unmap_hva_range etc. */
		spin_lock(&kvm->mmu_lock);
		/*
		 * This assumes it is acceptable to lose reference and
		 * change bits across a reset.
		 */
		स_रखो(memslot->arch.rmap, 0,
		       memslot->npages * माप(*memslot->arch.rmap));
		spin_unlock(&kvm->mmu_lock);
	पूर्ण
	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);
पूर्ण

/* Must be called with both HPTE and rmap locked */
अटल व्योम kvmppc_unmap_hpte(काष्ठा kvm *kvm, अचिन्हित दीर्घ i,
			      काष्ठा kvm_memory_slot *memslot,
			      अचिन्हित दीर्घ *rmapp, अचिन्हित दीर्घ gfn)
अणु
	__be64 *hptep = (__be64 *) (kvm->arch.hpt.virt + (i << 4));
	काष्ठा revmap_entry *rev = kvm->arch.hpt.rev;
	अचिन्हित दीर्घ j, h;
	अचिन्हित दीर्घ ptel, psize, rcbits;

	j = rev[i].क्रमw;
	अगर (j == i) अणु
		/* chain is now empty */
		*rmapp &= ~(KVMPPC_RMAP_PRESENT | KVMPPC_RMAP_INDEX);
	पूर्ण अन्यथा अणु
		/* हटाओ i from chain */
		h = rev[i].back;
		rev[h].क्रमw = j;
		rev[j].back = h;
		rev[i].क्रमw = rev[i].back = i;
		*rmapp = (*rmapp & ~KVMPPC_RMAP_INDEX) | j;
	पूर्ण

	/* Now check and modअगरy the HPTE */
	ptel = rev[i].guest_rpte;
	psize = kvmppc_actual_pgsz(be64_to_cpu(hptep[0]), ptel);
	अगर ((be64_to_cpu(hptep[0]) & HPTE_V_VALID) &&
	    hpte_rpn(ptel, psize) == gfn) अणु
		hptep[0] |= cpu_to_be64(HPTE_V_ABSENT);
		kvmppc_invalidate_hpte(kvm, hptep, i);
		hptep[1] &= ~cpu_to_be64(HPTE_R_KEY_HI | HPTE_R_KEY_LO);
		/* Harvest R and C */
		rcbits = be64_to_cpu(hptep[1]) & (HPTE_R_R | HPTE_R_C);
		*rmapp |= rcbits << KVMPPC_RMAP_RC_SHIFT;
		अगर ((rcbits & HPTE_R_C) && memslot->dirty_biपंचांगap)
			kvmppc_update_dirty_map(memslot, gfn, psize);
		अगर (rcbits & ~rev[i].guest_rpte) अणु
			rev[i].guest_rpte = ptel | rcbits;
			note_hpte_modअगरication(kvm, &rev[i]);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम kvm_unmap_rmapp(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *memslot,
			    अचिन्हित दीर्घ gfn)
अणु
	अचिन्हित दीर्घ i;
	__be64 *hptep;
	अचिन्हित दीर्घ *rmapp;

	rmapp = &memslot->arch.rmap[gfn - memslot->base_gfn];
	क्रम (;;) अणु
		lock_rmap(rmapp);
		अगर (!(*rmapp & KVMPPC_RMAP_PRESENT)) अणु
			unlock_rmap(rmapp);
			अवरोध;
		पूर्ण

		/*
		 * To aव्योम an ABBA deadlock with the HPTE lock bit,
		 * we can't spin on the HPTE lock जबतक holding the
		 * rmap chain lock.
		 */
		i = *rmapp & KVMPPC_RMAP_INDEX;
		hptep = (__be64 *) (kvm->arch.hpt.virt + (i << 4));
		अगर (!try_lock_hpte(hptep, HPTE_V_HVLOCK)) अणु
			/* unlock rmap beक्रमe spinning on the HPTE lock */
			unlock_rmap(rmapp);
			जबतक (be64_to_cpu(hptep[0]) & HPTE_V_HVLOCK)
				cpu_relax();
			जारी;
		पूर्ण

		kvmppc_unmap_hpte(kvm, i, memslot, rmapp, gfn);
		unlock_rmap(rmapp);
		__unlock_hpte(hptep, be64_to_cpu(hptep[0]));
	पूर्ण
पूर्ण

bool kvm_unmap_gfn_range_hv(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	gfn_t gfn;

	अगर (kvm_is_radix(kvm)) अणु
		क्रम (gfn = range->start; gfn < range->end; gfn++)
			kvm_unmap_radix(kvm, range->slot, gfn);
	पूर्ण अन्यथा अणु
		क्रम (gfn = range->start; gfn < range->end; gfn++)
			kvm_unmap_rmapp(kvm, range->slot, gfn);
	पूर्ण

	वापस false;
पूर्ण

व्योम kvmppc_core_flush_memslot_hv(काष्ठा kvm *kvm,
				  काष्ठा kvm_memory_slot *memslot)
अणु
	अचिन्हित दीर्घ gfn;
	अचिन्हित दीर्घ n;
	अचिन्हित दीर्घ *rmapp;

	gfn = memslot->base_gfn;
	rmapp = memslot->arch.rmap;
	अगर (kvm_is_radix(kvm)) अणु
		kvmppc_radix_flush_memslot(kvm, memslot);
		वापस;
	पूर्ण

	क्रम (n = memslot->npages; n; --n, ++gfn) अणु
		/*
		 * Testing the present bit without locking is OK because
		 * the memslot has been marked invalid alपढ़ोy, and hence
		 * no new HPTEs referencing this page can be created,
		 * thus the present bit can't go from 0 to 1.
		 */
		अगर (*rmapp & KVMPPC_RMAP_PRESENT)
			kvm_unmap_rmapp(kvm, memslot, gfn);
		++rmapp;
	पूर्ण
पूर्ण

अटल bool kvm_age_rmapp(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *memslot,
			  अचिन्हित दीर्घ gfn)
अणु
	काष्ठा revmap_entry *rev = kvm->arch.hpt.rev;
	अचिन्हित दीर्घ head, i, j;
	__be64 *hptep;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ *rmapp;

	rmapp = &memslot->arch.rmap[gfn - memslot->base_gfn];
 retry:
	lock_rmap(rmapp);
	अगर (*rmapp & KVMPPC_RMAP_REFERENCED) अणु
		*rmapp &= ~KVMPPC_RMAP_REFERENCED;
		ret = 1;
	पूर्ण
	अगर (!(*rmapp & KVMPPC_RMAP_PRESENT)) अणु
		unlock_rmap(rmapp);
		वापस ret;
	पूर्ण

	i = head = *rmapp & KVMPPC_RMAP_INDEX;
	करो अणु
		hptep = (__be64 *) (kvm->arch.hpt.virt + (i << 4));
		j = rev[i].क्रमw;

		/* If this HPTE isn't referenced, ignore it */
		अगर (!(be64_to_cpu(hptep[1]) & HPTE_R_R))
			जारी;

		अगर (!try_lock_hpte(hptep, HPTE_V_HVLOCK)) अणु
			/* unlock rmap beक्रमe spinning on the HPTE lock */
			unlock_rmap(rmapp);
			जबतक (be64_to_cpu(hptep[0]) & HPTE_V_HVLOCK)
				cpu_relax();
			जाओ retry;
		पूर्ण

		/* Now check and modअगरy the HPTE */
		अगर ((be64_to_cpu(hptep[0]) & HPTE_V_VALID) &&
		    (be64_to_cpu(hptep[1]) & HPTE_R_R)) अणु
			kvmppc_clear_ref_hpte(kvm, hptep, i);
			अगर (!(rev[i].guest_rpte & HPTE_R_R)) अणु
				rev[i].guest_rpte |= HPTE_R_R;
				note_hpte_modअगरication(kvm, &rev[i]);
			पूर्ण
			ret = 1;
		पूर्ण
		__unlock_hpte(hptep, be64_to_cpu(hptep[0]));
	पूर्ण जबतक ((i = j) != head);

	unlock_rmap(rmapp);
	वापस ret;
पूर्ण

bool kvm_age_gfn_hv(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	gfn_t gfn;
	bool ret = false;

	अगर (kvm_is_radix(kvm)) अणु
		क्रम (gfn = range->start; gfn < range->end; gfn++)
			ret |= kvm_age_radix(kvm, range->slot, gfn);
	पूर्ण अन्यथा अणु
		क्रम (gfn = range->start; gfn < range->end; gfn++)
			ret |= kvm_age_rmapp(kvm, range->slot, gfn);
	पूर्ण

	वापस ret;
पूर्ण

अटल bool kvm_test_age_rmapp(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *memslot,
			       अचिन्हित दीर्घ gfn)
अणु
	काष्ठा revmap_entry *rev = kvm->arch.hpt.rev;
	अचिन्हित दीर्घ head, i, j;
	अचिन्हित दीर्घ *hp;
	bool ret = true;
	अचिन्हित दीर्घ *rmapp;

	rmapp = &memslot->arch.rmap[gfn - memslot->base_gfn];
	अगर (*rmapp & KVMPPC_RMAP_REFERENCED)
		वापस true;

	lock_rmap(rmapp);
	अगर (*rmapp & KVMPPC_RMAP_REFERENCED)
		जाओ out;

	अगर (*rmapp & KVMPPC_RMAP_PRESENT) अणु
		i = head = *rmapp & KVMPPC_RMAP_INDEX;
		करो अणु
			hp = (अचिन्हित दीर्घ *)(kvm->arch.hpt.virt + (i << 4));
			j = rev[i].क्रमw;
			अगर (be64_to_cpu(hp[1]) & HPTE_R_R)
				जाओ out;
		पूर्ण जबतक ((i = j) != head);
	पूर्ण
	ret = false;

 out:
	unlock_rmap(rmapp);
	वापस ret;
पूर्ण

bool kvm_test_age_gfn_hv(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	WARN_ON(range->start + 1 != range->end);

	अगर (kvm_is_radix(kvm))
		वापस kvm_test_age_radix(kvm, range->slot, range->start);
	अन्यथा
		वापस kvm_test_age_rmapp(kvm, range->slot, range->start);
पूर्ण

bool kvm_set_spte_gfn_hv(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	WARN_ON(range->start + 1 != range->end);

	अगर (kvm_is_radix(kvm))
		kvm_unmap_radix(kvm, range->slot, range->start);
	अन्यथा
		kvm_unmap_rmapp(kvm, range->slot, range->start);

	वापस false;
पूर्ण

अटल पूर्णांक vcpus_running(काष्ठा kvm *kvm)
अणु
	वापस atomic_पढ़ो(&kvm->arch.vcpus_running) != 0;
पूर्ण

/*
 * Returns the number of प्रणाली pages that are dirty.
 * This can be more than 1 अगर we find a huge-page HPTE.
 */
अटल पूर्णांक kvm_test_clear_dirty_npages(काष्ठा kvm *kvm, अचिन्हित दीर्घ *rmapp)
अणु
	काष्ठा revmap_entry *rev = kvm->arch.hpt.rev;
	अचिन्हित दीर्घ head, i, j;
	अचिन्हित दीर्घ n;
	अचिन्हित दीर्घ v, r;
	__be64 *hptep;
	पूर्णांक npages_dirty = 0;

 retry:
	lock_rmap(rmapp);
	अगर (!(*rmapp & KVMPPC_RMAP_PRESENT)) अणु
		unlock_rmap(rmapp);
		वापस npages_dirty;
	पूर्ण

	i = head = *rmapp & KVMPPC_RMAP_INDEX;
	करो अणु
		अचिन्हित दीर्घ hptep1;
		hptep = (__be64 *) (kvm->arch.hpt.virt + (i << 4));
		j = rev[i].क्रमw;

		/*
		 * Checking the C (changed) bit here is racy since there
		 * is no guarantee about when the hardware ग_लिखोs it back.
		 * If the HPTE is not writable then it is stable since the
		 * page can't be written to, and we would have करोne a tlbie
		 * (which क्रमces the hardware to complete any ग_लिखोback)
		 * when making the HPTE पढ़ो-only.
		 * If vcpus are running then this call is racy anyway
		 * since the page could get dirtied subsequently, so we
		 * expect there to be a further call which would pick up
		 * any delayed C bit ग_लिखोback.
		 * Otherwise we need to करो the tlbie even अगर C==0 in
		 * order to pick up any delayed ग_लिखोback of C.
		 */
		hptep1 = be64_to_cpu(hptep[1]);
		अगर (!(hptep1 & HPTE_R_C) &&
		    (!hpte_is_writable(hptep1) || vcpus_running(kvm)))
			जारी;

		अगर (!try_lock_hpte(hptep, HPTE_V_HVLOCK)) अणु
			/* unlock rmap beक्रमe spinning on the HPTE lock */
			unlock_rmap(rmapp);
			जबतक (hptep[0] & cpu_to_be64(HPTE_V_HVLOCK))
				cpu_relax();
			जाओ retry;
		पूर्ण

		/* Now check and modअगरy the HPTE */
		अगर (!(hptep[0] & cpu_to_be64(HPTE_V_VALID))) अणु
			__unlock_hpte(hptep, be64_to_cpu(hptep[0]));
			जारी;
		पूर्ण

		/* need to make it temporarily असलent so C is stable */
		hptep[0] |= cpu_to_be64(HPTE_V_ABSENT);
		kvmppc_invalidate_hpte(kvm, hptep, i);
		v = be64_to_cpu(hptep[0]);
		r = be64_to_cpu(hptep[1]);
		अगर (r & HPTE_R_C) अणु
			hptep[1] = cpu_to_be64(r & ~HPTE_R_C);
			अगर (!(rev[i].guest_rpte & HPTE_R_C)) अणु
				rev[i].guest_rpte |= HPTE_R_C;
				note_hpte_modअगरication(kvm, &rev[i]);
			पूर्ण
			n = kvmppc_actual_pgsz(v, r);
			n = (n + PAGE_SIZE - 1) >> PAGE_SHIFT;
			अगर (n > npages_dirty)
				npages_dirty = n;
			eieio();
		पूर्ण
		v &= ~HPTE_V_ABSENT;
		v |= HPTE_V_VALID;
		__unlock_hpte(hptep, v);
	पूर्ण जबतक ((i = j) != head);

	unlock_rmap(rmapp);
	वापस npages_dirty;
पूर्ण

व्योम kvmppc_harvest_vpa_dirty(काष्ठा kvmppc_vpa *vpa,
			      काष्ठा kvm_memory_slot *memslot,
			      अचिन्हित दीर्घ *map)
अणु
	अचिन्हित दीर्घ gfn;

	अगर (!vpa->dirty || !vpa->pinned_addr)
		वापस;
	gfn = vpa->gpa >> PAGE_SHIFT;
	अगर (gfn < memslot->base_gfn ||
	    gfn >= memslot->base_gfn + memslot->npages)
		वापस;

	vpa->dirty = false;
	अगर (map)
		__set_bit_le(gfn - memslot->base_gfn, map);
पूर्ण

दीर्घ kvmppc_hv_get_dirty_log_hpt(काष्ठा kvm *kvm,
			काष्ठा kvm_memory_slot *memslot, अचिन्हित दीर्घ *map)
अणु
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ *rmapp;

	preempt_disable();
	rmapp = memslot->arch.rmap;
	क्रम (i = 0; i < memslot->npages; ++i) अणु
		पूर्णांक npages = kvm_test_clear_dirty_npages(kvm, rmapp);
		/*
		 * Note that अगर npages > 0 then i must be a multiple of npages,
		 * since we always put huge-page HPTEs in the rmap chain
		 * corresponding to their page base address.
		 */
		अगर (npages)
			set_dirty_bits(map, i, npages);
		++rmapp;
	पूर्ण
	preempt_enable();
	वापस 0;
पूर्ण

व्योम *kvmppc_pin_guest_page(काष्ठा kvm *kvm, अचिन्हित दीर्घ gpa,
			    अचिन्हित दीर्घ *nb_ret)
अणु
	काष्ठा kvm_memory_slot *memslot;
	अचिन्हित दीर्घ gfn = gpa >> PAGE_SHIFT;
	काष्ठा page *page, *pages[1];
	पूर्णांक npages;
	अचिन्हित दीर्घ hva, offset;
	पूर्णांक srcu_idx;

	srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
	memslot = gfn_to_memslot(kvm, gfn);
	अगर (!memslot || (memslot->flags & KVM_MEMSLOT_INVALID))
		जाओ err;
	hva = gfn_to_hva_memslot(memslot, gfn);
	npages = get_user_pages_fast(hva, 1, FOLL_WRITE, pages);
	अगर (npages < 1)
		जाओ err;
	page = pages[0];
	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);

	offset = gpa & (PAGE_SIZE - 1);
	अगर (nb_ret)
		*nb_ret = PAGE_SIZE - offset;
	वापस page_address(page) + offset;

 err:
	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);
	वापस शून्य;
पूर्ण

व्योम kvmppc_unpin_guest_page(काष्ठा kvm *kvm, व्योम *va, अचिन्हित दीर्घ gpa,
			     bool dirty)
अणु
	काष्ठा page *page = virt_to_page(va);
	काष्ठा kvm_memory_slot *memslot;
	अचिन्हित दीर्घ gfn;
	पूर्णांक srcu_idx;

	put_page(page);

	अगर (!dirty)
		वापस;

	/* We need to mark this page dirty in the memslot dirty_biपंचांगap, अगर any */
	gfn = gpa >> PAGE_SHIFT;
	srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
	memslot = gfn_to_memslot(kvm, gfn);
	अगर (memslot && memslot->dirty_biपंचांगap)
		set_bit_le(gfn - memslot->base_gfn, memslot->dirty_biपंचांगap);
	srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);
पूर्ण

/*
 * HPT resizing
 */
अटल पूर्णांक resize_hpt_allocate(काष्ठा kvm_resize_hpt *resize)
अणु
	पूर्णांक rc;

	rc = kvmppc_allocate_hpt(&resize->hpt, resize->order);
	अगर (rc < 0)
		वापस rc;

	resize_hpt_debug(resize, "resize_hpt_allocate(): HPT @ 0x%lx\n",
			 resize->hpt.virt);

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ resize_hpt_rehash_hpte(काष्ठा kvm_resize_hpt *resize,
					    अचिन्हित दीर्घ idx)
अणु
	काष्ठा kvm *kvm = resize->kvm;
	काष्ठा kvm_hpt_info *old = &kvm->arch.hpt;
	काष्ठा kvm_hpt_info *new = &resize->hpt;
	अचिन्हित दीर्घ old_hash_mask = (1ULL << (old->order - 7)) - 1;
	अचिन्हित दीर्घ new_hash_mask = (1ULL << (new->order - 7)) - 1;
	__be64 *hptep, *new_hptep;
	अचिन्हित दीर्घ vpte, rpte, guest_rpte;
	पूर्णांक ret;
	काष्ठा revmap_entry *rev;
	अचिन्हित दीर्घ apsize, avpn, pteg, hash;
	अचिन्हित दीर्घ new_idx, new_pteg, replace_vpte;
	पूर्णांक pshअगरt;

	hptep = (__be64 *)(old->virt + (idx << 4));

	/* Guest is stopped, so new HPTEs can't be added or faulted
	 * in, only unmapped or altered by host actions.  So, it's
	 * safe to check this beक्रमe we take the HPTE lock */
	vpte = be64_to_cpu(hptep[0]);
	अगर (!(vpte & HPTE_V_VALID) && !(vpte & HPTE_V_ABSENT))
		वापस 0; /* nothing to करो */

	जबतक (!try_lock_hpte(hptep, HPTE_V_HVLOCK))
		cpu_relax();

	vpte = be64_to_cpu(hptep[0]);

	ret = 0;
	अगर (!(vpte & HPTE_V_VALID) && !(vpte & HPTE_V_ABSENT))
		/* Nothing to करो */
		जाओ out;

	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		rpte = be64_to_cpu(hptep[1]);
		vpte = hpte_new_to_old_v(vpte, rpte);
	पूर्ण

	/* Unmap */
	rev = &old->rev[idx];
	guest_rpte = rev->guest_rpte;

	ret = -EIO;
	apsize = kvmppc_actual_pgsz(vpte, guest_rpte);
	अगर (!apsize)
		जाओ out;

	अगर (vpte & HPTE_V_VALID) अणु
		अचिन्हित दीर्घ gfn = hpte_rpn(guest_rpte, apsize);
		पूर्णांक srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
		काष्ठा kvm_memory_slot *memslot =
			__gfn_to_memslot(kvm_memslots(kvm), gfn);

		अगर (memslot) अणु
			अचिन्हित दीर्घ *rmapp;
			rmapp = &memslot->arch.rmap[gfn - memslot->base_gfn];

			lock_rmap(rmapp);
			kvmppc_unmap_hpte(kvm, idx, memslot, rmapp, gfn);
			unlock_rmap(rmapp);
		पूर्ण

		srcu_पढ़ो_unlock(&kvm->srcu, srcu_idx);
	पूर्ण

	/* Reload PTE after unmap */
	vpte = be64_to_cpu(hptep[0]);
	BUG_ON(vpte & HPTE_V_VALID);
	BUG_ON(!(vpte & HPTE_V_ABSENT));

	ret = 0;
	अगर (!(vpte & HPTE_V_BOLTED))
		जाओ out;

	rpte = be64_to_cpu(hptep[1]);

	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		vpte = hpte_new_to_old_v(vpte, rpte);
		rpte = hpte_new_to_old_r(rpte);
	पूर्ण

	pshअगरt = kvmppc_hpte_base_page_shअगरt(vpte, rpte);
	avpn = HPTE_V_AVPN_VAL(vpte) & ~(((1ul << pshअगरt) - 1) >> 23);
	pteg = idx / HPTES_PER_GROUP;
	अगर (vpte & HPTE_V_SECONDARY)
		pteg = ~pteg;

	अगर (!(vpte & HPTE_V_1TB_SEG)) अणु
		अचिन्हित दीर्घ offset, vsid;

		/* We only have 28 - 23 bits of offset in avpn */
		offset = (avpn & 0x1f) << 23;
		vsid = avpn >> 5;
		/* We can find more bits from the pteg value */
		अगर (pshअगरt < 23)
			offset |= ((vsid ^ pteg) & old_hash_mask) << pshअगरt;

		hash = vsid ^ (offset >> pshअगरt);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ offset, vsid;

		/* We only have 40 - 23 bits of seg_off in avpn */
		offset = (avpn & 0x1ffff) << 23;
		vsid = avpn >> 17;
		अगर (pshअगरt < 23)
			offset |= ((vsid ^ (vsid << 25) ^ pteg) & old_hash_mask) << pshअगरt;

		hash = vsid ^ (vsid << 25) ^ (offset >> pshअगरt);
	पूर्ण

	new_pteg = hash & new_hash_mask;
	अगर (vpte & HPTE_V_SECONDARY)
		new_pteg = ~hash & new_hash_mask;

	new_idx = new_pteg * HPTES_PER_GROUP + (idx % HPTES_PER_GROUP);
	new_hptep = (__be64 *)(new->virt + (new_idx << 4));

	replace_vpte = be64_to_cpu(new_hptep[0]);
	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		अचिन्हित दीर्घ replace_rpte = be64_to_cpu(new_hptep[1]);
		replace_vpte = hpte_new_to_old_v(replace_vpte, replace_rpte);
	पूर्ण

	अगर (replace_vpte & (HPTE_V_VALID | HPTE_V_ABSENT)) अणु
		BUG_ON(new->order >= old->order);

		अगर (replace_vpte & HPTE_V_BOLTED) अणु
			अगर (vpte & HPTE_V_BOLTED)
				/* Bolted collision, nothing we can करो */
				ret = -ENOSPC;
			/* Discard the new HPTE */
			जाओ out;
		पूर्ण

		/* Discard the previous HPTE */
	पूर्ण

	अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
		rpte = hpte_old_to_new_r(vpte, rpte);
		vpte = hpte_old_to_new_v(vpte);
	पूर्ण

	new_hptep[1] = cpu_to_be64(rpte);
	new->rev[new_idx].guest_rpte = guest_rpte;
	/* No need क्रम a barrier, since new HPT isn't active */
	new_hptep[0] = cpu_to_be64(vpte);
	unlock_hpte(new_hptep, vpte);

out:
	unlock_hpte(hptep, vpte);
	वापस ret;
पूर्ण

अटल पूर्णांक resize_hpt_rehash(काष्ठा kvm_resize_hpt *resize)
अणु
	काष्ठा kvm *kvm = resize->kvm;
	अचिन्हित  दीर्घ i;
	पूर्णांक rc;

	क्रम (i = 0; i < kvmppc_hpt_npte(&kvm->arch.hpt); i++) अणु
		rc = resize_hpt_rehash_hpte(resize, i);
		अगर (rc != 0)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम resize_hpt_pivot(काष्ठा kvm_resize_hpt *resize)
अणु
	काष्ठा kvm *kvm = resize->kvm;
	काष्ठा kvm_hpt_info hpt_पंचांगp;

	/* Exchange the pending tables in the resize काष्ठाure with
	 * the active tables */

	resize_hpt_debug(resize, "resize_hpt_pivot()\n");

	spin_lock(&kvm->mmu_lock);
	यंत्र अस्थिर("ptesync" : : : "memory");

	hpt_पंचांगp = kvm->arch.hpt;
	kvmppc_set_hpt(kvm, &resize->hpt);
	resize->hpt = hpt_पंचांगp;

	spin_unlock(&kvm->mmu_lock);

	synchronize_srcu_expedited(&kvm->srcu);

	अगर (cpu_has_feature(CPU_FTR_ARCH_300))
		kvmppc_setup_partition_table(kvm);

	resize_hpt_debug(resize, "resize_hpt_pivot() done\n");
पूर्ण

अटल व्योम resize_hpt_release(काष्ठा kvm *kvm, काष्ठा kvm_resize_hpt *resize)
अणु
	अगर (WARN_ON(!mutex_is_locked(&kvm->arch.mmu_setup_lock)))
		वापस;

	अगर (!resize)
		वापस;

	अगर (resize->error != -EBUSY) अणु
		अगर (resize->hpt.virt)
			kvmppc_मुक्त_hpt(&resize->hpt);
		kमुक्त(resize);
	पूर्ण

	अगर (kvm->arch.resize_hpt == resize)
		kvm->arch.resize_hpt = शून्य;
पूर्ण

अटल व्योम resize_hpt_prepare_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा kvm_resize_hpt *resize = container_of(work,
						     काष्ठा kvm_resize_hpt,
						     work);
	काष्ठा kvm *kvm = resize->kvm;
	पूर्णांक err = 0;

	अगर (WARN_ON(resize->error != -EBUSY))
		वापस;

	mutex_lock(&kvm->arch.mmu_setup_lock);

	/* Request is still current? */
	अगर (kvm->arch.resize_hpt == resize) अणु
		/* We may request large allocations here:
		 * करो not sleep with kvm->arch.mmu_setup_lock held क्रम a जबतक.
		 */
		mutex_unlock(&kvm->arch.mmu_setup_lock);

		resize_hpt_debug(resize, "resize_hpt_prepare_work(): order = %d\n",
				 resize->order);

		err = resize_hpt_allocate(resize);

		/* We have strict assumption about -EBUSY
		 * when preparing क्रम HPT resize.
		 */
		अगर (WARN_ON(err == -EBUSY))
			err = -EINPROGRESS;

		mutex_lock(&kvm->arch.mmu_setup_lock);
		/* It is possible that kvm->arch.resize_hpt != resize
		 * after we grab kvm->arch.mmu_setup_lock again.
		 */
	पूर्ण

	resize->error = err;

	अगर (kvm->arch.resize_hpt != resize)
		resize_hpt_release(kvm, resize);

	mutex_unlock(&kvm->arch.mmu_setup_lock);
पूर्ण

दीर्घ kvm_vm_ioctl_resize_hpt_prepare(काष्ठा kvm *kvm,
				     काष्ठा kvm_ppc_resize_hpt *rhpt)
अणु
	अचिन्हित दीर्घ flags = rhpt->flags;
	अचिन्हित दीर्घ shअगरt = rhpt->shअगरt;
	काष्ठा kvm_resize_hpt *resize;
	पूर्णांक ret;

	अगर (flags != 0 || kvm_is_radix(kvm))
		वापस -EINVAL;

	अगर (shअगरt && ((shअगरt < 18) || (shअगरt > 46)))
		वापस -EINVAL;

	mutex_lock(&kvm->arch.mmu_setup_lock);

	resize = kvm->arch.resize_hpt;

	अगर (resize) अणु
		अगर (resize->order == shअगरt) अणु
			/* Suitable resize in progress? */
			ret = resize->error;
			अगर (ret == -EBUSY)
				ret = 100; /* estimated समय in ms */
			अन्यथा अगर (ret)
				resize_hpt_release(kvm, resize);

			जाओ out;
		पूर्ण

		/* not suitable, cancel it */
		resize_hpt_release(kvm, resize);
	पूर्ण

	ret = 0;
	अगर (!shअगरt)
		जाओ out; /* nothing to करो */

	/* start new resize */

	resize = kzalloc(माप(*resize), GFP_KERNEL);
	अगर (!resize) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	resize->error = -EBUSY;
	resize->order = shअगरt;
	resize->kvm = kvm;
	INIT_WORK(&resize->work, resize_hpt_prepare_work);
	kvm->arch.resize_hpt = resize;

	schedule_work(&resize->work);

	ret = 100; /* estimated समय in ms */

out:
	mutex_unlock(&kvm->arch.mmu_setup_lock);
	वापस ret;
पूर्ण

अटल व्योम resize_hpt_boot_vcpu(व्योम *opaque)
अणु
	/* Nothing to करो, just क्रमce a KVM निकास */
पूर्ण

दीर्घ kvm_vm_ioctl_resize_hpt_commit(काष्ठा kvm *kvm,
				    काष्ठा kvm_ppc_resize_hpt *rhpt)
अणु
	अचिन्हित दीर्घ flags = rhpt->flags;
	अचिन्हित दीर्घ shअगरt = rhpt->shअगरt;
	काष्ठा kvm_resize_hpt *resize;
	दीर्घ ret;

	अगर (flags != 0 || kvm_is_radix(kvm))
		वापस -EINVAL;

	अगर (shअगरt && ((shअगरt < 18) || (shअगरt > 46)))
		वापस -EINVAL;

	mutex_lock(&kvm->arch.mmu_setup_lock);

	resize = kvm->arch.resize_hpt;

	/* This shouldn't be possible */
	ret = -EIO;
	अगर (WARN_ON(!kvm->arch.mmu_पढ़ोy))
		जाओ out_no_hpt;

	/* Stop VCPUs from running जबतक we mess with the HPT */
	kvm->arch.mmu_पढ़ोy = 0;
	smp_mb();

	/* Boot all CPUs out of the guest so they re-पढ़ो
	 * mmu_पढ़ोy */
	on_each_cpu(resize_hpt_boot_vcpu, शून्य, 1);

	ret = -ENXIO;
	अगर (!resize || (resize->order != shअगरt))
		जाओ out;

	ret = resize->error;
	अगर (ret)
		जाओ out;

	ret = resize_hpt_rehash(resize);
	अगर (ret)
		जाओ out;

	resize_hpt_pivot(resize);

out:
	/* Let VCPUs run again */
	kvm->arch.mmu_पढ़ोy = 1;
	smp_mb();
out_no_hpt:
	resize_hpt_release(kvm, resize);
	mutex_unlock(&kvm->arch.mmu_setup_lock);
	वापस ret;
पूर्ण

/*
 * Functions क्रम पढ़ोing and writing the hash table via पढ़ोs and
 * ग_लिखोs on a file descriptor.
 *
 * Reads वापस the guest view of the hash table, which has to be
 * pieced together from the real hash table and the guest_rpte
 * values in the revmap array.
 *
 * On ग_लिखोs, each HPTE written is considered in turn, and अगर it
 * is valid, it is written to the HPT as अगर an H_ENTER with the
 * exact flag set was करोne.  When the invalid count is non-zero
 * in the header written to the stream, the kernel will make
 * sure that that many HPTEs are invalid, and invalidate them
 * अगर not.
 */

काष्ठा kvm_htab_ctx अणु
	अचिन्हित दीर्घ	index;
	अचिन्हित दीर्घ	flags;
	काष्ठा kvm	*kvm;
	पूर्णांक		first_pass;
पूर्ण;

#घोषणा HPTE_SIZE	(2 * माप(अचिन्हित दीर्घ))

/*
 * Returns 1 अगर this HPT entry has been modअगरied or has pending
 * R/C bit changes.
 */
अटल पूर्णांक hpte_dirty(काष्ठा revmap_entry *revp, __be64 *hptp)
अणु
	अचिन्हित दीर्घ rcbits_unset;

	अगर (revp->guest_rpte & HPTE_GR_MODIFIED)
		वापस 1;

	/* Also need to consider changes in reference and changed bits */
	rcbits_unset = ~revp->guest_rpte & (HPTE_R_R | HPTE_R_C);
	अगर ((be64_to_cpu(hptp[0]) & HPTE_V_VALID) &&
	    (be64_to_cpu(hptp[1]) & rcbits_unset))
		वापस 1;

	वापस 0;
पूर्ण

अटल दीर्घ record_hpte(अचिन्हित दीर्घ flags, __be64 *hptp,
			अचिन्हित दीर्घ *hpte, काष्ठा revmap_entry *revp,
			पूर्णांक want_valid, पूर्णांक first_pass)
अणु
	अचिन्हित दीर्घ v, r, hr;
	अचिन्हित दीर्घ rcbits_unset;
	पूर्णांक ok = 1;
	पूर्णांक valid, dirty;

	/* Unmodअगरied entries are unपूर्णांकeresting except on the first pass */
	dirty = hpte_dirty(revp, hptp);
	अगर (!first_pass && !dirty)
		वापस 0;

	valid = 0;
	अगर (be64_to_cpu(hptp[0]) & (HPTE_V_VALID | HPTE_V_ABSENT)) अणु
		valid = 1;
		अगर ((flags & KVM_GET_HTAB_BOLTED_ONLY) &&
		    !(be64_to_cpu(hptp[0]) & HPTE_V_BOLTED))
			valid = 0;
	पूर्ण
	अगर (valid != want_valid)
		वापस 0;

	v = r = 0;
	अगर (valid || dirty) अणु
		/* lock the HPTE so it's stable and पढ़ो it */
		preempt_disable();
		जबतक (!try_lock_hpte(hptp, HPTE_V_HVLOCK))
			cpu_relax();
		v = be64_to_cpu(hptp[0]);
		hr = be64_to_cpu(hptp[1]);
		अगर (cpu_has_feature(CPU_FTR_ARCH_300)) अणु
			v = hpte_new_to_old_v(v, hr);
			hr = hpte_new_to_old_r(hr);
		पूर्ण

		/* re-evaluate valid and dirty from synchronized HPTE value */
		valid = !!(v & HPTE_V_VALID);
		dirty = !!(revp->guest_rpte & HPTE_GR_MODIFIED);

		/* Harvest R and C पूर्णांकo guest view अगर necessary */
		rcbits_unset = ~revp->guest_rpte & (HPTE_R_R | HPTE_R_C);
		अगर (valid && (rcbits_unset & hr)) अणु
			revp->guest_rpte |= (hr &
				(HPTE_R_R | HPTE_R_C)) | HPTE_GR_MODIFIED;
			dirty = 1;
		पूर्ण

		अगर (v & HPTE_V_ABSENT) अणु
			v &= ~HPTE_V_ABSENT;
			v |= HPTE_V_VALID;
			valid = 1;
		पूर्ण
		अगर ((flags & KVM_GET_HTAB_BOLTED_ONLY) && !(v & HPTE_V_BOLTED))
			valid = 0;

		r = revp->guest_rpte;
		/* only clear modअगरied अगर this is the right sort of entry */
		अगर (valid == want_valid && dirty) अणु
			r &= ~HPTE_GR_MODIFIED;
			revp->guest_rpte = r;
		पूर्ण
		unlock_hpte(hptp, be64_to_cpu(hptp[0]));
		preempt_enable();
		अगर (!(valid == want_valid && (first_pass || dirty)))
			ok = 0;
	पूर्ण
	hpte[0] = cpu_to_be64(v);
	hpte[1] = cpu_to_be64(r);
	वापस ok;
पूर्ण

अटल sमाप_प्रकार kvm_htab_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा kvm_htab_ctx *ctx = file->निजी_data;
	काष्ठा kvm *kvm = ctx->kvm;
	काष्ठा kvm_get_htab_header hdr;
	__be64 *hptp;
	काष्ठा revmap_entry *revp;
	अचिन्हित दीर्घ i, nb, nw;
	अचिन्हित दीर्घ __user *lbuf;
	काष्ठा kvm_get_htab_header __user *hptr;
	अचिन्हित दीर्घ flags;
	पूर्णांक first_pass;
	अचिन्हित दीर्घ hpte[2];

	अगर (!access_ok(buf, count))
		वापस -EFAULT;
	अगर (kvm_is_radix(kvm))
		वापस 0;

	first_pass = ctx->first_pass;
	flags = ctx->flags;

	i = ctx->index;
	hptp = (__be64 *)(kvm->arch.hpt.virt + (i * HPTE_SIZE));
	revp = kvm->arch.hpt.rev + i;
	lbuf = (अचिन्हित दीर्घ __user *)buf;

	nb = 0;
	जबतक (nb + माप(hdr) + HPTE_SIZE < count) अणु
		/* Initialize header */
		hptr = (काष्ठा kvm_get_htab_header __user *)buf;
		hdr.n_valid = 0;
		hdr.n_invalid = 0;
		nw = nb;
		nb += माप(hdr);
		lbuf = (अचिन्हित दीर्घ __user *)(buf + माप(hdr));

		/* Skip unपूर्णांकeresting entries, i.e. clean on not-first pass */
		अगर (!first_pass) अणु
			जबतक (i < kvmppc_hpt_npte(&kvm->arch.hpt) &&
			       !hpte_dirty(revp, hptp)) अणु
				++i;
				hptp += 2;
				++revp;
			पूर्ण
		पूर्ण
		hdr.index = i;

		/* Grab a series of valid entries */
		जबतक (i < kvmppc_hpt_npte(&kvm->arch.hpt) &&
		       hdr.n_valid < 0xffff &&
		       nb + HPTE_SIZE < count &&
		       record_hpte(flags, hptp, hpte, revp, 1, first_pass)) अणु
			/* valid entry, ग_लिखो it out */
			++hdr.n_valid;
			अगर (__put_user(hpte[0], lbuf) ||
			    __put_user(hpte[1], lbuf + 1))
				वापस -EFAULT;
			nb += HPTE_SIZE;
			lbuf += 2;
			++i;
			hptp += 2;
			++revp;
		पूर्ण
		/* Now skip invalid entries जबतक we can */
		जबतक (i < kvmppc_hpt_npte(&kvm->arch.hpt) &&
		       hdr.n_invalid < 0xffff &&
		       record_hpte(flags, hptp, hpte, revp, 0, first_pass)) अणु
			/* found an invalid entry */
			++hdr.n_invalid;
			++i;
			hptp += 2;
			++revp;
		पूर्ण

		अगर (hdr.n_valid || hdr.n_invalid) अणु
			/* ग_लिखो back the header */
			अगर (__copy_to_user(hptr, &hdr, माप(hdr)))
				वापस -EFAULT;
			nw = nb;
			buf = (अक्षर __user *)lbuf;
		पूर्ण अन्यथा अणु
			nb = nw;
		पूर्ण

		/* Check अगर we've wrapped around the hash table */
		अगर (i >= kvmppc_hpt_npte(&kvm->arch.hpt)) अणु
			i = 0;
			ctx->first_pass = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	ctx->index = i;

	वापस nb;
पूर्ण

अटल sमाप_प्रकार kvm_htab_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा kvm_htab_ctx *ctx = file->निजी_data;
	काष्ठा kvm *kvm = ctx->kvm;
	काष्ठा kvm_get_htab_header hdr;
	अचिन्हित दीर्घ i, j;
	अचिन्हित दीर्घ v, r;
	अचिन्हित दीर्घ __user *lbuf;
	__be64 *hptp;
	अचिन्हित दीर्घ पंचांगp[2];
	sमाप_प्रकार nb;
	दीर्घ पूर्णांक err, ret;
	पूर्णांक mmu_पढ़ोy;
	पूर्णांक pshअगरt;

	अगर (!access_ok(buf, count))
		वापस -EFAULT;
	अगर (kvm_is_radix(kvm))
		वापस -EINVAL;

	/* lock out vcpus from running जबतक we're करोing this */
	mutex_lock(&kvm->arch.mmu_setup_lock);
	mmu_पढ़ोy = kvm->arch.mmu_पढ़ोy;
	अगर (mmu_पढ़ोy) अणु
		kvm->arch.mmu_पढ़ोy = 0;	/* temporarily */
		/* order mmu_पढ़ोy vs. vcpus_running */
		smp_mb();
		अगर (atomic_पढ़ो(&kvm->arch.vcpus_running)) अणु
			kvm->arch.mmu_पढ़ोy = 1;
			mutex_unlock(&kvm->arch.mmu_setup_lock);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	err = 0;
	क्रम (nb = 0; nb + माप(hdr) <= count; ) अणु
		err = -EFAULT;
		अगर (__copy_from_user(&hdr, buf, माप(hdr)))
			अवरोध;

		err = 0;
		अगर (nb + hdr.n_valid * HPTE_SIZE > count)
			अवरोध;

		nb += माप(hdr);
		buf += माप(hdr);

		err = -EINVAL;
		i = hdr.index;
		अगर (i >= kvmppc_hpt_npte(&kvm->arch.hpt) ||
		    i + hdr.n_valid + hdr.n_invalid > kvmppc_hpt_npte(&kvm->arch.hpt))
			अवरोध;

		hptp = (__be64 *)(kvm->arch.hpt.virt + (i * HPTE_SIZE));
		lbuf = (अचिन्हित दीर्घ __user *)buf;
		क्रम (j = 0; j < hdr.n_valid; ++j) अणु
			__be64 hpte_v;
			__be64 hpte_r;

			err = -EFAULT;
			अगर (__get_user(hpte_v, lbuf) ||
			    __get_user(hpte_r, lbuf + 1))
				जाओ out;
			v = be64_to_cpu(hpte_v);
			r = be64_to_cpu(hpte_r);
			err = -EINVAL;
			अगर (!(v & HPTE_V_VALID))
				जाओ out;
			pshअगरt = kvmppc_hpte_base_page_shअगरt(v, r);
			अगर (pshअगरt <= 0)
				जाओ out;
			lbuf += 2;
			nb += HPTE_SIZE;

			अगर (be64_to_cpu(hptp[0]) & (HPTE_V_VALID | HPTE_V_ABSENT))
				kvmppc_करो_h_हटाओ(kvm, 0, i, 0, पंचांगp);
			err = -EIO;
			ret = kvmppc_virपंचांगode_करो_h_enter(kvm, H_EXACT, i, v, r,
							 पंचांगp);
			अगर (ret != H_SUCCESS) अणु
				pr_err("kvm_htab_write ret %ld i=%ld v=%lx "
				       "r=%lx\n", ret, i, v, r);
				जाओ out;
			पूर्ण
			अगर (!mmu_पढ़ोy && is_vrma_hpte(v)) अणु
				अचिन्हित दीर्घ senc, lpcr;

				senc = slb_pgsize_encoding(1ul << pshअगरt);
				kvm->arch.vrma_slb_v = senc | SLB_VSID_B_1T |
					(VRMA_VSID << SLB_VSID_SHIFT_1T);
				अगर (!cpu_has_feature(CPU_FTR_ARCH_300)) अणु
					lpcr = senc << (LPCR_VRMASD_SH - 4);
					kvmppc_update_lpcr(kvm, lpcr,
							   LPCR_VRMASD);
				पूर्ण अन्यथा अणु
					kvmppc_setup_partition_table(kvm);
				पूर्ण
				mmu_पढ़ोy = 1;
			पूर्ण
			++i;
			hptp += 2;
		पूर्ण

		क्रम (j = 0; j < hdr.n_invalid; ++j) अणु
			अगर (be64_to_cpu(hptp[0]) & (HPTE_V_VALID | HPTE_V_ABSENT))
				kvmppc_करो_h_हटाओ(kvm, 0, i, 0, पंचांगp);
			++i;
			hptp += 2;
		पूर्ण
		err = 0;
	पूर्ण

 out:
	/* Order HPTE updates vs. mmu_पढ़ोy */
	smp_wmb();
	kvm->arch.mmu_पढ़ोy = mmu_पढ़ोy;
	mutex_unlock(&kvm->arch.mmu_setup_lock);

	अगर (err)
		वापस err;
	वापस nb;
पूर्ण

अटल पूर्णांक kvm_htab_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा kvm_htab_ctx *ctx = filp->निजी_data;

	filp->निजी_data = शून्य;
	अगर (!(ctx->flags & KVM_GET_HTAB_WRITE))
		atomic_dec(&ctx->kvm->arch.hpte_mod_पूर्णांकerest);
	kvm_put_kvm(ctx->kvm);
	kमुक्त(ctx);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations kvm_htab_fops = अणु
	.पढ़ो		= kvm_htab_पढ़ो,
	.ग_लिखो		= kvm_htab_ग_लिखो,
	.llseek		= शेष_llseek,
	.release	= kvm_htab_release,
पूर्ण;

पूर्णांक kvm_vm_ioctl_get_htab_fd(काष्ठा kvm *kvm, काष्ठा kvm_get_htab_fd *ghf)
अणु
	पूर्णांक ret;
	काष्ठा kvm_htab_ctx *ctx;
	पूर्णांक rwflag;

	/* reject flags we करोn't recognize */
	अगर (ghf->flags & ~(KVM_GET_HTAB_BOLTED_ONLY | KVM_GET_HTAB_WRITE))
		वापस -EINVAL;
	ctx = kzalloc(माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;
	kvm_get_kvm(kvm);
	ctx->kvm = kvm;
	ctx->index = ghf->start_index;
	ctx->flags = ghf->flags;
	ctx->first_pass = 1;

	rwflag = (ghf->flags & KVM_GET_HTAB_WRITE) ? O_WRONLY : O_RDONLY;
	ret = anon_inode_getfd("kvm-htab", &kvm_htab_fops, ctx, rwflag | O_CLOEXEC);
	अगर (ret < 0) अणु
		kमुक्त(ctx);
		kvm_put_kvm_no_destroy(kvm);
		वापस ret;
	पूर्ण

	अगर (rwflag == O_RDONLY) अणु
		mutex_lock(&kvm->slots_lock);
		atomic_inc(&kvm->arch.hpte_mod_पूर्णांकerest);
		/* make sure kvmppc_करो_h_enter etc. see the increment */
		synchronize_srcu_expedited(&kvm->srcu);
		mutex_unlock(&kvm->slots_lock);
	पूर्ण

	वापस ret;
पूर्ण

काष्ठा debugfs_htab_state अणु
	काष्ठा kvm	*kvm;
	काष्ठा mutex	mutex;
	अचिन्हित दीर्घ	hpt_index;
	पूर्णांक		अक्षरs_left;
	पूर्णांक		buf_index;
	अक्षर		buf[64];
पूर्ण;

अटल पूर्णांक debugfs_htab_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा kvm *kvm = inode->i_निजी;
	काष्ठा debugfs_htab_state *p;

	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	kvm_get_kvm(kvm);
	p->kvm = kvm;
	mutex_init(&p->mutex);
	file->निजी_data = p;

	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल पूर्णांक debugfs_htab_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा debugfs_htab_state *p = file->निजी_data;

	kvm_put_kvm(p->kvm);
	kमुक्त(p);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार debugfs_htab_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				 माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा debugfs_htab_state *p = file->निजी_data;
	sमाप_प्रकार ret, r;
	अचिन्हित दीर्घ i, n;
	अचिन्हित दीर्घ v, hr, gr;
	काष्ठा kvm *kvm;
	__be64 *hptp;

	kvm = p->kvm;
	अगर (kvm_is_radix(kvm))
		वापस 0;

	ret = mutex_lock_पूर्णांकerruptible(&p->mutex);
	अगर (ret)
		वापस ret;

	अगर (p->अक्षरs_left) अणु
		n = p->अक्षरs_left;
		अगर (n > len)
			n = len;
		r = copy_to_user(buf, p->buf + p->buf_index, n);
		n -= r;
		p->अक्षरs_left -= n;
		p->buf_index += n;
		buf += n;
		len -= n;
		ret = n;
		अगर (r) अणु
			अगर (!n)
				ret = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण

	i = p->hpt_index;
	hptp = (__be64 *)(kvm->arch.hpt.virt + (i * HPTE_SIZE));
	क्रम (; len != 0 && i < kvmppc_hpt_npte(&kvm->arch.hpt);
	     ++i, hptp += 2) अणु
		अगर (!(be64_to_cpu(hptp[0]) & (HPTE_V_VALID | HPTE_V_ABSENT)))
			जारी;

		/* lock the HPTE so it's stable and पढ़ो it */
		preempt_disable();
		जबतक (!try_lock_hpte(hptp, HPTE_V_HVLOCK))
			cpu_relax();
		v = be64_to_cpu(hptp[0]) & ~HPTE_V_HVLOCK;
		hr = be64_to_cpu(hptp[1]);
		gr = kvm->arch.hpt.rev[i].guest_rpte;
		unlock_hpte(hptp, v);
		preempt_enable();

		अगर (!(v & (HPTE_V_VALID | HPTE_V_ABSENT)))
			जारी;

		n = scnम_लिखो(p->buf, माप(p->buf),
			      "%6lx %.16lx %.16lx %.16lx\n",
			      i, v, hr, gr);
		p->अक्षरs_left = n;
		अगर (n > len)
			n = len;
		r = copy_to_user(buf, p->buf, n);
		n -= r;
		p->अक्षरs_left -= n;
		p->buf_index = n;
		buf += n;
		len -= n;
		ret += n;
		अगर (r) अणु
			अगर (!ret)
				ret = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण
	p->hpt_index = i;

 out:
	mutex_unlock(&p->mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार debugfs_htab_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			   माप_प्रकार len, loff_t *ppos)
अणु
	वापस -EACCES;
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_htab_fops = अणु
	.owner	 = THIS_MODULE,
	.खोलो	 = debugfs_htab_खोलो,
	.release = debugfs_htab_release,
	.पढ़ो	 = debugfs_htab_पढ़ो,
	.ग_लिखो	 = debugfs_htab_ग_लिखो,
	.llseek	 = generic_file_llseek,
पूर्ण;

व्योम kvmppc_mmu_debugfs_init(काष्ठा kvm *kvm)
अणु
	debugfs_create_file("htab", 0400, kvm->arch.debugfs_dir, kvm,
			    &debugfs_htab_fops);
पूर्ण

व्योम kvmppc_mmu_book3s_hv_init(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_mmu *mmu = &vcpu->arch.mmu;

	vcpu->arch.slb_nr = 32;		/* POWER7/POWER8 */

	mmu->xlate = kvmppc_mmu_book3s_64_hv_xlate;

	vcpu->arch.hflags |= BOOK3S_HFLAG_SLB;
पूर्ण
