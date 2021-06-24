<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AD5672R, AD5674R, AD5676, AD5676R, AD5679R,
 * AD5681R, AD5682R, AD5683, AD5683R, AD5684,
 * AD5684R, AD5685R, AD5686, AD5686R
 * Digital to analog converters driver
 *
 * Copyright 2018 Analog Devices Inc.
 */

#समावेश "ad5686.h"

#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>

अटल पूर्णांक ad5686_spi_ग_लिखो(काष्ठा ad5686_state *st,
			    u8 cmd, u8 addr, u16 val)
अणु
	काष्ठा spi_device *spi = to_spi_device(st->dev);
	u8 tx_len, *buf;

	चयन (st->chip_info->regmap_type) अणु
	हाल AD5310_REGMAP:
		st->data[0].d16 = cpu_to_be16(AD5310_CMD(cmd) |
					      val);
		buf = &st->data[0].d8[0];
		tx_len = 2;
		अवरोध;
	हाल AD5683_REGMAP:
		st->data[0].d32 = cpu_to_be32(AD5686_CMD(cmd) |
					      AD5683_DATA(val));
		buf = &st->data[0].d8[1];
		tx_len = 3;
		अवरोध;
	हाल AD5686_REGMAP:
		st->data[0].d32 = cpu_to_be32(AD5686_CMD(cmd) |
					      AD5686_ADDR(addr) |
					      val);
		buf = &st->data[0].d8[1];
		tx_len = 3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस spi_ग_लिखो(spi, buf, tx_len);
पूर्ण

अटल पूर्णांक ad5686_spi_पढ़ो(काष्ठा ad5686_state *st, u8 addr)
अणु
	काष्ठा spi_transfer t[] = अणु
		अणु
			.tx_buf = &st->data[0].d8[1],
			.len = 3,
			.cs_change = 1,
		पूर्ण, अणु
			.tx_buf = &st->data[1].d8[1],
			.rx_buf = &st->data[2].d8[1],
			.len = 3,
		पूर्ण,
	पूर्ण;
	काष्ठा spi_device *spi = to_spi_device(st->dev);
	u8 cmd = 0;
	पूर्णांक ret;

	चयन (st->chip_info->regmap_type) अणु
	हाल AD5310_REGMAP:
		वापस -ENOTSUPP;
	हाल AD5683_REGMAP:
		cmd = AD5686_CMD_READBACK_ENABLE_V2;
		अवरोध;
	हाल AD5686_REGMAP:
		cmd = AD5686_CMD_READBACK_ENABLE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	st->data[0].d32 = cpu_to_be32(AD5686_CMD(cmd) |
				      AD5686_ADDR(addr));
	st->data[1].d32 = cpu_to_be32(AD5686_CMD(AD5686_CMD_NOOP));

	ret = spi_sync_transfer(spi, t, ARRAY_SIZE(t));
	अगर (ret < 0)
		वापस ret;

	वापस be32_to_cpu(st->data[2].d32);
पूर्ण

अटल पूर्णांक ad5686_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);

	वापस ad5686_probe(&spi->dev, id->driver_data, id->name,
			    ad5686_spi_ग_लिखो, ad5686_spi_पढ़ो);
पूर्ण

अटल पूर्णांक ad5686_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस ad5686_हटाओ(&spi->dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad5686_spi_id[] = अणु
	अणु"ad5310r", ID_AD5310Rपूर्ण,
	अणु"ad5672r", ID_AD5672Rपूर्ण,
	अणु"ad5674r", ID_AD5674Rपूर्ण,
	अणु"ad5676", ID_AD5676पूर्ण,
	अणु"ad5676r", ID_AD5676Rपूर्ण,
	अणु"ad5679r", ID_AD5679Rपूर्ण,
	अणु"ad5681r", ID_AD5681Rपूर्ण,
	अणु"ad5682r", ID_AD5682Rपूर्ण,
	अणु"ad5683", ID_AD5683पूर्ण,
	अणु"ad5683r", ID_AD5683Rपूर्ण,
	अणु"ad5684", ID_AD5684पूर्ण,
	अणु"ad5684r", ID_AD5684Rपूर्ण,
	अणु"ad5685", ID_AD5685Rपूर्ण, /* Does not exist */
	अणु"ad5685r", ID_AD5685Rपूर्ण,
	अणु"ad5686", ID_AD5686पूर्ण,
	अणु"ad5686r", ID_AD5686Rपूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad5686_spi_id);

अटल काष्ठा spi_driver ad5686_spi_driver = अणु
	.driver = अणु
		.name = "ad5686",
	पूर्ण,
	.probe = ad5686_spi_probe,
	.हटाओ = ad5686_spi_हटाओ,
	.id_table = ad5686_spi_id,
पूर्ण;

module_spi_driver(ad5686_spi_driver);

MODULE_AUTHOR("Stefan Popa <stefan.popa@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD5686 and similar multi-channel DACs");
MODULE_LICENSE("GPL v2");
