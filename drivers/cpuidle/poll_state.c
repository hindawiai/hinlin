<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * poll_state.c - Polling idle state
 */

#समावेश <linux/cpuidle.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/sched/idle.h>

#घोषणा POLL_IDLE_RELAX_COUNT	200

अटल पूर्णांक __cpuidle poll_idle(काष्ठा cpuidle_device *dev,
			       काष्ठा cpuidle_driver *drv, पूर्णांक index)
अणु
	u64 समय_start = local_घड़ी();

	dev->poll_समय_limit = false;

	local_irq_enable();
	अगर (!current_set_polling_and_test()) अणु
		अचिन्हित पूर्णांक loop_count = 0;
		u64 limit;

		limit = cpuidle_poll_समय(drv, dev);

		जबतक (!need_resched()) अणु
			cpu_relax();
			अगर (loop_count++ < POLL_IDLE_RELAX_COUNT)
				जारी;

			loop_count = 0;
			अगर (local_घड़ी() - समय_start > limit) अणु
				dev->poll_समय_limit = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	current_clr_polling();

	वापस index;
पूर्ण

व्योम cpuidle_poll_state_init(काष्ठा cpuidle_driver *drv)
अणु
	काष्ठा cpuidle_state *state = &drv->states[0];

	snम_लिखो(state->name, CPUIDLE_NAME_LEN, "POLL");
	snम_लिखो(state->desc, CPUIDLE_DESC_LEN, "CPUIDLE CORE POLL IDLE");
	state->निकास_latency = 0;
	state->target_residency = 0;
	state->निकास_latency_ns = 0;
	state->target_residency_ns = 0;
	state->घातer_usage = -1;
	state->enter = poll_idle;
	state->flags = CPUIDLE_FLAG_POLLING;
पूर्ण
EXPORT_SYMBOL_GPL(cpuidle_poll_state_init);
