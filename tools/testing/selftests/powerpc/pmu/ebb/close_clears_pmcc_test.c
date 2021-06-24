<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014, Michael Ellerman, IBM Corp.
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <समलाँघ.स>
#समावेश <संकेत.स>

#समावेश "ebb.h"


/*
 * Test that closing the EBB event clears MMCR0_PMCC, preventing further access
 * by userspace to the PMU hardware.
 */

पूर्णांक बंद_clears_pmcc(व्योम)
अणु
	काष्ठा event event;

	SKIP_IF(!ebb_is_supported());

	event_init_named(&event, 0x1001e, "cycles");
	event_leader_ebb_init(&event);

	FAIL_IF(event_खोलो(&event));

	ebb_enable_pmc_counting(1);
	setup_ebb_handler(standard_ebb_callee);
	ebb_global_enable();
	FAIL_IF(ebb_event_enable(&event));

	mtspr(SPRN_PMC1, pmc_sample_period(sample_period));

	जबतक (ebb_state.stats.ebb_count < 1)
		FAIL_IF(core_busy_loop());

	ebb_global_disable();
	event_बंद(&event);

	FAIL_IF(ebb_state.stats.ebb_count == 0);

	/* The real test is here, करो we take a संक_अवैध when writing PMU regs now
	 * that we have बंदd the event. We expect that we will. */

	FAIL_IF(catch_sigill(ग_लिखो_pmc1));

	/* We should still be able to पढ़ो EBB regs though */
	mfspr(SPRN_EBBHR);
	mfspr(SPRN_EBBRR);
	mfspr(SPRN_BESCR);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(बंद_clears_pmcc, "close_clears_pmcc");
पूर्ण
