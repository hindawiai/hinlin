<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ALSA SoC CPCAP codec driver
 *
 * Copyright (C) 2017 - 2018 Sebastian Reichel <sre@kernel.org>
 *
 * Very loosely based on original driver from Motorola:
 * Copyright (C) 2007 - 2009 Motorola, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/motorola-cpcap.h>
#समावेश <sound/core.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

/* Register 512 CPCAP_REG_VAUDIOC --- Audio Regulator and Bias Voltage */
#घोषणा CPCAP_BIT_AUDIO_LOW_PWR           6
#घोषणा CPCAP_BIT_AUD_LOWPWR_SPEED        5
#घोषणा CPCAP_BIT_VAUDIOPRISTBY           4
#घोषणा CPCAP_BIT_VAUDIO_MODE1            2
#घोषणा CPCAP_BIT_VAUDIO_MODE0            1
#घोषणा CPCAP_BIT_V_AUDIO_EN              0

/* Register 513 CPCAP_REG_CC     --- CODEC */
#घोषणा CPCAP_BIT_CDC_CLK2                15
#घोषणा CPCAP_BIT_CDC_CLK1                14
#घोषणा CPCAP_BIT_CDC_CLK0                13
#घोषणा CPCAP_BIT_CDC_SR3                 12
#घोषणा CPCAP_BIT_CDC_SR2                 11
#घोषणा CPCAP_BIT_CDC_SR1                 10
#घोषणा CPCAP_BIT_CDC_SR0                 9
#घोषणा CPCAP_BIT_CDC_CLOCK_TREE_RESET    8
#घोषणा CPCAP_BIT_MIC2_CDC_EN             7
#घोषणा CPCAP_BIT_CDC_EN_RX               6
#घोषणा CPCAP_BIT_DF_RESET                5
#घोषणा CPCAP_BIT_MIC1_CDC_EN             4
#घोषणा CPCAP_BIT_AUDOHPF_1		  3
#घोषणा CPCAP_BIT_AUDOHPF_0		  2
#घोषणा CPCAP_BIT_AUDIHPF_1		  1
#घोषणा CPCAP_BIT_AUDIHPF_0		  0

/* Register 514 CPCAP_REG_CDI    --- CODEC Digital Audio Interface */
#घोषणा CPCAP_BIT_CDC_PLL_SEL             15
#घोषणा CPCAP_BIT_CLK_IN_SEL              13
#घोषणा CPCAP_BIT_DIG_AUD_IN              12
#घोषणा CPCAP_BIT_CDC_CLK_EN              11
#घोषणा CPCAP_BIT_CDC_DIG_AUD_FS1         10
#घोषणा CPCAP_BIT_CDC_DIG_AUD_FS0         9
#घोषणा CPCAP_BIT_MIC2_TIMESLOT2          8
#घोषणा CPCAP_BIT_MIC2_TIMESLOT1          7
#घोषणा CPCAP_BIT_MIC2_TIMESLOT0          6
#घोषणा CPCAP_BIT_MIC1_RX_TIMESLOT2       5
#घोषणा CPCAP_BIT_MIC1_RX_TIMESLOT1       4
#घोषणा CPCAP_BIT_MIC1_RX_TIMESLOT0       3
#घोषणा CPCAP_BIT_FS_INV                  2
#घोषणा CPCAP_BIT_CLK_INV                 1
#घोषणा CPCAP_BIT_SMB_CDC                 0

/* Register 515 CPCAP_REG_SDAC   --- Stereo DAC */
#घोषणा CPCAP_BIT_FSYNC_CLK_IN_COMMON     11
#घोषणा CPCAP_BIT_SLAVE_PLL_CLK_INPUT     10
#घोषणा CPCAP_BIT_ST_CLOCK_TREE_RESET     9
#घोषणा CPCAP_BIT_DF_RESET_ST_DAC         8
#घोषणा CPCAP_BIT_ST_SR3                  7
#घोषणा CPCAP_BIT_ST_SR2                  6
#घोषणा CPCAP_BIT_ST_SR1                  5
#घोषणा CPCAP_BIT_ST_SR0                  4
#घोषणा CPCAP_BIT_ST_DAC_CLK2             3
#घोषणा CPCAP_BIT_ST_DAC_CLK1             2
#घोषणा CPCAP_BIT_ST_DAC_CLK0             1
#घोषणा CPCAP_BIT_ST_DAC_EN               0

/* Register 516 CPCAP_REG_SDACDI --- Stereo DAC Digital Audio Interface */
#घोषणा CPCAP_BIT_ST_L_TIMESLOT2          13
#घोषणा CPCAP_BIT_ST_L_TIMESLOT1          12
#घोषणा CPCAP_BIT_ST_L_TIMESLOT0          11
#घोषणा CPCAP_BIT_ST_R_TIMESLOT2          10
#घोषणा CPCAP_BIT_ST_R_TIMESLOT1          9
#घोषणा CPCAP_BIT_ST_R_TIMESLOT0          8
#घोषणा CPCAP_BIT_ST_DAC_CLK_IN_SEL       7
#घोषणा CPCAP_BIT_ST_FS_INV               6
#घोषणा CPCAP_BIT_ST_CLK_INV              5
#घोषणा CPCAP_BIT_ST_DIG_AUD_FS1          4
#घोषणा CPCAP_BIT_ST_DIG_AUD_FS0          3
#घोषणा CPCAP_BIT_DIG_AUD_IN_ST_DAC       2
#घोषणा CPCAP_BIT_ST_CLK_EN               1
#घोषणा CPCAP_BIT_SMB_ST_DAC              0

/* Register 517 CPCAP_REG_TXI    --- TX Interface */
#घोषणा CPCAP_BIT_PTT_TH		15
#घोषणा CPCAP_BIT_PTT_CMP_EN		14
#घोषणा CPCAP_BIT_HS_ID_TX		13
#घोषणा CPCAP_BIT_MB_ON2		12
#घोषणा CPCAP_BIT_MB_ON1L		11
#घोषणा CPCAP_BIT_MB_ON1R		10
#घोषणा CPCAP_BIT_RX_L_ENCODE		9
#घोषणा CPCAP_BIT_RX_R_ENCODE		8
#घोषणा CPCAP_BIT_MIC2_MUX		7
#घोषणा CPCAP_BIT_MIC2_PGA_EN		6
#घोषणा CPCAP_BIT_CDET_DIS		5
#घोषणा CPCAP_BIT_EMU_MIC_MUX		4
#घोषणा CPCAP_BIT_HS_MIC_MUX		3
#घोषणा CPCAP_BIT_MIC1_MUX		2
#घोषणा CPCAP_BIT_MIC1_PGA_EN		1
#घोषणा CPCAP_BIT_DLM			0

/* Register 518 CPCAP_REG_TXMP   --- Mic Gain */
#घोषणा CPCAP_BIT_MB_BIAS_R1              11
#घोषणा CPCAP_BIT_MB_BIAS_R0              10
#घोषणा CPCAP_BIT_MIC2_GAIN_4             9
#घोषणा CPCAP_BIT_MIC2_GAIN_3             8
#घोषणा CPCAP_BIT_MIC2_GAIN_2             7
#घोषणा CPCAP_BIT_MIC2_GAIN_1             6
#घोषणा CPCAP_BIT_MIC2_GAIN_0             5
#घोषणा CPCAP_BIT_MIC1_GAIN_4             4
#घोषणा CPCAP_BIT_MIC1_GAIN_3             3
#घोषणा CPCAP_BIT_MIC1_GAIN_2             2
#घोषणा CPCAP_BIT_MIC1_GAIN_1             1
#घोषणा CPCAP_BIT_MIC1_GAIN_0             0

/* Register 519 CPCAP_REG_RXOA   --- RX Output Amplअगरier */
#घोषणा CPCAP_BIT_UNUSED_519_15		15
#घोषणा CPCAP_BIT_UNUSED_519_14		14
#घोषणा CPCAP_BIT_UNUSED_519_13		13
#घोषणा CPCAP_BIT_STDAC_LOW_PWR_DISABLE	12
#घोषणा CPCAP_BIT_HS_LOW_PWR		11
#घोषणा CPCAP_BIT_HS_ID_RX		10
#घोषणा CPCAP_BIT_ST_HS_CP_EN		9
#घोषणा CPCAP_BIT_EMU_SPKR_R_EN		8
#घोषणा CPCAP_BIT_EMU_SPKR_L_EN		7
#घोषणा CPCAP_BIT_HS_L_EN		6
#घोषणा CPCAP_BIT_HS_R_EN		5
#घोषणा CPCAP_BIT_A4_LINEOUT_L_EN	4
#घोषणा CPCAP_BIT_A4_LINEOUT_R_EN	3
#घोषणा CPCAP_BIT_A2_LDSP_L_EN		2
#घोषणा CPCAP_BIT_A2_LDSP_R_EN		1
#घोषणा CPCAP_BIT_A1_EAR_EN		0

/* Register 520 CPCAP_REG_RXVC   --- RX Volume Control */
#घोषणा CPCAP_BIT_VOL_EXT3                15
#घोषणा CPCAP_BIT_VOL_EXT2                14
#घोषणा CPCAP_BIT_VOL_EXT1                13
#घोषणा CPCAP_BIT_VOL_EXT0                12
#घोषणा CPCAP_BIT_VOL_DAC3                11
#घोषणा CPCAP_BIT_VOL_DAC2                10
#घोषणा CPCAP_BIT_VOL_DAC1                9
#घोषणा CPCAP_BIT_VOL_DAC0                8
#घोषणा CPCAP_BIT_VOL_DAC_LSB_1dB1        7
#घोषणा CPCAP_BIT_VOL_DAC_LSB_1dB0        6
#घोषणा CPCAP_BIT_VOL_CDC3                5
#घोषणा CPCAP_BIT_VOL_CDC2                4
#घोषणा CPCAP_BIT_VOL_CDC1                3
#घोषणा CPCAP_BIT_VOL_CDC0                2
#घोषणा CPCAP_BIT_VOL_CDC_LSB_1dB1        1
#घोषणा CPCAP_BIT_VOL_CDC_LSB_1dB0        0

/* Register 521 CPCAP_REG_RXCOA  --- Codec to Output Amp Switches */
#घोषणा CPCAP_BIT_PGA_CDC_EN              10
#घोषणा CPCAP_BIT_CDC_SW                  9
#घोषणा CPCAP_BIT_PGA_OUTR_USBDP_CDC_SW   8
#घोषणा CPCAP_BIT_PGA_OUTL_USBDN_CDC_SW   7
#घोषणा CPCAP_BIT_ALEFT_HS_CDC_SW         6
#घोषणा CPCAP_BIT_ARIGHT_HS_CDC_SW        5
#घोषणा CPCAP_BIT_A4_LINEOUT_L_CDC_SW     4
#घोषणा CPCAP_BIT_A4_LINEOUT_R_CDC_SW     3
#घोषणा CPCAP_BIT_A2_LDSP_L_CDC_SW        2
#घोषणा CPCAP_BIT_A2_LDSP_R_CDC_SW        1
#घोषणा CPCAP_BIT_A1_EAR_CDC_SW           0

/* Register 522 CPCAP_REG_RXSDOA --- RX Stereo DAC to Output Amp Switches */
#घोषणा CPCAP_BIT_PGA_DAC_EN              12
#घोषणा CPCAP_BIT_ST_DAC_SW               11
#घोषणा CPCAP_BIT_MONO_DAC1               10
#घोषणा CPCAP_BIT_MONO_DAC0               9
#घोषणा CPCAP_BIT_PGA_OUTR_USBDP_DAC_SW   8
#घोषणा CPCAP_BIT_PGA_OUTL_USBDN_DAC_SW   7
#घोषणा CPCAP_BIT_ALEFT_HS_DAC_SW         6
#घोषणा CPCAP_BIT_ARIGHT_HS_DAC_SW        5
#घोषणा CPCAP_BIT_A4_LINEOUT_L_DAC_SW     4
#घोषणा CPCAP_BIT_A4_LINEOUT_R_DAC_SW     3
#घोषणा CPCAP_BIT_A2_LDSP_L_DAC_SW        2
#घोषणा CPCAP_BIT_A2_LDSP_R_DAC_SW        1
#घोषणा CPCAP_BIT_A1_EAR_DAC_SW           0

/* Register 523 CPCAP_REG_RXEPOA --- RX External PGA to Output Amp Switches */
#घोषणा CPCAP_BIT_PGA_EXT_L_EN            14
#घोषणा CPCAP_BIT_PGA_EXT_R_EN            13
#घोषणा CPCAP_BIT_PGA_IN_L_SW             12
#घोषणा CPCAP_BIT_PGA_IN_R_SW             11
#घोषणा CPCAP_BIT_MONO_EXT1               10
#घोषणा CPCAP_BIT_MONO_EXT0               9
#घोषणा CPCAP_BIT_PGA_OUTR_USBDP_EXT_SW   8
#घोषणा CPCAP_BIT_PGA_OUTL_USBDN_EXT_SW   7
#घोषणा CPCAP_BIT_ALEFT_HS_EXT_SW         6
#घोषणा CPCAP_BIT_ARIGHT_HS_EXT_SW        5
#घोषणा CPCAP_BIT_A4_LINEOUT_L_EXT_SW     4
#घोषणा CPCAP_BIT_A4_LINEOUT_R_EXT_SW     3
#घोषणा CPCAP_BIT_A2_LDSP_L_EXT_SW        2
#घोषणा CPCAP_BIT_A2_LDSP_R_EXT_SW        1
#घोषणा CPCAP_BIT_A1_EAR_EXT_SW           0

/* Register 525 CPCAP_REG_A2LA --- SPK Amplअगरier and Clock Config क्रम Headset */
#घोषणा CPCAP_BIT_NCP_CLK_SYNC            7
#घोषणा CPCAP_BIT_A2_CLK_SYNC             6
#घोषणा CPCAP_BIT_A2_FREE_RUN             5
#घोषणा CPCAP_BIT_A2_CLK2                 4
#घोषणा CPCAP_BIT_A2_CLK1                 3
#घोषणा CPCAP_BIT_A2_CLK0                 2
#घोषणा CPCAP_BIT_A2_CLK_IN               1
#घोषणा CPCAP_BIT_A2_CONFIG               0

#घोषणा SLEEP_ACTIVATE_POWER 2
#घोषणा CLOCK_TREE_RESET_TIME 1

/* स्थिरants क्रम ST delay workaround */
#घोषणा STM_STDAC_ACTIVATE_RAMP_TIME   1
#घोषणा STM_STDAC_EN_TEST_PRE          0x090C
#घोषणा STM_STDAC_EN_TEST_POST         0x0000
#घोषणा STM_STDAC_EN_ST_TEST1_PRE      0x2400
#घोषणा STM_STDAC_EN_ST_TEST1_POST     0x0400

काष्ठा cpcap_reg_info अणु
	u16 reg;
	u16 mask;
	u16 val;
पूर्ण;

अटल स्थिर काष्ठा cpcap_reg_info cpcap_शेष_regs[] = अणु
	अणु CPCAP_REG_VAUDIOC, 0x003F, 0x0000 पूर्ण,
	अणु CPCAP_REG_CC, 0xFFFF, 0x0000 पूर्ण,
	अणु CPCAP_REG_CC, 0xFFFF, 0x0000 पूर्ण,
	अणु CPCAP_REG_CDI, 0xBFFF, 0x0000 पूर्ण,
	अणु CPCAP_REG_SDAC, 0x0FFF, 0x0000 पूर्ण,
	अणु CPCAP_REG_SDACDI, 0x3FFF, 0x0000 पूर्ण,
	अणु CPCAP_REG_TXI, 0x0FDF, 0x0000 पूर्ण,
	अणु CPCAP_REG_TXMP, 0x0FFF, 0x0400 पूर्ण,
	अणु CPCAP_REG_RXOA, 0x01FF, 0x0000 पूर्ण,
	अणु CPCAP_REG_RXVC, 0xFF3C, 0x0000 पूर्ण,
	अणु CPCAP_REG_RXCOA, 0x07FF, 0x0000 पूर्ण,
	अणु CPCAP_REG_RXSDOA, 0x1FFF, 0x0000 पूर्ण,
	अणु CPCAP_REG_RXEPOA, 0x7FFF, 0x0000 पूर्ण,
	अणु CPCAP_REG_A2LA, BIT(CPCAP_BIT_A2_FREE_RUN),
	  BIT(CPCAP_BIT_A2_FREE_RUN) पूर्ण,
पूर्ण;

क्रमागत cpcap_dai अणु
	CPCAP_DAI_HIFI,
	CPCAP_DAI_VOICE,
पूर्ण;

काष्ठा cpcap_audio अणु
	काष्ठा snd_soc_component *component;
	काष्ठा regmap *regmap;

	u16 venकरोr;

	पूर्णांक codec_clk_id;
	पूर्णांक codec_freq;
	पूर्णांक codec_क्रमmat;
पूर्ण;

अटल पूर्णांक cpcap_st_workaround(काष्ठा snd_soc_dapm_widget *w,
			       काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा cpcap_audio *cpcap = snd_soc_component_get_drvdata(component);
	पूर्णांक err = 0;

	/* Only CPCAP from ST requires workaround */
	अगर (cpcap->venकरोr != CPCAP_VENDOR_ST)
		वापस 0;

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		err = regmap_ग_लिखो(cpcap->regmap, CPCAP_REG_TEST,
				   STM_STDAC_EN_TEST_PRE);
		अगर (err)
			वापस err;
		err = regmap_ग_लिखो(cpcap->regmap, CPCAP_REG_ST_TEST1,
				   STM_STDAC_EN_ST_TEST1_PRE);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMU:
		msleep(STM_STDAC_ACTIVATE_RAMP_TIME);

		err = regmap_ग_लिखो(cpcap->regmap, CPCAP_REG_ST_TEST1,
				   STM_STDAC_EN_ST_TEST1_POST);
		अगर (err)
			वापस err;
		err = regmap_ग_लिखो(cpcap->regmap, CPCAP_REG_TEST,
				   STM_STDAC_EN_TEST_POST);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

/* Capture Gain Control: 0dB to 31dB in 1dB steps */
अटल स्थिर DECLARE_TLV_DB_SCALE(mic_gain_tlv, 0, 100, 0);

/* Playback Gain Control: -33dB to 12dB in 3dB steps */
अटल स्थिर DECLARE_TLV_DB_SCALE(vol_tlv, -3300, 300, 0);

अटल स्थिर काष्ठा snd_kcontrol_new cpcap_snd_controls[] = अणु
	/* Playback Gain */
	SOC_SINGLE_TLV("HiFi Playback Volume",
		CPCAP_REG_RXVC, CPCAP_BIT_VOL_DAC0, 0xF, 0, vol_tlv),
	SOC_SINGLE_TLV("Voice Playback Volume",
		CPCAP_REG_RXVC, CPCAP_BIT_VOL_CDC0, 0xF, 0, vol_tlv),
	SOC_SINGLE_TLV("Ext Playback Volume",
		CPCAP_REG_RXVC, CPCAP_BIT_VOL_EXT0, 0xF, 0, vol_tlv),

	/* Capture Gain */
	SOC_SINGLE_TLV("Mic1 Capture Volume",
		CPCAP_REG_TXMP, CPCAP_BIT_MIC1_GAIN_0, 0x1F, 0, mic_gain_tlv),
	SOC_SINGLE_TLV("Mic2 Capture Volume",
		CPCAP_REG_TXMP, CPCAP_BIT_MIC2_GAIN_0, 0x1F, 0, mic_gain_tlv),

	/* Phase Invert */
	SOC_SINGLE("Hifi Left Phase Invert Switch",
		CPCAP_REG_RXSDOA, CPCAP_BIT_MONO_DAC0, 1, 0),
	SOC_SINGLE("Ext Left Phase Invert Switch",
		CPCAP_REG_RXEPOA, CPCAP_BIT_MONO_EXT0, 1, 0),
पूर्ण;

अटल स्थिर अक्षर * स्थिर cpcap_out_mux_texts[] = अणु
	"Off", "Voice", "HiFi", "Ext"
पूर्ण;

अटल स्थिर अक्षर * स्थिर cpcap_in_right_mux_texts[] = अणु
	"Off", "Mic 1", "Headset Mic", "EMU Mic", "Ext Right"
पूर्ण;

अटल स्थिर अक्षर * स्थिर cpcap_in_left_mux_texts[] = अणु
	"Off", "Mic 2", "Ext Left"
पूर्ण;

/*
 * input muxes use unusual रेजिस्टर layout, so that we need to use custom
 * getter/setter methods
 */
अटल SOC_ENUM_SINGLE_EXT_DECL(cpcap_input_left_mux_क्रमागत,
				cpcap_in_left_mux_texts);
अटल SOC_ENUM_SINGLE_EXT_DECL(cpcap_input_right_mux_क्रमागत,
				cpcap_in_right_mux_texts);

/*
 * mux uses same bit in CPCAP_REG_RXCOA, CPCAP_REG_RXSDOA & CPCAP_REG_RXEPOA;
 * even though the रेजिस्टर layout makes it look like a mixer, this is a mux.
 * Enabling multiple inमाला_दो will result in no audio being क्रमwarded.
 */
अटल SOC_ENUM_SINGLE_DECL(cpcap_earpiece_mux_क्रमागत, 0, 0, cpcap_out_mux_texts);
अटल SOC_ENUM_SINGLE_DECL(cpcap_spkr_r_mux_क्रमागत, 0, 1, cpcap_out_mux_texts);
अटल SOC_ENUM_SINGLE_DECL(cpcap_spkr_l_mux_क्रमागत, 0, 2, cpcap_out_mux_texts);
अटल SOC_ENUM_SINGLE_DECL(cpcap_line_r_mux_क्रमागत, 0, 3, cpcap_out_mux_texts);
अटल SOC_ENUM_SINGLE_DECL(cpcap_line_l_mux_क्रमागत, 0, 4, cpcap_out_mux_texts);
अटल SOC_ENUM_SINGLE_DECL(cpcap_hs_r_mux_क्रमागत, 0, 5, cpcap_out_mux_texts);
अटल SOC_ENUM_SINGLE_DECL(cpcap_hs_l_mux_क्रमागत, 0, 6, cpcap_out_mux_texts);
अटल SOC_ENUM_SINGLE_DECL(cpcap_emu_l_mux_क्रमागत, 0, 7, cpcap_out_mux_texts);
अटल SOC_ENUM_SINGLE_DECL(cpcap_emu_r_mux_क्रमागत, 0, 8, cpcap_out_mux_texts);

अटल पूर्णांक cpcap_output_mux_get_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा cpcap_audio *cpcap = snd_soc_component_get_drvdata(component);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक shअगरt = e->shअगरt_l;
	पूर्णांक reg_voice, reg_hअगरi, reg_ext, status;
	पूर्णांक err;

	err = regmap_पढ़ो(cpcap->regmap, CPCAP_REG_RXCOA, &reg_voice);
	अगर (err)
		वापस err;
	err = regmap_पढ़ो(cpcap->regmap, CPCAP_REG_RXSDOA, &reg_hअगरi);
	अगर (err)
		वापस err;
	err = regmap_पढ़ो(cpcap->regmap, CPCAP_REG_RXEPOA, &reg_ext);
	अगर (err)
		वापस err;

	reg_voice = (reg_voice >> shअगरt) & 1;
	reg_hअगरi = (reg_hअगरi >> shअगरt) & 1;
	reg_ext = (reg_ext >> shअगरt) & 1;
	status = reg_ext << 2 | reg_hअगरi << 1 | reg_voice;

	चयन (status) अणु
	हाल 0x04:
		ucontrol->value.क्रमागतerated.item[0] = 3;
		अवरोध;
	हाल 0x02:
		ucontrol->value.क्रमागतerated.item[0] = 2;
		अवरोध;
	हाल 0x01:
		ucontrol->value.क्रमागतerated.item[0] = 1;
		अवरोध;
	शेष:
		ucontrol->value.क्रमागतerated.item[0] = 0;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_output_mux_put_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
				     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा cpcap_audio *cpcap = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक muxval = ucontrol->value.क्रमागतerated.item[0];
	अचिन्हित पूर्णांक mask = BIT(e->shअगरt_l);
	u16 reg_voice = 0x00, reg_hअगरi = 0x00, reg_ext = 0x00;
	पूर्णांक err;

	चयन (muxval) अणु
	हाल 1:
		reg_voice = mask;
		अवरोध;
	हाल 2:
		reg_hअगरi = mask;
		अवरोध;
	हाल 3:
		reg_ext = mask;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	err = regmap_update_bits(cpcap->regmap, CPCAP_REG_RXCOA,
				 mask, reg_voice);
	अगर (err)
		वापस err;
	err = regmap_update_bits(cpcap->regmap, CPCAP_REG_RXSDOA,
				 mask, reg_hअगरi);
	अगर (err)
		वापस err;
	err = regmap_update_bits(cpcap->regmap, CPCAP_REG_RXEPOA,
				 mask, reg_ext);
	अगर (err)
		वापस err;

	snd_soc_dapm_mux_update_घातer(dapm, kcontrol, muxval, e, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_input_right_mux_get_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा cpcap_audio *cpcap = snd_soc_component_get_drvdata(component);
	पूर्णांक regval, mask;
	पूर्णांक err;

	err = regmap_पढ़ो(cpcap->regmap, CPCAP_REG_TXI, &regval);
	अगर (err)
		वापस err;

	mask = 0;
	mask |= BIT(CPCAP_BIT_MIC1_MUX);
	mask |= BIT(CPCAP_BIT_HS_MIC_MUX);
	mask |= BIT(CPCAP_BIT_EMU_MIC_MUX);
	mask |= BIT(CPCAP_BIT_RX_R_ENCODE);

	चयन (regval & mask) अणु
	हाल BIT(CPCAP_BIT_RX_R_ENCODE):
		ucontrol->value.क्रमागतerated.item[0] = 4;
		अवरोध;
	हाल BIT(CPCAP_BIT_EMU_MIC_MUX):
		ucontrol->value.क्रमागतerated.item[0] = 3;
		अवरोध;
	हाल BIT(CPCAP_BIT_HS_MIC_MUX):
		ucontrol->value.क्रमागतerated.item[0] = 2;
		अवरोध;
	हाल BIT(CPCAP_BIT_MIC1_MUX):
		ucontrol->value.क्रमागतerated.item[0] = 1;
		अवरोध;
	शेष:
		ucontrol->value.क्रमागतerated.item[0] = 0;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_input_right_mux_put_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
					  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा cpcap_audio *cpcap = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक muxval = ucontrol->value.क्रमागतerated.item[0];
	पूर्णांक regval = 0, mask;
	पूर्णांक err;

	mask = 0;
	mask |= BIT(CPCAP_BIT_MIC1_MUX);
	mask |= BIT(CPCAP_BIT_HS_MIC_MUX);
	mask |= BIT(CPCAP_BIT_EMU_MIC_MUX);
	mask |= BIT(CPCAP_BIT_RX_R_ENCODE);

	चयन (muxval) अणु
	हाल 1:
		regval = BIT(CPCAP_BIT_MIC1_MUX);
		अवरोध;
	हाल 2:
		regval = BIT(CPCAP_BIT_HS_MIC_MUX);
		अवरोध;
	हाल 3:
		regval = BIT(CPCAP_BIT_EMU_MIC_MUX);
		अवरोध;
	हाल 4:
		regval = BIT(CPCAP_BIT_RX_R_ENCODE);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	err = regmap_update_bits(cpcap->regmap, CPCAP_REG_TXI,
				 mask, regval);
	अगर (err)
		वापस err;

	snd_soc_dapm_mux_update_घातer(dapm, kcontrol, muxval, e, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_input_left_mux_get_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा cpcap_audio *cpcap = snd_soc_component_get_drvdata(component);
	पूर्णांक regval, mask;
	पूर्णांक err;

	err = regmap_पढ़ो(cpcap->regmap, CPCAP_REG_TXI, &regval);
	अगर (err)
		वापस err;

	mask = 0;
	mask |= BIT(CPCAP_BIT_MIC2_MUX);
	mask |= BIT(CPCAP_BIT_RX_L_ENCODE);

	चयन (regval & mask) अणु
	हाल BIT(CPCAP_BIT_RX_L_ENCODE):
		ucontrol->value.क्रमागतerated.item[0] = 2;
		अवरोध;
	हाल BIT(CPCAP_BIT_MIC2_MUX):
		ucontrol->value.क्रमागतerated.item[0] = 1;
		अवरोध;
	शेष:
		ucontrol->value.क्रमागतerated.item[0] = 0;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_input_left_mux_put_क्रमागत(काष्ठा snd_kcontrol *kcontrol,
					 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_kcontrol_component(kcontrol);
	काष्ठा cpcap_audio *cpcap = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm =
		snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा soc_क्रमागत *e = (काष्ठा soc_क्रमागत *)kcontrol->निजी_value;
	अचिन्हित पूर्णांक muxval = ucontrol->value.क्रमागतerated.item[0];
	पूर्णांक regval = 0, mask;
	पूर्णांक err;

	mask = 0;
	mask |= BIT(CPCAP_BIT_MIC2_MUX);
	mask |= BIT(CPCAP_BIT_RX_L_ENCODE);

	चयन (muxval) अणु
	हाल 1:
		regval = BIT(CPCAP_BIT_MIC2_MUX);
		अवरोध;
	हाल 2:
		regval = BIT(CPCAP_BIT_RX_L_ENCODE);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	err = regmap_update_bits(cpcap->regmap, CPCAP_REG_TXI,
				 mask, regval);
	अगर (err)
		वापस err;

	snd_soc_dapm_mux_update_घातer(dapm, kcontrol, muxval, e, शून्य);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new cpcap_input_left_mux =
	SOC_DAPM_ENUM_EXT("Input Left", cpcap_input_left_mux_क्रमागत,
			  cpcap_input_left_mux_get_क्रमागत,
			  cpcap_input_left_mux_put_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cpcap_input_right_mux =
	SOC_DAPM_ENUM_EXT("Input Right", cpcap_input_right_mux_क्रमागत,
			  cpcap_input_right_mux_get_क्रमागत,
			  cpcap_input_right_mux_put_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cpcap_emu_left_mux =
	SOC_DAPM_ENUM_EXT("EMU Left", cpcap_emu_l_mux_क्रमागत,
			  cpcap_output_mux_get_क्रमागत, cpcap_output_mux_put_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cpcap_emu_right_mux =
	SOC_DAPM_ENUM_EXT("EMU Right", cpcap_emu_r_mux_क्रमागत,
			  cpcap_output_mux_get_क्रमागत, cpcap_output_mux_put_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cpcap_hs_left_mux =
	SOC_DAPM_ENUM_EXT("Headset Left", cpcap_hs_l_mux_क्रमागत,
			  cpcap_output_mux_get_क्रमागत, cpcap_output_mux_put_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cpcap_hs_right_mux =
	SOC_DAPM_ENUM_EXT("Headset Right", cpcap_hs_r_mux_क्रमागत,
			  cpcap_output_mux_get_क्रमागत, cpcap_output_mux_put_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cpcap_line_left_mux =
	SOC_DAPM_ENUM_EXT("Line Left", cpcap_line_l_mux_क्रमागत,
			  cpcap_output_mux_get_क्रमागत, cpcap_output_mux_put_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cpcap_line_right_mux =
	SOC_DAPM_ENUM_EXT("Line Right", cpcap_line_r_mux_क्रमागत,
			  cpcap_output_mux_get_क्रमागत, cpcap_output_mux_put_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cpcap_speaker_left_mux =
	SOC_DAPM_ENUM_EXT("Speaker Left", cpcap_spkr_l_mux_क्रमागत,
			  cpcap_output_mux_get_क्रमागत, cpcap_output_mux_put_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cpcap_speaker_right_mux =
	SOC_DAPM_ENUM_EXT("Speaker Right", cpcap_spkr_r_mux_क्रमागत,
			  cpcap_output_mux_get_क्रमागत, cpcap_output_mux_put_क्रमागत);
अटल स्थिर काष्ठा snd_kcontrol_new cpcap_earpiece_mux =
	SOC_DAPM_ENUM_EXT("Earpiece", cpcap_earpiece_mux_क्रमागत,
			  cpcap_output_mux_get_क्रमागत, cpcap_output_mux_put_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new cpcap_hअगरi_mono_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("HiFi Mono Playback Switch",
		CPCAP_REG_RXSDOA, CPCAP_BIT_MONO_DAC1, 1, 0),
पूर्ण;
अटल स्थिर काष्ठा snd_kcontrol_new cpcap_ext_mono_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Ext Mono Playback Switch",
		CPCAP_REG_RXEPOA, CPCAP_BIT_MONO_EXT0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new cpcap_extr_mute_control =
	SOC_DAPM_SINGLE("Switch",
		CPCAP_REG_RXEPOA, CPCAP_BIT_PGA_IN_R_SW, 1, 0);
अटल स्थिर काष्ठा snd_kcontrol_new cpcap_extl_mute_control =
	SOC_DAPM_SINGLE("Switch",
		CPCAP_REG_RXEPOA, CPCAP_BIT_PGA_IN_L_SW, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new cpcap_voice_loopback =
	SOC_DAPM_SINGLE("Switch",
		CPCAP_REG_TXI, CPCAP_BIT_DLM, 1, 0);

अटल स्थिर काष्ठा snd_soc_dapm_widget cpcap_dapm_widमाला_लो[] = अणु
	/* DAIs */
	SND_SOC_DAPM_AIF_IN("HiFi RX", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("Voice RX", शून्य, 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("Voice TX", शून्य, 0, SND_SOC_NOPM, 0, 0),

	/* Power Supply */
	SND_SOC_DAPM_REGULATOR_SUPPLY("VAUDIO", SLEEP_ACTIVATE_POWER, 0),

	/* Highpass Filters */
	SND_SOC_DAPM_REG(snd_soc_dapm_pga, "Highpass Filter RX",
		CPCAP_REG_CC, CPCAP_BIT_AUDIHPF_0, 0x3, 0x3, 0x0),
	SND_SOC_DAPM_REG(snd_soc_dapm_pga, "Highpass Filter TX",
		CPCAP_REG_CC, CPCAP_BIT_AUDOHPF_0, 0x3, 0x3, 0x0),

	/* Clocks */
	SND_SOC_DAPM_SUPPLY("HiFi DAI Clock",
		CPCAP_REG_SDACDI, CPCAP_BIT_ST_CLK_EN, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Voice DAI Clock",
		CPCAP_REG_CDI, CPCAP_BIT_CDC_CLK_EN, 0, शून्य, 0),

	/* Microphone Bias */
	SND_SOC_DAPM_SUPPLY("MIC1R Bias",
		CPCAP_REG_TXI, CPCAP_BIT_MB_ON1R, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MIC1L Bias",
		CPCAP_REG_TXI, CPCAP_BIT_MB_ON1L, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("MIC2 Bias",
		CPCAP_REG_TXI, CPCAP_BIT_MB_ON2, 0, शून्य, 0),

	/* Inमाला_दो */
	SND_SOC_DAPM_INPUT("MICR"),
	SND_SOC_DAPM_INPUT("HSMIC"),
	SND_SOC_DAPM_INPUT("EMUMIC"),
	SND_SOC_DAPM_INPUT("MICL"),
	SND_SOC_DAPM_INPUT("EXTR"),
	SND_SOC_DAPM_INPUT("EXTL"),

	/* Capture Route */
	SND_SOC_DAPM_MUX("Right Capture Route",
		SND_SOC_NOPM, 0, 0, &cpcap_input_right_mux),
	SND_SOC_DAPM_MUX("Left Capture Route",
		SND_SOC_NOPM, 0, 0, &cpcap_input_left_mux),

	/* Capture PGAs */
	SND_SOC_DAPM_PGA("Microphone 1 PGA",
		CPCAP_REG_TXI, CPCAP_BIT_MIC1_PGA_EN, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Microphone 2 PGA",
		CPCAP_REG_TXI, CPCAP_BIT_MIC2_PGA_EN, 0, शून्य, 0),

	/* ADC */
	SND_SOC_DAPM_ADC("ADC Right", शून्य,
		CPCAP_REG_CC, CPCAP_BIT_MIC1_CDC_EN, 0),
	SND_SOC_DAPM_ADC("ADC Left", शून्य,
		CPCAP_REG_CC, CPCAP_BIT_MIC2_CDC_EN, 0),

	/* DAC */
	SND_SOC_DAPM_DAC_E("DAC HiFi", शून्य,
		CPCAP_REG_SDAC, CPCAP_BIT_ST_DAC_EN, 0,
		cpcap_st_workaround,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_DAC_E("DAC Voice", शून्य,
		CPCAP_REG_CC, CPCAP_BIT_CDC_EN_RX, 0,
		cpcap_st_workaround,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),

	/* Playback PGA */
	SND_SOC_DAPM_PGA("HiFi PGA",
		CPCAP_REG_RXSDOA, CPCAP_BIT_PGA_DAC_EN, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Voice PGA",
		CPCAP_REG_RXCOA, CPCAP_BIT_PGA_CDC_EN, 0, शून्य, 0),
	SND_SOC_DAPM_PGA_E("Ext Right PGA",
		CPCAP_REG_RXEPOA, CPCAP_BIT_PGA_EXT_R_EN, 0,
		शून्य, 0,
		cpcap_st_workaround,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),
	SND_SOC_DAPM_PGA_E("Ext Left PGA",
		CPCAP_REG_RXEPOA, CPCAP_BIT_PGA_EXT_L_EN, 0,
		शून्य, 0,
		cpcap_st_workaround,
		SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU),

	/* Playback Switch */
	SND_SOC_DAPM_SWITCH("Ext Right Enable", SND_SOC_NOPM, 0, 0,
		&cpcap_extr_mute_control),
	SND_SOC_DAPM_SWITCH("Ext Left Enable", SND_SOC_NOPM, 0, 0,
		&cpcap_extl_mute_control),

	/* Loopback Switch */
	SND_SOC_DAPM_SWITCH("Voice Loopback", SND_SOC_NOPM, 0, 0,
		&cpcap_voice_loopback),

	/* Mono Mixer */
	SOC_MIXER_ARRAY("HiFi Mono Left Mixer", SND_SOC_NOPM, 0, 0,
		cpcap_hअगरi_mono_mixer_controls),
	SOC_MIXER_ARRAY("HiFi Mono Right Mixer", SND_SOC_NOPM, 0, 0,
		cpcap_hअगरi_mono_mixer_controls),
	SOC_MIXER_ARRAY("Ext Mono Left Mixer", SND_SOC_NOPM, 0, 0,
		cpcap_ext_mono_mixer_controls),
	SOC_MIXER_ARRAY("Ext Mono Right Mixer", SND_SOC_NOPM, 0, 0,
		cpcap_ext_mono_mixer_controls),

	/* Output Routes */
	SND_SOC_DAPM_MUX("Earpiece Playback Route", SND_SOC_NOPM, 0, 0,
		&cpcap_earpiece_mux),
	SND_SOC_DAPM_MUX("Speaker Right Playback Route", SND_SOC_NOPM, 0, 0,
		&cpcap_speaker_right_mux),
	SND_SOC_DAPM_MUX("Speaker Left Playback Route", SND_SOC_NOPM, 0, 0,
		&cpcap_speaker_left_mux),
	SND_SOC_DAPM_MUX("Lineout Right Playback Route", SND_SOC_NOPM, 0, 0,
		&cpcap_line_right_mux),
	SND_SOC_DAPM_MUX("Lineout Left Playback Route", SND_SOC_NOPM, 0, 0,
		&cpcap_line_left_mux),
	SND_SOC_DAPM_MUX("Headset Right Playback Route", SND_SOC_NOPM, 0, 0,
		&cpcap_hs_right_mux),
	SND_SOC_DAPM_MUX("Headset Left Playback Route", SND_SOC_NOPM, 0, 0,
		&cpcap_hs_left_mux),
	SND_SOC_DAPM_MUX("EMU Right Playback Route", SND_SOC_NOPM, 0, 0,
		&cpcap_emu_right_mux),
	SND_SOC_DAPM_MUX("EMU Left Playback Route", SND_SOC_NOPM, 0, 0,
		&cpcap_emu_left_mux),

	/* Output Amplअगरier */
	SND_SOC_DAPM_PGA("Earpiece PGA",
		CPCAP_REG_RXOA, CPCAP_BIT_A1_EAR_EN, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Speaker Right PGA",
		CPCAP_REG_RXOA, CPCAP_BIT_A2_LDSP_R_EN, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Speaker Left PGA",
		CPCAP_REG_RXOA, CPCAP_BIT_A2_LDSP_L_EN, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Lineout Right PGA",
		CPCAP_REG_RXOA, CPCAP_BIT_A4_LINEOUT_R_EN, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Lineout Left PGA",
		CPCAP_REG_RXOA, CPCAP_BIT_A4_LINEOUT_L_EN, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Headset Right PGA",
		CPCAP_REG_RXOA, CPCAP_BIT_HS_R_EN, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Headset Left PGA",
		CPCAP_REG_RXOA, CPCAP_BIT_HS_L_EN, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("EMU Right PGA",
		CPCAP_REG_RXOA, CPCAP_BIT_EMU_SPKR_R_EN, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("EMU Left PGA",
		CPCAP_REG_RXOA, CPCAP_BIT_EMU_SPKR_L_EN, 0, शून्य, 0),

	/* Headet Charge Pump */
	SND_SOC_DAPM_SUPPLY("Headset Charge Pump",
		CPCAP_REG_RXOA, CPCAP_BIT_ST_HS_CP_EN, 0, शून्य, 0),

	/* Outमाला_दो */
	SND_SOC_DAPM_OUTPUT("EP"),
	SND_SOC_DAPM_OUTPUT("SPKR"),
	SND_SOC_DAPM_OUTPUT("SPKL"),
	SND_SOC_DAPM_OUTPUT("LINER"),
	SND_SOC_DAPM_OUTPUT("LINEL"),
	SND_SOC_DAPM_OUTPUT("HSR"),
	SND_SOC_DAPM_OUTPUT("HSL"),
	SND_SOC_DAPM_OUTPUT("EMUR"),
	SND_SOC_DAPM_OUTPUT("EMUL"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route पूर्णांकercon[] = अणु
	/* Power Supply */
	अणु"HiFi PGA", शून्य, "VAUDIO"पूर्ण,
	अणु"Voice PGA", शून्य, "VAUDIO"पूर्ण,
	अणु"Ext Right PGA", शून्य, "VAUDIO"पूर्ण,
	अणु"Ext Left PGA", शून्य, "VAUDIO"पूर्ण,
	अणु"Microphone 1 PGA", शून्य, "VAUDIO"पूर्ण,
	अणु"Microphone 2 PGA", शून्य, "VAUDIO"पूर्ण,

	/* Stream -> AIF */
	अणु"HiFi RX", शून्य, "HiFi Playback"पूर्ण,
	अणु"Voice RX", शून्य, "Voice Playback"पूर्ण,
	अणु"Voice Capture", शून्य, "Voice TX"पूर्ण,

	/* AIF घड़ीs */
	अणु"HiFi RX", शून्य, "HiFi DAI Clock"पूर्ण,
	अणु"Voice RX", शून्य, "Voice DAI Clock"पूर्ण,
	अणु"Voice TX", शून्य, "Voice DAI Clock"पूर्ण,

	/* Digital Loopback */
	अणु"Voice Loopback", "Switch", "Voice TX"पूर्ण,
	अणु"Voice RX", शून्य, "Voice Loopback"पूर्ण,

	/* Highpass Filters */
	अणु"Highpass Filter RX", शून्य, "Voice RX"पूर्ण,
	अणु"Voice TX", शून्य, "Highpass Filter TX"पूर्ण,

	/* AIF -> DAC mapping */
	अणु"DAC HiFi", शून्य, "HiFi RX"पूर्ण,
	अणु"DAC Voice", शून्य, "Highpass Filter RX"पूर्ण,

	/* DAC -> PGA */
	अणु"HiFi PGA", शून्य, "DAC HiFi"पूर्ण,
	अणु"Voice PGA", शून्य, "DAC Voice"पूर्ण,

	/* Ext Input -> PGA */
	अणु"Ext Right PGA", शून्य, "EXTR"पूर्ण,
	अणु"Ext Left PGA", शून्य, "EXTL"पूर्ण,

	/* Ext PGA -> Ext Playback Switch */
	अणु"Ext Right Enable", "Switch", "Ext Right PGA"पूर्ण,
	अणु"Ext Left Enable", "Switch", "Ext Left PGA"पूर्ण,

	/* HiFi PGA -> Mono Mixer */
	अणु"HiFi Mono Left Mixer", शून्य, "HiFi PGA"पूर्ण,
	अणु"HiFi Mono Left Mixer", "HiFi Mono Playback Switch", "HiFi PGA"पूर्ण,
	अणु"HiFi Mono Right Mixer", शून्य, "HiFi PGA"पूर्ण,
	अणु"HiFi Mono Right Mixer", "HiFi Mono Playback Switch", "HiFi PGA"पूर्ण,

	/* Ext Playback Switch -> Ext Mono Mixer */
	अणु"Ext Mono Right Mixer", शून्य, "Ext Right Enable"पूर्ण,
	अणु"Ext Mono Right Mixer", "Ext Mono Playback Switch", "Ext Left Enable"पूर्ण,
	अणु"Ext Mono Left Mixer", शून्य, "Ext Left Enable"पूर्ण,
	अणु"Ext Mono Left Mixer", "Ext Mono Playback Switch", "Ext Right Enable"पूर्ण,

	/* HiFi Mono Mixer -> Output Route */
	अणु"Earpiece Playback Route", "HiFi", "HiFi Mono Right Mixer"पूर्ण,
	अणु"Speaker Right Playback Route", "HiFi", "HiFi Mono Right Mixer"पूर्ण,
	अणु"Speaker Left Playback Route", "HiFi", "HiFi Mono Left Mixer"पूर्ण,
	अणु"Lineout Right Playback Route", "HiFi", "HiFi Mono Right Mixer"पूर्ण,
	अणु"Lineout Left Playback Route", "HiFi", "HiFi Mono Left Mixer"पूर्ण,
	अणु"Headset Right Playback Route", "HiFi", "HiFi Mono Right Mixer"पूर्ण,
	अणु"Headset Left Playback Route", "HiFi", "HiFi Mono Left Mixer"पूर्ण,
	अणु"EMU Right Playback Route", "HiFi", "HiFi Mono Right Mixer"पूर्ण,
	अणु"EMU Left Playback Route", "HiFi", "HiFi Mono Left Mixer"पूर्ण,

	/* Voice PGA -> Output Route */
	अणु"Earpiece Playback Route", "Voice", "Voice PGA"पूर्ण,
	अणु"Speaker Right Playback Route", "Voice", "Voice PGA"पूर्ण,
	अणु"Speaker Left Playback Route", "Voice", "Voice PGA"पूर्ण,
	अणु"Lineout Right Playback Route", "Voice", "Voice PGA"पूर्ण,
	अणु"Lineout Left Playback Route", "Voice", "Voice PGA"पूर्ण,
	अणु"Headset Right Playback Route", "Voice", "Voice PGA"पूर्ण,
	अणु"Headset Left Playback Route", "Voice", "Voice PGA"पूर्ण,
	अणु"EMU Right Playback Route", "Voice", "Voice PGA"पूर्ण,
	अणु"EMU Left Playback Route", "Voice", "Voice PGA"पूर्ण,

	/* Ext Mono Mixer -> Output Route */
	अणु"Earpiece Playback Route", "Ext", "Ext Mono Right Mixer"पूर्ण,
	अणु"Speaker Right Playback Route", "Ext", "Ext Mono Right Mixer"पूर्ण,
	अणु"Speaker Left Playback Route", "Ext", "Ext Mono Left Mixer"पूर्ण,
	अणु"Lineout Right Playback Route", "Ext", "Ext Mono Right Mixer"पूर्ण,
	अणु"Lineout Left Playback Route", "Ext", "Ext Mono Left Mixer"पूर्ण,
	अणु"Headset Right Playback Route", "Ext", "Ext Mono Right Mixer"पूर्ण,
	अणु"Headset Left Playback Route", "Ext", "Ext Mono Left Mixer"पूर्ण,
	अणु"EMU Right Playback Route", "Ext", "Ext Mono Right Mixer"पूर्ण,
	अणु"EMU Left Playback Route", "Ext", "Ext Mono Left Mixer"पूर्ण,

	/* Output Route -> Output Amplअगरier */
	अणु"Earpiece PGA", शून्य, "Earpiece Playback Route"पूर्ण,
	अणु"Speaker Right PGA", शून्य, "Speaker Right Playback Route"पूर्ण,
	अणु"Speaker Left PGA", शून्य, "Speaker Left Playback Route"पूर्ण,
	अणु"Lineout Right PGA", शून्य, "Lineout Right Playback Route"पूर्ण,
	अणु"Lineout Left PGA", शून्य, "Lineout Left Playback Route"पूर्ण,
	अणु"Headset Right PGA", शून्य, "Headset Right Playback Route"पूर्ण,
	अणु"Headset Left PGA", शून्य, "Headset Left Playback Route"पूर्ण,
	अणु"EMU Right PGA", शून्य, "EMU Right Playback Route"पूर्ण,
	अणु"EMU Left PGA", शून्य, "EMU Left Playback Route"पूर्ण,

	/* Output Amplअगरier -> Output */
	अणु"EP", शून्य, "Earpiece PGA"पूर्ण,
	अणु"SPKR", शून्य, "Speaker Right PGA"पूर्ण,
	अणु"SPKL", शून्य, "Speaker Left PGA"पूर्ण,
	अणु"LINER", शून्य, "Lineout Right PGA"पूर्ण,
	अणु"LINEL", शून्य, "Lineout Left PGA"पूर्ण,
	अणु"HSR", शून्य, "Headset Right PGA"पूर्ण,
	अणु"HSL", शून्य, "Headset Left PGA"पूर्ण,
	अणु"EMUR", शून्य, "EMU Right PGA"पूर्ण,
	अणु"EMUL", शून्य, "EMU Left PGA"पूर्ण,

	/* Headset Charge Pump -> Headset */
	अणु"HSR", शून्य, "Headset Charge Pump"पूर्ण,
	अणु"HSL", शून्य, "Headset Charge Pump"पूर्ण,

	/* Mic -> Mic Route */
	अणु"Right Capture Route", "Mic 1", "MICR"पूर्ण,
	अणु"Right Capture Route", "Headset Mic", "HSMIC"पूर्ण,
	अणु"Right Capture Route", "EMU Mic", "EMUMIC"पूर्ण,
	अणु"Right Capture Route", "Ext Right", "EXTR"पूर्ण,
	अणु"Left Capture Route", "Mic 2", "MICL"पूर्ण,
	अणु"Left Capture Route", "Ext Left", "EXTL"पूर्ण,

	/* Input Route -> Microphone PGA */
	अणु"Microphone 1 PGA", शून्य, "Right Capture Route"पूर्ण,
	अणु"Microphone 2 PGA", शून्य, "Left Capture Route"पूर्ण,

	/* Microphone PGA -> ADC */
	अणु"ADC Right", शून्य, "Microphone 1 PGA"पूर्ण,
	अणु"ADC Left", शून्य, "Microphone 2 PGA"पूर्ण,

	/* ADC -> Stream */
	अणु"Highpass Filter TX", शून्य, "ADC Right"पूर्ण,
	अणु"Highpass Filter TX", शून्य, "ADC Left"पूर्ण,

	/* Mic Bias */
	अणु"MICL", शून्य, "MIC1L Bias"पूर्ण,
	अणु"MICR", शून्य, "MIC1R Bias"पूर्ण,
पूर्ण;

अटल पूर्णांक cpcap_set_sysclk(काष्ठा cpcap_audio *cpcap, क्रमागत cpcap_dai dai,
			    पूर्णांक clk_id, पूर्णांक freq)
अणु
	u16 clkfreqreg, clkfreqshअगरt;
	u16 clkfreqmask, clkfreqval;
	u16 clkidreg, clkidshअगरt;
	u16 mask, val;
	पूर्णांक err;

	चयन (dai) अणु
	हाल CPCAP_DAI_HIFI:
		clkfreqreg = CPCAP_REG_SDAC;
		clkfreqshअगरt = CPCAP_BIT_ST_DAC_CLK0;
		clkidreg = CPCAP_REG_SDACDI;
		clkidshअगरt = CPCAP_BIT_ST_DAC_CLK_IN_SEL;
		अवरोध;
	हाल CPCAP_DAI_VOICE:
		clkfreqreg = CPCAP_REG_CC;
		clkfreqshअगरt = CPCAP_BIT_CDC_CLK0;
		clkidreg = CPCAP_REG_CDI;
		clkidshअगरt = CPCAP_BIT_CLK_IN_SEL;
		अवरोध;
	शेष:
		dev_err(cpcap->component->dev, "invalid DAI: %d", dai);
		वापस -EINVAL;
	पूर्ण

	/* setup clk id */
	अगर (clk_id < 0 || clk_id > 1) अणु
		dev_err(cpcap->component->dev, "invalid clk id %d", clk_id);
		वापस -EINVAL;
	पूर्ण
	err = regmap_update_bits(cpcap->regmap, clkidreg, BIT(clkidshअगरt),
				 clk_id ? BIT(clkidshअगरt) : 0);
	अगर (err)
		वापस err;

	/* enable PLL क्रम Voice DAI */
	अगर (dai == CPCAP_DAI_VOICE) अणु
		mask = BIT(CPCAP_BIT_CDC_PLL_SEL);
		val = BIT(CPCAP_BIT_CDC_PLL_SEL);
		err = regmap_update_bits(cpcap->regmap, CPCAP_REG_CDI,
					 mask, val);
		अगर (err)
			वापस err;
	पूर्ण

	/* setup frequency */
	clkfreqmask = 0x7 << clkfreqshअगरt;
	चयन (freq) अणु
	हाल 15360000:
		clkfreqval = 0x01 << clkfreqshअगरt;
		अवरोध;
	हाल 16800000:
		clkfreqval = 0x02 << clkfreqshअगरt;
		अवरोध;
	हाल 19200000:
		clkfreqval = 0x03 << clkfreqshअगरt;
		अवरोध;
	हाल 26000000:
		clkfreqval = 0x04 << clkfreqshअगरt;
		अवरोध;
	हाल 33600000:
		clkfreqval = 0x05 << clkfreqshअगरt;
		अवरोध;
	हाल 38400000:
		clkfreqval = 0x06 << clkfreqshअगरt;
		अवरोध;
	शेष:
		dev_err(cpcap->component->dev, "unsupported freq %u", freq);
		वापस -EINVAL;
	पूर्ण

	err = regmap_update_bits(cpcap->regmap, clkfreqreg,
				 clkfreqmask, clkfreqval);
	अगर (err)
		वापस err;

	अगर (dai == CPCAP_DAI_VOICE) अणु
		cpcap->codec_clk_id = clk_id;
		cpcap->codec_freq = freq;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_set_samprate(काष्ठा cpcap_audio *cpcap, क्रमागत cpcap_dai dai,
			      पूर्णांक samplerate)
अणु
	काष्ठा snd_soc_component *component = cpcap->component;
	u16 sampreg, sampmask, sampshअगरt, sampval, sampreset;
	पूर्णांक err, sampपढ़ोval;

	चयन (dai) अणु
	हाल CPCAP_DAI_HIFI:
		sampreg = CPCAP_REG_SDAC;
		sampshअगरt = CPCAP_BIT_ST_SR0;
		sampreset = BIT(CPCAP_BIT_DF_RESET_ST_DAC) |
			    BIT(CPCAP_BIT_ST_CLOCK_TREE_RESET);
		अवरोध;
	हाल CPCAP_DAI_VOICE:
		sampreg = CPCAP_REG_CC;
		sampshअगरt = CPCAP_BIT_CDC_SR0;
		sampreset = BIT(CPCAP_BIT_DF_RESET) |
			    BIT(CPCAP_BIT_CDC_CLOCK_TREE_RESET);
		अवरोध;
	शेष:
		dev_err(component->dev, "invalid DAI: %d", dai);
		वापस -EINVAL;
	पूर्ण

	sampmask = 0xF << sampshअगरt | sampreset;
	चयन (samplerate) अणु
	हाल 48000:
		sampval = 0x8 << sampshअगरt;
		अवरोध;
	हाल 44100:
		sampval = 0x7 << sampshअगरt;
		अवरोध;
	हाल 32000:
		sampval = 0x6 << sampshअगरt;
		अवरोध;
	हाल 24000:
		sampval = 0x5 << sampshअगरt;
		अवरोध;
	हाल 22050:
		sampval = 0x4 << sampshअगरt;
		अवरोध;
	हाल 16000:
		sampval = 0x3 << sampshअगरt;
		अवरोध;
	हाल 12000:
		sampval = 0x2 << sampshअगरt;
		अवरोध;
	हाल 11025:
		sampval = 0x1 << sampshअगरt;
		अवरोध;
	हाल 8000:
		sampval = 0x0 << sampshअगरt;
		अवरोध;
	शेष:
		dev_err(component->dev, "unsupported samplerate %d", samplerate);
		वापस -EINVAL;
	पूर्ण
	err = regmap_update_bits(cpcap->regmap, sampreg,
				 sampmask, sampval | sampreset);
	अगर (err)
		वापस err;

	/* Wait क्रम घड़ी tree reset to complete */
	mdelay(CLOCK_TREE_RESET_TIME);

	err = regmap_पढ़ो(cpcap->regmap, sampreg, &sampपढ़ोval);
	अगर (err)
		वापस err;

	अगर (sampपढ़ोval & sampreset) अणु
		dev_err(component->dev, "reset self-clear failed: %04x",
			sampपढ़ोval);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_hअगरi_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cpcap_audio *cpcap = snd_soc_component_get_drvdata(component);
	पूर्णांक rate = params_rate(params);

	dev_dbg(component->dev, "HiFi setup HW params: rate=%d", rate);
	वापस cpcap_set_samprate(cpcap, CPCAP_DAI_HIFI, rate);
पूर्ण

अटल पूर्णांक cpcap_hअगरi_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai, पूर्णांक clk_id,
				     अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cpcap_audio *cpcap = snd_soc_component_get_drvdata(component);
	काष्ठा device *dev = component->dev;

	dev_dbg(dev, "HiFi setup sysclk: clk_id=%u, freq=%u", clk_id, freq);
	वापस cpcap_set_sysclk(cpcap, CPCAP_DAI_HIFI, clk_id, freq);
पूर्ण

अटल पूर्णांक cpcap_hअगरi_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
				  अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cpcap_audio *cpcap = snd_soc_component_get_drvdata(component);
	काष्ठा device *dev = component->dev;
	अटल स्थिर u16 reg = CPCAP_REG_SDACDI;
	अटल स्थिर u16 mask =
		BIT(CPCAP_BIT_SMB_ST_DAC) |
		BIT(CPCAP_BIT_ST_CLK_INV) |
		BIT(CPCAP_BIT_ST_FS_INV) |
		BIT(CPCAP_BIT_ST_DIG_AUD_FS0) |
		BIT(CPCAP_BIT_ST_DIG_AUD_FS1) |
		BIT(CPCAP_BIT_ST_L_TIMESLOT0) |
		BIT(CPCAP_BIT_ST_L_TIMESLOT1) |
		BIT(CPCAP_BIT_ST_L_TIMESLOT2) |
		BIT(CPCAP_BIT_ST_R_TIMESLOT0) |
		BIT(CPCAP_BIT_ST_R_TIMESLOT1) |
		BIT(CPCAP_BIT_ST_R_TIMESLOT2);
	u16 val = 0x0000;

	dev_dbg(dev, "HiFi setup dai format (%08x)", fmt);

	/*
	 * "HiFi Playback" should always be configured as
	 * SND_SOC_DAIFMT_CBM_CFM - codec clk & frm master
	 * SND_SOC_DAIFMT_I2S - I2S mode
	 */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		val &= ~BIT(CPCAP_BIT_SMB_ST_DAC);
		अवरोध;
	शेष:
		dev_err(dev, "HiFi dai fmt failed: CPCAP should be master");
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_IB_IF:
		val |= BIT(CPCAP_BIT_ST_FS_INV);
		val |= BIT(CPCAP_BIT_ST_CLK_INV);
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		val &= ~BIT(CPCAP_BIT_ST_FS_INV);
		val |= BIT(CPCAP_BIT_ST_CLK_INV);
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		val |= BIT(CPCAP_BIT_ST_FS_INV);
		val &= ~BIT(CPCAP_BIT_ST_CLK_INV);
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_NF:
		val &= ~BIT(CPCAP_BIT_ST_FS_INV);
		val &= ~BIT(CPCAP_BIT_ST_CLK_INV);
		अवरोध;
	शेष:
		dev_err(dev, "HiFi dai fmt failed: unsupported clock invert mode");
		वापस -EINVAL;
	पूर्ण

	अगर (val & BIT(CPCAP_BIT_ST_CLK_INV))
		val &= ~BIT(CPCAP_BIT_ST_CLK_INV);
	अन्यथा
		val |= BIT(CPCAP_BIT_ST_CLK_INV);

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		val |= BIT(CPCAP_BIT_ST_DIG_AUD_FS0);
		val |= BIT(CPCAP_BIT_ST_DIG_AUD_FS1);
		अवरोध;
	शेष:
		/* 01 - 4 slots network mode */
		val |= BIT(CPCAP_BIT_ST_DIG_AUD_FS0);
		val &= ~BIT(CPCAP_BIT_ST_DIG_AUD_FS1);
		/* L on slot 1 */
		val |= BIT(CPCAP_BIT_ST_L_TIMESLOT0);
		अवरोध;
	पूर्ण

	dev_dbg(dev, "HiFi dai format: val=%04x", val);
	वापस regmap_update_bits(cpcap->regmap, reg, mask, val);
पूर्ण

अटल पूर्णांक cpcap_hअगरi_set_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cpcap_audio *cpcap = snd_soc_component_get_drvdata(component);
	अटल स्थिर u16 reg = CPCAP_REG_RXSDOA;
	अटल स्थिर u16 mask = BIT(CPCAP_BIT_ST_DAC_SW);
	u16 val;

	अगर (mute)
		val = 0;
	अन्यथा
		val = BIT(CPCAP_BIT_ST_DAC_SW);

	dev_dbg(component->dev, "HiFi mute: %d", mute);
	वापस regmap_update_bits(cpcap->regmap, reg, mask, val);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops cpcap_dai_hअगरi_ops = अणु
	.hw_params	= cpcap_hअगरi_hw_params,
	.set_sysclk	= cpcap_hअगरi_set_dai_sysclk,
	.set_fmt	= cpcap_hअगरi_set_dai_fmt,
	.mute_stream	= cpcap_hअगरi_set_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल पूर्णांक cpcap_voice_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा device *dev = component->dev;
	काष्ठा cpcap_audio *cpcap = snd_soc_component_get_drvdata(component);
	अटल स्थिर u16 reg_cdi = CPCAP_REG_CDI;
	पूर्णांक rate = params_rate(params);
	पूर्णांक channels = params_channels(params);
	पूर्णांक direction = substream->stream;
	u16 val, mask;
	पूर्णांक err;

	dev_dbg(dev, "Voice setup HW params: rate=%d, direction=%d, chan=%d",
		rate, direction, channels);

	err = cpcap_set_samprate(cpcap, CPCAP_DAI_VOICE, rate);
	अगर (err)
		वापस err;

	अगर (direction == SNDRV_PCM_STREAM_CAPTURE) अणु
		mask = 0x0000;
		mask |= BIT(CPCAP_BIT_MIC1_RX_TIMESLOT0);
		mask |= BIT(CPCAP_BIT_MIC1_RX_TIMESLOT1);
		mask |= BIT(CPCAP_BIT_MIC1_RX_TIMESLOT2);
		mask |= BIT(CPCAP_BIT_MIC2_TIMESLOT0);
		mask |= BIT(CPCAP_BIT_MIC2_TIMESLOT1);
		mask |= BIT(CPCAP_BIT_MIC2_TIMESLOT2);
		val = 0x0000;
		अगर (channels >= 2)
			val = BIT(CPCAP_BIT_MIC1_RX_TIMESLOT0);
		err = regmap_update_bits(cpcap->regmap, reg_cdi, mask, val);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_voice_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai, पूर्णांक clk_id,
				      अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cpcap_audio *cpcap = snd_soc_component_get_drvdata(component);

	dev_dbg(component->dev, "Voice setup sysclk: clk_id=%u, freq=%u",
		clk_id, freq);
	वापस cpcap_set_sysclk(cpcap, CPCAP_DAI_VOICE, clk_id, freq);
पूर्ण

अटल पूर्णांक cpcap_voice_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
				   अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cpcap_audio *cpcap = snd_soc_component_get_drvdata(component);
	अटल स्थिर u16 mask = BIT(CPCAP_BIT_SMB_CDC) |
				BIT(CPCAP_BIT_CLK_INV) |
				BIT(CPCAP_BIT_FS_INV) |
				BIT(CPCAP_BIT_CDC_DIG_AUD_FS0) |
				BIT(CPCAP_BIT_CDC_DIG_AUD_FS1);
	u16 val = 0x0000;
	पूर्णांक err;

	dev_dbg(component->dev, "Voice setup dai format (%08x)", fmt);

	/*
	 * "Voice Playback" and "Voice Capture" should always be
	 * configured as SND_SOC_DAIFMT_CBM_CFM - codec clk & frm
	 * master
	 */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		val &= ~BIT(CPCAP_BIT_SMB_CDC);
		अवरोध;
	शेष:
		dev_err(component->dev, "Voice dai fmt failed: CPCAP should be the master");
		val &= ~BIT(CPCAP_BIT_SMB_CDC);
		अवरोध;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_IB_IF:
		val |= BIT(CPCAP_BIT_CLK_INV);
		val |= BIT(CPCAP_BIT_FS_INV);
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		val |= BIT(CPCAP_BIT_CLK_INV);
		val &= ~BIT(CPCAP_BIT_FS_INV);
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		val &= ~BIT(CPCAP_BIT_CLK_INV);
		val |= BIT(CPCAP_BIT_FS_INV);
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_NF:
		val &= ~BIT(CPCAP_BIT_CLK_INV);
		val &= ~BIT(CPCAP_BIT_FS_INV);
		अवरोध;
	शेष:
		dev_err(component->dev, "Voice dai fmt failed: unsupported clock invert mode");
		अवरोध;
	पूर्ण

	अगर (val & BIT(CPCAP_BIT_CLK_INV))
		val &= ~BIT(CPCAP_BIT_CLK_INV);
	अन्यथा
		val |= BIT(CPCAP_BIT_CLK_INV);

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		/* 11 - true I2S mode */
		val |= BIT(CPCAP_BIT_CDC_DIG_AUD_FS0);
		val |= BIT(CPCAP_BIT_CDC_DIG_AUD_FS1);
		अवरोध;
	शेष:
		/* 4 बारlots network mode */
		val |= BIT(CPCAP_BIT_CDC_DIG_AUD_FS0);
		val &= ~BIT(CPCAP_BIT_CDC_DIG_AUD_FS1);
		अवरोध;
	पूर्ण

	dev_dbg(component->dev, "Voice dai format: val=%04x", val);
	err = regmap_update_bits(cpcap->regmap, CPCAP_REG_CDI, mask, val);
	अगर (err)
		वापस err;

	cpcap->codec_क्रमmat = val;
	वापस 0;
पूर्ण


/*
 * Configure codec क्रम voice call अगर requested.
 *
 * We can configure most with snd_soc_dai_set_sysclk(), snd_soc_dai_set_fmt()
 * and snd_soc_dai_set_tdm_slot(). This function configures the rest of the
 * cpcap related hardware as CPU is not involved in the voice call.
 */
अटल पूर्णांक cpcap_voice_call(काष्ठा cpcap_audio *cpcap, काष्ठा snd_soc_dai *dai,
			    bool voice_call)
अणु
	पूर्णांक mask, err;

	/* Modem to codec VAUDIO_MODE1 */
	mask = BIT(CPCAP_BIT_VAUDIO_MODE1);
	err = regmap_update_bits(cpcap->regmap, CPCAP_REG_VAUDIOC,
				 mask, voice_call ? mask : 0);
	अगर (err)
		वापस err;

	/* Clear MIC1_MUX क्रम call */
	mask = BIT(CPCAP_BIT_MIC1_MUX);
	err = regmap_update_bits(cpcap->regmap, CPCAP_REG_TXI,
				 mask, voice_call ? 0 : mask);
	अगर (err)
		वापस err;

	/* Set MIC2_MUX क्रम call */
	mask = BIT(CPCAP_BIT_MB_ON1L) | BIT(CPCAP_BIT_MB_ON1R) |
		BIT(CPCAP_BIT_MIC2_MUX) | BIT(CPCAP_BIT_MIC2_PGA_EN);
	err = regmap_update_bits(cpcap->regmap, CPCAP_REG_TXI,
				 mask, voice_call ? mask : 0);
	अगर (err)
		वापस err;

	/* Enable LDSP क्रम call */
	mask = BIT(CPCAP_BIT_A2_LDSP_L_EN) | BIT(CPCAP_BIT_A2_LDSP_R_EN);
	err = regmap_update_bits(cpcap->regmap, CPCAP_REG_RXOA,
				 mask, voice_call ? mask : 0);
	अगर (err)
		वापस err;

	/* Enable CPCAP_BIT_PGA_CDC_EN क्रम call */
	mask = BIT(CPCAP_BIT_PGA_CDC_EN);
	err = regmap_update_bits(cpcap->regmap, CPCAP_REG_RXCOA,
				 mask, voice_call ? mask : 0);
	अगर (err)
		वापस err;

	/* Unmute voice क्रम call */
	अगर (dai) अणु
		err = snd_soc_dai_digital_mute(dai, !voice_call,
					       SNDRV_PCM_STREAM_PLAYBACK);
		अगर (err)
			वापस err;
	पूर्ण

	/* Set modem to codec mic CDC and HPF क्रम call */
	mask = BIT(CPCAP_BIT_MIC2_CDC_EN) | BIT(CPCAP_BIT_CDC_EN_RX) |
	       BIT(CPCAP_BIT_AUDOHPF_1) | BIT(CPCAP_BIT_AUDOHPF_0) |
	       BIT(CPCAP_BIT_AUDIHPF_1) | BIT(CPCAP_BIT_AUDIHPF_0);
	err = regmap_update_bits(cpcap->regmap, CPCAP_REG_CC,
				 mask, voice_call ? mask : 0);
	अगर (err)
		वापस err;

	/* Enable modem to codec CDC क्रम call*/
	mask = BIT(CPCAP_BIT_CDC_CLK_EN);
	err = regmap_update_bits(cpcap->regmap, CPCAP_REG_CDI,
				 mask, voice_call ? mask : 0);

	वापस err;
पूर्ण

अटल पूर्णांक cpcap_voice_set_tdm_slot(काष्ठा snd_soc_dai *dai,
				    अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
				    पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cpcap_audio *cpcap = snd_soc_component_get_drvdata(component);
	पूर्णांक err, ts_mask, mask;
	bool voice_call;

	/*
	 * Primitive test क्रम voice call, probably needs more checks
	 * later on क्रम 16-bit calls detected, Bluetooth headset etc.
	 */
	अगर (tx_mask == 0 && rx_mask == 1 && slot_width == 8)
		voice_call = true;
	अन्यथा
		voice_call = false;

	ts_mask = 0x7 << CPCAP_BIT_MIC2_TIMESLOT0;
	ts_mask |= 0x7 << CPCAP_BIT_MIC1_RX_TIMESLOT0;

	mask = (tx_mask & 0x7) << CPCAP_BIT_MIC2_TIMESLOT0;
	mask |= (rx_mask & 0x7) << CPCAP_BIT_MIC1_RX_TIMESLOT0;

	err = regmap_update_bits(cpcap->regmap, CPCAP_REG_CDI,
				 ts_mask, mask);
	अगर (err)
		वापस err;

	err = cpcap_set_samprate(cpcap, CPCAP_DAI_VOICE, slot_width * 1000);
	अगर (err)
		वापस err;

	err = cpcap_voice_call(cpcap, dai, voice_call);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_voice_set_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cpcap_audio *cpcap = snd_soc_component_get_drvdata(component);
	अटल स्थिर u16 reg = CPCAP_REG_RXCOA;
	अटल स्थिर u16 mask = BIT(CPCAP_BIT_CDC_SW);
	u16 val;

	अगर (mute)
		val = 0;
	अन्यथा
		val = BIT(CPCAP_BIT_CDC_SW);

	dev_dbg(component->dev, "Voice mute: %d", mute);
	वापस regmap_update_bits(cpcap->regmap, reg, mask, val);
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops cpcap_dai_voice_ops = अणु
	.hw_params	= cpcap_voice_hw_params,
	.set_sysclk	= cpcap_voice_set_dai_sysclk,
	.set_fmt	= cpcap_voice_set_dai_fmt,
	.set_tdm_slot	= cpcap_voice_set_tdm_slot,
	.mute_stream	= cpcap_voice_set_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver cpcap_dai[] = अणु
अणु
	.id = 0,
	.name = "cpcap-hifi",
	.playback = अणु
		.stream_name = "HiFi Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FORMAT_S24_LE,
	पूर्ण,
	.ops = &cpcap_dai_hअगरi_ops,
पूर्ण,
अणु
	.id = 1,
	.name = "cpcap-voice",
	.playback = अणु
		.stream_name = "Voice Playback",
		.channels_min = 1,
		.channels_max = 1,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "Voice Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.ops = &cpcap_dai_voice_ops,
पूर्ण,
पूर्ण;

अटल पूर्णांक cpcap_dai_mux(काष्ठा cpcap_audio *cpcap, bool swap_dai_configuration)
अणु
	u16 hअगरi_val, voice_val;
	u16 hअगरi_mask = BIT(CPCAP_BIT_DIG_AUD_IN_ST_DAC);
	u16 voice_mask = BIT(CPCAP_BIT_DIG_AUD_IN);
	पूर्णांक err;



	अगर (!swap_dai_configuration) अणु
		/* Codec on DAI0, HiFi on DAI1 */
		voice_val = 0;
		hअगरi_val = hअगरi_mask;
	पूर्ण अन्यथा अणु
		/* Codec on DAI1, HiFi on DAI0 */
		voice_val = voice_mask;
		hअगरi_val = 0;
	पूर्ण

	err = regmap_update_bits(cpcap->regmap, CPCAP_REG_CDI,
				 voice_mask, voice_val);
	अगर (err)
		वापस err;

	err = regmap_update_bits(cpcap->regmap, CPCAP_REG_SDACDI,
				 hअगरi_mask, hअगरi_val);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_audio_reset(काष्ठा snd_soc_component *component,
			     bool swap_dai_configuration)
अणु
	काष्ठा cpcap_audio *cpcap = snd_soc_component_get_drvdata(component);
	पूर्णांक i, err = 0;

	dev_dbg(component->dev, "init audio codec");

	क्रम (i = 0; i < ARRAY_SIZE(cpcap_शेष_regs); i++) अणु
		err = regmap_update_bits(cpcap->regmap,
					 cpcap_शेष_regs[i].reg,
					 cpcap_शेष_regs[i].mask,
					 cpcap_शेष_regs[i].val);
		अगर (err)
			वापस err;
	पूर्ण

	/* setup शेष settings */
	err = cpcap_dai_mux(cpcap, swap_dai_configuration);
	अगर (err)
		वापस err;

	err = cpcap_set_sysclk(cpcap, CPCAP_DAI_HIFI, 0, 26000000);
	अगर (err)
		वापस err;
	err = cpcap_set_sysclk(cpcap, CPCAP_DAI_VOICE, 0, 26000000);
	अगर (err)
		वापस err;

	err = cpcap_set_samprate(cpcap, CPCAP_DAI_HIFI, 48000);
	अगर (err)
		वापस err;

	err = cpcap_set_samprate(cpcap, CPCAP_DAI_VOICE, 48000);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक cpcap_soc_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा cpcap_audio *cpcap;
	पूर्णांक err;

	cpcap = devm_kzalloc(component->dev, माप(*cpcap), GFP_KERNEL);
	अगर (!cpcap)
		वापस -ENOMEM;
	snd_soc_component_set_drvdata(component, cpcap);
	cpcap->component = component;

	cpcap->regmap = dev_get_regmap(component->dev->parent, शून्य);
	अगर (!cpcap->regmap)
		वापस -ENODEV;
	snd_soc_component_init_regmap(component, cpcap->regmap);

	err = cpcap_get_venकरोr(component->dev, cpcap->regmap, &cpcap->venकरोr);
	अगर (err)
		वापस err;

	वापस cpcap_audio_reset(component, false);
पूर्ण

अटल काष्ठा snd_soc_component_driver soc_codec_dev_cpcap = अणु
	.probe			= cpcap_soc_probe,
	.controls		= cpcap_snd_controls,
	.num_controls		= ARRAY_SIZE(cpcap_snd_controls),
	.dapm_widमाला_लो		= cpcap_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(cpcap_dapm_widमाला_लो),
	.dapm_routes		= पूर्णांकercon,
	.num_dapm_routes	= ARRAY_SIZE(पूर्णांकercon),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक cpcap_codec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *codec_node =
		of_get_child_by_name(pdev->dev.parent->of_node, "audio-codec");

	pdev->dev.of_node = codec_node;

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev, &soc_codec_dev_cpcap,
				      cpcap_dai, ARRAY_SIZE(cpcap_dai));
पूर्ण

अटल काष्ठा platक्रमm_driver cpcap_codec_driver = अणु
	.probe		= cpcap_codec_probe,
	.driver		= अणु
		.name	= "cpcap-codec",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(cpcap_codec_driver);

MODULE_ALIAS("platform:cpcap-codec");
MODULE_DESCRIPTION("ASoC CPCAP codec driver");
MODULE_AUTHOR("Sebastian Reichel");
MODULE_LICENSE("GPL v2");
