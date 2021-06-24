<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// cs4234.c -- ALSA SoC CS4234 driver
//
// Copyright (C) 2020 Cirrus Logic, Inc. and
//                    Cirrus Logic International Semiconductor Ltd.
//

#समावेश <linux/clk.h>
#समावेश <linux/completion.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <linux/workqueue.h>

#समावेश "cs4234.h"

काष्ठा cs4234 अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा regulator_bulk_data core_supplies[2];
	पूर्णांक num_core_supplies;
	काष्ठा completion vq_ramp_complete;
	काष्ठा delayed_work vq_ramp_delay;
	काष्ठा clk *mclk;
	अचिन्हित दीर्घ mclk_rate;
	अचिन्हित दीर्घ lrclk_rate;
	अचिन्हित पूर्णांक क्रमmat;
	काष्ठा snd_ratnum rate_भागiders[2];
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratnums rate_स्थिरraपूर्णांक;
पूर्ण;

/* -89.92dB to +6.02dB with step of 0.38dB */
अटल स्थिर DECLARE_TLV_DB_SCALE(dac_tlv, -8992, 38, 0);

अटल स्थिर अक्षर * स्थिर cs4234_dac14_delay_text[] = अणु
	  "0us", "100us", "150us", "200us", "225us", "250us", "275us", "300us",
	"325us", "350us", "375us", "400us", "425us", "450us", "475us", "500us",
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(cs4234_dac14_group_delay, CS4234_TPS_CTRL,
			    CS4234_GRP_DELAY_SHIFT, cs4234_dac14_delay_text);

अटल स्थिर अक्षर * स्थिर cs4234_noise_gate_text[] = अणु
	"72dB",  "78dB",  "84dB", "90dB", "96dB", "102dB", "138dB", "Disabled",
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(cs4234_ll_noise_gate, CS4234_LOW_LAT_CTRL1,
			    CS4234_LL_NG_SHIFT, cs4234_noise_gate_text);
अटल SOC_ENUM_SINGLE_DECL(cs4234_dac14_noise_gate, CS4234_DAC_CTRL1,
			    CS4234_DAC14_NG_SHIFT, cs4234_noise_gate_text);
अटल SOC_ENUM_SINGLE_DECL(cs4234_dac5_noise_gate, CS4234_DAC_CTRL2,
			    CS4234_DAC5_NG_SHIFT, cs4234_noise_gate_text);

अटल स्थिर अक्षर * स्थिर cs4234_dac5_config_fltr_sel_text[] = अणु
	"Interpolation Filter", "Sample and Hold"
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(cs4234_dac5_config_fltr_sel, CS4234_DAC_CTRL1,
			    CS4234_DAC5_CFG_FLTR_SHIFT,
			    cs4234_dac5_config_fltr_sel_text);

अटल स्थिर अक्षर * स्थिर cs4234_mute_delay_text[] = अणु
	"1x",  "4x",  "16x", "64x",
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(cs4234_mute_delay, CS4234_VOLUME_MODE,
			    CS4234_MUTE_DELAY_SHIFT, cs4234_mute_delay_text);

अटल स्थिर अक्षर * स्थिर cs4234_minmax_delay_text[] = अणु
	"1x",  "2x",  "4x", "8x", "16x",  "32x", "64x", "128x",
पूर्ण;
अटल SOC_ENUM_SINGLE_DECL(cs4234_min_delay, CS4234_VOLUME_MODE,
			    CS4234_MIN_DELAY_SHIFT, cs4234_minmax_delay_text);
अटल SOC_ENUM_SINGLE_DECL(cs4234_max_delay, CS4234_VOLUME_MODE,
			    CS4234_MAX_DELAY_SHIFT, cs4234_minmax_delay_text);

अटल पूर्णांक cs4234_dac14_grp_delay_put(काष्ठा snd_kcontrol *kctrl,
				      काष्ठा snd_ctl_elem_value *uctrl)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kctrl);
	काष्ठा cs4234 *cs4234 = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	अचिन्हित पूर्णांक val = 0;
	पूर्णांक ret = 0;

	snd_soc_dapm_mutex_lock(dapm);

	regmap_पढ़ो(cs4234->regmap, CS4234_ADC_CTRL2, &val);
	अगर ((val & 0x0F) != 0x0F) अणु // are all the ADCs घातerकरोwn
		ret = -EBUSY;
		dev_err(component->dev, "Can't change group delay while ADC are ON\n");
		जाओ निकास;
	पूर्ण

	regmap_पढ़ो(cs4234->regmap, CS4234_DAC_CTRL4, &val);
	अगर ((val & 0x1F) != 0x1F) अणु // are all the DACs घातerकरोwn
		ret = -EBUSY;
		dev_err(component->dev, "Can't change group delay while DAC are ON\n");
		जाओ निकास;
	पूर्ण

	ret = snd_soc_put_क्रमागत_द्विगुन(kctrl, uctrl);
निकास:
	snd_soc_dapm_mutex_unlock(dapm);

	वापस ret;
पूर्ण

अटल व्योम cs4234_vq_ramp_करोne(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *dw = to_delayed_work(work);
	काष्ठा cs4234 *cs4234 = container_of(dw, काष्ठा cs4234, vq_ramp_delay);

	complete_all(&cs4234->vq_ramp_complete);
पूर्ण

अटल पूर्णांक cs4234_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा cs4234 *cs4234 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_PREPARE:
		चयन (snd_soc_component_get_bias_level(component)) अणु
		हाल SND_SOC_BIAS_STANDBY:
			रुको_क्रम_completion(&cs4234->vq_ramp_complete);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget cs4234_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_AIF_IN("SDRX1", शून्य,  0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SDRX2", शून्य,  1, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SDRX3", शून्य,  2, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SDRX4", शून्य,  3, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("SDRX5", शून्य,  4, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_DAC("DAC1", शून्य, CS4234_DAC_CTRL4, CS4234_PDN_DAC1_SHIFT, 1),
	SND_SOC_DAPM_DAC("DAC2", शून्य, CS4234_DAC_CTRL4, CS4234_PDN_DAC2_SHIFT, 1),
	SND_SOC_DAPM_DAC("DAC3", शून्य, CS4234_DAC_CTRL4, CS4234_PDN_DAC3_SHIFT, 1),
	SND_SOC_DAPM_DAC("DAC4", शून्य, CS4234_DAC_CTRL4, CS4234_PDN_DAC4_SHIFT, 1),
	SND_SOC_DAPM_DAC("DAC5", शून्य, CS4234_DAC_CTRL4, CS4234_PDN_DAC5_SHIFT, 1),

	SND_SOC_DAPM_OUTPUT("AOUT1"),
	SND_SOC_DAPM_OUTPUT("AOUT2"),
	SND_SOC_DAPM_OUTPUT("AOUT3"),
	SND_SOC_DAPM_OUTPUT("AOUT4"),
	SND_SOC_DAPM_OUTPUT("AOUT5"),

	SND_SOC_DAPM_INPUT("AIN1"),
	SND_SOC_DAPM_INPUT("AIN2"),
	SND_SOC_DAPM_INPUT("AIN3"),
	SND_SOC_DAPM_INPUT("AIN4"),

	SND_SOC_DAPM_ADC("ADC1", शून्य, CS4234_ADC_CTRL2, CS4234_PDN_ADC1_SHIFT, 1),
	SND_SOC_DAPM_ADC("ADC2", शून्य, CS4234_ADC_CTRL2, CS4234_PDN_ADC2_SHIFT, 1),
	SND_SOC_DAPM_ADC("ADC3", शून्य, CS4234_ADC_CTRL2, CS4234_PDN_ADC3_SHIFT, 1),
	SND_SOC_DAPM_ADC("ADC4", शून्य, CS4234_ADC_CTRL2, CS4234_PDN_ADC4_SHIFT, 1),

	SND_SOC_DAPM_AIF_OUT("SDTX1", शून्य, 0, SND_SOC_NOPM, 0, 1),
	SND_SOC_DAPM_AIF_OUT("SDTX2", शून्य, 1, SND_SOC_NOPM, 0, 1),
	SND_SOC_DAPM_AIF_OUT("SDTX3", शून्य, 2, SND_SOC_NOPM, 0, 1),
	SND_SOC_DAPM_AIF_OUT("SDTX4", शून्य, 3, SND_SOC_NOPM, 0, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cs4234_dapm_routes[] = अणु
	/* Playback */
	अणु "AOUT1", शून्य, "DAC1" पूर्ण,
	अणु "AOUT2", शून्य, "DAC2" पूर्ण,
	अणु "AOUT3", शून्य, "DAC3" पूर्ण,
	अणु "AOUT4", शून्य, "DAC4" पूर्ण,
	अणु "AOUT5", शून्य, "DAC5" पूर्ण,

	अणु "DAC1", शून्य, "SDRX1" पूर्ण,
	अणु "DAC2", शून्य, "SDRX2" पूर्ण,
	अणु "DAC3", शून्य, "SDRX3" पूर्ण,
	अणु "DAC4", शून्य, "SDRX4" पूर्ण,
	अणु "DAC5", शून्य, "SDRX5" पूर्ण,

	अणु "SDRX1", शून्य, "Playback" पूर्ण,
	अणु "SDRX2", शून्य, "Playback" पूर्ण,
	अणु "SDRX3", शून्य, "Playback" पूर्ण,
	अणु "SDRX4", शून्य, "Playback" पूर्ण,
	अणु "SDRX5", शून्य, "Playback" पूर्ण,

	/* Capture */
	अणु "ADC1", शून्य, "AIN1" पूर्ण,
	अणु "ADC2", शून्य, "AIN2" पूर्ण,
	अणु "ADC3", शून्य, "AIN3" पूर्ण,
	अणु "ADC4", शून्य, "AIN4" पूर्ण,

	अणु "SDTX1", शून्य, "ADC1" पूर्ण,
	अणु "SDTX2", शून्य, "ADC2" पूर्ण,
	अणु "SDTX3", शून्य, "ADC3" पूर्ण,
	अणु "SDTX4", शून्य, "ADC4" पूर्ण,

	अणु "Capture", शून्य, "SDTX1" पूर्ण,
	अणु "Capture", शून्य, "SDTX2" पूर्ण,
	अणु "Capture", शून्य, "SDTX3" पूर्ण,
	अणु "Capture", शून्य, "SDTX4" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new cs4234_snd_controls[] = अणु
	SOC_SINGLE_TLV("Master Volume", CS4234_MASTER_VOL, 0, 0xff, 1, dac_tlv),
	SOC_SINGLE_TLV("DAC1 Volume", CS4234_DAC1_VOL, 0, 0xff, 1, dac_tlv),
	SOC_SINGLE_TLV("DAC2 Volume", CS4234_DAC2_VOL, 0, 0xff, 1, dac_tlv),
	SOC_SINGLE_TLV("DAC3 Volume", CS4234_DAC3_VOL, 0, 0xff, 1, dac_tlv),
	SOC_SINGLE_TLV("DAC4 Volume", CS4234_DAC4_VOL, 0, 0xff, 1, dac_tlv),
	SOC_SINGLE_TLV("DAC5 Volume", CS4234_DAC5_VOL, 0, 0xff, 1, dac_tlv),

	SOC_SINGLE("DAC5 Soft Ramp Switch", CS4234_DAC_CTRL3, CS4234_DAC5_ATT_SHIFT, 1, 1),
	SOC_SINGLE("DAC1-4 Soft Ramp Switch", CS4234_DAC_CTRL3, CS4234_DAC14_ATT_SHIFT, 1, 1),

	SOC_SINGLE("ADC HPF Switch", CS4234_ADC_CTRL1, CS4234_ENA_HPF_SHIFT, 1, 0),

	SOC_ENUM_EXT("DAC1-4 Group Delay", cs4234_dac14_group_delay,
		     snd_soc_get_क्रमागत_द्विगुन, cs4234_dac14_grp_delay_put),

	SOC_SINGLE("ADC1 Invert Switch", CS4234_ADC_CTRL1, CS4234_INV_ADC1_SHIFT, 1, 0),
	SOC_SINGLE("ADC2 Invert Switch", CS4234_ADC_CTRL1, CS4234_INV_ADC2_SHIFT, 1, 0),
	SOC_SINGLE("ADC3 Invert Switch", CS4234_ADC_CTRL1, CS4234_INV_ADC3_SHIFT, 1, 0),
	SOC_SINGLE("ADC4 Invert Switch", CS4234_ADC_CTRL1, CS4234_INV_ADC4_SHIFT, 1, 0),

	SOC_SINGLE("DAC1 Invert Switch", CS4234_DAC_CTRL2, CS4234_INV_DAC1_SHIFT, 1, 0),
	SOC_SINGLE("DAC2 Invert Switch", CS4234_DAC_CTRL2, CS4234_INV_DAC2_SHIFT, 1, 0),
	SOC_SINGLE("DAC3 Invert Switch", CS4234_DAC_CTRL2, CS4234_INV_DAC3_SHIFT, 1, 0),
	SOC_SINGLE("DAC4 Invert Switch", CS4234_DAC_CTRL2, CS4234_INV_DAC4_SHIFT, 1, 0),
	SOC_SINGLE("DAC5 Invert Switch", CS4234_DAC_CTRL2, CS4234_INV_DAC5_SHIFT, 1, 0),

	SOC_SINGLE("ADC1 Switch", CS4234_ADC_CTRL2, CS4234_MUTE_ADC1_SHIFT, 1, 1),
	SOC_SINGLE("ADC2 Switch", CS4234_ADC_CTRL2, CS4234_MUTE_ADC2_SHIFT, 1, 1),
	SOC_SINGLE("ADC3 Switch", CS4234_ADC_CTRL2, CS4234_MUTE_ADC3_SHIFT, 1, 1),
	SOC_SINGLE("ADC4 Switch", CS4234_ADC_CTRL2, CS4234_MUTE_ADC4_SHIFT, 1, 1),

	SOC_SINGLE("DAC1 Switch", CS4234_DAC_CTRL3, CS4234_MUTE_DAC1_SHIFT, 1, 1),
	SOC_SINGLE("DAC2 Switch", CS4234_DAC_CTRL3, CS4234_MUTE_DAC2_SHIFT, 1, 1),
	SOC_SINGLE("DAC3 Switch", CS4234_DAC_CTRL3, CS4234_MUTE_DAC3_SHIFT, 1, 1),
	SOC_SINGLE("DAC4 Switch", CS4234_DAC_CTRL3, CS4234_MUTE_DAC4_SHIFT, 1, 1),
	SOC_SINGLE("DAC5 Switch", CS4234_DAC_CTRL3, CS4234_MUTE_DAC5_SHIFT, 1, 1),
	SOC_SINGLE("Low-latency Switch", CS4234_DAC_CTRL3, CS4234_MUTE_LL_SHIFT, 1, 1),

	SOC_SINGLE("DAC1 Low-latency Invert Switch", CS4234_LOW_LAT_CTRL1,
		   CS4234_INV_LL1_SHIFT, 1, 0),
	SOC_SINGLE("DAC2 Low-latency Invert Switch", CS4234_LOW_LAT_CTRL1,
		   CS4234_INV_LL2_SHIFT, 1, 0),
	SOC_SINGLE("DAC3 Low-latency Invert Switch", CS4234_LOW_LAT_CTRL1,
		   CS4234_INV_LL3_SHIFT, 1, 0),
	SOC_SINGLE("DAC4 Low-latency Invert Switch", CS4234_LOW_LAT_CTRL1,
		   CS4234_INV_LL4_SHIFT, 1, 0),

	SOC_ENUM("Low-latency Noise Gate", cs4234_ll_noise_gate),
	SOC_ENUM("DAC1-4 Noise Gate", cs4234_dac14_noise_gate),
	SOC_ENUM("DAC5 Noise Gate", cs4234_dac5_noise_gate),

	SOC_SINGLE("DAC1-4 De-emphasis Switch", CS4234_DAC_CTRL1,
		   CS4234_DAC14_DE_SHIFT, 1, 0),
	SOC_SINGLE("DAC5 De-emphasis Switch", CS4234_DAC_CTRL1,
		   CS4234_DAC5_DE_SHIFT, 1, 0),

	SOC_SINGLE("DAC5 Master Controlled Switch", CS4234_DAC_CTRL1,
		   CS4234_DAC5_MVC_SHIFT, 1, 0),

	SOC_ENUM("DAC5 Filter", cs4234_dac5_config_fltr_sel),

	SOC_ENUM("Mute Delay", cs4234_mute_delay),
	SOC_ENUM("Ramp Minimum Delay", cs4234_min_delay),
	SOC_ENUM("Ramp Maximum Delay", cs4234_max_delay),

पूर्ण;

अटल पूर्णांक cs4234_dai_set_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक क्रमmat)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cs4234 *cs4234 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक sp_ctrl = 0;

	cs4234->क्रमmat = क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK;
	चयन (cs4234->क्रमmat) अणु
	हाल SND_SOC_DAIFMT_LEFT_J:
		sp_ctrl |= CS4234_LEFT_J << CS4234_SP_FORMAT_SHIFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		sp_ctrl |= CS4234_I2S << CS4234_SP_FORMAT_SHIFT;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A: /* TDM mode in datasheet */
		sp_ctrl |= CS4234_TDM << CS4234_SP_FORMAT_SHIFT;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported dai format\n");
		वापस -EINVAL;
	पूर्ण

	चयन (क्रमmat & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अगर (cs4234->क्रमmat == SND_SOC_DAIFMT_DSP_A) अणु
			dev_err(component->dev, "Unsupported DSP A format in master mode\n");
			वापस -EINVAL;
		पूर्ण
		sp_ctrl |= CS4234_MST_SLV_MASK;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported master/slave mode\n");
		वापस -EINVAL;
	पूर्ण

	चयन (क्रमmat & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		sp_ctrl |= CS4234_INVT_SCLK_MASK;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported inverted clock setting\n");
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(cs4234->regmap, CS4234_SP_CTRL,
			   CS4234_SP_FORMAT_MASK | CS4234_MST_SLV_MASK | CS4234_INVT_SCLK_MASK,
			   sp_ctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक cs4234_dai_hw_params(काष्ठा snd_pcm_substream *sub,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs4234 *cs4234 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक mclk_mult, द्विगुन_speed = 0;
	पूर्णांक ret = 0, rate_ad, sample_width;

	cs4234->lrclk_rate = params_rate(params);
	mclk_mult = cs4234->mclk_rate / cs4234->lrclk_rate;

	अगर (cs4234->lrclk_rate > 48000) अणु
		द्विगुन_speed = 1;
		mclk_mult *= 2;
	पूर्ण

	चयन (mclk_mult) अणु
	हाल 256:
	हाल 384:
	हाल 512:
		regmap_update_bits(cs4234->regmap, CS4234_CLOCK_SP,
				   CS4234_SPEED_MODE_MASK,
				   द्विगुन_speed << CS4234_SPEED_MODE_SHIFT);
		regmap_update_bits(cs4234->regmap, CS4234_CLOCK_SP,
				   CS4234_MCLK_RATE_MASK,
				   ((mclk_mult / 128) - 2) << CS4234_MCLK_RATE_SHIFT);
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported mclk/lrclk rate\n");
		वापस -EINVAL;
	पूर्ण

	चयन (cs4234->lrclk_rate) अणु
	हाल 48000:
	हाल 96000:
		rate_ad = CS4234_48K;
		अवरोध;
	हाल 44100:
	हाल 88200:
		rate_ad = CS4234_44K1;
		अवरोध;
	हाल 32000:
	हाल 64000:
		rate_ad = CS4234_32K;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported LR clock\n");
		वापस -EINVAL;
	पूर्ण
	regmap_update_bits(cs4234->regmap, CS4234_CLOCK_SP, CS4234_BASE_RATE_MASK,
			   rate_ad << CS4234_BASE_RATE_SHIFT);

	sample_width = params_width(params);
	चयन (sample_width) अणु
	हाल 16:
		sample_width = 0;
		अवरोध;
	हाल 18:
		sample_width = 1;
		अवरोध;
	हाल 20:
		sample_width = 2;
		अवरोध;
	हाल 24:
		sample_width = 3;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported sample width\n");
		वापस -EINVAL;
	पूर्ण
	अगर (sub->stream == SNDRV_PCM_STREAM_CAPTURE)
		regmap_update_bits(cs4234->regmap, CS4234_SAMPLE_WIDTH,
				   CS4234_SDOUTX_SW_MASK,
				   sample_width << CS4234_SDOUTX_SW_SHIFT);
	अन्यथा
		regmap_update_bits(cs4234->regmap, CS4234_SAMPLE_WIDTH,
				CS4234_INPUT_SW_MASK | CS4234_LOW_LAT_SW_MASK | CS4234_DAC5_SW_MASK,
				sample_width << CS4234_INPUT_SW_SHIFT |
				sample_width << CS4234_LOW_LAT_SW_SHIFT |
				sample_width << CS4234_DAC5_SW_SHIFT);

	वापस ret;
पूर्ण

/* Scale MCLK rate by 64 to aव्योम overflow in the ratnum calculation */
#घोषणा CS4234_MCLK_SCALE  64

अटल स्थिर काष्ठा snd_ratnum cs4234_भागiders[] = अणु
	अणु
		.num = 0,
		.den_min = 256 / CS4234_MCLK_SCALE,
		.den_max = 512 / CS4234_MCLK_SCALE,
		.den_step = 128 / CS4234_MCLK_SCALE,
	पूर्ण,
	अणु
		.num = 0,
		.den_min = 128 / CS4234_MCLK_SCALE,
		.den_max = 192 / CS4234_MCLK_SCALE,
		.den_step = 64 / CS4234_MCLK_SCALE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक cs4234_dai_rule_rate(काष्ठा snd_pcm_hw_params *params, काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा cs4234 *cs4234 = rule->निजी;
	पूर्णांक mclk = cs4234->mclk_rate;
	काष्ठा snd_पूर्णांकerval ranges[] = अणु
		अणु /* Single Speed Mode */
			.min = mclk / clamp(mclk / 30000, 256, 512),
			.max = mclk / clamp(mclk / 50000, 256, 512),
		पूर्ण,
		अणु /* Double Speed Mode */
			.min = mclk / clamp(mclk / 60000,  128, 256),
			.max = mclk / clamp(mclk / 100000, 128, 256),
		पूर्ण,
	पूर्ण;

	वापस snd_पूर्णांकerval_ranges(hw_param_पूर्णांकerval(params, rule->var),
				   ARRAY_SIZE(ranges), ranges, 0);
पूर्ण

अटल पूर्णांक cs4234_dai_startup(काष्ठा snd_pcm_substream *sub, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *comp = dai->component;
	काष्ठा cs4234 *cs4234 = snd_soc_component_get_drvdata(comp);
	पूर्णांक i, ret;

	चयन (cs4234->क्रमmat) अणु
	हाल SND_SOC_DAIFMT_LEFT_J:
	हाल SND_SOC_DAIFMT_I2S:
		cs4234->rate_स्थिरraपूर्णांक.nrats = 2;

		/*
		 * Playback only supports 24-bit samples in these modes.
		 * Note: SNDRV_PCM_HW_PARAM_SAMPLE_BITS स्थिरrains the physical
		 * width, which we करोn't care about, so स्थिरrain the क्रमmat.
		 */
		अगर (sub->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			ret = snd_pcm_hw_स्थिरraपूर्णांक_mask64(
						sub->runसमय,
						SNDRV_PCM_HW_PARAM_FORMAT,
						SNDRV_PCM_FMTBIT_S24_LE |
						SNDRV_PCM_FMTBIT_S24_3LE);
			अगर (ret < 0)
				वापस ret;

			ret = snd_pcm_hw_स्थिरraपूर्णांक_minmax(sub->runसमय,
							   SNDRV_PCM_HW_PARAM_CHANNELS,
							   1, 4);
			अगर (ret < 0)
				वापस ret;
		पूर्ण

		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		cs4234->rate_स्थिरraपूर्णांक.nrats = 1;
		अवरोध;
	शेष:
		dev_err(comp->dev, "Startup unsupported DAI format\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < cs4234->rate_स्थिरraपूर्णांक.nrats; i++)
		cs4234->rate_भागiders[i].num = cs4234->mclk_rate / CS4234_MCLK_SCALE;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_ratnums(sub->runसमय, 0,
					    SNDRV_PCM_HW_PARAM_RATE,
					    &cs4234->rate_स्थिरraपूर्णांक);
	अगर (ret < 0)
		वापस ret;

	/*
	 * MCLK/rate may be a valid ratio but out-of-spec (e.g. 24576000/64000)
	 * so this rule limits the range of sample rate क्रम given MCLK.
	 */
	वापस snd_pcm_hw_rule_add(sub->runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				   cs4234_dai_rule_rate, cs4234, -1);
पूर्ण

अटल पूर्णांक cs4234_dai_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
				   अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs4234 *cs4234 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक slot_offset, dac5_slot, dac5_mask_group;
	uपूर्णांक8_t dac5_masks[4];

	अगर (slot_width != 32) अणु
		dev_err(component->dev, "Unsupported slot width\n");
		वापस -EINVAL;
	पूर्ण

	/* Either 4 or 5 consecutive bits, DAC5 is optional */
	slot_offset = ffs(tx_mask) - 1;
	tx_mask >>= slot_offset;
	अगर ((slot_offset % 4) || ((tx_mask != 0x0F) && (tx_mask != 0x1F))) अणु
		dev_err(component->dev, "Unsupported tx slots allocation\n");
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(cs4234->regmap, CS4234_SP_DATA_SEL, CS4234_DAC14_SRC_MASK,
			   (slot_offset / 4) << CS4234_DAC14_SRC_SHIFT);
	regmap_update_bits(cs4234->regmap, CS4234_SP_DATA_SEL, CS4234_LL_SRC_MASK,
			   (slot_offset / 4) << CS4234_LL_SRC_SHIFT);

	अगर (tx_mask == 0x1F) अणु
		dac5_slot = slot_offset + 4;
		स_रखो(dac5_masks, 0xFF, माप(dac5_masks));
		dac5_mask_group = dac5_slot / 8;
		dac5_slot %= 8;
		dac5_masks[dac5_mask_group] ^= BIT(7 - dac5_slot);
		regmap_bulk_ग_लिखो(cs4234->regmap,
				  CS4234_SDIN1_MASK1,
				  dac5_masks,
				  ARRAY_SIZE(dac5_masks));
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops cs4234_dai_ops = अणु
	.set_fmt	= cs4234_dai_set_fmt,
	.hw_params	= cs4234_dai_hw_params,
	.startup	= cs4234_dai_startup,
	.set_tdm_slot	= cs4234_dai_set_tdm_slot,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver cs4234_dai[] = अणु
	अणु
		.name = "cs4234-dai",
		.playback = अणु
			.stream_name = "Playback",
			.channels_min = 1,
			.channels_max = 5,
			.rates = CS4234_PCM_RATES,
			.क्रमmats = CS4234_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "Capture",
			.channels_min = 1,
			.channels_max = 4,
			.rates = CS4234_PCM_RATES,
			.क्रमmats = CS4234_FORMATS,
		पूर्ण,
		.ops = &cs4234_dai_ops,
		.symmetric_rate = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष cs4234_शेष_reg[] = अणु
	अणु CS4234_CLOCK_SP,	 0x04पूर्ण,
	अणु CS4234_SAMPLE_WIDTH,	 0xFFपूर्ण,
	अणु CS4234_SP_CTRL,	 0x48पूर्ण,
	अणु CS4234_SP_DATA_SEL,	 0x01पूर्ण,
	अणु CS4234_SDIN1_MASK1,	 0xFFपूर्ण,
	अणु CS4234_SDIN1_MASK2,	 0xFFपूर्ण,
	अणु CS4234_SDIN2_MASK1,	 0xFFपूर्ण,
	अणु CS4234_SDIN2_MASK2,	 0xFFपूर्ण,
	अणु CS4234_TPS_CTRL,	 0x00पूर्ण,
	अणु CS4234_ADC_CTRL1,	 0xC0पूर्ण,
	अणु CS4234_ADC_CTRL2,	 0xFFपूर्ण,
	अणु CS4234_LOW_LAT_CTRL1,	 0xE0पूर्ण,
	अणु CS4234_DAC_CTRL1,	 0xE0पूर्ण,
	अणु CS4234_DAC_CTRL2,	 0xE0पूर्ण,
	अणु CS4234_DAC_CTRL3,	 0xBFपूर्ण,
	अणु CS4234_DAC_CTRL4,	 0x1Fपूर्ण,
	अणु CS4234_VOLUME_MODE,	 0x87पूर्ण,
	अणु CS4234_MASTER_VOL,	 0x10पूर्ण,
	अणु CS4234_DAC1_VOL,	 0x10पूर्ण,
	अणु CS4234_DAC2_VOL,	 0x10पूर्ण,
	अणु CS4234_DAC3_VOL,	 0x10पूर्ण,
	अणु CS4234_DAC4_VOL,	 0x10पूर्ण,
	अणु CS4234_DAC5_VOL,	 0x10पूर्ण,
	अणु CS4234_INT_CTRL,	 0x40पूर्ण,
	अणु CS4234_INT_MASK1,	 0x10पूर्ण,
	अणु CS4234_INT_MASK2,	 0x20पूर्ण,
पूर्ण;

अटल bool cs4234_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS4234_DEVID_AB ... CS4234_DEVID_EF:
	हाल CS4234_REVID ... CS4234_DAC5_VOL:
	हाल CS4234_INT_CTRL ... CS4234_MAX_REGISTER:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cs4234_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS4234_INT_NOTIFY1:
	हाल CS4234_INT_NOTIFY2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cs4234_ग_लिखोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS4234_DEVID_AB ... CS4234_REVID:
	हाल CS4234_INT_NOTIFY1 ... CS4234_INT_NOTIFY2:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_cs4234 = अणु
	.dapm_widमाला_लो		= cs4234_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(cs4234_dapm_widमाला_लो),
	.dapm_routes		= cs4234_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(cs4234_dapm_routes),
	.controls		= cs4234_snd_controls,
	.num_controls		= ARRAY_SIZE(cs4234_snd_controls),
	.set_bias_level		= cs4234_set_bias_level,
	.non_legacy_dai_naming	= 1,
	.idle_bias_on		= 1,
	.suspend_bias_off	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config cs4234_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = CS4234_MAX_REGISTER,
	.पढ़ोable_reg = cs4234_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = cs4234_अस्थिर_reg,
	.ग_लिखोable_reg = cs4234_ग_लिखोable_रेजिस्टर,
	.reg_शेषs = cs4234_शेष_reg,
	.num_reg_शेषs = ARRAY_SIZE(cs4234_शेष_reg),
	.cache_type = REGCACHE_RBTREE,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल स्थिर अक्षर * स्थिर cs4234_core_supplies[] = अणु
	"VA",
	"VL",
पूर्ण;

अटल व्योम cs4234_shutकरोwn(काष्ठा cs4234 *cs4234)
अणु
	cancel_delayed_work_sync(&cs4234->vq_ramp_delay);
	reinit_completion(&cs4234->vq_ramp_complete);

	regmap_update_bits(cs4234->regmap, CS4234_DAC_CTRL4, CS4234_VQ_RAMP_MASK,
			   CS4234_VQ_RAMP_MASK);
	msleep(50);
	regcache_cache_only(cs4234->regmap, true);
	/* Clear VQ Ramp Bit in cache क्रम the next PowerUp */
	regmap_update_bits(cs4234->regmap, CS4234_DAC_CTRL4, CS4234_VQ_RAMP_MASK, 0);
	gpiod_set_value_cansleep(cs4234->reset_gpio, 0);
	regulator_bulk_disable(cs4234->num_core_supplies, cs4234->core_supplies);
	clk_disable_unprepare(cs4234->mclk);
पूर्ण

अटल पूर्णांक cs4234_घातerup(काष्ठा cs4234 *cs4234)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(cs4234->mclk);
	अगर (ret) अणु
		dev_err(cs4234->dev, "Failed to enable mclk: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(cs4234->num_core_supplies, cs4234->core_supplies);
	अगर (ret) अणु
		dev_err(cs4234->dev, "Failed to enable core supplies: %d\n", ret);
		clk_disable_unprepare(cs4234->mclk);
		वापस ret;
	पूर्ण

	usleep_range(CS4234_HOLD_RESET_TIME_US, 2 * CS4234_HOLD_RESET_TIME_US);
	gpiod_set_value_cansleep(cs4234->reset_gpio, 1);

	/* Make sure hardware reset करोne 2 ms + (3000/MCLK) */
	usleep_range(CS4234_BOOT_TIME_US, CS4234_BOOT_TIME_US * 2);

	queue_delayed_work(प्रणाली_घातer_efficient_wq,
			   &cs4234->vq_ramp_delay,
			   msecs_to_jअगरfies(CS4234_VQ_CHARGE_MS));

	वापस 0;
पूर्ण

अटल पूर्णांक cs4234_i2c_probe(काष्ठा i2c_client *i2c_client, स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cs4234 *cs4234;
	काष्ठा device *dev = &i2c_client->dev;
	अचिन्हित पूर्णांक revid;
	uपूर्णांक32_t devid;
	uपूर्णांक8_t ids[3];
	पूर्णांक ret = 0, i;

	cs4234 = devm_kzalloc(dev, माप(*cs4234), GFP_KERNEL);
	अगर (!cs4234)
		वापस -ENOMEM;
	i2c_set_clientdata(i2c_client, cs4234);
	cs4234->dev = dev;
	init_completion(&cs4234->vq_ramp_complete);
	INIT_DELAYED_WORK(&cs4234->vq_ramp_delay, cs4234_vq_ramp_करोne);

	cs4234->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(cs4234->reset_gpio))
		वापस PTR_ERR(cs4234->reset_gpio);

	BUILD_BUG_ON(ARRAY_SIZE(cs4234->core_supplies) < ARRAY_SIZE(cs4234_core_supplies));

	cs4234->num_core_supplies = ARRAY_SIZE(cs4234_core_supplies);
	क्रम (i = 0; i < ARRAY_SIZE(cs4234_core_supplies); i++)
		cs4234->core_supplies[i].supply = cs4234_core_supplies[i];

	ret = devm_regulator_bulk_get(dev, cs4234->num_core_supplies, cs4234->core_supplies);
	अगर (ret) अणु
		dev_err(dev, "Failed to request core supplies %d\n", ret);
		वापस ret;
	पूर्ण

	cs4234->mclk = devm_clk_get(dev, "mclk");
	अगर (IS_ERR(cs4234->mclk)) अणु
		ret = PTR_ERR(cs4234->mclk);
		dev_err(dev, "Failed to get the mclk: %d\n", ret);
		वापस ret;
	पूर्ण
	cs4234->mclk_rate = clk_get_rate(cs4234->mclk);

	अगर (cs4234->mclk_rate < 7680000 || cs4234->mclk_rate > 25600000) अणु
		dev_err(dev, "Invalid Master Clock rate\n");
		वापस -EINVAL;
	पूर्ण

	cs4234->regmap = devm_regmap_init_i2c(i2c_client, &cs4234_regmap);
	अगर (IS_ERR(cs4234->regmap)) अणु
		ret = PTR_ERR(cs4234->regmap);
		dev_err(dev, "regmap_init() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = cs4234_घातerup(cs4234);
	अगर (ret)
		वापस ret;

	ret = regmap_bulk_पढ़ो(cs4234->regmap, CS4234_DEVID_AB, ids, ARRAY_SIZE(ids));
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read DEVID: %d\n", ret);
		जाओ fail_shutकरोwn;
	पूर्ण

	devid = (ids[0] << 16) | (ids[1] << 8) | ids[2];
	अगर (devid != CS4234_SUPPORTED_ID) अणु
		dev_err(dev, "Unknown device ID: %x\n", devid);
		ret = -EINVAL;
		जाओ fail_shutकरोwn;
	पूर्ण

	ret = regmap_पढ़ो(cs4234->regmap, CS4234_REVID, &revid);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read CS4234_REVID: %d\n", ret);
		जाओ fail_shutकरोwn;
	पूर्ण

	dev_info(dev, "Cirrus Logic CS4234, Alpha Rev: %02X, Numeric Rev: %02X\n",
		 (revid & 0xF0) >> 4, revid & 0x0F);

	ret = regulator_get_voltage(cs4234->core_supplies[CS4234_SUPPLY_VA].consumer);
	चयन (ret) अणु
	हाल 3135000 ... 3650000:
		regmap_update_bits(cs4234->regmap, CS4234_ADC_CTRL1,
				   CS4234_VA_SEL_MASK,
				   CS4234_3V3 << CS4234_VA_SEL_SHIFT);
		अवरोध;
	हाल 4750000 ... 5250000:
		regmap_update_bits(cs4234->regmap, CS4234_ADC_CTRL1,
				   CS4234_VA_SEL_MASK,
				   CS4234_5V << CS4234_VA_SEL_SHIFT);
		अवरोध;
	शेष:
		dev_err(dev, "Invalid VA voltage\n");
		ret = -EINVAL;
		जाओ fail_shutकरोwn;
	पूर्ण

	pm_runसमय_set_active(&i2c_client->dev);
	pm_runसमय_enable(&i2c_client->dev);

	स_नकल(&cs4234->rate_भागiders, &cs4234_भागiders, माप(cs4234_भागiders));
	cs4234->rate_स्थिरraपूर्णांक.rats = cs4234->rate_भागiders;

	ret = snd_soc_रेजिस्टर_component(dev, &soc_component_cs4234, cs4234_dai,
					 ARRAY_SIZE(cs4234_dai));
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to register component:%d\n", ret);
		pm_runसमय_disable(&i2c_client->dev);
		जाओ fail_shutकरोwn;
	पूर्ण

	वापस ret;

fail_shutकरोwn:
	cs4234_shutकरोwn(cs4234);

	वापस ret;
पूर्ण

अटल पूर्णांक cs4234_i2c_हटाओ(काष्ठा i2c_client *i2c_client)
अणु
	काष्ठा cs4234 *cs4234 = i2c_get_clientdata(i2c_client);
	काष्ठा device *dev = &i2c_client->dev;

	snd_soc_unरेजिस्टर_component(dev);
	pm_runसमय_disable(dev);
	cs4234_shutकरोwn(cs4234);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cs4234_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा cs4234 *cs4234 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = cs4234_घातerup(cs4234);
	अगर (ret)
		वापस ret;

	regcache_mark_dirty(cs4234->regmap);
	regcache_cache_only(cs4234->regmap, false);
	ret = regcache_sync(cs4234->regmap);
	अगर (ret) अणु
		dev_err(dev, "Failed to sync regmap: %d\n", ret);
		cs4234_shutकरोwn(cs4234);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused cs4234_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा cs4234 *cs4234 = dev_get_drvdata(dev);

	cs4234_shutकरोwn(cs4234);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops cs4234_pm = अणु
	SET_RUNTIME_PM_OPS(cs4234_runसमय_suspend, cs4234_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id cs4234_of_match[] = अणु
	अणु .compatible = "cirrus,cs4234", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cs4234_of_match);

अटल काष्ठा i2c_driver cs4234_i2c_driver = अणु
	.driver = अणु
		.name = "cs4234",
		.pm = &cs4234_pm,
		.of_match_table = cs4234_of_match,
	पूर्ण,
	.probe =	cs4234_i2c_probe,
	.हटाओ =	cs4234_i2c_हटाओ,
पूर्ण;
module_i2c_driver(cs4234_i2c_driver);

MODULE_DESCRIPTION("ASoC Cirrus Logic CS4234 driver");
MODULE_AUTHOR("Lucas Tanure <tanureal@opensource.cirrus.com>");
MODULE_LICENSE("GPL v2");
