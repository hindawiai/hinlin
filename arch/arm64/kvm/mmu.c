<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 - Virtual Open Systems and Columbia University
 * Author: Christoffer Dall <c.dall@भवखोलोप्रणालीs.com>
 */

#समावेश <linux/mman.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/पन.स>
#समावेश <linux/hugetlb.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <trace/events/kvm.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/kvm_arm.h>
#समावेश <यंत्र/kvm_mmu.h>
#समावेश <यंत्र/kvm_pgtable.h>
#समावेश <यंत्र/kvm_ras.h>
#समावेश <यंत्र/kvm_यंत्र.h>
#समावेश <यंत्र/kvm_emulate.h>
#समावेश <यंत्र/virt.h>

#समावेश "trace.h"

अटल काष्ठा kvm_pgtable *hyp_pgtable;
अटल DEFINE_MUTEX(kvm_hyp_pgd_mutex);

अटल अचिन्हित दीर्घ hyp_idmap_start;
अटल अचिन्हित दीर्घ hyp_idmap_end;
अटल phys_addr_t hyp_idmap_vector;

अटल अचिन्हित दीर्घ io_map_base;


/*
 * Release kvm_mmu_lock periodically अगर the memory region is large. Otherwise,
 * we may see kernel panics with CONFIG_DETECT_HUNG_TASK,
 * CONFIG_LOCKUP_DETECTOR, CONFIG_LOCKDEP. Additionally, holding the lock too
 * दीर्घ will also starve other vCPUs. We have to also make sure that the page
 * tables are not मुक्तd जबतक we released the lock.
 */
अटल पूर्णांक stage2_apply_range(काष्ठा kvm *kvm, phys_addr_t addr,
			      phys_addr_t end,
			      पूर्णांक (*fn)(काष्ठा kvm_pgtable *, u64, u64),
			      bool resched)
अणु
	पूर्णांक ret;
	u64 next;

	करो अणु
		काष्ठा kvm_pgtable *pgt = kvm->arch.mmu.pgt;
		अगर (!pgt)
			वापस -EINVAL;

		next = stage2_pgd_addr_end(kvm, addr, end);
		ret = fn(pgt, addr, next - addr);
		अगर (ret)
			अवरोध;

		अगर (resched && next != end)
			cond_resched_lock(&kvm->mmu_lock);
	पूर्ण जबतक (addr = next, addr != end);

	वापस ret;
पूर्ण

#घोषणा stage2_apply_range_resched(kvm, addr, end, fn)			\
	stage2_apply_range(kvm, addr, end, fn, true)

अटल bool memslot_is_logging(काष्ठा kvm_memory_slot *memslot)
अणु
	वापस memslot->dirty_biपंचांगap && !(memslot->flags & KVM_MEM_READONLY);
पूर्ण

/**
 * kvm_flush_remote_tlbs() - flush all VM TLB entries क्रम v7/8
 * @kvm:	poपूर्णांकer to kvm काष्ठाure.
 *
 * Interface to HYP function to flush all VM TLB entries
 */
व्योम kvm_flush_remote_tlbs(काष्ठा kvm *kvm)
अणु
	kvm_call_hyp(__kvm_tlb_flush_vmid, &kvm->arch.mmu);
पूर्ण

अटल bool kvm_is_device_pfn(अचिन्हित दीर्घ pfn)
अणु
	वापस !pfn_valid(pfn);
पूर्ण

अटल व्योम *stage2_memcache_zalloc_page(व्योम *arg)
अणु
	काष्ठा kvm_mmu_memory_cache *mc = arg;

	/* Allocated with __GFP_ZERO, so no need to zero */
	वापस kvm_mmu_memory_cache_alloc(mc);
पूर्ण

अटल व्योम *kvm_host_zalloc_pages_exact(माप_प्रकार size)
अणु
	वापस alloc_pages_exact(size, GFP_KERNEL_ACCOUNT | __GFP_ZERO);
पूर्ण

अटल व्योम kvm_host_get_page(व्योम *addr)
अणु
	get_page(virt_to_page(addr));
पूर्ण

अटल व्योम kvm_host_put_page(व्योम *addr)
अणु
	put_page(virt_to_page(addr));
पूर्ण

अटल पूर्णांक kvm_host_page_count(व्योम *addr)
अणु
	वापस page_count(virt_to_page(addr));
पूर्ण

अटल phys_addr_t kvm_host_pa(व्योम *addr)
अणु
	वापस __pa(addr);
पूर्ण

अटल व्योम *kvm_host_va(phys_addr_t phys)
अणु
	वापस __va(phys);
पूर्ण

/*
 * Unmapping vs dcache management:
 *
 * If a guest maps certain memory pages as uncached, all ग_लिखोs will
 * bypass the data cache and go directly to RAM.  However, the CPUs
 * can still speculate पढ़ोs (not ग_लिखोs) and fill cache lines with
 * data.
 *
 * Those cache lines will be *clean* cache lines though, so a
 * clean+invalidate operation is equivalent to an invalidate
 * operation, because no cache lines are marked dirty.
 *
 * Those clean cache lines could be filled prior to an uncached ग_लिखो
 * by the guest, and the cache coherent IO subप्रणाली would thereक्रमe
 * end up writing old data to disk.
 *
 * This is why right after unmapping a page/section and invalidating
 * the corresponding TLBs, we flush to make sure the IO subप्रणाली will
 * never hit in the cache.
 *
 * This is all aव्योमed on प्रणालीs that have ARM64_HAS_STAGE2_FWB, as
 * we then fully enक्रमce cacheability of RAM, no matter what the guest
 * करोes.
 */
/**
 * unmap_stage2_range -- Clear stage2 page table entries to unmap a range
 * @mmu:   The KVM stage-2 MMU poपूर्णांकer
 * @start: The पूर्णांकermediate physical base address of the range to unmap
 * @size:  The size of the area to unmap
 * @may_block: Whether or not we are permitted to block
 *
 * Clear a range of stage-2 mappings, lowering the various ref-counts.  Must
 * be called जबतक holding mmu_lock (unless क्रम मुक्तing the stage2 pgd beक्रमe
 * destroying the VM), otherwise another faulting VCPU may come in and mess
 * with things behind our backs.
 */
अटल व्योम __unmap_stage2_range(काष्ठा kvm_s2_mmu *mmu, phys_addr_t start, u64 size,
				 bool may_block)
अणु
	काष्ठा kvm *kvm = kvm_s2_mmu_to_kvm(mmu);
	phys_addr_t end = start + size;

	निश्चित_spin_locked(&kvm->mmu_lock);
	WARN_ON(size & ~PAGE_MASK);
	WARN_ON(stage2_apply_range(kvm, start, end, kvm_pgtable_stage2_unmap,
				   may_block));
पूर्ण

अटल व्योम unmap_stage2_range(काष्ठा kvm_s2_mmu *mmu, phys_addr_t start, u64 size)
अणु
	__unmap_stage2_range(mmu, start, size, true);
पूर्ण

अटल व्योम stage2_flush_memslot(काष्ठा kvm *kvm,
				 काष्ठा kvm_memory_slot *memslot)
अणु
	phys_addr_t addr = memslot->base_gfn << PAGE_SHIFT;
	phys_addr_t end = addr + PAGE_SIZE * memslot->npages;

	stage2_apply_range_resched(kvm, addr, end, kvm_pgtable_stage2_flush);
पूर्ण

/**
 * stage2_flush_vm - Invalidate cache क्रम pages mapped in stage 2
 * @kvm: The काष्ठा kvm poपूर्णांकer
 *
 * Go through the stage 2 page tables and invalidate any cache lines
 * backing memory alपढ़ोy mapped to the VM.
 */
अटल व्योम stage2_flush_vm(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_memslots *slots;
	काष्ठा kvm_memory_slot *memslot;
	पूर्णांक idx;

	idx = srcu_पढ़ो_lock(&kvm->srcu);
	spin_lock(&kvm->mmu_lock);

	slots = kvm_memslots(kvm);
	kvm_क्रम_each_memslot(memslot, slots)
		stage2_flush_memslot(kvm, memslot);

	spin_unlock(&kvm->mmu_lock);
	srcu_पढ़ो_unlock(&kvm->srcu, idx);
पूर्ण

/**
 * मुक्त_hyp_pgds - मुक्त Hyp-mode page tables
 */
व्योम मुक्त_hyp_pgds(व्योम)
अणु
	mutex_lock(&kvm_hyp_pgd_mutex);
	अगर (hyp_pgtable) अणु
		kvm_pgtable_hyp_destroy(hyp_pgtable);
		kमुक्त(hyp_pgtable);
		hyp_pgtable = शून्य;
	पूर्ण
	mutex_unlock(&kvm_hyp_pgd_mutex);
पूर्ण

अटल bool kvm_host_owns_hyp_mappings(व्योम)
अणु
	अगर (अटल_branch_likely(&kvm_रक्षित_mode_initialized))
		वापस false;

	/*
	 * This can happen at boot समय when __create_hyp_mappings() is called
	 * after the hyp protection has been enabled, but the अटल key has
	 * not been flipped yet.
	 */
	अगर (!hyp_pgtable && is_रक्षित_kvm_enabled())
		वापस false;

	WARN_ON(!hyp_pgtable);

	वापस true;
पूर्ण

अटल पूर्णांक __create_hyp_mappings(अचिन्हित दीर्घ start, अचिन्हित दीर्घ size,
				 अचिन्हित दीर्घ phys, क्रमागत kvm_pgtable_prot prot)
अणु
	पूर्णांक err;

	अगर (!kvm_host_owns_hyp_mappings()) अणु
		वापस kvm_call_hyp_nvhe(__pkvm_create_mappings,
					 start, size, phys, prot);
	पूर्ण

	mutex_lock(&kvm_hyp_pgd_mutex);
	err = kvm_pgtable_hyp_map(hyp_pgtable, start, size, phys, prot);
	mutex_unlock(&kvm_hyp_pgd_mutex);

	वापस err;
पूर्ण

अटल phys_addr_t kvm_kaddr_to_phys(व्योम *kaddr)
अणु
	अगर (!is_vदो_स्मृति_addr(kaddr)) अणु
		BUG_ON(!virt_addr_valid(kaddr));
		वापस __pa(kaddr);
	पूर्ण अन्यथा अणु
		वापस page_to_phys(vदो_स्मृति_to_page(kaddr)) +
		       offset_in_page(kaddr);
	पूर्ण
पूर्ण

/**
 * create_hyp_mappings - duplicate a kernel भव address range in Hyp mode
 * @from:	The भव kernel start address of the range
 * @to:		The भव kernel end address of the range (exclusive)
 * @prot:	The protection to be applied to this range
 *
 * The same भव address as the kernel भव address is also used
 * in Hyp-mode mapping (modulo HYP_PAGE_OFFSET) to the same underlying
 * physical pages.
 */
पूर्णांक create_hyp_mappings(व्योम *from, व्योम *to, क्रमागत kvm_pgtable_prot prot)
अणु
	phys_addr_t phys_addr;
	अचिन्हित दीर्घ virt_addr;
	अचिन्हित दीर्घ start = kern_hyp_va((अचिन्हित दीर्घ)from);
	अचिन्हित दीर्घ end = kern_hyp_va((अचिन्हित दीर्घ)to);

	अगर (is_kernel_in_hyp_mode())
		वापस 0;

	start = start & PAGE_MASK;
	end = PAGE_ALIGN(end);

	क्रम (virt_addr = start; virt_addr < end; virt_addr += PAGE_SIZE) अणु
		पूर्णांक err;

		phys_addr = kvm_kaddr_to_phys(from + virt_addr - start);
		err = __create_hyp_mappings(virt_addr, PAGE_SIZE, phys_addr,
					    prot);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __create_hyp_निजी_mapping(phys_addr_t phys_addr, माप_प्रकार size,
					अचिन्हित दीर्घ *haddr,
					क्रमागत kvm_pgtable_prot prot)
अणु
	अचिन्हित दीर्घ base;
	पूर्णांक ret = 0;

	अगर (!kvm_host_owns_hyp_mappings()) अणु
		base = kvm_call_hyp_nvhe(__pkvm_create_निजी_mapping,
					 phys_addr, size, prot);
		अगर (IS_ERR_OR_शून्य((व्योम *)base))
			वापस PTR_ERR((व्योम *)base);
		*haddr = base;

		वापस 0;
	पूर्ण

	mutex_lock(&kvm_hyp_pgd_mutex);

	/*
	 * This assumes that we have enough space below the idmap
	 * page to allocate our VAs. If not, the check below will
	 * kick. A potential alternative would be to detect that
	 * overflow and चयन to an allocation above the idmap.
	 *
	 * The allocated size is always a multiple of PAGE_SIZE.
	 */
	size = PAGE_ALIGN(size + offset_in_page(phys_addr));
	base = io_map_base - size;

	/*
	 * Verअगरy that BIT(VA_BITS - 1) hasn't been flipped by
	 * allocating the new area, as it would indicate we've
	 * overflowed the idmap/IO address range.
	 */
	अगर ((base ^ io_map_base) & BIT(VA_BITS - 1))
		ret = -ENOMEM;
	अन्यथा
		io_map_base = base;

	mutex_unlock(&kvm_hyp_pgd_mutex);

	अगर (ret)
		जाओ out;

	ret = __create_hyp_mappings(base, size, phys_addr, prot);
	अगर (ret)
		जाओ out;

	*haddr = base + offset_in_page(phys_addr);
out:
	वापस ret;
पूर्ण

/**
 * create_hyp_io_mappings - Map IO पूर्णांकo both kernel and HYP
 * @phys_addr:	The physical start address which माला_लो mapped
 * @size:	Size of the region being mapped
 * @kaddr:	Kernel VA क्रम this mapping
 * @haddr:	HYP VA क्रम this mapping
 */
पूर्णांक create_hyp_io_mappings(phys_addr_t phys_addr, माप_प्रकार size,
			   व्योम __iomem **kaddr,
			   व्योम __iomem **haddr)
अणु
	अचिन्हित दीर्घ addr;
	पूर्णांक ret;

	*kaddr = ioremap(phys_addr, size);
	अगर (!*kaddr)
		वापस -ENOMEM;

	अगर (is_kernel_in_hyp_mode()) अणु
		*haddr = *kaddr;
		वापस 0;
	पूर्ण

	ret = __create_hyp_निजी_mapping(phys_addr, size,
					   &addr, PAGE_HYP_DEVICE);
	अगर (ret) अणु
		iounmap(*kaddr);
		*kaddr = शून्य;
		*haddr = शून्य;
		वापस ret;
	पूर्ण

	*haddr = (व्योम __iomem *)addr;
	वापस 0;
पूर्ण

/**
 * create_hyp_exec_mappings - Map an executable range पूर्णांकo HYP
 * @phys_addr:	The physical start address which माला_लो mapped
 * @size:	Size of the region being mapped
 * @haddr:	HYP VA क्रम this mapping
 */
पूर्णांक create_hyp_exec_mappings(phys_addr_t phys_addr, माप_प्रकार size,
			     व्योम **haddr)
अणु
	अचिन्हित दीर्घ addr;
	पूर्णांक ret;

	BUG_ON(is_kernel_in_hyp_mode());

	ret = __create_hyp_निजी_mapping(phys_addr, size,
					   &addr, PAGE_HYP_EXEC);
	अगर (ret) अणु
		*haddr = शून्य;
		वापस ret;
	पूर्ण

	*haddr = (व्योम *)addr;
	वापस 0;
पूर्ण

अटल काष्ठा kvm_pgtable_mm_ops kvm_s2_mm_ops = अणु
	.zalloc_page		= stage2_memcache_zalloc_page,
	.zalloc_pages_exact	= kvm_host_zalloc_pages_exact,
	.मुक्त_pages_exact	= मुक्त_pages_exact,
	.get_page		= kvm_host_get_page,
	.put_page		= kvm_host_put_page,
	.page_count		= kvm_host_page_count,
	.phys_to_virt		= kvm_host_va,
	.virt_to_phys		= kvm_host_pa,
पूर्ण;

/**
 * kvm_init_stage2_mmu - Initialise a S2 MMU strucrure
 * @kvm:	The poपूर्णांकer to the KVM काष्ठाure
 * @mmu:	The poपूर्णांकer to the s2 MMU काष्ठाure
 *
 * Allocates only the stage-2 HW PGD level table(s).
 * Note we करोn't need locking here as this is only called when the VM is
 * created, which can only be करोne once.
 */
पूर्णांक kvm_init_stage2_mmu(काष्ठा kvm *kvm, काष्ठा kvm_s2_mmu *mmu)
अणु
	पूर्णांक cpu, err;
	काष्ठा kvm_pgtable *pgt;

	अगर (mmu->pgt != शून्य) अणु
		kvm_err("kvm_arch already initialized?\n");
		वापस -EINVAL;
	पूर्ण

	pgt = kzalloc(माप(*pgt), GFP_KERNEL);
	अगर (!pgt)
		वापस -ENOMEM;

	err = kvm_pgtable_stage2_init(pgt, &kvm->arch, &kvm_s2_mm_ops);
	अगर (err)
		जाओ out_मुक्त_pgtable;

	mmu->last_vcpu_ran = alloc_percpu(typeof(*mmu->last_vcpu_ran));
	अगर (!mmu->last_vcpu_ran) अणु
		err = -ENOMEM;
		जाओ out_destroy_pgtable;
	पूर्ण

	क्रम_each_possible_cpu(cpu)
		*per_cpu_ptr(mmu->last_vcpu_ran, cpu) = -1;

	mmu->arch = &kvm->arch;
	mmu->pgt = pgt;
	mmu->pgd_phys = __pa(pgt->pgd);
	mmu->vmid.vmid_gen = 0;
	वापस 0;

out_destroy_pgtable:
	kvm_pgtable_stage2_destroy(pgt);
out_मुक्त_pgtable:
	kमुक्त(pgt);
	वापस err;
पूर्ण

अटल व्योम stage2_unmap_memslot(काष्ठा kvm *kvm,
				 काष्ठा kvm_memory_slot *memslot)
अणु
	hva_t hva = memslot->userspace_addr;
	phys_addr_t addr = memslot->base_gfn << PAGE_SHIFT;
	phys_addr_t size = PAGE_SIZE * memslot->npages;
	hva_t reg_end = hva + size;

	/*
	 * A memory region could potentially cover multiple VMAs, and any holes
	 * between them, so iterate over all of them to find out अगर we should
	 * unmap any of them.
	 *
	 *     +--------------------------------------------+
	 * +---------------+----------------+   +----------------+
	 * |   : VMA 1     |      VMA 2     |   |    VMA 3  :    |
	 * +---------------+----------------+   +----------------+
	 *     |               memory region                |
	 *     +--------------------------------------------+
	 */
	करो अणु
		काष्ठा vm_area_काष्ठा *vma;
		hva_t vm_start, vm_end;

		vma = find_vma_पूर्णांकersection(current->mm, hva, reg_end);
		अगर (!vma)
			अवरोध;

		/*
		 * Take the पूर्णांकersection of this VMA with the memory region
		 */
		vm_start = max(hva, vma->vm_start);
		vm_end = min(reg_end, vma->vm_end);

		अगर (!(vma->vm_flags & VM_PFNMAP)) अणु
			gpa_t gpa = addr + (vm_start - memslot->userspace_addr);
			unmap_stage2_range(&kvm->arch.mmu, gpa, vm_end - vm_start);
		पूर्ण
		hva = vm_end;
	पूर्ण जबतक (hva < reg_end);
पूर्ण

/**
 * stage2_unmap_vm - Unmap Stage-2 RAM mappings
 * @kvm: The काष्ठा kvm poपूर्णांकer
 *
 * Go through the memregions and unmap any regular RAM
 * backing memory alपढ़ोy mapped to the VM.
 */
व्योम stage2_unmap_vm(काष्ठा kvm *kvm)
अणु
	काष्ठा kvm_memslots *slots;
	काष्ठा kvm_memory_slot *memslot;
	पूर्णांक idx;

	idx = srcu_पढ़ो_lock(&kvm->srcu);
	mmap_पढ़ो_lock(current->mm);
	spin_lock(&kvm->mmu_lock);

	slots = kvm_memslots(kvm);
	kvm_क्रम_each_memslot(memslot, slots)
		stage2_unmap_memslot(kvm, memslot);

	spin_unlock(&kvm->mmu_lock);
	mmap_पढ़ो_unlock(current->mm);
	srcu_पढ़ो_unlock(&kvm->srcu, idx);
पूर्ण

व्योम kvm_मुक्त_stage2_pgd(काष्ठा kvm_s2_mmu *mmu)
अणु
	काष्ठा kvm *kvm = kvm_s2_mmu_to_kvm(mmu);
	काष्ठा kvm_pgtable *pgt = शून्य;

	spin_lock(&kvm->mmu_lock);
	pgt = mmu->pgt;
	अगर (pgt) अणु
		mmu->pgd_phys = 0;
		mmu->pgt = शून्य;
		मुक्त_percpu(mmu->last_vcpu_ran);
	पूर्ण
	spin_unlock(&kvm->mmu_lock);

	अगर (pgt) अणु
		kvm_pgtable_stage2_destroy(pgt);
		kमुक्त(pgt);
	पूर्ण
पूर्ण

/**
 * kvm_phys_addr_ioremap - map a device range to guest IPA
 *
 * @kvm:	The KVM poपूर्णांकer
 * @guest_ipa:	The IPA at which to insert the mapping
 * @pa:		The physical address of the device
 * @size:	The size of the mapping
 * @writable:   Whether or not to create a writable mapping
 */
पूर्णांक kvm_phys_addr_ioremap(काष्ठा kvm *kvm, phys_addr_t guest_ipa,
			  phys_addr_t pa, अचिन्हित दीर्घ size, bool writable)
अणु
	phys_addr_t addr;
	पूर्णांक ret = 0;
	काष्ठा kvm_mmu_memory_cache cache = अणु 0, __GFP_ZERO, शून्य, पूर्ण;
	काष्ठा kvm_pgtable *pgt = kvm->arch.mmu.pgt;
	क्रमागत kvm_pgtable_prot prot = KVM_PGTABLE_PROT_DEVICE |
				     KVM_PGTABLE_PROT_R |
				     (writable ? KVM_PGTABLE_PROT_W : 0);

	size += offset_in_page(guest_ipa);
	guest_ipa &= PAGE_MASK;

	क्रम (addr = guest_ipa; addr < guest_ipa + size; addr += PAGE_SIZE) अणु
		ret = kvm_mmu_topup_memory_cache(&cache,
						 kvm_mmu_cache_min_pages(kvm));
		अगर (ret)
			अवरोध;

		spin_lock(&kvm->mmu_lock);
		ret = kvm_pgtable_stage2_map(pgt, addr, PAGE_SIZE, pa, prot,
					     &cache);
		spin_unlock(&kvm->mmu_lock);
		अगर (ret)
			अवरोध;

		pa += PAGE_SIZE;
	पूर्ण

	kvm_mmu_मुक्त_memory_cache(&cache);
	वापस ret;
पूर्ण

/**
 * stage2_wp_range() - ग_लिखो protect stage2 memory region range
 * @mmu:        The KVM stage-2 MMU poपूर्णांकer
 * @addr:	Start address of range
 * @end:	End address of range
 */
अटल व्योम stage2_wp_range(काष्ठा kvm_s2_mmu *mmu, phys_addr_t addr, phys_addr_t end)
अणु
	काष्ठा kvm *kvm = kvm_s2_mmu_to_kvm(mmu);
	stage2_apply_range_resched(kvm, addr, end, kvm_pgtable_stage2_wrprotect);
पूर्ण

/**
 * kvm_mmu_wp_memory_region() - ग_लिखो protect stage 2 entries क्रम memory slot
 * @kvm:	The KVM poपूर्णांकer
 * @slot:	The memory slot to ग_लिखो protect
 *
 * Called to start logging dirty pages after memory region
 * KVM_MEM_LOG_सूचीTY_PAGES operation is called. After this function वापसs
 * all present PUD, PMD and PTEs are ग_लिखो रक्षित in the memory region.
 * Afterwards पढ़ो of dirty page log can be called.
 *
 * Acquires kvm_mmu_lock. Called with kvm->slots_lock mutex acquired,
 * serializing operations क्रम VM memory regions.
 */
अटल व्योम kvm_mmu_wp_memory_region(काष्ठा kvm *kvm, पूर्णांक slot)
अणु
	काष्ठा kvm_memslots *slots = kvm_memslots(kvm);
	काष्ठा kvm_memory_slot *memslot = id_to_memslot(slots, slot);
	phys_addr_t start, end;

	अगर (WARN_ON_ONCE(!memslot))
		वापस;

	start = memslot->base_gfn << PAGE_SHIFT;
	end = (memslot->base_gfn + memslot->npages) << PAGE_SHIFT;

	spin_lock(&kvm->mmu_lock);
	stage2_wp_range(&kvm->arch.mmu, start, end);
	spin_unlock(&kvm->mmu_lock);
	kvm_flush_remote_tlbs(kvm);
पूर्ण

/**
 * kvm_mmu_ग_लिखो_protect_pt_masked() - ग_लिखो protect dirty pages
 * @kvm:	The KVM poपूर्णांकer
 * @slot:	The memory slot associated with mask
 * @gfn_offset:	The gfn offset in memory slot
 * @mask:	The mask of dirty pages at offset 'gfn_offset' in this memory
 *		slot to be ग_लिखो रक्षित
 *
 * Walks bits set in mask ग_लिखो protects the associated pte's. Caller must
 * acquire kvm_mmu_lock.
 */
अटल व्योम kvm_mmu_ग_लिखो_protect_pt_masked(काष्ठा kvm *kvm,
		काष्ठा kvm_memory_slot *slot,
		gfn_t gfn_offset, अचिन्हित दीर्घ mask)
अणु
	phys_addr_t base_gfn = slot->base_gfn + gfn_offset;
	phys_addr_t start = (base_gfn +  __ffs(mask)) << PAGE_SHIFT;
	phys_addr_t end = (base_gfn + __fls(mask) + 1) << PAGE_SHIFT;

	stage2_wp_range(&kvm->arch.mmu, start, end);
पूर्ण

/*
 * kvm_arch_mmu_enable_log_dirty_pt_masked - enable dirty logging क्रम selected
 * dirty pages.
 *
 * It calls kvm_mmu_ग_लिखो_protect_pt_masked to ग_लिखो protect selected pages to
 * enable dirty logging क्रम them.
 */
व्योम kvm_arch_mmu_enable_log_dirty_pt_masked(काष्ठा kvm *kvm,
		काष्ठा kvm_memory_slot *slot,
		gfn_t gfn_offset, अचिन्हित दीर्घ mask)
अणु
	kvm_mmu_ग_लिखो_protect_pt_masked(kvm, slot, gfn_offset, mask);
पूर्ण

अटल व्योम clean_dcache_guest_page(kvm_pfn_t pfn, अचिन्हित दीर्घ size)
अणु
	__clean_dcache_guest_page(pfn, size);
पूर्ण

अटल व्योम invalidate_icache_guest_page(kvm_pfn_t pfn, अचिन्हित दीर्घ size)
अणु
	__invalidate_icache_guest_page(pfn, size);
पूर्ण

अटल व्योम kvm_send_hwpoison_संकेत(अचिन्हित दीर्घ address, लघु lsb)
अणु
	send_sig_mceerr(BUS_MCEERR_AR, (व्योम __user *)address, lsb, current);
पूर्ण

अटल bool fault_supports_stage2_huge_mapping(काष्ठा kvm_memory_slot *memslot,
					       अचिन्हित दीर्घ hva,
					       अचिन्हित दीर्घ map_size)
अणु
	gpa_t gpa_start;
	hva_t uaddr_start, uaddr_end;
	माप_प्रकार size;

	/* The memslot and the VMA are guaranteed to be aligned to PAGE_SIZE */
	अगर (map_size == PAGE_SIZE)
		वापस true;

	size = memslot->npages * PAGE_SIZE;

	gpa_start = memslot->base_gfn << PAGE_SHIFT;

	uaddr_start = memslot->userspace_addr;
	uaddr_end = uaddr_start + size;

	/*
	 * Pages beदीर्घing to memslots that करोn't have the same alignment
	 * within a PMD/PUD क्रम userspace and IPA cannot be mapped with stage-2
	 * PMD/PUD entries, because we'll end up mapping the wrong pages.
	 *
	 * Consider a layout like the following:
	 *
	 *    memslot->userspace_addr:
	 *    +-----+--------------------+--------------------+---+
	 *    |abcde|fgh  Stage-1 block  |    Stage-1 block tv|xyz|
	 *    +-----+--------------------+--------------------+---+
	 *
	 *    memslot->base_gfn << PAGE_SHIFT:
	 *      +---+--------------------+--------------------+-----+
	 *      |abc|def  Stage-2 block  |    Stage-2 block   |tvxyz|
	 *      +---+--------------------+--------------------+-----+
	 *
	 * If we create those stage-2 blocks, we'll end up with this incorrect
	 * mapping:
	 *   d -> f
	 *   e -> g
	 *   f -> h
	 */
	अगर ((gpa_start & (map_size - 1)) != (uaddr_start & (map_size - 1)))
		वापस false;

	/*
	 * Next, let's make sure we're not trying to map anything not covered
	 * by the memslot. This means we have to prohibit block size mappings
	 * क्रम the beginning and end of a non-block aligned and non-block sized
	 * memory slot (illustrated by the head and tail parts of the
	 * userspace view above containing pages 'abcde' and 'xyz',
	 * respectively).
	 *
	 * Note that it करोesn't matter अगर we करो the check using the
	 * userspace_addr or the base_gfn, as both are equally aligned (per
	 * the check above) and equally sized.
	 */
	वापस (hva & ~(map_size - 1)) >= uaddr_start &&
	       (hva & ~(map_size - 1)) + map_size <= uaddr_end;
पूर्ण

/*
 * Check अगर the given hva is backed by a transparent huge page (THP) and
 * whether it can be mapped using block mapping in stage2. If so, adjust
 * the stage2 PFN and IPA accordingly. Only PMD_SIZE THPs are currently
 * supported. This will need to be updated to support other THP sizes.
 *
 * Returns the size of the mapping.
 */
अटल अचिन्हित दीर्घ
transparent_hugepage_adjust(काष्ठा kvm_memory_slot *memslot,
			    अचिन्हित दीर्घ hva, kvm_pfn_t *pfnp,
			    phys_addr_t *ipap)
अणु
	kvm_pfn_t pfn = *pfnp;

	/*
	 * Make sure the adjusपंचांगent is करोne only क्रम THP pages. Also make
	 * sure that the HVA and IPA are sufficiently aligned and that the
	 * block map is contained within the memslot.
	 */
	अगर (kvm_is_transparent_hugepage(pfn) &&
	    fault_supports_stage2_huge_mapping(memslot, hva, PMD_SIZE)) अणु
		/*
		 * The address we faulted on is backed by a transparent huge
		 * page.  However, because we map the compound huge page and
		 * not the inभागidual tail page, we need to transfer the
		 * refcount to the head page.  We have to be careful that the
		 * THP करोesn't start to split जबतक we are adjusting the
		 * refcounts.
		 *
		 * We are sure this करोesn't happen, because mmu_notअगरier_retry
		 * was successful and we are holding the mmu_lock, so अगर this
		 * THP is trying to split, it will be blocked in the mmu
		 * notअगरier beक्रमe touching any of the pages, specअगरically
		 * beक्रमe being able to call __split_huge_page_refcount().
		 *
		 * We can thereक्रमe safely transfer the refcount from PG_tail
		 * to PG_head and चयन the pfn from a tail page to the head
		 * page accordingly.
		 */
		*ipap &= PMD_MASK;
		kvm_release_pfn_clean(pfn);
		pfn &= ~(PTRS_PER_PMD - 1);
		kvm_get_pfn(pfn);
		*pfnp = pfn;

		वापस PMD_SIZE;
	पूर्ण

	/* Use page mapping अगर we cannot use block mapping. */
	वापस PAGE_SIZE;
पूर्ण

अटल पूर्णांक user_mem_पात(काष्ठा kvm_vcpu *vcpu, phys_addr_t fault_ipa,
			  काष्ठा kvm_memory_slot *memslot, अचिन्हित दीर्घ hva,
			  अचिन्हित दीर्घ fault_status)
अणु
	पूर्णांक ret = 0;
	bool ग_लिखो_fault, writable, क्रमce_pte = false;
	bool exec_fault;
	bool device = false;
	अचिन्हित दीर्घ mmu_seq;
	काष्ठा kvm *kvm = vcpu->kvm;
	काष्ठा kvm_mmu_memory_cache *memcache = &vcpu->arch.mmu_page_cache;
	काष्ठा vm_area_काष्ठा *vma;
	लघु vma_shअगरt;
	gfn_t gfn;
	kvm_pfn_t pfn;
	bool logging_active = memslot_is_logging(memslot);
	अचिन्हित दीर्घ fault_level = kvm_vcpu_trap_get_fault_level(vcpu);
	अचिन्हित दीर्घ vma_pagesize, fault_granule;
	क्रमागत kvm_pgtable_prot prot = KVM_PGTABLE_PROT_R;
	काष्ठा kvm_pgtable *pgt;

	fault_granule = 1UL << ARM64_HW_PGTABLE_LEVEL_SHIFT(fault_level);
	ग_लिखो_fault = kvm_is_ग_लिखो_fault(vcpu);
	exec_fault = kvm_vcpu_trap_is_exec_fault(vcpu);
	VM_BUG_ON(ग_लिखो_fault && exec_fault);

	अगर (fault_status == FSC_PERM && !ग_लिखो_fault && !exec_fault) अणु
		kvm_err("Unexpected L2 read permission error\n");
		वापस -EFAULT;
	पूर्ण

	/* Let's check अगर we will get back a huge page backed by hugetlbfs */
	mmap_पढ़ो_lock(current->mm);
	vma = find_vma_पूर्णांकersection(current->mm, hva, hva + 1);
	अगर (unlikely(!vma)) अणु
		kvm_err("Failed to find VMA for hva 0x%lx\n", hva);
		mmap_पढ़ो_unlock(current->mm);
		वापस -EFAULT;
	पूर्ण

	अगर (is_vm_hugetlb_page(vma))
		vma_shअगरt = huge_page_shअगरt(hstate_vma(vma));
	अन्यथा
		vma_shअगरt = PAGE_SHIFT;

	अगर (logging_active ||
	    (vma->vm_flags & VM_PFNMAP)) अणु
		क्रमce_pte = true;
		vma_shअगरt = PAGE_SHIFT;
	पूर्ण

	चयन (vma_shअगरt) अणु
#अगर_अघोषित __PAGETABLE_PMD_FOLDED
	हाल PUD_SHIFT:
		अगर (fault_supports_stage2_huge_mapping(memslot, hva, PUD_SIZE))
			अवरोध;
		fallthrough;
#पूर्ण_अगर
	हाल CONT_PMD_SHIFT:
		vma_shअगरt = PMD_SHIFT;
		fallthrough;
	हाल PMD_SHIFT:
		अगर (fault_supports_stage2_huge_mapping(memslot, hva, PMD_SIZE))
			अवरोध;
		fallthrough;
	हाल CONT_PTE_SHIFT:
		vma_shअगरt = PAGE_SHIFT;
		क्रमce_pte = true;
		fallthrough;
	हाल PAGE_SHIFT:
		अवरोध;
	शेष:
		WARN_ONCE(1, "Unknown vma_shift %d", vma_shअगरt);
	पूर्ण

	vma_pagesize = 1UL << vma_shअगरt;
	अगर (vma_pagesize == PMD_SIZE || vma_pagesize == PUD_SIZE)
		fault_ipa &= ~(vma_pagesize - 1);

	gfn = fault_ipa >> PAGE_SHIFT;
	mmap_पढ़ो_unlock(current->mm);

	/*
	 * Permission faults just need to update the existing leaf entry,
	 * and so normally करोn't require allocations from the memcache. The
	 * only exception to this is when dirty logging is enabled at runसमय
	 * and a ग_लिखो fault needs to collapse a block entry पूर्णांकo a table.
	 */
	अगर (fault_status != FSC_PERM || (logging_active && ग_लिखो_fault)) अणु
		ret = kvm_mmu_topup_memory_cache(memcache,
						 kvm_mmu_cache_min_pages(kvm));
		अगर (ret)
			वापस ret;
	पूर्ण

	mmu_seq = vcpu->kvm->mmu_notअगरier_seq;
	/*
	 * Ensure the पढ़ो of mmu_notअगरier_seq happens beक्रमe we call
	 * gfn_to_pfn_prot (which calls get_user_pages), so that we करोn't risk
	 * the page we just got a reference to माला_लो unmapped beक्रमe we have a
	 * chance to grab the mmu_lock, which ensure that अगर the page माला_लो
	 * unmapped afterwards, the call to kvm_unmap_gfn will take it away
	 * from us again properly. This smp_rmb() पूर्णांकeracts with the smp_wmb()
	 * in kvm_mmu_notअगरier_invalidate_<page|range_end>.
	 *
	 * Besides, __gfn_to_pfn_memslot() instead of gfn_to_pfn_prot() is
	 * used to aव्योम unnecessary overhead पूर्णांकroduced to locate the memory
	 * slot because it's always fixed even @gfn is adjusted क्रम huge pages.
	 */
	smp_rmb();

	pfn = __gfn_to_pfn_memslot(memslot, gfn, false, शून्य,
				   ग_लिखो_fault, &writable, शून्य);
	अगर (pfn == KVM_PFN_ERR_HWPOISON) अणु
		kvm_send_hwpoison_संकेत(hva, vma_shअगरt);
		वापस 0;
	पूर्ण
	अगर (is_error_noslot_pfn(pfn))
		वापस -EFAULT;

	अगर (kvm_is_device_pfn(pfn)) अणु
		device = true;
		क्रमce_pte = true;
	पूर्ण अन्यथा अगर (logging_active && !ग_लिखो_fault) अणु
		/*
		 * Only actually map the page as writable अगर this was a ग_लिखो
		 * fault.
		 */
		writable = false;
	पूर्ण

	अगर (exec_fault && device)
		वापस -ENOEXEC;

	spin_lock(&kvm->mmu_lock);
	pgt = vcpu->arch.hw_mmu->pgt;
	अगर (mmu_notअगरier_retry(kvm, mmu_seq))
		जाओ out_unlock;

	/*
	 * If we are not क्रमced to use page mapping, check अगर we are
	 * backed by a THP and thus use block mapping अगर possible.
	 */
	अगर (vma_pagesize == PAGE_SIZE && !क्रमce_pte)
		vma_pagesize = transparent_hugepage_adjust(memslot, hva,
							   &pfn, &fault_ipa);
	अगर (writable)
		prot |= KVM_PGTABLE_PROT_W;

	अगर (fault_status != FSC_PERM && !device)
		clean_dcache_guest_page(pfn, vma_pagesize);

	अगर (exec_fault) अणु
		prot |= KVM_PGTABLE_PROT_X;
		invalidate_icache_guest_page(pfn, vma_pagesize);
	पूर्ण

	अगर (device)
		prot |= KVM_PGTABLE_PROT_DEVICE;
	अन्यथा अगर (cpus_have_स्थिर_cap(ARM64_HAS_CACHE_DIC))
		prot |= KVM_PGTABLE_PROT_X;

	/*
	 * Under the premise of getting a FSC_PERM fault, we just need to relax
	 * permissions only अगर vma_pagesize equals fault_granule. Otherwise,
	 * kvm_pgtable_stage2_map() should be called to change block size.
	 */
	अगर (fault_status == FSC_PERM && vma_pagesize == fault_granule) अणु
		ret = kvm_pgtable_stage2_relax_perms(pgt, fault_ipa, prot);
	पूर्ण अन्यथा अणु
		ret = kvm_pgtable_stage2_map(pgt, fault_ipa, vma_pagesize,
					     __pfn_to_phys(pfn), prot,
					     memcache);
	पूर्ण

	/* Mark the page dirty only अगर the fault is handled successfully */
	अगर (writable && !ret) अणु
		kvm_set_pfn_dirty(pfn);
		mark_page_dirty_in_slot(kvm, memslot, gfn);
	पूर्ण

out_unlock:
	spin_unlock(&kvm->mmu_lock);
	kvm_set_pfn_accessed(pfn);
	kvm_release_pfn_clean(pfn);
	वापस ret != -EAGAIN ? ret : 0;
पूर्ण

/* Resolve the access fault by making the page young again. */
अटल व्योम handle_access_fault(काष्ठा kvm_vcpu *vcpu, phys_addr_t fault_ipa)
अणु
	pte_t pte;
	kvm_pte_t kpte;
	काष्ठा kvm_s2_mmu *mmu;

	trace_kvm_access_fault(fault_ipa);

	spin_lock(&vcpu->kvm->mmu_lock);
	mmu = vcpu->arch.hw_mmu;
	kpte = kvm_pgtable_stage2_mkyoung(mmu->pgt, fault_ipa);
	spin_unlock(&vcpu->kvm->mmu_lock);

	pte = __pte(kpte);
	अगर (pte_valid(pte))
		kvm_set_pfn_accessed(pte_pfn(pte));
पूर्ण

/**
 * kvm_handle_guest_पात - handles all 2nd stage पातs
 * @vcpu:	the VCPU poपूर्णांकer
 *
 * Any पात that माला_लो to the host is almost guaranteed to be caused by a
 * missing second stage translation table entry, which can mean that either the
 * guest simply needs more memory and we must allocate an appropriate page or it
 * can mean that the guest tried to access I/O memory, which is emulated by user
 * space. The distinction is based on the IPA causing the fault and whether this
 * memory region has been रेजिस्टरed as standard RAM by user space.
 */
पूर्णांक kvm_handle_guest_पात(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ fault_status;
	phys_addr_t fault_ipa;
	काष्ठा kvm_memory_slot *memslot;
	अचिन्हित दीर्घ hva;
	bool is_iabt, ग_लिखो_fault, writable;
	gfn_t gfn;
	पूर्णांक ret, idx;

	fault_status = kvm_vcpu_trap_get_fault_type(vcpu);

	fault_ipa = kvm_vcpu_get_fault_ipa(vcpu);
	is_iabt = kvm_vcpu_trap_is_iabt(vcpu);

	/* Synchronous External Abort? */
	अगर (kvm_vcpu_abt_issea(vcpu)) अणु
		/*
		 * For RAS the host kernel may handle this पात.
		 * There is no need to pass the error पूर्णांकo the guest.
		 */
		अगर (kvm_handle_guest_sea(fault_ipa, kvm_vcpu_get_esr(vcpu)))
			kvm_inject_vabt(vcpu);

		वापस 1;
	पूर्ण

	trace_kvm_guest_fault(*vcpu_pc(vcpu), kvm_vcpu_get_esr(vcpu),
			      kvm_vcpu_get_hfar(vcpu), fault_ipa);

	/* Check the stage-2 fault is trans. fault or ग_लिखो fault */
	अगर (fault_status != FSC_FAULT && fault_status != FSC_PERM &&
	    fault_status != FSC_ACCESS) अणु
		kvm_err("Unsupported FSC: EC=%#x xFSC=%#lx ESR_EL2=%#lx\n",
			kvm_vcpu_trap_get_class(vcpu),
			(अचिन्हित दीर्घ)kvm_vcpu_trap_get_fault(vcpu),
			(अचिन्हित दीर्घ)kvm_vcpu_get_esr(vcpu));
		वापस -EFAULT;
	पूर्ण

	idx = srcu_पढ़ो_lock(&vcpu->kvm->srcu);

	gfn = fault_ipa >> PAGE_SHIFT;
	memslot = gfn_to_memslot(vcpu->kvm, gfn);
	hva = gfn_to_hva_memslot_prot(memslot, gfn, &writable);
	ग_लिखो_fault = kvm_is_ग_लिखो_fault(vcpu);
	अगर (kvm_is_error_hva(hva) || (ग_लिखो_fault && !writable)) अणु
		/*
		 * The guest has put either its inकाष्ठाions or its page-tables
		 * somewhere it shouldn't have. Userspace won't be able to करो
		 * anything about this (there's no syndrome क्रम a start), so
		 * re-inject the पात back पूर्णांकo the guest.
		 */
		अगर (is_iabt) अणु
			ret = -ENOEXEC;
			जाओ out;
		पूर्ण

		अगर (kvm_vcpu_abt_iss1tw(vcpu)) अणु
			kvm_inject_dabt(vcpu, kvm_vcpu_get_hfar(vcpu));
			ret = 1;
			जाओ out_unlock;
		पूर्ण

		/*
		 * Check क्रम a cache मुख्यtenance operation. Since we
		 * ended-up here, we know it is outside of any memory
		 * slot. But we can't find out अगर that is क्रम a device,
		 * or अगर the guest is just being stupid. The only thing
		 * we know क्रम sure is that this range cannot be cached.
		 *
		 * So let's assume that the guest is just being
		 * cautious, and skip the inकाष्ठाion.
		 */
		अगर (kvm_is_error_hva(hva) && kvm_vcpu_dabt_is_cm(vcpu)) अणु
			kvm_incr_pc(vcpu);
			ret = 1;
			जाओ out_unlock;
		पूर्ण

		/*
		 * The IPA is reported as [MAX:12], so we need to
		 * complement it with the bottom 12 bits from the
		 * faulting VA. This is always 12 bits, irrespective
		 * of the page size.
		 */
		fault_ipa |= kvm_vcpu_get_hfar(vcpu) & ((1 << 12) - 1);
		ret = io_mem_पात(vcpu, fault_ipa);
		जाओ out_unlock;
	पूर्ण

	/* Userspace should not be able to रेजिस्टर out-of-bounds IPAs */
	VM_BUG_ON(fault_ipa >= kvm_phys_size(vcpu->kvm));

	अगर (fault_status == FSC_ACCESS) अणु
		handle_access_fault(vcpu, fault_ipa);
		ret = 1;
		जाओ out_unlock;
	पूर्ण

	ret = user_mem_पात(vcpu, fault_ipa, memslot, hva, fault_status);
	अगर (ret == 0)
		ret = 1;
out:
	अगर (ret == -ENOEXEC) अणु
		kvm_inject_pabt(vcpu, kvm_vcpu_get_hfar(vcpu));
		ret = 1;
	पूर्ण
out_unlock:
	srcu_पढ़ो_unlock(&vcpu->kvm->srcu, idx);
	वापस ret;
पूर्ण

bool kvm_unmap_gfn_range(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	अगर (!kvm->arch.mmu.pgt)
		वापस false;

	__unmap_stage2_range(&kvm->arch.mmu, range->start << PAGE_SHIFT,
			     (range->end - range->start) << PAGE_SHIFT,
			     range->may_block);

	वापस false;
पूर्ण

bool kvm_set_spte_gfn(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	kvm_pfn_t pfn = pte_pfn(range->pte);

	अगर (!kvm->arch.mmu.pgt)
		वापस false;

	WARN_ON(range->end - range->start != 1);

	/*
	 * We've moved a page around, probably through CoW, so let's treat it
	 * just like a translation fault and clean the cache to the PoC.
	 */
	clean_dcache_guest_page(pfn, PAGE_SIZE);

	/*
	 * The MMU notअगरiers will have unmapped a huge PMD beक्रमe calling
	 * ->change_pte() (which in turn calls kvm_set_spte_gfn()) and
	 * thereक्रमe we never need to clear out a huge PMD through this
	 * calling path and a memcache is not required.
	 */
	kvm_pgtable_stage2_map(kvm->arch.mmu.pgt, range->start << PAGE_SHIFT,
			       PAGE_SIZE, __pfn_to_phys(pfn),
			       KVM_PGTABLE_PROT_R, शून्य);

	वापस false;
पूर्ण

bool kvm_age_gfn(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	u64 size = (range->end - range->start) << PAGE_SHIFT;
	kvm_pte_t kpte;
	pte_t pte;

	अगर (!kvm->arch.mmu.pgt)
		वापस false;

	WARN_ON(size != PAGE_SIZE && size != PMD_SIZE && size != PUD_SIZE);

	kpte = kvm_pgtable_stage2_mkold(kvm->arch.mmu.pgt,
					range->start << PAGE_SHIFT);
	pte = __pte(kpte);
	वापस pte_valid(pte) && pte_young(pte);
पूर्ण

bool kvm_test_age_gfn(काष्ठा kvm *kvm, काष्ठा kvm_gfn_range *range)
अणु
	अगर (!kvm->arch.mmu.pgt)
		वापस false;

	वापस kvm_pgtable_stage2_is_young(kvm->arch.mmu.pgt,
					   range->start << PAGE_SHIFT);
पूर्ण

phys_addr_t kvm_mmu_get_httbr(व्योम)
अणु
	वापस __pa(hyp_pgtable->pgd);
पूर्ण

phys_addr_t kvm_get_idmap_vector(व्योम)
अणु
	वापस hyp_idmap_vector;
पूर्ण

अटल पूर्णांक kvm_map_idmap_text(व्योम)
अणु
	अचिन्हित दीर्घ size = hyp_idmap_end - hyp_idmap_start;
	पूर्णांक err = __create_hyp_mappings(hyp_idmap_start, size, hyp_idmap_start,
					PAGE_HYP_EXEC);
	अगर (err)
		kvm_err("Failed to idmap %lx-%lx\n",
			hyp_idmap_start, hyp_idmap_end);

	वापस err;
पूर्ण

अटल व्योम *kvm_hyp_zalloc_page(व्योम *arg)
अणु
	वापस (व्योम *)get_zeroed_page(GFP_KERNEL);
पूर्ण

अटल काष्ठा kvm_pgtable_mm_ops kvm_hyp_mm_ops = अणु
	.zalloc_page		= kvm_hyp_zalloc_page,
	.get_page		= kvm_host_get_page,
	.put_page		= kvm_host_put_page,
	.phys_to_virt		= kvm_host_va,
	.virt_to_phys		= kvm_host_pa,
पूर्ण;

पूर्णांक kvm_mmu_init(u32 *hyp_va_bits)
अणु
	पूर्णांक err;

	hyp_idmap_start = __pa_symbol(__hyp_idmap_text_start);
	hyp_idmap_start = ALIGN_DOWN(hyp_idmap_start, PAGE_SIZE);
	hyp_idmap_end = __pa_symbol(__hyp_idmap_text_end);
	hyp_idmap_end = ALIGN(hyp_idmap_end, PAGE_SIZE);
	hyp_idmap_vector = __pa_symbol(__kvm_hyp_init);

	/*
	 * We rely on the linker script to ensure at build समय that the HYP
	 * init code करोes not cross a page boundary.
	 */
	BUG_ON((hyp_idmap_start ^ (hyp_idmap_end - 1)) & PAGE_MASK);

	*hyp_va_bits = 64 - ((idmap_t0sz & TCR_T0SZ_MASK) >> TCR_T0SZ_OFFSET);
	kvm_debug("Using %u-bit virtual addresses at EL2\n", *hyp_va_bits);
	kvm_debug("IDMAP page: %lx\n", hyp_idmap_start);
	kvm_debug("HYP VA range: %lx:%lx\n",
		  kern_hyp_va(PAGE_OFFSET),
		  kern_hyp_va((अचिन्हित दीर्घ)high_memory - 1));

	अगर (hyp_idmap_start >= kern_hyp_va(PAGE_OFFSET) &&
	    hyp_idmap_start <  kern_hyp_va((अचिन्हित दीर्घ)high_memory - 1) &&
	    hyp_idmap_start != (अचिन्हित दीर्घ)__hyp_idmap_text_start) अणु
		/*
		 * The idmap page is पूर्णांकersecting with the VA space,
		 * it is not safe to जारी further.
		 */
		kvm_err("IDMAP intersecting with HYP VA, unable to continue\n");
		err = -EINVAL;
		जाओ out;
	पूर्ण

	hyp_pgtable = kzalloc(माप(*hyp_pgtable), GFP_KERNEL);
	अगर (!hyp_pgtable) अणु
		kvm_err("Hyp mode page-table not allocated\n");
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	err = kvm_pgtable_hyp_init(hyp_pgtable, *hyp_va_bits, &kvm_hyp_mm_ops);
	अगर (err)
		जाओ out_मुक्त_pgtable;

	err = kvm_map_idmap_text();
	अगर (err)
		जाओ out_destroy_pgtable;

	io_map_base = hyp_idmap_start;
	वापस 0;

out_destroy_pgtable:
	kvm_pgtable_hyp_destroy(hyp_pgtable);
out_मुक्त_pgtable:
	kमुक्त(hyp_pgtable);
	hyp_pgtable = शून्य;
out:
	वापस err;
पूर्ण

व्योम kvm_arch_commit_memory_region(काष्ठा kvm *kvm,
				   स्थिर काष्ठा kvm_userspace_memory_region *mem,
				   काष्ठा kvm_memory_slot *old,
				   स्थिर काष्ठा kvm_memory_slot *new,
				   क्रमागत kvm_mr_change change)
अणु
	/*
	 * At this poपूर्णांक memslot has been committed and there is an
	 * allocated dirty_biपंचांगap[], dirty pages will be tracked जबतक the
	 * memory slot is ग_लिखो रक्षित.
	 */
	अगर (change != KVM_MR_DELETE && mem->flags & KVM_MEM_LOG_सूचीTY_PAGES) अणु
		/*
		 * If we're with initial-all-set, we don't need to ग_लिखो
		 * protect any pages because they're all reported as dirty.
		 * Huge pages and normal pages will be ग_लिखो protect gradually.
		 */
		अगर (!kvm_dirty_log_manual_protect_and_init_set(kvm)) अणु
			kvm_mmu_wp_memory_region(kvm, mem->slot);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक kvm_arch_prepare_memory_region(काष्ठा kvm *kvm,
				   काष्ठा kvm_memory_slot *memslot,
				   स्थिर काष्ठा kvm_userspace_memory_region *mem,
				   क्रमागत kvm_mr_change change)
अणु
	hva_t hva = mem->userspace_addr;
	hva_t reg_end = hva + mem->memory_size;
	bool writable = !(mem->flags & KVM_MEM_READONLY);
	पूर्णांक ret = 0;

	अगर (change != KVM_MR_CREATE && change != KVM_MR_MOVE &&
			change != KVM_MR_FLAGS_ONLY)
		वापस 0;

	/*
	 * Prevent userspace from creating a memory region outside of the IPA
	 * space addressable by the KVM guest IPA space.
	 */
	अगर ((memslot->base_gfn + memslot->npages) > (kvm_phys_size(kvm) >> PAGE_SHIFT))
		वापस -EFAULT;

	mmap_पढ़ो_lock(current->mm);
	/*
	 * A memory region could potentially cover multiple VMAs, and any holes
	 * between them, so iterate over all of them to find out अगर we can map
	 * any of them right now.
	 *
	 *     +--------------------------------------------+
	 * +---------------+----------------+   +----------------+
	 * |   : VMA 1     |      VMA 2     |   |    VMA 3  :    |
	 * +---------------+----------------+   +----------------+
	 *     |               memory region                |
	 *     +--------------------------------------------+
	 */
	करो अणु
		काष्ठा vm_area_काष्ठा *vma;
		hva_t vm_start, vm_end;

		vma = find_vma_पूर्णांकersection(current->mm, hva, reg_end);
		अगर (!vma)
			अवरोध;

		/*
		 * Take the पूर्णांकersection of this VMA with the memory region
		 */
		vm_start = max(hva, vma->vm_start);
		vm_end = min(reg_end, vma->vm_end);

		अगर (vma->vm_flags & VM_PFNMAP) अणु
			gpa_t gpa = mem->guest_phys_addr +
				    (vm_start - mem->userspace_addr);
			phys_addr_t pa;

			pa = (phys_addr_t)vma->vm_pgoff << PAGE_SHIFT;
			pa += vm_start - vma->vm_start;

			/* IO region dirty page logging not allowed */
			अगर (memslot->flags & KVM_MEM_LOG_सूचीTY_PAGES) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण

			ret = kvm_phys_addr_ioremap(kvm, gpa, pa,
						    vm_end - vm_start,
						    writable);
			अगर (ret)
				अवरोध;
		पूर्ण
		hva = vm_end;
	पूर्ण जबतक (hva < reg_end);

	अगर (change == KVM_MR_FLAGS_ONLY)
		जाओ out;

	spin_lock(&kvm->mmu_lock);
	अगर (ret)
		unmap_stage2_range(&kvm->arch.mmu, mem->guest_phys_addr, mem->memory_size);
	अन्यथा अगर (!cpus_have_final_cap(ARM64_HAS_STAGE2_FWB))
		stage2_flush_memslot(kvm, memslot);
	spin_unlock(&kvm->mmu_lock);
out:
	mmap_पढ़ो_unlock(current->mm);
	वापस ret;
पूर्ण

व्योम kvm_arch_मुक्त_memslot(काष्ठा kvm *kvm, काष्ठा kvm_memory_slot *slot)
अणु
पूर्ण

व्योम kvm_arch_memslots_updated(काष्ठा kvm *kvm, u64 gen)
अणु
पूर्ण

व्योम kvm_arch_flush_shaकरोw_all(काष्ठा kvm *kvm)
अणु
	kvm_मुक्त_stage2_pgd(&kvm->arch.mmu);
पूर्ण

व्योम kvm_arch_flush_shaकरोw_memslot(काष्ठा kvm *kvm,
				   काष्ठा kvm_memory_slot *slot)
अणु
	gpa_t gpa = slot->base_gfn << PAGE_SHIFT;
	phys_addr_t size = slot->npages << PAGE_SHIFT;

	spin_lock(&kvm->mmu_lock);
	unmap_stage2_range(&kvm->arch.mmu, gpa, size);
	spin_unlock(&kvm->mmu_lock);
पूर्ण

/*
 * See note at ARMv7 ARM B1.14.4 (TL;DR: S/W ops are not easily भवized).
 *
 * Main problems:
 * - S/W ops are local to a CPU (not broadcast)
 * - We have line migration behind our back (speculation)
 * - System caches करोn't support S/W at all (damn!)
 *
 * In the face of the above, the best we can करो is to try and convert
 * S/W ops to VA ops. Because the guest is not allowed to infer the
 * S/W to PA mapping, it can only use S/W to nuke the whole cache,
 * which is a rather good thing क्रम us.
 *
 * Also, it is only used when turning caches on/off ("The expected
 * usage of the cache मुख्यtenance inकाष्ठाions that operate by set/way
 * is associated with the cache मुख्यtenance inकाष्ठाions associated
 * with the घातerकरोwn and घातerup of caches, अगर this is required by
 * the implementation.").
 *
 * We use the following policy:
 *
 * - If we trap a S/W operation, we enable VM trapping to detect
 *   caches being turned on/off, and करो a full clean.
 *
 * - We flush the caches on both caches being turned on and off.
 *
 * - Once the caches are enabled, we stop trapping VM ops.
 */
व्योम kvm_set_way_flush(काष्ठा kvm_vcpu *vcpu)
अणु
	अचिन्हित दीर्घ hcr = *vcpu_hcr(vcpu);

	/*
	 * If this is the first समय we करो a S/W operation
	 * (i.e. HCR_TVM not set) flush the whole memory, and set the
	 * VM trapping.
	 *
	 * Otherwise, rely on the VM trapping to रुको क्रम the MMU +
	 * Caches to be turned off. At that poपूर्णांक, we'll be able to
	 * clean the caches again.
	 */
	अगर (!(hcr & HCR_TVM)) अणु
		trace_kvm_set_way_flush(*vcpu_pc(vcpu),
					vcpu_has_cache_enabled(vcpu));
		stage2_flush_vm(vcpu->kvm);
		*vcpu_hcr(vcpu) = hcr | HCR_TVM;
	पूर्ण
पूर्ण

व्योम kvm_toggle_cache(काष्ठा kvm_vcpu *vcpu, bool was_enabled)
अणु
	bool now_enabled = vcpu_has_cache_enabled(vcpu);

	/*
	 * If चयनing the MMU+caches on, need to invalidate the caches.
	 * If चयनing it off, need to clean the caches.
	 * Clean + invalidate करोes the trick always.
	 */
	अगर (now_enabled != was_enabled)
		stage2_flush_vm(vcpu->kvm);

	/* Caches are now on, stop trapping VM ops (until a S/W op) */
	अगर (now_enabled)
		*vcpu_hcr(vcpu) &= ~HCR_TVM;

	trace_kvm_toggle_cache(*vcpu_pc(vcpu), was_enabled, now_enabled);
पूर्ण
