<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अघोषित TRACE_SYSTEM_VAR

#अगर_घोषित CONFIG_BPF_EVENTS

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
#घोषणा __perf_count(c)	(c)

#अघोषित __perf_task
#घोषणा __perf_task(t)	(t)

/* cast any पूर्णांकeger, poपूर्णांकer, or small काष्ठा to u64 */
#घोषणा UINTTYPE(size) \
	__typeof__(__builtin_choose_expr(size == 1,  (u8)1, \
		   __builtin_choose_expr(size == 2, (u16)2, \
		   __builtin_choose_expr(size == 4, (u32)3, \
		   __builtin_choose_expr(size == 8, (u64)4, \
					 (व्योम)5)))))
#घोषणा __CAST_TO_U64(x) (अणु \
	typeof(x) __src = (x); \
	UINTTYPE(माप(x)) __dst; \
	स_नकल(&__dst, &__src, माप(__dst)); \
	(u64)__dst; पूर्ण)

#घोषणा __CAST1(a,...) __CAST_TO_U64(a)
#घोषणा __CAST2(a,...) __CAST_TO_U64(a), __CAST1(__VA_ARGS__)
#घोषणा __CAST3(a,...) __CAST_TO_U64(a), __CAST2(__VA_ARGS__)
#घोषणा __CAST4(a,...) __CAST_TO_U64(a), __CAST3(__VA_ARGS__)
#घोषणा __CAST5(a,...) __CAST_TO_U64(a), __CAST4(__VA_ARGS__)
#घोषणा __CAST6(a,...) __CAST_TO_U64(a), __CAST5(__VA_ARGS__)
#घोषणा __CAST7(a,...) __CAST_TO_U64(a), __CAST6(__VA_ARGS__)
#घोषणा __CAST8(a,...) __CAST_TO_U64(a), __CAST7(__VA_ARGS__)
#घोषणा __CAST9(a,...) __CAST_TO_U64(a), __CAST8(__VA_ARGS__)
#घोषणा __CAST10(a,...) __CAST_TO_U64(a), __CAST9(__VA_ARGS__)
#घोषणा __CAST11(a,...) __CAST_TO_U64(a), __CAST10(__VA_ARGS__)
#घोषणा __CAST12(a,...) __CAST_TO_U64(a), __CAST11(__VA_ARGS__)
/* tracepoपूर्णांकs with more than 12 arguments will hit build error */
#घोषणा CAST_TO_U64(...) CONCATENATE(__CAST, COUNT_ARGS(__VA_ARGS__))(__VA_ARGS__)

#घोषणा __BPF_DECLARE_TRACE(call, proto, args)				\
अटल notrace व्योम							\
__bpf_trace_##call(व्योम *__data, proto)					\
अणु									\
	काष्ठा bpf_prog *prog = __data;					\
	CONCATENATE(bpf_trace_run, COUNT_ARGS(args))(prog, CAST_TO_U64(args));	\
पूर्ण

#अघोषित DECLARE_EVENT_CLASS
#घोषणा DECLARE_EVENT_CLASS(call, proto, args, tकाष्ठा, assign, prपूर्णांक)	\
	__BPF_DECLARE_TRACE(call, PARAMS(proto), PARAMS(args))

/*
 * This part is compiled out, it is only here as a build समय check
 * to make sure that अगर the tracepoपूर्णांक handling changes, the
 * bpf probe will fail to compile unless it too is updated.
 */
#घोषणा __DEFINE_EVENT(ढाँचा, call, proto, args, size)		\
अटल अंतरभूत व्योम bpf_test_probe_##call(व्योम)				\
अणु									\
	check_trace_callback_type_##call(__bpf_trace_##ढाँचा);	\
पूर्ण									\
प्रकार व्योम (*btf_trace_##call)(व्योम *__data, proto);			\
अटल जोड़ अणु								\
	काष्ठा bpf_raw_event_map event;					\
	btf_trace_##call handler;					\
पूर्ण __bpf_trace_tp_map_##call __used					\
__section("__bpf_raw_tp_map") = अणु					\
	.event = अणु							\
		.tp		= &__tracepoपूर्णांक_##call,			\
		.bpf_func	= __bpf_trace_##ढाँचा,		\
		.num_args	= COUNT_ARGS(args),			\
		.writable_size	= size,					\
	पूर्ण,								\
पूर्ण;

#घोषणा FIRST(x, ...) x

#अघोषित DEFINE_EVENT_WRITABLE
#घोषणा DEFINE_EVENT_WRITABLE(ढाँचा, call, proto, args, size)	\
अटल अंतरभूत व्योम bpf_test_buffer_##call(व्योम)				\
अणु									\
	/* BUILD_BUG_ON() is ignored अगर the code is completely eliminated, but \
	 * BUILD_BUG_ON_ZERO() uses a dअगरferent mechanism that is not	\
	 * dead-code-eliminated.					\
	 */								\
	FIRST(proto);							\
	(व्योम)BUILD_BUG_ON_ZERO(size != माप(*FIRST(args)));		\
पूर्ण									\
__DEFINE_EVENT(ढाँचा, call, PARAMS(proto), PARAMS(args), size)

#अघोषित DEFINE_EVENT
#घोषणा DEFINE_EVENT(ढाँचा, call, proto, args)			\
	__DEFINE_EVENT(ढाँचा, call, PARAMS(proto), PARAMS(args), 0)

#अघोषित DEFINE_EVENT_PRINT
#घोषणा DEFINE_EVENT_PRINT(ढाँचा, name, proto, args, prपूर्णांक)	\
	DEFINE_EVENT(ढाँचा, name, PARAMS(proto), PARAMS(args))

#अघोषित DECLARE_TRACE
#घोषणा DECLARE_TRACE(call, proto, args)				\
	__BPF_DECLARE_TRACE(call, PARAMS(proto), PARAMS(args))		\
	__DEFINE_EVENT(call, call, PARAMS(proto), PARAMS(args), 0)

#समावेश TRACE_INCLUDE(TRACE_INCLUDE_खाता)

#अघोषित DEFINE_EVENT_WRITABLE
#अघोषित __DEFINE_EVENT
#अघोषित FIRST

#पूर्ण_अगर /* CONFIG_BPF_EVENTS */
