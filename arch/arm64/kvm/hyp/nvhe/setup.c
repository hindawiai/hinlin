<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 Google LLC
 * Author: Quentin Perret <qperret@google.com>
 */

#समावेश <linux/kvm_host.h>
#समावेश <यंत्र/kvm_hyp.h>
#समावेश <यंत्र/kvm_mmu.h>
#समावेश <यंत्र/kvm_pgtable.h>

#समावेश <nvhe/early_भाग.स>
#समावेश <nvhe/gfp.h>
#समावेश <nvhe/memory.h>
#समावेश <nvhe/mem_protect.h>
#समावेश <nvhe/mm.h>
#समावेश <nvhe/trap_handler.h>

काष्ठा hyp_pool hpool;
अचिन्हित दीर्घ hyp_nr_cpus;

#घोषणा hyp_percpu_size ((अचिन्हित दीर्घ)__per_cpu_end - \
			 (अचिन्हित दीर्घ)__per_cpu_start)

अटल व्योम *vmemmap_base;
अटल व्योम *hyp_pgt_base;
अटल व्योम *host_s2_mem_pgt_base;
अटल व्योम *host_s2_dev_pgt_base;
अटल काष्ठा kvm_pgtable_mm_ops pkvm_pgtable_mm_ops;

अटल पूर्णांक भागide_memory_pool(व्योम *virt, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ vstart, vend, nr_pages;

	hyp_early_alloc_init(virt, size);

	hyp_vmemmap_range(__hyp_pa(virt), size, &vstart, &vend);
	nr_pages = (vend - vstart) >> PAGE_SHIFT;
	vmemmap_base = hyp_early_alloc_contig(nr_pages);
	अगर (!vmemmap_base)
		वापस -ENOMEM;

	nr_pages = hyp_s1_pgtable_pages();
	hyp_pgt_base = hyp_early_alloc_contig(nr_pages);
	अगर (!hyp_pgt_base)
		वापस -ENOMEM;

	nr_pages = host_s2_mem_pgtable_pages();
	host_s2_mem_pgt_base = hyp_early_alloc_contig(nr_pages);
	अगर (!host_s2_mem_pgt_base)
		वापस -ENOMEM;

	nr_pages = host_s2_dev_pgtable_pages();
	host_s2_dev_pgt_base = hyp_early_alloc_contig(nr_pages);
	अगर (!host_s2_dev_pgt_base)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक recreate_hyp_mappings(phys_addr_t phys, अचिन्हित दीर्घ size,
				 अचिन्हित दीर्घ *per_cpu_base,
				 u32 hyp_va_bits)
अणु
	व्योम *start, *end, *virt = hyp_phys_to_virt(phys);
	अचिन्हित दीर्घ pgt_size = hyp_s1_pgtable_pages() << PAGE_SHIFT;
	पूर्णांक ret, i;

	/* Recreate the hyp page-table using the early page allocator */
	hyp_early_alloc_init(hyp_pgt_base, pgt_size);
	ret = kvm_pgtable_hyp_init(&pkvm_pgtable, hyp_va_bits,
				   &hyp_early_alloc_mm_ops);
	अगर (ret)
		वापस ret;

	ret = hyp_create_idmap(hyp_va_bits);
	अगर (ret)
		वापस ret;

	ret = hyp_map_vectors();
	अगर (ret)
		वापस ret;

	ret = hyp_back_vmemmap(phys, size, hyp_virt_to_phys(vmemmap_base));
	अगर (ret)
		वापस ret;

	ret = pkvm_create_mappings(__hyp_text_start, __hyp_text_end, PAGE_HYP_EXEC);
	अगर (ret)
		वापस ret;

	ret = pkvm_create_mappings(__start_rodata, __end_rodata, PAGE_HYP_RO);
	अगर (ret)
		वापस ret;

	ret = pkvm_create_mappings(__hyp_rodata_start, __hyp_rodata_end, PAGE_HYP_RO);
	अगर (ret)
		वापस ret;

	ret = pkvm_create_mappings(__hyp_bss_start, __hyp_bss_end, PAGE_HYP);
	अगर (ret)
		वापस ret;

	ret = pkvm_create_mappings(__hyp_bss_end, __bss_stop, PAGE_HYP_RO);
	अगर (ret)
		वापस ret;

	ret = pkvm_create_mappings(virt, virt + size, PAGE_HYP);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < hyp_nr_cpus; i++) अणु
		start = (व्योम *)kern_hyp_va(per_cpu_base[i]);
		end = start + PAGE_ALIGN(hyp_percpu_size);
		ret = pkvm_create_mappings(start, end, PAGE_HYP);
		अगर (ret)
			वापस ret;

		end = (व्योम *)per_cpu_ptr(&kvm_init_params, i)->stack_hyp_va;
		start = end - PAGE_SIZE;
		ret = pkvm_create_mappings(start, end, PAGE_HYP);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम update_nvhe_init_params(व्योम)
अणु
	काष्ठा kvm_nvhe_init_params *params;
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < hyp_nr_cpus; i++) अणु
		params = per_cpu_ptr(&kvm_init_params, i);
		params->pgd_pa = __hyp_pa(pkvm_pgtable.pgd);
		__flush_dcache_area(params, माप(*params));
	पूर्ण
पूर्ण

अटल व्योम *hyp_zalloc_hyp_page(व्योम *arg)
अणु
	वापस hyp_alloc_pages(&hpool, 0);
पूर्ण

व्योम __noवापस __pkvm_init_finalise(व्योम)
अणु
	काष्ठा kvm_host_data *host_data = this_cpu_ptr(&kvm_host_data);
	काष्ठा kvm_cpu_context *host_ctxt = &host_data->host_ctxt;
	अचिन्हित दीर्घ nr_pages, reserved_pages, pfn;
	पूर्णांक ret;

	/* Now that the vmemmap is backed, install the full-fledged allocator */
	pfn = hyp_virt_to_pfn(hyp_pgt_base);
	nr_pages = hyp_s1_pgtable_pages();
	reserved_pages = hyp_early_alloc_nr_used_pages();
	ret = hyp_pool_init(&hpool, pfn, nr_pages, reserved_pages);
	अगर (ret)
		जाओ out;

	ret = kvm_host_prepare_stage2(host_s2_mem_pgt_base, host_s2_dev_pgt_base);
	अगर (ret)
		जाओ out;

	pkvm_pgtable_mm_ops = (काष्ठा kvm_pgtable_mm_ops) अणु
		.zalloc_page = hyp_zalloc_hyp_page,
		.phys_to_virt = hyp_phys_to_virt,
		.virt_to_phys = hyp_virt_to_phys,
		.get_page = hyp_get_page,
		.put_page = hyp_put_page,
	पूर्ण;
	pkvm_pgtable.mm_ops = &pkvm_pgtable_mm_ops;

out:
	/*
	 * We tail-called to here from handle___pkvm_init() and will not वापस,
	 * so make sure to propagate the वापस value to the host.
	 */
	cpu_reg(host_ctxt, 1) = ret;

	__host_enter(host_ctxt);
पूर्ण

पूर्णांक __pkvm_init(phys_addr_t phys, अचिन्हित दीर्घ size, अचिन्हित दीर्घ nr_cpus,
		अचिन्हित दीर्घ *per_cpu_base, u32 hyp_va_bits)
अणु
	काष्ठा kvm_nvhe_init_params *params;
	व्योम *virt = hyp_phys_to_virt(phys);
	व्योम (*fn)(phys_addr_t params_pa, व्योम *finalize_fn_va);
	पूर्णांक ret;

	अगर (!PAGE_ALIGNED(phys) || !PAGE_ALIGNED(size))
		वापस -EINVAL;

	hyp_spin_lock_init(&pkvm_pgd_lock);
	hyp_nr_cpus = nr_cpus;

	ret = भागide_memory_pool(virt, size);
	अगर (ret)
		वापस ret;

	ret = recreate_hyp_mappings(phys, size, per_cpu_base, hyp_va_bits);
	अगर (ret)
		वापस ret;

	update_nvhe_init_params();

	/* Jump in the idmap page to चयन to the new page-tables */
	params = this_cpu_ptr(&kvm_init_params);
	fn = (typeof(fn))__hyp_pa(__pkvm_init_चयन_pgd);
	fn(__hyp_pa(params), __pkvm_init_finalise);

	unreachable();
पूर्ण
