<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Aपंचांगel AT32 and AT91 SPI Controllers
 *
 * Copyright (C) 2006 Aपंचांगel Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>

#समावेश <linux/पन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <trace/events/spi.h>

/* SPI रेजिस्टर offsets */
#घोषणा SPI_CR					0x0000
#घोषणा SPI_MR					0x0004
#घोषणा SPI_RDR					0x0008
#घोषणा SPI_TDR					0x000c
#घोषणा SPI_SR					0x0010
#घोषणा SPI_IER					0x0014
#घोषणा SPI_IDR					0x0018
#घोषणा SPI_IMR					0x001c
#घोषणा SPI_CSR0				0x0030
#घोषणा SPI_CSR1				0x0034
#घोषणा SPI_CSR2				0x0038
#घोषणा SPI_CSR3				0x003c
#घोषणा SPI_FMR					0x0040
#घोषणा SPI_FLR					0x0044
#घोषणा SPI_VERSION				0x00fc
#घोषणा SPI_RPR					0x0100
#घोषणा SPI_RCR					0x0104
#घोषणा SPI_TPR					0x0108
#घोषणा SPI_TCR					0x010c
#घोषणा SPI_RNPR				0x0110
#घोषणा SPI_RNCR				0x0114
#घोषणा SPI_TNPR				0x0118
#घोषणा SPI_TNCR				0x011c
#घोषणा SPI_PTCR				0x0120
#घोषणा SPI_PTSR				0x0124

/* Bitfields in CR */
#घोषणा SPI_SPIEN_OFFSET			0
#घोषणा SPI_SPIEN_SIZE				1
#घोषणा SPI_SPIDIS_OFFSET			1
#घोषणा SPI_SPIDIS_SIZE				1
#घोषणा SPI_SWRST_OFFSET			7
#घोषणा SPI_SWRST_SIZE				1
#घोषणा SPI_LASTXFER_OFFSET			24
#घोषणा SPI_LASTXFER_SIZE			1
#घोषणा SPI_TXFCLR_OFFSET			16
#घोषणा SPI_TXFCLR_SIZE				1
#घोषणा SPI_RXFCLR_OFFSET			17
#घोषणा SPI_RXFCLR_SIZE				1
#घोषणा SPI_FIFOEN_OFFSET			30
#घोषणा SPI_FIFOEN_SIZE				1
#घोषणा SPI_FIFODIS_OFFSET			31
#घोषणा SPI_FIFODIS_SIZE			1

/* Bitfields in MR */
#घोषणा SPI_MSTR_OFFSET				0
#घोषणा SPI_MSTR_SIZE				1
#घोषणा SPI_PS_OFFSET				1
#घोषणा SPI_PS_SIZE				1
#घोषणा SPI_PCSDEC_OFFSET			2
#घोषणा SPI_PCSDEC_SIZE				1
#घोषणा SPI_FDIV_OFFSET				3
#घोषणा SPI_FDIV_SIZE				1
#घोषणा SPI_MODFDIS_OFFSET			4
#घोषणा SPI_MODFDIS_SIZE			1
#घोषणा SPI_WDRBT_OFFSET			5
#घोषणा SPI_WDRBT_SIZE				1
#घोषणा SPI_LLB_OFFSET				7
#घोषणा SPI_LLB_SIZE				1
#घोषणा SPI_PCS_OFFSET				16
#घोषणा SPI_PCS_SIZE				4
#घोषणा SPI_DLYBCS_OFFSET			24
#घोषणा SPI_DLYBCS_SIZE				8

/* Bitfields in RDR */
#घोषणा SPI_RD_OFFSET				0
#घोषणा SPI_RD_SIZE				16

/* Bitfields in TDR */
#घोषणा SPI_TD_OFFSET				0
#घोषणा SPI_TD_SIZE				16

/* Bitfields in SR */
#घोषणा SPI_RDRF_OFFSET				0
#घोषणा SPI_RDRF_SIZE				1
#घोषणा SPI_TDRE_OFFSET				1
#घोषणा SPI_TDRE_SIZE				1
#घोषणा SPI_MODF_OFFSET				2
#घोषणा SPI_MODF_SIZE				1
#घोषणा SPI_OVRES_OFFSET			3
#घोषणा SPI_OVRES_SIZE				1
#घोषणा SPI_ENDRX_OFFSET			4
#घोषणा SPI_ENDRX_SIZE				1
#घोषणा SPI_ENDTX_OFFSET			5
#घोषणा SPI_ENDTX_SIZE				1
#घोषणा SPI_RXBUFF_OFFSET			6
#घोषणा SPI_RXBUFF_SIZE				1
#घोषणा SPI_TXBUFE_OFFSET			7
#घोषणा SPI_TXBUFE_SIZE				1
#घोषणा SPI_NSSR_OFFSET				8
#घोषणा SPI_NSSR_SIZE				1
#घोषणा SPI_TXEMPTY_OFFSET			9
#घोषणा SPI_TXEMPTY_SIZE			1
#घोषणा SPI_SPIENS_OFFSET			16
#घोषणा SPI_SPIENS_SIZE				1
#घोषणा SPI_TXFEF_OFFSET			24
#घोषणा SPI_TXFEF_SIZE				1
#घोषणा SPI_TXFFF_OFFSET			25
#घोषणा SPI_TXFFF_SIZE				1
#घोषणा SPI_TXFTHF_OFFSET			26
#घोषणा SPI_TXFTHF_SIZE				1
#घोषणा SPI_RXFEF_OFFSET			27
#घोषणा SPI_RXFEF_SIZE				1
#घोषणा SPI_RXFFF_OFFSET			28
#घोषणा SPI_RXFFF_SIZE				1
#घोषणा SPI_RXFTHF_OFFSET			29
#घोषणा SPI_RXFTHF_SIZE				1
#घोषणा SPI_TXFPTEF_OFFSET			30
#घोषणा SPI_TXFPTEF_SIZE			1
#घोषणा SPI_RXFPTEF_OFFSET			31
#घोषणा SPI_RXFPTEF_SIZE			1

/* Bitfields in CSR0 */
#घोषणा SPI_CPOL_OFFSET				0
#घोषणा SPI_CPOL_SIZE				1
#घोषणा SPI_NCPHA_OFFSET			1
#घोषणा SPI_NCPHA_SIZE				1
#घोषणा SPI_CSAAT_OFFSET			3
#घोषणा SPI_CSAAT_SIZE				1
#घोषणा SPI_BITS_OFFSET				4
#घोषणा SPI_BITS_SIZE				4
#घोषणा SPI_SCBR_OFFSET				8
#घोषणा SPI_SCBR_SIZE				8
#घोषणा SPI_DLYBS_OFFSET			16
#घोषणा SPI_DLYBS_SIZE				8
#घोषणा SPI_DLYBCT_OFFSET			24
#घोषणा SPI_DLYBCT_SIZE				8

/* Bitfields in RCR */
#घोषणा SPI_RXCTR_OFFSET			0
#घोषणा SPI_RXCTR_SIZE				16

/* Bitfields in TCR */
#घोषणा SPI_TXCTR_OFFSET			0
#घोषणा SPI_TXCTR_SIZE				16

/* Bitfields in RNCR */
#घोषणा SPI_RXNCR_OFFSET			0
#घोषणा SPI_RXNCR_SIZE				16

/* Bitfields in TNCR */
#घोषणा SPI_TXNCR_OFFSET			0
#घोषणा SPI_TXNCR_SIZE				16

/* Bitfields in PTCR */
#घोषणा SPI_RXTEN_OFFSET			0
#घोषणा SPI_RXTEN_SIZE				1
#घोषणा SPI_RXTDIS_OFFSET			1
#घोषणा SPI_RXTDIS_SIZE				1
#घोषणा SPI_TXTEN_OFFSET			8
#घोषणा SPI_TXTEN_SIZE				1
#घोषणा SPI_TXTDIS_OFFSET			9
#घोषणा SPI_TXTDIS_SIZE				1

/* Bitfields in FMR */
#घोषणा SPI_TXRDYM_OFFSET			0
#घोषणा SPI_TXRDYM_SIZE				2
#घोषणा SPI_RXRDYM_OFFSET			4
#घोषणा SPI_RXRDYM_SIZE				2
#घोषणा SPI_TXFTHRES_OFFSET			16
#घोषणा SPI_TXFTHRES_SIZE			6
#घोषणा SPI_RXFTHRES_OFFSET			24
#घोषणा SPI_RXFTHRES_SIZE			6

/* Bitfields in FLR */
#घोषणा SPI_TXFL_OFFSET				0
#घोषणा SPI_TXFL_SIZE				6
#घोषणा SPI_RXFL_OFFSET				16
#घोषणा SPI_RXFL_SIZE				6

/* Constants क्रम BITS */
#घोषणा SPI_BITS_8_BPT				0
#घोषणा SPI_BITS_9_BPT				1
#घोषणा SPI_BITS_10_BPT				2
#घोषणा SPI_BITS_11_BPT				3
#घोषणा SPI_BITS_12_BPT				4
#घोषणा SPI_BITS_13_BPT				5
#घोषणा SPI_BITS_14_BPT				6
#घोषणा SPI_BITS_15_BPT				7
#घोषणा SPI_BITS_16_BPT				8
#घोषणा SPI_ONE_DATA				0
#घोषणा SPI_TWO_DATA				1
#घोषणा SPI_FOUR_DATA				2

/* Bit manipulation macros */
#घोषणा SPI_BIT(name) \
	(1 << SPI_##name##_OFFSET)
#घोषणा SPI_BF(name, value) \
	(((value) & ((1 << SPI_##name##_SIZE) - 1)) << SPI_##name##_OFFSET)
#घोषणा SPI_BFEXT(name, value) \
	(((value) >> SPI_##name##_OFFSET) & ((1 << SPI_##name##_SIZE) - 1))
#घोषणा SPI_BFINS(name, value, old) \
	(((old) & ~(((1 << SPI_##name##_SIZE) - 1) << SPI_##name##_OFFSET)) \
	  | SPI_BF(name, value))

/* Register access macros */
#घोषणा spi_पढ़ोl(port, reg) \
	पढ़ोl_relaxed((port)->regs + SPI_##reg)
#घोषणा spi_ग_लिखोl(port, reg, value) \
	ग_लिखोl_relaxed((value), (port)->regs + SPI_##reg)
#घोषणा spi_ग_लिखोw(port, reg, value) \
	ग_लिखोw_relaxed((value), (port)->regs + SPI_##reg)

/* use PIO क्रम small transfers, aव्योमing DMA setup/tearकरोwn overhead and
 * cache operations; better heuristics consider wordsize and bitrate.
 */
#घोषणा DMA_MIN_BYTES	16

#घोषणा SPI_DMA_TIMEOUT		(msecs_to_jअगरfies(1000))

#घोषणा AUTOSUSPEND_TIMEOUT	2000

काष्ठा aपंचांगel_spi_caps अणु
	bool	is_spi2;
	bool	has_wdrbt;
	bool	has_dma_support;
	bool	has_pdc_support;
पूर्ण;

/*
 * The core SPI transfer engine just talks to a रेजिस्टर bank to set up
 * DMA transfers; transfer queue progress is driven by IRQs.  The घड़ी
 * framework provides the base घड़ी, subभागided क्रम each spi_device.
 */
काष्ठा aपंचांगel_spi अणु
	spinlock_t		lock;
	अचिन्हित दीर्घ		flags;

	phys_addr_t		phybase;
	व्योम __iomem		*regs;
	पूर्णांक			irq;
	काष्ठा clk		*clk;
	काष्ठा platक्रमm_device	*pdev;
	अचिन्हित दीर्घ		spi_clk;

	काष्ठा spi_transfer	*current_transfer;
	पूर्णांक			current_reमुख्यing_bytes;
	पूर्णांक			करोne_status;
	dma_addr_t		dma_addr_rx_bbuf;
	dma_addr_t		dma_addr_tx_bbuf;
	व्योम			*addr_rx_bbuf;
	व्योम			*addr_tx_bbuf;

	काष्ठा completion	xfer_completion;

	काष्ठा aपंचांगel_spi_caps	caps;

	bool			use_dma;
	bool			use_pdc;

	bool			keep_cs;

	u32			fअगरo_size;
	u8			native_cs_मुक्त;
	u8			native_cs_क्रम_gpio;
पूर्ण;

/* Controller-specअगरic per-slave state */
काष्ठा aपंचांगel_spi_device अणु
	u32			csr;
पूर्ण;

#घोषणा SPI_MAX_DMA_XFER	65535 /* true क्रम both PDC and DMA */
#घोषणा INVALID_DMA_ADDRESS	0xffffffff

/*
 * Version 2 of the SPI controller has
 *  - CR.LASTXFER
 *  - SPI_MR.DIV32 may become FDIV or must-be-zero (here: always zero)
 *  - SPI_SR.TXEMPTY, SPI_SR.NSSR (and corresponding irqs)
 *  - SPI_CSRx.CSAAT
 *  - SPI_CSRx.SBCR allows faster घड़ीing
 */
अटल bool aपंचांगel_spi_is_v2(काष्ठा aपंचांगel_spi *as)
अणु
	वापस as->caps.is_spi2;
पूर्ण

/*
 * Earlier SPI controllers (e.g. on at91rm9200) have a design bug whereby
 * they assume that spi slave device state will not change on deselect, so
 * that स्वतःmagic deselection is OK.  ("NPCSx rises अगर no data is to be
 * transmitted")  Not so!  Workaround uses nCSx pins as GPIOs; or newer
 * controllers have CSAAT and मित्रs.
 *
 * Even controller newer than ar91rm9200, using GPIOs can make sens as
 * it lets us support active-high chipselects despite the controller's
 * belief that only active-low devices/प्रणालीs exists.
 *
 * However, at91rm9200 has a second erratum whereby nCS0 करोesn't work
 * right when driven with GPIO.  ("Mode Fault करोes not allow more than one
 * Master on Chip Select 0.")  No workaround exists क्रम that ... so क्रम
 * nCS0 on that chip, we (a) करोn't use the GPIO, (b) can't support CS_HIGH,
 * and (c) will trigger that first erratum in some हालs.
 */

अटल व्योम cs_activate(काष्ठा aपंचांगel_spi *as, काष्ठा spi_device *spi)
अणु
	काष्ठा aपंचांगel_spi_device *asd = spi->controller_state;
	पूर्णांक chip_select;
	u32 mr;

	अगर (spi->cs_gpiod)
		chip_select = as->native_cs_क्रम_gpio;
	अन्यथा
		chip_select = spi->chip_select;

	अगर (aपंचांगel_spi_is_v2(as)) अणु
		spi_ग_लिखोl(as, CSR0 + 4 * chip_select, asd->csr);
		/* For the low SPI version, there is a issue that PDC transfer
		 * on CS1,2,3 needs SPI_CSR0.BITS config as SPI_CSR1,2,3.BITS
		 */
		spi_ग_लिखोl(as, CSR0, asd->csr);
		अगर (as->caps.has_wdrbt) अणु
			spi_ग_लिखोl(as, MR,
					SPI_BF(PCS, ~(0x01 << chip_select))
					| SPI_BIT(WDRBT)
					| SPI_BIT(MODFDIS)
					| SPI_BIT(MSTR));
		पूर्ण अन्यथा अणु
			spi_ग_लिखोl(as, MR,
					SPI_BF(PCS, ~(0x01 << chip_select))
					| SPI_BIT(MODFDIS)
					| SPI_BIT(MSTR));
		पूर्ण

		mr = spi_पढ़ोl(as, MR);
		अगर (spi->cs_gpiod)
			gpiod_set_value(spi->cs_gpiod, 1);
	पूर्ण अन्यथा अणु
		u32 cpol = (spi->mode & SPI_CPOL) ? SPI_BIT(CPOL) : 0;
		पूर्णांक i;
		u32 csr;

		/* Make sure घड़ी polarity is correct */
		क्रम (i = 0; i < spi->master->num_chipselect; i++) अणु
			csr = spi_पढ़ोl(as, CSR0 + 4 * i);
			अगर ((csr ^ cpol) & SPI_BIT(CPOL))
				spi_ग_लिखोl(as, CSR0 + 4 * i,
						csr ^ SPI_BIT(CPOL));
		पूर्ण

		mr = spi_पढ़ोl(as, MR);
		mr = SPI_BFINS(PCS, ~(1 << chip_select), mr);
		अगर (spi->cs_gpiod)
			gpiod_set_value(spi->cs_gpiod, 1);
		spi_ग_लिखोl(as, MR, mr);
	पूर्ण

	dev_dbg(&spi->dev, "activate NPCS, mr %08x\n", mr);
पूर्ण

अटल व्योम cs_deactivate(काष्ठा aपंचांगel_spi *as, काष्ठा spi_device *spi)
अणु
	पूर्णांक chip_select;
	u32 mr;

	अगर (spi->cs_gpiod)
		chip_select = as->native_cs_क्रम_gpio;
	अन्यथा
		chip_select = spi->chip_select;

	/* only deactivate *this* device; someबार transfers to
	 * another device may be active when this routine is called.
	 */
	mr = spi_पढ़ोl(as, MR);
	अगर (~SPI_BFEXT(PCS, mr) & (1 << chip_select)) अणु
		mr = SPI_BFINS(PCS, 0xf, mr);
		spi_ग_लिखोl(as, MR, mr);
	पूर्ण

	dev_dbg(&spi->dev, "DEactivate NPCS, mr %08x\n", mr);

	अगर (!spi->cs_gpiod)
		spi_ग_लिखोl(as, CR, SPI_BIT(LASTXFER));
	अन्यथा
		gpiod_set_value(spi->cs_gpiod, 0);
पूर्ण

अटल व्योम aपंचांगel_spi_lock(काष्ठा aपंचांगel_spi *as) __acquires(&as->lock)
अणु
	spin_lock_irqsave(&as->lock, as->flags);
पूर्ण

अटल व्योम aपंचांगel_spi_unlock(काष्ठा aपंचांगel_spi *as) __releases(&as->lock)
अणु
	spin_unlock_irqrestore(&as->lock, as->flags);
पूर्ण

अटल अंतरभूत bool aपंचांगel_spi_is_vदो_स्मृति_xfer(काष्ठा spi_transfer *xfer)
अणु
	वापस is_vदो_स्मृति_addr(xfer->tx_buf) || is_vदो_स्मृति_addr(xfer->rx_buf);
पूर्ण

अटल अंतरभूत bool aपंचांगel_spi_use_dma(काष्ठा aपंचांगel_spi *as,
				काष्ठा spi_transfer *xfer)
अणु
	वापस as->use_dma && xfer->len >= DMA_MIN_BYTES;
पूर्ण

अटल bool aपंचांगel_spi_can_dma(काष्ठा spi_master *master,
			      काष्ठा spi_device *spi,
			      काष्ठा spi_transfer *xfer)
अणु
	काष्ठा aपंचांगel_spi *as = spi_master_get_devdata(master);

	अगर (IS_ENABLED(CONFIG_SOC_SAM_V4_V5))
		वापस aपंचांगel_spi_use_dma(as, xfer) &&
			!aपंचांगel_spi_is_vदो_स्मृति_xfer(xfer);
	अन्यथा
		वापस aपंचांगel_spi_use_dma(as, xfer);

पूर्ण

अटल पूर्णांक aपंचांगel_spi_dma_slave_config(काष्ठा aपंचांगel_spi *as,
				काष्ठा dma_slave_config *slave_config,
				u8 bits_per_word)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(as->pdev);
	पूर्णांक err = 0;

	अगर (bits_per_word > 8) अणु
		slave_config->dst_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
		slave_config->src_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
	पूर्ण अन्यथा अणु
		slave_config->dst_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
		slave_config->src_addr_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
	पूर्ण

	slave_config->dst_addr = (dma_addr_t)as->phybase + SPI_TDR;
	slave_config->src_addr = (dma_addr_t)as->phybase + SPI_RDR;
	slave_config->src_maxburst = 1;
	slave_config->dst_maxburst = 1;
	slave_config->device_fc = false;

	/*
	 * This driver uses fixed peripheral select mode (PS bit set to '0' in
	 * the Mode Register).
	 * So according to the datasheet, when FIFOs are available (and
	 * enabled), the Transmit FIFO operates in Multiple Data Mode.
	 * In this mode, up to 2 data, not 4, can be written पूर्णांकo the Transmit
	 * Data Register in a single access.
	 * However, the first data has to be written पूर्णांकo the lowest 16 bits and
	 * the second data पूर्णांकo the highest 16 bits of the Transmit
	 * Data Register. For 8bit data (the most frequent हाल), it would
	 * require to rework tx_buf so each data would actualy fit 16 bits.
	 * So we'd rather ग_लिखो only one data at the समय. Hence the transmit
	 * path works the same whether FIFOs are available (and enabled) or not.
	 */
	slave_config->direction = DMA_MEM_TO_DEV;
	अगर (dmaengine_slave_config(master->dma_tx, slave_config)) अणु
		dev_err(&as->pdev->dev,
			"failed to configure tx dma channel\n");
		err = -EINVAL;
	पूर्ण

	/*
	 * This driver configures the spi controller क्रम master mode (MSTR bit
	 * set to '1' in the Mode Register).
	 * So according to the datasheet, when FIFOs are available (and
	 * enabled), the Receive FIFO operates in Single Data Mode.
	 * So the receive path works the same whether FIFOs are available (and
	 * enabled) or not.
	 */
	slave_config->direction = DMA_DEV_TO_MEM;
	अगर (dmaengine_slave_config(master->dma_rx, slave_config)) अणु
		dev_err(&as->pdev->dev,
			"failed to configure rx dma channel\n");
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक aपंचांगel_spi_configure_dma(काष्ठा spi_master *master,
				   काष्ठा aपंचांगel_spi *as)
अणु
	काष्ठा dma_slave_config	slave_config;
	काष्ठा device *dev = &as->pdev->dev;
	पूर्णांक err;

	master->dma_tx = dma_request_chan(dev, "tx");
	अगर (IS_ERR(master->dma_tx)) अणु
		err = PTR_ERR(master->dma_tx);
		dev_dbg(dev, "No TX DMA channel, DMA is disabled\n");
		जाओ error_clear;
	पूर्ण

	master->dma_rx = dma_request_chan(dev, "rx");
	अगर (IS_ERR(master->dma_rx)) अणु
		err = PTR_ERR(master->dma_rx);
		/*
		 * No reason to check EPROBE_DEFER here since we have alपढ़ोy
		 * requested tx channel.
		 */
		dev_dbg(dev, "No RX DMA channel, DMA is disabled\n");
		जाओ error;
	पूर्ण

	err = aपंचांगel_spi_dma_slave_config(as, &slave_config, 8);
	अगर (err)
		जाओ error;

	dev_info(&as->pdev->dev,
			"Using %s (tx) and %s (rx) for DMA transfers\n",
			dma_chan_name(master->dma_tx),
			dma_chan_name(master->dma_rx));

	वापस 0;
error:
	अगर (!IS_ERR(master->dma_rx))
		dma_release_channel(master->dma_rx);
	अगर (!IS_ERR(master->dma_tx))
		dma_release_channel(master->dma_tx);
error_clear:
	master->dma_tx = master->dma_rx = शून्य;
	वापस err;
पूर्ण

अटल व्योम aपंचांगel_spi_stop_dma(काष्ठा spi_master *master)
अणु
	अगर (master->dma_rx)
		dmaengine_terminate_all(master->dma_rx);
	अगर (master->dma_tx)
		dmaengine_terminate_all(master->dma_tx);
पूर्ण

अटल व्योम aपंचांगel_spi_release_dma(काष्ठा spi_master *master)
अणु
	अगर (master->dma_rx) अणु
		dma_release_channel(master->dma_rx);
		master->dma_rx = शून्य;
	पूर्ण
	अगर (master->dma_tx) अणु
		dma_release_channel(master->dma_tx);
		master->dma_tx = शून्य;
	पूर्ण
पूर्ण

/* This function is called by the DMA driver from tasklet context */
अटल व्योम dma_callback(व्योम *data)
अणु
	काष्ठा spi_master	*master = data;
	काष्ठा aपंचांगel_spi	*as = spi_master_get_devdata(master);

	अगर (is_vदो_स्मृति_addr(as->current_transfer->rx_buf) &&
	    IS_ENABLED(CONFIG_SOC_SAM_V4_V5)) अणु
		स_नकल(as->current_transfer->rx_buf, as->addr_rx_bbuf,
		       as->current_transfer->len);
	पूर्ण
	complete(&as->xfer_completion);
पूर्ण

/*
 * Next transfer using PIO without FIFO.
 */
अटल व्योम aपंचांगel_spi_next_xfer_single(काष्ठा spi_master *master,
				       काष्ठा spi_transfer *xfer)
अणु
	काष्ठा aपंचांगel_spi	*as = spi_master_get_devdata(master);
	अचिन्हित दीर्घ xfer_pos = xfer->len - as->current_reमुख्यing_bytes;

	dev_vdbg(master->dev.parent, "atmel_spi_next_xfer_pio\n");

	/* Make sure data is not reमुख्यing in RDR */
	spi_पढ़ोl(as, RDR);
	जबतक (spi_पढ़ोl(as, SR) & SPI_BIT(RDRF)) अणु
		spi_पढ़ोl(as, RDR);
		cpu_relax();
	पूर्ण

	अगर (xfer->bits_per_word > 8)
		spi_ग_लिखोl(as, TDR, *(u16 *)(xfer->tx_buf + xfer_pos));
	अन्यथा
		spi_ग_लिखोl(as, TDR, *(u8 *)(xfer->tx_buf + xfer_pos));

	dev_dbg(master->dev.parent,
		"  start pio xfer %p: len %u tx %p rx %p bitpw %d\n",
		xfer, xfer->len, xfer->tx_buf, xfer->rx_buf,
		xfer->bits_per_word);

	/* Enable relevant पूर्णांकerrupts */
	spi_ग_लिखोl(as, IER, SPI_BIT(RDRF) | SPI_BIT(OVRES));
पूर्ण

/*
 * Next transfer using PIO with FIFO.
 */
अटल व्योम aपंचांगel_spi_next_xfer_fअगरo(काष्ठा spi_master *master,
				     काष्ठा spi_transfer *xfer)
अणु
	काष्ठा aपंचांगel_spi *as = spi_master_get_devdata(master);
	u32 current_reमुख्यing_data, num_data;
	u32 offset = xfer->len - as->current_reमुख्यing_bytes;
	स्थिर u16 *words = (स्थिर u16 *)((u8 *)xfer->tx_buf + offset);
	स्थिर u8  *bytes = (स्थिर u8  *)((u8 *)xfer->tx_buf + offset);
	u16 td0, td1;
	u32 fअगरomr;

	dev_vdbg(master->dev.parent, "atmel_spi_next_xfer_fifo\n");

	/* Compute the number of data to transfer in the current iteration */
	current_reमुख्यing_data = ((xfer->bits_per_word > 8) ?
				  ((u32)as->current_reमुख्यing_bytes >> 1) :
				  (u32)as->current_reमुख्यing_bytes);
	num_data = min(current_reमुख्यing_data, as->fअगरo_size);

	/* Flush RX and TX FIFOs */
	spi_ग_लिखोl(as, CR, SPI_BIT(RXFCLR) | SPI_BIT(TXFCLR));
	जबतक (spi_पढ़ोl(as, FLR))
		cpu_relax();

	/* Set RX FIFO Threshold to the number of data to transfer */
	fअगरomr = spi_पढ़ोl(as, FMR);
	spi_ग_लिखोl(as, FMR, SPI_BFINS(RXFTHRES, num_data, fअगरomr));

	/* Clear FIFO flags in the Status Register, especially RXFTHF */
	(व्योम)spi_पढ़ोl(as, SR);

	/* Fill TX FIFO */
	जबतक (num_data >= 2) अणु
		अगर (xfer->bits_per_word > 8) अणु
			td0 = *words++;
			td1 = *words++;
		पूर्ण अन्यथा अणु
			td0 = *bytes++;
			td1 = *bytes++;
		पूर्ण

		spi_ग_लिखोl(as, TDR, (td1 << 16) | td0);
		num_data -= 2;
	पूर्ण

	अगर (num_data) अणु
		अगर (xfer->bits_per_word > 8)
			td0 = *words++;
		अन्यथा
			td0 = *bytes++;

		spi_ग_लिखोw(as, TDR, td0);
		num_data--;
	पूर्ण

	dev_dbg(master->dev.parent,
		"  start fifo xfer %p: len %u tx %p rx %p bitpw %d\n",
		xfer, xfer->len, xfer->tx_buf, xfer->rx_buf,
		xfer->bits_per_word);

	/*
	 * Enable RX FIFO Threshold Flag पूर्णांकerrupt to be notअगरied about
	 * transfer completion.
	 */
	spi_ग_लिखोl(as, IER, SPI_BIT(RXFTHF) | SPI_BIT(OVRES));
पूर्ण

/*
 * Next transfer using PIO.
 */
अटल व्योम aपंचांगel_spi_next_xfer_pio(काष्ठा spi_master *master,
				    काष्ठा spi_transfer *xfer)
अणु
	काष्ठा aपंचांगel_spi *as = spi_master_get_devdata(master);

	अगर (as->fअगरo_size)
		aपंचांगel_spi_next_xfer_fअगरo(master, xfer);
	अन्यथा
		aपंचांगel_spi_next_xfer_single(master, xfer);
पूर्ण

/*
 * Submit next transfer क्रम DMA.
 */
अटल पूर्णांक aपंचांगel_spi_next_xfer_dma_submit(काष्ठा spi_master *master,
				काष्ठा spi_transfer *xfer,
				u32 *plen)
	__must_hold(&as->lock)
अणु
	काष्ठा aपंचांगel_spi	*as = spi_master_get_devdata(master);
	काष्ठा dma_chan		*rxchan = master->dma_rx;
	काष्ठा dma_chan		*txchan = master->dma_tx;
	काष्ठा dma_async_tx_descriptor *rxdesc;
	काष्ठा dma_async_tx_descriptor *txdesc;
	काष्ठा dma_slave_config	slave_config;
	dma_cookie_t		cookie;

	dev_vdbg(master->dev.parent, "atmel_spi_next_xfer_dma_submit\n");

	/* Check that the channels are available */
	अगर (!rxchan || !txchan)
		वापस -ENODEV;

	/* release lock क्रम DMA operations */
	aपंचांगel_spi_unlock(as);

	*plen = xfer->len;

	अगर (aपंचांगel_spi_dma_slave_config(as, &slave_config,
				       xfer->bits_per_word))
		जाओ err_निकास;

	/* Send both scatterlists */
	अगर (aपंचांगel_spi_is_vदो_स्मृति_xfer(xfer) &&
	    IS_ENABLED(CONFIG_SOC_SAM_V4_V5)) अणु
		rxdesc = dmaengine_prep_slave_single(rxchan,
						     as->dma_addr_rx_bbuf,
						     xfer->len,
						     DMA_DEV_TO_MEM,
						     DMA_PREP_INTERRUPT |
						     DMA_CTRL_ACK);
	पूर्ण अन्यथा अणु
		rxdesc = dmaengine_prep_slave_sg(rxchan,
						 xfer->rx_sg.sgl,
						 xfer->rx_sg.nents,
						 DMA_DEV_TO_MEM,
						 DMA_PREP_INTERRUPT |
						 DMA_CTRL_ACK);
	पूर्ण
	अगर (!rxdesc)
		जाओ err_dma;

	अगर (aपंचांगel_spi_is_vदो_स्मृति_xfer(xfer) &&
	    IS_ENABLED(CONFIG_SOC_SAM_V4_V5)) अणु
		स_नकल(as->addr_tx_bbuf, xfer->tx_buf, xfer->len);
		txdesc = dmaengine_prep_slave_single(txchan,
						     as->dma_addr_tx_bbuf,
						     xfer->len, DMA_MEM_TO_DEV,
						     DMA_PREP_INTERRUPT |
						     DMA_CTRL_ACK);
	पूर्ण अन्यथा अणु
		txdesc = dmaengine_prep_slave_sg(txchan,
						 xfer->tx_sg.sgl,
						 xfer->tx_sg.nents,
						 DMA_MEM_TO_DEV,
						 DMA_PREP_INTERRUPT |
						 DMA_CTRL_ACK);
	पूर्ण
	अगर (!txdesc)
		जाओ err_dma;

	dev_dbg(master->dev.parent,
		"  start dma xfer %p: len %u tx %p/%08llx rx %p/%08llx\n",
		xfer, xfer->len, xfer->tx_buf, (अचिन्हित दीर्घ दीर्घ)xfer->tx_dma,
		xfer->rx_buf, (अचिन्हित दीर्घ दीर्घ)xfer->rx_dma);

	/* Enable relevant पूर्णांकerrupts */
	spi_ग_लिखोl(as, IER, SPI_BIT(OVRES));

	/* Put the callback on the RX transfer only, that should finish last */
	rxdesc->callback = dma_callback;
	rxdesc->callback_param = master;

	/* Submit and fire RX and TX with TX last so we're पढ़ोy to पढ़ो! */
	cookie = rxdesc->tx_submit(rxdesc);
	अगर (dma_submit_error(cookie))
		जाओ err_dma;
	cookie = txdesc->tx_submit(txdesc);
	अगर (dma_submit_error(cookie))
		जाओ err_dma;
	rxchan->device->device_issue_pending(rxchan);
	txchan->device->device_issue_pending(txchan);

	/* take back lock */
	aपंचांगel_spi_lock(as);
	वापस 0;

err_dma:
	spi_ग_लिखोl(as, IDR, SPI_BIT(OVRES));
	aपंचांगel_spi_stop_dma(master);
err_निकास:
	aपंचांगel_spi_lock(as);
	वापस -ENOMEM;
पूर्ण

अटल व्योम aपंचांगel_spi_next_xfer_data(काष्ठा spi_master *master,
				काष्ठा spi_transfer *xfer,
				dma_addr_t *tx_dma,
				dma_addr_t *rx_dma,
				u32 *plen)
अणु
	*rx_dma = xfer->rx_dma + xfer->len - *plen;
	*tx_dma = xfer->tx_dma + xfer->len - *plen;
	अगर (*plen > master->max_dma_len)
		*plen = master->max_dma_len;
पूर्ण

अटल पूर्णांक aपंचांगel_spi_set_xfer_speed(काष्ठा aपंचांगel_spi *as,
				    काष्ठा spi_device *spi,
				    काष्ठा spi_transfer *xfer)
अणु
	u32			scbr, csr;
	अचिन्हित दीर्घ		bus_hz;
	पूर्णांक chip_select;

	अगर (spi->cs_gpiod)
		chip_select = as->native_cs_क्रम_gpio;
	अन्यथा
		chip_select = spi->chip_select;

	/* v1 chips start out at half the peripheral bus speed. */
	bus_hz = as->spi_clk;
	अगर (!aपंचांगel_spi_is_v2(as))
		bus_hz /= 2;

	/*
	 * Calculate the lowest भागider that satisfies the
	 * स्थिरraपूर्णांक, assuming भाग32/fभाग/mbz == 0.
	 */
	scbr = DIV_ROUND_UP(bus_hz, xfer->speed_hz);

	/*
	 * If the resulting भागider करोesn't fit पूर्णांकo the
	 * रेजिस्टर bitfield, we can't satisfy the स्थिरraपूर्णांक.
	 */
	अगर (scbr >= (1 << SPI_SCBR_SIZE)) अणु
		dev_err(&spi->dev,
			"setup: %d Hz too slow, scbr %u; min %ld Hz\n",
			xfer->speed_hz, scbr, bus_hz/255);
		वापस -EINVAL;
	पूर्ण
	अगर (scbr == 0) अणु
		dev_err(&spi->dev,
			"setup: %d Hz too high, scbr %u; max %ld Hz\n",
			xfer->speed_hz, scbr, bus_hz);
		वापस -EINVAL;
	पूर्ण
	csr = spi_पढ़ोl(as, CSR0 + 4 * chip_select);
	csr = SPI_BFINS(SCBR, scbr, csr);
	spi_ग_लिखोl(as, CSR0 + 4 * chip_select, csr);
	xfer->effective_speed_hz = bus_hz / scbr;

	वापस 0;
पूर्ण

/*
 * Submit next transfer क्रम PDC.
 * lock is held, spi irq is blocked
 */
अटल व्योम aपंचांगel_spi_pdc_next_xfer(काष्ठा spi_master *master,
					काष्ठा spi_message *msg,
					काष्ठा spi_transfer *xfer)
अणु
	काष्ठा aपंचांगel_spi	*as = spi_master_get_devdata(master);
	u32			len;
	dma_addr_t		tx_dma, rx_dma;

	spi_ग_लिखोl(as, PTCR, SPI_BIT(RXTDIS) | SPI_BIT(TXTDIS));

	len = as->current_reमुख्यing_bytes;
	aपंचांगel_spi_next_xfer_data(master, xfer, &tx_dma, &rx_dma, &len);
	as->current_reमुख्यing_bytes -= len;

	spi_ग_लिखोl(as, RPR, rx_dma);
	spi_ग_लिखोl(as, TPR, tx_dma);

	अगर (msg->spi->bits_per_word > 8)
		len >>= 1;
	spi_ग_लिखोl(as, RCR, len);
	spi_ग_लिखोl(as, TCR, len);

	dev_dbg(&msg->spi->dev,
		"  start xfer %p: len %u tx %p/%08llx rx %p/%08llx\n",
		xfer, xfer->len, xfer->tx_buf,
		(अचिन्हित दीर्घ दीर्घ)xfer->tx_dma, xfer->rx_buf,
		(अचिन्हित दीर्घ दीर्घ)xfer->rx_dma);

	अगर (as->current_reमुख्यing_bytes) अणु
		len = as->current_reमुख्यing_bytes;
		aपंचांगel_spi_next_xfer_data(master, xfer, &tx_dma, &rx_dma, &len);
		as->current_reमुख्यing_bytes -= len;

		spi_ग_लिखोl(as, RNPR, rx_dma);
		spi_ग_लिखोl(as, TNPR, tx_dma);

		अगर (msg->spi->bits_per_word > 8)
			len >>= 1;
		spi_ग_लिखोl(as, RNCR, len);
		spi_ग_लिखोl(as, TNCR, len);

		dev_dbg(&msg->spi->dev,
			"  next xfer %p: len %u tx %p/%08llx rx %p/%08llx\n",
			xfer, xfer->len, xfer->tx_buf,
			(अचिन्हित दीर्घ दीर्घ)xfer->tx_dma, xfer->rx_buf,
			(अचिन्हित दीर्घ दीर्घ)xfer->rx_dma);
	पूर्ण

	/* REVISIT: We're रुकोing क्रम RXBUFF beक्रमe we start the next
	 * transfer because we need to handle some dअगरficult timing
	 * issues otherwise. If we रुको क्रम TXBUFE in one transfer and
	 * then starts रुकोing क्रम RXBUFF in the next, it's dअगरficult
	 * to tell the dअगरference between the RXBUFF पूर्णांकerrupt we're
	 * actually रुकोing क्रम and the RXBUFF पूर्णांकerrupt of the
	 * previous transfer.
	 *
	 * It should be करोable, though. Just not now...
	 */
	spi_ग_लिखोl(as, IER, SPI_BIT(RXBUFF) | SPI_BIT(OVRES));
	spi_ग_लिखोl(as, PTCR, SPI_BIT(TXTEN) | SPI_BIT(RXTEN));
पूर्ण

/*
 * For DMA, tx_buf/tx_dma have the same relationship as rx_buf/rx_dma:
 *  - The buffer is either valid क्रम CPU access, अन्यथा शून्य
 *  - If the buffer is valid, so is its DMA address
 *
 * This driver manages the dma address unless message->is_dma_mapped.
 */
अटल पूर्णांक
aपंचांगel_spi_dma_map_xfer(काष्ठा aपंचांगel_spi *as, काष्ठा spi_transfer *xfer)
अणु
	काष्ठा device	*dev = &as->pdev->dev;

	xfer->tx_dma = xfer->rx_dma = INVALID_DMA_ADDRESS;
	अगर (xfer->tx_buf) अणु
		/* tx_buf is a स्थिर व्योम* where we need a व्योम * क्रम the dma
		 * mapping */
		व्योम *nonस्थिर_tx = (व्योम *)xfer->tx_buf;

		xfer->tx_dma = dma_map_single(dev,
				nonस्थिर_tx, xfer->len,
				DMA_TO_DEVICE);
		अगर (dma_mapping_error(dev, xfer->tx_dma))
			वापस -ENOMEM;
	पूर्ण
	अगर (xfer->rx_buf) अणु
		xfer->rx_dma = dma_map_single(dev,
				xfer->rx_buf, xfer->len,
				DMA_FROM_DEVICE);
		अगर (dma_mapping_error(dev, xfer->rx_dma)) अणु
			अगर (xfer->tx_buf)
				dma_unmap_single(dev,
						xfer->tx_dma, xfer->len,
						DMA_TO_DEVICE);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_spi_dma_unmap_xfer(काष्ठा spi_master *master,
				     काष्ठा spi_transfer *xfer)
अणु
	अगर (xfer->tx_dma != INVALID_DMA_ADDRESS)
		dma_unmap_single(master->dev.parent, xfer->tx_dma,
				 xfer->len, DMA_TO_DEVICE);
	अगर (xfer->rx_dma != INVALID_DMA_ADDRESS)
		dma_unmap_single(master->dev.parent, xfer->rx_dma,
				 xfer->len, DMA_FROM_DEVICE);
पूर्ण

अटल व्योम aपंचांगel_spi_disable_pdc_transfer(काष्ठा aपंचांगel_spi *as)
अणु
	spi_ग_लिखोl(as, PTCR, SPI_BIT(RXTDIS) | SPI_BIT(TXTDIS));
पूर्ण

अटल व्योम
aपंचांगel_spi_pump_single_data(काष्ठा aपंचांगel_spi *as, काष्ठा spi_transfer *xfer)
अणु
	u8		*rxp;
	u16		*rxp16;
	अचिन्हित दीर्घ	xfer_pos = xfer->len - as->current_reमुख्यing_bytes;

	अगर (xfer->bits_per_word > 8) अणु
		rxp16 = (u16 *)(((u8 *)xfer->rx_buf) + xfer_pos);
		*rxp16 = spi_पढ़ोl(as, RDR);
	पूर्ण अन्यथा अणु
		rxp = ((u8 *)xfer->rx_buf) + xfer_pos;
		*rxp = spi_पढ़ोl(as, RDR);
	पूर्ण
	अगर (xfer->bits_per_word > 8) अणु
		अगर (as->current_reमुख्यing_bytes > 2)
			as->current_reमुख्यing_bytes -= 2;
		अन्यथा
			as->current_reमुख्यing_bytes = 0;
	पूर्ण अन्यथा अणु
		as->current_reमुख्यing_bytes--;
	पूर्ण
पूर्ण

अटल व्योम
aपंचांगel_spi_pump_fअगरo_data(काष्ठा aपंचांगel_spi *as, काष्ठा spi_transfer *xfer)
अणु
	u32 fअगरolr = spi_पढ़ोl(as, FLR);
	u32 num_bytes, num_data = SPI_BFEXT(RXFL, fअगरolr);
	u32 offset = xfer->len - as->current_reमुख्यing_bytes;
	u16 *words = (u16 *)((u8 *)xfer->rx_buf + offset);
	u8  *bytes = (u8  *)((u8 *)xfer->rx_buf + offset);
	u16 rd; /* RD field is the lowest 16 bits of RDR */

	/* Update the number of reमुख्यing bytes to transfer */
	num_bytes = ((xfer->bits_per_word > 8) ?
		     (num_data << 1) :
		     num_data);

	अगर (as->current_reमुख्यing_bytes > num_bytes)
		as->current_reमुख्यing_bytes -= num_bytes;
	अन्यथा
		as->current_reमुख्यing_bytes = 0;

	/* Handle odd number of bytes when data are more than 8bit width */
	अगर (xfer->bits_per_word > 8)
		as->current_reमुख्यing_bytes &= ~0x1;

	/* Read data */
	जबतक (num_data) अणु
		rd = spi_पढ़ोl(as, RDR);
		अगर (xfer->bits_per_word > 8)
			*words++ = rd;
		अन्यथा
			*bytes++ = rd;
		num_data--;
	पूर्ण
पूर्ण

/* Called from IRQ
 *
 * Must update "current_remaining_bytes" to keep track of data
 * to transfer.
 */
अटल व्योम
aपंचांगel_spi_pump_pio_data(काष्ठा aपंचांगel_spi *as, काष्ठा spi_transfer *xfer)
अणु
	अगर (as->fअगरo_size)
		aपंचांगel_spi_pump_fअगरo_data(as, xfer);
	अन्यथा
		aपंचांगel_spi_pump_single_data(as, xfer);
पूर्ण

/* Interrupt
 *
 * No need क्रम locking in this Interrupt handler: करोne_status is the
 * only inक्रमmation modअगरied.
 */
अटल irqवापस_t
aपंचांगel_spi_pio_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा spi_master	*master = dev_id;
	काष्ठा aपंचांगel_spi	*as = spi_master_get_devdata(master);
	u32			status, pending, imr;
	काष्ठा spi_transfer	*xfer;
	पूर्णांक			ret = IRQ_NONE;

	imr = spi_पढ़ोl(as, IMR);
	status = spi_पढ़ोl(as, SR);
	pending = status & imr;

	अगर (pending & SPI_BIT(OVRES)) अणु
		ret = IRQ_HANDLED;
		spi_ग_लिखोl(as, IDR, SPI_BIT(OVRES));
		dev_warn(master->dev.parent, "overrun\n");

		/*
		 * When we get an overrun, we disregard the current
		 * transfer. Data will not be copied back from any
		 * bounce buffer and msg->actual_len will not be
		 * updated with the last xfer.
		 *
		 * We will also not process any remaning transfers in
		 * the message.
		 */
		as->करोne_status = -EIO;
		smp_wmb();

		/* Clear any overrun happening जबतक cleaning up */
		spi_पढ़ोl(as, SR);

		complete(&as->xfer_completion);

	पूर्ण अन्यथा अगर (pending & (SPI_BIT(RDRF) | SPI_BIT(RXFTHF))) अणु
		aपंचांगel_spi_lock(as);

		अगर (as->current_reमुख्यing_bytes) अणु
			ret = IRQ_HANDLED;
			xfer = as->current_transfer;
			aपंचांगel_spi_pump_pio_data(as, xfer);
			अगर (!as->current_reमुख्यing_bytes)
				spi_ग_लिखोl(as, IDR, pending);

			complete(&as->xfer_completion);
		पूर्ण

		aपंचांगel_spi_unlock(as);
	पूर्ण अन्यथा अणु
		WARN_ONCE(pending, "IRQ not handled, pending = %x\n", pending);
		ret = IRQ_HANDLED;
		spi_ग_लिखोl(as, IDR, pending);
	पूर्ण

	वापस ret;
पूर्ण

अटल irqवापस_t
aपंचांगel_spi_pdc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा spi_master	*master = dev_id;
	काष्ठा aपंचांगel_spi	*as = spi_master_get_devdata(master);
	u32			status, pending, imr;
	पूर्णांक			ret = IRQ_NONE;

	imr = spi_पढ़ोl(as, IMR);
	status = spi_पढ़ोl(as, SR);
	pending = status & imr;

	अगर (pending & SPI_BIT(OVRES)) अणु

		ret = IRQ_HANDLED;

		spi_ग_लिखोl(as, IDR, (SPI_BIT(RXBUFF) | SPI_BIT(ENDRX)
				     | SPI_BIT(OVRES)));

		/* Clear any overrun happening जबतक cleaning up */
		spi_पढ़ोl(as, SR);

		as->करोne_status = -EIO;

		complete(&as->xfer_completion);

	पूर्ण अन्यथा अगर (pending & (SPI_BIT(RXBUFF) | SPI_BIT(ENDRX))) अणु
		ret = IRQ_HANDLED;

		spi_ग_लिखोl(as, IDR, pending);

		complete(&as->xfer_completion);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_word_delay_csr(काष्ठा spi_device *spi, काष्ठा aपंचांगel_spi *as)
अणु
	काष्ठा spi_delay *delay = &spi->word_delay;
	u32 value = delay->value;

	चयन (delay->unit) अणु
	हाल SPI_DELAY_UNIT_NSECS:
		value /= 1000;
		अवरोध;
	हाल SPI_DELAY_UNIT_USECS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस (as->spi_clk / 1000000 * value) >> 5;
पूर्ण

अटल व्योम initialize_native_cs_क्रम_gpio(काष्ठा aपंचांगel_spi *as)
अणु
	पूर्णांक i;
	काष्ठा spi_master *master = platक्रमm_get_drvdata(as->pdev);

	अगर (!as->native_cs_मुक्त)
		वापस; /* alपढ़ोy initialized */

	अगर (!master->cs_gpiods)
		वापस; /* No CS GPIO */

	/*
	 * On the first version of the controller (AT91RM9200), CS0
	 * can't be used associated with GPIO
	 */
	अगर (aपंचांगel_spi_is_v2(as))
		i = 0;
	अन्यथा
		i = 1;

	क्रम (; i < 4; i++)
		अगर (master->cs_gpiods[i])
			as->native_cs_मुक्त |= BIT(i);

	अगर (as->native_cs_मुक्त)
		as->native_cs_क्रम_gpio = ffs(as->native_cs_मुक्त);
पूर्ण

अटल पूर्णांक aपंचांगel_spi_setup(काष्ठा spi_device *spi)
अणु
	काष्ठा aपंचांगel_spi	*as;
	काष्ठा aपंचांगel_spi_device	*asd;
	u32			csr;
	अचिन्हित पूर्णांक		bits = spi->bits_per_word;
	पूर्णांक chip_select;
	पूर्णांक			word_delay_csr;

	as = spi_master_get_devdata(spi->master);

	/* see notes above re chipselect */
	अगर (!spi->cs_gpiod && (spi->mode & SPI_CS_HIGH)) अणु
		dev_warn(&spi->dev, "setup: non GPIO CS can't be active-high\n");
		वापस -EINVAL;
	पूर्ण

	/* Setup() is called during spi_रेजिस्टर_controller(aka
	 * spi_रेजिस्टर_master) but after all membmers of the cs_gpiod
	 * array have been filled, so we can looked क्रम which native
	 * CS will be मुक्त क्रम using with GPIO
	 */
	initialize_native_cs_क्रम_gpio(as);

	अगर (spi->cs_gpiod && as->native_cs_मुक्त) अणु
		dev_err(&spi->dev,
			"No native CS available to support this GPIO CS\n");
		वापस -EBUSY;
	पूर्ण

	अगर (spi->cs_gpiod)
		chip_select = as->native_cs_क्रम_gpio;
	अन्यथा
		chip_select = spi->chip_select;

	csr = SPI_BF(BITS, bits - 8);
	अगर (spi->mode & SPI_CPOL)
		csr |= SPI_BIT(CPOL);
	अगर (!(spi->mode & SPI_CPHA))
		csr |= SPI_BIT(NCPHA);

	अगर (!spi->cs_gpiod)
		csr |= SPI_BIT(CSAAT);
	csr |= SPI_BF(DLYBS, 0);

	word_delay_csr = aपंचांगel_word_delay_csr(spi, as);
	अगर (word_delay_csr < 0)
		वापस word_delay_csr;

	/* DLYBCT adds delays between words.  This is useful क्रम slow devices
	 * that need a bit of समय to setup the next transfer.
	 */
	csr |= SPI_BF(DLYBCT, word_delay_csr);

	asd = spi->controller_state;
	अगर (!asd) अणु
		asd = kzalloc(माप(काष्ठा aपंचांगel_spi_device), GFP_KERNEL);
		अगर (!asd)
			वापस -ENOMEM;

		spi->controller_state = asd;
	पूर्ण

	asd->csr = csr;

	dev_dbg(&spi->dev,
		"setup: bpw %u mode 0x%x -> csr%d %08x\n",
		bits, spi->mode, spi->chip_select, csr);

	अगर (!aपंचांगel_spi_is_v2(as))
		spi_ग_लिखोl(as, CSR0 + 4 * chip_select, csr);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_spi_one_transfer(काष्ठा spi_master *master,
					काष्ठा spi_message *msg,
					काष्ठा spi_transfer *xfer)
अणु
	काष्ठा aपंचांगel_spi	*as;
	काष्ठा spi_device	*spi = msg->spi;
	u8			bits;
	u32			len;
	काष्ठा aपंचांगel_spi_device	*asd;
	पूर्णांक			समयout;
	पूर्णांक			ret;
	अचिन्हित दीर्घ		dma_समयout;

	as = spi_master_get_devdata(master);

	अगर (!(xfer->tx_buf || xfer->rx_buf) && xfer->len) अणु
		dev_dbg(&spi->dev, "missing rx or tx buf\n");
		वापस -EINVAL;
	पूर्ण

	asd = spi->controller_state;
	bits = (asd->csr >> 4) & 0xf;
	अगर (bits != xfer->bits_per_word - 8) अणु
		dev_dbg(&spi->dev,
			"you can't yet change bits_per_word in transfers\n");
		वापस -ENOPROTOOPT;
	पूर्ण

	/*
	 * DMA map early, क्रम perक्रमmance (empties dcache ASAP) and
	 * better fault reporting.
	 */
	अगर ((!msg->is_dma_mapped)
		&& as->use_pdc) अणु
		अगर (aपंचांगel_spi_dma_map_xfer(as, xfer) < 0)
			वापस -ENOMEM;
	पूर्ण

	aपंचांगel_spi_set_xfer_speed(as, msg->spi, xfer);

	as->करोne_status = 0;
	as->current_transfer = xfer;
	as->current_reमुख्यing_bytes = xfer->len;
	जबतक (as->current_reमुख्यing_bytes) अणु
		reinit_completion(&as->xfer_completion);

		अगर (as->use_pdc) अणु
			aपंचांगel_spi_pdc_next_xfer(master, msg, xfer);
		पूर्ण अन्यथा अगर (aपंचांगel_spi_use_dma(as, xfer)) अणु
			len = as->current_reमुख्यing_bytes;
			ret = aपंचांगel_spi_next_xfer_dma_submit(master,
								xfer, &len);
			अगर (ret) अणु
				dev_err(&spi->dev,
					"unable to use DMA, fallback to PIO\n");
				aपंचांगel_spi_next_xfer_pio(master, xfer);
			पूर्ण अन्यथा अणु
				as->current_reमुख्यing_bytes -= len;
				अगर (as->current_reमुख्यing_bytes < 0)
					as->current_reमुख्यing_bytes = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			aपंचांगel_spi_next_xfer_pio(master, xfer);
		पूर्ण

		/* पूर्णांकerrupts are disabled, so मुक्त the lock क्रम schedule */
		aपंचांगel_spi_unlock(as);
		dma_समयout = रुको_क्रम_completion_समयout(&as->xfer_completion,
							  SPI_DMA_TIMEOUT);
		aपंचांगel_spi_lock(as);
		अगर (WARN_ON(dma_समयout == 0)) अणु
			dev_err(&spi->dev, "spi transfer timeout\n");
			as->करोne_status = -EIO;
		पूर्ण

		अगर (as->करोne_status)
			अवरोध;
	पूर्ण

	अगर (as->करोne_status) अणु
		अगर (as->use_pdc) अणु
			dev_warn(master->dev.parent,
				"overrun (%u/%u remaining)\n",
				spi_पढ़ोl(as, TCR), spi_पढ़ोl(as, RCR));

			/*
			 * Clean up DMA रेजिस्टरs and make sure the data
			 * रेजिस्टरs are empty.
			 */
			spi_ग_लिखोl(as, RNCR, 0);
			spi_ग_लिखोl(as, TNCR, 0);
			spi_ग_लिखोl(as, RCR, 0);
			spi_ग_लिखोl(as, TCR, 0);
			क्रम (समयout = 1000; समयout; समयout--)
				अगर (spi_पढ़ोl(as, SR) & SPI_BIT(TXEMPTY))
					अवरोध;
			अगर (!समयout)
				dev_warn(master->dev.parent,
					 "timeout waiting for TXEMPTY");
			जबतक (spi_पढ़ोl(as, SR) & SPI_BIT(RDRF))
				spi_पढ़ोl(as, RDR);

			/* Clear any overrun happening जबतक cleaning up */
			spi_पढ़ोl(as, SR);

		पूर्ण अन्यथा अगर (aपंचांगel_spi_use_dma(as, xfer)) अणु
			aपंचांगel_spi_stop_dma(master);
		पूर्ण

		अगर (!msg->is_dma_mapped
			&& as->use_pdc)
			aपंचांगel_spi_dma_unmap_xfer(master, xfer);

		वापस 0;

	पूर्ण अन्यथा अणु
		/* only update length अगर no error */
		msg->actual_length += xfer->len;
	पूर्ण

	अगर (!msg->is_dma_mapped
		&& as->use_pdc)
		aपंचांगel_spi_dma_unmap_xfer(master, xfer);

	spi_transfer_delay_exec(xfer);

	अगर (xfer->cs_change) अणु
		अगर (list_is_last(&xfer->transfer_list,
				 &msg->transfers)) अणु
			as->keep_cs = true;
		पूर्ण अन्यथा अणु
			cs_deactivate(as, msg->spi);
			udelay(10);
			cs_activate(as, msg->spi);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_spi_transfer_one_message(काष्ठा spi_master *master,
						काष्ठा spi_message *msg)
अणु
	काष्ठा aपंचांगel_spi *as;
	काष्ठा spi_transfer *xfer;
	काष्ठा spi_device *spi = msg->spi;
	पूर्णांक ret = 0;

	as = spi_master_get_devdata(master);

	dev_dbg(&spi->dev, "new message %p submitted for %s\n",
					msg, dev_name(&spi->dev));

	aपंचांगel_spi_lock(as);
	cs_activate(as, spi);

	as->keep_cs = false;

	msg->status = 0;
	msg->actual_length = 0;

	list_क्रम_each_entry(xfer, &msg->transfers, transfer_list) अणु
		trace_spi_transfer_start(msg, xfer);

		ret = aपंचांगel_spi_one_transfer(master, msg, xfer);
		अगर (ret)
			जाओ msg_करोne;

		trace_spi_transfer_stop(msg, xfer);
	पूर्ण

	अगर (as->use_pdc)
		aपंचांगel_spi_disable_pdc_transfer(as);

	list_क्रम_each_entry(xfer, &msg->transfers, transfer_list) अणु
		dev_dbg(&spi->dev,
			"  xfer %p: len %u tx %p/%pad rx %p/%pad\n",
			xfer, xfer->len,
			xfer->tx_buf, &xfer->tx_dma,
			xfer->rx_buf, &xfer->rx_dma);
	पूर्ण

msg_करोne:
	अगर (!as->keep_cs)
		cs_deactivate(as, msg->spi);

	aपंचांगel_spi_unlock(as);

	msg->status = as->करोne_status;
	spi_finalize_current_message(spi->master);

	वापस ret;
पूर्ण

अटल व्योम aपंचांगel_spi_cleanup(काष्ठा spi_device *spi)
अणु
	काष्ठा aपंचांगel_spi_device	*asd = spi->controller_state;

	अगर (!asd)
		वापस;

	spi->controller_state = शून्य;
	kमुक्त(asd);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक aपंचांगel_get_version(काष्ठा aपंचांगel_spi *as)
अणु
	वापस spi_पढ़ोl(as, VERSION) & 0x00000fff;
पूर्ण

अटल व्योम aपंचांगel_get_caps(काष्ठा aपंचांगel_spi *as)
अणु
	अचिन्हित पूर्णांक version;

	version = aपंचांगel_get_version(as);

	as->caps.is_spi2 = version > 0x121;
	as->caps.has_wdrbt = version >= 0x210;
	as->caps.has_dma_support = version >= 0x212;
	as->caps.has_pdc_support = version < 0x212;
पूर्ण

अटल व्योम aपंचांगel_spi_init(काष्ठा aपंचांगel_spi *as)
अणु
	spi_ग_लिखोl(as, CR, SPI_BIT(SWRST));
	spi_ग_लिखोl(as, CR, SPI_BIT(SWRST)); /* AT91SAM9263 Rev B workaround */

	/* It is recommended to enable FIFOs first thing after reset */
	अगर (as->fअगरo_size)
		spi_ग_लिखोl(as, CR, SPI_BIT(FIFOEN));

	अगर (as->caps.has_wdrbt) अणु
		spi_ग_लिखोl(as, MR, SPI_BIT(WDRBT) | SPI_BIT(MODFDIS)
				| SPI_BIT(MSTR));
	पूर्ण अन्यथा अणु
		spi_ग_लिखोl(as, MR, SPI_BIT(MSTR) | SPI_BIT(MODFDIS));
	पूर्ण

	अगर (as->use_pdc)
		spi_ग_लिखोl(as, PTCR, SPI_BIT(RXTDIS) | SPI_BIT(TXTDIS));
	spi_ग_लिखोl(as, CR, SPI_BIT(SPIEN));
पूर्ण

अटल पूर्णांक aपंचांगel_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource		*regs;
	पूर्णांक			irq;
	काष्ठा clk		*clk;
	पूर्णांक			ret;
	काष्ठा spi_master	*master;
	काष्ठा aपंचांगel_spi	*as;

	/* Select शेष pin state */
	pinctrl_pm_select_शेष_state(&pdev->dev);

	regs = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!regs)
		वापस -ENXIO;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	clk = devm_clk_get(&pdev->dev, "spi_clk");
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	/* setup spi core then aपंचांगel-specअगरic driver state */
	master = spi_alloc_master(&pdev->dev, माप(*as));
	अगर (!master)
		वापस -ENOMEM;

	/* the spi->mode bits understood by this driver: */
	master->use_gpio_descriptors = true;
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;
	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(8, 16);
	master->dev.of_node = pdev->dev.of_node;
	master->bus_num = pdev->id;
	master->num_chipselect = 4;
	master->setup = aपंचांगel_spi_setup;
	master->flags = (SPI_MASTER_MUST_RX | SPI_MASTER_MUST_TX);
	master->transfer_one_message = aपंचांगel_spi_transfer_one_message;
	master->cleanup = aपंचांगel_spi_cleanup;
	master->स्वतः_runसमय_pm = true;
	master->max_dma_len = SPI_MAX_DMA_XFER;
	master->can_dma = aपंचांगel_spi_can_dma;
	platक्रमm_set_drvdata(pdev, master);

	as = spi_master_get_devdata(master);

	spin_lock_init(&as->lock);

	as->pdev = pdev;
	as->regs = devm_ioremap_resource(&pdev->dev, regs);
	अगर (IS_ERR(as->regs)) अणु
		ret = PTR_ERR(as->regs);
		जाओ out_unmap_regs;
	पूर्ण
	as->phybase = regs->start;
	as->irq = irq;
	as->clk = clk;

	init_completion(&as->xfer_completion);

	aपंचांगel_get_caps(as);

	as->use_dma = false;
	as->use_pdc = false;
	अगर (as->caps.has_dma_support) अणु
		ret = aपंचांगel_spi_configure_dma(master, as);
		अगर (ret == 0) अणु
			as->use_dma = true;
		पूर्ण अन्यथा अगर (ret == -EPROBE_DEFER) अणु
			जाओ out_unmap_regs;
		पूर्ण
	पूर्ण अन्यथा अगर (as->caps.has_pdc_support) अणु
		as->use_pdc = true;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_SOC_SAM_V4_V5)) अणु
		as->addr_rx_bbuf = dma_alloc_coherent(&pdev->dev,
						      SPI_MAX_DMA_XFER,
						      &as->dma_addr_rx_bbuf,
						      GFP_KERNEL | GFP_DMA);
		अगर (!as->addr_rx_bbuf) अणु
			as->use_dma = false;
		पूर्ण अन्यथा अणु
			as->addr_tx_bbuf = dma_alloc_coherent(&pdev->dev,
					SPI_MAX_DMA_XFER,
					&as->dma_addr_tx_bbuf,
					GFP_KERNEL | GFP_DMA);
			अगर (!as->addr_tx_bbuf) अणु
				as->use_dma = false;
				dma_मुक्त_coherent(&pdev->dev, SPI_MAX_DMA_XFER,
						  as->addr_rx_bbuf,
						  as->dma_addr_rx_bbuf);
			पूर्ण
		पूर्ण
		अगर (!as->use_dma)
			dev_info(master->dev.parent,
				 "  can not allocate dma coherent memory\n");
	पूर्ण

	अगर (as->caps.has_dma_support && !as->use_dma)
		dev_info(&pdev->dev, "Atmel SPI Controller using PIO only\n");

	अगर (as->use_pdc) अणु
		ret = devm_request_irq(&pdev->dev, irq, aपंचांगel_spi_pdc_पूर्णांकerrupt,
					0, dev_name(&pdev->dev), master);
	पूर्ण अन्यथा अणु
		ret = devm_request_irq(&pdev->dev, irq, aपंचांगel_spi_pio_पूर्णांकerrupt,
					0, dev_name(&pdev->dev), master);
	पूर्ण
	अगर (ret)
		जाओ out_unmap_regs;

	/* Initialize the hardware */
	ret = clk_prepare_enable(clk);
	अगर (ret)
		जाओ out_मुक्त_irq;

	as->spi_clk = clk_get_rate(clk);

	as->fअगरo_size = 0;
	अगर (!of_property_पढ़ो_u32(pdev->dev.of_node, "atmel,fifo-size",
				  &as->fअगरo_size)) अणु
		dev_info(&pdev->dev, "Using FIFO (%u data)\n", as->fअगरo_size);
	पूर्ण

	aपंचांगel_spi_init(as);

	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, AUTOSUSPEND_TIMEOUT);
	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);

	ret = devm_spi_रेजिस्टर_master(&pdev->dev, master);
	अगर (ret)
		जाओ out_मुक्त_dma;

	/* go! */
	dev_info(&pdev->dev, "Atmel SPI Controller version 0x%x at 0x%08lx (irq %d)\n",
			aपंचांगel_get_version(as), (अचिन्हित दीर्घ)regs->start,
			irq);

	वापस 0;

out_मुक्त_dma:
	pm_runसमय_disable(&pdev->dev);
	pm_runसमय_set_suspended(&pdev->dev);

	अगर (as->use_dma)
		aपंचांगel_spi_release_dma(master);

	spi_ग_लिखोl(as, CR, SPI_BIT(SWRST));
	spi_ग_लिखोl(as, CR, SPI_BIT(SWRST)); /* AT91SAM9263 Rev B workaround */
	clk_disable_unprepare(clk);
out_मुक्त_irq:
out_unmap_regs:
	spi_master_put(master);
	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master	*master = platक्रमm_get_drvdata(pdev);
	काष्ठा aपंचांगel_spi	*as = spi_master_get_devdata(master);

	pm_runसमय_get_sync(&pdev->dev);

	/* reset the hardware and block queue progress */
	अगर (as->use_dma) अणु
		aपंचांगel_spi_stop_dma(master);
		aपंचांगel_spi_release_dma(master);
		अगर (IS_ENABLED(CONFIG_SOC_SAM_V4_V5)) अणु
			dma_मुक्त_coherent(&pdev->dev, SPI_MAX_DMA_XFER,
					  as->addr_tx_bbuf,
					  as->dma_addr_tx_bbuf);
			dma_मुक्त_coherent(&pdev->dev, SPI_MAX_DMA_XFER,
					  as->addr_rx_bbuf,
					  as->dma_addr_rx_bbuf);
		पूर्ण
	पूर्ण

	spin_lock_irq(&as->lock);
	spi_ग_लिखोl(as, CR, SPI_BIT(SWRST));
	spi_ग_लिखोl(as, CR, SPI_BIT(SWRST)); /* AT91SAM9263 Rev B workaround */
	spi_पढ़ोl(as, SR);
	spin_unlock_irq(&as->lock);

	clk_disable_unprepare(as->clk);

	pm_runसमय_put_noidle(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक aपंचांगel_spi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा aपंचांगel_spi *as = spi_master_get_devdata(master);

	clk_disable_unprepare(as->clk);
	pinctrl_pm_select_sleep_state(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_spi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा aपंचांगel_spi *as = spi_master_get_devdata(master);

	pinctrl_pm_select_शेष_state(dev);

	वापस clk_prepare_enable(as->clk);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक aपंचांगel_spi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	पूर्णांक ret;

	/* Stop the queue running */
	ret = spi_master_suspend(master);
	अगर (ret)
		वापस ret;

	अगर (!pm_runसमय_suspended(dev))
		aपंचांगel_spi_runसमय_suspend(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_spi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा aपंचांगel_spi *as = spi_master_get_devdata(master);
	पूर्णांक ret;

	ret = clk_prepare_enable(as->clk);
	अगर (ret)
		वापस ret;

	aपंचांगel_spi_init(as);

	clk_disable_unprepare(as->clk);

	अगर (!pm_runसमय_suspended(dev)) अणु
		ret = aपंचांगel_spi_runसमय_resume(dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Start the queue running */
	वापस spi_master_resume(master);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops aपंचांगel_spi_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(aपंचांगel_spi_suspend, aपंचांगel_spi_resume)
	SET_RUNTIME_PM_OPS(aपंचांगel_spi_runसमय_suspend,
			   aपंचांगel_spi_runसमय_resume, शून्य)
पूर्ण;
#घोषणा ATMEL_SPI_PM_OPS	(&aपंचांगel_spi_pm_ops)
#अन्यथा
#घोषणा ATMEL_SPI_PM_OPS	शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id aपंचांगel_spi_dt_ids[] = अणु
	अणु .compatible = "atmel,at91rm9200-spi" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, aपंचांगel_spi_dt_ids);

अटल काष्ठा platक्रमm_driver aपंचांगel_spi_driver = अणु
	.driver		= अणु
		.name	= "atmel_spi",
		.pm	= ATMEL_SPI_PM_OPS,
		.of_match_table	= aपंचांगel_spi_dt_ids,
	पूर्ण,
	.probe		= aपंचांगel_spi_probe,
	.हटाओ		= aपंचांगel_spi_हटाओ,
पूर्ण;
module_platक्रमm_driver(aपंचांगel_spi_driver);

MODULE_DESCRIPTION("Atmel AT32/AT91 SPI Controller driver");
MODULE_AUTHOR("Haavard Skinnemoen (Atmel)");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:atmel_spi");
