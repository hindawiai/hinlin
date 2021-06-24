<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Aपंचांगel PDMIC driver
 *
 * Copyright (C) 2015 Aपंचांगel
 *
 * Author: Songjun Wu <songjun.wu@aपंचांगel.com>
 */

#समावेश <linux/of.h>
#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/tlv.h>
#समावेश "atmel-pdmic.h"

काष्ठा aपंचांगel_pdmic_pdata अणु
	u32 mic_min_freq;
	u32 mic_max_freq;
	s32 mic_offset;
	स्थिर अक्षर *card_name;
पूर्ण;

काष्ठा aपंचांगel_pdmic अणु
	dma_addr_t phy_base;
	काष्ठा regmap *regmap;
	काष्ठा clk *pclk;
	काष्ठा clk *gclk;
	काष्ठा device *dev;
	पूर्णांक irq;
	काष्ठा snd_pcm_substream *substream;
	स्थिर काष्ठा aपंचांगel_pdmic_pdata *pdata;
पूर्ण;

अटल स्थिर काष्ठा of_device_id aपंचांगel_pdmic_of_match[] = अणु
	अणु
		.compatible = "atmel,sama5d2-pdmic",
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, aपंचांगel_pdmic_of_match);

#घोषणा PDMIC_OFFSET_MAX_VAL	S16_MAX
#घोषणा PDMIC_OFFSET_MIN_VAL	S16_MIN

अटल काष्ठा aपंचांगel_pdmic_pdata *aपंचांगel_pdmic_dt_init(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा aपंचांगel_pdmic_pdata *pdata;

	अगर (!np) अणु
		dev_err(dev, "device node not found\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	अगर (of_property_पढ़ो_string(np, "atmel,model", &pdata->card_name))
		pdata->card_name = "PDMIC";

	अगर (of_property_पढ़ो_u32(np, "atmel,mic-min-freq",
				 &pdata->mic_min_freq)) अणु
		dev_err(dev, "failed to get mic-min-freq\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (of_property_पढ़ो_u32(np, "atmel,mic-max-freq",
				 &pdata->mic_max_freq)) अणु
		dev_err(dev, "failed to get mic-max-freq\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (pdata->mic_max_freq < pdata->mic_min_freq) अणु
		dev_err(dev,
			"mic-max-freq should not be less than mic-min-freq\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (of_property_पढ़ो_s32(np, "atmel,mic-offset", &pdata->mic_offset))
		pdata->mic_offset = 0;

	अगर (pdata->mic_offset > PDMIC_OFFSET_MAX_VAL) अणु
		dev_warn(dev,
			 "mic-offset value %d is larger than the max value %d, the max value is specified\n",
			 pdata->mic_offset, PDMIC_OFFSET_MAX_VAL);
		pdata->mic_offset = PDMIC_OFFSET_MAX_VAL;
	पूर्ण अन्यथा अगर (pdata->mic_offset < PDMIC_OFFSET_MIN_VAL) अणु
		dev_warn(dev,
			 "mic-offset value %d is less than the min value %d, the min value is specified\n",
			 pdata->mic_offset, PDMIC_OFFSET_MIN_VAL);
		pdata->mic_offset = PDMIC_OFFSET_MIN_VAL;
	पूर्ण

	वापस pdata;
पूर्ण

/* cpu dai component */
अटल पूर्णांक aपंचांगel_pdmic_cpu_dai_startup(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा aपंचांगel_pdmic *dd = snd_soc_card_get_drvdata(rtd->card);
	पूर्णांक ret;

	ret = clk_prepare_enable(dd->gclk);
	अगर (ret)
		वापस ret;

	ret =  clk_prepare_enable(dd->pclk);
	अगर (ret) अणु
		clk_disable_unprepare(dd->gclk);
		वापस ret;
	पूर्ण

	/* Clear all bits in the Control Register(PDMIC_CR) */
	regmap_ग_लिखो(dd->regmap, PDMIC_CR, 0);

	dd->substream = substream;

	/* Enable the overrun error पूर्णांकerrupt */
	regmap_ग_लिखो(dd->regmap, PDMIC_IER, PDMIC_IER_OVRE);

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_pdmic_cpu_dai_shutकरोwn(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा aपंचांगel_pdmic *dd = snd_soc_card_get_drvdata(rtd->card);

	/* Disable the overrun error पूर्णांकerrupt */
	regmap_ग_लिखो(dd->regmap, PDMIC_IDR, PDMIC_IDR_OVRE);

	clk_disable_unprepare(dd->gclk);
	clk_disable_unprepare(dd->pclk);
पूर्ण

अटल पूर्णांक aपंचांगel_pdmic_cpu_dai_prepare(काष्ठा snd_pcm_substream *substream,
					काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा aपंचांगel_pdmic *dd = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_component *component = cpu_dai->component;
	u32 val;
	पूर्णांक ret;

	/* Clean the PDMIC Converted Data Register */
	ret = regmap_पढ़ो(dd->regmap, PDMIC_CDR, &val);
	अगर (ret < 0)
		वापस 0;

	ret = snd_soc_component_update_bits(component, PDMIC_CR,
					    PDMIC_CR_ENPDM_MASK,
					    PDMIC_CR_ENPDM_DIS <<
					    PDMIC_CR_ENPDM_SHIFT);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

#घोषणा ATMEL_PDMIC_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE)

/* platक्रमm */
#घोषणा ATMEL_PDMIC_MAX_BUF_SIZE  (64 * 1024)
#घोषणा ATMEL_PDMIC_PREALLOC_BUF_SIZE  ATMEL_PDMIC_MAX_BUF_SIZE

अटल स्थिर काष्ठा snd_pcm_hardware aपंचांगel_pdmic_hw = अणु
	.info			= SNDRV_PCM_INFO_MMAP
				| SNDRV_PCM_INFO_MMAP_VALID
				| SNDRV_PCM_INFO_INTERLEAVED
				| SNDRV_PCM_INFO_RESUME
				| SNDRV_PCM_INFO_PAUSE,
	.क्रमmats		= ATMEL_PDMIC_FORMATS,
	.buffer_bytes_max	= ATMEL_PDMIC_MAX_BUF_SIZE,
	.period_bytes_min	= 256,
	.period_bytes_max	= 32 * 1024,
	.periods_min		= 2,
	.periods_max		= 256,
पूर्ण;

अटल पूर्णांक
aपंचांगel_pdmic_platक्रमm_configure_dma(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा dma_slave_config *slave_config)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा aपंचांगel_pdmic *dd = snd_soc_card_get_drvdata(rtd->card);
	पूर्णांक ret;

	ret = snd_hwparams_to_dma_slave_config(substream, params,
					       slave_config);
	अगर (ret) अणु
		dev_err(dd->dev,
			"hw params to dma slave configure failed\n");
		वापस ret;
	पूर्ण

	slave_config->src_addr		= dd->phy_base + PDMIC_CDR;
	slave_config->src_maxburst	= 1;
	slave_config->dst_maxburst	= 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_dmaengine_pcm_config
aपंचांगel_pdmic_dmaengine_pcm_config = अणु
	.prepare_slave_config	= aपंचांगel_pdmic_platक्रमm_configure_dma,
	.pcm_hardware		= &aपंचांगel_pdmic_hw,
	.pपुनः_स्मृति_buffer_size	= ATMEL_PDMIC_PREALLOC_BUF_SIZE,
पूर्ण;

/* codec */
/* Mic Gain = dgain * 2^(-scale) */
काष्ठा mic_gain अणु
	अचिन्हित पूर्णांक dgain;
	अचिन्हित पूर्णांक scale;
पूर्ण;

/* range from -90 dB to 90 dB */
अटल स्थिर काष्ठा mic_gain mic_gain_table[] = अणु
अणु    1, 15पूर्ण, अणु    1, 14पूर्ण,                           /* -90, -84 dB */
अणु    3, 15पूर्ण, अणु    1, 13पूर्ण, अणु    3, 14पूर्ण, अणु    1, 12पूर्ण, /* -81, -78, -75, -72 dB */
अणु    5, 14पूर्ण, अणु   13, 15पूर्ण,                           /* -70, -68 dB */
अणु    9, 14पूर्ण, अणु   21, 15पूर्ण, अणु   23, 15पूर्ण, अणु   13, 14पूर्ण, /* -65 ~ -62 dB */
अणु   29, 15पूर्ण, अणु   33, 15पूर्ण, अणु   37, 15पूर्ण, अणु   41, 15पूर्ण, /* -61 ~ -58 dB */
अणु   23, 14पूर्ण, अणु   13, 13पूर्ण, अणु   58, 15पूर्ण, अणु   65, 15पूर्ण, /* -57 ~ -54 dB */
अणु   73, 15पूर्ण, अणु   41, 14पूर्ण, अणु   23, 13पूर्ण, अणु   13, 12पूर्ण, /* -53 ~ -50 dB */
अणु   29, 13पूर्ण, अणु   65, 14पूर्ण, अणु   73, 14पूर्ण, अणु   41, 13पूर्ण, /* -49 ~ -46 dB */
अणु   23, 12पूर्ण, अणु  207, 15पूर्ण, अणु   29, 12पूर्ण, अणु   65, 13पूर्ण, /* -45 ~ -42 dB */
अणु   73, 13पूर्ण, अणु   41, 12पूर्ण, अणु   23, 11पूर्ण, अणु  413, 15पूर्ण, /* -41 ~ -38 dB */
अणु  463, 15पूर्ण, अणु  519, 15पूर्ण, अणु  583, 15पूर्ण, अणु  327, 14पूर्ण, /* -37 ~ -34 dB */
अणु  367, 14पूर्ण, अणु  823, 15पूर्ण, अणु  231, 13पूर्ण, अणु 1036, 15पूर्ण, /* -33 ~ -30 dB */
अणु 1163, 15पूर्ण, अणु 1305, 15पूर्ण, अणु  183, 12पूर्ण, अणु 1642, 15पूर्ण, /* -29 ~ -26 dB */
अणु 1843, 15पूर्ण, अणु 2068, 15पूर्ण, अणु  145, 11पूर्ण, अणु 2603, 15पूर्ण, /* -25 ~ -22 dB */
अणु  365, 12पूर्ण, अणु 3277, 15पूर्ण, अणु 3677, 15पूर्ण, अणु 4125, 15पूर्ण, /* -21 ~ -18 dB */
अणु 4629, 15पूर्ण, अणु 5193, 15पूर्ण, अणु 5827, 15पूर्ण, अणु 3269, 14पूर्ण, /* -17 ~ -14 dB */
अणु  917, 12पूर्ण, अणु 8231, 15पूर्ण, अणु 9235, 15पूर्ण, अणु 5181, 14पूर्ण, /* -13 ~ -10 dB */
अणु11627, 15पूर्ण, अणु13045, 15पूर्ण, अणु14637, 15पूर्ण, अणु16423, 15पूर्ण, /*  -9 ~ -6 dB */
अणु18427, 15पूर्ण, अणु20675, 15पूर्ण, अणु 5799, 13पूर्ण, अणु26029, 15पूर्ण, /*  -5 ~ -2 dB */
अणु 7301, 13पूर्ण, अणु    1,  0पूर्ण, अणु18383, 14पूर्ण, अणु10313, 13पूर्ण, /*  -1 ~ 2 dB */
अणु23143, 14पूर्ण, अणु25967, 14पूर्ण, अणु29135, 14पूर्ण, अणु16345, 13पूर्ण, /*   3 ~ 6 dB */
अणु 4585, 11पूर्ण, अणु20577, 13पूर्ण, अणु 1443,  9पूर्ण, अणु25905, 13पूर्ण, /*   7 ~ 10 dB */
अणु14533, 12पूर्ण, अणु 8153, 11पूर्ण, अणु 2287,  9पूर्ण, अणु20529, 12पूर्ण, /*  11 ~ 14 dB */
अणु11517, 11पूर्ण, अणु 6461, 10पूर्ण, अणु28997, 12पूर्ण, अणु 4067,  9पूर्ण, /*  15 ~ 18 dB */
अणु18253, 11पूर्ण, अणु   10,  0पूर्ण, अणु22979, 11पूर्ण, अणु25783, 11पूर्ण, /*  19 ~ 22 dB */
अणु28929, 11पूर्ण, अणु32459, 11पूर्ण, अणु 9105,  9पूर्ण, अणु20431, 10पूर्ण, /*  23 ~ 26 dB */
अणु22925, 10पूर्ण, अणु12861,  9पूर्ण, अणु 7215,  8पूर्ण, अणु16191,  9पूर्ण, /*  27 ~ 30 dB */
अणु 9083,  8पूर्ण, अणु20383,  9पूर्ण, अणु11435,  8पूर्ण, अणु 6145,  7पूर्ण, /*  31 ~ 34 dB */
अणु 3599,  6पूर्ण, अणु32305,  9पूर्ण, अणु18123,  8पूर्ण, अणु20335,  8पूर्ण, /*  35 ~ 38 dB */
अणु  713,  3पूर्ण, अणु  100,  0पूर्ण, अणु 7181,  6पूर्ण, अणु 8057,  6पूर्ण, /*  39 ~ 42 dB */
अणु  565,  2पूर्ण, अणु20287,  7पूर्ण, अणु11381,  6पूर्ण, अणु25539,  7पूर्ण, /*  43 ~ 46 dB */
अणु 1791,  3पूर्ण, अणु 4019,  4पूर्ण, अणु 9019,  5पूर्ण, अणु20239,  6पूर्ण, /*  47 ~ 50 dB */
अणु 5677,  4पूर्ण, अणु25479,  6पूर्ण, अणु 7147,  4पूर्ण, अणु 8019,  4पूर्ण, /*  51 ~ 54 dB */
अणु17995,  5पूर्ण, अणु20191,  5पूर्ण, अणु11327,  4पूर्ण, अणु12709,  4पूर्ण, /*  55 ~ 58 dB */
अणु 3565,  2पूर्ण, अणु 1000,  0पूर्ण, अणु 1122,  0पूर्ण, अणु 1259,  0पूर्ण, /*  59 ~ 62 dB */
अणु 2825,  1पूर्ण, अणु12679,  3पूर्ण, अणु 7113,  2पूर्ण, अणु 7981,  2पूर्ण, /*  63 ~ 66 dB */
अणु 8955,  2पूर्ण, अणु20095,  3पूर्ण, अणु22547,  3पूर्ण, अणु12649,  2पूर्ण, /*  67 ~ 70 dB */
अणु28385,  3पूर्ण, अणु 3981,  0पूर्ण, अणु17867,  2पूर्ण, अणु20047,  2पूर्ण, /*  71 ~ 74 dB */
अणु11247,  1पूर्ण, अणु12619,  1पूर्ण, अणु14159,  1पूर्ण, अणु31773,  2पूर्ण, /*  75 ~ 78 dB */
अणु17825,  1पूर्ण, अणु10000,  0पूर्ण, अणु11220,  0पूर्ण, अणु12589,  0पूर्ण, /*  79 ~ 82 dB */
अणु28251,  1पूर्ण, अणु15849,  0पूर्ण, अणु17783,  0पूर्ण, अणु19953,  0पूर्ण, /*  83 ~ 86 dB */
अणु22387,  0पूर्ण, अणु25119,  0पूर्ण, अणु28184,  0पूर्ण, अणु31623,  0पूर्ण, /*  87 ~ 90 dB */
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_RANGE(mic_gain_tlv,
	0, 1, TLV_DB_SCALE_ITEM(-9000, 600, 0),
	2, 5, TLV_DB_SCALE_ITEM(-8100, 300, 0),
	6, 7, TLV_DB_SCALE_ITEM(-7000, 200, 0),
	8, ARRAY_SIZE(mic_gain_table)-1, TLV_DB_SCALE_ITEM(-6500, 100, 0),
);

अटल पूर्णांक pdmic_get_mic_volsw(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	अचिन्हित पूर्णांक dgain_val, scale_val;
	पूर्णांक i;

	dgain_val = (snd_soc_component_पढ़ो(component, PDMIC_DSPR1) & PDMIC_DSPR1_DGAIN_MASK)
		    >> PDMIC_DSPR1_DGAIN_SHIFT;

	scale_val = (snd_soc_component_पढ़ो(component, PDMIC_DSPR0) & PDMIC_DSPR0_SCALE_MASK)
		    >> PDMIC_DSPR0_SCALE_SHIFT;

	क्रम (i = 0; i < ARRAY_SIZE(mic_gain_table); i++) अणु
		अगर ((mic_gain_table[i].dgain == dgain_val) &&
		    (mic_gain_table[i].scale == scale_val))
			ucontrol->value.पूर्णांकeger.value[0] = i;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pdmic_put_mic_volsw(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	पूर्णांक max = mc->max;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	val = ucontrol->value.पूर्णांकeger.value[0];

	अगर (val > max)
		वापस -EINVAL;

	ret = snd_soc_component_update_bits(component, PDMIC_DSPR1, PDMIC_DSPR1_DGAIN_MASK,
			 mic_gain_table[val].dgain << PDMIC_DSPR1_DGAIN_SHIFT);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_component_update_bits(component, PDMIC_DSPR0, PDMIC_DSPR0_SCALE_MASK,
			 mic_gain_table[val].scale << PDMIC_DSPR0_SCALE_SHIFT);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new aपंचांगel_pdmic_snd_controls[] = अणु
SOC_SINGLE_EXT_TLV("Mic Capture Volume", PDMIC_DSPR1, PDMIC_DSPR1_DGAIN_SHIFT,
		   ARRAY_SIZE(mic_gain_table)-1, 0,
		   pdmic_get_mic_volsw, pdmic_put_mic_volsw, mic_gain_tlv),

SOC_SINGLE("High Pass Filter Switch", PDMIC_DSPR0,
	   PDMIC_DSPR0_HPFBYP_SHIFT, 1, 1),

SOC_SINGLE("SINCC Filter Switch", PDMIC_DSPR0, PDMIC_DSPR0_SINBYP_SHIFT, 1, 1),
पूर्ण;

अटल पूर्णांक aपंचांगel_pdmic_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_card *card = snd_soc_component_get_drvdata(component);
	काष्ठा aपंचांगel_pdmic *dd = snd_soc_card_get_drvdata(card);

	snd_soc_component_update_bits(component, PDMIC_DSPR1, PDMIC_DSPR1_OFFSET_MASK,
		     (u32)(dd->pdata->mic_offset << PDMIC_DSPR1_OFFSET_SHIFT));

	वापस 0;
पूर्ण

#घोषणा PDMIC_MR_PRESCAL_MAX_VAL 127

अटल पूर्णांक
aपंचांगel_pdmic_cpu_dai_hw_params(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *params,
			      काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा aपंचांगel_pdmic *dd = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_component *component = cpu_dai->component;
	अचिन्हित पूर्णांक rate_min = substream->runसमय->hw.rate_min;
	अचिन्हित पूर्णांक rate_max = substream->runसमय->hw.rate_max;
	पूर्णांक fs = params_rate(params);
	पूर्णांक bits = params_width(params);
	अचिन्हित दीर्घ pclk_rate, gclk_rate;
	अचिन्हित पूर्णांक f_pdmic;
	u32 mr_val, dspr0_val, pclk_prescal, gclk_prescal;

	अगर (params_channels(params) != 1) अणु
		dev_err(component->dev,
			"only supports one channel\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((fs < rate_min) || (fs > rate_max)) अणु
		dev_err(component->dev,
			"sample rate is %dHz, min rate is %dHz, max rate is %dHz\n",
			fs, rate_min, rate_max);

		वापस -EINVAL;
	पूर्ण

	चयन (bits) अणु
	हाल 16:
		dspr0_val = (PDMIC_DSPR0_SIZE_16_BITS
			     << PDMIC_DSPR0_SIZE_SHIFT);
		अवरोध;
	हाल 32:
		dspr0_val = (PDMIC_DSPR0_SIZE_32_BITS
			     << PDMIC_DSPR0_SIZE_SHIFT);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर ((fs << 7) > (rate_max << 6)) अणु
		f_pdmic = fs << 6;
		dspr0_val |= PDMIC_DSPR0_OSR_64 << PDMIC_DSPR0_OSR_SHIFT;
	पूर्ण अन्यथा अणु
		f_pdmic = fs << 7;
		dspr0_val |= PDMIC_DSPR0_OSR_128 << PDMIC_DSPR0_OSR_SHIFT;
	पूर्ण

	pclk_rate = clk_get_rate(dd->pclk);
	gclk_rate = clk_get_rate(dd->gclk);

	/* PRESCAL = SELCK/(2*f_pdmic) - 1*/
	pclk_prescal = (u32)(pclk_rate/(f_pdmic << 1)) - 1;
	gclk_prescal = (u32)(gclk_rate/(f_pdmic << 1)) - 1;

	अगर ((pclk_prescal > PDMIC_MR_PRESCAL_MAX_VAL) ||
	    (gclk_rate/((gclk_prescal + 1) << 1) <
	     pclk_rate/((pclk_prescal + 1) << 1))) अणु
		mr_val = gclk_prescal << PDMIC_MR_PRESCAL_SHIFT;
		mr_val |= PDMIC_MR_CLKS_GCK << PDMIC_MR_CLKS_SHIFT;
	पूर्ण अन्यथा अणु
		mr_val = pclk_prescal << PDMIC_MR_PRESCAL_SHIFT;
		mr_val |= PDMIC_MR_CLKS_PCK << PDMIC_MR_CLKS_SHIFT;
	पूर्ण

	snd_soc_component_update_bits(component, PDMIC_MR,
		PDMIC_MR_PRESCAL_MASK | PDMIC_MR_CLKS_MASK, mr_val);

	snd_soc_component_update_bits(component, PDMIC_DSPR0,
		PDMIC_DSPR0_OSR_MASK | PDMIC_DSPR0_SIZE_MASK, dspr0_val);

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_pdmic_cpu_dai_trigger(काष्ठा snd_pcm_substream *substream,
				       पूर्णांक cmd, काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा snd_soc_component *component = cpu_dai->component;
	u32 val;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		val = PDMIC_CR_ENPDM_EN << PDMIC_CR_ENPDM_SHIFT;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		val = PDMIC_CR_ENPDM_DIS << PDMIC_CR_ENPDM_SHIFT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, PDMIC_CR, PDMIC_CR_ENPDM_MASK, val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops aपंचांगel_pdmic_cpu_dai_ops = अणु
	.startup	= aपंचांगel_pdmic_cpu_dai_startup,
	.shutकरोwn	= aपंचांगel_pdmic_cpu_dai_shutकरोwn,
	.prepare	= aपंचांगel_pdmic_cpu_dai_prepare,
	.hw_params	= aपंचांगel_pdmic_cpu_dai_hw_params,
	.trigger	= aपंचांगel_pdmic_cpu_dai_trigger,
पूर्ण;


अटल काष्ठा snd_soc_dai_driver aपंचांगel_pdmic_cpu_dai = अणु
	.capture = अणु
		.stream_name	= "Capture",
		.channels_min	= 1,
		.channels_max	= 1,
		.rates		= SNDRV_PCM_RATE_KNOT,
		.क्रमmats	= ATMEL_PDMIC_FORMATS,
	पूर्ण,
	.ops = &aपंचांगel_pdmic_cpu_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver aपंचांगel_pdmic_cpu_dai_component = अणु
	.name			= "atmel-pdmic",
	.probe			= aपंचांगel_pdmic_component_probe,
	.controls		= aपंचांगel_pdmic_snd_controls,
	.num_controls		= ARRAY_SIZE(aपंचांगel_pdmic_snd_controls),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
पूर्ण;

/* ASoC sound card */
अटल पूर्णांक aपंचांगel_pdmic_asoc_card_init(काष्ठा device *dev,
				काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_dai_link *dai_link;
	काष्ठा aपंचांगel_pdmic *dd = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_dai_link_component *comp;

	dai_link = devm_kzalloc(dev, माप(*dai_link), GFP_KERNEL);
	अगर (!dai_link)
		वापस -ENOMEM;

	comp = devm_kzalloc(dev, 3 * माप(*comp), GFP_KERNEL);
	अगर (!comp)
		वापस -ENOMEM;

	dai_link->cpus		= &comp[0];
	dai_link->codecs	= &comp[1];
	dai_link->platक्रमms	= &comp[2];

	dai_link->num_cpus	= 1;
	dai_link->num_codecs	= 1;
	dai_link->num_platक्रमms	= 1;

	dai_link->name			= "PDMIC";
	dai_link->stream_name		= "PDMIC PCM";
	dai_link->codecs->dai_name	= "snd-soc-dummy-dai";
	dai_link->cpus->dai_name	= dev_name(dev);
	dai_link->codecs->name		= "snd-soc-dummy";
	dai_link->platक्रमms->name	= dev_name(dev);

	card->dai_link	= dai_link;
	card->num_links	= 1;
	card->name	= dd->pdata->card_name;
	card->dev	= dev;

	वापस 0;
पूर्ण

अटल व्योम aपंचांगel_pdmic_get_sample_rate(काष्ठा aपंचांगel_pdmic *dd,
	अचिन्हित पूर्णांक *rate_min, अचिन्हित पूर्णांक *rate_max)
अणु
	u32 mic_min_freq = dd->pdata->mic_min_freq;
	u32 mic_max_freq = dd->pdata->mic_max_freq;
	u32 clk_max_rate = (u32)(clk_get_rate(dd->pclk) >> 1);
	u32 clk_min_rate = (u32)(clk_get_rate(dd->gclk) >> 8);

	अगर (mic_max_freq > clk_max_rate)
		mic_max_freq = clk_max_rate;

	अगर (mic_min_freq < clk_min_rate)
		mic_min_freq = clk_min_rate;

	*rate_min = DIV_ROUND_CLOSEST(mic_min_freq, 128);
	*rate_max = mic_max_freq >> 6;
पूर्ण

/* PDMIC पूर्णांकerrupt handler */
अटल irqवापस_t aपंचांगel_pdmic_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा aपंचांगel_pdmic *dd = (काष्ठा aपंचांगel_pdmic *)dev_id;
	u32 pdmic_isr;
	irqवापस_t ret = IRQ_NONE;

	regmap_पढ़ो(dd->regmap, PDMIC_ISR, &pdmic_isr);

	अगर (pdmic_isr & PDMIC_ISR_OVRE) अणु
		regmap_update_bits(dd->regmap, PDMIC_CR, PDMIC_CR_ENPDM_MASK,
				   PDMIC_CR_ENPDM_DIS << PDMIC_CR_ENPDM_SHIFT);

		snd_pcm_stop_xrun(dd->substream);

		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

/* regmap configuration */
#घोषणा ATMEL_PDMIC_REG_MAX    0x124
अटल स्थिर काष्ठा regmap_config aपंचांगel_pdmic_regmap_config = अणु
	.reg_bits	= 32,
	.reg_stride	= 4,
	.val_bits	= 32,
	.max_रेजिस्टर	= ATMEL_PDMIC_REG_MAX,
पूर्ण;

अटल पूर्णांक aपंचांगel_pdmic_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा aपंचांगel_pdmic *dd;
	काष्ठा resource *res;
	व्योम __iomem *io_base;
	स्थिर काष्ठा aपंचांगel_pdmic_pdata *pdata;
	काष्ठा snd_soc_card *card;
	अचिन्हित पूर्णांक rate_min, rate_max;
	पूर्णांक ret;

	pdata = aपंचांगel_pdmic_dt_init(dev);
	अगर (IS_ERR(pdata))
		वापस PTR_ERR(pdata);

	dd = devm_kzalloc(dev, माप(*dd), GFP_KERNEL);
	अगर (!dd)
		वापस -ENOMEM;

	dd->pdata = pdata;
	dd->dev = dev;

	dd->irq = platक्रमm_get_irq(pdev, 0);
	अगर (dd->irq < 0)
		वापस dd->irq;

	dd->pclk = devm_clk_get(dev, "pclk");
	अगर (IS_ERR(dd->pclk)) अणु
		ret = PTR_ERR(dd->pclk);
		dev_err(dev, "failed to get peripheral clock: %d\n", ret);
		वापस ret;
	पूर्ण

	dd->gclk = devm_clk_get(dev, "gclk");
	अगर (IS_ERR(dd->gclk)) अणु
		ret = PTR_ERR(dd->gclk);
		dev_err(dev, "failed to get GCK: %d\n", ret);
		वापस ret;
	पूर्ण

	/* The gclk घड़ी frequency must always be three बार
	 * lower than the pclk घड़ी frequency
	 */
	ret = clk_set_rate(dd->gclk, clk_get_rate(dd->pclk)/3);
	अगर (ret) अणु
		dev_err(dev, "failed to set GCK clock rate: %d\n", ret);
		वापस ret;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	io_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(io_base))
		वापस PTR_ERR(io_base);

	dd->phy_base = res->start;

	dd->regmap = devm_regmap_init_mmio(dev, io_base,
					   &aपंचांगel_pdmic_regmap_config);
	अगर (IS_ERR(dd->regmap)) अणु
		ret = PTR_ERR(dd->regmap);
		dev_err(dev, "failed to init register map: %d\n", ret);
		वापस ret;
	पूर्ण

	ret =  devm_request_irq(dev, dd->irq, aपंचांगel_pdmic_पूर्णांकerrupt, 0,
				"PDMIC", (व्योम *)dd);
	अगर (ret < 0) अणु
		dev_err(dev, "can't register ISR for IRQ %u (ret=%i)\n",
			dd->irq, ret);
		वापस ret;
	पूर्ण

	/* Get the minimal and maximal sample rate that the microphone supports */
	aपंचांगel_pdmic_get_sample_rate(dd, &rate_min, &rate_max);

	/* रेजिस्टर cpu dai */
	aपंचांगel_pdmic_cpu_dai.capture.rate_min = rate_min;
	aपंचांगel_pdmic_cpu_dai.capture.rate_max = rate_max;
	ret = devm_snd_soc_रेजिस्टर_component(dev,
					      &aपंचांगel_pdmic_cpu_dai_component,
					      &aपंचांगel_pdmic_cpu_dai, 1);
	अगर (ret) अणु
		dev_err(dev, "could not register CPU DAI: %d\n", ret);
		वापस ret;
	पूर्ण

	/* रेजिस्टर platक्रमm */
	ret = devm_snd_dmaengine_pcm_रेजिस्टर(dev,
					     &aपंचांगel_pdmic_dmaengine_pcm_config,
					     0);
	अगर (ret) अणु
		dev_err(dev, "could not register platform: %d\n", ret);
		वापस ret;
	पूर्ण

	/* रेजिस्टर sound card */
	card = devm_kzalloc(dev, माप(*card), GFP_KERNEL);
	अगर (!card) अणु
		ret = -ENOMEM;
		जाओ unरेजिस्टर_codec;
	पूर्ण

	snd_soc_card_set_drvdata(card, dd);

	ret = aपंचांगel_pdmic_asoc_card_init(dev, card);
	अगर (ret) अणु
		dev_err(dev, "failed to init sound card: %d\n", ret);
		जाओ unरेजिस्टर_codec;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_card(dev, card);
	अगर (ret) अणु
		dev_err(dev, "failed to register sound card: %d\n", ret);
		जाओ unरेजिस्टर_codec;
	पूर्ण

	वापस 0;

unरेजिस्टर_codec:
	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_pdmic_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver aपंचांगel_pdmic_driver = अणु
	.driver	= अणु
		.name		= "atmel-pdmic",
		.of_match_table	= of_match_ptr(aपंचांगel_pdmic_of_match),
		.pm		= &snd_soc_pm_ops,
	पूर्ण,
	.probe	= aपंचांगel_pdmic_probe,
	.हटाओ	= aपंचांगel_pdmic_हटाओ,
पूर्ण;
module_platक्रमm_driver(aपंचांगel_pdmic_driver);

MODULE_DESCRIPTION("Atmel PDMIC driver under ALSA SoC architecture");
MODULE_AUTHOR("Songjun Wu <songjun.wu@atmel.com>");
MODULE_LICENSE("GPL v2");
