<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
#अगर_अघोषित _LINUX_TRACEPOINT_H
#घोषणा _LINUX_TRACEPOINT_H

/*
 * Kernel Tracepoपूर्णांक API.
 *
 * See Documentation/trace/tracepoपूर्णांकs.rst.
 *
 * Copyright (C) 2008-2014 Mathieu Desnoyers <mathieu.desnoyers@efficios.com>
 *
 * Heavily inspired from the Linux Kernel Markers.
 */

#समावेश <linux/smp.h>
#समावेश <linux/srcu.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/tracepoपूर्णांक-defs.h>
#समावेश <linux/अटल_call.h>

काष्ठा module;
काष्ठा tracepoपूर्णांक;
काष्ठा notअगरier_block;

काष्ठा trace_eval_map अणु
	स्थिर अक्षर		*प्रणाली;
	स्थिर अक्षर		*eval_string;
	अचिन्हित दीर्घ		eval_value;
पूर्ण;

#घोषणा TRACEPOINT_DEFAULT_PRIO	10

बाह्य काष्ठा srcu_काष्ठा tracepoपूर्णांक_srcu;

बाह्य पूर्णांक
tracepoपूर्णांक_probe_रेजिस्टर(काष्ठा tracepoपूर्णांक *tp, व्योम *probe, व्योम *data);
बाह्य पूर्णांक
tracepoपूर्णांक_probe_रेजिस्टर_prio(काष्ठा tracepoपूर्णांक *tp, व्योम *probe, व्योम *data,
			       पूर्णांक prio);
बाह्य पूर्णांक
tracepoपूर्णांक_probe_unरेजिस्टर(काष्ठा tracepoपूर्णांक *tp, व्योम *probe, व्योम *data);
बाह्य व्योम
क्रम_each_kernel_tracepoपूर्णांक(व्योम (*fct)(काष्ठा tracepoपूर्णांक *tp, व्योम *priv),
		व्योम *priv);

#अगर_घोषित CONFIG_MODULES
काष्ठा tp_module अणु
	काष्ठा list_head list;
	काष्ठा module *mod;
पूर्ण;

bool trace_module_has_bad_taपूर्णांक(काष्ठा module *mod);
बाह्य पूर्णांक रेजिस्टर_tracepoपूर्णांक_module_notअगरier(काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक unरेजिस्टर_tracepoपूर्णांक_module_notअगरier(काष्ठा notअगरier_block *nb);
#अन्यथा
अटल अंतरभूत bool trace_module_has_bad_taपूर्णांक(काष्ठा module *mod)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत
पूर्णांक रेजिस्टर_tracepoपूर्णांक_module_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत
पूर्णांक unरेजिस्टर_tracepoपूर्णांक_module_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_MODULES */

/*
 * tracepoपूर्णांक_synchronize_unरेजिस्टर must be called between the last tracepoपूर्णांक
 * probe unregistration and the end of module निकास to make sure there is no
 * caller executing a probe when it is मुक्तd.
 */
#अगर_घोषित CONFIG_TRACEPOINTS
अटल अंतरभूत व्योम tracepoपूर्णांक_synchronize_unरेजिस्टर(व्योम)
अणु
	synchronize_srcu(&tracepoपूर्णांक_srcu);
	synchronize_rcu();
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम tracepoपूर्णांक_synchronize_unरेजिस्टर(व्योम)
अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_SYSCALL_TRACEPOINTS
बाह्य पूर्णांक syscall_regfunc(व्योम);
बाह्य व्योम syscall_unregfunc(व्योम);
#पूर्ण_अगर /* CONFIG_HAVE_SYSCALL_TRACEPOINTS */

#अगर_अघोषित PARAMS
#घोषणा PARAMS(args...) args
#पूर्ण_अगर

#घोषणा TRACE_DEFINE_ENUM(x)
#घोषणा TRACE_DEFINE_SIZखातापूर्ण(x)

#अगर_घोषित CONFIG_HAVE_ARCH_PREL32_RELOCATIONS
अटल अंतरभूत काष्ठा tracepoपूर्णांक *tracepoपूर्णांक_ptr_deref(tracepoपूर्णांक_ptr_t *p)
अणु
	वापस offset_to_ptr(p);
पूर्ण

#घोषणा __TRACEPOINT_ENTRY(name)					\
	यंत्र("	.section \"__tracepoints_ptrs\", \"a\"		\n"	\
	    "	.balign 4					\n"	\
	    "	.long 	__tracepoint_" #name " - .		\n"	\
	    "	.previous					\n")
#अन्यथा
अटल अंतरभूत काष्ठा tracepoपूर्णांक *tracepoपूर्णांक_ptr_deref(tracepoपूर्णांक_ptr_t *p)
अणु
	वापस *p;
पूर्ण

#घोषणा __TRACEPOINT_ENTRY(name)					 \
	अटल tracepoपूर्णांक_ptr_t __tracepoपूर्णांक_ptr_##name __used		 \
	__section("__tracepoints_ptrs") = &__tracepoपूर्णांक_##name
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_TRACEPOINT_H */

/*
 * Note: we keep the TRACE_EVENT and DECLARE_TRACE outside the include
 *  file अगरdef protection.
 *  This is due to the way trace events work. If a file includes two
 *  trace event headers under one "CREATE_TRACE_POINTS" the first include
 *  will override the TRACE_EVENT and अवरोध the second include.
 */

#अगर_अघोषित DECLARE_TRACE

#घोषणा TP_PROTO(args...)	args
#घोषणा TP_ARGS(args...)	args
#घोषणा TP_CONDITION(args...)	args

/*
 * Inभागidual subप्रणाली my have a separate configuration to
 * enable their tracepoपूर्णांकs. By शेष, this file will create
 * the tracepoपूर्णांकs अगर CONFIG_TRACEPOINT is defined. If a subप्रणाली
 * wants to be able to disable its tracepoपूर्णांकs from being created
 * it can define NOTRACE beक्रमe including the tracepoपूर्णांक headers.
 */
#अगर defined(CONFIG_TRACEPOINTS) && !defined(NOTRACE)
#घोषणा TRACEPOINTS_ENABLED
#पूर्ण_अगर

#अगर_घोषित TRACEPOINTS_ENABLED

#अगर_घोषित CONFIG_HAVE_STATIC_CALL
#घोषणा __DO_TRACE_CALL(name, args)					\
	करो अणु								\
		काष्ठा tracepoपूर्णांक_func *it_func_ptr;			\
		व्योम *__data;						\
		it_func_ptr =						\
			rcu_dereference_raw((&__tracepoपूर्णांक_##name)->funcs); \
		अगर (it_func_ptr) अणु					\
			__data = (it_func_ptr)->data;			\
			अटल_call(tp_func_##name)(__data, args);	\
		पूर्ण							\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा __DO_TRACE_CALL(name, args)	__traceiter_##name(शून्य, args)
#पूर्ण_अगर /* CONFIG_HAVE_STATIC_CALL */

/*
 * it_func[0] is never शून्य because there is at least one element in the array
 * when the array itself is non शून्य.
 */
#घोषणा __DO_TRACE(name, args, cond, rcuidle)				\
	करो अणु								\
		पूर्णांक __maybe_unused __idx = 0;				\
									\
		अगर (!(cond))						\
			वापस;						\
									\
		/* srcu can't be used from NMI */			\
		WARN_ON_ONCE(rcuidle && in_nmi());			\
									\
		/* keep srcu and sched-rcu usage consistent */		\
		preempt_disable_notrace();				\
									\
		/*							\
		 * For rcuidle callers, use srcu since sched-rcu	\
		 * करोesn't work from the idle path.			\
		 */							\
		अगर (rcuidle) अणु						\
			__idx = srcu_पढ़ो_lock_notrace(&tracepoपूर्णांक_srcu);\
			rcu_irq_enter_irqson();				\
		पूर्ण							\
									\
		__DO_TRACE_CALL(name, TP_ARGS(args));			\
									\
		अगर (rcuidle) अणु						\
			rcu_irq_निकास_irqson();				\
			srcu_पढ़ो_unlock_notrace(&tracepoपूर्णांक_srcu, __idx);\
		पूर्ण							\
									\
		preempt_enable_notrace();				\
	पूर्ण जबतक (0)

#अगर_अघोषित MODULE
#घोषणा __DECLARE_TRACE_RCU(name, proto, args, cond)			\
	अटल अंतरभूत व्योम trace_##name##_rcuidle(proto)		\
	अणु								\
		अगर (अटल_key_false(&__tracepoपूर्णांक_##name.key))		\
			__DO_TRACE(name,				\
				TP_ARGS(args),				\
				TP_CONDITION(cond), 1);			\
	पूर्ण
#अन्यथा
#घोषणा __DECLARE_TRACE_RCU(name, proto, args, cond)
#पूर्ण_अगर

/*
 * Make sure the alignment of the काष्ठाure in the __tracepoपूर्णांकs section will
 * not add unwanted padding between the beginning of the section and the
 * काष्ठाure. Force alignment to the same alignment as the section start.
 *
 * When lockdep is enabled, we make sure to always करो the RCU portions of
 * the tracepoपूर्णांक code, regardless of whether tracing is on. However,
 * करोn't check अगर the condition is false, due to पूर्णांकeraction with idle
 * instrumentation. This lets us find RCU issues triggered with tracepoपूर्णांकs
 * even when this tracepoपूर्णांक is off. This code has no purpose other than
 * poking RCU a bit.
 */
#घोषणा __DECLARE_TRACE(name, proto, args, cond, data_proto)		\
	बाह्य पूर्णांक __traceiter_##name(data_proto);			\
	DECLARE_STATIC_CALL(tp_func_##name, __traceiter_##name);	\
	बाह्य काष्ठा tracepoपूर्णांक __tracepoपूर्णांक_##name;			\
	अटल अंतरभूत व्योम trace_##name(proto)				\
	अणु								\
		अगर (अटल_key_false(&__tracepoपूर्णांक_##name.key))		\
			__DO_TRACE(name,				\
				TP_ARGS(args),				\
				TP_CONDITION(cond), 0);			\
		अगर (IS_ENABLED(CONFIG_LOCKDEP) && (cond)) अणु		\
			rcu_पढ़ो_lock_sched_notrace();			\
			rcu_dereference_sched(__tracepoपूर्णांक_##name.funcs);\
			rcu_पढ़ो_unlock_sched_notrace();		\
		पूर्ण							\
	पूर्ण								\
	__DECLARE_TRACE_RCU(name, PARAMS(proto), PARAMS(args),		\
			    PARAMS(cond))				\
	अटल अंतरभूत पूर्णांक						\
	रेजिस्टर_trace_##name(व्योम (*probe)(data_proto), व्योम *data)	\
	अणु								\
		वापस tracepoपूर्णांक_probe_रेजिस्टर(&__tracepoपूर्णांक_##name,	\
						(व्योम *)probe, data);	\
	पूर्ण								\
	अटल अंतरभूत पूर्णांक						\
	रेजिस्टर_trace_prio_##name(व्योम (*probe)(data_proto), व्योम *data,\
				   पूर्णांक prio)				\
	अणु								\
		वापस tracepoपूर्णांक_probe_रेजिस्टर_prio(&__tracepoपूर्णांक_##name, \
					      (व्योम *)probe, data, prio); \
	पूर्ण								\
	अटल अंतरभूत पूर्णांक						\
	unरेजिस्टर_trace_##name(व्योम (*probe)(data_proto), व्योम *data)	\
	अणु								\
		वापस tracepoपूर्णांक_probe_unरेजिस्टर(&__tracepoपूर्णांक_##name,\
						(व्योम *)probe, data);	\
	पूर्ण								\
	अटल अंतरभूत व्योम						\
	check_trace_callback_type_##name(व्योम (*cb)(data_proto))	\
	अणु								\
	पूर्ण								\
	अटल अंतरभूत bool						\
	trace_##name##_enabled(व्योम)					\
	अणु								\
		वापस अटल_key_false(&__tracepoपूर्णांक_##name.key);	\
	पूर्ण

/*
 * We have no guarantee that gcc and the linker won't up-align the tracepoपूर्णांक
 * काष्ठाures, so we create an array of poपूर्णांकers that will be used क्रम iteration
 * on the tracepoपूर्णांकs.
 */
#घोषणा DEFINE_TRACE_FN(_name, _reg, _unreg, proto, args)		\
	अटल स्थिर अक्षर __tpstrtab_##_name[]				\
	__section("__tracepoints_strings") = #_name;			\
	बाह्य काष्ठा अटल_call_key STATIC_CALL_KEY(tp_func_##_name);	\
	पूर्णांक __traceiter_##_name(व्योम *__data, proto);			\
	काष्ठा tracepoपूर्णांक __tracepoपूर्णांक_##_name	__used			\
	__section("__tracepoints") = अणु					\
		.name = __tpstrtab_##_name,				\
		.key = STATIC_KEY_INIT_FALSE,				\
		.अटल_call_key = &STATIC_CALL_KEY(tp_func_##_name),	\
		.अटल_call_tramp = STATIC_CALL_TRAMP_ADDR(tp_func_##_name), \
		.iterator = &__traceiter_##_name,			\
		.regfunc = _reg,					\
		.unregfunc = _unreg,					\
		.funcs = शून्य पूर्ण;					\
	__TRACEPOINT_ENTRY(_name);					\
	पूर्णांक __traceiter_##_name(व्योम *__data, proto)			\
	अणु								\
		काष्ठा tracepoपूर्णांक_func *it_func_ptr;			\
		व्योम *it_func;						\
									\
		it_func_ptr =						\
			rcu_dereference_raw((&__tracepoपूर्णांक_##_name)->funcs); \
		अगर (it_func_ptr) अणु					\
			करो अणु						\
				it_func = READ_ONCE((it_func_ptr)->func); \
				__data = (it_func_ptr)->data;		\
				((व्योम(*)(व्योम *, proto))(it_func))(__data, args); \
			पूर्ण जबतक ((++it_func_ptr)->func);		\
		पूर्ण							\
		वापस 0;						\
	पूर्ण								\
	DEFINE_STATIC_CALL(tp_func_##_name, __traceiter_##_name);

#घोषणा DEFINE_TRACE(name, proto, args)		\
	DEFINE_TRACE_FN(name, शून्य, शून्य, PARAMS(proto), PARAMS(args));

#घोषणा EXPORT_TRACEPOINT_SYMBOL_GPL(name)				\
	EXPORT_SYMBOL_GPL(__tracepoपूर्णांक_##name);				\
	EXPORT_SYMBOL_GPL(__traceiter_##name);				\
	EXPORT_STATIC_CALL_GPL(tp_func_##name)
#घोषणा EXPORT_TRACEPOINT_SYMBOL(name)					\
	EXPORT_SYMBOL(__tracepoपूर्णांक_##name);				\
	EXPORT_SYMBOL(__traceiter_##name);				\
	EXPORT_STATIC_CALL(tp_func_##name)


#अन्यथा /* !TRACEPOINTS_ENABLED */
#घोषणा __DECLARE_TRACE(name, proto, args, cond, data_proto)		\
	अटल अंतरभूत व्योम trace_##name(proto)				\
	अणु पूर्ण								\
	अटल अंतरभूत व्योम trace_##name##_rcuidle(proto)		\
	अणु पूर्ण								\
	अटल अंतरभूत पूर्णांक						\
	रेजिस्टर_trace_##name(व्योम (*probe)(data_proto),		\
			      व्योम *data)				\
	अणु								\
		वापस -ENOSYS;						\
	पूर्ण								\
	अटल अंतरभूत पूर्णांक						\
	unरेजिस्टर_trace_##name(व्योम (*probe)(data_proto),		\
				व्योम *data)				\
	अणु								\
		वापस -ENOSYS;						\
	पूर्ण								\
	अटल अंतरभूत व्योम check_trace_callback_type_##name(व्योम (*cb)(data_proto)) \
	अणु								\
	पूर्ण								\
	अटल अंतरभूत bool						\
	trace_##name##_enabled(व्योम)					\
	अणु								\
		वापस false;						\
	पूर्ण

#घोषणा DEFINE_TRACE_FN(name, reg, unreg, proto, args)
#घोषणा DEFINE_TRACE(name, proto, args)
#घोषणा EXPORT_TRACEPOINT_SYMBOL_GPL(name)
#घोषणा EXPORT_TRACEPOINT_SYMBOL(name)

#पूर्ण_अगर /* TRACEPOINTS_ENABLED */

#अगर_घोषित CONFIG_TRACING
/**
 * tracepoपूर्णांक_string - रेजिस्टर स्थिरant persistent string to trace प्रणाली
 * @str - a स्थिरant persistent string that will be referenced in tracepoपूर्णांकs
 *
 * If स्थिरant strings are being used in tracepoपूर्णांकs, it is faster and
 * more efficient to just save the poपूर्णांकer to the string and reference
 * that with a म_लिखो "%s" instead of saving the string in the ring buffer
 * and wasting space and समय.
 *
 * The problem with the above approach is that userspace tools that पढ़ो
 * the binary output of the trace buffers करो not have access to the string.
 * Instead they just show the address of the string which is not very
 * useful to users.
 *
 * With tracepoपूर्णांक_string(), the string will be रेजिस्टरed to the tracing
 * प्रणाली and exported to userspace via the debugfs/tracing/prपूर्णांकk_क्रमmats
 * file that maps the string address to the string text. This way userspace
 * tools that पढ़ो the binary buffers have a way to map the poपूर्णांकers to
 * the ASCII strings they represent.
 *
 * The @str used must be a स्थिरant string and persistent as it would not
 * make sense to show a string that no दीर्घer exists. But it is still fine
 * to be used with modules, because when modules are unloaded, अगर they
 * had tracepoपूर्णांकs, the ring buffers are cleared too. As दीर्घ as the string
 * करोes not change during the lअगरe of the module, it is fine to use
 * tracepoपूर्णांक_string() within a module.
 */
#घोषणा tracepoपूर्णांक_string(str)						\
	(अणु								\
		अटल स्थिर अक्षर *___tp_str __tracepoपूर्णांक_string = str; \
		___tp_str;						\
	पूर्ण)
#घोषणा __tracepoपूर्णांक_string	__used __section("__tracepoint_str")
#अन्यथा
/*
 * tracepoपूर्णांक_string() is used to save the string address क्रम userspace
 * tracing tools. When tracing isn't configured, there's no need to save
 * anything.
 */
# define tracepoपूर्णांक_string(str) str
# define __tracepoपूर्णांक_string
#पूर्ण_अगर

#घोषणा DECLARE_TRACE(name, proto, args)				\
	__DECLARE_TRACE(name, PARAMS(proto), PARAMS(args),		\
			cpu_online(raw_smp_processor_id()),		\
			PARAMS(व्योम *__data, proto))

#घोषणा DECLARE_TRACE_CONDITION(name, proto, args, cond)		\
	__DECLARE_TRACE(name, PARAMS(proto), PARAMS(args),		\
			cpu_online(raw_smp_processor_id()) && (PARAMS(cond)), \
			PARAMS(व्योम *__data, proto))

#घोषणा TRACE_EVENT_FLAGS(event, flag)

#घोषणा TRACE_EVENT_PERF_PERM(event, expr...)

#पूर्ण_अगर /* DECLARE_TRACE */

#अगर_अघोषित TRACE_EVENT
/*
 * For use with the TRACE_EVENT macro:
 *
 * We define a tracepoपूर्णांक, its arguments, its prपूर्णांकk क्रमmat
 * and its 'fast binary record' layout.
 *
 * Firstly, name your tracepoपूर्णांक via TRACE_EVENT(name : the
 * 'subsystem_event' notation is fine.
 *
 * Think about this whole स्थिरruct as the
 * 'trace_sched_switch() function' from now on.
 *
 *
 *  TRACE_EVENT(sched_चयन,
 *
 *	*
 *	* A function has a regular function arguments
 *	* prototype, declare it via TP_PROTO():
 *	*
 *
 *	TP_PROTO(काष्ठा rq *rq, काष्ठा task_काष्ठा *prev,
 *		 काष्ठा task_काष्ठा *next),
 *
 *	*
 *	* Define the call signature of the 'function'.
 *	* (Design sidenote: we use this instead of a
 *	*  TP_PROTO1/TP_PROTO2/TP_PROTO3 ugliness.)
 *	*
 *
 *	TP_ARGS(rq, prev, next),
 *
 *	*
 *	* Fast binary tracing: define the trace record via
 *	* TP_STRUCT__entry(). You can think about it like a
 *	* regular C काष्ठाure local variable definition.
 *	*
 *	* This is how the trace record is काष्ठाured and will
 *	* be saved पूर्णांकo the ring buffer. These are the fields
 *	* that will be exposed to user-space in
 *	* /sys/kernel/debug/tracing/events/<*>/क्रमmat.
 *	*
 *	* The declared 'local variable' is called '__entry'
 *	*
 *	* __field(pid_t, prev_prid) is equivalent to a standard declaration:
 *	*
 *	*	pid_t	prev_pid;
 *	*
 *	* __array(अक्षर, prev_comm, TASK_COMM_LEN) is equivalent to:
 *	*
 *	*	अक्षर	prev_comm[TASK_COMM_LEN];
 *	*
 *
 *	TP_STRUCT__entry(
 *		__array(	अक्षर,	prev_comm,	TASK_COMM_LEN	)
 *		__field(	pid_t,	prev_pid			)
 *		__field(	पूर्णांक,	prev_prio			)
 *		__array(	अक्षर,	next_comm,	TASK_COMM_LEN	)
 *		__field(	pid_t,	next_pid			)
 *		__field(	पूर्णांक,	next_prio			)
 *	),
 *
 *	*
 *	* Assign the entry पूर्णांकo the trace record, by embedding
 *	* a full C statement block पूर्णांकo TP_fast_assign(). You
 *	* can refer to the trace record as '__entry' -
 *	* otherwise you can put arbitrary C code in here.
 *	*
 *	* Note: this C code will execute every समय a trace event
 *	* happens, on an active tracepoपूर्णांक.
 *	*
 *
 *	TP_fast_assign(
 *		स_नकल(__entry->next_comm, next->comm, TASK_COMM_LEN);
 *		__entry->prev_pid	= prev->pid;
 *		__entry->prev_prio	= prev->prio;
 *		स_नकल(__entry->prev_comm, prev->comm, TASK_COMM_LEN);
 *		__entry->next_pid	= next->pid;
 *		__entry->next_prio	= next->prio;
 *	),
 *
 *	*
 *	* Formatted output of a trace record via TP_prपूर्णांकk().
 *	* This is how the tracepoपूर्णांक will appear under ftrace
 *	* plugins that make use of this tracepoपूर्णांक.
 *	*
 *	* (raw-binary tracing wont actually perक्रमm this step.)
 *	*
 *
 *	TP_prपूर्णांकk("task %s:%d [%d] ==> %s:%d [%d]",
 *		__entry->prev_comm, __entry->prev_pid, __entry->prev_prio,
 *		__entry->next_comm, __entry->next_pid, __entry->next_prio),
 *
 * );
 *
 * This macro स्थिरruct is thus used क्रम the regular prपूर्णांकk क्रमmat
 * tracing setup, it is used to स्थिरruct a function poपूर्णांकer based
 * tracepoपूर्णांक callback (this is used by programmatic plugins and
 * can also by used by generic instrumentation like SystemTap), and
 * it is also used to expose a काष्ठाured trace record in
 * /sys/kernel/debug/tracing/events/.
 *
 * A set of (un)registration functions can be passed to the variant
 * TRACE_EVENT_FN to perक्रमm any (un)registration work.
 */

#घोषणा DECLARE_EVENT_CLASS(name, proto, args, tकाष्ठा, assign, prपूर्णांक)
#घोषणा DEFINE_EVENT(ढाँचा, name, proto, args)		\
	DECLARE_TRACE(name, PARAMS(proto), PARAMS(args))
#घोषणा DEFINE_EVENT_FN(ढाँचा, name, proto, args, reg, unreg)\
	DECLARE_TRACE(name, PARAMS(proto), PARAMS(args))
#घोषणा DEFINE_EVENT_PRINT(ढाँचा, name, proto, args, prपूर्णांक)	\
	DECLARE_TRACE(name, PARAMS(proto), PARAMS(args))
#घोषणा DEFINE_EVENT_CONDITION(ढाँचा, name, proto,		\
			       args, cond)			\
	DECLARE_TRACE_CONDITION(name, PARAMS(proto),		\
				PARAMS(args), PARAMS(cond))

#घोषणा TRACE_EVENT(name, proto, args, काष्ठा, assign, prपूर्णांक)	\
	DECLARE_TRACE(name, PARAMS(proto), PARAMS(args))
#घोषणा TRACE_EVENT_FN(name, proto, args, काष्ठा,		\
		assign, prपूर्णांक, reg, unreg)			\
	DECLARE_TRACE(name, PARAMS(proto), PARAMS(args))
#घोषणा TRACE_EVENT_FN_COND(name, proto, args, cond, काष्ठा,		\
		assign, prपूर्णांक, reg, unreg)			\
	DECLARE_TRACE_CONDITION(name, PARAMS(proto),	\
			PARAMS(args), PARAMS(cond))
#घोषणा TRACE_EVENT_CONDITION(name, proto, args, cond,		\
			      काष्ठा, assign, prपूर्णांक)		\
	DECLARE_TRACE_CONDITION(name, PARAMS(proto),		\
				PARAMS(args), PARAMS(cond))

#घोषणा TRACE_EVENT_FLAGS(event, flag)

#घोषणा TRACE_EVENT_PERF_PERM(event, expr...)

#घोषणा DECLARE_EVENT_NOP(name, proto, args)				\
	अटल अंतरभूत व्योम trace_##name(proto)				\
	अणु पूर्ण								\
	अटल अंतरभूत bool trace_##name##_enabled(व्योम)			\
	अणु								\
		वापस false;						\
	पूर्ण

#घोषणा TRACE_EVENT_NOP(name, proto, args, काष्ठा, assign, prपूर्णांक)	\
	DECLARE_EVENT_NOP(name, PARAMS(proto), PARAMS(args))

#घोषणा DECLARE_EVENT_CLASS_NOP(name, proto, args, tकाष्ठा, assign, prपूर्णांक)
#घोषणा DEFINE_EVENT_NOP(ढाँचा, name, proto, args)			\
	DECLARE_EVENT_NOP(name, PARAMS(proto), PARAMS(args))

#पूर्ण_अगर /* अगरdef TRACE_EVENT (see note above) */
