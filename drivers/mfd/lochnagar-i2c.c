<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Lochnagar I2C bus पूर्णांकerface
 *
 * Copyright (c) 2012-2018 Cirrus Logic, Inc. and
 *                         Cirrus Logic International Semiconductor Ltd.
 *
 * Author: Charles Keepax <ckeepax@खोलोsource.cirrus.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>

#समावेश <linux/mfd/lochnagar.h>
#समावेश <linux/mfd/lochnagar1_regs.h>
#समावेश <linux/mfd/lochnagar2_regs.h>

#घोषणा LOCHNAGAR_BOOT_RETRIES		10
#घोषणा LOCHNAGAR_BOOT_DELAY_MS		350

#घोषणा LOCHNAGAR_CONFIG_POLL_US	10000

अटल bool lochnagar1_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल LOCHNAGAR_SOFTWARE_RESET:
	हाल LOCHNAGAR_FIRMWARE_ID1...LOCHNAGAR_FIRMWARE_ID2:
	हाल LOCHNAGAR1_CDC_AIF1_SEL...LOCHNAGAR1_CDC_AIF3_SEL:
	हाल LOCHNAGAR1_CDC_MCLK1_SEL...LOCHNAGAR1_CDC_MCLK2_SEL:
	हाल LOCHNAGAR1_CDC_AIF_CTRL1...LOCHNAGAR1_CDC_AIF_CTRL2:
	हाल LOCHNAGAR1_EXT_AIF_CTRL:
	हाल LOCHNAGAR1_DSP_AIF1_SEL...LOCHNAGAR1_DSP_AIF2_SEL:
	हाल LOCHNAGAR1_DSP_CLKIN_SEL:
	हाल LOCHNAGAR1_DSP_AIF:
	हाल LOCHNAGAR1_GF_AIF1...LOCHNAGAR1_GF_AIF2:
	हाल LOCHNAGAR1_PSIA_AIF:
	हाल LOCHNAGAR1_PSIA1_SEL...LOCHNAGAR1_PSIA2_SEL:
	हाल LOCHNAGAR1_SPDIF_AIF_SEL:
	हाल LOCHNAGAR1_GF_AIF3_SEL...LOCHNAGAR1_GF_AIF4_SEL:
	हाल LOCHNAGAR1_GF_CLKOUT1_SEL:
	हाल LOCHNAGAR1_GF_AIF1_SEL...LOCHNAGAR1_GF_AIF2_SEL:
	हाल LOCHNAGAR1_GF_GPIO2...LOCHNAGAR1_GF_GPIO7:
	हाल LOCHNAGAR1_RST:
	हाल LOCHNAGAR1_LED1...LOCHNAGAR1_LED2:
	हाल LOCHNAGAR1_I2C_CTRL:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config lochnagar1_i2c_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.reg_क्रमmat_endian = REGMAP_ENDIAN_BIG,
	.val_क्रमmat_endian = REGMAP_ENDIAN_BIG,

	.max_रेजिस्टर = 0x50,
	.पढ़ोable_reg = lochnagar1_पढ़ोable_रेजिस्टर,

	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,

	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence lochnagar1_patch[] = अणु
	अणु 0x40, 0x0083 पूर्ण,
	अणु 0x47, 0x0018 पूर्ण,
	अणु 0x50, 0x0000 पूर्ण,
पूर्ण;

अटल bool lochnagar2_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल LOCHNAGAR_SOFTWARE_RESET:
	हाल LOCHNAGAR_FIRMWARE_ID1...LOCHNAGAR_FIRMWARE_ID2:
	हाल LOCHNAGAR2_CDC_AIF1_CTRL...LOCHNAGAR2_CDC_AIF3_CTRL:
	हाल LOCHNAGAR2_DSP_AIF1_CTRL...LOCHNAGAR2_DSP_AIF2_CTRL:
	हाल LOCHNAGAR2_PSIA1_CTRL...LOCHNAGAR2_PSIA2_CTRL:
	हाल LOCHNAGAR2_GF_AIF3_CTRL...LOCHNAGAR2_GF_AIF4_CTRL:
	हाल LOCHNAGAR2_GF_AIF1_CTRL...LOCHNAGAR2_GF_AIF2_CTRL:
	हाल LOCHNAGAR2_SPDIF_AIF_CTRL:
	हाल LOCHNAGAR2_USB_AIF1_CTRL...LOCHNAGAR2_USB_AIF2_CTRL:
	हाल LOCHNAGAR2_ADAT_AIF_CTRL:
	हाल LOCHNAGAR2_CDC_MCLK1_CTRL...LOCHNAGAR2_CDC_MCLK2_CTRL:
	हाल LOCHNAGAR2_DSP_CLKIN_CTRL:
	हाल LOCHNAGAR2_PSIA1_MCLK_CTRL...LOCHNAGAR2_PSIA2_MCLK_CTRL:
	हाल LOCHNAGAR2_SPDIF_MCLK_CTRL:
	हाल LOCHNAGAR2_GF_CLKOUT1_CTRL...LOCHNAGAR2_GF_CLKOUT2_CTRL:
	हाल LOCHNAGAR2_ADAT_MCLK_CTRL:
	हाल LOCHNAGAR2_SOUNDCARD_MCLK_CTRL:
	हाल LOCHNAGAR2_GPIO_FPGA_GPIO1...LOCHNAGAR2_GPIO_FPGA_GPIO6:
	हाल LOCHNAGAR2_GPIO_CDC_GPIO1...LOCHNAGAR2_GPIO_CDC_GPIO8:
	हाल LOCHNAGAR2_GPIO_DSP_GPIO1...LOCHNAGAR2_GPIO_DSP_GPIO6:
	हाल LOCHNAGAR2_GPIO_GF_GPIO2...LOCHNAGAR2_GPIO_GF_GPIO7:
	हाल LOCHNAGAR2_GPIO_CDC_AIF1_BCLK...LOCHNAGAR2_GPIO_CDC_AIF3_TXDAT:
	हाल LOCHNAGAR2_GPIO_DSP_AIF1_BCLK...LOCHNAGAR2_GPIO_DSP_AIF2_TXDAT:
	हाल LOCHNAGAR2_GPIO_PSIA1_BCLK...LOCHNAGAR2_GPIO_PSIA2_TXDAT:
	हाल LOCHNAGAR2_GPIO_GF_AIF3_BCLK...LOCHNAGAR2_GPIO_GF_AIF4_TXDAT:
	हाल LOCHNAGAR2_GPIO_GF_AIF1_BCLK...LOCHNAGAR2_GPIO_GF_AIF2_TXDAT:
	हाल LOCHNAGAR2_GPIO_DSP_UART1_RX...LOCHNAGAR2_GPIO_DSP_UART2_TX:
	हाल LOCHNAGAR2_GPIO_GF_UART2_RX...LOCHNAGAR2_GPIO_GF_UART2_TX:
	हाल LOCHNAGAR2_GPIO_USB_UART_RX:
	हाल LOCHNAGAR2_GPIO_CDC_PDMCLK1...LOCHNAGAR2_GPIO_CDC_PDMDAT2:
	हाल LOCHNAGAR2_GPIO_CDC_DMICCLK1...LOCHNAGAR2_GPIO_CDC_DMICDAT4:
	हाल LOCHNAGAR2_GPIO_DSP_DMICCLK1...LOCHNAGAR2_GPIO_DSP_DMICDAT2:
	हाल LOCHNAGAR2_GPIO_I2C2_SCL...LOCHNAGAR2_GPIO_I2C4_SDA:
	हाल LOCHNAGAR2_GPIO_DSP_STANDBY:
	हाल LOCHNAGAR2_GPIO_CDC_MCLK1...LOCHNAGAR2_GPIO_CDC_MCLK2:
	हाल LOCHNAGAR2_GPIO_DSP_CLKIN:
	हाल LOCHNAGAR2_GPIO_PSIA1_MCLK...LOCHNAGAR2_GPIO_PSIA2_MCLK:
	हाल LOCHNAGAR2_GPIO_GF_GPIO1...LOCHNAGAR2_GPIO_GF_GPIO5:
	हाल LOCHNAGAR2_GPIO_DSP_GPIO20:
	हाल LOCHNAGAR2_GPIO_CHANNEL1...LOCHNAGAR2_GPIO_CHANNEL16:
	हाल LOCHNAGAR2_MINICARD_RESETS:
	हाल LOCHNAGAR2_ANALOGUE_PATH_CTRL1...LOCHNAGAR2_ANALOGUE_PATH_CTRL2:
	हाल LOCHNAGAR2_COMMS_CTRL4:
	हाल LOCHNAGAR2_SPDIF_CTRL:
	हाल LOCHNAGAR2_IMON_CTRL1...LOCHNAGAR2_IMON_CTRL4:
	हाल LOCHNAGAR2_IMON_DATA1...LOCHNAGAR2_IMON_DATA2:
	हाल LOCHNAGAR2_POWER_CTRL:
	हाल LOCHNAGAR2_MICVDD_CTRL1:
	हाल LOCHNAGAR2_MICVDD_CTRL2:
	हाल LOCHNAGAR2_VDDCORE_CDC_CTRL1:
	हाल LOCHNAGAR2_VDDCORE_CDC_CTRL2:
	हाल LOCHNAGAR2_SOUNDCARD_AIF_CTRL:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool lochnagar2_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल LOCHNAGAR2_GPIO_CHANNEL1...LOCHNAGAR2_GPIO_CHANNEL16:
	हाल LOCHNAGAR2_ANALOGUE_PATH_CTRL1:
	हाल LOCHNAGAR2_IMON_CTRL3...LOCHNAGAR2_IMON_CTRL4:
	हाल LOCHNAGAR2_IMON_DATA1...LOCHNAGAR2_IMON_DATA2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config lochnagar2_i2c_regmap = अणु
	.reg_bits = 16,
	.val_bits = 16,
	.reg_क्रमmat_endian = REGMAP_ENDIAN_BIG,
	.val_क्रमmat_endian = REGMAP_ENDIAN_BIG,

	.max_रेजिस्टर = 0x1F1F,
	.पढ़ोable_reg = lochnagar2_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = lochnagar2_अस्थिर_रेजिस्टर,

	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा reg_sequence lochnagar2_patch[] = अणु
	अणु 0x00EE, 0x0000 पूर्ण,
पूर्ण;

काष्ठा lochnagar_config अणु
	पूर्णांक id;
	स्थिर अक्षर * स्थिर name;
	क्रमागत lochnagar_type type;
	स्थिर काष्ठा regmap_config *regmap;
	स्थिर काष्ठा reg_sequence *patch;
	पूर्णांक npatch;
पूर्ण;

अटल काष्ठा lochnagar_config lochnagar_configs[] = अणु
	अणु
		.id = 0x50,
		.name = "lochnagar1",
		.type = LOCHNAGAR1,
		.regmap = &lochnagar1_i2c_regmap,
		.patch = lochnagar1_patch,
		.npatch = ARRAY_SIZE(lochnagar1_patch),
	पूर्ण,
	अणु
		.id = 0xCB58,
		.name = "lochnagar2",
		.type = LOCHNAGAR2,
		.regmap = &lochnagar2_i2c_regmap,
		.patch = lochnagar2_patch,
		.npatch = ARRAY_SIZE(lochnagar2_patch),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id lochnagar_of_match[] = अणु
	अणु .compatible = "cirrus,lochnagar1", .data = &lochnagar_configs[0] पूर्ण,
	अणु .compatible = "cirrus,lochnagar2", .data = &lochnagar_configs[1] पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल पूर्णांक lochnagar_रुको_क्रम_boot(काष्ठा regmap *regmap, अचिन्हित पूर्णांक *id)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < LOCHNAGAR_BOOT_RETRIES; ++i) अणु
		msleep(LOCHNAGAR_BOOT_DELAY_MS);

		/* The reset रेजिस्टर will वापस the device ID when पढ़ो */
		ret = regmap_पढ़ो(regmap, LOCHNAGAR_SOFTWARE_RESET, id);
		अगर (!ret)
			वापस ret;
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

/**
 * lochnagar_update_config - Synchronise the boards analogue configuration to
 *                           the hardware.
 *
 * @lochnagar: A poपूर्णांकer to the primary core data काष्ठाure.
 *
 * Return: Zero on success or an appropriate negative error code on failure.
 */
पूर्णांक lochnagar_update_config(काष्ठा lochnagar *lochnagar)
अणु
	काष्ठा regmap *regmap = lochnagar->regmap;
	अचिन्हित पूर्णांक करोne = LOCHNAGAR2_ANALOGUE_PATH_UPDATE_STS_MASK;
	पूर्णांक समयout_ms = LOCHNAGAR_BOOT_DELAY_MS * LOCHNAGAR_BOOT_RETRIES;
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक ret;

	lockdep_निश्चित_held(&lochnagar->analogue_config_lock);

	अगर (lochnagar->type != LOCHNAGAR2)
		वापस 0;

	/*
	 * Toggle the ANALOGUE_PATH_UPDATE bit and रुको क्रम the device to
	 * acknowledge that any outstanding changes to the analogue
	 * configuration have been applied.
	 */
	ret = regmap_ग_लिखो(regmap, LOCHNAGAR2_ANALOGUE_PATH_CTRL1, 0);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_ग_लिखो(regmap, LOCHNAGAR2_ANALOGUE_PATH_CTRL1,
			   LOCHNAGAR2_ANALOGUE_PATH_UPDATE_MASK);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो_poll_समयout(regmap,
				       LOCHNAGAR2_ANALOGUE_PATH_CTRL1, val,
				       (val & करोne), LOCHNAGAR_CONFIG_POLL_US,
				       समयout_ms * 1000);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(lochnagar_update_config);

अटल पूर्णांक lochnagar_i2c_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा device *dev = &i2c->dev;
	स्थिर काष्ठा lochnagar_config *config = शून्य;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा lochnagar *lochnagar;
	काष्ठा gpio_desc *reset, *present;
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक firmwareid;
	अचिन्हित पूर्णांक devid, rev;
	पूर्णांक ret;

	lochnagar = devm_kzalloc(dev, माप(*lochnagar), GFP_KERNEL);
	अगर (!lochnagar)
		वापस -ENOMEM;

	of_id = of_match_device(lochnagar_of_match, dev);
	अगर (!of_id)
		वापस -EINVAL;

	config = of_id->data;

	lochnagar->dev = dev;
	mutex_init(&lochnagar->analogue_config_lock);

	dev_set_drvdata(dev, lochnagar);

	reset = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(reset)) अणु
		ret = PTR_ERR(reset);
		dev_err(dev, "Failed to get reset GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	present = devm_gpiod_get_optional(dev, "present", GPIOD_OUT_HIGH);
	अगर (IS_ERR(present)) अणु
		ret = PTR_ERR(present);
		dev_err(dev, "Failed to get present GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Leave the Lochnagar in reset क्रम a reasonable amount of समय */
	msleep(20);

	/* Bring Lochnagar out of reset */
	gpiod_set_value_cansleep(reset, 1);

	/* Identअगरy Lochnagar */
	lochnagar->type = config->type;

	lochnagar->regmap = devm_regmap_init_i2c(i2c, config->regmap);
	अगर (IS_ERR(lochnagar->regmap)) अणु
		ret = PTR_ERR(lochnagar->regmap);
		dev_err(dev, "Failed to allocate register map: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Wait क्रम Lochnagar to boot */
	ret = lochnagar_रुको_क्रम_boot(lochnagar->regmap, &val);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read device ID: %d\n", ret);
		वापस ret;
	पूर्ण

	devid = val & LOCHNAGAR_DEVICE_ID_MASK;
	rev = val & LOCHNAGAR_REV_ID_MASK;

	अगर (devid != config->id) अणु
		dev_err(dev,
			"ID does not match %s (expected 0x%x got 0x%x)\n",
			config->name, config->id, devid);
		वापस -ENODEV;
	पूर्ण

	/* Identअगरy firmware */
	ret = regmap_पढ़ो(lochnagar->regmap, LOCHNAGAR_FIRMWARE_ID1, &val);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read firmware id 1: %d\n", ret);
		वापस ret;
	पूर्ण

	firmwareid = val;

	ret = regmap_पढ़ो(lochnagar->regmap, LOCHNAGAR_FIRMWARE_ID2, &val);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read firmware id 2: %d\n", ret);
		वापस ret;
	पूर्ण

	firmwareid |= (val << config->regmap->val_bits);

	dev_info(dev, "Found %s (0x%x) revision %u firmware 0x%.6x\n",
		 config->name, devid, rev + 1, firmwareid);

	ret = regmap_रेजिस्टर_patch(lochnagar->regmap, config->patch,
				    config->npatch);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to register patch: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_of_platक्रमm_populate(dev);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to populate child nodes: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा i2c_driver lochnagar_i2c_driver = अणु
	.driver = अणु
		.name = "lochnagar",
		.of_match_table = of_match_ptr(lochnagar_of_match),
		.suppress_bind_attrs = true,
	पूर्ण,
	.probe_new = lochnagar_i2c_probe,
पूर्ण;

अटल पूर्णांक __init lochnagar_i2c_init(व्योम)
अणु
	पूर्णांक ret;

	ret = i2c_add_driver(&lochnagar_i2c_driver);
	अगर (ret)
		pr_err("Failed to register Lochnagar driver: %d\n", ret);

	वापस ret;
पूर्ण
subsys_initcall(lochnagar_i2c_init);
