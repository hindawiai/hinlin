<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/module.h>
#समावेश <linux/version.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/delay.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/ptrace.h>

#समावेश <यंत्र/elf.h>
#समावेश <abi/reg_ops.h>

काष्ठा cpuinfo_csky cpu_data[NR_CPUS];

#अगर_घोषित CONFIG_STACKPROTECTOR
#समावेश <linux/stackprotector.h>
अचिन्हित दीर्घ __stack_chk_guard __पढ़ो_mostly;
EXPORT_SYMBOL(__stack_chk_guard);
#पूर्ण_अगर

यंत्रlinkage व्योम ret_from_विभाजन(व्योम);
यंत्रlinkage व्योम ret_from_kernel_thपढ़ो(व्योम);

/*
 * Some archs flush debug and FPU info here
 */
व्योम flush_thपढ़ो(व्योम)अणुपूर्ण

पूर्णांक copy_thपढ़ो(अचिन्हित दीर्घ clone_flags,
		अचिन्हित दीर्घ usp,
		अचिन्हित दीर्घ kthपढ़ो_arg,
		काष्ठा task_काष्ठा *p,
		अचिन्हित दीर्घ tls)
अणु
	काष्ठा चयन_stack *childstack;
	काष्ठा pt_regs *childregs = task_pt_regs(p);

#अगर_घोषित CONFIG_CPU_HAS_FPU
	save_to_user_fp(&p->thपढ़ो.user_fp);
#पूर्ण_अगर

	childstack = ((काष्ठा चयन_stack *) childregs) - 1;
	स_रखो(childstack, 0, माप(काष्ठा चयन_stack));

	/* setup thपढ़ो.sp क्रम चयन_to !!! */
	p->thपढ़ो.sp = (अचिन्हित दीर्घ)childstack;

	अगर (unlikely(p->flags & (PF_KTHREAD | PF_IO_WORKER))) अणु
		स_रखो(childregs, 0, माप(काष्ठा pt_regs));
		childstack->r15 = (अचिन्हित दीर्घ) ret_from_kernel_thपढ़ो;
		childstack->r10 = kthपढ़ो_arg;
		childstack->r9 = usp;
		childregs->sr = mfcr("psr");
	पूर्ण अन्यथा अणु
		*childregs = *(current_pt_regs());
		अगर (usp)
			childregs->usp = usp;
		अगर (clone_flags & CLONE_SETTLS)
			task_thपढ़ो_info(p)->tp_value = childregs->tls
						      = tls;

		childregs->a0 = 0;
		childstack->r15 = (अचिन्हित दीर्घ) ret_from_विभाजन;
	पूर्ण

	वापस 0;
पूर्ण

/* Fill in the fpu काष्ठाure क्रम a core dump.  */
पूर्णांक dump_fpu(काष्ठा pt_regs *regs, काष्ठा user_fp *fpu)
अणु
	स_नकल(fpu, &current->thपढ़ो.user_fp, माप(*fpu));
	वापस 1;
पूर्ण
EXPORT_SYMBOL(dump_fpu);

पूर्णांक dump_task_regs(काष्ठा task_काष्ठा *tsk, elf_gregset_t *pr_regs)
अणु
	काष्ठा pt_regs *regs = task_pt_regs(tsk);

	/* NOTE: usp is error value. */
	ELF_CORE_COPY_REGS((*pr_regs), regs)

	वापस 1;
पूर्ण

#अगर_अघोषित CONFIG_CPU_PM_NONE
व्योम arch_cpu_idle(व्योम)
अणु
#अगर_घोषित CONFIG_CPU_PM_WAIT
	यंत्र अस्थिर("wait\n");
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_PM_DOZE
	यंत्र अस्थिर("doze\n");
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_PM_STOP
	यंत्र अस्थिर("stop\n");
#पूर्ण_अगर
	raw_local_irq_enable();
पूर्ण
#पूर्ण_अगर
