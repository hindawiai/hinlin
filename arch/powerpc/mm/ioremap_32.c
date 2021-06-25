<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <mm/mmu_decl.h>

व्योम __iomem *ioremap_wt(phys_addr_t addr, अचिन्हित दीर्घ size)
अणु
	pgprot_t prot = pgprot_cached_wthru(PAGE_KERNEL);

	वापस __ioremap_caller(addr, size, prot, __builtin_वापस_address(0));
पूर्ण
EXPORT_SYMBOL(ioremap_wt);

व्योम __iomem *
__ioremap_caller(phys_addr_t addr, अचिन्हित दीर्घ size, pgprot_t prot, व्योम *caller)
अणु
	अचिन्हित दीर्घ v;
	phys_addr_t p, offset;
	पूर्णांक err;

	/*
	 * Choose an address to map it to.
	 * Once the vदो_स्मृति प्रणाली is running, we use it.
	 * Beक्रमe then, we use space going करोwn from IOREMAP_TOP
	 * (ioremap_bot records where we're up to).
	 */
	p = addr & PAGE_MASK;
	offset = addr & ~PAGE_MASK;
	size = PAGE_ALIGN(addr + size) - p;

	/*
	 * If the address lies within the first 16 MB, assume it's in ISA
	 * memory space
	 */
	अगर (p < 16 * 1024 * 1024)
		p += _ISA_MEM_BASE;

#अगर_अघोषित CONFIG_CRASH_DUMP
	/*
	 * Don't allow anybody to remap normal RAM that we're using.
	 * mem_init() sets high_memory so only करो the check after that.
	 */
	अगर (slab_is_available() && p <= virt_to_phys(high_memory - 1) &&
	    page_is_ram(__phys_to_pfn(p))) अणु
		pr_warn("%s(): phys addr 0x%llx is RAM lr %ps\n", __func__,
			(अचिन्हित दीर्घ दीर्घ)p, __builtin_वापस_address(0));
		वापस शून्य;
	पूर्ण
#पूर्ण_अगर

	अगर (size == 0)
		वापस शून्य;

	/*
	 * Is it alपढ़ोy mapped?  Perhaps overlapped by a previous
	 * mapping.
	 */
	v = p_block_mapped(p);
	अगर (v)
		वापस (व्योम __iomem *)v + offset;

	अगर (slab_is_available())
		वापस करो_ioremap(p, offset, size, prot, caller);

	/*
	 * Should check अगर it is a candidate क्रम a BAT mapping
	 */
	pr_warn("ioremap() called early from %pS. Use early_ioremap() instead\n", caller);

	err = early_ioremap_range(ioremap_bot - size, p, size, prot);
	अगर (err)
		वापस शून्य;
	ioremap_bot -= size;

	वापस (व्योम __iomem *)ioremap_bot + offset;
पूर्ण

व्योम iounmap(अस्थिर व्योम __iomem *addr)
अणु
	/*
	 * If mapped by BATs then there is nothing to करो.
	 * Calling vमुक्त() generates a benign warning.
	 */
	अगर (v_block_mapped((अचिन्हित दीर्घ)addr))
		वापस;

	अगर (addr > high_memory && (अचिन्हित दीर्घ)addr < ioremap_bot)
		vunmap((व्योम *)(PAGE_MASK & (अचिन्हित दीर्घ)addr));
पूर्ण
EXPORT_SYMBOL(iounmap);
