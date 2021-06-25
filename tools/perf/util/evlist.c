<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011, Red Hat Inc, Arnalकरो Carvalho de Melo <acme@redhat.com>
 *
 * Parts came from builtin-अणुtop,stat,recordपूर्ण.c, see those files क्रम further
 * copyright notes.
 */
#समावेश <api/fs/fs.h>
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <poll.h>
#समावेश "cpumap.h"
#समावेश "util/mmap.h"
#समावेश "thread_map.h"
#समावेश "target.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "debug.h"
#समावेश "units.h"
#समावेश "bpf_counter.h"
#समावेश <पूर्णांकernal/lib.h> // page_size
#समावेश "affinity.h"
#समावेश "../perf.h"
#समावेश "asm/bug.h"
#समावेश "bpf-event.h"
#समावेश "util/string2.h"
#समावेश "util/perf_api_probe.h"
#समावेश "util/evsel_fprintf.h"
#समावेश "util/evlist-hybrid.h"
#समावेश <संकेत.स>
#समावेश <unistd.h>
#समावेश <sched.h>
#समावेश <मानककोष.स>

#समावेश "parse-events.h"
#समावेश <subcmd/parse-options.h>

#समावेश <fcntl.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/mman.h>
#समावेश <sys/prctl.h>

#समावेश <linux/bitops.h>
#समावेश <linux/hash.h>
#समावेश <linux/log2.h>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>
#समावेश <perf/evlist.h>
#समावेश <perf/evsel.h>
#समावेश <perf/cpumap.h>
#समावेश <perf/mmap.h>

#समावेश <पूर्णांकernal/xyarray.h>

#अगर_घोषित LACKS_SIGQUEUE_PROTOTYPE
पूर्णांक sigqueue(pid_t pid, पूर्णांक sig, स्थिर जोड़ sigval value);
#पूर्ण_अगर

#घोषणा FD(e, x, y) (*(पूर्णांक *)xyarray__entry(e->core.fd, x, y))
#घोषणा SID(e, x, y) xyarray__entry(e->core.sample_id, x, y)

व्योम evlist__init(काष्ठा evlist *evlist, काष्ठा perf_cpu_map *cpus,
		  काष्ठा perf_thपढ़ो_map *thपढ़ोs)
अणु
	perf_evlist__init(&evlist->core);
	perf_evlist__set_maps(&evlist->core, cpus, thपढ़ोs);
	evlist->workload.pid = -1;
	evlist->bkw_mmap_state = BKW_MMAP_NOTREADY;
	evlist->ctl_fd.fd = -1;
	evlist->ctl_fd.ack = -1;
	evlist->ctl_fd.pos = -1;
पूर्ण

काष्ठा evlist *evlist__new(व्योम)
अणु
	काष्ठा evlist *evlist = zalloc(माप(*evlist));

	अगर (evlist != शून्य)
		evlist__init(evlist, शून्य, शून्य);

	वापस evlist;
पूर्ण

काष्ठा evlist *evlist__new_शेष(व्योम)
अणु
	काष्ठा evlist *evlist = evlist__new();

	अगर (evlist && evlist__add_शेष(evlist)) अणु
		evlist__delete(evlist);
		evlist = शून्य;
	पूर्ण

	वापस evlist;
पूर्ण

काष्ठा evlist *evlist__new_dummy(व्योम)
अणु
	काष्ठा evlist *evlist = evlist__new();

	अगर (evlist && evlist__add_dummy(evlist)) अणु
		evlist__delete(evlist);
		evlist = शून्य;
	पूर्ण

	वापस evlist;
पूर्ण

/**
 * evlist__set_id_pos - set the positions of event ids.
 * @evlist: selected event list
 *
 * Events with compatible sample types all have the same id_pos
 * and is_pos.  For convenience, put a copy on evlist.
 */
व्योम evlist__set_id_pos(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *first = evlist__first(evlist);

	evlist->id_pos = first->id_pos;
	evlist->is_pos = first->is_pos;
पूर्ण

अटल व्योम evlist__update_id_pos(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel)
		evsel__calc_id_pos(evsel);

	evlist__set_id_pos(evlist);
पूर्ण

अटल व्योम evlist__purge(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *pos, *n;

	evlist__क्रम_each_entry_safe(evlist, n, pos) अणु
		list_del_init(&pos->core.node);
		pos->evlist = शून्य;
		evsel__delete(pos);
	पूर्ण

	evlist->core.nr_entries = 0;
पूर्ण

व्योम evlist__निकास(काष्ठा evlist *evlist)
अणु
	zमुक्त(&evlist->mmap);
	zमुक्त(&evlist->overग_लिखो_mmap);
	perf_evlist__निकास(&evlist->core);
पूर्ण

व्योम evlist__delete(काष्ठा evlist *evlist)
अणु
	अगर (evlist == शून्य)
		वापस;

	evlist__munmap(evlist);
	evlist__बंद(evlist);
	evlist__purge(evlist);
	evlist__निकास(evlist);
	मुक्त(evlist);
पूर्ण

व्योम evlist__add(काष्ठा evlist *evlist, काष्ठा evsel *entry)
अणु
	entry->evlist = evlist;
	entry->idx = evlist->core.nr_entries;
	entry->tracking = !entry->idx;

	perf_evlist__add(&evlist->core, &entry->core);

	अगर (evlist->core.nr_entries == 1)
		evlist__set_id_pos(evlist);
पूर्ण

व्योम evlist__हटाओ(काष्ठा evlist *evlist, काष्ठा evsel *evsel)
अणु
	evsel->evlist = शून्य;
	perf_evlist__हटाओ(&evlist->core, &evsel->core);
पूर्ण

व्योम evlist__splice_list_tail(काष्ठा evlist *evlist, काष्ठा list_head *list)
अणु
	जबतक (!list_empty(list)) अणु
		काष्ठा evsel *evsel, *temp, *leader = शून्य;

		__evlist__क्रम_each_entry_safe(list, temp, evsel) अणु
			list_del_init(&evsel->core.node);
			evlist__add(evlist, evsel);
			leader = evsel;
			अवरोध;
		पूर्ण

		__evlist__क्रम_each_entry_safe(list, temp, evsel) अणु
			अगर (evsel->leader == leader) अणु
				list_del_init(&evsel->core.node);
				evlist__add(evlist, evsel);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक __evlist__set_tracepoपूर्णांकs_handlers(काष्ठा evlist *evlist,
				       स्थिर काष्ठा evsel_str_handler *assocs, माप_प्रकार nr_assocs)
अणु
	माप_प्रकार i;
	पूर्णांक err;

	क्रम (i = 0; i < nr_assocs; i++) अणु
		// Adding a handler क्रम an event not in this evlist, just ignore it.
		काष्ठा evsel *evsel = evlist__find_tracepoपूर्णांक_by_name(evlist, assocs[i].name);
		अगर (evsel == शून्य)
			जारी;

		err = -EEXIST;
		अगर (evsel->handler != शून्य)
			जाओ out;
		evsel->handler = assocs[i].handler;
	पूर्ण

	err = 0;
out:
	वापस err;
पूर्ण

व्योम __evlist__set_leader(काष्ठा list_head *list)
अणु
	काष्ठा evsel *evsel, *leader;

	leader = list_entry(list->next, काष्ठा evsel, core.node);
	evsel = list_entry(list->prev, काष्ठा evsel, core.node);

	leader->core.nr_members = evsel->idx - leader->idx + 1;

	__evlist__क्रम_each_entry(list, evsel) अणु
		evsel->leader = leader;
	पूर्ण
पूर्ण

व्योम evlist__set_leader(काष्ठा evlist *evlist)
अणु
	अगर (evlist->core.nr_entries) अणु
		evlist->nr_groups = evlist->core.nr_entries > 1 ? 1 : 0;
		__evlist__set_leader(&evlist->core.entries);
	पूर्ण
पूर्ण

पूर्णांक __evlist__add_शेष(काष्ठा evlist *evlist, bool precise)
अणु
	काष्ठा evsel *evsel;

	evsel = evsel__new_cycles(precise, PERF_TYPE_HARDWARE,
				  PERF_COUNT_HW_CPU_CYCLES);
	अगर (evsel == शून्य)
		वापस -ENOMEM;

	evlist__add(evlist, evsel);
	वापस 0;
पूर्ण

पूर्णांक evlist__add_dummy(काष्ठा evlist *evlist)
अणु
	काष्ठा perf_event_attr attr = अणु
		.type	= PERF_TYPE_SOFTWARE,
		.config = PERF_COUNT_SW_DUMMY,
		.size	= माप(attr), /* to capture ABI version */
	पूर्ण;
	काष्ठा evsel *evsel = evsel__new_idx(&attr, evlist->core.nr_entries);

	अगर (evsel == शून्य)
		वापस -ENOMEM;

	evlist__add(evlist, evsel);
	वापस 0;
पूर्ण

अटल पूर्णांक evlist__add_attrs(काष्ठा evlist *evlist, काष्ठा perf_event_attr *attrs, माप_प्रकार nr_attrs)
अणु
	काष्ठा evsel *evsel, *n;
	LIST_HEAD(head);
	माप_प्रकार i;

	क्रम (i = 0; i < nr_attrs; i++) अणु
		evsel = evsel__new_idx(attrs + i, evlist->core.nr_entries + i);
		अगर (evsel == शून्य)
			जाओ out_delete_partial_list;
		list_add_tail(&evsel->core.node, &head);
	पूर्ण

	evlist__splice_list_tail(evlist, &head);

	वापस 0;

out_delete_partial_list:
	__evlist__क्रम_each_entry_safe(&head, n, evsel)
		evsel__delete(evsel);
	वापस -1;
पूर्ण

पूर्णांक __evlist__add_शेष_attrs(काष्ठा evlist *evlist, काष्ठा perf_event_attr *attrs, माप_प्रकार nr_attrs)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < nr_attrs; i++)
		event_attr_init(attrs + i);

	वापस evlist__add_attrs(evlist, attrs, nr_attrs);
पूर्ण

__weak पूर्णांक arch_evlist__add_शेष_attrs(काष्ठा evlist *evlist __maybe_unused)
अणु
	वापस 0;
पूर्ण

काष्ठा evsel *evlist__find_tracepoपूर्णांक_by_id(काष्ठा evlist *evlist, पूर्णांक id)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->core.attr.type   == PERF_TYPE_TRACEPOINT &&
		    (पूर्णांक)evsel->core.attr.config == id)
			वापस evsel;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा evsel *evlist__find_tracepoपूर्णांक_by_name(काष्ठा evlist *evlist, स्थिर अक्षर *name)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर ((evsel->core.attr.type == PERF_TYPE_TRACEPOINT) &&
		    (म_भेद(evsel->name, name) == 0))
			वापस evsel;
	पूर्ण

	वापस शून्य;
पूर्ण

पूर्णांक evlist__add_newtp(काष्ठा evlist *evlist, स्थिर अक्षर *sys, स्थिर अक्षर *name, व्योम *handler)
अणु
	काष्ठा evsel *evsel = evsel__newtp(sys, name);

	अगर (IS_ERR(evsel))
		वापस -1;

	evsel->handler = handler;
	evlist__add(evlist, evsel);
	वापस 0;
पूर्ण

अटल पूर्णांक evlist__nr_thपढ़ोs(काष्ठा evlist *evlist, काष्ठा evsel *evsel)
अणु
	अगर (evsel->core.प्रणाली_wide)
		वापस 1;
	अन्यथा
		वापस perf_thपढ़ो_map__nr(evlist->core.thपढ़ोs);
पूर्ण

व्योम evlist__cpu_iter_start(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *pos;

	/*
	 * Reset the per evsel cpu_iter. This is needed because
	 * each evsel's cpumap may have a dअगरferent index space,
	 * and some operations need the index to modअगरy
	 * the FD xyarray (e.g. खोलो, बंद)
	 */
	evlist__क्रम_each_entry(evlist, pos)
		pos->cpu_iter = 0;
पूर्ण

bool evsel__cpu_iter_skip_no_inc(काष्ठा evsel *ev, पूर्णांक cpu)
अणु
	अगर (ev->cpu_iter >= ev->core.cpus->nr)
		वापस true;
	अगर (cpu >= 0 && ev->core.cpus->map[ev->cpu_iter] != cpu)
		वापस true;
	वापस false;
पूर्ण

bool evsel__cpu_iter_skip(काष्ठा evsel *ev, पूर्णांक cpu)
अणु
	अगर (!evsel__cpu_iter_skip_no_inc(ev, cpu)) अणु
		ev->cpu_iter++;
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक evsel__म_भेद(काष्ठा evsel *pos, अक्षर *evsel_name)
अणु
	अगर (!evsel_name)
		वापस 0;
	अगर (evsel__is_dummy_event(pos))
		वापस 1;
	वापस म_भेद(pos->name, evsel_name);
पूर्ण

अटल पूर्णांक evlist__is_enabled(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *pos;

	evlist__क्रम_each_entry(evlist, pos) अणु
		अगर (!evsel__is_group_leader(pos) || !pos->core.fd)
			जारी;
		/* If at least one event is enabled, evlist is enabled. */
		अगर (!pos->disabled)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम __evlist__disable(काष्ठा evlist *evlist, अक्षर *evsel_name)
अणु
	काष्ठा evsel *pos;
	काष्ठा affinity affinity;
	पूर्णांक cpu, i, imm = 0;
	bool has_imm = false;

	अगर (affinity__setup(&affinity) < 0)
		वापस;

	/* Disable 'immediate' events last */
	क्रम (imm = 0; imm <= 1; imm++) अणु
		evlist__क्रम_each_cpu(evlist, i, cpu) अणु
			affinity__set(&affinity, cpu);

			evlist__क्रम_each_entry(evlist, pos) अणु
				अगर (evsel__म_भेद(pos, evsel_name))
					जारी;
				अगर (evsel__cpu_iter_skip(pos, cpu))
					जारी;
				अगर (pos->disabled || !evsel__is_group_leader(pos) || !pos->core.fd)
					जारी;
				अगर (pos->immediate)
					has_imm = true;
				अगर (pos->immediate != imm)
					जारी;
				evsel__disable_cpu(pos, pos->cpu_iter - 1);
			पूर्ण
		पूर्ण
		अगर (!has_imm)
			अवरोध;
	पूर्ण

	affinity__cleanup(&affinity);
	evlist__क्रम_each_entry(evlist, pos) अणु
		अगर (evsel__म_भेद(pos, evsel_name))
			जारी;
		अगर (!evsel__is_group_leader(pos) || !pos->core.fd)
			जारी;
		pos->disabled = true;
	पूर्ण

	/*
	 * If we disabled only single event, we need to check
	 * the enabled state of the evlist manually.
	 */
	अगर (evsel_name)
		evlist->enabled = evlist__is_enabled(evlist);
	अन्यथा
		evlist->enabled = false;
पूर्ण

व्योम evlist__disable(काष्ठा evlist *evlist)
अणु
	__evlist__disable(evlist, शून्य);
पूर्ण

व्योम evlist__disable_evsel(काष्ठा evlist *evlist, अक्षर *evsel_name)
अणु
	__evlist__disable(evlist, evsel_name);
पूर्ण

अटल व्योम __evlist__enable(काष्ठा evlist *evlist, अक्षर *evsel_name)
अणु
	काष्ठा evsel *pos;
	काष्ठा affinity affinity;
	पूर्णांक cpu, i;

	अगर (affinity__setup(&affinity) < 0)
		वापस;

	evlist__क्रम_each_cpu(evlist, i, cpu) अणु
		affinity__set(&affinity, cpu);

		evlist__क्रम_each_entry(evlist, pos) अणु
			अगर (evsel__म_भेद(pos, evsel_name))
				जारी;
			अगर (evsel__cpu_iter_skip(pos, cpu))
				जारी;
			अगर (!evsel__is_group_leader(pos) || !pos->core.fd)
				जारी;
			evsel__enable_cpu(pos, pos->cpu_iter - 1);
		पूर्ण
	पूर्ण
	affinity__cleanup(&affinity);
	evlist__क्रम_each_entry(evlist, pos) अणु
		अगर (evsel__म_भेद(pos, evsel_name))
			जारी;
		अगर (!evsel__is_group_leader(pos) || !pos->core.fd)
			जारी;
		pos->disabled = false;
	पूर्ण

	/*
	 * Even single event sets the 'enabled' क्रम evlist,
	 * so the toggle can work properly and toggle to
	 * 'disabled' state.
	 */
	evlist->enabled = true;
पूर्ण

व्योम evlist__enable(काष्ठा evlist *evlist)
अणु
	__evlist__enable(evlist, शून्य);
पूर्ण

व्योम evlist__enable_evsel(काष्ठा evlist *evlist, अक्षर *evsel_name)
अणु
	__evlist__enable(evlist, evsel_name);
पूर्ण

व्योम evlist__toggle_enable(काष्ठा evlist *evlist)
अणु
	(evlist->enabled ? evlist__disable : evlist__enable)(evlist);
पूर्ण

अटल पूर्णांक evlist__enable_event_cpu(काष्ठा evlist *evlist, काष्ठा evsel *evsel, पूर्णांक cpu)
अणु
	पूर्णांक thपढ़ो;
	पूर्णांक nr_thपढ़ोs = evlist__nr_thपढ़ोs(evlist, evsel);

	अगर (!evsel->core.fd)
		वापस -EINVAL;

	क्रम (thपढ़ो = 0; thपढ़ो < nr_thपढ़ोs; thपढ़ो++) अणु
		पूर्णांक err = ioctl(FD(evsel, cpu, thपढ़ो), PERF_EVENT_IOC_ENABLE, 0);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक evlist__enable_event_thपढ़ो(काष्ठा evlist *evlist, काष्ठा evsel *evsel, पूर्णांक thपढ़ो)
अणु
	पूर्णांक cpu;
	पूर्णांक nr_cpus = perf_cpu_map__nr(evlist->core.cpus);

	अगर (!evsel->core.fd)
		वापस -EINVAL;

	क्रम (cpu = 0; cpu < nr_cpus; cpu++) अणु
		पूर्णांक err = ioctl(FD(evsel, cpu, thपढ़ो), PERF_EVENT_IOC_ENABLE, 0);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक evlist__enable_event_idx(काष्ठा evlist *evlist, काष्ठा evsel *evsel, पूर्णांक idx)
अणु
	bool per_cpu_mmaps = !perf_cpu_map__empty(evlist->core.cpus);

	अगर (per_cpu_mmaps)
		वापस evlist__enable_event_cpu(evlist, evsel, idx);

	वापस evlist__enable_event_thपढ़ो(evlist, evsel, idx);
पूर्ण

पूर्णांक evlist__add_pollfd(काष्ठा evlist *evlist, पूर्णांक fd)
अणु
	वापस perf_evlist__add_pollfd(&evlist->core, fd, शून्य, POLLIN, fdarray_flag__शेष);
पूर्ण

पूर्णांक evlist__filter_pollfd(काष्ठा evlist *evlist, लघु revents_and_mask)
अणु
	वापस perf_evlist__filter_pollfd(&evlist->core, revents_and_mask);
पूर्ण

#अगर_घोषित HAVE_EVENTFD_SUPPORT
पूर्णांक evlist__add_wakeup_eventfd(काष्ठा evlist *evlist, पूर्णांक fd)
अणु
	वापस perf_evlist__add_pollfd(&evlist->core, fd, शून्य, POLLIN,
				       fdarray_flag__nonfilterable);
पूर्ण
#पूर्ण_अगर

पूर्णांक evlist__poll(काष्ठा evlist *evlist, पूर्णांक समयout)
अणु
	वापस perf_evlist__poll(&evlist->core, समयout);
पूर्ण

काष्ठा perf_sample_id *evlist__id2sid(काष्ठा evlist *evlist, u64 id)
अणु
	काष्ठा hlist_head *head;
	काष्ठा perf_sample_id *sid;
	पूर्णांक hash;

	hash = hash_64(id, PERF_EVLIST__HLIST_BITS);
	head = &evlist->core.heads[hash];

	hlist_क्रम_each_entry(sid, head, node)
		अगर (sid->id == id)
			वापस sid;

	वापस शून्य;
पूर्ण

काष्ठा evsel *evlist__id2evsel(काष्ठा evlist *evlist, u64 id)
अणु
	काष्ठा perf_sample_id *sid;

	अगर (evlist->core.nr_entries == 1 || !id)
		वापस evlist__first(evlist);

	sid = evlist__id2sid(evlist, id);
	अगर (sid)
		वापस container_of(sid->evsel, काष्ठा evsel, core);

	अगर (!evlist__sample_id_all(evlist))
		वापस evlist__first(evlist);

	वापस शून्य;
पूर्ण

काष्ठा evsel *evlist__id2evsel_strict(काष्ठा evlist *evlist, u64 id)
अणु
	काष्ठा perf_sample_id *sid;

	अगर (!id)
		वापस शून्य;

	sid = evlist__id2sid(evlist, id);
	अगर (sid)
		वापस container_of(sid->evsel, काष्ठा evsel, core);

	वापस शून्य;
पूर्ण

अटल पूर्णांक evlist__event2id(काष्ठा evlist *evlist, जोड़ perf_event *event, u64 *id)
अणु
	स्थिर __u64 *array = event->sample.array;
	sमाप_प्रकार n;

	n = (event->header.size - माप(event->header)) >> 3;

	अगर (event->header.type == PERF_RECORD_SAMPLE) अणु
		अगर (evlist->id_pos >= n)
			वापस -1;
		*id = array[evlist->id_pos];
	पूर्ण अन्यथा अणु
		अगर (evlist->is_pos > n)
			वापस -1;
		n -= evlist->is_pos;
		*id = array[n];
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा evsel *evlist__event2evsel(काष्ठा evlist *evlist, जोड़ perf_event *event)
अणु
	काष्ठा evsel *first = evlist__first(evlist);
	काष्ठा hlist_head *head;
	काष्ठा perf_sample_id *sid;
	पूर्णांक hash;
	u64 id;

	अगर (evlist->core.nr_entries == 1)
		वापस first;

	अगर (!first->core.attr.sample_id_all &&
	    event->header.type != PERF_RECORD_SAMPLE)
		वापस first;

	अगर (evlist__event2id(evlist, event, &id))
		वापस शून्य;

	/* Synthesized events have an id of zero */
	अगर (!id)
		वापस first;

	hash = hash_64(id, PERF_EVLIST__HLIST_BITS);
	head = &evlist->core.heads[hash];

	hlist_क्रम_each_entry(sid, head, node) अणु
		अगर (sid->id == id)
			वापस container_of(sid->evsel, काष्ठा evsel, core);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक evlist__set_छोड़ोd(काष्ठा evlist *evlist, bool value)
अणु
	पूर्णांक i;

	अगर (!evlist->overग_लिखो_mmap)
		वापस 0;

	क्रम (i = 0; i < evlist->core.nr_mmaps; i++) अणु
		पूर्णांक fd = evlist->overग_लिखो_mmap[i].core.fd;
		पूर्णांक err;

		अगर (fd < 0)
			जारी;
		err = ioctl(fd, PERF_EVENT_IOC_PAUSE_OUTPUT, value ? 1 : 0);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक evlist__छोड़ो(काष्ठा evlist *evlist)
अणु
	वापस evlist__set_छोड़ोd(evlist, true);
पूर्ण

अटल पूर्णांक evlist__resume(काष्ठा evlist *evlist)
अणु
	वापस evlist__set_छोड़ोd(evlist, false);
पूर्ण

अटल व्योम evlist__munmap_noमुक्त(काष्ठा evlist *evlist)
अणु
	पूर्णांक i;

	अगर (evlist->mmap)
		क्रम (i = 0; i < evlist->core.nr_mmaps; i++)
			perf_mmap__munmap(&evlist->mmap[i].core);

	अगर (evlist->overग_लिखो_mmap)
		क्रम (i = 0; i < evlist->core.nr_mmaps; i++)
			perf_mmap__munmap(&evlist->overग_लिखो_mmap[i].core);
पूर्ण

व्योम evlist__munmap(काष्ठा evlist *evlist)
अणु
	evlist__munmap_noमुक्त(evlist);
	zमुक्त(&evlist->mmap);
	zमुक्त(&evlist->overग_लिखो_mmap);
पूर्ण

अटल व्योम perf_mmap__unmap_cb(काष्ठा perf_mmap *map)
अणु
	काष्ठा mmap *m = container_of(map, काष्ठा mmap, core);

	mmap__munmap(m);
पूर्ण

अटल काष्ठा mmap *evlist__alloc_mmap(काष्ठा evlist *evlist,
				       bool overग_लिखो)
अणु
	पूर्णांक i;
	काष्ठा mmap *map;

	map = zalloc(evlist->core.nr_mmaps * माप(काष्ठा mmap));
	अगर (!map)
		वापस शून्य;

	क्रम (i = 0; i < evlist->core.nr_mmaps; i++) अणु
		काष्ठा perf_mmap *prev = i ? &map[i - 1].core : शून्य;

		/*
		 * When the perf_mmap() call is made we grab one refcount, plus
		 * one extra to let perf_mmap__consume() get the last
		 * events after all real references (perf_mmap__get()) are
		 * dropped.
		 *
		 * Each PERF_EVENT_IOC_SET_OUTPUT poपूर्णांकs to this mmap and
		 * thus करोes perf_mmap__get() on it.
		 */
		perf_mmap__init(&map[i].core, prev, overग_लिखो, perf_mmap__unmap_cb);
	पूर्ण

	वापस map;
पूर्ण

अटल व्योम
perf_evlist__mmap_cb_idx(काष्ठा perf_evlist *_evlist,
			 काष्ठा perf_mmap_param *_mp,
			 पूर्णांक idx, bool per_cpu)
अणु
	काष्ठा evlist *evlist = container_of(_evlist, काष्ठा evlist, core);
	काष्ठा mmap_params *mp = container_of(_mp, काष्ठा mmap_params, core);

	auxtrace_mmap_params__set_idx(&mp->auxtrace_mp, evlist, idx, per_cpu);
पूर्ण

अटल काष्ठा perf_mmap*
perf_evlist__mmap_cb_get(काष्ठा perf_evlist *_evlist, bool overग_लिखो, पूर्णांक idx)
अणु
	काष्ठा evlist *evlist = container_of(_evlist, काष्ठा evlist, core);
	काष्ठा mmap *maps;

	maps = overग_लिखो ? evlist->overग_लिखो_mmap : evlist->mmap;

	अगर (!maps) अणु
		maps = evlist__alloc_mmap(evlist, overग_लिखो);
		अगर (!maps)
			वापस शून्य;

		अगर (overग_लिखो) अणु
			evlist->overग_लिखो_mmap = maps;
			अगर (evlist->bkw_mmap_state == BKW_MMAP_NOTREADY)
				evlist__toggle_bkw_mmap(evlist, BKW_MMAP_RUNNING);
		पूर्ण अन्यथा अणु
			evlist->mmap = maps;
		पूर्ण
	पूर्ण

	वापस &maps[idx].core;
पूर्ण

अटल पूर्णांक
perf_evlist__mmap_cb_mmap(काष्ठा perf_mmap *_map, काष्ठा perf_mmap_param *_mp,
			  पूर्णांक output, पूर्णांक cpu)
अणु
	काष्ठा mmap *map = container_of(_map, काष्ठा mmap, core);
	काष्ठा mmap_params *mp = container_of(_mp, काष्ठा mmap_params, core);

	वापस mmap__mmap(map, mp, output, cpu);
पूर्ण

अचिन्हित दीर्घ perf_event_mlock_kb_in_pages(व्योम)
अणु
	अचिन्हित दीर्घ pages;
	पूर्णांक max;

	अगर (sysctl__पढ़ो_पूर्णांक("kernel/perf_event_mlock_kb", &max) < 0) अणु
		/*
		 * Pick a once upon a समय good value, i.e. things look
		 * strange since we can't पढ़ो a sysctl value, but lets not
		 * die yet...
		 */
		max = 512;
	पूर्ण अन्यथा अणु
		max -= (page_size / 1024);
	पूर्ण

	pages = (max * 1024) / page_size;
	अगर (!is_घातer_of_2(pages))
		pages = roundकरोwn_घात_of_two(pages);

	वापस pages;
पूर्ण

माप_प्रकार evlist__mmap_size(अचिन्हित दीर्घ pages)
अणु
	अगर (pages == अच_पूर्णांक_उच्च)
		pages = perf_event_mlock_kb_in_pages();
	अन्यथा अगर (!is_घातer_of_2(pages))
		वापस 0;

	वापस (pages + 1) * page_size;
पूर्ण

अटल दीर्घ parse_pages_arg(स्थिर अक्षर *str, अचिन्हित दीर्घ min,
			    अचिन्हित दीर्घ max)
अणु
	अचिन्हित दीर्घ pages, val;
	अटल काष्ठा parse_tag tags[] = अणु
		अणु .tag  = 'B', .mult = 1       पूर्ण,
		अणु .tag  = 'K', .mult = 1 << 10 पूर्ण,
		अणु .tag  = 'M', .mult = 1 << 20 पूर्ण,
		अणु .tag  = 'G', .mult = 1 << 30 पूर्ण,
		अणु .tag  = 0 पूर्ण,
	पूर्ण;

	अगर (str == शून्य)
		वापस -EINVAL;

	val = parse_tag_value(str, tags);
	अगर (val != (अचिन्हित दीर्घ) -1) अणु
		/* we got file size value */
		pages = PERF_ALIGN(val, page_size) / page_size;
	पूर्ण अन्यथा अणु
		/* we got pages count value */
		अक्षर *eptr;
		pages = म_से_अदीर्घ(str, &eptr, 10);
		अगर (*eptr != '\0')
			वापस -EINVAL;
	पूर्ण

	अगर (pages == 0 && min == 0) अणु
		/* leave number of pages at 0 */
	पूर्ण अन्यथा अगर (!is_घातer_of_2(pages)) अणु
		अक्षर buf[100];

		/* round pages up to next घातer of 2 */
		pages = roundup_घात_of_two(pages);
		अगर (!pages)
			वापस -EINVAL;

		unit_number__scnम_लिखो(buf, माप(buf), pages * page_size);
		pr_info("rounding mmap pages size to %s (%lu pages)\n",
			buf, pages);
	पूर्ण

	अगर (pages > max)
		वापस -EINVAL;

	वापस pages;
पूर्ण

पूर्णांक __evlist__parse_mmap_pages(अचिन्हित पूर्णांक *mmap_pages, स्थिर अक्षर *str)
अणु
	अचिन्हित दीर्घ max = अच_पूर्णांक_उच्च;
	दीर्घ pages;

	अगर (max > SIZE_MAX / page_size)
		max = SIZE_MAX / page_size;

	pages = parse_pages_arg(str, 1, max);
	अगर (pages < 0) अणु
		pr_err("Invalid argument for --mmap_pages/-m\n");
		वापस -1;
	पूर्ण

	*mmap_pages = pages;
	वापस 0;
पूर्ण

पूर्णांक evlist__parse_mmap_pages(स्थिर काष्ठा option *opt, स्थिर अक्षर *str, पूर्णांक unset __maybe_unused)
अणु
	वापस __evlist__parse_mmap_pages(opt->value, str);
पूर्ण

/**
 * evlist__mmap_ex - Create mmaps to receive events.
 * @evlist: list of events
 * @pages: map length in pages
 * @overग_लिखो: overग_लिखो older events?
 * @auxtrace_pages - auxtrace map length in pages
 * @auxtrace_overग_लिखो - overग_लिखो older auxtrace data?
 *
 * If @overग_लिखो is %false the user needs to संकेत event consumption using
 * perf_mmap__ग_लिखो_tail().  Using evlist__mmap_पढ़ो() करोes this
 * स्वतःmatically.
 *
 * Similarly, अगर @auxtrace_overग_लिखो is %false the user needs to संकेत data
 * consumption using auxtrace_mmap__ग_लिखो_tail().
 *
 * Return: %0 on success, negative error code otherwise.
 */
पूर्णांक evlist__mmap_ex(काष्ठा evlist *evlist, अचिन्हित पूर्णांक pages,
			 अचिन्हित पूर्णांक auxtrace_pages,
			 bool auxtrace_overग_लिखो, पूर्णांक nr_cblocks, पूर्णांक affinity, पूर्णांक flush,
			 पूर्णांक comp_level)
अणु
	/*
	 * Delay setting mp.prot: set it beक्रमe calling perf_mmap__mmap.
	 * Its value is decided by evsel's ग_लिखो_backward.
	 * So &mp should not be passed through स्थिर poपूर्णांकer.
	 */
	काष्ठा mmap_params mp = अणु
		.nr_cblocks	= nr_cblocks,
		.affinity	= affinity,
		.flush		= flush,
		.comp_level	= comp_level
	पूर्ण;
	काष्ठा perf_evlist_mmap_ops ops = अणु
		.idx  = perf_evlist__mmap_cb_idx,
		.get  = perf_evlist__mmap_cb_get,
		.mmap = perf_evlist__mmap_cb_mmap,
	पूर्ण;

	evlist->core.mmap_len = evlist__mmap_size(pages);
	pr_debug("mmap size %zuB\n", evlist->core.mmap_len);

	auxtrace_mmap_params__init(&mp.auxtrace_mp, evlist->core.mmap_len,
				   auxtrace_pages, auxtrace_overग_लिखो);

	वापस perf_evlist__mmap_ops(&evlist->core, &ops, &mp.core);
पूर्ण

पूर्णांक evlist__mmap(काष्ठा evlist *evlist, अचिन्हित पूर्णांक pages)
अणु
	वापस evlist__mmap_ex(evlist, pages, 0, false, 0, PERF_AFFINITY_SYS, 1, 0);
पूर्ण

पूर्णांक evlist__create_maps(काष्ठा evlist *evlist, काष्ठा target *target)
अणु
	bool all_thपढ़ोs = (target->per_thपढ़ो && target->प्रणाली_wide);
	काष्ठा perf_cpu_map *cpus;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs;

	/*
	 * If specअगरy '-a' and '--per-thread' to perf record, perf record
	 * will override '--per-thread'. target->per_thपढ़ो = false and
	 * target->प्रणाली_wide = true.
	 *
	 * If specअगरy '--per-thread' only to perf record,
	 * target->per_thपढ़ो = true and target->प्रणाली_wide = false.
	 *
	 * So target->per_thपढ़ो && target->प्रणाली_wide is false.
	 * For perf record, thपढ़ो_map__new_str करोesn't call
	 * thपढ़ो_map__new_all_cpus. That will keep perf record's
	 * current behavior.
	 *
	 * For perf stat, it allows the हाल that target->per_thपढ़ो and
	 * target->प्रणाली_wide are all true. It means to collect प्रणाली-wide
	 * per-thपढ़ो data. thपढ़ो_map__new_str will call
	 * thपढ़ो_map__new_all_cpus to क्रमागतerate all thपढ़ोs.
	 */
	thपढ़ोs = thपढ़ो_map__new_str(target->pid, target->tid, target->uid,
				      all_thपढ़ोs);

	अगर (!thपढ़ोs)
		वापस -1;

	अगर (target__uses_dummy_map(target))
		cpus = perf_cpu_map__dummy_new();
	अन्यथा
		cpus = perf_cpu_map__new(target->cpu_list);

	अगर (!cpus)
		जाओ out_delete_thपढ़ोs;

	evlist->core.has_user_cpus = !!target->cpu_list;

	perf_evlist__set_maps(&evlist->core, cpus, thपढ़ोs);

	/* as evlist now has references, put count here */
	perf_cpu_map__put(cpus);
	perf_thपढ़ो_map__put(thपढ़ोs);

	वापस 0;

out_delete_thपढ़ोs:
	perf_thपढ़ो_map__put(thपढ़ोs);
	वापस -1;
पूर्ण

पूर्णांक evlist__apply_filters(काष्ठा evlist *evlist, काष्ठा evsel **err_evsel)
अणु
	काष्ठा evsel *evsel;
	पूर्णांक err = 0;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->filter == शून्य)
			जारी;

		/*
		 * filters only work क्रम tracepoपूर्णांक event, which करोesn't have cpu limit.
		 * So evlist and evsel should always be same.
		 */
		err = perf_evsel__apply_filter(&evsel->core, evsel->filter);
		अगर (err) अणु
			*err_evsel = evsel;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक evlist__set_tp_filter(काष्ठा evlist *evlist, स्थिर अक्षर *filter)
अणु
	काष्ठा evsel *evsel;
	पूर्णांक err = 0;

	अगर (filter == शून्य)
		वापस -1;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->core.attr.type != PERF_TYPE_TRACEPOINT)
			जारी;

		err = evsel__set_filter(evsel, filter);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक evlist__append_tp_filter(काष्ठा evlist *evlist, स्थिर अक्षर *filter)
अणु
	काष्ठा evsel *evsel;
	पूर्णांक err = 0;

	अगर (filter == शून्य)
		वापस -1;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->core.attr.type != PERF_TYPE_TRACEPOINT)
			जारी;

		err = evsel__append_tp_filter(evsel, filter);
		अगर (err)
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अक्षर *aप्र_लिखो__tp_filter_pids(माप_प्रकार npids, pid_t *pids)
अणु
	अक्षर *filter;
	माप_प्रकार i;

	क्रम (i = 0; i < npids; ++i) अणु
		अगर (i == 0) अणु
			अगर (aप्र_लिखो(&filter, "common_pid != %d", pids[i]) < 0)
				वापस शून्य;
		पूर्ण अन्यथा अणु
			अक्षर *पंचांगp;

			अगर (aप्र_लिखो(&पंचांगp, "%s && common_pid != %d", filter, pids[i]) < 0)
				जाओ out_मुक्त;

			मुक्त(filter);
			filter = पंचांगp;
		पूर्ण
	पूर्ण

	वापस filter;
out_मुक्त:
	मुक्त(filter);
	वापस शून्य;
पूर्ण

पूर्णांक evlist__set_tp_filter_pids(काष्ठा evlist *evlist, माप_प्रकार npids, pid_t *pids)
अणु
	अक्षर *filter = aप्र_लिखो__tp_filter_pids(npids, pids);
	पूर्णांक ret = evlist__set_tp_filter(evlist, filter);

	मुक्त(filter);
	वापस ret;
पूर्ण

पूर्णांक evlist__set_tp_filter_pid(काष्ठा evlist *evlist, pid_t pid)
अणु
	वापस evlist__set_tp_filter_pids(evlist, 1, &pid);
पूर्ण

पूर्णांक evlist__append_tp_filter_pids(काष्ठा evlist *evlist, माप_प्रकार npids, pid_t *pids)
अणु
	अक्षर *filter = aप्र_लिखो__tp_filter_pids(npids, pids);
	पूर्णांक ret = evlist__append_tp_filter(evlist, filter);

	मुक्त(filter);
	वापस ret;
पूर्ण

पूर्णांक evlist__append_tp_filter_pid(काष्ठा evlist *evlist, pid_t pid)
अणु
	वापस evlist__append_tp_filter_pids(evlist, 1, &pid);
पूर्ण

bool evlist__valid_sample_type(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *pos;

	अगर (evlist->core.nr_entries == 1)
		वापस true;

	अगर (evlist->id_pos < 0 || evlist->is_pos < 0)
		वापस false;

	evlist__क्रम_each_entry(evlist, pos) अणु
		अगर (pos->id_pos != evlist->id_pos ||
		    pos->is_pos != evlist->is_pos)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

u64 __evlist__combined_sample_type(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;

	अगर (evlist->combined_sample_type)
		वापस evlist->combined_sample_type;

	evlist__क्रम_each_entry(evlist, evsel)
		evlist->combined_sample_type |= evsel->core.attr.sample_type;

	वापस evlist->combined_sample_type;
पूर्ण

u64 evlist__combined_sample_type(काष्ठा evlist *evlist)
अणु
	evlist->combined_sample_type = 0;
	वापस __evlist__combined_sample_type(evlist);
पूर्ण

u64 evlist__combined_branch_type(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;
	u64 branch_type = 0;

	evlist__क्रम_each_entry(evlist, evsel)
		branch_type |= evsel->core.attr.branch_sample_type;
	वापस branch_type;
पूर्ण

bool evlist__valid_पढ़ो_क्रमmat(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *first = evlist__first(evlist), *pos = first;
	u64 पढ़ो_क्रमmat = first->core.attr.पढ़ो_क्रमmat;
	u64 sample_type = first->core.attr.sample_type;

	evlist__क्रम_each_entry(evlist, pos) अणु
		अगर (पढ़ो_क्रमmat != pos->core.attr.पढ़ो_क्रमmat) अणु
			pr_debug("Read format differs %#" PRIx64 " vs %#" PRIx64 "\n",
				 पढ़ो_क्रमmat, (u64)pos->core.attr.पढ़ो_क्रमmat);
		पूर्ण
	पूर्ण

	/* PERF_SAMPLE_READ implies PERF_FORMAT_ID. */
	अगर ((sample_type & PERF_SAMPLE_READ) &&
	    !(पढ़ो_क्रमmat & PERF_FORMAT_ID)) अणु
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

u16 evlist__id_hdr_size(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *first = evlist__first(evlist);
	काष्ठा perf_sample *data;
	u64 sample_type;
	u16 size = 0;

	अगर (!first->core.attr.sample_id_all)
		जाओ out;

	sample_type = first->core.attr.sample_type;

	अगर (sample_type & PERF_SAMPLE_TID)
		size += माप(data->tid) * 2;

       अगर (sample_type & PERF_SAMPLE_TIME)
		size += माप(data->समय);

	अगर (sample_type & PERF_SAMPLE_ID)
		size += माप(data->id);

	अगर (sample_type & PERF_SAMPLE_STREAM_ID)
		size += माप(data->stream_id);

	अगर (sample_type & PERF_SAMPLE_CPU)
		size += माप(data->cpu) * 2;

	अगर (sample_type & PERF_SAMPLE_IDENTIFIER)
		size += माप(data->id);
out:
	वापस size;
पूर्ण

bool evlist__valid_sample_id_all(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *first = evlist__first(evlist), *pos = first;

	evlist__क्रम_each_entry_जारी(evlist, pos) अणु
		अगर (first->core.attr.sample_id_all != pos->core.attr.sample_id_all)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

bool evlist__sample_id_all(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *first = evlist__first(evlist);
	वापस first->core.attr.sample_id_all;
पूर्ण

व्योम evlist__set_selected(काष्ठा evlist *evlist, काष्ठा evsel *evsel)
अणु
	evlist->selected = evsel;
पूर्ण

व्योम evlist__बंद(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;
	काष्ठा affinity affinity;
	पूर्णांक cpu, i;

	/*
	 * With perf record core.cpus is usually शून्य.
	 * Use the old method to handle this क्रम now.
	 */
	अगर (!evlist->core.cpus) अणु
		evlist__क्रम_each_entry_reverse(evlist, evsel)
			evsel__बंद(evsel);
		वापस;
	पूर्ण

	अगर (affinity__setup(&affinity) < 0)
		वापस;
	evlist__क्रम_each_cpu(evlist, i, cpu) अणु
		affinity__set(&affinity, cpu);

		evlist__क्रम_each_entry_reverse(evlist, evsel) अणु
			अगर (evsel__cpu_iter_skip(evsel, cpu))
			    जारी;
			perf_evsel__बंद_cpu(&evsel->core, evsel->cpu_iter - 1);
		पूर्ण
	पूर्ण
	affinity__cleanup(&affinity);
	evlist__क्रम_each_entry_reverse(evlist, evsel) अणु
		perf_evsel__मुक्त_fd(&evsel->core);
		perf_evsel__मुक्त_id(&evsel->core);
	पूर्ण
	perf_evlist__reset_id_hash(&evlist->core);
पूर्ण

अटल पूर्णांक evlist__create_syswide_maps(काष्ठा evlist *evlist)
अणु
	काष्ठा perf_cpu_map *cpus;
	काष्ठा perf_thपढ़ो_map *thपढ़ोs;
	पूर्णांक err = -ENOMEM;

	/*
	 * Try पढ़ोing /sys/devices/प्रणाली/cpu/online to get
	 * an all cpus map.
	 *
	 * FIXME: -ENOMEM is the best we can करो here, the cpu_map
	 * code needs an overhaul to properly क्रमward the
	 * error, and we may not want to करो that fallback to a
	 * शेष cpu identity map :-\
	 */
	cpus = perf_cpu_map__new(शून्य);
	अगर (!cpus)
		जाओ out;

	thपढ़ोs = perf_thपढ़ो_map__new_dummy();
	अगर (!thपढ़ोs)
		जाओ out_put;

	perf_evlist__set_maps(&evlist->core, cpus, thपढ़ोs);

	perf_thपढ़ो_map__put(thपढ़ोs);
out_put:
	perf_cpu_map__put(cpus);
out:
	वापस err;
पूर्ण

पूर्णांक evlist__खोलो(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;
	पूर्णांक err;

	/*
	 * Default: one fd per CPU, all thपढ़ोs, aka प्रणालीwide
	 * as sys_perf_event_खोलो(cpu = -1, thपढ़ो = -1) is EINVAL
	 */
	अगर (evlist->core.thपढ़ोs == शून्य && evlist->core.cpus == शून्य) अणु
		err = evlist__create_syswide_maps(evlist);
		अगर (err < 0)
			जाओ out_err;
	पूर्ण

	evlist__update_id_pos(evlist);

	evlist__क्रम_each_entry(evlist, evsel) अणु
		err = evsel__खोलो(evsel, evsel->core.cpus, evsel->core.thपढ़ोs);
		अगर (err < 0)
			जाओ out_err;
	पूर्ण

	वापस 0;
out_err:
	evlist__बंद(evlist);
	त्रुटि_सं = -err;
	वापस err;
पूर्ण

पूर्णांक evlist__prepare_workload(काष्ठा evlist *evlist, काष्ठा target *target, स्थिर अक्षर *argv[],
			     bool pipe_output, व्योम (*exec_error)(पूर्णांक signo, siginfo_t *info, व्योम *ucontext))
अणु
	पूर्णांक child_पढ़ोy_pipe[2], go_pipe[2];
	अक्षर bf;

	अगर (pipe(child_पढ़ोy_pipe) < 0) अणु
		लिखो_त्रुटि("failed to create 'ready' pipe");
		वापस -1;
	पूर्ण

	अगर (pipe(go_pipe) < 0) अणु
		लिखो_त्रुटि("failed to create 'go' pipe");
		जाओ out_बंद_पढ़ोy_pipe;
	पूर्ण

	evlist->workload.pid = विभाजन();
	अगर (evlist->workload.pid < 0) अणु
		लिखो_त्रुटि("failed to fork");
		जाओ out_बंद_pipes;
	पूर्ण

	अगर (!evlist->workload.pid) अणु
		पूर्णांक ret;

		अगर (pipe_output)
			dup2(2, 1);

		संकेत(संक_इति, संक_पूर्व);

		बंद(child_पढ़ोy_pipe[0]);
		बंद(go_pipe[1]);
		fcntl(go_pipe[0], F_SETFD, FD_CLOEXEC);

		/*
		 * Change the name of this process not to confuse --exclude-perf users
		 * that sees 'perf' in the winकरोw up to the execvp() and thinks that
		 * perf samples are not being excluded.
		 */
		prctl(PR_SET_NAME, "perf-exec");

		/*
		 * Tell the parent we're पढ़ोy to go
		 */
		बंद(child_पढ़ोy_pipe[1]);

		/*
		 * Wait until the parent tells us to go.
		 */
		ret = पढ़ो(go_pipe[0], &bf, 1);
		/*
		 * The parent will ask क्रम the execvp() to be perक्रमmed by
		 * writing exactly one byte, in workload.cork_fd, usually via
		 * evlist__start_workload().
		 *
		 * For cancelling the workload without actually running it,
		 * the parent will just बंद workload.cork_fd, without writing
		 * anything, i.e. पढ़ो will वापस zero and we just निकास()
		 * here.
		 */
		अगर (ret != 1) अणु
			अगर (ret == -1)
				लिखो_त्रुटि("unable to read pipe");
			निकास(ret);
		पूर्ण

		execvp(argv[0], (अक्षर **)argv);

		अगर (exec_error) अणु
			जोड़ sigval val;

			val.sival_पूर्णांक = त्रुटि_सं;
			अगर (sigqueue(getppid(), SIGUSR1, val))
				लिखो_त्रुटि(argv[0]);
		पूर्ण अन्यथा
			लिखो_त्रुटि(argv[0]);
		निकास(-1);
	पूर्ण

	अगर (exec_error) अणु
		काष्ठा sigaction act = अणु
			.sa_flags     = SA_SIGINFO,
			.sa_sigaction = exec_error,
		पूर्ण;
		sigaction(SIGUSR1, &act, शून्य);
	पूर्ण

	अगर (target__none(target)) अणु
		अगर (evlist->core.thपढ़ोs == शून्य) अणु
			ख_लिखो(मानक_त्रुटि, "FATAL: evlist->threads need to be set at this point (%s:%d).\n",
				__func__, __LINE__);
			जाओ out_बंद_pipes;
		पूर्ण
		perf_thपढ़ो_map__set_pid(evlist->core.thपढ़ोs, 0, evlist->workload.pid);
	पूर्ण

	बंद(child_पढ़ोy_pipe[1]);
	बंद(go_pipe[0]);
	/*
	 * रुको क्रम child to settle
	 */
	अगर (पढ़ो(child_पढ़ोy_pipe[0], &bf, 1) == -1) अणु
		लिखो_त्रुटि("unable to read pipe");
		जाओ out_बंद_pipes;
	पूर्ण

	fcntl(go_pipe[1], F_SETFD, FD_CLOEXEC);
	evlist->workload.cork_fd = go_pipe[1];
	बंद(child_पढ़ोy_pipe[0]);
	वापस 0;

out_बंद_pipes:
	बंद(go_pipe[0]);
	बंद(go_pipe[1]);
out_बंद_पढ़ोy_pipe:
	बंद(child_पढ़ोy_pipe[0]);
	बंद(child_पढ़ोy_pipe[1]);
	वापस -1;
पूर्ण

पूर्णांक evlist__start_workload(काष्ठा evlist *evlist)
अणु
	अगर (evlist->workload.cork_fd > 0) अणु
		अक्षर bf = 0;
		पूर्णांक ret;
		/*
		 * Remove the cork, let it rip!
		 */
		ret = ग_लिखो(evlist->workload.cork_fd, &bf, 1);
		अगर (ret < 0)
			लिखो_त्रुटि("unable to write to pipe");

		बंद(evlist->workload.cork_fd);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक evlist__parse_sample(काष्ठा evlist *evlist, जोड़ perf_event *event, काष्ठा perf_sample *sample)
अणु
	काष्ठा evsel *evsel = evlist__event2evsel(evlist, event);

	अगर (!evsel)
		वापस -EFAULT;
	वापस evsel__parse_sample(evsel, event, sample);
पूर्ण

पूर्णांक evlist__parse_sample_बारtamp(काष्ठा evlist *evlist, जोड़ perf_event *event, u64 *बारtamp)
अणु
	काष्ठा evsel *evsel = evlist__event2evsel(evlist, event);

	अगर (!evsel)
		वापस -EFAULT;
	वापस evsel__parse_sample_बारtamp(evsel, event, बारtamp);
पूर्ण

पूर्णांक evlist__म_त्रुटि_खोलो(काष्ठा evlist *evlist, पूर्णांक err, अक्षर *buf, माप_प्रकार size)
अणु
	पूर्णांक prपूर्णांकed, value;
	अक्षर sbuf[STRERR_बफ_मानE], *emsg = str_error_r(err, sbuf, माप(sbuf));

	चयन (err) अणु
	हाल EACCES:
	हाल EPERM:
		prपूर्णांकed = scnम_लिखो(buf, size,
				    "Error:\t%s.\n"
				    "Hint:\tCheck /proc/sys/kernel/perf_event_paranoid setting.", emsg);

		value = perf_event_paranoid();

		prपूर्णांकed += scnम_लिखो(buf + prपूर्णांकed, size - prपूर्णांकed, "\nHint:\t");

		अगर (value >= 2) अणु
			prपूर्णांकed += scnम_लिखो(buf + prपूर्णांकed, size - prपूर्णांकed,
					     "For your workloads it needs to be <= 1\nHint:\t");
		पूर्ण
		prपूर्णांकed += scnम_लिखो(buf + prपूर्णांकed, size - prपूर्णांकed,
				     "For system wide tracing it needs to be set to -1.\n");

		prपूर्णांकed += scnम_लिखो(buf + prपूर्णांकed, size - prपूर्णांकed,
				    "Hint:\tTry: 'sudo sh -c \"echo -1 > /proc/sys/kernel/perf_event_paranoid\"'\n"
				    "Hint:\tThe current value is %d.", value);
		अवरोध;
	हाल EINVAL: अणु
		काष्ठा evsel *first = evlist__first(evlist);
		पूर्णांक max_freq;

		अगर (sysctl__पढ़ो_पूर्णांक("kernel/perf_event_max_sample_rate", &max_freq) < 0)
			जाओ out_शेष;

		अगर (first->core.attr.sample_freq < (u64)max_freq)
			जाओ out_शेष;

		prपूर्णांकed = scnम_लिखो(buf, size,
				    "Error:\t%s.\n"
				    "Hint:\tCheck /proc/sys/kernel/perf_event_max_sample_rate.\n"
				    "Hint:\tThe current value is %d and %" PRIu64 " is being requested.",
				    emsg, max_freq, first->core.attr.sample_freq);
		अवरोध;
	पूर्ण
	शेष:
out_शेष:
		scnम_लिखो(buf, size, "%s", emsg);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक evlist__म_त्रुटि_mmap(काष्ठा evlist *evlist, पूर्णांक err, अक्षर *buf, माप_प्रकार size)
अणु
	अक्षर sbuf[STRERR_बफ_मानE], *emsg = str_error_r(err, sbuf, माप(sbuf));
	पूर्णांक pages_attempted = evlist->core.mmap_len / 1024, pages_max_per_user, prपूर्णांकed = 0;

	चयन (err) अणु
	हाल EPERM:
		sysctl__पढ़ो_पूर्णांक("kernel/perf_event_mlock_kb", &pages_max_per_user);
		prपूर्णांकed += scnम_लिखो(buf + prपूर्णांकed, size - prपूर्णांकed,
				     "Error:\t%s.\n"
				     "Hint:\tCheck /proc/sys/kernel/perf_event_mlock_kb (%d kB) setting.\n"
				     "Hint:\tTried using %zd kB.\n",
				     emsg, pages_max_per_user, pages_attempted);

		अगर (pages_attempted >= pages_max_per_user) अणु
			prपूर्णांकed += scnम_लिखो(buf + prपूर्णांकed, size - prपूर्णांकed,
					     "Hint:\tTry 'sudo sh -c \"echo %d > /proc/sys/kernel/perf_event_mlock_kb\"', or\n",
					     pages_max_per_user + pages_attempted);
		पूर्ण

		prपूर्णांकed += scnम_लिखो(buf + prपूर्णांकed, size - prपूर्णांकed,
				     "Hint:\tTry using a smaller -m/--mmap-pages value.");
		अवरोध;
	शेष:
		scnम_लिखो(buf, size, "%s", emsg);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

व्योम evlist__to_front(काष्ठा evlist *evlist, काष्ठा evsel *move_evsel)
अणु
	काष्ठा evsel *evsel, *n;
	LIST_HEAD(move);

	अगर (move_evsel == evlist__first(evlist))
		वापस;

	evlist__क्रम_each_entry_safe(evlist, n, evsel) अणु
		अगर (evsel->leader == move_evsel->leader)
			list_move_tail(&evsel->core.node, &move);
	पूर्ण

	list_splice(&move, &evlist->core.entries);
पूर्ण

काष्ठा evsel *evlist__get_tracking_event(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->tracking)
			वापस evsel;
	पूर्ण

	वापस evlist__first(evlist);
पूर्ण

व्योम evlist__set_tracking_event(काष्ठा evlist *evlist, काष्ठा evsel *tracking_evsel)
अणु
	काष्ठा evsel *evsel;

	अगर (tracking_evsel->tracking)
		वापस;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel != tracking_evsel)
			evsel->tracking = false;
	पूर्ण

	tracking_evsel->tracking = true;
पूर्ण

काष्ठा evsel *evlist__find_evsel_by_str(काष्ठा evlist *evlist, स्थिर अक्षर *str)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (!evsel->name)
			जारी;
		अगर (म_भेद(str, evsel->name) == 0)
			वापस evsel;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम evlist__toggle_bkw_mmap(काष्ठा evlist *evlist, क्रमागत bkw_mmap_state state)
अणु
	क्रमागत bkw_mmap_state old_state = evlist->bkw_mmap_state;
	क्रमागत action अणु
		NONE,
		PAUSE,
		RESUME,
	पूर्ण action = NONE;

	अगर (!evlist->overग_लिखो_mmap)
		वापस;

	चयन (old_state) अणु
	हाल BKW_MMAP_NOTREADY: अणु
		अगर (state != BKW_MMAP_RUNNING)
			जाओ state_err;
		अवरोध;
	पूर्ण
	हाल BKW_MMAP_RUNNING: अणु
		अगर (state != BKW_MMAP_DATA_PENDING)
			जाओ state_err;
		action = PAUSE;
		अवरोध;
	पूर्ण
	हाल BKW_MMAP_DATA_PENDING: अणु
		अगर (state != BKW_MMAP_EMPTY)
			जाओ state_err;
		अवरोध;
	पूर्ण
	हाल BKW_MMAP_EMPTY: अणु
		अगर (state != BKW_MMAP_RUNNING)
			जाओ state_err;
		action = RESUME;
		अवरोध;
	पूर्ण
	शेष:
		WARN_ONCE(1, "Shouldn't get there\n");
	पूर्ण

	evlist->bkw_mmap_state = state;

	चयन (action) अणु
	हाल PAUSE:
		evlist__छोड़ो(evlist);
		अवरोध;
	हाल RESUME:
		evlist__resume(evlist);
		अवरोध;
	हाल NONE:
	शेष:
		अवरोध;
	पूर्ण

state_err:
	वापस;
पूर्ण

bool evlist__exclude_kernel(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (!evsel->core.attr.exclude_kernel)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Events in data file are not collect in groups, but we still want
 * the group display. Set the artअगरicial group and set the leader's
 * क्रमced_leader flag to notअगरy the display code.
 */
व्योम evlist__क्रमce_leader(काष्ठा evlist *evlist)
अणु
	अगर (!evlist->nr_groups) अणु
		काष्ठा evsel *leader = evlist__first(evlist);

		evlist__set_leader(evlist);
		leader->क्रमced_leader = true;
	पूर्ण
पूर्ण

काष्ठा evsel *evlist__reset_weak_group(काष्ठा evlist *evsel_list, काष्ठा evsel *evsel, bool बंद)
अणु
	काष्ठा evsel *c2, *leader;
	bool is_खोलो = true;

	leader = evsel->leader;
	pr_debug("Weak group for %s/%d failed\n",
			leader->name, leader->core.nr_members);

	/*
	 * क्रम_each_group_member करोesn't work here because it doesn't
	 * include the first entry.
	 */
	evlist__क्रम_each_entry(evsel_list, c2) अणु
		अगर (c2 == evsel)
			is_खोलो = false;
		अगर (c2->leader == leader) अणु
			अगर (is_खोलो && बंद)
				perf_evsel__बंद(&c2->core);
			c2->leader = c2;
			c2->core.nr_members = 0;
			/*
			 * Set this क्रम all क्रमmer members of the group
			 * to indicate they get reखोलोed.
			 */
			c2->reset_group = true;
		पूर्ण
	पूर्ण
	वापस leader;
पूर्ण

अटल पूर्णांक evlist__parse_control_fअगरo(स्थिर अक्षर *str, पूर्णांक *ctl_fd, पूर्णांक *ctl_fd_ack, bool *ctl_fd_बंद)
अणु
	अक्षर *s, *p;
	पूर्णांक ret = 0, fd;

	अगर (म_भेदन(str, "fifo:", 5))
		वापस -EINVAL;

	str += 5;
	अगर (!*str || *str == ',')
		वापस -EINVAL;

	s = strdup(str);
	अगर (!s)
		वापस -ENOMEM;

	p = म_अक्षर(s, ',');
	अगर (p)
		*p = '\0';

	/*
	 * O_RDWR aव्योमs POLLHUPs which is necessary to allow the other
	 * end of a FIFO to be repeatedly खोलोed and बंदd.
	 */
	fd = खोलो(s, O_RDWR | O_NONBLOCK | O_CLOEXEC);
	अगर (fd < 0) अणु
		pr_err("Failed to open '%s'\n", s);
		ret = -त्रुटि_सं;
		जाओ out_मुक्त;
	पूर्ण
	*ctl_fd = fd;
	*ctl_fd_बंद = true;

	अगर (p && *++p) अणु
		/* O_RDWR | O_NONBLOCK means the other end need not be खोलो */
		fd = खोलो(p, O_RDWR | O_NONBLOCK | O_CLOEXEC);
		अगर (fd < 0) अणु
			pr_err("Failed to open '%s'\n", p);
			ret = -त्रुटि_सं;
			जाओ out_मुक्त;
		पूर्ण
		*ctl_fd_ack = fd;
	पूर्ण

out_मुक्त:
	मुक्त(s);
	वापस ret;
पूर्ण

पूर्णांक evlist__parse_control(स्थिर अक्षर *str, पूर्णांक *ctl_fd, पूर्णांक *ctl_fd_ack, bool *ctl_fd_बंद)
अणु
	अक्षर *comma = शून्य, *endptr = शून्य;

	*ctl_fd_बंद = false;

	अगर (म_भेदन(str, "fd:", 3))
		वापस evlist__parse_control_fअगरo(str, ctl_fd, ctl_fd_ack, ctl_fd_बंद);

	*ctl_fd = म_से_अदीर्घ(&str[3], &endptr, 0);
	अगर (endptr == &str[3])
		वापस -EINVAL;

	comma = म_अक्षर(str, ',');
	अगर (comma) अणु
		अगर (endptr != comma)
			वापस -EINVAL;

		*ctl_fd_ack = म_से_अदीर्घ(comma + 1, &endptr, 0);
		अगर (endptr == comma + 1 || *endptr != '\0')
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम evlist__बंद_control(पूर्णांक ctl_fd, पूर्णांक ctl_fd_ack, bool *ctl_fd_बंद)
अणु
	अगर (*ctl_fd_बंद) अणु
		*ctl_fd_बंद = false;
		बंद(ctl_fd);
		अगर (ctl_fd_ack >= 0)
			बंद(ctl_fd_ack);
	पूर्ण
पूर्ण

पूर्णांक evlist__initialize_ctlfd(काष्ठा evlist *evlist, पूर्णांक fd, पूर्णांक ack)
अणु
	अगर (fd == -1) अणु
		pr_debug("Control descriptor is not initialized\n");
		वापस 0;
	पूर्ण

	evlist->ctl_fd.pos = perf_evlist__add_pollfd(&evlist->core, fd, शून्य, POLLIN,
						     fdarray_flag__nonfilterable);
	अगर (evlist->ctl_fd.pos < 0) अणु
		evlist->ctl_fd.pos = -1;
		pr_err("Failed to add ctl fd entry: %m\n");
		वापस -1;
	पूर्ण

	evlist->ctl_fd.fd = fd;
	evlist->ctl_fd.ack = ack;

	वापस 0;
पूर्ण

bool evlist__ctlfd_initialized(काष्ठा evlist *evlist)
अणु
	वापस evlist->ctl_fd.pos >= 0;
पूर्ण

पूर्णांक evlist__finalize_ctlfd(काष्ठा evlist *evlist)
अणु
	काष्ठा pollfd *entries = evlist->core.pollfd.entries;

	अगर (!evlist__ctlfd_initialized(evlist))
		वापस 0;

	entries[evlist->ctl_fd.pos].fd = -1;
	entries[evlist->ctl_fd.pos].events = 0;
	entries[evlist->ctl_fd.pos].revents = 0;

	evlist->ctl_fd.pos = -1;
	evlist->ctl_fd.ack = -1;
	evlist->ctl_fd.fd = -1;

	वापस 0;
पूर्ण

अटल पूर्णांक evlist__ctlfd_recv(काष्ठा evlist *evlist, क्रमागत evlist_ctl_cmd *cmd,
			      अक्षर *cmd_data, माप_प्रकार data_size)
अणु
	पूर्णांक err;
	अक्षर c;
	माप_प्रकार bytes_पढ़ो = 0;

	*cmd = EVLIST_CTL_CMD_UNSUPPORTED;
	स_रखो(cmd_data, 0, data_size);
	data_size--;

	करो अणु
		err = पढ़ो(evlist->ctl_fd.fd, &c, 1);
		अगर (err > 0) अणु
			अगर (c == '\n' || c == '\0')
				अवरोध;
			cmd_data[bytes_पढ़ो++] = c;
			अगर (bytes_पढ़ो == data_size)
				अवरोध;
			जारी;
		पूर्ण अन्यथा अगर (err == -1) अणु
			अगर (त्रुटि_सं == EINTR)
				जारी;
			अगर (त्रुटि_सं == EAGAIN || त्रुटि_सं == EWOULDBLOCK)
				err = 0;
			अन्यथा
				pr_err("Failed to read from ctlfd %d: %m\n", evlist->ctl_fd.fd);
		पूर्ण
		अवरोध;
	पूर्ण जबतक (1);

	pr_debug("Message from ctl_fd: \"%s%s\"\n", cmd_data,
		 bytes_पढ़ो == data_size ? "" : c == '\n' ? "\\n" : "\\0");

	अगर (bytes_पढ़ो > 0) अणु
		अगर (!म_भेदन(cmd_data, EVLIST_CTL_CMD_ENABLE_TAG,
			     (माप(EVLIST_CTL_CMD_ENABLE_TAG)-1))) अणु
			*cmd = EVLIST_CTL_CMD_ENABLE;
		पूर्ण अन्यथा अगर (!म_भेदन(cmd_data, EVLIST_CTL_CMD_DISABLE_TAG,
				    (माप(EVLIST_CTL_CMD_DISABLE_TAG)-1))) अणु
			*cmd = EVLIST_CTL_CMD_DISABLE;
		पूर्ण अन्यथा अगर (!म_भेदन(cmd_data, EVLIST_CTL_CMD_SNAPSHOT_TAG,
				    (माप(EVLIST_CTL_CMD_SNAPSHOT_TAG)-1))) अणु
			*cmd = EVLIST_CTL_CMD_SNAPSHOT;
			pr_debug("is snapshot\n");
		पूर्ण अन्यथा अगर (!म_भेदन(cmd_data, EVLIST_CTL_CMD_EVLIST_TAG,
				    (माप(EVLIST_CTL_CMD_EVLIST_TAG)-1))) अणु
			*cmd = EVLIST_CTL_CMD_EVLIST;
		पूर्ण अन्यथा अगर (!म_भेदन(cmd_data, EVLIST_CTL_CMD_STOP_TAG,
				    (माप(EVLIST_CTL_CMD_STOP_TAG)-1))) अणु
			*cmd = EVLIST_CTL_CMD_STOP;
		पूर्ण अन्यथा अगर (!म_भेदन(cmd_data, EVLIST_CTL_CMD_PING_TAG,
				    (माप(EVLIST_CTL_CMD_PING_TAG)-1))) अणु
			*cmd = EVLIST_CTL_CMD_PING;
		पूर्ण
	पूर्ण

	वापस bytes_पढ़ो ? (पूर्णांक)bytes_पढ़ो : err;
पूर्ण

पूर्णांक evlist__ctlfd_ack(काष्ठा evlist *evlist)
अणु
	पूर्णांक err;

	अगर (evlist->ctl_fd.ack == -1)
		वापस 0;

	err = ग_लिखो(evlist->ctl_fd.ack, EVLIST_CTL_CMD_ACK_TAG,
		    माप(EVLIST_CTL_CMD_ACK_TAG));
	अगर (err == -1)
		pr_err("failed to write to ctl_ack_fd %d: %m\n", evlist->ctl_fd.ack);

	वापस err;
पूर्ण

अटल पूर्णांक get_cmd_arg(अक्षर *cmd_data, माप_प्रकार cmd_size, अक्षर **arg)
अणु
	अक्षर *data = cmd_data + cmd_size;

	/* no argument */
	अगर (!*data)
		वापस 0;

	/* there's argument */
	अगर (*data == ' ') अणु
		*arg = data + 1;
		वापस 1;
	पूर्ण

	/* malक्रमmed */
	वापस -1;
पूर्ण

अटल पूर्णांक evlist__ctlfd_enable(काष्ठा evlist *evlist, अक्षर *cmd_data, bool enable)
अणु
	काष्ठा evsel *evsel;
	अक्षर *name;
	पूर्णांक err;

	err = get_cmd_arg(cmd_data,
			  enable ? माप(EVLIST_CTL_CMD_ENABLE_TAG) - 1 :
				   माप(EVLIST_CTL_CMD_DISABLE_TAG) - 1,
			  &name);
	अगर (err < 0) अणु
		pr_info("failed: wrong command\n");
		वापस -1;
	पूर्ण

	अगर (err) अणु
		evsel = evlist__find_evsel_by_str(evlist, name);
		अगर (evsel) अणु
			अगर (enable)
				evlist__enable_evsel(evlist, name);
			अन्यथा
				evlist__disable_evsel(evlist, name);
			pr_info("Event %s %s\n", evsel->name,
				enable ? "enabled" : "disabled");
		पूर्ण अन्यथा अणु
			pr_info("failed: can't find '%s' event\n", name);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (enable) अणु
			evlist__enable(evlist);
			pr_info(EVLIST_ENABLED_MSG);
		पूर्ण अन्यथा अणु
			evlist__disable(evlist);
			pr_info(EVLIST_DISABLED_MSG);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक evlist__ctlfd_list(काष्ठा evlist *evlist, अक्षर *cmd_data)
अणु
	काष्ठा perf_attr_details details = अणु .verbose = false, पूर्ण;
	काष्ठा evsel *evsel;
	अक्षर *arg;
	पूर्णांक err;

	err = get_cmd_arg(cmd_data,
			  माप(EVLIST_CTL_CMD_EVLIST_TAG) - 1,
			  &arg);
	अगर (err < 0) अणु
		pr_info("failed: wrong command\n");
		वापस -1;
	पूर्ण

	अगर (err) अणु
		अगर (!म_भेद(arg, "-v")) अणु
			details.verbose = true;
		पूर्ण अन्यथा अगर (!म_भेद(arg, "-g")) अणु
			details.event_group = true;
		पूर्ण अन्यथा अगर (!म_भेद(arg, "-F")) अणु
			details.freq = true;
		पूर्ण अन्यथा अणु
			pr_info("failed: wrong command\n");
			वापस -1;
		पूर्ण
	पूर्ण

	evlist__क्रम_each_entry(evlist, evsel)
		evsel__ख_लिखो(evsel, &details, मानक_त्रुटि);

	वापस 0;
पूर्ण

पूर्णांक evlist__ctlfd_process(काष्ठा evlist *evlist, क्रमागत evlist_ctl_cmd *cmd)
अणु
	पूर्णांक err = 0;
	अक्षर cmd_data[EVLIST_CTL_CMD_MAX_LEN];
	पूर्णांक ctlfd_pos = evlist->ctl_fd.pos;
	काष्ठा pollfd *entries = evlist->core.pollfd.entries;

	अगर (!evlist__ctlfd_initialized(evlist) || !entries[ctlfd_pos].revents)
		वापस 0;

	अगर (entries[ctlfd_pos].revents & POLLIN) अणु
		err = evlist__ctlfd_recv(evlist, cmd, cmd_data,
					 EVLIST_CTL_CMD_MAX_LEN);
		अगर (err > 0) अणु
			चयन (*cmd) अणु
			हाल EVLIST_CTL_CMD_ENABLE:
			हाल EVLIST_CTL_CMD_DISABLE:
				err = evlist__ctlfd_enable(evlist, cmd_data,
							   *cmd == EVLIST_CTL_CMD_ENABLE);
				अवरोध;
			हाल EVLIST_CTL_CMD_EVLIST:
				err = evlist__ctlfd_list(evlist, cmd_data);
				अवरोध;
			हाल EVLIST_CTL_CMD_SNAPSHOT:
			हाल EVLIST_CTL_CMD_STOP:
			हाल EVLIST_CTL_CMD_PING:
				अवरोध;
			हाल EVLIST_CTL_CMD_ACK:
			हाल EVLIST_CTL_CMD_UNSUPPORTED:
			शेष:
				pr_debug("ctlfd: unsupported %d\n", *cmd);
				अवरोध;
			पूर्ण
			अगर (!(*cmd == EVLIST_CTL_CMD_ACK || *cmd == EVLIST_CTL_CMD_UNSUPPORTED ||
			      *cmd == EVLIST_CTL_CMD_SNAPSHOT))
				evlist__ctlfd_ack(evlist);
		पूर्ण
	पूर्ण

	अगर (entries[ctlfd_pos].revents & (POLLHUP | POLLERR))
		evlist__finalize_ctlfd(evlist);
	अन्यथा
		entries[ctlfd_pos].revents = 0;

	वापस err;
पूर्ण

काष्ठा evsel *evlist__find_evsel(काष्ठा evlist *evlist, पूर्णांक idx)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->idx == idx)
			वापस evsel;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक evlist__scnम_लिखो_evsels(काष्ठा evlist *evlist, माप_प्रकार size, अक्षर *bf)
अणु
	काष्ठा evsel *evsel;
	पूर्णांक prपूर्णांकed = 0;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel__is_dummy_event(evsel))
			जारी;
		अगर (size > (म_माप(evsel__name(evsel)) + (prपूर्णांकed ? 2 : 1))) अणु
			prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s%s", prपूर्णांकed ? "," : "", evsel__name(evsel));
		पूर्ण अन्यथा अणु
			prपूर्णांकed += scnम_लिखो(bf + prपूर्णांकed, size - prपूर्णांकed, "%s...", prपूर्णांकed ? "," : "");
			अवरोध;
		पूर्ण
	पूर्ण

	वापस prपूर्णांकed;
पूर्ण
