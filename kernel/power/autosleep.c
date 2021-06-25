<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * kernel/घातer/स्वतःsleep.c
 *
 * Opportunistic sleep support.
 *
 * Copyright (C) 2012 Rafael J. Wysocki <rjw@sisk.pl>
 */

#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pm_wakeup.h>

#समावेश "power.h"

अटल suspend_state_t स्वतःsleep_state;
अटल काष्ठा workqueue_काष्ठा *स्वतःsleep_wq;
/*
 * Note: it is only safe to mutex_lock(&स्वतःsleep_lock) अगर a wakeup_source
 * is active, otherwise a deadlock with try_to_suspend() is possible.
 * Alternatively mutex_lock_पूर्णांकerruptible() can be used.  This will then fail
 * अगर an स्वतः_sleep cycle tries to मुक्तze processes.
 */
अटल DEFINE_MUTEX(स्वतःsleep_lock);
अटल काष्ठा wakeup_source *स्वतःsleep_ws;

अटल व्योम try_to_suspend(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित पूर्णांक initial_count, final_count;

	अगर (!pm_get_wakeup_count(&initial_count, true))
		जाओ out;

	mutex_lock(&स्वतःsleep_lock);

	अगर (!pm_save_wakeup_count(initial_count) ||
		प्रणाली_state != SYSTEM_RUNNING) अणु
		mutex_unlock(&स्वतःsleep_lock);
		जाओ out;
	पूर्ण

	अगर (स्वतःsleep_state == PM_SUSPEND_ON) अणु
		mutex_unlock(&स्वतःsleep_lock);
		वापस;
	पूर्ण
	अगर (स्वतःsleep_state >= PM_SUSPEND_MAX)
		hibernate();
	अन्यथा
		pm_suspend(स्वतःsleep_state);

	mutex_unlock(&स्वतःsleep_lock);

	अगर (!pm_get_wakeup_count(&final_count, false))
		जाओ out;

	/*
	 * If the wakeup occurred क्रम an unknown reason, रुको to prevent the
	 * प्रणाली from trying to suspend and waking up in a tight loop.
	 */
	अगर (final_count == initial_count)
		schedule_समयout_unपूर्णांकerruptible(HZ / 2);

 out:
	queue_up_suspend_work();
पूर्ण

अटल DECLARE_WORK(suspend_work, try_to_suspend);

व्योम queue_up_suspend_work(व्योम)
अणु
	अगर (स्वतःsleep_state > PM_SUSPEND_ON)
		queue_work(स्वतःsleep_wq, &suspend_work);
पूर्ण

suspend_state_t pm_स्वतःsleep_state(व्योम)
अणु
	वापस स्वतःsleep_state;
पूर्ण

पूर्णांक pm_स्वतःsleep_lock(व्योम)
अणु
	वापस mutex_lock_पूर्णांकerruptible(&स्वतःsleep_lock);
पूर्ण

व्योम pm_स्वतःsleep_unlock(व्योम)
अणु
	mutex_unlock(&स्वतःsleep_lock);
पूर्ण

पूर्णांक pm_स्वतःsleep_set_state(suspend_state_t state)
अणु

#अगर_अघोषित CONFIG_HIBERNATION
	अगर (state >= PM_SUSPEND_MAX)
		वापस -EINVAL;
#पूर्ण_अगर

	__pm_stay_awake(स्वतःsleep_ws);

	mutex_lock(&स्वतःsleep_lock);

	स्वतःsleep_state = state;

	__pm_relax(स्वतःsleep_ws);

	अगर (state > PM_SUSPEND_ON) अणु
		pm_wakep_स्वतःsleep_enabled(true);
		queue_up_suspend_work();
	पूर्ण अन्यथा अणु
		pm_wakep_स्वतःsleep_enabled(false);
	पूर्ण

	mutex_unlock(&स्वतःsleep_lock);
	वापस 0;
पूर्ण

पूर्णांक __init pm_स्वतःsleep_init(व्योम)
अणु
	स्वतःsleep_ws = wakeup_source_रेजिस्टर(शून्य, "autosleep");
	अगर (!स्वतःsleep_ws)
		वापस -ENOMEM;

	स्वतःsleep_wq = alloc_ordered_workqueue("autosleep", 0);
	अगर (स्वतःsleep_wq)
		वापस 0;

	wakeup_source_unरेजिस्टर(स्वतःsleep_ws);
	वापस -ENOMEM;
पूर्ण
