<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * omap-mcbsp.c  --  OMAP ALSA SoC DAI driver using McBSP port
 *
 * Copyright (C) 2008 Nokia Corporation
 *
 * Contact: Jarkko Nikula <jarkko.nikula@biपंचांगer.com>
 *          Peter Ujfalusi <peter.ujfalusi@ti.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश "omap-mcbsp-priv.h"
#समावेश "omap-mcbsp.h"
#समावेश "sdma-pcm.h"

#घोषणा OMAP_MCBSP_RATES	(SNDRV_PCM_RATE_8000_96000)

क्रमागत अणु
	OMAP_MCBSP_WORD_8 = 0,
	OMAP_MCBSP_WORD_12,
	OMAP_MCBSP_WORD_16,
	OMAP_MCBSP_WORD_20,
	OMAP_MCBSP_WORD_24,
	OMAP_MCBSP_WORD_32,
पूर्ण;

अटल व्योम omap_mcbsp_dump_reg(काष्ठा omap_mcbsp *mcbsp)
अणु
	dev_dbg(mcbsp->dev, "**** McBSP%d regs ****\n", mcbsp->id);
	dev_dbg(mcbsp->dev, "DRR2:  0x%04x\n", MCBSP_READ(mcbsp, DRR2));
	dev_dbg(mcbsp->dev, "DRR1:  0x%04x\n", MCBSP_READ(mcbsp, DRR1));
	dev_dbg(mcbsp->dev, "DXR2:  0x%04x\n", MCBSP_READ(mcbsp, DXR2));
	dev_dbg(mcbsp->dev, "DXR1:  0x%04x\n", MCBSP_READ(mcbsp, DXR1));
	dev_dbg(mcbsp->dev, "SPCR2: 0x%04x\n", MCBSP_READ(mcbsp, SPCR2));
	dev_dbg(mcbsp->dev, "SPCR1: 0x%04x\n", MCBSP_READ(mcbsp, SPCR1));
	dev_dbg(mcbsp->dev, "RCR2:  0x%04x\n", MCBSP_READ(mcbsp, RCR2));
	dev_dbg(mcbsp->dev, "RCR1:  0x%04x\n", MCBSP_READ(mcbsp, RCR1));
	dev_dbg(mcbsp->dev, "XCR2:  0x%04x\n", MCBSP_READ(mcbsp, XCR2));
	dev_dbg(mcbsp->dev, "XCR1:  0x%04x\n", MCBSP_READ(mcbsp, XCR1));
	dev_dbg(mcbsp->dev, "SRGR2: 0x%04x\n", MCBSP_READ(mcbsp, SRGR2));
	dev_dbg(mcbsp->dev, "SRGR1: 0x%04x\n", MCBSP_READ(mcbsp, SRGR1));
	dev_dbg(mcbsp->dev, "PCR0:  0x%04x\n", MCBSP_READ(mcbsp, PCR0));
	dev_dbg(mcbsp->dev, "***********************\n");
पूर्ण

अटल पूर्णांक omap2_mcbsp_set_clks_src(काष्ठा omap_mcbsp *mcbsp, u8 fck_src_id)
अणु
	काष्ठा clk *fck_src;
	स्थिर अक्षर *src;
	पूर्णांक r;

	अगर (fck_src_id == MCBSP_CLKS_PAD_SRC)
		src = "pad_fck";
	अन्यथा अगर (fck_src_id == MCBSP_CLKS_PRCM_SRC)
		src = "prcm_fck";
	अन्यथा
		वापस -EINVAL;

	fck_src = clk_get(mcbsp->dev, src);
	अगर (IS_ERR(fck_src)) अणु
		dev_err(mcbsp->dev, "CLKS: could not clk_get() %s\n", src);
		वापस -EINVAL;
	पूर्ण

	pm_runसमय_put_sync(mcbsp->dev);

	r = clk_set_parent(mcbsp->fclk, fck_src);
	अगर (r)
		dev_err(mcbsp->dev, "CLKS: could not clk_set_parent() to %s\n",
			src);

	pm_runसमय_get_sync(mcbsp->dev);

	clk_put(fck_src);

	वापस r;
पूर्ण

अटल irqवापस_t omap_mcbsp_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा omap_mcbsp *mcbsp = data;
	u16 irqst;

	irqst = MCBSP_READ(mcbsp, IRQST);
	dev_dbg(mcbsp->dev, "IRQ callback : 0x%x\n", irqst);

	अगर (irqst & RSYNCERREN)
		dev_err(mcbsp->dev, "RX Frame Sync Error!\n");
	अगर (irqst & RFSREN)
		dev_dbg(mcbsp->dev, "RX Frame Sync\n");
	अगर (irqst & Rखातापूर्णEN)
		dev_dbg(mcbsp->dev, "RX End Of Frame\n");
	अगर (irqst & RRDYEN)
		dev_dbg(mcbsp->dev, "RX Buffer Threshold Reached\n");
	अगर (irqst & RUNDFLEN)
		dev_err(mcbsp->dev, "RX Buffer Underflow!\n");
	अगर (irqst & ROVFLEN)
		dev_err(mcbsp->dev, "RX Buffer Overflow!\n");

	अगर (irqst & XSYNCERREN)
		dev_err(mcbsp->dev, "TX Frame Sync Error!\n");
	अगर (irqst & XFSXEN)
		dev_dbg(mcbsp->dev, "TX Frame Sync\n");
	अगर (irqst & Xखातापूर्णEN)
		dev_dbg(mcbsp->dev, "TX End Of Frame\n");
	अगर (irqst & XRDYEN)
		dev_dbg(mcbsp->dev, "TX Buffer threshold Reached\n");
	अगर (irqst & XUNDFLEN)
		dev_err(mcbsp->dev, "TX Buffer Underflow!\n");
	अगर (irqst & XOVFLEN)
		dev_err(mcbsp->dev, "TX Buffer Overflow!\n");
	अगर (irqst & XEMPTYखातापूर्णEN)
		dev_dbg(mcbsp->dev, "TX Buffer empty at end of frame\n");

	MCBSP_WRITE(mcbsp, IRQST, irqst);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t omap_mcbsp_tx_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा omap_mcbsp *mcbsp = data;
	u16 irqst_spcr2;

	irqst_spcr2 = MCBSP_READ(mcbsp, SPCR2);
	dev_dbg(mcbsp->dev, "TX IRQ callback : 0x%x\n", irqst_spcr2);

	अगर (irqst_spcr2 & XSYNC_ERR) अणु
		dev_err(mcbsp->dev, "TX Frame Sync Error! : 0x%x\n",
			irqst_spcr2);
		/* Writing zero to XSYNC_ERR clears the IRQ */
		MCBSP_WRITE(mcbsp, SPCR2, MCBSP_READ_CACHE(mcbsp, SPCR2));
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t omap_mcbsp_rx_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा omap_mcbsp *mcbsp = data;
	u16 irqst_spcr1;

	irqst_spcr1 = MCBSP_READ(mcbsp, SPCR1);
	dev_dbg(mcbsp->dev, "RX IRQ callback : 0x%x\n", irqst_spcr1);

	अगर (irqst_spcr1 & RSYNC_ERR) अणु
		dev_err(mcbsp->dev, "RX Frame Sync Error! : 0x%x\n",
			irqst_spcr1);
		/* Writing zero to RSYNC_ERR clears the IRQ */
		MCBSP_WRITE(mcbsp, SPCR1, MCBSP_READ_CACHE(mcbsp, SPCR1));
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * omap_mcbsp_config simply ग_लिखो a config to the
 * appropriate McBSP.
 * You either call this function or set the McBSP रेजिस्टरs
 * by yourself beक्रमe calling omap_mcbsp_start().
 */
अटल व्योम omap_mcbsp_config(काष्ठा omap_mcbsp *mcbsp,
			      स्थिर काष्ठा omap_mcbsp_reg_cfg *config)
अणु
	dev_dbg(mcbsp->dev, "Configuring McBSP%d  phys_base: 0x%08lx\n",
		mcbsp->id, mcbsp->phys_base);

	/* We ग_लिखो the given config */
	MCBSP_WRITE(mcbsp, SPCR2, config->spcr2);
	MCBSP_WRITE(mcbsp, SPCR1, config->spcr1);
	MCBSP_WRITE(mcbsp, RCR2, config->rcr2);
	MCBSP_WRITE(mcbsp, RCR1, config->rcr1);
	MCBSP_WRITE(mcbsp, XCR2, config->xcr2);
	MCBSP_WRITE(mcbsp, XCR1, config->xcr1);
	MCBSP_WRITE(mcbsp, SRGR2, config->srgr2);
	MCBSP_WRITE(mcbsp, SRGR1, config->srgr1);
	MCBSP_WRITE(mcbsp, MCR2, config->mcr2);
	MCBSP_WRITE(mcbsp, MCR1, config->mcr1);
	MCBSP_WRITE(mcbsp, PCR0, config->pcr0);
	अगर (mcbsp->pdata->has_ccr) अणु
		MCBSP_WRITE(mcbsp, XCCR, config->xccr);
		MCBSP_WRITE(mcbsp, RCCR, config->rccr);
	पूर्ण
	/* Enable wakeup behavior */
	अगर (mcbsp->pdata->has_wakeup)
		MCBSP_WRITE(mcbsp, WAKEUPEN, XRDYEN | RRDYEN);

	/* Enable TX/RX sync error पूर्णांकerrupts by शेष */
	अगर (mcbsp->irq)
		MCBSP_WRITE(mcbsp, IRQEN, RSYNCERREN | XSYNCERREN |
			    RUNDFLEN | ROVFLEN | XUNDFLEN | XOVFLEN);
पूर्ण

/**
 * omap_mcbsp_dma_reg_params - वापसs the address of mcbsp data रेजिस्टर
 * @mcbsp: omap_mcbsp काष्ठा क्रम the McBSP instance
 * @stream: Stream direction (playback/capture)
 *
 * Returns the address of mcbsp data transmit रेजिस्टर or data receive रेजिस्टर
 * to be used by DMA क्रम transferring/receiving data
 */
अटल पूर्णांक omap_mcbsp_dma_reg_params(काष्ठा omap_mcbsp *mcbsp,
				     अचिन्हित पूर्णांक stream)
अणु
	पूर्णांक data_reg;

	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		अगर (mcbsp->pdata->reg_size == 2)
			data_reg = OMAP_MCBSP_REG_DXR1;
		अन्यथा
			data_reg = OMAP_MCBSP_REG_DXR;
	पूर्ण अन्यथा अणु
		अगर (mcbsp->pdata->reg_size == 2)
			data_reg = OMAP_MCBSP_REG_DRR1;
		अन्यथा
			data_reg = OMAP_MCBSP_REG_DRR;
	पूर्ण

	वापस mcbsp->phys_dma_base + data_reg * mcbsp->pdata->reg_step;
पूर्ण

/*
 * omap_mcbsp_set_rx_threshold configures the transmit threshold in words.
 * The threshold parameter is 1 based, and it is converted (threshold - 1)
 * क्रम the THRSH2 रेजिस्टर.
 */
अटल व्योम omap_mcbsp_set_tx_threshold(काष्ठा omap_mcbsp *mcbsp, u16 threshold)
अणु
	अगर (threshold && threshold <= mcbsp->max_tx_thres)
		MCBSP_WRITE(mcbsp, THRSH2, threshold - 1);
पूर्ण

/*
 * omap_mcbsp_set_rx_threshold configures the receive threshold in words.
 * The threshold parameter is 1 based, and it is converted (threshold - 1)
 * क्रम the THRSH1 रेजिस्टर.
 */
अटल व्योम omap_mcbsp_set_rx_threshold(काष्ठा omap_mcbsp *mcbsp, u16 threshold)
अणु
	अगर (threshold && threshold <= mcbsp->max_rx_thres)
		MCBSP_WRITE(mcbsp, THRSH1, threshold - 1);
पूर्ण

/*
 * omap_mcbsp_get_tx_delay वापसs the number of used slots in the McBSP FIFO
 */
अटल u16 omap_mcbsp_get_tx_delay(काष्ठा omap_mcbsp *mcbsp)
अणु
	u16 bufख_स्थिति;

	/* Returns the number of मुक्त locations in the buffer */
	bufख_स्थिति = MCBSP_READ(mcbsp, XBUFFSTAT);

	/* Number of slots are dअगरferent in McBSP ports */
	वापस mcbsp->pdata->buffer_size - bufख_स्थिति;
पूर्ण

/*
 * omap_mcbsp_get_rx_delay वापसs the number of मुक्त slots in the McBSP FIFO
 * to reach the threshold value (when the DMA will be triggered to पढ़ो it)
 */
अटल u16 omap_mcbsp_get_rx_delay(काष्ठा omap_mcbsp *mcbsp)
अणु
	u16 bufख_स्थिति, threshold;

	/* Returns the number of used locations in the buffer */
	bufख_स्थिति = MCBSP_READ(mcbsp, RBUFFSTAT);
	/* RX threshold */
	threshold = MCBSP_READ(mcbsp, THRSH1);

	/* Return the number of location till we reach the threshold limit */
	अगर (threshold <= bufख_स्थिति)
		वापस 0;
	अन्यथा
		वापस threshold - bufख_स्थिति;
पूर्ण

अटल पूर्णांक omap_mcbsp_request(काष्ठा omap_mcbsp *mcbsp)
अणु
	व्योम *reg_cache;
	पूर्णांक err;

	reg_cache = kzalloc(mcbsp->reg_cache_size, GFP_KERNEL);
	अगर (!reg_cache)
		वापस -ENOMEM;

	spin_lock(&mcbsp->lock);
	अगर (!mcbsp->मुक्त) अणु
		dev_err(mcbsp->dev, "McBSP%d is currently in use\n", mcbsp->id);
		err = -EBUSY;
		जाओ err_kमुक्त;
	पूर्ण

	mcbsp->मुक्त = false;
	mcbsp->reg_cache = reg_cache;
	spin_unlock(&mcbsp->lock);

	अगर(mcbsp->pdata->ops && mcbsp->pdata->ops->request)
		mcbsp->pdata->ops->request(mcbsp->id - 1);

	/*
	 * Make sure that transmitter, receiver and sample-rate generator are
	 * not running beक्रमe activating IRQs.
	 */
	MCBSP_WRITE(mcbsp, SPCR1, 0);
	MCBSP_WRITE(mcbsp, SPCR2, 0);

	अगर (mcbsp->irq) अणु
		err = request_irq(mcbsp->irq, omap_mcbsp_irq_handler, 0,
				  "McBSP", (व्योम *)mcbsp);
		अगर (err != 0) अणु
			dev_err(mcbsp->dev, "Unable to request IRQ\n");
			जाओ err_clk_disable;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = request_irq(mcbsp->tx_irq, omap_mcbsp_tx_irq_handler, 0,
				  "McBSP TX", (व्योम *)mcbsp);
		अगर (err != 0) अणु
			dev_err(mcbsp->dev, "Unable to request TX IRQ\n");
			जाओ err_clk_disable;
		पूर्ण

		err = request_irq(mcbsp->rx_irq, omap_mcbsp_rx_irq_handler, 0,
				  "McBSP RX", (व्योम *)mcbsp);
		अगर (err != 0) अणु
			dev_err(mcbsp->dev, "Unable to request RX IRQ\n");
			जाओ err_मुक्त_irq;
		पूर्ण
	पूर्ण

	वापस 0;
err_मुक्त_irq:
	मुक्त_irq(mcbsp->tx_irq, (व्योम *)mcbsp);
err_clk_disable:
	अगर(mcbsp->pdata->ops && mcbsp->pdata->ops->मुक्त)
		mcbsp->pdata->ops->मुक्त(mcbsp->id - 1);

	/* Disable wakeup behavior */
	अगर (mcbsp->pdata->has_wakeup)
		MCBSP_WRITE(mcbsp, WAKEUPEN, 0);

	spin_lock(&mcbsp->lock);
	mcbsp->मुक्त = true;
	mcbsp->reg_cache = शून्य;
err_kमुक्त:
	spin_unlock(&mcbsp->lock);
	kमुक्त(reg_cache);

	वापस err;
पूर्ण

अटल व्योम omap_mcbsp_मुक्त(काष्ठा omap_mcbsp *mcbsp)
अणु
	व्योम *reg_cache;

	अगर(mcbsp->pdata->ops && mcbsp->pdata->ops->मुक्त)
		mcbsp->pdata->ops->मुक्त(mcbsp->id - 1);

	/* Disable wakeup behavior */
	अगर (mcbsp->pdata->has_wakeup)
		MCBSP_WRITE(mcbsp, WAKEUPEN, 0);

	/* Disable पूर्णांकerrupt requests */
	अगर (mcbsp->irq) अणु
		MCBSP_WRITE(mcbsp, IRQEN, 0);

		मुक्त_irq(mcbsp->irq, (व्योम *)mcbsp);
	पूर्ण अन्यथा अणु
		मुक्त_irq(mcbsp->rx_irq, (व्योम *)mcbsp);
		मुक्त_irq(mcbsp->tx_irq, (व्योम *)mcbsp);
	पूर्ण

	reg_cache = mcbsp->reg_cache;

	/*
	 * Select CLKS source from पूर्णांकernal source unconditionally beक्रमe
	 * marking the McBSP port as मुक्त.
	 * If the बाह्यal घड़ी source via MCBSP_CLKS pin has been selected the
	 * प्रणाली will refuse to enter idle अगर the CLKS pin source is not reset
	 * back to पूर्णांकernal source.
	 */
	अगर (!mcbsp_omap1())
		omap2_mcbsp_set_clks_src(mcbsp, MCBSP_CLKS_PRCM_SRC);

	spin_lock(&mcbsp->lock);
	अगर (mcbsp->मुक्त)
		dev_err(mcbsp->dev, "McBSP%d was not reserved\n", mcbsp->id);
	अन्यथा
		mcbsp->मुक्त = true;
	mcbsp->reg_cache = शून्य;
	spin_unlock(&mcbsp->lock);

	kमुक्त(reg_cache);
पूर्ण

/*
 * Here we start the McBSP, by enabling transmitter, receiver or both.
 * If no transmitter or receiver is active prior calling, then sample-rate
 * generator and frame sync are started.
 */
अटल व्योम omap_mcbsp_start(काष्ठा omap_mcbsp *mcbsp, पूर्णांक stream)
अणु
	पूर्णांक tx = (stream == SNDRV_PCM_STREAM_PLAYBACK);
	पूर्णांक rx = !tx;
	पूर्णांक enable_srg = 0;
	u16 w;

	अगर (mcbsp->st_data)
		omap_mcbsp_st_start(mcbsp);

	/* Only enable SRG, अगर McBSP is master */
	w = MCBSP_READ_CACHE(mcbsp, PCR0);
	अगर (w & (FSXM | FSRM | CLKXM | CLKRM))
		enable_srg = !((MCBSP_READ_CACHE(mcbsp, SPCR2) |
				MCBSP_READ_CACHE(mcbsp, SPCR1)) & 1);

	अगर (enable_srg) अणु
		/* Start the sample generator */
		w = MCBSP_READ_CACHE(mcbsp, SPCR2);
		MCBSP_WRITE(mcbsp, SPCR2, w | (1 << 6));
	पूर्ण

	/* Enable transmitter and receiver */
	tx &= 1;
	w = MCBSP_READ_CACHE(mcbsp, SPCR2);
	MCBSP_WRITE(mcbsp, SPCR2, w | tx);

	rx &= 1;
	w = MCBSP_READ_CACHE(mcbsp, SPCR1);
	MCBSP_WRITE(mcbsp, SPCR1, w | rx);

	/*
	 * Worst हाल: CLKSRG*2 = 8000khz: (1/8000) * 2 * 2 usec
	 * REVISIT: 100us may give enough समय क्रम two CLKSRG, however
	 * due to some unknown PM related, घड़ी gating etc. reason it
	 * is now at 500us.
	 */
	udelay(500);

	अगर (enable_srg) अणु
		/* Start frame sync */
		w = MCBSP_READ_CACHE(mcbsp, SPCR2);
		MCBSP_WRITE(mcbsp, SPCR2, w | (1 << 7));
	पूर्ण

	अगर (mcbsp->pdata->has_ccr) अणु
		/* Release the transmitter and receiver */
		w = MCBSP_READ_CACHE(mcbsp, XCCR);
		w &= ~(tx ? XDISABLE : 0);
		MCBSP_WRITE(mcbsp, XCCR, w);
		w = MCBSP_READ_CACHE(mcbsp, RCCR);
		w &= ~(rx ? RDISABLE : 0);
		MCBSP_WRITE(mcbsp, RCCR, w);
	पूर्ण

	/* Dump McBSP Regs */
	omap_mcbsp_dump_reg(mcbsp);
पूर्ण

अटल व्योम omap_mcbsp_stop(काष्ठा omap_mcbsp *mcbsp, पूर्णांक stream)
अणु
	पूर्णांक tx = (stream == SNDRV_PCM_STREAM_PLAYBACK);
	पूर्णांक rx = !tx;
	पूर्णांक idle;
	u16 w;

	/* Reset transmitter */
	tx &= 1;
	अगर (mcbsp->pdata->has_ccr) अणु
		w = MCBSP_READ_CACHE(mcbsp, XCCR);
		w |= (tx ? XDISABLE : 0);
		MCBSP_WRITE(mcbsp, XCCR, w);
	पूर्ण
	w = MCBSP_READ_CACHE(mcbsp, SPCR2);
	MCBSP_WRITE(mcbsp, SPCR2, w & ~tx);

	/* Reset receiver */
	rx &= 1;
	अगर (mcbsp->pdata->has_ccr) अणु
		w = MCBSP_READ_CACHE(mcbsp, RCCR);
		w |= (rx ? RDISABLE : 0);
		MCBSP_WRITE(mcbsp, RCCR, w);
	पूर्ण
	w = MCBSP_READ_CACHE(mcbsp, SPCR1);
	MCBSP_WRITE(mcbsp, SPCR1, w & ~rx);

	idle = !((MCBSP_READ_CACHE(mcbsp, SPCR2) |
			MCBSP_READ_CACHE(mcbsp, SPCR1)) & 1);

	अगर (idle) अणु
		/* Reset the sample rate generator */
		w = MCBSP_READ_CACHE(mcbsp, SPCR2);
		MCBSP_WRITE(mcbsp, SPCR2, w & ~(1 << 6));
	पूर्ण

	अगर (mcbsp->st_data)
		omap_mcbsp_st_stop(mcbsp);
पूर्ण

#घोषणा max_thres(m)			(mcbsp->pdata->buffer_size)
#घोषणा valid_threshold(m, val)		((val) <= max_thres(m))
#घोषणा THRESHOLD_PROP_BUILDER(prop)					\
अटल sमाप_प्रकार prop##_show(काष्ठा device *dev,				\
			काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु									\
	काष्ठा omap_mcbsp *mcbsp = dev_get_drvdata(dev);		\
									\
	वापस प्र_लिखो(buf, "%u\n", mcbsp->prop);			\
पूर्ण									\
									\
अटल sमाप_प्रकार prop##_store(काष्ठा device *dev,				\
				काष्ठा device_attribute *attr,		\
				स्थिर अक्षर *buf, माप_प्रकार size)		\
अणु									\
	काष्ठा omap_mcbsp *mcbsp = dev_get_drvdata(dev);		\
	अचिन्हित दीर्घ val;						\
	पूर्णांक status;							\
									\
	status = kम_से_अदीर्घ(buf, 0, &val);				\
	अगर (status)							\
		वापस status;						\
									\
	अगर (!valid_threshold(mcbsp, val))				\
		वापस -गलत_तर्क;						\
									\
	mcbsp->prop = val;						\
	वापस size;							\
पूर्ण									\
									\
अटल DEVICE_ATTR(prop, 0644, prop##_show, prop##_store)

THRESHOLD_PROP_BUILDER(max_tx_thres);
THRESHOLD_PROP_BUILDER(max_rx_thres);

अटल स्थिर अक्षर * स्थिर dma_op_modes[] = अणु
	"element", "threshold",
पूर्ण;

अटल sमाप_प्रकार dma_op_mode_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा omap_mcbsp *mcbsp = dev_get_drvdata(dev);
	पूर्णांक dma_op_mode, i = 0;
	sमाप_प्रकार len = 0;
	स्थिर अक्षर * स्थिर *s;

	dma_op_mode = mcbsp->dma_op_mode;

	क्रम (s = &dma_op_modes[i]; i < ARRAY_SIZE(dma_op_modes); s++, i++) अणु
		अगर (dma_op_mode == i)
			len += प्र_लिखो(buf + len, "[%s] ", *s);
		अन्यथा
			len += प्र_लिखो(buf + len, "%s ", *s);
	पूर्ण
	len += प्र_लिखो(buf + len, "\n");

	वापस len;
पूर्ण

अटल sमाप_प्रकार dma_op_mode_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
				 माप_प्रकार size)
अणु
	काष्ठा omap_mcbsp *mcbsp = dev_get_drvdata(dev);
	पूर्णांक i;

	i = sysfs_match_string(dma_op_modes, buf);
	अगर (i < 0)
		वापस i;

	spin_lock_irq(&mcbsp->lock);
	अगर (!mcbsp->मुक्त) अणु
		size = -EBUSY;
		जाओ unlock;
	पूर्ण
	mcbsp->dma_op_mode = i;

unlock:
	spin_unlock_irq(&mcbsp->lock);

	वापस size;
पूर्ण

अटल DEVICE_ATTR_RW(dma_op_mode);

अटल स्थिर काष्ठा attribute *additional_attrs[] = अणु
	&dev_attr_max_tx_thres.attr,
	&dev_attr_max_rx_thres.attr,
	&dev_attr_dma_op_mode.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group additional_attr_group = अणु
	.attrs = (काष्ठा attribute **)additional_attrs,
पूर्ण;

/*
 * McBSP1 and McBSP3 are directly mapped on 1610 and 1510.
 * 730 has only 2 McBSP, and both of them are MPU peripherals.
 */
अटल पूर्णांक omap_mcbsp_init(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_mcbsp *mcbsp = platक्रमm_get_drvdata(pdev);
	काष्ठा resource *res;
	पूर्णांक ret = 0;

	spin_lock_init(&mcbsp->lock);
	mcbsp->मुक्त = true;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "mpu");
	अगर (!res)
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	mcbsp->io_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(mcbsp->io_base))
		वापस PTR_ERR(mcbsp->io_base);

	mcbsp->phys_base = res->start;
	mcbsp->reg_cache_size = resource_size(res);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "dma");
	अगर (!res)
		mcbsp->phys_dma_base = mcbsp->phys_base;
	अन्यथा
		mcbsp->phys_dma_base = res->start;

	/*
	 * OMAP1, 2 uses two पूर्णांकerrupt lines: TX, RX
	 * OMAP2430, OMAP3 SoC have combined IRQ line as well.
	 * OMAP4 and newer SoC only have the combined IRQ line.
	 * Use the combined IRQ अगर available since it gives better debugging
	 * possibilities.
	 */
	mcbsp->irq = platक्रमm_get_irq_byname(pdev, "common");
	अगर (mcbsp->irq == -ENXIO) अणु
		mcbsp->tx_irq = platक्रमm_get_irq_byname(pdev, "tx");

		अगर (mcbsp->tx_irq == -ENXIO) अणु
			mcbsp->irq = platक्रमm_get_irq(pdev, 0);
			mcbsp->tx_irq = 0;
		पूर्ण अन्यथा अणु
			mcbsp->rx_irq = platक्रमm_get_irq_byname(pdev, "rx");
			mcbsp->irq = 0;
		पूर्ण
	पूर्ण

	अगर (!pdev->dev.of_node) अणु
		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_DMA, "tx");
		अगर (!res) अणु
			dev_err(&pdev->dev, "invalid tx DMA channel\n");
			वापस -ENODEV;
		पूर्ण
		mcbsp->dma_req[0] = res->start;
		mcbsp->dma_data[0].filter_data = &mcbsp->dma_req[0];

		res = platक्रमm_get_resource_byname(pdev, IORESOURCE_DMA, "rx");
		अगर (!res) अणु
			dev_err(&pdev->dev, "invalid rx DMA channel\n");
			वापस -ENODEV;
		पूर्ण
		mcbsp->dma_req[1] = res->start;
		mcbsp->dma_data[1].filter_data = &mcbsp->dma_req[1];
	पूर्ण अन्यथा अणु
		mcbsp->dma_data[0].filter_data = "tx";
		mcbsp->dma_data[1].filter_data = "rx";
	पूर्ण

	mcbsp->dma_data[0].addr = omap_mcbsp_dma_reg_params(mcbsp,
						SNDRV_PCM_STREAM_PLAYBACK);
	mcbsp->dma_data[1].addr = omap_mcbsp_dma_reg_params(mcbsp,
						SNDRV_PCM_STREAM_CAPTURE);

	mcbsp->fclk = devm_clk_get(&pdev->dev, "fck");
	अगर (IS_ERR(mcbsp->fclk)) अणु
		ret = PTR_ERR(mcbsp->fclk);
		dev_err(mcbsp->dev, "unable to get fck: %d\n", ret);
		वापस ret;
	पूर्ण

	mcbsp->dma_op_mode = MCBSP_DMA_MODE_ELEMENT;
	अगर (mcbsp->pdata->buffer_size) अणु
		/*
		 * Initially configure the maximum thresholds to a safe value.
		 * The McBSP FIFO usage with these values should not go under
		 * 16 locations.
		 * If the whole FIFO without safety buffer is used, than there
		 * is a possibility that the DMA will be not able to push the
		 * new data on समय, causing channel shअगरts in runसमय.
		 */
		mcbsp->max_tx_thres = max_thres(mcbsp) - 0x10;
		mcbsp->max_rx_thres = max_thres(mcbsp) - 0x10;

		ret = sysfs_create_group(&mcbsp->dev->kobj,
					 &additional_attr_group);
		अगर (ret) अणु
			dev_err(mcbsp->dev,
				"Unable to create additional controls\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = omap_mcbsp_st_init(pdev);
	अगर (ret)
		जाओ err_st;

	वापस 0;

err_st:
	अगर (mcbsp->pdata->buffer_size)
		sysfs_हटाओ_group(&mcbsp->dev->kobj, &additional_attr_group);
	वापस ret;
पूर्ण

/*
 * Stream DMA parameters. DMA request line and port address are set runसमय
 * since they are dअगरferent between OMAP1 and later OMAPs
 */
अटल व्योम omap_mcbsp_set_threshold(काष्ठा snd_pcm_substream *substream,
		अचिन्हित पूर्णांक packet_size)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा omap_mcbsp *mcbsp = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक words;

	/* No need to proceed further अगर McBSP करोes not have FIFO */
	अगर (mcbsp->pdata->buffer_size == 0)
		वापस;

	/*
	 * Configure McBSP threshold based on either:
	 * packet_size, when the sDMA is in packet mode, or based on the
	 * period size in THRESHOLD mode, otherwise use McBSP threshold = 1
	 * क्रम mono streams.
	 */
	अगर (packet_size)
		words = packet_size;
	अन्यथा
		words = 1;

	/* Configure McBSP पूर्णांकernal buffer usage */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		omap_mcbsp_set_tx_threshold(mcbsp, words);
	अन्यथा
		omap_mcbsp_set_rx_threshold(mcbsp, words);
पूर्ण

अटल पूर्णांक omap_mcbsp_hwrule_min_buffersize(काष्ठा snd_pcm_hw_params *params,
				    काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval *buffer_size = hw_param_पूर्णांकerval(params,
					SNDRV_PCM_HW_PARAM_BUFFER_SIZE);
	काष्ठा snd_पूर्णांकerval *channels = hw_param_पूर्णांकerval(params,
					SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा omap_mcbsp *mcbsp = rule->निजी;
	काष्ठा snd_पूर्णांकerval frames;
	पूर्णांक size;

	snd_पूर्णांकerval_any(&frames);
	size = mcbsp->pdata->buffer_size;

	frames.min = size / channels->min;
	frames.पूर्णांकeger = 1;
	वापस snd_पूर्णांकerval_refine(buffer_size, &frames);
पूर्ण

अटल पूर्णांक omap_mcbsp_dai_startup(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा omap_mcbsp *mcbsp = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक err = 0;

	अगर (!snd_soc_dai_active(cpu_dai))
		err = omap_mcbsp_request(mcbsp);

	/*
	 * OMAP3 McBSP FIFO is word काष्ठाured.
	 * McBSP2 has 1024 + 256 = 1280 word दीर्घ buffer,
	 * McBSP1,3,4,5 has 128 word दीर्घ buffer
	 * This means that the size of the FIFO depends on the sample क्रमmat.
	 * For example on McBSP3:
	 * 16bit samples: size is 128 * 2 = 256 bytes
	 * 32bit samples: size is 128 * 4 = 512 bytes
	 * It is simpler to place स्थिरraपूर्णांक क्रम buffer and period based on
	 * channels.
	 * McBSP3 as example again (16 or 32 bit samples):
	 * 1 channel (mono): size is 128 frames (128 words)
	 * 2 channels (stereo): size is 128 / 2 = 64 frames (2 * 64 words)
	 * 4 channels: size is 128 / 4 = 32 frames (4 * 32 words)
	 */
	अगर (mcbsp->pdata->buffer_size) अणु
		/*
		* Rule क्रम the buffer size. We should not allow
		* smaller buffer than the FIFO size to aव्योम underruns.
		* This applies only क्रम the playback stream.
		*/
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			snd_pcm_hw_rule_add(substream->runसमय, 0,
					    SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
					    omap_mcbsp_hwrule_min_buffersize,
					    mcbsp,
					    SNDRV_PCM_HW_PARAM_CHANNELS, -1);

		/* Make sure, that the period size is always even */
		snd_pcm_hw_स्थिरraपूर्णांक_step(substream->runसमय, 0,
					   SNDRV_PCM_HW_PARAM_PERIOD_SIZE, 2);
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम omap_mcbsp_dai_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा omap_mcbsp *mcbsp = snd_soc_dai_get_drvdata(cpu_dai);
	पूर्णांक tx = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);
	पूर्णांक stream1 = tx ? SNDRV_PCM_STREAM_PLAYBACK : SNDRV_PCM_STREAM_CAPTURE;
	पूर्णांक stream2 = tx ? SNDRV_PCM_STREAM_CAPTURE : SNDRV_PCM_STREAM_PLAYBACK;

	अगर (mcbsp->latency[stream2])
		cpu_latency_qos_update_request(&mcbsp->pm_qos_req,
					       mcbsp->latency[stream2]);
	अन्यथा अगर (mcbsp->latency[stream1])
		cpu_latency_qos_हटाओ_request(&mcbsp->pm_qos_req);

	mcbsp->latency[stream1] = 0;

	अगर (!snd_soc_dai_active(cpu_dai)) अणु
		omap_mcbsp_मुक्त(mcbsp);
		mcbsp->configured = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक omap_mcbsp_dai_prepare(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा omap_mcbsp *mcbsp = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा pm_qos_request *pm_qos_req = &mcbsp->pm_qos_req;
	पूर्णांक tx = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK);
	पूर्णांक stream1 = tx ? SNDRV_PCM_STREAM_PLAYBACK : SNDRV_PCM_STREAM_CAPTURE;
	पूर्णांक stream2 = tx ? SNDRV_PCM_STREAM_CAPTURE : SNDRV_PCM_STREAM_PLAYBACK;
	पूर्णांक latency = mcbsp->latency[stream2];

	/* Prevent omap hardware from hitting off between FIFO fills */
	अगर (!latency || mcbsp->latency[stream1] < latency)
		latency = mcbsp->latency[stream1];

	अगर (cpu_latency_qos_request_active(pm_qos_req))
		cpu_latency_qos_update_request(pm_qos_req, latency);
	अन्यथा अगर (latency)
		cpu_latency_qos_add_request(pm_qos_req, latency);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_mcbsp_dai_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
				  काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा omap_mcbsp *mcbsp = snd_soc_dai_get_drvdata(cpu_dai);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		mcbsp->active++;
		omap_mcbsp_start(mcbsp, substream->stream);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		omap_mcbsp_stop(mcbsp, substream->stream);
		mcbsp->active--;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल snd_pcm_sframes_t omap_mcbsp_dai_delay(
			काष्ठा snd_pcm_substream *substream,
			काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा omap_mcbsp *mcbsp = snd_soc_dai_get_drvdata(cpu_dai);
	u16 fअगरo_use;
	snd_pcm_sframes_t delay;

	/* No need to proceed further अगर McBSP करोes not have FIFO */
	अगर (mcbsp->pdata->buffer_size == 0)
		वापस 0;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		fअगरo_use = omap_mcbsp_get_tx_delay(mcbsp);
	अन्यथा
		fअगरo_use = omap_mcbsp_get_rx_delay(mcbsp);

	/*
	 * Divide the used locations with the channel count to get the
	 * FIFO usage in samples (करोn't care about partial samples in the
	 * buffer).
	 */
	delay = fअगरo_use / substream->runसमय->channels;

	वापस delay;
पूर्ण

अटल पूर्णांक omap_mcbsp_dai_hw_params(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_pcm_hw_params *params,
				    काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा omap_mcbsp *mcbsp = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा omap_mcbsp_reg_cfg *regs = &mcbsp->cfg_regs;
	काष्ठा snd_dmaengine_dai_dma_data *dma_data;
	पूर्णांक wlen, channels, wpf;
	पूर्णांक pkt_size = 0;
	अचिन्हित पूर्णांक क्रमmat, भाग, framesize, master;
	अचिन्हित पूर्णांक buffer_size = mcbsp->pdata->buffer_size;

	dma_data = snd_soc_dai_get_dma_data(cpu_dai, substream);
	channels = params_channels(params);

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		wlen = 16;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		wlen = 32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (buffer_size) अणु
		पूर्णांक latency;

		अगर (mcbsp->dma_op_mode == MCBSP_DMA_MODE_THRESHOLD) अणु
			पूर्णांक period_words, max_thrsh;
			पूर्णांक भागider = 0;

			period_words = params_period_bytes(params) / (wlen / 8);
			अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
				max_thrsh = mcbsp->max_tx_thres;
			अन्यथा
				max_thrsh = mcbsp->max_rx_thres;
			/*
			 * Use sDMA packet mode अगर McBSP is in threshold mode:
			 * If period words less than the FIFO size the packet
			 * size is set to the number of period words, otherwise
			 * Look क्रम the biggest threshold value which भागides
			 * the period size evenly.
			 */
			भागider = period_words / max_thrsh;
			अगर (period_words % max_thrsh)
				भागider++;
			जबतक (period_words % भागider &&
				भागider < period_words)
				भागider++;
			अगर (भागider == period_words)
				वापस -EINVAL;

			pkt_size = period_words / भागider;
		पूर्ण अन्यथा अगर (channels > 1) अणु
			/* Use packet mode क्रम non mono streams */
			pkt_size = channels;
		पूर्ण

		latency = (buffer_size - pkt_size) / channels;
		latency = latency * USEC_PER_SEC /
			  (params->rate_num / params->rate_den);
		mcbsp->latency[substream->stream] = latency;

		omap_mcbsp_set_threshold(substream, pkt_size);
	पूर्ण

	dma_data->maxburst = pkt_size;

	अगर (mcbsp->configured) अणु
		/* McBSP alपढ़ोy configured by another stream */
		वापस 0;
	पूर्ण

	regs->rcr2	&= ~(RPHASE | RFRLEN2(0x7f) | RWDLEN2(7));
	regs->xcr2	&= ~(RPHASE | XFRLEN2(0x7f) | XWDLEN2(7));
	regs->rcr1	&= ~(RFRLEN1(0x7f) | RWDLEN1(7));
	regs->xcr1	&= ~(XFRLEN1(0x7f) | XWDLEN1(7));
	क्रमmat = mcbsp->fmt & SND_SOC_DAIFMT_FORMAT_MASK;
	wpf = channels;
	अगर (channels == 2 && (क्रमmat == SND_SOC_DAIFMT_I2S ||
			      क्रमmat == SND_SOC_DAIFMT_LEFT_J)) अणु
		/* Use dual-phase frames */
		regs->rcr2	|= RPHASE;
		regs->xcr2	|= XPHASE;
		/* Set 1 word per (McBSP) frame क्रम phase1 and phase2 */
		wpf--;
		regs->rcr2	|= RFRLEN2(wpf - 1);
		regs->xcr2	|= XFRLEN2(wpf - 1);
	पूर्ण

	regs->rcr1	|= RFRLEN1(wpf - 1);
	regs->xcr1	|= XFRLEN1(wpf - 1);

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		/* Set word lengths */
		regs->rcr2	|= RWDLEN2(OMAP_MCBSP_WORD_16);
		regs->rcr1	|= RWDLEN1(OMAP_MCBSP_WORD_16);
		regs->xcr2	|= XWDLEN2(OMAP_MCBSP_WORD_16);
		regs->xcr1	|= XWDLEN1(OMAP_MCBSP_WORD_16);
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		/* Set word lengths */
		regs->rcr2	|= RWDLEN2(OMAP_MCBSP_WORD_32);
		regs->rcr1	|= RWDLEN1(OMAP_MCBSP_WORD_32);
		regs->xcr2	|= XWDLEN2(OMAP_MCBSP_WORD_32);
		regs->xcr1	|= XWDLEN1(OMAP_MCBSP_WORD_32);
		अवरोध;
	शेष:
		/* Unsupported PCM क्रमmat */
		वापस -EINVAL;
	पूर्ण

	/* In McBSP master modes, FRAME (i.e. sample rate) is generated
	 * by _counting_ BCLKs. Calculate frame size in BCLKs */
	master = mcbsp->fmt & SND_SOC_DAIFMT_MASTER_MASK;
	अगर (master ==	SND_SOC_DAIFMT_CBS_CFS) अणु
		भाग = mcbsp->clk_भाग ? mcbsp->clk_भाग : 1;
		framesize = (mcbsp->in_freq / भाग) / params_rate(params);

		अगर (framesize < wlen * channels) अणु
			prपूर्णांकk(KERN_ERR "%s: not enough bandwidth for desired rate and "
					"channels\n", __func__);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा
		framesize = wlen * channels;

	/* Set FS period and length in terms of bit घड़ी periods */
	regs->srgr2	&= ~FPER(0xfff);
	regs->srgr1	&= ~FWID(0xff);
	चयन (क्रमmat) अणु
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_LEFT_J:
		regs->srgr2	|= FPER(framesize - 1);
		regs->srgr1	|= FWID((framesize >> 1) - 1);
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
	हाल SND_SOC_DAIFMT_DSP_B:
		regs->srgr2	|= FPER(framesize - 1);
		regs->srgr1	|= FWID(0);
		अवरोध;
	पूर्ण

	omap_mcbsp_config(mcbsp, &mcbsp->cfg_regs);
	mcbsp->wlen = wlen;
	mcbsp->configured = 1;

	वापस 0;
पूर्ण

/*
 * This must be called beक्रमe _set_clkभाग and _set_sysclk since McBSP रेजिस्टर
 * cache is initialized here
 */
अटल पूर्णांक omap_mcbsp_dai_set_dai_fmt(काष्ठा snd_soc_dai *cpu_dai,
				      अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा omap_mcbsp *mcbsp = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा omap_mcbsp_reg_cfg *regs = &mcbsp->cfg_regs;
	bool inv_fs = false;

	अगर (mcbsp->configured)
		वापस 0;

	mcbsp->fmt = fmt;
	स_रखो(regs, 0, माप(*regs));
	/* Generic McBSP रेजिस्टर settings */
	regs->spcr2	|= XINTM(3) | FREE;
	regs->spcr1	|= RINTM(3);
	/* RFIG and XFIG are not defined in 2430 and on OMAP3+ */
	अगर (!mcbsp->pdata->has_ccr) अणु
		regs->rcr2	|= RFIG;
		regs->xcr2	|= XFIG;
	पूर्ण

	/* Configure XCCR/RCCR only क्रम revisions which have ccr रेजिस्टरs */
	अगर (mcbsp->pdata->has_ccr) अणु
		regs->xccr = DXENDLY(1) | XDMAEN | XDISABLE;
		regs->rccr = RFULL_CYCLE | RDMAEN | RDISABLE;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		/* 1-bit data delay */
		regs->rcr2	|= RDATDLY(1);
		regs->xcr2	|= XDATDLY(1);
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		/* 0-bit data delay */
		regs->rcr2	|= RDATDLY(0);
		regs->xcr2	|= XDATDLY(0);
		regs->spcr1	|= RJUST(2);
		/* Invert FS polarity configuration */
		inv_fs = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		/* 1-bit data delay */
		regs->rcr2      |= RDATDLY(1);
		regs->xcr2      |= XDATDLY(1);
		/* Invert FS polarity configuration */
		inv_fs = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		/* 0-bit data delay */
		regs->rcr2      |= RDATDLY(0);
		regs->xcr2      |= XDATDLY(0);
		/* Invert FS polarity configuration */
		inv_fs = true;
		अवरोध;
	शेष:
		/* Unsupported data क्रमmat */
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		/* McBSP master. Set FS and bit घड़ीs as outमाला_दो */
		regs->pcr0	|= FSXM | FSRM |
				   CLKXM | CLKRM;
		/* Sample rate generator drives the FS */
		regs->srgr2	|= FSGM;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		/* McBSP slave. FS घड़ी as output */
		regs->srgr2	|= FSGM;
		regs->pcr0	|= FSXM | FSRM;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		/* McBSP slave */
		अवरोध;
	शेष:
		/* Unsupported master/slave configuration */
		वापस -EINVAL;
	पूर्ण

	/* Set bit घड़ी (CLKX/CLKR) and FS polarities */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		/*
		 * Normal BCLK + FS.
		 * FS active low. TX data driven on falling edge of bit घड़ी
		 * and RX data sampled on rising edge of bit घड़ी.
		 */
		regs->pcr0	|= FSXP | FSRP |
				   CLKXP | CLKRP;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		regs->pcr0	|= CLKXP | CLKRP;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		regs->pcr0	|= FSXP | FSRP;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (inv_fs)
		regs->pcr0 ^= FSXP | FSRP;

	वापस 0;
पूर्ण

अटल पूर्णांक omap_mcbsp_dai_set_clkभाग(काष्ठा snd_soc_dai *cpu_dai,
				     पूर्णांक भाग_id, पूर्णांक भाग)
अणु
	काष्ठा omap_mcbsp *mcbsp = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा omap_mcbsp_reg_cfg *regs = &mcbsp->cfg_regs;

	अगर (भाग_id != OMAP_MCBSP_CLKGDV)
		वापस -ENODEV;

	mcbsp->clk_भाग = भाग;
	regs->srgr1	&= ~CLKGDV(0xff);
	regs->srgr1	|= CLKGDV(भाग - 1);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_mcbsp_dai_set_dai_sysclk(काष्ठा snd_soc_dai *cpu_dai,
					 पूर्णांक clk_id, अचिन्हित पूर्णांक freq,
					 पूर्णांक dir)
अणु
	काष्ठा omap_mcbsp *mcbsp = snd_soc_dai_get_drvdata(cpu_dai);
	काष्ठा omap_mcbsp_reg_cfg *regs = &mcbsp->cfg_regs;
	पूर्णांक err = 0;

	अगर (mcbsp->active) अणु
		अगर (freq == mcbsp->in_freq)
			वापस 0;
		अन्यथा
			वापस -EBUSY;
	पूर्ण

	mcbsp->in_freq = freq;
	regs->srgr2 &= ~CLKSM;
	regs->pcr0 &= ~SCLKME;

	चयन (clk_id) अणु
	हाल OMAP_MCBSP_SYSCLK_CLK:
		regs->srgr2	|= CLKSM;
		अवरोध;
	हाल OMAP_MCBSP_SYSCLK_CLKS_FCLK:
		अगर (mcbsp_omap1()) अणु
			err = -EINVAL;
			अवरोध;
		पूर्ण
		err = omap2_mcbsp_set_clks_src(mcbsp,
					       MCBSP_CLKS_PRCM_SRC);
		अवरोध;
	हाल OMAP_MCBSP_SYSCLK_CLKS_EXT:
		अगर (mcbsp_omap1()) अणु
			err = 0;
			अवरोध;
		पूर्ण
		err = omap2_mcbsp_set_clks_src(mcbsp,
					       MCBSP_CLKS_PAD_SRC);
		अवरोध;

	हाल OMAP_MCBSP_SYSCLK_CLKX_EXT:
		regs->srgr2	|= CLKSM;
		regs->pcr0	|= SCLKME;
		/*
		 * If McBSP is master but yet the CLKX/CLKR pin drives the SRG,
		 * disable output on those pins. This enables to inject the
		 * reference घड़ी through CLKX/CLKR. For this to work
		 * set_dai_sysclk() _needs_ to be called after set_dai_fmt().
		 */
		regs->pcr0	&= ~CLKXM;
		अवरोध;
	हाल OMAP_MCBSP_SYSCLK_CLKR_EXT:
		regs->pcr0	|= SCLKME;
		/* Disable ouput on CLKR pin in master mode */
		regs->pcr0	&= ~CLKRM;
		अवरोध;
	शेष:
		err = -ENODEV;
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops mcbsp_dai_ops = अणु
	.startup	= omap_mcbsp_dai_startup,
	.shutकरोwn	= omap_mcbsp_dai_shutकरोwn,
	.prepare	= omap_mcbsp_dai_prepare,
	.trigger	= omap_mcbsp_dai_trigger,
	.delay		= omap_mcbsp_dai_delay,
	.hw_params	= omap_mcbsp_dai_hw_params,
	.set_fmt	= omap_mcbsp_dai_set_dai_fmt,
	.set_clkभाग	= omap_mcbsp_dai_set_clkभाग,
	.set_sysclk	= omap_mcbsp_dai_set_dai_sysclk,
पूर्ण;

अटल पूर्णांक omap_mcbsp_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा omap_mcbsp *mcbsp = snd_soc_dai_get_drvdata(dai);

	pm_runसमय_enable(mcbsp->dev);

	snd_soc_dai_init_dma_data(dai,
				  &mcbsp->dma_data[SNDRV_PCM_STREAM_PLAYBACK],
				  &mcbsp->dma_data[SNDRV_PCM_STREAM_CAPTURE]);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_mcbsp_हटाओ(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा omap_mcbsp *mcbsp = snd_soc_dai_get_drvdata(dai);

	pm_runसमय_disable(mcbsp->dev);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver omap_mcbsp_dai = अणु
	.probe = omap_mcbsp_probe,
	.हटाओ = omap_mcbsp_हटाओ,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 16,
		.rates = OMAP_MCBSP_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE,
	पूर्ण,
	.capture = अणु
		.channels_min = 1,
		.channels_max = 16,
		.rates = OMAP_MCBSP_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE,
	पूर्ण,
	.ops = &mcbsp_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver omap_mcbsp_component = अणु
	.name		= "omap-mcbsp",
पूर्ण;

अटल काष्ठा omap_mcbsp_platक्रमm_data omap2420_pdata = अणु
	.reg_step = 4,
	.reg_size = 2,
पूर्ण;

अटल काष्ठा omap_mcbsp_platक्रमm_data omap2430_pdata = अणु
	.reg_step = 4,
	.reg_size = 4,
	.has_ccr = true,
पूर्ण;

अटल काष्ठा omap_mcbsp_platक्रमm_data omap3_pdata = अणु
	.reg_step = 4,
	.reg_size = 4,
	.has_ccr = true,
	.has_wakeup = true,
पूर्ण;

अटल काष्ठा omap_mcbsp_platक्रमm_data omap4_pdata = अणु
	.reg_step = 4,
	.reg_size = 4,
	.has_ccr = true,
	.has_wakeup = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id omap_mcbsp_of_match[] = अणु
	अणु
		.compatible = "ti,omap2420-mcbsp",
		.data = &omap2420_pdata,
	पूर्ण,
	अणु
		.compatible = "ti,omap2430-mcbsp",
		.data = &omap2430_pdata,
	पूर्ण,
	अणु
		.compatible = "ti,omap3-mcbsp",
		.data = &omap3_pdata,
	पूर्ण,
	अणु
		.compatible = "ti,omap4-mcbsp",
		.data = &omap4_pdata,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, omap_mcbsp_of_match);

अटल पूर्णांक asoc_mcbsp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_mcbsp_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा omap_mcbsp *mcbsp;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक ret;

	match = of_match_device(omap_mcbsp_of_match, &pdev->dev);
	अगर (match) अणु
		काष्ठा device_node *node = pdev->dev.of_node;
		काष्ठा omap_mcbsp_platक्रमm_data *pdata_quirk = pdata;
		पूर्णांक buffer_size;

		pdata = devm_kzalloc(&pdev->dev,
				     माप(काष्ठा omap_mcbsp_platक्रमm_data),
				     GFP_KERNEL);
		अगर (!pdata)
			वापस -ENOMEM;

		स_नकल(pdata, match->data, माप(*pdata));
		अगर (!of_property_पढ़ो_u32(node, "ti,buffer-size", &buffer_size))
			pdata->buffer_size = buffer_size;
		अगर (pdata_quirk)
			pdata->क्रमce_ick_on = pdata_quirk->क्रमce_ick_on;
	पूर्ण अन्यथा अगर (!pdata) अणु
		dev_err(&pdev->dev, "missing platform data.\n");
		वापस -EINVAL;
	पूर्ण
	mcbsp = devm_kzalloc(&pdev->dev, माप(काष्ठा omap_mcbsp), GFP_KERNEL);
	अगर (!mcbsp)
		वापस -ENOMEM;

	mcbsp->id = pdev->id;
	mcbsp->pdata = pdata;
	mcbsp->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, mcbsp);

	ret = omap_mcbsp_init(pdev);
	अगर (ret)
		वापस ret;

	अगर (mcbsp->pdata->reg_size == 2) अणु
		omap_mcbsp_dai.playback.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE;
		omap_mcbsp_dai.capture.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &omap_mcbsp_component,
					      &omap_mcbsp_dai, 1);
	अगर (ret)
		वापस ret;

	वापस sdma_pcm_platक्रमm_रेजिस्टर(&pdev->dev, "tx", "rx");
पूर्ण

अटल पूर्णांक asoc_mcbsp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_mcbsp *mcbsp = platक्रमm_get_drvdata(pdev);

	अगर (mcbsp->pdata->ops && mcbsp->pdata->ops->मुक्त)
		mcbsp->pdata->ops->मुक्त(mcbsp->id);

	अगर (cpu_latency_qos_request_active(&mcbsp->pm_qos_req))
		cpu_latency_qos_हटाओ_request(&mcbsp->pm_qos_req);

	अगर (mcbsp->pdata->buffer_size)
		sysfs_हटाओ_group(&mcbsp->dev->kobj, &additional_attr_group);

	omap_mcbsp_st_cleanup(pdev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver asoc_mcbsp_driver = अणु
	.driver = अणु
			.name = "omap-mcbsp",
			.of_match_table = omap_mcbsp_of_match,
	पूर्ण,

	.probe = asoc_mcbsp_probe,
	.हटाओ = asoc_mcbsp_हटाओ,
पूर्ण;

module_platक्रमm_driver(asoc_mcbsp_driver);

MODULE_AUTHOR("Jarkko Nikula <jarkko.nikula@bitmer.com>");
MODULE_DESCRIPTION("OMAP I2S SoC Interface");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:omap-mcbsp");
