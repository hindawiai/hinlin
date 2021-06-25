<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Implementation of various प्रणाली calls क्रम Linux/PowerPC
 *
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *
 * Derived from "arch/i386/kernel/sys_i386.c"
 * Adapted from the i386 version by Gary Thomas
 * Modअगरied by Cort Dougan (cort@cs.nmt.edu)
 * and Paul Mackerras (paulus@cs.anu.edu.au).
 *
 * This file contains various अक्रमom प्रणाली calls that
 * have a non-standard calling sequence on the Linux/PPC
 * platक्रमm.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/smp.h>
#समावेश <linux/sem.h>
#समावेश <linux/msg.h>
#समावेश <linux/shm.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/mman.h>
#समावेश <linux/sys.h>
#समावेश <linux/ipc.h>
#समावेश <linux/utsname.h>
#समावेश <linux/file.h>
#समावेश <linux/personality.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/syscalls.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/यंत्र-prototypes.h>

अटल अंतरभूत दीर्घ करो_mmap2(अचिन्हित दीर्घ addr, माप_प्रकार len,
			अचिन्हित दीर्घ prot, अचिन्हित दीर्घ flags,
			अचिन्हित दीर्घ fd, अचिन्हित दीर्घ off, पूर्णांक shअगरt)
अणु
	दीर्घ ret = -EINVAL;

	अगर (!arch_validate_prot(prot, addr))
		जाओ out;

	अगर (shअगरt) अणु
		अगर (off & ((1 << shअगरt) - 1))
			जाओ out;
		off >>= shअगरt;
	पूर्ण

	ret = ksys_mmap_pgoff(addr, len, prot, flags, fd, off);
out:
	वापस ret;
पूर्ण

SYSCALL_DEFINE6(mmap2, अचिन्हित दीर्घ, addr, माप_प्रकार, len,
		अचिन्हित दीर्घ, prot, अचिन्हित दीर्घ, flags,
		अचिन्हित दीर्घ, fd, अचिन्हित दीर्घ, pgoff)
अणु
	वापस करो_mmap2(addr, len, prot, flags, fd, pgoff, PAGE_SHIFT-12);
पूर्ण

SYSCALL_DEFINE6(mmap, अचिन्हित दीर्घ, addr, माप_प्रकार, len,
		अचिन्हित दीर्घ, prot, अचिन्हित दीर्घ, flags,
		अचिन्हित दीर्घ, fd, off_t, offset)
अणु
	वापस करो_mmap2(addr, len, prot, flags, fd, offset, PAGE_SHIFT);
पूर्ण

#अगर_घोषित CONFIG_PPC32
/*
 * Due to some executables calling the wrong select we someबार
 * get wrong args.  This determines how the args are being passed
 * (a single ptr to them all args passed) then calls
 * sys_select() with the appropriate args. -- Cort
 */
पूर्णांक
ppc_select(पूर्णांक n, fd_set __user *inp, fd_set __user *outp, fd_set __user *exp, काष्ठा __kernel_old_समयval __user *tvp)
अणु
	अगर ( (अचिन्हित दीर्घ)n >= 4096 )
		वापस sys_old_select((व्योम __user *)n);

	वापस sys_select(n, inp, outp, exp, tvp);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC64
दीर्घ ppc64_personality(अचिन्हित दीर्घ personality)
अणु
	दीर्घ ret;

	अगर (personality(current->personality) == PER_LINUX32
	    && personality(personality) == PER_LINUX)
		personality = (personality & ~PER_MASK) | PER_LINUX32;
	ret = sys_personality(personality);
	अगर (personality(ret) == PER_LINUX32)
		ret = (ret & ~PER_MASK) | PER_LINUX;
	वापस ret;
पूर्ण
#पूर्ण_अगर

दीर्घ ppc_fadvise64_64(पूर्णांक fd, पूर्णांक advice, u32 offset_high, u32 offset_low,
		      u32 len_high, u32 len_low)
अणु
	वापस ksys_fadvise64_64(fd, (u64)offset_high << 32 | offset_low,
				 (u64)len_high << 32 | len_low, advice);
पूर्ण

SYSCALL_DEFINE0(चयन_endian)
अणु
	काष्ठा thपढ़ो_info *ti;

	current->thपढ़ो.regs->msr ^= MSR_LE;

	/*
	 * Set TIF_RESTOREALL so that r3 isn't clobbered on वापस to
	 * userspace. That also has the effect of restoring the non-अस्थिर
	 * GPRs, so we saved them on the way in here.
	 */
	ti = current_thपढ़ो_info();
	ti->flags |= _TIF_RESTOREALL;

	वापस 0;
पूर्ण
