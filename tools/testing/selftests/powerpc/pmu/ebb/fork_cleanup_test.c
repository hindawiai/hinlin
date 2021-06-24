<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014, Michael Ellerman, IBM Corp.
 */

#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <stdbool.h>
#समावेश <sys/types.h>
#समावेश <sys/रुको.h>
#समावेश <unistd.h>
#समावेश <समलाँघ.स>

#समावेश "ebb.h"


/*
 * Test that a विभाजन clears the PMU state of the child. eg. BESCR/EBBHR/EBBRR
 * are cleared, and MMCR0_PMCC is reset, preventing the child from accessing
 * the PMU.
 */

अटल काष्ठा event event;

अटल पूर्णांक child(व्योम)
अणु
	/* Even though we have EBE=0 we can still see the EBB regs */
	FAIL_IF(mfspr(SPRN_BESCR) != 0);
	FAIL_IF(mfspr(SPRN_EBBHR) != 0);
	FAIL_IF(mfspr(SPRN_EBBRR) != 0);

	FAIL_IF(catch_sigill(ग_लिखो_pmc1));

	/* We can still पढ़ो from the event, though it is on our parent */
	FAIL_IF(event_पढ़ो(&event));

	वापस 0;
पूर्ण

/* Tests that विभाजन clears EBB state */
पूर्णांक विभाजन_cleanup(व्योम)
अणु
	pid_t pid;

	SKIP_IF(!ebb_is_supported());

	event_init_named(&event, 0x1001e, "cycles");
	event_leader_ebb_init(&event);

	FAIL_IF(event_खोलो(&event));

	ebb_enable_pmc_counting(1);
	setup_ebb_handler(standard_ebb_callee);
	ebb_global_enable();

	FAIL_IF(ebb_event_enable(&event));

	mtspr(SPRN_MMCR0, MMCR0_FC);
	mtspr(SPRN_PMC1, pmc_sample_period(sample_period));

	/* Don't need to actually take any EBBs */

	pid = विभाजन();
	अगर (pid == 0)
		निकास(child());

	/* Child करोes the actual testing */
	FAIL_IF(रुको_क्रम_child(pid));

	/* After विभाजन */
	event_बंद(&event);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(विभाजन_cleanup, "fork_cleanup");
पूर्ण
