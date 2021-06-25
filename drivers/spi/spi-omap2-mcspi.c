<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OMAP2 McSPI controller driver
 *
 * Copyright (C) 2005, 2006 Nokia Corporation
 * Author:	Samuel Ortiz <samuel.ortiz@nokia.com> and
 *		Juha Yrjoडटloडट <juha.yrjola@nokia.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/gcd.h>

#समावेश <linux/spi/spi.h>

#समावेश <linux/platक्रमm_data/spi-omap2-mcspi.h>

#घोषणा OMAP2_MCSPI_MAX_FREQ		48000000
#घोषणा OMAP2_MCSPI_MAX_DIVIDER		4096
#घोषणा OMAP2_MCSPI_MAX_FIFODEPTH	64
#घोषणा OMAP2_MCSPI_MAX_FIFOWCNT	0xFFFF
#घोषणा SPI_AUTOSUSPEND_TIMEOUT		2000

#घोषणा OMAP2_MCSPI_REVISION		0x00
#घोषणा OMAP2_MCSPI_SYSSTATUS		0x14
#घोषणा OMAP2_MCSPI_IRQSTATUS		0x18
#घोषणा OMAP2_MCSPI_IRQENABLE		0x1c
#घोषणा OMAP2_MCSPI_WAKEUPENABLE	0x20
#घोषणा OMAP2_MCSPI_SYST		0x24
#घोषणा OMAP2_MCSPI_MODULCTRL		0x28
#घोषणा OMAP2_MCSPI_XFERLEVEL		0x7c

/* per-channel banks, 0x14 bytes each, first is: */
#घोषणा OMAP2_MCSPI_CHCONF0		0x2c
#घोषणा OMAP2_MCSPI_CHSTAT0		0x30
#घोषणा OMAP2_MCSPI_CHCTRL0		0x34
#घोषणा OMAP2_MCSPI_TX0			0x38
#घोषणा OMAP2_MCSPI_RX0			0x3c

/* per-रेजिस्टर biपंचांगasks: */
#घोषणा OMAP2_MCSPI_IRQSTATUS_EOW	BIT(17)

#घोषणा OMAP2_MCSPI_MODULCTRL_SINGLE	BIT(0)
#घोषणा OMAP2_MCSPI_MODULCTRL_MS	BIT(2)
#घोषणा OMAP2_MCSPI_MODULCTRL_STEST	BIT(3)

#घोषणा OMAP2_MCSPI_CHCONF_PHA		BIT(0)
#घोषणा OMAP2_MCSPI_CHCONF_POL		BIT(1)
#घोषणा OMAP2_MCSPI_CHCONF_CLKD_MASK	(0x0f << 2)
#घोषणा OMAP2_MCSPI_CHCONF_EPOL		BIT(6)
#घोषणा OMAP2_MCSPI_CHCONF_WL_MASK	(0x1f << 7)
#घोषणा OMAP2_MCSPI_CHCONF_TRM_RX_ONLY	BIT(12)
#घोषणा OMAP2_MCSPI_CHCONF_TRM_TX_ONLY	BIT(13)
#घोषणा OMAP2_MCSPI_CHCONF_TRM_MASK	(0x03 << 12)
#घोषणा OMAP2_MCSPI_CHCONF_DMAW		BIT(14)
#घोषणा OMAP2_MCSPI_CHCONF_DMAR		BIT(15)
#घोषणा OMAP2_MCSPI_CHCONF_DPE0		BIT(16)
#घोषणा OMAP2_MCSPI_CHCONF_DPE1		BIT(17)
#घोषणा OMAP2_MCSPI_CHCONF_IS		BIT(18)
#घोषणा OMAP2_MCSPI_CHCONF_TURBO	BIT(19)
#घोषणा OMAP2_MCSPI_CHCONF_FORCE	BIT(20)
#घोषणा OMAP2_MCSPI_CHCONF_FFET		BIT(27)
#घोषणा OMAP2_MCSPI_CHCONF_FFER		BIT(28)
#घोषणा OMAP2_MCSPI_CHCONF_CLKG		BIT(29)

#घोषणा OMAP2_MCSPI_CHSTAT_RXS		BIT(0)
#घोषणा OMAP2_MCSPI_CHSTAT_TXS		BIT(1)
#घोषणा OMAP2_MCSPI_CHSTAT_EOT		BIT(2)
#घोषणा OMAP2_MCSPI_CHSTAT_TXFFE	BIT(3)

#घोषणा OMAP2_MCSPI_CHCTRL_EN		BIT(0)
#घोषणा OMAP2_MCSPI_CHCTRL_EXTCLK_MASK	(0xff << 8)

#घोषणा OMAP2_MCSPI_WAKEUPENABLE_WKEN	BIT(0)

/* We have 2 DMA channels per CS, one क्रम RX and one क्रम TX */
काष्ठा omap2_mcspi_dma अणु
	काष्ठा dma_chan *dma_tx;
	काष्ठा dma_chan *dma_rx;

	काष्ठा completion dma_tx_completion;
	काष्ठा completion dma_rx_completion;

	अक्षर dma_rx_ch_name[14];
	अक्षर dma_tx_ch_name[14];
पूर्ण;

/* use PIO क्रम small transfers, aव्योमing DMA setup/tearकरोwn overhead and
 * cache operations; better heuristics consider wordsize and bitrate.
 */
#घोषणा DMA_MIN_BYTES			160


/*
 * Used क्रम context save and restore, काष्ठाure members to be updated whenever
 * corresponding रेजिस्टरs are modअगरied.
 */
काष्ठा omap2_mcspi_regs अणु
	u32 modulctrl;
	u32 wakeupenable;
	काष्ठा list_head cs;
पूर्ण;

काष्ठा omap2_mcspi अणु
	काष्ठा completion	txकरोne;
	काष्ठा spi_master	*master;
	/* Virtual base address of the controller */
	व्योम __iomem		*base;
	अचिन्हित दीर्घ		phys;
	/* SPI1 has 4 channels, जबतक SPI2 has 2 */
	काष्ठा omap2_mcspi_dma	*dma_channels;
	काष्ठा device		*dev;
	काष्ठा omap2_mcspi_regs ctx;
	पूर्णांक			fअगरo_depth;
	bool			slave_पातed;
	अचिन्हित पूर्णांक		pin_dir:1;
	माप_प्रकार			max_xfer_len;
पूर्ण;

काष्ठा omap2_mcspi_cs अणु
	व्योम __iomem		*base;
	अचिन्हित दीर्घ		phys;
	पूर्णांक			word_len;
	u16			mode;
	काष्ठा list_head	node;
	/* Context save and restore shaकरोw रेजिस्टर */
	u32			chconf0, chctrl0;
पूर्ण;

अटल अंतरभूत व्योम mcspi_ग_लिखो_reg(काष्ठा spi_master *master,
		पूर्णांक idx, u32 val)
अणु
	काष्ठा omap2_mcspi *mcspi = spi_master_get_devdata(master);

	ग_लिखोl_relaxed(val, mcspi->base + idx);
पूर्ण

अटल अंतरभूत u32 mcspi_पढ़ो_reg(काष्ठा spi_master *master, पूर्णांक idx)
अणु
	काष्ठा omap2_mcspi *mcspi = spi_master_get_devdata(master);

	वापस पढ़ोl_relaxed(mcspi->base + idx);
पूर्ण

अटल अंतरभूत व्योम mcspi_ग_लिखो_cs_reg(स्थिर काष्ठा spi_device *spi,
		पूर्णांक idx, u32 val)
अणु
	काष्ठा omap2_mcspi_cs	*cs = spi->controller_state;

	ग_लिखोl_relaxed(val, cs->base +  idx);
पूर्ण

अटल अंतरभूत u32 mcspi_पढ़ो_cs_reg(स्थिर काष्ठा spi_device *spi, पूर्णांक idx)
अणु
	काष्ठा omap2_mcspi_cs	*cs = spi->controller_state;

	वापस पढ़ोl_relaxed(cs->base + idx);
पूर्ण

अटल अंतरभूत u32 mcspi_cached_chconf0(स्थिर काष्ठा spi_device *spi)
अणु
	काष्ठा omap2_mcspi_cs *cs = spi->controller_state;

	वापस cs->chconf0;
पूर्ण

अटल अंतरभूत व्योम mcspi_ग_लिखो_chconf0(स्थिर काष्ठा spi_device *spi, u32 val)
अणु
	काष्ठा omap2_mcspi_cs *cs = spi->controller_state;

	cs->chconf0 = val;
	mcspi_ग_लिखो_cs_reg(spi, OMAP2_MCSPI_CHCONF0, val);
	mcspi_पढ़ो_cs_reg(spi, OMAP2_MCSPI_CHCONF0);
पूर्ण

अटल अंतरभूत पूर्णांक mcspi_bytes_per_word(पूर्णांक word_len)
अणु
	अगर (word_len <= 8)
		वापस 1;
	अन्यथा अगर (word_len <= 16)
		वापस 2;
	अन्यथा /* word_len <= 32 */
		वापस 4;
पूर्ण

अटल व्योम omap2_mcspi_set_dma_req(स्थिर काष्ठा spi_device *spi,
		पूर्णांक is_पढ़ो, पूर्णांक enable)
अणु
	u32 l, rw;

	l = mcspi_cached_chconf0(spi);

	अगर (is_पढ़ो) /* 1 is पढ़ो, 0 ग_लिखो */
		rw = OMAP2_MCSPI_CHCONF_DMAR;
	अन्यथा
		rw = OMAP2_MCSPI_CHCONF_DMAW;

	अगर (enable)
		l |= rw;
	अन्यथा
		l &= ~rw;

	mcspi_ग_लिखो_chconf0(spi, l);
पूर्ण

अटल व्योम omap2_mcspi_set_enable(स्थिर काष्ठा spi_device *spi, पूर्णांक enable)
अणु
	काष्ठा omap2_mcspi_cs *cs = spi->controller_state;
	u32 l;

	l = cs->chctrl0;
	अगर (enable)
		l |= OMAP2_MCSPI_CHCTRL_EN;
	अन्यथा
		l &= ~OMAP2_MCSPI_CHCTRL_EN;
	cs->chctrl0 = l;
	mcspi_ग_लिखो_cs_reg(spi, OMAP2_MCSPI_CHCTRL0, cs->chctrl0);
	/* Flash post-ग_लिखोs */
	mcspi_पढ़ो_cs_reg(spi, OMAP2_MCSPI_CHCTRL0);
पूर्ण

अटल व्योम omap2_mcspi_set_cs(काष्ठा spi_device *spi, bool enable)
अणु
	काष्ठा omap2_mcspi *mcspi = spi_master_get_devdata(spi->master);
	u32 l;

	/* The controller handles the inverted chip selects
	 * using the OMAP2_MCSPI_CHCONF_EPOL bit so revert
	 * the inversion from the core spi_set_cs function.
	 */
	अगर (spi->mode & SPI_CS_HIGH)
		enable = !enable;

	अगर (spi->controller_state) अणु
		पूर्णांक err = pm_runसमय_get_sync(mcspi->dev);
		अगर (err < 0) अणु
			pm_runसमय_put_noidle(mcspi->dev);
			dev_err(mcspi->dev, "failed to get sync: %d\n", err);
			वापस;
		पूर्ण

		l = mcspi_cached_chconf0(spi);

		अगर (enable)
			l &= ~OMAP2_MCSPI_CHCONF_FORCE;
		अन्यथा
			l |= OMAP2_MCSPI_CHCONF_FORCE;

		mcspi_ग_लिखो_chconf0(spi, l);

		pm_runसमय_mark_last_busy(mcspi->dev);
		pm_runसमय_put_स्वतःsuspend(mcspi->dev);
	पूर्ण
पूर्ण

अटल व्योम omap2_mcspi_set_mode(काष्ठा spi_master *master)
अणु
	काष्ठा omap2_mcspi	*mcspi = spi_master_get_devdata(master);
	काष्ठा omap2_mcspi_regs	*ctx = &mcspi->ctx;
	u32 l;

	/*
	 * Choose master or slave mode
	 */
	l = mcspi_पढ़ो_reg(master, OMAP2_MCSPI_MODULCTRL);
	l &= ~(OMAP2_MCSPI_MODULCTRL_STEST);
	अगर (spi_controller_is_slave(master)) अणु
		l |= (OMAP2_MCSPI_MODULCTRL_MS);
	पूर्ण अन्यथा अणु
		l &= ~(OMAP2_MCSPI_MODULCTRL_MS);
		l |= OMAP2_MCSPI_MODULCTRL_SINGLE;
	पूर्ण
	mcspi_ग_लिखो_reg(master, OMAP2_MCSPI_MODULCTRL, l);

	ctx->modulctrl = l;
पूर्ण

अटल व्योम omap2_mcspi_set_fअगरo(स्थिर काष्ठा spi_device *spi,
				काष्ठा spi_transfer *t, पूर्णांक enable)
अणु
	काष्ठा spi_master *master = spi->master;
	काष्ठा omap2_mcspi_cs *cs = spi->controller_state;
	काष्ठा omap2_mcspi *mcspi;
	अचिन्हित पूर्णांक wcnt;
	पूर्णांक max_fअगरo_depth, bytes_per_word;
	u32 chconf, xferlevel;

	mcspi = spi_master_get_devdata(master);

	chconf = mcspi_cached_chconf0(spi);
	अगर (enable) अणु
		bytes_per_word = mcspi_bytes_per_word(cs->word_len);
		अगर (t->len % bytes_per_word != 0)
			जाओ disable_fअगरo;

		अगर (t->rx_buf != शून्य && t->tx_buf != शून्य)
			max_fअगरo_depth = OMAP2_MCSPI_MAX_FIFODEPTH / 2;
		अन्यथा
			max_fअगरo_depth = OMAP2_MCSPI_MAX_FIFODEPTH;

		wcnt = t->len / bytes_per_word;
		अगर (wcnt > OMAP2_MCSPI_MAX_FIFOWCNT)
			जाओ disable_fअगरo;

		xferlevel = wcnt << 16;
		अगर (t->rx_buf != शून्य) अणु
			chconf |= OMAP2_MCSPI_CHCONF_FFER;
			xferlevel |= (bytes_per_word - 1) << 8;
		पूर्ण

		अगर (t->tx_buf != शून्य) अणु
			chconf |= OMAP2_MCSPI_CHCONF_FFET;
			xferlevel |= bytes_per_word - 1;
		पूर्ण

		mcspi_ग_लिखो_reg(master, OMAP2_MCSPI_XFERLEVEL, xferlevel);
		mcspi_ग_लिखो_chconf0(spi, chconf);
		mcspi->fअगरo_depth = max_fअगरo_depth;

		वापस;
	पूर्ण

disable_fअगरo:
	अगर (t->rx_buf != शून्य)
		chconf &= ~OMAP2_MCSPI_CHCONF_FFER;

	अगर (t->tx_buf != शून्य)
		chconf &= ~OMAP2_MCSPI_CHCONF_FFET;

	mcspi_ग_लिखो_chconf0(spi, chconf);
	mcspi->fअगरo_depth = 0;
पूर्ण

अटल पूर्णांक mcspi_रुको_क्रम_reg_bit(व्योम __iomem *reg, अचिन्हित दीर्घ bit)
अणु
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + msecs_to_jअगरfies(1000);
	जबतक (!(पढ़ोl_relaxed(reg) & bit)) अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			अगर (!(पढ़ोl_relaxed(reg) & bit))
				वापस -ETIMEDOUT;
			अन्यथा
				वापस 0;
		पूर्ण
		cpu_relax();
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mcspi_रुको_क्रम_completion(काष्ठा  omap2_mcspi *mcspi,
				     काष्ठा completion *x)
अणु
	अगर (spi_controller_is_slave(mcspi->master)) अणु
		अगर (रुको_क्रम_completion_पूर्णांकerruptible(x) ||
		    mcspi->slave_पातed)
			वापस -EINTR;
	पूर्ण अन्यथा अणु
		रुको_क्रम_completion(x);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम omap2_mcspi_rx_callback(व्योम *data)
अणु
	काष्ठा spi_device *spi = data;
	काष्ठा omap2_mcspi *mcspi = spi_master_get_devdata(spi->master);
	काष्ठा omap2_mcspi_dma *mcspi_dma = &mcspi->dma_channels[spi->chip_select];

	/* We must disable the DMA RX request */
	omap2_mcspi_set_dma_req(spi, 1, 0);

	complete(&mcspi_dma->dma_rx_completion);
पूर्ण

अटल व्योम omap2_mcspi_tx_callback(व्योम *data)
अणु
	काष्ठा spi_device *spi = data;
	काष्ठा omap2_mcspi *mcspi = spi_master_get_devdata(spi->master);
	काष्ठा omap2_mcspi_dma *mcspi_dma = &mcspi->dma_channels[spi->chip_select];

	/* We must disable the DMA TX request */
	omap2_mcspi_set_dma_req(spi, 0, 0);

	complete(&mcspi_dma->dma_tx_completion);
पूर्ण

अटल व्योम omap2_mcspi_tx_dma(काष्ठा spi_device *spi,
				काष्ठा spi_transfer *xfer,
				काष्ठा dma_slave_config cfg)
अणु
	काष्ठा omap2_mcspi	*mcspi;
	काष्ठा omap2_mcspi_dma  *mcspi_dma;
	काष्ठा dma_async_tx_descriptor *tx;

	mcspi = spi_master_get_devdata(spi->master);
	mcspi_dma = &mcspi->dma_channels[spi->chip_select];

	dmaengine_slave_config(mcspi_dma->dma_tx, &cfg);

	tx = dmaengine_prep_slave_sg(mcspi_dma->dma_tx, xfer->tx_sg.sgl,
				     xfer->tx_sg.nents,
				     DMA_MEM_TO_DEV,
				     DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (tx) अणु
		tx->callback = omap2_mcspi_tx_callback;
		tx->callback_param = spi;
		dmaengine_submit(tx);
	पूर्ण अन्यथा अणु
		/* FIXME: fall back to PIO? */
	पूर्ण
	dma_async_issue_pending(mcspi_dma->dma_tx);
	omap2_mcspi_set_dma_req(spi, 0, 1);
पूर्ण

अटल अचिन्हित
omap2_mcspi_rx_dma(काष्ठा spi_device *spi, काष्ठा spi_transfer *xfer,
				काष्ठा dma_slave_config cfg,
				अचिन्हित es)
अणु
	काष्ठा omap2_mcspi	*mcspi;
	काष्ठा omap2_mcspi_dma  *mcspi_dma;
	अचिन्हित पूर्णांक		count, transfer_reduction = 0;
	काष्ठा scatterlist	*sg_out[2];
	पूर्णांक			nb_sizes = 0, out_mapped_nents[2], ret, x;
	माप_प्रकार			sizes[2];
	u32			l;
	पूर्णांक			elements = 0;
	पूर्णांक			word_len, element_count;
	काष्ठा omap2_mcspi_cs	*cs = spi->controller_state;
	व्योम __iomem		*chstat_reg = cs->base + OMAP2_MCSPI_CHSTAT0;
	काष्ठा dma_async_tx_descriptor *tx;

	mcspi = spi_master_get_devdata(spi->master);
	mcspi_dma = &mcspi->dma_channels[spi->chip_select];
	count = xfer->len;

	/*
	 *  In the "End-of-Transfer Procedure" section क्रम DMA RX in OMAP35x TRM
	 *  it mentions reducing DMA transfer length by one element in master
	 *  normal mode.
	 */
	अगर (mcspi->fअगरo_depth == 0)
		transfer_reduction = es;

	word_len = cs->word_len;
	l = mcspi_cached_chconf0(spi);

	अगर (word_len <= 8)
		element_count = count;
	अन्यथा अगर (word_len <= 16)
		element_count = count >> 1;
	अन्यथा /* word_len <= 32 */
		element_count = count >> 2;


	dmaengine_slave_config(mcspi_dma->dma_rx, &cfg);

	/*
	 *  Reduce DMA transfer length by one more अगर McSPI is
	 *  configured in turbo mode.
	 */
	अगर ((l & OMAP2_MCSPI_CHCONF_TURBO) && mcspi->fअगरo_depth == 0)
		transfer_reduction += es;

	अगर (transfer_reduction) अणु
		/* Split sgl पूर्णांकo two. The second sgl won't be used. */
		sizes[0] = count - transfer_reduction;
		sizes[1] = transfer_reduction;
		nb_sizes = 2;
	पूर्ण अन्यथा अणु
		/*
		 * Don't bother splitting the sgl. This essentially
		 * clones the original sgl.
		 */
		sizes[0] = count;
		nb_sizes = 1;
	पूर्ण

	ret = sg_split(xfer->rx_sg.sgl, xfer->rx_sg.nents, 0, nb_sizes,
		       sizes, sg_out, out_mapped_nents, GFP_KERNEL);

	अगर (ret < 0) अणु
		dev_err(&spi->dev, "sg_split failed\n");
		वापस 0;
	पूर्ण

	tx = dmaengine_prep_slave_sg(mcspi_dma->dma_rx, sg_out[0],
				     out_mapped_nents[0], DMA_DEV_TO_MEM,
				     DMA_PREP_INTERRUPT | DMA_CTRL_ACK);
	अगर (tx) अणु
		tx->callback = omap2_mcspi_rx_callback;
		tx->callback_param = spi;
		dmaengine_submit(tx);
	पूर्ण अन्यथा अणु
		/* FIXME: fall back to PIO? */
	पूर्ण

	dma_async_issue_pending(mcspi_dma->dma_rx);
	omap2_mcspi_set_dma_req(spi, 1, 1);

	ret = mcspi_रुको_क्रम_completion(mcspi, &mcspi_dma->dma_rx_completion);
	अगर (ret || mcspi->slave_पातed) अणु
		dmaengine_terminate_sync(mcspi_dma->dma_rx);
		omap2_mcspi_set_dma_req(spi, 1, 0);
		वापस 0;
	पूर्ण

	क्रम (x = 0; x < nb_sizes; x++)
		kमुक्त(sg_out[x]);

	अगर (mcspi->fअगरo_depth > 0)
		वापस count;

	/*
	 *  Due to the DMA transfer length reduction the missing bytes must
	 *  be पढ़ो manually to receive all of the expected data.
	 */
	omap2_mcspi_set_enable(spi, 0);

	elements = element_count - 1;

	अगर (l & OMAP2_MCSPI_CHCONF_TURBO) अणु
		elements--;

		अगर (!mcspi_रुको_क्रम_reg_bit(chstat_reg,
					    OMAP2_MCSPI_CHSTAT_RXS)) अणु
			u32 w;

			w = mcspi_पढ़ो_cs_reg(spi, OMAP2_MCSPI_RX0);
			अगर (word_len <= 8)
				((u8 *)xfer->rx_buf)[elements++] = w;
			अन्यथा अगर (word_len <= 16)
				((u16 *)xfer->rx_buf)[elements++] = w;
			अन्यथा /* word_len <= 32 */
				((u32 *)xfer->rx_buf)[elements++] = w;
		पूर्ण अन्यथा अणु
			पूर्णांक bytes_per_word = mcspi_bytes_per_word(word_len);
			dev_err(&spi->dev, "DMA RX penultimate word empty\n");
			count -= (bytes_per_word << 1);
			omap2_mcspi_set_enable(spi, 1);
			वापस count;
		पूर्ण
	पूर्ण
	अगर (!mcspi_रुको_क्रम_reg_bit(chstat_reg, OMAP2_MCSPI_CHSTAT_RXS)) अणु
		u32 w;

		w = mcspi_पढ़ो_cs_reg(spi, OMAP2_MCSPI_RX0);
		अगर (word_len <= 8)
			((u8 *)xfer->rx_buf)[elements] = w;
		अन्यथा अगर (word_len <= 16)
			((u16 *)xfer->rx_buf)[elements] = w;
		अन्यथा /* word_len <= 32 */
			((u32 *)xfer->rx_buf)[elements] = w;
	पूर्ण अन्यथा अणु
		dev_err(&spi->dev, "DMA RX last word empty\n");
		count -= mcspi_bytes_per_word(word_len);
	पूर्ण
	omap2_mcspi_set_enable(spi, 1);
	वापस count;
पूर्ण

अटल अचिन्हित
omap2_mcspi_txrx_dma(काष्ठा spi_device *spi, काष्ठा spi_transfer *xfer)
अणु
	काष्ठा omap2_mcspi	*mcspi;
	काष्ठा omap2_mcspi_cs	*cs = spi->controller_state;
	काष्ठा omap2_mcspi_dma  *mcspi_dma;
	अचिन्हित पूर्णांक		count;
	u8			*rx;
	स्थिर u8		*tx;
	काष्ठा dma_slave_config	cfg;
	क्रमागत dma_slave_buswidth width;
	अचिन्हित es;
	व्योम __iomem		*chstat_reg;
	व्योम __iomem            *irqstat_reg;
	पूर्णांक			रुको_res;

	mcspi = spi_master_get_devdata(spi->master);
	mcspi_dma = &mcspi->dma_channels[spi->chip_select];

	अगर (cs->word_len <= 8) अणु
		width = DMA_SLAVE_BUSWIDTH_1_BYTE;
		es = 1;
	पूर्ण अन्यथा अगर (cs->word_len <= 16) अणु
		width = DMA_SLAVE_BUSWIDTH_2_BYTES;
		es = 2;
	पूर्ण अन्यथा अणु
		width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		es = 4;
	पूर्ण

	count = xfer->len;

	स_रखो(&cfg, 0, माप(cfg));
	cfg.src_addr = cs->phys + OMAP2_MCSPI_RX0;
	cfg.dst_addr = cs->phys + OMAP2_MCSPI_TX0;
	cfg.src_addr_width = width;
	cfg.dst_addr_width = width;
	cfg.src_maxburst = 1;
	cfg.dst_maxburst = 1;

	rx = xfer->rx_buf;
	tx = xfer->tx_buf;

	mcspi->slave_पातed = false;
	reinit_completion(&mcspi_dma->dma_tx_completion);
	reinit_completion(&mcspi_dma->dma_rx_completion);
	reinit_completion(&mcspi->txकरोne);
	अगर (tx) अणु
		/* Enable EOW IRQ to know end of tx in slave mode */
		अगर (spi_controller_is_slave(spi->master))
			mcspi_ग_लिखो_reg(spi->master,
					OMAP2_MCSPI_IRQENABLE,
					OMAP2_MCSPI_IRQSTATUS_EOW);
		omap2_mcspi_tx_dma(spi, xfer, cfg);
	पूर्ण

	अगर (rx != शून्य)
		count = omap2_mcspi_rx_dma(spi, xfer, cfg, es);

	अगर (tx != शून्य) अणु
		पूर्णांक ret;

		ret = mcspi_रुको_क्रम_completion(mcspi, &mcspi_dma->dma_tx_completion);
		अगर (ret || mcspi->slave_पातed) अणु
			dmaengine_terminate_sync(mcspi_dma->dma_tx);
			omap2_mcspi_set_dma_req(spi, 0, 0);
			वापस 0;
		पूर्ण

		अगर (spi_controller_is_slave(mcspi->master)) अणु
			ret = mcspi_रुको_क्रम_completion(mcspi, &mcspi->txकरोne);
			अगर (ret || mcspi->slave_पातed)
				वापस 0;
		पूर्ण

		अगर (mcspi->fअगरo_depth > 0) अणु
			irqstat_reg = mcspi->base + OMAP2_MCSPI_IRQSTATUS;

			अगर (mcspi_रुको_क्रम_reg_bit(irqstat_reg,
						OMAP2_MCSPI_IRQSTATUS_EOW) < 0)
				dev_err(&spi->dev, "EOW timed out\n");

			mcspi_ग_लिखो_reg(mcspi->master, OMAP2_MCSPI_IRQSTATUS,
					OMAP2_MCSPI_IRQSTATUS_EOW);
		पूर्ण

		/* क्रम TX_ONLY mode, be sure all words have shअगरted out */
		अगर (rx == शून्य) अणु
			chstat_reg = cs->base + OMAP2_MCSPI_CHSTAT0;
			अगर (mcspi->fअगरo_depth > 0) अणु
				रुको_res = mcspi_रुको_क्रम_reg_bit(chstat_reg,
						OMAP2_MCSPI_CHSTAT_TXFFE);
				अगर (रुको_res < 0)
					dev_err(&spi->dev, "TXFFE timed out\n");
			पूर्ण अन्यथा अणु
				रुको_res = mcspi_रुको_क्रम_reg_bit(chstat_reg,
						OMAP2_MCSPI_CHSTAT_TXS);
				अगर (रुको_res < 0)
					dev_err(&spi->dev, "TXS timed out\n");
			पूर्ण
			अगर (रुको_res >= 0 &&
				(mcspi_रुको_क्रम_reg_bit(chstat_reg,
					OMAP2_MCSPI_CHSTAT_EOT) < 0))
				dev_err(&spi->dev, "EOT timed out\n");
		पूर्ण
	पूर्ण
	वापस count;
पूर्ण

अटल अचिन्हित
omap2_mcspi_txrx_pio(काष्ठा spi_device *spi, काष्ठा spi_transfer *xfer)
अणु
	काष्ठा omap2_mcspi_cs	*cs = spi->controller_state;
	अचिन्हित पूर्णांक		count, c;
	u32			l;
	व्योम __iomem		*base = cs->base;
	व्योम __iomem		*tx_reg;
	व्योम __iomem		*rx_reg;
	व्योम __iomem		*chstat_reg;
	पूर्णांक			word_len;

	count = xfer->len;
	c = count;
	word_len = cs->word_len;

	l = mcspi_cached_chconf0(spi);

	/* We store the pre-calculated रेजिस्टर addresses on stack to speed
	 * up the transfer loop. */
	tx_reg		= base + OMAP2_MCSPI_TX0;
	rx_reg		= base + OMAP2_MCSPI_RX0;
	chstat_reg	= base + OMAP2_MCSPI_CHSTAT0;

	अगर (c < (word_len>>3))
		वापस 0;

	अगर (word_len <= 8) अणु
		u8		*rx;
		स्थिर u8	*tx;

		rx = xfer->rx_buf;
		tx = xfer->tx_buf;

		करो अणु
			c -= 1;
			अगर (tx != शून्य) अणु
				अगर (mcspi_रुको_क्रम_reg_bit(chstat_reg,
						OMAP2_MCSPI_CHSTAT_TXS) < 0) अणु
					dev_err(&spi->dev, "TXS timed out\n");
					जाओ out;
				पूर्ण
				dev_vdbg(&spi->dev, "write-%d %02x\n",
						word_len, *tx);
				ग_लिखोl_relaxed(*tx++, tx_reg);
			पूर्ण
			अगर (rx != शून्य) अणु
				अगर (mcspi_रुको_क्रम_reg_bit(chstat_reg,
						OMAP2_MCSPI_CHSTAT_RXS) < 0) अणु
					dev_err(&spi->dev, "RXS timed out\n");
					जाओ out;
				पूर्ण

				अगर (c == 1 && tx == शून्य &&
				    (l & OMAP2_MCSPI_CHCONF_TURBO)) अणु
					omap2_mcspi_set_enable(spi, 0);
					*rx++ = पढ़ोl_relaxed(rx_reg);
					dev_vdbg(&spi->dev, "read-%d %02x\n",
						    word_len, *(rx - 1));
					अगर (mcspi_रुको_क्रम_reg_bit(chstat_reg,
						OMAP2_MCSPI_CHSTAT_RXS) < 0) अणु
						dev_err(&spi->dev,
							"RXS timed out\n");
						जाओ out;
					पूर्ण
					c = 0;
				पूर्ण अन्यथा अगर (c == 0 && tx == शून्य) अणु
					omap2_mcspi_set_enable(spi, 0);
				पूर्ण

				*rx++ = पढ़ोl_relaxed(rx_reg);
				dev_vdbg(&spi->dev, "read-%d %02x\n",
						word_len, *(rx - 1));
			पूर्ण
		पूर्ण जबतक (c);
	पूर्ण अन्यथा अगर (word_len <= 16) अणु
		u16		*rx;
		स्थिर u16	*tx;

		rx = xfer->rx_buf;
		tx = xfer->tx_buf;
		करो अणु
			c -= 2;
			अगर (tx != शून्य) अणु
				अगर (mcspi_रुको_क्रम_reg_bit(chstat_reg,
						OMAP2_MCSPI_CHSTAT_TXS) < 0) अणु
					dev_err(&spi->dev, "TXS timed out\n");
					जाओ out;
				पूर्ण
				dev_vdbg(&spi->dev, "write-%d %04x\n",
						word_len, *tx);
				ग_लिखोl_relaxed(*tx++, tx_reg);
			पूर्ण
			अगर (rx != शून्य) अणु
				अगर (mcspi_रुको_क्रम_reg_bit(chstat_reg,
						OMAP2_MCSPI_CHSTAT_RXS) < 0) अणु
					dev_err(&spi->dev, "RXS timed out\n");
					जाओ out;
				पूर्ण

				अगर (c == 2 && tx == शून्य &&
				    (l & OMAP2_MCSPI_CHCONF_TURBO)) अणु
					omap2_mcspi_set_enable(spi, 0);
					*rx++ = पढ़ोl_relaxed(rx_reg);
					dev_vdbg(&spi->dev, "read-%d %04x\n",
						    word_len, *(rx - 1));
					अगर (mcspi_रुको_क्रम_reg_bit(chstat_reg,
						OMAP2_MCSPI_CHSTAT_RXS) < 0) अणु
						dev_err(&spi->dev,
							"RXS timed out\n");
						जाओ out;
					पूर्ण
					c = 0;
				पूर्ण अन्यथा अगर (c == 0 && tx == शून्य) अणु
					omap2_mcspi_set_enable(spi, 0);
				पूर्ण

				*rx++ = पढ़ोl_relaxed(rx_reg);
				dev_vdbg(&spi->dev, "read-%d %04x\n",
						word_len, *(rx - 1));
			पूर्ण
		पूर्ण जबतक (c >= 2);
	पूर्ण अन्यथा अगर (word_len <= 32) अणु
		u32		*rx;
		स्थिर u32	*tx;

		rx = xfer->rx_buf;
		tx = xfer->tx_buf;
		करो अणु
			c -= 4;
			अगर (tx != शून्य) अणु
				अगर (mcspi_रुको_क्रम_reg_bit(chstat_reg,
						OMAP2_MCSPI_CHSTAT_TXS) < 0) अणु
					dev_err(&spi->dev, "TXS timed out\n");
					जाओ out;
				पूर्ण
				dev_vdbg(&spi->dev, "write-%d %08x\n",
						word_len, *tx);
				ग_लिखोl_relaxed(*tx++, tx_reg);
			पूर्ण
			अगर (rx != शून्य) अणु
				अगर (mcspi_रुको_क्रम_reg_bit(chstat_reg,
						OMAP2_MCSPI_CHSTAT_RXS) < 0) अणु
					dev_err(&spi->dev, "RXS timed out\n");
					जाओ out;
				पूर्ण

				अगर (c == 4 && tx == शून्य &&
				    (l & OMAP2_MCSPI_CHCONF_TURBO)) अणु
					omap2_mcspi_set_enable(spi, 0);
					*rx++ = पढ़ोl_relaxed(rx_reg);
					dev_vdbg(&spi->dev, "read-%d %08x\n",
						    word_len, *(rx - 1));
					अगर (mcspi_रुको_क्रम_reg_bit(chstat_reg,
						OMAP2_MCSPI_CHSTAT_RXS) < 0) अणु
						dev_err(&spi->dev,
							"RXS timed out\n");
						जाओ out;
					पूर्ण
					c = 0;
				पूर्ण अन्यथा अगर (c == 0 && tx == शून्य) अणु
					omap2_mcspi_set_enable(spi, 0);
				पूर्ण

				*rx++ = पढ़ोl_relaxed(rx_reg);
				dev_vdbg(&spi->dev, "read-%d %08x\n",
						word_len, *(rx - 1));
			पूर्ण
		पूर्ण जबतक (c >= 4);
	पूर्ण

	/* क्रम TX_ONLY mode, be sure all words have shअगरted out */
	अगर (xfer->rx_buf == शून्य) अणु
		अगर (mcspi_रुको_क्रम_reg_bit(chstat_reg,
				OMAP2_MCSPI_CHSTAT_TXS) < 0) अणु
			dev_err(&spi->dev, "TXS timed out\n");
		पूर्ण अन्यथा अगर (mcspi_रुको_क्रम_reg_bit(chstat_reg,
				OMAP2_MCSPI_CHSTAT_EOT) < 0)
			dev_err(&spi->dev, "EOT timed out\n");

		/* disable chan to purge rx datas received in TX_ONLY transfer,
		 * otherwise these rx datas will affect the direct following
		 * RX_ONLY transfer.
		 */
		omap2_mcspi_set_enable(spi, 0);
	पूर्ण
out:
	omap2_mcspi_set_enable(spi, 1);
	वापस count - c;
पूर्ण

अटल u32 omap2_mcspi_calc_भागisor(u32 speed_hz)
अणु
	u32 भाग;

	क्रम (भाग = 0; भाग < 15; भाग++)
		अगर (speed_hz >= (OMAP2_MCSPI_MAX_FREQ >> भाग))
			वापस भाग;

	वापस 15;
पूर्ण

/* called only when no transfer is active to this device */
अटल पूर्णांक omap2_mcspi_setup_transfer(काष्ठा spi_device *spi,
		काष्ठा spi_transfer *t)
अणु
	काष्ठा omap2_mcspi_cs *cs = spi->controller_state;
	काष्ठा omap2_mcspi *mcspi;
	u32 l = 0, clkd = 0, भाग, extclk = 0, clkg = 0;
	u8 word_len = spi->bits_per_word;
	u32 speed_hz = spi->max_speed_hz;

	mcspi = spi_master_get_devdata(spi->master);

	अगर (t != शून्य && t->bits_per_word)
		word_len = t->bits_per_word;

	cs->word_len = word_len;

	अगर (t && t->speed_hz)
		speed_hz = t->speed_hz;

	speed_hz = min_t(u32, speed_hz, OMAP2_MCSPI_MAX_FREQ);
	अगर (speed_hz < (OMAP2_MCSPI_MAX_FREQ / OMAP2_MCSPI_MAX_DIVIDER)) अणु
		clkd = omap2_mcspi_calc_भागisor(speed_hz);
		speed_hz = OMAP2_MCSPI_MAX_FREQ >> clkd;
		clkg = 0;
	पूर्ण अन्यथा अणु
		भाग = (OMAP2_MCSPI_MAX_FREQ + speed_hz - 1) / speed_hz;
		speed_hz = OMAP2_MCSPI_MAX_FREQ / भाग;
		clkd = (भाग - 1) & 0xf;
		extclk = (भाग - 1) >> 4;
		clkg = OMAP2_MCSPI_CHCONF_CLKG;
	पूर्ण

	l = mcspi_cached_chconf0(spi);

	/* standard 4-wire master mode:  SCK, MOSI/out, MISO/in, nCS
	 * REVISIT: this controller could support SPI_3WIRE mode.
	 */
	अगर (mcspi->pin_dir == MCSPI_PINसूची_D0_IN_D1_OUT) अणु
		l &= ~OMAP2_MCSPI_CHCONF_IS;
		l &= ~OMAP2_MCSPI_CHCONF_DPE1;
		l |= OMAP2_MCSPI_CHCONF_DPE0;
	पूर्ण अन्यथा अणु
		l |= OMAP2_MCSPI_CHCONF_IS;
		l |= OMAP2_MCSPI_CHCONF_DPE1;
		l &= ~OMAP2_MCSPI_CHCONF_DPE0;
	पूर्ण

	/* wordlength */
	l &= ~OMAP2_MCSPI_CHCONF_WL_MASK;
	l |= (word_len - 1) << 7;

	/* set chipselect polarity; manage with FORCE */
	अगर (!(spi->mode & SPI_CS_HIGH))
		l |= OMAP2_MCSPI_CHCONF_EPOL;	/* active-low; normal */
	अन्यथा
		l &= ~OMAP2_MCSPI_CHCONF_EPOL;

	/* set घड़ी भागisor */
	l &= ~OMAP2_MCSPI_CHCONF_CLKD_MASK;
	l |= clkd << 2;

	/* set घड़ी granularity */
	l &= ~OMAP2_MCSPI_CHCONF_CLKG;
	l |= clkg;
	अगर (clkg) अणु
		cs->chctrl0 &= ~OMAP2_MCSPI_CHCTRL_EXTCLK_MASK;
		cs->chctrl0 |= extclk << 8;
		mcspi_ग_लिखो_cs_reg(spi, OMAP2_MCSPI_CHCTRL0, cs->chctrl0);
	पूर्ण

	/* set SPI mode 0..3 */
	अगर (spi->mode & SPI_CPOL)
		l |= OMAP2_MCSPI_CHCONF_POL;
	अन्यथा
		l &= ~OMAP2_MCSPI_CHCONF_POL;
	अगर (spi->mode & SPI_CPHA)
		l |= OMAP2_MCSPI_CHCONF_PHA;
	अन्यथा
		l &= ~OMAP2_MCSPI_CHCONF_PHA;

	mcspi_ग_लिखो_chconf0(spi, l);

	cs->mode = spi->mode;

	dev_dbg(&spi->dev, "setup: speed %d, sample %s edge, clk %s\n",
			speed_hz,
			(spi->mode & SPI_CPHA) ? "trailing" : "leading",
			(spi->mode & SPI_CPOL) ? "inverted" : "normal");

	वापस 0;
पूर्ण

/*
 * Note that we currently allow DMA only अगर we get a channel
 * क्रम both rx and tx. Otherwise we'll करो PIO क्रम both rx and tx.
 */
अटल पूर्णांक omap2_mcspi_request_dma(काष्ठा omap2_mcspi *mcspi,
				   काष्ठा omap2_mcspi_dma *mcspi_dma)
अणु
	पूर्णांक ret = 0;

	mcspi_dma->dma_rx = dma_request_chan(mcspi->dev,
					     mcspi_dma->dma_rx_ch_name);
	अगर (IS_ERR(mcspi_dma->dma_rx)) अणु
		ret = PTR_ERR(mcspi_dma->dma_rx);
		mcspi_dma->dma_rx = शून्य;
		जाओ no_dma;
	पूर्ण

	mcspi_dma->dma_tx = dma_request_chan(mcspi->dev,
					     mcspi_dma->dma_tx_ch_name);
	अगर (IS_ERR(mcspi_dma->dma_tx)) अणु
		ret = PTR_ERR(mcspi_dma->dma_tx);
		mcspi_dma->dma_tx = शून्य;
		dma_release_channel(mcspi_dma->dma_rx);
		mcspi_dma->dma_rx = शून्य;
	पूर्ण

	init_completion(&mcspi_dma->dma_rx_completion);
	init_completion(&mcspi_dma->dma_tx_completion);

no_dma:
	वापस ret;
पूर्ण

अटल व्योम omap2_mcspi_release_dma(काष्ठा spi_master *master)
अणु
	काष्ठा omap2_mcspi *mcspi = spi_master_get_devdata(master);
	काष्ठा omap2_mcspi_dma	*mcspi_dma;
	पूर्णांक i;

	क्रम (i = 0; i < master->num_chipselect; i++) अणु
		mcspi_dma = &mcspi->dma_channels[i];

		अगर (mcspi_dma->dma_rx) अणु
			dma_release_channel(mcspi_dma->dma_rx);
			mcspi_dma->dma_rx = शून्य;
		पूर्ण
		अगर (mcspi_dma->dma_tx) अणु
			dma_release_channel(mcspi_dma->dma_tx);
			mcspi_dma->dma_tx = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम omap2_mcspi_cleanup(काष्ठा spi_device *spi)
अणु
	काष्ठा omap2_mcspi_cs	*cs;

	अगर (spi->controller_state) अणु
		/* Unlink controller state from context save list */
		cs = spi->controller_state;
		list_del(&cs->node);

		kमुक्त(cs);
	पूर्ण
पूर्ण

अटल पूर्णांक omap2_mcspi_setup(काष्ठा spi_device *spi)
अणु
	bool			initial_setup = false;
	पूर्णांक			ret;
	काष्ठा omap2_mcspi	*mcspi = spi_master_get_devdata(spi->master);
	काष्ठा omap2_mcspi_regs	*ctx = &mcspi->ctx;
	काष्ठा omap2_mcspi_cs	*cs = spi->controller_state;

	अगर (!cs) अणु
		cs = kzalloc(माप *cs, GFP_KERNEL);
		अगर (!cs)
			वापस -ENOMEM;
		cs->base = mcspi->base + spi->chip_select * 0x14;
		cs->phys = mcspi->phys + spi->chip_select * 0x14;
		cs->mode = 0;
		cs->chconf0 = 0;
		cs->chctrl0 = 0;
		spi->controller_state = cs;
		/* Link this to context save list */
		list_add_tail(&cs->node, &ctx->cs);
		initial_setup = true;
	पूर्ण

	ret = pm_runसमय_get_sync(mcspi->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(mcspi->dev);
		अगर (initial_setup)
			omap2_mcspi_cleanup(spi);

		वापस ret;
	पूर्ण

	ret = omap2_mcspi_setup_transfer(spi, शून्य);
	अगर (ret && initial_setup)
		omap2_mcspi_cleanup(spi);

	pm_runसमय_mark_last_busy(mcspi->dev);
	pm_runसमय_put_स्वतःsuspend(mcspi->dev);

	वापस ret;
पूर्ण

अटल irqवापस_t omap2_mcspi_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा omap2_mcspi *mcspi = data;
	u32 irqstat;

	irqstat	= mcspi_पढ़ो_reg(mcspi->master, OMAP2_MCSPI_IRQSTATUS);
	अगर (!irqstat)
		वापस IRQ_NONE;

	/* Disable IRQ and wakeup slave xfer task */
	mcspi_ग_लिखो_reg(mcspi->master, OMAP2_MCSPI_IRQENABLE, 0);
	अगर (irqstat & OMAP2_MCSPI_IRQSTATUS_EOW)
		complete(&mcspi->txकरोne);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक omap2_mcspi_slave_पात(काष्ठा spi_master *master)
अणु
	काष्ठा omap2_mcspi *mcspi = spi_master_get_devdata(master);
	काष्ठा omap2_mcspi_dma *mcspi_dma = mcspi->dma_channels;

	mcspi->slave_पातed = true;
	complete(&mcspi_dma->dma_rx_completion);
	complete(&mcspi_dma->dma_tx_completion);
	complete(&mcspi->txकरोne);

	वापस 0;
पूर्ण

अटल पूर्णांक omap2_mcspi_transfer_one(काष्ठा spi_master *master,
				    काष्ठा spi_device *spi,
				    काष्ठा spi_transfer *t)
अणु

	/* We only enable one channel at a समय -- the one whose message is
	 * -- although this controller would gladly
	 * arbitrate among multiple channels.  This corresponds to "single
	 * channel" master mode.  As a side effect, we need to manage the
	 * chipselect with the FORCE bit ... CS != channel enable.
	 */

	काष्ठा omap2_mcspi		*mcspi;
	काष्ठा omap2_mcspi_dma		*mcspi_dma;
	काष्ठा omap2_mcspi_cs		*cs;
	काष्ठा omap2_mcspi_device_config *cd;
	पूर्णांक				par_override = 0;
	पूर्णांक				status = 0;
	u32				chconf;

	mcspi = spi_master_get_devdata(master);
	mcspi_dma = mcspi->dma_channels + spi->chip_select;
	cs = spi->controller_state;
	cd = spi->controller_data;

	/*
	 * The slave driver could have changed spi->mode in which हाल
	 * it will be dअगरferent from cs->mode (the current hardware setup).
	 * If so, set par_override (even though its not a parity issue) so
	 * omap2_mcspi_setup_transfer will be called to configure the hardware
	 * with the correct mode on the first iteration of the loop below.
	 */
	अगर (spi->mode != cs->mode)
		par_override = 1;

	omap2_mcspi_set_enable(spi, 0);

	अगर (spi->cs_gpiod)
		omap2_mcspi_set_cs(spi, spi->mode & SPI_CS_HIGH);

	अगर (par_override ||
	    (t->speed_hz != spi->max_speed_hz) ||
	    (t->bits_per_word != spi->bits_per_word)) अणु
		par_override = 1;
		status = omap2_mcspi_setup_transfer(spi, t);
		अगर (status < 0)
			जाओ out;
		अगर (t->speed_hz == spi->max_speed_hz &&
		    t->bits_per_word == spi->bits_per_word)
			par_override = 0;
	पूर्ण
	अगर (cd && cd->cs_per_word) अणु
		chconf = mcspi->ctx.modulctrl;
		chconf &= ~OMAP2_MCSPI_MODULCTRL_SINGLE;
		mcspi_ग_लिखो_reg(master, OMAP2_MCSPI_MODULCTRL, chconf);
		mcspi->ctx.modulctrl =
			mcspi_पढ़ो_cs_reg(spi, OMAP2_MCSPI_MODULCTRL);
	पूर्ण

	chconf = mcspi_cached_chconf0(spi);
	chconf &= ~OMAP2_MCSPI_CHCONF_TRM_MASK;
	chconf &= ~OMAP2_MCSPI_CHCONF_TURBO;

	अगर (t->tx_buf == शून्य)
		chconf |= OMAP2_MCSPI_CHCONF_TRM_RX_ONLY;
	अन्यथा अगर (t->rx_buf == शून्य)
		chconf |= OMAP2_MCSPI_CHCONF_TRM_TX_ONLY;

	अगर (cd && cd->turbo_mode && t->tx_buf == शून्य) अणु
		/* Turbo mode is क्रम more than one word */
		अगर (t->len > ((cs->word_len + 7) >> 3))
			chconf |= OMAP2_MCSPI_CHCONF_TURBO;
	पूर्ण

	mcspi_ग_लिखो_chconf0(spi, chconf);

	अगर (t->len) अणु
		अचिन्हित	count;

		अगर ((mcspi_dma->dma_rx && mcspi_dma->dma_tx) &&
		    master->cur_msg_mapped &&
		    master->can_dma(master, spi, t))
			omap2_mcspi_set_fअगरo(spi, t, 1);

		omap2_mcspi_set_enable(spi, 1);

		/* RX_ONLY mode needs dummy data in TX reg */
		अगर (t->tx_buf == शून्य)
			ग_लिखोl_relaxed(0, cs->base
					+ OMAP2_MCSPI_TX0);

		अगर ((mcspi_dma->dma_rx && mcspi_dma->dma_tx) &&
		    master->cur_msg_mapped &&
		    master->can_dma(master, spi, t))
			count = omap2_mcspi_txrx_dma(spi, t);
		अन्यथा
			count = omap2_mcspi_txrx_pio(spi, t);

		अगर (count != t->len) अणु
			status = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण

	omap2_mcspi_set_enable(spi, 0);

	अगर (mcspi->fअगरo_depth > 0)
		omap2_mcspi_set_fअगरo(spi, t, 0);

out:
	/* Restore शेषs अगर they were overriden */
	अगर (par_override) अणु
		par_override = 0;
		status = omap2_mcspi_setup_transfer(spi, शून्य);
	पूर्ण

	अगर (cd && cd->cs_per_word) अणु
		chconf = mcspi->ctx.modulctrl;
		chconf |= OMAP2_MCSPI_MODULCTRL_SINGLE;
		mcspi_ग_लिखो_reg(master, OMAP2_MCSPI_MODULCTRL, chconf);
		mcspi->ctx.modulctrl =
			mcspi_पढ़ो_cs_reg(spi, OMAP2_MCSPI_MODULCTRL);
	पूर्ण

	omap2_mcspi_set_enable(spi, 0);

	अगर (spi->cs_gpiod)
		omap2_mcspi_set_cs(spi, !(spi->mode & SPI_CS_HIGH));

	अगर (mcspi->fअगरo_depth > 0 && t)
		omap2_mcspi_set_fअगरo(spi, t, 0);

	वापस status;
पूर्ण

अटल पूर्णांक omap2_mcspi_prepare_message(काष्ठा spi_master *master,
				       काष्ठा spi_message *msg)
अणु
	काष्ठा omap2_mcspi	*mcspi = spi_master_get_devdata(master);
	काष्ठा omap2_mcspi_regs	*ctx = &mcspi->ctx;
	काष्ठा omap2_mcspi_cs	*cs;

	/* Only a single channel can have the FORCE bit enabled
	 * in its chconf0 रेजिस्टर.
	 * Scan all channels and disable them except the current one.
	 * A FORCE can reमुख्य from a last transfer having cs_change enabled
	 */
	list_क्रम_each_entry(cs, &ctx->cs, node) अणु
		अगर (msg->spi->controller_state == cs)
			जारी;

		अगर ((cs->chconf0 & OMAP2_MCSPI_CHCONF_FORCE)) अणु
			cs->chconf0 &= ~OMAP2_MCSPI_CHCONF_FORCE;
			ग_लिखोl_relaxed(cs->chconf0,
					cs->base + OMAP2_MCSPI_CHCONF0);
			पढ़ोl_relaxed(cs->base + OMAP2_MCSPI_CHCONF0);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool omap2_mcspi_can_dma(काष्ठा spi_master *master,
				काष्ठा spi_device *spi,
				काष्ठा spi_transfer *xfer)
अणु
	काष्ठा omap2_mcspi *mcspi = spi_master_get_devdata(spi->master);
	काष्ठा omap2_mcspi_dma *mcspi_dma =
		&mcspi->dma_channels[spi->chip_select];

	अगर (!mcspi_dma->dma_rx || !mcspi_dma->dma_tx)
		वापस false;

	अगर (spi_controller_is_slave(master))
		वापस true;

	master->dma_rx = mcspi_dma->dma_rx;
	master->dma_tx = mcspi_dma->dma_tx;

	वापस (xfer->len >= DMA_MIN_BYTES);
पूर्ण

अटल माप_प्रकार omap2_mcspi_max_xfer_size(काष्ठा spi_device *spi)
अणु
	काष्ठा omap2_mcspi *mcspi = spi_master_get_devdata(spi->master);
	काष्ठा omap2_mcspi_dma *mcspi_dma =
		&mcspi->dma_channels[spi->chip_select];

	अगर (mcspi->max_xfer_len && mcspi_dma->dma_rx)
		वापस mcspi->max_xfer_len;

	वापस SIZE_MAX;
पूर्ण

अटल पूर्णांक omap2_mcspi_controller_setup(काष्ठा omap2_mcspi *mcspi)
अणु
	काष्ठा spi_master	*master = mcspi->master;
	काष्ठा omap2_mcspi_regs	*ctx = &mcspi->ctx;
	पूर्णांक			ret = 0;

	ret = pm_runसमय_get_sync(mcspi->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(mcspi->dev);

		वापस ret;
	पूर्ण

	mcspi_ग_लिखो_reg(master, OMAP2_MCSPI_WAKEUPENABLE,
			OMAP2_MCSPI_WAKEUPENABLE_WKEN);
	ctx->wakeupenable = OMAP2_MCSPI_WAKEUPENABLE_WKEN;

	omap2_mcspi_set_mode(master);
	pm_runसमय_mark_last_busy(mcspi->dev);
	pm_runसमय_put_स्वतःsuspend(mcspi->dev);
	वापस 0;
पूर्ण

अटल पूर्णांक omap_mcspi_runसमय_suspend(काष्ठा device *dev)
अणु
	पूर्णांक error;

	error = pinctrl_pm_select_idle_state(dev);
	अगर (error)
		dev_warn(dev, "%s: failed to set pins: %i\n", __func__, error);

	वापस 0;
पूर्ण

/*
 * When SPI wake up from off-mode, CS is in activate state. If it was in
 * inactive state when driver was suspend, then क्रमce it to inactive state at
 * wake up.
 */
अटल पूर्णांक omap_mcspi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा omap2_mcspi *mcspi = spi_master_get_devdata(master);
	काष्ठा omap2_mcspi_regs *ctx = &mcspi->ctx;
	काष्ठा omap2_mcspi_cs *cs;
	पूर्णांक error;

	error = pinctrl_pm_select_शेष_state(dev);
	अगर (error)
		dev_warn(dev, "%s: failed to set pins: %i\n", __func__, error);

	/* McSPI: context restore */
	mcspi_ग_लिखो_reg(master, OMAP2_MCSPI_MODULCTRL, ctx->modulctrl);
	mcspi_ग_लिखो_reg(master, OMAP2_MCSPI_WAKEUPENABLE, ctx->wakeupenable);

	list_क्रम_each_entry(cs, &ctx->cs, node) अणु
		/*
		 * We need to toggle CS state क्रम OMAP take this
		 * change in account.
		 */
		अगर ((cs->chconf0 & OMAP2_MCSPI_CHCONF_FORCE) == 0) अणु
			cs->chconf0 |= OMAP2_MCSPI_CHCONF_FORCE;
			ग_लिखोl_relaxed(cs->chconf0,
				       cs->base + OMAP2_MCSPI_CHCONF0);
			cs->chconf0 &= ~OMAP2_MCSPI_CHCONF_FORCE;
			ग_लिखोl_relaxed(cs->chconf0,
				       cs->base + OMAP2_MCSPI_CHCONF0);
		पूर्ण अन्यथा अणु
			ग_लिखोl_relaxed(cs->chconf0,
				       cs->base + OMAP2_MCSPI_CHCONF0);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा omap2_mcspi_platक्रमm_config omap2_pdata = अणु
	.regs_offset = 0,
पूर्ण;

अटल काष्ठा omap2_mcspi_platक्रमm_config omap4_pdata = अणु
	.regs_offset = OMAP4_MCSPI_REG_OFFSET,
पूर्ण;

अटल काष्ठा omap2_mcspi_platक्रमm_config am654_pdata = अणु
	.regs_offset = OMAP4_MCSPI_REG_OFFSET,
	.max_xfer_len = SZ_4K - 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id omap_mcspi_of_match[] = अणु
	अणु
		.compatible = "ti,omap2-mcspi",
		.data = &omap2_pdata,
	पूर्ण,
	अणु
		.compatible = "ti,omap4-mcspi",
		.data = &omap4_pdata,
	पूर्ण,
	अणु
		.compatible = "ti,am654-mcspi",
		.data = &am654_pdata,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_mcspi_of_match);

अटल पूर्णांक omap2_mcspi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master	*master;
	स्थिर काष्ठा omap2_mcspi_platक्रमm_config *pdata;
	काष्ठा omap2_mcspi	*mcspi;
	काष्ठा resource		*r;
	पूर्णांक			status = 0, i;
	u32			regs_offset = 0;
	काष्ठा device_node	*node = pdev->dev.of_node;
	स्थिर काष्ठा of_device_id *match;

	अगर (of_property_पढ़ो_bool(node, "spi-slave"))
		master = spi_alloc_slave(&pdev->dev, माप(*mcspi));
	अन्यथा
		master = spi_alloc_master(&pdev->dev, माप(*mcspi));
	अगर (!master)
		वापस -ENOMEM;

	/* the spi->mode bits understood by this driver: */
	master->mode_bits = SPI_CPOL | SPI_CPHA | SPI_CS_HIGH;
	master->bits_per_word_mask = SPI_BPW_RANGE_MASK(4, 32);
	master->setup = omap2_mcspi_setup;
	master->स्वतः_runसमय_pm = true;
	master->prepare_message = omap2_mcspi_prepare_message;
	master->can_dma = omap2_mcspi_can_dma;
	master->transfer_one = omap2_mcspi_transfer_one;
	master->set_cs = omap2_mcspi_set_cs;
	master->cleanup = omap2_mcspi_cleanup;
	master->slave_पात = omap2_mcspi_slave_पात;
	master->dev.of_node = node;
	master->max_speed_hz = OMAP2_MCSPI_MAX_FREQ;
	master->min_speed_hz = OMAP2_MCSPI_MAX_FREQ >> 15;
	master->use_gpio_descriptors = true;

	platक्रमm_set_drvdata(pdev, master);

	mcspi = spi_master_get_devdata(master);
	mcspi->master = master;

	match = of_match_device(omap_mcspi_of_match, &pdev->dev);
	अगर (match) अणु
		u32 num_cs = 1; /* शेष number of chipselect */
		pdata = match->data;

		of_property_पढ़ो_u32(node, "ti,spi-num-cs", &num_cs);
		master->num_chipselect = num_cs;
		अगर (of_get_property(node, "ti,pindir-d0-out-d1-in", शून्य))
			mcspi->pin_dir = MCSPI_PINसूची_D0_OUT_D1_IN;
	पूर्ण अन्यथा अणु
		pdata = dev_get_platdata(&pdev->dev);
		master->num_chipselect = pdata->num_cs;
		mcspi->pin_dir = pdata->pin_dir;
	पूर्ण
	regs_offset = pdata->regs_offset;
	अगर (pdata->max_xfer_len) अणु
		mcspi->max_xfer_len = pdata->max_xfer_len;
		master->max_transfer_size = omap2_mcspi_max_xfer_size;
	पूर्ण

	r = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mcspi->base = devm_ioremap_resource(&pdev->dev, r);
	अगर (IS_ERR(mcspi->base)) अणु
		status = PTR_ERR(mcspi->base);
		जाओ मुक्त_master;
	पूर्ण
	mcspi->phys = r->start + regs_offset;
	mcspi->base += regs_offset;

	mcspi->dev = &pdev->dev;

	INIT_LIST_HEAD(&mcspi->ctx.cs);

	mcspi->dma_channels = devm_kसुस्मृति(&pdev->dev, master->num_chipselect,
					   माप(काष्ठा omap2_mcspi_dma),
					   GFP_KERNEL);
	अगर (mcspi->dma_channels == शून्य) अणु
		status = -ENOMEM;
		जाओ मुक्त_master;
	पूर्ण

	क्रम (i = 0; i < master->num_chipselect; i++) अणु
		प्र_लिखो(mcspi->dma_channels[i].dma_rx_ch_name, "rx%d", i);
		प्र_लिखो(mcspi->dma_channels[i].dma_tx_ch_name, "tx%d", i);

		status = omap2_mcspi_request_dma(mcspi,
						 &mcspi->dma_channels[i]);
		अगर (status == -EPROBE_DEFER)
			जाओ मुक्त_master;
	पूर्ण

	status = platक्रमm_get_irq(pdev, 0);
	अगर (status == -EPROBE_DEFER)
		जाओ मुक्त_master;
	अगर (status < 0) अणु
		dev_err(&pdev->dev, "no irq resource found\n");
		जाओ मुक्त_master;
	पूर्ण
	init_completion(&mcspi->txकरोne);
	status = devm_request_irq(&pdev->dev, status,
				  omap2_mcspi_irq_handler, 0, pdev->name,
				  mcspi);
	अगर (status) अणु
		dev_err(&pdev->dev, "Cannot request IRQ");
		जाओ मुक्त_master;
	पूर्ण

	pm_runसमय_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&pdev->dev, SPI_AUTOSUSPEND_TIMEOUT);
	pm_runसमय_enable(&pdev->dev);

	status = omap2_mcspi_controller_setup(mcspi);
	अगर (status < 0)
		जाओ disable_pm;

	status = devm_spi_रेजिस्टर_controller(&pdev->dev, master);
	अगर (status < 0)
		जाओ disable_pm;

	वापस status;

disable_pm:
	pm_runसमय_करोnt_use_स्वतःsuspend(&pdev->dev);
	pm_runसमय_put_sync(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
मुक्त_master:
	omap2_mcspi_release_dma(master);
	spi_master_put(master);
	वापस status;
पूर्ण

अटल पूर्णांक omap2_mcspi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा spi_master *master = platक्रमm_get_drvdata(pdev);
	काष्ठा omap2_mcspi *mcspi = spi_master_get_devdata(master);

	omap2_mcspi_release_dma(master);

	pm_runसमय_करोnt_use_स्वतःsuspend(mcspi->dev);
	pm_runसमय_put_sync(mcspi->dev);
	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

/* work with hotplug and coldplug */
MODULE_ALIAS("platform:omap2_mcspi");

अटल पूर्णांक __maybe_unused omap2_mcspi_suspend(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा omap2_mcspi *mcspi = spi_master_get_devdata(master);
	पूर्णांक error;

	error = pinctrl_pm_select_sleep_state(dev);
	अगर (error)
		dev_warn(mcspi->dev, "%s: failed to set pins: %i\n",
			 __func__, error);

	error = spi_master_suspend(master);
	अगर (error)
		dev_warn(mcspi->dev, "%s: master suspend failed: %i\n",
			 __func__, error);

	वापस pm_runसमय_क्रमce_suspend(dev);
पूर्ण

अटल पूर्णांक __maybe_unused omap2_mcspi_resume(काष्ठा device *dev)
अणु
	काष्ठा spi_master *master = dev_get_drvdata(dev);
	काष्ठा omap2_mcspi *mcspi = spi_master_get_devdata(master);
	पूर्णांक error;

	error = spi_master_resume(master);
	अगर (error)
		dev_warn(mcspi->dev, "%s: master resume failed: %i\n",
			 __func__, error);

	वापस pm_runसमय_क्रमce_resume(dev);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops omap2_mcspi_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(omap2_mcspi_suspend,
				omap2_mcspi_resume)
	.runसमय_suspend	= omap_mcspi_runसमय_suspend,
	.runसमय_resume		= omap_mcspi_runसमय_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver omap2_mcspi_driver = अणु
	.driver = अणु
		.name =		"omap2_mcspi",
		.pm =		&omap2_mcspi_pm_ops,
		.of_match_table = omap_mcspi_of_match,
	पूर्ण,
	.probe =	omap2_mcspi_probe,
	.हटाओ =	omap2_mcspi_हटाओ,
पूर्ण;

module_platक्रमm_driver(omap2_mcspi_driver);
MODULE_LICENSE("GPL");
