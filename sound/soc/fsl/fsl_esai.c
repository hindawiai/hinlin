<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Freescale ESAI ALSA SoC Digital Audio Interface (DAI) driver
//
// Copyright (C) 2014 Freescale Semiconductor, Inc.

#समावेश <linux/clk.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm_params.h>

#समावेश "fsl_esai.h"
#समावेश "imx-pcm.h"

#घोषणा FSL_ESAI_FORMATS	(SNDRV_PCM_FMTBIT_S8 | \
				SNDRV_PCM_FMTBIT_S16_LE | \
				SNDRV_PCM_FMTBIT_S20_3LE | \
				SNDRV_PCM_FMTBIT_S24_LE)

/**
 * काष्ठा fsl_esai_soc_data - soc specअगरic data
 * @reset_at_xrun: flags क्रम enable reset operaton
 */
काष्ठा fsl_esai_soc_data अणु
	bool reset_at_xrun;
पूर्ण;

/**
 * काष्ठा fsl_esai - ESAI निजी data
 * @dma_params_rx: DMA parameters क्रम receive channel
 * @dma_params_tx: DMA parameters क्रम transmit channel
 * @pdev: platक्रमm device poपूर्णांकer
 * @regmap: regmap handler
 * @coreclk: घड़ी source to access रेजिस्टर
 * @extalclk: esai घड़ी source to derive HCK, SCK and FS
 * @fsysclk: प्रणाली घड़ी source to derive HCK, SCK and FS
 * @spbaclk: SPBA घड़ी (optional, depending on SoC design)
 * @work: work to handle the reset operation
 * @soc: soc specअगरic data
 * @lock: spin lock between hw_reset() and trigger()
 * @fअगरo_depth: depth of tx/rx FIFO
 * @slot_width: width of each DAI slot
 * @slots: number of slots
 * @tx_mask: slot mask क्रम TX
 * @rx_mask: slot mask क्रम RX
 * @channels: channel num क्रम tx or rx
 * @hck_rate: घड़ी rate of desired HCKx घड़ी
 * @sck_rate: घड़ी rate of desired SCKx घड़ी
 * @hck_dir: the direction of HCKx pads
 * @sck_भाग: अगर using PSR/PM भागiders क्रम SCKx घड़ी
 * @slave_mode: अगर fully using DAI slave mode
 * @synchronous: अगर using tx/rx synchronous mode
 * @name: driver name
 */
काष्ठा fsl_esai अणु
	काष्ठा snd_dmaengine_dai_dma_data dma_params_rx;
	काष्ठा snd_dmaengine_dai_dma_data dma_params_tx;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा regmap *regmap;
	काष्ठा clk *coreclk;
	काष्ठा clk *extalclk;
	काष्ठा clk *fsysclk;
	काष्ठा clk *spbaclk;
	काष्ठा work_काष्ठा work;
	स्थिर काष्ठा fsl_esai_soc_data *soc;
	spinlock_t lock; /* Protect hw_reset and trigger */
	u32 fअगरo_depth;
	u32 slot_width;
	u32 slots;
	u32 tx_mask;
	u32 rx_mask;
	u32 channels[2];
	u32 hck_rate[2];
	u32 sck_rate[2];
	bool hck_dir[2];
	bool sck_भाग[2];
	bool slave_mode;
	bool synchronous;
	अक्षर name[32];
पूर्ण;

अटल काष्ठा fsl_esai_soc_data fsl_esai_vf610 = अणु
	.reset_at_xrun = true,
पूर्ण;

अटल काष्ठा fsl_esai_soc_data fsl_esai_imx35 = अणु
	.reset_at_xrun = true,
पूर्ण;

अटल काष्ठा fsl_esai_soc_data fsl_esai_imx6ull = अणु
	.reset_at_xrun = false,
पूर्ण;

अटल irqवापस_t esai_isr(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा fsl_esai *esai_priv = (काष्ठा fsl_esai *)devid;
	काष्ठा platक्रमm_device *pdev = esai_priv->pdev;
	u32 esr;
	u32 saisr;

	regmap_पढ़ो(esai_priv->regmap, REG_ESAI_ESR, &esr);
	regmap_पढ़ो(esai_priv->regmap, REG_ESAI_SAISR, &saisr);

	अगर ((saisr & (ESAI_SAISR_TUE | ESAI_SAISR_ROE)) &&
	    esai_priv->soc->reset_at_xrun) अणु
		dev_dbg(&pdev->dev, "reset module for xrun\n");
		regmap_update_bits(esai_priv->regmap, REG_ESAI_TCR,
				   ESAI_xCR_xEIE_MASK, 0);
		regmap_update_bits(esai_priv->regmap, REG_ESAI_RCR,
				   ESAI_xCR_xEIE_MASK, 0);
		schedule_work(&esai_priv->work);
	पूर्ण

	अगर (esr & ESAI_ESR_TINIT_MASK)
		dev_dbg(&pdev->dev, "isr: Transmission Initialized\n");

	अगर (esr & ESAI_ESR_RFF_MASK)
		dev_warn(&pdev->dev, "isr: Receiving overrun\n");

	अगर (esr & ESAI_ESR_TFE_MASK)
		dev_warn(&pdev->dev, "isr: Transmission underrun\n");

	अगर (esr & ESAI_ESR_TLS_MASK)
		dev_dbg(&pdev->dev, "isr: Just transmitted the last slot\n");

	अगर (esr & ESAI_ESR_TDE_MASK)
		dev_dbg(&pdev->dev, "isr: Transmission data exception\n");

	अगर (esr & ESAI_ESR_TED_MASK)
		dev_dbg(&pdev->dev, "isr: Transmitting even slots\n");

	अगर (esr & ESAI_ESR_TD_MASK)
		dev_dbg(&pdev->dev, "isr: Transmitting data\n");

	अगर (esr & ESAI_ESR_RLS_MASK)
		dev_dbg(&pdev->dev, "isr: Just received the last slot\n");

	अगर (esr & ESAI_ESR_RDE_MASK)
		dev_dbg(&pdev->dev, "isr: Receiving data exception\n");

	अगर (esr & ESAI_ESR_RED_MASK)
		dev_dbg(&pdev->dev, "isr: Receiving even slots\n");

	अगर (esr & ESAI_ESR_RD_MASK)
		dev_dbg(&pdev->dev, "isr: Receiving data\n");

	वापस IRQ_HANDLED;
पूर्ण

/**
 * fsl_esai_भागisor_cal - This function is used to calculate the
 * भागisors of psr, pm, fp and it is supposed to be called in
 * set_dai_sysclk() and set_bclk().
 *
 * @dai: poपूर्णांकer to DAI
 * @tx: current setting is क्रम playback or capture
 * @ratio: desired overall ratio क्रम the paticipating भागiders
 * @usefp: क्रम HCK setting, there is no need to set fp भागider
 * @fp: bypass other भागiders by setting fp directly अगर fp != 0
 */
अटल पूर्णांक fsl_esai_भागisor_cal(काष्ठा snd_soc_dai *dai, bool tx, u32 ratio,
				bool usefp, u32 fp)
अणु
	काष्ठा fsl_esai *esai_priv = snd_soc_dai_get_drvdata(dai);
	u32 psr, pm = 999, maxfp, prod, sub, savesub, i, j;

	maxfp = usefp ? 16 : 1;

	अगर (usefp && fp)
		जाओ out_fp;

	अगर (ratio > 2 * 8 * 256 * maxfp || ratio < 2) अणु
		dev_err(dai->dev, "the ratio is out of range (2 ~ %d)\n",
				2 * 8 * 256 * maxfp);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (ratio % 2) अणु
		dev_err(dai->dev, "the raio must be even if using upper divider\n");
		वापस -EINVAL;
	पूर्ण

	ratio /= 2;

	psr = ratio <= 256 * maxfp ? ESAI_xCCR_xPSR_BYPASS : ESAI_xCCR_xPSR_DIV8;

	/* Do not loop-search अगर PM (1 ~ 256) alone can serve the ratio */
	अगर (ratio <= 256) अणु
		pm = ratio;
		fp = 1;
		जाओ out;
	पूर्ण

	/* Set the max fluctuation -- 0.1% of the max devisor */
	savesub = (psr ? 1 : 8)  * 256 * maxfp / 1000;

	/* Find the best value क्रम PM */
	क्रम (i = 1; i <= 256; i++) अणु
		क्रम (j = 1; j <= maxfp; j++) अणु
			/* PSR (1 or 8) * PM (1 ~ 256) * FP (1 ~ 16) */
			prod = (psr ? 1 : 8) * i * j;

			अगर (prod == ratio)
				sub = 0;
			अन्यथा अगर (prod / ratio == 1)
				sub = prod - ratio;
			अन्यथा अगर (ratio / prod == 1)
				sub = ratio - prod;
			अन्यथा
				जारी;

			/* Calculate the fraction */
			sub = sub * 1000 / ratio;
			अगर (sub < savesub) अणु
				savesub = sub;
				pm = i;
				fp = j;
			पूर्ण

			/* We are lucky */
			अगर (savesub == 0)
				जाओ out;
		पूर्ण
	पूर्ण

	अगर (pm == 999) अणु
		dev_err(dai->dev, "failed to calculate proper divisors\n");
		वापस -EINVAL;
	पूर्ण

out:
	regmap_update_bits(esai_priv->regmap, REG_ESAI_xCCR(tx),
			   ESAI_xCCR_xPSR_MASK | ESAI_xCCR_xPM_MASK,
			   psr | ESAI_xCCR_xPM(pm));

out_fp:
	/* Bypass fp अगर not being required */
	अगर (maxfp <= 1)
		वापस 0;

	regmap_update_bits(esai_priv->regmap, REG_ESAI_xCCR(tx),
			   ESAI_xCCR_xFP_MASK, ESAI_xCCR_xFP(fp));

	वापस 0;
पूर्ण

/**
 * fsl_esai_set_dai_sysclk - configure the घड़ी frequency of MCLK (HCKT/HCKR)
 * @dai: poपूर्णांकer to DAI
 * @clk_id: The घड़ी source of HCKT/HCKR
 *	  (Input from outside; output from inside, FSYS or EXTAL)
 * @freq: The required घड़ी rate of HCKT/HCKR
 * @dir: The घड़ी direction of HCKT/HCKR
 *
 * Note: If the direction is input, we करो not care about clk_id.
 */
अटल पूर्णांक fsl_esai_set_dai_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
				   अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा fsl_esai *esai_priv = snd_soc_dai_get_drvdata(dai);
	काष्ठा clk *clksrc = esai_priv->extalclk;
	bool tx = (clk_id <= ESAI_HCKT_EXTAL || esai_priv->synchronous);
	bool in = dir == SND_SOC_CLOCK_IN;
	u32 ratio, ecr = 0;
	अचिन्हित दीर्घ clk_rate;
	पूर्णांक ret;

	अगर (freq == 0) अणु
		dev_err(dai->dev, "%sput freq of HCK%c should not be 0Hz\n",
			in ? "in" : "out", tx ? 'T' : 'R');
		वापस -EINVAL;
	पूर्ण

	/* Bypass भागider settings अगर the requirement करोesn't change */
	अगर (freq == esai_priv->hck_rate[tx] && dir == esai_priv->hck_dir[tx])
		वापस 0;

	/* sck_भाग can be only bypassed अगर ETO/ERO=0 and SNC_SOC_CLOCK_OUT */
	esai_priv->sck_भाग[tx] = true;

	/* Set the direction of HCKT/HCKR pins */
	regmap_update_bits(esai_priv->regmap, REG_ESAI_xCCR(tx),
			   ESAI_xCCR_xHCKD, in ? 0 : ESAI_xCCR_xHCKD);

	अगर (in)
		जाओ out;

	चयन (clk_id) अणु
	हाल ESAI_HCKT_FSYS:
	हाल ESAI_HCKR_FSYS:
		clksrc = esai_priv->fsysclk;
		अवरोध;
	हाल ESAI_HCKT_EXTAL:
		ecr |= ESAI_ECR_ETI;
		अवरोध;
	हाल ESAI_HCKR_EXTAL:
		ecr |= esai_priv->synchronous ? ESAI_ECR_ETI : ESAI_ECR_ERI;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (IS_ERR(clksrc)) अणु
		dev_err(dai->dev, "no assigned %s clock\n",
			(clk_id % 2) ? "extal" : "fsys");
		वापस PTR_ERR(clksrc);
	पूर्ण
	clk_rate = clk_get_rate(clksrc);

	ratio = clk_rate / freq;
	अगर (ratio * freq > clk_rate)
		ret = ratio * freq - clk_rate;
	अन्यथा अगर (ratio * freq < clk_rate)
		ret = clk_rate - ratio * freq;
	अन्यथा
		ret = 0;

	/* Block अगर घड़ी source can not be भागided पूर्णांकo the required rate */
	अगर (ret != 0 && clk_rate / ret < 1000) अणु
		dev_err(dai->dev, "failed to derive required HCK%c rate\n",
				tx ? 'T' : 'R');
		वापस -EINVAL;
	पूर्ण

	/* Only EXTAL source can be output directly without using PSR and PM */
	अगर (ratio == 1 && clksrc == esai_priv->extalclk) अणु
		/* Bypass all the भागiders अगर not being needed */
		ecr |= tx ? ESAI_ECR_ETO : ESAI_ECR_ERO;
		जाओ out;
	पूर्ण अन्यथा अगर (ratio < 2) अणु
		/* The ratio should be no less than 2 अगर using other sources */
		dev_err(dai->dev, "failed to derive required HCK%c rate\n",
				tx ? 'T' : 'R');
		वापस -EINVAL;
	पूर्ण

	ret = fsl_esai_भागisor_cal(dai, tx, ratio, false, 0);
	अगर (ret)
		वापस ret;

	esai_priv->sck_भाग[tx] = false;

out:
	esai_priv->hck_dir[tx] = dir;
	esai_priv->hck_rate[tx] = freq;

	regmap_update_bits(esai_priv->regmap, REG_ESAI_ECR,
			   tx ? ESAI_ECR_ETI | ESAI_ECR_ETO :
			   ESAI_ECR_ERI | ESAI_ECR_ERO, ecr);

	वापस 0;
पूर्ण

/**
 * fsl_esai_set_bclk - configure the related भागiders according to the bclk rate
 * @dai: poपूर्णांकer to DAI
 * @tx: direction boolean
 * @freq: bclk freq
 */
अटल पूर्णांक fsl_esai_set_bclk(काष्ठा snd_soc_dai *dai, bool tx, u32 freq)
अणु
	काष्ठा fsl_esai *esai_priv = snd_soc_dai_get_drvdata(dai);
	u32 hck_rate = esai_priv->hck_rate[tx];
	u32 sub, ratio = hck_rate / freq;
	पूर्णांक ret;

	/* Don't apply क्रम fully slave mode or unchanged bclk */
	अगर (esai_priv->slave_mode || esai_priv->sck_rate[tx] == freq)
		वापस 0;

	अगर (ratio * freq > hck_rate)
		sub = ratio * freq - hck_rate;
	अन्यथा अगर (ratio * freq < hck_rate)
		sub = hck_rate - ratio * freq;
	अन्यथा
		sub = 0;

	/* Block अगर घड़ी source can not be भागided पूर्णांकo the required rate */
	अगर (sub != 0 && hck_rate / sub < 1000) अणु
		dev_err(dai->dev, "failed to derive required SCK%c rate\n",
				tx ? 'T' : 'R');
		वापस -EINVAL;
	पूर्ण

	/* The ratio should be contented by FP alone अगर bypassing PM and PSR */
	अगर (!esai_priv->sck_भाग[tx] && (ratio > 16 || ratio == 0)) अणु
		dev_err(dai->dev, "the ratio is out of range (1 ~ 16)\n");
		वापस -EINVAL;
	पूर्ण

	ret = fsl_esai_भागisor_cal(dai, tx, ratio, true,
			esai_priv->sck_भाग[tx] ? 0 : ratio);
	अगर (ret)
		वापस ret;

	/* Save current bclk rate */
	esai_priv->sck_rate[tx] = freq;

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_esai_set_dai_tdm_slot(काष्ठा snd_soc_dai *dai, u32 tx_mask,
				     u32 rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा fsl_esai *esai_priv = snd_soc_dai_get_drvdata(dai);

	regmap_update_bits(esai_priv->regmap, REG_ESAI_TCCR,
			   ESAI_xCCR_xDC_MASK, ESAI_xCCR_xDC(slots));

	regmap_update_bits(esai_priv->regmap, REG_ESAI_RCCR,
			   ESAI_xCCR_xDC_MASK, ESAI_xCCR_xDC(slots));

	esai_priv->slot_width = slot_width;
	esai_priv->slots = slots;
	esai_priv->tx_mask = tx_mask;
	esai_priv->rx_mask = rx_mask;

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_esai_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा fsl_esai *esai_priv = snd_soc_dai_get_drvdata(dai);
	u32 xcr = 0, xccr = 0, mask;

	/* DAI mode */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		/* Data on rising edge of bclk, frame low, 1clk beक्रमe data */
		xcr |= ESAI_xCR_xFSR;
		xccr |= ESAI_xCCR_xFSP | ESAI_xCCR_xCKP | ESAI_xCCR_xHCKP;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		/* Data on rising edge of bclk, frame high */
		xccr |= ESAI_xCCR_xCKP | ESAI_xCCR_xHCKP;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		/* Data on rising edge of bclk, frame high, right aligned */
		xccr |= ESAI_xCCR_xCKP | ESAI_xCCR_xHCKP;
		xcr  |= ESAI_xCR_xWA;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		/* Data on rising edge of bclk, frame high, 1clk beक्रमe data */
		xcr |= ESAI_xCR_xFSL | ESAI_xCR_xFSR;
		xccr |= ESAI_xCCR_xCKP | ESAI_xCCR_xHCKP;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		/* Data on rising edge of bclk, frame high */
		xcr |= ESAI_xCR_xFSL;
		xccr |= ESAI_xCCR_xCKP | ESAI_xCCR_xHCKP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* DAI घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		/* Nothing to करो क्रम both normal हालs */
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		/* Invert bit घड़ी */
		xccr ^= ESAI_xCCR_xCKP | ESAI_xCCR_xHCKP;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		/* Invert frame घड़ी */
		xccr ^= ESAI_xCCR_xFSP;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		/* Invert both घड़ीs */
		xccr ^= ESAI_xCCR_xCKP | ESAI_xCCR_xHCKP | ESAI_xCCR_xFSP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	esai_priv->slave_mode = false;

	/* DAI घड़ी master masks */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		esai_priv->slave_mode = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		xccr |= ESAI_xCCR_xCKD;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		xccr |= ESAI_xCCR_xFSD;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		xccr |= ESAI_xCCR_xFSD | ESAI_xCCR_xCKD;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mask = ESAI_xCR_xFSL | ESAI_xCR_xFSR | ESAI_xCR_xWA;
	regmap_update_bits(esai_priv->regmap, REG_ESAI_TCR, mask, xcr);
	regmap_update_bits(esai_priv->regmap, REG_ESAI_RCR, mask, xcr);

	mask = ESAI_xCCR_xCKP | ESAI_xCCR_xHCKP | ESAI_xCCR_xFSP |
		ESAI_xCCR_xFSD | ESAI_xCCR_xCKD;
	regmap_update_bits(esai_priv->regmap, REG_ESAI_TCCR, mask, xccr);
	regmap_update_bits(esai_priv->regmap, REG_ESAI_RCCR, mask, xccr);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_esai_startup(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsl_esai *esai_priv = snd_soc_dai_get_drvdata(dai);

	अगर (!snd_soc_dai_active(dai)) अणु
		/* Set synchronous mode */
		regmap_update_bits(esai_priv->regmap, REG_ESAI_SAICR,
				   ESAI_SAICR_SYNC, esai_priv->synchronous ?
				   ESAI_SAICR_SYNC : 0);

		/* Set slots count */
		regmap_update_bits(esai_priv->regmap, REG_ESAI_TCCR,
				   ESAI_xCCR_xDC_MASK,
				   ESAI_xCCR_xDC(esai_priv->slots));
		regmap_update_bits(esai_priv->regmap, REG_ESAI_RCCR,
				   ESAI_xCCR_xDC_MASK,
				   ESAI_xCCR_xDC(esai_priv->slots));
	पूर्ण

	वापस 0;

पूर्ण

अटल पूर्णांक fsl_esai_hw_params(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *params,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsl_esai *esai_priv = snd_soc_dai_get_drvdata(dai);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	u32 width = params_width(params);
	u32 channels = params_channels(params);
	u32 pins = DIV_ROUND_UP(channels, esai_priv->slots);
	u32 slot_width = width;
	u32 bclk, mask, val;
	पूर्णांक ret;

	/* Override slot_width अगर being specअगरically set */
	अगर (esai_priv->slot_width)
		slot_width = esai_priv->slot_width;

	bclk = params_rate(params) * slot_width * esai_priv->slots;

	ret = fsl_esai_set_bclk(dai, esai_priv->synchronous || tx, bclk);
	अगर (ret)
		वापस ret;

	mask = ESAI_xCR_xSWS_MASK;
	val = ESAI_xCR_xSWS(slot_width, width);

	regmap_update_bits(esai_priv->regmap, REG_ESAI_xCR(tx), mask, val);
	/* Recording in synchronous mode needs to set TCR also */
	अगर (!tx && esai_priv->synchronous)
		regmap_update_bits(esai_priv->regmap, REG_ESAI_TCR, mask, val);

	/* Use Normal mode to support monaural audio */
	regmap_update_bits(esai_priv->regmap, REG_ESAI_xCR(tx),
			   ESAI_xCR_xMOD_MASK, params_channels(params) > 1 ?
			   ESAI_xCR_xMOD_NETWORK : 0);

	regmap_update_bits(esai_priv->regmap, REG_ESAI_xFCR(tx),
			   ESAI_xFCR_xFR_MASK, ESAI_xFCR_xFR);

	mask = ESAI_xFCR_xFR_MASK | ESAI_xFCR_xWA_MASK | ESAI_xFCR_xFWM_MASK |
	      (tx ? ESAI_xFCR_TE_MASK | ESAI_xFCR_TIEN : ESAI_xFCR_RE_MASK);
	val = ESAI_xFCR_xWA(width) | ESAI_xFCR_xFWM(esai_priv->fअगरo_depth) |
	     (tx ? ESAI_xFCR_TE(pins) | ESAI_xFCR_TIEN : ESAI_xFCR_RE(pins));

	regmap_update_bits(esai_priv->regmap, REG_ESAI_xFCR(tx), mask, val);

	अगर (tx)
		regmap_update_bits(esai_priv->regmap, REG_ESAI_TCR,
				ESAI_xCR_PADC, ESAI_xCR_PADC);

	/* Remove ESAI personal reset by configuring ESAI_PCRC and ESAI_PRRC */
	regmap_update_bits(esai_priv->regmap, REG_ESAI_PRRC,
			   ESAI_PRRC_PDC_MASK, ESAI_PRRC_PDC(ESAI_GPIO));
	regmap_update_bits(esai_priv->regmap, REG_ESAI_PCRC,
			   ESAI_PCRC_PC_MASK, ESAI_PCRC_PC(ESAI_GPIO));
	वापस 0;
पूर्ण

अटल पूर्णांक fsl_esai_hw_init(काष्ठा fsl_esai *esai_priv)
अणु
	काष्ठा platक्रमm_device *pdev = esai_priv->pdev;
	पूर्णांक ret;

	/* Reset ESAI unit */
	ret = regmap_update_bits(esai_priv->regmap, REG_ESAI_ECR,
				 ESAI_ECR_ESAIEN_MASK | ESAI_ECR_ERST_MASK,
				 ESAI_ECR_ESAIEN | ESAI_ECR_ERST);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to reset ESAI: %d\n", ret);
		वापस ret;
	पूर्ण

	/*
	 * We need to enable ESAI so as to access some of its रेजिस्टरs.
	 * Otherwise, we would fail to dump regmap from user space.
	 */
	ret = regmap_update_bits(esai_priv->regmap, REG_ESAI_ECR,
				 ESAI_ECR_ESAIEN_MASK | ESAI_ECR_ERST_MASK,
				 ESAI_ECR_ESAIEN);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to enable ESAI: %d\n", ret);
		वापस ret;
	पूर्ण

	regmap_update_bits(esai_priv->regmap, REG_ESAI_PRRC,
			   ESAI_PRRC_PDC_MASK, 0);
	regmap_update_bits(esai_priv->regmap, REG_ESAI_PCRC,
			   ESAI_PCRC_PC_MASK, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_esai_रेजिस्टर_restore(काष्ठा fsl_esai *esai_priv)
अणु
	पूर्णांक ret;

	/* FIFO reset क्रम safety */
	regmap_update_bits(esai_priv->regmap, REG_ESAI_TFCR,
			   ESAI_xFCR_xFR, ESAI_xFCR_xFR);
	regmap_update_bits(esai_priv->regmap, REG_ESAI_RFCR,
			   ESAI_xFCR_xFR, ESAI_xFCR_xFR);

	regcache_mark_dirty(esai_priv->regmap);
	ret = regcache_sync(esai_priv->regmap);
	अगर (ret)
		वापस ret;

	/* FIFO reset करोne */
	regmap_update_bits(esai_priv->regmap, REG_ESAI_TFCR, ESAI_xFCR_xFR, 0);
	regmap_update_bits(esai_priv->regmap, REG_ESAI_RFCR, ESAI_xFCR_xFR, 0);

	वापस 0;
पूर्ण

अटल व्योम fsl_esai_trigger_start(काष्ठा fsl_esai *esai_priv, bool tx)
अणु
	u8 i, channels = esai_priv->channels[tx];
	u32 pins = DIV_ROUND_UP(channels, esai_priv->slots);
	u32 mask;

	regmap_update_bits(esai_priv->regmap, REG_ESAI_xFCR(tx),
			   ESAI_xFCR_xFEN_MASK, ESAI_xFCR_xFEN);

	/* Write initial words reqiured by ESAI as normal procedure */
	क्रम (i = 0; tx && i < channels; i++)
		regmap_ग_लिखो(esai_priv->regmap, REG_ESAI_ETDR, 0x0);

	/*
	 * When set the TE/RE in the end of enablement flow, there
	 * will be channel swap issue क्रम multi data line हाल.
	 * In order to workaround this issue, we चयन the bit
	 * enablement sequence to below sequence
	 * 1) clear the xSMB & xSMA: which is करोne in probe and
	 *                           stop state.
	 * 2) set TE/RE
	 * 3) set xSMB
	 * 4) set xSMA:  xSMA is the last one in this flow, which
	 *               will trigger esai to start.
	 */
	regmap_update_bits(esai_priv->regmap, REG_ESAI_xCR(tx),
			   tx ? ESAI_xCR_TE_MASK : ESAI_xCR_RE_MASK,
			   tx ? ESAI_xCR_TE(pins) : ESAI_xCR_RE(pins));
	mask = tx ? esai_priv->tx_mask : esai_priv->rx_mask;

	regmap_update_bits(esai_priv->regmap, REG_ESAI_xSMB(tx),
			   ESAI_xSMB_xS_MASK, ESAI_xSMB_xS(mask));
	regmap_update_bits(esai_priv->regmap, REG_ESAI_xSMA(tx),
			   ESAI_xSMA_xS_MASK, ESAI_xSMA_xS(mask));

	/* Enable Exception पूर्णांकerrupt */
	regmap_update_bits(esai_priv->regmap, REG_ESAI_xCR(tx),
			   ESAI_xCR_xEIE_MASK, ESAI_xCR_xEIE);
पूर्ण

अटल व्योम fsl_esai_trigger_stop(काष्ठा fsl_esai *esai_priv, bool tx)
अणु
	regmap_update_bits(esai_priv->regmap, REG_ESAI_xCR(tx),
			   ESAI_xCR_xEIE_MASK, 0);

	regmap_update_bits(esai_priv->regmap, REG_ESAI_xCR(tx),
			   tx ? ESAI_xCR_TE_MASK : ESAI_xCR_RE_MASK, 0);
	regmap_update_bits(esai_priv->regmap, REG_ESAI_xSMA(tx),
			   ESAI_xSMA_xS_MASK, 0);
	regmap_update_bits(esai_priv->regmap, REG_ESAI_xSMB(tx),
			   ESAI_xSMB_xS_MASK, 0);

	/* Disable and reset FIFO */
	regmap_update_bits(esai_priv->regmap, REG_ESAI_xFCR(tx),
			   ESAI_xFCR_xFR | ESAI_xFCR_xFEN, ESAI_xFCR_xFR);
	regmap_update_bits(esai_priv->regmap, REG_ESAI_xFCR(tx),
			   ESAI_xFCR_xFR, 0);
पूर्ण

अटल व्योम fsl_esai_hw_reset(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fsl_esai *esai_priv = container_of(work, काष्ठा fsl_esai, work);
	bool tx = true, rx = false, enabled[2];
	अचिन्हित दीर्घ lock_flags;
	u32 tfcr, rfcr;

	spin_lock_irqsave(&esai_priv->lock, lock_flags);
	/* Save the रेजिस्टरs */
	regmap_पढ़ो(esai_priv->regmap, REG_ESAI_TFCR, &tfcr);
	regmap_पढ़ो(esai_priv->regmap, REG_ESAI_RFCR, &rfcr);
	enabled[tx] = tfcr & ESAI_xFCR_xFEN;
	enabled[rx] = rfcr & ESAI_xFCR_xFEN;

	/* Stop the tx & rx */
	fsl_esai_trigger_stop(esai_priv, tx);
	fsl_esai_trigger_stop(esai_priv, rx);

	/* Reset the esai, and ignore वापस value */
	fsl_esai_hw_init(esai_priv);

	/* Enक्रमce ESAI personal resets क्रम both TX and RX */
	regmap_update_bits(esai_priv->regmap, REG_ESAI_TCR,
			   ESAI_xCR_xPR_MASK, ESAI_xCR_xPR);
	regmap_update_bits(esai_priv->regmap, REG_ESAI_RCR,
			   ESAI_xCR_xPR_MASK, ESAI_xCR_xPR);

	/* Restore रेजिस्टरs by regcache_sync, and ignore वापस value */
	fsl_esai_रेजिस्टर_restore(esai_priv);

	/* Remove ESAI personal resets by configuring PCRC and PRRC also */
	regmap_update_bits(esai_priv->regmap, REG_ESAI_TCR,
			   ESAI_xCR_xPR_MASK, 0);
	regmap_update_bits(esai_priv->regmap, REG_ESAI_RCR,
			   ESAI_xCR_xPR_MASK, 0);
	regmap_update_bits(esai_priv->regmap, REG_ESAI_PRRC,
			   ESAI_PRRC_PDC_MASK, ESAI_PRRC_PDC(ESAI_GPIO));
	regmap_update_bits(esai_priv->regmap, REG_ESAI_PCRC,
			   ESAI_PCRC_PC_MASK, ESAI_PCRC_PC(ESAI_GPIO));

	/* Restart tx / rx, अगर they alपढ़ोy enabled */
	अगर (enabled[tx])
		fsl_esai_trigger_start(esai_priv, tx);
	अगर (enabled[rx])
		fsl_esai_trigger_start(esai_priv, rx);

	spin_unlock_irqrestore(&esai_priv->lock, lock_flags);
पूर्ण

अटल पूर्णांक fsl_esai_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsl_esai *esai_priv = snd_soc_dai_get_drvdata(dai);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	अचिन्हित दीर्घ lock_flags;

	esai_priv->channels[tx] = substream->runसमय->channels;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		spin_lock_irqsave(&esai_priv->lock, lock_flags);
		fsl_esai_trigger_start(esai_priv, tx);
		spin_unlock_irqrestore(&esai_priv->lock, lock_flags);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		spin_lock_irqsave(&esai_priv->lock, lock_flags);
		fsl_esai_trigger_stop(esai_priv, tx);
		spin_unlock_irqrestore(&esai_priv->lock, lock_flags);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops fsl_esai_dai_ops = अणु
	.startup = fsl_esai_startup,
	.trigger = fsl_esai_trigger,
	.hw_params = fsl_esai_hw_params,
	.set_sysclk = fsl_esai_set_dai_sysclk,
	.set_fmt = fsl_esai_set_dai_fmt,
	.set_tdm_slot = fsl_esai_set_dai_tdm_slot,
पूर्ण;

अटल पूर्णांक fsl_esai_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा fsl_esai *esai_priv = snd_soc_dai_get_drvdata(dai);

	snd_soc_dai_init_dma_data(dai, &esai_priv->dma_params_tx,
				  &esai_priv->dma_params_rx);

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver fsl_esai_dai = अणु
	.probe = fsl_esai_dai_probe,
	.playback = अणु
		.stream_name = "CPU-Playback",
		.channels_min = 1,
		.channels_max = 12,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = FSL_ESAI_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "CPU-Capture",
		.channels_min = 1,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = FSL_ESAI_FORMATS,
	पूर्ण,
	.ops = &fsl_esai_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver fsl_esai_component = अणु
	.name		= "fsl-esai",
पूर्ण;

अटल स्थिर काष्ठा reg_शेष fsl_esai_reg_शेषs[] = अणु
	अणुREG_ESAI_ETDR,	 0x00000000पूर्ण,
	अणुREG_ESAI_ECR,	 0x00000000पूर्ण,
	अणुREG_ESAI_TFCR,	 0x00000000पूर्ण,
	अणुREG_ESAI_RFCR,	 0x00000000पूर्ण,
	अणुREG_ESAI_TX0,	 0x00000000पूर्ण,
	अणुREG_ESAI_TX1,	 0x00000000पूर्ण,
	अणुREG_ESAI_TX2,	 0x00000000पूर्ण,
	अणुREG_ESAI_TX3,	 0x00000000पूर्ण,
	अणुREG_ESAI_TX4,	 0x00000000पूर्ण,
	अणुREG_ESAI_TX5,	 0x00000000पूर्ण,
	अणुREG_ESAI_TSR,	 0x00000000पूर्ण,
	अणुREG_ESAI_SAICR, 0x00000000पूर्ण,
	अणुREG_ESAI_TCR,	 0x00000000पूर्ण,
	अणुREG_ESAI_TCCR,	 0x00000000पूर्ण,
	अणुREG_ESAI_RCR,	 0x00000000पूर्ण,
	अणुREG_ESAI_RCCR,	 0x00000000पूर्ण,
	अणुREG_ESAI_TSMA,  0x0000ffffपूर्ण,
	अणुREG_ESAI_TSMB,  0x0000ffffपूर्ण,
	अणुREG_ESAI_RSMA,  0x0000ffffपूर्ण,
	अणुREG_ESAI_RSMB,  0x0000ffffपूर्ण,
	अणुREG_ESAI_PRRC,  0x00000000पूर्ण,
	अणुREG_ESAI_PCRC,  0x00000000पूर्ण,
पूर्ण;

अटल bool fsl_esai_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल REG_ESAI_ERDR:
	हाल REG_ESAI_ECR:
	हाल REG_ESAI_ESR:
	हाल REG_ESAI_TFCR:
	हाल REG_ESAI_TFSR:
	हाल REG_ESAI_RFCR:
	हाल REG_ESAI_RFSR:
	हाल REG_ESAI_RX0:
	हाल REG_ESAI_RX1:
	हाल REG_ESAI_RX2:
	हाल REG_ESAI_RX3:
	हाल REG_ESAI_SAISR:
	हाल REG_ESAI_SAICR:
	हाल REG_ESAI_TCR:
	हाल REG_ESAI_TCCR:
	हाल REG_ESAI_RCR:
	हाल REG_ESAI_RCCR:
	हाल REG_ESAI_TSMA:
	हाल REG_ESAI_TSMB:
	हाल REG_ESAI_RSMA:
	हाल REG_ESAI_RSMB:
	हाल REG_ESAI_PRRC:
	हाल REG_ESAI_PCRC:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool fsl_esai_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल REG_ESAI_ERDR:
	हाल REG_ESAI_ESR:
	हाल REG_ESAI_TFSR:
	हाल REG_ESAI_RFSR:
	हाल REG_ESAI_RX0:
	हाल REG_ESAI_RX1:
	हाल REG_ESAI_RX2:
	हाल REG_ESAI_RX3:
	हाल REG_ESAI_SAISR:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool fsl_esai_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल REG_ESAI_ETDR:
	हाल REG_ESAI_ECR:
	हाल REG_ESAI_TFCR:
	हाल REG_ESAI_RFCR:
	हाल REG_ESAI_TX0:
	हाल REG_ESAI_TX1:
	हाल REG_ESAI_TX2:
	हाल REG_ESAI_TX3:
	हाल REG_ESAI_TX4:
	हाल REG_ESAI_TX5:
	हाल REG_ESAI_TSR:
	हाल REG_ESAI_SAICR:
	हाल REG_ESAI_TCR:
	हाल REG_ESAI_TCCR:
	हाल REG_ESAI_RCR:
	हाल REG_ESAI_RCCR:
	हाल REG_ESAI_TSMA:
	हाल REG_ESAI_TSMB:
	हाल REG_ESAI_RSMA:
	हाल REG_ESAI_RSMB:
	हाल REG_ESAI_PRRC:
	हाल REG_ESAI_PCRC:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config fsl_esai_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,

	.max_रेजिस्टर = REG_ESAI_PCRC,
	.reg_शेषs = fsl_esai_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(fsl_esai_reg_शेषs),
	.पढ़ोable_reg = fsl_esai_पढ़ोable_reg,
	.अस्थिर_reg = fsl_esai_अस्थिर_reg,
	.ग_लिखोable_reg = fsl_esai_ग_लिखोable_reg,
	.cache_type = REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक fsl_esai_runसमय_resume(काष्ठा device *dev);
अटल पूर्णांक fsl_esai_runसमय_suspend(काष्ठा device *dev);

अटल पूर्णांक fsl_esai_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा fsl_esai *esai_priv;
	काष्ठा resource *res;
	स्थिर __be32 *iprop;
	व्योम __iomem *regs;
	पूर्णांक irq, ret;

	esai_priv = devm_kzalloc(&pdev->dev, माप(*esai_priv), GFP_KERNEL);
	अगर (!esai_priv)
		वापस -ENOMEM;

	esai_priv->pdev = pdev;
	snम_लिखो(esai_priv->name, माप(esai_priv->name), "%pOFn", np);

	esai_priv->soc = of_device_get_match_data(&pdev->dev);

	/* Get the addresses and IRQ */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	esai_priv->regmap = devm_regmap_init_mmio(&pdev->dev, regs, &fsl_esai_regmap_config);
	अगर (IS_ERR(esai_priv->regmap)) अणु
		dev_err(&pdev->dev, "failed to init regmap: %ld\n",
				PTR_ERR(esai_priv->regmap));
		वापस PTR_ERR(esai_priv->regmap);
	पूर्ण

	esai_priv->coreclk = devm_clk_get(&pdev->dev, "core");
	अगर (IS_ERR(esai_priv->coreclk)) अणु
		dev_err(&pdev->dev, "failed to get core clock: %ld\n",
				PTR_ERR(esai_priv->coreclk));
		वापस PTR_ERR(esai_priv->coreclk);
	पूर्ण

	esai_priv->extalclk = devm_clk_get(&pdev->dev, "extal");
	अगर (IS_ERR(esai_priv->extalclk))
		dev_warn(&pdev->dev, "failed to get extal clock: %ld\n",
				PTR_ERR(esai_priv->extalclk));

	esai_priv->fsysclk = devm_clk_get(&pdev->dev, "fsys");
	अगर (IS_ERR(esai_priv->fsysclk))
		dev_warn(&pdev->dev, "failed to get fsys clock: %ld\n",
				PTR_ERR(esai_priv->fsysclk));

	esai_priv->spbaclk = devm_clk_get(&pdev->dev, "spba");
	अगर (IS_ERR(esai_priv->spbaclk))
		dev_warn(&pdev->dev, "failed to get spba clock: %ld\n",
				PTR_ERR(esai_priv->spbaclk));

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(&pdev->dev, irq, esai_isr, IRQF_SHARED,
			       esai_priv->name, esai_priv);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to claim irq %u\n", irq);
		वापस ret;
	पूर्ण

	/* Set a शेष slot number */
	esai_priv->slots = 2;

	/* Set a शेष master/slave state */
	esai_priv->slave_mode = true;

	/* Determine the FIFO depth */
	iprop = of_get_property(np, "fsl,fifo-depth", शून्य);
	अगर (iprop)
		esai_priv->fअगरo_depth = be32_to_cpup(iprop);
	अन्यथा
		esai_priv->fअगरo_depth = 64;

	esai_priv->dma_params_tx.maxburst = 16;
	esai_priv->dma_params_rx.maxburst = 16;
	esai_priv->dma_params_tx.addr = res->start + REG_ESAI_ETDR;
	esai_priv->dma_params_rx.addr = res->start + REG_ESAI_ERDR;

	esai_priv->synchronous =
		of_property_पढ़ो_bool(np, "fsl,esai-synchronous");

	/* Implement full symmetry क्रम synchronous mode */
	अगर (esai_priv->synchronous) अणु
		fsl_esai_dai.symmetric_rate = 1;
		fsl_esai_dai.symmetric_channels = 1;
		fsl_esai_dai.symmetric_sample_bits = 1;
	पूर्ण

	dev_set_drvdata(&pdev->dev, esai_priv);
	spin_lock_init(&esai_priv->lock);
	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev)) अणु
		ret = fsl_esai_runसमय_resume(&pdev->dev);
		अगर (ret)
			जाओ err_pm_disable;
	पूर्ण

	ret = pm_runसमय_get_sync(&pdev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(&pdev->dev);
		जाओ err_pm_get_sync;
	पूर्ण

	ret = fsl_esai_hw_init(esai_priv);
	अगर (ret)
		जाओ err_pm_get_sync;

	esai_priv->tx_mask = 0xFFFFFFFF;
	esai_priv->rx_mask = 0xFFFFFFFF;

	/* Clear the TSMA, TSMB, RSMA, RSMB */
	regmap_ग_लिखो(esai_priv->regmap, REG_ESAI_TSMA, 0);
	regmap_ग_लिखो(esai_priv->regmap, REG_ESAI_TSMB, 0);
	regmap_ग_लिखो(esai_priv->regmap, REG_ESAI_RSMA, 0);
	regmap_ग_लिखो(esai_priv->regmap, REG_ESAI_RSMB, 0);

	ret = pm_runसमय_put_sync(&pdev->dev);
	अगर (ret < 0)
		जाओ err_pm_get_sync;

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &fsl_esai_component,
					      &fsl_esai_dai, 1);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to register DAI: %d\n", ret);
		जाओ err_pm_get_sync;
	पूर्ण

	INIT_WORK(&esai_priv->work, fsl_esai_hw_reset);

	ret = imx_pcm_dma_init(pdev, IMX_ESAI_DMABUF_SIZE);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to init imx pcm dma: %d\n", ret);
		जाओ err_pm_get_sync;
	पूर्ण

	वापस ret;

err_pm_get_sync:
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		fsl_esai_runसमय_suspend(&pdev->dev);
err_pm_disable:
	pm_runसमय_disable(&pdev->dev);
	वापस ret;
पूर्ण

अटल पूर्णांक fsl_esai_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_esai *esai_priv = platक्रमm_get_drvdata(pdev);

	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		fsl_esai_runसमय_suspend(&pdev->dev);

	cancel_work_sync(&esai_priv->work);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fsl_esai_dt_ids[] = अणु
	अणु .compatible = "fsl,imx35-esai", .data = &fsl_esai_imx35 पूर्ण,
	अणु .compatible = "fsl,vf610-esai", .data = &fsl_esai_vf610 पूर्ण,
	अणु .compatible = "fsl,imx6ull-esai", .data = &fsl_esai_imx6ull पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_esai_dt_ids);

अटल पूर्णांक fsl_esai_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा fsl_esai *esai = dev_get_drvdata(dev);
	पूर्णांक ret;

	/*
	 * Some platक्रमms might use the same bit to gate all three or two of
	 * घड़ीs, so keep all घड़ीs खोलो/बंद at the same समय क्रम safety
	 */
	ret = clk_prepare_enable(esai->coreclk);
	अगर (ret)
		वापस ret;
	अगर (!IS_ERR(esai->spbaclk)) अणु
		ret = clk_prepare_enable(esai->spbaclk);
		अगर (ret)
			जाओ err_spbaclk;
	पूर्ण
	अगर (!IS_ERR(esai->extalclk)) अणु
		ret = clk_prepare_enable(esai->extalclk);
		अगर (ret)
			जाओ err_extalclk;
	पूर्ण
	अगर (!IS_ERR(esai->fsysclk)) अणु
		ret = clk_prepare_enable(esai->fsysclk);
		अगर (ret)
			जाओ err_fsysclk;
	पूर्ण

	regcache_cache_only(esai->regmap, false);

	ret = fsl_esai_रेजिस्टर_restore(esai);
	अगर (ret)
		जाओ err_regcache_sync;

	वापस 0;

err_regcache_sync:
	अगर (!IS_ERR(esai->fsysclk))
		clk_disable_unprepare(esai->fsysclk);
err_fsysclk:
	अगर (!IS_ERR(esai->extalclk))
		clk_disable_unprepare(esai->extalclk);
err_extalclk:
	अगर (!IS_ERR(esai->spbaclk))
		clk_disable_unprepare(esai->spbaclk);
err_spbaclk:
	clk_disable_unprepare(esai->coreclk);

	वापस ret;
पूर्ण

अटल पूर्णांक fsl_esai_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा fsl_esai *esai = dev_get_drvdata(dev);

	regcache_cache_only(esai->regmap, true);

	अगर (!IS_ERR(esai->fsysclk))
		clk_disable_unprepare(esai->fsysclk);
	अगर (!IS_ERR(esai->extalclk))
		clk_disable_unprepare(esai->extalclk);
	अगर (!IS_ERR(esai->spbaclk))
		clk_disable_unprepare(esai->spbaclk);
	clk_disable_unprepare(esai->coreclk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops fsl_esai_pm_ops = अणु
	SET_RUNTIME_PM_OPS(fsl_esai_runसमय_suspend,
			   fsl_esai_runसमय_resume,
			   शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver fsl_esai_driver = अणु
	.probe = fsl_esai_probe,
	.हटाओ = fsl_esai_हटाओ,
	.driver = अणु
		.name = "fsl-esai-dai",
		.pm = &fsl_esai_pm_ops,
		.of_match_table = fsl_esai_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(fsl_esai_driver);

MODULE_AUTHOR("Freescale Semiconductor, Inc.");
MODULE_DESCRIPTION("Freescale ESAI CPU DAI driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:fsl-esai-dai");
