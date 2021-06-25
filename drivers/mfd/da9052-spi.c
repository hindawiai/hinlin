<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SPI access क्रम Dialog DA9052 PMICs.
 *
 * Copyright(c) 2011 Dialog Semiconductor Ltd.
 *
 * Author: David Dajun Chen <dchen@diasemi.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/err.h>

#समावेश <linux/mfd/da9052/da9052.h>

अटल पूर्णांक da9052_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा regmap_config config;
	पूर्णांक ret;
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	काष्ठा da9052 *da9052;

	da9052 = devm_kzalloc(&spi->dev, माप(काष्ठा da9052), GFP_KERNEL);
	अगर (!da9052)
		वापस -ENOMEM;

	spi->mode = SPI_MODE_0;
	spi->bits_per_word = 8;
	spi_setup(spi);

	da9052->dev = &spi->dev;
	da9052->chip_irq = spi->irq;

	spi_set_drvdata(spi, da9052);

	config = da9052_regmap_config;
	config.पढ़ो_flag_mask = 1;
	config.reg_bits = 7;
	config.pad_bits = 1;
	config.val_bits = 8;
	config.use_single_पढ़ो = true;
	config.use_single_ग_लिखो = true;

	da9052->regmap = devm_regmap_init_spi(spi, &config);
	अगर (IS_ERR(da9052->regmap)) अणु
		ret = PTR_ERR(da9052->regmap);
		dev_err(&spi->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण

	वापस da9052_device_init(da9052, id->driver_data);
पूर्ण

अटल पूर्णांक da9052_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा da9052 *da9052 = spi_get_drvdata(spi);

	da9052_device_निकास(da9052);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id da9052_spi_id[] = अणु
	अणु"da9052", DA9052पूर्ण,
	अणु"da9053-aa", DA9053_AAपूर्ण,
	अणु"da9053-ba", DA9053_BAपूर्ण,
	अणु"da9053-bb", DA9053_BBपूर्ण,
	अणु"da9053-bc", DA9053_BCपूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा spi_driver da9052_spi_driver = अणु
	.probe = da9052_spi_probe,
	.हटाओ = da9052_spi_हटाओ,
	.id_table = da9052_spi_id,
	.driver = अणु
		.name = "da9052",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init da9052_spi_init(व्योम)
अणु
	पूर्णांक ret;

	ret = spi_रेजिस्टर_driver(&da9052_spi_driver);
	अगर (ret != 0) अणु
		pr_err("Failed to register DA9052 SPI driver, %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
subsys_initcall(da9052_spi_init);

अटल व्योम __निकास da9052_spi_निकास(व्योम)
अणु
	spi_unरेजिस्टर_driver(&da9052_spi_driver);
पूर्ण
module_निकास(da9052_spi_निकास);

MODULE_AUTHOR("David Dajun Chen <dchen@diasemi.com>");
MODULE_DESCRIPTION("SPI driver for Dialog DA9052 PMIC");
MODULE_LICENSE("GPL");
