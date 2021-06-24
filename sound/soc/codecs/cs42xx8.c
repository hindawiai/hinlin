<शैली गुरु>
/*
 * Cirrus Logic CS42448/CS42888 Audio CODEC Digital Audio Interface (DAI) driver
 *
 * Copyright (C) 2014 Freescale Semiconductor, Inc.
 *
 * Author: Nicolin Chen <Guangyu.Chen@मुक्तscale.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#समावेश "cs42xx8.h"

#घोषणा CS42XX8_NUM_SUPPLIES 4
अटल स्थिर अक्षर *स्थिर cs42xx8_supply_names[CS42XX8_NUM_SUPPLIES] = अणु
	"VA",
	"VD",
	"VLS",
	"VLC",
पूर्ण;

#घोषणा CS42XX8_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE | \
			 SNDRV_PCM_FMTBIT_S20_3LE | \
			 SNDRV_PCM_FMTBIT_S24_LE | \
			 SNDRV_PCM_FMTBIT_S32_LE)

/* codec निजी data */
काष्ठा cs42xx8_priv अणु
	काष्ठा regulator_bulk_data supplies[CS42XX8_NUM_SUPPLIES];
	स्थिर काष्ठा cs42xx8_driver_data *drvdata;
	काष्ठा regmap *regmap;
	काष्ठा clk *clk;

	bool slave_mode;
	अचिन्हित दीर्घ sysclk;
	u32 tx_channels;
	काष्ठा gpio_desc *gpiod_reset;
	u32 rate[2];
पूर्ण;

/* -127.5dB to 0dB with step of 0.5dB */
अटल स्थिर DECLARE_TLV_DB_SCALE(dac_tlv, -12750, 50, 1);
/* -64dB to 24dB with step of 0.5dB */
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_tlv, -6400, 50, 0);

अटल स्थिर अक्षर *स्थिर cs42xx8_adc_single[] = अणु "Differential", "Single-Ended" पूर्ण;
अटल स्थिर अक्षर *स्थिर cs42xx8_szc[] = अणु "Immediate Change", "Zero Cross",
					"Soft Ramp", "Soft Ramp on Zero Cross" पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत adc1_single_क्रमागत =
	SOC_ENUM_SINGLE(CS42XX8_ADCCTL, 4, 2, cs42xx8_adc_single);
अटल स्थिर काष्ठा soc_क्रमागत adc2_single_क्रमागत =
	SOC_ENUM_SINGLE(CS42XX8_ADCCTL, 3, 2, cs42xx8_adc_single);
अटल स्थिर काष्ठा soc_क्रमागत adc3_single_क्रमागत =
	SOC_ENUM_SINGLE(CS42XX8_ADCCTL, 2, 2, cs42xx8_adc_single);
अटल स्थिर काष्ठा soc_क्रमागत dac_szc_क्रमागत =
	SOC_ENUM_SINGLE(CS42XX8_TXCTL, 5, 4, cs42xx8_szc);
अटल स्थिर काष्ठा soc_क्रमागत adc_szc_क्रमागत =
	SOC_ENUM_SINGLE(CS42XX8_TXCTL, 0, 4, cs42xx8_szc);

अटल स्थिर काष्ठा snd_kcontrol_new cs42xx8_snd_controls[] = अणु
	SOC_DOUBLE_R_TLV("DAC1 Playback Volume", CS42XX8_VOLAOUT1,
			 CS42XX8_VOLAOUT2, 0, 0xff, 1, dac_tlv),
	SOC_DOUBLE_R_TLV("DAC2 Playback Volume", CS42XX8_VOLAOUT3,
			 CS42XX8_VOLAOUT4, 0, 0xff, 1, dac_tlv),
	SOC_DOUBLE_R_TLV("DAC3 Playback Volume", CS42XX8_VOLAOUT5,
			 CS42XX8_VOLAOUT6, 0, 0xff, 1, dac_tlv),
	SOC_DOUBLE_R_TLV("DAC4 Playback Volume", CS42XX8_VOLAOUT7,
			 CS42XX8_VOLAOUT8, 0, 0xff, 1, dac_tlv),
	SOC_DOUBLE_R_S_TLV("ADC1 Capture Volume", CS42XX8_VOLAIN1,
			   CS42XX8_VOLAIN2, 0, -0x80, 0x30, 7, 0, adc_tlv),
	SOC_DOUBLE_R_S_TLV("ADC2 Capture Volume", CS42XX8_VOLAIN3,
			   CS42XX8_VOLAIN4, 0, -0x80, 0x30, 7, 0, adc_tlv),
	SOC_DOUBLE("DAC1 Invert Switch", CS42XX8_DACINV, 0, 1, 1, 0),
	SOC_DOUBLE("DAC2 Invert Switch", CS42XX8_DACINV, 2, 3, 1, 0),
	SOC_DOUBLE("DAC3 Invert Switch", CS42XX8_DACINV, 4, 5, 1, 0),
	SOC_DOUBLE("DAC4 Invert Switch", CS42XX8_DACINV, 6, 7, 1, 0),
	SOC_DOUBLE("ADC1 Invert Switch", CS42XX8_ADCINV, 0, 1, 1, 0),
	SOC_DOUBLE("ADC2 Invert Switch", CS42XX8_ADCINV, 2, 3, 1, 0),
	SOC_SINGLE("ADC High-Pass Filter Switch", CS42XX8_ADCCTL, 7, 1, 1),
	SOC_SINGLE("DAC De-emphasis Switch", CS42XX8_ADCCTL, 5, 1, 0),
	SOC_ENUM("ADC1 Single Ended Mode Switch", adc1_single_क्रमागत),
	SOC_ENUM("ADC2 Single Ended Mode Switch", adc2_single_क्रमागत),
	SOC_SINGLE("DAC Single Volume Control Switch", CS42XX8_TXCTL, 7, 1, 0),
	SOC_ENUM("DAC Soft Ramp & Zero Cross Control Switch", dac_szc_क्रमागत),
	SOC_SINGLE("DAC Auto Mute Switch", CS42XX8_TXCTL, 4, 1, 0),
	SOC_SINGLE("Mute ADC Serial Port Switch", CS42XX8_TXCTL, 3, 1, 0),
	SOC_SINGLE("ADC Single Volume Control Switch", CS42XX8_TXCTL, 2, 1, 0),
	SOC_ENUM("ADC Soft Ramp & Zero Cross Control Switch", adc_szc_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new cs42xx8_adc3_snd_controls[] = अणु
	SOC_DOUBLE_R_S_TLV("ADC3 Capture Volume", CS42XX8_VOLAIN5,
			   CS42XX8_VOLAIN6, 0, -0x80, 0x30, 7, 0, adc_tlv),
	SOC_DOUBLE("ADC3 Invert Switch", CS42XX8_ADCINV, 4, 5, 1, 0),
	SOC_ENUM("ADC3 Single Ended Mode Switch", adc3_single_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget cs42xx8_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("DAC1", "Playback", CS42XX8_PWRCTL, 1, 1),
	SND_SOC_DAPM_DAC("DAC2", "Playback", CS42XX8_PWRCTL, 2, 1),
	SND_SOC_DAPM_DAC("DAC3", "Playback", CS42XX8_PWRCTL, 3, 1),
	SND_SOC_DAPM_DAC("DAC4", "Playback", CS42XX8_PWRCTL, 4, 1),

	SND_SOC_DAPM_OUTPUT("AOUT1L"),
	SND_SOC_DAPM_OUTPUT("AOUT1R"),
	SND_SOC_DAPM_OUTPUT("AOUT2L"),
	SND_SOC_DAPM_OUTPUT("AOUT2R"),
	SND_SOC_DAPM_OUTPUT("AOUT3L"),
	SND_SOC_DAPM_OUTPUT("AOUT3R"),
	SND_SOC_DAPM_OUTPUT("AOUT4L"),
	SND_SOC_DAPM_OUTPUT("AOUT4R"),

	SND_SOC_DAPM_ADC("ADC1", "Capture", CS42XX8_PWRCTL, 5, 1),
	SND_SOC_DAPM_ADC("ADC2", "Capture", CS42XX8_PWRCTL, 6, 1),

	SND_SOC_DAPM_INPUT("AIN1L"),
	SND_SOC_DAPM_INPUT("AIN1R"),
	SND_SOC_DAPM_INPUT("AIN2L"),
	SND_SOC_DAPM_INPUT("AIN2R"),

	SND_SOC_DAPM_SUPPLY("PWR", CS42XX8_PWRCTL, 0, 1, शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget cs42xx8_adc3_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_ADC("ADC3", "Capture", CS42XX8_PWRCTL, 7, 1),

	SND_SOC_DAPM_INPUT("AIN3L"),
	SND_SOC_DAPM_INPUT("AIN3R"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cs42xx8_dapm_routes[] = अणु
	/* Playback */
	अणु "AOUT1L", शून्य, "DAC1" पूर्ण,
	अणु "AOUT1R", शून्य, "DAC1" पूर्ण,
	अणु "DAC1", शून्य, "PWR" पूर्ण,

	अणु "AOUT2L", शून्य, "DAC2" पूर्ण,
	अणु "AOUT2R", शून्य, "DAC2" पूर्ण,
	अणु "DAC2", शून्य, "PWR" पूर्ण,

	अणु "AOUT3L", शून्य, "DAC3" पूर्ण,
	अणु "AOUT3R", शून्य, "DAC3" पूर्ण,
	अणु "DAC3", शून्य, "PWR" पूर्ण,

	अणु "AOUT4L", शून्य, "DAC4" पूर्ण,
	अणु "AOUT4R", शून्य, "DAC4" पूर्ण,
	अणु "DAC4", शून्य, "PWR" पूर्ण,

	/* Capture */
	अणु "ADC1", शून्य, "AIN1L" पूर्ण,
	अणु "ADC1", शून्य, "AIN1R" पूर्ण,
	अणु "ADC1", शून्य, "PWR" पूर्ण,

	अणु "ADC2", शून्य, "AIN2L" पूर्ण,
	अणु "ADC2", शून्य, "AIN2R" पूर्ण,
	अणु "ADC2", शून्य, "PWR" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cs42xx8_adc3_dapm_routes[] = अणु
	/* Capture */
	अणु "ADC3", शून्य, "AIN3L" पूर्ण,
	अणु "ADC3", शून्य, "AIN3R" पूर्ण,
	अणु "ADC3", शून्य, "PWR" पूर्ण,
पूर्ण;

काष्ठा cs42xx8_ratios अणु
	अचिन्हित पूर्णांक mfreq;
	अचिन्हित पूर्णांक min_mclk;
	अचिन्हित पूर्णांक max_mclk;
	अचिन्हित पूर्णांक ratio[3];
पूर्ण;

/*
 * According to reference mannual, define the cs42xx8_ratio काष्ठा
 * MFreq2 | MFreq1 | MFreq0 |     Description     | SSM | DSM | QSM |
 * 0      | 0      | 0      |1.029MHz to 12.8MHz  | 256 | 128 |  64 |
 * 0      | 0      | 1      |1.536MHz to 19.2MHz  | 384 | 192 |  96 |
 * 0      | 1      | 0      |2.048MHz to 25.6MHz  | 512 | 256 | 128 |
 * 0      | 1      | 1      |3.072MHz to 38.4MHz  | 768 | 384 | 192 |
 * 1      | x      | x      |4.096MHz to 51.2MHz  |1024 | 512 | 256 |
 */
अटल स्थिर काष्ठा cs42xx8_ratios cs42xx8_ratios[] = अणु
	अणु 0, 1029000, 12800000, अणु256, 128, 64पूर्ण पूर्ण,
	अणु 2, 1536000, 19200000, अणु384, 192, 96पूर्ण पूर्ण,
	अणु 4, 2048000, 25600000, अणु512, 256, 128पूर्ण पूर्ण,
	अणु 6, 3072000, 38400000, अणु768, 384, 192पूर्ण पूर्ण,
	अणु 8, 4096000, 51200000, अणु1024, 512, 256पूर्ण पूर्ण,
पूर्ण;

अटल पूर्णांक cs42xx8_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
				  पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cs42xx8_priv *cs42xx8 = snd_soc_component_get_drvdata(component);

	cs42xx8->sysclk = freq;

	वापस 0;
पूर्ण

अटल पूर्णांक cs42xx8_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
			       अचिन्हित पूर्णांक क्रमmat)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cs42xx8_priv *cs42xx8 = snd_soc_component_get_drvdata(component);
	u32 val;

	/* Set DAI क्रमmat */
	चयन (क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_LEFT_J:
		val = CS42XX8_INTF_DAC_DIF_LEFTJ | CS42XX8_INTF_ADC_DIF_LEFTJ;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		val = CS42XX8_INTF_DAC_DIF_I2S | CS42XX8_INTF_ADC_DIF_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		val = CS42XX8_INTF_DAC_DIF_RIGHTJ | CS42XX8_INTF_ADC_DIF_RIGHTJ;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		val = CS42XX8_INTF_DAC_DIF_TDM | CS42XX8_INTF_ADC_DIF_TDM;
		अवरोध;
	शेष:
		dev_err(component->dev, "unsupported dai format\n");
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(cs42xx8->regmap, CS42XX8_INTF,
			   CS42XX8_INTF_DAC_DIF_MASK |
			   CS42XX8_INTF_ADC_DIF_MASK, val);

	/* Set master/slave audio पूर्णांकerface */
	चयन (क्रमmat & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		cs42xx8->slave_mode = true;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		cs42xx8->slave_mode = false;
		अवरोध;
	शेष:
		dev_err(component->dev, "unsupported master/slave mode\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs42xx8_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs42xx8_priv *cs42xx8 = snd_soc_component_get_drvdata(component);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	u32 ratio[2];
	u32 rate[2];
	u32 fm[2];
	u32 i, val, mask;
	bool condition1, condition2;

	अगर (tx)
		cs42xx8->tx_channels = params_channels(params);

	rate[tx]  = params_rate(params);
	rate[!tx] = cs42xx8->rate[!tx];

	ratio[tx] = rate[tx] > 0 ? cs42xx8->sysclk / rate[tx] : 0;
	ratio[!tx] = rate[!tx] > 0 ? cs42xx8->sysclk / rate[!tx] : 0;

	/* Get functional mode क्रम tx and rx according to rate */
	क्रम (i = 0; i < 2; i++) अणु
		अगर (cs42xx8->slave_mode) अणु
			fm[i] = CS42XX8_FM_AUTO;
		पूर्ण अन्यथा अणु
			अगर (rate[i] < 50000) अणु
				fm[i] = CS42XX8_FM_SINGLE;
			पूर्ण अन्यथा अगर (rate[i] > 50000 && rate[i] < 100000) अणु
				fm[i] = CS42XX8_FM_DOUBLE;
			पूर्ण अन्यथा अगर (rate[i] > 100000 && rate[i] < 200000) अणु
				fm[i] = CS42XX8_FM_QUAD;
			पूर्ण अन्यथा अणु
				dev_err(component->dev,
					"unsupported sample rate\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(cs42xx8_ratios); i++) अणु
		/* Is the ratio[tx] valid ? */
		condition1 = ((fm[tx] == CS42XX8_FM_AUTO) ?
			(cs42xx8_ratios[i].ratio[0] == ratio[tx] ||
			cs42xx8_ratios[i].ratio[1] == ratio[tx] ||
			cs42xx8_ratios[i].ratio[2] == ratio[tx]) :
			(cs42xx8_ratios[i].ratio[fm[tx]] == ratio[tx])) &&
			cs42xx8->sysclk >= cs42xx8_ratios[i].min_mclk &&
			cs42xx8->sysclk <= cs42xx8_ratios[i].max_mclk;

		अगर (!ratio[tx])
			condition1 = true;

		/* Is the ratio[!tx] valid ? */
		condition2 = ((fm[!tx] == CS42XX8_FM_AUTO) ?
			(cs42xx8_ratios[i].ratio[0] == ratio[!tx] ||
			cs42xx8_ratios[i].ratio[1] == ratio[!tx] ||
			cs42xx8_ratios[i].ratio[2] == ratio[!tx]) :
			(cs42xx8_ratios[i].ratio[fm[!tx]] == ratio[!tx]));

		अगर (!ratio[!tx])
			condition2 = true;

		/*
		 * Both ratio[tx] and ratio[!tx] is valid, then we get
		 * a proper MFreq.
		 */
		अगर (condition1 && condition2)
			अवरोध;
	पूर्ण

	अगर (i == ARRAY_SIZE(cs42xx8_ratios)) अणु
		dev_err(component->dev, "unsupported sysclk ratio\n");
		वापस -EINVAL;
	पूर्ण

	cs42xx8->rate[tx] = params_rate(params);

	mask = CS42XX8_FUNCMOD_MFREQ_MASK;
	val = cs42xx8_ratios[i].mfreq;

	regmap_update_bits(cs42xx8->regmap, CS42XX8_FUNCMOD,
			   CS42XX8_FUNCMOD_xC_FM_MASK(tx) | mask,
			   CS42XX8_FUNCMOD_xC_FM(tx, fm[tx]) | val);

	वापस 0;
पूर्ण

अटल पूर्णांक cs42xx8_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs42xx8_priv *cs42xx8 = snd_soc_component_get_drvdata(component);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;

	/* Clear stored rate */
	cs42xx8->rate[tx] = 0;

	regmap_update_bits(cs42xx8->regmap, CS42XX8_FUNCMOD,
			   CS42XX8_FUNCMOD_xC_FM_MASK(tx),
			   CS42XX8_FUNCMOD_xC_FM(tx, CS42XX8_FM_AUTO));
	वापस 0;
पूर्ण

अटल पूर्णांक cs42xx8_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs42xx8_priv *cs42xx8 = snd_soc_component_get_drvdata(component);
	u8 dac_unmute = cs42xx8->tx_channels ?
		        ~((0x1 << cs42xx8->tx_channels) - 1) : 0;

	regmap_ग_लिखो(cs42xx8->regmap, CS42XX8_DACMUTE,
		     mute ? CS42XX8_DACMUTE_ALL : dac_unmute);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops cs42xx8_dai_ops = अणु
	.set_fmt	= cs42xx8_set_dai_fmt,
	.set_sysclk	= cs42xx8_set_dai_sysclk,
	.hw_params	= cs42xx8_hw_params,
	.hw_मुक्त	= cs42xx8_hw_मुक्त,
	.mute_stream	= cs42xx8_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver cs42xx8_dai = अणु
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = CS42XX8_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.rates = SNDRV_PCM_RATE_8000_192000,
		.क्रमmats = CS42XX8_FORMATS,
	पूर्ण,
	.ops = &cs42xx8_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष cs42xx8_reg[] = अणु
	अणु 0x02, 0x00 पूर्ण,   /* Power Control */
	अणु 0x03, 0xF0 पूर्ण,   /* Functional Mode */
	अणु 0x04, 0x46 पूर्ण,   /* Interface Formats */
	अणु 0x05, 0x00 पूर्ण,   /* ADC Control & DAC De-Emphasis */
	अणु 0x06, 0x10 पूर्ण,   /* Transition Control */
	अणु 0x07, 0x00 पूर्ण,   /* DAC Channel Mute */
	अणु 0x08, 0x00 पूर्ण,   /* Volume Control AOUT1 */
	अणु 0x09, 0x00 पूर्ण,   /* Volume Control AOUT2 */
	अणु 0x0a, 0x00 पूर्ण,   /* Volume Control AOUT3 */
	अणु 0x0b, 0x00 पूर्ण,   /* Volume Control AOUT4 */
	अणु 0x0c, 0x00 पूर्ण,   /* Volume Control AOUT5 */
	अणु 0x0d, 0x00 पूर्ण,   /* Volume Control AOUT6 */
	अणु 0x0e, 0x00 पूर्ण,   /* Volume Control AOUT7 */
	अणु 0x0f, 0x00 पूर्ण,   /* Volume Control AOUT8 */
	अणु 0x10, 0x00 पूर्ण,   /* DAC Channel Invert */
	अणु 0x11, 0x00 पूर्ण,   /* Volume Control AIN1 */
	अणु 0x12, 0x00 पूर्ण,   /* Volume Control AIN2 */
	अणु 0x13, 0x00 पूर्ण,   /* Volume Control AIN3 */
	अणु 0x14, 0x00 पूर्ण,   /* Volume Control AIN4 */
	अणु 0x15, 0x00 पूर्ण,   /* Volume Control AIN5 */
	अणु 0x16, 0x00 पूर्ण,   /* Volume Control AIN6 */
	अणु 0x17, 0x00 पूर्ण,   /* ADC Channel Invert */
	अणु 0x18, 0x00 पूर्ण,   /* Status Control */
	अणु 0x1a, 0x00 पूर्ण,   /* Status Mask */
	अणु 0x1b, 0x00 पूर्ण,   /* MUTEC Pin Control */
पूर्ण;

अटल bool cs42xx8_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS42XX8_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cs42xx8_ग_लिखोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS42XX8_CHIPID:
	हाल CS42XX8_STATUS:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

स्थिर काष्ठा regmap_config cs42xx8_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = CS42XX8_LASTREG,
	.reg_शेषs = cs42xx8_reg,
	.num_reg_शेषs = ARRAY_SIZE(cs42xx8_reg),
	.अस्थिर_reg = cs42xx8_अस्थिर_रेजिस्टर,
	.ग_लिखोable_reg = cs42xx8_ग_लिखोable_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;
EXPORT_SYMBOL_GPL(cs42xx8_regmap_config);

अटल पूर्णांक cs42xx8_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cs42xx8_priv *cs42xx8 = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	चयन (cs42xx8->drvdata->num_adcs) अणु
	हाल 3:
		snd_soc_add_component_controls(component, cs42xx8_adc3_snd_controls,
					ARRAY_SIZE(cs42xx8_adc3_snd_controls));
		snd_soc_dapm_new_controls(dapm, cs42xx8_adc3_dapm_widमाला_लो,
					ARRAY_SIZE(cs42xx8_adc3_dapm_widमाला_लो));
		snd_soc_dapm_add_routes(dapm, cs42xx8_adc3_dapm_routes,
					ARRAY_SIZE(cs42xx8_adc3_dapm_routes));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Mute all DAC channels */
	regmap_ग_लिखो(cs42xx8->regmap, CS42XX8_DACMUTE, CS42XX8_DACMUTE_ALL);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver cs42xx8_driver = अणु
	.probe			= cs42xx8_component_probe,
	.controls		= cs42xx8_snd_controls,
	.num_controls		= ARRAY_SIZE(cs42xx8_snd_controls),
	.dapm_widमाला_लो		= cs42xx8_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(cs42xx8_dapm_widमाला_लो),
	.dapm_routes		= cs42xx8_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(cs42xx8_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

स्थिर काष्ठा cs42xx8_driver_data cs42448_data = अणु
	.name = "cs42448",
	.num_adcs = 3,
पूर्ण;
EXPORT_SYMBOL_GPL(cs42448_data);

स्थिर काष्ठा cs42xx8_driver_data cs42888_data = अणु
	.name = "cs42888",
	.num_adcs = 2,
पूर्ण;
EXPORT_SYMBOL_GPL(cs42888_data);

स्थिर काष्ठा of_device_id cs42xx8_of_match[] = अणु
	अणु .compatible = "cirrus,cs42448", .data = &cs42448_data, पूर्ण,
	अणु .compatible = "cirrus,cs42888", .data = &cs42888_data, पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cs42xx8_of_match);
EXPORT_SYMBOL_GPL(cs42xx8_of_match);

पूर्णांक cs42xx8_probe(काष्ठा device *dev, काष्ठा regmap *regmap)
अणु
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा cs42xx8_priv *cs42xx8;
	पूर्णांक ret, val, i;

	अगर (IS_ERR(regmap)) अणु
		ret = PTR_ERR(regmap);
		dev_err(dev, "failed to allocate regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	cs42xx8 = devm_kzalloc(dev, माप(*cs42xx8), GFP_KERNEL);
	अगर (cs42xx8 == शून्य)
		वापस -ENOMEM;

	cs42xx8->regmap = regmap;
	dev_set_drvdata(dev, cs42xx8);

	of_id = of_match_device(cs42xx8_of_match, dev);
	अगर (of_id)
		cs42xx8->drvdata = of_id->data;

	अगर (!cs42xx8->drvdata) अणु
		dev_err(dev, "failed to find driver data\n");
		वापस -EINVAL;
	पूर्ण

	cs42xx8->gpiod_reset = devm_gpiod_get_optional(dev, "reset",
							GPIOD_OUT_HIGH);
	अगर (IS_ERR(cs42xx8->gpiod_reset))
		वापस PTR_ERR(cs42xx8->gpiod_reset);

	gpiod_set_value_cansleep(cs42xx8->gpiod_reset, 0);

	cs42xx8->clk = devm_clk_get(dev, "mclk");
	अगर (IS_ERR(cs42xx8->clk)) अणु
		dev_err(dev, "failed to get the clock: %ld\n",
				PTR_ERR(cs42xx8->clk));
		वापस -EINVAL;
	पूर्ण

	cs42xx8->sysclk = clk_get_rate(cs42xx8->clk);

	क्रम (i = 0; i < ARRAY_SIZE(cs42xx8->supplies); i++)
		cs42xx8->supplies[i].supply = cs42xx8_supply_names[i];

	ret = devm_regulator_bulk_get(dev,
			ARRAY_SIZE(cs42xx8->supplies), cs42xx8->supplies);
	अगर (ret) अणु
		dev_err(dev, "failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(cs42xx8->supplies),
				    cs42xx8->supplies);
	अगर (ret) अणु
		dev_err(dev, "failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Make sure hardware reset करोne */
	msleep(5);

	/* Validate the chip ID */
	ret = regmap_पढ़ो(cs42xx8->regmap, CS42XX8_CHIPID, &val);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to get device ID, ret = %d", ret);
		जाओ err_enable;
	पूर्ण

	/* The top four bits of the chip ID should be 0000 */
	अगर (((val & CS42XX8_CHIPID_CHIP_ID_MASK) >> 4) != 0x00) अणु
		dev_err(dev, "unmatched chip ID: %d\n",
			(val & CS42XX8_CHIPID_CHIP_ID_MASK) >> 4);
		ret = -EINVAL;
		जाओ err_enable;
	पूर्ण

	dev_info(dev, "found device, revision %X\n",
			val & CS42XX8_CHIPID_REV_ID_MASK);

	cs42xx8_dai.name = cs42xx8->drvdata->name;

	/* Each adc supports stereo input */
	cs42xx8_dai.capture.channels_max = cs42xx8->drvdata->num_adcs * 2;

	ret = devm_snd_soc_रेजिस्टर_component(dev, &cs42xx8_driver, &cs42xx8_dai, 1);
	अगर (ret) अणु
		dev_err(dev, "failed to register component:%d\n", ret);
		जाओ err_enable;
	पूर्ण

	regcache_cache_only(cs42xx8->regmap, true);

err_enable:
	regulator_bulk_disable(ARRAY_SIZE(cs42xx8->supplies),
			       cs42xx8->supplies);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(cs42xx8_probe);

#अगर_घोषित CONFIG_PM
अटल पूर्णांक cs42xx8_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा cs42xx8_priv *cs42xx8 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(cs42xx8->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to enable mclk: %d\n", ret);
		वापस ret;
	पूर्ण

	gpiod_set_value_cansleep(cs42xx8->gpiod_reset, 0);

	ret = regulator_bulk_enable(ARRAY_SIZE(cs42xx8->supplies),
				    cs42xx8->supplies);
	अगर (ret) अणु
		dev_err(dev, "failed to enable supplies: %d\n", ret);
		जाओ err_clk;
	पूर्ण

	/* Make sure hardware reset करोne */
	msleep(5);

	regcache_cache_only(cs42xx8->regmap, false);
	regcache_mark_dirty(cs42xx8->regmap);

	ret = regcache_sync(cs42xx8->regmap);
	अगर (ret) अणु
		dev_err(dev, "failed to sync regmap: %d\n", ret);
		जाओ err_bulk;
	पूर्ण

	वापस 0;

err_bulk:
	regulator_bulk_disable(ARRAY_SIZE(cs42xx8->supplies),
			       cs42xx8->supplies);
err_clk:
	clk_disable_unprepare(cs42xx8->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक cs42xx8_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा cs42xx8_priv *cs42xx8 = dev_get_drvdata(dev);

	regcache_cache_only(cs42xx8->regmap, true);

	regulator_bulk_disable(ARRAY_SIZE(cs42xx8->supplies),
			       cs42xx8->supplies);

	gpiod_set_value_cansleep(cs42xx8->gpiod_reset, 1);

	clk_disable_unprepare(cs42xx8->clk);

	वापस 0;
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा dev_pm_ops cs42xx8_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(cs42xx8_runसमय_suspend, cs42xx8_runसमय_resume, शून्य)
पूर्ण;
EXPORT_SYMBOL_GPL(cs42xx8_pm);

MODULE_DESCRIPTION("Cirrus Logic CS42448/CS42888 ALSA SoC Codec Driver");
MODULE_AUTHOR("Freescale Semiconductor, Inc.");
MODULE_LICENSE("GPL");
