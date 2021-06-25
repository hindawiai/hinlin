<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ADT7310/ADT7310 digital temperature sensor driver
 *
 * Copyright 2012-2013 Analog Devices Inc.
 *   Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/spi/spi.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "adt7x10.h"

#घोषणा ADT7310_STATUS			0
#घोषणा ADT7310_CONFIG			1
#घोषणा ADT7310_TEMPERATURE		2
#घोषणा ADT7310_ID			3
#घोषणा ADT7310_T_CRIT			4
#घोषणा ADT7310_T_HYST			5
#घोषणा ADT7310_T_ALARM_HIGH		6
#घोषणा ADT7310_T_ALARM_LOW		7

अटल स्थिर u8 adt7310_reg_table[] = अणु
	[ADT7X10_TEMPERATURE]   = ADT7310_TEMPERATURE,
	[ADT7X10_STATUS]	= ADT7310_STATUS,
	[ADT7X10_CONFIG]	= ADT7310_CONFIG,
	[ADT7X10_T_ALARM_HIGH]	= ADT7310_T_ALARM_HIGH,
	[ADT7X10_T_ALARM_LOW]	= ADT7310_T_ALARM_LOW,
	[ADT7X10_T_CRIT]	= ADT7310_T_CRIT,
	[ADT7X10_T_HYST]	= ADT7310_T_HYST,
	[ADT7X10_ID]		= ADT7310_ID,
पूर्ण;

#घोषणा ADT7310_CMD_REG_OFFSET	3
#घोषणा ADT7310_CMD_READ	0x40

#घोषणा AD7310_COMMAND(reg) (adt7310_reg_table[(reg)] << ADT7310_CMD_REG_OFFSET)

अटल पूर्णांक adt7310_spi_पढ़ो_word(काष्ठा device *dev, u8 reg)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);

	वापस spi_w8r16be(spi, AD7310_COMMAND(reg) | ADT7310_CMD_READ);
पूर्ण

अटल पूर्णांक adt7310_spi_ग_लिखो_word(काष्ठा device *dev, u8 reg, u16 data)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	u8 buf[3];

	buf[0] = AD7310_COMMAND(reg);
	put_unaligned_be16(data, &buf[1]);

	वापस spi_ग_लिखो(spi, buf, माप(buf));
पूर्ण

अटल पूर्णांक adt7310_spi_पढ़ो_byte(काष्ठा device *dev, u8 reg)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);

	वापस spi_w8r8(spi, AD7310_COMMAND(reg) | ADT7310_CMD_READ);
पूर्ण

अटल पूर्णांक adt7310_spi_ग_लिखो_byte(काष्ठा device *dev, u8 reg,
	u8 data)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	u8 buf[2];

	buf[0] = AD7310_COMMAND(reg);
	buf[1] = data;

	वापस spi_ग_लिखो(spi, buf, माप(buf));
पूर्ण

अटल स्थिर काष्ठा adt7x10_ops adt7310_spi_ops = अणु
	.पढ़ो_word = adt7310_spi_पढ़ो_word,
	.ग_लिखो_word = adt7310_spi_ग_लिखो_word,
	.पढ़ो_byte = adt7310_spi_पढ़ो_byte,
	.ग_लिखो_byte = adt7310_spi_ग_लिखो_byte,
पूर्ण;

अटल पूर्णांक adt7310_spi_probe(काष्ठा spi_device *spi)
अणु
	वापस adt7x10_probe(&spi->dev, spi_get_device_id(spi)->name, spi->irq,
			&adt7310_spi_ops);
पूर्ण

अटल पूर्णांक adt7310_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस adt7x10_हटाओ(&spi->dev, spi->irq);
पूर्ण

अटल स्थिर काष्ठा spi_device_id adt7310_id[] = अणु
	अणु "adt7310", 0 पूर्ण,
	अणु "adt7320", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, adt7310_id);

अटल काष्ठा spi_driver adt7310_driver = अणु
	.driver = अणु
		.name	= "adt7310",
		.pm	= ADT7X10_DEV_PM_OPS,
	पूर्ण,
	.probe		= adt7310_spi_probe,
	.हटाओ		= adt7310_spi_हटाओ,
	.id_table	= adt7310_id,
पूर्ण;
module_spi_driver(adt7310_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("ADT7310/ADT7320 driver");
MODULE_LICENSE("GPL");
