<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/mm.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/security.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/mman.h>
#समावेश <यंत्र/tlb.h>

व्योम radix__flush_hugetlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr)
अणु
	पूर्णांक psize;
	काष्ठा hstate *hstate = hstate_file(vma->vm_file);

	psize = hstate_get_psize(hstate);
	radix__flush_tlb_page_psize(vma->vm_mm, vmaddr, psize);
पूर्ण

व्योम radix__local_flush_hugetlb_page(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ vmaddr)
अणु
	पूर्णांक psize;
	काष्ठा hstate *hstate = hstate_file(vma->vm_file);

	psize = hstate_get_psize(hstate);
	radix__local_flush_tlb_page_psize(vma->vm_mm, vmaddr, psize);
पूर्ण

व्योम radix__flush_hugetlb_tlb_range(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ start,
				   अचिन्हित दीर्घ end)
अणु
	पूर्णांक psize;
	काष्ठा hstate *hstate = hstate_file(vma->vm_file);

	psize = hstate_get_psize(hstate);
	radix__flush_tlb_range_psize(vma->vm_mm, start, end, psize);
पूर्ण

/*
 * A vairant of hugetlb_get_unmapped_area करोing topकरोwn search
 * FIXME!! should we करो as x86 करोes or non hugetlb area करोes ?
 * ie, use topकरोwn or not based on mmap_is_legacy check ?
 */
अचिन्हित दीर्घ
radix__hugetlb_get_unmapped_area(काष्ठा file *file, अचिन्हित दीर्घ addr,
				अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff,
				अचिन्हित दीर्घ flags)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा hstate *h = hstate_file(file);
	पूर्णांक fixed = (flags & MAP_FIXED);
	अचिन्हित दीर्घ high_limit;
	काष्ठा vm_unmapped_area_info info;

	high_limit = DEFAULT_MAP_WINDOW;
	अगर (addr >= high_limit || (fixed && (addr + len > high_limit)))
		high_limit = TASK_SIZE;

	अगर (len & ~huge_page_mask(h))
		वापस -EINVAL;
	अगर (len > high_limit)
		वापस -ENOMEM;

	अगर (fixed) अणु
		अगर (addr > high_limit - len)
			वापस -ENOMEM;
		अगर (prepare_hugepage_range(file, addr, len))
			वापस -EINVAL;
		वापस addr;
	पूर्ण

	अगर (addr) अणु
		addr = ALIGN(addr, huge_page_size(h));
		vma = find_vma(mm, addr);
		अगर (high_limit - len >= addr && addr >= mmap_min_addr &&
		    (!vma || addr + len <= vm_start_gap(vma)))
			वापस addr;
	पूर्ण
	/*
	 * We are always करोing an topकरोwn search here. Slice code
	 * करोes that too.
	 */
	info.flags = VM_UNMAPPED_AREA_TOPDOWN;
	info.length = len;
	info.low_limit = max(PAGE_SIZE, mmap_min_addr);
	info.high_limit = mm->mmap_base + (high_limit - DEFAULT_MAP_WINDOW);
	info.align_mask = PAGE_MASK & ~huge_page_mask(h);
	info.align_offset = 0;

	वापस vm_unmapped_area(&info);
पूर्ण

व्योम radix__huge_ptep_modअगरy_prot_commit(काष्ठा vm_area_काष्ठा *vma,
					 अचिन्हित दीर्घ addr, pte_t *ptep,
					 pte_t old_pte, pte_t pte)
अणु
	काष्ठा mm_काष्ठा *mm = vma->vm_mm;

	/*
	 * To aव्योम NMMU hang जबतक relaxing access we need to flush the tlb beक्रमe
	 * we set the new value.
	 */
	अगर (is_pte_rw_upgrade(pte_val(old_pte), pte_val(pte)) &&
	    (atomic_पढ़ो(&mm->context.copros) > 0))
		radix__flush_hugetlb_page(vma, addr);

	set_huge_pte_at(vma->vm_mm, addr, ptep, pte);
पूर्ण
