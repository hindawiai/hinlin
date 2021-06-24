<शैली गुरु>
/*
 * arch/sh/mm/mmap.c
 *
 * Copyright (C) 2008 - 2009  Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/processor.h>

अचिन्हित दीर्घ shm_align_mask = PAGE_SIZE - 1;	/* Sane caches */
EXPORT_SYMBOL(shm_align_mask);

#अगर_घोषित CONFIG_MMU
/*
 * To aव्योम cache aliases, we map the shared page with same color.
 */
अटल अंतरभूत अचिन्हित दीर्घ COLOUR_ALIGN(अचिन्हित दीर्घ addr,
					 अचिन्हित दीर्घ pgoff)
अणु
	अचिन्हित दीर्घ base = (addr + shm_align_mask) & ~shm_align_mask;
	अचिन्हित दीर्घ off = (pgoff << PAGE_SHIFT) & shm_align_mask;

	वापस base + off;
पूर्ण

अचिन्हित दीर्घ arch_get_unmapped_area(काष्ठा file *filp, अचिन्हित दीर्घ addr,
	अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक करो_colour_align;
	काष्ठा vm_unmapped_area_info info;

	अगर (flags & MAP_FIXED) अणु
		/* We करो not accept a shared mapping अगर it would violate
		 * cache aliasing स्थिरraपूर्णांकs.
		 */
		अगर ((flags & MAP_SHARED) &&
		    ((addr - (pgoff << PAGE_SHIFT)) & shm_align_mask))
			वापस -EINVAL;
		वापस addr;
	पूर्ण

	अगर (unlikely(len > TASK_SIZE))
		वापस -ENOMEM;

	करो_colour_align = 0;
	अगर (filp || (flags & MAP_SHARED))
		करो_colour_align = 1;

	अगर (addr) अणु
		अगर (करो_colour_align)
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
	info.low_limit = TASK_UNMAPPED_BASE;
	info.high_limit = TASK_SIZE;
	info.align_mask = करो_colour_align ? (PAGE_MASK & shm_align_mask) : 0;
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
	पूर्णांक करो_colour_align;
	काष्ठा vm_unmapped_area_info info;

	अगर (flags & MAP_FIXED) अणु
		/* We करो not accept a shared mapping अगर it would violate
		 * cache aliasing स्थिरraपूर्णांकs.
		 */
		अगर ((flags & MAP_SHARED) &&
		    ((addr - (pgoff << PAGE_SHIFT)) & shm_align_mask))
			वापस -EINVAL;
		वापस addr;
	पूर्ण

	अगर (unlikely(len > TASK_SIZE))
		वापस -ENOMEM;

	करो_colour_align = 0;
	अगर (filp || (flags & MAP_SHARED))
		करो_colour_align = 1;

	/* requesting a specअगरic address */
	अगर (addr) अणु
		अगर (करो_colour_align)
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
	info.low_limit = PAGE_SIZE;
	info.high_limit = mm->mmap_base;
	info.align_mask = करो_colour_align ? (PAGE_MASK & shm_align_mask) : 0;
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
		info.low_limit = TASK_UNMAPPED_BASE;
		info.high_limit = TASK_SIZE;
		addr = vm_unmapped_area(&info);
	पूर्ण

	वापस addr;
पूर्ण
#पूर्ण_अगर /* CONFIG_MMU */

/*
 * You really shouldn't be using पढ़ो() or ग_लिखो() on /dev/mem.  This
 * might go away in the future.
 */
पूर्णांक valid_phys_addr_range(phys_addr_t addr, माप_प्रकार count)
अणु
	अगर (addr < __MEMORY_START)
		वापस 0;
	अगर (addr + count > __pa(high_memory))
		वापस 0;

	वापस 1;
पूर्ण

पूर्णांक valid_mmap_phys_addr_range(अचिन्हित दीर्घ pfn, माप_प्रकार size)
अणु
	वापस 1;
पूर्ण
