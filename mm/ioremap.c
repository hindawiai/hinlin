<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Re-map IO memory to kernel address space so that we can access it.
 * This is needed क्रम high PCI addresses that aren't mapped in the
 * 640k-1MB IO memory area on PC's
 *
 * (C) Copyright 1995 1996 Linus Torvalds
 */
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/पन.स>
#समावेश <linux/export.h>
#समावेश <यंत्र/cacheflush.h>

#समावेश "pgalloc-track.h"

#अगर_घोषित CONFIG_HAVE_ARCH_HUGE_VMAP
अटल अचिन्हित पूर्णांक __ro_after_init iomap_max_page_shअगरt = BITS_PER_LONG - 1;

अटल पूर्णांक __init set_nohugeiomap(अक्षर *str)
अणु
	iomap_max_page_shअगरt = PAGE_SHIFT;
	वापस 0;
पूर्ण
early_param("nohugeiomap", set_nohugeiomap);
#अन्यथा /* CONFIG_HAVE_ARCH_HUGE_VMAP */
अटल स्थिर अचिन्हित पूर्णांक iomap_max_page_shअगरt = PAGE_SHIFT;
#पूर्ण_अगर	/* CONFIG_HAVE_ARCH_HUGE_VMAP */

पूर्णांक ioremap_page_range(अचिन्हित दीर्घ addr,
		       अचिन्हित दीर्घ end, phys_addr_t phys_addr, pgprot_t prot)
अणु
	वापस vmap_range(addr, end, phys_addr, prot, iomap_max_page_shअगरt);
पूर्ण

#अगर_घोषित CONFIG_GENERIC_IOREMAP
व्योम __iomem *ioremap_prot(phys_addr_t addr, माप_प्रकार size, अचिन्हित दीर्घ prot)
अणु
	अचिन्हित दीर्घ offset, vaddr;
	phys_addr_t last_addr;
	काष्ठा vm_काष्ठा *area;

	/* Disallow wrap-around or zero size */
	last_addr = addr + size - 1;
	अगर (!size || last_addr < addr)
		वापस शून्य;

	/* Page-align mappings */
	offset = addr & (~PAGE_MASK);
	addr -= offset;
	size = PAGE_ALIGN(size + offset);

	area = get_vm_area_caller(size, VM_IOREMAP,
			__builtin_वापस_address(0));
	अगर (!area)
		वापस शून्य;
	vaddr = (अचिन्हित दीर्घ)area->addr;

	अगर (ioremap_page_range(vaddr, vaddr + size, addr, __pgprot(prot))) अणु
		मुक्त_vm_area(area);
		वापस शून्य;
	पूर्ण

	वापस (व्योम __iomem *)(vaddr + offset);
पूर्ण
EXPORT_SYMBOL(ioremap_prot);

व्योम iounmap(अस्थिर व्योम __iomem *addr)
अणु
	vunmap((व्योम *)((अचिन्हित दीर्घ)addr & PAGE_MASK));
पूर्ण
EXPORT_SYMBOL(iounmap);
#पूर्ण_अगर /* CONFIG_GENERIC_IOREMAP */
