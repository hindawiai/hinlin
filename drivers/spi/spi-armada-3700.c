<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Marvell Armada-3700 SPI controller driver
 *
 * Copyright (C) 2016 Marvell Ltd.
 *
 * Author: Wilson Ding <dingwei@marvell.com>
 * Author: Roमुख्य Perier <roमुख्य.perier@मुक्त-electrons.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/spi/spi.h>

#घोषणा DRIVER_NAME			"armada_3700_spi"

#घोषणा A3700_SPI_MAX_SPEED_HZ		100000000
#घोषणा A3700_SPI_MAX_PRESCALE		30
#घोषणा A3700_SPI_TIMEOUT		10

/* SPI Register Offest */
#घोषणा A3700_SPI_IF_CTRL_REG		0x00
#घोषणा A3700_SPI_IF_CFG_REG		0x04
#घोषणा A3700_SPI_DATA_OUT_REG		0x08
#घोषणा A3700_SPI_DATA_IN_REG		0x0C
#घोषणा A3700_SPI_IF_INST_REG		0x10
#घोषणा A3700_SPI_IF_ADDR_REG		0x14
#घोषणा A3700_SPI_IF_RMODE_REG		0x18
#घोषणा A3700_SPI_IF_HDR_CNT_REG	0x1C
#घोषणा A3700_SPI_IF_DIN_CNT_REG	0x20
#घोषणा A3700_SPI_IF_TIME_REG		0x24
#घोषणा A3700_SPI_INT_STAT_REG		0x28
#घोषणा A3700_SPI_INT_MASK_REG		0x2C

/* A3700_SPI_IF_CTRL_REG */
#घोषणा A3700_SPI_EN			BIT(16)
#घोषणा A3700_SPI_ADDR_NOT_CONFIG	BIT(12)
#घोषणा A3700_SPI_WFIFO_OVERFLOW	BIT(11)
#घोषणा A3700_SPI_WFIFO_UNDERFLOW	BIT(10)
#घोषणा A3700_SPI_RFIFO_OVERFLOW	BIT(9)
#घोषणा A3700_SPI_RFIFO_UNDERFLOW	BIT(8)
#घोषणा A3700_SPI_WFIFO_FULL		BIT(7)
#घोषणा A3700_SPI_WFIFO_EMPTY		BIT(6)
#घोषणा A3700_SPI_RFIFO_FULL		BIT(5)
#घोषणा A3700_SPI_RFIFO_EMPTY		BIT(4)
#घोषणा A3700_SPI_WFIFO_RDY		BIT(3)
#घोषणा A3700_SPI_RFIFO_RDY		BIT(2)
#घोषणा A3700_SPI_XFER_RDY		BIT(1)
#घोषणा A3700_SPI_XFER_DONE		BIT(0)

/* A3700_SPI_IF_CFG_REG */
#घोषणा A3700_SPI_WFIFO_THRS		BIT(28)
#घोषणा A3700_SPI_RFIFO_THRS		BIT(24)
#घोषणा A3700_SPI_AUTO_CS		BIT(20)
#घोषणा A3700_SPI_DMA_RD_EN		BIT(18)
#घोषणा A3700_SPI_FIFO_MODE		BIT(17)
#घोषणा A3700_SPI_SRST			BIT(16)
#घोषणा A3700_SPI_XFER_START		BIT(15)
#घोषणा A3700_SPI_XFER_STOP		BIT(14)
#घोषणा A3700_SPI_INST_PIN		BIT(13)
#घोषणा A3700_SPI_ADDR_PIN		BIT(12)
#घोषणा A3700_SPI_DATA_PIN1		BIT(11)
#घोषणा A3700_SPI_DATA_PIN0		BIT(10)
#घोषणा A3700_SPI_FIFO_FLUSH		BIT(9)
#घोषणा A3700_SPI_RW_EN			BIT(8)
#घोषणा A3700_SPI_CLK_POL		BIT(7)
#घोषणा A3700_SPI_CLK_PHA		BIT(6)
#घोषणा A3700_SPI_BYTE_LEN		BIT(5)
#घोषणा A3700_SPI_CLK_PRESCALE		BIT(0)
#घोषणा A3700_SPI_CLK_PRESCALE_MASK	(0x1f)
#घोषणा A3700_SPI_CLK_EVEN_OFFS		(0x10)

#घोषणा A3700_SPI_WFIFO_THRS_BIT	28
#घोषणा A3700_SPI_RFIFO_THRS_BIT	24
#घोषणा A3700_SPI_FIFO_THRS_MASK	0x7

#घोषणा A3700_SPI_DATA_PIN_MASK		0x3

/* A3700_SPI_IF_HDR_CNT_REG */
#घोषणा A3700_SPI_DUMMY_CNT_BIT		12
#घोषणा A3700_SPI_DUMMY_CNT_MASK	0x7
#घोषणा A3700_SPI_RMODE_CNT_BIT		8
#घोषणा A3700_SPI_RMODE_CNT_MASK	0x3
#घोषणा A3700_SPI_ADDR_CNT_BIT		4
#घोषणा A3700_SPI_ADDR_CNT_MASK		0x7
#घोषणा A3700_SPI_INSTR_CNT_BIT		0
#घोषणा A3700_SPI_INSTR_CNT_MASK	0x3

/* A3700_SPI_IF_TIME_REG */
#घोषणा A3700_SPI_CLK_CAPT_EDGE		BIT(7)

काष्ठा a3700_spi अणु
	काष्ठा spi_master *master;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	अचिन्हित पूर्णांक irq;
	अचिन्हित पूर्णांक flags;
	bool xmit_data;
	स्थिर u8 *tx_buf;
	u8 *rx_buf;
	माप_प्रकार buf_len;
	u8 byte_len;
	u32 रुको_mask;
	काष्ठा completion करोne;
पूर्ण;

अटल u32 spireg_पढ़ो(काष्ठा a3700_spi *a3700_spi, u32 offset)
अणु
	वापस पढ़ोl(a3700_spi->base + offset);
पूर्ण

अटल व्योम spireg_ग_लिखो(काष्ठा a3700_spi *a3700_spi, u32 offset, u32 data)
अणु
	ग_लिखोl(data, a3700_spi->base + offset);
पूर्ण

अटल व्योम a3700_spi_स्वतः_cs_unset(काष्ठा a3700_spi *a3700_spi)
अणु
	u32 val;

	val = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CFG_REG);
	val &= ~A3700_SPI_AUTO_CS;
	spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_CFG_REG, val);
पूर्ण

अटल व्योम a3700_spi_activate_cs(काष्ठा a3700_spi *a3700_spi, अचिन्हित पूर्णांक cs)
अणु
	u32 val;

	val = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CTRL_REG);
	val |= (A3700_SPI_EN << cs);
	spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_CTRL_REG, val);
पूर्ण

अटल व्योम a3700_spi_deactivate_cs(काष्ठा a3700_spi *a3700_spi,
				    अचिन्हित पूर्णांक cs)
अणु
	u32 val;

	val = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CTRL_REG);
	val &= ~(A3700_SPI_EN << cs);
	spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_CTRL_REG, val);
पूर्ण

अटल पूर्णांक a3700_spi_pin_mode_set(काष्ठा a3700_spi *a3700_spi,
				  अचिन्हित पूर्णांक pin_mode, bool receiving)
अणु
	u32 val;

	val = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CFG_REG);
	val &= ~(A3700_SPI_INST_PIN | A3700_SPI_ADDR_PIN);
	val &= ~(A3700_SPI_DATA_PIN0 | A3700_SPI_DATA_PIN1);

	चयन (pin_mode) अणु
	हाल SPI_NBITS_SINGLE:
		अवरोध;
	हाल SPI_NBITS_DUAL:
		val |= A3700_SPI_DATA_PIN0;
		अवरोध;
	हाल SPI_NBITS_QUAD:
		val |= A3700_SPI_DATA_PIN1;
		/* RX during address reception uses 4-pin */
		अगर (receiving)
			val |= A3700_SPI_ADDR_PIN;
		अवरोध;
	शेष:
		dev_err(&a3700_spi->master->dev, "wrong pin mode %u", pin_mode);
		वापस -EINVAL;
	पूर्ण

	spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_CFG_REG, val);

	वापस 0;
पूर्ण

अटल व्योम a3700_spi_fअगरo_mode_set(काष्ठा a3700_spi *a3700_spi, bool enable)
अणु
	u32 val;

	val = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CFG_REG);
	अगर (enable)
		val |= A3700_SPI_FIFO_MODE;
	अन्यथा
		val &= ~A3700_SPI_FIFO_MODE;
	spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_CFG_REG, val);
पूर्ण

अटल व्योम a3700_spi_mode_set(काष्ठा a3700_spi *a3700_spi,
			       अचिन्हित पूर्णांक mode_bits)
अणु
	u32 val;

	val = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CFG_REG);

	अगर (mode_bits & SPI_CPOL)
		val |= A3700_SPI_CLK_POL;
	अन्यथा
		val &= ~A3700_SPI_CLK_POL;

	अगर (mode_bits & SPI_CPHA)
		val |= A3700_SPI_CLK_PHA;
	अन्यथा
		val &= ~A3700_SPI_CLK_PHA;

	spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_CFG_REG, val);
पूर्ण

अटल व्योम a3700_spi_घड़ी_set(काष्ठा a3700_spi *a3700_spi,
				अचिन्हित पूर्णांक speed_hz)
अणु
	u32 val;
	u32 prescale;

	prescale = DIV_ROUND_UP(clk_get_rate(a3700_spi->clk), speed_hz);

	/* For prescaler values over 15, we can only set it by steps of 2.
	 * Starting from A3700_SPI_CLK_EVEN_OFFS, we set values from 0 up to
	 * 30. We only use this range from 16 to 30.
	 */
	अगर (prescale > 15)
		prescale = A3700_SPI_CLK_EVEN_OFFS + DIV_ROUND_UP(prescale, 2);

	val = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CFG_REG);
	val = val & ~A3700_SPI_CLK_PRESCALE_MASK;

	val = val | (prescale & A3700_SPI_CLK_PRESCALE_MASK);
	spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_CFG_REG, val);

	अगर (prescale <= 2) अणु
		val = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_TIME_REG);
		val |= A3700_SPI_CLK_CAPT_EDGE;
		spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_TIME_REG, val);
	पूर्ण
पूर्ण

अटल व्योम a3700_spi_bytelen_set(काष्ठा a3700_spi *a3700_spi, अचिन्हित पूर्णांक len)
अणु
	u32 val;

	val = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CFG_REG);
	अगर (len == 4)
		val |= A3700_SPI_BYTE_LEN;
	अन्यथा
		val &= ~A3700_SPI_BYTE_LEN;
	spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_CFG_REG, val);

	a3700_spi->byte_len = len;
पूर्ण

अटल पूर्णांक a3700_spi_fअगरo_flush(काष्ठा a3700_spi *a3700_spi)
अणु
	पूर्णांक समयout = A3700_SPI_TIMEOUT;
	u32 val;

	val = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CFG_REG);
	val |= A3700_SPI_FIFO_FLUSH;
	spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_CFG_REG, val);

	जबतक (--समयout) अणु
		val = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CFG_REG);
		अगर (!(val & A3700_SPI_FIFO_FLUSH))
			वापस 0;
		udelay(1);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम a3700_spi_init(काष्ठा a3700_spi *a3700_spi)
अणु
	काष्ठा spi_master *master = a3700_spi->master;
	u32 val;
	पूर्णांक i;

	/* Reset SPI unit */
	val = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CFG_REG);
	val |= A3700_SPI_SRST;
	spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_CFG_REG, val);

	udelay(A3700_SPI_TIMEOUT);

	val = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CFG_REG);
	val &= ~A3700_SPI_SRST;
	spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_CFG_REG, val);

	/* Disable AUTO_CS and deactivate all chip-selects */
	a3700_spi_स्वतः_cs_unset(a3700_spi);
	क्रम (i = 0; i < master->num_chipselect; i++)
		a3700_spi_deactivate_cs(a3700_spi, i);

	/* Enable FIFO mode */
	a3700_spi_fअगरo_mode_set(a3700_spi, true);

	/* Set SPI mode */
	a3700_spi_mode_set(a3700_spi, master->mode_bits);

	/* Reset counters */
	spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_HDR_CNT_REG, 0);
	spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_DIN_CNT_REG, 0);

	/* Mask the पूर्णांकerrupts and clear cause bits */
	spireg_ग_लिखो(a3700_spi, A3700_SPI_INT_MASK_REG, 0);
	spireg_ग_लिखो(a3700_spi, A3700_SPI_INT_STAT_REG, ~0U);
पूर्ण

अटल irqवापस_t a3700_spi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा spi_master *master = dev_id;
	काष्ठा a3700_spi *a3700_spi;
	u32 cause;

	a3700_spi = spi_master_get_devdata(master);

	/* Get पूर्णांकerrupt causes */
	cause = spireg_पढ़ो(a3700_spi, A3700_SPI_INT_STAT_REG);

	अगर (!cause || !(a3700_spi->रुको_mask & cause))
		वापस IRQ_NONE;

	/* mask and acknowledge the SPI पूर्णांकerrupts */
	spireg_ग_लिखो(a3700_spi, A3700_SPI_INT_MASK_REG, 0);
	spireg_ग_लिखो(a3700_spi, A3700_SPI_INT_STAT_REG, cause);

	/* Wake up the transfer */
	complete(&a3700_spi->करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल bool a3700_spi_रुको_completion(काष्ठा spi_device *spi)
अणु
	काष्ठा a3700_spi *a3700_spi;
	अचिन्हित पूर्णांक समयout;
	अचिन्हित पूर्णांक ctrl_reg;
	अचिन्हित दीर्घ समयout_jअगरfies;

	a3700_spi = spi_master_get_devdata(spi->master);

	/* SPI पूर्णांकerrupt is edge-triggered, which means an पूर्णांकerrupt will
	 * be generated only when detecting a specअगरic status bit changed
	 * from '0' to '1'. So when we start रुकोing क्रम a पूर्णांकerrupt, we
	 * need to check status bit in control reg first, अगर it is alपढ़ोy 1,
	 * then we करो not need to रुको क्रम पूर्णांकerrupt
	 */
	ctrl_reg = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CTRL_REG);
	अगर (a3700_spi->रुको_mask & ctrl_reg)
		वापस true;

	reinit_completion(&a3700_spi->करोne);

	spireg_ग_लिखो(a3700_spi, A3700_SPI_INT_MASK_REG,
		     a3700_spi->रुको_mask);

	समयout_jअगरfies = msecs_to_jअगरfies(A3700_SPI_TIMEOUT);
	समयout = रुको_क्रम_completion_समयout(&a3700_spi->करोne,
					      समयout_jअगरfies);

	a3700_spi->रुको_mask = 0;

	अगर (समयout)
		वापस true;

	/* there might be the हाल that right after we checked the
	 * status bits in this routine and beक्रमe start to रुको क्रम
	 * पूर्णांकerrupt by रुको_क्रम_completion_समयout, the पूर्णांकerrupt
	 * happens, to aव्योम missing it we need to द्विगुन check
	 * status bits in control reg, अगर it is alपढ़ोy 1, then
	 * consider that we have the पूर्णांकerrupt successfully and
	 * वापस true.
	 */
	ctrl_reg = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CTRL_REG);
	अगर (a3700_spi->रुको_mask & ctrl_reg)
		वापस true;

	spireg_ग_लिखो(a3700_spi, A3700_SPI_INT_MASK_REG, 0);

	/* Timeout was reached */
	वापस false;
पूर्ण

अटल bool a3700_spi_transfer_रुको(काष्ठा spi_device *spi,
				    अचिन्हित पूर्णांक bit_mask)
अणु
	काष्ठा a3700_spi *a3700_spi;

	a3700_spi = spi_master_get_devdata(spi->master);
	a3700_spi->रुको_mask = bit_mask;

	वापस a3700_spi_रुको_completion(spi);
पूर्ण

अटल व्योम a3700_spi_fअगरo_thres_set(काष्ठा a3700_spi *a3700_spi,
				     अचिन्हित पूर्णांक bytes)
अणु
	u32 val;

	val = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CFG_REG);
	val &= ~(A3700_SPI_FIFO_THRS_MASK << A3700_SPI_RFIFO_THRS_BIT);
	val |= (bytes - 1) << A3700_SPI_RFIFO_THRS_BIT;
	val &= ~(A3700_SPI_FIFO_THRS_MASK << A3700_SPI_WFIFO_THRS_BIT);
	val |= (7 - bytes) << A3700_SPI_WFIFO_THRS_BIT;
	spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_CFG_REG, val);
पूर्ण

अटल व्योम a3700_spi_transfer_setup(काष्ठा spi_device *spi,
				     काष्ठा spi_transfer *xfer)
अणु
	काष्ठा a3700_spi *a3700_spi;

	a3700_spi = spi_master_get_devdata(spi->master);

	a3700_spi_घड़ी_set(a3700_spi, xfer->speed_hz);

	/* Use 4 bytes दीर्घ transfers. Each transfer method has its way to deal
	 * with the reमुख्यing bytes क्रम non 4-bytes aligned transfers.
	 */
	a3700_spi_bytelen_set(a3700_spi, 4);

	/* Initialize the working buffers */
	a3700_spi->tx_buf  = xfer->tx_buf;
	a3700_spi->rx_buf  = xfer->rx_buf;
	a3700_spi->buf_len = xfer->len;
पूर्ण

अटल व्योम a3700_spi_set_cs(काष्ठा spi_device *spi, bool enable)
अणु
	काष्ठा a3700_spi *a3700_spi = spi_master_get_devdata(spi->master);

	अगर (!enable)
		a3700_spi_activate_cs(a3700_spi, spi->chip_select);
	अन्यथा
		a3700_spi_deactivate_cs(a3700_spi, spi->chip_select);
पूर्ण

अटल व्योम a3700_spi_header_set(काष्ठा a3700_spi *a3700_spi)
अणु
	अचिन्हित पूर्णांक addr_cnt;
	u32 val = 0;

	/* Clear the header रेजिस्टरs */
	spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_INST_REG, 0);
	spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_ADDR_REG, 0);
	spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_RMODE_REG, 0);
	spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_HDR_CNT_REG, 0);

	/* Set header counters */
	अगर (a3700_spi->tx_buf) अणु
		/*
		 * when tx data is not 4 bytes aligned, there will be unexpected
		 * bytes out of SPI output रेजिस्टर, since it always shअगरts out
		 * as whole 4 bytes. This might cause incorrect transaction with
		 * some devices. To aव्योम that, use SPI header count feature to
		 * transfer up to 3 bytes of data first, and then make the rest
		 * of data 4-byte aligned.
		 */
		addr_cnt = a3700_spi->buf_len % 4;
		अगर (addr_cnt) अणु
			val = (addr_cnt & A3700_SPI_ADDR_CNT_MASK)
				<< A3700_SPI_ADDR_CNT_BIT;
			spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_HDR_CNT_REG, val);

			/* Update the buffer length to be transferred */
			a3700_spi->buf_len -= addr_cnt;

			/* transfer 1~3 bytes through address count */
			val = 0;
			जबतक (addr_cnt--) अणु
				val = (val << 8) | a3700_spi->tx_buf[0];
				a3700_spi->tx_buf++;
			पूर्ण
			spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_ADDR_REG, val);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक a3700_is_wfअगरo_full(काष्ठा a3700_spi *a3700_spi)
अणु
	u32 val;

	val = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CTRL_REG);
	वापस (val & A3700_SPI_WFIFO_FULL);
पूर्ण

अटल पूर्णांक a3700_spi_fअगरo_ग_लिखो(काष्ठा a3700_spi *a3700_spi)
अणु
	u32 val;

	जबतक (!a3700_is_wfअगरo_full(a3700_spi) && a3700_spi->buf_len) अणु
		val = *(u32 *)a3700_spi->tx_buf;
		spireg_ग_लिखो(a3700_spi, A3700_SPI_DATA_OUT_REG, val);
		a3700_spi->buf_len -= 4;
		a3700_spi->tx_buf += 4;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक a3700_is_rfअगरo_empty(काष्ठा a3700_spi *a3700_spi)
अणु
	u32 val = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CTRL_REG);

	वापस (val & A3700_SPI_RFIFO_EMPTY);
पूर्ण

अटल पूर्णांक a3700_spi_fअगरo_पढ़ो(काष्ठा a3700_spi *a3700_spi)
अणु
	u32 val;

	जबतक (!a3700_is_rfअगरo_empty(a3700_spi) && a3700_spi->buf_len) अणु
		val = spireg_पढ़ो(a3700_spi, A3700_SPI_DATA_IN_REG);
		अगर (a3700_spi->buf_len >= 4) अणु

			स_नकल(a3700_spi->rx_buf, &val, 4);

			a3700_spi->buf_len -= 4;
			a3700_spi->rx_buf += 4;
		पूर्ण अन्यथा अणु
			/*
			 * When reमुख्य bytes is not larger than 4, we should
			 * aव्योम memory overwriting and just ग_लिखो the left rx
			 * buffer bytes.
			 */
			जबतक (a3700_spi->buf_len) अणु
				*a3700_spi->rx_buf = val & 0xff;
				val >>= 8;

				a3700_spi->buf_len--;
				a3700_spi->rx_buf++;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम a3700_spi_transfer_पात_fअगरo(काष्ठा a3700_spi *a3700_spi)
अणु
	पूर्णांक समयout = A3700_SPI_TIMEOUT;
	u32 val;

	val = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CFG_REG);
	val |= A3700_SPI_XFER_STOP;
	spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_CFG_REG, val);

	जबतक (--समयout) अणु
		val = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CFG_REG);
		अगर (!(val & A3700_SPI_XFER_START))
			अवरोध;
		udelay(1);
	पूर्ण

	a3700_spi_fअगरo_flush(a3700_spi);

	val &= ~A3700_SPI_XFER_STOP;
	spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_CFG_REG, val);
पूर्ण

अटल पूर्णांक a3700_spi_prepare_message(काष्ठा spi_master *master,
				     काष्ठा spi_message *message)
अणु
	काष्ठा a3700_spi *a3700_spi = spi_master_get_devdata(master);
	काष्ठा spi_device *spi = message->spi;
	पूर्णांक ret;

	ret = clk_enable(a3700_spi->clk);
	अगर (ret) अणु
		dev_err(&spi->dev, "failed to enable clk with error %d\n", ret);
		वापस ret;
	पूर्ण

	/* Flush the FIFOs */
	ret = a3700_spi_fअगरo_flush(a3700_spi);
	अगर (ret)
		वापस ret;

	a3700_spi_mode_set(a3700_spi, spi->mode);

	वापस 0;
पूर्ण

अटल पूर्णांक a3700_spi_transfer_one_fअगरo(काष्ठा spi_master *master,
				  काष्ठा spi_device *spi,
				  काष्ठा spi_transfer *xfer)
अणु
	काष्ठा a3700_spi *a3700_spi = spi_master_get_devdata(master);
	पूर्णांक ret = 0, समयout = A3700_SPI_TIMEOUT;
	अचिन्हित पूर्णांक nbits = 0, byte_len;
	u32 val;

	/* Make sure we use FIFO mode */
	a3700_spi_fअगरo_mode_set(a3700_spi, true);

	/* Configure FIFO thresholds */
	byte_len = xfer->bits_per_word >> 3;
	a3700_spi_fअगरo_thres_set(a3700_spi, byte_len);

	अगर (xfer->tx_buf)
		nbits = xfer->tx_nbits;
	अन्यथा अगर (xfer->rx_buf)
		nbits = xfer->rx_nbits;

	a3700_spi_pin_mode_set(a3700_spi, nbits, xfer->rx_buf ? true : false);

	/* Flush the FIFOs */
	a3700_spi_fअगरo_flush(a3700_spi);

	/* Transfer first bytes of data when buffer is not 4-byte aligned */
	a3700_spi_header_set(a3700_spi);

	अगर (xfer->rx_buf) अणु
		/* Clear WFIFO, since it's last 2 bytes are shअगरted out during
		 * a पढ़ो operation
		 */
		spireg_ग_लिखो(a3700_spi, A3700_SPI_DATA_OUT_REG, 0);

		/* Set पढ़ो data length */
		spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_DIN_CNT_REG,
			     a3700_spi->buf_len);
		/* Start READ transfer */
		val = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CFG_REG);
		val &= ~A3700_SPI_RW_EN;
		val |= A3700_SPI_XFER_START;
		spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_CFG_REG, val);
	पूर्ण अन्यथा अगर (xfer->tx_buf) अणु
		/* Start Write transfer */
		val = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CFG_REG);
		val |= (A3700_SPI_XFER_START | A3700_SPI_RW_EN);
		spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_CFG_REG, val);

		/*
		 * If there are data to be written to the SPI device, xmit_data
		 * flag is set true; otherwise the inकाष्ठाion in SPI_INSTR करोes
		 * not require data to be written to the SPI device, then
		 * xmit_data flag is set false.
		 */
		a3700_spi->xmit_data = (a3700_spi->buf_len != 0);
	पूर्ण

	जबतक (a3700_spi->buf_len) अणु
		अगर (a3700_spi->tx_buf) अणु
			/* Wait wfअगरo पढ़ोy */
			अगर (!a3700_spi_transfer_रुको(spi,
						     A3700_SPI_WFIFO_RDY)) अणु
				dev_err(&spi->dev,
					"wait wfifo ready timed out\n");
				ret = -ETIMEDOUT;
				जाओ error;
			पूर्ण
			/* Fill up the wfअगरo */
			ret = a3700_spi_fअगरo_ग_लिखो(a3700_spi);
			अगर (ret)
				जाओ error;
		पूर्ण अन्यथा अगर (a3700_spi->rx_buf) अणु
			/* Wait rfअगरo पढ़ोy */
			अगर (!a3700_spi_transfer_रुको(spi,
						     A3700_SPI_RFIFO_RDY)) अणु
				dev_err(&spi->dev,
					"wait rfifo ready timed out\n");
				ret = -ETIMEDOUT;
				जाओ error;
			पूर्ण
			/* Drain out the rfअगरo */
			ret = a3700_spi_fअगरo_पढ़ो(a3700_spi);
			अगर (ret)
				जाओ error;
		पूर्ण
	पूर्ण

	/*
	 * Stop a ग_लिखो transfer in fअगरo mode:
	 *	- रुको all the bytes in wfअगरo to be shअगरted out
	 *	 - set XFER_STOP bit
	 *	- रुको XFER_START bit clear
	 *	- clear XFER_STOP bit
	 * Stop a पढ़ो transfer in fअगरo mode:
	 *	- the hardware is to reset the XFER_START bit
	 *	   after the number of bytes indicated in DIN_CNT
	 *	   रेजिस्टर
	 *	- just रुको XFER_START bit clear
	 */
	अगर (a3700_spi->tx_buf) अणु
		अगर (a3700_spi->xmit_data) अणु
			/*
			 * If there are data written to the SPI device, रुको
			 * until SPI_WFIFO_EMPTY is 1 to रुको क्रम all data to
			 * transfer out of ग_लिखो FIFO.
			 */
			अगर (!a3700_spi_transfer_रुको(spi,
						     A3700_SPI_WFIFO_EMPTY)) अणु
				dev_err(&spi->dev, "wait wfifo empty timed out\n");
				वापस -ETIMEDOUT;
			पूर्ण
		पूर्ण

		अगर (!a3700_spi_transfer_रुको(spi, A3700_SPI_XFER_RDY)) अणु
			dev_err(&spi->dev, "wait xfer ready timed out\n");
			वापस -ETIMEDOUT;
		पूर्ण

		val = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CFG_REG);
		val |= A3700_SPI_XFER_STOP;
		spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_CFG_REG, val);
	पूर्ण

	जबतक (--समयout) अणु
		val = spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CFG_REG);
		अगर (!(val & A3700_SPI_XFER_START))
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (समयout == 0) अणु
		dev_err(&spi->dev, "wait transfer start clear timed out\n");
		ret = -ETIMEDOUT;
		जाओ error;
	पूर्ण

	val &= ~A3700_SPI_XFER_STOP;
	spireg_ग_लिखो(a3700_spi, A3700_SPI_IF_CFG_REG, val);
	जाओ out;

error:
	a3700_spi_transfer_पात_fअगरo(a3700_spi);
out:
	spi_finalize_current_transfer(master);

	वापस ret;
पूर्ण

अटल पूर्णांक a3700_spi_transfer_one_full_duplex(काष्ठा spi_master *master,
				  काष्ठा spi_device *spi,
				  काष्ठा spi_transfer *xfer)
अणु
	काष्ठा a3700_spi *a3700_spi = spi_master_get_devdata(master);
	u32 val;

	/* Disable FIFO mode */
	a3700_spi_fअगरo_mode_set(a3700_spi, false);

	जबतक (a3700_spi->buf_len) अणु

		/* When we have less than 4 bytes to transfer, चयन to 1 byte
		 * mode. This is reset after each transfer
		 */
		अगर (a3700_spi->buf_len < 4)
			a3700_spi_bytelen_set(a3700_spi, 1);

		अगर (a3700_spi->byte_len == 1)
			val = *a3700_spi->tx_buf;
		अन्यथा
			val = *(u32 *)a3700_spi->tx_buf;

		spireg_ग_लिखो(a3700_spi, A3700_SPI_DATA_OUT_REG, val);

		/* Wait क्रम all the data to be shअगरted in / out */
		जबतक (!(spireg_पढ़ो(a3700_spi, A3700_SPI_IF_CTRL_REG) &
				A3700_SPI_XFER_DONE))
			cpu_relax();

		val = spireg_पढ़ो(a3700_spi, A3700_SPI_DATA_IN_REG);

		स_नकल(a3700_spi->rx_buf, &val, a3700_spi->byte_len);

		a3700_spi->buf_len -= a3700_spi->byte_len;
		a3700_spi->tx_buf += a3700_spi->byte_len;
		a3700_spi->rx_buf += a3700_spi->byte_len;

	पूर्ण

	spi_finalize_current_transfer(master);

	वापस 0;
पूर्ण

अटल पूर्णांक a3700_spi_transfer_one(काष्ठा spi_master *master,
				  काष्ठा spi_device *spi,
				  काष्ठा spi_transfer *xfer)
अणु
	a3700_spi_transfer_setup(spi, xfer);

	अगर (xfer->tx_buf && xfer->rx_buf)
		वापस a3700_spi_transfer_one_full_duplex(master, spi, xfer);

	वापस a3700_spi_transfer_one_fअगरo(master, spi, xfer);
पूर्ण

अटल पूर्णांक a3700_spi_unprepare_message(काष्ठा spi_master *master,
				       काष्ठा spi_message *message)
अणु
	काष्ठा a3700_spi *a3700_spi = spi_master_get_devdata(master);

	clk_disable(a3700_spi->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id a3700_spi_dt_ids[] = अणु
	अणु .compatible = "marvell,armada-3700-spi", .data = शून्य पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, a3700_spi_dt_ids);

अटल पूर्णांक a3700_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *of_node = dev->of_node;
	काष्ठा spi_master *master;
	काष्ठा a3700_spi *spi;
	u32 num_cs = 0;
	पूर्णांक irq, ret = 0;

	master = spi_alloc_master(dev, माप(*spi));
	अगर (!master) अणु
		dev_err(dev, "master allocation failed\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (of_property_पढ़ो_u32(of_node, "num-cs", &num_cs)) अणु
		dev_err(dev, "could not find num-cs\n");
		ret = -ENXIO;
		जाओ error;
	पूर्ण

	master->bus_num = pdev->id;
	master->dev.of_node = of_node;
	master->mode_bits = SPI_MODE_3;
	master->num_chipselect = num_cs;
	master->bits_per_word_mask = SPI_BPW_MASK(8) | SPI_BPW_MASK(32);
	master->prepare_message =  a3700_spi_prepare_message;
	master->transfer_one = a3700_spi_transfer_one;
	master->unprepare_message = a3700_spi_unprepare_message;
	master->set_cs = a3700_spi_set_cs;
	master->mode_bits |= (SPI_RX_DUAL | SPI_TX_DUAL |
			      SPI_RX_QUAD | SPI_TX_QUAD);

	platक्रमm_set_drvdata(pdev, master);

	spi = spi_master_get_devdata(master);

	spi->master = master;

	spi->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(spi->base)) अणु
		ret = PTR_ERR(spi->base);
		जाओ error;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = -ENXIO;
		जाओ error;
	पूर्ण
	spi->irq = irq;

	init_completion(&spi->करोne);

	spi->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(spi->clk)) अणु
		dev_err(dev, "could not find clk: %ld\n", PTR_ERR(spi->clk));
		जाओ error;
	पूर्ण

	ret = clk_prepare(spi->clk);
	अगर (ret) अणु
		dev_err(dev, "could not prepare clk: %d\n", ret);
		जाओ error;
	पूर्ण

	master->max_speed_hz = min_t(अचिन्हित दीर्घ, A3700_SPI_MAX_SPEED_HZ,
					clk_get_rate(spi->clk));
	master->min_speed_hz = DIV_ROUND_UP(clk_get_rate(spi->clk),
						A3700_SPI_MAX_PRESCALE);

	a3700_spi_init(spi);

	ret = devm_request_irq(dev, spi->irq, a3700_spi_पूर्णांकerrupt, 0,
			       dev_name(dev), master);
	अगर (ret) अणु
		dev_err(dev, "could not request IRQ: %d\n", ret);
		जाओ error_clk;
	पूर्ण

	ret = devm_spi_रेजिस्टर_master(dev, master);
	अगर (ret) अणु
		dev_err(dev, "Failed to register master\n");
		जाओ error_clk;
	पूर्ण

	वापस 0;

error_clk:
	clk_disable_unprepare(spi->clk);
error:
	spi_master_put(master);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक a3700_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा a3700_spi *spi = spi_master_get_devdata(master);

	clk_unprepare(spi->clk);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver a3700_spi_driver = अणु
	.driver = अणु
		.name	= DRIVER_NAME,
		.of_match_table = of_match_ptr(a3700_spi_dt_ids),
	पूर्ण,
	.probe		= a3700_spi_probe,
	.हटाओ		= a3700_spi_हटाओ,
पूर्ण;

module_platक्रमm_driver(a3700_spi_driver);

MODULE_DESCRIPTION("Armada-3700 SPI driver");
MODULE_AUTHOR("Wilson Ding <dingwei@marvell.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRIVER_NAME);
