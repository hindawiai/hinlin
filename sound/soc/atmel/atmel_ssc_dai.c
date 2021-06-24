<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * aपंचांगel_ssc_dai.c  --  ALSA SoC ATMEL SSC Audio Layer Platक्रमm driver
 *
 * Copyright (C) 2005 SAN People
 * Copyright (C) 2008 Aपंचांगel
 *
 * Author: Sedji Gaouaou <sedji.gaouaou@aपंचांगel.com>
 *         ATMEL CORP.
 *
 * Based on at91-ssc.c by
 * Frank Mandarino <fmandarino@endrelia.com>
 * Based on pxa2xx Platक्रमm drivers by
 * Liam Girdwood <lrg@slimlogic.co.uk>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/aपंचांगel_pdc.h>

#समावेश <linux/aपंचांगel-ssc.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>

#समावेश "atmel-pcm.h"
#समावेश "atmel_ssc_dai.h"


#घोषणा NUM_SSC_DEVICES		3

/*
 * SSC PDC रेजिस्टरs required by the PCM DMA engine.
 */
अटल काष्ठा aपंचांगel_pdc_regs pdc_tx_reg = अणु
	.xpr		= ATMEL_PDC_TPR,
	.xcr		= ATMEL_PDC_TCR,
	.xnpr		= ATMEL_PDC_TNPR,
	.xncr		= ATMEL_PDC_TNCR,
पूर्ण;

अटल काष्ठा aपंचांगel_pdc_regs pdc_rx_reg = अणु
	.xpr		= ATMEL_PDC_RPR,
	.xcr		= ATMEL_PDC_RCR,
	.xnpr		= ATMEL_PDC_RNPR,
	.xncr		= ATMEL_PDC_RNCR,
पूर्ण;

/*
 * SSC & PDC status bits क्रम transmit and receive.
 */
अटल काष्ठा aपंचांगel_ssc_mask ssc_tx_mask = अणु
	.ssc_enable	= SSC_BIT(CR_TXEN),
	.ssc_disable	= SSC_BIT(CR_TXDIS),
	.ssc_endx	= SSC_BIT(SR_ENDTX),
	.ssc_endbuf	= SSC_BIT(SR_TXBUFE),
	.ssc_error	= SSC_BIT(SR_OVRUN),
	.pdc_enable	= ATMEL_PDC_TXTEN,
	.pdc_disable	= ATMEL_PDC_TXTDIS,
पूर्ण;

अटल काष्ठा aपंचांगel_ssc_mask ssc_rx_mask = अणु
	.ssc_enable	= SSC_BIT(CR_RXEN),
	.ssc_disable	= SSC_BIT(CR_RXDIS),
	.ssc_endx	= SSC_BIT(SR_ENDRX),
	.ssc_endbuf	= SSC_BIT(SR_RXBUFF),
	.ssc_error	= SSC_BIT(SR_OVRUN),
	.pdc_enable	= ATMEL_PDC_RXTEN,
	.pdc_disable	= ATMEL_PDC_RXTDIS,
पूर्ण;


/*
 * DMA parameters.
 */
अटल काष्ठा aपंचांगel_pcm_dma_params ssc_dma_params[NUM_SSC_DEVICES][2] = अणु
	अणुअणु
	.name		= "SSC0 PCM out",
	.pdc		= &pdc_tx_reg,
	.mask		= &ssc_tx_mask,
	पूर्ण,
	अणु
	.name		= "SSC0 PCM in",
	.pdc		= &pdc_rx_reg,
	.mask		= &ssc_rx_mask,
	पूर्ण पूर्ण,
	अणुअणु
	.name		= "SSC1 PCM out",
	.pdc		= &pdc_tx_reg,
	.mask		= &ssc_tx_mask,
	पूर्ण,
	अणु
	.name		= "SSC1 PCM in",
	.pdc		= &pdc_rx_reg,
	.mask		= &ssc_rx_mask,
	पूर्ण पूर्ण,
	अणुअणु
	.name		= "SSC2 PCM out",
	.pdc		= &pdc_tx_reg,
	.mask		= &ssc_tx_mask,
	पूर्ण,
	अणु
	.name		= "SSC2 PCM in",
	.pdc		= &pdc_rx_reg,
	.mask		= &ssc_rx_mask,
	पूर्ण पूर्ण,
पूर्ण;


अटल काष्ठा aपंचांगel_ssc_info ssc_info[NUM_SSC_DEVICES] = अणु
	अणु
	.name		= "ssc0",
	.dir_mask	= SSC_सूची_MASK_UNUSED,
	.initialized	= 0,
	पूर्ण,
	अणु
	.name		= "ssc1",
	.dir_mask	= SSC_सूची_MASK_UNUSED,
	.initialized	= 0,
	पूर्ण,
	अणु
	.name		= "ssc2",
	.dir_mask	= SSC_सूची_MASK_UNUSED,
	.initialized	= 0,
	पूर्ण,
पूर्ण;


/*
 * SSC पूर्णांकerrupt handler.  Passes PDC पूर्णांकerrupts to the DMA
 * पूर्णांकerrupt handler in the PCM driver.
 */
अटल irqवापस_t aपंचांगel_ssc_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा aपंचांगel_ssc_info *ssc_p = dev_id;
	काष्ठा aपंचांगel_pcm_dma_params *dma_params;
	u32 ssc_sr;
	u32 ssc_substream_mask;
	पूर्णांक i;

	ssc_sr = (अचिन्हित दीर्घ)ssc_पढ़ोl(ssc_p->ssc->regs, SR)
			& (अचिन्हित दीर्घ)ssc_पढ़ोl(ssc_p->ssc->regs, IMR);

	/*
	 * Loop through the substreams attached to this SSC.  If
	 * a DMA-related पूर्णांकerrupt occurred on that substream, call
	 * the DMA पूर्णांकerrupt handler function, अगर one has been
	 * रेजिस्टरed in the dma_params काष्ठाure by the PCM driver.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(ssc_p->dma_params); i++) अणु
		dma_params = ssc_p->dma_params[i];

		अगर ((dma_params != शून्य) &&
			(dma_params->dma_पूर्णांकr_handler != शून्य)) अणु
			ssc_substream_mask = (dma_params->mask->ssc_endx |
					dma_params->mask->ssc_endbuf);
			अगर (ssc_sr & ssc_substream_mask) अणु
				dma_params->dma_पूर्णांकr_handler(ssc_sr,
						dma_params->
						substream);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/*
 * When the bit घड़ी is input, limit the maximum rate according to the
 * Serial Clock Ratio Considerations section from the SSC करोcumentation:
 *
 *   The Transmitter and the Receiver can be programmed to operate
 *   with the घड़ी संकेतs provided on either the TK or RK pins.
 *   This allows the SSC to support many slave-mode data transfers.
 *   In this हाल, the maximum घड़ी speed allowed on the RK pin is:
 *   - Peripheral घड़ी भागided by 2 अगर Receiver Frame Synchro is input
 *   - Peripheral घड़ी भागided by 3 अगर Receiver Frame Synchro is output
 *   In addition, the maximum घड़ी speed allowed on the TK pin is:
 *   - Peripheral घड़ी भागided by 6 अगर Transmit Frame Synchro is input
 *   - Peripheral घड़ी भागided by 2 अगर Transmit Frame Synchro is output
 *
 * When the bit घड़ी is output, limit the rate according to the
 * SSC भागider restrictions.
 */
अटल पूर्णांक aपंचांगel_ssc_hw_rule_rate(काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा aपंचांगel_ssc_info *ssc_p = rule->निजी;
	काष्ठा ssc_device *ssc = ssc_p->ssc;
	काष्ठा snd_पूर्णांकerval *i = hw_param_पूर्णांकerval(params, rule->var);
	काष्ठा snd_पूर्णांकerval t;
	काष्ठा snd_ratnum r = अणु
		.den_min = 1,
		.den_max = 4095,
		.den_step = 1,
	पूर्ण;
	अचिन्हित पूर्णांक num = 0, den = 0;
	पूर्णांक frame_size;
	पूर्णांक mck_भाग = 2;
	पूर्णांक ret;

	frame_size = snd_soc_params_to_frame_size(params);
	अगर (frame_size < 0)
		वापस frame_size;

	चयन (ssc_p->daअगरmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFS:
		अगर ((ssc_p->dir_mask & SSC_सूची_MASK_CAPTURE)
		    && ssc->clk_from_rk_pin)
			/* Receiver Frame Synchro (i.e. capture)
			 * is output (क्रमmat is _CFS) and the RK pin
			 * is used क्रम input (क्रमmat is _CBM_).
			 */
			mck_भाग = 3;
		अवरोध;

	हाल SND_SOC_DAIFMT_CBM_CFM:
		अगर ((ssc_p->dir_mask & SSC_सूची_MASK_PLAYBACK)
		    && !ssc->clk_from_rk_pin)
			/* Transmit Frame Synchro (i.e. playback)
			 * is input (क्रमmat is _CFM) and the TK pin
			 * is used क्रम input (क्रमmat _CBM_ but not
			 * using the RK pin).
			 */
			mck_भाग = 6;
		अवरोध;
	पूर्ण

	चयन (ssc_p->daअगरmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		r.num = ssc_p->mck_rate / mck_भाग / frame_size;

		ret = snd_पूर्णांकerval_ratnum(i, 1, &r, &num, &den);
		अगर (ret >= 0 && den && rule->var == SNDRV_PCM_HW_PARAM_RATE) अणु
			params->rate_num = num;
			params->rate_den = den;
		पूर्ण
		अवरोध;

	हाल SND_SOC_DAIFMT_CBM_CFS:
	हाल SND_SOC_DAIFMT_CBM_CFM:
		t.min = 8000;
		t.max = ssc_p->mck_rate / mck_भाग / frame_size;
		t.खोलोmin = t.खोलोmax = 0;
		t.पूर्णांकeger = 0;
		ret = snd_पूर्णांकerval_refine(i, &t);
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*-------------------------------------------------------------------------*\
 * DAI functions
\*-------------------------------------------------------------------------*/
/*
 * Startup.  Only that one substream allowed in each direction.
 */
अटल पूर्णांक aपंचांगel_ssc_startup(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dai->dev);
	काष्ठा aपंचांगel_ssc_info *ssc_p = &ssc_info[pdev->id];
	काष्ठा aपंचांगel_pcm_dma_params *dma_params;
	पूर्णांक dir, dir_mask;
	पूर्णांक ret;

	pr_debug("atmel_ssc_startup: SSC_SR=0x%x\n",
		ssc_पढ़ोl(ssc_p->ssc->regs, SR));

	/* Enable PMC peripheral घड़ी क्रम this SSC */
	pr_debug("atmel_ssc_dai: Starting clock\n");
	clk_enable(ssc_p->ssc->clk);
	ssc_p->mck_rate = clk_get_rate(ssc_p->ssc->clk);

	/* Reset the SSC unless initialized to keep it in a clean state */
	अगर (!ssc_p->initialized)
		ssc_ग_लिखोl(ssc_p->ssc->regs, CR, SSC_BIT(CR_SWRST));

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		dir = 0;
		dir_mask = SSC_सूची_MASK_PLAYBACK;
	पूर्ण अन्यथा अणु
		dir = 1;
		dir_mask = SSC_सूची_MASK_CAPTURE;
	पूर्ण

	ret = snd_pcm_hw_rule_add(substream->runसमय, 0,
				  SNDRV_PCM_HW_PARAM_RATE,
				  aपंचांगel_ssc_hw_rule_rate,
				  ssc_p,
				  SNDRV_PCM_HW_PARAM_FRAME_BITS,
				  SNDRV_PCM_HW_PARAM_CHANNELS, -1);
	अगर (ret < 0) अणु
		dev_err(dai->dev, "Failed to specify rate rule: %d\n", ret);
		वापस ret;
	पूर्ण

	dma_params = &ssc_dma_params[pdev->id][dir];
	dma_params->ssc = ssc_p->ssc;
	dma_params->substream = substream;

	ssc_p->dma_params[dir] = dma_params;

	snd_soc_dai_set_dma_data(dai, substream, dma_params);

	अगर (ssc_p->dir_mask & dir_mask)
		वापस -EBUSY;

	ssc_p->dir_mask |= dir_mask;

	वापस 0;
पूर्ण

/*
 * Shutकरोwn.  Clear DMA parameters and shutकरोwn the SSC अगर there
 * are no other substreams खोलो.
 */
अटल व्योम aपंचांगel_ssc_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dai->dev);
	काष्ठा aपंचांगel_ssc_info *ssc_p = &ssc_info[pdev->id];
	काष्ठा aपंचांगel_pcm_dma_params *dma_params;
	पूर्णांक dir, dir_mask;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		dir = 0;
	अन्यथा
		dir = 1;

	dma_params = ssc_p->dma_params[dir];

	अगर (dma_params != शून्य) अणु
		dma_params->ssc = शून्य;
		dma_params->substream = शून्य;
		ssc_p->dma_params[dir] = शून्य;
	पूर्ण

	dir_mask = 1 << dir;

	ssc_p->dir_mask &= ~dir_mask;
	अगर (!ssc_p->dir_mask) अणु
		अगर (ssc_p->initialized) अणु
			मुक्त_irq(ssc_p->ssc->irq, ssc_p);
			ssc_p->initialized = 0;
		पूर्ण

		/* Reset the SSC */
		ssc_ग_लिखोl(ssc_p->ssc->regs, CR, SSC_BIT(CR_SWRST));
		/* Clear the SSC भागiders */
		ssc_p->cmr_भाग = ssc_p->tcmr_period = ssc_p->rcmr_period = 0;
		ssc_p->क्रमced_भागider = 0;
	पूर्ण

	/* Shutकरोwn the SSC घड़ी. */
	pr_debug("atmel_ssc_dai: Stopping clock\n");
	clk_disable(ssc_p->ssc->clk);
पूर्ण


/*
 * Record the DAI क्रमmat क्रम use in hw_params().
 */
अटल पूर्णांक aपंचांगel_ssc_set_dai_fmt(काष्ठा snd_soc_dai *cpu_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(cpu_dai->dev);
	काष्ठा aपंचांगel_ssc_info *ssc_p = &ssc_info[pdev->id];

	ssc_p->daअगरmt = fmt;
	वापस 0;
पूर्ण

/*
 * Record SSC घड़ी भागiders क्रम use in hw_params().
 */
अटल पूर्णांक aपंचांगel_ssc_set_dai_clkभाग(काष्ठा snd_soc_dai *cpu_dai,
	पूर्णांक भाग_id, पूर्णांक भाग)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(cpu_dai->dev);
	काष्ठा aपंचांगel_ssc_info *ssc_p = &ssc_info[pdev->id];

	चयन (भाग_id) अणु
	हाल ATMEL_SSC_CMR_DIV:
		/*
		 * The same master घड़ी भागider is used क्रम both
		 * transmit and receive, so अगर a value has alपढ़ोy
		 * been set, it must match this value.
		 */
		अगर (ssc_p->dir_mask !=
			(SSC_सूची_MASK_PLAYBACK | SSC_सूची_MASK_CAPTURE))
			ssc_p->cmr_भाग = भाग;
		अन्यथा अगर (ssc_p->cmr_भाग == 0)
			ssc_p->cmr_भाग = भाग;
		अन्यथा
			अगर (भाग != ssc_p->cmr_भाग)
				वापस -EBUSY;
		ssc_p->क्रमced_भागider |= BIT(ATMEL_SSC_CMR_DIV);
		अवरोध;

	हाल ATMEL_SSC_TCMR_PERIOD:
		ssc_p->tcmr_period = भाग;
		ssc_p->क्रमced_भागider |= BIT(ATMEL_SSC_TCMR_PERIOD);
		अवरोध;

	हाल ATMEL_SSC_RCMR_PERIOD:
		ssc_p->rcmr_period = भाग;
		ssc_p->क्रमced_भागider |= BIT(ATMEL_SSC_RCMR_PERIOD);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Is the cpu-dai master of the frame घड़ी? */
अटल पूर्णांक aपंचांगel_ssc_cfs(काष्ठा aपंचांगel_ssc_info *ssc_p)
अणु
	चयन (ssc_p->daअगरmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFS:
	हाल SND_SOC_DAIFMT_CBS_CFS:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* Is the cpu-dai master of the bit घड़ी? */
अटल पूर्णांक aपंचांगel_ssc_cbs(काष्ठा aपंचांगel_ssc_info *ssc_p)
अणु
	चयन (ssc_p->daअगरmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFM:
	हाल SND_SOC_DAIFMT_CBS_CFS:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Configure the SSC.
 */
अटल पूर्णांक aपंचांगel_ssc_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dai->dev);
	पूर्णांक id = pdev->id;
	काष्ठा aपंचांगel_ssc_info *ssc_p = &ssc_info[id];
	काष्ठा ssc_device *ssc = ssc_p->ssc;
	काष्ठा aपंचांगel_pcm_dma_params *dma_params;
	पूर्णांक dir, channels, bits;
	u32 tfmr, rfmr, tcmr, rcmr;
	पूर्णांक ret;
	पूर्णांक fslen, fslen_ext, fs_osync, fs_edge;
	u32 cmr_भाग;
	u32 tcmr_period;
	u32 rcmr_period;

	/*
	 * Currently, there is only one set of dma params क्रम
	 * each direction.  If more are added, this code will
	 * have to be changed to select the proper set.
	 */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		dir = 0;
	अन्यथा
		dir = 1;

	/*
	 * If the cpu dai should provide BCLK, but noone has provided the
	 * भागider needed क्रम that to work, fall back to something sensible.
	 */
	cmr_भाग = ssc_p->cmr_भाग;
	अगर (!(ssc_p->क्रमced_भागider & BIT(ATMEL_SSC_CMR_DIV)) &&
	    aपंचांगel_ssc_cbs(ssc_p)) अणु
		पूर्णांक bclk_rate = snd_soc_params_to_bclk(params);

		अगर (bclk_rate < 0) अणु
			dev_err(dai->dev, "unable to calculate cmr_div: %d\n",
				bclk_rate);
			वापस bclk_rate;
		पूर्ण

		cmr_भाग = DIV_ROUND_CLOSEST(ssc_p->mck_rate, 2 * bclk_rate);
	पूर्ण

	/*
	 * If the cpu dai should provide LRCLK, but noone has provided the
	 * भागiders needed क्रम that to work, fall back to something sensible.
	 */
	tcmr_period = ssc_p->tcmr_period;
	rcmr_period = ssc_p->rcmr_period;
	अगर (aपंचांगel_ssc_cfs(ssc_p)) अणु
		पूर्णांक frame_size = snd_soc_params_to_frame_size(params);

		अगर (frame_size < 0) अणु
			dev_err(dai->dev,
				"unable to calculate tx/rx cmr_period: %d\n",
				frame_size);
			वापस frame_size;
		पूर्ण

		अगर (!(ssc_p->क्रमced_भागider & BIT(ATMEL_SSC_TCMR_PERIOD)))
			tcmr_period = frame_size / 2 - 1;
		अगर (!(ssc_p->क्रमced_भागider & BIT(ATMEL_SSC_RCMR_PERIOD)))
			rcmr_period = frame_size / 2 - 1;
	पूर्ण

	dma_params = ssc_p->dma_params[dir];

	channels = params_channels(params);

	/*
	 * Determine sample size in bits and the PDC increment.
	 */
	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S8:
		bits = 8;
		dma_params->pdc_xfer_size = 1;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_LE:
		bits = 16;
		dma_params->pdc_xfer_size = 2;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
		bits = 24;
		dma_params->pdc_xfer_size = 4;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		bits = 32;
		dma_params->pdc_xfer_size = 4;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_WARNING "atmel_ssc_dai: unsupported PCM format");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Compute SSC रेजिस्टर settings.
	 */

	fslen_ext = (bits - 1) / 16;
	fslen = (bits - 1) % 16;

	चयन (ssc_p->daअगरmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु

	हाल SND_SOC_DAIFMT_LEFT_J:
		fs_osync = SSC_FSOS_POSITIVE;
		fs_edge = SSC_START_RISING_RF;

		rcmr =	  SSC_BF(RCMR_STTDLY, 0);
		tcmr =	  SSC_BF(TCMR_STTDLY, 0);

		अवरोध;

	हाल SND_SOC_DAIFMT_I2S:
		fs_osync = SSC_FSOS_NEGATIVE;
		fs_edge = SSC_START_FALLING_RF;

		rcmr =	  SSC_BF(RCMR_STTDLY, 1);
		tcmr =	  SSC_BF(TCMR_STTDLY, 1);

		अवरोध;

	हाल SND_SOC_DAIFMT_DSP_A:
		/*
		 * DSP/PCM Mode A क्रमmat
		 *
		 * Data is transferred on first BCLK after LRC pulse rising
		 * edge.If stereo, the right channel data is contiguous with
		 * the left channel data.
		 */
		fs_osync = SSC_FSOS_POSITIVE;
		fs_edge = SSC_START_RISING_RF;
		fslen = fslen_ext = 0;

		rcmr =	  SSC_BF(RCMR_STTDLY, 1);
		tcmr =	  SSC_BF(TCMR_STTDLY, 1);

		अवरोध;

	शेष:
		prपूर्णांकk(KERN_WARNING "atmel_ssc_dai: unsupported DAI format 0x%x\n",
			ssc_p->daअगरmt);
		वापस -EINVAL;
	पूर्ण

	अगर (!aपंचांगel_ssc_cfs(ssc_p)) अणु
		fslen = fslen_ext = 0;
		rcmr_period = tcmr_period = 0;
		fs_osync = SSC_FSOS_NONE;
	पूर्ण

	rcmr |=	  SSC_BF(RCMR_START, fs_edge);
	tcmr |=	  SSC_BF(TCMR_START, fs_edge);

	अगर (aपंचांगel_ssc_cbs(ssc_p)) अणु
		/*
		 * SSC provides BCLK
		 *
		 * The SSC transmit and receive घड़ीs are generated from the
		 * MCK भागider, and the BCLK संकेत is output
		 * on the SSC TK line.
		 */
		rcmr |=	  SSC_BF(RCMR_CKS, SSC_CKS_DIV)
			| SSC_BF(RCMR_CKO, SSC_CKO_NONE);

		tcmr |=	  SSC_BF(TCMR_CKS, SSC_CKS_DIV)
			| SSC_BF(TCMR_CKO, SSC_CKO_CONTINUOUS);
	पूर्ण अन्यथा अणु
		rcmr |=	  SSC_BF(RCMR_CKS, ssc->clk_from_rk_pin ?
					SSC_CKS_PIN : SSC_CKS_CLOCK)
			| SSC_BF(RCMR_CKO, SSC_CKO_NONE);

		tcmr |=	  SSC_BF(TCMR_CKS, ssc->clk_from_rk_pin ?
					SSC_CKS_CLOCK : SSC_CKS_PIN)
			| SSC_BF(TCMR_CKO, SSC_CKO_NONE);
	पूर्ण

	rcmr |=	  SSC_BF(RCMR_PERIOD, rcmr_period)
		| SSC_BF(RCMR_CKI, SSC_CKI_RISING);

	tcmr |=   SSC_BF(TCMR_PERIOD, tcmr_period)
		| SSC_BF(TCMR_CKI, SSC_CKI_FALLING);

	rfmr =    SSC_BF(RFMR_FSLEN_EXT, fslen_ext)
		| SSC_BF(RFMR_FSEDGE, SSC_FSEDGE_POSITIVE)
		| SSC_BF(RFMR_FSOS, fs_osync)
		| SSC_BF(RFMR_FSLEN, fslen)
		| SSC_BF(RFMR_DATNB, (channels - 1))
		| SSC_BIT(RFMR_MSBF)
		| SSC_BF(RFMR_LOOP, 0)
		| SSC_BF(RFMR_DATLEN, (bits - 1));

	tfmr =    SSC_BF(TFMR_FSLEN_EXT, fslen_ext)
		| SSC_BF(TFMR_FSEDGE, SSC_FSEDGE_POSITIVE)
		| SSC_BF(TFMR_FSDEN, 0)
		| SSC_BF(TFMR_FSOS, fs_osync)
		| SSC_BF(TFMR_FSLEN, fslen)
		| SSC_BF(TFMR_DATNB, (channels - 1))
		| SSC_BIT(TFMR_MSBF)
		| SSC_BF(TFMR_DATDEF, 0)
		| SSC_BF(TFMR_DATLEN, (bits - 1));

	अगर (fslen_ext && !ssc->pdata->has_fslen_ext) अणु
		dev_err(dai->dev, "sample size %d is too large for SSC device\n",
			bits);
		वापस -EINVAL;
	पूर्ण

	pr_debug("atmel_ssc_hw_params: "
			"RCMR=%08x RFMR=%08x TCMR=%08x TFMR=%08x\n",
			rcmr, rfmr, tcmr, tfmr);

	अगर (!ssc_p->initialized) अणु
		अगर (!ssc_p->ssc->pdata->use_dma) अणु
			ssc_ग_लिखोl(ssc_p->ssc->regs, PDC_RPR, 0);
			ssc_ग_लिखोl(ssc_p->ssc->regs, PDC_RCR, 0);
			ssc_ग_लिखोl(ssc_p->ssc->regs, PDC_RNPR, 0);
			ssc_ग_लिखोl(ssc_p->ssc->regs, PDC_RNCR, 0);

			ssc_ग_लिखोl(ssc_p->ssc->regs, PDC_TPR, 0);
			ssc_ग_लिखोl(ssc_p->ssc->regs, PDC_TCR, 0);
			ssc_ग_लिखोl(ssc_p->ssc->regs, PDC_TNPR, 0);
			ssc_ग_लिखोl(ssc_p->ssc->regs, PDC_TNCR, 0);
		पूर्ण

		ret = request_irq(ssc_p->ssc->irq, aपंचांगel_ssc_पूर्णांकerrupt, 0,
				ssc_p->name, ssc_p);
		अगर (ret < 0) अणु
			prपूर्णांकk(KERN_WARNING
					"atmel_ssc_dai: request_irq failure\n");
			pr_debug("Atmel_ssc_dai: Stopping clock\n");
			clk_disable(ssc_p->ssc->clk);
			वापस ret;
		पूर्ण

		ssc_p->initialized = 1;
	पूर्ण

	/* set SSC घड़ी mode रेजिस्टर */
	ssc_ग_लिखोl(ssc_p->ssc->regs, CMR, cmr_भाग);

	/* set receive घड़ी mode and क्रमmat */
	ssc_ग_लिखोl(ssc_p->ssc->regs, RCMR, rcmr);
	ssc_ग_लिखोl(ssc_p->ssc->regs, RFMR, rfmr);

	/* set transmit घड़ी mode and क्रमmat */
	ssc_ग_लिखोl(ssc_p->ssc->regs, TCMR, tcmr);
	ssc_ग_लिखोl(ssc_p->ssc->regs, TFMR, tfmr);

	pr_debug("atmel_ssc_dai,hw_params: SSC initialized\n");
	वापस 0;
पूर्ण


अटल पूर्णांक aपंचांगel_ssc_prepare(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dai->dev);
	काष्ठा aपंचांगel_ssc_info *ssc_p = &ssc_info[pdev->id];
	काष्ठा aपंचांगel_pcm_dma_params *dma_params;
	पूर्णांक dir;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		dir = 0;
	अन्यथा
		dir = 1;

	dma_params = ssc_p->dma_params[dir];

	ssc_ग_लिखोl(ssc_p->ssc->regs, CR, dma_params->mask->ssc_disable);
	ssc_ग_लिखोl(ssc_p->ssc->regs, IDR, dma_params->mask->ssc_error);

	pr_debug("%s enabled SSC_SR=0x%08x\n",
			dir ? "receive" : "transmit",
			ssc_पढ़ोl(ssc_p->ssc->regs, SR));
	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_ssc_trigger(काष्ठा snd_pcm_substream *substream,
			     पूर्णांक cmd, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dai->dev);
	काष्ठा aपंचांगel_ssc_info *ssc_p = &ssc_info[pdev->id];
	काष्ठा aपंचांगel_pcm_dma_params *dma_params;
	पूर्णांक dir;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		dir = 0;
	अन्यथा
		dir = 1;

	dma_params = ssc_p->dma_params[dir];

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		ssc_ग_लिखोl(ssc_p->ssc->regs, CR, dma_params->mask->ssc_enable);
		अवरोध;
	शेष:
		ssc_ग_लिखोl(ssc_p->ssc->regs, CR, dma_params->mask->ssc_disable);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक aपंचांगel_ssc_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा aपंचांगel_ssc_info *ssc_p;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(component->dev);

	अगर (!snd_soc_component_active(component))
		वापस 0;

	ssc_p = &ssc_info[pdev->id];

	/* Save the status रेजिस्टर beक्रमe disabling transmit and receive */
	ssc_p->ssc_state.ssc_sr = ssc_पढ़ोl(ssc_p->ssc->regs, SR);
	ssc_ग_लिखोl(ssc_p->ssc->regs, CR, SSC_BIT(CR_TXDIS) | SSC_BIT(CR_RXDIS));

	/* Save the current पूर्णांकerrupt mask, then disable unmasked पूर्णांकerrupts */
	ssc_p->ssc_state.ssc_imr = ssc_पढ़ोl(ssc_p->ssc->regs, IMR);
	ssc_ग_लिखोl(ssc_p->ssc->regs, IDR, ssc_p->ssc_state.ssc_imr);

	ssc_p->ssc_state.ssc_cmr = ssc_पढ़ोl(ssc_p->ssc->regs, CMR);
	ssc_p->ssc_state.ssc_rcmr = ssc_पढ़ोl(ssc_p->ssc->regs, RCMR);
	ssc_p->ssc_state.ssc_rfmr = ssc_पढ़ोl(ssc_p->ssc->regs, RFMR);
	ssc_p->ssc_state.ssc_tcmr = ssc_पढ़ोl(ssc_p->ssc->regs, TCMR);
	ssc_p->ssc_state.ssc_tfmr = ssc_पढ़ोl(ssc_p->ssc->regs, TFMR);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_ssc_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा aपंचांगel_ssc_info *ssc_p;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(component->dev);
	u32 cr;

	अगर (!snd_soc_component_active(component))
		वापस 0;

	ssc_p = &ssc_info[pdev->id];

	/* restore SSC रेजिस्टर settings */
	ssc_ग_लिखोl(ssc_p->ssc->regs, TFMR, ssc_p->ssc_state.ssc_tfmr);
	ssc_ग_लिखोl(ssc_p->ssc->regs, TCMR, ssc_p->ssc_state.ssc_tcmr);
	ssc_ग_लिखोl(ssc_p->ssc->regs, RFMR, ssc_p->ssc_state.ssc_rfmr);
	ssc_ग_लिखोl(ssc_p->ssc->regs, RCMR, ssc_p->ssc_state.ssc_rcmr);
	ssc_ग_लिखोl(ssc_p->ssc->regs, CMR, ssc_p->ssc_state.ssc_cmr);

	/* re-enable पूर्णांकerrupts */
	ssc_ग_लिखोl(ssc_p->ssc->regs, IER, ssc_p->ssc_state.ssc_imr);

	/* Re-enable receive and transmit as appropriate */
	cr = 0;
	cr |=
	    (ssc_p->ssc_state.ssc_sr & SSC_BIT(SR_RXEN)) ? SSC_BIT(CR_RXEN) : 0;
	cr |=
	    (ssc_p->ssc_state.ssc_sr & SSC_BIT(SR_TXEN)) ? SSC_BIT(CR_TXEN) : 0;
	ssc_ग_लिखोl(ssc_p->ssc->regs, CR, cr);

	वापस 0;
पूर्ण
#अन्यथा /* CONFIG_PM */
#  define aपंचांगel_ssc_suspend	शून्य
#  define aपंचांगel_ssc_resume	शून्य
#पूर्ण_अगर /* CONFIG_PM */

#घोषणा ATMEL_SSC_FORMATS (SNDRV_PCM_FMTBIT_S8     | SNDRV_PCM_FMTBIT_S16_LE |\
			  SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops aपंचांगel_ssc_dai_ops = अणु
	.startup	= aपंचांगel_ssc_startup,
	.shutकरोwn	= aपंचांगel_ssc_shutकरोwn,
	.prepare	= aपंचांगel_ssc_prepare,
	.trigger	= aपंचांगel_ssc_trigger,
	.hw_params	= aपंचांगel_ssc_hw_params,
	.set_fmt	= aपंचांगel_ssc_set_dai_fmt,
	.set_clkभाग	= aपंचांगel_ssc_set_dai_clkभाग,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver aपंचांगel_ssc_dai = अणु
		.playback = अणु
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_CONTINUOUS,
			.rate_min = 8000,
			.rate_max = 384000,
			.क्रमmats = ATMEL_SSC_FORMATS,पूर्ण,
		.capture = अणु
			.channels_min = 1,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_CONTINUOUS,
			.rate_min = 8000,
			.rate_max = 384000,
			.क्रमmats = ATMEL_SSC_FORMATS,पूर्ण,
		.ops = &aपंचांगel_ssc_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver aपंचांगel_ssc_component = अणु
	.name		= "atmel-ssc",
	.suspend	= aपंचांगel_ssc_suspend,
	.resume		= aपंचांगel_ssc_resume,
पूर्ण;

अटल पूर्णांक asoc_ssc_init(काष्ठा device *dev)
अणु
	काष्ठा ssc_device *ssc = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = devm_snd_soc_रेजिस्टर_component(dev, &aपंचांगel_ssc_component,
					 &aपंचांगel_ssc_dai, 1);
	अगर (ret) अणु
		dev_err(dev, "Could not register DAI: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (ssc->pdata->use_dma)
		ret = aपंचांगel_pcm_dma_platक्रमm_रेजिस्टर(dev);
	अन्यथा
		ret = aपंचांगel_pcm_pdc_platक्रमm_रेजिस्टर(dev);

	अगर (ret) अणु
		dev_err(dev, "Could not register PCM: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * aपंचांगel_ssc_set_audio - Allocate the specअगरied SSC क्रम audio use.
 * @ssc_id: SSD ID in [0, NUM_SSC_DEVICES[
 */
पूर्णांक aपंचांगel_ssc_set_audio(पूर्णांक ssc_id)
अणु
	काष्ठा ssc_device *ssc;
	पूर्णांक ret;

	/* If we can grab the SSC briefly to parent the DAI device off it */
	ssc = ssc_request(ssc_id);
	अगर (IS_ERR(ssc)) अणु
		pr_err("Unable to parent ASoC SSC DAI on SSC: %ld\n",
			PTR_ERR(ssc));
		वापस PTR_ERR(ssc);
	पूर्ण अन्यथा अणु
		ssc_info[ssc_id].ssc = ssc;
	पूर्ण

	ret = asoc_ssc_init(&ssc->pdev->dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_ssc_set_audio);

व्योम aपंचांगel_ssc_put_audio(पूर्णांक ssc_id)
अणु
	काष्ठा ssc_device *ssc = ssc_info[ssc_id].ssc;

	ssc_मुक्त(ssc);
पूर्ण
EXPORT_SYMBOL_GPL(aपंचांगel_ssc_put_audio);

/* Module inक्रमmation */
MODULE_AUTHOR("Sedji Gaouaou, sedji.gaouaou@atmel.com, www.atmel.com");
MODULE_DESCRIPTION("ATMEL SSC ASoC Interface");
MODULE_LICENSE("GPL");
