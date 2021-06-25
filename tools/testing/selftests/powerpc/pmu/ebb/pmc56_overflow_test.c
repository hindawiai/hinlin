<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014, Michael Ellerman, IBM Corp.
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>

#समावेश "ebb.h"


/*
 * Test that PMC5 & 6 are frozen (ie. करोn't overflow) when they are not being
 * used. Tests the MMCR0_FC56 logic in the kernel.
 */

अटल पूर्णांक pmc56_overflowed;

अटल व्योम ebb_callee(व्योम)
अणु
	uपूर्णांक64_t val;

	val = mfspr(SPRN_BESCR);
	अगर (!(val & BESCR_PMEO)) अणु
		ebb_state.stats.spurious++;
		जाओ out;
	पूर्ण

	ebb_state.stats.ebb_count++;
	count_pmc(2, sample_period);

	val = mfspr(SPRN_PMC5);
	अगर (val >= COUNTER_OVERFLOW)
		pmc56_overflowed++;

	count_pmc(5, COUNTER_OVERFLOW);

	val = mfspr(SPRN_PMC6);
	अगर (val >= COUNTER_OVERFLOW)
		pmc56_overflowed++;

	count_pmc(6, COUNTER_OVERFLOW);

out:
	reset_ebb();
पूर्ण

पूर्णांक pmc56_overflow(व्योम)
अणु
	काष्ठा event event;

	SKIP_IF(!ebb_is_supported());

	/* Use PMC2 so we set PMCjCE, which enables PMC5/6 */
	event_init(&event, 0x2001e);
	event_leader_ebb_init(&event);

	event.attr.exclude_kernel = 1;
	event.attr.exclude_hv = 1;
	event.attr.exclude_idle = 1;

	FAIL_IF(event_खोलो(&event));

	setup_ebb_handler(ebb_callee);
	ebb_global_enable();

	FAIL_IF(ebb_event_enable(&event));

	mtspr(SPRN_PMC2, pmc_sample_period(sample_period));
	mtspr(SPRN_PMC5, 0);
	mtspr(SPRN_PMC6, 0);

	जबतक (ebb_state.stats.ebb_count < 10)
		FAIL_IF(core_busy_loop());

	ebb_global_disable();
	ebb_मुक्तze_pmcs();

	dump_ebb_state();

	म_लिखो("PMC5/6 overflow %d\n", pmc56_overflowed);

	event_बंद(&event);

	FAIL_IF(ebb_state.stats.ebb_count == 0 || pmc56_overflowed != 0);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(pmc56_overflow, "pmc56_overflow");
पूर्ण
