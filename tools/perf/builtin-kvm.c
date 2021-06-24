<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "builtin.h"
#समावेश "perf.h"

#समावेश "util/build-id.h"
#समावेश "util/evsel.h"
#समावेश "util/evlist.h"
#समावेश "util/mmap.h"
#समावेश "util/term.h"
#समावेश "util/symbol.h"
#समावेश "util/thread.h"
#समावेश "util/header.h"
#समावेश "util/session.h"
#समावेश "util/intlist.h"
#समावेश <subcmd/pager.h>
#समावेश <subcmd/parse-options.h>
#समावेश "util/trace-event.h"
#समावेश "util/debug.h"
#समावेश "util/tool.h"
#समावेश "util/stat.h"
#समावेश "util/synthetic-events.h"
#समावेश "util/top.h"
#समावेश "util/data.h"
#समावेश "util/ordered-events.h"
#समावेश "util/kvm-stat.h"
#समावेश "ui/ui.h"

#समावेश <sys/prctl.h>
#अगर_घोषित HAVE_TIMERFD_SUPPORT
#समावेश <sys/समयrfd.h>
#पूर्ण_अगर
#समावेश <sys/समय.स>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>

#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/समय64.h>
#समावेश <linux/zभाग.स>
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <poll.h>
#समावेश <termios.h>
#समावेश <semaphore.h>
#समावेश <संकेत.स>
#समावेश <गणित.स>
#समावेश <perf/mmap.h>

अटल स्थिर अक्षर *get_filename_क्रम_perf_kvm(व्योम)
अणु
	स्थिर अक्षर *filename;

	अगर (perf_host && !perf_guest)
		filename = strdup("perf.data.host");
	अन्यथा अगर (!perf_host && perf_guest)
		filename = strdup("perf.data.guest");
	अन्यथा
		filename = strdup("perf.data.kvm");

	वापस filename;
पूर्ण

#अगर_घोषित HAVE_KVM_STAT_SUPPORT

व्योम निकास_event_get_key(काष्ठा evsel *evsel,
			काष्ठा perf_sample *sample,
			काष्ठा event_key *key)
अणु
	key->info = 0;
	key->key  = evsel__पूर्णांकval(evsel, sample, kvm_निकास_reason);
पूर्ण

bool kvm_निकास_event(काष्ठा evsel *evsel)
अणु
	वापस !म_भेद(evsel->name, kvm_निकास_trace);
पूर्ण

bool निकास_event_begin(काष्ठा evsel *evsel,
		      काष्ठा perf_sample *sample, काष्ठा event_key *key)
अणु
	अगर (kvm_निकास_event(evsel)) अणु
		निकास_event_get_key(evsel, sample, key);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

bool kvm_entry_event(काष्ठा evsel *evsel)
अणु
	वापस !म_भेद(evsel->name, kvm_entry_trace);
पूर्ण

bool निकास_event_end(काष्ठा evsel *evsel,
		    काष्ठा perf_sample *sample __maybe_unused,
		    काष्ठा event_key *key __maybe_unused)
अणु
	वापस kvm_entry_event(evsel);
पूर्ण

अटल स्थिर अक्षर *get_निकास_reason(काष्ठा perf_kvm_stat *kvm,
				   काष्ठा निकास_reasons_table *tbl,
				   u64 निकास_code)
अणु
	जबतक (tbl->reason != शून्य) अणु
		अगर (tbl->निकास_code == निकास_code)
			वापस tbl->reason;
		tbl++;
	पूर्ण

	pr_err("unknown kvm exit code:%lld on %s\n",
		(अचिन्हित दीर्घ दीर्घ)निकास_code, kvm->निकास_reasons_isa);
	वापस "UNKNOWN";
पूर्ण

व्योम निकास_event_decode_key(काष्ठा perf_kvm_stat *kvm,
			   काष्ठा event_key *key,
			   अक्षर *decode)
अणु
	स्थिर अक्षर *निकास_reason = get_निकास_reason(kvm, key->निकास_reasons,
						  key->key);

	scnम_लिखो(decode, decode_str_len, "%s", निकास_reason);
पूर्ण

अटल bool रेजिस्टर_kvm_events_ops(काष्ठा perf_kvm_stat *kvm)
अणु
	काष्ठा kvm_reg_events_ops *events_ops = kvm_reg_events_ops;

	क्रम (events_ops = kvm_reg_events_ops; events_ops->name; events_ops++) अणु
		अगर (!म_भेद(events_ops->name, kvm->report_event)) अणु
			kvm->events_ops = events_ops->ops;
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

काष्ठा vcpu_event_record अणु
	पूर्णांक vcpu_id;
	u64 start_समय;
	काष्ठा kvm_event *last_event;
पूर्ण;


अटल व्योम init_kvm_event_record(काष्ठा perf_kvm_stat *kvm)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < EVENTS_CACHE_SIZE; i++)
		INIT_LIST_HEAD(&kvm->kvm_events_cache[i]);
पूर्ण

#अगर_घोषित HAVE_TIMERFD_SUPPORT
अटल व्योम clear_events_cache_stats(काष्ठा list_head *kvm_events_cache)
अणु
	काष्ठा list_head *head;
	काष्ठा kvm_event *event;
	अचिन्हित पूर्णांक i;
	पूर्णांक j;

	क्रम (i = 0; i < EVENTS_CACHE_SIZE; i++) अणु
		head = &kvm_events_cache[i];
		list_क्रम_each_entry(event, head, hash_entry) अणु
			/* reset stats क्रम event */
			event->total.समय = 0;
			init_stats(&event->total.stats);

			क्रम (j = 0; j < event->max_vcpu; ++j) अणु
				event->vcpu[j].समय = 0;
				init_stats(&event->vcpu[j].stats);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक kvm_events_hash_fn(u64 key)
अणु
	वापस key & (EVENTS_CACHE_SIZE - 1);
पूर्ण

अटल bool kvm_event_expand(काष्ठा kvm_event *event, पूर्णांक vcpu_id)
अणु
	पूर्णांक old_max_vcpu = event->max_vcpu;
	व्योम *prev;

	अगर (vcpu_id < event->max_vcpu)
		वापस true;

	जबतक (event->max_vcpu <= vcpu_id)
		event->max_vcpu += DEFAULT_VCPU_NUM;

	prev = event->vcpu;
	event->vcpu = पुनः_स्मृति(event->vcpu,
			      event->max_vcpu * माप(*event->vcpu));
	अगर (!event->vcpu) अणु
		मुक्त(prev);
		pr_err("Not enough memory\n");
		वापस false;
	पूर्ण

	स_रखो(event->vcpu + old_max_vcpu, 0,
	       (event->max_vcpu - old_max_vcpu) * माप(*event->vcpu));
	वापस true;
पूर्ण

अटल काष्ठा kvm_event *kvm_alloc_init_event(काष्ठा event_key *key)
अणु
	काष्ठा kvm_event *event;

	event = zalloc(माप(*event));
	अगर (!event) अणु
		pr_err("Not enough memory\n");
		वापस शून्य;
	पूर्ण

	event->key = *key;
	init_stats(&event->total.stats);
	वापस event;
पूर्ण

अटल काष्ठा kvm_event *find_create_kvm_event(काष्ठा perf_kvm_stat *kvm,
					       काष्ठा event_key *key)
अणु
	काष्ठा kvm_event *event;
	काष्ठा list_head *head;

	BUG_ON(key->key == INVALID_KEY);

	head = &kvm->kvm_events_cache[kvm_events_hash_fn(key->key)];
	list_क्रम_each_entry(event, head, hash_entry) अणु
		अगर (event->key.key == key->key && event->key.info == key->info)
			वापस event;
	पूर्ण

	event = kvm_alloc_init_event(key);
	अगर (!event)
		वापस शून्य;

	list_add(&event->hash_entry, head);
	वापस event;
पूर्ण

अटल bool handle_begin_event(काष्ठा perf_kvm_stat *kvm,
			       काष्ठा vcpu_event_record *vcpu_record,
			       काष्ठा event_key *key, u64 बारtamp)
अणु
	काष्ठा kvm_event *event = शून्य;

	अगर (key->key != INVALID_KEY)
		event = find_create_kvm_event(kvm, key);

	vcpu_record->last_event = event;
	vcpu_record->start_समय = बारtamp;
	वापस true;
पूर्ण

अटल व्योम
kvm_update_event_stats(काष्ठा kvm_event_stats *kvm_stats, u64 समय_dअगरf)
अणु
	kvm_stats->समय += समय_dअगरf;
	update_stats(&kvm_stats->stats, समय_dअगरf);
पूर्ण

अटल द्विगुन kvm_event_rel_stddev(पूर्णांक vcpu_id, काष्ठा kvm_event *event)
अणु
	काष्ठा kvm_event_stats *kvm_stats = &event->total;

	अगर (vcpu_id != -1)
		kvm_stats = &event->vcpu[vcpu_id];

	वापस rel_stddev_stats(stddev_stats(&kvm_stats->stats),
				avg_stats(&kvm_stats->stats));
पूर्ण

अटल bool update_kvm_event(काष्ठा kvm_event *event, पूर्णांक vcpu_id,
			     u64 समय_dअगरf)
अणु
	अगर (vcpu_id == -1) अणु
		kvm_update_event_stats(&event->total, समय_dअगरf);
		वापस true;
	पूर्ण

	अगर (!kvm_event_expand(event, vcpu_id))
		वापस false;

	kvm_update_event_stats(&event->vcpu[vcpu_id], समय_dअगरf);
	वापस true;
पूर्ण

अटल bool is_child_event(काष्ठा perf_kvm_stat *kvm,
			   काष्ठा evsel *evsel,
			   काष्ठा perf_sample *sample,
			   काष्ठा event_key *key)
अणु
	काष्ठा child_event_ops *child_ops;

	child_ops = kvm->events_ops->child_ops;

	अगर (!child_ops)
		वापस false;

	क्रम (; child_ops->name; child_ops++) अणु
		अगर (!म_भेद(evsel->name, child_ops->name)) अणु
			child_ops->get_key(evsel, sample, key);
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool handle_child_event(काष्ठा perf_kvm_stat *kvm,
			       काष्ठा vcpu_event_record *vcpu_record,
			       काष्ठा event_key *key,
			       काष्ठा perf_sample *sample __maybe_unused)
अणु
	काष्ठा kvm_event *event = शून्य;

	अगर (key->key != INVALID_KEY)
		event = find_create_kvm_event(kvm, key);

	vcpu_record->last_event = event;

	वापस true;
पूर्ण

अटल bool skip_event(स्थिर अक्षर *event)
अणु
	स्थिर अक्षर * स्थिर *skip_events;

	क्रम (skip_events = kvm_skip_events; *skip_events; skip_events++)
		अगर (!म_भेद(event, *skip_events))
			वापस true;

	वापस false;
पूर्ण

अटल bool handle_end_event(काष्ठा perf_kvm_stat *kvm,
			     काष्ठा vcpu_event_record *vcpu_record,
			     काष्ठा event_key *key,
			     काष्ठा perf_sample *sample)
अणु
	काष्ठा kvm_event *event;
	u64 समय_begin, समय_dअगरf;
	पूर्णांक vcpu;

	अगर (kvm->trace_vcpu == -1)
		vcpu = -1;
	अन्यथा
		vcpu = vcpu_record->vcpu_id;

	event = vcpu_record->last_event;
	समय_begin = vcpu_record->start_समय;

	/* The begin event is not caught. */
	अगर (!समय_begin)
		वापस true;

	/*
	 * In some हाल, the 'begin event' only records the start बारtamp,
	 * the actual event is recognized in the 'end event' (e.g. mmio-event).
	 */

	/* Both begin and end events did not get the key. */
	अगर (!event && key->key == INVALID_KEY)
		वापस true;

	अगर (!event)
		event = find_create_kvm_event(kvm, key);

	अगर (!event)
		वापस false;

	vcpu_record->last_event = शून्य;
	vcpu_record->start_समय = 0;

	/* seems to happen once in a जबतक during live mode */
	अगर (sample->समय < समय_begin) अणु
		pr_debug("End time before begin time; skipping event.\n");
		वापस true;
	पूर्ण

	समय_dअगरf = sample->समय - समय_begin;

	अगर (kvm->duration && समय_dअगरf > kvm->duration) अणु
		अक्षर decode[decode_str_len];

		kvm->events_ops->decode_key(kvm, &event->key, decode);
		अगर (!skip_event(decode)) अणु
			pr_info("%" PRIu64 " VM %d, vcpu %d: %s event took %" PRIu64 "usec\n",
				 sample->समय, sample->pid, vcpu_record->vcpu_id,
				 decode, समय_dअगरf / NSEC_PER_USEC);
		पूर्ण
	पूर्ण

	वापस update_kvm_event(event, vcpu, समय_dअगरf);
पूर्ण

अटल
काष्ठा vcpu_event_record *per_vcpu_record(काष्ठा thपढ़ो *thपढ़ो,
					  काष्ठा evsel *evsel,
					  काष्ठा perf_sample *sample)
अणु
	/* Only kvm_entry records vcpu id. */
	अगर (!thपढ़ो__priv(thपढ़ो) && kvm_entry_event(evsel)) अणु
		काष्ठा vcpu_event_record *vcpu_record;

		vcpu_record = zalloc(माप(*vcpu_record));
		अगर (!vcpu_record) अणु
			pr_err("%s: Not enough memory\n", __func__);
			वापस शून्य;
		पूर्ण

		vcpu_record->vcpu_id = evsel__पूर्णांकval(evsel, sample, vcpu_id_str);
		thपढ़ो__set_priv(thपढ़ो, vcpu_record);
	पूर्ण

	वापस thपढ़ो__priv(thपढ़ो);
पूर्ण

अटल bool handle_kvm_event(काष्ठा perf_kvm_stat *kvm,
			     काष्ठा thपढ़ो *thपढ़ो,
			     काष्ठा evsel *evsel,
			     काष्ठा perf_sample *sample)
अणु
	काष्ठा vcpu_event_record *vcpu_record;
	काष्ठा event_key key = अणु .key = INVALID_KEY,
				 .निकास_reasons = kvm->निकास_reasons पूर्ण;

	vcpu_record = per_vcpu_record(thपढ़ो, evsel, sample);
	अगर (!vcpu_record)
		वापस true;

	/* only process events क्रम vcpus user cares about */
	अगर ((kvm->trace_vcpu != -1) &&
	    (kvm->trace_vcpu != vcpu_record->vcpu_id))
		वापस true;

	अगर (kvm->events_ops->is_begin_event(evsel, sample, &key))
		वापस handle_begin_event(kvm, vcpu_record, &key, sample->समय);

	अगर (is_child_event(kvm, evsel, sample, &key))
		वापस handle_child_event(kvm, vcpu_record, &key, sample);

	अगर (kvm->events_ops->is_end_event(evsel, sample, &key))
		वापस handle_end_event(kvm, vcpu_record, &key, sample);

	वापस true;
पूर्ण

#घोषणा GET_EVENT_KEY(func, field)					\
अटल u64 get_event_ ##func(काष्ठा kvm_event *event, पूर्णांक vcpu)		\
अणु									\
	अगर (vcpu == -1)							\
		वापस event->total.field;				\
									\
	अगर (vcpu >= event->max_vcpu)					\
		वापस 0;						\
									\
	वापस event->vcpu[vcpu].field;					\
पूर्ण

#घोषणा COMPARE_EVENT_KEY(func, field)					\
GET_EVENT_KEY(func, field)						\
अटल पूर्णांक compare_kvm_event_ ## func(काष्ठा kvm_event *one,		\
					काष्ठा kvm_event *two, पूर्णांक vcpu)\
अणु									\
	वापस get_event_ ##func(one, vcpu) >				\
				get_event_ ##func(two, vcpu);		\
पूर्ण

GET_EVENT_KEY(समय, समय);
COMPARE_EVENT_KEY(count, stats.n);
COMPARE_EVENT_KEY(mean, stats.mean);
GET_EVENT_KEY(max, stats.max);
GET_EVENT_KEY(min, stats.min);

#घोषणा DEF_SORT_NAME_KEY(name, compare_key)				\
	अणु #name, compare_kvm_event_ ## compare_key पूर्ण

अटल काष्ठा kvm_event_key keys[] = अणु
	DEF_SORT_NAME_KEY(sample, count),
	DEF_SORT_NAME_KEY(समय, mean),
	अणु शून्य, शून्य पूर्ण
पूर्ण;

अटल bool select_key(काष्ठा perf_kvm_stat *kvm)
अणु
	पूर्णांक i;

	क्रम (i = 0; keys[i].name; i++) अणु
		अगर (!म_भेद(keys[i].name, kvm->sort_key)) अणु
			kvm->compare = keys[i].key;
			वापस true;
		पूर्ण
	पूर्ण

	pr_err("Unknown compare key:%s\n", kvm->sort_key);
	वापस false;
पूर्ण

अटल व्योम insert_to_result(काष्ठा rb_root *result, काष्ठा kvm_event *event,
			     key_cmp_fun bigger, पूर्णांक vcpu)
अणु
	काष्ठा rb_node **rb = &result->rb_node;
	काष्ठा rb_node *parent = शून्य;
	काष्ठा kvm_event *p;

	जबतक (*rb) अणु
		p = container_of(*rb, काष्ठा kvm_event, rb);
		parent = *rb;

		अगर (bigger(event, p, vcpu))
			rb = &(*rb)->rb_left;
		अन्यथा
			rb = &(*rb)->rb_right;
	पूर्ण

	rb_link_node(&event->rb, parent, rb);
	rb_insert_color(&event->rb, result);
पूर्ण

अटल व्योम
update_total_count(काष्ठा perf_kvm_stat *kvm, काष्ठा kvm_event *event)
अणु
	पूर्णांक vcpu = kvm->trace_vcpu;

	kvm->total_count += get_event_count(event, vcpu);
	kvm->total_समय += get_event_समय(event, vcpu);
पूर्ण

अटल bool event_is_valid(काष्ठा kvm_event *event, पूर्णांक vcpu)
अणु
	वापस !!get_event_count(event, vcpu);
पूर्ण

अटल व्योम sort_result(काष्ठा perf_kvm_stat *kvm)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक vcpu = kvm->trace_vcpu;
	काष्ठा kvm_event *event;

	क्रम (i = 0; i < EVENTS_CACHE_SIZE; i++) अणु
		list_क्रम_each_entry(event, &kvm->kvm_events_cache[i], hash_entry) अणु
			अगर (event_is_valid(event, vcpu)) अणु
				update_total_count(kvm, event);
				insert_to_result(&kvm->result, event,
						 kvm->compare, vcpu);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* वापसs left most element of result, and erase it */
अटल काष्ठा kvm_event *pop_from_result(काष्ठा rb_root *result)
अणु
	काष्ठा rb_node *node = rb_first(result);

	अगर (!node)
		वापस शून्य;

	rb_erase(node, result);
	वापस container_of(node, काष्ठा kvm_event, rb);
पूर्ण

अटल व्योम prपूर्णांक_vcpu_info(काष्ठा perf_kvm_stat *kvm)
अणु
	पूर्णांक vcpu = kvm->trace_vcpu;

	pr_info("Analyze events for ");

	अगर (kvm->opts.target.प्रणाली_wide)
		pr_info("all VMs, ");
	अन्यथा अगर (kvm->opts.target.pid)
		pr_info("pid(s) %s, ", kvm->opts.target.pid);
	अन्यथा
		pr_info("dazed and confused on what is monitored, ");

	अगर (vcpu == -1)
		pr_info("all VCPUs:\n\n");
	अन्यथा
		pr_info("VCPU %d:\n\n", vcpu);
पूर्ण

अटल व्योम show_समयofday(व्योम)
अणु
	अक्षर date[64];
	काष्ठा समयval tv;
	काष्ठा पंचांग lसमय;

	समय_लोofday(&tv, शून्य);
	अगर (स_स्थानीय_r(&tv.tv_sec, &lसमय)) अणु
		स_माला(date, माप(date), "%H:%M:%S", &lसमय);
		pr_info("%s.%06ld", date, tv.tv_usec);
	पूर्ण अन्यथा
		pr_info("00:00:00.000000");

	वापस;
पूर्ण

अटल व्योम prपूर्णांक_result(काष्ठा perf_kvm_stat *kvm)
अणु
	अक्षर decode[decode_str_len];
	काष्ठा kvm_event *event;
	पूर्णांक vcpu = kvm->trace_vcpu;

	अगर (kvm->live) अणु
		माला_दो(CONSOLE_CLEAR);
		show_समयofday();
	पूर्ण

	pr_info("\n\n");
	prपूर्णांक_vcpu_info(kvm);
	pr_info("%*s ", decode_str_len, kvm->events_ops->name);
	pr_info("%10s ", "Samples");
	pr_info("%9s ", "Samples%");

	pr_info("%9s ", "Time%");
	pr_info("%11s ", "Min Time");
	pr_info("%11s ", "Max Time");
	pr_info("%16s ", "Avg time");
	pr_info("\n\n");

	जबतक ((event = pop_from_result(&kvm->result))) अणु
		u64 ecount, eसमय, max, min;

		ecount = get_event_count(event, vcpu);
		eसमय = get_event_समय(event, vcpu);
		max = get_event_max(event, vcpu);
		min = get_event_min(event, vcpu);

		kvm->events_ops->decode_key(kvm, &event->key, decode);
		pr_info("%*s ", decode_str_len, decode);
		pr_info("%10llu ", (अचिन्हित दीर्घ दीर्घ)ecount);
		pr_info("%8.2f%% ", (द्विगुन)ecount / kvm->total_count * 100);
		pr_info("%8.2f%% ", (द्विगुन)eसमय / kvm->total_समय * 100);
		pr_info("%9.2fus ", (द्विगुन)min / NSEC_PER_USEC);
		pr_info("%9.2fus ", (द्विगुन)max / NSEC_PER_USEC);
		pr_info("%9.2fus ( +-%7.2f%% )", (द्विगुन)eसमय / ecount / NSEC_PER_USEC,
			kvm_event_rel_stddev(vcpu, event));
		pr_info("\n");
	पूर्ण

	pr_info("\nTotal Samples:%" PRIu64 ", Total events handled time:%.2fus.\n\n",
		kvm->total_count, kvm->total_समय / (द्विगुन)NSEC_PER_USEC);

	अगर (kvm->lost_events)
		pr_info("\nLost events: %" PRIu64 "\n\n", kvm->lost_events);
पूर्ण

#अगर_घोषित HAVE_TIMERFD_SUPPORT
अटल पूर्णांक process_lost_event(काष्ठा perf_tool *tool,
			      जोड़ perf_event *event __maybe_unused,
			      काष्ठा perf_sample *sample __maybe_unused,
			      काष्ठा machine *machine __maybe_unused)
अणु
	काष्ठा perf_kvm_stat *kvm = container_of(tool, काष्ठा perf_kvm_stat, tool);

	kvm->lost_events++;
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल bool skip_sample(काष्ठा perf_kvm_stat *kvm,
			काष्ठा perf_sample *sample)
अणु
	अगर (kvm->pid_list && पूर्णांकlist__find(kvm->pid_list, sample->pid) == शून्य)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक process_sample_event(काष्ठा perf_tool *tool,
				जोड़ perf_event *event,
				काष्ठा perf_sample *sample,
				काष्ठा evsel *evsel,
				काष्ठा machine *machine)
अणु
	पूर्णांक err = 0;
	काष्ठा thपढ़ो *thपढ़ो;
	काष्ठा perf_kvm_stat *kvm = container_of(tool, काष्ठा perf_kvm_stat,
						 tool);

	अगर (skip_sample(kvm, sample))
		वापस 0;

	thपढ़ो = machine__findnew_thपढ़ो(machine, sample->pid, sample->tid);
	अगर (thपढ़ो == शून्य) अणु
		pr_debug("problem processing %d event, skipping it.\n",
			event->header.type);
		वापस -1;
	पूर्ण

	अगर (!handle_kvm_event(kvm, thपढ़ो, evsel, sample))
		err = -1;

	thपढ़ो__put(thपढ़ो);
	वापस err;
पूर्ण

अटल पूर्णांक cpu_isa_config(काष्ठा perf_kvm_stat *kvm)
अणु
	अक्षर buf[128], *cpuid;
	पूर्णांक err;

	अगर (kvm->live) अणु
		err = get_cpuid(buf, माप(buf));
		अगर (err != 0) अणु
			pr_err("Failed to look up CPU type: %s\n",
			       str_error_r(err, buf, माप(buf)));
			वापस -err;
		पूर्ण
		cpuid = buf;
	पूर्ण अन्यथा
		cpuid = kvm->session->header.env.cpuid;

	अगर (!cpuid) अणु
		pr_err("Failed to look up CPU type\n");
		वापस -EINVAL;
	पूर्ण

	err = cpu_isa_init(kvm, cpuid);
	अगर (err == -ENOTSUP)
		pr_err("CPU %s is not supported.\n", cpuid);

	वापस err;
पूर्ण

अटल bool verअगरy_vcpu(पूर्णांक vcpu)
अणु
	अगर (vcpu != -1 && vcpu < 0) अणु
		pr_err("Invalid vcpu:%d.\n", vcpu);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

#अगर_घोषित HAVE_TIMERFD_SUPPORT
/* keeping the max events to a modest level to keep
 * the processing of samples per mmap smooth.
 */
#घोषणा PERF_KVM__MAX_EVENTS_PER_MMAP  25

अटल s64 perf_kvm__mmap_पढ़ो_idx(काष्ठा perf_kvm_stat *kvm, पूर्णांक idx,
				   u64 *mmap_समय)
अणु
	काष्ठा evlist *evlist = kvm->evlist;
	जोड़ perf_event *event;
	काष्ठा mmap *md;
	u64 बारtamp;
	s64 n = 0;
	पूर्णांक err;

	*mmap_समय = ULदीर्घ_उच्च;
	md = &evlist->mmap[idx];
	err = perf_mmap__पढ़ो_init(&md->core);
	अगर (err < 0)
		वापस (err == -EAGAIN) ? 0 : -1;

	जबतक ((event = perf_mmap__पढ़ो_event(&md->core)) != शून्य) अणु
		err = evlist__parse_sample_बारtamp(evlist, event, &बारtamp);
		अगर (err) अणु
			perf_mmap__consume(&md->core);
			pr_err("Failed to parse sample\n");
			वापस -1;
		पूर्ण

		err = perf_session__queue_event(kvm->session, event, बारtamp, 0);
		/*
		 * FIXME: Here we can't consume the event, as perf_session__queue_event will
		 *        poपूर्णांक to it, and it'll get possibly overwritten by the kernel.
		 */
		perf_mmap__consume(&md->core);

		अगर (err) अणु
			pr_err("Failed to enqueue sample: %d\n", err);
			वापस -1;
		पूर्ण

		/* save समय stamp of our first sample क्रम this mmap */
		अगर (n == 0)
			*mmap_समय = बारtamp;

		/* limit events per mmap handled all at once */
		n++;
		अगर (n == PERF_KVM__MAX_EVENTS_PER_MMAP)
			अवरोध;
	पूर्ण

	perf_mmap__पढ़ो_करोne(&md->core);
	वापस n;
पूर्ण

अटल पूर्णांक perf_kvm__mmap_पढ़ो(काष्ठा perf_kvm_stat *kvm)
अणु
	पूर्णांक i, err, throttled = 0;
	s64 n, ntotal = 0;
	u64 flush_समय = ULदीर्घ_उच्च, mmap_समय;

	क्रम (i = 0; i < kvm->evlist->core.nr_mmaps; i++) अणु
		n = perf_kvm__mmap_पढ़ो_idx(kvm, i, &mmap_समय);
		अगर (n < 0)
			वापस -1;

		/* flush समय is going to be the minimum of all the inभागidual
		 * mmap बार. Essentially, we flush all the samples queued up
		 * from the last pass under our minimal start समय -- that leaves
		 * a very small race क्रम samples to come in with a lower बारtamp.
		 * The ioctl to वापस the perf_घड़ी बारtamp should बंद the
		 * race entirely.
		 */
		अगर (mmap_समय < flush_समय)
			flush_समय = mmap_समय;

		ntotal += n;
		अगर (n == PERF_KVM__MAX_EVENTS_PER_MMAP)
			throttled = 1;
	पूर्ण

	/* flush queue after each round in which we processed events */
	अगर (ntotal) अणु
		काष्ठा ordered_events *oe = &kvm->session->ordered_events;

		oe->next_flush = flush_समय;
		err = ordered_events__flush(oe, OE_FLUSH__ROUND);
		अगर (err) अणु
			अगर (kvm->lost_events)
				pr_info("\nLost events: %" PRIu64 "\n\n",
					kvm->lost_events);
			वापस err;
		पूर्ण
	पूर्ण

	वापस throttled;
पूर्ण

अटल अस्थिर पूर्णांक करोne;

अटल व्योम sig_handler(पूर्णांक sig __maybe_unused)
अणु
	करोne = 1;
पूर्ण

अटल पूर्णांक perf_kvm__समयrfd_create(काष्ठा perf_kvm_stat *kvm)
अणु
	काष्ठा iसमयrspec new_value;
	पूर्णांक rc = -1;

	kvm->समयrfd = समयrfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK);
	अगर (kvm->समयrfd < 0) अणु
		pr_err("timerfd_create failed\n");
		जाओ out;
	पूर्ण

	new_value.it_value.tv_sec = kvm->display_समय;
	new_value.it_value.tv_nsec = 0;
	new_value.it_पूर्णांकerval.tv_sec = kvm->display_समय;
	new_value.it_पूर्णांकerval.tv_nsec = 0;

	अगर (समयrfd_समय_रखो(kvm->समयrfd, 0, &new_value, शून्य) != 0) अणु
		pr_err("timerfd_settime failed: %d\n", त्रुटि_सं);
		बंद(kvm->समयrfd);
		जाओ out;
	पूर्ण

	rc = 0;
out:
	वापस rc;
पूर्ण

अटल पूर्णांक perf_kvm__handle_समयrfd(काष्ठा perf_kvm_stat *kvm)
अणु
	uपूर्णांक64_t c;
	पूर्णांक rc;

	rc = पढ़ो(kvm->समयrfd, &c, माप(uपूर्णांक64_t));
	अगर (rc < 0) अणु
		अगर (त्रुटि_सं == EAGAIN)
			वापस 0;

		pr_err("Failed to read timer fd: %d\n", त्रुटि_सं);
		वापस -1;
	पूर्ण

	अगर (rc != माप(uपूर्णांक64_t)) अणु
		pr_err("Error reading timer fd - invalid size returned\n");
		वापस -1;
	पूर्ण

	अगर (c != 1)
		pr_debug("Missed timer beats: %" PRIu64 "\n", c-1);

	/* update display */
	sort_result(kvm);
	prपूर्णांक_result(kvm);

	/* reset counts */
	clear_events_cache_stats(kvm->kvm_events_cache);
	kvm->total_count = 0;
	kvm->total_समय = 0;
	kvm->lost_events = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक fd_set_nonblock(पूर्णांक fd)
अणु
	दीर्घ arg = 0;

	arg = fcntl(fd, F_GETFL);
	अगर (arg < 0) अणु
		pr_err("Failed to get current flags for fd %d\n", fd);
		वापस -1;
	पूर्ण

	अगर (fcntl(fd, F_SETFL, arg | O_NONBLOCK) < 0) अणु
		pr_err("Failed to set non-block option on fd %d\n", fd);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक perf_kvm__handle_मानक_निवेश(व्योम)
अणु
	पूर्णांक c;

	c = अ_लो(मानक_निवेश);
	अगर (c == 'q')
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_events_live_report(काष्ठा perf_kvm_stat *kvm)
अणु
	पूर्णांक nr_मानक_निवेश, ret, err = -EINVAL;
	काष्ठा termios save;

	/* live flag must be set first */
	kvm->live = true;

	ret = cpu_isa_config(kvm);
	अगर (ret < 0)
		वापस ret;

	अगर (!verअगरy_vcpu(kvm->trace_vcpu) ||
	    !select_key(kvm) ||
	    !रेजिस्टर_kvm_events_ops(kvm)) अणु
		जाओ out;
	पूर्ण

	set_term_quiet_input(&save);
	init_kvm_event_record(kvm);

	संकेत(संक_विघ्न, sig_handler);
	संकेत(संक_इति, sig_handler);

	/* add समयr fd */
	अगर (perf_kvm__समयrfd_create(kvm) < 0) अणु
		err = -1;
		जाओ out;
	पूर्ण

	अगर (evlist__add_pollfd(kvm->evlist, kvm->समयrfd) < 0)
		जाओ out;

	nr_मानक_निवेश = evlist__add_pollfd(kvm->evlist, fileno(मानक_निवेश));
	अगर (nr_मानक_निवेश < 0)
		जाओ out;

	अगर (fd_set_nonblock(fileno(मानक_निवेश)) != 0)
		जाओ out;

	/* everything is good - enable the events and process */
	evlist__enable(kvm->evlist);

	जबतक (!करोne) अणु
		काष्ठा fdarray *fda = &kvm->evlist->core.pollfd;
		पूर्णांक rc;

		rc = perf_kvm__mmap_पढ़ो(kvm);
		अगर (rc < 0)
			अवरोध;

		err = perf_kvm__handle_समयrfd(kvm);
		अगर (err)
			जाओ out;

		अगर (fda->entries[nr_मानक_निवेश].revents & POLLIN)
			करोne = perf_kvm__handle_मानक_निवेश();

		अगर (!rc && !करोne)
			err = evlist__poll(kvm->evlist, 100);
	पूर्ण

	evlist__disable(kvm->evlist);

	अगर (err == 0) अणु
		sort_result(kvm);
		prपूर्णांक_result(kvm);
	पूर्ण

out:
	अगर (kvm->समयrfd >= 0)
		बंद(kvm->समयrfd);

	tcsetattr(0, TCSAFLUSH, &save);
	वापस err;
पूर्ण

अटल पूर्णांक kvm_live_खोलो_events(काष्ठा perf_kvm_stat *kvm)
अणु
	पूर्णांक err, rc = -1;
	काष्ठा evsel *pos;
	काष्ठा evlist *evlist = kvm->evlist;
	अक्षर sbuf[STRERR_बफ_मानE];

	evlist__config(evlist, &kvm->opts, शून्य);

	/*
	 * Note: exclude_अणुguest,hostपूर्ण करो not apply here.
	 *       This command processes KVM tracepoपूर्णांकs from host only
	 */
	evlist__क्रम_each_entry(evlist, pos) अणु
		काष्ठा perf_event_attr *attr = &pos->core.attr;

		/* make sure these *are* set */
		evsel__set_sample_bit(pos, TID);
		evsel__set_sample_bit(pos, TIME);
		evsel__set_sample_bit(pos, CPU);
		evsel__set_sample_bit(pos, RAW);
		/* make sure these are *not*; want as small a sample as possible */
		evsel__reset_sample_bit(pos, PERIOD);
		evsel__reset_sample_bit(pos, IP);
		evsel__reset_sample_bit(pos, CALLCHAIN);
		evsel__reset_sample_bit(pos, ADDR);
		evsel__reset_sample_bit(pos, READ);
		attr->mmap = 0;
		attr->comm = 0;
		attr->task = 0;

		attr->sample_period = 1;

		attr->watermark = 0;
		attr->wakeup_events = 1000;

		/* will enable all once we are पढ़ोy */
		attr->disabled = 1;
	पूर्ण

	err = evlist__खोलो(evlist);
	अगर (err < 0) अणु
		म_लिखो("Couldn't create the events: %s\n",
		       str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		जाओ out;
	पूर्ण

	अगर (evlist__mmap(evlist, kvm->opts.mmap_pages) < 0) अणु
		ui__error("Failed to mmap the events: %s\n",
			  str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		evlist__बंद(evlist);
		जाओ out;
	पूर्ण

	rc = 0;

out:
	वापस rc;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक पढ़ो_events(काष्ठा perf_kvm_stat *kvm)
अणु
	पूर्णांक ret;

	काष्ठा perf_tool eops = अणु
		.sample			= process_sample_event,
		.comm			= perf_event__process_comm,
		.namespaces		= perf_event__process_namespaces,
		.ordered_events		= true,
	पूर्ण;
	काष्ठा perf_data file = अणु
		.path  = kvm->file_name,
		.mode  = PERF_DATA_MODE_READ,
		.क्रमce = kvm->क्रमce,
	पूर्ण;

	kvm->tool = eops;
	kvm->session = perf_session__new(&file, false, &kvm->tool);
	अगर (IS_ERR(kvm->session)) अणु
		pr_err("Initializing perf session failed\n");
		वापस PTR_ERR(kvm->session);
	पूर्ण

	symbol__init(&kvm->session->header.env);

	अगर (!perf_session__has_traces(kvm->session, "kvm record")) अणु
		ret = -EINVAL;
		जाओ out_delete;
	पूर्ण

	/*
	 * Do not use 'isa' recorded in kvm_निकास tracepoपूर्णांक since it is not
	 * traced in the old kernel.
	 */
	ret = cpu_isa_config(kvm);
	अगर (ret < 0)
		जाओ out_delete;

	ret = perf_session__process_events(kvm->session);

out_delete:
	perf_session__delete(kvm->session);
	वापस ret;
पूर्ण

अटल पूर्णांक parse_target_str(काष्ठा perf_kvm_stat *kvm)
अणु
	अगर (kvm->opts.target.pid) अणु
		kvm->pid_list = पूर्णांकlist__new(kvm->opts.target.pid);
		अगर (kvm->pid_list == शून्य) अणु
			pr_err("Error parsing process id string\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kvm_events_report_vcpu(काष्ठा perf_kvm_stat *kvm)
अणु
	पूर्णांक ret = -EINVAL;
	पूर्णांक vcpu = kvm->trace_vcpu;

	अगर (parse_target_str(kvm) != 0)
		जाओ निकास;

	अगर (!verअगरy_vcpu(vcpu))
		जाओ निकास;

	अगर (!select_key(kvm))
		जाओ निकास;

	अगर (!रेजिस्टर_kvm_events_ops(kvm))
		जाओ निकास;

	init_kvm_event_record(kvm);
	setup_pager();

	ret = पढ़ो_events(kvm);
	अगर (ret)
		जाओ निकास;

	sort_result(kvm);
	prपूर्णांक_result(kvm);

निकास:
	वापस ret;
पूर्ण

#घोषणा STRDUP_FAIL_EXIT(s)		\
	(अणु	अक्षर *_p;		\
	_p = strdup(s);		\
		अगर (!_p)		\
			वापस -ENOMEM;	\
		_p;			\
	पूर्ण)

पूर्णांक __weak setup_kvm_events_tp(काष्ठा perf_kvm_stat *kvm __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक
kvm_events_record(काष्ठा perf_kvm_stat *kvm, पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अचिन्हित पूर्णांक rec_argc, i, j, events_tp_size;
	स्थिर अक्षर **rec_argv;
	स्थिर अक्षर * स्थिर record_args[] = अणु
		"record",
		"-R",
		"-m", "1024",
		"-c", "1",
	पूर्ण;
	स्थिर अक्षर * स्थिर kvm_stat_record_usage[] = अणु
		"perf kvm stat record [<options>]",
		शून्य
	पूर्ण;
	स्थिर अक्षर * स्थिर *events_tp;
	पूर्णांक ret;

	events_tp_size = 0;
	ret = setup_kvm_events_tp(kvm);
	अगर (ret < 0) अणु
		pr_err("Unable to setup the kvm tracepoints\n");
		वापस ret;
	पूर्ण

	क्रम (events_tp = kvm_events_tp; *events_tp; events_tp++)
		events_tp_size++;

	rec_argc = ARRAY_SIZE(record_args) + argc + 2 +
		   2 * events_tp_size;
	rec_argv = सुस्मृति(rec_argc + 1, माप(अक्षर *));

	अगर (rec_argv == शून्य)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(record_args); i++)
		rec_argv[i] = STRDUP_FAIL_EXIT(record_args[i]);

	क्रम (j = 0; j < events_tp_size; j++) अणु
		rec_argv[i++] = "-e";
		rec_argv[i++] = STRDUP_FAIL_EXIT(kvm_events_tp[j]);
	पूर्ण

	rec_argv[i++] = STRDUP_FAIL_EXIT("-o");
	rec_argv[i++] = STRDUP_FAIL_EXIT(kvm->file_name);

	क्रम (j = 1; j < (अचिन्हित पूर्णांक)argc; j++, i++)
		rec_argv[i] = argv[j];

	set_option_flag(record_options, 'e', "event", PARSE_OPT_HIDDEN);
	set_option_flag(record_options, 0, "filter", PARSE_OPT_HIDDEN);
	set_option_flag(record_options, 'R', "raw-samples", PARSE_OPT_HIDDEN);

	set_option_flag(record_options, 'F', "freq", PARSE_OPT_DISABLED);
	set_option_flag(record_options, 0, "group", PARSE_OPT_DISABLED);
	set_option_flag(record_options, 'g', शून्य, PARSE_OPT_DISABLED);
	set_option_flag(record_options, 0, "call-graph", PARSE_OPT_DISABLED);
	set_option_flag(record_options, 'd', "data", PARSE_OPT_DISABLED);
	set_option_flag(record_options, 'T', "timestamp", PARSE_OPT_DISABLED);
	set_option_flag(record_options, 'P', "period", PARSE_OPT_DISABLED);
	set_option_flag(record_options, 'n', "no-samples", PARSE_OPT_DISABLED);
	set_option_flag(record_options, 'N', "no-buildid-cache", PARSE_OPT_DISABLED);
	set_option_flag(record_options, 'B', "no-buildid", PARSE_OPT_DISABLED);
	set_option_flag(record_options, 'G', "cgroup", PARSE_OPT_DISABLED);
	set_option_flag(record_options, 'b', "branch-any", PARSE_OPT_DISABLED);
	set_option_flag(record_options, 'j', "branch-filter", PARSE_OPT_DISABLED);
	set_option_flag(record_options, 'W', "weight", PARSE_OPT_DISABLED);
	set_option_flag(record_options, 0, "transaction", PARSE_OPT_DISABLED);

	record_usage = kvm_stat_record_usage;
	वापस cmd_record(i, rec_argv);
पूर्ण

अटल पूर्णांक
kvm_events_report(काष्ठा perf_kvm_stat *kvm, पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	स्थिर काष्ठा option kvm_events_report_options[] = अणु
		OPT_STRING(0, "event", &kvm->report_event, "report event",
			   "event for reporting: vmexit, "
			   "mmio (x86 only), ioport (x86 only)"),
		OPT_INTEGER(0, "vcpu", &kvm->trace_vcpu,
			    "vcpu id to report"),
		OPT_STRING('k', "key", &kvm->sort_key, "sort-key",
			    "key for sorting: sample(sort by samples number)"
			    " time (sort by avg time)"),
		OPT_STRING('p', "pid", &kvm->opts.target.pid, "pid",
			   "analyze events only for given process id(s)"),
		OPT_BOOLEAN('f', "force", &kvm->force, "don't complain, करो it"),
		OPT_END()
	पूर्ण;

	स्थिर अक्षर * स्थिर kvm_events_report_usage[] = अणु
		"perf kvm stat report [<options>]",
		शून्य
	पूर्ण;

	अगर (argc) अणु
		argc = parse_options(argc, argv,
				     kvm_events_report_options,
				     kvm_events_report_usage, 0);
		अगर (argc)
			usage_with_options(kvm_events_report_usage,
					   kvm_events_report_options);
	पूर्ण

	अगर (!kvm->opts.target.pid)
		kvm->opts.target.प्रणाली_wide = true;

	वापस kvm_events_report_vcpu(kvm);
पूर्ण

#अगर_घोषित HAVE_TIMERFD_SUPPORT
अटल काष्ठा evlist *kvm_live_event_list(व्योम)
अणु
	काष्ठा evlist *evlist;
	अक्षर *tp, *name, *sys;
	पूर्णांक err = -1;
	स्थिर अक्षर * स्थिर *events_tp;

	evlist = evlist__new();
	अगर (evlist == शून्य)
		वापस शून्य;

	क्रम (events_tp = kvm_events_tp; *events_tp; events_tp++) अणु

		tp = strdup(*events_tp);
		अगर (tp == शून्य)
			जाओ out;

		/* split tracepoपूर्णांक पूर्णांकo subप्रणाली and name */
		sys = tp;
		name = म_अक्षर(tp, ':');
		अगर (name == शून्य) अणु
			pr_err("Error parsing %s tracepoint: subsystem delimiter not found\n",
			       *events_tp);
			मुक्त(tp);
			जाओ out;
		पूर्ण
		*name = '\0';
		name++;

		अगर (evlist__add_newtp(evlist, sys, name, शून्य)) अणु
			pr_err("Failed to add %s tracepoint to the list\n", *events_tp);
			मुक्त(tp);
			जाओ out;
		पूर्ण

		मुक्त(tp);
	पूर्ण

	err = 0;

out:
	अगर (err) अणु
		evlist__delete(evlist);
		evlist = शून्य;
	पूर्ण

	वापस evlist;
पूर्ण

अटल पूर्णांक kvm_events_live(काष्ठा perf_kvm_stat *kvm,
			   पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अक्षर errbuf[बफ_मान];
	पूर्णांक err;

	स्थिर काष्ठा option live_options[] = अणु
		OPT_STRING('p', "pid", &kvm->opts.target.pid, "pid",
			"record events on existing process id"),
		OPT_CALLBACK('m', "mmap-pages", &kvm->opts.mmap_pages, "pages",
			"number of mmap data pages", evlist__parse_mmap_pages),
		OPT_INCR('v', "verbose", &verbose,
			"be more verbose (show counter open errors, etc)"),
		OPT_BOOLEAN('a', "all-cpus", &kvm->opts.target.प्रणाली_wide,
			"system-wide collection from all CPUs"),
		OPT_UINTEGER('d', "display", &kvm->display_समय,
			"time in seconds between display updates"),
		OPT_STRING(0, "event", &kvm->report_event, "report event",
			"event for reporting: "
			"vmexit, mmio (x86 only), ioport (x86 only)"),
		OPT_INTEGER(0, "vcpu", &kvm->trace_vcpu,
			"vcpu id to report"),
		OPT_STRING('k', "key", &kvm->sort_key, "sort-key",
			"key for sorting: sample(sort by samples number)"
			" time (sort by avg time)"),
		OPT_U64(0, "duration", &kvm->duration,
			"show events other than"
			" HLT (x86 only) or Wait state (s390 only)"
			" that take longer than duration usecs"),
		OPT_UINTEGER(0, "proc-map-timeout", &proc_map_समयout,
				"per thread proc mmap processing timeout in ms"),
		OPT_END()
	पूर्ण;
	स्थिर अक्षर * स्थिर live_usage[] = अणु
		"perf kvm stat live [<options>]",
		शून्य
	पूर्ण;
	काष्ठा perf_data data = अणु
		.mode = PERF_DATA_MODE_WRITE,
	पूर्ण;


	/* event handling */
	kvm->tool.sample = process_sample_event;
	kvm->tool.comm   = perf_event__process_comm;
	kvm->tool.निकास   = perf_event__process_निकास;
	kvm->tool.विभाजन   = perf_event__process_विभाजन;
	kvm->tool.lost   = process_lost_event;
	kvm->tool.namespaces  = perf_event__process_namespaces;
	kvm->tool.ordered_events = true;
	perf_tool__fill_शेषs(&kvm->tool);

	/* set शेषs */
	kvm->display_समय = 1;
	kvm->opts.user_पूर्णांकerval = 1;
	kvm->opts.mmap_pages = 512;
	kvm->opts.target.uses_mmap = false;
	kvm->opts.target.uid_str = शून्य;
	kvm->opts.target.uid = अच_पूर्णांक_उच्च;

	symbol__init(शून्य);
	disable_buildid_cache();

	use_browser = 0;

	अगर (argc) अणु
		argc = parse_options(argc, argv, live_options,
				     live_usage, 0);
		अगर (argc)
			usage_with_options(live_usage, live_options);
	पूर्ण

	kvm->duration *= NSEC_PER_USEC;   /* convert usec to nsec */

	/*
	 * target related setups
	 */
	err = target__validate(&kvm->opts.target);
	अगर (err) अणु
		target__म_त्रुटि(&kvm->opts.target, err, errbuf, बफ_मान);
		ui__warning("%s", errbuf);
	पूर्ण

	अगर (target__none(&kvm->opts.target))
		kvm->opts.target.प्रणाली_wide = true;


	/*
	 * generate the event list
	 */
	err = setup_kvm_events_tp(kvm);
	अगर (err < 0) अणु
		pr_err("Unable to setup the kvm tracepoints\n");
		वापस err;
	पूर्ण

	kvm->evlist = kvm_live_event_list();
	अगर (kvm->evlist == शून्य) अणु
		err = -1;
		जाओ out;
	पूर्ण

	अगर (evlist__create_maps(kvm->evlist, &kvm->opts.target) < 0)
		usage_with_options(live_usage, live_options);

	/*
	 * perf session
	 */
	kvm->session = perf_session__new(&data, false, &kvm->tool);
	अगर (IS_ERR(kvm->session)) अणु
		err = PTR_ERR(kvm->session);
		जाओ out;
	पूर्ण
	kvm->session->evlist = kvm->evlist;
	perf_session__set_id_hdr_size(kvm->session);
	ordered_events__set_copy_on_queue(&kvm->session->ordered_events, true);
	machine__syntheमाप_प्रकारhपढ़ोs(&kvm->session->machines.host, &kvm->opts.target,
				    kvm->evlist->core.thपढ़ोs, false, 1);
	err = kvm_live_खोलो_events(kvm);
	अगर (err)
		जाओ out;

	err = kvm_events_live_report(kvm);

out:
	perf_session__delete(kvm->session);
	kvm->session = शून्य;
	evlist__delete(kvm->evlist);

	वापस err;
पूर्ण
#पूर्ण_अगर

अटल व्योम prपूर्णांक_kvm_stat_usage(व्योम)
अणु
	म_लिखो("Usage: perf kvm stat <command>\n\n");

	म_लिखो("# Available commands:\n");
	म_लिखो("\trecord: record kvm events\n");
	म_लिखो("\treport: report statistical data of kvm events\n");
	म_लिखो("\tlive:   live reporting of statistical data of kvm events\n");

	म_लिखो("\nOtherwise, it is the alias of 'perf stat':\n");
पूर्ण

अटल पूर्णांक kvm_cmd_stat(स्थिर अक्षर *file_name, पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	काष्ठा perf_kvm_stat kvm = अणु
		.file_name = file_name,

		.trace_vcpu	= -1,
		.report_event	= "vmexit",
		.sort_key	= "sample",

	पूर्ण;

	अगर (argc == 1) अणु
		prपूर्णांक_kvm_stat_usage();
		जाओ perf_stat;
	पूर्ण

	अगर (!म_भेदन(argv[1], "rec", 3))
		वापस kvm_events_record(&kvm, argc - 1, argv + 1);

	अगर (!म_भेदन(argv[1], "rep", 3))
		वापस kvm_events_report(&kvm, argc - 1 , argv + 1);

#अगर_घोषित HAVE_TIMERFD_SUPPORT
	अगर (!म_भेदन(argv[1], "live", 4))
		वापस kvm_events_live(&kvm, argc - 1 , argv + 1);
#पूर्ण_अगर

perf_stat:
	वापस cmd_stat(argc, argv);
पूर्ण
#पूर्ण_अगर /* HAVE_KVM_STAT_SUPPORT */

पूर्णांक __weak kvm_add_शेष_arch_event(पूर्णांक *argc __maybe_unused,
					स्थिर अक्षर **argv __maybe_unused)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक __cmd_record(स्थिर अक्षर *file_name, पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक rec_argc, i = 0, j, ret;
	स्थिर अक्षर **rec_argv;

	ret = kvm_add_शेष_arch_event(&argc, argv);
	अगर (ret)
		वापस -EINVAL;

	rec_argc = argc + 2;
	rec_argv = सुस्मृति(rec_argc + 1, माप(अक्षर *));
	rec_argv[i++] = strdup("record");
	rec_argv[i++] = strdup("-o");
	rec_argv[i++] = strdup(file_name);
	क्रम (j = 1; j < argc; j++, i++)
		rec_argv[i] = argv[j];

	BUG_ON(i != rec_argc);

	वापस cmd_record(i, rec_argv);
पूर्ण

अटल पूर्णांक __cmd_report(स्थिर अक्षर *file_name, पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक rec_argc, i = 0, j;
	स्थिर अक्षर **rec_argv;

	rec_argc = argc + 2;
	rec_argv = सुस्मृति(rec_argc + 1, माप(अक्षर *));
	rec_argv[i++] = strdup("report");
	rec_argv[i++] = strdup("-i");
	rec_argv[i++] = strdup(file_name);
	क्रम (j = 1; j < argc; j++, i++)
		rec_argv[i] = argv[j];

	BUG_ON(i != rec_argc);

	वापस cmd_report(i, rec_argv);
पूर्ण

अटल पूर्णांक
__cmd_buildid_list(स्थिर अक्षर *file_name, पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	पूर्णांक rec_argc, i = 0, j;
	स्थिर अक्षर **rec_argv;

	rec_argc = argc + 2;
	rec_argv = सुस्मृति(rec_argc + 1, माप(अक्षर *));
	rec_argv[i++] = strdup("buildid-list");
	rec_argv[i++] = strdup("-i");
	rec_argv[i++] = strdup(file_name);
	क्रम (j = 1; j < argc; j++, i++)
		rec_argv[i] = argv[j];

	BUG_ON(i != rec_argc);

	वापस cmd_buildid_list(i, rec_argv);
पूर्ण

पूर्णांक cmd_kvm(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	स्थिर अक्षर *file_name = शून्य;
	स्थिर काष्ठा option kvm_options[] = अणु
		OPT_STRING('i', "input", &file_name, "file",
			   "Input file name"),
		OPT_STRING('o', "output", &file_name, "file",
			   "Output file name"),
		OPT_BOOLEAN(0, "guest", &perf_guest,
			    "Collect guest os data"),
		OPT_BOOLEAN(0, "host", &perf_host,
			    "Collect host os data"),
		OPT_STRING(0, "guestmount", &symbol_conf.guesपंचांगount, "directory",
			   "guest mount directory under which every guest os"
			   " instance has a subdir"),
		OPT_STRING(0, "guestvmlinux", &symbol_conf.शेष_guest_vmlinux_name,
			   "file", "file saving guest os vmlinux"),
		OPT_STRING(0, "guestkallsyms", &symbol_conf.शेष_guest_kallsyms,
			   "file", "file saving guest os /proc/kallsyms"),
		OPT_STRING(0, "guestmodules", &symbol_conf.शेष_guest_modules,
			   "file", "file saving guest os /proc/modules"),
		OPT_INCR('v', "verbose", &verbose,
			    "be more verbose (show counter open errors, etc)"),
		OPT_END()
	पूर्ण;

	स्थिर अक्षर *स्थिर kvm_subcommands[] = अणु "top", "record", "report", "diff",
						"buildid-list", "stat", शून्य पूर्ण;
	स्थिर अक्षर *kvm_usage[] = अणु शून्य, शून्य पूर्ण;

	perf_host  = 0;
	perf_guest = 1;

	argc = parse_options_subcommand(argc, argv, kvm_options, kvm_subcommands, kvm_usage,
					PARSE_OPT_STOP_AT_NON_OPTION);
	अगर (!argc)
		usage_with_options(kvm_usage, kvm_options);

	अगर (!perf_host)
		perf_guest = 1;

	अगर (!file_name) अणु
		file_name = get_filename_क्रम_perf_kvm();

		अगर (!file_name) अणु
			pr_err("Failed to allocate memory for filename\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर (!म_भेदन(argv[0], "rec", 3))
		वापस __cmd_record(file_name, argc, argv);
	अन्यथा अगर (!म_भेदन(argv[0], "rep", 3))
		वापस __cmd_report(file_name, argc, argv);
	अन्यथा अगर (!म_भेदन(argv[0], "diff", 4))
		वापस cmd_dअगरf(argc, argv);
	अन्यथा अगर (!म_भेदन(argv[0], "top", 3))
		वापस cmd_top(argc, argv);
	अन्यथा अगर (!म_भेदन(argv[0], "buildid-list", 12))
		वापस __cmd_buildid_list(file_name, argc, argv);
#अगर_घोषित HAVE_KVM_STAT_SUPPORT
	अन्यथा अगर (!म_भेदन(argv[0], "stat", 4))
		वापस kvm_cmd_stat(file_name, argc, argv);
#पूर्ण_अगर
	अन्यथा
		usage_with_options(kvm_usage, kvm_options);

	वापस 0;
पूर्ण
