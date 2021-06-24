<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on arch/arm/mm/ioremap.c
 *
 * (C) Copyright 1995 1996 Linus Torvalds
 * Hacked क्रम ARM by Phil Blundell <philb@gnu.org>
 * Hacked to allow all architectures to build, and various cleanups
 * by Russell King
 * Copyright (C) 2012 ARM Ltd.
 */

#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/fixmap.h>
#समावेश <यंत्र/tlbflush.h>

अटल व्योम __iomem *__ioremap_caller(phys_addr_t phys_addr, माप_प्रकार size,
				      pgprot_t prot, व्योम *caller)
अणु
	अचिन्हित दीर्घ last_addr;
	अचिन्हित दीर्घ offset = phys_addr & ~PAGE_MASK;
	पूर्णांक err;
	अचिन्हित दीर्घ addr;
	काष्ठा vm_काष्ठा *area;

	/*
	 * Page align the mapping address and size, taking account of any
	 * offset.
	 */
	phys_addr &= PAGE_MASK;
	size = PAGE_ALIGN(size + offset);

	/*
	 * Don't allow wraparound, zero size or outside PHYS_MASK.
	 */
	last_addr = phys_addr + size - 1;
	अगर (!size || last_addr < phys_addr || (last_addr & ~PHYS_MASK))
		वापस शून्य;

	/*
	 * Don't allow RAM to be mapped.
	 */
	अगर (WARN_ON(pfn_valid(__phys_to_pfn(phys_addr))))
		वापस शून्य;

	area = get_vm_area_caller(size, VM_IOREMAP, caller);
	अगर (!area)
		वापस शून्य;
	addr = (अचिन्हित दीर्घ)area->addr;
	area->phys_addr = phys_addr;

	err = ioremap_page_range(addr, addr + size, phys_addr, prot);
	अगर (err) अणु
		vunmap((व्योम *)addr);
		वापस शून्य;
	पूर्ण

	वापस (व्योम __iomem *)(offset + addr);
पूर्ण

व्योम __iomem *__ioremap(phys_addr_t phys_addr, माप_प्रकार size, pgprot_t prot)
अणु
	वापस __ioremap_caller(phys_addr, size, prot,
				__builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL(__ioremap);

व्योम iounmap(अस्थिर व्योम __iomem *io_addr)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)io_addr & PAGE_MASK;

	/*
	 * We could get an address outside vदो_स्मृति range in हाल
	 * of ioremap_cache() reusing a RAM mapping.
	 */
	अगर (is_vदो_स्मृति_addr((व्योम *)addr))
		vunmap((व्योम *)addr);
पूर्ण
EXPORT_SYMBOL(iounmap);

व्योम __iomem *ioremap_cache(phys_addr_t phys_addr, माप_प्रकार size)
अणु
	/* For normal memory we alपढ़ोy have a cacheable mapping. */
	अगर (pfn_valid(__phys_to_pfn(phys_addr)))
		वापस (व्योम __iomem *)__phys_to_virt(phys_addr);

	वापस __ioremap_caller(phys_addr, size, __pgprot(PROT_NORMAL),
				__builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL(ioremap_cache);

/*
 * Must be called after early_fixmap_init
 */
व्योम __init early_ioremap_init(व्योम)
अणु
	early_ioremap_setup();
पूर्ण
