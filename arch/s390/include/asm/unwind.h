<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_S390_UNWIND_H
#घोषणा _ASM_S390_UNWIND_H

#समावेश <linux/sched.h>
#समावेश <linux/ftrace.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/stacktrace.h>

/*
 * To use the stack unwinder it has to be initialized with unwind_start.
 * There four combinations क्रम task and regs:
 * 1) task==शून्य, regs==शून्य: the unwind starts क्रम the task that is currently
 *    running, sp/ip picked up from the CPU रेजिस्टरs
 * 2) task==शून्य, regs!=शून्य: the unwind starts from the sp/ip found in
 *    the काष्ठा pt_regs of an पूर्णांकerrupt frame क्रम the current task
 * 3) task!=शून्य, regs==शून्य: the unwind starts क्रम an inactive task with
 *    the sp picked up from task->thपढ़ो.ksp and the ip picked up from the
 *    वापस address stored by __चयन_to
 * 4) task!=शून्य, regs!=शून्य: the sp/ip are picked up from the पूर्णांकerrupt
 *    frame 'regs' of a inactive task
 * If 'first_frame' is not zero unwind_start skips unwind frames until it
 * reaches the specअगरied stack poपूर्णांकer.
 * The end of the unwinding is indicated with unwind_करोne, this can be true
 * right after unwind_start, e.g. with first_frame!=0 that can not be found.
 * unwind_next_frame skips to the next frame.
 * Once the unwind is completed unwind_error() can be used to check अगर there
 * has been a situation where the unwinder could not correctly understand
 * the tasks call chain.
 */

काष्ठा unwind_state अणु
	काष्ठा stack_info stack_info;
	अचिन्हित दीर्घ stack_mask;
	काष्ठा task_काष्ठा *task;
	काष्ठा pt_regs *regs;
	अचिन्हित दीर्घ sp, ip;
	पूर्णांक graph_idx;
	bool reliable;
	bool error;
पूर्ण;

व्योम __unwind_start(काष्ठा unwind_state *state, काष्ठा task_काष्ठा *task,
		    काष्ठा pt_regs *regs, अचिन्हित दीर्घ first_frame);
bool unwind_next_frame(काष्ठा unwind_state *state);
अचिन्हित दीर्घ unwind_get_वापस_address(काष्ठा unwind_state *state);

अटल अंतरभूत bool unwind_करोne(काष्ठा unwind_state *state)
अणु
	वापस state->stack_info.type == STACK_TYPE_UNKNOWN;
पूर्ण

अटल अंतरभूत bool unwind_error(काष्ठा unwind_state *state)
अणु
	वापस state->error;
पूर्ण

अटल अंतरभूत व्योम unwind_start(काष्ठा unwind_state *state,
				काष्ठा task_काष्ठा *task,
				काष्ठा pt_regs *regs,
				अचिन्हित दीर्घ first_frame)
अणु
	task = task ?: current;
	first_frame = first_frame ?: get_stack_poपूर्णांकer(task, regs);
	__unwind_start(state, task, regs, first_frame);
पूर्ण

अटल अंतरभूत काष्ठा pt_regs *unwind_get_entry_regs(काष्ठा unwind_state *state)
अणु
	वापस unwind_करोne(state) ? शून्य : state->regs;
पूर्ण

#घोषणा unwind_क्रम_each_frame(state, task, regs, first_frame)	\
	क्रम (unwind_start(state, task, regs, first_frame);	\
	     !unwind_करोne(state);				\
	     unwind_next_frame(state))

अटल अंतरभूत व्योम unwind_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम unwind_module_init(काष्ठा module *mod, व्योम *orc_ip,
				      माप_प्रकार orc_ip_size, व्योम *orc,
				      माप_प्रकार orc_size) अणुपूर्ण

#पूर्ण_अगर /* _ASM_S390_UNWIND_H */
