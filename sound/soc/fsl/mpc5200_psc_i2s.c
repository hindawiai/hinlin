<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Freescale MPC5200 PSC in I2S mode
// ALSA SoC Digital Audio Interface (DAI) driver
//
// Copyright (C) 2008 Secret Lab Technologies Ltd.
// Copyright (C) 2009 Jon Smirl, Digispeaker

#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश <यंत्र/mpc52xx_psc.h>

#समावेश "mpc5200_dma.h"

/**
 * PSC_I2S_RATES: sample rates supported by the I2S
 *
 * This driver currently only supports the PSC running in I2S slave mode,
 * which means the codec determines the sample rate.  Thereक्रमe, we tell
 * ALSA that we support all rates and let the codec driver decide what rates
 * are really supported.
 */
#घोषणा PSC_I2S_RATES SNDRV_PCM_RATE_CONTINUOUS

/**
 * PSC_I2S_FORMATS: audio क्रमmats supported by the PSC I2S mode
 */
#घोषणा PSC_I2S_FORMATS (SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_S16_BE | \
			 SNDRV_PCM_FMTBIT_S24_BE | SNDRV_PCM_FMTBIT_S32_BE)

अटल पूर्णांक psc_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा psc_dma *psc_dma = snd_soc_dai_get_drvdata(asoc_rtd_to_cpu(rtd, 0));
	u32 mode;

	dev_dbg(psc_dma->dev, "%s(substream=%p) p_size=%i p_bytes=%i"
		" periods=%i buffer_size=%i  buffer_bytes=%i\n",
		__func__, substream, params_period_size(params),
		params_period_bytes(params), params_periods(params),
		params_buffer_size(params), params_buffer_bytes(params));

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S8:
		mode = MPC52xx_PSC_SICR_SIM_CODEC_8;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_BE:
		mode = MPC52xx_PSC_SICR_SIM_CODEC_16;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_BE:
		mode = MPC52xx_PSC_SICR_SIM_CODEC_24;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_BE:
		mode = MPC52xx_PSC_SICR_SIM_CODEC_32;
		अवरोध;
	शेष:
		dev_dbg(psc_dma->dev, "invalid format\n");
		वापस -EINVAL;
	पूर्ण
	out_be32(&psc_dma->psc_regs->sicr, psc_dma->sicr | mode);

	वापस 0;
पूर्ण

/**
 * psc_i2s_set_sysclk: set the घड़ी frequency and direction
 *
 * This function is called by the machine driver to tell us what the घड़ी
 * frequency and direction are.
 *
 * Currently, we only support operating as a घड़ी slave (SND_SOC_CLOCK_IN),
 * and we करोn't care about the frequency.  Return an error अगर the direction
 * is not SND_SOC_CLOCK_IN.
 *
 * @clk_id: reserved, should be zero
 * @freq: the frequency of the given घड़ी ID, currently ignored
 * @dir: SND_SOC_CLOCK_IN (घड़ी slave) or SND_SOC_CLOCK_OUT (घड़ी master)
 */
अटल पूर्णांक psc_i2s_set_sysclk(काष्ठा snd_soc_dai *cpu_dai,
			      पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा psc_dma *psc_dma = snd_soc_dai_get_drvdata(cpu_dai);
	dev_dbg(psc_dma->dev, "psc_i2s_set_sysclk(cpu_dai=%p, dir=%i)\n",
				cpu_dai, dir);
	वापस (dir == SND_SOC_CLOCK_IN) ? 0 : -EINVAL;
पूर्ण

/**
 * psc_i2s_set_fmt: set the serial क्रमmat.
 *
 * This function is called by the machine driver to tell us what serial
 * क्रमmat to use.
 *
 * This driver only supports I2S mode.  Return an error अगर the क्रमmat is
 * not SND_SOC_DAIFMT_I2S.
 *
 * @क्रमmat: one of SND_SOC_DAIFMT_xxx
 */
अटल पूर्णांक psc_i2s_set_fmt(काष्ठा snd_soc_dai *cpu_dai, अचिन्हित पूर्णांक क्रमmat)
अणु
	काष्ठा psc_dma *psc_dma = snd_soc_dai_get_drvdata(cpu_dai);
	dev_dbg(psc_dma->dev, "psc_i2s_set_fmt(cpu_dai=%p, format=%i)\n",
				cpu_dai, क्रमmat);
	वापस (क्रमmat == SND_SOC_DAIFMT_I2S) ? 0 : -EINVAL;
पूर्ण

/* ---------------------------------------------------------------------
 * ALSA SoC Bindings
 *
 * - Digital Audio Interface (DAI) ढाँचा
 * - create/destroy dai hooks
 */

/**
 * psc_i2s_dai_ढाँचा: ढाँचा CPU Digital Audio Interface
 */
अटल स्थिर काष्ठा snd_soc_dai_ops psc_i2s_dai_ops = अणु
	.hw_params	= psc_i2s_hw_params,
	.set_sysclk	= psc_i2s_set_sysclk,
	.set_fmt	= psc_i2s_set_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver psc_i2s_dai[] = अणुअणु
	.name = "mpc5200-psc-i2s.0",
	.playback = अणु
		.stream_name = "I2S Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = PSC_I2S_RATES,
		.क्रमmats = PSC_I2S_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "I2S Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = PSC_I2S_RATES,
		.क्रमmats = PSC_I2S_FORMATS,
	पूर्ण,
	.ops = &psc_i2s_dai_ops,
पूर्ण पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver psc_i2s_component = अणु
	.name		= "mpc5200-i2s",
पूर्ण;

/* ---------------------------------------------------------------------
 * OF platक्रमm bus binding code:
 * - Probe/हटाओ operations
 * - OF device match table
 */
अटल पूर्णांक psc_i2s_of_probe(काष्ठा platक्रमm_device *op)
अणु
	पूर्णांक rc;
	काष्ठा psc_dma *psc_dma;
	काष्ठा mpc52xx_psc __iomem *regs;

	rc = mpc5200_audio_dma_create(op);
	अगर (rc != 0)
		वापस rc;

	rc = snd_soc_रेजिस्टर_component(&op->dev, &psc_i2s_component,
					psc_i2s_dai, ARRAY_SIZE(psc_i2s_dai));
	अगर (rc != 0) अणु
		pr_err("Failed to register DAI\n");
		वापस rc;
	पूर्ण

	psc_dma = dev_get_drvdata(&op->dev);
	regs = psc_dma->psc_regs;

	/* Configure the serial पूर्णांकerface mode; शेषing to CODEC8 mode */
	psc_dma->sicr = MPC52xx_PSC_SICR_DTS1 | MPC52xx_PSC_SICR_I2S |
			MPC52xx_PSC_SICR_CLKPOL;
	out_be32(&psc_dma->psc_regs->sicr,
		 psc_dma->sicr | MPC52xx_PSC_SICR_SIM_CODEC_8);

	/* Check क्रम the codec handle.  If it is not present then we
	 * are करोne */
	अगर (!of_get_property(op->dev.of_node, "codec-handle", शून्य))
		वापस 0;

	/* Due to errata in the dma mode; need to line up enabling
	 * the transmitter with a transition on the frame sync
	 * line */

	/* first make sure it is low */
	जबतक ((in_8(&regs->ipcr_acr.ipcr) & 0x80) != 0)
		;
	/* then रुको क्रम the transition to high */
	जबतक ((in_8(&regs->ipcr_acr.ipcr) & 0x80) == 0)
		;
	/* Finally, enable the PSC.
	 * Receiver must always be enabled; even when we only want
	 * transmit.  (see 15.3.2.3 of MPC5200B User's Guide) */

	/* Go */
	out_8(&psc_dma->psc_regs->command,
			MPC52xx_PSC_TX_ENABLE | MPC52xx_PSC_RX_ENABLE);

	वापस 0;

पूर्ण

अटल पूर्णांक psc_i2s_of_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	mpc5200_audio_dma_destroy(op);
	snd_soc_unरेजिस्टर_component(&op->dev);
	वापस 0;
पूर्ण

/* Match table क्रम of_platक्रमm binding */
अटल स्थिर काष्ठा of_device_id psc_i2s_match[] = अणु
	अणु .compatible = "fsl,mpc5200-psc-i2s", पूर्ण,
	अणु .compatible = "fsl,mpc5200b-psc-i2s", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, psc_i2s_match);

अटल काष्ठा platक्रमm_driver psc_i2s_driver = अणु
	.probe = psc_i2s_of_probe,
	.हटाओ = psc_i2s_of_हटाओ,
	.driver = अणु
		.name = "mpc5200-psc-i2s",
		.of_match_table = psc_i2s_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(psc_i2s_driver);

MODULE_AUTHOR("Grant Likely <grant.likely@secretlab.ca>");
MODULE_DESCRIPTION("Freescale MPC5200 PSC in I2S mode ASoC Driver");
MODULE_LICENSE("GPL");

