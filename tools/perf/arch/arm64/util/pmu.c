<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश "../../../util/cpumap.h"
#समावेश "../../../util/pmu.h"

काष्ठा pmu_events_map *pmu_events_map__find(व्योम)
अणु
	काष्ठा perf_pmu *pmu = शून्य;

	जबतक ((pmu = perf_pmu__scan(pmu))) अणु
		अगर (!is_pmu_core(pmu->name))
			जारी;

		/*
		 * The cpumap should cover all CPUs. Otherwise, some CPUs may
		 * not support some events or have dअगरferent event IDs.
		 */
		अगर (pmu->cpus->nr != cpu__max_cpu())
			वापस शून्य;

		वापस perf_pmu__find_map(pmu);
	पूर्ण

	वापस शून्य;
पूर्ण
