<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/parisc/mm/ioremap.c
 *
 * (C) Copyright 1995 1996 Linus Torvalds
 * (C) Copyright 2001-2019 Helge Deller <deller@gmx.de>
 * (C) Copyright 2005 Kyle McMartin <kyle@parisc-linux.org>
 */

#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>

/*
 * Generic mapping function (not visible outside):
 */

/*
 * Remap an arbitrary physical address space पूर्णांकo the kernel भव
 * address space.
 *
 * NOTE! We need to allow non-page-aligned mappings too: we will obviously
 * have to convert them पूर्णांकo an offset in a page-aligned mapping, but the
 * caller shouldn't need to know that small detail.
 */
व्योम __iomem *ioremap(अचिन्हित दीर्घ phys_addr, अचिन्हित दीर्घ size)
अणु
	व्योम __iomem *addr;
	काष्ठा vm_काष्ठा *area;
	अचिन्हित दीर्घ offset, last_addr;
	pgprot_t pgprot;

#अगर_घोषित CONFIG_EISA
	अचिन्हित दीर्घ end = phys_addr + size - 1;
	/* Support EISA addresses */
	अगर ((phys_addr >= 0x00080000 && end < 0x000fffff) ||
	    (phys_addr >= 0x00500000 && end < 0x03bfffff))
		phys_addr |= F_EXTEND(0xfc000000);
#पूर्ण_अगर

	/* Don't allow wraparound or zero size */
	last_addr = phys_addr + size - 1;
	अगर (!size || last_addr < phys_addr)
		वापस शून्य;

	/*
	 * Don't allow anybody to remap normal RAM that we're using..
	 */
	अगर (phys_addr < virt_to_phys(high_memory)) अणु
		अक्षर *t_addr, *t_end;
		काष्ठा page *page;

		t_addr = __va(phys_addr);
		t_end = t_addr + (size - 1);
	   
		क्रम (page = virt_to_page(t_addr); 
		     page <= virt_to_page(t_end); page++) अणु
			अगर(!PageReserved(page))
				वापस शून्य;
		पूर्ण
	पूर्ण

	pgprot = __pgprot(_PAGE_PRESENT | _PAGE_RW | _PAGE_सूचीTY |
			  _PAGE_ACCESSED | _PAGE_NO_CACHE);

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

	addr = (व्योम __iomem *) area->addr;
	अगर (ioremap_page_range((अचिन्हित दीर्घ)addr, (अचिन्हित दीर्घ)addr + size,
			       phys_addr, pgprot)) अणु
		vunmap(addr);
		वापस शून्य;
	पूर्ण

	वापस (व्योम __iomem *) (offset + (अक्षर __iomem *)addr);
पूर्ण
EXPORT_SYMBOL(ioremap);

व्योम iounmap(स्थिर अस्थिर व्योम __iomem *io_addr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)io_addr & PAGE_MASK;

	अगर (is_vदो_स्मृति_addr((व्योम *)addr))
		vunmap((व्योम *)addr);
पूर्ण
EXPORT_SYMBOL(iounmap);
