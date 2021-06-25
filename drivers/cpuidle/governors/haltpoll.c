<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * haltpoll.c - haltpoll idle governor
 *
 * Copyright 2019 Red Hat, Inc. and/or its affiliates.
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 *
 * Authors: Marcelo Tosatti <mtosatti@redhat.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/समय.स>
#समावेश <linux/kसमय.स>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/tick.h>
#समावेश <linux/sched.h>
#समावेश <linux/module.h>
#समावेश <linux/kvm_para.h>

अटल अचिन्हित पूर्णांक guest_halt_poll_ns __पढ़ो_mostly = 200000;
module_param(guest_halt_poll_ns, uपूर्णांक, 0644);

/* भागision factor to shrink halt_poll_ns */
अटल अचिन्हित पूर्णांक guest_halt_poll_shrink __पढ़ो_mostly = 2;
module_param(guest_halt_poll_shrink, uपूर्णांक, 0644);

/* multiplication factor to grow per-cpu poll_limit_ns */
अटल अचिन्हित पूर्णांक guest_halt_poll_grow __पढ़ो_mostly = 2;
module_param(guest_halt_poll_grow, uपूर्णांक, 0644);

/* value in us to start growing per-cpu halt_poll_ns */
अटल अचिन्हित पूर्णांक guest_halt_poll_grow_start __पढ़ो_mostly = 50000;
module_param(guest_halt_poll_grow_start, uपूर्णांक, 0644);

/* allow shrinking guest halt poll */
अटल bool guest_halt_poll_allow_shrink __पढ़ो_mostly = true;
module_param(guest_halt_poll_allow_shrink, bool, 0644);

/**
 * haltpoll_select - selects the next idle state to enter
 * @drv: cpuidle driver containing state data
 * @dev: the CPU
 * @stop_tick: indication on whether or not to stop the tick
 */
अटल पूर्णांक haltpoll_select(काष्ठा cpuidle_driver *drv,
			   काष्ठा cpuidle_device *dev,
			   bool *stop_tick)
अणु
	s64 latency_req = cpuidle_governor_latency_req(dev->cpu);

	अगर (!drv->state_count || latency_req == 0) अणु
		*stop_tick = false;
		वापस 0;
	पूर्ण

	अगर (dev->poll_limit_ns == 0)
		वापस 1;

	/* Last state was poll? */
	अगर (dev->last_state_idx == 0) अणु
		/* Halt अगर no event occurred on poll winकरोw */
		अगर (dev->poll_समय_limit == true)
			वापस 1;

		*stop_tick = false;
		/* Otherwise, poll again */
		वापस 0;
	पूर्ण

	*stop_tick = false;
	/* Last state was halt: poll */
	वापस 0;
पूर्ण

अटल व्योम adjust_poll_limit(काष्ठा cpuidle_device *dev, u64 block_ns)
अणु
	अचिन्हित पूर्णांक val;

	/* Grow cpu_halt_poll_us अगर
	 * cpu_halt_poll_us < block_ns < guest_halt_poll_us
	 */
	अगर (block_ns > dev->poll_limit_ns && block_ns <= guest_halt_poll_ns) अणु
		val = dev->poll_limit_ns * guest_halt_poll_grow;

		अगर (val < guest_halt_poll_grow_start)
			val = guest_halt_poll_grow_start;
		अगर (val > guest_halt_poll_ns)
			val = guest_halt_poll_ns;

		dev->poll_limit_ns = val;
	पूर्ण अन्यथा अगर (block_ns > guest_halt_poll_ns &&
		   guest_halt_poll_allow_shrink) अणु
		अचिन्हित पूर्णांक shrink = guest_halt_poll_shrink;

		val = dev->poll_limit_ns;
		अगर (shrink == 0)
			val = 0;
		अन्यथा
			val /= shrink;
		dev->poll_limit_ns = val;
	पूर्ण
पूर्ण

/**
 * haltpoll_reflect - update variables and update poll समय
 * @dev: the CPU
 * @index: the index of actual entered state
 */
अटल व्योम haltpoll_reflect(काष्ठा cpuidle_device *dev, पूर्णांक index)
अणु
	dev->last_state_idx = index;

	अगर (index != 0)
		adjust_poll_limit(dev, dev->last_residency_ns);
पूर्ण

/**
 * haltpoll_enable_device - scans a CPU's states and करोes setup
 * @drv: cpuidle driver
 * @dev: the CPU
 */
अटल पूर्णांक haltpoll_enable_device(काष्ठा cpuidle_driver *drv,
				  काष्ठा cpuidle_device *dev)
अणु
	dev->poll_limit_ns = 0;

	वापस 0;
पूर्ण

अटल काष्ठा cpuidle_governor haltpoll_governor = अणु
	.name =			"haltpoll",
	.rating =		9,
	.enable =		haltpoll_enable_device,
	.select =		haltpoll_select,
	.reflect =		haltpoll_reflect,
पूर्ण;

अटल पूर्णांक __init init_haltpoll(व्योम)
अणु
	अगर (kvm_para_available())
		वापस cpuidle_रेजिस्टर_governor(&haltpoll_governor);

	वापस 0;
पूर्ण

postcore_initcall(init_haltpoll);
