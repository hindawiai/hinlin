<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/sched.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/bitops.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/unwind.h>

अचिन्हित दीर्घ unwind_get_वापस_address(काष्ठा unwind_state *state)
अणु
	अगर (unwind_करोne(state))
		वापस 0;
	वापस __kernel_text_address(state->ip) ? state->ip : 0;
पूर्ण
EXPORT_SYMBOL_GPL(unwind_get_वापस_address);

अटल bool outside_of_stack(काष्ठा unwind_state *state, अचिन्हित दीर्घ sp)
अणु
	वापस (sp <= state->sp) ||
		(sp > state->stack_info.end - माप(काष्ठा stack_frame));
पूर्ण

अटल bool update_stack_info(काष्ठा unwind_state *state, अचिन्हित दीर्घ sp)
अणु
	काष्ठा stack_info *info = &state->stack_info;
	अचिन्हित दीर्घ *mask = &state->stack_mask;

	/* New stack poपूर्णांकer leaves the current stack */
	अगर (get_stack_info(sp, state->task, info, mask) != 0 ||
	    !on_stack(info, sp, माप(काष्ठा stack_frame)))
		/* 'sp' करोes not poपूर्णांक to a valid stack */
		वापस false;
	वापस true;
पूर्ण

अटल अंतरभूत bool is_final_pt_regs(काष्ठा unwind_state *state,
				    काष्ठा pt_regs *regs)
अणु
	/* user mode or kernel thपढ़ो pt_regs at the bottom of task stack */
	अगर (task_pt_regs(state->task) == regs)
		वापस true;

	/* user mode pt_regs at the bottom of irq stack */
	वापस state->stack_info.type == STACK_TYPE_IRQ &&
	       state->stack_info.end - माप(काष्ठा pt_regs) == (अचिन्हित दीर्घ)regs &&
	       READ_ONCE_NOCHECK(regs->psw.mask) & PSW_MASK_PSTATE;
पूर्ण

bool unwind_next_frame(काष्ठा unwind_state *state)
अणु
	काष्ठा stack_info *info = &state->stack_info;
	काष्ठा stack_frame *sf;
	काष्ठा pt_regs *regs;
	अचिन्हित दीर्घ sp, ip;
	bool reliable;

	regs = state->regs;
	अगर (unlikely(regs)) अणु
		sp = state->sp;
		sf = (काष्ठा stack_frame *) sp;
		ip = READ_ONCE_NOCHECK(sf->gprs[8]);
		reliable = false;
		regs = शून्य;
		अगर (!__kernel_text_address(ip)) अणु
			/* skip bogus %r14 */
			state->regs = शून्य;
			वापस unwind_next_frame(state);
		पूर्ण
	पूर्ण अन्यथा अणु
		sf = (काष्ठा stack_frame *) state->sp;
		sp = READ_ONCE_NOCHECK(sf->back_chain);
		अगर (likely(sp)) अणु
			/* Non-zero back-chain poपूर्णांकs to the previous frame */
			अगर (unlikely(outside_of_stack(state, sp))) अणु
				अगर (!update_stack_info(state, sp))
					जाओ out_err;
			पूर्ण
			sf = (काष्ठा stack_frame *) sp;
			ip = READ_ONCE_NOCHECK(sf->gprs[8]);
			reliable = true;
		पूर्ण अन्यथा अणु
			/* No back-chain, look क्रम a pt_regs काष्ठाure */
			sp = state->sp + STACK_FRAME_OVERHEAD;
			अगर (!on_stack(info, sp, माप(काष्ठा pt_regs)))
				जाओ out_err;
			regs = (काष्ठा pt_regs *) sp;
			अगर (is_final_pt_regs(state, regs))
				जाओ out_stop;
			ip = READ_ONCE_NOCHECK(regs->psw.addr);
			sp = READ_ONCE_NOCHECK(regs->gprs[15]);
			अगर (unlikely(outside_of_stack(state, sp))) अणु
				अगर (!update_stack_info(state, sp))
					जाओ out_err;
			पूर्ण
			reliable = true;
		पूर्ण
	पूर्ण

	/* Sanity check: ABI requires SP to be aligned 8 bytes. */
	अगर (sp & 0x7)
		जाओ out_err;

	ip = ftrace_graph_ret_addr(state->task, &state->graph_idx, ip, (व्योम *) sp);

	/* Update unwind state */
	state->sp = sp;
	state->ip = ip;
	state->regs = regs;
	state->reliable = reliable;
	वापस true;

out_err:
	state->error = true;
out_stop:
	state->stack_info.type = STACK_TYPE_UNKNOWN;
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(unwind_next_frame);

व्योम __unwind_start(काष्ठा unwind_state *state, काष्ठा task_काष्ठा *task,
		    काष्ठा pt_regs *regs, अचिन्हित दीर्घ first_frame)
अणु
	काष्ठा stack_info *info = &state->stack_info;
	काष्ठा stack_frame *sf;
	अचिन्हित दीर्घ ip, sp;

	स_रखो(state, 0, माप(*state));
	state->task = task;
	state->regs = regs;

	/* Don't even attempt to start from user mode regs: */
	अगर (regs && user_mode(regs)) अणु
		info->type = STACK_TYPE_UNKNOWN;
		वापस;
	पूर्ण

	/* Get the inकाष्ठाion poपूर्णांकer from pt_regs or the stack frame */
	अगर (regs) अणु
		ip = regs->psw.addr;
		sp = regs->gprs[15];
	पूर्ण अन्यथा अगर (task == current) अणु
		sp = current_frame_address();
	पूर्ण अन्यथा अणु
		sp = task->thपढ़ो.ksp;
	पूर्ण

	/* Get current stack poपूर्णांकer and initialize stack info */
	अगर (!update_stack_info(state, sp)) अणु
		/* Something is wrong with the stack poपूर्णांकer */
		info->type = STACK_TYPE_UNKNOWN;
		state->error = true;
		वापस;
	पूर्ण

	अगर (!regs) अणु
		/* Stack frame is within valid stack */
		sf = (काष्ठा stack_frame *)sp;
		ip = READ_ONCE_NOCHECK(sf->gprs[8]);
	पूर्ण

	ip = ftrace_graph_ret_addr(state->task, &state->graph_idx, ip, शून्य);

	/* Update unwind state */
	state->sp = sp;
	state->ip = ip;
	state->reliable = true;

	अगर (!first_frame)
		वापस;
	/* Skip through the call chain to the specअगरied starting frame */
	जबतक (!unwind_करोne(state)) अणु
		अगर (on_stack(&state->stack_info, first_frame, माप(काष्ठा stack_frame))) अणु
			अगर (state->sp >= first_frame)
				अवरोध;
		पूर्ण
		unwind_next_frame(state);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(__unwind_start);
