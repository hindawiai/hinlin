<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * auxtrace.c: AUX area tracing support
 * Copyright (c) 2013-2014, Intel Corporation.
 */

#समावेश <त्रुटिसं.स>
#समावेश <stdbool.h>

#समावेश "../../../util/header.h"
#समावेश "../../../util/debug.h"
#समावेश "../../../util/pmu.h"
#समावेश "../../../util/auxtrace.h"
#समावेश "../../../util/intel-pt.h"
#समावेश "../../../util/intel-bts.h"
#समावेश "../../../util/evlist.h"

अटल
काष्ठा auxtrace_record *auxtrace_record__init_पूर्णांकel(काष्ठा evlist *evlist,
						    पूर्णांक *err)
अणु
	काष्ठा perf_pmu *पूर्णांकel_pt_pmu;
	काष्ठा perf_pmu *पूर्णांकel_bts_pmu;
	काष्ठा evsel *evsel;
	bool found_pt = false;
	bool found_bts = false;

	पूर्णांकel_pt_pmu = perf_pmu__find(INTEL_PT_PMU_NAME);
	अगर (पूर्णांकel_pt_pmu)
		पूर्णांकel_pt_pmu->auxtrace = true;
	पूर्णांकel_bts_pmu = perf_pmu__find(INTEL_BTS_PMU_NAME);
	अगर (पूर्णांकel_bts_pmu)
		पूर्णांकel_bts_pmu->auxtrace = true;

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (पूर्णांकel_pt_pmu && evsel->core.attr.type == पूर्णांकel_pt_pmu->type)
			found_pt = true;
		अगर (पूर्णांकel_bts_pmu && evsel->core.attr.type == पूर्णांकel_bts_pmu->type)
			found_bts = true;
	पूर्ण

	अगर (found_pt && found_bts) अणु
		pr_err("intel_pt and intel_bts may not be used together\n");
		*err = -EINVAL;
		वापस शून्य;
	पूर्ण

	अगर (found_pt)
		वापस पूर्णांकel_pt_recording_init(err);

	अगर (found_bts)
		वापस पूर्णांकel_bts_recording_init(err);

	वापस शून्य;
पूर्ण

काष्ठा auxtrace_record *auxtrace_record__init(काष्ठा evlist *evlist,
					      पूर्णांक *err)
अणु
	अक्षर buffer[64];
	पूर्णांक ret;

	*err = 0;

	ret = get_cpuid(buffer, माप(buffer));
	अगर (ret) अणु
		*err = ret;
		वापस शून्य;
	पूर्ण

	अगर (!म_भेदन(buffer, "GenuineIntel,", 13))
		वापस auxtrace_record__init_पूर्णांकel(evlist, err);

	वापस शून्य;
पूर्ण
