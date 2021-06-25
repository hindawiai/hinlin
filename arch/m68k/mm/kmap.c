<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/m68k/mm/kmap.c
 *
 *  Copyright (C) 1997 Roman Hodek
 *
 *  10/01/99 cleaned up the code and changing to the same पूर्णांकerface
 *	     used by other architectures		/Roman Zippel
 */

#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/segment.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/tlbflush.h>

#अघोषित DEBUG

/*
 * For 040/060 we can use the भव memory area like other architectures,
 * but क्रम 020/030 we want to use early termination page descriptors and we
 * can't mix this with normal page descriptors, so we have to copy that code
 * (mm/vदो_स्मृति.c) and वापस appropriately aligned addresses.
 */

#अगर_घोषित CPU_M68040_OR_M68060_ONLY

#घोषणा IO_SIZE		PAGE_SIZE

अटल अंतरभूत काष्ठा vm_काष्ठा *get_io_area(अचिन्हित दीर्घ size)
अणु
	वापस get_vm_area(size, VM_IOREMAP);
पूर्ण


अटल अंतरभूत व्योम मुक्त_io_area(व्योम *addr)
अणु
	vमुक्त((व्योम *)(PAGE_MASK & (अचिन्हित दीर्घ)addr));
पूर्ण

#अन्यथा

#घोषणा IO_SIZE		PMD_SIZE

अटल काष्ठा vm_काष्ठा *iolist;

/*
 * __मुक्त_io_area unmaps nearly everything, so be careful
 * Currently it करोesn't मुक्त poपूर्णांकer/page tables anymore but this
 * wasn't used anyway and might be added later.
 */
अटल व्योम __मुक्त_io_area(व्योम *addr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ virtaddr = (अचिन्हित दीर्घ)addr;
	pgd_t *pgd_dir;
	p4d_t *p4d_dir;
	pud_t *pud_dir;
	pmd_t *pmd_dir;
	pte_t *pte_dir;

	जबतक ((दीर्घ)size > 0) अणु
		pgd_dir = pgd_offset_k(virtaddr);
		p4d_dir = p4d_offset(pgd_dir, virtaddr);
		pud_dir = pud_offset(p4d_dir, virtaddr);
		अगर (pud_bad(*pud_dir)) अणु
			prपूर्णांकk("iounmap: bad pud(%08lx)\n", pud_val(*pud_dir));
			pud_clear(pud_dir);
			वापस;
		पूर्ण
		pmd_dir = pmd_offset(pud_dir, virtaddr);

#अगर CONFIG_PGTABLE_LEVELS == 3
		अगर (CPU_IS_020_OR_030) अणु
			पूर्णांक pmd_type = pmd_val(*pmd_dir) & _DESCTYPE_MASK;

			अगर (pmd_type == _PAGE_PRESENT) अणु
				pmd_clear(pmd_dir);
				virtaddr += PMD_SIZE;
				size -= PMD_SIZE;

			पूर्ण अन्यथा अगर (pmd_type == 0)
				जारी;
		पूर्ण
#पूर्ण_अगर

		अगर (pmd_bad(*pmd_dir)) अणु
			prपूर्णांकk("iounmap: bad pmd (%08lx)\n", pmd_val(*pmd_dir));
			pmd_clear(pmd_dir);
			वापस;
		पूर्ण
		pte_dir = pte_offset_kernel(pmd_dir, virtaddr);

		pte_val(*pte_dir) = 0;
		virtaddr += PAGE_SIZE;
		size -= PAGE_SIZE;
	पूर्ण

	flush_tlb_all();
पूर्ण

अटल काष्ठा vm_काष्ठा *get_io_area(अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ addr;
	काष्ठा vm_काष्ठा **p, *पंचांगp, *area;

	area = kदो_स्मृति(माप(*area), GFP_KERNEL);
	अगर (!area)
		वापस शून्य;
	addr = KMAP_START;
	क्रम (p = &iolist; (पंचांगp = *p) ; p = &पंचांगp->next) अणु
		अगर (size + addr < (अचिन्हित दीर्घ)पंचांगp->addr)
			अवरोध;
		अगर (addr > KMAP_END-size) अणु
			kमुक्त(area);
			वापस शून्य;
		पूर्ण
		addr = पंचांगp->size + (अचिन्हित दीर्घ)पंचांगp->addr;
	पूर्ण
	area->addr = (व्योम *)addr;
	area->size = size + IO_SIZE;
	area->next = *p;
	*p = area;
	वापस area;
पूर्ण

अटल अंतरभूत व्योम मुक्त_io_area(व्योम *addr)
अणु
	काष्ठा vm_काष्ठा **p, *पंचांगp;

	अगर (!addr)
		वापस;
	addr = (व्योम *)((अचिन्हित दीर्घ)addr & -IO_SIZE);
	क्रम (p = &iolist ; (पंचांगp = *p) ; p = &पंचांगp->next) अणु
		अगर (पंचांगp->addr == addr) अणु
			*p = पंचांगp->next;
			/* हटाओ gap added in get_io_area() */
			__मुक्त_io_area(पंचांगp->addr, पंचांगp->size - IO_SIZE);
			kमुक्त(पंचांगp);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

#पूर्ण_अगर

/*
 * Map some physical address range पूर्णांकo the kernel address space.
 */
/* Rewritten by Andreas Schwab to हटाओ all races. */

व्योम __iomem *__ioremap(अचिन्हित दीर्घ physaddr, अचिन्हित दीर्घ size, पूर्णांक cacheflag)
अणु
	काष्ठा vm_काष्ठा *area;
	अचिन्हित दीर्घ virtaddr, retaddr;
	दीर्घ offset;
	pgd_t *pgd_dir;
	p4d_t *p4d_dir;
	pud_t *pud_dir;
	pmd_t *pmd_dir;
	pte_t *pte_dir;

	/*
	 * Don't allow mappings that wrap..
	 */
	अगर (!size || physaddr > (अचिन्हित दीर्घ)(-size))
		वापस शून्य;

#अगर_घोषित CONFIG_AMIGA
	अगर (MACH_IS_AMIGA) अणु
		अगर ((physaddr >= 0x40000000) && (physaddr + size < 0x60000000)
		    && (cacheflag == IOMAP_NOCACHE_SER))
			वापस (व्योम __iomem *)physaddr;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_COLDFIRE
	अगर (__cf_पूर्णांकernalio(physaddr))
		वापस (व्योम __iomem *) physaddr;
#पूर्ण_अगर

#अगर_घोषित DEBUG
	prपूर्णांकk("ioremap: 0x%lx,0x%lx(%d) - ", physaddr, size, cacheflag);
#पूर्ण_अगर
	/*
	 * Mappings have to be aligned
	 */
	offset = physaddr & (IO_SIZE - 1);
	physaddr &= -IO_SIZE;
	size = (size + offset + IO_SIZE - 1) & -IO_SIZE;

	/*
	 * Ok, go क्रम it..
	 */
	area = get_io_area(size);
	अगर (!area)
		वापस शून्य;

	virtaddr = (अचिन्हित दीर्घ)area->addr;
	retaddr = virtaddr + offset;
#अगर_घोषित DEBUG
	prपूर्णांकk("0x%lx,0x%lx,0x%lx", physaddr, virtaddr, retaddr);
#पूर्ण_अगर

	/*
	 * add cache and table flags to physical address
	 */
	अगर (CPU_IS_040_OR_060) अणु
		physaddr |= (_PAGE_PRESENT | _PAGE_GLOBAL040 |
			     _PAGE_ACCESSED | _PAGE_सूचीTY);
		चयन (cacheflag) अणु
		हाल IOMAP_FULL_CACHING:
			physaddr |= _PAGE_CACHE040;
			अवरोध;
		हाल IOMAP_NOCACHE_SER:
		शेष:
			physaddr |= _PAGE_NOCACHE_S;
			अवरोध;
		हाल IOMAP_NOCACHE_NONSER:
			physaddr |= _PAGE_NOCACHE;
			अवरोध;
		हाल IOMAP_WRITETHROUGH:
			physaddr |= _PAGE_CACHE040W;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		physaddr |= (_PAGE_PRESENT | _PAGE_ACCESSED |
			     _PAGE_सूचीTY | _PAGE_READWRITE);
		चयन (cacheflag) अणु
		हाल IOMAP_NOCACHE_SER:
		हाल IOMAP_NOCACHE_NONSER:
		शेष:
			physaddr |= _PAGE_NOCACHE030;
			अवरोध;
		हाल IOMAP_FULL_CACHING:
		हाल IOMAP_WRITETHROUGH:
			अवरोध;
		पूर्ण
	पूर्ण

	जबतक ((दीर्घ)size > 0) अणु
#अगर_घोषित DEBUG
		अगर (!(virtaddr & (PMD_SIZE-1)))
			prपूर्णांकk ("\npa=%#lx va=%#lx ", physaddr, virtaddr);
#पूर्ण_अगर
		pgd_dir = pgd_offset_k(virtaddr);
		p4d_dir = p4d_offset(pgd_dir, virtaddr);
		pud_dir = pud_offset(p4d_dir, virtaddr);
		pmd_dir = pmd_alloc(&init_mm, pud_dir, virtaddr);
		अगर (!pmd_dir) अणु
			prपूर्णांकk("ioremap: no mem for pmd_dir\n");
			वापस शून्य;
		पूर्ण

#अगर CONFIG_PGTABLE_LEVELS == 3
		अगर (CPU_IS_020_OR_030) अणु
			pmd_val(*pmd_dir) = physaddr;
			physaddr += PMD_SIZE;
			virtaddr += PMD_SIZE;
			size -= PMD_SIZE;
		पूर्ण अन्यथा
#पूर्ण_अगर
		अणु
			pte_dir = pte_alloc_kernel(pmd_dir, virtaddr);
			अगर (!pte_dir) अणु
				prपूर्णांकk("ioremap: no mem for pte_dir\n");
				वापस शून्य;
			पूर्ण

			pte_val(*pte_dir) = physaddr;
			virtaddr += PAGE_SIZE;
			physaddr += PAGE_SIZE;
			size -= PAGE_SIZE;
		पूर्ण
	पूर्ण
#अगर_घोषित DEBUG
	prपूर्णांकk("\n");
#पूर्ण_अगर
	flush_tlb_all();

	वापस (व्योम __iomem *)retaddr;
पूर्ण
EXPORT_SYMBOL(__ioremap);

/*
 * Unmap an ioremap()ed region again
 */
व्योम iounmap(व्योम __iomem *addr)
अणु
#अगर_घोषित CONFIG_AMIGA
	अगर ((!MACH_IS_AMIGA) ||
	    (((अचिन्हित दीर्घ)addr < 0x40000000) ||
	     ((अचिन्हित दीर्घ)addr > 0x60000000)))
			मुक्त_io_area((__क्रमce व्योम *)addr);
#अन्यथा
#अगर_घोषित CONFIG_COLDFIRE
	अगर (cf_पूर्णांकernalio(addr))
		वापस;
#पूर्ण_अगर
	मुक्त_io_area((__क्रमce व्योम *)addr);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(iounmap);

/*
 * Set new cache mode क्रम some kernel address space.
 * The caller must push data क्रम that range itself, अगर such data may alपढ़ोy
 * be in the cache.
 */
व्योम kernel_set_cachemode(व्योम *addr, अचिन्हित दीर्घ size, पूर्णांक cmode)
अणु
	अचिन्हित दीर्घ virtaddr = (अचिन्हित दीर्घ)addr;
	pgd_t *pgd_dir;
	p4d_t *p4d_dir;
	pud_t *pud_dir;
	pmd_t *pmd_dir;
	pte_t *pte_dir;

	अगर (CPU_IS_040_OR_060) अणु
		चयन (cmode) अणु
		हाल IOMAP_FULL_CACHING:
			cmode = _PAGE_CACHE040;
			अवरोध;
		हाल IOMAP_NOCACHE_SER:
		शेष:
			cmode = _PAGE_NOCACHE_S;
			अवरोध;
		हाल IOMAP_NOCACHE_NONSER:
			cmode = _PAGE_NOCACHE;
			अवरोध;
		हाल IOMAP_WRITETHROUGH:
			cmode = _PAGE_CACHE040W;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (cmode) अणु
		हाल IOMAP_NOCACHE_SER:
		हाल IOMAP_NOCACHE_NONSER:
		शेष:
			cmode = _PAGE_NOCACHE030;
			अवरोध;
		हाल IOMAP_FULL_CACHING:
		हाल IOMAP_WRITETHROUGH:
			cmode = 0;
		पूर्ण
	पूर्ण

	जबतक ((दीर्घ)size > 0) अणु
		pgd_dir = pgd_offset_k(virtaddr);
		p4d_dir = p4d_offset(pgd_dir, virtaddr);
		pud_dir = pud_offset(p4d_dir, virtaddr);
		अगर (pud_bad(*pud_dir)) अणु
			prपूर्णांकk("iocachemode: bad pud(%08lx)\n", pud_val(*pud_dir));
			pud_clear(pud_dir);
			वापस;
		पूर्ण
		pmd_dir = pmd_offset(pud_dir, virtaddr);

#अगर CONFIG_PGTABLE_LEVELS == 3
		अगर (CPU_IS_020_OR_030) अणु
			अचिन्हित दीर्घ pmd = pmd_val(*pmd_dir);

			अगर ((pmd & _DESCTYPE_MASK) == _PAGE_PRESENT) अणु
				*pmd_dir = __pmd((pmd & _CACHEMASK040) | cmode);
				virtaddr += PMD_SIZE;
				size -= PMD_SIZE;
				जारी;
			पूर्ण
		पूर्ण
#पूर्ण_अगर

		अगर (pmd_bad(*pmd_dir)) अणु
			prपूर्णांकk("iocachemode: bad pmd (%08lx)\n", pmd_val(*pmd_dir));
			pmd_clear(pmd_dir);
			वापस;
		पूर्ण
		pte_dir = pte_offset_kernel(pmd_dir, virtaddr);

		pte_val(*pte_dir) = (pte_val(*pte_dir) & _CACHEMASK040) | cmode;
		virtaddr += PAGE_SIZE;
		size -= PAGE_SIZE;
	पूर्ण

	flush_tlb_all();
पूर्ण
EXPORT_SYMBOL(kernel_set_cachemode);
