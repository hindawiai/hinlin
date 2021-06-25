<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Designware SPI core controller driver (refer pxa2xx_spi.c)
 *
 * Copyright (c) 2009, Intel Corporation.
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/preempt.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi-स्मृति.स>
#समावेश <linux/माला.स>
#समावेश <linux/of.h>

#समावेश "spi-dw.h"

#अगर_घोषित CONFIG_DEBUG_FS
#समावेश <linux/debugfs.h>
#पूर्ण_अगर

/* Slave spi_device related */
काष्ठा chip_data अणु
	u32 cr0;
	u32 rx_sample_dly;	/* RX sample delay */
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS

#घोषणा DW_SPI_DBGFS_REG(_name, _off)	\
अणु					\
	.name = _name,			\
	.offset = _off,			\
पूर्ण

अटल स्थिर काष्ठा debugfs_reg32 dw_spi_dbgfs_regs[] = अणु
	DW_SPI_DBGFS_REG("CTRLR0", DW_SPI_CTRLR0),
	DW_SPI_DBGFS_REG("CTRLR1", DW_SPI_CTRLR1),
	DW_SPI_DBGFS_REG("SSIENR", DW_SPI_SSIENR),
	DW_SPI_DBGFS_REG("SER", DW_SPI_SER),
	DW_SPI_DBGFS_REG("BAUDR", DW_SPI_BAUDR),
	DW_SPI_DBGFS_REG("TXFTLR", DW_SPI_TXFTLR),
	DW_SPI_DBGFS_REG("RXFTLR", DW_SPI_RXFTLR),
	DW_SPI_DBGFS_REG("TXFLR", DW_SPI_TXFLR),
	DW_SPI_DBGFS_REG("RXFLR", DW_SPI_RXFLR),
	DW_SPI_DBGFS_REG("SR", DW_SPI_SR),
	DW_SPI_DBGFS_REG("IMR", DW_SPI_IMR),
	DW_SPI_DBGFS_REG("ISR", DW_SPI_ISR),
	DW_SPI_DBGFS_REG("DMACR", DW_SPI_DMACR),
	DW_SPI_DBGFS_REG("DMATDLR", DW_SPI_DMATDLR),
	DW_SPI_DBGFS_REG("DMARDLR", DW_SPI_DMARDLR),
	DW_SPI_DBGFS_REG("RX_SAMPLE_DLY", DW_SPI_RX_SAMPLE_DLY),
पूर्ण;

अटल पूर्णांक dw_spi_debugfs_init(काष्ठा dw_spi *dws)
अणु
	अक्षर name[32];

	snम_लिखो(name, 32, "dw_spi%d", dws->master->bus_num);
	dws->debugfs = debugfs_create_dir(name, शून्य);
	अगर (!dws->debugfs)
		वापस -ENOMEM;

	dws->regset.regs = dw_spi_dbgfs_regs;
	dws->regset.nregs = ARRAY_SIZE(dw_spi_dbgfs_regs);
	dws->regset.base = dws->regs;
	debugfs_create_regset32("registers", 0400, dws->debugfs, &dws->regset);

	वापस 0;
पूर्ण

अटल व्योम dw_spi_debugfs_हटाओ(काष्ठा dw_spi *dws)
अणु
	debugfs_हटाओ_recursive(dws->debugfs);
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक dw_spi_debugfs_init(काष्ठा dw_spi *dws)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम dw_spi_debugfs_हटाओ(काष्ठा dw_spi *dws)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_DEBUG_FS */

व्योम dw_spi_set_cs(काष्ठा spi_device *spi, bool enable)
अणु
	काष्ठा dw_spi *dws = spi_controller_get_devdata(spi->controller);
	bool cs_high = !!(spi->mode & SPI_CS_HIGH);

	/*
	 * DW SPI controller demands any native CS being set in order to
	 * proceed with data transfer. So in order to activate the SPI
	 * communications we must set a corresponding bit in the Slave
	 * Enable रेजिस्टर no matter whether the SPI core is configured to
	 * support active-high or active-low CS level.
	 */
	अगर (cs_high == enable)
		dw_ग_लिखोl(dws, DW_SPI_SER, BIT(spi->chip_select));
	अन्यथा
		dw_ग_लिखोl(dws, DW_SPI_SER, 0);
पूर्ण
EXPORT_SYMBOL_GPL(dw_spi_set_cs);

/* Return the max entries we can fill पूर्णांकo tx fअगरo */
अटल अंतरभूत u32 tx_max(काष्ठा dw_spi *dws)
अणु
	u32 tx_room, rxtx_gap;

	tx_room = dws->fअगरo_len - dw_पढ़ोl(dws, DW_SPI_TXFLR);

	/*
	 * Another concern is about the tx/rx mismatch, we
	 * though to use (dws->fअगरo_len - rxflr - txflr) as
	 * one maximum value क्रम tx, but it करोesn't cover the
	 * data which is out of tx/rx fअगरo and inside the
	 * shअगरt रेजिस्टरs. So a control from sw poपूर्णांक of
	 * view is taken.
	 */
	rxtx_gap = dws->fअगरo_len - (dws->rx_len - dws->tx_len);

	वापस min3((u32)dws->tx_len, tx_room, rxtx_gap);
पूर्ण

/* Return the max entries we should पढ़ो out of rx fअगरo */
अटल अंतरभूत u32 rx_max(काष्ठा dw_spi *dws)
अणु
	वापस min_t(u32, dws->rx_len, dw_पढ़ोl(dws, DW_SPI_RXFLR));
पूर्ण

अटल व्योम dw_ग_लिखोr(काष्ठा dw_spi *dws)
अणु
	u32 max = tx_max(dws);
	u32 txw = 0;

	जबतक (max--) अणु
		अगर (dws->tx) अणु
			अगर (dws->n_bytes == 1)
				txw = *(u8 *)(dws->tx);
			अन्यथा अगर (dws->n_bytes == 2)
				txw = *(u16 *)(dws->tx);
			अन्यथा
				txw = *(u32 *)(dws->tx);

			dws->tx += dws->n_bytes;
		पूर्ण
		dw_ग_लिखो_io_reg(dws, DW_SPI_DR, txw);
		--dws->tx_len;
	पूर्ण
पूर्ण

अटल व्योम dw_पढ़ोer(काष्ठा dw_spi *dws)
अणु
	u32 max = rx_max(dws);
	u32 rxw;

	जबतक (max--) अणु
		rxw = dw_पढ़ो_io_reg(dws, DW_SPI_DR);
		अगर (dws->rx) अणु
			अगर (dws->n_bytes == 1)
				*(u8 *)(dws->rx) = rxw;
			अन्यथा अगर (dws->n_bytes == 2)
				*(u16 *)(dws->rx) = rxw;
			अन्यथा
				*(u32 *)(dws->rx) = rxw;

			dws->rx += dws->n_bytes;
		पूर्ण
		--dws->rx_len;
	पूर्ण
पूर्ण

पूर्णांक dw_spi_check_status(काष्ठा dw_spi *dws, bool raw)
अणु
	u32 irq_status;
	पूर्णांक ret = 0;

	अगर (raw)
		irq_status = dw_पढ़ोl(dws, DW_SPI_RISR);
	अन्यथा
		irq_status = dw_पढ़ोl(dws, DW_SPI_ISR);

	अगर (irq_status & SPI_INT_RXOI) अणु
		dev_err(&dws->master->dev, "RX FIFO overflow detected\n");
		ret = -EIO;
	पूर्ण

	अगर (irq_status & SPI_INT_RXUI) अणु
		dev_err(&dws->master->dev, "RX FIFO underflow detected\n");
		ret = -EIO;
	पूर्ण

	अगर (irq_status & SPI_INT_TXOI) अणु
		dev_err(&dws->master->dev, "TX FIFO overflow detected\n");
		ret = -EIO;
	पूर्ण

	/* Generically handle the erroneous situation */
	अगर (ret) अणु
		spi_reset_chip(dws);
		अगर (dws->master->cur_msg)
			dws->master->cur_msg->status = ret;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dw_spi_check_status);

अटल irqवापस_t dw_spi_transfer_handler(काष्ठा dw_spi *dws)
अणु
	u16 irq_status = dw_पढ़ोl(dws, DW_SPI_ISR);

	अगर (dw_spi_check_status(dws, false)) अणु
		spi_finalize_current_transfer(dws->master);
		वापस IRQ_HANDLED;
	पूर्ण

	/*
	 * Read data from the Rx FIFO every समय we've got a chance executing
	 * this method. If there is nothing left to receive, terminate the
	 * procedure. Otherwise adjust the Rx FIFO Threshold level अगर it's a
	 * final stage of the transfer. By करोing so we'll get the next IRQ
	 * right when the leftover incoming data is received.
	 */
	dw_पढ़ोer(dws);
	अगर (!dws->rx_len) अणु
		spi_mask_पूर्णांकr(dws, 0xff);
		spi_finalize_current_transfer(dws->master);
	पूर्ण अन्यथा अगर (dws->rx_len <= dw_पढ़ोl(dws, DW_SPI_RXFTLR)) अणु
		dw_ग_लिखोl(dws, DW_SPI_RXFTLR, dws->rx_len - 1);
	पूर्ण

	/*
	 * Send data out अगर Tx FIFO Empty IRQ is received. The IRQ will be
	 * disabled after the data transmission is finished so not to
	 * have the TXE IRQ flood at the final stage of the transfer.
	 */
	अगर (irq_status & SPI_INT_TXEI) अणु
		dw_ग_लिखोr(dws);
		अगर (!dws->tx_len)
			spi_mask_पूर्णांकr(dws, SPI_INT_TXEI);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t dw_spi_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा spi_controller *master = dev_id;
	काष्ठा dw_spi *dws = spi_controller_get_devdata(master);
	u16 irq_status = dw_पढ़ोl(dws, DW_SPI_ISR) & 0x3f;

	अगर (!irq_status)
		वापस IRQ_NONE;

	अगर (!master->cur_msg) अणु
		spi_mask_पूर्णांकr(dws, 0xff);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस dws->transfer_handler(dws);
पूर्ण

अटल u32 dw_spi_prepare_cr0(काष्ठा dw_spi *dws, काष्ठा spi_device *spi)
अणु
	u32 cr0 = 0;

	अगर (!(dws->caps & DW_SPI_CAP_DWC_SSI)) अणु
		/* CTRLR0[ 5: 4] Frame Format */
		cr0 |= SSI_MOTO_SPI << SPI_FRF_OFFSET;

		/*
		 * SPI mode (SCPOL|SCPH)
		 * CTRLR0[ 6] Serial Clock Phase
		 * CTRLR0[ 7] Serial Clock Polarity
		 */
		cr0 |= ((spi->mode & SPI_CPOL) ? 1 : 0) << SPI_SCOL_OFFSET;
		cr0 |= ((spi->mode & SPI_CPHA) ? 1 : 0) << SPI_SCPH_OFFSET;

		/* CTRLR0[11] Shअगरt Register Loop */
		cr0 |= ((spi->mode & SPI_LOOP) ? 1 : 0) << SPI_SRL_OFFSET;
	पूर्ण अन्यथा अणु
		/* CTRLR0[ 7: 6] Frame Format */
		cr0 |= SSI_MOTO_SPI << DWC_SSI_CTRLR0_FRF_OFFSET;

		/*
		 * SPI mode (SCPOL|SCPH)
		 * CTRLR0[ 8] Serial Clock Phase
		 * CTRLR0[ 9] Serial Clock Polarity
		 */
		cr0 |= ((spi->mode & SPI_CPOL) ? 1 : 0) << DWC_SSI_CTRLR0_SCPOL_OFFSET;
		cr0 |= ((spi->mode & SPI_CPHA) ? 1 : 0) << DWC_SSI_CTRLR0_SCPH_OFFSET;

		/* CTRLR0[13] Shअगरt Register Loop */
		cr0 |= ((spi->mode & SPI_LOOP) ? 1 : 0) << DWC_SSI_CTRLR0_SRL_OFFSET;

		अगर (dws->caps & DW_SPI_CAP_KEEMBAY_MST)
			cr0 |= DWC_SSI_CTRLR0_KEEMBAY_MST;
	पूर्ण

	वापस cr0;
पूर्ण

व्योम dw_spi_update_config(काष्ठा dw_spi *dws, काष्ठा spi_device *spi,
			  काष्ठा dw_spi_cfg *cfg)
अणु
	काष्ठा chip_data *chip = spi_get_ctldata(spi);
	u32 cr0 = chip->cr0;
	u32 speed_hz;
	u16 clk_भाग;

	/* CTRLR0[ 4/3: 0] or CTRLR0[ 20: 16] Data Frame Size */
	cr0 |= (cfg->dfs - 1) << dws->dfs_offset;

	अगर (!(dws->caps & DW_SPI_CAP_DWC_SSI))
		/* CTRLR0[ 9:8] Transfer Mode */
		cr0 |= cfg->पंचांगode << SPI_TMOD_OFFSET;
	अन्यथा
		/* CTRLR0[11:10] Transfer Mode */
		cr0 |= cfg->पंचांगode << DWC_SSI_CTRLR0_TMOD_OFFSET;

	dw_ग_लिखोl(dws, DW_SPI_CTRLR0, cr0);

	अगर (cfg->पंचांगode == SPI_TMOD_EPROMREAD || cfg->पंचांगode == SPI_TMOD_RO)
		dw_ग_लिखोl(dws, DW_SPI_CTRLR1, cfg->ndf ? cfg->ndf - 1 : 0);

	/* Note DW APB SSI घड़ी भागider करोesn't support odd numbers */
	clk_भाग = (DIV_ROUND_UP(dws->max_freq, cfg->freq) + 1) & 0xfffe;
	speed_hz = dws->max_freq / clk_भाग;

	अगर (dws->current_freq != speed_hz) अणु
		spi_set_clk(dws, clk_भाग);
		dws->current_freq = speed_hz;
	पूर्ण

	/* Update RX sample delay अगर required */
	अगर (dws->cur_rx_sample_dly != chip->rx_sample_dly) अणु
		dw_ग_लिखोl(dws, DW_SPI_RX_SAMPLE_DLY, chip->rx_sample_dly);
		dws->cur_rx_sample_dly = chip->rx_sample_dly;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(dw_spi_update_config);

अटल व्योम dw_spi_irq_setup(काष्ठा dw_spi *dws)
अणु
	u16 level;
	u8 imask;

	/*
	 * Originally Tx and Rx data lengths match. Rx FIFO Threshold level
	 * will be adjusted at the final stage of the IRQ-based SPI transfer
	 * execution so not to lose the leftover of the incoming data.
	 */
	level = min_t(u16, dws->fअगरo_len / 2, dws->tx_len);
	dw_ग_लिखोl(dws, DW_SPI_TXFTLR, level);
	dw_ग_लिखोl(dws, DW_SPI_RXFTLR, level - 1);

	dws->transfer_handler = dw_spi_transfer_handler;

	imask = SPI_INT_TXEI | SPI_INT_TXOI | SPI_INT_RXUI | SPI_INT_RXOI |
		SPI_INT_RXFI;
	spi_umask_पूर्णांकr(dws, imask);
पूर्ण

/*
 * The iterative procedure of the poll-based transfer is simple: ग_लिखो as much
 * as possible to the Tx FIFO, रुको until the pending to receive data is पढ़ोy
 * to be पढ़ो, पढ़ो it from the Rx FIFO and check whether the perक्रमmed
 * procedure has been successful.
 *
 * Note this method the same way as the IRQ-based transfer won't work well क्रम
 * the SPI devices connected to the controller with native CS due to the
 * स्वतःmatic CS निश्चितion/de-निश्चितion.
 */
अटल पूर्णांक dw_spi_poll_transfer(काष्ठा dw_spi *dws,
				काष्ठा spi_transfer *transfer)
अणु
	काष्ठा spi_delay delay;
	u16 nbits;
	पूर्णांक ret;

	delay.unit = SPI_DELAY_UNIT_SCK;
	nbits = dws->n_bytes * BITS_PER_BYTE;

	करो अणु
		dw_ग_लिखोr(dws);

		delay.value = nbits * (dws->rx_len - dws->tx_len);
		spi_delay_exec(&delay, transfer);

		dw_पढ़ोer(dws);

		ret = dw_spi_check_status(dws, true);
		अगर (ret)
			वापस ret;
	पूर्ण जबतक (dws->rx_len);

	वापस 0;
पूर्ण

अटल पूर्णांक dw_spi_transfer_one(काष्ठा spi_controller *master,
		काष्ठा spi_device *spi, काष्ठा spi_transfer *transfer)
अणु
	काष्ठा dw_spi *dws = spi_controller_get_devdata(master);
	काष्ठा dw_spi_cfg cfg = अणु
		.पंचांगode = SPI_TMOD_TR,
		.dfs = transfer->bits_per_word,
		.freq = transfer->speed_hz,
	पूर्ण;
	पूर्णांक ret;

	dws->dma_mapped = 0;
	dws->n_bytes = DIV_ROUND_UP(transfer->bits_per_word, BITS_PER_BYTE);
	dws->tx = (व्योम *)transfer->tx_buf;
	dws->tx_len = transfer->len / dws->n_bytes;
	dws->rx = transfer->rx_buf;
	dws->rx_len = dws->tx_len;

	/* Ensure the data above is visible क्रम all CPUs */
	smp_mb();

	spi_enable_chip(dws, 0);

	dw_spi_update_config(dws, spi, &cfg);

	transfer->effective_speed_hz = dws->current_freq;

	/* Check अगर current transfer is a DMA transaction */
	अगर (master->can_dma && master->can_dma(master, spi, transfer))
		dws->dma_mapped = master->cur_msg_mapped;

	/* For poll mode just disable all पूर्णांकerrupts */
	spi_mask_पूर्णांकr(dws, 0xff);

	अगर (dws->dma_mapped) अणु
		ret = dws->dma_ops->dma_setup(dws, transfer);
		अगर (ret)
			वापस ret;
	पूर्ण

	spi_enable_chip(dws, 1);

	अगर (dws->dma_mapped)
		वापस dws->dma_ops->dma_transfer(dws, transfer);
	अन्यथा अगर (dws->irq == IRQ_NOTCONNECTED)
		वापस dw_spi_poll_transfer(dws, transfer);

	dw_spi_irq_setup(dws);

	वापस 1;
पूर्ण

अटल व्योम dw_spi_handle_err(काष्ठा spi_controller *master,
		काष्ठा spi_message *msg)
अणु
	काष्ठा dw_spi *dws = spi_controller_get_devdata(master);

	अगर (dws->dma_mapped)
		dws->dma_ops->dma_stop(dws);

	spi_reset_chip(dws);
पूर्ण

अटल पूर्णांक dw_spi_adjust_mem_op_size(काष्ठा spi_mem *mem, काष्ठा spi_mem_op *op)
अणु
	अगर (op->data.dir == SPI_MEM_DATA_IN)
		op->data.nbytes = clamp_val(op->data.nbytes, 0, SPI_NDF_MASK + 1);

	वापस 0;
पूर्ण

अटल bool dw_spi_supports_mem_op(काष्ठा spi_mem *mem,
				   स्थिर काष्ठा spi_mem_op *op)
अणु
	अगर (op->data.buswidth > 1 || op->addr.buswidth > 1 ||
	    op->dummy.buswidth > 1 || op->cmd.buswidth > 1)
		वापस false;

	वापस spi_mem_शेष_supports_op(mem, op);
पूर्ण

अटल पूर्णांक dw_spi_init_mem_buf(काष्ठा dw_spi *dws, स्थिर काष्ठा spi_mem_op *op)
अणु
	अचिन्हित पूर्णांक i, j, len;
	u8 *out;

	/*
	 * Calculate the total length of the EEPROM command transfer and
	 * either use the pre-allocated buffer or create a temporary one.
	 */
	len = op->cmd.nbytes + op->addr.nbytes + op->dummy.nbytes;
	अगर (op->data.dir == SPI_MEM_DATA_OUT)
		len += op->data.nbytes;

	अगर (len <= SPI_BUF_SIZE) अणु
		out = dws->buf;
	पूर्ण अन्यथा अणु
		out = kzalloc(len, GFP_KERNEL);
		अगर (!out)
			वापस -ENOMEM;
	पूर्ण

	/*
	 * Collect the operation code, address and dummy bytes पूर्णांकo the single
	 * buffer. If it's a transfer with data to be sent, also copy it पूर्णांकo the
	 * single buffer in order to speed the data transmission up.
	 */
	क्रम (i = 0; i < op->cmd.nbytes; ++i)
		out[i] = SPI_GET_BYTE(op->cmd.opcode, op->cmd.nbytes - i - 1);
	क्रम (j = 0; j < op->addr.nbytes; ++i, ++j)
		out[i] = SPI_GET_BYTE(op->addr.val, op->addr.nbytes - j - 1);
	क्रम (j = 0; j < op->dummy.nbytes; ++i, ++j)
		out[i] = 0x0;

	अगर (op->data.dir == SPI_MEM_DATA_OUT)
		स_नकल(&out[i], op->data.buf.out, op->data.nbytes);

	dws->n_bytes = 1;
	dws->tx = out;
	dws->tx_len = len;
	अगर (op->data.dir == SPI_MEM_DATA_IN) अणु
		dws->rx = op->data.buf.in;
		dws->rx_len = op->data.nbytes;
	पूर्ण अन्यथा अणु
		dws->rx = शून्य;
		dws->rx_len = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dw_spi_मुक्त_mem_buf(काष्ठा dw_spi *dws)
अणु
	अगर (dws->tx != dws->buf)
		kमुक्त(dws->tx);
पूर्ण

अटल पूर्णांक dw_spi_ग_लिखो_then_पढ़ो(काष्ठा dw_spi *dws, काष्ठा spi_device *spi)
अणु
	u32 room, entries, sts;
	अचिन्हित पूर्णांक len;
	u8 *buf;

	/*
	 * At initial stage we just pre-fill the Tx FIFO in with no rush,
	 * since native CS hasn't been enabled yet and the स्वतःmatic data
	 * transmission won't start til we करो that.
	 */
	len = min(dws->fअगरo_len, dws->tx_len);
	buf = dws->tx;
	जबतक (len--)
		dw_ग_लिखो_io_reg(dws, DW_SPI_DR, *buf++);

	/*
	 * After setting any bit in the SER रेजिस्टर the transmission will
	 * start स्वतःmatically. We have to keep up with that procedure
	 * otherwise the CS de-निश्चितion will happen whereupon the memory
	 * operation will be pre-terminated.
	 */
	len = dws->tx_len - ((व्योम *)buf - dws->tx);
	dw_spi_set_cs(spi, false);
	जबतक (len) अणु
		entries = पढ़ोl_relaxed(dws->regs + DW_SPI_TXFLR);
		अगर (!entries) अणु
			dev_err(&dws->master->dev, "CS de-assertion on Tx\n");
			वापस -EIO;
		पूर्ण
		room = min(dws->fअगरo_len - entries, len);
		क्रम (; room; --room, --len)
			dw_ग_लिखो_io_reg(dws, DW_SPI_DR, *buf++);
	पूर्ण

	/*
	 * Data fetching will start स्वतःmatically अगर the EEPROM-पढ़ो mode is
	 * activated. We have to keep up with the incoming data pace to
	 * prevent the Rx FIFO overflow causing the inbound data loss.
	 */
	len = dws->rx_len;
	buf = dws->rx;
	जबतक (len) अणु
		entries = पढ़ोl_relaxed(dws->regs + DW_SPI_RXFLR);
		अगर (!entries) अणु
			sts = पढ़ोl_relaxed(dws->regs + DW_SPI_RISR);
			अगर (sts & SPI_INT_RXOI) अणु
				dev_err(&dws->master->dev, "FIFO overflow on Rx\n");
				वापस -EIO;
			पूर्ण
			जारी;
		पूर्ण
		entries = min(entries, len);
		क्रम (; entries; --entries, --len)
			*buf++ = dw_पढ़ो_io_reg(dws, DW_SPI_DR);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत bool dw_spi_ctlr_busy(काष्ठा dw_spi *dws)
अणु
	वापस dw_पढ़ोl(dws, DW_SPI_SR) & SR_BUSY;
पूर्ण

अटल पूर्णांक dw_spi_रुको_mem_op_करोne(काष्ठा dw_spi *dws)
अणु
	पूर्णांक retry = SPI_WAIT_RETRIES;
	काष्ठा spi_delay delay;
	अचिन्हित दीर्घ ns, us;
	u32 nents;

	nents = dw_पढ़ोl(dws, DW_SPI_TXFLR);
	ns = NSEC_PER_SEC / dws->current_freq * nents;
	ns *= dws->n_bytes * BITS_PER_BYTE;
	अगर (ns <= NSEC_PER_USEC) अणु
		delay.unit = SPI_DELAY_UNIT_NSECS;
		delay.value = ns;
	पूर्ण अन्यथा अणु
		us = DIV_ROUND_UP(ns, NSEC_PER_USEC);
		delay.unit = SPI_DELAY_UNIT_USECS;
		delay.value = clamp_val(us, 0, अच_लघु_उच्च);
	पूर्ण

	जबतक (dw_spi_ctlr_busy(dws) && retry--)
		spi_delay_exec(&delay, शून्य);

	अगर (retry < 0) अणु
		dev_err(&dws->master->dev, "Mem op hanged up\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dw_spi_stop_mem_op(काष्ठा dw_spi *dws, काष्ठा spi_device *spi)
अणु
	spi_enable_chip(dws, 0);
	dw_spi_set_cs(spi, true);
	spi_enable_chip(dws, 1);
पूर्ण

/*
 * The SPI memory operation implementation below is the best choice क्रम the
 * devices, which are selected by the native chip-select lane. It's
 * specअगरically developed to workaround the problem with स्वतःmatic chip-select
 * lane toggle when there is no data in the Tx FIFO buffer. Luckily the current
 * SPI-mem core calls exec_op() callback only अगर the GPIO-based CS is
 * unavailable.
 */
अटल पूर्णांक dw_spi_exec_mem_op(काष्ठा spi_mem *mem, स्थिर काष्ठा spi_mem_op *op)
अणु
	काष्ठा dw_spi *dws = spi_controller_get_devdata(mem->spi->controller);
	काष्ठा dw_spi_cfg cfg;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	/*
	 * Collect the outbound data पूर्णांकo a single buffer to speed the
	 * transmission up at least on the initial stage.
	 */
	ret = dw_spi_init_mem_buf(dws, op);
	अगर (ret)
		वापस ret;

	/*
	 * DW SPI EEPROM-पढ़ो mode is required only क्रम the SPI memory Data-IN
	 * operation. Transmit-only mode is suitable क्रम the rest of them.
	 */
	cfg.dfs = 8;
	cfg.freq = clamp(mem->spi->max_speed_hz, 0U, dws->max_mem_freq);
	अगर (op->data.dir == SPI_MEM_DATA_IN) अणु
		cfg.पंचांगode = SPI_TMOD_EPROMREAD;
		cfg.ndf = op->data.nbytes;
	पूर्ण अन्यथा अणु
		cfg.पंचांगode = SPI_TMOD_TO;
	पूर्ण

	spi_enable_chip(dws, 0);

	dw_spi_update_config(dws, mem->spi, &cfg);

	spi_mask_पूर्णांकr(dws, 0xff);

	spi_enable_chip(dws, 1);

	/*
	 * DW APB SSI controller has very nasty peculiarities. First originally
	 * (without any venकरोr-specअगरic modअगरications) it करोesn't provide a
	 * direct way to set and clear the native chip-select संकेत. Instead
	 * the controller निश्चितs the CS lane अगर Tx FIFO isn't empty and a
	 * transmission is going on, and स्वतःmatically de-निश्चितs it back to
	 * the high level अगर the Tx FIFO करोesn't have anything to be pushed
	 * out. Due to that a multi-tasking or heavy IRQs activity might be
	 * fatal, since the transfer procedure preemption may cause the Tx FIFO
	 * getting empty and sudden CS de-निश्चितion, which in the middle of the
	 * transfer will most likely cause the data loss. Secondly the
	 * EEPROM-पढ़ो or Read-only DW SPI transfer modes imply the incoming
	 * data being स्वतःmatically pulled in पूर्णांकo the Rx FIFO. So अगर the
	 * driver software is late in fetching the data from the FIFO beक्रमe
	 * it's overflown, new incoming data will be lost. In order to make
	 * sure the executed memory operations are CS-atomic and to prevent the
	 * Rx FIFO overflow we have to disable the local पूर्णांकerrupts so to block
	 * any preemption during the subsequent IO operations.
	 *
	 * Note. At some circumstances disabling IRQs may not help to prevent
	 * the problems described above. The CS de-निश्चितion and Rx FIFO
	 * overflow may still happen due to the relatively slow प्रणाली bus or
	 * CPU not working fast enough, so the ग_लिखो-then-पढ़ो algo implemented
	 * here just won't keep up with the SPI bus data transfer. Such
	 * situation is highly platक्रमm specअगरic and is supposed to be fixed by
	 * manually restricting the SPI bus frequency using the
	 * dws->max_mem_freq parameter.
	 */
	local_irq_save(flags);
	preempt_disable();

	ret = dw_spi_ग_लिखो_then_पढ़ो(dws, mem->spi);

	local_irq_restore(flags);
	preempt_enable();

	/*
	 * Wait क्रम the operation being finished and check the controller
	 * status only अगर there hasn't been any run-समय error detected. In the
	 * क्रमmer हाल it's just poपूर्णांकless. In the later one to prevent an
	 * additional error message prपूर्णांकing since any hw error flag being set
	 * would be due to an error detected on the data transfer.
	 */
	अगर (!ret) अणु
		ret = dw_spi_रुको_mem_op_करोne(dws);
		अगर (!ret)
			ret = dw_spi_check_status(dws, true);
	पूर्ण

	dw_spi_stop_mem_op(dws, mem->spi);

	dw_spi_मुक्त_mem_buf(dws);

	वापस ret;
पूर्ण

/*
 * Initialize the शेष memory operations अगर a glue layer hasn't specअगरied
 * custom ones. Direct mapping operations will be preserved anyway since DW SPI
 * controller करोesn't have an embedded dirmap पूर्णांकerface. Note the memory
 * operations implemented in this driver is the best choice only क्रम the DW APB
 * SSI controller with standard native CS functionality. If a hardware venकरोr
 * has fixed the स्वतःmatic CS निश्चितion/de-निश्चितion peculiarity, then it will
 * be safer to use the normal SPI-messages-based transfers implementation.
 */
अटल व्योम dw_spi_init_mem_ops(काष्ठा dw_spi *dws)
अणु
	अगर (!dws->mem_ops.exec_op && !(dws->caps & DW_SPI_CAP_CS_OVERRIDE) &&
	    !dws->set_cs) अणु
		dws->mem_ops.adjust_op_size = dw_spi_adjust_mem_op_size;
		dws->mem_ops.supports_op = dw_spi_supports_mem_op;
		dws->mem_ops.exec_op = dw_spi_exec_mem_op;
		अगर (!dws->max_mem_freq)
			dws->max_mem_freq = dws->max_freq;
	पूर्ण
पूर्ण

/* This may be called twice क्रम each spi dev */
अटल पूर्णांक dw_spi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा dw_spi *dws = spi_controller_get_devdata(spi->controller);
	काष्ठा chip_data *chip;

	/* Only alloc on first setup */
	chip = spi_get_ctldata(spi);
	अगर (!chip) अणु
		काष्ठा dw_spi *dws = spi_controller_get_devdata(spi->controller);
		u32 rx_sample_dly_ns;

		chip = kzalloc(माप(काष्ठा chip_data), GFP_KERNEL);
		अगर (!chip)
			वापस -ENOMEM;
		spi_set_ctldata(spi, chip);
		/* Get specअगरic / शेष rx-sample-delay */
		अगर (device_property_पढ़ो_u32(&spi->dev,
					     "rx-sample-delay-ns",
					     &rx_sample_dly_ns) != 0)
			/* Use शेष controller value */
			rx_sample_dly_ns = dws->def_rx_sample_dly_ns;
		chip->rx_sample_dly = DIV_ROUND_CLOSEST(rx_sample_dly_ns,
							NSEC_PER_SEC /
							dws->max_freq);
	पूर्ण

	/*
	 * Update CR0 data each समय the setup callback is invoked since
	 * the device parameters could have been changed, क्रम instance, by
	 * the MMC SPI driver or something अन्यथा.
	 */
	chip->cr0 = dw_spi_prepare_cr0(dws, spi);

	वापस 0;
पूर्ण

अटल व्योम dw_spi_cleanup(काष्ठा spi_device *spi)
अणु
	काष्ठा chip_data *chip = spi_get_ctldata(spi);

	kमुक्त(chip);
	spi_set_ctldata(spi, शून्य);
पूर्ण

/* Restart the controller, disable all पूर्णांकerrupts, clean rx fअगरo */
अटल व्योम spi_hw_init(काष्ठा device *dev, काष्ठा dw_spi *dws)
अणु
	spi_reset_chip(dws);

	/*
	 * Try to detect the FIFO depth अगर not set by पूर्णांकerface driver,
	 * the depth could be from 2 to 256 from HW spec
	 */
	अगर (!dws->fअगरo_len) अणु
		u32 fअगरo;

		क्रम (fअगरo = 1; fअगरo < 256; fअगरo++) अणु
			dw_ग_लिखोl(dws, DW_SPI_TXFTLR, fअगरo);
			अगर (fअगरo != dw_पढ़ोl(dws, DW_SPI_TXFTLR))
				अवरोध;
		पूर्ण
		dw_ग_लिखोl(dws, DW_SPI_TXFTLR, 0);

		dws->fअगरo_len = (fअगरo == 1) ? 0 : fअगरo;
		dev_dbg(dev, "Detected FIFO size: %u bytes\n", dws->fअगरo_len);
	पूर्ण

	/*
	 * Detect CTRLR0.DFS field size and offset by testing the lowest bits
	 * writability. Note DWC SSI controller also has the extended DFS, but
	 * with zero offset.
	 */
	अगर (!(dws->caps & DW_SPI_CAP_DWC_SSI)) अणु
		u32 cr0, पंचांगp = dw_पढ़ोl(dws, DW_SPI_CTRLR0);

		spi_enable_chip(dws, 0);
		dw_ग_लिखोl(dws, DW_SPI_CTRLR0, 0xffffffff);
		cr0 = dw_पढ़ोl(dws, DW_SPI_CTRLR0);
		dw_ग_लिखोl(dws, DW_SPI_CTRLR0, पंचांगp);
		spi_enable_chip(dws, 1);

		अगर (!(cr0 & SPI_DFS_MASK)) अणु
			dws->caps |= DW_SPI_CAP_DFS32;
			dws->dfs_offset = SPI_DFS32_OFFSET;
			dev_dbg(dev, "Detected 32-bits max data frame size\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		dws->caps |= DW_SPI_CAP_DFS32;
	पूर्ण

	/* enable HW fixup क्रम explicit CS deselect क्रम Amazon's alpine chip */
	अगर (dws->caps & DW_SPI_CAP_CS_OVERRIDE)
		dw_ग_लिखोl(dws, DW_SPI_CS_OVERRIDE, 0xF);
पूर्ण

पूर्णांक dw_spi_add_host(काष्ठा device *dev, काष्ठा dw_spi *dws)
अणु
	काष्ठा spi_controller *master;
	पूर्णांक ret;

	अगर (!dws)
		वापस -EINVAL;

	master = spi_alloc_master(dev, 0);
	अगर (!master)
		वापस -ENOMEM;

	dws->master = master;
	dws->dma_addr = (dma_addr_t)(dws->paddr + DW_SPI_DR);

	spi_controller_set_devdata(master, dws);

	/* Basic HW init */
	spi_hw_init(dev, dws);

	ret = request_irq(dws->irq, dw_spi_irq, IRQF_SHARED, dev_name(dev),
			  master);
	अगर (ret < 0 && ret != -ENOTCONN) अणु
		dev_err(dev, "can not get IRQ\n");
		जाओ err_मुक्त_master;
	पूर्ण

	dw_spi_init_mem_ops(dws);

	master->use_gpio_descriptors = true;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_LOOP;
	अगर (dws->caps & DW_SPI_CAP_DFS32)
		master->bits_per_word_mask = SPI_BPW_RANGE_MASK(4, 32);
	अन्यथा
		master->bits_per_word_mask = SPI_BPW_RANGE_MASK(4, 16);
	master->bus_num = dws->bus_num;
	master->num_chipselect = dws->num_cs;
	master->setup = dw_spi_setup;
	master->cleanup = dw_spi_cleanup;
	अगर (dws->set_cs)
		master->set_cs = dws->set_cs;
	अन्यथा
		master->set_cs = dw_spi_set_cs;
	master->transfer_one = dw_spi_transfer_one;
	master->handle_err = dw_spi_handle_err;
	अगर (dws->mem_ops.exec_op)
		master->mem_ops = &dws->mem_ops;
	master->max_speed_hz = dws->max_freq;
	master->dev.of_node = dev->of_node;
	master->dev.fwnode = dev->fwnode;
	master->flags = SPI_MASTER_GPIO_SS;
	master->स्वतः_runसमय_pm = true;

	/* Get शेष rx sample delay */
	device_property_पढ़ो_u32(dev, "rx-sample-delay-ns",
				 &dws->def_rx_sample_dly_ns);

	अगर (dws->dma_ops && dws->dma_ops->dma_init) अणु
		ret = dws->dma_ops->dma_init(dev, dws);
		अगर (ret) अणु
			dev_warn(dev, "DMA init failed\n");
		पूर्ण अन्यथा अणु
			master->can_dma = dws->dma_ops->can_dma;
			master->flags |= SPI_CONTROLLER_MUST_TX;
		पूर्ण
	पूर्ण

	ret = spi_रेजिस्टर_controller(master);
	अगर (ret) अणु
		dev_err(&master->dev, "problem registering spi master\n");
		जाओ err_dma_निकास;
	पूर्ण

	dw_spi_debugfs_init(dws);
	वापस 0;

err_dma_निकास:
	अगर (dws->dma_ops && dws->dma_ops->dma_निकास)
		dws->dma_ops->dma_निकास(dws);
	spi_enable_chip(dws, 0);
	मुक्त_irq(dws->irq, master);
err_मुक्त_master:
	spi_controller_put(master);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dw_spi_add_host);

व्योम dw_spi_हटाओ_host(काष्ठा dw_spi *dws)
अणु
	dw_spi_debugfs_हटाओ(dws);

	spi_unरेजिस्टर_controller(dws->master);

	अगर (dws->dma_ops && dws->dma_ops->dma_निकास)
		dws->dma_ops->dma_निकास(dws);

	spi_shutकरोwn_chip(dws);

	मुक्त_irq(dws->irq, dws->master);
पूर्ण
EXPORT_SYMBOL_GPL(dw_spi_हटाओ_host);

पूर्णांक dw_spi_suspend_host(काष्ठा dw_spi *dws)
अणु
	पूर्णांक ret;

	ret = spi_controller_suspend(dws->master);
	अगर (ret)
		वापस ret;

	spi_shutकरोwn_chip(dws);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(dw_spi_suspend_host);

पूर्णांक dw_spi_resume_host(काष्ठा dw_spi *dws)
अणु
	spi_hw_init(&dws->master->dev, dws);
	वापस spi_controller_resume(dws->master);
पूर्ण
EXPORT_SYMBOL_GPL(dw_spi_resume_host);

MODULE_AUTHOR("Feng Tang <feng.tang@intel.com>");
MODULE_DESCRIPTION("Driver for DesignWare SPI controller core");
MODULE_LICENSE("GPL v2");
