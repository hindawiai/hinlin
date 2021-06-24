<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**
 * drivers/extcon/extcon-usb-gpio.c - USB GPIO extcon driver
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - https://www.ti.com
 * Author: Roger Quadros <rogerq@ti.com>
 */

#समावेश <linux/extcon-provider.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/pinctrl/consumer.h>

#घोषणा USB_GPIO_DEBOUNCE_MS	20	/* ms */

काष्ठा usb_extcon_info अणु
	काष्ठा device *dev;
	काष्ठा extcon_dev *edev;

	काष्ठा gpio_desc *id_gpiod;
	काष्ठा gpio_desc *vbus_gpiod;
	पूर्णांक id_irq;
	पूर्णांक vbus_irq;

	अचिन्हित दीर्घ debounce_jअगरfies;
	काष्ठा delayed_work wq_detcable;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक usb_extcon_cable[] = अणु
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_NONE,
पूर्ण;

/*
 * "USB" = VBUS and "USB-HOST" = !ID, so we have:
 * Both "USB" and "USB-HOST" can't be set as active at the
 * same समय so अगर "USB-HOST" is active (i.e. ID is 0)  we keep "USB" inactive
 * even अगर VBUS is on.
 *
 *  State              |    ID   |   VBUS
 * ----------------------------------------
 *  [1] USB            |    H    |    H
 *  [2] none           |    H    |    L
 *  [3] USB-HOST       |    L    |    H
 *  [4] USB-HOST       |    L    |    L
 *
 * In हाल we have only one of these संकेतs:
 * - VBUS only - we want to distinguish between [1] and [2], so ID is always 1.
 * - ID only - we want to distinguish between [1] and [4], so VBUS = ID.
*/
अटल व्योम usb_extcon_detect_cable(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक id, vbus;
	काष्ठा usb_extcon_info *info = container_of(to_delayed_work(work),
						    काष्ठा usb_extcon_info,
						    wq_detcable);

	/* check ID and VBUS and update cable state */
	id = info->id_gpiod ?
		gpiod_get_value_cansleep(info->id_gpiod) : 1;
	vbus = info->vbus_gpiod ?
		gpiod_get_value_cansleep(info->vbus_gpiod) : id;

	/* at first we clean states which are no दीर्घer active */
	अगर (id)
		extcon_set_state_sync(info->edev, EXTCON_USB_HOST, false);
	अगर (!vbus)
		extcon_set_state_sync(info->edev, EXTCON_USB, false);

	अगर (!id) अणु
		extcon_set_state_sync(info->edev, EXTCON_USB_HOST, true);
	पूर्ण अन्यथा अणु
		अगर (vbus)
			extcon_set_state_sync(info->edev, EXTCON_USB, true);
	पूर्ण
पूर्ण

अटल irqवापस_t usb_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा usb_extcon_info *info = dev_id;

	queue_delayed_work(प्रणाली_घातer_efficient_wq, &info->wq_detcable,
			   info->debounce_jअगरfies);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक usb_extcon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा usb_extcon_info *info;
	पूर्णांक ret;

	अगर (!np)
		वापस -EINVAL;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->dev = dev;
	info->id_gpiod = devm_gpiod_get_optional(&pdev->dev, "id", GPIOD_IN);
	info->vbus_gpiod = devm_gpiod_get_optional(&pdev->dev, "vbus",
						   GPIOD_IN);

	अगर (!info->id_gpiod && !info->vbus_gpiod) अणु
		dev_err(dev, "failed to get gpios\n");
		वापस -ENODEV;
	पूर्ण

	अगर (IS_ERR(info->id_gpiod))
		वापस PTR_ERR(info->id_gpiod);

	अगर (IS_ERR(info->vbus_gpiod))
		वापस PTR_ERR(info->vbus_gpiod);

	info->edev = devm_extcon_dev_allocate(dev, usb_extcon_cable);
	अगर (IS_ERR(info->edev)) अणु
		dev_err(dev, "failed to allocate extcon device\n");
		वापस -ENOMEM;
	पूर्ण

	ret = devm_extcon_dev_रेजिस्टर(dev, info->edev);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to register extcon device\n");
		वापस ret;
	पूर्ण

	अगर (info->id_gpiod)
		ret = gpiod_set_debounce(info->id_gpiod,
					 USB_GPIO_DEBOUNCE_MS * 1000);
	अगर (!ret && info->vbus_gpiod)
		ret = gpiod_set_debounce(info->vbus_gpiod,
					 USB_GPIO_DEBOUNCE_MS * 1000);

	अगर (ret < 0)
		info->debounce_jअगरfies = msecs_to_jअगरfies(USB_GPIO_DEBOUNCE_MS);

	INIT_DELAYED_WORK(&info->wq_detcable, usb_extcon_detect_cable);

	अगर (info->id_gpiod) अणु
		info->id_irq = gpiod_to_irq(info->id_gpiod);
		अगर (info->id_irq < 0) अणु
			dev_err(dev, "failed to get ID IRQ\n");
			वापस info->id_irq;
		पूर्ण

		ret = devm_request_thपढ़ोed_irq(dev, info->id_irq, शून्य,
						usb_irq_handler,
						IRQF_TRIGGER_RISING |
						IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
						pdev->name, info);
		अगर (ret < 0) अणु
			dev_err(dev, "failed to request handler for ID IRQ\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (info->vbus_gpiod) अणु
		info->vbus_irq = gpiod_to_irq(info->vbus_gpiod);
		अगर (info->vbus_irq < 0) अणु
			dev_err(dev, "failed to get VBUS IRQ\n");
			वापस info->vbus_irq;
		पूर्ण

		ret = devm_request_thपढ़ोed_irq(dev, info->vbus_irq, शून्य,
						usb_irq_handler,
						IRQF_TRIGGER_RISING |
						IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
						pdev->name, info);
		अगर (ret < 0) अणु
			dev_err(dev, "failed to request handler for VBUS IRQ\n");
			वापस ret;
		पूर्ण
	पूर्ण

	platक्रमm_set_drvdata(pdev, info);
	device_set_wakeup_capable(&pdev->dev, true);

	/* Perक्रमm initial detection */
	usb_extcon_detect_cable(&info->wq_detcable.work);

	वापस 0;
पूर्ण

अटल पूर्णांक usb_extcon_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_extcon_info *info = platक्रमm_get_drvdata(pdev);

	cancel_delayed_work_sync(&info->wq_detcable);
	device_init_wakeup(&pdev->dev, false);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक usb_extcon_suspend(काष्ठा device *dev)
अणु
	काष्ठा usb_extcon_info *info = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (device_may_wakeup(dev)) अणु
		अगर (info->id_gpiod) अणु
			ret = enable_irq_wake(info->id_irq);
			अगर (ret)
				वापस ret;
		पूर्ण
		अगर (info->vbus_gpiod) अणु
			ret = enable_irq_wake(info->vbus_irq);
			अगर (ret) अणु
				अगर (info->id_gpiod)
					disable_irq_wake(info->id_irq);

				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * We करोn't want to process any IRQs after this poपूर्णांक
	 * as GPIOs used behind I2C subप्रणाली might not be
	 * accessible until resume completes. So disable IRQ.
	 */
	अगर (info->id_gpiod)
		disable_irq(info->id_irq);
	अगर (info->vbus_gpiod)
		disable_irq(info->vbus_irq);

	अगर (!device_may_wakeup(dev))
		pinctrl_pm_select_sleep_state(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक usb_extcon_resume(काष्ठा device *dev)
अणु
	काष्ठा usb_extcon_info *info = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	अगर (!device_may_wakeup(dev))
		pinctrl_pm_select_शेष_state(dev);

	अगर (device_may_wakeup(dev)) अणु
		अगर (info->id_gpiod) अणु
			ret = disable_irq_wake(info->id_irq);
			अगर (ret)
				वापस ret;
		पूर्ण
		अगर (info->vbus_gpiod) अणु
			ret = disable_irq_wake(info->vbus_irq);
			अगर (ret) अणु
				अगर (info->id_gpiod)
					enable_irq_wake(info->id_irq);

				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (info->id_gpiod)
		enable_irq(info->id_irq);
	अगर (info->vbus_gpiod)
		enable_irq(info->vbus_irq);

	queue_delayed_work(प्रणाली_घातer_efficient_wq,
			   &info->wq_detcable, 0);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(usb_extcon_pm_ops,
			 usb_extcon_suspend, usb_extcon_resume);

अटल स्थिर काष्ठा of_device_id usb_extcon_dt_match[] = अणु
	अणु .compatible = "linux,extcon-usb-gpio", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, usb_extcon_dt_match);

अटल स्थिर काष्ठा platक्रमm_device_id usb_extcon_platक्रमm_ids[] = अणु
	अणु .name = "extcon-usb-gpio", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, usb_extcon_platक्रमm_ids);

अटल काष्ठा platक्रमm_driver usb_extcon_driver = अणु
	.probe		= usb_extcon_probe,
	.हटाओ		= usb_extcon_हटाओ,
	.driver		= अणु
		.name	= "extcon-usb-gpio",
		.pm	= &usb_extcon_pm_ops,
		.of_match_table = usb_extcon_dt_match,
	पूर्ण,
	.id_table = usb_extcon_platक्रमm_ids,
पूर्ण;

module_platक्रमm_driver(usb_extcon_driver);

MODULE_AUTHOR("Roger Quadros <rogerq@ti.com>");
MODULE_DESCRIPTION("USB GPIO extcon driver");
MODULE_LICENSE("GPL v2");
