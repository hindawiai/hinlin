<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/lib/copypage-armv4mc.S
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
 * ARMv4 mini-dcache optimised copy_user_highpage
 *
 * We flush the destination cache lines just beक्रमe we ग_लिखो the data पूर्णांकo the
 * corresponding address.  Since the Dcache is पढ़ो-allocate, this हटाओs the
 * Dcache aliasing issue.  The ग_लिखोs will be क्रमwarded to the ग_लिखो buffer,
 * and merged as appropriate.
 *
 * Note: We rely on all ARMv4 processors implementing the "invalidate D line"
 * inकाष्ठाion.  If your processor करोes not supply this, you have to ग_लिखो your
 * own copy_user_highpage that करोes the right thing.
 */
अटल व्योम mc_copy_user_page(व्योम *from, व्योम *to)
अणु
	पूर्णांक पंचांगp;

	यंत्र अस्थिर ("\
	.syntax unअगरied\न\
	ldmia	%0!, अणुr2, r3, ip, lrपूर्ण		@ 4\न\
1:	mcr	p15, 0, %1, c7, c6, 1		@ 1   invalidate D line\न\
	sपंचांगia	%1!, अणुr2, r3, ip, lrपूर्ण		@ 4\न\
	ldmia	%0!, अणुr2, r3, ip, lrपूर्ण		@ 4+1\न\
	sपंचांगia	%1!, अणुr2, r3, ip, lrपूर्ण		@ 4\न\
	ldmia	%0!, अणुr2, r3, ip, lrपूर्ण		@ 4\न\
	mcr	p15, 0, %1, c7, c6, 1		@ 1   invalidate D line\न\
	sपंचांगia	%1!, अणुr2, r3, ip, lrपूर्ण		@ 4\न\
	ldmia	%0!, अणुr2, r3, ip, lrपूर्ण		@ 4\न\
	subs	%2, %2, #1			@ 1\न\
	sपंचांगia	%1!, अणुr2, r3, ip, lrपूर्ण		@ 4\न\
	ldmiane	%0!, अणुr2, r3, ip, lrपूर्ण		@ 4\न\
	bne	1b				@ "
	: "+&r" (from), "+&r" (to), "=&r" (पंचांगp)
	: "2" (PAGE_SIZE / 64)
	: "r2", "r3", "ip", "lr");
पूर्ण

व्योम v4_mc_copy_user_highpage(काष्ठा page *to, काष्ठा page *from,
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
 * ARMv4 optimised clear_user_page
 */
व्योम v4_mc_clear_user_highpage(काष्ठा page *page, अचिन्हित दीर्घ vaddr)
अणु
	व्योम *ptr, *kaddr = kmap_atomic(page);
	यंत्र अस्थिर("\
	mov	r1, %2				@ 1\न\
	mov	r2, #0				@ 1\न\
	mov	r3, #0				@ 1\न\
	mov	ip, #0				@ 1\न\
	mov	lr, #0				@ 1\न\
1:	mcr	p15, 0, %0, c7, c6, 1		@ 1   invalidate D line\न\
	sपंचांगia	%0!, अणुr2, r3, ip, lrपूर्ण		@ 4\न\
	sपंचांगia	%0!, अणुr2, r3, ip, lrपूर्ण		@ 4\न\
	mcr	p15, 0, %0, c7, c6, 1		@ 1   invalidate D line\न\
	sपंचांगia	%0!, अणुr2, r3, ip, lrपूर्ण		@ 4\न\
	sपंचांगia	%0!, अणुr2, r3, ip, lrपूर्ण		@ 4\न\
	subs	r1, r1, #1			@ 1\न\
	bne	1b				@ 1"
	: "=r" (ptr)
	: "0" (kaddr), "I" (PAGE_SIZE / 64)
	: "r1", "r2", "r3", "ip", "lr");
	kunmap_atomic(kaddr);
पूर्ण

काष्ठा cpu_user_fns v4_mc_user_fns __initdata = अणु
	.cpu_clear_user_highpage = v4_mc_clear_user_highpage,
	.cpu_copy_user_highpage	= v4_mc_copy_user_highpage,
पूर्ण;
