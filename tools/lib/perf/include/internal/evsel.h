<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LIBPERF_INTERNAL_EVSEL_H
#घोषणा __LIBPERF_INTERNAL_EVSEL_H

#समावेश <linux/types.h>
#समावेश <linux/perf_event.h>
#समावेश <stdbool.h>
#समावेश <sys/types.h>

काष्ठा perf_cpu_map;
काष्ठा perf_thपढ़ो_map;
काष्ठा xyarray;

/*
 * Per fd, to map back from PERF_SAMPLE_ID to evsel, only used when there are
 * more than one entry in the evlist.
 */
काष्ठा perf_sample_id अणु
	काष्ठा hlist_node	 node;
	u64			 id;
	काष्ठा perf_evsel	*evsel;
       /*
	* 'idx' will be used क्रम AUX area sampling. A sample will have AUX area
	* data that will be queued क्रम decoding, where there are separate
	* queues क्रम each CPU (per-cpu tracing) or task (per-thपढ़ो tracing).
	* The sample ID can be used to lookup 'idx' which is effectively the
	* queue number.
	*/
	पूर्णांक			 idx;
	पूर्णांक			 cpu;
	pid_t			 tid;

	/* Holds total ID period value क्रम PERF_SAMPLE_READ processing. */
	u64			 period;
पूर्ण;

काष्ठा perf_evsel अणु
	काष्ठा list_head	 node;
	काष्ठा perf_event_attr	 attr;
	काष्ठा perf_cpu_map	*cpus;
	काष्ठा perf_cpu_map	*own_cpus;
	काष्ठा perf_thपढ़ो_map	*thपढ़ोs;
	काष्ठा xyarray		*fd;
	काष्ठा xyarray		*mmap;
	काष्ठा xyarray		*sample_id;
	u64			*id;
	u32			 ids;

	/* parse modअगरier helper */
	पूर्णांक			 nr_members;
	bool			 प्रणाली_wide;
पूर्ण;

व्योम perf_evsel__init(काष्ठा perf_evsel *evsel, काष्ठा perf_event_attr *attr);
पूर्णांक perf_evsel__alloc_fd(काष्ठा perf_evsel *evsel, पूर्णांक ncpus, पूर्णांक nthपढ़ोs);
व्योम perf_evsel__बंद_fd(काष्ठा perf_evsel *evsel);
व्योम perf_evsel__मुक्त_fd(काष्ठा perf_evsel *evsel);
पूर्णांक perf_evsel__पढ़ो_size(काष्ठा perf_evsel *evsel);
पूर्णांक perf_evsel__apply_filter(काष्ठा perf_evsel *evsel, स्थिर अक्षर *filter);

पूर्णांक perf_evsel__alloc_id(काष्ठा perf_evsel *evsel, पूर्णांक ncpus, पूर्णांक nthपढ़ोs);
व्योम perf_evsel__मुक्त_id(काष्ठा perf_evsel *evsel);

#पूर्ण_अगर /* __LIBPERF_INTERNAL_EVSEL_H */
