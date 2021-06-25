<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AD5593R Digital <-> Analog converters driver
 *
 * Copyright 2015-2016 Analog Devices Inc.
 * Author: Paul Cercueil <paul.cercueil@analog.com>
 */

#समावेश "ad5592r-base.h"

#समावेश <linux/bitops.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>

#घोषणा AD5593R_MODE_CONF		(0 << 4)
#घोषणा AD5593R_MODE_DAC_WRITE		(1 << 4)
#घोषणा AD5593R_MODE_ADC_READBACK	(4 << 4)
#घोषणा AD5593R_MODE_DAC_READBACK	(5 << 4)
#घोषणा AD5593R_MODE_GPIO_READBACK	(6 << 4)
#घोषणा AD5593R_MODE_REG_READBACK	(7 << 4)

अटल पूर्णांक ad5593r_ग_लिखो_dac(काष्ठा ad5592r_state *st, अचिन्हित chan, u16 value)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(st->dev);

	वापस i2c_smbus_ग_लिखो_word_swapped(i2c,
			AD5593R_MODE_DAC_WRITE | chan, value);
पूर्ण

अटल पूर्णांक ad5593r_पढ़ो_adc(काष्ठा ad5592r_state *st, अचिन्हित chan, u16 *value)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(st->dev);
	s32 val;

	val = i2c_smbus_ग_लिखो_word_swapped(i2c,
			AD5593R_MODE_CONF | AD5592R_REG_ADC_SEQ, BIT(chan));
	अगर (val < 0)
		वापस (पूर्णांक) val;

	val = i2c_smbus_पढ़ो_word_swapped(i2c, AD5593R_MODE_ADC_READBACK);
	अगर (val < 0)
		वापस (पूर्णांक) val;

	*value = (u16) val;

	वापस 0;
पूर्ण

अटल पूर्णांक ad5593r_reg_ग_लिखो(काष्ठा ad5592r_state *st, u8 reg, u16 value)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(st->dev);

	वापस i2c_smbus_ग_लिखो_word_swapped(i2c,
			AD5593R_MODE_CONF | reg, value);
पूर्ण

अटल पूर्णांक ad5593r_reg_पढ़ो(काष्ठा ad5592r_state *st, u8 reg, u16 *value)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(st->dev);
	s32 val;

	val = i2c_smbus_पढ़ो_word_swapped(i2c, AD5593R_MODE_REG_READBACK | reg);
	अगर (val < 0)
		वापस (पूर्णांक) val;

	*value = (u16) val;

	वापस 0;
पूर्ण

अटल पूर्णांक ad5593r_gpio_पढ़ो(काष्ठा ad5592r_state *st, u8 *value)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(st->dev);
	s32 val;

	val = i2c_smbus_पढ़ो_word_swapped(i2c, AD5593R_MODE_GPIO_READBACK);
	अगर (val < 0)
		वापस (पूर्णांक) val;

	*value = (u8) val;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ad5592r_rw_ops ad5593r_rw_ops = अणु
	.ग_लिखो_dac = ad5593r_ग_लिखो_dac,
	.पढ़ो_adc = ad5593r_पढ़ो_adc,
	.reg_ग_लिखो = ad5593r_reg_ग_लिखो,
	.reg_पढ़ो = ad5593r_reg_पढ़ो,
	.gpio_पढ़ो = ad5593r_gpio_पढ़ो,
पूर्ण;

अटल पूर्णांक ad5593r_i2c_probe(काष्ठा i2c_client *i2c,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	वापस ad5592r_probe(&i2c->dev, id->name, &ad5593r_rw_ops);
पूर्ण

अटल पूर्णांक ad5593r_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	वापस ad5592r_हटाओ(&i2c->dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ad5593r_i2c_ids[] = अणु
	अणु .name = "ad5593r", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ad5593r_i2c_ids);

अटल स्थिर काष्ठा of_device_id ad5593r_of_match[] = अणु
	अणु .compatible = "adi,ad5593r", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ad5593r_of_match);

अटल स्थिर काष्ठा acpi_device_id ad5593r_acpi_match[] = अणु
	अणु"ADS5593", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ad5593r_acpi_match);

अटल काष्ठा i2c_driver ad5593r_driver = अणु
	.driver = अणु
		.name = "ad5593r",
		.of_match_table = ad5593r_of_match,
		.acpi_match_table = ad5593r_acpi_match,
	पूर्ण,
	.probe = ad5593r_i2c_probe,
	.हटाओ = ad5593r_i2c_हटाओ,
	.id_table = ad5593r_i2c_ids,
पूर्ण;
module_i2c_driver(ad5593r_driver);

MODULE_AUTHOR("Paul Cercueil <paul.cercueil@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD5593R multi-channel converters");
MODULE_LICENSE("GPL v2");
