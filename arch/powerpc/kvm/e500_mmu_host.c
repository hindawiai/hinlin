<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008-2013 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Author: Yu Liu, yu.liu@मुक्तscale.com
 *         Scott Wood, scottwood@मुक्तscale.com
 *         Ashish Kalra, ashish.kalra@मुक्तscale.com
 *         Varun Sethi, varun.sethi@मुक्तscale.com
 *         Alexander Graf, agraf@suse.de
 *
 * Description:
 * This file is based on arch/घातerpc/kvm/44x_tlb.c,
 * by Hollis Blanअक्षरd <hollisb@us.ibm.com>.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/log2.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/hugetlb.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/pte-walk.h>

#समावेश "e500.h"
#समावेश "timing.h"
#समावेश "e500_mmu_host.h"

#समावेश "trace_booke.h"

#घोषणा to_htlb1_esel(esel) (host_tlb_params[1].entries - (esel) - 1)

अटल काष्ठा kvmppc_e500_tlb_params host_tlb_params[E500_TLB_NUM];

अटल अंतरभूत अचिन्हित पूर्णांक tlb1_max_shaकरोw_size(व्योम)
अणु
	/* reserve one entry क्रम magic page */
	वापस host_tlb_params[1].entries - tlbcam_index - 1;
पूर्ण

अटल अंतरभूत u32 e500_shaकरोw_mas3_attrib(u32 mas3, पूर्णांक usermode)
अणु
	/* Mask off reserved bits. */
	mas3 &= MAS3_ATTRIB_MASK;

#अगर_अघोषित CONFIG_KVM_BOOKE_HV
	अगर (!usermode) अणु
		/* Guest is in supervisor mode,
		 * so we need to translate guest
		 * supervisor permissions पूर्णांकo user permissions. */
		mas3 &= ~E500_TLB_USER_PERM_MASK;
		mas3 |= (mas3 & E500_TLB_SUPER_PERM_MASK) << 1;
	पूर्ण
	mas3 |= E500_TLB_SUPER_PERM_MASK;
#पूर्ण_अगर
	वापस mas3;
पूर्ण

/*
 * writing shaकरोw tlb entry to host TLB
 */
अटल अंतरभूत व्योम __ग_लिखो_host_tlbe(काष्ठा kvm_book3e_206_tlb_entry *stlbe,
				     uपूर्णांक32_t mas0,
				     uपूर्णांक32_t lpid)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	mtspr(SPRN_MAS0, mas0);
	mtspr(SPRN_MAS1, stlbe->mas1);
	mtspr(SPRN_MAS2, (अचिन्हित दीर्घ)stlbe->mas2);
	mtspr(SPRN_MAS3, (u32)stlbe->mas7_3);
	mtspr(SPRN_MAS7, (u32)(stlbe->mas7_3 >> 32));
#अगर_घोषित CONFIG_KVM_BOOKE_HV
	mtspr(SPRN_MAS8, MAS8_TGS | get_thपढ़ो_specअगरic_lpid(lpid));
#पूर्ण_अगर
	यंत्र अस्थिर("isync; tlbwe" : : : "memory");

#अगर_घोषित CONFIG_KVM_BOOKE_HV
	/* Must clear mas8 क्रम other host tlbwe's */
	mtspr(SPRN_MAS8, 0);
	isync();
#पूर्ण_अगर
	local_irq_restore(flags);

	trace_kvm_booke206_stlb_ग_लिखो(mas0, stlbe->mas8, stlbe->mas1,
	                              stlbe->mas2, stlbe->mas7_3);
पूर्ण

/*
 * Acquire a mas0 with victim hपूर्णांक, as अगर we just took a TLB miss.
 *
 * We करोn't care about the address we're searching for, other than that it's
 * in the right set and is not present in the TLB.  Using a zero PID and a
 * userspace address means we करोn't have to set and then restore MAS5, or
 * calculate a proper MAS6 value.
 */
अटल u32 get_host_mas0(अचिन्हित दीर्घ eaddr)
अणु
	अचिन्हित दीर्घ flags;
	u32 mas0;
	u32 mas4;

	local_irq_save(flags);
	mtspr(SPRN_MAS6, 0);
	mas4 = mfspr(SPRN_MAS4);
	mtspr(SPRN_MAS4, mas4 & ~MAS4_TLBSEL_MASK);
	यंत्र अस्थिर("tlbsx 0, %0" : : "b" (eaddr & ~CONFIG_PAGE_OFFSET));
	mas0 = mfspr(SPRN_MAS0);
	mtspr(SPRN_MAS4, mas4);
	local_irq_restore(flags);

	वापस mas0;
पूर्ण

/* sesel is क्रम tlb1 only */
अटल अंतरभूत व्योम ग_लिखो_host_tlbe(काष्ठा kvmppc_vcpu_e500 *vcpu_e500,
		पूर्णांक tlbsel, पूर्णांक sesel, काष्ठा kvm_book3e_206_tlb_entry *stlbe)
अणु
	u32 mas0;

	अगर (tlbsel == 0) अणु
		mas0 = get_host_mas0(stlbe->mas2);
		__ग_लिखो_host_tlbe(stlbe, mas0, vcpu_e500->vcpu.kvm->arch.lpid);
	पूर्ण अन्यथा अणु
		__ग_लिखो_host_tlbe(stlbe,
				  MAS0_TLBSEL(1) |
				  MAS0_ESEL(to_htlb1_esel(sesel)),
				  vcpu_e500->vcpu.kvm->arch.lpid);
	पूर्ण
पूर्ण

/* sesel is क्रम tlb1 only */
अटल व्योम ग_लिखो_stlbe(काष्ठा kvmppc_vcpu_e500 *vcpu_e500,
			काष्ठा kvm_book3e_206_tlb_entry *gtlbe,
			काष्ठा kvm_book3e_206_tlb_entry *stlbe,
			पूर्णांक stlbsel, पूर्णांक sesel)
अणु
	पूर्णांक stid;

	preempt_disable();
	stid = kvmppc_e500_get_tlb_stid(&vcpu_e500->vcpu, gtlbe);

	stlbe->mas1 |= MAS1_TID(stid);
	ग_लिखो_host_tlbe(vcpu_e500, stlbsel, sesel, stlbe);
	preempt_enable();
पूर्ण

#अगर_घोषित CONFIG_KVM_E500V2
/* XXX should be a hook in the gva2hpa translation */
व्योम kvmppc_map_magic(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	काष्ठा kvm_book3e_206_tlb_entry magic;
	uदीर्घ shared_page = ((uदीर्घ)vcpu->arch.shared) & PAGE_MASK;
	अचिन्हित पूर्णांक stid;
	kvm_pfn_t pfn;

	pfn = (kvm_pfn_t)virt_to_phys((व्योम *)shared_page) >> PAGE_SHIFT;
	get_page(pfn_to_page(pfn));

	preempt_disable();
	stid = kvmppc_e500_get_sid(vcpu_e500, 0, 0, 0, 0);

	magic.mas1 = MAS1_VALID | MAS1_TS | MAS1_TID(stid) |
		     MAS1_TSIZE(BOOK3E_PAGESZ_4K);
	magic.mas2 = vcpu->arch.magic_page_ea | MAS2_M;
	magic.mas7_3 = ((u64)pfn << PAGE_SHIFT) |
		       MAS3_SW | MAS3_SR | MAS3_UW | MAS3_UR;
	magic.mas8 = 0;

	__ग_लिखो_host_tlbe(&magic, MAS0_TLBSEL(1) | MAS0_ESEL(tlbcam_index), 0);
	preempt_enable();
पूर्ण
#पूर्ण_अगर

व्योम inval_gtlbe_on_host(काष्ठा kvmppc_vcpu_e500 *vcpu_e500, पूर्णांक tlbsel,
			 पूर्णांक esel)
अणु
	काष्ठा kvm_book3e_206_tlb_entry *gtlbe =
		get_entry(vcpu_e500, tlbsel, esel);
	काष्ठा tlbe_ref *ref = &vcpu_e500->gtlb_priv[tlbsel][esel].ref;

	/* Don't bother with unmapped entries */
	अगर (!(ref->flags & E500_TLB_VALID)) अणु
		WARN(ref->flags & (E500_TLB_BITMAP | E500_TLB_TLB0),
		     "%s: flags %x\n", __func__, ref->flags);
		WARN_ON(tlbsel == 1 && vcpu_e500->g2h_tlb1_map[esel]);
	पूर्ण

	अगर (tlbsel == 1 && ref->flags & E500_TLB_BITMAP) अणु
		u64 पंचांगp = vcpu_e500->g2h_tlb1_map[esel];
		पूर्णांक hw_tlb_indx;
		अचिन्हित दीर्घ flags;

		local_irq_save(flags);
		जबतक (पंचांगp) अणु
			hw_tlb_indx = __ilog2_u64(पंचांगp & -पंचांगp);
			mtspr(SPRN_MAS0,
			      MAS0_TLBSEL(1) |
			      MAS0_ESEL(to_htlb1_esel(hw_tlb_indx)));
			mtspr(SPRN_MAS1, 0);
			यंत्र अस्थिर("tlbwe");
			vcpu_e500->h2g_tlb1_rmap[hw_tlb_indx] = 0;
			पंचांगp &= पंचांगp - 1;
		पूर्ण
		mb();
		vcpu_e500->g2h_tlb1_map[esel] = 0;
		ref->flags &= ~(E500_TLB_BITMAP | E500_TLB_VALID);
		local_irq_restore(flags);
	पूर्ण

	अगर (tlbsel == 1 && ref->flags & E500_TLB_TLB0) अणु
		/*
		 * TLB1 entry is backed by 4k pages. This should happen
		 * rarely and is not worth optimizing. Invalidate everything.
		 */
		kvmppc_e500_tlbil_all(vcpu_e500);
		ref->flags &= ~(E500_TLB_TLB0 | E500_TLB_VALID);
	पूर्ण

	/*
	 * If TLB entry is still valid then it's a TLB0 entry, and thus
	 * backed by at most one host tlbe per shaकरोw pid
	 */
	अगर (ref->flags & E500_TLB_VALID)
		kvmppc_e500_tlbil_one(vcpu_e500, gtlbe);

	/* Mark the TLB as not backed by the host anymore */
	ref->flags = 0;
पूर्ण

अटल अंतरभूत पूर्णांक tlbe_is_writable(काष्ठा kvm_book3e_206_tlb_entry *tlbe)
अणु
	वापस tlbe->mas7_3 & (MAS3_SW|MAS3_UW);
पूर्ण

अटल अंतरभूत व्योम kvmppc_e500_ref_setup(काष्ठा tlbe_ref *ref,
					 काष्ठा kvm_book3e_206_tlb_entry *gtlbe,
					 kvm_pfn_t pfn, अचिन्हित पूर्णांक wimg)
अणु
	ref->pfn = pfn;
	ref->flags = E500_TLB_VALID;

	/* Use guest supplied MAS2_G and MAS2_E */
	ref->flags |= (gtlbe->mas2 & MAS2_ATTRIB_MASK) | wimg;

	/* Mark the page accessed */
	kvm_set_pfn_accessed(pfn);

	अगर (tlbe_is_writable(gtlbe))
		kvm_set_pfn_dirty(pfn);
पूर्ण

अटल अंतरभूत व्योम kvmppc_e500_ref_release(काष्ठा tlbe_ref *ref)
अणु
	अगर (ref->flags & E500_TLB_VALID) अणु
		/* FIXME: करोn't log bogus pfn क्रम TLB1 */
		trace_kvm_booke206_ref_release(ref->pfn, ref->flags);
		ref->flags = 0;
	पूर्ण
पूर्ण

अटल व्योम clear_tlb1_biपंचांगap(काष्ठा kvmppc_vcpu_e500 *vcpu_e500)
अणु
	अगर (vcpu_e500->g2h_tlb1_map)
		स_रखो(vcpu_e500->g2h_tlb1_map, 0,
		       माप(u64) * vcpu_e500->gtlb_params[1].entries);
	अगर (vcpu_e500->h2g_tlb1_rmap)
		स_रखो(vcpu_e500->h2g_tlb1_rmap, 0,
		       माप(अचिन्हित पूर्णांक) * host_tlb_params[1].entries);
पूर्ण

अटल व्योम clear_tlb_privs(काष्ठा kvmppc_vcpu_e500 *vcpu_e500)
अणु
	पूर्णांक tlbsel;
	पूर्णांक i;

	क्रम (tlbsel = 0; tlbsel <= 1; tlbsel++) अणु
		क्रम (i = 0; i < vcpu_e500->gtlb_params[tlbsel].entries; i++) अणु
			काष्ठा tlbe_ref *ref =
				&vcpu_e500->gtlb_priv[tlbsel][i].ref;
			kvmppc_e500_ref_release(ref);
		पूर्ण
	पूर्ण
पूर्ण

व्योम kvmppc_core_flush_tlb(काष्ठा kvm_vcpu *vcpu)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	kvmppc_e500_tlbil_all(vcpu_e500);
	clear_tlb_privs(vcpu_e500);
	clear_tlb1_biपंचांगap(vcpu_e500);
पूर्ण

/* TID must be supplied by the caller */
अटल व्योम kvmppc_e500_setup_stlbe(
	काष्ठा kvm_vcpu *vcpu,
	काष्ठा kvm_book3e_206_tlb_entry *gtlbe,
	पूर्णांक tsize, काष्ठा tlbe_ref *ref, u64 gvaddr,
	काष्ठा kvm_book3e_206_tlb_entry *stlbe)
अणु
	kvm_pfn_t pfn = ref->pfn;
	u32 pr = vcpu->arch.shared->msr & MSR_PR;

	BUG_ON(!(ref->flags & E500_TLB_VALID));

	/* Force IPROT=0 क्रम all guest mappings. */
	stlbe->mas1 = MAS1_TSIZE(tsize) | get_tlb_sts(gtlbe) | MAS1_VALID;
	stlbe->mas2 = (gvaddr & MAS2_EPN) | (ref->flags & E500_TLB_MAS2_ATTR);
	stlbe->mas7_3 = ((u64)pfn << PAGE_SHIFT) |
			e500_shaकरोw_mas3_attrib(gtlbe->mas7_3, pr);
पूर्ण

अटल अंतरभूत पूर्णांक kvmppc_e500_shaकरोw_map(काष्ठा kvmppc_vcpu_e500 *vcpu_e500,
	u64 gvaddr, gfn_t gfn, काष्ठा kvm_book3e_206_tlb_entry *gtlbe,
	पूर्णांक tlbsel, काष्ठा kvm_book3e_206_tlb_entry *stlbe,
	काष्ठा tlbe_ref *ref)
अणु
	काष्ठा kvm_memory_slot *slot;
	अचिन्हित दीर्घ pfn = 0; /* silence GCC warning */
	अचिन्हित दीर्घ hva;
	पूर्णांक pfnmap = 0;
	पूर्णांक tsize = BOOK3E_PAGESZ_4K;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ mmu_seq;
	काष्ठा kvm *kvm = vcpu_e500->vcpu.kvm;
	अचिन्हित दीर्घ tsize_pages = 0;
	pte_t *ptep;
	अचिन्हित पूर्णांक wimg = 0;
	pgd_t *pgdir;
	अचिन्हित दीर्घ flags;

	/* used to check क्रम invalidations in progress */
	mmu_seq = kvm->mmu_notअगरier_seq;
	smp_rmb();

	/*
	 * Translate guest physical to true physical, acquiring
	 * a page reference अगर it is normal, non-reserved memory.
	 *
	 * gfn_to_memslot() must succeed because otherwise we wouldn't
	 * have gotten this far.  Eventually we should just pass the slot
	 * poपूर्णांकer through from the first lookup.
	 */
	slot = gfn_to_memslot(vcpu_e500->vcpu.kvm, gfn);
	hva = gfn_to_hva_memslot(slot, gfn);

	अगर (tlbsel == 1) अणु
		काष्ठा vm_area_काष्ठा *vma;
		mmap_पढ़ो_lock(kvm->mm);

		vma = find_vma(kvm->mm, hva);
		अगर (vma && hva >= vma->vm_start &&
		    (vma->vm_flags & VM_PFNMAP)) अणु
			/*
			 * This VMA is a physically contiguous region (e.g.
			 * /dev/mem) that bypasses normal Linux page
			 * management.  Find the overlap between the
			 * vma and the memslot.
			 */

			अचिन्हित दीर्घ start, end;
			अचिन्हित दीर्घ slot_start, slot_end;

			pfnmap = 1;

			start = vma->vm_pgoff;
			end = start +
			      vma_pages(vma);

			pfn = start + ((hva - vma->vm_start) >> PAGE_SHIFT);

			slot_start = pfn - (gfn - slot->base_gfn);
			slot_end = slot_start + slot->npages;

			अगर (start < slot_start)
				start = slot_start;
			अगर (end > slot_end)
				end = slot_end;

			tsize = (gtlbe->mas1 & MAS1_TSIZE_MASK) >>
				MAS1_TSIZE_SHIFT;

			/*
			 * e500 करोesn't implement the lowest tsize bit,
			 * or 1K pages.
			 */
			tsize = max(BOOK3E_PAGESZ_4K, tsize & ~1);

			/*
			 * Now find the largest tsize (up to what the guest
			 * requested) that will cover gfn, stay within the
			 * range, and क्रम which gfn and pfn are mutually
			 * aligned.
			 */

			क्रम (; tsize > BOOK3E_PAGESZ_4K; tsize -= 2) अणु
				अचिन्हित दीर्घ gfn_start, gfn_end;
				tsize_pages = 1UL << (tsize - 2);

				gfn_start = gfn & ~(tsize_pages - 1);
				gfn_end = gfn_start + tsize_pages;

				अगर (gfn_start + pfn - gfn < start)
					जारी;
				अगर (gfn_end + pfn - gfn > end)
					जारी;
				अगर ((gfn & (tsize_pages - 1)) !=
				    (pfn & (tsize_pages - 1)))
					जारी;

				gvaddr &= ~((tsize_pages << PAGE_SHIFT) - 1);
				pfn &= ~(tsize_pages - 1);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (vma && hva >= vma->vm_start &&
			   is_vm_hugetlb_page(vma)) अणु
			अचिन्हित दीर्घ psize = vma_kernel_pagesize(vma);

			tsize = (gtlbe->mas1 & MAS1_TSIZE_MASK) >>
				MAS1_TSIZE_SHIFT;

			/*
			 * Take the largest page size that satisfies both host
			 * and guest mapping
			 */
			tsize = min(__ilog2(psize) - 10, tsize);

			/*
			 * e500 करोesn't implement the lowest tsize bit,
			 * or 1K pages.
			 */
			tsize = max(BOOK3E_PAGESZ_4K, tsize & ~1);
		पूर्ण

		mmap_पढ़ो_unlock(kvm->mm);
	पूर्ण

	अगर (likely(!pfnmap)) अणु
		tsize_pages = 1UL << (tsize + 10 - PAGE_SHIFT);
		pfn = gfn_to_pfn_memslot(slot, gfn);
		अगर (is_error_noslot_pfn(pfn)) अणु
			अगर (prपूर्णांकk_ratelimit())
				pr_err("%s: real page not found for gfn %lx\n",
				       __func__, (दीर्घ)gfn);
			वापस -EINVAL;
		पूर्ण

		/* Align guest and physical address to page map boundaries */
		pfn &= ~(tsize_pages - 1);
		gvaddr &= ~((tsize_pages << PAGE_SHIFT) - 1);
	पूर्ण

	spin_lock(&kvm->mmu_lock);
	अगर (mmu_notअगरier_retry(kvm, mmu_seq)) अणु
		ret = -EAGAIN;
		जाओ out;
	पूर्ण


	pgdir = vcpu_e500->vcpu.arch.pgdir;
	/*
	 * We are just looking at the wimg bits, so we करोn't
	 * care much about the trans splitting bit.
	 * We are holding kvm->mmu_lock so a notअगरier invalidate
	 * can't run hence pfn won't change.
	 */
	local_irq_save(flags);
	ptep = find_linux_pte(pgdir, hva, शून्य, शून्य);
	अगर (ptep) अणु
		pte_t pte = READ_ONCE(*ptep);

		अगर (pte_present(pte)) अणु
			wimg = (pte_val(pte) >> PTE_WIMGE_SHIFT) &
				MAS2_WIMGE_MASK;
			local_irq_restore(flags);
		पूर्ण अन्यथा अणु
			local_irq_restore(flags);
			pr_err_ratelimited("%s: pte not present: gfn %lx,pfn %lx\n",
					   __func__, (दीर्घ)gfn, pfn);
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण
	kvmppc_e500_ref_setup(ref, gtlbe, pfn, wimg);

	kvmppc_e500_setup_stlbe(&vcpu_e500->vcpu, gtlbe, tsize,
				ref, gvaddr, stlbe);

	/* Clear i-cache क्रम new pages */
	kvmppc_mmu_flush_icache(pfn);

out:
	spin_unlock(&kvm->mmu_lock);

	/* Drop refcount on page, so that mmu notअगरiers can clear it */
	kvm_release_pfn_clean(pfn);

	वापस ret;
पूर्ण

/* XXX only map the one-one हाल, क्रम now use TLB0 */
अटल पूर्णांक kvmppc_e500_tlb0_map(काष्ठा kvmppc_vcpu_e500 *vcpu_e500, पूर्णांक esel,
				काष्ठा kvm_book3e_206_tlb_entry *stlbe)
अणु
	काष्ठा kvm_book3e_206_tlb_entry *gtlbe;
	काष्ठा tlbe_ref *ref;
	पूर्णांक stlbsel = 0;
	पूर्णांक sesel = 0;
	पूर्णांक r;

	gtlbe = get_entry(vcpu_e500, 0, esel);
	ref = &vcpu_e500->gtlb_priv[0][esel].ref;

	r = kvmppc_e500_shaकरोw_map(vcpu_e500, get_tlb_eaddr(gtlbe),
			get_tlb_raddr(gtlbe) >> PAGE_SHIFT,
			gtlbe, 0, stlbe, ref);
	अगर (r)
		वापस r;

	ग_लिखो_stlbe(vcpu_e500, gtlbe, stlbe, stlbsel, sesel);

	वापस 0;
पूर्ण

अटल पूर्णांक kvmppc_e500_tlb1_map_tlb1(काष्ठा kvmppc_vcpu_e500 *vcpu_e500,
				     काष्ठा tlbe_ref *ref,
				     पूर्णांक esel)
अणु
	अचिन्हित पूर्णांक sesel = vcpu_e500->host_tlb1_nv++;

	अगर (unlikely(vcpu_e500->host_tlb1_nv >= tlb1_max_shaकरोw_size()))
		vcpu_e500->host_tlb1_nv = 0;

	अगर (vcpu_e500->h2g_tlb1_rmap[sesel]) अणु
		अचिन्हित पूर्णांक idx = vcpu_e500->h2g_tlb1_rmap[sesel] - 1;
		vcpu_e500->g2h_tlb1_map[idx] &= ~(1ULL << sesel);
	पूर्ण

	vcpu_e500->gtlb_priv[1][esel].ref.flags |= E500_TLB_BITMAP;
	vcpu_e500->g2h_tlb1_map[esel] |= (u64)1 << sesel;
	vcpu_e500->h2g_tlb1_rmap[sesel] = esel + 1;
	WARN_ON(!(ref->flags & E500_TLB_VALID));

	वापस sesel;
पूर्ण

/* Caller must ensure that the specअगरied guest TLB entry is safe to insert पूर्णांकo
 * the shaकरोw TLB. */
/* For both one-one and one-to-many */
अटल पूर्णांक kvmppc_e500_tlb1_map(काष्ठा kvmppc_vcpu_e500 *vcpu_e500,
		u64 gvaddr, gfn_t gfn, काष्ठा kvm_book3e_206_tlb_entry *gtlbe,
		काष्ठा kvm_book3e_206_tlb_entry *stlbe, पूर्णांक esel)
अणु
	काष्ठा tlbe_ref *ref = &vcpu_e500->gtlb_priv[1][esel].ref;
	पूर्णांक sesel;
	पूर्णांक r;

	r = kvmppc_e500_shaकरोw_map(vcpu_e500, gvaddr, gfn, gtlbe, 1, stlbe,
				   ref);
	अगर (r)
		वापस r;

	/* Use TLB0 when we can only map a page with 4k */
	अगर (get_tlb_tsize(stlbe) == BOOK3E_PAGESZ_4K) अणु
		vcpu_e500->gtlb_priv[1][esel].ref.flags |= E500_TLB_TLB0;
		ग_लिखो_stlbe(vcpu_e500, gtlbe, stlbe, 0, 0);
		वापस 0;
	पूर्ण

	/* Otherwise map पूर्णांकo TLB1 */
	sesel = kvmppc_e500_tlb1_map_tlb1(vcpu_e500, ref, esel);
	ग_लिखो_stlbe(vcpu_e500, gtlbe, stlbe, 1, sesel);

	वापस 0;
पूर्ण

व्योम kvmppc_mmu_map(काष्ठा kvm_vcpu *vcpu, u64 eaddr, gpa_t gpaddr,
		    अचिन्हित पूर्णांक index)
अणु
	काष्ठा kvmppc_vcpu_e500 *vcpu_e500 = to_e500(vcpu);
	काष्ठा tlbe_priv *priv;
	काष्ठा kvm_book3e_206_tlb_entry *gtlbe, stlbe;
	पूर्णांक tlbsel = tlbsel_of(index);
	पूर्णांक esel = esel_of(index);

	gtlbe = get_entry(vcpu_e500, tlbsel, esel);

	चयन (tlbsel) अणु
	हाल 0:
		priv = &vcpu_e500->gtlb_priv[tlbsel][esel];

		/* Triggers after clear_tlb_privs or on initial mapping */
		अगर (!(priv->ref.flags & E500_TLB_VALID)) अणु
			kvmppc_e500_tlb0_map(vcpu_e500, esel, &stlbe);
		पूर्ण अन्यथा अणु
			kvmppc_e500_setup_stlbe(vcpu, gtlbe, BOOK3E_PAGESZ_4K,
						&priv->ref, eaddr, &stlbe);
			ग_लिखो_stlbe(vcpu_e500, gtlbe, &stlbe, 0, 0);
		पूर्ण
		अवरोध;

	हाल 1: अणु
		gfn_t gfn = gpaddr >> PAGE_SHIFT;
		kvmppc_e500_tlb1_map(vcpu_e500, eaddr, gfn, gtlbe, &stlbe,
				     esel);
		अवरोध;
	पूर्ण

	शेष:
		BUG();
		अवरोध;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_KVM_BOOKE_HV
पूर्णांक kvmppc_load_last_inst(काष्ठा kvm_vcpu *vcpu,
		क्रमागत inकाष्ठाion_fetch_type type, u32 *instr)
अणु
	gva_t geaddr;
	hpa_t addr;
	hfn_t pfn;
	hva_t eaddr;
	u32 mas1, mas2, mas3;
	u64 mas7_mas3;
	काष्ठा page *page;
	अचिन्हित पूर्णांक addr_space, psize_shअगरt;
	bool pr;
	अचिन्हित दीर्घ flags;

	/* Search TLB क्रम guest pc to get the real address */
	geaddr = kvmppc_get_pc(vcpu);

	addr_space = (vcpu->arch.shared->msr & MSR_IS) >> MSR_IR_LG;

	local_irq_save(flags);
	mtspr(SPRN_MAS6, (vcpu->arch.pid << MAS6_SPID_SHIFT) | addr_space);
	mtspr(SPRN_MAS5, MAS5_SGS | get_lpid(vcpu));
	यंत्र अस्थिर("tlbsx 0, %[geaddr]\n" : :
		     [geaddr] "r" (geaddr));
	mtspr(SPRN_MAS5, 0);
	mtspr(SPRN_MAS8, 0);
	mas1 = mfspr(SPRN_MAS1);
	mas2 = mfspr(SPRN_MAS2);
	mas3 = mfspr(SPRN_MAS3);
#अगर_घोषित CONFIG_64BIT
	mas7_mas3 = mfspr(SPRN_MAS7_MAS3);
#अन्यथा
	mas7_mas3 = ((u64)mfspr(SPRN_MAS7) << 32) | mas3;
#पूर्ण_अगर
	local_irq_restore(flags);

	/*
	 * If the TLB entry क्रम guest pc was evicted, वापस to the guest.
	 * There are high chances to find a valid TLB entry next समय.
	 */
	अगर (!(mas1 & MAS1_VALID))
		वापस EMULATE_AGAIN;

	/*
	 * Another thपढ़ो may reग_लिखो the TLB entry in parallel, करोn't
	 * execute from the address अगर the execute permission is not set
	 */
	pr = vcpu->arch.shared->msr & MSR_PR;
	अगर (unlikely((pr && !(mas3 & MAS3_UX)) ||
		     (!pr && !(mas3 & MAS3_SX)))) अणु
		pr_err_ratelimited(
			"%s: Instruction emulation from guest address %08lx without execute permission\n",
			__func__, geaddr);
		वापस EMULATE_AGAIN;
	पूर्ण

	/*
	 * The real address will be mapped by a cacheable, memory coherent,
	 * ग_लिखो-back page. Check क्रम mismatches when LRAT is used.
	 */
	अगर (has_feature(vcpu, VCPU_FTR_MMU_V2) &&
	    unlikely((mas2 & MAS2_I) || (mas2 & MAS2_W) || !(mas2 & MAS2_M))) अणु
		pr_err_ratelimited(
			"%s: Instruction emulation from guest address %08lx mismatches storage attributes\n",
			__func__, geaddr);
		वापस EMULATE_AGAIN;
	पूर्ण

	/* Get pfn */
	psize_shअगरt = MAS1_GET_TSIZE(mas1) + 10;
	addr = (mas7_mas3 & (~0ULL << psize_shअगरt)) |
	       (geaddr & ((1ULL << psize_shअगरt) - 1ULL));
	pfn = addr >> PAGE_SHIFT;

	/* Guard against emulation from devices area */
	अगर (unlikely(!page_is_ram(pfn))) अणु
		pr_err_ratelimited("%s: Instruction emulation from non-RAM host address %08llx is not supported\n",
			 __func__, addr);
		वापस EMULATE_AGAIN;
	पूर्ण

	/* Map a page and get guest's inकाष्ठाion */
	page = pfn_to_page(pfn);
	eaddr = (अचिन्हित दीर्घ)kmap_atomic(page);
	*instr = *(u32 *)(eaddr | (अचिन्हित दीर्घ)(addr & ~PAGE_MASK));
	kunmap_atomic((u32 *)eaddr);

	वापस EMULATE_DONE;
पूर्ण
#अन्यथा
पूर्णांक kvmppc_load_last_inst(काष्ठा kvm_vcpu *vcpu,
		क्रमागत inकाष्ठाion_fetch_type type, u32 *instr)
अणु
	वापस EMULATE_AGAIN;
पूर्ण
#पूर्ण_अगर

/************* MMU Notअगरiers *************/

अटल bool kvm_e500_mmu_unmap_gfn(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	/*
	 * Flush all shaकरोw tlb entries everywhere. This is slow, but
	 * we are 100% sure that we catch the to be unmapped page
	 */
	वापस true;
पूर्ण

bool kvm_unmap_gfn_range(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	वापस kvm_e500_mmu_unmap_gfn(kvm, range);
पूर्ण

bool kvm_age_gfn(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	/* XXX could be more clever ;) */
	वापस false;
पूर्ण

bool kvm_test_age_gfn(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	/* XXX could be more clever ;) */
	वापस false;
पूर्ण

bool kvm_set_spte_gfn(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	/* The page will get remapped properly on its next fault */
	वापस kvm_e500_mmu_unmap_gfn(kvm, range);
पूर्ण

/*****************************************/

पूर्णांक e500_mmu_host_init(काष्ठा kvmppc_vcpu_e500 *vcpu_e500)
अणु
	host_tlb_params[0].entries = mfspr(SPRN_TLB0CFG) & TLBnCFG_N_ENTRY;
	host_tlb_params[1].entries = mfspr(SPRN_TLB1CFG) & TLBnCFG_N_ENTRY;

	/*
	 * This should never happen on real e500 hardware, but is
	 * architecturally possible -- e.g. in some weird nested
	 * भवization हाल.
	 */
	अगर (host_tlb_params[0].entries == 0 ||
	    host_tlb_params[1].entries == 0) अणु
		pr_err("%s: need to know host tlb size\n", __func__);
		वापस -ENODEV;
	पूर्ण

	host_tlb_params[0].ways = (mfspr(SPRN_TLB0CFG) & TLBnCFG_ASSOC) >>
				  TLBnCFG_ASSOC_SHIFT;
	host_tlb_params[1].ways = host_tlb_params[1].entries;

	अगर (!is_घातer_of_2(host_tlb_params[0].entries) ||
	    !is_घातer_of_2(host_tlb_params[0].ways) ||
	    host_tlb_params[0].entries < host_tlb_params[0].ways ||
	    host_tlb_params[0].ways == 0) अणु
		pr_err("%s: bad tlb0 host config: %u entries %u ways\n",
		       __func__, host_tlb_params[0].entries,
		       host_tlb_params[0].ways);
		वापस -ENODEV;
	पूर्ण

	host_tlb_params[0].sets =
		host_tlb_params[0].entries / host_tlb_params[0].ways;
	host_tlb_params[1].sets = 1;
	vcpu_e500->h2g_tlb1_rmap = kसुस्मृति(host_tlb_params[1].entries,
					   माप(*vcpu_e500->h2g_tlb1_rmap),
					   GFP_KERNEL);
	अगर (!vcpu_e500->h2g_tlb1_rmap)
		वापस -EINVAL;

	वापस 0;
पूर्ण

व्योम e500_mmu_host_uninit(काष्ठा kvmppc_vcpu_e500 *vcpu_e500)
अणु
	kमुक्त(vcpu_e500->h2g_tlb1_rmap);
पूर्ण
