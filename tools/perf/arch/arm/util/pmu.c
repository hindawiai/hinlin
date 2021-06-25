<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright(C) 2015 Linaro Limited. All rights reserved.
 * Author: Mathieu Poirier <mathieu.poirier@linaro.org>
 */

#समावेश <माला.स>
#समावेश <linux/coresight-pmu.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/माला.स>

#समावेश "arm-spe.h"
#समावेश "../../util/pmu.h"

काष्ठा perf_event_attr
*perf_pmu__get_शेष_config(काष्ठा perf_pmu *pmu __maybe_unused)
अणु
#अगर_घोषित HAVE_AUXTRACE_SUPPORT
	अगर (!म_भेद(pmu->name, CORESIGHT_ETM_PMU_NAME)) अणु
		/* add ETM शेष config here */
		pmu->selectable = true;
#अगर defined(__aarch64__)
	पूर्ण अन्यथा अगर (strstarts(pmu->name, ARM_SPE_PMU_NAME)) अणु
		वापस arm_spe_pmu_शेष_config(pmu);
#पूर्ण_अगर
	पूर्ण

#पूर्ण_अगर
	वापस शून्य;
पूर्ण
