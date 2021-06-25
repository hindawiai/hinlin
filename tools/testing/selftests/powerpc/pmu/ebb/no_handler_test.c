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


/* Test that things work sanely अगर we have no handler */

अटल पूर्णांक no_handler_test(व्योम)
अणु
	काष्ठा event event;
	u64 val;
	पूर्णांक i;

	SKIP_IF(!ebb_is_supported());

	event_init_named(&event, 0x1001e, "cycles");
	event_leader_ebb_init(&event);

	event.attr.exclude_kernel = 1;
	event.attr.exclude_hv = 1;
	event.attr.exclude_idle = 1;

	FAIL_IF(event_खोलो(&event));
	FAIL_IF(ebb_event_enable(&event));

	val = mfspr(SPRN_EBBHR);
	FAIL_IF(val != 0);

	/* Make sure it overflows quickly */
	sample_period = 1000;
	mtspr(SPRN_PMC1, pmc_sample_period(sample_period));

	/* Spin to make sure the event has समय to overflow */
	क्रम (i = 0; i < 1000; i++)
		mb();

	dump_ebb_state();

	/* We expect to see the PMU frozen & PMAO set */
	val = mfspr(SPRN_MMCR0);
	FAIL_IF(val != 0x0000000080000080);

	event_बंद(&event);

	dump_ebb_state();

	/* The real test is that we never took an EBB at 0x0 */

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(no_handler_test,"no_handler_test");
पूर्ण
