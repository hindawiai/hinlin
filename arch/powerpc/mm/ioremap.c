<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <यंत्र/io-workarounds.h>

अचिन्हित दीर्घ ioremap_bot;
EXPORT_SYMBOL(ioremap_bot);

व्योम __iomem *ioremap(phys_addr_t addr, अचिन्हित दीर्घ size)
अणु
	pgprot_t prot = pgprot_noncached(PAGE_KERNEL);
	व्योम *caller = __builtin_वापस_address(0);

	अगर (iowa_is_active())
		वापस iowa_ioremap(addr, size, prot, caller);
	वापस __ioremap_caller(addr, size, prot, caller);
पूर्ण
EXPORT_SYMBOL(ioremap);

व्योम __iomem *ioremap_wc(phys_addr_t addr, अचिन्हित दीर्घ size)
अणु
	pgprot_t prot = pgprot_noncached_wc(PAGE_KERNEL);
	व्योम *caller = __builtin_वापस_address(0);

	अगर (iowa_is_active())
		वापस iowa_ioremap(addr, size, prot, caller);
	वापस __ioremap_caller(addr, size, prot, caller);
पूर्ण
EXPORT_SYMBOL(ioremap_wc);

व्योम __iomem *ioremap_coherent(phys_addr_t addr, अचिन्हित दीर्घ size)
अणु
	pgprot_t prot = pgprot_cached(PAGE_KERNEL);
	व्योम *caller = __builtin_वापस_address(0);

	अगर (iowa_is_active())
		वापस iowa_ioremap(addr, size, prot, caller);
	वापस __ioremap_caller(addr, size, prot, caller);
पूर्ण

व्योम __iomem *ioremap_prot(phys_addr_t addr, अचिन्हित दीर्घ size, अचिन्हित दीर्घ flags)
अणु
	pte_t pte = __pte(flags);
	व्योम *caller = __builtin_वापस_address(0);

	/* ग_लिखोable implies dirty क्रम kernel addresses */
	अगर (pte_ग_लिखो(pte))
		pte = pte_सूची_गढ़ोty(pte);

	/* we करोn't want to let _PAGE_USER and _PAGE_EXEC leak out */
	pte = pte_exprotect(pte);
	pte = pte_mkprivileged(pte);

	अगर (iowa_is_active())
		वापस iowa_ioremap(addr, size, pte_pgprot(pte), caller);
	वापस __ioremap_caller(addr, size, pte_pgprot(pte), caller);
पूर्ण
EXPORT_SYMBOL(ioremap_prot);

पूर्णांक early_ioremap_range(अचिन्हित दीर्घ ea, phys_addr_t pa,
			अचिन्हित दीर्घ size, pgprot_t prot)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < size; i += PAGE_SIZE) अणु
		पूर्णांक err = map_kernel_page(ea + i, pa + i, prot);

		अगर (WARN_ON_ONCE(err))  /* Should clean up */
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम __iomem *करो_ioremap(phys_addr_t pa, phys_addr_t offset, अचिन्हित दीर्घ size,
			 pgprot_t prot, व्योम *caller)
अणु
	काष्ठा vm_काष्ठा *area;
	पूर्णांक ret;
	अचिन्हित दीर्घ va;

	area = __get_vm_area_caller(size, VM_IOREMAP, IOREMAP_START, IOREMAP_END, caller);
	अगर (area == शून्य)
		वापस शून्य;

	area->phys_addr = pa;
	va = (अचिन्हित दीर्घ)area->addr;

	ret = ioremap_page_range(va, va + size, pa, prot);
	अगर (!ret)
		वापस (व्योम __iomem *)area->addr + offset;

	vunmap_range(va, va + size);
	मुक्त_vm_area(area);

	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_ZONE_DEVICE
/*
 * Override the generic version in mm/memremap.c.
 *
 * With hash translation, the direct-map range is mapped with just one
 * page size selected by htab_init_page_sizes(). Consult
 * mmu_psize_defs[] to determine the minimum page size alignment.
*/
अचिन्हित दीर्घ memremap_compat_align(व्योम)
अणु
	अचिन्हित पूर्णांक shअगरt = mmu_psize_defs[mmu_linear_psize].shअगरt;

	अगर (radix_enabled())
		वापस SUBSECTION_SIZE;
	वापस max(SUBSECTION_SIZE, 1UL << shअगरt);

पूर्ण
EXPORT_SYMBOL_GPL(memremap_compat_align);
#पूर्ण_अगर
