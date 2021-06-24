<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*  linux/arch/sparc/kernel/process.c
 *
 *  Copyright (C) 1995, 2008 David S. Miller (davem@davemloft.net)
 *  Copyright (C) 1996 Eddie C. Dost   (ecd@skynet.be)
 */

/*
 * This file handles the architecture-dependent parts of process handling..
 */

#समावेश <मानकतर्क.स>

#समावेश <linux/elfcore.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/ptrace.h>
#समावेश <linux/user.h>
#समावेश <linux/smp.h>
#समावेश <linux/reboot.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>
#समावेश <linux/cpu.h>

#समावेश <यंत्र/auxपन.स>
#समावेश <यंत्र/oplib.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/psr.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/setup.h>

#समावेश "kernel.h"

/* 
 * Power management idle function 
 * Set in pm platक्रमm drivers (apc.c and pmc.c)
 */
व्योम (*sparc_idle)(व्योम);

/* 
 * Power-off handler instantiation क्रम pm.h compliance
 * This is करोne via auxio, but could be used as a fallback
 * handler when auxio is not present-- unused क्रम now...
 */
व्योम (*pm_घातer_off)(व्योम) = machine_घातer_off;
EXPORT_SYMBOL(pm_घातer_off);

/*
 * sysctl - toggle घातer-off restriction क्रम serial console 
 * प्रणालीs in machine_घातer_off()
 */
पूर्णांक scons_pwroff = 1;

बाह्य व्योम fpsave(अचिन्हित दीर्घ *, अचिन्हित दीर्घ *, व्योम *, अचिन्हित दीर्घ *);

काष्ठा task_काष्ठा *last_task_used_math = शून्य;
काष्ठा thपढ़ो_info *current_set[NR_CPUS];

/* Idle loop support. */
व्योम arch_cpu_idle(व्योम)
अणु
	अगर (sparc_idle)
		(*sparc_idle)();
	raw_local_irq_enable();
पूर्ण

/* XXX cli/sti -> local_irq_xxx here, check this works once SMP is fixed. */
व्योम machine_halt(व्योम)
अणु
	local_irq_enable();
	mdelay(8);
	local_irq_disable();
	prom_halt();
	panic("Halt failed!");
पूर्ण

व्योम machine_restart(अक्षर * cmd)
अणु
	अक्षर *p;
	
	local_irq_enable();
	mdelay(8);
	local_irq_disable();

	p = म_अक्षर (reboot_command, '\n');
	अगर (p) *p = 0;
	अगर (cmd)
		prom_reboot(cmd);
	अगर (*reboot_command)
		prom_reboot(reboot_command);
	prom_feval ("reset");
	panic("Reboot failed!");
पूर्ण

व्योम machine_घातer_off(व्योम)
अणु
	अगर (auxio_घातer_रेजिस्टर &&
	    (!of_node_is_type(of_console_device, "serial") || scons_pwroff)) अणु
		u8 घातer_रेजिस्टर = sbus_पढ़ोb(auxio_घातer_रेजिस्टर);
		घातer_रेजिस्टर |= AUXIO_POWER_OFF;
		sbus_ग_लिखोb(घातer_रेजिस्टर, auxio_घातer_रेजिस्टर);
	पूर्ण

	machine_halt();
पूर्ण

व्योम show_regs(काष्ठा pt_regs *r)
अणु
	काष्ठा reg_winकरोw32 *rw = (काष्ठा reg_winकरोw32 *) r->u_regs[14];

	show_regs_prपूर्णांक_info(KERN_DEFAULT);

        prपूर्णांकk("PSR: %08lx PC: %08lx NPC: %08lx Y: %08lx    %s\n",
	       r->psr, r->pc, r->npc, r->y, prपूर्णांक_taपूर्णांकed());
	prपूर्णांकk("PC: <%pS>\n", (व्योम *) r->pc);
	prपूर्णांकk("%%G: %08lx %08lx  %08lx %08lx  %08lx %08lx  %08lx %08lx\n",
	       r->u_regs[0], r->u_regs[1], r->u_regs[2], r->u_regs[3],
	       r->u_regs[4], r->u_regs[5], r->u_regs[6], r->u_regs[7]);
	prपूर्णांकk("%%O: %08lx %08lx  %08lx %08lx  %08lx %08lx  %08lx %08lx\n",
	       r->u_regs[8], r->u_regs[9], r->u_regs[10], r->u_regs[11],
	       r->u_regs[12], r->u_regs[13], r->u_regs[14], r->u_regs[15]);
	prपूर्णांकk("RPC: <%pS>\n", (व्योम *) r->u_regs[15]);

	prपूर्णांकk("%%L: %08lx %08lx  %08lx %08lx  %08lx %08lx  %08lx %08lx\n",
	       rw->locals[0], rw->locals[1], rw->locals[2], rw->locals[3],
	       rw->locals[4], rw->locals[5], rw->locals[6], rw->locals[7]);
	prपूर्णांकk("%%I: %08lx %08lx  %08lx %08lx  %08lx %08lx  %08lx %08lx\n",
	       rw->ins[0], rw->ins[1], rw->ins[2], rw->ins[3],
	       rw->ins[4], rw->ins[5], rw->ins[6], rw->ins[7]);
पूर्ण

/*
 * The show_stack() is बाह्यal API which we करो not use ourselves.
 * The oops is prपूर्णांकed in die_अगर_kernel.
 */
व्योम show_stack(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ *_ksp, स्थिर अक्षर *loglvl)
अणु
	अचिन्हित दीर्घ pc, fp;
	अचिन्हित दीर्घ task_base;
	काष्ठा reg_winकरोw32 *rw;
	पूर्णांक count = 0;

	अगर (!tsk)
		tsk = current;

	अगर (tsk == current && !_ksp)
		__यंत्र__ __अस्थिर__("mov	%%fp, %0" : "=r" (_ksp));

	task_base = (अचिन्हित दीर्घ) task_stack_page(tsk);
	fp = (अचिन्हित दीर्घ) _ksp;
	करो अणु
		/* Bogus frame poपूर्णांकer? */
		अगर (fp < (task_base + माप(काष्ठा thपढ़ो_info)) ||
		    fp >= (task_base + (PAGE_SIZE << 1)))
			अवरोध;
		rw = (काष्ठा reg_winकरोw32 *) fp;
		pc = rw->ins[7];
		prपूर्णांकk("%s[%08lx : ", loglvl, pc);
		prपूर्णांकk("%s%pS ] ", loglvl, (व्योम *) pc);
		fp = rw->ins[6];
	पूर्ण जबतक (++count < 16);
	prपूर्णांकk("%s\n", loglvl);
पूर्ण

/*
 * Free current thपढ़ो data काष्ठाures etc..
 */
व्योम निकास_thपढ़ो(काष्ठा task_काष्ठा *tsk)
अणु
#अगर_अघोषित CONFIG_SMP
	अगर (last_task_used_math == tsk) अणु
#अन्यथा
	अगर (test_tsk_thपढ़ो_flag(tsk, TIF_USEDFPU)) अणु
#पूर्ण_अगर
		/* Keep process from leaving FPU in a bogon state. */
		put_psr(get_psr() | PSR_EF);
		fpsave(&tsk->thपढ़ो.भग्न_regs[0], &tsk->thपढ़ो.fsr,
		       &tsk->thपढ़ो.fpqueue[0], &tsk->thपढ़ो.fpqdepth);
#अगर_अघोषित CONFIG_SMP
		last_task_used_math = शून्य;
#अन्यथा
		clear_ti_thपढ़ो_flag(task_thपढ़ो_info(tsk), TIF_USEDFPU);
#पूर्ण_अगर
	पूर्ण
पूर्ण

व्योम flush_thपढ़ो(व्योम)
अणु
	current_thपढ़ो_info()->w_saved = 0;

#अगर_अघोषित CONFIG_SMP
	अगर(last_task_used_math == current) अणु
#अन्यथा
	अगर (test_thपढ़ो_flag(TIF_USEDFPU)) अणु
#पूर्ण_अगर
		/* Clean the fpu. */
		put_psr(get_psr() | PSR_EF);
		fpsave(&current->thपढ़ो.भग्न_regs[0], &current->thपढ़ो.fsr,
		       &current->thपढ़ो.fpqueue[0], &current->thपढ़ो.fpqdepth);
#अगर_अघोषित CONFIG_SMP
		last_task_used_math = शून्य;
#अन्यथा
		clear_thपढ़ो_flag(TIF_USEDFPU);
#पूर्ण_अगर
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा sparc_stackf __user *
clone_stackframe(काष्ठा sparc_stackf __user *dst,
		 काष्ठा sparc_stackf __user *src)
अणु
	अचिन्हित दीर्घ size, fp;
	काष्ठा sparc_stackf *पंचांगp;
	काष्ठा sparc_stackf __user *sp;

	अगर (get_user(पंचांगp, &src->fp))
		वापस शून्य;

	fp = (अचिन्हित दीर्घ) पंचांगp;
	size = (fp - ((अचिन्हित दीर्घ) src));
	fp = (अचिन्हित दीर्घ) dst;
	sp = (काष्ठा sparc_stackf __user *)(fp - size); 

	/* करो_विभाजन() grअसल the parent semaphore, we must release it
	 * temporarily so we can build the child clone stack frame
	 * without deadlocking.
	 */
	अगर (__copy_user(sp, src, size))
		sp = शून्य;
	अन्यथा अगर (put_user(fp, &sp->fp))
		sp = शून्य;

	वापस sp;
पूर्ण

/* Copy a Sparc thपढ़ो.  The विभाजन() वापस value conventions
 * under SunOS are nothing लघु of bletcherous:
 * Parent -->  %o0 == childs  pid, %o1 == 0
 * Child  -->  %o0 == parents pid, %o1 == 1
 *
 * NOTE: We have a separate विभाजन kpsr/kwim because
 *       the parent could change these values between
 *       sys_विभाजन invocation and when we reach here
 *       अगर the parent should sleep जबतक trying to
 *       allocate the task_काष्ठा and kernel stack in
 *       करो_विभाजन().
 * XXX See comment above sys_vविभाजन in sparc64. toकरो.
 */
बाह्य व्योम ret_from_विभाजन(व्योम);
बाह्य व्योम ret_from_kernel_thपढ़ो(व्योम);

पूर्णांक copy_thपढ़ो(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ sp, अचिन्हित दीर्घ arg,
		काष्ठा task_काष्ठा *p, अचिन्हित दीर्घ tls)
अणु
	काष्ठा thपढ़ो_info *ti = task_thपढ़ो_info(p);
	काष्ठा pt_regs *childregs, *regs = current_pt_regs();
	अक्षर *new_stack;

#अगर_अघोषित CONFIG_SMP
	अगर(last_task_used_math == current) अणु
#अन्यथा
	अगर (test_thपढ़ो_flag(TIF_USEDFPU)) अणु
#पूर्ण_अगर
		put_psr(get_psr() | PSR_EF);
		fpsave(&p->thपढ़ो.भग्न_regs[0], &p->thपढ़ो.fsr,
		       &p->thपढ़ो.fpqueue[0], &p->thपढ़ो.fpqdepth);
	पूर्ण

	/*
	 *  p->thपढ़ो_info         new_stack   childregs stack bottom
	 *  !                      !           !             !
	 *  V                      V (stk.fr.) V  (pt_regs)  V
	 *  +----- - - - - - ------+===========+=============+
	 */
	new_stack = task_stack_page(p) + THREAD_SIZE;
	new_stack -= STACKFRAME_SZ + TRACEREG_SZ;
	childregs = (काष्ठा pt_regs *) (new_stack + STACKFRAME_SZ);

	/*
	 * A new process must start with पूर्णांकerrupts disabled, see schedule_tail()
	 * and finish_task_चयन(). (If we करो not करो it and अगर a समयr पूर्णांकerrupt
	 * hits beक्रमe we unlock and attempts to take the rq->lock, we deadlock.)
	 *
	 * Thus, kpsr |= PSR_PIL.
	 */
	ti->ksp = (अचिन्हित दीर्घ) new_stack;
	p->thपढ़ो.kregs = childregs;

	अगर (unlikely(p->flags & (PF_KTHREAD | PF_IO_WORKER))) अणु
		बाह्य पूर्णांक nwinकरोws;
		अचिन्हित दीर्घ psr;
		स_रखो(new_stack, 0, STACKFRAME_SZ + TRACEREG_SZ);
		p->thपढ़ो.current_ds = KERNEL_DS;
		ti->kpc = (((अचिन्हित दीर्घ) ret_from_kernel_thपढ़ो) - 0x8);
		childregs->u_regs[UREG_G1] = sp; /* function */
		childregs->u_regs[UREG_G2] = arg;
		psr = childregs->psr = get_psr();
		ti->kpsr = psr | PSR_PIL;
		ti->kwim = 1 << (((psr & PSR_CWP) + 1) % nwinकरोws);
		वापस 0;
	पूर्ण
	स_नकल(new_stack, (अक्षर *)regs - STACKFRAME_SZ, STACKFRAME_SZ + TRACEREG_SZ);
	childregs->u_regs[UREG_FP] = sp;
	p->thपढ़ो.current_ds = USER_DS;
	ti->kpc = (((अचिन्हित दीर्घ) ret_from_विभाजन) - 0x8);
	ti->kpsr = current->thपढ़ो.विभाजन_kpsr | PSR_PIL;
	ti->kwim = current->thपढ़ो.विभाजन_kwim;

	अगर (sp != regs->u_regs[UREG_FP]) अणु
		काष्ठा sparc_stackf __user *childstack;
		काष्ठा sparc_stackf __user *parentstack;

		/*
		 * This is a clone() call with supplied user stack.
		 * Set some valid stack frames to give to the child.
		 */
		childstack = (काष्ठा sparc_stackf __user *)
			(sp & ~0xfUL);
		parentstack = (काष्ठा sparc_stackf __user *)
			regs->u_regs[UREG_FP];

#अगर 0
		prपूर्णांकk("clone: parent stack:\n");
		show_stackframe(parentstack);
#पूर्ण_अगर

		childstack = clone_stackframe(childstack, parentstack);
		अगर (!childstack)
			वापस -EFAULT;

#अगर 0
		prपूर्णांकk("clone: child stack:\n");
		show_stackframe(childstack);
#पूर्ण_अगर

		childregs->u_regs[UREG_FP] = (अचिन्हित दीर्घ)childstack;
	पूर्ण

#अगर_घोषित CONFIG_SMP
	/* FPU must be disabled on SMP. */
	childregs->psr &= ~PSR_EF;
	clear_tsk_thपढ़ो_flag(p, TIF_USEDFPU);
#पूर्ण_अगर

	/* Set the वापस value क्रम the child. */
	childregs->u_regs[UREG_I0] = current->pid;
	childregs->u_regs[UREG_I1] = 1;

	/* Set the वापस value क्रम the parent. */
	regs->u_regs[UREG_I1] = 0;

	अगर (clone_flags & CLONE_SETTLS)
		childregs->u_regs[UREG_G7] = tls;

	वापस 0;
पूर्ण

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित दीर्घ pc, fp, bias = 0;
	अचिन्हित दीर्घ task_base = (अचिन्हित दीर्घ) task;
        अचिन्हित दीर्घ ret = 0;
	काष्ठा reg_winकरोw32 *rw;
	पूर्णांक count = 0;

	अगर (!task || task == current ||
            task->state == TASK_RUNNING)
		जाओ out;

	fp = task_thपढ़ो_info(task)->ksp + bias;
	करो अणु
		/* Bogus frame poपूर्णांकer? */
		अगर (fp < (task_base + माप(काष्ठा thपढ़ो_info)) ||
		    fp >= (task_base + (2 * PAGE_SIZE)))
			अवरोध;
		rw = (काष्ठा reg_winकरोw32 *) fp;
		pc = rw->ins[7];
		अगर (!in_sched_functions(pc)) अणु
			ret = pc;
			जाओ out;
		पूर्ण
		fp = rw->ins[6] + bias;
	पूर्ण जबतक (++count < 16);

out:
	वापस ret;
पूर्ण

