<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LIBPERF_THREADMAP_H
#घोषणा __LIBPERF_THREADMAP_H

#समावेश <perf/core.h>
#समावेश <sys/types.h>

काष्ठा perf_thपढ़ो_map;

LIBPERF_API काष्ठा perf_thपढ़ो_map *perf_thपढ़ो_map__new_dummy(व्योम);

LIBPERF_API व्योम perf_thपढ़ो_map__set_pid(काष्ठा perf_thपढ़ो_map *map, पूर्णांक thपढ़ो, pid_t pid);
LIBPERF_API अक्षर *perf_thपढ़ो_map__comm(काष्ठा perf_thपढ़ो_map *map, पूर्णांक thपढ़ो);
LIBPERF_API पूर्णांक perf_thपढ़ो_map__nr(काष्ठा perf_thपढ़ो_map *thपढ़ोs);
LIBPERF_API pid_t perf_thपढ़ो_map__pid(काष्ठा perf_thपढ़ो_map *map, पूर्णांक thपढ़ो);

LIBPERF_API काष्ठा perf_thपढ़ो_map *perf_thपढ़ो_map__get(काष्ठा perf_thपढ़ो_map *map);
LIBPERF_API व्योम perf_thपढ़ो_map__put(काष्ठा perf_thपढ़ो_map *map);

#पूर्ण_अगर /* __LIBPERF_THREADMAP_H */
