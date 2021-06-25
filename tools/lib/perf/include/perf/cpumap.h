<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LIBPERF_CPUMAP_H
#घोषणा __LIBPERF_CPUMAP_H

#समावेश <perf/core.h>
#समावेश <मानकपन.स>
#समावेश <stdbool.h>

काष्ठा perf_cpu_map;

LIBPERF_API काष्ठा perf_cpu_map *perf_cpu_map__dummy_new(व्योम);
LIBPERF_API काष्ठा perf_cpu_map *perf_cpu_map__new(स्थिर अक्षर *cpu_list);
LIBPERF_API काष्ठा perf_cpu_map *perf_cpu_map__पढ़ो(खाता *file);
LIBPERF_API काष्ठा perf_cpu_map *perf_cpu_map__get(काष्ठा perf_cpu_map *map);
LIBPERF_API काष्ठा perf_cpu_map *perf_cpu_map__merge(काष्ठा perf_cpu_map *orig,
						     काष्ठा perf_cpu_map *other);
LIBPERF_API व्योम perf_cpu_map__put(काष्ठा perf_cpu_map *map);
LIBPERF_API पूर्णांक perf_cpu_map__cpu(स्थिर काष्ठा perf_cpu_map *cpus, पूर्णांक idx);
LIBPERF_API पूर्णांक perf_cpu_map__nr(स्थिर काष्ठा perf_cpu_map *cpus);
LIBPERF_API bool perf_cpu_map__empty(स्थिर काष्ठा perf_cpu_map *map);
LIBPERF_API पूर्णांक perf_cpu_map__max(काष्ठा perf_cpu_map *map);

#घोषणा perf_cpu_map__क्रम_each_cpu(cpu, idx, cpus)		\
	क्रम ((idx) = 0, (cpu) = perf_cpu_map__cpu(cpus, idx);	\
	     (idx) < perf_cpu_map__nr(cpus);			\
	     (idx)++, (cpu) = perf_cpu_map__cpu(cpus, idx))

#पूर्ण_अगर /* __LIBPERF_CPUMAP_H */
