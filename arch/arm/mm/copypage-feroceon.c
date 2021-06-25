<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mm/copypage-feroceon.S
 *
 *  Copyright (C) 2008 Marvell Semiconductors
 *
 * This handles copy_user_highpage and clear_user_page on Feroceon
 * more optimally than the generic implementations.
 */
#समावेश <linux/init.h>
#समावेश <linux/highस्मृति.स>

अटल व्योम feroceon_copy_user_page(व्योम *kto, स्थिर व्योम *kfrom)
अणु
	पूर्णांक पंचांगp;

	यंत्र अस्थिर ("\
1:	ldmia	%1!, अणुr2 - r7, ip, lrपूर्ण		\न\
	pld	[%1, #0]			\न\
	pld	[%1, #32]			\न\
	pld	[%1, #64]			\न\
	pld	[%1, #96]			\न\
	pld	[%1, #128]			\न\
	pld	[%1, #160]			\न\
	pld	[%1, #192]			\न\
	sपंचांगia	%0, अणुr2 - r7, ip, lrपूर्ण		\न\
	ldmia	%1!, अणुr2 - r7, ip, lrपूर्ण		\न\
	mcr	p15, 0, %0, c7, c14, 1		@ clean and invalidate D line\न\
	add	%0, %0, #32			\न\
	sपंचांगia	%0, अणुr2 - r7, ip, lrपूर्ण		\न\
	ldmia	%1!, अणुr2 - r7, ip, lrपूर्ण		\न\
	mcr	p15, 0, %0, c7, c14, 1		@ clean and invalidate D line\न\
	add	%0, %0, #32			\न\
	sपंचांगia	%0, अणुr2 - r7, ip, lrपूर्ण		\न\
	ldmia	%1!, अणुr2 - r7, ip, lrपूर्ण		\न\
	mcr	p15, 0, %0, c7, c14, 1		@ clean and invalidate D line\न\
	add	%0, %0, #32			\न\
	sपंचांगia	%0, अणुr2 - r7, ip, lrपूर्ण		\न\
	ldmia	%1!, अणुr2 - r7, ip, lrपूर्ण		\न\
	mcr	p15, 0, %0, c7, c14, 1		@ clean and invalidate D line\न\
	add	%0, %0, #32			\न\
	sपंचांगia	%0, अणुr2 - r7, ip, lrपूर्ण		\न\
	ldmia	%1!, अणुr2 - r7, ip, lrपूर्ण		\न\
	mcr	p15, 0, %0, c7, c14, 1		@ clean and invalidate D line\न\
	add	%0, %0, #32			\न\
	sपंचांगia	%0, अणुr2 - r7, ip, lrपूर्ण		\न\
	ldmia	%1!, अणुr2 - r7, ip, lrपूर्ण		\न\
	mcr	p15, 0, %0, c7, c14, 1		@ clean and invalidate D line\न\
	add	%0, %0, #32			\न\
	sपंचांगia	%0, अणुr2 - r7, ip, lrपूर्ण		\न\
	ldmia	%1!, अणुr2 - r7, ip, lrपूर्ण		\न\
	mcr	p15, 0, %0, c7, c14, 1		@ clean and invalidate D line\न\
	add	%0, %0, #32			\न\
	sपंचांगia	%0, अणुr2 - r7, ip, lrपूर्ण		\न\
	subs	%2, %2, #(32 * 8)		\न\
	mcr	p15, 0, %0, c7, c14, 1		@ clean and invalidate D line\न\
	add	%0, %0, #32			\न\
	bne	1b				\न\
	mcr	p15, 0, %2, c7, c10, 4		@ drain WB"
	: "+&r" (kto), "+&r" (kfrom), "=&r" (पंचांगp)
	: "2" (PAGE_SIZE)
	: "r2", "r3", "r4", "r5", "r6", "r7", "ip", "lr");
पूर्ण

व्योम feroceon_copy_user_highpage(काष्ठा page *to, काष्ठा page *from,
	अचिन्हित दीर्घ vaddr, काष्ठा vm_area_काष्ठा *vma)
अणु
	व्योम *kto, *kfrom;

	kto = kmap_atomic(to);
	kfrom = kmap_atomic(from);
	flush_cache_page(vma, vaddr, page_to_pfn(from));
	feroceon_copy_user_page(kto, kfrom);
	kunmap_atomic(kfrom);
	kunmap_atomic(kto);
पूर्ण

व्योम feroceon_clear_user_highpage(काष्ठा page *page, अचिन्हित दीर्घ vaddr)
अणु
	व्योम *ptr, *kaddr = kmap_atomic(page);
	यंत्र अस्थिर ("\
	mov	r1, %2				\न\
	mov	r2, #0				\न\
	mov	r3, #0				\न\
	mov	r4, #0				\न\
	mov	r5, #0				\न\
	mov	r6, #0				\न\
	mov	r7, #0				\न\
	mov	ip, #0				\न\
	mov	lr, #0				\न\
1:	sपंचांगia	%0, अणुr2-r7, ip, lrपूर्ण		\न\
	subs	r1, r1, #1			\न\
	mcr	p15, 0, %0, c7, c14, 1		@ clean and invalidate D line\न\
	add	%0, %0, #32			\न\
	bne	1b				\न\
	mcr	p15, 0, r1, c7, c10, 4		@ drain WB"
	: "=r" (ptr)
	: "0" (kaddr), "I" (PAGE_SIZE / 32)
	: "r1", "r2", "r3", "r4", "r5", "r6", "r7", "ip", "lr");
	kunmap_atomic(kaddr);
पूर्ण

काष्ठा cpu_user_fns feroceon_user_fns __initdata = अणु
	.cpu_clear_user_highpage = feroceon_clear_user_highpage,
	.cpu_copy_user_highpage	= feroceon_copy_user_highpage,
पूर्ण;

