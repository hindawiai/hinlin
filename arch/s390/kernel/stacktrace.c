<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Stack trace management functions
 *
 *  Copyright IBM Corp. 2006
 *  Author(s): Heiko Carstens <heiko.carstens@de.ibm.com>
 */

#समावेश <linux/stacktrace.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/unwind.h>
#समावेश <यंत्र/kprobes.h>

व्योम arch_stack_walk(stack_trace_consume_fn consume_entry, व्योम *cookie,
		     काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	काष्ठा unwind_state state;
	अचिन्हित दीर्घ addr;

	unwind_क्रम_each_frame(&state, task, regs, 0) अणु
		addr = unwind_get_वापस_address(&state);
		अगर (!addr || !consume_entry(cookie, addr))
			अवरोध;
	पूर्ण
पूर्ण

पूर्णांक arch_stack_walk_reliable(stack_trace_consume_fn consume_entry,
			     व्योम *cookie, काष्ठा task_काष्ठा *task)
अणु
	काष्ठा unwind_state state;
	अचिन्हित दीर्घ addr;

	unwind_क्रम_each_frame(&state, task, शून्य, 0) अणु
		अगर (state.stack_info.type != STACK_TYPE_TASK)
			वापस -EINVAL;

		अगर (state.regs)
			वापस -EINVAL;

		addr = unwind_get_वापस_address(&state);
		अगर (!addr)
			वापस -EINVAL;

#अगर_घोषित CONFIG_KPROBES
		/*
		 * Mark stacktraces with kretprobed functions on them
		 * as unreliable.
		 */
		अगर (state.ip == (अचिन्हित दीर्घ)kretprobe_trampoline)
			वापस -EINVAL;
#पूर्ण_अगर

		अगर (!consume_entry(cookie, addr))
			वापस -EINVAL;
	पूर्ण

	/* Check क्रम stack corruption */
	अगर (unwind_error(&state))
		वापस -EINVAL;
	वापस 0;
पूर्ण
