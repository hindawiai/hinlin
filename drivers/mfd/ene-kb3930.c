<शैली गुरु>
// SPDX-License-Identअगरier: BSD-2-Clause OR GPL-2.0-or-later
/*
 * ENE KB3930 Embedded Controller Driver
 *
 * Copyright (C) 2020 Lubomir Rपूर्णांकel
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/module.h>
#समावेश <linux/reboot.h>
#समावेश <linux/regmap.h>

/* I2C रेजिस्टरs that are multiplexing access to the EC RAM. */
क्रमागत अणु
	EC_DATA_IN	= 0x00,
	EC_RAM_OUT	= 0x80,
	EC_RAM_IN	= 0x81,
पूर्ण;

/* EC RAM रेजिस्टरs. */
क्रमागत अणु
	EC_MODEL	= 0x30,
	EC_VERSION_MAJ	= 0x31,
	EC_VERSION_MIN	= 0x32,
पूर्ण;

काष्ठा kb3930 अणु
	काष्ठा i2c_client *client;
	काष्ठा regmap *ram_regmap;
	काष्ठा gpio_descs *off_gpios;
पूर्ण;

अटल काष्ठा kb3930 *kb3930_घातer_off;

#घोषणा EC_GPIO_WAVE		0
#घोषणा EC_GPIO_OFF_MODE	1

#घोषणा EC_OFF_MODE_REBOOT	0
#घोषणा EC_OFF_MODE_POWER	1

अटल व्योम kb3930_off(काष्ठा kb3930 *ddata, पूर्णांक off_mode)
अणु
	gpiod_direction_output(ddata->off_gpios->desc[EC_GPIO_OFF_MODE],
			       off_mode);

	/*
	 * This creates a 10 Hz wave on EC_GPIO_WAVE that संकेतs a
	 * shutकरोwn request to the EC. Once the EC detects it, it will
	 * proceed to turn the घातer off or reset the board depending on
	 * the value of EC_GPIO_OFF_MODE.
	 */
	जबतक (1) अणु
		mdelay(50);
		gpiod_direction_output(ddata->off_gpios->desc[EC_GPIO_WAVE], 0);
		mdelay(50);
		gpiod_direction_output(ddata->off_gpios->desc[EC_GPIO_WAVE], 1);
	पूर्ण
पूर्ण

अटल पूर्णांक kb3930_restart(काष्ठा notअगरier_block *this,
			  अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	kb3930_off(kb3930_घातer_off, EC_OFF_MODE_REBOOT);
	वापस NOTIFY_DONE;
पूर्ण

अटल व्योम kb3930_pm_घातer_off(व्योम)
अणु
	kb3930_off(kb3930_घातer_off, EC_OFF_MODE_POWER);
पूर्ण

अटल काष्ठा notअगरier_block kb3930_restart_nb = अणु
	.notअगरier_call = kb3930_restart,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell ariel_ec_cells[] = अणु
	अणु .name = "dell-wyse-ariel-led", पूर्ण,
	अणु .name = "dell-wyse-ariel-power", पूर्ण,
पूर्ण;

अटल पूर्णांक kb3930_ec_ram_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
				   अचिन्हित पूर्णांक val)
अणु
	काष्ठा kb3930 *ddata = context;

	वापस i2c_smbus_ग_लिखो_word_data(ddata->client, EC_RAM_OUT,
					 (val << 8) | reg);
पूर्ण

अटल पूर्णांक kb3930_ec_ram_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
				  अचिन्हित पूर्णांक *val)
अणु
	काष्ठा kb3930 *ddata = context;
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_word_data(ddata->client, EC_RAM_IN, reg);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_पढ़ो_word_data(ddata->client, EC_DATA_IN);
	अगर (ret < 0)
		वापस ret;

	*val = ret >> 8;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा regmap_config kb3930_ram_regmap_config = अणु
	.name = "ec_ram",
	.reg_bits = 8,
	.val_bits = 8,
	.reg_stride = 1,
	.max_रेजिस्टर = 0xff,
	.reg_ग_लिखो = kb3930_ec_ram_reg_ग_लिखो,
	.reg_पढ़ो = kb3930_ec_ram_reg_पढ़ो,
	.fast_io = false,
पूर्ण;

अटल पूर्णांक kb3930_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा kb3930 *ddata;
	अचिन्हित पूर्णांक model;
	पूर्णांक ret;

	ddata = devm_kzalloc(dev, माप(*ddata), GFP_KERNEL);
	अगर (!ddata)
		वापस -ENOMEM;

	kb3930_घातer_off = ddata;
	ddata->client = client;
	i2c_set_clientdata(client, ddata);

	ddata->ram_regmap = devm_regmap_init(dev, शून्य, ddata,
					     &kb3930_ram_regmap_config);
	अगर (IS_ERR(ddata->ram_regmap))
		वापस PTR_ERR(ddata->ram_regmap);

	ret = regmap_पढ़ो(ddata->ram_regmap, EC_MODEL, &model);
	अगर (ret < 0)
		वापस ret;

	/* Currently we only support the cells present on Dell Ariel model. */
	अगर (model != 'J') अणु
		dev_err(dev, "unknown board model: %02x\n", model);
		वापस -ENODEV;
	पूर्ण

	ret = devm_mfd_add_devices(dev, PLATFORM_DEVID_AUTO,
				   ariel_ec_cells,
				   ARRAY_SIZE(ariel_ec_cells),
				   शून्य, 0, शून्य);
	अगर (ret)
		वापस ret;

	अगर (of_property_पढ़ो_bool(np, "system-power-controller")) अणु
		ddata->off_gpios =
			devm_gpiod_get_array_optional(dev, "off", GPIOD_IN);
		अगर (IS_ERR(ddata->off_gpios))
			वापस PTR_ERR(ddata->off_gpios);
		अगर (ddata->off_gpios->ndescs < 2) अणु
			dev_err(dev, "invalid off-gpios property\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (ddata->off_gpios) अणु
		रेजिस्टर_restart_handler(&kb3930_restart_nb);
		अगर (!pm_घातer_off)
			pm_घातer_off = kb3930_pm_घातer_off;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kb3930_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा kb3930 *ddata = i2c_get_clientdata(client);

	अगर (ddata->off_gpios) अणु
		अगर (pm_घातer_off == kb3930_pm_घातer_off)
			pm_घातer_off = शून्य;
		unरेजिस्टर_restart_handler(&kb3930_restart_nb);
	पूर्ण
	kb3930_घातer_off = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id kb3930_dt_ids[] = अणु
	अणु .compatible = "ene,kb3930" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, kb3930_dt_ids);

अटल काष्ठा i2c_driver kb3930_driver = अणु
	.probe_new = kb3930_probe,
	.हटाओ = kb3930_हटाओ,
	.driver = अणु
		.name = "ene-kb3930",
		.of_match_table = kb3930_dt_ids,
	पूर्ण,
पूर्ण;
module_i2c_driver(kb3930_driver);

MODULE_AUTHOR("Lubomir Rintel <lkundrak@v3.sk>");
MODULE_DESCRIPTION("ENE KB3930 Embedded Controller Driver");
MODULE_LICENSE("Dual BSD/GPL");
