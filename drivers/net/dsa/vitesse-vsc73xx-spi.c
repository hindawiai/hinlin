<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* DSA driver क्रम:
 * Vitesse VSC7385 SparX-G5 5+1-port Integrated Gigabit Ethernet Switch
 * Vitesse VSC7388 SparX-G8 8-port Integrated Gigabit Ethernet Switch
 * Vitesse VSC7395 SparX-G5e 5+1-port Integrated Gigabit Ethernet Switch
 * Vitesse VSC7398 SparX-G8e 8-port Integrated Gigabit Ethernet Switch
 *
 * This driver takes control of the चयन chip over SPI and
 * configures it to route packages around when connected to a CPU port.
 *
 * Copyright (C) 2018 Linus Wallej <linus.walleij@linaro.org>
 * Includes portions of code from the firmware uploader by:
 * Copyright (C) 2009 Gabor Juhos <juhosg@खोलोwrt.org>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/spi/spi.h>

#समावेश "vitesse-vsc73xx.h"

#घोषणा VSC73XX_CMD_SPI_MODE_READ		0
#घोषणा VSC73XX_CMD_SPI_MODE_WRITE		1
#घोषणा VSC73XX_CMD_SPI_MODE_SHIFT		4
#घोषणा VSC73XX_CMD_SPI_BLOCK_SHIFT		5
#घोषणा VSC73XX_CMD_SPI_BLOCK_MASK		0x7
#घोषणा VSC73XX_CMD_SPI_SUBBLOCK_MASK		0xf

/*
 * काष्ठा vsc73xx_spi - VSC73xx SPI state container
 */
काष्ठा vsc73xx_spi अणु
	काष्ठा spi_device	*spi;
	काष्ठा mutex		lock; /* Protects SPI traffic */
	काष्ठा vsc73xx		vsc;
पूर्ण;

अटल स्थिर काष्ठा vsc73xx_ops vsc73xx_spi_ops;

अटल u8 vsc73xx_make_addr(u8 mode, u8 block, u8 subblock)
अणु
	u8 ret;

	ret =
	    (block & VSC73XX_CMD_SPI_BLOCK_MASK) << VSC73XX_CMD_SPI_BLOCK_SHIFT;
	ret |= (mode & 1) << VSC73XX_CMD_SPI_MODE_SHIFT;
	ret |= subblock & VSC73XX_CMD_SPI_SUBBLOCK_MASK;

	वापस ret;
पूर्ण

अटल पूर्णांक vsc73xx_spi_पढ़ो(काष्ठा vsc73xx *vsc, u8 block, u8 subblock, u8 reg,
			    u32 *val)
अणु
	काष्ठा vsc73xx_spi *vsc_spi = vsc->priv;
	काष्ठा spi_transfer t[2];
	काष्ठा spi_message m;
	u8 cmd[4];
	u8 buf[4];
	पूर्णांक ret;

	अगर (!vsc73xx_is_addr_valid(block, subblock))
		वापस -EINVAL;

	spi_message_init(&m);

	स_रखो(&t, 0, माप(t));

	t[0].tx_buf = cmd;
	t[0].len = माप(cmd);
	spi_message_add_tail(&t[0], &m);

	t[1].rx_buf = buf;
	t[1].len = माप(buf);
	spi_message_add_tail(&t[1], &m);

	cmd[0] = vsc73xx_make_addr(VSC73XX_CMD_SPI_MODE_READ, block, subblock);
	cmd[1] = reg;
	cmd[2] = 0;
	cmd[3] = 0;

	mutex_lock(&vsc_spi->lock);
	ret = spi_sync(vsc_spi->spi, &m);
	mutex_unlock(&vsc_spi->lock);

	अगर (ret)
		वापस ret;

	*val = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];

	वापस 0;
पूर्ण

अटल पूर्णांक vsc73xx_spi_ग_लिखो(काष्ठा vsc73xx *vsc, u8 block, u8 subblock, u8 reg,
			     u32 val)
अणु
	काष्ठा vsc73xx_spi *vsc_spi = vsc->priv;
	काष्ठा spi_transfer t[2];
	काष्ठा spi_message m;
	u8 cmd[2];
	u8 buf[4];
	पूर्णांक ret;

	अगर (!vsc73xx_is_addr_valid(block, subblock))
		वापस -EINVAL;

	spi_message_init(&m);

	स_रखो(&t, 0, माप(t));

	t[0].tx_buf = cmd;
	t[0].len = माप(cmd);
	spi_message_add_tail(&t[0], &m);

	t[1].tx_buf = buf;
	t[1].len = माप(buf);
	spi_message_add_tail(&t[1], &m);

	cmd[0] = vsc73xx_make_addr(VSC73XX_CMD_SPI_MODE_WRITE, block, subblock);
	cmd[1] = reg;

	buf[0] = (val >> 24) & 0xff;
	buf[1] = (val >> 16) & 0xff;
	buf[2] = (val >> 8) & 0xff;
	buf[3] = val & 0xff;

	mutex_lock(&vsc_spi->lock);
	ret = spi_sync(vsc_spi->spi, &m);
	mutex_unlock(&vsc_spi->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक vsc73xx_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा vsc73xx_spi *vsc_spi;
	पूर्णांक ret;

	vsc_spi = devm_kzalloc(dev, माप(*vsc_spi), GFP_KERNEL);
	अगर (!vsc_spi)
		वापस -ENOMEM;

	spi_set_drvdata(spi, vsc_spi);
	vsc_spi->spi = spi_dev_get(spi);
	vsc_spi->vsc.dev = dev;
	vsc_spi->vsc.priv = vsc_spi;
	vsc_spi->vsc.ops = &vsc73xx_spi_ops;
	mutex_init(&vsc_spi->lock);

	spi->mode = SPI_MODE_0;
	spi->bits_per_word = 8;
	ret = spi_setup(spi);
	अगर (ret < 0) अणु
		dev_err(dev, "spi setup failed.\n");
		वापस ret;
	पूर्ण

	वापस vsc73xx_probe(&vsc_spi->vsc);
पूर्ण

अटल पूर्णांक vsc73xx_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा vsc73xx_spi *vsc_spi = spi_get_drvdata(spi);

	वापस vsc73xx_हटाओ(&vsc_spi->vsc);
पूर्ण

अटल स्थिर काष्ठा vsc73xx_ops vsc73xx_spi_ops = अणु
	.पढ़ो = vsc73xx_spi_पढ़ो,
	.ग_लिखो = vsc73xx_spi_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा of_device_id vsc73xx_of_match[] = अणु
	अणु
		.compatible = "vitesse,vsc7385",
	पूर्ण,
	अणु
		.compatible = "vitesse,vsc7388",
	पूर्ण,
	अणु
		.compatible = "vitesse,vsc7395",
	पूर्ण,
	अणु
		.compatible = "vitesse,vsc7398",
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, vsc73xx_of_match);

अटल काष्ठा spi_driver vsc73xx_spi_driver = अणु
	.probe = vsc73xx_spi_probe,
	.हटाओ = vsc73xx_spi_हटाओ,
	.driver = अणु
		.name = "vsc73xx-spi",
		.of_match_table = vsc73xx_of_match,
	पूर्ण,
पूर्ण;
module_spi_driver(vsc73xx_spi_driver);

MODULE_AUTHOR("Linus Walleij <linus.walleij@linaro.org>");
MODULE_DESCRIPTION("Vitesse VSC7385/7388/7395/7398 SPI driver");
MODULE_LICENSE("GPL v2");
