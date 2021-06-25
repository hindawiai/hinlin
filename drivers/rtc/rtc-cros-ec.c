<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// RTC driver क्रम ChromeOS Embedded Controller.
//
// Copyright (C) 2017 Google, Inc.
// Author: Stephen Barber <smbarber@chromium.org>

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/cros_ec_commands.h>
#समावेश <linux/platक्रमm_data/cros_ec_proto.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rtc.h>
#समावेश <linux/slab.h>

#घोषणा DRV_NAME	"cros-ec-rtc"

/**
 * काष्ठा cros_ec_rtc - Driver data क्रम EC RTC
 *
 * @cros_ec: Poपूर्णांकer to EC device
 * @rtc: Poपूर्णांकer to RTC device
 * @notअगरier: Notअगरier info क्रम responding to EC events
 * @saved_alarm: Alarm to restore when पूर्णांकerrupts are reenabled
 */
काष्ठा cros_ec_rtc अणु
	काष्ठा cros_ec_device *cros_ec;
	काष्ठा rtc_device *rtc;
	काष्ठा notअगरier_block notअगरier;
	u32 saved_alarm;
पूर्ण;

अटल पूर्णांक cros_ec_rtc_get(काष्ठा cros_ec_device *cros_ec, u32 command,
			   u32 *response)
अणु
	पूर्णांक ret;
	काष्ठा अणु
		काष्ठा cros_ec_command msg;
		काष्ठा ec_response_rtc data;
	पूर्ण __packed msg;

	स_रखो(&msg, 0, माप(msg));
	msg.msg.command = command;
	msg.msg.insize = माप(msg.data);

	ret = cros_ec_cmd_xfer_status(cros_ec, &msg.msg);
	अगर (ret < 0) अणु
		dev_err(cros_ec->dev,
			"error getting %s from EC: %d\n",
			command == EC_CMD_RTC_GET_VALUE ? "time" : "alarm",
			ret);
		वापस ret;
	पूर्ण

	*response = msg.data.समय;

	वापस 0;
पूर्ण

अटल पूर्णांक cros_ec_rtc_set(काष्ठा cros_ec_device *cros_ec, u32 command,
			   u32 param)
अणु
	पूर्णांक ret = 0;
	काष्ठा अणु
		काष्ठा cros_ec_command msg;
		काष्ठा ec_response_rtc data;
	पूर्ण __packed msg;

	स_रखो(&msg, 0, माप(msg));
	msg.msg.command = command;
	msg.msg.outsize = माप(msg.data);
	msg.data.समय = param;

	ret = cros_ec_cmd_xfer_status(cros_ec, &msg.msg);
	अगर (ret < 0) अणु
		dev_err(cros_ec->dev, "error setting %s on EC: %d\n",
			command == EC_CMD_RTC_SET_VALUE ? "time" : "alarm",
			ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* Read the current समय from the EC. */
अटल पूर्णांक cros_ec_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा cros_ec_rtc *cros_ec_rtc = dev_get_drvdata(dev);
	काष्ठा cros_ec_device *cros_ec = cros_ec_rtc->cros_ec;
	पूर्णांक ret;
	u32 समय;

	ret = cros_ec_rtc_get(cros_ec, EC_CMD_RTC_GET_VALUE, &समय);
	अगर (ret) अणु
		dev_err(dev, "error getting time: %d\n", ret);
		वापस ret;
	पूर्ण

	rtc_समय64_to_पंचांग(समय, पंचांग);

	वापस 0;
पूर्ण

/* Set the current EC समय. */
अटल पूर्णांक cros_ec_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	काष्ठा cros_ec_rtc *cros_ec_rtc = dev_get_drvdata(dev);
	काष्ठा cros_ec_device *cros_ec = cros_ec_rtc->cros_ec;
	पूर्णांक ret;
	समय64_t समय = rtc_पंचांग_to_समय64(पंचांग);

	ret = cros_ec_rtc_set(cros_ec, EC_CMD_RTC_SET_VALUE, (u32)समय);
	अगर (ret < 0) अणु
		dev_err(dev, "error setting time: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/* Read alarm समय from RTC. */
अटल पूर्णांक cros_ec_rtc_पढ़ो_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा cros_ec_rtc *cros_ec_rtc = dev_get_drvdata(dev);
	काष्ठा cros_ec_device *cros_ec = cros_ec_rtc->cros_ec;
	पूर्णांक ret;
	u32 current_समय, alarm_offset;

	/*
	 * The EC host command क्रम getting the alarm is relative (i.e. 5
	 * seconds from now) whereas rtc_wkalrm is असलolute. Get the current
	 * RTC समय first so we can calculate the relative समय.
	 */
	ret = cros_ec_rtc_get(cros_ec, EC_CMD_RTC_GET_VALUE, &current_समय);
	अगर (ret < 0) अणु
		dev_err(dev, "error getting time: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = cros_ec_rtc_get(cros_ec, EC_CMD_RTC_GET_ALARM, &alarm_offset);
	अगर (ret < 0) अणु
		dev_err(dev, "error getting alarm: %d\n", ret);
		वापस ret;
	पूर्ण

	rtc_समय64_to_पंचांग(current_समय + alarm_offset, &alrm->समय);

	वापस 0;
पूर्ण

/* Set the EC's RTC alarm. */
अटल पूर्णांक cros_ec_rtc_set_alarm(काष्ठा device *dev, काष्ठा rtc_wkalrm *alrm)
अणु
	काष्ठा cros_ec_rtc *cros_ec_rtc = dev_get_drvdata(dev);
	काष्ठा cros_ec_device *cros_ec = cros_ec_rtc->cros_ec;
	पूर्णांक ret;
	समय64_t alarm_समय;
	u32 current_समय, alarm_offset;

	/*
	 * The EC host command क्रम setting the alarm is relative
	 * (i.e. 5 seconds from now) whereas rtc_wkalrm is असलolute.
	 * Get the current RTC समय first so we can calculate the
	 * relative समय.
	 */
	ret = cros_ec_rtc_get(cros_ec, EC_CMD_RTC_GET_VALUE, &current_समय);
	अगर (ret < 0) अणु
		dev_err(dev, "error getting time: %d\n", ret);
		वापस ret;
	पूर्ण

	alarm_समय = rtc_पंचांग_to_समय64(&alrm->समय);

	अगर (alarm_समय < 0 || alarm_समय > U32_MAX)
		वापस -EINVAL;

	अगर (!alrm->enabled) अणु
		/*
		 * If the alarm is being disabled, send an alarm
		 * clear command.
		 */
		alarm_offset = EC_RTC_ALARM_CLEAR;
		cros_ec_rtc->saved_alarm = (u32)alarm_समय;
	पूर्ण अन्यथा अणु
		/* Don't set an alarm in the past. */
		अगर ((u32)alarm_समय <= current_समय)
			वापस -ETIME;

		alarm_offset = (u32)alarm_समय - current_समय;
	पूर्ण

	ret = cros_ec_rtc_set(cros_ec, EC_CMD_RTC_SET_ALARM, alarm_offset);
	अगर (ret < 0) अणु
		dev_err(dev, "error setting alarm: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cros_ec_rtc_alarm_irq_enable(काष्ठा device *dev,
					अचिन्हित पूर्णांक enabled)
अणु
	काष्ठा cros_ec_rtc *cros_ec_rtc = dev_get_drvdata(dev);
	काष्ठा cros_ec_device *cros_ec = cros_ec_rtc->cros_ec;
	पूर्णांक ret;
	u32 current_समय, alarm_offset, alarm_value;

	ret = cros_ec_rtc_get(cros_ec, EC_CMD_RTC_GET_VALUE, &current_समय);
	अगर (ret < 0) अणु
		dev_err(dev, "error getting time: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (enabled) अणु
		/* Restore saved alarm अगर it's still in the future. */
		अगर (cros_ec_rtc->saved_alarm < current_समय)
			alarm_offset = EC_RTC_ALARM_CLEAR;
		अन्यथा
			alarm_offset = cros_ec_rtc->saved_alarm - current_समय;

		ret = cros_ec_rtc_set(cros_ec, EC_CMD_RTC_SET_ALARM,
				      alarm_offset);
		अगर (ret < 0) अणु
			dev_err(dev, "error restoring alarm: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Disable alarm, saving the old alarm value. */
		ret = cros_ec_rtc_get(cros_ec, EC_CMD_RTC_GET_ALARM,
				      &alarm_offset);
		अगर (ret < 0) अणु
			dev_err(dev, "error saving alarm: %d\n", ret);
			वापस ret;
		पूर्ण

		alarm_value = current_समय + alarm_offset;

		/*
		 * If the current EC alarm is alपढ़ोy past, we करोn't want
		 * to set an alarm when we go through the alarm irq enable
		 * path.
		 */
		अगर (alarm_value < current_समय)
			cros_ec_rtc->saved_alarm = EC_RTC_ALARM_CLEAR;
		अन्यथा
			cros_ec_rtc->saved_alarm = alarm_value;

		alarm_offset = EC_RTC_ALARM_CLEAR;
		ret = cros_ec_rtc_set(cros_ec, EC_CMD_RTC_SET_ALARM,
				      alarm_offset);
		अगर (ret < 0) अणु
			dev_err(dev, "error disabling alarm: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cros_ec_rtc_event(काष्ठा notअगरier_block *nb,
			     अचिन्हित दीर्घ queued_during_suspend,
			     व्योम *_notअगरy)
अणु
	काष्ठा cros_ec_rtc *cros_ec_rtc;
	काष्ठा rtc_device *rtc;
	काष्ठा cros_ec_device *cros_ec;
	u32 host_event;

	cros_ec_rtc = container_of(nb, काष्ठा cros_ec_rtc, notअगरier);
	rtc = cros_ec_rtc->rtc;
	cros_ec = cros_ec_rtc->cros_ec;

	host_event = cros_ec_get_host_event(cros_ec);
	अगर (host_event & EC_HOST_EVENT_MASK(EC_HOST_EVENT_RTC)) अणु
		rtc_update_irq(rtc, 1, RTC_IRQF | RTC_AF);
		वापस NOTIFY_OK;
	पूर्ण अन्यथा अणु
		वापस NOTIFY_DONE;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops cros_ec_rtc_ops = अणु
	.पढ़ो_समय = cros_ec_rtc_पढ़ो_समय,
	.set_समय = cros_ec_rtc_set_समय,
	.पढ़ो_alarm = cros_ec_rtc_पढ़ो_alarm,
	.set_alarm = cros_ec_rtc_set_alarm,
	.alarm_irq_enable = cros_ec_rtc_alarm_irq_enable,
पूर्ण;

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक cros_ec_rtc_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा cros_ec_rtc *cros_ec_rtc = dev_get_drvdata(&pdev->dev);

	अगर (device_may_wakeup(dev))
		वापस enable_irq_wake(cros_ec_rtc->cros_ec->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक cros_ec_rtc_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा cros_ec_rtc *cros_ec_rtc = dev_get_drvdata(&pdev->dev);

	अगर (device_may_wakeup(dev))
		वापस disable_irq_wake(cros_ec_rtc->cros_ec->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(cros_ec_rtc_pm_ops, cros_ec_rtc_suspend,
			 cros_ec_rtc_resume);

अटल पूर्णांक cros_ec_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cros_ec_dev *ec_dev = dev_get_drvdata(pdev->dev.parent);
	काष्ठा cros_ec_device *cros_ec = ec_dev->ec_dev;
	काष्ठा cros_ec_rtc *cros_ec_rtc;
	काष्ठा rtc_समय पंचांग;
	पूर्णांक ret;

	cros_ec_rtc = devm_kzalloc(&pdev->dev, माप(*cros_ec_rtc),
				   GFP_KERNEL);
	अगर (!cros_ec_rtc)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, cros_ec_rtc);
	cros_ec_rtc->cros_ec = cros_ec;

	/* Get initial समय */
	ret = cros_ec_rtc_पढ़ो_समय(&pdev->dev, &पंचांग);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to read RTC time\n");
		वापस ret;
	पूर्ण

	ret = device_init_wakeup(&pdev->dev, 1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to initialize wakeup\n");
		वापस ret;
	पूर्ण

	cros_ec_rtc->rtc = devm_rtc_allocate_device(&pdev->dev);
	अगर (IS_ERR(cros_ec_rtc->rtc))
		वापस PTR_ERR(cros_ec_rtc->rtc);

	cros_ec_rtc->rtc->ops = &cros_ec_rtc_ops;
	cros_ec_rtc->rtc->range_max = U32_MAX;

	ret = devm_rtc_रेजिस्टर_device(cros_ec_rtc->rtc);
	अगर (ret)
		वापस ret;

	/* Get RTC events from the EC. */
	cros_ec_rtc->notअगरier.notअगरier_call = cros_ec_rtc_event;
	ret = blocking_notअगरier_chain_रेजिस्टर(&cros_ec->event_notअगरier,
					       &cros_ec_rtc->notअगरier);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register notifier\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cros_ec_rtc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cros_ec_rtc *cros_ec_rtc = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	ret = blocking_notअगरier_chain_unरेजिस्टर(
				&cros_ec_rtc->cros_ec->event_notअगरier,
				&cros_ec_rtc->notअगरier);
	अगर (ret) अणु
		dev_err(dev, "failed to unregister notifier\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver cros_ec_rtc_driver = अणु
	.probe = cros_ec_rtc_probe,
	.हटाओ = cros_ec_rtc_हटाओ,
	.driver = अणु
		.name = DRV_NAME,
		.pm = &cros_ec_rtc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(cros_ec_rtc_driver);

MODULE_DESCRIPTION("RTC driver for Chrome OS ECs");
MODULE_AUTHOR("Stephen Barber <smbarber@chromium.org>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
