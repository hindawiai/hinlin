<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014, Michael Ellerman, IBM Corp.
 */

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <stdbool.h>

#समावेश "ebb.h"


/*
 * Test of counting cycles जबतक manipulating the user accessible bits in MMCR2.
 */

/* We use two values because the first मुक्तzes PMC1 and so we would get no EBBs */
#घोषणा MMCR2_EXPECTED_1 0x4020100804020000UL /* (FC1P|FC2P|FC3P|FC4P|FC5P|FC6P) */
#घोषणा MMCR2_EXPECTED_2 0x0020100804020000UL /* (     FC2P|FC3P|FC4P|FC5P|FC6P) */


पूर्णांक cycles_with_mmcr2(व्योम)
अणु
	काष्ठा event event;
	uपूर्णांक64_t val, expected[2], actual;
	पूर्णांक i;
	bool bad_mmcr2;

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

	/* XXX Set of MMCR2 must be after enable */
	expected[0] = MMCR2_EXPECTED_1;
	expected[1] = MMCR2_EXPECTED_2;
	i = 0;
	bad_mmcr2 = false;

	/* Make sure we loop until we take at least one EBB */
	जबतक ((ebb_state.stats.ebb_count < 20 && !bad_mmcr2) ||
		ebb_state.stats.ebb_count < 1)
	अणु
		mtspr(SPRN_MMCR2, expected[i % 2]);

		FAIL_IF(core_busy_loop());

		val = mfspr(SPRN_MMCR2);
		अगर (val != expected[i % 2]) अणु
			bad_mmcr2 = true;
			actual = val;
		पूर्ण

		i++;
	पूर्ण

	ebb_global_disable();
	ebb_मुक्तze_pmcs();

	dump_ebb_state();

	event_बंद(&event);

	FAIL_IF(ebb_state.stats.ebb_count == 0);

	अगर (bad_mmcr2)
		म_लिखो("Bad MMCR2 value seen is 0x%lx\n", actual);

	FAIL_IF(bad_mmcr2);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(cycles_with_mmcr2, "cycles_with_mmcr2");
पूर्ण
