<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 LAPIS Semiconductor Co., Ltd.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश "ml26124.h"

#घोषणा DVOL_CTL_DVMUTE_ON		BIT(4)	/* Digital volume MUTE On */
#घोषणा DVOL_CTL_DVMUTE_OFF		0	/* Digital volume MUTE Off */
#घोषणा ML26124_SAI_NO_DELAY	BIT(1)
#घोषणा ML26124_SAI_FRAME_SYNC	(BIT(5) | BIT(0)) /* For mono (Telecodec) */
#घोषणा ML26134_CACHESIZE 212
#घोषणा ML26124_VMID	BIT(1)
#घोषणा ML26124_RATES (SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_32000 |\
		       SNDRV_PCM_RATE_48000)
#घोषणा ML26124_FORMATS (SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE |\
			 SNDRV_PCM_FMTBIT_S32_LE)
#घोषणा ML26124_NUM_REGISTER ML26134_CACHESIZE

काष्ठा ml26124_priv अणु
	u32 mclk;
	u32 rate;
	काष्ठा regmap *regmap;
	पूर्णांक clk_in;
	काष्ठा snd_pcm_substream *substream;
पूर्ण;

काष्ठा clk_coeff अणु
	u32 mclk;
	u32 rate;
	u8 pllnl;
	u8 pllnh;
	u8 pllml;
	u8 pllmh;
	u8 plद_भाग;
पूर्ण;

/* ML26124 configuration */
अटल स्थिर DECLARE_TLV_DB_SCALE(digital_tlv, -7150, 50, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(alclvl, -2250, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(mingain, -1200, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(maxgain, -675, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(boost_vol, -1200, 75, 0);

अटल स्थिर अक्षर * स्थिर ml26124_companding[] = अणु"16bit PCM", "u-law",
						  "A-law"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(ml26124_adc_companding_क्रमागत,
			    ML26124_SAI_TRANS_CTL, 6, ml26124_companding);

अटल SOC_ENUM_SINGLE_DECL(ml26124_dac_companding_क्रमागत,
			    ML26124_SAI_RCV_CTL, 6, ml26124_companding);

अटल स्थिर काष्ठा snd_kcontrol_new ml26124_snd_controls[] = अणु
	SOC_SINGLE_TLV("Capture Digital Volume", ML26124_RECORD_DIG_VOL, 0,
			0xff, 1, digital_tlv),
	SOC_SINGLE_TLV("Playback Digital Volume", ML26124_PLBAK_DIG_VOL, 0,
			0xff, 1, digital_tlv),
	SOC_SINGLE_TLV("Digital Boost Volume", ML26124_DIGI_BOOST_VOL, 0,
			0x3f, 0, boost_vol),
	SOC_SINGLE_TLV("EQ Band0 Volume", ML26124_EQ_GAIN_BRAND0, 0,
			0xff, 1, digital_tlv),
	SOC_SINGLE_TLV("EQ Band1 Volume", ML26124_EQ_GAIN_BRAND1, 0,
			0xff, 1, digital_tlv),
	SOC_SINGLE_TLV("EQ Band2 Volume", ML26124_EQ_GAIN_BRAND2, 0,
			0xff, 1, digital_tlv),
	SOC_SINGLE_TLV("EQ Band3 Volume", ML26124_EQ_GAIN_BRAND3, 0,
			0xff, 1, digital_tlv),
	SOC_SINGLE_TLV("EQ Band4 Volume", ML26124_EQ_GAIN_BRAND4, 0,
			0xff, 1, digital_tlv),
	SOC_SINGLE_TLV("ALC Target Level", ML26124_ALC_TARGET_LEV, 0,
			0xf, 1, alclvl),
	SOC_SINGLE_TLV("ALC Min Input Volume", ML26124_ALC_MAXMIN_GAIN, 0,
			7, 0, mingain),
	SOC_SINGLE_TLV("ALC Max Input Volume", ML26124_ALC_MAXMIN_GAIN, 4,
			7, 1, maxgain),
	SOC_SINGLE_TLV("Playback Limiter Min Input Volume",
			ML26124_PL_MAXMIN_GAIN, 0, 7, 0, mingain),
	SOC_SINGLE_TLV("Playback Limiter Max Input Volume",
			ML26124_PL_MAXMIN_GAIN, 4, 7, 1, maxgain),
	SOC_SINGLE_TLV("Playback Boost Volume", ML26124_PLYBAK_BOST_VOL, 0,
			0x3f, 0, boost_vol),
	SOC_SINGLE("DC High Pass Filter Switch", ML26124_FILTER_EN, 0, 1, 0),
	SOC_SINGLE("Noise High Pass Filter Switch", ML26124_FILTER_EN, 1, 1, 0),
	SOC_SINGLE("ZC Switch", ML26124_PW_ZCCMP_PW_MNG, 1,
		    1, 0),
	SOC_SINGLE("EQ Band0 Switch", ML26124_FILTER_EN, 2, 1, 0),
	SOC_SINGLE("EQ Band1 Switch", ML26124_FILTER_EN, 3, 1, 0),
	SOC_SINGLE("EQ Band2 Switch", ML26124_FILTER_EN, 4, 1, 0),
	SOC_SINGLE("EQ Band3 Switch", ML26124_FILTER_EN, 5, 1, 0),
	SOC_SINGLE("EQ Band4 Switch", ML26124_FILTER_EN, 6, 1, 0),
	SOC_SINGLE("Play Limiter", ML26124_DVOL_CTL, 0, 1, 0),
	SOC_SINGLE("Capture Limiter", ML26124_DVOL_CTL, 1, 1, 0),
	SOC_SINGLE("Digital Volume Fade Switch", ML26124_DVOL_CTL, 3, 1, 0),
	SOC_SINGLE("Digital Switch", ML26124_DVOL_CTL, 4, 1, 0),
	SOC_ENUM("DAC Companding", ml26124_dac_companding_क्रमागत),
	SOC_ENUM("ADC Companding", ml26124_adc_companding_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new ml26124_output_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("DAC Switch", ML26124_SPK_AMP_OUT, 1, 1, 0),
	SOC_DAPM_SINGLE("Line in loopback Switch", ML26124_SPK_AMP_OUT, 3, 1,
			 0),
	SOC_DAPM_SINGLE("PGA Switch", ML26124_SPK_AMP_OUT, 5, 1, 0),
पूर्ण;

/* Input mux */
अटल स्थिर अक्षर * स्थिर ml26124_input_select[] = अणु"Analog MIC SingleEnded in",
				"Digital MIC in", "Analog MIC Differential in"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(ml26124_insel_क्रमागत,
			    ML26124_MIC_IF_CTL, 0, ml26124_input_select);

अटल स्थिर काष्ठा snd_kcontrol_new ml26124_input_mux_controls =
	SOC_DAPM_ENUM("Input Select", ml26124_insel_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new ml26124_line_control =
	SOC_DAPM_SINGLE("Switch", ML26124_PW_LOUT_PW_MNG, 1, 1, 0);

अटल स्थिर काष्ठा snd_soc_dapm_widget ml26124_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("MCLKEN", ML26124_CLK_EN, 0, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLLEN", ML26124_CLK_EN, 1, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("PLLOE", ML26124_CLK_EN, 2, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MICBIAS", ML26124_PW_REF_PW_MNG, 2, 0, शून्य, 0),
	SND_SOC_DAPM_MIXER("Output Mixer", SND_SOC_NOPM, 0, 0,
			   &ml26124_output_mixer_controls[0],
			   ARRAY_SIZE(ml26124_output_mixer_controls)),
	SND_SOC_DAPM_DAC("DAC", "Playback", ML26124_PW_DAC_PW_MNG, 1, 0),
	SND_SOC_DAPM_ADC("ADC", "Capture", ML26124_PW_IN_PW_MNG, 1, 0),
	SND_SOC_DAPM_PGA("PGA", ML26124_PW_IN_PW_MNG, 3, 0, शून्य, 0),
	SND_SOC_DAPM_MUX("Input Mux", SND_SOC_NOPM, 0, 0,
			  &ml26124_input_mux_controls),
	SND_SOC_DAPM_SWITCH("Line Out Enable", SND_SOC_NOPM, 0, 0,
			     &ml26124_line_control),
	SND_SOC_DAPM_INPUT("MDIN"),
	SND_SOC_DAPM_INPUT("MIN"),
	SND_SOC_DAPM_INPUT("LIN"),
	SND_SOC_DAPM_OUTPUT("SPOUT"),
	SND_SOC_DAPM_OUTPUT("LOUT"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ml26124_पूर्णांकercon[] = अणु
	/* Supply */
	अणु"DAC", शून्य, "MCLKEN"पूर्ण,
	अणु"ADC", शून्य, "MCLKEN"पूर्ण,
	अणु"DAC", शून्य, "PLLEN"पूर्ण,
	अणु"ADC", शून्य, "PLLEN"पूर्ण,
	अणु"DAC", शून्य, "PLLOE"पूर्ण,
	अणु"ADC", शून्य, "PLLOE"पूर्ण,

	/* output mixer */
	अणु"Output Mixer", "DAC Switch", "DAC"पूर्ण,
	अणु"Output Mixer", "Line in loopback Switch", "LIN"पूर्ण,

	/* outमाला_दो */
	अणु"LOUT", शून्य, "Output Mixer"पूर्ण,
	अणु"SPOUT", शून्य, "Output Mixer"पूर्ण,
	अणु"Line Out Enable", शून्य, "LOUT"पूर्ण,

	/* input */
	अणु"ADC", शून्य, "Input Mux"पूर्ण,
	अणु"Input Mux", "Analog MIC SingleEnded in", "PGA"पूर्ण,
	अणु"Input Mux", "Analog MIC Differential in", "PGA"पूर्ण,
	अणु"PGA", शून्य, "MIN"पूर्ण,
पूर्ण;

/* PLLOutputFreq(Hz) = InputMclkFreq(Hz) * PLLM / (PLLN * PLLDIV) */
अटल स्थिर काष्ठा clk_coeff coeff_भाग[] = अणु
	अणु12288000, 16000, 0xc, 0x0, 0x20, 0x0, 0x4पूर्ण,
	अणु12288000, 32000, 0xc, 0x0, 0x20, 0x0, 0x4पूर्ण,
	अणु12288000, 48000, 0xc, 0x0, 0x30, 0x0, 0x4पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष ml26124_reg[] = अणु
	/* CLOCK control Register */
	अणु0x00, 0x00 पूर्ण,	/* Sampling Rate */
	अणु0x02, 0x00पूर्ण,	/* PLL NL */
	अणु0x04, 0x00पूर्ण,	/* PLLNH */
	अणु0x06, 0x00पूर्ण,	/* PLLML */
	अणु0x08, 0x00पूर्ण,	/* MLLMH */
	अणु0x0a, 0x00पूर्ण,	/* PLLDIV */
	अणु0x0c, 0x00पूर्ण,	/* Clock Enable */
	अणु0x0e, 0x00पूर्ण,	/* CLK Input/Output Control */

	/* System Control Register */
	अणु0x10, 0x00पूर्ण,	/* Software RESET */
	अणु0x12, 0x00पूर्ण,	/* Record/Playback Run */
	अणु0x14, 0x00पूर्ण,	/* Mic Input/Output control */

	/* Power Management Register */
	अणु0x20, 0x00पूर्ण,	/* Reference Power Management */
	अणु0x22, 0x00पूर्ण,	/* Input Power Management */
	अणु0x24, 0x00पूर्ण,	/* DAC Power Management */
	अणु0x26, 0x00पूर्ण,	/* SP-AMP Power Management */
	अणु0x28, 0x00पूर्ण,	/* LINEOUT Power Management */
	अणु0x2a, 0x00पूर्ण,	/* VIDEO Power Management */
	अणु0x2e, 0x00पूर्ण,	/* AC-CMP Power Management */

	/* Analog reference Control Register */
	अणु0x30, 0x04पूर्ण,	/* MICBIAS Voltage Control */

	/* Input/Output Amplअगरier Control Register */
	अणु0x32, 0x10पूर्ण,	/* MIC Input Volume */
	अणु0x38, 0x00पूर्ण,	/* Mic Boost Volume */
	अणु0x3a, 0x33पूर्ण,	/* Speaker AMP Volume */
	अणु0x48, 0x00पूर्ण,	/* AMP Volume Control Function Enable */
	अणु0x4a, 0x00पूर्ण,	/* Amplअगरier Volume Fader Control */

	/* Analog Path Control Register */
	अणु0x54, 0x00पूर्ण,	/* Speaker AMP Output Control */
	अणु0x5a, 0x00पूर्ण,	/* Mic IF Control */
	अणु0xe8, 0x01पूर्ण,	/* Mic Select Control */

	/* Audio Interface Control Register */
	अणु0x60, 0x00पूर्ण,	/* SAI-Trans Control */
	अणु0x62, 0x00पूर्ण,	/* SAI-Receive Control */
	अणु0x64, 0x00पूर्ण,	/* SAI Mode select */

	/* DSP Control Register */
	अणु0x66, 0x01पूर्ण,	/* Filter Func Enable */
	अणु0x68, 0x00पूर्ण,	/* Volume Control Func Enable */
	अणु0x6A, 0x00पूर्ण,	/* Mixer & Volume Control*/
	अणु0x6C, 0xffपूर्ण,	/* Record Digital Volume */
	अणु0x70, 0xffपूर्ण,	/* Playback Digital Volume */
	अणु0x72, 0x10पूर्ण,	/* Digital Boost Volume */
	अणु0x74, 0xe7पूर्ण,	/* EQ gain Band0 */
	अणु0x76, 0xe7पूर्ण,	/* EQ gain Band1 */
	अणु0x78, 0xe7पूर्ण,	/* EQ gain Band2 */
	अणु0x7A, 0xe7पूर्ण,	/* EQ gain Band3 */
	अणु0x7C, 0xe7पूर्ण,	/* EQ gain Band4 */
	अणु0x7E, 0x00पूर्ण,	/* HPF2 CutOff*/
	अणु0x80, 0x00पूर्ण,	/* EQ Band0 Coef0L */
	अणु0x82, 0x00पूर्ण,	/* EQ Band0 Coef0H */
	अणु0x84, 0x00पूर्ण,	/* EQ Band0 Coef0L */
	अणु0x86, 0x00पूर्ण,	/* EQ Band0 Coef0H */
	अणु0x88, 0x00पूर्ण,	/* EQ Band1 Coef0L */
	अणु0x8A, 0x00पूर्ण,	/* EQ Band1 Coef0H */
	अणु0x8C, 0x00पूर्ण,	/* EQ Band1 Coef0L */
	अणु0x8E, 0x00पूर्ण,	/* EQ Band1 Coef0H */
	अणु0x90, 0x00पूर्ण,	/* EQ Band2 Coef0L */
	अणु0x92, 0x00पूर्ण,	/* EQ Band2 Coef0H */
	अणु0x94, 0x00पूर्ण,	/* EQ Band2 Coef0L */
	अणु0x96, 0x00पूर्ण,	/* EQ Band2 Coef0H */
	अणु0x98, 0x00पूर्ण,	/* EQ Band3 Coef0L */
	अणु0x9A, 0x00पूर्ण,	/* EQ Band3 Coef0H */
	अणु0x9C, 0x00पूर्ण,	/* EQ Band3 Coef0L */
	अणु0x9E, 0x00पूर्ण,	/* EQ Band3 Coef0H */
	अणु0xA0, 0x00पूर्ण,	/* EQ Band4 Coef0L */
	अणु0xA2, 0x00पूर्ण,	/* EQ Band4 Coef0H */
	अणु0xA4, 0x00पूर्ण,	/* EQ Band4 Coef0L */
	अणु0xA6, 0x00पूर्ण,	/* EQ Band4 Coef0H */

	/* ALC Control Register */
	अणु0xb0, 0x00पूर्ण,	/* ALC Mode */
	अणु0xb2, 0x02पूर्ण,	/* ALC Attack Time */
	अणु0xb4, 0x03पूर्ण,	/* ALC Decay Time */
	अणु0xb6, 0x00पूर्ण,	/* ALC Hold Time */
	अणु0xb8, 0x0bपूर्ण,	/* ALC Target Level */
	अणु0xba, 0x70पूर्ण,	/* ALC Max/Min Gain */
	अणु0xbc, 0x00पूर्ण,	/* Noise Gate Threshold */
	अणु0xbe, 0x00पूर्ण,	/* ALC ZeroCross TimeOut */

	/* Playback Limiter Control Register */
	अणु0xc0, 0x04पूर्ण,	/* PL Attack Time */
	अणु0xc2, 0x05पूर्ण,	/* PL Decay Time */
	अणु0xc4, 0x0dपूर्ण,	/* PL Target Level */
	अणु0xc6, 0x70पूर्ण,	/* PL Max/Min Gain */
	अणु0xc8, 0x10पूर्ण,	/* Playback Boost Volume */
	अणु0xca, 0x00पूर्ण,	/* PL ZeroCross TimeOut */

	/* Video Amplअगरier Control Register */
	अणु0xd0, 0x01पूर्ण,	/* VIDEO AMP Gain Control */
	अणु0xd2, 0x01पूर्ण,	/* VIDEO AMP Setup 1 */
	अणु0xd4, 0x01पूर्ण,	/* VIDEO AMP Control2 */
पूर्ण;

/* Get sampling rate value of sampling rate setting रेजिस्टर (0x0) */
अटल अंतरभूत पूर्णांक get_srate(पूर्णांक rate)
अणु
	पूर्णांक srate;

	चयन (rate) अणु
	हाल 16000:
		srate = 3;
		अवरोध;
	हाल 32000:
		srate = 6;
		अवरोध;
	हाल 48000:
		srate = 8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस srate;
पूर्ण

अटल अंतरभूत पूर्णांक get_coeff(पूर्णांक mclk, पूर्णांक rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(coeff_भाग); i++) अणु
		अगर (coeff_भाग[i].rate == rate && coeff_भाग[i].mclk == mclk)
			वापस i;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ml26124_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *hw_params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा ml26124_priv *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक i = get_coeff(priv->mclk, params_rate(hw_params));
	पूर्णांक srate;

	अगर (i < 0)
		वापस i;
	priv->substream = substream;
	priv->rate = params_rate(hw_params);

	अगर (priv->clk_in) अणु
		चयन (priv->mclk / params_rate(hw_params)) अणु
		हाल 256:
			snd_soc_component_update_bits(component, ML26124_CLK_CTL,
					    BIT(0) | BIT(1), 1);
			अवरोध;
		हाल 512:
			snd_soc_component_update_bits(component, ML26124_CLK_CTL,
					    BIT(0) | BIT(1), 2);
			अवरोध;
		हाल 1024:
			snd_soc_component_update_bits(component, ML26124_CLK_CTL,
					    BIT(0) | BIT(1), 3);
			अवरोध;
		शेष:
			dev_err(component->dev, "Unsupported MCLKI\n");
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(component, ML26124_CLK_CTL,
				    BIT(0) | BIT(1), 0);
	पूर्ण

	srate = get_srate(params_rate(hw_params));
	अगर (srate < 0)
		वापस srate;

	snd_soc_component_update_bits(component, ML26124_SMPLING_RATE, 0xf, srate);
	snd_soc_component_update_bits(component, ML26124_PLLNL, 0xff, coeff_भाग[i].pllnl);
	snd_soc_component_update_bits(component, ML26124_PLLNH, 0x1, coeff_भाग[i].pllnh);
	snd_soc_component_update_bits(component, ML26124_PLLML, 0xff, coeff_भाग[i].pllml);
	snd_soc_component_update_bits(component, ML26124_PLLMH, 0x3f, coeff_भाग[i].pllmh);
	snd_soc_component_update_bits(component, ML26124_PLLDIV, 0x1f, coeff_भाग[i].plद_भाग);

	वापस 0;
पूर्ण

अटल पूर्णांक ml26124_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा ml26124_priv *priv = snd_soc_component_get_drvdata(component);

	चयन (priv->substream->stream) अणु
	हाल SNDRV_PCM_STREAM_CAPTURE:
		snd_soc_component_update_bits(component, ML26124_REC_PLYBAK_RUN, BIT(0), 1);
		अवरोध;
	हाल SNDRV_PCM_STREAM_PLAYBACK:
		snd_soc_component_update_bits(component, ML26124_REC_PLYBAK_RUN, BIT(1), 2);
		अवरोध;
	पूर्ण

	अगर (mute)
		snd_soc_component_update_bits(component, ML26124_DVOL_CTL, BIT(4),
				    DVOL_CTL_DVMUTE_ON);
	अन्यथा
		snd_soc_component_update_bits(component, ML26124_DVOL_CTL, BIT(4),
				    DVOL_CTL_DVMUTE_OFF);

	वापस 0;
पूर्ण

अटल पूर्णांक ml26124_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	अचिन्हित अक्षर mode;
	काष्ठा snd_soc_component *component = codec_dai->component;

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		mode = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		mode = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	snd_soc_component_update_bits(component, ML26124_SAI_MODE_SEL, BIT(0), mode);

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ml26124_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा ml26124_priv *priv = snd_soc_component_get_drvdata(component);

	चयन (clk_id) अणु
	हाल ML26124_USE_PLLOUT:
		priv->clk_in = ML26124_USE_PLLOUT;
		अवरोध;
	हाल ML26124_USE_MCLKI:
		priv->clk_in = ML26124_USE_MCLKI;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	priv->mclk = freq;

	वापस 0;
पूर्ण

अटल पूर्णांक ml26124_set_bias_level(काष्ठा snd_soc_component *component,
		क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा ml26124_priv *priv = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		snd_soc_component_update_bits(component, ML26124_PW_SPAMP_PW_MNG,
				    ML26124_R26_MASK, ML26124_BLT_PREAMP_ON);
		msleep(100);
		snd_soc_component_update_bits(component, ML26124_PW_SPAMP_PW_MNG,
				    ML26124_R26_MASK,
				    ML26124_MICBEN_ON | ML26124_BLT_ALL_ON);
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		/* VMID ON */
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			snd_soc_component_update_bits(component, ML26124_PW_REF_PW_MNG,
					    ML26124_VMID, ML26124_VMID);
			msleep(500);
			regcache_sync(priv->regmap);
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		/* VMID OFF */
		snd_soc_component_update_bits(component, ML26124_PW_REF_PW_MNG,
				    ML26124_VMID, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops ml26124_dai_ops = अणु
	.hw_params	= ml26124_hw_params,
	.mute_stream	= ml26124_mute,
	.set_fmt	= ml26124_set_dai_fmt,
	.set_sysclk	= ml26124_set_dai_sysclk,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver ml26124_dai = अणु
	.name = "ml26124-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = ML26124_RATES,
		.क्रमmats = ML26124_FORMATS,पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = ML26124_RATES,
		.क्रमmats = ML26124_FORMATS,पूर्ण,
	.ops = &ml26124_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल पूर्णांक ml26124_probe(काष्ठा snd_soc_component *component)
अणु
	/* Software Reset */
	snd_soc_component_update_bits(component, ML26124_SW_RST, 0x01, 1);
	snd_soc_component_update_bits(component, ML26124_SW_RST, 0x01, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_ml26124 = अणु
	.probe			= ml26124_probe,
	.set_bias_level		= ml26124_set_bias_level,
	.controls		= ml26124_snd_controls,
	.num_controls		= ARRAY_SIZE(ml26124_snd_controls),
	.dapm_widमाला_लो		= ml26124_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ml26124_dapm_widमाला_लो),
	.dapm_routes		= ml26124_पूर्णांकercon,
	.num_dapm_routes	= ARRAY_SIZE(ml26124_पूर्णांकercon),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ml26124_i2c_regmap = अणु
	.val_bits = 8,
	.reg_bits = 8,
	.max_रेजिस्टर = ML26124_NUM_REGISTER,
	.reg_शेषs = ml26124_reg,
	.num_reg_शेषs = ARRAY_SIZE(ml26124_reg),
	.cache_type = REGCACHE_RBTREE,
	.ग_लिखो_flag_mask = 0x01,
पूर्ण;

अटल पूर्णांक ml26124_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ml26124_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(&i2c->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, priv);

	priv->regmap = devm_regmap_init_i2c(i2c, &ml26124_i2c_regmap);
	अगर (IS_ERR(priv->regmap)) अणु
		ret = PTR_ERR(priv->regmap);
		dev_err(&i2c->dev, "regmap_init_i2c() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_ml26124, &ml26124_dai, 1);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ml26124_i2c_id[] = अणु
	अणु "ml26124", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ml26124_i2c_id);

अटल काष्ठा i2c_driver ml26124_i2c_driver = अणु
	.driver = अणु
		.name = "ml26124",
	पूर्ण,
	.probe = ml26124_i2c_probe,
	.id_table = ml26124_i2c_id,
पूर्ण;

module_i2c_driver(ml26124_i2c_driver);

MODULE_AUTHOR("Tomoya MORINAGA <tomoya.rohm@gmail.com>");
MODULE_DESCRIPTION("LAPIS Semiconductor ML26124 ALSA SoC codec driver");
MODULE_LICENSE("GPL");
