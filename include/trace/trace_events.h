<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Stage 1 of the trace events.
 *
 * Override the macros in the event tracepoपूर्णांक header <trace/events/XXX.h>
 * to include the following:
 *
 * काष्ठा trace_event_raw_<call> अणु
 *	काष्ठा trace_entry		ent;
 *	<type>				<item>;
 *	<type2>				<item2>[<len>];
 *	[...]
 * पूर्ण;
 *
 * The <type> <item> is created by the __field(type, item) macro or
 * the __array(type2, item2, len) macro.
 * We simply करो "type item;", and that will create the fields
 * in the काष्ठाure.
 */

#समावेश <linux/trace_events.h>

#अगर_अघोषित TRACE_SYSTEM_VAR
#घोषणा TRACE_SYSTEM_VAR TRACE_SYSTEM
#पूर्ण_अगर

#घोषणा __app__(x, y) str__##x##y
#घोषणा __app(x, y) __app__(x, y)

#घोषणा TRACE_SYSTEM_STRING __app(TRACE_SYSTEM_VAR,__trace_प्रणाली_name)

#घोषणा TRACE_MAKE_SYSTEM_STR()				\
	अटल स्थिर अक्षर TRACE_SYSTEM_STRING[] =	\
		__stringअगरy(TRACE_SYSTEM)

TRACE_MAKE_SYSTEM_STR();

#अघोषित TRACE_DEFINE_ENUM
#घोषणा TRACE_DEFINE_ENUM(a)				\
	अटल काष्ठा trace_eval_map __used __initdata	\
	__##TRACE_SYSTEM##_##a =			\
	अणु						\
		.प्रणाली = TRACE_SYSTEM_STRING,		\
		.eval_string = #a,			\
		.eval_value = a				\
	पूर्ण;						\
	अटल काष्ठा trace_eval_map __used		\
	__section("_ftrace_eval_map")			\
	*TRACE_SYSTEM##_##a = &__##TRACE_SYSTEM##_##a

#अघोषित TRACE_DEFINE_SIZखातापूर्ण
#घोषणा TRACE_DEFINE_SIZखातापूर्ण(a)				\
	अटल काष्ठा trace_eval_map __used __initdata	\
	__##TRACE_SYSTEM##_##a =			\
	अणु						\
		.प्रणाली = TRACE_SYSTEM_STRING,		\
		.eval_string = "sizeof(" #a ")",	\
		.eval_value = माप(a)			\
	पूर्ण;						\
	अटल काष्ठा trace_eval_map __used		\
	__section("_ftrace_eval_map")			\
	*TRACE_SYSTEM##_##a = &__##TRACE_SYSTEM##_##a

/*
 * DECLARE_EVENT_CLASS can be used to add a generic function
 * handlers क्रम events. That is, अगर all events have the same
 * parameters and just have distinct trace poपूर्णांकs.
 * Each tracepoपूर्णांक can be defined with DEFINE_EVENT and that
 * will map the DECLARE_EVENT_CLASS to the tracepoपूर्णांक.
 *
 * TRACE_EVENT is a one to one mapping between tracepoपूर्णांक and ढाँचा.
 */
#अघोषित TRACE_EVENT
#घोषणा TRACE_EVENT(name, proto, args, tकाष्ठा, assign, prपूर्णांक) \
	DECLARE_EVENT_CLASS(name,			       \
			     PARAMS(proto),		       \
			     PARAMS(args),		       \
			     PARAMS(tकाष्ठा),		       \
			     PARAMS(assign),		       \
			     PARAMS(prपूर्णांक));		       \
	DEFINE_EVENT(name, name, PARAMS(proto), PARAMS(args));


#अघोषित __field
#घोषणा __field(type, item)		type	item;

#अघोषित __field_ext
#घोषणा __field_ext(type, item, filter_type)	type	item;

#अघोषित __field_काष्ठा
#घोषणा __field_काष्ठा(type, item)	type	item;

#अघोषित __field_काष्ठा_ext
#घोषणा __field_काष्ठा_ext(type, item, filter_type)	type	item;

#अघोषित __array
#घोषणा __array(type, item, len)	type	item[len];

#अघोषित __dynamic_array
#घोषणा __dynamic_array(type, item, len) u32 __data_loc_##item;

#अघोषित __string
#घोषणा __string(item, src) __dynamic_array(अक्षर, item, -1)

#अघोषित __biपंचांगask
#घोषणा __biपंचांगask(item, nr_bits) __dynamic_array(अक्षर, item, -1)

#अघोषित TP_STRUCT__entry
#घोषणा TP_STRUCT__entry(args...) args

#अघोषित DECLARE_EVENT_CLASS
#घोषणा DECLARE_EVENT_CLASS(name, proto, args, tकाष्ठा, assign, prपूर्णांक)	\
	काष्ठा trace_event_raw_##name अणु					\
		काष्ठा trace_entry	ent;				\
		tकाष्ठा							\
		अक्षर			__data[0];			\
	पूर्ण;								\
									\
	अटल काष्ठा trace_event_class event_class_##name;

#अघोषित DEFINE_EVENT
#घोषणा DEFINE_EVENT(ढाँचा, name, proto, args)	\
	अटल काष्ठा trace_event_call	__used		\
	__attribute__((__aligned__(4))) event_##name

#अघोषित DEFINE_EVENT_FN
#घोषणा DEFINE_EVENT_FN(ढाँचा, name, proto, args, reg, unreg)	\
	DEFINE_EVENT(ढाँचा, name, PARAMS(proto), PARAMS(args))

#अघोषित DEFINE_EVENT_PRINT
#घोषणा DEFINE_EVENT_PRINT(ढाँचा, name, proto, args, prपूर्णांक)	\
	DEFINE_EVENT(ढाँचा, name, PARAMS(proto), PARAMS(args))

/* Callbacks are meaningless to ftrace. */
#अघोषित TRACE_EVENT_FN
#घोषणा TRACE_EVENT_FN(name, proto, args, tकाष्ठा,			\
		assign, prपूर्णांक, reg, unreg)				\
	TRACE_EVENT(name, PARAMS(proto), PARAMS(args),			\
		PARAMS(tकाष्ठा), PARAMS(assign), PARAMS(prपूर्णांक))		\

#अघोषित TRACE_EVENT_FN_COND
#घोषणा TRACE_EVENT_FN_COND(name, proto, args, cond, tकाष्ठा,	\
		assign, prपूर्णांक, reg, unreg)				\
	TRACE_EVENT_CONDITION(name, PARAMS(proto), PARAMS(args), PARAMS(cond),		\
		PARAMS(tकाष्ठा), PARAMS(assign), PARAMS(prपूर्णांक))		\

#अघोषित TRACE_EVENT_FLAGS
#घोषणा TRACE_EVENT_FLAGS(name, value)					\
	__TRACE_EVENT_FLAGS(name, value)

#अघोषित TRACE_EVENT_PERF_PERM
#घोषणा TRACE_EVENT_PERF_PERM(name, expr...)				\
	__TRACE_EVENT_PERF_PERM(name, expr)

#समावेश TRACE_INCLUDE(TRACE_INCLUDE_खाता)

/*
 * Stage 2 of the trace events.
 *
 * Include the following:
 *
 * काष्ठा trace_event_data_offsets_<call> अणु
 *	u32				<item1>;
 *	u32				<item2>;
 *	[...]
 * पूर्ण;
 *
 * The __dynamic_array() macro will create each u32 <item>, this is
 * to keep the offset of each array from the beginning of the event.
 * The size of an array is also encoded, in the higher 16 bits of <item>.
 */

#अघोषित TRACE_DEFINE_ENUM
#घोषणा TRACE_DEFINE_ENUM(a)

#अघोषित TRACE_DEFINE_SIZखातापूर्ण
#घोषणा TRACE_DEFINE_SIZखातापूर्ण(a)

#अघोषित __field
#घोषणा __field(type, item)

#अघोषित __field_ext
#घोषणा __field_ext(type, item, filter_type)

#अघोषित __field_काष्ठा
#घोषणा __field_काष्ठा(type, item)

#अघोषित __field_काष्ठा_ext
#घोषणा __field_काष्ठा_ext(type, item, filter_type)

#अघोषित __array
#घोषणा __array(type, item, len)

#अघोषित __dynamic_array
#घोषणा __dynamic_array(type, item, len)	u32 item;

#अघोषित __string
#घोषणा __string(item, src) __dynamic_array(अक्षर, item, -1)

#अघोषित __biपंचांगask
#घोषणा __biपंचांगask(item, nr_bits) __dynamic_array(अचिन्हित दीर्घ, item, -1)

#अघोषित DECLARE_EVENT_CLASS
#घोषणा DECLARE_EVENT_CLASS(call, proto, args, tकाष्ठा, assign, prपूर्णांक)	\
	काष्ठा trace_event_data_offsets_##call अणु			\
		tकाष्ठा;						\
	पूर्ण;

#अघोषित DEFINE_EVENT
#घोषणा DEFINE_EVENT(ढाँचा, name, proto, args)

#अघोषित DEFINE_EVENT_PRINT
#घोषणा DEFINE_EVENT_PRINT(ढाँचा, name, proto, args, prपूर्णांक)

#अघोषित TRACE_EVENT_FLAGS
#घोषणा TRACE_EVENT_FLAGS(event, flag)

#अघोषित TRACE_EVENT_PERF_PERM
#घोषणा TRACE_EVENT_PERF_PERM(event, expr...)

#समावेश TRACE_INCLUDE(TRACE_INCLUDE_खाता)

/*
 * Stage 3 of the trace events.
 *
 * Override the macros in the event tracepoपूर्णांक header <trace/events/XXX.h>
 * to include the following:
 *
 * क्रमागत prपूर्णांक_line_t
 * trace_raw_output_<call>(काष्ठा trace_iterator *iter, पूर्णांक flags)
 * अणु
 *	काष्ठा trace_seq *s = &iter->seq;
 *	काष्ठा trace_event_raw_<call> *field; <-- defined in stage 1
 *	काष्ठा trace_seq *p = &iter->पंचांगp_seq;
 *
 * -------(क्रम event)-------
 *
 *	काष्ठा trace_entry *entry;
 *
 *	entry = iter->ent;
 *
 *	अगर (entry->type != event_<call>->event.type) अणु
 *		WARN_ON_ONCE(1);
 *		वापस TRACE_TYPE_UNHANDLED;
 *	पूर्ण
 *
 *	field = (typeof(field))entry;
 *
 *	trace_seq_init(p);
 *	वापस trace_output_call(iter, <call>, <TP_prपूर्णांकk> "\n");
 *
 * ------(or, क्रम event class)------
 *
 *	पूर्णांक ret;
 *
 *	field = (typeof(field))iter->ent;
 *
 *	ret = trace_raw_output_prep(iter, trace_event);
 *	अगर (ret != TRACE_TYPE_HANDLED)
 *		वापस ret;
 *
 *	trace_event_म_लिखो(iter, <TP_prपूर्णांकk> "\n");
 *
 *	वापस trace_handle_वापस(s);
 * -------
 *  पूर्ण
 *
 * This is the method used to prपूर्णांक the raw event to the trace
 * output क्रमmat. Note, this is not needed अगर the data is पढ़ो
 * in binary.
 */

#अघोषित __entry
#घोषणा __entry field

#अघोषित TP_prपूर्णांकk
#घोषणा TP_prपूर्णांकk(fmt, args...) fmt "\n", args

#अघोषित __get_dynamic_array
#घोषणा __get_dynamic_array(field)	\
		((व्योम *)__entry + (__entry->__data_loc_##field & 0xffff))

#अघोषित __get_dynamic_array_len
#घोषणा __get_dynamic_array_len(field)	\
		((__entry->__data_loc_##field >> 16) & 0xffff)

#अघोषित __get_str
#घोषणा __get_str(field) ((अक्षर *)__get_dynamic_array(field))

#अघोषित __get_biपंचांगask
#घोषणा __get_biपंचांगask(field)						\
	(अणु								\
		व्योम *__biपंचांगask = __get_dynamic_array(field);		\
		अचिन्हित पूर्णांक __biपंचांगask_size;				\
		__biपंचांगask_size = __get_dynamic_array_len(field);	\
		trace_prपूर्णांक_biपंचांगask_seq(p, __biपंचांगask, __biपंचांगask_size);	\
	पूर्ण)

#अघोषित __prपूर्णांक_flags
#घोषणा __prपूर्णांक_flags(flag, delim, flag_array...)			\
	(अणु								\
		अटल स्थिर काष्ठा trace_prपूर्णांक_flags __flags[] =	\
			अणु flag_array, अणु -1, शून्य पूर्णपूर्ण;			\
		trace_prपूर्णांक_flags_seq(p, delim, flag, __flags);	\
	पूर्ण)

#अघोषित __prपूर्णांक_symbolic
#घोषणा __prपूर्णांक_symbolic(value, symbol_array...)			\
	(अणु								\
		अटल स्थिर काष्ठा trace_prपूर्णांक_flags symbols[] =	\
			अणु symbol_array, अणु -1, शून्य पूर्णपूर्ण;			\
		trace_prपूर्णांक_symbols_seq(p, value, symbols);		\
	पूर्ण)

#अघोषित __prपूर्णांक_flags_u64
#अघोषित __prपूर्णांक_symbolic_u64
#अगर BITS_PER_LONG == 32
#घोषणा __prपूर्णांक_flags_u64(flag, delim, flag_array...)			\
	(अणु								\
		अटल स्थिर काष्ठा trace_prपूर्णांक_flags_u64 __flags[] =	\
			अणु flag_array, अणु -1, शून्य पूर्ण पूर्ण;			\
		trace_prपूर्णांक_flags_seq_u64(p, delim, flag, __flags);	\
	पूर्ण)

#घोषणा __prपूर्णांक_symbolic_u64(value, symbol_array...)			\
	(अणु								\
		अटल स्थिर काष्ठा trace_prपूर्णांक_flags_u64 symbols[] =	\
			अणु symbol_array, अणु -1, शून्य पूर्ण पूर्ण;			\
		trace_prपूर्णांक_symbols_seq_u64(p, value, symbols);	\
	पूर्ण)
#अन्यथा
#घोषणा __prपूर्णांक_flags_u64(flag, delim, flag_array...)			\
			__prपूर्णांक_flags(flag, delim, flag_array)

#घोषणा __prपूर्णांक_symbolic_u64(value, symbol_array...)			\
			__prपूर्णांक_symbolic(value, symbol_array)
#पूर्ण_अगर

#अघोषित __prपूर्णांक_hex
#घोषणा __prपूर्णांक_hex(buf, buf_len)					\
	trace_prपूर्णांक_hex_seq(p, buf, buf_len, false)

#अघोषित __prपूर्णांक_hex_str
#घोषणा __prपूर्णांक_hex_str(buf, buf_len)					\
	trace_prपूर्णांक_hex_seq(p, buf, buf_len, true)

#अघोषित __prपूर्णांक_array
#घोषणा __prपूर्णांक_array(array, count, el_size)				\
	(अणु								\
		BUILD_BUG_ON(el_size != 1 && el_size != 2 &&		\
			     el_size != 4 && el_size != 8);		\
		trace_prपूर्णांक_array_seq(p, array, count, el_size);	\
	पूर्ण)

#अघोषित __prपूर्णांक_hex_dump
#घोषणा __prपूर्णांक_hex_dump(prefix_str, prefix_type,			\
			 rowsize, groupsize, buf, len, ascii)		\
	trace_prपूर्णांक_hex_dump_seq(p, prefix_str, prefix_type,		\
				 rowsize, groupsize, buf, len, ascii)

#अघोषित DECLARE_EVENT_CLASS
#घोषणा DECLARE_EVENT_CLASS(call, proto, args, tकाष्ठा, assign, prपूर्णांक)	\
अटल notrace क्रमागत prपूर्णांक_line_t					\
trace_raw_output_##call(काष्ठा trace_iterator *iter, पूर्णांक flags,		\
			काष्ठा trace_event *trace_event)		\
अणु									\
	काष्ठा trace_seq *s = &iter->seq;				\
	काष्ठा trace_seq __maybe_unused *p = &iter->पंचांगp_seq;		\
	काष्ठा trace_event_raw_##call *field;				\
	पूर्णांक ret;							\
									\
	field = (typeof(field))iter->ent;				\
									\
	ret = trace_raw_output_prep(iter, trace_event);			\
	अगर (ret != TRACE_TYPE_HANDLED)					\
		वापस ret;						\
									\
	trace_event_म_लिखो(iter, prपूर्णांक);				\
									\
	वापस trace_handle_वापस(s);					\
पूर्ण									\
अटल काष्ठा trace_event_functions trace_event_type_funcs_##call = अणु	\
	.trace			= trace_raw_output_##call,		\
पूर्ण;

#अघोषित DEFINE_EVENT_PRINT
#घोषणा DEFINE_EVENT_PRINT(ढाँचा, call, proto, args, prपूर्णांक)		\
अटल notrace क्रमागत prपूर्णांक_line_t					\
trace_raw_output_##call(काष्ठा trace_iterator *iter, पूर्णांक flags,		\
			 काष्ठा trace_event *event)			\
अणु									\
	काष्ठा trace_event_raw_##ढाँचा *field;			\
	काष्ठा trace_entry *entry;					\
	काष्ठा trace_seq *p = &iter->पंचांगp_seq;				\
									\
	entry = iter->ent;						\
									\
	अगर (entry->type != event_##call.event.type) अणु			\
		WARN_ON_ONCE(1);					\
		वापस TRACE_TYPE_UNHANDLED;				\
	पूर्ण								\
									\
	field = (typeof(field))entry;					\
									\
	trace_seq_init(p);						\
	वापस trace_output_call(iter, #call, prपूर्णांक);			\
पूर्ण									\
अटल काष्ठा trace_event_functions trace_event_type_funcs_##call = अणु	\
	.trace			= trace_raw_output_##call,		\
पूर्ण;

#समावेश TRACE_INCLUDE(TRACE_INCLUDE_खाता)

#अघोषित __field_ext
#घोषणा __field_ext(_type, _item, _filter_type) अणु			\
	.type = #_type, .name = #_item,					\
	.size = माप(_type), .align = __alignof__(_type),		\
	.is_चिन्हित = is_चिन्हित_type(_type), .filter_type = _filter_type पूर्ण,

#अघोषित __field_काष्ठा_ext
#घोषणा __field_काष्ठा_ext(_type, _item, _filter_type) अणु		\
	.type = #_type, .name = #_item,					\
	.size = माप(_type), .align = __alignof__(_type),		\
	0, .filter_type = _filter_type पूर्ण,

#अघोषित __field
#घोषणा __field(type, item)	__field_ext(type, item, FILTER_OTHER)

#अघोषित __field_काष्ठा
#घोषणा __field_काष्ठा(type, item) __field_काष्ठा_ext(type, item, FILTER_OTHER)

#अघोषित __array
#घोषणा __array(_type, _item, _len) अणु					\
	.type = #_type"["__stringअगरy(_len)"]", .name = #_item,		\
	.size = माप(_type[_len]), .align = __alignof__(_type),	\
	.is_चिन्हित = is_चिन्हित_type(_type), .filter_type = FILTER_OTHER पूर्ण,

#अघोषित __dynamic_array
#घोषणा __dynamic_array(_type, _item, _len) अणु				\
	.type = "__data_loc " #_type "[]", .name = #_item,		\
	.size = 4, .align = 4,						\
	.is_चिन्हित = is_चिन्हित_type(_type), .filter_type = FILTER_OTHER पूर्ण,

#अघोषित __string
#घोषणा __string(item, src) __dynamic_array(अक्षर, item, -1)

#अघोषित __biपंचांगask
#घोषणा __biपंचांगask(item, nr_bits) __dynamic_array(अचिन्हित दीर्घ, item, -1)

#अघोषित DECLARE_EVENT_CLASS
#घोषणा DECLARE_EVENT_CLASS(call, proto, args, tकाष्ठा, func, prपूर्णांक)	\
अटल काष्ठा trace_event_fields trace_event_fields_##call[] = अणु	\
	tकाष्ठा								\
	अणुपूर्ण पूर्ण;

#अघोषित DEFINE_EVENT_PRINT
#घोषणा DEFINE_EVENT_PRINT(ढाँचा, name, proto, args, prपूर्णांक)

#समावेश TRACE_INCLUDE(TRACE_INCLUDE_खाता)

/*
 * remember the offset of each array from the beginning of the event.
 */

#अघोषित __entry
#घोषणा __entry entry

#अघोषित __field
#घोषणा __field(type, item)

#अघोषित __field_ext
#घोषणा __field_ext(type, item, filter_type)

#अघोषित __field_काष्ठा
#घोषणा __field_काष्ठा(type, item)

#अघोषित __field_काष्ठा_ext
#घोषणा __field_काष्ठा_ext(type, item, filter_type)

#अघोषित __array
#घोषणा __array(type, item, len)

#अघोषित __dynamic_array
#घोषणा __dynamic_array(type, item, len)				\
	__item_length = (len) * माप(type);				\
	__data_offsets->item = __data_size +				\
			       दुरत्व(typeof(*entry), __data);	\
	__data_offsets->item |= __item_length << 16;			\
	__data_size += __item_length;

#अघोषित __string
#घोषणा __string(item, src) __dynamic_array(अक्षर, item,			\
		    म_माप((src) ? (स्थिर अक्षर *)(src) : "(null)") + 1)

/*
 * __biपंचांगask_size_in_bytes_raw is the number of bytes needed to hold
 * num_possible_cpus().
 */
#घोषणा __biपंचांगask_size_in_bytes_raw(nr_bits)	\
	(((nr_bits) + 7) / 8)

#घोषणा __biपंचांगask_size_in_दीर्घs(nr_bits)			\
	((__biपंचांगask_size_in_bytes_raw(nr_bits) +		\
	  ((BITS_PER_LONG / 8) - 1)) / (BITS_PER_LONG / 8))

/*
 * __biपंचांगask_size_in_bytes is the number of bytes needed to hold
 * num_possible_cpus() padded out to the nearest दीर्घ. This is what
 * is saved in the buffer, just to be consistent.
 */
#घोषणा __biपंचांगask_size_in_bytes(nr_bits)				\
	(__biपंचांगask_size_in_दीर्घs(nr_bits) * (BITS_PER_LONG / 8))

#अघोषित __biपंचांगask
#घोषणा __biपंचांगask(item, nr_bits) __dynamic_array(अचिन्हित दीर्घ, item,	\
					 __biपंचांगask_size_in_दीर्घs(nr_bits))

#अघोषित DECLARE_EVENT_CLASS
#घोषणा DECLARE_EVENT_CLASS(call, proto, args, tकाष्ठा, assign, prपूर्णांक)	\
अटल अंतरभूत notrace पूर्णांक trace_event_get_offsets_##call(		\
	काष्ठा trace_event_data_offsets_##call *__data_offsets, proto)	\
अणु									\
	पूर्णांक __data_size = 0;						\
	पूर्णांक __maybe_unused __item_length;				\
	काष्ठा trace_event_raw_##call __maybe_unused *entry;		\
									\
	tकाष्ठा;							\
									\
	वापस __data_size;						\
पूर्ण

#समावेश TRACE_INCLUDE(TRACE_INCLUDE_खाता)

/*
 * Stage 4 of the trace events.
 *
 * Override the macros in the event tracepoपूर्णांक header <trace/events/XXX.h>
 * to include the following:
 *
 * For those macros defined with TRACE_EVENT:
 *
 * अटल काष्ठा trace_event_call event_<call>;
 *
 * अटल व्योम trace_event_raw_event_<call>(व्योम *__data, proto)
 * अणु
 *	काष्ठा trace_event_file *trace_file = __data;
 *	काष्ठा trace_event_call *event_call = trace_file->event_call;
 *	काष्ठा trace_event_data_offsets_<call> __maybe_unused __data_offsets;
 *	अचिन्हित दीर्घ eflags = trace_file->flags;
 *	क्रमागत event_trigger_type __tt = ETT_NONE;
 *	काष्ठा ring_buffer_event *event;
 *	काष्ठा trace_event_raw_<call> *entry; <-- defined in stage 1
 *	काष्ठा trace_buffer *buffer;
 *	अचिन्हित दीर्घ irq_flags;
 *	पूर्णांक __data_size;
 *	पूर्णांक pc;
 *
 *	अगर (!(eflags & EVENT_खाता_FL_TRIGGER_COND)) अणु
 *		अगर (eflags & EVENT_खाता_FL_TRIGGER_MODE)
 *			event_triggers_call(trace_file, शून्य);
 *		अगर (eflags & EVENT_खाता_FL_SOFT_DISABLED)
 *			वापस;
 *	पूर्ण
 *
 *	local_save_flags(irq_flags);
 *	pc = preempt_count();
 *
 *	__data_size = trace_event_get_offsets_<call>(&__data_offsets, args);
 *
 *	event = trace_event_buffer_lock_reserve(&buffer, trace_file,
 *				  event_<call>->event.type,
 *				  माप(*entry) + __data_size,
 *				  irq_flags, pc);
 *	अगर (!event)
 *		वापस;
 *	entry	= ring_buffer_event_data(event);
 *
 *	अणु <assign>; पूर्ण  <-- Here we assign the entries by the __field and
 *			   __array macros.
 *
 *	अगर (eflags & EVENT_खाता_FL_TRIGGER_COND)
 *		__tt = event_triggers_call(trace_file, entry);
 *
 *	अगर (test_bit(EVENT_खाता_FL_SOFT_DISABLED_BIT,
 *		     &trace_file->flags))
 *		ring_buffer_discard_commit(buffer, event);
 *	अन्यथा अगर (!filter_check_discard(trace_file, entry, buffer, event))
 *		trace_buffer_unlock_commit(buffer, event, irq_flags, pc);
 *
 *	अगर (__tt)
 *		event_triggers_post_call(trace_file, __tt);
 * पूर्ण
 *
 * अटल काष्ठा trace_event ftrace_event_type_<call> = अणु
 *	.trace			= trace_raw_output_<call>, <-- stage 2
 * पूर्ण;
 *
 * अटल अक्षर prपूर्णांक_fmt_<call>[] = <TP_prपूर्णांकk>;
 *
 * अटल काष्ठा trace_event_class __used event_class_<ढाँचा> = अणु
 *	.प्रणाली			= "<system>",
 *	.fields_array		= trace_event_fields_<call>,
 *	.fields			= LIST_HEAD_INIT(event_class_##call.fields),
 *	.raw_init		= trace_event_raw_init,
 *	.probe			= trace_event_raw_event_##call,
 *	.reg			= trace_event_reg,
 * पूर्ण;
 *
 * अटल काष्ठा trace_event_call event_<call> = अणु
 *	.class			= event_class_<ढाँचा>,
 *	अणु
 *		.tp			= &__tracepoपूर्णांक_<call>,
 *	पूर्ण,
 *	.event			= &ftrace_event_type_<call>,
 *	.prपूर्णांक_fmt		= prपूर्णांक_fmt_<call>,
 *	.flags			= TRACE_EVENT_FL_TRACEPOINT,
 * पूर्ण;
 * // its only safe to use poपूर्णांकers when करोing linker tricks to
 * // create an array.
 * अटल काष्ठा trace_event_call __used
 * __section("_ftrace_events") *__event_<call> = &event_<call>;
 *
 */

#अगर_घोषित CONFIG_PERF_EVENTS

#घोषणा _TRACE_PERF_PROTO(call, proto)					\
	अटल notrace व्योम						\
	perf_trace_##call(व्योम *__data, proto);

#घोषणा _TRACE_PERF_INIT(call)						\
	.perf_probe		= perf_trace_##call,

#अन्यथा
#घोषणा _TRACE_PERF_PROTO(call, proto)
#घोषणा _TRACE_PERF_INIT(call)
#पूर्ण_अगर /* CONFIG_PERF_EVENTS */

#अघोषित __entry
#घोषणा __entry entry

#अघोषित __field
#घोषणा __field(type, item)

#अघोषित __field_काष्ठा
#घोषणा __field_काष्ठा(type, item)

#अघोषित __array
#घोषणा __array(type, item, len)

#अघोषित __dynamic_array
#घोषणा __dynamic_array(type, item, len)				\
	__entry->__data_loc_##item = __data_offsets.item;

#अघोषित __string
#घोषणा __string(item, src) __dynamic_array(अक्षर, item, -1)

#अघोषित __assign_str
#घोषणा __assign_str(dst, src)						\
	म_नकल(__get_str(dst), (src) ? (स्थिर अक्षर *)(src) : "(null)");

#अघोषित __biपंचांगask
#घोषणा __biपंचांगask(item, nr_bits) __dynamic_array(अचिन्हित दीर्घ, item, -1)

#अघोषित __get_biपंचांगask
#घोषणा __get_biपंचांगask(field) (अक्षर *)__get_dynamic_array(field)

#अघोषित __assign_biपंचांगask
#घोषणा __assign_biपंचांगask(dst, src, nr_bits)					\
	स_नकल(__get_biपंचांगask(dst), (src), __biपंचांगask_size_in_bytes(nr_bits))

#अघोषित TP_fast_assign
#घोषणा TP_fast_assign(args...) args

#अघोषित __perf_count
#घोषणा __perf_count(c)	(c)

#अघोषित __perf_task
#घोषणा __perf_task(t)	(t)

#अघोषित DECLARE_EVENT_CLASS
#घोषणा DECLARE_EVENT_CLASS(call, proto, args, tकाष्ठा, assign, prपूर्णांक)	\
									\
अटल notrace व्योम							\
trace_event_raw_event_##call(व्योम *__data, proto)			\
अणु									\
	काष्ठा trace_event_file *trace_file = __data;			\
	काष्ठा trace_event_data_offsets_##call __maybe_unused __data_offsets;\
	काष्ठा trace_event_buffer fbuffer;				\
	काष्ठा trace_event_raw_##call *entry;				\
	पूर्णांक __data_size;						\
									\
	अगर (trace_trigger_soft_disabled(trace_file))			\
		वापस;							\
									\
	__data_size = trace_event_get_offsets_##call(&__data_offsets, args); \
									\
	entry = trace_event_buffer_reserve(&fbuffer, trace_file,	\
				 माप(*entry) + __data_size);		\
									\
	अगर (!entry)							\
		वापस;							\
									\
	tकाष्ठा								\
									\
	अणु assign; पूर्ण							\
									\
	trace_event_buffer_commit(&fbuffer);				\
पूर्ण
/*
 * The ftrace_test_probe is compiled out, it is only here as a build समय check
 * to make sure that अगर the tracepoपूर्णांक handling changes, the ftrace probe will
 * fail to compile unless it too is updated.
 */

#अघोषित DEFINE_EVENT
#घोषणा DEFINE_EVENT(ढाँचा, call, proto, args)			\
अटल अंतरभूत व्योम ftrace_test_probe_##call(व्योम)			\
अणु									\
	check_trace_callback_type_##call(trace_event_raw_event_##ढाँचा); \
पूर्ण

#समावेश TRACE_INCLUDE(TRACE_INCLUDE_खाता)

#अघोषित __entry
#घोषणा __entry REC

#अघोषित __prपूर्णांक_flags
#अघोषित __prपूर्णांक_symbolic
#अघोषित __prपूर्णांक_hex
#अघोषित __prपूर्णांक_hex_str
#अघोषित __get_dynamic_array
#अघोषित __get_dynamic_array_len
#अघोषित __get_str
#अघोषित __get_biपंचांगask
#अघोषित __prपूर्णांक_array
#अघोषित __prपूर्णांक_hex_dump

#अघोषित TP_prपूर्णांकk
#घोषणा TP_prपूर्णांकk(fmt, args...) "\"" fmt "\", "  __stringअगरy(args)

#अघोषित DECLARE_EVENT_CLASS
#घोषणा DECLARE_EVENT_CLASS(call, proto, args, tकाष्ठा, assign, prपूर्णांक)	\
_TRACE_PERF_PROTO(call, PARAMS(proto));					\
अटल अक्षर prपूर्णांक_fmt_##call[] = prपूर्णांक;					\
अटल काष्ठा trace_event_class __used __refdata event_class_##call = अणु \
	.प्रणाली			= TRACE_SYSTEM_STRING,			\
	.fields_array		= trace_event_fields_##call,		\
	.fields			= LIST_HEAD_INIT(event_class_##call.fields),\
	.raw_init		= trace_event_raw_init,			\
	.probe			= trace_event_raw_event_##call,		\
	.reg			= trace_event_reg,			\
	_TRACE_PERF_INIT(call)						\
पूर्ण;

#अघोषित DEFINE_EVENT
#घोषणा DEFINE_EVENT(ढाँचा, call, proto, args)			\
									\
अटल काष्ठा trace_event_call __used event_##call = अणु			\
	.class			= &event_class_##ढाँचा,		\
	अणु								\
		.tp			= &__tracepoपूर्णांक_##call,		\
	पूर्ण,								\
	.event.funcs		= &trace_event_type_funcs_##ढाँचा,	\
	.prपूर्णांक_fmt		= prपूर्णांक_fmt_##ढाँचा,			\
	.flags			= TRACE_EVENT_FL_TRACEPOINT,		\
पूर्ण;									\
अटल काष्ठा trace_event_call __used					\
__section("_ftrace_events") *__event_##call = &event_##call

#अघोषित DEFINE_EVENT_PRINT
#घोषणा DEFINE_EVENT_PRINT(ढाँचा, call, proto, args, prपूर्णांक)		\
									\
अटल अक्षर prपूर्णांक_fmt_##call[] = prपूर्णांक;					\
									\
अटल काष्ठा trace_event_call __used event_##call = अणु			\
	.class			= &event_class_##ढाँचा,		\
	अणु								\
		.tp			= &__tracepoपूर्णांक_##call,		\
	पूर्ण,								\
	.event.funcs		= &trace_event_type_funcs_##call,	\
	.prपूर्णांक_fmt		= prपूर्णांक_fmt_##call,			\
	.flags			= TRACE_EVENT_FL_TRACEPOINT,		\
पूर्ण;									\
अटल काष्ठा trace_event_call __used					\
__section("_ftrace_events") *__event_##call = &event_##call

#समावेश TRACE_INCLUDE(TRACE_INCLUDE_खाता)
