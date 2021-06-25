<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Support क्रम usb functionality of Hikey series boards
 * based on Hisilicon Kirin Soc.
 *
 * Copyright (C) 2017-2018 Hilisicon Electronics Co., Ltd.
 *		http://www.huawei.com
 *
 * Authors: Yu Chen <chenyu56@huawei.com>
 */

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb/role.h>

#घोषणा DEVICE_DRIVER_NAME "hisi_hikey_usb"

#घोषणा HUB_VBUS_POWER_ON 1
#घोषणा HUB_VBUS_POWER_OFF 0
#घोषणा USB_SWITCH_TO_HUB 1
#घोषणा USB_SWITCH_TO_TYPEC 0
#घोषणा TYPEC_VBUS_POWER_ON 1
#घोषणा TYPEC_VBUS_POWER_OFF 0

काष्ठा hisi_hikey_usb अणु
	काष्ठा device *dev;
	काष्ठा gpio_desc *otg_चयन;
	काष्ठा gpio_desc *typec_vbus;
	काष्ठा gpio_desc *hub_vbus;
	काष्ठा gpio_desc *reset;

	काष्ठा regulator *regulator;

	काष्ठा usb_role_चयन *hub_role_sw;

	काष्ठा usb_role_चयन *dev_role_sw;
	क्रमागत usb_role role;

	काष्ठा mutex lock;
	काष्ठा work_काष्ठा work;

	काष्ठा notअगरier_block nb;
पूर्ण;

अटल व्योम hub_घातer_ctrl(काष्ठा hisi_hikey_usb *hisi_hikey_usb, पूर्णांक value)
अणु
	पूर्णांक ret, status;

	अगर (hisi_hikey_usb->hub_vbus)
		gpiod_set_value_cansleep(hisi_hikey_usb->hub_vbus, value);

	अगर (!hisi_hikey_usb->regulator)
		वापस;

	status = regulator_is_enabled(hisi_hikey_usb->regulator);
	अगर (status == !!value)
		वापस;

	अगर (value)
		ret = regulator_enable(hisi_hikey_usb->regulator);
	अन्यथा
		ret = regulator_disable(hisi_hikey_usb->regulator);

	अगर (ret)
		dev_err(hisi_hikey_usb->dev,
			"Can't switch regulator state to %s\n",
			value ? "enabled" : "disabled");
पूर्ण

अटल व्योम usb_चयन_ctrl(काष्ठा hisi_hikey_usb *hisi_hikey_usb,
			    पूर्णांक चयन_to)
अणु
	अगर (!hisi_hikey_usb->otg_चयन)
		वापस;

	gpiod_set_value_cansleep(hisi_hikey_usb->otg_चयन, चयन_to);
पूर्ण

अटल व्योम usb_typec_घातer_ctrl(काष्ठा hisi_hikey_usb *hisi_hikey_usb,
				 पूर्णांक value)
अणु
	अगर (!hisi_hikey_usb->typec_vbus)
		वापस;

	gpiod_set_value_cansleep(hisi_hikey_usb->typec_vbus, value);
पूर्ण

अटल व्योम relay_set_role_चयन(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hisi_hikey_usb *hisi_hikey_usb = container_of(work,
							काष्ठा hisi_hikey_usb,
							work);
	काष्ठा usb_role_चयन *sw;
	क्रमागत usb_role role;

	अगर (!hisi_hikey_usb || !hisi_hikey_usb->dev_role_sw)
		वापस;

	mutex_lock(&hisi_hikey_usb->lock);
	चयन (hisi_hikey_usb->role) अणु
	हाल USB_ROLE_NONE:
		usb_typec_घातer_ctrl(hisi_hikey_usb, TYPEC_VBUS_POWER_OFF);
		usb_चयन_ctrl(hisi_hikey_usb, USB_SWITCH_TO_HUB);
		hub_घातer_ctrl(hisi_hikey_usb, HUB_VBUS_POWER_ON);
		अवरोध;
	हाल USB_ROLE_HOST:
		hub_घातer_ctrl(hisi_hikey_usb, HUB_VBUS_POWER_OFF);
		usb_चयन_ctrl(hisi_hikey_usb, USB_SWITCH_TO_TYPEC);
		usb_typec_घातer_ctrl(hisi_hikey_usb, TYPEC_VBUS_POWER_ON);
		अवरोध;
	हाल USB_ROLE_DEVICE:
		hub_घातer_ctrl(hisi_hikey_usb, HUB_VBUS_POWER_OFF);
		usb_typec_घातer_ctrl(hisi_hikey_usb, TYPEC_VBUS_POWER_OFF);
		usb_चयन_ctrl(hisi_hikey_usb, USB_SWITCH_TO_TYPEC);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	sw = hisi_hikey_usb->dev_role_sw;
	role = hisi_hikey_usb->role;
	mutex_unlock(&hisi_hikey_usb->lock);

	usb_role_चयन_set_role(sw, role);
पूर्ण

अटल पूर्णांक hub_usb_role_चयन_set(काष्ठा usb_role_चयन *sw, क्रमागत usb_role role)
अणु
	काष्ठा hisi_hikey_usb *hisi_hikey_usb = usb_role_चयन_get_drvdata(sw);

	अगर (!hisi_hikey_usb || !hisi_hikey_usb->dev_role_sw)
		वापस -EINVAL;

	mutex_lock(&hisi_hikey_usb->lock);
	hisi_hikey_usb->role = role;
	mutex_unlock(&hisi_hikey_usb->lock);

	schedule_work(&hisi_hikey_usb->work);

	वापस 0;
पूर्ण

अटल पूर्णांक hisi_hikey_usb_parse_kirin970(काष्ठा platक्रमm_device *pdev,
					 काष्ठा hisi_hikey_usb *hisi_hikey_usb)
अणु
	काष्ठा regulator *regulator;

	regulator = devm_regulator_get(&pdev->dev, "hub-vdd");
	अगर (IS_ERR(regulator)) अणु
		अगर (PTR_ERR(regulator) == -EPROBE_DEFER) अणु
			dev_info(&pdev->dev,
				 "waiting for hub-vdd-supply to be probed\n");
			वापस PTR_ERR(regulator);
		पूर्ण
		dev_err(&pdev->dev,
			"get hub-vdd-supply failed with error %ld\n",
			PTR_ERR(regulator));
		वापस PTR_ERR(regulator);
	पूर्ण
	hisi_hikey_usb->regulator = regulator;

	hisi_hikey_usb->reset = devm_gpiod_get(&pdev->dev, "hub_reset_en_gpio",
					       GPIOD_OUT_HIGH);
	वापस PTR_ERR_OR_ZERO(hisi_hikey_usb->reset);
पूर्ण

अटल पूर्णांक hisi_hikey_usb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा hisi_hikey_usb *hisi_hikey_usb;
	काष्ठा usb_role_चयन_desc hub_role_चयन = अणुशून्यपूर्ण;
	पूर्णांक ret;

	hisi_hikey_usb = devm_kzalloc(dev, माप(*hisi_hikey_usb), GFP_KERNEL);
	अगर (!hisi_hikey_usb)
		वापस -ENOMEM;

	hisi_hikey_usb->dev = &pdev->dev;

	hisi_hikey_usb->otg_चयन = devm_gpiod_get(dev, "otg-switch",
						    GPIOD_OUT_HIGH);
	अगर (IS_ERR(hisi_hikey_usb->otg_चयन))
		वापस PTR_ERR(hisi_hikey_usb->otg_चयन);

	hisi_hikey_usb->typec_vbus = devm_gpiod_get(dev, "typec-vbus",
						    GPIOD_OUT_LOW);
	अगर (IS_ERR(hisi_hikey_usb->typec_vbus))
		वापस PTR_ERR(hisi_hikey_usb->typec_vbus);

	/* Parse Kirin 970-specअगरic OF data */
	अगर (of_device_is_compatible(pdev->dev.of_node,
				    "hisilicon,kirin970_hikey_usbhub")) अणु
		ret = hisi_hikey_usb_parse_kirin970(pdev, hisi_hikey_usb);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		/* hub-vdd33-en is optional */
		hisi_hikey_usb->hub_vbus = devm_gpiod_get_optional(dev, "hub-vdd33-en",
								   GPIOD_OUT_HIGH);
		अगर (IS_ERR(hisi_hikey_usb->hub_vbus))
			वापस PTR_ERR(hisi_hikey_usb->hub_vbus);
	पूर्ण

	hisi_hikey_usb->dev_role_sw = usb_role_चयन_get(dev);
	अगर (!hisi_hikey_usb->dev_role_sw)
		वापस -EPROBE_DEFER;
	अगर (IS_ERR(hisi_hikey_usb->dev_role_sw))
		वापस PTR_ERR(hisi_hikey_usb->dev_role_sw);

	INIT_WORK(&hisi_hikey_usb->work, relay_set_role_चयन);
	mutex_init(&hisi_hikey_usb->lock);

	hub_role_चयन.fwnode = dev_fwnode(dev);
	hub_role_चयन.set = hub_usb_role_चयन_set;
	hub_role_चयन.driver_data = hisi_hikey_usb;

	hisi_hikey_usb->hub_role_sw = usb_role_चयन_रेजिस्टर(dev,
							       &hub_role_चयन);

	अगर (IS_ERR(hisi_hikey_usb->hub_role_sw)) अणु
		usb_role_चयन_put(hisi_hikey_usb->dev_role_sw);
		वापस PTR_ERR(hisi_hikey_usb->hub_role_sw);
	पूर्ण

	platक्रमm_set_drvdata(pdev, hisi_hikey_usb);

	वापस 0;
पूर्ण

अटल पूर्णांक  hisi_hikey_usb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा hisi_hikey_usb *hisi_hikey_usb = platक्रमm_get_drvdata(pdev);

	अगर (hisi_hikey_usb->hub_role_sw)
		usb_role_चयन_unरेजिस्टर(hisi_hikey_usb->hub_role_sw);

	अगर (hisi_hikey_usb->dev_role_sw)
		usb_role_चयन_put(hisi_hikey_usb->dev_role_sw);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id id_table_hisi_hikey_usb[] = अणु
	अणु .compatible = "hisilicon,gpio_hubv1" पूर्ण,
	अणु .compatible = "hisilicon,kirin970_hikey_usbhub" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, id_table_hisi_hikey_usb);

अटल काष्ठा platक्रमm_driver hisi_hikey_usb_driver = अणु
	.probe = hisi_hikey_usb_probe,
	.हटाओ = hisi_hikey_usb_हटाओ,
	.driver = अणु
		.name = DEVICE_DRIVER_NAME,
		.of_match_table = id_table_hisi_hikey_usb,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(hisi_hikey_usb_driver);

MODULE_AUTHOR("Yu Chen <chenyu56@huawei.com>");
MODULE_DESCRIPTION("Driver Support for USB functionality of Hikey");
MODULE_LICENSE("GPL v2");
