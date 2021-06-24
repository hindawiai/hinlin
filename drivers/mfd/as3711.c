<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AS3711 PMIC MFC driver
 *
 * Copyright (C) 2012 Renesas Electronics Corporation
 * Author: Guennadi Liakhovetski, <g.liakhovetski@gmx.de>
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/as3711.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

क्रमागत अणु
	AS3711_REGULATOR,
	AS3711_BACKLIGHT,
पूर्ण;

/*
 * Ok to have it अटल: it is only used during probing and multiple I2C devices
 * cannot be probed simultaneously. Just make sure to aव्योम stale data.
 */
अटल काष्ठा mfd_cell as3711_subdevs[] = अणु
	[AS3711_REGULATOR] = अणु.name = "as3711-regulator",पूर्ण,
	[AS3711_BACKLIGHT] = अणु.name = "as3711-backlight",पूर्ण,
पूर्ण;

अटल bool as3711_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल AS3711_GPIO_SIGNAL_IN:
	हाल AS3711_INTERRUPT_STATUS_1:
	हाल AS3711_INTERRUPT_STATUS_2:
	हाल AS3711_INTERRUPT_STATUS_3:
	हाल AS3711_CHARGER_STATUS_1:
	हाल AS3711_CHARGER_STATUS_2:
	हाल AS3711_REG_STATUS:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool as3711_precious_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल AS3711_INTERRUPT_STATUS_1:
	हाल AS3711_INTERRUPT_STATUS_2:
	हाल AS3711_INTERRUPT_STATUS_3:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool as3711_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल AS3711_SD_1_VOLTAGE:
	हाल AS3711_SD_2_VOLTAGE:
	हाल AS3711_SD_3_VOLTAGE:
	हाल AS3711_SD_4_VOLTAGE:
	हाल AS3711_LDO_1_VOLTAGE:
	हाल AS3711_LDO_2_VOLTAGE:
	हाल AS3711_LDO_3_VOLTAGE:
	हाल AS3711_LDO_4_VOLTAGE:
	हाल AS3711_LDO_5_VOLTAGE:
	हाल AS3711_LDO_6_VOLTAGE:
	हाल AS3711_LDO_7_VOLTAGE:
	हाल AS3711_LDO_8_VOLTAGE:
	हाल AS3711_SD_CONTROL:
	हाल AS3711_GPIO_SIGNAL_OUT:
	हाल AS3711_GPIO_SIGNAL_IN:
	हाल AS3711_SD_CONTROL_1:
	हाल AS3711_SD_CONTROL_2:
	हाल AS3711_CURR_CONTROL:
	हाल AS3711_CURR1_VALUE:
	हाल AS3711_CURR2_VALUE:
	हाल AS3711_CURR3_VALUE:
	हाल AS3711_STEPUP_CONTROL_1:
	हाल AS3711_STEPUP_CONTROL_2:
	हाल AS3711_STEPUP_CONTROL_4:
	हाल AS3711_STEPUP_CONTROL_5:
	हाल AS3711_REG_STATUS:
	हाल AS3711_INTERRUPT_STATUS_1:
	हाल AS3711_INTERRUPT_STATUS_2:
	हाल AS3711_INTERRUPT_STATUS_3:
	हाल AS3711_CHARGER_STATUS_1:
	हाल AS3711_CHARGER_STATUS_2:
	हाल AS3711_ASIC_ID_1:
	हाल AS3711_ASIC_ID_2:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config as3711_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.अस्थिर_reg = as3711_अस्थिर_reg,
	.पढ़ोable_reg = as3711_पढ़ोable_reg,
	.precious_reg = as3711_precious_reg,
	.max_रेजिस्टर = AS3711_MAX_REG,
	.num_reg_शेषs_raw = AS3711_NUM_REGS,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id as3711_of_match[] = अणु
	अणु.compatible = "ams,as3711",पूर्ण,
	अणुपूर्ण
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक as3711_i2c_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा as3711 *as3711;
	काष्ठा as3711_platक्रमm_data *pdata;
	अचिन्हित पूर्णांक id1, id2;
	पूर्णांक ret;

	अगर (!client->dev.of_node) अणु
		pdata = dev_get_platdata(&client->dev);
		अगर (!pdata)
			dev_dbg(&client->dev, "Platform data not found\n");
	पूर्ण अन्यथा अणु
		pdata = devm_kzalloc(&client->dev,
				     माप(*pdata), GFP_KERNEL);
		अगर (!pdata)
			वापस -ENOMEM;
	पूर्ण

	as3711 = devm_kzalloc(&client->dev, माप(काष्ठा as3711), GFP_KERNEL);
	अगर (!as3711)
		वापस -ENOMEM;

	as3711->dev = &client->dev;
	i2c_set_clientdata(client, as3711);

	अगर (client->irq)
		dev_notice(&client->dev, "IRQ not supported yet\n");

	as3711->regmap = devm_regmap_init_i2c(client, &as3711_regmap_config);
	अगर (IS_ERR(as3711->regmap)) अणु
		ret = PTR_ERR(as3711->regmap);
		dev_err(&client->dev,
			"regmap initialization failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(as3711->regmap, AS3711_ASIC_ID_1, &id1);
	अगर (!ret)
		ret = regmap_पढ़ो(as3711->regmap, AS3711_ASIC_ID_2, &id2);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "regmap_read() failed: %d\n", ret);
		वापस ret;
	पूर्ण
	अगर (id1 != 0x8b)
		वापस -ENODEV;
	dev_info(as3711->dev, "AS3711 detected: %x:%x\n", id1, id2);

	/*
	 * We can reuse as3711_subdevs[],
	 * it will be copied in mfd_add_devices()
	 */
	अगर (pdata) अणु
		as3711_subdevs[AS3711_REGULATOR].platक्रमm_data =
			&pdata->regulator;
		as3711_subdevs[AS3711_REGULATOR].pdata_size =
			माप(pdata->regulator);
		as3711_subdevs[AS3711_BACKLIGHT].platक्रमm_data =
			&pdata->backlight;
		as3711_subdevs[AS3711_BACKLIGHT].pdata_size =
			माप(pdata->backlight);
	पूर्ण अन्यथा अणु
		as3711_subdevs[AS3711_REGULATOR].platक्रमm_data = शून्य;
		as3711_subdevs[AS3711_REGULATOR].pdata_size = 0;
		as3711_subdevs[AS3711_BACKLIGHT].platक्रमm_data = शून्य;
		as3711_subdevs[AS3711_BACKLIGHT].pdata_size = 0;
	पूर्ण

	ret = devm_mfd_add_devices(as3711->dev, -1, as3711_subdevs,
				   ARRAY_SIZE(as3711_subdevs), शून्य, 0, शून्य);
	अगर (ret < 0)
		dev_err(&client->dev, "add mfd devices failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id as3711_i2c_id[] = अणु
	अणु.name = "as3711", .driver_data = 0पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा i2c_driver as3711_i2c_driver = अणु
	.driver = अणु
		   .name = "as3711",
		   .of_match_table = of_match_ptr(as3711_of_match),
	पूर्ण,
	.probe = as3711_i2c_probe,
	.id_table = as3711_i2c_id,
पूर्ण;

अटल पूर्णांक __init as3711_i2c_init(व्योम)
अणु
	वापस i2c_add_driver(&as3711_i2c_driver);
पूर्ण
/* Initialise early */
subsys_initcall(as3711_i2c_init);
