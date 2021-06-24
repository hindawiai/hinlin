<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014, Michael Ellerman, IBM Corp.
 */

#समावेश <sched.h>
#समावेश <संकेत.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/mman.h>

#समावेश "ebb.h"


/*
 * Test that tries to trigger CPU_FTR_PMAO_BUG. Which is a hardware defect
 * where an exception triggers but we context चयन beक्रमe it is delivered and
 * lose the exception.
 */

अटल पूर्णांक test_body(व्योम)
अणु
	पूर्णांक i, orig_period, max_period;
	काष्ठा event event;

	SKIP_IF(!ebb_is_supported());

	/* We use PMC4 to make sure the kernel चयनes all counters correctly */
	event_init_named(&event, 0x40002, "instructions");
	event_leader_ebb_init(&event);

	event.attr.exclude_kernel = 1;
	event.attr.exclude_hv = 1;
	event.attr.exclude_idle = 1;

	FAIL_IF(event_खोलो(&event));

	ebb_enable_pmc_counting(4);
	setup_ebb_handler(standard_ebb_callee);
	ebb_global_enable();
	FAIL_IF(ebb_event_enable(&event));

	/*
	 * We want a low sample period, but we also want to get out of the EBB
	 * handler without tripping up again.
	 *
	 * This value picked after much experimentation.
	 */
	orig_period = max_period = sample_period = 400;

	mtspr(SPRN_PMC4, pmc_sample_period(sample_period));

	जबतक (ebb_state.stats.ebb_count < 1000000) अणु
		/*
		 * We are trying to get the EBB exception to race exactly with
		 * us entering the kernel to करो the syscall. We then need the
		 * kernel to decide our बारlice is up and context चयन to
		 * the other thपढ़ो. When we come back our EBB will have been
		 * lost and we'll spin in this जबतक loop क्रमever.
		 */

		क्रम (i = 0; i < 100000; i++)
			sched_yield();

		/* Change the sample period slightly to try and hit the race */
		अगर (sample_period >= (orig_period + 200))
			sample_period = orig_period;
		अन्यथा
			sample_period++;

		अगर (sample_period > max_period)
			max_period = sample_period;
	पूर्ण

	ebb_मुक्तze_pmcs();
	ebb_global_disable();

	mtspr(SPRN_PMC4, 0xdead);

	dump_summary_ebb_state();
	dump_ebb_hw_state();

	event_बंद(&event);

	FAIL_IF(ebb_state.stats.ebb_count == 0);

	/* We vary our sample period so we need extra fudge here */
	FAIL_IF(!ebb_check_count(4, orig_period, 2 * (max_period - orig_period)));

	वापस 0;
पूर्ण

अटल पूर्णांक lost_exception(व्योम)
अणु
	वापस eat_cpu(test_body);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	test_harness_set_समयout(300);
	वापस test_harness(lost_exception, "lost_exception");
पूर्ण
