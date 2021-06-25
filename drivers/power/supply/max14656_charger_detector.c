<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Maxim MAX14656 / AL32 USB Charger Detector driver
 *
 * Copyright (C) 2014 LG Electronics, Inc
 * Copyright (C) 2016 Alexander Kurz <akurz@blala.de>
 *
 * Components from Maxim AL32 Charger detection Driver क्रम MX50 Yoshi Board
 * Copyright (C) Amazon Technologies Inc. All rights reserved.
 * Manish Lachwani (lachwani@lab126.com)
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_device.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/घातer_supply.h>

#घोषणा MAX14656_MANUFACTURER	"Maxim Integrated"
#घोषणा MAX14656_NAME		"max14656"

#घोषणा MAX14656_DEVICE_ID	0x00
#घोषणा MAX14656_INTERRUPT_1	0x01
#घोषणा MAX14656_INTERRUPT_2	0x02
#घोषणा MAX14656_STATUS_1	0x03
#घोषणा MAX14656_STATUS_2	0x04
#घोषणा MAX14656_INTMASK_1	0x05
#घोषणा MAX14656_INTMASK_2	0x06
#घोषणा MAX14656_CONTROL_1	0x07
#घोषणा MAX14656_CONTROL_2	0x08
#घोषणा MAX14656_CONTROL_3	0x09

#घोषणा DEVICE_VENDOR_MASK	0xf0
#घोषणा DEVICE_REV_MASK		0x0f
#घोषणा INT_EN_REG_MASK		BIT(4)
#घोषणा CHG_TYPE_INT_MASK	BIT(0)
#घोषणा STATUS1_VB_VALID_MASK	BIT(4)
#घोषणा STATUS1_CHG_TYPE_MASK	0xf
#घोषणा INT1_DCD_TIMEOUT_MASK	BIT(7)
#घोषणा CONTROL1_DEFAULT	0x0d
#घोषणा CONTROL1_INT_EN		BIT(4)
#घोषणा CONTROL1_INT_ACTIVE_HIGH	BIT(5)
#घोषणा CONTROL1_EDGE		BIT(7)
#घोषणा CONTROL2_DEFAULT	0x8e
#घोषणा CONTROL2_ADC_EN		BIT(0)
#घोषणा CONTROL3_DEFAULT	0x8d

क्रमागत max14656_chg_type अणु
	MAX14656_NO_CHARGER	= 0,
	MAX14656_SDP_CHARGER,
	MAX14656_CDP_CHARGER,
	MAX14656_DCP_CHARGER,
	MAX14656_APPLE_500MA_CHARGER,
	MAX14656_APPLE_1A_CHARGER,
	MAX14656_APPLE_2A_CHARGER,
	MAX14656_SPECIAL_500MA_CHARGER,
	MAX14656_APPLE_12W,
	MAX14656_CHARGER_LAST
पूर्ण;

अटल स्थिर काष्ठा max14656_chg_type_props अणु
	क्रमागत घातer_supply_type type;
पूर्ण chg_type_props[] = अणु
	अणु POWER_SUPPLY_TYPE_UNKNOWN पूर्ण,
	अणु POWER_SUPPLY_TYPE_USB पूर्ण,
	अणु POWER_SUPPLY_TYPE_USB_CDP पूर्ण,
	अणु POWER_SUPPLY_TYPE_USB_DCP पूर्ण,
	अणु POWER_SUPPLY_TYPE_USB_DCP पूर्ण,
	अणु POWER_SUPPLY_TYPE_USB_DCP पूर्ण,
	अणु POWER_SUPPLY_TYPE_USB_DCP पूर्ण,
	अणु POWER_SUPPLY_TYPE_USB_DCP पूर्ण,
	अणु POWER_SUPPLY_TYPE_USB पूर्ण,
पूर्ण;

काष्ठा max14656_chip अणु
	काष्ठा i2c_client	*client;
	काष्ठा घातer_supply	*detect_psy;
	काष्ठा घातer_supply_desc psy_desc;
	काष्ठा delayed_work	irq_work;

	पूर्णांक irq;
	पूर्णांक online;
पूर्ण;

अटल पूर्णांक max14656_पढ़ो_reg(काष्ठा i2c_client *client, पूर्णांक reg, u8 *val)
अणु
	s32 ret;

	ret = i2c_smbus_पढ़ो_byte_data(client, reg);
	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"i2c read fail: can't read from %02x: %d\n",
			reg, ret);
		वापस ret;
	पूर्ण
	*val = ret;
	वापस 0;
पूर्ण

अटल पूर्णांक max14656_ग_लिखो_reg(काष्ठा i2c_client *client, पूर्णांक reg, u8 val)
अणु
	s32 ret;

	ret = i2c_smbus_ग_लिखो_byte_data(client, reg, val);
	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"i2c write fail: can't write %02x to %02x: %d\n",
			val, reg, ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक max14656_पढ़ो_block_reg(काष्ठा i2c_client *client, u8 reg,
				  u8 length, u8 *val)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_i2c_block_data(client, reg, length, val);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to block read reg 0x%x: %d\n",
				reg, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा        REG_TOTAL_NUM   5
अटल व्योम max14656_irq_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा max14656_chip *chip =
		container_of(work, काष्ठा max14656_chip, irq_work.work);

	u8 buf[REG_TOTAL_NUM];
	u8 chg_type;

	max14656_पढ़ो_block_reg(chip->client, MAX14656_DEVICE_ID,
				REG_TOTAL_NUM, buf);

	अगर ((buf[MAX14656_STATUS_1] & STATUS1_VB_VALID_MASK) &&
		(buf[MAX14656_STATUS_1] & STATUS1_CHG_TYPE_MASK)) अणु
		chg_type = buf[MAX14656_STATUS_1] & STATUS1_CHG_TYPE_MASK;
		अगर (chg_type < MAX14656_CHARGER_LAST)
			chip->psy_desc.type = chg_type_props[chg_type].type;
		अन्यथा
			chip->psy_desc.type = POWER_SUPPLY_TYPE_UNKNOWN;
		chip->online = 1;
	पूर्ण अन्यथा अणु
		chip->online = 0;
		chip->psy_desc.type = POWER_SUPPLY_TYPE_UNKNOWN;
	पूर्ण

	घातer_supply_changed(chip->detect_psy);
पूर्ण

अटल irqवापस_t max14656_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा max14656_chip *chip = dev_id;

	schedule_delayed_work(&chip->irq_work, msecs_to_jअगरfies(100));

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक max14656_hw_init(काष्ठा max14656_chip *chip)
अणु
	uपूर्णांक8_t val = 0;
	uपूर्णांक8_t rev;
	काष्ठा i2c_client *client = chip->client;

	अगर (max14656_पढ़ो_reg(client, MAX14656_DEVICE_ID, &val))
		वापस -ENODEV;

	अगर ((val & DEVICE_VENDOR_MASK) != 0x20) अणु
		dev_err(&client->dev, "wrong vendor ID %d\n",
			((val & DEVICE_VENDOR_MASK) >> 4));
		वापस -ENODEV;
	पूर्ण
	rev = val & DEVICE_REV_MASK;

	/* Turn on ADC_EN */
	अगर (max14656_ग_लिखो_reg(client, MAX14656_CONTROL_2, CONTROL2_ADC_EN))
		वापस -EINVAL;

	/* turn on पूर्णांकerrupts and low घातer mode */
	अगर (max14656_ग_लिखो_reg(client, MAX14656_CONTROL_1,
		CONTROL1_DEFAULT |
		CONTROL1_INT_EN |
		CONTROL1_INT_ACTIVE_HIGH |
		CONTROL1_EDGE))
		वापस -EINVAL;

	अगर (max14656_ग_लिखो_reg(client, MAX14656_INTMASK_1, 0x3))
		वापस -EINVAL;

	अगर (max14656_ग_लिखो_reg(client, MAX14656_INTMASK_2, 0x1))
		वापस -EINVAL;

	dev_info(&client->dev, "detected revision %d\n", rev);
	वापस 0;
पूर्ण

अटल पूर्णांक max14656_get_property(काष्ठा घातer_supply *psy,
			    क्रमागत घातer_supply_property psp,
			    जोड़ घातer_supply_propval *val)
अणु
	काष्ठा max14656_chip *chip = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = chip->online;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = MAX14656_NAME;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = MAX14656_MANUFACTURER;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल क्रमागत घातer_supply_property max14656_battery_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER,
पूर्ण;

अटल व्योम stop_irq_work(व्योम *data)
अणु
	काष्ठा max14656_chip *chip = data;

	cancel_delayed_work_sync(&chip->irq_work);
पूर्ण


अटल पूर्णांक max14656_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा device *dev = &client->dev;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा max14656_chip *chip;
	पूर्णांक irq = client->irq;
	पूर्णांक ret = 0;

	अगर (irq <= 0) अणु
		dev_err(dev, "invalid irq number: %d\n", irq);
		वापस -ENODEV;
	पूर्ण

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		dev_err(dev, "No support for SMBUS_BYTE_DATA\n");
		वापस -ENODEV;
	पूर्ण

	chip = devm_kzalloc(dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	psy_cfg.drv_data = chip;
	chip->client = client;
	chip->online = 0;
	chip->psy_desc.name = MAX14656_NAME;
	chip->psy_desc.type = POWER_SUPPLY_TYPE_UNKNOWN;
	chip->psy_desc.properties = max14656_battery_props;
	chip->psy_desc.num_properties = ARRAY_SIZE(max14656_battery_props);
	chip->psy_desc.get_property = max14656_get_property;
	chip->irq = irq;

	ret = max14656_hw_init(chip);
	अगर (ret)
		वापस -ENODEV;

	chip->detect_psy = devm_घातer_supply_रेजिस्टर(dev,
		       &chip->psy_desc, &psy_cfg);
	अगर (IS_ERR(chip->detect_psy)) अणु
		dev_err(dev, "power_supply_register failed\n");
		वापस -EINVAL;
	पूर्ण

	INIT_DELAYED_WORK(&chip->irq_work, max14656_irq_worker);
	ret = devm_add_action(dev, stop_irq_work, chip);
	अगर (ret) अणु
		dev_err(dev, "devm_add_action %d failed\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_request_irq(dev, chip->irq, max14656_irq,
			       IRQF_TRIGGER_FALLING,
			       MAX14656_NAME, chip);
	अगर (ret) अणु
		dev_err(dev, "request_irq %d failed\n", chip->irq);
		वापस -EINVAL;
	पूर्ण
	enable_irq_wake(chip->irq);

	schedule_delayed_work(&chip->irq_work, msecs_to_jअगरfies(2000));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max14656_id[] = अणु
	अणु "max14656", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max14656_id);

अटल स्थिर काष्ठा of_device_id max14656_match_table[] = अणु
	अणु .compatible = "maxim,max14656", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max14656_match_table);

अटल काष्ठा i2c_driver max14656_i2c_driver = अणु
	.driver = अणु
		.name	= "max14656",
		.of_match_table = max14656_match_table,
	पूर्ण,
	.probe		= max14656_probe,
	.id_table	= max14656_id,
पूर्ण;
module_i2c_driver(max14656_i2c_driver);

MODULE_DESCRIPTION("MAX14656 USB charger detector");
MODULE_LICENSE("GPL v2");
