<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mm/copypage-v4wb.c
 *
 *  Copyright (C) 1995-1999 Russell King
 */
#समावेश <linux/init.h>
#समावेश <linux/highस्मृति.स>

/*
 * ARMv4 optimised copy_user_highpage
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
अटल व्योम v4wb_copy_user_page(व्योम *kto, स्थिर व्योम *kfrom)
अणु
	पूर्णांक पंचांगp;

	यंत्र अस्थिर ("\
	.syntax unअगरied\न\
	ldmia	%1!, अणुr3, r4, ip, lrपूर्ण		@ 4\न\
1:	mcr	p15, 0, %0, c7, c6, 1		@ 1   invalidate D line\न\
	sपंचांगia	%0!, अणुr3, r4, ip, lrपूर्ण		@ 4\न\
	ldmia	%1!, अणुr3, r4, ip, lrपूर्ण		@ 4+1\न\
	sपंचांगia	%0!, अणुr3, r4, ip, lrपूर्ण		@ 4\न\
	ldmia	%1!, अणुr3, r4, ip, lrपूर्ण		@ 4\न\
	mcr	p15, 0, %0, c7, c6, 1		@ 1   invalidate D line\न\
	sपंचांगia	%0!, अणुr3, r4, ip, lrपूर्ण		@ 4\न\
	ldmia	%1!, अणुr3, r4, ip, lrपूर्ण		@ 4\न\
	subs	%2, %2, #1			@ 1\न\
	sपंचांगia	%0!, अणुr3, r4, ip, lrपूर्ण		@ 4\न\
	ldmiane	%1!, अणुr3, r4, ip, lrपूर्ण		@ 4\न\
	bne	1b				@ 1\न\
	mcr	p15, 0, %1, c7, c10, 4		@ 1   drain WB"
	: "+&r" (kto), "+&r" (kfrom), "=&r" (पंचांगp)
	: "2" (PAGE_SIZE / 64)
	: "r3", "r4", "ip", "lr");
पूर्ण

व्योम v4wb_copy_user_highpage(काष्ठा page *to, काष्ठा page *from,
	अचिन्हित दीर्घ vaddr, काष्ठा vm_area_काष्ठा *vma)
अणु
	व्योम *kto, *kfrom;

	kto = kmap_atomic(to);
	kfrom = kmap_atomic(from);
	flush_cache_page(vma, vaddr, page_to_pfn(from));
	v4wb_copy_user_page(kto, kfrom);
	kunmap_atomic(kfrom);
	kunmap_atomic(kto);
पूर्ण

/*
 * ARMv4 optimised clear_user_page
 *
 * Same story as above.
 */
व्योम v4wb_clear_user_highpage(काष्ठा page *page, अचिन्हित दीर्घ vaddr)
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
	bne	1b				@ 1\न\
	mcr	p15, 0, r1, c7, c10, 4		@ 1   drain WB"
	: "=r" (ptr)
	: "0" (kaddr), "I" (PAGE_SIZE / 64)
	: "r1", "r2", "r3", "ip", "lr");
	kunmap_atomic(kaddr);
पूर्ण

काष्ठा cpu_user_fns v4wb_user_fns __initdata = अणु
	.cpu_clear_user_highpage = v4wb_clear_user_highpage,
	.cpu_copy_user_highpage	= v4wb_copy_user_highpage,
पूर्ण;
