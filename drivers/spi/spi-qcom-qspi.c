<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2017-2018, The Linux foundation. All rights reserved.

#समावेश <linux/clk.h>
#समावेश <linux/पूर्णांकerconnect.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/pm_opp.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi-स्मृति.स>


#घोषणा QSPI_NUM_CS		2
#घोषणा QSPI_BYTES_PER_WORD	4

#घोषणा MSTR_CONFIG		0x0000
#घोषणा FULL_CYCLE_MODE		BIT(3)
#घोषणा FB_CLK_EN		BIT(4)
#घोषणा PIN_HOLDN		BIT(6)
#घोषणा PIN_WPN			BIT(7)
#घोषणा DMA_ENABLE		BIT(8)
#घोषणा BIG_ENDIAN_MODE		BIT(9)
#घोषणा SPI_MODE_MSK		0xc00
#घोषणा SPI_MODE_SHFT		10
#घोषणा CHIP_SELECT_NUM		BIT(12)
#घोषणा SBL_EN			BIT(13)
#घोषणा LPA_BASE_MSK		0x3c000
#घोषणा LPA_BASE_SHFT		14
#घोषणा TX_DATA_DELAY_MSK	0xc0000
#घोषणा TX_DATA_DELAY_SHFT	18
#घोषणा TX_CLK_DELAY_MSK	0x300000
#घोषणा TX_CLK_DELAY_SHFT	20
#घोषणा TX_CS_N_DELAY_MSK	0xc00000
#घोषणा TX_CS_N_DELAY_SHFT	22
#घोषणा TX_DATA_OE_DELAY_MSK	0x3000000
#घोषणा TX_DATA_OE_DELAY_SHFT	24

#घोषणा AHB_MASTER_CFG				0x0004
#घोषणा HMEM_TYPE_START_MID_TRANS_MSK		0x7
#घोषणा HMEM_TYPE_START_MID_TRANS_SHFT		0
#घोषणा HMEM_TYPE_LAST_TRANS_MSK		0x38
#घोषणा HMEM_TYPE_LAST_TRANS_SHFT		3
#घोषणा USE_HMEMTYPE_LAST_ON_DESC_OR_CHAIN_MSK	0xc0
#घोषणा USE_HMEMTYPE_LAST_ON_DESC_OR_CHAIN_SHFT	6
#घोषणा HMEMTYPE_READ_TRANS_MSK			0x700
#घोषणा HMEMTYPE_READ_TRANS_SHFT		8
#घोषणा HSHARED					BIT(11)
#घोषणा HINNERSHARED				BIT(12)

#घोषणा MSTR_INT_EN		0x000C
#घोषणा MSTR_INT_STATUS		0x0010
#घोषणा RESP_FIFO_UNDERRUN	BIT(0)
#घोषणा RESP_FIFO_NOT_EMPTY	BIT(1)
#घोषणा RESP_FIFO_RDY		BIT(2)
#घोषणा HRESP_FROM_NOC_ERR	BIT(3)
#घोषणा WR_FIFO_EMPTY		BIT(9)
#घोषणा WR_FIFO_FULL		BIT(10)
#घोषणा WR_FIFO_OVERRUN		BIT(11)
#घोषणा TRANSACTION_DONE	BIT(16)
#घोषणा QSPI_ERR_IRQS		(RESP_FIFO_UNDERRUN | HRESP_FROM_NOC_ERR | \
				 WR_FIFO_OVERRUN)
#घोषणा QSPI_ALL_IRQS		(QSPI_ERR_IRQS | RESP_FIFO_RDY | \
				 WR_FIFO_EMPTY | WR_FIFO_FULL | \
				 TRANSACTION_DONE)

#घोषणा PIO_XFER_CTRL		0x0014
#घोषणा REQUEST_COUNT_MSK	0xffff

#घोषणा PIO_XFER_CFG		0x0018
#घोषणा TRANSFER_सूचीECTION	BIT(0)
#घोषणा MULTI_IO_MODE_MSK	0xe
#घोषणा MULTI_IO_MODE_SHFT	1
#घोषणा TRANSFER_FRAGMENT	BIT(8)
#घोषणा SDR_1BIT		1
#घोषणा SDR_2BIT		2
#घोषणा SDR_4BIT		3
#घोषणा DDR_1BIT		5
#घोषणा DDR_2BIT		6
#घोषणा DDR_4BIT		7
#घोषणा DMA_DESC_SINGLE_SPI	1
#घोषणा DMA_DESC_DUAL_SPI	2
#घोषणा DMA_DESC_QUAD_SPI	3

#घोषणा PIO_XFER_STATUS		0x001c
#घोषणा WR_FIFO_BYTES_MSK	0xffff0000
#घोषणा WR_FIFO_BYTES_SHFT	16

#घोषणा PIO_DATAOUT_1B		0x0020
#घोषणा PIO_DATAOUT_4B		0x0024

#घोषणा RD_FIFO_CFG		0x0028
#घोषणा CONTINUOUS_MODE		BIT(0)

#घोषणा RD_FIFO_STATUS	0x002c
#घोषणा FIFO_EMPTY	BIT(11)
#घोषणा WR_CNTS_MSK	0x7f0
#घोषणा WR_CNTS_SHFT	4
#घोषणा RDY_64BYTE	BIT(3)
#घोषणा RDY_32BYTE	BIT(2)
#घोषणा RDY_16BYTE	BIT(1)
#घोषणा FIFO_RDY	BIT(0)

#घोषणा RD_FIFO_RESET		0x0030
#घोषणा RESET_FIFO		BIT(0)

#घोषणा CUR_MEM_ADDR		0x0048
#घोषणा HW_VERSION		0x004c
#घोषणा RD_FIFO			0x0050
#घोषणा SAMPLING_CLK_CFG	0x0090
#घोषणा SAMPLING_CLK_STATUS	0x0094


क्रमागत qspi_dir अणु
	QSPI_READ,
	QSPI_WRITE,
पूर्ण;

काष्ठा qspi_xfer अणु
	जोड़ अणु
		स्थिर व्योम *tx_buf;
		व्योम *rx_buf;
	पूर्ण;
	अचिन्हित पूर्णांक rem_bytes;
	अचिन्हित पूर्णांक buswidth;
	क्रमागत qspi_dir dir;
	bool is_last;
पूर्ण;

क्रमागत qspi_घड़ीs अणु
	QSPI_CLK_CORE,
	QSPI_CLK_IFACE,
	QSPI_NUM_CLKS
पूर्ण;

काष्ठा qcom_qspi अणु
	व्योम __iomem *base;
	काष्ठा device *dev;
	काष्ठा clk_bulk_data *clks;
	काष्ठा qspi_xfer xfer;
	काष्ठा icc_path *icc_path_cpu_to_qspi;
	अचिन्हित दीर्घ last_speed;
	/* Lock to protect data accessed by IRQs */
	spinlock_t lock;
पूर्ण;

अटल u32 qspi_buswidth_to_iomode(काष्ठा qcom_qspi *ctrl,
				   अचिन्हित पूर्णांक buswidth)
अणु
	चयन (buswidth) अणु
	हाल 1:
		वापस SDR_1BIT << MULTI_IO_MODE_SHFT;
	हाल 2:
		वापस SDR_2BIT << MULTI_IO_MODE_SHFT;
	हाल 4:
		वापस SDR_4BIT << MULTI_IO_MODE_SHFT;
	शेष:
		dev_warn_once(ctrl->dev,
				"Unexpected bus width: %u\n", buswidth);
		वापस SDR_1BIT << MULTI_IO_MODE_SHFT;
	पूर्ण
पूर्ण

अटल व्योम qcom_qspi_pio_xfer_cfg(काष्ठा qcom_qspi *ctrl)
अणु
	u32 pio_xfer_cfg;
	स्थिर काष्ठा qspi_xfer *xfer;

	xfer = &ctrl->xfer;
	pio_xfer_cfg = पढ़ोl(ctrl->base + PIO_XFER_CFG);
	pio_xfer_cfg &= ~TRANSFER_सूचीECTION;
	pio_xfer_cfg |= xfer->dir;
	अगर (xfer->is_last)
		pio_xfer_cfg &= ~TRANSFER_FRAGMENT;
	अन्यथा
		pio_xfer_cfg |= TRANSFER_FRAGMENT;
	pio_xfer_cfg &= ~MULTI_IO_MODE_MSK;
	pio_xfer_cfg |= qspi_buswidth_to_iomode(ctrl, xfer->buswidth);

	ग_लिखोl(pio_xfer_cfg, ctrl->base + PIO_XFER_CFG);
पूर्ण

अटल व्योम qcom_qspi_pio_xfer_ctrl(काष्ठा qcom_qspi *ctrl)
अणु
	u32 pio_xfer_ctrl;

	pio_xfer_ctrl = पढ़ोl(ctrl->base + PIO_XFER_CTRL);
	pio_xfer_ctrl &= ~REQUEST_COUNT_MSK;
	pio_xfer_ctrl |= ctrl->xfer.rem_bytes;
	ग_लिखोl(pio_xfer_ctrl, ctrl->base + PIO_XFER_CTRL);
पूर्ण

अटल व्योम qcom_qspi_pio_xfer(काष्ठा qcom_qspi *ctrl)
अणु
	u32 पूर्णांकs;

	qcom_qspi_pio_xfer_cfg(ctrl);

	/* Ack any previous पूर्णांकerrupts that might be hanging around */
	ग_लिखोl(QSPI_ALL_IRQS, ctrl->base + MSTR_INT_STATUS);

	/* Setup new पूर्णांकerrupts */
	अगर (ctrl->xfer.dir == QSPI_WRITE)
		पूर्णांकs = QSPI_ERR_IRQS | WR_FIFO_EMPTY;
	अन्यथा
		पूर्णांकs = QSPI_ERR_IRQS | RESP_FIFO_RDY;
	ग_लिखोl(पूर्णांकs, ctrl->base + MSTR_INT_EN);

	/* Kick off the transfer */
	qcom_qspi_pio_xfer_ctrl(ctrl);
पूर्ण

अटल व्योम qcom_qspi_handle_err(काष्ठा spi_master *master,
				 काष्ठा spi_message *msg)
अणु
	काष्ठा qcom_qspi *ctrl = spi_master_get_devdata(master);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ctrl->lock, flags);
	ग_लिखोl(0, ctrl->base + MSTR_INT_EN);
	ctrl->xfer.rem_bytes = 0;
	spin_unlock_irqrestore(&ctrl->lock, flags);
पूर्ण

अटल पूर्णांक qcom_qspi_set_speed(काष्ठा qcom_qspi *ctrl, अचिन्हित दीर्घ speed_hz)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक avg_bw_cpu;

	अगर (speed_hz == ctrl->last_speed)
		वापस 0;

	/* In regular operation (SBL_EN=1) core must be 4x transfer घड़ी */
	ret = dev_pm_opp_set_rate(ctrl->dev, speed_hz * 4);
	अगर (ret) अणु
		dev_err(ctrl->dev, "Failed to set core clk %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * Set BW quota क्रम CPU as driver supports FIFO mode only.
	 * We करोn't have explicit peak requirement so keep it equal to avg_bw.
	 */
	avg_bw_cpu = Bps_to_icc(speed_hz);
	ret = icc_set_bw(ctrl->icc_path_cpu_to_qspi, avg_bw_cpu, avg_bw_cpu);
	अगर (ret) अणु
		dev_err(ctrl->dev, "%s: ICC BW voting failed for cpu: %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	ctrl->last_speed = speed_hz;

	वापस 0;
पूर्ण

अटल पूर्णांक qcom_qspi_transfer_one(काष्ठा spi_master *master,
				  काष्ठा spi_device *slv,
				  काष्ठा spi_transfer *xfer)
अणु
	काष्ठा qcom_qspi *ctrl = spi_master_get_devdata(master);
	पूर्णांक ret;
	अचिन्हित दीर्घ speed_hz;
	अचिन्हित दीर्घ flags;

	speed_hz = slv->max_speed_hz;
	अगर (xfer->speed_hz)
		speed_hz = xfer->speed_hz;

	ret = qcom_qspi_set_speed(ctrl, speed_hz);
	अगर (ret)
		वापस ret;

	spin_lock_irqsave(&ctrl->lock, flags);

	/* We are half duplex, so either rx or tx will be set */
	अगर (xfer->rx_buf) अणु
		ctrl->xfer.dir = QSPI_READ;
		ctrl->xfer.buswidth = xfer->rx_nbits;
		ctrl->xfer.rx_buf = xfer->rx_buf;
	पूर्ण अन्यथा अणु
		ctrl->xfer.dir = QSPI_WRITE;
		ctrl->xfer.buswidth = xfer->tx_nbits;
		ctrl->xfer.tx_buf = xfer->tx_buf;
	पूर्ण
	ctrl->xfer.is_last = list_is_last(&xfer->transfer_list,
					  &master->cur_msg->transfers);
	ctrl->xfer.rem_bytes = xfer->len;
	qcom_qspi_pio_xfer(ctrl);

	spin_unlock_irqrestore(&ctrl->lock, flags);

	/* We'll call spi_finalize_current_transfer() when करोne */
	वापस 1;
पूर्ण

अटल पूर्णांक qcom_qspi_prepare_message(काष्ठा spi_master *master,
				     काष्ठा spi_message *message)
अणु
	u32 mstr_cfg;
	काष्ठा qcom_qspi *ctrl;
	पूर्णांक tx_data_oe_delay = 1;
	पूर्णांक tx_data_delay = 1;
	अचिन्हित दीर्घ flags;

	ctrl = spi_master_get_devdata(master);
	spin_lock_irqsave(&ctrl->lock, flags);

	mstr_cfg = पढ़ोl(ctrl->base + MSTR_CONFIG);
	mstr_cfg &= ~CHIP_SELECT_NUM;
	अगर (message->spi->chip_select)
		mstr_cfg |= CHIP_SELECT_NUM;

	mstr_cfg |= FB_CLK_EN | PIN_WPN | PIN_HOLDN | SBL_EN | FULL_CYCLE_MODE;
	mstr_cfg &= ~(SPI_MODE_MSK | TX_DATA_OE_DELAY_MSK | TX_DATA_DELAY_MSK);
	mstr_cfg |= message->spi->mode << SPI_MODE_SHFT;
	mstr_cfg |= tx_data_oe_delay << TX_DATA_OE_DELAY_SHFT;
	mstr_cfg |= tx_data_delay << TX_DATA_DELAY_SHFT;
	mstr_cfg &= ~DMA_ENABLE;

	ग_लिखोl(mstr_cfg, ctrl->base + MSTR_CONFIG);
	spin_unlock_irqrestore(&ctrl->lock, flags);

	वापस 0;
पूर्ण

अटल irqवापस_t pio_पढ़ो(काष्ठा qcom_qspi *ctrl)
अणु
	u32 rd_fअगरo_status;
	u32 rd_fअगरo;
	अचिन्हित पूर्णांक wr_cnts;
	अचिन्हित पूर्णांक bytes_to_पढ़ो;
	अचिन्हित पूर्णांक words_to_पढ़ो;
	u32 *word_buf;
	u8 *byte_buf;
	पूर्णांक i;

	rd_fअगरo_status = पढ़ोl(ctrl->base + RD_FIFO_STATUS);

	अगर (!(rd_fअगरo_status & FIFO_RDY)) अणु
		dev_dbg(ctrl->dev, "Spurious IRQ %#x\n", rd_fअगरo_status);
		वापस IRQ_NONE;
	पूर्ण

	wr_cnts = (rd_fअगरo_status & WR_CNTS_MSK) >> WR_CNTS_SHFT;
	wr_cnts = min(wr_cnts, ctrl->xfer.rem_bytes);

	words_to_पढ़ो = wr_cnts / QSPI_BYTES_PER_WORD;
	bytes_to_पढ़ो = wr_cnts % QSPI_BYTES_PER_WORD;

	अगर (words_to_पढ़ो) अणु
		word_buf = ctrl->xfer.rx_buf;
		ctrl->xfer.rem_bytes -= words_to_पढ़ो * QSPI_BYTES_PER_WORD;
		ioपढ़ो32_rep(ctrl->base + RD_FIFO, word_buf, words_to_पढ़ो);
		ctrl->xfer.rx_buf = word_buf + words_to_पढ़ो;
	पूर्ण

	अगर (bytes_to_पढ़ो) अणु
		byte_buf = ctrl->xfer.rx_buf;
		rd_fअगरo = पढ़ोl(ctrl->base + RD_FIFO);
		ctrl->xfer.rem_bytes -= bytes_to_पढ़ो;
		क्रम (i = 0; i < bytes_to_पढ़ो; i++)
			*byte_buf++ = rd_fअगरo >> (i * BITS_PER_BYTE);
		ctrl->xfer.rx_buf = byte_buf;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t pio_ग_लिखो(काष्ठा qcom_qspi *ctrl)
अणु
	स्थिर व्योम *xfer_buf = ctrl->xfer.tx_buf;
	स्थिर पूर्णांक *word_buf;
	स्थिर अक्षर *byte_buf;
	अचिन्हित पूर्णांक wr_fअगरo_bytes;
	अचिन्हित पूर्णांक wr_fअगरo_words;
	अचिन्हित पूर्णांक wr_size;
	अचिन्हित पूर्णांक rem_words;

	wr_fअगरo_bytes = पढ़ोl(ctrl->base + PIO_XFER_STATUS);
	wr_fअगरo_bytes >>= WR_FIFO_BYTES_SHFT;

	अगर (ctrl->xfer.rem_bytes < QSPI_BYTES_PER_WORD) अणु
		/* Process the last 1-3 bytes */
		wr_size = min(wr_fअगरo_bytes, ctrl->xfer.rem_bytes);
		ctrl->xfer.rem_bytes -= wr_size;

		byte_buf = xfer_buf;
		जबतक (wr_size--)
			ग_लिखोl(*byte_buf++,
			       ctrl->base + PIO_DATAOUT_1B);
		ctrl->xfer.tx_buf = byte_buf;
	पूर्ण अन्यथा अणु
		/*
		 * Process all the whole words; to keep things simple we'll
		 * just रुको क्रम the next पूर्णांकerrupt to handle the last 1-3
		 * bytes अगर we करोn't have an even number of words.
		 */
		rem_words = ctrl->xfer.rem_bytes / QSPI_BYTES_PER_WORD;
		wr_fअगरo_words = wr_fअगरo_bytes / QSPI_BYTES_PER_WORD;

		wr_size = min(rem_words, wr_fअगरo_words);
		ctrl->xfer.rem_bytes -= wr_size * QSPI_BYTES_PER_WORD;

		word_buf = xfer_buf;
		ioग_लिखो32_rep(ctrl->base + PIO_DATAOUT_4B, word_buf, wr_size);
		ctrl->xfer.tx_buf = word_buf + wr_size;

	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t qcom_qspi_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 पूर्णांक_status;
	काष्ठा qcom_qspi *ctrl = dev_id;
	irqवापस_t ret = IRQ_NONE;

	spin_lock(&ctrl->lock);

	पूर्णांक_status = पढ़ोl(ctrl->base + MSTR_INT_STATUS);
	ग_लिखोl(पूर्णांक_status, ctrl->base + MSTR_INT_STATUS);

	अगर (ctrl->xfer.dir == QSPI_WRITE) अणु
		अगर (पूर्णांक_status & WR_FIFO_EMPTY)
			ret = pio_ग_लिखो(ctrl);
	पूर्ण अन्यथा अणु
		अगर (पूर्णांक_status & RESP_FIFO_RDY)
			ret = pio_पढ़ो(ctrl);
	पूर्ण

	अगर (पूर्णांक_status & QSPI_ERR_IRQS) अणु
		अगर (पूर्णांक_status & RESP_FIFO_UNDERRUN)
			dev_err(ctrl->dev, "IRQ error: FIFO underrun\n");
		अगर (पूर्णांक_status & WR_FIFO_OVERRUN)
			dev_err(ctrl->dev, "IRQ error: FIFO overrun\n");
		अगर (पूर्णांक_status & HRESP_FROM_NOC_ERR)
			dev_err(ctrl->dev, "IRQ error: NOC response error\n");
		ret = IRQ_HANDLED;
	पूर्ण

	अगर (!ctrl->xfer.rem_bytes) अणु
		ग_लिखोl(0, ctrl->base + MSTR_INT_EN);
		spi_finalize_current_transfer(dev_get_drvdata(ctrl->dev));
	पूर्ण

	spin_unlock(&ctrl->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक qcom_qspi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा device *dev;
	काष्ठा spi_master *master;
	काष्ठा qcom_qspi *ctrl;

	dev = &pdev->dev;

	master = devm_spi_alloc_master(dev, माप(*ctrl));
	अगर (!master)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, master);

	ctrl = spi_master_get_devdata(master);

	spin_lock_init(&ctrl->lock);
	ctrl->dev = dev;
	ctrl->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(ctrl->base))
		वापस PTR_ERR(ctrl->base);

	ctrl->clks = devm_kसुस्मृति(dev, QSPI_NUM_CLKS,
				  माप(*ctrl->clks), GFP_KERNEL);
	अगर (!ctrl->clks)
		वापस -ENOMEM;

	ctrl->clks[QSPI_CLK_CORE].id = "core";
	ctrl->clks[QSPI_CLK_IFACE].id = "iface";
	ret = devm_clk_bulk_get(dev, QSPI_NUM_CLKS, ctrl->clks);
	अगर (ret)
		वापस ret;

	ctrl->icc_path_cpu_to_qspi = devm_of_icc_get(dev, "qspi-config");
	अगर (IS_ERR(ctrl->icc_path_cpu_to_qspi))
		वापस dev_err_probe(dev, PTR_ERR(ctrl->icc_path_cpu_to_qspi),
				     "Failed to get cpu path\n");

	/* Set BW vote क्रम रेजिस्टर access */
	ret = icc_set_bw(ctrl->icc_path_cpu_to_qspi, Bps_to_icc(1000),
				Bps_to_icc(1000));
	अगर (ret) अणु
		dev_err(ctrl->dev, "%s: ICC BW voting failed for cpu: %d\n",
				__func__, ret);
		वापस ret;
	पूर्ण

	ret = icc_disable(ctrl->icc_path_cpu_to_qspi);
	अगर (ret) अणु
		dev_err(ctrl->dev, "%s: ICC disable failed for cpu: %d\n",
				__func__, ret);
		वापस ret;
	पूर्ण

	ret = platक्रमm_get_irq(pdev, 0);
	अगर (ret < 0)
		वापस ret;
	ret = devm_request_irq(dev, ret, qcom_qspi_irq, 0, dev_name(dev), ctrl);
	अगर (ret) अणु
		dev_err(dev, "Failed to request irq %d\n", ret);
		वापस ret;
	पूर्ण

	master->max_speed_hz = 300000000;
	master->num_chipselect = QSPI_NUM_CS;
	master->bus_num = -1;
	master->dev.of_node = pdev->dev.of_node;
	master->mode_bits = SPI_MODE_0 |
			    SPI_TX_DUAL | SPI_RX_DUAL |
			    SPI_TX_QUAD | SPI_RX_QUAD;
	master->flags = SPI_MASTER_HALF_DUPLEX;
	master->prepare_message = qcom_qspi_prepare_message;
	master->transfer_one = qcom_qspi_transfer_one;
	master->handle_err = qcom_qspi_handle_err;
	master->स्वतः_runसमय_pm = true;

	ret = devm_pm_opp_set_clkname(&pdev->dev, "core");
	अगर (ret)
		वापस ret;
	/* OPP table is optional */
	ret = devm_pm_opp_of_add_table(&pdev->dev);
	अगर (ret && ret != -ENODEV) अणु
		dev_err(&pdev->dev, "invalid OPP table in device tree\n");
		वापस ret;
	पूर्ण

	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, 250);
	pm_runसमय_enable(dev);

	ret = spi_रेजिस्टर_master(master);
	अगर (!ret)
		वापस 0;

	pm_runसमय_disable(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक qcom_qspi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);

	/* Unरेजिस्टर _beक्रमe_ disabling pm_runसमय() so we stop transfers */
	spi_unरेजिस्टर_master(master);

	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused qcom_qspi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा qcom_qspi *ctrl = spi_master_get_devdata(master);
	पूर्णांक ret;

	/* Drop the perक्रमmance state vote */
	dev_pm_opp_set_rate(dev, 0);
	clk_bulk_disable_unprepare(QSPI_NUM_CLKS, ctrl->clks);

	ret = icc_disable(ctrl->icc_path_cpu_to_qspi);
	अगर (ret) अणु
		dev_err_ratelimited(ctrl->dev, "%s: ICC disable failed for cpu: %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused qcom_qspi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा qcom_qspi *ctrl = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = icc_enable(ctrl->icc_path_cpu_to_qspi);
	अगर (ret) अणु
		dev_err_ratelimited(ctrl->dev, "%s: ICC enable failed for cpu: %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	ret = clk_bulk_prepare_enable(QSPI_NUM_CLKS, ctrl->clks);
	अगर (ret)
		वापस ret;

	वापस dev_pm_opp_set_rate(dev, ctrl->last_speed * 4);
पूर्ण

अटल पूर्णांक __maybe_unused qcom_qspi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = spi_master_suspend(master);
	अगर (ret)
		वापस ret;

	ret = pm_runसमय_क्रमce_suspend(dev);
	अगर (ret)
		spi_master_resume(master);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused qcom_qspi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = pm_runसमय_क्रमce_resume(dev);
	अगर (ret)
		वापस ret;

	ret = spi_master_resume(master);
	अगर (ret)
		pm_runसमय_क्रमce_suspend(dev);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops qcom_qspi_dev_pm_ops = अणु
	SET_RUNTIME_PM_OPS(qcom_qspi_runसमय_suspend,
			   qcom_qspi_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(qcom_qspi_suspend, qcom_qspi_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id qcom_qspi_dt_match[] = अणु
	अणु .compatible = "qcom,qspi-v1", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, qcom_qspi_dt_match);

अटल काष्ठा platक्रमm_driver qcom_qspi_driver = अणु
	.driver = अणु
		.name		= "qcom_qspi",
		.pm		= &qcom_qspi_dev_pm_ops,
		.of_match_table = qcom_qspi_dt_match,
	पूर्ण,
	.probe = qcom_qspi_probe,
	.हटाओ = qcom_qspi_हटाओ,
पूर्ण;
module_platक्रमm_driver(qcom_qspi_driver);

MODULE_DESCRIPTION("SPI driver for QSPI cores");
MODULE_LICENSE("GPL v2");
