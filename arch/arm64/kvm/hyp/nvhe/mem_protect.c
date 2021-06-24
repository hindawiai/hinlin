<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 Google LLC
 * Author: Quentin Perret <qperret@google.com>
 */

#समावेश <linux/kvm_host.h>
#समावेश <यंत्र/kvm_emulate.h>
#समावेश <यंत्र/kvm_hyp.h>
#समावेश <यंत्र/kvm_mmu.h>
#समावेश <यंत्र/kvm_pgtable.h>
#समावेश <यंत्र/stage2_pgtable.h>

#समावेश <hyp/चयन.h>

#समावेश <nvhe/gfp.h>
#समावेश <nvhe/memory.h>
#समावेश <nvhe/mem_protect.h>
#समावेश <nvhe/mm.h>

#घोषणा KVM_HOST_S2_FLAGS (KVM_PGTABLE_S2_NOFWB | KVM_PGTABLE_S2_IDMAP)

बाह्य अचिन्हित दीर्घ hyp_nr_cpus;
काष्ठा host_kvm host_kvm;

अटल काष्ठा hyp_pool host_s2_mem;
अटल काष्ठा hyp_pool host_s2_dev;

/*
 * Copies of the host's CPU features रेजिस्टरs holding sanitized values.
 */
u64 id_aa64mmfr0_el1_sys_val;
u64 id_aa64mmfr1_el1_sys_val;

अटल स्थिर u8 pkvm_hyp_id = 1;

अटल व्योम *host_s2_zalloc_pages_exact(माप_प्रकार size)
अणु
	वापस hyp_alloc_pages(&host_s2_mem, get_order(size));
पूर्ण

अटल व्योम *host_s2_zalloc_page(व्योम *pool)
अणु
	वापस hyp_alloc_pages(pool, 0);
पूर्ण

अटल पूर्णांक prepare_s2_pools(व्योम *mem_pgt_pool, व्योम *dev_pgt_pool)
अणु
	अचिन्हित दीर्घ nr_pages, pfn;
	पूर्णांक ret;

	pfn = hyp_virt_to_pfn(mem_pgt_pool);
	nr_pages = host_s2_mem_pgtable_pages();
	ret = hyp_pool_init(&host_s2_mem, pfn, nr_pages, 0);
	अगर (ret)
		वापस ret;

	pfn = hyp_virt_to_pfn(dev_pgt_pool);
	nr_pages = host_s2_dev_pgtable_pages();
	ret = hyp_pool_init(&host_s2_dev, pfn, nr_pages, 0);
	अगर (ret)
		वापस ret;

	host_kvm.mm_ops = (काष्ठा kvm_pgtable_mm_ops) अणु
		.zalloc_pages_exact = host_s2_zalloc_pages_exact,
		.zalloc_page = host_s2_zalloc_page,
		.phys_to_virt = hyp_phys_to_virt,
		.virt_to_phys = hyp_virt_to_phys,
		.page_count = hyp_page_count,
		.get_page = hyp_get_page,
		.put_page = hyp_put_page,
	पूर्ण;

	वापस 0;
पूर्ण

अटल व्योम prepare_host_vtcr(व्योम)
अणु
	u32 parange, phys_shअगरt;

	/* The host stage 2 is id-mapped, so use parange क्रम T0SZ */
	parange = kvm_get_parange(id_aa64mmfr0_el1_sys_val);
	phys_shअगरt = id_aa64mmfr0_parange_to_phys_shअगरt(parange);

	host_kvm.arch.vtcr = kvm_get_vtcr(id_aa64mmfr0_el1_sys_val,
					  id_aa64mmfr1_el1_sys_val, phys_shअगरt);
पूर्ण

पूर्णांक kvm_host_prepare_stage2(व्योम *mem_pgt_pool, व्योम *dev_pgt_pool)
अणु
	काष्ठा kvm_s2_mmu *mmu = &host_kvm.arch.mmu;
	पूर्णांक ret;

	prepare_host_vtcr();
	hyp_spin_lock_init(&host_kvm.lock);

	ret = prepare_s2_pools(mem_pgt_pool, dev_pgt_pool);
	अगर (ret)
		वापस ret;

	ret = kvm_pgtable_stage2_init_flags(&host_kvm.pgt, &host_kvm.arch,
					    &host_kvm.mm_ops, KVM_HOST_S2_FLAGS);
	अगर (ret)
		वापस ret;

	mmu->pgd_phys = __hyp_pa(host_kvm.pgt.pgd);
	mmu->arch = &host_kvm.arch;
	mmu->pgt = &host_kvm.pgt;
	mmu->vmid.vmid_gen = 0;
	mmu->vmid.vmid = 0;

	वापस 0;
पूर्ण

पूर्णांक __pkvm_prot_finalize(व्योम)
अणु
	काष्ठा kvm_s2_mmu *mmu = &host_kvm.arch.mmu;
	काष्ठा kvm_nvhe_init_params *params = this_cpu_ptr(&kvm_init_params);

	params->vttbr = kvm_get_vttbr(mmu);
	params->vtcr = host_kvm.arch.vtcr;
	params->hcr_el2 |= HCR_VM;
	kvm_flush_dcache_to_poc(params, माप(*params));

	ग_लिखो_sysreg(params->hcr_el2, hcr_el2);
	__load_stage2(&host_kvm.arch.mmu, host_kvm.arch.vtcr);

	/*
	 * Make sure to have an ISB beक्रमe the TLB मुख्यtenance below but only
	 * when __load_stage2() करोesn't include one alपढ़ोy.
	 */
	यंत्र(ALTERNATIVE("isb", "nop", ARM64_WORKAROUND_SPECULATIVE_AT));

	/* Invalidate stale HCR bits that may be cached in TLBs */
	__tlbi(vmalls12e1);
	dsb(nsh);
	isb();

	वापस 0;
पूर्ण

अटल पूर्णांक host_stage2_unmap_dev_all(व्योम)
अणु
	काष्ठा kvm_pgtable *pgt = &host_kvm.pgt;
	काष्ठा memblock_region *reg;
	u64 addr = 0;
	पूर्णांक i, ret;

	/* Unmap all non-memory regions to recycle the pages */
	क्रम (i = 0; i < hyp_memblock_nr; i++, addr = reg->base + reg->size) अणु
		reg = &hyp_memory[i];
		ret = kvm_pgtable_stage2_unmap(pgt, addr, reg->base - addr);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस kvm_pgtable_stage2_unmap(pgt, addr, BIT(pgt->ia_bits) - addr);
पूर्ण

अटल bool find_mem_range(phys_addr_t addr, काष्ठा kvm_mem_range *range)
अणु
	पूर्णांक cur, left = 0, right = hyp_memblock_nr;
	काष्ठा memblock_region *reg;
	phys_addr_t end;

	range->start = 0;
	range->end = अच_दीर्घ_उच्च;

	/* The list of memblock regions is sorted, binary search it */
	जबतक (left < right) अणु
		cur = (left + right) >> 1;
		reg = &hyp_memory[cur];
		end = reg->base + reg->size;
		अगर (addr < reg->base) अणु
			right = cur;
			range->end = reg->base;
		पूर्ण अन्यथा अगर (addr >= end) अणु
			left = cur + 1;
			range->start = end;
		पूर्ण अन्यथा अणु
			range->start = reg->base;
			range->end = end;
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool range_is_memory(u64 start, u64 end)
अणु
	काष्ठा kvm_mem_range r1, r2;

	अगर (!find_mem_range(start, &r1) || !find_mem_range(end, &r2))
		वापस false;
	अगर (r1.start != r2.start)
		वापस false;

	वापस true;
पूर्ण

अटल अंतरभूत पूर्णांक __host_stage2_idmap(u64 start, u64 end,
				      क्रमागत kvm_pgtable_prot prot,
				      काष्ठा hyp_pool *pool)
अणु
	वापस kvm_pgtable_stage2_map(&host_kvm.pgt, start, end - start, start,
				      prot, pool);
पूर्ण

अटल पूर्णांक host_stage2_idmap(u64 addr)
अणु
	क्रमागत kvm_pgtable_prot prot = KVM_PGTABLE_PROT_R | KVM_PGTABLE_PROT_W;
	काष्ठा kvm_mem_range range;
	bool is_memory = find_mem_range(addr, &range);
	काष्ठा hyp_pool *pool = is_memory ? &host_s2_mem : &host_s2_dev;
	पूर्णांक ret;

	अगर (is_memory)
		prot |= KVM_PGTABLE_PROT_X;

	hyp_spin_lock(&host_kvm.lock);
	ret = kvm_pgtable_stage2_find_range(&host_kvm.pgt, addr, prot, &range);
	अगर (ret)
		जाओ unlock;

	ret = __host_stage2_idmap(range.start, range.end, prot, pool);
	अगर (is_memory || ret != -ENOMEM)
		जाओ unlock;

	/*
	 * host_s2_mem has been provided with enough pages to cover all of
	 * memory with page granularity, so we should never hit the ENOMEM हाल.
	 * However, it is dअगरficult to know how much of the MMIO range we will
	 * need to cover upfront, so we may need to 'recycle' the pages अगर we
	 * run out.
	 */
	ret = host_stage2_unmap_dev_all();
	अगर (ret)
		जाओ unlock;

	ret = __host_stage2_idmap(range.start, range.end, prot, pool);

unlock:
	hyp_spin_unlock(&host_kvm.lock);

	वापस ret;
पूर्ण

पूर्णांक __pkvm_mark_hyp(phys_addr_t start, phys_addr_t end)
अणु
	पूर्णांक ret;

	/*
	 * host_stage2_unmap_dev_all() currently relies on MMIO mappings being
	 * non-persistent, so करोn't allow changing page ownership in MMIO range.
	 */
	अगर (!range_is_memory(start, end))
		वापस -EINVAL;

	hyp_spin_lock(&host_kvm.lock);
	ret = kvm_pgtable_stage2_set_owner(&host_kvm.pgt, start, end - start,
					   &host_s2_mem, pkvm_hyp_id);
	hyp_spin_unlock(&host_kvm.lock);

	वापस ret != -EAGAIN ? ret : 0;
पूर्ण

व्योम handle_host_mem_पात(काष्ठा kvm_cpu_context *host_ctxt)
अणु
	काष्ठा kvm_vcpu_fault_info fault;
	u64 esr, addr;
	पूर्णांक ret = 0;

	esr = पढ़ो_sysreg_el2(SYS_ESR);
	BUG_ON(!__get_fault_info(esr, &fault));

	addr = (fault.hpfar_el2 & HPFAR_MASK) << 8;
	ret = host_stage2_idmap(addr);
	BUG_ON(ret && ret != -EAGAIN);
पूर्ण
