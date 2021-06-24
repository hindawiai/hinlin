<शैली गुरु>
/*
 * Stack trace management functions
 *
 *  Copyright (C) 2006-2009 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 */
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/export.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/unwind.h>

व्योम arch_stack_walk(stack_trace_consume_fn consume_entry, व्योम *cookie,
		     काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	काष्ठा unwind_state state;
	अचिन्हित दीर्घ addr;

	अगर (regs && !consume_entry(cookie, regs->ip))
		वापस;

	क्रम (unwind_start(&state, task, regs, शून्य); !unwind_करोne(&state);
	     unwind_next_frame(&state)) अणु
		addr = unwind_get_वापस_address(&state);
		अगर (!addr || !consume_entry(cookie, addr))
			अवरोध;
	पूर्ण
पूर्ण

पूर्णांक arch_stack_walk_reliable(stack_trace_consume_fn consume_entry,
			     व्योम *cookie, काष्ठा task_काष्ठा *task)
अणु
	काष्ठा unwind_state state;
	काष्ठा pt_regs *regs;
	अचिन्हित दीर्घ addr;

	क्रम (unwind_start(&state, task, शून्य, शून्य);
	     !unwind_करोne(&state) && !unwind_error(&state);
	     unwind_next_frame(&state)) अणु

		regs = unwind_get_entry_regs(&state, शून्य);
		अगर (regs) अणु
			/* Success path क्रम user tasks */
			अगर (user_mode(regs))
				वापस 0;

			/*
			 * Kernel mode रेजिस्टरs on the stack indicate an
			 * in-kernel पूर्णांकerrupt or exception (e.g., preemption
			 * or a page fault), which can make frame poपूर्णांकers
			 * unreliable.
			 */
			अगर (IS_ENABLED(CONFIG_FRAME_POINTER))
				वापस -EINVAL;
		पूर्ण

		addr = unwind_get_वापस_address(&state);

		/*
		 * A शून्य or invalid वापस address probably means there's some
		 * generated code which __kernel_text_address() करोesn't know
		 * about.
		 */
		अगर (!addr)
			वापस -EINVAL;

		अगर (!consume_entry(cookie, addr))
			वापस -EINVAL;
	पूर्ण

	/* Check क्रम stack corruption */
	अगर (unwind_error(&state))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* Userspace stacktrace - based on kernel/trace/trace_sysprof.c */

काष्ठा stack_frame_user अणु
	स्थिर व्योम __user	*next_fp;
	अचिन्हित दीर्घ		ret_addr;
पूर्ण;

अटल पूर्णांक
copy_stack_frame(स्थिर काष्ठा stack_frame_user __user *fp,
		 काष्ठा stack_frame_user *frame)
अणु
	पूर्णांक ret;

	अगर (__range_not_ok(fp, माप(*frame), TASK_SIZE))
		वापस 0;

	ret = 1;
	pagefault_disable();
	अगर (__get_user(frame->next_fp, &fp->next_fp) ||
	    __get_user(frame->ret_addr, &fp->ret_addr))
		ret = 0;
	pagefault_enable();

	वापस ret;
पूर्ण

व्योम arch_stack_walk_user(stack_trace_consume_fn consume_entry, व्योम *cookie,
			  स्थिर काष्ठा pt_regs *regs)
अणु
	स्थिर व्योम __user *fp = (स्थिर व्योम __user *)regs->bp;

	अगर (!consume_entry(cookie, regs->ip))
		वापस;

	जबतक (1) अणु
		काष्ठा stack_frame_user frame;

		frame.next_fp = शून्य;
		frame.ret_addr = 0;
		अगर (!copy_stack_frame(fp, &frame))
			अवरोध;
		अगर ((अचिन्हित दीर्घ)fp < regs->sp)
			अवरोध;
		अगर (!frame.ret_addr)
			अवरोध;
		अगर (!consume_entry(cookie, frame.ret_addr))
			अवरोध;
		fp = frame.next_fp;
	पूर्ण
पूर्ण

