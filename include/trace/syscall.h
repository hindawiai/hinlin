<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TRACE_SYSCALL_H
#घोषणा _TRACE_SYSCALL_H

#समावेश <linux/tracepoपूर्णांक.h>
#समावेश <linux/unistd.h>
#समावेश <linux/trace_events.h>
#समावेश <linux/thपढ़ो_info.h>

#समावेश <यंत्र/ptrace.h>


/*
 * A syscall entry in the ftrace syscalls array.
 *
 * @name: name of the syscall
 * @syscall_nr: number of the syscall
 * @nb_args: number of parameters it takes
 * @types: list of types as strings
 * @args: list of args as strings (args[i] matches types[i])
 * @enter_fields: list of fields क्रम syscall_enter trace event
 * @enter_event: associated syscall_enter trace event
 * @निकास_event: associated syscall_निकास trace event
 */
काष्ठा syscall_metadata अणु
	स्थिर अक्षर	*name;
	पूर्णांक		syscall_nr;
	पूर्णांक		nb_args;
	स्थिर अक्षर	**types;
	स्थिर अक्षर	**args;
	काष्ठा list_head enter_fields;

	काष्ठा trace_event_call *enter_event;
	काष्ठा trace_event_call *निकास_event;
पूर्ण;

#अगर defined(CONFIG_TRACEPOINTS) && defined(CONFIG_HAVE_SYSCALL_TRACEPOINTS)
अटल अंतरभूत व्योम syscall_tracepoपूर्णांक_update(काष्ठा task_काष्ठा *p)
अणु
	अगर (test_syscall_work(SYSCALL_TRACEPOINT))
		set_task_syscall_work(p, SYSCALL_TRACEPOINT);
	अन्यथा
		clear_task_syscall_work(p, SYSCALL_TRACEPOINT);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम syscall_tracepoपूर्णांक_update(काष्ठा task_काष्ठा *p)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _TRACE_SYSCALL_H */
