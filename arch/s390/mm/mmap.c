<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  flexible mmap layout support
 *
 * Copyright 2003-2004 Red Hat Inc., Durham, North Carolina.
 * All Rights Reserved.
 *
 * Started by Ingo Molnar <mingo@elte.hu>
 */

#समावेश <linux/elf-अक्रमomize.h>
#समावेश <linux/personality.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/mm.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/compat.h>
#समावेश <linux/security.h>
#समावेश <यंत्र/elf.h>

अटल अचिन्हित दीर्घ stack_maxअक्रमom_size(व्योम)
अणु
	अगर (!(current->flags & PF_RANDOMIZE))
		वापस 0;
	वापस STACK_RND_MASK << PAGE_SHIFT;
पूर्ण

अटल अंतरभूत पूर्णांक mmap_is_legacy(काष्ठा rlimit *rlim_stack)
अणु
	अगर (current->personality & ADDR_COMPAT_LAYOUT)
		वापस 1;
	अगर (rlim_stack->rlim_cur == RLIM_अनन्त)
		वापस 1;
	वापस sysctl_legacy_va_layout;
पूर्ण

अचिन्हित दीर्घ arch_mmap_rnd(व्योम)
अणु
	वापस (get_अक्रमom_पूर्णांक() & MMAP_RND_MASK) << PAGE_SHIFT;
पूर्ण

अटल अचिन्हित दीर्घ mmap_base_legacy(अचिन्हित दीर्घ rnd)
अणु
	वापस TASK_UNMAPPED_BASE + rnd;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ mmap_base(अचिन्हित दीर्घ rnd,
				      काष्ठा rlimit *rlim_stack)
अणु
	अचिन्हित दीर्घ gap = rlim_stack->rlim_cur;
	अचिन्हित दीर्घ pad = stack_maxअक्रमom_size() + stack_guard_gap;
	अचिन्हित दीर्घ gap_min, gap_max;

	/* Values बंद to RLIM_अनन्त can overflow. */
	अगर (gap + pad > gap)
		gap += pad;

	/*
	 * Top of mmap area (just below the process stack).
	 * Leave at least a ~32 MB hole.
	 */
	gap_min = 32 * 1024 * 1024UL;
	gap_max = (STACK_TOP / 6) * 5;

	अगर (gap < gap_min)
		gap = gap_min;
	अन्यथा अगर (gap > gap_max)
		gap = gap_max;

	वापस PAGE_ALIGN(STACK_TOP - gap - rnd);
पूर्ण

अचिन्हित दीर्घ arch_get_unmapped_area(काष्ठा file *filp, अचिन्हित दीर्घ addr,
				     अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff,
				     अचिन्हित दीर्घ flags)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा vm_unmapped_area_info info;

	अगर (len > TASK_SIZE - mmap_min_addr)
		वापस -ENOMEM;

	अगर (flags & MAP_FIXED)
		जाओ check_asce_limit;

	अगर (addr) अणु
		addr = PAGE_ALIGN(addr);
		vma = find_vma(mm, addr);
		अगर (TASK_SIZE - len >= addr && addr >= mmap_min_addr &&
		    (!vma || addr + len <= vm_start_gap(vma)))
			जाओ check_asce_limit;
	पूर्ण

	info.flags = 0;
	info.length = len;
	info.low_limit = mm->mmap_base;
	info.high_limit = TASK_SIZE;
	अगर (filp || (flags & MAP_SHARED))
		info.align_mask = MMAP_ALIGN_MASK << PAGE_SHIFT;
	अन्यथा
		info.align_mask = 0;
	info.align_offset = pgoff << PAGE_SHIFT;
	addr = vm_unmapped_area(&info);
	अगर (offset_in_page(addr))
		वापस addr;

check_asce_limit:
	वापस check_asce_limit(mm, addr, len);
पूर्ण

अचिन्हित दीर्घ arch_get_unmapped_area_topकरोwn(काष्ठा file *filp, अचिन्हित दीर्घ addr,
					     अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff,
					     अचिन्हित दीर्घ flags)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_unmapped_area_info info;

	/* requested length too big क्रम entire address space */
	अगर (len > TASK_SIZE - mmap_min_addr)
		वापस -ENOMEM;

	अगर (flags & MAP_FIXED)
		जाओ check_asce_limit;

	/* requesting a specअगरic address */
	अगर (addr) अणु
		addr = PAGE_ALIGN(addr);
		vma = find_vma(mm, addr);
		अगर (TASK_SIZE - len >= addr && addr >= mmap_min_addr &&
				(!vma || addr + len <= vm_start_gap(vma)))
			जाओ check_asce_limit;
	पूर्ण

	info.flags = VM_UNMAPPED_AREA_TOPDOWN;
	info.length = len;
	info.low_limit = max(PAGE_SIZE, mmap_min_addr);
	info.high_limit = mm->mmap_base;
	अगर (filp || (flags & MAP_SHARED))
		info.align_mask = MMAP_ALIGN_MASK << PAGE_SHIFT;
	अन्यथा
		info.align_mask = 0;
	info.align_offset = pgoff << PAGE_SHIFT;
	addr = vm_unmapped_area(&info);

	/*
	 * A failed mmap() very likely causes application failure,
	 * so fall back to the bottom-up function here. This scenario
	 * can happen with large stack limits and large mmap()
	 * allocations.
	 */
	अगर (offset_in_page(addr)) अणु
		VM_BUG_ON(addr != -ENOMEM);
		info.flags = 0;
		info.low_limit = TASK_UNMAPPED_BASE;
		info.high_limit = TASK_SIZE;
		addr = vm_unmapped_area(&info);
		अगर (offset_in_page(addr))
			वापस addr;
	पूर्ण

check_asce_limit:
	वापस check_asce_limit(mm, addr, len);
पूर्ण

/*
 * This function, called very early during the creation of a new
 * process VM image, sets up which VM layout function to use:
 */
व्योम arch_pick_mmap_layout(काष्ठा mm_काष्ठा *mm, काष्ठा rlimit *rlim_stack)
अणु
	अचिन्हित दीर्घ अक्रमom_factor = 0UL;

	अगर (current->flags & PF_RANDOMIZE)
		अक्रमom_factor = arch_mmap_rnd();

	/*
	 * Fall back to the standard layout अगर the personality
	 * bit is set, or अगर the expected stack growth is unlimited:
	 */
	अगर (mmap_is_legacy(rlim_stack)) अणु
		mm->mmap_base = mmap_base_legacy(अक्रमom_factor);
		mm->get_unmapped_area = arch_get_unmapped_area;
	पूर्ण अन्यथा अणु
		mm->mmap_base = mmap_base(अक्रमom_factor, rlim_stack);
		mm->get_unmapped_area = arch_get_unmapped_area_topकरोwn;
	पूर्ण
पूर्ण
