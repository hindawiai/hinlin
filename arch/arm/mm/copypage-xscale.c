<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/lib/copypage-xscale.S
 *
 *  Copyright (C) 1995-2005 Russell King
 *
 * This handles the mini data cache, as found on SA11x0 and XScale
 * processors.  When we copy a user page page, we map it in such a way
 * that accesses to this page will not touch the मुख्य data cache, but
 * will be cached in the mini data cache.  This prevents us thrashing
 * the मुख्य data cache on page faults.
 */
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>

#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/cacheflush.h>

#समावेश "mm.h"

#घोषणा minicache_pgprot __pgprot(L_PTE_PRESENT | L_PTE_YOUNG | \
				  L_PTE_MT_MINICACHE)

अटल DEFINE_RAW_SPINLOCK(minicache_lock);

/*
 * XScale mini-dcache optimised copy_user_highpage
 *
 * We flush the destination cache lines just beक्रमe we ग_लिखो the data पूर्णांकo the
 * corresponding address.  Since the Dcache is पढ़ो-allocate, this हटाओs the
 * Dcache aliasing issue.  The ग_लिखोs will be क्रमwarded to the ग_लिखो buffer,
 * and merged as appropriate.
 */
अटल व्योम mc_copy_user_page(व्योम *from, व्योम *to)
अणु
	पूर्णांक पंचांगp;

	/*
	 * Strangely enough, best perक्रमmance is achieved
	 * when prefetching destination as well.  (NP)
	 */
	यंत्र अस्थिर ("\
.arch xscale					\न\
	pld	[%0, #0]			\न\
	pld	[%0, #32]			\न\
	pld	[%1, #0]			\न\
	pld	[%1, #32]			\न\
1:	pld	[%0, #64]			\न\
	pld	[%0, #96]			\न\
	pld	[%1, #64]			\न\
	pld	[%1, #96]			\न\
2:	ldrd	r2, r3, [%0], #8		\न\
	ldrd	r4, r5, [%0], #8		\न\
	mov	ip, %1				\न\
	strd	r2, r3, [%1], #8		\न\
	ldrd	r2, r3, [%0], #8		\न\
	strd	r4, r5, [%1], #8		\न\
	ldrd	r4, r5, [%0], #8		\न\
	strd	r2, r3, [%1], #8		\न\
	strd	r4, r5, [%1], #8		\न\
	mcr	p15, 0, ip, c7, c10, 1		@ clean D line\न\
	ldrd	r2, r3, [%0], #8		\न\
	mcr	p15, 0, ip, c7, c6, 1		@ invalidate D line\न\
	ldrd	r4, r5, [%0], #8		\न\
	mov	ip, %1				\न\
	strd	r2, r3, [%1], #8		\न\
	ldrd	r2, r3, [%0], #8		\न\
	strd	r4, r5, [%1], #8		\न\
	ldrd	r4, r5, [%0], #8		\न\
	strd	r2, r3, [%1], #8		\न\
	strd	r4, r5, [%1], #8		\न\
	mcr	p15, 0, ip, c7, c10, 1		@ clean D line\न\
	subs	%2, %2, #1			\न\
	mcr	p15, 0, ip, c7, c6, 1		@ invalidate D line\न\
	bgt	1b				\न\
	beq	2b				"
	: "+&r" (from), "+&r" (to), "=&r" (पंचांगp)
	: "2" (PAGE_SIZE / 64 - 1)
	: "r2", "r3", "r4", "r5", "ip");
पूर्ण

व्योम xscale_mc_copy_user_highpage(काष्ठा page *to, काष्ठा page *from,
	अचिन्हित दीर्घ vaddr, काष्ठा vm_area_काष्ठा *vma)
अणु
	व्योम *kto = kmap_atomic(to);

	अगर (!test_and_set_bit(PG_dcache_clean, &from->flags))
		__flush_dcache_page(page_mapping_file(from), from);

	raw_spin_lock(&minicache_lock);

	set_top_pte(COPYPAGE_MINICACHE, mk_pte(from, minicache_pgprot));

	mc_copy_user_page((व्योम *)COPYPAGE_MINICACHE, kto);

	raw_spin_unlock(&minicache_lock);

	kunmap_atomic(kto);
पूर्ण

/*
 * XScale optimised clear_user_page
 */
व्योम
xscale_mc_clear_user_highpage(काष्ठा page *page, अचिन्हित दीर्घ vaddr)
अणु
	व्योम *ptr, *kaddr = kmap_atomic(page);
	यंत्र अस्थिर("\
.arch xscale					\न\
	mov	r1, %2				\न\
	mov	r2, #0				\न\
	mov	r3, #0				\न\
1:	mov	ip, %0				\न\
	strd	r2, r3, [%0], #8		\न\
	strd	r2, r3, [%0], #8		\न\
	strd	r2, r3, [%0], #8		\न\
	strd	r2, r3, [%0], #8		\न\
	mcr	p15, 0, ip, c7, c10, 1		@ clean D line\न\
	subs	r1, r1, #1			\न\
	mcr	p15, 0, ip, c7, c6, 1		@ invalidate D line\न\
	bne	1b"
	: "=r" (ptr)
	: "0" (kaddr), "I" (PAGE_SIZE / 32)
	: "r1", "r2", "r3", "ip");
	kunmap_atomic(kaddr);
पूर्ण

काष्ठा cpu_user_fns xscale_mc_user_fns __initdata = अणु
	.cpu_clear_user_highpage = xscale_mc_clear_user_highpage,
	.cpu_copy_user_highpage	= xscale_mc_copy_user_highpage,
पूर्ण;
