<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014, Michael Ellerman, IBM Corp.
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>

#समावेश "ebb.h"


/*
 * Basic test that counts user cycles and takes EBBs.
 */
पूर्णांक cycles(व्योम)
अणु
	काष्ठा event event;

	SKIP_IF(!ebb_is_supported());

	event_init_named(&event, 0x1001e, "cycles");
	event_leader_ebb_init(&event);

	event.attr.exclude_kernel = 1;
	event.attr.exclude_hv = 1;
	event.attr.exclude_idle = 1;

	FAIL_IF(event_खोलो(&event));

	ebb_enable_pmc_counting(1);
	setup_ebb_handler(standard_ebb_callee);
	ebb_global_enable();
	FAIL_IF(ebb_event_enable(&event));

	mtspr(SPRN_PMC1, pmc_sample_period(sample_period));

	जबतक (ebb_state.stats.ebb_count < 10) अणु
		FAIL_IF(core_busy_loop());
		FAIL_IF(ebb_check_mmcr0());
	पूर्ण

	ebb_global_disable();
	ebb_मुक्तze_pmcs();

	dump_ebb_state();

	event_बंद(&event);

	FAIL_IF(ebb_state.stats.ebb_count == 0);
	FAIL_IF(!ebb_check_count(1, sample_period, 100));

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(cycles, "cycles");
पूर्ण
