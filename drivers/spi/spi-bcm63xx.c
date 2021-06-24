<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Broadcom BCM63xx SPI controller support
 *
 * Copyright (C) 2009-2012 Florian Fainelli <florian@खोलोwrt.org>
 * Copyright (C) 2010 Tanguy Bouzeloc <tanguy.bouzeloc@efixo.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/completion.h>
#समावेश <linux/err.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/reset.h>

/* BCM 6338/6348 SPI core */
#घोषणा SPI_6348_RSET_SIZE		64
#घोषणा SPI_6348_CMD			0x00	/* 16-bits रेजिस्टर */
#घोषणा SPI_6348_INT_STATUS		0x02
#घोषणा SPI_6348_INT_MASK_ST		0x03
#घोषणा SPI_6348_INT_MASK		0x04
#घोषणा SPI_6348_ST			0x05
#घोषणा SPI_6348_CLK_CFG		0x06
#घोषणा SPI_6348_FILL_BYTE		0x07
#घोषणा SPI_6348_MSG_TAIL		0x09
#घोषणा SPI_6348_RX_TAIL		0x0b
#घोषणा SPI_6348_MSG_CTL		0x40	/* 8-bits रेजिस्टर */
#घोषणा SPI_6348_MSG_CTL_WIDTH		8
#घोषणा SPI_6348_MSG_DATA		0x41
#घोषणा SPI_6348_MSG_DATA_SIZE		0x3f
#घोषणा SPI_6348_RX_DATA		0x80
#घोषणा SPI_6348_RX_DATA_SIZE		0x3f

/* BCM 3368/6358/6262/6368 SPI core */
#घोषणा SPI_6358_RSET_SIZE		1804
#घोषणा SPI_6358_MSG_CTL		0x00	/* 16-bits रेजिस्टर */
#घोषणा SPI_6358_MSG_CTL_WIDTH		16
#घोषणा SPI_6358_MSG_DATA		0x02
#घोषणा SPI_6358_MSG_DATA_SIZE		0x21e
#घोषणा SPI_6358_RX_DATA		0x400
#घोषणा SPI_6358_RX_DATA_SIZE		0x220
#घोषणा SPI_6358_CMD			0x700	/* 16-bits रेजिस्टर */
#घोषणा SPI_6358_INT_STATUS		0x702
#घोषणा SPI_6358_INT_MASK_ST		0x703
#घोषणा SPI_6358_INT_MASK		0x704
#घोषणा SPI_6358_ST			0x705
#घोषणा SPI_6358_CLK_CFG		0x706
#घोषणा SPI_6358_FILL_BYTE		0x707
#घोषणा SPI_6358_MSG_TAIL		0x709
#घोषणा SPI_6358_RX_TAIL		0x70B

/* Shared SPI definitions */

/* Message configuration */
#घोषणा SPI_FD_RW			0x00
#घोषणा SPI_HD_W			0x01
#घोषणा SPI_HD_R			0x02
#घोषणा SPI_BYTE_CNT_SHIFT		0
#घोषणा SPI_6348_MSG_TYPE_SHIFT		6
#घोषणा SPI_6358_MSG_TYPE_SHIFT		14

/* Command */
#घोषणा SPI_CMD_NOOP			0x00
#घोषणा SPI_CMD_SOFT_RESET		0x01
#घोषणा SPI_CMD_HARD_RESET		0x02
#घोषणा SPI_CMD_START_IMMEDIATE		0x03
#घोषणा SPI_CMD_COMMAND_SHIFT		0
#घोषणा SPI_CMD_COMMAND_MASK		0x000f
#घोषणा SPI_CMD_DEVICE_ID_SHIFT		4
#घोषणा SPI_CMD_PREPEND_BYTE_CNT_SHIFT	8
#घोषणा SPI_CMD_ONE_BYTE_SHIFT		11
#घोषणा SPI_CMD_ONE_WIRE_SHIFT		12
#घोषणा SPI_DEV_ID_0			0
#घोषणा SPI_DEV_ID_1			1
#घोषणा SPI_DEV_ID_2			2
#घोषणा SPI_DEV_ID_3			3

/* Interrupt mask */
#घोषणा SPI_INTR_CMD_DONE		0x01
#घोषणा SPI_INTR_RX_OVERFLOW		0x02
#घोषणा SPI_INTR_TX_UNDERFLOW		0x04
#घोषणा SPI_INTR_TX_OVERFLOW		0x08
#घोषणा SPI_INTR_RX_UNDERFLOW		0x10
#घोषणा SPI_INTR_CLEAR_ALL		0x1f

/* Status */
#घोषणा SPI_RX_EMPTY			0x02
#घोषणा SPI_CMD_BUSY			0x04
#घोषणा SPI_SERIAL_BUSY			0x08

/* Clock configuration */
#घोषणा SPI_CLK_20MHZ			0x00
#घोषणा SPI_CLK_0_391MHZ		0x01
#घोषणा SPI_CLK_0_781MHZ		0x02	/* शेष */
#घोषणा SPI_CLK_1_563MHZ		0x03
#घोषणा SPI_CLK_3_125MHZ		0x04
#घोषणा SPI_CLK_6_250MHZ		0x05
#घोषणा SPI_CLK_12_50MHZ		0x06
#घोषणा SPI_CLK_MASK			0x07
#घोषणा SPI_SSOFFTIME_MASK		0x38
#घोषणा SPI_SSOFFTIME_SHIFT		3
#घोषणा SPI_BYTE_SWAP			0x80

क्रमागत bcm63xx_regs_spi अणु
	SPI_CMD,
	SPI_INT_STATUS,
	SPI_INT_MASK_ST,
	SPI_INT_MASK,
	SPI_ST,
	SPI_CLK_CFG,
	SPI_FILL_BYTE,
	SPI_MSG_TAIL,
	SPI_RX_TAIL,
	SPI_MSG_CTL,
	SPI_MSG_DATA,
	SPI_RX_DATA,
	SPI_MSG_TYPE_SHIFT,
	SPI_MSG_CTL_WIDTH,
	SPI_MSG_DATA_SIZE,
पूर्ण;

#घोषणा BCM63XX_SPI_MAX_PREPEND		15

#घोषणा BCM63XX_SPI_MAX_CS		8
#घोषणा BCM63XX_SPI_BUS_NUM		0

काष्ठा bcm63xx_spi अणु
	काष्ठा completion	करोne;

	व्योम __iomem		*regs;
	पूर्णांक			irq;

	/* Platक्रमm data */
	स्थिर अचिन्हित दीर्घ	*reg_offsets;
	अचिन्हित पूर्णांक		fअगरo_size;
	अचिन्हित पूर्णांक		msg_type_shअगरt;
	अचिन्हित पूर्णांक		msg_ctl_width;

	/* data iomem */
	u8 __iomem		*tx_io;
	स्थिर u8 __iomem	*rx_io;

	काष्ठा clk		*clk;
	काष्ठा platक्रमm_device	*pdev;
पूर्ण;

अटल अंतरभूत u8 bcm_spi_पढ़ोb(काष्ठा bcm63xx_spi *bs,
			       अचिन्हित पूर्णांक offset)
अणु
	वापस पढ़ोb(bs->regs + bs->reg_offsets[offset]);
पूर्ण

अटल अंतरभूत u16 bcm_spi_पढ़ोw(काष्ठा bcm63xx_spi *bs,
				अचिन्हित पूर्णांक offset)
अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	वापस ioपढ़ो16be(bs->regs + bs->reg_offsets[offset]);
#अन्यथा
	वापस पढ़ोw(bs->regs + bs->reg_offsets[offset]);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम bcm_spi_ग_लिखोb(काष्ठा bcm63xx_spi *bs,
				  u8 value, अचिन्हित पूर्णांक offset)
अणु
	ग_लिखोb(value, bs->regs + bs->reg_offsets[offset]);
पूर्ण

अटल अंतरभूत व्योम bcm_spi_ग_लिखोw(काष्ठा bcm63xx_spi *bs,
				  u16 value, अचिन्हित पूर्णांक offset)
अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	ioग_लिखो16be(value, bs->regs + bs->reg_offsets[offset]);
#अन्यथा
	ग_लिखोw(value, bs->regs + bs->reg_offsets[offset]);
#पूर्ण_अगर
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक bcm63xx_spi_freq_table[SPI_CLK_MASK][2] = अणु
	अणु 20000000, SPI_CLK_20MHZ पूर्ण,
	अणु 12500000, SPI_CLK_12_50MHZ पूर्ण,
	अणु  6250000, SPI_CLK_6_250MHZ पूर्ण,
	अणु  3125000, SPI_CLK_3_125MHZ पूर्ण,
	अणु  1563000, SPI_CLK_1_563MHZ पूर्ण,
	अणु   781000, SPI_CLK_0_781MHZ पूर्ण,
	अणु   391000, SPI_CLK_0_391MHZ पूर्ण
पूर्ण;

अटल व्योम bcm63xx_spi_setup_transfer(काष्ठा spi_device *spi,
				      काष्ठा spi_transfer *t)
अणु
	काष्ठा bcm63xx_spi *bs = spi_master_get_devdata(spi->master);
	u8 clk_cfg, reg;
	पूर्णांक i;

	/* Default to lowest घड़ी configuration */
	clk_cfg = SPI_CLK_0_391MHZ;

	/* Find the बंदst घड़ी configuration */
	क्रम (i = 0; i < SPI_CLK_MASK; i++) अणु
		अगर (t->speed_hz >= bcm63xx_spi_freq_table[i][0]) अणु
			clk_cfg = bcm63xx_spi_freq_table[i][1];
			अवरोध;
		पूर्ण
	पूर्ण

	/* clear existing घड़ी configuration bits of the रेजिस्टर */
	reg = bcm_spi_पढ़ोb(bs, SPI_CLK_CFG);
	reg &= ~SPI_CLK_MASK;
	reg |= clk_cfg;

	bcm_spi_ग_लिखोb(bs, reg, SPI_CLK_CFG);
	dev_dbg(&spi->dev, "Setting clock register to %02x (hz %d)\n",
		clk_cfg, t->speed_hz);
पूर्ण

/* the spi->mode bits understood by this driver: */
#घोषणा MODEBITS (SPI_CPOL | SPI_CPHA)

अटल पूर्णांक bcm63xx_txrx_bufs(काष्ठा spi_device *spi, काष्ठा spi_transfer *first,
				अचिन्हित पूर्णांक num_transfers)
अणु
	काष्ठा bcm63xx_spi *bs = spi_master_get_devdata(spi->master);
	u16 msg_ctl;
	u16 cmd;
	अचिन्हित पूर्णांक i, समयout = 0, prepend_len = 0, len = 0;
	काष्ठा spi_transfer *t = first;
	bool करो_rx = false;
	bool करो_tx = false;

	/* Disable the CMD_DONE पूर्णांकerrupt */
	bcm_spi_ग_लिखोb(bs, 0, SPI_INT_MASK);

	dev_dbg(&spi->dev, "txrx: tx %p, rx %p, len %d\n",
		t->tx_buf, t->rx_buf, t->len);

	अगर (num_transfers > 1 && t->tx_buf && t->len <= BCM63XX_SPI_MAX_PREPEND)
		prepend_len = t->len;

	/* prepare the buffer */
	क्रम (i = 0; i < num_transfers; i++) अणु
		अगर (t->tx_buf) अणु
			करो_tx = true;
			स_नकल_toio(bs->tx_io + len, t->tx_buf, t->len);

			/* करोn't prepend more than one tx */
			अगर (t != first)
				prepend_len = 0;
		पूर्ण

		अगर (t->rx_buf) अणु
			करो_rx = true;
			/* prepend is half-duplex ग_लिखो only */
			अगर (t == first)
				prepend_len = 0;
		पूर्ण

		len += t->len;

		t = list_entry(t->transfer_list.next, काष्ठा spi_transfer,
			       transfer_list);
	पूर्ण

	reinit_completion(&bs->करोne);

	/* Fill in the Message control रेजिस्टर */
	msg_ctl = (len << SPI_BYTE_CNT_SHIFT);

	अगर (करो_rx && करो_tx && prepend_len == 0)
		msg_ctl |= (SPI_FD_RW << bs->msg_type_shअगरt);
	अन्यथा अगर (करो_rx)
		msg_ctl |= (SPI_HD_R << bs->msg_type_shअगरt);
	अन्यथा अगर (करो_tx)
		msg_ctl |= (SPI_HD_W << bs->msg_type_shअगरt);

	चयन (bs->msg_ctl_width) अणु
	हाल 8:
		bcm_spi_ग_लिखोb(bs, msg_ctl, SPI_MSG_CTL);
		अवरोध;
	हाल 16:
		bcm_spi_ग_लिखोw(bs, msg_ctl, SPI_MSG_CTL);
		अवरोध;
	पूर्ण

	/* Issue the transfer */
	cmd = SPI_CMD_START_IMMEDIATE;
	cmd |= (prepend_len << SPI_CMD_PREPEND_BYTE_CNT_SHIFT);
	cmd |= (spi->chip_select << SPI_CMD_DEVICE_ID_SHIFT);
	bcm_spi_ग_लिखोw(bs, cmd, SPI_CMD);

	/* Enable the CMD_DONE पूर्णांकerrupt */
	bcm_spi_ग_लिखोb(bs, SPI_INTR_CMD_DONE, SPI_INT_MASK);

	समयout = रुको_क्रम_completion_समयout(&bs->करोne, HZ);
	अगर (!समयout)
		वापस -ETIMEDOUT;

	अगर (!करो_rx)
		वापस 0;

	len = 0;
	t = first;
	/* Read out all the data */
	क्रम (i = 0; i < num_transfers; i++) अणु
		अगर (t->rx_buf)
			स_नकल_fromio(t->rx_buf, bs->rx_io + len, t->len);

		अगर (t != first || prepend_len == 0)
			len += t->len;

		t = list_entry(t->transfer_list.next, काष्ठा spi_transfer,
			       transfer_list);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm63xx_spi_transfer_one(काष्ठा spi_master *master,
					काष्ठा spi_message *m)
अणु
	काष्ठा bcm63xx_spi *bs = spi_master_get_devdata(master);
	काष्ठा spi_transfer *t, *first = शून्य;
	काष्ठा spi_device *spi = m->spi;
	पूर्णांक status = 0;
	अचिन्हित पूर्णांक n_transfers = 0, total_len = 0;
	bool can_use_prepend = false;

	/*
	 * This SPI controller करोes not support keeping CS active after a
	 * transfer.
	 * Work around this by merging as many transfers we can पूर्णांकo one big
	 * full-duplex transfers.
	 */
	list_क्रम_each_entry(t, &m->transfers, transfer_list) अणु
		अगर (!first)
			first = t;

		n_transfers++;
		total_len += t->len;

		अगर (n_transfers == 2 && !first->rx_buf && !t->tx_buf &&
		    first->len <= BCM63XX_SPI_MAX_PREPEND)
			can_use_prepend = true;
		अन्यथा अगर (can_use_prepend && t->tx_buf)
			can_use_prepend = false;

		/* we can only transfer one fअगरo worth of data */
		अगर ((can_use_prepend &&
		     total_len > (bs->fअगरo_size + BCM63XX_SPI_MAX_PREPEND)) ||
		    (!can_use_prepend && total_len > bs->fअगरo_size)) अणु
			dev_err(&spi->dev, "unable to do transfers larger than FIFO size (%i > %i)\n",
				total_len, bs->fअगरo_size);
			status = -EINVAL;
			जाओ निकास;
		पूर्ण

		/* all combined transfers have to have the same speed */
		अगर (t->speed_hz != first->speed_hz) अणु
			dev_err(&spi->dev, "unable to change speed between transfers\n");
			status = -EINVAL;
			जाओ निकास;
		पूर्ण

		/* CS will be deनिश्चितed directly after transfer */
		अगर (t->delay.value) अणु
			dev_err(&spi->dev, "unable to keep CS asserted after transfer\n");
			status = -EINVAL;
			जाओ निकास;
		पूर्ण

		अगर (t->cs_change ||
		    list_is_last(&t->transfer_list, &m->transfers)) अणु
			/* configure adapter क्रम a new transfer */
			bcm63xx_spi_setup_transfer(spi, first);

			/* send the data */
			status = bcm63xx_txrx_bufs(spi, first, n_transfers);
			अगर (status)
				जाओ निकास;

			m->actual_length += total_len;

			first = शून्य;
			n_transfers = 0;
			total_len = 0;
			can_use_prepend = false;
		पूर्ण
	पूर्ण
निकास:
	m->status = status;
	spi_finalize_current_message(master);

	वापस 0;
पूर्ण

/* This driver supports single master mode only. Hence
 * CMD_DONE is the only पूर्णांकerrupt we care about
 */
अटल irqवापस_t bcm63xx_spi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा spi_master *master = (काष्ठा spi_master *)dev_id;
	काष्ठा bcm63xx_spi *bs = spi_master_get_devdata(master);
	u8 पूर्णांकr;

	/* Read पूर्णांकerupts and clear them immediately */
	पूर्णांकr = bcm_spi_पढ़ोb(bs, SPI_INT_STATUS);
	bcm_spi_ग_लिखोb(bs, SPI_INTR_CLEAR_ALL, SPI_INT_STATUS);
	bcm_spi_ग_लिखोb(bs, 0, SPI_INT_MASK);

	/* A transfer completed */
	अगर (पूर्णांकr & SPI_INTR_CMD_DONE)
		complete(&bs->करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल माप_प्रकार bcm63xx_spi_max_length(काष्ठा spi_device *spi)
अणु
	काष्ठा bcm63xx_spi *bs = spi_master_get_devdata(spi->master);

	वापस bs->fअगरo_size;
पूर्ण

अटल स्थिर अचिन्हित दीर्घ bcm6348_spi_reg_offsets[] = अणु
	[SPI_CMD]		= SPI_6348_CMD,
	[SPI_INT_STATUS]	= SPI_6348_INT_STATUS,
	[SPI_INT_MASK_ST]	= SPI_6348_INT_MASK_ST,
	[SPI_INT_MASK]		= SPI_6348_INT_MASK,
	[SPI_ST]		= SPI_6348_ST,
	[SPI_CLK_CFG]		= SPI_6348_CLK_CFG,
	[SPI_FILL_BYTE]		= SPI_6348_FILL_BYTE,
	[SPI_MSG_TAIL]		= SPI_6348_MSG_TAIL,
	[SPI_RX_TAIL]		= SPI_6348_RX_TAIL,
	[SPI_MSG_CTL]		= SPI_6348_MSG_CTL,
	[SPI_MSG_DATA]		= SPI_6348_MSG_DATA,
	[SPI_RX_DATA]		= SPI_6348_RX_DATA,
	[SPI_MSG_TYPE_SHIFT]	= SPI_6348_MSG_TYPE_SHIFT,
	[SPI_MSG_CTL_WIDTH]	= SPI_6348_MSG_CTL_WIDTH,
	[SPI_MSG_DATA_SIZE]	= SPI_6348_MSG_DATA_SIZE,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ bcm6358_spi_reg_offsets[] = अणु
	[SPI_CMD]		= SPI_6358_CMD,
	[SPI_INT_STATUS]	= SPI_6358_INT_STATUS,
	[SPI_INT_MASK_ST]	= SPI_6358_INT_MASK_ST,
	[SPI_INT_MASK]		= SPI_6358_INT_MASK,
	[SPI_ST]		= SPI_6358_ST,
	[SPI_CLK_CFG]		= SPI_6358_CLK_CFG,
	[SPI_FILL_BYTE]		= SPI_6358_FILL_BYTE,
	[SPI_MSG_TAIL]		= SPI_6358_MSG_TAIL,
	[SPI_RX_TAIL]		= SPI_6358_RX_TAIL,
	[SPI_MSG_CTL]		= SPI_6358_MSG_CTL,
	[SPI_MSG_DATA]		= SPI_6358_MSG_DATA,
	[SPI_RX_DATA]		= SPI_6358_RX_DATA,
	[SPI_MSG_TYPE_SHIFT]	= SPI_6358_MSG_TYPE_SHIFT,
	[SPI_MSG_CTL_WIDTH]	= SPI_6358_MSG_CTL_WIDTH,
	[SPI_MSG_DATA_SIZE]	= SPI_6358_MSG_DATA_SIZE,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id bcm63xx_spi_dev_match[] = अणु
	अणु
		.name = "bcm6348-spi",
		.driver_data = (अचिन्हित दीर्घ)bcm6348_spi_reg_offsets,
	पूर्ण,
	अणु
		.name = "bcm6358-spi",
		.driver_data = (अचिन्हित दीर्घ)bcm6358_spi_reg_offsets,
	पूर्ण,
	अणु
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id bcm63xx_spi_of_match[] = अणु
	अणु .compatible = "brcm,bcm6348-spi", .data = &bcm6348_spi_reg_offsets पूर्ण,
	अणु .compatible = "brcm,bcm6358-spi", .data = &bcm6358_spi_reg_offsets पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक bcm63xx_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *r;
	स्थिर अचिन्हित दीर्घ *bcm63xx_spireg;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक irq, bus_num;
	काष्ठा spi_master *master;
	काष्ठा clk *clk;
	काष्ठा bcm63xx_spi *bs;
	पूर्णांक ret;
	u32 num_cs = BCM63XX_SPI_MAX_CS;
	काष्ठा reset_control *reset;

	अगर (dev->of_node) अणु
		स्थिर काष्ठा of_device_id *match;

		match = of_match_node(bcm63xx_spi_of_match, dev->of_node);
		अगर (!match)
			वापस -EINVAL;
		bcm63xx_spireg = match->data;

		of_property_पढ़ो_u32(dev->of_node, "num-cs", &num_cs);
		अगर (num_cs > BCM63XX_SPI_MAX_CS) अणु
			dev_warn(dev, "unsupported number of cs (%i), reducing to 8\n",
				 num_cs);
			num_cs = BCM63XX_SPI_MAX_CS;
		पूर्ण

		bus_num = -1;
	पूर्ण अन्यथा अगर (pdev->id_entry->driver_data) अणु
		स्थिर काष्ठा platक्रमm_device_id *match = pdev->id_entry;

		bcm63xx_spireg = (स्थिर अचिन्हित दीर्घ *)match->driver_data;
		bus_num = BCM63XX_SPI_BUS_NUM;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	clk = devm_clk_get(dev, "spi");
	अगर (IS_ERR(clk)) अणु
		dev_err(dev, "no clock for device\n");
		वापस PTR_ERR(clk);
	पूर्ण

	reset = devm_reset_control_get_optional_exclusive(dev, शून्य);
	अगर (IS_ERR(reset))
		वापस PTR_ERR(reset);

	master = spi_alloc_master(dev, माप(*bs));
	अगर (!master) अणु
		dev_err(dev, "out of memory\n");
		वापस -ENOMEM;
	पूर्ण

	bs = spi_master_get_devdata(master);
	init_completion(&bs->करोne);

	platक्रमm_set_drvdata(pdev, master);
	bs->pdev = pdev;

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	bs->regs = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(bs->regs)) अणु
		ret = PTR_ERR(bs->regs);
		जाओ out_err;
	पूर्ण

	bs->irq = irq;
	bs->clk = clk;
	bs->reg_offsets = bcm63xx_spireg;
	bs->fअगरo_size = bs->reg_offsets[SPI_MSG_DATA_SIZE];

	ret = devm_request_irq(&pdev->dev, irq, bcm63xx_spi_पूर्णांकerrupt, 0,
							pdev->name, master);
	अगर (ret) अणु
		dev_err(dev, "unable to request irq\n");
		जाओ out_err;
	पूर्ण

	master->dev.of_node = dev->of_node;
	master->bus_num = bus_num;
	master->num_chipselect = num_cs;
	master->transfer_one_message = bcm63xx_spi_transfer_one;
	master->mode_bits = MODEBITS;
	master->bits_per_word_mask = SPI_BPW_MASK(8);
	master->max_transfer_size = bcm63xx_spi_max_length;
	master->max_message_size = bcm63xx_spi_max_length;
	master->स्वतः_runसमय_pm = true;
	bs->msg_type_shअगरt = bs->reg_offsets[SPI_MSG_TYPE_SHIFT];
	bs->msg_ctl_width = bs->reg_offsets[SPI_MSG_CTL_WIDTH];
	bs->tx_io = (u8 *)(bs->regs + bs->reg_offsets[SPI_MSG_DATA]);
	bs->rx_io = (स्थिर u8 *)(bs->regs + bs->reg_offsets[SPI_RX_DATA]);

	/* Initialize hardware */
	ret = clk_prepare_enable(bs->clk);
	अगर (ret)
		जाओ out_err;

	ret = reset_control_reset(reset);
	अगर (ret) अणु
		dev_err(dev, "unable to reset device: %d\n", ret);
		जाओ out_clk_disable;
	पूर्ण

	bcm_spi_ग_लिखोb(bs, SPI_INTR_CLEAR_ALL, SPI_INT_STATUS);

	pm_runसमय_enable(&pdev->dev);

	/* रेजिस्टर and we are करोne */
	ret = devm_spi_रेजिस्टर_master(dev, master);
	अगर (ret) अणु
		dev_err(dev, "spi register failed\n");
		जाओ out_pm_disable;
	पूर्ण

	dev_info(dev, "at %pr (irq %d, FIFOs size %d)\n",
		 r, irq, bs->fअगरo_size);

	वापस 0;

out_pm_disable:
	pm_runसमय_disable(&pdev->dev);
out_clk_disable:
	clk_disable_unprepare(clk);
out_err:
	spi_master_put(master);
	वापस ret;
पूर्ण

अटल पूर्णांक bcm63xx_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा bcm63xx_spi *bs = spi_master_get_devdata(master);

	/* reset spi block */
	bcm_spi_ग_लिखोb(bs, 0, SPI_INT_MASK);

	/* HW shutकरोwn */
	clk_disable_unprepare(bs->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक bcm63xx_spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा bcm63xx_spi *bs = spi_master_get_devdata(master);

	spi_master_suspend(master);

	clk_disable_unprepare(bs->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm63xx_spi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा bcm63xx_spi *bs = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = clk_prepare_enable(bs->clk);
	अगर (ret)
		वापस ret;

	spi_master_resume(master);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops bcm63xx_spi_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(bcm63xx_spi_suspend, bcm63xx_spi_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver bcm63xx_spi_driver = अणु
	.driver = अणु
		.name	= "bcm63xx-spi",
		.pm	= &bcm63xx_spi_pm_ops,
		.of_match_table = bcm63xx_spi_of_match,
	पूर्ण,
	.id_table	= bcm63xx_spi_dev_match,
	.probe		= bcm63xx_spi_probe,
	.हटाओ		= bcm63xx_spi_हटाओ,
पूर्ण;

module_platक्रमm_driver(bcm63xx_spi_driver);

MODULE_ALIAS("platform:bcm63xx_spi");
MODULE_AUTHOR("Florian Fainelli <florian@openwrt.org>");
MODULE_AUTHOR("Tanguy Bouzeloc <tanguy.bouzeloc@efixo.com>");
MODULE_DESCRIPTION("Broadcom BCM63xx SPI Controller driver");
MODULE_LICENSE("GPL");
