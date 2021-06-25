<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/x86_64/mm/init.c
 *
 *  Copyright (C) 1995  Linus Torvalds
 *  Copyright (C) 2000  Pavel Machek <pavel@ucw.cz>
 *  Copyright (C) 2002,2003 Andi Kleen <ak@suse.de>
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
#समावेश <linux/smp.h>
#समावेश <linux/init.h>
#समावेश <linux/initrd.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/memblock.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/pci.h>
#समावेश <linux/pfn.h>
#समावेश <linux/poison.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/memory.h>
#समावेश <linux/memory_hotplug.h>
#समावेश <linux/memremap.h>
#समावेश <linux/nmi.h>
#समावेश <linux/gfp.h>
#समावेश <linux/kcore.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/bios_ebda.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/proto.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/kdebug.h>
#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/init.h>
#समावेश <यंत्र/uv/uv.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/ftrace.h>

#समावेश "mm_internal.h"

#समावेश "ident_map.c"

#घोषणा DEFINE_POPULATE(fname, type1, type2, init)		\
अटल अंतरभूत व्योम fname##_init(काष्ठा mm_काष्ठा *mm,		\
		type1##_t *arg1, type2##_t *arg2, bool init)	\
अणु								\
	अगर (init)						\
		fname##_safe(mm, arg1, arg2);			\
	अन्यथा							\
		fname(mm, arg1, arg2);				\
पूर्ण

DEFINE_POPULATE(p4d_populate, p4d, pud, init)
DEFINE_POPULATE(pgd_populate, pgd, p4d, init)
DEFINE_POPULATE(pud_populate, pud, pmd, init)
DEFINE_POPULATE(pmd_populate_kernel, pmd, pte, init)

#घोषणा DEFINE_ENTRY(type1, type2, init)			\
अटल अंतरभूत व्योम set_##type1##_init(type1##_t *arg1,		\
			type2##_t arg2, bool init)		\
अणु								\
	अगर (init)						\
		set_##type1##_safe(arg1, arg2);			\
	अन्यथा							\
		set_##type1(arg1, arg2);			\
पूर्ण

DEFINE_ENTRY(p4d, p4d, init)
DEFINE_ENTRY(pud, pud, init)
DEFINE_ENTRY(pmd, pmd, init)
DEFINE_ENTRY(pte, pte, init)


/*
 * NOTE: pagetable_init alloc all the fixmap pagetables contiguous on the
 * physical space so we can cache the place of the first one and move
 * around without checking the pgd every समय.
 */

/* Bits supported by the hardware: */
pteval_t __supported_pte_mask __पढ़ो_mostly = ~0;
/* Bits allowed in normal kernel mappings: */
pteval_t __शेष_kernel_pte_mask __पढ़ो_mostly = ~0;
EXPORT_SYMBOL_GPL(__supported_pte_mask);
/* Used in PAGE_KERNEL_* macros which are reasonably used out-of-tree: */
EXPORT_SYMBOL(__शेष_kernel_pte_mask);

पूर्णांक क्रमce_personality32;

/*
 * noexec32=on|off
 * Control non executable heap क्रम 32bit processes.
 * To control the stack too use noexec=off
 *
 * on	PROT_READ करोes not imply PROT_EXEC क्रम 32-bit processes (शेष)
 * off	PROT_READ implies PROT_EXEC
 */
अटल पूर्णांक __init nonx32_setup(अक्षर *str)
अणु
	अगर (!म_भेद(str, "on"))
		क्रमce_personality32 &= ~READ_IMPLIES_EXEC;
	अन्यथा अगर (!म_भेद(str, "off"))
		क्रमce_personality32 |= READ_IMPLIES_EXEC;
	वापस 1;
पूर्ण
__setup("noexec32=", nonx32_setup);

अटल व्योम sync_global_pgds_l5(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ addr;

	क्रम (addr = start; addr <= end; addr = ALIGN(addr + 1, PGसूची_SIZE)) अणु
		स्थिर pgd_t *pgd_ref = pgd_offset_k(addr);
		काष्ठा page *page;

		/* Check क्रम overflow */
		अगर (addr < start)
			अवरोध;

		अगर (pgd_none(*pgd_ref))
			जारी;

		spin_lock(&pgd_lock);
		list_क्रम_each_entry(page, &pgd_list, lru) अणु
			pgd_t *pgd;
			spinlock_t *pgt_lock;

			pgd = (pgd_t *)page_address(page) + pgd_index(addr);
			/* the pgt_lock only क्रम Xen */
			pgt_lock = &pgd_page_get_mm(page)->page_table_lock;
			spin_lock(pgt_lock);

			अगर (!pgd_none(*pgd_ref) && !pgd_none(*pgd))
				BUG_ON(pgd_page_vaddr(*pgd) != pgd_page_vaddr(*pgd_ref));

			अगर (pgd_none(*pgd))
				set_pgd(pgd, *pgd_ref);

			spin_unlock(pgt_lock);
		पूर्ण
		spin_unlock(&pgd_lock);
	पूर्ण
पूर्ण

अटल व्योम sync_global_pgds_l4(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ addr;

	क्रम (addr = start; addr <= end; addr = ALIGN(addr + 1, PGसूची_SIZE)) अणु
		pgd_t *pgd_ref = pgd_offset_k(addr);
		स्थिर p4d_t *p4d_ref;
		काष्ठा page *page;

		/*
		 * With folded p4d, pgd_none() is always false, we need to
		 * handle synchronization on p4d level.
		 */
		MAYBE_BUILD_BUG_ON(pgd_none(*pgd_ref));
		p4d_ref = p4d_offset(pgd_ref, addr);

		अगर (p4d_none(*p4d_ref))
			जारी;

		spin_lock(&pgd_lock);
		list_क्रम_each_entry(page, &pgd_list, lru) अणु
			pgd_t *pgd;
			p4d_t *p4d;
			spinlock_t *pgt_lock;

			pgd = (pgd_t *)page_address(page) + pgd_index(addr);
			p4d = p4d_offset(pgd, addr);
			/* the pgt_lock only क्रम Xen */
			pgt_lock = &pgd_page_get_mm(page)->page_table_lock;
			spin_lock(pgt_lock);

			अगर (!p4d_none(*p4d_ref) && !p4d_none(*p4d))
				BUG_ON(p4d_page_vaddr(*p4d)
				       != p4d_page_vaddr(*p4d_ref));

			अगर (p4d_none(*p4d))
				set_p4d(p4d, *p4d_ref);

			spin_unlock(pgt_lock);
		पूर्ण
		spin_unlock(&pgd_lock);
	पूर्ण
पूर्ण

/*
 * When memory was added make sure all the processes MM have
 * suitable PGD entries in the local PGD level page.
 */
अटल व्योम sync_global_pgds(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अगर (pgtable_l5_enabled())
		sync_global_pgds_l5(start, end);
	अन्यथा
		sync_global_pgds_l4(start, end);
पूर्ण

/*
 * NOTE: This function is marked __ref because it calls __init function
 * (alloc_booपंचांगem_pages). It's safe to करो it ONLY when after_booपंचांगem == 0.
 */
अटल __ref व्योम *spp_getpage(व्योम)
अणु
	व्योम *ptr;

	अगर (after_booपंचांगem)
		ptr = (व्योम *) get_zeroed_page(GFP_ATOMIC);
	अन्यथा
		ptr = memblock_alloc(PAGE_SIZE, PAGE_SIZE);

	अगर (!ptr || ((अचिन्हित दीर्घ)ptr & ~PAGE_MASK)) अणु
		panic("set_pte_phys: cannot allocate page data %s\n",
			after_booपंचांगem ? "after bootmem" : "");
	पूर्ण

	pr_debug("spp_getpage %p\n", ptr);

	वापस ptr;
पूर्ण

अटल p4d_t *fill_p4d(pgd_t *pgd, अचिन्हित दीर्घ vaddr)
अणु
	अगर (pgd_none(*pgd)) अणु
		p4d_t *p4d = (p4d_t *)spp_getpage();
		pgd_populate(&init_mm, pgd, p4d);
		अगर (p4d != p4d_offset(pgd, 0))
			prपूर्णांकk(KERN_ERR "PAGETABLE BUG #00! %p <-> %p\n",
			       p4d, p4d_offset(pgd, 0));
	पूर्ण
	वापस p4d_offset(pgd, vaddr);
पूर्ण

अटल pud_t *fill_pud(p4d_t *p4d, अचिन्हित दीर्घ vaddr)
अणु
	अगर (p4d_none(*p4d)) अणु
		pud_t *pud = (pud_t *)spp_getpage();
		p4d_populate(&init_mm, p4d, pud);
		अगर (pud != pud_offset(p4d, 0))
			prपूर्णांकk(KERN_ERR "PAGETABLE BUG #01! %p <-> %p\n",
			       pud, pud_offset(p4d, 0));
	पूर्ण
	वापस pud_offset(p4d, vaddr);
पूर्ण

अटल pmd_t *fill_pmd(pud_t *pud, अचिन्हित दीर्घ vaddr)
अणु
	अगर (pud_none(*pud)) अणु
		pmd_t *pmd = (pmd_t *) spp_getpage();
		pud_populate(&init_mm, pud, pmd);
		अगर (pmd != pmd_offset(pud, 0))
			prपूर्णांकk(KERN_ERR "PAGETABLE BUG #02! %p <-> %p\n",
			       pmd, pmd_offset(pud, 0));
	पूर्ण
	वापस pmd_offset(pud, vaddr);
पूर्ण

अटल pte_t *fill_pte(pmd_t *pmd, अचिन्हित दीर्घ vaddr)
अणु
	अगर (pmd_none(*pmd)) अणु
		pte_t *pte = (pte_t *) spp_getpage();
		pmd_populate_kernel(&init_mm, pmd, pte);
		अगर (pte != pte_offset_kernel(pmd, 0))
			prपूर्णांकk(KERN_ERR "PAGETABLE BUG #03!\n");
	पूर्ण
	वापस pte_offset_kernel(pmd, vaddr);
पूर्ण

अटल व्योम __set_pte_vaddr(pud_t *pud, अचिन्हित दीर्घ vaddr, pte_t new_pte)
अणु
	pmd_t *pmd = fill_pmd(pud, vaddr);
	pte_t *pte = fill_pte(pmd, vaddr);

	set_pte(pte, new_pte);

	/*
	 * It's enough to flush this one mapping.
	 * (PGE mappings get flushed as well)
	 */
	flush_tlb_one_kernel(vaddr);
पूर्ण

व्योम set_pte_vaddr_p4d(p4d_t *p4d_page, अचिन्हित दीर्घ vaddr, pte_t new_pte)
अणु
	p4d_t *p4d = p4d_page + p4d_index(vaddr);
	pud_t *pud = fill_pud(p4d, vaddr);

	__set_pte_vaddr(pud, vaddr, new_pte);
पूर्ण

व्योम set_pte_vaddr_pud(pud_t *pud_page, अचिन्हित दीर्घ vaddr, pte_t new_pte)
अणु
	pud_t *pud = pud_page + pud_index(vaddr);

	__set_pte_vaddr(pud, vaddr, new_pte);
पूर्ण

व्योम set_pte_vaddr(अचिन्हित दीर्घ vaddr, pte_t pteval)
अणु
	pgd_t *pgd;
	p4d_t *p4d_page;

	pr_debug("set_pte_vaddr %lx to %lx\n", vaddr, native_pte_val(pteval));

	pgd = pgd_offset_k(vaddr);
	अगर (pgd_none(*pgd)) अणु
		prपूर्णांकk(KERN_ERR
			"PGD FIXMAP MISSING, it should be setup in head.S!\n");
		वापस;
	पूर्ण

	p4d_page = p4d_offset(pgd, 0);
	set_pte_vaddr_p4d(p4d_page, vaddr, pteval);
पूर्ण

pmd_t * __init populate_extra_pmd(अचिन्हित दीर्घ vaddr)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;

	pgd = pgd_offset_k(vaddr);
	p4d = fill_p4d(pgd, vaddr);
	pud = fill_pud(p4d, vaddr);
	वापस fill_pmd(pud, vaddr);
पूर्ण

pte_t * __init populate_extra_pte(अचिन्हित दीर्घ vaddr)
अणु
	pmd_t *pmd;

	pmd = populate_extra_pmd(vaddr);
	वापस fill_pte(pmd, vaddr);
पूर्ण

/*
 * Create large page table mappings क्रम a range of physical addresses.
 */
अटल व्योम __init __init_extra_mapping(अचिन्हित दीर्घ phys, अचिन्हित दीर्घ size,
					क्रमागत page_cache_mode cache)
अणु
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pgprot_t prot;

	pgprot_val(prot) = pgprot_val(PAGE_KERNEL_LARGE) |
		protval_4k_2_large(cachemode2protval(cache));
	BUG_ON((phys & ~PMD_MASK) || (size & ~PMD_MASK));
	क्रम (; size; phys += PMD_SIZE, size -= PMD_SIZE) अणु
		pgd = pgd_offset_k((अचिन्हित दीर्घ)__va(phys));
		अगर (pgd_none(*pgd)) अणु
			p4d = (p4d_t *) spp_getpage();
			set_pgd(pgd, __pgd(__pa(p4d) | _KERNPG_TABLE |
						_PAGE_USER));
		पूर्ण
		p4d = p4d_offset(pgd, (अचिन्हित दीर्घ)__va(phys));
		अगर (p4d_none(*p4d)) अणु
			pud = (pud_t *) spp_getpage();
			set_p4d(p4d, __p4d(__pa(pud) | _KERNPG_TABLE |
						_PAGE_USER));
		पूर्ण
		pud = pud_offset(p4d, (अचिन्हित दीर्घ)__va(phys));
		अगर (pud_none(*pud)) अणु
			pmd = (pmd_t *) spp_getpage();
			set_pud(pud, __pud(__pa(pmd) | _KERNPG_TABLE |
						_PAGE_USER));
		पूर्ण
		pmd = pmd_offset(pud, phys);
		BUG_ON(!pmd_none(*pmd));
		set_pmd(pmd, __pmd(phys | pgprot_val(prot)));
	पूर्ण
पूर्ण

व्योम __init init_extra_mapping_wb(अचिन्हित दीर्घ phys, अचिन्हित दीर्घ size)
अणु
	__init_extra_mapping(phys, size, _PAGE_CACHE_MODE_WB);
पूर्ण

व्योम __init init_extra_mapping_uc(अचिन्हित दीर्घ phys, अचिन्हित दीर्घ size)
अणु
	__init_extra_mapping(phys, size, _PAGE_CACHE_MODE_UC);
पूर्ण

/*
 * The head.S code sets up the kernel high mapping:
 *
 *   from __START_KERNEL_map to __START_KERNEL_map + size (== _end-_text)
 *
 * phys_base holds the negative offset to the kernel, which is added
 * to the compile समय generated pmds. This results in invalid pmds up
 * to the poपूर्णांक where we hit the physaddr 0 mapping.
 *
 * We limit the mappings to the region from _text to _brk_end.  _brk_end
 * is rounded up to the 2MB boundary. This catches the invalid pmds as
 * well, as they are located beक्रमe _text:
 */
व्योम __init cleanup_highmap(व्योम)
अणु
	अचिन्हित दीर्घ vaddr = __START_KERNEL_map;
	अचिन्हित दीर्घ vaddr_end = __START_KERNEL_map + KERNEL_IMAGE_SIZE;
	अचिन्हित दीर्घ end = roundup((अचिन्हित दीर्घ)_brk_end, PMD_SIZE) - 1;
	pmd_t *pmd = level2_kernel_pgt;

	/*
	 * Native path, max_pfn_mapped is not set yet.
	 * Xen has valid max_pfn_mapped set in
	 *	arch/x86/xen/mmu.c:xen_setup_kernel_pagetable().
	 */
	अगर (max_pfn_mapped)
		vaddr_end = __START_KERNEL_map + (max_pfn_mapped << PAGE_SHIFT);

	क्रम (; vaddr + PMD_SIZE - 1 < vaddr_end; pmd++, vaddr += PMD_SIZE) अणु
		अगर (pmd_none(*pmd))
			जारी;
		अगर (vaddr < (अचिन्हित दीर्घ) _text || vaddr > end)
			set_pmd(pmd, __pmd(0));
	पूर्ण
पूर्ण

/*
 * Create PTE level page table mapping क्रम physical addresses.
 * It वापसs the last physical address mapped.
 */
अटल अचिन्हित दीर्घ __meminit
phys_pte_init(pte_t *pte_page, अचिन्हित दीर्घ paddr, अचिन्हित दीर्घ paddr_end,
	      pgprot_t prot, bool init)
अणु
	अचिन्हित दीर्घ pages = 0, paddr_next;
	अचिन्हित दीर्घ paddr_last = paddr_end;
	pte_t *pte;
	पूर्णांक i;

	pte = pte_page + pte_index(paddr);
	i = pte_index(paddr);

	क्रम (; i < PTRS_PER_PTE; i++, paddr = paddr_next, pte++) अणु
		paddr_next = (paddr & PAGE_MASK) + PAGE_SIZE;
		अगर (paddr >= paddr_end) अणु
			अगर (!after_booपंचांगem &&
			    !e820__mapped_any(paddr & PAGE_MASK, paddr_next,
					     E820_TYPE_RAM) &&
			    !e820__mapped_any(paddr & PAGE_MASK, paddr_next,
					     E820_TYPE_RESERVED_KERN))
				set_pte_init(pte, __pte(0), init);
			जारी;
		पूर्ण

		/*
		 * We will re-use the existing mapping.
		 * Xen क्रम example has some special requirements, like mapping
		 * pagetable pages as RO. So assume someone who pre-setup
		 * these mappings are more पूर्णांकelligent.
		 */
		अगर (!pte_none(*pte)) अणु
			अगर (!after_booपंचांगem)
				pages++;
			जारी;
		पूर्ण

		अगर (0)
			pr_info("   pte=%p addr=%lx pte=%016lx\n", pte, paddr,
				pfn_pte(paddr >> PAGE_SHIFT, PAGE_KERNEL).pte);
		pages++;
		set_pte_init(pte, pfn_pte(paddr >> PAGE_SHIFT, prot), init);
		paddr_last = (paddr & PAGE_MASK) + PAGE_SIZE;
	पूर्ण

	update_page_count(PG_LEVEL_4K, pages);

	वापस paddr_last;
पूर्ण

/*
 * Create PMD level page table mapping क्रम physical addresses. The भव
 * and physical address have to be aligned at this level.
 * It वापसs the last physical address mapped.
 */
अटल अचिन्हित दीर्घ __meminit
phys_pmd_init(pmd_t *pmd_page, अचिन्हित दीर्घ paddr, अचिन्हित दीर्घ paddr_end,
	      अचिन्हित दीर्घ page_size_mask, pgprot_t prot, bool init)
अणु
	अचिन्हित दीर्घ pages = 0, paddr_next;
	अचिन्हित दीर्घ paddr_last = paddr_end;

	पूर्णांक i = pmd_index(paddr);

	क्रम (; i < PTRS_PER_PMD; i++, paddr = paddr_next) अणु
		pmd_t *pmd = pmd_page + pmd_index(paddr);
		pte_t *pte;
		pgprot_t new_prot = prot;

		paddr_next = (paddr & PMD_MASK) + PMD_SIZE;
		अगर (paddr >= paddr_end) अणु
			अगर (!after_booपंचांगem &&
			    !e820__mapped_any(paddr & PMD_MASK, paddr_next,
					     E820_TYPE_RAM) &&
			    !e820__mapped_any(paddr & PMD_MASK, paddr_next,
					     E820_TYPE_RESERVED_KERN))
				set_pmd_init(pmd, __pmd(0), init);
			जारी;
		पूर्ण

		अगर (!pmd_none(*pmd)) अणु
			अगर (!pmd_large(*pmd)) अणु
				spin_lock(&init_mm.page_table_lock);
				pte = (pte_t *)pmd_page_vaddr(*pmd);
				paddr_last = phys_pte_init(pte, paddr,
							   paddr_end, prot,
							   init);
				spin_unlock(&init_mm.page_table_lock);
				जारी;
			पूर्ण
			/*
			 * If we are ok with PG_LEVEL_2M mapping, then we will
			 * use the existing mapping,
			 *
			 * Otherwise, we will split the large page mapping but
			 * use the same existing protection bits except क्रम
			 * large page, so that we करोn't violate Intel's TLB
			 * Application note (317080) which says, जबतक changing
			 * the page sizes, new and old translations should
			 * not dअगरfer with respect to page frame and
			 * attributes.
			 */
			अगर (page_size_mask & (1 << PG_LEVEL_2M)) अणु
				अगर (!after_booपंचांगem)
					pages++;
				paddr_last = paddr_next;
				जारी;
			पूर्ण
			new_prot = pte_pgprot(pte_clrhuge(*(pte_t *)pmd));
		पूर्ण

		अगर (page_size_mask & (1<<PG_LEVEL_2M)) अणु
			pages++;
			spin_lock(&init_mm.page_table_lock);
			set_pte_init((pte_t *)pmd,
				     pfn_pte((paddr & PMD_MASK) >> PAGE_SHIFT,
					     __pgprot(pgprot_val(prot) | _PAGE_PSE)),
				     init);
			spin_unlock(&init_mm.page_table_lock);
			paddr_last = paddr_next;
			जारी;
		पूर्ण

		pte = alloc_low_page();
		paddr_last = phys_pte_init(pte, paddr, paddr_end, new_prot, init);

		spin_lock(&init_mm.page_table_lock);
		pmd_populate_kernel_init(&init_mm, pmd, pte, init);
		spin_unlock(&init_mm.page_table_lock);
	पूर्ण
	update_page_count(PG_LEVEL_2M, pages);
	वापस paddr_last;
पूर्ण

/*
 * Create PUD level page table mapping क्रम physical addresses. The भव
 * and physical address करो not have to be aligned at this level. KASLR can
 * अक्रमomize भव addresses up to this level.
 * It वापसs the last physical address mapped.
 */
अटल अचिन्हित दीर्घ __meminit
phys_pud_init(pud_t *pud_page, अचिन्हित दीर्घ paddr, अचिन्हित दीर्घ paddr_end,
	      अचिन्हित दीर्घ page_size_mask, pgprot_t _prot, bool init)
अणु
	अचिन्हित दीर्घ pages = 0, paddr_next;
	अचिन्हित दीर्घ paddr_last = paddr_end;
	अचिन्हित दीर्घ vaddr = (अचिन्हित दीर्घ)__va(paddr);
	पूर्णांक i = pud_index(vaddr);

	क्रम (; i < PTRS_PER_PUD; i++, paddr = paddr_next) अणु
		pud_t *pud;
		pmd_t *pmd;
		pgprot_t prot = _prot;

		vaddr = (अचिन्हित दीर्घ)__va(paddr);
		pud = pud_page + pud_index(vaddr);
		paddr_next = (paddr & PUD_MASK) + PUD_SIZE;

		अगर (paddr >= paddr_end) अणु
			अगर (!after_booपंचांगem &&
			    !e820__mapped_any(paddr & PUD_MASK, paddr_next,
					     E820_TYPE_RAM) &&
			    !e820__mapped_any(paddr & PUD_MASK, paddr_next,
					     E820_TYPE_RESERVED_KERN))
				set_pud_init(pud, __pud(0), init);
			जारी;
		पूर्ण

		अगर (!pud_none(*pud)) अणु
			अगर (!pud_large(*pud)) अणु
				pmd = pmd_offset(pud, 0);
				paddr_last = phys_pmd_init(pmd, paddr,
							   paddr_end,
							   page_size_mask,
							   prot, init);
				जारी;
			पूर्ण
			/*
			 * If we are ok with PG_LEVEL_1G mapping, then we will
			 * use the existing mapping.
			 *
			 * Otherwise, we will split the gbpage mapping but use
			 * the same existing protection  bits except क्रम large
			 * page, so that we करोn't violate Intel's TLB
			 * Application note (317080) which says, जबतक changing
			 * the page sizes, new and old translations should
			 * not dअगरfer with respect to page frame and
			 * attributes.
			 */
			अगर (page_size_mask & (1 << PG_LEVEL_1G)) अणु
				अगर (!after_booपंचांगem)
					pages++;
				paddr_last = paddr_next;
				जारी;
			पूर्ण
			prot = pte_pgprot(pte_clrhuge(*(pte_t *)pud));
		पूर्ण

		अगर (page_size_mask & (1<<PG_LEVEL_1G)) अणु
			pages++;
			spin_lock(&init_mm.page_table_lock);

			prot = __pgprot(pgprot_val(prot) | __PAGE_KERNEL_LARGE);

			set_pte_init((pte_t *)pud,
				     pfn_pte((paddr & PUD_MASK) >> PAGE_SHIFT,
					     prot),
				     init);
			spin_unlock(&init_mm.page_table_lock);
			paddr_last = paddr_next;
			जारी;
		पूर्ण

		pmd = alloc_low_page();
		paddr_last = phys_pmd_init(pmd, paddr, paddr_end,
					   page_size_mask, prot, init);

		spin_lock(&init_mm.page_table_lock);
		pud_populate_init(&init_mm, pud, pmd, init);
		spin_unlock(&init_mm.page_table_lock);
	पूर्ण

	update_page_count(PG_LEVEL_1G, pages);

	वापस paddr_last;
पूर्ण

अटल अचिन्हित दीर्घ __meminit
phys_p4d_init(p4d_t *p4d_page, अचिन्हित दीर्घ paddr, अचिन्हित दीर्घ paddr_end,
	      अचिन्हित दीर्घ page_size_mask, pgprot_t prot, bool init)
अणु
	अचिन्हित दीर्घ vaddr, vaddr_end, vaddr_next, paddr_next, paddr_last;

	paddr_last = paddr_end;
	vaddr = (अचिन्हित दीर्घ)__va(paddr);
	vaddr_end = (अचिन्हित दीर्घ)__va(paddr_end);

	अगर (!pgtable_l5_enabled())
		वापस phys_pud_init((pud_t *) p4d_page, paddr, paddr_end,
				     page_size_mask, prot, init);

	क्रम (; vaddr < vaddr_end; vaddr = vaddr_next) अणु
		p4d_t *p4d = p4d_page + p4d_index(vaddr);
		pud_t *pud;

		vaddr_next = (vaddr & P4D_MASK) + P4D_SIZE;
		paddr = __pa(vaddr);

		अगर (paddr >= paddr_end) अणु
			paddr_next = __pa(vaddr_next);
			अगर (!after_booपंचांगem &&
			    !e820__mapped_any(paddr & P4D_MASK, paddr_next,
					     E820_TYPE_RAM) &&
			    !e820__mapped_any(paddr & P4D_MASK, paddr_next,
					     E820_TYPE_RESERVED_KERN))
				set_p4d_init(p4d, __p4d(0), init);
			जारी;
		पूर्ण

		अगर (!p4d_none(*p4d)) अणु
			pud = pud_offset(p4d, 0);
			paddr_last = phys_pud_init(pud, paddr, __pa(vaddr_end),
					page_size_mask, prot, init);
			जारी;
		पूर्ण

		pud = alloc_low_page();
		paddr_last = phys_pud_init(pud, paddr, __pa(vaddr_end),
					   page_size_mask, prot, init);

		spin_lock(&init_mm.page_table_lock);
		p4d_populate_init(&init_mm, p4d, pud, init);
		spin_unlock(&init_mm.page_table_lock);
	पूर्ण

	वापस paddr_last;
पूर्ण

अटल अचिन्हित दीर्घ __meminit
__kernel_physical_mapping_init(अचिन्हित दीर्घ paddr_start,
			       अचिन्हित दीर्घ paddr_end,
			       अचिन्हित दीर्घ page_size_mask,
			       pgprot_t prot, bool init)
अणु
	bool pgd_changed = false;
	अचिन्हित दीर्घ vaddr, vaddr_start, vaddr_end, vaddr_next, paddr_last;

	paddr_last = paddr_end;
	vaddr = (अचिन्हित दीर्घ)__va(paddr_start);
	vaddr_end = (अचिन्हित दीर्घ)__va(paddr_end);
	vaddr_start = vaddr;

	क्रम (; vaddr < vaddr_end; vaddr = vaddr_next) अणु
		pgd_t *pgd = pgd_offset_k(vaddr);
		p4d_t *p4d;

		vaddr_next = (vaddr & PGसूची_MASK) + PGसूची_SIZE;

		अगर (pgd_val(*pgd)) अणु
			p4d = (p4d_t *)pgd_page_vaddr(*pgd);
			paddr_last = phys_p4d_init(p4d, __pa(vaddr),
						   __pa(vaddr_end),
						   page_size_mask,
						   prot, init);
			जारी;
		पूर्ण

		p4d = alloc_low_page();
		paddr_last = phys_p4d_init(p4d, __pa(vaddr), __pa(vaddr_end),
					   page_size_mask, prot, init);

		spin_lock(&init_mm.page_table_lock);
		अगर (pgtable_l5_enabled())
			pgd_populate_init(&init_mm, pgd, p4d, init);
		अन्यथा
			p4d_populate_init(&init_mm, p4d_offset(pgd, vaddr),
					  (pud_t *) p4d, init);

		spin_unlock(&init_mm.page_table_lock);
		pgd_changed = true;
	पूर्ण

	अगर (pgd_changed)
		sync_global_pgds(vaddr_start, vaddr_end - 1);

	वापस paddr_last;
पूर्ण


/*
 * Create page table mapping क्रम the physical memory क्रम specअगरic physical
 * addresses. Note that it can only be used to populate non-present entries.
 * The भव and physical addresses have to be aligned on PMD level
 * करोwn. It वापसs the last physical address mapped.
 */
अचिन्हित दीर्घ __meminit
kernel_physical_mapping_init(अचिन्हित दीर्घ paddr_start,
			     अचिन्हित दीर्घ paddr_end,
			     अचिन्हित दीर्घ page_size_mask, pgprot_t prot)
अणु
	वापस __kernel_physical_mapping_init(paddr_start, paddr_end,
					      page_size_mask, prot, true);
पूर्ण

/*
 * This function is similar to kernel_physical_mapping_init() above with the
 * exception that it uses set_अणुpud,pmdपूर्ण() instead of the set_अणुpud,pteपूर्ण_safe()
 * when updating the mapping. The caller is responsible to flush the TLBs after
 * the function वापसs.
 */
अचिन्हित दीर्घ __meminit
kernel_physical_mapping_change(अचिन्हित दीर्घ paddr_start,
			       अचिन्हित दीर्घ paddr_end,
			       अचिन्हित दीर्घ page_size_mask)
अणु
	वापस __kernel_physical_mapping_init(paddr_start, paddr_end,
					      page_size_mask, PAGE_KERNEL,
					      false);
पूर्ण

#अगर_अघोषित CONFIG_NUMA
व्योम __init iniपंचांगem_init(व्योम)
अणु
	memblock_set_node(0, PHYS_ADDR_MAX, &memblock.memory, 0);
पूर्ण
#पूर्ण_अगर

व्योम __init paging_init(व्योम)
अणु
	sparse_init();

	/*
	 * clear the शेष setting with node 0
	 * note: करोn't use nodes_clear here, that is really clearing when
	 *	 numa support is not compiled in, and later node_set_state
	 *	 will not set it back.
	 */
	node_clear_state(0, N_MEMORY);
	node_clear_state(0, N_NORMAL_MEMORY);

	zone_sizes_init();
पूर्ण

#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
#घोषणा PAGE_UNUSED 0xFD

/*
 * The unused vmemmap range, which was not yet स_रखो(PAGE_UNUSED), ranges
 * from unused_pmd_start to next PMD_SIZE boundary.
 */
अटल अचिन्हित दीर्घ unused_pmd_start __meminitdata;

अटल व्योम __meminit vmemmap_flush_unused_pmd(व्योम)
अणु
	अगर (!unused_pmd_start)
		वापस;
	/*
	 * Clears (unused_pmd_start, PMD_END]
	 */
	स_रखो((व्योम *)unused_pmd_start, PAGE_UNUSED,
	       ALIGN(unused_pmd_start, PMD_SIZE) - unused_pmd_start);
	unused_pmd_start = 0;
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
/* Returns true अगर the PMD is completely unused and thus it can be मुक्तd */
अटल bool __meminit vmemmap_pmd_is_unused(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ start = ALIGN_DOWN(addr, PMD_SIZE);

	/*
	 * Flush the unused range cache to ensure that स_प्रथम_inv() will work
	 * क्रम the whole range.
	 */
	vmemmap_flush_unused_pmd();
	स_रखो((व्योम *)addr, PAGE_UNUSED, end - addr);

	वापस !स_प्रथम_inv((व्योम *)start, PAGE_UNUSED, PMD_SIZE);
पूर्ण
#पूर्ण_अगर

अटल व्योम __meminit __vmemmap_use_sub_pmd(अचिन्हित दीर्घ start)
अणु
	/*
	 * As we expect to add in the same granularity as we हटाओ, it's
	 * sufficient to mark only some piece used to block the memmap page from
	 * getting हटाओd when removing some other adjacent memmap (just in
	 * हाल the first memmap never माला_लो initialized e.g., because the memory
	 * block never माला_लो onlined).
	 */
	स_रखो((व्योम *)start, 0, माप(काष्ठा page));
पूर्ण

अटल व्योम __meminit vmemmap_use_sub_pmd(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	/*
	 * We only optimize अगर the new used range directly follows the
	 * previously unused range (esp., when populating consecutive sections).
	 */
	अगर (unused_pmd_start == start) अणु
		अगर (likely(IS_ALIGNED(end, PMD_SIZE)))
			unused_pmd_start = 0;
		अन्यथा
			unused_pmd_start = end;
		वापस;
	पूर्ण

	/*
	 * If the range करोes not contiguously follows previous one, make sure
	 * to mark the unused range of the previous one so it can be हटाओd.
	 */
	vmemmap_flush_unused_pmd();
	__vmemmap_use_sub_pmd(start);
पूर्ण


अटल व्योम __meminit vmemmap_use_new_sub_pmd(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	vmemmap_flush_unused_pmd();

	/*
	 * Could be our memmap page is filled with PAGE_UNUSED alपढ़ोy from a
	 * previous हटाओ. Make sure to reset it.
	 */
	__vmemmap_use_sub_pmd(start);

	/*
	 * Mark with PAGE_UNUSED the unused parts of the new memmap range
	 */
	अगर (!IS_ALIGNED(start, PMD_SIZE))
		स_रखो((व्योम *)start, PAGE_UNUSED,
			start - ALIGN_DOWN(start, PMD_SIZE));

	/*
	 * We want to aव्योम स_रखो(PAGE_UNUSED) when populating the vmemmap of
	 * consecutive sections. Remember क्रम the last added PMD where the
	 * unused range begins.
	 */
	अगर (!IS_ALIGNED(end, PMD_SIZE))
		unused_pmd_start = end;
पूर्ण
#पूर्ण_अगर

/*
 * Memory hotplug specअगरic functions
 */
#अगर_घोषित CONFIG_MEMORY_HOTPLUG
/*
 * After memory hotplug the variables max_pfn, max_low_pfn and high_memory need
 * updating.
 */
अटल व्योम update_end_of_memory_vars(u64 start, u64 size)
अणु
	अचिन्हित दीर्घ end_pfn = PFN_UP(start + size);

	अगर (end_pfn > max_pfn) अणु
		max_pfn = end_pfn;
		max_low_pfn = end_pfn;
		high_memory = (व्योम *)__va(max_pfn * PAGE_SIZE - 1) + 1;
	पूर्ण
पूर्ण

पूर्णांक add_pages(पूर्णांक nid, अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ nr_pages,
	      काष्ठा mhp_params *params)
अणु
	पूर्णांक ret;

	ret = __add_pages(nid, start_pfn, nr_pages, params);
	WARN_ON_ONCE(ret);

	/* update max_pfn, max_low_pfn and high_memory */
	update_end_of_memory_vars(start_pfn << PAGE_SHIFT,
				  nr_pages << PAGE_SHIFT);

	वापस ret;
पूर्ण

पूर्णांक arch_add_memory(पूर्णांक nid, u64 start, u64 size,
		    काष्ठा mhp_params *params)
अणु
	अचिन्हित दीर्घ start_pfn = start >> PAGE_SHIFT;
	अचिन्हित दीर्घ nr_pages = size >> PAGE_SHIFT;

	init_memory_mapping(start, start + size, params->pgprot);

	वापस add_pages(nid, start_pfn, nr_pages, params);
पूर्ण

अटल व्योम __meminit मुक्त_pagetable(काष्ठा page *page, पूर्णांक order)
अणु
	अचिन्हित दीर्घ magic;
	अचिन्हित पूर्णांक nr_pages = 1 << order;

	/* booपंचांगem page has reserved flag */
	अगर (PageReserved(page)) अणु
		__ClearPageReserved(page);

		magic = (अचिन्हित दीर्घ)page->मुक्तlist;
		अगर (magic == SECTION_INFO || magic == MIX_SECTION_INFO) अणु
			जबतक (nr_pages--)
				put_page_booपंचांगem(page++);
		पूर्ण अन्यथा
			जबतक (nr_pages--)
				मुक्त_reserved_page(page++);
	पूर्ण अन्यथा
		मुक्त_pages((अचिन्हित दीर्घ)page_address(page), order);
पूर्ण

अटल व्योम __meminit मुक्त_hugepage_table(काष्ठा page *page,
		काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अगर (alपंचांगap)
		vmem_alपंचांगap_मुक्त(alपंचांगap, PMD_SIZE / PAGE_SIZE);
	अन्यथा
		मुक्त_pagetable(page, get_order(PMD_SIZE));
पूर्ण

अटल व्योम __meminit मुक्त_pte_table(pte_t *pte_start, pmd_t *pmd)
अणु
	pte_t *pte;
	पूर्णांक i;

	क्रम (i = 0; i < PTRS_PER_PTE; i++) अणु
		pte = pte_start + i;
		अगर (!pte_none(*pte))
			वापस;
	पूर्ण

	/* मुक्त a pte talbe */
	मुक्त_pagetable(pmd_page(*pmd), 0);
	spin_lock(&init_mm.page_table_lock);
	pmd_clear(pmd);
	spin_unlock(&init_mm.page_table_lock);
पूर्ण

अटल व्योम __meminit मुक्त_pmd_table(pmd_t *pmd_start, pud_t *pud)
अणु
	pmd_t *pmd;
	पूर्णांक i;

	क्रम (i = 0; i < PTRS_PER_PMD; i++) अणु
		pmd = pmd_start + i;
		अगर (!pmd_none(*pmd))
			वापस;
	पूर्ण

	/* मुक्त a pmd talbe */
	मुक्त_pagetable(pud_page(*pud), 0);
	spin_lock(&init_mm.page_table_lock);
	pud_clear(pud);
	spin_unlock(&init_mm.page_table_lock);
पूर्ण

अटल व्योम __meminit मुक्त_pud_table(pud_t *pud_start, p4d_t *p4d)
अणु
	pud_t *pud;
	पूर्णांक i;

	क्रम (i = 0; i < PTRS_PER_PUD; i++) अणु
		pud = pud_start + i;
		अगर (!pud_none(*pud))
			वापस;
	पूर्ण

	/* मुक्त a pud talbe */
	मुक्त_pagetable(p4d_page(*p4d), 0);
	spin_lock(&init_mm.page_table_lock);
	p4d_clear(p4d);
	spin_unlock(&init_mm.page_table_lock);
पूर्ण

अटल व्योम __meminit
हटाओ_pte_table(pte_t *pte_start, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
		 bool direct)
अणु
	अचिन्हित दीर्घ next, pages = 0;
	pte_t *pte;
	phys_addr_t phys_addr;

	pte = pte_start + pte_index(addr);
	क्रम (; addr < end; addr = next, pte++) अणु
		next = (addr + PAGE_SIZE) & PAGE_MASK;
		अगर (next > end)
			next = end;

		अगर (!pte_present(*pte))
			जारी;

		/*
		 * We mapped [0,1G) memory as identity mapping when
		 * initializing, in arch/x86/kernel/head_64.S. These
		 * pagetables cannot be हटाओd.
		 */
		phys_addr = pte_val(*pte) + (addr & PAGE_MASK);
		अगर (phys_addr < (phys_addr_t)0x40000000)
			वापस;

		अगर (!direct)
			मुक्त_pagetable(pte_page(*pte), 0);

		spin_lock(&init_mm.page_table_lock);
		pte_clear(&init_mm, addr, pte);
		spin_unlock(&init_mm.page_table_lock);

		/* For non-direct mapping, pages means nothing. */
		pages++;
	पूर्ण

	/* Call मुक्त_pte_table() in हटाओ_pmd_table(). */
	flush_tlb_all();
	अगर (direct)
		update_page_count(PG_LEVEL_4K, -pages);
पूर्ण

अटल व्योम __meminit
हटाओ_pmd_table(pmd_t *pmd_start, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
		 bool direct, काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ next, pages = 0;
	pte_t *pte_base;
	pmd_t *pmd;

	pmd = pmd_start + pmd_index(addr);
	क्रम (; addr < end; addr = next, pmd++) अणु
		next = pmd_addr_end(addr, end);

		अगर (!pmd_present(*pmd))
			जारी;

		अगर (pmd_large(*pmd)) अणु
			अगर (IS_ALIGNED(addr, PMD_SIZE) &&
			    IS_ALIGNED(next, PMD_SIZE)) अणु
				अगर (!direct)
					मुक्त_hugepage_table(pmd_page(*pmd),
							    alपंचांगap);

				spin_lock(&init_mm.page_table_lock);
				pmd_clear(pmd);
				spin_unlock(&init_mm.page_table_lock);
				pages++;
			पूर्ण
#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
			अन्यथा अगर (vmemmap_pmd_is_unused(addr, next)) अणु
					मुक्त_hugepage_table(pmd_page(*pmd),
							    alपंचांगap);
					spin_lock(&init_mm.page_table_lock);
					pmd_clear(pmd);
					spin_unlock(&init_mm.page_table_lock);
			पूर्ण
#पूर्ण_अगर
			जारी;
		पूर्ण

		pte_base = (pte_t *)pmd_page_vaddr(*pmd);
		हटाओ_pte_table(pte_base, addr, next, direct);
		मुक्त_pte_table(pte_base, pmd);
	पूर्ण

	/* Call मुक्त_pmd_table() in हटाओ_pud_table(). */
	अगर (direct)
		update_page_count(PG_LEVEL_2M, -pages);
पूर्ण

अटल व्योम __meminit
हटाओ_pud_table(pud_t *pud_start, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
		 काष्ठा vmem_alपंचांगap *alपंचांगap, bool direct)
अणु
	अचिन्हित दीर्घ next, pages = 0;
	pmd_t *pmd_base;
	pud_t *pud;

	pud = pud_start + pud_index(addr);
	क्रम (; addr < end; addr = next, pud++) अणु
		next = pud_addr_end(addr, end);

		अगर (!pud_present(*pud))
			जारी;

		अगर (pud_large(*pud) &&
		    IS_ALIGNED(addr, PUD_SIZE) &&
		    IS_ALIGNED(next, PUD_SIZE)) अणु
			spin_lock(&init_mm.page_table_lock);
			pud_clear(pud);
			spin_unlock(&init_mm.page_table_lock);
			pages++;
			जारी;
		पूर्ण

		pmd_base = pmd_offset(pud, 0);
		हटाओ_pmd_table(pmd_base, addr, next, direct, alपंचांगap);
		मुक्त_pmd_table(pmd_base, pud);
	पूर्ण

	अगर (direct)
		update_page_count(PG_LEVEL_1G, -pages);
पूर्ण

अटल व्योम __meminit
हटाओ_p4d_table(p4d_t *p4d_start, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ end,
		 काष्ठा vmem_alपंचांगap *alपंचांगap, bool direct)
अणु
	अचिन्हित दीर्घ next, pages = 0;
	pud_t *pud_base;
	p4d_t *p4d;

	p4d = p4d_start + p4d_index(addr);
	क्रम (; addr < end; addr = next, p4d++) अणु
		next = p4d_addr_end(addr, end);

		अगर (!p4d_present(*p4d))
			जारी;

		BUILD_BUG_ON(p4d_large(*p4d));

		pud_base = pud_offset(p4d, 0);
		हटाओ_pud_table(pud_base, addr, next, alपंचांगap, direct);
		/*
		 * For 4-level page tables we करो not want to मुक्त PUDs, but in the
		 * 5-level हाल we should मुक्त them. This code will have to change
		 * to adapt क्रम boot-समय चयनing between 4 and 5 level page tables.
		 */
		अगर (pgtable_l5_enabled())
			मुक्त_pud_table(pud_base, p4d);
	पूर्ण

	अगर (direct)
		update_page_count(PG_LEVEL_512G, -pages);
पूर्ण

/* start and end are both भव address. */
अटल व्योम __meminit
हटाओ_pagetable(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, bool direct,
		काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ next;
	अचिन्हित दीर्घ addr;
	pgd_t *pgd;
	p4d_t *p4d;

	क्रम (addr = start; addr < end; addr = next) अणु
		next = pgd_addr_end(addr, end);

		pgd = pgd_offset_k(addr);
		अगर (!pgd_present(*pgd))
			जारी;

		p4d = p4d_offset(pgd, 0);
		हटाओ_p4d_table(p4d, addr, next, alपंचांगap, direct);
	पूर्ण

	flush_tlb_all();
पूर्ण

व्योम __ref vmemmap_मुक्त(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
		काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	VM_BUG_ON(!IS_ALIGNED(start, PAGE_SIZE));
	VM_BUG_ON(!IS_ALIGNED(end, PAGE_SIZE));

	हटाओ_pagetable(start, end, false, alपंचांगap);
पूर्ण

अटल व्योम __meminit
kernel_physical_mapping_हटाओ(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	start = (अचिन्हित दीर्घ)__va(start);
	end = (अचिन्हित दीर्घ)__va(end);

	हटाओ_pagetable(start, end, true, शून्य);
पूर्ण

व्योम __ref arch_हटाओ_memory(पूर्णांक nid, u64 start, u64 size,
			      काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ start_pfn = start >> PAGE_SHIFT;
	अचिन्हित दीर्घ nr_pages = size >> PAGE_SHIFT;

	__हटाओ_pages(start_pfn, nr_pages, alपंचांगap);
	kernel_physical_mapping_हटाओ(start, start + size);
पूर्ण
#पूर्ण_अगर /* CONFIG_MEMORY_HOTPLUG */

अटल काष्ठा kcore_list kcore_vsyscall;

अटल व्योम __init रेजिस्टर_page_booपंचांगem_info(व्योम)
अणु
#अगर_घोषित CONFIG_NUMA
	पूर्णांक i;

	क्रम_each_online_node(i)
		रेजिस्टर_page_booपंचांगem_info_node(NODE_DATA(i));
#पूर्ण_अगर
पूर्ण

/*
 * Pre-allocates page-table pages क्रम the vदो_स्मृति area in the kernel page-table.
 * Only the level which needs to be synchronized between all page-tables is
 * allocated because the synchronization can be expensive.
 */
अटल व्योम __init pपुनः_स्मृतिate_vदो_स्मृति_pages(व्योम)
अणु
	अचिन्हित दीर्घ addr;
	स्थिर अक्षर *lvl;

	क्रम (addr = VMALLOC_START; addr <= VMALLOC_END; addr = ALIGN(addr + 1, PGसूची_SIZE)) अणु
		pgd_t *pgd = pgd_offset_k(addr);
		p4d_t *p4d;
		pud_t *pud;

		lvl = "p4d";
		p4d = p4d_alloc(&init_mm, pgd, addr);
		अगर (!p4d)
			जाओ failed;

		अगर (pgtable_l5_enabled())
			जारी;

		/*
		 * The goal here is to allocate all possibly required
		 * hardware page tables poपूर्णांकed to by the top hardware
		 * level.
		 *
		 * On 4-level प्रणालीs, the P4D layer is folded away and
		 * the above code करोes no pपुनः_स्मृतिation.  Below, go करोwn
		 * to the pud _software_ level to ensure the second
		 * hardware level is allocated on 4-level प्रणालीs too.
		 */
		lvl = "pud";
		pud = pud_alloc(&init_mm, p4d, addr);
		अगर (!pud)
			जाओ failed;
	पूर्ण

	वापस;

failed:

	/*
	 * The pages have to be there now or they will be missing in
	 * process page-tables later.
	 */
	panic("Failed to pre-allocate %s pages for vmalloc area\n", lvl);
पूर्ण

व्योम __init mem_init(व्योम)
अणु
	pci_iommu_alloc();

	/* clear_bss() alपढ़ोy clear the empty_zero_page */

	/* this will put all memory onto the मुक्तlists */
	memblock_मुक्त_all();
	after_booपंचांगem = 1;
	x86_init.hyper.init_after_booपंचांगem();

	/*
	 * Must be करोne after boot memory is put on मुक्तlist, because here we
	 * might set fields in deferred काष्ठा pages that have not yet been
	 * initialized, and memblock_मुक्त_all() initializes all the reserved
	 * deferred pages क्रम us.
	 */
	रेजिस्टर_page_booपंचांगem_info();

	/* Register memory areas क्रम /proc/kcore */
	अगर (get_gate_vma(&init_mm))
		kclist_add(&kcore_vsyscall, (व्योम *)VSYSCALL_ADDR, PAGE_SIZE, KCORE_USER);

	pपुनः_स्मृतिate_vदो_स्मृति_pages();
पूर्ण

#अगर_घोषित CONFIG_DEFERRED_STRUCT_PAGE_INIT
पूर्णांक __init deferred_page_init_max_thपढ़ोs(स्थिर काष्ठा cpumask *node_cpumask)
अणु
	/*
	 * More CPUs always led to greater speedups on tested प्रणालीs, up to
	 * all the nodes' CPUs.  Use all since the प्रणाली is otherwise idle
	 * now.
	 */
	वापस max_t(पूर्णांक, cpumask_weight(node_cpumask), 1);
पूर्ण
#पूर्ण_अगर

पूर्णांक kernel_set_to_पढ़ोonly;

व्योम mark_rodata_ro(व्योम)
अणु
	अचिन्हित दीर्घ start = PFN_ALIGN(_text);
	अचिन्हित दीर्घ rodata_start = PFN_ALIGN(__start_rodata);
	अचिन्हित दीर्घ end = (अचिन्हित दीर्घ)__end_rodata_hpage_align;
	अचिन्हित दीर्घ text_end = PFN_ALIGN(_etext);
	अचिन्हित दीर्घ rodata_end = PFN_ALIGN(__end_rodata);
	अचिन्हित दीर्घ all_end;

	prपूर्णांकk(KERN_INFO "Write protecting the kernel read-only data: %luk\n",
	       (end - start) >> 10);
	set_memory_ro(start, (end - start) >> PAGE_SHIFT);

	kernel_set_to_पढ़ोonly = 1;

	/*
	 * The rodata/data/bss/brk section (but not the kernel text!)
	 * should also be not-executable.
	 *
	 * We align all_end to PMD_SIZE because the existing mapping
	 * is a full PMD. If we would align _brk_end to PAGE_SIZE we
	 * split the PMD and the reminder between _brk_end and the end
	 * of the PMD will reमुख्य mapped executable.
	 *
	 * Any PMD which was setup after the one which covers _brk_end
	 * has been zapped alपढ़ोy via cleanup_highmem().
	 */
	all_end = roundup((अचिन्हित दीर्घ)_brk_end, PMD_SIZE);
	set_memory_nx(text_end, (all_end - text_end) >> PAGE_SHIFT);

	set_ftrace_ops_ro();

#अगर_घोषित CONFIG_CPA_DEBUG
	prपूर्णांकk(KERN_INFO "Testing CPA: undo %lx-%lx\n", start, end);
	set_memory_rw(start, (end-start) >> PAGE_SHIFT);

	prपूर्णांकk(KERN_INFO "Testing CPA: again\n");
	set_memory_ro(start, (end-start) >> PAGE_SHIFT);
#पूर्ण_अगर

	मुक्त_kernel_image_pages("unused kernel image (text/rodata gap)",
				(व्योम *)text_end, (व्योम *)rodata_start);
	मुक्त_kernel_image_pages("unused kernel image (rodata/data gap)",
				(व्योम *)rodata_end, (व्योम *)_sdata);

	debug_checkwx();
पूर्ण

पूर्णांक kern_addr_valid(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित दीर्घ above = ((दीर्घ)addr) >> __VIRTUAL_MASK_SHIFT;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	अगर (above != 0 && above != -1UL)
		वापस 0;

	pgd = pgd_offset_k(addr);
	अगर (pgd_none(*pgd))
		वापस 0;

	p4d = p4d_offset(pgd, addr);
	अगर (p4d_none(*p4d))
		वापस 0;

	pud = pud_offset(p4d, addr);
	अगर (pud_none(*pud))
		वापस 0;

	अगर (pud_large(*pud))
		वापस pfn_valid(pud_pfn(*pud));

	pmd = pmd_offset(pud, addr);
	अगर (pmd_none(*pmd))
		वापस 0;

	अगर (pmd_large(*pmd))
		वापस pfn_valid(pmd_pfn(*pmd));

	pte = pte_offset_kernel(pmd, addr);
	अगर (pte_none(*pte))
		वापस 0;

	वापस pfn_valid(pte_pfn(*pte));
पूर्ण

/*
 * Block size is the minimum amount of memory which can be hotplugged or
 * hotहटाओd. It must be घातer of two and must be equal or larger than
 * MIN_MEMORY_BLOCK_SIZE.
 */
#घोषणा MAX_BLOCK_SIZE (2UL << 30)

/* Amount of ram needed to start using large blocks */
#घोषणा MEM_SIZE_FOR_LARGE_BLOCK (64UL << 30)

/* Adjustable memory block size */
अटल अचिन्हित दीर्घ set_memory_block_size;
पूर्णांक __init set_memory_block_size_order(अचिन्हित पूर्णांक order)
अणु
	अचिन्हित दीर्घ size = 1UL << order;

	अगर (size > MEM_SIZE_FOR_LARGE_BLOCK || size < MIN_MEMORY_BLOCK_SIZE)
		वापस -EINVAL;

	set_memory_block_size = size;
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ probe_memory_block_size(व्योम)
अणु
	अचिन्हित दीर्घ boot_mem_end = max_pfn << PAGE_SHIFT;
	अचिन्हित दीर्घ bz;

	/* If memory block size has been set, then use it */
	bz = set_memory_block_size;
	अगर (bz)
		जाओ करोne;

	/* Use regular block अगर RAM is smaller than MEM_SIZE_FOR_LARGE_BLOCK */
	अगर (boot_mem_end < MEM_SIZE_FOR_LARGE_BLOCK) अणु
		bz = MIN_MEMORY_BLOCK_SIZE;
		जाओ करोne;
	पूर्ण

	/*
	 * Use max block size to minimize overhead on bare metal, where
	 * alignment क्रम memory hotplug isn't a concern.
	 */
	अगर (!boot_cpu_has(X86_FEATURE_HYPERVISOR)) अणु
		bz = MAX_BLOCK_SIZE;
		जाओ करोne;
	पूर्ण

	/* Find the largest allowed block size that aligns to memory end */
	क्रम (bz = MAX_BLOCK_SIZE; bz > MIN_MEMORY_BLOCK_SIZE; bz >>= 1) अणु
		अगर (IS_ALIGNED(boot_mem_end, bz))
			अवरोध;
	पूर्ण
करोne:
	pr_info("x86/mm: Memory block size: %ldMB\n", bz >> 20);

	वापस bz;
पूर्ण

अटल अचिन्हित दीर्घ memory_block_size_probed;
अचिन्हित दीर्घ memory_block_size_bytes(व्योम)
अणु
	अगर (!memory_block_size_probed)
		memory_block_size_probed = probe_memory_block_size();

	वापस memory_block_size_probed;
पूर्ण

#अगर_घोषित CONFIG_SPARSEMEM_VMEMMAP
/*
 * Initialise the sparsemem vmemmap using huge-pages at the PMD level.
 */
अटल दीर्घ __meminitdata addr_start, addr_end;
अटल व्योम __meminitdata *p_start, *p_end;
अटल पूर्णांक __meminitdata node_start;

अटल पूर्णांक __meminit vmemmap_populate_hugepages(अचिन्हित दीर्घ start,
		अचिन्हित दीर्घ end, पूर्णांक node, काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ next;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	क्रम (addr = start; addr < end; addr = next) अणु
		next = pmd_addr_end(addr, end);

		pgd = vmemmap_pgd_populate(addr, node);
		अगर (!pgd)
			वापस -ENOMEM;

		p4d = vmemmap_p4d_populate(pgd, addr, node);
		अगर (!p4d)
			वापस -ENOMEM;

		pud = vmemmap_pud_populate(p4d, addr, node);
		अगर (!pud)
			वापस -ENOMEM;

		pmd = pmd_offset(pud, addr);
		अगर (pmd_none(*pmd)) अणु
			व्योम *p;

			p = vmemmap_alloc_block_buf(PMD_SIZE, node, alपंचांगap);
			अगर (p) अणु
				pte_t entry;

				entry = pfn_pte(__pa(p) >> PAGE_SHIFT,
						PAGE_KERNEL_LARGE);
				set_pmd(pmd, __pmd(pte_val(entry)));

				/* check to see अगर we have contiguous blocks */
				अगर (p_end != p || node_start != node) अणु
					अगर (p_start)
						pr_debug(" [%lx-%lx] PMD -> [%p-%p] on node %d\n",
						       addr_start, addr_end-1, p_start, p_end-1, node_start);
					addr_start = addr;
					node_start = node;
					p_start = p;
				पूर्ण

				addr_end = addr + PMD_SIZE;
				p_end = p + PMD_SIZE;

				अगर (!IS_ALIGNED(addr, PMD_SIZE) ||
				    !IS_ALIGNED(next, PMD_SIZE))
					vmemmap_use_new_sub_pmd(addr, next);

				जारी;
			पूर्ण अन्यथा अगर (alपंचांगap)
				वापस -ENOMEM; /* no fallback */
		पूर्ण अन्यथा अगर (pmd_large(*pmd)) अणु
			vmemmap_verअगरy((pte_t *)pmd, node, addr, next);
			vmemmap_use_sub_pmd(addr, next);
			जारी;
		पूर्ण
		अगर (vmemmap_populate_basepages(addr, next, node, शून्य))
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक __meminit vmemmap_populate(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end, पूर्णांक node,
		काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	पूर्णांक err;

	VM_BUG_ON(!IS_ALIGNED(start, PAGE_SIZE));
	VM_BUG_ON(!IS_ALIGNED(end, PAGE_SIZE));

	अगर (end - start < PAGES_PER_SECTION * माप(काष्ठा page))
		err = vmemmap_populate_basepages(start, end, node, शून्य);
	अन्यथा अगर (boot_cpu_has(X86_FEATURE_PSE))
		err = vmemmap_populate_hugepages(start, end, node, alपंचांगap);
	अन्यथा अगर (alपंचांगap) अणु
		pr_err_once("%s: no cpu support for altmap allocations\n",
				__func__);
		err = -ENOMEM;
	पूर्ण अन्यथा
		err = vmemmap_populate_basepages(start, end, node, शून्य);
	अगर (!err)
		sync_global_pgds(start, end - 1);
	वापस err;
पूर्ण

#अगर defined(CONFIG_MEMORY_HOTPLUG_SPARSE) && defined(CONFIG_HAVE_BOOTMEM_INFO_NODE)
व्योम रेजिस्टर_page_booपंचांगem_memmap(अचिन्हित दीर्घ section_nr,
				  काष्ठा page *start_page, अचिन्हित दीर्घ nr_pages)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)start_page;
	अचिन्हित दीर्घ end = (अचिन्हित दीर्घ)(start_page + nr_pages);
	अचिन्हित दीर्घ next;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	अचिन्हित पूर्णांक nr_pmd_pages;
	काष्ठा page *page;

	क्रम (; addr < end; addr = next) अणु
		pte_t *pte = शून्य;

		pgd = pgd_offset_k(addr);
		अगर (pgd_none(*pgd)) अणु
			next = (addr + PAGE_SIZE) & PAGE_MASK;
			जारी;
		पूर्ण
		get_page_booपंचांगem(section_nr, pgd_page(*pgd), MIX_SECTION_INFO);

		p4d = p4d_offset(pgd, addr);
		अगर (p4d_none(*p4d)) अणु
			next = (addr + PAGE_SIZE) & PAGE_MASK;
			जारी;
		पूर्ण
		get_page_booपंचांगem(section_nr, p4d_page(*p4d), MIX_SECTION_INFO);

		pud = pud_offset(p4d, addr);
		अगर (pud_none(*pud)) अणु
			next = (addr + PAGE_SIZE) & PAGE_MASK;
			जारी;
		पूर्ण
		get_page_booपंचांगem(section_nr, pud_page(*pud), MIX_SECTION_INFO);

		अगर (!boot_cpu_has(X86_FEATURE_PSE)) अणु
			next = (addr + PAGE_SIZE) & PAGE_MASK;
			pmd = pmd_offset(pud, addr);
			अगर (pmd_none(*pmd))
				जारी;
			get_page_booपंचांगem(section_nr, pmd_page(*pmd),
					 MIX_SECTION_INFO);

			pte = pte_offset_kernel(pmd, addr);
			अगर (pte_none(*pte))
				जारी;
			get_page_booपंचांगem(section_nr, pte_page(*pte),
					 SECTION_INFO);
		पूर्ण अन्यथा अणु
			next = pmd_addr_end(addr, end);

			pmd = pmd_offset(pud, addr);
			अगर (pmd_none(*pmd))
				जारी;

			nr_pmd_pages = 1 << get_order(PMD_SIZE);
			page = pmd_page(*pmd);
			जबतक (nr_pmd_pages--)
				get_page_booपंचांगem(section_nr, page++,
						 SECTION_INFO);
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

व्योम __meminit vmemmap_populate_prपूर्णांक_last(व्योम)
अणु
	अगर (p_start) अणु
		pr_debug(" [%lx-%lx] PMD -> [%p-%p] on node %d\n",
			addr_start, addr_end-1, p_start, p_end-1, node_start);
		p_start = शून्य;
		p_end = शून्य;
		node_start = 0;
	पूर्ण
पूर्ण
#पूर्ण_अगर
