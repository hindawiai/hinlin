<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Spपढ़ोtrum Communications Inc.

#समावेश <linux/clk.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dma/sprd-dma.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/spi/spi.h>

#घोषणा SPRD_SPI_TXD			0x0
#घोषणा SPRD_SPI_CLKD			0x4
#घोषणा SPRD_SPI_CTL0			0x8
#घोषणा SPRD_SPI_CTL1			0xc
#घोषणा SPRD_SPI_CTL2			0x10
#घोषणा SPRD_SPI_CTL3			0x14
#घोषणा SPRD_SPI_CTL4			0x18
#घोषणा SPRD_SPI_CTL5			0x1c
#घोषणा SPRD_SPI_INT_EN			0x20
#घोषणा SPRD_SPI_INT_CLR		0x24
#घोषणा SPRD_SPI_INT_RAW_STS		0x28
#घोषणा SPRD_SPI_INT_MASK_STS		0x2c
#घोषणा SPRD_SPI_STS1			0x30
#घोषणा SPRD_SPI_STS2			0x34
#घोषणा SPRD_SPI_DSP_WAIT		0x38
#घोषणा SPRD_SPI_STS3			0x3c
#घोषणा SPRD_SPI_CTL6			0x40
#घोषणा SPRD_SPI_STS4			0x44
#घोषणा SPRD_SPI_FIFO_RST		0x48
#घोषणा SPRD_SPI_CTL7			0x4c
#घोषणा SPRD_SPI_STS5			0x50
#घोषणा SPRD_SPI_CTL8			0x54
#घोषणा SPRD_SPI_CTL9			0x58
#घोषणा SPRD_SPI_CTL10			0x5c
#घोषणा SPRD_SPI_CTL11			0x60
#घोषणा SPRD_SPI_CTL12			0x64
#घोषणा SPRD_SPI_STS6			0x68
#घोषणा SPRD_SPI_STS7			0x6c
#घोषणा SPRD_SPI_STS8			0x70
#घोषणा SPRD_SPI_STS9			0x74

/* Bits & mask definition क्रम रेजिस्टर CTL0 */
#घोषणा SPRD_SPI_SCK_REV		BIT(13)
#घोषणा SPRD_SPI_NG_TX			BIT(1)
#घोषणा SPRD_SPI_NG_RX			BIT(0)
#घोषणा SPRD_SPI_CHNL_LEN_MASK		GENMASK(4, 0)
#घोषणा SPRD_SPI_CSN_MASK		GENMASK(11, 8)
#घोषणा SPRD_SPI_CS0_VALID		BIT(8)

/* Bits & mask definition क्रम रेजिस्टर SPI_INT_EN */
#घोषणा SPRD_SPI_TX_END_INT_EN		BIT(8)
#घोषणा SPRD_SPI_RX_END_INT_EN		BIT(9)

/* Bits & mask definition क्रम रेजिस्टर SPI_INT_RAW_STS */
#घोषणा SPRD_SPI_TX_END_RAW		BIT(8)
#घोषणा SPRD_SPI_RX_END_RAW		BIT(9)

/* Bits & mask definition क्रम रेजिस्टर SPI_INT_CLR */
#घोषणा SPRD_SPI_TX_END_CLR		BIT(8)
#घोषणा SPRD_SPI_RX_END_CLR		BIT(9)

/* Bits & mask definition क्रम रेजिस्टर INT_MASK_STS */
#घोषणा SPRD_SPI_MASK_RX_END		BIT(9)
#घोषणा SPRD_SPI_MASK_TX_END		BIT(8)

/* Bits & mask definition क्रम रेजिस्टर STS2 */
#घोषणा SPRD_SPI_TX_BUSY		BIT(8)

/* Bits & mask definition क्रम रेजिस्टर CTL1 */
#घोषणा SPRD_SPI_RX_MODE		BIT(12)
#घोषणा SPRD_SPI_TX_MODE		BIT(13)
#घोषणा SPRD_SPI_RTX_MD_MASK		GENMASK(13, 12)

/* Bits & mask definition क्रम रेजिस्टर CTL2 */
#घोषणा SPRD_SPI_DMA_EN			BIT(6)

/* Bits & mask definition क्रम रेजिस्टर CTL4 */
#घोषणा SPRD_SPI_START_RX		BIT(9)
#घोषणा SPRD_SPI_ONLY_RECV_MASK		GENMASK(8, 0)

/* Bits & mask definition क्रम रेजिस्टर SPI_INT_CLR */
#घोषणा SPRD_SPI_RX_END_INT_CLR		BIT(9)
#घोषणा SPRD_SPI_TX_END_INT_CLR		BIT(8)

/* Bits & mask definition क्रम रेजिस्टर SPI_INT_RAW */
#घोषणा SPRD_SPI_RX_END_IRQ		BIT(9)
#घोषणा SPRD_SPI_TX_END_IRQ		BIT(8)

/* Bits & mask definition क्रम रेजिस्टर CTL12 */
#घोषणा SPRD_SPI_SW_RX_REQ		BIT(0)
#घोषणा SPRD_SPI_SW_TX_REQ		BIT(1)

/* Bits & mask definition क्रम रेजिस्टर CTL7 */
#घोषणा SPRD_SPI_DATA_LINE2_EN		BIT(15)
#घोषणा SPRD_SPI_MODE_MASK		GENMASK(5, 3)
#घोषणा SPRD_SPI_MODE_OFFSET		3
#घोषणा SPRD_SPI_3WIRE_MODE		4
#घोषणा SPRD_SPI_4WIRE_MODE		0

/* Bits & mask definition क्रम रेजिस्टर CTL8 */
#घोषणा SPRD_SPI_TX_MAX_LEN_MASK	GENMASK(19, 0)
#घोषणा SPRD_SPI_TX_LEN_H_MASK		GENMASK(3, 0)
#घोषणा SPRD_SPI_TX_LEN_H_OFFSET	16

/* Bits & mask definition क्रम रेजिस्टर CTL9 */
#घोषणा SPRD_SPI_TX_LEN_L_MASK		GENMASK(15, 0)

/* Bits & mask definition क्रम रेजिस्टर CTL10 */
#घोषणा SPRD_SPI_RX_MAX_LEN_MASK	GENMASK(19, 0)
#घोषणा SPRD_SPI_RX_LEN_H_MASK		GENMASK(3, 0)
#घोषणा SPRD_SPI_RX_LEN_H_OFFSET	16

/* Bits & mask definition क्रम रेजिस्टर CTL11 */
#घोषणा SPRD_SPI_RX_LEN_L_MASK		GENMASK(15, 0)

/* Default & maximum word delay cycles */
#घोषणा SPRD_SPI_MIN_DELAY_CYCLE	14
#घोषणा SPRD_SPI_MAX_DELAY_CYCLE	130

#घोषणा SPRD_SPI_FIFO_SIZE		32
#घोषणा SPRD_SPI_CHIP_CS_NUM		0x4
#घोषणा SPRD_SPI_CHNL_LEN		2
#घोषणा SPRD_SPI_DEFAULT_SOURCE		26000000
#घोषणा SPRD_SPI_MAX_SPEED_HZ		48000000
#घोषणा SPRD_SPI_AUTOSUSPEND_DELAY	100
#घोषणा SPRD_SPI_DMA_STEP		8

क्रमागत sprd_spi_dma_channel अणु
	SPRD_SPI_RX,
	SPRD_SPI_TX,
	SPRD_SPI_MAX,
पूर्ण;

काष्ठा sprd_spi_dma अणु
	bool enable;
	काष्ठा dma_chan *dma_chan[SPRD_SPI_MAX];
	क्रमागत dma_slave_buswidth width;
	u32 fragmens_len;
	u32 rx_len;
पूर्ण;

काष्ठा sprd_spi अणु
	व्योम __iomem *base;
	phys_addr_t phy_base;
	काष्ठा device *dev;
	काष्ठा clk *clk;
	पूर्णांक irq;
	u32 src_clk;
	u32 hw_mode;
	u32 trans_len;
	u32 trans_mode;
	u32 word_delay;
	u32 hw_speed_hz;
	u32 len;
	पूर्णांक status;
	काष्ठा sprd_spi_dma dma;
	काष्ठा completion xfer_completion;
	स्थिर व्योम *tx_buf;
	व्योम *rx_buf;
	पूर्णांक (*पढ़ो_bufs)(काष्ठा sprd_spi *ss, u32 len);
	पूर्णांक (*ग_लिखो_bufs)(काष्ठा sprd_spi *ss, u32 len);
पूर्ण;

अटल u32 sprd_spi_transfer_max_समयout(काष्ठा sprd_spi *ss,
					 काष्ठा spi_transfer *t)
अणु
	/*
	 * The समय spent on transmission of the full FIFO data is the maximum
	 * SPI transmission समय.
	 */
	u32 size = t->bits_per_word * SPRD_SPI_FIFO_SIZE;
	u32 bit_समय_us = DIV_ROUND_UP(USEC_PER_SEC, ss->hw_speed_hz);
	u32 total_समय_us = size * bit_समय_us;
	/*
	 * There is an पूर्णांकerval between data and the data in our SPI hardware,
	 * so the total transmission समय need add the पूर्णांकerval समय.
	 */
	u32 पूर्णांकerval_cycle = SPRD_SPI_FIFO_SIZE * ss->word_delay;
	u32 पूर्णांकerval_समय_us = DIV_ROUND_UP(पूर्णांकerval_cycle * USEC_PER_SEC,
					    ss->src_clk);

	वापस total_समय_us + पूर्णांकerval_समय_us;
पूर्ण

अटल पूर्णांक sprd_spi_रुको_क्रम_tx_end(काष्ठा sprd_spi *ss, काष्ठा spi_transfer *t)
अणु
	u32 val, us;
	पूर्णांक ret;

	us = sprd_spi_transfer_max_समयout(ss, t);
	ret = पढ़ोl_relaxed_poll_समयout(ss->base + SPRD_SPI_INT_RAW_STS, val,
					 val & SPRD_SPI_TX_END_IRQ, 0, us);
	अगर (ret) अणु
		dev_err(ss->dev, "SPI error, spi send timeout!\n");
		वापस ret;
	पूर्ण

	ret = पढ़ोl_relaxed_poll_समयout(ss->base + SPRD_SPI_STS2, val,
					 !(val & SPRD_SPI_TX_BUSY), 0, us);
	अगर (ret) अणु
		dev_err(ss->dev, "SPI error, spi busy timeout!\n");
		वापस ret;
	पूर्ण

	ग_लिखोl_relaxed(SPRD_SPI_TX_END_INT_CLR, ss->base + SPRD_SPI_INT_CLR);

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_spi_रुको_क्रम_rx_end(काष्ठा sprd_spi *ss, काष्ठा spi_transfer *t)
अणु
	u32 val, us;
	पूर्णांक ret;

	us = sprd_spi_transfer_max_समयout(ss, t);
	ret = पढ़ोl_relaxed_poll_समयout(ss->base + SPRD_SPI_INT_RAW_STS, val,
					 val & SPRD_SPI_RX_END_IRQ, 0, us);
	अगर (ret) अणु
		dev_err(ss->dev, "SPI error, spi rx timeout!\n");
		वापस ret;
	पूर्ण

	ग_लिखोl_relaxed(SPRD_SPI_RX_END_INT_CLR, ss->base + SPRD_SPI_INT_CLR);

	वापस 0;
पूर्ण

अटल व्योम sprd_spi_tx_req(काष्ठा sprd_spi *ss)
अणु
	ग_लिखोl_relaxed(SPRD_SPI_SW_TX_REQ, ss->base + SPRD_SPI_CTL12);
पूर्ण

अटल व्योम sprd_spi_rx_req(काष्ठा sprd_spi *ss)
अणु
	ग_लिखोl_relaxed(SPRD_SPI_SW_RX_REQ, ss->base + SPRD_SPI_CTL12);
पूर्ण

अटल व्योम sprd_spi_enter_idle(काष्ठा sprd_spi *ss)
अणु
	u32 val = पढ़ोl_relaxed(ss->base + SPRD_SPI_CTL1);

	val &= ~SPRD_SPI_RTX_MD_MASK;
	ग_लिखोl_relaxed(val, ss->base + SPRD_SPI_CTL1);
पूर्ण

अटल व्योम sprd_spi_set_transfer_bits(काष्ठा sprd_spi *ss, u32 bits)
अणु
	u32 val = पढ़ोl_relaxed(ss->base + SPRD_SPI_CTL0);

	/* Set the valid bits क्रम every transaction */
	val &= ~(SPRD_SPI_CHNL_LEN_MASK << SPRD_SPI_CHNL_LEN);
	val |= bits << SPRD_SPI_CHNL_LEN;
	ग_लिखोl_relaxed(val, ss->base + SPRD_SPI_CTL0);
पूर्ण

अटल व्योम sprd_spi_set_tx_length(काष्ठा sprd_spi *ss, u32 length)
अणु
	u32 val = पढ़ोl_relaxed(ss->base + SPRD_SPI_CTL8);

	length &= SPRD_SPI_TX_MAX_LEN_MASK;
	val &= ~SPRD_SPI_TX_LEN_H_MASK;
	val |= length >> SPRD_SPI_TX_LEN_H_OFFSET;
	ग_लिखोl_relaxed(val, ss->base + SPRD_SPI_CTL8);

	val = length & SPRD_SPI_TX_LEN_L_MASK;
	ग_लिखोl_relaxed(val, ss->base + SPRD_SPI_CTL9);
पूर्ण

अटल व्योम sprd_spi_set_rx_length(काष्ठा sprd_spi *ss, u32 length)
अणु
	u32 val = पढ़ोl_relaxed(ss->base + SPRD_SPI_CTL10);

	length &= SPRD_SPI_RX_MAX_LEN_MASK;
	val &= ~SPRD_SPI_RX_LEN_H_MASK;
	val |= length >> SPRD_SPI_RX_LEN_H_OFFSET;
	ग_लिखोl_relaxed(val, ss->base + SPRD_SPI_CTL10);

	val = length & SPRD_SPI_RX_LEN_L_MASK;
	ग_लिखोl_relaxed(val, ss->base + SPRD_SPI_CTL11);
पूर्ण

अटल व्योम sprd_spi_chipselect(काष्ठा spi_device *sdev, bool cs)
अणु
	काष्ठा spi_controller *sctlr = sdev->controller;
	काष्ठा sprd_spi *ss = spi_controller_get_devdata(sctlr);
	u32 val;

	val = पढ़ोl_relaxed(ss->base + SPRD_SPI_CTL0);
	/*  The SPI controller will pull करोwn CS pin अगर cs is 0 */
	अगर (!cs) अणु
		val &= ~SPRD_SPI_CS0_VALID;
		ग_लिखोl_relaxed(val, ss->base + SPRD_SPI_CTL0);
	पूर्ण अन्यथा अणु
		val |= SPRD_SPI_CSN_MASK;
		ग_लिखोl_relaxed(val, ss->base + SPRD_SPI_CTL0);
	पूर्ण
पूर्ण

अटल पूर्णांक sprd_spi_ग_लिखो_only_receive(काष्ठा sprd_spi *ss, u32 len)
अणु
	u32 val;

	/* Clear the start receive bit and reset receive data number */
	val = पढ़ोl_relaxed(ss->base + SPRD_SPI_CTL4);
	val &= ~(SPRD_SPI_START_RX | SPRD_SPI_ONLY_RECV_MASK);
	ग_लिखोl_relaxed(val, ss->base + SPRD_SPI_CTL4);

	/* Set the receive data length */
	val = पढ़ोl_relaxed(ss->base + SPRD_SPI_CTL4);
	val |= len & SPRD_SPI_ONLY_RECV_MASK;
	ग_लिखोl_relaxed(val, ss->base + SPRD_SPI_CTL4);

	/* Trigger to receive data */
	val = पढ़ोl_relaxed(ss->base + SPRD_SPI_CTL4);
	val |= SPRD_SPI_START_RX;
	ग_लिखोl_relaxed(val, ss->base + SPRD_SPI_CTL4);

	वापस len;
पूर्ण

अटल पूर्णांक sprd_spi_ग_लिखो_bufs_u8(काष्ठा sprd_spi *ss, u32 len)
अणु
	u8 *tx_p = (u8 *)ss->tx_buf;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		ग_लिखोb_relaxed(tx_p[i], ss->base + SPRD_SPI_TXD);

	ss->tx_buf += i;
	वापस i;
पूर्ण

अटल पूर्णांक sprd_spi_ग_लिखो_bufs_u16(काष्ठा sprd_spi *ss, u32 len)
अणु
	u16 *tx_p = (u16 *)ss->tx_buf;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		ग_लिखोw_relaxed(tx_p[i], ss->base + SPRD_SPI_TXD);

	ss->tx_buf += i << 1;
	वापस i << 1;
पूर्ण

अटल पूर्णांक sprd_spi_ग_लिखो_bufs_u32(काष्ठा sprd_spi *ss, u32 len)
अणु
	u32 *tx_p = (u32 *)ss->tx_buf;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		ग_लिखोl_relaxed(tx_p[i], ss->base + SPRD_SPI_TXD);

	ss->tx_buf += i << 2;
	वापस i << 2;
पूर्ण

अटल पूर्णांक sprd_spi_पढ़ो_bufs_u8(काष्ठा sprd_spi *ss, u32 len)
अणु
	u8 *rx_p = (u8 *)ss->rx_buf;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		rx_p[i] = पढ़ोb_relaxed(ss->base + SPRD_SPI_TXD);

	ss->rx_buf += i;
	वापस i;
पूर्ण

अटल पूर्णांक sprd_spi_पढ़ो_bufs_u16(काष्ठा sprd_spi *ss, u32 len)
अणु
	u16 *rx_p = (u16 *)ss->rx_buf;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		rx_p[i] = पढ़ोw_relaxed(ss->base + SPRD_SPI_TXD);

	ss->rx_buf += i << 1;
	वापस i << 1;
पूर्ण

अटल पूर्णांक sprd_spi_पढ़ो_bufs_u32(काष्ठा sprd_spi *ss, u32 len)
अणु
	u32 *rx_p = (u32 *)ss->rx_buf;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		rx_p[i] = पढ़ोl_relaxed(ss->base + SPRD_SPI_TXD);

	ss->rx_buf += i << 2;
	वापस i << 2;
पूर्ण

अटल पूर्णांक sprd_spi_txrx_bufs(काष्ठा spi_device *sdev, काष्ठा spi_transfer *t)
अणु
	काष्ठा sprd_spi *ss = spi_controller_get_devdata(sdev->controller);
	u32 trans_len = ss->trans_len, len;
	पूर्णांक ret, ग_लिखो_size = 0, पढ़ो_size = 0;

	जबतक (trans_len) अणु
		len = trans_len > SPRD_SPI_FIFO_SIZE ? SPRD_SPI_FIFO_SIZE :
			trans_len;
		अगर (ss->trans_mode & SPRD_SPI_TX_MODE) अणु
			sprd_spi_set_tx_length(ss, len);
			ग_लिखो_size += ss->ग_लिखो_bufs(ss, len);

			/*
			 * For our 3 wires mode or dual TX line mode, we need
			 * to request the controller to transfer.
			 */
			अगर (ss->hw_mode & SPI_3WIRE || ss->hw_mode & SPI_TX_DUAL)
				sprd_spi_tx_req(ss);

			ret = sprd_spi_रुको_क्रम_tx_end(ss, t);
		पूर्ण अन्यथा अणु
			sprd_spi_set_rx_length(ss, len);

			/*
			 * For our 3 wires mode or dual TX line mode, we need
			 * to request the controller to पढ़ो.
			 */
			अगर (ss->hw_mode & SPI_3WIRE || ss->hw_mode & SPI_TX_DUAL)
				sprd_spi_rx_req(ss);
			अन्यथा
				ग_लिखो_size += ss->ग_लिखो_bufs(ss, len);

			ret = sprd_spi_रुको_क्रम_rx_end(ss, t);
		पूर्ण

		अगर (ret)
			जाओ complete;

		अगर (ss->trans_mode & SPRD_SPI_RX_MODE)
			पढ़ो_size += ss->पढ़ो_bufs(ss, len);

		trans_len -= len;
	पूर्ण

	अगर (ss->trans_mode & SPRD_SPI_TX_MODE)
		ret = ग_लिखो_size;
	अन्यथा
		ret = पढ़ो_size;
complete:
	sprd_spi_enter_idle(ss);

	वापस ret;
पूर्ण

अटल व्योम sprd_spi_irq_enable(काष्ठा sprd_spi *ss)
अणु
	u32 val;

	/* Clear पूर्णांकerrupt status beक्रमe enabling पूर्णांकerrupt. */
	ग_लिखोl_relaxed(SPRD_SPI_TX_END_CLR | SPRD_SPI_RX_END_CLR,
		ss->base + SPRD_SPI_INT_CLR);
	/* Enable SPI पूर्णांकerrupt only in DMA mode. */
	val = पढ़ोl_relaxed(ss->base + SPRD_SPI_INT_EN);
	ग_लिखोl_relaxed(val | SPRD_SPI_TX_END_INT_EN |
		       SPRD_SPI_RX_END_INT_EN,
		       ss->base + SPRD_SPI_INT_EN);
पूर्ण

अटल व्योम sprd_spi_irq_disable(काष्ठा sprd_spi *ss)
अणु
	ग_लिखोl_relaxed(0, ss->base + SPRD_SPI_INT_EN);
पूर्ण

अटल व्योम sprd_spi_dma_enable(काष्ठा sprd_spi *ss, bool enable)
अणु
	u32 val = पढ़ोl_relaxed(ss->base + SPRD_SPI_CTL2);

	अगर (enable)
		val |= SPRD_SPI_DMA_EN;
	अन्यथा
		val &= ~SPRD_SPI_DMA_EN;

	ग_लिखोl_relaxed(val, ss->base + SPRD_SPI_CTL2);
पूर्ण

अटल पूर्णांक sprd_spi_dma_submit(काष्ठा dma_chan *dma_chan,
			       काष्ठा dma_slave_config *c,
			       काष्ठा sg_table *sg,
			       क्रमागत dma_transfer_direction dir)
अणु
	काष्ठा dma_async_tx_descriptor *desc;
	dma_cookie_t cookie;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = dmaengine_slave_config(dma_chan, c);
	अगर (ret < 0)
		वापस ret;

	flags = SPRD_DMA_FLAGS(SPRD_DMA_CHN_MODE_NONE, SPRD_DMA_NO_TRG,
			       SPRD_DMA_FRAG_REQ, SPRD_DMA_TRANS_INT);
	desc = dmaengine_prep_slave_sg(dma_chan, sg->sgl, sg->nents, dir, flags);
	अगर (!desc)
		वापस  -ENODEV;

	cookie = dmaengine_submit(desc);
	अगर (dma_submit_error(cookie))
		वापस dma_submit_error(cookie);

	dma_async_issue_pending(dma_chan);

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_spi_dma_rx_config(काष्ठा sprd_spi *ss, काष्ठा spi_transfer *t)
अणु
	काष्ठा dma_chan *dma_chan = ss->dma.dma_chan[SPRD_SPI_RX];
	काष्ठा dma_slave_config config = अणु
		.src_addr = ss->phy_base,
		.src_addr_width = ss->dma.width,
		.dst_addr_width = ss->dma.width,
		.dst_maxburst = ss->dma.fragmens_len,
	पूर्ण;
	पूर्णांक ret;

	ret = sprd_spi_dma_submit(dma_chan, &config, &t->rx_sg, DMA_DEV_TO_MEM);
	अगर (ret)
		वापस ret;

	वापस ss->dma.rx_len;
पूर्ण

अटल पूर्णांक sprd_spi_dma_tx_config(काष्ठा sprd_spi *ss, काष्ठा spi_transfer *t)
अणु
	काष्ठा dma_chan *dma_chan = ss->dma.dma_chan[SPRD_SPI_TX];
	काष्ठा dma_slave_config config = अणु
		.dst_addr = ss->phy_base,
		.src_addr_width = ss->dma.width,
		.dst_addr_width = ss->dma.width,
		.src_maxburst = ss->dma.fragmens_len,
	पूर्ण;
	पूर्णांक ret;

	ret = sprd_spi_dma_submit(dma_chan, &config, &t->tx_sg, DMA_MEM_TO_DEV);
	अगर (ret)
		वापस ret;

	वापस t->len;
पूर्ण

अटल पूर्णांक sprd_spi_dma_request(काष्ठा sprd_spi *ss)
अणु
	ss->dma.dma_chan[SPRD_SPI_RX] = dma_request_chan(ss->dev, "rx_chn");
	अगर (IS_ERR_OR_शून्य(ss->dma.dma_chan[SPRD_SPI_RX]))
		वापस dev_err_probe(ss->dev, PTR_ERR(ss->dma.dma_chan[SPRD_SPI_RX]),
				     "request RX DMA channel failed!\n");

	ss->dma.dma_chan[SPRD_SPI_TX]  = dma_request_chan(ss->dev, "tx_chn");
	अगर (IS_ERR_OR_शून्य(ss->dma.dma_chan[SPRD_SPI_TX])) अणु
		dma_release_channel(ss->dma.dma_chan[SPRD_SPI_RX]);
		वापस dev_err_probe(ss->dev, PTR_ERR(ss->dma.dma_chan[SPRD_SPI_TX]),
				     "request TX DMA channel failed!\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sprd_spi_dma_release(काष्ठा sprd_spi *ss)
अणु
	अगर (ss->dma.dma_chan[SPRD_SPI_RX])
		dma_release_channel(ss->dma.dma_chan[SPRD_SPI_RX]);

	अगर (ss->dma.dma_chan[SPRD_SPI_TX])
		dma_release_channel(ss->dma.dma_chan[SPRD_SPI_TX]);
पूर्ण

अटल पूर्णांक sprd_spi_dma_txrx_bufs(काष्ठा spi_device *sdev,
				  काष्ठा spi_transfer *t)
अणु
	काष्ठा sprd_spi *ss = spi_master_get_devdata(sdev->master);
	u32 trans_len = ss->trans_len;
	पूर्णांक ret, ग_लिखो_size = 0;

	reinit_completion(&ss->xfer_completion);
	sprd_spi_irq_enable(ss);
	अगर (ss->trans_mode & SPRD_SPI_TX_MODE) अणु
		ग_लिखो_size = sprd_spi_dma_tx_config(ss, t);
		sprd_spi_set_tx_length(ss, trans_len);

		/*
		 * For our 3 wires mode or dual TX line mode, we need
		 * to request the controller to transfer.
		 */
		अगर (ss->hw_mode & SPI_3WIRE || ss->hw_mode & SPI_TX_DUAL)
			sprd_spi_tx_req(ss);
	पूर्ण अन्यथा अणु
		sprd_spi_set_rx_length(ss, trans_len);

		/*
		 * For our 3 wires mode or dual TX line mode, we need
		 * to request the controller to पढ़ो.
		 */
		अगर (ss->hw_mode & SPI_3WIRE || ss->hw_mode & SPI_TX_DUAL)
			sprd_spi_rx_req(ss);
		अन्यथा
			ग_लिखो_size = ss->ग_लिखो_bufs(ss, trans_len);
	पूर्ण

	अगर (ग_लिखो_size < 0) अणु
		ret = ग_लिखो_size;
		dev_err(ss->dev, "failed to write, ret = %d\n", ret);
		जाओ trans_complete;
	पूर्ण

	अगर (ss->trans_mode & SPRD_SPI_RX_MODE) अणु
		/*
		 * Set up the DMA receive data length, which must be an
		 * पूर्णांकegral multiple of fragment length. But when the length
		 * of received data is less than fragment length, DMA can be
		 * configured to receive data according to the actual length
		 * of received data.
		 */
		ss->dma.rx_len = t->len > ss->dma.fragmens_len ?
			(t->len - t->len % ss->dma.fragmens_len) :
			 t->len;
		ret = sprd_spi_dma_rx_config(ss, t);
		अगर (ret < 0) अणु
			dev_err(&sdev->dev,
				"failed to configure rx DMA, ret = %d\n", ret);
			जाओ trans_complete;
		पूर्ण
	पूर्ण

	sprd_spi_dma_enable(ss, true);
	रुको_क्रम_completion(&(ss->xfer_completion));

	अगर (ss->trans_mode & SPRD_SPI_TX_MODE)
		ret = ग_लिखो_size;
	अन्यथा
		ret = ss->dma.rx_len;

trans_complete:
	sprd_spi_dma_enable(ss, false);
	sprd_spi_enter_idle(ss);
	sprd_spi_irq_disable(ss);

	वापस ret;
पूर्ण

अटल व्योम sprd_spi_set_speed(काष्ठा sprd_spi *ss, u32 speed_hz)
अणु
	/*
	 * From SPI datasheet, the prescale calculation क्रमmula:
	 * prescale = SPI source घड़ी / (2 * SPI_freq) - 1;
	 */
	u32 clk_भाग = DIV_ROUND_UP(ss->src_clk, speed_hz << 1) - 1;

	/* Save the real hardware speed */
	ss->hw_speed_hz = (ss->src_clk >> 1) / (clk_भाग + 1);
	ग_लिखोl_relaxed(clk_भाग, ss->base + SPRD_SPI_CLKD);
पूर्ण

अटल पूर्णांक sprd_spi_init_hw(काष्ठा sprd_spi *ss, काष्ठा spi_transfer *t)
अणु
	काष्ठा spi_delay *d = &t->word_delay;
	u16 word_delay, पूर्णांकerval;
	u32 val;

	अगर (d->unit != SPI_DELAY_UNIT_SCK)
		वापस -EINVAL;

	val = पढ़ोl_relaxed(ss->base + SPRD_SPI_CTL0);
	val &= ~(SPRD_SPI_SCK_REV | SPRD_SPI_NG_TX | SPRD_SPI_NG_RX);
	/* Set शेष chip selection, घड़ी phase and घड़ी polarity */
	val |= ss->hw_mode & SPI_CPHA ? SPRD_SPI_NG_RX : SPRD_SPI_NG_TX;
	val |= ss->hw_mode & SPI_CPOL ? SPRD_SPI_SCK_REV : 0;
	ग_लिखोl_relaxed(val, ss->base + SPRD_SPI_CTL0);

	/*
	 * Set the पूर्णांकervals of two SPI frames, and the पूर्णांकeval calculation
	 * क्रमmula as below per datasheet:
	 * पूर्णांकerval समय (source घड़ी cycles) = पूर्णांकerval * 4 + 10.
	 */
	word_delay = clamp_t(u16, d->value, SPRD_SPI_MIN_DELAY_CYCLE,
			     SPRD_SPI_MAX_DELAY_CYCLE);
	पूर्णांकerval = DIV_ROUND_UP(word_delay - 10, 4);
	ss->word_delay = पूर्णांकerval * 4 + 10;
	ग_लिखोl_relaxed(पूर्णांकerval, ss->base + SPRD_SPI_CTL5);

	/* Reset SPI fअगरo */
	ग_लिखोl_relaxed(1, ss->base + SPRD_SPI_FIFO_RST);
	ग_लिखोl_relaxed(0, ss->base + SPRD_SPI_FIFO_RST);

	/* Set SPI work mode */
	val = पढ़ोl_relaxed(ss->base + SPRD_SPI_CTL7);
	val &= ~SPRD_SPI_MODE_MASK;

	अगर (ss->hw_mode & SPI_3WIRE)
		val |= SPRD_SPI_3WIRE_MODE << SPRD_SPI_MODE_OFFSET;
	अन्यथा
		val |= SPRD_SPI_4WIRE_MODE << SPRD_SPI_MODE_OFFSET;

	अगर (ss->hw_mode & SPI_TX_DUAL)
		val |= SPRD_SPI_DATA_LINE2_EN;
	अन्यथा
		val &= ~SPRD_SPI_DATA_LINE2_EN;

	ग_लिखोl_relaxed(val, ss->base + SPRD_SPI_CTL7);

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_spi_setup_transfer(काष्ठा spi_device *sdev,
				   काष्ठा spi_transfer *t)
अणु
	काष्ठा sprd_spi *ss = spi_controller_get_devdata(sdev->controller);
	u8 bits_per_word = t->bits_per_word;
	u32 val, mode = 0;
	पूर्णांक ret;

	ss->len = t->len;
	ss->tx_buf = t->tx_buf;
	ss->rx_buf = t->rx_buf;

	ss->hw_mode = sdev->mode;
	ret = sprd_spi_init_hw(ss, t);
	अगर (ret)
		वापस ret;

	/* Set tansfer speed and valid bits */
	sprd_spi_set_speed(ss, t->speed_hz);
	sprd_spi_set_transfer_bits(ss, bits_per_word);

	अगर (bits_per_word > 16)
		bits_per_word = round_up(bits_per_word, 16);
	अन्यथा
		bits_per_word = round_up(bits_per_word, 8);

	चयन (bits_per_word) अणु
	हाल 8:
		ss->trans_len = t->len;
		ss->पढ़ो_bufs = sprd_spi_पढ़ो_bufs_u8;
		ss->ग_लिखो_bufs = sprd_spi_ग_लिखो_bufs_u8;
		ss->dma.width = DMA_SLAVE_BUSWIDTH_1_BYTE;
		ss->dma.fragmens_len = SPRD_SPI_DMA_STEP;
		अवरोध;
	हाल 16:
		ss->trans_len = t->len >> 1;
		ss->पढ़ो_bufs = sprd_spi_पढ़ो_bufs_u16;
		ss->ग_लिखो_bufs = sprd_spi_ग_लिखो_bufs_u16;
		ss->dma.width = DMA_SLAVE_BUSWIDTH_2_BYTES;
		ss->dma.fragmens_len = SPRD_SPI_DMA_STEP << 1;
		अवरोध;
	हाल 32:
		ss->trans_len = t->len >> 2;
		ss->पढ़ो_bufs = sprd_spi_पढ़ो_bufs_u32;
		ss->ग_लिखो_bufs = sprd_spi_ग_लिखो_bufs_u32;
		ss->dma.width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		ss->dma.fragmens_len = SPRD_SPI_DMA_STEP << 2;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Set transfer पढ़ो or ग_लिखो mode */
	val = पढ़ोl_relaxed(ss->base + SPRD_SPI_CTL1);
	val &= ~SPRD_SPI_RTX_MD_MASK;
	अगर (t->tx_buf)
		mode |= SPRD_SPI_TX_MODE;
	अगर (t->rx_buf)
		mode |= SPRD_SPI_RX_MODE;

	ग_लिखोl_relaxed(val | mode, ss->base + SPRD_SPI_CTL1);

	ss->trans_mode = mode;

	/*
	 * If in only receive mode, we need to trigger the SPI controller to
	 * receive data स्वतःmatically.
	 */
	अगर (ss->trans_mode == SPRD_SPI_RX_MODE)
		ss->ग_लिखो_bufs = sprd_spi_ग_लिखो_only_receive;

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_spi_transfer_one(काष्ठा spi_controller *sctlr,
				 काष्ठा spi_device *sdev,
				 काष्ठा spi_transfer *t)
अणु
	पूर्णांक ret;

	ret = sprd_spi_setup_transfer(sdev, t);
	अगर (ret)
		जाओ setup_err;

	अगर (sctlr->can_dma(sctlr, sdev, t))
		ret = sprd_spi_dma_txrx_bufs(sdev, t);
	अन्यथा
		ret = sprd_spi_txrx_bufs(sdev, t);

	अगर (ret == t->len)
		ret = 0;
	अन्यथा अगर (ret >= 0)
		ret = -EREMOTEIO;

setup_err:
	spi_finalize_current_transfer(sctlr);

	वापस ret;
पूर्ण

अटल irqवापस_t sprd_spi_handle_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sprd_spi *ss = (काष्ठा sprd_spi *)data;
	u32 val = पढ़ोl_relaxed(ss->base + SPRD_SPI_INT_MASK_STS);

	अगर (val & SPRD_SPI_MASK_TX_END) अणु
		ग_लिखोl_relaxed(SPRD_SPI_TX_END_CLR, ss->base + SPRD_SPI_INT_CLR);
		अगर (!(ss->trans_mode & SPRD_SPI_RX_MODE))
			complete(&ss->xfer_completion);

		वापस IRQ_HANDLED;
	पूर्ण

	अगर (val & SPRD_SPI_MASK_RX_END) अणु
		ग_लिखोl_relaxed(SPRD_SPI_RX_END_CLR, ss->base + SPRD_SPI_INT_CLR);
		अगर (ss->dma.rx_len < ss->len) अणु
			ss->rx_buf += ss->dma.rx_len;
			ss->dma.rx_len +=
				ss->पढ़ो_bufs(ss, ss->len - ss->dma.rx_len);
		पूर्ण
		complete(&ss->xfer_completion);

		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक sprd_spi_irq_init(काष्ठा platक्रमm_device *pdev, काष्ठा sprd_spi *ss)
अणु
	पूर्णांक ret;

	ss->irq = platक्रमm_get_irq(pdev, 0);
	अगर (ss->irq < 0)
		वापस ss->irq;

	ret = devm_request_irq(&pdev->dev, ss->irq, sprd_spi_handle_irq,
				0, pdev->name, ss);
	अगर (ret)
		dev_err(&pdev->dev, "failed to request spi irq %d, ret = %d\n",
			ss->irq, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक sprd_spi_clk_init(काष्ठा platक्रमm_device *pdev, काष्ठा sprd_spi *ss)
अणु
	काष्ठा clk *clk_spi, *clk_parent;

	clk_spi = devm_clk_get(&pdev->dev, "spi");
	अगर (IS_ERR(clk_spi)) अणु
		dev_warn(&pdev->dev, "can't get the spi clock\n");
		clk_spi = शून्य;
	पूर्ण

	clk_parent = devm_clk_get(&pdev->dev, "source");
	अगर (IS_ERR(clk_parent)) अणु
		dev_warn(&pdev->dev, "can't get the source clock\n");
		clk_parent = शून्य;
	पूर्ण

	ss->clk = devm_clk_get(&pdev->dev, "enable");
	अगर (IS_ERR(ss->clk)) अणु
		dev_err(&pdev->dev, "can't get the enable clock\n");
		वापस PTR_ERR(ss->clk);
	पूर्ण

	अगर (!clk_set_parent(clk_spi, clk_parent))
		ss->src_clk = clk_get_rate(clk_spi);
	अन्यथा
		ss->src_clk = SPRD_SPI_DEFAULT_SOURCE;

	वापस 0;
पूर्ण

अटल bool sprd_spi_can_dma(काष्ठा spi_controller *sctlr,
			     काष्ठा spi_device *spi, काष्ठा spi_transfer *t)
अणु
	काष्ठा sprd_spi *ss = spi_controller_get_devdata(sctlr);

	वापस ss->dma.enable && (t->len > SPRD_SPI_FIFO_SIZE);
पूर्ण

अटल पूर्णांक sprd_spi_dma_init(काष्ठा platक्रमm_device *pdev, काष्ठा sprd_spi *ss)
अणु
	पूर्णांक ret;

	ret = sprd_spi_dma_request(ss);
	अगर (ret) अणु
		अगर (ret == -EPROBE_DEFER)
			वापस ret;

		dev_warn(&pdev->dev,
			 "failed to request dma, enter no dma mode, ret = %d\n",
			 ret);

		वापस 0;
	पूर्ण

	ss->dma.enable = true;

	वापस 0;
पूर्ण

अटल पूर्णांक sprd_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_controller *sctlr;
	काष्ठा resource *res;
	काष्ठा sprd_spi *ss;
	पूर्णांक ret;

	pdev->id = of_alias_get_id(pdev->dev.of_node, "spi");
	sctlr = spi_alloc_master(&pdev->dev, माप(*ss));
	अगर (!sctlr)
		वापस -ENOMEM;

	ss = spi_controller_get_devdata(sctlr);
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	ss->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(ss->base)) अणु
		ret = PTR_ERR(ss->base);
		जाओ मुक्त_controller;
	पूर्ण

	ss->phy_base = res->start;
	ss->dev = &pdev->dev;
	sctlr->dev.of_node = pdev->dev.of_node;
	sctlr->mode_bits = SPI_CPOL | SPI_CPHA | SPI_3WIRE | SPI_TX_DUAL;
	sctlr->bus_num = pdev->id;
	sctlr->set_cs = sprd_spi_chipselect;
	sctlr->transfer_one = sprd_spi_transfer_one;
	sctlr->can_dma = sprd_spi_can_dma;
	sctlr->स्वतः_runसमय_pm = true;
	sctlr->max_speed_hz = min_t(u32, ss->src_clk >> 1,
				    SPRD_SPI_MAX_SPEED_HZ);

	init_completion(&ss->xfer_completion);
	platक्रमm_set_drvdata(pdev, sctlr);
	ret = sprd_spi_clk_init(pdev, ss);
	अगर (ret)
		जाओ मुक्त_controller;

	ret = sprd_spi_irq_init(pdev, ss);
	अगर (ret)
		जाओ मुक्त_controller;

	ret = sprd_spi_dma_init(pdev, ss);
	अगर (ret)
		जाओ मुक्त_controller;

	ret = clk_prepare_enable(ss->clk);
	अगर (ret)
		जाओ release_dma;

	ret = pm_runसमय_set_active(&pdev->dev);
	अगर (ret < 0)
		जाओ disable_clk;

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev,
					 SPRD_SPI_AUTOSUSPEND_DELAY);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);
	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "failed to resume SPI controller\n");
		जाओ err_rpm_put;
	पूर्ण

	ret = devm_spi_रेजिस्टर_controller(&pdev->dev, sctlr);
	अगर (ret)
		जाओ err_rpm_put;

	pm_runसमय_mark_last_busy(&pdev->dev);
	pm_runसमय_put_स्वतःsuspend(&pdev->dev);

	वापस 0;

err_rpm_put:
	pm_runसमय_put_noidle(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
disable_clk:
	clk_disable_unprepare(ss->clk);
release_dma:
	sprd_spi_dma_release(ss);
मुक्त_controller:
	spi_controller_put(sctlr);

	वापस ret;
पूर्ण

अटल पूर्णांक sprd_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_controller *sctlr = platक्रमm_get_drvdata(pdev);
	काष्ठा sprd_spi *ss = spi_controller_get_devdata(sctlr);
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(ss->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(ss->dev);
		dev_err(ss->dev, "failed to resume SPI controller\n");
		वापस ret;
	पूर्ण

	spi_controller_suspend(sctlr);

	अगर (ss->dma.enable)
		sprd_spi_dma_release(ss);
	clk_disable_unprepare(ss->clk);
	pm_runसमय_put_noidle(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sprd_spi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_controller *sctlr = dev_get_drvdata(dev);
	काष्ठा sprd_spi *ss = spi_controller_get_devdata(sctlr);

	अगर (ss->dma.enable)
		sprd_spi_dma_release(ss);

	clk_disable_unprepare(ss->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sprd_spi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_controller *sctlr = dev_get_drvdata(dev);
	काष्ठा sprd_spi *ss = spi_controller_get_devdata(sctlr);
	पूर्णांक ret;

	ret = clk_prepare_enable(ss->clk);
	अगर (ret)
		वापस ret;

	अगर (!ss->dma.enable)
		वापस 0;

	ret = sprd_spi_dma_request(ss);
	अगर (ret)
		clk_disable_unprepare(ss->clk);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops sprd_spi_pm_ops = अणु
	SET_RUNTIME_PM_OPS(sprd_spi_runसमय_suspend,
			   sprd_spi_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id sprd_spi_of_match[] = अणु
	अणु .compatible = "sprd,sc9860-spi", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sprd_spi_of_match);

अटल काष्ठा platक्रमm_driver sprd_spi_driver = अणु
	.driver = अणु
		.name = "sprd-spi",
		.of_match_table = sprd_spi_of_match,
		.pm = &sprd_spi_pm_ops,
	पूर्ण,
	.probe = sprd_spi_probe,
	.हटाओ  = sprd_spi_हटाओ,
पूर्ण;

module_platक्रमm_driver(sprd_spi_driver);

MODULE_DESCRIPTION("Spreadtrum SPI Controller driver");
MODULE_AUTHOR("Lanqing Liu <lanqing.liu@spreadtrum.com>");
MODULE_LICENSE("GPL v2");
