<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2016, Prodys S.L.
 *
 * This adds support क्रम sbs-अक्षरger compilant chips as defined here:
 * http://sbs-क्रमum.org/specs/sbc110.pdf
 *
 * Implemetation based on sbs-battery.c
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/regmap.h>
#समावेश <linux/bitops.h>

#घोषणा SBS_CHARGER_REG_SPEC_INFO		0x11
#घोषणा SBS_CHARGER_REG_STATUS			0x13
#घोषणा SBS_CHARGER_REG_ALARM_WARNING		0x16

#घोषणा SBS_CHARGER_STATUS_CHARGE_INHIBITED	BIT(1)
#घोषणा SBS_CHARGER_STATUS_RES_COLD		BIT(9)
#घोषणा SBS_CHARGER_STATUS_RES_HOT		BIT(10)
#घोषणा SBS_CHARGER_STATUS_BATTERY_PRESENT	BIT(14)
#घोषणा SBS_CHARGER_STATUS_AC_PRESENT		BIT(15)

#घोषणा SBS_CHARGER_POLL_TIME			500

काष्ठा sbs_info अणु
	काष्ठा i2c_client		*client;
	काष्ठा घातer_supply		*घातer_supply;
	काष्ठा regmap			*regmap;
	काष्ठा delayed_work		work;
	अचिन्हित पूर्णांक			last_state;
पूर्ण;

अटल पूर्णांक sbs_get_property(काष्ठा घातer_supply *psy,
			    क्रमागत घातer_supply_property psp,
			    जोड़ घातer_supply_propval *val)
अणु
	काष्ठा sbs_info *chip = घातer_supply_get_drvdata(psy);
	अचिन्हित पूर्णांक reg;

	reg = chip->last_state;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_PRESENT:
		val->पूर्णांकval = !!(reg & SBS_CHARGER_STATUS_BATTERY_PRESENT);
		अवरोध;

	हाल POWER_SUPPLY_PROP_ONLINE:
		val->पूर्णांकval = !!(reg & SBS_CHARGER_STATUS_AC_PRESENT);
		अवरोध;

	हाल POWER_SUPPLY_PROP_STATUS:
		val->पूर्णांकval = POWER_SUPPLY_STATUS_UNKNOWN;

		अगर (!(reg & SBS_CHARGER_STATUS_BATTERY_PRESENT))
			val->पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		अन्यथा अगर (reg & SBS_CHARGER_STATUS_AC_PRESENT &&
			 !(reg & SBS_CHARGER_STATUS_CHARGE_INHIBITED))
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;

		अवरोध;

	हाल POWER_SUPPLY_PROP_HEALTH:
		अगर (reg & SBS_CHARGER_STATUS_RES_COLD)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_COLD;
		अगर (reg & SBS_CHARGER_STATUS_RES_HOT)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERHEAT;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;

		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sbs_check_state(काष्ठा sbs_info *chip)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	ret = regmap_पढ़ो(chip->regmap, SBS_CHARGER_REG_STATUS, &reg);
	अगर (!ret && reg != chip->last_state) अणु
		chip->last_state = reg;
		घातer_supply_changed(chip->घातer_supply);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sbs_delayed_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sbs_info *chip = container_of(work, काष्ठा sbs_info, work.work);

	sbs_check_state(chip);

	schedule_delayed_work(&chip->work,
			      msecs_to_jअगरfies(SBS_CHARGER_POLL_TIME));
पूर्ण

अटल irqवापस_t sbs_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sbs_info *chip = data;
	पूर्णांक ret;

	ret = sbs_check_state(chip);

	वापस ret ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल क्रमागत घातer_supply_property sbs_properties[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_HEALTH,
पूर्ण;

अटल bool sbs_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस reg >= SBS_CHARGER_REG_SPEC_INFO;
पूर्ण

अटल bool sbs_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल SBS_CHARGER_REG_STATUS:
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config sbs_regmap = अणु
	.reg_bits	= 8,
	.val_bits	= 16,
	.max_रेजिस्टर	= SBS_CHARGER_REG_ALARM_WARNING,
	.पढ़ोable_reg	= sbs_पढ़ोable_reg,
	.अस्थिर_reg	= sbs_अस्थिर_reg,
	.val_क्रमmat_endian = REGMAP_ENDIAN_LITTLE, /* since based on SMBus */
पूर्ण;

अटल स्थिर काष्ठा घातer_supply_desc sbs_desc = अणु
	.name = "sbs-charger",
	.type = POWER_SUPPLY_TYPE_MAINS,
	.properties = sbs_properties,
	.num_properties = ARRAY_SIZE(sbs_properties),
	.get_property = sbs_get_property,
पूर्ण;

अटल पूर्णांक sbs_probe(काष्ठा i2c_client *client,
		     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	काष्ठा sbs_info *chip;
	पूर्णांक ret, val;

	chip = devm_kzalloc(&client->dev, माप(काष्ठा sbs_info), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->client = client;
	psy_cfg.of_node = client->dev.of_node;
	psy_cfg.drv_data = chip;

	i2c_set_clientdata(client, chip);

	chip->regmap = devm_regmap_init_i2c(client, &sbs_regmap);
	अगर (IS_ERR(chip->regmap))
		वापस PTR_ERR(chip->regmap);

	/*
	 * Beक्रमe we रेजिस्टर, we need to make sure we can actually talk
	 * to the battery.
	 */
	ret = regmap_पढ़ो(chip->regmap, SBS_CHARGER_REG_STATUS, &val);
	अगर (ret)
		वापस dev_err_probe(&client->dev, ret, "Failed to get device status\n");
	chip->last_state = val;

	chip->घातer_supply = devm_घातer_supply_रेजिस्टर(&client->dev, &sbs_desc, &psy_cfg);
	अगर (IS_ERR(chip->घातer_supply))
		वापस dev_err_probe(&client->dev, PTR_ERR(chip->घातer_supply),
				     "Failed to register power supply\n");

	/*
	 * The sbs-अक्षरger spec करोesn't impose the use of an पूर्णांकerrupt. So in
	 * the हाल it wasn't provided we use polling in order get the charger's
	 * status.
	 */
	अगर (client->irq) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					शून्य, sbs_irq_thपढ़ो,
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					dev_name(&client->dev), chip);
		अगर (ret)
			वापस dev_err_probe(&client->dev, ret, "Failed to request irq\n");
	पूर्ण अन्यथा अणु
		INIT_DELAYED_WORK(&chip->work, sbs_delayed_work);
		schedule_delayed_work(&chip->work,
				      msecs_to_jअगरfies(SBS_CHARGER_POLL_TIME));
	पूर्ण

	dev_info(&client->dev,
		 "%s: smart charger device registered\n", client->name);

	वापस 0;
पूर्ण

अटल पूर्णांक sbs_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा sbs_info *chip = i2c_get_clientdata(client);

	cancel_delayed_work_sync(&chip->work);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id sbs_dt_ids[] = अणु
	अणु .compatible = "sbs,sbs-charger" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sbs_dt_ids);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id sbs_id[] = अणु
	अणु "sbs-charger", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sbs_id);

अटल काष्ठा i2c_driver sbs_driver = अणु
	.probe		= sbs_probe,
	.हटाओ		= sbs_हटाओ,
	.id_table	= sbs_id,
	.driver = अणु
		.name	= "sbs-charger",
		.of_match_table = of_match_ptr(sbs_dt_ids),
	पूर्ण,
पूर्ण;
module_i2c_driver(sbs_driver);

MODULE_AUTHOR("Nicolas Saenz Julienne <nicolassaenzj@gmail.com>");
MODULE_DESCRIPTION("SBS smart charger driver");
MODULE_LICENSE("GPL v2");
