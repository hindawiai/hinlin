<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  flexible mmap layout support
 *
 * Copyright 2003-2004 Red Hat Inc., Durham, North Carolina.
 * All Rights Reserved.
 *
 * Started by Ingo Molnar <mingo@elte.hu>
 */

#समावेश <linux/personality.h>
#समावेश <linux/mm.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/mm.h>
#समावेश <linux/elf-अक्रमomize.h>
#समावेश <linux/security.h>
#समावेश <linux/mman.h>

/*
 * Top of mmap area (just below the process stack).
 *
 * Leave at least a ~128 MB hole.
 */
#घोषणा MIN_GAP (128*1024*1024)
#घोषणा MAX_GAP (TASK_SIZE/6*5)

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
	अचिन्हित दीर्घ shअगरt, rnd;

	shअगरt = mmap_rnd_bits;
#अगर_घोषित CONFIG_COMPAT
	अगर (is_32bit_task())
		shअगरt = mmap_rnd_compat_bits;
#पूर्ण_अगर
	rnd = get_अक्रमom_दीर्घ() % (1ul << shअगरt);

	वापस rnd << PAGE_SHIFT;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ stack_maxअक्रमom_size(व्योम)
अणु
	अगर (!(current->flags & PF_RANDOMIZE))
		वापस 0;

	/* 8MB क्रम 32bit, 1GB क्रम 64bit */
	अगर (is_32bit_task())
		वापस (1<<23);
	अन्यथा
		वापस (1<<30);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ mmap_base(अचिन्हित दीर्घ rnd,
				      काष्ठा rlimit *rlim_stack)
अणु
	अचिन्हित दीर्घ gap = rlim_stack->rlim_cur;
	अचिन्हित दीर्घ pad = stack_maxअक्रमom_size() + stack_guard_gap;

	/* Values बंद to RLIM_अनन्त can overflow. */
	अगर (gap + pad > gap)
		gap += pad;

	अगर (gap < MIN_GAP)
		gap = MIN_GAP;
	अन्यथा अगर (gap > MAX_GAP)
		gap = MAX_GAP;

	वापस PAGE_ALIGN(DEFAULT_MAP_WINDOW - gap - rnd);
पूर्ण

#अगर_घोषित CONFIG_PPC_RADIX_MMU
/*
 * Same function as generic code used only क्रम radix, because we करोn't need to overload
 * the generic one. But we will have to duplicate, because hash select
 * HAVE_ARCH_UNMAPPED_AREA
 */
अटल अचिन्हित दीर्घ
radix__arch_get_unmapped_area(काष्ठा file *filp, अचिन्हित दीर्घ addr,
			     अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff,
			     अचिन्हित दीर्घ flags)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma;
	पूर्णांक fixed = (flags & MAP_FIXED);
	अचिन्हित दीर्घ high_limit;
	काष्ठा vm_unmapped_area_info info;

	high_limit = DEFAULT_MAP_WINDOW;
	अगर (addr >= high_limit || (fixed && (addr + len > high_limit)))
		high_limit = TASK_SIZE;

	अगर (len > high_limit)
		वापस -ENOMEM;

	अगर (fixed) अणु
		अगर (addr > high_limit - len)
			वापस -ENOMEM;
		वापस addr;
	पूर्ण

	अगर (addr) अणु
		addr = PAGE_ALIGN(addr);
		vma = find_vma(mm, addr);
		अगर (high_limit - len >= addr && addr >= mmap_min_addr &&
		    (!vma || addr + len <= vm_start_gap(vma)))
			वापस addr;
	पूर्ण

	info.flags = 0;
	info.length = len;
	info.low_limit = mm->mmap_base;
	info.high_limit = high_limit;
	info.align_mask = 0;

	वापस vm_unmapped_area(&info);
पूर्ण

अटल अचिन्हित दीर्घ
radix__arch_get_unmapped_area_topकरोwn(काष्ठा file *filp,
				     स्थिर अचिन्हित दीर्घ addr0,
				     स्थिर अचिन्हित दीर्घ len,
				     स्थिर अचिन्हित दीर्घ pgoff,
				     स्थिर अचिन्हित दीर्घ flags)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा mm_काष्ठा *mm = current->mm;
	अचिन्हित दीर्घ addr = addr0;
	पूर्णांक fixed = (flags & MAP_FIXED);
	अचिन्हित दीर्घ high_limit;
	काष्ठा vm_unmapped_area_info info;

	high_limit = DEFAULT_MAP_WINDOW;
	अगर (addr >= high_limit || (fixed && (addr + len > high_limit)))
		high_limit = TASK_SIZE;

	अगर (len > high_limit)
		वापस -ENOMEM;

	अगर (fixed) अणु
		अगर (addr > high_limit - len)
			वापस -ENOMEM;
		वापस addr;
	पूर्ण

	अगर (addr) अणु
		addr = PAGE_ALIGN(addr);
		vma = find_vma(mm, addr);
		अगर (high_limit - len >= addr && addr >= mmap_min_addr &&
		    (!vma || addr + len <= vm_start_gap(vma)))
			वापस addr;
	पूर्ण

	info.flags = VM_UNMAPPED_AREA_TOPDOWN;
	info.length = len;
	info.low_limit = max(PAGE_SIZE, mmap_min_addr);
	info.high_limit = mm->mmap_base + (high_limit - DEFAULT_MAP_WINDOW);
	info.align_mask = 0;

	addr = vm_unmapped_area(&info);
	अगर (!(addr & ~PAGE_MASK))
		वापस addr;
	VM_BUG_ON(addr != -ENOMEM);

	/*
	 * A failed mmap() very likely causes application failure,
	 * so fall back to the bottom-up function here. This scenario
	 * can happen with large stack limits and large mmap()
	 * allocations.
	 */
	वापस radix__arch_get_unmapped_area(filp, addr0, len, pgoff, flags);
पूर्ण

अटल व्योम radix__arch_pick_mmap_layout(काष्ठा mm_काष्ठा *mm,
					अचिन्हित दीर्घ अक्रमom_factor,
					काष्ठा rlimit *rlim_stack)
अणु
	अगर (mmap_is_legacy(rlim_stack)) अणु
		mm->mmap_base = TASK_UNMAPPED_BASE;
		mm->get_unmapped_area = radix__arch_get_unmapped_area;
	पूर्ण अन्यथा अणु
		mm->mmap_base = mmap_base(अक्रमom_factor, rlim_stack);
		mm->get_unmapped_area = radix__arch_get_unmapped_area_topकरोwn;
	पूर्ण
पूर्ण
#अन्यथा
/* dummy */
बाह्य व्योम radix__arch_pick_mmap_layout(काष्ठा mm_काष्ठा *mm,
					अचिन्हित दीर्घ अक्रमom_factor,
					काष्ठा rlimit *rlim_stack);
#पूर्ण_अगर
/*
 * This function, called very early during the creation of a new
 * process VM image, sets up which VM layout function to use:
 */
व्योम arch_pick_mmap_layout(काष्ठा mm_काष्ठा *mm, काष्ठा rlimit *rlim_stack)
अणु
	अचिन्हित दीर्घ अक्रमom_factor = 0UL;

	अगर (current->flags & PF_RANDOMIZE)
		अक्रमom_factor = arch_mmap_rnd();

	अगर (radix_enabled())
		वापस radix__arch_pick_mmap_layout(mm, अक्रमom_factor,
						    rlim_stack);
	/*
	 * Fall back to the standard layout अगर the personality
	 * bit is set, or अगर the expected stack growth is unlimited:
	 */
	अगर (mmap_is_legacy(rlim_stack)) अणु
		mm->mmap_base = TASK_UNMAPPED_BASE;
		mm->get_unmapped_area = arch_get_unmapped_area;
	पूर्ण अन्यथा अणु
		mm->mmap_base = mmap_base(अक्रमom_factor, rlim_stack);
		mm->get_unmapped_area = arch_get_unmapped_area_topकरोwn;
	पूर्ण
पूर्ण
