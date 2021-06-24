<शैली गुरु>
/*
 * Architecture-dependent parts of process handling.
 *
 * Copyright (C) 2013 Altera Corporation
 * Copyright (C) 2010 Tobias Klauser <tklauser@distanz.ch>
 * Copyright (C) 2009 Wind River Systems Inc
 *   Implemented by fredrik.markstrom@gmail.com and ivarholmqvist@gmail.com
 * Copyright (C) 2004 Microtronix Datacom Ltd
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/tick.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/cpuinfo.h>

यंत्रlinkage व्योम ret_from_विभाजन(व्योम);
यंत्रlinkage व्योम ret_from_kernel_thपढ़ो(व्योम);

व्योम (*pm_घातer_off)(व्योम) = शून्य;
EXPORT_SYMBOL(pm_घातer_off);

व्योम arch_cpu_idle(व्योम)
अणु
	raw_local_irq_enable();
पूर्ण

/*
 * The development boards have no way to pull a board reset. Just jump to the
 * cpu reset address and let the boot loader or the code in head.S take care of
 * resetting peripherals.
 */
व्योम machine_restart(अक्षर *__unused)
अणु
	pr_notice("Machine restart (%08x)...\n", cpuinfo.reset_addr);
	local_irq_disable();
	__यंत्र__ __अस्थिर__ (
	"jmp	%0\n\t"
	:
	: "r" (cpuinfo.reset_addr)
	: "r4");
पूर्ण

व्योम machine_halt(व्योम)
अणु
	pr_notice("Machine halt...\n");
	local_irq_disable();
	क्रम (;;)
		;
पूर्ण

/*
 * There is no way to घातer off the development boards. So just spin क्रम now. If
 * we ever have a way of resetting a board using a GPIO we should add that here.
 */
व्योम machine_घातer_off(व्योम)
अणु
	pr_notice("Machine power off...\n");
	local_irq_disable();
	क्रम (;;)
		;
पूर्ण

व्योम show_regs(काष्ठा pt_regs *regs)
अणु
	pr_notice("\n");
	show_regs_prपूर्णांक_info(KERN_DEFAULT);

	pr_notice("r1: %08lx r2: %08lx r3: %08lx r4: %08lx\n",
		regs->r1,  regs->r2,  regs->r3,  regs->r4);

	pr_notice("r5: %08lx r6: %08lx r7: %08lx r8: %08lx\n",
		regs->r5,  regs->r6,  regs->r7,  regs->r8);

	pr_notice("r9: %08lx r10: %08lx r11: %08lx r12: %08lx\n",
		regs->r9,  regs->r10, regs->r11, regs->r12);

	pr_notice("r13: %08lx r14: %08lx r15: %08lx\n",
		regs->r13, regs->r14, regs->r15);

	pr_notice("ra: %08lx fp:  %08lx sp: %08lx gp: %08lx\n",
		regs->ra,  regs->fp,  regs->sp,  regs->gp);

	pr_notice("ea: %08lx estatus: %08lx\n",
		regs->ea,  regs->estatus);
पूर्ण

व्योम flush_thपढ़ो(व्योम)
अणु
पूर्ण

पूर्णांक copy_thपढ़ो(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ usp, अचिन्हित दीर्घ arg,
		काष्ठा task_काष्ठा *p, अचिन्हित दीर्घ tls)
अणु
	काष्ठा pt_regs *childregs = task_pt_regs(p);
	काष्ठा pt_regs *regs;
	काष्ठा चयन_stack *stack;
	काष्ठा चयन_stack *childstack =
		((काष्ठा चयन_stack *)childregs) - 1;

	अगर (unlikely(p->flags & (PF_KTHREAD | PF_IO_WORKER))) अणु
		स_रखो(childstack, 0,
			माप(काष्ठा चयन_stack) + माप(काष्ठा pt_regs));

		childstack->r16 = usp;		/* fn */
		childstack->r17 = arg;
		childstack->ra = (अचिन्हित दीर्घ) ret_from_kernel_thपढ़ो;
		childregs->estatus = STATUS_PIE;
		childregs->sp = (अचिन्हित दीर्घ) childstack;

		p->thपढ़ो.ksp = (अचिन्हित दीर्घ) childstack;
		p->thपढ़ो.kregs = childregs;
		वापस 0;
	पूर्ण

	regs = current_pt_regs();
	*childregs = *regs;
	childregs->r2 = 0;	/* Set the वापस value क्रम the child. */
	childregs->r7 = 0;

	stack = ((काष्ठा चयन_stack *) regs) - 1;
	*childstack = *stack;
	childstack->ra = (अचिन्हित दीर्घ)ret_from_विभाजन;
	p->thपढ़ो.kregs = childregs;
	p->thपढ़ो.ksp = (अचिन्हित दीर्घ) childstack;

	अगर (usp)
		childregs->sp = usp;

	/* Initialize tls रेजिस्टर. */
	अगर (clone_flags & CLONE_SETTLS)
		childstack->r23 = tls;

	वापस 0;
पूर्ण

/*
 *	Generic dumping code. Used क्रम panic and debug.
 */
व्योम dump(काष्ठा pt_regs *fp)
अणु
	अचिन्हित दीर्घ	*sp;
	अचिन्हित अक्षर	*tp;
	पूर्णांक		i;

	pr_emerg("\nCURRENT PROCESS:\n\n");
	pr_emerg("COMM=%s PID=%d\n", current->comm, current->pid);

	अगर (current->mm) अणु
		pr_emerg("TEXT=%08x-%08x DATA=%08x-%08x BSS=%08x-%08x\n",
			(पूर्णांक) current->mm->start_code,
			(पूर्णांक) current->mm->end_code,
			(पूर्णांक) current->mm->start_data,
			(पूर्णांक) current->mm->end_data,
			(पूर्णांक) current->mm->end_data,
			(पूर्णांक) current->mm->brk);
		pr_emerg("USER-STACK=%08x  KERNEL-STACK=%08x\n\n",
			(पूर्णांक) current->mm->start_stack,
			(पूर्णांक)(((अचिन्हित दीर्घ) current) + THREAD_SIZE));
	पूर्ण

	pr_emerg("PC: %08lx\n", fp->ea);
	pr_emerg("SR: %08lx    SP: %08lx\n",
		(दीर्घ) fp->estatus, (दीर्घ) fp);

	pr_emerg("r1: %08lx    r2: %08lx    r3: %08lx\n",
		fp->r1, fp->r2, fp->r3);

	pr_emerg("r4: %08lx    r5: %08lx    r6: %08lx    r7: %08lx\n",
		fp->r4, fp->r5, fp->r6, fp->r7);
	pr_emerg("r8: %08lx    r9: %08lx    r10: %08lx    r11: %08lx\n",
		fp->r8, fp->r9, fp->r10, fp->r11);
	pr_emerg("r12: %08lx  r13: %08lx    r14: %08lx    r15: %08lx\n",
		fp->r12, fp->r13, fp->r14, fp->r15);
	pr_emerg("or2: %08lx   ra: %08lx     fp: %08lx    sp: %08lx\n",
		fp->orig_r2, fp->ra, fp->fp, fp->sp);
	pr_emerg("\nUSP: %08x   TRAPFRAME: %08x\n",
		(अचिन्हित पूर्णांक) fp->sp, (अचिन्हित पूर्णांक) fp);

	pr_emerg("\nCODE:");
	tp = ((अचिन्हित अक्षर *) fp->ea) - 0x20;
	क्रम (sp = (अचिन्हित दीर्घ *) tp, i = 0; (i < 0x40);  i += 4) अणु
		अगर ((i % 0x10) == 0)
			pr_emerg("\n%08x: ", (पूर्णांक) (tp + i));
		pr_emerg("%08x ", (पूर्णांक) *sp++);
	पूर्ण
	pr_emerg("\n");

	pr_emerg("\nKERNEL STACK:");
	tp = ((अचिन्हित अक्षर *) fp) - 0x40;
	क्रम (sp = (अचिन्हित दीर्घ *) tp, i = 0; (i < 0xc0); i += 4) अणु
		अगर ((i % 0x10) == 0)
			pr_emerg("\n%08x: ", (पूर्णांक) (tp + i));
		pr_emerg("%08x ", (पूर्णांक) *sp++);
	पूर्ण
	pr_emerg("\n");
	pr_emerg("\n");

	pr_emerg("\nUSER STACK:");
	tp = (अचिन्हित अक्षर *) (fp->sp - 0x10);
	क्रम (sp = (अचिन्हित दीर्घ *) tp, i = 0; (i < 0x80); i += 4) अणु
		अगर ((i % 0x10) == 0)
			pr_emerg("\n%08x: ", (पूर्णांक) (tp + i));
		pr_emerg("%08x ", (पूर्णांक) *sp++);
	पूर्ण
	pr_emerg("\n\n");
पूर्ण

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ fp, pc;
	अचिन्हित दीर्घ stack_page;
	पूर्णांक count = 0;

	अगर (!p || p == current || p->state == TASK_RUNNING)
		वापस 0;

	stack_page = (अचिन्हित दीर्घ)p;
	fp = ((काष्ठा चयन_stack *)p->thपढ़ो.ksp)->fp;	/* ;dgt2 */
	करो अणु
		अगर (fp < stack_page+माप(काष्ठा task_काष्ठा) ||
			fp >= 8184+stack_page)	/* ;dgt2;पंचांगp */
			वापस 0;
		pc = ((अचिन्हित दीर्घ *)fp)[1];
		अगर (!in_sched_functions(pc))
			वापस pc;
		fp = *(अचिन्हित दीर्घ *) fp;
	पूर्ण जबतक (count++ < 16);		/* ;dgt2;पंचांगp */
	वापस 0;
पूर्ण

/*
 * Do necessary setup to start up a newly executed thपढ़ो.
 * Will startup in user mode (status_extension = 0).
 */
व्योम start_thपढ़ो(काष्ठा pt_regs *regs, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ sp)
अणु
	स_रखो((व्योम *) regs, 0, माप(काष्ठा pt_regs));
	regs->estatus = ESTATUS_EPIE | ESTATUS_EU;
	regs->ea = pc;
	regs->sp = sp;
पूर्ण

यंत्रlinkage पूर्णांक nios2_clone(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ newsp,
			   पूर्णांक __user *parent_tidptr, पूर्णांक __user *child_tidptr,
			   अचिन्हित दीर्घ tls)
अणु
	काष्ठा kernel_clone_args args = अणु
		.flags		= (lower_32_bits(clone_flags) & ~CSIGNAL),
		.pidfd		= parent_tidptr,
		.child_tid	= child_tidptr,
		.parent_tid	= parent_tidptr,
		.निकास_संकेत	= (lower_32_bits(clone_flags) & CSIGNAL),
		.stack		= newsp,
		.tls		= tls,
	पूर्ण;

	वापस kernel_clone(&args);
पूर्ण
