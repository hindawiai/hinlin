<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

व्योम __iomem *__ioremap_caller(phys_addr_t addr, अचिन्हित दीर्घ size,
			       pgprot_t prot, व्योम *caller)
अणु
	phys_addr_t paligned, offset;
	व्योम __iomem *ret;
	पूर्णांक err;

	/* We करोn't support the 4K PFN hack with ioremap */
	अगर (pgprot_val(prot) & H_PAGE_4K_PFN)
		वापस शून्य;

	/*
	 * Choose an address to map it to. Once the vदो_स्मृति प्रणाली is running,
	 * we use it. Beक्रमe that, we map using addresses going up from
	 * ioremap_bot.  vदो_स्मृति will use the addresses from IOREMAP_BASE
	 * through ioremap_bot.
	 */
	paligned = addr & PAGE_MASK;
	offset = addr & ~PAGE_MASK;
	size = PAGE_ALIGN(addr + size) - paligned;

	अगर (size == 0 || paligned == 0)
		वापस शून्य;

	अगर (slab_is_available())
		वापस करो_ioremap(paligned, offset, size, prot, caller);

	pr_warn("ioremap() called early from %pS. Use early_ioremap() instead\n", caller);

	err = early_ioremap_range(ioremap_bot, paligned, size, prot);
	अगर (err)
		वापस शून्य;

	ret = (व्योम __iomem *)ioremap_bot + offset;
	ioremap_bot += size;

	वापस ret;
पूर्ण

/*
 * Unmap an IO region and हटाओ it from vदो_स्मृति'd list.
 * Access to IO memory should be serialized by driver.
 */
व्योम iounmap(अस्थिर व्योम __iomem *token)
अणु
	व्योम *addr;

	अगर (!slab_is_available())
		वापस;

	addr = (व्योम *)((अचिन्हित दीर्घ __क्रमce)PCI_FIX_ADDR(token) & PAGE_MASK);

	अगर ((अचिन्हित दीर्घ)addr < ioremap_bot) अणु
		pr_warn("Attempt to iounmap early bolted mapping at 0x%p\n", addr);
		वापस;
	पूर्ण
	vunmap(addr);
पूर्ण
EXPORT_SYMBOL(iounmap);
