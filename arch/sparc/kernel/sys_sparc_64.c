<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* linux/arch/sparc64/kernel/sys_sparc.c
 *
 * This file contains various अक्रमom प्रणाली calls that
 * have a non-standard calling sequence on the Linux/sparc
 * platक्रमm.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/mm.h>
#समावेश <linux/sem.h>
#समावेश <linux/msg.h>
#समावेश <linux/shm.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/mman.h>
#समावेश <linux/utsname.h>
#समावेश <linux/smp.h>
#समावेश <linux/slab.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/ipc.h>
#समावेश <linux/personality.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/export.h>
#समावेश <linux/context_tracking.h>
#समावेश <linux/समयx.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/utrap.h>
#समावेश <यंत्र/unistd.h>

#समावेश "entry.h"
#समावेश "kernel.h"
#समावेश "systbls.h"

/* #घोषणा DEBUG_UNIMP_SYSCALL */

SYSCALL_DEFINE0(getpagesize)
अणु
	वापस PAGE_SIZE;
पूर्ण

/* Does addr --> addr+len fall within 4GB of the VA-space hole or
 * overflow past the end of the 64-bit address space?
 */
अटल अंतरभूत पूर्णांक invalid_64bit_range(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len)
अणु
	अचिन्हित दीर्घ va_exclude_start, va_exclude_end;

	va_exclude_start = VA_EXCLUDE_START;
	va_exclude_end   = VA_EXCLUDE_END;

	अगर (unlikely(len >= va_exclude_start))
		वापस 1;

	अगर (unlikely((addr + len) < addr))
		वापस 1;

	अगर (unlikely((addr >= va_exclude_start && addr < va_exclude_end) ||
		     ((addr + len) >= va_exclude_start &&
		      (addr + len) < va_exclude_end)))
		वापस 1;

	वापस 0;
पूर्ण

/* These functions dअगरfer from the शेष implementations in
 * mm/mmap.c in two ways:
 *
 * 1) For file backed MAP_SHARED mmap()'s we D-cache color align,
 *    क्रम fixed such mappings we just validate what the user gave us.
 * 2) For 64-bit tasks we aव्योम mapping anything within 4GB of
 *    the spitfire/niagara VA-hole.
 */

अटल अंतरभूत अचिन्हित दीर्घ COLOR_ALIGN(अचिन्हित दीर्घ addr,
					 अचिन्हित दीर्घ pgoff)
अणु
	अचिन्हित दीर्घ base = (addr+SHMLBA-1)&~(SHMLBA-1);
	अचिन्हित दीर्घ off = (pgoff<<PAGE_SHIFT) & (SHMLBA-1);

	वापस base + off;
पूर्ण

अचिन्हित दीर्घ arch_get_unmapped_area(काष्ठा file *filp, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	काष्ठा mm_काष्ठा *mm = current->mm;
	काष्ठा vm_area_काष्ठा * vma;
	अचिन्हित दीर्घ task_size = TASK_SIZE;
	पूर्णांक करो_color_align;
	काष्ठा vm_unmapped_area_info info;

	अगर (flags & MAP_FIXED) अणु
		/* We करो not accept a shared mapping अगर it would violate
		 * cache aliasing स्थिरraपूर्णांकs.
		 */
		अगर ((flags & MAP_SHARED) &&
		    ((addr - (pgoff << PAGE_SHIFT)) & (SHMLBA - 1)))
			वापस -EINVAL;
		वापस addr;
	पूर्ण

	अगर (test_thपढ़ो_flag(TIF_32BIT))
		task_size = STACK_TOP32;
	अगर (unlikely(len > task_size || len >= VA_EXCLUDE_START))
		वापस -ENOMEM;

	करो_color_align = 0;
	अगर (filp || (flags & MAP_SHARED))
		करो_color_align = 1;

	अगर (addr) अणु
		अगर (करो_color_align)
			addr = COLOR_ALIGN(addr, pgoff);
		अन्यथा
			addr = PAGE_ALIGN(addr);

		vma = find_vma(mm, addr);
		अगर (task_size - len >= addr &&
		    (!vma || addr + len <= vm_start_gap(vma)))
			वापस addr;
	पूर्ण

	info.flags = 0;
	info.length = len;
	info.low_limit = TASK_UNMAPPED_BASE;
	info.high_limit = min(task_size, VA_EXCLUDE_START);
	info.align_mask = करो_color_align ? (PAGE_MASK & (SHMLBA - 1)) : 0;
	info.align_offset = pgoff << PAGE_SHIFT;
	addr = vm_unmapped_area(&info);

	अगर ((addr & ~PAGE_MASK) && task_size > VA_EXCLUDE_END) अणु
		VM_BUG_ON(addr != -ENOMEM);
		info.low_limit = VA_EXCLUDE_END;
		info.high_limit = task_size;
		addr = vm_unmapped_area(&info);
	पूर्ण

	वापस addr;
पूर्ण

अचिन्हित दीर्घ
arch_get_unmapped_area_topकरोwn(काष्ठा file *filp, स्थिर अचिन्हित दीर्घ addr0,
			  स्थिर अचिन्हित दीर्घ len, स्थिर अचिन्हित दीर्घ pgoff,
			  स्थिर अचिन्हित दीर्घ flags)
अणु
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा mm_काष्ठा *mm = current->mm;
	अचिन्हित दीर्घ task_size = STACK_TOP32;
	अचिन्हित दीर्घ addr = addr0;
	पूर्णांक करो_color_align;
	काष्ठा vm_unmapped_area_info info;

	/* This should only ever run क्रम 32-bit processes.  */
	BUG_ON(!test_thपढ़ो_flag(TIF_32BIT));

	अगर (flags & MAP_FIXED) अणु
		/* We करो not accept a shared mapping अगर it would violate
		 * cache aliasing स्थिरraपूर्णांकs.
		 */
		अगर ((flags & MAP_SHARED) &&
		    ((addr - (pgoff << PAGE_SHIFT)) & (SHMLBA - 1)))
			वापस -EINVAL;
		वापस addr;
	पूर्ण

	अगर (unlikely(len > task_size))
		वापस -ENOMEM;

	करो_color_align = 0;
	अगर (filp || (flags & MAP_SHARED))
		करो_color_align = 1;

	/* requesting a specअगरic address */
	अगर (addr) अणु
		अगर (करो_color_align)
			addr = COLOR_ALIGN(addr, pgoff);
		अन्यथा
			addr = PAGE_ALIGN(addr);

		vma = find_vma(mm, addr);
		अगर (task_size - len >= addr &&
		    (!vma || addr + len <= vm_start_gap(vma)))
			वापस addr;
	पूर्ण

	info.flags = VM_UNMAPPED_AREA_TOPDOWN;
	info.length = len;
	info.low_limit = PAGE_SIZE;
	info.high_limit = mm->mmap_base;
	info.align_mask = करो_color_align ? (PAGE_MASK & (SHMLBA - 1)) : 0;
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
		info.high_limit = STACK_TOP32;
		addr = vm_unmapped_area(&info);
	पूर्ण

	वापस addr;
पूर्ण

/* Try to align mapping such that we align it as much as possible. */
अचिन्हित दीर्घ get_fb_unmapped_area(काष्ठा file *filp, अचिन्हित दीर्घ orig_addr, अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ align_goal, addr = -ENOMEM;
	अचिन्हित दीर्घ (*get_area)(काष्ठा file *, अचिन्हित दीर्घ,
				  अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ);

	get_area = current->mm->get_unmapped_area;

	अगर (flags & MAP_FIXED) अणु
		/* Ok, करोn't mess with it. */
		वापस get_area(शून्य, orig_addr, len, pgoff, flags);
	पूर्ण
	flags &= ~MAP_SHARED;

	align_goal = PAGE_SIZE;
	अगर (len >= (4UL * 1024 * 1024))
		align_goal = (4UL * 1024 * 1024);
	अन्यथा अगर (len >= (512UL * 1024))
		align_goal = (512UL * 1024);
	अन्यथा अगर (len >= (64UL * 1024))
		align_goal = (64UL * 1024);

	करो अणु
		addr = get_area(शून्य, orig_addr, len + (align_goal - PAGE_SIZE), pgoff, flags);
		अगर (!(addr & ~PAGE_MASK)) अणु
			addr = (addr + (align_goal - 1UL)) & ~(align_goal - 1UL);
			अवरोध;
		पूर्ण

		अगर (align_goal == (4UL * 1024 * 1024))
			align_goal = (512UL * 1024);
		अन्यथा अगर (align_goal == (512UL * 1024))
			align_goal = (64UL * 1024);
		अन्यथा
			align_goal = PAGE_SIZE;
	पूर्ण जबतक ((addr & ~PAGE_MASK) && align_goal > PAGE_SIZE);

	/* Mapping is smaller than 64K or larger areas could not
	 * be obtained.
	 */
	अगर (addr & ~PAGE_MASK)
		addr = get_area(शून्य, orig_addr, len, pgoff, flags);

	वापस addr;
पूर्ण
EXPORT_SYMBOL(get_fb_unmapped_area);

/* Essentially the same as PowerPC.  */
अटल अचिन्हित दीर्घ mmap_rnd(व्योम)
अणु
	अचिन्हित दीर्घ rnd = 0UL;

	अगर (current->flags & PF_RANDOMIZE) अणु
		अचिन्हित दीर्घ val = get_अक्रमom_दीर्घ();
		अगर (test_thपढ़ो_flag(TIF_32BIT))
			rnd = (val % (1UL << (23UL-PAGE_SHIFT)));
		अन्यथा
			rnd = (val % (1UL << (30UL-PAGE_SHIFT)));
	पूर्ण
	वापस rnd << PAGE_SHIFT;
पूर्ण

व्योम arch_pick_mmap_layout(काष्ठा mm_काष्ठा *mm, काष्ठा rlimit *rlim_stack)
अणु
	अचिन्हित दीर्घ अक्रमom_factor = mmap_rnd();
	अचिन्हित दीर्घ gap;

	/*
	 * Fall back to the standard layout अगर the personality
	 * bit is set, or अगर the expected stack growth is unlimited:
	 */
	gap = rlim_stack->rlim_cur;
	अगर (!test_thपढ़ो_flag(TIF_32BIT) ||
	    (current->personality & ADDR_COMPAT_LAYOUT) ||
	    gap == RLIM_अनन्त ||
	    sysctl_legacy_va_layout) अणु
		mm->mmap_base = TASK_UNMAPPED_BASE + अक्रमom_factor;
		mm->get_unmapped_area = arch_get_unmapped_area;
	पूर्ण अन्यथा अणु
		/* We know it's 32-bit */
		अचिन्हित दीर्घ task_size = STACK_TOP32;

		अगर (gap < 128 * 1024 * 1024)
			gap = 128 * 1024 * 1024;
		अगर (gap > (task_size / 6 * 5))
			gap = (task_size / 6 * 5);

		mm->mmap_base = PAGE_ALIGN(task_size - gap - अक्रमom_factor);
		mm->get_unmapped_area = arch_get_unmapped_area_topकरोwn;
	पूर्ण
पूर्ण

/*
 * sys_pipe() is the normal C calling standard क्रम creating
 * a pipe. It's not the way unix traditionally करोes this, though.
 */
SYSCALL_DEFINE0(sparc_pipe)
अणु
	पूर्णांक fd[2];
	पूर्णांक error;

	error = करो_pipe_flags(fd, 0);
	अगर (error)
		जाओ out;
	current_pt_regs()->u_regs[UREG_I1] = fd[1];
	error = fd[0];
out:
	वापस error;
पूर्ण

/*
 * sys_ipc() is the de-multiplexer क्रम the SysV IPC calls..
 *
 * This is really horribly ugly.
 */

SYSCALL_DEFINE6(sparc_ipc, अचिन्हित पूर्णांक, call, पूर्णांक, first, अचिन्हित दीर्घ, second,
		अचिन्हित दीर्घ, third, व्योम __user *, ptr, दीर्घ, fअगरth)
अणु
	दीर्घ err;

	अगर (!IS_ENABLED(CONFIG_SYSVIPC))
		वापस -ENOSYS;

	/* No need क्रम backward compatibility. We can start fresh... */
	अगर (call <= SEMTIMEDOP) अणु
		चयन (call) अणु
		हाल SEMOP:
			err = ksys_semसमयकरोp(first, ptr,
					      (अचिन्हित पूर्णांक)second, शून्य);
			जाओ out;
		हाल SEMTIMEDOP:
			err = ksys_semसमयकरोp(first, ptr, (अचिन्हित पूर्णांक)second,
				(स्थिर काष्ठा __kernel_बारpec __user *)
					      (अचिन्हित दीर्घ) fअगरth);
			जाओ out;
		हाल SEMGET:
			err = ksys_semget(first, (पूर्णांक)second, (पूर्णांक)third);
			जाओ out;
		हाल SEMCTL: अणु
			err = ksys_old_semctl(first, second,
					      (पूर्णांक)third | IPC_64,
					      (अचिन्हित दीर्घ) ptr);
			जाओ out;
		पूर्ण
		शेष:
			err = -ENOSYS;
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (call <= MSGCTL) अणु
		चयन (call) अणु
		हाल MSGSND:
			err = ksys_msgsnd(first, ptr, (माप_प्रकार)second,
					 (पूर्णांक)third);
			जाओ out;
		हाल MSGRCV:
			err = ksys_msgrcv(first, ptr, (माप_प्रकार)second, fअगरth,
					 (पूर्णांक)third);
			जाओ out;
		हाल MSGGET:
			err = ksys_msgget((key_t)first, (पूर्णांक)second);
			जाओ out;
		हाल MSGCTL:
			err = ksys_old_msgctl(first, (पूर्णांक)second | IPC_64, ptr);
			जाओ out;
		शेष:
			err = -ENOSYS;
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (call <= SHMCTL) अणु
		चयन (call) अणु
		हाल SHMAT: अणु
			uदीर्घ raddr;
			err = करो_shmat(first, ptr, (पूर्णांक)second, &raddr, SHMLBA);
			अगर (!err) अणु
				अगर (put_user(raddr,
					     (uदीर्घ __user *) third))
					err = -EFAULT;
			पूर्ण
			जाओ out;
		पूर्ण
		हाल SHMDT:
			err = ksys_shmdt(ptr);
			जाओ out;
		हाल SHMGET:
			err = ksys_shmget(first, (माप_प्रकार)second, (पूर्णांक)third);
			जाओ out;
		हाल SHMCTL:
			err = ksys_old_shmctl(first, (पूर्णांक)second | IPC_64, ptr);
			जाओ out;
		शेष:
			err = -ENOSYS;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = -ENOSYS;
	पूर्ण
out:
	वापस err;
पूर्ण

SYSCALL_DEFINE1(sparc64_personality, अचिन्हित दीर्घ, personality)
अणु
	दीर्घ ret;

	अगर (personality(current->personality) == PER_LINUX32 &&
	    personality(personality) == PER_LINUX)
		personality |= PER_LINUX32;
	ret = sys_personality(personality);
	अगर (personality(ret) == PER_LINUX32)
		ret &= ~PER_LINUX32;

	वापस ret;
पूर्ण

पूर्णांक sparc_mmap_check(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len)
अणु
	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		अगर (len >= STACK_TOP32)
			वापस -EINVAL;

		अगर (addr > STACK_TOP32 - len)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (len >= VA_EXCLUDE_START)
			वापस -EINVAL;

		अगर (invalid_64bit_range(addr, len))
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Linux version of mmap */
SYSCALL_DEFINE6(mmap, अचिन्हित दीर्घ, addr, अचिन्हित दीर्घ, len,
		अचिन्हित दीर्घ, prot, अचिन्हित दीर्घ, flags, अचिन्हित दीर्घ, fd,
		अचिन्हित दीर्घ, off)
अणु
	अचिन्हित दीर्घ retval = -EINVAL;

	अगर ((off + PAGE_ALIGN(len)) < off)
		जाओ out;
	अगर (off & ~PAGE_MASK)
		जाओ out;
	retval = ksys_mmap_pgoff(addr, len, prot, flags, fd, off >> PAGE_SHIFT);
out:
	वापस retval;
पूर्ण

SYSCALL_DEFINE2(64_munmap, अचिन्हित दीर्घ, addr, माप_प्रकार, len)
अणु
	अगर (invalid_64bit_range(addr, len))
		वापस -EINVAL;

	वापस vm_munmap(addr, len);
पूर्ण
                
SYSCALL_DEFINE5(64_mremap, अचिन्हित दीर्घ, addr,	अचिन्हित दीर्घ, old_len,
		अचिन्हित दीर्घ, new_len, अचिन्हित दीर्घ, flags,
		अचिन्हित दीर्घ, new_addr)
अणु
	अगर (test_thपढ़ो_flag(TIF_32BIT))
		वापस -EINVAL;
	वापस sys_mremap(addr, old_len, new_len, flags, new_addr);
पूर्ण

SYSCALL_DEFINE0(nis_syscall)
अणु
	अटल पूर्णांक count;
	काष्ठा pt_regs *regs = current_pt_regs();
	
	/* Don't make the प्रणाली unusable, अगर someone goes stuck */
	अगर (count++ > 5)
		वापस -ENOSYS;

	prपूर्णांकk ("Unimplemented SPARC system call %ld\n",regs->u_regs[1]);
#अगर_घोषित DEBUG_UNIMP_SYSCALL	
	show_regs (regs);
#पूर्ण_अगर

	वापस -ENOSYS;
पूर्ण

/* #घोषणा DEBUG_SPARC_BREAKPOINT */

यंत्रlinkage व्योम sparc_अवरोधpoपूर्णांक(काष्ठा pt_regs *regs)
अणु
	क्रमागत ctx_state prev_state = exception_enter();

	अगर (test_thपढ़ो_flag(TIF_32BIT)) अणु
		regs->tpc &= 0xffffffff;
		regs->tnpc &= 0xffffffff;
	पूर्ण
#अगर_घोषित DEBUG_SPARC_BREAKPOINT
        prपूर्णांकk ("TRAP: Entering kernel PC=%lx, nPC=%lx\n", regs->tpc, regs->tnpc);
#पूर्ण_अगर
	क्रमce_sig_fault(SIGTRAP, TRAP_BRKPT, (व्योम __user *)regs->tpc, 0);
#अगर_घोषित DEBUG_SPARC_BREAKPOINT
	prपूर्णांकk ("TRAP: Returning to space: PC=%lx nPC=%lx\n", regs->tpc, regs->tnpc);
#पूर्ण_अगर
	exception_निकास(prev_state);
पूर्ण

SYSCALL_DEFINE2(getकरोमुख्यname, अक्षर __user *, name, पूर्णांक, len)
अणु
	पूर्णांक nlen, err;
	अक्षर पंचांगp[__NEW_UTS_LEN + 1];

	अगर (len < 0)
		वापस -EINVAL;

	करोwn_पढ़ो(&uts_sem);

	nlen = म_माप(utsname()->करोमुख्यname) + 1;
	err = -EINVAL;
	अगर (nlen > len)
		जाओ out_unlock;
	स_नकल(पंचांगp, utsname()->करोमुख्यname, nlen);

	up_पढ़ो(&uts_sem);

	अगर (copy_to_user(name, पंचांगp, nlen))
		वापस -EFAULT;
	वापस 0;

out_unlock:
	up_पढ़ो(&uts_sem);
	वापस err;
पूर्ण

SYSCALL_DEFINE1(sparc_adjसमयx, काष्ठा __kernel_समयx __user *, txc_p)
अणु
	काष्ठा __kernel_समयx txc;
	काष्ठा __kernel_old_समयval *tv = (व्योम *)&txc.समय;
	पूर्णांक ret;

	/* Copy the user data space पूर्णांकo the kernel copy
	 * काष्ठाure. But bear in mind that the काष्ठाures
	 * may change
	 */
	अगर (copy_from_user(&txc, txc_p, माप(txc)))
		वापस -EFAULT;

	/*
	 * override क्रम sparc64 specअगरic समयval type: tv_usec
	 * is 32 bit wide instead of 64-bit in __kernel_समयx
	 */
	txc.समय.tv_usec = tv->tv_usec;
	ret = करो_adjसमयx(&txc);
	tv->tv_usec = txc.समय.tv_usec;

	वापस copy_to_user(txc_p, &txc, माप(txc)) ? -EFAULT : ret;
पूर्ण

SYSCALL_DEFINE2(sparc_घड़ी_adjसमय, स्थिर घड़ीid_t, which_घड़ी,
		काष्ठा __kernel_समयx __user *, txc_p)
अणु
	काष्ठा __kernel_समयx txc;
	काष्ठा __kernel_old_समयval *tv = (व्योम *)&txc.समय;
	पूर्णांक ret;

	अगर (!IS_ENABLED(CONFIG_POSIX_TIMERS)) अणु
		pr_err_once("process %d (%s) attempted a POSIX timer syscall "
		    "while CONFIG_POSIX_TIMERS is not set\n",
		    current->pid, current->comm);

		वापस -ENOSYS;
	पूर्ण

	/* Copy the user data space पूर्णांकo the kernel copy
	 * काष्ठाure. But bear in mind that the काष्ठाures
	 * may change
	 */
	अगर (copy_from_user(&txc, txc_p, माप(txc)))
		वापस -EFAULT;

	/*
	 * override क्रम sparc64 specअगरic समयval type: tv_usec
	 * is 32 bit wide instead of 64-bit in __kernel_समयx
	 */
	txc.समय.tv_usec = tv->tv_usec;
	ret = करो_घड़ी_adjसमय(which_घड़ी, &txc);
	tv->tv_usec = txc.समय.tv_usec;

	वापस copy_to_user(txc_p, &txc, माप(txc)) ? -EFAULT : ret;
पूर्ण

SYSCALL_DEFINE5(utrap_install, utrap_entry_t, type,
		utrap_handler_t, new_p, utrap_handler_t, new_d,
		utrap_handler_t __user *, old_p,
		utrap_handler_t __user *, old_d)
अणु
	अगर (type < UT_INSTRUCTION_EXCEPTION || type > UT_TRAP_INSTRUCTION_31)
		वापस -EINVAL;
	अगर (new_p == (utrap_handler_t)(दीर्घ)UTH_NOCHANGE) अणु
		अगर (old_p) अणु
			अगर (!current_thपढ़ो_info()->utraps) अणु
				अगर (put_user(शून्य, old_p))
					वापस -EFAULT;
			पूर्ण अन्यथा अणु
				अगर (put_user((utrap_handler_t)(current_thपढ़ो_info()->utraps[type]), old_p))
					वापस -EFAULT;
			पूर्ण
		पूर्ण
		अगर (old_d) अणु
			अगर (put_user(शून्य, old_d))
				वापस -EFAULT;
		पूर्ण
		वापस 0;
	पूर्ण
	अगर (!current_thपढ़ो_info()->utraps) अणु
		current_thपढ़ो_info()->utraps =
			kसुस्मृति(UT_TRAP_INSTRUCTION_31 + 1, माप(दीर्घ),
				GFP_KERNEL);
		अगर (!current_thपढ़ो_info()->utraps)
			वापस -ENOMEM;
		current_thपढ़ो_info()->utraps[0] = 1;
	पूर्ण अन्यथा अणु
		अगर ((utrap_handler_t)current_thपढ़ो_info()->utraps[type] != new_p &&
		    current_thपढ़ो_info()->utraps[0] > 1) अणु
			अचिन्हित दीर्घ *p = current_thपढ़ो_info()->utraps;

			current_thपढ़ो_info()->utraps =
				kदो_स्मृति_array(UT_TRAP_INSTRUCTION_31 + 1,
					      माप(दीर्घ),
					      GFP_KERNEL);
			अगर (!current_thपढ़ो_info()->utraps) अणु
				current_thपढ़ो_info()->utraps = p;
				वापस -ENOMEM;
			पूर्ण
			p[0]--;
			current_thपढ़ो_info()->utraps[0] = 1;
			स_नकल(current_thपढ़ो_info()->utraps+1, p+1,
			       UT_TRAP_INSTRUCTION_31*माप(दीर्घ));
		पूर्ण
	पूर्ण
	अगर (old_p) अणु
		अगर (put_user((utrap_handler_t)(current_thपढ़ो_info()->utraps[type]), old_p))
			वापस -EFAULT;
	पूर्ण
	अगर (old_d) अणु
		अगर (put_user(शून्य, old_d))
			वापस -EFAULT;
	पूर्ण
	current_thपढ़ो_info()->utraps[type] = (दीर्घ)new_p;

	वापस 0;
पूर्ण

SYSCALL_DEFINE1(memory_ordering, अचिन्हित दीर्घ, model)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();
	अगर (model >= 3)
		वापस -EINVAL;
	regs->tstate = (regs->tstate & ~TSTATE_MM) | (model << 14);
	वापस 0;
पूर्ण

SYSCALL_DEFINE5(rt_sigaction, पूर्णांक, sig, स्थिर काष्ठा sigaction __user *, act,
		काष्ठा sigaction __user *, oact, व्योम __user *, restorer,
		माप_प्रकार, sigsetsize)
अणु
	काष्ठा k_sigaction new_ka, old_ka;
	पूर्णांक ret;

	/* XXX: Don't preclude handling different sized sigset_t's.  */
	अगर (sigsetsize != माप(sigset_t))
		वापस -EINVAL;

	अगर (act) अणु
		new_ka.ka_restorer = restorer;
		अगर (copy_from_user(&new_ka.sa, act, माप(*act)))
			वापस -EFAULT;
	पूर्ण

	ret = करो_sigaction(sig, act ? &new_ka : शून्य, oact ? &old_ka : शून्य);

	अगर (!ret && oact) अणु
		अगर (copy_to_user(oact, &old_ka.sa, माप(*oact)))
			वापस -EFAULT;
	पूर्ण

	वापस ret;
पूर्ण

SYSCALL_DEFINE0(kern_features)
अणु
	वापस KERN_FEATURE_MIXED_MODE_STACK;
पूर्ण
