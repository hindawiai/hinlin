<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(C) 2015 Linaro Limited. All rights reserved.
 * Author: Mathieu Poirier <mathieu.poirier@linaro.org>
 */

#समावेश <stdbool.h>
#समावेश <linux/coresight-pmu.h>
#समावेश <linux/zभाग.स>

#समावेश "../../util/auxtrace.h"
#समावेश "../../util/debug.h"
#समावेश "../../util/evlist.h"
#समावेश "../../util/pmu.h"
#समावेश "cs-etm.h"
#समावेश "arm-spe.h"

अटल काष्ठा perf_pmu **find_all_arm_spe_pmus(पूर्णांक *nr_spes, पूर्णांक *err)
अणु
	काष्ठा perf_pmu **arm_spe_pmus = शून्य;
	पूर्णांक ret, i, nr_cpus = sysconf(_SC_NPROCESSORS_CONF);
	/* arm_spe_xxxxxxxxx\0 */
	अक्षर arm_spe_pmu_name[माप(ARM_SPE_PMU_NAME) + 10];

	arm_spe_pmus = zalloc(माप(काष्ठा perf_pmu *) * nr_cpus);
	अगर (!arm_spe_pmus) अणु
		pr_err("spes alloc failed\n");
		*err = -ENOMEM;
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < nr_cpus; i++) अणु
		ret = प्र_लिखो(arm_spe_pmu_name, "%s%d", ARM_SPE_PMU_NAME, i);
		अगर (ret < 0) अणु
			pr_err("sprintf failed\n");
			*err = -ENOMEM;
			वापस शून्य;
		पूर्ण

		arm_spe_pmus[*nr_spes] = perf_pmu__find(arm_spe_pmu_name);
		अगर (arm_spe_pmus[*nr_spes]) अणु
			pr_debug2("%s %d: arm_spe_pmu %d type %d name %s\n",
				 __func__, __LINE__, *nr_spes,
				 arm_spe_pmus[*nr_spes]->type,
				 arm_spe_pmus[*nr_spes]->name);
			(*nr_spes)++;
		पूर्ण
	पूर्ण

	वापस arm_spe_pmus;
पूर्ण

काष्ठा auxtrace_record
*auxtrace_record__init(काष्ठा evlist *evlist, पूर्णांक *err)
अणु
	काष्ठा perf_pmu	*cs_eपंचांग_pmu;
	काष्ठा evsel *evsel;
	bool found_eपंचांग = false;
	काष्ठा perf_pmu *found_spe = शून्य;
	काष्ठा perf_pmu **arm_spe_pmus = शून्य;
	पूर्णांक nr_spes = 0;
	पूर्णांक i = 0;

	अगर (!evlist)
		वापस शून्य;

	cs_eपंचांग_pmu = perf_pmu__find(CORESIGHT_ETM_PMU_NAME);
	arm_spe_pmus = find_all_arm_spe_pmus(&nr_spes, err);

	evlist__क्रम_each_entry(evlist, evsel) अणु
		अगर (cs_eपंचांग_pmu &&
		    evsel->core.attr.type == cs_eपंचांग_pmu->type)
			found_eपंचांग = true;

		अगर (!nr_spes || found_spe)
			जारी;

		क्रम (i = 0; i < nr_spes; i++) अणु
			अगर (evsel->core.attr.type == arm_spe_pmus[i]->type) अणु
				found_spe = arm_spe_pmus[i];
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	मुक्त(arm_spe_pmus);

	अगर (found_eपंचांग && found_spe) अणु
		pr_err("Concurrent ARM Coresight ETM and SPE operation not currently supported\n");
		*err = -EOPNOTSUPP;
		वापस शून्य;
	पूर्ण

	अगर (found_eपंचांग)
		वापस cs_eपंचांग_record_init(err);

#अगर defined(__aarch64__)
	अगर (found_spe)
		वापस arm_spe_recording_init(err, found_spe);
#पूर्ण_अगर

	/*
	 * Clear 'err' even if we haven't found an event - that way perf
	 * record can still be used even अगर tracers aren't present.  The शून्य
	 * वापस value will take care of telling the infraकाष्ठाure HW tracing
	 * isn't available.
	 */
	*err = 0;
	वापस शून्य;
पूर्ण
