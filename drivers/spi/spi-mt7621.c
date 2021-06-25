<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// spi-mt7621.c -- MediaTek MT7621 SPI controller driver
//
// Copyright (C) 2011 Sergiy <piratfm@gmail.com>
// Copyright (C) 2011-2013 Gabor Juhos <juhosg@खोलोwrt.org>
// Copyright (C) 2014-2015 Felix Fietkau <nbd@nbd.name>
//
// Some parts are based on spi-orion.c:
//   Author: Shadi Ammouri <shadi@marvell.com>
//   Copyright (C) 2007-2008 Marvell Ltd.

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/spi/spi.h>

#घोषणा DRIVER_NAME		"spi-mt7621"

/* in usec */
#घोषणा RALINK_SPI_WAIT_MAX_LOOP 2000

/* SPISTAT रेजिस्टर bit field */
#घोषणा SPISTAT_BUSY		BIT(0)

#घोषणा MT7621_SPI_TRANS	0x00
#घोषणा SPITRANS_BUSY		BIT(16)

#घोषणा MT7621_SPI_OPCODE	0x04
#घोषणा MT7621_SPI_DATA0	0x08
#घोषणा MT7621_SPI_DATA4	0x18
#घोषणा SPI_CTL_TX_RX_CNT_MASK	0xff
#घोषणा SPI_CTL_START		BIT(8)

#घोषणा MT7621_SPI_MASTER	0x28
#घोषणा MASTER_MORE_BUFMODE	BIT(2)
#घोषणा MASTER_FULL_DUPLEX	BIT(10)
#घोषणा MASTER_RS_CLK_SEL	GENMASK(27, 16)
#घोषणा MASTER_RS_CLK_SEL_SHIFT	16
#घोषणा MASTER_RS_SLAVE_SEL	GENMASK(31, 29)

#घोषणा MT7621_SPI_MOREBUF	0x2c
#घोषणा MT7621_SPI_POLAR	0x38
#घोषणा MT7621_SPI_SPACE	0x3c

#घोषणा MT7621_CPHA		BIT(5)
#घोषणा MT7621_CPOL		BIT(4)
#घोषणा MT7621_LSB_FIRST	BIT(3)

काष्ठा mt7621_spi अणु
	काष्ठा spi_controller	*master;
	व्योम __iomem		*base;
	अचिन्हित पूर्णांक		sys_freq;
	अचिन्हित पूर्णांक		speed;
	काष्ठा clk		*clk;
	पूर्णांक			pending_ग_लिखो;
पूर्ण;

अटल अंतरभूत काष्ठा mt7621_spi *spidev_to_mt7621_spi(काष्ठा spi_device *spi)
अणु
	वापस spi_controller_get_devdata(spi->master);
पूर्ण

अटल अंतरभूत u32 mt7621_spi_पढ़ो(काष्ठा mt7621_spi *rs, u32 reg)
अणु
	वापस ioपढ़ो32(rs->base + reg);
पूर्ण

अटल अंतरभूत व्योम mt7621_spi_ग_लिखो(काष्ठा mt7621_spi *rs, u32 reg, u32 val)
अणु
	ioग_लिखो32(val, rs->base + reg);
पूर्ण

अटल व्योम mt7621_spi_set_cs(काष्ठा spi_device *spi, पूर्णांक enable)
अणु
	काष्ठा mt7621_spi *rs = spidev_to_mt7621_spi(spi);
	पूर्णांक cs = spi->chip_select;
	u32 polar = 0;
	u32 master;

	/*
	 * Select SPI device 7, enable "more buffer mode" and disable
	 * full-duplex (only half-duplex really works on this chip
	 * reliably)
	 */
	master = mt7621_spi_पढ़ो(rs, MT7621_SPI_MASTER);
	master |= MASTER_RS_SLAVE_SEL | MASTER_MORE_BUFMODE;
	master &= ~MASTER_FULL_DUPLEX;
	mt7621_spi_ग_लिखो(rs, MT7621_SPI_MASTER, master);

	rs->pending_ग_लिखो = 0;

	अगर (enable)
		polar = BIT(cs);
	mt7621_spi_ग_लिखो(rs, MT7621_SPI_POLAR, polar);
पूर्ण

अटल पूर्णांक mt7621_spi_prepare(काष्ठा spi_device *spi, अचिन्हित पूर्णांक speed)
अणु
	काष्ठा mt7621_spi *rs = spidev_to_mt7621_spi(spi);
	u32 rate;
	u32 reg;

	dev_dbg(&spi->dev, "speed:%u\n", speed);

	rate = DIV_ROUND_UP(rs->sys_freq, speed);
	dev_dbg(&spi->dev, "rate-1:%u\n", rate);

	अगर (rate > 4097)
		वापस -EINVAL;

	अगर (rate < 2)
		rate = 2;

	reg = mt7621_spi_पढ़ो(rs, MT7621_SPI_MASTER);
	reg &= ~MASTER_RS_CLK_SEL;
	reg |= (rate - 2) << MASTER_RS_CLK_SEL_SHIFT;
	rs->speed = speed;

	reg &= ~MT7621_LSB_FIRST;
	अगर (spi->mode & SPI_LSB_FIRST)
		reg |= MT7621_LSB_FIRST;

	/*
	 * This SPI controller seems to be tested on SPI flash only and some
	 * bits are swizzled under other SPI modes probably due to incorrect
	 * wiring inside the silicon. Only mode 0 works correctly.
	 */
	reg &= ~(MT7621_CPHA | MT7621_CPOL);

	mt7621_spi_ग_लिखो(rs, MT7621_SPI_MASTER, reg);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक mt7621_spi_रुको_till_पढ़ोy(काष्ठा mt7621_spi *rs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RALINK_SPI_WAIT_MAX_LOOP; i++) अणु
		u32 status;

		status = mt7621_spi_पढ़ो(rs, MT7621_SPI_TRANS);
		अगर ((status & SPITRANS_BUSY) == 0)
			वापस 0;
		cpu_relax();
		udelay(1);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम mt7621_spi_पढ़ो_half_duplex(काष्ठा mt7621_spi *rs,
					पूर्णांक rx_len, u8 *buf)
अणु
	पूर्णांक tx_len;

	/*
	 * Combine with any pending ग_लिखो, and perक्रमm one or more half-duplex
	 * transactions पढ़ोing 'len' bytes. Data to be written is alपढ़ोy in
	 * MT7621_SPI_DATA.
	 */
	tx_len = rs->pending_ग_लिखो;
	rs->pending_ग_लिखो = 0;

	जबतक (rx_len || tx_len) अणु
		पूर्णांक i;
		u32 val = (min(tx_len, 4) * 8) << 24;
		पूर्णांक rx = min(rx_len, 32);

		अगर (tx_len > 4)
			val |= (tx_len - 4) * 8;
		val |= (rx * 8) << 12;
		mt7621_spi_ग_लिखो(rs, MT7621_SPI_MOREBUF, val);

		tx_len = 0;

		val = mt7621_spi_पढ़ो(rs, MT7621_SPI_TRANS);
		val |= SPI_CTL_START;
		mt7621_spi_ग_लिखो(rs, MT7621_SPI_TRANS, val);

		mt7621_spi_रुको_till_पढ़ोy(rs);

		क्रम (i = 0; i < rx; i++) अणु
			अगर ((i % 4) == 0)
				val = mt7621_spi_पढ़ो(rs, MT7621_SPI_DATA0 + i);
			*buf++ = val & 0xff;
			val >>= 8;
		पूर्ण

		rx_len -= i;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम mt7621_spi_flush(काष्ठा mt7621_spi *rs)
अणु
	mt7621_spi_पढ़ो_half_duplex(rs, 0, शून्य);
पूर्ण

अटल व्योम mt7621_spi_ग_लिखो_half_duplex(काष्ठा mt7621_spi *rs,
					 पूर्णांक tx_len, स्थिर u8 *buf)
अणु
	पूर्णांक len = rs->pending_ग_लिखो;
	पूर्णांक val = 0;

	अगर (len & 3) अणु
		val = mt7621_spi_पढ़ो(rs, MT7621_SPI_OPCODE + (len & ~3));
		अगर (len < 4) अणु
			val <<= (4 - len) * 8;
			val = swab32(val);
		पूर्ण
	पूर्ण

	जबतक (tx_len > 0) अणु
		अगर (len >= 36) अणु
			rs->pending_ग_लिखो = len;
			mt7621_spi_flush(rs);
			len = 0;
		पूर्ण

		val |= *buf++ << (8 * (len & 3));
		len++;
		अगर ((len & 3) == 0) अणु
			अगर (len == 4)
				/* The byte-order of the opcode is weird! */
				val = swab32(val);
			mt7621_spi_ग_लिखो(rs, MT7621_SPI_OPCODE + len - 4, val);
			val = 0;
		पूर्ण
		tx_len -= 1;
	पूर्ण

	अगर (len & 3) अणु
		अगर (len < 4) अणु
			val = swab32(val);
			val >>= (4 - len) * 8;
		पूर्ण
		mt7621_spi_ग_लिखो(rs, MT7621_SPI_OPCODE + (len & ~3), val);
	पूर्ण

	rs->pending_ग_लिखो = len;
पूर्ण

अटल पूर्णांक mt7621_spi_transfer_one_message(काष्ठा spi_controller *master,
					   काष्ठा spi_message *m)
अणु
	काष्ठा mt7621_spi *rs = spi_controller_get_devdata(master);
	काष्ठा spi_device *spi = m->spi;
	अचिन्हित पूर्णांक speed = spi->max_speed_hz;
	काष्ठा spi_transfer *t = शून्य;
	पूर्णांक status = 0;

	mt7621_spi_रुको_till_पढ़ोy(rs);

	list_क्रम_each_entry(t, &m->transfers, transfer_list)
		अगर (t->speed_hz < speed)
			speed = t->speed_hz;

	अगर (mt7621_spi_prepare(spi, speed)) अणु
		status = -EIO;
		जाओ msg_करोne;
	पूर्ण

	/* Assert CS */
	mt7621_spi_set_cs(spi, 1);

	m->actual_length = 0;
	list_क्रम_each_entry(t, &m->transfers, transfer_list) अणु
		अगर ((t->rx_buf) && (t->tx_buf)) अणु
			/*
			 * This controller will shअगरt some extra data out
			 * of spi_opcode अगर (mosi_bit_cnt > 0) &&
			 * (cmd_bit_cnt == 0). So the claimed full-duplex
			 * support is broken since we have no way to पढ़ो
			 * the MISO value during that bit.
			 */
			status = -EIO;
			जाओ msg_करोne;
		पूर्ण अन्यथा अगर (t->rx_buf) अणु
			mt7621_spi_पढ़ो_half_duplex(rs, t->len, t->rx_buf);
		पूर्ण अन्यथा अगर (t->tx_buf) अणु
			mt7621_spi_ग_लिखो_half_duplex(rs, t->len, t->tx_buf);
		पूर्ण
		m->actual_length += t->len;
	पूर्ण

	/* Flush data and deनिश्चित CS */
	mt7621_spi_flush(rs);
	mt7621_spi_set_cs(spi, 0);

msg_करोne:
	m->status = status;
	spi_finalize_current_message(master);

	वापस 0;
पूर्ण

अटल पूर्णांक mt7621_spi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा mt7621_spi *rs = spidev_to_mt7621_spi(spi);

	अगर ((spi->max_speed_hz == 0) ||
	    (spi->max_speed_hz > (rs->sys_freq / 2)))
		spi->max_speed_hz = rs->sys_freq / 2;

	अगर (spi->max_speed_hz < (rs->sys_freq / 4097)) अणु
		dev_err(&spi->dev, "setup: requested speed is too low %d Hz\n",
			spi->max_speed_hz);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id mt7621_spi_match[] = अणु
	अणु .compatible = "ralink,mt7621-spi" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mt7621_spi_match);

अटल पूर्णांक mt7621_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा spi_controller *master;
	काष्ठा mt7621_spi *rs;
	व्योम __iomem *base;
	पूर्णांक status = 0;
	काष्ठा clk *clk;
	पूर्णांक ret;

	match = of_match_device(mt7621_spi_match, &pdev->dev);
	अगर (!match)
		वापस -EINVAL;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(clk)) अणु
		dev_err(&pdev->dev, "unable to get SYS clock, err=%d\n",
			status);
		वापस PTR_ERR(clk);
	पूर्ण

	status = clk_prepare_enable(clk);
	अगर (status)
		वापस status;

	master = devm_spi_alloc_master(&pdev->dev, माप(*rs));
	अगर (!master) अणु
		dev_info(&pdev->dev, "master allocation failed\n");
		clk_disable_unprepare(clk);
		वापस -ENOMEM;
	पूर्ण

	master->mode_bits = SPI_LSB_FIRST;
	master->flags = SPI_CONTROLLER_HALF_DUPLEX;
	master->setup = mt7621_spi_setup;
	master->transfer_one_message = mt7621_spi_transfer_one_message;
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	master->dev.of_node = pdev->dev.of_node;
	master->num_chipselect = 2;

	dev_set_drvdata(&pdev->dev, master);

	rs = spi_controller_get_devdata(master);
	rs->base = base;
	rs->clk = clk;
	rs->master = master;
	rs->sys_freq = clk_get_rate(rs->clk);
	rs->pending_ग_लिखो = 0;
	dev_info(&pdev->dev, "sys_freq: %u\n", rs->sys_freq);

	ret = device_reset(&pdev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "SPI reset failed!\n");
		clk_disable_unprepare(clk);
		वापस ret;
	पूर्ण

	ret = spi_रेजिस्टर_controller(master);
	अगर (ret)
		clk_disable_unprepare(clk);

	वापस ret;
पूर्ण

अटल पूर्णांक mt7621_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_controller *master;
	काष्ठा mt7621_spi *rs;

	master = dev_get_drvdata(&pdev->dev);
	rs = spi_controller_get_devdata(master);

	spi_unरेजिस्टर_controller(master);
	clk_disable_unprepare(rs->clk);

	वापस 0;
पूर्ण

MODULE_ALIAS("platform:" DRIVER_NAME);

अटल काष्ठा platक्रमm_driver mt7621_spi_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = mt7621_spi_match,
	पूर्ण,
	.probe = mt7621_spi_probe,
	.हटाओ = mt7621_spi_हटाओ,
पूर्ण;

module_platक्रमm_driver(mt7621_spi_driver);

MODULE_DESCRIPTION("MT7621 SPI driver");
MODULE_AUTHOR("Felix Fietkau <nbd@nbd.name>");
MODULE_LICENSE("GPL");
