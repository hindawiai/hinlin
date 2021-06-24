<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * BME680 - SPI Driver
 *
 * Copyright (C) 2018 Himanshu Jha <himanshujha199640@gmail.com>
 */
#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>

#समावेश "bme680.h"

काष्ठा bme680_spi_bus_context अणु
	काष्ठा spi_device *spi;
	u8 current_page;
पूर्ण;

/*
 * In SPI mode there are only 7 address bits, a "page" रेजिस्टर determines
 * which part of the 8-bit range is active. This function looks at the address
 * and ग_लिखोs the page selection bit अगर needed
 */
अटल पूर्णांक bme680_regmap_spi_select_page(
	काष्ठा bme680_spi_bus_context *ctx, u8 reg)
अणु
	काष्ठा spi_device *spi = ctx->spi;
	पूर्णांक ret;
	u8 buf[2];
	u8 page = (reg & 0x80) ? 0 : 1; /* Page "1" is low range */

	अगर (page == ctx->current_page)
		वापस 0;

	/*
	 * Data sheet claims we're only allowed to change bit 4, so we must करो
	 * a पढ़ो-modअगरy-ग_लिखो on each and every page select
	 */
	buf[0] = BME680_REG_STATUS;
	ret = spi_ग_लिखो_then_पढ़ो(spi, buf, 1, buf + 1, 1);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "failed to set page %u\n", page);
		वापस ret;
	पूर्ण

	buf[0] = BME680_REG_STATUS;
	अगर (page)
		buf[1] |= BME680_SPI_MEM_PAGE_BIT;
	अन्यथा
		buf[1] &= ~BME680_SPI_MEM_PAGE_BIT;

	ret = spi_ग_लिखो(spi, buf, 2);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "failed to set page %u\n", page);
		वापस ret;
	पूर्ण

	ctx->current_page = page;

	वापस 0;
पूर्ण

अटल पूर्णांक bme680_regmap_spi_ग_लिखो(व्योम *context, स्थिर व्योम *data,
				   माप_प्रकार count)
अणु
	काष्ठा bme680_spi_bus_context *ctx = context;
	काष्ठा spi_device *spi = ctx->spi;
	पूर्णांक ret;
	u8 buf[2];

	स_नकल(buf, data, 2);

	ret = bme680_regmap_spi_select_page(ctx, buf[0]);
	अगर (ret)
		वापस ret;

	/*
	 * The SPI रेजिस्टर address (= full रेजिस्टर address without bit 7)
	 * and the ग_लिखो command (bit7 = RW = '0')
	 */
	buf[0] &= ~0x80;

	वापस spi_ग_लिखो(spi, buf, 2);
पूर्ण

अटल पूर्णांक bme680_regmap_spi_पढ़ो(व्योम *context, स्थिर व्योम *reg,
				  माप_प्रकार reg_size, व्योम *val, माप_प्रकार val_size)
अणु
	काष्ठा bme680_spi_bus_context *ctx = context;
	काष्ठा spi_device *spi = ctx->spi;
	पूर्णांक ret;
	u8 addr = *(स्थिर u8 *)reg;

	ret = bme680_regmap_spi_select_page(ctx, addr);
	अगर (ret)
		वापस ret;

	addr |= 0x80; /* bit7 = RW = '1' */

	वापस spi_ग_लिखो_then_पढ़ो(spi, &addr, 1, val, val_size);
पूर्ण

अटल काष्ठा regmap_bus bme680_regmap_bus = अणु
	.ग_लिखो = bme680_regmap_spi_ग_लिखो,
	.पढ़ो = bme680_regmap_spi_पढ़ो,
	.reg_क्रमmat_endian_शेष = REGMAP_ENDIAN_BIG,
	.val_क्रमmat_endian_शेष = REGMAP_ENDIAN_BIG,
पूर्ण;

अटल पूर्णांक bme680_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	काष्ठा bme680_spi_bus_context *bus_context;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	spi->bits_per_word = 8;
	ret = spi_setup(spi);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "spi_setup failed!\n");
		वापस ret;
	पूर्ण

	bus_context = devm_kzalloc(&spi->dev, माप(*bus_context), GFP_KERNEL);
	अगर (!bus_context)
		वापस -ENOMEM;

	bus_context->spi = spi;
	bus_context->current_page = 0xff; /* Undefined on warm boot */

	regmap = devm_regmap_init(&spi->dev, &bme680_regmap_bus,
				  bus_context, &bme680_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&spi->dev, "Failed to register spi regmap %ld\n", PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण

	वापस bme680_core_probe(&spi->dev, regmap, id->name);
पूर्ण

अटल स्थिर काष्ठा spi_device_id bme680_spi_id[] = अणु
	अणु"bme680", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, bme680_spi_id);

अटल स्थिर काष्ठा acpi_device_id bme680_acpi_match[] = अणु
	अणु"BME0680", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, bme680_acpi_match);

अटल स्थिर काष्ठा of_device_id bme680_of_spi_match[] = अणु
	अणु .compatible = "bosch,bme680", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bme680_of_spi_match);

अटल काष्ठा spi_driver bme680_spi_driver = अणु
	.driver = अणु
		.name			= "bme680_spi",
		.acpi_match_table	= ACPI_PTR(bme680_acpi_match),
		.of_match_table		= bme680_of_spi_match,
	पूर्ण,
	.probe = bme680_spi_probe,
	.id_table = bme680_spi_id,
पूर्ण;
module_spi_driver(bme680_spi_driver);

MODULE_AUTHOR("Himanshu Jha <himanshujha199640@gmail.com>");
MODULE_DESCRIPTION("Bosch BME680 SPI driver");
MODULE_LICENSE("GPL v2");
