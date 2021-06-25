<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * srmmu.c:  SRMMU specअगरic routines क्रम memory management.
 *
 * Copyright (C) 1995 David S. Miller  (davem@caip.rutgers.edu)
 * Copyright (C) 1995,2002 Pete Zaitcev (zaitcev@yahoo.com)
 * Copyright (C) 1996 Eddie C. Dost    (ecd@skynet.be)
 * Copyright (C) 1997,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 * Copyright (C) 1999,2000 Anton Blanअक्षरd (anton@samba.org)
 */

#समावेश <linux/seq_file.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/memblock.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/log2.h>
#समावेश <linux/gfp.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/io-unit.h>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/pgtable.h>
#समावेश <यंत्र/bitext.h>
#समावेश <यंत्र/vaddrs.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/mbus.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/asi.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/पन.स>

/* Now the cpu specअगरic definitions. */
#समावेश <यंत्र/turbosparc.h>
#समावेश <यंत्र/tsunami.h>
#समावेश <यंत्र/viking.h>
#समावेश <यंत्र/swअगरt.h>
#समावेश <यंत्र/leon.h>
#समावेश <यंत्र/mxcc.h>
#समावेश <यंत्र/ross.h>

#समावेश "mm_32.h"

क्रमागत mbus_module srmmu_modtype;
अटल अचिन्हित पूर्णांक hwbug_biपंचांगask;
पूर्णांक vac_cache_size;
EXPORT_SYMBOL(vac_cache_size);
पूर्णांक vac_line_size;

बाह्य काष्ठा resource sparc_iomap;

बाह्य अचिन्हित दीर्घ last_valid_pfn;

अटल pgd_t *srmmu_swapper_pg_dir;

स्थिर काष्ठा sparc32_cachetlb_ops *sparc32_cachetlb_ops;
EXPORT_SYMBOL(sparc32_cachetlb_ops);

#अगर_घोषित CONFIG_SMP
स्थिर काष्ठा sparc32_cachetlb_ops *local_ops;

#घोषणा FLUSH_BEGIN(mm)
#घोषणा FLUSH_END
#अन्यथा
#घोषणा FLUSH_BEGIN(mm) अगर ((mm)->context != NO_CONTEXT) अणु
#घोषणा FLUSH_END	पूर्ण
#पूर्ण_अगर

पूर्णांक flush_page_क्रम_dma_global = 1;

अक्षर *srmmu_name;

ctxd_t *srmmu_ctx_table_phys;
अटल ctxd_t *srmmu_context_table;

पूर्णांक viking_mxcc_present;
अटल DEFINE_SPINLOCK(srmmu_context_spinlock);

अटल पूर्णांक is_hypersparc;

अटल पूर्णांक srmmu_cache_pagetables;

/* these will be initialized in srmmu_nocache_calcsize() */
अटल अचिन्हित दीर्घ srmmu_nocache_size;
अटल अचिन्हित दीर्घ srmmu_nocache_end;

/* 1 bit <=> 256 bytes of nocache <=> 64 PTEs */
#घोषणा SRMMU_NOCACHE_BITMAP_SHIFT (PAGE_SHIFT - 4)

/* The context table is a nocache user with the biggest alignment needs. */
#घोषणा SRMMU_NOCACHE_ALIGN_MAX (माप(ctxd_t)*SRMMU_MAX_CONTEXTS)

व्योम *srmmu_nocache_pool;
अटल काष्ठा bit_map srmmu_nocache_map;

अटल अंतरभूत पूर्णांक srmmu_pmd_none(pmd_t pmd)
अणु वापस !(pmd_val(pmd) & 0xFFFFFFF); पूर्ण

/* XXX should we hyper_flush_whole_icache here - Anton */
अटल अंतरभूत व्योम srmmu_ctxd_set(ctxd_t *ctxp, pgd_t *pgdp)
अणु
	pte_t pte;

	pte = __pte((SRMMU_ET_PTD | (__nocache_pa(pgdp) >> 4)));
	set_pte((pte_t *)ctxp, pte);
पूर्ण

/*
 * Locations of MSI Registers.
 */
#घोषणा MSI_MBUS_ARBEN	0xe0001008	/* MBus Arbiter Enable रेजिस्टर */

/*
 * Useful bits in the MSI Registers.
 */
#घोषणा MSI_ASYNC_MODE  0x80000000	/* Operate the MSI asynchronously */

अटल व्योम msi_set_sync(व्योम)
अणु
	__यंत्र__ __अस्थिर__ ("lda [%0] %1, %%g3\n\t"
			      "andn %%g3, %2, %%g3\n\t"
			      "sta %%g3, [%0] %1\n\t" : :
			      "r" (MSI_MBUS_ARBEN),
			      "i" (ASI_M_CTL), "r" (MSI_ASYNC_MODE) : "g3");
पूर्ण

व्योम pmd_set(pmd_t *pmdp, pte_t *ptep)
अणु
	अचिन्हित दीर्घ ptp = __nocache_pa(ptep) >> 4;
	set_pte((pte_t *)&pmd_val(*pmdp), __pte(SRMMU_ET_PTD | ptp));
पूर्ण

/*
 * size: bytes to allocate in the nocache area.
 * align: bytes, number to align at.
 * Returns the भव address of the allocated area.
 */
अटल व्योम *__srmmu_get_nocache(पूर्णांक size, पूर्णांक align)
अणु
	पूर्णांक offset, minsz = 1 << SRMMU_NOCACHE_BITMAP_SHIFT;
	अचिन्हित दीर्घ addr;

	अगर (size < minsz) अणु
		prपूर्णांकk(KERN_ERR "Size 0x%x too small for nocache request\n",
		       size);
		size = minsz;
	पूर्ण
	अगर (size & (minsz - 1)) अणु
		prपूर्णांकk(KERN_ERR "Size 0x%x unaligned in nocache request\n",
		       size);
		size += minsz - 1;
	पूर्ण
	BUG_ON(align > SRMMU_NOCACHE_ALIGN_MAX);

	offset = bit_map_string_get(&srmmu_nocache_map,
				    size >> SRMMU_NOCACHE_BITMAP_SHIFT,
				    align >> SRMMU_NOCACHE_BITMAP_SHIFT);
	अगर (offset == -1) अणु
		prपूर्णांकk(KERN_ERR "srmmu: out of nocache %d: %d/%d\n",
		       size, (पूर्णांक) srmmu_nocache_size,
		       srmmu_nocache_map.used << SRMMU_NOCACHE_BITMAP_SHIFT);
		वापस शून्य;
	पूर्ण

	addr = SRMMU_NOCACHE_VADDR + (offset << SRMMU_NOCACHE_BITMAP_SHIFT);
	वापस (व्योम *)addr;
पूर्ण

व्योम *srmmu_get_nocache(पूर्णांक size, पूर्णांक align)
अणु
	व्योम *पंचांगp;

	पंचांगp = __srmmu_get_nocache(size, align);

	अगर (पंचांगp)
		स_रखो(पंचांगp, 0, size);

	वापस पंचांगp;
पूर्ण

व्योम srmmu_मुक्त_nocache(व्योम *addr, पूर्णांक size)
अणु
	अचिन्हित दीर्घ vaddr;
	पूर्णांक offset;

	vaddr = (अचिन्हित दीर्घ)addr;
	अगर (vaddr < SRMMU_NOCACHE_VADDR) अणु
		prपूर्णांकk("Vaddr %lx is smaller than nocache base 0x%lx\n",
		    vaddr, (अचिन्हित दीर्घ)SRMMU_NOCACHE_VADDR);
		BUG();
	पूर्ण
	अगर (vaddr + size > srmmu_nocache_end) अणु
		prपूर्णांकk("Vaddr %lx is bigger than nocache end 0x%lx\n",
		    vaddr, srmmu_nocache_end);
		BUG();
	पूर्ण
	अगर (!is_घातer_of_2(size)) अणु
		prपूर्णांकk("Size 0x%x is not a power of 2\n", size);
		BUG();
	पूर्ण
	अगर (size < SRMMU_NOCACHE_BITMAP_SHIFT) अणु
		prपूर्णांकk("Size 0x%x is too small\n", size);
		BUG();
	पूर्ण
	अगर (vaddr & (size - 1)) अणु
		prपूर्णांकk("Vaddr %lx is not aligned to size 0x%x\n", vaddr, size);
		BUG();
	पूर्ण

	offset = (vaddr - SRMMU_NOCACHE_VADDR) >> SRMMU_NOCACHE_BITMAP_SHIFT;
	size = size >> SRMMU_NOCACHE_BITMAP_SHIFT;

	bit_map_clear(&srmmu_nocache_map, offset, size);
पूर्ण

अटल व्योम srmmu_early_allocate_ptable_skeleton(अचिन्हित दीर्घ start,
						 अचिन्हित दीर्घ end);

/* Return how much physical memory we have.  */
अटल अचिन्हित दीर्घ __init probe_memory(व्योम)
अणु
	अचिन्हित दीर्घ total = 0;
	पूर्णांक i;

	क्रम (i = 0; sp_banks[i].num_bytes; i++)
		total += sp_banks[i].num_bytes;

	वापस total;
पूर्ण

/*
 * Reserve nocache dynamically proportionally to the amount of
 * प्रणाली RAM. -- Tomas Szepe <szepe@pinerecords.com>, June 2002
 */
अटल व्योम __init srmmu_nocache_calcsize(व्योम)
अणु
	अचिन्हित दीर्घ sysmemavail = probe_memory() / 1024;
	पूर्णांक srmmu_nocache_npages;

	srmmu_nocache_npages =
		sysmemavail / SRMMU_NOCACHE_ALCRATIO / 1024 * 256;

 /* P3 XXX The 4x overuse: corroborated by /proc/meminfo. */
	// अगर (srmmu_nocache_npages < 256) srmmu_nocache_npages = 256;
	अगर (srmmu_nocache_npages < SRMMU_MIN_NOCACHE_PAGES)
		srmmu_nocache_npages = SRMMU_MIN_NOCACHE_PAGES;

	/* anything above 1280 blows up */
	अगर (srmmu_nocache_npages > SRMMU_MAX_NOCACHE_PAGES)
		srmmu_nocache_npages = SRMMU_MAX_NOCACHE_PAGES;

	srmmu_nocache_size = srmmu_nocache_npages * PAGE_SIZE;
	srmmu_nocache_end = SRMMU_NOCACHE_VADDR + srmmu_nocache_size;
पूर्ण

अटल व्योम __init srmmu_nocache_init(व्योम)
अणु
	व्योम *srmmu_nocache_biपंचांगap;
	अचिन्हित पूर्णांक biपंचांगap_bits;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	अचिन्हित दीर्घ paddr, vaddr;
	अचिन्हित दीर्घ pteval;

	biपंचांगap_bits = srmmu_nocache_size >> SRMMU_NOCACHE_BITMAP_SHIFT;

	srmmu_nocache_pool = memblock_alloc(srmmu_nocache_size,
					    SRMMU_NOCACHE_ALIGN_MAX);
	अगर (!srmmu_nocache_pool)
		panic("%s: Failed to allocate %lu bytes align=0x%x\n",
		      __func__, srmmu_nocache_size, SRMMU_NOCACHE_ALIGN_MAX);
	स_रखो(srmmu_nocache_pool, 0, srmmu_nocache_size);

	srmmu_nocache_biपंचांगap =
		memblock_alloc(BITS_TO_LONGS(biपंचांगap_bits) * माप(दीर्घ),
			       SMP_CACHE_BYTES);
	अगर (!srmmu_nocache_biपंचांगap)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      BITS_TO_LONGS(biपंचांगap_bits) * माप(दीर्घ));
	bit_map_init(&srmmu_nocache_map, srmmu_nocache_biपंचांगap, biपंचांगap_bits);

	srmmu_swapper_pg_dir = __srmmu_get_nocache(SRMMU_PGD_TABLE_SIZE, SRMMU_PGD_TABLE_SIZE);
	स_रखो(__nocache_fix(srmmu_swapper_pg_dir), 0, SRMMU_PGD_TABLE_SIZE);
	init_mm.pgd = srmmu_swapper_pg_dir;

	srmmu_early_allocate_ptable_skeleton(SRMMU_NOCACHE_VADDR, srmmu_nocache_end);

	paddr = __pa((अचिन्हित दीर्घ)srmmu_nocache_pool);
	vaddr = SRMMU_NOCACHE_VADDR;

	जबतक (vaddr < srmmu_nocache_end) अणु
		pgd = pgd_offset_k(vaddr);
		p4d = p4d_offset(pgd, vaddr);
		pud = pud_offset(p4d, vaddr);
		pmd = pmd_offset(__nocache_fix(pud), vaddr);
		pte = pte_offset_kernel(__nocache_fix(pmd), vaddr);

		pteval = ((paddr >> 4) | SRMMU_ET_PTE | SRMMU_PRIV);

		अगर (srmmu_cache_pagetables)
			pteval |= SRMMU_CACHE;

		set_pte(__nocache_fix(pte), __pte(pteval));

		vaddr += PAGE_SIZE;
		paddr += PAGE_SIZE;
	पूर्ण

	flush_cache_all();
	flush_tlb_all();
पूर्ण

pgd_t *get_pgd_fast(व्योम)
अणु
	pgd_t *pgd = शून्य;

	pgd = __srmmu_get_nocache(SRMMU_PGD_TABLE_SIZE, SRMMU_PGD_TABLE_SIZE);
	अगर (pgd) अणु
		pgd_t *init = pgd_offset_k(0);
		स_रखो(pgd, 0, USER_PTRS_PER_PGD * माप(pgd_t));
		स_नकल(pgd + USER_PTRS_PER_PGD, init + USER_PTRS_PER_PGD,
						(PTRS_PER_PGD - USER_PTRS_PER_PGD) * माप(pgd_t));
	पूर्ण

	वापस pgd;
पूर्ण

/*
 * Hardware needs alignment to 256 only, but we align to whole page size
 * to reduce fragmentation problems due to the buddy principle.
 * XXX Provide actual fragmentation statistics in /proc.
 *
 * Alignments up to the page size are the same क्रम physical and भव
 * addresses of the nocache area.
 */
pgtable_t pte_alloc_one(काष्ठा mm_काष्ठा *mm)
अणु
	pte_t *ptep;
	काष्ठा page *page;

	अगर (!(ptep = pte_alloc_one_kernel(mm)))
		वापस शून्य;
	page = pfn_to_page(__nocache_pa((अचिन्हित दीर्घ)ptep) >> PAGE_SHIFT);
	spin_lock(&mm->page_table_lock);
	अगर (page_ref_inc_वापस(page) == 2 && !pgtable_pte_page_ctor(page)) अणु
		page_ref_dec(page);
		ptep = शून्य;
	पूर्ण
	spin_unlock(&mm->page_table_lock);

	वापस ptep;
पूर्ण

व्योम pte_मुक्त(काष्ठा mm_काष्ठा *mm, pgtable_t ptep)
अणु
	काष्ठा page *page;

	page = pfn_to_page(__nocache_pa((अचिन्हित दीर्घ)ptep) >> PAGE_SHIFT);
	spin_lock(&mm->page_table_lock);
	अगर (page_ref_dec_वापस(page) == 1)
		pgtable_pte_page_dtor(page);
	spin_unlock(&mm->page_table_lock);

	srmmu_मुक्त_nocache(ptep, SRMMU_PTE_TABLE_SIZE);
पूर्ण

/* context handling - a dynamically sized pool is used */
#घोषणा NO_CONTEXT	-1

काष्ठा ctx_list अणु
	काष्ठा ctx_list *next;
	काष्ठा ctx_list *prev;
	अचिन्हित पूर्णांक ctx_number;
	काष्ठा mm_काष्ठा *ctx_mm;
पूर्ण;

अटल काष्ठा ctx_list *ctx_list_pool;
अटल काष्ठा ctx_list ctx_मुक्त;
अटल काष्ठा ctx_list ctx_used;

/* At boot समय we determine the number of contexts */
अटल पूर्णांक num_contexts;

अटल अंतरभूत व्योम हटाओ_from_ctx_list(काष्ठा ctx_list *entry)
अणु
	entry->next->prev = entry->prev;
	entry->prev->next = entry->next;
पूर्ण

अटल अंतरभूत व्योम add_to_ctx_list(काष्ठा ctx_list *head, काष्ठा ctx_list *entry)
अणु
	entry->next = head;
	(entry->prev = head->prev)->next = entry;
	head->prev = entry;
पूर्ण
#घोषणा add_to_मुक्त_ctxlist(entry) add_to_ctx_list(&ctx_मुक्त, entry)
#घोषणा add_to_used_ctxlist(entry) add_to_ctx_list(&ctx_used, entry)


अटल अंतरभूत व्योम alloc_context(काष्ठा mm_काष्ठा *old_mm, काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा ctx_list *ctxp;

	ctxp = ctx_मुक्त.next;
	अगर (ctxp != &ctx_मुक्त) अणु
		हटाओ_from_ctx_list(ctxp);
		add_to_used_ctxlist(ctxp);
		mm->context = ctxp->ctx_number;
		ctxp->ctx_mm = mm;
		वापस;
	पूर्ण
	ctxp = ctx_used.next;
	अगर (ctxp->ctx_mm == old_mm)
		ctxp = ctxp->next;
	अगर (ctxp == &ctx_used)
		panic("out of mmu contexts");
	flush_cache_mm(ctxp->ctx_mm);
	flush_tlb_mm(ctxp->ctx_mm);
	हटाओ_from_ctx_list(ctxp);
	add_to_used_ctxlist(ctxp);
	ctxp->ctx_mm->context = NO_CONTEXT;
	ctxp->ctx_mm = mm;
	mm->context = ctxp->ctx_number;
पूर्ण

अटल अंतरभूत व्योम मुक्त_context(पूर्णांक context)
अणु
	काष्ठा ctx_list *ctx_old;

	ctx_old = ctx_list_pool + context;
	हटाओ_from_ctx_list(ctx_old);
	add_to_मुक्त_ctxlist(ctx_old);
पूर्ण

अटल व्योम __init sparc_context_init(पूर्णांक numctx)
अणु
	पूर्णांक ctx;
	अचिन्हित दीर्घ size;

	size = numctx * माप(काष्ठा ctx_list);
	ctx_list_pool = memblock_alloc(size, SMP_CACHE_BYTES);
	अगर (!ctx_list_pool)
		panic("%s: Failed to allocate %lu bytes\n", __func__, size);

	क्रम (ctx = 0; ctx < numctx; ctx++) अणु
		काष्ठा ctx_list *clist;

		clist = (ctx_list_pool + ctx);
		clist->ctx_number = ctx;
		clist->ctx_mm = शून्य;
	पूर्ण
	ctx_मुक्त.next = ctx_मुक्त.prev = &ctx_मुक्त;
	ctx_used.next = ctx_used.prev = &ctx_used;
	क्रम (ctx = 0; ctx < numctx; ctx++)
		add_to_मुक्त_ctxlist(ctx_list_pool + ctx);
पूर्ण

व्योम चयन_mm(काष्ठा mm_काष्ठा *old_mm, काष्ठा mm_काष्ठा *mm,
	       काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित दीर्घ flags;

	अगर (mm->context == NO_CONTEXT) अणु
		spin_lock_irqsave(&srmmu_context_spinlock, flags);
		alloc_context(old_mm, mm);
		spin_unlock_irqrestore(&srmmu_context_spinlock, flags);
		srmmu_ctxd_set(&srmmu_context_table[mm->context], mm->pgd);
	पूर्ण

	अगर (sparc_cpu_model == sparc_leon)
		leon_चयन_mm();

	अगर (is_hypersparc)
		hyper_flush_whole_icache();

	srmmu_set_context(mm->context);
पूर्ण

/* Low level IO area allocation on the SRMMU. */
अटल अंतरभूत व्योम srmmu_mapioaddr(अचिन्हित दीर्घ physaddr,
				   अचिन्हित दीर्घ virt_addr, पूर्णांक bus_type)
अणु
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;
	अचिन्हित दीर्घ पंचांगp;

	physaddr &= PAGE_MASK;
	pgdp = pgd_offset_k(virt_addr);
	p4dp = p4d_offset(pgdp, virt_addr);
	pudp = pud_offset(p4dp, virt_addr);
	pmdp = pmd_offset(pudp, virt_addr);
	ptep = pte_offset_kernel(pmdp, virt_addr);
	पंचांगp = (physaddr >> 4) | SRMMU_ET_PTE;

	/* I need to test whether this is consistent over all
	 * sun4m's.  The bus_type represents the upper 4 bits of
	 * 36-bit physical address on the I/O space lines...
	 */
	पंचांगp |= (bus_type << 28);
	पंचांगp |= SRMMU_PRIV;
	__flush_page_to_ram(virt_addr);
	set_pte(ptep, __pte(पंचांगp));
पूर्ण

व्योम srmmu_mapiorange(अचिन्हित पूर्णांक bus, अचिन्हित दीर्घ xpa,
		      अचिन्हित दीर्घ xva, अचिन्हित पूर्णांक len)
अणु
	जबतक (len != 0) अणु
		len -= PAGE_SIZE;
		srmmu_mapioaddr(xpa, xva, bus);
		xva += PAGE_SIZE;
		xpa += PAGE_SIZE;
	पूर्ण
	flush_tlb_all();
पूर्ण

अटल अंतरभूत व्योम srmmu_unmapioaddr(अचिन्हित दीर्घ virt_addr)
अणु
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;


	pgdp = pgd_offset_k(virt_addr);
	p4dp = p4d_offset(pgdp, virt_addr);
	pudp = pud_offset(p4dp, virt_addr);
	pmdp = pmd_offset(pudp, virt_addr);
	ptep = pte_offset_kernel(pmdp, virt_addr);

	/* No need to flush uncacheable page. */
	__pte_clear(ptep);
पूर्ण

व्योम srmmu_unmapiorange(अचिन्हित दीर्घ virt_addr, अचिन्हित पूर्णांक len)
अणु
	जबतक (len != 0) अणु
		len -= PAGE_SIZE;
		srmmu_unmapioaddr(virt_addr);
		virt_addr += PAGE_SIZE;
	पूर्ण
	flush_tlb_all();
पूर्ण

/* tsunami.S */
बाह्य व्योम tsunami_flush_cache_all(व्योम);
बाह्य व्योम tsunami_flush_cache_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम tsunami_flush_cache_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम tsunami_flush_cache_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page);
बाह्य व्योम tsunami_flush_page_to_ram(अचिन्हित दीर्घ page);
बाह्य व्योम tsunami_flush_page_क्रम_dma(अचिन्हित दीर्घ page);
बाह्य व्योम tsunami_flush_sig_insns(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ insn_addr);
बाह्य व्योम tsunami_flush_tlb_all(व्योम);
बाह्य व्योम tsunami_flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम tsunami_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम tsunami_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page);
बाह्य व्योम tsunami_setup_blockops(व्योम);

/* swअगरt.S */
बाह्य व्योम swअगरt_flush_cache_all(व्योम);
बाह्य व्योम swअगरt_flush_cache_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम swअगरt_flush_cache_range(काष्ठा vm_area_काष्ठा *vma,
				    अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम swअगरt_flush_cache_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page);
बाह्य व्योम swअगरt_flush_page_to_ram(अचिन्हित दीर्घ page);
बाह्य व्योम swअगरt_flush_page_क्रम_dma(अचिन्हित दीर्घ page);
बाह्य व्योम swअगरt_flush_sig_insns(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ insn_addr);
बाह्य व्योम swअगरt_flush_tlb_all(व्योम);
बाह्य व्योम swअगरt_flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम swअगरt_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
				  अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम swअगरt_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page);

#अगर 0  /* P3: deadwood to debug precise flushes on Swअगरt. */
व्योम swअगरt_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page)
अणु
	पूर्णांक cctx, ctx1;

	page &= PAGE_MASK;
	अगर ((ctx1 = vma->vm_mm->context) != -1) अणु
		cctx = srmmu_get_context();
/* Is context # ever dअगरferent from current context? P3 */
		अगर (cctx != ctx1) अणु
			prपूर्णांकk("flush ctx %02x curr %02x\n", ctx1, cctx);
			srmmu_set_context(ctx1);
			swअगरt_flush_page(page);
			__यंत्र__ __अस्थिर__("sta %%g0, [%0] %1\n\t" : :
					"r" (page), "i" (ASI_M_FLUSH_PROBE));
			srmmu_set_context(cctx);
		पूर्ण अन्यथा अणु
			 /* Rm. prot. bits from virt. c. */
			/* swअगरt_flush_cache_all(); */
			/* swअगरt_flush_cache_page(vma, page); */
			swअगरt_flush_page(page);

			__यंत्र__ __अस्थिर__("sta %%g0, [%0] %1\n\t" : :
				"r" (page), "i" (ASI_M_FLUSH_PROBE));
			/* same as above: srmmu_flush_tlb_page() */
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*
 * The following are all MBUS based SRMMU modules, and thereक्रमe could
 * be found in a multiprocessor configuration.  On the whole, these
 * chips seems to be much more touchy about DVMA and page tables
 * with respect to cache coherency.
 */

/* viking.S */
बाह्य व्योम viking_flush_cache_all(व्योम);
बाह्य व्योम viking_flush_cache_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम viking_flush_cache_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
				     अचिन्हित दीर्घ end);
बाह्य व्योम viking_flush_cache_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page);
बाह्य व्योम viking_flush_page_to_ram(अचिन्हित दीर्घ page);
बाह्य व्योम viking_flush_page_क्रम_dma(अचिन्हित दीर्घ page);
बाह्य व्योम viking_flush_sig_insns(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr);
बाह्य व्योम viking_flush_page(अचिन्हित दीर्घ page);
बाह्य व्योम viking_mxcc_flush_page(अचिन्हित दीर्घ page);
बाह्य व्योम viking_flush_tlb_all(व्योम);
बाह्य व्योम viking_flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम viking_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
				   अचिन्हित दीर्घ end);
बाह्य व्योम viking_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma,
				  अचिन्हित दीर्घ page);
बाह्य व्योम sun4dsmp_flush_tlb_all(व्योम);
बाह्य व्योम sun4dsmp_flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम sun4dsmp_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
				   अचिन्हित दीर्घ end);
बाह्य व्योम sun4dsmp_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma,
				  अचिन्हित दीर्घ page);

/* hypersparc.S */
बाह्य व्योम hypersparc_flush_cache_all(व्योम);
बाह्य व्योम hypersparc_flush_cache_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम hypersparc_flush_cache_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम hypersparc_flush_cache_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page);
बाह्य व्योम hypersparc_flush_page_to_ram(अचिन्हित दीर्घ page);
बाह्य व्योम hypersparc_flush_page_क्रम_dma(अचिन्हित दीर्घ page);
बाह्य व्योम hypersparc_flush_sig_insns(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ insn_addr);
बाह्य व्योम hypersparc_flush_tlb_all(व्योम);
बाह्य व्योम hypersparc_flush_tlb_mm(काष्ठा mm_काष्ठा *mm);
बाह्य व्योम hypersparc_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम hypersparc_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page);
बाह्य व्योम hypersparc_setup_blockops(व्योम);

/*
 * NOTE: All of this startup code assumes the low 16mb (approx.) of
 *       kernel mappings are करोne with one single contiguous chunk of
 *       ram.  On small ram machines (classics मुख्यly) we only get
 *       around 8mb mapped क्रम us.
 */

अटल व्योम __init early_pgtable_allocfail(अक्षर *type)
अणु
	prom_म_लिखो("inherit_prom_mappings: Cannot alloc kernel %s.\n", type);
	prom_halt();
पूर्ण

अटल व्योम __init srmmu_early_allocate_ptable_skeleton(अचिन्हित दीर्घ start,
							अचिन्हित दीर्घ end)
अणु
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;

	जबतक (start < end) अणु
		pgdp = pgd_offset_k(start);
		p4dp = p4d_offset(pgdp, start);
		pudp = pud_offset(p4dp, start);
		अगर (pud_none(*__nocache_fix(pudp))) अणु
			pmdp = __srmmu_get_nocache(
			    SRMMU_PMD_TABLE_SIZE, SRMMU_PMD_TABLE_SIZE);
			अगर (pmdp == शून्य)
				early_pgtable_allocfail("pmd");
			स_रखो(__nocache_fix(pmdp), 0, SRMMU_PMD_TABLE_SIZE);
			pud_set(__nocache_fix(pudp), pmdp);
		पूर्ण
		pmdp = pmd_offset(__nocache_fix(pudp), start);
		अगर (srmmu_pmd_none(*__nocache_fix(pmdp))) अणु
			ptep = __srmmu_get_nocache(PTE_SIZE, PTE_SIZE);
			अगर (ptep == शून्य)
				early_pgtable_allocfail("pte");
			स_रखो(__nocache_fix(ptep), 0, PTE_SIZE);
			pmd_set(__nocache_fix(pmdp), ptep);
		पूर्ण
		अगर (start > (0xffffffffUL - PMD_SIZE))
			अवरोध;
		start = (start + PMD_SIZE) & PMD_MASK;
	पूर्ण
पूर्ण

अटल व्योम __init srmmu_allocate_ptable_skeleton(अचिन्हित दीर्घ start,
						  अचिन्हित दीर्घ end)
अणु
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;

	जबतक (start < end) अणु
		pgdp = pgd_offset_k(start);
		p4dp = p4d_offset(pgdp, start);
		pudp = pud_offset(p4dp, start);
		अगर (pud_none(*pudp)) अणु
			pmdp = __srmmu_get_nocache(SRMMU_PMD_TABLE_SIZE, SRMMU_PMD_TABLE_SIZE);
			अगर (pmdp == शून्य)
				early_pgtable_allocfail("pmd");
			स_रखो(pmdp, 0, SRMMU_PMD_TABLE_SIZE);
			pud_set((pud_t *)pgdp, pmdp);
		पूर्ण
		pmdp = pmd_offset(pudp, start);
		अगर (srmmu_pmd_none(*pmdp)) अणु
			ptep = __srmmu_get_nocache(PTE_SIZE,
							     PTE_SIZE);
			अगर (ptep == शून्य)
				early_pgtable_allocfail("pte");
			स_रखो(ptep, 0, PTE_SIZE);
			pmd_set(pmdp, ptep);
		पूर्ण
		अगर (start > (0xffffffffUL - PMD_SIZE))
			अवरोध;
		start = (start + PMD_SIZE) & PMD_MASK;
	पूर्ण
पूर्ण

/* These flush types are not available on all chips... */
अटल अंतरभूत अचिन्हित दीर्घ srmmu_probe(अचिन्हित दीर्घ vaddr)
अणु
	अचिन्हित दीर्घ retval;

	अगर (sparc_cpu_model != sparc_leon) अणु

		vaddr &= PAGE_MASK;
		__यंत्र__ __अस्थिर__("lda [%1] %2, %0\n\t" :
				     "=r" (retval) :
				     "r" (vaddr | 0x400), "i" (ASI_M_FLUSH_PROBE));
	पूर्ण अन्यथा अणु
		retval = leon_swprobe(vaddr, शून्य);
	पूर्ण
	वापस retval;
पूर्ण

/*
 * This is much cleaner than poking around physical address space
 * looking at the prom's page table directly which is what most
 * other OS's करो.  Yuck... this is much better.
 */
अटल व्योम __init srmmu_inherit_prom_mappings(अचिन्हित दीर्घ start,
					       अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ probed;
	अचिन्हित दीर्घ addr;
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep;
	पूर्णांक what; /* 0 = normal-pte, 1 = pmd-level pte, 2 = pgd-level pte */

	जबतक (start <= end) अणु
		अगर (start == 0)
			अवरोध; /* probably wrap around */
		अगर (start == 0xfef00000)
			start = KADB_DEBUGGER_BEGVM;
		probed = srmmu_probe(start);
		अगर (!probed) अणु
			/* जारी probing until we find an entry */
			start += PAGE_SIZE;
			जारी;
		पूर्ण

		/* A red snapper, see what it really is. */
		what = 0;
		addr = start - PAGE_SIZE;

		अगर (!(start & ~(PMD_MASK))) अणु
			अगर (srmmu_probe(addr + PMD_SIZE) == probed)
				what = 1;
		पूर्ण

		अगर (!(start & ~(PGसूची_MASK))) अणु
			अगर (srmmu_probe(addr + PGसूची_SIZE) == probed)
				what = 2;
		पूर्ण

		pgdp = pgd_offset_k(start);
		p4dp = p4d_offset(pgdp, start);
		pudp = pud_offset(p4dp, start);
		अगर (what == 2) अणु
			*__nocache_fix(pgdp) = __pgd(probed);
			start += PGसूची_SIZE;
			जारी;
		पूर्ण
		अगर (pud_none(*__nocache_fix(pudp))) अणु
			pmdp = __srmmu_get_nocache(SRMMU_PMD_TABLE_SIZE,
						   SRMMU_PMD_TABLE_SIZE);
			अगर (pmdp == शून्य)
				early_pgtable_allocfail("pmd");
			स_रखो(__nocache_fix(pmdp), 0, SRMMU_PMD_TABLE_SIZE);
			pud_set(__nocache_fix(pudp), pmdp);
		पूर्ण
		pmdp = pmd_offset(__nocache_fix(pudp), start);
		अगर (what == 1) अणु
			*(pmd_t *)__nocache_fix(pmdp) = __pmd(probed);
			start += PMD_SIZE;
			जारी;
		पूर्ण
		अगर (srmmu_pmd_none(*__nocache_fix(pmdp))) अणु
			ptep = __srmmu_get_nocache(PTE_SIZE, PTE_SIZE);
			अगर (ptep == शून्य)
				early_pgtable_allocfail("pte");
			स_रखो(__nocache_fix(ptep), 0, PTE_SIZE);
			pmd_set(__nocache_fix(pmdp), ptep);
		पूर्ण
		ptep = pte_offset_kernel(__nocache_fix(pmdp), start);
		*__nocache_fix(ptep) = __pte(probed);
		start += PAGE_SIZE;
	पूर्ण
पूर्ण

#घोषणा KERNEL_PTE(page_shअगरted) ((page_shअगरted)|SRMMU_CACHE|SRMMU_PRIV|SRMMU_VALID)

/* Create a third-level SRMMU 16MB page mapping. */
अटल व्योम __init करो_large_mapping(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ phys_base)
अणु
	pgd_t *pgdp = pgd_offset_k(vaddr);
	अचिन्हित दीर्घ big_pte;

	big_pte = KERNEL_PTE(phys_base >> 4);
	*__nocache_fix(pgdp) = __pgd(big_pte);
पूर्ण

/* Map sp_bank entry SP_ENTRY, starting at भव address VBASE. */
अटल अचिन्हित दीर्घ __init map_spbank(अचिन्हित दीर्घ vbase, पूर्णांक sp_entry)
अणु
	अचिन्हित दीर्घ pstart = (sp_banks[sp_entry].base_addr & PGसूची_MASK);
	अचिन्हित दीर्घ vstart = (vbase & PGसूची_MASK);
	अचिन्हित दीर्घ vend = PGसूची_ALIGN(vbase + sp_banks[sp_entry].num_bytes);
	/* Map "low" memory only */
	स्थिर अचिन्हित दीर्घ min_vaddr = PAGE_OFFSET;
	स्थिर अचिन्हित दीर्घ max_vaddr = PAGE_OFFSET + SRMMU_MAXMEM;

	अगर (vstart < min_vaddr || vstart >= max_vaddr)
		वापस vstart;

	अगर (vend > max_vaddr || vend < min_vaddr)
		vend = max_vaddr;

	जबतक (vstart < vend) अणु
		करो_large_mapping(vstart, pstart);
		vstart += PGसूची_SIZE; pstart += PGसूची_SIZE;
	पूर्ण
	वापस vstart;
पूर्ण

अटल व्योम __init map_kernel(व्योम)
अणु
	पूर्णांक i;

	अगर (phys_base > 0) अणु
		करो_large_mapping(PAGE_OFFSET, phys_base);
	पूर्ण

	क्रम (i = 0; sp_banks[i].num_bytes != 0; i++) अणु
		map_spbank((अचिन्हित दीर्घ)__va(sp_banks[i].base_addr), i);
	पूर्ण
पूर्ण

व्योम (*poke_srmmu)(व्योम) = शून्य;

व्योम __init srmmu_paging_init(व्योम)
अणु
	पूर्णांक i;
	phandle cpunode;
	अक्षर node_str[128];
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	अचिन्हित दीर्घ pages_avail;

	init_mm.context = (अचिन्हित दीर्घ) NO_CONTEXT;
	sparc_iomap.start = SUN4M_IOBASE_VADDR;	/* 16MB of IOSPACE on all sun4m's. */

	अगर (sparc_cpu_model == sun4d)
		num_contexts = 65536; /* We know it is Viking */
	अन्यथा अणु
		/* Find the number of contexts on the srmmu. */
		cpunode = prom_अ_लोhild(prom_root_node);
		num_contexts = 0;
		जबतक (cpunode != 0) अणु
			prom_माला_लोtring(cpunode, "device_type", node_str, माप(node_str));
			अगर (!म_भेद(node_str, "cpu")) अणु
				num_contexts = prom_getपूर्णांकशेष(cpunode, "mmu-nctx", 0x8);
				अवरोध;
			पूर्ण
			cpunode = prom_माला_लोibling(cpunode);
		पूर्ण
	पूर्ण

	अगर (!num_contexts) अणु
		prom_म_लिखो("Something wrong, can't find cpu node in paging_init.\n");
		prom_halt();
	पूर्ण

	pages_avail = 0;
	last_valid_pfn = booपंचांगem_init(&pages_avail);

	srmmu_nocache_calcsize();
	srmmu_nocache_init();
	srmmu_inherit_prom_mappings(0xfe400000, (LINUX_OPPROM_ENDVM - PAGE_SIZE));
	map_kernel();

	/* ctx table has to be physically aligned to its size */
	srmmu_context_table = __srmmu_get_nocache(num_contexts * माप(ctxd_t), num_contexts * माप(ctxd_t));
	srmmu_ctx_table_phys = (ctxd_t *)__nocache_pa(srmmu_context_table);

	क्रम (i = 0; i < num_contexts; i++)
		srmmu_ctxd_set(__nocache_fix(&srmmu_context_table[i]), srmmu_swapper_pg_dir);

	flush_cache_all();
	srmmu_set_ctable_ptr((अचिन्हित दीर्घ)srmmu_ctx_table_phys);
#अगर_घोषित CONFIG_SMP
	/* Stop from hanging here... */
	local_ops->tlb_all();
#अन्यथा
	flush_tlb_all();
#पूर्ण_अगर
	poke_srmmu();

	srmmu_allocate_ptable_skeleton(sparc_iomap.start, IOBASE_END);
	srmmu_allocate_ptable_skeleton(DVMA_VADDR, DVMA_END);

	srmmu_allocate_ptable_skeleton(
		__fix_to_virt(__end_of_fixed_addresses - 1), FIXADDR_TOP);
	srmmu_allocate_ptable_skeleton(PKMAP_BASE, PKMAP_END);

	pgd = pgd_offset_k(PKMAP_BASE);
	p4d = p4d_offset(pgd, PKMAP_BASE);
	pud = pud_offset(p4d, PKMAP_BASE);
	pmd = pmd_offset(pud, PKMAP_BASE);
	pte = pte_offset_kernel(pmd, PKMAP_BASE);
	pkmap_page_table = pte;

	flush_cache_all();
	flush_tlb_all();

	sparc_context_init(num_contexts);

	अणु
		अचिन्हित दीर्घ max_zone_pfn[MAX_NR_ZONES] = अणु 0 पूर्ण;

		max_zone_pfn[ZONE_DMA] = max_low_pfn;
		max_zone_pfn[ZONE_NORMAL] = max_low_pfn;
		max_zone_pfn[ZONE_HIGHMEM] = highend_pfn;

		मुक्त_area_init(max_zone_pfn);
	पूर्ण
पूर्ण

व्योम mmu_info(काष्ठा seq_file *m)
अणु
	seq_म_लिखो(m,
		   "MMU type\t: %s\n"
		   "contexts\t: %d\n"
		   "nocache total\t: %ld\n"
		   "nocache used\t: %d\n",
		   srmmu_name,
		   num_contexts,
		   srmmu_nocache_size,
		   srmmu_nocache_map.used << SRMMU_NOCACHE_BITMAP_SHIFT);
पूर्ण

पूर्णांक init_new_context(काष्ठा task_काष्ठा *tsk, काष्ठा mm_काष्ठा *mm)
अणु
	mm->context = NO_CONTEXT;
	वापस 0;
पूर्ण

व्योम destroy_context(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ flags;

	अगर (mm->context != NO_CONTEXT) अणु
		flush_cache_mm(mm);
		srmmu_ctxd_set(&srmmu_context_table[mm->context], srmmu_swapper_pg_dir);
		flush_tlb_mm(mm);
		spin_lock_irqsave(&srmmu_context_spinlock, flags);
		मुक्त_context(mm->context);
		spin_unlock_irqrestore(&srmmu_context_spinlock, flags);
		mm->context = NO_CONTEXT;
	पूर्ण
पूर्ण

/* Init various srmmu chip types. */
अटल व्योम __init srmmu_is_bad(व्योम)
अणु
	prom_म_लिखो("Could not determine SRMMU chip type.\n");
	prom_halt();
पूर्ण

अटल व्योम __init init_vac_layout(व्योम)
अणु
	phandle nd;
	पूर्णांक cache_lines;
	अक्षर node_str[128];
#अगर_घोषित CONFIG_SMP
	पूर्णांक cpu = 0;
	अचिन्हित दीर्घ max_size = 0;
	अचिन्हित दीर्घ min_line_size = 0x10000000;
#पूर्ण_अगर

	nd = prom_अ_लोhild(prom_root_node);
	जबतक ((nd = prom_माला_लोibling(nd)) != 0) अणु
		prom_माला_लोtring(nd, "device_type", node_str, माप(node_str));
		अगर (!म_भेद(node_str, "cpu")) अणु
			vac_line_size = prom_getपूर्णांक(nd, "cache-line-size");
			अगर (vac_line_size == -1) अणु
				prom_म_लिखो("can't determine cache-line-size, halting.\n");
				prom_halt();
			पूर्ण
			cache_lines = prom_getपूर्णांक(nd, "cache-nlines");
			अगर (cache_lines == -1) अणु
				prom_म_लिखो("can't determine cache-nlines, halting.\n");
				prom_halt();
			पूर्ण

			vac_cache_size = cache_lines * vac_line_size;
#अगर_घोषित CONFIG_SMP
			अगर (vac_cache_size > max_size)
				max_size = vac_cache_size;
			अगर (vac_line_size < min_line_size)
				min_line_size = vac_line_size;
			//FIXME: cpus not contiguous!!
			cpu++;
			अगर (cpu >= nr_cpu_ids || !cpu_online(cpu))
				अवरोध;
#अन्यथा
			अवरोध;
#पूर्ण_अगर
		पूर्ण
	पूर्ण
	अगर (nd == 0) अणु
		prom_म_लिखो("No CPU nodes found, halting.\n");
		prom_halt();
	पूर्ण
#अगर_घोषित CONFIG_SMP
	vac_cache_size = max_size;
	vac_line_size = min_line_size;
#पूर्ण_अगर
	prपूर्णांकk("SRMMU: Using VAC size of %d bytes, line size %d bytes.\n",
	       (पूर्णांक)vac_cache_size, (पूर्णांक)vac_line_size);
पूर्ण

अटल व्योम poke_hypersparc(व्योम)
अणु
	अस्थिर अचिन्हित दीर्घ clear;
	अचिन्हित दीर्घ mreg = srmmu_get_mmureg();

	hyper_flush_unconditional_combined();

	mreg &= ~(HYPERSPARC_CWENABLE);
	mreg |= (HYPERSPARC_CENABLE | HYPERSPARC_WBENABLE);
	mreg |= (HYPERSPARC_CMODE);

	srmmu_set_mmureg(mreg);

#अगर 0 /* XXX I think this is bad news... -DaveM */
	hyper_clear_all_tags();
#पूर्ण_अगर

	put_ross_icr(HYPERSPARC_ICCR_FTD | HYPERSPARC_ICCR_ICE);
	hyper_flush_whole_icache();
	clear = srmmu_get_faddr();
	clear = srmmu_get_ख_स्थितिus();
पूर्ण

अटल स्थिर काष्ठा sparc32_cachetlb_ops hypersparc_ops = अणु
	.cache_all	= hypersparc_flush_cache_all,
	.cache_mm	= hypersparc_flush_cache_mm,
	.cache_page	= hypersparc_flush_cache_page,
	.cache_range	= hypersparc_flush_cache_range,
	.tlb_all	= hypersparc_flush_tlb_all,
	.tlb_mm		= hypersparc_flush_tlb_mm,
	.tlb_page	= hypersparc_flush_tlb_page,
	.tlb_range	= hypersparc_flush_tlb_range,
	.page_to_ram	= hypersparc_flush_page_to_ram,
	.sig_insns	= hypersparc_flush_sig_insns,
	.page_क्रम_dma	= hypersparc_flush_page_क्रम_dma,
पूर्ण;

अटल व्योम __init init_hypersparc(व्योम)
अणु
	srmmu_name = "ROSS HyperSparc";
	srmmu_modtype = HyperSparc;

	init_vac_layout();

	is_hypersparc = 1;
	sparc32_cachetlb_ops = &hypersparc_ops;

	poke_srmmu = poke_hypersparc;

	hypersparc_setup_blockops();
पूर्ण

अटल व्योम poke_swअगरt(व्योम)
अणु
	अचिन्हित दीर्घ mreg;

	/* Clear any crap from the cache or अन्यथा... */
	swअगरt_flush_cache_all();

	/* Enable I & D caches */
	mreg = srmmu_get_mmureg();
	mreg |= (SWIFT_IE | SWIFT_DE);
	/*
	 * The Swअगरt branch folding logic is completely broken.  At
	 * trap समय, अगर things are just right, अगर can mistakenly
	 * think that a trap is coming from kernel mode when in fact
	 * it is coming from user mode (it mis-executes the branch in
	 * the trap code).  So you see things like crashme completely
	 * hosing your machine which is completely unacceptable.  Turn
	 * this shit off... nice job Fujitsu.
	 */
	mreg &= ~(SWIFT_BF);
	srmmu_set_mmureg(mreg);
पूर्ण

अटल स्थिर काष्ठा sparc32_cachetlb_ops swअगरt_ops = अणु
	.cache_all	= swअगरt_flush_cache_all,
	.cache_mm	= swअगरt_flush_cache_mm,
	.cache_page	= swअगरt_flush_cache_page,
	.cache_range	= swअगरt_flush_cache_range,
	.tlb_all	= swअगरt_flush_tlb_all,
	.tlb_mm		= swअगरt_flush_tlb_mm,
	.tlb_page	= swअगरt_flush_tlb_page,
	.tlb_range	= swअगरt_flush_tlb_range,
	.page_to_ram	= swअगरt_flush_page_to_ram,
	.sig_insns	= swअगरt_flush_sig_insns,
	.page_क्रम_dma	= swअगरt_flush_page_क्रम_dma,
पूर्ण;

#घोषणा SWIFT_MASKID_ADDR  0x10003018
अटल व्योम __init init_swअगरt(व्योम)
अणु
	अचिन्हित दीर्घ swअगरt_rev;

	__यंत्र__ __अस्थिर__("lda [%1] %2, %0\n\t"
			     "srl %0, 0x18, %0\n\t" :
			     "=r" (swअगरt_rev) :
			     "r" (SWIFT_MASKID_ADDR), "i" (ASI_M_BYPASS));
	srmmu_name = "Fujitsu Swift";
	चयन (swअगरt_rev) अणु
	हाल 0x11:
	हाल 0x20:
	हाल 0x23:
	हाल 0x30:
		srmmu_modtype = Swअगरt_lots_o_bugs;
		hwbug_biपंचांगask |= (HWBUG_KERN_ACCBROKEN | HWBUG_KERN_CBITBROKEN);
		/*
		 * Gee george, I wonder why Sun is so hush hush about
		 * this hardware bug... really braindamage stuff going
		 * on here.  However I think we can find a way to aव्योम
		 * all of the workaround overhead under Linux.  Basically,
		 * any page fault can cause kernel pages to become user
		 * accessible (the mmu माला_लो confused and clears some of
		 * the ACC bits in kernel ptes).  Aha, sounds pretty
		 * horrible eh?  But रुको, after extensive testing it appears
		 * that अगर you use pgd_t level large kernel pte's (like the
		 * 4MB pages on the Pentium) the bug करोes not get tripped
		 * at all.  This aव्योमs almost all of the major overhead.
		 * Welcome to a world where your venकरोr tells you to,
		 * "apply this kernel patch" instead of "sorry क्रम the
		 * broken hardware, send it back and we'll give you
		 * properly functioning parts"
		 */
		अवरोध;
	हाल 0x25:
	हाल 0x31:
		srmmu_modtype = Swअगरt_bad_c;
		hwbug_biपंचांगask |= HWBUG_KERN_CBITBROKEN;
		/*
		 * You see Sun allude to this hardware bug but never
		 * admit things directly, they'll say things like,
		 * "the Swift chip cache problems" or similar.
		 */
		अवरोध;
	शेष:
		srmmu_modtype = Swअगरt_ok;
		अवरोध;
	पूर्ण

	sparc32_cachetlb_ops = &swअगरt_ops;
	flush_page_क्रम_dma_global = 0;

	/*
	 * Are you now convinced that the Swअगरt is one of the
	 * biggest VLSI पातions of all समय?  Bravo Fujitsu!
	 * Fujitsu, the !#?!%$'d up processor people.  I bet अगर
	 * you examined the microcode of the Swअगरt you'd find
	 * XXX's all over the place.
	 */
	poke_srmmu = poke_swअगरt;
पूर्ण

अटल व्योम turbosparc_flush_cache_all(व्योम)
अणु
	flush_user_winकरोws();
	turbosparc_idflash_clear();
पूर्ण

अटल व्योम turbosparc_flush_cache_mm(काष्ठा mm_काष्ठा *mm)
अणु
	FLUSH_BEGIN(mm)
	flush_user_winकरोws();
	turbosparc_idflash_clear();
	FLUSH_END
पूर्ण

अटल व्योम turbosparc_flush_cache_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	FLUSH_BEGIN(vma->vm_mm)
	flush_user_winकरोws();
	turbosparc_idflash_clear();
	FLUSH_END
पूर्ण

अटल व्योम turbosparc_flush_cache_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page)
अणु
	FLUSH_BEGIN(vma->vm_mm)
	flush_user_winकरोws();
	अगर (vma->vm_flags & VM_EXEC)
		turbosparc_flush_icache();
	turbosparc_flush_dcache();
	FLUSH_END
पूर्ण

/* TurboSparc is copy-back, अगर we turn it on, but this करोes not work. */
अटल व्योम turbosparc_flush_page_to_ram(अचिन्हित दीर्घ page)
अणु
#अगर_घोषित TURBOSPARC_WRITEBACK
	अस्थिर अचिन्हित दीर्घ clear;

	अगर (srmmu_probe(page))
		turbosparc_flush_page_cache(page);
	clear = srmmu_get_ख_स्थितिus();
#पूर्ण_अगर
पूर्ण

अटल व्योम turbosparc_flush_sig_insns(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ insn_addr)
अणु
पूर्ण

अटल व्योम turbosparc_flush_page_क्रम_dma(अचिन्हित दीर्घ page)
अणु
	turbosparc_flush_dcache();
पूर्ण

अटल व्योम turbosparc_flush_tlb_all(व्योम)
अणु
	srmmu_flush_whole_tlb();
पूर्ण

अटल व्योम turbosparc_flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	FLUSH_BEGIN(mm)
	srmmu_flush_whole_tlb();
	FLUSH_END
पूर्ण

अटल व्योम turbosparc_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	FLUSH_BEGIN(vma->vm_mm)
	srmmu_flush_whole_tlb();
	FLUSH_END
पूर्ण

अटल व्योम turbosparc_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page)
अणु
	FLUSH_BEGIN(vma->vm_mm)
	srmmu_flush_whole_tlb();
	FLUSH_END
पूर्ण


अटल व्योम poke_turbosparc(व्योम)
अणु
	अचिन्हित दीर्घ mreg = srmmu_get_mmureg();
	अचिन्हित दीर्घ ccreg;

	/* Clear any crap from the cache or अन्यथा... */
	turbosparc_flush_cache_all();
	/* Temporarily disable I & D caches */
	mreg &= ~(TURBOSPARC_ICENABLE | TURBOSPARC_DCENABLE);
	mreg &= ~(TURBOSPARC_PCENABLE);		/* Don't check parity */
	srmmu_set_mmureg(mreg);

	ccreg = turbosparc_get_ccreg();

#अगर_घोषित TURBOSPARC_WRITEBACK
	ccreg |= (TURBOSPARC_SNENABLE);		/* Do DVMA snooping in Dcache */
	ccreg &= ~(TURBOSPARC_uS2 | TURBOSPARC_WTENABLE);
			/* Write-back D-cache, emulate VLSI
			 * पातion number three, not number one */
#अन्यथा
	/* For now let's play safe, optimize later */
	ccreg |= (TURBOSPARC_SNENABLE | TURBOSPARC_WTENABLE);
			/* Do DVMA snooping in Dcache, Write-thru D-cache */
	ccreg &= ~(TURBOSPARC_uS2);
			/* Emulate VLSI पातion number three, not number one */
#पूर्ण_अगर

	चयन (ccreg & 7) अणु
	हाल 0: /* No SE cache */
	हाल 7: /* Test mode */
		अवरोध;
	शेष:
		ccreg |= (TURBOSPARC_SCENABLE);
	पूर्ण
	turbosparc_set_ccreg(ccreg);

	mreg |= (TURBOSPARC_ICENABLE | TURBOSPARC_DCENABLE); /* I & D caches on */
	mreg |= (TURBOSPARC_ICSNOOP);		/* Icache snooping on */
	srmmu_set_mmureg(mreg);
पूर्ण

अटल स्थिर काष्ठा sparc32_cachetlb_ops turbosparc_ops = अणु
	.cache_all	= turbosparc_flush_cache_all,
	.cache_mm	= turbosparc_flush_cache_mm,
	.cache_page	= turbosparc_flush_cache_page,
	.cache_range	= turbosparc_flush_cache_range,
	.tlb_all	= turbosparc_flush_tlb_all,
	.tlb_mm		= turbosparc_flush_tlb_mm,
	.tlb_page	= turbosparc_flush_tlb_page,
	.tlb_range	= turbosparc_flush_tlb_range,
	.page_to_ram	= turbosparc_flush_page_to_ram,
	.sig_insns	= turbosparc_flush_sig_insns,
	.page_क्रम_dma	= turbosparc_flush_page_क्रम_dma,
पूर्ण;

अटल व्योम __init init_turbosparc(व्योम)
अणु
	srmmu_name = "Fujitsu TurboSparc";
	srmmu_modtype = TurboSparc;
	sparc32_cachetlb_ops = &turbosparc_ops;
	poke_srmmu = poke_turbosparc;
पूर्ण

अटल व्योम poke_tsunami(व्योम)
अणु
	अचिन्हित दीर्घ mreg = srmmu_get_mmureg();

	tsunami_flush_icache();
	tsunami_flush_dcache();
	mreg &= ~TSUNAMI_ITD;
	mreg |= (TSUNAMI_IENAB | TSUNAMI_DENAB);
	srmmu_set_mmureg(mreg);
पूर्ण

अटल स्थिर काष्ठा sparc32_cachetlb_ops tsunami_ops = अणु
	.cache_all	= tsunami_flush_cache_all,
	.cache_mm	= tsunami_flush_cache_mm,
	.cache_page	= tsunami_flush_cache_page,
	.cache_range	= tsunami_flush_cache_range,
	.tlb_all	= tsunami_flush_tlb_all,
	.tlb_mm		= tsunami_flush_tlb_mm,
	.tlb_page	= tsunami_flush_tlb_page,
	.tlb_range	= tsunami_flush_tlb_range,
	.page_to_ram	= tsunami_flush_page_to_ram,
	.sig_insns	= tsunami_flush_sig_insns,
	.page_क्रम_dma	= tsunami_flush_page_क्रम_dma,
पूर्ण;

अटल व्योम __init init_tsunami(व्योम)
अणु
	/*
	 * Tsunami's pretty sane, Sun and TI actually got it
	 * somewhat right this समय.  Fujitsu should have
	 * taken some lessons from them.
	 */

	srmmu_name = "TI Tsunami";
	srmmu_modtype = Tsunami;
	sparc32_cachetlb_ops = &tsunami_ops;
	poke_srmmu = poke_tsunami;

	tsunami_setup_blockops();
पूर्ण

अटल व्योम poke_viking(व्योम)
अणु
	अचिन्हित दीर्घ mreg = srmmu_get_mmureg();
	अटल पूर्णांक smp_catch;

	अगर (viking_mxcc_present) अणु
		अचिन्हित दीर्घ mxcc_control = mxcc_get_creg();

		mxcc_control |= (MXCC_CTL_ECE | MXCC_CTL_PRE | MXCC_CTL_MCE);
		mxcc_control &= ~(MXCC_CTL_RRC);
		mxcc_set_creg(mxcc_control);

		/*
		 * We करोn't need memory parity checks.
		 * XXX This is a mess, have to dig out later. ecd.
		viking_mxcc_turn_off_parity(&mreg, &mxcc_control);
		 */

		/* We करो cache ptables on MXCC. */
		mreg |= VIKING_TCENABLE;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ bpreg;

		mreg &= ~(VIKING_TCENABLE);
		अगर (smp_catch++) अणु
			/* Must disable mixed-cmd mode here क्रम other cpu's. */
			bpreg = viking_get_bpreg();
			bpreg &= ~(VIKING_ACTION_MIX);
			viking_set_bpreg(bpreg);

			/* Just in हाल PROM करोes something funny. */
			msi_set_sync();
		पूर्ण
	पूर्ण

	mreg |= VIKING_SPENABLE;
	mreg |= (VIKING_ICENABLE | VIKING_DCENABLE);
	mreg |= VIKING_SBENABLE;
	mreg &= ~(VIKING_ACENABLE);
	srmmu_set_mmureg(mreg);
पूर्ण

अटल काष्ठा sparc32_cachetlb_ops viking_ops __ro_after_init = अणु
	.cache_all	= viking_flush_cache_all,
	.cache_mm	= viking_flush_cache_mm,
	.cache_page	= viking_flush_cache_page,
	.cache_range	= viking_flush_cache_range,
	.tlb_all	= viking_flush_tlb_all,
	.tlb_mm		= viking_flush_tlb_mm,
	.tlb_page	= viking_flush_tlb_page,
	.tlb_range	= viking_flush_tlb_range,
	.page_to_ram	= viking_flush_page_to_ram,
	.sig_insns	= viking_flush_sig_insns,
	.page_क्रम_dma	= viking_flush_page_क्रम_dma,
पूर्ण;

#अगर_घोषित CONFIG_SMP
/* On sun4d the cpu broadcasts local TLB flushes, so we can just
 * perक्रमm the local TLB flush and all the other cpus will see it.
 * But, unक्रमtunately, there is a bug in the sun4d XBUS backplane
 * that requires that we add some synchronization to these flushes.
 *
 * The bug is that the fअगरo which keeps track of all the pending TLB
 * broadcasts in the प्रणाली is an entry or two too small, so अगर we
 * have too many going at once we'll overflow that fअगरo and lose a TLB
 * flush resulting in corruption.
 *
 * Our workaround is to take a global spinlock around the TLB flushes,
 * which guarentees we won't ever have too many pending.  It's a big
 * hammer, but a semaphore like प्रणाली to make sure we only have N TLB
 * flushes going at once will require SMP locking anyways so there's
 * no real value in trying any harder than this.
 */
अटल काष्ठा sparc32_cachetlb_ops viking_sun4d_smp_ops __ro_after_init = अणु
	.cache_all	= viking_flush_cache_all,
	.cache_mm	= viking_flush_cache_mm,
	.cache_page	= viking_flush_cache_page,
	.cache_range	= viking_flush_cache_range,
	.tlb_all	= sun4dsmp_flush_tlb_all,
	.tlb_mm		= sun4dsmp_flush_tlb_mm,
	.tlb_page	= sun4dsmp_flush_tlb_page,
	.tlb_range	= sun4dsmp_flush_tlb_range,
	.page_to_ram	= viking_flush_page_to_ram,
	.sig_insns	= viking_flush_sig_insns,
	.page_क्रम_dma	= viking_flush_page_क्रम_dma,
पूर्ण;
#पूर्ण_अगर

अटल व्योम __init init_viking(व्योम)
अणु
	अचिन्हित दीर्घ mreg = srmmu_get_mmureg();

	/* Ahhh, the viking.  SRMMU VLSI पातion number two... */
	अगर (mreg & VIKING_MMODE) अणु
		srmmu_name = "TI Viking";
		viking_mxcc_present = 0;
		msi_set_sync();

		/*
		 * We need this to make sure old viking takes no hits
		 * on it's cache क्रम dma snoops to workaround the
		 * "load from non-cacheable memory" पूर्णांकerrupt bug.
		 * This is only necessary because of the new way in
		 * which we use the IOMMU.
		 */
		viking_ops.page_क्रम_dma = viking_flush_page;
#अगर_घोषित CONFIG_SMP
		viking_sun4d_smp_ops.page_क्रम_dma = viking_flush_page;
#पूर्ण_अगर
		flush_page_क्रम_dma_global = 0;
	पूर्ण अन्यथा अणु
		srmmu_name = "TI Viking/MXCC";
		viking_mxcc_present = 1;
		srmmu_cache_pagetables = 1;
	पूर्ण

	sparc32_cachetlb_ops = (स्थिर काष्ठा sparc32_cachetlb_ops *)
		&viking_ops;
#अगर_घोषित CONFIG_SMP
	अगर (sparc_cpu_model == sun4d)
		sparc32_cachetlb_ops = (स्थिर काष्ठा sparc32_cachetlb_ops *)
			&viking_sun4d_smp_ops;
#पूर्ण_अगर

	poke_srmmu = poke_viking;
पूर्ण

/* Probe क्रम the srmmu chip version. */
अटल व्योम __init get_srmmu_type(व्योम)
अणु
	अचिन्हित दीर्घ mreg, psr;
	अचिन्हित दीर्घ mod_typ, mod_rev, psr_typ, psr_vers;

	srmmu_modtype = SRMMU_INVAL_MOD;
	hwbug_biपंचांगask = 0;

	mreg = srmmu_get_mmureg(); psr = get_psr();
	mod_typ = (mreg & 0xf0000000) >> 28;
	mod_rev = (mreg & 0x0f000000) >> 24;
	psr_typ = (psr >> 28) & 0xf;
	psr_vers = (psr >> 24) & 0xf;

	/* First, check क्रम sparc-leon. */
	अगर (sparc_cpu_model == sparc_leon) अणु
		init_leon();
		वापस;
	पूर्ण

	/* Second, check क्रम HyperSparc or Cypress. */
	अगर (mod_typ == 1) अणु
		चयन (mod_rev) अणु
		हाल 7:
			/* UP or MP Hypersparc */
			init_hypersparc();
			अवरोध;
		हाल 0:
		हाल 2:
		हाल 10:
		हाल 11:
		हाल 12:
		हाल 13:
		हाल 14:
		हाल 15:
		शेष:
			prom_म_लिखो("Sparc-Linux Cypress support does not longer exit.\n");
			prom_halt();
			अवरोध;
		पूर्ण
		वापस;
	पूर्ण

	/* Now Fujitsu TurboSparc. It might happen that it is
	 * in Swअगरt emulation mode, so we will check later...
	 */
	अगर (psr_typ == 0 && psr_vers == 5) अणु
		init_turbosparc();
		वापस;
	पूर्ण

	/* Next check क्रम Fujitsu Swअगरt. */
	अगर (psr_typ == 0 && psr_vers == 4) अणु
		phandle cpunode;
		अक्षर node_str[128];

		/* Look अगर it is not a TurboSparc emulating Swअगरt... */
		cpunode = prom_अ_लोhild(prom_root_node);
		जबतक ((cpunode = prom_माला_लोibling(cpunode)) != 0) अणु
			prom_माला_लोtring(cpunode, "device_type", node_str, माप(node_str));
			अगर (!म_भेद(node_str, "cpu")) अणु
				अगर (!prom_getपूर्णांकशेष(cpunode, "psr-implementation", 1) &&
				    prom_getपूर्णांकशेष(cpunode, "psr-version", 1) == 5) अणु
					init_turbosparc();
					वापस;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण

		init_swअगरt();
		वापस;
	पूर्ण

	/* Now the Viking family of srmmu. */
	अगर (psr_typ == 4 &&
	   ((psr_vers == 0) ||
	    ((psr_vers == 1) && (mod_typ == 0) && (mod_rev == 0)))) अणु
		init_viking();
		वापस;
	पूर्ण

	/* Finally the Tsunami. */
	अगर (psr_typ == 4 && psr_vers == 1 && (mod_typ || mod_rev)) अणु
		init_tsunami();
		वापस;
	पूर्ण

	/* Oh well */
	srmmu_is_bad();
पूर्ण

#अगर_घोषित CONFIG_SMP
/* Local cross-calls. */
अटल व्योम smp_flush_page_क्रम_dma(अचिन्हित दीर्घ page)
अणु
	xc1((smpfunc_t) local_ops->page_क्रम_dma, page);
	local_ops->page_क्रम_dma(page);
पूर्ण

अटल व्योम smp_flush_cache_all(व्योम)
अणु
	xc0((smpfunc_t) local_ops->cache_all);
	local_ops->cache_all();
पूर्ण

अटल व्योम smp_flush_tlb_all(व्योम)
अणु
	xc0((smpfunc_t) local_ops->tlb_all);
	local_ops->tlb_all();
पूर्ण

अटल व्योम smp_flush_cache_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (mm->context != NO_CONTEXT) अणु
		cpumask_t cpu_mask;
		cpumask_copy(&cpu_mask, mm_cpumask(mm));
		cpumask_clear_cpu(smp_processor_id(), &cpu_mask);
		अगर (!cpumask_empty(&cpu_mask))
			xc1((smpfunc_t) local_ops->cache_mm, (अचिन्हित दीर्घ) mm);
		local_ops->cache_mm(mm);
	पूर्ण
पूर्ण

अटल व्योम smp_flush_tlb_mm(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (mm->context != NO_CONTEXT) अणु
		cpumask_t cpu_mask;
		cpumask_copy(&cpu_mask, mm_cpumask(mm));
		cpumask_clear_cpu(smp_processor_id(), &cpu_mask);
		अगर (!cpumask_empty(&cpu_mask)) अणु
			xc1((smpfunc_t) local_ops->tlb_mm, (अचिन्हित दीर्घ) mm);
			अगर (atomic_पढ़ो(&mm->mm_users) == 1 && current->active_mm == mm)
				cpumask_copy(mm_cpumask(mm),
					     cpumask_of(smp_processor_id()));
		पूर्ण
		local_ops->tlb_mm(mm);
	पूर्ण
पूर्ण

अटल व्योम smp_flush_cache_range(काष्ठा vm_area_काष्ठा *vma,
				  अचिन्हित दीर्घ start,
				  अचिन्हित दीर्घ end)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

	अगर (mm->context != NO_CONTEXT) अणु
		cpumask_t cpu_mask;
		cpumask_copy(&cpu_mask, mm_cpumask(mm));
		cpumask_clear_cpu(smp_processor_id(), &cpu_mask);
		अगर (!cpumask_empty(&cpu_mask))
			xc3((smpfunc_t) local_ops->cache_range,
			    (अचिन्हित दीर्घ) vma, start, end);
		local_ops->cache_range(vma, start, end);
	पूर्ण
पूर्ण

अटल व्योम smp_flush_tlb_range(काष्ठा vm_area_काष्ठा *vma,
				अचिन्हित दीर्घ start,
				अचिन्हित दीर्घ end)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

	अगर (mm->context != NO_CONTEXT) अणु
		cpumask_t cpu_mask;
		cpumask_copy(&cpu_mask, mm_cpumask(mm));
		cpumask_clear_cpu(smp_processor_id(), &cpu_mask);
		अगर (!cpumask_empty(&cpu_mask))
			xc3((smpfunc_t) local_ops->tlb_range,
			    (अचिन्हित दीर्घ) vma, start, end);
		local_ops->tlb_range(vma, start, end);
	पूर्ण
पूर्ण

अटल व्योम smp_flush_cache_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

	अगर (mm->context != NO_CONTEXT) अणु
		cpumask_t cpu_mask;
		cpumask_copy(&cpu_mask, mm_cpumask(mm));
		cpumask_clear_cpu(smp_processor_id(), &cpu_mask);
		अगर (!cpumask_empty(&cpu_mask))
			xc2((smpfunc_t) local_ops->cache_page,
			    (अचिन्हित दीर्घ) vma, page);
		local_ops->cache_page(vma, page);
	पूर्ण
पूर्ण

अटल व्योम smp_flush_tlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ page)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

	अगर (mm->context != NO_CONTEXT) अणु
		cpumask_t cpu_mask;
		cpumask_copy(&cpu_mask, mm_cpumask(mm));
		cpumask_clear_cpu(smp_processor_id(), &cpu_mask);
		अगर (!cpumask_empty(&cpu_mask))
			xc2((smpfunc_t) local_ops->tlb_page,
			    (अचिन्हित दीर्घ) vma, page);
		local_ops->tlb_page(vma, page);
	पूर्ण
पूर्ण

अटल व्योम smp_flush_page_to_ram(अचिन्हित दीर्घ page)
अणु
	/* Current theory is that those who call this are the one's
	 * who have just dirtied their cache with the pages contents
	 * in kernel space, thereक्रमe we only run this on local cpu.
	 *
	 * XXX This experiment failed, research further... -DaveM
	 */
#अगर 1
	xc1((smpfunc_t) local_ops->page_to_ram, page);
#पूर्ण_अगर
	local_ops->page_to_ram(page);
पूर्ण

अटल व्योम smp_flush_sig_insns(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ insn_addr)
अणु
	cpumask_t cpu_mask;
	cpumask_copy(&cpu_mask, mm_cpumask(mm));
	cpumask_clear_cpu(smp_processor_id(), &cpu_mask);
	अगर (!cpumask_empty(&cpu_mask))
		xc2((smpfunc_t) local_ops->sig_insns,
		    (अचिन्हित दीर्घ) mm, insn_addr);
	local_ops->sig_insns(mm, insn_addr);
पूर्ण

अटल काष्ठा sparc32_cachetlb_ops smp_cachetlb_ops __ro_after_init = अणु
	.cache_all	= smp_flush_cache_all,
	.cache_mm	= smp_flush_cache_mm,
	.cache_page	= smp_flush_cache_page,
	.cache_range	= smp_flush_cache_range,
	.tlb_all	= smp_flush_tlb_all,
	.tlb_mm		= smp_flush_tlb_mm,
	.tlb_page	= smp_flush_tlb_page,
	.tlb_range	= smp_flush_tlb_range,
	.page_to_ram	= smp_flush_page_to_ram,
	.sig_insns	= smp_flush_sig_insns,
	.page_क्रम_dma	= smp_flush_page_क्रम_dma,
पूर्ण;
#पूर्ण_अगर

/* Load up routines and स्थिरants क्रम sun4m and sun4d mmu */
व्योम __init load_mmu(व्योम)
अणु
	/* Functions */
	get_srmmu_type();

#अगर_घोषित CONFIG_SMP
	/* El चयनeroo... */
	local_ops = sparc32_cachetlb_ops;

	अगर (sparc_cpu_model == sun4d || sparc_cpu_model == sparc_leon) अणु
		smp_cachetlb_ops.tlb_all = local_ops->tlb_all;
		smp_cachetlb_ops.tlb_mm = local_ops->tlb_mm;
		smp_cachetlb_ops.tlb_range = local_ops->tlb_range;
		smp_cachetlb_ops.tlb_page = local_ops->tlb_page;
	पूर्ण

	अगर (poke_srmmu == poke_viking) अणु
		/* Aव्योम unnecessary cross calls. */
		smp_cachetlb_ops.cache_all = local_ops->cache_all;
		smp_cachetlb_ops.cache_mm = local_ops->cache_mm;
		smp_cachetlb_ops.cache_range = local_ops->cache_range;
		smp_cachetlb_ops.cache_page = local_ops->cache_page;

		smp_cachetlb_ops.page_to_ram = local_ops->page_to_ram;
		smp_cachetlb_ops.sig_insns = local_ops->sig_insns;
		smp_cachetlb_ops.page_क्रम_dma = local_ops->page_क्रम_dma;
	पूर्ण

	/* It really is स्थिर after this poपूर्णांक. */
	sparc32_cachetlb_ops = (स्थिर काष्ठा sparc32_cachetlb_ops *)
		&smp_cachetlb_ops;
#पूर्ण_अगर

	अगर (sparc_cpu_model != sun4d)
		ld_mmu_iommu();
#अगर_घोषित CONFIG_SMP
	अगर (sparc_cpu_model == sun4d)
		sun4d_init_smp();
	अन्यथा अगर (sparc_cpu_model == sparc_leon)
		leon_init_smp();
	अन्यथा
		sun4m_init_smp();
#पूर्ण_अगर
पूर्ण
