<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/sched.h>
#समावेश <linux/ftrace.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/bitops.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/unwind.h>

अचिन्हित दीर्घ unwind_get_वापस_address(काष्ठा unwind_state *state)
अणु
	अचिन्हित दीर्घ addr;

	अगर (unwind_करोne(state))
		वापस 0;

	addr = READ_ONCE_NOCHECK(*state->sp);

	वापस ftrace_graph_ret_addr(state->task, &state->graph_idx,
				     addr, state->sp);
पूर्ण
EXPORT_SYMBOL_GPL(unwind_get_वापस_address);

अचिन्हित दीर्घ *unwind_get_वापस_address_ptr(काष्ठा unwind_state *state)
अणु
	वापस शून्य;
पूर्ण

bool unwind_next_frame(काष्ठा unwind_state *state)
अणु
	काष्ठा stack_info *info = &state->stack_info;

	अगर (unwind_करोne(state))
		वापस false;

	करो अणु
		क्रम (state->sp++; state->sp < info->end; state->sp++) अणु
			अचिन्हित दीर्घ addr = READ_ONCE_NOCHECK(*state->sp);

			अगर (__kernel_text_address(addr))
				वापस true;
		पूर्ण

		state->sp = PTR_ALIGN(info->next_sp, माप(दीर्घ));

	पूर्ण जबतक (!get_stack_info(state->sp, state->task, info,
				 &state->stack_mask));

	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(unwind_next_frame);

व्योम __unwind_start(काष्ठा unwind_state *state, काष्ठा task_काष्ठा *task,
		    काष्ठा pt_regs *regs, अचिन्हित दीर्घ *first_frame)
अणु
	स_रखो(state, 0, माप(*state));

	state->task = task;
	state->sp   = PTR_ALIGN(first_frame, माप(दीर्घ));

	get_stack_info(first_frame, state->task, &state->stack_info,
		       &state->stack_mask);

	/*
	 * The caller can provide the address of the first frame directly
	 * (first_frame) or indirectly (regs->sp) to indicate which stack frame
	 * to start unwinding at.  Skip ahead until we reach it.
	 */
	अगर (!unwind_करोne(state) &&
	    (!on_stack(&state->stack_info, first_frame, माप(दीर्घ)) ||
	    !__kernel_text_address(*first_frame)))
		unwind_next_frame(state);
पूर्ण
EXPORT_SYMBOL_GPL(__unwind_start);
