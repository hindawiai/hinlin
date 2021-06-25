<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  S390 version
 *    Copyright IBM Corp. 1999, 2000
 *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com),
 *               Thomas Spatzier (tspat@de.ibm.com)
 *
 *  Derived from "arch/i386/kernel/sys_i386.c"
 *
 *  This file contains various अक्रमom प्रणाली calls that
 *  have a non-standard calling sequence on the Linux/s390
 *  platक्रमm.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/fs.h>
#समावेश <linux/smp.h>
#समावेश <linux/sem.h>
#समावेश <linux/msg.h>
#समावेश <linux/shm.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/syscalls.h>
#समावेश <linux/mman.h>
#समावेश <linux/file.h>
#समावेश <linux/utsname.h>
#समावेश <linux/personality.h>
#समावेश <linux/unistd.h>
#समावेश <linux/ipc.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/माला.स>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/entry-common.h>

#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/vसमय.स>

#समावेश "entry.h"

/*
 * Perक्रमm the mmap() प्रणाली call. Linux क्रम S/390 isn't able to handle more
 * than 5 प्रणाली call parameters, so this प्रणाली call uses a memory block
 * क्रम parameter passing.
 */

काष्ठा s390_mmap_arg_काष्ठा अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ len;
	अचिन्हित दीर्घ prot;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ fd;
	अचिन्हित दीर्घ offset;
पूर्ण;

SYSCALL_DEFINE1(mmap2, काष्ठा s390_mmap_arg_काष्ठा __user *, arg)
अणु
	काष्ठा s390_mmap_arg_काष्ठा a;
	पूर्णांक error = -EFAULT;

	अगर (copy_from_user(&a, arg, माप(a)))
		जाओ out;
	error = ksys_mmap_pgoff(a.addr, a.len, a.prot, a.flags, a.fd, a.offset);
out:
	वापस error;
पूर्ण

#अगर_घोषित CONFIG_SYSVIPC
/*
 * sys_ipc() is the de-multiplexer क्रम the SysV IPC calls.
 */
SYSCALL_DEFINE5(s390_ipc, uपूर्णांक, call, पूर्णांक, first, अचिन्हित दीर्घ, second,
		अचिन्हित दीर्घ, third, व्योम __user *, ptr)
अणु
	अगर (call >> 16)
		वापस -EINVAL;
	/* The s390 sys_ipc variant has only five parameters instead of six
	 * like the generic variant. The only dअगरference is the handling of
	 * the SEMTIMEDOP subcall where on s390 the third parameter is used
	 * as a poपूर्णांकer to a काष्ठा बारpec where the generic variant uses
	 * the fअगरth parameter.
	 * Thereक्रमe we can call the generic variant by simply passing the
	 * third parameter also as fअगरth parameter.
	 */
	वापस ksys_ipc(call, first, second, third, ptr, third);
पूर्ण
#पूर्ण_अगर /* CONFIG_SYSVIPC */

SYSCALL_DEFINE1(s390_personality, अचिन्हित पूर्णांक, personality)
अणु
	अचिन्हित पूर्णांक ret = current->personality;

	अगर (personality(current->personality) == PER_LINUX32 &&
	    personality(personality) == PER_LINUX)
		personality |= PER_LINUX32;

	अगर (personality != 0xffffffff)
		set_personality(personality);

	अगर (personality(ret) == PER_LINUX32)
		ret &= ~PER_LINUX32;

	वापस ret;
पूर्ण

SYSCALL_DEFINE0(ni_syscall)
अणु
	वापस -ENOSYS;
पूर्ण

व्योम करो_syscall(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ nr;

	nr = regs->पूर्णांक_code & 0xffff;
	अगर (!nr) अणु
		nr = regs->gprs[1] & 0xffff;
		regs->पूर्णांक_code &= ~0xffffUL;
		regs->पूर्णांक_code |= nr;
	पूर्ण

	regs->gprs[2] = nr;

	nr = syscall_enter_from_user_mode_work(regs, nr);

	/*
	 * In the s390 ptrace ABI, both the syscall number and the वापस value
	 * use gpr2. However, userspace माला_दो the syscall number either in the
	 * svc inकाष्ठाion itself, or uses gpr1. To make at least skipping syscalls
	 * work, the ptrace code sets PIF_SYSCALL_RET_SET, which is checked here
	 * and अगर set, the syscall will be skipped.
	 */
	अगर (!test_pt_regs_flag(regs, PIF_SYSCALL_RET_SET)) अणु
		regs->gprs[2] = -ENOSYS;
		अगर (likely(nr < NR_syscalls))
			regs->gprs[2] = current->thपढ़ो.sys_call_table[nr](regs);
	पूर्ण अन्यथा अणु
		clear_pt_regs_flag(regs, PIF_SYSCALL_RET_SET);
	पूर्ण
	syscall_निकास_to_user_mode_work(regs);
पूर्ण

व्योम noinstr __करो_syscall(काष्ठा pt_regs *regs, पूर्णांक per_trap)
अणु
	add_अक्रमom_kstack_offset();
	enter_from_user_mode(regs);

	स_नकल(&regs->gprs[8], S390_lowcore.save_area_sync, 8 * माप(अचिन्हित दीर्घ));
	स_नकल(&regs->पूर्णांक_code, &S390_lowcore.svc_ilc, माप(regs->पूर्णांक_code));
	regs->psw = S390_lowcore.svc_old_psw;

	update_समयr_sys();

	local_irq_enable();
	regs->orig_gpr2 = regs->gprs[2];

	अगर (per_trap)
		set_thपढ़ो_flag(TIF_PER_TRAP);

	क्रम (;;) अणु
		regs->flags = 0;
		set_pt_regs_flag(regs, PIF_SYSCALL);
		करो_syscall(regs);
		अगर (!test_pt_regs_flag(regs, PIF_SYSCALL_RESTART))
			अवरोध;
		local_irq_enable();
	पूर्ण
	निकास_to_user_mode();
पूर्ण
