<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AD5592R Digital <-> Analog converters driver
 *
 * Copyright 2015-2016 Analog Devices Inc.
 * Author: Paul Cercueil <paul.cercueil@analog.com>
 */

#समावेश "ad5592r-base.h"

#समावेश <linux/bitops.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/spi/spi.h>

#घोषणा AD5592R_GPIO_READBACK_EN	BIT(10)
#घोषणा AD5592R_LDAC_READBACK_EN	BIT(6)

अटल पूर्णांक ad5592r_spi_wnop_r16(काष्ठा ad5592r_state *st, __be16 *buf)
अणु
	काष्ठा spi_device *spi = container_of(st->dev, काष्ठा spi_device, dev);
	काष्ठा spi_transfer t = अणु
			.tx_buf	= &st->spi_msg_nop,
			.rx_buf	= buf,
			.len = 2
		पूर्ण;

	st->spi_msg_nop = 0; /* NOP */

	वापस spi_sync_transfer(spi, &t, 1);
पूर्ण

अटल पूर्णांक ad5592r_ग_लिखो_dac(काष्ठा ad5592r_state *st, अचिन्हित chan, u16 value)
अणु
	काष्ठा spi_device *spi = container_of(st->dev, काष्ठा spi_device, dev);

	st->spi_msg = cpu_to_be16(BIT(15) | (chan << 12) | value);

	वापस spi_ग_लिखो(spi, &st->spi_msg, माप(st->spi_msg));
पूर्ण

अटल पूर्णांक ad5592r_पढ़ो_adc(काष्ठा ad5592r_state *st, अचिन्हित chan, u16 *value)
अणु
	काष्ठा spi_device *spi = container_of(st->dev, काष्ठा spi_device, dev);
	पूर्णांक ret;

	st->spi_msg = cpu_to_be16((AD5592R_REG_ADC_SEQ << 11) | BIT(chan));

	ret = spi_ग_लिखो(spi, &st->spi_msg, माप(st->spi_msg));
	अगर (ret)
		वापस ret;

	/*
	 * Invalid data:
	 * See Figure 40. Single-Channel ADC Conversion Sequence
	 */
	ret = ad5592r_spi_wnop_r16(st, &st->spi_msg);
	अगर (ret)
		वापस ret;

	ret = ad5592r_spi_wnop_r16(st, &st->spi_msg);
	अगर (ret)
		वापस ret;

	*value = be16_to_cpu(st->spi_msg);

	वापस 0;
पूर्ण

अटल पूर्णांक ad5592r_reg_ग_लिखो(काष्ठा ad5592r_state *st, u8 reg, u16 value)
अणु
	काष्ठा spi_device *spi = container_of(st->dev, काष्ठा spi_device, dev);

	st->spi_msg = cpu_to_be16((reg << 11) | value);

	वापस spi_ग_लिखो(spi, &st->spi_msg, माप(st->spi_msg));
पूर्ण

अटल पूर्णांक ad5592r_reg_पढ़ो(काष्ठा ad5592r_state *st, u8 reg, u16 *value)
अणु
	काष्ठा spi_device *spi = container_of(st->dev, काष्ठा spi_device, dev);
	पूर्णांक ret;

	st->spi_msg = cpu_to_be16((AD5592R_REG_LDAC << 11) |
				   AD5592R_LDAC_READBACK_EN | (reg << 2));

	ret = spi_ग_लिखो(spi, &st->spi_msg, माप(st->spi_msg));
	अगर (ret)
		वापस ret;

	ret = ad5592r_spi_wnop_r16(st, &st->spi_msg);
	अगर (ret)
		वापस ret;

	*value = be16_to_cpu(st->spi_msg);

	वापस 0;
पूर्ण

अटल पूर्णांक ad5592r_gpio_पढ़ो(काष्ठा ad5592r_state *st, u8 *value)
अणु
	पूर्णांक ret;

	ret = ad5592r_reg_ग_लिखो(st, AD5592R_REG_GPIO_IN_EN,
				AD5592R_GPIO_READBACK_EN | st->gpio_in);
	अगर (ret)
		वापस ret;

	ret = ad5592r_spi_wnop_r16(st, &st->spi_msg);
	अगर (ret)
		वापस ret;

	*value = (u8) be16_to_cpu(st->spi_msg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ad5592r_rw_ops ad5592r_rw_ops = अणु
	.ग_लिखो_dac = ad5592r_ग_लिखो_dac,
	.पढ़ो_adc = ad5592r_पढ़ो_adc,
	.reg_ग_लिखो = ad5592r_reg_ग_लिखो,
	.reg_पढ़ो = ad5592r_reg_पढ़ो,
	.gpio_पढ़ो = ad5592r_gpio_पढ़ो,
पूर्ण;

अटल पूर्णांक ad5592r_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);

	वापस ad5592r_probe(&spi->dev, id->name, &ad5592r_rw_ops);
पूर्ण

अटल पूर्णांक ad5592r_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस ad5592r_हटाओ(&spi->dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad5592r_spi_ids[] = अणु
	अणु .name = "ad5592r", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad5592r_spi_ids);

अटल स्थिर काष्ठा of_device_id ad5592r_of_match[] = अणु
	अणु .compatible = "adi,ad5592r", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ad5592r_of_match);

अटल स्थिर काष्ठा acpi_device_id ad5592r_acpi_match[] = अणु
	अणु"ADS5592", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ad5592r_acpi_match);

अटल काष्ठा spi_driver ad5592r_spi_driver = अणु
	.driver = अणु
		.name = "ad5592r",
		.of_match_table = ad5592r_of_match,
		.acpi_match_table = ad5592r_acpi_match,
	पूर्ण,
	.probe = ad5592r_spi_probe,
	.हटाओ = ad5592r_spi_हटाओ,
	.id_table = ad5592r_spi_ids,
पूर्ण;
module_spi_driver(ad5592r_spi_driver);

MODULE_AUTHOR("Paul Cercueil <paul.cercueil@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD5592R multi-channel converters");
MODULE_LICENSE("GPL v2");
