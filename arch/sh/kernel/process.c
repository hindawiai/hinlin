<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/mm.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/export.h>
#समावेश <linux/stackprotector.h>
#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/ptrace.h>

काष्ठा kmem_cache *task_xstate_cachep = शून्य;
अचिन्हित पूर्णांक xstate_size;

#अगर_घोषित CONFIG_STACKPROTECTOR
अचिन्हित दीर्घ __stack_chk_guard __पढ़ो_mostly;
EXPORT_SYMBOL(__stack_chk_guard);
#पूर्ण_अगर

/*
 * this माला_लो called so that we can store lazy state पूर्णांकo memory and copy the
 * current task पूर्णांकo the new thपढ़ो.
 */
पूर्णांक arch_dup_task_काष्ठा(काष्ठा task_काष्ठा *dst, काष्ठा task_काष्ठा *src)
अणु
	unlazy_fpu(src, task_pt_regs(src));
	*dst = *src;

	अगर (src->thपढ़ो.xstate) अणु
		dst->thपढ़ो.xstate = kmem_cache_alloc(task_xstate_cachep,
						      GFP_KERNEL);
		अगर (!dst->thपढ़ो.xstate)
			वापस -ENOMEM;
		स_नकल(dst->thपढ़ो.xstate, src->thपढ़ो.xstate, xstate_size);
	पूर्ण

	वापस 0;
पूर्ण

व्योम मुक्त_thपढ़ो_xstate(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (tsk->thपढ़ो.xstate) अणु
		kmem_cache_मुक्त(task_xstate_cachep, tsk->thपढ़ो.xstate);
		tsk->thपढ़ो.xstate = शून्य;
	पूर्ण
पूर्ण

व्योम arch_release_task_काष्ठा(काष्ठा task_काष्ठा *tsk)
अणु
	मुक्त_thपढ़ो_xstate(tsk);
पूर्ण

व्योम arch_task_cache_init(व्योम)
अणु
	अगर (!xstate_size)
		वापस;

	task_xstate_cachep = kmem_cache_create("task_xstate", xstate_size,
					       __alignof__(जोड़ thपढ़ो_xstate),
					       SLAB_PANIC, शून्य);
पूर्ण

#अगर_घोषित CONFIG_SH_FPU_EMU
# define HAVE_SOFTFP	1
#अन्यथा
# define HAVE_SOFTFP	0
#पूर्ण_अगर

व्योम init_thपढ़ो_xstate(व्योम)
अणु
	अगर (boot_cpu_data.flags & CPU_HAS_FPU)
		xstate_size = माप(काष्ठा sh_fpu_hard_काष्ठा);
	अन्यथा अगर (HAVE_SOFTFP)
		xstate_size = माप(काष्ठा sh_fpu_soft_काष्ठा);
	अन्यथा
		xstate_size = 0;
पूर्ण
