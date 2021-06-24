<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/arch/h8300/kernel/process.c
 *
 * Yoshinori Sato <ysato@users.sourceक्रमge.jp>
 *
 *  Based on:
 *
 *  linux/arch/m68knommu/kernel/process.c
 *
 *  Copyright (C) 1998  D. Jeff Dionne <jeff@ryeham.ee.ryerson.ca>,
 *                      Kenneth Albanowski <kjahds@kjahds.com>,
 *                      The Silver Hammer Group, Ltd.
 *
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
#समावेश <linux/smp.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/user.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/reboot.h>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/rcupdate.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/setup.h>

व्योम (*pm_घातer_off)(व्योम) = शून्य;
EXPORT_SYMBOL(pm_घातer_off);

यंत्रlinkage व्योम ret_from_विभाजन(व्योम);
यंत्रlinkage व्योम ret_from_kernel_thपढ़ो(व्योम);

/*
 * The idle loop on an H8/300..
 */
व्योम arch_cpu_idle(व्योम)
अणु
	raw_local_irq_enable();
	__यंत्र__("sleep");
पूर्ण

व्योम machine_restart(अक्षर *__unused)
अणु
	local_irq_disable();
	__यंत्र__("jmp @@0");
पूर्ण

व्योम machine_halt(व्योम)
अणु
	local_irq_disable();
	__यंत्र__("sleep");
	क्रम (;;)
		;
पूर्ण

व्योम machine_घातer_off(व्योम)
अणु
	local_irq_disable();
	__यंत्र__("sleep");
	क्रम (;;)
		;
पूर्ण

व्योम show_regs(काष्ठा pt_regs *regs)
अणु
	show_regs_prपूर्णांक_info(KERN_DEFAULT);

	pr_notice("\n");
	pr_notice("PC: %08lx  Status: %02x\n",
	       regs->pc, regs->ccr);
	pr_notice("ORIG_ER0: %08lx ER0: %08lx ER1: %08lx\n",
	       regs->orig_er0, regs->er0, regs->er1);
	pr_notice("ER2: %08lx ER3: %08lx ER4: %08lx ER5: %08lx\n",
	       regs->er2, regs->er3, regs->er4, regs->er5);
	pr_notice("ER6' %08lx ", regs->er6);
	अगर (user_mode(regs))
		prपूर्णांकk("USP: %08lx\n", rdusp());
	अन्यथा
		prपूर्णांकk("\n");
पूर्ण

व्योम flush_thपढ़ो(व्योम)
अणु
पूर्ण

पूर्णांक copy_thपढ़ो(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ usp,
		अचिन्हित दीर्घ topstk, काष्ठा task_काष्ठा *p, अचिन्हित दीर्घ tls)
अणु
	काष्ठा pt_regs *childregs;

	childregs = (काष्ठा pt_regs *) (THREAD_SIZE + task_stack_page(p)) - 1;

	अगर (unlikely(p->flags & (PF_KTHREAD | PF_IO_WORKER))) अणु
		स_रखो(childregs, 0, माप(काष्ठा pt_regs));
		childregs->retpc = (अचिन्हित दीर्घ) ret_from_kernel_thपढ़ो;
		childregs->er4 = topstk; /* arg */
		childregs->er5 = usp; /* fn */
	पूर्ण  अन्यथा अणु
		*childregs = *current_pt_regs();
		childregs->er0 = 0;
		childregs->retpc = (अचिन्हित दीर्घ) ret_from_विभाजन;
		p->thपढ़ो.usp = usp ?: rdusp();
	पूर्ण
	p->thपढ़ो.ksp = (अचिन्हित दीर्घ)childregs;

	वापस 0;
पूर्ण

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ fp, pc;
	अचिन्हित दीर्घ stack_page;
	पूर्णांक count = 0;

	अगर (!p || p == current || p->state == TASK_RUNNING)
		वापस 0;

	stack_page = (अचिन्हित दीर्घ)p;
	fp = ((काष्ठा pt_regs *)p->thपढ़ो.ksp)->er6;
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

/* generic sys_clone is not enough रेजिस्टरs */
यंत्रlinkage पूर्णांक sys_clone(अचिन्हित दीर्घ __user *args)
अणु
	अचिन्हित दीर्घ clone_flags;
	अचिन्हित दीर्घ  newsp;
	uपूर्णांकptr_t parent_tidptr;
	uपूर्णांकptr_t child_tidptr;
	काष्ठा kernel_clone_args kargs = अणुपूर्ण;

	get_user(clone_flags, &args[0]);
	get_user(newsp, &args[1]);
	get_user(parent_tidptr, &args[2]);
	get_user(child_tidptr, &args[3]);

	kargs.flags		= (lower_32_bits(clone_flags) & ~CSIGNAL);
	kargs.pidfd		= (पूर्णांक __user *)parent_tidptr;
	kargs.child_tid		= (पूर्णांक __user *)child_tidptr;
	kargs.parent_tid	= (पूर्णांक __user *)parent_tidptr;
	kargs.निकास_संकेत	= (lower_32_bits(clone_flags) & CSIGNAL);
	kargs.stack		= newsp;

	वापस kernel_clone(&kargs);
पूर्ण
