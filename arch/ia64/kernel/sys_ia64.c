<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file contains various प्रणाली calls that have dअगरferent calling
 * conventions on dअगरferent platक्रमms.
 *
 * Copyright (C) 1999-2000, 2002-2003, 2005 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/mman.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/shm.h>
#समावेश <linux/file.h>		/* करोh, must come after sched.h... */
#समावेश <linux/smp.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/highuid.h>
#समावेश <linux/hugetlb.h>

#समावेश <यंत्र/shmparam.h>
#समावेश <linux/uaccess.h>

अचिन्हित दीर्घ
arch_get_unmapped_area (काष्ठा file *filp, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
			अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	दीर्घ map_shared = (flags & MAP_SHARED);
	अचिन्हित दीर्घ align_mask = 0;
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_unmapped_area_info info;

	अगर (len > RGN_MAP_LIMIT)
		वापस -ENOMEM;

	/* handle fixed mapping: prevent overlap with huge pages */
	अगर (flags & MAP_FIXED) अणु
		अगर (is_hugepage_only_range(mm, addr, len))
			वापस -EINVAL;
		वापस addr;
	पूर्ण

#अगर_घोषित CONFIG_HUGETLB_PAGE
	अगर (REGION_NUMBER(addr) == RGN_HPAGE)
		addr = 0;
#पूर्ण_अगर
	अगर (!addr)
		addr = TASK_UNMAPPED_BASE;

	अगर (map_shared && (TASK_SIZE > 0xfffffffful))
		/*
		 * For 64-bit tasks, align shared segments to 1MB to aव्योम potential
		 * perक्रमmance penalty due to भव aliasing (see ASDM).  For 32-bit
		 * tasks, we prefer to aव्योम exhausting the address space too quickly by
		 * limiting alignment to a single page.
		 */
		align_mask = PAGE_MASK & (SHMLBA - 1);

	info.flags = 0;
	info.length = len;
	info.low_limit = addr;
	info.high_limit = TASK_SIZE;
	info.align_mask = align_mask;
	info.align_offset = 0;
	वापस vm_unmapped_area(&info);
पूर्ण

यंत्रlinkage दीर्घ
ia64_getpriority (पूर्णांक which, पूर्णांक who)
अणु
	दीर्घ prio;

	prio = sys_getpriority(which, who);
	अगर (prio >= 0) अणु
		क्रमce_successful_syscall_वापस();
		prio = 20 - prio;
	पूर्ण
	वापस prio;
पूर्ण

/* XXX obsolete, but leave it here until the old libc is gone... */
यंत्रlinkage अचिन्हित दीर्घ
sys_getpagesize (व्योम)
अणु
	वापस PAGE_SIZE;
पूर्ण

यंत्रlinkage अचिन्हित दीर्घ
ia64_brk (अचिन्हित दीर्घ brk)
अणु
	अचिन्हित दीर्घ retval = sys_brk(brk);
	क्रमce_successful_syscall_वापस();
	वापस retval;
पूर्ण

/*
 * On IA-64, we वापस the two file descriptors in ret0 and ret1 (r8
 * and r9) as this is faster than करोing a copy_to_user().
 */
यंत्रlinkage दीर्घ
sys_ia64_pipe (व्योम)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(current);
	पूर्णांक fd[2];
	पूर्णांक retval;

	retval = करो_pipe_flags(fd, 0);
	अगर (retval)
		जाओ out;
	retval = fd[0];
	regs->r9 = fd[1];
  out:
	वापस retval;
पूर्ण

पूर्णांक ia64_mmap_check(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len,
		अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ roff;

	/*
	 * Don't permit mappings पूर्णांकo unmapped space, the भव page table
	 * of a region, or across a region boundary.  Note: RGN_MAP_LIMIT is
	 * equal to 2^n-PAGE_SIZE (क्रम some पूर्णांकeger n <= 61) and len > 0.
	 */
	roff = REGION_OFFSET(addr);
	अगर ((len > RGN_MAP_LIMIT) || (roff > (RGN_MAP_LIMIT - len)))
		वापस -EINVAL;
	वापस 0;
पूर्ण

/*
 * mmap2() is like mmap() except that the offset is expressed in units
 * of PAGE_SIZE (instead of bytes).  This allows to mmap2() (pieces
 * of) files that are larger than the address space of the CPU.
 */
यंत्रlinkage अचिन्हित दीर्घ
sys_mmap2 (अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len, पूर्णांक prot, पूर्णांक flags, पूर्णांक fd, दीर्घ pgoff)
अणु
	addr = ksys_mmap_pgoff(addr, len, prot, flags, fd, pgoff);
	अगर (!IS_ERR((व्योम *) addr))
		क्रमce_successful_syscall_वापस();
	वापस addr;
पूर्ण

यंत्रlinkage अचिन्हित दीर्घ
sys_mmap (अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len, पूर्णांक prot, पूर्णांक flags, पूर्णांक fd, दीर्घ off)
अणु
	अगर (offset_in_page(off) != 0)
		वापस -EINVAL;

	addr = ksys_mmap_pgoff(addr, len, prot, flags, fd, off >> PAGE_SHIFT);
	अगर (!IS_ERR((व्योम *) addr))
		क्रमce_successful_syscall_वापस();
	वापस addr;
पूर्ण

यंत्रlinkage अचिन्हित दीर्घ
ia64_mremap (अचिन्हित दीर्घ addr, अचिन्हित दीर्घ old_len, अचिन्हित दीर्घ new_len, अचिन्हित दीर्घ flags,
	     अचिन्हित दीर्घ new_addr)
अणु
	addr = sys_mremap(addr, old_len, new_len, flags, new_addr);
	अगर (!IS_ERR((व्योम *) addr))
		क्रमce_successful_syscall_वापस();
	वापस addr;
पूर्ण
