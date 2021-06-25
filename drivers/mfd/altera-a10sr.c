<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Altera Arria10 DevKit System Resource MFD Driver
 *
 * Author: Thor Thayer <tthayer@खोलोsource.altera.com>
 *
 * Copyright Intel Corporation (C) 2014-2016. All Rights Reserved
 *
 * SPI access क्रम Altera Arria10 MAX5 System Resource Chip
 *
 * Adapted from DA9052
 */

#समावेश <linux/mfd/altera-a10sr.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/spi/spi.h>

अटल स्थिर काष्ठा mfd_cell altr_a10sr_subdev_info[] = अणु
	अणु
		.name = "altr_a10sr_gpio",
		.of_compatible = "altr,a10sr-gpio",
	पूर्ण,
	अणु
		.name = "altr_a10sr_reset",
		.of_compatible = "altr,a10sr-reset",
	पूर्ण,
पूर्ण;

अटल bool altr_a10sr_reg_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ALTR_A10SR_VERSION_READ:
	हाल ALTR_A10SR_LED_REG:
	हाल ALTR_A10SR_PBDSW_REG:
	हाल ALTR_A10SR_PBDSW_IRQ_REG:
	हाल ALTR_A10SR_PWR_GOOD1_REG:
	हाल ALTR_A10SR_PWR_GOOD2_REG:
	हाल ALTR_A10SR_PWR_GOOD3_REG:
	हाल ALTR_A10SR_FMCAB_REG:
	हाल ALTR_A10SR_HPS_RST_REG:
	हाल ALTR_A10SR_USB_QSPI_REG:
	हाल ALTR_A10SR_SFPA_REG:
	हाल ALTR_A10SR_SFPB_REG:
	हाल ALTR_A10SR_I2C_M_REG:
	हाल ALTR_A10SR_WARM_RST_REG:
	हाल ALTR_A10SR_WR_KEY_REG:
	हाल ALTR_A10SR_PMBUS_REG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool altr_a10sr_reg_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ALTR_A10SR_LED_REG:
	हाल ALTR_A10SR_PBDSW_IRQ_REG:
	हाल ALTR_A10SR_FMCAB_REG:
	हाल ALTR_A10SR_HPS_RST_REG:
	हाल ALTR_A10SR_USB_QSPI_REG:
	हाल ALTR_A10SR_SFPA_REG:
	हाल ALTR_A10SR_SFPB_REG:
	हाल ALTR_A10SR_WARM_RST_REG:
	हाल ALTR_A10SR_WR_KEY_REG:
	हाल ALTR_A10SR_PMBUS_REG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool altr_a10sr_reg_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ALTR_A10SR_PBDSW_REG:
	हाल ALTR_A10SR_PBDSW_IRQ_REG:
	हाल ALTR_A10SR_PWR_GOOD1_REG:
	हाल ALTR_A10SR_PWR_GOOD2_REG:
	हाल ALTR_A10SR_PWR_GOOD3_REG:
	हाल ALTR_A10SR_HPS_RST_REG:
	हाल ALTR_A10SR_I2C_M_REG:
	हाल ALTR_A10SR_WARM_RST_REG:
	हाल ALTR_A10SR_WR_KEY_REG:
	हाल ALTR_A10SR_PMBUS_REG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config altr_a10sr_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.cache_type = REGCACHE_NONE,

	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
	.पढ़ो_flag_mask = 1,
	.ग_लिखो_flag_mask = 0,

	.max_रेजिस्टर = ALTR_A10SR_WR_KEY_REG,
	.पढ़ोable_reg = altr_a10sr_reg_पढ़ोable,
	.ग_लिखोable_reg = altr_a10sr_reg_ग_लिखोable,
	.अस्थिर_reg = altr_a10sr_reg_अस्थिर,

पूर्ण;

अटल पूर्णांक altr_a10sr_spi_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;
	काष्ठा altr_a10sr *a10sr;

	a10sr = devm_kzalloc(&spi->dev, माप(*a10sr),
			     GFP_KERNEL);
	अगर (!a10sr)
		वापस -ENOMEM;

	spi->mode = SPI_MODE_3;
	spi->bits_per_word = 8;
	spi_setup(spi);

	a10sr->dev = &spi->dev;

	spi_set_drvdata(spi, a10sr);

	a10sr->regmap = devm_regmap_init_spi(spi, &altr_a10sr_regmap_config);
	अगर (IS_ERR(a10sr->regmap)) अणु
		ret = PTR_ERR(a10sr->regmap);
		dev_err(&spi->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = devm_mfd_add_devices(a10sr->dev, PLATFORM_DEVID_AUTO,
				   altr_a10sr_subdev_info,
				   ARRAY_SIZE(altr_a10sr_subdev_info),
				   शून्य, 0, शून्य);
	अगर (ret)
		dev_err(a10sr->dev, "Failed to register sub-devices: %d\n",
			ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id altr_a10sr_spi_of_match[] = अणु
	अणु .compatible = "altr,a10sr" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा spi_driver altr_a10sr_spi_driver = अणु
	.probe = altr_a10sr_spi_probe,
	.driver = अणु
		.name = "altr_a10sr",
		.of_match_table = of_match_ptr(altr_a10sr_spi_of_match),
	पूर्ण,
पूर्ण;
builtin_driver(altr_a10sr_spi_driver, spi_रेजिस्टर_driver)
