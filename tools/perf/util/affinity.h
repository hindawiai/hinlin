<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#अगर_अघोषित PERF_AFFINITY_H
#घोषणा PERF_AFFINITY_H 1

#समावेश <stdbool.h>

काष्ठा affinity अणु
	अचिन्हित दीर्घ *orig_cpus;
	अचिन्हित दीर्घ *sched_cpus;
	bool changed;
पूर्ण;

व्योम affinity__cleanup(काष्ठा affinity *a);
व्योम affinity__set(काष्ठा affinity *a, पूर्णांक cpu);
पूर्णांक affinity__setup(काष्ठा affinity *a);

#पूर्ण_अगर // PERF_AFFINITY_H
