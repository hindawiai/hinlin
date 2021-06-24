<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * This driver supports the digital controls क्रम the पूर्णांकernal codec
 * found in Allwinner's A33 SoCs.
 *
 * (C) Copyright 2010-2016
 * Reuuimlla Technology Co., Ltd. <www.reuuimllatech.com>
 * huangxin <huangxin@Reuuimllatech.com>
 * Mylथउne Josseअक्रम <mylene.josseअक्रम@मुक्त-electrons.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/log2.h>

#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>

#घोषणा SUN8I_SYSCLK_CTL				0x00c
#घोषणा SUN8I_SYSCLK_CTL_AIF1CLK_ENA			11
#घोषणा SUN8I_SYSCLK_CTL_AIF1CLK_SRC_PLL		(0x2 << 8)
#घोषणा SUN8I_SYSCLK_CTL_AIF2CLK_ENA			7
#घोषणा SUN8I_SYSCLK_CTL_AIF2CLK_SRC_PLL		(0x2 << 4)
#घोषणा SUN8I_SYSCLK_CTL_SYSCLK_ENA			3
#घोषणा SUN8I_SYSCLK_CTL_SYSCLK_SRC			0
#घोषणा SUN8I_SYSCLK_CTL_SYSCLK_SRC_AIF1CLK		(0x0 << 0)
#घोषणा SUN8I_SYSCLK_CTL_SYSCLK_SRC_AIF2CLK		(0x1 << 0)
#घोषणा SUN8I_MOD_CLK_ENA				0x010
#घोषणा SUN8I_MOD_CLK_ENA_AIF1				15
#घोषणा SUN8I_MOD_CLK_ENA_AIF2				14
#घोषणा SUN8I_MOD_CLK_ENA_AIF3				13
#घोषणा SUN8I_MOD_CLK_ENA_ADC				3
#घोषणा SUN8I_MOD_CLK_ENA_DAC				2
#घोषणा SUN8I_MOD_RST_CTL				0x014
#घोषणा SUN8I_MOD_RST_CTL_AIF1				15
#घोषणा SUN8I_MOD_RST_CTL_AIF2				14
#घोषणा SUN8I_MOD_RST_CTL_AIF3				13
#घोषणा SUN8I_MOD_RST_CTL_ADC				3
#घोषणा SUN8I_MOD_RST_CTL_DAC				2
#घोषणा SUN8I_SYS_SR_CTRL				0x018
#घोषणा SUN8I_SYS_SR_CTRL_AIF1_FS			12
#घोषणा SUN8I_SYS_SR_CTRL_AIF2_FS			8
#घोषणा SUN8I_AIF_CLK_CTRL(n)				(0x040 * (1 + (n)))
#घोषणा SUN8I_AIF_CLK_CTRL_MSTR_MOD			15
#घोषणा SUN8I_AIF_CLK_CTRL_CLK_INV			13
#घोषणा SUN8I_AIF_CLK_CTRL_BCLK_DIV			9
#घोषणा SUN8I_AIF_CLK_CTRL_LRCK_DIV			6
#घोषणा SUN8I_AIF_CLK_CTRL_WORD_SIZ			4
#घोषणा SUN8I_AIF_CLK_CTRL_DATA_FMT			2
#घोषणा SUN8I_AIF1_ADCDAT_CTRL				0x044
#घोषणा SUN8I_AIF1_ADCDAT_CTRL_AIF1_AD0L_ENA		15
#घोषणा SUN8I_AIF1_ADCDAT_CTRL_AIF1_AD0R_ENA		14
#घोषणा SUN8I_AIF1_ADCDAT_CTRL_AIF1_AD0L_SRC		10
#घोषणा SUN8I_AIF1_ADCDAT_CTRL_AIF1_AD0R_SRC		8
#घोषणा SUN8I_AIF1_DACDAT_CTRL				0x048
#घोषणा SUN8I_AIF1_DACDAT_CTRL_AIF1_DA0L_ENA		15
#घोषणा SUN8I_AIF1_DACDAT_CTRL_AIF1_DA0R_ENA		14
#घोषणा SUN8I_AIF1_DACDAT_CTRL_AIF1_DA0L_SRC		10
#घोषणा SUN8I_AIF1_DACDAT_CTRL_AIF1_DA0R_SRC		8
#घोषणा SUN8I_AIF1_MXR_SRC				0x04c
#घोषणा SUN8I_AIF1_MXR_SRC_AD0L_MXR_SRC_AIF1DA0L	15
#घोषणा SUN8I_AIF1_MXR_SRC_AD0L_MXR_SRC_AIF2DACL	14
#घोषणा SUN8I_AIF1_MXR_SRC_AD0L_MXR_SRC_ADCL		13
#घोषणा SUN8I_AIF1_MXR_SRC_AD0L_MXR_SRC_AIF2DACR	12
#घोषणा SUN8I_AIF1_MXR_SRC_AD0R_MXR_SRC_AIF1DA0R	11
#घोषणा SUN8I_AIF1_MXR_SRC_AD0R_MXR_SRC_AIF2DACR	10
#घोषणा SUN8I_AIF1_MXR_SRC_AD0R_MXR_SRC_ADCR		9
#घोषणा SUN8I_AIF1_MXR_SRC_AD0R_MXR_SRC_AIF2DACL	8
#घोषणा SUN8I_AIF2_ADCDAT_CTRL				0x084
#घोषणा SUN8I_AIF2_ADCDAT_CTRL_AIF2_ADCL_ENA		15
#घोषणा SUN8I_AIF2_ADCDAT_CTRL_AIF2_ADCR_ENA		14
#घोषणा SUN8I_AIF2_ADCDAT_CTRL_AIF2_ADCL_SRC		10
#घोषणा SUN8I_AIF2_ADCDAT_CTRL_AIF2_ADCR_SRC		8
#घोषणा SUN8I_AIF2_DACDAT_CTRL				0x088
#घोषणा SUN8I_AIF2_DACDAT_CTRL_AIF2_DACL_ENA		15
#घोषणा SUN8I_AIF2_DACDAT_CTRL_AIF2_DACR_ENA		14
#घोषणा SUN8I_AIF2_DACDAT_CTRL_AIF2_DACL_SRC		10
#घोषणा SUN8I_AIF2_DACDAT_CTRL_AIF2_DACR_SRC		8
#घोषणा SUN8I_AIF2_MXR_SRC				0x08c
#घोषणा SUN8I_AIF2_MXR_SRC_ADCL_MXR_SRC_AIF1DA0L	15
#घोषणा SUN8I_AIF2_MXR_SRC_ADCL_MXR_SRC_AIF1DA1L	14
#घोषणा SUN8I_AIF2_MXR_SRC_ADCL_MXR_SRC_AIF2DACR	13
#घोषणा SUN8I_AIF2_MXR_SRC_ADCL_MXR_SRC_ADCL		12
#घोषणा SUN8I_AIF2_MXR_SRC_ADCR_MXR_SRC_AIF1DA0R	11
#घोषणा SUN8I_AIF2_MXR_SRC_ADCR_MXR_SRC_AIF1DA1R	10
#घोषणा SUN8I_AIF2_MXR_SRC_ADCR_MXR_SRC_AIF2DACL	9
#घोषणा SUN8I_AIF2_MXR_SRC_ADCR_MXR_SRC_ADCR		8
#घोषणा SUN8I_AIF3_CLK_CTRL_AIF3_CLK_SRC_AIF1		(0x0 << 0)
#घोषणा SUN8I_AIF3_CLK_CTRL_AIF3_CLK_SRC_AIF2		(0x1 << 0)
#घोषणा SUN8I_AIF3_CLK_CTRL_AIF3_CLK_SRC_AIF1CLK	(0x2 << 0)
#घोषणा SUN8I_AIF3_PATH_CTRL				0x0cc
#घोषणा SUN8I_AIF3_PATH_CTRL_AIF3_ADC_SRC		10
#घोषणा SUN8I_AIF3_PATH_CTRL_AIF2_DAC_SRC		8
#घोषणा SUN8I_AIF3_PATH_CTRL_AIF3_PINS_TRI		7
#घोषणा SUN8I_ADC_DIG_CTRL				0x100
#घोषणा SUN8I_ADC_DIG_CTRL_ENAD				15
#घोषणा SUN8I_ADC_DIG_CTRL_ADOUT_DTS			2
#घोषणा SUN8I_ADC_DIG_CTRL_ADOUT_DLY			1
#घोषणा SUN8I_DAC_DIG_CTRL				0x120
#घोषणा SUN8I_DAC_DIG_CTRL_ENDA				15
#घोषणा SUN8I_DAC_MXR_SRC				0x130
#घोषणा SUN8I_DAC_MXR_SRC_DACL_MXR_SRC_AIF1DA0L		15
#घोषणा SUN8I_DAC_MXR_SRC_DACL_MXR_SRC_AIF1DA1L		14
#घोषणा SUN8I_DAC_MXR_SRC_DACL_MXR_SRC_AIF2DACL		13
#घोषणा SUN8I_DAC_MXR_SRC_DACL_MXR_SRC_ADCL		12
#घोषणा SUN8I_DAC_MXR_SRC_DACR_MXR_SRC_AIF1DA0R		11
#घोषणा SUN8I_DAC_MXR_SRC_DACR_MXR_SRC_AIF1DA1R		10
#घोषणा SUN8I_DAC_MXR_SRC_DACR_MXR_SRC_AIF2DACR		9
#घोषणा SUN8I_DAC_MXR_SRC_DACR_MXR_SRC_ADCR		8

#घोषणा SUN8I_SYSCLK_CTL_AIF1CLK_SRC_MASK	GENMASK(9, 8)
#घोषणा SUN8I_SYSCLK_CTL_AIF2CLK_SRC_MASK	GENMASK(5, 4)
#घोषणा SUN8I_SYS_SR_CTRL_AIF1_FS_MASK		GENMASK(15, 12)
#घोषणा SUN8I_SYS_SR_CTRL_AIF2_FS_MASK		GENMASK(11, 8)
#घोषणा SUN8I_AIF_CLK_CTRL_CLK_INV_MASK		GENMASK(14, 13)
#घोषणा SUN8I_AIF_CLK_CTRL_BCLK_DIV_MASK	GENMASK(12, 9)
#घोषणा SUN8I_AIF_CLK_CTRL_LRCK_DIV_MASK	GENMASK(8, 6)
#घोषणा SUN8I_AIF_CLK_CTRL_WORD_SIZ_MASK	GENMASK(5, 4)
#घोषणा SUN8I_AIF_CLK_CTRL_DATA_FMT_MASK	GENMASK(3, 2)
#घोषणा SUN8I_AIF3_CLK_CTRL_AIF3_CLK_SRC_MASK	GENMASK(1, 0)

#घोषणा SUN8I_CODEC_PASSTHROUGH_SAMPLE_RATE 48000

#घोषणा SUN8I_CODEC_PCM_FORMATS	(SNDRV_PCM_FMTBIT_S8     |\
				 SNDRV_PCM_FMTBIT_S16_LE |\
				 SNDRV_PCM_FMTBIT_S20_LE |\
				 SNDRV_PCM_FMTBIT_S24_LE |\
				 SNDRV_PCM_FMTBIT_S20_3LE|\
				 SNDRV_PCM_FMTBIT_S24_3LE)

#घोषणा SUN8I_CODEC_PCM_RATES	(SNDRV_PCM_RATE_8000_48000|\
				 SNDRV_PCM_RATE_88200     |\
				 SNDRV_PCM_RATE_96000     |\
				 SNDRV_PCM_RATE_176400    |\
				 SNDRV_PCM_RATE_192000    |\
				 SNDRV_PCM_RATE_KNOT)

क्रमागत अणु
	SUN8I_CODEC_AIF1,
	SUN8I_CODEC_AIF2,
	SUN8I_CODEC_AIF3,
	SUN8I_CODEC_NAIFS
पूर्ण;

काष्ठा sun8i_codec_aअगर अणु
	अचिन्हित पूर्णांक	lrck_भाग_order;
	अचिन्हित पूर्णांक	sample_rate;
	अचिन्हित पूर्णांक	slots;
	अचिन्हित पूर्णांक	slot_width;
	अचिन्हित पूर्णांक	active_streams	: 2;
	अचिन्हित पूर्णांक	खोलो_streams	: 2;
पूर्ण;

काष्ठा sun8i_codec_quirks अणु
	bool legacy_widमाला_लो	: 1;
	bool lrck_inversion	: 1;
पूर्ण;

काष्ठा sun8i_codec अणु
	काष्ठा regmap			*regmap;
	काष्ठा clk			*clk_module;
	स्थिर काष्ठा sun8i_codec_quirks	*quirks;
	काष्ठा sun8i_codec_aअगर		aअगरs[SUN8I_CODEC_NAIFS];
	अचिन्हित पूर्णांक			sysclk_rate;
	पूर्णांक				sysclk_refcnt;
पूर्ण;

अटल काष्ठा snd_soc_dai_driver sun8i_codec_dais[];

अटल पूर्णांक sun8i_codec_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sun8i_codec *scodec = dev_get_drvdata(dev);
	पूर्णांक ret;

	regcache_cache_only(scodec->regmap, false);

	ret = regcache_sync(scodec->regmap);
	अगर (ret) अणु
		dev_err(dev, "Failed to sync regmap cache\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_codec_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sun8i_codec *scodec = dev_get_drvdata(dev);

	regcache_cache_only(scodec->regmap, true);
	regcache_mark_dirty(scodec->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_codec_get_hw_rate(अचिन्हित पूर्णांक sample_rate)
अणु
	चयन (sample_rate) अणु
	हाल 7350:
	हाल 8000:
		वापस 0x0;
	हाल 11025:
		वापस 0x1;
	हाल 12000:
		वापस 0x2;
	हाल 14700:
	हाल 16000:
		वापस 0x3;
	हाल 22050:
		वापस 0x4;
	हाल 24000:
		वापस 0x5;
	हाल 29400:
	हाल 32000:
		वापस 0x6;
	हाल 44100:
		वापस 0x7;
	हाल 48000:
		वापस 0x8;
	हाल 88200:
	हाल 96000:
		वापस 0x9;
	हाल 176400:
	हाल 192000:
		वापस 0xa;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक sun8i_codec_update_sample_rate(काष्ठा sun8i_codec *scodec)
अणु
	अचिन्हित पूर्णांक max_rate = 0;
	पूर्णांक hw_rate, i;

	क्रम (i = SUN8I_CODEC_AIF1; i < SUN8I_CODEC_NAIFS; ++i) अणु
		काष्ठा sun8i_codec_aअगर *aअगर = &scodec->aअगरs[i];

		अगर (aअगर->active_streams)
			max_rate = max(max_rate, aअगर->sample_rate);
	पूर्ण

	/* Set the sample rate क्रम ADC->DAC passthrough when no AIF is active. */
	अगर (!max_rate)
		max_rate = SUN8I_CODEC_PASSTHROUGH_SAMPLE_RATE;

	hw_rate = sun8i_codec_get_hw_rate(max_rate);
	अगर (hw_rate < 0)
		वापस hw_rate;

	regmap_update_bits(scodec->regmap, SUN8I_SYS_SR_CTRL,
			   SUN8I_SYS_SR_CTRL_AIF1_FS_MASK,
			   hw_rate << SUN8I_SYS_SR_CTRL_AIF1_FS);

	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_codec_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा sun8i_codec *scodec = snd_soc_dai_get_drvdata(dai);
	u32 dsp_क्रमmat, क्रमmat, invert, value;

	/* घड़ी masters */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS: /* Codec slave, DAI master */
		value = 0x1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM: /* Codec Master, DAI slave */
		value = 0x0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (dai->id == SUN8I_CODEC_AIF3) अणु
		/* AIF3 only supports master mode. */
		अगर (value)
			वापस -EINVAL;

		/* Use the AIF2 BCLK and LRCK क्रम AIF3. */
		regmap_update_bits(scodec->regmap, SUN8I_AIF_CLK_CTRL(dai->id),
				   SUN8I_AIF3_CLK_CTRL_AIF3_CLK_SRC_MASK,
				   SUN8I_AIF3_CLK_CTRL_AIF3_CLK_SRC_AIF2);
	पूर्ण अन्यथा अणु
		regmap_update_bits(scodec->regmap, SUN8I_AIF_CLK_CTRL(dai->id),
				   BIT(SUN8I_AIF_CLK_CTRL_MSTR_MOD),
				   value << SUN8I_AIF_CLK_CTRL_MSTR_MOD);
	पूर्ण

	/* DAI क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		क्रमmat = 0x0;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		क्रमmat = 0x1;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		क्रमmat = 0x2;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		क्रमmat = 0x3;
		dsp_क्रमmat = 0x0; /* Set LRCK_INV to 0 */
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		क्रमmat = 0x3;
		dsp_क्रमmat = 0x1; /* Set LRCK_INV to 1 */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (dai->id == SUN8I_CODEC_AIF3) अणु
		/* AIF3 only supports DSP mode. */
		अगर (क्रमmat != 3)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		regmap_update_bits(scodec->regmap, SUN8I_AIF_CLK_CTRL(dai->id),
				   SUN8I_AIF_CLK_CTRL_DATA_FMT_MASK,
				   क्रमmat << SUN8I_AIF_CLK_CTRL_DATA_FMT);
	पूर्ण

	/* घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF: /* Normal */
		invert = 0x0;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF: /* Inverted LRCK */
		invert = 0x1;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF: /* Inverted BCLK */
		invert = 0x2;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF: /* Both inverted */
		invert = 0x3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (क्रमmat == 0x3) अणु
		/* Inverted LRCK is not available in DSP mode. */
		अगर (invert & BIT(0))
			वापस -EINVAL;

		/* Instead, the bit selects between DSP A/B क्रमmats. */
		invert |= dsp_क्रमmat;
	पूर्ण अन्यथा अणु
		/*
		 * It appears that the DAI and the codec in the A33 SoC करोn't
		 * share the same polarity क्रम the LRCK संकेत when they mean
		 * 'normal' and 'inverted' in the datasheet.
		 *
		 * Since the DAI here is our regular i2s driver that have been
		 * tested with way more codecs than just this one, it means
		 * that the codec probably माला_लो it backward, and we have to
		 * invert the value here.
		 */
		invert ^= scodec->quirks->lrck_inversion;
	पूर्ण

	regmap_update_bits(scodec->regmap, SUN8I_AIF_CLK_CTRL(dai->id),
			   SUN8I_AIF_CLK_CTRL_CLK_INV_MASK,
			   invert << SUN8I_AIF_CLK_CTRL_CLK_INV);

	वापस 0;
पूर्ण

अटल पूर्णांक sun8i_codec_set_tdm_slot(काष्ठा snd_soc_dai *dai,
				    अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
				    पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा sun8i_codec *scodec = snd_soc_dai_get_drvdata(dai);
	काष्ठा sun8i_codec_aअगर *aअगर = &scodec->aअगरs[dai->id];

	अगर (slot_width && !is_घातer_of_2(slot_width))
		वापस -EINVAL;

	aअगर->slots = slots;
	aअगर->slot_width = slot_width;

	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक sun8i_codec_rates[] = अणु
	  7350,   8000,  11025,  12000,  14700,  16000,  22050,  24000,
	 29400,  32000,  44100,  48000,  88200,  96000, 176400, 192000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list sun8i_codec_all_rates = अणु
	.list	= sun8i_codec_rates,
	.count	= ARRAY_SIZE(sun8i_codec_rates),
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list sun8i_codec_22M_rates = अणु
	.list	= sun8i_codec_rates,
	.count	= ARRAY_SIZE(sun8i_codec_rates),
	.mask	= 0x5555,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list sun8i_codec_24M_rates = अणु
	.list	= sun8i_codec_rates,
	.count	= ARRAY_SIZE(sun8i_codec_rates),
	.mask	= 0xaaaa,
पूर्ण;

अटल पूर्णांक sun8i_codec_startup(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sun8i_codec *scodec = snd_soc_dai_get_drvdata(dai);
	स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list *list;

	/* hw_स्थिरraपूर्णांकs is not relevant क्रम codec2codec DAIs. */
	अगर (dai->id != SUN8I_CODEC_AIF1)
		वापस 0;

	अगर (!scodec->sysclk_refcnt)
		list = &sun8i_codec_all_rates;
	अन्यथा अगर (scodec->sysclk_rate == 22579200)
		list = &sun8i_codec_22M_rates;
	अन्यथा अगर (scodec->sysclk_rate == 24576000)
		list = &sun8i_codec_24M_rates;
	अन्यथा
		वापस -EINVAL;

	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
					  SNDRV_PCM_HW_PARAM_RATE, list);
पूर्ण

काष्ठा sun8i_codec_clk_भाग अणु
	u8	भाग;
	u8	val;
पूर्ण;

अटल स्थिर काष्ठा sun8i_codec_clk_भाग sun8i_codec_bclk_भाग[] = अणु
	अणु .भाग = 1,	.val = 0 पूर्ण,
	अणु .भाग = 2,	.val = 1 पूर्ण,
	अणु .भाग = 4,	.val = 2 पूर्ण,
	अणु .भाग = 6,	.val = 3 पूर्ण,
	अणु .भाग = 8,	.val = 4 पूर्ण,
	अणु .भाग = 12,	.val = 5 पूर्ण,
	अणु .भाग = 16,	.val = 6 पूर्ण,
	अणु .भाग = 24,	.val = 7 पूर्ण,
	अणु .भाग = 32,	.val = 8 पूर्ण,
	अणु .भाग = 48,	.val = 9 पूर्ण,
	अणु .भाग = 64,	.val = 10 पूर्ण,
	अणु .भाग = 96,	.val = 11 पूर्ण,
	अणु .भाग = 128,	.val = 12 पूर्ण,
	अणु .भाग = 192,	.val = 13 पूर्ण,
पूर्ण;

अटल पूर्णांक sun8i_codec_get_bclk_भाग(अचिन्हित पूर्णांक sysclk_rate,
				    अचिन्हित पूर्णांक lrck_भाग_order,
				    अचिन्हित पूर्णांक sample_rate)
अणु
	अचिन्हित पूर्णांक भाग = sysclk_rate / sample_rate >> lrck_भाग_order;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sun8i_codec_bclk_भाग); i++) अणु
		स्थिर काष्ठा sun8i_codec_clk_भाग *bभाग = &sun8i_codec_bclk_भाग[i];

		अगर (bभाग->भाग == भाग)
			वापस bभाग->val;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sun8i_codec_get_lrck_भाग_order(अचिन्हित पूर्णांक slots,
					  अचिन्हित पूर्णांक slot_width)
अणु
	अचिन्हित पूर्णांक भाग = slots * slot_width;

	अगर (भाग < 16 || भाग > 256)
		वापस -EINVAL;

	वापस order_base_2(भाग);
पूर्ण

अटल अचिन्हित पूर्णांक sun8i_codec_get_sysclk_rate(अचिन्हित पूर्णांक sample_rate)
अणु
	वापस (sample_rate % 4000) ? 22579200 : 24576000;
पूर्ण

अटल पूर्णांक sun8i_codec_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sun8i_codec *scodec = snd_soc_dai_get_drvdata(dai);
	काष्ठा sun8i_codec_aअगर *aअगर = &scodec->aअगरs[dai->id];
	अचिन्हित पूर्णांक sample_rate = params_rate(params);
	अचिन्हित पूर्णांक slots = aअगर->slots ?: params_channels(params);
	अचिन्हित पूर्णांक slot_width = aअगर->slot_width ?: params_width(params);
	अचिन्हित पूर्णांक sysclk_rate = sun8i_codec_get_sysclk_rate(sample_rate);
	पूर्णांक bclk_भाग, lrck_भाग_order, ret, word_size;
	u32 clk_reg;

	/* word size */
	चयन (params_width(params)) अणु
	हाल 8:
		word_size = 0x0;
		अवरोध;
	हाल 16:
		word_size = 0x1;
		अवरोध;
	हाल 20:
		word_size = 0x2;
		अवरोध;
	हाल 24:
		word_size = 0x3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(scodec->regmap, SUN8I_AIF_CLK_CTRL(dai->id),
			   SUN8I_AIF_CLK_CTRL_WORD_SIZ_MASK,
			   word_size << SUN8I_AIF_CLK_CTRL_WORD_SIZ);

	/* LRCK भागider (BCLK/LRCK ratio) */
	lrck_भाग_order = sun8i_codec_get_lrck_भाग_order(slots, slot_width);
	अगर (lrck_भाग_order < 0)
		वापस lrck_भाग_order;

	अगर (dai->id == SUN8I_CODEC_AIF2 || dai->id == SUN8I_CODEC_AIF3) अणु
		/* AIF2 and AIF3 share AIF2's BCLK and LRCK generation circuitry. */
		पूर्णांक partner = (SUN8I_CODEC_AIF2 + SUN8I_CODEC_AIF3) - dai->id;
		स्थिर काष्ठा sun8i_codec_aअगर *partner_aअगर = &scodec->aअगरs[partner];
		स्थिर अक्षर *partner_name = sun8i_codec_dais[partner].name;

		अगर (partner_aअगर->खोलो_streams &&
		    (lrck_भाग_order != partner_aअगर->lrck_भाग_order ||
		     sample_rate != partner_aअगर->sample_rate)) अणु
			dev_err(dai->dev,
				"%s sample and bit rates must match %s when both are used\n",
				dai->name, partner_name);
			वापस -EBUSY;
		पूर्ण

		clk_reg = SUN8I_AIF_CLK_CTRL(SUN8I_CODEC_AIF2);
	पूर्ण अन्यथा अणु
		clk_reg = SUN8I_AIF_CLK_CTRL(dai->id);
	पूर्ण

	regmap_update_bits(scodec->regmap, clk_reg,
			   SUN8I_AIF_CLK_CTRL_LRCK_DIV_MASK,
			   (lrck_भाग_order - 4) << SUN8I_AIF_CLK_CTRL_LRCK_DIV);

	/* BCLK भागider (SYSCLK/BCLK ratio) */
	bclk_भाग = sun8i_codec_get_bclk_भाग(sysclk_rate, lrck_भाग_order, sample_rate);
	अगर (bclk_भाग < 0)
		वापस bclk_भाग;

	regmap_update_bits(scodec->regmap, clk_reg,
			   SUN8I_AIF_CLK_CTRL_BCLK_DIV_MASK,
			   bclk_भाग << SUN8I_AIF_CLK_CTRL_BCLK_DIV);

	/*
	 * SYSCLK rate
	 *
	 * Clock rate protection is reference counted; but hw_params may be
	 * called many बार per substream, without matching calls to hw_मुक्त.
	 * Protect the घड़ी rate once per AIF, on the first hw_params call
	 * क्रम the first substream. clk_set_rate() will allow घड़ी rate
	 * changes on subsequent calls अगर only one AIF has खोलो streams.
	 */
	ret = (aअगर->खोलो_streams ? clk_set_rate : clk_set_rate_exclusive)(scodec->clk_module,
									  sysclk_rate);
	अगर (ret == -EBUSY)
		dev_err(dai->dev,
			"%s sample rate (%u Hz) conflicts with other audio streams\n",
			dai->name, sample_rate);
	अगर (ret < 0)
		वापस ret;

	अगर (!aअगर->खोलो_streams)
		scodec->sysclk_refcnt++;
	scodec->sysclk_rate = sysclk_rate;

	aअगर->lrck_भाग_order = lrck_भाग_order;
	aअगर->sample_rate = sample_rate;
	aअगर->खोलो_streams |= BIT(substream->stream);

	वापस sun8i_codec_update_sample_rate(scodec);
पूर्ण

अटल पूर्णांक sun8i_codec_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा sun8i_codec *scodec = snd_soc_dai_get_drvdata(dai);
	काष्ठा sun8i_codec_aअगर *aअगर = &scodec->aअगरs[dai->id];

	/* Drop references when the last substream क्रम the AIF is मुक्तd. */
	अगर (aअगर->खोलो_streams != BIT(substream->stream))
		जाओ करोne;

	clk_rate_exclusive_put(scodec->clk_module);
	scodec->sysclk_refcnt--;
	aअगर->lrck_भाग_order = 0;
	aअगर->sample_rate = 0;

करोne:
	aअगर->खोलो_streams &= ~BIT(substream->stream);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops sun8i_codec_dai_ops = अणु
	.set_fmt	= sun8i_codec_set_fmt,
	.set_tdm_slot	= sun8i_codec_set_tdm_slot,
	.startup	= sun8i_codec_startup,
	.hw_params	= sun8i_codec_hw_params,
	.hw_मुक्त	= sun8i_codec_hw_मुक्त,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver sun8i_codec_dais[] = अणु
	अणु
		.name	= "sun8i-codec-aif1",
		.id	= SUN8I_CODEC_AIF1,
		.ops	= &sun8i_codec_dai_ops,
		/* capture capabilities */
		.capture = अणु
			.stream_name	= "AIF1 Capture",
			.channels_min	= 1,
			.channels_max	= 2,
			.rates		= SUN8I_CODEC_PCM_RATES,
			.क्रमmats	= SUN8I_CODEC_PCM_FORMATS,
			.sig_bits	= 24,
		पूर्ण,
		/* playback capabilities */
		.playback = अणु
			.stream_name	= "AIF1 Playback",
			.channels_min	= 1,
			.channels_max	= 2,
			.rates		= SUN8I_CODEC_PCM_RATES,
			.क्रमmats	= SUN8I_CODEC_PCM_FORMATS,
		पूर्ण,
		.symmetric_rate		= true,
		.symmetric_channels	= true,
		.symmetric_sample_bits	= true,
	पूर्ण,
	अणु
		.name	= "sun8i-codec-aif2",
		.id	= SUN8I_CODEC_AIF2,
		.ops	= &sun8i_codec_dai_ops,
		/* capture capabilities */
		.capture = अणु
			.stream_name	= "AIF2 Capture",
			.channels_min	= 1,
			.channels_max	= 2,
			.rates		= SUN8I_CODEC_PCM_RATES,
			.क्रमmats	= SUN8I_CODEC_PCM_FORMATS,
			.sig_bits	= 24,
		पूर्ण,
		/* playback capabilities */
		.playback = अणु
			.stream_name	= "AIF2 Playback",
			.channels_min	= 1,
			.channels_max	= 2,
			.rates		= SUN8I_CODEC_PCM_RATES,
			.क्रमmats	= SUN8I_CODEC_PCM_FORMATS,
		पूर्ण,
		.symmetric_rate		= true,
		.symmetric_channels	= true,
		.symmetric_sample_bits	= true,
	पूर्ण,
	अणु
		.name	= "sun8i-codec-aif3",
		.id	= SUN8I_CODEC_AIF3,
		.ops	= &sun8i_codec_dai_ops,
		/* capture capabilities */
		.capture = अणु
			.stream_name	= "AIF3 Capture",
			.channels_min	= 1,
			.channels_max	= 1,
			.rates		= SUN8I_CODEC_PCM_RATES,
			.क्रमmats	= SUN8I_CODEC_PCM_FORMATS,
			.sig_bits	= 24,
		पूर्ण,
		/* playback capabilities */
		.playback = अणु
			.stream_name	= "AIF3 Playback",
			.channels_min	= 1,
			.channels_max	= 1,
			.rates		= SUN8I_CODEC_PCM_RATES,
			.क्रमmats	= SUN8I_CODEC_PCM_FORMATS,
		पूर्ण,
		.symmetric_rate		= true,
		.symmetric_channels	= true,
		.symmetric_sample_bits	= true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक sun8i_codec_aअगर_event(काष्ठा snd_soc_dapm_widget *w,
				 काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा sun8i_codec *scodec = snd_soc_component_get_drvdata(component);
	काष्ठा sun8i_codec_aअगर *aअगर = &scodec->aअगरs[w->sname[3] - '1'];
	पूर्णांक stream = w->id == snd_soc_dapm_aअगर_out;

	अगर (SND_SOC_DAPM_EVENT_ON(event))
		aअगर->active_streams |= BIT(stream);
	अन्यथा
		aअगर->active_streams &= ~BIT(stream);

	वापस sun8i_codec_update_sample_rate(scodec);
पूर्ण

अटल स्थिर अक्षर *स्थिर sun8i_aअगर_stereo_mux_क्रमागत_values[] = अणु
	"Stereo", "Reverse Stereo", "Sum Mono", "Mix Mono"
पूर्ण;

अटल SOC_ENUM_DOUBLE_DECL(sun8i_aअगर1_ad0_stereo_mux_क्रमागत,
			    SUN8I_AIF1_ADCDAT_CTRL,
			    SUN8I_AIF1_ADCDAT_CTRL_AIF1_AD0L_SRC,
			    SUN8I_AIF1_ADCDAT_CTRL_AIF1_AD0R_SRC,
			    sun8i_aअगर_stereo_mux_क्रमागत_values);

अटल स्थिर काष्ठा snd_kcontrol_new sun8i_aअगर1_ad0_stereo_mux_control =
	SOC_DAPM_ENUM("AIF1 AD0 Stereo Capture Route",
		      sun8i_aअगर1_ad0_stereo_mux_क्रमागत);

अटल SOC_ENUM_DOUBLE_DECL(sun8i_aअगर2_adc_stereo_mux_क्रमागत,
			    SUN8I_AIF2_ADCDAT_CTRL,
			    SUN8I_AIF2_ADCDAT_CTRL_AIF2_ADCL_SRC,
			    SUN8I_AIF2_ADCDAT_CTRL_AIF2_ADCR_SRC,
			    sun8i_aअगर_stereo_mux_क्रमागत_values);

अटल स्थिर काष्ठा snd_kcontrol_new sun8i_aअगर2_adc_stereo_mux_control =
	SOC_DAPM_ENUM("AIF2 ADC Stereo Capture Route",
		      sun8i_aअगर2_adc_stereo_mux_क्रमागत);

अटल स्थिर अक्षर *स्थिर sun8i_aअगर3_adc_mux_क्रमागत_values[] = अणु
	"None", "AIF2 ADCL", "AIF2 ADCR"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(sun8i_aअगर3_adc_mux_क्रमागत,
			    SUN8I_AIF3_PATH_CTRL,
			    SUN8I_AIF3_PATH_CTRL_AIF3_ADC_SRC,
			    sun8i_aअगर3_adc_mux_क्रमागत_values);

अटल स्थिर काष्ठा snd_kcontrol_new sun8i_aअगर3_adc_mux_control =
	SOC_DAPM_ENUM("AIF3 ADC Source Capture Route",
		      sun8i_aअगर3_adc_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new sun8i_aअगर1_ad0_mixer_controls[] = अणु
	SOC_DAPM_DOUBLE("AIF1 Slot 0 Digital ADC Capture Switch",
			SUN8I_AIF1_MXR_SRC,
			SUN8I_AIF1_MXR_SRC_AD0L_MXR_SRC_AIF1DA0L,
			SUN8I_AIF1_MXR_SRC_AD0R_MXR_SRC_AIF1DA0R, 1, 0),
	SOC_DAPM_DOUBLE("AIF2 Digital ADC Capture Switch",
			SUN8I_AIF1_MXR_SRC,
			SUN8I_AIF1_MXR_SRC_AD0L_MXR_SRC_AIF2DACL,
			SUN8I_AIF1_MXR_SRC_AD0R_MXR_SRC_AIF2DACR, 1, 0),
	SOC_DAPM_DOUBLE("AIF1 Data Digital ADC Capture Switch",
			SUN8I_AIF1_MXR_SRC,
			SUN8I_AIF1_MXR_SRC_AD0L_MXR_SRC_ADCL,
			SUN8I_AIF1_MXR_SRC_AD0R_MXR_SRC_ADCR, 1, 0),
	SOC_DAPM_DOUBLE("AIF2 Inv Digital ADC Capture Switch",
			SUN8I_AIF1_MXR_SRC,
			SUN8I_AIF1_MXR_SRC_AD0L_MXR_SRC_AIF2DACR,
			SUN8I_AIF1_MXR_SRC_AD0R_MXR_SRC_AIF2DACL, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new sun8i_aअगर2_adc_mixer_controls[] = अणु
	SOC_DAPM_DOUBLE("AIF2 ADC Mixer AIF1 DA0 Capture Switch",
			SUN8I_AIF2_MXR_SRC,
			SUN8I_AIF2_MXR_SRC_ADCL_MXR_SRC_AIF1DA0L,
			SUN8I_AIF2_MXR_SRC_ADCR_MXR_SRC_AIF1DA0R, 1, 0),
	SOC_DAPM_DOUBLE("AIF2 ADC Mixer AIF1 DA1 Capture Switch",
			SUN8I_AIF2_MXR_SRC,
			SUN8I_AIF2_MXR_SRC_ADCL_MXR_SRC_AIF1DA1L,
			SUN8I_AIF2_MXR_SRC_ADCR_MXR_SRC_AIF1DA1R, 1, 0),
	SOC_DAPM_DOUBLE("AIF2 ADC Mixer AIF2 DAC Rev Capture Switch",
			SUN8I_AIF2_MXR_SRC,
			SUN8I_AIF2_MXR_SRC_ADCL_MXR_SRC_AIF2DACR,
			SUN8I_AIF2_MXR_SRC_ADCR_MXR_SRC_AIF2DACL, 1, 0),
	SOC_DAPM_DOUBLE("AIF2 ADC Mixer ADC Capture Switch",
			SUN8I_AIF2_MXR_SRC,
			SUN8I_AIF2_MXR_SRC_ADCL_MXR_SRC_ADCL,
			SUN8I_AIF2_MXR_SRC_ADCR_MXR_SRC_ADCR, 1, 0),
पूर्ण;

अटल स्थिर अक्षर *स्थिर sun8i_aअगर2_dac_mux_क्रमागत_values[] = अणु
	"AIF2", "AIF3+2", "AIF2+3"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(sun8i_aअगर2_dac_mux_क्रमागत,
			    SUN8I_AIF3_PATH_CTRL,
			    SUN8I_AIF3_PATH_CTRL_AIF2_DAC_SRC,
			    sun8i_aअगर2_dac_mux_क्रमागत_values);

अटल स्थिर काष्ठा snd_kcontrol_new sun8i_aअगर2_dac_mux_control =
	SOC_DAPM_ENUM("AIF2 DAC Source Playback Route",
		      sun8i_aअगर2_dac_mux_क्रमागत);

अटल SOC_ENUM_DOUBLE_DECL(sun8i_aअगर1_da0_stereo_mux_क्रमागत,
			    SUN8I_AIF1_DACDAT_CTRL,
			    SUN8I_AIF1_DACDAT_CTRL_AIF1_DA0L_SRC,
			    SUN8I_AIF1_DACDAT_CTRL_AIF1_DA0R_SRC,
			    sun8i_aअगर_stereo_mux_क्रमागत_values);

अटल स्थिर काष्ठा snd_kcontrol_new sun8i_aअगर1_da0_stereo_mux_control =
	SOC_DAPM_ENUM("AIF1 DA0 Stereo Playback Route",
		      sun8i_aअगर1_da0_stereo_mux_क्रमागत);

अटल SOC_ENUM_DOUBLE_DECL(sun8i_aअगर2_dac_stereo_mux_क्रमागत,
			    SUN8I_AIF2_DACDAT_CTRL,
			    SUN8I_AIF2_DACDAT_CTRL_AIF2_DACL_SRC,
			    SUN8I_AIF2_DACDAT_CTRL_AIF2_DACR_SRC,
			    sun8i_aअगर_stereo_mux_क्रमागत_values);

अटल स्थिर काष्ठा snd_kcontrol_new sun8i_aअगर2_dac_stereo_mux_control =
	SOC_DAPM_ENUM("AIF2 DAC Stereo Playback Route",
		      sun8i_aअगर2_dac_stereo_mux_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new sun8i_dac_mixer_controls[] = अणु
	SOC_DAPM_DOUBLE("AIF1 Slot 0 Digital DAC Playback Switch",
			SUN8I_DAC_MXR_SRC,
			SUN8I_DAC_MXR_SRC_DACL_MXR_SRC_AIF1DA0L,
			SUN8I_DAC_MXR_SRC_DACR_MXR_SRC_AIF1DA0R, 1, 0),
	SOC_DAPM_DOUBLE("AIF1 Slot 1 Digital DAC Playback Switch",
			SUN8I_DAC_MXR_SRC,
			SUN8I_DAC_MXR_SRC_DACL_MXR_SRC_AIF1DA1L,
			SUN8I_DAC_MXR_SRC_DACR_MXR_SRC_AIF1DA1R, 1, 0),
	SOC_DAPM_DOUBLE("AIF2 Digital DAC Playback Switch", SUN8I_DAC_MXR_SRC,
			SUN8I_DAC_MXR_SRC_DACL_MXR_SRC_AIF2DACL,
			SUN8I_DAC_MXR_SRC_DACR_MXR_SRC_AIF2DACR, 1, 0),
	SOC_DAPM_DOUBLE("ADC Digital DAC Playback Switch", SUN8I_DAC_MXR_SRC,
			SUN8I_DAC_MXR_SRC_DACL_MXR_SRC_ADCL,
			SUN8I_DAC_MXR_SRC_DACR_MXR_SRC_ADCR, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget sun8i_codec_dapm_widमाला_लो[] = अणु
	/* System Clocks */
	SND_SOC_DAPM_CLOCK_SUPPLY("mod"),

	SND_SOC_DAPM_SUPPLY("AIF1CLK",
			    SUN8I_SYSCLK_CTL,
			    SUN8I_SYSCLK_CTL_AIF1CLK_ENA, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("AIF2CLK",
			    SUN8I_SYSCLK_CTL,
			    SUN8I_SYSCLK_CTL_AIF2CLK_ENA, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("SYSCLK",
			    SUN8I_SYSCLK_CTL,
			    SUN8I_SYSCLK_CTL_SYSCLK_ENA, 0, शून्य, 0),

	/* Module Clocks */
	SND_SOC_DAPM_SUPPLY("CLK AIF1",
			    SUN8I_MOD_CLK_ENA,
			    SUN8I_MOD_CLK_ENA_AIF1, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CLK AIF2",
			    SUN8I_MOD_CLK_ENA,
			    SUN8I_MOD_CLK_ENA_AIF2, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CLK AIF3",
			    SUN8I_MOD_CLK_ENA,
			    SUN8I_MOD_CLK_ENA_AIF3, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CLK ADC",
			    SUN8I_MOD_CLK_ENA,
			    SUN8I_MOD_CLK_ENA_ADC, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("CLK DAC",
			    SUN8I_MOD_CLK_ENA,
			    SUN8I_MOD_CLK_ENA_DAC, 0, शून्य, 0),

	/* Module Resets */
	SND_SOC_DAPM_SUPPLY("RST AIF1",
			    SUN8I_MOD_RST_CTL,
			    SUN8I_MOD_RST_CTL_AIF1, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("RST AIF2",
			    SUN8I_MOD_RST_CTL,
			    SUN8I_MOD_RST_CTL_AIF2, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("RST AIF3",
			    SUN8I_MOD_RST_CTL,
			    SUN8I_MOD_RST_CTL_AIF3, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("RST ADC",
			    SUN8I_MOD_RST_CTL,
			    SUN8I_MOD_RST_CTL_ADC, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("RST DAC",
			    SUN8I_MOD_RST_CTL,
			    SUN8I_MOD_RST_CTL_DAC, 0, शून्य, 0),

	/* Module Supplies */
	SND_SOC_DAPM_SUPPLY("ADC",
			    SUN8I_ADC_DIG_CTRL,
			    SUN8I_ADC_DIG_CTRL_ENAD, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("DAC",
			    SUN8I_DAC_DIG_CTRL,
			    SUN8I_DAC_DIG_CTRL_ENDA, 0, शून्य, 0),

	/* AIF "ADC" Outमाला_दो */
	SND_SOC_DAPM_AIF_OUT_E("AIF1 AD0L", "AIF1 Capture", 0,
			       SUN8I_AIF1_ADCDAT_CTRL,
			       SUN8I_AIF1_ADCDAT_CTRL_AIF1_AD0L_ENA, 0,
			       sun8i_codec_aअगर_event,
			       SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_AIF_OUT("AIF1 AD0R", "AIF1 Capture", 1,
			     SUN8I_AIF1_ADCDAT_CTRL,
			     SUN8I_AIF1_ADCDAT_CTRL_AIF1_AD0R_ENA, 0),

	SND_SOC_DAPM_AIF_OUT_E("AIF2 ADCL", "AIF2 Capture", 0,
			       SUN8I_AIF2_ADCDAT_CTRL,
			       SUN8I_AIF2_ADCDAT_CTRL_AIF2_ADCL_ENA, 0,
			       sun8i_codec_aअगर_event,
			       SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_AIF_OUT("AIF2 ADCR", "AIF2 Capture", 1,
			     SUN8I_AIF2_ADCDAT_CTRL,
			     SUN8I_AIF2_ADCDAT_CTRL_AIF2_ADCR_ENA, 0),

	SND_SOC_DAPM_AIF_OUT_E("AIF3 ADC", "AIF3 Capture", 0,
			       SND_SOC_NOPM, 0, 0,
			       sun8i_codec_aअगर_event,
			       SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	/* AIF "ADC" Mono/Stereo Muxes */
	SND_SOC_DAPM_MUX("AIF1 AD0L Stereo Mux", SND_SOC_NOPM, 0, 0,
			 &sun8i_aअगर1_ad0_stereo_mux_control),
	SND_SOC_DAPM_MUX("AIF1 AD0R Stereo Mux", SND_SOC_NOPM, 0, 0,
			 &sun8i_aअगर1_ad0_stereo_mux_control),

	SND_SOC_DAPM_MUX("AIF2 ADCL Stereo Mux", SND_SOC_NOPM, 0, 0,
			 &sun8i_aअगर2_adc_stereo_mux_control),
	SND_SOC_DAPM_MUX("AIF2 ADCR Stereo Mux", SND_SOC_NOPM, 0, 0,
			 &sun8i_aअगर2_adc_stereo_mux_control),

	/* AIF "ADC" Output Muxes */
	SND_SOC_DAPM_MUX("AIF3 ADC Source Capture Route", SND_SOC_NOPM, 0, 0,
			 &sun8i_aअगर3_adc_mux_control),

	/* AIF "ADC" Mixers */
	SOC_MIXER_ARRAY("AIF1 AD0L Mixer", SND_SOC_NOPM, 0, 0,
			sun8i_aअगर1_ad0_mixer_controls),
	SOC_MIXER_ARRAY("AIF1 AD0R Mixer", SND_SOC_NOPM, 0, 0,
			sun8i_aअगर1_ad0_mixer_controls),

	SOC_MIXER_ARRAY("AIF2 ADCL Mixer", SND_SOC_NOPM, 0, 0,
			sun8i_aअगर2_adc_mixer_controls),
	SOC_MIXER_ARRAY("AIF2 ADCR Mixer", SND_SOC_NOPM, 0, 0,
			sun8i_aअगर2_adc_mixer_controls),

	/* AIF "DAC" Input Muxes */
	SND_SOC_DAPM_MUX("AIF2 DACL Source", SND_SOC_NOPM, 0, 0,
			 &sun8i_aअगर2_dac_mux_control),
	SND_SOC_DAPM_MUX("AIF2 DACR Source", SND_SOC_NOPM, 0, 0,
			 &sun8i_aअगर2_dac_mux_control),

	/* AIF "DAC" Mono/Stereo Muxes */
	SND_SOC_DAPM_MUX("AIF1 DA0L Stereo Mux", SND_SOC_NOPM, 0, 0,
			 &sun8i_aअगर1_da0_stereo_mux_control),
	SND_SOC_DAPM_MUX("AIF1 DA0R Stereo Mux", SND_SOC_NOPM, 0, 0,
			 &sun8i_aअगर1_da0_stereo_mux_control),

	SND_SOC_DAPM_MUX("AIF2 DACL Stereo Mux", SND_SOC_NOPM, 0, 0,
			 &sun8i_aअगर2_dac_stereo_mux_control),
	SND_SOC_DAPM_MUX("AIF2 DACR Stereo Mux", SND_SOC_NOPM, 0, 0,
			 &sun8i_aअगर2_dac_stereo_mux_control),

	/* AIF "DAC" Inमाला_दो */
	SND_SOC_DAPM_AIF_IN_E("AIF1 DA0L", "AIF1 Playback", 0,
			      SUN8I_AIF1_DACDAT_CTRL,
			      SUN8I_AIF1_DACDAT_CTRL_AIF1_DA0L_ENA, 0,
			      sun8i_codec_aअगर_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_AIF_IN("AIF1 DA0R", "AIF1 Playback", 1,
			    SUN8I_AIF1_DACDAT_CTRL,
			    SUN8I_AIF1_DACDAT_CTRL_AIF1_DA0R_ENA, 0),

	SND_SOC_DAPM_AIF_IN_E("AIF2 DACL", "AIF2 Playback", 0,
			      SUN8I_AIF2_DACDAT_CTRL,
			      SUN8I_AIF2_DACDAT_CTRL_AIF2_DACL_ENA, 0,
			      sun8i_codec_aअगर_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
	SND_SOC_DAPM_AIF_IN("AIF2 DACR", "AIF2 Playback", 1,
			    SUN8I_AIF2_DACDAT_CTRL,
			    SUN8I_AIF2_DACDAT_CTRL_AIF2_DACR_ENA, 0),

	SND_SOC_DAPM_AIF_IN_E("AIF3 DAC", "AIF3 Playback", 0,
			      SND_SOC_NOPM, 0, 0,
			      sun8i_codec_aअगर_event,
			      SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

	/* ADC Inमाला_दो (connected to analog codec DAPM context) */
	SND_SOC_DAPM_ADC("ADCL", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("ADCR", शून्य, SND_SOC_NOPM, 0, 0),

	/* DAC Outमाला_दो (connected to analog codec DAPM context) */
	SND_SOC_DAPM_DAC("DACL", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("DACR", शून्य, SND_SOC_NOPM, 0, 0),

	/* DAC Mixers */
	SOC_MIXER_ARRAY("DACL Mixer", SND_SOC_NOPM, 0, 0,
			sun8i_dac_mixer_controls),
	SOC_MIXER_ARRAY("DACR Mixer", SND_SOC_NOPM, 0, 0,
			sun8i_dac_mixer_controls),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route sun8i_codec_dapm_routes[] = अणु
	/* Clock Routes */
	अणु "AIF1CLK", शून्य, "mod" पूर्ण,

	अणु "SYSCLK", शून्य, "AIF1CLK" पूर्ण,

	अणु "CLK AIF1", शून्य, "AIF1CLK" पूर्ण,
	अणु "CLK AIF1", शून्य, "SYSCLK" पूर्ण,
	अणु "RST AIF1", शून्य, "CLK AIF1" पूर्ण,
	अणु "AIF1 AD0L", शून्य, "RST AIF1" पूर्ण,
	अणु "AIF1 AD0R", शून्य, "RST AIF1" पूर्ण,
	अणु "AIF1 DA0L", शून्य, "RST AIF1" पूर्ण,
	अणु "AIF1 DA0R", शून्य, "RST AIF1" पूर्ण,

	अणु "CLK AIF2", शून्य, "AIF2CLK" पूर्ण,
	अणु "CLK AIF2", शून्य, "SYSCLK" पूर्ण,
	अणु "RST AIF2", शून्य, "CLK AIF2" पूर्ण,
	अणु "AIF2 ADCL", शून्य, "RST AIF2" पूर्ण,
	अणु "AIF2 ADCR", शून्य, "RST AIF2" पूर्ण,
	अणु "AIF2 DACL", शून्य, "RST AIF2" पूर्ण,
	अणु "AIF2 DACR", शून्य, "RST AIF2" पूर्ण,

	अणु "CLK AIF3", शून्य, "AIF1CLK" पूर्ण,
	अणु "CLK AIF3", शून्य, "SYSCLK" पूर्ण,
	अणु "RST AIF3", शून्य, "CLK AIF3" पूर्ण,
	अणु "AIF3 ADC", शून्य, "RST AIF3" पूर्ण,
	अणु "AIF3 DAC", शून्य, "RST AIF3" पूर्ण,

	अणु "CLK ADC", शून्य, "SYSCLK" पूर्ण,
	अणु "RST ADC", शून्य, "CLK ADC" पूर्ण,
	अणु "ADC", शून्य, "RST ADC" पूर्ण,
	अणु "ADCL", शून्य, "ADC" पूर्ण,
	अणु "ADCR", शून्य, "ADC" पूर्ण,

	अणु "CLK DAC", शून्य, "SYSCLK" पूर्ण,
	अणु "RST DAC", शून्य, "CLK DAC" पूर्ण,
	अणु "DAC", शून्य, "RST DAC" पूर्ण,
	अणु "DACL", शून्य, "DAC" पूर्ण,
	अणु "DACR", शून्य, "DAC" पूर्ण,

	/* AIF "ADC" Output Routes */
	अणु "AIF1 AD0L", शून्य, "AIF1 AD0L Stereo Mux" पूर्ण,
	अणु "AIF1 AD0R", शून्य, "AIF1 AD0R Stereo Mux" पूर्ण,

	अणु "AIF2 ADCL", शून्य, "AIF2 ADCL Stereo Mux" पूर्ण,
	अणु "AIF2 ADCR", शून्य, "AIF2 ADCR Stereo Mux" पूर्ण,

	अणु "AIF3 ADC", शून्य, "AIF3 ADC Source Capture Route" पूर्ण,

	/* AIF "ADC" Mono/Stereo Mux Routes */
	अणु "AIF1 AD0L Stereo Mux", "Stereo", "AIF1 AD0L Mixer" पूर्ण,
	अणु "AIF1 AD0L Stereo Mux", "Reverse Stereo", "AIF1 AD0R Mixer" पूर्ण,
	अणु "AIF1 AD0L Stereo Mux", "Sum Mono", "AIF1 AD0L Mixer" पूर्ण,
	अणु "AIF1 AD0L Stereo Mux", "Sum Mono", "AIF1 AD0R Mixer" पूर्ण,
	अणु "AIF1 AD0L Stereo Mux", "Mix Mono", "AIF1 AD0L Mixer" पूर्ण,
	अणु "AIF1 AD0L Stereo Mux", "Mix Mono", "AIF1 AD0R Mixer" पूर्ण,

	अणु "AIF1 AD0R Stereo Mux", "Stereo", "AIF1 AD0R Mixer" पूर्ण,
	अणु "AIF1 AD0R Stereo Mux", "Reverse Stereo", "AIF1 AD0L Mixer" पूर्ण,
	अणु "AIF1 AD0R Stereo Mux", "Sum Mono", "AIF1 AD0L Mixer" पूर्ण,
	अणु "AIF1 AD0R Stereo Mux", "Sum Mono", "AIF1 AD0R Mixer" पूर्ण,
	अणु "AIF1 AD0R Stereo Mux", "Mix Mono", "AIF1 AD0L Mixer" पूर्ण,
	अणु "AIF1 AD0R Stereo Mux", "Mix Mono", "AIF1 AD0R Mixer" पूर्ण,

	अणु "AIF2 ADCL Stereo Mux", "Stereo", "AIF2 ADCL Mixer" पूर्ण,
	अणु "AIF2 ADCL Stereo Mux", "Reverse Stereo", "AIF2 ADCR Mixer" पूर्ण,
	अणु "AIF2 ADCL Stereo Mux", "Sum Mono", "AIF2 ADCL Mixer" पूर्ण,
	अणु "AIF2 ADCL Stereo Mux", "Sum Mono", "AIF2 ADCR Mixer" पूर्ण,
	अणु "AIF2 ADCL Stereo Mux", "Mix Mono", "AIF2 ADCL Mixer" पूर्ण,
	अणु "AIF2 ADCL Stereo Mux", "Mix Mono", "AIF2 ADCR Mixer" पूर्ण,

	अणु "AIF2 ADCR Stereo Mux", "Stereo", "AIF2 ADCR Mixer" पूर्ण,
	अणु "AIF2 ADCR Stereo Mux", "Reverse Stereo", "AIF2 ADCL Mixer" पूर्ण,
	अणु "AIF2 ADCR Stereo Mux", "Sum Mono", "AIF2 ADCL Mixer" पूर्ण,
	अणु "AIF2 ADCR Stereo Mux", "Sum Mono", "AIF2 ADCR Mixer" पूर्ण,
	अणु "AIF2 ADCR Stereo Mux", "Mix Mono", "AIF2 ADCL Mixer" पूर्ण,
	अणु "AIF2 ADCR Stereo Mux", "Mix Mono", "AIF2 ADCR Mixer" पूर्ण,

	/* AIF "ADC" Output Mux Routes */
	अणु "AIF3 ADC Source Capture Route", "AIF2 ADCL", "AIF2 ADCL Mixer" पूर्ण,
	अणु "AIF3 ADC Source Capture Route", "AIF2 ADCR", "AIF2 ADCR Mixer" पूर्ण,

	/* AIF "ADC" Mixer Routes */
	अणु "AIF1 AD0L Mixer", "AIF1 Slot 0 Digital ADC Capture Switch", "AIF1 DA0L Stereo Mux" पूर्ण,
	अणु "AIF1 AD0L Mixer", "AIF2 Digital ADC Capture Switch", "AIF2 DACL Source" पूर्ण,
	अणु "AIF1 AD0L Mixer", "AIF1 Data Digital ADC Capture Switch", "ADCL" पूर्ण,
	अणु "AIF1 AD0L Mixer", "AIF2 Inv Digital ADC Capture Switch", "AIF2 DACR Source" पूर्ण,

	अणु "AIF1 AD0R Mixer", "AIF1 Slot 0 Digital ADC Capture Switch", "AIF1 DA0R Stereo Mux" पूर्ण,
	अणु "AIF1 AD0R Mixer", "AIF2 Digital ADC Capture Switch", "AIF2 DACR Source" पूर्ण,
	अणु "AIF1 AD0R Mixer", "AIF1 Data Digital ADC Capture Switch", "ADCR" पूर्ण,
	अणु "AIF1 AD0R Mixer", "AIF2 Inv Digital ADC Capture Switch", "AIF2 DACL Source" पूर्ण,

	अणु "AIF2 ADCL Mixer", "AIF2 ADC Mixer AIF1 DA0 Capture Switch", "AIF1 DA0L Stereo Mux" पूर्ण,
	अणु "AIF2 ADCL Mixer", "AIF2 ADC Mixer AIF2 DAC Rev Capture Switch", "AIF2 DACR Source" पूर्ण,
	अणु "AIF2 ADCL Mixer", "AIF2 ADC Mixer ADC Capture Switch", "ADCL" पूर्ण,

	अणु "AIF2 ADCR Mixer", "AIF2 ADC Mixer AIF1 DA0 Capture Switch", "AIF1 DA0R Stereo Mux" पूर्ण,
	अणु "AIF2 ADCR Mixer", "AIF2 ADC Mixer AIF2 DAC Rev Capture Switch", "AIF2 DACL Source" पूर्ण,
	अणु "AIF2 ADCR Mixer", "AIF2 ADC Mixer ADC Capture Switch", "ADCR" पूर्ण,

	/* AIF "DAC" Input Mux Routes */
	अणु "AIF2 DACL Source", "AIF2", "AIF2 DACL Stereo Mux" पूर्ण,
	अणु "AIF2 DACL Source", "AIF3+2", "AIF3 DAC" पूर्ण,
	अणु "AIF2 DACL Source", "AIF2+3", "AIF2 DACL Stereo Mux" पूर्ण,

	अणु "AIF2 DACR Source", "AIF2", "AIF2 DACR Stereo Mux" पूर्ण,
	अणु "AIF2 DACR Source", "AIF3+2", "AIF2 DACR Stereo Mux" पूर्ण,
	अणु "AIF2 DACR Source", "AIF2+3", "AIF3 DAC" पूर्ण,

	/* AIF "DAC" Mono/Stereo Mux Routes */
	अणु "AIF1 DA0L Stereo Mux", "Stereo", "AIF1 DA0L" पूर्ण,
	अणु "AIF1 DA0L Stereo Mux", "Reverse Stereo", "AIF1 DA0R" पूर्ण,
	अणु "AIF1 DA0L Stereo Mux", "Sum Mono", "AIF1 DA0L" पूर्ण,
	अणु "AIF1 DA0L Stereo Mux", "Sum Mono", "AIF1 DA0R" पूर्ण,
	अणु "AIF1 DA0L Stereo Mux", "Mix Mono", "AIF1 DA0L" पूर्ण,
	अणु "AIF1 DA0L Stereo Mux", "Mix Mono", "AIF1 DA0R" पूर्ण,

	अणु "AIF1 DA0R Stereo Mux", "Stereo", "AIF1 DA0R" पूर्ण,
	अणु "AIF1 DA0R Stereo Mux", "Reverse Stereo", "AIF1 DA0L" पूर्ण,
	अणु "AIF1 DA0R Stereo Mux", "Sum Mono", "AIF1 DA0L" पूर्ण,
	अणु "AIF1 DA0R Stereo Mux", "Sum Mono", "AIF1 DA0R" पूर्ण,
	अणु "AIF1 DA0R Stereo Mux", "Mix Mono", "AIF1 DA0L" पूर्ण,
	अणु "AIF1 DA0R Stereo Mux", "Mix Mono", "AIF1 DA0R" पूर्ण,

	अणु "AIF2 DACL Stereo Mux", "Stereo", "AIF2 DACL" पूर्ण,
	अणु "AIF2 DACL Stereo Mux", "Reverse Stereo", "AIF2 DACR" पूर्ण,
	अणु "AIF2 DACL Stereo Mux", "Sum Mono", "AIF2 DACL" पूर्ण,
	अणु "AIF2 DACL Stereo Mux", "Sum Mono", "AIF2 DACR" पूर्ण,
	अणु "AIF2 DACL Stereo Mux", "Mix Mono", "AIF2 DACL" पूर्ण,
	अणु "AIF2 DACL Stereo Mux", "Mix Mono", "AIF2 DACR" पूर्ण,

	अणु "AIF2 DACR Stereo Mux", "Stereo", "AIF2 DACR" पूर्ण,
	अणु "AIF2 DACR Stereo Mux", "Reverse Stereo", "AIF2 DACL" पूर्ण,
	अणु "AIF2 DACR Stereo Mux", "Sum Mono", "AIF2 DACL" पूर्ण,
	अणु "AIF2 DACR Stereo Mux", "Sum Mono", "AIF2 DACR" पूर्ण,
	अणु "AIF2 DACR Stereo Mux", "Mix Mono", "AIF2 DACL" पूर्ण,
	अणु "AIF2 DACR Stereo Mux", "Mix Mono", "AIF2 DACR" पूर्ण,

	/* DAC Output Routes */
	अणु "DACL", शून्य, "DACL Mixer" पूर्ण,
	अणु "DACR", शून्य, "DACR Mixer" पूर्ण,

	/* DAC Mixer Routes */
	अणु "DACL Mixer", "AIF1 Slot 0 Digital DAC Playback Switch", "AIF1 DA0L Stereo Mux" पूर्ण,
	अणु "DACL Mixer", "AIF2 Digital DAC Playback Switch", "AIF2 DACL Source" पूर्ण,
	अणु "DACL Mixer", "ADC Digital DAC Playback Switch", "ADCL" पूर्ण,

	अणु "DACR Mixer", "AIF1 Slot 0 Digital DAC Playback Switch", "AIF1 DA0R Stereo Mux" पूर्ण,
	अणु "DACR Mixer", "AIF2 Digital DAC Playback Switch", "AIF2 DACR Source" पूर्ण,
	अणु "DACR Mixer", "ADC Digital DAC Playback Switch", "ADCR" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget sun8i_codec_legacy_widमाला_लो[] = अणु
	/* Legacy ADC Inमाला_दो (connected to analog codec DAPM context) */
	SND_SOC_DAPM_ADC("AIF1 Slot 0 Left ADC", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_ADC("AIF1 Slot 0 Right ADC", शून्य, SND_SOC_NOPM, 0, 0),

	/* Legacy DAC Outमाला_दो (connected to analog codec DAPM context) */
	SND_SOC_DAPM_DAC("AIF1 Slot 0 Left", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC("AIF1 Slot 0 Right", शून्य, SND_SOC_NOPM, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route sun8i_codec_legacy_routes[] = अणु
	/* Legacy ADC Routes */
	अणु "ADCL", शून्य, "AIF1 Slot 0 Left ADC" पूर्ण,
	अणु "ADCR", शून्य, "AIF1 Slot 0 Right ADC" पूर्ण,

	/* Legacy DAC Routes */
	अणु "AIF1 Slot 0 Left", शून्य, "DACL" पूर्ण,
	अणु "AIF1 Slot 0 Right", शून्य, "DACR" पूर्ण,
पूर्ण;

अटल पूर्णांक sun8i_codec_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	काष्ठा sun8i_codec *scodec = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	/* Add widमाला_लो क्रम backward compatibility with old device trees. */
	अगर (scodec->quirks->legacy_widमाला_लो) अणु
		ret = snd_soc_dapm_new_controls(dapm, sun8i_codec_legacy_widमाला_लो,
						ARRAY_SIZE(sun8i_codec_legacy_widमाला_लो));
		अगर (ret)
			वापस ret;

		ret = snd_soc_dapm_add_routes(dapm, sun8i_codec_legacy_routes,
					      ARRAY_SIZE(sun8i_codec_legacy_routes));
		अगर (ret)
			वापस ret;
	पूर्ण

	/*
	 * AIF1CLK and AIF2CLK share a pair of घड़ी parents: PLL_AUDIO ("mod")
	 * and MCLK (from the CPU DAI connected to AIF1). MCLK's parent is also
	 * PLL_AUDIO, so using it adds no additional flexibility. Use PLL_AUDIO
	 * directly to simplअगरy the घड़ी tree.
	 */
	regmap_update_bits(scodec->regmap, SUN8I_SYSCLK_CTL,
			   SUN8I_SYSCLK_CTL_AIF1CLK_SRC_MASK |
			   SUN8I_SYSCLK_CTL_AIF2CLK_SRC_MASK,
			   SUN8I_SYSCLK_CTL_AIF1CLK_SRC_PLL |
			   SUN8I_SYSCLK_CTL_AIF2CLK_SRC_PLL);

	/* Use AIF1CLK as the SYSCLK parent since AIF1 is used most often. */
	regmap_update_bits(scodec->regmap, SUN8I_SYSCLK_CTL,
			   BIT(SUN8I_SYSCLK_CTL_SYSCLK_SRC),
			   SUN8I_SYSCLK_CTL_SYSCLK_SRC_AIF1CLK);

	/* Program the शेष sample rate. */
	sun8i_codec_update_sample_rate(scodec);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver sun8i_soc_component = अणु
	.dapm_widमाला_लो		= sun8i_codec_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(sun8i_codec_dapm_widमाला_लो),
	.dapm_routes		= sun8i_codec_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(sun8i_codec_dapm_routes),
	.probe			= sun8i_codec_component_probe,
	.idle_bias_on		= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config sun8i_codec_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= SUN8I_DAC_MXR_SRC,

	.cache_type	= REGCACHE_FLAT,
पूर्ण;

अटल पूर्णांक sun8i_codec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun8i_codec *scodec;
	व्योम __iomem *base;
	पूर्णांक ret;

	scodec = devm_kzalloc(&pdev->dev, माप(*scodec), GFP_KERNEL);
	अगर (!scodec)
		वापस -ENOMEM;

	scodec->clk_module = devm_clk_get(&pdev->dev, "mod");
	अगर (IS_ERR(scodec->clk_module)) अणु
		dev_err(&pdev->dev, "Failed to get the module clock\n");
		वापस PTR_ERR(scodec->clk_module);
	पूर्ण

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base)) अणु
		dev_err(&pdev->dev, "Failed to map the registers\n");
		वापस PTR_ERR(base);
	पूर्ण

	scodec->regmap = devm_regmap_init_mmio_clk(&pdev->dev, "bus", base,
						   &sun8i_codec_regmap_config);
	अगर (IS_ERR(scodec->regmap)) अणु
		dev_err(&pdev->dev, "Failed to create our regmap\n");
		वापस PTR_ERR(scodec->regmap);
	पूर्ण

	scodec->quirks = of_device_get_match_data(&pdev->dev);

	platक्रमm_set_drvdata(pdev, scodec);

	pm_runसमय_enable(&pdev->dev);
	अगर (!pm_runसमय_enabled(&pdev->dev)) अणु
		ret = sun8i_codec_runसमय_resume(&pdev->dev);
		अगर (ret)
			जाओ err_pm_disable;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &sun8i_soc_component,
					      sun8i_codec_dais,
					      ARRAY_SIZE(sun8i_codec_dais));
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to register codec\n");
		जाओ err_suspend;
	पूर्ण

	वापस ret;

err_suspend:
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		sun8i_codec_runसमय_suspend(&pdev->dev);

err_pm_disable:
	pm_runसमय_disable(&pdev->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक sun8i_codec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);
	अगर (!pm_runसमय_status_suspended(&pdev->dev))
		sun8i_codec_runसमय_suspend(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sun8i_codec_quirks sun8i_a33_quirks = अणु
	.legacy_widमाला_लो	= true,
	.lrck_inversion	= true,
पूर्ण;

अटल स्थिर काष्ठा sun8i_codec_quirks sun50i_a64_quirks = अणु
पूर्ण;

अटल स्थिर काष्ठा of_device_id sun8i_codec_of_match[] = अणु
	अणु .compatible = "allwinner,sun8i-a33-codec", .data = &sun8i_a33_quirks पूर्ण,
	अणु .compatible = "allwinner,sun50i-a64-codec", .data = &sun50i_a64_quirks पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun8i_codec_of_match);

अटल स्थिर काष्ठा dev_pm_ops sun8i_codec_pm_ops = अणु
	SET_RUNTIME_PM_OPS(sun8i_codec_runसमय_suspend,
			   sun8i_codec_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver sun8i_codec_driver = अणु
	.driver = अणु
		.name = "sun8i-codec",
		.of_match_table = sun8i_codec_of_match,
		.pm = &sun8i_codec_pm_ops,
	पूर्ण,
	.probe = sun8i_codec_probe,
	.हटाओ = sun8i_codec_हटाओ,
पूर्ण;
module_platक्रमm_driver(sun8i_codec_driver);

MODULE_DESCRIPTION("Allwinner A33 (sun8i) codec driver");
MODULE_AUTHOR("Mylथउne Josserand <mylene.josserand@free-electrons.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:sun8i-codec");
