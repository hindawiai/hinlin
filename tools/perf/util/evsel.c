<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 *
 * Parts came from builtin-अणुtop,stat,recordपूर्ण.c, see those files क्रम further
 * copyright notes.
 */

#समावेश <byteswap.h>
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <linux/bitops.h>
#समावेश <api/fs/fs.h>
#समावेश <api/fs/tracing_path.h>
#समावेश <traceevent/event-parse.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/compiler.h>
#समावेश <linux/err.h>
#समावेश <linux/zभाग.स>
#समावेश <sys/ioctl.h>
#समावेश <sys/resource.h>
#समावेश <sys/types.h>
#समावेश <dirent.h>
#समावेश <मानककोष.स>
#समावेश <perf/evsel.h>
#समावेश "asm/bug.h"
#समावेश "bpf_counter.h"
#समावेश "callchain.h"
#समावेश "cgroup.h"
#समावेश "counts.h"
#समावेश "event.h"
#समावेश "evsel.h"
#समावेश "util/env.h"
#समावेश "util/evsel_config.h"
#समावेश "util/evsel_fprintf.h"
#समावेश "evlist.h"
#समावेश <perf/cpumap.h>
#समावेश "thread_map.h"
#समावेश "target.h"
#समावेश "perf_regs.h"
#समावेश "record.h"
#समावेश "debug.h"
#समावेश "trace-event.h"
#समावेश "stat.h"
#समावेश "string2.h"
#समावेश "memswap.h"
#समावेश "util.h"
#समावेश "hashmap.h"
#समावेश "pmu-hybrid.h"
#समावेश "../perf-sys.h"
#समावेश "util/parse-branch-options.h"
#समावेश <पूर्णांकernal/xyarray.h>
#समावेश <पूर्णांकernal/lib.h>

#समावेश <linux/प्रकार.स>

काष्ठा perf_missing_features perf_missing_features;

अटल घड़ीid_t घड़ीid;

अटल पूर्णांक evsel__no_extra_init(काष्ठा evsel *evsel __maybe_unused)
अणु
	वापस 0;
पूर्ण

व्योम __weak test_attr__पढ़ोy(व्योम) अणु पूर्ण

अटल व्योम evsel__no_extra_fini(काष्ठा evsel *evsel __maybe_unused)
अणु
पूर्ण

अटल काष्ठा अणु
	माप_प्रकार	size;
	पूर्णांक	(*init)(काष्ठा evsel *evsel);
	व्योम	(*fini)(काष्ठा evsel *evsel);
पूर्ण perf_evsel__object = अणु
	.size = माप(काष्ठा evsel),
	.init = evsel__no_extra_init,
	.fini = evsel__no_extra_fini,
पूर्ण;

पूर्णांक evsel__object_config(माप_प्रकार object_size, पूर्णांक (*init)(काष्ठा evsel *evsel),
			 व्योम (*fini)(काष्ठा evsel *evsel))
अणु

	अगर (object_size == 0)
		जाओ set_methods;

	अगर (perf_evsel__object.size > object_size)
		वापस -EINVAL;

	perf_evsel__object.size = object_size;

set_methods:
	अगर (init != शून्य)
		perf_evsel__object.init = init;

	अगर (fini != शून्य)
		perf_evsel__object.fini = fini;

	वापस 0;
पूर्ण

#घोषणा FD(e, x, y) (*(पूर्णांक *)xyarray__entry(e->core.fd, x, y))

पूर्णांक __evsel__sample_size(u64 sample_type)
अणु
	u64 mask = sample_type & PERF_SAMPLE_MASK;
	पूर्णांक size = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 64; i++) अणु
		अगर (mask & (1ULL << i))
			size++;
	पूर्ण

	size *= माप(u64);

	वापस size;
पूर्ण

/**
 * __perf_evsel__calc_id_pos - calculate id_pos.
 * @sample_type: sample type
 *
 * This function वापसs the position of the event id (PERF_SAMPLE_ID or
 * PERF_SAMPLE_IDENTIFIER) in a sample event i.e. in the array of काष्ठा
 * perf_record_sample.
 */
अटल पूर्णांक __perf_evsel__calc_id_pos(u64 sample_type)
अणु
	पूर्णांक idx = 0;

	अगर (sample_type & PERF_SAMPLE_IDENTIFIER)
		वापस 0;

	अगर (!(sample_type & PERF_SAMPLE_ID))
		वापस -1;

	अगर (sample_type & PERF_SAMPLE_IP)
		idx += 1;

	अगर (sample_type & PERF_SAMPLE_TID)
		idx += 1;

	अगर (sample_type & PERF_SAMPLE_TIME)
		idx += 1;

	अगर (sample_type & PERF_SAMPLE_ADDR)
		idx += 1;

	वापस idx;
पूर्ण

/**
 * __perf_evsel__calc_is_pos - calculate is_pos.
 * @sample_type: sample type
 *
 * This function वापसs the position (counting backwards) of the event id
 * (PERF_SAMPLE_ID or PERF_SAMPLE_IDENTIFIER) in a non-sample event i.e. अगर
 * sample_id_all is used there is an id sample appended to non-sample events.
 */
अटल पूर्णांक __perf_evsel__calc_is_pos(u64 sample_type)
अणु
	पूर्णांक idx = 1;

	अगर (sample_type & PERF_SAMPLE_IDENTIFIER)
		वापस 1;

	अगर (!(sample_type & PERF_SAMPLE_ID))
		वापस -1;

	अगर (sample_type & PERF_SAMPLE_CPU)
		idx += 1;

	अगर (sample_type & PERF_SAMPLE_STREAM_ID)
		idx += 1;

	वापस idx;
पूर्ण

व्योम evsel__calc_id_pos(काष्ठा evsel *evsel)
अणु
	evsel->id_pos = __perf_evsel__calc_id_pos(evsel->core.attr.sample_type);
	evsel->is_pos = __perf_evsel__calc_is_pos(evsel->core.attr.sample_type);
पूर्ण

व्योम __evsel__set_sample_bit(काष्ठा evsel *evsel,
				  क्रमागत perf_event_sample_क्रमmat bit)
अणु
	अगर (!(evsel->core.attr.sample_type & bit)) अणु
		evsel->core.attr.sample_type |= bit;
		evsel->sample_size += माप(u64);
		evsel__calc_id_pos(evsel);
	पूर्ण
पूर्ण

व्योम __evsel__reset_sample_bit(काष्ठा evsel *evsel,
				    क्रमागत perf_event_sample_क्रमmat bit)
अणु
	अगर (evsel->core.attr.sample_type & bit) अणु
		evsel->core.attr.sample_type &= ~bit;
		evsel->sample_size -= माप(u64);
		evsel__calc_id_pos(evsel);
	पूर्ण
पूर्ण

व्योम evsel__set_sample_id(काष्ठा evsel *evsel,
			       bool can_sample_identअगरier)
अणु
	अगर (can_sample_identअगरier) अणु
		evsel__reset_sample_bit(evsel, ID);
		evsel__set_sample_bit(evsel, IDENTIFIER);
	पूर्ण अन्यथा अणु
		evsel__set_sample_bit(evsel, ID);
	पूर्ण
	evsel->core.attr.पढ़ो_क्रमmat |= PERF_FORMAT_ID;
पूर्ण

/**
 * evsel__is_function_event - Return whether given evsel is a function
 * trace event
 *
 * @evsel - evsel selector to be tested
 *
 * Return %true अगर event is function trace event
 */
bool evsel__is_function_event(काष्ठा evsel *evsel)
अणु
#घोषणा FUNCTION_EVENT "ftrace:function"

	वापस evsel->name &&
	       !म_भेदन(FUNCTION_EVENT, evsel->name, माप(FUNCTION_EVENT));

#अघोषित FUNCTION_EVENT
पूर्ण

व्योम evsel__init(काष्ठा evsel *evsel,
		 काष्ठा perf_event_attr *attr, पूर्णांक idx)
अणु
	perf_evsel__init(&evsel->core, attr);
	evsel->idx	   = idx;
	evsel->tracking	   = !idx;
	evsel->leader	   = evsel;
	evsel->unit	   = "";
	evsel->scale	   = 1.0;
	evsel->max_events  = अच_दीर्घ_उच्च;
	evsel->evlist	   = शून्य;
	evsel->bpf_obj	   = शून्य;
	evsel->bpf_fd	   = -1;
	INIT_LIST_HEAD(&evsel->config_terms);
	INIT_LIST_HEAD(&evsel->bpf_counter_list);
	perf_evsel__object.init(evsel);
	evsel->sample_size = __evsel__sample_size(attr->sample_type);
	evsel__calc_id_pos(evsel);
	evsel->cmdline_group_boundary = false;
	evsel->metric_expr   = शून्य;
	evsel->metric_name   = शून्य;
	evsel->metric_events = शून्य;
	evsel->per_pkg_mask  = शून्य;
	evsel->collect_stat  = false;
	evsel->pmu_name      = शून्य;
पूर्ण

काष्ठा evsel *evsel__new_idx(काष्ठा perf_event_attr *attr, पूर्णांक idx)
अणु
	काष्ठा evsel *evsel = zalloc(perf_evsel__object.size);

	अगर (!evsel)
		वापस शून्य;
	evsel__init(evsel, attr, idx);

	अगर (evsel__is_bpf_output(evsel)) अणु
		evsel->core.attr.sample_type |= (PERF_SAMPLE_RAW | PERF_SAMPLE_TIME |
					    PERF_SAMPLE_CPU | PERF_SAMPLE_PERIOD),
		evsel->core.attr.sample_period = 1;
	पूर्ण

	अगर (evsel__is_घड़ी(evsel)) अणु
		/*
		 * The evsel->unit poपूर्णांकs to अटल alias->unit
		 * so it's ok to use अटल string in here.
		 */
		अटल स्थिर अक्षर *unit = "msec";

		evsel->unit = unit;
		evsel->scale = 1e-6;
	पूर्ण

	वापस evsel;
पूर्ण

अटल bool perf_event_can_profile_kernel(व्योम)
अणु
	वापस perf_event_paranoid_check(1);
पूर्ण

काष्ठा evsel *evsel__new_cycles(bool precise, __u32 type, __u64 config)
अणु
	काष्ठा perf_event_attr attr = अणु
		.type	= type,
		.config	= config,
		.exclude_kernel	= !perf_event_can_profile_kernel(),
	पूर्ण;
	काष्ठा evsel *evsel;

	event_attr_init(&attr);

	अगर (!precise)
		जाओ new_event;

	/*
	 * Now let the usual logic to set up the perf_event_attr शेषs
	 * to kick in when we वापस and beक्रमe perf_evsel__खोलो() is called.
	 */
new_event:
	evsel = evsel__new(&attr);
	अगर (evsel == शून्य)
		जाओ out;

	evsel->precise_max = true;

	/* use aप्र_लिखो() because मुक्त(evsel) assumes name is allocated */
	अगर (aप्र_लिखो(&evsel->name, "cycles%s%s%.*s",
		     (attr.precise_ip || attr.exclude_kernel) ? ":" : "",
		     attr.exclude_kernel ? "u" : "",
		     attr.precise_ip ? attr.precise_ip + 1 : 0, "ppp") < 0)
		जाओ error_मुक्त;
out:
	वापस evsel;
error_मुक्त:
	evsel__delete(evsel);
	evsel = शून्य;
	जाओ out;
पूर्ण

अटल पूर्णांक evsel__copy_config_terms(काष्ठा evsel *dst, काष्ठा evsel *src)
अणु
	काष्ठा evsel_config_term *pos, *पंचांगp;

	list_क्रम_each_entry(pos, &src->config_terms, list) अणु
		पंचांगp = दो_स्मृति(माप(*पंचांगp));
		अगर (पंचांगp == शून्य)
			वापस -ENOMEM;

		*पंचांगp = *pos;
		अगर (पंचांगp->मुक्त_str) अणु
			पंचांगp->val.str = strdup(pos->val.str);
			अगर (पंचांगp->val.str == शून्य) अणु
				मुक्त(पंचांगp);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण
		list_add_tail(&पंचांगp->list, &dst->config_terms);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * evsel__clone - create a new evsel copied from @orig
 * @orig: original evsel
 *
 * The assumption is that @orig is not configured nor खोलोed yet.
 * So we only care about the attributes that can be set जबतक it's parsed.
 */
काष्ठा evsel *evsel__clone(काष्ठा evsel *orig)
अणु
	काष्ठा evsel *evsel;

	BUG_ON(orig->core.fd);
	BUG_ON(orig->counts);
	BUG_ON(orig->priv);
	BUG_ON(orig->per_pkg_mask);

	/* cannot handle BPF objects क्रम now */
	अगर (orig->bpf_obj)
		वापस शून्य;

	evsel = evsel__new(&orig->core.attr);
	अगर (evsel == शून्य)
		वापस शून्य;

	evsel->core.cpus = perf_cpu_map__get(orig->core.cpus);
	evsel->core.own_cpus = perf_cpu_map__get(orig->core.own_cpus);
	evsel->core.thपढ़ोs = perf_thपढ़ो_map__get(orig->core.thपढ़ोs);
	evsel->core.nr_members = orig->core.nr_members;
	evsel->core.प्रणाली_wide = orig->core.प्रणाली_wide;

	अगर (orig->name) अणु
		evsel->name = strdup(orig->name);
		अगर (evsel->name == शून्य)
			जाओ out_err;
	पूर्ण
	अगर (orig->group_name) अणु
		evsel->group_name = strdup(orig->group_name);
		अगर (evsel->group_name == शून्य)
			जाओ out_err;
	पूर्ण
	अगर (orig->pmu_name) अणु
		evsel->pmu_name = strdup(orig->pmu_name);
		अगर (evsel->pmu_name == शून्य)
			जाओ out_err;
	पूर्ण
	अगर (orig->filter) अणु
		evsel->filter = strdup(orig->filter);
		अगर (evsel->filter == शून्य)
			जाओ out_err;
	पूर्ण
	evsel->cgrp = cgroup__get(orig->cgrp);
	evsel->tp_क्रमmat = orig->tp_क्रमmat;
	evsel->handler = orig->handler;
	evsel->leader = orig->leader;

	evsel->max_events = orig->max_events;
	evsel->tool_event = orig->tool_event;
	evsel->unit = orig->unit;
	evsel->scale = orig->scale;
	evsel->snapshot = orig->snapshot;
	evsel->per_pkg = orig->per_pkg;
	evsel->percore = orig->percore;
	evsel->precise_max = orig->precise_max;
	evsel->use_uncore_alias = orig->use_uncore_alias;
	evsel->is_libpfm_event = orig->is_libpfm_event;

	evsel->exclude_GH = orig->exclude_GH;
	evsel->sample_पढ़ो = orig->sample_पढ़ो;
	evsel->स्वतः_merge_stats = orig->स्वतः_merge_stats;
	evsel->collect_stat = orig->collect_stat;
	evsel->weak_group = orig->weak_group;
	evsel->use_config_name = orig->use_config_name;

	अगर (evsel__copy_config_terms(evsel, orig) < 0)
		जाओ out_err;

	वापस evsel;

out_err:
	evsel__delete(evsel);
	वापस शून्य;
पूर्ण

/*
 * Returns poपूर्णांकer with encoded error via <linux/err.h> पूर्णांकerface.
 */
काष्ठा evsel *evsel__newtp_idx(स्थिर अक्षर *sys, स्थिर अक्षर *name, पूर्णांक idx)
अणु
	काष्ठा evsel *evsel = zalloc(perf_evsel__object.size);
	पूर्णांक err = -ENOMEM;

	अगर (evsel == शून्य) अणु
		जाओ out_err;
	पूर्ण अन्यथा अणु
		काष्ठा perf_event_attr attr = अणु
			.type	       = PERF_TYPE_TRACEPOINT,
			.sample_type   = (PERF_SAMPLE_RAW | PERF_SAMPLE_TIME |
					  PERF_SAMPLE_CPU | PERF_SAMPLE_PERIOD),
		पूर्ण;

		अगर (aप्र_लिखो(&evsel->name, "%s:%s", sys, name) < 0)
			जाओ out_मुक्त;

		evsel->tp_क्रमmat = trace_event__tp_क्रमmat(sys, name);
		अगर (IS_ERR(evsel->tp_क्रमmat)) अणु
			err = PTR_ERR(evsel->tp_क्रमmat);
			जाओ out_मुक्त;
		पूर्ण

		event_attr_init(&attr);
		attr.config = evsel->tp_क्रमmat->id;
		attr.sample_period = 1;
		evsel__init(evsel, &attr, idx);
	पूर्ण

	वापस evsel;

out_मुक्त:
	zमुक्त(&evsel->name);
	मुक्त(evsel);
out_err:
	वापस ERR_PTR(err);
पूर्ण

स्थिर अक्षर *evsel__hw_names[PERF_COUNT_HW_MAX] = अणु
	"cycles",
	"instructions",
	"cache-references",
	"cache-misses",
	"branches",
	"branch-misses",
	"bus-cycles",
	"stalled-cycles-frontend",
	"stalled-cycles-backend",
	"ref-cycles",
पूर्ण;

अक्षर *evsel__bpf_counter_events;

bool evsel__match_bpf_counter_events(स्थिर अक्षर *name)
अणु
	पूर्णांक name_len;
	bool match;
	अक्षर *ptr;

	अगर (!evsel__bpf_counter_events)
		वापस false;

	ptr = म_माला(evsel__bpf_counter_events, name);
	name_len = म_माप(name);

	/* check name matches a full token in evsel__bpf_counter_events */
	match = (ptr != शून्य) &&
		((ptr == evsel__bpf_counter_events) || (*(ptr - 1) == ',')) &&
		((*(ptr + name_len) == ',') || (*(ptr + name_len) == '\0'));

	वापस match;
पूर्ण

अटल स्थिर अक्षर *__evsel__hw_name(u64 config)
अणु
	अगर (config < PERF_COUNT_HW_MAX && evsel__hw_names[config])
		वापस evsel__hw_names[config];

	वापस "unknown-hardware";
पूर्ण

अटल पूर्णांक evsel__add_modअगरiers(काष्ठा evsel *evsel, अक्षर *bf, माप_प्रकार size)
अणु
	पूर्णांक colon = 0, r = 0;
	काष्ठा perf_event_attr *attr = &evsel->core.attr;
	bool exclude_guest_शेष = false;

#घोषणा MOD_PRINT(context, mod)	करो अणु					\
		अगर (!attr->exclude_##context) अणु				\
			अगर (!colon) colon = ++r;			\
			r += scnम_लिखो(bf + r, size - r, "%c", mod);	\
		पूर्ण पूर्ण जबतक(0)

	अगर (attr->exclude_kernel || attr->exclude_user || attr->exclude_hv) अणु
		MOD_PRINT(kernel, 'k');
		MOD_PRINT(user, 'u');
		MOD_PRINT(hv, 'h');
		exclude_guest_शेष = true;
	पूर्ण

	अगर (attr->precise_ip) अणु
		अगर (!colon)
			colon = ++r;
		r += scnम_लिखो(bf + r, size - r, "%.*s", attr->precise_ip, "ppp");
		exclude_guest_शेष = true;
	पूर्ण

	अगर (attr->exclude_host || attr->exclude_guest == exclude_guest_शेष) अणु
		MOD_PRINT(host, 'H');
		MOD_PRINT(guest, 'G');
	पूर्ण
#अघोषित MOD_PRINT
	अगर (colon)
		bf[colon - 1] = ':';
	वापस r;
पूर्ण

अटल पूर्णांक evsel__hw_name(काष्ठा evsel *evsel, अक्षर *bf, माप_प्रकार size)
अणु
	पूर्णांक r = scnम_लिखो(bf, size, "%s", __evsel__hw_name(evsel->core.attr.config));
	वापस r + evsel__add_modअगरiers(evsel, bf + r, size - r);
पूर्ण

स्थिर अक्षर *evsel__sw_names[PERF_COUNT_SW_MAX] = अणु
	"cpu-clock",
	"task-clock",
	"page-faults",
	"context-switches",
	"cpu-migrations",
	"minor-faults",
	"major-faults",
	"alignment-faults",
	"emulation-faults",
	"dummy",
पूर्ण;

अटल स्थिर अक्षर *__evsel__sw_name(u64 config)
अणु
	अगर (config < PERF_COUNT_SW_MAX && evsel__sw_names[config])
		वापस evsel__sw_names[config];
	वापस "unknown-software";
पूर्ण

अटल पूर्णांक evsel__sw_name(काष्ठा evsel *evsel, अक्षर *bf, माप_प्रकार size)
अणु
	पूर्णांक r = scnम_लिखो(bf, size, "%s", __evsel__sw_name(evsel->core.attr.config));
	वापस r + evsel__add_modअगरiers(evsel, bf + r, size - r);
पूर्ण

अटल पूर्णांक __evsel__bp_name(अक्षर *bf, माप_प्रकार size, u64 addr, u64 type)
अणु
	पूर्णांक r;

	r = scnम_लिखो(bf, size, "mem:0x%" PRIx64 ":", addr);

	अगर (type & HW_BREAKPOINT_R)
		r += scnम_लिखो(bf + r, size - r, "r");

	अगर (type & HW_BREAKPOINT_W)
		r += scnम_लिखो(bf + r, size - r, "w");

	अगर (type & HW_BREAKPOINT_X)
		r += scnम_लिखो(bf + r, size - r, "x");

	वापस r;
पूर्ण

अटल पूर्णांक evsel__bp_name(काष्ठा evsel *evsel, अक्षर *bf, माप_प्रकार size)
अणु
	काष्ठा perf_event_attr *attr = &evsel->core.attr;
	पूर्णांक r = __evsel__bp_name(bf, size, attr->bp_addr, attr->bp_type);
	वापस r + evsel__add_modअगरiers(evsel, bf + r, size - r);
पूर्ण

स्थिर अक्षर *evsel__hw_cache[PERF_COUNT_HW_CACHE_MAX][EVSEL__MAX_ALIASES] = अणु
 अणु "L1-dcache",	"l1-d",		"l1d",		"L1-data",		पूर्ण,
 अणु "L1-icache",	"l1-i",		"l1i",		"L1-instruction",	पूर्ण,
 अणु "LLC",	"L2",							पूर्ण,
 अणु "dTLB",	"d-tlb",	"Data-TLB",				पूर्ण,
 अणु "iTLB",	"i-tlb",	"Instruction-TLB",			पूर्ण,
 अणु "branch",	"branches",	"bpu",		"btb",		"bpc",	पूर्ण,
 अणु "node",								पूर्ण,
पूर्ण;

स्थिर अक्षर *evsel__hw_cache_op[PERF_COUNT_HW_CACHE_OP_MAX][EVSEL__MAX_ALIASES] = अणु
 अणु "load",	"loads",	"read",					पूर्ण,
 अणु "store",	"stores",	"write",				पूर्ण,
 अणु "prefetch",	"prefetches",	"speculative-read", "speculative-load",	पूर्ण,
पूर्ण;

स्थिर अक्षर *evsel__hw_cache_result[PERF_COUNT_HW_CACHE_RESULT_MAX][EVSEL__MAX_ALIASES] = अणु
 अणु "refs",	"Reference",	"ops",		"access",		पूर्ण,
 अणु "misses",	"miss",							पूर्ण,
पूर्ण;

#घोषणा C(x)		PERF_COUNT_HW_CACHE_##x
#घोषणा CACHE_READ	(1 << C(OP_READ))
#घोषणा CACHE_WRITE	(1 << C(OP_WRITE))
#घोषणा CACHE_PREFETCH	(1 << C(OP_PREFETCH))
#घोषणा COP(x)		(1 << x)

/*
 * cache operation stat
 * L1I : Read and prefetch only
 * ITLB and BPU : Read-only
 */
अटल अचिन्हित दीर्घ evsel__hw_cache_stat[C(MAX)] = अणु
 [C(L1D)]	= (CACHE_READ | CACHE_WRITE | CACHE_PREFETCH),
 [C(L1I)]	= (CACHE_READ | CACHE_PREFETCH),
 [C(LL)]	= (CACHE_READ | CACHE_WRITE | CACHE_PREFETCH),
 [C(DTLB)]	= (CACHE_READ | CACHE_WRITE | CACHE_PREFETCH),
 [C(ITLB)]	= (CACHE_READ),
 [C(BPU)]	= (CACHE_READ),
 [C(NODE)]	= (CACHE_READ | CACHE_WRITE | CACHE_PREFETCH),
पूर्ण;

bool evsel__is_cache_op_valid(u8 type, u8 op)
अणु
	अगर (evsel__hw_cache_stat[type] & COP(op))
		वापस true;	/* valid */
	अन्यथा
		वापस false;	/* invalid */
पूर्ण

पूर्णांक __evsel__hw_cache_type_op_res_name(u8 type, u8 op, u8 result, अक्षर *bf, माप_प्रकार size)
अणु
	अगर (result) अणु
		वापस scnम_लिखो(bf, size, "%s-%s-%s", evsel__hw_cache[type][0],
				 evsel__hw_cache_op[op][0],
				 evsel__hw_cache_result[result][0]);
	पूर्ण

	वापस scnम_लिखो(bf, size, "%s-%s", evsel__hw_cache[type][0],
			 evsel__hw_cache_op[op][1]);
पूर्ण

अटल पूर्णांक __evsel__hw_cache_name(u64 config, अक्षर *bf, माप_प्रकार size)
अणु
	u8 op, result, type = (config >>  0) & 0xff;
	स्थिर अक्षर *err = "unknown-ext-hardware-cache-type";

	अगर (type >= PERF_COUNT_HW_CACHE_MAX)
		जाओ out_err;

	op = (config >>  8) & 0xff;
	err = "unknown-ext-hardware-cache-op";
	अगर (op >= PERF_COUNT_HW_CACHE_OP_MAX)
		जाओ out_err;

	result = (config >> 16) & 0xff;
	err = "unknown-ext-hardware-cache-result";
	अगर (result >= PERF_COUNT_HW_CACHE_RESULT_MAX)
		जाओ out_err;

	err = "invalid-cache";
	अगर (!evsel__is_cache_op_valid(type, op))
		जाओ out_err;

	वापस __evsel__hw_cache_type_op_res_name(type, op, result, bf, size);
out_err:
	वापस scnम_लिखो(bf, size, "%s", err);
पूर्ण

अटल पूर्णांक evsel__hw_cache_name(काष्ठा evsel *evsel, अक्षर *bf, माप_प्रकार size)
अणु
	पूर्णांक ret = __evsel__hw_cache_name(evsel->core.attr.config, bf, size);
	वापस ret + evsel__add_modअगरiers(evsel, bf + ret, size - ret);
पूर्ण

अटल पूर्णांक evsel__raw_name(काष्ठा evsel *evsel, अक्षर *bf, माप_प्रकार size)
अणु
	पूर्णांक ret = scnम_लिखो(bf, size, "raw 0x%" PRIx64, evsel->core.attr.config);
	वापस ret + evsel__add_modअगरiers(evsel, bf + ret, size - ret);
पूर्ण

अटल पूर्णांक evsel__tool_name(अक्षर *bf, माप_प्रकार size)
अणु
	पूर्णांक ret = scnम_लिखो(bf, size, "duration_time");
	वापस ret;
पूर्ण

स्थिर अक्षर *evsel__name(काष्ठा evsel *evsel)
अणु
	अक्षर bf[128];

	अगर (!evsel)
		जाओ out_unknown;

	अगर (evsel->name)
		वापस evsel->name;

	चयन (evsel->core.attr.type) अणु
	हाल PERF_TYPE_RAW:
		evsel__raw_name(evsel, bf, माप(bf));
		अवरोध;

	हाल PERF_TYPE_HARDWARE:
		evsel__hw_name(evsel, bf, माप(bf));
		अवरोध;

	हाल PERF_TYPE_HW_CACHE:
		evsel__hw_cache_name(evsel, bf, माप(bf));
		अवरोध;

	हाल PERF_TYPE_SOFTWARE:
		अगर (evsel->tool_event)
			evsel__tool_name(bf, माप(bf));
		अन्यथा
			evsel__sw_name(evsel, bf, माप(bf));
		अवरोध;

	हाल PERF_TYPE_TRACEPOINT:
		scnम_लिखो(bf, माप(bf), "%s", "unknown tracepoint");
		अवरोध;

	हाल PERF_TYPE_BREAKPOINT:
		evsel__bp_name(evsel, bf, माप(bf));
		अवरोध;

	शेष:
		scnम_लिखो(bf, माप(bf), "unknown attr type: %d",
			  evsel->core.attr.type);
		अवरोध;
	पूर्ण

	evsel->name = strdup(bf);

	अगर (evsel->name)
		वापस evsel->name;
out_unknown:
	वापस "unknown";
पूर्ण

स्थिर अक्षर *evsel__group_name(काष्ठा evsel *evsel)
अणु
	वापस evsel->group_name ?: "anon group";
पूर्ण

/*
 * Returns the group details क्रम the specअगरied leader,
 * with following rules.
 *
 *  For record -e '{cycles,instructions}'
 *    'anon group { cycles:u, instructions:u }'
 *
 *  For record -e 'cycles,instructions' and report --group
 *    'cycles:u, instructions:u'
 */
पूर्णांक evsel__group_desc(काष्ठा evsel *evsel, अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक ret = 0;
	काष्ठा evsel *pos;
	स्थिर अक्षर *group_name = evsel__group_name(evsel);

	अगर (!evsel->क्रमced_leader)
		ret = scnम_लिखो(buf, size, "%s { ", group_name);

	ret += scnम_लिखो(buf + ret, size - ret, "%s", evsel__name(evsel));

	क्रम_each_group_member(pos, evsel)
		ret += scnम_लिखो(buf + ret, size - ret, ", %s", evsel__name(pos));

	अगर (!evsel->क्रमced_leader)
		ret += scnम_लिखो(buf + ret, size - ret, " }");

	वापस ret;
पूर्ण

अटल व्योम __evsel__config_callchain(काष्ठा evsel *evsel, काष्ठा record_opts *opts,
				      काष्ठा callchain_param *param)
अणु
	bool function = evsel__is_function_event(evsel);
	काष्ठा perf_event_attr *attr = &evsel->core.attr;

	evsel__set_sample_bit(evsel, CALLCHAIN);

	attr->sample_max_stack = param->max_stack;

	अगर (opts->kernel_callchains)
		attr->exclude_callchain_user = 1;
	अगर (opts->user_callchains)
		attr->exclude_callchain_kernel = 1;
	अगर (param->record_mode == CALLCHAIN_LBR) अणु
		अगर (!opts->branch_stack) अणु
			अगर (attr->exclude_user) अणु
				pr_warning("LBR callstack option is only available "
					   "to get user callchain information. "
					   "Falling back to framepointers.\n");
			पूर्ण अन्यथा अणु
				evsel__set_sample_bit(evsel, BRANCH_STACK);
				attr->branch_sample_type = PERF_SAMPLE_BRANCH_USER |
							PERF_SAMPLE_BRANCH_CALL_STACK |
							PERF_SAMPLE_BRANCH_NO_CYCLES |
							PERF_SAMPLE_BRANCH_NO_FLAGS |
							PERF_SAMPLE_BRANCH_HW_INDEX;
			पूर्ण
		पूर्ण अन्यथा
			 pr_warning("Cannot use LBR callstack with branch stack. "
				    "Falling back to framepointers.\n");
	पूर्ण

	अगर (param->record_mode == CALLCHAIN_DWARF) अणु
		अगर (!function) अणु
			evsel__set_sample_bit(evsel, REGS_USER);
			evsel__set_sample_bit(evsel, STACK_USER);
			अगर (opts->sample_user_regs && DWARF_MINIMAL_REGS != PERF_REGS_MASK) अणु
				attr->sample_regs_user |= DWARF_MINIMAL_REGS;
				pr_warning("WARNING: The use of --call-graph=dwarf may require all the user registers, "
					   "specifying a subset with --user-regs may render DWARF unwinding unreliable, "
					   "so the minimal registers set (IP, SP) is explicitly forced.\n");
			पूर्ण अन्यथा अणु
				attr->sample_regs_user |= PERF_REGS_MASK;
			पूर्ण
			attr->sample_stack_user = param->dump_size;
			attr->exclude_callchain_user = 1;
		पूर्ण अन्यथा अणु
			pr_info("Cannot use DWARF unwind for function trace event,"
				" falling back to framepointers.\n");
		पूर्ण
	पूर्ण

	अगर (function) अणु
		pr_info("Disabling user space callchains for function trace event.\n");
		attr->exclude_callchain_user = 1;
	पूर्ण
पूर्ण

व्योम evsel__config_callchain(काष्ठा evsel *evsel, काष्ठा record_opts *opts,
			     काष्ठा callchain_param *param)
अणु
	अगर (param->enabled)
		वापस __evsel__config_callchain(evsel, opts, param);
पूर्ण

अटल व्योम evsel__reset_callgraph(काष्ठा evsel *evsel, काष्ठा callchain_param *param)
अणु
	काष्ठा perf_event_attr *attr = &evsel->core.attr;

	evsel__reset_sample_bit(evsel, CALLCHAIN);
	अगर (param->record_mode == CALLCHAIN_LBR) अणु
		evsel__reset_sample_bit(evsel, BRANCH_STACK);
		attr->branch_sample_type &= ~(PERF_SAMPLE_BRANCH_USER |
					      PERF_SAMPLE_BRANCH_CALL_STACK |
					      PERF_SAMPLE_BRANCH_HW_INDEX);
	पूर्ण
	अगर (param->record_mode == CALLCHAIN_DWARF) अणु
		evsel__reset_sample_bit(evsel, REGS_USER);
		evsel__reset_sample_bit(evsel, STACK_USER);
	पूर्ण
पूर्ण

अटल व्योम evsel__apply_config_terms(काष्ठा evsel *evsel,
				      काष्ठा record_opts *opts, bool track)
अणु
	काष्ठा evsel_config_term *term;
	काष्ठा list_head *config_terms = &evsel->config_terms;
	काष्ठा perf_event_attr *attr = &evsel->core.attr;
	/* callgraph शेष */
	काष्ठा callchain_param param = अणु
		.record_mode = callchain_param.record_mode,
	पूर्ण;
	u32 dump_size = 0;
	पूर्णांक max_stack = 0;
	स्थिर अक्षर *callgraph_buf = शून्य;

	list_क्रम_each_entry(term, config_terms, list) अणु
		चयन (term->type) अणु
		हाल EVSEL__CONFIG_TERM_PERIOD:
			अगर (!(term->weak && opts->user_पूर्णांकerval != ULदीर्घ_उच्च)) अणु
				attr->sample_period = term->val.period;
				attr->freq = 0;
				evsel__reset_sample_bit(evsel, PERIOD);
			पूर्ण
			अवरोध;
		हाल EVSEL__CONFIG_TERM_FREQ:
			अगर (!(term->weak && opts->user_freq != अच_पूर्णांक_उच्च)) अणु
				attr->sample_freq = term->val.freq;
				attr->freq = 1;
				evsel__set_sample_bit(evsel, PERIOD);
			पूर्ण
			अवरोध;
		हाल EVSEL__CONFIG_TERM_TIME:
			अगर (term->val.समय)
				evsel__set_sample_bit(evsel, TIME);
			अन्यथा
				evsel__reset_sample_bit(evsel, TIME);
			अवरोध;
		हाल EVSEL__CONFIG_TERM_CALLGRAPH:
			callgraph_buf = term->val.str;
			अवरोध;
		हाल EVSEL__CONFIG_TERM_BRANCH:
			अगर (term->val.str && म_भेद(term->val.str, "no")) अणु
				evsel__set_sample_bit(evsel, BRANCH_STACK);
				parse_branch_str(term->val.str,
						 &attr->branch_sample_type);
			पूर्ण अन्यथा
				evsel__reset_sample_bit(evsel, BRANCH_STACK);
			अवरोध;
		हाल EVSEL__CONFIG_TERM_STACK_USER:
			dump_size = term->val.stack_user;
			अवरोध;
		हाल EVSEL__CONFIG_TERM_MAX_STACK:
			max_stack = term->val.max_stack;
			अवरोध;
		हाल EVSEL__CONFIG_TERM_MAX_EVENTS:
			evsel->max_events = term->val.max_events;
			अवरोध;
		हाल EVSEL__CONFIG_TERM_INHERIT:
			/*
			 * attr->inherit should has alपढ़ोy been set by
			 * evsel__config. If user explicitly set
			 * inherit using config terms, override global
			 * opt->no_inherit setting.
			 */
			attr->inherit = term->val.inherit ? 1 : 0;
			अवरोध;
		हाल EVSEL__CONFIG_TERM_OVERWRITE:
			attr->ग_लिखो_backward = term->val.overग_लिखो ? 1 : 0;
			अवरोध;
		हाल EVSEL__CONFIG_TERM_DRV_CFG:
			अवरोध;
		हाल EVSEL__CONFIG_TERM_PERCORE:
			अवरोध;
		हाल EVSEL__CONFIG_TERM_AUX_OUTPUT:
			attr->aux_output = term->val.aux_output ? 1 : 0;
			अवरोध;
		हाल EVSEL__CONFIG_TERM_AUX_SAMPLE_SIZE:
			/* Alपढ़ोy applied by auxtrace */
			अवरोध;
		हाल EVSEL__CONFIG_TERM_CFG_CHG:
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* User explicitly set per-event callgraph, clear the old setting and reset. */
	अगर ((callgraph_buf != शून्य) || (dump_size > 0) || max_stack) अणु
		bool sample_address = false;

		अगर (max_stack) अणु
			param.max_stack = max_stack;
			अगर (callgraph_buf == शून्य)
				callgraph_buf = "fp";
		पूर्ण

		/* parse callgraph parameters */
		अगर (callgraph_buf != शून्य) अणु
			अगर (!म_भेद(callgraph_buf, "no")) अणु
				param.enabled = false;
				param.record_mode = CALLCHAIN_NONE;
			पूर्ण अन्यथा अणु
				param.enabled = true;
				अगर (parse_callchain_record(callgraph_buf, &param)) अणु
					pr_err("per-event callgraph setting for %s failed. "
					       "Apply callgraph global setting for it\n",
					       evsel->name);
					वापस;
				पूर्ण
				अगर (param.record_mode == CALLCHAIN_DWARF)
					sample_address = true;
			पूर्ण
		पूर्ण
		अगर (dump_size > 0) अणु
			dump_size = round_up(dump_size, माप(u64));
			param.dump_size = dump_size;
		पूर्ण

		/* If global callgraph set, clear it */
		अगर (callchain_param.enabled)
			evsel__reset_callgraph(evsel, &callchain_param);

		/* set perf-event callgraph */
		अगर (param.enabled) अणु
			अगर (sample_address) अणु
				evsel__set_sample_bit(evsel, ADDR);
				evsel__set_sample_bit(evsel, DATA_SRC);
				evsel->core.attr.mmap_data = track;
			पूर्ण
			evsel__config_callchain(evsel, opts, &param);
		पूर्ण
	पूर्ण
पूर्ण

काष्ठा evsel_config_term *__evsel__get_config_term(काष्ठा evsel *evsel, क्रमागत evsel_term_type type)
अणु
	काष्ठा evsel_config_term *term, *found_term = शून्य;

	list_क्रम_each_entry(term, &evsel->config_terms, list) अणु
		अगर (term->type == type)
			found_term = term;
	पूर्ण

	वापस found_term;
पूर्ण

व्योम __weak arch_evsel__set_sample_weight(काष्ठा evsel *evsel)
अणु
	evsel__set_sample_bit(evsel, WEIGHT);
पूर्ण

/*
 * The enable_on_exec/disabled value strategy:
 *
 *  1) For any type of traced program:
 *    - all independent events and group leaders are disabled
 *    - all group members are enabled
 *
 *     Group members are ruled by group leaders. They need to
 *     be enabled, because the group scheduling relies on that.
 *
 *  2) For traced programs executed by perf:
 *     - all independent events and group leaders have
 *       enable_on_exec set
 *     - we करोn't specअगरically enable or disable any event during
 *       the record command
 *
 *     Independent events and group leaders are initially disabled
 *     and get enabled by exec. Group members are ruled by group
 *     leaders as stated in 1).
 *
 *  3) For traced programs attached by perf (pid/tid):
 *     - we specअगरically enable or disable all events during
 *       the record command
 *
 *     When attaching events to alपढ़ोy running traced we
 *     enable/disable events specअगरically, as there's no
 *     initial traced exec call.
 */
व्योम evsel__config(काष्ठा evsel *evsel, काष्ठा record_opts *opts,
		   काष्ठा callchain_param *callchain)
अणु
	काष्ठा evsel *leader = evsel->leader;
	काष्ठा perf_event_attr *attr = &evsel->core.attr;
	पूर्णांक track = evsel->tracking;
	bool per_cpu = opts->target.शेष_per_cpu && !opts->target.per_thपढ़ो;

	attr->sample_id_all = perf_missing_features.sample_id_all ? 0 : 1;
	attr->inherit	    = !opts->no_inherit;
	attr->ग_लिखो_backward = opts->overग_लिखो ? 1 : 0;

	evsel__set_sample_bit(evsel, IP);
	evsel__set_sample_bit(evsel, TID);

	अगर (evsel->sample_पढ़ो) अणु
		evsel__set_sample_bit(evsel, READ);

		/*
		 * We need ID even in हाल of single event, because
		 * PERF_SAMPLE_READ process ID specअगरic data.
		 */
		evsel__set_sample_id(evsel, false);

		/*
		 * Apply group क्रमmat only अगर we beदीर्घ to group
		 * with more than one members.
		 */
		अगर (leader->core.nr_members > 1) अणु
			attr->पढ़ो_क्रमmat |= PERF_FORMAT_GROUP;
			attr->inherit = 0;
		पूर्ण
	पूर्ण

	/*
	 * We शेष some events to have a शेष पूर्णांकerval. But keep
	 * it a weak assumption overridable by the user.
	 */
	अगर (!attr->sample_period) अणु
		अगर (opts->freq) अणु
			attr->freq		= 1;
			attr->sample_freq	= opts->freq;
		पूर्ण अन्यथा अणु
			attr->sample_period = opts->शेष_पूर्णांकerval;
		पूर्ण
	पूर्ण
	/*
	 * If attr->freq was set (here or earlier), ask क्रम period
	 * to be sampled.
	 */
	अगर (attr->freq)
		evsel__set_sample_bit(evsel, PERIOD);

	अगर (opts->no_samples)
		attr->sample_freq = 0;

	अगर (opts->inherit_stat) अणु
		evsel->core.attr.पढ़ो_क्रमmat |=
			PERF_FORMAT_TOTAL_TIME_ENABLED |
			PERF_FORMAT_TOTAL_TIME_RUNNING |
			PERF_FORMAT_ID;
		attr->inherit_stat = 1;
	पूर्ण

	अगर (opts->sample_address) अणु
		evsel__set_sample_bit(evsel, ADDR);
		attr->mmap_data = track;
	पूर्ण

	/*
	 * We करोn't allow user space callchains क्रम  function trace
	 * event, due to issues with page faults जबतक tracing page
	 * fault handler and its overall trickiness nature.
	 */
	अगर (evsel__is_function_event(evsel))
		evsel->core.attr.exclude_callchain_user = 1;

	अगर (callchain && callchain->enabled && !evsel->no_aux_samples)
		evsel__config_callchain(evsel, opts, callchain);

	अगर (opts->sample_पूर्णांकr_regs && !evsel->no_aux_samples &&
	    !evsel__is_dummy_event(evsel)) अणु
		attr->sample_regs_पूर्णांकr = opts->sample_पूर्णांकr_regs;
		evsel__set_sample_bit(evsel, REGS_INTR);
	पूर्ण

	अगर (opts->sample_user_regs && !evsel->no_aux_samples &&
	    !evsel__is_dummy_event(evsel)) अणु
		attr->sample_regs_user |= opts->sample_user_regs;
		evsel__set_sample_bit(evsel, REGS_USER);
	पूर्ण

	अगर (target__has_cpu(&opts->target) || opts->sample_cpu)
		evsel__set_sample_bit(evsel, CPU);

	/*
	 * When the user explicitly disabled समय करोn't क्रमce it here.
	 */
	अगर (opts->sample_समय &&
	    (!perf_missing_features.sample_id_all &&
	    (!opts->no_inherit || target__has_cpu(&opts->target) || per_cpu ||
	     opts->sample_समय_set)))
		evsel__set_sample_bit(evsel, TIME);

	अगर (opts->raw_samples && !evsel->no_aux_samples) अणु
		evsel__set_sample_bit(evsel, TIME);
		evsel__set_sample_bit(evsel, RAW);
		evsel__set_sample_bit(evsel, CPU);
	पूर्ण

	अगर (opts->sample_address)
		evsel__set_sample_bit(evsel, DATA_SRC);

	अगर (opts->sample_phys_addr)
		evsel__set_sample_bit(evsel, PHYS_ADDR);

	अगर (opts->no_buffering) अणु
		attr->watermark = 0;
		attr->wakeup_events = 1;
	पूर्ण
	अगर (opts->branch_stack && !evsel->no_aux_samples) अणु
		evsel__set_sample_bit(evsel, BRANCH_STACK);
		attr->branch_sample_type = opts->branch_stack;
	पूर्ण

	अगर (opts->sample_weight)
		arch_evsel__set_sample_weight(evsel);

	attr->task     = track;
	attr->mmap     = track;
	attr->mmap2    = track && !perf_missing_features.mmap2;
	attr->comm     = track;
	attr->build_id = track && opts->build_id;

	/*
	 * ksymbol is tracked separately with text poke because it needs to be
	 * प्रणाली wide and enabled immediately.
	 */
	अगर (!opts->text_poke)
		attr->ksymbol = track && !perf_missing_features.ksymbol;
	attr->bpf_event = track && !opts->no_bpf_event && !perf_missing_features.bpf;

	अगर (opts->record_namespaces)
		attr->namespaces  = track;

	अगर (opts->record_cgroup) अणु
		attr->cgroup = track && !perf_missing_features.cgroup;
		evsel__set_sample_bit(evsel, CGROUP);
	पूर्ण

	अगर (opts->sample_data_page_size)
		evsel__set_sample_bit(evsel, DATA_PAGE_SIZE);

	अगर (opts->sample_code_page_size)
		evsel__set_sample_bit(evsel, CODE_PAGE_SIZE);

	अगर (opts->record_चयन_events)
		attr->context_चयन = track;

	अगर (opts->sample_transaction)
		evsel__set_sample_bit(evsel, TRANSACTION);

	अगर (opts->running_समय) अणु
		evsel->core.attr.पढ़ो_क्रमmat |=
			PERF_FORMAT_TOTAL_TIME_ENABLED |
			PERF_FORMAT_TOTAL_TIME_RUNNING;
	पूर्ण

	/*
	 * XXX see the function comment above
	 *
	 * Disabling only independent events or group leaders,
	 * keeping group members enabled.
	 */
	अगर (evsel__is_group_leader(evsel))
		attr->disabled = 1;

	/*
	 * Setting enable_on_exec क्रम independent events and
	 * group leaders क्रम traced executed by perf.
	 */
	अगर (target__none(&opts->target) && evsel__is_group_leader(evsel) &&
	    !opts->initial_delay)
		attr->enable_on_exec = 1;

	अगर (evsel->immediate) अणु
		attr->disabled = 0;
		attr->enable_on_exec = 0;
	पूर्ण

	घड़ीid = opts->घड़ीid;
	अगर (opts->use_घड़ीid) अणु
		attr->use_घड़ीid = 1;
		attr->घड़ीid = opts->घड़ीid;
	पूर्ण

	अगर (evsel->precise_max)
		attr->precise_ip = 3;

	अगर (opts->all_user) अणु
		attr->exclude_kernel = 1;
		attr->exclude_user   = 0;
	पूर्ण

	अगर (opts->all_kernel) अणु
		attr->exclude_kernel = 0;
		attr->exclude_user   = 1;
	पूर्ण

	अगर (evsel->core.own_cpus || evsel->unit)
		evsel->core.attr.पढ़ो_क्रमmat |= PERF_FORMAT_ID;

	/*
	 * Apply event specअगरic term settings,
	 * it overloads any global configuration.
	 */
	evsel__apply_config_terms(evsel, opts, track);

	evsel->ignore_missing_thपढ़ो = opts->ignore_missing_thपढ़ो;

	/* The --period option takes the precedence. */
	अगर (opts->period_set) अणु
		अगर (opts->period)
			evsel__set_sample_bit(evsel, PERIOD);
		अन्यथा
			evsel__reset_sample_bit(evsel, PERIOD);
	पूर्ण

	/*
	 * A dummy event never triggers any actual counter and thereक्रमe
	 * cannot be used with branch_stack.
	 *
	 * For initial_delay, a dummy event is added implicitly.
	 * The software event will trigger -EOPNOTSUPP error out,
	 * अगर BRANCH_STACK bit is set.
	 */
	अगर (evsel__is_dummy_event(evsel))
		evsel__reset_sample_bit(evsel, BRANCH_STACK);
पूर्ण

पूर्णांक evsel__set_filter(काष्ठा evsel *evsel, स्थिर अक्षर *filter)
अणु
	अक्षर *new_filter = strdup(filter);

	अगर (new_filter != शून्य) अणु
		मुक्त(evsel->filter);
		evsel->filter = new_filter;
		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक evsel__append_filter(काष्ठा evsel *evsel, स्थिर अक्षर *fmt, स्थिर अक्षर *filter)
अणु
	अक्षर *new_filter;

	अगर (evsel->filter == शून्य)
		वापस evsel__set_filter(evsel, filter);

	अगर (aप्र_लिखो(&new_filter, fmt, evsel->filter, filter) > 0) अणु
		मुक्त(evsel->filter);
		evsel->filter = new_filter;
		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण

पूर्णांक evsel__append_tp_filter(काष्ठा evsel *evsel, स्थिर अक्षर *filter)
अणु
	वापस evsel__append_filter(evsel, "(%s) && (%s)", filter);
पूर्ण

पूर्णांक evsel__append_addr_filter(काष्ठा evsel *evsel, स्थिर अक्षर *filter)
अणु
	वापस evsel__append_filter(evsel, "%s,%s", filter);
पूर्ण

/* Caller has to clear disabled after going through all CPUs. */
पूर्णांक evsel__enable_cpu(काष्ठा evsel *evsel, पूर्णांक cpu)
अणु
	वापस perf_evsel__enable_cpu(&evsel->core, cpu);
पूर्ण

पूर्णांक evsel__enable(काष्ठा evsel *evsel)
अणु
	पूर्णांक err = perf_evsel__enable(&evsel->core);

	अगर (!err)
		evsel->disabled = false;
	वापस err;
पूर्ण

/* Caller has to set disabled after going through all CPUs. */
पूर्णांक evsel__disable_cpu(काष्ठा evsel *evsel, पूर्णांक cpu)
अणु
	वापस perf_evsel__disable_cpu(&evsel->core, cpu);
पूर्ण

पूर्णांक evsel__disable(काष्ठा evsel *evsel)
अणु
	पूर्णांक err = perf_evsel__disable(&evsel->core);
	/*
	 * We mark it disabled here so that tools that disable a event can
	 * ignore events after they disable it. I.e. the ring buffer may have
	 * alपढ़ोy a few more events queued up beक्रमe the kernel got the stop
	 * request.
	 */
	अगर (!err)
		evsel->disabled = true;

	वापस err;
पूर्ण

अटल व्योम evsel__मुक्त_config_terms(काष्ठा evsel *evsel)
अणु
	काष्ठा evsel_config_term *term, *h;

	list_क्रम_each_entry_safe(term, h, &evsel->config_terms, list) अणु
		list_del_init(&term->list);
		अगर (term->मुक्त_str)
			zमुक्त(&term->val.str);
		मुक्त(term);
	पूर्ण
पूर्ण

व्योम evsel__निकास(काष्ठा evsel *evsel)
अणु
	निश्चित(list_empty(&evsel->core.node));
	निश्चित(evsel->evlist == शून्य);
	bpf_counter__destroy(evsel);
	evsel__मुक्त_counts(evsel);
	perf_evsel__मुक्त_fd(&evsel->core);
	perf_evsel__मुक्त_id(&evsel->core);
	evsel__मुक्त_config_terms(evsel);
	cgroup__put(evsel->cgrp);
	perf_cpu_map__put(evsel->core.cpus);
	perf_cpu_map__put(evsel->core.own_cpus);
	perf_thपढ़ो_map__put(evsel->core.thपढ़ोs);
	zमुक्त(&evsel->group_name);
	zमुक्त(&evsel->name);
	zमुक्त(&evsel->pmu_name);
	evsel__zero_per_pkg(evsel);
	hashmap__मुक्त(evsel->per_pkg_mask);
	evsel->per_pkg_mask = शून्य;
	zमुक्त(&evsel->metric_events);
	perf_evsel__object.fini(evsel);
पूर्ण

व्योम evsel__delete(काष्ठा evsel *evsel)
अणु
	evsel__निकास(evsel);
	मुक्त(evsel);
पूर्ण

व्योम evsel__compute_deltas(काष्ठा evsel *evsel, पूर्णांक cpu, पूर्णांक thपढ़ो,
			   काष्ठा perf_counts_values *count)
अणु
	काष्ठा perf_counts_values पंचांगp;

	अगर (!evsel->prev_raw_counts)
		वापस;

	अगर (cpu == -1) अणु
		पंचांगp = evsel->prev_raw_counts->aggr;
		evsel->prev_raw_counts->aggr = *count;
	पूर्ण अन्यथा अणु
		पंचांगp = *perf_counts(evsel->prev_raw_counts, cpu, thपढ़ो);
		*perf_counts(evsel->prev_raw_counts, cpu, thपढ़ो) = *count;
	पूर्ण

	count->val = count->val - पंचांगp.val;
	count->ena = count->ena - पंचांगp.ena;
	count->run = count->run - पंचांगp.run;
पूर्ण

व्योम perf_counts_values__scale(काष्ठा perf_counts_values *count,
			       bool scale, s8 *pscaled)
अणु
	s8 scaled = 0;

	अगर (scale) अणु
		अगर (count->run == 0) अणु
			scaled = -1;
			count->val = 0;
		पूर्ण अन्यथा अगर (count->run < count->ena) अणु
			scaled = 1;
			count->val = (u64)((द्विगुन) count->val * count->ena / count->run);
		पूर्ण
	पूर्ण

	अगर (pscaled)
		*pscaled = scaled;
पूर्ण

अटल पूर्णांक evsel__पढ़ो_one(काष्ठा evsel *evsel, पूर्णांक cpu, पूर्णांक thपढ़ो)
अणु
	काष्ठा perf_counts_values *count = perf_counts(evsel->counts, cpu, thपढ़ो);

	वापस perf_evsel__पढ़ो(&evsel->core, cpu, thपढ़ो, count);
पूर्ण

अटल व्योम evsel__set_count(काष्ठा evsel *counter, पूर्णांक cpu, पूर्णांक thपढ़ो, u64 val, u64 ena, u64 run)
अणु
	काष्ठा perf_counts_values *count;

	count = perf_counts(counter->counts, cpu, thपढ़ो);

	count->val    = val;
	count->ena    = ena;
	count->run    = run;

	perf_counts__set_loaded(counter->counts, cpu, thपढ़ो, true);
पूर्ण

अटल पूर्णांक evsel__process_group_data(काष्ठा evsel *leader, पूर्णांक cpu, पूर्णांक thपढ़ो, u64 *data)
अणु
	u64 पढ़ो_क्रमmat = leader->core.attr.पढ़ो_क्रमmat;
	काष्ठा sample_पढ़ो_value *v;
	u64 nr, ena = 0, run = 0, i;

	nr = *data++;

	अगर (nr != (u64) leader->core.nr_members)
		वापस -EINVAL;

	अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_ENABLED)
		ena = *data++;

	अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_RUNNING)
		run = *data++;

	v = (काष्ठा sample_पढ़ो_value *) data;

	evsel__set_count(leader, cpu, thपढ़ो, v[0].value, ena, run);

	क्रम (i = 1; i < nr; i++) अणु
		काष्ठा evsel *counter;

		counter = evlist__id2evsel(leader->evlist, v[i].id);
		अगर (!counter)
			वापस -EINVAL;

		evsel__set_count(counter, cpu, thपढ़ो, v[i].value, ena, run);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक evsel__पढ़ो_group(काष्ठा evsel *leader, पूर्णांक cpu, पूर्णांक thपढ़ो)
अणु
	काष्ठा perf_stat_evsel *ps = leader->stats;
	u64 पढ़ो_क्रमmat = leader->core.attr.पढ़ो_क्रमmat;
	पूर्णांक size = perf_evsel__पढ़ो_size(&leader->core);
	u64 *data = ps->group_data;

	अगर (!(पढ़ो_क्रमmat & PERF_FORMAT_ID))
		वापस -EINVAL;

	अगर (!evsel__is_group_leader(leader))
		वापस -EINVAL;

	अगर (!data) अणु
		data = zalloc(size);
		अगर (!data)
			वापस -ENOMEM;

		ps->group_data = data;
	पूर्ण

	अगर (FD(leader, cpu, thपढ़ो) < 0)
		वापस -EINVAL;

	अगर (पढ़ोn(FD(leader, cpu, thपढ़ो), data, size) <= 0)
		वापस -त्रुटि_सं;

	वापस evsel__process_group_data(leader, cpu, thपढ़ो, data);
पूर्ण

पूर्णांक evsel__पढ़ो_counter(काष्ठा evsel *evsel, पूर्णांक cpu, पूर्णांक thपढ़ो)
अणु
	u64 पढ़ो_क्रमmat = evsel->core.attr.पढ़ो_क्रमmat;

	अगर (पढ़ो_क्रमmat & PERF_FORMAT_GROUP)
		वापस evsel__पढ़ो_group(evsel, cpu, thपढ़ो);

	वापस evsel__पढ़ो_one(evsel, cpu, thपढ़ो);
पूर्ण

पूर्णांक __evsel__पढ़ो_on_cpu(काष्ठा evsel *evsel, पूर्णांक cpu, पूर्णांक thपढ़ो, bool scale)
अणु
	काष्ठा perf_counts_values count;
	माप_प्रकार nv = scale ? 3 : 1;

	अगर (FD(evsel, cpu, thपढ़ो) < 0)
		वापस -EINVAL;

	अगर (evsel->counts == शून्य && evsel__alloc_counts(evsel, cpu + 1, thपढ़ो + 1) < 0)
		वापस -ENOMEM;

	अगर (पढ़ोn(FD(evsel, cpu, thपढ़ो), &count, nv * माप(u64)) <= 0)
		वापस -त्रुटि_सं;

	evsel__compute_deltas(evsel, cpu, thपढ़ो, &count);
	perf_counts_values__scale(&count, scale, शून्य);
	*perf_counts(evsel->counts, cpu, thपढ़ो) = count;
	वापस 0;
पूर्ण

अटल पूर्णांक get_group_fd(काष्ठा evsel *evsel, पूर्णांक cpu, पूर्णांक thपढ़ो)
अणु
	काष्ठा evsel *leader = evsel->leader;
	पूर्णांक fd;

	अगर (evsel__is_group_leader(evsel))
		वापस -1;

	/*
	 * Leader must be alपढ़ोy processed/खोलो,
	 * अगर not it's a bug.
	 */
	BUG_ON(!leader->core.fd);

	fd = FD(leader, cpu, thपढ़ो);
	BUG_ON(fd == -1);

	वापस fd;
पूर्ण

अटल व्योम evsel__हटाओ_fd(काष्ठा evsel *pos, पूर्णांक nr_cpus, पूर्णांक nr_thपढ़ोs, पूर्णांक thपढ़ो_idx)
अणु
	क्रम (पूर्णांक cpu = 0; cpu < nr_cpus; cpu++)
		क्रम (पूर्णांक thपढ़ो = thपढ़ो_idx; thपढ़ो < nr_thपढ़ोs - 1; thपढ़ो++)
			FD(pos, cpu, thपढ़ो) = FD(pos, cpu, thपढ़ो + 1);
पूर्ण

अटल पूर्णांक update_fds(काष्ठा evsel *evsel,
		      पूर्णांक nr_cpus, पूर्णांक cpu_idx,
		      पूर्णांक nr_thपढ़ोs, पूर्णांक thपढ़ो_idx)
अणु
	काष्ठा evsel *pos;

	अगर (cpu_idx >= nr_cpus || thपढ़ो_idx >= nr_thपढ़ोs)
		वापस -EINVAL;

	evlist__क्रम_each_entry(evsel->evlist, pos) अणु
		nr_cpus = pos != evsel ? nr_cpus : cpu_idx;

		evsel__हटाओ_fd(pos, nr_cpus, nr_thपढ़ोs, thपढ़ो_idx);

		/*
		 * Since fds क्रम next evsel has not been created,
		 * there is no need to iterate whole event list.
		 */
		अगर (pos == evsel)
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool ignore_missing_thपढ़ो(काष्ठा evsel *evsel,
				  पूर्णांक nr_cpus, पूर्णांक cpu,
				  काष्ठा perf_thपढ़ो_map *thपढ़ोs,
				  पूर्णांक thपढ़ो, पूर्णांक err)
अणु
	pid_t ignore_pid = perf_thपढ़ो_map__pid(thपढ़ोs, thपढ़ो);

	अगर (!evsel->ignore_missing_thपढ़ो)
		वापस false;

	/* The प्रणाली wide setup करोes not work with thपढ़ोs. */
	अगर (evsel->core.प्रणाली_wide)
		वापस false;

	/* The -ESRCH is perf event syscall त्रुटि_सं क्रम pid's not found. */
	अगर (err != -ESRCH)
		वापस false;

	/* If there's only one thपढ़ो, let it fail. */
	अगर (thपढ़ोs->nr == 1)
		वापस false;

	/*
	 * We should हटाओ fd क्रम missing_thपढ़ो first
	 * because thपढ़ो_map__हटाओ() will decrease thपढ़ोs->nr.
	 */
	अगर (update_fds(evsel, nr_cpus, cpu, thपढ़ोs->nr, thपढ़ो))
		वापस false;

	अगर (thपढ़ो_map__हटाओ(thपढ़ोs, thपढ़ो))
		वापस false;

	pr_warning("WARNING: Ignored open failure for pid %d\n",
		   ignore_pid);
	वापस true;
पूर्ण

अटल पूर्णांक __खोलो_attr__ख_लिखो(खाता *fp, स्थिर अक्षर *name, स्थिर अक्षर *val,
				व्योम *priv __maybe_unused)
अणु
	वापस ख_लिखो(fp, "  %-32s %s\n", name, val);
पूर्ण

अटल व्योम display_attr(काष्ठा perf_event_attr *attr)
अणु
	अगर (verbose >= 2 || debug_peo_args) अणु
		ख_लिखो(मानक_त्रुटि, "%.60s\n", graph_करोtted_line);
		ख_लिखो(मानक_त्रुटि, "perf_event_attr:\n");
		perf_event_attr__ख_लिखो(मानक_त्रुटि, attr, __खोलो_attr__ख_लिखो, शून्य);
		ख_लिखो(मानक_त्रुटि, "%.60s\n", graph_करोtted_line);
	पूर्ण
पूर्ण

अटल पूर्णांक perf_event_खोलो(काष्ठा evsel *evsel,
			   pid_t pid, पूर्णांक cpu, पूर्णांक group_fd,
			   अचिन्हित दीर्घ flags)
अणु
	पूर्णांक precise_ip = evsel->core.attr.precise_ip;
	पूर्णांक fd;

	जबतक (1) अणु
		pr_debug2_peo("sys_perf_event_open: pid %d  cpu %d  group_fd %d  flags %#lx",
			  pid, cpu, group_fd, flags);

		fd = sys_perf_event_खोलो(&evsel->core.attr, pid, cpu, group_fd, flags);
		अगर (fd >= 0)
			अवरोध;

		/* Do not try less precise अगर not requested. */
		अगर (!evsel->precise_max)
			अवरोध;

		/*
		 * We tried all the precise_ip values, and it's
		 * still failing, so leave it to standard fallback.
		 */
		अगर (!evsel->core.attr.precise_ip) अणु
			evsel->core.attr.precise_ip = precise_ip;
			अवरोध;
		पूर्ण

		pr_debug2_peo("\nsys_perf_event_open failed, error %d\n", -ENOTSUP);
		evsel->core.attr.precise_ip--;
		pr_debug2_peo("decreasing precise_ip by one (%d)\n", evsel->core.attr.precise_ip);
		display_attr(&evsel->core.attr);
	पूर्ण

	वापस fd;
पूर्ण

अटल पूर्णांक evsel__खोलो_cpu(काष्ठा evsel *evsel, काष्ठा perf_cpu_map *cpus,
		काष्ठा perf_thपढ़ो_map *thपढ़ोs,
		पूर्णांक start_cpu, पूर्णांक end_cpu)
अणु
	पूर्णांक cpu, thपढ़ो, nthपढ़ोs;
	अचिन्हित दीर्घ flags = PERF_FLAG_FD_CLOEXEC;
	पूर्णांक pid = -1, err, old_त्रुटि_सं;
	क्रमागत अणु NO_CHANGE, SET_TO_MAX, INCREASED_MAX पूर्ण set_rlimit = NO_CHANGE;

	अगर ((perf_missing_features.ग_लिखो_backward && evsel->core.attr.ग_लिखो_backward) ||
	    (perf_missing_features.aux_output     && evsel->core.attr.aux_output))
		वापस -EINVAL;

	अगर (cpus == शून्य) अणु
		अटल काष्ठा perf_cpu_map *empty_cpu_map;

		अगर (empty_cpu_map == शून्य) अणु
			empty_cpu_map = perf_cpu_map__dummy_new();
			अगर (empty_cpu_map == शून्य)
				वापस -ENOMEM;
		पूर्ण

		cpus = empty_cpu_map;
	पूर्ण

	अगर (thपढ़ोs == शून्य) अणु
		अटल काष्ठा perf_thपढ़ो_map *empty_thपढ़ो_map;

		अगर (empty_thपढ़ो_map == शून्य) अणु
			empty_thपढ़ो_map = thपढ़ो_map__new_by_tid(-1);
			अगर (empty_thपढ़ो_map == शून्य)
				वापस -ENOMEM;
		पूर्ण

		thपढ़ोs = empty_thपढ़ो_map;
	पूर्ण

	अगर (evsel->core.प्रणाली_wide)
		nthपढ़ोs = 1;
	अन्यथा
		nthपढ़ोs = thपढ़ोs->nr;

	अगर (evsel->core.fd == शून्य &&
	    perf_evsel__alloc_fd(&evsel->core, cpus->nr, nthपढ़ोs) < 0)
		वापस -ENOMEM;

	अगर (evsel->cgrp) अणु
		flags |= PERF_FLAG_PID_CGROUP;
		pid = evsel->cgrp->fd;
	पूर्ण

fallback_missing_features:
	अगर (perf_missing_features.weight_काष्ठा) अणु
		evsel__set_sample_bit(evsel, WEIGHT);
		evsel__reset_sample_bit(evsel, WEIGHT_STRUCT);
	पूर्ण
	अगर (perf_missing_features.घड़ीid_wrong)
		evsel->core.attr.घड़ीid = CLOCK_MONOTONIC; /* should always work */
	अगर (perf_missing_features.घड़ीid) अणु
		evsel->core.attr.use_घड़ीid = 0;
		evsel->core.attr.घड़ीid = 0;
	पूर्ण
	अगर (perf_missing_features.cloexec)
		flags &= ~(अचिन्हित दीर्घ)PERF_FLAG_FD_CLOEXEC;
	अगर (perf_missing_features.mmap2)
		evsel->core.attr.mmap2 = 0;
	अगर (perf_missing_features.exclude_guest)
		evsel->core.attr.exclude_guest = evsel->core.attr.exclude_host = 0;
	अगर (perf_missing_features.lbr_flags)
		evsel->core.attr.branch_sample_type &= ~(PERF_SAMPLE_BRANCH_NO_FLAGS |
				     PERF_SAMPLE_BRANCH_NO_CYCLES);
	अगर (perf_missing_features.group_पढ़ो && evsel->core.attr.inherit)
		evsel->core.attr.पढ़ो_क्रमmat &= ~(PERF_FORMAT_GROUP|PERF_FORMAT_ID);
	अगर (perf_missing_features.ksymbol)
		evsel->core.attr.ksymbol = 0;
	अगर (perf_missing_features.bpf)
		evsel->core.attr.bpf_event = 0;
	अगर (perf_missing_features.branch_hw_idx)
		evsel->core.attr.branch_sample_type &= ~PERF_SAMPLE_BRANCH_HW_INDEX;
retry_sample_id:
	अगर (perf_missing_features.sample_id_all)
		evsel->core.attr.sample_id_all = 0;

	display_attr(&evsel->core.attr);

	क्रम (cpu = start_cpu; cpu < end_cpu; cpu++) अणु

		क्रम (thपढ़ो = 0; thपढ़ो < nthपढ़ोs; thपढ़ो++) अणु
			पूर्णांक fd, group_fd;

			अगर (!evsel->cgrp && !evsel->core.प्रणाली_wide)
				pid = perf_thपढ़ो_map__pid(thपढ़ोs, thपढ़ो);

			group_fd = get_group_fd(evsel, cpu, thपढ़ो);
retry_खोलो:
			test_attr__पढ़ोy();

			fd = perf_event_खोलो(evsel, pid, cpus->map[cpu],
					     group_fd, flags);

			FD(evsel, cpu, thपढ़ो) = fd;

			bpf_counter__install_pe(evsel, cpu, fd);

			अगर (unlikely(test_attr__enabled)) अणु
				test_attr__खोलो(&evsel->core.attr, pid, cpus->map[cpu],
						fd, group_fd, flags);
			पूर्ण

			अगर (fd < 0) अणु
				err = -त्रुटि_सं;

				अगर (ignore_missing_thपढ़ो(evsel, cpus->nr, cpu, thपढ़ोs, thपढ़ो, err)) अणु
					/*
					 * We just हटाओd 1 thपढ़ो, so take a step
					 * back on thपढ़ो index and lower the upper
					 * nthपढ़ोs limit.
					 */
					nthपढ़ोs--;
					thपढ़ो--;

					/* ... and pretend like nothing have happened. */
					err = 0;
					जारी;
				पूर्ण

				pr_debug2_peo("\nsys_perf_event_open failed, error %d\n",
					  err);
				जाओ try_fallback;
			पूर्ण

			pr_debug2_peo(" = %d\n", fd);

			अगर (evsel->bpf_fd >= 0) अणु
				पूर्णांक evt_fd = fd;
				पूर्णांक bpf_fd = evsel->bpf_fd;

				err = ioctl(evt_fd,
					    PERF_EVENT_IOC_SET_BPF,
					    bpf_fd);
				अगर (err && त्रुटि_सं != EEXIST) अणु
					pr_err("failed to attach bpf fd %d: %s\n",
					       bpf_fd, म_त्रुटि(त्रुटि_सं));
					err = -EINVAL;
					जाओ out_बंद;
				पूर्ण
			पूर्ण

			set_rlimit = NO_CHANGE;

			/*
			 * If we succeeded but had to समाप्त घड़ीid, fail and
			 * have evsel__खोलो_म_त्रुटि() prपूर्णांक us a nice error.
			 */
			अगर (perf_missing_features.घड़ीid ||
			    perf_missing_features.घड़ीid_wrong) अणु
				err = -EINVAL;
				जाओ out_बंद;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

try_fallback:
	/*
	 * perf stat needs between 5 and 22 fds per CPU. When we run out
	 * of them try to increase the limits.
	 */
	अगर (err == -EMखाता && set_rlimit < INCREASED_MAX) अणु
		काष्ठा rlimit l;

		old_त्रुटि_सं = त्रुटि_सं;
		अगर (getrlimit(RLIMIT_NOखाता, &l) == 0) अणु
			अगर (set_rlimit == NO_CHANGE)
				l.rlim_cur = l.rlim_max;
			अन्यथा अणु
				l.rlim_cur = l.rlim_max + 1000;
				l.rlim_max = l.rlim_cur;
			पूर्ण
			अगर (setrlimit(RLIMIT_NOखाता, &l) == 0) अणु
				set_rlimit++;
				त्रुटि_सं = old_त्रुटि_सं;
				जाओ retry_खोलो;
			पूर्ण
		पूर्ण
		त्रुटि_सं = old_त्रुटि_सं;
	पूर्ण

	अगर (err != -EINVAL || cpu > 0 || thपढ़ो > 0)
		जाओ out_बंद;

	/*
	 * Must probe features in the order they were added to the
	 * perf_event_attr पूर्णांकerface.
	 */
	अगर (!perf_missing_features.weight_काष्ठा &&
	    (evsel->core.attr.sample_type & PERF_SAMPLE_WEIGHT_STRUCT)) अणु
		perf_missing_features.weight_काष्ठा = true;
		pr_debug2("switching off weight struct support\n");
		जाओ fallback_missing_features;
	पूर्ण अन्यथा अगर (!perf_missing_features.code_page_size &&
	    (evsel->core.attr.sample_type & PERF_SAMPLE_CODE_PAGE_SIZE)) अणु
		perf_missing_features.code_page_size = true;
		pr_debug2_peo("Kernel has no PERF_SAMPLE_CODE_PAGE_SIZE support, bailing out\n");
		जाओ out_बंद;
	पूर्ण अन्यथा अगर (!perf_missing_features.data_page_size &&
	    (evsel->core.attr.sample_type & PERF_SAMPLE_DATA_PAGE_SIZE)) अणु
		perf_missing_features.data_page_size = true;
		pr_debug2_peo("Kernel has no PERF_SAMPLE_DATA_PAGE_SIZE support, bailing out\n");
		जाओ out_बंद;
	पूर्ण अन्यथा अगर (!perf_missing_features.cgroup && evsel->core.attr.cgroup) अणु
		perf_missing_features.cgroup = true;
		pr_debug2_peo("Kernel has no cgroup sampling support, bailing out\n");
		जाओ out_बंद;
        पूर्ण अन्यथा अगर (!perf_missing_features.branch_hw_idx &&
	    (evsel->core.attr.branch_sample_type & PERF_SAMPLE_BRANCH_HW_INDEX)) अणु
		perf_missing_features.branch_hw_idx = true;
		pr_debug2("switching off branch HW index support\n");
		जाओ fallback_missing_features;
	पूर्ण अन्यथा अगर (!perf_missing_features.aux_output && evsel->core.attr.aux_output) अणु
		perf_missing_features.aux_output = true;
		pr_debug2_peo("Kernel has no attr.aux_output support, bailing out\n");
		जाओ out_बंद;
	पूर्ण अन्यथा अगर (!perf_missing_features.bpf && evsel->core.attr.bpf_event) अणु
		perf_missing_features.bpf = true;
		pr_debug2_peo("switching off bpf_event\n");
		जाओ fallback_missing_features;
	पूर्ण अन्यथा अगर (!perf_missing_features.ksymbol && evsel->core.attr.ksymbol) अणु
		perf_missing_features.ksymbol = true;
		pr_debug2_peo("switching off ksymbol\n");
		जाओ fallback_missing_features;
	पूर्ण अन्यथा अगर (!perf_missing_features.ग_लिखो_backward && evsel->core.attr.ग_लिखो_backward) अणु
		perf_missing_features.ग_लिखो_backward = true;
		pr_debug2_peo("switching off write_backward\n");
		जाओ out_बंद;
	पूर्ण अन्यथा अगर (!perf_missing_features.घड़ीid_wrong && evsel->core.attr.use_घड़ीid) अणु
		perf_missing_features.घड़ीid_wrong = true;
		pr_debug2_peo("switching off clockid\n");
		जाओ fallback_missing_features;
	पूर्ण अन्यथा अगर (!perf_missing_features.घड़ीid && evsel->core.attr.use_घड़ीid) अणु
		perf_missing_features.घड़ीid = true;
		pr_debug2_peo("switching off use_clockid\n");
		जाओ fallback_missing_features;
	पूर्ण अन्यथा अगर (!perf_missing_features.cloexec && (flags & PERF_FLAG_FD_CLOEXEC)) अणु
		perf_missing_features.cloexec = true;
		pr_debug2_peo("switching off cloexec flag\n");
		जाओ fallback_missing_features;
	पूर्ण अन्यथा अगर (!perf_missing_features.mmap2 && evsel->core.attr.mmap2) अणु
		perf_missing_features.mmap2 = true;
		pr_debug2_peo("switching off mmap2\n");
		जाओ fallback_missing_features;
	पूर्ण अन्यथा अगर (!perf_missing_features.exclude_guest &&
		   (evsel->core.attr.exclude_guest || evsel->core.attr.exclude_host)) अणु
		perf_missing_features.exclude_guest = true;
		pr_debug2_peo("switching off exclude_guest, exclude_host\n");
		जाओ fallback_missing_features;
	पूर्ण अन्यथा अगर (!perf_missing_features.sample_id_all) अणु
		perf_missing_features.sample_id_all = true;
		pr_debug2_peo("switching off sample_id_all\n");
		जाओ retry_sample_id;
	पूर्ण अन्यथा अगर (!perf_missing_features.lbr_flags &&
			(evsel->core.attr.branch_sample_type &
			 (PERF_SAMPLE_BRANCH_NO_CYCLES |
			  PERF_SAMPLE_BRANCH_NO_FLAGS))) अणु
		perf_missing_features.lbr_flags = true;
		pr_debug2_peo("switching off branch sample type no (cycles/flags)\n");
		जाओ fallback_missing_features;
	पूर्ण अन्यथा अगर (!perf_missing_features.group_पढ़ो &&
		    evsel->core.attr.inherit &&
		   (evsel->core.attr.पढ़ो_क्रमmat & PERF_FORMAT_GROUP) &&
		   evsel__is_group_leader(evsel)) अणु
		perf_missing_features.group_पढ़ो = true;
		pr_debug2_peo("switching off group read\n");
		जाओ fallback_missing_features;
	पूर्ण
out_बंद:
	अगर (err)
		thपढ़ोs->err_thपढ़ो = thपढ़ो;

	old_त्रुटि_सं = त्रुटि_सं;
	करो अणु
		जबतक (--thपढ़ो >= 0) अणु
			अगर (FD(evsel, cpu, thपढ़ो) >= 0)
				बंद(FD(evsel, cpu, thपढ़ो));
			FD(evsel, cpu, thपढ़ो) = -1;
		पूर्ण
		thपढ़ो = nthपढ़ोs;
	पूर्ण जबतक (--cpu >= 0);
	त्रुटि_सं = old_त्रुटि_सं;
	वापस err;
पूर्ण

पूर्णांक evsel__खोलो(काष्ठा evsel *evsel, काष्ठा perf_cpu_map *cpus,
		काष्ठा perf_thपढ़ो_map *thपढ़ोs)
अणु
	वापस evsel__खोलो_cpu(evsel, cpus, thपढ़ोs, 0, cpus ? cpus->nr : 1);
पूर्ण

व्योम evsel__बंद(काष्ठा evsel *evsel)
अणु
	perf_evsel__बंद(&evsel->core);
	perf_evsel__मुक्त_id(&evsel->core);
पूर्ण

पूर्णांक evsel__खोलो_per_cpu(काष्ठा evsel *evsel, काष्ठा perf_cpu_map *cpus, पूर्णांक cpu)
अणु
	अगर (cpu == -1)
		वापस evsel__खोलो_cpu(evsel, cpus, शून्य, 0,
					cpus ? cpus->nr : 1);

	वापस evsel__खोलो_cpu(evsel, cpus, शून्य, cpu, cpu + 1);
पूर्ण

पूर्णांक evsel__खोलो_per_thपढ़ो(काष्ठा evsel *evsel, काष्ठा perf_thपढ़ो_map *thपढ़ोs)
अणु
	वापस evsel__खोलो(evsel, शून्य, thपढ़ोs);
पूर्ण

अटल पूर्णांक perf_evsel__parse_id_sample(स्थिर काष्ठा evsel *evsel,
				       स्थिर जोड़ perf_event *event,
				       काष्ठा perf_sample *sample)
अणु
	u64 type = evsel->core.attr.sample_type;
	स्थिर __u64 *array = event->sample.array;
	bool swapped = evsel->needs_swap;
	जोड़ u64_swap u;

	array += ((event->header.size -
		   माप(event->header)) / माप(u64)) - 1;

	अगर (type & PERF_SAMPLE_IDENTIFIER) अणु
		sample->id = *array;
		array--;
	पूर्ण

	अगर (type & PERF_SAMPLE_CPU) अणु
		u.val64 = *array;
		अगर (swapped) अणु
			/* unकरो swap of u64, then swap on inभागidual u32s */
			u.val64 = bswap_64(u.val64);
			u.val32[0] = bswap_32(u.val32[0]);
		पूर्ण

		sample->cpu = u.val32[0];
		array--;
	पूर्ण

	अगर (type & PERF_SAMPLE_STREAM_ID) अणु
		sample->stream_id = *array;
		array--;
	पूर्ण

	अगर (type & PERF_SAMPLE_ID) अणु
		sample->id = *array;
		array--;
	पूर्ण

	अगर (type & PERF_SAMPLE_TIME) अणु
		sample->समय = *array;
		array--;
	पूर्ण

	अगर (type & PERF_SAMPLE_TID) अणु
		u.val64 = *array;
		अगर (swapped) अणु
			/* unकरो swap of u64, then swap on inभागidual u32s */
			u.val64 = bswap_64(u.val64);
			u.val32[0] = bswap_32(u.val32[0]);
			u.val32[1] = bswap_32(u.val32[1]);
		पूर्ण

		sample->pid = u.val32[0];
		sample->tid = u.val32[1];
		array--;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत bool overflow(स्थिर व्योम *endp, u16 max_size, स्थिर व्योम *offset,
			    u64 size)
अणु
	वापस size > max_size || offset + size > endp;
पूर्ण

#घोषणा OVERFLOW_CHECK(offset, size, max_size)				\
	करो अणु								\
		अगर (overflow(endp, (max_size), (offset), (size)))	\
			वापस -EFAULT;					\
	पूर्ण जबतक (0)

#घोषणा OVERFLOW_CHECK_u64(offset) \
	OVERFLOW_CHECK(offset, माप(u64), माप(u64))

अटल पूर्णांक
perf_event__check_size(जोड़ perf_event *event, अचिन्हित पूर्णांक sample_size)
अणु
	/*
	 * The evsel's sample_size is based on PERF_SAMPLE_MASK which includes
	 * up to PERF_SAMPLE_PERIOD.  After that overflow() must be used to
	 * check the क्रमmat करोes not go past the end of the event.
	 */
	अगर (sample_size + माप(event->header) > event->header.size)
		वापस -EFAULT;

	वापस 0;
पूर्ण

व्योम __weak arch_perf_parse_sample_weight(काष्ठा perf_sample *data,
					  स्थिर __u64 *array,
					  u64 type __maybe_unused)
अणु
	data->weight = *array;
पूर्ण

पूर्णांक evsel__parse_sample(काष्ठा evsel *evsel, जोड़ perf_event *event,
			काष्ठा perf_sample *data)
अणु
	u64 type = evsel->core.attr.sample_type;
	bool swapped = evsel->needs_swap;
	स्थिर __u64 *array;
	u16 max_size = event->header.size;
	स्थिर व्योम *endp = (व्योम *)event + max_size;
	u64 sz;

	/*
	 * used क्रम cross-endian analysis. See git commit 65014ab3
	 * क्रम why this goofiness is needed.
	 */
	जोड़ u64_swap u;

	स_रखो(data, 0, माप(*data));
	data->cpu = data->pid = data->tid = -1;
	data->stream_id = data->id = data->समय = -1ULL;
	data->period = evsel->core.attr.sample_period;
	data->cpumode = event->header.misc & PERF_RECORD_MISC_CPUMODE_MASK;
	data->misc    = event->header.misc;
	data->id = -1ULL;
	data->data_src = PERF_MEM_DATA_SRC_NONE;

	अगर (event->header.type != PERF_RECORD_SAMPLE) अणु
		अगर (!evsel->core.attr.sample_id_all)
			वापस 0;
		वापस perf_evsel__parse_id_sample(evsel, event, data);
	पूर्ण

	array = event->sample.array;

	अगर (perf_event__check_size(event, evsel->sample_size))
		वापस -EFAULT;

	अगर (type & PERF_SAMPLE_IDENTIFIER) अणु
		data->id = *array;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_IP) अणु
		data->ip = *array;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_TID) अणु
		u.val64 = *array;
		अगर (swapped) अणु
			/* unकरो swap of u64, then swap on inभागidual u32s */
			u.val64 = bswap_64(u.val64);
			u.val32[0] = bswap_32(u.val32[0]);
			u.val32[1] = bswap_32(u.val32[1]);
		पूर्ण

		data->pid = u.val32[0];
		data->tid = u.val32[1];
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_TIME) अणु
		data->समय = *array;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_ADDR) अणु
		data->addr = *array;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_ID) अणु
		data->id = *array;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_STREAM_ID) अणु
		data->stream_id = *array;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_CPU) अणु

		u.val64 = *array;
		अगर (swapped) अणु
			/* unकरो swap of u64, then swap on inभागidual u32s */
			u.val64 = bswap_64(u.val64);
			u.val32[0] = bswap_32(u.val32[0]);
		पूर्ण

		data->cpu = u.val32[0];
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_PERIOD) अणु
		data->period = *array;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_READ) अणु
		u64 पढ़ो_क्रमmat = evsel->core.attr.पढ़ो_क्रमmat;

		OVERFLOW_CHECK_u64(array);
		अगर (पढ़ो_क्रमmat & PERF_FORMAT_GROUP)
			data->पढ़ो.group.nr = *array;
		अन्यथा
			data->पढ़ो.one.value = *array;

		array++;

		अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_ENABLED) अणु
			OVERFLOW_CHECK_u64(array);
			data->पढ़ो.समय_enabled = *array;
			array++;
		पूर्ण

		अगर (पढ़ो_क्रमmat & PERF_FORMAT_TOTAL_TIME_RUNNING) अणु
			OVERFLOW_CHECK_u64(array);
			data->पढ़ो.समय_running = *array;
			array++;
		पूर्ण

		/* PERF_FORMAT_ID is क्रमced क्रम PERF_SAMPLE_READ */
		अगर (पढ़ो_क्रमmat & PERF_FORMAT_GROUP) अणु
			स्थिर u64 max_group_nr = UINT64_MAX /
					माप(काष्ठा sample_पढ़ो_value);

			अगर (data->पढ़ो.group.nr > max_group_nr)
				वापस -EFAULT;
			sz = data->पढ़ो.group.nr *
			     माप(काष्ठा sample_पढ़ो_value);
			OVERFLOW_CHECK(array, sz, max_size);
			data->पढ़ो.group.values =
					(काष्ठा sample_पढ़ो_value *)array;
			array = (व्योम *)array + sz;
		पूर्ण अन्यथा अणु
			OVERFLOW_CHECK_u64(array);
			data->पढ़ो.one.id = *array;
			array++;
		पूर्ण
	पूर्ण

	अगर (type & PERF_SAMPLE_CALLCHAIN) अणु
		स्थिर u64 max_callchain_nr = UINT64_MAX / माप(u64);

		OVERFLOW_CHECK_u64(array);
		data->callchain = (काष्ठा ip_callchain *)array++;
		अगर (data->callchain->nr > max_callchain_nr)
			वापस -EFAULT;
		sz = data->callchain->nr * माप(u64);
		OVERFLOW_CHECK(array, sz, max_size);
		array = (व्योम *)array + sz;
	पूर्ण

	अगर (type & PERF_SAMPLE_RAW) अणु
		OVERFLOW_CHECK_u64(array);
		u.val64 = *array;

		/*
		 * Unकरो swap of u64, then swap on inभागidual u32s,
		 * get the size of the raw area and unकरो all of the
		 * swap. The pevent पूर्णांकerface handles endianness by
		 * itself.
		 */
		अगर (swapped) अणु
			u.val64 = bswap_64(u.val64);
			u.val32[0] = bswap_32(u.val32[0]);
			u.val32[1] = bswap_32(u.val32[1]);
		पूर्ण
		data->raw_size = u.val32[0];

		/*
		 * The raw data is aligned on 64bits including the
		 * u32 size, so it's safe to use mem_bswap_64.
		 */
		अगर (swapped)
			mem_bswap_64((व्योम *) array, data->raw_size);

		array = (व्योम *)array + माप(u32);

		OVERFLOW_CHECK(array, data->raw_size, max_size);
		data->raw_data = (व्योम *)array;
		array = (व्योम *)array + data->raw_size;
	पूर्ण

	अगर (type & PERF_SAMPLE_BRANCH_STACK) अणु
		स्थिर u64 max_branch_nr = UINT64_MAX /
					  माप(काष्ठा branch_entry);

		OVERFLOW_CHECK_u64(array);
		data->branch_stack = (काष्ठा branch_stack *)array++;

		अगर (data->branch_stack->nr > max_branch_nr)
			वापस -EFAULT;

		sz = data->branch_stack->nr * माप(काष्ठा branch_entry);
		अगर (evsel__has_branch_hw_idx(evsel))
			sz += माप(u64);
		अन्यथा
			data->no_hw_idx = true;
		OVERFLOW_CHECK(array, sz, max_size);
		array = (व्योम *)array + sz;
	पूर्ण

	अगर (type & PERF_SAMPLE_REGS_USER) अणु
		OVERFLOW_CHECK_u64(array);
		data->user_regs.abi = *array;
		array++;

		अगर (data->user_regs.abi) अणु
			u64 mask = evsel->core.attr.sample_regs_user;

			sz = hweight64(mask) * माप(u64);
			OVERFLOW_CHECK(array, sz, max_size);
			data->user_regs.mask = mask;
			data->user_regs.regs = (u64 *)array;
			array = (व्योम *)array + sz;
		पूर्ण
	पूर्ण

	अगर (type & PERF_SAMPLE_STACK_USER) अणु
		OVERFLOW_CHECK_u64(array);
		sz = *array++;

		data->user_stack.offset = ((अक्षर *)(array - 1)
					  - (अक्षर *) event);

		अगर (!sz) अणु
			data->user_stack.size = 0;
		पूर्ण अन्यथा अणु
			OVERFLOW_CHECK(array, sz, max_size);
			data->user_stack.data = (अक्षर *)array;
			array = (व्योम *)array + sz;
			OVERFLOW_CHECK_u64(array);
			data->user_stack.size = *array++;
			अगर (WARN_ONCE(data->user_stack.size > sz,
				      "user stack dump failure\n"))
				वापस -EFAULT;
		पूर्ण
	पूर्ण

	अगर (type & PERF_SAMPLE_WEIGHT_TYPE) अणु
		OVERFLOW_CHECK_u64(array);
		arch_perf_parse_sample_weight(data, array, type);
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_DATA_SRC) अणु
		OVERFLOW_CHECK_u64(array);
		data->data_src = *array;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_TRANSACTION) अणु
		OVERFLOW_CHECK_u64(array);
		data->transaction = *array;
		array++;
	पूर्ण

	data->पूर्णांकr_regs.abi = PERF_SAMPLE_REGS_ABI_NONE;
	अगर (type & PERF_SAMPLE_REGS_INTR) अणु
		OVERFLOW_CHECK_u64(array);
		data->पूर्णांकr_regs.abi = *array;
		array++;

		अगर (data->पूर्णांकr_regs.abi != PERF_SAMPLE_REGS_ABI_NONE) अणु
			u64 mask = evsel->core.attr.sample_regs_पूर्णांकr;

			sz = hweight64(mask) * माप(u64);
			OVERFLOW_CHECK(array, sz, max_size);
			data->पूर्णांकr_regs.mask = mask;
			data->पूर्णांकr_regs.regs = (u64 *)array;
			array = (व्योम *)array + sz;
		पूर्ण
	पूर्ण

	data->phys_addr = 0;
	अगर (type & PERF_SAMPLE_PHYS_ADDR) अणु
		data->phys_addr = *array;
		array++;
	पूर्ण

	data->cgroup = 0;
	अगर (type & PERF_SAMPLE_CGROUP) अणु
		data->cgroup = *array;
		array++;
	पूर्ण

	data->data_page_size = 0;
	अगर (type & PERF_SAMPLE_DATA_PAGE_SIZE) अणु
		data->data_page_size = *array;
		array++;
	पूर्ण

	data->code_page_size = 0;
	अगर (type & PERF_SAMPLE_CODE_PAGE_SIZE) अणु
		data->code_page_size = *array;
		array++;
	पूर्ण

	अगर (type & PERF_SAMPLE_AUX) अणु
		OVERFLOW_CHECK_u64(array);
		sz = *array++;

		OVERFLOW_CHECK(array, sz, max_size);
		/* Unकरो swap of data */
		अगर (swapped)
			mem_bswap_64((अक्षर *)array, sz);
		data->aux_sample.size = sz;
		data->aux_sample.data = (अक्षर *)array;
		array = (व्योम *)array + sz;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक evsel__parse_sample_बारtamp(काष्ठा evsel *evsel, जोड़ perf_event *event,
				  u64 *बारtamp)
अणु
	u64 type = evsel->core.attr.sample_type;
	स्थिर __u64 *array;

	अगर (!(type & PERF_SAMPLE_TIME))
		वापस -1;

	अगर (event->header.type != PERF_RECORD_SAMPLE) अणु
		काष्ठा perf_sample data = अणु
			.समय = -1ULL,
		पूर्ण;

		अगर (!evsel->core.attr.sample_id_all)
			वापस -1;
		अगर (perf_evsel__parse_id_sample(evsel, event, &data))
			वापस -1;

		*बारtamp = data.समय;
		वापस 0;
	पूर्ण

	array = event->sample.array;

	अगर (perf_event__check_size(event, evsel->sample_size))
		वापस -EFAULT;

	अगर (type & PERF_SAMPLE_IDENTIFIER)
		array++;

	अगर (type & PERF_SAMPLE_IP)
		array++;

	अगर (type & PERF_SAMPLE_TID)
		array++;

	अगर (type & PERF_SAMPLE_TIME)
		*बारtamp = *array;

	वापस 0;
पूर्ण

काष्ठा tep_क्रमmat_field *evsel__field(काष्ठा evsel *evsel, स्थिर अक्षर *name)
अणु
	वापस tep_find_field(evsel->tp_क्रमmat, name);
पूर्ण

व्योम *evsel__rawptr(काष्ठा evsel *evsel, काष्ठा perf_sample *sample, स्थिर अक्षर *name)
अणु
	काष्ठा tep_क्रमmat_field *field = evsel__field(evsel, name);
	पूर्णांक offset;

	अगर (!field)
		वापस शून्य;

	offset = field->offset;

	अगर (field->flags & TEP_FIELD_IS_DYNAMIC) अणु
		offset = *(पूर्णांक *)(sample->raw_data + field->offset);
		offset &= 0xffff;
	पूर्ण

	वापस sample->raw_data + offset;
पूर्ण

u64 क्रमmat_field__पूर्णांकval(काष्ठा tep_क्रमmat_field *field, काष्ठा perf_sample *sample,
			 bool needs_swap)
अणु
	u64 value;
	व्योम *ptr = sample->raw_data + field->offset;

	चयन (field->size) अणु
	हाल 1:
		वापस *(u8 *)ptr;
	हाल 2:
		value = *(u16 *)ptr;
		अवरोध;
	हाल 4:
		value = *(u32 *)ptr;
		अवरोध;
	हाल 8:
		स_नकल(&value, ptr, माप(u64));
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	अगर (!needs_swap)
		वापस value;

	चयन (field->size) अणु
	हाल 2:
		वापस bswap_16(value);
	हाल 4:
		वापस bswap_32(value);
	हाल 8:
		वापस bswap_64(value);
	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

u64 evsel__पूर्णांकval(काष्ठा evsel *evsel, काष्ठा perf_sample *sample, स्थिर अक्षर *name)
अणु
	काष्ठा tep_क्रमmat_field *field = evsel__field(evsel, name);

	अगर (!field)
		वापस 0;

	वापस field ? क्रमmat_field__पूर्णांकval(field, sample, evsel->needs_swap) : 0;
पूर्ण

bool evsel__fallback(काष्ठा evsel *evsel, पूर्णांक err, अक्षर *msg, माप_प्रकार msgsize)
अणु
	पूर्णांक paranoid;

	अगर ((err == ENOENT || err == ENXIO || err == ENODEV) &&
	    evsel->core.attr.type   == PERF_TYPE_HARDWARE &&
	    evsel->core.attr.config == PERF_COUNT_HW_CPU_CYCLES) अणु
		/*
		 * If it's cycles then fall back to hrसमयr based
		 * cpu-घड़ी-tick sw counter, which is always available even अगर
		 * no PMU support.
		 *
		 * PPC वापसs ENXIO until 2.6.37 (behavior changed with commit
		 * b0a873e).
		 */
		scnम_लिखो(msg, msgsize, "%s",
"The cycles event is not supported, trying to fall back to cpu-clock-ticks");

		evsel->core.attr.type   = PERF_TYPE_SOFTWARE;
		evsel->core.attr.config = PERF_COUNT_SW_CPU_CLOCK;

		zमुक्त(&evsel->name);
		वापस true;
	पूर्ण अन्यथा अगर (err == EACCES && !evsel->core.attr.exclude_kernel &&
		   (paranoid = perf_event_paranoid()) > 1) अणु
		स्थिर अक्षर *name = evsel__name(evsel);
		अक्षर *new_name;
		स्थिर अक्षर *sep = ":";

		/* If event has exclude user then करोn't exclude kernel. */
		अगर (evsel->core.attr.exclude_user)
			वापस false;

		/* Is there alपढ़ोy the separator in the name. */
		अगर (म_अक्षर(name, '/') ||
		    (म_अक्षर(name, ':') && !evsel->is_libpfm_event))
			sep = "";

		अगर (aप्र_लिखो(&new_name, "%s%su", name, sep) < 0)
			वापस false;

		अगर (evsel->name)
			मुक्त(evsel->name);
		evsel->name = new_name;
		scnम_लिखो(msg, msgsize, "kernel.perf_event_paranoid=%d, trying "
			  "to fall back to excluding kernel and hypervisor "
			  " samples", paranoid);
		evsel->core.attr.exclude_kernel = 1;
		evsel->core.attr.exclude_hv     = 1;

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool find_process(स्थिर अक्षर *name)
अणु
	माप_प्रकार len = म_माप(name);
	सूची *dir;
	काष्ठा dirent *d;
	पूर्णांक ret = -1;

	dir = सूची_खोलो(procfs__mountpoपूर्णांक());
	अगर (!dir)
		वापस false;

	/* Walk through the directory. */
	जबतक (ret && (d = सूची_पढ़ो(dir)) != शून्य) अणु
		अक्षर path[PATH_MAX];
		अक्षर *data;
		माप_प्रकार size;

		अगर ((d->d_type != DT_सूची) ||
		     !म_भेद(".", d->d_name) ||
		     !म_भेद("..", d->d_name))
			जारी;

		scnम_लिखो(path, माप(path), "%s/%s/comm",
			  procfs__mountpoपूर्णांक(), d->d_name);

		अगर (filename__पढ़ो_str(path, &data, &size))
			जारी;

		ret = म_भेदन(name, data, len);
		मुक्त(data);
	पूर्ण

	बंद_सूची(dir);
	वापस ret ? false : true;
पूर्ण

पूर्णांक evsel__खोलो_म_त्रुटि(काष्ठा evsel *evsel, काष्ठा target *target,
			 पूर्णांक err, अक्षर *msg, माप_प्रकार size)
अणु
	अक्षर sbuf[STRERR_बफ_मानE];
	पूर्णांक prपूर्णांकed = 0, enक्रमced = 0;

	चयन (err) अणु
	हाल EPERM:
	हाल EACCES:
		prपूर्णांकed += scnम_लिखो(msg + prपूर्णांकed, size - prपूर्णांकed,
			"Access to performance monitoring and observability operations is limited.\n");

		अगर (!sysfs__पढ़ो_पूर्णांक("fs/selinux/enforce", &enक्रमced)) अणु
			अगर (enक्रमced) अणु
				prपूर्णांकed += scnम_लिखो(msg + prपूर्णांकed, size - prपूर्णांकed,
					"Enforced MAC policy settings (SELinux) can limit access to performance\n"
					"monitoring and observability operations. Inspect system audit records for\n"
					"more perf_event access control information and adjusting the policy.\n");
			पूर्ण
		पूर्ण

		अगर (err == EPERM)
			prपूर्णांकed += scnम_लिखो(msg, size,
				"No permission to enable %s event.\n\n", evsel__name(evsel));

		वापस scnम_लिखो(msg + prपूर्णांकed, size - prपूर्णांकed,
		 "Consider adjusting /proc/sys/kernel/perf_event_paranoid setting to open\n"
		 "access to performance monitoring and observability operations for processes\n"
		 "without CAP_PERFMON, CAP_SYS_PTRACE or CAP_SYS_ADMIN Linux capability.\n"
		 "More information can be found at 'Perf events and tool security' document:\n"
		 "https://www.kernel.org/doc/html/latest/admin-guide/perf-security.html\n"
		 "perf_event_paranoid setting is %d:\n"
		 "  -1: Allow use of (almost) all events by all users\n"
		 "      Ignore mlock limit after perf_event_mlock_kb without CAP_IPC_LOCK\n"
		 ">= 0: Disallow raw and ftrace function tracepoint access\n"
		 ">= 1: Disallow CPU event access\n"
		 ">= 2: Disallow kernel profiling\n"
		 "To make the adjusted perf_event_paranoid setting permanent preserve it\n"
		 "in /etc/sysctl.conf (e.g. kernel.perf_event_paranoid = <setting>)",
		 perf_event_paranoid());
	हाल ENOENT:
		वापस scnम_लिखो(msg, size, "The %s event is not supported.", evsel__name(evsel));
	हाल EMखाता:
		वापस scnम_लिखो(msg, size, "%s",
			 "Too many events are opened.\n"
			 "Probably the maximum number of open file descriptors has been reached.\n"
			 "Hint: Try again after reducing the number of events.\n"
			 "Hint: Try increasing the limit with 'ulimit -n <limit>'");
	हाल ENOMEM:
		अगर (evsel__has_callchain(evsel) &&
		    access("/proc/sys/kernel/perf_event_max_stack", F_OK) == 0)
			वापस scnम_लिखो(msg, size,
					 "Not enough memory to setup event with callchain.\n"
					 "Hint: Try tweaking /proc/sys/kernel/perf_event_max_stack\n"
					 "Hint: Current value: %d", sysctl__max_stack());
		अवरोध;
	हाल ENODEV:
		अगर (target->cpu_list)
			वापस scnम_लिखो(msg, size, "%s",
	 "No such device - did you specify an out-of-range profile CPU?");
		अवरोध;
	हाल EOPNOTSUPP:
		अगर (evsel->core.attr.aux_output)
			वापस scnम_लिखो(msg, size,
	"%s: PMU Hardware doesn't support 'aux_output' feature",
					 evsel__name(evsel));
		अगर (evsel->core.attr.sample_period != 0)
			वापस scnम_लिखो(msg, size,
	"%s: PMU Hardware doesn't support sampling/overflow-interrupts. Try 'perf stat'",
					 evsel__name(evsel));
		अगर (evsel->core.attr.precise_ip)
			वापस scnम_लिखो(msg, size, "%s",
	"\'precise\' request may not be supported. Try removing 'p' modifier.");
#अगर defined(__i386__) || defined(__x86_64__)
		अगर (evsel->core.attr.type == PERF_TYPE_HARDWARE)
			वापस scnम_लिखो(msg, size, "%s",
	"No hardware sampling interrupt available.\n");
#पूर्ण_अगर
		अवरोध;
	हाल EBUSY:
		अगर (find_process("oprofiled"))
			वापस scnम_लिखो(msg, size,
	"The PMU counters are busy/taken by another profiler.\n"
	"We found oprofile daemon running, please stop it and try again.");
		अवरोध;
	हाल EINVAL:
		अगर (evsel->core.attr.sample_type & PERF_SAMPLE_CODE_PAGE_SIZE && perf_missing_features.code_page_size)
			वापस scnम_लिखो(msg, size, "Asking for the code page size isn't supported by this kernel.");
		अगर (evsel->core.attr.sample_type & PERF_SAMPLE_DATA_PAGE_SIZE && perf_missing_features.data_page_size)
			वापस scnम_लिखो(msg, size, "Asking for the data page size isn't supported by this kernel.");
		अगर (evsel->core.attr.ग_लिखो_backward && perf_missing_features.ग_लिखो_backward)
			वापस scnम_लिखो(msg, size, "Reading from overwrite event is not supported by this kernel.");
		अगर (perf_missing_features.घड़ीid)
			वापस scnम_लिखो(msg, size, "clockid feature not supported.");
		अगर (perf_missing_features.घड़ीid_wrong)
			वापस scnम_लिखो(msg, size, "wrong clockid (%d).", घड़ीid);
		अगर (perf_missing_features.aux_output)
			वापस scnम_लिखो(msg, size, "The 'aux_output' feature is not supported, update the kernel.");
		अवरोध;
	हाल ENODATA:
		वापस scnम_लिखो(msg, size, "Cannot collect data source with the load latency event alone. "
				 "Please add an auxiliary event in front of the load latency event.");
	शेष:
		अवरोध;
	पूर्ण

	वापस scnम_लिखो(msg, size,
	"The sys_perf_event_open() syscall returned with %d (%s) for event (%s).\n"
	"/bin/dmesg | grep -i perf may provide additional information.\n",
			 err, str_error_r(err, sbuf, माप(sbuf)), evsel__name(evsel));
पूर्ण

काष्ठा perf_env *evsel__env(काष्ठा evsel *evsel)
अणु
	अगर (evsel && evsel->evlist)
		वापस evsel->evlist->env;
	वापस &perf_env;
पूर्ण

अटल पूर्णांक store_evsel_ids(काष्ठा evsel *evsel, काष्ठा evlist *evlist)
अणु
	पूर्णांक cpu, thपढ़ो;

	क्रम (cpu = 0; cpu < xyarray__max_x(evsel->core.fd); cpu++) अणु
		क्रम (thपढ़ो = 0; thपढ़ो < xyarray__max_y(evsel->core.fd);
		     thपढ़ो++) अणु
			पूर्णांक fd = FD(evsel, cpu, thपढ़ो);

			अगर (perf_evlist__id_add_fd(&evlist->core, &evsel->core,
						   cpu, thपढ़ो, fd) < 0)
				वापस -1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक evsel__store_ids(काष्ठा evsel *evsel, काष्ठा evlist *evlist)
अणु
	काष्ठा perf_cpu_map *cpus = evsel->core.cpus;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs = evsel->core.thपढ़ोs;

	अगर (perf_evsel__alloc_id(&evsel->core, cpus->nr, thपढ़ोs->nr))
		वापस -ENOMEM;

	वापस store_evsel_ids(evsel, evlist);
पूर्ण

व्योम evsel__zero_per_pkg(काष्ठा evsel *evsel)
अणु
	काष्ठा hashmap_entry *cur;
	माप_प्रकार bkt;

	अगर (evsel->per_pkg_mask) अणु
		hashmap__क्रम_each_entry(evsel->per_pkg_mask, cur, bkt)
			मुक्त((अक्षर *)cur->key);

		hashmap__clear(evsel->per_pkg_mask);
	पूर्ण
पूर्ण

bool evsel__is_hybrid(काष्ठा evsel *evsel)
अणु
	वापस evsel->pmu_name && perf_pmu__is_hybrid(evsel->pmu_name);
पूर्ण
