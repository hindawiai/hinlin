<शैली गुरु>
/*
 * Copyright (C) 2010 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2009 Wind River Systems Inc
 *   Implemented by fredrik.markstrom@gmail.com and ivarholmqvist@gmail.com
 * Copyright (C) 2004 Microtronix Datacom Ltd.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>

अटल अंतरभूत व्योम remap_area_pte(pte_t *pte, अचिन्हित दीर्घ address,
				अचिन्हित दीर्घ size, अचिन्हित दीर्घ phys_addr,
				अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ end;
	अचिन्हित दीर्घ pfn;
	pgprot_t pgprot = __pgprot(_PAGE_GLOBAL | _PAGE_PRESENT | _PAGE_READ
				| _PAGE_WRITE | flags);

	address &= ~PMD_MASK;
	end = address + size;
	अगर (end > PMD_SIZE)
		end = PMD_SIZE;
	अगर (address >= end)
		BUG();
	pfn = PFN_DOWN(phys_addr);
	करो अणु
		अगर (!pte_none(*pte)) अणु
			pr_err("remap_area_pte: page already exists\n");
			BUG();
		पूर्ण
		set_pte(pte, pfn_pte(pfn, pgprot));
		address += PAGE_SIZE;
		pfn++;
		pte++;
	पूर्ण जबतक (address && (address < end));
पूर्ण

अटल अंतरभूत पूर्णांक remap_area_pmd(pmd_t *pmd, अचिन्हित दीर्घ address,
				अचिन्हित दीर्घ size, अचिन्हित दीर्घ phys_addr,
				अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ end;

	address &= ~PGसूची_MASK;
	end = address + size;
	अगर (end > PGसूची_SIZE)
		end = PGसूची_SIZE;
	phys_addr -= address;
	अगर (address >= end)
		BUG();
	करो अणु
		pte_t *pte = pte_alloc_kernel(pmd, address);

		अगर (!pte)
			वापस -ENOMEM;
		remap_area_pte(pte, address, end - address, address + phys_addr,
			flags);
		address = (address + PMD_SIZE) & PMD_MASK;
		pmd++;
	पूर्ण जबतक (address && (address < end));
	वापस 0;
पूर्ण

अटल पूर्णांक remap_area_pages(अचिन्हित दीर्घ address, अचिन्हित दीर्घ phys_addr,
				अचिन्हित दीर्घ size, अचिन्हित दीर्घ flags)
अणु
	पूर्णांक error;
	pgd_t *dir;
	अचिन्हित दीर्घ end = address + size;

	phys_addr -= address;
	dir = pgd_offset(&init_mm, address);
	flush_cache_all();
	अगर (address >= end)
		BUG();
	करो अणु
		p4d_t *p4d;
		pud_t *pud;
		pmd_t *pmd;

		error = -ENOMEM;
		p4d = p4d_alloc(&init_mm, dir, address);
		अगर (!p4d)
			अवरोध;
		pud = pud_alloc(&init_mm, p4d, address);
		अगर (!pud)
			अवरोध;
		pmd = pmd_alloc(&init_mm, pud, address);
		अगर (!pmd)
			अवरोध;
		अगर (remap_area_pmd(pmd, address, end - address,
			phys_addr + address, flags))
			अवरोध;
		error = 0;
		address = (address + PGसूची_SIZE) & PGसूची_MASK;
		dir++;
	पूर्ण जबतक (address && (address < end));
	flush_tlb_all();
	वापस error;
पूर्ण

#घोषणा IS_MAPPABLE_UNCACHEABLE(addr) (addr < 0x20000000UL)

/*
 * Map some physical address range पूर्णांकo the kernel address space.
 */
व्योम __iomem *ioremap(अचिन्हित दीर्घ phys_addr, अचिन्हित दीर्घ size)
अणु
	काष्ठा vm_काष्ठा *area;
	अचिन्हित दीर्घ offset;
	अचिन्हित दीर्घ last_addr;
	व्योम *addr;

	/* Don't allow wraparound or zero size */
	last_addr = phys_addr + size - 1;

	अगर (!size || last_addr < phys_addr)
		वापस शून्य;

	/* Don't allow anybody to remap normal RAM that we're using */
	अगर (phys_addr > PHYS_OFFSET && phys_addr < virt_to_phys(high_memory)) अणु
		अक्षर *t_addr, *t_end;
		काष्ठा page *page;

		t_addr = __va(phys_addr);
		t_end = t_addr + (size - 1);
		क्रम (page = virt_to_page(t_addr);
			page <= virt_to_page(t_end); page++)
			अगर (!PageReserved(page))
				वापस शून्य;
	पूर्ण

	/*
	 * Map uncached objects in the low part of address space to
	 * CONFIG_NIOS2_IO_REGION_BASE
	 */
	अगर (IS_MAPPABLE_UNCACHEABLE(phys_addr) &&
	    IS_MAPPABLE_UNCACHEABLE(last_addr))
		वापस (व्योम __iomem *)(CONFIG_NIOS2_IO_REGION_BASE + phys_addr);

	/* Mappings have to be page-aligned */
	offset = phys_addr & ~PAGE_MASK;
	phys_addr &= PAGE_MASK;
	size = PAGE_ALIGN(last_addr + 1) - phys_addr;

	/* Ok, go क्रम it */
	area = get_vm_area(size, VM_IOREMAP);
	अगर (!area)
		वापस शून्य;
	addr = area->addr;
	अगर (remap_area_pages((अचिन्हित दीर्घ) addr, phys_addr, size, 0)) अणु
		vunmap(addr);
		वापस शून्य;
	पूर्ण
	वापस (व्योम __iomem *) (offset + (अक्षर *)addr);
पूर्ण
EXPORT_SYMBOL(ioremap);

/*
 * iounmap unmaps nearly everything, so be careful
 * it करोesn't मुक्त currently poपूर्णांकer/page tables anymore but it
 * wasn't used anyway and might be added later.
 */
व्योम iounmap(व्योम __iomem *addr)
अणु
	काष्ठा vm_काष्ठा *p;

	अगर ((अचिन्हित दीर्घ) addr > CONFIG_NIOS2_IO_REGION_BASE)
		वापस;

	p = हटाओ_vm_area((व्योम *) (PAGE_MASK & (अचिन्हित दीर्घ __क्रमce) addr));
	अगर (!p)
		pr_err("iounmap: bad address %p\n", addr);
	kमुक्त(p);
पूर्ण
EXPORT_SYMBOL(iounmap);
