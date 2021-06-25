<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PCM3168A codec driver
 *
 * Copyright (C) 2015 Imagination Technologies Ltd.
 *
 * Author: Damien Horsley <Damien.Horsley@imgtec.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>

#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#समावेश "pcm3168a.h"

#घोषणा PCM3168A_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | \
			 SNDRV_PCM_FMTBIT_S24_3LE | \
			 SNDRV_PCM_FMTBIT_S24_LE)

#घोषणा PCM3168A_FMT_I2S		0x0
#घोषणा PCM3168A_FMT_LEFT_J		0x1
#घोषणा PCM3168A_FMT_RIGHT_J		0x2
#घोषणा PCM3168A_FMT_RIGHT_J_16		0x3
#घोषणा PCM3168A_FMT_DSP_A		0x4
#घोषणा PCM3168A_FMT_DSP_B		0x5
#घोषणा PCM3168A_FMT_I2S_TDM		0x6
#घोषणा PCM3168A_FMT_LEFT_J_TDM		0x7
#घोषणा PCM3168A_FMT_DSP_MASK		0x4

#घोषणा PCM3168A_NUM_SUPPLIES 6
अटल स्थिर अक्षर *स्थिर pcm3168a_supply_names[PCM3168A_NUM_SUPPLIES] = अणु
	"VDD1",
	"VDD2",
	"VCCAD1",
	"VCCAD2",
	"VCCDA1",
	"VCCDA2"
पूर्ण;

#घोषणा PCM3168A_DAI_DAC		0
#घोषणा PCM3168A_DAI_ADC		1

/* ADC/DAC side parameters */
काष्ठा pcm3168a_io_params अणु
	bool master_mode;
	अचिन्हित पूर्णांक fmt;
	पूर्णांक tdm_slots;
	u32 tdm_mask;
	पूर्णांक slot_width;
पूर्ण;

काष्ठा pcm3168a_priv अणु
	काष्ठा regulator_bulk_data supplies[PCM3168A_NUM_SUPPLIES];
	काष्ठा regmap *regmap;
	काष्ठा clk *scki;
	काष्ठा gpio_desc *gpio_rst;
	अचिन्हित दीर्घ sysclk;

	काष्ठा pcm3168a_io_params io_params[2];
	काष्ठा snd_soc_dai_driver dai_drv[2];
पूर्ण;

अटल स्थिर अक्षर *स्थिर pcm3168a_roll_off[] = अणु "Sharp", "Slow" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(pcm3168a_d1_roll_off, PCM3168A_DAC_OP_FLT,
		PCM3168A_DAC_FLT_SHIFT, pcm3168a_roll_off);
अटल SOC_ENUM_SINGLE_DECL(pcm3168a_d2_roll_off, PCM3168A_DAC_OP_FLT,
		PCM3168A_DAC_FLT_SHIFT + 1, pcm3168a_roll_off);
अटल SOC_ENUM_SINGLE_DECL(pcm3168a_d3_roll_off, PCM3168A_DAC_OP_FLT,
		PCM3168A_DAC_FLT_SHIFT + 2, pcm3168a_roll_off);
अटल SOC_ENUM_SINGLE_DECL(pcm3168a_d4_roll_off, PCM3168A_DAC_OP_FLT,
		PCM3168A_DAC_FLT_SHIFT + 3, pcm3168a_roll_off);

अटल स्थिर अक्षर *स्थिर pcm3168a_volume_type[] = अणु
		"Individual", "Master + Individual" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(pcm3168a_dac_volume_type, PCM3168A_DAC_ATT_DEMP_ZF,
		PCM3168A_DAC_ATMDDA_SHIFT, pcm3168a_volume_type);

अटल स्थिर अक्षर *स्थिर pcm3168a_att_speed_mult[] = अणु "2048", "4096" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(pcm3168a_dac_att_mult, PCM3168A_DAC_ATT_DEMP_ZF,
		PCM3168A_DAC_ATSPDA_SHIFT, pcm3168a_att_speed_mult);

अटल स्थिर अक्षर *स्थिर pcm3168a_demp[] = अणु
		"Disabled", "48khz", "44.1khz", "32khz" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(pcm3168a_dac_demp, PCM3168A_DAC_ATT_DEMP_ZF,
		PCM3168A_DAC_DEMP_SHIFT, pcm3168a_demp);

अटल स्थिर अक्षर *स्थिर pcm3168a_zf_func[] = अणु
		"DAC 1/2/3/4 AND", "DAC 1/2/3/4 OR", "DAC 1/2/3 AND",
		"DAC 1/2/3 OR", "DAC 4 AND", "DAC 4 OR" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(pcm3168a_dac_zf_func, PCM3168A_DAC_ATT_DEMP_ZF,
		PCM3168A_DAC_AZRO_SHIFT, pcm3168a_zf_func);

अटल स्थिर अक्षर *स्थिर pcm3168a_pol[] = अणु "Active High", "Active Low" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(pcm3168a_dac_zf_pol, PCM3168A_DAC_ATT_DEMP_ZF,
		PCM3168A_DAC_ATSPDA_SHIFT, pcm3168a_pol);

अटल स्थिर अक्षर *स्थिर pcm3168a_con[] = अणु "Differential", "Single-Ended" पूर्ण;

अटल SOC_ENUM_DOUBLE_DECL(pcm3168a_adc1_con, PCM3168A_ADC_SEAD,
				0, 1, pcm3168a_con);
अटल SOC_ENUM_DOUBLE_DECL(pcm3168a_adc2_con, PCM3168A_ADC_SEAD,
				2, 3, pcm3168a_con);
अटल SOC_ENUM_DOUBLE_DECL(pcm3168a_adc3_con, PCM3168A_ADC_SEAD,
				4, 5, pcm3168a_con);

अटल SOC_ENUM_SINGLE_DECL(pcm3168a_adc_volume_type, PCM3168A_ADC_ATT_OVF,
		PCM3168A_ADC_ATMDAD_SHIFT, pcm3168a_volume_type);

अटल SOC_ENUM_SINGLE_DECL(pcm3168a_adc_att_mult, PCM3168A_ADC_ATT_OVF,
		PCM3168A_ADC_ATSPAD_SHIFT, pcm3168a_att_speed_mult);

अटल SOC_ENUM_SINGLE_DECL(pcm3168a_adc_ov_pol, PCM3168A_ADC_ATT_OVF,
		PCM3168A_ADC_OVFP_SHIFT, pcm3168a_pol);

/* -100db to 0db, रेजिस्टर values 0-54 cause mute */
अटल स्थिर DECLARE_TLV_DB_SCALE(pcm3168a_dac_tlv, -10050, 50, 1);

/* -100db to 20db, रेजिस्टर values 0-14 cause mute */
अटल स्थिर DECLARE_TLV_DB_SCALE(pcm3168a_adc_tlv, -10050, 50, 1);

अटल स्थिर काष्ठा snd_kcontrol_new pcm3168a_snd_controls[] = अणु
	SOC_SINGLE("DAC Power-Save Switch", PCM3168A_DAC_PWR_MST_FMT,
			PCM3168A_DAC_PSMDA_SHIFT, 1, 1),
	SOC_ENUM("DAC1 Digital Filter roll-off", pcm3168a_d1_roll_off),
	SOC_ENUM("DAC2 Digital Filter roll-off", pcm3168a_d2_roll_off),
	SOC_ENUM("DAC3 Digital Filter roll-off", pcm3168a_d3_roll_off),
	SOC_ENUM("DAC4 Digital Filter roll-off", pcm3168a_d4_roll_off),
	SOC_DOUBLE("DAC1 Invert Switch", PCM3168A_DAC_INV, 0, 1, 1, 0),
	SOC_DOUBLE("DAC2 Invert Switch", PCM3168A_DAC_INV, 2, 3, 1, 0),
	SOC_DOUBLE("DAC3 Invert Switch", PCM3168A_DAC_INV, 4, 5, 1, 0),
	SOC_DOUBLE("DAC4 Invert Switch", PCM3168A_DAC_INV, 6, 7, 1, 0),
	SOC_ENUM("DAC Volume Control Type", pcm3168a_dac_volume_type),
	SOC_ENUM("DAC Volume Rate Multiplier", pcm3168a_dac_att_mult),
	SOC_ENUM("DAC De-Emphasis", pcm3168a_dac_demp),
	SOC_ENUM("DAC Zero Flag Function", pcm3168a_dac_zf_func),
	SOC_ENUM("DAC Zero Flag Polarity", pcm3168a_dac_zf_pol),
	SOC_SINGLE_RANGE_TLV("Master Playback Volume",
			PCM3168A_DAC_VOL_MASTER, 0, 54, 255, 0,
			pcm3168a_dac_tlv),
	SOC_DOUBLE_R_RANGE_TLV("DAC1 Playback Volume",
			PCM3168A_DAC_VOL_CHAN_START,
			PCM3168A_DAC_VOL_CHAN_START + 1,
			0, 54, 255, 0, pcm3168a_dac_tlv),
	SOC_DOUBLE_R_RANGE_TLV("DAC2 Playback Volume",
			PCM3168A_DAC_VOL_CHAN_START + 2,
			PCM3168A_DAC_VOL_CHAN_START + 3,
			0, 54, 255, 0, pcm3168a_dac_tlv),
	SOC_DOUBLE_R_RANGE_TLV("DAC3 Playback Volume",
			PCM3168A_DAC_VOL_CHAN_START + 4,
			PCM3168A_DAC_VOL_CHAN_START + 5,
			0, 54, 255, 0, pcm3168a_dac_tlv),
	SOC_DOUBLE_R_RANGE_TLV("DAC4 Playback Volume",
			PCM3168A_DAC_VOL_CHAN_START + 6,
			PCM3168A_DAC_VOL_CHAN_START + 7,
			0, 54, 255, 0, pcm3168a_dac_tlv),
	SOC_SINGLE("ADC1 High-Pass Filter Switch", PCM3168A_ADC_PWR_HPFB,
			PCM3168A_ADC_BYP_SHIFT, 1, 1),
	SOC_SINGLE("ADC2 High-Pass Filter Switch", PCM3168A_ADC_PWR_HPFB,
			PCM3168A_ADC_BYP_SHIFT + 1, 1, 1),
	SOC_SINGLE("ADC3 High-Pass Filter Switch", PCM3168A_ADC_PWR_HPFB,
			PCM3168A_ADC_BYP_SHIFT + 2, 1, 1),
	SOC_ENUM("ADC1 Connection Type", pcm3168a_adc1_con),
	SOC_ENUM("ADC2 Connection Type", pcm3168a_adc2_con),
	SOC_ENUM("ADC3 Connection Type", pcm3168a_adc3_con),
	SOC_DOUBLE("ADC1 Invert Switch", PCM3168A_ADC_INV, 0, 1, 1, 0),
	SOC_DOUBLE("ADC2 Invert Switch", PCM3168A_ADC_INV, 2, 3, 1, 0),
	SOC_DOUBLE("ADC3 Invert Switch", PCM3168A_ADC_INV, 4, 5, 1, 0),
	SOC_DOUBLE("ADC1 Mute Switch", PCM3168A_ADC_MUTE, 0, 1, 1, 0),
	SOC_DOUBLE("ADC2 Mute Switch", PCM3168A_ADC_MUTE, 2, 3, 1, 0),
	SOC_DOUBLE("ADC3 Mute Switch", PCM3168A_ADC_MUTE, 4, 5, 1, 0),
	SOC_ENUM("ADC Volume Control Type", pcm3168a_adc_volume_type),
	SOC_ENUM("ADC Volume Rate Multiplier", pcm3168a_adc_att_mult),
	SOC_ENUM("ADC Overflow Flag Polarity", pcm3168a_adc_ov_pol),
	SOC_SINGLE_RANGE_TLV("Master Capture Volume",
			PCM3168A_ADC_VOL_MASTER, 0, 14, 255, 0,
			pcm3168a_adc_tlv),
	SOC_DOUBLE_R_RANGE_TLV("ADC1 Capture Volume",
			PCM3168A_ADC_VOL_CHAN_START,
			PCM3168A_ADC_VOL_CHAN_START + 1,
			0, 14, 255, 0, pcm3168a_adc_tlv),
	SOC_DOUBLE_R_RANGE_TLV("ADC2 Capture Volume",
			PCM3168A_ADC_VOL_CHAN_START + 2,
			PCM3168A_ADC_VOL_CHAN_START + 3,
			0, 14, 255, 0, pcm3168a_adc_tlv),
	SOC_DOUBLE_R_RANGE_TLV("ADC3 Capture Volume",
			PCM3168A_ADC_VOL_CHAN_START + 4,
			PCM3168A_ADC_VOL_CHAN_START + 5,
			0, 14, 255, 0, pcm3168a_adc_tlv)
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget pcm3168a_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("DAC1", "Playback", PCM3168A_DAC_OP_FLT,
			PCM3168A_DAC_OPEDA_SHIFT, 1),
	SND_SOC_DAPM_DAC("DAC2", "Playback", PCM3168A_DAC_OP_FLT,
			PCM3168A_DAC_OPEDA_SHIFT + 1, 1),
	SND_SOC_DAPM_DAC("DAC3", "Playback", PCM3168A_DAC_OP_FLT,
			PCM3168A_DAC_OPEDA_SHIFT + 2, 1),
	SND_SOC_DAPM_DAC("DAC4", "Playback", PCM3168A_DAC_OP_FLT,
			PCM3168A_DAC_OPEDA_SHIFT + 3, 1),

	SND_SOC_DAPM_OUTPUT("AOUT1L"),
	SND_SOC_DAPM_OUTPUT("AOUT1R"),
	SND_SOC_DAPM_OUTPUT("AOUT2L"),
	SND_SOC_DAPM_OUTPUT("AOUT2R"),
	SND_SOC_DAPM_OUTPUT("AOUT3L"),
	SND_SOC_DAPM_OUTPUT("AOUT3R"),
	SND_SOC_DAPM_OUTPUT("AOUT4L"),
	SND_SOC_DAPM_OUTPUT("AOUT4R"),

	SND_SOC_DAPM_ADC("ADC1", "Capture", PCM3168A_ADC_PWR_HPFB,
			PCM3168A_ADC_PSVAD_SHIFT, 1),
	SND_SOC_DAPM_ADC("ADC2", "Capture", PCM3168A_ADC_PWR_HPFB,
			PCM3168A_ADC_PSVAD_SHIFT + 1, 1),
	SND_SOC_DAPM_ADC("ADC3", "Capture", PCM3168A_ADC_PWR_HPFB,
			PCM3168A_ADC_PSVAD_SHIFT + 2, 1),

	SND_SOC_DAPM_INPUT("AIN1L"),
	SND_SOC_DAPM_INPUT("AIN1R"),
	SND_SOC_DAPM_INPUT("AIN2L"),
	SND_SOC_DAPM_INPUT("AIN2R"),
	SND_SOC_DAPM_INPUT("AIN3L"),
	SND_SOC_DAPM_INPUT("AIN3R")
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route pcm3168a_dapm_routes[] = अणु
	/* Playback */
	अणु "AOUT1L", शून्य, "DAC1" पूर्ण,
	अणु "AOUT1R", शून्य, "DAC1" पूर्ण,

	अणु "AOUT2L", शून्य, "DAC2" पूर्ण,
	अणु "AOUT2R", शून्य, "DAC2" पूर्ण,

	अणु "AOUT3L", शून्य, "DAC3" पूर्ण,
	अणु "AOUT3R", शून्य, "DAC3" पूर्ण,

	अणु "AOUT4L", शून्य, "DAC4" पूर्ण,
	अणु "AOUT4R", शून्य, "DAC4" पूर्ण,

	/* Capture */
	अणु "ADC1", शून्य, "AIN1L" पूर्ण,
	अणु "ADC1", शून्य, "AIN1R" पूर्ण,

	अणु "ADC2", शून्य, "AIN2L" पूर्ण,
	अणु "ADC2", शून्य, "AIN2R" पूर्ण,

	अणु "ADC3", शून्य, "AIN3L" पूर्ण,
	अणु "ADC3", शून्य, "AIN3R" पूर्ण
पूर्ण;

अटल अचिन्हित पूर्णांक pcm3168a_scki_ratios[] = अणु
	768,
	512,
	384,
	256,
	192,
	128
पूर्ण;

#घोषणा PCM3168A_NUM_SCKI_RATIOS_DAC	ARRAY_SIZE(pcm3168a_scki_ratios)
#घोषणा PCM3168A_NUM_SCKI_RATIOS_ADC	(ARRAY_SIZE(pcm3168a_scki_ratios) - 2)

#घोषणा PCM3168A_MAX_SYSCLK		36864000

अटल पूर्णांक pcm3168a_reset(काष्ठा pcm3168a_priv *pcm3168a)
अणु
	पूर्णांक ret;

	ret = regmap_ग_लिखो(pcm3168a->regmap, PCM3168A_RST_SMODE, 0);
	अगर (ret)
		वापस ret;

	/* Internal reset is de-निश्चितed after 3846 SCKI cycles */
	msleep(DIV_ROUND_UP(3846 * 1000, pcm3168a->sysclk));

	वापस regmap_ग_लिखो(pcm3168a->regmap, PCM3168A_RST_SMODE,
			PCM3168A_MRST_MASK | PCM3168A_SRST_MASK);
पूर्ण

अटल पूर्णांक pcm3168a_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm3168a_priv *pcm3168a = snd_soc_component_get_drvdata(component);

	regmap_ग_लिखो(pcm3168a->regmap, PCM3168A_DAC_MUTE, mute ? 0xff : 0);

	वापस 0;
पूर्ण

अटल पूर्णांक pcm3168a_set_dai_sysclk(काष्ठा snd_soc_dai *dai,
				  पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा pcm3168a_priv *pcm3168a = snd_soc_component_get_drvdata(dai->component);
	पूर्णांक ret;

	/*
	 * Some sound card sets 0 Hz as reset,
	 * but it is impossible to set. Ignore it here
	 */
	अगर (freq == 0)
		वापस 0;

	अगर (freq > PCM3168A_MAX_SYSCLK)
		वापस -EINVAL;

	ret = clk_set_rate(pcm3168a->scki, freq);
	अगर (ret)
		वापस ret;

	pcm3168a->sysclk = freq;

	वापस 0;
पूर्ण

अटल व्योम pcm3168a_update_fixup_pcm_stream(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm3168a_priv *pcm3168a = snd_soc_component_get_drvdata(component);
	u64 क्रमmats = SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S24_LE;
	अचिन्हित पूर्णांक channel_max = dai->id == PCM3168A_DAI_DAC ? 8 : 6;

	अगर (pcm3168a->io_params[dai->id].fmt == PCM3168A_FMT_RIGHT_J) अणु
		/* S16_LE is only supported in RIGHT_J mode */
		क्रमmats |= SNDRV_PCM_FMTBIT_S16_LE;

		/*
		 * If multi DIN/DOUT is not selected, RIGHT_J can only support
		 * two channels (no TDM support)
		 */
		अगर (pcm3168a->io_params[dai->id].tdm_slots != 2)
			channel_max = 2;
	पूर्ण

	अगर (dai->id == PCM3168A_DAI_DAC) अणु
		dai->driver->playback.channels_max = channel_max;
		dai->driver->playback.क्रमmats = क्रमmats;
	पूर्ण अन्यथा अणु
		dai->driver->capture.channels_max = channel_max;
		dai->driver->capture.क्रमmats = क्रमmats;
	पूर्ण
पूर्ण

अटल पूर्णांक pcm3168a_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक क्रमmat)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm3168a_priv *pcm3168a = snd_soc_component_get_drvdata(component);
	u32 fmt, reg, mask, shअगरt;
	bool master_mode;

	चयन (क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_LEFT_J:
		fmt = PCM3168A_FMT_LEFT_J;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		fmt = PCM3168A_FMT_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		fmt = PCM3168A_FMT_RIGHT_J;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		fmt = PCM3168A_FMT_DSP_A;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		fmt = PCM3168A_FMT_DSP_B;
		अवरोध;
	शेष:
		dev_err(component->dev, "unsupported dai format\n");
		वापस -EINVAL;
	पूर्ण

	चयन (क्रमmat & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		master_mode = false;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		master_mode = true;
		अवरोध;
	शेष:
		dev_err(component->dev, "unsupported master/slave mode\n");
		वापस -EINVAL;
	पूर्ण

	चयन (क्रमmat & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (dai->id == PCM3168A_DAI_DAC) अणु
		reg = PCM3168A_DAC_PWR_MST_FMT;
		mask = PCM3168A_DAC_FMT_MASK;
		shअगरt = PCM3168A_DAC_FMT_SHIFT;
	पूर्ण अन्यथा अणु
		reg = PCM3168A_ADC_MST_FMT;
		mask = PCM3168A_ADC_FMTAD_MASK;
		shअगरt = PCM3168A_ADC_FMTAD_SHIFT;
	पूर्ण

	pcm3168a->io_params[dai->id].master_mode = master_mode;
	pcm3168a->io_params[dai->id].fmt = fmt;

	regmap_update_bits(pcm3168a->regmap, reg, mask, fmt << shअगरt);

	pcm3168a_update_fixup_pcm_stream(dai);

	वापस 0;
पूर्ण

अटल पूर्णांक pcm3168a_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
				 अचिन्हित पूर्णांक rx_mask, पूर्णांक slots,
				 पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm3168a_priv *pcm3168a = snd_soc_component_get_drvdata(component);
	काष्ठा pcm3168a_io_params *io_params = &pcm3168a->io_params[dai->id];

	अगर (tx_mask >= (1<<slots) || rx_mask >= (1<<slots)) अणु
		dev_err(component->dev,
			"Bad tdm mask tx: 0x%08x rx: 0x%08x slots %d\n",
			tx_mask, rx_mask, slots);
		वापस -EINVAL;
	पूर्ण

	अगर (slot_width &&
	    (slot_width != 16 && slot_width != 24 && slot_width != 32 )) अणु
		dev_err(component->dev, "Unsupported slot_width %d\n",
			slot_width);
		वापस -EINVAL;
	पूर्ण

	io_params->tdm_slots = slots;
	io_params->slot_width = slot_width;
	/* Ignore the not relevant mask क्रम the DAI/direction */
	अगर (dai->id == PCM3168A_DAI_DAC)
		io_params->tdm_mask = tx_mask;
	अन्यथा
		io_params->tdm_mask = rx_mask;

	pcm3168a_update_fixup_pcm_stream(dai);

	वापस 0;
पूर्ण

अटल पूर्णांक pcm3168a_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा pcm3168a_priv *pcm3168a = snd_soc_component_get_drvdata(component);
	काष्ठा pcm3168a_io_params *io_params = &pcm3168a->io_params[dai->id];
	bool master_mode;
	u32 val, mask, shअगरt, reg;
	अचिन्हित पूर्णांक rate, fmt, ratio, max_ratio;
	अचिन्हित पूर्णांक tdm_slots;
	पूर्णांक i, slot_width;

	rate = params_rate(params);

	ratio = pcm3168a->sysclk / rate;

	अगर (dai->id == PCM3168A_DAI_DAC) अणु
		max_ratio = PCM3168A_NUM_SCKI_RATIOS_DAC;
		reg = PCM3168A_DAC_PWR_MST_FMT;
		mask = PCM3168A_DAC_MSDA_MASK;
		shअगरt = PCM3168A_DAC_MSDA_SHIFT;
	पूर्ण अन्यथा अणु
		max_ratio = PCM3168A_NUM_SCKI_RATIOS_ADC;
		reg = PCM3168A_ADC_MST_FMT;
		mask = PCM3168A_ADC_MSAD_MASK;
		shअगरt = PCM3168A_ADC_MSAD_SHIFT;
	पूर्ण

	master_mode = io_params->master_mode;
	fmt = io_params->fmt;

	क्रम (i = 0; i < max_ratio; i++) अणु
		अगर (pcm3168a_scki_ratios[i] == ratio)
			अवरोध;
	पूर्ण

	अगर (i == max_ratio) अणु
		dev_err(component->dev, "unsupported sysclk ratio\n");
		वापस -EINVAL;
	पूर्ण

	अगर (io_params->slot_width)
		slot_width = io_params->slot_width;
	अन्यथा
		slot_width = params_width(params);

	चयन (slot_width) अणु
	हाल 16:
		अगर (master_mode || (fmt != PCM3168A_FMT_RIGHT_J)) अणु
			dev_err(component->dev, "16-bit slots are supported only for slave mode using right justified\n");
			वापस -EINVAL;
		पूर्ण
		fmt = PCM3168A_FMT_RIGHT_J_16;
		अवरोध;
	हाल 24:
		अगर (master_mode || (fmt & PCM3168A_FMT_DSP_MASK)) अणु
			dev_err(component->dev, "24-bit slots not supported in master mode, or slave mode using DSP\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल 32:
		अवरोध;
	शेष:
		dev_err(component->dev, "unsupported frame size: %d\n", slot_width);
		वापस -EINVAL;
	पूर्ण

	अगर (io_params->tdm_slots)
		tdm_slots = io_params->tdm_slots;
	अन्यथा
		tdm_slots = params_channels(params);

	/*
	 * Switch the codec to TDM mode when more than 2 TDM slots are needed
	 * क्रम the stream.
	 * If pcm3168a->tdm_slots is not set or set to more than 2 (8/6 usually)
	 * then DIN1/DOUT1 is used in TDM mode.
	 * If pcm3168a->tdm_slots is set to 2 then DIN1/2/3/4 and DOUT1/2/3 is
	 * used in normal mode, no need to चयन to TDM modes.
	 */
	अगर (tdm_slots > 2) अणु
		चयन (fmt) अणु
		हाल PCM3168A_FMT_I2S:
		हाल PCM3168A_FMT_DSP_A:
			fmt = PCM3168A_FMT_I2S_TDM;
			अवरोध;
		हाल PCM3168A_FMT_LEFT_J:
		हाल PCM3168A_FMT_DSP_B:
			fmt = PCM3168A_FMT_LEFT_J_TDM;
			अवरोध;
		शेष:
			dev_err(component->dev,
				"TDM is supported under DSP/I2S/Left_J only\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (master_mode)
		val = ((i + 1) << shअगरt);
	अन्यथा
		val = 0;

	regmap_update_bits(pcm3168a->regmap, reg, mask, val);

	अगर (dai->id == PCM3168A_DAI_DAC) अणु
		mask = PCM3168A_DAC_FMT_MASK;
		shअगरt = PCM3168A_DAC_FMT_SHIFT;
	पूर्ण अन्यथा अणु
		mask = PCM3168A_ADC_FMTAD_MASK;
		shअगरt = PCM3168A_ADC_FMTAD_SHIFT;
	पूर्ण

	regmap_update_bits(pcm3168a->regmap, reg, mask, fmt << shअगरt);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops pcm3168a_dai_ops = अणु
	.set_fmt	= pcm3168a_set_dai_fmt,
	.set_sysclk	= pcm3168a_set_dai_sysclk,
	.hw_params	= pcm3168a_hw_params,
	.mute_stream	= pcm3168a_mute,
	.set_tdm_slot	= pcm3168a_set_tdm_slot,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver pcm3168a_dais[] = अणु
	अणु
		.name = "pcm3168a-dac",
		.id = PCM3168A_DAI_DAC,
		.playback = अणु
			.stream_name = "Playback",
			.channels_min = 1,
			.channels_max = 8,
			.rates = SNDRV_PCM_RATE_8000_192000,
			.क्रमmats = PCM3168A_FORMATS
		पूर्ण,
		.ops = &pcm3168a_dai_ops
	पूर्ण,
	अणु
		.name = "pcm3168a-adc",
		.id = PCM3168A_DAI_ADC,
		.capture = अणु
			.stream_name = "Capture",
			.channels_min = 1,
			.channels_max = 6,
			.rates = SNDRV_PCM_RATE_8000_96000,
			.क्रमmats = PCM3168A_FORMATS
		पूर्ण,
		.ops = &pcm3168a_dai_ops
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष pcm3168a_reg_शेष[] = अणु
	अणु PCM3168A_RST_SMODE, PCM3168A_MRST_MASK | PCM3168A_SRST_MASK पूर्ण,
	अणु PCM3168A_DAC_PWR_MST_FMT, 0x00 पूर्ण,
	अणु PCM3168A_DAC_OP_FLT, 0x00 पूर्ण,
	अणु PCM3168A_DAC_INV, 0x00 पूर्ण,
	अणु PCM3168A_DAC_MUTE, 0x00 पूर्ण,
	अणु PCM3168A_DAC_ZERO, 0x00 पूर्ण,
	अणु PCM3168A_DAC_ATT_DEMP_ZF, 0x00 पूर्ण,
	अणु PCM3168A_DAC_VOL_MASTER, 0xff पूर्ण,
	अणु PCM3168A_DAC_VOL_CHAN_START, 0xff पूर्ण,
	अणु PCM3168A_DAC_VOL_CHAN_START + 1, 0xff पूर्ण,
	अणु PCM3168A_DAC_VOL_CHAN_START + 2, 0xff पूर्ण,
	अणु PCM3168A_DAC_VOL_CHAN_START + 3, 0xff पूर्ण,
	अणु PCM3168A_DAC_VOL_CHAN_START + 4, 0xff पूर्ण,
	अणु PCM3168A_DAC_VOL_CHAN_START + 5, 0xff पूर्ण,
	अणु PCM3168A_DAC_VOL_CHAN_START + 6, 0xff पूर्ण,
	अणु PCM3168A_DAC_VOL_CHAN_START + 7, 0xff पूर्ण,
	अणु PCM3168A_ADC_SMODE, 0x00 पूर्ण,
	अणु PCM3168A_ADC_MST_FMT, 0x00 पूर्ण,
	अणु PCM3168A_ADC_PWR_HPFB, 0x00 पूर्ण,
	अणु PCM3168A_ADC_SEAD, 0x00 पूर्ण,
	अणु PCM3168A_ADC_INV, 0x00 पूर्ण,
	अणु PCM3168A_ADC_MUTE, 0x00 पूर्ण,
	अणु PCM3168A_ADC_OV, 0x00 पूर्ण,
	अणु PCM3168A_ADC_ATT_OVF, 0x00 पूर्ण,
	अणु PCM3168A_ADC_VOL_MASTER, 0xd3 पूर्ण,
	अणु PCM3168A_ADC_VOL_CHAN_START, 0xd3 पूर्ण,
	अणु PCM3168A_ADC_VOL_CHAN_START + 1, 0xd3 पूर्ण,
	अणु PCM3168A_ADC_VOL_CHAN_START + 2, 0xd3 पूर्ण,
	अणु PCM3168A_ADC_VOL_CHAN_START + 3, 0xd3 पूर्ण,
	अणु PCM3168A_ADC_VOL_CHAN_START + 4, 0xd3 पूर्ण,
	अणु PCM3168A_ADC_VOL_CHAN_START + 5, 0xd3 पूर्ण
पूर्ण;

अटल bool pcm3168a_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	अगर (reg >= PCM3168A_RST_SMODE)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल bool pcm3168a_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल PCM3168A_RST_SMODE:
	हाल PCM3168A_DAC_ZERO:
	हाल PCM3168A_ADC_OV:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool pcm3168a_ग_लिखोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	अगर (reg < PCM3168A_RST_SMODE)
		वापस false;

	चयन (reg) अणु
	हाल PCM3168A_DAC_ZERO:
	हाल PCM3168A_ADC_OV:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

स्थिर काष्ठा regmap_config pcm3168a_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = PCM3168A_ADC_VOL_CHAN_START + 5,
	.reg_शेषs = pcm3168a_reg_शेष,
	.num_reg_शेषs = ARRAY_SIZE(pcm3168a_reg_शेष),
	.पढ़ोable_reg = pcm3168a_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = pcm3168a_अस्थिर_रेजिस्टर,
	.ग_लिखोable_reg = pcm3168a_ग_लिखोable_रेजिस्टर,
	.cache_type = REGCACHE_FLAT
पूर्ण;
EXPORT_SYMBOL_GPL(pcm3168a_regmap);

अटल स्थिर काष्ठा snd_soc_component_driver pcm3168a_driver = अणु
	.controls		= pcm3168a_snd_controls,
	.num_controls		= ARRAY_SIZE(pcm3168a_snd_controls),
	.dapm_widमाला_लो		= pcm3168a_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(pcm3168a_dapm_widमाला_लो),
	.dapm_routes		= pcm3168a_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(pcm3168a_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

पूर्णांक pcm3168a_probe(काष्ठा device *dev, काष्ठा regmap *regmap)
अणु
	काष्ठा pcm3168a_priv *pcm3168a;
	पूर्णांक ret, i;

	pcm3168a = devm_kzalloc(dev, माप(*pcm3168a), GFP_KERNEL);
	अगर (pcm3168a == शून्य)
		वापस -ENOMEM;

	dev_set_drvdata(dev, pcm3168a);

	/*
	 * Request the reset (connected to RST pin) gpio line as non exclusive
	 * as the same reset line might be connected to multiple pcm3168a codec
	 *
	 * The RST is low active, we want the GPIO line to be high initially, so
	 * request the initial level to LOW which in practice means DEASSERTED:
	 * The deनिश्चितed level of GPIO_ACTIVE_LOW is HIGH.
	 */
	pcm3168a->gpio_rst = devm_gpiod_get_optional(dev, "reset",
						GPIOD_OUT_LOW |
						GPIOD_FLAGS_BIT_NONEXCLUSIVE);
	अगर (IS_ERR(pcm3168a->gpio_rst)) अणु
		ret = PTR_ERR(pcm3168a->gpio_rst);
		अगर (ret != -EPROBE_DEFER )
			dev_err(dev, "failed to acquire RST gpio: %d\n", ret);

		वापस ret;
	पूर्ण

	pcm3168a->scki = devm_clk_get(dev, "scki");
	अगर (IS_ERR(pcm3168a->scki)) अणु
		ret = PTR_ERR(pcm3168a->scki);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to acquire clock 'scki': %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(pcm3168a->scki);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable mclk: %d\n", ret);
		वापस ret;
	पूर्ण

	pcm3168a->sysclk = clk_get_rate(pcm3168a->scki);

	क्रम (i = 0; i < ARRAY_SIZE(pcm3168a->supplies); i++)
		pcm3168a->supplies[i].supply = pcm3168a_supply_names[i];

	ret = devm_regulator_bulk_get(dev,
			ARRAY_SIZE(pcm3168a->supplies), pcm3168a->supplies);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to request supplies: %d\n", ret);
		जाओ err_clk;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(pcm3168a->supplies),
				    pcm3168a->supplies);
	अगर (ret) अणु
		dev_err(dev, "failed to enable supplies: %d\n", ret);
		जाओ err_clk;
	पूर्ण

	pcm3168a->regmap = regmap;
	अगर (IS_ERR(pcm3168a->regmap)) अणु
		ret = PTR_ERR(pcm3168a->regmap);
		dev_err(dev, "failed to allocate regmap: %d\n", ret);
		जाओ err_regulator;
	पूर्ण

	अगर (pcm3168a->gpio_rst) अणु
		/*
		 * The device is taken out from reset via GPIO line, रुको क्रम
		 * 3846 SCKI घड़ी cycles क्रम the पूर्णांकernal reset de-निश्चितion
		 */
		msleep(DIV_ROUND_UP(3846 * 1000, pcm3168a->sysclk));
	पूर्ण अन्यथा अणु
		ret = pcm3168a_reset(pcm3168a);
		अगर (ret) अणु
			dev_err(dev, "Failed to reset device: %d\n", ret);
			जाओ err_regulator;
		पूर्ण
	पूर्ण

	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	pm_runसमय_idle(dev);

	स_नकल(pcm3168a->dai_drv, pcm3168a_dais, माप(pcm3168a->dai_drv));
	ret = devm_snd_soc_रेजिस्टर_component(dev, &pcm3168a_driver,
					      pcm3168a->dai_drv,
					      ARRAY_SIZE(pcm3168a->dai_drv));
	अगर (ret) अणु
		dev_err(dev, "failed to register component: %d\n", ret);
		जाओ err_regulator;
	पूर्ण

	वापस 0;

err_regulator:
	regulator_bulk_disable(ARRAY_SIZE(pcm3168a->supplies),
			pcm3168a->supplies);
err_clk:
	clk_disable_unprepare(pcm3168a->scki);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(pcm3168a_probe);

अटल व्योम pcm3168a_disable(काष्ठा device *dev)
अणु
	काष्ठा pcm3168a_priv *pcm3168a = dev_get_drvdata(dev);

	regulator_bulk_disable(ARRAY_SIZE(pcm3168a->supplies),
			       pcm3168a->supplies);
	clk_disable_unprepare(pcm3168a->scki);
पूर्ण

व्योम pcm3168a_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा pcm3168a_priv *pcm3168a = dev_get_drvdata(dev);

	/*
	 * The RST is low active, we want the GPIO line to be low when the
	 * driver is हटाओd, so set level to 1 which in practice means
	 * ASSERTED:
	 * The निश्चितed level of GPIO_ACTIVE_LOW is LOW.
	 */
	gpiod_set_value_cansleep(pcm3168a->gpio_rst, 1);
	pm_runसमय_disable(dev);
#अगर_अघोषित CONFIG_PM
	pcm3168a_disable(dev);
#पूर्ण_अगर
पूर्ण
EXPORT_SYMBOL_GPL(pcm3168a_हटाओ);

#अगर_घोषित CONFIG_PM
अटल पूर्णांक pcm3168a_rt_resume(काष्ठा device *dev)
अणु
	काष्ठा pcm3168a_priv *pcm3168a = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(pcm3168a->scki);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable mclk: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(pcm3168a->supplies),
				    pcm3168a->supplies);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable supplies: %d\n", ret);
		जाओ err_clk;
	पूर्ण

	ret = pcm3168a_reset(pcm3168a);
	अगर (ret) अणु
		dev_err(dev, "Failed to reset device: %d\n", ret);
		जाओ err_regulator;
	पूर्ण

	regcache_cache_only(pcm3168a->regmap, false);

	regcache_mark_dirty(pcm3168a->regmap);

	ret = regcache_sync(pcm3168a->regmap);
	अगर (ret) अणु
		dev_err(dev, "Failed to sync regmap: %d\n", ret);
		जाओ err_regulator;
	पूर्ण

	वापस 0;

err_regulator:
	regulator_bulk_disable(ARRAY_SIZE(pcm3168a->supplies),
			       pcm3168a->supplies);
err_clk:
	clk_disable_unprepare(pcm3168a->scki);

	वापस ret;
पूर्ण

अटल पूर्णांक pcm3168a_rt_suspend(काष्ठा device *dev)
अणु
	काष्ठा pcm3168a_priv *pcm3168a = dev_get_drvdata(dev);

	regcache_cache_only(pcm3168a->regmap, true);

	pcm3168a_disable(dev);

	वापस 0;
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा dev_pm_ops pcm3168a_pm_ops = अणु
	SET_RUNTIME_PM_OPS(pcm3168a_rt_suspend, pcm3168a_rt_resume, शून्य)
पूर्ण;
EXPORT_SYMBOL_GPL(pcm3168a_pm_ops);

MODULE_DESCRIPTION("PCM3168A codec driver");
MODULE_AUTHOR("Damien Horsley <Damien.Horsley@imgtec.com>");
MODULE_LICENSE("GPL v2");
