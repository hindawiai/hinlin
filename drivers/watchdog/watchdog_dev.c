<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *	watchकरोg_dev.c
 *
 *	(c) Copyright 2008-2011 Alan Cox <alan@lxorguk.ukuu.org.uk>,
 *						All Rights Reserved.
 *
 *	(c) Copyright 2008-2011 Wim Van Sebroeck <wim@iguana.be>.
 *
 *
 *	This source code is part of the generic code that can be used
 *	by all the watchकरोg समयr drivers.
 *
 *	This part of the generic code takes care of the following
 *	misc device: /dev/watchकरोg.
 *
 *	Based on source code of the following authors:
 *	  Matt Domsch <Matt_Domsch@dell.com>,
 *	  Rob Radez <rob@osinvestor.com>,
 *	  Rusty Lynch <rusty@linux.co.पूर्णांकel.com>
 *	  Satyam Sharma <satyam@infradead.org>
 *	  Randy Dunlap <अक्रमy.dunlap@oracle.com>
 *
 *	Neither Alan Cox, CymruNet Ltd., Wim Van Sebroeck nor Iguana vzw.
 *	admit liability nor provide warranty क्रम any of this software.
 *	This material is provided "AS-IS" and at no अक्षरge.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/cdev.h>		/* For अक्षरacter device */
#समावेश <linux/त्रुटिसं.स>	/* For the -ENODEV/... values */
#समावेश <linux/fs.h>		/* For file operations */
#समावेश <linux/init.h>		/* For __init/__निकास/... */
#समावेश <linux/hrसमयr.h>	/* For hrसमयrs */
#समावेश <linux/kernel.h>	/* For prपूर्णांकk/panic/... */
#समावेश <linux/kthपढ़ो.h>	/* For kthपढ़ो_work */
#समावेश <linux/miscdevice.h>	/* For handling misc devices */
#समावेश <linux/module.h>	/* For module stuff/... */
#समावेश <linux/mutex.h>	/* For mutexes */
#समावेश <linux/slab.h>		/* For memory functions */
#समावेश <linux/types.h>	/* For standard types (like माप_प्रकार) */
#समावेश <linux/watchकरोg.h>	/* For watchकरोg specअगरic items */
#समावेश <linux/uaccess.h>	/* For copy_to_user/put_user/... */

#समावेश "watchdog_core.h"
#समावेश "watchdog_pretimeout.h"

/*
 * काष्ठा watchकरोg_core_data - watchकरोg core पूर्णांकernal data
 * @dev:	The watchकरोg's पूर्णांकernal device
 * @cdev:	The watchकरोg's Character device.
 * @wdd:	Poपूर्णांकer to watchकरोg device.
 * @lock:	Lock क्रम watchकरोg core.
 * @status:	Watchकरोg core पूर्णांकernal status bits.
 */
काष्ठा watchकरोg_core_data अणु
	काष्ठा device dev;
	काष्ठा cdev cdev;
	काष्ठा watchकरोg_device *wdd;
	काष्ठा mutex lock;
	kसमय_प्रकार last_keepalive;
	kसमय_प्रकार last_hw_keepalive;
	kसमय_प्रकार खोलो_deadline;
	काष्ठा hrसमयr समयr;
	काष्ठा kthपढ़ो_work work;
	अचिन्हित दीर्घ status;		/* Internal status bits */
#घोषणा _WDOG_DEV_OPEN		0	/* Opened ? */
#घोषणा _WDOG_ALLOW_RELEASE	1	/* Did we receive the magic अक्षर ? */
#घोषणा _WDOG_KEEPALIVE		2	/* Did we receive a keepalive ? */
पूर्ण;

/* the dev_t काष्ठाure to store the dynamically allocated watchकरोg devices */
अटल dev_t watchकरोg_devt;
/* Reference to watchकरोg device behind /dev/watchकरोg */
अटल काष्ठा watchकरोg_core_data *old_wd_data;

अटल काष्ठा kthपढ़ो_worker *watchकरोg_kworker;

अटल bool handle_boot_enabled =
	IS_ENABLED(CONFIG_WATCHDOG_HANDLE_BOOT_ENABLED);

अटल अचिन्हित खोलो_समयout = CONFIG_WATCHDOG_OPEN_TIMEOUT;

अटल bool watchकरोg_past_खोलो_deadline(काष्ठा watchकरोg_core_data *data)
अणु
	वापस kसमय_after(kसमय_get(), data->खोलो_deadline);
पूर्ण

अटल व्योम watchकरोg_set_खोलो_deadline(काष्ठा watchकरोg_core_data *data)
अणु
	data->खोलो_deadline = खोलो_समयout ?
		kसमय_get() + kसमय_set(खोलो_समयout, 0) : KTIME_MAX;
पूर्ण

अटल अंतरभूत bool watchकरोg_need_worker(काष्ठा watchकरोg_device *wdd)
अणु
	/* All variables in milli-seconds */
	अचिन्हित पूर्णांक hm = wdd->max_hw_heartbeat_ms;
	अचिन्हित पूर्णांक t = wdd->समयout * 1000;

	/*
	 * A worker to generate heartbeat requests is needed अगर all of the
	 * following conditions are true.
	 * - Userspace activated the watchकरोg.
	 * - The driver provided a value क्रम the maximum hardware समयout, and
	 *   thus is aware that the framework supports generating heartbeat
	 *   requests.
	 * - Userspace requests a दीर्घer समयout than the hardware can handle.
	 *
	 * Alternatively, अगर userspace has not खोलोed the watchकरोg
	 * device, we take care of feeding the watchकरोg अगर it is
	 * running.
	 */
	वापस (hm && watchकरोg_active(wdd) && t > hm) ||
		(t && !watchकरोg_active(wdd) && watchकरोg_hw_running(wdd));
पूर्ण

अटल kसमय_प्रकार watchकरोg_next_keepalive(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा watchकरोg_core_data *wd_data = wdd->wd_data;
	अचिन्हित पूर्णांक समयout_ms = wdd->समयout * 1000;
	kसमय_प्रकार keepalive_पूर्णांकerval;
	kसमय_प्रकार last_heartbeat, latest_heartbeat;
	kसमय_प्रकार virt_समयout;
	अचिन्हित पूर्णांक hw_heartbeat_ms;

	अगर (watchकरोg_active(wdd))
		virt_समयout = kसमय_add(wd_data->last_keepalive,
					 ms_to_kसमय(समयout_ms));
	अन्यथा
		virt_समयout = wd_data->खोलो_deadline;

	hw_heartbeat_ms = min_not_zero(समयout_ms, wdd->max_hw_heartbeat_ms);
	keepalive_पूर्णांकerval = ms_to_kसमय(hw_heartbeat_ms / 2);

	/*
	 * To ensure that the watchकरोg बार out wdd->समयout seconds
	 * after the most recent ping from userspace, the last
	 * worker ping has to come in hw_heartbeat_ms beक्रमe this समयout.
	 */
	last_heartbeat = kसमय_sub(virt_समयout, ms_to_kसमय(hw_heartbeat_ms));
	latest_heartbeat = kसमय_sub(last_heartbeat, kसमय_get());
	अगर (kसमय_beक्रमe(latest_heartbeat, keepalive_पूर्णांकerval))
		वापस latest_heartbeat;
	वापस keepalive_पूर्णांकerval;
पूर्ण

अटल अंतरभूत व्योम watchकरोg_update_worker(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा watchकरोg_core_data *wd_data = wdd->wd_data;

	अगर (watchकरोg_need_worker(wdd)) अणु
		kसमय_प्रकार t = watchकरोg_next_keepalive(wdd);

		अगर (t > 0)
			hrसमयr_start(&wd_data->समयr, t,
				      HRTIMER_MODE_REL_HARD);
	पूर्ण अन्यथा अणु
		hrसमयr_cancel(&wd_data->समयr);
	पूर्ण
पूर्ण

अटल पूर्णांक __watchकरोg_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा watchकरोg_core_data *wd_data = wdd->wd_data;
	kसमय_प्रकार earliest_keepalive, now;
	पूर्णांक err;

	earliest_keepalive = kसमय_add(wd_data->last_hw_keepalive,
				       ms_to_kसमय(wdd->min_hw_heartbeat_ms));
	now = kसमय_get();

	अगर (kसमय_after(earliest_keepalive, now)) अणु
		hrसमयr_start(&wd_data->समयr,
			      kसमय_sub(earliest_keepalive, now),
			      HRTIMER_MODE_REL_HARD);
		वापस 0;
	पूर्ण

	wd_data->last_hw_keepalive = now;

	अगर (wdd->ops->ping)
		err = wdd->ops->ping(wdd);  /* ping the watchकरोg */
	अन्यथा
		err = wdd->ops->start(wdd); /* restart watchकरोg */

	watchकरोg_update_worker(wdd);

	वापस err;
पूर्ण

/*
 *	watchकरोg_ping: ping the watchकरोg.
 *	@wdd: the watchकरोg device to ping
 *
 *	The caller must hold wd_data->lock.
 *
 *	If the watchकरोg has no own ping operation then it needs to be
 *	restarted via the start operation. This wrapper function करोes
 *	exactly that.
 *	We only ping when the watchकरोg device is running.
 */

अटल पूर्णांक watchकरोg_ping(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा watchकरोg_core_data *wd_data = wdd->wd_data;

	अगर (!watchकरोg_active(wdd) && !watchकरोg_hw_running(wdd))
		वापस 0;

	set_bit(_WDOG_KEEPALIVE, &wd_data->status);

	wd_data->last_keepalive = kसमय_get();
	वापस __watchकरोg_ping(wdd);
पूर्ण

अटल bool watchकरोg_worker_should_ping(काष्ठा watchकरोg_core_data *wd_data)
अणु
	काष्ठा watchकरोg_device *wdd = wd_data->wdd;

	अगर (!wdd)
		वापस false;

	अगर (watchकरोg_active(wdd))
		वापस true;

	वापस watchकरोg_hw_running(wdd) && !watchकरोg_past_खोलो_deadline(wd_data);
पूर्ण

अटल व्योम watchकरोg_ping_work(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा watchकरोg_core_data *wd_data;

	wd_data = container_of(work, काष्ठा watchकरोg_core_data, work);

	mutex_lock(&wd_data->lock);
	अगर (watchकरोg_worker_should_ping(wd_data))
		__watchकरोg_ping(wd_data->wdd);
	mutex_unlock(&wd_data->lock);
पूर्ण

अटल क्रमागत hrसमयr_restart watchकरोg_समयr_expired(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा watchकरोg_core_data *wd_data;

	wd_data = container_of(समयr, काष्ठा watchकरोg_core_data, समयr);

	kthपढ़ो_queue_work(watchकरोg_kworker, &wd_data->work);
	वापस HRTIMER_NORESTART;
पूर्ण

/*
 *	watchकरोg_start: wrapper to start the watchकरोg.
 *	@wdd: the watchकरोg device to start
 *
 *	The caller must hold wd_data->lock.
 *
 *	Start the watchकरोg अगर it is not active and mark it active.
 *	This function वापसs zero on success or a negative त्रुटि_सं code क्रम
 *	failure.
 */

अटल पूर्णांक watchकरोg_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा watchकरोg_core_data *wd_data = wdd->wd_data;
	kसमय_प्रकार started_at;
	पूर्णांक err;

	अगर (watchकरोg_active(wdd))
		वापस 0;

	set_bit(_WDOG_KEEPALIVE, &wd_data->status);

	started_at = kसमय_get();
	अगर (watchकरोg_hw_running(wdd) && wdd->ops->ping) अणु
		err = __watchकरोg_ping(wdd);
		अगर (err == 0)
			set_bit(WDOG_ACTIVE, &wdd->status);
	पूर्ण अन्यथा अणु
		err = wdd->ops->start(wdd);
		अगर (err == 0) अणु
			set_bit(WDOG_ACTIVE, &wdd->status);
			wd_data->last_keepalive = started_at;
			wd_data->last_hw_keepalive = started_at;
			watchकरोg_update_worker(wdd);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

/*
 *	watchकरोg_stop: wrapper to stop the watchकरोg.
 *	@wdd: the watchकरोg device to stop
 *
 *	The caller must hold wd_data->lock.
 *
 *	Stop the watchकरोg अगर it is still active and unmark it active.
 *	This function वापसs zero on success or a negative त्रुटि_सं code क्रम
 *	failure.
 *	If the 'nowayout' feature was set, the watchकरोg cannot be stopped.
 */

अटल पूर्णांक watchकरोg_stop(काष्ठा watchकरोg_device *wdd)
अणु
	पूर्णांक err = 0;

	अगर (!watchकरोg_active(wdd))
		वापस 0;

	अगर (test_bit(WDOG_NO_WAY_OUT, &wdd->status)) अणु
		pr_info("watchdog%d: nowayout prevents watchdog being stopped!\n",
			wdd->id);
		वापस -EBUSY;
	पूर्ण

	अगर (wdd->ops->stop) अणु
		clear_bit(WDOG_HW_RUNNING, &wdd->status);
		err = wdd->ops->stop(wdd);
	पूर्ण अन्यथा अणु
		set_bit(WDOG_HW_RUNNING, &wdd->status);
	पूर्ण

	अगर (err == 0) अणु
		clear_bit(WDOG_ACTIVE, &wdd->status);
		watchकरोg_update_worker(wdd);
	पूर्ण

	वापस err;
पूर्ण

/*
 *	watchकरोg_get_status: wrapper to get the watchकरोg status
 *	@wdd: the watchकरोg device to get the status from
 *
 *	The caller must hold wd_data->lock.
 *
 *	Get the watchकरोg's status flags.
 */

अटल अचिन्हित पूर्णांक watchकरोg_get_status(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा watchकरोg_core_data *wd_data = wdd->wd_data;
	अचिन्हित पूर्णांक status;

	अगर (wdd->ops->status)
		status = wdd->ops->status(wdd);
	अन्यथा
		status = wdd->bootstatus & (WDIOF_CARDRESET |
					    WDIOF_OVERHEAT |
					    WDIOF_FANFAULT |
					    WDIOF_EXTERN1 |
					    WDIOF_EXTERN2 |
					    WDIOF_POWERUNDER |
					    WDIOF_POWEROVER);

	अगर (test_bit(_WDOG_ALLOW_RELEASE, &wd_data->status))
		status |= WDIOF_MAGICCLOSE;

	अगर (test_and_clear_bit(_WDOG_KEEPALIVE, &wd_data->status))
		status |= WDIOF_KEEPALIVEPING;

	वापस status;
पूर्ण

/*
 *	watchकरोg_set_समयout: set the watchकरोg समयr समयout
 *	@wdd: the watchकरोg device to set the समयout क्रम
 *	@समयout: समयout to set in seconds
 *
 *	The caller must hold wd_data->lock.
 */

अटल पूर्णांक watchकरोg_set_समयout(काष्ठा watchकरोg_device *wdd,
							अचिन्हित पूर्णांक समयout)
अणु
	पूर्णांक err = 0;

	अगर (!(wdd->info->options & WDIOF_SETTIMEOUT))
		वापस -EOPNOTSUPP;

	अगर (watchकरोg_समयout_invalid(wdd, समयout))
		वापस -EINVAL;

	अगर (wdd->ops->set_समयout) अणु
		err = wdd->ops->set_समयout(wdd, समयout);
	पूर्ण अन्यथा अणु
		wdd->समयout = समयout;
		/* Disable preसमयout अगर it करोesn't fit the new समयout */
		अगर (wdd->preसमयout >= wdd->समयout)
			wdd->preसमयout = 0;
	पूर्ण

	watchकरोg_update_worker(wdd);

	वापस err;
पूर्ण

/*
 *	watchकरोg_set_preसमयout: set the watchकरोg समयr preसमयout
 *	@wdd: the watchकरोg device to set the समयout क्रम
 *	@समयout: preसमयout to set in seconds
 */

अटल पूर्णांक watchकरोg_set_preसमयout(काष्ठा watchकरोg_device *wdd,
				   अचिन्हित पूर्णांक समयout)
अणु
	पूर्णांक err = 0;

	अगर (!(wdd->info->options & WDIOF_PRETIMEOUT))
		वापस -EOPNOTSUPP;

	अगर (watchकरोg_preसमयout_invalid(wdd, समयout))
		वापस -EINVAL;

	अगर (wdd->ops->set_preसमयout)
		err = wdd->ops->set_preसमयout(wdd, समयout);
	अन्यथा
		wdd->preसमयout = समयout;

	वापस err;
पूर्ण

/*
 *	watchकरोg_get_समयleft: wrapper to get the समय left beक्रमe a reboot
 *	@wdd: the watchकरोg device to get the reमुख्यing समय from
 *	@समयleft: the समय that's left
 *
 *	The caller must hold wd_data->lock.
 *
 *	Get the समय beक्रमe a watchकरोg will reboot (अगर not pinged).
 */

अटल पूर्णांक watchकरोg_get_समयleft(काष्ठा watchकरोg_device *wdd,
							अचिन्हित पूर्णांक *समयleft)
अणु
	*समयleft = 0;

	अगर (!wdd->ops->get_समयleft)
		वापस -EOPNOTSUPP;

	*समयleft = wdd->ops->get_समयleft(wdd);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_WATCHDOG_SYSFS
अटल sमाप_प्रकार nowayout_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा watchकरोg_device *wdd = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", !!test_bit(WDOG_NO_WAY_OUT, &wdd->status));
पूर्ण

अटल sमाप_प्रकार nowayout_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा watchकरोg_device *wdd = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक value;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 0, &value);
	अगर (ret)
		वापस ret;
	अगर (value > 1)
		वापस -EINVAL;
	/* nowayout cannot be disabled once set */
	अगर (test_bit(WDOG_NO_WAY_OUT, &wdd->status) && !value)
		वापस -EPERM;
	watchकरोg_set_nowayout(wdd, value);
	वापस len;
पूर्ण
अटल DEVICE_ATTR_RW(nowayout);

अटल sमाप_प्रकार status_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा watchकरोg_device *wdd = dev_get_drvdata(dev);
	काष्ठा watchकरोg_core_data *wd_data = wdd->wd_data;
	अचिन्हित पूर्णांक status;

	mutex_lock(&wd_data->lock);
	status = watchकरोg_get_status(wdd);
	mutex_unlock(&wd_data->lock);

	वापस प्र_लिखो(buf, "0x%x\n", status);
पूर्ण
अटल DEVICE_ATTR_RO(status);

अटल sमाप_प्रकार bootstatus_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा watchकरोg_device *wdd = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", wdd->bootstatus);
पूर्ण
अटल DEVICE_ATTR_RO(bootstatus);

अटल sमाप_प्रकार समयleft_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा watchकरोg_device *wdd = dev_get_drvdata(dev);
	काष्ठा watchकरोg_core_data *wd_data = wdd->wd_data;
	sमाप_प्रकार status;
	अचिन्हित पूर्णांक val;

	mutex_lock(&wd_data->lock);
	status = watchकरोg_get_समयleft(wdd, &val);
	mutex_unlock(&wd_data->lock);
	अगर (!status)
		status = प्र_लिखो(buf, "%u\n", val);

	वापस status;
पूर्ण
अटल DEVICE_ATTR_RO(समयleft);

अटल sमाप_प्रकार समयout_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा watchकरोg_device *wdd = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", wdd->समयout);
पूर्ण
अटल DEVICE_ATTR_RO(समयout);

अटल sमाप_प्रकार preसमयout_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा watchकरोg_device *wdd = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%u\n", wdd->preसमयout);
पूर्ण
अटल DEVICE_ATTR_RO(preसमयout);

अटल sमाप_प्रकार identity_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा watchकरोg_device *wdd = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", wdd->info->identity);
पूर्ण
अटल DEVICE_ATTR_RO(identity);

अटल sमाप_प्रकार state_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा watchकरोg_device *wdd = dev_get_drvdata(dev);

	अगर (watchकरोg_active(wdd))
		वापस प्र_लिखो(buf, "active\n");

	वापस प्र_लिखो(buf, "inactive\n");
पूर्ण
अटल DEVICE_ATTR_RO(state);

अटल sमाप_प्रकार preसमयout_available_governors_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस watchकरोg_preसमयout_available_governors_get(buf);
पूर्ण
अटल DEVICE_ATTR_RO(preसमयout_available_governors);

अटल sमाप_प्रकार preसमयout_governor_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा watchकरोg_device *wdd = dev_get_drvdata(dev);

	वापस watchकरोg_preसमयout_governor_get(wdd, buf);
पूर्ण

अटल sमाप_प्रकार preसमयout_governor_store(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा watchकरोg_device *wdd = dev_get_drvdata(dev);
	पूर्णांक ret = watchकरोg_preसमयout_governor_set(wdd, buf);

	अगर (!ret)
		ret = count;

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RW(preसमयout_governor);

अटल umode_t wdt_is_visible(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा watchकरोg_device *wdd = dev_get_drvdata(dev);
	umode_t mode = attr->mode;

	अगर (attr == &dev_attr_समयleft.attr && !wdd->ops->get_समयleft)
		mode = 0;
	अन्यथा अगर (attr == &dev_attr_preसमयout.attr &&
		 !(wdd->info->options & WDIOF_PRETIMEOUT))
		mode = 0;
	अन्यथा अगर ((attr == &dev_attr_preसमयout_governor.attr ||
		  attr == &dev_attr_preसमयout_available_governors.attr) &&
		 (!(wdd->info->options & WDIOF_PRETIMEOUT) ||
		  !IS_ENABLED(CONFIG_WATCHDOG_PRETIMEOUT_GOV)))
		mode = 0;

	वापस mode;
पूर्ण
अटल काष्ठा attribute *wdt_attrs[] = अणु
	&dev_attr_state.attr,
	&dev_attr_identity.attr,
	&dev_attr_समयout.attr,
	&dev_attr_preसमयout.attr,
	&dev_attr_समयleft.attr,
	&dev_attr_bootstatus.attr,
	&dev_attr_status.attr,
	&dev_attr_nowayout.attr,
	&dev_attr_preसमयout_governor.attr,
	&dev_attr_preसमयout_available_governors.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group wdt_group = अणु
	.attrs = wdt_attrs,
	.is_visible = wdt_is_visible,
पूर्ण;
__ATTRIBUTE_GROUPS(wdt);
#अन्यथा
#घोषणा wdt_groups	शून्य
#पूर्ण_अगर

/*
 *	watchकरोg_ioctl_op: call the watchकरोg drivers ioctl op अगर defined
 *	@wdd: the watchकरोg device to करो the ioctl on
 *	@cmd: watchकरोg command
 *	@arg: argument poपूर्णांकer
 *
 *	The caller must hold wd_data->lock.
 */

अटल पूर्णांक watchकरोg_ioctl_op(काष्ठा watchकरोg_device *wdd, अचिन्हित पूर्णांक cmd,
							अचिन्हित दीर्घ arg)
अणु
	अगर (!wdd->ops->ioctl)
		वापस -ENOIOCTLCMD;

	वापस wdd->ops->ioctl(wdd, cmd, arg);
पूर्ण

/*
 *	watchकरोg_ग_लिखो: ग_लिखोs to the watchकरोg.
 *	@file: file from VFS
 *	@data: user address of data
 *	@len: length of data
 *	@ppos: poपूर्णांकer to the file offset
 *
 *	A ग_लिखो to a watchकरोg device is defined as a keepalive ping.
 *	Writing the magic 'V' sequence allows the next बंद to turn
 *	off the watchकरोg (अगर 'nowayout' is not set).
 */

अटल sमाप_प्रकार watchकरोg_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
						माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा watchकरोg_core_data *wd_data = file->निजी_data;
	काष्ठा watchकरोg_device *wdd;
	पूर्णांक err;
	माप_प्रकार i;
	अक्षर c;

	अगर (len == 0)
		वापस 0;

	/*
	 * Note: just in हाल someone wrote the magic अक्षरacter
	 * five months ago...
	 */
	clear_bit(_WDOG_ALLOW_RELEASE, &wd_data->status);

	/* scan to see whether or not we got the magic अक्षरacter */
	क्रम (i = 0; i != len; i++) अणु
		अगर (get_user(c, data + i))
			वापस -EFAULT;
		अगर (c == 'V')
			set_bit(_WDOG_ALLOW_RELEASE, &wd_data->status);
	पूर्ण

	/* someone wrote to us, so we send the watchकरोg a keepalive ping */

	err = -ENODEV;
	mutex_lock(&wd_data->lock);
	wdd = wd_data->wdd;
	अगर (wdd)
		err = watchकरोg_ping(wdd);
	mutex_unlock(&wd_data->lock);

	अगर (err < 0)
		वापस err;

	वापस len;
पूर्ण

/*
 *	watchकरोg_ioctl: handle the dअगरferent ioctl's क्रम the watchकरोg device.
 *	@file: file handle to the device
 *	@cmd: watchकरोg command
 *	@arg: argument poपूर्णांकer
 *
 *	The watchकरोg API defines a common set of functions क्रम all watchकरोgs
 *	according to their available features.
 */

अटल दीर्घ watchकरोg_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
							अचिन्हित दीर्घ arg)
अणु
	काष्ठा watchकरोg_core_data *wd_data = file->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;
	काष्ठा watchकरोg_device *wdd;
	पूर्णांक __user *p = argp;
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	mutex_lock(&wd_data->lock);

	wdd = wd_data->wdd;
	अगर (!wdd) अणु
		err = -ENODEV;
		जाओ out_ioctl;
	पूर्ण

	err = watchकरोg_ioctl_op(wdd, cmd, arg);
	अगर (err != -ENOIOCTLCMD)
		जाओ out_ioctl;

	चयन (cmd) अणु
	हाल WDIOC_GETSUPPORT:
		err = copy_to_user(argp, wdd->info,
			माप(काष्ठा watchकरोg_info)) ? -EFAULT : 0;
		अवरोध;
	हाल WDIOC_GETSTATUS:
		val = watchकरोg_get_status(wdd);
		err = put_user(val, p);
		अवरोध;
	हाल WDIOC_GETBOOTSTATUS:
		err = put_user(wdd->bootstatus, p);
		अवरोध;
	हाल WDIOC_SETOPTIONS:
		अगर (get_user(val, p)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (val & WDIOS_DISABLECARD) अणु
			err = watchकरोg_stop(wdd);
			अगर (err < 0)
				अवरोध;
		पूर्ण
		अगर (val & WDIOS_ENABLECARD)
			err = watchकरोg_start(wdd);
		अवरोध;
	हाल WDIOC_KEEPALIVE:
		अगर (!(wdd->info->options & WDIOF_KEEPALIVEPING)) अणु
			err = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
		err = watchकरोg_ping(wdd);
		अवरोध;
	हाल WDIOC_SETTIMEOUT:
		अगर (get_user(val, p)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		err = watchकरोg_set_समयout(wdd, val);
		अगर (err < 0)
			अवरोध;
		/* If the watchकरोg is active then we send a keepalive ping
		 * to make sure that the watchकरोg keep's running (and अगर
		 * possible that it takes the new समयout) */
		err = watchकरोg_ping(wdd);
		अगर (err < 0)
			अवरोध;
		fallthrough;
	हाल WDIOC_GETTIMEOUT:
		/* समयout == 0 means that we करोn't know the समयout */
		अगर (wdd->समयout == 0) अणु
			err = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
		err = put_user(wdd->समयout, p);
		अवरोध;
	हाल WDIOC_GETTIMELEFT:
		err = watchकरोg_get_समयleft(wdd, &val);
		अगर (err < 0)
			अवरोध;
		err = put_user(val, p);
		अवरोध;
	हाल WDIOC_SETPRETIMEOUT:
		अगर (get_user(val, p)) अणु
			err = -EFAULT;
			अवरोध;
		पूर्ण
		err = watchकरोg_set_preसमयout(wdd, val);
		अवरोध;
	हाल WDIOC_GETPRETIMEOUT:
		err = put_user(wdd->preसमयout, p);
		अवरोध;
	शेष:
		err = -ENOTTY;
		अवरोध;
	पूर्ण

out_ioctl:
	mutex_unlock(&wd_data->lock);
	वापस err;
पूर्ण

/*
 *	watchकरोg_खोलो: खोलो the /dev/watchकरोg* devices.
 *	@inode: inode of device
 *	@file: file handle to device
 *
 *	When the /dev/watchकरोg* device माला_लो खोलोed, we start the watchकरोg.
 *	Watch out: the /dev/watchकरोg device is single खोलो, so we make sure
 *	it can only be खोलोed once.
 */

अटल पूर्णांक watchकरोg_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा watchकरोg_core_data *wd_data;
	काष्ठा watchकरोg_device *wdd;
	bool hw_running;
	पूर्णांक err;

	/* Get the corresponding watchकरोg device */
	अगर (imajor(inode) == MISC_MAJOR)
		wd_data = old_wd_data;
	अन्यथा
		wd_data = container_of(inode->i_cdev, काष्ठा watchकरोg_core_data,
				       cdev);

	/* the watchकरोg is single खोलो! */
	अगर (test_and_set_bit(_WDOG_DEV_OPEN, &wd_data->status))
		वापस -EBUSY;

	wdd = wd_data->wdd;

	/*
	 * If the /dev/watchकरोg device is खोलो, we करोn't want the module
	 * to be unloaded.
	 */
	hw_running = watchकरोg_hw_running(wdd);
	अगर (!hw_running && !try_module_get(wdd->ops->owner)) अणु
		err = -EBUSY;
		जाओ out_clear;
	पूर्ण

	err = watchकरोg_start(wdd);
	अगर (err < 0)
		जाओ out_mod;

	file->निजी_data = wd_data;

	अगर (!hw_running)
		get_device(&wd_data->dev);

	/*
	 * खोलो_समयout only applies क्रम the first खोलो from
	 * userspace. Set खोलो_deadline to infinity so that the kernel
	 * will take care of an always-running hardware watchकरोg in
	 * हाल the device माला_लो magic-बंदd or WDIOS_DISABLECARD is
	 * applied.
	 */
	wd_data->खोलो_deadline = KTIME_MAX;

	/* dev/watchकरोg is a भव (and thus non-seekable) fileप्रणाली */
	वापस stream_खोलो(inode, file);

out_mod:
	module_put(wd_data->wdd->ops->owner);
out_clear:
	clear_bit(_WDOG_DEV_OPEN, &wd_data->status);
	वापस err;
पूर्ण

अटल व्योम watchकरोg_core_data_release(काष्ठा device *dev)
अणु
	काष्ठा watchकरोg_core_data *wd_data;

	wd_data = container_of(dev, काष्ठा watchकरोg_core_data, dev);

	kमुक्त(wd_data);
पूर्ण

/*
 *	watchकरोg_release: release the watchकरोg device.
 *	@inode: inode of device
 *	@file: file handle to device
 *
 *	This is the code क्रम when /dev/watchकरोg माला_लो बंदd. We will only
 *	stop the watchकरोg when we have received the magic अक्षर (and nowayout
 *	was not set), अन्यथा the watchकरोg will keep running.
 */

अटल पूर्णांक watchकरोg_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा watchकरोg_core_data *wd_data = file->निजी_data;
	काष्ठा watchकरोg_device *wdd;
	पूर्णांक err = -EBUSY;
	bool running;

	mutex_lock(&wd_data->lock);

	wdd = wd_data->wdd;
	अगर (!wdd)
		जाओ करोne;

	/*
	 * We only stop the watchकरोg अगर we received the magic अक्षरacter
	 * or अगर WDIOF_MAGICCLOSE is not set. If nowayout was set then
	 * watchकरोg_stop will fail.
	 */
	अगर (!watchकरोg_active(wdd))
		err = 0;
	अन्यथा अगर (test_and_clear_bit(_WDOG_ALLOW_RELEASE, &wd_data->status) ||
		 !(wdd->info->options & WDIOF_MAGICCLOSE))
		err = watchकरोg_stop(wdd);

	/* If the watchकरोg was not stopped, send a keepalive ping */
	अगर (err < 0) अणु
		pr_crit("watchdog%d: watchdog did not stop!\n", wdd->id);
		watchकरोg_ping(wdd);
	पूर्ण

	watchकरोg_update_worker(wdd);

	/* make sure that /dev/watchकरोg can be re-खोलोed */
	clear_bit(_WDOG_DEV_OPEN, &wd_data->status);

करोne:
	running = wdd && watchकरोg_hw_running(wdd);
	mutex_unlock(&wd_data->lock);
	/*
	 * Allow the owner module to be unloaded again unless the watchकरोg
	 * is still running. If the watchकरोg is still running, it can not
	 * be stopped, and its driver must not be unloaded.
	 */
	अगर (!running) अणु
		module_put(wd_data->cdev.owner);
		put_device(&wd_data->dev);
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations watchकरोg_fops = अणु
	.owner		= THIS_MODULE,
	.ग_लिखो		= watchकरोg_ग_लिखो,
	.unlocked_ioctl	= watchकरोg_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.खोलो		= watchकरोg_खोलो,
	.release	= watchकरोg_release,
पूर्ण;

अटल काष्ठा miscdevice watchकरोg_miscdev = अणु
	.minor		= WATCHDOG_MINOR,
	.name		= "watchdog",
	.fops		= &watchकरोg_fops,
पूर्ण;

अटल काष्ठा class watchकरोg_class = अणु
	.name =		"watchdog",
	.owner =	THIS_MODULE,
	.dev_groups =	wdt_groups,
पूर्ण;

/*
 *	watchकरोg_cdev_रेजिस्टर: रेजिस्टर watchकरोg अक्षरacter device
 *	@wdd: watchकरोg device
 *
 *	Register a watchकरोg अक्षरacter device including handling the legacy
 *	/dev/watchकरोg node. /dev/watchकरोg is actually a miscdevice and
 *	thus we set it up like that.
 */

अटल पूर्णांक watchकरोg_cdev_रेजिस्टर(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा watchकरोg_core_data *wd_data;
	पूर्णांक err;

	wd_data = kzalloc(माप(काष्ठा watchकरोg_core_data), GFP_KERNEL);
	अगर (!wd_data)
		वापस -ENOMEM;
	mutex_init(&wd_data->lock);

	wd_data->wdd = wdd;
	wdd->wd_data = wd_data;

	अगर (IS_ERR_OR_शून्य(watchकरोg_kworker)) अणु
		kमुक्त(wd_data);
		वापस -ENODEV;
	पूर्ण

	device_initialize(&wd_data->dev);
	wd_data->dev.devt = MKDEV(MAJOR(watchकरोg_devt), wdd->id);
	wd_data->dev.class = &watchकरोg_class;
	wd_data->dev.parent = wdd->parent;
	wd_data->dev.groups = wdd->groups;
	wd_data->dev.release = watchकरोg_core_data_release;
	dev_set_drvdata(&wd_data->dev, wdd);
	dev_set_name(&wd_data->dev, "watchdog%d", wdd->id);

	kthपढ़ो_init_work(&wd_data->work, watchकरोg_ping_work);
	hrसमयr_init(&wd_data->समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL_HARD);
	wd_data->समयr.function = watchकरोg_समयr_expired;

	अगर (wdd->id == 0) अणु
		old_wd_data = wd_data;
		watchकरोg_miscdev.parent = wdd->parent;
		err = misc_रेजिस्टर(&watchकरोg_miscdev);
		अगर (err != 0) अणु
			pr_err("%s: cannot register miscdev on minor=%d (err=%d).\n",
				wdd->info->identity, WATCHDOG_MINOR, err);
			अगर (err == -EBUSY)
				pr_err("%s: a legacy watchdog module is probably present.\n",
					wdd->info->identity);
			old_wd_data = शून्य;
			put_device(&wd_data->dev);
			वापस err;
		पूर्ण
	पूर्ण

	/* Fill in the data काष्ठाures */
	cdev_init(&wd_data->cdev, &watchकरोg_fops);

	/* Add the device */
	err = cdev_device_add(&wd_data->cdev, &wd_data->dev);
	अगर (err) अणु
		pr_err("watchdog%d unable to add device %d:%d\n",
			wdd->id,  MAJOR(watchकरोg_devt), wdd->id);
		अगर (wdd->id == 0) अणु
			misc_deरेजिस्टर(&watchकरोg_miscdev);
			old_wd_data = शून्य;
			put_device(&wd_data->dev);
		पूर्ण
		वापस err;
	पूर्ण

	wd_data->cdev.owner = wdd->ops->owner;

	/* Record समय of most recent heartbeat as 'just before now'. */
	wd_data->last_hw_keepalive = kसमय_sub(kसमय_get(), 1);
	watchकरोg_set_खोलो_deadline(wd_data);

	/*
	 * If the watchकरोg is running, prevent its driver from being unloaded,
	 * and schedule an immediate ping.
	 */
	अगर (watchकरोg_hw_running(wdd)) अणु
		__module_get(wdd->ops->owner);
		get_device(&wd_data->dev);
		अगर (handle_boot_enabled)
			hrसमयr_start(&wd_data->समयr, 0,
				      HRTIMER_MODE_REL_HARD);
		अन्यथा
			pr_info("watchdog%d running and kernel based pre-userspace handler disabled\n",
				wdd->id);
	पूर्ण

	वापस 0;
पूर्ण

/*
 *	watchकरोg_cdev_unरेजिस्टर: unरेजिस्टर watchकरोg अक्षरacter device
 *	@watchकरोg: watchकरोg device
 *
 *	Unरेजिस्टर watchकरोg अक्षरacter device and अगर needed the legacy
 *	/dev/watchकरोg device.
 */

अटल व्योम watchकरोg_cdev_unरेजिस्टर(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा watchकरोg_core_data *wd_data = wdd->wd_data;

	cdev_device_del(&wd_data->cdev, &wd_data->dev);
	अगर (wdd->id == 0) अणु
		misc_deरेजिस्टर(&watchकरोg_miscdev);
		old_wd_data = शून्य;
	पूर्ण

	अगर (watchकरोg_active(wdd) &&
	    test_bit(WDOG_STOP_ON_UNREGISTER, &wdd->status)) अणु
		watchकरोg_stop(wdd);
	पूर्ण

	mutex_lock(&wd_data->lock);
	wd_data->wdd = शून्य;
	wdd->wd_data = शून्य;
	mutex_unlock(&wd_data->lock);

	hrसमयr_cancel(&wd_data->समयr);
	kthपढ़ो_cancel_work_sync(&wd_data->work);

	put_device(&wd_data->dev);
पूर्ण

/*
 *	watchकरोg_dev_रेजिस्टर: रेजिस्टर a watchकरोg device
 *	@wdd: watchकरोg device
 *
 *	Register a watchकरोg device including handling the legacy
 *	/dev/watchकरोg node. /dev/watchकरोg is actually a miscdevice and
 *	thus we set it up like that.
 */

पूर्णांक watchकरोg_dev_रेजिस्टर(काष्ठा watchकरोg_device *wdd)
अणु
	पूर्णांक ret;

	ret = watchकरोg_cdev_रेजिस्टर(wdd);
	अगर (ret)
		वापस ret;

	ret = watchकरोg_रेजिस्टर_preसमयout(wdd);
	अगर (ret)
		watchकरोg_cdev_unरेजिस्टर(wdd);

	वापस ret;
पूर्ण

/*
 *	watchकरोg_dev_unरेजिस्टर: unरेजिस्टर a watchकरोg device
 *	@watchकरोg: watchकरोg device
 *
 *	Unरेजिस्टर watchकरोg device and अगर needed the legacy
 *	/dev/watchकरोg device.
 */

व्योम watchकरोg_dev_unरेजिस्टर(काष्ठा watchकरोg_device *wdd)
अणु
	watchकरोg_unरेजिस्टर_preसमयout(wdd);
	watchकरोg_cdev_unरेजिस्टर(wdd);
पूर्ण

/*
 *	watchकरोg_set_last_hw_keepalive: set last HW keepalive समय क्रम watchकरोg
 *	@wdd: watchकरोg device
 *	@last_ping_ms: समय since last HW heartbeat
 *
 *	Adjusts the last known HW keepalive समय क्रम a watchकरोg समयr.
 *	This is needed अगर the watchकरोg is alपढ़ोy running when the probe
 *	function is called, and it can't be pinged immediately. This
 *	function must be called immediately after watchकरोg registration,
 *	and min_hw_heartbeat_ms must be set क्रम this to be useful.
 */
पूर्णांक watchकरोg_set_last_hw_keepalive(काष्ठा watchकरोg_device *wdd,
				   अचिन्हित पूर्णांक last_ping_ms)
अणु
	काष्ठा watchकरोg_core_data *wd_data;
	kसमय_प्रकार now;

	अगर (!wdd)
		वापस -EINVAL;

	wd_data = wdd->wd_data;

	now = kसमय_get();

	wd_data->last_hw_keepalive = kसमय_sub(now, ms_to_kसमय(last_ping_ms));

	वापस __watchकरोg_ping(wdd);
पूर्ण
EXPORT_SYMBOL_GPL(watchकरोg_set_last_hw_keepalive);

/*
 *	watchकरोg_dev_init: init dev part of watchकरोg core
 *
 *	Allocate a range of अक्षरdev nodes to use क्रम watchकरोg devices
 */

पूर्णांक __init watchकरोg_dev_init(व्योम)
अणु
	पूर्णांक err;

	watchकरोg_kworker = kthपढ़ो_create_worker(0, "watchdogd");
	अगर (IS_ERR(watchकरोg_kworker)) अणु
		pr_err("Failed to create watchdog kworker\n");
		वापस PTR_ERR(watchकरोg_kworker);
	पूर्ण
	sched_set_fअगरo(watchकरोg_kworker->task);

	err = class_रेजिस्टर(&watchकरोg_class);
	अगर (err < 0) अणु
		pr_err("couldn't register class\n");
		जाओ err_रेजिस्टर;
	पूर्ण

	err = alloc_chrdev_region(&watchकरोg_devt, 0, MAX_DOGS, "watchdog");
	अगर (err < 0) अणु
		pr_err("watchdog: unable to allocate char dev region\n");
		जाओ err_alloc;
	पूर्ण

	वापस 0;

err_alloc:
	class_unरेजिस्टर(&watchकरोg_class);
err_रेजिस्टर:
	kthपढ़ो_destroy_worker(watchकरोg_kworker);
	वापस err;
पूर्ण

/*
 *	watchकरोg_dev_निकास: निकास dev part of watchकरोg core
 *
 *	Release the range of अक्षरdev nodes used क्रम watchकरोg devices
 */

व्योम __निकास watchकरोg_dev_निकास(व्योम)
अणु
	unरेजिस्टर_chrdev_region(watchकरोg_devt, MAX_DOGS);
	class_unरेजिस्टर(&watchकरोg_class);
	kthपढ़ो_destroy_worker(watchकरोg_kworker);
पूर्ण

module_param(handle_boot_enabled, bool, 0444);
MODULE_PARM_DESC(handle_boot_enabled,
	"Watchdog core auto-updates boot enabled watchdogs before userspace takes over (default="
	__MODULE_STRING(IS_ENABLED(CONFIG_WATCHDOG_HANDLE_BOOT_ENABLED)) ")");

module_param(खोलो_समयout, uपूर्णांक, 0644);
MODULE_PARM_DESC(खोलो_समयout,
	"Maximum time (in seconds, 0 means infinity) for userspace to take over a running watchdog (default="
	__MODULE_STRING(CONFIG_WATCHDOG_OPEN_TIMEOUT) ")");
