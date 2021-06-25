<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright 2010 Paul Mackerras, IBM Corp. <paulus@au1.ibm.com>
 * Copyright 2011 David Gibson, IBM Corporation <dwg@au1.ibm.com>
 * Copyright 2016 Alexey Kardashevskiy, IBM Corporation <aik@au1.ibm.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/kvm.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/gfp.h>
#समावेश <linux/slab.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/list.h>
#समावेश <linux/stringअगरy.h>

#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/book3s/64/mmu-hash.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/synch.h>
#समावेश <यंत्र/ppc-opcode.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/tce.h>
#समावेश <यंत्र/pte-walk.h>

#अगर_घोषित CONFIG_BUG

#घोषणा WARN_ON_ONCE_RM(condition)	(अणु			\
	अटल bool __section(".data.unlikely") __warned;	\
	पूर्णांक __ret_warn_once = !!(condition);			\
								\
	अगर (unlikely(__ret_warn_once && !__warned)) अणु		\
		__warned = true;				\
		pr_err("WARN_ON_ONCE_RM: (%s) at %s:%u\n",	\
				__stringअगरy(condition),		\
				__func__, __LINE__);		\
		dump_stack();					\
	पूर्ण							\
	unlikely(__ret_warn_once);				\
पूर्ण)

#अन्यथा

#घोषणा WARN_ON_ONCE_RM(condition) (अणु				\
	पूर्णांक __ret_warn_on = !!(condition);			\
	unlikely(__ret_warn_on);				\
पूर्ण)

#पूर्ण_अगर

/*
 * Finds a TCE table descriptor by LIOBN.
 *
 * WARNING: This will be called in real or भव mode on HV KVM and भव
 *          mode on PR KVM
 */
काष्ठा kvmppc_spapr_tce_table *kvmppc_find_table(काष्ठा kvm *kvm,
		अचिन्हित दीर्घ liobn)
अणु
	काष्ठा kvmppc_spapr_tce_table *stt;

	list_क्रम_each_entry_lockless(stt, &kvm->arch.spapr_tce_tables, list)
		अगर (stt->liobn == liobn)
			वापस stt;

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_find_table);

#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
अटल दीर्घ kvmppc_rm_tce_to_ua(काष्ठा kvm *kvm,
				अचिन्हित दीर्घ tce, अचिन्हित दीर्घ *ua)
अणु
	अचिन्हित दीर्घ gfn = tce >> PAGE_SHIFT;
	काष्ठा kvm_memory_slot *memslot;

	memslot = search_memslots(kvm_memslots_raw(kvm), gfn);
	अगर (!memslot)
		वापस -EINVAL;

	*ua = __gfn_to_hva_memslot(memslot, gfn) |
		(tce & ~(PAGE_MASK | TCE_PCI_READ | TCE_PCI_WRITE));

	वापस 0;
पूर्ण

/*
 * Validates TCE address.
 * At the moment flags and page mask are validated.
 * As the host kernel करोes not access those addresses (just माला_दो them
 * to the table and user space is supposed to process them), we can skip
 * checking other things (such as TCE is a guest RAM address or the page
 * was actually allocated).
 */
अटल दीर्घ kvmppc_rm_tce_validate(काष्ठा kvmppc_spapr_tce_table *stt,
		अचिन्हित दीर्घ tce)
अणु
	अचिन्हित दीर्घ gpa = tce & ~(TCE_PCI_READ | TCE_PCI_WRITE);
	क्रमागत dma_data_direction dir = iommu_tce_direction(tce);
	काष्ठा kvmppc_spapr_tce_iommu_table *stit;
	अचिन्हित दीर्घ ua = 0;

	/* Allow userspace to poison TCE table */
	अगर (dir == DMA_NONE)
		वापस H_SUCCESS;

	अगर (iommu_tce_check_gpa(stt->page_shअगरt, gpa))
		वापस H_PARAMETER;

	अगर (kvmppc_rm_tce_to_ua(stt->kvm, tce, &ua))
		वापस H_TOO_HARD;

	list_क्रम_each_entry_lockless(stit, &stt->iommu_tables, next) अणु
		अचिन्हित दीर्घ hpa = 0;
		काष्ठा mm_iommu_table_group_mem_t *mem;
		दीर्घ shअगरt = stit->tbl->it_page_shअगरt;

		mem = mm_iommu_lookup_rm(stt->kvm->mm, ua, 1ULL << shअगरt);
		अगर (!mem)
			वापस H_TOO_HARD;

		अगर (mm_iommu_ua_to_hpa_rm(mem, ua, shअगरt, &hpa))
			वापस H_TOO_HARD;
	पूर्ण

	वापस H_SUCCESS;
पूर्ण

/* Note on the use of page_address() in real mode,
 *
 * It is safe to use page_address() in real mode on ppc64 because
 * page_address() is always defined as lowmem_page_address()
 * which वापसs __va(PFN_PHYS(page_to_pfn(page))) which is arithmetic
 * operation and करोes not access page काष्ठा.
 *
 * Theoretically page_address() could be defined dअगरferent
 * but either WANT_PAGE_VIRTUAL or HASHED_PAGE_VIRTUAL
 * would have to be enabled.
 * WANT_PAGE_VIRTUAL is never enabled on ppc32/ppc64,
 * HASHED_PAGE_VIRTUAL could be enabled क्रम ppc32 only and only
 * अगर CONFIG_HIGHMEM is defined. As CONFIG_SPARSEMEM_VMEMMAP
 * is not expected to be enabled on ppc32, page_address()
 * is safe क्रम ppc32 as well.
 *
 * WARNING: This will be called in real-mode on HV KVM and भव
 *          mode on PR KVM
 */
अटल u64 *kvmppc_page_address(काष्ठा page *page)
अणु
#अगर defined(HASHED_PAGE_VIRTUAL) || defined(WANT_PAGE_VIRTUAL)
#त्रुटि TODO: fix to aव्योम page_address() here
#पूर्ण_अगर
	वापस (u64 *) page_address(page);
पूर्ण

/*
 * Handles TCE requests क्रम emulated devices.
 * Puts guest TCE values to the table and expects user space to convert them.
 * Cannot fail so kvmppc_rm_tce_validate must be called beक्रमe it.
 */
अटल व्योम kvmppc_rm_tce_put(काष्ठा kvmppc_spapr_tce_table *stt,
		अचिन्हित दीर्घ idx, अचिन्हित दीर्घ tce)
अणु
	काष्ठा page *page;
	u64 *tbl;

	idx -= stt->offset;
	page = stt->pages[idx / TCES_PER_PAGE];
	/*
	 * page must not be शून्य in real mode,
	 * kvmppc_rm_ioba_validate() must have taken care of this.
	 */
	WARN_ON_ONCE_RM(!page);
	tbl = kvmppc_page_address(page);

	tbl[idx % TCES_PER_PAGE] = tce;
पूर्ण

/*
 * TCEs pages are allocated in kvmppc_rm_tce_put() which won't be able to करो so
 * in real mode.
 * Check अगर kvmppc_rm_tce_put() can succeed in real mode, i.e. a TCEs page is
 * allocated or not required (when clearing a tce entry).
 */
अटल दीर्घ kvmppc_rm_ioba_validate(काष्ठा kvmppc_spapr_tce_table *stt,
		अचिन्हित दीर्घ ioba, अचिन्हित दीर्घ npages, bool clearing)
अणु
	अचिन्हित दीर्घ i, idx, sttpage, sttpages;
	अचिन्हित दीर्घ ret = kvmppc_ioba_validate(stt, ioba, npages);

	अगर (ret)
		वापस ret;
	/*
	 * clearing==true says kvmppc_rm_tce_put won't be allocating pages
	 * क्रम empty tces.
	 */
	अगर (clearing)
		वापस H_SUCCESS;

	idx = (ioba >> stt->page_shअगरt) - stt->offset;
	sttpage = idx / TCES_PER_PAGE;
	sttpages = ALIGN(idx % TCES_PER_PAGE + npages, TCES_PER_PAGE) /
			TCES_PER_PAGE;
	क्रम (i = sttpage; i < sttpage + sttpages; ++i)
		अगर (!stt->pages[i])
			वापस H_TOO_HARD;

	वापस H_SUCCESS;
पूर्ण

अटल दीर्घ iommu_tce_xchg_no_समाप्त_rm(काष्ठा mm_काष्ठा *mm,
		काष्ठा iommu_table *tbl,
		अचिन्हित दीर्घ entry, अचिन्हित दीर्घ *hpa,
		क्रमागत dma_data_direction *direction)
अणु
	दीर्घ ret;

	ret = tbl->it_ops->xchg_no_समाप्त(tbl, entry, hpa, direction, true);

	अगर (!ret && ((*direction == DMA_FROM_DEVICE) ||
				(*direction == DMA_BIसूचीECTIONAL))) अणु
		__be64 *pua = IOMMU_TABLE_USERSPACE_ENTRY_RO(tbl, entry);
		/*
		 * kvmppc_rm_tce_iommu_करो_map() updates the UA cache after
		 * calling this so we still get here a valid UA.
		 */
		अगर (pua && *pua)
			mm_iommu_ua_mark_dirty_rm(mm, be64_to_cpu(*pua));
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम iommu_tce_समाप्त_rm(काष्ठा iommu_table *tbl,
		अचिन्हित दीर्घ entry, अचिन्हित दीर्घ pages)
अणु
	अगर (tbl->it_ops->tce_समाप्त)
		tbl->it_ops->tce_समाप्त(tbl, entry, pages, true);
पूर्ण

अटल व्योम kvmppc_rm_clear_tce(काष्ठा kvm *kvm, काष्ठा iommu_table *tbl,
		अचिन्हित दीर्घ entry)
अणु
	अचिन्हित दीर्घ hpa = 0;
	क्रमागत dma_data_direction dir = DMA_NONE;

	iommu_tce_xchg_no_समाप्त_rm(kvm->mm, tbl, entry, &hpa, &dir);
पूर्ण

अटल दीर्घ kvmppc_rm_tce_iommu_mapped_dec(काष्ठा kvm *kvm,
		काष्ठा iommu_table *tbl, अचिन्हित दीर्घ entry)
अणु
	काष्ठा mm_iommu_table_group_mem_t *mem = शून्य;
	स्थिर अचिन्हित दीर्घ pgsize = 1ULL << tbl->it_page_shअगरt;
	__be64 *pua = IOMMU_TABLE_USERSPACE_ENTRY_RO(tbl, entry);

	अगर (!pua)
		/* it_userspace allocation might be delayed */
		वापस H_TOO_HARD;

	mem = mm_iommu_lookup_rm(kvm->mm, be64_to_cpu(*pua), pgsize);
	अगर (!mem)
		वापस H_TOO_HARD;

	mm_iommu_mapped_dec(mem);

	*pua = cpu_to_be64(0);

	वापस H_SUCCESS;
पूर्ण

अटल दीर्घ kvmppc_rm_tce_iommu_करो_unmap(काष्ठा kvm *kvm,
		काष्ठा iommu_table *tbl, अचिन्हित दीर्घ entry)
अणु
	क्रमागत dma_data_direction dir = DMA_NONE;
	अचिन्हित दीर्घ hpa = 0;
	दीर्घ ret;

	अगर (iommu_tce_xchg_no_समाप्त_rm(kvm->mm, tbl, entry, &hpa, &dir))
		/*
		 * real mode xchg can fail अगर काष्ठा page crosses
		 * a page boundary
		 */
		वापस H_TOO_HARD;

	अगर (dir == DMA_NONE)
		वापस H_SUCCESS;

	ret = kvmppc_rm_tce_iommu_mapped_dec(kvm, tbl, entry);
	अगर (ret)
		iommu_tce_xchg_no_समाप्त_rm(kvm->mm, tbl, entry, &hpa, &dir);

	वापस ret;
पूर्ण

अटल दीर्घ kvmppc_rm_tce_iommu_unmap(काष्ठा kvm *kvm,
		काष्ठा kvmppc_spapr_tce_table *stt, काष्ठा iommu_table *tbl,
		अचिन्हित दीर्घ entry)
अणु
	अचिन्हित दीर्घ i, ret = H_SUCCESS;
	अचिन्हित दीर्घ subpages = 1ULL << (stt->page_shअगरt - tbl->it_page_shअगरt);
	अचिन्हित दीर्घ io_entry = entry * subpages;

	क्रम (i = 0; i < subpages; ++i) अणु
		ret = kvmppc_rm_tce_iommu_करो_unmap(kvm, tbl, io_entry + i);
		अगर (ret != H_SUCCESS)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल दीर्घ kvmppc_rm_tce_iommu_करो_map(काष्ठा kvm *kvm, काष्ठा iommu_table *tbl,
		अचिन्हित दीर्घ entry, अचिन्हित दीर्घ ua,
		क्रमागत dma_data_direction dir)
अणु
	दीर्घ ret;
	अचिन्हित दीर्घ hpa = 0;
	__be64 *pua = IOMMU_TABLE_USERSPACE_ENTRY_RO(tbl, entry);
	काष्ठा mm_iommu_table_group_mem_t *mem;

	अगर (!pua)
		/* it_userspace allocation might be delayed */
		वापस H_TOO_HARD;

	mem = mm_iommu_lookup_rm(kvm->mm, ua, 1ULL << tbl->it_page_shअगरt);
	अगर (!mem)
		वापस H_TOO_HARD;

	अगर (WARN_ON_ONCE_RM(mm_iommu_ua_to_hpa_rm(mem, ua, tbl->it_page_shअगरt,
			&hpa)))
		वापस H_TOO_HARD;

	अगर (WARN_ON_ONCE_RM(mm_iommu_mapped_inc(mem)))
		वापस H_TOO_HARD;

	ret = iommu_tce_xchg_no_समाप्त_rm(kvm->mm, tbl, entry, &hpa, &dir);
	अगर (ret) अणु
		mm_iommu_mapped_dec(mem);
		/*
		 * real mode xchg can fail अगर काष्ठा page crosses
		 * a page boundary
		 */
		वापस H_TOO_HARD;
	पूर्ण

	अगर (dir != DMA_NONE)
		kvmppc_rm_tce_iommu_mapped_dec(kvm, tbl, entry);

	*pua = cpu_to_be64(ua);

	वापस 0;
पूर्ण

अटल दीर्घ kvmppc_rm_tce_iommu_map(काष्ठा kvm *kvm,
		काष्ठा kvmppc_spapr_tce_table *stt, काष्ठा iommu_table *tbl,
		अचिन्हित दीर्घ entry, अचिन्हित दीर्घ ua,
		क्रमागत dma_data_direction dir)
अणु
	अचिन्हित दीर्घ i, pgoff, ret = H_SUCCESS;
	अचिन्हित दीर्घ subpages = 1ULL << (stt->page_shअगरt - tbl->it_page_shअगरt);
	अचिन्हित दीर्घ io_entry = entry * subpages;

	क्रम (i = 0, pgoff = 0; i < subpages;
			++i, pgoff += IOMMU_PAGE_SIZE(tbl)) अणु

		ret = kvmppc_rm_tce_iommu_करो_map(kvm, tbl,
				io_entry + i, ua + pgoff, dir);
		अगर (ret != H_SUCCESS)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

दीर्घ kvmppc_rm_h_put_tce(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ liobn,
		अचिन्हित दीर्घ ioba, अचिन्हित दीर्घ tce)
अणु
	काष्ठा kvmppc_spapr_tce_table *stt;
	दीर्घ ret;
	काष्ठा kvmppc_spapr_tce_iommu_table *stit;
	अचिन्हित दीर्घ entry, ua = 0;
	क्रमागत dma_data_direction dir;

	/* udbg_म_लिखो("H_PUT_TCE(): liobn=0x%lx ioba=0x%lx, tce=0x%lx\n", */
	/* 	    liobn, ioba, tce); */

	/* For radix, we might be in भव mode, so punt */
	अगर (kvm_is_radix(vcpu->kvm))
		वापस H_TOO_HARD;

	stt = kvmppc_find_table(vcpu->kvm, liobn);
	अगर (!stt)
		वापस H_TOO_HARD;

	ret = kvmppc_rm_ioba_validate(stt, ioba, 1, tce == 0);
	अगर (ret != H_SUCCESS)
		वापस ret;

	ret = kvmppc_rm_tce_validate(stt, tce);
	अगर (ret != H_SUCCESS)
		वापस ret;

	dir = iommu_tce_direction(tce);
	अगर ((dir != DMA_NONE) && kvmppc_rm_tce_to_ua(vcpu->kvm, tce, &ua))
		वापस H_PARAMETER;

	entry = ioba >> stt->page_shअगरt;

	list_क्रम_each_entry_lockless(stit, &stt->iommu_tables, next) अणु
		अगर (dir == DMA_NONE)
			ret = kvmppc_rm_tce_iommu_unmap(vcpu->kvm, stt,
					stit->tbl, entry);
		अन्यथा
			ret = kvmppc_rm_tce_iommu_map(vcpu->kvm, stt,
					stit->tbl, entry, ua, dir);

		iommu_tce_समाप्त_rm(stit->tbl, entry, 1);

		अगर (ret != H_SUCCESS) अणु
			kvmppc_rm_clear_tce(vcpu->kvm, stit->tbl, entry);
			वापस ret;
		पूर्ण
	पूर्ण

	kvmppc_rm_tce_put(stt, entry, tce);

	वापस H_SUCCESS;
पूर्ण

अटल दीर्घ kvmppc_rm_ua_to_hpa(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ mmu_seq,
				अचिन्हित दीर्घ ua, अचिन्हित दीर्घ *phpa)
अणु
	pte_t *ptep, pte;
	अचिन्हित shअगरt = 0;

	/*
	 * Called in real mode with MSR_EE = 0. We are safe here.
	 * It is ok to करो the lookup with arch.pgdir here, because
	 * we are करोing this on secondary cpus and current task there
	 * is not the hypervisor. Also this is safe against THP in the
	 * host, because an IPI to primary thपढ़ो will रुको क्रम the secondary
	 * to निकास which will agains result in the below page table walk
	 * to finish.
	 */
	/* an rmap lock won't make it safe. because that just ensure hash
	 * page table entries are हटाओd with rmap lock held. After that
	 * mmu notअगरier वापसs and we go ahead and removing ptes from Qemu page table.
	 */
	ptep = find_kvm_host_pte(vcpu->kvm, mmu_seq, ua, &shअगरt);
	अगर (!ptep)
		वापस -ENXIO;

	pte = READ_ONCE(*ptep);
	अगर (!pte_present(pte))
		वापस -ENXIO;

	अगर (!shअगरt)
		shअगरt = PAGE_SHIFT;

	/* Aव्योम handling anything potentially complicated in realmode */
	अगर (shअगरt > PAGE_SHIFT)
		वापस -EAGAIN;

	अगर (!pte_young(pte))
		वापस -EAGAIN;

	*phpa = (pte_pfn(pte) << PAGE_SHIFT) | (ua & ((1ULL << shअगरt) - 1)) |
			(ua & ~PAGE_MASK);

	वापस 0;
पूर्ण

दीर्घ kvmppc_rm_h_put_tce_indirect(काष्ठा kvm_vcpu *vcpu,
		अचिन्हित दीर्घ liobn, अचिन्हित दीर्घ ioba,
		अचिन्हित दीर्घ tce_list,	अचिन्हित दीर्घ npages)
अणु
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा kvmppc_spapr_tce_table *stt;
	दीर्घ i, ret = H_SUCCESS;
	अचिन्हित दीर्घ tces, entry, ua = 0;
	अचिन्हित दीर्घ mmu_seq;
	bool prereg = false;
	काष्ठा kvmppc_spapr_tce_iommu_table *stit;

	/* For radix, we might be in भव mode, so punt */
	अगर (kvm_is_radix(vcpu->kvm))
		वापस H_TOO_HARD;

	/*
	 * used to check क्रम invalidations in progress
	 */
	mmu_seq = kvm->mmu_notअगरier_seq;
	smp_rmb();

	stt = kvmppc_find_table(vcpu->kvm, liobn);
	अगर (!stt)
		वापस H_TOO_HARD;

	entry = ioba >> stt->page_shअगरt;
	/*
	 * The spec says that the maximum size of the list is 512 TCEs
	 * so the whole table addressed resides in 4K page
	 */
	अगर (npages > 512)
		वापस H_PARAMETER;

	अगर (tce_list & (SZ_4K - 1))
		वापस H_PARAMETER;

	ret = kvmppc_rm_ioba_validate(stt, ioba, npages, false);
	अगर (ret != H_SUCCESS)
		वापस ret;

	अगर (mm_iommu_preरेजिस्टरed(vcpu->kvm->mm)) अणु
		/*
		 * We get here अगर guest memory was pre-रेजिस्टरed which
		 * is normally VFIO हाल and gpa->hpa translation करोes not
		 * depend on hpt.
		 */
		काष्ठा mm_iommu_table_group_mem_t *mem;

		अगर (kvmppc_rm_tce_to_ua(vcpu->kvm, tce_list, &ua))
			वापस H_TOO_HARD;

		mem = mm_iommu_lookup_rm(vcpu->kvm->mm, ua, IOMMU_PAGE_SIZE_4K);
		अगर (mem)
			prereg = mm_iommu_ua_to_hpa_rm(mem, ua,
					IOMMU_PAGE_SHIFT_4K, &tces) == 0;
	पूर्ण

	अगर (!prereg) अणु
		/*
		 * This is usually a हाल of a guest with emulated devices only
		 * when TCE list is not in preरेजिस्टरed memory.
		 * We करो not require memory to be preरेजिस्टरed in this हाल
		 * so lock rmap and करो __find_linux_pte_or_hugepte().
		 */
		अगर (kvmppc_rm_tce_to_ua(vcpu->kvm, tce_list, &ua))
			वापस H_TOO_HARD;

		arch_spin_lock(&kvm->mmu_lock.rlock.raw_lock);
		अगर (kvmppc_rm_ua_to_hpa(vcpu, mmu_seq, ua, &tces)) अणु
			ret = H_TOO_HARD;
			जाओ unlock_निकास;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < npages; ++i) अणु
		अचिन्हित दीर्घ tce = be64_to_cpu(((u64 *)tces)[i]);

		ret = kvmppc_rm_tce_validate(stt, tce);
		अगर (ret != H_SUCCESS)
			जाओ unlock_निकास;
	पूर्ण

	क्रम (i = 0; i < npages; ++i) अणु
		अचिन्हित दीर्घ tce = be64_to_cpu(((u64 *)tces)[i]);

		ua = 0;
		अगर (kvmppc_rm_tce_to_ua(vcpu->kvm, tce, &ua)) अणु
			ret = H_PARAMETER;
			जाओ invalidate_निकास;
		पूर्ण

		list_क्रम_each_entry_lockless(stit, &stt->iommu_tables, next) अणु
			ret = kvmppc_rm_tce_iommu_map(vcpu->kvm, stt,
					stit->tbl, entry + i, ua,
					iommu_tce_direction(tce));

			अगर (ret != H_SUCCESS) अणु
				kvmppc_rm_clear_tce(vcpu->kvm, stit->tbl,
						entry);
				जाओ invalidate_निकास;
			पूर्ण
		पूर्ण

		kvmppc_rm_tce_put(stt, entry + i, tce);
	पूर्ण

invalidate_निकास:
	list_क्रम_each_entry_lockless(stit, &stt->iommu_tables, next)
		iommu_tce_समाप्त_rm(stit->tbl, entry, npages);

unlock_निकास:
	अगर (!prereg)
		arch_spin_unlock(&kvm->mmu_lock.rlock.raw_lock);
	वापस ret;
पूर्ण

दीर्घ kvmppc_rm_h_stuff_tce(काष्ठा kvm_vcpu *vcpu,
		अचिन्हित दीर्घ liobn, अचिन्हित दीर्घ ioba,
		अचिन्हित दीर्घ tce_value, अचिन्हित दीर्घ npages)
अणु
	काष्ठा kvmppc_spapr_tce_table *stt;
	दीर्घ i, ret;
	काष्ठा kvmppc_spapr_tce_iommu_table *stit;

	/* For radix, we might be in भव mode, so punt */
	अगर (kvm_is_radix(vcpu->kvm))
		वापस H_TOO_HARD;

	stt = kvmppc_find_table(vcpu->kvm, liobn);
	अगर (!stt)
		वापस H_TOO_HARD;

	ret = kvmppc_rm_ioba_validate(stt, ioba, npages, tce_value == 0);
	अगर (ret != H_SUCCESS)
		वापस ret;

	/* Check permission bits only to allow userspace poison TCE क्रम debug */
	अगर (tce_value & (TCE_PCI_WRITE | TCE_PCI_READ))
		वापस H_PARAMETER;

	list_क्रम_each_entry_lockless(stit, &stt->iommu_tables, next) अणु
		अचिन्हित दीर्घ entry = ioba >> stt->page_shअगरt;

		क्रम (i = 0; i < npages; ++i) अणु
			ret = kvmppc_rm_tce_iommu_unmap(vcpu->kvm, stt,
					stit->tbl, entry + i);

			अगर (ret == H_SUCCESS)
				जारी;

			अगर (ret == H_TOO_HARD)
				जाओ invalidate_निकास;

			WARN_ON_ONCE_RM(1);
			kvmppc_rm_clear_tce(vcpu->kvm, stit->tbl, entry);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < npages; ++i, ioba += (1ULL << stt->page_shअगरt))
		kvmppc_rm_tce_put(stt, ioba >> stt->page_shअगरt, tce_value);

invalidate_निकास:
	list_क्रम_each_entry_lockless(stit, &stt->iommu_tables, next)
		iommu_tce_समाप्त_rm(stit->tbl, ioba >> stt->page_shअगरt, npages);

	वापस ret;
पूर्ण

/* This can be called in either भव mode or real mode */
दीर्घ kvmppc_h_get_tce(काष्ठा kvm_vcpu *vcpu, अचिन्हित दीर्घ liobn,
		      अचिन्हित दीर्घ ioba)
अणु
	काष्ठा kvmppc_spapr_tce_table *stt;
	दीर्घ ret;
	अचिन्हित दीर्घ idx;
	काष्ठा page *page;
	u64 *tbl;

	stt = kvmppc_find_table(vcpu->kvm, liobn);
	अगर (!stt)
		वापस H_TOO_HARD;

	ret = kvmppc_ioba_validate(stt, ioba, 1);
	अगर (ret != H_SUCCESS)
		वापस ret;

	idx = (ioba >> stt->page_shअगरt) - stt->offset;
	page = stt->pages[idx / TCES_PER_PAGE];
	अगर (!page) अणु
		vcpu->arch.regs.gpr[4] = 0;
		वापस H_SUCCESS;
	पूर्ण
	tbl = (u64 *)page_address(page);

	vcpu->arch.regs.gpr[4] = tbl[idx % TCES_PER_PAGE];

	वापस H_SUCCESS;
पूर्ण
EXPORT_SYMBOL_GPL(kvmppc_h_get_tce);

#पूर्ण_अगर /* KVM_BOOK3S_HV_POSSIBLE */
