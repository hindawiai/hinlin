<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ChromeOS EC multi-function device
 *
 * Copyright (C) 2012 Google, Inc
 *
 * The ChromeOS EC multi function device is used to mux all the requests
 * to the EC device क्रम its multiple features: keyboard controller,
 * battery अक्षरging and regulator control, firmware update.
 */

#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/suspend.h>

#समावेश "cros_ec.h"

#घोषणा CROS_EC_DEV_EC_INDEX 0
#घोषणा CROS_EC_DEV_PD_INDEX 1

अटल काष्ठा cros_ec_platक्रमm ec_p = अणु
	.ec_name = CROS_EC_DEV_NAME,
	.cmd_offset = EC_CMD_PASSTHRU_OFFSET(CROS_EC_DEV_EC_INDEX),
पूर्ण;

अटल काष्ठा cros_ec_platक्रमm pd_p = अणु
	.ec_name = CROS_EC_DEV_PD_NAME,
	.cmd_offset = EC_CMD_PASSTHRU_OFFSET(CROS_EC_DEV_PD_INDEX),
पूर्ण;

/**
 * cros_ec_irq_handler() - top half part of the पूर्णांकerrupt handler
 * @irq: IRQ id
 * @data: (ec_dev) Device with events to process.
 *
 * Return: Wakeup the bottom half
 */
अटल irqवापस_t cros_ec_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cros_ec_device *ec_dev = data;

	ec_dev->last_event_समय = cros_ec_get_समय_ns();

	वापस IRQ_WAKE_THREAD;
पूर्ण

/**
 * cros_ec_handle_event() - process and क्रमward pending events on EC
 * @ec_dev: Device with events to process.
 *
 * Call this function in a loop when the kernel is notअगरied that the EC has
 * pending events.
 *
 * Return: true अगर more events are still pending and this function should be
 * called again.
 */
अटल bool cros_ec_handle_event(काष्ठा cros_ec_device *ec_dev)
अणु
	bool wake_event;
	bool ec_has_more_events;
	पूर्णांक ret;

	ret = cros_ec_get_next_event(ec_dev, &wake_event, &ec_has_more_events);

	/*
	 * Signal only अगर wake host events or any पूर्णांकerrupt अगर
	 * cros_ec_get_next_event() वापसed an error (शेष value क्रम
	 * wake_event is true)
	 */
	अगर (wake_event && device_may_wakeup(ec_dev->dev))
		pm_wakeup_event(ec_dev->dev, 0);

	अगर (ret > 0)
		blocking_notअगरier_call_chain(&ec_dev->event_notअगरier,
					     0, ec_dev);

	वापस ec_has_more_events;
पूर्ण

/**
 * cros_ec_irq_thपढ़ो() - bottom half part of the पूर्णांकerrupt handler
 * @irq: IRQ id
 * @data: (ec_dev) Device with events to process.
 *
 * Return: Interrupt handled.
 */
irqवापस_t cros_ec_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा cros_ec_device *ec_dev = data;
	bool ec_has_more_events;

	करो अणु
		ec_has_more_events = cros_ec_handle_event(ec_dev);
	पूर्ण जबतक (ec_has_more_events);

	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL(cros_ec_irq_thपढ़ो);

अटल पूर्णांक cros_ec_sleep_event(काष्ठा cros_ec_device *ec_dev, u8 sleep_event)
अणु
	पूर्णांक ret;
	काष्ठा अणु
		काष्ठा cros_ec_command msg;
		जोड़ अणु
			काष्ठा ec_params_host_sleep_event req0;
			काष्ठा ec_params_host_sleep_event_v1 req1;
			काष्ठा ec_response_host_sleep_event_v1 resp1;
		पूर्ण u;
	पूर्ण __packed buf;

	स_रखो(&buf, 0, माप(buf));

	अगर (ec_dev->host_sleep_v1) अणु
		buf.u.req1.sleep_event = sleep_event;
		buf.u.req1.suspend_params.sleep_समयout_ms =
				EC_HOST_SLEEP_TIMEOUT_DEFAULT;

		buf.msg.outsize = माप(buf.u.req1);
		अगर ((sleep_event == HOST_SLEEP_EVENT_S3_RESUME) ||
		    (sleep_event == HOST_SLEEP_EVENT_S0IX_RESUME))
			buf.msg.insize = माप(buf.u.resp1);

		buf.msg.version = 1;

	पूर्ण अन्यथा अणु
		buf.u.req0.sleep_event = sleep_event;
		buf.msg.outsize = माप(buf.u.req0);
	पूर्ण

	buf.msg.command = EC_CMD_HOST_SLEEP_EVENT;

	ret = cros_ec_cmd_xfer_status(ec_dev, &buf.msg);

	/* For now, report failure to transition to S0ix with a warning. */
	अगर (ret >= 0 && ec_dev->host_sleep_v1 &&
	    (sleep_event == HOST_SLEEP_EVENT_S0IX_RESUME)) अणु
		ec_dev->last_resume_result =
			buf.u.resp1.resume_response.sleep_transitions;

		WARN_ONCE(buf.u.resp1.resume_response.sleep_transitions &
			  EC_HOST_RESUME_SLEEP_TIMEOUT,
			  "EC detected sleep transition timeout. Total slp_s0 transitions: %d",
			  buf.u.resp1.resume_response.sleep_transitions &
			  EC_HOST_RESUME_SLEEP_TRANSITIONS_MASK);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक cros_ec_पढ़ोy_event(काष्ठा notअगरier_block *nb,
			       अचिन्हित दीर्घ queued_during_suspend,
			       व्योम *_notअगरy)
अणु
	काष्ठा cros_ec_device *ec_dev = container_of(nb, काष्ठा cros_ec_device,
						     notअगरier_पढ़ोy);
	u32 host_event = cros_ec_get_host_event(ec_dev);

	अगर (host_event & EC_HOST_EVENT_MASK(EC_HOST_EVENT_INTERFACE_READY)) अणु
		mutex_lock(&ec_dev->lock);
		cros_ec_query_all(ec_dev);
		mutex_unlock(&ec_dev->lock);
		वापस NOTIFY_OK;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

/**
 * cros_ec_रेजिस्टर() - Register a new ChromeOS EC, using the provided info.
 * @ec_dev: Device to रेजिस्टर.
 *
 * Beक्रमe calling this, allocate a poपूर्णांकer to a new device and then fill
 * in all the fields up to the --निजी-- marker.
 *
 * Return: 0 on success or negative error code.
 */
पूर्णांक cros_ec_रेजिस्टर(काष्ठा cros_ec_device *ec_dev)
अणु
	काष्ठा device *dev = ec_dev->dev;
	पूर्णांक err = 0;

	BLOCKING_INIT_NOTIFIER_HEAD(&ec_dev->event_notअगरier);

	ec_dev->max_request = माप(काष्ठा ec_params_hello);
	ec_dev->max_response = माप(काष्ठा ec_response_get_protocol_info);
	ec_dev->max_passthru = 0;

	ec_dev->din = devm_kzalloc(dev, ec_dev->din_size, GFP_KERNEL);
	अगर (!ec_dev->din)
		वापस -ENOMEM;

	ec_dev->करोut = devm_kzalloc(dev, ec_dev->करोut_size, GFP_KERNEL);
	अगर (!ec_dev->करोut)
		वापस -ENOMEM;

	mutex_init(&ec_dev->lock);

	err = cros_ec_query_all(ec_dev);
	अगर (err) अणु
		dev_err(dev, "Cannot identify the EC: error %d\n", err);
		वापस err;
	पूर्ण

	अगर (ec_dev->irq > 0) अणु
		err = devm_request_thपढ़ोed_irq(dev, ec_dev->irq,
						cros_ec_irq_handler,
						cros_ec_irq_thपढ़ो,
						IRQF_TRIGGER_LOW | IRQF_ONESHOT,
						"chromeos-ec", ec_dev);
		अगर (err) अणु
			dev_err(dev, "Failed to request IRQ %d: %d",
				ec_dev->irq, err);
			वापस err;
		पूर्ण
	पूर्ण

	/* Register a platक्रमm device क्रम the मुख्य EC instance */
	ec_dev->ec = platक्रमm_device_रेजिस्टर_data(ec_dev->dev, "cros-ec-dev",
					PLATFORM_DEVID_AUTO, &ec_p,
					माप(काष्ठा cros_ec_platक्रमm));
	अगर (IS_ERR(ec_dev->ec)) अणु
		dev_err(ec_dev->dev,
			"Failed to create CrOS EC platform device\n");
		वापस PTR_ERR(ec_dev->ec);
	पूर्ण

	अगर (ec_dev->max_passthru) अणु
		/*
		 * Register a platक्रमm device क्रम the PD behind the मुख्य EC.
		 * We make the following assumptions:
		 * - behind an EC, we have a pd
		 * - only one device added.
		 * - the EC is responsive at init समय (it is not true क्रम a
		 *   sensor hub).
		 */
		ec_dev->pd = platक्रमm_device_रेजिस्टर_data(ec_dev->dev,
					"cros-ec-dev",
					PLATFORM_DEVID_AUTO, &pd_p,
					माप(काष्ठा cros_ec_platक्रमm));
		अगर (IS_ERR(ec_dev->pd)) अणु
			dev_err(ec_dev->dev,
				"Failed to create CrOS PD platform device\n");
			platक्रमm_device_unरेजिस्टर(ec_dev->ec);
			वापस PTR_ERR(ec_dev->pd);
		पूर्ण
	पूर्ण

	अगर (IS_ENABLED(CONFIG_OF) && dev->of_node) अणु
		err = devm_of_platक्रमm_populate(dev);
		अगर (err) अणु
			platक्रमm_device_unरेजिस्टर(ec_dev->pd);
			platक्रमm_device_unरेजिस्टर(ec_dev->ec);
			dev_err(dev, "Failed to register sub-devices\n");
			वापस err;
		पूर्ण
	पूर्ण

	/*
	 * Clear sleep event - this will fail harmlessly on platक्रमms that
	 * करोn't implement the sleep event host command.
	 */
	err = cros_ec_sleep_event(ec_dev, 0);
	अगर (err < 0)
		dev_dbg(ec_dev->dev, "Error %d clearing sleep event to ec",
			err);

	अगर (ec_dev->mkbp_event_supported) अणु
		/*
		 * Register the notअगरier क्रम EC_HOST_EVENT_INTERFACE_READY
		 * event.
		 */
		ec_dev->notअगरier_पढ़ोy.notअगरier_call = cros_ec_पढ़ोy_event;
		err = blocking_notअगरier_chain_रेजिस्टर(&ec_dev->event_notअगरier,
						      &ec_dev->notअगरier_पढ़ोy);
		अगर (err)
			वापस err;
	पूर्ण

	dev_info(dev, "Chrome EC device registered\n");

	/*
	 * Unlock EC that may be रुकोing क्रम AP to process MKBP events.
	 * If the AP takes to दीर्घ to answer, the EC would stop sending events.
	 */
	अगर (ec_dev->mkbp_event_supported)
		cros_ec_irq_thपढ़ो(0, ec_dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cros_ec_रेजिस्टर);

/**
 * cros_ec_unरेजिस्टर() - Remove a ChromeOS EC.
 * @ec_dev: Device to unरेजिस्टर.
 *
 * Call this to deरेजिस्टर a ChromeOS EC, then clean up any निजी data.
 *
 * Return: 0 on success or negative error code.
 */
पूर्णांक cros_ec_unरेजिस्टर(काष्ठा cros_ec_device *ec_dev)
अणु
	अगर (ec_dev->pd)
		platक्रमm_device_unरेजिस्टर(ec_dev->pd);
	platक्रमm_device_unरेजिस्टर(ec_dev->ec);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cros_ec_unरेजिस्टर);

#अगर_घोषित CONFIG_PM_SLEEP
/**
 * cros_ec_suspend() - Handle a suspend operation क्रम the ChromeOS EC device.
 * @ec_dev: Device to suspend.
 *
 * This can be called by drivers to handle a suspend event.
 *
 * Return: 0 on success or negative error code.
 */
पूर्णांक cros_ec_suspend(काष्ठा cros_ec_device *ec_dev)
अणु
	काष्ठा device *dev = ec_dev->dev;
	पूर्णांक ret;
	u8 sleep_event;

	sleep_event = (!IS_ENABLED(CONFIG_ACPI) || pm_suspend_via_firmware()) ?
		      HOST_SLEEP_EVENT_S3_SUSPEND :
		      HOST_SLEEP_EVENT_S0IX_SUSPEND;

	ret = cros_ec_sleep_event(ec_dev, sleep_event);
	अगर (ret < 0)
		dev_dbg(ec_dev->dev, "Error %d sending suspend event to ec",
			ret);

	अगर (device_may_wakeup(dev))
		ec_dev->wake_enabled = !enable_irq_wake(ec_dev->irq);

	disable_irq(ec_dev->irq);
	ec_dev->was_wake_device = ec_dev->wake_enabled;
	ec_dev->suspended = true;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cros_ec_suspend);

अटल व्योम cros_ec_report_events_during_suspend(काष्ठा cros_ec_device *ec_dev)
अणु
	जबतक (ec_dev->mkbp_event_supported &&
	       cros_ec_get_next_event(ec_dev, शून्य, शून्य) > 0)
		blocking_notअगरier_call_chain(&ec_dev->event_notअगरier,
					     1, ec_dev);
पूर्ण

/**
 * cros_ec_resume() - Handle a resume operation क्रम the ChromeOS EC device.
 * @ec_dev: Device to resume.
 *
 * This can be called by drivers to handle a resume event.
 *
 * Return: 0 on success or negative error code.
 */
पूर्णांक cros_ec_resume(काष्ठा cros_ec_device *ec_dev)
अणु
	पूर्णांक ret;
	u8 sleep_event;

	ec_dev->suspended = false;
	enable_irq(ec_dev->irq);

	sleep_event = (!IS_ENABLED(CONFIG_ACPI) || pm_suspend_via_firmware()) ?
		      HOST_SLEEP_EVENT_S3_RESUME :
		      HOST_SLEEP_EVENT_S0IX_RESUME;

	ret = cros_ec_sleep_event(ec_dev, sleep_event);
	अगर (ret < 0)
		dev_dbg(ec_dev->dev, "Error %d sending resume event to ec",
			ret);

	अगर (ec_dev->wake_enabled) अणु
		disable_irq_wake(ec_dev->irq);
		ec_dev->wake_enabled = 0;
	पूर्ण
	/*
	 * Let the mfd devices know about events that occur during
	 * suspend. This way the clients know what to करो with them.
	 */
	cros_ec_report_events_during_suspend(ec_dev);


	वापस 0;
पूर्ण
EXPORT_SYMBOL(cros_ec_resume);

#पूर्ण_अगर

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ChromeOS EC core driver");
