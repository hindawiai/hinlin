<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम SBS compliant Smart Battery System Managers
 *
 * The device communicates via i2c at address 0x0a and multiplexes access to up
 * to four smart batteries at address 0x0b.
 *
 * Via sysfs पूर्णांकerface the online state and अक्षरge type are presented.
 *
 * Datasheet SBSM:    http://sbs-क्रमum.org/specs/sbsm100b.pdf
 * Datasheet LTC1760: http://cds.linear.com/करोcs/en/datasheet/1760fb.pdf
 *
 * Karl-Heinz Schneider <karl-heinz@schneider-inet.de>
 */

#समावेश <linux/gpio/driver.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-mux.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/property.h>

#घोषणा SBSM_MAX_BATS  4
#घोषणा SBSM_RETRY_CNT 3

/* रेजिस्टरs addresses */
#घोषणा SBSM_CMD_BATSYSSTATE     0x01
#घोषणा SBSM_CMD_BATSYSSTATECONT 0x02
#घोषणा SBSM_CMD_BATSYSINFO      0x04
#घोषणा SBSM_CMD_LTC             0x3c

#घोषणा SBSM_MASK_BAT_SUPPORTED  GENMASK(3, 0)
#घोषणा SBSM_MASK_CHARGE_BAT     GENMASK(7, 4)
#घोषणा SBSM_BIT_AC_PRESENT      BIT(0)
#घोषणा SBSM_BIT_TURBO           BIT(7)

#घोषणा SBSM_SMB_BAT_OFFSET      11
काष्ठा sbsm_data अणु
	काष्ठा i2c_client *client;
	काष्ठा i2c_mux_core *muxc;

	काष्ठा घातer_supply *psy;

	u8 cur_chan;          /* currently selected channel */
	काष्ठा gpio_chip chip;
	bool is_ltc1760;      /* special capabilities */

	अचिन्हित पूर्णांक supported_bats;
	अचिन्हित पूर्णांक last_state;
	अचिन्हित पूर्णांक last_state_cont;
पूर्ण;

अटल क्रमागत घातer_supply_property sbsm_props[] = अणु
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_CHARGE_TYPE,
पूर्ण;

अटल पूर्णांक sbsm_पढ़ो_word(काष्ठा i2c_client *client, u8 address)
अणु
	पूर्णांक reg, retries;

	क्रम (retries = SBSM_RETRY_CNT; retries > 0; retries--) अणु
		reg = i2c_smbus_पढ़ो_word_data(client, address);
		अगर (reg >= 0)
			अवरोध;
	पूर्ण

	अगर (reg < 0) अणु
		dev_err(&client->dev, "failed to read register 0x%02x\n",
			address);
	पूर्ण

	वापस reg;
पूर्ण

अटल पूर्णांक sbsm_ग_लिखो_word(काष्ठा i2c_client *client, u8 address, u16 word)
अणु
	पूर्णांक ret, retries;

	क्रम (retries = SBSM_RETRY_CNT; retries > 0; retries--) अणु
		ret = i2c_smbus_ग_लिखो_word_data(client, address, word);
		अगर (ret >= 0)
			अवरोध;
	पूर्ण
	अगर (ret < 0)
		dev_err(&client->dev, "failed to write to register 0x%02x\n",
			address);

	वापस ret;
पूर्ण

अटल पूर्णांक sbsm_get_property(काष्ठा घातer_supply *psy,
			     क्रमागत घातer_supply_property psp,
			     जोड़ घातer_supply_propval *val)
अणु
	काष्ठा sbsm_data *data = घातer_supply_get_drvdata(psy);
	पूर्णांक regval = 0;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ONLINE:
		regval = sbsm_पढ़ो_word(data->client, SBSM_CMD_BATSYSSTATECONT);
		अगर (regval < 0)
			वापस regval;
		val->पूर्णांकval = !!(regval & SBSM_BIT_AC_PRESENT);
		अवरोध;

	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		regval = sbsm_पढ़ो_word(data->client, SBSM_CMD_BATSYSSTATE);
		अगर (regval < 0)
			वापस regval;

		अगर ((regval & SBSM_MASK_CHARGE_BAT) == 0) अणु
			val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_NONE;
			वापस 0;
		पूर्ण
		val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_TRICKLE;

		अगर (data->is_ltc1760) अणु
			/* अक्षरge mode fast अगर turbo is active */
			regval = sbsm_पढ़ो_word(data->client, SBSM_CMD_LTC);
			अगर (regval < 0)
				वापस regval;
			अन्यथा अगर (regval & SBSM_BIT_TURBO)
				val->पूर्णांकval = POWER_SUPPLY_CHARGE_TYPE_FAST;
		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sbsm_prop_is_ग_लिखोable(काष्ठा घातer_supply *psy,
				  क्रमागत घातer_supply_property psp)
अणु
	काष्ठा sbsm_data *data = घातer_supply_get_drvdata(psy);

	वापस (psp == POWER_SUPPLY_PROP_CHARGE_TYPE) && data->is_ltc1760;
पूर्ण

अटल पूर्णांक sbsm_set_property(काष्ठा घातer_supply *psy,
			     क्रमागत घातer_supply_property psp,
			     स्थिर जोड़ घातer_supply_propval *val)
अणु
	काष्ठा sbsm_data *data = घातer_supply_get_drvdata(psy);
	पूर्णांक ret = -EINVAL;
	u16 regval;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_CHARGE_TYPE:
		/* ग_लिखो 1 to TURBO अगर type fast is given */
		अगर (!data->is_ltc1760)
			अवरोध;
		regval = val->पूर्णांकval ==
			 POWER_SUPPLY_CHARGE_TYPE_FAST ? SBSM_BIT_TURBO : 0;
		ret = sbsm_ग_लिखो_word(data->client, SBSM_CMD_LTC, regval);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Switch to battery
 * Parameter chan is directly the content of SMB_BAT* nibble
 */
अटल पूर्णांक sbsm_select(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा sbsm_data *data = i2c_mux_priv(muxc);
	काष्ठा device *dev = &data->client->dev;
	पूर्णांक ret = 0;
	u16 reg;

	अगर (data->cur_chan == chan)
		वापस ret;

	/* chan goes from 1 ... 4 */
	reg = BIT(SBSM_SMB_BAT_OFFSET + chan);
	ret = sbsm_ग_लिखो_word(data->client, SBSM_CMD_BATSYSSTATE, reg);
	अगर (ret)
		dev_err(dev, "Failed to select channel %i\n", chan);
	अन्यथा
		data->cur_chan = chan;

	वापस ret;
पूर्ण

अटल पूर्णांक sbsm_gpio_get_value(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक off)
अणु
	काष्ठा sbsm_data *data = gpiochip_get_data(gc);
	पूर्णांक ret;

	ret = sbsm_पढ़ो_word(data->client, SBSM_CMD_BATSYSSTATE);
	अगर (ret < 0)
		वापस ret;

	वापस ret & BIT(off);
पूर्ण

/*
 * This needs to be defined or the GPIO lib fails to रेजिस्टर the pin.
 * But the 'gpio' is always an input.
 */
अटल पूर्णांक sbsm_gpio_direction_input(काष्ठा gpio_chip *gc, अचिन्हित पूर्णांक off)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक sbsm_करो_alert(काष्ठा device *dev, व्योम *d)
अणु
	काष्ठा i2c_client *client = i2c_verअगरy_client(dev);
	काष्ठा i2c_driver *driver;

	अगर (!client || client->addr != 0x0b)
		वापस 0;

	device_lock(dev);
	अगर (client->dev.driver) अणु
		driver = to_i2c_driver(client->dev.driver);
		अगर (driver->alert)
			driver->alert(client, I2C_PROTOCOL_SMBUS_ALERT, 0);
		अन्यथा
			dev_warn(&client->dev, "no driver alert()!\n");
	पूर्ण अन्यथा अणु
		dev_dbg(&client->dev, "alert with no driver\n");
	पूर्ण
	device_unlock(dev);

	वापस -EBUSY;
पूर्ण

अटल व्योम sbsm_alert(काष्ठा i2c_client *client, क्रमागत i2c_alert_protocol prot,
		       अचिन्हित पूर्णांक d)
अणु
	काष्ठा sbsm_data *sbsm = i2c_get_clientdata(client);

	पूर्णांक ret, i, irq_bat = 0, state = 0;

	ret = sbsm_पढ़ो_word(sbsm->client, SBSM_CMD_BATSYSSTATE);
	अगर (ret >= 0) अणु
		irq_bat = ret ^ sbsm->last_state;
		sbsm->last_state = ret;
		state = ret;
	पूर्ण

	ret = sbsm_पढ़ो_word(sbsm->client, SBSM_CMD_BATSYSSTATECONT);
	अगर ((ret >= 0) &&
	    ((ret ^ sbsm->last_state_cont) & SBSM_BIT_AC_PRESENT)) अणु
		irq_bat |= sbsm->supported_bats & state;
		घातer_supply_changed(sbsm->psy);
	पूर्ण
	sbsm->last_state_cont = ret;

	क्रम (i = 0; i < SBSM_MAX_BATS; i++) अणु
		अगर (irq_bat & BIT(i)) अणु
			device_क्रम_each_child(&sbsm->muxc->adapter[i]->dev,
					      शून्य, sbsm_करो_alert);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक sbsm_gpio_setup(काष्ठा sbsm_data *data)
अणु
	काष्ठा gpio_chip *gc = &data->chip;
	काष्ठा i2c_client *client = data->client;
	काष्ठा device *dev = &client->dev;
	पूर्णांक ret;

	अगर (!device_property_present(dev, "gpio-controller"))
		वापस 0;

	ret  = sbsm_पढ़ो_word(client, SBSM_CMD_BATSYSSTATE);
	अगर (ret < 0)
		वापस ret;
	data->last_state = ret;

	ret  = sbsm_पढ़ो_word(client, SBSM_CMD_BATSYSSTATECONT);
	अगर (ret < 0)
		वापस ret;
	data->last_state_cont = ret;

	gc->get = sbsm_gpio_get_value;
	gc->direction_input  = sbsm_gpio_direction_input;
	gc->can_sleep = true;
	gc->base = -1;
	gc->ngpio = SBSM_MAX_BATS;
	gc->label = client->name;
	gc->parent = dev;
	gc->owner = THIS_MODULE;

	ret = devm_gpiochip_add_data(dev, gc, data);
	अगर (ret)
		वापस dev_err_probe(dev, ret, "devm_gpiochip_add_data failed\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc sbsm_शेष_psy_desc = अणु
	.type = POWER_SUPPLY_TYPE_MAINS,
	.properties = sbsm_props,
	.num_properties = ARRAY_SIZE(sbsm_props),
	.get_property = &sbsm_get_property,
	.set_property = &sbsm_set_property,
	.property_is_ग_लिखोable = &sbsm_prop_is_ग_लिखोable,
पूर्ण;

अटल व्योम sbsm_del_mux_adapter(व्योम *data)
अणु
	काष्ठा sbsm_data *sbsm = data;
	i2c_mux_del_adapters(sbsm->muxc);
पूर्ण

अटल पूर्णांक sbsm_probe(काष्ठा i2c_client *client,
		      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा sbsm_data *data;
	काष्ठा device *dev = &client->dev;
	काष्ठा घातer_supply_desc *psy_desc;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	पूर्णांक ret = 0, i;

	/* Device listens only at address 0x0a */
	अगर (client->addr != 0x0a)
		वापस -EINVAL;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WORD_DATA))
		वापस -EPFNOSUPPORT;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);

	data->client = client;
	data->is_ltc1760 = !!म_माला(id->name, "ltc1760");

	ret  = sbsm_पढ़ो_word(client, SBSM_CMD_BATSYSINFO);
	अगर (ret < 0)
		वापस ret;
	data->supported_bats = ret & SBSM_MASK_BAT_SUPPORTED;
	data->muxc = i2c_mux_alloc(adapter, dev, SBSM_MAX_BATS, 0,
				   I2C_MUX_LOCKED, &sbsm_select, शून्य);
	अगर (!data->muxc)
		वापस dev_err_probe(dev, -ENOMEM, "failed to alloc i2c mux\n");
	data->muxc->priv = data;

	ret = devm_add_action_or_reset(dev, sbsm_del_mux_adapter, data);
	अगर (ret)
		वापस ret;

	/* रेजिस्टर muxed i2c channels. One क्रम each supported battery */
	क्रम (i = 0; i < SBSM_MAX_BATS; ++i) अणु
		अगर (data->supported_bats & BIT(i)) अणु
			ret = i2c_mux_add_adapter(data->muxc, 0, i + 1, 0);
			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (ret)
		वापस dev_err_probe(dev, ret, "failed to register i2c mux channel %d\n", i + 1);

	psy_desc = devm_kmemdup(dev, &sbsm_शेष_psy_desc, माप(*psy_desc), GFP_KERNEL);
	अगर (!psy_desc)
		वापस -ENOMEM;

	psy_desc->name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "sbsm-%s", dev_name(&client->dev));
	अगर (!psy_desc->name)
		वापस -ENOMEM;

	ret = sbsm_gpio_setup(data);
	अगर (ret < 0)
		वापस ret;

	psy_cfg.drv_data = data;
	psy_cfg.of_node = dev->of_node;
	data->psy = devm_घातer_supply_रेजिस्टर(dev, psy_desc, &psy_cfg);
	अगर (IS_ERR(data->psy))
		वापस dev_err_probe(dev, PTR_ERR(data->psy),
				     "failed to register power supply %s\n", psy_desc->name);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id sbsm_ids[] = अणु
	अणु "sbs-manager", 0 पूर्ण,
	अणु "ltc1760",     0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sbsm_ids);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id sbsm_dt_ids[] = अणु
	अणु .compatible = "sbs,sbs-manager" पूर्ण,
	अणु .compatible = "lltc,ltc1760" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sbsm_dt_ids);
#पूर्ण_अगर

अटल काष्ठा i2c_driver sbsm_driver = अणु
	.driver = अणु
		.name = "sbsm",
		.of_match_table = of_match_ptr(sbsm_dt_ids),
	पूर्ण,
	.probe		= sbsm_probe,
	.alert		= sbsm_alert,
	.id_table	= sbsm_ids
पूर्ण;
module_i2c_driver(sbsm_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Karl-Heinz Schneider <karl-heinz@schneider-inet.de>");
MODULE_DESCRIPTION("SBSM Smart Battery System Manager");
