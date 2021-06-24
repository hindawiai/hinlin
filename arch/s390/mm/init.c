<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  S390 version
 *    Copyright IBM Corp. 1999
 *    Author(s): Harपंचांगut Penner (hp@de.ibm.com)
 *
 *  Derived from "arch/i386/mm/init.c"
 *    Copyright (C) 1995  Linus Torvalds
 */

#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mman.h>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/swiotlb.h>
#समावेश <linux/smp.h>
#समावेश <linux/init.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/memblock.h>
#समावेश <linux/memory.h>
#समावेश <linux/pfn.h>
#समावेश <linux/poison.h>
#समावेश <linux/initrd.h>
#समावेश <linux/export.h>
#समावेश <linux/cma.h>
#समावेश <linux/gfp.h>
#समावेश <linux/dma-direct.h>
#समावेश <यंत्र/processor.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/ptdump.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/lowcore.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/ctl_reg.h>
#समावेश <यंत्र/sclp.h>
#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/kasan.h>
#समावेश <यंत्र/dma-mapping.h>
#समावेश <यंत्र/uv.h>
#समावेश <linux/virtio_config.h>

pgd_t swapper_pg_dir[PTRS_PER_PGD] __section(".bss..swapper_pg_dir");
अटल pgd_t invalid_pg_dir[PTRS_PER_PGD] __section(".bss..invalid_pg_dir");

अचिन्हित दीर्घ s390_invalid_asce;

अचिन्हित दीर्घ empty_zero_page, zero_page_mask;
EXPORT_SYMBOL(empty_zero_page);
EXPORT_SYMBOL(zero_page_mask);

bool iniपंचांगem_मुक्तd;

अटल व्योम __init setup_zero_pages(व्योम)
अणु
	अचिन्हित पूर्णांक order;
	काष्ठा page *page;
	पूर्णांक i;

	/* Latest machines require a mapping granularity of 512KB */
	order = 7;

	/* Limit number of empty zero pages क्रम small memory sizes */
	जबतक (order > 2 && (totalram_pages() >> 10) < (1UL << order))
		order--;

	empty_zero_page = __get_मुक्त_pages(GFP_KERNEL | __GFP_ZERO, order);
	अगर (!empty_zero_page)
		panic("Out of memory in setup_zero_pages");

	page = virt_to_page((व्योम *) empty_zero_page);
	split_page(page, order);
	क्रम (i = 1 << order; i > 0; i--) अणु
		mark_page_reserved(page);
		page++;
	पूर्ण

	zero_page_mask = ((PAGE_SIZE << order) - 1) & PAGE_MASK;
पूर्ण

/*
 * paging_init() sets up the page tables
 */
व्योम __init paging_init(व्योम)
अणु
	अचिन्हित दीर्घ max_zone_pfns[MAX_NR_ZONES];
	अचिन्हित दीर्घ pgd_type, asce_bits;
	psw_t psw;

	s390_invalid_asce  = (अचिन्हित दीर्घ)invalid_pg_dir;
	s390_invalid_asce |= _ASCE_TYPE_REGION3 | _ASCE_TABLE_LENGTH;
	crst_table_init((अचिन्हित दीर्घ *)invalid_pg_dir, _REGION3_ENTRY_EMPTY);
	init_mm.pgd = swapper_pg_dir;
	अगर (VMALLOC_END > _REGION2_SIZE) अणु
		asce_bits = _ASCE_TYPE_REGION2 | _ASCE_TABLE_LENGTH;
		pgd_type = _REGION2_ENTRY_EMPTY;
	पूर्ण अन्यथा अणु
		asce_bits = _ASCE_TYPE_REGION3 | _ASCE_TABLE_LENGTH;
		pgd_type = _REGION3_ENTRY_EMPTY;
	पूर्ण
	init_mm.context.asce = (__pa(init_mm.pgd) & PAGE_MASK) | asce_bits;
	S390_lowcore.kernel_asce = init_mm.context.asce;
	S390_lowcore.user_asce = s390_invalid_asce;
	crst_table_init((अचिन्हित दीर्घ *) init_mm.pgd, pgd_type);
	vmem_map_init();
	kasan_copy_shaकरोw_mapping();

	/* enable भव mapping in kernel mode */
	__ctl_load(S390_lowcore.kernel_asce, 1, 1);
	__ctl_load(S390_lowcore.user_asce, 7, 7);
	__ctl_load(S390_lowcore.kernel_asce, 13, 13);
	psw.mask = __extract_psw();
	psw_bits(psw).dat = 1;
	psw_bits(psw).as = PSW_BITS_AS_HOME;
	__load_psw_mask(psw.mask);
	kasan_मुक्त_early_identity();

	sparse_init();
	zone_dma_bits = 31;
	स_रखो(max_zone_pfns, 0, माप(max_zone_pfns));
	max_zone_pfns[ZONE_DMA] = PFN_DOWN(MAX_DMA_ADDRESS);
	max_zone_pfns[ZONE_NORMAL] = max_low_pfn;
	मुक्त_area_init(max_zone_pfns);
पूर्ण

व्योम mark_rodata_ro(व्योम)
अणु
	अचिन्हित दीर्घ size = __end_ro_after_init - __start_ro_after_init;

	set_memory_ro((अचिन्हित दीर्घ)__start_ro_after_init, size >> PAGE_SHIFT);
	pr_info("Write protected read-only-after-init data: %luk\n", size >> 10);
	debug_checkwx();
पूर्ण

पूर्णांक set_memory_encrypted(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	पूर्णांक i;

	/* make specअगरied pages unshared, (swiotlb, dma_मुक्त) */
	क्रम (i = 0; i < numpages; ++i) अणु
		uv_हटाओ_shared(addr);
		addr += PAGE_SIZE;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक set_memory_decrypted(अचिन्हित दीर्घ addr, पूर्णांक numpages)
अणु
	पूर्णांक i;
	/* make specअगरied pages shared (swiotlb, dma_alloca) */
	क्रम (i = 0; i < numpages; ++i) अणु
		uv_set_shared(addr);
		addr += PAGE_SIZE;
	पूर्ण
	वापस 0;
पूर्ण

/* are we a रक्षित भवization guest? */
bool क्रमce_dma_unencrypted(काष्ठा device *dev)
अणु
	वापस is_prot_virt_guest();
पूर्ण

#अगर_घोषित CONFIG_ARCH_HAS_RESTRICTED_VIRTIO_MEMORY_ACCESS

पूर्णांक arch_has_restricted_virtio_memory_access(व्योम)
अणु
	वापस is_prot_virt_guest();
पूर्ण
EXPORT_SYMBOL(arch_has_restricted_virtio_memory_access);

#पूर्ण_अगर

/* रक्षित भवization */
अटल व्योम pv_init(व्योम)
अणु
	अगर (!is_prot_virt_guest())
		वापस;

	/* make sure bounce buffers are shared */
	swiotlb_init(1);
	swiotlb_update_mem_attributes();
	swiotlb_क्रमce = SWIOTLB_FORCE;
पूर्ण

व्योम __init mem_init(व्योम)
अणु
	cpumask_set_cpu(0, &init_mm.context.cpu_attach_mask);
	cpumask_set_cpu(0, mm_cpumask(&init_mm));

	set_max_mapnr(max_low_pfn);
        high_memory = (व्योम *) __va(max_low_pfn * PAGE_SIZE);

	pv_init();

	/* Setup guest page hपूर्णांकing */
	cmma_init();

	/* this will put all low memory onto the मुक्तlists */
	memblock_मुक्त_all();
	setup_zero_pages();	/* Setup zeroed pages. */

	cmma_init_nodat();
पूर्ण

व्योम मुक्त_iniपंचांगem(व्योम)
अणु
	iniपंचांगem_मुक्तd = true;
	__set_memory((अचिन्हित दीर्घ)_sinittext,
		     (अचिन्हित दीर्घ)(_einittext - _sinittext) >> PAGE_SHIFT,
		     SET_MEMORY_RW | SET_MEMORY_NX);
	मुक्त_iniपंचांगem_शेष(POISON_FREE_INITMEM);
पूर्ण

अचिन्हित दीर्घ memory_block_size_bytes(व्योम)
अणु
	/*
	 * Make sure the memory block size is always greater
	 * or equal than the memory increment size.
	 */
	वापस max_t(अचिन्हित दीर्घ, MIN_MEMORY_BLOCK_SIZE, sclp.rzm);
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG

#अगर_घोषित CONFIG_CMA

/* Prevent memory blocks which contain cma regions from going offline */

काष्ठा s390_cma_mem_data अणु
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
पूर्ण;

अटल पूर्णांक s390_cma_check_range(काष्ठा cma *cma, व्योम *data)
अणु
	काष्ठा s390_cma_mem_data *mem_data;
	अचिन्हित दीर्घ start, end;

	mem_data = data;
	start = cma_get_base(cma);
	end = start + cma_get_size(cma);
	अगर (end < mem_data->start)
		वापस 0;
	अगर (start >= mem_data->end)
		वापस 0;
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक s390_cma_mem_notअगरier(काष्ठा notअगरier_block *nb,
				 अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा s390_cma_mem_data mem_data;
	काष्ठा memory_notअगरy *arg;
	पूर्णांक rc = 0;

	arg = data;
	mem_data.start = arg->start_pfn << PAGE_SHIFT;
	mem_data.end = mem_data.start + (arg->nr_pages << PAGE_SHIFT);
	अगर (action == MEM_GOING_OFFLINE)
		rc = cma_क्रम_each_area(s390_cma_check_range, &mem_data);
	वापस notअगरier_from_त्रुटि_सं(rc);
पूर्ण

अटल काष्ठा notअगरier_block s390_cma_mem_nb = अणु
	.notअगरier_call = s390_cma_mem_notअगरier,
पूर्ण;

अटल पूर्णांक __init s390_cma_mem_init(व्योम)
अणु
	वापस रेजिस्टर_memory_notअगरier(&s390_cma_mem_nb);
पूर्ण
device_initcall(s390_cma_mem_init);

#पूर्ण_अगर /* CONFIG_CMA */

पूर्णांक arch_add_memory(पूर्णांक nid, u64 start, u64 size,
		    काष्ठा mhp_params *params)
अणु
	अचिन्हित दीर्घ start_pfn = PFN_DOWN(start);
	अचिन्हित दीर्घ size_pages = PFN_DOWN(size);
	पूर्णांक rc;

	अगर (WARN_ON_ONCE(params->alपंचांगap))
		वापस -EINVAL;

	अगर (WARN_ON_ONCE(params->pgprot.pgprot != PAGE_KERNEL.pgprot))
		वापस -EINVAL;

	VM_BUG_ON(!mhp_range_allowed(start, size, true));
	rc = vmem_add_mapping(start, size);
	अगर (rc)
		वापस rc;

	rc = __add_pages(nid, start_pfn, size_pages, params);
	अगर (rc)
		vmem_हटाओ_mapping(start, size);
	वापस rc;
पूर्ण

व्योम arch_हटाओ_memory(पूर्णांक nid, u64 start, u64 size,
			काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ start_pfn = start >> PAGE_SHIFT;
	अचिन्हित दीर्घ nr_pages = size >> PAGE_SHIFT;

	__हटाओ_pages(start_pfn, nr_pages, alपंचांगap);
	vmem_हटाओ_mapping(start, size);
पूर्ण
#पूर्ण_अगर /* CONFIG_MEMORY_HOTPLUG */
