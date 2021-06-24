<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/arm/mm/mmap.c
 */
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/shm.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/mm.h>
#समावेश <linux/पन.स>
#समावेश <linux/personality.h>
#समावेश <linux/अक्रमom.h>
#समावेश <यंत्र/cachetype.h>

#घोषणा COLOUR_ALIGN(addr,pgoff)		\
	((((addr)+SHMLBA-1)&~(SHMLBA-1)) +	\
	 (((pgoff)<<PAGE_SHIFT) & (SHMLBA-1)))

/*
 * We need to ensure that shared mappings are correctly aligned to
 * aव्योम aliasing issues with VIPT caches.  We need to ensure that
 * a specअगरic page of an object is always mapped at a multiple of
 * SHMLBA bytes.
 *
 * We unconditionally provide this function क्रम all हालs, however
 * in the VIVT हाल, we optimise out the alignment rules.
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
	 * We only need to करो colour alignment अगर either the I or D
	 * caches alias.
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

अचिन्हित दीर्घ
arch_get_unmapped_area_topकरोwn(काष्ठा file *filp, स्थिर अचिन्हित दीर्घ addr0,
			स्थिर अचिन्हित दीर्घ len, स्थिर अचिन्हित दीर्घ pgoff,
			स्थिर अचिन्हित दीर्घ flags)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा mm_काष्ठा *mm = current->mm;
	अचिन्हित दीर्घ addr = addr0;
	पूर्णांक करो_align = 0;
	पूर्णांक aliasing = cache_is_vipt_aliasing();
	काष्ठा vm_unmapped_area_info info;

	/*
	 * We only need to करो colour alignment अगर either the I or D
	 * caches alias.
	 */
	अगर (aliasing)
		करो_align = filp || (flags & MAP_SHARED);

	/* requested length too big क्रम entire address space */
	अगर (len > TASK_SIZE)
		वापस -ENOMEM;

	अगर (flags & MAP_FIXED) अणु
		अगर (aliasing && flags & MAP_SHARED &&
		    (addr - (pgoff << PAGE_SHIFT)) & (SHMLBA - 1))
			वापस -EINVAL;
		वापस addr;
	पूर्ण

	/* requesting a specअगरic address */
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

	info.flags = VM_UNMAPPED_AREA_TOPDOWN;
	info.length = len;
	info.low_limit = FIRST_USER_ADDRESS;
	info.high_limit = mm->mmap_base;
	info.align_mask = करो_align ? (PAGE_MASK & (SHMLBA - 1)) : 0;
	info.align_offset = pgoff << PAGE_SHIFT;
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
		info.low_limit = mm->mmap_base;
		info.high_limit = TASK_SIZE;
		addr = vm_unmapped_area(&info);
	पूर्ण

	वापस addr;
पूर्ण

/*
 * You really shouldn't be using पढ़ो() or ग_लिखो() on /dev/mem.  This
 * might go away in the future.
 */
पूर्णांक valid_phys_addr_range(phys_addr_t addr, माप_प्रकार size)
अणु
	अगर (addr < PHYS_OFFSET)
		वापस 0;
	अगर (addr + size > __pa(high_memory - 1) + 1)
		वापस 0;

	वापस 1;
पूर्ण

/*
 * Do not allow /dev/mem mappings beyond the supported physical range.
 */
पूर्णांक valid_mmap_phys_addr_range(अचिन्हित दीर्घ pfn, माप_प्रकार size)
अणु
	वापस (pfn + (size >> PAGE_SHIFT)) <= (1 + (PHYS_MASK >> PAGE_SHIFT));
पूर्ण
