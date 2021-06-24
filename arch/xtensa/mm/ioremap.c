<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ioremap implementation.
 *
 * Copyright (C) 2015 Cadence Design Systems Inc.
 */

#समावेश <linux/पन.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/पन.स>

अटल व्योम __iomem *xtensa_ioremap(अचिन्हित दीर्घ paddr, अचिन्हित दीर्घ size,
				    pgprot_t prot)
अणु
	अचिन्हित दीर्घ offset = paddr & ~PAGE_MASK;
	अचिन्हित दीर्घ pfn = __phys_to_pfn(paddr);
	काष्ठा vm_काष्ठा *area;
	अचिन्हित दीर्घ vaddr;
	पूर्णांक err;

	paddr &= PAGE_MASK;

	WARN_ON(pfn_valid(pfn));

	size = PAGE_ALIGN(offset + size);

	area = get_vm_area(size, VM_IOREMAP);
	अगर (!area)
		वापस शून्य;

	vaddr = (अचिन्हित दीर्घ)area->addr;
	area->phys_addr = paddr;

	err = ioremap_page_range(vaddr, vaddr + size, paddr, prot);

	अगर (err) अणु
		vunmap((व्योम *)vaddr);
		वापस शून्य;
	पूर्ण

	flush_cache_vmap(vaddr, vaddr + size);
	वापस (व्योम __iomem *)(offset + vaddr);
पूर्ण

व्योम __iomem *xtensa_ioremap_nocache(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	वापस xtensa_ioremap(addr, size, pgprot_noncached(PAGE_KERNEL));
पूर्ण
EXPORT_SYMBOL(xtensa_ioremap_nocache);

व्योम __iomem *xtensa_ioremap_cache(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	वापस xtensa_ioremap(addr, size, PAGE_KERNEL);
पूर्ण
EXPORT_SYMBOL(xtensa_ioremap_cache);

व्योम xtensa_iounmap(अस्थिर व्योम __iomem *io_addr)
अणु
	व्योम *addr = (व्योम *)(PAGE_MASK & (अचिन्हित दीर्घ)io_addr);

	vunmap(addr);
पूर्ण
EXPORT_SYMBOL(xtensa_iounmap);
