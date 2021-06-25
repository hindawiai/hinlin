<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Synquacer HSSPI controller driver
//
// Copyright (c) 2015-2018 Socionext Inc.
// Copyright (c) 2018-2019 Linaro Ltd.
//

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/clk.h>

/* HSSPI रेजिस्टर address definitions */
#घोषणा SYNQUACER_HSSPI_REG_MCTRL	0x00
#घोषणा SYNQUACER_HSSPI_REG_PCC0	0x04
#घोषणा SYNQUACER_HSSPI_REG_PCC(n)	(SYNQUACER_HSSPI_REG_PCC0 + (n) * 4)
#घोषणा SYNQUACER_HSSPI_REG_TXF		0x14
#घोषणा SYNQUACER_HSSPI_REG_TXE		0x18
#घोषणा SYNQUACER_HSSPI_REG_TXC		0x1C
#घोषणा SYNQUACER_HSSPI_REG_RXF		0x20
#घोषणा SYNQUACER_HSSPI_REG_RXE		0x24
#घोषणा SYNQUACER_HSSPI_REG_RXC		0x28
#घोषणा SYNQUACER_HSSPI_REG_FAULTF	0x2C
#घोषणा SYNQUACER_HSSPI_REG_FAULTC	0x30
#घोषणा SYNQUACER_HSSPI_REG_DMCFG	0x34
#घोषणा SYNQUACER_HSSPI_REG_DMSTART	0x38
#घोषणा SYNQUACER_HSSPI_REG_DMBCC	0x3C
#घोषणा SYNQUACER_HSSPI_REG_DMSTATUS	0x40
#घोषणा SYNQUACER_HSSPI_REG_FIFOCFG	0x4C
#घोषणा SYNQUACER_HSSPI_REG_TX_FIFO	0x50
#घोषणा SYNQUACER_HSSPI_REG_RX_FIFO	0x90
#घोषणा SYNQUACER_HSSPI_REG_MID		0xFC

/* HSSPI रेजिस्टर bit definitions */
#घोषणा SYNQUACER_HSSPI_MCTRL_MEN			BIT(0)
#घोषणा SYNQUACER_HSSPI_MCTRL_COMMAND_SEQUENCE_EN	BIT(1)
#घोषणा SYNQUACER_HSSPI_MCTRL_CDSS			BIT(3)
#घोषणा SYNQUACER_HSSPI_MCTRL_MES			BIT(4)
#घोषणा SYNQUACER_HSSPI_MCTRL_SYNCON			BIT(5)

#घोषणा SYNQUACER_HSSPI_PCC_CPHA		BIT(0)
#घोषणा SYNQUACER_HSSPI_PCC_CPOL		BIT(1)
#घोषणा SYNQUACER_HSSPI_PCC_ACES		BIT(2)
#घोषणा SYNQUACER_HSSPI_PCC_RTM			BIT(3)
#घोषणा SYNQUACER_HSSPI_PCC_SSPOL		BIT(4)
#घोषणा SYNQUACER_HSSPI_PCC_Sसूची		BIT(7)
#घोषणा SYNQUACER_HSSPI_PCC_SENDIAN		BIT(8)
#घोषणा SYNQUACER_HSSPI_PCC_SAFESYNC		BIT(16)
#घोषणा SYNQUACER_HSSPI_PCC_SS2CD_SHIFT		5U
#घोषणा SYNQUACER_HSSPI_PCC_CDRS_MASK		0x7f
#घोषणा SYNQUACER_HSSPI_PCC_CDRS_SHIFT		9U

#घोषणा SYNQUACER_HSSPI_TXF_FIFO_FULL		BIT(0)
#घोषणा SYNQUACER_HSSPI_TXF_FIFO_EMPTY		BIT(1)
#घोषणा SYNQUACER_HSSPI_TXF_SLAVE_RELEASED	BIT(6)

#घोषणा SYNQUACER_HSSPI_TXE_FIFO_FULL		BIT(0)
#घोषणा SYNQUACER_HSSPI_TXE_FIFO_EMPTY		BIT(1)
#घोषणा SYNQUACER_HSSPI_TXE_SLAVE_RELEASED	BIT(6)

#घोषणा SYNQUACER_HSSPI_RXF_FIFO_MORE_THAN_THRESHOLD		BIT(5)
#घोषणा SYNQUACER_HSSPI_RXF_SLAVE_RELEASED			BIT(6)

#घोषणा SYNQUACER_HSSPI_RXE_FIFO_MORE_THAN_THRESHOLD		BIT(5)
#घोषणा SYNQUACER_HSSPI_RXE_SLAVE_RELEASED			BIT(6)

#घोषणा SYNQUACER_HSSPI_DMCFG_SSDC		BIT(1)
#घोषणा SYNQUACER_HSSPI_DMCFG_MSTARTEN		BIT(2)

#घोषणा SYNQUACER_HSSPI_DMSTART_START		BIT(0)
#घोषणा SYNQUACER_HSSPI_DMSTOP_STOP		BIT(8)
#घोषणा SYNQUACER_HSSPI_DMPSEL_CS_MASK		0x3
#घोषणा SYNQUACER_HSSPI_DMPSEL_CS_SHIFT		16U
#घोषणा SYNQUACER_HSSPI_DMTRP_BUS_WIDTH_SHIFT	24U
#घोषणा SYNQUACER_HSSPI_DMTRP_DATA_MASK		0x3
#घोषणा SYNQUACER_HSSPI_DMTRP_DATA_SHIFT	26U
#घोषणा SYNQUACER_HSSPI_DMTRP_DATA_TXRX		0
#घोषणा SYNQUACER_HSSPI_DMTRP_DATA_RX		1
#घोषणा SYNQUACER_HSSPI_DMTRP_DATA_TX		2

#घोषणा SYNQUACER_HSSPI_DMSTATUS_RX_DATA_MASK	0x1f
#घोषणा SYNQUACER_HSSPI_DMSTATUS_RX_DATA_SHIFT	8U
#घोषणा SYNQUACER_HSSPI_DMSTATUS_TX_DATA_MASK	0x1f
#घोषणा SYNQUACER_HSSPI_DMSTATUS_TX_DATA_SHIFT	16U

#घोषणा SYNQUACER_HSSPI_FIFOCFG_RX_THRESHOLD_MASK	0xf
#घोषणा SYNQUACER_HSSPI_FIFOCFG_RX_THRESHOLD_SHIFT	0U
#घोषणा SYNQUACER_HSSPI_FIFOCFG_TX_THRESHOLD_MASK	0xf
#घोषणा SYNQUACER_HSSPI_FIFOCFG_TX_THRESHOLD_SHIFT	4U
#घोषणा SYNQUACER_HSSPI_FIFOCFG_FIFO_WIDTH_MASK		0x3
#घोषणा SYNQUACER_HSSPI_FIFOCFG_FIFO_WIDTH_SHIFT	8U
#घोषणा SYNQUACER_HSSPI_FIFOCFG_RX_FLUSH		BIT(11)
#घोषणा SYNQUACER_HSSPI_FIFOCFG_TX_FLUSH		BIT(12)

#घोषणा SYNQUACER_HSSPI_FIFO_DEPTH		16U
#घोषणा SYNQUACER_HSSPI_FIFO_TX_THRESHOLD	4U
#घोषणा SYNQUACER_HSSPI_FIFO_RX_THRESHOLD \
	(SYNQUACER_HSSPI_FIFO_DEPTH - SYNQUACER_HSSPI_FIFO_TX_THRESHOLD)

#घोषणा SYNQUACER_HSSPI_TRANSFER_MODE_TX	BIT(1)
#घोषणा SYNQUACER_HSSPI_TRANSFER_MODE_RX	BIT(2)
#घोषणा SYNQUACER_HSSPI_TRANSFER_TMOUT_MSEC	2000U
#घोषणा SYNQUACER_HSSPI_ENABLE_TMOUT_MSEC	1000U

#घोषणा SYNQUACER_HSSPI_CLOCK_SRC_IHCLK		0
#घोषणा SYNQUACER_HSSPI_CLOCK_SRC_IPCLK		1

#घोषणा SYNQUACER_HSSPI_NUM_CHIP_SELECT		4U
#घोषणा SYNQUACER_HSSPI_IRQ_NAME_MAX		32U

काष्ठा synquacer_spi अणु
	काष्ठा device *dev;
	काष्ठा completion transfer_करोne;
	अचिन्हित पूर्णांक cs;
	अचिन्हित पूर्णांक bpw;
	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक speed;
	bool aces, rपंचांग;
	व्योम *rx_buf;
	स्थिर व्योम *tx_buf;
	काष्ठा clk *clk;
	पूर्णांक clk_src_type;
	व्योम __iomem *regs;
	u32 tx_words, rx_words;
	अचिन्हित पूर्णांक bus_width;
	अचिन्हित पूर्णांक transfer_mode;
	अक्षर rx_irq_name[SYNQUACER_HSSPI_IRQ_NAME_MAX];
	अक्षर tx_irq_name[SYNQUACER_HSSPI_IRQ_NAME_MAX];
पूर्ण;

अटल पूर्णांक पढ़ो_fअगरo(काष्ठा synquacer_spi *sspi)
अणु
	u32 len = पढ़ोl(sspi->regs + SYNQUACER_HSSPI_REG_DMSTATUS);

	len = (len >> SYNQUACER_HSSPI_DMSTATUS_RX_DATA_SHIFT) &
	       SYNQUACER_HSSPI_DMSTATUS_RX_DATA_MASK;
	len = min(len, sspi->rx_words);

	चयन (sspi->bpw) अणु
	हाल 8: अणु
		u8 *buf = sspi->rx_buf;

		ioपढ़ो8_rep(sspi->regs + SYNQUACER_HSSPI_REG_RX_FIFO,
			    buf, len);
		sspi->rx_buf = buf + len;
		अवरोध;
	पूर्ण
	हाल 16: अणु
		u16 *buf = sspi->rx_buf;

		ioपढ़ो16_rep(sspi->regs + SYNQUACER_HSSPI_REG_RX_FIFO,
			     buf, len);
		sspi->rx_buf = buf + len;
		अवरोध;
	पूर्ण
	हाल 24:
		/* fallthrough, should use 32-bits access */
	हाल 32: अणु
		u32 *buf = sspi->rx_buf;

		ioपढ़ो32_rep(sspi->regs + SYNQUACER_HSSPI_REG_RX_FIFO,
			     buf, len);
		sspi->rx_buf = buf + len;
		अवरोध;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण

	sspi->rx_words -= len;
	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_fअगरo(काष्ठा synquacer_spi *sspi)
अणु
	u32 len = पढ़ोl(sspi->regs + SYNQUACER_HSSPI_REG_DMSTATUS);

	len = (len >> SYNQUACER_HSSPI_DMSTATUS_TX_DATA_SHIFT) &
	       SYNQUACER_HSSPI_DMSTATUS_TX_DATA_MASK;
	len = min(SYNQUACER_HSSPI_FIFO_DEPTH - len,
		    sspi->tx_words);

	चयन (sspi->bpw) अणु
	हाल 8: अणु
		स्थिर u8 *buf = sspi->tx_buf;

		ioग_लिखो8_rep(sspi->regs + SYNQUACER_HSSPI_REG_TX_FIFO,
			     buf, len);
		sspi->tx_buf = buf + len;
		अवरोध;
	पूर्ण
	हाल 16: अणु
		स्थिर u16 *buf = sspi->tx_buf;

		ioग_लिखो16_rep(sspi->regs + SYNQUACER_HSSPI_REG_TX_FIFO,
			      buf, len);
		sspi->tx_buf = buf + len;
		अवरोध;
	पूर्ण
	हाल 24:
		/* fallthrough, should use 32-bits access */
	हाल 32: अणु
		स्थिर u32 *buf = sspi->tx_buf;

		ioग_लिखो32_rep(sspi->regs + SYNQUACER_HSSPI_REG_TX_FIFO,
			      buf, len);
		sspi->tx_buf = buf + len;
		अवरोध;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण

	sspi->tx_words -= len;
	वापस 0;
पूर्ण

अटल पूर्णांक synquacer_spi_config(काष्ठा spi_master *master,
				काष्ठा spi_device *spi,
				काष्ठा spi_transfer *xfer)
अणु
	काष्ठा synquacer_spi *sspi = spi_master_get_devdata(master);
	अचिन्हित पूर्णांक speed, mode, bpw, cs, bus_width, transfer_mode;
	u32 rate, val, भाग;

	/* Full Duplex only on 1-bit wide bus */
	अगर (xfer->rx_buf && xfer->tx_buf &&
	    (xfer->rx_nbits != 1 || xfer->tx_nbits != 1)) अणु
		dev_err(sspi->dev,
			"RX and TX bus widths must be 1-bit for Full-Duplex!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (xfer->tx_buf) अणु
		bus_width = xfer->tx_nbits;
		transfer_mode = SYNQUACER_HSSPI_TRANSFER_MODE_TX;
	पूर्ण अन्यथा अणु
		bus_width = xfer->rx_nbits;
		transfer_mode = SYNQUACER_HSSPI_TRANSFER_MODE_RX;
	पूर्ण

	mode = spi->mode;
	cs = spi->chip_select;
	speed = xfer->speed_hz;
	bpw = xfer->bits_per_word;

	/* वापस अगर nothing to change */
	अगर (speed == sspi->speed &&
		bus_width == sspi->bus_width && bpw == sspi->bpw &&
		mode == sspi->mode && cs == sspi->cs &&
		transfer_mode == sspi->transfer_mode) अणु
		वापस 0;
	पूर्ण

	sspi->transfer_mode = transfer_mode;
	rate = master->max_speed_hz;

	भाग = DIV_ROUND_UP(rate, speed);
	अगर (भाग > 254) अणु
		dev_err(sspi->dev, "Requested rate too low (%u)\n",
			sspi->speed);
		वापस -EINVAL;
	पूर्ण

	val = पढ़ोl(sspi->regs + SYNQUACER_HSSPI_REG_PCC(cs));
	val &= ~SYNQUACER_HSSPI_PCC_SAFESYNC;
	अगर (bpw == 8 &&	(mode & (SPI_TX_DUAL | SPI_RX_DUAL)) && भाग < 3)
		val |= SYNQUACER_HSSPI_PCC_SAFESYNC;
	अगर (bpw == 8 &&	(mode & (SPI_TX_QUAD | SPI_RX_QUAD)) && भाग < 6)
		val |= SYNQUACER_HSSPI_PCC_SAFESYNC;
	अगर (bpw == 16 && (mode & (SPI_TX_QUAD | SPI_RX_QUAD)) && भाग < 3)
		val |= SYNQUACER_HSSPI_PCC_SAFESYNC;

	अगर (mode & SPI_CPHA)
		val |= SYNQUACER_HSSPI_PCC_CPHA;
	अन्यथा
		val &= ~SYNQUACER_HSSPI_PCC_CPHA;

	अगर (mode & SPI_CPOL)
		val |= SYNQUACER_HSSPI_PCC_CPOL;
	अन्यथा
		val &= ~SYNQUACER_HSSPI_PCC_CPOL;

	अगर (mode & SPI_CS_HIGH)
		val |= SYNQUACER_HSSPI_PCC_SSPOL;
	अन्यथा
		val &= ~SYNQUACER_HSSPI_PCC_SSPOL;

	अगर (mode & SPI_LSB_FIRST)
		val |= SYNQUACER_HSSPI_PCC_Sसूची;
	अन्यथा
		val &= ~SYNQUACER_HSSPI_PCC_Sसूची;

	अगर (sspi->aces)
		val |= SYNQUACER_HSSPI_PCC_ACES;
	अन्यथा
		val &= ~SYNQUACER_HSSPI_PCC_ACES;

	अगर (sspi->rपंचांग)
		val |= SYNQUACER_HSSPI_PCC_RTM;
	अन्यथा
		val &= ~SYNQUACER_HSSPI_PCC_RTM;

	val |= (3 << SYNQUACER_HSSPI_PCC_SS2CD_SHIFT);
	val |= SYNQUACER_HSSPI_PCC_SENDIAN;

	val &= ~(SYNQUACER_HSSPI_PCC_CDRS_MASK <<
		 SYNQUACER_HSSPI_PCC_CDRS_SHIFT);
	val |= ((भाग >> 1) << SYNQUACER_HSSPI_PCC_CDRS_SHIFT);

	ग_लिखोl(val, sspi->regs + SYNQUACER_HSSPI_REG_PCC(cs));

	val = पढ़ोl(sspi->regs + SYNQUACER_HSSPI_REG_FIFOCFG);
	val &= ~(SYNQUACER_HSSPI_FIFOCFG_FIFO_WIDTH_MASK <<
		 SYNQUACER_HSSPI_FIFOCFG_FIFO_WIDTH_SHIFT);
	val |= ((bpw / 8 - 1) << SYNQUACER_HSSPI_FIFOCFG_FIFO_WIDTH_SHIFT);
	ग_लिखोl(val, sspi->regs + SYNQUACER_HSSPI_REG_FIFOCFG);

	val = पढ़ोl(sspi->regs + SYNQUACER_HSSPI_REG_DMSTART);
	val &= ~(SYNQUACER_HSSPI_DMTRP_DATA_MASK <<
		 SYNQUACER_HSSPI_DMTRP_DATA_SHIFT);

	अगर (xfer->rx_buf)
		val |= (SYNQUACER_HSSPI_DMTRP_DATA_RX <<
			SYNQUACER_HSSPI_DMTRP_DATA_SHIFT);
	अन्यथा
		val |= (SYNQUACER_HSSPI_DMTRP_DATA_TX <<
			SYNQUACER_HSSPI_DMTRP_DATA_SHIFT);

	val &= ~(3 << SYNQUACER_HSSPI_DMTRP_BUS_WIDTH_SHIFT);
	val |= ((bus_width >> 1) << SYNQUACER_HSSPI_DMTRP_BUS_WIDTH_SHIFT);
	ग_लिखोl(val, sspi->regs + SYNQUACER_HSSPI_REG_DMSTART);

	sspi->bpw = bpw;
	sspi->mode = mode;
	sspi->speed = speed;
	sspi->cs = spi->chip_select;
	sspi->bus_width = bus_width;

	वापस 0;
पूर्ण

अटल पूर्णांक synquacer_spi_transfer_one(काष्ठा spi_master *master,
				      काष्ठा spi_device *spi,
				      काष्ठा spi_transfer *xfer)
अणु
	काष्ठा synquacer_spi *sspi = spi_master_get_devdata(master);
	पूर्णांक ret;
	पूर्णांक status = 0;
	u32 words;
	u8 bpw;
	u32 val;

	val = पढ़ोl(sspi->regs + SYNQUACER_HSSPI_REG_DMSTART);
	val &= ~SYNQUACER_HSSPI_DMSTOP_STOP;
	ग_लिखोl(val, sspi->regs + SYNQUACER_HSSPI_REG_DMSTART);

	val = पढ़ोl(sspi->regs + SYNQUACER_HSSPI_REG_FIFOCFG);
	val |= SYNQUACER_HSSPI_FIFOCFG_RX_FLUSH;
	val |= SYNQUACER_HSSPI_FIFOCFG_TX_FLUSH;
	ग_लिखोl(val, sspi->regs + SYNQUACER_HSSPI_REG_FIFOCFG);

	/*
	 * See अगर we can transfer 4-bytes as 1 word
	 * to maximize the FIFO buffer efficiency.
	 */
	bpw = xfer->bits_per_word;
	अगर (bpw == 8 && !(xfer->len % 4) && !(spi->mode & SPI_LSB_FIRST))
		xfer->bits_per_word = 32;

	ret = synquacer_spi_config(master, spi, xfer);

	/* restore */
	xfer->bits_per_word = bpw;

	अगर (ret)
		वापस ret;

	reinit_completion(&sspi->transfer_करोne);

	sspi->tx_buf = xfer->tx_buf;
	sspi->rx_buf = xfer->rx_buf;

	चयन (sspi->bpw) अणु
	हाल 8:
		words = xfer->len;
		अवरोध;
	हाल 16:
		words = xfer->len / 2;
		अवरोध;
	हाल 24:
		/* fallthrough, should use 32-bits access */
	हाल 32:
		words = xfer->len / 4;
		अवरोध;
	शेष:
		dev_err(sspi->dev, "unsupported bpw: %d\n", sspi->bpw);
		वापस -EINVAL;
	पूर्ण

	अगर (xfer->tx_buf)
		sspi->tx_words = words;
	अन्यथा
		sspi->tx_words = 0;

	अगर (xfer->rx_buf)
		sspi->rx_words = words;
	अन्यथा
		sspi->rx_words = 0;

	अगर (xfer->tx_buf) अणु
		status = ग_लिखो_fअगरo(sspi);
		अगर (status < 0) अणु
			dev_err(sspi->dev, "failed write_fifo. status: 0x%x\n",
				status);
			वापस status;
		पूर्ण
	पूर्ण

	अगर (xfer->rx_buf) अणु
		val = पढ़ोl(sspi->regs + SYNQUACER_HSSPI_REG_FIFOCFG);
		val &= ~(SYNQUACER_HSSPI_FIFOCFG_RX_THRESHOLD_MASK <<
			 SYNQUACER_HSSPI_FIFOCFG_RX_THRESHOLD_SHIFT);
		val |= ((sspi->rx_words > SYNQUACER_HSSPI_FIFO_DEPTH ?
			SYNQUACER_HSSPI_FIFO_RX_THRESHOLD : sspi->rx_words) <<
			SYNQUACER_HSSPI_FIFOCFG_RX_THRESHOLD_SHIFT);
		ग_लिखोl(val, sspi->regs + SYNQUACER_HSSPI_REG_FIFOCFG);
	पूर्ण

	ग_लिखोl(~0, sspi->regs + SYNQUACER_HSSPI_REG_TXC);
	ग_लिखोl(~0, sspi->regs + SYNQUACER_HSSPI_REG_RXC);

	/* Trigger */
	val = पढ़ोl(sspi->regs + SYNQUACER_HSSPI_REG_DMSTART);
	val |= SYNQUACER_HSSPI_DMSTART_START;
	ग_लिखोl(val, sspi->regs + SYNQUACER_HSSPI_REG_DMSTART);

	अगर (xfer->tx_buf) अणु
		val = SYNQUACER_HSSPI_TXE_FIFO_EMPTY;
		ग_लिखोl(val, sspi->regs + SYNQUACER_HSSPI_REG_TXE);
		status = रुको_क्रम_completion_समयout(&sspi->transfer_करोne,
			msecs_to_jअगरfies(SYNQUACER_HSSPI_TRANSFER_TMOUT_MSEC));
		ग_लिखोl(0, sspi->regs + SYNQUACER_HSSPI_REG_TXE);
	पूर्ण

	अगर (xfer->rx_buf) अणु
		u32 buf[SYNQUACER_HSSPI_FIFO_DEPTH];

		val = SYNQUACER_HSSPI_RXE_FIFO_MORE_THAN_THRESHOLD |
		      SYNQUACER_HSSPI_RXE_SLAVE_RELEASED;
		ग_लिखोl(val, sspi->regs + SYNQUACER_HSSPI_REG_RXE);
		status = रुको_क्रम_completion_समयout(&sspi->transfer_करोne,
			msecs_to_jअगरfies(SYNQUACER_HSSPI_TRANSFER_TMOUT_MSEC));
		ग_लिखोl(0, sspi->regs + SYNQUACER_HSSPI_REG_RXE);

		/* stop RX and clean RXFIFO */
		val = पढ़ोl(sspi->regs + SYNQUACER_HSSPI_REG_DMSTART);
		val |= SYNQUACER_HSSPI_DMSTOP_STOP;
		ग_लिखोl(val, sspi->regs + SYNQUACER_HSSPI_REG_DMSTART);
		sspi->rx_buf = buf;
		sspi->rx_words = SYNQUACER_HSSPI_FIFO_DEPTH;
		पढ़ो_fअगरo(sspi);
	पूर्ण

	अगर (status < 0) अणु
		dev_err(sspi->dev, "failed to transfer. status: 0x%x\n",
			status);
		वापस status;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम synquacer_spi_set_cs(काष्ठा spi_device *spi, bool enable)
अणु
	काष्ठा synquacer_spi *sspi = spi_master_get_devdata(spi->master);
	u32 val;

	val = पढ़ोl(sspi->regs + SYNQUACER_HSSPI_REG_DMSTART);
	val &= ~(SYNQUACER_HSSPI_DMPSEL_CS_MASK <<
		 SYNQUACER_HSSPI_DMPSEL_CS_SHIFT);
	val |= spi->chip_select << SYNQUACER_HSSPI_DMPSEL_CS_SHIFT;

	अगर (!enable)
		val |= SYNQUACER_HSSPI_DMSTOP_STOP;

	ग_लिखोl(val, sspi->regs + SYNQUACER_HSSPI_REG_DMSTART);
पूर्ण

अटल पूर्णांक synquacer_spi_रुको_status_update(काष्ठा synquacer_spi *sspi,
					    bool enable)
अणु
	u32 val;
	अचिन्हित दीर्घ समयout = jअगरfies +
		msecs_to_jअगरfies(SYNQUACER_HSSPI_ENABLE_TMOUT_MSEC);

	/* रुको MES(Module Enable Status) is updated */
	करो अणु
		val = पढ़ोl(sspi->regs + SYNQUACER_HSSPI_REG_MCTRL) &
		      SYNQUACER_HSSPI_MCTRL_MES;
		अगर (enable && val)
			वापस 0;
		अगर (!enable && !val)
			वापस 0;
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयout));

	dev_err(sspi->dev, "timeout occurs in updating Module Enable Status\n");
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक synquacer_spi_enable(काष्ठा spi_master *master)
अणु
	u32 val;
	पूर्णांक status;
	काष्ठा synquacer_spi *sspi = spi_master_get_devdata(master);

	/* Disable module */
	ग_लिखोl(0, sspi->regs + SYNQUACER_HSSPI_REG_MCTRL);
	status = synquacer_spi_रुको_status_update(sspi, false);
	अगर (status < 0)
		वापस status;

	ग_लिखोl(0, sspi->regs + SYNQUACER_HSSPI_REG_TXE);
	ग_लिखोl(0, sspi->regs + SYNQUACER_HSSPI_REG_RXE);
	ग_लिखोl(~0, sspi->regs + SYNQUACER_HSSPI_REG_TXC);
	ग_लिखोl(~0, sspi->regs + SYNQUACER_HSSPI_REG_RXC);
	ग_लिखोl(~0, sspi->regs + SYNQUACER_HSSPI_REG_FAULTC);

	val = पढ़ोl(sspi->regs + SYNQUACER_HSSPI_REG_DMCFG);
	val &= ~SYNQUACER_HSSPI_DMCFG_SSDC;
	val &= ~SYNQUACER_HSSPI_DMCFG_MSTARTEN;
	ग_लिखोl(val, sspi->regs + SYNQUACER_HSSPI_REG_DMCFG);

	val = पढ़ोl(sspi->regs + SYNQUACER_HSSPI_REG_MCTRL);
	अगर (sspi->clk_src_type == SYNQUACER_HSSPI_CLOCK_SRC_IPCLK)
		val |= SYNQUACER_HSSPI_MCTRL_CDSS;
	अन्यथा
		val &= ~SYNQUACER_HSSPI_MCTRL_CDSS;

	val &= ~SYNQUACER_HSSPI_MCTRL_COMMAND_SEQUENCE_EN;
	val |= SYNQUACER_HSSPI_MCTRL_MEN;
	val |= SYNQUACER_HSSPI_MCTRL_SYNCON;

	/* Enable module */
	ग_लिखोl(val, sspi->regs + SYNQUACER_HSSPI_REG_MCTRL);
	status = synquacer_spi_रुको_status_update(sspi, true);
	अगर (status < 0)
		वापस status;

	वापस 0;
पूर्ण

अटल irqवापस_t sq_spi_rx_handler(पूर्णांक irq, व्योम *priv)
अणु
	uपूर्णांक32_t val;
	काष्ठा synquacer_spi *sspi = priv;

	val = पढ़ोl(sspi->regs + SYNQUACER_HSSPI_REG_RXF);
	अगर ((val & SYNQUACER_HSSPI_RXF_SLAVE_RELEASED) ||
	    (val & SYNQUACER_HSSPI_RXF_FIFO_MORE_THAN_THRESHOLD)) अणु
		पढ़ो_fअगरo(sspi);

		अगर (sspi->rx_words == 0) अणु
			ग_लिखोl(0, sspi->regs + SYNQUACER_HSSPI_REG_RXE);
			complete(&sspi->transfer_करोne);
		पूर्ण
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t sq_spi_tx_handler(पूर्णांक irq, व्योम *priv)
अणु
	uपूर्णांक32_t val;
	काष्ठा synquacer_spi *sspi = priv;

	val = पढ़ोl(sspi->regs + SYNQUACER_HSSPI_REG_TXF);
	अगर (val & SYNQUACER_HSSPI_TXF_FIFO_EMPTY) अणु
		अगर (sspi->tx_words == 0) अणु
			ग_लिखोl(0, sspi->regs + SYNQUACER_HSSPI_REG_TXE);
			complete(&sspi->transfer_करोne);
		पूर्ण अन्यथा अणु
			ग_लिखो_fअगरo(sspi);
		पूर्ण
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक synquacer_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा spi_master *master;
	काष्ठा synquacer_spi *sspi;
	पूर्णांक ret;
	पूर्णांक rx_irq, tx_irq;

	master = spi_alloc_master(&pdev->dev, माप(*sspi));
	अगर (!master)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, master);

	sspi = spi_master_get_devdata(master);
	sspi->dev = &pdev->dev;

	init_completion(&sspi->transfer_करोne);

	sspi->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(sspi->regs)) अणु
		ret = PTR_ERR(sspi->regs);
		जाओ put_spi;
	पूर्ण

	sspi->clk_src_type = SYNQUACER_HSSPI_CLOCK_SRC_IHCLK; /* Default */
	device_property_पढ़ो_u32(&pdev->dev, "socionext,ihclk-rate",
				 &master->max_speed_hz); /* क्रम ACPI */

	अगर (dev_of_node(&pdev->dev)) अणु
		अगर (device_property_match_string(&pdev->dev,
					 "clock-names", "iHCLK") >= 0) अणु
			sspi->clk_src_type = SYNQUACER_HSSPI_CLOCK_SRC_IHCLK;
			sspi->clk = devm_clk_get(sspi->dev, "iHCLK");
		पूर्ण अन्यथा अगर (device_property_match_string(&pdev->dev,
						"clock-names", "iPCLK") >= 0) अणु
			sspi->clk_src_type = SYNQUACER_HSSPI_CLOCK_SRC_IPCLK;
			sspi->clk = devm_clk_get(sspi->dev, "iPCLK");
		पूर्ण अन्यथा अणु
			dev_err(&pdev->dev, "specified wrong clock source\n");
			ret = -EINVAL;
			जाओ put_spi;
		पूर्ण

		अगर (IS_ERR(sspi->clk)) अणु
			ret = dev_err_probe(&pdev->dev, PTR_ERR(sspi->clk),
					    "clock not found\n");
			जाओ put_spi;
		पूर्ण

		ret = clk_prepare_enable(sspi->clk);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to enable clock (%d)\n",
				ret);
			जाओ put_spi;
		पूर्ण

		master->max_speed_hz = clk_get_rate(sspi->clk);
	पूर्ण

	अगर (!master->max_speed_hz) अणु
		dev_err(&pdev->dev, "missing clock source\n");
		ret = -EINVAL;
		जाओ disable_clk;
	पूर्ण
	master->min_speed_hz = master->max_speed_hz / 254;

	sspi->aces = device_property_पढ़ो_bool(&pdev->dev,
					       "socionext,set-aces");
	sspi->rपंचांग = device_property_पढ़ो_bool(&pdev->dev, "socionext,use-rtm");

	master->num_chipselect = SYNQUACER_HSSPI_NUM_CHIP_SELECT;

	rx_irq = platक्रमm_get_irq(pdev, 0);
	अगर (rx_irq <= 0) अणु
		ret = rx_irq;
		जाओ disable_clk;
	पूर्ण
	snम_लिखो(sspi->rx_irq_name, SYNQUACER_HSSPI_IRQ_NAME_MAX, "%s-rx",
		 dev_name(&pdev->dev));
	ret = devm_request_irq(&pdev->dev, rx_irq, sq_spi_rx_handler,
				0, sspi->rx_irq_name, sspi);
	अगर (ret) अणु
		dev_err(&pdev->dev, "request rx_irq failed (%d)\n", ret);
		जाओ disable_clk;
	पूर्ण

	tx_irq = platक्रमm_get_irq(pdev, 1);
	अगर (tx_irq <= 0) अणु
		ret = tx_irq;
		जाओ disable_clk;
	पूर्ण
	snम_लिखो(sspi->tx_irq_name, SYNQUACER_HSSPI_IRQ_NAME_MAX, "%s-tx",
		 dev_name(&pdev->dev));
	ret = devm_request_irq(&pdev->dev, tx_irq, sq_spi_tx_handler,
				0, sspi->tx_irq_name, sspi);
	अगर (ret) अणु
		dev_err(&pdev->dev, "request tx_irq failed (%d)\n", ret);
		जाओ disable_clk;
	पूर्ण

	master->dev.of_node = np;
	master->dev.fwnode = pdev->dev.fwnode;
	master->स्वतः_runसमय_pm = true;
	master->bus_num = pdev->id;

	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_TX_DUAL | SPI_RX_DUAL |
			    SPI_TX_QUAD | SPI_RX_QUAD;
	master->bits_per_word_mask = SPI_BPW_MASK(32) | SPI_BPW_MASK(24) |
				     SPI_BPW_MASK(16) | SPI_BPW_MASK(8);

	master->set_cs = synquacer_spi_set_cs;
	master->transfer_one = synquacer_spi_transfer_one;

	ret = synquacer_spi_enable(master);
	अगर (ret)
		जाओ disable_clk;

	pm_runसमय_set_active(sspi->dev);
	pm_runसमय_enable(sspi->dev);

	ret = devm_spi_रेजिस्टर_master(sspi->dev, master);
	अगर (ret)
		जाओ disable_pm;

	वापस 0;

disable_pm:
	pm_runसमय_disable(sspi->dev);
disable_clk:
	clk_disable_unprepare(sspi->clk);
put_spi:
	spi_master_put(master);

	वापस ret;
पूर्ण

अटल पूर्णांक synquacer_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा synquacer_spi *sspi = spi_master_get_devdata(master);

	pm_runसमय_disable(sspi->dev);

	clk_disable_unprepare(sspi->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused synquacer_spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा synquacer_spi *sspi = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = spi_master_suspend(master);
	अगर (ret)
		वापस ret;

	अगर (!pm_runसमय_suspended(dev))
		clk_disable_unprepare(sspi->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused synquacer_spi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा synquacer_spi *sspi = spi_master_get_devdata(master);
	पूर्णांक ret;

	अगर (!pm_runसमय_suspended(dev)) अणु
		/* Ensure reconfigure during next xfer */
		sspi->speed = 0;

		ret = clk_prepare_enable(sspi->clk);
		अगर (ret < 0) अणु
			dev_err(dev, "failed to enable clk (%d)\n",
				ret);
			वापस ret;
		पूर्ण

		ret = synquacer_spi_enable(master);
		अगर (ret) अणु
			dev_err(dev, "failed to enable spi (%d)\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = spi_master_resume(master);
	अगर (ret < 0)
		clk_disable_unprepare(sspi->clk);

	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(synquacer_spi_pm_ops, synquacer_spi_suspend,
			 synquacer_spi_resume);

अटल स्थिर काष्ठा of_device_id synquacer_spi_of_match[] = अणु
	अणु.compatible = "socionext,synquacer-spi"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, synquacer_spi_of_match);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id synquacer_hsspi_acpi_ids[] = अणु
	अणु "SCX0004" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, synquacer_hsspi_acpi_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver synquacer_spi_driver = अणु
	.driver = अणु
		.name = "synquacer-spi",
		.pm = &synquacer_spi_pm_ops,
		.of_match_table = synquacer_spi_of_match,
		.acpi_match_table = ACPI_PTR(synquacer_hsspi_acpi_ids),
	पूर्ण,
	.probe = synquacer_spi_probe,
	.हटाओ = synquacer_spi_हटाओ,
पूर्ण;
module_platक्रमm_driver(synquacer_spi_driver);

MODULE_DESCRIPTION("Socionext Synquacer HS-SPI controller driver");
MODULE_AUTHOR("Masahisa Kojima <masahisa.kojima@linaro.org>");
MODULE_AUTHOR("Jassi Brar <jaswinder.singh@linaro.org>");
MODULE_LICENSE("GPL v2");
