<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Microchip KSZ9477 series रेजिस्टर access through SPI
 *
 * Copyright (C) 2017-2019 Microchip Technology Inc.
 */

#समावेश <यंत्र/unaligned.h>

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>

#समावेश "ksz_common.h"

#घोषणा SPI_ADDR_SHIFT			24
#घोषणा SPI_ADDR_ALIGN			3
#घोषणा SPI_TURNAROUND_SHIFT		5

KSZ_REGMAP_TABLE(ksz9477, 32, SPI_ADDR_SHIFT,
		 SPI_TURNAROUND_SHIFT, SPI_ADDR_ALIGN);

अटल पूर्णांक ksz9477_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा regmap_config rc;
	काष्ठा ksz_device *dev;
	पूर्णांक i, ret;

	dev = ksz_चयन_alloc(&spi->dev, spi);
	अगर (!dev)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(ksz9477_regmap_config); i++) अणु
		rc = ksz9477_regmap_config[i];
		rc.lock_arg = &dev->regmap_mutex;
		dev->regmap[i] = devm_regmap_init_spi(spi, &rc);
		अगर (IS_ERR(dev->regmap[i])) अणु
			ret = PTR_ERR(dev->regmap[i]);
			dev_err(&spi->dev,
				"Failed to initialize regmap%i: %d\n",
				ksz9477_regmap_config[i].val_bits, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (spi->dev.platक्रमm_data)
		dev->pdata = spi->dev.platक्रमm_data;

	/* setup spi */
	spi->mode = SPI_MODE_3;
	ret = spi_setup(spi);
	अगर (ret)
		वापस ret;

	ret = ksz9477_चयन_रेजिस्टर(dev);

	/* Main DSA driver may not be started yet. */
	अगर (ret)
		वापस ret;

	spi_set_drvdata(spi, dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ksz9477_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा ksz_device *dev = spi_get_drvdata(spi);

	अगर (dev)
		ksz_चयन_हटाओ(dev);

	वापस 0;
पूर्ण

अटल व्योम ksz9477_spi_shutकरोwn(काष्ठा spi_device *spi)
अणु
	काष्ठा ksz_device *dev = spi_get_drvdata(spi);

	अगर (dev && dev->dev_ops->shutकरोwn)
		dev->dev_ops->shutकरोwn(dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id ksz9477_dt_ids[] = अणु
	अणु .compatible = "microchip,ksz9477" पूर्ण,
	अणु .compatible = "microchip,ksz9897" पूर्ण,
	अणु .compatible = "microchip,ksz9893" पूर्ण,
	अणु .compatible = "microchip,ksz9563" पूर्ण,
	अणु .compatible = "microchip,ksz8563" पूर्ण,
	अणु .compatible = "microchip,ksz9567" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ksz9477_dt_ids);

अटल काष्ठा spi_driver ksz9477_spi_driver = अणु
	.driver = अणु
		.name	= "ksz9477-switch",
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(ksz9477_dt_ids),
	पूर्ण,
	.probe	= ksz9477_spi_probe,
	.हटाओ	= ksz9477_spi_हटाओ,
	.shutकरोwn = ksz9477_spi_shutकरोwn,
पूर्ण;

module_spi_driver(ksz9477_spi_driver);

MODULE_ALIAS("spi:ksz9477");
MODULE_ALIAS("spi:ksz9897");
MODULE_ALIAS("spi:ksz9893");
MODULE_ALIAS("spi:ksz9563");
MODULE_ALIAS("spi:ksz8563");
MODULE_ALIAS("spi:ksz9567");
MODULE_AUTHOR("Woojung Huh <Woojung.Huh@microchip.com>");
MODULE_DESCRIPTION("Microchip KSZ9477 Series Switch SPI access Driver");
MODULE_LICENSE("GPL");
