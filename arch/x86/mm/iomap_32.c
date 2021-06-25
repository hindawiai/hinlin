<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright तऊ 2008 Ingo Molnar
 */

#समावेश <यंत्र/iomap.h>
#समावेश <यंत्र/memtype.h>
#समावेश <linux/export.h>
#समावेश <linux/highस्मृति.स>

अटल पूर्णांक is_io_mapping_possible(resource_माप_प्रकार base, अचिन्हित दीर्घ size)
अणु
#अगर !defined(CONFIG_X86_PAE) && defined(CONFIG_PHYS_ADDR_T_64BIT)
	/* There is no way to map greater than 1 << 32 address without PAE */
	अगर (base + size > 0x100000000ULL)
		वापस 0;
#पूर्ण_अगर
	वापस 1;
पूर्ण

पूर्णांक iomap_create_wc(resource_माप_प्रकार base, अचिन्हित दीर्घ size, pgprot_t *prot)
अणु
	क्रमागत page_cache_mode pcm = _PAGE_CACHE_MODE_WC;
	पूर्णांक ret;

	अगर (!is_io_mapping_possible(base, size))
		वापस -EINVAL;

	ret = memtype_reserve_io(base, base + size, &pcm);
	अगर (ret)
		वापस ret;

	*prot = __pgprot(__PAGE_KERNEL | cachemode2protval(pcm));
	/* Filter out unsupported __PAGE_KERNEL* bits: */
	pgprot_val(*prot) &= __शेष_kernel_pte_mask;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(iomap_create_wc);

व्योम iomap_मुक्त(resource_माप_प्रकार base, अचिन्हित दीर्घ size)
अणु
	memtype_मुक्त_io(base, base + size);
पूर्ण
EXPORT_SYMBOL_GPL(iomap_मुक्त);

व्योम __iomem *__iomap_local_pfn_prot(अचिन्हित दीर्घ pfn, pgprot_t prot)
अणु
	/*
	 * For non-PAT प्रणालीs, translate non-WB request to UC- just in
	 * हाल the caller set the PWT bit to prot directly without using
	 * pgprot_ग_लिखोcombine(). UC- translates to uncached अगर the MTRR
	 * is UC or WC. UC- माला_लो the real पूर्णांकention, of the user, which is
	 * "WC if the MTRR is WC, UC if you can't do that."
	 */
	अगर (!pat_enabled() && pgprot2cachemode(prot) != _PAGE_CACHE_MODE_WB)
		prot = __pgprot(__PAGE_KERNEL |
				cachemode2protval(_PAGE_CACHE_MODE_UC_MINUS));

	/* Filter out unsupported __PAGE_KERNEL* bits: */
	pgprot_val(prot) &= __शेष_kernel_pte_mask;

	वापस (व्योम __क्रमce __iomem *)__kmap_local_pfn_prot(pfn, prot);
पूर्ण
EXPORT_SYMBOL_GPL(__iomap_local_pfn_prot);
