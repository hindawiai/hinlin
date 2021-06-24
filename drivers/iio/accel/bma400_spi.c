<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SPI IIO driver क्रम Bosch BMA400 triaxial acceleration sensor.
 *
 * Copyright 2020 Dan Robertson <dan@dlrobertson.com>
 *
 */
#समावेश <linux/bits.h>
#समावेश <linux/init.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>

#समावेश "bma400.h"

#घोषणा BMA400_MAX_SPI_READ 2
#घोषणा BMA400_SPI_READ_BUFFER_SIZE (BMA400_MAX_SPI_READ + 1)

अटल पूर्णांक bma400_regmap_spi_पढ़ो(व्योम *context,
				  स्थिर व्योम *reg, माप_प्रकार reg_size,
				  व्योम *val, माप_प्रकार val_size)
अणु
	काष्ठा device *dev = context;
	काष्ठा spi_device *spi = to_spi_device(dev);
	u8 result[BMA400_SPI_READ_BUFFER_SIZE];
	sमाप_प्रकार status;

	अगर (val_size > BMA400_MAX_SPI_READ)
		वापस -EINVAL;

	status = spi_ग_लिखो_then_पढ़ो(spi, reg, 1, result, val_size + 1);
	अगर (status)
		वापस status;

	/*
	 * From the BMA400 datasheet:
	 *
	 * > For a basic पढ़ो operation two bytes have to be पढ़ो and the first
	 * > has to be dropped and the second byte must be पूर्णांकerpreted.
	 */
	स_नकल(val, result + 1, val_size);

	वापस 0;
पूर्ण

अटल पूर्णांक bma400_regmap_spi_ग_लिखो(व्योम *context, स्थिर व्योम *data,
				   माप_प्रकार count)
अणु
	काष्ठा device *dev = context;
	काष्ठा spi_device *spi = to_spi_device(dev);

	वापस spi_ग_लिखो(spi, data, count);
पूर्ण

अटल काष्ठा regmap_bus bma400_regmap_bus = अणु
	.पढ़ो = bma400_regmap_spi_पढ़ो,
	.ग_लिखो = bma400_regmap_spi_ग_लिखो,
	.पढ़ो_flag_mask = BIT(7),
	.max_raw_पढ़ो = BMA400_MAX_SPI_READ,
पूर्ण;

अटल पूर्णांक bma400_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	regmap = devm_regmap_init(&spi->dev, &bma400_regmap_bus,
				  &spi->dev, &bma400_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&spi->dev, "failed to create regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	/*
	 * Per the bma400 datasheet, the first SPI पढ़ो may
	 * वापस garbage. As the datasheet recommends, the
	 * chip ID रेजिस्टर will be पढ़ो here and checked
	 * again in the following probe.
	 */
	ret = regmap_पढ़ो(regmap, BMA400_CHIP_ID_REG, &val);
	अगर (ret)
		dev_err(&spi->dev, "Failed to read chip id register\n");

	वापस bma400_probe(&spi->dev, regmap, id->name);
पूर्ण

अटल पूर्णांक bma400_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस bma400_हटाओ(&spi->dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id bma400_spi_ids[] = अणु
	अणु "bma400", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, bma400_spi_ids);

अटल स्थिर काष्ठा of_device_id bma400_of_spi_match[] = अणु
	अणु .compatible = "bosch,bma400" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bma400_of_spi_match);

अटल काष्ठा spi_driver bma400_spi_driver = अणु
	.driver = अणु
		.name = "bma400",
		.of_match_table = bma400_of_spi_match,
	पूर्ण,
	.probe    = bma400_spi_probe,
	.हटाओ   = bma400_spi_हटाओ,
	.id_table = bma400_spi_ids,
पूर्ण;

module_spi_driver(bma400_spi_driver);
MODULE_AUTHOR("Dan Robertson <dan@dlrobertson.com>");
MODULE_DESCRIPTION("Bosch BMA400 triaxial acceleration sensor (SPI)");
MODULE_LICENSE("GPL");
