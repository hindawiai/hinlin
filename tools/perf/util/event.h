<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_RECORD_H
#घोषणा __PERF_RECORD_H
/*
 * The linux/मानकघोष.स isn't need here, but is needed क्रम __always_अंतरभूत used
 * in files included from uapi/linux/perf_event.h such as
 * /usr/include/linux/swab.h and /usr/include/linux/byteorder/little_endian.h,
 * detected in at least musl libc, used in Alpine Linux. -acme
 */
#समावेश <मानकपन.स>
#समावेश <linux/मानकघोष.स>
#समावेश <perf/event.h>
#समावेश <linux/types.h>

#समावेश "perf_regs.h"

काष्ठा dso;
काष्ठा machine;
काष्ठा perf_event_attr;

#अगर_घोषित __LP64__
/*
 * /usr/include/पूर्णांकtypes.h uses just 'lu' क्रम PRIu64, but we end up defining
 * __u64 as दीर्घ दीर्घ अचिन्हित पूर्णांक, and then -Werror=क्रमmat= kicks in and
 * complains of the mismatched types, so use these two special extra PRI
 * macros to overcome that.
 */
#घोषणा PRI_lu64 "l" PRIu64
#घोषणा PRI_lx64 "l" PRIx64
#घोषणा PRI_ld64 "l" PRId64
#अन्यथा
#घोषणा PRI_lu64 PRIu64
#घोषणा PRI_lx64 PRIx64
#घोषणा PRI_ld64 PRId64
#पूर्ण_अगर

#घोषणा PERF_SAMPLE_MASK				\
	(PERF_SAMPLE_IP | PERF_SAMPLE_TID |		\
	 PERF_SAMPLE_TIME | PERF_SAMPLE_ADDR |		\
	PERF_SAMPLE_ID | PERF_SAMPLE_STREAM_ID |	\
	 PERF_SAMPLE_CPU | PERF_SAMPLE_PERIOD |		\
	 PERF_SAMPLE_IDENTIFIER)

/* perf sample has 16 bits size limit */
#घोषणा PERF_SAMPLE_MAX_SIZE (1 << 16)

काष्ठा regs_dump अणु
	u64 abi;
	u64 mask;
	u64 *regs;

	/* Cached values/mask filled by first रेजिस्टर access. */
	u64 cache_regs[PERF_REGS_MAX];
	u64 cache_mask;
पूर्ण;

काष्ठा stack_dump अणु
	u16 offset;
	u64 size;
	अक्षर *data;
पूर्ण;

काष्ठा sample_पढ़ो_value अणु
	u64 value;
	u64 id;
पूर्ण;

काष्ठा sample_पढ़ो अणु
	u64 समय_enabled;
	u64 समय_running;
	जोड़ अणु
		काष्ठा अणु
			u64 nr;
			काष्ठा sample_पढ़ो_value *values;
		पूर्ण group;
		काष्ठा sample_पढ़ो_value one;
	पूर्ण;
पूर्ण;

काष्ठा ip_callchain अणु
	u64 nr;
	u64 ips[];
पूर्ण;

काष्ठा branch_stack;

क्रमागत अणु
	PERF_IP_FLAG_BRANCH		= 1ULL << 0,
	PERF_IP_FLAG_CALL		= 1ULL << 1,
	PERF_IP_FLAG_RETURN		= 1ULL << 2,
	PERF_IP_FLAG_CONDITIONAL	= 1ULL << 3,
	PERF_IP_FLAG_SYSCALLRET		= 1ULL << 4,
	PERF_IP_FLAG_ASYNC		= 1ULL << 5,
	PERF_IP_FLAG_INTERRUPT		= 1ULL << 6,
	PERF_IP_FLAG_TX_ABORT		= 1ULL << 7,
	PERF_IP_FLAG_TRACE_BEGIN	= 1ULL << 8,
	PERF_IP_FLAG_TRACE_END		= 1ULL << 9,
	PERF_IP_FLAG_IN_TX		= 1ULL << 10,
	PERF_IP_FLAG_VMENTRY		= 1ULL << 11,
	PERF_IP_FLAG_VMEXIT		= 1ULL << 12,
पूर्ण;

#घोषणा PERF_IP_FLAG_CHARS "bcrosyiABExgh"

#घोषणा PERF_BRANCH_MASK		(\
	PERF_IP_FLAG_BRANCH		|\
	PERF_IP_FLAG_CALL		|\
	PERF_IP_FLAG_RETURN		|\
	PERF_IP_FLAG_CONDITIONAL	|\
	PERF_IP_FLAG_SYSCALLRET		|\
	PERF_IP_FLAG_ASYNC		|\
	PERF_IP_FLAG_INTERRUPT		|\
	PERF_IP_FLAG_TX_ABORT		|\
	PERF_IP_FLAG_TRACE_BEGIN	|\
	PERF_IP_FLAG_TRACE_END		|\
	PERF_IP_FLAG_VMENTRY		|\
	PERF_IP_FLAG_VMEXIT)

#घोषणा MAX_INSN 16

काष्ठा aux_sample अणु
	u64 size;
	व्योम *data;
पूर्ण;

काष्ठा perf_sample अणु
	u64 ip;
	u32 pid, tid;
	u64 समय;
	u64 addr;
	u64 id;
	u64 stream_id;
	u64 period;
	u64 weight;
	u64 transaction;
	u64 insn_cnt;
	u64 cyc_cnt;
	u32 cpu;
	u32 raw_size;
	u64 data_src;
	u64 phys_addr;
	u64 data_page_size;
	u64 code_page_size;
	u64 cgroup;
	u32 flags;
	u16 insn_len;
	u8  cpumode;
	u16 misc;
	u16 ins_lat;
	u16 p_stage_cyc;
	bool no_hw_idx;		/* No hw_idx collected in branch_stack */
	अक्षर insn[MAX_INSN];
	व्योम *raw_data;
	काष्ठा ip_callchain *callchain;
	काष्ठा branch_stack *branch_stack;
	काष्ठा regs_dump  user_regs;
	काष्ठा regs_dump  पूर्णांकr_regs;
	काष्ठा stack_dump user_stack;
	काष्ठा sample_पढ़ो पढ़ो;
	काष्ठा aux_sample aux_sample;
पूर्ण;

#घोषणा PERF_MEM_DATA_SRC_NONE \
	(PERF_MEM_S(OP, NA) |\
	 PERF_MEM_S(LVL, NA) |\
	 PERF_MEM_S(SNOOP, NA) |\
	 PERF_MEM_S(LOCK, NA) |\
	 PERF_MEM_S(TLB, NA))

/* Attribute type क्रम custom synthesized events */
#घोषणा PERF_TYPE_SYNTH		(पूर्णांक_उच्च + 1U)

/* Attribute config क्रम custom synthesized events */
क्रमागत perf_synth_id अणु
	PERF_SYNTH_INTEL_PTWRITE,
	PERF_SYNTH_INTEL_MWAIT,
	PERF_SYNTH_INTEL_PWRE,
	PERF_SYNTH_INTEL_EXSTOP,
	PERF_SYNTH_INTEL_PWRX,
	PERF_SYNTH_INTEL_CBR,
	PERF_SYNTH_INTEL_PSB,
पूर्ण;

/*
 * Raw data क्रमmats क्रम synthesized events. Note that 4 bytes of padding are
 * present to match the 'size' member of PERF_SAMPLE_RAW data which is always
 * 8-byte aligned. That means we must dereference raw_data with an offset of 4.
 * Refer perf_sample__synth_ptr() and perf_synth__raw_data().  It also means the
 * काष्ठाure sizes are 4 bytes bigger than the raw_size, refer
 * perf_synth__raw_size().
 */

काष्ठा perf_synth_पूर्णांकel_ptग_लिखो अणु
	u32 padding;
	जोड़ अणु
		काष्ठा अणु
			u32	ip		:  1,
				reserved	: 31;
		पूर्ण;
		u32	flags;
	पूर्ण;
	u64	payload;
पूर्ण;

काष्ठा perf_synth_पूर्णांकel_mरुको अणु
	u32 padding;
	u32 reserved;
	जोड़ अणु
		काष्ठा अणु
			u64	hपूर्णांकs		:  8,
				reserved1	: 24,
				extensions	:  2,
				reserved2	: 30;
		पूर्ण;
		u64	payload;
	पूर्ण;
पूर्ण;

काष्ठा perf_synth_पूर्णांकel_pwre अणु
	u32 padding;
	u32 reserved;
	जोड़ अणु
		काष्ठा अणु
			u64	reserved1	:  7,
				hw		:  1,
				subcstate	:  4,
				cstate		:  4,
				reserved2	: 48;
		पूर्ण;
		u64	payload;
	पूर्ण;
पूर्ण;

काष्ठा perf_synth_पूर्णांकel_exstop अणु
	u32 padding;
	जोड़ अणु
		काष्ठा अणु
			u32	ip		:  1,
				reserved	: 31;
		पूर्ण;
		u32	flags;
	पूर्ण;
पूर्ण;

काष्ठा perf_synth_पूर्णांकel_pwrx अणु
	u32 padding;
	u32 reserved;
	जोड़ अणु
		काष्ठा अणु
			u64	deepest_cstate	:  4,
				last_cstate	:  4,
				wake_reason	:  4,
				reserved1	: 52;
		पूर्ण;
		u64	payload;
	पूर्ण;
पूर्ण;

काष्ठा perf_synth_पूर्णांकel_cbr अणु
	u32 padding;
	जोड़ अणु
		काष्ठा अणु
			u32	cbr		:  8,
				reserved1	:  8,
				max_nonturbo	:  8,
				reserved2	:  8;
		पूर्ण;
		u32	flags;
	पूर्ण;
	u32 freq;
	u32 reserved3;
पूर्ण;

काष्ठा perf_synth_पूर्णांकel_psb अणु
	u32 padding;
	u32 reserved;
	u64 offset;
पूर्ण;

/*
 * raw_data is always 4 bytes from an 8-byte boundary, so subtract 4 to get
 * 8-byte alignment.
 */
अटल अंतरभूत व्योम *perf_sample__synth_ptr(काष्ठा perf_sample *sample)
अणु
	वापस sample->raw_data - 4;
पूर्ण

अटल अंतरभूत व्योम *perf_synth__raw_data(व्योम *p)
अणु
	वापस p + 4;
पूर्ण

#घोषणा perf_synth__raw_size(d) (माप(d) - 4)

#घोषणा perf_sample__bad_synth_size(s, d) ((s)->raw_size < माप(d) - 4)

क्रमागत अणु
	PERF_STAT_ROUND_TYPE__INTERVAL	= 0,
	PERF_STAT_ROUND_TYPE__FINAL	= 1,
पूर्ण;

व्योम perf_event__prपूर्णांक_totals(व्योम);

काष्ठा perf_cpu_map;
काष्ठा perf_record_stat_config;
काष्ठा perf_stat_config;
काष्ठा perf_tool;

व्योम perf_event__पढ़ो_stat_config(काष्ठा perf_stat_config *config,
				  काष्ठा perf_record_stat_config *event);

पूर्णांक perf_event__process_comm(काष्ठा perf_tool *tool,
			     जोड़ perf_event *event,
			     काष्ठा perf_sample *sample,
			     काष्ठा machine *machine);
पूर्णांक perf_event__process_lost(काष्ठा perf_tool *tool,
			     जोड़ perf_event *event,
			     काष्ठा perf_sample *sample,
			     काष्ठा machine *machine);
पूर्णांक perf_event__process_lost_samples(काष्ठा perf_tool *tool,
				     जोड़ perf_event *event,
				     काष्ठा perf_sample *sample,
				     काष्ठा machine *machine);
पूर्णांक perf_event__process_aux(काष्ठा perf_tool *tool,
			    जोड़ perf_event *event,
			    काष्ठा perf_sample *sample,
			    काष्ठा machine *machine);
पूर्णांक perf_event__process_itrace_start(काष्ठा perf_tool *tool,
				     जोड़ perf_event *event,
				     काष्ठा perf_sample *sample,
				     काष्ठा machine *machine);
पूर्णांक perf_event__process_चयन(काष्ठा perf_tool *tool,
			       जोड़ perf_event *event,
			       काष्ठा perf_sample *sample,
			       काष्ठा machine *machine);
पूर्णांक perf_event__process_namespaces(काष्ठा perf_tool *tool,
				   जोड़ perf_event *event,
				   काष्ठा perf_sample *sample,
				   काष्ठा machine *machine);
पूर्णांक perf_event__process_cgroup(काष्ठा perf_tool *tool,
			       जोड़ perf_event *event,
			       काष्ठा perf_sample *sample,
			       काष्ठा machine *machine);
पूर्णांक perf_event__process_mmap(काष्ठा perf_tool *tool,
			     जोड़ perf_event *event,
			     काष्ठा perf_sample *sample,
			     काष्ठा machine *machine);
पूर्णांक perf_event__process_mmap2(काष्ठा perf_tool *tool,
			     जोड़ perf_event *event,
			     काष्ठा perf_sample *sample,
			     काष्ठा machine *machine);
पूर्णांक perf_event__process_विभाजन(काष्ठा perf_tool *tool,
			     जोड़ perf_event *event,
			     काष्ठा perf_sample *sample,
			     काष्ठा machine *machine);
पूर्णांक perf_event__process_निकास(काष्ठा perf_tool *tool,
			     जोड़ perf_event *event,
			     काष्ठा perf_sample *sample,
			     काष्ठा machine *machine);
पूर्णांक perf_event__process_ksymbol(काष्ठा perf_tool *tool,
				जोड़ perf_event *event,
				काष्ठा perf_sample *sample,
				काष्ठा machine *machine);
पूर्णांक perf_event__process_bpf(काष्ठा perf_tool *tool,
			    जोड़ perf_event *event,
			    काष्ठा perf_sample *sample,
			    काष्ठा machine *machine);
पूर्णांक perf_event__process_text_poke(काष्ठा perf_tool *tool,
				  जोड़ perf_event *event,
				  काष्ठा perf_sample *sample,
				  काष्ठा machine *machine);
पूर्णांक perf_event__process(काष्ठा perf_tool *tool,
			जोड़ perf_event *event,
			काष्ठा perf_sample *sample,
			काष्ठा machine *machine);

काष्ठा addr_location;

पूर्णांक machine__resolve(काष्ठा machine *machine, काष्ठा addr_location *al,
		     काष्ठा perf_sample *sample);

व्योम addr_location__put(काष्ठा addr_location *al);

काष्ठा thपढ़ो;

bool is_bts_event(काष्ठा perf_event_attr *attr);
bool sample_addr_correlates_sym(काष्ठा perf_event_attr *attr);
व्योम thपढ़ो__resolve(काष्ठा thपढ़ो *thपढ़ो, काष्ठा addr_location *al,
		     काष्ठा perf_sample *sample);

स्थिर अक्षर *perf_event__name(अचिन्हित पूर्णांक id);

माप_प्रकार perf_event__ख_लिखो_comm(जोड़ perf_event *event, खाता *fp);
माप_प्रकार perf_event__ख_लिखो_mmap(जोड़ perf_event *event, खाता *fp);
माप_प्रकार perf_event__ख_लिखो_mmap2(जोड़ perf_event *event, खाता *fp);
माप_प्रकार perf_event__ख_लिखो_task(जोड़ perf_event *event, खाता *fp);
माप_प्रकार perf_event__ख_लिखो_aux(जोड़ perf_event *event, खाता *fp);
माप_प्रकार perf_event__ख_लिखो_itrace_start(जोड़ perf_event *event, खाता *fp);
माप_प्रकार perf_event__ख_लिखो_चयन(जोड़ perf_event *event, खाता *fp);
माप_प्रकार perf_event__ख_लिखो_thपढ़ो_map(जोड़ perf_event *event, खाता *fp);
माप_प्रकार perf_event__ख_लिखो_cpu_map(जोड़ perf_event *event, खाता *fp);
माप_प्रकार perf_event__ख_लिखो_namespaces(जोड़ perf_event *event, खाता *fp);
माप_प्रकार perf_event__ख_लिखो_cgroup(जोड़ perf_event *event, खाता *fp);
माप_प्रकार perf_event__ख_लिखो_ksymbol(जोड़ perf_event *event, खाता *fp);
माप_प्रकार perf_event__ख_लिखो_bpf(जोड़ perf_event *event, खाता *fp);
माप_प्रकार perf_event__ख_लिखो_text_poke(जोड़ perf_event *event, काष्ठा machine *machine,खाता *fp);
माप_प्रकार perf_event__ख_लिखो(जोड़ perf_event *event, काष्ठा machine *machine, खाता *fp);

पूर्णांक kallsyms__get_function_start(स्थिर अक्षर *kallsyms_filename,
				 स्थिर अक्षर *symbol_name, u64 *addr);

व्योम *cpu_map_data__alloc(काष्ठा perf_cpu_map *map, माप_प्रकार *size, u16 *type, पूर्णांक *max);
व्योम  cpu_map_data__synthesize(काष्ठा perf_record_cpu_map_data *data, काष्ठा perf_cpu_map *map,
			       u16 type, पूर्णांक max);

व्योम event_attr_init(काष्ठा perf_event_attr *attr);

पूर्णांक perf_event_paranoid(व्योम);
bool perf_event_paranoid_check(पूर्णांक max_level);

बाह्य पूर्णांक sysctl_perf_event_max_stack;
बाह्य पूर्णांक sysctl_perf_event_max_contexts_per_stack;
बाह्य अचिन्हित पूर्णांक proc_map_समयout;

#घोषणा PAGE_SIZE_NAME_LEN	32
अक्षर *get_page_size_name(u64 size, अक्षर *str);

व्योम arch_perf_parse_sample_weight(काष्ठा perf_sample *data, स्थिर __u64 *array, u64 type);
व्योम arch_perf_synthesize_sample_weight(स्थिर काष्ठा perf_sample *data, __u64 *array, u64 type);
स्थिर अक्षर *arch_perf_header_entry(स्थिर अक्षर *se_header);
पूर्णांक arch_support_sort_key(स्थिर अक्षर *sort_key);

#पूर्ण_अगर /* __PERF_RECORD_H */
