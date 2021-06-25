<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/ptrace.h>

पूर्णांक init_fpu(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (tsk_used_math(tsk)) अणु
		अगर ((boot_cpu_data.flags & CPU_HAS_FPU) && tsk == current)
			unlazy_fpu(tsk, task_pt_regs(tsk));
		वापस 0;
	पूर्ण

	/*
	 * Memory allocation at the first usage of the FPU and other state.
	 */
	अगर (!tsk->thपढ़ो.xstate) अणु
		tsk->thपढ़ो.xstate = kmem_cache_alloc(task_xstate_cachep,
						      GFP_KERNEL);
		अगर (!tsk->thपढ़ो.xstate)
			वापस -ENOMEM;
	पूर्ण

	अगर (boot_cpu_data.flags & CPU_HAS_FPU) अणु
		काष्ठा sh_fpu_hard_काष्ठा *fp = &tsk->thपढ़ो.xstate->hardfpu;
		स_रखो(fp, 0, xstate_size);
		fp->fpscr = FPSCR_INIT;
	पूर्ण अन्यथा अणु
		काष्ठा sh_fpu_soft_काष्ठा *fp = &tsk->thपढ़ो.xstate->softfpu;
		स_रखो(fp, 0, xstate_size);
		fp->fpscr = FPSCR_INIT;
	पूर्ण

	set_stopped_child_used_math(tsk);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_SH_FPU
व्योम __fpu_state_restore(व्योम)
अणु
	काष्ठा task_काष्ठा *tsk = current;

	restore_fpu(tsk);

	task_thपढ़ो_info(tsk)->status |= TS_USEDFPU;
	tsk->thपढ़ो.fpu_counter++;
पूर्ण

व्योम fpu_state_restore(काष्ठा pt_regs *regs)
अणु
	काष्ठा task_काष्ठा *tsk = current;

	अगर (unlikely(!user_mode(regs))) अणु
		prपूर्णांकk(KERN_ERR "BUG: FPU is used in kernel mode.\n");
		BUG();
		वापस;
	पूर्ण

	अगर (!tsk_used_math(tsk)) अणु
		local_irq_enable();
		/*
		 * करोes a slab alloc which can sleep
		 */
		अगर (init_fpu(tsk)) अणु
			/*
			 * ran out of memory!
			 */
			करो_group_निकास(SIGKILL);
			वापस;
		पूर्ण
		local_irq_disable();
	पूर्ण

	grab_fpu(regs);

	__fpu_state_restore();
पूर्ण

BUILD_TRAP_HANDLER(fpu_state_restore)
अणु
	TRAP_HANDLER_DECL;

	fpu_state_restore(regs);
पूर्ण
#पूर्ण_अगर /* CONFIG_SH_FPU */
