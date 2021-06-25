<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ARC700 mmap
 *
 * (started from arm version - क्रम VIPT alias handling)
 *
 * Copyright (C) 2013 Synopsys, Inc. (www.synopsys.com)
 */

#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/sched/mm.h>

#समावेश <यंत्र/cacheflush.h>

#घोषणा COLOUR_ALIGN(addr, pgoff)			\
	((((addr) + SHMLBA - 1) & ~(SHMLBA - 1)) +	\
	 (((pgoff) << PAGE_SHIFT) & (SHMLBA - 1)))

/*
 * Ensure that shared mappings are correctly aligned to
 * aव्योम aliasing issues with VIPT caches.
 * We need to ensure that
 * a specअगरic page of an object is always mapped at a multiple of
 * SHMLBA bytes.
 */
अचिन्हित दीर्घ
arch_get_unmapped_area(काष्ठा file *filp, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक करो_align = 0;
	पूर्णांक aliasing = cache_is_vipt_aliasing();
	काष्ठा vm_unmapped_area_info info;

	/*
	 * We only need to करो colour alignment अगर D cache aliases.
	 */
	अगर (aliasing)
		करो_align = filp || (flags & MAP_SHARED);

	/*
	 * We enक्रमce the MAP_FIXED हाल.
	 */
	अगर (flags & MAP_FIXED) अणु
		अगर (aliasing && flags & MAP_SHARED &&
		    (addr - (pgoff << PAGE_SHIFT)) & (SHMLBA - 1))
			वापस -EINVAL;
		वापस addr;
	पूर्ण

	अगर (len > TASK_SIZE)
		वापस -ENOMEM;

	अगर (addr) अणु
		अगर (करो_align)
			addr = COLOUR_ALIGN(addr, pgoff);
		अन्यथा
			addr = PAGE_ALIGN(addr);

		vma = find_vma(mm, addr);
		अगर (TASK_SIZE - len >= addr &&
		    (!vma || addr + len <= vm_start_gap(vma)))
			वापस addr;
	पूर्ण

	info.flags = 0;
	info.length = len;
	info.low_limit = mm->mmap_base;
	info.high_limit = TASK_SIZE;
	info.align_mask = करो_align ? (PAGE_MASK & (SHMLBA - 1)) : 0;
	info.align_offset = pgoff << PAGE_SHIFT;
	वापस vm_unmapped_area(&info);
पूर्ण
