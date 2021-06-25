<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LIBPERF_EVLIST_H
#घोषणा __LIBPERF_EVLIST_H

#समावेश <perf/core.h>
#समावेश <stdbool.h>

काष्ठा perf_evlist;
काष्ठा perf_evsel;
काष्ठा perf_cpu_map;
काष्ठा perf_thपढ़ो_map;

LIBPERF_API व्योम perf_evlist__add(काष्ठा perf_evlist *evlist,
				  काष्ठा perf_evsel *evsel);
LIBPERF_API व्योम perf_evlist__हटाओ(काष्ठा perf_evlist *evlist,
				     काष्ठा perf_evsel *evsel);
LIBPERF_API काष्ठा perf_evlist *perf_evlist__new(व्योम);
LIBPERF_API व्योम perf_evlist__delete(काष्ठा perf_evlist *evlist);
LIBPERF_API काष्ठा perf_evsel* perf_evlist__next(काष्ठा perf_evlist *evlist,
						 काष्ठा perf_evsel *evsel);
LIBPERF_API पूर्णांक perf_evlist__खोलो(काष्ठा perf_evlist *evlist);
LIBPERF_API व्योम perf_evlist__बंद(काष्ठा perf_evlist *evlist);
LIBPERF_API व्योम perf_evlist__enable(काष्ठा perf_evlist *evlist);
LIBPERF_API व्योम perf_evlist__disable(काष्ठा perf_evlist *evlist);

#घोषणा perf_evlist__क्रम_each_evsel(evlist, pos)	\
	क्रम ((pos) = perf_evlist__next((evlist), शून्य);	\
	     (pos) != शून्य;				\
	     (pos) = perf_evlist__next((evlist), (pos)))

LIBPERF_API व्योम perf_evlist__set_maps(काष्ठा perf_evlist *evlist,
				       काष्ठा perf_cpu_map *cpus,
				       काष्ठा perf_thपढ़ो_map *thपढ़ोs);
LIBPERF_API पूर्णांक perf_evlist__poll(काष्ठा perf_evlist *evlist, पूर्णांक समयout);
LIBPERF_API पूर्णांक perf_evlist__filter_pollfd(काष्ठा perf_evlist *evlist,
					   लघु revents_and_mask);

LIBPERF_API पूर्णांक perf_evlist__mmap(काष्ठा perf_evlist *evlist, पूर्णांक pages);
LIBPERF_API व्योम perf_evlist__munmap(काष्ठा perf_evlist *evlist);

LIBPERF_API काष्ठा perf_mmap *perf_evlist__next_mmap(काष्ठा perf_evlist *evlist,
						     काष्ठा perf_mmap *map,
						     bool overग_लिखो);
#घोषणा perf_evlist__क्रम_each_mmap(evlist, pos, overग_लिखो)		\
	क्रम ((pos) = perf_evlist__next_mmap((evlist), शून्य, overग_लिखो);	\
	     (pos) != शून्य;						\
	     (pos) = perf_evlist__next_mmap((evlist), (pos), overग_लिखो))

#पूर्ण_अगर /* __LIBPERF_EVLIST_H */
