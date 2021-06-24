<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/m68k/kernel/process.c
 *
 *  Copyright (C) 1995  Hamish Macकरोnald
 *
 *  68060 fixes by Jesper Skov
 */

/*
 * This file handles the architecture-dependent parts of process handling..
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/smp.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/user.h>
#समावेश <linux/reboot.h>
#समावेश <linux/init_task.h>
#समावेश <linux/mqueue.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/setup.h>


यंत्रlinkage व्योम ret_from_विभाजन(व्योम);
यंत्रlinkage व्योम ret_from_kernel_thपढ़ो(व्योम);

व्योम arch_cpu_idle(व्योम)
अणु
#अगर defined(MACH_ATARI_ONLY)
	/* block out HSYNC on the atari (falcon) */
	__यंत्र__("stop #0x2200" : : : "cc");
#अन्यथा
	__यंत्र__("stop #0x2000" : : : "cc");
#पूर्ण_अगर
पूर्ण

व्योम machine_restart(अक्षर * __unused)
अणु
	अगर (mach_reset)
		mach_reset();
	क्रम (;;);
पूर्ण

व्योम machine_halt(व्योम)
अणु
	अगर (mach_halt)
		mach_halt();
	क्रम (;;);
पूर्ण

व्योम machine_घातer_off(व्योम)
अणु
	अगर (mach_घातer_off)
		mach_घातer_off();
	क्रम (;;);
पूर्ण

व्योम (*pm_घातer_off)(व्योम) = machine_घातer_off;
EXPORT_SYMBOL(pm_घातer_off);

व्योम show_regs(काष्ठा pt_regs * regs)
अणु
	pr_info("Format %02x  Vector: %04x  PC: %08lx  Status: %04x    %s\n",
		regs->क्रमmat, regs->vector, regs->pc, regs->sr,
		prपूर्णांक_taपूर्णांकed());
	pr_info("ORIG_D0: %08lx  D0: %08lx  A2: %08lx  A1: %08lx\n",
		regs->orig_d0, regs->d0, regs->a2, regs->a1);
	pr_info("A0: %08lx  D5: %08lx  D4: %08lx\n", regs->a0, regs->d5,
		regs->d4);
	pr_info("D3: %08lx  D2: %08lx  D1: %08lx\n", regs->d3, regs->d2,
		regs->d1);
	अगर (!(regs->sr & PS_S))
		pr_info("USP: %08lx\n", rdusp());
पूर्ण

व्योम flush_thपढ़ो(व्योम)
अणु
	current->thपढ़ो.fs = __USER_DS;
#अगर_घोषित CONFIG_FPU
	अगर (!FPU_IS_EMU) अणु
		अचिन्हित दीर्घ zero = 0;
		यंत्र अस्थिर("frestore %0": :"m" (zero));
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * Why not generic sys_clone, you ask?  m68k passes all arguments on stack.
 * And we need all रेजिस्टरs saved, which means a bunch of stuff pushed
 * on top of pt_regs, which means that sys_clone() arguments would be
 * buried.  We could, of course, copy them, but it's too costly क्रम no
 * good reason - generic clone() would have to copy them *again* क्रम
 * kernel_clone() anyway.  So in this हाल it's actually better to pass pt_regs *
 * and extract arguments क्रम kernel_clone() from there.  Eventually we might
 * go क्रम calling kernel_clone() directly from the wrapper, but only after we
 * are finished with kernel_clone() prototype conversion.
 */
यंत्रlinkage पूर्णांक m68k_clone(काष्ठा pt_regs *regs)
अणु
	/* regs will be equal to current_pt_regs() */
	काष्ठा kernel_clone_args args = अणु
		.flags		= regs->d1 & ~CSIGNAL,
		.pidfd		= (पूर्णांक __user *)regs->d3,
		.child_tid	= (पूर्णांक __user *)regs->d4,
		.parent_tid	= (पूर्णांक __user *)regs->d3,
		.निकास_संकेत	= regs->d1 & CSIGNAL,
		.stack		= regs->d2,
		.tls		= regs->d5,
	पूर्ण;

	वापस kernel_clone(&args);
पूर्ण

/*
 * Because extra रेजिस्टरs are saved on the stack after the sys_clone3()
 * arguments, this C wrapper extracts them from pt_regs * and then calls the
 * generic sys_clone3() implementation.
 */
यंत्रlinkage पूर्णांक m68k_clone3(काष्ठा pt_regs *regs)
अणु
	वापस sys_clone3((काष्ठा clone_args __user *)regs->d1, regs->d2);
पूर्ण

पूर्णांक copy_thपढ़ो(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ usp, अचिन्हित दीर्घ arg,
		काष्ठा task_काष्ठा *p, अचिन्हित दीर्घ tls)
अणु
	काष्ठा विभाजन_frame अणु
		काष्ठा चयन_stack sw;
		काष्ठा pt_regs regs;
	पूर्ण *frame;

	frame = (काष्ठा विभाजन_frame *) (task_stack_page(p) + THREAD_SIZE) - 1;

	p->thपढ़ो.ksp = (अचिन्हित दीर्घ)frame;
	p->thपढ़ो.esp0 = (अचिन्हित दीर्घ)&frame->regs;

	/*
	 * Must save the current SFC/DFC value, NOT the value when
	 * the parent was last descheduled - RGH  10-08-96
	 */
	p->thपढ़ो.fs = get_fs().seg;

	अगर (unlikely(p->flags & (PF_KTHREAD | PF_IO_WORKER))) अणु
		/* kernel thपढ़ो */
		स_रखो(frame, 0, माप(काष्ठा विभाजन_frame));
		frame->regs.sr = PS_S;
		frame->sw.a3 = usp; /* function */
		frame->sw.d7 = arg;
		frame->sw.retpc = (अचिन्हित दीर्घ)ret_from_kernel_thपढ़ो;
		p->thपढ़ो.usp = 0;
		वापस 0;
	पूर्ण
	स_नकल(frame, container_of(current_pt_regs(), काष्ठा विभाजन_frame, regs),
		माप(काष्ठा विभाजन_frame));
	frame->regs.d0 = 0;
	frame->sw.retpc = (अचिन्हित दीर्घ)ret_from_विभाजन;
	p->thपढ़ो.usp = usp ?: rdusp();

	अगर (clone_flags & CLONE_SETTLS)
		task_thपढ़ो_info(p)->tp_value = tls;

#अगर_घोषित CONFIG_FPU
	अगर (!FPU_IS_EMU) अणु
		/* Copy the current fpu state */
		यंत्र अस्थिर ("fsave %0" : : "m" (p->thपढ़ो.fpstate[0]) : "memory");

		अगर (!CPU_IS_060 ? p->thपढ़ो.fpstate[0] : p->thपढ़ो.fpstate[2]) अणु
			अगर (CPU_IS_COLDFIRE) अणु
				यंत्र अस्थिर ("fmovemd %/fp0-%/fp7,%0\n\t"
					      "fmovel %/fpiar,%1\n\t"
					      "fmovel %/fpcr,%2\n\t"
					      "fmovel %/fpsr,%3"
					      :
					      : "m" (p->thपढ़ो.fp[0]),
						"m" (p->thपढ़ो.fpcntl[0]),
						"m" (p->thपढ़ो.fpcntl[1]),
						"m" (p->thपढ़ो.fpcntl[2])
					      : "memory");
			पूर्ण अन्यथा अणु
				यंत्र अस्थिर ("fmovemx %/fp0-%/fp7,%0\n\t"
					      "fmoveml %/fpiar/%/fpcr/%/fpsr,%1"
					      :
					      : "m" (p->thपढ़ो.fp[0]),
						"m" (p->thपढ़ो.fpcntl[0])
					      : "memory");
			पूर्ण
		पूर्ण

		/* Restore the state in हाल the fpu was busy */
		यंत्र अस्थिर ("frestore %0" : : "m" (p->thपढ़ो.fpstate[0]));
	पूर्ण
#पूर्ण_अगर /* CONFIG_FPU */

	वापस 0;
पूर्ण

/* Fill in the fpu काष्ठाure क्रम a core dump.  */
पूर्णांक dump_fpu (काष्ठा pt_regs *regs, काष्ठा user_m68kfp_काष्ठा *fpu)
अणु
	अगर (FPU_IS_EMU) अणु
		पूर्णांक i;

		स_नकल(fpu->fpcntl, current->thपढ़ो.fpcntl, 12);
		स_नकल(fpu->fpregs, current->thपढ़ो.fp, 96);
		/* Convert पूर्णांकernal fpu reg representation
		 * पूर्णांकo दीर्घ द्विगुन क्रमmat
		 */
		क्रम (i = 0; i < 24; i += 3)
			fpu->fpregs[i] = ((fpu->fpregs[i] & 0xffff0000) << 15) |
			                 ((fpu->fpregs[i] & 0x0000ffff) << 16);
		वापस 1;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_FPU)) अणु
		अक्षर fpustate[216];

		/* First dump the fpu context to aव्योम protocol violation.  */
		यंत्र अस्थिर ("fsave %0" :: "m" (fpustate[0]) : "memory");
		अगर (!CPU_IS_060 ? !fpustate[0] : !fpustate[2])
			वापस 0;

		अगर (CPU_IS_COLDFIRE) अणु
			यंत्र अस्थिर ("fmovel %/fpiar,%0\n\t"
				      "fmovel %/fpcr,%1\n\t"
				      "fmovel %/fpsr,%2\n\t"
				      "fmovemd %/fp0-%/fp7,%3"
				      :
				      : "m" (fpu->fpcntl[0]),
					"m" (fpu->fpcntl[1]),
					"m" (fpu->fpcntl[2]),
					"m" (fpu->fpregs[0])
				      : "memory");
		पूर्ण अन्यथा अणु
			यंत्र अस्थिर ("fmovem %/fpiar/%/fpcr/%/fpsr,%0"
				      :
				      : "m" (fpu->fpcntl[0])
				      : "memory");
			यंत्र अस्थिर ("fmovemx %/fp0-%/fp7,%0"
				      :
				      : "m" (fpu->fpregs[0])
				      : "memory");
		पूर्ण
	पूर्ण

	वापस 1;
पूर्ण
EXPORT_SYMBOL(dump_fpu);

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ fp, pc;
	अचिन्हित दीर्घ stack_page;
	पूर्णांक count = 0;
	अगर (!p || p == current || p->state == TASK_RUNNING)
		वापस 0;

	stack_page = (अचिन्हित दीर्घ)task_stack_page(p);
	fp = ((काष्ठा चयन_stack *)p->thपढ़ो.ksp)->a6;
	करो अणु
		अगर (fp < stack_page+माप(काष्ठा thपढ़ो_info) ||
		    fp >= 8184+stack_page)
			वापस 0;
		pc = ((अचिन्हित दीर्घ *)fp)[1];
		अगर (!in_sched_functions(pc))
			वापस pc;
		fp = *(अचिन्हित दीर्घ *) fp;
	पूर्ण जबतक (count++ < 16);
	वापस 0;
पूर्ण
