<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अघोषित TRACE_SYSTEM_VAR

#अगर_घोषित CONFIG_PERF_EVENTS

#अघोषित __entry
#घोषणा __entry entry

#अघोषित __get_dynamic_array
#घोषणा __get_dynamic_array(field)	\
		((व्योम *)__entry + (__entry->__data_loc_##field & 0xffff))

#अघोषित __get_dynamic_array_len
#घोषणा __get_dynamic_array_len(field)	\
		((__entry->__data_loc_##field >> 16) & 0xffff)

#अघोषित __get_str
#घोषणा __get_str(field) ((अक्षर *)__get_dynamic_array(field))

#अघोषित __get_biपंचांगask
#घोषणा __get_biपंचांगask(field) (अक्षर *)__get_dynamic_array(field)

#अघोषित __perf_count
#घोषणा __perf_count(c)	(__count = (c))

#अघोषित __perf_task
#घोषणा __perf_task(t)	(__task = (t))

#अघोषित DECLARE_EVENT_CLASS
#घोषणा DECLARE_EVENT_CLASS(call, proto, args, tकाष्ठा, assign, prपूर्णांक)	\
अटल notrace व्योम							\
perf_trace_##call(व्योम *__data, proto)					\
अणु									\
	काष्ठा trace_event_call *event_call = __data;			\
	काष्ठा trace_event_data_offsets_##call __maybe_unused __data_offsets;\
	काष्ठा trace_event_raw_##call *entry;				\
	काष्ठा pt_regs *__regs;						\
	u64 __count = 1;						\
	काष्ठा task_काष्ठा *__task = शून्य;				\
	काष्ठा hlist_head *head;					\
	पूर्णांक __entry_size;						\
	पूर्णांक __data_size;						\
	पूर्णांक rctx;							\
									\
	__data_size = trace_event_get_offsets_##call(&__data_offsets, args); \
									\
	head = this_cpu_ptr(event_call->perf_events);			\
	अगर (!bpf_prog_array_valid(event_call) &&			\
	    __builtin_स्थिरant_p(!__task) && !__task &&			\
	    hlist_empty(head))						\
		वापस;							\
									\
	__entry_size = ALIGN(__data_size + माप(*entry) + माप(u32),\
			     माप(u64));				\
	__entry_size -= माप(u32);					\
									\
	entry = perf_trace_buf_alloc(__entry_size, &__regs, &rctx);	\
	अगर (!entry)							\
		वापस;							\
									\
	perf_fetch_caller_regs(__regs);					\
									\
	tकाष्ठा								\
									\
	अणु assign; पूर्ण							\
									\
	perf_trace_run_bpf_submit(entry, __entry_size, rctx,		\
				  event_call, __count, __regs,		\
				  head, __task);			\
पूर्ण

/*
 * This part is compiled out, it is only here as a build समय check
 * to make sure that अगर the tracepoपूर्णांक handling changes, the
 * perf probe will fail to compile unless it too is updated.
 */
#अघोषित DEFINE_EVENT
#घोषणा DEFINE_EVENT(ढाँचा, call, proto, args)			\
अटल अंतरभूत व्योम perf_test_probe_##call(व्योम)				\
अणु									\
	check_trace_callback_type_##call(perf_trace_##ढाँचा);	\
पूर्ण


#अघोषित DEFINE_EVENT_PRINT
#घोषणा DEFINE_EVENT_PRINT(ढाँचा, name, proto, args, prपूर्णांक)	\
	DEFINE_EVENT(ढाँचा, name, PARAMS(proto), PARAMS(args))

#समावेश TRACE_INCLUDE(TRACE_INCLUDE_खाता)
#पूर्ण_अगर /* CONFIG_PERF_EVENTS */
