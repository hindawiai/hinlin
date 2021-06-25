<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LIBPERF_EVENT_H
#घोषणा __LIBPERF_EVENT_H

#समावेश <linux/perf_event.h>
#समावेश <linux/types.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/bpf.h>
#समावेश <sys/types.h> /* pid_t */

#घोषणा event_contains(obj, mem) ((obj).header.size > दुरत्व(typeof(obj), mem))

काष्ठा perf_record_mmap अणु
	काष्ठा perf_event_header header;
	__u32			 pid, tid;
	__u64			 start;
	__u64			 len;
	__u64			 pgoff;
	अक्षर			 filename[PATH_MAX];
पूर्ण;

काष्ठा perf_record_mmap2 अणु
	काष्ठा perf_event_header header;
	__u32			 pid, tid;
	__u64			 start;
	__u64			 len;
	__u64			 pgoff;
	जोड़ अणु
		काष्ठा अणु
			__u32	 maj;
			__u32	 min;
			__u64	 ino;
			__u64	 ino_generation;
		पूर्ण;
		काष्ठा अणु
			__u8	 build_id_size;
			__u8	 __reserved_1;
			__u16	 __reserved_2;
			__u8	 build_id[20];
		पूर्ण;
	पूर्ण;
	__u32			 prot;
	__u32			 flags;
	अक्षर			 filename[PATH_MAX];
पूर्ण;

काष्ठा perf_record_comm अणु
	काष्ठा perf_event_header header;
	__u32			 pid, tid;
	अक्षर			 comm[16];
पूर्ण;

काष्ठा perf_record_namespaces अणु
	काष्ठा perf_event_header header;
	__u32			 pid, tid;
	__u64			 nr_namespaces;
	काष्ठा perf_ns_link_info link_info[];
पूर्ण;

काष्ठा perf_record_विभाजन अणु
	काष्ठा perf_event_header header;
	__u32			 pid, ppid;
	__u32			 tid, ptid;
	__u64			 समय;
पूर्ण;

काष्ठा perf_record_lost अणु
	काष्ठा perf_event_header header;
	__u64			 id;
	__u64			 lost;
पूर्ण;

काष्ठा perf_record_lost_samples अणु
	काष्ठा perf_event_header header;
	__u64			 lost;
पूर्ण;

/*
 * PERF_FORMAT_ENABLED | PERF_FORMAT_RUNNING | PERF_FORMAT_ID
 */
काष्ठा perf_record_पढ़ो अणु
	काष्ठा perf_event_header header;
	__u32			 pid, tid;
	__u64			 value;
	__u64			 समय_enabled;
	__u64			 समय_running;
	__u64			 id;
पूर्ण;

काष्ठा perf_record_throttle अणु
	काष्ठा perf_event_header header;
	__u64			 समय;
	__u64			 id;
	__u64			 stream_id;
पूर्ण;

#अगर_अघोषित KSYM_NAME_LEN
#घोषणा KSYM_NAME_LEN 256
#पूर्ण_अगर

काष्ठा perf_record_ksymbol अणु
	काष्ठा perf_event_header header;
	__u64			 addr;
	__u32			 len;
	__u16			 ksym_type;
	__u16			 flags;
	अक्षर			 name[KSYM_NAME_LEN];
पूर्ण;

काष्ठा perf_record_bpf_event अणु
	काष्ठा perf_event_header header;
	__u16			 type;
	__u16			 flags;
	__u32			 id;

	/* क्रम bpf_prog types */
	__u8			 tag[BPF_TAG_SIZE];  // prog tag
पूर्ण;

काष्ठा perf_record_cgroup अणु
	काष्ठा perf_event_header header;
	__u64			 id;
	अक्षर			 path[PATH_MAX];
पूर्ण;

काष्ठा perf_record_text_poke_event अणु
	काष्ठा perf_event_header header;
	__u64			addr;
	__u16			old_len;
	__u16			new_len;
	__u8			bytes[];
पूर्ण;

काष्ठा perf_record_sample अणु
	काष्ठा perf_event_header header;
	__u64			 array[];
पूर्ण;

काष्ठा perf_record_चयन अणु
	काष्ठा perf_event_header header;
	__u32			 next_prev_pid;
	__u32			 next_prev_tid;
पूर्ण;

काष्ठा perf_record_header_attr अणु
	काष्ठा perf_event_header header;
	काष्ठा perf_event_attr	 attr;
	__u64			 id[];
पूर्ण;

क्रमागत अणु
	PERF_CPU_MAP__CPUS = 0,
	PERF_CPU_MAP__MASK = 1,
पूर्ण;

काष्ठा cpu_map_entries अणु
	__u16			 nr;
	__u16			 cpu[];
पूर्ण;

काष्ठा perf_record_record_cpu_map अणु
	__u16			 nr;
	__u16			 दीर्घ_size;
	अचिन्हित दीर्घ		 mask[];
पूर्ण;

काष्ठा perf_record_cpu_map_data अणु
	__u16			 type;
	अक्षर			 data[];
पूर्ण;

काष्ठा perf_record_cpu_map अणु
	काष्ठा perf_event_header	 header;
	काष्ठा perf_record_cpu_map_data	 data;
पूर्ण;

क्रमागत अणु
	PERF_EVENT_UPDATE__UNIT  = 0,
	PERF_EVENT_UPDATE__SCALE = 1,
	PERF_EVENT_UPDATE__NAME  = 2,
	PERF_EVENT_UPDATE__CPUS  = 3,
पूर्ण;

काष्ठा perf_record_event_update_cpus अणु
	काष्ठा perf_record_cpu_map_data	 cpus;
पूर्ण;

काष्ठा perf_record_event_update_scale अणु
	द्विगुन			 scale;
पूर्ण;

काष्ठा perf_record_event_update अणु
	काष्ठा perf_event_header header;
	__u64			 type;
	__u64			 id;
	अक्षर			 data[];
पूर्ण;

#घोषणा MAX_EVENT_NAME 64

काष्ठा perf_trace_event_type अणु
	__u64			 event_id;
	अक्षर			 name[MAX_EVENT_NAME];
पूर्ण;

काष्ठा perf_record_header_event_type अणु
	काष्ठा perf_event_header	 header;
	काष्ठा perf_trace_event_type	 event_type;
पूर्ण;

काष्ठा perf_record_header_tracing_data अणु
	काष्ठा perf_event_header header;
	__u32			 size;
पूर्ण;

#घोषणा PERF_RECORD_MISC_BUILD_ID_SIZE (1 << 15)

काष्ठा perf_record_header_build_id अणु
	काष्ठा perf_event_header header;
	pid_t			 pid;
	जोड़ अणु
		__u8		 build_id[24];
		काष्ठा अणु
			__u8	 data[20];
			__u8	 size;
			__u8	 reserved1__;
			__u16	 reserved2__;
		पूर्ण;
	पूर्ण;
	अक्षर			 filename[];
पूर्ण;

काष्ठा id_index_entry अणु
	__u64			 id;
	__u64			 idx;
	__u64			 cpu;
	__u64			 tid;
पूर्ण;

काष्ठा perf_record_id_index अणु
	काष्ठा perf_event_header header;
	__u64			 nr;
	काष्ठा id_index_entry	 entries[0];
पूर्ण;

काष्ठा perf_record_auxtrace_info अणु
	काष्ठा perf_event_header header;
	__u32			 type;
	__u32			 reserved__; /* For alignment */
	__u64			 priv[];
पूर्ण;

काष्ठा perf_record_auxtrace अणु
	काष्ठा perf_event_header header;
	__u64			 size;
	__u64			 offset;
	__u64			 reference;
	__u32			 idx;
	__u32			 tid;
	__u32			 cpu;
	__u32			 reserved__; /* For alignment */
पूर्ण;

#घोषणा MAX_AUXTRACE_ERROR_MSG 64

काष्ठा perf_record_auxtrace_error अणु
	काष्ठा perf_event_header header;
	__u32			 type;
	__u32			 code;
	__u32			 cpu;
	__u32			 pid;
	__u32			 tid;
	__u32			 fmt;
	__u64			 ip;
	__u64			 समय;
	अक्षर			 msg[MAX_AUXTRACE_ERROR_MSG];
पूर्ण;

काष्ठा perf_record_aux अणु
	काष्ठा perf_event_header header;
	__u64			 aux_offset;
	__u64			 aux_size;
	__u64			 flags;
पूर्ण;

काष्ठा perf_record_itrace_start अणु
	काष्ठा perf_event_header header;
	__u32			 pid;
	__u32			 tid;
पूर्ण;

काष्ठा perf_record_thपढ़ो_map_entry अणु
	__u64			 pid;
	अक्षर			 comm[16];
पूर्ण;

काष्ठा perf_record_thपढ़ो_map अणु
	काष्ठा perf_event_header		 header;
	__u64					 nr;
	काष्ठा perf_record_thपढ़ो_map_entry	 entries[];
पूर्ण;

क्रमागत अणु
	PERF_STAT_CONFIG_TERM__AGGR_MODE	= 0,
	PERF_STAT_CONFIG_TERM__INTERVAL		= 1,
	PERF_STAT_CONFIG_TERM__SCALE		= 2,
	PERF_STAT_CONFIG_TERM__MAX		= 3,
पूर्ण;

काष्ठा perf_record_stat_config_entry अणु
	__u64			 tag;
	__u64			 val;
पूर्ण;

काष्ठा perf_record_stat_config अणु
	काष्ठा perf_event_header		 header;
	__u64					 nr;
	काष्ठा perf_record_stat_config_entry	 data[];
पूर्ण;

काष्ठा perf_record_stat अणु
	काष्ठा perf_event_header header;

	__u64			 id;
	__u32			 cpu;
	__u32			 thपढ़ो;

	जोड़ अणु
		काष्ठा अणु
			__u64	 val;
			__u64	 ena;
			__u64	 run;
		पूर्ण;
		__u64		 values[3];
	पूर्ण;
पूर्ण;

काष्ठा perf_record_stat_round अणु
	काष्ठा perf_event_header header;
	__u64			 type;
	__u64			 समय;
पूर्ण;

काष्ठा perf_record_समय_conv अणु
	काष्ठा perf_event_header header;
	__u64			 समय_shअगरt;
	__u64			 समय_mult;
	__u64			 समय_zero;
	__u64			 समय_cycles;
	__u64			 समय_mask;
	__u8			 cap_user_समय_zero;
	__u8			 cap_user_समय_लघु;
	__u8			 reserved[6];	/* For alignment */
पूर्ण;

काष्ठा perf_record_header_feature अणु
	काष्ठा perf_event_header header;
	__u64			 feat_id;
	अक्षर			 data[];
पूर्ण;

काष्ठा perf_record_compressed अणु
	काष्ठा perf_event_header header;
	अक्षर			 data[];
पूर्ण;

क्रमागत perf_user_event_type अणु /* above any possible kernel type */
	PERF_RECORD_USER_TYPE_START		= 64,
	PERF_RECORD_HEADER_ATTR			= 64,
	PERF_RECORD_HEADER_EVENT_TYPE		= 65, /* deprecated */
	PERF_RECORD_HEADER_TRACING_DATA		= 66,
	PERF_RECORD_HEADER_BUILD_ID		= 67,
	PERF_RECORD_FINISHED_ROUND		= 68,
	PERF_RECORD_ID_INDEX			= 69,
	PERF_RECORD_AUXTRACE_INFO		= 70,
	PERF_RECORD_AUXTRACE			= 71,
	PERF_RECORD_AUXTRACE_ERROR		= 72,
	PERF_RECORD_THREAD_MAP			= 73,
	PERF_RECORD_CPU_MAP			= 74,
	PERF_RECORD_STAT_CONFIG			= 75,
	PERF_RECORD_STAT			= 76,
	PERF_RECORD_STAT_ROUND			= 77,
	PERF_RECORD_EVENT_UPDATE		= 78,
	PERF_RECORD_TIME_CONV			= 79,
	PERF_RECORD_HEADER_FEATURE		= 80,
	PERF_RECORD_COMPRESSED			= 81,
	PERF_RECORD_HEADER_MAX
पूर्ण;

जोड़ perf_event अणु
	काष्ठा perf_event_header		header;
	काष्ठा perf_record_mmap			mmap;
	काष्ठा perf_record_mmap2		mmap2;
	काष्ठा perf_record_comm			comm;
	काष्ठा perf_record_namespaces		namespaces;
	काष्ठा perf_record_cgroup		cgroup;
	काष्ठा perf_record_विभाजन			विभाजन;
	काष्ठा perf_record_lost			lost;
	काष्ठा perf_record_lost_samples		lost_samples;
	काष्ठा perf_record_पढ़ो			पढ़ो;
	काष्ठा perf_record_throttle		throttle;
	काष्ठा perf_record_sample		sample;
	काष्ठा perf_record_bpf_event		bpf;
	काष्ठा perf_record_ksymbol		ksymbol;
	काष्ठा perf_record_text_poke_event	text_poke;
	काष्ठा perf_record_header_attr		attr;
	काष्ठा perf_record_event_update		event_update;
	काष्ठा perf_record_header_event_type	event_type;
	काष्ठा perf_record_header_tracing_data	tracing_data;
	काष्ठा perf_record_header_build_id	build_id;
	काष्ठा perf_record_id_index		id_index;
	काष्ठा perf_record_auxtrace_info	auxtrace_info;
	काष्ठा perf_record_auxtrace		auxtrace;
	काष्ठा perf_record_auxtrace_error	auxtrace_error;
	काष्ठा perf_record_aux			aux;
	काष्ठा perf_record_itrace_start		itrace_start;
	काष्ठा perf_record_चयन		context_चयन;
	काष्ठा perf_record_thपढ़ो_map		thपढ़ो_map;
	काष्ठा perf_record_cpu_map		cpu_map;
	काष्ठा perf_record_stat_config		stat_config;
	काष्ठा perf_record_stat			stat;
	काष्ठा perf_record_stat_round		stat_round;
	काष्ठा perf_record_समय_conv		समय_conv;
	काष्ठा perf_record_header_feature	feat;
	काष्ठा perf_record_compressed		pack;
पूर्ण;

#पूर्ण_अगर /* __LIBPERF_EVENT_H */
