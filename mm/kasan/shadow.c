<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file contains KASAN runसमय code that manages shaकरोw memory क्रम
 * generic and software tag-based KASAN modes.
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 * Author: Andrey Ryabinin <ryabinin.a.a@gmail.com>
 *
 * Some code borrowed from https://github.com/xairy/kasan-prototype by
 *        Andrey Konovalov <andreyknvl@gmail.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/kasan.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kfence.h>
#समावेश <linux/kmemleak.h>
#समावेश <linux/memory.h>
#समावेश <linux/mm.h>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/tlbflush.h>

#समावेश "kasan.h"

bool __kasan_check_पढ़ो(स्थिर अस्थिर व्योम *p, अचिन्हित पूर्णांक size)
अणु
	वापस kasan_check_range((अचिन्हित दीर्घ)p, size, false, _RET_IP_);
पूर्ण
EXPORT_SYMBOL(__kasan_check_पढ़ो);

bool __kasan_check_ग_लिखो(स्थिर अस्थिर व्योम *p, अचिन्हित पूर्णांक size)
अणु
	वापस kasan_check_range((अचिन्हित दीर्घ)p, size, true, _RET_IP_);
पूर्ण
EXPORT_SYMBOL(__kasan_check_ग_लिखो);

#अघोषित स_रखो
व्योम *स_रखो(व्योम *addr, पूर्णांक c, माप_प्रकार len)
अणु
	अगर (!kasan_check_range((अचिन्हित दीर्घ)addr, len, true, _RET_IP_))
		वापस शून्य;

	वापस __स_रखो(addr, c, len);
पूर्ण

#अगर_घोषित __HAVE_ARCH_MEMMOVE
#अघोषित स_हटाओ
व्योम *स_हटाओ(व्योम *dest, स्थिर व्योम *src, माप_प्रकार len)
अणु
	अगर (!kasan_check_range((अचिन्हित दीर्घ)src, len, false, _RET_IP_) ||
	    !kasan_check_range((अचिन्हित दीर्घ)dest, len, true, _RET_IP_))
		वापस शून्य;

	वापस __स_हटाओ(dest, src, len);
पूर्ण
#पूर्ण_अगर

#अघोषित स_नकल
व्योम *स_नकल(व्योम *dest, स्थिर व्योम *src, माप_प्रकार len)
अणु
	अगर (!kasan_check_range((अचिन्हित दीर्घ)src, len, false, _RET_IP_) ||
	    !kasan_check_range((अचिन्हित दीर्घ)dest, len, true, _RET_IP_))
		वापस शून्य;

	वापस __स_नकल(dest, src, len);
पूर्ण

व्योम kasan_poison(स्थिर व्योम *addr, माप_प्रकार size, u8 value, bool init)
अणु
	व्योम *shaकरोw_start, *shaकरोw_end;

	/*
	 * Perक्रमm shaकरोw offset calculation based on untagged address, as
	 * some of the callers (e.g. kasan_poison_object_data) pass tagged
	 * addresses to this function.
	 */
	addr = kasan_reset_tag(addr);

	/* Skip KFENCE memory अगर called explicitly outside of sl*b. */
	अगर (is_kfence_address(addr))
		वापस;

	अगर (WARN_ON((अचिन्हित दीर्घ)addr & KASAN_GRANULE_MASK))
		वापस;
	अगर (WARN_ON(size & KASAN_GRANULE_MASK))
		वापस;

	shaकरोw_start = kasan_mem_to_shaकरोw(addr);
	shaकरोw_end = kasan_mem_to_shaकरोw(addr + size);

	__स_रखो(shaकरोw_start, value, shaकरोw_end - shaकरोw_start);
पूर्ण
EXPORT_SYMBOL(kasan_poison);

#अगर_घोषित CONFIG_KASAN_GENERIC
व्योम kasan_poison_last_granule(स्थिर व्योम *addr, माप_प्रकार size)
अणु
	अगर (size & KASAN_GRANULE_MASK) अणु
		u8 *shaकरोw = (u8 *)kasan_mem_to_shaकरोw(addr + size);
		*shaकरोw = size & KASAN_GRANULE_MASK;
	पूर्ण
पूर्ण
#पूर्ण_अगर

व्योम kasan_unpoison(स्थिर व्योम *addr, माप_प्रकार size, bool init)
अणु
	u8 tag = get_tag(addr);

	/*
	 * Perक्रमm shaकरोw offset calculation based on untagged address, as
	 * some of the callers (e.g. kasan_unpoison_object_data) pass tagged
	 * addresses to this function.
	 */
	addr = kasan_reset_tag(addr);

	/*
	 * Skip KFENCE memory अगर called explicitly outside of sl*b. Also note
	 * that calls to ksize(), where size is not a multiple of machine-word
	 * size, would otherwise poison the invalid portion of the word.
	 */
	अगर (is_kfence_address(addr))
		वापस;

	अगर (WARN_ON((अचिन्हित दीर्घ)addr & KASAN_GRANULE_MASK))
		वापस;

	/* Unpoison all granules that cover the object. */
	kasan_poison(addr, round_up(size, KASAN_GRANULE_SIZE), tag, false);

	/* Partially poison the last granule क्रम the generic mode. */
	अगर (IS_ENABLED(CONFIG_KASAN_GENERIC))
		kasan_poison_last_granule(addr, size);
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
अटल bool shaकरोw_mapped(अचिन्हित दीर्घ addr)
अणु
	pgd_t *pgd = pgd_offset_k(addr);
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	अगर (pgd_none(*pgd))
		वापस false;
	p4d = p4d_offset(pgd, addr);
	अगर (p4d_none(*p4d))
		वापस false;
	pud = pud_offset(p4d, addr);
	अगर (pud_none(*pud))
		वापस false;

	/*
	 * We can't use pud_large() or pud_huge(), the first one is
	 * arch-specअगरic, the last one depends on HUGETLB_PAGE.  So let's abuse
	 * pud_bad(), अगर pud is bad then it's bad because it's huge.
	 */
	अगर (pud_bad(*pud))
		वापस true;
	pmd = pmd_offset(pud, addr);
	अगर (pmd_none(*pmd))
		वापस false;

	अगर (pmd_bad(*pmd))
		वापस true;
	pte = pte_offset_kernel(pmd, addr);
	वापस !pte_none(*pte);
पूर्ण

अटल पूर्णांक __meminit kasan_mem_notअगरier(काष्ठा notअगरier_block *nb,
			अचिन्हित दीर्घ action, व्योम *data)
अणु
	काष्ठा memory_notअगरy *mem_data = data;
	अचिन्हित दीर्घ nr_shaकरोw_pages, start_kaddr, shaकरोw_start;
	अचिन्हित दीर्घ shaकरोw_end, shaकरोw_size;

	nr_shaकरोw_pages = mem_data->nr_pages >> KASAN_SHADOW_SCALE_SHIFT;
	start_kaddr = (अचिन्हित दीर्घ)pfn_to_kaddr(mem_data->start_pfn);
	shaकरोw_start = (अचिन्हित दीर्घ)kasan_mem_to_shaकरोw((व्योम *)start_kaddr);
	shaकरोw_size = nr_shaकरोw_pages << PAGE_SHIFT;
	shaकरोw_end = shaकरोw_start + shaकरोw_size;

	अगर (WARN_ON(mem_data->nr_pages % KASAN_GRANULE_SIZE) ||
		WARN_ON(start_kaddr % KASAN_MEMORY_PER_SHADOW_PAGE))
		वापस NOTIFY_BAD;

	चयन (action) अणु
	हाल MEM_GOING_ONLINE: अणु
		व्योम *ret;

		/*
		 * If shaकरोw is mapped alपढ़ोy than it must have been mapped
		 * during the boot. This could happen अगर we onlining previously
		 * offlined memory.
		 */
		अगर (shaकरोw_mapped(shaकरोw_start))
			वापस NOTIFY_OK;

		ret = __vदो_स्मृति_node_range(shaकरोw_size, PAGE_SIZE, shaकरोw_start,
					shaकरोw_end, GFP_KERNEL,
					PAGE_KERNEL, VM_NO_GUARD,
					pfn_to_nid(mem_data->start_pfn),
					__builtin_वापस_address(0));
		अगर (!ret)
			वापस NOTIFY_BAD;

		kmemleak_ignore(ret);
		वापस NOTIFY_OK;
	पूर्ण
	हाल MEM_CANCEL_ONLINE:
	हाल MEM_OFFLINE: अणु
		काष्ठा vm_काष्ठा *vm;

		/*
		 * shaकरोw_start was either mapped during boot by kasan_init()
		 * or during memory online by __vदो_स्मृति_node_range().
		 * In the latter हाल we can use vमुक्त() to मुक्त shaकरोw.
		 * Non-शून्य result of the find_vm_area() will tell us अगर
		 * that was the second हाल.
		 *
		 * Currently it's not possible to मुक्त shaकरोw mapped
		 * during boot by kasan_init(). It's because the code
		 * to करो that hasn't been written yet. So we'll just
		 * leak the memory.
		 */
		vm = find_vm_area((व्योम *)shaकरोw_start);
		अगर (vm)
			vमुक्त((व्योम *)shaकरोw_start);
	पूर्ण
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक __init kasan_memhotplug_init(व्योम)
अणु
	hotplug_memory_notअगरier(kasan_mem_notअगरier, 0);

	वापस 0;
पूर्ण

core_initcall(kasan_memhotplug_init);
#पूर्ण_अगर

#अगर_घोषित CONFIG_KASAN_VMALLOC

अटल पूर्णांक kasan_populate_vदो_स्मृति_pte(pte_t *ptep, अचिन्हित दीर्घ addr,
				      व्योम *unused)
अणु
	अचिन्हित दीर्घ page;
	pte_t pte;

	अगर (likely(!pte_none(*ptep)))
		वापस 0;

	page = __get_मुक्त_page(GFP_KERNEL);
	अगर (!page)
		वापस -ENOMEM;

	स_रखो((व्योम *)page, KASAN_VMALLOC_INVALID, PAGE_SIZE);
	pte = pfn_pte(PFN_DOWN(__pa(page)), PAGE_KERNEL);

	spin_lock(&init_mm.page_table_lock);
	अगर (likely(pte_none(*ptep))) अणु
		set_pte_at(&init_mm, addr, ptep, pte);
		page = 0;
	पूर्ण
	spin_unlock(&init_mm.page_table_lock);
	अगर (page)
		मुक्त_page(page);
	वापस 0;
पूर्ण

पूर्णांक kasan_populate_vदो_स्मृति(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ shaकरोw_start, shaकरोw_end;
	पूर्णांक ret;

	अगर (!is_vदो_स्मृति_or_module_addr((व्योम *)addr))
		वापस 0;

	shaकरोw_start = (अचिन्हित दीर्घ)kasan_mem_to_shaकरोw((व्योम *)addr);
	shaकरोw_start = ALIGN_DOWN(shaकरोw_start, PAGE_SIZE);
	shaकरोw_end = (अचिन्हित दीर्घ)kasan_mem_to_shaकरोw((व्योम *)addr + size);
	shaकरोw_end = ALIGN(shaकरोw_end, PAGE_SIZE);

	ret = apply_to_page_range(&init_mm, shaकरोw_start,
				  shaकरोw_end - shaकरोw_start,
				  kasan_populate_vदो_स्मृति_pte, शून्य);
	अगर (ret)
		वापस ret;

	flush_cache_vmap(shaकरोw_start, shaकरोw_end);

	/*
	 * We need to be careful about पूर्णांकer-cpu effects here. Consider:
	 *
	 *   CPU#0				  CPU#1
	 * WRITE_ONCE(p, vदो_स्मृति(100));		जबतक (x = READ_ONCE(p)) ;
	 *					p[99] = 1;
	 *
	 * With compiler instrumentation, that ends up looking like this:
	 *
	 *   CPU#0				  CPU#1
	 * // vदो_स्मृति() allocates memory
	 * // let a = area->addr
	 * // we reach kasan_populate_vदो_स्मृति
	 * // and call kasan_unpoison:
	 * STORE shaकरोw(a), unpoison_val
	 * ...
	 * STORE shaकरोw(a+99), unpoison_val	x = LOAD p
	 * // rest of vदो_स्मृति process		<data dependency>
	 * STORE p, a				LOAD shaकरोw(x+99)
	 *
	 * If there is no barrier between the end of unpoisoning the shaकरोw
	 * and the store of the result to p, the stores could be committed
	 * in a dअगरferent order by CPU#0, and CPU#1 could erroneously observe
	 * poison in the shaकरोw.
	 *
	 * We need some sort of barrier between the stores.
	 *
	 * In the vदो_स्मृति() हाल, this is provided by a smp_wmb() in
	 * clear_vm_uninitialized_flag(). In the per-cpu allocator and in
	 * get_vm_area() and मित्रs, the caller माला_लो shaकरोw allocated but
	 * करोesn't have any pages mapped पूर्णांकo the भव address space that
	 * has been reserved. Mapping those pages in will involve taking and
	 * releasing a page-table lock, which will provide the barrier.
	 */

	वापस 0;
पूर्ण

/*
 * Poison the shaकरोw क्रम a vदो_स्मृति region. Called as part of the
 * मुक्तing process at the समय the region is मुक्तd.
 */
व्योम kasan_poison_vदो_स्मृति(स्थिर व्योम *start, अचिन्हित दीर्घ size)
अणु
	अगर (!is_vदो_स्मृति_or_module_addr(start))
		वापस;

	size = round_up(size, KASAN_GRANULE_SIZE);
	kasan_poison(start, size, KASAN_VMALLOC_INVALID, false);
पूर्ण

व्योम kasan_unpoison_vदो_स्मृति(स्थिर व्योम *start, अचिन्हित दीर्घ size)
अणु
	अगर (!is_vदो_स्मृति_or_module_addr(start))
		वापस;

	kasan_unpoison(start, size, false);
पूर्ण

अटल पूर्णांक kasan_depopulate_vदो_स्मृति_pte(pte_t *ptep, अचिन्हित दीर्घ addr,
					व्योम *unused)
अणु
	अचिन्हित दीर्घ page;

	page = (अचिन्हित दीर्घ)__va(pte_pfn(*ptep) << PAGE_SHIFT);

	spin_lock(&init_mm.page_table_lock);

	अगर (likely(!pte_none(*ptep))) अणु
		pte_clear(&init_mm, addr, ptep);
		मुक्त_page(page);
	पूर्ण
	spin_unlock(&init_mm.page_table_lock);

	वापस 0;
पूर्ण

/*
 * Release the backing क्रम the vदो_स्मृति region [start, end), which
 * lies within the मुक्त region [मुक्त_region_start, मुक्त_region_end).
 *
 * This can be run lazily, दीर्घ after the region was मुक्तd. It runs
 * under vmap_area_lock, so it's not safe to पूर्णांकeract with the vदो_स्मृति/vmap
 * infraकाष्ठाure.
 *
 * How करोes this work?
 * -------------------
 *
 * We have a region that is page aligned, labeled as A.
 * That might not map onto the shaकरोw in a way that is page-aligned:
 *
 *                    start                     end
 *                    v                         v
 * |????????|????????|AAAAAAAA|AA....AA|AAAAAAAA|????????| < vदो_स्मृति
 *  -------- -------- --------          -------- --------
 *      |        |       |                 |        |
 *      |        |       |         /-------/        |
 *      \-------\|/------/         |/---------------/
 *              |||                ||
 *             |??AAAAAA|AAAAAAAA|AA??????|                < shaकरोw
 *                 (1)      (2)      (3)
 *
 * First we align the start upwards and the end करोwnwards, so that the
 * shaकरोw of the region aligns with shaकरोw page boundaries. In the
 * example, this gives us the shaकरोw page (2). This is the shaकरोw entirely
 * covered by this allocation.
 *
 * Then we have the tricky bits. We want to know अगर we can मुक्त the
 * partially covered shaकरोw pages - (1) and (3) in the example. For this,
 * we are given the start and end of the मुक्त region that contains this
 * allocation. Extending our previous example, we could have:
 *
 *  मुक्त_region_start                                    मुक्त_region_end
 *  |                 start                     end      |
 *  v                 v                         v        v
 * |FFFFFFFF|FFFFFFFF|AAAAAAAA|AA....AA|AAAAAAAA|FFFFFFFF| < vदो_स्मृति
 *  -------- -------- --------          -------- --------
 *      |        |       |                 |        |
 *      |        |       |         /-------/        |
 *      \-------\|/------/         |/---------------/
 *              |||                ||
 *             |FFAAAAAA|AAAAAAAA|AAF?????|                < shaकरोw
 *                 (1)      (2)      (3)
 *
 * Once again, we align the start of the मुक्त region up, and the end of
 * the मुक्त region करोwn so that the shaकरोw is page aligned. So we can मुक्त
 * page (1) - we know no allocation currently uses anything in that page,
 * because all of it is in the vदो_स्मृति मुक्त region. But we cannot मुक्त
 * page (3), because we can't be sure that the rest of it is unused.
 *
 * We only consider pages that contain part of the original region क्रम
 * मुक्तing: we करोn't try to free other pages from the free region or we'd
 * end up trying to मुक्त huge chunks of भव address space.
 *
 * Concurrency
 * -----------
 *
 * How करो we know that we're not मुक्तing a page that is simultaneously
 * being used क्रम a fresh allocation in kasan_populate_vदो_स्मृति(_pte)?
 *
 * We _can_ have kasan_release_vदो_स्मृति and kasan_populate_vदो_स्मृति running
 * at the same समय. While we run under मुक्त_vmap_area_lock, the population
 * code करोes not.
 *
 * मुक्त_vmap_area_lock instead operates to ensure that the larger range
 * [मुक्त_region_start, मुक्त_region_end) is safe: because __alloc_vmap_area and
 * the per-cpu region-finding algorithm both run under मुक्त_vmap_area_lock,
 * no space identअगरied as मुक्त will become used जबतक we are running. This
 * means that so दीर्घ as we are careful with alignment and only मुक्त shaकरोw
 * pages entirely covered by the मुक्त region, we will not run in to any
 * trouble - any simultaneous allocations will be क्रम disjoपूर्णांक regions.
 */
व्योम kasan_release_vदो_स्मृति(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end,
			   अचिन्हित दीर्घ मुक्त_region_start,
			   अचिन्हित दीर्घ मुक्त_region_end)
अणु
	व्योम *shaकरोw_start, *shaकरोw_end;
	अचिन्हित दीर्घ region_start, region_end;
	अचिन्हित दीर्घ size;

	region_start = ALIGN(start, KASAN_MEMORY_PER_SHADOW_PAGE);
	region_end = ALIGN_DOWN(end, KASAN_MEMORY_PER_SHADOW_PAGE);

	मुक्त_region_start = ALIGN(मुक्त_region_start, KASAN_MEMORY_PER_SHADOW_PAGE);

	अगर (start != region_start &&
	    मुक्त_region_start < region_start)
		region_start -= KASAN_MEMORY_PER_SHADOW_PAGE;

	मुक्त_region_end = ALIGN_DOWN(मुक्त_region_end, KASAN_MEMORY_PER_SHADOW_PAGE);

	अगर (end != region_end &&
	    मुक्त_region_end > region_end)
		region_end += KASAN_MEMORY_PER_SHADOW_PAGE;

	shaकरोw_start = kasan_mem_to_shaकरोw((व्योम *)region_start);
	shaकरोw_end = kasan_mem_to_shaकरोw((व्योम *)region_end);

	अगर (shaकरोw_end > shaकरोw_start) अणु
		size = shaकरोw_end - shaकरोw_start;
		apply_to_existing_page_range(&init_mm,
					     (अचिन्हित दीर्घ)shaकरोw_start,
					     size, kasan_depopulate_vदो_स्मृति_pte,
					     शून्य);
		flush_tlb_kernel_range((अचिन्हित दीर्घ)shaकरोw_start,
				       (अचिन्हित दीर्घ)shaकरोw_end);
	पूर्ण
पूर्ण

#अन्यथा /* CONFIG_KASAN_VMALLOC */

पूर्णांक kasan_module_alloc(व्योम *addr, माप_प्रकार size)
अणु
	व्योम *ret;
	माप_प्रकार scaled_size;
	माप_प्रकार shaकरोw_size;
	अचिन्हित दीर्घ shaकरोw_start;

	shaकरोw_start = (अचिन्हित दीर्घ)kasan_mem_to_shaकरोw(addr);
	scaled_size = (size + KASAN_GRANULE_SIZE - 1) >>
				KASAN_SHADOW_SCALE_SHIFT;
	shaकरोw_size = round_up(scaled_size, PAGE_SIZE);

	अगर (WARN_ON(!PAGE_ALIGNED(shaकरोw_start)))
		वापस -EINVAL;

	ret = __vदो_स्मृति_node_range(shaकरोw_size, 1, shaकरोw_start,
			shaकरोw_start + shaकरोw_size,
			GFP_KERNEL,
			PAGE_KERNEL, VM_NO_GUARD, NUMA_NO_NODE,
			__builtin_वापस_address(0));

	अगर (ret) अणु
		__स_रखो(ret, KASAN_SHADOW_INIT, shaकरोw_size);
		find_vm_area(addr)->flags |= VM_KASAN;
		kmemleak_ignore(ret);
		वापस 0;
	पूर्ण

	वापस -ENOMEM;
पूर्ण

व्योम kasan_मुक्त_shaकरोw(स्थिर काष्ठा vm_काष्ठा *vm)
अणु
	अगर (vm->flags & VM_KASAN)
		vमुक्त(kasan_mem_to_shaकरोw(vm->addr));
पूर्ण

#पूर्ण_अगर
