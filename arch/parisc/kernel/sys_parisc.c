<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/*
 *    PARISC specअगरic syscalls
 *
 *    Copyright (C) 1999-2003 Matthew Wilcox <willy at parisc-linux.org>
 *    Copyright (C) 2000-2003 Paul Bame <bame at parisc-linux.org>
 *    Copyright (C) 2001 Thomas Bogenकरोerfer <tsbogend at parisc-linux.org>
 *    Copyright (C) 1999-2020 Helge Deller <deller@gmx.de>
 */

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/elf.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/linkage.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/mm.h>
#समावेश <linux/shm.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/utsname.h>
#समावेश <linux/personality.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/compat.h>

/* we स्थिरruct an artअगरicial offset क्रम the mapping based on the physical
 * address of the kernel mapping variable */
#घोषणा GET_LAST_MMAP(filp)		\
	(filp ? ((अचिन्हित दीर्घ) filp->f_mapping) >> 8 : 0UL)
#घोषणा SET_LAST_MMAP(filp, val)	\
	 अणु /* nothing */ पूर्ण

अटल पूर्णांक get_offset(अचिन्हित पूर्णांक last_mmap)
अणु
	वापस (last_mmap & (SHM_COLOUR-1)) >> PAGE_SHIFT;
पूर्ण

अटल अचिन्हित दीर्घ shared_align_offset(अचिन्हित पूर्णांक last_mmap,
					 अचिन्हित दीर्घ pgoff)
अणु
	वापस (get_offset(last_mmap) + pgoff) << PAGE_SHIFT;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ COLOR_ALIGN(अचिन्हित दीर्घ addr,
			 अचिन्हित पूर्णांक last_mmap, अचिन्हित दीर्घ pgoff)
अणु
	अचिन्हित दीर्घ base = (addr+SHM_COLOUR-1) & ~(SHM_COLOUR-1);
	अचिन्हित दीर्घ off  = (SHM_COLOUR-1) &
		(shared_align_offset(last_mmap, pgoff) << PAGE_SHIFT);

	वापस base + off;
पूर्ण


#घोषणा STACK_SIZE_DEFAULT (USER_WIDE_MODE			\
			? (1 << 30)	/* 1 GB */		\
			: (CONFIG_STACK_MAX_DEFAULT_SIZE_MB*1024*1024))

अचिन्हित दीर्घ calc_max_stack_size(अचिन्हित दीर्घ stack_max)
अणु
#अगर_घोषित CONFIG_COMPAT
	अगर (!USER_WIDE_MODE && (stack_max == COMPAT_RLIM_अनन्त))
		stack_max = STACK_SIZE_DEFAULT;
	अन्यथा
#पूर्ण_अगर
	अगर (stack_max == RLIM_अनन्त)
		stack_max = STACK_SIZE_DEFAULT;

	वापस stack_max;
पूर्ण


/*
 * Top of mmap area (just below the process stack).
 */

/*
 * When called from arch_get_unmapped_area(), rlim_stack will be शून्य,
 * indicating that "current" should be used instead of a passed-in
 * value from the exec bprm as करोne with arch_pick_mmap_layout().
 */
अटल अचिन्हित दीर्घ mmap_upper_limit(काष्ठा rlimit *rlim_stack)
अणु
	अचिन्हित दीर्घ stack_base;

	/* Limit stack size - see setup_arg_pages() in fs/exec.c */
	stack_base = rlim_stack ? rlim_stack->rlim_max
				: rlimit_max(RLIMIT_STACK);

	stack_base = calc_max_stack_size(stack_base);

	/* Add space क्रम stack अक्रमomization. */
	अगर (current->flags & PF_RANDOMIZE)
		stack_base += (STACK_RND_MASK << PAGE_SHIFT);

	वापस PAGE_ALIGN(STACK_TOP - stack_base);
पूर्ण


अचिन्हित दीर्घ arch_get_unmapped_area(काष्ठा file *filp, अचिन्हित दीर्घ addr,
		अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा *vma, *prev;
	अचिन्हित दीर्घ task_size = TASK_SIZE;
	पूर्णांक करो_color_align, last_mmap;
	काष्ठा vm_unmapped_area_info info;

	अगर (len > task_size)
		वापस -ENOMEM;

	करो_color_align = 0;
	अगर (filp || (flags & MAP_SHARED))
		करो_color_align = 1;
	last_mmap = GET_LAST_MMAP(filp);

	अगर (flags & MAP_FIXED) अणु
		अगर ((flags & MAP_SHARED) && last_mmap &&
		    (addr - shared_align_offset(last_mmap, pgoff))
				& (SHM_COLOUR - 1))
			वापस -EINVAL;
		जाओ found_addr;
	पूर्ण

	अगर (addr) अणु
		अगर (करो_color_align && last_mmap)
			addr = COLOR_ALIGN(addr, last_mmap, pgoff);
		अन्यथा
			addr = PAGE_ALIGN(addr);

		vma = find_vma_prev(mm, addr, &prev);
		अगर (task_size - len >= addr &&
		    (!vma || addr + len <= vm_start_gap(vma)) &&
		    (!prev || addr >= vm_end_gap(prev)))
			जाओ found_addr;
	पूर्ण

	info.flags = 0;
	info.length = len;
	info.low_limit = mm->mmap_legacy_base;
	info.high_limit = mmap_upper_limit(शून्य);
	info.align_mask = last_mmap ? (PAGE_MASK & (SHM_COLOUR - 1)) : 0;
	info.align_offset = shared_align_offset(last_mmap, pgoff);
	addr = vm_unmapped_area(&info);

found_addr:
	अगर (करो_color_align && !last_mmap && !(addr & ~PAGE_MASK))
		SET_LAST_MMAP(filp, addr - (pgoff << PAGE_SHIFT));

	वापस addr;
पूर्ण

अचिन्हित दीर्घ
arch_get_unmapped_area_topकरोwn(काष्ठा file *filp, स्थिर अचिन्हित दीर्घ addr0,
			  स्थिर अचिन्हित दीर्घ len, स्थिर अचिन्हित दीर्घ pgoff,
			  स्थिर अचिन्हित दीर्घ flags)
अणु
	काष्ठा vm_area_काष्ठा *vma, *prev;
	काष्ठा mm_काष्ठा *mm = current->mm;
	अचिन्हित दीर्घ addr = addr0;
	पूर्णांक करो_color_align, last_mmap;
	काष्ठा vm_unmapped_area_info info;

	/* requested length too big क्रम entire address space */
	अगर (len > TASK_SIZE)
		वापस -ENOMEM;

	करो_color_align = 0;
	अगर (filp || (flags & MAP_SHARED))
		करो_color_align = 1;
	last_mmap = GET_LAST_MMAP(filp);

	अगर (flags & MAP_FIXED) अणु
		अगर ((flags & MAP_SHARED) && last_mmap &&
		    (addr - shared_align_offset(last_mmap, pgoff))
			& (SHM_COLOUR - 1))
			वापस -EINVAL;
		जाओ found_addr;
	पूर्ण

	/* requesting a specअगरic address */
	अगर (addr) अणु
		अगर (करो_color_align && last_mmap)
			addr = COLOR_ALIGN(addr, last_mmap, pgoff);
		अन्यथा
			addr = PAGE_ALIGN(addr);

		vma = find_vma_prev(mm, addr, &prev);
		अगर (TASK_SIZE - len >= addr &&
		    (!vma || addr + len <= vm_start_gap(vma)) &&
		    (!prev || addr >= vm_end_gap(prev)))
			जाओ found_addr;
	पूर्ण

	info.flags = VM_UNMAPPED_AREA_TOPDOWN;
	info.length = len;
	info.low_limit = PAGE_SIZE;
	info.high_limit = mm->mmap_base;
	info.align_mask = last_mmap ? (PAGE_MASK & (SHM_COLOUR - 1)) : 0;
	info.align_offset = shared_align_offset(last_mmap, pgoff);
	addr = vm_unmapped_area(&info);
	अगर (!(addr & ~PAGE_MASK))
		जाओ found_addr;
	VM_BUG_ON(addr != -ENOMEM);

	/*
	 * A failed mmap() very likely causes application failure,
	 * so fall back to the bottom-up function here. This scenario
	 * can happen with large stack limits and large mmap()
	 * allocations.
	 */
	वापस arch_get_unmapped_area(filp, addr0, len, pgoff, flags);

found_addr:
	अगर (करो_color_align && !last_mmap && !(addr & ~PAGE_MASK))
		SET_LAST_MMAP(filp, addr - (pgoff << PAGE_SHIFT));

	वापस addr;
पूर्ण

अटल पूर्णांक mmap_is_legacy(व्योम)
अणु
	अगर (current->personality & ADDR_COMPAT_LAYOUT)
		वापस 1;

	/* parisc stack always grows up - so a unlimited stack should
	 * not be an indicator to use the legacy memory layout.
	 * अगर (rlimit(RLIMIT_STACK) == RLIM_अनन्त)
	 *	वापस 1;
	 */

	वापस sysctl_legacy_va_layout;
पूर्ण

अटल अचिन्हित दीर्घ mmap_rnd(व्योम)
अणु
	अचिन्हित दीर्घ rnd = 0;

	अगर (current->flags & PF_RANDOMIZE)
		rnd = get_अक्रमom_पूर्णांक() & MMAP_RND_MASK;

	वापस rnd << PAGE_SHIFT;
पूर्ण

अचिन्हित दीर्घ arch_mmap_rnd(व्योम)
अणु
	वापस (get_अक्रमom_पूर्णांक() & MMAP_RND_MASK) << PAGE_SHIFT;
पूर्ण

अटल अचिन्हित दीर्घ mmap_legacy_base(व्योम)
अणु
	वापस TASK_UNMAPPED_BASE + mmap_rnd();
पूर्ण

/*
 * This function, called very early during the creation of a new
 * process VM image, sets up which VM layout function to use:
 */
व्योम arch_pick_mmap_layout(काष्ठा mm_काष्ठा *mm, काष्ठा rlimit *rlim_stack)
अणु
	mm->mmap_legacy_base = mmap_legacy_base();
	mm->mmap_base = mmap_upper_limit(rlim_stack);

	अगर (mmap_is_legacy()) अणु
		mm->mmap_base = mm->mmap_legacy_base;
		mm->get_unmapped_area = arch_get_unmapped_area;
	पूर्ण अन्यथा अणु
		mm->get_unmapped_area = arch_get_unmapped_area_topकरोwn;
	पूर्ण
पूर्ण


यंत्रlinkage अचिन्हित दीर्घ sys_mmap2(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
	अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags, अचिन्हित दीर्घ fd,
	अचिन्हित दीर्घ pgoff)
अणु
	/* Make sure the shअगरt क्रम mmap2 is स्थिरant (12), no matter what PAGE_SIZE
	   we have. */
	वापस ksys_mmap_pgoff(addr, len, prot, flags, fd,
			       pgoff >> (PAGE_SHIFT - 12));
पूर्ण

यंत्रlinkage अचिन्हित दीर्घ sys_mmap(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
		अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags, अचिन्हित दीर्घ fd,
		अचिन्हित दीर्घ offset)
अणु
	अगर (!(offset & ~PAGE_MASK)) अणु
		वापस ksys_mmap_pgoff(addr, len, prot, flags, fd,
					offset >> PAGE_SHIFT);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* Fucking broken ABI */

#अगर_घोषित CONFIG_64BIT
यंत्रlinkage दीर्घ parisc_truncate64(स्थिर अक्षर __user * path,
					अचिन्हित पूर्णांक high, अचिन्हित पूर्णांक low)
अणु
	वापस ksys_truncate(path, (दीर्घ)high << 32 | low);
पूर्ण

यंत्रlinkage दीर्घ parisc_ftruncate64(अचिन्हित पूर्णांक fd,
					अचिन्हित पूर्णांक high, अचिन्हित पूर्णांक low)
अणु
	वापस ksys_ftruncate(fd, (दीर्घ)high << 32 | low);
पूर्ण

/* stubs क्रम the benefit of the syscall_table since truncate64 and truncate 
 * are identical on LP64 */
यंत्रlinkage दीर्घ sys_truncate64(स्थिर अक्षर __user * path, अचिन्हित दीर्घ length)
अणु
	वापस ksys_truncate(path, length);
पूर्ण
यंत्रlinkage दीर्घ sys_ftruncate64(अचिन्हित पूर्णांक fd, अचिन्हित दीर्घ length)
अणु
	वापस ksys_ftruncate(fd, length);
पूर्ण
यंत्रlinkage दीर्घ sys_fcntl64(अचिन्हित पूर्णांक fd, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	वापस sys_fcntl(fd, cmd, arg);
पूर्ण
#अन्यथा

यंत्रlinkage दीर्घ parisc_truncate64(स्थिर अक्षर __user * path,
					अचिन्हित पूर्णांक high, अचिन्हित पूर्णांक low)
अणु
	वापस ksys_truncate(path, (loff_t)high << 32 | low);
पूर्ण

यंत्रlinkage दीर्घ parisc_ftruncate64(अचिन्हित पूर्णांक fd,
					अचिन्हित पूर्णांक high, अचिन्हित पूर्णांक low)
अणु
	वापस sys_ftruncate64(fd, (loff_t)high << 32 | low);
पूर्ण
#पूर्ण_अगर

यंत्रlinkage sमाप_प्रकार parisc_pपढ़ो64(अचिन्हित पूर्णांक fd, अक्षर __user *buf, माप_प्रकार count,
					अचिन्हित पूर्णांक high, अचिन्हित पूर्णांक low)
अणु
	वापस ksys_pपढ़ो64(fd, buf, count, (loff_t)high << 32 | low);
पूर्ण

यंत्रlinkage sमाप_प्रकार parisc_pग_लिखो64(अचिन्हित पूर्णांक fd, स्थिर अक्षर __user *buf,
			माप_प्रकार count, अचिन्हित पूर्णांक high, अचिन्हित पूर्णांक low)
अणु
	वापस ksys_pग_लिखो64(fd, buf, count, (loff_t)high << 32 | low);
पूर्ण

यंत्रlinkage sमाप_प्रकार parisc_पढ़ोahead(पूर्णांक fd, अचिन्हित पूर्णांक high, अचिन्हित पूर्णांक low,
		                    माप_प्रकार count)
अणु
	वापस ksys_पढ़ोahead(fd, (loff_t)high << 32 | low, count);
पूर्ण

यंत्रlinkage दीर्घ parisc_fadvise64_64(पूर्णांक fd,
			अचिन्हित पूर्णांक high_off, अचिन्हित पूर्णांक low_off,
			अचिन्हित पूर्णांक high_len, अचिन्हित पूर्णांक low_len, पूर्णांक advice)
अणु
	वापस ksys_fadvise64_64(fd, (loff_t)high_off << 32 | low_off,
			(loff_t)high_len << 32 | low_len, advice);
पूर्ण

यंत्रlinkage दीर्घ parisc_sync_file_range(पूर्णांक fd,
			u32 hi_off, u32 lo_off, u32 hi_nbytes, u32 lo_nbytes,
			अचिन्हित पूर्णांक flags)
अणु
	वापस ksys_sync_file_range(fd, (loff_t)hi_off << 32 | lo_off,
			(loff_t)hi_nbytes << 32 | lo_nbytes, flags);
पूर्ण

यंत्रlinkage दीर्घ parisc_fallocate(पूर्णांक fd, पूर्णांक mode, u32 offhi, u32 offlo,
				u32 lenhi, u32 lenlo)
अणु
	वापस ksys_fallocate(fd, mode, ((u64)offhi << 32) | offlo,
			      ((u64)lenhi << 32) | lenlo);
पूर्ण

दीर्घ parisc_personality(अचिन्हित दीर्घ personality)
अणु
	दीर्घ err;

	अगर (personality(current->personality) == PER_LINUX32
	    && personality(personality) == PER_LINUX)
		personality = (personality & ~PER_MASK) | PER_LINUX32;

	err = sys_personality(personality);
	अगर (personality(err) == PER_LINUX32)
		err = (err & ~PER_MASK) | PER_LINUX;

	वापस err;
पूर्ण

/*
 * Up to kernel v5.9 we defined O_NONBLOCK as 000200004,
 * since then O_NONBLOCK is defined as 000200000.
 *
 * The following wrapper functions mask out the old
 * O_NDELAY bit from calls which use O_NONBLOCK.
 *
 * XXX: Remove those in year 2022 (or later)?
 */

#घोषणा O_NONBLOCK_OLD		000200004
#घोषणा O_NONBLOCK_MASK_OUT	(O_NONBLOCK_OLD & ~O_NONBLOCK)

अटल पूर्णांक FIX_O_NONBLOCK(पूर्णांक flags)
अणु
	अगर (flags & O_NONBLOCK_MASK_OUT) अणु
		काष्ठा task_काष्ठा *tsk = current;
		pr_warn_once("%s(%d) uses a deprecated O_NONBLOCK value.\n",
			tsk->comm, tsk->pid);
	पूर्ण
	वापस flags & ~O_NONBLOCK_MASK_OUT;
पूर्ण

यंत्रlinkage दीर्घ parisc_समयrfd_create(पूर्णांक घड़ीid, पूर्णांक flags)
अणु
	flags = FIX_O_NONBLOCK(flags);
	वापस sys_समयrfd_create(घड़ीid, flags);
पूर्ण

यंत्रlinkage दीर्घ parisc_संकेतfd4(पूर्णांक ufd, sigset_t __user *user_mask,
	माप_प्रकार sizemask, पूर्णांक flags)
अणु
	flags = FIX_O_NONBLOCK(flags);
	वापस sys_संकेतfd4(ufd, user_mask, sizemask, flags);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
यंत्रlinkage दीर्घ parisc_compat_संकेतfd4(पूर्णांक ufd,
	compat_sigset_t __user *user_mask,
	compat_माप_प्रकार sizemask, पूर्णांक flags)
अणु
	flags = FIX_O_NONBLOCK(flags);
	वापस compat_sys_संकेतfd4(ufd, user_mask, sizemask, flags);
पूर्ण
#पूर्ण_अगर

यंत्रlinkage दीर्घ parisc_eventfd2(अचिन्हित पूर्णांक count, पूर्णांक flags)
अणु
	flags = FIX_O_NONBLOCK(flags);
	वापस sys_eventfd2(count, flags);
पूर्ण

यंत्रlinkage दीर्घ parisc_userfaultfd(पूर्णांक flags)
अणु
	flags = FIX_O_NONBLOCK(flags);
	वापस sys_userfaultfd(flags);
पूर्ण

यंत्रlinkage दीर्घ parisc_pipe2(पूर्णांक __user *fildes, पूर्णांक flags)
अणु
	flags = FIX_O_NONBLOCK(flags);
	वापस sys_pipe2(fildes, flags);
पूर्ण

यंत्रlinkage दीर्घ parisc_inotअगरy_init1(पूर्णांक flags)
अणु
	flags = FIX_O_NONBLOCK(flags);
	वापस sys_inotअगरy_init1(flags);
पूर्ण
