<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* ptrace.c: Sparc process tracing support.
 *
 * Copyright (C) 1996, 2008 David S. Miller (davem@davemloft.net)
 *
 * Based upon code written by Ross Biro, Linus Torvalds, Bob Manson,
 * and David Mosberger.
 *
 * Added Linux support -miguel (weird, eh?, the original code was meant
 * to emulate SunOS).
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/user.h>
#समावेश <linux/smp.h>
#समावेश <linux/security.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/regset.h>
#समावेश <linux/elf.h>
#समावेश <linux/tracehook.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/cacheflush.h>

#समावेश "kernel.h"

/* #घोषणा ALLOW_INIT_TRACING */

/*
 * Called by kernel/ptrace.c when detaching..
 *
 * Make sure single step bits etc are not set.
 */
व्योम ptrace_disable(काष्ठा task_काष्ठा *child)
अणु
	/* nothing to करो */
पूर्ण

क्रमागत sparc_regset अणु
	REGSET_GENERAL,
	REGSET_FP,
पूर्ण;

अटल पूर्णांक regwinकरोw32_get(काष्ठा task_काष्ठा *target,
			   स्थिर काष्ठा pt_regs *regs,
			   u32 *uregs)
अणु
	अचिन्हित दीर्घ reg_winकरोw = regs->u_regs[UREG_I6];
	पूर्णांक size = 16 * माप(u32);

	अगर (target == current) अणु
		अगर (copy_from_user(uregs, (व्योम __user *)reg_winकरोw, size))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		अगर (access_process_vm(target, reg_winकरोw, uregs, size,
				      FOLL_FORCE) != size)
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक regwinकरोw32_set(काष्ठा task_काष्ठा *target,
			   स्थिर काष्ठा pt_regs *regs,
			   u32 *uregs)
अणु
	अचिन्हित दीर्घ reg_winकरोw = regs->u_regs[UREG_I6];
	पूर्णांक size = 16 * माप(u32);

	अगर (target == current) अणु
		अगर (copy_to_user((व्योम __user *)reg_winकरोw, uregs, size))
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		अगर (access_process_vm(target, reg_winकरोw, uregs, size,
				      FOLL_FORCE | FOLL_WRITE) != size)
			वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक genregs32_get(काष्ठा task_काष्ठा *target,
			 स्थिर काष्ठा user_regset *regset,
			 काष्ठा membuf to)
अणु
	स्थिर काष्ठा pt_regs *regs = target->thपढ़ो.kregs;
	u32 uregs[16];

	अगर (target == current)
		flush_user_winकरोws();

	membuf_ग_लिखो(&to, regs->u_regs, 16 * माप(u32));
	अगर (!to.left)
		वापस 0;
	अगर (regwinकरोw32_get(target, regs, uregs))
		वापस -EFAULT;
	membuf_ग_लिखो(&to, uregs, 16 * माप(u32));
	membuf_store(&to, regs->psr);
	membuf_store(&to, regs->pc);
	membuf_store(&to, regs->npc);
	membuf_store(&to, regs->y);
	वापस membuf_zero(&to, 2 * माप(u32));
पूर्ण

अटल पूर्णांक genregs32_set(काष्ठा task_काष्ठा *target,
			 स्थिर काष्ठा user_regset *regset,
			 अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			 स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा pt_regs *regs = target->thपढ़ो.kregs;
	u32 uregs[16];
	u32 psr;
	पूर्णांक ret;

	अगर (target == current)
		flush_user_winकरोws();

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 regs->u_regs,
				 0, 16 * माप(u32));
	अगर (ret || !count)
		वापस ret;

	अगर (regwinकरोw32_get(target, regs, uregs))
		वापस -EFAULT;
	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 uregs,
				 16 * माप(u32), 32 * माप(u32));
	अगर (ret)
		वापस ret;
	अगर (regwinकरोw32_set(target, regs, uregs))
		वापस -EFAULT;
	अगर (!count)
		वापस 0;

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &psr,
				 32 * माप(u32), 33 * माप(u32));
	अगर (ret)
		वापस ret;
	regs->psr = (regs->psr & ~(PSR_ICC | PSR_SYSCALL)) |
		    (psr & (PSR_ICC | PSR_SYSCALL));
	अगर (!count)
		वापस 0;
	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &regs->pc,
				 33 * माप(u32), 34 * माप(u32));
	अगर (ret || !count)
		वापस ret;
	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &regs->npc,
				 34 * माप(u32), 35 * माप(u32));
	अगर (ret || !count)
		वापस ret;
	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &regs->y,
				 35 * माप(u32), 36 * माप(u32));
	अगर (ret || !count)
		वापस ret;
	वापस user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
					 36 * माप(u32), 38 * माप(u32));
पूर्ण

अटल पूर्णांक fpregs32_get(काष्ठा task_काष्ठा *target,
			स्थिर काष्ठा user_regset *regset,
			काष्ठा membuf to)
अणु
#अगर 0
	अगर (target == current)
		save_and_clear_fpu();
#पूर्ण_अगर

	membuf_ग_लिखो(&to, target->thपढ़ो.भग्न_regs, 32 * माप(u32));
	membuf_zero(&to, माप(u32));
	membuf_ग_लिखो(&to, &target->thपढ़ो.fsr, माप(u32));
	membuf_store(&to, (u32)((1 << 8) | (8 << 16)));
	वापस membuf_zero(&to, 64 * माप(u32));
पूर्ण

अटल पूर्णांक fpregs32_set(काष्ठा task_काष्ठा *target,
			स्थिर काष्ठा user_regset *regset,
			अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	अचिन्हित दीर्घ *fpregs = target->thपढ़ो.भग्न_regs;
	पूर्णांक ret;

#अगर 0
	अगर (target == current)
		save_and_clear_fpu();
#पूर्ण_अगर
	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 fpregs,
				 0, 32 * माप(u32));
	अगर (!ret)
		user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
					  32 * माप(u32),
					  33 * माप(u32));
	अगर (!ret)
		ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
					 &target->thपढ़ो.fsr,
					 33 * माप(u32),
					 34 * माप(u32));
	अगर (!ret)
		ret = user_regset_copyin_ignore(&pos, &count, &kbuf, &ubuf,
						34 * माप(u32), -1);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा user_regset sparc32_regsets[] = अणु
	/* Format is:
	 * 	G0 --> G7
	 *	O0 --> O7
	 *	L0 --> L7
	 *	I0 --> I7
	 *	PSR, PC, nPC, Y, WIM, TBR
	 */
	[REGSET_GENERAL] = अणु
		.core_note_type = NT_PRSTATUS,
		.n = 38,
		.size = माप(u32), .align = माप(u32),
		.regset_get = genregs32_get, .set = genregs32_set
	पूर्ण,
	/* Format is:
	 *	F0 --> F31
	 *	empty 32-bit word
	 *	FSR (32--bit word)
	 *	FPU QUEUE COUNT (8-bit अक्षर)
	 *	FPU QUEUE ENTRYSIZE (8-bit अक्षर)
	 *	FPU ENABLED (8-bit अक्षर)
	 *	empty 8-bit अक्षर
	 *	FPU QUEUE (64 32-bit पूर्णांकs)
	 */
	[REGSET_FP] = अणु
		.core_note_type = NT_PRFPREG,
		.n = 99,
		.size = माप(u32), .align = माप(u32),
		.regset_get = fpregs32_get, .set = fpregs32_set
	पूर्ण,
पूर्ण;

अटल पूर्णांक getregs_get(काष्ठा task_काष्ठा *target,
			 स्थिर काष्ठा user_regset *regset,
			 काष्ठा membuf to)
अणु
	स्थिर काष्ठा pt_regs *regs = target->thपढ़ो.kregs;

	अगर (target == current)
		flush_user_winकरोws();

	membuf_store(&to, regs->psr);
	membuf_store(&to, regs->pc);
	membuf_store(&to, regs->npc);
	membuf_store(&to, regs->y);
	वापस membuf_ग_लिखो(&to, regs->u_regs + 1, 15 * माप(u32));
पूर्ण

अटल पूर्णांक setregs_set(काष्ठा task_काष्ठा *target,
			 स्थिर काष्ठा user_regset *regset,
			 अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			 स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	काष्ठा pt_regs *regs = target->thपढ़ो.kregs;
	u32 v[4];
	पूर्णांक ret;

	अगर (target == current)
		flush_user_winकरोws();

	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 v,
				 0, 4 * माप(u32));
	अगर (ret)
		वापस ret;
	regs->psr = (regs->psr & ~(PSR_ICC | PSR_SYSCALL)) |
		    (v[0] & (PSR_ICC | PSR_SYSCALL));
	regs->pc = v[1];
	regs->npc = v[2];
	regs->y = v[3];
	वापस user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 regs->u_regs + 1,
				 4 * माप(u32) , 19 * माप(u32));
पूर्ण

अटल पूर्णांक getfpregs_get(काष्ठा task_काष्ठा *target,
			स्थिर काष्ठा user_regset *regset,
			काष्ठा membuf to)
अणु
#अगर 0
	अगर (target == current)
		save_and_clear_fpu();
#पूर्ण_अगर
	membuf_ग_लिखो(&to, &target->thपढ़ो.भग्न_regs, 32 * माप(u32));
	membuf_ग_लिखो(&to, &target->thपढ़ो.fsr, माप(u32));
	वापस membuf_zero(&to, 35 * माप(u32));
पूर्ण

अटल पूर्णांक setfpregs_set(काष्ठा task_काष्ठा *target,
			स्थिर काष्ठा user_regset *regset,
			अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf)
अणु
	अचिन्हित दीर्घ *fpregs = target->thपढ़ो.भग्न_regs;
	पूर्णांक ret;

#अगर 0
	अगर (target == current)
		save_and_clear_fpu();
#पूर्ण_अगर
	ret = user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 fpregs,
				 0, 32 * माप(u32));
	अगर (ret)
		वापस ret;
	वापस user_regset_copyin(&pos, &count, &kbuf, &ubuf,
				 &target->thपढ़ो.fsr,
				 32 * माप(u32),
				 33 * माप(u32));
पूर्ण

अटल स्थिर काष्ठा user_regset ptrace32_regsets[] = अणु
	[REGSET_GENERAL] = अणु
		.n = 19, .size = माप(u32),
		.regset_get = getregs_get, .set = setregs_set,
	पूर्ण,
	[REGSET_FP] = अणु
		.n = 68, .size = माप(u32),
		.regset_get = getfpregs_get, .set = setfpregs_set,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा user_regset_view ptrace32_view = अणु
	.regsets = ptrace32_regsets, .n = ARRAY_SIZE(ptrace32_regsets)
पूर्ण;

अटल स्थिर काष्ठा user_regset_view user_sparc32_view = अणु
	.name = "sparc", .e_machine = EM_SPARC,
	.regsets = sparc32_regsets, .n = ARRAY_SIZE(sparc32_regsets)
पूर्ण;

स्थिर काष्ठा user_regset_view *task_user_regset_view(काष्ठा task_काष्ठा *task)
अणु
	वापस &user_sparc32_view;
पूर्ण

काष्ठा fps अणु
	अचिन्हित दीर्घ regs[32];
	अचिन्हित दीर्घ fsr;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ extra;
	अचिन्हित दीर्घ fpqd;
	काष्ठा fq अणु
		अचिन्हित दीर्घ *insnaddr;
		अचिन्हित दीर्घ insn;
	पूर्ण fpq[16];
पूर्ण;

दीर्घ arch_ptrace(काष्ठा task_काष्ठा *child, दीर्घ request,
		 अचिन्हित दीर्घ addr, अचिन्हित दीर्घ data)
अणु
	अचिन्हित दीर्घ addr2 = current->thपढ़ो.kregs->u_regs[UREG_I4];
	व्योम __user *addr2p;
	काष्ठा pt_regs __user *pregs;
	काष्ठा fps __user *fps;
	पूर्णांक ret;

	addr2p = (व्योम __user *) addr2;
	pregs = (काष्ठा pt_regs __user *) addr;
	fps = (काष्ठा fps __user *) addr;

	चयन(request) अणु
	हाल PTRACE_GETREGS: अणु
		ret = copy_regset_to_user(child, &ptrace32_view,
					  REGSET_GENERAL, 0,
					  19 * माप(u32),
					  pregs);
		अवरोध;
	पूर्ण

	हाल PTRACE_SETREGS: अणु
		ret = copy_regset_from_user(child, &ptrace32_view,
					    REGSET_GENERAL, 0,
					    19 * माप(u32),
					    pregs);
		अवरोध;
	पूर्ण

	हाल PTRACE_GETFPREGS: अणु
		ret = copy_regset_to_user(child, &ptrace32_view,
					  REGSET_FP, 0,
					  68 * माप(u32),
					  fps);
		अवरोध;
	पूर्ण

	हाल PTRACE_SETFPREGS: अणु
		ret = copy_regset_from_user(child, &ptrace32_view,
					  REGSET_FP, 0,
					  33 * माप(u32),
					  fps);
		अवरोध;
	पूर्ण

	हाल PTRACE_READTEXT:
	हाल PTRACE_READDATA:
		ret = ptrace_पढ़ोdata(child, addr, addr2p, data);

		अगर (ret == data)
			ret = 0;
		अन्यथा अगर (ret >= 0)
			ret = -EIO;
		अवरोध;

	हाल PTRACE_WRITETEXT:
	हाल PTRACE_WRITEDATA:
		ret = ptrace_ग_लिखोdata(child, addr2p, addr, data);

		अगर (ret == data)
			ret = 0;
		अन्यथा अगर (ret >= 0)
			ret = -EIO;
		अवरोध;

	शेष:
		अगर (request == PTRACE_SPARC_DETACH)
			request = PTRACE_DETACH;
		ret = ptrace_request(child, request, addr, data);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

यंत्रlinkage पूर्णांक syscall_trace(काष्ठा pt_regs *regs, पूर्णांक syscall_निकास_p)
अणु
	पूर्णांक ret = 0;

	अगर (test_thपढ़ो_flag(TIF_SYSCALL_TRACE)) अणु
		अगर (syscall_निकास_p)
			tracehook_report_syscall_निकास(regs, 0);
		अन्यथा
			ret = tracehook_report_syscall_entry(regs);
	पूर्ण

	वापस ret;
पूर्ण
