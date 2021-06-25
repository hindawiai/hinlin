<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Microchip KSZ8795 series रेजिस्टर access through SPI
 *
 * Copyright (C) 2017 Microchip Technology Inc.
 *	Tristram Ha <Tristram.Ha@microchip.com>
 */

#समावेश <यंत्र/unaligned.h>

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>

#समावेश "ksz8.h"
#समावेश "ksz_common.h"

#घोषणा KSZ8795_SPI_ADDR_SHIFT			12
#घोषणा KSZ8795_SPI_ADDR_ALIGN			3
#घोषणा KSZ8795_SPI_TURNAROUND_SHIFT		1

#घोषणा KSZ8863_SPI_ADDR_SHIFT			8
#घोषणा KSZ8863_SPI_ADDR_ALIGN			8
#घोषणा KSZ8863_SPI_TURNAROUND_SHIFT		0

KSZ_REGMAP_TABLE(ksz8795, 16, KSZ8795_SPI_ADDR_SHIFT,
		 KSZ8795_SPI_TURNAROUND_SHIFT, KSZ8795_SPI_ADDR_ALIGN);

KSZ_REGMAP_TABLE(ksz8863, 16, KSZ8863_SPI_ADDR_SHIFT,
		 KSZ8863_SPI_TURNAROUND_SHIFT, KSZ8863_SPI_ADDR_ALIGN);

अटल पूर्णांक ksz8795_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा regmap_config *regmap_config;
	काष्ठा device *ddev = &spi->dev;
	काष्ठा regmap_config rc;
	काष्ठा ksz_device *dev;
	काष्ठा ksz8 *ksz8;
	पूर्णांक i, ret = 0;

	ksz8 = devm_kzalloc(&spi->dev, माप(काष्ठा ksz8), GFP_KERNEL);
	अगर (!ksz8)
		वापस -ENOMEM;

	ksz8->priv = spi;

	dev = ksz_चयन_alloc(&spi->dev, ksz8);
	अगर (!dev)
		वापस -ENOMEM;

	regmap_config = device_get_match_data(ddev);
	अगर (!regmap_config)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(ksz8795_regmap_config); i++) अणु
		rc = regmap_config[i];
		rc.lock_arg = &dev->regmap_mutex;
		dev->regmap[i] = devm_regmap_init_spi(spi, &rc);
		अगर (IS_ERR(dev->regmap[i])) अणु
			ret = PTR_ERR(dev->regmap[i]);
			dev_err(&spi->dev,
				"Failed to initialize regmap%i: %d\n",
				regmap_config[i].val_bits, ret);
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

	ret = ksz8_चयन_रेजिस्टर(dev);

	/* Main DSA driver may not be started yet. */
	अगर (ret)
		वापस ret;

	spi_set_drvdata(spi, dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ksz8795_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा ksz_device *dev = spi_get_drvdata(spi);

	अगर (dev)
		ksz_चयन_हटाओ(dev);

	वापस 0;
पूर्ण

अटल व्योम ksz8795_spi_shutकरोwn(काष्ठा spi_device *spi)
अणु
	काष्ठा ksz_device *dev = spi_get_drvdata(spi);

	अगर (dev && dev->dev_ops->shutकरोwn)
		dev->dev_ops->shutकरोwn(dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id ksz8795_dt_ids[] = अणु
	अणु .compatible = "microchip,ksz8765", .data = &ksz8795_regmap_config पूर्ण,
	अणु .compatible = "microchip,ksz8794", .data = &ksz8795_regmap_config पूर्ण,
	अणु .compatible = "microchip,ksz8795", .data = &ksz8795_regmap_config पूर्ण,
	अणु .compatible = "microchip,ksz8863", .data = &ksz8863_regmap_config पूर्ण,
	अणु .compatible = "microchip,ksz8873", .data = &ksz8863_regmap_config पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ksz8795_dt_ids);

अटल काष्ठा spi_driver ksz8795_spi_driver = अणु
	.driver = अणु
		.name	= "ksz8795-switch",
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(ksz8795_dt_ids),
	पूर्ण,
	.probe	= ksz8795_spi_probe,
	.हटाओ	= ksz8795_spi_हटाओ,
	.shutकरोwn = ksz8795_spi_shutकरोwn,
पूर्ण;

module_spi_driver(ksz8795_spi_driver);

MODULE_AUTHOR("Tristram Ha <Tristram.Ha@microchip.com>");
MODULE_DESCRIPTION("Microchip KSZ8795 Series Switch SPI Driver");
MODULE_LICENSE("GPL");
