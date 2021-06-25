<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * IA-32 Huge TLB Page Support क्रम Kernel.
 *
 * Copyright (C) 2002, Rohit Seth <rohit.seth@पूर्णांकel.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/err.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/compat.h>
#समावेश <यंत्र/mman.h>
#समावेश <यंत्र/tlb.h>
#समावेश <यंत्र/tlbflush.h>
#समावेश <यंत्र/elf.h>

#अगर 0	/* This is just क्रम testing */
काष्ठा page *
follow_huge_addr(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ address, पूर्णांक ग_लिखो)
अणु
	अचिन्हित दीर्घ start = address;
	पूर्णांक length = 1;
	पूर्णांक nr;
	काष्ठा page *page;
	काष्ठा vm_area_काष्ठा *vma;

	vma = find_vma(mm, addr);
	अगर (!vma || !is_vm_hugetlb_page(vma))
		वापस ERR_PTR(-EINVAL);

	pte = huge_pte_offset(mm, address, vma_mmu_pagesize(vma));

	/* hugetlb should be locked, and hence, prefaulted */
	WARN_ON(!pte || pte_none(*pte));

	page = &pte_page(*pte)[vpfn % (HPAGE_SIZE/PAGE_SIZE)];

	WARN_ON(!PageHead(page));

	वापस page;
पूर्ण

पूर्णांक pmd_huge(pmd_t pmd)
अणु
	वापस 0;
पूर्ण

पूर्णांक pud_huge(pud_t pud)
अणु
	वापस 0;
पूर्ण

#अन्यथा

/*
 * pmd_huge() वापसs 1 अगर @pmd is hugetlb related entry, that is normal
 * hugetlb entry or non-present (migration or hwpoisoned) hugetlb entry.
 * Otherwise, वापसs 0.
 */
पूर्णांक pmd_huge(pmd_t pmd)
अणु
	वापस !pmd_none(pmd) &&
		(pmd_val(pmd) & (_PAGE_PRESENT|_PAGE_PSE)) != _PAGE_PRESENT;
पूर्ण

पूर्णांक pud_huge(pud_t pud)
अणु
	वापस !!(pud_val(pud) & _PAGE_PSE);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HUGETLB_PAGE
अटल अचिन्हित दीर्घ hugetlb_get_unmapped_area_bottomup(काष्ठा file *file,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
		अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	काष्ठा hstate *h = hstate_file(file);
	काष्ठा vm_unmapped_area_info info;

	info.flags = 0;
	info.length = len;
	info.low_limit = get_mmap_base(1);

	/*
	 * If hपूर्णांक address is above DEFAULT_MAP_WINDOW, look क्रम unmapped area
	 * in the full address space.
	 */
	info.high_limit = in_32bit_syscall() ?
		task_size_32bit() : task_size_64bit(addr > DEFAULT_MAP_WINDOW);

	info.align_mask = PAGE_MASK & ~huge_page_mask(h);
	info.align_offset = 0;
	वापस vm_unmapped_area(&info);
पूर्ण

अटल अचिन्हित दीर्घ hugetlb_get_unmapped_area_topकरोwn(काष्ठा file *file,
		अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
		अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	काष्ठा hstate *h = hstate_file(file);
	काष्ठा vm_unmapped_area_info info;

	info.flags = VM_UNMAPPED_AREA_TOPDOWN;
	info.length = len;
	info.low_limit = PAGE_SIZE;
	info.high_limit = get_mmap_base(0);

	/*
	 * If hपूर्णांक address is above DEFAULT_MAP_WINDOW, look क्रम unmapped area
	 * in the full address space.
	 */
	अगर (addr > DEFAULT_MAP_WINDOW && !in_32bit_syscall())
		info.high_limit += TASK_SIZE_MAX - DEFAULT_MAP_WINDOW;

	info.align_mask = PAGE_MASK & ~huge_page_mask(h);
	info.align_offset = 0;
	addr = vm_unmapped_area(&info);

	/*
	 * A failed mmap() very likely causes application failure,
	 * so fall back to the bottom-up function here. This scenario
	 * can happen with large stack limits and large mmap()
	 * allocations.
	 */
	अगर (addr & ~PAGE_MASK) अणु
		VM_BUG_ON(addr != -ENOMEM);
		info.flags = 0;
		info.low_limit = TASK_UNMAPPED_BASE;
		info.high_limit = TASK_SIZE_LOW;
		addr = vm_unmapped_area(&info);
	पूर्ण

	वापस addr;
पूर्ण

अचिन्हित दीर्घ
hugetlb_get_unmapped_area(काष्ठा file *file, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	काष्ठा hstate *h = hstate_file(file);
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;

	अगर (len & ~huge_page_mask(h))
		वापस -EINVAL;

	अगर (len > TASK_SIZE)
		वापस -ENOMEM;

	/* No address checking. See comment at mmap_address_hपूर्णांक_valid() */
	अगर (flags & MAP_FIXED) अणु
		अगर (prepare_hugepage_range(file, addr, len))
			वापस -EINVAL;
		वापस addr;
	पूर्ण

	अगर (addr) अणु
		addr &= huge_page_mask(h);
		अगर (!mmap_address_hपूर्णांक_valid(addr, len))
			जाओ get_unmapped_area;

		vma = find_vma(mm, addr);
		अगर (!vma || addr + len <= vm_start_gap(vma))
			वापस addr;
	पूर्ण

get_unmapped_area:
	अगर (mm->get_unmapped_area == arch_get_unmapped_area)
		वापस hugetlb_get_unmapped_area_bottomup(file, addr, len,
				pgoff, flags);
	अन्यथा
		वापस hugetlb_get_unmapped_area_topकरोwn(file, addr, len,
				pgoff, flags);
पूर्ण
#पूर्ण_अगर /* CONFIG_HUGETLB_PAGE */

#अगर_घोषित CONFIG_X86_64
bool __init arch_hugetlb_valid_size(अचिन्हित दीर्घ size)
अणु
	अगर (size == PMD_SIZE)
		वापस true;
	अन्यथा अगर (size == PUD_SIZE && boot_cpu_has(X86_FEATURE_GBPAGES))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

#अगर_घोषित CONFIG_CONTIG_ALLOC
अटल __init पूर्णांक gigantic_pages_init(व्योम)
अणु
	/* With compaction or CMA we can allocate gigantic pages at runसमय */
	अगर (boot_cpu_has(X86_FEATURE_GBPAGES))
		hugetlb_add_hstate(PUD_SHIFT - PAGE_SHIFT);
	वापस 0;
पूर्ण
arch_initcall(gigantic_pages_init);
#पूर्ण_अगर
#पूर्ण_अगर
