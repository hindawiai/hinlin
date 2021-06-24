<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LIBPERF_EVSEL_H
#घोषणा __LIBPERF_EVSEL_H

#समावेश <मानक_निवेशt.h>
#समावेश <perf/core.h>

काष्ठा perf_evsel;
काष्ठा perf_event_attr;
काष्ठा perf_cpu_map;
काष्ठा perf_thपढ़ो_map;

काष्ठा perf_counts_values अणु
	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक64_t val;
			uपूर्णांक64_t ena;
			uपूर्णांक64_t run;
		पूर्ण;
		uपूर्णांक64_t values[3];
	पूर्ण;
पूर्ण;

LIBPERF_API काष्ठा perf_evsel *perf_evsel__new(काष्ठा perf_event_attr *attr);
LIBPERF_API व्योम perf_evsel__delete(काष्ठा perf_evsel *evsel);
LIBPERF_API पूर्णांक perf_evsel__खोलो(काष्ठा perf_evsel *evsel, काष्ठा perf_cpu_map *cpus,
				 काष्ठा perf_thपढ़ो_map *thपढ़ोs);
LIBPERF_API व्योम perf_evsel__बंद(काष्ठा perf_evsel *evsel);
LIBPERF_API व्योम perf_evsel__बंद_cpu(काष्ठा perf_evsel *evsel, पूर्णांक cpu);
LIBPERF_API पूर्णांक perf_evsel__mmap(काष्ठा perf_evsel *evsel, पूर्णांक pages);
LIBPERF_API व्योम perf_evsel__munmap(काष्ठा perf_evsel *evsel);
LIBPERF_API व्योम *perf_evsel__mmap_base(काष्ठा perf_evsel *evsel, पूर्णांक cpu, पूर्णांक thपढ़ो);
LIBPERF_API पूर्णांक perf_evsel__पढ़ो(काष्ठा perf_evsel *evsel, पूर्णांक cpu, पूर्णांक thपढ़ो,
				 काष्ठा perf_counts_values *count);
LIBPERF_API पूर्णांक perf_evsel__enable(काष्ठा perf_evsel *evsel);
LIBPERF_API पूर्णांक perf_evsel__enable_cpu(काष्ठा perf_evsel *evsel, पूर्णांक cpu);
LIBPERF_API पूर्णांक perf_evsel__disable(काष्ठा perf_evsel *evsel);
LIBPERF_API पूर्णांक perf_evsel__disable_cpu(काष्ठा perf_evsel *evsel, पूर्णांक cpu);
LIBPERF_API काष्ठा perf_cpu_map *perf_evsel__cpus(काष्ठा perf_evsel *evsel);
LIBPERF_API काष्ठा perf_thपढ़ो_map *perf_evsel__thपढ़ोs(काष्ठा perf_evsel *evsel);
LIBPERF_API काष्ठा perf_event_attr *perf_evsel__attr(काष्ठा perf_evsel *evsel);

#पूर्ण_अगर /* __LIBPERF_EVSEL_H */
