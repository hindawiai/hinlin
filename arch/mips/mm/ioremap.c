<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * (C) Copyright 1995 1996 Linus Torvalds
 * (C) Copyright 2001, 2002 Ralf Baechle
 */
#समावेश <linux/export.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/ioport.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <ioremap.h>

#घोषणा IS_LOW512(addr) (!((phys_addr_t)(addr) & (phys_addr_t) ~0x1fffffffULL))
#घोषणा IS_KSEG1(addr) (((अचिन्हित दीर्घ)(addr) & ~0x1fffffffUL) == CKSEG1)

अटल पूर्णांक __ioremap_check_ram(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ nr_pages,
			       व्योम *arg)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < nr_pages; i++) अणु
		अगर (pfn_valid(start_pfn + i) &&
		    !PageReserved(pfn_to_page(start_pfn + i)))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * ioremap_prot     -   map bus memory पूर्णांकo CPU space
 * @phys_addr:    bus address of the memory
 * @size:      size of the resource to map
 *
 * ioremap_prot gives the caller control over cache coherency attributes (CCA)
 */
व्योम __iomem *ioremap_prot(phys_addr_t phys_addr, अचिन्हित दीर्घ size,
		अचिन्हित दीर्घ prot_val)
अणु
	अचिन्हित दीर्घ flags = prot_val & _CACHE_MASK;
	अचिन्हित दीर्घ offset, pfn, last_pfn;
	काष्ठा vm_काष्ठा *area;
	phys_addr_t last_addr;
	अचिन्हित दीर्घ vaddr;
	व्योम __iomem *cpu_addr;

	cpu_addr = plat_ioremap(phys_addr, size, flags);
	अगर (cpu_addr)
		वापस cpu_addr;

	phys_addr = fixup_bigphys_addr(phys_addr, size);

	/* Don't allow wraparound or zero size */
	last_addr = phys_addr + size - 1;
	अगर (!size || last_addr < phys_addr)
		वापस शून्य;

	/*
	 * Map uncached objects in the low 512mb of address space using KSEG1,
	 * otherwise map using page tables.
	 */
	अगर (IS_LOW512(phys_addr) && IS_LOW512(last_addr) &&
	    flags == _CACHE_UNCACHED)
		वापस (व्योम __iomem *) CKSEG1ADDR(phys_addr);

	/*
	 * Don't allow anybody to remap RAM that may be allocated by the page
	 * allocator, since that could lead to races & data clobbering.
	 */
	pfn = PFN_DOWN(phys_addr);
	last_pfn = PFN_DOWN(last_addr);
	अगर (walk_प्रणाली_ram_range(pfn, last_pfn - pfn + 1, शून्य,
				  __ioremap_check_ram) == 1) अणु
		WARN_ONCE(1, "ioremap on RAM at %pa - %pa\n",
			  &phys_addr, &last_addr);
		वापस शून्य;
	पूर्ण

	/*
	 * Mappings have to be page-aligned
	 */
	offset = phys_addr & ~PAGE_MASK;
	phys_addr &= PAGE_MASK;
	size = PAGE_ALIGN(last_addr + 1) - phys_addr;

	/*
	 * Ok, go क्रम it..
	 */
	area = get_vm_area(size, VM_IOREMAP);
	अगर (!area)
		वापस शून्य;
	vaddr = (अचिन्हित दीर्घ)area->addr;

	flags |= _PAGE_GLOBAL | _PAGE_PRESENT | __READABLE | __WRITEABLE;
	अगर (ioremap_page_range(vaddr, vaddr + size, phys_addr,
			__pgprot(flags))) अणु
		मुक्त_vm_area(area);
		वापस शून्य;
	पूर्ण

	वापस (व्योम __iomem *)(vaddr + offset);
पूर्ण
EXPORT_SYMBOL(ioremap_prot);

व्योम iounmap(स्थिर अस्थिर व्योम __iomem *addr)
अणु
	अगर (!plat_iounmap(addr) && !IS_KSEG1(addr))
		vunmap((व्योम *)((अचिन्हित दीर्घ)addr & PAGE_MASK));
पूर्ण
EXPORT_SYMBOL(iounmap);
