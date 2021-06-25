<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Ethernet driver क्रम the WIZnet W5100/W5200/W5500 chip.
 *
 * Copyright (C) 2016 Akinobu Mita <akinobu.mita@gmail.com>
 *
 * Datasheet:
 * http://www.wiznet.co.kr/wp-content/uploads/wiznethome/Chip/W5100/Document/W5100_Datasheet_v1.2.6.pdf
 * http://wiznethome.cafe24.com/wp-content/uploads/wiznethome/Chip/W5200/Documents/W5200_DS_V140E.pdf
 * http://wizwiki.net/wiki/lib/exe/fetch.php?media=products:w5500:w5500_ds_v106e_141230.pdf
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of_net.h>
#समावेश <linux/of_device.h>
#समावेश <linux/spi/spi.h>

#समावेश "w5100.h"

#घोषणा W5100_SPI_WRITE_OPCODE 0xf0
#घोषणा W5100_SPI_READ_OPCODE 0x0f

अटल पूर्णांक w5100_spi_पढ़ो(काष्ठा net_device *ndev, u32 addr)
अणु
	काष्ठा spi_device *spi = to_spi_device(ndev->dev.parent);
	u8 cmd[3] = अणु W5100_SPI_READ_OPCODE, addr >> 8, addr & 0xff पूर्ण;
	u8 data;
	पूर्णांक ret;

	ret = spi_ग_लिखो_then_पढ़ो(spi, cmd, माप(cmd), &data, 1);

	वापस ret ? ret : data;
पूर्ण

अटल पूर्णांक w5100_spi_ग_लिखो(काष्ठा net_device *ndev, u32 addr, u8 data)
अणु
	काष्ठा spi_device *spi = to_spi_device(ndev->dev.parent);
	u8 cmd[4] = अणु W5100_SPI_WRITE_OPCODE, addr >> 8, addr & 0xff, dataपूर्ण;

	वापस spi_ग_लिखो_then_पढ़ो(spi, cmd, माप(cmd), शून्य, 0);
पूर्ण

अटल पूर्णांक w5100_spi_पढ़ो16(काष्ठा net_device *ndev, u32 addr)
अणु
	u16 data;
	पूर्णांक ret;

	ret = w5100_spi_पढ़ो(ndev, addr);
	अगर (ret < 0)
		वापस ret;
	data = ret << 8;
	ret = w5100_spi_पढ़ो(ndev, addr + 1);

	वापस ret < 0 ? ret : data | ret;
पूर्ण

अटल पूर्णांक w5100_spi_ग_लिखो16(काष्ठा net_device *ndev, u32 addr, u16 data)
अणु
	पूर्णांक ret;

	ret = w5100_spi_ग_लिखो(ndev, addr, data >> 8);
	अगर (ret)
		वापस ret;

	वापस w5100_spi_ग_लिखो(ndev, addr + 1, data & 0xff);
पूर्ण

अटल पूर्णांक w5100_spi_पढ़ोbulk(काष्ठा net_device *ndev, u32 addr, u8 *buf,
			      पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		पूर्णांक ret = w5100_spi_पढ़ो(ndev, addr + i);

		अगर (ret < 0)
			वापस ret;
		buf[i] = ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक w5100_spi_ग_लिखोbulk(काष्ठा net_device *ndev, u32 addr, स्थिर u8 *buf,
			       पूर्णांक len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++) अणु
		पूर्णांक ret = w5100_spi_ग_लिखो(ndev, addr + i, buf[i]);

		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा w5100_ops w5100_spi_ops = अणु
	.may_sleep = true,
	.chip_id = W5100,
	.पढ़ो = w5100_spi_पढ़ो,
	.ग_लिखो = w5100_spi_ग_लिखो,
	.पढ़ो16 = w5100_spi_पढ़ो16,
	.ग_लिखो16 = w5100_spi_ग_लिखो16,
	.पढ़ोbulk = w5100_spi_पढ़ोbulk,
	.ग_लिखोbulk = w5100_spi_ग_लिखोbulk,
पूर्ण;

#घोषणा W5200_SPI_WRITE_OPCODE 0x80

काष्ठा w5200_spi_priv अणु
	/* Serialize access to cmd_buf */
	काष्ठा mutex cmd_lock;

	/* DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	u8 cmd_buf[4] ____cacheline_aligned;
पूर्ण;

अटल काष्ठा w5200_spi_priv *w5200_spi_priv(काष्ठा net_device *ndev)
अणु
	वापस w5100_ops_priv(ndev);
पूर्ण

अटल पूर्णांक w5200_spi_init(काष्ठा net_device *ndev)
अणु
	काष्ठा w5200_spi_priv *spi_priv = w5200_spi_priv(ndev);

	mutex_init(&spi_priv->cmd_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक w5200_spi_पढ़ो(काष्ठा net_device *ndev, u32 addr)
अणु
	काष्ठा spi_device *spi = to_spi_device(ndev->dev.parent);
	u8 cmd[4] = अणु addr >> 8, addr & 0xff, 0, 1 पूर्ण;
	u8 data;
	पूर्णांक ret;

	ret = spi_ग_लिखो_then_पढ़ो(spi, cmd, माप(cmd), &data, 1);

	वापस ret ? ret : data;
पूर्ण

अटल पूर्णांक w5200_spi_ग_लिखो(काष्ठा net_device *ndev, u32 addr, u8 data)
अणु
	काष्ठा spi_device *spi = to_spi_device(ndev->dev.parent);
	u8 cmd[5] = अणु addr >> 8, addr & 0xff, W5200_SPI_WRITE_OPCODE, 1, data पूर्ण;

	वापस spi_ग_लिखो_then_पढ़ो(spi, cmd, माप(cmd), शून्य, 0);
पूर्ण

अटल पूर्णांक w5200_spi_पढ़ो16(काष्ठा net_device *ndev, u32 addr)
अणु
	काष्ठा spi_device *spi = to_spi_device(ndev->dev.parent);
	u8 cmd[4] = अणु addr >> 8, addr & 0xff, 0, 2 पूर्ण;
	__be16 data;
	पूर्णांक ret;

	ret = spi_ग_लिखो_then_पढ़ो(spi, cmd, माप(cmd), &data, माप(data));

	वापस ret ? ret : be16_to_cpu(data);
पूर्ण

अटल पूर्णांक w5200_spi_ग_लिखो16(काष्ठा net_device *ndev, u32 addr, u16 data)
अणु
	काष्ठा spi_device *spi = to_spi_device(ndev->dev.parent);
	u8 cmd[6] = अणु
		addr >> 8, addr & 0xff,
		W5200_SPI_WRITE_OPCODE, 2,
		data >> 8, data & 0xff
	पूर्ण;

	वापस spi_ग_लिखो_then_पढ़ो(spi, cmd, माप(cmd), शून्य, 0);
पूर्ण

अटल पूर्णांक w5200_spi_पढ़ोbulk(काष्ठा net_device *ndev, u32 addr, u8 *buf,
			      पूर्णांक len)
अणु
	काष्ठा spi_device *spi = to_spi_device(ndev->dev.parent);
	काष्ठा w5200_spi_priv *spi_priv = w5200_spi_priv(ndev);
	काष्ठा spi_transfer xfer[] = अणु
		अणु
			.tx_buf = spi_priv->cmd_buf,
			.len = माप(spi_priv->cmd_buf),
		पूर्ण,
		अणु
			.rx_buf = buf,
			.len = len,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	mutex_lock(&spi_priv->cmd_lock);

	spi_priv->cmd_buf[0] = addr >> 8;
	spi_priv->cmd_buf[1] = addr;
	spi_priv->cmd_buf[2] = len >> 8;
	spi_priv->cmd_buf[3] = len;
	ret = spi_sync_transfer(spi, xfer, ARRAY_SIZE(xfer));

	mutex_unlock(&spi_priv->cmd_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक w5200_spi_ग_लिखोbulk(काष्ठा net_device *ndev, u32 addr, स्थिर u8 *buf,
			       पूर्णांक len)
अणु
	काष्ठा spi_device *spi = to_spi_device(ndev->dev.parent);
	काष्ठा w5200_spi_priv *spi_priv = w5200_spi_priv(ndev);
	काष्ठा spi_transfer xfer[] = अणु
		अणु
			.tx_buf = spi_priv->cmd_buf,
			.len = माप(spi_priv->cmd_buf),
		पूर्ण,
		अणु
			.tx_buf = buf,
			.len = len,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	mutex_lock(&spi_priv->cmd_lock);

	spi_priv->cmd_buf[0] = addr >> 8;
	spi_priv->cmd_buf[1] = addr;
	spi_priv->cmd_buf[2] = W5200_SPI_WRITE_OPCODE | (len >> 8);
	spi_priv->cmd_buf[3] = len;
	ret = spi_sync_transfer(spi, xfer, ARRAY_SIZE(xfer));

	mutex_unlock(&spi_priv->cmd_lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा w5100_ops w5200_ops = अणु
	.may_sleep = true,
	.chip_id = W5200,
	.पढ़ो = w5200_spi_पढ़ो,
	.ग_लिखो = w5200_spi_ग_लिखो,
	.पढ़ो16 = w5200_spi_पढ़ो16,
	.ग_लिखो16 = w5200_spi_ग_लिखो16,
	.पढ़ोbulk = w5200_spi_पढ़ोbulk,
	.ग_लिखोbulk = w5200_spi_ग_लिखोbulk,
	.init = w5200_spi_init,
पूर्ण;

#घोषणा W5500_SPI_BLOCK_SELECT(addr) (((addr) >> 16) & 0x1f)
#घोषणा W5500_SPI_READ_CONTROL(addr) (W5500_SPI_BLOCK_SELECT(addr) << 3)
#घोषणा W5500_SPI_WRITE_CONTROL(addr)	\
	((W5500_SPI_BLOCK_SELECT(addr) << 3) | BIT(2))

काष्ठा w5500_spi_priv अणु
	/* Serialize access to cmd_buf */
	काष्ठा mutex cmd_lock;

	/* DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	u8 cmd_buf[3] ____cacheline_aligned;
पूर्ण;

अटल काष्ठा w5500_spi_priv *w5500_spi_priv(काष्ठा net_device *ndev)
अणु
	वापस w5100_ops_priv(ndev);
पूर्ण

अटल पूर्णांक w5500_spi_init(काष्ठा net_device *ndev)
अणु
	काष्ठा w5500_spi_priv *spi_priv = w5500_spi_priv(ndev);

	mutex_init(&spi_priv->cmd_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक w5500_spi_पढ़ो(काष्ठा net_device *ndev, u32 addr)
अणु
	काष्ठा spi_device *spi = to_spi_device(ndev->dev.parent);
	u8 cmd[3] = अणु
		addr >> 8,
		addr,
		W5500_SPI_READ_CONTROL(addr)
	पूर्ण;
	u8 data;
	पूर्णांक ret;

	ret = spi_ग_लिखो_then_पढ़ो(spi, cmd, माप(cmd), &data, 1);

	वापस ret ? ret : data;
पूर्ण

अटल पूर्णांक w5500_spi_ग_लिखो(काष्ठा net_device *ndev, u32 addr, u8 data)
अणु
	काष्ठा spi_device *spi = to_spi_device(ndev->dev.parent);
	u8 cmd[4] = अणु
		addr >> 8,
		addr,
		W5500_SPI_WRITE_CONTROL(addr),
		data
	पूर्ण;

	वापस spi_ग_लिखो_then_पढ़ो(spi, cmd, माप(cmd), शून्य, 0);
पूर्ण

अटल पूर्णांक w5500_spi_पढ़ो16(काष्ठा net_device *ndev, u32 addr)
अणु
	काष्ठा spi_device *spi = to_spi_device(ndev->dev.parent);
	u8 cmd[3] = अणु
		addr >> 8,
		addr,
		W5500_SPI_READ_CONTROL(addr)
	पूर्ण;
	__be16 data;
	पूर्णांक ret;

	ret = spi_ग_लिखो_then_पढ़ो(spi, cmd, माप(cmd), &data, माप(data));

	वापस ret ? ret : be16_to_cpu(data);
पूर्ण

अटल पूर्णांक w5500_spi_ग_लिखो16(काष्ठा net_device *ndev, u32 addr, u16 data)
अणु
	काष्ठा spi_device *spi = to_spi_device(ndev->dev.parent);
	u8 cmd[5] = अणु
		addr >> 8,
		addr,
		W5500_SPI_WRITE_CONTROL(addr),
		data >> 8,
		data
	पूर्ण;

	वापस spi_ग_लिखो_then_पढ़ो(spi, cmd, माप(cmd), शून्य, 0);
पूर्ण

अटल पूर्णांक w5500_spi_पढ़ोbulk(काष्ठा net_device *ndev, u32 addr, u8 *buf,
			      पूर्णांक len)
अणु
	काष्ठा spi_device *spi = to_spi_device(ndev->dev.parent);
	काष्ठा w5500_spi_priv *spi_priv = w5500_spi_priv(ndev);
	काष्ठा spi_transfer xfer[] = अणु
		अणु
			.tx_buf = spi_priv->cmd_buf,
			.len = माप(spi_priv->cmd_buf),
		पूर्ण,
		अणु
			.rx_buf = buf,
			.len = len,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	mutex_lock(&spi_priv->cmd_lock);

	spi_priv->cmd_buf[0] = addr >> 8;
	spi_priv->cmd_buf[1] = addr;
	spi_priv->cmd_buf[2] = W5500_SPI_READ_CONTROL(addr);
	ret = spi_sync_transfer(spi, xfer, ARRAY_SIZE(xfer));

	mutex_unlock(&spi_priv->cmd_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक w5500_spi_ग_लिखोbulk(काष्ठा net_device *ndev, u32 addr, स्थिर u8 *buf,
			       पूर्णांक len)
अणु
	काष्ठा spi_device *spi = to_spi_device(ndev->dev.parent);
	काष्ठा w5500_spi_priv *spi_priv = w5500_spi_priv(ndev);
	काष्ठा spi_transfer xfer[] = अणु
		अणु
			.tx_buf = spi_priv->cmd_buf,
			.len = माप(spi_priv->cmd_buf),
		पूर्ण,
		अणु
			.tx_buf = buf,
			.len = len,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	mutex_lock(&spi_priv->cmd_lock);

	spi_priv->cmd_buf[0] = addr >> 8;
	spi_priv->cmd_buf[1] = addr;
	spi_priv->cmd_buf[2] = W5500_SPI_WRITE_CONTROL(addr);
	ret = spi_sync_transfer(spi, xfer, ARRAY_SIZE(xfer));

	mutex_unlock(&spi_priv->cmd_lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा w5100_ops w5500_ops = अणु
	.may_sleep = true,
	.chip_id = W5500,
	.पढ़ो = w5500_spi_पढ़ो,
	.ग_लिखो = w5500_spi_ग_लिखो,
	.पढ़ो16 = w5500_spi_पढ़ो16,
	.ग_लिखो16 = w5500_spi_ग_लिखो16,
	.पढ़ोbulk = w5500_spi_पढ़ोbulk,
	.ग_लिखोbulk = w5500_spi_ग_लिखोbulk,
	.init = w5500_spi_init,
पूर्ण;

अटल स्थिर काष्ठा of_device_id w5100_of_match[] = अणु
	अणु .compatible = "wiznet,w5100", .data = (स्थिर व्योम*)W5100, पूर्ण,
	अणु .compatible = "wiznet,w5200", .data = (स्थिर व्योम*)W5200, पूर्ण,
	अणु .compatible = "wiznet,w5500", .data = (स्थिर व्योम*)W5500, पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, w5100_of_match);

अटल पूर्णांक w5100_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा of_device_id *of_id;
	स्थिर काष्ठा w5100_ops *ops;
	kernel_uदीर्घ_t driver_data;
	स्थिर व्योम *mac = शून्य;
	u8 पंचांगpmac[ETH_ALEN];
	पूर्णांक priv_size;
	पूर्णांक ret;

	ret = of_get_mac_address(spi->dev.of_node, पंचांगpmac);
	अगर (!ret)
		mac = पंचांगpmac;

	अगर (spi->dev.of_node) अणु
		of_id = of_match_device(w5100_of_match, &spi->dev);
		अगर (!of_id)
			वापस -ENODEV;
		driver_data = (kernel_uदीर्घ_t)of_id->data;
	पूर्ण अन्यथा अणु
		driver_data = spi_get_device_id(spi)->driver_data;
	पूर्ण

	चयन (driver_data) अणु
	हाल W5100:
		ops = &w5100_spi_ops;
		priv_size = 0;
		अवरोध;
	हाल W5200:
		ops = &w5200_ops;
		priv_size = माप(काष्ठा w5200_spi_priv);
		अवरोध;
	हाल W5500:
		ops = &w5500_ops;
		priv_size = माप(काष्ठा w5500_spi_priv);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस w5100_probe(&spi->dev, ops, priv_size, mac, spi->irq, -EINVAL);
पूर्ण

अटल पूर्णांक w5100_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस w5100_हटाओ(&spi->dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id w5100_spi_ids[] = अणु
	अणु "w5100", W5100 पूर्ण,
	अणु "w5200", W5200 पूर्ण,
	अणु "w5500", W5500 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, w5100_spi_ids);

अटल काष्ठा spi_driver w5100_spi_driver = अणु
	.driver		= अणु
		.name	= "w5100",
		.pm	= &w5100_pm_ops,
		.of_match_table = w5100_of_match,
	पूर्ण,
	.probe		= w5100_spi_probe,
	.हटाओ		= w5100_spi_हटाओ,
	.id_table	= w5100_spi_ids,
पूर्ण;
module_spi_driver(w5100_spi_driver);

MODULE_DESCRIPTION("WIZnet W5100/W5200/W5500 Ethernet driver for SPI mode");
MODULE_AUTHOR("Akinobu Mita <akinobu.mita@gmail.com>");
MODULE_LICENSE("GPL");
