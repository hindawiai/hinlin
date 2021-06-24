<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Palmas USB transceiver driver
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - https://www.ti.com
 * Author: Graeme Gregory <gg@slimlogic.co.uk>
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 * Based on twl6030_usb.c
 * Author: Hema HK <hemahk@ti.com>
 */

#समावेश <linux/devm-helpers.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/mfd/palmas.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/workqueue.h>

#घोषणा USB_GPIO_DEBOUNCE_MS	20	/* ms */

अटल स्थिर अचिन्हित पूर्णांक palmas_extcon_cable[] = अणु
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_NONE,
पूर्ण;

अटल व्योम palmas_usb_wakeup(काष्ठा palmas *palmas, पूर्णांक enable)
अणु
	अगर (enable)
		palmas_ग_लिखो(palmas, PALMAS_USB_OTG_BASE, PALMAS_USB_WAKEUP,
			PALMAS_USB_WAKEUP_ID_WK_UP_COMP);
	अन्यथा
		palmas_ग_लिखो(palmas, PALMAS_USB_OTG_BASE, PALMAS_USB_WAKEUP, 0);
पूर्ण

अटल irqवापस_t palmas_vbus_irq_handler(पूर्णांक irq, व्योम *_palmas_usb)
अणु
	काष्ठा palmas_usb *palmas_usb = _palmas_usb;
	काष्ठा extcon_dev *edev = palmas_usb->edev;
	अचिन्हित पूर्णांक vbus_line_state;

	palmas_पढ़ो(palmas_usb->palmas, PALMAS_INTERRUPT_BASE,
		PALMAS_INT3_LINE_STATE, &vbus_line_state);

	अगर (vbus_line_state & PALMAS_INT3_LINE_STATE_VBUS) अणु
		अगर (palmas_usb->linkstat != PALMAS_USB_STATE_VBUS) अणु
			palmas_usb->linkstat = PALMAS_USB_STATE_VBUS;
			extcon_set_state_sync(edev, EXTCON_USB, true);
			dev_dbg(palmas_usb->dev, "USB cable is attached\n");
		पूर्ण अन्यथा अणु
			dev_dbg(palmas_usb->dev,
				"Spurious connect event detected\n");
		पूर्ण
	पूर्ण अन्यथा अगर (!(vbus_line_state & PALMAS_INT3_LINE_STATE_VBUS)) अणु
		अगर (palmas_usb->linkstat == PALMAS_USB_STATE_VBUS) अणु
			palmas_usb->linkstat = PALMAS_USB_STATE_DISCONNECT;
			extcon_set_state_sync(edev, EXTCON_USB, false);
			dev_dbg(palmas_usb->dev, "USB cable is detached\n");
		पूर्ण अन्यथा अणु
			dev_dbg(palmas_usb->dev,
				"Spurious disconnect event detected\n");
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t palmas_id_irq_handler(पूर्णांक irq, व्योम *_palmas_usb)
अणु
	अचिन्हित पूर्णांक set, id_src;
	काष्ठा palmas_usb *palmas_usb = _palmas_usb;
	काष्ठा extcon_dev *edev = palmas_usb->edev;

	palmas_पढ़ो(palmas_usb->palmas, PALMAS_USB_OTG_BASE,
		PALMAS_USB_ID_INT_LATCH_SET, &set);
	palmas_पढ़ो(palmas_usb->palmas, PALMAS_USB_OTG_BASE,
		PALMAS_USB_ID_INT_SRC, &id_src);

	अगर ((set & PALMAS_USB_ID_INT_SRC_ID_GND) &&
				(id_src & PALMAS_USB_ID_INT_SRC_ID_GND)) अणु
		palmas_ग_लिखो(palmas_usb->palmas, PALMAS_USB_OTG_BASE,
			PALMAS_USB_ID_INT_LATCH_CLR,
			PALMAS_USB_ID_INT_EN_HI_CLR_ID_GND);
		palmas_usb->linkstat = PALMAS_USB_STATE_ID;
		extcon_set_state_sync(edev, EXTCON_USB_HOST, true);
		dev_dbg(palmas_usb->dev, "USB-HOST cable is attached\n");
	पूर्ण अन्यथा अगर ((set & PALMAS_USB_ID_INT_SRC_ID_FLOAT) &&
				(id_src & PALMAS_USB_ID_INT_SRC_ID_FLOAT)) अणु
		palmas_ग_लिखो(palmas_usb->palmas, PALMAS_USB_OTG_BASE,
			PALMAS_USB_ID_INT_LATCH_CLR,
			PALMAS_USB_ID_INT_EN_HI_CLR_ID_FLOAT);
		palmas_usb->linkstat = PALMAS_USB_STATE_DISCONNECT;
		extcon_set_state_sync(edev, EXTCON_USB_HOST, false);
		dev_dbg(palmas_usb->dev, "USB-HOST cable is detached\n");
	पूर्ण अन्यथा अगर ((palmas_usb->linkstat == PALMAS_USB_STATE_ID) &&
				(!(set & PALMAS_USB_ID_INT_SRC_ID_GND))) अणु
		palmas_usb->linkstat = PALMAS_USB_STATE_DISCONNECT;
		extcon_set_state_sync(edev, EXTCON_USB_HOST, false);
		dev_dbg(palmas_usb->dev, "USB-HOST cable is detached\n");
	पूर्ण अन्यथा अगर ((palmas_usb->linkstat == PALMAS_USB_STATE_DISCONNECT) &&
				(id_src & PALMAS_USB_ID_INT_SRC_ID_GND)) अणु
		palmas_usb->linkstat = PALMAS_USB_STATE_ID;
		extcon_set_state_sync(edev, EXTCON_USB_HOST, true);
		dev_dbg(palmas_usb->dev, " USB-HOST cable is attached\n");
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम palmas_gpio_id_detect(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक id;
	काष्ठा palmas_usb *palmas_usb = container_of(to_delayed_work(work),
						     काष्ठा palmas_usb,
						     wq_detectid);
	काष्ठा extcon_dev *edev = palmas_usb->edev;

	अगर (!palmas_usb->id_gpiod)
		वापस;

	id = gpiod_get_value_cansleep(palmas_usb->id_gpiod);

	अगर (id) अणु
		extcon_set_state_sync(edev, EXTCON_USB_HOST, false);
		dev_dbg(palmas_usb->dev, "USB-HOST cable is detached\n");
	पूर्ण अन्यथा अणु
		extcon_set_state_sync(edev, EXTCON_USB_HOST, true);
		dev_dbg(palmas_usb->dev, "USB-HOST cable is attached\n");
	पूर्ण
पूर्ण

अटल irqवापस_t palmas_gpio_id_irq_handler(पूर्णांक irq, व्योम *_palmas_usb)
अणु
	काष्ठा palmas_usb *palmas_usb = _palmas_usb;

	queue_delayed_work(प्रणाली_घातer_efficient_wq, &palmas_usb->wq_detectid,
			   palmas_usb->sw_debounce_jअगरfies);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम palmas_enable_irq(काष्ठा palmas_usb *palmas_usb)
अणु
	palmas_ग_लिखो(palmas_usb->palmas, PALMAS_USB_OTG_BASE,
		PALMAS_USB_VBUS_CTRL_SET,
		PALMAS_USB_VBUS_CTRL_SET_VBUS_ACT_COMP);

	अगर (palmas_usb->enable_id_detection) अणु
		palmas_ग_लिखो(palmas_usb->palmas, PALMAS_USB_OTG_BASE,
			     PALMAS_USB_ID_CTRL_SET,
			     PALMAS_USB_ID_CTRL_SET_ID_ACT_COMP);

		palmas_ग_लिखो(palmas_usb->palmas, PALMAS_USB_OTG_BASE,
			     PALMAS_USB_ID_INT_EN_HI_SET,
			     PALMAS_USB_ID_INT_EN_HI_SET_ID_GND |
			     PALMAS_USB_ID_INT_EN_HI_SET_ID_FLOAT);
	पूर्ण

	अगर (palmas_usb->enable_vbus_detection)
		palmas_vbus_irq_handler(palmas_usb->vbus_irq, palmas_usb);

	/* cold plug क्रम host mode needs this delay */
	अगर (palmas_usb->enable_id_detection) अणु
		msleep(30);
		palmas_id_irq_handler(palmas_usb->id_irq, palmas_usb);
	पूर्ण
पूर्ण

अटल पूर्णांक palmas_usb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा palmas *palmas = dev_get_drvdata(pdev->dev.parent);
	काष्ठा palmas_usb_platक्रमm_data	*pdata = dev_get_platdata(&pdev->dev);
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा palmas_usb *palmas_usb;
	पूर्णांक status;

	अगर (!palmas) अणु
		dev_err(&pdev->dev, "failed to get valid parent\n");
		वापस -EINVAL;
	पूर्ण

	palmas_usb = devm_kzalloc(&pdev->dev, माप(*palmas_usb), GFP_KERNEL);
	अगर (!palmas_usb)
		वापस -ENOMEM;

	अगर (node && !pdata) अणु
		palmas_usb->wakeup = of_property_पढ़ो_bool(node, "ti,wakeup");
		palmas_usb->enable_id_detection = of_property_पढ़ो_bool(node,
						"ti,enable-id-detection");
		palmas_usb->enable_vbus_detection = of_property_पढ़ो_bool(node,
						"ti,enable-vbus-detection");
	पूर्ण अन्यथा अणु
		palmas_usb->wakeup = true;
		palmas_usb->enable_id_detection = true;
		palmas_usb->enable_vbus_detection = true;

		अगर (pdata)
			palmas_usb->wakeup = pdata->wakeup;
	पूर्ण

	palmas_usb->id_gpiod = devm_gpiod_get_optional(&pdev->dev, "id",
							GPIOD_IN);
	अगर (IS_ERR(palmas_usb->id_gpiod))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(palmas_usb->id_gpiod),
				     "failed to get id gpio\n");

	palmas_usb->vbus_gpiod = devm_gpiod_get_optional(&pdev->dev, "vbus",
							GPIOD_IN);
	अगर (IS_ERR(palmas_usb->vbus_gpiod))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(palmas_usb->vbus_gpiod),
				     "failed to get id gpio\n");

	अगर (palmas_usb->enable_id_detection && palmas_usb->id_gpiod) अणु
		palmas_usb->enable_id_detection = false;
		palmas_usb->enable_gpio_id_detection = true;
	पूर्ण

	अगर (palmas_usb->enable_vbus_detection && palmas_usb->vbus_gpiod) अणु
		palmas_usb->enable_vbus_detection = false;
		palmas_usb->enable_gpio_vbus_detection = true;
	पूर्ण

	अगर (palmas_usb->enable_gpio_id_detection) अणु
		u32 debounce;

		अगर (of_property_पढ़ो_u32(node, "debounce-delay-ms", &debounce))
			debounce = USB_GPIO_DEBOUNCE_MS;

		status = gpiod_set_debounce(palmas_usb->id_gpiod,
					    debounce * 1000);
		अगर (status < 0)
			palmas_usb->sw_debounce_jअगरfies = msecs_to_jअगरfies(debounce);
	पूर्ण

	status = devm_delayed_work_स्वतःcancel(&pdev->dev,
					      &palmas_usb->wq_detectid,
					      palmas_gpio_id_detect);
	अगर (status)
		वापस status;

	palmas->usb = palmas_usb;
	palmas_usb->palmas = palmas;

	palmas_usb->dev	 = &pdev->dev;

	palmas_usb_wakeup(palmas, palmas_usb->wakeup);

	platक्रमm_set_drvdata(pdev, palmas_usb);

	palmas_usb->edev = devm_extcon_dev_allocate(&pdev->dev,
						    palmas_extcon_cable);
	अगर (IS_ERR(palmas_usb->edev)) अणु
		dev_err(&pdev->dev, "failed to allocate extcon device\n");
		वापस -ENOMEM;
	पूर्ण

	status = devm_extcon_dev_रेजिस्टर(&pdev->dev, palmas_usb->edev);
	अगर (status) अणु
		dev_err(&pdev->dev, "failed to register extcon device\n");
		वापस status;
	पूर्ण

	अगर (palmas_usb->enable_id_detection) अणु
		palmas_usb->id_otg_irq = regmap_irq_get_virq(palmas->irq_data,
							     PALMAS_ID_OTG_IRQ);
		palmas_usb->id_irq = regmap_irq_get_virq(palmas->irq_data,
							 PALMAS_ID_IRQ);
		status = devm_request_thपढ़ोed_irq(palmas_usb->dev,
				palmas_usb->id_irq,
				शून्य, palmas_id_irq_handler,
				IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING |
				IRQF_ONESHOT,
				"palmas_usb_id", palmas_usb);
		अगर (status < 0) अणु
			dev_err(&pdev->dev, "can't get IRQ %d, err %d\n",
					palmas_usb->id_irq, status);
			वापस status;
		पूर्ण
	पूर्ण अन्यथा अगर (palmas_usb->enable_gpio_id_detection) अणु
		palmas_usb->gpio_id_irq = gpiod_to_irq(palmas_usb->id_gpiod);
		अगर (palmas_usb->gpio_id_irq < 0) अणु
			dev_err(&pdev->dev, "failed to get id irq\n");
			वापस palmas_usb->gpio_id_irq;
		पूर्ण
		status = devm_request_thपढ़ोed_irq(&pdev->dev,
						   palmas_usb->gpio_id_irq,
						   शून्य,
						   palmas_gpio_id_irq_handler,
						   IRQF_TRIGGER_RISING |
						   IRQF_TRIGGER_FALLING |
						   IRQF_ONESHOT,
						   "palmas_usb_id",
						   palmas_usb);
		अगर (status < 0) अणु
			dev_err(&pdev->dev,
				"failed to request handler for id irq\n");
			वापस status;
		पूर्ण
	पूर्ण

	अगर (palmas_usb->enable_vbus_detection) अणु
		palmas_usb->vbus_otg_irq = regmap_irq_get_virq(palmas->irq_data,
						       PALMAS_VBUS_OTG_IRQ);
		palmas_usb->vbus_irq = regmap_irq_get_virq(palmas->irq_data,
							   PALMAS_VBUS_IRQ);
		status = devm_request_thपढ़ोed_irq(palmas_usb->dev,
				palmas_usb->vbus_irq, शून्य,
				palmas_vbus_irq_handler,
				IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING |
				IRQF_ONESHOT,
				"palmas_usb_vbus", palmas_usb);
		अगर (status < 0) अणु
			dev_err(&pdev->dev, "can't get IRQ %d, err %d\n",
					palmas_usb->vbus_irq, status);
			वापस status;
		पूर्ण
	पूर्ण अन्यथा अगर (palmas_usb->enable_gpio_vbus_detection) अणु
		/* remux GPIO_1 as VBUSDET */
		status = palmas_update_bits(palmas,
			PALMAS_PU_PD_OD_BASE,
			PALMAS_PRIMARY_SECONDARY_PAD1,
			PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_1_MASK,
			(1 << PALMAS_PRIMARY_SECONDARY_PAD1_GPIO_1_SHIFT));
		अगर (status < 0) अणु
			dev_err(&pdev->dev, "can't remux GPIO1\n");
			वापस status;
		पूर्ण

		palmas_usb->vbus_otg_irq = regmap_irq_get_virq(palmas->irq_data,
						       PALMAS_VBUS_OTG_IRQ);
		palmas_usb->gpio_vbus_irq = gpiod_to_irq(palmas_usb->vbus_gpiod);
		अगर (palmas_usb->gpio_vbus_irq < 0) अणु
			dev_err(&pdev->dev, "failed to get vbus irq\n");
			वापस palmas_usb->gpio_vbus_irq;
		पूर्ण
		status = devm_request_thपढ़ोed_irq(&pdev->dev,
						palmas_usb->gpio_vbus_irq,
						शून्य,
						palmas_vbus_irq_handler,
						IRQF_TRIGGER_FALLING |
						IRQF_TRIGGER_RISING |
						IRQF_ONESHOT,
						"palmas_usb_vbus",
						palmas_usb);
		अगर (status < 0) अणु
			dev_err(&pdev->dev,
				"failed to request handler for vbus irq\n");
			वापस status;
		पूर्ण
	पूर्ण

	palmas_enable_irq(palmas_usb);
	/* perक्रमm initial detection */
	अगर (palmas_usb->enable_gpio_vbus_detection)
		palmas_vbus_irq_handler(palmas_usb->gpio_vbus_irq, palmas_usb);
	palmas_gpio_id_detect(&palmas_usb->wq_detectid.work);
	device_set_wakeup_capable(&pdev->dev, true);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक palmas_usb_suspend(काष्ठा device *dev)
अणु
	काष्ठा palmas_usb *palmas_usb = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev)) अणु
		अगर (palmas_usb->enable_vbus_detection)
			enable_irq_wake(palmas_usb->vbus_irq);
		अगर (palmas_usb->enable_gpio_vbus_detection)
			enable_irq_wake(palmas_usb->gpio_vbus_irq);
		अगर (palmas_usb->enable_id_detection)
			enable_irq_wake(palmas_usb->id_irq);
		अगर (palmas_usb->enable_gpio_id_detection)
			enable_irq_wake(palmas_usb->gpio_id_irq);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक palmas_usb_resume(काष्ठा device *dev)
अणु
	काष्ठा palmas_usb *palmas_usb = dev_get_drvdata(dev);

	अगर (device_may_wakeup(dev)) अणु
		अगर (palmas_usb->enable_vbus_detection)
			disable_irq_wake(palmas_usb->vbus_irq);
		अगर (palmas_usb->enable_gpio_vbus_detection)
			disable_irq_wake(palmas_usb->gpio_vbus_irq);
		अगर (palmas_usb->enable_id_detection)
			disable_irq_wake(palmas_usb->id_irq);
		अगर (palmas_usb->enable_gpio_id_detection)
			disable_irq_wake(palmas_usb->gpio_id_irq);
	पूर्ण

	/* check अगर GPIO states changed जबतक suspend/resume */
	अगर (palmas_usb->enable_gpio_vbus_detection)
		palmas_vbus_irq_handler(palmas_usb->gpio_vbus_irq, palmas_usb);
	palmas_gpio_id_detect(&palmas_usb->wq_detectid.work);

	वापस 0;
पूर्ण;
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(palmas_pm_ops, palmas_usb_suspend, palmas_usb_resume);

अटल स्थिर काष्ठा of_device_id of_palmas_match_tbl[] = अणु
	अणु .compatible = "ti,palmas-usb", पूर्ण,
	अणु .compatible = "ti,palmas-usb-vid", पूर्ण,
	अणु .compatible = "ti,twl6035-usb", पूर्ण,
	अणु .compatible = "ti,twl6035-usb-vid", पूर्ण,
	अणु /* end */ पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver palmas_usb_driver = अणु
	.probe = palmas_usb_probe,
	.driver = अणु
		.name = "palmas-usb",
		.of_match_table = of_palmas_match_tbl,
		.pm = &palmas_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(palmas_usb_driver);

MODULE_ALIAS("platform:palmas-usb");
MODULE_AUTHOR("Graeme Gregory <gg@slimlogic.co.uk>");
MODULE_DESCRIPTION("Palmas USB transceiver driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(of, of_palmas_match_tbl);
