<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI QSPI driver
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - https://www.ti.com
 * Author: Sourav Poddar <sourav.poddar@ti.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/omap-dma.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/sizes.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi-स्मृति.स>

काष्ठा ti_qspi_regs अणु
	u32 clkctrl;
पूर्ण;

काष्ठा ti_qspi अणु
	काष्ठा completion	transfer_complete;

	/* list synchronization */
	काष्ठा mutex            list_lock;

	काष्ठा spi_master	*master;
	व्योम __iomem            *base;
	व्योम __iomem            *mmap_base;
	माप_प्रकार			mmap_size;
	काष्ठा regmap		*ctrl_base;
	अचिन्हित पूर्णांक		ctrl_reg;
	काष्ठा clk		*fclk;
	काष्ठा device           *dev;

	काष्ठा ti_qspi_regs     ctx_reg;

	dma_addr_t		mmap_phys_base;
	dma_addr_t		rx_bb_dma_addr;
	व्योम			*rx_bb_addr;
	काष्ठा dma_chan		*rx_chan;

	u32 spi_max_frequency;
	u32 cmd;
	u32 dc;

	bool mmap_enabled;
	पूर्णांक current_cs;
पूर्ण;

#घोषणा QSPI_PID			(0x0)
#घोषणा QSPI_SYSCONFIG			(0x10)
#घोषणा QSPI_SPI_CLOCK_CNTRL_REG	(0x40)
#घोषणा QSPI_SPI_DC_REG			(0x44)
#घोषणा QSPI_SPI_CMD_REG		(0x48)
#घोषणा QSPI_SPI_STATUS_REG		(0x4c)
#घोषणा QSPI_SPI_DATA_REG		(0x50)
#घोषणा QSPI_SPI_SETUP_REG(n)		((0x54 + 4 * n))
#घोषणा QSPI_SPI_SWITCH_REG		(0x64)
#घोषणा QSPI_SPI_DATA_REG_1		(0x68)
#घोषणा QSPI_SPI_DATA_REG_2		(0x6c)
#घोषणा QSPI_SPI_DATA_REG_3		(0x70)

#घोषणा QSPI_COMPLETION_TIMEOUT		msecs_to_jअगरfies(2000)

/* Clock Control */
#घोषणा QSPI_CLK_EN			(1 << 31)
#घोषणा QSPI_CLK_DIV_MAX		0xffff

/* Command */
#घोषणा QSPI_EN_CS(n)			(n << 28)
#घोषणा QSPI_WLEN(n)			((n - 1) << 19)
#घोषणा QSPI_3_PIN			(1 << 18)
#घोषणा QSPI_RD_SNGL			(1 << 16)
#घोषणा QSPI_WR_SNGL			(2 << 16)
#घोषणा QSPI_RD_DUAL			(3 << 16)
#घोषणा QSPI_RD_QUAD			(7 << 16)
#घोषणा QSPI_INVAL			(4 << 16)
#घोषणा QSPI_FLEN(n)			((n - 1) << 0)
#घोषणा QSPI_WLEN_MAX_BITS		128
#घोषणा QSPI_WLEN_MAX_BYTES		16
#घोषणा QSPI_WLEN_MASK			QSPI_WLEN(QSPI_WLEN_MAX_BITS)

/* STATUS REGISTER */
#घोषणा BUSY				0x01
#घोषणा WC				0x02

/* Device Control */
#घोषणा QSPI_DD(m, n)			(m << (3 + n * 8))
#घोषणा QSPI_CKPHA(n)			(1 << (2 + n * 8))
#घोषणा QSPI_CSPOL(n)			(1 << (1 + n * 8))
#घोषणा QSPI_CKPOL(n)			(1 << (n * 8))

#घोषणा	QSPI_FRAME			4096

#घोषणा QSPI_AUTOSUSPEND_TIMEOUT         2000

#घोषणा MEM_CS_EN(n)			((n + 1) << 8)
#घोषणा MEM_CS_MASK			(7 << 8)

#घोषणा MM_SWITCH			0x1

#घोषणा QSPI_SETUP_RD_NORMAL		(0x0 << 12)
#घोषणा QSPI_SETUP_RD_DUAL		(0x1 << 12)
#घोषणा QSPI_SETUP_RD_QUAD		(0x3 << 12)
#घोषणा QSPI_SETUP_ADDR_SHIFT		8
#घोषणा QSPI_SETUP_DUMMY_SHIFT		10

#घोषणा QSPI_DMA_BUFFER_SIZE            SZ_64K

अटल अंतरभूत अचिन्हित दीर्घ ti_qspi_पढ़ो(काष्ठा ti_qspi *qspi,
		अचिन्हित दीर्घ reg)
अणु
	वापस पढ़ोl(qspi->base + reg);
पूर्ण

अटल अंतरभूत व्योम ti_qspi_ग_लिखो(काष्ठा ti_qspi *qspi,
		अचिन्हित दीर्घ val, अचिन्हित दीर्घ reg)
अणु
	ग_लिखोl(val, qspi->base + reg);
पूर्ण

अटल पूर्णांक ti_qspi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा ti_qspi	*qspi = spi_master_get_devdata(spi->master);
	काष्ठा ti_qspi_regs *ctx_reg = &qspi->ctx_reg;
	पूर्णांक clk_भाग = 0, ret;
	u32 clk_ctrl_reg, clk_rate, clk_mask;

	अगर (spi->master->busy) अणु
		dev_dbg(qspi->dev, "master busy doing other transfers\n");
		वापस -EBUSY;
	पूर्ण

	अगर (!qspi->spi_max_frequency) अणु
		dev_err(qspi->dev, "spi max frequency not defined\n");
		वापस -EINVAL;
	पूर्ण

	clk_rate = clk_get_rate(qspi->fclk);

	clk_भाग = DIV_ROUND_UP(clk_rate, qspi->spi_max_frequency) - 1;

	अगर (clk_भाग < 0) अणु
		dev_dbg(qspi->dev, "clock divider < 0, using /1 divider\n");
		वापस -EINVAL;
	पूर्ण

	अगर (clk_भाग > QSPI_CLK_DIV_MAX) अणु
		dev_dbg(qspi->dev, "clock divider >%d , using /%d divider\n",
				QSPI_CLK_DIV_MAX, QSPI_CLK_DIV_MAX + 1);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(qspi->dev, "hz: %d, clock divider %d\n",
			qspi->spi_max_frequency, clk_भाग);

	ret = pm_runसमय_get_sync(qspi->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(qspi->dev);
		dev_err(qspi->dev, "pm_runtime_get_sync() failed\n");
		वापस ret;
	पूर्ण

	clk_ctrl_reg = ti_qspi_पढ़ो(qspi, QSPI_SPI_CLOCK_CNTRL_REG);

	clk_ctrl_reg &= ~QSPI_CLK_EN;

	/* disable SCLK */
	ti_qspi_ग_लिखो(qspi, clk_ctrl_reg, QSPI_SPI_CLOCK_CNTRL_REG);

	/* enable SCLK */
	clk_mask = QSPI_CLK_EN | clk_भाग;
	ti_qspi_ग_लिखो(qspi, clk_mask, QSPI_SPI_CLOCK_CNTRL_REG);
	ctx_reg->clkctrl = clk_mask;

	pm_runसमय_mark_last_busy(qspi->dev);
	ret = pm_runसमय_put_स्वतःsuspend(qspi->dev);
	अगर (ret < 0) अणु
		dev_err(qspi->dev, "pm_runtime_put_autosuspend() failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ti_qspi_restore_ctx(काष्ठा ti_qspi *qspi)
अणु
	काष्ठा ti_qspi_regs *ctx_reg = &qspi->ctx_reg;

	ti_qspi_ग_लिखो(qspi, ctx_reg->clkctrl, QSPI_SPI_CLOCK_CNTRL_REG);
पूर्ण

अटल अंतरभूत u32 qspi_is_busy(काष्ठा ti_qspi *qspi)
अणु
	u32 stat;
	अचिन्हित दीर्घ समयout = jअगरfies + QSPI_COMPLETION_TIMEOUT;

	stat = ti_qspi_पढ़ो(qspi, QSPI_SPI_STATUS_REG);
	जबतक ((stat & BUSY) && समय_after(समयout, jअगरfies)) अणु
		cpu_relax();
		stat = ti_qspi_पढ़ो(qspi, QSPI_SPI_STATUS_REG);
	पूर्ण

	WARN(stat & BUSY, "qspi busy\n");
	वापस stat & BUSY;
पूर्ण

अटल अंतरभूत पूर्णांक ti_qspi_poll_wc(काष्ठा ti_qspi *qspi)
अणु
	u32 stat;
	अचिन्हित दीर्घ समयout = jअगरfies + QSPI_COMPLETION_TIMEOUT;

	करो अणु
		stat = ti_qspi_पढ़ो(qspi, QSPI_SPI_STATUS_REG);
		अगर (stat & WC)
			वापस 0;
		cpu_relax();
	पूर्ण जबतक (समय_after(समयout, jअगरfies));

	stat = ti_qspi_पढ़ो(qspi, QSPI_SPI_STATUS_REG);
	अगर (stat & WC)
		वापस 0;
	वापस  -ETIMEDOUT;
पूर्ण

अटल पूर्णांक qspi_ग_लिखो_msg(काष्ठा ti_qspi *qspi, काष्ठा spi_transfer *t,
			  पूर्णांक count)
अणु
	पूर्णांक wlen, xfer_len;
	अचिन्हित पूर्णांक cmd;
	स्थिर u8 *txbuf;
	u32 data;

	txbuf = t->tx_buf;
	cmd = qspi->cmd | QSPI_WR_SNGL;
	wlen = t->bits_per_word >> 3;	/* in bytes */
	xfer_len = wlen;

	जबतक (count) अणु
		अगर (qspi_is_busy(qspi))
			वापस -EBUSY;

		चयन (wlen) अणु
		हाल 1:
			dev_dbg(qspi->dev, "tx cmd %08x dc %08x data %02x\n",
					cmd, qspi->dc, *txbuf);
			अगर (count >= QSPI_WLEN_MAX_BYTES) अणु
				u32 *txp = (u32 *)txbuf;

				data = cpu_to_be32(*txp++);
				ग_लिखोl(data, qspi->base +
				       QSPI_SPI_DATA_REG_3);
				data = cpu_to_be32(*txp++);
				ग_लिखोl(data, qspi->base +
				       QSPI_SPI_DATA_REG_2);
				data = cpu_to_be32(*txp++);
				ग_लिखोl(data, qspi->base +
				       QSPI_SPI_DATA_REG_1);
				data = cpu_to_be32(*txp++);
				ग_लिखोl(data, qspi->base +
				       QSPI_SPI_DATA_REG);
				xfer_len = QSPI_WLEN_MAX_BYTES;
				cmd |= QSPI_WLEN(QSPI_WLEN_MAX_BITS);
			पूर्ण अन्यथा अणु
				ग_लिखोb(*txbuf, qspi->base + QSPI_SPI_DATA_REG);
				cmd = qspi->cmd | QSPI_WR_SNGL;
				xfer_len = wlen;
				cmd |= QSPI_WLEN(wlen);
			पूर्ण
			अवरोध;
		हाल 2:
			dev_dbg(qspi->dev, "tx cmd %08x dc %08x data %04x\n",
					cmd, qspi->dc, *txbuf);
			ग_लिखोw(*((u16 *)txbuf), qspi->base + QSPI_SPI_DATA_REG);
			अवरोध;
		हाल 4:
			dev_dbg(qspi->dev, "tx cmd %08x dc %08x data %08x\n",
					cmd, qspi->dc, *txbuf);
			ग_लिखोl(*((u32 *)txbuf), qspi->base + QSPI_SPI_DATA_REG);
			अवरोध;
		पूर्ण

		ti_qspi_ग_लिखो(qspi, cmd, QSPI_SPI_CMD_REG);
		अगर (ti_qspi_poll_wc(qspi)) अणु
			dev_err(qspi->dev, "write timed out\n");
			वापस -ETIMEDOUT;
		पूर्ण
		txbuf += xfer_len;
		count -= xfer_len;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qspi_पढ़ो_msg(काष्ठा ti_qspi *qspi, काष्ठा spi_transfer *t,
			 पूर्णांक count)
अणु
	पूर्णांक wlen;
	अचिन्हित पूर्णांक cmd;
	u32 rx;
	u8 rxlen, rx_wlen;
	u8 *rxbuf;

	rxbuf = t->rx_buf;
	cmd = qspi->cmd;
	चयन (t->rx_nbits) अणु
	हाल SPI_NBITS_DUAL:
		cmd |= QSPI_RD_DUAL;
		अवरोध;
	हाल SPI_NBITS_QUAD:
		cmd |= QSPI_RD_QUAD;
		अवरोध;
	शेष:
		cmd |= QSPI_RD_SNGL;
		अवरोध;
	पूर्ण
	wlen = t->bits_per_word >> 3;	/* in bytes */
	rx_wlen = wlen;

	जबतक (count) अणु
		dev_dbg(qspi->dev, "rx cmd %08x dc %08x\n", cmd, qspi->dc);
		अगर (qspi_is_busy(qspi))
			वापस -EBUSY;

		चयन (wlen) अणु
		हाल 1:
			/*
			 * Optimize the 8-bit words transfers, as used by
			 * the SPI flash devices.
			 */
			अगर (count >= QSPI_WLEN_MAX_BYTES) अणु
				rxlen = QSPI_WLEN_MAX_BYTES;
			पूर्ण अन्यथा अणु
				rxlen = min(count, 4);
			पूर्ण
			rx_wlen = rxlen << 3;
			cmd &= ~QSPI_WLEN_MASK;
			cmd |= QSPI_WLEN(rx_wlen);
			अवरोध;
		शेष:
			rxlen = wlen;
			अवरोध;
		पूर्ण

		ti_qspi_ग_लिखो(qspi, cmd, QSPI_SPI_CMD_REG);
		अगर (ti_qspi_poll_wc(qspi)) अणु
			dev_err(qspi->dev, "read timed out\n");
			वापस -ETIMEDOUT;
		पूर्ण

		चयन (wlen) अणु
		हाल 1:
			/*
			 * Optimize the 8-bit words transfers, as used by
			 * the SPI flash devices.
			 */
			अगर (count >= QSPI_WLEN_MAX_BYTES) अणु
				u32 *rxp = (u32 *) rxbuf;
				rx = पढ़ोl(qspi->base + QSPI_SPI_DATA_REG_3);
				*rxp++ = be32_to_cpu(rx);
				rx = पढ़ोl(qspi->base + QSPI_SPI_DATA_REG_2);
				*rxp++ = be32_to_cpu(rx);
				rx = पढ़ोl(qspi->base + QSPI_SPI_DATA_REG_1);
				*rxp++ = be32_to_cpu(rx);
				rx = पढ़ोl(qspi->base + QSPI_SPI_DATA_REG);
				*rxp++ = be32_to_cpu(rx);
			पूर्ण अन्यथा अणु
				u8 *rxp = rxbuf;
				rx = पढ़ोl(qspi->base + QSPI_SPI_DATA_REG);
				अगर (rx_wlen >= 8)
					*rxp++ = rx >> (rx_wlen - 8);
				अगर (rx_wlen >= 16)
					*rxp++ = rx >> (rx_wlen - 16);
				अगर (rx_wlen >= 24)
					*rxp++ = rx >> (rx_wlen - 24);
				अगर (rx_wlen >= 32)
					*rxp++ = rx;
			पूर्ण
			अवरोध;
		हाल 2:
			*((u16 *)rxbuf) = पढ़ोw(qspi->base + QSPI_SPI_DATA_REG);
			अवरोध;
		हाल 4:
			*((u32 *)rxbuf) = पढ़ोl(qspi->base + QSPI_SPI_DATA_REG);
			अवरोध;
		पूर्ण
		rxbuf += rxlen;
		count -= rxlen;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qspi_transfer_msg(काष्ठा ti_qspi *qspi, काष्ठा spi_transfer *t,
			     पूर्णांक count)
अणु
	पूर्णांक ret;

	अगर (t->tx_buf) अणु
		ret = qspi_ग_लिखो_msg(qspi, t, count);
		अगर (ret) अणु
			dev_dbg(qspi->dev, "Error while writing\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (t->rx_buf) अणु
		ret = qspi_पढ़ो_msg(qspi, t, count);
		अगर (ret) अणु
			dev_dbg(qspi->dev, "Error while reading\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ti_qspi_dma_callback(व्योम *param)
अणु
	काष्ठा ti_qspi *qspi = param;

	complete(&qspi->transfer_complete);
पूर्ण

अटल पूर्णांक ti_qspi_dma_xfer(काष्ठा ti_qspi *qspi, dma_addr_t dma_dst,
			    dma_addr_t dma_src, माप_प्रकार len)
अणु
	काष्ठा dma_chan *chan = qspi->rx_chan;
	dma_cookie_t cookie;
	क्रमागत dma_ctrl_flags flags = DMA_CTRL_ACK | DMA_PREP_INTERRUPT;
	काष्ठा dma_async_tx_descriptor *tx;
	पूर्णांक ret;

	tx = dmaengine_prep_dma_स_नकल(chan, dma_dst, dma_src, len, flags);
	अगर (!tx) अणु
		dev_err(qspi->dev, "device_prep_dma_memcpy error\n");
		वापस -EIO;
	पूर्ण

	tx->callback = ti_qspi_dma_callback;
	tx->callback_param = qspi;
	cookie = tx->tx_submit(tx);
	reinit_completion(&qspi->transfer_complete);

	ret = dma_submit_error(cookie);
	अगर (ret) अणु
		dev_err(qspi->dev, "dma_submit_error %d\n", cookie);
		वापस -EIO;
	पूर्ण

	dma_async_issue_pending(chan);
	ret = रुको_क्रम_completion_समयout(&qspi->transfer_complete,
					  msecs_to_jअगरfies(len));
	अगर (ret <= 0) अणु
		dmaengine_terminate_sync(chan);
		dev_err(qspi->dev, "DMA wait_for_completion_timeout\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ti_qspi_dma_bounce_buffer(काष्ठा ti_qspi *qspi, loff_t offs,
				     व्योम *to, माप_प्रकार पढ़ोsize)
अणु
	dma_addr_t dma_src = qspi->mmap_phys_base + offs;
	पूर्णांक ret = 0;

	/*
	 * Use bounce buffer as FS like jffs2, ubअगरs may pass
	 * buffers that करोes not beदीर्घ to kernel lowmem region.
	 */
	जबतक (पढ़ोsize != 0) अणु
		माप_प्रकार xfer_len = min_t(माप_प्रकार, QSPI_DMA_BUFFER_SIZE,
					पढ़ोsize);

		ret = ti_qspi_dma_xfer(qspi, qspi->rx_bb_dma_addr,
				       dma_src, xfer_len);
		अगर (ret != 0)
			वापस ret;
		स_नकल(to, qspi->rx_bb_addr, xfer_len);
		पढ़ोsize -= xfer_len;
		dma_src += xfer_len;
		to += xfer_len;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ti_qspi_dma_xfer_sg(काष्ठा ti_qspi *qspi, काष्ठा sg_table rx_sg,
			       loff_t from)
अणु
	काष्ठा scatterlist *sg;
	dma_addr_t dma_src = qspi->mmap_phys_base + from;
	dma_addr_t dma_dst;
	पूर्णांक i, len, ret;

	क्रम_each_sg(rx_sg.sgl, sg, rx_sg.nents, i) अणु
		dma_dst = sg_dma_address(sg);
		len = sg_dma_len(sg);
		ret = ti_qspi_dma_xfer(qspi, dma_dst, dma_src, len);
		अगर (ret)
			वापस ret;
		dma_src += len;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ti_qspi_enable_memory_map(काष्ठा spi_device *spi)
अणु
	काष्ठा ti_qspi  *qspi = spi_master_get_devdata(spi->master);

	ti_qspi_ग_लिखो(qspi, MM_SWITCH, QSPI_SPI_SWITCH_REG);
	अगर (qspi->ctrl_base) अणु
		regmap_update_bits(qspi->ctrl_base, qspi->ctrl_reg,
				   MEM_CS_MASK,
				   MEM_CS_EN(spi->chip_select));
	पूर्ण
	qspi->mmap_enabled = true;
	qspi->current_cs = spi->chip_select;
पूर्ण

अटल व्योम ti_qspi_disable_memory_map(काष्ठा spi_device *spi)
अणु
	काष्ठा ti_qspi  *qspi = spi_master_get_devdata(spi->master);

	ti_qspi_ग_लिखो(qspi, 0, QSPI_SPI_SWITCH_REG);
	अगर (qspi->ctrl_base)
		regmap_update_bits(qspi->ctrl_base, qspi->ctrl_reg,
				   MEM_CS_MASK, 0);
	qspi->mmap_enabled = false;
	qspi->current_cs = -1;
पूर्ण

अटल व्योम ti_qspi_setup_mmap_पढ़ो(काष्ठा spi_device *spi, u8 opcode,
				    u8 data_nbits, u8 addr_width,
				    u8 dummy_bytes)
अणु
	काष्ठा ti_qspi  *qspi = spi_master_get_devdata(spi->master);
	u32 memval = opcode;

	चयन (data_nbits) अणु
	हाल SPI_NBITS_QUAD:
		memval |= QSPI_SETUP_RD_QUAD;
		अवरोध;
	हाल SPI_NBITS_DUAL:
		memval |= QSPI_SETUP_RD_DUAL;
		अवरोध;
	शेष:
		memval |= QSPI_SETUP_RD_NORMAL;
		अवरोध;
	पूर्ण
	memval |= ((addr_width - 1) << QSPI_SETUP_ADDR_SHIFT |
		   dummy_bytes << QSPI_SETUP_DUMMY_SHIFT);
	ti_qspi_ग_लिखो(qspi, memval,
		      QSPI_SPI_SETUP_REG(spi->chip_select));
पूर्ण

अटल पूर्णांक ti_qspi_adjust_op_size(काष्ठा spi_mem *mem, काष्ठा spi_mem_op *op)
अणु
	काष्ठा ti_qspi *qspi = spi_controller_get_devdata(mem->spi->master);
	माप_प्रकार max_len;

	अगर (op->data.dir == SPI_MEM_DATA_IN) अणु
		अगर (op->addr.val < qspi->mmap_size) अणु
			/* Limit MMIO to the mmaped region */
			अगर (op->addr.val + op->data.nbytes > qspi->mmap_size) अणु
				max_len = qspi->mmap_size - op->addr.val;
				op->data.nbytes = min((माप_प्रकार) op->data.nbytes,
						      max_len);
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * Use fallback mode (SW generated transfers) above the
			 * mmaped region.
			 * Adjust size to comply with the QSPI max frame length.
			 */
			max_len = QSPI_FRAME;
			max_len -= 1 + op->addr.nbytes + op->dummy.nbytes;
			op->data.nbytes = min((माप_प्रकार) op->data.nbytes,
					      max_len);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ti_qspi_exec_mem_op(काष्ठा spi_mem *mem,
			       स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा ti_qspi *qspi = spi_master_get_devdata(mem->spi->master);
	u32 from = 0;
	पूर्णांक ret = 0;

	/* Only optimize पढ़ो path. */
	अगर (!op->data.nbytes || op->data.dir != SPI_MEM_DATA_IN ||
	    !op->addr.nbytes || op->addr.nbytes > 4)
		वापस -ENOTSUPP;

	/* Address exceeds MMIO winकरोw size, fall back to regular mode. */
	from = op->addr.val;
	अगर (from + op->data.nbytes > qspi->mmap_size)
		वापस -ENOTSUPP;

	mutex_lock(&qspi->list_lock);

	अगर (!qspi->mmap_enabled || qspi->current_cs != mem->spi->chip_select)
		ti_qspi_enable_memory_map(mem->spi);
	ti_qspi_setup_mmap_पढ़ो(mem->spi, op->cmd.opcode, op->data.buswidth,
				op->addr.nbytes, op->dummy.nbytes);

	अगर (qspi->rx_chan) अणु
		काष्ठा sg_table sgt;

		अगर (virt_addr_valid(op->data.buf.in) &&
		    !spi_controller_dma_map_mem_op_data(mem->spi->master, op,
							&sgt)) अणु
			ret = ti_qspi_dma_xfer_sg(qspi, sgt, from);
			spi_controller_dma_unmap_mem_op_data(mem->spi->master,
							     op, &sgt);
		पूर्ण अन्यथा अणु
			ret = ti_qspi_dma_bounce_buffer(qspi, from,
							op->data.buf.in,
							op->data.nbytes);
		पूर्ण
	पूर्ण अन्यथा अणु
		स_नकल_fromio(op->data.buf.in, qspi->mmap_base + from,
			      op->data.nbytes);
	पूर्ण

	mutex_unlock(&qspi->list_lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा spi_controller_mem_ops ti_qspi_mem_ops = अणु
	.exec_op = ti_qspi_exec_mem_op,
	.adjust_op_size = ti_qspi_adjust_op_size,
पूर्ण;

अटल पूर्णांक ti_qspi_start_transfer_one(काष्ठा spi_master *master,
		काष्ठा spi_message *m)
अणु
	काष्ठा ti_qspi *qspi = spi_master_get_devdata(master);
	काष्ठा spi_device *spi = m->spi;
	काष्ठा spi_transfer *t;
	पूर्णांक status = 0, ret;
	अचिन्हित पूर्णांक frame_len_words, transfer_len_words;
	पूर्णांक wlen;

	/* setup device control reg */
	qspi->dc = 0;

	अगर (spi->mode & SPI_CPHA)
		qspi->dc |= QSPI_CKPHA(spi->chip_select);
	अगर (spi->mode & SPI_CPOL)
		qspi->dc |= QSPI_CKPOL(spi->chip_select);
	अगर (spi->mode & SPI_CS_HIGH)
		qspi->dc |= QSPI_CSPOL(spi->chip_select);

	frame_len_words = 0;
	list_क्रम_each_entry(t, &m->transfers, transfer_list)
		frame_len_words += t->len / (t->bits_per_word >> 3);
	frame_len_words = min_t(अचिन्हित पूर्णांक, frame_len_words, QSPI_FRAME);

	/* setup command reg */
	qspi->cmd = 0;
	qspi->cmd |= QSPI_EN_CS(spi->chip_select);
	qspi->cmd |= QSPI_FLEN(frame_len_words);

	ti_qspi_ग_लिखो(qspi, qspi->dc, QSPI_SPI_DC_REG);

	mutex_lock(&qspi->list_lock);

	अगर (qspi->mmap_enabled)
		ti_qspi_disable_memory_map(spi);

	list_क्रम_each_entry(t, &m->transfers, transfer_list) अणु
		qspi->cmd = ((qspi->cmd & ~QSPI_WLEN_MASK) |
			     QSPI_WLEN(t->bits_per_word));

		wlen = t->bits_per_word >> 3;
		transfer_len_words = min(t->len / wlen, frame_len_words);

		ret = qspi_transfer_msg(qspi, t, transfer_len_words * wlen);
		अगर (ret) अणु
			dev_dbg(qspi->dev, "transfer message failed\n");
			mutex_unlock(&qspi->list_lock);
			वापस -EINVAL;
		पूर्ण

		m->actual_length += transfer_len_words * wlen;
		frame_len_words -= transfer_len_words;
		अगर (frame_len_words == 0)
			अवरोध;
	पूर्ण

	mutex_unlock(&qspi->list_lock);

	ti_qspi_ग_लिखो(qspi, qspi->cmd | QSPI_INVAL, QSPI_SPI_CMD_REG);
	m->status = status;
	spi_finalize_current_message(master);

	वापस status;
पूर्ण

अटल पूर्णांक ti_qspi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा ti_qspi      *qspi;

	qspi = dev_get_drvdata(dev);
	ti_qspi_restore_ctx(qspi);

	वापस 0;
पूर्ण

अटल व्योम ti_qspi_dma_cleanup(काष्ठा ti_qspi *qspi)
अणु
	अगर (qspi->rx_bb_addr)
		dma_मुक्त_coherent(qspi->dev, QSPI_DMA_BUFFER_SIZE,
				  qspi->rx_bb_addr,
				  qspi->rx_bb_dma_addr);

	अगर (qspi->rx_chan)
		dma_release_channel(qspi->rx_chan);
पूर्ण

अटल स्थिर काष्ठा of_device_id ti_qspi_match[] = अणु
	अणु.compatible = "ti,dra7xxx-qspi" पूर्ण,
	अणु.compatible = "ti,am4372-qspi" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_qspi_match);

अटल पूर्णांक ti_qspi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा  ti_qspi *qspi;
	काष्ठा spi_master *master;
	काष्ठा resource         *r, *res_mmap;
	काष्ठा device_node *np = pdev->dev.of_node;
	u32 max_freq;
	पूर्णांक ret = 0, num_cs, irq;
	dma_cap_mask_t mask;

	master = spi_alloc_master(&pdev->dev, माप(*qspi));
	अगर (!master)
		वापस -ENOMEM;

	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_RX_DUAL | SPI_RX_QUAD;

	master->flags = SPI_MASTER_HALF_DUPLEX;
	master->setup = ti_qspi_setup;
	master->स्वतः_runसमय_pm = true;
	master->transfer_one_message = ti_qspi_start_transfer_one;
	master->dev.of_node = pdev->dev.of_node;
	master->bits_per_word_mask = SPI_BPW_MASK(32) | SPI_BPW_MASK(16) |
				     SPI_BPW_MASK(8);
	master->mem_ops = &ti_qspi_mem_ops;

	अगर (!of_property_पढ़ो_u32(np, "num-cs", &num_cs))
		master->num_chipselect = num_cs;

	qspi = spi_master_get_devdata(master);
	qspi->master = master;
	qspi->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, qspi);

	r = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "qspi_base");
	अगर (r == शून्य) अणु
		r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
		अगर (r == शून्य) अणु
			dev_err(&pdev->dev, "missing platform data\n");
			ret = -ENODEV;
			जाओ मुक्त_master;
		पूर्ण
	पूर्ण

	res_mmap = platक्रमm_get_resource_byname(pdev,
			IORESOURCE_MEM, "qspi_mmap");
	अगर (res_mmap == शून्य) अणु
		res_mmap = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
		अगर (res_mmap == शून्य) अणु
			dev_err(&pdev->dev,
				"memory mapped resource not required\n");
		पूर्ण
	पूर्ण

	अगर (res_mmap)
		qspi->mmap_size = resource_size(res_mmap);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0) अणु
		ret = irq;
		जाओ मुक्त_master;
	पूर्ण

	mutex_init(&qspi->list_lock);

	qspi->base = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(qspi->base)) अणु
		ret = PTR_ERR(qspi->base);
		जाओ मुक्त_master;
	पूर्ण


	अगर (of_property_पढ़ो_bool(np, "syscon-chipselects")) अणु
		qspi->ctrl_base =
		syscon_regmap_lookup_by_phandle(np,
						"syscon-chipselects");
		अगर (IS_ERR(qspi->ctrl_base)) अणु
			ret = PTR_ERR(qspi->ctrl_base);
			जाओ मुक्त_master;
		पूर्ण
		ret = of_property_पढ़ो_u32_index(np,
						 "syscon-chipselects",
						 1, &qspi->ctrl_reg);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"couldn't get ctrl_mod reg index\n");
			जाओ मुक्त_master;
		पूर्ण
	पूर्ण

	qspi->fclk = devm_clk_get(&pdev->dev, "fck");
	अगर (IS_ERR(qspi->fclk)) अणु
		ret = PTR_ERR(qspi->fclk);
		dev_err(&pdev->dev, "could not get clk: %d\n", ret);
	पूर्ण

	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, QSPI_AUTOSUSPEND_TIMEOUT);
	pm_runसमय_enable(&pdev->dev);

	अगर (!of_property_पढ़ो_u32(np, "spi-max-frequency", &max_freq))
		qspi->spi_max_frequency = max_freq;

	dma_cap_zero(mask);
	dma_cap_set(DMA_MEMCPY, mask);

	qspi->rx_chan = dma_request_chan_by_mask(&mask);
	अगर (IS_ERR(qspi->rx_chan)) अणु
		dev_err(qspi->dev,
			"No Rx DMA available, trying mmap mode\n");
		qspi->rx_chan = शून्य;
		ret = 0;
		जाओ no_dma;
	पूर्ण
	qspi->rx_bb_addr = dma_alloc_coherent(qspi->dev,
					      QSPI_DMA_BUFFER_SIZE,
					      &qspi->rx_bb_dma_addr,
					      GFP_KERNEL | GFP_DMA);
	अगर (!qspi->rx_bb_addr) अणु
		dev_err(qspi->dev,
			"dma_alloc_coherent failed, using PIO mode\n");
		dma_release_channel(qspi->rx_chan);
		जाओ no_dma;
	पूर्ण
	master->dma_rx = qspi->rx_chan;
	init_completion(&qspi->transfer_complete);
	अगर (res_mmap)
		qspi->mmap_phys_base = (dma_addr_t)res_mmap->start;

no_dma:
	अगर (!qspi->rx_chan && res_mmap) अणु
		qspi->mmap_base = devm_ioremap_resource(&pdev->dev, res_mmap);
		अगर (IS_ERR(qspi->mmap_base)) अणु
			dev_info(&pdev->dev,
				 "mmap failed with error %ld using PIO mode\n",
				 PTR_ERR(qspi->mmap_base));
			qspi->mmap_base = शून्य;
			master->mem_ops = शून्य;
		पूर्ण
	पूर्ण
	qspi->mmap_enabled = false;
	qspi->current_cs = -1;

	ret = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (!ret)
		वापस 0;

	ti_qspi_dma_cleanup(qspi);

	pm_runसमय_disable(&pdev->dev);
मुक्त_master:
	spi_master_put(master);
	वापस ret;
पूर्ण

अटल पूर्णांक ti_qspi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ti_qspi *qspi = platक्रमm_get_drvdata(pdev);
	पूर्णांक rc;

	rc = spi_master_suspend(qspi->master);
	अगर (rc)
		वापस rc;

	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	ti_qspi_dma_cleanup(qspi);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ti_qspi_pm_ops = अणु
	.runसमय_resume = ti_qspi_runसमय_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver ti_qspi_driver = अणु
	.probe	= ti_qspi_probe,
	.हटाओ = ti_qspi_हटाओ,
	.driver = अणु
		.name	= "ti-qspi",
		.pm =   &ti_qspi_pm_ops,
		.of_match_table = ti_qspi_match,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(ti_qspi_driver);

MODULE_AUTHOR("Sourav Poddar <sourav.poddar@ti.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("TI QSPI controller driver");
MODULE_ALIAS("platform:ti-qspi");
