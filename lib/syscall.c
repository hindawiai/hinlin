<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ptrace.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/syscall.h>

अटल पूर्णांक collect_syscall(काष्ठा task_काष्ठा *target, काष्ठा syscall_info *info)
अणु
	अचिन्हित दीर्घ args[6] = अणु पूर्ण;
	काष्ठा pt_regs *regs;

	अगर (!try_get_task_stack(target)) अणु
		/* Task has no stack, so the task isn't in a syscall. */
		स_रखो(info, 0, माप(*info));
		info->data.nr = -1;
		वापस 0;
	पूर्ण

	regs = task_pt_regs(target);
	अगर (unlikely(!regs)) अणु
		put_task_stack(target);
		वापस -EAGAIN;
	पूर्ण

	info->sp = user_stack_poपूर्णांकer(regs);
	info->data.inकाष्ठाion_poपूर्णांकer = inकाष्ठाion_poपूर्णांकer(regs);

	info->data.nr = syscall_get_nr(target, regs);
	अगर (info->data.nr != -1L)
		syscall_get_arguments(target, regs, args);

	info->data.args[0] = args[0];
	info->data.args[1] = args[1];
	info->data.args[2] = args[2];
	info->data.args[3] = args[3];
	info->data.args[4] = args[4];
	info->data.args[5] = args[5];

	put_task_stack(target);
	वापस 0;
पूर्ण

/**
 * task_current_syscall - Discover what a blocked task is करोing.
 * @target:		thपढ़ो to examine
 * @info:		काष्ठाure with the following fields:
 *			 .sp        - filled with user stack poपूर्णांकer
 *			 .data.nr   - filled with प्रणाली call number or -1
 *			 .data.args - filled with @maxargs प्रणाली call arguments
 *			 .data.inकाष्ठाion_poपूर्णांकer - filled with user PC
 *
 * If @target is blocked in a प्रणाली call, वापसs zero with @info.data.nr
 * set to the call's number and @info.data.args filled in with its
 * arguments. Registers not used क्रम प्रणाली call arguments may not be available
 * and it is not kosher to use &काष्ठा user_regset calls जबतक the प्रणाली
 * call is still in progress.  Note we may get this result अगर @target
 * has finished its प्रणाली call but not yet वापसed to user mode, such
 * as when it's stopped क्रम संकेत handling or syscall निकास tracing.
 *
 * If @target is blocked in the kernel during a fault or exception,
 * वापसs zero with *@info.data.nr set to -1 and करोes not fill in
 * @info.data.args. If so, it's now safe to examine @target using
 * &काष्ठा user_regset get() calls as दीर्घ as we're sure @target won't वापस
 * to user mode.
 *
 * Returns -%EAGAIN अगर @target करोes not reमुख्य blocked.
 */
पूर्णांक task_current_syscall(काष्ठा task_काष्ठा *target, काष्ठा syscall_info *info)
अणु
	दीर्घ state;
	अचिन्हित दीर्घ ncsw;

	अगर (target == current)
		वापस collect_syscall(target, info);

	state = target->state;
	अगर (unlikely(!state))
		वापस -EAGAIN;

	ncsw = रुको_task_inactive(target, state);
	अगर (unlikely(!ncsw) ||
	    unlikely(collect_syscall(target, info)) ||
	    unlikely(रुको_task_inactive(target, state) != ncsw))
		वापस -EAGAIN;

	वापस 0;
पूर्ण
