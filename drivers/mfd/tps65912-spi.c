<शैली गुरु>
/*
 * SPI access driver क्रम TI TPS65912x PMICs
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - https://www.ti.com/
 *	Andrew F. Davis <afd@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether expressed or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 क्रम more details.
 *
 * Based on the TPS65218 driver and the previous TPS65912 driver by
 * Margarita Olaya Cabrera <magi@slimlogic.co.uk>
 */

#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>

#समावेश <linux/mfd/tps65912.h>

अटल स्थिर काष्ठा of_device_id tps65912_spi_of_match_table[] = अणु
	अणु .compatible = "ti,tps65912", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tps65912_spi_of_match_table);

अटल पूर्णांक tps65912_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा tps65912 *tps;

	tps = devm_kzalloc(&spi->dev, माप(*tps), GFP_KERNEL);
	अगर (!tps)
		वापस -ENOMEM;

	spi_set_drvdata(spi, tps);
	tps->dev = &spi->dev;
	tps->irq = spi->irq;

	tps->regmap = devm_regmap_init_spi(spi, &tps65912_regmap_config);
	अगर (IS_ERR(tps->regmap)) अणु
		dev_err(tps->dev, "Failed to initialize register map\n");
		वापस PTR_ERR(tps->regmap);
	पूर्ण

	वापस tps65912_device_init(tps);
पूर्ण

अटल पूर्णांक tps65912_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा tps65912 *tps = spi_get_drvdata(spi);

	वापस tps65912_device_निकास(tps);
पूर्ण

अटल स्थिर काष्ठा spi_device_id tps65912_spi_id_table[] = अणु
	अणु "tps65912", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, tps65912_spi_id_table);

अटल काष्ठा spi_driver tps65912_spi_driver = अणु
	.driver		= अणु
		.name	= "tps65912",
		.of_match_table = tps65912_spi_of_match_table,
	पूर्ण,
	.probe		= tps65912_spi_probe,
	.हटाओ		= tps65912_spi_हटाओ,
	.id_table       = tps65912_spi_id_table,
पूर्ण;
module_spi_driver(tps65912_spi_driver);

MODULE_AUTHOR("Andrew F. Davis <afd@ti.com>");
MODULE_DESCRIPTION("TPS65912x SPI Interface Driver");
MODULE_LICENSE("GPL v2");
