<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_STACKTRACE_H
#घोषणा __LINUX_STACKTRACE_H

#समावेश <linux/types.h>
#समावेश <यंत्र/त्रुटिसं.स>

काष्ठा task_काष्ठा;
काष्ठा pt_regs;

#अगर_घोषित CONFIG_STACKTRACE
व्योम stack_trace_prपूर्णांक(स्थिर अचिन्हित दीर्घ *trace, अचिन्हित पूर्णांक nr_entries,
		       पूर्णांक spaces);
पूर्णांक stack_trace_snprपूर्णांक(अक्षर *buf, माप_प्रकार size, स्थिर अचिन्हित दीर्घ *entries,
			अचिन्हित पूर्णांक nr_entries, पूर्णांक spaces);
अचिन्हित पूर्णांक stack_trace_save(अचिन्हित दीर्घ *store, अचिन्हित पूर्णांक size,
			      अचिन्हित पूर्णांक skipnr);
अचिन्हित पूर्णांक stack_trace_save_tsk(काष्ठा task_काष्ठा *task,
				  अचिन्हित दीर्घ *store, अचिन्हित पूर्णांक size,
				  अचिन्हित पूर्णांक skipnr);
अचिन्हित पूर्णांक stack_trace_save_regs(काष्ठा pt_regs *regs, अचिन्हित दीर्घ *store,
				   अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक skipnr);
अचिन्हित पूर्णांक stack_trace_save_user(अचिन्हित दीर्घ *store, अचिन्हित पूर्णांक size);

/* Internal पूर्णांकerfaces. Do not use in generic code */
#अगर_घोषित CONFIG_ARCH_STACKWALK

/**
 * stack_trace_consume_fn - Callback क्रम arch_stack_walk()
 * @cookie:	Caller supplied poपूर्णांकer handed back by arch_stack_walk()
 * @addr:	The stack entry address to consume
 *
 * Return:	True, अगर the entry was consumed or skipped
 *		False, अगर there is no space left to store
 */
प्रकार bool (*stack_trace_consume_fn)(व्योम *cookie, अचिन्हित दीर्घ addr);
/**
 * arch_stack_walk - Architecture specअगरic function to walk the stack
 * @consume_entry:	Callback which is invoked by the architecture code क्रम
 *			each entry.
 * @cookie:		Caller supplied poपूर्णांकer which is handed back to
 *			@consume_entry
 * @task:		Poपूर्णांकer to a task काष्ठा, can be शून्य
 * @regs:		Poपूर्णांकer to रेजिस्टरs, can be शून्य
 *
 * ============ ======= ============================================
 * task	        regs
 * ============ ======= ============================================
 * task		शून्य	Stack trace from task (can be current)
 * current	regs	Stack trace starting on regs->stackpoपूर्णांकer
 * ============ ======= ============================================
 */
व्योम arch_stack_walk(stack_trace_consume_fn consume_entry, व्योम *cookie,
		     काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs);

/**
 * arch_stack_walk_reliable - Architecture specअगरic function to walk the
 *			      stack reliably
 *
 * @consume_entry:	Callback which is invoked by the architecture code क्रम
 *			each entry.
 * @cookie:		Caller supplied poपूर्णांकer which is handed back to
 *			@consume_entry
 * @task:		Poपूर्णांकer to a task काष्ठा, can be शून्य
 *
 * This function वापसs an error अगर it detects any unreliable
 * features of the stack. Otherwise it guarantees that the stack
 * trace is reliable.
 *
 * If the task is not 'current', the caller *must* ensure the task is
 * inactive and its stack is pinned.
 */
पूर्णांक arch_stack_walk_reliable(stack_trace_consume_fn consume_entry, व्योम *cookie,
			     काष्ठा task_काष्ठा *task);

व्योम arch_stack_walk_user(stack_trace_consume_fn consume_entry, व्योम *cookie,
			  स्थिर काष्ठा pt_regs *regs);

#अन्यथा /* CONFIG_ARCH_STACKWALK */
काष्ठा stack_trace अणु
	अचिन्हित पूर्णांक nr_entries, max_entries;
	अचिन्हित दीर्घ *entries;
	अचिन्हित पूर्णांक skip;	/* input argument: How many entries to skip */
पूर्ण;

बाह्य व्योम save_stack_trace(काष्ठा stack_trace *trace);
बाह्य व्योम save_stack_trace_regs(काष्ठा pt_regs *regs,
				  काष्ठा stack_trace *trace);
बाह्य व्योम save_stack_trace_tsk(काष्ठा task_काष्ठा *tsk,
				काष्ठा stack_trace *trace);
बाह्य पूर्णांक save_stack_trace_tsk_reliable(काष्ठा task_काष्ठा *tsk,
					 काष्ठा stack_trace *trace);
बाह्य व्योम save_stack_trace_user(काष्ठा stack_trace *trace);
#पूर्ण_अगर /* !CONFIG_ARCH_STACKWALK */
#पूर्ण_अगर /* CONFIG_STACKTRACE */

#अगर defined(CONFIG_STACKTRACE) && defined(CONFIG_HAVE_RELIABLE_STACKTRACE)
पूर्णांक stack_trace_save_tsk_reliable(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ *store,
				  अचिन्हित पूर्णांक size);
#अन्यथा
अटल अंतरभूत पूर्णांक stack_trace_save_tsk_reliable(काष्ठा task_काष्ठा *tsk,
						अचिन्हित दीर्घ *store,
						अचिन्हित पूर्णांक size)
अणु
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __LINUX_STACKTRACE_H */
