<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/m68k/mm/memory.c
 *
 *  Copyright (C) 1995  Hamish Macकरोnald
 */

#समावेश <linux/module.h>
#समावेश <linux/mm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/gfp.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/segment.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/machdep.h>


/* invalidate page in both caches */
अटल अंतरभूत व्योम clear040(अचिन्हित दीर्घ paddr)
अणु
	यंत्र अस्थिर (
		"nop\n\t"
		".chip 68040\n\t"
		"cinvp %%bc,(%0)\n\t"
		".chip 68k"
		: : "a" (paddr));
पूर्ण

/* invalidate page in i-cache */
अटल अंतरभूत व्योम cleari040(अचिन्हित दीर्घ paddr)
अणु
	यंत्र अस्थिर (
		"nop\n\t"
		".chip 68040\n\t"
		"cinvp %%ic,(%0)\n\t"
		".chip 68k"
		: : "a" (paddr));
पूर्ण

/* push page in both caches */
/* RZ: cpush %bc DOES invalidate %ic, regardless of DPI */
अटल अंतरभूत व्योम push040(अचिन्हित दीर्घ paddr)
अणु
	यंत्र अस्थिर (
		"nop\n\t"
		".chip 68040\n\t"
		"cpushp %%bc,(%0)\n\t"
		".chip 68k"
		: : "a" (paddr));
पूर्ण

/* push and invalidate page in both caches, must disable पूर्णांकs
 * to aव्योम invalidating valid data */
अटल अंतरभूत व्योम pushcl040(अचिन्हित दीर्घ paddr)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	push040(paddr);
	अगर (CPU_IS_060)
		clear040(paddr);
	local_irq_restore(flags);
पूर्ण

/*
 * 040: Hit every page containing an address in the range paddr..paddr+len-1.
 * (Low order bits of the ea of a CINVP/CPUSHP are "don't care"s).
 * Hit every page until there is a page or less to go. Hit the next page,
 * and the one after that अगर the range hits it.
 */
/* ++roman: A little bit more care is required here: The CINVP inकाष्ठाion
 * invalidates cache entries WITHOUT WRITING सूचीTY DATA BACK! So the beginning
 * and the end of the region must be treated dअगरferently अगर they are not
 * exactly at the beginning or end of a page boundary. Else, maybe too much
 * data becomes invalidated and thus lost क्रमever. CPUSHP करोes what we need:
 * it invalidates the page after pushing dirty data to memory. (Thanks to Jes
 * क्रम discovering the problem!)
 */
/* ... but on the '060, CPUSH doesn't invalidate (क्रम us, since we have set
 * the DPI bit in the CACR; would it cause problems with temporarily changing
 * this?). So we have to push first and then additionally to invalidate.
 */


/*
 * cache_clear() semantics: Clear any cache entries क्रम the area in question,
 * without writing back dirty entries first. This is useful अगर the data will
 * be overwritten anyway, e.g. by DMA to memory. The range is defined by a
 * _physical_ address.
 */

व्योम cache_clear (अचिन्हित दीर्घ paddr, पूर्णांक len)
अणु
    अगर (CPU_IS_COLDFIRE) अणु
	clear_cf_bcache(0, DCACHE_MAX_ADDR);
    पूर्ण अन्यथा अगर (CPU_IS_040_OR_060) अणु
	पूर्णांक पंचांगp;

	/*
	 * We need special treaपंचांगent क्रम the first page, in हाल it
	 * is not page-aligned. Page align the addresses to work
	 * around bug I17 in the 68060.
	 */
	अगर ((पंचांगp = -paddr & (PAGE_SIZE - 1))) अणु
	    pushcl040(paddr & PAGE_MASK);
	    अगर ((len -= पंचांगp) <= 0)
		वापस;
	    paddr += पंचांगp;
	पूर्ण
	पंचांगp = PAGE_SIZE;
	paddr &= PAGE_MASK;
	जबतक ((len -= पंचांगp) >= 0) अणु
	    clear040(paddr);
	    paddr += पंचांगp;
	पूर्ण
	अगर ((len += पंचांगp))
	    /* a page boundary माला_लो crossed at the end */
	    pushcl040(paddr);
    पूर्ण
    अन्यथा /* 68030 or 68020 */
	यंत्र अस्थिर ("movec %/cacr,%/d0\n\t"
		      "oriw %0,%/d0\n\t"
		      "movec %/d0,%/cacr"
		      : : "i" (FLUSH_I_AND_D)
		      : "d0");
#अगर_घोषित CONFIG_M68K_L2_CACHE
    अगर(mach_l2_flush)
	mach_l2_flush(0);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(cache_clear);


/*
 * cache_push() semantics: Write back any dirty cache data in the given area,
 * and invalidate the range in the inकाष्ठाion cache. It needs not (but may)
 * invalidate those entries also in the data cache. The range is defined by a
 * _physical_ address.
 */

व्योम cache_push (अचिन्हित दीर्घ paddr, पूर्णांक len)
अणु
    अगर (CPU_IS_COLDFIRE) अणु
	flush_cf_bcache(0, DCACHE_MAX_ADDR);
    पूर्ण अन्यथा अगर (CPU_IS_040_OR_060) अणु
	पूर्णांक पंचांगp = PAGE_SIZE;

	/*
         * on 68040 or 68060, push cache lines क्रम pages in the range;
	 * on the '040 this also invalidates the pushed lines, but not on
	 * the '060!
	 */
	len += paddr & (PAGE_SIZE - 1);

	/*
	 * Work around bug I17 in the 68060 affecting some inकाष्ठाion
	 * lines not being invalidated properly.
	 */
	paddr &= PAGE_MASK;

	करो अणु
	    push040(paddr);
	    paddr += पंचांगp;
	पूर्ण जबतक ((len -= पंचांगp) > 0);
    पूर्ण
    /*
     * 68030/68020 have no ग_लिखोback cache. On the other hand,
     * cache_push is actually a superset of cache_clear (the lines
     * get written back and invalidated), so we should make sure
     * to perक्रमm the corresponding actions. After all, this is getting
     * called in places where we've just loaded code, or whatever, so
     * flushing the icache is appropriate; flushing the dcache shouldn't
     * be required.
     */
    अन्यथा /* 68030 or 68020 */
	यंत्र अस्थिर ("movec %/cacr,%/d0\n\t"
		      "oriw %0,%/d0\n\t"
		      "movec %/d0,%/cacr"
		      : : "i" (FLUSH_I)
		      : "d0");
#अगर_घोषित CONFIG_M68K_L2_CACHE
    अगर(mach_l2_flush)
	mach_l2_flush(1);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL(cache_push);

