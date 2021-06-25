<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright 2016 Paul Mackerras, IBM Corp. <paulus@au1.ibm.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/anon_inodes.h>
#समावेश <linux/file.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/pte-walk.h>
#समावेश <यंत्र/ultravisor.h>
#समावेश <यंत्र/kvm_book3s_uvस्मृति.स>

/*
 * Supported radix tree geometry.
 * Like p9, we support either 5 or 9 bits at the first (lowest) level,
 * क्रम a page size of 64k or 4k.
 */
अटल पूर्णांक p9_supported_radix_bits[4] = अणु 5, 9, 9, 13 पूर्ण;

अचिन्हित दीर्घ __kvmhv_copy_tofrom_guest_radix(पूर्णांक lpid, पूर्णांक pid,
					      gva_t eaddr, व्योम *to, व्योम *from,
					      अचिन्हित दीर्घ n)
अणु
	पूर्णांक old_pid, old_lpid;
	अचिन्हित दीर्घ quadrant, ret = n;
	bool is_load = !!to;

	/* Can't access quadrants 1 or 2 in non-HV mode, call the HV to करो it */
	अगर (kvmhv_on_pseries())
		वापस plpar_hcall_norets(H_COPY_TOFROM_GUEST, lpid, pid, eaddr,
					  (to != शून्य) ? __pa(to): 0,
					  (from != शून्य) ? __pa(from): 0, n);

	quadrant = 1;
	अगर (!pid)
		quadrant = 2;
	अगर (is_load)
		from = (व्योम *) (eaddr | (quadrant << 62));
	अन्यथा
		to = (व्योम *) (eaddr | (quadrant << 62));

	preempt_disable();

	/* चयन the lpid first to aव्योम running host with unallocated pid */
	old_lpid = mfspr(SPRN_LPID);
	अगर (old_lpid != lpid)
		mtspr(SPRN_LPID, lpid);
	अगर (quadrant == 1) अणु
		old_pid = mfspr(SPRN_PID);
		अगर (old_pid != pid)
			mtspr(SPRN_PID, pid);
	पूर्ण
	isync();

	अगर (is_load)
		ret = copy_from_user_nofault(to, (स्थिर व्योम __user *)from, n);
	अन्यथा
		ret = copy_to_user_nofault((व्योम __user *)to, from, n);

	/* चयन the pid first to aव्योम running host with unallocated pid */
	अगर (quadrant == 1 && pid != old_pid)
		mtspr(SPRN_PID, old_pid);
	अगर (lpid != old_lpid)
		mtspr(SPRN_LPID, old_lpid);
	isync();

	preempt_enable();

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__kvmhv_copy_tofrom_guest_radix);

अटल दीर्घ kvmhv_copy_tofrom_guest_radix(काष्ठा kvm_vcpu *vcpu, gva_t eaddr,
					  व्योम *to, व्योम *from, अचिन्हित दीर्घ n)
अणु
	पूर्णांक lpid = vcpu->kvm->arch.lpid;
	पूर्णांक pid = vcpu->arch.pid;

	/* This would cause a data segment पूर्णांकr so करोn't allow the access */
	अगर (eaddr & (0x3FFUL << 52))
		वापस -EINVAL;

	/* Should we be using the nested lpid */
	अगर (vcpu->arch.nested)
		lpid = vcpu->arch.nested->shaकरोw_lpid;

	/* If accessing quadrant 3 then pid is expected to be 0 */
	अगर (((eaddr >> 62) & 0x3) == 0x3)
		pid = 0;

	eaddr &= ~(0xFFFUL << 52);

	वापस __kvmhv_copy_tofrom_guest_radix(lpid, pid, eaddr, to, from, n);
पूर्ण

दीर्घ kvmhv_copy_from_guest_radix(काष्ठा kvm_vcpu *vcpu, gva_t eaddr, व्योम *to,
				 अचिन्हित दीर्घ n)
अणु
	दीर्घ ret;

	ret = kvmhv_copy_tofrom_guest_radix(vcpu, eaddr, to, शून्य, n);
	अगर (ret > 0)
		स_रखो(to + (n - ret), 0, ret);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(kvmhv_copy_from_guest_radix);

दीर्घ kvmhv_copy_to_guest_radix(काष्ठा kvm_vcpu *vcpu, gva_t eaddr, व्योम *from,
			       अचिन्हित दीर्घ n)
अणु
	वापस kvmhv_copy_tofrom_guest_radix(vcpu, eaddr, शून्य, from, n);
पूर्ण
EXPORT_SYMBOL_GPL(kvmhv_copy_to_guest_radix);

पूर्णांक kvmppc_mmu_walk_radix_tree(काष्ठा kvm_vcpu *vcpu, gva_t eaddr,
			       काष्ठा kvmppc_pte *gpte, u64 root,
			       u64 *pte_ret_p)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	पूर्णांक ret, level, ps;
	अचिन्हित दीर्घ rts, bits, offset, index;
	u64 pte, base, gpa;
	__be64 rpte;

	rts = ((root & RTS1_MASK) >> (RTS1_SHIFT - 3)) |
		((root & RTS2_MASK) >> RTS2_SHIFT);
	bits = root & RPDS_MASK;
	base = root & RPDB_MASK;

	offset = rts + 31;

	/* Current implementations only support 52-bit space */
	अगर (offset != 52)
		वापस -EINVAL;

	/* Walk each level of the radix tree */
	क्रम (level = 3; level >= 0; --level) अणु
		u64 addr;
		/* Check a valid size */
		अगर (level && bits != p9_supported_radix_bits[level])
			वापस -EINVAL;
		अगर (level == 0 && !(bits == 5 || bits == 9))
			वापस -EINVAL;
		offset -= bits;
		index = (eaddr >> offset) & ((1UL << bits) - 1);
		/* Check that low bits of page table base are zero */
		अगर (base & ((1UL << (bits + 3)) - 1))
			वापस -EINVAL;
		/* Read the entry from guest memory */
		addr = base + (index * माप(rpte));
		vcpu->srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
		ret = kvm_पढ़ो_guest(kvm, addr, &rpte, माप(rpte));
		srcu_पढ़ो_unlock(&kvm->srcu, vcpu->srcu_idx);
		अगर (ret) अणु
			अगर (pte_ret_p)
				*pte_ret_p = addr;
			वापस ret;
		पूर्ण
		pte = __be64_to_cpu(rpte);
		अगर (!(pte & _PAGE_PRESENT))
			वापस -ENOENT;
		/* Check अगर a leaf entry */
		अगर (pte & _PAGE_PTE)
			अवरोध;
		/* Get पढ़ोy to walk the next level */
		base = pte & RPDB_MASK;
		bits = pte & RPDS_MASK;
	पूर्ण

	/* Need a leaf at lowest level; 512GB pages not supported */
	अगर (level < 0 || level == 3)
		वापस -EINVAL;

	/* We found a valid leaf PTE */
	/* Offset is now log base 2 of the page size */
	gpa = pte & 0x01fffffffffff000ul;
	अगर (gpa & ((1ul << offset) - 1))
		वापस -EINVAL;
	gpa |= eaddr & ((1ul << offset) - 1);
	क्रम (ps = MMU_PAGE_4K; ps < MMU_PAGE_COUNT; ++ps)
		अगर (offset == mmu_psize_defs[ps].shअगरt)
			अवरोध;
	gpte->page_size = ps;
	gpte->page_shअगरt = offset;

	gpte->eaddr = eaddr;
	gpte->raddr = gpa;

	/* Work out permissions */
	gpte->may_पढ़ो = !!(pte & _PAGE_READ);
	gpte->may_ग_लिखो = !!(pte & _PAGE_WRITE);
	gpte->may_execute = !!(pte & _PAGE_EXEC);

	gpte->rc = pte & (_PAGE_ACCESSED | _PAGE_सूचीTY);

	अगर (pte_ret_p)
		*pte_ret_p = pte;

	वापस 0;
पूर्ण

/*
 * Used to walk a partition or process table radix tree in guest memory
 * Note: We exploit the fact that a partition table and a process
 * table have the same layout, a partition-scoped page table and a
 * process-scoped page table have the same layout, and the 2nd
 * द्विगुनword of a partition table entry has the same layout as
 * the PTCR रेजिस्टर.
 */
पूर्णांक kvmppc_mmu_radix_translate_table(काष्ठा kvm_vcpu *vcpu, gva_t eaddr,
				     काष्ठा kvmppc_pte *gpte, u64 table,
				     पूर्णांक table_index, u64 *pte_ret_p)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	पूर्णांक ret;
	अचिन्हित दीर्घ size, ptbl, root;
	काष्ठा prtb_entry entry;

	अगर ((table & PRTS_MASK) > 24)
		वापस -EINVAL;
	size = 1ul << ((table & PRTS_MASK) + 12);

	/* Is the table big enough to contain this entry? */
	अगर ((table_index * माप(entry)) >= size)
		वापस -EINVAL;

	/* Read the table to find the root of the radix tree */
	ptbl = (table & PRTB_MASK) + (table_index * माप(entry));
	vcpu->srcu_idx = srcu_पढ़ो_lock(&kvm->srcu);
	ret = kvm_पढ़ो_guest(kvm, ptbl, &entry, माप(entry));
	srcu_पढ़ो_unlock(&kvm->srcu, vcpu->srcu_idx);
	अगर (ret)
		वापस ret;

	/* Root is stored in the first द्विगुन word */
	root = be64_to_cpu(entry.prtb0);

	वापस kvmppc_mmu_walk_radix_tree(vcpu, eaddr, gpte, root, pte_ret_p);
पूर्ण

पूर्णांक kvmppc_mmu_radix_xlate(काष्ठा kvm_vcpu *vcpu, gva_t eaddr,
			   काष्ठा kvmppc_pte *gpte, bool data, bool isग_लिखो)
अणु
	u32 pid;
	u64 pte;
	पूर्णांक ret;

	/* Work out effective PID */
	चयन (eaddr >> 62) अणु
	हाल 0:
		pid = vcpu->arch.pid;
		अवरोध;
	हाल 3:
		pid = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = kvmppc_mmu_radix_translate_table(vcpu, eaddr, gpte,
				vcpu->kvm->arch.process_table, pid, &pte);
	अगर (ret)
		वापस ret;

	/* Check privilege (applies only to process scoped translations) */
	अगर (kvmppc_get_msr(vcpu) & MSR_PR) अणु
		अगर (pte & _PAGE_PRIVILEGED) अणु
			gpte->may_पढ़ो = 0;
			gpte->may_ग_लिखो = 0;
			gpte->may_execute = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!(pte & _PAGE_PRIVILEGED)) अणु
			/* Check AMR/IAMR to see अगर strict mode is in क्रमce */
			अगर (vcpu->arch.amr & (1ul << 62))
				gpte->may_पढ़ो = 0;
			अगर (vcpu->arch.amr & (1ul << 63))
				gpte->may_ग_लिखो = 0;
			अगर (vcpu->arch.iamr & (1ul << 62))
				gpte->may_execute = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम kvmppc_radix_tlbie_page(काष्ठा kvm *kvm, अचिन्हित दीर्घ addr,
			     अचिन्हित पूर्णांक pshअगरt, अचिन्हित पूर्णांक lpid)
अणु
	अचिन्हित दीर्घ psize = PAGE_SIZE;
	पूर्णांक psi;
	दीर्घ rc;
	अचिन्हित दीर्घ rb;

	अगर (pshअगरt)
		psize = 1UL << pshअगरt;
	अन्यथा
		pshअगरt = PAGE_SHIFT;

	addr &= ~(psize - 1);

	अगर (!kvmhv_on_pseries()) अणु
		radix__flush_tlb_lpid_page(lpid, addr, psize);
		वापस;
	पूर्ण

	psi = shअगरt_to_mmu_psize(pshअगरt);
	rb = addr | (mmu_get_ap(psi) << PPC_BITLSHIFT(58));
	rc = plpar_hcall_norets(H_TLB_INVALIDATE, H_TLBIE_P1_ENC(0, 0, 1),
				lpid, rb);
	अगर (rc)
		pr_err("KVM: TLB page invalidation hcall failed, rc=%ld\n", rc);
पूर्ण

अटल व्योम kvmppc_radix_flush_pwc(काष्ठा kvm *kvm, अचिन्हित पूर्णांक lpid)
अणु
	दीर्घ rc;

	अगर (!kvmhv_on_pseries()) अणु
		radix__flush_pwc_lpid(lpid);
		वापस;
	पूर्ण

	rc = plpar_hcall_norets(H_TLB_INVALIDATE, H_TLBIE_P1_ENC(1, 0, 1),
				lpid, TLBIEL_INVAL_SET_LPID);
	अगर (rc)
		pr_err("KVM: TLB PWC invalidation hcall failed, rc=%ld\n", rc);
पूर्ण

अटल अचिन्हित दीर्घ kvmppc_radix_update_pte(काष्ठा kvm *kvm, pte_t *ptep,
				      अचिन्हित दीर्घ clr, अचिन्हित दीर्घ set,
				      अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक shअगरt)
अणु
	वापस __radix_pte_update(ptep, clr, set);
पूर्ण

अटल व्योम kvmppc_radix_set_pte_at(काष्ठा kvm *kvm, अचिन्हित दीर्घ addr,
			     pte_t *ptep, pte_t pte)
अणु
	radix__set_pte_at(kvm->mm, addr, ptep, pte, 0);
पूर्ण

अटल काष्ठा kmem_cache *kvm_pte_cache;
अटल काष्ठा kmem_cache *kvm_pmd_cache;

अटल pte_t *kvmppc_pte_alloc(व्योम)
अणु
	pte_t *pte;

	pte = kmem_cache_alloc(kvm_pte_cache, GFP_KERNEL);
	/* pmd_populate() will only reference _pa(pte). */
	kmemleak_ignore(pte);

	वापस pte;
पूर्ण

अटल व्योम kvmppc_pte_मुक्त(pte_t *ptep)
अणु
	kmem_cache_मुक्त(kvm_pte_cache, ptep);
पूर्ण

अटल pmd_t *kvmppc_pmd_alloc(व्योम)
अणु
	pmd_t *pmd;

	pmd = kmem_cache_alloc(kvm_pmd_cache, GFP_KERNEL);
	/* pud_populate() will only reference _pa(pmd). */
	kmemleak_ignore(pmd);

	वापस pmd;
पूर्ण

अटल व्योम kvmppc_pmd_मुक्त(pmd_t *pmdp)
अणु
	kmem_cache_मुक्त(kvm_pmd_cache, pmdp);
पूर्ण

/* Called with kvm->mmu_lock held */
व्योम kvmppc_unmap_pte(काष्ठा kvm *kvm, pte_t *pte, अचिन्हित दीर्घ gpa,
		      अचिन्हित पूर्णांक shअगरt,
		      स्थिर काष्ठा kvm_memory_slot *memslot,
		      अचिन्हित पूर्णांक lpid)

अणु
	अचिन्हित दीर्घ old;
	अचिन्हित दीर्घ gfn = gpa >> PAGE_SHIFT;
	अचिन्हित दीर्घ page_size = PAGE_SIZE;
	अचिन्हित दीर्घ hpa;

	old = kvmppc_radix_update_pte(kvm, pte, ~0UL, 0, gpa, shअगरt);
	kvmppc_radix_tlbie_page(kvm, gpa, shअगरt, lpid);

	/* The following only applies to L1 entries */
	अगर (lpid != kvm->arch.lpid)
		वापस;

	अगर (!memslot) अणु
		memslot = gfn_to_memslot(kvm, gfn);
		अगर (!memslot)
			वापस;
	पूर्ण
	अगर (shअगरt) अणु /* 1GB or 2MB page */
		page_size = 1ul << shअगरt;
		अगर (shअगरt == PMD_SHIFT)
			kvm->stat.num_2M_pages--;
		अन्यथा अगर (shअगरt == PUD_SHIFT)
			kvm->stat.num_1G_pages--;
	पूर्ण

	gpa &= ~(page_size - 1);
	hpa = old & PTE_RPN_MASK;
	kvmhv_हटाओ_nest_rmap_range(kvm, memslot, gpa, hpa, page_size);

	अगर ((old & _PAGE_सूचीTY) && memslot->dirty_biपंचांगap)
		kvmppc_update_dirty_map(memslot, gfn, page_size);
पूर्ण

/*
 * kvmppc_मुक्त_p?d are used to मुक्त existing page tables, and recursively
 * descend and clear and मुक्त children.
 * Callers are responsible क्रम flushing the PWC.
 *
 * When page tables are being unmapped/मुक्तd as part of page fault path
 * (full == false), valid ptes are generally not expected; however, there
 * is one situation where they arise, which is when dirty page logging is
 * turned off क्रम a memslot जबतक the VM is running.  The new memslot
 * becomes visible to page faults beक्रमe the memslot commit function
 * माला_लो to flush the memslot, which can lead to a 2MB page mapping being
 * installed क्रम a guest physical address where there are alपढ़ोy 64kB
 * (or 4kB) mappings (of sub-pages of the same 2MB page).
 */
अटल व्योम kvmppc_unmap_मुक्त_pte(काष्ठा kvm *kvm, pte_t *pte, bool full,
				  अचिन्हित पूर्णांक lpid)
अणु
	अगर (full) अणु
		स_रखो(pte, 0, माप(दीर्घ) << RADIX_PTE_INDEX_SIZE);
	पूर्ण अन्यथा अणु
		pte_t *p = pte;
		अचिन्हित दीर्घ it;

		क्रम (it = 0; it < PTRS_PER_PTE; ++it, ++p) अणु
			अगर (pte_val(*p) == 0)
				जारी;
			kvmppc_unmap_pte(kvm, p,
					 pte_pfn(*p) << PAGE_SHIFT,
					 PAGE_SHIFT, शून्य, lpid);
		पूर्ण
	पूर्ण

	kvmppc_pte_मुक्त(pte);
पूर्ण

अटल व्योम kvmppc_unmap_मुक्त_pmd(काष्ठा kvm *kvm, pmd_t *pmd, bool full,
				  अचिन्हित पूर्णांक lpid)
अणु
	अचिन्हित दीर्घ im;
	pmd_t *p = pmd;

	क्रम (im = 0; im < PTRS_PER_PMD; ++im, ++p) अणु
		अगर (!pmd_present(*p))
			जारी;
		अगर (pmd_is_leaf(*p)) अणु
			अगर (full) अणु
				pmd_clear(p);
			पूर्ण अन्यथा अणु
				WARN_ON_ONCE(1);
				kvmppc_unmap_pte(kvm, (pte_t *)p,
					 pte_pfn(*(pte_t *)p) << PAGE_SHIFT,
					 PMD_SHIFT, शून्य, lpid);
			पूर्ण
		पूर्ण अन्यथा अणु
			pte_t *pte;

			pte = pte_offset_map(p, 0);
			kvmppc_unmap_मुक्त_pte(kvm, pte, full, lpid);
			pmd_clear(p);
		पूर्ण
	पूर्ण
	kvmppc_pmd_मुक्त(pmd);
पूर्ण

अटल व्योम kvmppc_unmap_मुक्त_pud(काष्ठा kvm *kvm, pud_t *pud,
				  अचिन्हित पूर्णांक lpid)
अणु
	अचिन्हित दीर्घ iu;
	pud_t *p = pud;

	क्रम (iu = 0; iu < PTRS_PER_PUD; ++iu, ++p) अणु
		अगर (!pud_present(*p))
			जारी;
		अगर (pud_is_leaf(*p)) अणु
			pud_clear(p);
		पूर्ण अन्यथा अणु
			pmd_t *pmd;

			pmd = pmd_offset(p, 0);
			kvmppc_unmap_मुक्त_pmd(kvm, pmd, true, lpid);
			pud_clear(p);
		पूर्ण
	पूर्ण
	pud_मुक्त(kvm->mm, pud);
पूर्ण

व्योम kvmppc_मुक्त_pgtable_radix(काष्ठा kvm *kvm, pgd_t *pgd, अचिन्हित पूर्णांक lpid)
अणु
	अचिन्हित दीर्घ ig;

	क्रम (ig = 0; ig < PTRS_PER_PGD; ++ig, ++pgd) अणु
		p4d_t *p4d = p4d_offset(pgd, 0);
		pud_t *pud;

		अगर (!p4d_present(*p4d))
			जारी;
		pud = pud_offset(p4d, 0);
		kvmppc_unmap_मुक्त_pud(kvm, pud, lpid);
		p4d_clear(p4d);
	पूर्ण
पूर्ण

व्योम kvmppc_मुक्त_radix(काष्ठा kvm *kvm)
अणु
	अगर (kvm->arch.pgtable) अणु
		kvmppc_मुक्त_pgtable_radix(kvm, kvm->arch.pgtable,
					  kvm->arch.lpid);
		pgd_मुक्त(kvm->mm, kvm->arch.pgtable);
		kvm->arch.pgtable = शून्य;
	पूर्ण
पूर्ण

अटल व्योम kvmppc_unmap_मुक्त_pmd_entry_table(काष्ठा kvm *kvm, pmd_t *pmd,
					अचिन्हित दीर्घ gpa, अचिन्हित पूर्णांक lpid)
अणु
	pte_t *pte = pte_offset_kernel(pmd, 0);

	/*
	 * Clearing the pmd entry then flushing the PWC ensures that the pte
	 * page no दीर्घer be cached by the MMU, so can be मुक्तd without
	 * flushing the PWC again.
	 */
	pmd_clear(pmd);
	kvmppc_radix_flush_pwc(kvm, lpid);

	kvmppc_unmap_मुक्त_pte(kvm, pte, false, lpid);
पूर्ण

अटल व्योम kvmppc_unmap_मुक्त_pud_entry_table(काष्ठा kvm *kvm, pud_t *pud,
					अचिन्हित दीर्घ gpa, अचिन्हित पूर्णांक lpid)
अणु
	pmd_t *pmd = pmd_offset(pud, 0);

	/*
	 * Clearing the pud entry then flushing the PWC ensures that the pmd
	 * page and any children pte pages will no दीर्घer be cached by the MMU,
	 * so can be मुक्तd without flushing the PWC again.
	 */
	pud_clear(pud);
	kvmppc_radix_flush_pwc(kvm, lpid);

	kvmppc_unmap_मुक्त_pmd(kvm, pmd, false, lpid);
पूर्ण

/*
 * There are a number of bits which may dअगरfer between dअगरferent faults to
 * the same partition scope entry. RC bits, in the course of cleaning and
 * aging. And the ग_लिखो bit can change, either the access could have been
 * upgraded, or a पढ़ो fault could happen concurrently with a ग_लिखो fault
 * that sets those bits first.
 */
#घोषणा PTE_BITS_MUST_MATCH (~(_PAGE_WRITE | _PAGE_सूचीTY | _PAGE_ACCESSED))

पूर्णांक kvmppc_create_pte(काष्ठा kvm *kvm, pgd_t *pgtable, pte_t pte,
		      अचिन्हित दीर्घ gpa, अचिन्हित पूर्णांक level,
		      अचिन्हित दीर्घ mmu_seq, अचिन्हित पूर्णांक lpid,
		      अचिन्हित दीर्घ *rmapp, काष्ठा rmap_nested **n_rmap)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud, *new_pud = शून्य;
	pmd_t *pmd, *new_pmd = शून्य;
	pte_t *ptep, *new_ptep = शून्य;
	पूर्णांक ret;

	/* Traverse the guest's 2nd-level tree, allocate new levels needed */
	pgd = pgtable + pgd_index(gpa);
	p4d = p4d_offset(pgd, gpa);

	pud = शून्य;
	अगर (p4d_present(*p4d))
		pud = pud_offset(p4d, gpa);
	अन्यथा
		new_pud = pud_alloc_one(kvm->mm, gpa);

	pmd = शून्य;
	अगर (pud && pud_present(*pud) && !pud_is_leaf(*pud))
		pmd = pmd_offset(pud, gpa);
	अन्यथा अगर (level <= 1)
		new_pmd = kvmppc_pmd_alloc();

	अगर (level == 0 && !(pmd && pmd_present(*pmd) && !pmd_is_leaf(*pmd)))
		new_ptep = kvmppc_pte_alloc();

	/* Check अगर we might have been invalidated; let the guest retry अगर so */
	spin_lock(&kvm->mmu_lock);
	ret = -EAGAIN;
	अगर (mmu_notअगरier_retry(kvm, mmu_seq))
		जाओ out_unlock;

	/* Now traverse again under the lock and change the tree */
	ret = -ENOMEM;
	अगर (p4d_none(*p4d)) अणु
		अगर (!new_pud)
			जाओ out_unlock;
		p4d_populate(kvm->mm, p4d, new_pud);
		new_pud = शून्य;
	पूर्ण
	pud = pud_offset(p4d, gpa);
	अगर (pud_is_leaf(*pud)) अणु
		अचिन्हित दीर्घ hgpa = gpa & PUD_MASK;

		/* Check अगर we raced and someone अन्यथा has set the same thing */
		अगर (level == 2) अणु
			अगर (pud_raw(*pud) == pte_raw(pte)) अणु
				ret = 0;
				जाओ out_unlock;
			पूर्ण
			/* Valid 1GB page here alपढ़ोy, add our extra bits */
			WARN_ON_ONCE((pud_val(*pud) ^ pte_val(pte)) &
							PTE_BITS_MUST_MATCH);
			kvmppc_radix_update_pte(kvm, (pte_t *)pud,
					      0, pte_val(pte), hgpa, PUD_SHIFT);
			ret = 0;
			जाओ out_unlock;
		पूर्ण
		/*
		 * If we raced with another CPU which has just put
		 * a 1GB pte in after we saw a pmd page, try again.
		 */
		अगर (!new_pmd) अणु
			ret = -EAGAIN;
			जाओ out_unlock;
		पूर्ण
		/* Valid 1GB page here alपढ़ोy, हटाओ it */
		kvmppc_unmap_pte(kvm, (pte_t *)pud, hgpa, PUD_SHIFT, शून्य,
				 lpid);
	पूर्ण
	अगर (level == 2) अणु
		अगर (!pud_none(*pud)) अणु
			/*
			 * There's a page table page here, but we wanted to
			 * install a large page, so हटाओ and मुक्त the page
			 * table page.
			 */
			kvmppc_unmap_मुक्त_pud_entry_table(kvm, pud, gpa, lpid);
		पूर्ण
		kvmppc_radix_set_pte_at(kvm, gpa, (pte_t *)pud, pte);
		अगर (rmapp && n_rmap)
			kvmhv_insert_nest_rmap(kvm, rmapp, n_rmap);
		ret = 0;
		जाओ out_unlock;
	पूर्ण
	अगर (pud_none(*pud)) अणु
		अगर (!new_pmd)
			जाओ out_unlock;
		pud_populate(kvm->mm, pud, new_pmd);
		new_pmd = शून्य;
	पूर्ण
	pmd = pmd_offset(pud, gpa);
	अगर (pmd_is_leaf(*pmd)) अणु
		अचिन्हित दीर्घ lgpa = gpa & PMD_MASK;

		/* Check अगर we raced and someone अन्यथा has set the same thing */
		अगर (level == 1) अणु
			अगर (pmd_raw(*pmd) == pte_raw(pte)) अणु
				ret = 0;
				जाओ out_unlock;
			पूर्ण
			/* Valid 2MB page here alपढ़ोy, add our extra bits */
			WARN_ON_ONCE((pmd_val(*pmd) ^ pte_val(pte)) &
							PTE_BITS_MUST_MATCH);
			kvmppc_radix_update_pte(kvm, pmdp_ptep(pmd),
					0, pte_val(pte), lgpa, PMD_SHIFT);
			ret = 0;
			जाओ out_unlock;
		पूर्ण

		/*
		 * If we raced with another CPU which has just put
		 * a 2MB pte in after we saw a pte page, try again.
		 */
		अगर (!new_ptep) अणु
			ret = -EAGAIN;
			जाओ out_unlock;
		पूर्ण
		/* Valid 2MB page here alपढ़ोy, हटाओ it */
		kvmppc_unmap_pte(kvm, pmdp_ptep(pmd), lgpa, PMD_SHIFT, शून्य,
				 lpid);
	पूर्ण
	अगर (level == 1) अणु
		अगर (!pmd_none(*pmd)) अणु
			/*
			 * There's a page table page here, but we wanted to
			 * install a large page, so हटाओ and मुक्त the page
			 * table page.
			 */
			kvmppc_unmap_मुक्त_pmd_entry_table(kvm, pmd, gpa, lpid);
		पूर्ण
		kvmppc_radix_set_pte_at(kvm, gpa, pmdp_ptep(pmd), pte);
		अगर (rmapp && n_rmap)
			kvmhv_insert_nest_rmap(kvm, rmapp, n_rmap);
		ret = 0;
		जाओ out_unlock;
	पूर्ण
	अगर (pmd_none(*pmd)) अणु
		अगर (!new_ptep)
			जाओ out_unlock;
		pmd_populate(kvm->mm, pmd, new_ptep);
		new_ptep = शून्य;
	पूर्ण
	ptep = pte_offset_kernel(pmd, gpa);
	अगर (pte_present(*ptep)) अणु
		/* Check अगर someone अन्यथा set the same thing */
		अगर (pte_raw(*ptep) == pte_raw(pte)) अणु
			ret = 0;
			जाओ out_unlock;
		पूर्ण
		/* Valid page here alपढ़ोy, add our extra bits */
		WARN_ON_ONCE((pte_val(*ptep) ^ pte_val(pte)) &
							PTE_BITS_MUST_MATCH);
		kvmppc_radix_update_pte(kvm, ptep, 0, pte_val(pte), gpa, 0);
		ret = 0;
		जाओ out_unlock;
	पूर्ण
	kvmppc_radix_set_pte_at(kvm, gpa, ptep, pte);
	अगर (rmapp && n_rmap)
		kvmhv_insert_nest_rmap(kvm, rmapp, n_rmap);
	ret = 0;

 out_unlock:
	spin_unlock(&kvm->mmu_lock);
	अगर (new_pud)
		pud_मुक्त(kvm->mm, new_pud);
	अगर (new_pmd)
		kvmppc_pmd_मुक्त(new_pmd);
	अगर (new_ptep)
		kvmppc_pte_मुक्त(new_ptep);
	वापस ret;
पूर्ण

bool kvmppc_hv_handle_set_rc(काष्ठा kvm *kvm, bool nested, bool writing,
			     अचिन्हित दीर्घ gpa, अचिन्हित पूर्णांक lpid)
अणु
	अचिन्हित दीर्घ pgflags;
	अचिन्हित पूर्णांक shअगरt;
	pte_t *ptep;

	/*
	 * Need to set an R or C bit in the 2nd-level tables;
	 * since we are just helping out the hardware here,
	 * it is sufficient to करो what the hardware करोes.
	 */
	pgflags = _PAGE_ACCESSED;
	अगर (writing)
		pgflags |= _PAGE_सूचीTY;

	अगर (nested)
		ptep = find_kvm_nested_guest_pte(kvm, lpid, gpa, &shअगरt);
	अन्यथा
		ptep = find_kvm_secondary_pte(kvm, gpa, &shअगरt);

	अगर (ptep && pte_present(*ptep) && (!writing || pte_ग_लिखो(*ptep))) अणु
		kvmppc_radix_update_pte(kvm, ptep, 0, pgflags, gpa, shअगरt);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

पूर्णांक kvmppc_book3s_instantiate_page(काष्ठा kvm_vcpu *vcpu,
				   अचिन्हित दीर्घ gpa,
				   काष्ठा kvm_memory_slot *memslot,
				   bool writing, bool kvm_ro,
				   pte_t *inserted_pte, अचिन्हित पूर्णांक *levelp)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा page *page = शून्य;
	अचिन्हित दीर्घ mmu_seq;
	अचिन्हित दीर्घ hva, gfn = gpa >> PAGE_SHIFT;
	bool upgrade_ग_लिखो = false;
	bool *upgrade_p = &upgrade_ग_लिखो;
	pte_t pte, *ptep;
	अचिन्हित पूर्णांक shअगरt, level;
	पूर्णांक ret;
	bool large_enable;

	/* used to check क्रम invalidations in progress */
	mmu_seq = kvm->mmu_notअगरier_seq;
	smp_rmb();

	/*
	 * Do a fast check first, since __gfn_to_pfn_memslot करोesn't
	 * करो it with !atomic && !async, which is how we call it.
	 * We always ask क्रम ग_लिखो permission since the common हाल
	 * is that the page is writable.
	 */
	hva = gfn_to_hva_memslot(memslot, gfn);
	अगर (!kvm_ro && get_user_page_fast_only(hva, FOLL_WRITE, &page)) अणु
		upgrade_ग_लिखो = true;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ pfn;

		/* Call KVM generic code to करो the slow-path check */
		pfn = __gfn_to_pfn_memslot(memslot, gfn, false, शून्य,
					   writing, upgrade_p, शून्य);
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

	/* If we're logging dirty pages, always map single pages */
	large_enable = !(memslot->flags & KVM_MEM_LOG_सूचीTY_PAGES);

	/* Get pte level from shअगरt/size */
	अगर (large_enable && shअगरt == PUD_SHIFT &&
	    (gpa & (PUD_SIZE - PAGE_SIZE)) ==
	    (hva & (PUD_SIZE - PAGE_SIZE))) अणु
		level = 2;
	पूर्ण अन्यथा अगर (large_enable && shअगरt == PMD_SHIFT &&
		   (gpa & (PMD_SIZE - PAGE_SIZE)) ==
		   (hva & (PMD_SIZE - PAGE_SIZE))) अणु
		level = 1;
	पूर्ण अन्यथा अणु
		level = 0;
		अगर (shअगरt > PAGE_SHIFT) अणु
			/*
			 * If the pte maps more than one page, bring over
			 * bits from the भव address to get the real
			 * address of the specअगरic single page we want.
			 */
			अचिन्हित दीर्घ rpnmask = (1ul << shअगरt) - PAGE_SIZE;
			pte = __pte(pte_val(pte) | (hva & rpnmask));
		पूर्ण
	पूर्ण

	pte = __pte(pte_val(pte) | _PAGE_EXEC | _PAGE_ACCESSED);
	अगर (writing || upgrade_ग_लिखो) अणु
		अगर (pte_val(pte) & _PAGE_WRITE)
			pte = __pte(pte_val(pte) | _PAGE_सूचीTY);
	पूर्ण अन्यथा अणु
		pte = __pte(pte_val(pte) & ~(_PAGE_WRITE | _PAGE_सूचीTY));
	पूर्ण

	/* Allocate space in the tree and ग_लिखो the PTE */
	ret = kvmppc_create_pte(kvm, kvm->arch.pgtable, pte, gpa, level,
				mmu_seq, kvm->arch.lpid, शून्य, शून्य);
	अगर (inserted_pte)
		*inserted_pte = pte;
	अगर (levelp)
		*levelp = level;

	अगर (page) अणु
		अगर (!ret && (pte_val(pte) & _PAGE_WRITE))
			set_page_dirty_lock(page);
		put_page(page);
	पूर्ण

	/* Increment number of large pages अगर we (successfully) inserted one */
	अगर (!ret) अणु
		अगर (level == 1)
			kvm->stat.num_2M_pages++;
		अन्यथा अगर (level == 2)
			kvm->stat.num_1G_pages++;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक kvmppc_book3s_radix_page_fault(काष्ठा kvm_vcpu *vcpu,
				   अचिन्हित दीर्घ ea, अचिन्हित दीर्घ dsisr)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	अचिन्हित दीर्घ gpa, gfn;
	काष्ठा kvm_memory_slot *memslot;
	दीर्घ ret;
	bool writing = !!(dsisr & DSISR_ISSTORE);
	bool kvm_ro = false;

	/* Check क्रम unusual errors */
	अगर (dsisr & DSISR_UNSUPP_MMU) अणु
		pr_err("KVM: Got unsupported MMU fault\n");
		वापस -EFAULT;
	पूर्ण
	अगर (dsisr & DSISR_BADACCESS) अणु
		/* Reflect to the guest as DSI */
		pr_err("KVM: Got radix HV page fault with DSISR=%lx\n", dsisr);
		kvmppc_core_queue_data_storage(vcpu, ea, dsisr);
		वापस RESUME_GUEST;
	पूर्ण

	/* Translate the logical address */
	gpa = vcpu->arch.fault_gpa & ~0xfffUL;
	gpa &= ~0xF000000000000000ul;
	gfn = gpa >> PAGE_SHIFT;
	अगर (!(dsisr & DSISR_PRTABLE_FAULT))
		gpa |= ea & 0xfff;

	अगर (kvm->arch.secure_guest & KVMPPC_SECURE_INIT_DONE)
		वापस kvmppc_send_page_to_uv(kvm, gfn);

	/* Get the corresponding memslot */
	memslot = gfn_to_memslot(kvm, gfn);

	/* No memslot means it's an emulated MMIO region */
	अगर (!memslot || (memslot->flags & KVM_MEMSLOT_INVALID)) अणु
		अगर (dsisr & (DSISR_PRTABLE_FAULT | DSISR_BADACCESS |
			     DSISR_SET_RC)) अणु
			/*
			 * Bad address in guest page table tree, or other
			 * unusual error - reflect it to the guest as DSI.
			 */
			kvmppc_core_queue_data_storage(vcpu, ea, dsisr);
			वापस RESUME_GUEST;
		पूर्ण
		वापस kvmppc_hv_emulate_mmio(vcpu, gpa, ea, writing);
	पूर्ण

	अगर (memslot->flags & KVM_MEM_READONLY) अणु
		अगर (writing) अणु
			/* give the guest a DSI */
			kvmppc_core_queue_data_storage(vcpu, ea, DSISR_ISSTORE |
						       DSISR_PROTFAULT);
			वापस RESUME_GUEST;
		पूर्ण
		kvm_ro = true;
	पूर्ण

	/* Failed to set the reference/change bits */
	अगर (dsisr & DSISR_SET_RC) अणु
		spin_lock(&kvm->mmu_lock);
		अगर (kvmppc_hv_handle_set_rc(kvm, false, writing,
					    gpa, kvm->arch.lpid))
			dsisr &= ~DSISR_SET_RC;
		spin_unlock(&kvm->mmu_lock);

		अगर (!(dsisr & (DSISR_BAD_FAULT_64S | DSISR_NOHPTE |
			       DSISR_PROTFAULT | DSISR_SET_RC)))
			वापस RESUME_GUEST;
	पूर्ण

	/* Try to insert a pte */
	ret = kvmppc_book3s_instantiate_page(vcpu, gpa, memslot, writing,
					     kvm_ro, शून्य, शून्य);

	अगर (ret == 0 || ret == -EAGAIN)
		ret = RESUME_GUEST;
	वापस ret;
पूर्ण

/* Called with kvm->mmu_lock held */
व्योम kvm_unmap_radix(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *memslot,
		     अचिन्हित दीर्घ gfn)
अणु
	pte_t *ptep;
	अचिन्हित दीर्घ gpa = gfn << PAGE_SHIFT;
	अचिन्हित पूर्णांक shअगरt;

	अगर (kvm->arch.secure_guest & KVMPPC_SECURE_INIT_DONE) अणु
		uv_page_inval(kvm->arch.lpid, gpa, PAGE_SHIFT);
		वापस;
	पूर्ण

	ptep = find_kvm_secondary_pte(kvm, gpa, &shअगरt);
	अगर (ptep && pte_present(*ptep))
		kvmppc_unmap_pte(kvm, ptep, gpa, shअगरt, memslot,
				 kvm->arch.lpid);
पूर्ण

/* Called with kvm->mmu_lock held */
bool kvm_age_radix(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *memslot,
		   अचिन्हित दीर्घ gfn)
अणु
	pte_t *ptep;
	अचिन्हित दीर्घ gpa = gfn << PAGE_SHIFT;
	अचिन्हित पूर्णांक shअगरt;
	bool ref = false;
	अचिन्हित दीर्घ old, *rmapp;

	अगर (kvm->arch.secure_guest & KVMPPC_SECURE_INIT_DONE)
		वापस ref;

	ptep = find_kvm_secondary_pte(kvm, gpa, &shअगरt);
	अगर (ptep && pte_present(*ptep) && pte_young(*ptep)) अणु
		old = kvmppc_radix_update_pte(kvm, ptep, _PAGE_ACCESSED, 0,
					      gpa, shअगरt);
		/* XXX need to flush tlb here? */
		/* Also clear bit in ptes in shaकरोw pgtable क्रम nested guests */
		rmapp = &memslot->arch.rmap[gfn - memslot->base_gfn];
		kvmhv_update_nest_rmap_rc_list(kvm, rmapp, _PAGE_ACCESSED, 0,
					       old & PTE_RPN_MASK,
					       1UL << shअगरt);
		ref = true;
	पूर्ण
	वापस ref;
पूर्ण

/* Called with kvm->mmu_lock held */
bool kvm_test_age_radix(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *memslot,
			अचिन्हित दीर्घ gfn)

अणु
	pte_t *ptep;
	अचिन्हित दीर्घ gpa = gfn << PAGE_SHIFT;
	अचिन्हित पूर्णांक shअगरt;
	bool ref = false;

	अगर (kvm->arch.secure_guest & KVMPPC_SECURE_INIT_DONE)
		वापस ref;

	ptep = find_kvm_secondary_pte(kvm, gpa, &shअगरt);
	अगर (ptep && pte_present(*ptep) && pte_young(*ptep))
		ref = true;
	वापस ref;
पूर्ण

/* Returns the number of PAGE_SIZE pages that are dirty */
अटल पूर्णांक kvm_radix_test_clear_dirty(काष्ठा kvm *kvm,
				काष्ठा kvm_memory_slot *memslot, पूर्णांक pagक्रमागत)
अणु
	अचिन्हित दीर्घ gfn = memslot->base_gfn + pagक्रमागत;
	अचिन्हित दीर्घ gpa = gfn << PAGE_SHIFT;
	pte_t *ptep, pte;
	अचिन्हित पूर्णांक shअगरt;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ old, *rmapp;

	अगर (kvm->arch.secure_guest & KVMPPC_SECURE_INIT_DONE)
		वापस ret;

	/*
	 * For perक्रमmance reasons we करोn't hold kvm->mmu_lock जबतक walking the
	 * partition scoped table.
	 */
	ptep = find_kvm_secondary_pte_unlocked(kvm, gpa, &shअगरt);
	अगर (!ptep)
		वापस 0;

	pte = READ_ONCE(*ptep);
	अगर (pte_present(pte) && pte_dirty(pte)) अणु
		spin_lock(&kvm->mmu_lock);
		/*
		 * Recheck the pte again
		 */
		अगर (pte_val(pte) != pte_val(*ptep)) अणु
			/*
			 * We have KVM_MEM_LOG_सूचीTY_PAGES enabled. Hence we can
			 * only find PAGE_SIZE pte entries here. We can जारी
			 * to use the pte addr वापसed by above page table
			 * walk.
			 */
			अगर (!pte_present(*ptep) || !pte_dirty(*ptep)) अणु
				spin_unlock(&kvm->mmu_lock);
				वापस 0;
			पूर्ण
		पूर्ण

		ret = 1;
		VM_BUG_ON(shअगरt);
		old = kvmppc_radix_update_pte(kvm, ptep, _PAGE_सूचीTY, 0,
					      gpa, shअगरt);
		kvmppc_radix_tlbie_page(kvm, gpa, shअगरt, kvm->arch.lpid);
		/* Also clear bit in ptes in shaकरोw pgtable क्रम nested guests */
		rmapp = &memslot->arch.rmap[gfn - memslot->base_gfn];
		kvmhv_update_nest_rmap_rc_list(kvm, rmapp, _PAGE_सूचीTY, 0,
					       old & PTE_RPN_MASK,
					       1UL << shअगरt);
		spin_unlock(&kvm->mmu_lock);
	पूर्ण
	वापस ret;
पूर्ण

दीर्घ kvmppc_hv_get_dirty_log_radix(काष्ठा kvm *kvm,
			काष्ठा kvm_memory_slot *memslot, अचिन्हित दीर्घ *map)
अणु
	अचिन्हित दीर्घ i, j;
	पूर्णांक npages;

	क्रम (i = 0; i < memslot->npages; i = j) अणु
		npages = kvm_radix_test_clear_dirty(kvm, memslot, i);

		/*
		 * Note that अगर npages > 0 then i must be a multiple of npages,
		 * since huge pages are only used to back the guest at guest
		 * real addresses that are a multiple of their size.
		 * Since we have at most one PTE covering any given guest
		 * real address, अगर npages > 1 we can skip to i + npages.
		 */
		j = i + 1;
		अगर (npages) अणु
			set_dirty_bits(map, i, npages);
			j = i + npages;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

व्योम kvmppc_radix_flush_memslot(काष्ठा kvm *kvm,
				स्थिर काष्ठा kvm_memory_slot *memslot)
अणु
	अचिन्हित दीर्घ n;
	pte_t *ptep;
	अचिन्हित दीर्घ gpa;
	अचिन्हित पूर्णांक shअगरt;

	अगर (kvm->arch.secure_guest & KVMPPC_SECURE_INIT_START)
		kvmppc_uvmem_drop_pages(memslot, kvm, true);

	अगर (kvm->arch.secure_guest & KVMPPC_SECURE_INIT_DONE)
		वापस;

	gpa = memslot->base_gfn << PAGE_SHIFT;
	spin_lock(&kvm->mmu_lock);
	क्रम (n = memslot->npages; n; --n) अणु
		ptep = find_kvm_secondary_pte(kvm, gpa, &shअगरt);
		अगर (ptep && pte_present(*ptep))
			kvmppc_unmap_pte(kvm, ptep, gpa, shअगरt, memslot,
					 kvm->arch.lpid);
		gpa += PAGE_SIZE;
	पूर्ण
	/*
	 * Increase the mmu notअगरier sequence number to prevent any page
	 * fault that पढ़ो the memslot earlier from writing a PTE.
	 */
	kvm->mmu_notअगरier_seq++;
	spin_unlock(&kvm->mmu_lock);
पूर्ण

अटल व्योम add_rmmu_ap_encoding(काष्ठा kvm_ppc_rmmu_info *info,
				 पूर्णांक psize, पूर्णांक *indexp)
अणु
	अगर (!mmu_psize_defs[psize].shअगरt)
		वापस;
	info->ap_encodings[*indexp] = mmu_psize_defs[psize].shअगरt |
		(mmu_psize_defs[psize].ap << 29);
	++(*indexp);
पूर्ण

पूर्णांक kvmhv_get_rmmu_info(काष्ठा kvm *kvm, काष्ठा kvm_ppc_rmmu_info *info)
अणु
	पूर्णांक i;

	अगर (!radix_enabled())
		वापस -EINVAL;
	स_रखो(info, 0, माप(*info));

	/* 4k page size */
	info->geometries[0].page_shअगरt = 12;
	info->geometries[0].level_bits[0] = 9;
	क्रम (i = 1; i < 4; ++i)
		info->geometries[0].level_bits[i] = p9_supported_radix_bits[i];
	/* 64k page size */
	info->geometries[1].page_shअगरt = 16;
	क्रम (i = 0; i < 4; ++i)
		info->geometries[1].level_bits[i] = p9_supported_radix_bits[i];

	i = 0;
	add_rmmu_ap_encoding(info, MMU_PAGE_4K, &i);
	add_rmmu_ap_encoding(info, MMU_PAGE_64K, &i);
	add_rmmu_ap_encoding(info, MMU_PAGE_2M, &i);
	add_rmmu_ap_encoding(info, MMU_PAGE_1G, &i);

	वापस 0;
पूर्ण

पूर्णांक kvmppc_init_vm_radix(काष्ठा kvm *kvm)
अणु
	kvm->arch.pgtable = pgd_alloc(kvm->mm);
	अगर (!kvm->arch.pgtable)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम pte_ctor(व्योम *addr)
अणु
	स_रखो(addr, 0, RADIX_PTE_TABLE_SIZE);
पूर्ण

अटल व्योम pmd_ctor(व्योम *addr)
अणु
	स_रखो(addr, 0, RADIX_PMD_TABLE_SIZE);
पूर्ण

काष्ठा debugfs_radix_state अणु
	काष्ठा kvm	*kvm;
	काष्ठा mutex	mutex;
	अचिन्हित दीर्घ	gpa;
	पूर्णांक		lpid;
	पूर्णांक		अक्षरs_left;
	पूर्णांक		buf_index;
	अक्षर		buf[128];
	u8		hdr;
पूर्ण;

अटल पूर्णांक debugfs_radix_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा kvm *kvm = inode->i_निजी;
	काष्ठा debugfs_radix_state *p;

	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	kvm_get_kvm(kvm);
	p->kvm = kvm;
	mutex_init(&p->mutex);
	file->निजी_data = p;

	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल पूर्णांक debugfs_radix_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा debugfs_radix_state *p = file->निजी_data;

	kvm_put_kvm(p->kvm);
	kमुक्त(p);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार debugfs_radix_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				 माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा debugfs_radix_state *p = file->निजी_data;
	sमाप_प्रकार ret, r;
	अचिन्हित दीर्घ n;
	काष्ठा kvm *kvm;
	अचिन्हित दीर्घ gpa;
	pgd_t *pgt;
	काष्ठा kvm_nested_guest *nested;
	pgd_t *pgdp;
	p4d_t p4d, *p4dp;
	pud_t pud, *pudp;
	pmd_t pmd, *pmdp;
	pte_t *ptep;
	पूर्णांक shअगरt;
	अचिन्हित दीर्घ pte;

	kvm = p->kvm;
	अगर (!kvm_is_radix(kvm))
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

	gpa = p->gpa;
	nested = शून्य;
	pgt = शून्य;
	जबतक (len != 0 && p->lpid >= 0) अणु
		अगर (gpa >= RADIX_PGTABLE_RANGE) अणु
			gpa = 0;
			pgt = शून्य;
			अगर (nested) अणु
				kvmhv_put_nested(nested);
				nested = शून्य;
			पूर्ण
			p->lpid = kvmhv_nested_next_lpid(kvm, p->lpid);
			p->hdr = 0;
			अगर (p->lpid < 0)
				अवरोध;
		पूर्ण
		अगर (!pgt) अणु
			अगर (p->lpid == 0) अणु
				pgt = kvm->arch.pgtable;
			पूर्ण अन्यथा अणु
				nested = kvmhv_get_nested(kvm, p->lpid, false);
				अगर (!nested) अणु
					gpa = RADIX_PGTABLE_RANGE;
					जारी;
				पूर्ण
				pgt = nested->shaकरोw_pgtable;
			पूर्ण
		पूर्ण
		n = 0;
		अगर (!p->hdr) अणु
			अगर (p->lpid > 0)
				n = scnम_लिखो(p->buf, माप(p->buf),
					      "\nNested LPID %d: ", p->lpid);
			n += scnम_लिखो(p->buf + n, माप(p->buf) - n,
				      "pgdir: %lx\n", (अचिन्हित दीर्घ)pgt);
			p->hdr = 1;
			जाओ copy;
		पूर्ण

		pgdp = pgt + pgd_index(gpa);
		p4dp = p4d_offset(pgdp, gpa);
		p4d = READ_ONCE(*p4dp);
		अगर (!(p4d_val(p4d) & _PAGE_PRESENT)) अणु
			gpa = (gpa & P4D_MASK) + P4D_SIZE;
			जारी;
		पूर्ण

		pudp = pud_offset(&p4d, gpa);
		pud = READ_ONCE(*pudp);
		अगर (!(pud_val(pud) & _PAGE_PRESENT)) अणु
			gpa = (gpa & PUD_MASK) + PUD_SIZE;
			जारी;
		पूर्ण
		अगर (pud_val(pud) & _PAGE_PTE) अणु
			pte = pud_val(pud);
			shअगरt = PUD_SHIFT;
			जाओ leaf;
		पूर्ण

		pmdp = pmd_offset(&pud, gpa);
		pmd = READ_ONCE(*pmdp);
		अगर (!(pmd_val(pmd) & _PAGE_PRESENT)) अणु
			gpa = (gpa & PMD_MASK) + PMD_SIZE;
			जारी;
		पूर्ण
		अगर (pmd_val(pmd) & _PAGE_PTE) अणु
			pte = pmd_val(pmd);
			shअगरt = PMD_SHIFT;
			जाओ leaf;
		पूर्ण

		ptep = pte_offset_kernel(&pmd, gpa);
		pte = pte_val(READ_ONCE(*ptep));
		अगर (!(pte & _PAGE_PRESENT)) अणु
			gpa += PAGE_SIZE;
			जारी;
		पूर्ण
		shअगरt = PAGE_SHIFT;
	leaf:
		n = scnम_लिखो(p->buf, माप(p->buf),
			      " %lx: %lx %d\n", gpa, pte, shअगरt);
		gpa += 1ul << shअगरt;
	copy:
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
			अवरोध;
		पूर्ण
	पूर्ण
	p->gpa = gpa;
	अगर (nested)
		kvmhv_put_nested(nested);

 out:
	mutex_unlock(&p->mutex);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार debugfs_radix_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			   माप_प्रकार len, loff_t *ppos)
अणु
	वापस -EACCES;
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_radix_fops = अणु
	.owner	 = THIS_MODULE,
	.खोलो	 = debugfs_radix_खोलो,
	.release = debugfs_radix_release,
	.पढ़ो	 = debugfs_radix_पढ़ो,
	.ग_लिखो	 = debugfs_radix_ग_लिखो,
	.llseek	 = generic_file_llseek,
पूर्ण;

व्योम kvmhv_radix_debugfs_init(काष्ठा kvm *kvm)
अणु
	debugfs_create_file("radix", 0400, kvm->arch.debugfs_dir, kvm,
			    &debugfs_radix_fops);
पूर्ण

पूर्णांक kvmppc_radix_init(व्योम)
अणु
	अचिन्हित दीर्घ size = माप(व्योम *) << RADIX_PTE_INDEX_SIZE;

	kvm_pte_cache = kmem_cache_create("kvm-pte", size, size, 0, pte_ctor);
	अगर (!kvm_pte_cache)
		वापस -ENOMEM;

	size = माप(व्योम *) << RADIX_PMD_INDEX_SIZE;

	kvm_pmd_cache = kmem_cache_create("kvm-pmd", size, size, 0, pmd_ctor);
	अगर (!kvm_pmd_cache) अणु
		kmem_cache_destroy(kvm_pte_cache);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

व्योम kvmppc_radix_निकास(व्योम)
अणु
	kmem_cache_destroy(kvm_pte_cache);
	kmem_cache_destroy(kvm_pmd_cache);
पूर्ण
