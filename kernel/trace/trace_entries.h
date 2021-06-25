<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file defines the trace event काष्ठाures that go पूर्णांकo the ring
 * buffer directly. They are created via macros so that changes क्रम them
 * appear in the क्रमmat file. Using macros will स्वतःmate this process.
 *
 * The macro used to create a ftrace data काष्ठाure is:
 *
 * FTRACE_ENTRY( name, काष्ठा_name, id, काष्ठाure, prपूर्णांक )
 *
 * @name: the name used the event name, as well as the name of
 *   the directory that holds the क्रमmat file.
 *
 * @काष्ठा_name: the name of the काष्ठाure that is created.
 *
 * @id: The event identअगरier that is used to detect what event
 *    this is from the ring buffer.
 *
 * @काष्ठाure: the काष्ठाure layout
 *
 *  - __field(	type,	item	)
 *	  This is equivalent to declaring
 *		type	item;
 *	  in the काष्ठाure.
 *  - __array(	type,	item,	size	)
 *	  This is equivalent to declaring
 *		type	item[size];
 *	  in the काष्ठाure.
 *
 *   * क्रम काष्ठाures within काष्ठाures, the क्रमmat of the पूर्णांकernal
 *	काष्ठाure is laid out. This allows the पूर्णांकernal काष्ठाure
 *	to be deciphered क्रम the क्रमmat file. Although these macros
 *	may become out of sync with the पूर्णांकernal काष्ठाure, they
 *	will create a compile error अगर it happens. Since the
 *	पूर्णांकernal काष्ठाures are just tracing helpers, this is not
 *	an issue.
 *
 *	When an पूर्णांकernal काष्ठाure is used, it should use:
 *
 *	__field_काष्ठा(	type,	item	)
 *
 *	instead of __field. This will prevent it from being shown in
 *	the output file. The fields in the काष्ठाure should use.
 *
 *	__field_desc(	type,	container,	item		)
 *	__array_desc(	type,	container,	item,	len	)
 *
 *	type, item and len are the same as __field and __array, but
 *	container is added. This is the name of the item in
 *	__field_काष्ठा that this is describing.
 *
 *
 * @prपूर्णांक: the prपूर्णांक क्रमmat shown to users in the क्रमmat file.
 */

/*
 * Function trace entry - function address and parent function address:
 */
FTRACE_ENTRY_REG(function, ftrace_entry,

	TRACE_FN,

	F_STRUCT(
		__field_fn(	अचिन्हित दीर्घ,	ip		)
		__field_fn(	अचिन्हित दीर्घ,	parent_ip	)
	),

	F_prपूर्णांकk(" %ps <-- %ps",
		 (व्योम *)__entry->ip, (व्योम *)__entry->parent_ip),

	perf_ftrace_event_रेजिस्टर
);

/* Function call entry */
FTRACE_ENTRY_PACKED(funcgraph_entry, ftrace_graph_ent_entry,

	TRACE_GRAPH_ENT,

	F_STRUCT(
		__field_काष्ठा(	काष्ठा ftrace_graph_ent,	graph_ent	)
		__field_packed(	अचिन्हित दीर्घ,	graph_ent,	func		)
		__field_packed(	पूर्णांक,		graph_ent,	depth		)
	),

	F_prपूर्णांकk("--> %ps (%d)", (व्योम *)__entry->func, __entry->depth)
);

/* Function वापस entry */
FTRACE_ENTRY_PACKED(funcgraph_निकास, ftrace_graph_ret_entry,

	TRACE_GRAPH_RET,

	F_STRUCT(
		__field_काष्ठा(	काष्ठा ftrace_graph_ret,	ret	)
		__field_packed(	अचिन्हित दीर्घ,	ret,		func	)
		__field_packed(	पूर्णांक,		ret,		depth	)
		__field_packed(	अचिन्हित पूर्णांक,	ret,		overrun	)
		__field_packed(	अचिन्हित दीर्घ दीर्घ, ret,	callसमय)
		__field_packed(	अचिन्हित दीर्घ दीर्घ, ret,	retसमय	)
	),

	F_prपूर्णांकk("<-- %ps (%d) (start: %llx  end: %llx) over: %d",
		 (व्योम *)__entry->func, __entry->depth,
		 __entry->callसमय, __entry->retसमय,
		 __entry->depth)
);

/*
 * Context चयन trace entry - which task (and prio) we चयनed from/to:
 *
 * This is used क्रम both wakeup and context चयनes. We only want
 * to create one काष्ठाure, but we need two outमाला_दो क्रम it.
 */
#घोषणा FTRACE_CTX_FIELDS					\
	__field(	अचिन्हित पूर्णांक,	prev_pid	)	\
	__field(	अचिन्हित पूर्णांक,	next_pid	)	\
	__field(	अचिन्हित पूर्णांक,	next_cpu	)       \
	__field(	अचिन्हित अक्षर,	prev_prio	)	\
	__field(	अचिन्हित अक्षर,	prev_state	)	\
	__field(	अचिन्हित अक्षर,	next_prio	)	\
	__field(	अचिन्हित अक्षर,	next_state	)

FTRACE_ENTRY(context_चयन, ctx_चयन_entry,

	TRACE_CTX,

	F_STRUCT(
		FTRACE_CTX_FIELDS
	),

	F_prपूर्णांकk("%u:%u:%u  ==> %u:%u:%u [%03u]",
		 __entry->prev_pid, __entry->prev_prio, __entry->prev_state,
		 __entry->next_pid, __entry->next_prio, __entry->next_state,
		 __entry->next_cpu)
);

/*
 * FTRACE_ENTRY_DUP only creates the क्रमmat file, it will not
 *  create another काष्ठाure.
 */
FTRACE_ENTRY_DUP(wakeup, ctx_चयन_entry,

	TRACE_WAKE,

	F_STRUCT(
		FTRACE_CTX_FIELDS
	),

	F_prपूर्णांकk("%u:%u:%u  ==+ %u:%u:%u [%03u]",
		 __entry->prev_pid, __entry->prev_prio, __entry->prev_state,
		 __entry->next_pid, __entry->next_prio, __entry->next_state,
		 __entry->next_cpu)
);

/*
 * Stack-trace entry:
 */

#घोषणा FTRACE_STACK_ENTRIES	8

FTRACE_ENTRY(kernel_stack, stack_entry,

	TRACE_STACK,

	F_STRUCT(
		__field(	पूर्णांक,		size	)
		__array(	अचिन्हित दीर्घ,	caller,	FTRACE_STACK_ENTRIES	)
	),

	F_prपूर्णांकk("\t=> %ps\n\t=> %ps\n\t=> %ps\n"
		 "\t=> %ps\n\t=> %ps\n\t=> %ps\n"
		 "\t=> %ps\n\t=> %ps\n",
		 (व्योम *)__entry->caller[0], (व्योम *)__entry->caller[1],
		 (व्योम *)__entry->caller[2], (व्योम *)__entry->caller[3],
		 (व्योम *)__entry->caller[4], (व्योम *)__entry->caller[5],
		 (व्योम *)__entry->caller[6], (व्योम *)__entry->caller[7])
);

FTRACE_ENTRY(user_stack, userstack_entry,

	TRACE_USER_STACK,

	F_STRUCT(
		__field(	अचिन्हित पूर्णांक,	tgid	)
		__array(	अचिन्हित दीर्घ,	caller, FTRACE_STACK_ENTRIES	)
	),

	F_prपूर्णांकk("\t=> %ps\n\t=> %ps\n\t=> %ps\n"
		 "\t=> %ps\n\t=> %ps\n\t=> %ps\n"
		 "\t=> %ps\n\t=> %ps\n",
		 (व्योम *)__entry->caller[0], (व्योम *)__entry->caller[1],
		 (व्योम *)__entry->caller[2], (व्योम *)__entry->caller[3],
		 (व्योम *)__entry->caller[4], (व्योम *)__entry->caller[5],
		 (व्योम *)__entry->caller[6], (व्योम *)__entry->caller[7])
);

/*
 * trace_prपूर्णांकk entry:
 */
FTRACE_ENTRY(bprपूर्णांक, bprपूर्णांक_entry,

	TRACE_BPRINT,

	F_STRUCT(
		__field(	अचिन्हित दीर्घ,	ip	)
		__field(	स्थिर अक्षर *,	fmt	)
		__dynamic_array(	u32,	buf	)
	),

	F_prपूर्णांकk("%ps: %s",
		 (व्योम *)__entry->ip, __entry->fmt)
);

FTRACE_ENTRY_REG(prपूर्णांक, prपूर्णांक_entry,

	TRACE_PRINT,

	F_STRUCT(
		__field(	अचिन्हित दीर्घ,	ip	)
		__dynamic_array(	अक्षर,	buf	)
	),

	F_prपूर्णांकk("%ps: %s",
		 (व्योम *)__entry->ip, __entry->buf),

	ftrace_event_रेजिस्टर
);

FTRACE_ENTRY(raw_data, raw_data_entry,

	TRACE_RAW_DATA,

	F_STRUCT(
		__field(	अचिन्हित पूर्णांक,	id	)
		__dynamic_array(	अक्षर,	buf	)
	),

	F_prपूर्णांकk("id:%04x %08x",
		 __entry->id, (पूर्णांक)__entry->buf[0])
);

FTRACE_ENTRY(bमाला_दो, bमाला_दो_entry,

	TRACE_BPUTS,

	F_STRUCT(
		__field(	अचिन्हित दीर्घ,	ip	)
		__field(	स्थिर अक्षर *,	str	)
	),

	F_prपूर्णांकk("%ps: %s",
		 (व्योम *)__entry->ip, __entry->str)
);

FTRACE_ENTRY(mmiotrace_rw, trace_mmiotrace_rw,

	TRACE_MMIO_RW,

	F_STRUCT(
		__field_काष्ठा(	काष्ठा mmiotrace_rw,	rw	)
		__field_desc(	resource_माप_प्रकार, rw,	phys	)
		__field_desc(	अचिन्हित दीर्घ,	rw,	value	)
		__field_desc(	अचिन्हित दीर्घ,	rw,	pc	)
		__field_desc(	पूर्णांक,		rw,	map_id	)
		__field_desc(	अचिन्हित अक्षर,	rw,	opcode	)
		__field_desc(	अचिन्हित अक्षर,	rw,	width	)
	),

	F_prपूर्णांकk("%lx %lx %lx %d %x %x",
		 (अचिन्हित दीर्घ)__entry->phys, __entry->value, __entry->pc,
		 __entry->map_id, __entry->opcode, __entry->width)
);

FTRACE_ENTRY(mmiotrace_map, trace_mmiotrace_map,

	TRACE_MMIO_MAP,

	F_STRUCT(
		__field_काष्ठा(	काष्ठा mmiotrace_map,	map	)
		__field_desc(	resource_माप_प्रकार, map,	phys	)
		__field_desc(	अचिन्हित दीर्घ,	map,	virt	)
		__field_desc(	अचिन्हित दीर्घ,	map,	len	)
		__field_desc(	पूर्णांक,		map,	map_id	)
		__field_desc(	अचिन्हित अक्षर,	map,	opcode	)
	),

	F_prपूर्णांकk("%lx %lx %lx %d %x",
		 (अचिन्हित दीर्घ)__entry->phys, __entry->virt, __entry->len,
		 __entry->map_id, __entry->opcode)
);


#घोषणा TRACE_FUNC_SIZE 30
#घोषणा TRACE_खाता_SIZE 20

FTRACE_ENTRY(branch, trace_branch,

	TRACE_BRANCH,

	F_STRUCT(
		__field(	अचिन्हित पूर्णांक,	line				)
		__array(	अक्षर,		func,	TRACE_FUNC_SIZE+1	)
		__array(	अक्षर,		file,	TRACE_खाता_SIZE+1	)
		__field(	अक्षर,		correct				)
		__field(	अक्षर,		स्थिरant			)
	),

	F_prपूर्णांकk("%u:%s:%s (%u)%s",
		 __entry->line,
		 __entry->func, __entry->file, __entry->correct,
		 __entry->स्थिरant ? " CONSTANT" : "")
);


FTRACE_ENTRY(hwlat, hwlat_entry,

	TRACE_HWLAT,

	F_STRUCT(
		__field(	u64,			duration	)
		__field(	u64,			outer_duration	)
		__field(	u64,			nmi_total_ts	)
		__field_काष्ठा( काष्ठा बारpec64,	बारtamp	)
		__field_desc(	s64,	बारtamp,	tv_sec		)
		__field_desc(	दीर्घ,	बारtamp,	tv_nsec		)
		__field(	अचिन्हित पूर्णांक,		nmi_count	)
		__field(	अचिन्हित पूर्णांक,		seqnum		)
		__field(	अचिन्हित पूर्णांक,		count		)
	),

	F_prपूर्णांकk("cnt:%u\tts:%010llu.%010lu\tinner:%llu\touter:%llu\tcount:%d\tnmi-ts:%llu\tnmi-count:%u\n",
		 __entry->seqnum,
		 __entry->tv_sec,
		 __entry->tv_nsec,
		 __entry->duration,
		 __entry->outer_duration,
		 __entry->count,
		 __entry->nmi_total_ts,
		 __entry->nmi_count)
);

#घोषणा FUNC_REPEATS_GET_DELTA_TS(entry)				\
	(((u64)(entry)->top_delta_ts << 32) | (entry)->bottom_delta_ts)	\

FTRACE_ENTRY(func_repeats, func_repeats_entry,

	TRACE_FUNC_REPEATS,

	F_STRUCT(
		__field(	अचिन्हित दीर्घ,	ip		)
		__field(	अचिन्हित दीर्घ,	parent_ip	)
		__field(	u16	,	count		)
		__field(	u16	,	top_delta_ts	)
		__field(	u32	,	bottom_delta_ts	)
	),

	F_prपूर्णांकk(" %ps <-%ps\t(repeats:%u  delta: -%llu)",
		 (व्योम *)__entry->ip,
		 (व्योम *)__entry->parent_ip,
		 __entry->count,
		 FUNC_REPEATS_GET_DELTA_TS(__entry))
);
