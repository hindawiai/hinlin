<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cs4265.c -- CS4265 ALSA SoC audio driver
 *
 * Copyright 2014 Cirrus Logic, Inc.
 *
 * Author: Paul Handrigan <paul.handrigan@cirrus.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश "cs4265.h"

काष्ठा cs4265_निजी अणु
	काष्ठा regmap *regmap;
	काष्ठा gpio_desc *reset_gpio;
	u8 क्रमmat;
	u32 sysclk;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष cs4265_reg_शेषs[] = अणु
	अणु CS4265_PWRCTL, 0x0F पूर्ण,
	अणु CS4265_DAC_CTL, 0x08 पूर्ण,
	अणु CS4265_ADC_CTL, 0x00 पूर्ण,
	अणु CS4265_MCLK_FREQ, 0x00 पूर्ण,
	अणु CS4265_SIG_SEL, 0x40 पूर्ण,
	अणु CS4265_CHB_PGA_CTL, 0x00 पूर्ण,
	अणु CS4265_CHA_PGA_CTL, 0x00 पूर्ण,
	अणु CS4265_ADC_CTL2, 0x19 पूर्ण,
	अणु CS4265_DAC_CHA_VOL, 0x00 पूर्ण,
	अणु CS4265_DAC_CHB_VOL, 0x00 पूर्ण,
	अणु CS4265_DAC_CTL2, 0xC0 पूर्ण,
	अणु CS4265_SPDIF_CTL1, 0x00 पूर्ण,
	अणु CS4265_SPDIF_CTL2, 0x00 पूर्ण,
	अणु CS4265_INT_MASK, 0x00 पूर्ण,
	अणु CS4265_STATUS_MODE_MSB, 0x00 पूर्ण,
	अणु CS4265_STATUS_MODE_LSB, 0x00 पूर्ण,
पूर्ण;

अटल bool cs4265_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS4265_CHIP_ID ... CS4265_MAX_REGISTER:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cs4265_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS4265_INT_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल DECLARE_TLV_DB_SCALE(pga_tlv, -1200, 50, 0);

अटल DECLARE_TLV_DB_SCALE(dac_tlv, -12750, 50, 0);

अटल स्थिर अक्षर * स्थिर digital_input_mux_text[] = अणु
	"SDIN1", "SDIN2"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(digital_input_mux_क्रमागत, CS4265_SIG_SEL, 7,
		digital_input_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new digital_input_mux =
	SOC_DAPM_ENUM("Digital Input Mux", digital_input_mux_क्रमागत);

अटल स्थिर अक्षर * स्थिर mic_linein_text[] = अणु
	"MIC", "LINEIN"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(mic_linein_क्रमागत, CS4265_ADC_CTL2, 0,
		mic_linein_text);

अटल स्थिर अक्षर * स्थिर cam_mode_text[] = अणु
	"One Byte", "Two Byte"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(cam_mode_क्रमागत, CS4265_SPDIF_CTL1, 5,
		cam_mode_text);

अटल स्थिर अक्षर * स्थिर cam_mono_stereo_text[] = अणु
	"Stereo", "Mono"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(spdअगर_mono_stereo_क्रमागत, CS4265_SPDIF_CTL2, 2,
		cam_mono_stereo_text);

अटल स्थिर अक्षर * स्थिर mono_select_text[] = अणु
	"Channel A", "Channel B"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(spdअगर_mono_select_क्रमागत, CS4265_SPDIF_CTL2, 0,
		mono_select_text);

अटल स्थिर काष्ठा snd_kcontrol_new mic_linein_mux =
	SOC_DAPM_ENUM("ADC Input Capture Mux", mic_linein_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new loopback_ctl =
	SOC_DAPM_SINGLE("Switch", CS4265_SIG_SEL, 1, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new spdअगर_चयन =
	SOC_DAPM_SINGLE("Switch", SND_SOC_NOPM, 0, 0, 0);

अटल स्थिर काष्ठा snd_kcontrol_new dac_चयन =
	SOC_DAPM_SINGLE("Switch", CS4265_PWRCTL, 1, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new cs4265_snd_controls[] = अणु

	SOC_DOUBLE_R_SX_TLV("PGA Volume", CS4265_CHA_PGA_CTL,
			      CS4265_CHB_PGA_CTL, 0, 0x28, 0x30, pga_tlv),
	SOC_DOUBLE_R_TLV("DAC Volume", CS4265_DAC_CHA_VOL,
		      CS4265_DAC_CHB_VOL, 0, 0xFF, 1, dac_tlv),
	SOC_SINGLE("De-emp 44.1kHz Switch", CS4265_DAC_CTL, 1,
				1, 0),
	SOC_SINGLE("DAC INV Switch", CS4265_DAC_CTL2, 5,
				1, 0),
	SOC_SINGLE("DAC Zero Cross Switch", CS4265_DAC_CTL2, 6,
				1, 0),
	SOC_SINGLE("DAC Soft Ramp Switch", CS4265_DAC_CTL2, 7,
				1, 0),
	SOC_SINGLE("ADC HPF Switch", CS4265_ADC_CTL, 1,
				1, 0),
	SOC_SINGLE("ADC Zero Cross Switch", CS4265_ADC_CTL2, 3,
				1, 1),
	SOC_SINGLE("ADC Soft Ramp Switch", CS4265_ADC_CTL2, 7,
				1, 0),
	SOC_SINGLE("E to F Buffer Disable Switch", CS4265_SPDIF_CTL1,
				6, 1, 0),
	SOC_ENUM("C Data Access", cam_mode_क्रमागत),
	SOC_SINGLE("SPDIF Switch", CS4265_SPDIF_CTL2, 5, 1, 1),
	SOC_SINGLE("Validity Bit Control Switch", CS4265_SPDIF_CTL2,
				3, 1, 0),
	SOC_ENUM("SPDIF Mono/Stereo", spdअगर_mono_stereo_क्रमागत),
	SOC_SINGLE("MMTLR Data Switch", CS4265_SPDIF_CTL2, 0, 1, 0),
	SOC_ENUM("Mono Channel Select", spdअगर_mono_select_क्रमागत),
	SND_SOC_BYTES("C Data Buffer", CS4265_C_DATA_BUFF, 24),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget cs4265_dapm_widमाला_लो[] = अणु

	SND_SOC_DAPM_INPUT("LINEINL"),
	SND_SOC_DAPM_INPUT("LINEINR"),
	SND_SOC_DAPM_INPUT("MICL"),
	SND_SOC_DAPM_INPUT("MICR"),

	SND_SOC_DAPM_AIF_OUT("DOUT", शून्य,  0,
			SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("SPDIFOUT", शून्य,  0,
			SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_MUX("ADC Mux", SND_SOC_NOPM, 0, 0, &mic_linein_mux),

	SND_SOC_DAPM_ADC("ADC", शून्य, CS4265_PWRCTL, 2, 1),
	SND_SOC_DAPM_PGA("Pre-amp MIC", CS4265_PWRCTL, 3,
			1, शून्य, 0),

	SND_SOC_DAPM_MUX("Input Mux", SND_SOC_NOPM,
			 0, 0, &digital_input_mux),

	SND_SOC_DAPM_MIXER("SDIN1 Input Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SDIN2 Input Mixer", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("SPDIF Transmitter", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_SWITCH("Loopback", SND_SOC_NOPM, 0, 0,
			&loopback_ctl),
	SND_SOC_DAPM_SWITCH("SPDIF", SND_SOC_NOPM, 0, 0,
			&spdअगर_चयन),
	SND_SOC_DAPM_SWITCH("DAC", CS4265_PWRCTL, 1, 1,
			&dac_चयन),

	SND_SOC_DAPM_AIF_IN("DIN1", शून्य,  0,
			SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("DIN2", शून्य,  0,
			SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("TXIN", शून्य,  0,
			CS4265_SPDIF_CTL2, 5, 1),

	SND_SOC_DAPM_OUTPUT("LINEOUTL"),
	SND_SOC_DAPM_OUTPUT("LINEOUTR"),

पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cs4265_audio_map[] = अणु

	अणु"DIN1", शून्य, "DAI1 Playback"पूर्ण,
	अणु"DIN2", शून्य, "DAI2 Playback"पूर्ण,
	अणु"SDIN1 Input Mixer", शून्य, "DIN1"पूर्ण,
	अणु"SDIN2 Input Mixer", शून्य, "DIN2"पूर्ण,
	अणु"Input Mux", "SDIN1", "SDIN1 Input Mixer"पूर्ण,
	अणु"Input Mux", "SDIN2", "SDIN2 Input Mixer"पूर्ण,
	अणु"DAC", "Switch", "Input Mux"पूर्ण,
	अणु"SPDIF", "Switch", "Input Mux"पूर्ण,
	अणु"LINEOUTL", शून्य, "DAC"पूर्ण,
	अणु"LINEOUTR", शून्य, "DAC"पूर्ण,
	अणु"SPDIFOUT", शून्य, "SPDIF"पूर्ण,

	अणु"Pre-amp MIC", शून्य, "MICL"पूर्ण,
	अणु"Pre-amp MIC", शून्य, "MICR"पूर्ण,
	अणु"ADC Mux", "MIC", "Pre-amp MIC"पूर्ण,
	अणु"ADC Mux", "LINEIN", "LINEINL"पूर्ण,
	अणु"ADC Mux", "LINEIN", "LINEINR"पूर्ण,
	अणु"ADC", शून्य, "ADC Mux"पूर्ण,
	अणु"DOUT", शून्य, "ADC"पूर्ण,
	अणु"DAI1 Capture", शून्य, "DOUT"पूर्ण,
	अणु"DAI2 Capture", शून्य, "DOUT"पूर्ण,

	/* Loopback */
	अणु"Loopback", "Switch", "ADC"पूर्ण,
	अणु"DAC", शून्य, "Loopback"पूर्ण,
पूर्ण;

काष्ठा cs4265_clk_para अणु
	u32 mclk;
	u32 rate;
	u8 fm_mode; /* values 1, 2, or 4 */
	u8 mclkभाग;
पूर्ण;

अटल स्थिर काष्ठा cs4265_clk_para clk_map_table[] = अणु
	/*32k*/
	अणु8192000, 32000, 0, 0पूर्ण,
	अणु12288000, 32000, 0, 1पूर्ण,
	अणु16384000, 32000, 0, 2पूर्ण,
	अणु24576000, 32000, 0, 3पूर्ण,
	अणु32768000, 32000, 0, 4पूर्ण,

	/*44.1k*/
	अणु11289600, 44100, 0, 0पूर्ण,
	अणु16934400, 44100, 0, 1पूर्ण,
	अणु22579200, 44100, 0, 2पूर्ण,
	अणु33868000, 44100, 0, 3पूर्ण,
	अणु45158400, 44100, 0, 4पूर्ण,

	/*48k*/
	अणु12288000, 48000, 0, 0पूर्ण,
	अणु18432000, 48000, 0, 1पूर्ण,
	अणु24576000, 48000, 0, 2पूर्ण,
	अणु36864000, 48000, 0, 3पूर्ण,
	अणु49152000, 48000, 0, 4पूर्ण,

	/*64k*/
	अणु8192000, 64000, 1, 0पूर्ण,
	अणु12288000, 64000, 1, 1पूर्ण,
	अणु16934400, 64000, 1, 2पूर्ण,
	अणु24576000, 64000, 1, 3पूर्ण,
	अणु32768000, 64000, 1, 4पूर्ण,

	/* 88.2k */
	अणु11289600, 88200, 1, 0पूर्ण,
	अणु16934400, 88200, 1, 1पूर्ण,
	अणु22579200, 88200, 1, 2पूर्ण,
	अणु33868000, 88200, 1, 3पूर्ण,
	अणु45158400, 88200, 1, 4पूर्ण,

	/* 96k */
	अणु12288000, 96000, 1, 0पूर्ण,
	अणु18432000, 96000, 1, 1पूर्ण,
	अणु24576000, 96000, 1, 2पूर्ण,
	अणु36864000, 96000, 1, 3पूर्ण,
	अणु49152000, 96000, 1, 4पूर्ण,

	/* 128k */
	अणु8192000, 128000, 2, 0पूर्ण,
	अणु12288000, 128000, 2, 1पूर्ण,
	अणु16934400, 128000, 2, 2पूर्ण,
	अणु24576000, 128000, 2, 3पूर्ण,
	अणु32768000, 128000, 2, 4पूर्ण,

	/* 176.4k */
	अणु11289600, 176400, 2, 0पूर्ण,
	अणु16934400, 176400, 2, 1पूर्ण,
	अणु22579200, 176400, 2, 2पूर्ण,
	अणु33868000, 176400, 2, 3पूर्ण,
	अणु49152000, 176400, 2, 4पूर्ण,

	/* 192k */
	अणु12288000, 192000, 2, 0पूर्ण,
	अणु18432000, 192000, 2, 1पूर्ण,
	अणु24576000, 192000, 2, 2पूर्ण,
	अणु36864000, 192000, 2, 3पूर्ण,
	अणु49152000, 192000, 2, 4पूर्ण,
पूर्ण;

अटल पूर्णांक cs4265_get_clk_index(पूर्णांक mclk, पूर्णांक rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(clk_map_table); i++) अणु
		अगर (clk_map_table[i].rate == rate &&
				clk_map_table[i].mclk == mclk)
			वापस i;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cs4265_set_sysclk(काष्ठा snd_soc_dai *codec_dai, पूर्णांक clk_id,
			अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cs4265_निजी *cs4265 = snd_soc_component_get_drvdata(component);
	पूर्णांक i;

	अगर (clk_id != 0) अणु
		dev_err(component->dev, "Invalid clk_id %d\n", clk_id);
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(clk_map_table); i++) अणु
		अगर (clk_map_table[i].mclk == freq) अणु
			cs4265->sysclk = freq;
			वापस 0;
		पूर्ण
	पूर्ण
	cs4265->sysclk = 0;
	dev_err(component->dev, "Invalid freq parameter %d\n", freq);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक cs4265_set_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cs4265_निजी *cs4265 = snd_soc_component_get_drvdata(component);
	u8 अगरace = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		snd_soc_component_update_bits(component, CS4265_ADC_CTL,
				CS4265_ADC_MASTER,
				CS4265_ADC_MASTER);
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		snd_soc_component_update_bits(component, CS4265_ADC_CTL,
				CS4265_ADC_MASTER,
				0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	 /* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगरace |= SND_SOC_DAIFMT_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अगरace |= SND_SOC_DAIFMT_RIGHT_J;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगरace |= SND_SOC_DAIFMT_LEFT_J;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	cs4265->क्रमmat = अगरace;
	वापस 0;
पूर्ण

अटल पूर्णांक cs4265_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	अगर (mute) अणु
		snd_soc_component_update_bits(component, CS4265_DAC_CTL,
			CS4265_DAC_CTL_MUTE,
			CS4265_DAC_CTL_MUTE);
		snd_soc_component_update_bits(component, CS4265_SPDIF_CTL2,
			CS4265_SPDIF_CTL2_MUTE,
			CS4265_SPDIF_CTL2_MUTE);
	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(component, CS4265_DAC_CTL,
			CS4265_DAC_CTL_MUTE,
			0);
		snd_soc_component_update_bits(component, CS4265_SPDIF_CTL2,
			CS4265_SPDIF_CTL2_MUTE,
			0);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cs4265_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_pcm_hw_params *params,
				     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs4265_निजी *cs4265 = snd_soc_component_get_drvdata(component);
	पूर्णांक index;

	अगर (substream->stream == SNDRV_PCM_STREAM_CAPTURE &&
		((cs4265->क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK)
		== SND_SOC_DAIFMT_RIGHT_J))
		वापस -EINVAL;

	index = cs4265_get_clk_index(cs4265->sysclk, params_rate(params));
	अगर (index >= 0) अणु
		snd_soc_component_update_bits(component, CS4265_ADC_CTL,
			CS4265_ADC_FM, clk_map_table[index].fm_mode << 6);
		snd_soc_component_update_bits(component, CS4265_MCLK_FREQ,
			CS4265_MCLK_FREQ_MASK,
			clk_map_table[index].mclkभाग << 4);

	पूर्ण अन्यथा अणु
		dev_err(component->dev, "can't get correct mclk\n");
		वापस -EINVAL;
	पूर्ण

	चयन (cs4265->क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		snd_soc_component_update_bits(component, CS4265_DAC_CTL,
			CS4265_DAC_CTL_DIF, (1 << 4));
		snd_soc_component_update_bits(component, CS4265_ADC_CTL,
			CS4265_ADC_DIF, (1 << 4));
		snd_soc_component_update_bits(component, CS4265_SPDIF_CTL2,
			CS4265_SPDIF_CTL2_DIF, (1 << 6));
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अगर (params_width(params) == 16) अणु
			snd_soc_component_update_bits(component, CS4265_DAC_CTL,
				CS4265_DAC_CTL_DIF, (2 << 4));
			snd_soc_component_update_bits(component, CS4265_SPDIF_CTL2,
				CS4265_SPDIF_CTL2_DIF, (2 << 6));
		पूर्ण अन्यथा अणु
			snd_soc_component_update_bits(component, CS4265_DAC_CTL,
				CS4265_DAC_CTL_DIF, (3 << 4));
			snd_soc_component_update_bits(component, CS4265_SPDIF_CTL2,
				CS4265_SPDIF_CTL2_DIF, (3 << 6));
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		snd_soc_component_update_bits(component, CS4265_DAC_CTL,
			CS4265_DAC_CTL_DIF, 0);
		snd_soc_component_update_bits(component, CS4265_ADC_CTL,
			CS4265_ADC_DIF, 0);
		snd_soc_component_update_bits(component, CS4265_SPDIF_CTL2,
			CS4265_SPDIF_CTL2_DIF, 0);

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cs4265_set_bias_level(काष्ठा snd_soc_component *component,
					क्रमागत snd_soc_bias_level level)
अणु
	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		snd_soc_component_update_bits(component, CS4265_PWRCTL,
			CS4265_PWRCTL_PDN, 0);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		snd_soc_component_update_bits(component, CS4265_PWRCTL,
			CS4265_PWRCTL_PDN,
			CS4265_PWRCTL_PDN);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, CS4265_PWRCTL,
			CS4265_PWRCTL_PDN,
			CS4265_PWRCTL_PDN);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा CS4265_RATES (SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 | \
			SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_64000 | \
			SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000 | \
			SNDRV_PCM_RATE_176400 | SNDRV_PCM_RATE_192000)

#घोषणा CS4265_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_U16_LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_U24_LE | \
			SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_U32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops cs4265_ops = अणु
	.hw_params	= cs4265_pcm_hw_params,
	.mute_stream	= cs4265_mute,
	.set_fmt	= cs4265_set_fmt,
	.set_sysclk	= cs4265_set_sysclk,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver cs4265_dai[] = अणु
	अणु
		.name = "cs4265-dai1",
		.playback = अणु
			.stream_name = "DAI1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = CS4265_RATES,
			.क्रमmats = CS4265_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "DAI1 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = CS4265_RATES,
			.क्रमmats = CS4265_FORMATS,
		पूर्ण,
		.ops = &cs4265_ops,
	पूर्ण,
	अणु
		.name = "cs4265-dai2",
		.playback = अणु
			.stream_name = "DAI2 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = CS4265_RATES,
			.क्रमmats = CS4265_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name = "DAI2 Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = CS4265_RATES,
			.क्रमmats = CS4265_FORMATS,
		पूर्ण,
		.ops = &cs4265_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_cs4265 = अणु
	.set_bias_level		= cs4265_set_bias_level,
	.controls		= cs4265_snd_controls,
	.num_controls		= ARRAY_SIZE(cs4265_snd_controls),
	.dapm_widमाला_लो		= cs4265_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(cs4265_dapm_widमाला_लो),
	.dapm_routes		= cs4265_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(cs4265_audio_map),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config cs4265_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = CS4265_MAX_REGISTER,
	.reg_शेषs = cs4265_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(cs4265_reg_शेषs),
	.पढ़ोable_reg = cs4265_पढ़ोable_रेजिस्टर,
	.अस्थिर_reg = cs4265_अस्थिर_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक cs4265_i2c_probe(काष्ठा i2c_client *i2c_client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cs4265_निजी *cs4265;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक devid = 0;
	अचिन्हित पूर्णांक reg;

	cs4265 = devm_kzalloc(&i2c_client->dev, माप(काष्ठा cs4265_निजी),
			       GFP_KERNEL);
	अगर (cs4265 == शून्य)
		वापस -ENOMEM;

	cs4265->regmap = devm_regmap_init_i2c(i2c_client, &cs4265_regmap);
	अगर (IS_ERR(cs4265->regmap)) अणु
		ret = PTR_ERR(cs4265->regmap);
		dev_err(&i2c_client->dev, "regmap_init() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	cs4265->reset_gpio = devm_gpiod_get_optional(&i2c_client->dev,
		"reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(cs4265->reset_gpio))
		वापस PTR_ERR(cs4265->reset_gpio);

	अगर (cs4265->reset_gpio) अणु
		mdelay(1);
		gpiod_set_value_cansleep(cs4265->reset_gpio, 1);
	पूर्ण

	i2c_set_clientdata(i2c_client, cs4265);

	ret = regmap_पढ़ो(cs4265->regmap, CS4265_CHIP_ID, &reg);
	devid = reg & CS4265_CHIP_ID_MASK;
	अगर (devid != CS4265_CHIP_ID_VAL) अणु
		ret = -ENODEV;
		dev_err(&i2c_client->dev,
			"CS4265 Device ID (%X). Expected %X\n",
			devid, CS4265_CHIP_ID);
		वापस ret;
	पूर्ण
	dev_info(&i2c_client->dev,
		"CS4265 Version %x\n",
			reg & CS4265_REV_ID_MASK);

	regmap_ग_लिखो(cs4265->regmap, CS4265_PWRCTL, 0x0F);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c_client->dev,
			&soc_component_cs4265, cs4265_dai,
			ARRAY_SIZE(cs4265_dai));
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id cs4265_of_match[] = अणु
	अणु .compatible = "cirrus,cs4265", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cs4265_of_match);

अटल स्थिर काष्ठा i2c_device_id cs4265_id[] = अणु
	अणु "cs4265", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cs4265_id);

अटल काष्ठा i2c_driver cs4265_i2c_driver = अणु
	.driver = अणु
		.name = "cs4265",
		.of_match_table = cs4265_of_match,
	पूर्ण,
	.id_table = cs4265_id,
	.probe =    cs4265_i2c_probe,
पूर्ण;

module_i2c_driver(cs4265_i2c_driver);

MODULE_DESCRIPTION("ASoC CS4265 driver");
MODULE_AUTHOR("Paul Handrigan, Cirrus Logic Inc, <paul.handrigan@cirrus.com>");
MODULE_LICENSE("GPL");
