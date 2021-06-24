<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/lib/uaccess_with_स_नकल.c
 *
 *  Written by: Lennert Buytenhek and Nicolas Pitre
 *  Copyright (C) 2009 Marvell Semiconductor
 */

#समावेश <linux/kernel.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched.h>
#समावेश <linux/hardirq.h> /* क्रम in_atomic() */
#समावेश <linux/gfp.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/hugetlb.h>
#समावेश <यंत्र/current.h>
#समावेश <यंत्र/page.h>

अटल पूर्णांक
pin_page_क्रम_ग_लिखो(स्थिर व्योम __user *_addr, pte_t **ptep, spinlock_t **ptlp)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)_addr;
	pgd_t *pgd;
	p4d_t *p4d;
	pmd_t *pmd;
	pte_t *pte;
	pud_t *pud;
	spinlock_t *ptl;

	pgd = pgd_offset(current->mm, addr);
	अगर (unlikely(pgd_none(*pgd) || pgd_bad(*pgd)))
		वापस 0;

	p4d = p4d_offset(pgd, addr);
	अगर (unlikely(p4d_none(*p4d) || p4d_bad(*p4d)))
		वापस 0;

	pud = pud_offset(p4d, addr);
	अगर (unlikely(pud_none(*pud) || pud_bad(*pud)))
		वापस 0;

	pmd = pmd_offset(pud, addr);
	अगर (unlikely(pmd_none(*pmd)))
		वापस 0;

	/*
	 * A pmd can be bad अगर it refers to a HugeTLB or THP page.
	 *
	 * Both THP and HugeTLB pages have the same pmd layout
	 * and should not be manipulated by the pte functions.
	 *
	 * Lock the page table क्रम the destination and check
	 * to see that it's still huge and whether or not we will
	 * need to fault on ग_लिखो.
	 */
	अगर (unlikely(pmd_thp_or_huge(*pmd))) अणु
		ptl = &current->mm->page_table_lock;
		spin_lock(ptl);
		अगर (unlikely(!pmd_thp_or_huge(*pmd)
			|| pmd_hugewillfault(*pmd))) अणु
			spin_unlock(ptl);
			वापस 0;
		पूर्ण

		*ptep = शून्य;
		*ptlp = ptl;
		वापस 1;
	पूर्ण

	अगर (unlikely(pmd_bad(*pmd)))
		वापस 0;

	pte = pte_offset_map_lock(current->mm, pmd, addr, &ptl);
	अगर (unlikely(!pte_present(*pte) || !pte_young(*pte) ||
	    !pte_ग_लिखो(*pte) || !pte_dirty(*pte))) अणु
		pte_unmap_unlock(pte, ptl);
		वापस 0;
	पूर्ण

	*ptep = pte;
	*ptlp = ptl;

	वापस 1;
पूर्ण

अटल अचिन्हित दीर्घ noअंतरभूत
__copy_to_user_स_नकल(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	अचिन्हित दीर्घ ua_flags;
	पूर्णांक atomic;

	अगर (uaccess_kernel()) अणु
		स_नकल((व्योम *)to, from, n);
		वापस 0;
	पूर्ण

	/* the mmap semaphore is taken only अगर not in an atomic context */
	atomic = faulthandler_disabled();

	अगर (!atomic)
		mmap_पढ़ो_lock(current->mm);
	जबतक (n) अणु
		pte_t *pte;
		spinlock_t *ptl;
		पूर्णांक tocopy;

		जबतक (!pin_page_क्रम_ग_लिखो(to, &pte, &ptl)) अणु
			अगर (!atomic)
				mmap_पढ़ो_unlock(current->mm);
			अगर (__put_user(0, (अक्षर __user *)to))
				जाओ out;
			अगर (!atomic)
				mmap_पढ़ो_lock(current->mm);
		पूर्ण

		tocopy = (~(अचिन्हित दीर्घ)to & ~PAGE_MASK) + 1;
		अगर (tocopy > n)
			tocopy = n;

		ua_flags = uaccess_save_and_enable();
		स_नकल((व्योम *)to, from, tocopy);
		uaccess_restore(ua_flags);
		to += tocopy;
		from += tocopy;
		n -= tocopy;

		अगर (pte)
			pte_unmap_unlock(pte, ptl);
		अन्यथा
			spin_unlock(ptl);
	पूर्ण
	अगर (!atomic)
		mmap_पढ़ो_unlock(current->mm);

out:
	वापस n;
पूर्ण

अचिन्हित दीर्घ
arm_copy_to_user(व्योम __user *to, स्थिर व्योम *from, अचिन्हित दीर्घ n)
अणु
	/*
	 * This test is stubbed out of the मुख्य function above to keep
	 * the overhead क्रम small copies low by aव्योमing a large
	 * रेजिस्टर dump on the stack just to reload them right away.
	 * With frame poपूर्णांकer disabled, tail call optimization kicks in
	 * as well making this test almost invisible.
	 */
	अगर (n < 64) अणु
		अचिन्हित दीर्घ ua_flags = uaccess_save_and_enable();
		n = __copy_to_user_std(to, from, n);
		uaccess_restore(ua_flags);
	पूर्ण अन्यथा अणु
		n = __copy_to_user_स_नकल(uaccess_mask_range_ptr(to, n),
					  from, n);
	पूर्ण
	वापस n;
पूर्ण
	
अटल अचिन्हित दीर्घ noअंतरभूत
__clear_user_स_रखो(व्योम __user *addr, अचिन्हित दीर्घ n)
अणु
	अचिन्हित दीर्घ ua_flags;

	अगर (uaccess_kernel()) अणु
		स_रखो((व्योम *)addr, 0, n);
		वापस 0;
	पूर्ण

	mmap_पढ़ो_lock(current->mm);
	जबतक (n) अणु
		pte_t *pte;
		spinlock_t *ptl;
		पूर्णांक tocopy;

		जबतक (!pin_page_क्रम_ग_लिखो(addr, &pte, &ptl)) अणु
			mmap_पढ़ो_unlock(current->mm);
			अगर (__put_user(0, (अक्षर __user *)addr))
				जाओ out;
			mmap_पढ़ो_lock(current->mm);
		पूर्ण

		tocopy = (~(अचिन्हित दीर्घ)addr & ~PAGE_MASK) + 1;
		अगर (tocopy > n)
			tocopy = n;

		ua_flags = uaccess_save_and_enable();
		स_रखो((व्योम *)addr, 0, tocopy);
		uaccess_restore(ua_flags);
		addr += tocopy;
		n -= tocopy;

		अगर (pte)
			pte_unmap_unlock(pte, ptl);
		अन्यथा
			spin_unlock(ptl);
	पूर्ण
	mmap_पढ़ो_unlock(current->mm);

out:
	वापस n;
पूर्ण

अचिन्हित दीर्घ arm_clear_user(व्योम __user *addr, अचिन्हित दीर्घ n)
अणु
	/* See rational क्रम this in __copy_to_user() above. */
	अगर (n < 64) अणु
		अचिन्हित दीर्घ ua_flags = uaccess_save_and_enable();
		n = __clear_user_std(addr, n);
		uaccess_restore(ua_flags);
	पूर्ण अन्यथा अणु
		n = __clear_user_स_रखो(addr, n);
	पूर्ण
	वापस n;
पूर्ण

#अगर 0

/*
 * This code is disabled by शेष, but kept around in हाल the chosen
 * thresholds need to be revalidated.  Some overhead (small but still)
 * would be implied by a runसमय determined variable threshold, and
 * so far the measurement on concerned tarमाला_लो didn't show a worthजबतक
 * variation.
 *
 * Note that a fairly precise sched_घड़ी() implementation is needed
 * क्रम results to make some sense.
 */

#समावेश <linux/vदो_स्मृति.h>

अटल पूर्णांक __init test_माप_प्रकारreshold(व्योम)
अणु
	काष्ठा page *src_page, *dst_page;
	व्योम *user_ptr, *kernel_ptr;
	अचिन्हित दीर्घ दीर्घ t0, t1, t2;
	पूर्णांक size, ret;

	ret = -ENOMEM;
	src_page = alloc_page(GFP_KERNEL);
	अगर (!src_page)
		जाओ no_src;
	dst_page = alloc_page(GFP_KERNEL);
	अगर (!dst_page)
		जाओ no_dst;
	kernel_ptr = page_address(src_page);
	user_ptr = vmap(&dst_page, 1, VM_IOREMAP, __pgprot(__P010));
	अगर (!user_ptr)
		जाओ no_vmap;

	/* warm up the src page dcache */
	ret = __copy_to_user_स_नकल(user_ptr, kernel_ptr, PAGE_SIZE);

	क्रम (size = PAGE_SIZE; size >= 4; size /= 2) अणु
		t0 = sched_घड़ी();
		ret |= __copy_to_user_स_नकल(user_ptr, kernel_ptr, size);
		t1 = sched_घड़ी();
		ret |= __copy_to_user_std(user_ptr, kernel_ptr, size);
		t2 = sched_घड़ी();
		prपूर्णांकk("copy_to_user: %d %llu %llu\n", size, t1 - t0, t2 - t1);
	पूर्ण

	क्रम (size = PAGE_SIZE; size >= 4; size /= 2) अणु
		t0 = sched_घड़ी();
		ret |= __clear_user_स_रखो(user_ptr, size);
		t1 = sched_घड़ी();
		ret |= __clear_user_std(user_ptr, size);
		t2 = sched_घड़ी();
		prपूर्णांकk("clear_user: %d %llu %llu\n", size, t1 - t0, t2 - t1);
	पूर्ण

	अगर (ret)
		ret = -EFAULT;

	vunmap(user_ptr);
no_vmap:
	put_page(dst_page);
no_dst:
	put_page(src_page);
no_src:
	वापस ret;
पूर्ण

subsys_initcall(test_माप_प्रकारreshold);

#पूर्ण_अगर
