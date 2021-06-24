<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 1996, 1997, 2000, 2001, 05 by Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 * Copyright (C) 2001 MIPS Technologies, Inc.
 */
#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/linkage.h>
#समावेश <linux/fs.h>
#समावेश <linux/smp.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/माला.स>
#समावेश <linux/syscalls.h>
#समावेश <linux/file.h>
#समावेश <linux/utsname.h>
#समावेश <linux/unistd.h>
#समावेश <linux/sem.h>
#समावेश <linux/msg.h>
#समावेश <linux/shm.h>
#समावेश <linux/compiler.h>
#समावेश <linux/ipc.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <linux/elf.h>
#समावेश <linux/sched/task_stack.h>

#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/यंत्र-eva.h>
#समावेश <यंत्र/branch.h>
#समावेश <यंत्र/cachectl.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/यंत्र-offsets.h>
#समावेश <यंत्र/संकेत.स>
#समावेश <यंत्र/sim.h>
#समावेश <यंत्र/shmparam.h>
#समावेश <यंत्र/sync.h>
#समावेश <यंत्र/sysmips.h>
#समावेश <यंत्र/चयन_to.h>

/*
 * For historic reasons the pipe(2) syscall on MIPS has an unusual calling
 * convention.	It वापसs results in रेजिस्टरs $v0 / $v1 which means there
 * is no need क्रम it to करो verअगरy the validity of a userspace poपूर्णांकer
 * argument.  Historically that used to be expensive in Linux.	These days
 * the perक्रमmance advantage is negligible.
 */
यंत्रlinkage पूर्णांक sysm_pipe(व्योम)
अणु
	पूर्णांक fd[2];
	पूर्णांक error = करो_pipe_flags(fd, 0);
	अगर (error)
		वापस error;
	current_pt_regs()->regs[3] = fd[1];
	वापस fd[0];
पूर्ण

SYSCALL_DEFINE6(mips_mmap, अचिन्हित दीर्घ, addr, अचिन्हित दीर्घ, len,
	अचिन्हित दीर्घ, prot, अचिन्हित दीर्घ, flags, अचिन्हित दीर्घ,
	fd, off_t, offset)
अणु
	अगर (offset & ~PAGE_MASK)
		वापस -EINVAL;
	वापस ksys_mmap_pgoff(addr, len, prot, flags, fd,
			       offset >> PAGE_SHIFT);
पूर्ण

SYSCALL_DEFINE6(mips_mmap2, अचिन्हित दीर्घ, addr, अचिन्हित दीर्घ, len,
	अचिन्हित दीर्घ, prot, अचिन्हित दीर्घ, flags, अचिन्हित दीर्घ, fd,
	अचिन्हित दीर्घ, pgoff)
अणु
	अगर (pgoff & (~PAGE_MASK >> 12))
		वापस -EINVAL;

	वापस ksys_mmap_pgoff(addr, len, prot, flags, fd,
			       pgoff >> (PAGE_SHIFT - 12));
पूर्ण

save_अटल_function(sys_विभाजन);
save_अटल_function(sys_clone);
save_अटल_function(sys_clone3);

SYSCALL_DEFINE1(set_thपढ़ो_area, अचिन्हित दीर्घ, addr)
अणु
	काष्ठा thपढ़ो_info *ti = task_thपढ़ो_info(current);

	ti->tp_value = addr;
	अगर (cpu_has_userlocal)
		ग_लिखो_c0_userlocal(addr);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mips_atomic_set(अचिन्हित दीर्घ addr, अचिन्हित दीर्घ new)
अणु
	अचिन्हित दीर्घ old, पंचांगp;
	काष्ठा pt_regs *regs;
	अचिन्हित पूर्णांक err;

	अगर (unlikely(addr & 3))
		वापस -EINVAL;

	अगर (unlikely(!access_ok((स्थिर व्योम __user *)addr, 4)))
		वापस -EINVAL;

	अगर (cpu_has_llsc && IS_ENABLED(CONFIG_WAR_R10000_LLSC)) अणु
		__यंत्र__ __अस्थिर__ (
		"	.set	push					\n"
		"	.set	arch=r4000				\n"
		"	li	%[err], 0				\n"
		"1:	ll	%[old], (%[addr])			\n"
		"	move	%[tmp], %[new]				\n"
		"2:	sc	%[tmp], (%[addr])			\n"
		"	beqzl	%[tmp], 1b				\n"
		"3:							\n"
		"	.insn						\n"
		"	.section .fixup,\"ax\"				\n"
		"4:	li	%[err], %[efault]			\n"
		"	j	3b					\n"
		"	.previous					\n"
		"	.section __ex_table,\"a\"			\n"
		"	"STR(PTR)"	1b, 4b				\n"
		"	"STR(PTR)"	2b, 4b				\n"
		"	.previous					\n"
		"	.set	pop					\n"
		: [old] "=&r" (old),
		  [err] "=&r" (err),
		  [पंचांगp] "=&r" (पंचांगp)
		: [addr] "r" (addr),
		  [new] "r" (new),
		  [efault] "i" (-EFAULT)
		: "memory");
	पूर्ण अन्यथा अगर (cpu_has_llsc) अणु
		__यंत्र__ __अस्थिर__ (
		"	.set	push					\n"
		"	.set	"MIPS_ISA_ARCH_LEVEL"			\n"
		"	li	%[err], 0				\n"
		"1:							\n"
		"	" __SYNC(full, loongson3_war) "			\n"
		user_ll("%[old]", "(%[addr])")
		"	move	%[tmp], %[new]				\n"
		"2:							\n"
		user_sc("%[tmp]", "(%[addr])")
		"	beqz	%[tmp], 1b				\n"
		"3:							\n"
		"	.insn						\n"
		"	.section .fixup,\"ax\"				\n"
		"5:	li	%[err], %[efault]			\n"
		"	j	3b					\n"
		"	.previous					\n"
		"	.section __ex_table,\"a\"			\n"
		"	"STR(PTR)"	1b, 5b				\n"
		"	"STR(PTR)"	2b, 5b				\n"
		"	.previous					\n"
		"	.set	pop					\n"
		: [old] "=&r" (old),
		  [err] "=&r" (err),
		  [पंचांगp] "=&r" (पंचांगp)
		: [addr] "r" (addr),
		  [new] "r" (new),
		  [efault] "i" (-EFAULT)
		: "memory");
	पूर्ण अन्यथा अणु
		करो अणु
			preempt_disable();
			ll_bit = 1;
			ll_task = current;
			preempt_enable();

			err = __get_user(old, (अचिन्हित पूर्णांक *) addr);
			err |= __put_user(new, (अचिन्हित पूर्णांक *) addr);
			अगर (err)
				अवरोध;
			rmb();
		पूर्ण जबतक (!ll_bit);
	पूर्ण

	अगर (unlikely(err))
		वापस err;

	regs = current_pt_regs();
	regs->regs[2] = old;
	regs->regs[7] = 0;	/* No error */

	/*
	 * Don't let your children करो this ...
	 */
	__यंत्र__ __अस्थिर__(
	"	move	$29, %0						\n"
	"	j	syscall_exit					\n"
	: /* no outमाला_दो */
	: "r" (regs));

	/* unreached.  Honestly.  */
	unreachable();
पूर्ण

/*
 * mips_atomic_set() normally वापसs directly via syscall_निकास potentially
 * clobbering अटल रेजिस्टरs, so be sure to preserve them.
 */
save_अटल_function(sys_sysmips);

SYSCALL_DEFINE3(sysmips, दीर्घ, cmd, दीर्घ, arg1, दीर्घ, arg2)
अणु
	चयन (cmd) अणु
	हाल MIPS_ATOMIC_SET:
		वापस mips_atomic_set(arg1, arg2);

	हाल MIPS_FIXADE:
		अगर (arg1 & ~3)
			वापस -EINVAL;

		अगर (arg1 & 1)
			set_thपढ़ो_flag(TIF_FIXADE);
		अन्यथा
			clear_thपढ़ो_flag(TIF_FIXADE);
		अगर (arg1 & 2)
			set_thपढ़ो_flag(TIF_LOGADE);
		अन्यथा
			clear_thपढ़ो_flag(TIF_LOGADE);

		वापस 0;

	हाल FLUSH_CACHE:
		__flush_cache_all();
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/*
 * No implemented yet ...
 */
SYSCALL_DEFINE3(cachectl, अक्षर *, addr, पूर्णांक, nbytes, पूर्णांक, op)
अणु
	वापस -ENOSYS;
पूर्ण

/*
 * If we ever come here the user sp is bad.  Zap the process right away.
 * Due to the bad stack संकेतing wouldn't work.
 */
यंत्रlinkage व्योम bad_stack(व्योम)
अणु
	करो_निकास(संक_अंश);
पूर्ण
