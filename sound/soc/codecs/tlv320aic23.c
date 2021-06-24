<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ALSA SoC TLV320AIC23 codec driver
 *
 * Author:      Arun KS, <arunks@mistralsolutions.com>
 * Copyright:   (C) 2008 Mistral Solutions Pvt Ltd.,
 *
 * Based on sound/soc/codecs/wm8731.c by Riअक्षरd Purdie
 *
 * Notes:
 *  The AIC23 is a driver क्रम a low घातer stereo audio
 *  codec tlv320aic23
 *
 *  The machine layer should disable unsupported inमाला_दो/outमाला_दो by
 *  snd_soc_dapm_disable_pin(codec, "LHPOUT"), etc.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <sound/initval.h>

#समावेश "tlv320aic23.h"

/*
 * AIC23 रेजिस्टर cache
 */
अटल स्थिर काष्ठा reg_शेष tlv320aic23_reg[] = अणु
	अणु  0, 0x0097 पूर्ण,
	अणु  1, 0x0097 पूर्ण,
	अणु  2, 0x00F9 पूर्ण,
	अणु  3, 0x00F9 पूर्ण,
	अणु  4, 0x001A पूर्ण,
	अणु  5, 0x0004 पूर्ण,
	अणु  6, 0x0007 पूर्ण,
	अणु  7, 0x0001 पूर्ण,
	अणु  8, 0x0020 पूर्ण,
	अणु  9, 0x0000 पूर्ण,
पूर्ण;

स्थिर काष्ठा regmap_config tlv320aic23_regmap = अणु
	.reg_bits = 7,
	.val_bits = 9,

	.max_रेजिस्टर = TLV320AIC23_RESET,
	.reg_शेषs = tlv320aic23_reg,
	.num_reg_शेषs = ARRAY_SIZE(tlv320aic23_reg),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;
EXPORT_SYMBOL(tlv320aic23_regmap);

अटल स्थिर अक्षर *rec_src_text[] = अणु "Line", "Mic" पूर्ण;
अटल स्थिर अक्षर *deemph_text[] = अणु"None", "32Khz", "44.1Khz", "48Khz"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(rec_src_क्रमागत,
			    TLV320AIC23_ANLG, 2, rec_src_text);

अटल स्थिर काष्ठा snd_kcontrol_new tlv320aic23_rec_src_mux_controls =
SOC_DAPM_ENUM("Input Select", rec_src_क्रमागत);

अटल SOC_ENUM_SINGLE_DECL(tlv320aic23_deemph,
			    TLV320AIC23_DIGT, 1, deemph_text);

अटल स्थिर DECLARE_TLV_DB_SCALE(out_gain_tlv, -12100, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(input_gain_tlv, -1725, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(sidetone_vol_tlv, -1800, 300, 0);

अटल पूर्णांक snd_soc_tlv320aic23_put_volsw(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	u16 val, reg;

	val = (ucontrol->value.पूर्णांकeger.value[0] & 0x07);

	/* linear conversion to userspace
	* 000	=	-6db
	* 001	=	-9db
	* 010	=	-12db
	* 011	=	-18db (Min)
	* 100	=	0db (Max)
	*/
	val = (val >= 4) ? 4  : (3 - val);

	reg = snd_soc_component_पढ़ो(component, TLV320AIC23_ANLG) & (~0x1C0);
	snd_soc_component_ग_लिखो(component, TLV320AIC23_ANLG, reg | (val << 6));

	वापस 0;
पूर्ण

अटल पूर्णांक snd_soc_tlv320aic23_get_volsw(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	u16 val;

	val = snd_soc_component_पढ़ो(component, TLV320AIC23_ANLG) & (0x1C0);
	val = val >> 6;
	val = (val >= 4) ? 4  : (3 -  val);
	ucontrol->value.पूर्णांकeger.value[0] = val;
	वापस 0;

पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new tlv320aic23_snd_controls[] = अणु
	SOC_DOUBLE_R_TLV("Digital Playback Volume", TLV320AIC23_LCHNVOL,
			 TLV320AIC23_RCHNVOL, 0, 127, 0, out_gain_tlv),
	SOC_SINGLE("Digital Playback Switch", TLV320AIC23_DIGT, 3, 1, 1),
	SOC_DOUBLE_R("Line Input Switch", TLV320AIC23_LINVOL,
		     TLV320AIC23_RINVOL, 7, 1, 0),
	SOC_DOUBLE_R_TLV("Line Input Volume", TLV320AIC23_LINVOL,
			 TLV320AIC23_RINVOL, 0, 31, 0, input_gain_tlv),
	SOC_SINGLE("Mic Input Switch", TLV320AIC23_ANLG, 1, 1, 1),
	SOC_SINGLE("Mic Booster Switch", TLV320AIC23_ANLG, 0, 1, 0),
	SOC_SINGLE_EXT_TLV("Sidetone Volume", TLV320AIC23_ANLG, 6, 4, 0,
			   snd_soc_tlv320aic23_get_volsw,
			   snd_soc_tlv320aic23_put_volsw, sidetone_vol_tlv),
	SOC_ENUM("Playback De-emphasis", tlv320aic23_deemph),
पूर्ण;

/* PGA Mixer controls क्रम Line and Mic चयन */
अटल स्थिर काष्ठा snd_kcontrol_new tlv320aic23_output_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Line Bypass Switch", TLV320AIC23_ANLG, 3, 1, 0),
	SOC_DAPM_SINGLE("Mic Sidetone Switch", TLV320AIC23_ANLG, 5, 1, 0),
	SOC_DAPM_SINGLE("Playback Switch", TLV320AIC23_ANLG, 4, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget tlv320aic23_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("DAC", "Playback", TLV320AIC23_PWR, 3, 1),
	SND_SOC_DAPM_ADC("ADC", "Capture", TLV320AIC23_PWR, 2, 1),
	SND_SOC_DAPM_MUX("Capture Source", SND_SOC_NOPM, 0, 0,
			 &tlv320aic23_rec_src_mux_controls),
	SND_SOC_DAPM_MIXER("Output Mixer", TLV320AIC23_PWR, 4, 1,
			   &tlv320aic23_output_mixer_controls[0],
			   ARRAY_SIZE(tlv320aic23_output_mixer_controls)),
	SND_SOC_DAPM_PGA("Line Input", TLV320AIC23_PWR, 0, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("Mic Input", TLV320AIC23_PWR, 1, 1, शून्य, 0),

	SND_SOC_DAPM_OUTPUT("LHPOUT"),
	SND_SOC_DAPM_OUTPUT("RHPOUT"),
	SND_SOC_DAPM_OUTPUT("LOUT"),
	SND_SOC_DAPM_OUTPUT("ROUT"),

	SND_SOC_DAPM_INPUT("LLINEIN"),
	SND_SOC_DAPM_INPUT("RLINEIN"),

	SND_SOC_DAPM_INPUT("MICIN"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route tlv320aic23_पूर्णांकercon[] = अणु
	/* Output Mixer */
	अणु"Output Mixer", "Line Bypass Switch", "Line Input"पूर्ण,
	अणु"Output Mixer", "Playback Switch", "DAC"पूर्ण,
	अणु"Output Mixer", "Mic Sidetone Switch", "Mic Input"पूर्ण,

	/* Outमाला_दो */
	अणु"RHPOUT", शून्य, "Output Mixer"पूर्ण,
	अणु"LHPOUT", शून्य, "Output Mixer"पूर्ण,
	अणु"LOUT", शून्य, "Output Mixer"पूर्ण,
	अणु"ROUT", शून्य, "Output Mixer"पूर्ण,

	/* Inमाला_दो */
	अणु"Line Input", शून्य, "LLINEIN"पूर्ण,
	अणु"Line Input", शून्य, "RLINEIN"पूर्ण,
	अणु"Mic Input", शून्य, "MICIN"पूर्ण,

	/* input mux */
	अणु"Capture Source", "Line", "Line Input"पूर्ण,
	अणु"Capture Source", "Mic", "Mic Input"पूर्ण,
	अणु"ADC", शून्य, "Capture Source"पूर्ण,

पूर्ण;

/* AIC23 driver data */
काष्ठा aic23 अणु
	काष्ठा regmap *regmap;
	पूर्णांक mclk;
	पूर्णांक requested_adc;
	पूर्णांक requested_dac;
पूर्ण;

/*
 * Common Crystals used
 * 11.2896 Mhz /128 = *88.2k  /192 = 58.8k
 * 12.0000 Mhz /125 = *96k    /136 = 88.235K
 * 12.2880 Mhz /128 = *96k    /192 = 64k
 * 16.9344 Mhz /128 = 132.3k /192 = *88.2k
 * 18.4320 Mhz /128 = 144k   /192 = *96k
 */

/*
 * Normal BOSR 0-256/2 = 128, 1-384/2 = 192
 * USB BOSR 0-250/2 = 125, 1-272/2 = 136
 */
अटल स्थिर पूर्णांक bosr_usb_भागisor_table[] = अणु
	128, 125, 192, 136
पूर्ण;
#घोषणा LOWER_GROUP ((1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<6) | (1<<7))
#घोषणा UPPER_GROUP ((1<<8) | (1<<9) | (1<<10) | (1<<11)        | (1<<15))
अटल स्थिर अचिन्हित लघु sr_valid_mask[] = अणु
	LOWER_GROUP|UPPER_GROUP,	/* Normal, bosr - 0*/
	LOWER_GROUP,			/* Usb, bosr - 0*/
	LOWER_GROUP|UPPER_GROUP,	/* Normal, bosr - 1*/
	UPPER_GROUP,			/* Usb, bosr - 1*/
पूर्ण;
/*
 * Every भागisor is a factor of 11*12
 */
#घोषणा SR_MULT (11*12)
#घोषणा A(x) (SR_MULT/x)
अटल स्थिर अचिन्हित अक्षर sr_adc_mult_table[] = अणु
	A(2), A(2), A(12), A(12),  0, 0, A(3), A(1),
	A(2), A(2), A(11), A(11),  0, 0, 0, A(1)
पूर्ण;
अटल स्थिर अचिन्हित अक्षर sr_dac_mult_table[] = अणु
	A(2), A(12), A(2), A(12),  0, 0, A(3), A(1),
	A(2), A(11), A(2), A(11),  0, 0, 0, A(1)
पूर्ण;

अटल अचिन्हित get_score(पूर्णांक adc, पूर्णांक adc_l, पूर्णांक adc_h, पूर्णांक need_adc,
		पूर्णांक dac, पूर्णांक dac_l, पूर्णांक dac_h, पूर्णांक need_dac)
अणु
	अगर ((adc >= adc_l) && (adc <= adc_h) &&
			(dac >= dac_l) && (dac <= dac_h)) अणु
		पूर्णांक dअगरf_adc = need_adc - adc;
		पूर्णांक dअगरf_dac = need_dac - dac;
		वापस असल(dअगरf_adc) + असल(dअगरf_dac);
	पूर्ण
	वापस अच_पूर्णांक_उच्च;
पूर्ण

अटल पूर्णांक find_rate(पूर्णांक mclk, u32 need_adc, u32 need_dac)
अणु
	पूर्णांक i, j;
	पूर्णांक best_i = -1;
	पूर्णांक best_j = -1;
	पूर्णांक best_भाग = 0;
	अचिन्हित best_score = अच_पूर्णांक_उच्च;
	पूर्णांक adc_l, adc_h, dac_l, dac_h;

	need_adc *= SR_MULT;
	need_dac *= SR_MULT;
	/*
	 * rates given are +/- 1/32
	 */
	adc_l = need_adc - (need_adc >> 5);
	adc_h = need_adc + (need_adc >> 5);
	dac_l = need_dac - (need_dac >> 5);
	dac_h = need_dac + (need_dac >> 5);
	क्रम (i = 0; i < ARRAY_SIZE(bosr_usb_भागisor_table); i++) अणु
		पूर्णांक base = mclk / bosr_usb_भागisor_table[i];
		पूर्णांक mask = sr_valid_mask[i];
		क्रम (j = 0; j < ARRAY_SIZE(sr_adc_mult_table);
				j++, mask >>= 1) अणु
			पूर्णांक adc;
			पूर्णांक dac;
			पूर्णांक score;
			अगर ((mask & 1) == 0)
				जारी;
			adc = base * sr_adc_mult_table[j];
			dac = base * sr_dac_mult_table[j];
			score = get_score(adc, adc_l, adc_h, need_adc,
					dac, dac_l, dac_h, need_dac);
			अगर (best_score > score) अणु
				best_score = score;
				best_i = i;
				best_j = j;
				best_भाग = 0;
			पूर्ण
			score = get_score((adc >> 1), adc_l, adc_h, need_adc,
					(dac >> 1), dac_l, dac_h, need_dac);
			/* prefer to have a /2 */
			अगर ((score != अच_पूर्णांक_उच्च) && (best_score >= score)) अणु
				best_score = score;
				best_i = i;
				best_j = j;
				best_भाग = 1;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस (best_j << 2) | best_i | (best_भाग << TLV320AIC23_CLKIN_SHIFT);
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम get_current_sample_rates(काष्ठा snd_soc_component *component, पूर्णांक mclk,
		u32 *sample_rate_adc, u32 *sample_rate_dac)
अणु
	पूर्णांक src = snd_soc_component_पढ़ो(component, TLV320AIC23_SRATE);
	पूर्णांक sr = (src >> 2) & 0x0f;
	पूर्णांक val = (mclk / bosr_usb_भागisor_table[src & 3]);
	पूर्णांक adc = (val * sr_adc_mult_table[sr]) / SR_MULT;
	पूर्णांक dac = (val * sr_dac_mult_table[sr]) / SR_MULT;
	अगर (src & TLV320AIC23_CLKIN_HALF) अणु
		adc >>= 1;
		dac >>= 1;
	पूर्ण
	*sample_rate_adc = adc;
	*sample_rate_dac = dac;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक set_sample_rate_control(काष्ठा snd_soc_component *component, पूर्णांक mclk,
		u32 sample_rate_adc, u32 sample_rate_dac)
अणु
	/* Search क्रम the right sample rate */
	पूर्णांक data = find_rate(mclk, sample_rate_adc, sample_rate_dac);
	अगर (data < 0) अणु
		prपूर्णांकk(KERN_ERR "%s:Invalid rate %u,%u requested\n",
				__func__, sample_rate_adc, sample_rate_dac);
		वापस -EINVAL;
	पूर्ण
	snd_soc_component_ग_लिखो(component, TLV320AIC23_SRATE, data);
#अगर_घोषित DEBUG
	अणु
		u32 adc, dac;
		get_current_sample_rates(component, mclk, &adc, &dac);
		prपूर्णांकk(KERN_DEBUG "actual samplerate = %u,%u reg=%x\n",
			adc, dac, data);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक tlv320aic23_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 अगरace_reg;
	पूर्णांक ret;
	काष्ठा aic23 *aic23 = snd_soc_component_get_drvdata(component);
	u32 sample_rate_adc = aic23->requested_adc;
	u32 sample_rate_dac = aic23->requested_dac;
	u32 sample_rate = params_rate(params);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		aic23->requested_dac = sample_rate_dac = sample_rate;
		अगर (!sample_rate_adc)
			sample_rate_adc = sample_rate;
	पूर्ण अन्यथा अणु
		aic23->requested_adc = sample_rate_adc = sample_rate;
		अगर (!sample_rate_dac)
			sample_rate_dac = sample_rate;
	पूर्ण
	ret = set_sample_rate_control(component, aic23->mclk, sample_rate_adc,
			sample_rate_dac);
	अगर (ret < 0)
		वापस ret;

	अगरace_reg = snd_soc_component_पढ़ो(component, TLV320AIC23_DIGT_FMT) & ~(0x03 << 2);

	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		अगरace_reg |= (0x01 << 2);
		अवरोध;
	हाल 24:
		अगरace_reg |= (0x02 << 2);
		अवरोध;
	हाल 32:
		अगरace_reg |= (0x03 << 2);
		अवरोध;
	पूर्ण
	snd_soc_component_ग_लिखो(component, TLV320AIC23_DIGT_FMT, अगरace_reg);

	वापस 0;
पूर्ण

अटल पूर्णांक tlv320aic23_pcm_prepare(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	/* set active */
	snd_soc_component_ग_लिखो(component, TLV320AIC23_ACTIVE, 0x0001);

	वापस 0;
पूर्ण

अटल व्योम tlv320aic23_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा aic23 *aic23 = snd_soc_component_get_drvdata(component);

	/* deactivate */
	अगर (!snd_soc_component_active(component)) अणु
		udelay(50);
		snd_soc_component_ग_लिखो(component, TLV320AIC23_ACTIVE, 0x0);
	पूर्ण
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		aic23->requested_dac = 0;
	अन्यथा
		aic23->requested_adc = 0;
पूर्ण

अटल पूर्णांक tlv320aic23_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 reg;

	reg = snd_soc_component_पढ़ो(component, TLV320AIC23_DIGT);
	अगर (mute)
		reg |= TLV320AIC23_DACM_MUTE;

	अन्यथा
		reg &= ~TLV320AIC23_DACM_MUTE;

	snd_soc_component_ग_लिखो(component, TLV320AIC23_DIGT, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक tlv320aic23_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
				   अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 अगरace_reg;

	अगरace_reg = snd_soc_component_पढ़ो(component, TLV320AIC23_DIGT_FMT) & (~0x03);

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अगरace_reg |= TLV320AIC23_MS_MASTER;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अगरace_reg &= ~TLV320AIC23_MS_MASTER;
		अवरोध;
	शेष:
		वापस -EINVAL;

	पूर्ण

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगरace_reg |= TLV320AIC23_FOR_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		अगरace_reg |= TLV320AIC23_LRP_ON;
		fallthrough;
	हाल SND_SOC_DAIFMT_DSP_B:
		अगरace_reg |= TLV320AIC23_FOR_DSP;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगरace_reg |= TLV320AIC23_FOR_LJUST;
		अवरोध;
	शेष:
		वापस -EINVAL;

	पूर्ण

	snd_soc_component_ग_लिखो(component, TLV320AIC23_DIGT_FMT, अगरace_reg);

	वापस 0;
पूर्ण

अटल पूर्णांक tlv320aic23_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
				      पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा aic23 *aic23 = snd_soc_dai_get_drvdata(codec_dai);
	aic23->mclk = freq;
	वापस 0;
पूर्ण

अटल पूर्णांक tlv320aic23_set_bias_level(काष्ठा snd_soc_component *component,
				      क्रमागत snd_soc_bias_level level)
अणु
	u16 reg = snd_soc_component_पढ़ो(component, TLV320AIC23_PWR) & 0x17f;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		/* vref/mid, osc on, dac unmute */
		reg &= ~(TLV320AIC23_DEVICE_PWR_OFF | TLV320AIC23_OSC_OFF | \
			TLV320AIC23_DAC_OFF);
		snd_soc_component_ग_लिखो(component, TLV320AIC23_PWR, reg);
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		/* everything off except vref/vmid, */
		snd_soc_component_ग_लिखो(component, TLV320AIC23_PWR,
			      reg | TLV320AIC23_CLK_OFF);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		/* everything off, dac mute, inactive */
		snd_soc_component_ग_लिखो(component, TLV320AIC23_ACTIVE, 0x0);
		snd_soc_component_ग_लिखो(component, TLV320AIC23_PWR, 0x1ff);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा AIC23_RATES	SNDRV_PCM_RATE_8000_96000
#घोषणा AIC23_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
			 SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops tlv320aic23_dai_ops = अणु
	.prepare	= tlv320aic23_pcm_prepare,
	.hw_params	= tlv320aic23_hw_params,
	.shutकरोwn	= tlv320aic23_shutकरोwn,
	.mute_stream	= tlv320aic23_mute,
	.set_fmt	= tlv320aic23_set_dai_fmt,
	.set_sysclk	= tlv320aic23_set_dai_sysclk,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver tlv320aic23_dai = अणु
	.name = "tlv320aic23-hifi",
	.playback = अणु
		     .stream_name = "Playback",
		     .channels_min = 2,
		     .channels_max = 2,
		     .rates = AIC23_RATES,
		     .क्रमmats = AIC23_FORMATS,पूर्ण,
	.capture = अणु
		    .stream_name = "Capture",
		    .channels_min = 2,
		    .channels_max = 2,
		    .rates = AIC23_RATES,
		    .क्रमmats = AIC23_FORMATS,पूर्ण,
	.ops = &tlv320aic23_dai_ops,
पूर्ण;

अटल पूर्णांक tlv320aic23_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा aic23 *aic23 = snd_soc_component_get_drvdata(component);
	regcache_mark_dirty(aic23->regmap);
	regcache_sync(aic23->regmap);

	वापस 0;
पूर्ण

अटल पूर्णांक tlv320aic23_component_probe(काष्ठा snd_soc_component *component)
अणु
	/* Reset codec */
	snd_soc_component_ग_लिखो(component, TLV320AIC23_RESET, 0);

	snd_soc_component_ग_लिखो(component, TLV320AIC23_DIGT, TLV320AIC23_DEEMP_44K);

	/* Unmute input */
	snd_soc_component_update_bits(component, TLV320AIC23_LINVOL,
			    TLV320AIC23_LIM_MUTED, TLV320AIC23_LRS_ENABLED);

	snd_soc_component_update_bits(component, TLV320AIC23_RINVOL,
			    TLV320AIC23_LIM_MUTED, TLV320AIC23_LRS_ENABLED);

	snd_soc_component_update_bits(component, TLV320AIC23_ANLG,
			    TLV320AIC23_BYPASS_ON | TLV320AIC23_MICM_MUTED,
			    0);

	/* Default output volume */
	snd_soc_component_ग_लिखो(component, TLV320AIC23_LCHNVOL,
		      TLV320AIC23_DEFAULT_OUT_VOL & TLV320AIC23_OUT_VOL_MASK);
	snd_soc_component_ग_लिखो(component, TLV320AIC23_RCHNVOL,
		      TLV320AIC23_DEFAULT_OUT_VOL & TLV320AIC23_OUT_VOL_MASK);

	snd_soc_component_ग_लिखो(component, TLV320AIC23_ACTIVE, 0x1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_tlv320aic23 = अणु
	.probe			= tlv320aic23_component_probe,
	.resume			= tlv320aic23_resume,
	.set_bias_level		= tlv320aic23_set_bias_level,
	.controls		= tlv320aic23_snd_controls,
	.num_controls		= ARRAY_SIZE(tlv320aic23_snd_controls),
	.dapm_widमाला_लो		= tlv320aic23_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(tlv320aic23_dapm_widमाला_लो),
	.dapm_routes		= tlv320aic23_पूर्णांकercon,
	.num_dapm_routes	= ARRAY_SIZE(tlv320aic23_पूर्णांकercon),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

पूर्णांक tlv320aic23_probe(काष्ठा device *dev, काष्ठा regmap *regmap)
अणु
	काष्ठा aic23 *aic23;

	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	aic23 = devm_kzalloc(dev, माप(काष्ठा aic23), GFP_KERNEL);
	अगर (aic23 == शून्य)
		वापस -ENOMEM;

	aic23->regmap = regmap;

	dev_set_drvdata(dev, aic23);

	वापस devm_snd_soc_रेजिस्टर_component(dev,
				      &soc_component_dev_tlv320aic23,
				      &tlv320aic23_dai, 1);
पूर्ण
EXPORT_SYMBOL(tlv320aic23_probe);

MODULE_DESCRIPTION("ASoC TLV320AIC23 codec driver");
MODULE_AUTHOR("Arun KS <arunks@mistralsolutions.com>");
MODULE_LICENSE("GPL");
