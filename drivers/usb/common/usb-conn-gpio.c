<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB GPIO Based Connection Detection Driver
 *
 * Copyright (C) 2019 MediaTek Inc.
 *
 * Author: Chunfeng Yun <chunfeng.yun@mediatek.com>
 *
 * Some code borrowed from drivers/extcon/extcon-usb-gpio.c
 */

#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/usb/role.h>

#घोषणा USB_GPIO_DEB_MS		20	/* ms */
#घोषणा USB_GPIO_DEB_US		((USB_GPIO_DEB_MS) * 1000)	/* us */

#घोषणा USB_CONN_IRQF	\
	(IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING | IRQF_ONESHOT)

काष्ठा usb_conn_info अणु
	काष्ठा device *dev;
	काष्ठा usb_role_चयन *role_sw;
	क्रमागत usb_role last_role;
	काष्ठा regulator *vbus;
	काष्ठा delayed_work dw_det;
	अचिन्हित दीर्घ debounce_jअगरfies;

	काष्ठा gpio_desc *id_gpiod;
	काष्ठा gpio_desc *vbus_gpiod;
	पूर्णांक id_irq;
	पूर्णांक vbus_irq;

	काष्ठा घातer_supply_desc desc;
	काष्ठा घातer_supply *अक्षरger;
पूर्ण;

/*
 * "DEVICE" = VBUS and "HOST" = !ID, so we have:
 * Both "DEVICE" and "HOST" can't be set as active at the same समय
 * so अगर "HOST" is active (i.e. ID is 0)  we keep "DEVICE" inactive
 * even अगर VBUS is on.
 *
 *  Role          |   ID  |  VBUS
 * ------------------------------------
 *  [1] DEVICE    |   H   |   H
 *  [2] NONE      |   H   |   L
 *  [3] HOST      |   L   |   H
 *  [4] HOST      |   L   |   L
 *
 * In हाल we have only one of these संकेतs:
 * - VBUS only - we want to distinguish between [1] and [2], so ID is always 1
 * - ID only - we want to distinguish between [1] and [4], so VBUS = ID
 */
अटल व्योम usb_conn_detect_cable(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा usb_conn_info *info;
	क्रमागत usb_role role;
	पूर्णांक id, vbus, ret;

	info = container_of(to_delayed_work(work),
			    काष्ठा usb_conn_info, dw_det);

	/* check ID and VBUS */
	id = info->id_gpiod ?
		gpiod_get_value_cansleep(info->id_gpiod) : 1;
	vbus = info->vbus_gpiod ?
		gpiod_get_value_cansleep(info->vbus_gpiod) : id;

	अगर (!id)
		role = USB_ROLE_HOST;
	अन्यथा अगर (vbus)
		role = USB_ROLE_DEVICE;
	अन्यथा
		role = USB_ROLE_NONE;

	dev_dbg(info->dev, "role %d/%d, gpios: id %d, vbus %d\n",
		info->last_role, role, id, vbus);

	अगर (info->last_role == role) अणु
		dev_warn(info->dev, "repeated role: %d\n", role);
		वापस;
	पूर्ण

	अगर (info->last_role == USB_ROLE_HOST && info->vbus)
		regulator_disable(info->vbus);

	ret = usb_role_चयन_set_role(info->role_sw, role);
	अगर (ret)
		dev_err(info->dev, "failed to set role: %d\n", ret);

	अगर (role == USB_ROLE_HOST && info->vbus) अणु
		ret = regulator_enable(info->vbus);
		अगर (ret)
			dev_err(info->dev, "enable vbus regulator failed\n");
	पूर्ण

	info->last_role = role;

	अगर (info->vbus)
		dev_dbg(info->dev, "vbus regulator is %s\n",
			regulator_is_enabled(info->vbus) ? "enabled" : "disabled");

	घातer_supply_changed(info->अक्षरger);
पूर्ण

अटल व्योम usb_conn_queue_dwork(काष्ठा usb_conn_info *info,
				 अचिन्हित दीर्घ delay)
अणु
	queue_delayed_work(प्रणाली_घातer_efficient_wq, &info->dw_det, delay);
पूर्ण

अटल irqवापस_t usb_conn_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा usb_conn_info *info = dev_id;

	usb_conn_queue_dwork(info, info->debounce_jअगरfies);

	वापस IRQ_HANDLED;
पूर्ण

अटल क्रमागत घातer_supply_property usb_अक्षरger_properties[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
पूर्ण;

अटल पूर्णांक usb_अक्षरger_get_property(काष्ठा घातer_supply *psy,
				    क्रमागत घातer_supply_property psp,
				    जोड़ घातer_supply_propval *val)
अणु
	काष्ठा usb_conn_info *info = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = info->last_role == USB_ROLE_DEVICE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक usb_conn_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा घातer_supply_desc *desc;
	काष्ठा usb_conn_info *info;
	काष्ठा घातer_supply_config cfg = अणु
		.of_node = dev->of_node,
	पूर्ण;
	bool need_vbus = true;
	पूर्णांक ret = 0;

	info = devm_kzalloc(dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	info->dev = dev;
	info->id_gpiod = devm_gpiod_get_optional(dev, "id", GPIOD_IN);
	अगर (IS_ERR(info->id_gpiod))
		वापस PTR_ERR(info->id_gpiod);

	info->vbus_gpiod = devm_gpiod_get_optional(dev, "vbus", GPIOD_IN);
	अगर (IS_ERR(info->vbus_gpiod))
		वापस PTR_ERR(info->vbus_gpiod);

	अगर (!info->id_gpiod && !info->vbus_gpiod) अणु
		dev_err(dev, "failed to get gpios\n");
		वापस -ENODEV;
	पूर्ण

	अगर (info->id_gpiod)
		ret = gpiod_set_debounce(info->id_gpiod, USB_GPIO_DEB_US);
	अगर (!ret && info->vbus_gpiod)
		ret = gpiod_set_debounce(info->vbus_gpiod, USB_GPIO_DEB_US);
	अगर (ret < 0)
		info->debounce_jअगरfies = msecs_to_jअगरfies(USB_GPIO_DEB_MS);

	INIT_DELAYED_WORK(&info->dw_det, usb_conn_detect_cable);

	/*
	 * If the USB connector is a child of a USB port and that port alपढ़ोy provides the VBUS
	 * supply, there's no need क्रम the USB connector to provide it again.
	 */
	अगर (dev->parent && dev->parent->of_node) अणु
		अगर (of_find_property(dev->parent->of_node, "vbus-supply", शून्य))
			need_vbus = false;
	पूर्ण

	अगर (!need_vbus) अणु
		info->vbus = devm_regulator_get_optional(dev, "vbus");
		अगर (PTR_ERR(info->vbus) == -ENODEV)
			info->vbus = शून्य;
	पूर्ण अन्यथा अणु
		info->vbus = devm_regulator_get(dev, "vbus");
	पूर्ण

	अगर (IS_ERR(info->vbus)) अणु
		अगर (PTR_ERR(info->vbus) != -EPROBE_DEFER)
			dev_err(dev, "failed to get vbus: %ld\n", PTR_ERR(info->vbus));
		वापस PTR_ERR(info->vbus);
	पूर्ण

	info->role_sw = usb_role_चयन_get(dev);
	अगर (IS_ERR(info->role_sw)) अणु
		अगर (PTR_ERR(info->role_sw) != -EPROBE_DEFER)
			dev_err(dev, "failed to get role switch\n");

		वापस PTR_ERR(info->role_sw);
	पूर्ण

	अगर (info->id_gpiod) अणु
		info->id_irq = gpiod_to_irq(info->id_gpiod);
		अगर (info->id_irq < 0) अणु
			dev_err(dev, "failed to get ID IRQ\n");
			ret = info->id_irq;
			जाओ put_role_sw;
		पूर्ण

		ret = devm_request_thपढ़ोed_irq(dev, info->id_irq, शून्य,
						usb_conn_isr, USB_CONN_IRQF,
						pdev->name, info);
		अगर (ret < 0) अणु
			dev_err(dev, "failed to request ID IRQ\n");
			जाओ put_role_sw;
		पूर्ण
	पूर्ण

	अगर (info->vbus_gpiod) अणु
		info->vbus_irq = gpiod_to_irq(info->vbus_gpiod);
		अगर (info->vbus_irq < 0) अणु
			dev_err(dev, "failed to get VBUS IRQ\n");
			ret = info->vbus_irq;
			जाओ put_role_sw;
		पूर्ण

		ret = devm_request_thपढ़ोed_irq(dev, info->vbus_irq, शून्य,
						usb_conn_isr, USB_CONN_IRQF,
						pdev->name, info);
		अगर (ret < 0) अणु
			dev_err(dev, "failed to request VBUS IRQ\n");
			जाओ put_role_sw;
		पूर्ण
	पूर्ण

	desc = &info->desc;
	desc->name = "usb-charger";
	desc->properties = usb_अक्षरger_properties;
	desc->num_properties = ARRAY_SIZE(usb_अक्षरger_properties);
	desc->get_property = usb_अक्षरger_get_property;
	desc->type = POWER_SUPPLY_TYPE_USB;
	cfg.drv_data = info;

	info->अक्षरger = devm_घातer_supply_रेजिस्टर(dev, desc, &cfg);
	अगर (IS_ERR(info->अक्षरger)) अणु
		dev_err(dev, "Unable to register charger\n");
		वापस PTR_ERR(info->अक्षरger);
	पूर्ण

	platक्रमm_set_drvdata(pdev, info);

	/* Perक्रमm initial detection */
	usb_conn_queue_dwork(info, 0);

	वापस 0;

put_role_sw:
	usb_role_चयन_put(info->role_sw);
	वापस ret;
पूर्ण

अटल पूर्णांक usb_conn_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usb_conn_info *info = platक्रमm_get_drvdata(pdev);

	cancel_delayed_work_sync(&info->dw_det);

	अगर (info->last_role == USB_ROLE_HOST && info->vbus)
		regulator_disable(info->vbus);

	usb_role_चयन_put(info->role_sw);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused usb_conn_suspend(काष्ठा device *dev)
अणु
	काष्ठा usb_conn_info *info = dev_get_drvdata(dev);

	अगर (info->id_gpiod)
		disable_irq(info->id_irq);
	अगर (info->vbus_gpiod)
		disable_irq(info->vbus_irq);

	pinctrl_pm_select_sleep_state(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused usb_conn_resume(काष्ठा device *dev)
अणु
	काष्ठा usb_conn_info *info = dev_get_drvdata(dev);

	pinctrl_pm_select_शेष_state(dev);

	अगर (info->id_gpiod)
		enable_irq(info->id_irq);
	अगर (info->vbus_gpiod)
		enable_irq(info->vbus_irq);

	usb_conn_queue_dwork(info, 0);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(usb_conn_pm_ops,
			 usb_conn_suspend, usb_conn_resume);

अटल स्थिर काष्ठा of_device_id usb_conn_dt_match[] = अणु
	अणु .compatible = "gpio-usb-b-connector", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, usb_conn_dt_match);

अटल काष्ठा platक्रमm_driver usb_conn_driver = अणु
	.probe		= usb_conn_probe,
	.हटाओ		= usb_conn_हटाओ,
	.driver		= अणु
		.name	= "usb-conn-gpio",
		.pm	= &usb_conn_pm_ops,
		.of_match_table = usb_conn_dt_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(usb_conn_driver);

MODULE_AUTHOR("Chunfeng Yun <chunfeng.yun@mediatek.com>");
MODULE_DESCRIPTION("USB GPIO based connection detection driver");
MODULE_LICENSE("GPL v2");
