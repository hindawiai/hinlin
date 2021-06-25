<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * address space "slices" (meta-segments) support
 *
 * Copyright (C) 2007 Benjamin Herrenschmidt, IBM Corporation.
 *
 * Based on hugetlb implementation
 *
 * Copyright (C) 2003 David Gibson, IBM Corporation.
 */

#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/err.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/export.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/security.h>
#समावेश <यंत्र/mman.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/copro.h>
#समावेश <यंत्र/hugetlb.h>
#समावेश <यंत्र/mmu_context.h>

अटल DEFINE_SPINLOCK(slice_convert_lock);

#अगर_घोषित DEBUG
पूर्णांक _slice_debug = 1;

अटल व्योम slice_prपूर्णांक_mask(स्थिर अक्षर *label, स्थिर काष्ठा slice_mask *mask)
अणु
	अगर (!_slice_debug)
		वापस;
	pr_devel("%s low_slice: %*pbl\n", label,
			(पूर्णांक)SLICE_NUM_LOW, &mask->low_slices);
	pr_devel("%s high_slice: %*pbl\n", label,
			(पूर्णांक)SLICE_NUM_HIGH, mask->high_slices);
पूर्ण

#घोषणा slice_dbg(fmt...) करो अणु अगर (_slice_debug) pr_devel(fmt); पूर्ण जबतक (0)

#अन्यथा

अटल व्योम slice_prपूर्णांक_mask(स्थिर अक्षर *label, स्थिर काष्ठा slice_mask *mask) अणुपूर्ण
#घोषणा slice_dbg(fmt...)

#पूर्ण_अगर

अटल अंतरभूत notrace bool slice_addr_is_low(अचिन्हित दीर्घ addr)
अणु
	u64 पंचांगp = (u64)addr;

	वापस पंचांगp < SLICE_LOW_TOP;
पूर्ण

अटल व्योम slice_range_to_mask(अचिन्हित दीर्घ start, अचिन्हित दीर्घ len,
				काष्ठा slice_mask *ret)
अणु
	अचिन्हित दीर्घ end = start + len - 1;

	ret->low_slices = 0;
	अगर (SLICE_NUM_HIGH)
		biपंचांगap_zero(ret->high_slices, SLICE_NUM_HIGH);

	अगर (slice_addr_is_low(start)) अणु
		अचिन्हित दीर्घ mend = min(end,
					 (अचिन्हित दीर्घ)(SLICE_LOW_TOP - 1));

		ret->low_slices = (1u << (GET_LOW_SLICE_INDEX(mend) + 1))
			- (1u << GET_LOW_SLICE_INDEX(start));
	पूर्ण

	अगर (SLICE_NUM_HIGH && !slice_addr_is_low(end)) अणु
		अचिन्हित दीर्घ start_index = GET_HIGH_SLICE_INDEX(start);
		अचिन्हित दीर्घ align_end = ALIGN(end, (1UL << SLICE_HIGH_SHIFT));
		अचिन्हित दीर्घ count = GET_HIGH_SLICE_INDEX(align_end) - start_index;

		biपंचांगap_set(ret->high_slices, start_index, count);
	पूर्ण
पूर्ण

अटल पूर्णांक slice_area_is_मुक्त(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			      अचिन्हित दीर्घ len)
अणु
	काष्ठा vm_area_काष्ठा *vma;

	अगर ((mm_ctx_slb_addr_limit(&mm->context) - len) < addr)
		वापस 0;
	vma = find_vma(mm, addr);
	वापस (!vma || (addr + len) <= vm_start_gap(vma));
पूर्ण

अटल पूर्णांक slice_low_has_vma(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ slice)
अणु
	वापस !slice_area_is_मुक्त(mm, slice << SLICE_LOW_SHIFT,
				   1ul << SLICE_LOW_SHIFT);
पूर्ण

अटल पूर्णांक slice_high_has_vma(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ slice)
अणु
	अचिन्हित दीर्घ start = slice << SLICE_HIGH_SHIFT;
	अचिन्हित दीर्घ end = start + (1ul << SLICE_HIGH_SHIFT);

	/* Hack, so that each addresses is controlled by exactly one
	 * of the high or low area biपंचांगaps, the first high area starts
	 * at 4GB, not 0 */
	अगर (start == 0)
		start = (अचिन्हित दीर्घ)SLICE_LOW_TOP;

	वापस !slice_area_is_मुक्त(mm, start, end - start);
पूर्ण

अटल व्योम slice_mask_क्रम_मुक्त(काष्ठा mm_काष्ठा *mm, काष्ठा slice_mask *ret,
				अचिन्हित दीर्घ high_limit)
अणु
	अचिन्हित दीर्घ i;

	ret->low_slices = 0;
	अगर (SLICE_NUM_HIGH)
		biपंचांगap_zero(ret->high_slices, SLICE_NUM_HIGH);

	क्रम (i = 0; i < SLICE_NUM_LOW; i++)
		अगर (!slice_low_has_vma(mm, i))
			ret->low_slices |= 1u << i;

	अगर (slice_addr_is_low(high_limit - 1))
		वापस;

	क्रम (i = 0; i < GET_HIGH_SLICE_INDEX(high_limit); i++)
		अगर (!slice_high_has_vma(mm, i))
			__set_bit(i, ret->high_slices);
पूर्ण

अटल bool slice_check_range_fits(काष्ठा mm_काष्ठा *mm,
			   स्थिर काष्ठा slice_mask *available,
			   अचिन्हित दीर्घ start, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ end = start + len - 1;
	u64 low_slices = 0;

	अगर (slice_addr_is_low(start)) अणु
		अचिन्हित दीर्घ mend = min(end,
					 (अचिन्हित दीर्घ)(SLICE_LOW_TOP - 1));

		low_slices = (1u << (GET_LOW_SLICE_INDEX(mend) + 1))
				- (1u << GET_LOW_SLICE_INDEX(start));
	पूर्ण
	अगर ((low_slices & available->low_slices) != low_slices)
		वापस false;

	अगर (SLICE_NUM_HIGH && !slice_addr_is_low(end)) अणु
		अचिन्हित दीर्घ start_index = GET_HIGH_SLICE_INDEX(start);
		अचिन्हित दीर्घ align_end = ALIGN(end, (1UL << SLICE_HIGH_SHIFT));
		अचिन्हित दीर्घ count = GET_HIGH_SLICE_INDEX(align_end) - start_index;
		अचिन्हित दीर्घ i;

		क्रम (i = start_index; i < start_index + count; i++) अणु
			अगर (!test_bit(i, available->high_slices))
				वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम slice_flush_segments(व्योम *parm)
अणु
#अगर_घोषित CONFIG_PPC64
	काष्ठा mm_काष्ठा *mm = parm;
	अचिन्हित दीर्घ flags;

	अगर (mm != current->active_mm)
		वापस;

	copy_mm_to_paca(current->active_mm);

	local_irq_save(flags);
	slb_flush_and_restore_bolted();
	local_irq_restore(flags);
#पूर्ण_अगर
पूर्ण

अटल व्योम slice_convert(काष्ठा mm_काष्ठा *mm,
				स्थिर काष्ठा slice_mask *mask, पूर्णांक psize)
अणु
	पूर्णांक index, mask_index;
	/* Write the new slice psize bits */
	अचिन्हित अक्षर *hpsizes, *lpsizes;
	काष्ठा slice_mask *psize_mask, *old_mask;
	अचिन्हित दीर्घ i, flags;
	पूर्णांक old_psize;

	slice_dbg("slice_convert(mm=%p, psize=%d)\n", mm, psize);
	slice_prपूर्णांक_mask(" mask", mask);

	psize_mask = slice_mask_क्रम_size(&mm->context, psize);

	/* We need to use a spinlock here to protect against
	 * concurrent 64k -> 4k demotion ...
	 */
	spin_lock_irqsave(&slice_convert_lock, flags);

	lpsizes = mm_ctx_low_slices(&mm->context);
	क्रम (i = 0; i < SLICE_NUM_LOW; i++) अणु
		अगर (!(mask->low_slices & (1u << i)))
			जारी;

		mask_index = i & 0x1;
		index = i >> 1;

		/* Update the slice_mask */
		old_psize = (lpsizes[index] >> (mask_index * 4)) & 0xf;
		old_mask = slice_mask_क्रम_size(&mm->context, old_psize);
		old_mask->low_slices &= ~(1u << i);
		psize_mask->low_slices |= 1u << i;

		/* Update the sizes array */
		lpsizes[index] = (lpsizes[index] & ~(0xf << (mask_index * 4))) |
				(((अचिन्हित दीर्घ)psize) << (mask_index * 4));
	पूर्ण

	hpsizes = mm_ctx_high_slices(&mm->context);
	क्रम (i = 0; i < GET_HIGH_SLICE_INDEX(mm_ctx_slb_addr_limit(&mm->context)); i++) अणु
		अगर (!test_bit(i, mask->high_slices))
			जारी;

		mask_index = i & 0x1;
		index = i >> 1;

		/* Update the slice_mask */
		old_psize = (hpsizes[index] >> (mask_index * 4)) & 0xf;
		old_mask = slice_mask_क्रम_size(&mm->context, old_psize);
		__clear_bit(i, old_mask->high_slices);
		__set_bit(i, psize_mask->high_slices);

		/* Update the sizes array */
		hpsizes[index] = (hpsizes[index] & ~(0xf << (mask_index * 4))) |
				(((अचिन्हित दीर्घ)psize) << (mask_index * 4));
	पूर्ण

	slice_dbg(" lsps=%lx, hsps=%lx\n",
		  (अचिन्हित दीर्घ)mm_ctx_low_slices(&mm->context),
		  (अचिन्हित दीर्घ)mm_ctx_high_slices(&mm->context));

	spin_unlock_irqrestore(&slice_convert_lock, flags);

	copro_flush_all_slbs(mm);
पूर्ण

/*
 * Compute which slice addr is part of;
 * set *boundary_addr to the start or end boundary of that slice
 * (depending on 'end' parameter);
 * वापस boolean indicating अगर the slice is marked as available in the
 * 'available' slice_mark.
 */
अटल bool slice_scan_available(अचिन्हित दीर्घ addr,
				 स्थिर काष्ठा slice_mask *available,
				 पूर्णांक end, अचिन्हित दीर्घ *boundary_addr)
अणु
	अचिन्हित दीर्घ slice;
	अगर (slice_addr_is_low(addr)) अणु
		slice = GET_LOW_SLICE_INDEX(addr);
		*boundary_addr = (slice + end) << SLICE_LOW_SHIFT;
		वापस !!(available->low_slices & (1u << slice));
	पूर्ण अन्यथा अणु
		slice = GET_HIGH_SLICE_INDEX(addr);
		*boundary_addr = (slice + end) ?
			((slice + end) << SLICE_HIGH_SHIFT) : SLICE_LOW_TOP;
		वापस !!test_bit(slice, available->high_slices);
	पूर्ण
पूर्ण

अटल अचिन्हित दीर्घ slice_find_area_bottomup(काष्ठा mm_काष्ठा *mm,
					      अचिन्हित दीर्घ len,
					      स्थिर काष्ठा slice_mask *available,
					      पूर्णांक psize, अचिन्हित दीर्घ high_limit)
अणु
	पूर्णांक pshअगरt = max_t(पूर्णांक, mmu_psize_defs[psize].shअगरt, PAGE_SHIFT);
	अचिन्हित दीर्घ addr, found, next_end;
	काष्ठा vm_unmapped_area_info info;

	info.flags = 0;
	info.length = len;
	info.align_mask = PAGE_MASK & ((1ul << pshअगरt) - 1);
	info.align_offset = 0;

	addr = TASK_UNMAPPED_BASE;
	/*
	 * Check till the allow max value क्रम this mmap request
	 */
	जबतक (addr < high_limit) अणु
		info.low_limit = addr;
		अगर (!slice_scan_available(addr, available, 1, &addr))
			जारी;

 next_slice:
		/*
		 * At this poपूर्णांक [info.low_limit; addr) covers
		 * available slices only and ends at a slice boundary.
		 * Check अगर we need to reduce the range, or अगर we can
		 * extend it to cover the next available slice.
		 */
		अगर (addr >= high_limit)
			addr = high_limit;
		अन्यथा अगर (slice_scan_available(addr, available, 1, &next_end)) अणु
			addr = next_end;
			जाओ next_slice;
		पूर्ण
		info.high_limit = addr;

		found = vm_unmapped_area(&info);
		अगर (!(found & ~PAGE_MASK))
			वापस found;
	पूर्ण

	वापस -ENOMEM;
पूर्ण

अटल अचिन्हित दीर्घ slice_find_area_topकरोwn(काष्ठा mm_काष्ठा *mm,
					     अचिन्हित दीर्घ len,
					     स्थिर काष्ठा slice_mask *available,
					     पूर्णांक psize, अचिन्हित दीर्घ high_limit)
अणु
	पूर्णांक pshअगरt = max_t(पूर्णांक, mmu_psize_defs[psize].shअगरt, PAGE_SHIFT);
	अचिन्हित दीर्घ addr, found, prev;
	काष्ठा vm_unmapped_area_info info;
	अचिन्हित दीर्घ min_addr = max(PAGE_SIZE, mmap_min_addr);

	info.flags = VM_UNMAPPED_AREA_TOPDOWN;
	info.length = len;
	info.align_mask = PAGE_MASK & ((1ul << pshअगरt) - 1);
	info.align_offset = 0;

	addr = mm->mmap_base;
	/*
	 * If we are trying to allocate above DEFAULT_MAP_WINDOW
	 * Add the dअगरferent to the mmap_base.
	 * Only क्रम that request क्रम which high_limit is above
	 * DEFAULT_MAP_WINDOW we should apply this.
	 */
	अगर (high_limit > DEFAULT_MAP_WINDOW)
		addr += mm_ctx_slb_addr_limit(&mm->context) - DEFAULT_MAP_WINDOW;

	जबतक (addr > min_addr) अणु
		info.high_limit = addr;
		अगर (!slice_scan_available(addr - 1, available, 0, &addr))
			जारी;

 prev_slice:
		/*
		 * At this poपूर्णांक [addr; info.high_limit) covers
		 * available slices only and starts at a slice boundary.
		 * Check अगर we need to reduce the range, or अगर we can
		 * extend it to cover the previous available slice.
		 */
		अगर (addr < min_addr)
			addr = min_addr;
		अन्यथा अगर (slice_scan_available(addr - 1, available, 0, &prev)) अणु
			addr = prev;
			जाओ prev_slice;
		पूर्ण
		info.low_limit = addr;

		found = vm_unmapped_area(&info);
		अगर (!(found & ~PAGE_MASK))
			वापस found;
	पूर्ण

	/*
	 * A failed mmap() very likely causes application failure,
	 * so fall back to the bottom-up function here. This scenario
	 * can happen with large stack limits and large mmap()
	 * allocations.
	 */
	वापस slice_find_area_bottomup(mm, len, available, psize, high_limit);
पूर्ण


अटल अचिन्हित दीर्घ slice_find_area(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ len,
				     स्थिर काष्ठा slice_mask *mask, पूर्णांक psize,
				     पूर्णांक topकरोwn, अचिन्हित दीर्घ high_limit)
अणु
	अगर (topकरोwn)
		वापस slice_find_area_topकरोwn(mm, len, mask, psize, high_limit);
	अन्यथा
		वापस slice_find_area_bottomup(mm, len, mask, psize, high_limit);
पूर्ण

अटल अंतरभूत व्योम slice_copy_mask(काष्ठा slice_mask *dst,
					स्थिर काष्ठा slice_mask *src)
अणु
	dst->low_slices = src->low_slices;
	अगर (!SLICE_NUM_HIGH)
		वापस;
	biपंचांगap_copy(dst->high_slices, src->high_slices, SLICE_NUM_HIGH);
पूर्ण

अटल अंतरभूत व्योम slice_or_mask(काष्ठा slice_mask *dst,
					स्थिर काष्ठा slice_mask *src1,
					स्थिर काष्ठा slice_mask *src2)
अणु
	dst->low_slices = src1->low_slices | src2->low_slices;
	अगर (!SLICE_NUM_HIGH)
		वापस;
	biपंचांगap_or(dst->high_slices, src1->high_slices, src2->high_slices, SLICE_NUM_HIGH);
पूर्ण

अटल अंतरभूत व्योम slice_andnot_mask(काष्ठा slice_mask *dst,
					स्थिर काष्ठा slice_mask *src1,
					स्थिर काष्ठा slice_mask *src2)
अणु
	dst->low_slices = src1->low_slices & ~src2->low_slices;
	अगर (!SLICE_NUM_HIGH)
		वापस;
	biपंचांगap_andnot(dst->high_slices, src1->high_slices, src2->high_slices, SLICE_NUM_HIGH);
पूर्ण

#अगर_घोषित CONFIG_PPC_64K_PAGES
#घोषणा MMU_PAGE_BASE	MMU_PAGE_64K
#अन्यथा
#घोषणा MMU_PAGE_BASE	MMU_PAGE_4K
#पूर्ण_अगर

अचिन्हित दीर्घ slice_get_unmapped_area(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
				      अचिन्हित दीर्घ flags, अचिन्हित पूर्णांक psize,
				      पूर्णांक topकरोwn)
अणु
	काष्ठा slice_mask good_mask;
	काष्ठा slice_mask potential_mask;
	स्थिर काष्ठा slice_mask *maskp;
	स्थिर काष्ठा slice_mask *compat_maskp = शून्य;
	पूर्णांक fixed = (flags & MAP_FIXED);
	पूर्णांक pshअगरt = max_t(पूर्णांक, mmu_psize_defs[psize].shअगरt, PAGE_SHIFT);
	अचिन्हित दीर्घ page_size = 1UL << pshअगरt;
	काष्ठा mm_काष्ठा *mm = current->mm;
	अचिन्हित दीर्घ newaddr;
	अचिन्हित दीर्घ high_limit;

	high_limit = DEFAULT_MAP_WINDOW;
	अगर (addr >= high_limit || (fixed && (addr + len > high_limit)))
		high_limit = TASK_SIZE;

	अगर (len > high_limit)
		वापस -ENOMEM;
	अगर (len & (page_size - 1))
		वापस -EINVAL;
	अगर (fixed) अणु
		अगर (addr & (page_size - 1))
			वापस -EINVAL;
		अगर (addr > high_limit - len)
			वापस -ENOMEM;
	पूर्ण

	अगर (high_limit > mm_ctx_slb_addr_limit(&mm->context)) अणु
		/*
		 * Increasing the slb_addr_limit करोes not require
		 * slice mask cache to be recalculated because it should
		 * be alपढ़ोy initialised beyond the old address limit.
		 */
		mm_ctx_set_slb_addr_limit(&mm->context, high_limit);

		on_each_cpu(slice_flush_segments, mm, 1);
	पूर्ण

	/* Sanity checks */
	BUG_ON(mm->task_size == 0);
	BUG_ON(mm_ctx_slb_addr_limit(&mm->context) == 0);
	VM_BUG_ON(radix_enabled());

	slice_dbg("slice_get_unmapped_area(mm=%p, psize=%d...\n", mm, psize);
	slice_dbg(" addr=%lx, len=%lx, flags=%lx, topdown=%d\n",
		  addr, len, flags, topकरोwn);

	/* If hपूर्णांक, make sure it matches our alignment restrictions */
	अगर (!fixed && addr) अणु
		addr = ALIGN(addr, page_size);
		slice_dbg(" aligned addr=%lx\n", addr);
		/* Ignore hपूर्णांक अगर it's too large or overlaps a VMA */
		अगर (addr > high_limit - len || addr < mmap_min_addr ||
		    !slice_area_is_मुक्त(mm, addr, len))
			addr = 0;
	पूर्ण

	/* First make up a "good" mask of slices that have the right size
	 * alपढ़ोy
	 */
	maskp = slice_mask_क्रम_size(&mm->context, psize);

	/*
	 * Here "good" means slices that are alपढ़ोy the right page size,
	 * "compat" means slices that have a compatible page size (i.e.
	 * 4k in a 64k pagesize kernel), and "free" means slices without
	 * any VMAs.
	 *
	 * If MAP_FIXED:
	 *	check अगर fits in good | compat => OK
	 *	check अगर fits in good | compat | मुक्त => convert मुक्त
	 *	अन्यथा bad
	 * If have hपूर्णांक:
	 *	check अगर hपूर्णांक fits in good => OK
	 *	check अगर hपूर्णांक fits in good | मुक्त => convert मुक्त
	 * Otherwise:
	 *	search in good, found => OK
	 *	search in good | मुक्त, found => convert मुक्त
	 *	search in good | compat | मुक्त, found => convert मुक्त.
	 */

	/*
	 * If we support combo pages, we can allow 64k pages in 4k slices
	 * The mask copies could be aव्योमed in most हालs here अगर we had
	 * a poपूर्णांकer to good mask क्रम the next code to use.
	 */
	अगर (IS_ENABLED(CONFIG_PPC_64K_PAGES) && psize == MMU_PAGE_64K) अणु
		compat_maskp = slice_mask_क्रम_size(&mm->context, MMU_PAGE_4K);
		अगर (fixed)
			slice_or_mask(&good_mask, maskp, compat_maskp);
		अन्यथा
			slice_copy_mask(&good_mask, maskp);
	पूर्ण अन्यथा अणु
		slice_copy_mask(&good_mask, maskp);
	पूर्ण

	slice_prपूर्णांक_mask(" good_mask", &good_mask);
	अगर (compat_maskp)
		slice_prपूर्णांक_mask(" compat_mask", compat_maskp);

	/* First check hपूर्णांक अगर it's valid or अगर we have MAP_FIXED */
	अगर (addr != 0 || fixed) अणु
		/* Check अगर we fit in the good mask. If we करो, we just वापस,
		 * nothing अन्यथा to करो
		 */
		अगर (slice_check_range_fits(mm, &good_mask, addr, len)) अणु
			slice_dbg(" fits good !\n");
			newaddr = addr;
			जाओ वापस_addr;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Now let's see अगर we can find something in the existing
		 * slices क्रम that size
		 */
		newaddr = slice_find_area(mm, len, &good_mask,
					  psize, topकरोwn, high_limit);
		अगर (newaddr != -ENOMEM) अणु
			/* Found within the good mask, we करोn't have to setup,
			 * we thus वापस directly
			 */
			slice_dbg(" found area at 0x%lx\n", newaddr);
			जाओ वापस_addr;
		पूर्ण
	पूर्ण
	/*
	 * We करोn't fit in the good mask, check what other slices are
	 * empty and thus can be converted
	 */
	slice_mask_क्रम_मुक्त(mm, &potential_mask, high_limit);
	slice_or_mask(&potential_mask, &potential_mask, &good_mask);
	slice_prपूर्णांक_mask(" potential", &potential_mask);

	अगर (addr != 0 || fixed) अणु
		अगर (slice_check_range_fits(mm, &potential_mask, addr, len)) अणु
			slice_dbg(" fits potential !\n");
			newaddr = addr;
			जाओ convert;
		पूर्ण
	पूर्ण

	/* If we have MAP_FIXED and failed the above steps, then error out */
	अगर (fixed)
		वापस -EBUSY;

	slice_dbg(" search...\n");

	/* If we had a hपूर्णांक that didn't work out, see अगर we can fit
	 * anywhere in the good area.
	 */
	अगर (addr) अणु
		newaddr = slice_find_area(mm, len, &good_mask,
					  psize, topकरोwn, high_limit);
		अगर (newaddr != -ENOMEM) अणु
			slice_dbg(" found area at 0x%lx\n", newaddr);
			जाओ वापस_addr;
		पूर्ण
	पूर्ण

	/* Now let's see अगर we can find something in the existing slices
	 * क्रम that size plus मुक्त slices
	 */
	newaddr = slice_find_area(mm, len, &potential_mask,
				  psize, topकरोwn, high_limit);

	अगर (IS_ENABLED(CONFIG_PPC_64K_PAGES) && newaddr == -ENOMEM &&
	    psize == MMU_PAGE_64K) अणु
		/* retry the search with 4k-page slices included */
		slice_or_mask(&potential_mask, &potential_mask, compat_maskp);
		newaddr = slice_find_area(mm, len, &potential_mask,
					  psize, topकरोwn, high_limit);
	पूर्ण

	अगर (newaddr == -ENOMEM)
		वापस -ENOMEM;

	slice_range_to_mask(newaddr, len, &potential_mask);
	slice_dbg(" found potential area at 0x%lx\n", newaddr);
	slice_prपूर्णांक_mask(" mask", &potential_mask);

 convert:
	/*
	 * Try to allocate the context beक्रमe we करो slice convert
	 * so that we handle the context allocation failure gracefully.
	 */
	अगर (need_extra_context(mm, newaddr)) अणु
		अगर (alloc_extended_context(mm, newaddr) < 0)
			वापस -ENOMEM;
	पूर्ण

	slice_andnot_mask(&potential_mask, &potential_mask, &good_mask);
	अगर (compat_maskp && !fixed)
		slice_andnot_mask(&potential_mask, &potential_mask, compat_maskp);
	अगर (potential_mask.low_slices ||
		(SLICE_NUM_HIGH &&
		 !biपंचांगap_empty(potential_mask.high_slices, SLICE_NUM_HIGH))) अणु
		slice_convert(mm, &potential_mask, psize);
		अगर (psize > MMU_PAGE_BASE)
			on_each_cpu(slice_flush_segments, mm, 1);
	पूर्ण
	वापस newaddr;

वापस_addr:
	अगर (need_extra_context(mm, newaddr)) अणु
		अगर (alloc_extended_context(mm, newaddr) < 0)
			वापस -ENOMEM;
	पूर्ण
	वापस newaddr;
पूर्ण
EXPORT_SYMBOL_GPL(slice_get_unmapped_area);

अचिन्हित दीर्घ arch_get_unmapped_area(काष्ठा file *filp,
				     अचिन्हित दीर्घ addr,
				     अचिन्हित दीर्घ len,
				     अचिन्हित दीर्घ pgoff,
				     अचिन्हित दीर्घ flags)
अणु
	वापस slice_get_unmapped_area(addr, len, flags,
				       mm_ctx_user_psize(&current->mm->context), 0);
पूर्ण

अचिन्हित दीर्घ arch_get_unmapped_area_topकरोwn(काष्ठा file *filp,
					     स्थिर अचिन्हित दीर्घ addr0,
					     स्थिर अचिन्हित दीर्घ len,
					     स्थिर अचिन्हित दीर्घ pgoff,
					     स्थिर अचिन्हित दीर्घ flags)
अणु
	वापस slice_get_unmapped_area(addr0, len, flags,
				       mm_ctx_user_psize(&current->mm->context), 1);
पूर्ण

अचिन्हित पूर्णांक notrace get_slice_psize(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr)
अणु
	अचिन्हित अक्षर *psizes;
	पूर्णांक index, mask_index;

	VM_BUG_ON(radix_enabled());

	अगर (slice_addr_is_low(addr)) अणु
		psizes = mm_ctx_low_slices(&mm->context);
		index = GET_LOW_SLICE_INDEX(addr);
	पूर्ण अन्यथा अणु
		psizes = mm_ctx_high_slices(&mm->context);
		index = GET_HIGH_SLICE_INDEX(addr);
	पूर्ण
	mask_index = index & 0x1;
	वापस (psizes[index >> 1] >> (mask_index * 4)) & 0xf;
पूर्ण
EXPORT_SYMBOL_GPL(get_slice_psize);

व्योम slice_init_new_context_exec(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित अक्षर *hpsizes, *lpsizes;
	काष्ठा slice_mask *mask;
	अचिन्हित पूर्णांक psize = mmu_भव_psize;

	slice_dbg("slice_init_new_context_exec(mm=%p)\n", mm);

	/*
	 * In the हाल of exec, use the शेष limit. In the
	 * हाल of विभाजन it is just inherited from the mm being
	 * duplicated.
	 */
	mm_ctx_set_slb_addr_limit(&mm->context, SLB_ADDR_LIMIT_DEFAULT);
	mm_ctx_set_user_psize(&mm->context, psize);

	/*
	 * Set all slice psizes to the शेष.
	 */
	lpsizes = mm_ctx_low_slices(&mm->context);
	स_रखो(lpsizes, (psize << 4) | psize, SLICE_NUM_LOW >> 1);

	hpsizes = mm_ctx_high_slices(&mm->context);
	स_रखो(hpsizes, (psize << 4) | psize, SLICE_NUM_HIGH >> 1);

	/*
	 * Slice mask cache starts zeroed, fill the शेष size cache.
	 */
	mask = slice_mask_क्रम_size(&mm->context, psize);
	mask->low_slices = ~0UL;
	अगर (SLICE_NUM_HIGH)
		biपंचांगap_fill(mask->high_slices, SLICE_NUM_HIGH);
पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3S_64
व्योम slice_setup_new_exec(व्योम)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;

	slice_dbg("slice_setup_new_exec(mm=%p)\n", mm);

	अगर (!is_32bit_task())
		वापस;

	mm_ctx_set_slb_addr_limit(&mm->context, DEFAULT_MAP_WINDOW);
पूर्ण
#पूर्ण_अगर

व्योम slice_set_range_psize(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ start,
			   अचिन्हित दीर्घ len, अचिन्हित पूर्णांक psize)
अणु
	काष्ठा slice_mask mask;

	VM_BUG_ON(radix_enabled());

	slice_range_to_mask(start, len, &mask);
	slice_convert(mm, &mask, psize);
पूर्ण

#अगर_घोषित CONFIG_HUGETLB_PAGE
/*
 * is_hugepage_only_range() is used by generic code to verअगरy whether
 * a normal mmap mapping (non hugetlbfs) is valid on a given area.
 *
 * until the generic code provides a more generic hook and/or starts
 * calling arch get_unmapped_area क्रम MAP_FIXED (which our implementation
 * here knows how to deal with), we hijack it to keep standard mappings
 * away from us.
 *
 * because of that generic code limitation, MAP_FIXED mapping cannot
 * "convert" back a slice with no VMAs to the standard page size, only
 * get_unmapped_area() can. It would be possible to fix it here but I
 * prefer working on fixing the generic code instead.
 *
 * WARNING: This will not work अगर hugetlbfs isn't enabled since the
 * generic code will redefine that function as 0 in that. This is ok
 * क्रम now as we only use slices with hugetlbfs enabled. This should
 * be fixed as the generic code माला_लो fixed.
 */
पूर्णांक slice_is_hugepage_only_range(काष्ठा mm_काष्ठा *mm, अचिन्हित दीर्घ addr,
			   अचिन्हित दीर्घ len)
अणु
	स्थिर काष्ठा slice_mask *maskp;
	अचिन्हित पूर्णांक psize = mm_ctx_user_psize(&mm->context);

	VM_BUG_ON(radix_enabled());

	maskp = slice_mask_क्रम_size(&mm->context, psize);

	/* We need to account क्रम 4k slices too */
	अगर (IS_ENABLED(CONFIG_PPC_64K_PAGES) && psize == MMU_PAGE_64K) अणु
		स्थिर काष्ठा slice_mask *compat_maskp;
		काष्ठा slice_mask available;

		compat_maskp = slice_mask_क्रम_size(&mm->context, MMU_PAGE_4K);
		slice_or_mask(&available, maskp, compat_maskp);
		वापस !slice_check_range_fits(mm, &available, addr, len);
	पूर्ण

	वापस !slice_check_range_fits(mm, maskp, addr, len);
पूर्ण
#पूर्ण_अगर
