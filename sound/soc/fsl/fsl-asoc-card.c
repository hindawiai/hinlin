<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Freescale Generic ASoC Sound Card driver with ASRC
//
// Copyright (C) 2014 Freescale Semiconductor, Inc.
//
// Author: Nicolin Chen <nicoleotsuka@gmail.com>

#समावेश <linux/clk.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#अगर IS_ENABLED(CONFIG_SND_AC97_CODEC)
#समावेश <sound/ac97_codec.h>
#पूर्ण_अगर
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>
#समावेश <sound/simple_card_utils.h>

#समावेश "fsl_esai.h"
#समावेश "fsl_sai.h"
#समावेश "imx-audmux.h"

#समावेश "../codecs/sgtl5000.h"
#समावेश "../codecs/wm8962.h"
#समावेश "../codecs/wm8960.h"
#समावेश "../codecs/wm8994.h"

#घोषणा CS427x_SYSCLK_MCLK 0

#घोषणा RX 0
#घोषणा TX 1

/* Default DAI क्रमmat without Master and Slave flag */
#घोषणा DAI_FMT_BASE (SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF)

/**
 * काष्ठा codec_priv - CODEC निजी data
 * @mclk_freq: Clock rate of MCLK
 * @मुक्त_freq: Clock rate of MCLK क्रम hw_मुक्त()
 * @mclk_id: MCLK (or मुख्य घड़ी) id क्रम set_sysclk()
 * @fll_id: FLL (or secordary घड़ी) id क्रम set_sysclk()
 * @pll_id: PLL id क्रम set_pll()
 */
काष्ठा codec_priv अणु
	अचिन्हित दीर्घ mclk_freq;
	अचिन्हित दीर्घ मुक्त_freq;
	u32 mclk_id;
	u32 fll_id;
	u32 pll_id;
पूर्ण;

/**
 * काष्ठा cpu_priv - CPU निजी data
 * @sysclk_freq: SYSCLK rates क्रम set_sysclk()
 * @sysclk_dir: SYSCLK directions क्रम set_sysclk()
 * @sysclk_id: SYSCLK ids क्रम set_sysclk()
 * @slot_width: Slot width of each frame
 *
 * Note: [1] क्रम tx and [0] क्रम rx
 */
काष्ठा cpu_priv अणु
	अचिन्हित दीर्घ sysclk_freq[2];
	u32 sysclk_dir[2];
	u32 sysclk_id[2];
	u32 slot_width;
पूर्ण;

/**
 * काष्ठा fsl_asoc_card_priv - Freescale Generic ASOC card निजी data
 * @dai_link: DAI link काष्ठाure including normal one and DPCM link
 * @hp_jack: Headphone Jack काष्ठाure
 * @mic_jack: Microphone Jack काष्ठाure
 * @pdev: platक्रमm device poपूर्णांकer
 * @codec_priv: CODEC निजी data
 * @cpu_priv: CPU निजी data
 * @card: ASoC card काष्ठाure
 * @streams: Mask of current active streams
 * @sample_rate: Current sample rate
 * @sample_क्रमmat: Current sample क्रमmat
 * @asrc_rate: ASRC sample rate used by Back-Ends
 * @asrc_क्रमmat: ASRC sample क्रमmat used by Back-Ends
 * @dai_fmt: DAI क्रमmat between CPU and CODEC
 * @name: Card name
 */

काष्ठा fsl_asoc_card_priv अणु
	काष्ठा snd_soc_dai_link dai_link[3];
	काष्ठा asoc_simple_jack hp_jack;
	काष्ठा asoc_simple_jack mic_jack;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा codec_priv codec_priv;
	काष्ठा cpu_priv cpu_priv;
	काष्ठा snd_soc_card card;
	u8 streams;
	u32 sample_rate;
	snd_pcm_क्रमmat_t sample_क्रमmat;
	u32 asrc_rate;
	snd_pcm_क्रमmat_t asrc_क्रमmat;
	u32 dai_fmt;
	अक्षर name[32];
पूर्ण;

/*
 * This dapm route map exists क्रम DPCM link only.
 * The other routes shall go through Device Tree.
 *
 * Note: keep all ASRC routes in the second half
 *	 to drop them easily क्रम non-ASRC हालs.
 */
अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु
	/* 1st half -- Normal DAPM routes */
	अणु"Playback",  शून्य, "CPU-Playback"पूर्ण,
	अणु"CPU-Capture",  शून्य, "Capture"पूर्ण,
	/* 2nd half -- ASRC DAPM routes */
	अणु"CPU-Playback",  शून्य, "ASRC-Playback"पूर्ण,
	अणु"ASRC-Capture",  शून्य, "CPU-Capture"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map_ac97[] = अणु
	/* 1st half -- Normal DAPM routes */
	अणु"Playback",  शून्य, "AC97 Playback"पूर्ण,
	अणु"AC97 Capture",  शून्य, "Capture"पूर्ण,
	/* 2nd half -- ASRC DAPM routes */
	अणु"AC97 Playback",  शून्य, "ASRC-Playback"पूर्ण,
	अणु"ASRC-Capture",  शून्य, "AC97 Capture"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map_tx[] = अणु
	/* 1st half -- Normal DAPM routes */
	अणु"Playback",  शून्य, "CPU-Playback"पूर्ण,
	/* 2nd half -- ASRC DAPM routes */
	अणु"CPU-Playback",  शून्य, "ASRC-Playback"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map_rx[] = अणु
	/* 1st half -- Normal DAPM routes */
	अणु"CPU-Capture",  शून्य, "Capture"पूर्ण,
	/* 2nd half -- ASRC DAPM routes */
	अणु"ASRC-Capture",  शून्य, "CPU-Capture"पूर्ण,
पूर्ण;

/* Add all possible widमाला_लो पूर्णांकo here without being redundant */
अटल स्थिर काष्ठा snd_soc_dapm_widget fsl_asoc_card_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_LINE("Line Out Jack", शून्य),
	SND_SOC_DAPM_LINE("Line In Jack", शून्य),
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_SPK("Ext Spk", शून्य),
	SND_SOC_DAPM_MIC("Mic Jack", शून्य),
	SND_SOC_DAPM_MIC("AMIC", शून्य),
	SND_SOC_DAPM_MIC("DMIC", शून्य),
पूर्ण;

अटल bool fsl_asoc_card_is_ac97(काष्ठा fsl_asoc_card_priv *priv)
अणु
	वापस priv->dai_fmt == SND_SOC_DAIFMT_AC97;
पूर्ण

अटल पूर्णांक fsl_asoc_card_hw_params(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा fsl_asoc_card_priv *priv = snd_soc_card_get_drvdata(rtd->card);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	काष्ठा codec_priv *codec_priv = &priv->codec_priv;
	काष्ठा cpu_priv *cpu_priv = &priv->cpu_priv;
	काष्ठा device *dev = rtd->card->dev;
	अचिन्हित पूर्णांक pll_out;
	पूर्णांक ret;

	priv->sample_rate = params_rate(params);
	priv->sample_क्रमmat = params_क्रमmat(params);
	priv->streams |= BIT(substream->stream);

	अगर (fsl_asoc_card_is_ac97(priv))
		वापस 0;

	/* Specअगरic configurations of DAIs starts from here */
	ret = snd_soc_dai_set_sysclk(asoc_rtd_to_cpu(rtd, 0), cpu_priv->sysclk_id[tx],
				     cpu_priv->sysclk_freq[tx],
				     cpu_priv->sysclk_dir[tx]);
	अगर (ret && ret != -ENOTSUPP) अणु
		dev_err(dev, "failed to set sysclk for cpu dai\n");
		जाओ fail;
	पूर्ण

	अगर (cpu_priv->slot_width) अणु
		ret = snd_soc_dai_set_tdm_slot(asoc_rtd_to_cpu(rtd, 0), 0x3, 0x3, 2,
					       cpu_priv->slot_width);
		अगर (ret && ret != -ENOTSUPP) अणु
			dev_err(dev, "failed to set TDM slot for cpu dai\n");
			जाओ fail;
		पूर्ण
	पूर्ण

	/* Specअगरic configuration क्रम PLL */
	अगर (codec_priv->pll_id && codec_priv->fll_id) अणु
		अगर (priv->sample_क्रमmat == SNDRV_PCM_FORMAT_S24_LE)
			pll_out = priv->sample_rate * 384;
		अन्यथा
			pll_out = priv->sample_rate * 256;

		ret = snd_soc_dai_set_pll(asoc_rtd_to_codec(rtd, 0),
					  codec_priv->pll_id,
					  codec_priv->mclk_id,
					  codec_priv->mclk_freq, pll_out);
		अगर (ret) अणु
			dev_err(dev, "failed to start FLL: %d\n", ret);
			जाओ fail;
		पूर्ण

		ret = snd_soc_dai_set_sysclk(asoc_rtd_to_codec(rtd, 0),
					     codec_priv->fll_id,
					     pll_out, SND_SOC_CLOCK_IN);

		अगर (ret && ret != -ENOTSUPP) अणु
			dev_err(dev, "failed to set SYSCLK: %d\n", ret);
			जाओ fail;
		पूर्ण
	पूर्ण

	वापस 0;

fail:
	priv->streams &= ~BIT(substream->stream);
	वापस ret;
पूर्ण

अटल पूर्णांक fsl_asoc_card_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;
	काष्ठा fsl_asoc_card_priv *priv = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा codec_priv *codec_priv = &priv->codec_priv;
	काष्ठा device *dev = rtd->card->dev;
	पूर्णांक ret;

	priv->streams &= ~BIT(substream->stream);

	अगर (!priv->streams && codec_priv->pll_id && codec_priv->fll_id) अणु
		/* Force freq to be मुक्त_freq to aव्योम error message in codec */
		ret = snd_soc_dai_set_sysclk(asoc_rtd_to_codec(rtd, 0),
					     codec_priv->mclk_id,
					     codec_priv->मुक्त_freq,
					     SND_SOC_CLOCK_IN);
		अगर (ret) अणु
			dev_err(dev, "failed to switch away from FLL: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = snd_soc_dai_set_pll(asoc_rtd_to_codec(rtd, 0),
					  codec_priv->pll_id, 0, 0, 0);
		अगर (ret && ret != -ENOTSUPP) अणु
			dev_err(dev, "failed to stop FLL: %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops fsl_asoc_card_ops = अणु
	.hw_params = fsl_asoc_card_hw_params,
	.hw_मुक्त = fsl_asoc_card_hw_मुक्त,
पूर्ण;

अटल पूर्णांक be_hw_params_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
			      काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा fsl_asoc_card_priv *priv = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_पूर्णांकerval *rate;
	काष्ठा snd_mask *mask;

	rate = hw_param_पूर्णांकerval(params, SNDRV_PCM_HW_PARAM_RATE);
	rate->max = rate->min = priv->asrc_rate;

	mask = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	snd_mask_none(mask);
	snd_mask_set_क्रमmat(mask, priv->asrc_क्रमmat);

	वापस 0;
पूर्ण

SND_SOC_DAILINK_DEFS(hअगरi,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(hअगरi_fe,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(hअगरi_be,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_DUMMY()));

अटल काष्ठा snd_soc_dai_link fsl_asoc_card_dai[] = अणु
	/* Default ASoC DAI Link*/
	अणु
		.name = "HiFi",
		.stream_name = "HiFi",
		.ops = &fsl_asoc_card_ops,
		SND_SOC_DAILINK_REG(hअगरi),
	पूर्ण,
	/* DPCM Link between Front-End and Back-End (Optional) */
	अणु
		.name = "HiFi-ASRC-FE",
		.stream_name = "HiFi-ASRC-FE",
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.dynamic = 1,
		SND_SOC_DAILINK_REG(hअगरi_fe),
	पूर्ण,
	अणु
		.name = "HiFi-ASRC-BE",
		.stream_name = "HiFi-ASRC-BE",
		.be_hw_params_fixup = be_hw_params_fixup,
		.ops = &fsl_asoc_card_ops,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(hअगरi_be),
	पूर्ण,
पूर्ण;

अटल पूर्णांक fsl_asoc_card_audmux_init(काष्ठा device_node *np,
				     काष्ठा fsl_asoc_card_priv *priv)
अणु
	काष्ठा device *dev = &priv->pdev->dev;
	u32 पूर्णांक_ptcr = 0, ext_ptcr = 0;
	पूर्णांक पूर्णांक_port, ext_port;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u32(np, "mux-int-port", &पूर्णांक_port);
	अगर (ret) अणु
		dev_err(dev, "mux-int-port missing or invalid\n");
		वापस ret;
	पूर्ण
	ret = of_property_पढ़ो_u32(np, "mux-ext-port", &ext_port);
	अगर (ret) अणु
		dev_err(dev, "mux-ext-port missing or invalid\n");
		वापस ret;
	पूर्ण

	/*
	 * The port numbering in the hardware manual starts at 1, जबतक
	 * the AUDMUX API expects it starts at 0.
	 */
	पूर्णांक_port--;
	ext_port--;

	/*
	 * Use asynchronous mode (6 wires) क्रम all हालs except AC97.
	 * If only 4 wires are needed, just set SSI पूर्णांकo
	 * synchronous mode and enable 4 PADs in IOMUX.
	 */
	चयन (priv->dai_fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		पूर्णांक_ptcr = IMX_AUDMUX_V2_PTCR_RFSEL(8 | ext_port) |
			   IMX_AUDMUX_V2_PTCR_RCSEL(8 | ext_port) |
			   IMX_AUDMUX_V2_PTCR_TFSEL(ext_port) |
			   IMX_AUDMUX_V2_PTCR_TCSEL(ext_port) |
			   IMX_AUDMUX_V2_PTCR_RFSसूची |
			   IMX_AUDMUX_V2_PTCR_RCLKसूची |
			   IMX_AUDMUX_V2_PTCR_TFSसूची |
			   IMX_AUDMUX_V2_PTCR_TCLKसूची;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		पूर्णांक_ptcr = IMX_AUDMUX_V2_PTCR_RCSEL(8 | ext_port) |
			   IMX_AUDMUX_V2_PTCR_TCSEL(ext_port) |
			   IMX_AUDMUX_V2_PTCR_RCLKसूची |
			   IMX_AUDMUX_V2_PTCR_TCLKसूची;
		ext_ptcr = IMX_AUDMUX_V2_PTCR_RFSEL(8 | पूर्णांक_port) |
			   IMX_AUDMUX_V2_PTCR_TFSEL(पूर्णांक_port) |
			   IMX_AUDMUX_V2_PTCR_RFSसूची |
			   IMX_AUDMUX_V2_PTCR_TFSसूची;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		पूर्णांक_ptcr = IMX_AUDMUX_V2_PTCR_RFSEL(8 | ext_port) |
			   IMX_AUDMUX_V2_PTCR_TFSEL(ext_port) |
			   IMX_AUDMUX_V2_PTCR_RFSसूची |
			   IMX_AUDMUX_V2_PTCR_TFSसूची;
		ext_ptcr = IMX_AUDMUX_V2_PTCR_RCSEL(8 | पूर्णांक_port) |
			   IMX_AUDMUX_V2_PTCR_TCSEL(पूर्णांक_port) |
			   IMX_AUDMUX_V2_PTCR_RCLKसूची |
			   IMX_AUDMUX_V2_PTCR_TCLKसूची;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		ext_ptcr = IMX_AUDMUX_V2_PTCR_RFSEL(8 | पूर्णांक_port) |
			   IMX_AUDMUX_V2_PTCR_RCSEL(8 | पूर्णांक_port) |
			   IMX_AUDMUX_V2_PTCR_TFSEL(पूर्णांक_port) |
			   IMX_AUDMUX_V2_PTCR_TCSEL(पूर्णांक_port) |
			   IMX_AUDMUX_V2_PTCR_RFSसूची |
			   IMX_AUDMUX_V2_PTCR_RCLKसूची |
			   IMX_AUDMUX_V2_PTCR_TFSसूची |
			   IMX_AUDMUX_V2_PTCR_TCLKसूची;
		अवरोध;
	शेष:
		अगर (!fsl_asoc_card_is_ac97(priv))
			वापस -EINVAL;
	पूर्ण

	अगर (fsl_asoc_card_is_ac97(priv)) अणु
		पूर्णांक_ptcr = IMX_AUDMUX_V2_PTCR_SYN |
			   IMX_AUDMUX_V2_PTCR_TCSEL(ext_port) |
			   IMX_AUDMUX_V2_PTCR_TCLKसूची;
		ext_ptcr = IMX_AUDMUX_V2_PTCR_SYN |
			   IMX_AUDMUX_V2_PTCR_TFSEL(पूर्णांक_port) |
			   IMX_AUDMUX_V2_PTCR_TFSसूची;
	पूर्ण

	/* Asynchronous mode can not be set aदीर्घ with RCLKसूची */
	अगर (!fsl_asoc_card_is_ac97(priv)) अणु
		अचिन्हित पूर्णांक pdcr =
				IMX_AUDMUX_V2_PDCR_RXDSEL(ext_port);

		ret = imx_audmux_v2_configure_port(पूर्णांक_port, 0,
						   pdcr);
		अगर (ret) अणु
			dev_err(dev, "audmux internal port setup failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = imx_audmux_v2_configure_port(पूर्णांक_port, पूर्णांक_ptcr,
					   IMX_AUDMUX_V2_PDCR_RXDSEL(ext_port));
	अगर (ret) अणु
		dev_err(dev, "audmux internal port setup failed\n");
		वापस ret;
	पूर्ण

	अगर (!fsl_asoc_card_is_ac97(priv)) अणु
		अचिन्हित पूर्णांक pdcr =
				IMX_AUDMUX_V2_PDCR_RXDSEL(पूर्णांक_port);

		ret = imx_audmux_v2_configure_port(ext_port, 0,
						   pdcr);
		अगर (ret) अणु
			dev_err(dev, "audmux external port setup failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = imx_audmux_v2_configure_port(ext_port, ext_ptcr,
					   IMX_AUDMUX_V2_PDCR_RXDSEL(पूर्णांक_port));
	अगर (ret) अणु
		dev_err(dev, "audmux external port setup failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hp_jack_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			 व्योम *data)
अणु
	काष्ठा snd_soc_jack *jack = (काष्ठा snd_soc_jack *)data;
	काष्ठा snd_soc_dapm_context *dapm = &jack->card->dapm;

	अगर (event & SND_JACK_HEADPHONE)
		/* Disable speaker अगर headphone is plugged in */
		snd_soc_dapm_disable_pin(dapm, "Ext Spk");
	अन्यथा
		snd_soc_dapm_enable_pin(dapm, "Ext Spk");

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block hp_jack_nb = अणु
	.notअगरier_call = hp_jack_event,
पूर्ण;

अटल पूर्णांक mic_jack_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			  व्योम *data)
अणु
	काष्ठा snd_soc_jack *jack = (काष्ठा snd_soc_jack *)data;
	काष्ठा snd_soc_dapm_context *dapm = &jack->card->dapm;

	अगर (event & SND_JACK_MICROPHONE)
		/* Disable dmic अगर microphone is plugged in */
		snd_soc_dapm_disable_pin(dapm, "DMIC");
	अन्यथा
		snd_soc_dapm_enable_pin(dapm, "DMIC");

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block mic_jack_nb = अणु
	.notअगरier_call = mic_jack_event,
पूर्ण;

अटल पूर्णांक fsl_asoc_card_late_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा fsl_asoc_card_priv *priv = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_pcm_runसमय *rtd = list_first_entry(
			&card->rtd_list, काष्ठा snd_soc_pcm_runसमय, list);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा codec_priv *codec_priv = &priv->codec_priv;
	काष्ठा device *dev = card->dev;
	पूर्णांक ret;

	अगर (fsl_asoc_card_is_ac97(priv)) अणु
#अगर IS_ENABLED(CONFIG_SND_AC97_CODEC)
		काष्ठा snd_soc_component *component = asoc_rtd_to_codec(rtd, 0)->component;
		काष्ठा snd_ac97 *ac97 = snd_soc_component_get_drvdata(component);

		/*
		 * Use slots 3/4 क्रम S/PDIF so SSI won't try to enable
		 * other slots and send some samples there
		 * due to SLOTREQ bits क्रम S/PDIF received from codec
		 */
		snd_ac97_update_bits(ac97, AC97_EXTENDED_STATUS,
				     AC97_EA_SPSA_SLOT_MASK, AC97_EA_SPSA_3_4);
#पूर्ण_अगर

		वापस 0;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(codec_dai, codec_priv->mclk_id,
				     codec_priv->mclk_freq, SND_SOC_CLOCK_IN);
	अगर (ret && ret != -ENOTSUPP) अणु
		dev_err(dev, "failed to set sysclk in %s\n", __func__);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_asoc_card_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *cpu_np, *codec_np, *asrc_np;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा platक्रमm_device *asrc_pdev = शून्य;
	काष्ठा device_node *bitclkmaster = शून्य;
	काष्ठा device_node *framemaster = शून्य;
	काष्ठा platक्रमm_device *cpu_pdev;
	काष्ठा fsl_asoc_card_priv *priv;
	काष्ठा device *codec_dev = शून्य;
	स्थिर अक्षर *codec_dai_name;
	स्थिर अक्षर *codec_dev_name;
	अचिन्हित पूर्णांक daअगरmt;
	u32 width;
	पूर्णांक ret;

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	cpu_np = of_parse_phandle(np, "audio-cpu", 0);
	/* Give a chance to old DT binding */
	अगर (!cpu_np)
		cpu_np = of_parse_phandle(np, "ssi-controller", 0);
	अगर (!cpu_np) अणु
		dev_err(&pdev->dev, "CPU phandle missing or invalid\n");
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	cpu_pdev = of_find_device_by_node(cpu_np);
	अगर (!cpu_pdev) अणु
		dev_err(&pdev->dev, "failed to find CPU DAI device\n");
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	codec_np = of_parse_phandle(np, "audio-codec", 0);
	अगर (codec_np) अणु
		काष्ठा platक्रमm_device *codec_pdev;
		काष्ठा i2c_client *codec_i2c;

		codec_i2c = of_find_i2c_device_by_node(codec_np);
		अगर (codec_i2c) अणु
			codec_dev = &codec_i2c->dev;
			codec_dev_name = codec_i2c->name;
		पूर्ण
		अगर (!codec_dev) अणु
			codec_pdev = of_find_device_by_node(codec_np);
			अगर (codec_pdev) अणु
				codec_dev = &codec_pdev->dev;
				codec_dev_name = codec_pdev->name;
			पूर्ण
		पूर्ण
	पूर्ण

	asrc_np = of_parse_phandle(np, "audio-asrc", 0);
	अगर (asrc_np)
		asrc_pdev = of_find_device_by_node(asrc_np);

	/* Get the MCLK rate only, and leave it controlled by CODEC drivers */
	अगर (codec_dev) अणु
		काष्ठा clk *codec_clk = clk_get(codec_dev, शून्य);

		अगर (!IS_ERR(codec_clk)) अणु
			priv->codec_priv.mclk_freq = clk_get_rate(codec_clk);
			clk_put(codec_clk);
		पूर्ण
	पूर्ण

	/* Default sample rate and क्रमmat, will be updated in hw_params() */
	priv->sample_rate = 44100;
	priv->sample_क्रमmat = SNDRV_PCM_FORMAT_S16_LE;

	/* Assign a शेष DAI क्रमmat, and allow each card to overग_लिखो it */
	priv->dai_fmt = DAI_FMT_BASE;

	स_नकल(priv->dai_link, fsl_asoc_card_dai,
	       माप(काष्ठा snd_soc_dai_link) * ARRAY_SIZE(priv->dai_link));

	priv->card.dapm_routes = audio_map;
	priv->card.num_dapm_routes = ARRAY_SIZE(audio_map);
	/* Diversअगरy the card configurations */
	अगर (of_device_is_compatible(np, "fsl,imx-audio-cs42888")) अणु
		codec_dai_name = "cs42888";
		priv->cpu_priv.sysclk_freq[TX] = priv->codec_priv.mclk_freq;
		priv->cpu_priv.sysclk_freq[RX] = priv->codec_priv.mclk_freq;
		priv->cpu_priv.sysclk_dir[TX] = SND_SOC_CLOCK_OUT;
		priv->cpu_priv.sysclk_dir[RX] = SND_SOC_CLOCK_OUT;
		priv->cpu_priv.slot_width = 32;
		priv->dai_fmt |= SND_SOC_DAIFMT_CBS_CFS;
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "fsl,imx-audio-cs427x")) अणु
		codec_dai_name = "cs4271-hifi";
		priv->codec_priv.mclk_id = CS427x_SYSCLK_MCLK;
		priv->dai_fmt |= SND_SOC_DAIFMT_CBM_CFM;
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "fsl,imx-audio-sgtl5000")) अणु
		codec_dai_name = "sgtl5000";
		priv->codec_priv.mclk_id = SGTL5000_SYSCLK;
		priv->dai_fmt |= SND_SOC_DAIFMT_CBM_CFM;
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "fsl,imx-audio-tlv320aic32x4")) अणु
		codec_dai_name = "tlv320aic32x4-hifi";
		priv->dai_fmt |= SND_SOC_DAIFMT_CBM_CFM;
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "fsl,imx-audio-wm8962")) अणु
		codec_dai_name = "wm8962";
		priv->codec_priv.mclk_id = WM8962_SYSCLK_MCLK;
		priv->codec_priv.fll_id = WM8962_SYSCLK_FLL;
		priv->codec_priv.pll_id = WM8962_FLL;
		priv->dai_fmt |= SND_SOC_DAIFMT_CBM_CFM;
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "fsl,imx-audio-wm8960")) अणु
		codec_dai_name = "wm8960-hifi";
		priv->codec_priv.fll_id = WM8960_SYSCLK_AUTO;
		priv->codec_priv.pll_id = WM8960_SYSCLK_AUTO;
		priv->dai_fmt |= SND_SOC_DAIFMT_CBM_CFM;
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "fsl,imx-audio-ac97")) अणु
		codec_dai_name = "ac97-hifi";
		priv->dai_fmt = SND_SOC_DAIFMT_AC97;
		priv->card.dapm_routes = audio_map_ac97;
		priv->card.num_dapm_routes = ARRAY_SIZE(audio_map_ac97);
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "fsl,imx-audio-mqs")) अणु
		codec_dai_name = "fsl-mqs-dai";
		priv->dai_fmt = SND_SOC_DAIFMT_LEFT_J |
				SND_SOC_DAIFMT_CBS_CFS |
				SND_SOC_DAIFMT_NB_NF;
		priv->dai_link[1].dpcm_capture = 0;
		priv->dai_link[2].dpcm_capture = 0;
		priv->card.dapm_routes = audio_map_tx;
		priv->card.num_dapm_routes = ARRAY_SIZE(audio_map_tx);
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "fsl,imx-audio-wm8524")) अणु
		codec_dai_name = "wm8524-hifi";
		priv->dai_fmt |= SND_SOC_DAIFMT_CBS_CFS;
		priv->dai_link[1].dpcm_capture = 0;
		priv->dai_link[2].dpcm_capture = 0;
		priv->cpu_priv.slot_width = 32;
		priv->card.dapm_routes = audio_map_tx;
		priv->card.num_dapm_routes = ARRAY_SIZE(audio_map_tx);
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "fsl,imx-audio-si476x")) अणु
		codec_dai_name = "si476x-codec";
		priv->dai_fmt |= SND_SOC_DAIFMT_CBS_CFS;
		priv->card.dapm_routes = audio_map_rx;
		priv->card.num_dapm_routes = ARRAY_SIZE(audio_map_rx);
	पूर्ण अन्यथा अगर (of_device_is_compatible(np, "fsl,imx-audio-wm8958")) अणु
		codec_dai_name = "wm8994-aif1";
		priv->dai_fmt |= SND_SOC_DAIFMT_CBM_CFM;
		priv->codec_priv.mclk_id = WM8994_FLL_SRC_MCLK1;
		priv->codec_priv.fll_id = WM8994_SYSCLK_FLL1;
		priv->codec_priv.pll_id = WM8994_FLL1;
		priv->codec_priv.मुक्त_freq = priv->codec_priv.mclk_freq;
		priv->card.dapm_routes = शून्य;
		priv->card.num_dapm_routes = 0;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev, "unknown Device Tree compatible\n");
		ret = -EINVAL;
		जाओ asrc_fail;
	पूर्ण

	/* Format info from DT is optional. */
	daअगरmt = snd_soc_of_parse_daअगरmt(np, शून्य,
					 &bitclkmaster, &framemaster);
	daअगरmt &= ~SND_SOC_DAIFMT_MASTER_MASK;
	अगर (bitclkmaster || framemaster) अणु
		अगर (codec_np == bitclkmaster)
			daअगरmt |= (codec_np == framemaster) ?
				SND_SOC_DAIFMT_CBM_CFM : SND_SOC_DAIFMT_CBM_CFS;
		अन्यथा
			daअगरmt |= (codec_np == framemaster) ?
				SND_SOC_DAIFMT_CBS_CFM : SND_SOC_DAIFMT_CBS_CFS;

		/* Override dai_fmt with value from DT */
		priv->dai_fmt = daअगरmt;
	पूर्ण

	/* Change direction according to क्रमmat */
	अगर (priv->dai_fmt & SND_SOC_DAIFMT_CBM_CFM) अणु
		priv->cpu_priv.sysclk_dir[TX] = SND_SOC_CLOCK_IN;
		priv->cpu_priv.sysclk_dir[RX] = SND_SOC_CLOCK_IN;
	पूर्ण

	of_node_put(bitclkmaster);
	of_node_put(framemaster);

	अगर (!fsl_asoc_card_is_ac97(priv) && !codec_dev) अणु
		dev_err(&pdev->dev, "failed to find codec device\n");
		ret = -EPROBE_DEFER;
		जाओ asrc_fail;
	पूर्ण

	/* Common settings क्रम corresponding Freescale CPU DAI driver */
	अगर (of_node_name_eq(cpu_np, "ssi")) अणु
		/* Only SSI needs to configure AUDMUX */
		ret = fsl_asoc_card_audmux_init(np, priv);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to init audmux\n");
			जाओ asrc_fail;
		पूर्ण
	पूर्ण अन्यथा अगर (of_node_name_eq(cpu_np, "esai")) अणु
		काष्ठा clk *esai_clk = clk_get(&cpu_pdev->dev, "extal");

		अगर (!IS_ERR(esai_clk)) अणु
			priv->cpu_priv.sysclk_freq[TX] = clk_get_rate(esai_clk);
			priv->cpu_priv.sysclk_freq[RX] = clk_get_rate(esai_clk);
			clk_put(esai_clk);
		पूर्ण अन्यथा अगर (PTR_ERR(esai_clk) == -EPROBE_DEFER) अणु
			ret = -EPROBE_DEFER;
			जाओ asrc_fail;
		पूर्ण

		priv->cpu_priv.sysclk_id[1] = ESAI_HCKT_EXTAL;
		priv->cpu_priv.sysclk_id[0] = ESAI_HCKR_EXTAL;
	पूर्ण अन्यथा अगर (of_node_name_eq(cpu_np, "sai")) अणु
		priv->cpu_priv.sysclk_id[1] = FSL_SAI_CLK_MAST1;
		priv->cpu_priv.sysclk_id[0] = FSL_SAI_CLK_MAST1;
	पूर्ण

	/* Initialize sound card */
	priv->pdev = pdev;
	priv->card.dev = &pdev->dev;
	priv->card.owner = THIS_MODULE;
	ret = snd_soc_of_parse_card_name(&priv->card, "model");
	अगर (ret) अणु
		snम_लिखो(priv->name, माप(priv->name), "%s-audio",
			 fsl_asoc_card_is_ac97(priv) ? "ac97" : codec_dev_name);
		priv->card.name = priv->name;
	पूर्ण
	priv->card.dai_link = priv->dai_link;
	priv->card.late_probe = fsl_asoc_card_late_probe;
	priv->card.dapm_widमाला_लो = fsl_asoc_card_dapm_widमाला_लो;
	priv->card.num_dapm_widमाला_लो = ARRAY_SIZE(fsl_asoc_card_dapm_widमाला_लो);

	/* Drop the second half of DAPM routes -- ASRC */
	अगर (!asrc_pdev)
		priv->card.num_dapm_routes /= 2;

	अगर (of_property_पढ़ो_bool(np, "audio-routing")) अणु
		ret = snd_soc_of_parse_audio_routing(&priv->card, "audio-routing");
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to parse audio-routing: %d\n", ret);
			जाओ asrc_fail;
		पूर्ण
	पूर्ण

	/* Normal DAI Link */
	priv->dai_link[0].cpus->of_node = cpu_np;
	priv->dai_link[0].codecs->dai_name = codec_dai_name;

	अगर (!fsl_asoc_card_is_ac97(priv))
		priv->dai_link[0].codecs->of_node = codec_np;
	अन्यथा अणु
		u32 idx;

		ret = of_property_पढ़ो_u32(cpu_np, "cell-index", &idx);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"cannot get CPU index property\n");
			जाओ asrc_fail;
		पूर्ण

		priv->dai_link[0].codecs->name =
				devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL,
					       "ac97-codec.%u",
					       (अचिन्हित पूर्णांक)idx);
		अगर (!priv->dai_link[0].codecs->name) अणु
			ret = -ENOMEM;
			जाओ asrc_fail;
		पूर्ण
	पूर्ण

	priv->dai_link[0].platक्रमms->of_node = cpu_np;
	priv->dai_link[0].dai_fmt = priv->dai_fmt;
	priv->card.num_links = 1;

	अगर (asrc_pdev) अणु
		/* DPCM DAI Links only अगर ASRC exsits */
		priv->dai_link[1].cpus->of_node = asrc_np;
		priv->dai_link[1].platक्रमms->of_node = asrc_np;
		priv->dai_link[2].codecs->dai_name = codec_dai_name;
		priv->dai_link[2].codecs->of_node = codec_np;
		priv->dai_link[2].codecs->name =
				priv->dai_link[0].codecs->name;
		priv->dai_link[2].cpus->of_node = cpu_np;
		priv->dai_link[2].dai_fmt = priv->dai_fmt;
		priv->card.num_links = 3;

		ret = of_property_पढ़ो_u32(asrc_np, "fsl,asrc-rate",
					   &priv->asrc_rate);
		अगर (ret) अणु
			dev_err(&pdev->dev, "failed to get output rate\n");
			ret = -EINVAL;
			जाओ asrc_fail;
		पूर्ण

		ret = of_property_पढ़ो_u32(asrc_np, "fsl,asrc-format",
					   &priv->asrc_क्रमmat);
		अगर (ret) अणु
			/* Fallback to old binding; translate to asrc_क्रमmat */
			ret = of_property_पढ़ो_u32(asrc_np, "fsl,asrc-width",
						   &width);
			अगर (ret) अणु
				dev_err(&pdev->dev,
					"failed to decide output format\n");
				जाओ asrc_fail;
			पूर्ण

			अगर (width == 24)
				priv->asrc_क्रमmat = SNDRV_PCM_FORMAT_S24_LE;
			अन्यथा
				priv->asrc_क्रमmat = SNDRV_PCM_FORMAT_S16_LE;
		पूर्ण
	पूर्ण

	/* Finish card रेजिस्टरing */
	platक्रमm_set_drvdata(pdev, priv);
	snd_soc_card_set_drvdata(&priv->card, priv);

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, &priv->card);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n", ret);
		जाओ asrc_fail;
	पूर्ण

	/*
	 * Properties "hp-det-gpio" and "mic-det-gpio" are optional, and
	 * asoc_simple_init_jack uses these properties क्रम creating
	 * Headphone Jack and Microphone Jack.
	 *
	 * The notअगरier is initialized in snd_soc_card_jack_new(), then
	 * snd_soc_jack_notअगरier_रेजिस्टर can be called.
	 */
	अगर (of_property_पढ़ो_bool(np, "hp-det-gpio")) अणु
		ret = asoc_simple_init_jack(&priv->card, &priv->hp_jack,
					    1, शून्य, "Headphone Jack");
		अगर (ret)
			जाओ asrc_fail;

		snd_soc_jack_notअगरier_रेजिस्टर(&priv->hp_jack.jack, &hp_jack_nb);
	पूर्ण

	अगर (of_property_पढ़ो_bool(np, "mic-det-gpio")) अणु
		ret = asoc_simple_init_jack(&priv->card, &priv->mic_jack,
					    0, शून्य, "Mic Jack");
		अगर (ret)
			जाओ asrc_fail;

		snd_soc_jack_notअगरier_रेजिस्टर(&priv->mic_jack.jack, &mic_jack_nb);
	पूर्ण

asrc_fail:
	of_node_put(asrc_np);
	of_node_put(codec_np);
	put_device(&cpu_pdev->dev);
fail:
	of_node_put(cpu_np);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id fsl_asoc_card_dt_ids[] = अणु
	अणु .compatible = "fsl,imx-audio-ac97", पूर्ण,
	अणु .compatible = "fsl,imx-audio-cs42888", पूर्ण,
	अणु .compatible = "fsl,imx-audio-cs427x", पूर्ण,
	अणु .compatible = "fsl,imx-audio-tlv320aic32x4", पूर्ण,
	अणु .compatible = "fsl,imx-audio-sgtl5000", पूर्ण,
	अणु .compatible = "fsl,imx-audio-wm8962", पूर्ण,
	अणु .compatible = "fsl,imx-audio-wm8960", पूर्ण,
	अणु .compatible = "fsl,imx-audio-mqs", पूर्ण,
	अणु .compatible = "fsl,imx-audio-wm8524", पूर्ण,
	अणु .compatible = "fsl,imx-audio-si476x", पूर्ण,
	अणु .compatible = "fsl,imx-audio-wm8958", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_asoc_card_dt_ids);

अटल काष्ठा platक्रमm_driver fsl_asoc_card_driver = अणु
	.probe = fsl_asoc_card_probe,
	.driver = अणु
		.name = "fsl-asoc-card",
		.pm = &snd_soc_pm_ops,
		.of_match_table = fsl_asoc_card_dt_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(fsl_asoc_card_driver);

MODULE_DESCRIPTION("Freescale Generic ASoC Sound Card driver with ASRC");
MODULE_AUTHOR("Nicolin Chen <nicoleotsuka@gmail.com>");
MODULE_ALIAS("platform:fsl-asoc-card");
MODULE_LICENSE("GPL");
