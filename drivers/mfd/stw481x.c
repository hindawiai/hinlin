<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Core driver क्रम STw4810/STw4811
 *
 * Copyright (C) 2013 ST-Ericsson SA
 * Written on behalf of Linaro क्रम ST-Ericsson
 *
 * Author: Linus Walleij <linus.walleij@linaro.org>
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/stw481x.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>

/*
 * This driver can only access the non-USB portions of STw4811, the रेजिस्टर
 * range 0x00-0x10 dealing with USB is bound to the two special I2C pins used
 * क्रम USB control.
 */

/* Registers inside the घातer control address space */
#घोषणा STW_PC_VCORE_SEL	0x05U
#घोषणा STW_PC_VAUX_SEL		0x06U
#घोषणा STW_PC_VPLL_SEL		0x07U

/**
 * stw481x_get_pctl_reg() - get a घातer control रेजिस्टर
 * @stw481x: handle to the stw481x chip
 * @reg: घातer control रेजिस्टर to fetch
 *
 * The घातer control रेजिस्टरs is a set of one-समय-programmable रेजिस्टरs
 * in its own रेजिस्टर space, accessed by writing addess bits to these
 * two रेजिस्टरs: bits 7,6,5 of PCTL_REG_LO corresponds to the 3 LSBs of
 * the address and bits 8,9 of PCTL_REG_HI corresponds to the 2 MSBs of
 * the address, क्रमming an address space of 5 bits, i.e. 32 रेजिस्टरs
 * 0x00 ... 0x1f can be obtained.
 */
अटल पूर्णांक stw481x_get_pctl_reg(काष्ठा stw481x *stw481x, u8 reg)
अणु
	u8 msb = (reg >> 3) & 0x03;
	u8 lsb = (reg << 5) & 0xe0;
	अचिन्हित पूर्णांक val;
	u8 vrfy;
	पूर्णांक ret;

	ret = regmap_ग_लिखो(stw481x->map, STW_PCTL_REG_HI, msb);
	अगर (ret)
		वापस ret;
	ret = regmap_ग_लिखो(stw481x->map, STW_PCTL_REG_LO, lsb);
	अगर (ret)
		वापस ret;
	ret = regmap_पढ़ो(stw481x->map, STW_PCTL_REG_HI, &val);
	अगर (ret)
		वापस ret;
	vrfy = (val & 0x03) << 3;
	ret = regmap_पढ़ो(stw481x->map, STW_PCTL_REG_LO, &val);
	अगर (ret)
		वापस ret;
	vrfy |= ((val >> 5) & 0x07);
	अगर (vrfy != reg)
		वापस -EIO;
	वापस (val >> 1) & 0x0f;
पूर्ण

अटल पूर्णांक stw481x_startup(काष्ठा stw481x *stw481x)
अणु
	/* Voltages multiplied by 100 */
	अटल स्थिर u8 vcore_val[] = अणु
		100, 105, 110, 115, 120, 122, 124, 126, 128,
		130, 132, 134, 136, 138, 140, 145
	पूर्ण;
	अटल स्थिर u8 vpll_val[] = अणु 105, 120, 130, 180 पूर्ण;
	अटल स्थिर u8 vaux_val[] = अणु 15, 18, 25, 28 पूर्ण;
	u8 vcore;
	u8 vcore_slp;
	u8 vpll;
	u8 vaux;
	bool vaux_en;
	bool it_warn;
	पूर्णांक ret;
	अचिन्हित पूर्णांक val;

	ret = regmap_पढ़ो(stw481x->map, STW_CONF1, &val);
	अगर (ret)
		वापस ret;
	vaux_en = !!(val & STW_CONF1_PDN_VAUX);
	it_warn = !!(val & STW_CONF1_IT_WARN);

	dev_info(&stw481x->client->dev, "voltages %s\n",
		(val & STW_CONF1_V_MONITORING) ? "OK" : "LOW");
	dev_info(&stw481x->client->dev, "MMC level shifter %s\n",
		(val & STW_CONF1_MMC_LS_STATUS) ? "high impedance" : "ON");
	dev_info(&stw481x->client->dev, "VMMC: %s\n",
		(val & STW_CONF1_PDN_VMMC) ? "ON" : "disabled");

	dev_info(&stw481x->client->dev, "STw481x power control registers:\n");

	ret = stw481x_get_pctl_reg(stw481x, STW_PC_VCORE_SEL);
	अगर (ret < 0)
		वापस ret;
	vcore = ret & 0x0f;

	ret = stw481x_get_pctl_reg(stw481x, STW_PC_VAUX_SEL);
	अगर (ret < 0)
		वापस ret;
	vaux = (ret >> 2) & 3;
	vpll = (ret >> 4) & 1; /* Save bit 4 */

	ret = stw481x_get_pctl_reg(stw481x, STW_PC_VPLL_SEL);
	अगर (ret < 0)
		वापस ret;
	vpll |= (ret >> 1) & 2;

	dev_info(&stw481x->client->dev, "VCORE: %u.%uV %s\n",
		vcore_val[vcore] / 100, vcore_val[vcore] % 100,
		(ret & 4) ? "ON" : "OFF");

	dev_info(&stw481x->client->dev, "VPLL:  %u.%uV %s\n",
		vpll_val[vpll] / 100, vpll_val[vpll] % 100,
		(ret & 0x10) ? "ON" : "OFF");

	dev_info(&stw481x->client->dev, "VAUX:  %u.%uV %s\n",
		vaux_val[vaux] / 10, vaux_val[vaux] % 10,
		vaux_en ? "ON" : "OFF");

	ret = regmap_पढ़ो(stw481x->map, STW_CONF2, &val);
	अगर (ret)
		वापस ret;

	dev_info(&stw481x->client->dev, "TWARN: %s threshold, %s\n",
		it_warn ? "below" : "above",
		(val & STW_CONF2_MASK_TWARN) ?
		 "enabled" : "mask through VDDOK");
	dev_info(&stw481x->client->dev, "VMMC: %s\n",
		(val & STW_CONF2_VMMC_EXT) ? "internal" : "external");
	dev_info(&stw481x->client->dev, "IT WAKE UP: %s\n",
		(val & STW_CONF2_MASK_IT_WAKE_UP) ? "enabled" : "masked");
	dev_info(&stw481x->client->dev, "GPO1: %s\n",
		(val & STW_CONF2_GPO1) ? "low" : "high impedance");
	dev_info(&stw481x->client->dev, "GPO2: %s\n",
		(val & STW_CONF2_GPO2) ? "low" : "high impedance");

	ret = regmap_पढ़ो(stw481x->map, STW_VCORE_SLEEP, &val);
	अगर (ret)
		वापस ret;
	vcore_slp = val & 0x0f;
	dev_info(&stw481x->client->dev, "VCORE SLEEP: %u.%uV\n",
		vcore_val[vcore_slp] / 100, vcore_val[vcore_slp] % 100);

	वापस 0;
पूर्ण

/*
 * MFD cells - we have one cell which is selected operation
 * mode, and we always have a GPIO cell.
 */
अटल काष्ठा mfd_cell stw481x_cells[] = अणु
	अणु
		.of_compatible = "st,stw481x-vmmc",
		.name = "stw481x-vmmc-regulator",
		.id = -1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config stw481x_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक stw481x_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा stw481x			*stw481x;
	पूर्णांक ret;
	पूर्णांक i;

	stw481x = devm_kzalloc(&client->dev, माप(*stw481x), GFP_KERNEL);
	अगर (!stw481x)
		वापस -ENOMEM;

	i2c_set_clientdata(client, stw481x);
	stw481x->client = client;
	stw481x->map = devm_regmap_init_i2c(client, &stw481x_regmap_config);
	अगर (IS_ERR(stw481x->map)) अणु
		ret = PTR_ERR(stw481x->map);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = stw481x_startup(stw481x);
	अगर (ret) अणु
		dev_err(&client->dev, "chip initialization failed\n");
		वापस ret;
	पूर्ण

	/* Set up and रेजिस्टर the platक्रमm devices. */
	क्रम (i = 0; i < ARRAY_SIZE(stw481x_cells); i++) अणु
		/* One state holder क्रम all drivers, this is simple */
		stw481x_cells[i].platक्रमm_data = stw481x;
		stw481x_cells[i].pdata_size = माप(*stw481x);
	पूर्ण

	ret = devm_mfd_add_devices(&client->dev, 0, stw481x_cells,
				   ARRAY_SIZE(stw481x_cells), शून्य, 0, शून्य);
	अगर (ret)
		वापस ret;

	dev_info(&client->dev, "initialized STw481x device\n");

	वापस ret;
पूर्ण

/*
 * This ID table is completely unused, as this is a pure
 * device-tree probed driver, but it has to be here due to
 * the काष्ठाure of the I2C core.
 */
अटल स्थिर काष्ठा i2c_device_id stw481x_id[] = अणु
	अणु "stw481x", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, stw481x_id);

अटल स्थिर काष्ठा of_device_id stw481x_match[] = अणु
	अणु .compatible = "st,stw4810", पूर्ण,
	अणु .compatible = "st,stw4811", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, stw481x_match);

अटल काष्ठा i2c_driver stw481x_driver = अणु
	.driver = अणु
		.name	= "stw481x",
		.of_match_table = stw481x_match,
	पूर्ण,
	.probe		= stw481x_probe,
	.id_table	= stw481x_id,
पूर्ण;

module_i2c_driver(stw481x_driver);

MODULE_AUTHOR("Linus Walleij");
MODULE_DESCRIPTION("STw481x PMIC driver");
MODULE_LICENSE("GPL v2");
