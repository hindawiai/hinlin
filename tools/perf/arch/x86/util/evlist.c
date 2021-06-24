<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <मानकपन.स>
#समावेश "util/pmu.h"
#समावेश "util/evlist.h"
#समावेश "util/parse-events.h"

#घोषणा TOPDOWN_L1_EVENTS	"{slots,topdown-retiring,topdown-bad-spec,topdown-fe-bound,topdown-be-bound}"

पूर्णांक arch_evlist__add_शेष_attrs(काष्ठा evlist *evlist)
अणु
	अगर (!pmu_have_event("cpu", "slots"))
		वापस 0;

	वापस parse_events(evlist, TOPDOWN_L1_EVENTS, शून्य);
पूर्ण
