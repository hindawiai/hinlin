<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Emulate a local घड़ी event device via a pseuकरो घड़ी device.
 */
#समावेश <linux/cpu.h>
#समावेश <linux/err.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/percpu.h>
#समावेश <linux/profile.h>
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/module.h>

#समावेश "tick-internal.h"

अटल काष्ठा hrसमयr bस_समयr;

अटल पूर्णांक bc_shutकरोwn(काष्ठा घड़ी_event_device *evt)
अणु
	/*
	 * Note, we cannot cancel the समयr here as we might
	 * run पूर्णांकo the following live lock scenario:
	 *
	 * cpu 0		cpu1
	 * lock(broadcast_lock);
	 *			hrसमयr_पूर्णांकerrupt()
	 *			bc_handler()
	 *			   tick_handle_oneshot_broadcast();
	 *			    lock(broadcast_lock);
	 * hrसमयr_cancel()
	 *  रुको_क्रम_callback()
	 */
	hrसमयr_try_to_cancel(&bस_समयr);
	वापस 0;
पूर्ण

/*
 * This is called from the guts of the broadcast code when the cpu
 * which is about to enter idle has the earliest broadcast समयr event.
 */
अटल पूर्णांक bc_set_next(kसमय_प्रकार expires, काष्ठा घड़ी_event_device *bc)
अणु
	/*
	 * This is called either from enter/निकास idle code or from the
	 * broadcast handler. In all हालs tick_broadcast_lock is held.
	 *
	 * hrसमयr_cancel() cannot be called here neither from the
	 * broadcast handler nor from the enter/निकास idle code. The idle
	 * code can run पूर्णांकo the problem described in bc_shutकरोwn() and the
	 * broadcast handler cannot रुको क्रम itself to complete क्रम obvious
	 * reasons.
	 *
	 * Each caller tries to arm the hrसमयr on its own CPU, but अगर the
	 * hrसमयr callback function is currently running, then
	 * hrसमयr_start() cannot move it and the समयr stays on the CPU on
	 * which it is asचिन्हित at the moment.
	 *
	 * As this can be called from idle code, the hrसमयr_start()
	 * invocation has to be wrapped with RCU_NONIDLE() as
	 * hrसमयr_start() can call पूर्णांकo tracing.
	 */
	RCU_NONIDLE( अणु
		hrसमयr_start(&bस_समयr, expires, HRTIMER_MODE_ABS_PINNED_HARD);
		/*
		 * The core tick broadcast mode expects bc->bound_on to be set
		 * correctly to prevent a CPU which has the broadcast hrसमयr
		 * armed from going deep idle.
		 *
		 * As tick_broadcast_lock is held, nothing can change the cpu
		 * base which was just established in hrसमयr_start() above. So
		 * the below access is safe even without holding the hrसमयr
		 * base lock.
		 */
		bc->bound_on = bस_समयr.base->cpu_base->cpu;
	पूर्ण );
	वापस 0;
पूर्ण

अटल काष्ठा घड़ी_event_device ce_broadcast_hrसमयr = अणु
	.name			= "bc_hrtimer",
	.set_state_shutकरोwn	= bc_shutकरोwn,
	.set_next_kसमय		= bc_set_next,
	.features		= CLOCK_EVT_FEAT_ONESHOT |
				  CLOCK_EVT_FEAT_KTIME |
				  CLOCK_EVT_FEAT_HRTIMER,
	.rating			= 0,
	.bound_on		= -1,
	.min_delta_ns		= 1,
	.max_delta_ns		= KTIME_MAX,
	.min_delta_ticks	= 1,
	.max_delta_ticks	= अच_दीर्घ_उच्च,
	.mult			= 1,
	.shअगरt			= 0,
	.cpumask		= cpu_possible_mask,
पूर्ण;

अटल क्रमागत hrसमयr_restart bc_handler(काष्ठा hrसमयr *t)
अणु
	ce_broadcast_hrसमयr.event_handler(&ce_broadcast_hrसमयr);

	वापस HRTIMER_NORESTART;
पूर्ण

व्योम tick_setup_hrसमयr_broadcast(व्योम)
अणु
	hrसमयr_init(&bस_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_ABS_HARD);
	bस_समयr.function = bc_handler;
	घड़ीevents_रेजिस्टर_device(&ce_broadcast_hrसमयr);
पूर्ण
