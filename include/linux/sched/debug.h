<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_DEBUG_H
#घोषणा _LINUX_SCHED_DEBUG_H

/*
 * Various scheduler/task debugging पूर्णांकerfaces:
 */

काष्ठा task_काष्ठा;
काष्ठा pid_namespace;

बाह्य व्योम dump_cpu_task(पूर्णांक cpu);

/*
 * Only dump TASK_* tasks. (0 क्रम all tasks)
 */
बाह्य व्योम show_state_filter(अचिन्हित दीर्घ state_filter);

अटल अंतरभूत व्योम show_state(व्योम)
अणु
	show_state_filter(0);
पूर्ण

काष्ठा pt_regs;

बाह्य व्योम show_regs(काष्ठा pt_regs *);

/*
 * TASK is a poपूर्णांकer to the task whose backtrace we want to see (or शून्य क्रम current
 * task), SP is the stack poपूर्णांकer of the first frame that should be shown in the back
 * trace (or शून्य अगर the entire call-chain of the task should be shown).
 */
बाह्य व्योम show_stack(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ *sp,
		       स्थिर अक्षर *loglvl);

बाह्य व्योम sched_show_task(काष्ठा task_काष्ठा *p);

#अगर_घोषित CONFIG_SCHED_DEBUG
काष्ठा seq_file;
बाह्य व्योम proc_sched_show_task(काष्ठा task_काष्ठा *p,
				 काष्ठा pid_namespace *ns, काष्ठा seq_file *m);
बाह्य व्योम proc_sched_set_task(काष्ठा task_काष्ठा *p);
#पूर्ण_अगर

/* Attach to any functions which should be ignored in wchan output. */
#घोषणा __sched		__section(".sched.text")

/* Linker adds these: start and end of __sched functions */
बाह्य अक्षर __sched_text_start[], __sched_text_end[];

/* Is this address in the __sched functions? */
बाह्य पूर्णांक in_sched_functions(अचिन्हित दीर्घ addr);

#पूर्ण_अगर /* _LINUX_SCHED_DEBUG_H */
