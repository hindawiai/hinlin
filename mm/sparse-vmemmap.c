<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Virtual Memory Map support
 *
 * (C) 2007 sgi. Christoph Lameter.
 *
 * Virtual memory maps allow VM primitives pfn_to_page, page_to_pfn,
 * virt_to_page, page_address() to be implemented as a base offset
 * calculation without memory access.
 *
 * However, भव mappings need a page table and TLBs. Many Linux
 * architectures alपढ़ोy map their physical space using 1-1 mappings
 * via TLBs. For those arches the भव memory map is essentially
 * क्रम मुक्त अगर we use the same page size as the 1-1 mappings. In that
 * हाल the overhead consists of a few additional pages that are
 * allocated to create a view of memory क्रम vmemmap.
 *
 * The architecture is expected to provide a vmemmap_populate() function
 * to instantiate the mapping.
 */
#समावेश <linux/mm.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/memblock.h>
#समावेश <linux/memremap.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sched.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/pgभाग.स>

/*
 * Allocate a block of memory to be used to back the भव memory map
 * or to back the page tables that are used to create the mapping.
 * Uses the मुख्य allocators अगर they are available, अन्यथा booपंचांगem.
 */

अटल व्योम * __ref __earlyonly_booपंचांगem_alloc(पूर्णांक node,
				अचिन्हित दीर्घ size,
				अचिन्हित दीर्घ align,
				अचिन्हित दीर्घ goal)
अणु
	वापस memblock_alloc_try_nid_raw(size, align, goal,
					       MEMBLOCK_ALLOC_ACCESSIBLE, node);
पूर्ण

व्योम * __meminit vmemmap_alloc_block(अचिन्हित दीर्घ size, पूर्णांक node)
अणु
	/* If the मुख्य allocator is up use that, fallback to booपंचांगem. */
	अगर (slab_is_available()) अणु
		gfp_t gfp_mask = GFP_KERNEL|__GFP_RETRY_MAYFAIL|__GFP_NOWARN;
		पूर्णांक order = get_order(size);
		अटल bool warned;
		काष्ठा page *page;

		page = alloc_pages_node(node, gfp_mask, order);
		अगर (page)
			वापस page_address(page);

		अगर (!warned) अणु
			warn_alloc(gfp_mask & ~__GFP_NOWARN, शून्य,
				   "vmemmap alloc failure: order:%u", order);
			warned = true;
		पूर्ण
		वापस शून्य;
	पूर्ण अन्यथा
		वापस __earlyonly_booपंचांगem_alloc(node, size, size,
				__pa(MAX_DMA_ADDRESS));
पूर्ण

अटल व्योम * __meminit alपंचांगap_alloc_block_buf(अचिन्हित दीर्घ size,
					       काष्ठा vmem_alपंचांगap *alपंचांगap);

/* need to make sure size is all the same during early stage */
व्योम * __meminit vmemmap_alloc_block_buf(अचिन्हित दीर्घ size, पूर्णांक node,
					 काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	व्योम *ptr;

	अगर (alपंचांगap)
		वापस alपंचांगap_alloc_block_buf(size, alपंचांगap);

	ptr = sparse_buffer_alloc(size);
	अगर (!ptr)
		ptr = vmemmap_alloc_block(size, node);
	वापस ptr;
पूर्ण

अटल अचिन्हित दीर्घ __meminit vmem_alपंचांगap_next_pfn(काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	वापस alपंचांगap->base_pfn + alपंचांगap->reserve + alपंचांगap->alloc
		+ alपंचांगap->align;
पूर्ण

अटल अचिन्हित दीर्घ __meminit vmem_alपंचांगap_nr_मुक्त(काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ allocated = alपंचांगap->alloc + alपंचांगap->align;

	अगर (alपंचांगap->मुक्त > allocated)
		वापस alपंचांगap->मुक्त - allocated;
	वापस 0;
पूर्ण

अटल व्योम * __meminit alपंचांगap_alloc_block_buf(अचिन्हित दीर्घ size,
					       काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ pfn, nr_pfns, nr_align;

	अगर (size & ~PAGE_MASK) अणु
		pr_warn_once("%s: allocations must be multiple of PAGE_SIZE (%ld)\n",
				__func__, size);
		वापस शून्य;
	पूर्ण

	pfn = vmem_alपंचांगap_next_pfn(alपंचांगap);
	nr_pfns = size >> PAGE_SHIFT;
	nr_align = 1UL << find_first_bit(&nr_pfns, BITS_PER_LONG);
	nr_align = ALIGN(pfn, nr_align) - pfn;
	अगर (nr_pfns + nr_align > vmem_alपंचांगap_nr_मुक्त(alपंचांगap))
		वापस शून्य;

	alपंचांगap->alloc += nr_pfns;
	alपंचांगap->align += nr_align;
	pfn += nr_align;

	pr_debug("%s: pfn: %#lx alloc: %ld align: %ld nr: %#lx\n",
			__func__, pfn, alपंचांगap->alloc, alपंचांगap->align, nr_pfns);
	वापस __va(__pfn_to_phys(pfn));
पूर्ण

व्योम __meminit vmemmap_verअगरy(pte_t *pte, पूर्णांक node,
				अचिन्हित दीर्घ start, अचिन्हित दीर्घ end)
अणु
	अचिन्हित दीर्घ pfn = pte_pfn(*pte);
	पूर्णांक actual_node = early_pfn_to_nid(pfn);

	अगर (node_distance(actual_node, node) > LOCAL_DISTANCE)
		pr_warn("[%lx-%lx] potential offnode page_structs\n",
			start, end - 1);
पूर्ण

pte_t * __meminit vmemmap_pte_populate(pmd_t *pmd, अचिन्हित दीर्घ addr, पूर्णांक node,
				       काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	pte_t *pte = pte_offset_kernel(pmd, addr);
	अगर (pte_none(*pte)) अणु
		pte_t entry;
		व्योम *p;

		p = vmemmap_alloc_block_buf(PAGE_SIZE, node, alपंचांगap);
		अगर (!p)
			वापस शून्य;
		entry = pfn_pte(__pa(p) >> PAGE_SHIFT, PAGE_KERNEL);
		set_pte_at(&init_mm, addr, pte, entry);
	पूर्ण
	वापस pte;
पूर्ण

अटल व्योम * __meminit vmemmap_alloc_block_zero(अचिन्हित दीर्घ size, पूर्णांक node)
अणु
	व्योम *p = vmemmap_alloc_block(size, node);

	अगर (!p)
		वापस शून्य;
	स_रखो(p, 0, size);

	वापस p;
पूर्ण

pmd_t * __meminit vmemmap_pmd_populate(pud_t *pud, अचिन्हित दीर्घ addr, पूर्णांक node)
अणु
	pmd_t *pmd = pmd_offset(pud, addr);
	अगर (pmd_none(*pmd)) अणु
		व्योम *p = vmemmap_alloc_block_zero(PAGE_SIZE, node);
		अगर (!p)
			वापस शून्य;
		pmd_populate_kernel(&init_mm, pmd, p);
	पूर्ण
	वापस pmd;
पूर्ण

pud_t * __meminit vmemmap_pud_populate(p4d_t *p4d, अचिन्हित दीर्घ addr, पूर्णांक node)
अणु
	pud_t *pud = pud_offset(p4d, addr);
	अगर (pud_none(*pud)) अणु
		व्योम *p = vmemmap_alloc_block_zero(PAGE_SIZE, node);
		अगर (!p)
			वापस शून्य;
		pud_populate(&init_mm, pud, p);
	पूर्ण
	वापस pud;
पूर्ण

p4d_t * __meminit vmemmap_p4d_populate(pgd_t *pgd, अचिन्हित दीर्घ addr, पूर्णांक node)
अणु
	p4d_t *p4d = p4d_offset(pgd, addr);
	अगर (p4d_none(*p4d)) अणु
		व्योम *p = vmemmap_alloc_block_zero(PAGE_SIZE, node);
		अगर (!p)
			वापस शून्य;
		p4d_populate(&init_mm, p4d, p);
	पूर्ण
	वापस p4d;
पूर्ण

pgd_t * __meminit vmemmap_pgd_populate(अचिन्हित दीर्घ addr, पूर्णांक node)
अणु
	pgd_t *pgd = pgd_offset_k(addr);
	अगर (pgd_none(*pgd)) अणु
		व्योम *p = vmemmap_alloc_block_zero(PAGE_SIZE, node);
		अगर (!p)
			वापस शून्य;
		pgd_populate(&init_mm, pgd, p);
	पूर्ण
	वापस pgd;
पूर्ण

पूर्णांक __meminit vmemmap_populate_basepages(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
					 पूर्णांक node, काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ addr = start;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	क्रम (; addr < end; addr += PAGE_SIZE) अणु
		pgd = vmemmap_pgd_populate(addr, node);
		अगर (!pgd)
			वापस -ENOMEM;
		p4d = vmemmap_p4d_populate(pgd, addr, node);
		अगर (!p4d)
			वापस -ENOMEM;
		pud = vmemmap_pud_populate(p4d, addr, node);
		अगर (!pud)
			वापस -ENOMEM;
		pmd = vmemmap_pmd_populate(pud, addr, node);
		अगर (!pmd)
			वापस -ENOMEM;
		pte = vmemmap_pte_populate(pmd, addr, node, alपंचांगap);
		अगर (!pte)
			वापस -ENOMEM;
		vmemmap_verअगरy(pte, node, addr, addr + PAGE_SIZE);
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा page * __meminit __populate_section_memmap(अचिन्हित दीर्घ pfn,
		अचिन्हित दीर्घ nr_pages, पूर्णांक nid, काष्ठा vmem_alपंचांगap *alपंचांगap)
अणु
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ) pfn_to_page(pfn);
	अचिन्हित दीर्घ end = start + nr_pages * माप(काष्ठा page);

	अगर (WARN_ON_ONCE(!IS_ALIGNED(pfn, PAGES_PER_SUBSECTION) ||
		!IS_ALIGNED(nr_pages, PAGES_PER_SUBSECTION)))
		वापस शून्य;

	अगर (vmemmap_populate(start, end, nid, alपंचांगap))
		वापस शून्य;

	वापस pfn_to_page(pfn);
पूर्ण
