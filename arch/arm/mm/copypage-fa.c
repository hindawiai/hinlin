<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/lib/copypage-fa.S
 *
 *  Copyright (C) 2005 Faraday Corp.
 *  Copyright (C) 2008-2009 Paulius Zaleckas <paulius.zaleckas@teltonika.lt>
 *
 * Based on copypage-v4wb.S:
 *  Copyright (C) 1995-1999 Russell King
 */
#समावेश <linux/init.h>
#समावेश <linux/highस्मृति.स>

/*
 * Faraday optimised copy_user_page
 */
अटल व्योम fa_copy_user_page(व्योम *kto, स्थिर व्योम *kfrom)
अणु
	पूर्णांक पंचांगp;

	यंत्र अस्थिर ("\
1:	ldmia	%1!, अणुr3, r4, ip, lrपूर्ण		@ 4\न\
	sपंचांगia	%0, अणुr3, r4, ip, lrपूर्ण		@ 4\न\
	mcr	p15, 0, %0, c7, c14, 1		@ 1   clean and invalidate D line\न\
	add	%0, %0, #16			@ 1\न\
	ldmia	%1!, अणुr3, r4, ip, lrपूर्ण		@ 4\न\
	sपंचांगia	%0, अणुr3, r4, ip, lrपूर्ण		@ 4\न\
	mcr	p15, 0, %0, c7, c14, 1		@ 1   clean and invalidate D line\न\
	add	%0, %0, #16			@ 1\न\
	subs	%2, %2, #1			@ 1\न\
	bne	1b				@ 1\न\
	mcr	p15, 0, %2, c7, c10, 4		@ 1   drain WB"
	: "+&r" (kto), "+&r" (kfrom), "=&r" (पंचांगp)
	: "2" (PAGE_SIZE / 32)
	: "r3", "r4", "ip", "lr");
पूर्ण

व्योम fa_copy_user_highpage(काष्ठा page *to, काष्ठा page *from,
	अचिन्हित दीर्घ vaddr, काष्ठा vm_area_काष्ठा *vma)
अणु
	व्योम *kto, *kfrom;

	kto = kmap_atomic(to);
	kfrom = kmap_atomic(from);
	fa_copy_user_page(kto, kfrom);
	kunmap_atomic(kfrom);
	kunmap_atomic(kto);
पूर्ण

/*
 * Faraday optimised clear_user_page
 *
 * Same story as above.
 */
व्योम fa_clear_user_highpage(काष्ठा page *page, अचिन्हित दीर्घ vaddr)
अणु
	व्योम *ptr, *kaddr = kmap_atomic(page);
	यंत्र अस्थिर("\
	mov	r1, %2				@ 1\न\
	mov	r2, #0				@ 1\न\
	mov	r3, #0				@ 1\न\
	mov	ip, #0				@ 1\न\
	mov	lr, #0				@ 1\न\
1:	sपंचांगia	%0, अणुr2, r3, ip, lrपूर्ण		@ 4\न\
	mcr	p15, 0, %0, c7, c14, 1		@ 1   clean and invalidate D line\न\
	add	%0, %0, #16			@ 1\न\
	sपंचांगia	%0, अणुr2, r3, ip, lrपूर्ण		@ 4\न\
	mcr	p15, 0, %0, c7, c14, 1		@ 1   clean and invalidate D line\न\
	add	%0, %0, #16			@ 1\न\
	subs	r1, r1, #1			@ 1\न\
	bne	1b				@ 1\न\
	mcr	p15, 0, r1, c7, c10, 4		@ 1   drain WB"
	: "=r" (ptr)
	: "0" (kaddr), "I" (PAGE_SIZE / 32)
	: "r1", "r2", "r3", "ip", "lr");
	kunmap_atomic(kaddr);
पूर्ण

काष्ठा cpu_user_fns fa_user_fns __initdata = अणु
	.cpu_clear_user_highpage = fa_clear_user_highpage,
	.cpu_copy_user_highpage	= fa_copy_user_highpage,
पूर्ण;
