<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* linux/arch/sparc/kernel/sys_sparc.c
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
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/sem.h>
#समावेश <linux/msg.h>
#समावेश <linux/shm.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/syscalls.h>
#समावेश <linux/mman.h>
#समावेश <linux/utsname.h>
#समावेश <linux/smp.h>
#समावेश <linux/ipc.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unistd.h>

#समावेश "systbls.h"

/* #घोषणा DEBUG_UNIMP_SYSCALL */

/* XXX Make this per-binary type, this way we can detect the type of
 * XXX a binary.  Every Sparc executable calls this very early on.
 */
SYSCALL_DEFINE0(getpagesize)
अणु
	वापस PAGE_SIZE; /* Possibly older binaries want 8192 on sun4's? */
पूर्ण

अचिन्हित दीर्घ arch_get_unmapped_area(काष्ठा file *filp, अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags)
अणु
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

	/* See यंत्र-sparc/uaccess.h */
	अगर (len > TASK_SIZE - PAGE_SIZE)
		वापस -ENOMEM;
	अगर (!addr)
		addr = TASK_UNMAPPED_BASE;

	info.flags = 0;
	info.length = len;
	info.low_limit = addr;
	info.high_limit = TASK_SIZE;
	info.align_mask = (flags & MAP_SHARED) ?
		(PAGE_MASK & (SHMLBA - 1)) : 0;
	info.align_offset = pgoff << PAGE_SHIFT;
	वापस vm_unmapped_area(&info);
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

पूर्णांक sparc_mmap_check(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ len)
अणु
	/* See यंत्र-sparc/uaccess.h */
	अगर (len > TASK_SIZE - PAGE_SIZE || addr + len > TASK_SIZE - PAGE_SIZE)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* Linux version of mmap */

SYSCALL_DEFINE6(mmap2, अचिन्हित दीर्घ, addr, अचिन्हित दीर्घ, len,
	अचिन्हित दीर्घ, prot, अचिन्हित दीर्घ, flags, अचिन्हित दीर्घ, fd,
	अचिन्हित दीर्घ, pgoff)
अणु
	/* Make sure the shअगरt क्रम mmap2 is स्थिरant (12), no matter what PAGE_SIZE
	   we have. */
	वापस ksys_mmap_pgoff(addr, len, prot, flags, fd,
			       pgoff >> (PAGE_SHIFT - 12));
पूर्ण

SYSCALL_DEFINE6(mmap, अचिन्हित दीर्घ, addr, अचिन्हित दीर्घ, len,
	अचिन्हित दीर्घ, prot, अचिन्हित दीर्घ, flags, अचिन्हित दीर्घ, fd,
	अचिन्हित दीर्घ, off)
अणु
	/* no alignment check? */
	वापस ksys_mmap_pgoff(addr, len, prot, flags, fd, off >> PAGE_SHIFT);
पूर्ण

SYSCALL_DEFINE5(sparc_remap_file_pages, अचिन्हित दीर्घ, start, अचिन्हित दीर्घ, size,
			   अचिन्हित दीर्घ, prot, अचिन्हित दीर्घ, pgoff,
			   अचिन्हित दीर्घ, flags)
अणु
	/* This works on an existing mmap so we करोn't need to validate
	 * the range as that was करोne at the original mmap call.
	 */
	वापस sys_remap_file_pages(start, size, prot,
				    (pgoff >> (PAGE_SHIFT - 12)), flags);
पूर्ण

SYSCALL_DEFINE0(nis_syscall)
अणु
	अटल पूर्णांक count = 0;
	काष्ठा pt_regs *regs = current_pt_regs();

	अगर (count++ > 5)
		वापस -ENOSYS;
	prपूर्णांकk ("%s[%d]: Unimplemented SPARC system call %d\n",
		current->comm, task_pid_nr(current), (पूर्णांक)regs->u_regs[1]);
#अगर_घोषित DEBUG_UNIMP_SYSCALL	
	show_regs (regs);
#पूर्ण_अगर
	वापस -ENOSYS;
पूर्ण

/* #घोषणा DEBUG_SPARC_BREAKPOINT */

यंत्रlinkage व्योम
sparc_अवरोधpoपूर्णांक (काष्ठा pt_regs *regs)
अणु

#अगर_घोषित DEBUG_SPARC_BREAKPOINT
        prपूर्णांकk ("TRAP: Entering kernel PC=%x, nPC=%x\n", regs->pc, regs->npc);
#पूर्ण_अगर
	क्रमce_sig_fault(SIGTRAP, TRAP_BRKPT, (व्योम __user *)regs->pc, 0);

#अगर_घोषित DEBUG_SPARC_BREAKPOINT
	prपूर्णांकk ("TRAP: Returning to space: PC=%x nPC=%x\n", regs->pc, regs->npc);
#पूर्ण_अगर
पूर्ण

SYSCALL_DEFINE3(sparc_sigaction, पूर्णांक, sig,
		काष्ठा old_sigaction __user *,act,
		काष्ठा old_sigaction __user *,oact)
अणु
	WARN_ON_ONCE(sig >= 0);
	वापस sys_sigaction(-sig, act, oact);
पूर्ण

SYSCALL_DEFINE5(rt_sigaction, पूर्णांक, sig,
		 स्थिर काष्ठा sigaction __user *, act,
		 काष्ठा sigaction __user *, oact,
		 व्योम __user *, restorer,
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
