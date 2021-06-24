<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
//  max17040_battery.c
//  fuel-gauge प्रणालीs क्रम lithium-ion (Li+) batteries
//
//  Copyright (C) 2009 Samsung Electronics
//  Minkyu Kang <mk7.kang@samsung.com>

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/of_device.h>
#समावेश <linux/max17040_battery.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#घोषणा MAX17040_VCELL	0x02
#घोषणा MAX17040_SOC	0x04
#घोषणा MAX17040_MODE	0x06
#घोषणा MAX17040_VER	0x08
#घोषणा MAX17040_CONFIG	0x0C
#घोषणा MAX17040_STATUS	0x1A
#घोषणा MAX17040_CMD	0xFE


#घोषणा MAX17040_DELAY		1000
#घोषणा MAX17040_BATTERY_FULL	95
#घोषणा MAX17040_RCOMP_DEFAULT  0x9700

#घोषणा MAX17040_ATHD_MASK		0x3f
#घोषणा MAX17040_ALSC_MASK		0x40
#घोषणा MAX17040_ATHD_DEFAULT_POWER_UP	4
#घोषणा MAX17040_STATUS_HD_MASK		0x1000
#घोषणा MAX17040_STATUS_SC_MASK		0x2000
#घोषणा MAX17040_CFG_RCOMP_MASK		0xff00

क्रमागत chip_id अणु
	ID_MAX17040,
	ID_MAX17041,
	ID_MAX17043,
	ID_MAX17044,
	ID_MAX17048,
	ID_MAX17049,
	ID_MAX17058,
	ID_MAX17059,
पूर्ण;

/* values that dअगरfer by chip_id */
काष्ठा chip_data अणु
	u16 reset_val;
	u16 vcell_shअगरt;
	u16 vcell_mul;
	u16 vcell_भाग;
	u8  has_low_soc_alert;
	u8  rcomp_bytes;
	u8  has_soc_alert;
पूर्ण;

अटल काष्ठा chip_data max17040_family[] = अणु
	[ID_MAX17040] = अणु
		.reset_val = 0x0054,
		.vcell_shअगरt = 4,
		.vcell_mul = 1250,
		.vcell_भाग = 1,
		.has_low_soc_alert = 0,
		.rcomp_bytes = 2,
		.has_soc_alert = 0,
	पूर्ण,
	[ID_MAX17041] = अणु
		.reset_val = 0x0054,
		.vcell_shअगरt = 4,
		.vcell_mul = 2500,
		.vcell_भाग = 1,
		.has_low_soc_alert = 0,
		.rcomp_bytes = 2,
		.has_soc_alert = 0,
	पूर्ण,
	[ID_MAX17043] = अणु
		.reset_val = 0x0054,
		.vcell_shअगरt = 4,
		.vcell_mul = 1250,
		.vcell_भाग = 1,
		.has_low_soc_alert = 1,
		.rcomp_bytes = 1,
		.has_soc_alert = 0,
	पूर्ण,
	[ID_MAX17044] = अणु
		.reset_val = 0x0054,
		.vcell_shअगरt = 4,
		.vcell_mul = 2500,
		.vcell_भाग = 1,
		.has_low_soc_alert = 1,
		.rcomp_bytes = 1,
		.has_soc_alert = 0,
	पूर्ण,
	[ID_MAX17048] = अणु
		.reset_val = 0x5400,
		.vcell_shअगरt = 0,
		.vcell_mul = 625,
		.vcell_भाग = 8,
		.has_low_soc_alert = 1,
		.rcomp_bytes = 1,
		.has_soc_alert = 1,
	पूर्ण,
	[ID_MAX17049] = अणु
		.reset_val = 0x5400,
		.vcell_shअगरt = 0,
		.vcell_mul = 625,
		.vcell_भाग = 4,
		.has_low_soc_alert = 1,
		.rcomp_bytes = 1,
		.has_soc_alert = 1,
	पूर्ण,
	[ID_MAX17058] = अणु
		.reset_val = 0x5400,
		.vcell_shअगरt = 0,
		.vcell_mul = 625,
		.vcell_भाग = 8,
		.has_low_soc_alert = 1,
		.rcomp_bytes = 1,
		.has_soc_alert = 0,
	पूर्ण,
	[ID_MAX17059] = अणु
		.reset_val = 0x5400,
		.vcell_shअगरt = 0,
		.vcell_mul = 625,
		.vcell_भाग = 4,
		.has_low_soc_alert = 1,
		.rcomp_bytes = 1,
		.has_soc_alert = 0,
	पूर्ण,
पूर्ण;

काष्ठा max17040_chip अणु
	काष्ठा i2c_client		*client;
	काष्ठा regmap			*regmap;
	काष्ठा delayed_work		work;
	काष्ठा घातer_supply		*battery;
	काष्ठा max17040_platक्रमm_data	*pdata;
	काष्ठा chip_data		data;

	/* battery capacity */
	पूर्णांक soc;
	/* State Of Charge */
	पूर्णांक status;
	/* Low alert threshold from 32% to 1% of the State of Charge */
	u32 low_soc_alert;
	/* some devices वापस twice the capacity */
	bool quirk_द्विगुन_soc;
	/* higher 8 bits क्रम 17043+, 16 bits क्रम 17040,41 */
	u16 rcomp;
पूर्ण;

अटल पूर्णांक max17040_reset(काष्ठा max17040_chip *chip)
अणु
	वापस regmap_ग_लिखो(chip->regmap, MAX17040_CMD, chip->data.reset_val);
पूर्ण

अटल पूर्णांक max17040_set_low_soc_alert(काष्ठा max17040_chip *chip, u32 level)
अणु
	level = 32 - level * (chip->quirk_द्विगुन_soc ? 2 : 1);
	वापस regmap_update_bits(chip->regmap, MAX17040_CONFIG,
			MAX17040_ATHD_MASK, level);
पूर्ण

अटल पूर्णांक max17040_set_soc_alert(काष्ठा max17040_chip *chip, bool enable)
अणु
	वापस regmap_update_bits(chip->regmap, MAX17040_CONFIG,
			MAX17040_ALSC_MASK, enable ? MAX17040_ALSC_MASK : 0);
पूर्ण

अटल पूर्णांक max17040_set_rcomp(काष्ठा max17040_chip *chip, u16 rcomp)
अणु
	u16 mask = chip->data.rcomp_bytes == 2 ?
		0xffff : MAX17040_CFG_RCOMP_MASK;

	वापस regmap_update_bits(chip->regmap, MAX17040_CONFIG, mask, rcomp);
पूर्ण

अटल पूर्णांक max17040_raw_vcell_to_uvolts(काष्ठा max17040_chip *chip, u16 vcell)
अणु
	काष्ठा chip_data *d = &chip->data;

	वापस (vcell >> d->vcell_shअगरt) * d->vcell_mul / d->vcell_भाग;
पूर्ण


अटल पूर्णांक max17040_get_vcell(काष्ठा max17040_chip *chip)
अणु
	u32 vcell;

	regmap_पढ़ो(chip->regmap, MAX17040_VCELL, &vcell);

	वापस max17040_raw_vcell_to_uvolts(chip, vcell);
पूर्ण

अटल पूर्णांक max17040_get_soc(काष्ठा max17040_chip *chip)
अणु
	u32 soc;

	regmap_पढ़ो(chip->regmap, MAX17040_SOC, &soc);

	वापस soc >> (chip->quirk_द्विगुन_soc ? 9 : 8);
पूर्ण

अटल पूर्णांक max17040_get_version(काष्ठा max17040_chip *chip)
अणु
	पूर्णांक ret;
	u32 version;

	ret = regmap_पढ़ो(chip->regmap, MAX17040_VER, &version);

	वापस ret ? ret : version;
पूर्ण

अटल पूर्णांक max17040_get_online(काष्ठा max17040_chip *chip)
अणु
	वापस chip->pdata && chip->pdata->battery_online ?
		chip->pdata->battery_online() : 1;
पूर्ण

अटल पूर्णांक max17040_get_status(काष्ठा max17040_chip *chip)
अणु
	अगर (!chip->pdata || !chip->pdata->अक्षरger_online
			|| !chip->pdata->अक्षरger_enable)
		वापस POWER_SUPPLY_STATUS_UNKNOWN;

	अगर (max17040_get_soc(chip) > MAX17040_BATTERY_FULL)
		वापस POWER_SUPPLY_STATUS_FULL;

	अगर (chip->pdata->अक्षरger_online())
		अगर (chip->pdata->अक्षरger_enable())
			वापस POWER_SUPPLY_STATUS_CHARGING;
		अन्यथा
			वापस POWER_SUPPLY_STATUS_NOT_CHARGING;
	अन्यथा
		वापस POWER_SUPPLY_STATUS_DISCHARGING;
पूर्ण

अटल पूर्णांक max17040_get_of_data(काष्ठा max17040_chip *chip)
अणु
	काष्ठा device *dev = &chip->client->dev;
	काष्ठा chip_data *data = &max17040_family[
		(uपूर्णांकptr_t) of_device_get_match_data(dev)];
	पूर्णांक rcomp_len;
	u8 rcomp[2];

	chip->quirk_द्विगुन_soc = device_property_पढ़ो_bool(dev,
							   "maxim,double-soc");

	chip->low_soc_alert = MAX17040_ATHD_DEFAULT_POWER_UP;
	device_property_पढ़ो_u32(dev,
				 "maxim,alert-low-soc-level",
				 &chip->low_soc_alert);

	अगर (chip->low_soc_alert <= 0 ||
	    chip->low_soc_alert > (chip->quirk_द्विगुन_soc ? 16 : 32)) अणु
		dev_err(dev, "maxim,alert-low-soc-level out of bounds\n");
		वापस -EINVAL;
	पूर्ण

	rcomp_len = device_property_count_u8(dev, "maxim,rcomp");
	chip->rcomp = MAX17040_RCOMP_DEFAULT;
	अगर (rcomp_len == data->rcomp_bytes) अणु
		अगर (!device_property_पढ़ो_u8_array(dev, "maxim,rcomp",
						   rcomp, rcomp_len))
			chip->rcomp = rcomp_len == 2 ? rcomp[0] << 8 | rcomp[1] :
				      rcomp[0] << 8;
	पूर्ण अन्यथा अगर (rcomp_len > 0) अणु
		dev_err(dev, "maxim,rcomp has incorrect length\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम max17040_check_changes(काष्ठा max17040_chip *chip)
अणु
	chip->soc = max17040_get_soc(chip);
	chip->status = max17040_get_status(chip);
पूर्ण

अटल व्योम max17040_queue_work(काष्ठा max17040_chip *chip)
अणु
	queue_delayed_work(प्रणाली_घातer_efficient_wq, &chip->work,
			   MAX17040_DELAY);
पूर्ण

अटल व्योम max17040_stop_work(व्योम *data)
अणु
	काष्ठा max17040_chip *chip = data;

	cancel_delayed_work_sync(&chip->work);
पूर्ण

अटल व्योम max17040_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा max17040_chip *chip;
	पूर्णांक last_soc, last_status;

	chip = container_of(work, काष्ठा max17040_chip, work.work);

	/* store SOC and status to check changes */
	last_soc = chip->soc;
	last_status = chip->status;
	max17040_check_changes(chip);

	/* check changes and send uevent */
	अगर (last_soc != chip->soc || last_status != chip->status)
		घातer_supply_changed(chip->battery);

	max17040_queue_work(chip);
पूर्ण

/* Returns true अगर alert cause was SOC change, not low SOC */
अटल bool max17040_handle_soc_alert(काष्ठा max17040_chip *chip)
अणु
	bool ret = true;
	u32 data;

	regmap_पढ़ो(chip->regmap, MAX17040_STATUS, &data);

	अगर (data & MAX17040_STATUS_HD_MASK) अणु
		// this alert was caused by low soc
		ret = false;
	पूर्ण
	अगर (data & MAX17040_STATUS_SC_MASK) अणु
		// soc change bit -- deनिश्चित to mark as handled
		regmap_ग_लिखो(chip->regmap, MAX17040_STATUS,
				data & ~MAX17040_STATUS_SC_MASK);
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t max17040_thपढ़ो_handler(पूर्णांक id, व्योम *dev)
अणु
	काष्ठा max17040_chip *chip = dev;

	अगर (!(chip->data.has_soc_alert && max17040_handle_soc_alert(chip)))
		dev_warn(&chip->client->dev, "IRQ: Alert battery low level\n");

	/* पढ़ो रेजिस्टरs */
	max17040_check_changes(chip);

	/* send uevent */
	घातer_supply_changed(chip->battery);

	/* reset alert bit */
	max17040_set_low_soc_alert(chip, chip->low_soc_alert);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक max17040_enable_alert_irq(काष्ठा max17040_chip *chip)
अणु
	काष्ठा i2c_client *client = chip->client;
	अचिन्हित पूर्णांक flags;
	पूर्णांक ret;

	flags = IRQF_TRIGGER_FALLING | IRQF_ONESHOT;
	ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq, शून्य,
					max17040_thपढ़ो_handler, flags,
					chip->battery->desc->name, chip);

	वापस ret;
पूर्ण

अटल पूर्णांक max17040_prop_ग_लिखोable(काष्ठा घातer_supply *psy,
				   क्रमागत घातer_supply_property psp)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक max17040_set_property(काष्ठा घातer_supply *psy,
			    क्रमागत घातer_supply_property psp,
			    स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा max17040_chip *chip = घातer_supply_get_drvdata(psy);
	पूर्णांक ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN:
		/* alert threshold can be programmed from 1% up to 16/32% */
		अगर ((val->पूर्णांकval < 1) ||
		    (val->पूर्णांकval > (chip->quirk_द्विगुन_soc ? 16 : 32))) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		ret = max17040_set_low_soc_alert(chip, val->पूर्णांकval);
		chip->low_soc_alert = val->पूर्णांकval;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक max17040_get_property(काष्ठा घातer_supply *psy,
			    क्रमागत घातer_supply_property psp,
			    जोड़ घातer_supply_propval *val)
अणु
	काष्ठा max17040_chip *chip = घातer_supply_get_drvdata(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = max17040_get_status(chip);
		अवरोध;
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = max17040_get_online(chip);
		अवरोध;
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->पूर्णांकval = max17040_get_vcell(chip);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY:
		val->पूर्णांकval = max17040_get_soc(chip);
		अवरोध;
	हाल POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN:
		val->पूर्णांकval = chip->low_soc_alert;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config max17040_regmap = अणु
	.reg_bits	= 8,
	.reg_stride	= 2,
	.val_bits	= 16,
	.val_क्रमmat_endian = REGMAP_ENDIAN_BIG,
पूर्ण;

अटल क्रमागत घातer_supply_property max17040_battery_props[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_ALERT_MIN,
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc max17040_battery_desc = अणु
	.name			= "battery",
	.type			= POWER_SUPPLY_TYPE_BATTERY,
	.get_property		= max17040_get_property,
	.set_property		= max17040_set_property,
	.property_is_ग_लिखोable  = max17040_prop_ग_लिखोable,
	.properties		= max17040_battery_props,
	.num_properties		= ARRAY_SIZE(max17040_battery_props),
पूर्ण;

अटल पूर्णांक max17040_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा max17040_chip *chip;
	क्रमागत chip_id chip_id;
	bool enable_irq = false;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE))
		वापस -EIO;

	chip = devm_kzalloc(&client->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->client = client;
	chip->regmap = devm_regmap_init_i2c(client, &max17040_regmap);
	chip->pdata = client->dev.platक्रमm_data;
	chip_id = (क्रमागत chip_id) id->driver_data;
	अगर (client->dev.of_node) अणु
		ret = max17040_get_of_data(chip);
		अगर (ret)
			वापस ret;
		chip_id = (uपूर्णांकptr_t)of_device_get_match_data(&client->dev);
	पूर्ण
	chip->data = max17040_family[chip_id];

	i2c_set_clientdata(client, chip);
	psy_cfg.drv_data = chip;

	chip->battery = devm_घातer_supply_रेजिस्टर(&client->dev,
				&max17040_battery_desc, &psy_cfg);
	अगर (IS_ERR(chip->battery)) अणु
		dev_err(&client->dev, "failed: power supply register\n");
		वापस PTR_ERR(chip->battery);
	पूर्ण

	ret = max17040_get_version(chip);
	अगर (ret < 0)
		वापस ret;
	dev_dbg(&chip->client->dev, "MAX17040 Fuel-Gauge Ver 0x%x\n", ret);

	अगर (chip_id == ID_MAX17040 || chip_id == ID_MAX17041)
		max17040_reset(chip);

	max17040_set_rcomp(chip, chip->rcomp);

	/* check पूर्णांकerrupt */
	अगर (client->irq && chip->data.has_low_soc_alert) अणु
		ret = max17040_set_low_soc_alert(chip, chip->low_soc_alert);
		अगर (ret) अणु
			dev_err(&client->dev,
				"Failed to set low SOC alert: err %d\n", ret);
			वापस ret;
		पूर्ण

		enable_irq = true;
	पूर्ण

	अगर (client->irq && chip->data.has_soc_alert) अणु
		ret = max17040_set_soc_alert(chip, 1);
		अगर (ret) अणु
			dev_err(&client->dev,
				"Failed to set SOC alert: err %d\n", ret);
			वापस ret;
		पूर्ण
		enable_irq = true;
	पूर्ण अन्यथा अणु
		/* soc alerts negate the need क्रम polling */
		INIT_DEFERRABLE_WORK(&chip->work, max17040_work);
		ret = devm_add_action(&client->dev, max17040_stop_work, chip);
		अगर (ret)
			वापस ret;
		max17040_queue_work(chip);
	पूर्ण

	अगर (enable_irq) अणु
		ret = max17040_enable_alert_irq(chip);
		अगर (ret) अणु
			client->irq = 0;
			dev_warn(&client->dev,
				 "Failed to get IRQ err %d\n", ret);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक max17040_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा max17040_chip *chip = i2c_get_clientdata(client);

	अगर (client->irq && chip->data.has_soc_alert)
		// disable soc alert to prevent wakeup
		max17040_set_soc_alert(chip, 0);
	अन्यथा
		cancel_delayed_work(&chip->work);

	अगर (client->irq && device_may_wakeup(dev))
		enable_irq_wake(client->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक max17040_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा max17040_chip *chip = i2c_get_clientdata(client);

	अगर (client->irq && device_may_wakeup(dev))
		disable_irq_wake(client->irq);

	अगर (client->irq && chip->data.has_soc_alert)
		max17040_set_soc_alert(chip, 1);
	अन्यथा
		max17040_queue_work(chip);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(max17040_pm_ops, max17040_suspend, max17040_resume);
#घोषणा MAX17040_PM_OPS (&max17040_pm_ops)

#अन्यथा

#घोषणा MAX17040_PM_OPS शून्य

#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा i2c_device_id max17040_id[] = अणु
	अणु "max17040", ID_MAX17040 पूर्ण,
	अणु "max17041", ID_MAX17041 पूर्ण,
	अणु "max17043", ID_MAX17043 पूर्ण,
	अणु "max77836-battery", ID_MAX17043 पूर्ण,
	अणु "max17044", ID_MAX17044 पूर्ण,
	अणु "max17048", ID_MAX17048 पूर्ण,
	अणु "max17049", ID_MAX17049 पूर्ण,
	अणु "max17058", ID_MAX17058 पूर्ण,
	अणु "max17059", ID_MAX17059 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max17040_id);

अटल स्थिर काष्ठा of_device_id max17040_of_match[] = अणु
	अणु .compatible = "maxim,max17040", .data = (व्योम *) ID_MAX17040 पूर्ण,
	अणु .compatible = "maxim,max17041", .data = (व्योम *) ID_MAX17041 पूर्ण,
	अणु .compatible = "maxim,max17043", .data = (व्योम *) ID_MAX17043 पूर्ण,
	अणु .compatible = "maxim,max77836-battery", .data = (व्योम *) ID_MAX17043 पूर्ण,
	अणु .compatible = "maxim,max17044", .data = (व्योम *) ID_MAX17044 पूर्ण,
	अणु .compatible = "maxim,max17048", .data = (व्योम *) ID_MAX17048 पूर्ण,
	अणु .compatible = "maxim,max17049", .data = (व्योम *) ID_MAX17049 पूर्ण,
	अणु .compatible = "maxim,max17058", .data = (व्योम *) ID_MAX17058 पूर्ण,
	अणु .compatible = "maxim,max17059", .data = (व्योम *) ID_MAX17059 पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, max17040_of_match);

अटल काष्ठा i2c_driver max17040_i2c_driver = अणु
	.driver	= अणु
		.name	= "max17040",
		.of_match_table = max17040_of_match,
		.pm	= MAX17040_PM_OPS,
	पूर्ण,
	.probe		= max17040_probe,
	.id_table	= max17040_id,
पूर्ण;
module_i2c_driver(max17040_i2c_driver);

MODULE_AUTHOR("Minkyu Kang <mk7.kang@samsung.com>");
MODULE_DESCRIPTION("MAX17040 Fuel Gauge");
MODULE_LICENSE("GPL");
