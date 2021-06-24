<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**
 * extcon-qcom-spmi-misc.c - Qualcomm USB extcon driver to support USB ID
 *			and VBUS detection based on extcon-usb-gpio.c.
 *
 * Copyright (C) 2016 Linaro, Ltd.
 * Stephen Boyd <stephen.boyd@linaro.org>
 */

#समावेश <linux/devm-helpers.h>
#समावेश <linux/extcon-provider.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

#घोषणा USB_ID_DEBOUNCE_MS	5	/* ms */

काष्ठा qcom_usb_extcon_info अणु
	काष्ठा extcon_dev *edev;
	पूर्णांक id_irq;
	पूर्णांक vbus_irq;
	काष्ठा delayed_work wq_detcable;
	अचिन्हित दीर्घ debounce_jअगरfies;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक qcom_usb_extcon_cable[] = अणु
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_NONE,
पूर्ण;

अटल व्योम qcom_usb_extcon_detect_cable(काष्ठा work_काष्ठा *work)
अणु
	bool state = false;
	पूर्णांक ret;
	जोड़ extcon_property_value val;
	काष्ठा qcom_usb_extcon_info *info = container_of(to_delayed_work(work),
						    काष्ठा qcom_usb_extcon_info,
						    wq_detcable);

	अगर (info->id_irq > 0) अणु
		/* check ID and update cable state */
		ret = irq_get_irqchip_state(info->id_irq,
				IRQCHIP_STATE_LINE_LEVEL, &state);
		अगर (ret)
			वापस;

		अगर (!state) अणु
			val.पूर्णांकval = true;
			extcon_set_property(info->edev, EXTCON_USB_HOST,
						EXTCON_PROP_USB_SS, val);
		पूर्ण
		extcon_set_state_sync(info->edev, EXTCON_USB_HOST, !state);
	पूर्ण

	अगर (info->vbus_irq > 0) अणु
		/* check VBUS and update cable state */
		ret = irq_get_irqchip_state(info->vbus_irq,
				IRQCHIP_STATE_LINE_LEVEL, &state);
		अगर (ret)
			वापस;

		अगर (state) अणु
			val.पूर्णांकval = true;
			extcon_set_property(info->edev, EXTCON_USB,
						EXTCON_PROP_USB_SS, val);
		पूर्ण
		extcon_set_state_sync(info->edev, EXTCON_USB, state);
	पूर्ण
पूर्ण

अटल irqवापस_t qcom_usb_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा qcom_usb_extcon_info *info = dev_id;

	queue_delayed_work(प्रणाली_घातer_efficient_wq, &info->wq_detcable,
			   info->debounce_jअगरfies);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक qcom_usb_extcon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा qcom_usb_extcon_info *info;
	पूर्णांक ret;

	info = devm_kzalloc(dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->edev = devm_extcon_dev_allocate(dev, qcom_usb_extcon_cable);
	अगर (IS_ERR(info->edev)) अणु
		dev_err(dev, "failed to allocate extcon device\n");
		वापस -ENOMEM;
	पूर्ण

	ret = devm_extcon_dev_रेजिस्टर(dev, info->edev);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to register extcon device\n");
		वापस ret;
	पूर्ण

	ret = extcon_set_property_capability(info->edev,
			EXTCON_USB, EXTCON_PROP_USB_SS);
	ret |= extcon_set_property_capability(info->edev,
			EXTCON_USB_HOST, EXTCON_PROP_USB_SS);
	अगर (ret) अणु
		dev_err(dev, "failed to register extcon props rc=%d\n",
						ret);
		वापस ret;
	पूर्ण

	info->debounce_jअगरfies = msecs_to_jअगरfies(USB_ID_DEBOUNCE_MS);

	ret = devm_delayed_work_स्वतःcancel(dev, &info->wq_detcable,
					   qcom_usb_extcon_detect_cable);
	अगर (ret)
		वापस ret;

	info->id_irq = platक्रमm_get_irq_byname(pdev, "usb_id");
	अगर (info->id_irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(dev, info->id_irq, शून्य,
					qcom_usb_irq_handler,
					IRQF_TRIGGER_RISING |
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					pdev->name, info);
		अगर (ret < 0) अणु
			dev_err(dev, "failed to request handler for ID IRQ\n");
			वापस ret;
		पूर्ण
	पूर्ण

	info->vbus_irq = platक्रमm_get_irq_byname(pdev, "usb_vbus");
	अगर (info->vbus_irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(dev, info->vbus_irq, शून्य,
					qcom_usb_irq_handler,
					IRQF_TRIGGER_RISING |
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					pdev->name, info);
		अगर (ret < 0) अणु
			dev_err(dev, "failed to request handler for VBUS IRQ\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (info->id_irq < 0 && info->vbus_irq < 0) अणु
		dev_err(dev, "ID and VBUS IRQ not found\n");
		वापस -EINVAL;
	पूर्ण

	platक्रमm_set_drvdata(pdev, info);
	device_init_wakeup(dev, 1);

	/* Perक्रमm initial detection */
	qcom_usb_extcon_detect_cable(&info->wq_detcable.work);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक qcom_usb_extcon_suspend(काष्ठा device *dev)
अणु
	काष्ठा qcom_usb_extcon_info *info = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (device_may_wakeup(dev)) अणु
		अगर (info->id_irq > 0)
			ret = enable_irq_wake(info->id_irq);
		अगर (info->vbus_irq > 0)
			ret = enable_irq_wake(info->vbus_irq);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_usb_extcon_resume(काष्ठा device *dev)
अणु
	काष्ठा qcom_usb_extcon_info *info = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (device_may_wakeup(dev)) अणु
		अगर (info->id_irq > 0)
			ret = disable_irq_wake(info->id_irq);
		अगर (info->vbus_irq > 0)
			ret = disable_irq_wake(info->vbus_irq);
	पूर्ण

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(qcom_usb_extcon_pm_ops,
			 qcom_usb_extcon_suspend, qcom_usb_extcon_resume);

अटल स्थिर काष्ठा of_device_id qcom_usb_extcon_dt_match[] = अणु
	अणु .compatible = "qcom,pm8941-misc", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_usb_extcon_dt_match);

अटल काष्ठा platक्रमm_driver qcom_usb_extcon_driver = अणु
	.probe		= qcom_usb_extcon_probe,
	.driver		= अणु
		.name	= "extcon-pm8941-misc",
		.pm	= &qcom_usb_extcon_pm_ops,
		.of_match_table = qcom_usb_extcon_dt_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(qcom_usb_extcon_driver);

MODULE_DESCRIPTION("QCOM USB ID extcon driver");
MODULE_AUTHOR("Stephen Boyd <stephen.boyd@linaro.org>");
MODULE_LICENSE("GPL v2");
