<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM संकेत

#अगर !defined(_TRACE_SIGNAL_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _TRACE_SIGNAL_H

#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/tracepoपूर्णांक.h>

#घोषणा TP_STORE_SIGINFO(__entry, info)				\
	करो अणु							\
		अगर (info == SEND_SIG_NOINFO) अणु			\
			__entry->त्रुटि_सं	= 0;			\
			__entry->code	= SI_USER;		\
		पूर्ण अन्यथा अगर (info == SEND_SIG_PRIV) अणु		\
			__entry->त्रुटि_सं	= 0;			\
			__entry->code	= SI_KERNEL;		\
		पूर्ण अन्यथा अणु					\
			__entry->त्रुटि_सं	= info->si_त्रुटि_सं;	\
			__entry->code	= info->si_code;	\
		पूर्ण						\
	पूर्ण जबतक (0)

#अगर_अघोषित TRACE_HEADER_MULTI_READ
क्रमागत अणु
	TRACE_SIGNAL_DELIVERED,
	TRACE_SIGNAL_IGNORED,
	TRACE_SIGNAL_ALREADY_PENDING,
	TRACE_SIGNAL_OVERFLOW_FAIL,
	TRACE_SIGNAL_LOSE_INFO,
पूर्ण;
#पूर्ण_अगर

/**
 * संकेत_generate - called when a संकेत is generated
 * @sig: संकेत number
 * @info: poपूर्णांकer to काष्ठा siginfo
 * @task: poपूर्णांकer to काष्ठा task_काष्ठा
 * @group: shared or निजी
 * @result: TRACE_SIGNAL_*
 *
 * Current process sends a 'sig' signal to 'task' process with
 * 'info' siginfo. If 'info' is SEND_SIG_NOINFO or SEND_SIG_PRIV,
 * 'info' is not a pointer and you can't access its field. Instead,
 * SEND_SIG_NOINFO means that si_code is SI_USER, and SEND_SIG_PRIV
 * means that si_code is SI_KERNEL.
 */
TRACE_EVENT(संकेत_generate,

	TP_PROTO(पूर्णांक sig, काष्ठा kernel_siginfo *info, काष्ठा task_काष्ठा *task,
			पूर्णांक group, पूर्णांक result),

	TP_ARGS(sig, info, task, group, result),

	TP_STRUCT__entry(
		__field(	पूर्णांक,	sig			)
		__field(	पूर्णांक,	त्रुटि_सं			)
		__field(	पूर्णांक,	code			)
		__array(	अक्षर,	comm,	TASK_COMM_LEN	)
		__field(	pid_t,	pid			)
		__field(	पूर्णांक,	group			)
		__field(	पूर्णांक,	result			)
	),

	TP_fast_assign(
		__entry->sig	= sig;
		TP_STORE_SIGINFO(__entry, info);
		स_नकल(__entry->comm, task->comm, TASK_COMM_LEN);
		__entry->pid	= task->pid;
		__entry->group	= group;
		__entry->result	= result;
	),

	TP_prपूर्णांकk("sig=%d errno=%d code=%d comm=%s pid=%d grp=%d res=%d",
		  __entry->sig, __entry->त्रुटि_सं, __entry->code,
		  __entry->comm, __entry->pid, __entry->group,
		  __entry->result)
);

/**
 * संकेत_deliver - called when a संकेत is delivered
 * @sig: संकेत number
 * @info: poपूर्णांकer to काष्ठा siginfo
 * @ka: poपूर्णांकer to काष्ठा k_sigaction
 *
 * A 'sig' signal is delivered to current process with 'info' siginfo,
 * and it will be handled by 'ka'. ka->sa.sa_handler can be संक_छोड़ो or
 * संक_पूर्व.
 * Note that some संकेतs reported by संकेत_generate tracepoपूर्णांक can be
 * lost, ignored or modअगरied (by debugger) beक्रमe hitting this tracepoपूर्णांक.
 * This means, this can show which संकेतs are actually delivered, but
 * matching generated संकेतs and delivered संकेतs may not be correct.
 */
TRACE_EVENT(संकेत_deliver,

	TP_PROTO(पूर्णांक sig, काष्ठा kernel_siginfo *info, काष्ठा k_sigaction *ka),

	TP_ARGS(sig, info, ka),

	TP_STRUCT__entry(
		__field(	पूर्णांक,		sig		)
		__field(	पूर्णांक,		त्रुटि_सं		)
		__field(	पूर्णांक,		code		)
		__field(	अचिन्हित दीर्घ,	sa_handler	)
		__field(	अचिन्हित दीर्घ,	sa_flags	)
	),

	TP_fast_assign(
		__entry->sig	= sig;
		TP_STORE_SIGINFO(__entry, info);
		__entry->sa_handler	= (अचिन्हित दीर्घ)ka->sa.sa_handler;
		__entry->sa_flags	= ka->sa.sa_flags;
	),

	TP_prपूर्णांकk("sig=%d errno=%d code=%d sa_handler=%lx sa_flags=%lx",
		  __entry->sig, __entry->त्रुटि_सं, __entry->code,
		  __entry->sa_handler, __entry->sa_flags)
);

#पूर्ण_अगर /* _TRACE_SIGNAL_H */

/* This part must be outside protection */
#समावेश <trace/define_trace.h>
