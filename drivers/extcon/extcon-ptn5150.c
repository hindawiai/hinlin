<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// extcon-ptn5150.c - PTN5150 CC logic extcon driver to support USB detection
//
// Based on extcon-sm5502.c driver
// Copyright (c) 2018-2019 by Vijai Kumar K
// Author: Vijai Kumar K <vijaikumar.kanagarajan@gmail.com>
// Copyright (c) 2020 Krzysztof Kozlowski <krzk@kernel.org>

#समावेश <linux/bitfield.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/extcon-provider.h>
#समावेश <linux/gpio/consumer.h>

/* PTN5150 रेजिस्टरs */
#घोषणा PTN5150_REG_DEVICE_ID			0x01
#घोषणा PTN5150_REG_CONTROL			0x02
#घोषणा PTN5150_REG_INT_STATUS			0x03
#घोषणा PTN5150_REG_CC_STATUS			0x04
#घोषणा PTN5150_REG_CON_DET			0x09
#घोषणा PTN5150_REG_VCONN_STATUS		0x0a
#घोषणा PTN5150_REG_RESET			0x0b
#घोषणा PTN5150_REG_INT_MASK			0x18
#घोषणा PTN5150_REG_INT_REG_STATUS		0x19
#घोषणा PTN5150_REG_END				PTN5150_REG_INT_REG_STATUS

#घोषणा PTN5150_DFP_ATTACHED			0x1
#घोषणा PTN5150_UFP_ATTACHED			0x2

/* Define PTN5150 MASK/SHIFT स्थिरant */
#घोषणा PTN5150_REG_DEVICE_ID_VERSION		GENMASK(7, 3)
#घोषणा PTN5150_REG_DEVICE_ID_VENDOR		GENMASK(2, 0)

#घोषणा PTN5150_REG_CC_PORT_ATTACHMENT		GENMASK(4, 2)
#घोषणा PTN5150_REG_CC_VBUS_DETECTION		BIT(7)
#घोषणा PTN5150_REG_INT_CABLE_ATTACH_MASK	BIT(0)
#घोषणा PTN5150_REG_INT_CABLE_DETACH_MASK	BIT(1)

काष्ठा ptn5150_info अणु
	काष्ठा device *dev;
	काष्ठा extcon_dev *edev;
	काष्ठा i2c_client *i2c;
	काष्ठा regmap *regmap;
	काष्ठा gpio_desc *पूर्णांक_gpiod;
	काष्ठा gpio_desc *vbus_gpiod;
	पूर्णांक irq;
	काष्ठा work_काष्ठा irq_work;
	काष्ठा mutex mutex;
पूर्ण;

/* List of detectable cables */
अटल स्थिर अचिन्हित पूर्णांक ptn5150_extcon_cable[] = अणु
	EXTCON_USB,
	EXTCON_USB_HOST,
	EXTCON_NONE,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ptn5150_regmap_config = अणु
	.reg_bits	= 8,
	.val_bits	= 8,
	.max_रेजिस्टर	= PTN5150_REG_END,
पूर्ण;

अटल व्योम ptn5150_check_state(काष्ठा ptn5150_info *info)
अणु
	अचिन्हित पूर्णांक port_status, reg_data, vbus;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, PTN5150_REG_CC_STATUS, &reg_data);
	अगर (ret) अणु
		dev_err(info->dev, "failed to read CC STATUS %d\n", ret);
		वापस;
	पूर्ण

	port_status = FIELD_GET(PTN5150_REG_CC_PORT_ATTACHMENT, reg_data);

	चयन (port_status) अणु
	हाल PTN5150_DFP_ATTACHED:
		extcon_set_state_sync(info->edev, EXTCON_USB_HOST, false);
		gpiod_set_value_cansleep(info->vbus_gpiod, 0);
		extcon_set_state_sync(info->edev, EXTCON_USB, true);
		अवरोध;
	हाल PTN5150_UFP_ATTACHED:
		extcon_set_state_sync(info->edev, EXTCON_USB, false);
		vbus = FIELD_GET(PTN5150_REG_CC_VBUS_DETECTION, reg_data);
		अगर (vbus)
			gpiod_set_value_cansleep(info->vbus_gpiod, 0);
		अन्यथा
			gpiod_set_value_cansleep(info->vbus_gpiod, 1);

		extcon_set_state_sync(info->edev, EXTCON_USB_HOST, true);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ptn5150_irq_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ptn5150_info *info = container_of(work,
			काष्ठा ptn5150_info, irq_work);
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक पूर्णांक_status;

	अगर (!info->edev)
		वापस;

	mutex_lock(&info->mutex);

	/* Clear पूर्णांकerrupt. Read would clear the रेजिस्टर */
	ret = regmap_पढ़ो(info->regmap, PTN5150_REG_INT_STATUS, &पूर्णांक_status);
	अगर (ret) अणु
		dev_err(info->dev, "failed to read INT STATUS %d\n", ret);
		mutex_unlock(&info->mutex);
		वापस;
	पूर्ण

	अगर (पूर्णांक_status) अणु
		अचिन्हित पूर्णांक cable_attach;

		cable_attach = पूर्णांक_status & PTN5150_REG_INT_CABLE_ATTACH_MASK;
		अगर (cable_attach) अणु
			ptn5150_check_state(info);
		पूर्ण अन्यथा अणु
			extcon_set_state_sync(info->edev,
					EXTCON_USB_HOST, false);
			extcon_set_state_sync(info->edev,
					EXTCON_USB, false);
			gpiod_set_value_cansleep(info->vbus_gpiod, 0);
		पूर्ण
	पूर्ण

	/* Clear पूर्णांकerrupt. Read would clear the रेजिस्टर */
	ret = regmap_पढ़ो(info->regmap, PTN5150_REG_INT_REG_STATUS,
			&पूर्णांक_status);
	अगर (ret) अणु
		dev_err(info->dev,
			"failed to read INT REG STATUS %d\n", ret);
		mutex_unlock(&info->mutex);
		वापस;
	पूर्ण

	mutex_unlock(&info->mutex);
पूर्ण


अटल irqवापस_t ptn5150_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ptn5150_info *info = data;

	schedule_work(&info->irq_work);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ptn5150_init_dev_type(काष्ठा ptn5150_info *info)
अणु
	अचिन्हित पूर्णांक reg_data, venकरोr_id, version_id;
	पूर्णांक ret;

	ret = regmap_पढ़ो(info->regmap, PTN5150_REG_DEVICE_ID, &reg_data);
	अगर (ret) अणु
		dev_err(info->dev, "failed to read DEVICE_ID %d\n", ret);
		वापस -EINVAL;
	पूर्ण

	venकरोr_id = FIELD_GET(PTN5150_REG_DEVICE_ID_VENDOR, reg_data);
	version_id = FIELD_GET(PTN5150_REG_DEVICE_ID_VERSION, reg_data);
	dev_dbg(info->dev, "Device type: version: 0x%x, vendor: 0x%x\n",
		version_id, venकरोr_id);

	/* Clear any existing पूर्णांकerrupts */
	ret = regmap_पढ़ो(info->regmap, PTN5150_REG_INT_STATUS, &reg_data);
	अगर (ret) अणु
		dev_err(info->dev,
			"failed to read PTN5150_REG_INT_STATUS %d\n",
			ret);
		वापस -EINVAL;
	पूर्ण

	ret = regmap_पढ़ो(info->regmap, PTN5150_REG_INT_REG_STATUS, &reg_data);
	अगर (ret) अणु
		dev_err(info->dev,
			"failed to read PTN5150_REG_INT_REG_STATUS %d\n", ret);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ptn5150_i2c_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा device *dev = &i2c->dev;
	काष्ठा device_node *np = i2c->dev.of_node;
	काष्ठा ptn5150_info *info;
	पूर्णांक ret;

	अगर (!np)
		वापस -EINVAL;

	info = devm_kzalloc(&i2c->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;
	i2c_set_clientdata(i2c, info);

	info->dev = &i2c->dev;
	info->i2c = i2c;
	info->vbus_gpiod = devm_gpiod_get(&i2c->dev, "vbus", GPIOD_OUT_LOW);
	अगर (IS_ERR(info->vbus_gpiod)) अणु
		ret = PTR_ERR(info->vbus_gpiod);
		अगर (ret == -ENOENT) अणु
			dev_info(dev, "No VBUS GPIO, ignoring VBUS control\n");
			info->vbus_gpiod = शून्य;
		पूर्ण अन्यथा अणु
			वापस dev_err_probe(dev, ret, "failed to get VBUS GPIO\n");
		पूर्ण
	पूर्ण

	mutex_init(&info->mutex);

	INIT_WORK(&info->irq_work, ptn5150_irq_work);

	info->regmap = devm_regmap_init_i2c(i2c, &ptn5150_regmap_config);
	अगर (IS_ERR(info->regmap)) अणु
		वापस dev_err_probe(info->dev, PTR_ERR(info->regmap),
				     "failed to allocate register map\n");
	पूर्ण

	अगर (i2c->irq > 0) अणु
		info->irq = i2c->irq;
	पूर्ण अन्यथा अणु
		info->पूर्णांक_gpiod = devm_gpiod_get(&i2c->dev, "int", GPIOD_IN);
		अगर (IS_ERR(info->पूर्णांक_gpiod)) अणु
			वापस dev_err_probe(dev, PTR_ERR(info->पूर्णांक_gpiod),
					     "failed to get INT GPIO\n");
		पूर्ण

		info->irq = gpiod_to_irq(info->पूर्णांक_gpiod);
		अगर (info->irq < 0) अणु
			dev_err(dev, "failed to get INTB IRQ\n");
			वापस info->irq;
		पूर्ण
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, info->irq, शून्य,
					ptn5150_irq_handler,
					IRQF_TRIGGER_FALLING |
					IRQF_ONESHOT,
					i2c->name, info);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to request handler for INTB IRQ\n");
		वापस ret;
	पूर्ण

	/* Allocate extcon device */
	info->edev = devm_extcon_dev_allocate(info->dev, ptn5150_extcon_cable);
	अगर (IS_ERR(info->edev)) अणु
		dev_err(info->dev, "failed to allocate memory for extcon\n");
		वापस -ENOMEM;
	पूर्ण

	/* Register extcon device */
	ret = devm_extcon_dev_रेजिस्टर(info->dev, info->edev);
	अगर (ret) अणु
		dev_err(info->dev, "failed to register extcon device\n");
		वापस ret;
	पूर्ण

	extcon_set_property_capability(info->edev, EXTCON_USB,
					EXTCON_PROP_USB_VBUS);
	extcon_set_property_capability(info->edev, EXTCON_USB_HOST,
					EXTCON_PROP_USB_VBUS);
	extcon_set_property_capability(info->edev, EXTCON_USB_HOST,
					EXTCON_PROP_USB_TYPEC_POLARITY);

	/* Initialize PTN5150 device and prपूर्णांक venकरोr id and version id */
	ret = ptn5150_init_dev_type(info);
	अगर (ret)
		वापस -EINVAL;

	/*
	 * Update current extcon state अगर क्रम example OTG connection was there
	 * beक्रमe the probe
	 */
	mutex_lock(&info->mutex);
	ptn5150_check_state(info);
	mutex_unlock(&info->mutex);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ptn5150_dt_match[] = अणु
	अणु .compatible = "nxp,ptn5150" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ptn5150_dt_match);

अटल स्थिर काष्ठा i2c_device_id ptn5150_i2c_id[] = अणु
	अणु "ptn5150", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ptn5150_i2c_id);

अटल काष्ठा i2c_driver ptn5150_i2c_driver = अणु
	.driver		= अणु
		.name	= "ptn5150",
		.of_match_table = ptn5150_dt_match,
	पूर्ण,
	.probe_new	= ptn5150_i2c_probe,
	.id_table = ptn5150_i2c_id,
पूर्ण;
module_i2c_driver(ptn5150_i2c_driver);

MODULE_DESCRIPTION("NXP PTN5150 CC logic Extcon driver");
MODULE_AUTHOR("Vijai Kumar K <vijaikumar.kanagarajan@gmail.com>");
MODULE_AUTHOR("Krzysztof Kozlowski <krzk@kernel.org>");
MODULE_LICENSE("GPL v2");
