<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * devfreq: Generic Dynamic Voltage and Frequency Scaling (DVFS) Framework
 *	    क्रम Non-CPU Devices.
 *
 * Copyright (C) 2011 Samsung Electronics
 *	MyungJoo Ham <myungjoo.ham@samsung.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/kmod.h>
#समावेश <linux/sched.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/devfreq_cooling.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/pm_opp.h>
#समावेश <linux/devfreq.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/list.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/of.h>
#समावेश <linux/pm_qos.h>
#समावेश "governor.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/devfreq.h>

#घोषणा IS_SUPPORTED_FLAG(f, name) ((f & DEVFREQ_GOV_FLAG_##name) ? true : false)
#घोषणा IS_SUPPORTED_ATTR(f, name) ((f & DEVFREQ_GOV_ATTR_##name) ? true : false)
#घोषणा HZ_PER_KHZ	1000

अटल काष्ठा class *devfreq_class;
अटल काष्ठा dentry *devfreq_debugfs;

/*
 * devfreq core provides delayed work based load monitoring helper
 * functions. Governors can use these or can implement their own
 * monitoring mechanism.
 */
अटल काष्ठा workqueue_काष्ठा *devfreq_wq;

/* The list of all device-devfreq governors */
अटल LIST_HEAD(devfreq_governor_list);
/* The list of all device-devfreq */
अटल LIST_HEAD(devfreq_list);
अटल DEFINE_MUTEX(devfreq_list_lock);

अटल स्थिर अक्षर समयr_name[][DEVFREQ_NAME_LEN] = अणु
	[DEVFREQ_TIMER_DEFERRABLE] = अणु "deferrable" पूर्ण,
	[DEVFREQ_TIMER_DELAYED] = अणु "delayed" पूर्ण,
पूर्ण;

/**
 * find_device_devfreq() - find devfreq काष्ठा using device poपूर्णांकer
 * @dev:	device poपूर्णांकer used to lookup device devfreq.
 *
 * Search the list of device devfreqs and वापस the matched device's
 * devfreq info. devfreq_list_lock should be held by the caller.
 */
अटल काष्ठा devfreq *find_device_devfreq(काष्ठा device *dev)
अणु
	काष्ठा devfreq *पंचांगp_devfreq;

	lockdep_निश्चित_held(&devfreq_list_lock);

	अगर (IS_ERR_OR_शून्य(dev)) अणु
		pr_err("DEVFREQ: %s: Invalid parameters\n", __func__);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	list_क्रम_each_entry(पंचांगp_devfreq, &devfreq_list, node) अणु
		अगर (पंचांगp_devfreq->dev.parent == dev)
			वापस पंचांगp_devfreq;
	पूर्ण

	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अचिन्हित दीर्घ find_available_min_freq(काष्ठा devfreq *devfreq)
अणु
	काष्ठा dev_pm_opp *opp;
	अचिन्हित दीर्घ min_freq = 0;

	opp = dev_pm_opp_find_freq_उच्चमान(devfreq->dev.parent, &min_freq);
	अगर (IS_ERR(opp))
		min_freq = 0;
	अन्यथा
		dev_pm_opp_put(opp);

	वापस min_freq;
पूर्ण

अटल अचिन्हित दीर्घ find_available_max_freq(काष्ठा devfreq *devfreq)
अणु
	काष्ठा dev_pm_opp *opp;
	अचिन्हित दीर्घ max_freq = अच_दीर्घ_उच्च;

	opp = dev_pm_opp_find_freq_न्यूनमान(devfreq->dev.parent, &max_freq);
	अगर (IS_ERR(opp))
		max_freq = 0;
	अन्यथा
		dev_pm_opp_put(opp);

	वापस max_freq;
पूर्ण

/**
 * get_freq_range() - Get the current freq range
 * @devfreq:	the devfreq instance
 * @min_freq:	the min frequency
 * @max_freq:	the max frequency
 *
 * This takes पूर्णांकo consideration all स्थिरraपूर्णांकs.
 */
अटल व्योम get_freq_range(काष्ठा devfreq *devfreq,
			   अचिन्हित दीर्घ *min_freq,
			   अचिन्हित दीर्घ *max_freq)
अणु
	अचिन्हित दीर्घ *freq_table = devfreq->profile->freq_table;
	s32 qos_min_freq, qos_max_freq;

	lockdep_निश्चित_held(&devfreq->lock);

	/*
	 * Initialize minimum/maximum frequency from freq table.
	 * The devfreq drivers can initialize this in either ascending or
	 * descending order and devfreq core supports both.
	 */
	अगर (freq_table[0] < freq_table[devfreq->profile->max_state - 1]) अणु
		*min_freq = freq_table[0];
		*max_freq = freq_table[devfreq->profile->max_state - 1];
	पूर्ण अन्यथा अणु
		*min_freq = freq_table[devfreq->profile->max_state - 1];
		*max_freq = freq_table[0];
	पूर्ण

	/* Apply स्थिरraपूर्णांकs from PM QoS */
	qos_min_freq = dev_pm_qos_पढ़ो_value(devfreq->dev.parent,
					     DEV_PM_QOS_MIN_FREQUENCY);
	qos_max_freq = dev_pm_qos_पढ़ो_value(devfreq->dev.parent,
					     DEV_PM_QOS_MAX_FREQUENCY);
	*min_freq = max(*min_freq, (अचिन्हित दीर्घ)HZ_PER_KHZ * qos_min_freq);
	अगर (qos_max_freq != PM_QOS_MAX_FREQUENCY_DEFAULT_VALUE)
		*max_freq = min(*max_freq,
				(अचिन्हित दीर्घ)HZ_PER_KHZ * qos_max_freq);

	/* Apply स्थिरraपूर्णांकs from OPP पूर्णांकerface */
	*min_freq = max(*min_freq, devfreq->scaling_min_freq);
	*max_freq = min(*max_freq, devfreq->scaling_max_freq);

	अगर (*min_freq > *max_freq)
		*min_freq = *max_freq;
पूर्ण

/**
 * devfreq_get_freq_level() - Lookup freq_table क्रम the frequency
 * @devfreq:	the devfreq instance
 * @freq:	the target frequency
 */
अटल पूर्णांक devfreq_get_freq_level(काष्ठा devfreq *devfreq, अचिन्हित दीर्घ freq)
अणु
	पूर्णांक lev;

	क्रम (lev = 0; lev < devfreq->profile->max_state; lev++)
		अगर (freq == devfreq->profile->freq_table[lev])
			वापस lev;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक set_freq_table(काष्ठा devfreq *devfreq)
अणु
	काष्ठा devfreq_dev_profile *profile = devfreq->profile;
	काष्ठा dev_pm_opp *opp;
	अचिन्हित दीर्घ freq;
	पूर्णांक i, count;

	/* Initialize the freq_table from OPP table */
	count = dev_pm_opp_get_opp_count(devfreq->dev.parent);
	अगर (count <= 0)
		वापस -EINVAL;

	profile->max_state = count;
	profile->freq_table = devm_kसुस्मृति(devfreq->dev.parent,
					profile->max_state,
					माप(*profile->freq_table),
					GFP_KERNEL);
	अगर (!profile->freq_table) अणु
		profile->max_state = 0;
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0, freq = 0; i < profile->max_state; i++, freq++) अणु
		opp = dev_pm_opp_find_freq_उच्चमान(devfreq->dev.parent, &freq);
		अगर (IS_ERR(opp)) अणु
			devm_kमुक्त(devfreq->dev.parent, profile->freq_table);
			profile->max_state = 0;
			वापस PTR_ERR(opp);
		पूर्ण
		dev_pm_opp_put(opp);
		profile->freq_table[i] = freq;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * devfreq_update_status() - Update statistics of devfreq behavior
 * @devfreq:	the devfreq instance
 * @freq:	the update target frequency
 */
पूर्णांक devfreq_update_status(काष्ठा devfreq *devfreq, अचिन्हित दीर्घ freq)
अणु
	पूर्णांक lev, prev_lev, ret = 0;
	u64 cur_समय;

	lockdep_निश्चित_held(&devfreq->lock);
	cur_समय = get_jअगरfies_64();

	/* Immediately निकास अगर previous_freq is not initialized yet. */
	अगर (!devfreq->previous_freq)
		जाओ out;

	prev_lev = devfreq_get_freq_level(devfreq, devfreq->previous_freq);
	अगर (prev_lev < 0) अणु
		ret = prev_lev;
		जाओ out;
	पूर्ण

	devfreq->stats.समय_in_state[prev_lev] +=
			cur_समय - devfreq->stats.last_update;

	lev = devfreq_get_freq_level(devfreq, freq);
	अगर (lev < 0) अणु
		ret = lev;
		जाओ out;
	पूर्ण

	अगर (lev != prev_lev) अणु
		devfreq->stats.trans_table[
			(prev_lev * devfreq->profile->max_state) + lev]++;
		devfreq->stats.total_trans++;
	पूर्ण

out:
	devfreq->stats.last_update = cur_समय;
	वापस ret;
पूर्ण
EXPORT_SYMBOL(devfreq_update_status);

/**
 * find_devfreq_governor() - find devfreq governor from name
 * @name:	name of the governor
 *
 * Search the list of devfreq governors and वापस the matched
 * governor's poपूर्णांकer. devfreq_list_lock should be held by the caller.
 */
अटल काष्ठा devfreq_governor *find_devfreq_governor(स्थिर अक्षर *name)
अणु
	काष्ठा devfreq_governor *पंचांगp_governor;

	lockdep_निश्चित_held(&devfreq_list_lock);

	अगर (IS_ERR_OR_शून्य(name)) अणु
		pr_err("DEVFREQ: %s: Invalid parameters\n", __func__);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	list_क्रम_each_entry(पंचांगp_governor, &devfreq_governor_list, node) अणु
		अगर (!म_भेदन(पंचांगp_governor->name, name, DEVFREQ_NAME_LEN))
			वापस पंचांगp_governor;
	पूर्ण

	वापस ERR_PTR(-ENODEV);
पूर्ण

/**
 * try_then_request_governor() - Try to find the governor and request the
 *                               module अगर is not found.
 * @name:	name of the governor
 *
 * Search the list of devfreq governors and request the module and try again
 * अगर is not found. This can happen when both drivers (the governor driver
 * and the driver that call devfreq_add_device) are built as modules.
 * devfreq_list_lock should be held by the caller. Returns the matched
 * governor's poपूर्णांकer or an error poपूर्णांकer.
 */
अटल काष्ठा devfreq_governor *try_then_request_governor(स्थिर अक्षर *name)
अणु
	काष्ठा devfreq_governor *governor;
	पूर्णांक err = 0;

	lockdep_निश्चित_held(&devfreq_list_lock);

	अगर (IS_ERR_OR_शून्य(name)) अणु
		pr_err("DEVFREQ: %s: Invalid parameters\n", __func__);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	governor = find_devfreq_governor(name);
	अगर (IS_ERR(governor)) अणु
		mutex_unlock(&devfreq_list_lock);

		अगर (!म_भेदन(name, DEVFREQ_GOV_SIMPLE_ONDEMAND,
			     DEVFREQ_NAME_LEN))
			err = request_module("governor_%s", "simpleondemand");
		अन्यथा
			err = request_module("governor_%s", name);
		/* Restore previous state beक्रमe वापस */
		mutex_lock(&devfreq_list_lock);
		अगर (err)
			वापस (err < 0) ? ERR_PTR(err) : ERR_PTR(-EINVAL);

		governor = find_devfreq_governor(name);
	पूर्ण

	वापस governor;
पूर्ण

अटल पूर्णांक devfreq_notअगरy_transition(काष्ठा devfreq *devfreq,
		काष्ठा devfreq_freqs *freqs, अचिन्हित पूर्णांक state)
अणु
	अगर (!devfreq)
		वापस -EINVAL;

	चयन (state) अणु
	हाल DEVFREQ_PRECHANGE:
		srcu_notअगरier_call_chain(&devfreq->transition_notअगरier_list,
				DEVFREQ_PRECHANGE, freqs);
		अवरोध;

	हाल DEVFREQ_POSTCHANGE:
		srcu_notअगरier_call_chain(&devfreq->transition_notअगरier_list,
				DEVFREQ_POSTCHANGE, freqs);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक devfreq_set_target(काष्ठा devfreq *devfreq, अचिन्हित दीर्घ new_freq,
			      u32 flags)
अणु
	काष्ठा devfreq_freqs freqs;
	अचिन्हित दीर्घ cur_freq;
	पूर्णांक err = 0;

	अगर (devfreq->profile->get_cur_freq)
		devfreq->profile->get_cur_freq(devfreq->dev.parent, &cur_freq);
	अन्यथा
		cur_freq = devfreq->previous_freq;

	freqs.old = cur_freq;
	freqs.new = new_freq;
	devfreq_notअगरy_transition(devfreq, &freqs, DEVFREQ_PRECHANGE);

	err = devfreq->profile->target(devfreq->dev.parent, &new_freq, flags);
	अगर (err) अणु
		freqs.new = cur_freq;
		devfreq_notअगरy_transition(devfreq, &freqs, DEVFREQ_POSTCHANGE);
		वापस err;
	पूर्ण

	/*
	 * Prपूर्णांक devfreq_frequency trace inक्रमmation between DEVFREQ_PRECHANGE
	 * and DEVFREQ_POSTCHANGE because क्रम showing the correct frequency
	 * change order of between devfreq device and passive devfreq device.
	 */
	अगर (trace_devfreq_frequency_enabled() && new_freq != cur_freq)
		trace_devfreq_frequency(devfreq, new_freq, cur_freq);

	freqs.new = new_freq;
	devfreq_notअगरy_transition(devfreq, &freqs, DEVFREQ_POSTCHANGE);

	अगर (devfreq_update_status(devfreq, new_freq))
		dev_err(&devfreq->dev,
			"Couldn't update frequency transition information.\n");

	devfreq->previous_freq = new_freq;

	अगर (devfreq->suspend_freq)
		devfreq->resume_freq = new_freq;

	वापस err;
पूर्ण

/**
 * devfreq_update_target() - Reevaluate the device and configure frequency
 *			   on the final stage.
 * @devfreq:	the devfreq instance.
 * @freq:	the new frequency of parent device. This argument
 *		is only used क्रम devfreq device using passive governor.
 *
 * Note: Lock devfreq->lock beक्रमe calling devfreq_update_target. This function
 *	 should be only used by both update_devfreq() and devfreq governors.
 */
पूर्णांक devfreq_update_target(काष्ठा devfreq *devfreq, अचिन्हित दीर्घ freq)
अणु
	अचिन्हित दीर्घ min_freq, max_freq;
	पूर्णांक err = 0;
	u32 flags = 0;

	lockdep_निश्चित_held(&devfreq->lock);

	अगर (!devfreq->governor)
		वापस -EINVAL;

	/* Reevaluate the proper frequency */
	err = devfreq->governor->get_target_freq(devfreq, &freq);
	अगर (err)
		वापस err;
	get_freq_range(devfreq, &min_freq, &max_freq);

	अगर (freq < min_freq) अणु
		freq = min_freq;
		flags &= ~DEVFREQ_FLAG_LEAST_UPPER_BOUND; /* Use GLB */
	पूर्ण
	अगर (freq > max_freq) अणु
		freq = max_freq;
		flags |= DEVFREQ_FLAG_LEAST_UPPER_BOUND; /* Use LUB */
	पूर्ण

	वापस devfreq_set_target(devfreq, freq, flags);
पूर्ण
EXPORT_SYMBOL(devfreq_update_target);

/* Load monitoring helper functions क्रम governors use */

/**
 * update_devfreq() - Reevaluate the device and configure frequency.
 * @devfreq:	the devfreq instance.
 *
 * Note: Lock devfreq->lock beक्रमe calling update_devfreq
 *	 This function is exported क्रम governors.
 */
पूर्णांक update_devfreq(काष्ठा devfreq *devfreq)
अणु
	वापस devfreq_update_target(devfreq, 0L);
पूर्ण
EXPORT_SYMBOL(update_devfreq);

/**
 * devfreq_monitor() - Periodically poll devfreq objects.
 * @work:	the work काष्ठा used to run devfreq_monitor periodically.
 *
 */
अटल व्योम devfreq_monitor(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक err;
	काष्ठा devfreq *devfreq = container_of(work,
					काष्ठा devfreq, work.work);

	mutex_lock(&devfreq->lock);
	err = update_devfreq(devfreq);
	अगर (err)
		dev_err(&devfreq->dev, "dvfs failed with (%d) error\n", err);

	queue_delayed_work(devfreq_wq, &devfreq->work,
				msecs_to_jअगरfies(devfreq->profile->polling_ms));
	mutex_unlock(&devfreq->lock);

	trace_devfreq_monitor(devfreq);
पूर्ण

/**
 * devfreq_monitor_start() - Start load monitoring of devfreq instance
 * @devfreq:	the devfreq instance.
 *
 * Helper function क्रम starting devfreq device load monitoring. By
 * शेष delayed work based monitoring is supported. Function
 * to be called from governor in response to DEVFREQ_GOV_START
 * event when device is added to devfreq framework.
 */
व्योम devfreq_monitor_start(काष्ठा devfreq *devfreq)
अणु
	अगर (IS_SUPPORTED_FLAG(devfreq->governor->flags, IRQ_DRIVEN))
		वापस;

	चयन (devfreq->profile->समयr) अणु
	हाल DEVFREQ_TIMER_DEFERRABLE:
		INIT_DEFERRABLE_WORK(&devfreq->work, devfreq_monitor);
		अवरोध;
	हाल DEVFREQ_TIMER_DELAYED:
		INIT_DELAYED_WORK(&devfreq->work, devfreq_monitor);
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (devfreq->profile->polling_ms)
		queue_delayed_work(devfreq_wq, &devfreq->work,
			msecs_to_jअगरfies(devfreq->profile->polling_ms));
पूर्ण
EXPORT_SYMBOL(devfreq_monitor_start);

/**
 * devfreq_monitor_stop() - Stop load monitoring of a devfreq instance
 * @devfreq:	the devfreq instance.
 *
 * Helper function to stop devfreq device load monitoring. Function
 * to be called from governor in response to DEVFREQ_GOV_STOP
 * event when device is हटाओd from devfreq framework.
 */
व्योम devfreq_monitor_stop(काष्ठा devfreq *devfreq)
अणु
	अगर (IS_SUPPORTED_FLAG(devfreq->governor->flags, IRQ_DRIVEN))
		वापस;

	cancel_delayed_work_sync(&devfreq->work);
पूर्ण
EXPORT_SYMBOL(devfreq_monitor_stop);

/**
 * devfreq_monitor_suspend() - Suspend load monitoring of a devfreq instance
 * @devfreq:	the devfreq instance.
 *
 * Helper function to suspend devfreq device load monitoring. Function
 * to be called from governor in response to DEVFREQ_GOV_SUSPEND
 * event or when polling पूर्णांकerval is set to zero.
 *
 * Note: Though this function is same as devfreq_monitor_stop(),
 * पूर्णांकentionally kept separate to provide hooks क्रम collecting
 * transition statistics.
 */
व्योम devfreq_monitor_suspend(काष्ठा devfreq *devfreq)
अणु
	mutex_lock(&devfreq->lock);
	अगर (devfreq->stop_polling) अणु
		mutex_unlock(&devfreq->lock);
		वापस;
	पूर्ण

	devfreq_update_status(devfreq, devfreq->previous_freq);
	devfreq->stop_polling = true;
	mutex_unlock(&devfreq->lock);

	अगर (IS_SUPPORTED_FLAG(devfreq->governor->flags, IRQ_DRIVEN))
		वापस;

	cancel_delayed_work_sync(&devfreq->work);
पूर्ण
EXPORT_SYMBOL(devfreq_monitor_suspend);

/**
 * devfreq_monitor_resume() - Resume load monitoring of a devfreq instance
 * @devfreq:    the devfreq instance.
 *
 * Helper function to resume devfreq device load monitoring. Function
 * to be called from governor in response to DEVFREQ_GOV_RESUME
 * event or when polling पूर्णांकerval is set to non-zero.
 */
व्योम devfreq_monitor_resume(काष्ठा devfreq *devfreq)
अणु
	अचिन्हित दीर्घ freq;

	mutex_lock(&devfreq->lock);

	अगर (IS_SUPPORTED_FLAG(devfreq->governor->flags, IRQ_DRIVEN))
		जाओ out_update;

	अगर (!devfreq->stop_polling)
		जाओ out;

	अगर (!delayed_work_pending(&devfreq->work) &&
			devfreq->profile->polling_ms)
		queue_delayed_work(devfreq_wq, &devfreq->work,
			msecs_to_jअगरfies(devfreq->profile->polling_ms));

out_update:
	devfreq->stats.last_update = get_jअगरfies_64();
	devfreq->stop_polling = false;

	अगर (devfreq->profile->get_cur_freq &&
		!devfreq->profile->get_cur_freq(devfreq->dev.parent, &freq))
		devfreq->previous_freq = freq;

out:
	mutex_unlock(&devfreq->lock);
पूर्ण
EXPORT_SYMBOL(devfreq_monitor_resume);

/**
 * devfreq_update_पूर्णांकerval() - Update device devfreq monitoring पूर्णांकerval
 * @devfreq:    the devfreq instance.
 * @delay:      new polling पूर्णांकerval to be set.
 *
 * Helper function to set new load monitoring polling पूर्णांकerval. Function
 * to be called from governor in response to DEVFREQ_GOV_UPDATE_INTERVAL event.
 */
व्योम devfreq_update_पूर्णांकerval(काष्ठा devfreq *devfreq, अचिन्हित पूर्णांक *delay)
अणु
	अचिन्हित पूर्णांक cur_delay = devfreq->profile->polling_ms;
	अचिन्हित पूर्णांक new_delay = *delay;

	mutex_lock(&devfreq->lock);
	devfreq->profile->polling_ms = new_delay;

	अगर (IS_SUPPORTED_FLAG(devfreq->governor->flags, IRQ_DRIVEN))
		जाओ out;

	अगर (devfreq->stop_polling)
		जाओ out;

	/* अगर new delay is zero, stop polling */
	अगर (!new_delay) अणु
		mutex_unlock(&devfreq->lock);
		cancel_delayed_work_sync(&devfreq->work);
		वापस;
	पूर्ण

	/* अगर current delay is zero, start polling with new delay */
	अगर (!cur_delay) अणु
		queue_delayed_work(devfreq_wq, &devfreq->work,
			msecs_to_jअगरfies(devfreq->profile->polling_ms));
		जाओ out;
	पूर्ण

	/* अगर current delay is greater than new delay, restart polling */
	अगर (cur_delay > new_delay) अणु
		mutex_unlock(&devfreq->lock);
		cancel_delayed_work_sync(&devfreq->work);
		mutex_lock(&devfreq->lock);
		अगर (!devfreq->stop_polling)
			queue_delayed_work(devfreq_wq, &devfreq->work,
				msecs_to_jअगरfies(devfreq->profile->polling_ms));
	पूर्ण
out:
	mutex_unlock(&devfreq->lock);
पूर्ण
EXPORT_SYMBOL(devfreq_update_पूर्णांकerval);

/**
 * devfreq_notअगरier_call() - Notअगरy that the device frequency requirements
 *			     has been changed out of devfreq framework.
 * @nb:		the notअगरier_block (supposed to be devfreq->nb)
 * @type:	not used
 * @devp:	not used
 *
 * Called by a notअगरier that uses devfreq->nb.
 */
अटल पूर्णांक devfreq_notअगरier_call(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ type,
				 व्योम *devp)
अणु
	काष्ठा devfreq *devfreq = container_of(nb, काष्ठा devfreq, nb);
	पूर्णांक err = -EINVAL;

	mutex_lock(&devfreq->lock);

	devfreq->scaling_min_freq = find_available_min_freq(devfreq);
	अगर (!devfreq->scaling_min_freq)
		जाओ out;

	devfreq->scaling_max_freq = find_available_max_freq(devfreq);
	अगर (!devfreq->scaling_max_freq) अणु
		devfreq->scaling_max_freq = अच_दीर्घ_उच्च;
		जाओ out;
	पूर्ण

	err = update_devfreq(devfreq);

out:
	mutex_unlock(&devfreq->lock);
	अगर (err)
		dev_err(devfreq->dev.parent,
			"failed to update frequency from OPP notifier (%d)\n",
			err);

	वापस NOTIFY_OK;
पूर्ण

/**
 * qos_notअगरier_call() - Common handler क्रम QoS स्थिरraपूर्णांकs.
 * @devfreq:    the devfreq instance.
 */
अटल पूर्णांक qos_notअगरier_call(काष्ठा devfreq *devfreq)
अणु
	पूर्णांक err;

	mutex_lock(&devfreq->lock);
	err = update_devfreq(devfreq);
	mutex_unlock(&devfreq->lock);
	अगर (err)
		dev_err(devfreq->dev.parent,
			"failed to update frequency from PM QoS (%d)\n",
			err);

	वापस NOTIFY_OK;
पूर्ण

/**
 * qos_min_notअगरier_call() - Callback क्रम QoS min_freq changes.
 * @nb:		Should be devfreq->nb_min
 */
अटल पूर्णांक qos_min_notअगरier_call(काष्ठा notअगरier_block *nb,
					 अचिन्हित दीर्घ val, व्योम *ptr)
अणु
	वापस qos_notअगरier_call(container_of(nb, काष्ठा devfreq, nb_min));
पूर्ण

/**
 * qos_max_notअगरier_call() - Callback क्रम QoS max_freq changes.
 * @nb:		Should be devfreq->nb_max
 */
अटल पूर्णांक qos_max_notअगरier_call(काष्ठा notअगरier_block *nb,
					 अचिन्हित दीर्घ val, व्योम *ptr)
अणु
	वापस qos_notअगरier_call(container_of(nb, काष्ठा devfreq, nb_max));
पूर्ण

/**
 * devfreq_dev_release() - Callback क्रम काष्ठा device to release the device.
 * @dev:	the devfreq device
 *
 * Remove devfreq from the list and release its resources.
 */
अटल व्योम devfreq_dev_release(काष्ठा device *dev)
अणु
	काष्ठा devfreq *devfreq = to_devfreq(dev);
	पूर्णांक err;

	mutex_lock(&devfreq_list_lock);
	list_del(&devfreq->node);
	mutex_unlock(&devfreq_list_lock);

	err = dev_pm_qos_हटाओ_notअगरier(devfreq->dev.parent, &devfreq->nb_max,
					 DEV_PM_QOS_MAX_FREQUENCY);
	अगर (err && err != -ENOENT)
		dev_warn(dev->parent,
			"Failed to remove max_freq notifier: %d\n", err);
	err = dev_pm_qos_हटाओ_notअगरier(devfreq->dev.parent, &devfreq->nb_min,
					 DEV_PM_QOS_MIN_FREQUENCY);
	अगर (err && err != -ENOENT)
		dev_warn(dev->parent,
			"Failed to remove min_freq notifier: %d\n", err);

	अगर (dev_pm_qos_request_active(&devfreq->user_max_freq_req)) अणु
		err = dev_pm_qos_हटाओ_request(&devfreq->user_max_freq_req);
		अगर (err < 0)
			dev_warn(dev->parent,
				"Failed to remove max_freq request: %d\n", err);
	पूर्ण
	अगर (dev_pm_qos_request_active(&devfreq->user_min_freq_req)) अणु
		err = dev_pm_qos_हटाओ_request(&devfreq->user_min_freq_req);
		अगर (err < 0)
			dev_warn(dev->parent,
				"Failed to remove min_freq request: %d\n", err);
	पूर्ण

	अगर (devfreq->profile->निकास)
		devfreq->profile->निकास(devfreq->dev.parent);

	अगर (devfreq->opp_table)
		dev_pm_opp_put_opp_table(devfreq->opp_table);

	mutex_destroy(&devfreq->lock);
	kमुक्त(devfreq);
पूर्ण

अटल व्योम create_sysfs_files(काष्ठा devfreq *devfreq,
				स्थिर काष्ठा devfreq_governor *gov);
अटल व्योम हटाओ_sysfs_files(काष्ठा devfreq *devfreq,
				स्थिर काष्ठा devfreq_governor *gov);

/**
 * devfreq_add_device() - Add devfreq feature to the device
 * @dev:	the device to add devfreq feature.
 * @profile:	device-specअगरic profile to run devfreq.
 * @governor_name:	name of the policy to choose frequency.
 * @data:	निजी data क्रम the governor. The devfreq framework करोes not
 *		touch this value.
 */
काष्ठा devfreq *devfreq_add_device(काष्ठा device *dev,
				   काष्ठा devfreq_dev_profile *profile,
				   स्थिर अक्षर *governor_name,
				   व्योम *data)
अणु
	काष्ठा devfreq *devfreq;
	काष्ठा devfreq_governor *governor;
	पूर्णांक err = 0;

	अगर (!dev || !profile || !governor_name) अणु
		dev_err(dev, "%s: Invalid parameters.\n", __func__);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	mutex_lock(&devfreq_list_lock);
	devfreq = find_device_devfreq(dev);
	mutex_unlock(&devfreq_list_lock);
	अगर (!IS_ERR(devfreq)) अणु
		dev_err(dev, "%s: devfreq device already exists!\n",
			__func__);
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	devfreq = kzalloc(माप(काष्ठा devfreq), GFP_KERNEL);
	अगर (!devfreq) अणु
		err = -ENOMEM;
		जाओ err_out;
	पूर्ण

	mutex_init(&devfreq->lock);
	mutex_lock(&devfreq->lock);
	devfreq->dev.parent = dev;
	devfreq->dev.class = devfreq_class;
	devfreq->dev.release = devfreq_dev_release;
	INIT_LIST_HEAD(&devfreq->node);
	devfreq->profile = profile;
	devfreq->previous_freq = profile->initial_freq;
	devfreq->last_status.current_frequency = profile->initial_freq;
	devfreq->data = data;
	devfreq->nb.notअगरier_call = devfreq_notअगरier_call;

	अगर (devfreq->profile->समयr < 0
		|| devfreq->profile->समयr >= DEVFREQ_TIMER_NUM) अणु
		mutex_unlock(&devfreq->lock);
		जाओ err_dev;
	पूर्ण

	अगर (!devfreq->profile->max_state && !devfreq->profile->freq_table) अणु
		mutex_unlock(&devfreq->lock);
		err = set_freq_table(devfreq);
		अगर (err < 0)
			जाओ err_dev;
		mutex_lock(&devfreq->lock);
	पूर्ण

	devfreq->scaling_min_freq = find_available_min_freq(devfreq);
	अगर (!devfreq->scaling_min_freq) अणु
		mutex_unlock(&devfreq->lock);
		err = -EINVAL;
		जाओ err_dev;
	पूर्ण

	devfreq->scaling_max_freq = find_available_max_freq(devfreq);
	अगर (!devfreq->scaling_max_freq) अणु
		mutex_unlock(&devfreq->lock);
		err = -EINVAL;
		जाओ err_dev;
	पूर्ण

	devfreq->suspend_freq = dev_pm_opp_get_suspend_opp_freq(dev);
	devfreq->opp_table = dev_pm_opp_get_opp_table(dev);
	अगर (IS_ERR(devfreq->opp_table))
		devfreq->opp_table = शून्य;

	atomic_set(&devfreq->suspend_count, 0);

	dev_set_name(&devfreq->dev, "%s", dev_name(dev));
	err = device_रेजिस्टर(&devfreq->dev);
	अगर (err) अणु
		mutex_unlock(&devfreq->lock);
		put_device(&devfreq->dev);
		जाओ err_out;
	पूर्ण

	devfreq->stats.trans_table = devm_kzalloc(&devfreq->dev,
			array3_size(माप(अचिन्हित पूर्णांक),
				    devfreq->profile->max_state,
				    devfreq->profile->max_state),
			GFP_KERNEL);
	अगर (!devfreq->stats.trans_table) अणु
		mutex_unlock(&devfreq->lock);
		err = -ENOMEM;
		जाओ err_devfreq;
	पूर्ण

	devfreq->stats.समय_in_state = devm_kसुस्मृति(&devfreq->dev,
			devfreq->profile->max_state,
			माप(*devfreq->stats.समय_in_state),
			GFP_KERNEL);
	अगर (!devfreq->stats.समय_in_state) अणु
		mutex_unlock(&devfreq->lock);
		err = -ENOMEM;
		जाओ err_devfreq;
	पूर्ण

	devfreq->stats.total_trans = 0;
	devfreq->stats.last_update = get_jअगरfies_64();

	srcu_init_notअगरier_head(&devfreq->transition_notअगरier_list);

	mutex_unlock(&devfreq->lock);

	err = dev_pm_qos_add_request(dev, &devfreq->user_min_freq_req,
				     DEV_PM_QOS_MIN_FREQUENCY, 0);
	अगर (err < 0)
		जाओ err_devfreq;
	err = dev_pm_qos_add_request(dev, &devfreq->user_max_freq_req,
				     DEV_PM_QOS_MAX_FREQUENCY,
				     PM_QOS_MAX_FREQUENCY_DEFAULT_VALUE);
	अगर (err < 0)
		जाओ err_devfreq;

	devfreq->nb_min.notअगरier_call = qos_min_notअगरier_call;
	err = dev_pm_qos_add_notअगरier(dev, &devfreq->nb_min,
				      DEV_PM_QOS_MIN_FREQUENCY);
	अगर (err)
		जाओ err_devfreq;

	devfreq->nb_max.notअगरier_call = qos_max_notअगरier_call;
	err = dev_pm_qos_add_notअगरier(dev, &devfreq->nb_max,
				      DEV_PM_QOS_MAX_FREQUENCY);
	अगर (err)
		जाओ err_devfreq;

	mutex_lock(&devfreq_list_lock);

	governor = try_then_request_governor(governor_name);
	अगर (IS_ERR(governor)) अणु
		dev_err(dev, "%s: Unable to find governor for the device\n",
			__func__);
		err = PTR_ERR(governor);
		जाओ err_init;
	पूर्ण

	devfreq->governor = governor;
	err = devfreq->governor->event_handler(devfreq, DEVFREQ_GOV_START,
						शून्य);
	अगर (err) अणु
		dev_err(dev, "%s: Unable to start governor for the device\n",
			__func__);
		जाओ err_init;
	पूर्ण
	create_sysfs_files(devfreq, devfreq->governor);

	list_add(&devfreq->node, &devfreq_list);

	mutex_unlock(&devfreq_list_lock);

	अगर (devfreq->profile->is_cooling_device) अणु
		devfreq->cdev = devfreq_cooling_em_रेजिस्टर(devfreq, शून्य);
		अगर (IS_ERR(devfreq->cdev))
			devfreq->cdev = शून्य;
	पूर्ण

	वापस devfreq;

err_init:
	mutex_unlock(&devfreq_list_lock);
err_devfreq:
	devfreq_हटाओ_device(devfreq);
	devfreq = शून्य;
err_dev:
	kमुक्त(devfreq);
err_out:
	वापस ERR_PTR(err);
पूर्ण
EXPORT_SYMBOL(devfreq_add_device);

/**
 * devfreq_हटाओ_device() - Remove devfreq feature from a device.
 * @devfreq:	the devfreq instance to be हटाओd
 *
 * The opposite of devfreq_add_device().
 */
पूर्णांक devfreq_हटाओ_device(काष्ठा devfreq *devfreq)
अणु
	अगर (!devfreq)
		वापस -EINVAL;

	devfreq_cooling_unरेजिस्टर(devfreq->cdev);

	अगर (devfreq->governor) अणु
		devfreq->governor->event_handler(devfreq,
						 DEVFREQ_GOV_STOP, शून्य);
		हटाओ_sysfs_files(devfreq, devfreq->governor);
	पूर्ण

	device_unरेजिस्टर(&devfreq->dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(devfreq_हटाओ_device);

अटल पूर्णांक devm_devfreq_dev_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा devfreq **r = res;

	अगर (WARN_ON(!r || !*r))
		वापस 0;

	वापस *r == data;
पूर्ण

अटल व्योम devm_devfreq_dev_release(काष्ठा device *dev, व्योम *res)
अणु
	devfreq_हटाओ_device(*(काष्ठा devfreq **)res);
पूर्ण

/**
 * devm_devfreq_add_device() - Resource-managed devfreq_add_device()
 * @dev:	the device to add devfreq feature.
 * @profile:	device-specअगरic profile to run devfreq.
 * @governor_name:	name of the policy to choose frequency.
 * @data:	निजी data क्रम the governor. The devfreq framework करोes not
 *		touch this value.
 *
 * This function manages स्वतःmatically the memory of devfreq device using device
 * resource management and simplअगरy the मुक्त operation क्रम memory of devfreq
 * device.
 */
काष्ठा devfreq *devm_devfreq_add_device(काष्ठा device *dev,
					काष्ठा devfreq_dev_profile *profile,
					स्थिर अक्षर *governor_name,
					व्योम *data)
अणु
	काष्ठा devfreq **ptr, *devfreq;

	ptr = devres_alloc(devm_devfreq_dev_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	devfreq = devfreq_add_device(dev, profile, governor_name, data);
	अगर (IS_ERR(devfreq)) अणु
		devres_मुक्त(ptr);
		वापस devfreq;
	पूर्ण

	*ptr = devfreq;
	devres_add(dev, ptr);

	वापस devfreq;
पूर्ण
EXPORT_SYMBOL(devm_devfreq_add_device);

#अगर_घोषित CONFIG_OF
/*
 * devfreq_get_devfreq_by_node - Get the devfreq device from devicetree
 * @node - poपूर्णांकer to device_node
 *
 * वापस the instance of devfreq device
 */
काष्ठा devfreq *devfreq_get_devfreq_by_node(काष्ठा device_node *node)
अणु
	काष्ठा devfreq *devfreq;

	अगर (!node)
		वापस ERR_PTR(-EINVAL);

	mutex_lock(&devfreq_list_lock);
	list_क्रम_each_entry(devfreq, &devfreq_list, node) अणु
		अगर (devfreq->dev.parent
			&& devfreq->dev.parent->of_node == node) अणु
			mutex_unlock(&devfreq_list_lock);
			वापस devfreq;
		पूर्ण
	पूर्ण
	mutex_unlock(&devfreq_list_lock);

	वापस ERR_PTR(-ENODEV);
पूर्ण

/*
 * devfreq_get_devfreq_by_phandle - Get the devfreq device from devicetree
 * @dev - instance to the given device
 * @phandle_name - name of property holding a phandle value
 * @index - index पूर्णांकo list of devfreq
 *
 * वापस the instance of devfreq device
 */
काष्ठा devfreq *devfreq_get_devfreq_by_phandle(काष्ठा device *dev,
					स्थिर अक्षर *phandle_name, पूर्णांक index)
अणु
	काष्ठा device_node *node;
	काष्ठा devfreq *devfreq;

	अगर (!dev || !phandle_name)
		वापस ERR_PTR(-EINVAL);

	अगर (!dev->of_node)
		वापस ERR_PTR(-EINVAL);

	node = of_parse_phandle(dev->of_node, phandle_name, index);
	अगर (!node)
		वापस ERR_PTR(-ENODEV);

	devfreq = devfreq_get_devfreq_by_node(node);
	of_node_put(node);

	वापस devfreq;
पूर्ण

#अन्यथा
काष्ठा devfreq *devfreq_get_devfreq_by_node(काष्ठा device_node *node)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

काष्ठा devfreq *devfreq_get_devfreq_by_phandle(काष्ठा device *dev,
					स्थिर अक्षर *phandle_name, पूर्णांक index)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण
#पूर्ण_अगर /* CONFIG_OF */
EXPORT_SYMBOL_GPL(devfreq_get_devfreq_by_node);
EXPORT_SYMBOL_GPL(devfreq_get_devfreq_by_phandle);

/**
 * devm_devfreq_हटाओ_device() - Resource-managed devfreq_हटाओ_device()
 * @dev:	the device from which to हटाओ devfreq feature.
 * @devfreq:	the devfreq instance to be हटाओd
 */
व्योम devm_devfreq_हटाओ_device(काष्ठा device *dev, काष्ठा devfreq *devfreq)
अणु
	WARN_ON(devres_release(dev, devm_devfreq_dev_release,
			       devm_devfreq_dev_match, devfreq));
पूर्ण
EXPORT_SYMBOL(devm_devfreq_हटाओ_device);

/**
 * devfreq_suspend_device() - Suspend devfreq of a device.
 * @devfreq: the devfreq instance to be suspended
 *
 * This function is पूर्णांकended to be called by the pm callbacks
 * (e.g., runसमय_suspend, suspend) of the device driver that
 * holds the devfreq.
 */
पूर्णांक devfreq_suspend_device(काष्ठा devfreq *devfreq)
अणु
	पूर्णांक ret;

	अगर (!devfreq)
		वापस -EINVAL;

	अगर (atomic_inc_वापस(&devfreq->suspend_count) > 1)
		वापस 0;

	अगर (devfreq->governor) अणु
		ret = devfreq->governor->event_handler(devfreq,
					DEVFREQ_GOV_SUSPEND, शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (devfreq->suspend_freq) अणु
		mutex_lock(&devfreq->lock);
		ret = devfreq_set_target(devfreq, devfreq->suspend_freq, 0);
		mutex_unlock(&devfreq->lock);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(devfreq_suspend_device);

/**
 * devfreq_resume_device() - Resume devfreq of a device.
 * @devfreq: the devfreq instance to be resumed
 *
 * This function is पूर्णांकended to be called by the pm callbacks
 * (e.g., runसमय_resume, resume) of the device driver that
 * holds the devfreq.
 */
पूर्णांक devfreq_resume_device(काष्ठा devfreq *devfreq)
अणु
	पूर्णांक ret;

	अगर (!devfreq)
		वापस -EINVAL;

	अगर (atomic_dec_वापस(&devfreq->suspend_count) >= 1)
		वापस 0;

	अगर (devfreq->resume_freq) अणु
		mutex_lock(&devfreq->lock);
		ret = devfreq_set_target(devfreq, devfreq->resume_freq, 0);
		mutex_unlock(&devfreq->lock);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (devfreq->governor) अणु
		ret = devfreq->governor->event_handler(devfreq,
					DEVFREQ_GOV_RESUME, शून्य);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(devfreq_resume_device);

/**
 * devfreq_suspend() - Suspend devfreq governors and devices
 *
 * Called during प्रणाली wide Suspend/Hibernate cycles क्रम suspending governors
 * and devices preserving the state क्रम resume. On some platक्रमms the devfreq
 * device must have precise state (frequency) after resume in order to provide
 * fully operating setup.
 */
व्योम devfreq_suspend(व्योम)
अणु
	काष्ठा devfreq *devfreq;
	पूर्णांक ret;

	mutex_lock(&devfreq_list_lock);
	list_क्रम_each_entry(devfreq, &devfreq_list, node) अणु
		ret = devfreq_suspend_device(devfreq);
		अगर (ret)
			dev_err(&devfreq->dev,
				"failed to suspend devfreq device\n");
	पूर्ण
	mutex_unlock(&devfreq_list_lock);
पूर्ण

/**
 * devfreq_resume() - Resume devfreq governors and devices
 *
 * Called during प्रणाली wide Suspend/Hibernate cycle क्रम resuming governors and
 * devices that are suspended with devfreq_suspend().
 */
व्योम devfreq_resume(व्योम)
अणु
	काष्ठा devfreq *devfreq;
	पूर्णांक ret;

	mutex_lock(&devfreq_list_lock);
	list_क्रम_each_entry(devfreq, &devfreq_list, node) अणु
		ret = devfreq_resume_device(devfreq);
		अगर (ret)
			dev_warn(&devfreq->dev,
				 "failed to resume devfreq device\n");
	पूर्ण
	mutex_unlock(&devfreq_list_lock);
पूर्ण

/**
 * devfreq_add_governor() - Add devfreq governor
 * @governor:	the devfreq governor to be added
 */
पूर्णांक devfreq_add_governor(काष्ठा devfreq_governor *governor)
अणु
	काष्ठा devfreq_governor *g;
	काष्ठा devfreq *devfreq;
	पूर्णांक err = 0;

	अगर (!governor) अणु
		pr_err("%s: Invalid parameters.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&devfreq_list_lock);
	g = find_devfreq_governor(governor->name);
	अगर (!IS_ERR(g)) अणु
		pr_err("%s: governor %s already registered\n", __func__,
		       g->name);
		err = -EINVAL;
		जाओ err_out;
	पूर्ण

	list_add(&governor->node, &devfreq_governor_list);

	list_क्रम_each_entry(devfreq, &devfreq_list, node) अणु
		पूर्णांक ret = 0;
		काष्ठा device *dev = devfreq->dev.parent;

		अगर (!म_भेदन(devfreq->governor->name, governor->name,
			     DEVFREQ_NAME_LEN)) अणु
			/* The following should never occur */
			अगर (devfreq->governor) अणु
				dev_warn(dev,
					 "%s: Governor %s already present\n",
					 __func__, devfreq->governor->name);
				ret = devfreq->governor->event_handler(devfreq,
							DEVFREQ_GOV_STOP, शून्य);
				अगर (ret) अणु
					dev_warn(dev,
						 "%s: Governor %s stop = %d\n",
						 __func__,
						 devfreq->governor->name, ret);
				पूर्ण
				/* Fall through */
			पूर्ण
			devfreq->governor = governor;
			ret = devfreq->governor->event_handler(devfreq,
						DEVFREQ_GOV_START, शून्य);
			अगर (ret) अणु
				dev_warn(dev, "%s: Governor %s start=%d\n",
					 __func__, devfreq->governor->name,
					 ret);
			पूर्ण
		पूर्ण
	पूर्ण

err_out:
	mutex_unlock(&devfreq_list_lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL(devfreq_add_governor);

/**
 * devfreq_हटाओ_governor() - Remove devfreq feature from a device.
 * @governor:	the devfreq governor to be हटाओd
 */
पूर्णांक devfreq_हटाओ_governor(काष्ठा devfreq_governor *governor)
अणु
	काष्ठा devfreq_governor *g;
	काष्ठा devfreq *devfreq;
	पूर्णांक err = 0;

	अगर (!governor) अणु
		pr_err("%s: Invalid parameters.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&devfreq_list_lock);
	g = find_devfreq_governor(governor->name);
	अगर (IS_ERR(g)) अणु
		pr_err("%s: governor %s not registered\n", __func__,
		       governor->name);
		err = PTR_ERR(g);
		जाओ err_out;
	पूर्ण
	list_क्रम_each_entry(devfreq, &devfreq_list, node) अणु
		पूर्णांक ret;
		काष्ठा device *dev = devfreq->dev.parent;

		अगर (!म_भेदन(devfreq->governor->name, governor->name,
			     DEVFREQ_NAME_LEN)) अणु
			/* we should have a devfreq governor! */
			अगर (!devfreq->governor) अणु
				dev_warn(dev, "%s: Governor %s NOT present\n",
					 __func__, governor->name);
				जारी;
				/* Fall through */
			पूर्ण
			ret = devfreq->governor->event_handler(devfreq,
						DEVFREQ_GOV_STOP, शून्य);
			अगर (ret) अणु
				dev_warn(dev, "%s: Governor %s stop=%d\n",
					 __func__, devfreq->governor->name,
					 ret);
			पूर्ण
			devfreq->governor = शून्य;
		पूर्ण
	पूर्ण

	list_del(&governor->node);
err_out:
	mutex_unlock(&devfreq_list_lock);

	वापस err;
पूर्ण
EXPORT_SYMBOL(devfreq_हटाओ_governor);

अटल sमाप_प्रकार name_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा devfreq *df = to_devfreq(dev);
	वापस प्र_लिखो(buf, "%s\n", dev_name(df->dev.parent));
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल sमाप_प्रकार governor_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा devfreq *df = to_devfreq(dev);

	अगर (!df->governor)
		वापस -EINVAL;

	वापस प्र_लिखो(buf, "%s\n", df->governor->name);
पूर्ण

अटल sमाप_प्रकार governor_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा devfreq *df = to_devfreq(dev);
	पूर्णांक ret;
	अक्षर str_governor[DEVFREQ_NAME_LEN + 1];
	स्थिर काष्ठा devfreq_governor *governor, *prev_governor;

	अगर (!df->governor)
		वापस -EINVAL;

	ret = माला_पूछो(buf, "%" __stringअगरy(DEVFREQ_NAME_LEN) "s", str_governor);
	अगर (ret != 1)
		वापस -EINVAL;

	mutex_lock(&devfreq_list_lock);
	governor = try_then_request_governor(str_governor);
	अगर (IS_ERR(governor)) अणु
		ret = PTR_ERR(governor);
		जाओ out;
	पूर्ण
	अगर (df->governor == governor) अणु
		ret = 0;
		जाओ out;
	पूर्ण अन्यथा अगर (IS_SUPPORTED_FLAG(df->governor->flags, IMMUTABLE)
		|| IS_SUPPORTED_FLAG(governor->flags, IMMUTABLE)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/*
	 * Stop the current governor and हटाओ the specअगरic sysfs files
	 * which depend on current governor.
	 */
	ret = df->governor->event_handler(df, DEVFREQ_GOV_STOP, शून्य);
	अगर (ret) अणु
		dev_warn(dev, "%s: Governor %s not stopped(%d)\n",
			 __func__, df->governor->name, ret);
		जाओ out;
	पूर्ण
	हटाओ_sysfs_files(df, df->governor);

	/*
	 * Start the new governor and create the specअगरic sysfs files
	 * which depend on the new governor.
	 */
	prev_governor = df->governor;
	df->governor = governor;
	ret = df->governor->event_handler(df, DEVFREQ_GOV_START, शून्य);
	अगर (ret) अणु
		dev_warn(dev, "%s: Governor %s not started(%d)\n",
			 __func__, df->governor->name, ret);

		/* Restore previous governor */
		df->governor = prev_governor;
		ret = df->governor->event_handler(df, DEVFREQ_GOV_START, शून्य);
		अगर (ret) अणु
			dev_err(dev,
				"%s: reverting to Governor %s failed (%d)\n",
				__func__, prev_governor->name, ret);
			df->governor = शून्य;
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * Create the sysfs files क्रम the new governor. But अगर failed to start
	 * the new governor, restore the sysfs files of previous governor.
	 */
	create_sysfs_files(df, df->governor);

out:
	mutex_unlock(&devfreq_list_lock);

	अगर (!ret)
		ret = count;
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RW(governor);

अटल sमाप_प्रकार available_governors_show(काष्ठा device *d,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा devfreq *df = to_devfreq(d);
	sमाप_प्रकार count = 0;

	अगर (!df->governor)
		वापस -EINVAL;

	mutex_lock(&devfreq_list_lock);

	/*
	 * The devfreq with immutable governor (e.g., passive) shows
	 * only own governor.
	 */
	अगर (IS_SUPPORTED_FLAG(df->governor->flags, IMMUTABLE)) अणु
		count = scnम_लिखो(&buf[count], DEVFREQ_NAME_LEN,
				  "%s ", df->governor->name);
	/*
	 * The devfreq device shows the रेजिस्टरed governor except क्रम
	 * immutable governors such as passive governor .
	 */
	पूर्ण अन्यथा अणु
		काष्ठा devfreq_governor *governor;

		list_क्रम_each_entry(governor, &devfreq_governor_list, node) अणु
			अगर (IS_SUPPORTED_FLAG(governor->flags, IMMUTABLE))
				जारी;
			count += scnम_लिखो(&buf[count], (PAGE_SIZE - count - 2),
					   "%s ", governor->name);
		पूर्ण
	पूर्ण

	mutex_unlock(&devfreq_list_lock);

	/* Truncate the trailing space */
	अगर (count)
		count--;

	count += प्र_लिखो(&buf[count], "\n");

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RO(available_governors);

अटल sमाप_प्रकार cur_freq_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	अचिन्हित दीर्घ freq;
	काष्ठा devfreq *df = to_devfreq(dev);

	अगर (!df->profile)
		वापस -EINVAL;

	अगर (df->profile->get_cur_freq &&
		!df->profile->get_cur_freq(df->dev.parent, &freq))
		वापस प्र_लिखो(buf, "%lu\n", freq);

	वापस प्र_लिखो(buf, "%lu\n", df->previous_freq);
पूर्ण
अटल DEVICE_ATTR_RO(cur_freq);

अटल sमाप_प्रकार target_freq_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा devfreq *df = to_devfreq(dev);

	वापस प्र_लिखो(buf, "%lu\n", df->previous_freq);
पूर्ण
अटल DEVICE_ATTR_RO(target_freq);

अटल sमाप_प्रकार min_freq_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा devfreq *df = to_devfreq(dev);
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	/*
	 * Protect against theoretical sysfs ग_लिखोs between
	 * device_add and dev_pm_qos_add_request
	 */
	अगर (!dev_pm_qos_request_active(&df->user_min_freq_req))
		वापस -EAGAIN;

	ret = माला_पूछो(buf, "%lu", &value);
	अगर (ret != 1)
		वापस -EINVAL;

	/* Round करोwn to kHz क्रम PM QoS */
	ret = dev_pm_qos_update_request(&df->user_min_freq_req,
					value / HZ_PER_KHZ);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार min_freq_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा devfreq *df = to_devfreq(dev);
	अचिन्हित दीर्घ min_freq, max_freq;

	mutex_lock(&df->lock);
	get_freq_range(df, &min_freq, &max_freq);
	mutex_unlock(&df->lock);

	वापस प्र_लिखो(buf, "%lu\n", min_freq);
पूर्ण
अटल DEVICE_ATTR_RW(min_freq);

अटल sमाप_प्रकार max_freq_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा devfreq *df = to_devfreq(dev);
	अचिन्हित दीर्घ value;
	पूर्णांक ret;

	/*
	 * Protect against theoretical sysfs ग_लिखोs between
	 * device_add and dev_pm_qos_add_request
	 */
	अगर (!dev_pm_qos_request_active(&df->user_max_freq_req))
		वापस -EINVAL;

	ret = माला_पूछो(buf, "%lu", &value);
	अगर (ret != 1)
		वापस -EINVAL;

	/*
	 * PM QoS frequencies are in kHz so we need to convert. Convert by
	 * rounding upwards so that the acceptable पूर्णांकerval never shrinks.
	 *
	 * For example अगर the user ग_लिखोs "666666666" to sysfs this value will
	 * be converted to 666667 kHz and back to 666667000 Hz beक्रमe an OPP
	 * lookup, this ensures that an OPP of 666666666Hz is still accepted.
	 *
	 * A value of zero means "no limit".
	 */
	अगर (value)
		value = DIV_ROUND_UP(value, HZ_PER_KHZ);
	अन्यथा
		value = PM_QOS_MAX_FREQUENCY_DEFAULT_VALUE;

	ret = dev_pm_qos_update_request(&df->user_max_freq_req, value);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार max_freq_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			     अक्षर *buf)
अणु
	काष्ठा devfreq *df = to_devfreq(dev);
	अचिन्हित दीर्घ min_freq, max_freq;

	mutex_lock(&df->lock);
	get_freq_range(df, &min_freq, &max_freq);
	mutex_unlock(&df->lock);

	वापस प्र_लिखो(buf, "%lu\n", max_freq);
पूर्ण
अटल DEVICE_ATTR_RW(max_freq);

अटल sमाप_प्रकार available_frequencies_show(काष्ठा device *d,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा devfreq *df = to_devfreq(d);
	sमाप_प्रकार count = 0;
	पूर्णांक i;

	अगर (!df->profile)
		वापस -EINVAL;

	mutex_lock(&df->lock);

	क्रम (i = 0; i < df->profile->max_state; i++)
		count += scnम_लिखो(&buf[count], (PAGE_SIZE - count - 2),
				"%lu ", df->profile->freq_table[i]);

	mutex_unlock(&df->lock);
	/* Truncate the trailing space */
	अगर (count)
		count--;

	count += प्र_लिखो(&buf[count], "\n");

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RO(available_frequencies);

अटल sमाप_प्रकार trans_stat_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा devfreq *df = to_devfreq(dev);
	sमाप_प्रकार len;
	पूर्णांक i, j;
	अचिन्हित पूर्णांक max_state;

	अगर (!df->profile)
		वापस -EINVAL;
	max_state = df->profile->max_state;

	अगर (max_state == 0)
		वापस प्र_लिखो(buf, "Not Supported.\n");

	mutex_lock(&df->lock);
	अगर (!df->stop_polling &&
			devfreq_update_status(df, df->previous_freq)) अणु
		mutex_unlock(&df->lock);
		वापस 0;
	पूर्ण
	mutex_unlock(&df->lock);

	len = प्र_लिखो(buf, "     From  :   To\n");
	len += प्र_लिखो(buf + len, "           :");
	क्रम (i = 0; i < max_state; i++)
		len += प्र_लिखो(buf + len, "%10lu",
				df->profile->freq_table[i]);

	len += प्र_लिखो(buf + len, "   time(ms)\n");

	क्रम (i = 0; i < max_state; i++) अणु
		अगर (df->profile->freq_table[i]
					== df->previous_freq) अणु
			len += प्र_लिखो(buf + len, "*");
		पूर्ण अन्यथा अणु
			len += प्र_लिखो(buf + len, " ");
		पूर्ण
		len += प्र_लिखो(buf + len, "%10lu:",
				df->profile->freq_table[i]);
		क्रम (j = 0; j < max_state; j++)
			len += प्र_लिखो(buf + len, "%10u",
				df->stats.trans_table[(i * max_state) + j]);

		len += प्र_लिखो(buf + len, "%10llu\n", (u64)
			jअगरfies64_to_msecs(df->stats.समय_in_state[i]));
	पूर्ण

	len += प्र_लिखो(buf + len, "Total transition : %u\n",
					df->stats.total_trans);
	वापस len;
पूर्ण

अटल sमाप_प्रकार trans_stat_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा devfreq *df = to_devfreq(dev);
	पूर्णांक err, value;

	अगर (!df->profile)
		वापस -EINVAL;

	अगर (df->profile->max_state == 0)
		वापस count;

	err = kstrtoपूर्णांक(buf, 10, &value);
	अगर (err || value != 0)
		वापस -EINVAL;

	mutex_lock(&df->lock);
	स_रखो(df->stats.समय_in_state, 0, (df->profile->max_state *
					माप(*df->stats.समय_in_state)));
	स_रखो(df->stats.trans_table, 0, array3_size(माप(अचिन्हित पूर्णांक),
					df->profile->max_state,
					df->profile->max_state));
	df->stats.total_trans = 0;
	df->stats.last_update = get_jअगरfies_64();
	mutex_unlock(&df->lock);

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RW(trans_stat);

अटल काष्ठा attribute *devfreq_attrs[] = अणु
	&dev_attr_name.attr,
	&dev_attr_governor.attr,
	&dev_attr_available_governors.attr,
	&dev_attr_cur_freq.attr,
	&dev_attr_available_frequencies.attr,
	&dev_attr_target_freq.attr,
	&dev_attr_min_freq.attr,
	&dev_attr_max_freq.attr,
	&dev_attr_trans_stat.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(devfreq);

अटल sमाप_प्रकार polling_पूर्णांकerval_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा devfreq *df = to_devfreq(dev);

	अगर (!df->profile)
		वापस -EINVAL;

	वापस प्र_लिखो(buf, "%d\n", df->profile->polling_ms);
पूर्ण

अटल sमाप_प्रकार polling_पूर्णांकerval_store(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा devfreq *df = to_devfreq(dev);
	अचिन्हित पूर्णांक value;
	पूर्णांक ret;

	अगर (!df->governor)
		वापस -EINVAL;

	ret = माला_पूछो(buf, "%u", &value);
	अगर (ret != 1)
		वापस -EINVAL;

	df->governor->event_handler(df, DEVFREQ_GOV_UPDATE_INTERVAL, &value);
	ret = count;

	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RW(polling_पूर्णांकerval);

अटल sमाप_प्रकार समयr_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा devfreq *df = to_devfreq(dev);

	अगर (!df->profile)
		वापस -EINVAL;

	वापस प्र_लिखो(buf, "%s\n", समयr_name[df->profile->समयr]);
पूर्ण

अटल sमाप_प्रकार समयr_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा devfreq *df = to_devfreq(dev);
	अक्षर str_समयr[DEVFREQ_NAME_LEN + 1];
	पूर्णांक समयr = -1;
	पूर्णांक ret = 0, i;

	अगर (!df->governor || !df->profile)
		वापस -EINVAL;

	ret = माला_पूछो(buf, "%16s", str_समयr);
	अगर (ret != 1)
		वापस -EINVAL;

	क्रम (i = 0; i < DEVFREQ_TIMER_NUM; i++) अणु
		अगर (!म_भेदन(समयr_name[i], str_समयr, DEVFREQ_NAME_LEN)) अणु
			समयr = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (समयr < 0) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (df->profile->समयr == समयr) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	mutex_lock(&df->lock);
	df->profile->समयr = समयr;
	mutex_unlock(&df->lock);

	ret = df->governor->event_handler(df, DEVFREQ_GOV_STOP, शून्य);
	अगर (ret) अणु
		dev_warn(dev, "%s: Governor %s not stopped(%d)\n",
			 __func__, df->governor->name, ret);
		जाओ out;
	पूर्ण

	ret = df->governor->event_handler(df, DEVFREQ_GOV_START, शून्य);
	अगर (ret)
		dev_warn(dev, "%s: Governor %s not started(%d)\n",
			 __func__, df->governor->name, ret);
out:
	वापस ret ? ret : count;
पूर्ण
अटल DEVICE_ATTR_RW(समयr);

#घोषणा CREATE_SYSFS_खाता(df, name)					\
अणु									\
	पूर्णांक ret;							\
	ret = sysfs_create_file(&df->dev.kobj, &dev_attr_##name.attr);	\
	अगर (ret < 0) अणु							\
		dev_warn(&df->dev,					\
			"Unable to create attr(%s)\n", "##name");	\
	पूर्ण								\
पूर्ण									\

/* Create the specअगरic sysfs files which depend on each governor. */
अटल व्योम create_sysfs_files(काष्ठा devfreq *devfreq,
				स्थिर काष्ठा devfreq_governor *gov)
अणु
	अगर (IS_SUPPORTED_ATTR(gov->attrs, POLLING_INTERVAL))
		CREATE_SYSFS_खाता(devfreq, polling_पूर्णांकerval);
	अगर (IS_SUPPORTED_ATTR(gov->attrs, TIMER))
		CREATE_SYSFS_खाता(devfreq, समयr);
पूर्ण

/* Remove the specअगरic sysfs files which depend on each governor. */
अटल व्योम हटाओ_sysfs_files(काष्ठा devfreq *devfreq,
				स्थिर काष्ठा devfreq_governor *gov)
अणु
	अगर (IS_SUPPORTED_ATTR(gov->attrs, POLLING_INTERVAL))
		sysfs_हटाओ_file(&devfreq->dev.kobj,
				&dev_attr_polling_पूर्णांकerval.attr);
	अगर (IS_SUPPORTED_ATTR(gov->attrs, TIMER))
		sysfs_हटाओ_file(&devfreq->dev.kobj, &dev_attr_समयr.attr);
पूर्ण

/**
 * devfreq_summary_show() - Show the summary of the devfreq devices
 * @s:		seq_file instance to show the summary of devfreq devices
 * @data:	not used
 *
 * Show the summary of the devfreq devices via 'devfreq_summary' debugfs file.
 * It helps that user can know the detailed inक्रमmation of the devfreq devices.
 *
 * Return 0 always because it shows the inक्रमmation without any data change.
 */
अटल पूर्णांक devfreq_summary_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा devfreq *devfreq;
	काष्ठा devfreq *p_devfreq = शून्य;
	अचिन्हित दीर्घ cur_freq, min_freq, max_freq;
	अचिन्हित पूर्णांक polling_ms;
	अचिन्हित पूर्णांक समयr;

	seq_म_लिखो(s, "%-30s %-30s %-15s %-10s %10s %12s %12s %12s\n",
			"dev",
			"parent_dev",
			"governor",
			"timer",
			"polling_ms",
			"cur_freq_Hz",
			"min_freq_Hz",
			"max_freq_Hz");
	seq_म_लिखो(s, "%30s %30s %15s %10s %10s %12s %12s %12s\n",
			"------------------------------",
			"------------------------------",
			"---------------",
			"----------",
			"----------",
			"------------",
			"------------",
			"------------");

	mutex_lock(&devfreq_list_lock);

	list_क्रम_each_entry_reverse(devfreq, &devfreq_list, node) अणु
#अगर IS_ENABLED(CONFIG_DEVFREQ_GOV_PASSIVE)
		अगर (!म_भेदन(devfreq->governor->name, DEVFREQ_GOV_PASSIVE,
							DEVFREQ_NAME_LEN)) अणु
			काष्ठा devfreq_passive_data *data = devfreq->data;

			अगर (data)
				p_devfreq = data->parent;
		पूर्ण अन्यथा अणु
			p_devfreq = शून्य;
		पूर्ण
#पूर्ण_अगर

		mutex_lock(&devfreq->lock);
		cur_freq = devfreq->previous_freq;
		get_freq_range(devfreq, &min_freq, &max_freq);
		समयr = devfreq->profile->समयr;

		अगर (IS_SUPPORTED_ATTR(devfreq->governor->attrs, POLLING_INTERVAL))
			polling_ms = devfreq->profile->polling_ms;
		अन्यथा
			polling_ms = 0;
		mutex_unlock(&devfreq->lock);

		seq_म_लिखो(s,
			"%-30s %-30s %-15s %-10s %10d %12ld %12ld %12ld\n",
			dev_name(&devfreq->dev),
			p_devfreq ? dev_name(&p_devfreq->dev) : "null",
			devfreq->governor->name,
			polling_ms ? समयr_name[समयr] : "null",
			polling_ms,
			cur_freq,
			min_freq,
			max_freq);
	पूर्ण

	mutex_unlock(&devfreq_list_lock);

	वापस 0;
पूर्ण
DEFINE_SHOW_ATTRIBUTE(devfreq_summary);

अटल पूर्णांक __init devfreq_init(व्योम)
अणु
	devfreq_class = class_create(THIS_MODULE, "devfreq");
	अगर (IS_ERR(devfreq_class)) अणु
		pr_err("%s: couldn't create class\n", __खाता__);
		वापस PTR_ERR(devfreq_class);
	पूर्ण

	devfreq_wq = create_मुक्तzable_workqueue("devfreq_wq");
	अगर (!devfreq_wq) अणु
		class_destroy(devfreq_class);
		pr_err("%s: couldn't create workqueue\n", __खाता__);
		वापस -ENOMEM;
	पूर्ण
	devfreq_class->dev_groups = devfreq_groups;

	devfreq_debugfs = debugfs_create_dir("devfreq", शून्य);
	debugfs_create_file("devfreq_summary", 0444,
				devfreq_debugfs, शून्य,
				&devfreq_summary_fops);

	वापस 0;
पूर्ण
subsys_initcall(devfreq_init);

/*
 * The following are helper functions क्रम devfreq user device drivers with
 * OPP framework.
 */

/**
 * devfreq_recommended_opp() - Helper function to get proper OPP क्रम the
 *			     freq value given to target callback.
 * @dev:	The devfreq user device. (parent of devfreq)
 * @freq:	The frequency given to target function
 * @flags:	Flags handed from devfreq framework.
 *
 * The callers are required to call dev_pm_opp_put() क्रम the वापसed OPP after
 * use.
 */
काष्ठा dev_pm_opp *devfreq_recommended_opp(काष्ठा device *dev,
					   अचिन्हित दीर्घ *freq,
					   u32 flags)
अणु
	काष्ठा dev_pm_opp *opp;

	अगर (flags & DEVFREQ_FLAG_LEAST_UPPER_BOUND) अणु
		/* The freq is an upper bound. opp should be lower */
		opp = dev_pm_opp_find_freq_न्यूनमान(dev, freq);

		/* If not available, use the बंदst opp */
		अगर (opp == ERR_PTR(-दुस्फल))
			opp = dev_pm_opp_find_freq_उच्चमान(dev, freq);
	पूर्ण अन्यथा अणु
		/* The freq is an lower bound. opp should be higher */
		opp = dev_pm_opp_find_freq_उच्चमान(dev, freq);

		/* If not available, use the बंदst opp */
		अगर (opp == ERR_PTR(-दुस्फल))
			opp = dev_pm_opp_find_freq_न्यूनमान(dev, freq);
	पूर्ण

	वापस opp;
पूर्ण
EXPORT_SYMBOL(devfreq_recommended_opp);

/**
 * devfreq_रेजिस्टर_opp_notअगरier() - Helper function to get devfreq notअगरied
 *				     क्रम any changes in the OPP availability
 *				     changes
 * @dev:	The devfreq user device. (parent of devfreq)
 * @devfreq:	The devfreq object.
 */
पूर्णांक devfreq_रेजिस्टर_opp_notअगरier(काष्ठा device *dev, काष्ठा devfreq *devfreq)
अणु
	वापस dev_pm_opp_रेजिस्टर_notअगरier(dev, &devfreq->nb);
पूर्ण
EXPORT_SYMBOL(devfreq_रेजिस्टर_opp_notअगरier);

/**
 * devfreq_unरेजिस्टर_opp_notअगरier() - Helper function to stop getting devfreq
 *				       notअगरied क्रम any changes in the OPP
 *				       availability changes anymore.
 * @dev:	The devfreq user device. (parent of devfreq)
 * @devfreq:	The devfreq object.
 *
 * At निकास() callback of devfreq_dev_profile, this must be included अगर
 * devfreq_recommended_opp is used.
 */
पूर्णांक devfreq_unरेजिस्टर_opp_notअगरier(काष्ठा device *dev, काष्ठा devfreq *devfreq)
अणु
	वापस dev_pm_opp_unरेजिस्टर_notअगरier(dev, &devfreq->nb);
पूर्ण
EXPORT_SYMBOL(devfreq_unरेजिस्टर_opp_notअगरier);

अटल व्योम devm_devfreq_opp_release(काष्ठा device *dev, व्योम *res)
अणु
	devfreq_unरेजिस्टर_opp_notअगरier(dev, *(काष्ठा devfreq **)res);
पूर्ण

/**
 * devm_devfreq_रेजिस्टर_opp_notअगरier() - Resource-managed
 *					  devfreq_रेजिस्टर_opp_notअगरier()
 * @dev:	The devfreq user device. (parent of devfreq)
 * @devfreq:	The devfreq object.
 */
पूर्णांक devm_devfreq_रेजिस्टर_opp_notअगरier(काष्ठा device *dev,
				       काष्ठा devfreq *devfreq)
अणु
	काष्ठा devfreq **ptr;
	पूर्णांक ret;

	ptr = devres_alloc(devm_devfreq_opp_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	ret = devfreq_रेजिस्टर_opp_notअगरier(dev, devfreq);
	अगर (ret) अणु
		devres_मुक्त(ptr);
		वापस ret;
	पूर्ण

	*ptr = devfreq;
	devres_add(dev, ptr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(devm_devfreq_रेजिस्टर_opp_notअगरier);

/**
 * devm_devfreq_unरेजिस्टर_opp_notअगरier() - Resource-managed
 *					    devfreq_unरेजिस्टर_opp_notअगरier()
 * @dev:	The devfreq user device. (parent of devfreq)
 * @devfreq:	The devfreq object.
 */
व्योम devm_devfreq_unरेजिस्टर_opp_notअगरier(काष्ठा device *dev,
					 काष्ठा devfreq *devfreq)
अणु
	WARN_ON(devres_release(dev, devm_devfreq_opp_release,
			       devm_devfreq_dev_match, devfreq));
पूर्ण
EXPORT_SYMBOL(devm_devfreq_unरेजिस्टर_opp_notअगरier);

/**
 * devfreq_रेजिस्टर_notअगरier() - Register a driver with devfreq
 * @devfreq:	The devfreq object.
 * @nb:		The notअगरier block to रेजिस्टर.
 * @list:	DEVFREQ_TRANSITION_NOTIFIER.
 */
पूर्णांक devfreq_रेजिस्टर_notअगरier(काष्ठा devfreq *devfreq,
			      काष्ठा notअगरier_block *nb,
			      अचिन्हित पूर्णांक list)
अणु
	पूर्णांक ret = 0;

	अगर (!devfreq)
		वापस -EINVAL;

	चयन (list) अणु
	हाल DEVFREQ_TRANSITION_NOTIFIER:
		ret = srcu_notअगरier_chain_रेजिस्टर(
				&devfreq->transition_notअगरier_list, nb);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(devfreq_रेजिस्टर_notअगरier);

/*
 * devfreq_unरेजिस्टर_notअगरier() - Unरेजिस्टर a driver with devfreq
 * @devfreq:	The devfreq object.
 * @nb:		The notअगरier block to be unरेजिस्टरed.
 * @list:	DEVFREQ_TRANSITION_NOTIFIER.
 */
पूर्णांक devfreq_unरेजिस्टर_notअगरier(काष्ठा devfreq *devfreq,
				काष्ठा notअगरier_block *nb,
				अचिन्हित पूर्णांक list)
अणु
	पूर्णांक ret = 0;

	अगर (!devfreq)
		वापस -EINVAL;

	चयन (list) अणु
	हाल DEVFREQ_TRANSITION_NOTIFIER:
		ret = srcu_notअगरier_chain_unरेजिस्टर(
				&devfreq->transition_notअगरier_list, nb);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(devfreq_unरेजिस्टर_notअगरier);

काष्ठा devfreq_notअगरier_devres अणु
	काष्ठा devfreq *devfreq;
	काष्ठा notअगरier_block *nb;
	अचिन्हित पूर्णांक list;
पूर्ण;

अटल व्योम devm_devfreq_notअगरier_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा devfreq_notअगरier_devres *this = res;

	devfreq_unरेजिस्टर_notअगरier(this->devfreq, this->nb, this->list);
पूर्ण

/**
 * devm_devfreq_रेजिस्टर_notअगरier()
 *	- Resource-managed devfreq_रेजिस्टर_notअगरier()
 * @dev:	The devfreq user device. (parent of devfreq)
 * @devfreq:	The devfreq object.
 * @nb:		The notअगरier block to be unरेजिस्टरed.
 * @list:	DEVFREQ_TRANSITION_NOTIFIER.
 */
पूर्णांक devm_devfreq_रेजिस्टर_notअगरier(काष्ठा device *dev,
				काष्ठा devfreq *devfreq,
				काष्ठा notअगरier_block *nb,
				अचिन्हित पूर्णांक list)
अणु
	काष्ठा devfreq_notअगरier_devres *ptr;
	पूर्णांक ret;

	ptr = devres_alloc(devm_devfreq_notअगरier_release, माप(*ptr),
				GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	ret = devfreq_रेजिस्टर_notअगरier(devfreq, nb, list);
	अगर (ret) अणु
		devres_मुक्त(ptr);
		वापस ret;
	पूर्ण

	ptr->devfreq = devfreq;
	ptr->nb = nb;
	ptr->list = list;
	devres_add(dev, ptr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(devm_devfreq_रेजिस्टर_notअगरier);

/**
 * devm_devfreq_unरेजिस्टर_notअगरier()
 *	- Resource-managed devfreq_unरेजिस्टर_notअगरier()
 * @dev:	The devfreq user device. (parent of devfreq)
 * @devfreq:	The devfreq object.
 * @nb:		The notअगरier block to be unरेजिस्टरed.
 * @list:	DEVFREQ_TRANSITION_NOTIFIER.
 */
व्योम devm_devfreq_unरेजिस्टर_notअगरier(काष्ठा device *dev,
				      काष्ठा devfreq *devfreq,
				      काष्ठा notअगरier_block *nb,
				      अचिन्हित पूर्णांक list)
अणु
	WARN_ON(devres_release(dev, devm_devfreq_notअगरier_release,
			       devm_devfreq_dev_match, devfreq));
पूर्ण
EXPORT_SYMBOL(devm_devfreq_unरेजिस्टर_notअगरier);
