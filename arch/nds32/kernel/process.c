<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/delay.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/proc-fns.h>
#समावेश <यंत्र/fpu.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/reboot.h>

#अगर IS_ENABLED(CONFIG_LAZY_FPU)
काष्ठा task_काष्ठा *last_task_used_math;
#पूर्ण_अगर

बाह्य व्योम setup_mm_क्रम_reboot(अक्षर mode);

बाह्य अंतरभूत व्योम arch_reset(अक्षर mode)
अणु
	अगर (mode == 's') अणु
		/* Use cpu handler, jump to 0 */
		cpu_reset(0);
	पूर्ण
पूर्ण

व्योम (*pm_घातer_off) (व्योम);
EXPORT_SYMBOL(pm_घातer_off);

अटल अक्षर reboot_mode_nds32 = 'h';

पूर्णांक __init reboot_setup(अक्षर *str)
अणु
	reboot_mode_nds32 = str[0];
	वापस 1;
पूर्ण

अटल पूर्णांक cpub_pwroff(व्योम)
अणु
	वापस 0;
पूर्ण

__setup("reboot=", reboot_setup);

व्योम machine_halt(व्योम)
अणु
	cpub_pwroff();
पूर्ण

EXPORT_SYMBOL(machine_halt);

व्योम machine_घातer_off(व्योम)
अणु
	अगर (pm_घातer_off)
		pm_घातer_off();
पूर्ण

EXPORT_SYMBOL(machine_घातer_off);

व्योम machine_restart(अक्षर *cmd)
अणु
	/*
	 * Clean and disable cache, and turn off पूर्णांकerrupts
	 */
	cpu_proc_fin();

	/*
	 * Tell the mm प्रणाली that we are going to reboot -
	 * we may need it to insert some 1:1 mappings so that
	 * soft boot works.
	 */
	setup_mm_क्रम_reboot(reboot_mode_nds32);

	/* Execute kernel restart handler call chain */
	करो_kernel_restart(cmd);

	/*
	 * Now call the architecture specअगरic reboot code.
	 */
	arch_reset(reboot_mode_nds32);

	/*
	 * Whoops - the architecture was unable to reboot.
	 * Tell the user!
	 */
	mdelay(1000);
	pr_info("Reboot failed -- System halted\n");
	जबतक (1) ;
पूर्ण

EXPORT_SYMBOL(machine_restart);

व्योम show_regs(काष्ठा pt_regs *regs)
अणु
	prपूर्णांकk("PC is at %pS\n", (व्योम *)inकाष्ठाion_poपूर्णांकer(regs));
	prपूर्णांकk("LP is at %pS\n", (व्योम *)regs->lp);
	pr_info("pc : [<%08lx>]    lp : [<%08lx>]    %s\n"
		"sp : %08lx  fp : %08lx  gp : %08lx\n",
		inकाष्ठाion_poपूर्णांकer(regs),
		regs->lp, prपूर्णांक_taपूर्णांकed(), regs->sp, regs->fp, regs->gp);
	pr_info("r25: %08lx  r24: %08lx\n", regs->uregs[25], regs->uregs[24]);

	pr_info("r23: %08lx  r22: %08lx  r21: %08lx  r20: %08lx\n",
		regs->uregs[23], regs->uregs[22],
		regs->uregs[21], regs->uregs[20]);
	pr_info("r19: %08lx  r18: %08lx  r17: %08lx  r16: %08lx\n",
		regs->uregs[19], regs->uregs[18],
		regs->uregs[17], regs->uregs[16]);
	pr_info("r15: %08lx  r14: %08lx  r13: %08lx  r12: %08lx\n",
		regs->uregs[15], regs->uregs[14],
		regs->uregs[13], regs->uregs[12]);
	pr_info("r11: %08lx  r10: %08lx  r9 : %08lx  r8 : %08lx\n",
		regs->uregs[11], regs->uregs[10],
		regs->uregs[9], regs->uregs[8]);
	pr_info("r7 : %08lx  r6 : %08lx  r5 : %08lx  r4 : %08lx\n",
		regs->uregs[7], regs->uregs[6], regs->uregs[5], regs->uregs[4]);
	pr_info("r3 : %08lx  r2 : %08lx  r1 : %08lx  r0 : %08lx\n",
		regs->uregs[3], regs->uregs[2], regs->uregs[1], regs->uregs[0]);
	pr_info("  IRQs o%s  Segment %s\n",
		पूर्णांकerrupts_enabled(regs) ? "n" : "ff",
		uaccess_kernel() ? "kernel" : "user");
पूर्ण

EXPORT_SYMBOL(show_regs);

व्योम निकास_thपढ़ो(काष्ठा task_काष्ठा *tsk)
अणु
#अगर defined(CONFIG_FPU) && defined(CONFIG_LAZY_FPU)
	अगर (last_task_used_math == tsk)
		last_task_used_math = शून्य;
#पूर्ण_अगर
पूर्ण

व्योम flush_thपढ़ो(व्योम)
अणु
#अगर defined(CONFIG_FPU)
	clear_fpu(task_pt_regs(current));
	clear_used_math();
# अगरdef CONFIG_LAZY_FPU
	अगर (last_task_used_math == current)
		last_task_used_math = शून्य;
# endअगर
#पूर्ण_अगर
पूर्ण

DEFINE_PER_CPU(काष्ठा task_काष्ठा *, __entry_task);

यंत्रlinkage व्योम ret_from_विभाजन(व्योम) __यंत्र__("ret_from_fork");
पूर्णांक copy_thपढ़ो(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ stack_start,
		अचिन्हित दीर्घ stk_sz, काष्ठा task_काष्ठा *p, अचिन्हित दीर्घ tls)
अणु
	काष्ठा pt_regs *childregs = task_pt_regs(p);

	स_रखो(&p->thपढ़ो.cpu_context, 0, माप(काष्ठा cpu_context));

	अगर (unlikely(p->flags & (PF_KTHREAD | PF_IO_WORKER))) अणु
		स_रखो(childregs, 0, माप(काष्ठा pt_regs));
		/* kernel thपढ़ो fn */
		p->thपढ़ो.cpu_context.r6 = stack_start;
		/* kernel thपढ़ो argument */
		p->thपढ़ो.cpu_context.r7 = stk_sz;
	पूर्ण अन्यथा अणु
		*childregs = *current_pt_regs();
		अगर (stack_start)
			childregs->sp = stack_start;
		/* child get zero as ret. */
		childregs->uregs[0] = 0;
		childregs->osp = 0;
		अगर (clone_flags & CLONE_SETTLS)
			childregs->uregs[25] = tls;
	पूर्ण
	/* cpu context चयनing  */
	p->thपढ़ो.cpu_context.pc = (अचिन्हित दीर्घ)ret_from_विभाजन;
	p->thपढ़ो.cpu_context.sp = (अचिन्हित दीर्घ)childregs;

#अगर IS_ENABLED(CONFIG_FPU)
	अगर (used_math()) अणु
# अगर !IS_ENABLED(CONFIG_LAZY_FPU)
		unlazy_fpu(current);
# अन्यथा
		preempt_disable();
		अगर (last_task_used_math == current)
			save_fpu(current);
		preempt_enable();
# endअगर
		p->thपढ़ो.fpu = current->thपढ़ो.fpu;
		clear_fpu(task_pt_regs(p));
		set_stopped_child_used_math(p);
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HWZOL
	childregs->lb = 0;
	childregs->le = 0;
	childregs->lc = 0;
#पूर्ण_अगर

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_FPU)
काष्ठा task_काष्ठा *_चयन_fpu(काष्ठा task_काष्ठा *prev, काष्ठा task_काष्ठा *next)
अणु
#अगर !IS_ENABLED(CONFIG_LAZY_FPU)
	unlazy_fpu(prev);
#पूर्ण_अगर
	अगर (!(next->flags & PF_KTHREAD))
		clear_fpu(task_pt_regs(next));
	वापस prev;
पूर्ण
#पूर्ण_अगर

/*
 * fill in the fpe काष्ठाure क्रम a core dump...
 */
पूर्णांक dump_fpu(काष्ठा pt_regs *regs, elf_fpregset_t * fpu)
अणु
	पूर्णांक fpvalid = 0;
#अगर IS_ENABLED(CONFIG_FPU)
	काष्ठा task_काष्ठा *tsk = current;

	fpvalid = tsk_used_math(tsk);
	अगर (fpvalid) अणु
		lose_fpu();
		स_नकल(fpu, &tsk->thपढ़ो.fpu, माप(*fpu));
	पूर्ण
#पूर्ण_अगर
	वापस fpvalid;
पूर्ण

EXPORT_SYMBOL(dump_fpu);

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ fp, lr;
	अचिन्हित दीर्घ stack_start, stack_end;
	पूर्णांक count = 0;

	अगर (!p || p == current || p->state == TASK_RUNNING)
		वापस 0;

	अगर (IS_ENABLED(CONFIG_FRAME_POINTER)) अणु
		stack_start = (अचिन्हित दीर्घ)end_of_stack(p);
		stack_end = (अचिन्हित दीर्घ)task_stack_page(p) + THREAD_SIZE;

		fp = thपढ़ो_saved_fp(p);
		करो अणु
			अगर (fp < stack_start || fp > stack_end)
				वापस 0;
			lr = ((अचिन्हित दीर्घ *)fp)[0];
			अगर (!in_sched_functions(lr))
				वापस lr;
			fp = *(अचिन्हित दीर्घ *)(fp + 4);
		पूर्ण जबतक (count++ < 16);
	पूर्ण
	वापस 0;
पूर्ण

EXPORT_SYMBOL(get_wchan);
