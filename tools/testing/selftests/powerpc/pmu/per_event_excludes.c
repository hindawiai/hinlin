<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014, Michael Ellerman, IBM Corp.
 */

#घोषणा _GNU_SOURCE

#समावेश <elf.h>
#समावेश <सीमा.स>
#समावेश <मानकपन.स>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <sys/prctl.h>

#समावेश "event.h"
#समावेश "lib.h"
#समावेश "utils.h"

/*
 * Test that per-event excludes work.
 */

अटल पूर्णांक per_event_excludes(व्योम)
अणु
	काष्ठा event *e, events[4];
	पूर्णांक i;

	SKIP_IF(!have_hwcap2(PPC_FEATURE2_ARCH_2_07));

	/*
	 * We need to create the events disabled, otherwise the running/enabled
	 * counts करोn't match up.
	 */
	e = &events[0];
	event_init_opts(e, PERF_COUNT_HW_INSTRUCTIONS,
			PERF_TYPE_HARDWARE, "instructions");
	e->attr.disabled = 1;

	e = &events[1];
	event_init_opts(e, PERF_COUNT_HW_INSTRUCTIONS,
			PERF_TYPE_HARDWARE, "instructions(k)");
	e->attr.disabled = 1;
	e->attr.exclude_user = 1;
	e->attr.exclude_hv = 1;

	e = &events[2];
	event_init_opts(e, PERF_COUNT_HW_INSTRUCTIONS,
			PERF_TYPE_HARDWARE, "instructions(h)");
	e->attr.disabled = 1;
	e->attr.exclude_user = 1;
	e->attr.exclude_kernel = 1;

	e = &events[3];
	event_init_opts(e, PERF_COUNT_HW_INSTRUCTIONS,
			PERF_TYPE_HARDWARE, "instructions(u)");
	e->attr.disabled = 1;
	e->attr.exclude_hv = 1;
	e->attr.exclude_kernel = 1;

	FAIL_IF(event_खोलो(&events[0]));

	/*
	 * The खोलो here will fail अगर we करोn't have per event exclude support,
	 * because the second event has an incompatible set of exclude settings
	 * and we're asking क्रम the events to be in a group.
	 */
	क्रम (i = 1; i < 4; i++)
		FAIL_IF(event_खोलो_with_group(&events[i], events[0].fd));

	/*
	 * Even though the above will fail without per-event excludes we keep
	 * testing in order to be thorough.
	 */
	prctl(PR_TASK_PERF_EVENTS_ENABLE);

	/* Spin क्रम a जबतक */
	क्रम (i = 0; i < पूर्णांक_उच्च; i++)
		यंत्र अस्थिर("" : : : "memory");

	prctl(PR_TASK_PERF_EVENTS_DISABLE);

	क्रम (i = 0; i < 4; i++) अणु
		FAIL_IF(event_पढ़ो(&events[i]));
		event_report(&events[i]);
	पूर्ण

	/*
	 * We should see that all events have enabled == running. That
	 * shows that they were all on the PMU at once.
	 */
	क्रम (i = 0; i < 4; i++)
		FAIL_IF(events[i].result.running != events[i].result.enabled);

	/*
	 * We can also check that the result क्रम inकाष्ठाions is >= all the
	 * other counts. That's because it is counting all inकाष्ठाions जबतक
	 * the others are counting a subset.
	 */
	क्रम (i = 1; i < 4; i++)
		FAIL_IF(events[0].result.value < events[i].result.value);

	क्रम (i = 0; i < 4; i++)
		event_बंद(&events[i]);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(per_event_excludes, "per_event_excludes");
पूर्ण
