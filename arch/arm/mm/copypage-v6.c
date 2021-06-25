<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mm/copypage-v6.c
 *
 *  Copyright (C) 2002 Deep Blue Solutions Ltd, All Rights Reserved.
 */
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/pagemap.h>

#समावेश <यंत्र/shmparam.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cachetype.h>

#समावेश "mm.h"

#अगर SHMLBA > 16384
#त्रुटि FIX ME
#पूर्ण_अगर

अटल DEFINE_RAW_SPINLOCK(v6_lock);

/*
 * Copy the user page.  No aliasing to deal with so we can just
 * attack the kernel's existing mapping of these pages.
 */
अटल व्योम v6_copy_user_highpage_nonaliasing(काष्ठा page *to,
	काष्ठा page *from, अचिन्हित दीर्घ vaddr, काष्ठा vm_area_काष्ठा *vma)
अणु
	व्योम *kto, *kfrom;

	kfrom = kmap_atomic(from);
	kto = kmap_atomic(to);
	copy_page(kto, kfrom);
	kunmap_atomic(kto);
	kunmap_atomic(kfrom);
पूर्ण

/*
 * Clear the user page.  No aliasing to deal with so we can just
 * attack the kernel's existing mapping of this page.
 */
अटल व्योम v6_clear_user_highpage_nonaliasing(काष्ठा page *page, अचिन्हित दीर्घ vaddr)
अणु
	व्योम *kaddr = kmap_atomic(page);
	clear_page(kaddr);
	kunmap_atomic(kaddr);
पूर्ण

/*
 * Discard data in the kernel mapping क्रम the new page.
 * FIXME: needs this MCRR to be supported.
 */
अटल व्योम discard_old_kernel_data(व्योम *kto)
अणु
	__यंत्र__("mcrr	p15, 0, %1, %0, c6	@ 0xec401f06"
	   :
	   : "r" (kto),
	     "r" ((अचिन्हित दीर्घ)kto + PAGE_SIZE - 1)
	   : "cc");
पूर्ण

/*
 * Copy the page, taking account of the cache colour.
 */
अटल व्योम v6_copy_user_highpage_aliasing(काष्ठा page *to,
	काष्ठा page *from, अचिन्हित दीर्घ vaddr, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित पूर्णांक offset = CACHE_COLOUR(vaddr);
	अचिन्हित दीर्घ kfrom, kto;

	अगर (!test_and_set_bit(PG_dcache_clean, &from->flags))
		__flush_dcache_page(page_mapping_file(from), from);

	/* FIXME: not highmem safe */
	discard_old_kernel_data(page_address(to));

	/*
	 * Now copy the page using the same cache colour as the
	 * pages ultimate destination.
	 */
	raw_spin_lock(&v6_lock);

	kfrom = COPYPAGE_V6_FROM + (offset << PAGE_SHIFT);
	kto   = COPYPAGE_V6_TO + (offset << PAGE_SHIFT);

	set_top_pte(kfrom, mk_pte(from, PAGE_KERNEL));
	set_top_pte(kto, mk_pte(to, PAGE_KERNEL));

	copy_page((व्योम *)kto, (व्योम *)kfrom);

	raw_spin_unlock(&v6_lock);
पूर्ण

/*
 * Clear the user page.  We need to deal with the aliasing issues,
 * so remap the kernel page पूर्णांकo the same cache colour as the user
 * page.
 */
अटल व्योम v6_clear_user_highpage_aliasing(काष्ठा page *page, अचिन्हित दीर्घ vaddr)
अणु
	अचिन्हित दीर्घ to = COPYPAGE_V6_TO + (CACHE_COLOUR(vaddr) << PAGE_SHIFT);

	/* FIXME: not highmem safe */
	discard_old_kernel_data(page_address(page));

	/*
	 * Now clear the page using the same cache colour as
	 * the pages ultimate destination.
	 */
	raw_spin_lock(&v6_lock);

	set_top_pte(to, mk_pte(page, PAGE_KERNEL));
	clear_page((व्योम *)to);

	raw_spin_unlock(&v6_lock);
पूर्ण

काष्ठा cpu_user_fns v6_user_fns __initdata = अणु
	.cpu_clear_user_highpage = v6_clear_user_highpage_nonaliasing,
	.cpu_copy_user_highpage	= v6_copy_user_highpage_nonaliasing,
पूर्ण;

अटल पूर्णांक __init v6_userpage_init(व्योम)
अणु
	अगर (cache_is_vipt_aliasing()) अणु
		cpu_user.cpu_clear_user_highpage = v6_clear_user_highpage_aliasing;
		cpu_user.cpu_copy_user_highpage = v6_copy_user_highpage_aliasing;
	पूर्ण

	वापस 0;
पूर्ण

core_initcall(v6_userpage_init);
