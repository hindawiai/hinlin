<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * API bus driver क्रम ADT7316/7/8 ADT7516/7/9 digital temperature
 * sensor, ADC and DAC
 *
 * Copyright 2010 Analog Devices Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spi/spi.h>

#समावेश "adt7316.h"

#घोषणा ADT7316_SPI_MAX_FREQ_HZ		5000000
#घोषणा ADT7316_SPI_CMD_READ		0x91
#घोषणा ADT7316_SPI_CMD_WRITE		0x90

/*
 * adt7316 रेजिस्टर access by SPI
 */

अटल पूर्णांक adt7316_spi_multi_पढ़ो(व्योम *client, u8 reg, u8 count, u8 *data)
अणु
	काष्ठा spi_device *spi_dev = client;
	u8 cmd[2];
	पूर्णांक ret;

	अगर (count > ADT7316_REG_MAX_ADDR)
		count = ADT7316_REG_MAX_ADDR;

	cmd[0] = ADT7316_SPI_CMD_WRITE;
	cmd[1] = reg;

	ret = spi_ग_लिखो(spi_dev, cmd, 2);
	अगर (ret < 0) अणु
		dev_err(&spi_dev->dev, "SPI fail to select reg\n");
		वापस ret;
	पूर्ण

	cmd[0] = ADT7316_SPI_CMD_READ;

	ret = spi_ग_लिखो_then_पढ़ो(spi_dev, cmd, 1, data, count);
	अगर (ret < 0) अणु
		dev_err(&spi_dev->dev, "SPI read data error\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adt7316_spi_multi_ग_लिखो(व्योम *client, u8 reg, u8 count, u8 *data)
अणु
	काष्ठा spi_device *spi_dev = client;
	u8 buf[ADT7316_REG_MAX_ADDR + 2];
	पूर्णांक i, ret;

	अगर (count > ADT7316_REG_MAX_ADDR)
		count = ADT7316_REG_MAX_ADDR;

	buf[0] = ADT7316_SPI_CMD_WRITE;
	buf[1] = reg;
	क्रम (i = 0; i < count; i++)
		buf[i + 2] = data[i];

	ret = spi_ग_लिखो(spi_dev, buf, count + 2);
	अगर (ret < 0) अणु
		dev_err(&spi_dev->dev, "SPI write error\n");
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक adt7316_spi_पढ़ो(व्योम *client, u8 reg, u8 *data)
अणु
	वापस adt7316_spi_multi_पढ़ो(client, reg, 1, data);
पूर्ण

अटल पूर्णांक adt7316_spi_ग_लिखो(व्योम *client, u8 reg, u8 val)
अणु
	वापस adt7316_spi_multi_ग_लिखो(client, reg, 1, &val);
पूर्ण

/*
 * device probe and हटाओ
 */

अटल पूर्णांक adt7316_spi_probe(काष्ठा spi_device *spi_dev)
अणु
	काष्ठा adt7316_bus bus = अणु
		.client = spi_dev,
		.irq = spi_dev->irq,
		.पढ़ो = adt7316_spi_पढ़ो,
		.ग_लिखो = adt7316_spi_ग_लिखो,
		.multi_पढ़ो = adt7316_spi_multi_पढ़ो,
		.multi_ग_लिखो = adt7316_spi_multi_ग_लिखो,
	पूर्ण;

	/* करोn't exceed max specअगरied SPI CLK frequency */
	अगर (spi_dev->max_speed_hz > ADT7316_SPI_MAX_FREQ_HZ) अणु
		dev_err(&spi_dev->dev, "SPI CLK %d Hz?\n",
			spi_dev->max_speed_hz);
		वापस -EINVAL;
	पूर्ण

	/* चयन from शेष I2C protocol to SPI protocol */
	adt7316_spi_ग_लिखो(spi_dev, 0, 0);
	adt7316_spi_ग_लिखो(spi_dev, 0, 0);
	adt7316_spi_ग_लिखो(spi_dev, 0, 0);

	वापस adt7316_probe(&spi_dev->dev, &bus, spi_dev->modalias);
पूर्ण

अटल स्थिर काष्ठा spi_device_id adt7316_spi_id[] = अणु
	अणु "adt7316", 0 पूर्ण,
	अणु "adt7317", 0 पूर्ण,
	अणु "adt7318", 0 पूर्ण,
	अणु "adt7516", 0 पूर्ण,
	अणु "adt7517", 0 पूर्ण,
	अणु "adt7519", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(spi, adt7316_spi_id);

अटल स्थिर काष्ठा of_device_id adt7316_of_spi_match[] = अणु
	अणु .compatible = "adi,adt7316" पूर्ण,
	अणु .compatible = "adi,adt7317" पूर्ण,
	अणु .compatible = "adi,adt7318" पूर्ण,
	अणु .compatible = "adi,adt7516" पूर्ण,
	अणु .compatible = "adi,adt7517" पूर्ण,
	अणु .compatible = "adi,adt7519" पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, adt7316_of_spi_match);

अटल काष्ठा spi_driver adt7316_driver = अणु
	.driver = अणु
		.name = "adt7316",
		.of_match_table = adt7316_of_spi_match,
		.pm = ADT7316_PM_OPS,
	पूर्ण,
	.probe = adt7316_spi_probe,
	.id_table = adt7316_spi_id,
पूर्ण;
module_spi_driver(adt7316_driver);

MODULE_AUTHOR("Sonic Zhang <sonic.zhang@analog.com>");
MODULE_DESCRIPTION("SPI bus driver for Analog Devices ADT7316/7/8 and ADT7516/7/9 digital temperature sensor, ADC and DAC");
MODULE_LICENSE("GPL v2");
