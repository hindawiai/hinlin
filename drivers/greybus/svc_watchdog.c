<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SVC Greybus "watchdog" driver.
 *
 * Copyright 2016 Google Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/suspend.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/greybus.h>

#घोषणा SVC_WATCHDOG_PERIOD	(2 * HZ)

काष्ठा gb_svc_watchकरोg अणु
	काष्ठा delayed_work	work;
	काष्ठा gb_svc		*svc;
	bool			enabled;
	काष्ठा notअगरier_block pm_notअगरier;
पूर्ण;

अटल काष्ठा delayed_work reset_work;

अटल पूर्णांक svc_watchकरोg_pm_notअगरier(काष्ठा notअगरier_block *notअगरier,
				    अचिन्हित दीर्घ pm_event, व्योम *unused)
अणु
	काष्ठा gb_svc_watchकरोg *watchकरोg =
		container_of(notअगरier, काष्ठा gb_svc_watchकरोg, pm_notअगरier);

	चयन (pm_event) अणु
	हाल PM_SUSPEND_PREPARE:
		gb_svc_watchकरोg_disable(watchकरोg->svc);
		अवरोध;
	हाल PM_POST_SUSPEND:
		gb_svc_watchकरोg_enable(watchकरोg->svc);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल व्योम greybus_reset(काष्ठा work_काष्ठा *work)
अणु
	अटल अक्षर स्थिर start_path[] = "/system/bin/start";
	अटल अक्षर *envp[] = अणु
		"HOME=/",
		"PATH=/sbin:/vendor/bin:/system/sbin:/system/bin:/system/xbin",
		शून्य,
	पूर्ण;
	अटल अक्षर *argv[] = अणु
		(अक्षर *)start_path,
		"unipro_reset",
		शून्य,
	पूर्ण;

	pr_err("svc_watchdog: calling \"%s %s\" to reset greybus network!\n",
	       argv[0], argv[1]);
	call_usermodehelper(start_path, argv, envp, UMH_WAIT_EXEC);
पूर्ण

अटल व्योम करो_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा gb_svc_watchकरोg *watchकरोg;
	काष्ठा gb_svc *svc;
	पूर्णांक retval;

	watchकरोg = container_of(work, काष्ठा gb_svc_watchकरोg, work.work);
	svc = watchकरोg->svc;

	dev_dbg(&svc->dev, "%s: ping.\n", __func__);
	retval = gb_svc_ping(svc);
	अगर (retval) अणु
		/*
		 * Something went really wrong, let's warn userspace and then
		 * pull the plug and reset the whole greybus network.
		 * We need to करो this outside of this workqueue as we will be
		 * tearing करोwn the svc device itself.  So queue up
		 * yet-another-callback to करो that.
		 */
		dev_err(&svc->dev,
			"SVC ping has returned %d, something is wrong!!!\n",
			retval);

		अगर (svc->action == GB_SVC_WATCHDOG_BITE_PANIC_KERNEL) अणु
			panic("SVC is not responding\n");
		पूर्ण अन्यथा अगर (svc->action == GB_SVC_WATCHDOG_BITE_RESET_UNIPRO) अणु
			dev_err(&svc->dev, "Resetting the greybus network, watch out!!!\n");

			INIT_DELAYED_WORK(&reset_work, greybus_reset);
			schedule_delayed_work(&reset_work, HZ / 2);

			/*
			 * Disable ourselves, we करोn't want to trip again unless
			 * userspace wants us to.
			 */
			watchकरोg->enabled = false;
		पूर्ण
	पूर्ण

	/* resubmit our work to happen again, अगर we are still "alive" */
	अगर (watchकरोg->enabled)
		schedule_delayed_work(&watchकरोg->work, SVC_WATCHDOG_PERIOD);
पूर्ण

पूर्णांक gb_svc_watchकरोg_create(काष्ठा gb_svc *svc)
अणु
	काष्ठा gb_svc_watchकरोg *watchकरोg;
	पूर्णांक retval;

	अगर (svc->watchकरोg)
		वापस 0;

	watchकरोg = kदो_स्मृति(माप(*watchकरोg), GFP_KERNEL);
	अगर (!watchकरोg)
		वापस -ENOMEM;

	watchकरोg->enabled = false;
	watchकरोg->svc = svc;
	INIT_DELAYED_WORK(&watchकरोg->work, करो_work);
	svc->watchकरोg = watchकरोg;

	watchकरोg->pm_notअगरier.notअगरier_call = svc_watchकरोg_pm_notअगरier;
	retval = रेजिस्टर_pm_notअगरier(&watchकरोg->pm_notअगरier);
	अगर (retval) अणु
		dev_err(&svc->dev, "error registering pm notifier(%d)\n",
			retval);
		जाओ svc_watchकरोg_create_err;
	पूर्ण

	retval = gb_svc_watchकरोg_enable(svc);
	अगर (retval) अणु
		dev_err(&svc->dev, "error enabling watchdog (%d)\n", retval);
		unरेजिस्टर_pm_notअगरier(&watchकरोg->pm_notअगरier);
		जाओ svc_watchकरोg_create_err;
	पूर्ण
	वापस retval;

svc_watchकरोg_create_err:
	svc->watchकरोg = शून्य;
	kमुक्त(watchकरोg);

	वापस retval;
पूर्ण

व्योम gb_svc_watchकरोg_destroy(काष्ठा gb_svc *svc)
अणु
	काष्ठा gb_svc_watchकरोg *watchकरोg = svc->watchकरोg;

	अगर (!watchकरोg)
		वापस;

	unरेजिस्टर_pm_notअगरier(&watchकरोg->pm_notअगरier);
	gb_svc_watchकरोg_disable(svc);
	svc->watchकरोg = शून्य;
	kमुक्त(watchकरोg);
पूर्ण

bool gb_svc_watchकरोg_enabled(काष्ठा gb_svc *svc)
अणु
	अगर (!svc || !svc->watchकरोg)
		वापस false;
	वापस svc->watchकरोg->enabled;
पूर्ण

पूर्णांक gb_svc_watchकरोg_enable(काष्ठा gb_svc *svc)
अणु
	काष्ठा gb_svc_watchकरोg *watchकरोg;

	अगर (!svc->watchकरोg)
		वापस -ENODEV;

	watchकरोg = svc->watchकरोg;
	अगर (watchकरोg->enabled)
		वापस 0;

	watchकरोg->enabled = true;
	schedule_delayed_work(&watchकरोg->work, SVC_WATCHDOG_PERIOD);
	वापस 0;
पूर्ण

पूर्णांक gb_svc_watchकरोg_disable(काष्ठा gb_svc *svc)
अणु
	काष्ठा gb_svc_watchकरोg *watchकरोg;

	अगर (!svc->watchकरोg)
		वापस -ENODEV;

	watchकरोg = svc->watchकरोg;
	अगर (!watchकरोg->enabled)
		वापस 0;

	watchकरोg->enabled = false;
	cancel_delayed_work_sync(&watchकरोg->work);
	वापस 0;
पूर्ण
