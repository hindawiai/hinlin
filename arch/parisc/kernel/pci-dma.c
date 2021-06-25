<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
** PARISC 1.1 Dynamic DMA mapping support.
** This implementation is क्रम PA-RISC platक्रमms that करो not support
** I/O TLBs (aka DMA address translation hardware).
** See Documentation/core-api/dma-api-howto.rst क्रम पूर्णांकerface definitions.
**
**      (c) Copyright 1999,2000 Hewlett-Packard Company
**      (c) Copyright 2000 Grant Grundler
**	(c) Copyright 2000 Philipp Rumpf <prumpf@tux.org>
**      (c) Copyright 2000 John Marvin
**
** "leveraged" from 2.3.47: arch/ia64/kernel/pci-dma.c.
** (I assume it's from David Mosberger-Tang but there was no Copyright)
**
** AFAIK, all PA7100LC and PA7300LC platक्रमms can use this code.
**
** - ggg
*/

#समावेश <linux/init.h>
#समावेश <linux/gfp.h>
#समावेश <linux/mm.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/dma-direct.h>
#समावेश <linux/dma-map-ops.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/dma.h>    /* क्रम DMA_CHUNK_SIZE */
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/page.h>	/* get_order */
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/tlbflush.h>	/* क्रम purge_tlb_*() macros */

अटल काष्ठा proc_dir_entry * proc_gsc_root __पढ़ो_mostly = शून्य;
अटल अचिन्हित दीर्घ pcxl_used_bytes __पढ़ो_mostly = 0;
अटल अचिन्हित दीर्घ pcxl_used_pages __पढ़ो_mostly = 0;

बाह्य अचिन्हित दीर्घ pcxl_dma_start; /* Start of pcxl dma mapping area */
अटल DEFINE_SPINLOCK(pcxl_res_lock);
अटल अक्षर    *pcxl_res_map;
अटल पूर्णांक     pcxl_res_hपूर्णांक;
अटल पूर्णांक     pcxl_res_size;

#अगर_घोषित DEBUG_PCXL_RESOURCE
#घोषणा DBG_RES(x...)	prपूर्णांकk(x)
#अन्यथा
#घोषणा DBG_RES(x...)
#पूर्ण_अगर


/*
** Dump a hex representation of the resource map.
*/

#अगर_घोषित DUMP_RESMAP
अटल
व्योम dump_resmap(व्योम)
अणु
	u_दीर्घ *res_ptr = (अचिन्हित दीर्घ *)pcxl_res_map;
	u_दीर्घ i = 0;

	prपूर्णांकk("res_map: ");
	क्रम(; i < (pcxl_res_size / माप(अचिन्हित दीर्घ)); ++i, ++res_ptr)
		prपूर्णांकk("%08lx ", *res_ptr);

	prपूर्णांकk("\n");
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम dump_resmap(व्योम) अणु;पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक map_pte_uncached(pte_t * pte,
		अचिन्हित दीर्घ vaddr,
		अचिन्हित दीर्घ size, अचिन्हित दीर्घ *paddr_ptr)
अणु
	अचिन्हित दीर्घ end;
	अचिन्हित दीर्घ orig_vaddr = vaddr;

	vaddr &= ~PMD_MASK;
	end = vaddr + size;
	अगर (end > PMD_SIZE)
		end = PMD_SIZE;
	करो अणु
		अचिन्हित दीर्घ flags;

		अगर (!pte_none(*pte))
			prपूर्णांकk(KERN_ERR "map_pte_uncached: page already exists\n");
		purge_tlb_start(flags);
		set_pte(pte, __mk_pte(*paddr_ptr, PAGE_KERNEL_UNC));
		pdtlb_kernel(orig_vaddr);
		purge_tlb_end(flags);
		vaddr += PAGE_SIZE;
		orig_vaddr += PAGE_SIZE;
		(*paddr_ptr) += PAGE_SIZE;
		pte++;
	पूर्ण जबतक (vaddr < end);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक map_pmd_uncached(pmd_t * pmd, अचिन्हित दीर्घ vaddr,
		अचिन्हित दीर्घ size, अचिन्हित दीर्घ *paddr_ptr)
अणु
	अचिन्हित दीर्घ end;
	अचिन्हित दीर्घ orig_vaddr = vaddr;

	vaddr &= ~PGसूची_MASK;
	end = vaddr + size;
	अगर (end > PGसूची_SIZE)
		end = PGसूची_SIZE;
	करो अणु
		pte_t * pte = pte_alloc_kernel(pmd, vaddr);
		अगर (!pte)
			वापस -ENOMEM;
		अगर (map_pte_uncached(pte, orig_vaddr, end - vaddr, paddr_ptr))
			वापस -ENOMEM;
		vaddr = (vaddr + PMD_SIZE) & PMD_MASK;
		orig_vaddr += PMD_SIZE;
		pmd++;
	पूर्ण जबतक (vaddr < end);
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक map_uncached_pages(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ paddr)
अणु
	pgd_t * dir;
	अचिन्हित दीर्घ end = vaddr + size;

	dir = pgd_offset_k(vaddr);
	करो अणु
		p4d_t *p4d;
		pud_t *pud;
		pmd_t *pmd;

		p4d = p4d_offset(dir, vaddr);
		pud = pud_offset(p4d, vaddr);
		pmd = pmd_alloc(शून्य, pud, vaddr);

		अगर (!pmd)
			वापस -ENOMEM;
		अगर (map_pmd_uncached(pmd, vaddr, end - vaddr, &paddr))
			वापस -ENOMEM;
		vaddr = vaddr + PGसूची_SIZE;
		dir++;
	पूर्ण जबतक (vaddr && (vaddr < end));
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम unmap_uncached_pte(pmd_t * pmd, अचिन्हित दीर्घ vaddr,
		अचिन्हित दीर्घ size)
अणु
	pte_t * pte;
	अचिन्हित दीर्घ end;
	अचिन्हित दीर्घ orig_vaddr = vaddr;

	अगर (pmd_none(*pmd))
		वापस;
	अगर (pmd_bad(*pmd)) अणु
		pmd_ERROR(*pmd);
		pmd_clear(pmd);
		वापस;
	पूर्ण
	pte = pte_offset_map(pmd, vaddr);
	vaddr &= ~PMD_MASK;
	end = vaddr + size;
	अगर (end > PMD_SIZE)
		end = PMD_SIZE;
	करो अणु
		अचिन्हित दीर्घ flags;
		pte_t page = *pte;

		pte_clear(&init_mm, vaddr, pte);
		purge_tlb_start(flags);
		pdtlb_kernel(orig_vaddr);
		purge_tlb_end(flags);
		vaddr += PAGE_SIZE;
		orig_vaddr += PAGE_SIZE;
		pte++;
		अगर (pte_none(page) || pte_present(page))
			जारी;
		prपूर्णांकk(KERN_CRIT "Whee.. Swapped out page in kernel page table\n");
	पूर्ण जबतक (vaddr < end);
पूर्ण

अटल अंतरभूत व्योम unmap_uncached_pmd(pgd_t * dir, अचिन्हित दीर्घ vaddr,
		अचिन्हित दीर्घ size)
अणु
	pmd_t * pmd;
	अचिन्हित दीर्घ end;
	अचिन्हित दीर्घ orig_vaddr = vaddr;

	अगर (pgd_none(*dir))
		वापस;
	अगर (pgd_bad(*dir)) अणु
		pgd_ERROR(*dir);
		pgd_clear(dir);
		वापस;
	पूर्ण
	pmd = pmd_offset(pud_offset(p4d_offset(dir, vaddr), vaddr), vaddr);
	vaddr &= ~PGसूची_MASK;
	end = vaddr + size;
	अगर (end > PGसूची_SIZE)
		end = PGसूची_SIZE;
	करो अणु
		unmap_uncached_pte(pmd, orig_vaddr, end - vaddr);
		vaddr = (vaddr + PMD_SIZE) & PMD_MASK;
		orig_vaddr += PMD_SIZE;
		pmd++;
	पूर्ण जबतक (vaddr < end);
पूर्ण

अटल व्योम unmap_uncached_pages(अचिन्हित दीर्घ vaddr, अचिन्हित दीर्घ size)
अणु
	pgd_t * dir;
	अचिन्हित दीर्घ end = vaddr + size;

	dir = pgd_offset_k(vaddr);
	करो अणु
		unmap_uncached_pmd(dir, vaddr, end - vaddr);
		vaddr = vaddr + PGसूची_SIZE;
		dir++;
	पूर्ण जबतक (vaddr && (vaddr < end));
पूर्ण

#घोषणा PCXL_SEARCH_LOOP(idx, mask, size)  \
       क्रम(; res_ptr < res_end; ++res_ptr) \
       अणु \
               अगर(0 == ((*res_ptr) & mask)) अणु \
                       *res_ptr |= mask; \
		       idx = (पूर्णांक)((u_दीर्घ)res_ptr - (u_दीर्घ)pcxl_res_map); \
		       pcxl_res_hपूर्णांक = idx + (size >> 3); \
                       जाओ resource_found; \
               पूर्ण \
       पूर्ण

#घोषणा PCXL_FIND_FREE_MAPPING(idx, mask, size)  अणु \
       u##size *res_ptr = (u##size *)&(pcxl_res_map[pcxl_res_hपूर्णांक & ~((size >> 3) - 1)]); \
       u##size *res_end = (u##size *)&pcxl_res_map[pcxl_res_size]; \
       PCXL_SEARCH_LOOP(idx, mask, size); \
       res_ptr = (u##size *)&pcxl_res_map[0]; \
       PCXL_SEARCH_LOOP(idx, mask, size); \
पूर्ण

अचिन्हित दीर्घ
pcxl_alloc_range(माप_प्रकार size)
अणु
	पूर्णांक res_idx;
	u_दीर्घ mask, flags;
	अचिन्हित पूर्णांक pages_needed = size >> PAGE_SHIFT;

	mask = (u_दीर्घ) -1L;
 	mask >>= BITS_PER_LONG - pages_needed;

	DBG_RES("pcxl_alloc_range() size: %d pages_needed %d pages_mask 0x%08lx\n", 
		size, pages_needed, mask);

	spin_lock_irqsave(&pcxl_res_lock, flags);

	अगर(pages_needed <= 8) अणु
		PCXL_FIND_FREE_MAPPING(res_idx, mask, 8);
	पूर्ण अन्यथा अगर(pages_needed <= 16) अणु
		PCXL_FIND_FREE_MAPPING(res_idx, mask, 16);
	पूर्ण अन्यथा अगर(pages_needed <= 32) अणु
		PCXL_FIND_FREE_MAPPING(res_idx, mask, 32);
	पूर्ण अन्यथा अणु
		panic("%s: pcxl_alloc_range() Too many pages to map.\n",
		      __खाता__);
	पूर्ण

	dump_resmap();
	panic("%s: pcxl_alloc_range() out of dma mapping resources\n",
	      __खाता__);
	
resource_found:
	
	DBG_RES("pcxl_alloc_range() res_idx %d mask 0x%08lx res_hint: %d\n",
		res_idx, mask, pcxl_res_hपूर्णांक);

	pcxl_used_pages += pages_needed;
	pcxl_used_bytes += ((pages_needed >> 3) ? (pages_needed >> 3) : 1);

	spin_unlock_irqrestore(&pcxl_res_lock, flags);

	dump_resmap();

	/* 
	** वापस the corresponding vaddr in the pcxl dma map
	*/
	वापस (pcxl_dma_start + (res_idx << (PAGE_SHIFT + 3)));
पूर्ण

#घोषणा PCXL_FREE_MAPPINGS(idx, m, size) \
		u##size *res_ptr = (u##size *)&(pcxl_res_map[(idx) + (((size >> 3) - 1) & (~((size >> 3) - 1)))]); \
		/* BUG_ON((*res_ptr & m) != m); */ \
		*res_ptr &= ~m;

/*
** clear bits in the pcxl resource map
*/
अटल व्योम
pcxl_मुक्त_range(अचिन्हित दीर्घ vaddr, माप_प्रकार size)
अणु
	u_दीर्घ mask, flags;
	अचिन्हित पूर्णांक res_idx = (vaddr - pcxl_dma_start) >> (PAGE_SHIFT + 3);
	अचिन्हित पूर्णांक pages_mapped = size >> PAGE_SHIFT;

	mask = (u_दीर्घ) -1L;
 	mask >>= BITS_PER_LONG - pages_mapped;

	DBG_RES("pcxl_free_range() res_idx: %d size: %d pages_mapped %d mask 0x%08lx\n", 
		res_idx, size, pages_mapped, mask);

	spin_lock_irqsave(&pcxl_res_lock, flags);

	अगर(pages_mapped <= 8) अणु
		PCXL_FREE_MAPPINGS(res_idx, mask, 8);
	पूर्ण अन्यथा अगर(pages_mapped <= 16) अणु
		PCXL_FREE_MAPPINGS(res_idx, mask, 16);
	पूर्ण अन्यथा अगर(pages_mapped <= 32) अणु
		PCXL_FREE_MAPPINGS(res_idx, mask, 32);
	पूर्ण अन्यथा अणु
		panic("%s: pcxl_free_range() Too many pages to unmap.\n",
		      __खाता__);
	पूर्ण
	
	pcxl_used_pages -= (pages_mapped ? pages_mapped : 1);
	pcxl_used_bytes -= ((pages_mapped >> 3) ? (pages_mapped >> 3) : 1);

	spin_unlock_irqrestore(&pcxl_res_lock, flags);

	dump_resmap();
पूर्ण

अटल पूर्णांक __maybe_unused proc_pcxl_dma_show(काष्ठा seq_file *m, व्योम *v)
अणु
#अगर 0
	u_दीर्घ i = 0;
	अचिन्हित दीर्घ *res_ptr = (u_दीर्घ *)pcxl_res_map;
#पूर्ण_अगर
	अचिन्हित दीर्घ total_pages = pcxl_res_size << 3;   /* 8 bits per byte */

	seq_म_लिखो(m, "\nDMA Mapping Area size    : %d bytes (%ld pages)\n",
		PCXL_DMA_MAP_SIZE, total_pages);

	seq_म_लिखो(m, "Resource bitmap : %d bytes\n", pcxl_res_size);

	seq_माला_दो(m,  "     	  total:    free:    used:   % used:\n");
	seq_म_लिखो(m, "blocks  %8d %8ld %8ld %8ld%%\n", pcxl_res_size,
		pcxl_res_size - pcxl_used_bytes, pcxl_used_bytes,
		(pcxl_used_bytes * 100) / pcxl_res_size);

	seq_म_लिखो(m, "pages   %8ld %8ld %8ld %8ld%%\n", total_pages,
		total_pages - pcxl_used_pages, pcxl_used_pages,
		(pcxl_used_pages * 100 / total_pages));

#अगर 0
	seq_माला_दो(m, "\nResource bitmap:");

	क्रम(; i < (pcxl_res_size / माप(u_दीर्घ)); ++i, ++res_ptr) अणु
		अगर ((i & 7) == 0)
		    seq_माला_दो(m,"\n   ");
		seq_म_लिखो(m, "%s %08lx", buf, *res_ptr);
	पूर्ण
#पूर्ण_अगर
	seq_अ_दो(m, '\n');
	वापस 0;
पूर्ण

अटल पूर्णांक __init
pcxl_dma_init(व्योम)
अणु
	अगर (pcxl_dma_start == 0)
		वापस 0;

	pcxl_res_size = PCXL_DMA_MAP_SIZE >> (PAGE_SHIFT + 3);
	pcxl_res_hपूर्णांक = 0;
	pcxl_res_map = (अक्षर *)__get_मुक्त_pages(GFP_KERNEL,
					    get_order(pcxl_res_size));
	स_रखो(pcxl_res_map, 0, pcxl_res_size);
	proc_gsc_root = proc_सूची_गढ़ो("gsc", शून्य);
	अगर (!proc_gsc_root)
    		prपूर्णांकk(KERN_WARNING
			"pcxl_dma_init: Unable to create gsc /proc dir entry\n");
	अन्यथा अणु
		काष्ठा proc_dir_entry* ent;
		ent = proc_create_single("pcxl_dma", 0, proc_gsc_root,
				proc_pcxl_dma_show);
		अगर (!ent)
			prपूर्णांकk(KERN_WARNING
				"pci-dma.c: Unable to create pcxl_dma /proc entry.\n");
	पूर्ण
	वापस 0;
पूर्ण

__initcall(pcxl_dma_init);

व्योम *arch_dma_alloc(काष्ठा device *dev, माप_प्रकार size,
		dma_addr_t *dma_handle, gfp_t gfp, अचिन्हित दीर्घ attrs)
अणु
	अचिन्हित दीर्घ vaddr;
	अचिन्हित दीर्घ paddr;
	पूर्णांक order;

	अगर (boot_cpu_data.cpu_type != pcxl2 && boot_cpu_data.cpu_type != pcxl)
		वापस शून्य;

	order = get_order(size);
	size = 1 << (order + PAGE_SHIFT);
	vaddr = pcxl_alloc_range(size);
	paddr = __get_मुक्त_pages(gfp | __GFP_ZERO, order);
	flush_kernel_dcache_range(paddr, size);
	paddr = __pa(paddr);
	map_uncached_pages(vaddr, size, paddr);
	*dma_handle = (dma_addr_t) paddr;

#अगर 0
/* This probably isn't needed to support EISA cards.
** ISA cards will certainly only support 24-bit DMA addressing.
** Not clear अगर we can, want, or need to support ISA.
*/
	अगर (!dev || *dev->coherent_dma_mask < 0xffffffff)
		gfp |= GFP_DMA;
#पूर्ण_अगर
	वापस (व्योम *)vaddr;
पूर्ण

व्योम arch_dma_मुक्त(काष्ठा device *dev, माप_प्रकार size, व्योम *vaddr,
		dma_addr_t dma_handle, अचिन्हित दीर्घ attrs)
अणु
	पूर्णांक order = get_order(size);

	WARN_ON_ONCE(boot_cpu_data.cpu_type != pcxl2 &&
		     boot_cpu_data.cpu_type != pcxl);

	size = 1 << (order + PAGE_SHIFT);
	unmap_uncached_pages((अचिन्हित दीर्घ)vaddr, size);
	pcxl_मुक्त_range((अचिन्हित दीर्घ)vaddr, size);

	मुक्त_pages((अचिन्हित दीर्घ)__va(dma_handle), order);
पूर्ण

व्योम arch_sync_dma_क्रम_device(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	flush_kernel_dcache_range((अचिन्हित दीर्घ)phys_to_virt(paddr), size);
पूर्ण

व्योम arch_sync_dma_क्रम_cpu(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	flush_kernel_dcache_range((अचिन्हित दीर्घ)phys_to_virt(paddr), size);
पूर्ण
