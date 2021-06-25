<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI LMU (Lighting Management Unit) Core Driver
 *
 * Copyright 2017 Texas Instruments
 *
 * Author: Milo Kim <milo.kim@ti.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/ti-lmu.h>
#समावेश <linux/mfd/ti-lmu-रेजिस्टर.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>

काष्ठा ti_lmu_data अणु
	स्थिर काष्ठा mfd_cell *cells;
	पूर्णांक num_cells;
	अचिन्हित पूर्णांक max_रेजिस्टर;
पूर्ण;

अटल पूर्णांक ti_lmu_enable_hw(काष्ठा ti_lmu *lmu, क्रमागत ti_lmu_id id)
अणु
	अगर (lmu->en_gpio)
		gpiod_set_value(lmu->en_gpio, 1);

	/* Delay about 1ms after HW enable pin control */
	usleep_range(1000, 1500);

	/* LM3631 has additional घातer up sequence - enable LCD_EN bit. */
	अगर (id == LM3631) अणु
		वापस regmap_update_bits(lmu->regmap, LM3631_REG_DEVCTRL,
					  LM3631_LCD_EN_MASK,
					  LM3631_LCD_EN_MASK);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ti_lmu_disable_hw(व्योम *data)
अणु
	काष्ठा ti_lmu *lmu = data;
	अगर (lmu->en_gpio)
		gpiod_set_value(lmu->en_gpio, 0);
पूर्ण

#घोषणा LM363X_REGULATOR(_id)			\
अणु						\
	.name          = "lm363x-regulator",	\
	.id            = _id,			\
	.of_compatible = "ti,lm363x-regulator",	\
पूर्ण						\

अटल स्थिर काष्ठा mfd_cell lm3631_devices[] = अणु
	LM363X_REGULATOR(LM3631_BOOST),
	LM363X_REGULATOR(LM3631_LDO_CONT),
	LM363X_REGULATOR(LM3631_LDO_OREF),
	LM363X_REGULATOR(LM3631_LDO_POS),
	LM363X_REGULATOR(LM3631_LDO_NEG),
	अणु
		.name          = "ti-lmu-backlight",
		.id            = LM3631,
		.of_compatible = "ti,lm3631-backlight",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell lm3632_devices[] = अणु
	LM363X_REGULATOR(LM3632_BOOST),
	LM363X_REGULATOR(LM3632_LDO_POS),
	LM363X_REGULATOR(LM3632_LDO_NEG),
	अणु
		.name          = "ti-lmu-backlight",
		.id            = LM3632,
		.of_compatible = "ti,lm3632-backlight",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell lm3633_devices[] = अणु
	अणु
		.name          = "ti-lmu-backlight",
		.id            = LM3633,
		.of_compatible = "ti,lm3633-backlight",
	पूर्ण,
	अणु
		.name          = "lm3633-leds",
		.of_compatible = "ti,lm3633-leds",
	पूर्ण,
	/* Monitoring driver क्रम खोलो/लघु circuit detection */
	अणु
		.name          = "ti-lmu-fault-monitor",
		.id            = LM3633,
		.of_compatible = "ti,lm3633-fault-monitor",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell lm3695_devices[] = अणु
	अणु
		.name          = "ti-lmu-backlight",
		.id            = LM3695,
		.of_compatible = "ti,lm3695-backlight",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा mfd_cell lm36274_devices[] = अणु
	LM363X_REGULATOR(LM36274_BOOST),
	LM363X_REGULATOR(LM36274_LDO_POS),
	LM363X_REGULATOR(LM36274_LDO_NEG),
	अणु
		.name          = "lm36274-leds",
		.id            = LM36274,
		.of_compatible = "ti,lm36274-backlight",
	पूर्ण,
पूर्ण;

#घोषणा TI_LMU_DATA(chip, max_reg)		\
अटल स्थिर काष्ठा ti_lmu_data chip##_data =	\
अणु						\
	.cells = chip##_devices,		\
	.num_cells = ARRAY_SIZE(chip##_devices),\
	.max_रेजिस्टर = max_reg,		\
पूर्ण						\

TI_LMU_DATA(lm3631, LM3631_MAX_REG);
TI_LMU_DATA(lm3632, LM3632_MAX_REG);
TI_LMU_DATA(lm3633, LM3633_MAX_REG);
TI_LMU_DATA(lm3695, LM3695_MAX_REG);
TI_LMU_DATA(lm36274, LM36274_MAX_REG);

अटल पूर्णांक ti_lmu_probe(काष्ठा i2c_client *cl, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &cl->dev;
	स्थिर काष्ठा ti_lmu_data *data;
	काष्ठा regmap_config regmap_cfg;
	काष्ठा ti_lmu *lmu;
	पूर्णांक ret;

	/*
	 * Get device specअगरic data from of_match table.
	 * This data is defined by using TI_LMU_DATA() macro.
	 */
	data = of_device_get_match_data(dev);
	अगर (!data)
		वापस -ENODEV;

	lmu = devm_kzalloc(dev, माप(*lmu), GFP_KERNEL);
	अगर (!lmu)
		वापस -ENOMEM;

	lmu->dev = &cl->dev;

	/* Setup regmap */
	स_रखो(&regmap_cfg, 0, माप(काष्ठा regmap_config));
	regmap_cfg.reg_bits = 8;
	regmap_cfg.val_bits = 8;
	regmap_cfg.name = id->name;
	regmap_cfg.max_रेजिस्टर = data->max_रेजिस्टर;

	lmu->regmap = devm_regmap_init_i2c(cl, &regmap_cfg);
	अगर (IS_ERR(lmu->regmap))
		वापस PTR_ERR(lmu->regmap);

	/* HW enable pin control and additional घातer up sequence अगर required */
	lmu->en_gpio = devm_gpiod_get_optional(dev, "enable", GPIOD_OUT_HIGH);
	अगर (IS_ERR(lmu->en_gpio)) अणु
		ret = PTR_ERR(lmu->en_gpio);
		dev_err(dev, "Can not request enable GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = ti_lmu_enable_hw(lmu, id->driver_data);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(dev, ti_lmu_disable_hw, lmu);
	अगर (ret)
		वापस ret;

	/*
	 * Fault circuit(खोलो/लघु) can be detected by ti-lmu-fault-monitor.
	 * After fault detection is करोne, some devices should re-initialize
	 * configuration. The notअगरier enables such kind of handling.
	 */
	BLOCKING_INIT_NOTIFIER_HEAD(&lmu->notअगरier);

	i2c_set_clientdata(cl, lmu);

	वापस devm_mfd_add_devices(lmu->dev, 0, data->cells,
				    data->num_cells, शून्य, 0, शून्य);
पूर्ण

अटल स्थिर काष्ठा of_device_id ti_lmu_of_match[] = अणु
	अणु .compatible = "ti,lm3631", .data = &lm3631_data पूर्ण,
	अणु .compatible = "ti,lm3632", .data = &lm3632_data पूर्ण,
	अणु .compatible = "ti,lm3633", .data = &lm3633_data पूर्ण,
	अणु .compatible = "ti,lm3695", .data = &lm3695_data पूर्ण,
	अणु .compatible = "ti,lm36274", .data = &lm36274_data पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_lmu_of_match);

अटल स्थिर काष्ठा i2c_device_id ti_lmu_ids[] = अणु
	अणु "lm3631", LM3631 पूर्ण,
	अणु "lm3632", LM3632 पूर्ण,
	अणु "lm3633", LM3633 पूर्ण,
	अणु "lm3695", LM3695 पूर्ण,
	अणु "lm36274", LM36274 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ti_lmu_ids);

अटल काष्ठा i2c_driver ti_lmu_driver = अणु
	.probe = ti_lmu_probe,
	.driver = अणु
		.name = "ti-lmu",
		.of_match_table = ti_lmu_of_match,
	पूर्ण,
	.id_table = ti_lmu_ids,
पूर्ण;

module_i2c_driver(ti_lmu_driver);

MODULE_DESCRIPTION("TI LMU MFD Core Driver");
MODULE_AUTHOR("Milo Kim");
MODULE_LICENSE("GPL v2");
