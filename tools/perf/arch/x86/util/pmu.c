<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <माला.स>

#समावेश <linux/मानकघोष.स>
#समावेश <linux/perf_event.h>

#समावेश "../../../util/intel-pt.h"
#समावेश "../../../util/intel-bts.h"
#समावेश "../../../util/pmu.h"

काष्ठा perf_event_attr *perf_pmu__get_शेष_config(काष्ठा perf_pmu *pmu __maybe_unused)
अणु
#अगर_घोषित HAVE_AUXTRACE_SUPPORT
	अगर (!म_भेद(pmu->name, INTEL_PT_PMU_NAME))
		वापस पूर्णांकel_pt_pmu_शेष_config(pmu);
	अगर (!म_भेद(pmu->name, INTEL_BTS_PMU_NAME))
		pmu->selectable = true;
#पूर्ण_अगर
	वापस शून्य;
पूर्ण
