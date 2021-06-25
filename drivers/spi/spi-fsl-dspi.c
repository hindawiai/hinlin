<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright 2013 Freescale Semiconductor, Inc.
// Copyright 2020 NXP
//
// Freescale DSPI driver
// This file contains a driver क्रम the Freescale DSPI

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi-fsl-dspi.h>

#घोषणा DRIVER_NAME			"fsl-dspi"

#घोषणा SPI_MCR				0x00
#घोषणा SPI_MCR_MASTER			BIT(31)
#घोषणा SPI_MCR_PCSIS(x)		((x) << 16)
#घोषणा SPI_MCR_CLR_TXF			BIT(11)
#घोषणा SPI_MCR_CLR_RXF			BIT(10)
#घोषणा SPI_MCR_XSPI			BIT(3)
#घोषणा SPI_MCR_DIS_TXF			BIT(13)
#घोषणा SPI_MCR_DIS_RXF			BIT(12)
#घोषणा SPI_MCR_HALT			BIT(0)

#घोषणा SPI_TCR				0x08
#घोषणा SPI_TCR_GET_TCNT(x)		(((x) & GENMASK(31, 16)) >> 16)

#घोषणा SPI_CTAR(x)			(0x0c + (((x) & GENMASK(1, 0)) * 4))
#घोषणा SPI_CTAR_FMSZ(x)		(((x) << 27) & GENMASK(30, 27))
#घोषणा SPI_CTAR_CPOL			BIT(26)
#घोषणा SPI_CTAR_CPHA			BIT(25)
#घोषणा SPI_CTAR_LSBFE			BIT(24)
#घोषणा SPI_CTAR_PCSSCK(x)		(((x) << 22) & GENMASK(23, 22))
#घोषणा SPI_CTAR_PASC(x)		(((x) << 20) & GENMASK(21, 20))
#घोषणा SPI_CTAR_PDT(x)			(((x) << 18) & GENMASK(19, 18))
#घोषणा SPI_CTAR_PBR(x)			(((x) << 16) & GENMASK(17, 16))
#घोषणा SPI_CTAR_CSSCK(x)		(((x) << 12) & GENMASK(15, 12))
#घोषणा SPI_CTAR_ASC(x)			(((x) << 8) & GENMASK(11, 8))
#घोषणा SPI_CTAR_DT(x)			(((x) << 4) & GENMASK(7, 4))
#घोषणा SPI_CTAR_BR(x)			((x) & GENMASK(3, 0))
#घोषणा SPI_CTAR_SCALE_BITS		0xf

#घोषणा SPI_CTAR0_SLAVE			0x0c

#घोषणा SPI_SR				0x2c
#घोषणा SPI_SR_TCFQF			BIT(31)
#घोषणा SPI_SR_TFUF			BIT(27)
#घोषणा SPI_SR_TFFF			BIT(25)
#घोषणा SPI_SR_CMDTCF			BIT(23)
#घोषणा SPI_SR_SPEF			BIT(21)
#घोषणा SPI_SR_RFOF			BIT(19)
#घोषणा SPI_SR_TFIWF			BIT(18)
#घोषणा SPI_SR_RFDF			BIT(17)
#घोषणा SPI_SR_CMDFFF			BIT(16)
#घोषणा SPI_SR_CLEAR			(SPI_SR_TCFQF | \
					SPI_SR_TFUF | SPI_SR_TFFF | \
					SPI_SR_CMDTCF | SPI_SR_SPEF | \
					SPI_SR_RFOF | SPI_SR_TFIWF | \
					SPI_SR_RFDF | SPI_SR_CMDFFF)

#घोषणा SPI_RSER_TFFFE			BIT(25)
#घोषणा SPI_RSER_TFFFD			BIT(24)
#घोषणा SPI_RSER_RFDFE			BIT(17)
#घोषणा SPI_RSER_RFDFD			BIT(16)

#घोषणा SPI_RSER			0x30
#घोषणा SPI_RSER_TCFQE			BIT(31)
#घोषणा SPI_RSER_CMDTCFE		BIT(23)

#घोषणा SPI_PUSHR			0x34
#घोषणा SPI_PUSHR_CMD_CONT		BIT(15)
#घोषणा SPI_PUSHR_CMD_CTAS(x)		(((x) << 12 & GENMASK(14, 12)))
#घोषणा SPI_PUSHR_CMD_EOQ		BIT(11)
#घोषणा SPI_PUSHR_CMD_CTCNT		BIT(10)
#घोषणा SPI_PUSHR_CMD_PCS(x)		(BIT(x) & GENMASK(5, 0))

#घोषणा SPI_PUSHR_SLAVE			0x34

#घोषणा SPI_POPR			0x38

#घोषणा SPI_TXFR0			0x3c
#घोषणा SPI_TXFR1			0x40
#घोषणा SPI_TXFR2			0x44
#घोषणा SPI_TXFR3			0x48
#घोषणा SPI_RXFR0			0x7c
#घोषणा SPI_RXFR1			0x80
#घोषणा SPI_RXFR2			0x84
#घोषणा SPI_RXFR3			0x88

#घोषणा SPI_CTARE(x)			(0x11c + (((x) & GENMASK(1, 0)) * 4))
#घोषणा SPI_CTARE_FMSZE(x)		(((x) & 0x1) << 16)
#घोषणा SPI_CTARE_DTCP(x)		((x) & 0x7ff)

#घोषणा SPI_SREX			0x13c

#घोषणा SPI_FRAME_BITS(bits)		SPI_CTAR_FMSZ((bits) - 1)
#घोषणा SPI_FRAME_EBITS(bits)		SPI_CTARE_FMSZE(((bits) - 1) >> 4)

#घोषणा DMA_COMPLETION_TIMEOUT		msecs_to_jअगरfies(3000)

काष्ठा chip_data अणु
	u32			ctar_val;
पूर्ण;

क्रमागत dspi_trans_mode अणु
	DSPI_XSPI_MODE,
	DSPI_DMA_MODE,
पूर्ण;

काष्ठा fsl_dspi_devtype_data अणु
	क्रमागत dspi_trans_mode	trans_mode;
	u8			max_घड़ी_factor;
	पूर्णांक			fअगरo_size;
पूर्ण;

क्रमागत अणु
	LS1021A,
	LS1012A,
	LS1028A,
	LS1043A,
	LS1046A,
	LS2080A,
	LS2085A,
	LX2160A,
	MCF5441X,
	VF610,
पूर्ण;

अटल स्थिर काष्ठा fsl_dspi_devtype_data devtype_data[] = अणु
	[VF610] = अणु
		.trans_mode		= DSPI_DMA_MODE,
		.max_घड़ी_factor	= 2,
		.fअगरo_size		= 4,
	पूर्ण,
	[LS1021A] = अणु
		/* Has A-011218 DMA erratum */
		.trans_mode		= DSPI_XSPI_MODE,
		.max_घड़ी_factor	= 8,
		.fअगरo_size		= 4,
	पूर्ण,
	[LS1012A] = अणु
		/* Has A-011218 DMA erratum */
		.trans_mode		= DSPI_XSPI_MODE,
		.max_घड़ी_factor	= 8,
		.fअगरo_size		= 16,
	पूर्ण,
	[LS1028A] = अणु
		.trans_mode		= DSPI_XSPI_MODE,
		.max_घड़ी_factor	= 8,
		.fअगरo_size		= 4,
	पूर्ण,
	[LS1043A] = अणु
		/* Has A-011218 DMA erratum */
		.trans_mode		= DSPI_XSPI_MODE,
		.max_घड़ी_factor	= 8,
		.fअगरo_size		= 16,
	पूर्ण,
	[LS1046A] = अणु
		/* Has A-011218 DMA erratum */
		.trans_mode		= DSPI_XSPI_MODE,
		.max_घड़ी_factor	= 8,
		.fअगरo_size		= 16,
	पूर्ण,
	[LS2080A] = अणु
		.trans_mode		= DSPI_XSPI_MODE,
		.max_घड़ी_factor	= 8,
		.fअगरo_size		= 4,
	पूर्ण,
	[LS2085A] = अणु
		.trans_mode		= DSPI_XSPI_MODE,
		.max_घड़ी_factor	= 8,
		.fअगरo_size		= 4,
	पूर्ण,
	[LX2160A] = अणु
		.trans_mode		= DSPI_XSPI_MODE,
		.max_घड़ी_factor	= 8,
		.fअगरo_size		= 4,
	पूर्ण,
	[MCF5441X] = अणु
		.trans_mode		= DSPI_DMA_MODE,
		.max_घड़ी_factor	= 8,
		.fअगरo_size		= 16,
	पूर्ण,
पूर्ण;

काष्ठा fsl_dspi_dma अणु
	u32					*tx_dma_buf;
	काष्ठा dma_chan				*chan_tx;
	dma_addr_t				tx_dma_phys;
	काष्ठा completion			cmd_tx_complete;
	काष्ठा dma_async_tx_descriptor		*tx_desc;

	u32					*rx_dma_buf;
	काष्ठा dma_chan				*chan_rx;
	dma_addr_t				rx_dma_phys;
	काष्ठा completion			cmd_rx_complete;
	काष्ठा dma_async_tx_descriptor		*rx_desc;
पूर्ण;

काष्ठा fsl_dspi अणु
	काष्ठा spi_controller			*ctlr;
	काष्ठा platक्रमm_device			*pdev;

	काष्ठा regmap				*regmap;
	काष्ठा regmap				*regmap_pushr;
	पूर्णांक					irq;
	काष्ठा clk				*clk;

	काष्ठा spi_transfer			*cur_transfer;
	काष्ठा spi_message			*cur_msg;
	काष्ठा chip_data			*cur_chip;
	माप_प्रकार					progress;
	माप_प्रकार					len;
	स्थिर व्योम				*tx;
	व्योम					*rx;
	u16					tx_cmd;
	स्थिर काष्ठा fsl_dspi_devtype_data	*devtype_data;

	काष्ठा completion			xfer_करोne;

	काष्ठा fsl_dspi_dma			*dma;

	पूर्णांक					oper_word_size;
	पूर्णांक					oper_bits_per_word;

	पूर्णांक					words_in_flight;

	/*
	 * Offsets क्रम CMD and TXDATA within SPI_PUSHR when accessed
	 * inभागidually (in XSPI mode)
	 */
	पूर्णांक					pushr_cmd;
	पूर्णांक					pushr_tx;

	व्योम (*host_to_dev)(काष्ठा fsl_dspi *dspi, u32 *txdata);
	व्योम (*dev_to_host)(काष्ठा fsl_dspi *dspi, u32 rxdata);
पूर्ण;

अटल व्योम dspi_native_host_to_dev(काष्ठा fsl_dspi *dspi, u32 *txdata)
अणु
	चयन (dspi->oper_word_size) अणु
	हाल 1:
		*txdata = *(u8 *)dspi->tx;
		अवरोध;
	हाल 2:
		*txdata = *(u16 *)dspi->tx;
		अवरोध;
	हाल 4:
		*txdata = *(u32 *)dspi->tx;
		अवरोध;
	पूर्ण
	dspi->tx += dspi->oper_word_size;
पूर्ण

अटल व्योम dspi_native_dev_to_host(काष्ठा fsl_dspi *dspi, u32 rxdata)
अणु
	चयन (dspi->oper_word_size) अणु
	हाल 1:
		*(u8 *)dspi->rx = rxdata;
		अवरोध;
	हाल 2:
		*(u16 *)dspi->rx = rxdata;
		अवरोध;
	हाल 4:
		*(u32 *)dspi->rx = rxdata;
		अवरोध;
	पूर्ण
	dspi->rx += dspi->oper_word_size;
पूर्ण

अटल व्योम dspi_8on32_host_to_dev(काष्ठा fsl_dspi *dspi, u32 *txdata)
अणु
	*txdata = cpu_to_be32(*(u32 *)dspi->tx);
	dspi->tx += माप(u32);
पूर्ण

अटल व्योम dspi_8on32_dev_to_host(काष्ठा fsl_dspi *dspi, u32 rxdata)
अणु
	*(u32 *)dspi->rx = be32_to_cpu(rxdata);
	dspi->rx += माप(u32);
पूर्ण

अटल व्योम dspi_8on16_host_to_dev(काष्ठा fsl_dspi *dspi, u32 *txdata)
अणु
	*txdata = cpu_to_be16(*(u16 *)dspi->tx);
	dspi->tx += माप(u16);
पूर्ण

अटल व्योम dspi_8on16_dev_to_host(काष्ठा fsl_dspi *dspi, u32 rxdata)
अणु
	*(u16 *)dspi->rx = be16_to_cpu(rxdata);
	dspi->rx += माप(u16);
पूर्ण

अटल व्योम dspi_16on32_host_to_dev(काष्ठा fsl_dspi *dspi, u32 *txdata)
अणु
	u16 hi = *(u16 *)dspi->tx;
	u16 lo = *(u16 *)(dspi->tx + 2);

	*txdata = (u32)hi << 16 | lo;
	dspi->tx += माप(u32);
पूर्ण

अटल व्योम dspi_16on32_dev_to_host(काष्ठा fsl_dspi *dspi, u32 rxdata)
अणु
	u16 hi = rxdata & 0xffff;
	u16 lo = rxdata >> 16;

	*(u16 *)dspi->rx = lo;
	*(u16 *)(dspi->rx + 2) = hi;
	dspi->rx += माप(u32);
पूर्ण

/*
 * Pop one word from the TX buffer क्रम pushing पूर्णांकo the
 * PUSHR रेजिस्टर (TX FIFO)
 */
अटल u32 dspi_pop_tx(काष्ठा fsl_dspi *dspi)
अणु
	u32 txdata = 0;

	अगर (dspi->tx)
		dspi->host_to_dev(dspi, &txdata);
	dspi->len -= dspi->oper_word_size;
	वापस txdata;
पूर्ण

/* Prepare one TX FIFO entry (txdata plus cmd) */
अटल u32 dspi_pop_tx_pushr(काष्ठा fsl_dspi *dspi)
अणु
	u16 cmd = dspi->tx_cmd, data = dspi_pop_tx(dspi);

	अगर (spi_controller_is_slave(dspi->ctlr))
		वापस data;

	अगर (dspi->len > 0)
		cmd |= SPI_PUSHR_CMD_CONT;
	वापस cmd << 16 | data;
पूर्ण

/* Push one word to the RX buffer from the POPR रेजिस्टर (RX FIFO) */
अटल व्योम dspi_push_rx(काष्ठा fsl_dspi *dspi, u32 rxdata)
अणु
	अगर (!dspi->rx)
		वापस;
	dspi->dev_to_host(dspi, rxdata);
पूर्ण

अटल व्योम dspi_tx_dma_callback(व्योम *arg)
अणु
	काष्ठा fsl_dspi *dspi = arg;
	काष्ठा fsl_dspi_dma *dma = dspi->dma;

	complete(&dma->cmd_tx_complete);
पूर्ण

अटल व्योम dspi_rx_dma_callback(व्योम *arg)
अणु
	काष्ठा fsl_dspi *dspi = arg;
	काष्ठा fsl_dspi_dma *dma = dspi->dma;
	पूर्णांक i;

	अगर (dspi->rx) अणु
		क्रम (i = 0; i < dspi->words_in_flight; i++)
			dspi_push_rx(dspi, dspi->dma->rx_dma_buf[i]);
	पूर्ण

	complete(&dma->cmd_rx_complete);
पूर्ण

अटल पूर्णांक dspi_next_xfer_dma_submit(काष्ठा fsl_dspi *dspi)
अणु
	काष्ठा device *dev = &dspi->pdev->dev;
	काष्ठा fsl_dspi_dma *dma = dspi->dma;
	पूर्णांक समय_left;
	पूर्णांक i;

	क्रम (i = 0; i < dspi->words_in_flight; i++)
		dspi->dma->tx_dma_buf[i] = dspi_pop_tx_pushr(dspi);

	dma->tx_desc = dmaengine_prep_slave_single(dma->chan_tx,
					dma->tx_dma_phys,
					dspi->words_in_flight *
					DMA_SLAVE_BUSWIDTH_4_BYTES,
					DMA_MEM_TO_DEV,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!dma->tx_desc) अणु
		dev_err(dev, "Not able to get desc for DMA xfer\n");
		वापस -EIO;
	पूर्ण

	dma->tx_desc->callback = dspi_tx_dma_callback;
	dma->tx_desc->callback_param = dspi;
	अगर (dma_submit_error(dmaengine_submit(dma->tx_desc))) अणु
		dev_err(dev, "DMA submit failed\n");
		वापस -EINVAL;
	पूर्ण

	dma->rx_desc = dmaengine_prep_slave_single(dma->chan_rx,
					dma->rx_dma_phys,
					dspi->words_in_flight *
					DMA_SLAVE_BUSWIDTH_4_BYTES,
					DMA_DEV_TO_MEM,
					DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (!dma->rx_desc) अणु
		dev_err(dev, "Not able to get desc for DMA xfer\n");
		वापस -EIO;
	पूर्ण

	dma->rx_desc->callback = dspi_rx_dma_callback;
	dma->rx_desc->callback_param = dspi;
	अगर (dma_submit_error(dmaengine_submit(dma->rx_desc))) अणु
		dev_err(dev, "DMA submit failed\n");
		वापस -EINVAL;
	पूर्ण

	reinit_completion(&dspi->dma->cmd_rx_complete);
	reinit_completion(&dspi->dma->cmd_tx_complete);

	dma_async_issue_pending(dma->chan_rx);
	dma_async_issue_pending(dma->chan_tx);

	अगर (spi_controller_is_slave(dspi->ctlr)) अणु
		रुको_क्रम_completion_पूर्णांकerruptible(&dspi->dma->cmd_rx_complete);
		वापस 0;
	पूर्ण

	समय_left = रुको_क्रम_completion_समयout(&dspi->dma->cmd_tx_complete,
						DMA_COMPLETION_TIMEOUT);
	अगर (समय_left == 0) अणु
		dev_err(dev, "DMA tx timeout\n");
		dmaengine_terminate_all(dma->chan_tx);
		dmaengine_terminate_all(dma->chan_rx);
		वापस -ETIMEDOUT;
	पूर्ण

	समय_left = रुको_क्रम_completion_समयout(&dspi->dma->cmd_rx_complete,
						DMA_COMPLETION_TIMEOUT);
	अगर (समय_left == 0) अणु
		dev_err(dev, "DMA rx timeout\n");
		dmaengine_terminate_all(dma->chan_tx);
		dmaengine_terminate_all(dma->chan_rx);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dspi_setup_accel(काष्ठा fsl_dspi *dspi);

अटल पूर्णांक dspi_dma_xfer(काष्ठा fsl_dspi *dspi)
अणु
	काष्ठा spi_message *message = dspi->cur_msg;
	काष्ठा device *dev = &dspi->pdev->dev;
	पूर्णांक ret = 0;

	/*
	 * dspi->len माला_लो decremented by dspi_pop_tx_pushr in
	 * dspi_next_xfer_dma_submit
	 */
	जबतक (dspi->len) अणु
		/* Figure out operational bits-per-word क्रम this chunk */
		dspi_setup_accel(dspi);

		dspi->words_in_flight = dspi->len / dspi->oper_word_size;
		अगर (dspi->words_in_flight > dspi->devtype_data->fअगरo_size)
			dspi->words_in_flight = dspi->devtype_data->fअगरo_size;

		message->actual_length += dspi->words_in_flight *
					  dspi->oper_word_size;

		ret = dspi_next_xfer_dma_submit(dspi);
		अगर (ret) अणु
			dev_err(dev, "DMA transfer failed\n");
			अवरोध;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक dspi_request_dma(काष्ठा fsl_dspi *dspi, phys_addr_t phy_addr)
अणु
	पूर्णांक dma_bufsize = dspi->devtype_data->fअगरo_size * 2;
	काष्ठा device *dev = &dspi->pdev->dev;
	काष्ठा dma_slave_config cfg;
	काष्ठा fsl_dspi_dma *dma;
	पूर्णांक ret;

	dma = devm_kzalloc(dev, माप(*dma), GFP_KERNEL);
	अगर (!dma)
		वापस -ENOMEM;

	dma->chan_rx = dma_request_chan(dev, "rx");
	अगर (IS_ERR(dma->chan_rx)) अणु
		dev_err(dev, "rx dma channel not available\n");
		ret = PTR_ERR(dma->chan_rx);
		वापस ret;
	पूर्ण

	dma->chan_tx = dma_request_chan(dev, "tx");
	अगर (IS_ERR(dma->chan_tx)) अणु
		dev_err(dev, "tx dma channel not available\n");
		ret = PTR_ERR(dma->chan_tx);
		जाओ err_tx_channel;
	पूर्ण

	dma->tx_dma_buf = dma_alloc_coherent(dma->chan_tx->device->dev,
					     dma_bufsize, &dma->tx_dma_phys,
					     GFP_KERNEL);
	अगर (!dma->tx_dma_buf) अणु
		ret = -ENOMEM;
		जाओ err_tx_dma_buf;
	पूर्ण

	dma->rx_dma_buf = dma_alloc_coherent(dma->chan_rx->device->dev,
					     dma_bufsize, &dma->rx_dma_phys,
					     GFP_KERNEL);
	अगर (!dma->rx_dma_buf) अणु
		ret = -ENOMEM;
		जाओ err_rx_dma_buf;
	पूर्ण

	cfg.src_addr = phy_addr + SPI_POPR;
	cfg.dst_addr = phy_addr + SPI_PUSHR;
	cfg.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	cfg.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	cfg.src_maxburst = 1;
	cfg.dst_maxburst = 1;

	cfg.direction = DMA_DEV_TO_MEM;
	ret = dmaengine_slave_config(dma->chan_rx, &cfg);
	अगर (ret) अणु
		dev_err(dev, "can't configure rx dma channel\n");
		ret = -EINVAL;
		जाओ err_slave_config;
	पूर्ण

	cfg.direction = DMA_MEM_TO_DEV;
	ret = dmaengine_slave_config(dma->chan_tx, &cfg);
	अगर (ret) अणु
		dev_err(dev, "can't configure tx dma channel\n");
		ret = -EINVAL;
		जाओ err_slave_config;
	पूर्ण

	dspi->dma = dma;
	init_completion(&dma->cmd_tx_complete);
	init_completion(&dma->cmd_rx_complete);

	वापस 0;

err_slave_config:
	dma_मुक्त_coherent(dma->chan_rx->device->dev,
			  dma_bufsize, dma->rx_dma_buf, dma->rx_dma_phys);
err_rx_dma_buf:
	dma_मुक्त_coherent(dma->chan_tx->device->dev,
			  dma_bufsize, dma->tx_dma_buf, dma->tx_dma_phys);
err_tx_dma_buf:
	dma_release_channel(dma->chan_tx);
err_tx_channel:
	dma_release_channel(dma->chan_rx);

	devm_kमुक्त(dev, dma);
	dspi->dma = शून्य;

	वापस ret;
पूर्ण

अटल व्योम dspi_release_dma(काष्ठा fsl_dspi *dspi)
अणु
	पूर्णांक dma_bufsize = dspi->devtype_data->fअगरo_size * 2;
	काष्ठा fsl_dspi_dma *dma = dspi->dma;

	अगर (!dma)
		वापस;

	अगर (dma->chan_tx) अणु
		dma_मुक्त_coherent(dma->chan_tx->device->dev, dma_bufsize,
				  dma->tx_dma_buf, dma->tx_dma_phys);
		dma_release_channel(dma->chan_tx);
	पूर्ण

	अगर (dma->chan_rx) अणु
		dma_मुक्त_coherent(dma->chan_rx->device->dev, dma_bufsize,
				  dma->rx_dma_buf, dma->rx_dma_phys);
		dma_release_channel(dma->chan_rx);
	पूर्ण
पूर्ण

अटल व्योम hz_to_spi_baud(अक्षर *pbr, अक्षर *br, पूर्णांक speed_hz,
			   अचिन्हित दीर्घ clkrate)
अणु
	/* Valid baud rate pre-scaler values */
	पूर्णांक pbr_tbl[4] = अणु2, 3, 5, 7पूर्ण;
	पूर्णांक brs[16] = अणु	2,	4,	6,	8,
			16,	32,	64,	128,
			256,	512,	1024,	2048,
			4096,	8192,	16384,	32768 पूर्ण;
	पूर्णांक scale_needed, scale, minscale = पूर्णांक_उच्च;
	पूर्णांक i, j;

	scale_needed = clkrate / speed_hz;
	अगर (clkrate % speed_hz)
		scale_needed++;

	क्रम (i = 0; i < ARRAY_SIZE(brs); i++)
		क्रम (j = 0; j < ARRAY_SIZE(pbr_tbl); j++) अणु
			scale = brs[i] * pbr_tbl[j];
			अगर (scale >= scale_needed) अणु
				अगर (scale < minscale) अणु
					minscale = scale;
					*br = i;
					*pbr = j;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण

	अगर (minscale == पूर्णांक_उच्च) अणु
		pr_warn("Can not find valid baud rate,speed_hz is %d,clkrate is %ld, we use the max prescaler value.\n",
			speed_hz, clkrate);
		*pbr = ARRAY_SIZE(pbr_tbl) - 1;
		*br =  ARRAY_SIZE(brs) - 1;
	पूर्ण
पूर्ण

अटल व्योम ns_delay_scale(अक्षर *psc, अक्षर *sc, पूर्णांक delay_ns,
			   अचिन्हित दीर्घ clkrate)
अणु
	पूर्णांक scale_needed, scale, minscale = पूर्णांक_उच्च;
	पूर्णांक pscale_tbl[4] = अणु1, 3, 5, 7पूर्ण;
	u32 reमुख्यder;
	पूर्णांक i, j;

	scale_needed = भाग_u64_rem((u64)delay_ns * clkrate, NSEC_PER_SEC,
				   &reमुख्यder);
	अगर (reमुख्यder)
		scale_needed++;

	क्रम (i = 0; i < ARRAY_SIZE(pscale_tbl); i++)
		क्रम (j = 0; j <= SPI_CTAR_SCALE_BITS; j++) अणु
			scale = pscale_tbl[i] * (2 << j);
			अगर (scale >= scale_needed) अणु
				अगर (scale < minscale) अणु
					minscale = scale;
					*psc = i;
					*sc = j;
				पूर्ण
				अवरोध;
			पूर्ण
		पूर्ण

	अगर (minscale == पूर्णांक_उच्च) अणु
		pr_warn("Cannot find correct scale values for %dns delay at clkrate %ld, using max prescaler value",
			delay_ns, clkrate);
		*psc = ARRAY_SIZE(pscale_tbl) - 1;
		*sc = SPI_CTAR_SCALE_BITS;
	पूर्ण
पूर्ण

अटल व्योम dspi_pushr_cmd_ग_लिखो(काष्ठा fsl_dspi *dspi, u16 cmd)
अणु
	/*
	 * The only समय when the PCS करोesn't need continuation after this word
	 * is when it's last. We need to look ahead, because we actually call
	 * dspi_pop_tx (the function that decrements dspi->len) _after_
	 * dspi_pushr_cmd_ग_लिखो with XSPI mode. As क्रम how much in advance? One
	 * word is enough. If there's more to transmit than that,
	 * dspi_xspi_ग_लिखो will know to split the FIFO ग_लिखोs in 2, and
	 * generate a new PUSHR command with the final word that will have PCS
	 * deनिश्चितed (not जारीd) here.
	 */
	अगर (dspi->len > dspi->oper_word_size)
		cmd |= SPI_PUSHR_CMD_CONT;
	regmap_ग_लिखो(dspi->regmap_pushr, dspi->pushr_cmd, cmd);
पूर्ण

अटल व्योम dspi_pushr_txdata_ग_लिखो(काष्ठा fsl_dspi *dspi, u16 txdata)
अणु
	regmap_ग_लिखो(dspi->regmap_pushr, dspi->pushr_tx, txdata);
पूर्ण

अटल व्योम dspi_xspi_fअगरo_ग_लिखो(काष्ठा fsl_dspi *dspi, पूर्णांक num_words)
अणु
	पूर्णांक num_bytes = num_words * dspi->oper_word_size;
	u16 tx_cmd = dspi->tx_cmd;

	/*
	 * If the PCS needs to de-निश्चित (i.e. we're at the end of the buffer
	 * and cs_change करोes not want the PCS to stay on), then we need a new
	 * PUSHR command, since this one (क्रम the body of the buffer)
	 * necessarily has the CONT bit set.
	 * So send one word less during this go, to क्रमce a split and a command
	 * with a single word next समय, when CONT will be unset.
	 */
	अगर (!(dspi->tx_cmd & SPI_PUSHR_CMD_CONT) && num_bytes == dspi->len)
		tx_cmd |= SPI_PUSHR_CMD_EOQ;

	/* Update CTARE */
	regmap_ग_लिखो(dspi->regmap, SPI_CTARE(0),
		     SPI_FRAME_EBITS(dspi->oper_bits_per_word) |
		     SPI_CTARE_DTCP(num_words));

	/*
	 * Write the CMD FIFO entry first, and then the two
	 * corresponding TX FIFO entries (or one...).
	 */
	dspi_pushr_cmd_ग_लिखो(dspi, tx_cmd);

	/* Fill TX FIFO with as many transfers as possible */
	जबतक (num_words--) अणु
		u32 data = dspi_pop_tx(dspi);

		dspi_pushr_txdata_ग_लिखो(dspi, data & 0xFFFF);
		अगर (dspi->oper_bits_per_word > 16)
			dspi_pushr_txdata_ग_लिखो(dspi, data >> 16);
	पूर्ण
पूर्ण

अटल u32 dspi_popr_पढ़ो(काष्ठा fsl_dspi *dspi)
अणु
	u32 rxdata = 0;

	regmap_पढ़ो(dspi->regmap, SPI_POPR, &rxdata);
	वापस rxdata;
पूर्ण

अटल व्योम dspi_fअगरo_पढ़ो(काष्ठा fsl_dspi *dspi)
अणु
	पूर्णांक num_fअगरo_entries = dspi->words_in_flight;

	/* Read one FIFO entry and push to rx buffer */
	जबतक (num_fअगरo_entries--)
		dspi_push_rx(dspi, dspi_popr_पढ़ो(dspi));
पूर्ण

अटल व्योम dspi_setup_accel(काष्ठा fsl_dspi *dspi)
अणु
	काष्ठा spi_transfer *xfer = dspi->cur_transfer;
	bool odd = !!(dspi->len & 1);

	/* No accel क्रम frames not multiple of 8 bits at the moment */
	अगर (xfer->bits_per_word % 8)
		जाओ no_accel;

	अगर (!odd && dspi->len <= dspi->devtype_data->fअगरo_size * 2) अणु
		dspi->oper_bits_per_word = 16;
	पूर्ण अन्यथा अगर (odd && dspi->len <= dspi->devtype_data->fअगरo_size) अणु
		dspi->oper_bits_per_word = 8;
	पूर्ण अन्यथा अणु
		/* Start off with maximum supported by hardware */
		अगर (dspi->devtype_data->trans_mode == DSPI_XSPI_MODE)
			dspi->oper_bits_per_word = 32;
		अन्यथा
			dspi->oper_bits_per_word = 16;

		/*
		 * And go करोwn only अगर the buffer can't be sent with
		 * words this big
		 */
		करो अणु
			अगर (dspi->len >= DIV_ROUND_UP(dspi->oper_bits_per_word, 8))
				अवरोध;

			dspi->oper_bits_per_word /= 2;
		पूर्ण जबतक (dspi->oper_bits_per_word > 8);
	पूर्ण

	अगर (xfer->bits_per_word == 8 && dspi->oper_bits_per_word == 32) अणु
		dspi->dev_to_host = dspi_8on32_dev_to_host;
		dspi->host_to_dev = dspi_8on32_host_to_dev;
	पूर्ण अन्यथा अगर (xfer->bits_per_word == 8 && dspi->oper_bits_per_word == 16) अणु
		dspi->dev_to_host = dspi_8on16_dev_to_host;
		dspi->host_to_dev = dspi_8on16_host_to_dev;
	पूर्ण अन्यथा अगर (xfer->bits_per_word == 16 && dspi->oper_bits_per_word == 32) अणु
		dspi->dev_to_host = dspi_16on32_dev_to_host;
		dspi->host_to_dev = dspi_16on32_host_to_dev;
	पूर्ण अन्यथा अणु
no_accel:
		dspi->dev_to_host = dspi_native_dev_to_host;
		dspi->host_to_dev = dspi_native_host_to_dev;
		dspi->oper_bits_per_word = xfer->bits_per_word;
	पूर्ण

	dspi->oper_word_size = DIV_ROUND_UP(dspi->oper_bits_per_word, 8);

	/*
	 * Update CTAR here (code is common क्रम XSPI and DMA modes).
	 * We will update CTARE in the portion specअगरic to XSPI, when we
	 * also know the preload value (DTCP).
	 */
	regmap_ग_लिखो(dspi->regmap, SPI_CTAR(0),
		     dspi->cur_chip->ctar_val |
		     SPI_FRAME_BITS(dspi->oper_bits_per_word));
पूर्ण

अटल व्योम dspi_fअगरo_ग_लिखो(काष्ठा fsl_dspi *dspi)
अणु
	पूर्णांक num_fअगरo_entries = dspi->devtype_data->fअगरo_size;
	काष्ठा spi_transfer *xfer = dspi->cur_transfer;
	काष्ठा spi_message *msg = dspi->cur_msg;
	पूर्णांक num_words, num_bytes;

	dspi_setup_accel(dspi);

	/* In XSPI mode each 32-bit word occupies 2 TX FIFO entries */
	अगर (dspi->oper_word_size == 4)
		num_fअगरo_entries /= 2;

	/*
	 * Integer भागision पूर्णांकentionally trims off odd (or non-multiple of 4)
	 * numbers of bytes at the end of the buffer, which will be sent next
	 * समय using a smaller oper_word_size.
	 */
	num_words = dspi->len / dspi->oper_word_size;
	अगर (num_words > num_fअगरo_entries)
		num_words = num_fअगरo_entries;

	/* Update total number of bytes that were transferred */
	num_bytes = num_words * dspi->oper_word_size;
	msg->actual_length += num_bytes;
	dspi->progress += num_bytes / DIV_ROUND_UP(xfer->bits_per_word, 8);

	/*
	 * Update shared variable क्रम use in the next पूर्णांकerrupt (both in
	 * dspi_fअगरo_पढ़ो and in dspi_fअगरo_ग_लिखो).
	 */
	dspi->words_in_flight = num_words;

	spi_take_बारtamp_pre(dspi->ctlr, xfer, dspi->progress, !dspi->irq);

	dspi_xspi_fअगरo_ग_लिखो(dspi, num_words);
	/*
	 * Everything after this poपूर्णांक is in a potential race with the next
	 * पूर्णांकerrupt, so we must never use dspi->words_in_flight again since it
	 * might alपढ़ोy be modअगरied by the next dspi_fअगरo_ग_लिखो.
	 */

	spi_take_बारtamp_post(dspi->ctlr, dspi->cur_transfer,
				dspi->progress, !dspi->irq);
पूर्ण

अटल पूर्णांक dspi_rxtx(काष्ठा fsl_dspi *dspi)
अणु
	dspi_fअगरo_पढ़ो(dspi);

	अगर (!dspi->len)
		/* Success! */
		वापस 0;

	dspi_fअगरo_ग_लिखो(dspi);

	वापस -EINPROGRESS;
पूर्ण

अटल पूर्णांक dspi_poll(काष्ठा fsl_dspi *dspi)
अणु
	पूर्णांक tries = 1000;
	u32 spi_sr;

	करो अणु
		regmap_पढ़ो(dspi->regmap, SPI_SR, &spi_sr);
		regmap_ग_लिखो(dspi->regmap, SPI_SR, spi_sr);

		अगर (spi_sr & SPI_SR_CMDTCF)
			अवरोध;
	पूर्ण जबतक (--tries);

	अगर (!tries)
		वापस -ETIMEDOUT;

	वापस dspi_rxtx(dspi);
पूर्ण

अटल irqवापस_t dspi_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा fsl_dspi *dspi = (काष्ठा fsl_dspi *)dev_id;
	u32 spi_sr;

	regmap_पढ़ो(dspi->regmap, SPI_SR, &spi_sr);
	regmap_ग_लिखो(dspi->regmap, SPI_SR, spi_sr);

	अगर (!(spi_sr & SPI_SR_CMDTCF))
		वापस IRQ_NONE;

	अगर (dspi_rxtx(dspi) == 0)
		complete(&dspi->xfer_करोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dspi_transfer_one_message(काष्ठा spi_controller *ctlr,
				     काष्ठा spi_message *message)
अणु
	काष्ठा fsl_dspi *dspi = spi_controller_get_devdata(ctlr);
	काष्ठा spi_device *spi = message->spi;
	काष्ठा spi_transfer *transfer;
	पूर्णांक status = 0;

	message->actual_length = 0;

	list_क्रम_each_entry(transfer, &message->transfers, transfer_list) अणु
		dspi->cur_transfer = transfer;
		dspi->cur_msg = message;
		dspi->cur_chip = spi_get_ctldata(spi);
		/* Prepare command word क्रम CMD FIFO */
		dspi->tx_cmd = SPI_PUSHR_CMD_CTAS(0) |
			       SPI_PUSHR_CMD_PCS(spi->chip_select);
		अगर (list_is_last(&dspi->cur_transfer->transfer_list,
				 &dspi->cur_msg->transfers)) अणु
			/* Leave PCS activated after last transfer when
			 * cs_change is set.
			 */
			अगर (transfer->cs_change)
				dspi->tx_cmd |= SPI_PUSHR_CMD_CONT;
		पूर्ण अन्यथा अणु
			/* Keep PCS active between transfers in same message
			 * when cs_change is not set, and de-activate PCS
			 * between transfers in the same message when
			 * cs_change is set.
			 */
			अगर (!transfer->cs_change)
				dspi->tx_cmd |= SPI_PUSHR_CMD_CONT;
		पूर्ण

		dspi->tx = transfer->tx_buf;
		dspi->rx = transfer->rx_buf;
		dspi->len = transfer->len;
		dspi->progress = 0;

		regmap_update_bits(dspi->regmap, SPI_MCR,
				   SPI_MCR_CLR_TXF | SPI_MCR_CLR_RXF,
				   SPI_MCR_CLR_TXF | SPI_MCR_CLR_RXF);

		spi_take_बारtamp_pre(dspi->ctlr, dspi->cur_transfer,
				       dspi->progress, !dspi->irq);

		अगर (dspi->devtype_data->trans_mode == DSPI_DMA_MODE) अणु
			status = dspi_dma_xfer(dspi);
		पूर्ण अन्यथा अणु
			dspi_fअगरo_ग_लिखो(dspi);

			अगर (dspi->irq) अणु
				रुको_क्रम_completion(&dspi->xfer_करोne);
				reinit_completion(&dspi->xfer_करोne);
			पूर्ण अन्यथा अणु
				करो अणु
					status = dspi_poll(dspi);
				पूर्ण जबतक (status == -EINPROGRESS);
			पूर्ण
		पूर्ण
		अगर (status)
			अवरोध;

		spi_transfer_delay_exec(transfer);
	पूर्ण

	message->status = status;
	spi_finalize_current_message(ctlr);

	वापस status;
पूर्ण

अटल पूर्णांक dspi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा fsl_dspi *dspi = spi_controller_get_devdata(spi->controller);
	अचिन्हित अक्षर br = 0, pbr = 0, pcssck = 0, cssck = 0;
	u32 cs_sck_delay = 0, sck_cs_delay = 0;
	काष्ठा fsl_dspi_platक्रमm_data *pdata;
	अचिन्हित अक्षर pasc = 0, asc = 0;
	काष्ठा chip_data *chip;
	अचिन्हित दीर्घ clkrate;

	/* Only alloc on first setup */
	chip = spi_get_ctldata(spi);
	अगर (chip == शून्य) अणु
		chip = kzalloc(माप(काष्ठा chip_data), GFP_KERNEL);
		अगर (!chip)
			वापस -ENOMEM;
	पूर्ण

	pdata = dev_get_platdata(&dspi->pdev->dev);

	अगर (!pdata) अणु
		of_property_पढ़ो_u32(spi->dev.of_node, "fsl,spi-cs-sck-delay",
				     &cs_sck_delay);

		of_property_पढ़ो_u32(spi->dev.of_node, "fsl,spi-sck-cs-delay",
				     &sck_cs_delay);
	पूर्ण अन्यथा अणु
		cs_sck_delay = pdata->cs_sck_delay;
		sck_cs_delay = pdata->sck_cs_delay;
	पूर्ण

	clkrate = clk_get_rate(dspi->clk);
	hz_to_spi_baud(&pbr, &br, spi->max_speed_hz, clkrate);

	/* Set PCS to SCK delay scale values */
	ns_delay_scale(&pcssck, &cssck, cs_sck_delay, clkrate);

	/* Set After SCK delay scale values */
	ns_delay_scale(&pasc, &asc, sck_cs_delay, clkrate);

	chip->ctar_val = 0;
	अगर (spi->mode & SPI_CPOL)
		chip->ctar_val |= SPI_CTAR_CPOL;
	अगर (spi->mode & SPI_CPHA)
		chip->ctar_val |= SPI_CTAR_CPHA;

	अगर (!spi_controller_is_slave(dspi->ctlr)) अणु
		chip->ctar_val |= SPI_CTAR_PCSSCK(pcssck) |
				  SPI_CTAR_CSSCK(cssck) |
				  SPI_CTAR_PASC(pasc) |
				  SPI_CTAR_ASC(asc) |
				  SPI_CTAR_PBR(pbr) |
				  SPI_CTAR_BR(br);

		अगर (spi->mode & SPI_LSB_FIRST)
			chip->ctar_val |= SPI_CTAR_LSBFE;
	पूर्ण

	spi_set_ctldata(spi, chip);

	वापस 0;
पूर्ण

अटल व्योम dspi_cleanup(काष्ठा spi_device *spi)
अणु
	काष्ठा chip_data *chip = spi_get_ctldata((काष्ठा spi_device *)spi);

	dev_dbg(&spi->dev, "spi_device %u.%u cleanup\n",
		spi->controller->bus_num, spi->chip_select);

	kमुक्त(chip);
पूर्ण

अटल स्थिर काष्ठा of_device_id fsl_dspi_dt_ids[] = अणु
	अणु
		.compatible = "fsl,vf610-dspi",
		.data = &devtype_data[VF610],
	पूर्ण, अणु
		.compatible = "fsl,ls1021a-v1.0-dspi",
		.data = &devtype_data[LS1021A],
	पूर्ण, अणु
		.compatible = "fsl,ls1012a-dspi",
		.data = &devtype_data[LS1012A],
	पूर्ण, अणु
		.compatible = "fsl,ls1028a-dspi",
		.data = &devtype_data[LS1028A],
	पूर्ण, अणु
		.compatible = "fsl,ls1043a-dspi",
		.data = &devtype_data[LS1043A],
	पूर्ण, अणु
		.compatible = "fsl,ls1046a-dspi",
		.data = &devtype_data[LS1046A],
	पूर्ण, अणु
		.compatible = "fsl,ls2080a-dspi",
		.data = &devtype_data[LS2080A],
	पूर्ण, अणु
		.compatible = "fsl,ls2085a-dspi",
		.data = &devtype_data[LS2085A],
	पूर्ण, अणु
		.compatible = "fsl,lx2160a-dspi",
		.data = &devtype_data[LX2160A],
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_dspi_dt_ids);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक dspi_suspend(काष्ठा device *dev)
अणु
	काष्ठा fsl_dspi *dspi = dev_get_drvdata(dev);

	अगर (dspi->irq)
		disable_irq(dspi->irq);
	spi_controller_suspend(dspi->ctlr);
	clk_disable_unprepare(dspi->clk);

	pinctrl_pm_select_sleep_state(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक dspi_resume(काष्ठा device *dev)
अणु
	काष्ठा fsl_dspi *dspi = dev_get_drvdata(dev);
	पूर्णांक ret;

	pinctrl_pm_select_शेष_state(dev);

	ret = clk_prepare_enable(dspi->clk);
	अगर (ret)
		वापस ret;
	spi_controller_resume(dspi->ctlr);
	अगर (dspi->irq)
		enable_irq(dspi->irq);

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(dspi_pm, dspi_suspend, dspi_resume);

अटल स्थिर काष्ठा regmap_range dspi_अस्थिर_ranges[] = अणु
	regmap_reg_range(SPI_MCR, SPI_TCR),
	regmap_reg_range(SPI_SR, SPI_SR),
	regmap_reg_range(SPI_PUSHR, SPI_RXFR3),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table dspi_अस्थिर_table = अणु
	.yes_ranges	= dspi_अस्थिर_ranges,
	.n_yes_ranges	= ARRAY_SIZE(dspi_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config dspi_regmap_config = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
	.max_रेजिस्टर	= 0x88,
	.अस्थिर_table	= &dspi_अस्थिर_table,
पूर्ण;

अटल स्थिर काष्ठा regmap_range dspi_xspi_अस्थिर_ranges[] = अणु
	regmap_reg_range(SPI_MCR, SPI_TCR),
	regmap_reg_range(SPI_SR, SPI_SR),
	regmap_reg_range(SPI_PUSHR, SPI_RXFR3),
	regmap_reg_range(SPI_SREX, SPI_SREX),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table dspi_xspi_अस्थिर_table = अणु
	.yes_ranges	= dspi_xspi_अस्थिर_ranges,
	.n_yes_ranges	= ARRAY_SIZE(dspi_xspi_अस्थिर_ranges),
पूर्ण;

अटल स्थिर काष्ठा regmap_config dspi_xspi_regmap_config[] = अणु
	अणु
		.reg_bits	= 32,
		.val_bits	= 32,
		.reg_stride	= 4,
		.max_रेजिस्टर	= 0x13c,
		.अस्थिर_table	= &dspi_xspi_अस्थिर_table,
	पूर्ण,
	अणु
		.name		= "pushr",
		.reg_bits	= 16,
		.val_bits	= 16,
		.reg_stride	= 2,
		.max_रेजिस्टर	= 0x2,
	पूर्ण,
पूर्ण;

अटल पूर्णांक dspi_init(काष्ठा fsl_dspi *dspi)
अणु
	अचिन्हित पूर्णांक mcr;

	/* Set idle states क्रम all chip select संकेतs to high */
	mcr = SPI_MCR_PCSIS(GENMASK(dspi->ctlr->max_native_cs - 1, 0));

	अगर (dspi->devtype_data->trans_mode == DSPI_XSPI_MODE)
		mcr |= SPI_MCR_XSPI;
	अगर (!spi_controller_is_slave(dspi->ctlr))
		mcr |= SPI_MCR_MASTER;

	regmap_ग_लिखो(dspi->regmap, SPI_MCR, mcr);
	regmap_ग_लिखो(dspi->regmap, SPI_SR, SPI_SR_CLEAR);

	चयन (dspi->devtype_data->trans_mode) अणु
	हाल DSPI_XSPI_MODE:
		regmap_ग_लिखो(dspi->regmap, SPI_RSER, SPI_RSER_CMDTCFE);
		अवरोध;
	हाल DSPI_DMA_MODE:
		regmap_ग_लिखो(dspi->regmap, SPI_RSER,
			     SPI_RSER_TFFFE | SPI_RSER_TFFFD |
			     SPI_RSER_RFDFE | SPI_RSER_RFDFD);
		अवरोध;
	शेष:
		dev_err(&dspi->pdev->dev, "unsupported trans_mode %u\n",
			dspi->devtype_data->trans_mode);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dspi_slave_पात(काष्ठा spi_master *master)
अणु
	काष्ठा fsl_dspi *dspi = spi_master_get_devdata(master);

	/*
	 * Terminate all pending DMA transactions क्रम the SPI working
	 * in SLAVE mode.
	 */
	अगर (dspi->devtype_data->trans_mode == DSPI_DMA_MODE) अणु
		dmaengine_terminate_sync(dspi->dma->chan_rx);
		dmaengine_terminate_sync(dspi->dma->chan_tx);
	पूर्ण

	/* Clear the पूर्णांकernal DSPI RX and TX FIFO buffers */
	regmap_update_bits(dspi->regmap, SPI_MCR,
			   SPI_MCR_CLR_TXF | SPI_MCR_CLR_RXF,
			   SPI_MCR_CLR_TXF | SPI_MCR_CLR_RXF);

	वापस 0;
पूर्ण

अटल पूर्णांक dspi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा regmap_config *regmap_config;
	काष्ठा fsl_dspi_platक्रमm_data *pdata;
	काष्ठा spi_controller *ctlr;
	पूर्णांक ret, cs_num, bus_num = -1;
	काष्ठा fsl_dspi *dspi;
	काष्ठा resource *res;
	व्योम __iomem *base;
	bool big_endian;

	dspi = devm_kzalloc(&pdev->dev, माप(*dspi), GFP_KERNEL);
	अगर (!dspi)
		वापस -ENOMEM;

	ctlr = spi_alloc_master(&pdev->dev, 0);
	अगर (!ctlr)
		वापस -ENOMEM;

	spi_controller_set_devdata(ctlr, dspi);
	platक्रमm_set_drvdata(pdev, dspi);

	dspi->pdev = pdev;
	dspi->ctlr = ctlr;

	ctlr->setup = dspi_setup;
	ctlr->transfer_one_message = dspi_transfer_one_message;
	ctlr->dev.of_node = pdev->dev.of_node;

	ctlr->cleanup = dspi_cleanup;
	ctlr->slave_पात = dspi_slave_पात;
	ctlr->mode_bits = SPI_CPOL | SPI_CPHA | SPI_LSB_FIRST;

	pdata = dev_get_platdata(&pdev->dev);
	अगर (pdata) अणु
		ctlr->num_chipselect = ctlr->max_native_cs = pdata->cs_num;
		ctlr->bus_num = pdata->bus_num;

		/* Only Coldfire uses platक्रमm data */
		dspi->devtype_data = &devtype_data[MCF5441X];
		big_endian = true;
	पूर्ण अन्यथा अणु

		ret = of_property_पढ़ो_u32(np, "spi-num-chipselects", &cs_num);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "can't get spi-num-chipselects\n");
			जाओ out_ctlr_put;
		पूर्ण
		ctlr->num_chipselect = ctlr->max_native_cs = cs_num;

		of_property_पढ़ो_u32(np, "bus-num", &bus_num);
		ctlr->bus_num = bus_num;

		अगर (of_property_पढ़ो_bool(np, "spi-slave"))
			ctlr->slave = true;

		dspi->devtype_data = of_device_get_match_data(&pdev->dev);
		अगर (!dspi->devtype_data) अणु
			dev_err(&pdev->dev, "can't get devtype_data\n");
			ret = -EFAULT;
			जाओ out_ctlr_put;
		पूर्ण

		big_endian = of_device_is_big_endian(np);
	पूर्ण
	अगर (big_endian) अणु
		dspi->pushr_cmd = 0;
		dspi->pushr_tx = 2;
	पूर्ण अन्यथा अणु
		dspi->pushr_cmd = 2;
		dspi->pushr_tx = 0;
	पूर्ण

	अगर (dspi->devtype_data->trans_mode == DSPI_XSPI_MODE)
		ctlr->bits_per_word_mask = SPI_BPW_RANGE_MASK(4, 32);
	अन्यथा
		ctlr->bits_per_word_mask = SPI_BPW_RANGE_MASK(4, 16);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base)) अणु
		ret = PTR_ERR(base);
		जाओ out_ctlr_put;
	पूर्ण

	अगर (dspi->devtype_data->trans_mode == DSPI_XSPI_MODE)
		regmap_config = &dspi_xspi_regmap_config[0];
	अन्यथा
		regmap_config = &dspi_regmap_config;
	dspi->regmap = devm_regmap_init_mmio(&pdev->dev, base, regmap_config);
	अगर (IS_ERR(dspi->regmap)) अणु
		dev_err(&pdev->dev, "failed to init regmap: %ld\n",
				PTR_ERR(dspi->regmap));
		ret = PTR_ERR(dspi->regmap);
		जाओ out_ctlr_put;
	पूर्ण

	अगर (dspi->devtype_data->trans_mode == DSPI_XSPI_MODE) अणु
		dspi->regmap_pushr = devm_regmap_init_mmio(
			&pdev->dev, base + SPI_PUSHR,
			&dspi_xspi_regmap_config[1]);
		अगर (IS_ERR(dspi->regmap_pushr)) अणु
			dev_err(&pdev->dev,
				"failed to init pushr regmap: %ld\n",
				PTR_ERR(dspi->regmap_pushr));
			ret = PTR_ERR(dspi->regmap_pushr);
			जाओ out_ctlr_put;
		पूर्ण
	पूर्ण

	dspi->clk = devm_clk_get(&pdev->dev, "dspi");
	अगर (IS_ERR(dspi->clk)) अणु
		ret = PTR_ERR(dspi->clk);
		dev_err(&pdev->dev, "unable to get clock\n");
		जाओ out_ctlr_put;
	पूर्ण
	ret = clk_prepare_enable(dspi->clk);
	अगर (ret)
		जाओ out_ctlr_put;

	ret = dspi_init(dspi);
	अगर (ret)
		जाओ out_clk_put;

	dspi->irq = platक्रमm_get_irq(pdev, 0);
	अगर (dspi->irq <= 0) अणु
		dev_info(&pdev->dev,
			 "can't get platform irq, using poll mode\n");
		dspi->irq = 0;
		जाओ poll_mode;
	पूर्ण

	init_completion(&dspi->xfer_करोne);

	ret = request_thपढ़ोed_irq(dspi->irq, dspi_पूर्णांकerrupt, शून्य,
				   IRQF_SHARED, pdev->name, dspi);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Unable to attach DSPI interrupt\n");
		जाओ out_clk_put;
	पूर्ण

poll_mode:

	अगर (dspi->devtype_data->trans_mode == DSPI_DMA_MODE) अणु
		ret = dspi_request_dma(dspi, res->start);
		अगर (ret < 0) अणु
			dev_err(&pdev->dev, "can't get dma channels\n");
			जाओ out_मुक्त_irq;
		पूर्ण
	पूर्ण

	ctlr->max_speed_hz =
		clk_get_rate(dspi->clk) / dspi->devtype_data->max_घड़ी_factor;

	अगर (dspi->devtype_data->trans_mode != DSPI_DMA_MODE)
		ctlr->ptp_sts_supported = true;

	ret = spi_रेजिस्टर_controller(ctlr);
	अगर (ret != 0) अणु
		dev_err(&pdev->dev, "Problem registering DSPI ctlr\n");
		जाओ out_release_dma;
	पूर्ण

	वापस ret;

out_release_dma:
	dspi_release_dma(dspi);
out_मुक्त_irq:
	अगर (dspi->irq)
		मुक्त_irq(dspi->irq, dspi);
out_clk_put:
	clk_disable_unprepare(dspi->clk);
out_ctlr_put:
	spi_controller_put(ctlr);

	वापस ret;
पूर्ण

अटल पूर्णांक dspi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_dspi *dspi = platक्रमm_get_drvdata(pdev);

	/* Disconnect from the SPI framework */
	spi_unरेजिस्टर_controller(dspi->ctlr);

	/* Disable RX and TX */
	regmap_update_bits(dspi->regmap, SPI_MCR,
			   SPI_MCR_DIS_TXF | SPI_MCR_DIS_RXF,
			   SPI_MCR_DIS_TXF | SPI_MCR_DIS_RXF);

	/* Stop Running */
	regmap_update_bits(dspi->regmap, SPI_MCR, SPI_MCR_HALT, SPI_MCR_HALT);

	dspi_release_dma(dspi);
	अगर (dspi->irq)
		मुक्त_irq(dspi->irq, dspi);
	clk_disable_unprepare(dspi->clk);

	वापस 0;
पूर्ण

अटल व्योम dspi_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	dspi_हटाओ(pdev);
पूर्ण

अटल काष्ठा platक्रमm_driver fsl_dspi_driver = अणु
	.driver.name		= DRIVER_NAME,
	.driver.of_match_table	= fsl_dspi_dt_ids,
	.driver.owner		= THIS_MODULE,
	.driver.pm		= &dspi_pm,
	.probe			= dspi_probe,
	.हटाओ			= dspi_हटाओ,
	.shutकरोwn		= dspi_shutकरोwn,
पूर्ण;
module_platक्रमm_driver(fsl_dspi_driver);

MODULE_DESCRIPTION("Freescale DSPI Controller Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRIVER_NAME);
