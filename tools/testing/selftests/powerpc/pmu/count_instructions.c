<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2013, Michael Ellerman, IBM Corp.
 */

#घोषणा _GNU_SOURCE

#समावेश <मानकपन.स>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <sys/prctl.h>

#समावेश "event.h"
#समावेश "utils.h"
#समावेश "lib.h"

बाह्य व्योम thirty_two_inकाष्ठाion_loop(u64 loops);

अटल व्योम setup_event(काष्ठा event *e, u64 config, अक्षर *name)
अणु
	event_init_opts(e, config, PERF_TYPE_HARDWARE, name);

	e->attr.disabled = 1;
	e->attr.exclude_kernel = 1;
	e->attr.exclude_hv = 1;
	e->attr.exclude_idle = 1;
पूर्ण

अटल पूर्णांक करो_count_loop(काष्ठा event *events, u64 inकाष्ठाions,
			 u64 overhead, bool report)
अणु
	s64 dअगरference, expected;
	द्विगुन percentage;

	prctl(PR_TASK_PERF_EVENTS_ENABLE);

	/* Run क्रम 1M inकाष्ठाions */
	thirty_two_inकाष्ठाion_loop(inकाष्ठाions >> 5);

	prctl(PR_TASK_PERF_EVENTS_DISABLE);

	event_पढ़ो(&events[0]);
	event_पढ़ो(&events[1]);

	expected = inकाष्ठाions + overhead;
	dअगरference = events[0].result.value - expected;
	percentage = (द्विगुन)dअगरference / events[0].result.value * 100;

	अगर (report) अणु
		event_report(&events[0]);
		event_report(&events[1]);

		म_लिखो("Looped for %llu instructions, overhead %llu\n", inकाष्ठाions, overhead);
		म_लिखो("Expected %llu\n", expected);
		म_लिखो("Actual   %llu\n", events[0].result.value);
		म_लिखो("Delta    %lld, %f%%\n", dअगरference, percentage);
	पूर्ण

	event_reset(&events[0]);
	event_reset(&events[1]);

	अगर (dअगरference < 0)
		dअगरference = -dअगरference;

	/* Tolerate a dअगरference below 0.0001 % */
	dअगरference *= 10000 * 100;
	अगर (dअगरference / events[0].result.value)
		वापस -1;

	वापस 0;
पूर्ण

/* Count how many inकाष्ठाions it takes to करो a null loop */
अटल u64 determine_overhead(काष्ठा event *events)
अणु
	u64 current, overhead;
	पूर्णांक i;

	करो_count_loop(events, 0, 0, false);
	overhead = events[0].result.value;

	क्रम (i = 0; i < 100; i++) अणु
		करो_count_loop(events, 0, 0, false);
		current = events[0].result.value;
		अगर (current < overhead) अणु
			म_लिखो("Replacing overhead %llu with %llu\n", overhead, current);
			overhead = current;
		पूर्ण
	पूर्ण

	वापस overhead;
पूर्ण

अटल पूर्णांक test_body(व्योम)
अणु
	काष्ठा event events[2];
	u64 overhead;

	setup_event(&events[0], PERF_COUNT_HW_INSTRUCTIONS, "instructions");
	setup_event(&events[1], PERF_COUNT_HW_CPU_CYCLES, "cycles");

	अगर (event_खोलो(&events[0])) अणु
		लिखो_त्रुटि("perf_event_open");
		वापस -1;
	पूर्ण

	अगर (event_खोलो_with_group(&events[1], events[0].fd)) अणु
		लिखो_त्रुटि("perf_event_open");
		वापस -1;
	पूर्ण

	overhead = determine_overhead(events);
	म_लिखो("Overhead of null loop: %llu instructions\n", overhead);

	/* Run क्रम 1Mi inकाष्ठाions */
	FAIL_IF(करो_count_loop(events, 1000000, overhead, true));

	/* Run क्रम 10Mi inकाष्ठाions */
	FAIL_IF(करो_count_loop(events, 10000000, overhead, true));

	/* Run क्रम 100Mi inकाष्ठाions */
	FAIL_IF(करो_count_loop(events, 100000000, overhead, true));

	/* Run क्रम 1Bi inकाष्ठाions */
	FAIL_IF(करो_count_loop(events, 1000000000, overhead, true));

	/* Run क्रम 16Bi inकाष्ठाions */
	FAIL_IF(करो_count_loop(events, 16000000000, overhead, true));

	/* Run क्रम 64Bi inकाष्ठाions */
	FAIL_IF(करो_count_loop(events, 64000000000, overhead, true));

	event_बंद(&events[0]);
	event_बंद(&events[1]);

	वापस 0;
पूर्ण

अटल पूर्णांक count_inकाष्ठाions(व्योम)
अणु
	वापस eat_cpu(test_body);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(count_inकाष्ठाions, "count_instructions");
पूर्ण
