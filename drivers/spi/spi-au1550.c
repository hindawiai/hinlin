<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * au1550 psc spi controller driver
 * may work also with au1200, au1210, au1250
 * will not work on au1000, au1100 and au1500 (no full spi controller there)
 *
 * Copyright (c) 2006 ATRON electronic GmbH
 * Author: Jan Nikitenko <jan.nikitenko@gmail.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/resource.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi_bitbang.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/completion.h>
#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/mach-au1x00/au1xxx_psc.h>
#समावेश <यंत्र/mach-au1x00/au1xxx_dbdma.h>

#समावेश <यंत्र/mach-au1x00/au1550_spi.h>

अटल अचिन्हित पूर्णांक usedma = 1;
module_param(usedma, uपूर्णांक, 0644);

/*
#घोषणा AU1550_SPI_DEBUG_LOOPBACK
*/


#घोषणा AU1550_SPI_DBDMA_DESCRIPTORS 1
#घोषणा AU1550_SPI_DMA_RXTMP_MINSIZE 2048U

काष्ठा au1550_spi अणु
	काष्ठा spi_bitbang bitbang;

	अस्थिर psc_spi_t __iomem *regs;
	पूर्णांक irq;

	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक tx_count;
	अचिन्हित पूर्णांक rx_count;
	स्थिर u8 *tx;
	u8 *rx;

	व्योम (*rx_word)(काष्ठा au1550_spi *hw);
	व्योम (*tx_word)(काष्ठा au1550_spi *hw);
	पूर्णांक (*txrx_bufs)(काष्ठा spi_device *spi, काष्ठा spi_transfer *t);
	irqवापस_t (*irq_callback)(काष्ठा au1550_spi *hw);

	काष्ठा completion master_करोne;

	अचिन्हित पूर्णांक usedma;
	u32 dma_tx_id;
	u32 dma_rx_id;
	u32 dma_tx_ch;
	u32 dma_rx_ch;

	u8 *dma_rx_पंचांगpbuf;
	अचिन्हित पूर्णांक dma_rx_पंचांगpbuf_size;
	u32 dma_rx_पंचांगpbuf_addr;

	काष्ठा spi_master *master;
	काष्ठा device *dev;
	काष्ठा au1550_spi_info *pdata;
	काष्ठा resource *ioarea;
पूर्ण;


/* we use an 8-bit memory device क्रम dma transfers to/from spi fअगरo */
अटल dbdev_tab_t au1550_spi_mem_dbdev = अणु
	.dev_id			= DBDMA_MEM_CHAN,
	.dev_flags		= DEV_FLAGS_ANYUSE|DEV_FLAGS_SYNC,
	.dev_tsize		= 0,
	.dev_devwidth		= 8,
	.dev_physaddr		= 0x00000000,
	.dev_पूर्णांकlevel		= 0,
	.dev_पूर्णांकpolarity	= 0
पूर्ण;

अटल पूर्णांक ddma_memid;	/* id to above mem dma device */

अटल व्योम au1550_spi_bits_handlers_set(काष्ठा au1550_spi *hw, पूर्णांक bpw);


/*
 *  compute BRG and DIV bits to setup spi घड़ी based on मुख्य input घड़ी rate
 *  that was specअगरied in platक्रमm data काष्ठाure
 *  according to au1550 datasheet:
 *    psc_tempclk = psc_मुख्यclk / (2 << DIV)
 *    spiclk = psc_tempclk / (2 * (BRG + 1))
 *    BRG valid range is 4..63
 *    DIV valid range is 0..3
 */
अटल u32 au1550_spi_baudcfg(काष्ठा au1550_spi *hw, अचिन्हित पूर्णांक speed_hz)
अणु
	u32 मुख्यclk_hz = hw->pdata->मुख्यclk_hz;
	u32 भाग, brg;

	क्रम (भाग = 0; भाग < 4; भाग++) अणु
		brg = मुख्यclk_hz / speed_hz / (4 << भाग);
		/* now we have BRG+1 in brg, so count with that */
		अगर (brg < (4 + 1)) अणु
			brg = (4 + 1);	/* speed_hz too big */
			अवरोध;		/* set lowest brg (भाग is == 0) */
		पूर्ण
		अगर (brg <= (63 + 1))
			अवरोध;		/* we have valid brg and भाग */
	पूर्ण
	अगर (भाग == 4) अणु
		भाग = 3;		/* speed_hz too small */
		brg = (63 + 1);		/* set highest brg and भाग */
	पूर्ण
	brg--;
	वापस PSC_SPICFG_SET_BAUD(brg) | PSC_SPICFG_SET_DIV(भाग);
पूर्ण

अटल अंतरभूत व्योम au1550_spi_mask_ack_all(काष्ठा au1550_spi *hw)
अणु
	hw->regs->psc_spimsk =
		  PSC_SPIMSK_MM | PSC_SPIMSK_RR | PSC_SPIMSK_RO
		| PSC_SPIMSK_RU | PSC_SPIMSK_TR | PSC_SPIMSK_TO
		| PSC_SPIMSK_TU | PSC_SPIMSK_SD | PSC_SPIMSK_MD;
	wmb(); /* drain ग_लिखोbuffer */

	hw->regs->psc_spievent =
		  PSC_SPIEVNT_MM | PSC_SPIEVNT_RR | PSC_SPIEVNT_RO
		| PSC_SPIEVNT_RU | PSC_SPIEVNT_TR | PSC_SPIEVNT_TO
		| PSC_SPIEVNT_TU | PSC_SPIEVNT_SD | PSC_SPIEVNT_MD;
	wmb(); /* drain ग_लिखोbuffer */
पूर्ण

अटल व्योम au1550_spi_reset_fअगरos(काष्ठा au1550_spi *hw)
अणु
	u32 pcr;

	hw->regs->psc_spipcr = PSC_SPIPCR_RC | PSC_SPIPCR_TC;
	wmb(); /* drain ग_लिखोbuffer */
	करो अणु
		pcr = hw->regs->psc_spipcr;
		wmb(); /* drain ग_लिखोbuffer */
	पूर्ण जबतक (pcr != 0);
पूर्ण

/*
 * dma transfers are used क्रम the most common spi word size of 8-bits
 * we cannot easily change alपढ़ोy set up dma channels' width, so अगर we wanted
 * dma support क्रम more than 8-bit words (up to 24 bits), we would need to
 * setup dma channels from scratch on each spi transfer, based on bits_per_word
 * instead we have pre set up 8 bit dma channels supporting spi 4 to 8 bits
 * transfers, and 9 to 24 bits spi transfers will be करोne in pio irq based mode
 * callbacks to handle dma or pio are set up in au1550_spi_bits_handlers_set()
 */
अटल व्योम au1550_spi_chipsel(काष्ठा spi_device *spi, पूर्णांक value)
अणु
	काष्ठा au1550_spi *hw = spi_master_get_devdata(spi->master);
	अचिन्हित पूर्णांक cspol = spi->mode & SPI_CS_HIGH ? 1 : 0;
	u32 cfg, stat;

	चयन (value) अणु
	हाल BITBANG_CS_INACTIVE:
		अगर (hw->pdata->deactivate_cs)
			hw->pdata->deactivate_cs(hw->pdata, spi->chip_select,
					cspol);
		अवरोध;

	हाल BITBANG_CS_ACTIVE:
		au1550_spi_bits_handlers_set(hw, spi->bits_per_word);

		cfg = hw->regs->psc_spicfg;
		wmb(); /* drain ग_लिखोbuffer */
		hw->regs->psc_spicfg = cfg & ~PSC_SPICFG_DE_ENABLE;
		wmb(); /* drain ग_लिखोbuffer */

		अगर (spi->mode & SPI_CPOL)
			cfg |= PSC_SPICFG_BI;
		अन्यथा
			cfg &= ~PSC_SPICFG_BI;
		अगर (spi->mode & SPI_CPHA)
			cfg &= ~PSC_SPICFG_CDE;
		अन्यथा
			cfg |= PSC_SPICFG_CDE;

		अगर (spi->mode & SPI_LSB_FIRST)
			cfg |= PSC_SPICFG_MLF;
		अन्यथा
			cfg &= ~PSC_SPICFG_MLF;

		अगर (hw->usedma && spi->bits_per_word <= 8)
			cfg &= ~PSC_SPICFG_DD_DISABLE;
		अन्यथा
			cfg |= PSC_SPICFG_DD_DISABLE;
		cfg = PSC_SPICFG_CLR_LEN(cfg);
		cfg |= PSC_SPICFG_SET_LEN(spi->bits_per_word);

		cfg = PSC_SPICFG_CLR_BAUD(cfg);
		cfg &= ~PSC_SPICFG_SET_DIV(3);
		cfg |= au1550_spi_baudcfg(hw, spi->max_speed_hz);

		hw->regs->psc_spicfg = cfg | PSC_SPICFG_DE_ENABLE;
		wmb(); /* drain ग_लिखोbuffer */
		करो अणु
			stat = hw->regs->psc_spistat;
			wmb(); /* drain ग_लिखोbuffer */
		पूर्ण जबतक ((stat & PSC_SPISTAT_DR) == 0);

		अगर (hw->pdata->activate_cs)
			hw->pdata->activate_cs(hw->pdata, spi->chip_select,
					cspol);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक au1550_spi_setupxfer(काष्ठा spi_device *spi, काष्ठा spi_transfer *t)
अणु
	काष्ठा au1550_spi *hw = spi_master_get_devdata(spi->master);
	अचिन्हित पूर्णांक bpw, hz;
	u32 cfg, stat;

	अगर (t) अणु
		bpw = t->bits_per_word;
		hz = t->speed_hz;
	पूर्ण अन्यथा अणु
		bpw = spi->bits_per_word;
		hz = spi->max_speed_hz;
	पूर्ण

	अगर (!hz)
		वापस -EINVAL;

	au1550_spi_bits_handlers_set(hw, spi->bits_per_word);

	cfg = hw->regs->psc_spicfg;
	wmb(); /* drain ग_लिखोbuffer */
	hw->regs->psc_spicfg = cfg & ~PSC_SPICFG_DE_ENABLE;
	wmb(); /* drain ग_लिखोbuffer */

	अगर (hw->usedma && bpw <= 8)
		cfg &= ~PSC_SPICFG_DD_DISABLE;
	अन्यथा
		cfg |= PSC_SPICFG_DD_DISABLE;
	cfg = PSC_SPICFG_CLR_LEN(cfg);
	cfg |= PSC_SPICFG_SET_LEN(bpw);

	cfg = PSC_SPICFG_CLR_BAUD(cfg);
	cfg &= ~PSC_SPICFG_SET_DIV(3);
	cfg |= au1550_spi_baudcfg(hw, hz);

	hw->regs->psc_spicfg = cfg;
	wmb(); /* drain ग_लिखोbuffer */

	अगर (cfg & PSC_SPICFG_DE_ENABLE) अणु
		करो अणु
			stat = hw->regs->psc_spistat;
			wmb(); /* drain ग_लिखोbuffer */
		पूर्ण जबतक ((stat & PSC_SPISTAT_DR) == 0);
	पूर्ण

	au1550_spi_reset_fअगरos(hw);
	au1550_spi_mask_ack_all(hw);
	वापस 0;
पूर्ण

/*
 * क्रम dma spi transfers, we have to setup rx channel, otherwise there is
 * no reliable way how to recognize that spi transfer is करोne
 * dma complete callbacks are called beक्रमe real spi transfer is finished
 * and अगर only tx dma channel is set up (and rx fअगरo overflow event masked)
 * spi master करोne event irq is not generated unless rx fअगरo is empty (emptied)
 * so we need rx पंचांगp buffer to use क्रम rx dma अगर user करोes not provide one
 */
अटल पूर्णांक au1550_spi_dma_rxपंचांगp_alloc(काष्ठा au1550_spi *hw, अचिन्हित पूर्णांक size)
अणु
	hw->dma_rx_पंचांगpbuf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!hw->dma_rx_पंचांगpbuf)
		वापस -ENOMEM;
	hw->dma_rx_पंचांगpbuf_size = size;
	hw->dma_rx_पंचांगpbuf_addr = dma_map_single(hw->dev, hw->dma_rx_पंचांगpbuf,
			size, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(hw->dev, hw->dma_rx_पंचांगpbuf_addr)) अणु
		kमुक्त(hw->dma_rx_पंचांगpbuf);
		hw->dma_rx_पंचांगpbuf = 0;
		hw->dma_rx_पंचांगpbuf_size = 0;
		वापस -EFAULT;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम au1550_spi_dma_rxपंचांगp_मुक्त(काष्ठा au1550_spi *hw)
अणु
	dma_unmap_single(hw->dev, hw->dma_rx_पंचांगpbuf_addr,
			hw->dma_rx_पंचांगpbuf_size, DMA_FROM_DEVICE);
	kमुक्त(hw->dma_rx_पंचांगpbuf);
	hw->dma_rx_पंचांगpbuf = 0;
	hw->dma_rx_पंचांगpbuf_size = 0;
पूर्ण

अटल पूर्णांक au1550_spi_dma_txrxb(काष्ठा spi_device *spi, काष्ठा spi_transfer *t)
अणु
	काष्ठा au1550_spi *hw = spi_master_get_devdata(spi->master);
	dma_addr_t dma_tx_addr;
	dma_addr_t dma_rx_addr;
	u32 res;

	hw->len = t->len;
	hw->tx_count = 0;
	hw->rx_count = 0;

	hw->tx = t->tx_buf;
	hw->rx = t->rx_buf;
	dma_tx_addr = t->tx_dma;
	dma_rx_addr = t->rx_dma;

	/*
	 * check अगर buffers are alपढ़ोy dma mapped, map them otherwise:
	 * - first map the TX buffer, so cache data माला_लो written to memory
	 * - then map the RX buffer, so that cache entries (with
	 *   soon-to-be-stale data) get हटाओd
	 * use rx buffer in place of tx अगर tx buffer was not provided
	 * use temp rx buffer (pपुनः_स्मृतिated or पुनः_स्मृति to fit) क्रम rx dma
	 */
	अगर (t->tx_buf) अणु
		अगर (t->tx_dma == 0) अणु	/* अगर DMA_ADDR_INVALID, map it */
			dma_tx_addr = dma_map_single(hw->dev,
					(व्योम *)t->tx_buf,
					t->len, DMA_TO_DEVICE);
			अगर (dma_mapping_error(hw->dev, dma_tx_addr))
				dev_err(hw->dev, "tx dma map error\n");
		पूर्ण
	पूर्ण

	अगर (t->rx_buf) अणु
		अगर (t->rx_dma == 0) अणु	/* अगर DMA_ADDR_INVALID, map it */
			dma_rx_addr = dma_map_single(hw->dev,
					(व्योम *)t->rx_buf,
					t->len, DMA_FROM_DEVICE);
			अगर (dma_mapping_error(hw->dev, dma_rx_addr))
				dev_err(hw->dev, "rx dma map error\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (t->len > hw->dma_rx_पंचांगpbuf_size) अणु
			पूर्णांक ret;

			au1550_spi_dma_rxपंचांगp_मुक्त(hw);
			ret = au1550_spi_dma_rxपंचांगp_alloc(hw, max(t->len,
					AU1550_SPI_DMA_RXTMP_MINSIZE));
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		hw->rx = hw->dma_rx_पंचांगpbuf;
		dma_rx_addr = hw->dma_rx_पंचांगpbuf_addr;
		dma_sync_single_क्रम_device(hw->dev, dma_rx_addr,
			t->len, DMA_FROM_DEVICE);
	पूर्ण

	अगर (!t->tx_buf) अणु
		dma_sync_single_क्रम_device(hw->dev, dma_rx_addr,
				t->len, DMA_BIसूचीECTIONAL);
		hw->tx = hw->rx;
	पूर्ण

	/* put buffers on the ring */
	res = au1xxx_dbdma_put_dest(hw->dma_rx_ch, virt_to_phys(hw->rx),
				    t->len, DDMA_FLAGS_IE);
	अगर (!res)
		dev_err(hw->dev, "rx dma put dest error\n");

	res = au1xxx_dbdma_put_source(hw->dma_tx_ch, virt_to_phys(hw->tx),
				      t->len, DDMA_FLAGS_IE);
	अगर (!res)
		dev_err(hw->dev, "tx dma put source error\n");

	au1xxx_dbdma_start(hw->dma_rx_ch);
	au1xxx_dbdma_start(hw->dma_tx_ch);

	/* by शेष enable nearly all events पूर्णांकerrupt */
	hw->regs->psc_spimsk = PSC_SPIMSK_SD;
	wmb(); /* drain ग_लिखोbuffer */

	/* start the transfer */
	hw->regs->psc_spipcr = PSC_SPIPCR_MS;
	wmb(); /* drain ग_लिखोbuffer */

	रुको_क्रम_completion(&hw->master_करोne);

	au1xxx_dbdma_stop(hw->dma_tx_ch);
	au1xxx_dbdma_stop(hw->dma_rx_ch);

	अगर (!t->rx_buf) अणु
		/* using the temporal pपुनः_स्मृतिated and premapped buffer */
		dma_sync_single_क्रम_cpu(hw->dev, dma_rx_addr, t->len,
			DMA_FROM_DEVICE);
	पूर्ण
	/* unmap buffers अगर mapped above */
	अगर (t->rx_buf && t->rx_dma == 0)
		dma_unmap_single(hw->dev, dma_rx_addr, t->len,
			DMA_FROM_DEVICE);
	अगर (t->tx_buf && t->tx_dma == 0)
		dma_unmap_single(hw->dev, dma_tx_addr, t->len,
			DMA_TO_DEVICE);

	वापस hw->rx_count < hw->tx_count ? hw->rx_count : hw->tx_count;
पूर्ण

अटल irqवापस_t au1550_spi_dma_irq_callback(काष्ठा au1550_spi *hw)
अणु
	u32 stat, evnt;

	stat = hw->regs->psc_spistat;
	evnt = hw->regs->psc_spievent;
	wmb(); /* drain ग_लिखोbuffer */
	अगर ((stat & PSC_SPISTAT_DI) == 0) अणु
		dev_err(hw->dev, "Unexpected IRQ!\n");
		वापस IRQ_NONE;
	पूर्ण

	अगर ((evnt & (PSC_SPIEVNT_MM | PSC_SPIEVNT_RO
				| PSC_SPIEVNT_RU | PSC_SPIEVNT_TO
				| PSC_SPIEVNT_TU | PSC_SPIEVNT_SD))
			!= 0) अणु
		/*
		 * due to an spi error we consider transfer as करोne,
		 * so mask all events until beक्रमe next transfer start
		 * and stop the possibly running dma immediately
		 */
		au1550_spi_mask_ack_all(hw);
		au1xxx_dbdma_stop(hw->dma_rx_ch);
		au1xxx_dbdma_stop(hw->dma_tx_ch);

		/* get number of transferred bytes */
		hw->rx_count = hw->len - au1xxx_get_dma_residue(hw->dma_rx_ch);
		hw->tx_count = hw->len - au1xxx_get_dma_residue(hw->dma_tx_ch);

		au1xxx_dbdma_reset(hw->dma_rx_ch);
		au1xxx_dbdma_reset(hw->dma_tx_ch);
		au1550_spi_reset_fअगरos(hw);

		अगर (evnt == PSC_SPIEVNT_RO)
			dev_err(hw->dev,
				"dma transfer: receive FIFO overflow!\n");
		अन्यथा
			dev_err(hw->dev,
				"dma transfer: unexpected SPI error (event=0x%x stat=0x%x)!\n",
				evnt, stat);

		complete(&hw->master_करोne);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर ((evnt & PSC_SPIEVNT_MD) != 0) अणु
		/* transfer completed successfully */
		au1550_spi_mask_ack_all(hw);
		hw->rx_count = hw->len;
		hw->tx_count = hw->len;
		complete(&hw->master_करोne);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण


/* routines to handle dअगरferent word sizes in pio mode */
#घोषणा AU1550_SPI_RX_WORD(size, mask)					\
अटल व्योम au1550_spi_rx_word_##size(काष्ठा au1550_spi *hw)		\
अणु									\
	u32 fअगरoword = hw->regs->psc_spitxrx & (u32)(mask);		\
	wmb(); /* drain ग_लिखोbuffer */					\
	अगर (hw->rx) अणु							\
		*(u##size *)hw->rx = (u##size)fअगरoword;			\
		hw->rx += (size) / 8;					\
	पूर्ण								\
	hw->rx_count += (size) / 8;					\
पूर्ण

#घोषणा AU1550_SPI_TX_WORD(size, mask)					\
अटल व्योम au1550_spi_tx_word_##size(काष्ठा au1550_spi *hw)		\
अणु									\
	u32 fअगरoword = 0;						\
	अगर (hw->tx) अणु							\
		fअगरoword = *(u##size *)hw->tx & (u32)(mask);		\
		hw->tx += (size) / 8;					\
	पूर्ण								\
	hw->tx_count += (size) / 8;					\
	अगर (hw->tx_count >= hw->len)					\
		fअगरoword |= PSC_SPITXRX_LC;				\
	hw->regs->psc_spitxrx = fअगरoword;				\
	wmb(); /* drain ग_लिखोbuffer */					\
पूर्ण

AU1550_SPI_RX_WORD(8, 0xff)
AU1550_SPI_RX_WORD(16, 0xffff)
AU1550_SPI_RX_WORD(32, 0xffffff)
AU1550_SPI_TX_WORD(8, 0xff)
AU1550_SPI_TX_WORD(16, 0xffff)
AU1550_SPI_TX_WORD(32, 0xffffff)

अटल पूर्णांक au1550_spi_pio_txrxb(काष्ठा spi_device *spi, काष्ठा spi_transfer *t)
अणु
	u32 stat, mask;
	काष्ठा au1550_spi *hw = spi_master_get_devdata(spi->master);

	hw->tx = t->tx_buf;
	hw->rx = t->rx_buf;
	hw->len = t->len;
	hw->tx_count = 0;
	hw->rx_count = 0;

	/* by शेष enable nearly all events after filling tx fअगरo */
	mask = PSC_SPIMSK_SD;

	/* fill the transmit FIFO */
	जबतक (hw->tx_count < hw->len) अणु

		hw->tx_word(hw);

		अगर (hw->tx_count >= hw->len) अणु
			/* mask tx fअगरo request पूर्णांकerrupt as we are करोne */
			mask |= PSC_SPIMSK_TR;
		पूर्ण

		stat = hw->regs->psc_spistat;
		wmb(); /* drain ग_लिखोbuffer */
		अगर (stat & PSC_SPISTAT_TF)
			अवरोध;
	पूर्ण

	/* enable event पूर्णांकerrupts */
	hw->regs->psc_spimsk = mask;
	wmb(); /* drain ग_लिखोbuffer */

	/* start the transfer */
	hw->regs->psc_spipcr = PSC_SPIPCR_MS;
	wmb(); /* drain ग_लिखोbuffer */

	रुको_क्रम_completion(&hw->master_करोne);

	वापस hw->rx_count < hw->tx_count ? hw->rx_count : hw->tx_count;
पूर्ण

अटल irqवापस_t au1550_spi_pio_irq_callback(काष्ठा au1550_spi *hw)
अणु
	पूर्णांक busy;
	u32 stat, evnt;

	stat = hw->regs->psc_spistat;
	evnt = hw->regs->psc_spievent;
	wmb(); /* drain ग_लिखोbuffer */
	अगर ((stat & PSC_SPISTAT_DI) == 0) अणु
		dev_err(hw->dev, "Unexpected IRQ!\n");
		वापस IRQ_NONE;
	पूर्ण

	अगर ((evnt & (PSC_SPIEVNT_MM | PSC_SPIEVNT_RO
				| PSC_SPIEVNT_RU | PSC_SPIEVNT_TO
				| PSC_SPIEVNT_SD))
			!= 0) अणु
		/*
		 * due to an error we consider transfer as करोne,
		 * so mask all events until beक्रमe next transfer start
		 */
		au1550_spi_mask_ack_all(hw);
		au1550_spi_reset_fअगरos(hw);
		dev_err(hw->dev,
			"pio transfer: unexpected SPI error (event=0x%x stat=0x%x)!\n",
			evnt, stat);
		complete(&hw->master_करोne);
		वापस IRQ_HANDLED;
	पूर्ण

	/*
	 * जबतक there is something to पढ़ो from rx fअगरo
	 * or there is a space to ग_लिखो to tx fअगरo:
	 */
	करो अणु
		busy = 0;
		stat = hw->regs->psc_spistat;
		wmb(); /* drain ग_लिखोbuffer */

		/*
		 * Take care to not let the Rx FIFO overflow.
		 *
		 * We only ग_लिखो a byte अगर we have पढ़ो one at least. Initially,
		 * the ग_लिखो fअगरo is full, so we should पढ़ो from the पढ़ो fअगरo
		 * first.
		 * In हाल we miss a word from the पढ़ो fअगरo, we should get a
		 * RO event and should back out.
		 */
		अगर (!(stat & PSC_SPISTAT_RE) && hw->rx_count < hw->len) अणु
			hw->rx_word(hw);
			busy = 1;

			अगर (!(stat & PSC_SPISTAT_TF) && hw->tx_count < hw->len)
				hw->tx_word(hw);
		पूर्ण
	पूर्ण जबतक (busy);

	hw->regs->psc_spievent = PSC_SPIEVNT_RR | PSC_SPIEVNT_TR;
	wmb(); /* drain ग_लिखोbuffer */

	/*
	 * Restart the SPI transmission in हाल of a transmit underflow.
	 * This seems to work despite the notes in the Au1550 data book
	 * of Figure 8-4 with flowअक्षरt क्रम SPI master operation:
	 *
	 * """Note 1: An XFR Error Interrupt occurs, unless masked,
	 * क्रम any of the following events: Tx FIFO Underflow,
	 * Rx FIFO Overflow, or Multiple-master Error
	 *    Note 2: In हाल of a Tx Underflow Error, all zeroes are
	 * transmitted."""
	 *
	 * By simply restarting the spi transfer on Tx Underflow Error,
	 * we assume that spi transfer was छोड़ोd instead of zeroes
	 * transmittion mentioned in the Note 2 of Au1550 data book.
	 */
	अगर (evnt & PSC_SPIEVNT_TU) अणु
		hw->regs->psc_spievent = PSC_SPIEVNT_TU | PSC_SPIEVNT_MD;
		wmb(); /* drain ग_लिखोbuffer */
		hw->regs->psc_spipcr = PSC_SPIPCR_MS;
		wmb(); /* drain ग_लिखोbuffer */
	पूर्ण

	अगर (hw->rx_count >= hw->len) अणु
		/* transfer completed successfully */
		au1550_spi_mask_ack_all(hw);
		complete(&hw->master_करोne);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक au1550_spi_txrx_bufs(काष्ठा spi_device *spi, काष्ठा spi_transfer *t)
अणु
	काष्ठा au1550_spi *hw = spi_master_get_devdata(spi->master);

	वापस hw->txrx_bufs(spi, t);
पूर्ण

अटल irqवापस_t au1550_spi_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा au1550_spi *hw = dev;

	वापस hw->irq_callback(hw);
पूर्ण

अटल व्योम au1550_spi_bits_handlers_set(काष्ठा au1550_spi *hw, पूर्णांक bpw)
अणु
	अगर (bpw <= 8) अणु
		अगर (hw->usedma) अणु
			hw->txrx_bufs = &au1550_spi_dma_txrxb;
			hw->irq_callback = &au1550_spi_dma_irq_callback;
		पूर्ण अन्यथा अणु
			hw->rx_word = &au1550_spi_rx_word_8;
			hw->tx_word = &au1550_spi_tx_word_8;
			hw->txrx_bufs = &au1550_spi_pio_txrxb;
			hw->irq_callback = &au1550_spi_pio_irq_callback;
		पूर्ण
	पूर्ण अन्यथा अगर (bpw <= 16) अणु
		hw->rx_word = &au1550_spi_rx_word_16;
		hw->tx_word = &au1550_spi_tx_word_16;
		hw->txrx_bufs = &au1550_spi_pio_txrxb;
		hw->irq_callback = &au1550_spi_pio_irq_callback;
	पूर्ण अन्यथा अणु
		hw->rx_word = &au1550_spi_rx_word_32;
		hw->tx_word = &au1550_spi_tx_word_32;
		hw->txrx_bufs = &au1550_spi_pio_txrxb;
		hw->irq_callback = &au1550_spi_pio_irq_callback;
	पूर्ण
पूर्ण

अटल व्योम au1550_spi_setup_psc_as_spi(काष्ठा au1550_spi *hw)
अणु
	u32 stat, cfg;

	/* set up the PSC क्रम SPI mode */
	hw->regs->psc_ctrl = PSC_CTRL_DISABLE;
	wmb(); /* drain ग_लिखोbuffer */
	hw->regs->psc_sel = PSC_SEL_PS_SPIMODE;
	wmb(); /* drain ग_लिखोbuffer */

	hw->regs->psc_spicfg = 0;
	wmb(); /* drain ग_लिखोbuffer */

	hw->regs->psc_ctrl = PSC_CTRL_ENABLE;
	wmb(); /* drain ग_लिखोbuffer */

	करो अणु
		stat = hw->regs->psc_spistat;
		wmb(); /* drain ग_लिखोbuffer */
	पूर्ण जबतक ((stat & PSC_SPISTAT_SR) == 0);


	cfg = hw->usedma ? 0 : PSC_SPICFG_DD_DISABLE;
	cfg |= PSC_SPICFG_SET_LEN(8);
	cfg |= PSC_SPICFG_RT_FIFO8 | PSC_SPICFG_TT_FIFO8;
	/* use minimal allowed brg and भाग values as initial setting: */
	cfg |= PSC_SPICFG_SET_BAUD(4) | PSC_SPICFG_SET_DIV(0);

#अगर_घोषित AU1550_SPI_DEBUG_LOOPBACK
	cfg |= PSC_SPICFG_LB;
#पूर्ण_अगर

	hw->regs->psc_spicfg = cfg;
	wmb(); /* drain ग_लिखोbuffer */

	au1550_spi_mask_ack_all(hw);

	hw->regs->psc_spicfg |= PSC_SPICFG_DE_ENABLE;
	wmb(); /* drain ग_लिखोbuffer */

	करो अणु
		stat = hw->regs->psc_spistat;
		wmb(); /* drain ग_लिखोbuffer */
	पूर्ण जबतक ((stat & PSC_SPISTAT_DR) == 0);

	au1550_spi_reset_fअगरos(hw);
पूर्ण


अटल पूर्णांक au1550_spi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा au1550_spi *hw;
	काष्ठा spi_master *master;
	काष्ठा resource *r;
	पूर्णांक err = 0;

	master = spi_alloc_master(&pdev->dev, माप(काष्ठा au1550_spi));
	अगर (master == शून्य) अणु
		dev_err(&pdev->dev, "No memory for spi_master\n");
		err = -ENOMEM;
		जाओ err_nomem;
	पूर्ण

	/* the spi->mode bits understood by this driver: */
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH | SPI_LSB_FIRST;
	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(4, 24);

	hw = spi_master_get_devdata(master);

	hw->master = master;
	hw->pdata = dev_get_platdata(&pdev->dev);
	hw->dev = &pdev->dev;

	अगर (hw->pdata == शून्य) अणु
		dev_err(&pdev->dev, "No platform data supplied\n");
		err = -ENOENT;
		जाओ err_no_pdata;
	पूर्ण

	r = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!r) अणु
		dev_err(&pdev->dev, "no IRQ\n");
		err = -ENODEV;
		जाओ err_no_iores;
	पूर्ण
	hw->irq = r->start;

	hw->usedma = 0;
	r = platक्रमm_get_resource(pdev, IORESOURCE_DMA, 0);
	अगर (r) अणु
		hw->dma_tx_id = r->start;
		r = platक्रमm_get_resource(pdev, IORESOURCE_DMA, 1);
		अगर (r) अणु
			hw->dma_rx_id = r->start;
			अगर (usedma && ddma_memid) अणु
				अगर (pdev->dev.dma_mask == शून्य)
					dev_warn(&pdev->dev, "no dma mask\n");
				अन्यथा
					hw->usedma = 1;
			पूर्ण
		पूर्ण
	पूर्ण

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!r) अणु
		dev_err(&pdev->dev, "no mmio resource\n");
		err = -ENODEV;
		जाओ err_no_iores;
	पूर्ण

	hw->ioarea = request_mem_region(r->start, माप(psc_spi_t),
					pdev->name);
	अगर (!hw->ioarea) अणु
		dev_err(&pdev->dev, "Cannot reserve iomem region\n");
		err = -ENXIO;
		जाओ err_no_iores;
	पूर्ण

	hw->regs = (psc_spi_t __iomem *)ioremap(r->start, माप(psc_spi_t));
	अगर (!hw->regs) अणु
		dev_err(&pdev->dev, "cannot ioremap\n");
		err = -ENXIO;
		जाओ err_ioremap;
	पूर्ण

	platक्रमm_set_drvdata(pdev, hw);

	init_completion(&hw->master_करोne);

	hw->bitbang.master = hw->master;
	hw->bitbang.setup_transfer = au1550_spi_setupxfer;
	hw->bitbang.chipselect = au1550_spi_chipsel;
	hw->bitbang.txrx_bufs = au1550_spi_txrx_bufs;

	अगर (hw->usedma) अणु
		hw->dma_tx_ch = au1xxx_dbdma_chan_alloc(ddma_memid,
			hw->dma_tx_id, शून्य, (व्योम *)hw);
		अगर (hw->dma_tx_ch == 0) अणु
			dev_err(&pdev->dev,
				"Cannot allocate tx dma channel\n");
			err = -ENXIO;
			जाओ err_no_txdma;
		पूर्ण
		au1xxx_dbdma_set_devwidth(hw->dma_tx_ch, 8);
		अगर (au1xxx_dbdma_ring_alloc(hw->dma_tx_ch,
			AU1550_SPI_DBDMA_DESCRIPTORS) == 0) अणु
			dev_err(&pdev->dev,
				"Cannot allocate tx dma descriptors\n");
			err = -ENXIO;
			जाओ err_no_txdma_descr;
		पूर्ण


		hw->dma_rx_ch = au1xxx_dbdma_chan_alloc(hw->dma_rx_id,
			ddma_memid, शून्य, (व्योम *)hw);
		अगर (hw->dma_rx_ch == 0) अणु
			dev_err(&pdev->dev,
				"Cannot allocate rx dma channel\n");
			err = -ENXIO;
			जाओ err_no_rxdma;
		पूर्ण
		au1xxx_dbdma_set_devwidth(hw->dma_rx_ch, 8);
		अगर (au1xxx_dbdma_ring_alloc(hw->dma_rx_ch,
			AU1550_SPI_DBDMA_DESCRIPTORS) == 0) अणु
			dev_err(&pdev->dev,
				"Cannot allocate rx dma descriptors\n");
			err = -ENXIO;
			जाओ err_no_rxdma_descr;
		पूर्ण

		err = au1550_spi_dma_rxपंचांगp_alloc(hw,
			AU1550_SPI_DMA_RXTMP_MINSIZE);
		अगर (err < 0) अणु
			dev_err(&pdev->dev,
				"Cannot allocate initial rx dma tmp buffer\n");
			जाओ err_dma_rxपंचांगp_alloc;
		पूर्ण
	पूर्ण

	au1550_spi_bits_handlers_set(hw, 8);

	err = request_irq(hw->irq, au1550_spi_irq, 0, pdev->name, hw);
	अगर (err) अणु
		dev_err(&pdev->dev, "Cannot claim IRQ\n");
		जाओ err_no_irq;
	पूर्ण

	master->bus_num = pdev->id;
	master->num_chipselect = hw->pdata->num_chipselect;

	/*
	 *  precompute valid range क्रम spi freq - from au1550 datasheet:
	 *    psc_tempclk = psc_मुख्यclk / (2 << DIV)
	 *    spiclk = psc_tempclk / (2 * (BRG + 1))
	 *    BRG valid range is 4..63
	 *    DIV valid range is 0..3
	 *  round the min and max frequencies to values that would still
	 *  produce valid brg and भाग
	 */
	अणु
		पूर्णांक min_भाग = (2 << 0) * (2 * (4 + 1));
		पूर्णांक max_भाग = (2 << 3) * (2 * (63 + 1));

		master->max_speed_hz = hw->pdata->मुख्यclk_hz / min_भाग;
		master->min_speed_hz =
				hw->pdata->मुख्यclk_hz / (max_भाग + 1) + 1;
	पूर्ण

	au1550_spi_setup_psc_as_spi(hw);

	err = spi_bitbang_start(&hw->bitbang);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to register SPI master\n");
		जाओ err_रेजिस्टर;
	पूर्ण

	dev_info(&pdev->dev,
		"spi master registered: bus_num=%d num_chipselect=%d\n",
		master->bus_num, master->num_chipselect);

	वापस 0;

err_रेजिस्टर:
	मुक्त_irq(hw->irq, hw);

err_no_irq:
	au1550_spi_dma_rxपंचांगp_मुक्त(hw);

err_dma_rxपंचांगp_alloc:
err_no_rxdma_descr:
	अगर (hw->usedma)
		au1xxx_dbdma_chan_मुक्त(hw->dma_rx_ch);

err_no_rxdma:
err_no_txdma_descr:
	अगर (hw->usedma)
		au1xxx_dbdma_chan_मुक्त(hw->dma_tx_ch);

err_no_txdma:
	iounmap((व्योम __iomem *)hw->regs);

err_ioremap:
	release_mem_region(r->start, माप(psc_spi_t));

err_no_iores:
err_no_pdata:
	spi_master_put(hw->master);

err_nomem:
	वापस err;
पूर्ण

अटल पूर्णांक au1550_spi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा au1550_spi *hw = platक्रमm_get_drvdata(pdev);

	dev_info(&pdev->dev, "spi master remove: bus_num=%d\n",
		hw->master->bus_num);

	spi_bitbang_stop(&hw->bitbang);
	मुक्त_irq(hw->irq, hw);
	iounmap((व्योम __iomem *)hw->regs);
	release_mem_region(hw->ioarea->start, माप(psc_spi_t));

	अगर (hw->usedma) अणु
		au1550_spi_dma_rxपंचांगp_मुक्त(hw);
		au1xxx_dbdma_chan_मुक्त(hw->dma_rx_ch);
		au1xxx_dbdma_chan_मुक्त(hw->dma_tx_ch);
	पूर्ण

	spi_master_put(hw->master);
	वापस 0;
पूर्ण

/* work with hotplug and coldplug */
MODULE_ALIAS("platform:au1550-spi");

अटल काष्ठा platक्रमm_driver au1550_spi_drv = अणु
	.probe = au1550_spi_probe,
	.हटाओ = au1550_spi_हटाओ,
	.driver = अणु
		.name = "au1550-spi",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init au1550_spi_init(व्योम)
अणु
	/*
	 * create memory device with 8 bits dev_devwidth
	 * needed क्रम proper byte ordering to spi fअगरo
	 */
	चयन (alchemy_get_cputype()) अणु
	हाल ALCHEMY_CPU_AU1550:
	हाल ALCHEMY_CPU_AU1200:
	हाल ALCHEMY_CPU_AU1300:
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	अगर (usedma) अणु
		ddma_memid = au1xxx_ddma_add_device(&au1550_spi_mem_dbdev);
		अगर (!ddma_memid)
			prपूर्णांकk(KERN_ERR "au1550-spi: cannot add memory dbdma device\n");
	पूर्ण
	वापस platक्रमm_driver_रेजिस्टर(&au1550_spi_drv);
पूर्ण
module_init(au1550_spi_init);

अटल व्योम __निकास au1550_spi_निकास(व्योम)
अणु
	अगर (usedma && ddma_memid)
		au1xxx_ddma_del_device(ddma_memid);
	platक्रमm_driver_unरेजिस्टर(&au1550_spi_drv);
पूर्ण
module_निकास(au1550_spi_निकास);

MODULE_DESCRIPTION("Au1550 PSC SPI Driver");
MODULE_AUTHOR("Jan Nikitenko <jan.nikitenko@gmail.com>");
MODULE_LICENSE("GPL");
