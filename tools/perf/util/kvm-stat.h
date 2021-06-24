<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_KVM_STAT_H
#घोषणा __PERF_KVM_STAT_H

#अगर_घोषित HAVE_KVM_STAT_SUPPORT

#समावेश "tool.h"
#समावेश "stat.h"
#समावेश "record.h"

काष्ठा evsel;
काष्ठा evlist;
काष्ठा perf_session;

काष्ठा event_key अणु
	#घोषणा INVALID_KEY     (~0ULL)
	u64 key;
	पूर्णांक info;
	काष्ठा निकास_reasons_table *निकास_reasons;
पूर्ण;

काष्ठा kvm_event_stats अणु
	u64 समय;
	काष्ठा stats stats;
पूर्ण;

काष्ठा kvm_event अणु
	काष्ठा list_head hash_entry;
	काष्ठा rb_node rb;

	काष्ठा event_key key;

	काष्ठा kvm_event_stats total;

	#घोषणा DEFAULT_VCPU_NUM 8
	पूर्णांक max_vcpu;
	काष्ठा kvm_event_stats *vcpu;
पूर्ण;

प्रकार पूर्णांक (*key_cmp_fun)(काष्ठा kvm_event*, काष्ठा kvm_event*, पूर्णांक);

काष्ठा kvm_event_key अणु
	स्थिर अक्षर *name;
	key_cmp_fun key;
पूर्ण;

काष्ठा perf_kvm_stat;

काष्ठा child_event_ops अणु
	व्योम (*get_key)(काष्ठा evsel *evsel,
			काष्ठा perf_sample *sample,
			काष्ठा event_key *key);
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा kvm_events_ops अणु
	bool (*is_begin_event)(काष्ठा evsel *evsel,
			       काष्ठा perf_sample *sample,
			       काष्ठा event_key *key);
	bool (*is_end_event)(काष्ठा evsel *evsel,
			     काष्ठा perf_sample *sample, काष्ठा event_key *key);
	काष्ठा child_event_ops *child_ops;
	व्योम (*decode_key)(काष्ठा perf_kvm_stat *kvm, काष्ठा event_key *key,
			   अक्षर *decode);
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा निकास_reasons_table अणु
	अचिन्हित दीर्घ निकास_code;
	स्थिर अक्षर *reason;
पूर्ण;

#घोषणा EVENTS_BITS		12
#घोषणा EVENTS_CACHE_SIZE	(1UL << EVENTS_BITS)

काष्ठा perf_kvm_stat अणु
	काष्ठा perf_tool    tool;
	काष्ठा record_opts  opts;
	काष्ठा evlist  *evlist;
	काष्ठा perf_session *session;

	स्थिर अक्षर *file_name;
	स्थिर अक्षर *report_event;
	स्थिर अक्षर *sort_key;
	पूर्णांक trace_vcpu;

	काष्ठा निकास_reasons_table *निकास_reasons;
	स्थिर अक्षर *निकास_reasons_isa;

	काष्ठा kvm_events_ops *events_ops;
	key_cmp_fun compare;
	काष्ठा list_head kvm_events_cache[EVENTS_CACHE_SIZE];

	u64 total_समय;
	u64 total_count;
	u64 lost_events;
	u64 duration;

	काष्ठा पूर्णांकlist *pid_list;

	काष्ठा rb_root result;

	पूर्णांक समयrfd;
	अचिन्हित पूर्णांक display_समय;
	bool live;
	bool क्रमce;
पूर्ण;

काष्ठा kvm_reg_events_ops अणु
	स्थिर अक्षर *name;
	काष्ठा kvm_events_ops *ops;
पूर्ण;

व्योम निकास_event_get_key(काष्ठा evsel *evsel,
			काष्ठा perf_sample *sample,
			काष्ठा event_key *key);
bool निकास_event_begin(काष्ठा evsel *evsel,
		      काष्ठा perf_sample *sample,
		      काष्ठा event_key *key);
bool निकास_event_end(काष्ठा evsel *evsel,
		    काष्ठा perf_sample *sample,
		    काष्ठा event_key *key);
व्योम निकास_event_decode_key(काष्ठा perf_kvm_stat *kvm,
			   काष्ठा event_key *key,
			   अक्षर *decode);

bool kvm_निकास_event(काष्ठा evsel *evsel);
bool kvm_entry_event(काष्ठा evsel *evsel);
पूर्णांक setup_kvm_events_tp(काष्ठा perf_kvm_stat *kvm);

#घोषणा define_निकास_reasons_table(name, symbols)	\
	अटल काष्ठा निकास_reasons_table name[] = अणु	\
		symbols, अणु -1, शून्य पूर्ण			\
	पूर्ण

/*
 * arch specअगरic callbacks and data काष्ठाures
 */
पूर्णांक cpu_isa_init(काष्ठा perf_kvm_stat *kvm, स्थिर अक्षर *cpuid);

बाह्य स्थिर अक्षर *kvm_events_tp[];
बाह्य काष्ठा kvm_reg_events_ops kvm_reg_events_ops[];
बाह्य स्थिर अक्षर * स्थिर kvm_skip_events[];
बाह्य स्थिर अक्षर *vcpu_id_str;
बाह्य स्थिर पूर्णांक decode_str_len;
बाह्य स्थिर अक्षर *kvm_निकास_reason;
बाह्य स्थिर अक्षर *kvm_entry_trace;
बाह्य स्थिर अक्षर *kvm_निकास_trace;
#पूर्ण_अगर /* HAVE_KVM_STAT_SUPPORT */

बाह्य पूर्णांक kvm_add_शेष_arch_event(पूर्णांक *argc, स्थिर अक्षर **argv);
#पूर्ण_अगर /* __PERF_KVM_STAT_H */
