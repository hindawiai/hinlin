<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 * Copyright (C) 2019 Western Digital Corporation or its affiliates.
 * Copyright (C) 2020 FORTH-ICS/CARV
 *  Nick Kossअगरidis <mick@ics.क्रमth.gr>
 */

#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/memblock.h>
#समावेश <linux/initrd.h>
#समावेश <linux/swap.h>
#समावेश <linux/sizes.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/libfdt.h>
#समावेश <linux/set_memory.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/crash_dump.h>

#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/soc.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/ptdump.h>
#समावेश <यंत्र/numa.h>

#समावेश "../kernel/head.h"

अचिन्हित दीर्घ kernel_virt_addr = KERNEL_LINK_ADDR;
EXPORT_SYMBOL(kernel_virt_addr);
#अगर_घोषित CONFIG_XIP_KERNEL
#घोषणा kernel_virt_addr       (*((अचिन्हित दीर्घ *)XIP_FIXUP(&kernel_virt_addr)))
#पूर्ण_अगर

अचिन्हित दीर्घ empty_zero_page[PAGE_SIZE / माप(अचिन्हित दीर्घ)]
							__page_aligned_bss;
EXPORT_SYMBOL(empty_zero_page);

बाह्य अक्षर _start[];
#घोषणा DTB_EARLY_BASE_VA      PGसूची_SIZE
व्योम *_dtb_early_va __initdata;
uपूर्णांकptr_t _dtb_early_pa __initdata;

काष्ठा pt_alloc_ops अणु
	pte_t *(*get_pte_virt)(phys_addr_t pa);
	phys_addr_t (*alloc_pte)(uपूर्णांकptr_t va);
#अगर_अघोषित __PAGETABLE_PMD_FOLDED
	pmd_t *(*get_pmd_virt)(phys_addr_t pa);
	phys_addr_t (*alloc_pmd)(uपूर्णांकptr_t va);
#पूर्ण_अगर
पूर्ण;

अटल phys_addr_t dma32_phys_limit __ro_after_init;

अटल व्योम __init zone_sizes_init(व्योम)
अणु
	अचिन्हित दीर्घ max_zone_pfns[MAX_NR_ZONES] = अणु 0, पूर्ण;

#अगर_घोषित CONFIG_ZONE_DMA32
	max_zone_pfns[ZONE_DMA32] = PFN_DOWN(dma32_phys_limit);
#पूर्ण_अगर
	max_zone_pfns[ZONE_NORMAL] = max_low_pfn;

	मुक्त_area_init(max_zone_pfns);
पूर्ण

अटल व्योम __init setup_zero_page(व्योम)
अणु
	स_रखो((व्योम *)empty_zero_page, 0, PAGE_SIZE);
पूर्ण

#अगर defined(CONFIG_MMU) && defined(CONFIG_DEBUG_VM)
अटल अंतरभूत व्योम prपूर्णांक_mlk(अक्षर *name, अचिन्हित दीर्घ b, अचिन्हित दीर्घ t)
अणु
	pr_notice("%12s : 0x%08lx - 0x%08lx   (%4ld kB)\n", name, b, t,
		  (((t) - (b)) >> 10));
पूर्ण

अटल अंतरभूत व्योम prपूर्णांक_mlm(अक्षर *name, अचिन्हित दीर्घ b, अचिन्हित दीर्घ t)
अणु
	pr_notice("%12s : 0x%08lx - 0x%08lx   (%4ld MB)\n", name, b, t,
		  (((t) - (b)) >> 20));
पूर्ण

अटल व्योम __init prपूर्णांक_vm_layout(व्योम)
अणु
	pr_notice("Virtual kernel memory layout:\n");
	prपूर्णांक_mlk("fixmap", (अचिन्हित दीर्घ)FIXADDR_START,
		  (अचिन्हित दीर्घ)FIXADDR_TOP);
	prपूर्णांक_mlm("pci io", (अचिन्हित दीर्घ)PCI_IO_START,
		  (अचिन्हित दीर्घ)PCI_IO_END);
	prपूर्णांक_mlm("vmemmap", (अचिन्हित दीर्घ)VMEMMAP_START,
		  (अचिन्हित दीर्घ)VMEMMAP_END);
	prपूर्णांक_mlm("vmalloc", (अचिन्हित दीर्घ)VMALLOC_START,
		  (अचिन्हित दीर्घ)VMALLOC_END);
	prपूर्णांक_mlm("lowmem", (अचिन्हित दीर्घ)PAGE_OFFSET,
		  (अचिन्हित दीर्घ)high_memory);
#अगर_घोषित CONFIG_64BIT
	prपूर्णांक_mlm("kernel", (अचिन्हित दीर्घ)KERNEL_LINK_ADDR,
		  (अचिन्हित दीर्घ)ADDRESS_SPACE_END);
#पूर्ण_अगर
पूर्ण
#अन्यथा
अटल व्योम prपूर्णांक_vm_layout(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_VM */

व्योम __init mem_init(व्योम)
अणु
#अगर_घोषित CONFIG_FLATMEM
	BUG_ON(!mem_map);
#पूर्ण_अगर /* CONFIG_FLATMEM */

	high_memory = (व्योम *)(__va(PFN_PHYS(max_low_pfn)));
	memblock_मुक्त_all();

	prपूर्णांक_vm_layout();
पूर्ण

व्योम __init setup_booपंचांगem(व्योम)
अणु
	phys_addr_t vmlinux_end = __pa_symbol(&_end);
	phys_addr_t vmlinux_start = __pa_symbol(&_start);
	phys_addr_t dram_end = memblock_end_of_DRAM();
	phys_addr_t max_mapped_addr = __pa(~(uदीर्घ)0);

#अगर_घोषित CONFIG_XIP_KERNEL
	vmlinux_start = __pa_symbol(&_sdata);
#पूर्ण_अगर

	/* The maximal physical memory size is -PAGE_OFFSET. */
	memblock_enक्रमce_memory_limit(-PAGE_OFFSET);

	/*
	 * Reserve from the start of the kernel to the end of the kernel
	 */
#अगर defined(CONFIG_64BIT) && defined(CONFIG_STRICT_KERNEL_RWX)
	/*
	 * Make sure we align the reservation on PMD_SIZE since we will
	 * map the kernel in the linear mapping as पढ़ो-only: we करो not want
	 * any allocation to happen between _end and the next pmd aligned page.
	 */
	vmlinux_end = (vmlinux_end + PMD_SIZE - 1) & PMD_MASK;
#पूर्ण_अगर
	memblock_reserve(vmlinux_start, vmlinux_end - vmlinux_start);

	/*
	 * memblock allocator is not aware of the fact that last 4K bytes of
	 * the addressable memory can not be mapped because of IS_ERR_VALUE
	 * macro. Make sure that last 4k bytes are not usable by memblock
	 * अगर end of dram is equal to maximum addressable memory.
	 */
	अगर (max_mapped_addr == (dram_end - 1))
		memblock_set_current_limit(max_mapped_addr - 4096);

	min_low_pfn = PFN_UP(memblock_start_of_DRAM());
	max_low_pfn = max_pfn = PFN_DOWN(dram_end);

	dma32_phys_limit = min(4UL * SZ_1G, (अचिन्हित दीर्घ)PFN_PHYS(max_low_pfn));
	set_max_mapnr(max_low_pfn - ARCH_PFN_OFFSET);

	reserve_initrd_mem();
	/*
	 * If DTB is built in, no need to reserve its memblock.
	 * Otherwise, करो reserve it but aव्योम using
	 * early_init_fdt_reserve_self() since __pa() करोes
	 * not work क्रम DTB poपूर्णांकers that are fixmap addresses
	 */
	अगर (!IS_ENABLED(CONFIG_BUILTIN_DTB))
		memblock_reserve(dtb_early_pa, fdt_totalsize(dtb_early_va));

	early_init_fdt_scan_reserved_mem();
	dma_contiguous_reserve(dma32_phys_limit);
	memblock_allow_resize();
पूर्ण

#अगर_घोषित CONFIG_XIP_KERNEL

बाह्य अक्षर _xiprom[], _exiprom[];
बाह्य अक्षर _sdata[], _edata[];

#पूर्ण_अगर /* CONFIG_XIP_KERNEL */

#अगर_घोषित CONFIG_MMU
अटल काष्ठा pt_alloc_ops _pt_ops __ro_after_init;

#अगर_घोषित CONFIG_XIP_KERNEL
#घोषणा pt_ops (*(काष्ठा pt_alloc_ops *)XIP_FIXUP(&_pt_ops))
#अन्यथा
#घोषणा pt_ops _pt_ops
#पूर्ण_अगर

/* Offset between linear mapping भव address and kernel load address */
अचिन्हित दीर्घ va_pa_offset __ro_after_init;
EXPORT_SYMBOL(va_pa_offset);
#अगर_घोषित CONFIG_XIP_KERNEL
#घोषणा va_pa_offset   (*((अचिन्हित दीर्घ *)XIP_FIXUP(&va_pa_offset)))
#पूर्ण_अगर
/* Offset between kernel mapping भव address and kernel load address */
#अगर_घोषित CONFIG_64BIT
अचिन्हित दीर्घ va_kernel_pa_offset;
EXPORT_SYMBOL(va_kernel_pa_offset);
#पूर्ण_अगर
#अगर_घोषित CONFIG_XIP_KERNEL
#घोषणा va_kernel_pa_offset    (*((अचिन्हित दीर्घ *)XIP_FIXUP(&va_kernel_pa_offset)))
#पूर्ण_अगर
अचिन्हित दीर्घ va_kernel_xip_pa_offset;
EXPORT_SYMBOL(va_kernel_xip_pa_offset);
#अगर_घोषित CONFIG_XIP_KERNEL
#घोषणा va_kernel_xip_pa_offset        (*((अचिन्हित दीर्घ *)XIP_FIXUP(&va_kernel_xip_pa_offset)))
#पूर्ण_अगर
अचिन्हित दीर्घ pfn_base __ro_after_init;
EXPORT_SYMBOL(pfn_base);

pgd_t swapper_pg_dir[PTRS_PER_PGD] __page_aligned_bss;
pgd_t trampoline_pg_dir[PTRS_PER_PGD] __page_aligned_bss;
pte_t fixmap_pte[PTRS_PER_PTE] __page_aligned_bss;

pgd_t early_pg_dir[PTRS_PER_PGD] __initdata __aligned(PAGE_SIZE);

#अगर_घोषित CONFIG_XIP_KERNEL
#घोषणा trampoline_pg_dir      ((pgd_t *)XIP_FIXUP(trampoline_pg_dir))
#घोषणा fixmap_pte             ((pte_t *)XIP_FIXUP(fixmap_pte))
#घोषणा early_pg_dir           ((pgd_t *)XIP_FIXUP(early_pg_dir))
#पूर्ण_अगर /* CONFIG_XIP_KERNEL */

व्योम __set_fixmap(क्रमागत fixed_addresses idx, phys_addr_t phys, pgprot_t prot)
अणु
	अचिन्हित दीर्घ addr = __fix_to_virt(idx);
	pte_t *ptep;

	BUG_ON(idx <= FIX_HOLE || idx >= __end_of_fixed_addresses);

	ptep = &fixmap_pte[pte_index(addr)];

	अगर (pgprot_val(prot))
		set_pte(ptep, pfn_pte(phys >> PAGE_SHIFT, prot));
	अन्यथा
		pte_clear(&init_mm, addr, ptep);
	local_flush_tlb_page(addr);
पूर्ण

अटल अंतरभूत pte_t *__init get_pte_virt_early(phys_addr_t pa)
अणु
	वापस (pte_t *)((uपूर्णांकptr_t)pa);
पूर्ण

अटल अंतरभूत pte_t *__init get_pte_virt_fixmap(phys_addr_t pa)
अणु
	clear_fixmap(FIX_PTE);
	वापस (pte_t *)set_fixmap_offset(FIX_PTE, pa);
पूर्ण

अटल अंतरभूत pte_t *get_pte_virt_late(phys_addr_t pa)
अणु
	वापस (pte_t *) __va(pa);
पूर्ण

अटल अंतरभूत phys_addr_t __init alloc_pte_early(uपूर्णांकptr_t va)
अणु
	/*
	 * We only create PMD or PGD early mappings so we
	 * should never reach here with MMU disabled.
	 */
	BUG();
पूर्ण

अटल अंतरभूत phys_addr_t __init alloc_pte_fixmap(uपूर्णांकptr_t va)
अणु
	वापस memblock_phys_alloc(PAGE_SIZE, PAGE_SIZE);
पूर्ण

अटल phys_addr_t alloc_pte_late(uपूर्णांकptr_t va)
अणु
	अचिन्हित दीर्घ vaddr;

	vaddr = __get_मुक्त_page(GFP_KERNEL);
	BUG_ON(!vaddr || !pgtable_pte_page_ctor(virt_to_page(vaddr)));

	वापस __pa(vaddr);
पूर्ण

अटल व्योम __init create_pte_mapping(pte_t *ptep,
				      uपूर्णांकptr_t va, phys_addr_t pa,
				      phys_addr_t sz, pgprot_t prot)
अणु
	uपूर्णांकptr_t pte_idx = pte_index(va);

	BUG_ON(sz != PAGE_SIZE);

	अगर (pte_none(ptep[pte_idx]))
		ptep[pte_idx] = pfn_pte(PFN_DOWN(pa), prot);
पूर्ण

#अगर_अघोषित __PAGETABLE_PMD_FOLDED

pmd_t trampoline_pmd[PTRS_PER_PMD] __page_aligned_bss;
pmd_t fixmap_pmd[PTRS_PER_PMD] __page_aligned_bss;
pmd_t early_pmd[PTRS_PER_PMD] __initdata __aligned(PAGE_SIZE);
pmd_t early_dtb_pmd[PTRS_PER_PMD] __initdata __aligned(PAGE_SIZE);

#अगर_घोषित CONFIG_XIP_KERNEL
#घोषणा trampoline_pmd ((pmd_t *)XIP_FIXUP(trampoline_pmd))
#घोषणा fixmap_pmd     ((pmd_t *)XIP_FIXUP(fixmap_pmd))
#घोषणा early_pmd      ((pmd_t *)XIP_FIXUP(early_pmd))
#पूर्ण_अगर /* CONFIG_XIP_KERNEL */

अटल pmd_t *__init get_pmd_virt_early(phys_addr_t pa)
अणु
	/* Beक्रमe MMU is enabled */
	वापस (pmd_t *)((uपूर्णांकptr_t)pa);
पूर्ण

अटल pmd_t *__init get_pmd_virt_fixmap(phys_addr_t pa)
अणु
	clear_fixmap(FIX_PMD);
	वापस (pmd_t *)set_fixmap_offset(FIX_PMD, pa);
पूर्ण

अटल pmd_t *get_pmd_virt_late(phys_addr_t pa)
अणु
	वापस (pmd_t *) __va(pa);
पूर्ण

अटल phys_addr_t __init alloc_pmd_early(uपूर्णांकptr_t va)
अणु
	BUG_ON((va - kernel_virt_addr) >> PGसूची_SHIFT);

	वापस (uपूर्णांकptr_t)early_pmd;
पूर्ण

अटल phys_addr_t __init alloc_pmd_fixmap(uपूर्णांकptr_t va)
अणु
	वापस memblock_phys_alloc(PAGE_SIZE, PAGE_SIZE);
पूर्ण

अटल phys_addr_t alloc_pmd_late(uपूर्णांकptr_t va)
अणु
	अचिन्हित दीर्घ vaddr;

	vaddr = __get_मुक्त_page(GFP_KERNEL);
	BUG_ON(!vaddr);
	वापस __pa(vaddr);
पूर्ण

अटल व्योम __init create_pmd_mapping(pmd_t *pmdp,
				      uपूर्णांकptr_t va, phys_addr_t pa,
				      phys_addr_t sz, pgprot_t prot)
अणु
	pte_t *ptep;
	phys_addr_t pte_phys;
	uपूर्णांकptr_t pmd_idx = pmd_index(va);

	अगर (sz == PMD_SIZE) अणु
		अगर (pmd_none(pmdp[pmd_idx]))
			pmdp[pmd_idx] = pfn_pmd(PFN_DOWN(pa), prot);
		वापस;
	पूर्ण

	अगर (pmd_none(pmdp[pmd_idx])) अणु
		pte_phys = pt_ops.alloc_pte(va);
		pmdp[pmd_idx] = pfn_pmd(PFN_DOWN(pte_phys), PAGE_TABLE);
		ptep = pt_ops.get_pte_virt(pte_phys);
		स_रखो(ptep, 0, PAGE_SIZE);
	पूर्ण अन्यथा अणु
		pte_phys = PFN_PHYS(_pmd_pfn(pmdp[pmd_idx]));
		ptep = pt_ops.get_pte_virt(pte_phys);
	पूर्ण

	create_pte_mapping(ptep, va, pa, sz, prot);
पूर्ण

#घोषणा pgd_next_t		pmd_t
#घोषणा alloc_pgd_next(__va)	pt_ops.alloc_pmd(__va)
#घोषणा get_pgd_next_virt(__pa)	pt_ops.get_pmd_virt(__pa)
#घोषणा create_pgd_next_mapping(__nextp, __va, __pa, __sz, __prot)	\
	create_pmd_mapping(__nextp, __va, __pa, __sz, __prot)
#घोषणा fixmap_pgd_next		fixmap_pmd
#अन्यथा
#घोषणा pgd_next_t		pte_t
#घोषणा alloc_pgd_next(__va)	pt_ops.alloc_pte(__va)
#घोषणा get_pgd_next_virt(__pa)	pt_ops.get_pte_virt(__pa)
#घोषणा create_pgd_next_mapping(__nextp, __va, __pa, __sz, __prot)	\
	create_pte_mapping(__nextp, __va, __pa, __sz, __prot)
#घोषणा fixmap_pgd_next		fixmap_pte
#पूर्ण_अगर

व्योम __init create_pgd_mapping(pgd_t *pgdp,
				      uपूर्णांकptr_t va, phys_addr_t pa,
				      phys_addr_t sz, pgprot_t prot)
अणु
	pgd_next_t *nextp;
	phys_addr_t next_phys;
	uपूर्णांकptr_t pgd_idx = pgd_index(va);

	अगर (sz == PGसूची_SIZE) अणु
		अगर (pgd_val(pgdp[pgd_idx]) == 0)
			pgdp[pgd_idx] = pfn_pgd(PFN_DOWN(pa), prot);
		वापस;
	पूर्ण

	अगर (pgd_val(pgdp[pgd_idx]) == 0) अणु
		next_phys = alloc_pgd_next(va);
		pgdp[pgd_idx] = pfn_pgd(PFN_DOWN(next_phys), PAGE_TABLE);
		nextp = get_pgd_next_virt(next_phys);
		स_रखो(nextp, 0, PAGE_SIZE);
	पूर्ण अन्यथा अणु
		next_phys = PFN_PHYS(_pgd_pfn(pgdp[pgd_idx]));
		nextp = get_pgd_next_virt(next_phys);
	पूर्ण

	create_pgd_next_mapping(nextp, va, pa, sz, prot);
पूर्ण

अटल uपूर्णांकptr_t __init best_map_size(phys_addr_t base, phys_addr_t size)
अणु
	/* Upgrade to PMD_SIZE mappings whenever possible */
	अगर ((base & (PMD_SIZE - 1)) || (size & (PMD_SIZE - 1)))
		वापस PAGE_SIZE;

	वापस PMD_SIZE;
पूर्ण

#अगर_घोषित CONFIG_XIP_KERNEL
/* called from head.S with MMU off */
यंत्रlinkage व्योम __init __copy_data(व्योम)
अणु
	व्योम *from = (व्योम *)(&_sdata);
	व्योम *end = (व्योम *)(&_end);
	व्योम *to = (व्योम *)CONFIG_PHYS_RAM_BASE;
	माप_प्रकार sz = (माप_प्रकार)(end - from + 1);

	स_नकल(to, from, sz);
पूर्ण
#पूर्ण_अगर

/*
 * setup_vm() is called from head.S with MMU-off.
 *
 * Following requirements should be honoured क्रम setup_vm() to work
 * correctly:
 * 1) It should use PC-relative addressing क्रम accessing kernel symbols.
 *    To achieve this we always use GCC cmodel=medany.
 * 2) The compiler instrumentation क्रम FTRACE will not work क्रम setup_vm()
 *    so disable compiler instrumentation when FTRACE is enabled.
 *
 * Currently, the above requirements are honoured by using custom CFLAGS
 * क्रम init.o in mm/Makefile.
 */

#अगर_अघोषित __riscv_cmodel_medany
#त्रुटि "setup_vm() is called from head.S before relocate so it should not use absolute addressing."
#पूर्ण_अगर

uपूर्णांकptr_t load_pa, load_sz;
#अगर_घोषित CONFIG_XIP_KERNEL
#घोषणा load_pa        (*((uपूर्णांकptr_t *)XIP_FIXUP(&load_pa)))
#घोषणा load_sz        (*((uपूर्णांकptr_t *)XIP_FIXUP(&load_sz)))
#पूर्ण_अगर

#अगर_घोषित CONFIG_XIP_KERNEL
uपूर्णांकptr_t xiprom, xiprom_sz;
#घोषणा xiprom_sz      (*((uपूर्णांकptr_t *)XIP_FIXUP(&xiprom_sz)))
#घोषणा xiprom         (*((uपूर्णांकptr_t *)XIP_FIXUP(&xiprom)))

अटल व्योम __init create_kernel_page_table(pgd_t *pgdir, uपूर्णांकptr_t map_size)
अणु
	uपूर्णांकptr_t va, end_va;

	/* Map the flash resident part */
	end_va = kernel_virt_addr + xiprom_sz;
	क्रम (va = kernel_virt_addr; va < end_va; va += map_size)
		create_pgd_mapping(pgdir, va,
				   xiprom + (va - kernel_virt_addr),
				   map_size, PAGE_KERNEL_EXEC);

	/* Map the data in RAM */
	end_va = kernel_virt_addr + XIP_OFFSET + load_sz;
	क्रम (va = kernel_virt_addr + XIP_OFFSET; va < end_va; va += map_size)
		create_pgd_mapping(pgdir, va,
				   load_pa + (va - (kernel_virt_addr + XIP_OFFSET)),
				   map_size, PAGE_KERNEL);
पूर्ण
#अन्यथा
अटल व्योम __init create_kernel_page_table(pgd_t *pgdir, uपूर्णांकptr_t map_size)
अणु
	uपूर्णांकptr_t va, end_va;

	end_va = kernel_virt_addr + load_sz;
	क्रम (va = kernel_virt_addr; va < end_va; va += map_size)
		create_pgd_mapping(pgdir, va,
				   load_pa + (va - kernel_virt_addr),
				   map_size, PAGE_KERNEL_EXEC);
पूर्ण
#पूर्ण_अगर

यंत्रlinkage व्योम __init setup_vm(uपूर्णांकptr_t dtb_pa)
अणु
	uपूर्णांकptr_t __maybe_unused pa;
	uपूर्णांकptr_t map_size;
#अगर_अघोषित __PAGETABLE_PMD_FOLDED
	pmd_t fix_bmap_spmd, fix_bmap_epmd;
#पूर्ण_अगर

#अगर_घोषित CONFIG_XIP_KERNEL
	xiprom = (uपूर्णांकptr_t)CONFIG_XIP_PHYS_ADDR;
	xiprom_sz = (uपूर्णांकptr_t)(&_exiprom) - (uपूर्णांकptr_t)(&_xiprom);

	load_pa = (uपूर्णांकptr_t)CONFIG_PHYS_RAM_BASE;
	load_sz = (uपूर्णांकptr_t)(&_end) - (uपूर्णांकptr_t)(&_sdata);

	va_kernel_xip_pa_offset = kernel_virt_addr - xiprom;
#अन्यथा
	load_pa = (uपूर्णांकptr_t)(&_start);
	load_sz = (uपूर्णांकptr_t)(&_end) - load_pa;
#पूर्ण_अगर

	va_pa_offset = PAGE_OFFSET - load_pa;
#अगर_घोषित CONFIG_64BIT
	va_kernel_pa_offset = kernel_virt_addr - load_pa;
#पूर्ण_अगर

	pfn_base = PFN_DOWN(load_pa);

	/*
	 * Enक्रमce boot alignment requirements of RV32 and
	 * RV64 by only allowing PMD or PGD mappings.
	 */
	map_size = PMD_SIZE;

	/* Sanity check alignment and size */
	BUG_ON((PAGE_OFFSET % PGसूची_SIZE) != 0);
	BUG_ON((load_pa % map_size) != 0);

	pt_ops.alloc_pte = alloc_pte_early;
	pt_ops.get_pte_virt = get_pte_virt_early;
#अगर_अघोषित __PAGETABLE_PMD_FOLDED
	pt_ops.alloc_pmd = alloc_pmd_early;
	pt_ops.get_pmd_virt = get_pmd_virt_early;
#पूर्ण_अगर
	/* Setup early PGD क्रम fixmap */
	create_pgd_mapping(early_pg_dir, FIXADDR_START,
			   (uपूर्णांकptr_t)fixmap_pgd_next, PGसूची_SIZE, PAGE_TABLE);

#अगर_अघोषित __PAGETABLE_PMD_FOLDED
	/* Setup fixmap PMD */
	create_pmd_mapping(fixmap_pmd, FIXADDR_START,
			   (uपूर्णांकptr_t)fixmap_pte, PMD_SIZE, PAGE_TABLE);
	/* Setup trampoline PGD and PMD */
	create_pgd_mapping(trampoline_pg_dir, kernel_virt_addr,
			   (uपूर्णांकptr_t)trampoline_pmd, PGसूची_SIZE, PAGE_TABLE);
#अगर_घोषित CONFIG_XIP_KERNEL
	create_pmd_mapping(trampoline_pmd, kernel_virt_addr,
			   xiprom, PMD_SIZE, PAGE_KERNEL_EXEC);
#अन्यथा
	create_pmd_mapping(trampoline_pmd, kernel_virt_addr,
			   load_pa, PMD_SIZE, PAGE_KERNEL_EXEC);
#पूर्ण_अगर
#अन्यथा
	/* Setup trampoline PGD */
	create_pgd_mapping(trampoline_pg_dir, kernel_virt_addr,
			   load_pa, PGसूची_SIZE, PAGE_KERNEL_EXEC);
#पूर्ण_अगर

	/*
	 * Setup early PGD covering entire kernel which will allow
	 * us to reach paging_init(). We map all memory banks later
	 * in setup_vm_final() below.
	 */
	create_kernel_page_table(early_pg_dir, map_size);

#अगर_अघोषित __PAGETABLE_PMD_FOLDED
	/* Setup early PMD क्रम DTB */
	create_pgd_mapping(early_pg_dir, DTB_EARLY_BASE_VA,
			   (uपूर्णांकptr_t)early_dtb_pmd, PGसूची_SIZE, PAGE_TABLE);
#अगर_अघोषित CONFIG_BUILTIN_DTB
	/* Create two consecutive PMD mappings क्रम FDT early scan */
	pa = dtb_pa & ~(PMD_SIZE - 1);
	create_pmd_mapping(early_dtb_pmd, DTB_EARLY_BASE_VA,
			   pa, PMD_SIZE, PAGE_KERNEL);
	create_pmd_mapping(early_dtb_pmd, DTB_EARLY_BASE_VA + PMD_SIZE,
			   pa + PMD_SIZE, PMD_SIZE, PAGE_KERNEL);
	dtb_early_va = (व्योम *)DTB_EARLY_BASE_VA + (dtb_pa & (PMD_SIZE - 1));
#अन्यथा /* CONFIG_BUILTIN_DTB */
#अगर_घोषित CONFIG_64BIT
	/*
	 * __va can't be used since it would वापस a linear mapping address
	 * whereas dtb_early_va will be used beक्रमe setup_vm_final installs
	 * the linear mapping.
	 */
	dtb_early_va = kernel_mapping_pa_to_va(XIP_FIXUP(dtb_pa));
#अन्यथा
	dtb_early_va = __va(dtb_pa);
#पूर्ण_अगर /* CONFIG_64BIT */
#पूर्ण_अगर /* CONFIG_BUILTIN_DTB */
#अन्यथा
#अगर_अघोषित CONFIG_BUILTIN_DTB
	/* Create two consecutive PGD mappings क्रम FDT early scan */
	pa = dtb_pa & ~(PGसूची_SIZE - 1);
	create_pgd_mapping(early_pg_dir, DTB_EARLY_BASE_VA,
			   pa, PGसूची_SIZE, PAGE_KERNEL);
	create_pgd_mapping(early_pg_dir, DTB_EARLY_BASE_VA + PGसूची_SIZE,
			   pa + PGसूची_SIZE, PGसूची_SIZE, PAGE_KERNEL);
	dtb_early_va = (व्योम *)DTB_EARLY_BASE_VA + (dtb_pa & (PGसूची_SIZE - 1));
#अन्यथा /* CONFIG_BUILTIN_DTB */
#अगर_घोषित CONFIG_64BIT
	dtb_early_va = kernel_mapping_pa_to_va(XIP_FIXUP(dtb_pa));
#अन्यथा
	dtb_early_va = __va(dtb_pa);
#पूर्ण_अगर /* CONFIG_64BIT */
#पूर्ण_अगर /* CONFIG_BUILTIN_DTB */
#पूर्ण_अगर
	dtb_early_pa = dtb_pa;

	/*
	 * Booसमय fixmap only can handle PMD_SIZE mapping. Thus, boot-ioremap
	 * range can not span multiple pmds.
	 */
	BUILD_BUG_ON((__fix_to_virt(FIX_BTMAP_BEGIN) >> PMD_SHIFT)
		     != (__fix_to_virt(FIX_BTMAP_END) >> PMD_SHIFT));

#अगर_अघोषित __PAGETABLE_PMD_FOLDED
	/*
	 * Early ioremap fixmap is alपढ़ोy created as it lies within first 2MB
	 * of fixmap region. We always map PMD_SIZE. Thus, both FIX_BTMAP_END
	 * FIX_BTMAP_BEGIN should lie in the same pmd. Verअगरy that and warn
	 * the user अगर not.
	 */
	fix_bmap_spmd = fixmap_pmd[pmd_index(__fix_to_virt(FIX_BTMAP_BEGIN))];
	fix_bmap_epmd = fixmap_pmd[pmd_index(__fix_to_virt(FIX_BTMAP_END))];
	अगर (pmd_val(fix_bmap_spmd) != pmd_val(fix_bmap_epmd)) अणु
		WARN_ON(1);
		pr_warn("fixmap btmap start [%08lx] != end [%08lx]\n",
			pmd_val(fix_bmap_spmd), pmd_val(fix_bmap_epmd));
		pr_warn("fix_to_virt(FIX_BTMAP_BEGIN): %08lx\n",
			fix_to_virt(FIX_BTMAP_BEGIN));
		pr_warn("fix_to_virt(FIX_BTMAP_END):   %08lx\n",
			fix_to_virt(FIX_BTMAP_END));

		pr_warn("FIX_BTMAP_END:       %d\n", FIX_BTMAP_END);
		pr_warn("FIX_BTMAP_BEGIN:     %d\n", FIX_BTMAP_BEGIN);
	पूर्ण
#पूर्ण_अगर
पूर्ण

#अगर defined(CONFIG_64BIT) && defined(CONFIG_STRICT_KERNEL_RWX)
व्योम protect_kernel_linear_mapping_text_rodata(व्योम)
अणु
	अचिन्हित दीर्घ text_start = (अचिन्हित दीर्घ)lm_alias(_start);
	अचिन्हित दीर्घ init_text_start = (अचिन्हित दीर्घ)lm_alias(__init_text_begin);
	अचिन्हित दीर्घ rodata_start = (अचिन्हित दीर्घ)lm_alias(__start_rodata);
	अचिन्हित दीर्घ data_start = (अचिन्हित दीर्घ)lm_alias(_data);

	set_memory_ro(text_start, (init_text_start - text_start) >> PAGE_SHIFT);
	set_memory_nx(text_start, (init_text_start - text_start) >> PAGE_SHIFT);

	set_memory_ro(rodata_start, (data_start - rodata_start) >> PAGE_SHIFT);
	set_memory_nx(rodata_start, (data_start - rodata_start) >> PAGE_SHIFT);
पूर्ण
#पूर्ण_अगर

अटल व्योम __init setup_vm_final(व्योम)
अणु
	uपूर्णांकptr_t va, map_size;
	phys_addr_t pa, start, end;
	u64 i;

	/**
	 * MMU is enabled at this poपूर्णांक. But page table setup is not complete yet.
	 * fixmap page table alloc functions should be used at this poपूर्णांक
	 */
	pt_ops.alloc_pte = alloc_pte_fixmap;
	pt_ops.get_pte_virt = get_pte_virt_fixmap;
#अगर_अघोषित __PAGETABLE_PMD_FOLDED
	pt_ops.alloc_pmd = alloc_pmd_fixmap;
	pt_ops.get_pmd_virt = get_pmd_virt_fixmap;
#पूर्ण_अगर
	/* Setup swapper PGD क्रम fixmap */
	create_pgd_mapping(swapper_pg_dir, FIXADDR_START,
			   __pa_symbol(fixmap_pgd_next),
			   PGसूची_SIZE, PAGE_TABLE);

	/* Map all memory banks in the linear mapping */
	क्रम_each_mem_range(i, &start, &end) अणु
		अगर (start >= end)
			अवरोध;
		अगर (start <= __pa(PAGE_OFFSET) &&
		    __pa(PAGE_OFFSET) < end)
			start = __pa(PAGE_OFFSET);

		map_size = best_map_size(start, end - start);
		क्रम (pa = start; pa < end; pa += map_size) अणु
			va = (uपूर्णांकptr_t)__va(pa);
			create_pgd_mapping(swapper_pg_dir, va, pa,
					   map_size,
#अगर_घोषित CONFIG_64BIT
					   PAGE_KERNEL
#अन्यथा
					   PAGE_KERNEL_EXEC
#पूर्ण_अगर
					);

		पूर्ण
	पूर्ण

#अगर_घोषित CONFIG_64BIT
	/* Map the kernel */
	create_kernel_page_table(swapper_pg_dir, PMD_SIZE);
#पूर्ण_अगर

	/* Clear fixmap PTE and PMD mappings */
	clear_fixmap(FIX_PTE);
	clear_fixmap(FIX_PMD);

	/* Move to swapper page table */
	csr_ग_लिखो(CSR_SATP, PFN_DOWN(__pa_symbol(swapper_pg_dir)) | SATP_MODE);
	local_flush_tlb_all();

	/* generic page allocation functions must be used to setup page table */
	pt_ops.alloc_pte = alloc_pte_late;
	pt_ops.get_pte_virt = get_pte_virt_late;
#अगर_अघोषित __PAGETABLE_PMD_FOLDED
	pt_ops.alloc_pmd = alloc_pmd_late;
	pt_ops.get_pmd_virt = get_pmd_virt_late;
#पूर्ण_अगर
पूर्ण
#अन्यथा
यंत्रlinkage व्योम __init setup_vm(uपूर्णांकptr_t dtb_pa)
अणु
	dtb_early_va = (व्योम *)dtb_pa;
	dtb_early_pa = dtb_pa;
पूर्ण

अटल अंतरभूत व्योम setup_vm_final(व्योम)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_MMU */

#अगर_घोषित CONFIG_STRICT_KERNEL_RWX
व्योम __init protect_kernel_text_data(व्योम)
अणु
	अचिन्हित दीर्घ text_start = (अचिन्हित दीर्घ)_start;
	अचिन्हित दीर्घ init_text_start = (अचिन्हित दीर्घ)__init_text_begin;
	अचिन्हित दीर्घ init_data_start = (अचिन्हित दीर्घ)__init_data_begin;
	अचिन्हित दीर्घ rodata_start = (अचिन्हित दीर्घ)__start_rodata;
	अचिन्हित दीर्घ data_start = (अचिन्हित दीर्घ)_data;
#अगर defined(CONFIG_64BIT) && defined(CONFIG_MMU)
	अचिन्हित दीर्घ end_va = kernel_virt_addr + load_sz;
#अन्यथा
	अचिन्हित दीर्घ end_va = (अचिन्हित दीर्घ)(__va(PFN_PHYS(max_low_pfn)));
#पूर्ण_अगर

	set_memory_ro(text_start, (init_text_start - text_start) >> PAGE_SHIFT);
	set_memory_ro(init_text_start, (init_data_start - init_text_start) >> PAGE_SHIFT);
	set_memory_nx(init_data_start, (rodata_start - init_data_start) >> PAGE_SHIFT);
	/* rodata section is marked पढ़ोonly in mark_rodata_ro */
	set_memory_nx(rodata_start, (data_start - rodata_start) >> PAGE_SHIFT);
	set_memory_nx(data_start, (end_va - data_start) >> PAGE_SHIFT);
पूर्ण

व्योम mark_rodata_ro(व्योम)
अणु
	अचिन्हित दीर्घ rodata_start = (अचिन्हित दीर्घ)__start_rodata;
	अचिन्हित दीर्घ data_start = (अचिन्हित दीर्घ)_data;

	set_memory_ro(rodata_start, (data_start - rodata_start) >> PAGE_SHIFT);

	debug_checkwx();
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_KEXEC_CORE
/*
 * reserve_crashkernel() - reserves memory क्रम crash kernel
 *
 * This function reserves memory area given in "crashkernel=" kernel command
 * line parameter. The memory reserved is used by dump capture kernel when
 * primary kernel is crashing.
 */
अटल व्योम __init reserve_crashkernel(व्योम)
अणु
	अचिन्हित दीर्घ दीर्घ crash_base = 0;
	अचिन्हित दीर्घ दीर्घ crash_size = 0;
	अचिन्हित दीर्घ search_start = memblock_start_of_DRAM();
	अचिन्हित दीर्घ search_end = memblock_end_of_DRAM();

	पूर्णांक ret = 0;

	/*
	 * Don't reserve a region क्रम a crash kernel on a crash kernel
	 * since it करोesn't make much sense and we have limited memory
	 * resources.
	 */
#अगर_घोषित CONFIG_CRASH_DUMP
	अगर (is_kdump_kernel()) अणु
		pr_info("crashkernel: ignoring reservation request\n");
		वापस;
	पूर्ण
#पूर्ण_अगर

	ret = parse_crashkernel(boot_command_line, memblock_phys_mem_size(),
				&crash_size, &crash_base);
	अगर (ret || !crash_size)
		वापस;

	crash_size = PAGE_ALIGN(crash_size);

	अगर (crash_base == 0) अणु
		/*
		 * Current riscv boot protocol requires 2MB alignment क्रम
		 * RV64 and 4MB alignment क्रम RV32 (hugepage size)
		 */
		crash_base = memblock_find_in_range(search_start, search_end,
						    crash_size, PMD_SIZE);

		अगर (crash_base == 0) अणु
			pr_warn("crashkernel: couldn't allocate %lldKB\n",
				crash_size >> 10);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* User specअगरies base address explicitly. */
		अगर (!memblock_is_region_memory(crash_base, crash_size)) अणु
			pr_warn("crashkernel: requested region is not memory\n");
			वापस;
		पूर्ण

		अगर (memblock_is_region_reserved(crash_base, crash_size)) अणु
			pr_warn("crashkernel: requested region is reserved\n");
			वापस;
		पूर्ण


		अगर (!IS_ALIGNED(crash_base, PMD_SIZE)) अणु
			pr_warn("crashkernel: requested region is misaligned\n");
			वापस;
		पूर्ण
	पूर्ण
	memblock_reserve(crash_base, crash_size);

	pr_info("crashkernel: reserved 0x%016llx - 0x%016llx (%lld MB)\n",
		crash_base, crash_base + crash_size, crash_size >> 20);

	crashk_res.start = crash_base;
	crashk_res.end = crash_base + crash_size - 1;
पूर्ण
#पूर्ण_अगर /* CONFIG_KEXEC_CORE */

#अगर_घोषित CONFIG_CRASH_DUMP
/*
 * We keep track of the ELF core header of the crashed
 * kernel with a reserved-memory region with compatible
 * string "linux,elfcorehdr". Here we रेजिस्टर a callback
 * to populate elfcorehdr_addr/size when this region is
 * present. Note that this region will be marked as
 * reserved once we call early_init_fdt_scan_reserved_mem()
 * later on.
 */
अटल पूर्णांक elfcore_hdr_setup(काष्ठा reserved_mem *rmem)
अणु
	elfcorehdr_addr = rmem->base;
	elfcorehdr_size = rmem->size;
	वापस 0;
पूर्ण

RESERVEDMEM_OF_DECLARE(elfcorehdr, "linux,elfcorehdr", elfcore_hdr_setup);
#पूर्ण_अगर

व्योम __init paging_init(व्योम)
अणु
	setup_vm_final();
	setup_zero_page();
पूर्ण

व्योम __init misc_mem_init(व्योम)
अणु
	early_memtest(min_low_pfn << PAGE_SHIFT, max_low_pfn << PAGE_SHIFT);
	arch_numa_init();
	sparse_init();
	zone_sizes_init();
#अगर_घोषित CONFIG_KEXEC_CORE
	reserve_crashkernel();
#पूर्ण_अगर
	memblock_dump_all();
पूर्ण

#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
पूर्णांक __meminit vmemmap_populate(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, पूर्णांक node,
			       काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	वापस vmemmap_populate_basepages(start, end, node, शून्य);
पूर्ण
#पूर्ण_अगर
