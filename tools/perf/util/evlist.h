<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_EVLIST_H
#घोषणा __PERF_EVLIST_H 1

#समावेश <linux/compiler.h>
#समावेश <linux/kernel.h>
#समावेश <linux/refcount.h>
#समावेश <linux/list.h>
#समावेश <api/fd/array.h>
#समावेश <पूर्णांकernal/evlist.h>
#समावेश <पूर्णांकernal/evsel.h>
#समावेश "events_stats.h"
#समावेश "evsel.h"
#समावेश <pthपढ़ो.h>
#समावेश <संकेत.स>
#समावेश <unistd.h>

काष्ठा pollfd;
काष्ठा thपढ़ो_map;
काष्ठा perf_cpu_map;
काष्ठा record_opts;

/*
 * State machine of bkw_mmap_state:
 *
 *                     .________________(क्रमbid)_____________.
 *                     |                                     V
 * NOTREADY --(0)--> RUNNING --(1)--> DATA_PENDING --(2)--> EMPTY
 *                     ^  ^              |   ^               |
 *                     |  |__(क्रमbid)____/   |___(क्रमbid)___/|
 *                     |                                     |
 *                      \_________________(3)_______________/
 *
 * NOTREADY     : Backward ring buffers are not पढ़ोy
 * RUNNING      : Backward ring buffers are recording
 * DATA_PENDING : We are required to collect data from backward ring buffers
 * EMPTY        : We have collected data from backward ring buffers.
 *
 * (0): Setup backward ring buffer
 * (1): Pause ring buffers क्रम पढ़ोing
 * (2): Read from ring buffers
 * (3): Resume ring buffers क्रम recording
 */
क्रमागत bkw_mmap_state अणु
	BKW_MMAP_NOTREADY,
	BKW_MMAP_RUNNING,
	BKW_MMAP_DATA_PENDING,
	BKW_MMAP_EMPTY,
पूर्ण;

काष्ठा evlist अणु
	काष्ठा perf_evlist core;
	पूर्णांक		 nr_groups;
	bool		 enabled;
	पूर्णांक		 id_pos;
	पूर्णांक		 is_pos;
	u64		 combined_sample_type;
	क्रमागत bkw_mmap_state bkw_mmap_state;
	काष्ठा अणु
		पूर्णांक	cork_fd;
		pid_t	pid;
	पूर्ण workload;
	काष्ठा mmap *mmap;
	काष्ठा mmap *overग_लिखो_mmap;
	काष्ठा evsel *selected;
	काष्ठा events_stats stats;
	काष्ठा perf_env	*env;
	व्योम (*trace_event_sample_raw)(काष्ठा evlist *evlist,
				       जोड़ perf_event *event,
				       काष्ठा perf_sample *sample);
	u64		first_sample_समय;
	u64		last_sample_समय;
	काष्ठा अणु
		pthपढ़ो_t		th;
		अस्थिर पूर्णांक		करोne;
	पूर्ण thपढ़ो;
	काष्ठा अणु
		पूर्णांक	fd;	/* control file descriptor */
		पूर्णांक	ack;	/* ack file descriptor क्रम control commands */
		पूर्णांक	pos;	/* index at evlist core object to check संकेतs */
	पूर्ण ctl_fd;
पूर्ण;

काष्ठा evsel_str_handler अणु
	स्थिर अक्षर *name;
	व्योम	   *handler;
पूर्ण;

काष्ठा evlist *evlist__new(व्योम);
काष्ठा evlist *evlist__new_शेष(व्योम);
काष्ठा evlist *evlist__new_dummy(व्योम);
व्योम evlist__init(काष्ठा evlist *evlist, काष्ठा perf_cpu_map *cpus,
		  काष्ठा perf_thपढ़ो_map *thपढ़ोs);
व्योम evlist__निकास(काष्ठा evlist *evlist);
व्योम evlist__delete(काष्ठा evlist *evlist);

व्योम evlist__add(काष्ठा evlist *evlist, काष्ठा evsel *entry);
व्योम evlist__हटाओ(काष्ठा evlist *evlist, काष्ठा evsel *evsel);

पूर्णांक __evlist__add_शेष(काष्ठा evlist *evlist, bool precise);

अटल अंतरभूत पूर्णांक evlist__add_शेष(काष्ठा evlist *evlist)
अणु
	वापस __evlist__add_शेष(evlist, true);
पूर्ण

पूर्णांक __evlist__add_शेष_attrs(काष्ठा evlist *evlist,
				     काष्ठा perf_event_attr *attrs, माप_प्रकार nr_attrs);

#घोषणा evlist__add_शेष_attrs(evlist, array) \
	__evlist__add_शेष_attrs(evlist, array, ARRAY_SIZE(array))

पूर्णांक arch_evlist__add_शेष_attrs(काष्ठा evlist *evlist);

पूर्णांक evlist__add_dummy(काष्ठा evlist *evlist);

पूर्णांक evlist__add_sb_event(काष्ठा evlist *evlist, काष्ठा perf_event_attr *attr,
			 evsel__sb_cb_t cb, व्योम *data);
व्योम evlist__set_cb(काष्ठा evlist *evlist, evsel__sb_cb_t cb, व्योम *data);
पूर्णांक evlist__start_sb_thपढ़ो(काष्ठा evlist *evlist, काष्ठा target *target);
व्योम evlist__stop_sb_thपढ़ो(काष्ठा evlist *evlist);

पूर्णांक evlist__add_newtp(काष्ठा evlist *evlist, स्थिर अक्षर *sys, स्थिर अक्षर *name, व्योम *handler);

पूर्णांक __evlist__set_tracepoपूर्णांकs_handlers(काष्ठा evlist *evlist,
				       स्थिर काष्ठा evsel_str_handler *assocs,
				       माप_प्रकार nr_assocs);

#घोषणा evlist__set_tracepoपूर्णांकs_handlers(evlist, array) \
	__evlist__set_tracepoपूर्णांकs_handlers(evlist, array, ARRAY_SIZE(array))

पूर्णांक evlist__set_tp_filter(काष्ठा evlist *evlist, स्थिर अक्षर *filter);
पूर्णांक evlist__set_tp_filter_pid(काष्ठा evlist *evlist, pid_t pid);
पूर्णांक evlist__set_tp_filter_pids(काष्ठा evlist *evlist, माप_प्रकार npids, pid_t *pids);

पूर्णांक evlist__append_tp_filter(काष्ठा evlist *evlist, स्थिर अक्षर *filter);

पूर्णांक evlist__append_tp_filter_pid(काष्ठा evlist *evlist, pid_t pid);
पूर्णांक evlist__append_tp_filter_pids(काष्ठा evlist *evlist, माप_प्रकार npids, pid_t *pids);

काष्ठा evsel *evlist__find_tracepoपूर्णांक_by_id(काष्ठा evlist *evlist, पूर्णांक id);
काष्ठा evsel *evlist__find_tracepoपूर्णांक_by_name(काष्ठा evlist *evlist, स्थिर अक्षर *name);

पूर्णांक evlist__add_pollfd(काष्ठा evlist *evlist, पूर्णांक fd);
पूर्णांक evlist__filter_pollfd(काष्ठा evlist *evlist, लघु revents_and_mask);

#अगर_घोषित HAVE_EVENTFD_SUPPORT
पूर्णांक evlist__add_wakeup_eventfd(काष्ठा evlist *evlist, पूर्णांक fd);
#पूर्ण_अगर

पूर्णांक evlist__poll(काष्ठा evlist *evlist, पूर्णांक समयout);

काष्ठा evsel *evlist__id2evsel(काष्ठा evlist *evlist, u64 id);
काष्ठा evsel *evlist__id2evsel_strict(काष्ठा evlist *evlist, u64 id);

काष्ठा perf_sample_id *evlist__id2sid(काष्ठा evlist *evlist, u64 id);

व्योम evlist__toggle_bkw_mmap(काष्ठा evlist *evlist, क्रमागत bkw_mmap_state state);

व्योम evlist__mmap_consume(काष्ठा evlist *evlist, पूर्णांक idx);

पूर्णांक evlist__खोलो(काष्ठा evlist *evlist);
व्योम evlist__बंद(काष्ठा evlist *evlist);

काष्ठा callchain_param;

व्योम evlist__set_id_pos(काष्ठा evlist *evlist);
व्योम evlist__config(काष्ठा evlist *evlist, काष्ठा record_opts *opts, काष्ठा callchain_param *callchain);
पूर्णांक record_opts__config(काष्ठा record_opts *opts);

पूर्णांक evlist__prepare_workload(काष्ठा evlist *evlist, काष्ठा target *target,
			     स्थिर अक्षर *argv[], bool pipe_output,
			     व्योम (*exec_error)(पूर्णांक signo, siginfo_t *info, व्योम *ucontext));
पूर्णांक evlist__start_workload(काष्ठा evlist *evlist);

काष्ठा option;

पूर्णांक __evlist__parse_mmap_pages(अचिन्हित पूर्णांक *mmap_pages, स्थिर अक्षर *str);
पूर्णांक evlist__parse_mmap_pages(स्थिर काष्ठा option *opt, स्थिर अक्षर *str, पूर्णांक unset);

अचिन्हित दीर्घ perf_event_mlock_kb_in_pages(व्योम);

पूर्णांक evlist__mmap_ex(काष्ठा evlist *evlist, अचिन्हित पूर्णांक pages,
			 अचिन्हित पूर्णांक auxtrace_pages,
			 bool auxtrace_overग_लिखो, पूर्णांक nr_cblocks,
			 पूर्णांक affinity, पूर्णांक flush, पूर्णांक comp_level);
पूर्णांक evlist__mmap(काष्ठा evlist *evlist, अचिन्हित पूर्णांक pages);
व्योम evlist__munmap(काष्ठा evlist *evlist);

माप_प्रकार evlist__mmap_size(अचिन्हित दीर्घ pages);

व्योम evlist__disable(काष्ठा evlist *evlist);
व्योम evlist__enable(काष्ठा evlist *evlist);
व्योम evlist__toggle_enable(काष्ठा evlist *evlist);
व्योम evlist__disable_evsel(काष्ठा evlist *evlist, अक्षर *evsel_name);
व्योम evlist__enable_evsel(काष्ठा evlist *evlist, अक्षर *evsel_name);

पूर्णांक evlist__enable_event_idx(काष्ठा evlist *evlist, काष्ठा evsel *evsel, पूर्णांक idx);

व्योम evlist__set_selected(काष्ठा evlist *evlist, काष्ठा evsel *evsel);

पूर्णांक evlist__create_maps(काष्ठा evlist *evlist, काष्ठा target *target);
पूर्णांक evlist__apply_filters(काष्ठा evlist *evlist, काष्ठा evsel **err_evsel);

व्योम __evlist__set_leader(काष्ठा list_head *list);
व्योम evlist__set_leader(काष्ठा evlist *evlist);

u64 __evlist__combined_sample_type(काष्ठा evlist *evlist);
u64 evlist__combined_sample_type(काष्ठा evlist *evlist);
u64 evlist__combined_branch_type(काष्ठा evlist *evlist);
bool evlist__sample_id_all(काष्ठा evlist *evlist);
u16 evlist__id_hdr_size(काष्ठा evlist *evlist);

पूर्णांक evlist__parse_sample(काष्ठा evlist *evlist, जोड़ perf_event *event, काष्ठा perf_sample *sample);
पूर्णांक evlist__parse_sample_बारtamp(काष्ठा evlist *evlist, जोड़ perf_event *event, u64 *बारtamp);

bool evlist__valid_sample_type(काष्ठा evlist *evlist);
bool evlist__valid_sample_id_all(काष्ठा evlist *evlist);
bool evlist__valid_पढ़ो_क्रमmat(काष्ठा evlist *evlist);

व्योम evlist__splice_list_tail(काष्ठा evlist *evlist, काष्ठा list_head *list);

अटल अंतरभूत bool evlist__empty(काष्ठा evlist *evlist)
अणु
	वापस list_empty(&evlist->core.entries);
पूर्ण

अटल अंतरभूत काष्ठा evsel *evlist__first(काष्ठा evlist *evlist)
अणु
	काष्ठा perf_evsel *evsel = perf_evlist__first(&evlist->core);

	वापस container_of(evsel, काष्ठा evsel, core);
पूर्ण

अटल अंतरभूत काष्ठा evsel *evlist__last(काष्ठा evlist *evlist)
अणु
	काष्ठा perf_evsel *evsel = perf_evlist__last(&evlist->core);

	वापस container_of(evsel, काष्ठा evsel, core);
पूर्ण

पूर्णांक evlist__म_त्रुटि_खोलो(काष्ठा evlist *evlist, पूर्णांक err, अक्षर *buf, माप_प्रकार size);
पूर्णांक evlist__म_त्रुटि_mmap(काष्ठा evlist *evlist, पूर्णांक err, अक्षर *buf, माप_प्रकार size);

bool evlist__can_select_event(काष्ठा evlist *evlist, स्थिर अक्षर *str);
व्योम evlist__to_front(काष्ठा evlist *evlist, काष्ठा evsel *move_evsel);

/**
 * __evlist__क्रम_each_entry - iterate thru all the evsels
 * @list: list_head instance to iterate
 * @evsel: काष्ठा evsel iterator
 */
#घोषणा __evlist__क्रम_each_entry(list, evsel) \
        list_क्रम_each_entry(evsel, list, core.node)

/**
 * evlist__क्रम_each_entry - iterate thru all the evsels
 * @evlist: evlist instance to iterate
 * @evsel: काष्ठा evsel iterator
 */
#घोषणा evlist__क्रम_each_entry(evlist, evsel) \
	__evlist__क्रम_each_entry(&(evlist)->core.entries, evsel)

/**
 * __evlist__क्रम_each_entry_जारी - जारी iteration thru all the evsels
 * @list: list_head instance to iterate
 * @evsel: काष्ठा evsel iterator
 */
#घोषणा __evlist__क्रम_each_entry_जारी(list, evsel) \
        list_क्रम_each_entry_जारी(evsel, list, core.node)

/**
 * evlist__क्रम_each_entry_जारी - जारी iteration thru all the evsels
 * @evlist: evlist instance to iterate
 * @evsel: काष्ठा evsel iterator
 */
#घोषणा evlist__क्रम_each_entry_जारी(evlist, evsel) \
	__evlist__क्रम_each_entry_जारी(&(evlist)->core.entries, evsel)

/**
 * __evlist__क्रम_each_entry_reverse - iterate thru all the evsels in reverse order
 * @list: list_head instance to iterate
 * @evsel: काष्ठा evsel iterator
 */
#घोषणा __evlist__क्रम_each_entry_reverse(list, evsel) \
        list_क्रम_each_entry_reverse(evsel, list, core.node)

/**
 * evlist__क्रम_each_entry_reverse - iterate thru all the evsels in reverse order
 * @evlist: evlist instance to iterate
 * @evsel: काष्ठा evsel iterator
 */
#घोषणा evlist__क्रम_each_entry_reverse(evlist, evsel) \
	__evlist__क्रम_each_entry_reverse(&(evlist)->core.entries, evsel)

/**
 * __evlist__क्रम_each_entry_safe - safely iterate thru all the evsels
 * @list: list_head instance to iterate
 * @पंचांगp: काष्ठा evsel temp iterator
 * @evsel: काष्ठा evsel iterator
 */
#घोषणा __evlist__क्रम_each_entry_safe(list, पंचांगp, evsel) \
        list_क्रम_each_entry_safe(evsel, पंचांगp, list, core.node)

/**
 * evlist__क्रम_each_entry_safe - safely iterate thru all the evsels
 * @evlist: evlist instance to iterate
 * @evsel: काष्ठा evsel iterator
 * @पंचांगp: काष्ठा evsel temp iterator
 */
#घोषणा evlist__क्रम_each_entry_safe(evlist, पंचांगp, evsel) \
	__evlist__क्रम_each_entry_safe(&(evlist)->core.entries, पंचांगp, evsel)

#घोषणा evlist__क्रम_each_cpu(evlist, index, cpu)	\
	evlist__cpu_iter_start(evlist);			\
	perf_cpu_map__क्रम_each_cpu (cpu, index, (evlist)->core.all_cpus)

काष्ठा evsel *evlist__get_tracking_event(काष्ठा evlist *evlist);
व्योम evlist__set_tracking_event(काष्ठा evlist *evlist, काष्ठा evsel *tracking_evsel);

व्योम evlist__cpu_iter_start(काष्ठा evlist *evlist);
bool evsel__cpu_iter_skip(काष्ठा evsel *ev, पूर्णांक cpu);
bool evsel__cpu_iter_skip_no_inc(काष्ठा evsel *ev, पूर्णांक cpu);

काष्ठा evsel *evlist__find_evsel_by_str(काष्ठा evlist *evlist, स्थिर अक्षर *str);

काष्ठा evsel *evlist__event2evsel(काष्ठा evlist *evlist, जोड़ perf_event *event);

bool evlist__exclude_kernel(काष्ठा evlist *evlist);

व्योम evlist__क्रमce_leader(काष्ठा evlist *evlist);

काष्ठा evsel *evlist__reset_weak_group(काष्ठा evlist *evlist, काष्ठा evsel *evsel, bool बंद);

#घोषणा EVLIST_CTL_CMD_ENABLE_TAG  "enable"
#घोषणा EVLIST_CTL_CMD_DISABLE_TAG "disable"
#घोषणा EVLIST_CTL_CMD_ACK_TAG     "ack\n"
#घोषणा EVLIST_CTL_CMD_SNAPSHOT_TAG "snapshot"
#घोषणा EVLIST_CTL_CMD_EVLIST_TAG "evlist"
#घोषणा EVLIST_CTL_CMD_STOP_TAG "stop"
#घोषणा EVLIST_CTL_CMD_PING_TAG "ping"

#घोषणा EVLIST_CTL_CMD_MAX_LEN 64

क्रमागत evlist_ctl_cmd अणु
	EVLIST_CTL_CMD_UNSUPPORTED = 0,
	EVLIST_CTL_CMD_ENABLE,
	EVLIST_CTL_CMD_DISABLE,
	EVLIST_CTL_CMD_ACK,
	EVLIST_CTL_CMD_SNAPSHOT,
	EVLIST_CTL_CMD_EVLIST,
	EVLIST_CTL_CMD_STOP,
	EVLIST_CTL_CMD_PING,
पूर्ण;

पूर्णांक evlist__parse_control(स्थिर अक्षर *str, पूर्णांक *ctl_fd, पूर्णांक *ctl_fd_ack, bool *ctl_fd_बंद);
व्योम evlist__बंद_control(पूर्णांक ctl_fd, पूर्णांक ctl_fd_ack, bool *ctl_fd_बंद);
पूर्णांक evlist__initialize_ctlfd(काष्ठा evlist *evlist, पूर्णांक ctl_fd, पूर्णांक ctl_fd_ack);
पूर्णांक evlist__finalize_ctlfd(काष्ठा evlist *evlist);
bool evlist__ctlfd_initialized(काष्ठा evlist *evlist);
पूर्णांक evlist__ctlfd_process(काष्ठा evlist *evlist, क्रमागत evlist_ctl_cmd *cmd);
पूर्णांक evlist__ctlfd_ack(काष्ठा evlist *evlist);

#घोषणा EVLIST_ENABLED_MSG "Events enabled\n"
#घोषणा EVLIST_DISABLED_MSG "Events disabled\n"

काष्ठा evsel *evlist__find_evsel(काष्ठा evlist *evlist, पूर्णांक idx);

पूर्णांक evlist__scnम_लिखो_evsels(काष्ठा evlist *evlist, माप_प्रकार size, अक्षर *bf);
#पूर्ण_अगर /* __PERF_EVLIST_H */
