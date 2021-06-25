<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 - Google LLC
 * Author: Quentin Perret <qperret@google.com>
 */

#समावेश <linux/kvm_host.h>
#समावेश <linux/memblock.h>
#समावेश <linux/sort.h>

#समावेश <यंत्र/kvm_host.h>

#समावेश <nvhe/memory.h>
#समावेश <nvhe/mm.h>

अटल काष्ठा memblock_region *hyp_memory = kvm_nvhe_sym(hyp_memory);
अटल अचिन्हित पूर्णांक *hyp_memblock_nr_ptr = &kvm_nvhe_sym(hyp_memblock_nr);

phys_addr_t hyp_mem_base;
phys_addr_t hyp_mem_size;

अटल पूर्णांक cmp_hyp_memblock(स्थिर व्योम *p1, स्थिर व्योम *p2)
अणु
	स्थिर काष्ठा memblock_region *r1 = p1;
	स्थिर काष्ठा memblock_region *r2 = p2;

	वापस r1->base < r2->base ? -1 : (r1->base > r2->base);
पूर्ण

अटल व्योम __init sort_memblock_regions(व्योम)
अणु
	sort(hyp_memory,
	     *hyp_memblock_nr_ptr,
	     माप(काष्ठा memblock_region),
	     cmp_hyp_memblock,
	     शून्य);
पूर्ण

अटल पूर्णांक __init रेजिस्टर_memblock_regions(व्योम)
अणु
	काष्ठा memblock_region *reg;

	क्रम_each_mem_region(reg) अणु
		अगर (*hyp_memblock_nr_ptr >= HYP_MEMBLOCK_REGIONS)
			वापस -ENOMEM;

		hyp_memory[*hyp_memblock_nr_ptr] = *reg;
		(*hyp_memblock_nr_ptr)++;
	पूर्ण
	sort_memblock_regions();

	वापस 0;
पूर्ण

व्योम __init kvm_hyp_reserve(व्योम)
अणु
	u64 nr_pages, prev, hyp_mem_pages = 0;
	पूर्णांक ret;

	अगर (!is_hyp_mode_available() || is_kernel_in_hyp_mode())
		वापस;

	अगर (kvm_get_mode() != KVM_MODE_PROTECTED)
		वापस;

	ret = रेजिस्टर_memblock_regions();
	अगर (ret) अणु
		*hyp_memblock_nr_ptr = 0;
		kvm_err("Failed to register hyp memblocks: %d\n", ret);
		वापस;
	पूर्ण

	hyp_mem_pages += hyp_s1_pgtable_pages();
	hyp_mem_pages += host_s2_mem_pgtable_pages();
	hyp_mem_pages += host_s2_dev_pgtable_pages();

	/*
	 * The hyp_vmemmap needs to be backed by pages, but these pages
	 * themselves need to be present in the vmemmap, so compute the number
	 * of pages needed by looking क्रम a fixed poपूर्णांक.
	 */
	nr_pages = 0;
	करो अणु
		prev = nr_pages;
		nr_pages = hyp_mem_pages + prev;
		nr_pages = DIV_ROUND_UP(nr_pages * माप(काष्ठा hyp_page), PAGE_SIZE);
		nr_pages += __hyp_pgtable_max_pages(nr_pages);
	पूर्ण जबतक (nr_pages != prev);
	hyp_mem_pages += nr_pages;

	/*
	 * Try to allocate a PMD-aligned region to reduce TLB pressure once
	 * this is unmapped from the host stage-2, and fallback to PAGE_SIZE.
	 */
	hyp_mem_size = hyp_mem_pages << PAGE_SHIFT;
	hyp_mem_base = memblock_find_in_range(0, memblock_end_of_DRAM(),
					      ALIGN(hyp_mem_size, PMD_SIZE),
					      PMD_SIZE);
	अगर (!hyp_mem_base)
		hyp_mem_base = memblock_find_in_range(0, memblock_end_of_DRAM(),
						      hyp_mem_size, PAGE_SIZE);
	अन्यथा
		hyp_mem_size = ALIGN(hyp_mem_size, PMD_SIZE);

	अगर (!hyp_mem_base) अणु
		kvm_err("Failed to reserve hyp memory\n");
		वापस;
	पूर्ण
	memblock_reserve(hyp_mem_base, hyp_mem_size);

	kvm_info("Reserved %lld MiB at 0x%llx\n", hyp_mem_size >> 20,
		 hyp_mem_base);
पूर्ण
