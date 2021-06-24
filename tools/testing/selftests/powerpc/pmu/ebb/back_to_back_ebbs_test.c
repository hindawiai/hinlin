<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2014, Michael Ellerman, IBM Corp.
 */

#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>

#समावेश "ebb.h"


#घोषणा NUMBER_OF_EBBS	50

/*
 * Test that अगर we overflow the counter जबतक in the EBB handler, we take
 * another EBB on निकासing from the handler.
 *
 * We करो this by counting with a stupidly low sample period, causing us to
 * overflow the PMU जबतक we're still in the EBB handler, leading to another
 * EBB.
 *
 * We get out of what would otherwise be an infinite loop by leaving the
 * counter frozen once we've taken enough EBBs.
 */

अटल व्योम ebb_callee(व्योम)
अणु
	uपूर्णांक64_t siar, val;

	val = mfspr(SPRN_BESCR);
	अगर (!(val & BESCR_PMEO)) अणु
		ebb_state.stats.spurious++;
		जाओ out;
	पूर्ण

	ebb_state.stats.ebb_count++;
	trace_log_counter(ebb_state.trace, ebb_state.stats.ebb_count);

	/* Resets the PMC */
	count_pmc(1, sample_period);

out:
	अगर (ebb_state.stats.ebb_count == NUMBER_OF_EBBS)
		/* Reset but leave counters frozen */
		reset_ebb_with_clear_mask(MMCR0_PMAO);
	अन्यथा
		/* Unमुक्तzes */
		reset_ebb();

	/* Do some stuff to chew some cycles and pop the counter */
	siar = mfspr(SPRN_SIAR);
	trace_log_reg(ebb_state.trace, SPRN_SIAR, siar);

	val = mfspr(SPRN_PMC1);
	trace_log_reg(ebb_state.trace, SPRN_PMC1, val);

	val = mfspr(SPRN_MMCR0);
	trace_log_reg(ebb_state.trace, SPRN_MMCR0, val);
पूर्ण

पूर्णांक back_to_back_ebbs(व्योम)
अणु
	काष्ठा event event;

	SKIP_IF(!ebb_is_supported());

	event_init_named(&event, 0x1001e, "cycles");
	event_leader_ebb_init(&event);

	event.attr.exclude_kernel = 1;
	event.attr.exclude_hv = 1;
	event.attr.exclude_idle = 1;

	FAIL_IF(event_खोलो(&event));

	setup_ebb_handler(ebb_callee);

	FAIL_IF(ebb_event_enable(&event));

	sample_period = 5;

	ebb_मुक्तze_pmcs();
	mtspr(SPRN_PMC1, pmc_sample_period(sample_period));
	ebb_global_enable();
	ebb_unमुक्तze_pmcs();

	जबतक (ebb_state.stats.ebb_count < NUMBER_OF_EBBS)
		FAIL_IF(core_busy_loop());

	ebb_global_disable();
	ebb_मुक्तze_pmcs();

	dump_ebb_state();

	event_बंद(&event);

	FAIL_IF(ebb_state.stats.ebb_count != NUMBER_OF_EBBS);

	वापस 0;
पूर्ण

पूर्णांक मुख्य(व्योम)
अणु
	वापस test_harness(back_to_back_ebbs, "back_to_back_ebbs");
पूर्ण
