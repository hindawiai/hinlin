<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Initialize MMU support.
 *
 * Copyright (C) 1998-2003 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>

#समावेश <linux/dma-map-ops.h>
#समावेश <linux/dmar.h>
#समावेश <linux/efi.h>
#समावेश <linux/elf.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/mmzone.h>
#समावेश <linux/module.h>
#समावेश <linux/personality.h>
#समावेश <linux/reboot.h>
#समावेश <linux/slab.h>
#समावेश <linux/swap.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/bitops.h>
#समावेश <linux/kexec.h>
#समावेश <linux/swiotlb.h>

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/efi.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/patch.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/sal.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/tlb.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/mca.h>

बाह्य व्योम ia64_tlb_init (व्योम);

अचिन्हित दीर्घ MAX_DMA_ADDRESS = PAGE_OFFSET + 0x100000000UL;

काष्ठा page *zero_page_memmap_ptr;	/* map entry क्रम zero page */
EXPORT_SYMBOL(zero_page_memmap_ptr);

व्योम
__ia64_sync_icache_dcache (pte_t pte)
अणु
	अचिन्हित दीर्घ addr;
	काष्ठा page *page;

	page = pte_page(pte);
	addr = (अचिन्हित दीर्घ) page_address(page);

	अगर (test_bit(PG_arch_1, &page->flags))
		वापस;				/* i-cache is alपढ़ोy coherent with d-cache */

	flush_icache_range(addr, addr + page_size(page));
	set_bit(PG_arch_1, &page->flags);	/* mark page as clean */
पूर्ण

/*
 * Since DMA is i-cache coherent, any (complete) pages that were written via
 * DMA can be marked as "clean" so that lazy_mmu_prot_update() करोesn't have to
 * flush them when they get mapped पूर्णांकo an executable vm-area.
 */
व्योम arch_dma_mark_clean(phys_addr_t paddr, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ pfn = PHYS_PFN(paddr);

	करो अणु
		set_bit(PG_arch_1, &pfn_to_page(pfn)->flags);
	पूर्ण जबतक (++pfn <= PHYS_PFN(paddr + size - 1));
पूर्ण

अंतरभूत व्योम
ia64_set_rbs_bot (व्योम)
अणु
	अचिन्हित दीर्घ stack_size = rlimit_max(RLIMIT_STACK) & -16;

	अगर (stack_size > MAX_USER_STACK_SIZE)
		stack_size = MAX_USER_STACK_SIZE;
	current->thपढ़ो.rbs_bot = PAGE_ALIGN(current->mm->start_stack - stack_size);
पूर्ण

/*
 * This perक्रमms some platक्रमm-dependent address space initialization.
 * On IA-64, we want to setup the VM area क्रम the रेजिस्टर backing
 * store (which grows upwards) and install the gateway page which is
 * used क्रम संकेत trampolines, etc.
 */
व्योम
ia64_init_addr_space (व्योम)
अणु
	काष्ठा vm_area_काष्ठा *vma;

	ia64_set_rbs_bot();

	/*
	 * If we're out of memory and kmem_cache_alloc() वापसs शून्य, we simply ignore
	 * the problem.  When the process attempts to ग_लिखो to the रेजिस्टर backing store
	 * क्रम the first समय, it will get a SEGFAULT in this हाल.
	 */
	vma = vm_area_alloc(current->mm);
	अगर (vma) अणु
		vma_set_anonymous(vma);
		vma->vm_start = current->thपढ़ो.rbs_bot & PAGE_MASK;
		vma->vm_end = vma->vm_start + PAGE_SIZE;
		vma->vm_flags = VM_DATA_DEFAULT_FLAGS|VM_GROWSUP|VM_ACCOUNT;
		vma->vm_page_prot = vm_get_page_prot(vma->vm_flags);
		mmap_ग_लिखो_lock(current->mm);
		अगर (insert_vm_काष्ठा(current->mm, vma)) अणु
			mmap_ग_लिखो_unlock(current->mm);
			vm_area_मुक्त(vma);
			वापस;
		पूर्ण
		mmap_ग_लिखो_unlock(current->mm);
	पूर्ण

	/* map NaT-page at address zero to speed up speculative dereferencing of शून्य: */
	अगर (!(current->personality & MMAP_PAGE_ZERO)) अणु
		vma = vm_area_alloc(current->mm);
		अगर (vma) अणु
			vma_set_anonymous(vma);
			vma->vm_end = PAGE_SIZE;
			vma->vm_page_prot = __pgprot(pgprot_val(PAGE_READONLY) | _PAGE_MA_NAT);
			vma->vm_flags = VM_READ | VM_MAYREAD | VM_IO |
					VM_DONTEXPAND | VM_DONTDUMP;
			mmap_ग_लिखो_lock(current->mm);
			अगर (insert_vm_काष्ठा(current->mm, vma)) अणु
				mmap_ग_लिखो_unlock(current->mm);
				vm_area_मुक्त(vma);
				वापस;
			पूर्ण
			mmap_ग_लिखो_unlock(current->mm);
		पूर्ण
	पूर्ण
पूर्ण

व्योम
मुक्त_iniपंचांगem (व्योम)
अणु
	मुक्त_reserved_area(ia64_imva(__init_begin), ia64_imva(__init_end),
			   -1, "unused kernel");
पूर्ण

व्योम __init
मुक्त_initrd_mem (अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	/*
	 * EFI uses 4KB pages जबतक the kernel can use 4KB or bigger.
	 * Thus EFI and the kernel may have dअगरferent page sizes. It is
	 * thereक्रमe possible to have the initrd share the same page as
	 * the end of the kernel (given current setup).
	 *
	 * To aव्योम मुक्तing/using the wrong page (kernel sized) we:
	 *	- align up the beginning of initrd
	 *	- align करोwn the end of initrd
	 *
	 *  |             |
	 *  |=============| a000
	 *  |             |
	 *  |             |
	 *  |             | 9000
	 *  |/////////////|
	 *  |/////////////|
	 *  |=============| 8000
	 *  |///INITRD////|
	 *  |/////////////|
	 *  |/////////////| 7000
	 *  |             |
	 *  |KKKKKKKKKKKKK|
	 *  |=============| 6000
	 *  |KKKKKKKKKKKKK|
	 *  |KKKKKKKKKKKKK|
	 *  K=kernel using 8KB pages
	 *
	 * In this example, we must मुक्त page 8000 ONLY. So we must align up
	 * initrd_start and keep initrd_end as is.
	 */
	start = PAGE_ALIGN(start);
	end = end & PAGE_MASK;

	अगर (start < end)
		prपूर्णांकk(KERN_INFO "Freeing initrd memory: %ldkB freed\n", (end - start) >> 10);

	क्रम (; start < end; start += PAGE_SIZE) अणु
		अगर (!virt_addr_valid(start))
			जारी;
		मुक्त_reserved_page(virt_to_page(start));
	पूर्ण
पूर्ण

/*
 * This installs a clean page in the kernel's page table.
 */
अटल काष्ठा page * __init
put_kernel_page (काष्ठा page *page, अचिन्हित दीर्घ address, pgprot_t pgprot)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	pgd = pgd_offset_k(address);		/* note: this is NOT pgd_offset()! */

	अणु
		p4d = p4d_alloc(&init_mm, pgd, address);
		अगर (!p4d)
			जाओ out;
		pud = pud_alloc(&init_mm, p4d, address);
		अगर (!pud)
			जाओ out;
		pmd = pmd_alloc(&init_mm, pud, address);
		अगर (!pmd)
			जाओ out;
		pte = pte_alloc_kernel(pmd, address);
		अगर (!pte)
			जाओ out;
		अगर (!pte_none(*pte))
			जाओ out;
		set_pte(pte, mk_pte(page, pgprot));
	पूर्ण
  out:
	/* no need क्रम flush_tlb */
	वापस page;
पूर्ण

अटल व्योम __init
setup_gate (व्योम)
अणु
	काष्ठा page *page;

	/*
	 * Map the gate page twice: once पढ़ो-only to export the ELF
	 * headers etc. and once execute-only page to enable
	 * privilege-promotion via "epc":
	 */
	page = virt_to_page(ia64_imva(__start_gate_section));
	put_kernel_page(page, GATE_ADDR, PAGE_READONLY);
#अगर_घोषित HAVE_BUGGY_SEGREL
	page = virt_to_page(ia64_imva(__start_gate_section + PAGE_SIZE));
	put_kernel_page(page, GATE_ADDR + PAGE_SIZE, PAGE_GATE);
#अन्यथा
	put_kernel_page(page, GATE_ADDR + PERCPU_PAGE_SIZE, PAGE_GATE);
	/* Fill in the holes (अगर any) with पढ़ो-only zero pages: */
	अणु
		अचिन्हित दीर्घ addr;

		क्रम (addr = GATE_ADDR + PAGE_SIZE;
		     addr < GATE_ADDR + PERCPU_PAGE_SIZE;
		     addr += PAGE_SIZE)
		अणु
			put_kernel_page(ZERO_PAGE(0), addr,
					PAGE_READONLY);
			put_kernel_page(ZERO_PAGE(0), addr + PERCPU_PAGE_SIZE,
					PAGE_READONLY);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	ia64_patch_gate();
पूर्ण

अटल काष्ठा vm_area_काष्ठा gate_vma;

अटल पूर्णांक __init gate_vma_init(व्योम)
अणु
	vma_init(&gate_vma, शून्य);
	gate_vma.vm_start = FIXADDR_USER_START;
	gate_vma.vm_end = FIXADDR_USER_END;
	gate_vma.vm_flags = VM_READ | VM_MAYREAD | VM_EXEC | VM_MAYEXEC;
	gate_vma.vm_page_prot = __P101;

	वापस 0;
पूर्ण
__initcall(gate_vma_init);

काष्ठा vm_area_काष्ठा *get_gate_vma(काष्ठा mm_काष्ठा *mm)
अणु
	वापस &gate_vma;
पूर्ण

पूर्णांक in_gate_area_no_mm(अचिन्हित दीर्घ addr)
अणु
	अगर ((addr >= FIXADDR_USER_START) && (addr < FIXADDR_USER_END))
		वापस 1;
	वापस 0;
पूर्ण

पूर्णांक in_gate_area(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	वापस in_gate_area_no_mm(addr);
पूर्ण

व्योम ia64_mmu_init(व्योम *my_cpu_data)
अणु
	अचिन्हित दीर्घ pta, impl_va_bits;
	बाह्य व्योम tlb_init(व्योम);

#अगर_घोषित CONFIG_DISABLE_VHPT
#	define VHPT_ENABLE_BIT	0
#अन्यथा
#	define VHPT_ENABLE_BIT	1
#पूर्ण_अगर

	/*
	 * Check अगर the भवly mapped linear page table (VMLPT) overlaps with a mapped
	 * address space.  The IA-64 architecture guarantees that at least 50 bits of
	 * भव address space are implemented but अगर we pick a large enough page size
	 * (e.g., 64KB), the mapped address space is big enough that it will overlap with
	 * VMLPT.  I assume that once we run on machines big enough to warrant 64KB pages,
	 * IMPL_VA_MSB will be signअगरicantly bigger, so this is unlikely to become a
	 * problem in practice.  Alternatively, we could truncate the top of the mapped
	 * address space to not permit mappings that would overlap with the VMLPT.
	 * --davidm 00/12/06
	 */
#	define pte_bits			3
#	define mapped_space_bits	(3*(PAGE_SHIFT - pte_bits) + PAGE_SHIFT)
	/*
	 * The भव page table has to cover the entire implemented address space within
	 * a region even though not all of this space may be mappable.  The reason क्रम
	 * this is that the Access bit and Dirty bit fault handlers perक्रमm
	 * non-speculative accesses to the भव page table, so the address range of the
	 * भव page table itself needs to be covered by भव page table.
	 */
#	define vmlpt_bits		(impl_va_bits - PAGE_SHIFT + pte_bits)
#	define POW2(n)			(1ULL << (n))

	impl_va_bits = ffz(~(local_cpu_data->unimpl_va_mask | (7UL << 61)));

	अगर (impl_va_bits < 51 || impl_va_bits > 61)
		panic("CPU has bogus IMPL_VA_MSB value of %lu!\n", impl_va_bits - 1);
	/*
	 * mapped_space_bits - PAGE_SHIFT is the total number of ptes we need,
	 * which must fit पूर्णांकo "vmlpt_bits - pte_bits" slots. Second half of
	 * the test makes sure that our mapped space करोesn't overlap the
	 * unimplemented hole in the middle of the region.
	 */
	अगर ((mapped_space_bits - PAGE_SHIFT > vmlpt_bits - pte_bits) ||
	    (mapped_space_bits > impl_va_bits - 1))
		panic("Cannot build a big enough virtual-linear page table"
		      " to cover mapped address space.\n"
		      " Try using a smaller page size.\n");


	/* place the VMLPT at the end of each page-table mapped region: */
	pta = POW2(61) - POW2(vmlpt_bits);

	/*
	 * Set the (भवly mapped linear) page table address.  Bit
	 * 8 selects between the लघु and दीर्घ क्रमmat, bits 2-7 the
	 * size of the table, and bit 0 whether the VHPT walker is
	 * enabled.
	 */
	ia64_set_pta(pta | (0 << 8) | (vmlpt_bits << 2) | VHPT_ENABLE_BIT);

	ia64_tlb_init();

#अगर_घोषित	CONFIG_HUGETLB_PAGE
	ia64_set_rr(HPAGE_REGION_BASE, HPAGE_SHIFT << 2);
	ia64_srlz_d();
#पूर्ण_अगर
पूर्ण

पूर्णांक __init रेजिस्टर_active_ranges(u64 start, u64 len, पूर्णांक nid)
अणु
	u64 end = start + len;

#अगर_घोषित CONFIG_KEXEC
	अगर (start > crashk_res.start && start < crashk_res.end)
		start = crashk_res.end;
	अगर (end > crashk_res.start && end < crashk_res.end)
		end = crashk_res.start;
#पूर्ण_अगर

	अगर (start < end)
		memblock_add_node(__pa(start), end - start, nid);
	वापस 0;
पूर्ण

पूर्णांक
find_max_min_low_pfn (u64 start, u64 end, व्योम *arg)
अणु
	अचिन्हित दीर्घ pfn_start, pfn_end;
#अगर_घोषित CONFIG_FLATMEM
	pfn_start = (PAGE_ALIGN(__pa(start))) >> PAGE_SHIFT;
	pfn_end = (PAGE_ALIGN(__pa(end - 1))) >> PAGE_SHIFT;
#अन्यथा
	pfn_start = GRANULEROUNDDOWN(__pa(start)) >> PAGE_SHIFT;
	pfn_end = GRANULEROUNDUP(__pa(end - 1)) >> PAGE_SHIFT;
#पूर्ण_अगर
	min_low_pfn = min(min_low_pfn, pfn_start);
	max_low_pfn = max(max_low_pfn, pfn_end);
	वापस 0;
पूर्ण

/*
 * Boot command-line option "nolwsys" can be used to disable the use of any light-weight
 * प्रणाली call handler.  When this option is in effect, all fsyscalls will end up bubbling
 * करोwn पूर्णांकo the kernel and calling the normal (heavy-weight) syscall handler.  This is
 * useful क्रम perक्रमmance testing, but conceivably could also come in handy क्रम debugging
 * purposes.
 */

अटल पूर्णांक nolwsys __initdata;

अटल पूर्णांक __init
nolwsys_setup (अक्षर *s)
अणु
	nolwsys = 1;
	वापस 1;
पूर्ण

__setup("nolwsys", nolwsys_setup);

व्योम __init
mem_init (व्योम)
अणु
	पूर्णांक i;

	BUG_ON(PTRS_PER_PGD * माप(pgd_t) != PAGE_SIZE);
	BUG_ON(PTRS_PER_PMD * माप(pmd_t) != PAGE_SIZE);
	BUG_ON(PTRS_PER_PTE * माप(pte_t) != PAGE_SIZE);

	/*
	 * This needs to be called _after_ the command line has been parsed but
	 * _beक्रमe_ any drivers that may need the PCI DMA पूर्णांकerface are
	 * initialized or booपंचांगem has been मुक्तd.
	 */
	करो अणु
#अगर_घोषित CONFIG_INTEL_IOMMU
		detect_पूर्णांकel_iommu();
		अगर (iommu_detected)
			अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SWIOTLB
		swiotlb_init(1);
#पूर्ण_अगर
	पूर्ण जबतक (0);

#अगर_घोषित CONFIG_FLATMEM
	BUG_ON(!mem_map);
#पूर्ण_अगर

	set_max_mapnr(max_low_pfn);
	high_memory = __va(max_low_pfn * PAGE_SIZE);
	memblock_मुक्त_all();

	/*
	 * For fsyscall entrpoपूर्णांकs with no light-weight handler, use the ordinary
	 * (heavy-weight) handler, but mark it by setting bit 0, so the fsyscall entry
	 * code can tell them apart.
	 */
	क्रम (i = 0; i < NR_syscalls; ++i) अणु
		बाह्य अचिन्हित दीर्घ fsyscall_table[NR_syscalls];
		बाह्य अचिन्हित दीर्घ sys_call_table[NR_syscalls];

		अगर (!fsyscall_table[i] || nolwsys)
			fsyscall_table[i] = sys_call_table[i] | 1;
	पूर्ण
	setup_gate();
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
पूर्णांक arch_add_memory(पूर्णांक nid, u64 start, u64 size,
		    काष्ठा mhp_params *params)
अणु
	अचिन्हित दीर्घ start_pfn = start >> PAGE_SHIFT;
	अचिन्हित दीर्घ nr_pages = size >> PAGE_SHIFT;
	पूर्णांक ret;

	अगर (WARN_ON_ONCE(params->pgprot.pgprot != PAGE_KERNEL.pgprot))
		वापस -EINVAL;

	ret = __add_pages(nid, start_pfn, nr_pages, params);
	अगर (ret)
		prपूर्णांकk("%s: Problem encountered in __add_pages() as ret=%d\n",
		       __func__,  ret);

	वापस ret;
पूर्ण

व्योम arch_हटाओ_memory(पूर्णांक nid, u64 start, u64 size,
			काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ start_pfn = start >> PAGE_SHIFT;
	अचिन्हित दीर्घ nr_pages = size >> PAGE_SHIFT;

	__हटाओ_pages(start_pfn, nr_pages, alपंचांगap);
पूर्ण
#पूर्ण_अगर
