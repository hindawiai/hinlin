<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Freescale SSI ALSA SoC Digital Audio Interface (DAI) driver
//
// Author: Timur Tabi <timur@मुक्तscale.com>
//
// Copyright 2007-2010 Freescale Semiconductor, Inc.
//
// Some notes why imx-pcm-fiq is used instead of DMA on some boards:
//
// The i.MX SSI core has some nasty limitations in AC97 mode. While most
// sane processor venकरोrs have a FIFO per AC97 slot, the i.MX has only
// one FIFO which combines all valid receive slots. We cannot even select
// which slots we want to receive. The WM9712 with which this driver
// was developed with always sends GPIO status data in slot 12 which
// we receive in our (PCM-) data stream. The only chance we have is to
// manually skip this data in the FIQ handler. With sampling rates dअगरferent
// from 48000Hz not every frame has valid receive data, so the ratio
// between pcm data and GPIO status data changes. Our FIQ handler is not
// able to handle this, hence this driver only works with 48000Hz sampling
// rate.
// Reading and writing AC97 रेजिस्टरs is another challenge. The core
// provides us status bits when the पढ़ो रेजिस्टर is updated with *another*
// value. When we पढ़ो the same रेजिस्टर two बार (and the रेजिस्टर still
// contains the same value) these status bits are not set. We work
// around this by not polling these bits but only रुको a fixed delay.

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/clk.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश "fsl_ssi.h"
#समावेश "imx-pcm.h"

/* Define RX and TX to index ssi->regvals array; Can be 0 or 1 only */
#घोषणा RX 0
#घोषणा TX 1

/**
 * FSLSSI_I2S_FORMATS: audio क्रमmats supported by the SSI
 *
 * The SSI has a limitation in that the samples must be in the same byte
 * order as the host CPU.  This is because when multiple bytes are written
 * to the STX रेजिस्टर, the bytes and bits must be written in the same
 * order.  The STX is a shअगरt रेजिस्टर, so all the bits need to be aligned
 * (bit-endianness must match byte-endianness).  Processors typically ग_लिखो
 * the bits within a byte in the same order that the bytes of a word are
 * written in.  So अगर the host CPU is big-endian, then only big-endian
 * samples will be written to STX properly.
 */
#अगर_घोषित __BIG_ENDIAN
#घोषणा FSLSSI_I2S_FORMATS \
	(SNDRV_PCM_FMTBIT_S8 | \
	 SNDRV_PCM_FMTBIT_S16_BE | \
	 SNDRV_PCM_FMTBIT_S18_3BE | \
	 SNDRV_PCM_FMTBIT_S20_3BE | \
	 SNDRV_PCM_FMTBIT_S24_3BE | \
	 SNDRV_PCM_FMTBIT_S24_BE)
#अन्यथा
#घोषणा FSLSSI_I2S_FORMATS \
	(SNDRV_PCM_FMTBIT_S8 | \
	 SNDRV_PCM_FMTBIT_S16_LE | \
	 SNDRV_PCM_FMTBIT_S18_3LE | \
	 SNDRV_PCM_FMTBIT_S20_3LE | \
	 SNDRV_PCM_FMTBIT_S24_3LE | \
	 SNDRV_PCM_FMTBIT_S24_LE)
#पूर्ण_अगर

/*
 * In AC97 mode, TXसूची bit is क्रमced to 0 and TFसूची bit is क्रमced to 1:
 *  - SSI inमाला_दो बाह्यal bit घड़ी and outमाला_दो frame sync घड़ी -- CBM_CFS
 *  - Also have NB_NF to mark these two घड़ीs will not be inverted
 */
#घोषणा FSLSSI_AC97_DAIFMT \
	(SND_SOC_DAIFMT_AC97 | \
	 SND_SOC_DAIFMT_CBM_CFS | \
	 SND_SOC_DAIFMT_NB_NF)

#घोषणा FSLSSI_SIER_DBG_RX_FLAGS \
	(SSI_SIER_RFF0_EN | \
	 SSI_SIER_RLS_EN | \
	 SSI_SIER_RFS_EN | \
	 SSI_SIER_ROE0_EN | \
	 SSI_SIER_RFRC_EN)
#घोषणा FSLSSI_SIER_DBG_TX_FLAGS \
	(SSI_SIER_TFE0_EN | \
	 SSI_SIER_TLS_EN | \
	 SSI_SIER_TFS_EN | \
	 SSI_SIER_TUE0_EN | \
	 SSI_SIER_TFRC_EN)

क्रमागत fsl_ssi_type अणु
	FSL_SSI_MCP8610,
	FSL_SSI_MX21,
	FSL_SSI_MX35,
	FSL_SSI_MX51,
पूर्ण;

काष्ठा fsl_ssi_regvals अणु
	u32 sier;
	u32 srcr;
	u32 stcr;
	u32 scr;
पूर्ण;

अटल bool fsl_ssi_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल REG_SSI_SACCEN:
	हाल REG_SSI_SACCDIS:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल bool fsl_ssi_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल REG_SSI_STX0:
	हाल REG_SSI_STX1:
	हाल REG_SSI_SRX0:
	हाल REG_SSI_SRX1:
	हाल REG_SSI_SISR:
	हाल REG_SSI_SFCSR:
	हाल REG_SSI_SACNT:
	हाल REG_SSI_SACADD:
	हाल REG_SSI_SACDAT:
	हाल REG_SSI_SATAG:
	हाल REG_SSI_SACCST:
	हाल REG_SSI_SOR:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool fsl_ssi_precious_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल REG_SSI_SRX0:
	हाल REG_SSI_SRX1:
	हाल REG_SSI_SISR:
	हाल REG_SSI_SACADD:
	हाल REG_SSI_SACDAT:
	हाल REG_SSI_SATAG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool fsl_ssi_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल REG_SSI_SRX0:
	हाल REG_SSI_SRX1:
	हाल REG_SSI_SACCST:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config fsl_ssi_regconfig = अणु
	.max_रेजिस्टर = REG_SSI_SACCDIS,
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.val_क्रमmat_endian = REGMAP_ENDIAN_NATIVE,
	.num_reg_शेषs_raw = REG_SSI_SACCDIS / माप(uपूर्णांक32_t) + 1,
	.पढ़ोable_reg = fsl_ssi_पढ़ोable_reg,
	.अस्थिर_reg = fsl_ssi_अस्थिर_reg,
	.precious_reg = fsl_ssi_precious_reg,
	.ग_लिखोable_reg = fsl_ssi_ग_लिखोable_reg,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

काष्ठा fsl_ssi_soc_data अणु
	bool imx;
	bool imx21regs; /* imx21-class SSI - no SACCअणुST,EN,DISपूर्ण regs */
	bool offline_config;
	u32 sisr_ग_लिखो_mask;
पूर्ण;

/**
 * काष्ठा fsl_ssi - per-SSI निजी data
 * @regs: Poपूर्णांकer to the regmap रेजिस्टरs
 * @irq: IRQ of this SSI
 * @cpu_dai_drv: CPU DAI driver क्रम this device
 * @dai_fmt: DAI configuration this device is currently used with
 * @streams: Mask of current active streams: BIT(TX) and BIT(RX)
 * @i2s_net: I2S and Network mode configurations of SCR रेजिस्टर
 *           (this is the initial settings based on the DAI क्रमmat)
 * @synchronous: Use synchronous mode - both of TX and RX use STCK and SFCK
 * @use_dma: DMA is used or FIQ with stream filter
 * @use_dual_fअगरo: DMA with support क्रम dual FIFO mode
 * @has_ipg_clk_name: If "ipg" is in the घड़ी name list of device tree
 * @fअगरo_depth: Depth of the SSI FIFOs
 * @slot_width: Width of each DAI slot
 * @slots: Number of slots
 * @regvals: Specअगरic RX/TX रेजिस्टर settings
 * @clk: Clock source to access रेजिस्टर
 * @baudclk: Clock source to generate bit and frame-sync घड़ीs
 * @baudclk_streams: Active streams that are using baudclk
 * @regcache_sfcsr: Cache sfcsr रेजिस्टर value during suspend and resume
 * @regcache_sacnt: Cache sacnt रेजिस्टर value during suspend and resume
 * @dma_params_tx: DMA transmit parameters
 * @dma_params_rx: DMA receive parameters
 * @ssi_phys: physical address of the SSI रेजिस्टरs
 * @fiq_params: FIQ stream filtering parameters
 * @card_pdev: Platक्रमm_device poपूर्णांकer to रेजिस्टर a sound card क्रम PowerPC or
 *             to रेजिस्टर a CODEC platक्रमm device क्रम AC97
 * @card_name: Platक्रमm_device name to रेजिस्टर a sound card क्रम PowerPC or
 *             to रेजिस्टर a CODEC platक्रमm device क्रम AC97
 * @card_idx: The index of SSI to रेजिस्टर a sound card क्रम PowerPC or
 *            to रेजिस्टर a CODEC platक्रमm device क्रम AC97
 * @dbg_stats: Debugging statistics
 * @soc: SoC specअगरic data
 * @dev: Poपूर्णांकer to &pdev->dev
 * @fअगरo_watermark: The FIFO watermark setting. Notअगरies DMA when there are
 *                  @fअगरo_watermark or fewer words in TX fअगरo or
 *                  @fअगरo_watermark or more empty words in RX fअगरo.
 * @dma_maxburst: Max number of words to transfer in one go. So far,
 *                this is always the same as fअगरo_watermark.
 * @ac97_reg_lock: Mutex lock to serialize AC97 रेजिस्टर access operations
 */
काष्ठा fsl_ssi अणु
	काष्ठा regmap *regs;
	पूर्णांक irq;
	काष्ठा snd_soc_dai_driver cpu_dai_drv;

	अचिन्हित पूर्णांक dai_fmt;
	u8 streams;
	u8 i2s_net;
	bool synchronous;
	bool use_dma;
	bool use_dual_fअगरo;
	bool has_ipg_clk_name;
	अचिन्हित पूर्णांक fअगरo_depth;
	अचिन्हित पूर्णांक slot_width;
	अचिन्हित पूर्णांक slots;
	काष्ठा fsl_ssi_regvals regvals[2];

	काष्ठा clk *clk;
	काष्ठा clk *baudclk;
	अचिन्हित पूर्णांक baudclk_streams;

	u32 regcache_sfcsr;
	u32 regcache_sacnt;

	काष्ठा snd_dmaengine_dai_dma_data dma_params_tx;
	काष्ठा snd_dmaengine_dai_dma_data dma_params_rx;
	dma_addr_t ssi_phys;

	काष्ठा imx_pcm_fiq_params fiq_params;

	काष्ठा platक्रमm_device *card_pdev;
	अक्षर card_name[32];
	u32 card_idx;

	काष्ठा fsl_ssi_dbg dbg_stats;

	स्थिर काष्ठा fsl_ssi_soc_data *soc;
	काष्ठा device *dev;

	u32 fअगरo_watermark;
	u32 dma_maxburst;

	काष्ठा mutex ac97_reg_lock;
पूर्ण;

/*
 * SoC specअगरic data
 *
 * Notes:
 * 1) SSI in earlier SoCS has critical bits in control रेजिस्टरs that
 *    cannot be changed after SSI starts running -- a software reset
 *    (set SSIEN to 0) is required to change their values. So adding
 *    an offline_config flag क्रम these SoCs.
 * 2) SDMA is available since imx35. However, imx35 करोes not support
 *    DMA bits changing when SSI is running, so set offline_config.
 * 3) imx51 and later versions support रेजिस्टर configurations when
 *    SSI is running (SSIEN); For these versions, DMA needs to be
 *    configured beक्रमe SSI sends DMA request to aव्योम an undefined
 *    DMA request on the SDMA side.
 */

अटल काष्ठा fsl_ssi_soc_data fsl_ssi_mpc8610 = अणु
	.imx = false,
	.offline_config = true,
	.sisr_ग_लिखो_mask = SSI_SISR_RFRC | SSI_SISR_TFRC |
			   SSI_SISR_ROE0 | SSI_SISR_ROE1 |
			   SSI_SISR_TUE0 | SSI_SISR_TUE1,
पूर्ण;

अटल काष्ठा fsl_ssi_soc_data fsl_ssi_imx21 = अणु
	.imx = true,
	.imx21regs = true,
	.offline_config = true,
	.sisr_ग_लिखो_mask = 0,
पूर्ण;

अटल काष्ठा fsl_ssi_soc_data fsl_ssi_imx35 = अणु
	.imx = true,
	.offline_config = true,
	.sisr_ग_लिखो_mask = SSI_SISR_RFRC | SSI_SISR_TFRC |
			   SSI_SISR_ROE0 | SSI_SISR_ROE1 |
			   SSI_SISR_TUE0 | SSI_SISR_TUE1,
पूर्ण;

अटल काष्ठा fsl_ssi_soc_data fsl_ssi_imx51 = अणु
	.imx = true,
	.offline_config = false,
	.sisr_ग_लिखो_mask = SSI_SISR_ROE0 | SSI_SISR_ROE1 |
			   SSI_SISR_TUE0 | SSI_SISR_TUE1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id fsl_ssi_ids[] = अणु
	अणु .compatible = "fsl,mpc8610-ssi", .data = &fsl_ssi_mpc8610 पूर्ण,
	अणु .compatible = "fsl,imx51-ssi", .data = &fsl_ssi_imx51 पूर्ण,
	अणु .compatible = "fsl,imx35-ssi", .data = &fsl_ssi_imx35 पूर्ण,
	अणु .compatible = "fsl,imx21-ssi", .data = &fsl_ssi_imx21 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_ssi_ids);

अटल bool fsl_ssi_is_ac97(काष्ठा fsl_ssi *ssi)
अणु
	वापस (ssi->dai_fmt & SND_SOC_DAIFMT_FORMAT_MASK) ==
		SND_SOC_DAIFMT_AC97;
पूर्ण

अटल bool fsl_ssi_is_i2s_master(काष्ठा fsl_ssi *ssi)
अणु
	वापस (ssi->dai_fmt & SND_SOC_DAIFMT_MASTER_MASK) ==
		SND_SOC_DAIFMT_CBS_CFS;
पूर्ण

अटल bool fsl_ssi_is_i2s_cbm_cfs(काष्ठा fsl_ssi *ssi)
अणु
	वापस (ssi->dai_fmt & SND_SOC_DAIFMT_MASTER_MASK) ==
		SND_SOC_DAIFMT_CBM_CFS;
पूर्ण

/**
 * fsl_ssi_isr - Interrupt handler to gather states
 * @irq: irq number
 * @dev_id: context
 */
अटल irqवापस_t fsl_ssi_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा fsl_ssi *ssi = dev_id;
	काष्ठा regmap *regs = ssi->regs;
	u32 sisr, sisr2;

	regmap_पढ़ो(regs, REG_SSI_SISR, &sisr);

	sisr2 = sisr & ssi->soc->sisr_ग_लिखो_mask;
	/* Clear the bits that we set */
	अगर (sisr2)
		regmap_ग_लिखो(regs, REG_SSI_SISR, sisr2);

	fsl_ssi_dbg_isr(&ssi->dbg_stats, sisr);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * fsl_ssi_config_enable - Set SCR, SIER, STCR and SRCR रेजिस्टरs with
 * cached values in regvals
 * @ssi: SSI context
 * @tx: direction
 *
 * Notes:
 * 1) For offline_config SoCs, enable all necessary bits of both streams
 *    when 1st stream starts, even अगर the opposite stream will not start
 * 2) It also clears FIFO beक्रमe setting regvals; SOR is safe to set online
 */
अटल व्योम fsl_ssi_config_enable(काष्ठा fsl_ssi *ssi, bool tx)
अणु
	काष्ठा fsl_ssi_regvals *vals = ssi->regvals;
	पूर्णांक dir = tx ? TX : RX;
	u32 sier, srcr, stcr;

	/* Clear dirty data in the FIFO; It also prevents channel slipping */
	regmap_update_bits(ssi->regs, REG_SSI_SOR,
			   SSI_SOR_xX_CLR(tx), SSI_SOR_xX_CLR(tx));

	/*
	 * On offline_config SoCs, SxCR and SIER are alपढ़ोy configured when
	 * the previous stream started. So skip all SxCR and SIER settings
	 * to prevent online reconfigurations, then jump to set SCR directly
	 */
	अगर (ssi->soc->offline_config && ssi->streams)
		जाओ enable_scr;

	अगर (ssi->soc->offline_config) अणु
		/*
		 * Online reconfiguration not supported, so enable all bits क्रम
		 * both streams at once to aव्योम necessity of reconfigurations
		 */
		srcr = vals[RX].srcr | vals[TX].srcr;
		stcr = vals[RX].stcr | vals[TX].stcr;
		sier = vals[RX].sier | vals[TX].sier;
	पूर्ण अन्यथा अणु
		/* Otherwise, only set bits क्रम the current stream */
		srcr = vals[dir].srcr;
		stcr = vals[dir].stcr;
		sier = vals[dir].sier;
	पूर्ण

	/* Configure SRCR, STCR and SIER at once */
	regmap_update_bits(ssi->regs, REG_SSI_SRCR, srcr, srcr);
	regmap_update_bits(ssi->regs, REG_SSI_STCR, stcr, stcr);
	regmap_update_bits(ssi->regs, REG_SSI_SIER, sier, sier);

enable_scr:
	/*
	 * Start DMA beक्रमe setting TE to aव्योम FIFO underrun
	 * which may cause a channel slip or a channel swap
	 *
	 * TODO: FIQ हालs might also need this upon testing
	 */
	अगर (ssi->use_dma && tx) अणु
		पूर्णांक try = 100;
		u32 sfcsr;

		/* Enable SSI first to send TX DMA request */
		regmap_update_bits(ssi->regs, REG_SSI_SCR,
				   SSI_SCR_SSIEN, SSI_SCR_SSIEN);

		/* Busy रुको until TX FIFO not empty -- DMA working */
		करो अणु
			regmap_पढ़ो(ssi->regs, REG_SSI_SFCSR, &sfcsr);
			अगर (SSI_SFCSR_TFCNT0(sfcsr))
				अवरोध;
		पूर्ण जबतक (--try);

		/* FIFO still empty -- something might be wrong */
		अगर (!SSI_SFCSR_TFCNT0(sfcsr))
			dev_warn(ssi->dev, "Timeout waiting TX FIFO filling\n");
	पूर्ण
	/* Enable all reमुख्यing bits in SCR */
	regmap_update_bits(ssi->regs, REG_SSI_SCR,
			   vals[dir].scr, vals[dir].scr);

	/* Log the enabled stream to the mask */
	ssi->streams |= BIT(dir);
पूर्ण

/*
 * Exclude bits that are used by the opposite stream
 *
 * When both streams are active, disabling some bits क्रम the current stream
 * might अवरोध the other stream अगर these bits are used by it.
 *
 * @vals : regvals of the current stream
 * @avals: regvals of the opposite stream
 * @aactive: active state of the opposite stream
 *
 *  1) XOR vals and avals to get the dअगरferences अगर the other stream is active;
 *     Otherwise, वापस current vals अगर the other stream is not active
 *  2) AND the result of 1) with the current vals
 */
#घोषणा _ssi_xor_shared_bits(vals, avals, aactive) \
	((vals) ^ ((avals) * (aactive)))

#घोषणा ssi_excl_shared_bits(vals, avals, aactive) \
	((vals) & _ssi_xor_shared_bits(vals, avals, aactive))

/**
 * fsl_ssi_config_disable - Unset SCR, SIER, STCR and SRCR रेजिस्टरs
 * with cached values in regvals
 * @ssi: SSI context
 * @tx: direction
 *
 * Notes:
 * 1) For offline_config SoCs, to aव्योम online reconfigurations, disable all
 *    bits of both streams at once when the last stream is पात to end
 * 2) It also clears FIFO after unsetting regvals; SOR is safe to set online
 */
अटल व्योम fsl_ssi_config_disable(काष्ठा fsl_ssi *ssi, bool tx)
अणु
	काष्ठा fsl_ssi_regvals *vals, *avals;
	u32 sier, srcr, stcr, scr;
	पूर्णांक adir = tx ? RX : TX;
	पूर्णांक dir = tx ? TX : RX;
	bool aactive;

	/* Check अगर the opposite stream is active */
	aactive = ssi->streams & BIT(adir);

	vals = &ssi->regvals[dir];

	/* Get regvals of the opposite stream to keep opposite stream safe */
	avals = &ssi->regvals[adir];

	/*
	 * To keep the other stream safe, exclude shared bits between
	 * both streams, and get safe bits to disable current stream
	 */
	scr = ssi_excl_shared_bits(vals->scr, avals->scr, aactive);

	/* Disable safe bits of SCR रेजिस्टर क्रम the current stream */
	regmap_update_bits(ssi->regs, REG_SSI_SCR, scr, 0);

	/* Log the disabled stream to the mask */
	ssi->streams &= ~BIT(dir);

	/*
	 * On offline_config SoCs, अगर the other stream is active, skip
	 * SxCR and SIER settings to prevent online reconfigurations
	 */
	अगर (ssi->soc->offline_config && aactive)
		जाओ fअगरo_clear;

	अगर (ssi->soc->offline_config) अणु
		/* Now there is only current stream active, disable all bits */
		srcr = vals->srcr | avals->srcr;
		stcr = vals->stcr | avals->stcr;
		sier = vals->sier | avals->sier;
	पूर्ण अन्यथा अणु
		/*
		 * To keep the other stream safe, exclude shared bits between
		 * both streams, and get safe bits to disable current stream
		 */
		sier = ssi_excl_shared_bits(vals->sier, avals->sier, aactive);
		srcr = ssi_excl_shared_bits(vals->srcr, avals->srcr, aactive);
		stcr = ssi_excl_shared_bits(vals->stcr, avals->stcr, aactive);
	पूर्ण

	/* Clear configurations of SRCR, STCR and SIER at once */
	regmap_update_bits(ssi->regs, REG_SSI_SRCR, srcr, 0);
	regmap_update_bits(ssi->regs, REG_SSI_STCR, stcr, 0);
	regmap_update_bits(ssi->regs, REG_SSI_SIER, sier, 0);

fअगरo_clear:
	/* Clear reमुख्यing data in the FIFO */
	regmap_update_bits(ssi->regs, REG_SSI_SOR,
			   SSI_SOR_xX_CLR(tx), SSI_SOR_xX_CLR(tx));
पूर्ण

अटल व्योम fsl_ssi_tx_ac97_saccst_setup(काष्ठा fsl_ssi *ssi)
अणु
	काष्ठा regmap *regs = ssi->regs;

	/* no SACCअणुST,EN,DISपूर्ण regs on imx21-class SSI */
	अगर (!ssi->soc->imx21regs) अणु
		/* Disable all channel slots */
		regmap_ग_लिखो(regs, REG_SSI_SACCDIS, 0xff);
		/* Enable slots 3 & 4 -- PCM Playback Left & Right channels */
		regmap_ग_लिखो(regs, REG_SSI_SACCEN, 0x300);
	पूर्ण
पूर्ण

/**
 * fsl_ssi_setup_regvals - Cache critical bits of SIER, SRCR, STCR and
 * SCR to later set them safely
 * @ssi: SSI context
 */
अटल व्योम fsl_ssi_setup_regvals(काष्ठा fsl_ssi *ssi)
अणु
	काष्ठा fsl_ssi_regvals *vals = ssi->regvals;

	vals[RX].sier = SSI_SIER_RFF0_EN | FSLSSI_SIER_DBG_RX_FLAGS;
	vals[RX].srcr = SSI_SRCR_RFEN0;
	vals[RX].scr = SSI_SCR_SSIEN | SSI_SCR_RE;
	vals[TX].sier = SSI_SIER_TFE0_EN | FSLSSI_SIER_DBG_TX_FLAGS;
	vals[TX].stcr = SSI_STCR_TFEN0;
	vals[TX].scr = SSI_SCR_SSIEN | SSI_SCR_TE;

	/* AC97 has alपढ़ोy enabled SSIEN, RE and TE, so ignore them */
	अगर (fsl_ssi_is_ac97(ssi))
		vals[RX].scr = vals[TX].scr = 0;

	अगर (ssi->use_dual_fअगरo) अणु
		vals[RX].srcr |= SSI_SRCR_RFEN1;
		vals[TX].stcr |= SSI_STCR_TFEN1;
	पूर्ण

	अगर (ssi->use_dma) अणु
		vals[RX].sier |= SSI_SIER_RDMAE;
		vals[TX].sier |= SSI_SIER_TDMAE;
	पूर्ण अन्यथा अणु
		vals[RX].sier |= SSI_SIER_RIE;
		vals[TX].sier |= SSI_SIER_TIE;
	पूर्ण
पूर्ण

अटल व्योम fsl_ssi_setup_ac97(काष्ठा fsl_ssi *ssi)
अणु
	काष्ठा regmap *regs = ssi->regs;

	/* Setup the घड़ी control रेजिस्टर */
	regmap_ग_लिखो(regs, REG_SSI_STCCR, SSI_SxCCR_WL(17) | SSI_SxCCR_DC(13));
	regmap_ग_लिखो(regs, REG_SSI_SRCCR, SSI_SxCCR_WL(17) | SSI_SxCCR_DC(13));

	/* Enable AC97 mode and startup the SSI */
	regmap_ग_लिखो(regs, REG_SSI_SACNT, SSI_SACNT_AC97EN | SSI_SACNT_FV);

	/* AC97 has to communicate with codec beक्रमe starting a stream */
	regmap_update_bits(regs, REG_SSI_SCR,
			   SSI_SCR_SSIEN | SSI_SCR_TE | SSI_SCR_RE,
			   SSI_SCR_SSIEN | SSI_SCR_TE | SSI_SCR_RE);

	regmap_ग_लिखो(regs, REG_SSI_SOR, SSI_SOR_WAIT(3));
पूर्ण

अटल पूर्णांक fsl_ssi_startup(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा fsl_ssi *ssi = snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));
	पूर्णांक ret;

	ret = clk_prepare_enable(ssi->clk);
	अगर (ret)
		वापस ret;

	/*
	 * When using dual fअगरo mode, it is safer to ensure an even period
	 * size. If appearing to an odd number जबतक DMA always starts its
	 * task from fअगरo0, fअगरo1 would be neglected at the end of each
	 * period. But SSI would still access fअगरo1 with an invalid data.
	 */
	अगर (ssi->use_dual_fअगरo)
		snd_pcm_hw_स्थिरraपूर्णांक_step(substream->runसमय, 0,
					   SNDRV_PCM_HW_PARAM_PERIOD_SIZE, 2);

	वापस 0;
पूर्ण

अटल व्योम fsl_ssi_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा fsl_ssi *ssi = snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));

	clk_disable_unprepare(ssi->clk);
पूर्ण

/**
 * fsl_ssi_set_bclk - Configure Digital Audio Interface bit घड़ी
 * @substream: ASoC substream
 * @dai: poपूर्णांकer to DAI
 * @hw_params: poपूर्णांकers to hw_params
 *
 * Notes: This function can be only called when using SSI as DAI master
 *
 * Quick inकाष्ठाion क्रम parameters:
 * freq: Output BCLK frequency = samplerate * slots * slot_width
 *       (In 2-channel I2S Master mode, slot_width is fixed 32)
 */
अटल पूर्णांक fsl_ssi_set_bclk(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_soc_dai *dai,
			    काष्ठा snd_pcm_hw_params *hw_params)
अणु
	bool tx2, tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	काष्ठा fsl_ssi *ssi = snd_soc_dai_get_drvdata(dai);
	काष्ठा regmap *regs = ssi->regs;
	u32 pm = 999, भाग2, psr, stccr, mask, afreq, factor, i;
	अचिन्हित दीर्घ clkrate, baudrate, पंचांगprate;
	अचिन्हित पूर्णांक channels = params_channels(hw_params);
	अचिन्हित पूर्णांक slot_width = params_width(hw_params);
	अचिन्हित पूर्णांक slots = 2;
	u64 sub, savesub = 100000;
	अचिन्हित पूर्णांक freq;
	bool baudclk_is_used;
	पूर्णांक ret;

	/* Override slots and slot_width अगर being specअगरically set... */
	अगर (ssi->slots)
		slots = ssi->slots;
	अगर (ssi->slot_width)
		slot_width = ssi->slot_width;

	/* ...but क्रमce 32 bits क्रम stereo audio using I2S Master Mode */
	अगर (channels == 2 &&
	    (ssi->i2s_net & SSI_SCR_I2S_MODE_MASK) == SSI_SCR_I2S_MODE_MASTER)
		slot_width = 32;

	/* Generate bit घड़ी based on the slot number and slot width */
	freq = slots * slot_width * params_rate(hw_params);

	/* Don't apply it to any non-baudclk circumstance */
	अगर (IS_ERR(ssi->baudclk))
		वापस -EINVAL;

	/*
	 * Hardware limitation: The bclk rate must be
	 * never greater than 1/5 IPG घड़ी rate
	 */
	अगर (freq * 5 > clk_get_rate(ssi->clk)) अणु
		dev_err(dai->dev, "bitclk > ipgclk / 5\n");
		वापस -EINVAL;
	पूर्ण

	baudclk_is_used = ssi->baudclk_streams & ~(BIT(substream->stream));

	/* It should be alपढ़ोy enough to भागide घड़ी by setting pm alone */
	psr = 0;
	भाग2 = 0;

	factor = (भाग2 + 1) * (7 * psr + 1) * 2;

	क्रम (i = 0; i < 255; i++) अणु
		पंचांगprate = freq * factor * (i + 1);

		अगर (baudclk_is_used)
			clkrate = clk_get_rate(ssi->baudclk);
		अन्यथा
			clkrate = clk_round_rate(ssi->baudclk, पंचांगprate);

		clkrate /= factor;
		afreq = clkrate / (i + 1);

		अगर (freq == afreq)
			sub = 0;
		अन्यथा अगर (freq / afreq == 1)
			sub = freq - afreq;
		अन्यथा अगर (afreq / freq == 1)
			sub = afreq - freq;
		अन्यथा
			जारी;

		/* Calculate the fraction */
		sub *= 100000;
		करो_भाग(sub, freq);

		अगर (sub < savesub && !(i == 0)) अणु
			baudrate = पंचांगprate;
			savesub = sub;
			pm = i;
		पूर्ण

		/* We are lucky */
		अगर (savesub == 0)
			अवरोध;
	पूर्ण

	/* No proper pm found अगर it is still reमुख्यing the initial value */
	अगर (pm == 999) अणु
		dev_err(dai->dev, "failed to handle the required sysclk\n");
		वापस -EINVAL;
	पूर्ण

	stccr = SSI_SxCCR_PM(pm + 1);
	mask = SSI_SxCCR_PM_MASK | SSI_SxCCR_DIV2 | SSI_SxCCR_PSR;

	/* STCCR is used क्रम RX in synchronous mode */
	tx2 = tx || ssi->synchronous;
	regmap_update_bits(regs, REG_SSI_SxCCR(tx2), mask, stccr);

	अगर (!baudclk_is_used) अणु
		ret = clk_set_rate(ssi->baudclk, baudrate);
		अगर (ret) अणु
			dev_err(dai->dev, "failed to set baudclk rate\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * fsl_ssi_hw_params - Configure SSI based on PCM hardware parameters
 * @substream: ASoC substream
 * @hw_params: poपूर्णांकers to hw_params
 * @dai: poपूर्णांकer to DAI
 *
 * Notes:
 * 1) SxCCR.WL bits are critical bits that require SSI to be temporarily
 *    disabled on offline_config SoCs. Even क्रम online configurable SoCs
 *    running in synchronous mode (both TX and RX use STCCR), it is not
 *    safe to re-configure them when both two streams start running.
 * 2) SxCCR.PM, SxCCR.DIV2 and SxCCR.PSR bits will be configured in the
 *    fsl_ssi_set_bclk() अगर SSI is the DAI घड़ी master.
 */
अटल पूर्णांक fsl_ssi_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *hw_params,
			     काष्ठा snd_soc_dai *dai)
अणु
	bool tx2, tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	काष्ठा fsl_ssi *ssi = snd_soc_dai_get_drvdata(dai);
	काष्ठा regmap *regs = ssi->regs;
	अचिन्हित पूर्णांक channels = params_channels(hw_params);
	अचिन्हित पूर्णांक sample_size = params_width(hw_params);
	u32 wl = SSI_SxCCR_WL(sample_size);
	पूर्णांक ret;

	अगर (fsl_ssi_is_i2s_master(ssi)) अणु
		ret = fsl_ssi_set_bclk(substream, dai, hw_params);
		अगर (ret)
			वापस ret;

		/* Do not enable the घड़ी अगर it is alपढ़ोy enabled */
		अगर (!(ssi->baudclk_streams & BIT(substream->stream))) अणु
			ret = clk_prepare_enable(ssi->baudclk);
			अगर (ret)
				वापस ret;

			ssi->baudclk_streams |= BIT(substream->stream);
		पूर्ण
	पूर्ण

	/*
	 * SSI is properly configured अगर it is enabled and running in
	 * the synchronous mode; Note that AC97 mode is an exception
	 * that should set separate configurations क्रम STCCR and SRCCR
	 * despite running in the synchronous mode.
	 */
	अगर (ssi->streams && ssi->synchronous)
		वापस 0;

	अगर (!fsl_ssi_is_ac97(ssi)) अणु
		/*
		 * Keep the ssi->i2s_net पूर्णांकact जबतक having a local variable
		 * to override settings क्रम special use हालs. Otherwise, the
		 * ssi->i2s_net will lose the settings क्रम regular use हालs.
		 */
		u8 i2s_net = ssi->i2s_net;

		/* Normal + Network mode to send 16-bit data in 32-bit frames */
		अगर (fsl_ssi_is_i2s_cbm_cfs(ssi) && sample_size == 16)
			i2s_net = SSI_SCR_I2S_MODE_NORMAL | SSI_SCR_NET;

		/* Use Normal mode to send mono data at 1st slot of 2 slots */
		अगर (channels == 1)
			i2s_net = SSI_SCR_I2S_MODE_NORMAL;

		regmap_update_bits(regs, REG_SSI_SCR,
				   SSI_SCR_I2S_NET_MASK, i2s_net);
	पूर्ण

	/* In synchronous mode, the SSI uses STCCR क्रम capture */
	tx2 = tx || ssi->synchronous;
	regmap_update_bits(regs, REG_SSI_SxCCR(tx2), SSI_SxCCR_WL_MASK, wl);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_ssi_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा fsl_ssi *ssi = snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));

	अगर (fsl_ssi_is_i2s_master(ssi) &&
	    ssi->baudclk_streams & BIT(substream->stream)) अणु
		clk_disable_unprepare(ssi->baudclk);
		ssi->baudclk_streams &= ~BIT(substream->stream);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक _fsl_ssi_set_dai_fmt(काष्ठा fsl_ssi *ssi, अचिन्हित पूर्णांक fmt)
अणु
	u32 strcr = 0, scr = 0, stcr, srcr, mask;
	अचिन्हित पूर्णांक slots;

	ssi->dai_fmt = fmt;

	/* Synchronize frame sync घड़ी क्रम TE to aव्योम data slipping */
	scr |= SSI_SCR_SYNC_TX_FS;

	/* Set to शेष shअगरting settings: LSB_ALIGNED */
	strcr |= SSI_STCR_TXBIT0;

	/* Use Network mode as शेष */
	ssi->i2s_net = SSI_SCR_NET;
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
		हाल SND_SOC_DAIFMT_CBS_CFS:
			अगर (IS_ERR(ssi->baudclk)) अणु
				dev_err(ssi->dev,
					"missing baudclk for master mode\n");
				वापस -EINVAL;
			पूर्ण
			fallthrough;
		हाल SND_SOC_DAIFMT_CBM_CFS:
			ssi->i2s_net |= SSI_SCR_I2S_MODE_MASTER;
			अवरोध;
		हाल SND_SOC_DAIFMT_CBM_CFM:
			ssi->i2s_net |= SSI_SCR_I2S_MODE_SLAVE;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		slots = ssi->slots ? : 2;
		regmap_update_bits(ssi->regs, REG_SSI_STCCR,
				   SSI_SxCCR_DC_MASK, SSI_SxCCR_DC(slots));
		regmap_update_bits(ssi->regs, REG_SSI_SRCCR,
				   SSI_SxCCR_DC_MASK, SSI_SxCCR_DC(slots));

		/* Data on rising edge of bclk, frame low, 1clk beक्रमe data */
		strcr |= SSI_STCR_TFSI | SSI_STCR_TSCKP | SSI_STCR_TEFS;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		/* Data on rising edge of bclk, frame high */
		strcr |= SSI_STCR_TSCKP;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		/* Data on rising edge of bclk, frame high, 1clk beक्रमe data */
		strcr |= SSI_STCR_TFSL | SSI_STCR_TSCKP | SSI_STCR_TEFS;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		/* Data on rising edge of bclk, frame high */
		strcr |= SSI_STCR_TFSL | SSI_STCR_TSCKP;
		अवरोध;
	हाल SND_SOC_DAIFMT_AC97:
		/* Data on falling edge of bclk, frame high, 1clk beक्रमe data */
		strcr |= SSI_STCR_TEFS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	scr |= ssi->i2s_net;

	/* DAI घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		/* Nothing to करो क्रम both normal हालs */
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		/* Invert bit घड़ी */
		strcr ^= SSI_STCR_TSCKP;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		/* Invert frame घड़ी */
		strcr ^= SSI_STCR_TFSI;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		/* Invert both घड़ीs */
		strcr ^= SSI_STCR_TSCKP;
		strcr ^= SSI_STCR_TFSI;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* DAI घड़ी master masks */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		/* Output bit and frame sync घड़ीs */
		strcr |= SSI_STCR_TFसूची | SSI_STCR_TXसूची;
		scr |= SSI_SCR_SYS_CLK_EN;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		/* Input bit or frame sync घड़ीs */
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		/* Input bit घड़ी but output frame sync घड़ी */
		strcr |= SSI_STCR_TFसूची;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	stcr = strcr;
	srcr = strcr;

	/* Set SYN mode and clear RXसूची bit when using SYN or AC97 mode */
	अगर (ssi->synchronous || fsl_ssi_is_ac97(ssi)) अणु
		srcr &= ~SSI_SRCR_RXसूची;
		scr |= SSI_SCR_SYN;
	पूर्ण

	mask = SSI_STCR_TFसूची | SSI_STCR_TXसूची | SSI_STCR_TSCKP |
	       SSI_STCR_TFSL | SSI_STCR_TFSI | SSI_STCR_TEFS | SSI_STCR_TXBIT0;

	regmap_update_bits(ssi->regs, REG_SSI_STCR, mask, stcr);
	regmap_update_bits(ssi->regs, REG_SSI_SRCR, mask, srcr);

	mask = SSI_SCR_SYNC_TX_FS | SSI_SCR_I2S_MODE_MASK |
	       SSI_SCR_SYS_CLK_EN | SSI_SCR_SYN;
	regmap_update_bits(ssi->regs, REG_SSI_SCR, mask, scr);

	वापस 0;
पूर्ण

/**
 * fsl_ssi_set_dai_fmt - Configure Digital Audio Interface (DAI) Format
 * @dai: poपूर्णांकer to DAI
 * @fmt: क्रमmat mask
 */
अटल पूर्णांक fsl_ssi_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा fsl_ssi *ssi = snd_soc_dai_get_drvdata(dai);

	/* AC97 configured DAIFMT earlier in the probe() */
	अगर (fsl_ssi_is_ac97(ssi))
		वापस 0;

	वापस _fsl_ssi_set_dai_fmt(ssi, fmt);
पूर्ण

/**
 * fsl_ssi_set_dai_tdm_slot - Set TDM slot number and slot width
 * @dai: poपूर्णांकer to DAI
 * @tx_mask: mask क्रम TX
 * @rx_mask: mask क्रम RX
 * @slots: number of slots
 * @slot_width: number of bits per slot
 */
अटल पूर्णांक fsl_ssi_set_dai_tdm_slot(काष्ठा snd_soc_dai *dai, u32 tx_mask,
				    u32 rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा fsl_ssi *ssi = snd_soc_dai_get_drvdata(dai);
	काष्ठा regmap *regs = ssi->regs;
	u32 val;

	/* The word length should be 8, 10, 12, 16, 18, 20, 22 or 24 */
	अगर (slot_width & 1 || slot_width < 8 || slot_width > 24) अणु
		dev_err(dai->dev, "invalid slot width: %d\n", slot_width);
		वापस -EINVAL;
	पूर्ण

	/* The slot number should be >= 2 अगर using Network mode or I2S mode */
	अगर (ssi->i2s_net && slots < 2) अणु
		dev_err(dai->dev, "slot number should be >= 2 in I2S or NET\n");
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(regs, REG_SSI_STCCR,
			   SSI_SxCCR_DC_MASK, SSI_SxCCR_DC(slots));
	regmap_update_bits(regs, REG_SSI_SRCCR,
			   SSI_SxCCR_DC_MASK, SSI_SxCCR_DC(slots));

	/* Save the SCR रेजिस्टर value */
	regmap_पढ़ो(regs, REG_SSI_SCR, &val);
	/* Temporarily enable SSI to allow SxMSKs to be configurable */
	regmap_update_bits(regs, REG_SSI_SCR, SSI_SCR_SSIEN, SSI_SCR_SSIEN);

	regmap_ग_लिखो(regs, REG_SSI_STMSK, ~tx_mask);
	regmap_ग_लिखो(regs, REG_SSI_SRMSK, ~rx_mask);

	/* Restore the value of SSIEN bit */
	regmap_update_bits(regs, REG_SSI_SCR, SSI_SCR_SSIEN, val);

	ssi->slot_width = slot_width;
	ssi->slots = slots;

	वापस 0;
पूर्ण

/**
 * fsl_ssi_trigger - Start or stop SSI and corresponding DMA transaction.
 * @substream: ASoC substream
 * @cmd: trigger command
 * @dai: poपूर्णांकer to DAI
 *
 * The DMA channel is in बाह्यal master start and छोड़ो mode, which
 * means the SSI completely controls the flow of data.
 */
अटल पूर्णांक fsl_ssi_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा fsl_ssi *ssi = snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		/*
		 * SACCST might be modअगरied via AC Link by a CODEC अगर it sends
		 * extra bits in their SLOTREQ requests, which'll accidentally
		 * send valid data to slots other than normal playback slots.
		 *
		 * To be safe, configure SACCST right beक्रमe TX starts.
		 */
		अगर (tx && fsl_ssi_is_ac97(ssi))
			fsl_ssi_tx_ac97_saccst_setup(ssi);
		fsl_ssi_config_enable(ssi, tx);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		fsl_ssi_config_disable(ssi, tx);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_ssi_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsl_ssi *ssi = snd_soc_dai_get_drvdata(dai);

	अगर (ssi->soc->imx && ssi->use_dma)
		snd_soc_dai_init_dma_data(dai, &ssi->dma_params_tx,
					  &ssi->dma_params_rx);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops fsl_ssi_dai_ops = अणु
	.startup = fsl_ssi_startup,
	.shutकरोwn = fsl_ssi_shutकरोwn,
	.hw_params = fsl_ssi_hw_params,
	.hw_मुक्त = fsl_ssi_hw_मुक्त,
	.set_fmt = fsl_ssi_set_dai_fmt,
	.set_tdm_slot = fsl_ssi_set_dai_tdm_slot,
	.trigger = fsl_ssi_trigger,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver fsl_ssi_dai_ढाँचा = अणु
	.probe = fsl_ssi_dai_probe,
	.playback = अणु
		.stream_name = "CPU-Playback",
		.channels_min = 1,
		.channels_max = 32,
		.rates = SNDRV_PCM_RATE_CONTINUOUS,
		.क्रमmats = FSLSSI_I2S_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "CPU-Capture",
		.channels_min = 1,
		.channels_max = 32,
		.rates = SNDRV_PCM_RATE_CONTINUOUS,
		.क्रमmats = FSLSSI_I2S_FORMATS,
	पूर्ण,
	.ops = &fsl_ssi_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver fsl_ssi_component = अणु
	.name = "fsl-ssi",
पूर्ण;

अटल काष्ठा snd_soc_dai_driver fsl_ssi_ac97_dai = अणु
	.symmetric_channels = 1,
	.probe = fsl_ssi_dai_probe,
	.playback = अणु
		.stream_name = "AC97 Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16 | SNDRV_PCM_FMTBIT_S20,
	पूर्ण,
	.capture = अणु
		.stream_name = "AC97 Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_48000,
		/* 16-bit capture is broken (errata ERR003778) */
		.क्रमmats = SNDRV_PCM_FMTBIT_S20,
	पूर्ण,
	.ops = &fsl_ssi_dai_ops,
पूर्ण;

अटल काष्ठा fsl_ssi *fsl_ac97_data;

अटल व्योम fsl_ssi_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg,
			       अचिन्हित लघु val)
अणु
	काष्ठा regmap *regs = fsl_ac97_data->regs;
	अचिन्हित पूर्णांक lreg;
	अचिन्हित पूर्णांक lval;
	पूर्णांक ret;

	अगर (reg > 0x7f)
		वापस;

	mutex_lock(&fsl_ac97_data->ac97_reg_lock);

	ret = clk_prepare_enable(fsl_ac97_data->clk);
	अगर (ret) अणु
		pr_err("ac97 write clk_prepare_enable failed: %d\n",
			ret);
		जाओ ret_unlock;
	पूर्ण

	lreg = reg <<  12;
	regmap_ग_लिखो(regs, REG_SSI_SACADD, lreg);

	lval = val << 4;
	regmap_ग_लिखो(regs, REG_SSI_SACDAT, lval);

	regmap_update_bits(regs, REG_SSI_SACNT,
			   SSI_SACNT_RDWR_MASK, SSI_SACNT_WR);
	udelay(100);

	clk_disable_unprepare(fsl_ac97_data->clk);

ret_unlock:
	mutex_unlock(&fsl_ac97_data->ac97_reg_lock);
पूर्ण

अटल अचिन्हित लघु fsl_ssi_ac97_पढ़ो(काष्ठा snd_ac97 *ac97,
					अचिन्हित लघु reg)
अणु
	काष्ठा regmap *regs = fsl_ac97_data->regs;
	अचिन्हित लघु val = 0;
	u32 reg_val;
	अचिन्हित पूर्णांक lreg;
	पूर्णांक ret;

	mutex_lock(&fsl_ac97_data->ac97_reg_lock);

	ret = clk_prepare_enable(fsl_ac97_data->clk);
	अगर (ret) अणु
		pr_err("ac97 read clk_prepare_enable failed: %d\n", ret);
		जाओ ret_unlock;
	पूर्ण

	lreg = (reg & 0x7f) <<  12;
	regmap_ग_लिखो(regs, REG_SSI_SACADD, lreg);
	regmap_update_bits(regs, REG_SSI_SACNT,
			   SSI_SACNT_RDWR_MASK, SSI_SACNT_RD);

	udelay(100);

	regmap_पढ़ो(regs, REG_SSI_SACDAT, &reg_val);
	val = (reg_val >> 4) & 0xffff;

	clk_disable_unprepare(fsl_ac97_data->clk);

ret_unlock:
	mutex_unlock(&fsl_ac97_data->ac97_reg_lock);
	वापस val;
पूर्ण

अटल काष्ठा snd_ac97_bus_ops fsl_ssi_ac97_ops = अणु
	.पढ़ो = fsl_ssi_ac97_पढ़ो,
	.ग_लिखो = fsl_ssi_ac97_ग_लिखो,
पूर्ण;

/**
 * fsl_ssi_hw_init - Initialize SSI रेजिस्टरs
 * @ssi: SSI context
 */
अटल पूर्णांक fsl_ssi_hw_init(काष्ठा fsl_ssi *ssi)
अणु
	u32 wm = ssi->fअगरo_watermark;

	/* Initialize regvals */
	fsl_ssi_setup_regvals(ssi);

	/* Set watermarks */
	regmap_ग_लिखो(ssi->regs, REG_SSI_SFCSR,
		     SSI_SFCSR_TFWM0(wm) | SSI_SFCSR_RFWM0(wm) |
		     SSI_SFCSR_TFWM1(wm) | SSI_SFCSR_RFWM1(wm));

	/* Enable Dual FIFO mode */
	अगर (ssi->use_dual_fअगरo)
		regmap_update_bits(ssi->regs, REG_SSI_SCR,
				   SSI_SCR_TCH_EN, SSI_SCR_TCH_EN);

	/* AC97 should start earlier to communicate with CODECs */
	अगर (fsl_ssi_is_ac97(ssi)) अणु
		_fsl_ssi_set_dai_fmt(ssi, ssi->dai_fmt);
		fsl_ssi_setup_ac97(ssi);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * fsl_ssi_hw_clean - Clear SSI रेजिस्टरs
 * @ssi: SSI context
 */
अटल व्योम fsl_ssi_hw_clean(काष्ठा fsl_ssi *ssi)
अणु
	/* Disable रेजिस्टरs क्रम AC97 */
	अगर (fsl_ssi_is_ac97(ssi)) अणु
		/* Disable TE and RE bits first */
		regmap_update_bits(ssi->regs, REG_SSI_SCR,
				   SSI_SCR_TE | SSI_SCR_RE, 0);
		/* Disable AC97 mode */
		regmap_ग_लिखो(ssi->regs, REG_SSI_SACNT, 0);
		/* Unset WAIT bits */
		regmap_ग_लिखो(ssi->regs, REG_SSI_SOR, 0);
		/* Disable SSI -- software reset */
		regmap_update_bits(ssi->regs, REG_SSI_SCR, SSI_SCR_SSIEN, 0);
	पूर्ण
पूर्ण

/*
 * Make every अक्षरacter in a string lower-हाल
 */
अटल व्योम make_lowerहाल(अक्षर *s)
अणु
	अगर (!s)
		वापस;
	क्रम (; *s; s++)
		*s = छोटे(*s);
पूर्ण

अटल पूर्णांक fsl_ssi_imx_probe(काष्ठा platक्रमm_device *pdev,
			     काष्ठा fsl_ssi *ssi, व्योम __iomem *iomem)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	/* Backward compatible क्रम a DT without ipg घड़ी name asचिन्हित */
	अगर (ssi->has_ipg_clk_name)
		ssi->clk = devm_clk_get(dev, "ipg");
	अन्यथा
		ssi->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(ssi->clk)) अणु
		ret = PTR_ERR(ssi->clk);
		dev_err(dev, "failed to get clock: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Enable the घड़ी since regmap will not handle it in this हाल */
	अगर (!ssi->has_ipg_clk_name) अणु
		ret = clk_prepare_enable(ssi->clk);
		अगर (ret) अणु
			dev_err(dev, "clk_prepare_enable failed: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Do not error out क्रम slave हालs that live without a baud घड़ी */
	ssi->baudclk = devm_clk_get(dev, "baud");
	अगर (IS_ERR(ssi->baudclk))
		dev_dbg(dev, "failed to get baud clock: %ld\n",
			 PTR_ERR(ssi->baudclk));

	ssi->dma_params_tx.maxburst = ssi->dma_maxburst;
	ssi->dma_params_rx.maxburst = ssi->dma_maxburst;
	ssi->dma_params_tx.addr = ssi->ssi_phys + REG_SSI_STX0;
	ssi->dma_params_rx.addr = ssi->ssi_phys + REG_SSI_SRX0;

	/* Use even numbers to aव्योम channel swap due to SDMA script design */
	अगर (ssi->use_dual_fअगरo) अणु
		ssi->dma_params_tx.maxburst &= ~0x1;
		ssi->dma_params_rx.maxburst &= ~0x1;
	पूर्ण

	अगर (!ssi->use_dma) अणु
		/*
		 * Some boards use an incompatible codec. Use imx-fiq-pcm-audio
		 * to get it working, as DMA is not possible in this situation.
		 */
		ssi->fiq_params.irq = ssi->irq;
		ssi->fiq_params.base = iomem;
		ssi->fiq_params.dma_params_rx = &ssi->dma_params_rx;
		ssi->fiq_params.dma_params_tx = &ssi->dma_params_tx;

		ret = imx_pcm_fiq_init(pdev, &ssi->fiq_params);
		अगर (ret)
			जाओ error_pcm;
	पूर्ण अन्यथा अणु
		ret = imx_pcm_dma_init(pdev, IMX_SSI_DMABUF_SIZE);
		अगर (ret)
			जाओ error_pcm;
	पूर्ण

	वापस 0;

error_pcm:
	अगर (!ssi->has_ipg_clk_name)
		clk_disable_unprepare(ssi->clk);

	वापस ret;
पूर्ण

अटल व्योम fsl_ssi_imx_clean(काष्ठा platक्रमm_device *pdev, काष्ठा fsl_ssi *ssi)
अणु
	अगर (!ssi->use_dma)
		imx_pcm_fiq_निकास(pdev);
	अगर (!ssi->has_ipg_clk_name)
		clk_disable_unprepare(ssi->clk);
पूर्ण

अटल पूर्णांक fsl_ssi_probe_from_dt(काष्ठा fsl_ssi *ssi)
अणु
	काष्ठा device *dev = ssi->dev;
	काष्ठा device_node *np = dev->of_node;
	स्थिर अक्षर *p, *sprop;
	स्थिर __be32 *iprop;
	u32 dmas[4];
	पूर्णांक ret;

	ret = of_property_match_string(np, "clock-names", "ipg");
	/* Get error code अगर not found */
	ssi->has_ipg_clk_name = ret >= 0;

	/* Check अगर being used in AC97 mode */
	sprop = of_get_property(np, "fsl,mode", शून्य);
	अगर (sprop && !म_भेद(sprop, "ac97-slave")) अणु
		ssi->dai_fmt = FSLSSI_AC97_DAIFMT;

		ret = of_property_पढ़ो_u32(np, "cell-index", &ssi->card_idx);
		अगर (ret) अणु
			dev_err(dev, "failed to get SSI index property\n");
			वापस -EINVAL;
		पूर्ण
		म_नकल(ssi->card_name, "ac97-codec");
	पूर्ण अन्यथा अगर (!of_find_property(np, "fsl,ssi-asynchronous", शून्य)) अणु
		/*
		 * In synchronous mode, STCK and STFS ports are used by RX
		 * as well. So the software should limit the sample rates,
		 * sample bits and channels to be symmetric.
		 *
		 * This is exclusive with FSLSSI_AC97_FORMATS as AC97 runs
		 * in the SSI synchronous mode however it करोes not have to
		 * limit symmetric sample rates and sample bits.
		 */
		ssi->synchronous = true;
	पूर्ण

	/* Select DMA or FIQ */
	ssi->use_dma = !of_property_पढ़ो_bool(np, "fsl,fiq-stream-filter");

	/* Fetch FIFO depth; Set to 8 क्रम older DT without this property */
	iprop = of_get_property(np, "fsl,fifo-depth", शून्य);
	अगर (iprop)
		ssi->fअगरo_depth = be32_to_cpup(iprop);
	अन्यथा
		ssi->fअगरo_depth = 8;

	/* Use dual FIFO mode depending on the support from SDMA script */
	ret = of_property_पढ़ो_u32_array(np, "dmas", dmas, 4);
	अगर (ssi->use_dma && !ret && dmas[2] == IMX_DMATYPE_SSI_DUAL)
		ssi->use_dual_fअगरo = true;

	/*
	 * Backward compatible क्रम older bindings by manually triggering the
	 * machine driver's probe(). Use /compatible property, including the
	 * address of CPU DAI driver काष्ठाure, as the name of machine driver
	 *
	 * If card_name is set by AC97 earlier, bypass here since it uses a
	 * dअगरferent name to रेजिस्टर the device.
	 */
	अगर (!ssi->card_name[0] && of_get_property(np, "codec-handle", शून्य)) अणु
		काष्ठा device_node *root = of_find_node_by_path("/");

		sprop = of_get_property(root, "compatible", शून्य);
		of_node_put(root);
		/* Strip "fsl," in the compatible name अगर applicable */
		p = म_खोजप(sprop, ',');
		अगर (p)
			sprop = p + 1;
		snम_लिखो(ssi->card_name, माप(ssi->card_name),
			 "snd-soc-%s", sprop);
		make_lowerहाल(ssi->card_name);
		ssi->card_idx = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_ssi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा regmap_config regconfig = fsl_ssi_regconfig;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा fsl_ssi *ssi;
	काष्ठा resource *res;
	व्योम __iomem *iomem;
	पूर्णांक ret = 0;

	ssi = devm_kzalloc(dev, माप(*ssi), GFP_KERNEL);
	अगर (!ssi)
		वापस -ENOMEM;

	ssi->dev = dev;
	ssi->soc = of_device_get_match_data(&pdev->dev);

	/* Probe from DT */
	ret = fsl_ssi_probe_from_dt(ssi);
	अगर (ret)
		वापस ret;

	अगर (fsl_ssi_is_ac97(ssi)) अणु
		स_नकल(&ssi->cpu_dai_drv, &fsl_ssi_ac97_dai,
		       माप(fsl_ssi_ac97_dai));
		fsl_ac97_data = ssi;
	पूर्ण अन्यथा अणु
		स_नकल(&ssi->cpu_dai_drv, &fsl_ssi_dai_ढाँचा,
		       माप(fsl_ssi_dai_ढाँचा));
	पूर्ण
	ssi->cpu_dai_drv.name = dev_name(dev);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	iomem = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(iomem))
		वापस PTR_ERR(iomem);
	ssi->ssi_phys = res->start;

	अगर (ssi->soc->imx21regs) अणु
		/* No SACCअणुST,EN,DISपूर्ण regs in imx21-class SSI */
		regconfig.max_रेजिस्टर = REG_SSI_SRMSK;
		regconfig.num_reg_शेषs_raw =
			REG_SSI_SRMSK / माप(uपूर्णांक32_t) + 1;
	पूर्ण

	अगर (ssi->has_ipg_clk_name)
		ssi->regs = devm_regmap_init_mmio_clk(dev, "ipg", iomem,
						      &regconfig);
	अन्यथा
		ssi->regs = devm_regmap_init_mmio(dev, iomem, &regconfig);
	अगर (IS_ERR(ssi->regs)) अणु
		dev_err(dev, "failed to init register map\n");
		वापस PTR_ERR(ssi->regs);
	पूर्ण

	ssi->irq = platक्रमm_get_irq(pdev, 0);
	अगर (ssi->irq < 0)
		वापस ssi->irq;

	/* Set software limitations क्रम synchronous mode except AC97 */
	अगर (ssi->synchronous && !fsl_ssi_is_ac97(ssi)) अणु
		ssi->cpu_dai_drv.symmetric_rate = 1;
		ssi->cpu_dai_drv.symmetric_channels = 1;
		ssi->cpu_dai_drv.symmetric_sample_bits = 1;
	पूर्ण

	/*
	 * Configure TX and RX DMA watermarks -- when to send a DMA request
	 *
	 * Values should be tested to aव्योम FIFO under/over run. Set maxburst
	 * to fअगरo_watermark to maxiumize DMA transaction to reduce overhead.
	 */
	चयन (ssi->fअगरo_depth) अणु
	हाल 15:
		/*
		 * Set to 8 as a balanced configuration -- When TX FIFO has 8
		 * empty slots, send a DMA request to fill these 8 slots. The
		 * reमुख्यing 7 slots should be able to allow DMA to finish the
		 * transaction beक्रमe TX FIFO underruns; Same applies to RX.
		 *
		 * Tested with हालs running at 48kHz @ 16 bits x 16 channels
		 */
		ssi->fअगरo_watermark = 8;
		ssi->dma_maxburst = 8;
		अवरोध;
	हाल 8:
	शेष:
		/* Safely use old watermark configurations क्रम older chips */
		ssi->fअगरo_watermark = ssi->fअगरo_depth - 2;
		ssi->dma_maxburst = ssi->fअगरo_depth - 2;
		अवरोध;
	पूर्ण

	dev_set_drvdata(dev, ssi);

	अगर (ssi->soc->imx) अणु
		ret = fsl_ssi_imx_probe(pdev, ssi, iomem);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (fsl_ssi_is_ac97(ssi)) अणु
		mutex_init(&ssi->ac97_reg_lock);
		ret = snd_soc_set_ac97_ops_of_reset(&fsl_ssi_ac97_ops, pdev);
		अगर (ret) अणु
			dev_err(dev, "failed to set AC'97 ops\n");
			जाओ error_ac97_ops;
		पूर्ण
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(dev, &fsl_ssi_component,
					      &ssi->cpu_dai_drv, 1);
	अगर (ret) अणु
		dev_err(dev, "failed to register DAI: %d\n", ret);
		जाओ error_asoc_रेजिस्टर;
	पूर्ण

	अगर (ssi->use_dma) अणु
		ret = devm_request_irq(dev, ssi->irq, fsl_ssi_isr, 0,
				       dev_name(dev), ssi);
		अगर (ret < 0) अणु
			dev_err(dev, "failed to claim irq %u\n", ssi->irq);
			जाओ error_asoc_रेजिस्टर;
		पूर्ण
	पूर्ण

	fsl_ssi_debugfs_create(&ssi->dbg_stats, dev);

	/* Initially configures SSI रेजिस्टरs */
	fsl_ssi_hw_init(ssi);

	/* Register a platक्रमm device क्रम older bindings or AC97 */
	अगर (ssi->card_name[0]) अणु
		काष्ठा device *parent = dev;
		/*
		 * Do not set SSI dev as the parent of AC97 CODEC device since
		 * it करोes not have a DT node. Otherwise ASoC core will assume
		 * CODEC has the same DT node as the SSI, so it may bypass the
		 * dai_probe() of SSI and then cause शून्य DMA data poपूर्णांकers.
		 */
		अगर (fsl_ssi_is_ac97(ssi))
			parent = शून्य;

		ssi->card_pdev = platक्रमm_device_रेजिस्टर_data(parent,
				ssi->card_name, ssi->card_idx, शून्य, 0);
		अगर (IS_ERR(ssi->card_pdev)) अणु
			ret = PTR_ERR(ssi->card_pdev);
			dev_err(dev, "failed to register %s: %d\n",
				ssi->card_name, ret);
			जाओ error_sound_card;
		पूर्ण
	पूर्ण

	वापस 0;

error_sound_card:
	fsl_ssi_debugfs_हटाओ(&ssi->dbg_stats);
error_asoc_रेजिस्टर:
	अगर (fsl_ssi_is_ac97(ssi))
		snd_soc_set_ac97_ops(शून्य);
error_ac97_ops:
	अगर (fsl_ssi_is_ac97(ssi))
		mutex_destroy(&ssi->ac97_reg_lock);

	अगर (ssi->soc->imx)
		fsl_ssi_imx_clean(pdev, ssi);

	वापस ret;
पूर्ण

अटल पूर्णांक fsl_ssi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_ssi *ssi = dev_get_drvdata(&pdev->dev);

	fsl_ssi_debugfs_हटाओ(&ssi->dbg_stats);

	अगर (ssi->card_pdev)
		platक्रमm_device_unरेजिस्टर(ssi->card_pdev);

	/* Clean up SSI रेजिस्टरs */
	fsl_ssi_hw_clean(ssi);

	अगर (ssi->soc->imx)
		fsl_ssi_imx_clean(pdev, ssi);

	अगर (fsl_ssi_is_ac97(ssi)) अणु
		snd_soc_set_ac97_ops(शून्य);
		mutex_destroy(&ssi->ac97_reg_lock);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक fsl_ssi_suspend(काष्ठा device *dev)
अणु
	काष्ठा fsl_ssi *ssi = dev_get_drvdata(dev);
	काष्ठा regmap *regs = ssi->regs;

	regmap_पढ़ो(regs, REG_SSI_SFCSR, &ssi->regcache_sfcsr);
	regmap_पढ़ो(regs, REG_SSI_SACNT, &ssi->regcache_sacnt);

	regcache_cache_only(regs, true);
	regcache_mark_dirty(regs);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_ssi_resume(काष्ठा device *dev)
अणु
	काष्ठा fsl_ssi *ssi = dev_get_drvdata(dev);
	काष्ठा regmap *regs = ssi->regs;

	regcache_cache_only(regs, false);

	regmap_update_bits(regs, REG_SSI_SFCSR,
			   SSI_SFCSR_RFWM1_MASK | SSI_SFCSR_TFWM1_MASK |
			   SSI_SFCSR_RFWM0_MASK | SSI_SFCSR_TFWM0_MASK,
			   ssi->regcache_sfcsr);
	regmap_ग_लिखो(regs, REG_SSI_SACNT, ssi->regcache_sacnt);

	वापस regcache_sync(regs);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops fsl_ssi_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(fsl_ssi_suspend, fsl_ssi_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver fsl_ssi_driver = अणु
	.driver = अणु
		.name = "fsl-ssi-dai",
		.of_match_table = fsl_ssi_ids,
		.pm = &fsl_ssi_pm,
	पूर्ण,
	.probe = fsl_ssi_probe,
	.हटाओ = fsl_ssi_हटाओ,
पूर्ण;

module_platक्रमm_driver(fsl_ssi_driver);

MODULE_ALIAS("platform:fsl-ssi-dai");
MODULE_AUTHOR("Timur Tabi <timur@freescale.com>");
MODULE_DESCRIPTION("Freescale Synchronous Serial Interface (SSI) ASoC Driver");
MODULE_LICENSE("GPL v2");
