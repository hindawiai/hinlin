<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mm/copypage-xsc3.S
 *
 *  Copyright (C) 2004 Intel Corp.
 *
 * Adapted क्रम 3rd gen XScale core, no more mini-dcache
 * Author: Matt Gilbert (matthew.m.gilbert@पूर्णांकel.com)
 */
#समावेश <linux/init.h>
#समावेश <linux/highस्मृति.स>

/*
 * General note:
 *  We करोn't really want ग_लिखो-allocate cache behaviour क्रम these functions
 *  since that will just eat through 8K of the cache.
 */

/*
 * XSC3 optimised copy_user_highpage
 *
 * The source page may have some clean entries in the cache alपढ़ोy, but we
 * can safely ignore them - अवरोध_cow() will flush them out of the cache
 * अगर we eventually end up using our copied page.
 *
 */
अटल व्योम xsc3_mc_copy_user_page(व्योम *kto, स्थिर व्योम *kfrom)
अणु
	पूर्णांक पंचांगp;

	यंत्र अस्थिर ("\
	pld	[%1, #0]			\न\
	pld	[%1, #32]			\न\
1:	pld	[%1, #64]			\न\
	pld	[%1, #96]			\न\
						\न\
2:	ldrd	r2, r3, [%1], #8		\न\
	ldrd	r4, r5, [%1], #8		\न\
	mcr	p15, 0, %0, c7, c6, 1		@ invalidate\न\
	strd	r2, r3, [%0], #8		\न\
	ldrd	r2, r3, [%1], #8		\न\
	strd	r4, r5, [%0], #8		\न\
	ldrd	r4, r5, [%1], #8		\न\
	strd	r2, r3, [%0], #8		\न\
	strd	r4, r5, [%0], #8		\न\
	ldrd	r2, r3, [%1], #8		\न\
	ldrd	r4, r5, [%1], #8		\न\
	mcr	p15, 0, %0, c7, c6, 1		@ invalidate\न\
	strd	r2, r3, [%0], #8		\न\
	ldrd	r2, r3, [%1], #8		\न\
	subs	%2, %2, #1			\न\
	strd	r4, r5, [%0], #8		\न\
	ldrd	r4, r5, [%1], #8		\न\
	strd	r2, r3, [%0], #8		\न\
	strd	r4, r5, [%0], #8		\न\
	bgt	1b				\न\
	beq	2b				"
	: "+&r" (kto), "+&r" (kfrom), "=&r" (पंचांगp)
	: "2" (PAGE_SIZE / 64 - 1)
	: "r2", "r3", "r4", "r5");
पूर्ण

व्योम xsc3_mc_copy_user_highpage(काष्ठा page *to, काष्ठा page *from,
	अचिन्हित दीर्घ vaddr, काष्ठा vm_area_काष्ठा *vma)
अणु
	व्योम *kto, *kfrom;

	kto = kmap_atomic(to);
	kfrom = kmap_atomic(from);
	flush_cache_page(vma, vaddr, page_to_pfn(from));
	xsc3_mc_copy_user_page(kto, kfrom);
	kunmap_atomic(kfrom);
	kunmap_atomic(kto);
पूर्ण

/*
 * XScale optimised clear_user_page
 */
व्योम xsc3_mc_clear_user_highpage(काष्ठा page *page, अचिन्हित दीर्घ vaddr)
अणु
	व्योम *ptr, *kaddr = kmap_atomic(page);
	यंत्र अस्थिर ("\
	mov	r1, %2				\न\
	mov	r2, #0				\न\
	mov	r3, #0				\न\
1:	mcr	p15, 0, %0, c7, c6, 1		@ invalidate line\न\
	strd	r2, r3, [%0], #8		\न\
	strd	r2, r3, [%0], #8		\न\
	strd	r2, r3, [%0], #8		\न\
	strd	r2, r3, [%0], #8		\न\
	subs	r1, r1, #1			\न\
	bne	1b"
	: "=r" (ptr)
	: "0" (kaddr), "I" (PAGE_SIZE / 32)
	: "r1", "r2", "r3");
	kunmap_atomic(kaddr);
पूर्ण

काष्ठा cpu_user_fns xsc3_mc_user_fns __initdata = अणु
	.cpu_clear_user_highpage = xsc3_mc_clear_user_highpage,
	.cpu_copy_user_highpage	= xsc3_mc_copy_user_highpage,
पूर्ण;
