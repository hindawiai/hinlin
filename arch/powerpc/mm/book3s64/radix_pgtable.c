<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Page table handling routines क्रम radix page table.
 *
 * Copyright 2015-2016, Aneesh Kumar K.V, IBM Corporation.
 */

#घोषणा pr_fmt(fmt) "radix-mmu: " fmt

#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/memblock.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/mm.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/string_helpers.h>
#समावेश <linux/memory.h>

#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/घातernv.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/trace.h>
#समावेश <यंत्र/uaccess.h>
#समावेश <यंत्र/ultravisor.h>

#समावेश <trace/events/thp.h>

अचिन्हित पूर्णांक mmu_pid_bits;
अचिन्हित पूर्णांक mmu_base_pid;
अचिन्हित दीर्घ radix_mem_block_size __ro_after_init;

अटल __ref व्योम *early_alloc_pgtable(अचिन्हित दीर्घ size, पूर्णांक nid,
			अचिन्हित दीर्घ region_start, अचिन्हित दीर्घ region_end)
अणु
	phys_addr_t min_addr = MEMBLOCK_LOW_LIMIT;
	phys_addr_t max_addr = MEMBLOCK_ALLOC_ANYWHERE;
	व्योम *ptr;

	अगर (region_start)
		min_addr = region_start;
	अगर (region_end)
		max_addr = region_end;

	ptr = memblock_alloc_try_nid(size, size, min_addr, max_addr, nid);

	अगर (!ptr)
		panic("%s: Failed to allocate %lu bytes align=0x%lx nid=%d from=%pa max_addr=%pa\n",
		      __func__, size, size, nid, &min_addr, &max_addr);

	वापस ptr;
पूर्ण

/*
 * When allocating pud or pmd poपूर्णांकers, we allocate a complete page
 * of PAGE_SIZE rather than PUD_TABLE_SIZE or PMD_TABLE_SIZE. This
 * is to ensure that the page obtained from the memblock allocator
 * can be completely used as page table page and can be मुक्तd
 * correctly when the page table entries are हटाओd.
 */
अटल पूर्णांक early_map_kernel_page(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ pa,
			  pgprot_t flags,
			  अचिन्हित पूर्णांक map_page_size,
			  पूर्णांक nid,
			  अचिन्हित दीर्घ region_start, अचिन्हित दीर्घ region_end)
अणु
	अचिन्हित दीर्घ pfn = pa >> PAGE_SHIFT;
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;

	pgdp = pgd_offset_k(ea);
	p4dp = p4d_offset(pgdp, ea);
	अगर (p4d_none(*p4dp)) अणु
		pudp = early_alloc_pgtable(PAGE_SIZE, nid,
					   region_start, region_end);
		p4d_populate(&init_mm, p4dp, pudp);
	पूर्ण
	pudp = pud_offset(p4dp, ea);
	अगर (map_page_size == PUD_SIZE) अणु
		ptep = (pte_t *)pudp;
		जाओ set_the_pte;
	पूर्ण
	अगर (pud_none(*pudp)) अणु
		pmdp = early_alloc_pgtable(PAGE_SIZE, nid, region_start,
					   region_end);
		pud_populate(&init_mm, pudp, pmdp);
	पूर्ण
	pmdp = pmd_offset(pudp, ea);
	अगर (map_page_size == PMD_SIZE) अणु
		ptep = pmdp_ptep(pmdp);
		जाओ set_the_pte;
	पूर्ण
	अगर (!pmd_present(*pmdp)) अणु
		ptep = early_alloc_pgtable(PAGE_SIZE, nid,
						region_start, region_end);
		pmd_populate_kernel(&init_mm, pmdp, ptep);
	पूर्ण
	ptep = pte_offset_kernel(pmdp, ea);

set_the_pte:
	set_pte_at(&init_mm, ea, ptep, pfn_pte(pfn, flags));
	यंत्र अस्थिर("ptesync": : :"memory");
	वापस 0;
पूर्ण

/*
 * nid, region_start, and region_end are hपूर्णांकs to try to place the page
 * table memory in the same node or region.
 */
अटल पूर्णांक __map_kernel_page(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ pa,
			  pgprot_t flags,
			  अचिन्हित पूर्णांक map_page_size,
			  पूर्णांक nid,
			  अचिन्हित दीर्घ region_start, अचिन्हित दीर्घ region_end)
अणु
	अचिन्हित दीर्घ pfn = pa >> PAGE_SHIFT;
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;
	/*
	 * Make sure task size is correct as per the max adddr
	 */
	BUILD_BUG_ON(TASK_SIZE_USER64 > RADIX_PGTABLE_RANGE);

#अगर_घोषित CONFIG_PPC_64K_PAGES
	BUILD_BUG_ON(RADIX_KERN_MAP_SIZE != (1UL << MAX_EA_BITS_PER_CONTEXT));
#पूर्ण_अगर

	अगर (unlikely(!slab_is_available()))
		वापस early_map_kernel_page(ea, pa, flags, map_page_size,
						nid, region_start, region_end);

	/*
	 * Should make page table allocation functions be able to take a
	 * node, so we can place kernel page tables on the right nodes after
	 * boot.
	 */
	pgdp = pgd_offset_k(ea);
	p4dp = p4d_offset(pgdp, ea);
	pudp = pud_alloc(&init_mm, p4dp, ea);
	अगर (!pudp)
		वापस -ENOMEM;
	अगर (map_page_size == PUD_SIZE) अणु
		ptep = (pte_t *)pudp;
		जाओ set_the_pte;
	पूर्ण
	pmdp = pmd_alloc(&init_mm, pudp, ea);
	अगर (!pmdp)
		वापस -ENOMEM;
	अगर (map_page_size == PMD_SIZE) अणु
		ptep = pmdp_ptep(pmdp);
		जाओ set_the_pte;
	पूर्ण
	ptep = pte_alloc_kernel(pmdp, ea);
	अगर (!ptep)
		वापस -ENOMEM;

set_the_pte:
	set_pte_at(&init_mm, ea, ptep, pfn_pte(pfn, flags));
	यंत्र अस्थिर("ptesync": : :"memory");
	वापस 0;
पूर्ण

पूर्णांक radix__map_kernel_page(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ pa,
			  pgprot_t flags,
			  अचिन्हित पूर्णांक map_page_size)
अणु
	वापस __map_kernel_page(ea, pa, flags, map_page_size, -1, 0, 0);
पूर्ण

#अगर_घोषित CONFIG_STRICT_KERNEL_RWX
अटल व्योम radix__change_memory_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
				       अचिन्हित दीर्घ clear)
अणु
	अचिन्हित दीर्घ idx;
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;

	start = ALIGN_DOWN(start, PAGE_SIZE);
	end = PAGE_ALIGN(end); // aligns up

	pr_debug("Changing flags on range %lx-%lx removing 0x%lx\n",
		 start, end, clear);

	क्रम (idx = start; idx < end; idx += PAGE_SIZE) अणु
		pgdp = pgd_offset_k(idx);
		p4dp = p4d_offset(pgdp, idx);
		pudp = pud_alloc(&init_mm, p4dp, idx);
		अगर (!pudp)
			जारी;
		अगर (pud_is_leaf(*pudp)) अणु
			ptep = (pte_t *)pudp;
			जाओ update_the_pte;
		पूर्ण
		pmdp = pmd_alloc(&init_mm, pudp, idx);
		अगर (!pmdp)
			जारी;
		अगर (pmd_is_leaf(*pmdp)) अणु
			ptep = pmdp_ptep(pmdp);
			जाओ update_the_pte;
		पूर्ण
		ptep = pte_alloc_kernel(pmdp, idx);
		अगर (!ptep)
			जारी;
update_the_pte:
		radix__pte_update(&init_mm, idx, ptep, clear, 0, 0);
	पूर्ण

	radix__flush_tlb_kernel_range(start, end);
पूर्ण

व्योम radix__mark_rodata_ro(व्योम)
अणु
	अचिन्हित दीर्घ start, end;

	start = (अचिन्हित दीर्घ)_stext;
	end = (अचिन्हित दीर्घ)__init_begin;

	radix__change_memory_range(start, end, _PAGE_WRITE);
पूर्ण

व्योम radix__mark_iniपंचांगem_nx(व्योम)
अणु
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ)__init_begin;
	अचिन्हित दीर्घ end = (अचिन्हित दीर्घ)__init_end;

	radix__change_memory_range(start, end, _PAGE_EXEC);
पूर्ण
#पूर्ण_अगर /* CONFIG_STRICT_KERNEL_RWX */

अटल अंतरभूत व्योम __meminit
prपूर्णांक_mapping(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, अचिन्हित दीर्घ size, bool exec)
अणु
	अक्षर buf[10];

	अगर (end <= start)
		वापस;

	string_get_size(size, 1, STRING_UNITS_2, buf, माप(buf));

	pr_info("Mapped 0x%016lx-0x%016lx with %s pages%s\n", start, end, buf,
		exec ? " (exec)" : "");
पूर्ण

अटल अचिन्हित दीर्घ next_boundary(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end)
अणु
#अगर_घोषित CONFIG_STRICT_KERNEL_RWX
	अगर (addr < __pa_symbol(__init_begin))
		वापस __pa_symbol(__init_begin);
#पूर्ण_अगर
	वापस end;
पूर्ण

अटल पूर्णांक __meminit create_physical_mapping(अचिन्हित दीर्घ start,
					     अचिन्हित दीर्घ end,
					     अचिन्हित दीर्घ max_mapping_size,
					     पूर्णांक nid, pgprot_t _prot)
अणु
	अचिन्हित दीर्घ vaddr, addr, mapping_size = 0;
	bool prev_exec, exec = false;
	pgprot_t prot;
	पूर्णांक psize;

	start = ALIGN(start, PAGE_SIZE);
	end   = ALIGN_DOWN(end, PAGE_SIZE);
	क्रम (addr = start; addr < end; addr += mapping_size) अणु
		अचिन्हित दीर्घ gap, previous_size;
		पूर्णांक rc;

		gap = next_boundary(addr, end) - addr;
		अगर (gap > max_mapping_size)
			gap = max_mapping_size;
		previous_size = mapping_size;
		prev_exec = exec;

		अगर (IS_ALIGNED(addr, PUD_SIZE) && gap >= PUD_SIZE &&
		    mmu_psize_defs[MMU_PAGE_1G].shअगरt) अणु
			mapping_size = PUD_SIZE;
			psize = MMU_PAGE_1G;
		पूर्ण अन्यथा अगर (IS_ALIGNED(addr, PMD_SIZE) && gap >= PMD_SIZE &&
			   mmu_psize_defs[MMU_PAGE_2M].shअगरt) अणु
			mapping_size = PMD_SIZE;
			psize = MMU_PAGE_2M;
		पूर्ण अन्यथा अणु
			mapping_size = PAGE_SIZE;
			psize = mmu_भव_psize;
		पूर्ण

		vaddr = (अचिन्हित दीर्घ)__va(addr);

		अगर (overlaps_kernel_text(vaddr, vaddr + mapping_size) ||
		    overlaps_पूर्णांकerrupt_vector_text(vaddr, vaddr + mapping_size)) अणु
			prot = PAGE_KERNEL_X;
			exec = true;
		पूर्ण अन्यथा अणु
			prot = _prot;
			exec = false;
		पूर्ण

		अगर (mapping_size != previous_size || exec != prev_exec) अणु
			prपूर्णांक_mapping(start, addr, previous_size, prev_exec);
			start = addr;
		पूर्ण

		rc = __map_kernel_page(vaddr, addr, prot, mapping_size, nid, start, end);
		अगर (rc)
			वापस rc;

		update_page_count(psize, 1);
	पूर्ण

	prपूर्णांक_mapping(start, addr, mapping_size, exec);
	वापस 0;
पूर्ण

अटल व्योम __init radix_init_pgtable(व्योम)
अणु
	अचिन्हित दीर्घ rts_field;
	phys_addr_t start, end;
	u64 i;

	/* We करोn't support slb क्रम radix */
	mmu_slb_size = 0;

	/*
	 * Create the linear mapping
	 */
	क्रम_each_mem_range(i, &start, &end) अणु
		/*
		 * The memblock allocator  is up at this poपूर्णांक, so the
		 * page tables will be allocated within the range. No
		 * need or a node (which we करोn't have yet).
		 */

		अगर (end >= RADIX_VMALLOC_START) अणु
			pr_warn("Outside the supported range\n");
			जारी;
		पूर्ण

		WARN_ON(create_physical_mapping(start, end,
						radix_mem_block_size,
						-1, PAGE_KERNEL));
	पूर्ण

	/* Find out how many PID bits are supported */
	अगर (!cpu_has_feature(CPU_FTR_P9_RADIX_PREFETCH_BUG)) अणु
		अगर (!mmu_pid_bits)
			mmu_pid_bits = 20;
		mmu_base_pid = 1;
	पूर्ण अन्यथा अगर (cpu_has_feature(CPU_FTR_HVMODE)) अणु
		अगर (!mmu_pid_bits)
			mmu_pid_bits = 20;
#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
		/*
		 * When KVM is possible, we only use the top half of the
		 * PID space to aव्योम collisions between host and guest PIDs
		 * which can cause problems due to prefetch when निकासing the
		 * guest with AIL=3
		 */
		mmu_base_pid = 1 << (mmu_pid_bits - 1);
#अन्यथा
		mmu_base_pid = 1;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		/* The guest uses the bottom half of the PID space */
		अगर (!mmu_pid_bits)
			mmu_pid_bits = 19;
		mmu_base_pid = 1;
	पूर्ण

	/*
	 * Allocate Partition table and process table क्रम the
	 * host.
	 */
	BUG_ON(PRTB_SIZE_SHIFT > 36);
	process_tb = early_alloc_pgtable(1UL << PRTB_SIZE_SHIFT, -1, 0, 0);
	/*
	 * Fill in the process table.
	 */
	rts_field = radix__get_tree_size();
	process_tb->prtb0 = cpu_to_be64(rts_field | __pa(init_mm.pgd) | RADIX_PGD_INDEX_SIZE);

	/*
	 * The init_mm context is given the first available (non-zero) PID,
	 * which is the "guard PID" and contains no page table. PIDR should
	 * never be set to zero because that duplicates the kernel address
	 * space at the 0x0... offset (quadrant 0)!
	 *
	 * An arbitrary PID that may later be allocated by the PID allocator
	 * क्रम userspace processes must not be used either, because that
	 * would cause stale user mappings क्रम that PID on CPUs outside of
	 * the TLB invalidation scheme (because it won't be in mm_cpumask).
	 *
	 * So permanently carve out one PID क्रम the purpose of a guard PID.
	 */
	init_mm.context.id = mmu_base_pid;
	mmu_base_pid++;
पूर्ण

अटल व्योम __init radix_init_partition_table(व्योम)
अणु
	अचिन्हित दीर्घ rts_field, dw0, dw1;

	mmu_partition_table_init();
	rts_field = radix__get_tree_size();
	dw0 = rts_field | __pa(init_mm.pgd) | RADIX_PGD_INDEX_SIZE | PATB_HR;
	dw1 = __pa(process_tb) | (PRTB_SIZE_SHIFT - 12) | PATB_GR;
	mmu_partition_table_set_entry(0, dw0, dw1, false);

	pr_info("Initializing Radix MMU\n");
पूर्ण

अटल पूर्णांक __init get_idx_from_shअगरt(अचिन्हित पूर्णांक shअगरt)
अणु
	पूर्णांक idx = -1;

	चयन (shअगरt) अणु
	हाल 0xc:
		idx = MMU_PAGE_4K;
		अवरोध;
	हाल 0x10:
		idx = MMU_PAGE_64K;
		अवरोध;
	हाल 0x15:
		idx = MMU_PAGE_2M;
		अवरोध;
	हाल 0x1e:
		idx = MMU_PAGE_1G;
		अवरोध;
	पूर्ण
	वापस idx;
पूर्ण

अटल पूर्णांक __init radix_dt_scan_page_sizes(अचिन्हित दीर्घ node,
					   स्थिर अक्षर *uname, पूर्णांक depth,
					   व्योम *data)
अणु
	पूर्णांक size = 0;
	पूर्णांक shअगरt, idx;
	अचिन्हित पूर्णांक ap;
	स्थिर __be32 *prop;
	स्थिर अक्षर *type = of_get_flat_dt_prop(node, "device_type", शून्य);

	/* We are scanning "cpu" nodes only */
	अगर (type == शून्य || म_भेद(type, "cpu") != 0)
		वापस 0;

	/* Find MMU PID size */
	prop = of_get_flat_dt_prop(node, "ibm,mmu-pid-bits", &size);
	अगर (prop && size == 4)
		mmu_pid_bits = be32_to_cpup(prop);

	/* Grab page size encodings */
	prop = of_get_flat_dt_prop(node, "ibm,processor-radix-AP-encodings", &size);
	अगर (!prop)
		वापस 0;

	pr_info("Page sizes from device-tree:\n");
	क्रम (; size >= 4; size -= 4, ++prop) अणु

		काष्ठा mmu_psize_def *def;

		/* top 3 bit is AP encoding */
		shअगरt = be32_to_cpu(prop[0]) & ~(0xe << 28);
		ap = be32_to_cpu(prop[0]) >> 29;
		pr_info("Page size shift = %d AP=0x%x\n", shअगरt, ap);

		idx = get_idx_from_shअगरt(shअगरt);
		अगर (idx < 0)
			जारी;

		def = &mmu_psize_defs[idx];
		def->shअगरt = shअगरt;
		def->ap  = ap;
	पूर्ण

	/* needed ? */
	cur_cpu_spec->mmu_features &= ~MMU_FTR_NO_SLBIE_B;
	वापस 1;
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
अटल पूर्णांक __init probe_memory_block_size(अचिन्हित दीर्घ node, स्थिर अक्षर *uname, पूर्णांक
					  depth, व्योम *data)
अणु
	अचिन्हित दीर्घ *mem_block_size = (अचिन्हित दीर्घ *)data;
	स्थिर __be32 *prop;
	पूर्णांक len;

	अगर (depth != 1)
		वापस 0;

	अगर (म_भेद(uname, "ibm,dynamic-reconfiguration-memory"))
		वापस 0;

	prop = of_get_flat_dt_prop(node, "ibm,lmb-size", &len);

	अगर (!prop || len < dt_root_size_cells * माप(__be32))
		/*
		 * Nothing in the device tree
		 */
		*mem_block_size = MIN_MEMORY_BLOCK_SIZE;
	अन्यथा
		*mem_block_size = of_पढ़ो_number(prop, dt_root_size_cells);
	वापस 1;
पूर्ण

अटल अचिन्हित दीर्घ radix_memory_block_size(व्योम)
अणु
	अचिन्हित दीर्घ mem_block_size = MIN_MEMORY_BLOCK_SIZE;

	/*
	 * OPAL firmware feature is set by now. Hence we are ok
	 * to test OPAL feature.
	 */
	अगर (firmware_has_feature(FW_FEATURE_OPAL))
		mem_block_size = 1UL * 1024 * 1024 * 1024;
	अन्यथा
		of_scan_flat_dt(probe_memory_block_size, &mem_block_size);

	वापस mem_block_size;
पूर्ण

#अन्यथा   /* CONFIG_MEMORY_HOTPLUG */

अटल अचिन्हित दीर्घ radix_memory_block_size(व्योम)
अणु
	वापस 1UL * 1024 * 1024 * 1024;
पूर्ण

#पूर्ण_अगर /* CONFIG_MEMORY_HOTPLUG */


व्योम __init radix__early_init_devtree(व्योम)
अणु
	पूर्णांक rc;

	/*
	 * Try to find the available page sizes in the device-tree
	 */
	rc = of_scan_flat_dt(radix_dt_scan_page_sizes, शून्य);
	अगर (!rc) अणु
		/*
		 * No page size details found in device tree.
		 * Let's assume we have page 4k and 64k support
		 */
		mmu_psize_defs[MMU_PAGE_4K].shअगरt = 12;
		mmu_psize_defs[MMU_PAGE_4K].ap = 0x0;

		mmu_psize_defs[MMU_PAGE_64K].shअगरt = 16;
		mmu_psize_defs[MMU_PAGE_64K].ap = 0x5;
	पूर्ण

	/*
	 * Max mapping size used when mapping pages. We करोn't use
	 * ppc_md.memory_block_size() here because this get called
	 * early and we करोn't have machine probe called yet. Also
	 * the pseries implementation only check क्रम ibm,lmb-size.
	 * All hypervisor supporting radix करो expose that device
	 * tree node.
	 */
	radix_mem_block_size = radix_memory_block_size();
	वापस;
पूर्ण

अटल व्योम radix_init_amor(व्योम)
अणु
	/*
	* In HV mode, we init AMOR (Authority Mask Override Register) so that
	* the hypervisor and guest can setup IAMR (Inकाष्ठाion Authority Mask
	* Register), enable key 0 and set it to 1.
	*
	* AMOR = 0b1100 .... 0000 (Mask क्रम key 0 is 11)
	*/
	mtspr(SPRN_AMOR, (3ul << 62));
पूर्ण

व्योम __init radix__early_init_mmu(व्योम)
अणु
	अचिन्हित दीर्घ lpcr;

#अगर_घोषित CONFIG_PPC_64K_PAGES
	/* PAGE_SIZE mappings */
	mmu_भव_psize = MMU_PAGE_64K;
#अन्यथा
	mmu_भव_psize = MMU_PAGE_4K;
#पूर्ण_अगर

#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
	/* vmemmap mapping */
	अगर (mmu_psize_defs[MMU_PAGE_2M].shअगरt) अणु
		/*
		 * map vmemmap using 2M अगर available
		 */
		mmu_vmemmap_psize = MMU_PAGE_2M;
	पूर्ण अन्यथा
		mmu_vmemmap_psize = mmu_भव_psize;
#पूर्ण_अगर
	/*
	 * initialize page table size
	 */
	__pte_index_size = RADIX_PTE_INDEX_SIZE;
	__pmd_index_size = RADIX_PMD_INDEX_SIZE;
	__pud_index_size = RADIX_PUD_INDEX_SIZE;
	__pgd_index_size = RADIX_PGD_INDEX_SIZE;
	__pud_cache_index = RADIX_PUD_INDEX_SIZE;
	__pte_table_size = RADIX_PTE_TABLE_SIZE;
	__pmd_table_size = RADIX_PMD_TABLE_SIZE;
	__pud_table_size = RADIX_PUD_TABLE_SIZE;
	__pgd_table_size = RADIX_PGD_TABLE_SIZE;

	__pmd_val_bits = RADIX_PMD_VAL_BITS;
	__pud_val_bits = RADIX_PUD_VAL_BITS;
	__pgd_val_bits = RADIX_PGD_VAL_BITS;

	__kernel_virt_start = RADIX_KERN_VIRT_START;
	__vदो_स्मृति_start = RADIX_VMALLOC_START;
	__vदो_स्मृति_end = RADIX_VMALLOC_END;
	__kernel_io_start = RADIX_KERN_IO_START;
	__kernel_io_end = RADIX_KERN_IO_END;
	vmemmap = (काष्ठा page *)RADIX_VMEMMAP_START;
	ioremap_bot = IOREMAP_BASE;

#अगर_घोषित CONFIG_PCI
	pci_io_base = ISA_IO_BASE;
#पूर्ण_अगर
	__pte_frag_nr = RADIX_PTE_FRAG_NR;
	__pte_frag_size_shअगरt = RADIX_PTE_FRAG_SIZE_SHIFT;
	__pmd_frag_nr = RADIX_PMD_FRAG_NR;
	__pmd_frag_size_shअगरt = RADIX_PMD_FRAG_SIZE_SHIFT;

	radix_init_pgtable();

	अगर (!firmware_has_feature(FW_FEATURE_LPAR)) अणु
		lpcr = mfspr(SPRN_LPCR);
		mtspr(SPRN_LPCR, lpcr | LPCR_UPRT | LPCR_HR);
		radix_init_partition_table();
		radix_init_amor();
	पूर्ण अन्यथा अणु
		radix_init_pseries();
	पूर्ण

	memblock_set_current_limit(MEMBLOCK_ALLOC_ANYWHERE);

	/* Switch to the guard PID beक्रमe turning on MMU */
	radix__चयन_mmu_context(शून्य, &init_mm);
	tlbiel_all();
पूर्ण

व्योम radix__early_init_mmu_secondary(व्योम)
अणु
	अचिन्हित दीर्घ lpcr;
	/*
	 * update partition table control रेजिस्टर and UPRT
	 */
	अगर (!firmware_has_feature(FW_FEATURE_LPAR)) अणु
		lpcr = mfspr(SPRN_LPCR);
		mtspr(SPRN_LPCR, lpcr | LPCR_UPRT | LPCR_HR);

		set_ptcr_when_no_uv(__pa(partition_tb) |
				    (PATB_SIZE_SHIFT - 12));

		radix_init_amor();
	पूर्ण

	radix__चयन_mmu_context(शून्य, &init_mm);
	tlbiel_all();

	/* Make sure userspace can't change the AMR */
	mtspr(SPRN_UAMOR, 0);
पूर्ण

व्योम radix__mmu_cleanup_all(व्योम)
अणु
	अचिन्हित दीर्घ lpcr;

	अगर (!firmware_has_feature(FW_FEATURE_LPAR)) अणु
		lpcr = mfspr(SPRN_LPCR);
		mtspr(SPRN_LPCR, lpcr & ~LPCR_UPRT);
		set_ptcr_when_no_uv(0);
		घातernv_set_nmmu_ptcr(0);
		radix__flush_tlb_all();
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
अटल व्योम मुक्त_pte_table(pte_t *pte_start, pmd_t *pmd)
अणु
	pte_t *pte;
	पूर्णांक i;

	क्रम (i = 0; i < PTRS_PER_PTE; i++) अणु
		pte = pte_start + i;
		अगर (!pte_none(*pte))
			वापस;
	पूर्ण

	pte_मुक्त_kernel(&init_mm, pte_start);
	pmd_clear(pmd);
पूर्ण

अटल व्योम मुक्त_pmd_table(pmd_t *pmd_start, pud_t *pud)
अणु
	pmd_t *pmd;
	पूर्णांक i;

	क्रम (i = 0; i < PTRS_PER_PMD; i++) अणु
		pmd = pmd_start + i;
		अगर (!pmd_none(*pmd))
			वापस;
	पूर्ण

	pmd_मुक्त(&init_mm, pmd_start);
	pud_clear(pud);
पूर्ण

अटल व्योम मुक्त_pud_table(pud_t *pud_start, p4d_t *p4d)
अणु
	pud_t *pud;
	पूर्णांक i;

	क्रम (i = 0; i < PTRS_PER_PUD; i++) अणु
		pud = pud_start + i;
		अगर (!pud_none(*pud))
			वापस;
	पूर्ण

	pud_मुक्त(&init_mm, pud_start);
	p4d_clear(p4d);
पूर्ण

अटल व्योम हटाओ_pte_table(pte_t *pte_start, अचिन्हित दीर्घ addr,
			     अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ next;
	pte_t *pte;

	pte = pte_start + pte_index(addr);
	क्रम (; addr < end; addr = next, pte++) अणु
		next = (addr + PAGE_SIZE) & PAGE_MASK;
		अगर (next > end)
			next = end;

		अगर (!pte_present(*pte))
			जारी;

		अगर (!PAGE_ALIGNED(addr) || !PAGE_ALIGNED(next)) अणु
			/*
			 * The vmemmap_मुक्त() and हटाओ_section_mapping()
			 * codepaths call us with aligned addresses.
			 */
			WARN_ONCE(1, "%s: unaligned range\n", __func__);
			जारी;
		पूर्ण

		pte_clear(&init_mm, addr, pte);
	पूर्ण
पूर्ण

अटल व्योम __meminit हटाओ_pmd_table(pmd_t *pmd_start, अचिन्हित दीर्घ addr,
			     अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ next;
	pte_t *pte_base;
	pmd_t *pmd;

	pmd = pmd_start + pmd_index(addr);
	क्रम (; addr < end; addr = next, pmd++) अणु
		next = pmd_addr_end(addr, end);

		अगर (!pmd_present(*pmd))
			जारी;

		अगर (pmd_is_leaf(*pmd)) अणु
			अगर (!IS_ALIGNED(addr, PMD_SIZE) ||
			    !IS_ALIGNED(next, PMD_SIZE)) अणु
				WARN_ONCE(1, "%s: unaligned range\n", __func__);
				जारी;
			पूर्ण
			pte_clear(&init_mm, addr, (pte_t *)pmd);
			जारी;
		पूर्ण

		pte_base = (pte_t *)pmd_page_vaddr(*pmd);
		हटाओ_pte_table(pte_base, addr, next);
		मुक्त_pte_table(pte_base, pmd);
	पूर्ण
पूर्ण

अटल व्योम __meminit हटाओ_pud_table(pud_t *pud_start, अचिन्हित दीर्घ addr,
			     अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ next;
	pmd_t *pmd_base;
	pud_t *pud;

	pud = pud_start + pud_index(addr);
	क्रम (; addr < end; addr = next, pud++) अणु
		next = pud_addr_end(addr, end);

		अगर (!pud_present(*pud))
			जारी;

		अगर (pud_is_leaf(*pud)) अणु
			अगर (!IS_ALIGNED(addr, PUD_SIZE) ||
			    !IS_ALIGNED(next, PUD_SIZE)) अणु
				WARN_ONCE(1, "%s: unaligned range\n", __func__);
				जारी;
			पूर्ण
			pte_clear(&init_mm, addr, (pte_t *)pud);
			जारी;
		पूर्ण

		pmd_base = (pmd_t *)pud_page_vaddr(*pud);
		हटाओ_pmd_table(pmd_base, addr, next);
		मुक्त_pmd_table(pmd_base, pud);
	पूर्ण
पूर्ण

अटल व्योम __meminit हटाओ_pagetable(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ addr, next;
	pud_t *pud_base;
	pgd_t *pgd;
	p4d_t *p4d;

	spin_lock(&init_mm.page_table_lock);

	क्रम (addr = start; addr < end; addr = next) अणु
		next = pgd_addr_end(addr, end);

		pgd = pgd_offset_k(addr);
		p4d = p4d_offset(pgd, addr);
		अगर (!p4d_present(*p4d))
			जारी;

		अगर (p4d_is_leaf(*p4d)) अणु
			अगर (!IS_ALIGNED(addr, P4D_SIZE) ||
			    !IS_ALIGNED(next, P4D_SIZE)) अणु
				WARN_ONCE(1, "%s: unaligned range\n", __func__);
				जारी;
			पूर्ण

			pte_clear(&init_mm, addr, (pte_t *)pgd);
			जारी;
		पूर्ण

		pud_base = (pud_t *)p4d_page_vaddr(*p4d);
		हटाओ_pud_table(pud_base, addr, next);
		मुक्त_pud_table(pud_base, p4d);
	पूर्ण

	spin_unlock(&init_mm.page_table_lock);
	radix__flush_tlb_kernel_range(start, end);
पूर्ण

पूर्णांक __meminit radix__create_section_mapping(अचिन्हित दीर्घ start,
					    अचिन्हित दीर्घ end, पूर्णांक nid,
					    pgprot_t prot)
अणु
	अगर (end >= RADIX_VMALLOC_START) अणु
		pr_warn("Outside the supported range\n");
		वापस -1;
	पूर्ण

	वापस create_physical_mapping(__pa(start), __pa(end),
				       radix_mem_block_size, nid, prot);
पूर्ण

पूर्णांक __meminit radix__हटाओ_section_mapping(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	हटाओ_pagetable(start, end);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_MEMORY_HOTPLUG */

#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
अटल पूर्णांक __map_kernel_page_nid(अचिन्हित दीर्घ ea, अचिन्हित दीर्घ pa,
				 pgprot_t flags, अचिन्हित पूर्णांक map_page_size,
				 पूर्णांक nid)
अणु
	वापस __map_kernel_page(ea, pa, flags, map_page_size, nid, 0, 0);
पूर्ण

पूर्णांक __meminit radix__vmemmap_create_mapping(अचिन्हित दीर्घ start,
				      अचिन्हित दीर्घ page_size,
				      अचिन्हित दीर्घ phys)
अणु
	/* Create a PTE encoding */
	अचिन्हित दीर्घ flags = _PAGE_PRESENT | _PAGE_ACCESSED | _PAGE_KERNEL_RW;
	पूर्णांक nid = early_pfn_to_nid(phys >> PAGE_SHIFT);
	पूर्णांक ret;

	अगर ((start + page_size) >= RADIX_VMEMMAP_END) अणु
		pr_warn("Outside the supported range\n");
		वापस -1;
	पूर्ण

	ret = __map_kernel_page_nid(start, phys, __pgprot(flags), page_size, nid);
	BUG_ON(ret);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
व्योम __meminit radix__vmemmap_हटाओ_mapping(अचिन्हित दीर्घ start, अचिन्हित दीर्घ page_size)
अणु
	हटाओ_pagetable(start, start + page_size);
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE

अचिन्हित दीर्घ radix__pmd_hugepage_update(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
				  pmd_t *pmdp, अचिन्हित दीर्घ clr,
				  अचिन्हित दीर्घ set)
अणु
	अचिन्हित दीर्घ old;

#अगर_घोषित CONFIG_DEBUG_VM
	WARN_ON(!radix__pmd_trans_huge(*pmdp) && !pmd_devmap(*pmdp));
	निश्चित_spin_locked(pmd_lockptr(mm, pmdp));
#पूर्ण_अगर

	old = radix__pte_update(mm, addr, (pte_t *)pmdp, clr, set, 1);
	trace_hugepage_update(addr, old, clr, set);

	वापस old;
पूर्ण

pmd_t radix__pmdp_collapse_flush(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ address,
			pmd_t *pmdp)

अणु
	pmd_t pmd;

	VM_BUG_ON(address & ~HPAGE_PMD_MASK);
	VM_BUG_ON(radix__pmd_trans_huge(*pmdp));
	VM_BUG_ON(pmd_devmap(*pmdp));
	/*
	 * khugepaged calls this क्रम normal pmd
	 */
	pmd = *pmdp;
	pmd_clear(pmdp);

	/*
	 * pmdp collapse_flush need to ensure that there are no parallel gup
	 * walk after this call. This is needed so that we can have stable
	 * page ref count when collapsing a page. We करोn't allow a collapse page
	 * अगर we have gup taken on the page. We can ensure that by sending IPI
	 * because gup walk happens with IRQ disabled.
	 */
	serialize_against_pte_lookup(vma->vm_mm);

	radix__flush_tlb_collapsed_pmd(vma->vm_mm, address);

	वापस pmd;
पूर्ण

/*
 * For us pgtable_t is pte_t *. Inorder to save the deposisted
 * page table, we consider the allocated page table as a list
 * head. On withdraw we need to make sure we zero out the used
 * list_head memory area.
 */
व्योम radix__pgtable_trans_huge_deposit(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp,
				 pgtable_t pgtable)
अणु
	काष्ठा list_head *lh = (काष्ठा list_head *) pgtable;

	निश्चित_spin_locked(pmd_lockptr(mm, pmdp));

	/* FIFO */
	अगर (!pmd_huge_pte(mm, pmdp))
		INIT_LIST_HEAD(lh);
	अन्यथा
		list_add(lh, (काष्ठा list_head *) pmd_huge_pte(mm, pmdp));
	pmd_huge_pte(mm, pmdp) = pgtable;
पूर्ण

pgtable_t radix__pgtable_trans_huge_withdraw(काष्ठा mm_काष्ठा *mm, pmd_t *pmdp)
अणु
	pte_t *ptep;
	pgtable_t pgtable;
	काष्ठा list_head *lh;

	निश्चित_spin_locked(pmd_lockptr(mm, pmdp));

	/* FIFO */
	pgtable = pmd_huge_pte(mm, pmdp);
	lh = (काष्ठा list_head *) pgtable;
	अगर (list_empty(lh))
		pmd_huge_pte(mm, pmdp) = शून्य;
	अन्यथा अणु
		pmd_huge_pte(mm, pmdp) = (pgtable_t) lh->next;
		list_del(lh);
	पूर्ण
	ptep = (pte_t *) pgtable;
	*ptep = __pte(0);
	ptep++;
	*ptep = __pte(0);
	वापस pgtable;
पूर्ण

pmd_t radix__pmdp_huge_get_and_clear(काष्ठा mm_काष्ठा *mm,
				     अचिन्हित दीर्घ addr, pmd_t *pmdp)
अणु
	pmd_t old_pmd;
	अचिन्हित दीर्घ old;

	old = radix__pmd_hugepage_update(mm, addr, pmdp, ~0UL, 0);
	old_pmd = __pmd(old);
	वापस old_pmd;
पूर्ण

#पूर्ण_अगर /* CONFIG_TRANSPARENT_HUGEPAGE */

व्योम radix__ptep_set_access_flags(काष्ठा vm_area_काष्ठा *vma, pte_t *ptep,
				  pte_t entry, अचिन्हित दीर्घ address, पूर्णांक psize)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;
	अचिन्हित दीर्घ set = pte_val(entry) & (_PAGE_सूचीTY | _PAGE_ACCESSED |
					      _PAGE_RW | _PAGE_EXEC);

	अचिन्हित दीर्घ change = pte_val(entry) ^ pte_val(*ptep);
	/*
	 * To aव्योम NMMU hang जबतक relaxing access, we need mark
	 * the pte invalid in between.
	 */
	अगर ((change & _PAGE_RW) && atomic_पढ़ो(&mm->context.copros) > 0) अणु
		अचिन्हित दीर्घ old_pte, new_pte;

		old_pte = __radix_pte_update(ptep, _PAGE_PRESENT, _PAGE_INVALID);
		/*
		 * new value of pte
		 */
		new_pte = old_pte | set;
		radix__flush_tlb_page_psize(mm, address, psize);
		__radix_pte_update(ptep, _PAGE_INVALID, new_pte);
	पूर्ण अन्यथा अणु
		__radix_pte_update(ptep, 0, set);
		/*
		 * Book3S करोes not require a TLB flush when relaxing access
		 * restrictions when the address space is not attached to a
		 * NMMU, because the core MMU will reload the pte after taking
		 * an access fault, which is defined by the architecture.
		 */
	पूर्ण
	/* See ptesync comment in radix__set_pte_at */
पूर्ण

व्योम radix__ptep_modअगरy_prot_commit(काष्ठा vm_area_काष्ठा *vma,
				    अचिन्हित दीर्घ addr, pte_t *ptep,
				    pte_t old_pte, pte_t pte)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

	/*
	 * To aव्योम NMMU hang जबतक relaxing access we need to flush the tlb beक्रमe
	 * we set the new value. We need to करो this only क्रम radix, because hash
	 * translation करोes flush when updating the linux pte.
	 */
	अगर (is_pte_rw_upgrade(pte_val(old_pte), pte_val(pte)) &&
	    (atomic_पढ़ो(&mm->context.copros) > 0))
		radix__flush_tlb_page(vma, addr);

	set_pte_at(mm, addr, ptep, pte);
पूर्ण

पूर्णांक pud_set_huge(pud_t *pud, phys_addr_t addr, pgprot_t prot)
अणु
	pte_t *ptep = (pte_t *)pud;
	pte_t new_pud = pfn_pte(__phys_to_pfn(addr), prot);

	अगर (!radix_enabled())
		वापस 0;

	set_pte_at(&init_mm, 0 /* radix unused */, ptep, new_pud);

	वापस 1;
पूर्ण

पूर्णांक pud_clear_huge(pud_t *pud)
अणु
	अगर (pud_huge(*pud)) अणु
		pud_clear(pud);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक pud_मुक्त_pmd_page(pud_t *pud, अचिन्हित दीर्घ addr)
अणु
	pmd_t *pmd;
	पूर्णांक i;

	pmd = (pmd_t *)pud_page_vaddr(*pud);
	pud_clear(pud);

	flush_tlb_kernel_range(addr, addr + PUD_SIZE);

	क्रम (i = 0; i < PTRS_PER_PMD; i++) अणु
		अगर (!pmd_none(pmd[i])) अणु
			pte_t *pte;
			pte = (pte_t *)pmd_page_vaddr(pmd[i]);

			pte_मुक्त_kernel(&init_mm, pte);
		पूर्ण
	पूर्ण

	pmd_मुक्त(&init_mm, pmd);

	वापस 1;
पूर्ण

पूर्णांक pmd_set_huge(pmd_t *pmd, phys_addr_t addr, pgprot_t prot)
अणु
	pte_t *ptep = (pte_t *)pmd;
	pte_t new_pmd = pfn_pte(__phys_to_pfn(addr), prot);

	अगर (!radix_enabled())
		वापस 0;

	set_pte_at(&init_mm, 0 /* radix unused */, ptep, new_pmd);

	वापस 1;
पूर्ण

पूर्णांक pmd_clear_huge(pmd_t *pmd)
अणु
	अगर (pmd_huge(*pmd)) अणु
		pmd_clear(pmd);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक pmd_मुक्त_pte_page(pmd_t *pmd, अचिन्हित दीर्घ addr)
अणु
	pte_t *pte;

	pte = (pte_t *)pmd_page_vaddr(*pmd);
	pmd_clear(pmd);

	flush_tlb_kernel_range(addr, addr + PMD_SIZE);

	pte_मुक्त_kernel(&init_mm, pte);

	वापस 1;
पूर्ण
