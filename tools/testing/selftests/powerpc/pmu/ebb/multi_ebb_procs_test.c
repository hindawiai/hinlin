<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014, Michael Ellerman, IBM Corp.
 */

#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <संकेत.स>

#समावेश "ebb.h"


/*
 * Test running multiple EBB using processes at once on a single CPU. They
 * should all run happily without पूर्णांकerfering with each other.
 */

अटल bool child_should_निकास;

अटल व्योम sigपूर्णांक_handler(पूर्णांक संकेत)
अणु
	child_should_निकास = true;
पूर्ण

काष्ठा sigaction sigपूर्णांक_action = अणु
	.sa_handler = sigपूर्णांक_handler,
पूर्ण;

अटल पूर्णांक cycles_child(व्योम)
अणु
	काष्ठा event event;

	अगर (sigaction(संक_विघ्न, &sigपूर्णांक_action, शून्य)) अणु
		लिखो_त्रुटि("sigaction");
		वापस 1;
	पूर्ण

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

	जबतक (!child_should_निकास) अणु
		FAIL_IF(core_busy_loop());
		FAIL_IF(ebb_check_mmcr0());
	पूर्ण

	ebb_global_disable();
	ebb_मुक्तze_pmcs();

	dump_summary_ebb_state();

	event_बंद(&event);

	FAIL_IF(ebb_state.stats.ebb_count == 0);

	वापस 0;
पूर्ण

#घोषणा NR_CHILDREN	4

पूर्णांक multi_ebb_procs(व्योम)
अणु
	pid_t pids[NR_CHILDREN];
	पूर्णांक cpu, rc, i;

	SKIP_IF(!ebb_is_supported());

	cpu = pick_online_cpu();
	FAIL_IF(cpu < 0);
	FAIL_IF(bind_to_cpu(cpu));

	क्रम (i = 0; i < NR_CHILDREN; i++) अणु
		pids[i] = विभाजन();
		अगर (pids[i] == 0)
			निकास(cycles_child());
	पूर्ण

	/* Have them all run क्रम "a while" */
	sleep(10);

	rc = 0;
	क्रम (i = 0; i < NR_CHILDREN; i++) अणु
		/* Tell them to stop */
		समाप्त(pids[i], संक_विघ्न);
		/* And रुको */
		rc |= रुको_क्रम_child(pids[i]);
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(multi_ebb_procs, "multi_ebb_procs");
पूर्ण
