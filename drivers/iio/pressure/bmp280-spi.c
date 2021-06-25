<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SPI पूर्णांकerface क्रम the BMP280 driver
 *
 * Inspired by the older BMP085 driver drivers/misc/bmp085-spi.c
 */
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/err.h>
#समावेश <linux/regmap.h>

#समावेश "bmp280.h"

अटल पूर्णांक bmp280_regmap_spi_ग_लिखो(व्योम *context, स्थिर व्योम *data,
                                   माप_प्रकार count)
अणु
	काष्ठा device *dev = context;
	काष्ठा spi_device *spi = to_spi_device(dev);
	u8 buf[2];

	स_नकल(buf, data, 2);
	/*
	 * The SPI रेजिस्टर address (= full रेजिस्टर address without bit 7) and
	 * the ग_लिखो command (bit7 = RW = '0')
	 */
	buf[0] &= ~0x80;

	वापस spi_ग_लिखो_then_पढ़ो(spi, buf, 2, शून्य, 0);
पूर्ण

अटल पूर्णांक bmp280_regmap_spi_पढ़ो(व्योम *context, स्थिर व्योम *reg,
                                  माप_प्रकार reg_size, व्योम *val, माप_प्रकार val_size)
अणु
	काष्ठा device *dev = context;
	काष्ठा spi_device *spi = to_spi_device(dev);

	वापस spi_ग_लिखो_then_पढ़ो(spi, reg, reg_size, val, val_size);
पूर्ण

अटल काष्ठा regmap_bus bmp280_regmap_bus = अणु
	.ग_लिखो = bmp280_regmap_spi_ग_लिखो,
	.पढ़ो = bmp280_regmap_spi_पढ़ो,
	.reg_क्रमmat_endian_शेष = REGMAP_ENDIAN_BIG,
	.val_क्रमmat_endian_शेष = REGMAP_ENDIAN_BIG,
पूर्ण;

अटल पूर्णांक bmp280_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	काष्ठा regmap *regmap;
	स्थिर काष्ठा regmap_config *regmap_config;
	पूर्णांक ret;

	spi->bits_per_word = 8;
	ret = spi_setup(spi);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "spi_setup failed!\n");
		वापस ret;
	पूर्ण

	चयन (id->driver_data) अणु
	हाल BMP180_CHIP_ID:
		regmap_config = &bmp180_regmap_config;
		अवरोध;
	हाल BMP280_CHIP_ID:
	हाल BME280_CHIP_ID:
		regmap_config = &bmp280_regmap_config;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap = devm_regmap_init(&spi->dev,
				  &bmp280_regmap_bus,
				  &spi->dev,
				  regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&spi->dev, "failed to allocate register map\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस bmp280_common_probe(&spi->dev,
				   regmap,
				   id->driver_data,
				   id->name,
				   spi->irq);
पूर्ण

अटल स्थिर काष्ठा of_device_id bmp280_of_spi_match[] = अणु
	अणु .compatible = "bosch,bmp085", पूर्ण,
	अणु .compatible = "bosch,bmp180", पूर्ण,
	अणु .compatible = "bosch,bmp181", पूर्ण,
	अणु .compatible = "bosch,bmp280", पूर्ण,
	अणु .compatible = "bosch,bme280", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bmp280_of_spi_match);

अटल स्थिर काष्ठा spi_device_id bmp280_spi_id[] = अणु
	अणु "bmp180", BMP180_CHIP_ID पूर्ण,
	अणु "bmp181", BMP180_CHIP_ID पूर्ण,
	अणु "bmp280", BMP280_CHIP_ID पूर्ण,
	अणु "bme280", BME280_CHIP_ID पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, bmp280_spi_id);

अटल काष्ठा spi_driver bmp280_spi_driver = अणु
	.driver = अणु
		.name = "bmp280",
		.of_match_table = bmp280_of_spi_match,
		.pm = &bmp280_dev_pm_ops,
	पूर्ण,
	.id_table = bmp280_spi_id,
	.probe = bmp280_spi_probe,
पूर्ण;
module_spi_driver(bmp280_spi_driver);

MODULE_DESCRIPTION("BMP280 SPI bus driver");
MODULE_LICENSE("GPL");
