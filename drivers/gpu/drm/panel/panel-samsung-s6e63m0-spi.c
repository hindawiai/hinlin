<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/delay.h>

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "panel-samsung-s6e63m0.h"

#घोषणा DATA_MASK	0x100

अटल पूर्णांक s6e63m0_spi_dcs_पढ़ो(काष्ठा device *dev, स्थिर u8 cmd, u8 *data)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);
	u16 buf[1];
	u16 rbuf[1];
	पूर्णांक ret;

	/* SPI buffers are always in CPU order */
	buf[0] = (u16)cmd;
	ret = spi_ग_लिखो_then_पढ़ो(spi, buf, 2, rbuf, 2);
	dev_dbg(dev, "READ CMD: %04x RET: %04x\n", buf[0], rbuf[0]);
	अगर (!ret)
		/* These high 8 bits of the 9 contains the पढ़ोout */
		*data = (rbuf[0] & 0x1ff) >> 1;

	वापस ret;
पूर्ण

अटल पूर्णांक s6e63m0_spi_ग_लिखो_word(काष्ठा device *dev, u16 data)
अणु
	काष्ठा spi_device *spi = to_spi_device(dev);

	/* SPI buffers are always in CPU order */
	वापस spi_ग_लिखो(spi, &data, 2);
पूर्ण

अटल पूर्णांक s6e63m0_spi_dcs_ग_लिखो(काष्ठा device *dev, स्थिर u8 *data, माप_प्रकार len)
अणु
	पूर्णांक ret = 0;

	dev_dbg(dev, "SPI writing dcs seq: %*ph\n", (पूर्णांक)len, data);

	/*
	 * This sends 9 bits with the first bit (bit 8) set to 0
	 * This indicates that this is a command. Anything after the
	 * command is data.
	 */
	ret = s6e63m0_spi_ग_लिखो_word(dev, *data);

	जबतक (!ret && --len) अणु
		++data;
		/* This sends 9 bits with the first bit (bit 8) set to 1 */
		ret = s6e63m0_spi_ग_लिखो_word(dev, *data | DATA_MASK);
	पूर्ण

	अगर (ret) अणु
		dev_err(dev, "SPI error %d writing dcs seq: %*ph\n", ret,
			(पूर्णांक)len, data);
	पूर्ण

	usleep_range(300, 310);

	वापस ret;
पूर्ण

अटल पूर्णांक s6e63m0_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	पूर्णांक ret;

	spi->bits_per_word = 9;
	/* Preserve e.g. SPI_3WIRE setting */
	spi->mode |= SPI_MODE_3;
	ret = spi_setup(spi);
	अगर (ret < 0) अणु
		dev_err(dev, "spi setup failed.\n");
		वापस ret;
	पूर्ण
	वापस s6e63m0_probe(dev, s6e63m0_spi_dcs_पढ़ो, s6e63m0_spi_dcs_ग_लिखो,
			     false);
पूर्ण

अटल पूर्णांक s6e63m0_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस s6e63m0_हटाओ(&spi->dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id s6e63m0_spi_of_match[] = अणु
	अणु .compatible = "samsung,s6e63m0" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, s6e63m0_spi_of_match);

अटल काष्ठा spi_driver s6e63m0_spi_driver = अणु
	.probe			= s6e63m0_spi_probe,
	.हटाओ			= s6e63m0_spi_हटाओ,
	.driver			= अणु
		.name		= "panel-samsung-s6e63m0",
		.of_match_table = s6e63m0_spi_of_match,
	पूर्ण,
पूर्ण;
module_spi_driver(s6e63m0_spi_driver);

MODULE_AUTHOR("Paweध Chmiel <pawel.mikolaj.chmiel@gmail.com>");
MODULE_DESCRIPTION("s6e63m0 LCD SPI Driver");
MODULE_LICENSE("GPL v2");
