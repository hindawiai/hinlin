<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2011 Wind River Systems,
 *   written by Ralf Baechle <ralf@linux-mips.org>
 */
#समावेश <linux/compiler.h>
#समावेश <linux/elf-अक्रमomize.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/export.h>
#समावेश <linux/personality.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/mm.h>

अचिन्हित दीर्घ shm_align_mask = PAGE_SIZE - 1;	/* Sane caches */
EXPORT_SYMBOL(shm_align_mask);

#घोषणा COLOUR_ALIGN(addr, pgoff)				\
	((((addr) + shm_align_mask) & ~shm_align_mask) +	\
	 (((pgoff) << PAGE_SHIFT) & shm_align_mask))

क्रमागत mmap_allocation_direction अणुUP, DOWNपूर्ण;

अटल अचिन्हित दीर्घ arch_get_unmapped_area_common(काष्ठा file *filp,
	अचिन्हित दीर्घ addr0, अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff,
	अचिन्हित दीर्घ flags, क्रमागत mmap_allocation_direction dir)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	अचिन्हित दीर्घ addr = addr0;
	पूर्णांक करो_color_align;
	काष्ठा vm_unmapped_area_info info;

	अगर (unlikely(len > TASK_SIZE))
		वापस -ENOMEM;

	अगर (flags & MAP_FIXED) अणु
		/* Even MAP_FIXED mappings must reside within TASK_SIZE */
		अगर (TASK_SIZE - len < addr)
			वापस -EINVAL;

		/*
		 * We करो not accept a shared mapping अगर it would violate
		 * cache aliasing स्थिरraपूर्णांकs.
		 */
		अगर ((flags & MAP_SHARED) &&
		    ((addr - (pgoff << PAGE_SHIFT)) & shm_align_mask))
			वापस -EINVAL;
		वापस addr;
	पूर्ण

	करो_color_align = 0;
	अगर (filp || (flags & MAP_SHARED))
		करो_color_align = 1;

	/* requesting a specअगरic address */
	अगर (addr) अणु
		अगर (करो_color_align)
			addr = COLOUR_ALIGN(addr, pgoff);
		अन्यथा
			addr = PAGE_ALIGN(addr);

		vma = find_vma(mm, addr);
		अगर (TASK_SIZE - len >= addr &&
		    (!vma || addr + len <= vm_start_gap(vma)))
			वापस addr;
	पूर्ण

	info.length = len;
	info.align_mask = करो_color_align ? (PAGE_MASK & shm_align_mask) : 0;
	info.align_offset = pgoff << PAGE_SHIFT;

	अगर (dir == DOWN) अणु
		info.flags = VM_UNMAPPED_AREA_TOPDOWN;
		info.low_limit = PAGE_SIZE;
		info.high_limit = mm->mmap_base;
		addr = vm_unmapped_area(&info);

		अगर (!(addr & ~PAGE_MASK))
			वापस addr;

		/*
		 * A failed mmap() very likely causes application failure,
		 * so fall back to the bottom-up function here. This scenario
		 * can happen with large stack limits and large mmap()
		 * allocations.
		 */
	पूर्ण

	info.flags = 0;
	info.low_limit = mm->mmap_base;
	info.high_limit = TASK_SIZE;
	वापस vm_unmapped_area(&info);
पूर्ण

अचिन्हित दीर्घ arch_get_unmapped_area(काष्ठा file *filp, अचिन्हित दीर्घ addr0,
	अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	वापस arch_get_unmapped_area_common(filp,
			addr0, len, pgoff, flags, UP);
पूर्ण

/*
 * There is no need to export this but sched.h declares the function as
 * बाह्य so making it अटल here results in an error.
 */
अचिन्हित दीर्घ arch_get_unmapped_area_topकरोwn(काष्ठा file *filp,
	अचिन्हित दीर्घ addr0, अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff,
	अचिन्हित दीर्घ flags)
अणु
	वापस arch_get_unmapped_area_common(filp,
			addr0, len, pgoff, flags, DOWN);
पूर्ण

bool __virt_addr_valid(स्थिर अस्थिर व्योम *kaddr)
अणु
	अचिन्हित दीर्घ vaddr = (अचिन्हित दीर्घ)kaddr;

	अगर ((vaddr < PAGE_OFFSET) || (vaddr >= MAP_BASE))
		वापस false;

	वापस pfn_valid(PFN_DOWN(virt_to_phys(kaddr)));
पूर्ण
EXPORT_SYMBOL_GPL(__virt_addr_valid);
