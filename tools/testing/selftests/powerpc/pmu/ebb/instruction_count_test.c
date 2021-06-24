<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014, Michael Ellerman, IBM Corp.
 */

#घोषणा _GNU_SOURCE

#समावेश <मानकपन.स>
#समावेश <stdbool.h>
#समावेश <माला.स>
#समावेश <sys/prctl.h>

#समावेश "ebb.h"


/*
 * Run a calibrated inकाष्ठाion loop and count inकाष्ठाions executed using
 * EBBs. Make sure the counts look right.
 */

बाह्य व्योम thirty_two_inकाष्ठाion_loop(uपूर्णांक64_t loops);

अटल bool counters_frozen = true;

अटल पूर्णांक करो_count_loop(काष्ठा event *event, uपूर्णांक64_t inकाष्ठाions,
			 uपूर्णांक64_t overhead, bool report)
अणु
	पूर्णांक64_t dअगरference, expected;
	द्विगुन percentage;

	clear_ebb_stats();

	counters_frozen = false;
	mb();
	mtspr(SPRN_MMCR0, mfspr(SPRN_MMCR0) & ~MMCR0_FC);

	thirty_two_inकाष्ठाion_loop(inकाष्ठाions >> 5);

	counters_frozen = true;
	mb();
	mtspr(SPRN_MMCR0, mfspr(SPRN_MMCR0) | MMCR0_FC);

	count_pmc(4, sample_period);

	event->result.value = ebb_state.stats.pmc_count[4-1];
	expected = inकाष्ठाions + overhead;
	dअगरference = event->result.value - expected;
	percentage = (द्विगुन)dअगरference / event->result.value * 100;

	अगर (report) अणु
		म_लिखो("Looped for %lu instructions, overhead %lu\n", inकाष्ठाions, overhead);
		म_लिखो("Expected %lu\n", expected);
		म_लिखो("Actual   %llu\n", event->result.value);
		म_लिखो("Delta    %ld, %f%%\n", dअगरference, percentage);
		म_लिखो("Took %d EBBs\n", ebb_state.stats.ebb_count);
	पूर्ण

	अगर (dअगरference < 0)
		dअगरference = -dअगरference;

	/* Tolerate a dअगरference of up to 0.0001 % */
	dअगरference *= 10000 * 100;
	अगर (dअगरference / event->result.value)
		वापस -1;

	वापस 0;
पूर्ण

/* Count how many inकाष्ठाions it takes to करो a null loop */
अटल uपूर्णांक64_t determine_overhead(काष्ठा event *event)
अणु
	uपूर्णांक64_t current, overhead;
	पूर्णांक i;

	करो_count_loop(event, 0, 0, false);
	overhead = event->result.value;

	क्रम (i = 0; i < 100; i++) अणु
		करो_count_loop(event, 0, 0, false);
		current = event->result.value;
		अगर (current < overhead) अणु
			म_लिखो("Replacing overhead %lu with %lu\n", overhead, current);
			overhead = current;
		पूर्ण
	पूर्ण

	वापस overhead;
पूर्ण

अटल व्योम pmc4_ebb_callee(व्योम)
अणु
	uपूर्णांक64_t val;

	val = mfspr(SPRN_BESCR);
	अगर (!(val & BESCR_PMEO)) अणु
		ebb_state.stats.spurious++;
		जाओ out;
	पूर्ण

	ebb_state.stats.ebb_count++;
	count_pmc(4, sample_period);
out:
	अगर (counters_frozen)
		reset_ebb_with_clear_mask(MMCR0_PMAO);
	अन्यथा
		reset_ebb();
पूर्ण

पूर्णांक inकाष्ठाion_count(व्योम)
अणु
	काष्ठा event event;
	uपूर्णांक64_t overhead;

	SKIP_IF(!ebb_is_supported());

	event_init_named(&event, 0x400FA, "PM_RUN_INST_CMPL");
	event_leader_ebb_init(&event);
	event.attr.exclude_kernel = 1;
	event.attr.exclude_hv = 1;
	event.attr.exclude_idle = 1;

	FAIL_IF(event_खोलो(&event));
	FAIL_IF(ebb_event_enable(&event));

	sample_period = COUNTER_OVERFLOW;

	setup_ebb_handler(pmc4_ebb_callee);
	mtspr(SPRN_MMCR0, mfspr(SPRN_MMCR0) & ~MMCR0_FC);
	ebb_global_enable();

	overhead = determine_overhead(&event);
	म_लिखो("Overhead of null loop: %lu instructions\n", overhead);

	/* Run क्रम 1M inकाष्ठाions */
	FAIL_IF(करो_count_loop(&event, 0x100000, overhead, true));

	/* Run क्रम 10M inकाष्ठाions */
	FAIL_IF(करो_count_loop(&event, 0xa00000, overhead, true));

	/* Run क्रम 100M inकाष्ठाions */
	FAIL_IF(करो_count_loop(&event, 0x6400000, overhead, true));

	/* Run क्रम 1G inकाष्ठाions */
	FAIL_IF(करो_count_loop(&event, 0x40000000, overhead, true));

	/* Run क्रम 16G inकाष्ठाions */
	FAIL_IF(करो_count_loop(&event, 0x400000000, overhead, true));

	/* Run क्रम 64G inकाष्ठाions */
	FAIL_IF(करो_count_loop(&event, 0x1000000000, overhead, true));

	/* Run क्रम 128G inकाष्ठाions */
	FAIL_IF(करो_count_loop(&event, 0x2000000000, overhead, true));

	ebb_global_disable();
	event_बंद(&event);

	म_लिखो("Finished OK\n");

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	test_harness_set_समयout(300);
	वापस test_harness(inकाष्ठाion_count, "instruction_count");
पूर्ण
