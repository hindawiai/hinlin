<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file contains functions which manage high resolution tick
 * related events.
 *
 * Copyright(C) 2005-2006, Thomas Gleixner <tglx@linutronix.de>
 * Copyright(C) 2005-2007, Red Hat, Inc., Ingo Molnar
 * Copyright(C) 2006-2007, Timesys Corp., Thomas Gleixner
 */
#समावेश <linux/cpu.h>
#समावेश <linux/err.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/percpu.h>
#समावेश <linux/profile.h>
#समावेश <linux/sched.h>

#समावेश "tick-internal.h"

/**
 * tick_program_event
 */
पूर्णांक tick_program_event(kसमय_प्रकार expires, पूर्णांक क्रमce)
अणु
	काष्ठा घड़ी_event_device *dev = __this_cpu_पढ़ो(tick_cpu_device.evtdev);

	अगर (unlikely(expires == KTIME_MAX)) अणु
		/*
		 * We करोn't need the घड़ी event device any more, stop it.
		 */
		घड़ीevents_चयन_state(dev, CLOCK_EVT_STATE_ONESHOT_STOPPED);
		dev->next_event = KTIME_MAX;
		वापस 0;
	पूर्ण

	अगर (unlikely(घड़ीevent_state_oneshot_stopped(dev))) अणु
		/*
		 * We need the घड़ी event again, configure it in ONESHOT mode
		 * beक्रमe using it.
		 */
		घड़ीevents_चयन_state(dev, CLOCK_EVT_STATE_ONESHOT);
	पूर्ण

	वापस घड़ीevents_program_event(dev, expires, क्रमce);
पूर्ण

/**
 * tick_resume_oneshot - resume oneshot mode
 */
व्योम tick_resume_oneshot(व्योम)
अणु
	काष्ठा घड़ी_event_device *dev = __this_cpu_पढ़ो(tick_cpu_device.evtdev);

	घड़ीevents_चयन_state(dev, CLOCK_EVT_STATE_ONESHOT);
	घड़ीevents_program_event(dev, kसमय_get(), true);
पूर्ण

/**
 * tick_setup_oneshot - setup the event device क्रम oneshot mode (hres or nohz)
 */
व्योम tick_setup_oneshot(काष्ठा घड़ी_event_device *newdev,
			व्योम (*handler)(काष्ठा घड़ी_event_device *),
			kसमय_प्रकार next_event)
अणु
	newdev->event_handler = handler;
	घड़ीevents_चयन_state(newdev, CLOCK_EVT_STATE_ONESHOT);
	घड़ीevents_program_event(newdev, next_event, true);
पूर्ण

/**
 * tick_चयन_to_oneshot - चयन to oneshot mode
 */
पूर्णांक tick_चयन_to_oneshot(व्योम (*handler)(काष्ठा घड़ी_event_device *))
अणु
	काष्ठा tick_device *td = this_cpu_ptr(&tick_cpu_device);
	काष्ठा घड़ी_event_device *dev = td->evtdev;

	अगर (!dev || !(dev->features & CLOCK_EVT_FEAT_ONESHOT) ||
		    !tick_device_is_functional(dev)) अणु

		pr_info("Clockevents: could not switch to one-shot mode:");
		अगर (!dev) अणु
			pr_cont(" no tick device\n");
		पूर्ण अन्यथा अणु
			अगर (!tick_device_is_functional(dev))
				pr_cont(" %s is not functional.\n", dev->name);
			अन्यथा
				pr_cont(" %s does not support one-shot mode.\n",
					dev->name);
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	td->mode = TICKDEV_MODE_ONESHOT;
	dev->event_handler = handler;
	घड़ीevents_चयन_state(dev, CLOCK_EVT_STATE_ONESHOT);
	tick_broadcast_चयन_to_oneshot();
	वापस 0;
पूर्ण

/**
 * tick_check_oneshot_mode - check whether the प्रणाली is in oneshot mode
 *
 * वापसs 1 when either nohz or highres are enabled. otherwise 0.
 */
पूर्णांक tick_oneshot_mode_active(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	local_irq_save(flags);
	ret = __this_cpu_पढ़ो(tick_cpu_device.mode) == TICKDEV_MODE_ONESHOT;
	local_irq_restore(flags);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_HIGH_RES_TIMERS
/**
 * tick_init_highres - चयन to high resolution mode
 *
 * Called with पूर्णांकerrupts disabled.
 */
पूर्णांक tick_init_highres(व्योम)
अणु
	वापस tick_चयन_to_oneshot(hrसमयr_पूर्णांकerrupt);
पूर्ण
#पूर्ण_अगर
