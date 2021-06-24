<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014, Michael Ellerman, IBM Corp.
 */

#समावेश <sched.h>
#समावेश <संकेत.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>

#समावेश "ebb.h"


/*
 * Test that the kernel properly handles PMAE across context चयनes.
 *
 * We test this by calling पूर्णांकo the kernel inside our EBB handler, where PMAE
 * is clear. A cpu eater companion thपढ़ो is running on the same CPU as us to
 * encourage the scheduler to चयन us.
 *
 * The kernel must make sure that when it context चयनes us back in, it
 * honours the fact that we had PMAE clear.
 *
 * Observed to hit the failing हाल on the first EBB with a broken kernel.
 */

अटल bool mmcr0_mismatch;
अटल uपूर्णांक64_t beक्रमe, after;

अटल व्योम syscall_ebb_callee(व्योम)
अणु
	uपूर्णांक64_t val;

	val = mfspr(SPRN_BESCR);
	अगर (!(val & BESCR_PMEO)) अणु
		ebb_state.stats.spurious++;
		जाओ out;
	पूर्ण

	ebb_state.stats.ebb_count++;
	count_pmc(1, sample_period);

	beक्रमe = mfspr(SPRN_MMCR0);

	/* Try and get ourselves scheduled, to क्रमce a PMU context चयन */
	sched_yield();

	after = mfspr(SPRN_MMCR0);
	अगर (beक्रमe != after)
		mmcr0_mismatch = true;

out:
	reset_ebb();
पूर्ण

अटल पूर्णांक test_body(व्योम)
अणु
	काष्ठा event event;

	SKIP_IF(!ebb_is_supported());

	event_init_named(&event, 0x1001e, "cycles");
	event_leader_ebb_init(&event);

	event.attr.exclude_kernel = 1;
	event.attr.exclude_hv = 1;
	event.attr.exclude_idle = 1;

	FAIL_IF(event_खोलो(&event));

	setup_ebb_handler(syscall_ebb_callee);
	ebb_global_enable();

	FAIL_IF(ebb_event_enable(&event));

	mtspr(SPRN_PMC1, pmc_sample_period(sample_period));

	जबतक (ebb_state.stats.ebb_count < 20 && !mmcr0_mismatch)
		FAIL_IF(core_busy_loop());

	ebb_global_disable();
	ebb_मुक्तze_pmcs();

	dump_ebb_state();

	अगर (mmcr0_mismatch)
		म_लिखो("Saw MMCR0 before 0x%lx after 0x%lx\n", beक्रमe, after);

	event_बंद(&event);

	FAIL_IF(ebb_state.stats.ebb_count == 0);
	FAIL_IF(mmcr0_mismatch);

	वापस 0;
पूर्ण

पूर्णांक pmae_handling(व्योम)
अणु
	वापस eat_cpu(test_body);
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(pmae_handling, "pmae_handling");
पूर्ण
