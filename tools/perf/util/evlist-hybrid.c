<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश "cpumap.h"
#समावेश "evlist.h"
#समावेश "evsel.h"
#समावेश "../perf.h"
#समावेश "util/pmu-hybrid.h"
#समावेश "util/evlist-hybrid.h"
#समावेश "debug.h"
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <linux/err.h>
#समावेश <linux/माला.स>
#समावेश <perf/evlist.h>
#समावेश <perf/evsel.h>
#समावेश <perf/cpumap.h>

पूर्णांक evlist__add_शेष_hybrid(काष्ठा evlist *evlist, bool precise)
अणु
	काष्ठा evsel *evsel;
	काष्ठा perf_pmu *pmu;
	__u64 config;
	काष्ठा perf_cpu_map *cpus;

	perf_pmu__क्रम_each_hybrid_pmu(pmu) अणु
		config = PERF_COUNT_HW_CPU_CYCLES |
			 ((__u64)pmu->type << PERF_PMU_TYPE_SHIFT);
		evsel = evsel__new_cycles(precise, PERF_TYPE_HARDWARE,
					  config);
		अगर (!evsel)
			वापस -ENOMEM;

		cpus = perf_cpu_map__get(pmu->cpus);
		evsel->core.cpus = cpus;
		evsel->core.own_cpus = perf_cpu_map__get(cpus);
		evsel->pmu_name = strdup(pmu->name);
		evlist__add(evlist, evsel);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool group_hybrid_conflict(काष्ठा evsel *leader)
अणु
	काष्ठा evsel *pos, *prev = शून्य;

	क्रम_each_group_evsel(pos, leader) अणु
		अगर (!evsel__is_hybrid(pos))
			जारी;

		अगर (prev && म_भेद(prev->pmu_name, pos->pmu_name))
			वापस true;

		prev = pos;
	पूर्ण

	वापस false;
पूर्ण

व्योम evlist__warn_hybrid_group(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel__is_group_leader(evsel) &&
		    evsel->core.nr_members > 1 &&
		    group_hybrid_conflict(evsel)) अणु
			pr_warning("WARNING: events in group from "
				   "different hybrid PMUs!\n");
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

bool evlist__has_hybrid(काष्ठा evlist *evlist)
अणु
	काष्ठा evsel *evsel;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (evsel->pmu_name &&
		    perf_pmu__is_hybrid(evsel->pmu_name)) अणु
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण
