<शैली गुरु>
/*
 * Battery अक्षरger driver क्रम TI BQ24735
 *
 * Copyright (c) 2013, NVIDIA CORPORATION.  All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 *
 * You should have received a copy of the GNU General Public License aदीर्घ
 * with this program; अगर not, ग_लिखो to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA  02110-1301, USA.
 */

#समावेश <linux/devm-helpers.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/slab.h>

#समावेश <linux/घातer/bq24735-अक्षरger.h>

#घोषणा BQ24735_CHG_OPT			0x12
#घोषणा BQ24735_CHG_OPT_CHARGE_DISABLE	(1 << 0)
#घोषणा BQ24735_CHG_OPT_AC_PRESENT	(1 << 4)
#घोषणा BQ24735_CHARGE_CURRENT		0x14
#घोषणा BQ24735_CHARGE_CURRENT_MASK	0x1fc0
#घोषणा BQ24735_CHARGE_VOLTAGE		0x15
#घोषणा BQ24735_CHARGE_VOLTAGE_MASK	0x7ff0
#घोषणा BQ24735_INPUT_CURRENT		0x3f
#घोषणा BQ24735_INPUT_CURRENT_MASK	0x1f80
#घोषणा BQ24735_MANUFACTURER_ID		0xfe
#घोषणा BQ24735_DEVICE_ID		0xff

काष्ठा bq24735 अणु
	काष्ठा घातer_supply		*अक्षरger;
	काष्ठा घातer_supply_desc	अक्षरger_desc;
	काष्ठा i2c_client		*client;
	काष्ठा bq24735_platक्रमm		*pdata;
	काष्ठा mutex			lock;
	काष्ठा gpio_desc		*status_gpio;
	काष्ठा delayed_work		poll;
	u32				poll_पूर्णांकerval;
	bool				अक्षरging;
पूर्ण;

अटल अंतरभूत काष्ठा bq24735 *to_bq24735(काष्ठा घातer_supply *psy)
अणु
	वापस घातer_supply_get_drvdata(psy);
पूर्ण

अटल क्रमागत घातer_supply_property bq24735_अक्षरger_properties[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_ONLINE,
पूर्ण;

अटल पूर्णांक bq24735_अक्षरger_property_is_ग_लिखोable(काष्ठा घातer_supply *psy,
						 क्रमागत घातer_supply_property psp)
अणु
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		वापस 1;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक bq24735_ग_लिखो_word(काष्ठा i2c_client *client, u8 reg,
				     u16 value)
अणु
	वापस i2c_smbus_ग_लिखो_word_data(client, reg, value);
पूर्ण

अटल अंतरभूत पूर्णांक bq24735_पढ़ो_word(काष्ठा i2c_client *client, u8 reg)
अणु
	वापस i2c_smbus_पढ़ो_word_data(client, reg);
पूर्ण

अटल पूर्णांक bq24735_update_word(काष्ठा i2c_client *client, u8 reg,
			       u16 mask, u16 value)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक ret;

	ret = bq24735_पढ़ो_word(client, reg);
	अगर (ret < 0)
		वापस ret;

	पंचांगp = ret & ~mask;
	पंचांगp |= value & mask;

	वापस bq24735_ग_लिखो_word(client, reg, पंचांगp);
पूर्ण

अटल पूर्णांक bq24735_config_अक्षरger(काष्ठा bq24735 *अक्षरger)
अणु
	काष्ठा bq24735_platक्रमm *pdata = अक्षरger->pdata;
	पूर्णांक ret;
	u16 value;

	अगर (pdata->ext_control)
		वापस 0;

	अगर (pdata->अक्षरge_current) अणु
		value = pdata->अक्षरge_current & BQ24735_CHARGE_CURRENT_MASK;

		ret = bq24735_ग_लिखो_word(अक्षरger->client,
					 BQ24735_CHARGE_CURRENT, value);
		अगर (ret < 0) अणु
			dev_err(&अक्षरger->client->dev,
				"Failed to write charger current : %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (pdata->अक्षरge_voltage) अणु
		value = pdata->अक्षरge_voltage & BQ24735_CHARGE_VOLTAGE_MASK;

		ret = bq24735_ग_लिखो_word(अक्षरger->client,
					 BQ24735_CHARGE_VOLTAGE, value);
		अगर (ret < 0) अणु
			dev_err(&अक्षरger->client->dev,
				"Failed to write charger voltage : %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (pdata->input_current) अणु
		value = pdata->input_current & BQ24735_INPUT_CURRENT_MASK;

		ret = bq24735_ग_लिखो_word(अक्षरger->client,
					 BQ24735_INPUT_CURRENT, value);
		अगर (ret < 0) अणु
			dev_err(&अक्षरger->client->dev,
				"Failed to write input current : %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक bq24735_enable_अक्षरging(काष्ठा bq24735 *अक्षरger)
अणु
	पूर्णांक ret;

	अगर (अक्षरger->pdata->ext_control)
		वापस 0;

	ret = bq24735_config_अक्षरger(अक्षरger);
	अगर (ret)
		वापस ret;

	वापस bq24735_update_word(अक्षरger->client, BQ24735_CHG_OPT,
				   BQ24735_CHG_OPT_CHARGE_DISABLE, 0);
पूर्ण

अटल अंतरभूत पूर्णांक bq24735_disable_अक्षरging(काष्ठा bq24735 *अक्षरger)
अणु
	अगर (अक्षरger->pdata->ext_control)
		वापस 0;

	वापस bq24735_update_word(अक्षरger->client, BQ24735_CHG_OPT,
				   BQ24735_CHG_OPT_CHARGE_DISABLE,
				   BQ24735_CHG_OPT_CHARGE_DISABLE);
पूर्ण

अटल bool bq24735_अक्षरger_is_present(काष्ठा bq24735 *अक्षरger)
अणु
	अगर (अक्षरger->status_gpio) अणु
		वापस !gpiod_get_value_cansleep(अक्षरger->status_gpio);
	पूर्ण अन्यथा अणु
		पूर्णांक ac = 0;

		ac = bq24735_पढ़ो_word(अक्षरger->client, BQ24735_CHG_OPT);
		अगर (ac < 0) अणु
			dev_dbg(&अक्षरger->client->dev,
				"Failed to read charger options : %d\n",
				ac);
			वापस false;
		पूर्ण
		वापस (ac & BQ24735_CHG_OPT_AC_PRESENT) ? true : false;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक bq24735_अक्षरger_is_अक्षरging(काष्ठा bq24735 *अक्षरger)
अणु
	पूर्णांक ret;

	अगर (!bq24735_अक्षरger_is_present(अक्षरger))
		वापस 0;

	ret  = bq24735_पढ़ो_word(अक्षरger->client, BQ24735_CHG_OPT);
	अगर (ret < 0)
		वापस ret;

	वापस !(ret & BQ24735_CHG_OPT_CHARGE_DISABLE);
पूर्ण

अटल व्योम bq24735_update(काष्ठा bq24735 *अक्षरger)
अणु
	mutex_lock(&अक्षरger->lock);

	अगर (अक्षरger->अक्षरging && bq24735_अक्षरger_is_present(अक्षरger))
		bq24735_enable_अक्षरging(अक्षरger);
	अन्यथा
		bq24735_disable_अक्षरging(अक्षरger);

	mutex_unlock(&अक्षरger->lock);

	घातer_supply_changed(अक्षरger->अक्षरger);
पूर्ण

अटल irqवापस_t bq24735_अक्षरger_isr(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा घातer_supply *psy = devid;
	काष्ठा bq24735 *अक्षरger = to_bq24735(psy);

	bq24735_update(अक्षरger);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम bq24735_poll(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bq24735 *अक्षरger = container_of(work, काष्ठा bq24735, poll.work);

	bq24735_update(अक्षरger);

	schedule_delayed_work(&अक्षरger->poll,
			      msecs_to_jअगरfies(अक्षरger->poll_पूर्णांकerval));
पूर्ण

अटल पूर्णांक bq24735_अक्षरger_get_property(काष्ठा घातer_supply *psy,
					क्रमागत घातer_supply_property psp,
					जोड़ घातer_supply_propval *val)
अणु
	काष्ठा bq24735 *अक्षरger = to_bq24735(psy);

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = bq24735_अक्षरger_is_present(अक्षरger) ? 1 : 0;
		अवरोध;
	हाल POWER_SUPPLY_PROP_STATUS:
		चयन (bq24735_अक्षरger_is_अक्षरging(अक्षरger)) अणु
		हाल 1:
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
			अवरोध;
		हाल 0:
			val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
			अवरोध;
		शेष:
			val->पूर्णांकval = POWER_SUPPLY_STATUS_UNKNOWN;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bq24735_अक्षरger_set_property(काष्ठा घातer_supply *psy,
					क्रमागत घातer_supply_property psp,
					स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा bq24735 *अक्षरger = to_bq24735(psy);
	पूर्णांक ret;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_STATUS:
		चयन (val->पूर्णांकval) अणु
		हाल POWER_SUPPLY_STATUS_CHARGING:
			mutex_lock(&अक्षरger->lock);
			अक्षरger->अक्षरging = true;
			ret = bq24735_enable_अक्षरging(अक्षरger);
			mutex_unlock(&अक्षरger->lock);
			अगर (ret)
				वापस ret;
			अवरोध;
		हाल POWER_SUPPLY_STATUS_DISCHARGING:
		हाल POWER_SUPPLY_STATUS_NOT_CHARGING:
			mutex_lock(&अक्षरger->lock);
			अक्षरger->अक्षरging = false;
			ret = bq24735_disable_अक्षरging(अक्षरger);
			mutex_unlock(&अक्षरger->lock);
			अगर (ret)
				वापस ret;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		घातer_supply_changed(psy);
		अवरोध;
	शेष:
		वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा bq24735_platक्रमm *bq24735_parse_dt_data(काष्ठा i2c_client *client)
अणु
	काष्ठा bq24735_platक्रमm *pdata;
	काष्ठा device_node *np = client->dev.of_node;
	u32 val;
	पूर्णांक ret;

	pdata = devm_kzalloc(&client->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata) अणु
		dev_err(&client->dev,
			"Memory alloc for bq24735 pdata failed\n");
		वापस शून्य;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "ti,charge-current", &val);
	अगर (!ret)
		pdata->अक्षरge_current = val;

	ret = of_property_पढ़ो_u32(np, "ti,charge-voltage", &val);
	अगर (!ret)
		pdata->अक्षरge_voltage = val;

	ret = of_property_पढ़ो_u32(np, "ti,input-current", &val);
	अगर (!ret)
		pdata->input_current = val;

	pdata->ext_control = of_property_पढ़ो_bool(np, "ti,external-control");

	वापस pdata;
पूर्ण

अटल पूर्णांक bq24735_अक्षरger_probe(काष्ठा i2c_client *client,
				 स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा bq24735 *अक्षरger;
	काष्ठा घातer_supply_desc *supply_desc;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	अक्षर *name;

	अक्षरger = devm_kzalloc(&client->dev, माप(*अक्षरger), GFP_KERNEL);
	अगर (!अक्षरger)
		वापस -ENOMEM;

	mutex_init(&अक्षरger->lock);
	अक्षरger->अक्षरging = true;
	अक्षरger->pdata = client->dev.platक्रमm_data;

	अगर (IS_ENABLED(CONFIG_OF) && !अक्षरger->pdata && client->dev.of_node)
		अक्षरger->pdata = bq24735_parse_dt_data(client);

	अगर (!अक्षरger->pdata) अणु
		dev_err(&client->dev, "no platform data provided\n");
		वापस -EINVAL;
	पूर्ण

	name = (अक्षर *)अक्षरger->pdata->name;
	अगर (!name) अणु
		name = devm_kaप्र_लिखो(&client->dev, GFP_KERNEL,
				      "bq24735@%s",
				      dev_name(&client->dev));
		अगर (!name) अणु
			dev_err(&client->dev, "Failed to alloc device name\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अक्षरger->client = client;

	supply_desc = &अक्षरger->अक्षरger_desc;

	supply_desc->name = name;
	supply_desc->type = POWER_SUPPLY_TYPE_MAINS;
	supply_desc->properties = bq24735_अक्षरger_properties;
	supply_desc->num_properties = ARRAY_SIZE(bq24735_अक्षरger_properties);
	supply_desc->get_property = bq24735_अक्षरger_get_property;
	supply_desc->set_property = bq24735_अक्षरger_set_property;
	supply_desc->property_is_ग_लिखोable =
				bq24735_अक्षरger_property_is_ग_लिखोable;

	psy_cfg.supplied_to = अक्षरger->pdata->supplied_to;
	psy_cfg.num_supplicants = अक्षरger->pdata->num_supplicants;
	psy_cfg.of_node = client->dev.of_node;
	psy_cfg.drv_data = अक्षरger;

	i2c_set_clientdata(client, अक्षरger);

	अक्षरger->status_gpio = devm_gpiod_get_optional(&client->dev,
						       "ti,ac-detect",
						       GPIOD_IN);
	अगर (IS_ERR(अक्षरger->status_gpio)) अणु
		ret = PTR_ERR(अक्षरger->status_gpio);
		dev_err(&client->dev, "Getting gpio failed: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (bq24735_अक्षरger_is_present(अक्षरger)) अणु
		ret = bq24735_पढ़ो_word(client, BQ24735_MANUFACTURER_ID);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "Failed to read manufacturer id : %d\n",
				ret);
			वापस ret;
		पूर्ण अन्यथा अगर (ret != 0x0040) अणु
			dev_err(&client->dev,
				"manufacturer id mismatch. 0x0040 != 0x%04x\n", ret);
			वापस -ENODEV;
		पूर्ण

		ret = bq24735_पढ़ो_word(client, BQ24735_DEVICE_ID);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "Failed to read device id : %d\n", ret);
			वापस ret;
		पूर्ण अन्यथा अगर (ret != 0x000B) अणु
			dev_err(&client->dev,
				"device id mismatch. 0x000b != 0x%04x\n", ret);
			वापस -ENODEV;
		पूर्ण

		ret = bq24735_enable_अक्षरging(अक्षरger);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "Failed to enable charging\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अक्षरger->अक्षरger = devm_घातer_supply_रेजिस्टर(&client->dev, supply_desc,
						      &psy_cfg);
	अगर (IS_ERR(अक्षरger->अक्षरger)) अणु
		ret = PTR_ERR(अक्षरger->अक्षरger);
		dev_err(&client->dev, "Failed to register power supply: %d\n",
			ret);
		वापस ret;
	पूर्ण

	अगर (client->irq) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
						शून्य, bq24735_अक्षरger_isr,
						IRQF_TRIGGER_RISING |
						IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT,
						supply_desc->name,
						अक्षरger->अक्षरger);
		अगर (ret) अणु
			dev_err(&client->dev,
				"Unable to register IRQ %d err %d\n",
				client->irq, ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		ret = device_property_पढ़ो_u32(&client->dev, "poll-interval",
					       &अक्षरger->poll_पूर्णांकerval);
		अगर (ret)
			वापस 0;
		अगर (!अक्षरger->poll_पूर्णांकerval)
			वापस 0;

		ret = devm_delayed_work_स्वतःcancel(&client->dev, &अक्षरger->poll,
						   bq24735_poll);
		अगर (ret)
			वापस ret;

		schedule_delayed_work(&अक्षरger->poll,
				      msecs_to_jअगरfies(अक्षरger->poll_पूर्णांकerval));
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id bq24735_अक्षरger_id[] = अणु
	अणु "bq24735-charger", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bq24735_अक्षरger_id);

अटल स्थिर काष्ठा of_device_id bq24735_match_ids[] = अणु
	अणु .compatible = "ti,bq24735", पूर्ण,
	अणु /* end */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bq24735_match_ids);

अटल काष्ठा i2c_driver bq24735_अक्षरger_driver = अणु
	.driver = अणु
		.name = "bq24735-charger",
		.of_match_table = bq24735_match_ids,
	पूर्ण,
	.probe = bq24735_अक्षरger_probe,
	.id_table = bq24735_अक्षरger_id,
पूर्ण;

module_i2c_driver(bq24735_अक्षरger_driver);

MODULE_DESCRIPTION("bq24735 battery charging driver");
MODULE_AUTHOR("Darbha Sriharsha <dsriharsha@nvidia.com>");
MODULE_LICENSE("GPL v2");
