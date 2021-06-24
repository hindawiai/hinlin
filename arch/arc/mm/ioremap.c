<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/cache.h>

अटल अंतरभूत bool arc_uncached_addr_space(phys_addr_t paddr)
अणु
	अगर (is_isa_arcompact()) अणु
		अगर (paddr >= ARC_UNCACHED_ADDR_SPACE)
			वापस true;
	पूर्ण अन्यथा अगर (paddr >= perip_base && paddr <= perip_end) अणु
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम __iomem *ioremap(phys_addr_t paddr, अचिन्हित दीर्घ size)
अणु
	phys_addr_t end;

	/* Don't allow wraparound or zero size */
	end = paddr + size - 1;
	अगर (!size || (end < paddr))
		वापस शून्य;

	/*
	 * If the region is h/w uncached, MMU mapping can be elided as optim
	 * The cast to u32 is fine as this region can only be inside 4GB
	 */
	अगर (arc_uncached_addr_space(paddr))
		वापस (व्योम __iomem *)(u32)paddr;

	वापस ioremap_prot(paddr, size, PAGE_KERNEL_NO_CACHE);
पूर्ण
EXPORT_SYMBOL(ioremap);

/*
 * ioremap with access flags
 * Cache semantics wise it is same as ioremap - "forced" uncached.
 * However unlike vanilla ioremap which bypasses ARC MMU क्रम addresses in
 * ARC hardware uncached region, this one still goes thru the MMU as caller
 * might need finer access control (R/W/X)
 */
व्योम __iomem *ioremap_prot(phys_addr_t paddr, अचिन्हित दीर्घ size,
			   अचिन्हित दीर्घ flags)
अणु
	अचिन्हित पूर्णांक off;
	अचिन्हित दीर्घ vaddr;
	काष्ठा vm_काष्ठा *area;
	phys_addr_t end;
	pgprot_t prot = __pgprot(flags);

	/* Don't allow wraparound, zero size */
	end = paddr + size - 1;
	अगर ((!size) || (end < paddr))
		वापस शून्य;

	/* An early platक्रमm driver might end up here */
	अगर (!slab_is_available())
		वापस शून्य;

	/* क्रमce uncached */
	prot = pgprot_noncached(prot);

	/* Mappings have to be page-aligned */
	off = paddr & ~PAGE_MASK;
	paddr &= PAGE_MASK_PHYS;
	size = PAGE_ALIGN(end + 1) - paddr;

	/*
	 * Ok, go क्रम it..
	 */
	area = get_vm_area(size, VM_IOREMAP);
	अगर (!area)
		वापस शून्य;
	area->phys_addr = paddr;
	vaddr = (अचिन्हित दीर्घ)area->addr;
	अगर (ioremap_page_range(vaddr, vaddr + size, paddr, prot)) अणु
		vunmap((व्योम __क्रमce *)vaddr);
		वापस शून्य;
	पूर्ण
	वापस (व्योम __iomem *)(off + (अक्षर __iomem *)vaddr);
पूर्ण
EXPORT_SYMBOL(ioremap_prot);


व्योम iounmap(स्थिर व्योम __iomem *addr)
अणु
	/* weird द्विगुन cast to handle phys_addr_t > 32 bits */
	अगर (arc_uncached_addr_space((phys_addr_t)(u32)addr))
		वापस;

	vमुक्त((व्योम *)(PAGE_MASK & (अचिन्हित दीर्घ __क्रमce)addr));
पूर्ण
EXPORT_SYMBOL(iounmap);
