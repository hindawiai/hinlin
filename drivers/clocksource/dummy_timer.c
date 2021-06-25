<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/घड़ीsource/dummy_समयr.c
 *
 *  Copyright (C) 2013 ARM Ltd.
 *  All Rights Reserved
 */
#समावेश <linux/घड़ीchips.h>
#समावेश <linux/cpu.h>
#समावेश <linux/init.h>
#समावेश <linux/percpu.h>
#समावेश <linux/cpumask.h>

अटल DEFINE_PER_CPU(काष्ठा घड़ी_event_device, dummy_समयr_evt);

अटल पूर्णांक dummy_समयr_starting_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा घड़ी_event_device *evt = per_cpu_ptr(&dummy_समयr_evt, cpu);

	evt->name	= "dummy_timer";
	evt->features	= CLOCK_EVT_FEAT_PERIODIC |
			  CLOCK_EVT_FEAT_ONESHOT |
			  CLOCK_EVT_FEAT_DUMMY;
	evt->rating	= 100;
	evt->cpumask	= cpumask_of(cpu);

	घड़ीevents_रेजिस्टर_device(evt);
	वापस 0;
पूर्ण

अटल पूर्णांक __init dummy_समयr_रेजिस्टर(व्योम)
अणु
	वापस cpuhp_setup_state(CPUHP_AP_DUMMY_TIMER_STARTING,
				 "clockevents/dummy_timer:starting",
				 dummy_समयr_starting_cpu, शून्य);
पूर्ण
early_initcall(dummy_समयr_रेजिस्टर);
