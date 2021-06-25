<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LIBPERF_INTERNAL_CPUMAP_H
#घोषणा __LIBPERF_INTERNAL_CPUMAP_H

#समावेश <linux/refcount.h>

काष्ठा perf_cpu_map अणु
	refcount_t	refcnt;
	पूर्णांक		nr;
	पूर्णांक		map[];
पूर्ण;

#अगर_अघोषित MAX_NR_CPUS
#घोषणा MAX_NR_CPUS	2048
#पूर्ण_अगर

पूर्णांक perf_cpu_map__idx(काष्ठा perf_cpu_map *cpus, पूर्णांक cpu);

#पूर्ण_अगर /* __LIBPERF_INTERNAL_CPUMAP_H */
