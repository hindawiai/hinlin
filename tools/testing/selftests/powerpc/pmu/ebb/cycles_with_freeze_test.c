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
 * Test of counting cycles जबतक using MMCR0_FC (मुक्तze counters) to only count
 * parts of the code. This is complicated by the fact that FC is set by the
 * hardware when the event overflows. We may take the EBB after we have set FC,
 * so we have to be careful about whether we clear FC at the end of the EBB
 * handler or not.
 */

अटल bool counters_frozen = false;
अटल पूर्णांक ebbs_जबतक_frozen = 0;

अटल व्योम ebb_callee(व्योम)
अणु
	uपूर्णांक64_t mask, val;

	mask = MMCR0_PMAO | MMCR0_FC;

	val = mfspr(SPRN_BESCR);
	अगर (!(val & BESCR_PMEO)) अणु
		ebb_state.stats.spurious++;
		जाओ out;
	पूर्ण

	ebb_state.stats.ebb_count++;
	trace_log_counter(ebb_state.trace, ebb_state.stats.ebb_count);

	val = mfspr(SPRN_MMCR0);
	trace_log_reg(ebb_state.trace, SPRN_MMCR0, val);

	अगर (counters_frozen) अणु
		trace_log_string(ebb_state.trace, "frozen");
		ebbs_जबतक_frozen++;
		mask &= ~MMCR0_FC;
	पूर्ण

	count_pmc(1, sample_period);
out:
	reset_ebb_with_clear_mask(mask);
पूर्ण

पूर्णांक cycles_with_मुक्तze(व्योम)
अणु
	काष्ठा event event;
	uपूर्णांक64_t val;
	bool fc_cleared;

	SKIP_IF(!ebb_is_supported());

	event_init_named(&event, 0x1001e, "cycles");
	event_leader_ebb_init(&event);

	event.attr.exclude_kernel = 1;
	event.attr.exclude_hv = 1;
	event.attr.exclude_idle = 1;

	FAIL_IF(event_खोलो(&event));

	setup_ebb_handler(ebb_callee);
	ebb_global_enable();
	FAIL_IF(ebb_event_enable(&event));

	mtspr(SPRN_PMC1, pmc_sample_period(sample_period));

	fc_cleared = false;

	/* Make sure we loop until we take at least one EBB */
	जबतक ((ebb_state.stats.ebb_count < 20 && !fc_cleared) ||
		ebb_state.stats.ebb_count < 1)
	अणु
		counters_frozen = false;
		mb();
		mtspr(SPRN_MMCR0, mfspr(SPRN_MMCR0) & ~MMCR0_FC);

		FAIL_IF(core_busy_loop());

		counters_frozen = true;
		mb();
		mtspr(SPRN_MMCR0, mfspr(SPRN_MMCR0) |  MMCR0_FC);

		val = mfspr(SPRN_MMCR0);
		अगर (! (val & MMCR0_FC)) अणु
			म_लिखो("Outside of loop, FC NOT set MMCR0 0x%lx\n", val);
			fc_cleared = true;
		पूर्ण
	पूर्ण

	ebb_global_disable();
	ebb_मुक्तze_pmcs();

	dump_ebb_state();

	म_लिखो("EBBs while frozen %d\n", ebbs_जबतक_frozen);

	event_बंद(&event);

	FAIL_IF(ebb_state.stats.ebb_count == 0);
	FAIL_IF(fc_cleared);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(cycles_with_मुक्तze, "cycles_with_freeze");
पूर्ण
