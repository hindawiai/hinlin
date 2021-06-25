<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_UNWIND_H
#घोषणा _ASM_X86_UNWIND_H

#समावेश <linux/sched.h>
#समावेश <linux/ftrace.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/stacktrace.h>

#घोषणा IRET_FRAME_OFFSET (दुरत्व(काष्ठा pt_regs, ip))
#घोषणा IRET_FRAME_SIZE   (माप(काष्ठा pt_regs) - IRET_FRAME_OFFSET)

काष्ठा unwind_state अणु
	काष्ठा stack_info stack_info;
	अचिन्हित दीर्घ stack_mask;
	काष्ठा task_काष्ठा *task;
	पूर्णांक graph_idx;
	bool error;
#अगर defined(CONFIG_UNWINDER_ORC)
	bool संकेत, full_regs;
	अचिन्हित दीर्घ sp, bp, ip;
	काष्ठा pt_regs *regs, *prev_regs;
#या_अगर defined(CONFIG_UNWINDER_FRAME_POINTER)
	bool got_irq;
	अचिन्हित दीर्घ *bp, *orig_sp, ip;
	/*
	 * If non-शून्य: The current frame is incomplete and करोesn't contain a
	 * valid BP. When looking क्रम the next frame, use this instead of the
	 * non-existent saved BP.
	 */
	अचिन्हित दीर्घ *next_bp;
	काष्ठा pt_regs *regs;
#अन्यथा
	अचिन्हित दीर्घ *sp;
#पूर्ण_अगर
पूर्ण;

व्योम __unwind_start(काष्ठा unwind_state *state, काष्ठा task_काष्ठा *task,
		    काष्ठा pt_regs *regs, अचिन्हित दीर्घ *first_frame);
bool unwind_next_frame(काष्ठा unwind_state *state);
अचिन्हित दीर्घ unwind_get_वापस_address(काष्ठा unwind_state *state);
अचिन्हित दीर्घ *unwind_get_वापस_address_ptr(काष्ठा unwind_state *state);

अटल अंतरभूत bool unwind_करोne(काष्ठा unwind_state *state)
अणु
	वापस state->stack_info.type == STACK_TYPE_UNKNOWN;
पूर्ण

अटल अंतरभूत bool unwind_error(काष्ठा unwind_state *state)
अणु
	वापस state->error;
पूर्ण

अटल अंतरभूत
व्योम unwind_start(काष्ठा unwind_state *state, काष्ठा task_काष्ठा *task,
		  काष्ठा pt_regs *regs, अचिन्हित दीर्घ *first_frame)
अणु
	first_frame = first_frame ? : get_stack_poपूर्णांकer(task, regs);

	__unwind_start(state, task, regs, first_frame);
पूर्ण

#अगर defined(CONFIG_UNWINDER_ORC) || defined(CONFIG_UNWINDER_FRAME_POINTER)
/*
 * If 'partial' वापसs true, only the iret frame रेजिस्टरs are valid.
 */
अटल अंतरभूत काष्ठा pt_regs *unwind_get_entry_regs(काष्ठा unwind_state *state,
						    bool *partial)
अणु
	अगर (unwind_करोne(state))
		वापस शून्य;

	अगर (partial) अणु
#अगर_घोषित CONFIG_UNWINDER_ORC
		*partial = !state->full_regs;
#अन्यथा
		*partial = false;
#पूर्ण_अगर
	पूर्ण

	वापस state->regs;
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा pt_regs *unwind_get_entry_regs(काष्ठा unwind_state *state,
						    bool *partial)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_UNWINDER_ORC
व्योम unwind_init(व्योम);
व्योम unwind_module_init(काष्ठा module *mod, व्योम *orc_ip, माप_प्रकार orc_ip_size,
			व्योम *orc, माप_प्रकार orc_size);
#अन्यथा
अटल अंतरभूत व्योम unwind_init(व्योम) अणुपूर्ण
अटल अंतरभूत
व्योम unwind_module_init(काष्ठा module *mod, व्योम *orc_ip, माप_प्रकार orc_ip_size,
			व्योम *orc, माप_प्रकार orc_size) अणुपूर्ण
#पूर्ण_अगर

/*
 * This disables KASAN checking when पढ़ोing a value from another task's stack,
 * since the other task could be running on another CPU and could have poisoned
 * the stack in the meanसमय.
 */
#घोषणा READ_ONCE_TASK_STACK(task, x)			\
(अणु							\
	अचिन्हित दीर्घ val;				\
	अगर (task == current)				\
		val = READ_ONCE(x);			\
	अन्यथा						\
		val = READ_ONCE_NOCHECK(x);		\
	val;						\
पूर्ण)

अटल अंतरभूत bool task_on_another_cpu(काष्ठा task_काष्ठा *task)
अणु
#अगर_घोषित CONFIG_SMP
	वापस task != current && task->on_cpu;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* _ASM_X86_UNWIND_H */
