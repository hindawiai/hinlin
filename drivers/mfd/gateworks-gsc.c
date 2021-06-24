<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * The Gateworks System Controller (GSC) is a multi-function
 * device deचिन्हित क्रम use in Gateworks Single Board Computers.
 * The control पूर्णांकerface is I2C, with an पूर्णांकerrupt. The device supports
 * प्रणाली functions such as push-button monitoring, multiple ADC's क्रम
 * voltage and temperature monitoring, fan controller and watchकरोg monitor.
 *
 * Copyright (C) 2020 Gateworks Corporation
 */

#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mfd/gsc.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

#समावेश <यंत्र/unaligned.h>

/*
 * The GSC suffers from an errata where occasionally during
 * ADC cycles the chip can NAK I2C transactions. To ensure we have reliable
 * रेजिस्टर access we place retries around रेजिस्टर access.
 */
#घोषणा I2C_RETRIES	3

पूर्णांक gsc_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा i2c_client *client = context;
	पूर्णांक retry, ret;

	क्रम (retry = 0; retry < I2C_RETRIES; retry++) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(client, reg, val);
		/*
		 * -EAGAIN वापसed when the i2c host controller is busy
		 * -EIO वापसed when i2c device is busy
		 */
		अगर (ret != -EAGAIN && ret != -EIO)
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gsc_ग_लिखो);

पूर्णांक gsc_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक *val)
अणु
	काष्ठा i2c_client *client = context;
	पूर्णांक retry, ret;

	क्रम (retry = 0; retry < I2C_RETRIES; retry++) अणु
		ret = i2c_smbus_पढ़ो_byte_data(client, reg);
		/*
		 * -EAGAIN वापसed when the i2c host controller is busy
		 * -EIO वापसed when i2c device is busy
		 */
		अगर (ret != -EAGAIN && ret != -EIO)
			अवरोध;
	पूर्ण
	*val = ret & 0xff;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(gsc_पढ़ो);

/*
 * gsc_घातerकरोwn - API to use GSC to घातer करोwn board क्रम a specअगरic समय
 *
 * secs - number of seconds to reमुख्य घातered off
 */
अटल पूर्णांक gsc_घातerकरोwn(काष्ठा gsc_dev *gsc, अचिन्हित दीर्घ secs)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर regs[4];

	dev_info(&gsc->i2c->dev, "GSC powerdown for %ld seconds\n",
		 secs);

	put_unaligned_le32(secs, regs);
	ret = regmap_bulk_ग_लिखो(gsc->regmap, GSC_TIME_ADD, regs, 4);
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(gsc->regmap, GSC_CTRL_1,
				 BIT(GSC_CTRL_1_SLEEP_ADD),
				 BIT(GSC_CTRL_1_SLEEP_ADD));
	अगर (ret)
		वापस ret;

	ret = regmap_update_bits(gsc->regmap, GSC_CTRL_1,
				 BIT(GSC_CTRL_1_SLEEP_ACTIVATE) |
				 BIT(GSC_CTRL_1_SLEEP_ENABLE),
				 BIT(GSC_CTRL_1_SLEEP_ACTIVATE) |
				 BIT(GSC_CTRL_1_SLEEP_ENABLE));


	वापस ret;
पूर्ण

अटल sमाप_प्रकार gsc_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा gsc_dev *gsc = dev_get_drvdata(dev);
	स्थिर अक्षर *name = attr->attr.name;
	पूर्णांक rz = 0;

	अगर (strहालcmp(name, "fw_version") == 0)
		rz = प्र_लिखो(buf, "%d\n", gsc->fwver);
	अन्यथा अगर (strहालcmp(name, "fw_crc") == 0)
		rz = प्र_लिखो(buf, "0x%04x\n", gsc->fwcrc);
	अन्यथा
		dev_err(dev, "invalid command: '%s'\n", name);

	वापस rz;
पूर्ण

अटल sमाप_प्रकार gsc_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा gsc_dev *gsc = dev_get_drvdata(dev);
	स्थिर अक्षर *name = attr->attr.name;
	दीर्घ value;

	अगर (strहालcmp(name, "powerdown") == 0) अणु
		अगर (kम_से_दीर्घ(buf, 0, &value) == 0)
			gsc_घातerकरोwn(gsc, value);
	पूर्ण अन्यथा अणु
		dev_err(dev, "invalid command: '%s\n", name);
	पूर्ण

	वापस count;
पूर्ण

अटल काष्ठा device_attribute attr_fwver =
	__ATTR(fw_version, 0440, gsc_show, शून्य);
अटल काष्ठा device_attribute attr_fwcrc =
	__ATTR(fw_crc, 0440, gsc_show, शून्य);
अटल काष्ठा device_attribute attr_pwrकरोwn =
	__ATTR(घातerकरोwn, 0220, शून्य, gsc_store);

अटल काष्ठा attribute *gsc_attrs[] = अणु
	&attr_fwver.attr,
	&attr_fwcrc.attr,
	&attr_pwrकरोwn.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group attr_group = अणु
	.attrs = gsc_attrs,
पूर्ण;

अटल स्थिर काष्ठा of_device_id gsc_of_match[] = अणु
	अणु .compatible = "gw,gsc", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, gsc_of_match);

अटल काष्ठा regmap_bus gsc_regmap_bus = अणु
	.reg_पढ़ो = gsc_पढ़ो,
	.reg_ग_लिखो = gsc_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा regmap_config gsc_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.cache_type = REGCACHE_NONE,
	.max_रेजिस्टर = GSC_WP,
पूर्ण;

अटल स्थिर काष्ठा regmap_irq gsc_irqs[] = अणु
	REGMAP_IRQ_REG(GSC_IRQ_PB, 0, BIT(GSC_IRQ_PB)),
	REGMAP_IRQ_REG(GSC_IRQ_KEY_ERASED, 0, BIT(GSC_IRQ_KEY_ERASED)),
	REGMAP_IRQ_REG(GSC_IRQ_EEPROM_WP, 0, BIT(GSC_IRQ_EEPROM_WP)),
	REGMAP_IRQ_REG(GSC_IRQ_RESV, 0, BIT(GSC_IRQ_RESV)),
	REGMAP_IRQ_REG(GSC_IRQ_GPIO, 0, BIT(GSC_IRQ_GPIO)),
	REGMAP_IRQ_REG(GSC_IRQ_TAMPER, 0, BIT(GSC_IRQ_TAMPER)),
	REGMAP_IRQ_REG(GSC_IRQ_WDT_TIMEOUT, 0, BIT(GSC_IRQ_WDT_TIMEOUT)),
	REGMAP_IRQ_REG(GSC_IRQ_SWITCH_HOLD, 0, BIT(GSC_IRQ_SWITCH_HOLD)),
पूर्ण;

अटल स्थिर काष्ठा regmap_irq_chip gsc_irq_chip = अणु
	.name = "gateworks-gsc",
	.irqs = gsc_irqs,
	.num_irqs = ARRAY_SIZE(gsc_irqs),
	.num_regs = 1,
	.status_base = GSC_IRQ_STATUS,
	.mask_base = GSC_IRQ_ENABLE,
	.mask_invert = true,
	.ack_base = GSC_IRQ_STATUS,
	.ack_invert = true,
पूर्ण;

अटल पूर्णांक gsc_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा gsc_dev *gsc;
	काष्ठा regmap_irq_chip_data *irq_data;
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg;

	gsc = devm_kzalloc(dev, माप(*gsc), GFP_KERNEL);
	अगर (!gsc)
		वापस -ENOMEM;

	gsc->dev = &client->dev;
	gsc->i2c = client;
	i2c_set_clientdata(client, gsc);

	gsc->regmap = devm_regmap_init(dev, &gsc_regmap_bus, client,
				       &gsc_regmap_config);
	अगर (IS_ERR(gsc->regmap))
		वापस PTR_ERR(gsc->regmap);

	अगर (regmap_पढ़ो(gsc->regmap, GSC_FW_VER, &reg))
		वापस -EIO;
	gsc->fwver = reg;

	regmap_पढ़ो(gsc->regmap, GSC_FW_CRC, &reg);
	gsc->fwcrc = reg;
	regmap_पढ़ो(gsc->regmap, GSC_FW_CRC + 1, &reg);
	gsc->fwcrc |= reg << 8;

	gsc->i2c_hwmon = devm_i2c_new_dummy_device(dev, client->adapter,
						   GSC_HWMON);
	अगर (IS_ERR(gsc->i2c_hwmon)) अणु
		dev_err(dev, "Failed to allocate I2C device for HWMON\n");
		वापस PTR_ERR(gsc->i2c_hwmon);
	पूर्ण

	ret = devm_regmap_add_irq_chip(dev, gsc->regmap, client->irq,
				       IRQF_ONESHOT | IRQF_SHARED |
				       IRQF_TRIGGER_LOW, 0,
				       &gsc_irq_chip, &irq_data);
	अगर (ret)
		वापस ret;

	dev_info(dev, "Gateworks System Controller v%d: fw 0x%04x\n",
		 gsc->fwver, gsc->fwcrc);

	ret = sysfs_create_group(&dev->kobj, &attr_group);
	अगर (ret)
		dev_err(dev, "failed to create sysfs attrs\n");

	ret = devm_of_platक्रमm_populate(dev);
	अगर (ret) अणु
		sysfs_हटाओ_group(&dev->kobj, &attr_group);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gsc_हटाओ(काष्ठा i2c_client *client)
अणु
	sysfs_हटाओ_group(&client->dev.kobj, &attr_group);

	वापस 0;
पूर्ण

अटल काष्ठा i2c_driver gsc_driver = अणु
	.driver = अणु
		.name	= "gateworks-gsc",
		.of_match_table = gsc_of_match,
	पूर्ण,
	.probe_new	= gsc_probe,
	.हटाओ		= gsc_हटाओ,
पूर्ण;
module_i2c_driver(gsc_driver);

MODULE_AUTHOR("Tim Harvey <tharvey@gateworks.com>");
MODULE_DESCRIPTION("I2C Core interface for GSC");
MODULE_LICENSE("GPL v2");
