<शैली गुरु>
/*
 * B53 रेजिस्टर access through SPI
 *
 * Copyright (C) 2011-2013 Jonas Gorski <jogo@खोलोwrt.org>
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <यंत्र/unaligned.h>

#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/platक्रमm_data/b53.h>

#समावेश "b53_priv.h"

#घोषणा B53_SPI_DATA		0xf0

#घोषणा B53_SPI_STATUS		0xfe
#घोषणा B53_SPI_CMD_SPIF	BIT(7)
#घोषणा B53_SPI_CMD_RACK	BIT(5)

#घोषणा B53_SPI_CMD_READ	0x00
#घोषणा B53_SPI_CMD_WRITE	0x01
#घोषणा B53_SPI_CMD_NORMAL	0x60
#घोषणा B53_SPI_CMD_FAST	0x10

#घोषणा B53_SPI_PAGE_SELECT	0xff

अटल अंतरभूत पूर्णांक b53_spi_पढ़ो_reg(काष्ठा spi_device *spi, u8 reg, u8 *val,
				   अचिन्हित पूर्णांक len)
अणु
	u8 txbuf[2];

	txbuf[0] = B53_SPI_CMD_NORMAL | B53_SPI_CMD_READ;
	txbuf[1] = reg;

	वापस spi_ग_लिखो_then_पढ़ो(spi, txbuf, 2, val, len);
पूर्ण

अटल अंतरभूत पूर्णांक b53_spi_clear_status(काष्ठा spi_device *spi)
अणु
	अचिन्हित पूर्णांक i;
	u8 rxbuf;
	पूर्णांक ret;

	क्रम (i = 0; i < 10; i++) अणु
		ret = b53_spi_पढ़ो_reg(spi, B53_SPI_STATUS, &rxbuf, 1);
		अगर (ret)
			वापस ret;

		अगर (!(rxbuf & B53_SPI_CMD_SPIF))
			अवरोध;

		mdelay(1);
	पूर्ण

	अगर (i == 10)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक b53_spi_set_page(काष्ठा spi_device *spi, u8 page)
अणु
	u8 txbuf[3];

	txbuf[0] = B53_SPI_CMD_NORMAL | B53_SPI_CMD_WRITE;
	txbuf[1] = B53_SPI_PAGE_SELECT;
	txbuf[2] = page;

	वापस spi_ग_लिखो(spi, txbuf, माप(txbuf));
पूर्ण

अटल अंतरभूत पूर्णांक b53_prepare_reg_access(काष्ठा spi_device *spi, u8 page)
अणु
	पूर्णांक ret = b53_spi_clear_status(spi);

	अगर (ret)
		वापस ret;

	वापस b53_spi_set_page(spi, page);
पूर्ण

अटल पूर्णांक b53_spi_prepare_reg_पढ़ो(काष्ठा spi_device *spi, u8 reg)
अणु
	u8 rxbuf;
	पूर्णांक retry_count;
	पूर्णांक ret;

	ret = b53_spi_पढ़ो_reg(spi, reg, &rxbuf, 1);
	अगर (ret)
		वापस ret;

	क्रम (retry_count = 0; retry_count < 10; retry_count++) अणु
		ret = b53_spi_पढ़ो_reg(spi, B53_SPI_STATUS, &rxbuf, 1);
		अगर (ret)
			वापस ret;

		अगर (rxbuf & B53_SPI_CMD_RACK)
			अवरोध;

		mdelay(1);
	पूर्ण

	अगर (retry_count == 10)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक b53_spi_पढ़ो(काष्ठा b53_device *dev, u8 page, u8 reg, u8 *data,
			अचिन्हित पूर्णांक len)
अणु
	काष्ठा spi_device *spi = dev->priv;
	पूर्णांक ret;

	ret = b53_prepare_reg_access(spi, page);
	अगर (ret)
		वापस ret;

	ret = b53_spi_prepare_reg_पढ़ो(spi, reg);
	अगर (ret)
		वापस ret;

	वापस b53_spi_पढ़ो_reg(spi, B53_SPI_DATA, data, len);
पूर्ण

अटल पूर्णांक b53_spi_पढ़ो8(काष्ठा b53_device *dev, u8 page, u8 reg, u8 *val)
अणु
	वापस b53_spi_पढ़ो(dev, page, reg, val, 1);
पूर्ण

अटल पूर्णांक b53_spi_पढ़ो16(काष्ठा b53_device *dev, u8 page, u8 reg, u16 *val)
अणु
	__le16 value;
	पूर्णांक ret;

	ret = b53_spi_पढ़ो(dev, page, reg, (u8 *)&value, 2);

	अगर (!ret)
		*val = le16_to_cpu(value);

	वापस ret;
पूर्ण

अटल पूर्णांक b53_spi_पढ़ो32(काष्ठा b53_device *dev, u8 page, u8 reg, u32 *val)
अणु
	__le32 value;
	पूर्णांक ret;

	ret = b53_spi_पढ़ो(dev, page, reg, (u8 *)&value, 4);

	अगर (!ret)
		*val = le32_to_cpu(value);

	वापस ret;
पूर्ण

अटल पूर्णांक b53_spi_पढ़ो48(काष्ठा b53_device *dev, u8 page, u8 reg, u64 *val)
अणु
	__le64 value;
	पूर्णांक ret;

	*val = 0;
	ret = b53_spi_पढ़ो(dev, page, reg, (u8 *)&value, 6);
	अगर (!ret)
		*val = le64_to_cpu(value);

	वापस ret;
पूर्ण

अटल पूर्णांक b53_spi_पढ़ो64(काष्ठा b53_device *dev, u8 page, u8 reg, u64 *val)
अणु
	__le64 value;
	पूर्णांक ret;

	ret = b53_spi_पढ़ो(dev, page, reg, (u8 *)&value, 8);

	अगर (!ret)
		*val = le64_to_cpu(value);

	वापस ret;
पूर्ण

अटल पूर्णांक b53_spi_ग_लिखो8(काष्ठा b53_device *dev, u8 page, u8 reg, u8 value)
अणु
	काष्ठा spi_device *spi = dev->priv;
	पूर्णांक ret;
	u8 txbuf[3];

	ret = b53_prepare_reg_access(spi, page);
	अगर (ret)
		वापस ret;

	txbuf[0] = B53_SPI_CMD_NORMAL | B53_SPI_CMD_WRITE;
	txbuf[1] = reg;
	txbuf[2] = value;

	वापस spi_ग_लिखो(spi, txbuf, माप(txbuf));
पूर्ण

अटल पूर्णांक b53_spi_ग_लिखो16(काष्ठा b53_device *dev, u8 page, u8 reg, u16 value)
अणु
	काष्ठा spi_device *spi = dev->priv;
	पूर्णांक ret;
	u8 txbuf[4];

	ret = b53_prepare_reg_access(spi, page);
	अगर (ret)
		वापस ret;

	txbuf[0] = B53_SPI_CMD_NORMAL | B53_SPI_CMD_WRITE;
	txbuf[1] = reg;
	put_unaligned_le16(value, &txbuf[2]);

	वापस spi_ग_लिखो(spi, txbuf, माप(txbuf));
पूर्ण

अटल पूर्णांक b53_spi_ग_लिखो32(काष्ठा b53_device *dev, u8 page, u8 reg, u32 value)
अणु
	काष्ठा spi_device *spi = dev->priv;
	पूर्णांक ret;
	u8 txbuf[6];

	ret = b53_prepare_reg_access(spi, page);
	अगर (ret)
		वापस ret;

	txbuf[0] = B53_SPI_CMD_NORMAL | B53_SPI_CMD_WRITE;
	txbuf[1] = reg;
	put_unaligned_le32(value, &txbuf[2]);

	वापस spi_ग_लिखो(spi, txbuf, माप(txbuf));
पूर्ण

अटल पूर्णांक b53_spi_ग_लिखो48(काष्ठा b53_device *dev, u8 page, u8 reg, u64 value)
अणु
	काष्ठा spi_device *spi = dev->priv;
	पूर्णांक ret;
	u8 txbuf[10];

	ret = b53_prepare_reg_access(spi, page);
	अगर (ret)
		वापस ret;

	txbuf[0] = B53_SPI_CMD_NORMAL | B53_SPI_CMD_WRITE;
	txbuf[1] = reg;
	put_unaligned_le64(value, &txbuf[2]);

	वापस spi_ग_लिखो(spi, txbuf, माप(txbuf) - 2);
पूर्ण

अटल पूर्णांक b53_spi_ग_लिखो64(काष्ठा b53_device *dev, u8 page, u8 reg, u64 value)
अणु
	काष्ठा spi_device *spi = dev->priv;
	पूर्णांक ret;
	u8 txbuf[10];

	ret = b53_prepare_reg_access(spi, page);
	अगर (ret)
		वापस ret;

	txbuf[0] = B53_SPI_CMD_NORMAL | B53_SPI_CMD_WRITE;
	txbuf[1] = reg;
	put_unaligned_le64(value, &txbuf[2]);

	वापस spi_ग_लिखो(spi, txbuf, माप(txbuf));
पूर्ण

अटल स्थिर काष्ठा b53_io_ops b53_spi_ops = अणु
	.पढ़ो8 = b53_spi_पढ़ो8,
	.पढ़ो16 = b53_spi_पढ़ो16,
	.पढ़ो32 = b53_spi_पढ़ो32,
	.पढ़ो48 = b53_spi_पढ़ो48,
	.पढ़ो64 = b53_spi_पढ़ो64,
	.ग_लिखो8 = b53_spi_ग_लिखो8,
	.ग_लिखो16 = b53_spi_ग_लिखो16,
	.ग_लिखो32 = b53_spi_ग_लिखो32,
	.ग_लिखो48 = b53_spi_ग_लिखो48,
	.ग_लिखो64 = b53_spi_ग_लिखो64,
पूर्ण;

अटल पूर्णांक b53_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा b53_device *dev;
	पूर्णांक ret;

	dev = b53_चयन_alloc(&spi->dev, &b53_spi_ops, spi);
	अगर (!dev)
		वापस -ENOMEM;

	अगर (spi->dev.platक्रमm_data)
		dev->pdata = spi->dev.platक्रमm_data;

	ret = b53_चयन_रेजिस्टर(dev);
	अगर (ret)
		वापस ret;

	spi_set_drvdata(spi, dev);

	वापस 0;
पूर्ण

अटल पूर्णांक b53_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा b53_device *dev = spi_get_drvdata(spi);

	अगर (dev)
		b53_चयन_हटाओ(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id b53_spi_of_match[] = अणु
	अणु .compatible = "brcm,bcm5325" पूर्ण,
	अणु .compatible = "brcm,bcm5365" पूर्ण,
	अणु .compatible = "brcm,bcm5395" पूर्ण,
	अणु .compatible = "brcm,bcm5397" पूर्ण,
	अणु .compatible = "brcm,bcm5398" पूर्ण,
	अणु .compatible = "brcm,bcm53115" पूर्ण,
	अणु .compatible = "brcm,bcm53125" पूर्ण,
	अणु .compatible = "brcm,bcm53128" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, b53_spi_of_match);

अटल काष्ठा spi_driver b53_spi_driver = अणु
	.driver = अणु
		.name	= "b53-switch",
		.of_match_table = b53_spi_of_match,
	पूर्ण,
	.probe	= b53_spi_probe,
	.हटाओ	= b53_spi_हटाओ,
पूर्ण;

module_spi_driver(b53_spi_driver);

MODULE_AUTHOR("Jonas Gorski <jogo@openwrt.org>");
MODULE_DESCRIPTION("B53 SPI access driver");
MODULE_LICENSE("Dual BSD/GPL");
