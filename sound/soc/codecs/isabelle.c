<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * isabelle.c - Low घातer high fidelity audio codec driver
 *
 * Copyright (c) 2012 Texas Instruments, Inc
 *
 * Initially based on sound/soc/codecs/twl6040.c
 */
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/tlv.h>
#समावेश <sound/jack.h>
#समावेश <sound/initval.h>
#समावेश <यंत्र/भाग64.h>
#समावेश "isabelle.h"


/* Register शेष values क्रम ISABELLE driver. */
अटल स्थिर काष्ठा reg_शेष isabelle_reg_defs[] = अणु
	अणु 0, 0x00 पूर्ण,
	अणु 1, 0x00 पूर्ण,
	अणु 2, 0x00 पूर्ण,
	अणु 3, 0x00 पूर्ण,
	अणु 4, 0x00 पूर्ण,
	अणु 5, 0x00 पूर्ण,
	अणु 6, 0x00 पूर्ण,
	अणु 7, 0x00 पूर्ण,
	अणु 8, 0x00 पूर्ण,
	अणु 9, 0x00 पूर्ण,
	अणु 10, 0x00 पूर्ण,
	अणु 11, 0x00 पूर्ण,
	अणु 12, 0x00 पूर्ण,
	अणु 13, 0x00 पूर्ण,
	अणु 14, 0x00 पूर्ण,
	अणु 15, 0x00 पूर्ण,
	अणु 16, 0x00 पूर्ण,
	अणु 17, 0x00 पूर्ण,
	अणु 18, 0x00 पूर्ण,
	अणु 19, 0x00 पूर्ण,
	अणु 20, 0x00 पूर्ण,
	अणु 21, 0x02 पूर्ण,
	अणु 22, 0x02 पूर्ण,
	अणु 23, 0x02 पूर्ण,
	अणु 24, 0x02 पूर्ण,
	अणु 25, 0x0F पूर्ण,
	अणु 26, 0x8F पूर्ण,
	अणु 27, 0x0F पूर्ण,
	अणु 28, 0x8F पूर्ण,
	अणु 29, 0x00 पूर्ण,
	अणु 30, 0x00 पूर्ण,
	अणु 31, 0x00 पूर्ण,
	अणु 32, 0x00 पूर्ण,
	अणु 33, 0x00 पूर्ण,
	अणु 34, 0x00 पूर्ण,
	अणु 35, 0x00 पूर्ण,
	अणु 36, 0x00 पूर्ण,
	अणु 37, 0x00 पूर्ण,
	अणु 38, 0x00 पूर्ण,
	अणु 39, 0x00 पूर्ण,
	अणु 40, 0x00 पूर्ण,
	अणु 41, 0x00 पूर्ण,
	अणु 42, 0x00 पूर्ण,
	अणु 43, 0x00 पूर्ण,
	अणु 44, 0x00 पूर्ण,
	अणु 45, 0x00 पूर्ण,
	अणु 46, 0x00 पूर्ण,
	अणु 47, 0x00 पूर्ण,
	अणु 48, 0x00 पूर्ण,
	अणु 49, 0x00 पूर्ण,
	अणु 50, 0x00 पूर्ण,
	अणु 51, 0x00 पूर्ण,
	अणु 52, 0x00 पूर्ण,
	अणु 53, 0x00 पूर्ण,
	अणु 54, 0x00 पूर्ण,
	अणु 55, 0x00 पूर्ण,
	अणु 56, 0x00 पूर्ण,
	अणु 57, 0x00 पूर्ण,
	अणु 58, 0x00 पूर्ण,
	अणु 59, 0x00 पूर्ण,
	अणु 60, 0x00 पूर्ण,
	अणु 61, 0x00 पूर्ण,
	अणु 62, 0x00 पूर्ण,
	अणु 63, 0x00 पूर्ण,
	अणु 64, 0x00 पूर्ण,
	अणु 65, 0x00 पूर्ण,
	अणु 66, 0x00 पूर्ण,
	अणु 67, 0x00 पूर्ण,
	अणु 68, 0x00 पूर्ण,
	अणु 69, 0x90 पूर्ण,
	अणु 70, 0x90 पूर्ण,
	अणु 71, 0x90 पूर्ण,
	अणु 72, 0x00 पूर्ण,
	अणु 73, 0x00 पूर्ण,
	अणु 74, 0x00 पूर्ण,
	अणु 75, 0x00 पूर्ण,
	अणु 76, 0x00 पूर्ण,
	अणु 77, 0x00 पूर्ण,
	अणु 78, 0x00 पूर्ण,
	अणु 79, 0x00 पूर्ण,
	अणु 80, 0x00 पूर्ण,
	अणु 81, 0x00 पूर्ण,
	अणु 82, 0x00 पूर्ण,
	अणु 83, 0x00 पूर्ण,
	अणु 84, 0x00 पूर्ण,
	अणु 85, 0x07 पूर्ण,
	अणु 86, 0x00 पूर्ण,
	अणु 87, 0x00 पूर्ण,
	अणु 88, 0x00 पूर्ण,
	अणु 89, 0x07 पूर्ण,
	अणु 90, 0x80 पूर्ण,
	अणु 91, 0x07 पूर्ण,
	अणु 92, 0x07 पूर्ण,
	अणु 93, 0x00 पूर्ण,
	अणु 94, 0x00 पूर्ण,
	अणु 95, 0x00 पूर्ण,
	अणु 96, 0x00 पूर्ण,
	अणु 97, 0x00 पूर्ण,
	अणु 98, 0x00 पूर्ण,
	अणु 99, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *isabelle_rx1_texts[] = अणु"VRX1", "ARX1"पूर्ण;
अटल स्थिर अक्षर *isabelle_rx2_texts[] = अणु"VRX2", "ARX2"पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत isabelle_rx1_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(ISABELLE_VOICE_HPF_CFG_REG, 3,
			ARRAY_SIZE(isabelle_rx1_texts), isabelle_rx1_texts),
	SOC_ENUM_SINGLE(ISABELLE_AUDIO_HPF_CFG_REG, 5,
			ARRAY_SIZE(isabelle_rx1_texts), isabelle_rx1_texts),
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत isabelle_rx2_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(ISABELLE_VOICE_HPF_CFG_REG, 2,
			ARRAY_SIZE(isabelle_rx2_texts), isabelle_rx2_texts),
	SOC_ENUM_SINGLE(ISABELLE_AUDIO_HPF_CFG_REG, 4,
			ARRAY_SIZE(isabelle_rx2_texts), isabelle_rx2_texts),
पूर्ण;

/* Headset DAC playback चयनes */
अटल स्थिर काष्ठा snd_kcontrol_new rx1_mux_controls =
	SOC_DAPM_ENUM("Route", isabelle_rx1_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new rx2_mux_controls =
	SOC_DAPM_ENUM("Route", isabelle_rx2_क्रमागत);

/* TX input selection */
अटल स्थिर अक्षर *isabelle_atx_texts[] = अणु"AMIC1", "DMIC"पूर्ण;
अटल स्थिर अक्षर *isabelle_vtx_texts[] = अणु"AMIC2", "DMIC"पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत isabelle_atx_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(ISABELLE_AMIC_CFG_REG, 7,
			ARRAY_SIZE(isabelle_atx_texts), isabelle_atx_texts),
	SOC_ENUM_SINGLE(ISABELLE_DMIC_CFG_REG, 0,
			ARRAY_SIZE(isabelle_atx_texts), isabelle_atx_texts),
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत isabelle_vtx_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(ISABELLE_AMIC_CFG_REG, 6,
			ARRAY_SIZE(isabelle_vtx_texts), isabelle_vtx_texts),
	SOC_ENUM_SINGLE(ISABELLE_DMIC_CFG_REG, 0,
			ARRAY_SIZE(isabelle_vtx_texts), isabelle_vtx_texts),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new atx_mux_controls =
	SOC_DAPM_ENUM("Route", isabelle_atx_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new vtx_mux_controls =
	SOC_DAPM_ENUM("Route", isabelle_vtx_क्रमागत);

/* Left analog microphone selection */
अटल स्थिर अक्षर *isabelle_amic1_texts[] = अणु
	"Main Mic", "Headset Mic", "Aux/FM Left"पूर्ण;

/* Left analog microphone selection */
अटल स्थिर अक्षर *isabelle_amic2_texts[] = अणु"Sub Mic", "Aux/FM Right"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(isabelle_amic1_क्रमागत,
			    ISABELLE_AMIC_CFG_REG, 5,
			    isabelle_amic1_texts);

अटल SOC_ENUM_SINGLE_DECL(isabelle_amic2_क्रमागत,
			    ISABELLE_AMIC_CFG_REG, 4,
			    isabelle_amic2_texts);

अटल स्थिर काष्ठा snd_kcontrol_new amic1_control =
	SOC_DAPM_ENUM("Route", isabelle_amic1_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new amic2_control =
	SOC_DAPM_ENUM("Route", isabelle_amic2_क्रमागत);

अटल स्थिर अक्षर *isabelle_st_audio_texts[] = अणु"ATX1", "ATX2"पूर्ण;

अटल स्थिर अक्षर *isabelle_st_voice_texts[] = अणु"VTX1", "VTX2"पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत isabelle_st_audio_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(ISABELLE_ATX_STPGA1_CFG_REG, 7,
			ARRAY_SIZE(isabelle_st_audio_texts),
			isabelle_st_audio_texts),
	SOC_ENUM_SINGLE(ISABELLE_ATX_STPGA2_CFG_REG, 7,
			ARRAY_SIZE(isabelle_st_audio_texts),
			isabelle_st_audio_texts),
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत isabelle_st_voice_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(ISABELLE_VTX_STPGA1_CFG_REG, 7,
			ARRAY_SIZE(isabelle_st_voice_texts),
			isabelle_st_voice_texts),
	SOC_ENUM_SINGLE(ISABELLE_VTX2_STPGA2_CFG_REG, 7,
			ARRAY_SIZE(isabelle_st_voice_texts),
			isabelle_st_voice_texts),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new st_audio_control =
	SOC_DAPM_ENUM("Route", isabelle_st_audio_क्रमागत);

अटल स्थिर काष्ठा snd_kcontrol_new st_voice_control =
	SOC_DAPM_ENUM("Route", isabelle_st_voice_क्रमागत);

/* Mixer controls */
अटल स्थिर काष्ठा snd_kcontrol_new isabelle_hs_left_mixer_controls[] = अणु
SOC_DAPM_SINGLE("DAC1L Playback Switch", ISABELLE_HSDRV_CFG1_REG, 7, 1, 0),
SOC_DAPM_SINGLE("APGA1 Playback Switch", ISABELLE_HSDRV_CFG1_REG, 6, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new isabelle_hs_right_mixer_controls[] = अणु
SOC_DAPM_SINGLE("DAC1R Playback Switch", ISABELLE_HSDRV_CFG1_REG, 5, 1, 0),
SOC_DAPM_SINGLE("APGA2 Playback Switch", ISABELLE_HSDRV_CFG1_REG, 4, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new isabelle_hf_left_mixer_controls[] = अणु
SOC_DAPM_SINGLE("DAC2L Playback Switch", ISABELLE_HFLPGA_CFG_REG, 7, 1, 0),
SOC_DAPM_SINGLE("APGA1 Playback Switch", ISABELLE_HFLPGA_CFG_REG, 6, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new isabelle_hf_right_mixer_controls[] = अणु
SOC_DAPM_SINGLE("DAC2R Playback Switch", ISABELLE_HFRPGA_CFG_REG, 7, 1, 0),
SOC_DAPM_SINGLE("APGA2 Playback Switch", ISABELLE_HFRPGA_CFG_REG, 6, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new isabelle_ep_mixer_controls[] = अणु
SOC_DAPM_SINGLE("DAC2L Playback Switch", ISABELLE_EARDRV_CFG1_REG, 7, 1, 0),
SOC_DAPM_SINGLE("APGA1 Playback Switch", ISABELLE_EARDRV_CFG1_REG, 6, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new isabelle_aux_left_mixer_controls[] = अणु
SOC_DAPM_SINGLE("DAC3L Playback Switch", ISABELLE_LINEAMP_CFG_REG, 7, 1, 0),
SOC_DAPM_SINGLE("APGA1 Playback Switch", ISABELLE_LINEAMP_CFG_REG, 6, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new isabelle_aux_right_mixer_controls[] = अणु
SOC_DAPM_SINGLE("DAC3R Playback Switch", ISABELLE_LINEAMP_CFG_REG, 5, 1, 0),
SOC_DAPM_SINGLE("APGA2 Playback Switch", ISABELLE_LINEAMP_CFG_REG, 4, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new isabelle_dpga1_left_mixer_controls[] = अणु
SOC_DAPM_SINGLE("RX1 Playback Switch", ISABELLE_DPGA1LR_IN_SEL_REG, 7, 1, 0),
SOC_DAPM_SINGLE("RX3 Playback Switch", ISABELLE_DPGA1LR_IN_SEL_REG, 6, 1, 0),
SOC_DAPM_SINGLE("RX5 Playback Switch", ISABELLE_DPGA1LR_IN_SEL_REG, 5, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new isabelle_dpga1_right_mixer_controls[] = अणु
SOC_DAPM_SINGLE("RX2 Playback Switch", ISABELLE_DPGA1LR_IN_SEL_REG, 3, 1, 0),
SOC_DAPM_SINGLE("RX4 Playback Switch", ISABELLE_DPGA1LR_IN_SEL_REG, 2, 1, 0),
SOC_DAPM_SINGLE("RX6 Playback Switch", ISABELLE_DPGA1LR_IN_SEL_REG, 1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new isabelle_dpga2_left_mixer_controls[] = अणु
SOC_DAPM_SINGLE("RX1 Playback Switch", ISABELLE_DPGA2L_IN_SEL_REG, 7, 1, 0),
SOC_DAPM_SINGLE("RX2 Playback Switch", ISABELLE_DPGA2L_IN_SEL_REG, 6, 1, 0),
SOC_DAPM_SINGLE("RX3 Playback Switch", ISABELLE_DPGA2L_IN_SEL_REG, 5, 1, 0),
SOC_DAPM_SINGLE("RX4 Playback Switch", ISABELLE_DPGA2L_IN_SEL_REG, 4, 1, 0),
SOC_DAPM_SINGLE("RX5 Playback Switch", ISABELLE_DPGA2L_IN_SEL_REG, 3, 1, 0),
SOC_DAPM_SINGLE("RX6 Playback Switch", ISABELLE_DPGA2L_IN_SEL_REG, 2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new isabelle_dpga2_right_mixer_controls[] = अणु
SOC_DAPM_SINGLE("USNC Playback Switch", ISABELLE_DPGA2R_IN_SEL_REG, 7, 1, 0),
SOC_DAPM_SINGLE("RX2 Playback Switch", ISABELLE_DPGA2R_IN_SEL_REG, 3, 1, 0),
SOC_DAPM_SINGLE("RX4 Playback Switch", ISABELLE_DPGA2R_IN_SEL_REG, 2, 1, 0),
SOC_DAPM_SINGLE("RX6 Playback Switch", ISABELLE_DPGA2R_IN_SEL_REG, 1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new isabelle_dpga3_left_mixer_controls[] = अणु
SOC_DAPM_SINGLE("RX1 Playback Switch", ISABELLE_DPGA3LR_IN_SEL_REG, 7, 1, 0),
SOC_DAPM_SINGLE("RX3 Playback Switch", ISABELLE_DPGA3LR_IN_SEL_REG, 6, 1, 0),
SOC_DAPM_SINGLE("RX5 Playback Switch", ISABELLE_DPGA3LR_IN_SEL_REG, 5, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new isabelle_dpga3_right_mixer_controls[] = अणु
SOC_DAPM_SINGLE("RX2 Playback Switch", ISABELLE_DPGA3LR_IN_SEL_REG, 3, 1, 0),
SOC_DAPM_SINGLE("RX4 Playback Switch", ISABELLE_DPGA3LR_IN_SEL_REG, 2, 1, 0),
SOC_DAPM_SINGLE("RX6 Playback Switch", ISABELLE_DPGA3LR_IN_SEL_REG, 1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new isabelle_rx1_mixer_controls[] = अणु
SOC_DAPM_SINGLE("ST1 Playback Switch", ISABELLE_RX_INPUT_CFG_REG, 7, 1, 0),
SOC_DAPM_SINGLE("DL1 Playback Switch", ISABELLE_RX_INPUT_CFG_REG, 6, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new isabelle_rx2_mixer_controls[] = अणु
SOC_DAPM_SINGLE("ST2 Playback Switch", ISABELLE_RX_INPUT_CFG_REG, 5, 1, 0),
SOC_DAPM_SINGLE("DL2 Playback Switch", ISABELLE_RX_INPUT_CFG_REG, 4, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new isabelle_rx3_mixer_controls[] = अणु
SOC_DAPM_SINGLE("ST1 Playback Switch", ISABELLE_RX_INPUT_CFG_REG, 3, 1, 0),
SOC_DAPM_SINGLE("DL3 Playback Switch", ISABELLE_RX_INPUT_CFG_REG, 2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new isabelle_rx4_mixer_controls[] = अणु
SOC_DAPM_SINGLE("ST2 Playback Switch", ISABELLE_RX_INPUT_CFG_REG, 1, 1, 0),
SOC_DAPM_SINGLE("DL4 Playback Switch", ISABELLE_RX_INPUT_CFG_REG, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new isabelle_rx5_mixer_controls[] = अणु
SOC_DAPM_SINGLE("ST1 Playback Switch", ISABELLE_RX_INPUT_CFG2_REG, 7, 1, 0),
SOC_DAPM_SINGLE("DL5 Playback Switch", ISABELLE_RX_INPUT_CFG2_REG, 6, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new isabelle_rx6_mixer_controls[] = अणु
SOC_DAPM_SINGLE("ST2 Playback Switch", ISABELLE_RX_INPUT_CFG2_REG, 5, 1, 0),
SOC_DAPM_SINGLE("DL6 Playback Switch", ISABELLE_RX_INPUT_CFG2_REG, 4, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new ep_path_enable_control =
	SOC_DAPM_SINGLE("Switch", ISABELLE_EARDRV_CFG2_REG, 0, 1, 0);

/* TLV Declarations */
अटल स्थिर DECLARE_TLV_DB_SCALE(mic_amp_tlv, 0, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(afm_amp_tlv, -3300, 300, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(dac_tlv, -1200, 200, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(hf_tlv, -5000, 200, 0);

/* from -63 to 0 dB in 1 dB steps */
अटल स्थिर DECLARE_TLV_DB_SCALE(dpga_tlv, -6300, 100, 1);

/* from -63 to 9 dB in 1 dB steps */
अटल स्थिर DECLARE_TLV_DB_SCALE(rx_tlv, -6300, 100, 1);

अटल स्थिर DECLARE_TLV_DB_SCALE(st_tlv, -2700, 300, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(tx_tlv, -600, 100, 0);

अटल स्थिर काष्ठा snd_kcontrol_new isabelle_snd_controls[] = अणु
	SOC_DOUBLE_TLV("Headset Playback Volume", ISABELLE_HSDRV_GAIN_REG,
			4, 0, 0xF, 0, dac_tlv),
	SOC_DOUBLE_R_TLV("Handsfree Playback Volume",
			ISABELLE_HFLPGA_CFG_REG, ISABELLE_HFRPGA_CFG_REG,
			0, 0x1F, 0, hf_tlv),
	SOC_DOUBLE_TLV("Aux Playback Volume", ISABELLE_LINEAMP_GAIN_REG,
			4, 0, 0xF, 0, dac_tlv),
	SOC_SINGLE_TLV("Earpiece Playback Volume", ISABELLE_EARDRV_CFG1_REG,
			0, 0xF, 0, dac_tlv),

	SOC_DOUBLE_TLV("Aux FM Volume", ISABELLE_APGA_GAIN_REG, 4, 0, 0xF, 0,
			afm_amp_tlv),
	SOC_SINGLE_TLV("Mic1 Capture Volume", ISABELLE_MIC1_GAIN_REG, 3, 0x1F,
			0, mic_amp_tlv),
	SOC_SINGLE_TLV("Mic2 Capture Volume", ISABELLE_MIC2_GAIN_REG, 3, 0x1F,
			0, mic_amp_tlv),

	SOC_DOUBLE_R_TLV("DPGA1 Volume", ISABELLE_DPGA1L_GAIN_REG,
			ISABELLE_DPGA1R_GAIN_REG, 0, 0x3F, 0, dpga_tlv),
	SOC_DOUBLE_R_TLV("DPGA2 Volume", ISABELLE_DPGA2L_GAIN_REG,
			ISABELLE_DPGA2R_GAIN_REG, 0, 0x3F, 0, dpga_tlv),
	SOC_DOUBLE_R_TLV("DPGA3 Volume", ISABELLE_DPGA3L_GAIN_REG,
			ISABELLE_DPGA3R_GAIN_REG, 0, 0x3F, 0, dpga_tlv),

	SOC_SINGLE_TLV("Sidetone Audio TX1 Volume",
			ISABELLE_ATX_STPGA1_CFG_REG, 0, 0xF, 0, st_tlv),
	SOC_SINGLE_TLV("Sidetone Audio TX2 Volume",
			ISABELLE_ATX_STPGA2_CFG_REG, 0, 0xF, 0, st_tlv),
	SOC_SINGLE_TLV("Sidetone Voice TX1 Volume",
			ISABELLE_VTX_STPGA1_CFG_REG, 0, 0xF, 0, st_tlv),
	SOC_SINGLE_TLV("Sidetone Voice TX2 Volume",
			ISABELLE_VTX2_STPGA2_CFG_REG, 0, 0xF, 0, st_tlv),

	SOC_SINGLE_TLV("Audio TX1 Volume", ISABELLE_ATX1_DPGA_REG, 4, 0xF, 0,
			tx_tlv),
	SOC_SINGLE_TLV("Audio TX2 Volume", ISABELLE_ATX2_DPGA_REG, 4, 0xF, 0,
			tx_tlv),
	SOC_SINGLE_TLV("Voice TX1 Volume", ISABELLE_VTX1_DPGA_REG, 4, 0xF, 0,
			tx_tlv),
	SOC_SINGLE_TLV("Voice TX2 Volume", ISABELLE_VTX2_DPGA_REG, 4, 0xF, 0,
			tx_tlv),

	SOC_SINGLE_TLV("RX1 DPGA Volume", ISABELLE_RX1_DPGA_REG, 0, 0x3F, 0,
			rx_tlv),
	SOC_SINGLE_TLV("RX2 DPGA Volume", ISABELLE_RX2_DPGA_REG, 0, 0x3F, 0,
			rx_tlv),
	SOC_SINGLE_TLV("RX3 DPGA Volume", ISABELLE_RX3_DPGA_REG, 0, 0x3F, 0,
			rx_tlv),
	SOC_SINGLE_TLV("RX4 DPGA Volume", ISABELLE_RX4_DPGA_REG, 0, 0x3F, 0,
			rx_tlv),
	SOC_SINGLE_TLV("RX5 DPGA Volume", ISABELLE_RX5_DPGA_REG, 0, 0x3F, 0,
			rx_tlv),
	SOC_SINGLE_TLV("RX6 DPGA Volume", ISABELLE_RX6_DPGA_REG, 0, 0x3F, 0,
			rx_tlv),

	SOC_SINGLE("Headset Noise Gate", ISABELLE_HS_NG_CFG1_REG, 7, 1, 0),
	SOC_SINGLE("Handsfree Noise Gate", ISABELLE_HF_NG_CFG1_REG, 7, 1, 0),

	SOC_SINGLE("ATX1 Filter Bypass Switch", ISABELLE_AUDIO_HPF_CFG_REG,
		7, 1, 0),
	SOC_SINGLE("ATX2 Filter Bypass Switch", ISABELLE_AUDIO_HPF_CFG_REG,
		6, 1, 0),
	SOC_SINGLE("ARX1 Filter Bypass Switch", ISABELLE_AUDIO_HPF_CFG_REG,
		5, 1, 0),
	SOC_SINGLE("ARX2 Filter Bypass Switch", ISABELLE_AUDIO_HPF_CFG_REG,
		4, 1, 0),
	SOC_SINGLE("ARX3 Filter Bypass Switch", ISABELLE_AUDIO_HPF_CFG_REG,
		3, 1, 0),
	SOC_SINGLE("ARX4 Filter Bypass Switch", ISABELLE_AUDIO_HPF_CFG_REG,
		2, 1, 0),
	SOC_SINGLE("ARX5 Filter Bypass Switch", ISABELLE_AUDIO_HPF_CFG_REG,
		1, 1, 0),
	SOC_SINGLE("ARX6 Filter Bypass Switch", ISABELLE_AUDIO_HPF_CFG_REG,
		0, 1, 0),
	SOC_SINGLE("VRX1 Filter Bypass Switch", ISABELLE_AUDIO_HPF_CFG_REG,
		3, 1, 0),
	SOC_SINGLE("VRX2 Filter Bypass Switch", ISABELLE_AUDIO_HPF_CFG_REG,
		2, 1, 0),

	SOC_SINGLE("ATX1 Filter Enable Switch", ISABELLE_ALU_TX_EN_REG,
		7, 1, 0),
	SOC_SINGLE("ATX2 Filter Enable Switch", ISABELLE_ALU_TX_EN_REG,
		6, 1, 0),
	SOC_SINGLE("VTX1 Filter Enable Switch", ISABELLE_ALU_TX_EN_REG,
		5, 1, 0),
	SOC_SINGLE("VTX2 Filter Enable Switch", ISABELLE_ALU_TX_EN_REG,
		4, 1, 0),
	SOC_SINGLE("RX1 Filter Enable Switch", ISABELLE_ALU_RX_EN_REG,
		5, 1, 0),
	SOC_SINGLE("RX2 Filter Enable Switch", ISABELLE_ALU_RX_EN_REG,
		4, 1, 0),
	SOC_SINGLE("RX3 Filter Enable Switch", ISABELLE_ALU_RX_EN_REG,
		3, 1, 0),
	SOC_SINGLE("RX4 Filter Enable Switch", ISABELLE_ALU_RX_EN_REG,
		2, 1, 0),
	SOC_SINGLE("RX5 Filter Enable Switch", ISABELLE_ALU_RX_EN_REG,
		1, 1, 0),
	SOC_SINGLE("RX6 Filter Enable Switch", ISABELLE_ALU_RX_EN_REG,
		0, 1, 0),

	SOC_SINGLE("ULATX12 Capture Switch", ISABELLE_ULATX12_INTF_CFG_REG,
		7, 1, 0),

	SOC_SINGLE("DL12 Playback Switch", ISABELLE_DL12_INTF_CFG_REG,
		7, 1, 0),
	SOC_SINGLE("DL34 Playback Switch", ISABELLE_DL34_INTF_CFG_REG,
		7, 1, 0),
	SOC_SINGLE("DL56 Playback Switch", ISABELLE_DL56_INTF_CFG_REG,
		7, 1, 0),

	/* DMIC Switch */
	SOC_SINGLE("DMIC Switch", ISABELLE_DMIC_CFG_REG, 0, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget isabelle_dapm_widमाला_लो[] = अणु
	/* Inमाला_दो */
	SND_SOC_DAPM_INPUT("MAINMIC"),
	SND_SOC_DAPM_INPUT("HSMIC"),
	SND_SOC_DAPM_INPUT("SUBMIC"),
	SND_SOC_DAPM_INPUT("LINEIN1"),
	SND_SOC_DAPM_INPUT("LINEIN2"),
	SND_SOC_DAPM_INPUT("DMICDAT"),

	/* Outमाला_दो */
	SND_SOC_DAPM_OUTPUT("HSOL"),
	SND_SOC_DAPM_OUTPUT("HSOR"),
	SND_SOC_DAPM_OUTPUT("HFL"),
	SND_SOC_DAPM_OUTPUT("HFR"),
	SND_SOC_DAPM_OUTPUT("EP"),
	SND_SOC_DAPM_OUTPUT("LINEOUT1"),
	SND_SOC_DAPM_OUTPUT("LINEOUT2"),

	SND_SOC_DAPM_PGA("DL1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DL2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DL3", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DL4", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DL5", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DL6", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* Analog input muxes क्रम the capture amplअगरiers */
	SND_SOC_DAPM_MUX("Analog Left Capture Route",
			SND_SOC_NOPM, 0, 0, &amic1_control),
	SND_SOC_DAPM_MUX("Analog Right Capture Route",
			SND_SOC_NOPM, 0, 0, &amic2_control),

	SND_SOC_DAPM_MUX("Sidetone Audio Playback", SND_SOC_NOPM, 0, 0,
			&st_audio_control),
	SND_SOC_DAPM_MUX("Sidetone Voice Playback", SND_SOC_NOPM, 0, 0,
			&st_voice_control),

	/* AIF */
	SND_SOC_DAPM_AIF_IN("INTF1_SDI", शून्य, 0, ISABELLE_INTF_EN_REG, 7, 0),
	SND_SOC_DAPM_AIF_IN("INTF2_SDI", शून्य, 0, ISABELLE_INTF_EN_REG, 6, 0),

	SND_SOC_DAPM_AIF_OUT("INTF1_SDO", शून्य, 0, ISABELLE_INTF_EN_REG, 5, 0),
	SND_SOC_DAPM_AIF_OUT("INTF2_SDO", शून्य, 0, ISABELLE_INTF_EN_REG, 4, 0),

	SND_SOC_DAPM_OUT_DRV("ULATX1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("ULATX2", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("ULVTX1", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("ULVTX2", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* Analog Capture PGAs */
	SND_SOC_DAPM_PGA("MicAmp1", ISABELLE_AMIC_CFG_REG, 5, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("MicAmp2", ISABELLE_AMIC_CFG_REG, 4, 0, शून्य, 0),

	/* Auxiliary FM PGAs */
	SND_SOC_DAPM_PGA("APGA1", ISABELLE_APGA_CFG_REG, 7, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("APGA2", ISABELLE_APGA_CFG_REG, 6, 0, शून्य, 0),

	/* ADCs */
	SND_SOC_DAPM_ADC("ADC1", "Left Front Capture",
			ISABELLE_AMIC_CFG_REG, 7, 0),
	SND_SOC_DAPM_ADC("ADC2", "Right Front Capture",
			ISABELLE_AMIC_CFG_REG, 6, 0),

	/* Microphone Bias */
	SND_SOC_DAPM_SUPPLY("Headset Mic Bias", ISABELLE_ABIAS_CFG_REG,
			3, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Main Mic Bias", ISABELLE_ABIAS_CFG_REG,
			2, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Digital Mic1 Bias",
			ISABELLE_DBIAS_CFG_REG, 3, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Digital Mic2 Bias",
			ISABELLE_DBIAS_CFG_REG, 2, 0, शून्य, 0),

	/* Mixers */
	SND_SOC_DAPM_MIXER("Headset Left Mixer", SND_SOC_NOPM, 0, 0,
			isabelle_hs_left_mixer_controls,
			ARRAY_SIZE(isabelle_hs_left_mixer_controls)),
	SND_SOC_DAPM_MIXER("Headset Right Mixer", SND_SOC_NOPM, 0, 0,
			isabelle_hs_right_mixer_controls,
			ARRAY_SIZE(isabelle_hs_right_mixer_controls)),
	SND_SOC_DAPM_MIXER("Handsfree Left Mixer", SND_SOC_NOPM, 0, 0,
			isabelle_hf_left_mixer_controls,
			ARRAY_SIZE(isabelle_hf_left_mixer_controls)),
	SND_SOC_DAPM_MIXER("Handsfree Right Mixer", SND_SOC_NOPM, 0, 0,
			isabelle_hf_right_mixer_controls,
			ARRAY_SIZE(isabelle_hf_right_mixer_controls)),
	SND_SOC_DAPM_MIXER("LINEOUT1 Mixer", SND_SOC_NOPM, 0, 0,
			isabelle_aux_left_mixer_controls,
			ARRAY_SIZE(isabelle_aux_left_mixer_controls)),
	SND_SOC_DAPM_MIXER("LINEOUT2 Mixer", SND_SOC_NOPM, 0, 0,
			isabelle_aux_right_mixer_controls,
			ARRAY_SIZE(isabelle_aux_right_mixer_controls)),
	SND_SOC_DAPM_MIXER("Earphone Mixer", SND_SOC_NOPM, 0, 0,
			isabelle_ep_mixer_controls,
			ARRAY_SIZE(isabelle_ep_mixer_controls)),

	SND_SOC_DAPM_MIXER("DPGA1L Mixer", SND_SOC_NOPM, 0, 0,
			isabelle_dpga1_left_mixer_controls,
			ARRAY_SIZE(isabelle_dpga1_left_mixer_controls)),
	SND_SOC_DAPM_MIXER("DPGA1R Mixer", SND_SOC_NOPM, 0, 0,
			isabelle_dpga1_right_mixer_controls,
			ARRAY_SIZE(isabelle_dpga1_right_mixer_controls)),
	SND_SOC_DAPM_MIXER("DPGA2L Mixer", SND_SOC_NOPM, 0, 0,
			isabelle_dpga2_left_mixer_controls,
			ARRAY_SIZE(isabelle_dpga2_left_mixer_controls)),
	SND_SOC_DAPM_MIXER("DPGA2R Mixer", SND_SOC_NOPM, 0, 0,
			isabelle_dpga2_right_mixer_controls,
			ARRAY_SIZE(isabelle_dpga2_right_mixer_controls)),
	SND_SOC_DAPM_MIXER("DPGA3L Mixer", SND_SOC_NOPM, 0, 0,
			isabelle_dpga3_left_mixer_controls,
			ARRAY_SIZE(isabelle_dpga3_left_mixer_controls)),
	SND_SOC_DAPM_MIXER("DPGA3R Mixer", SND_SOC_NOPM, 0, 0,
			isabelle_dpga3_right_mixer_controls,
			ARRAY_SIZE(isabelle_dpga3_right_mixer_controls)),

	SND_SOC_DAPM_MIXER("RX1 Mixer", SND_SOC_NOPM, 0, 0,
			isabelle_rx1_mixer_controls,
			ARRAY_SIZE(isabelle_rx1_mixer_controls)),
	SND_SOC_DAPM_MIXER("RX2 Mixer", SND_SOC_NOPM, 0, 0,
			isabelle_rx2_mixer_controls,
			ARRAY_SIZE(isabelle_rx2_mixer_controls)),
	SND_SOC_DAPM_MIXER("RX3 Mixer", SND_SOC_NOPM, 0, 0,
			isabelle_rx3_mixer_controls,
			ARRAY_SIZE(isabelle_rx3_mixer_controls)),
	SND_SOC_DAPM_MIXER("RX4 Mixer", SND_SOC_NOPM, 0, 0,
			isabelle_rx4_mixer_controls,
			ARRAY_SIZE(isabelle_rx4_mixer_controls)),
	SND_SOC_DAPM_MIXER("RX5 Mixer", SND_SOC_NOPM, 0, 0,
			isabelle_rx5_mixer_controls,
			ARRAY_SIZE(isabelle_rx5_mixer_controls)),
	SND_SOC_DAPM_MIXER("RX6 Mixer", SND_SOC_NOPM, 0, 0,
			isabelle_rx6_mixer_controls,
			ARRAY_SIZE(isabelle_rx6_mixer_controls)),

	/* DACs */
	SND_SOC_DAPM_DAC("DAC1L", "Headset Playback", ISABELLE_DAC_CFG_REG,
			5, 0),
	SND_SOC_DAPM_DAC("DAC1R", "Headset Playback", ISABELLE_DAC_CFG_REG,
			4, 0),
	SND_SOC_DAPM_DAC("DAC2L", "Handsfree Playback", ISABELLE_DAC_CFG_REG,
			3, 0),
	SND_SOC_DAPM_DAC("DAC2R", "Handsfree Playback", ISABELLE_DAC_CFG_REG,
			2, 0),
	SND_SOC_DAPM_DAC("DAC3L", "Lineout Playback", ISABELLE_DAC_CFG_REG,
			1, 0),
	SND_SOC_DAPM_DAC("DAC3R", "Lineout Playback", ISABELLE_DAC_CFG_REG,
			0, 0),

	/* Analog Playback PGAs */
	SND_SOC_DAPM_PGA("Sidetone Audio PGA", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Sidetone Voice PGA", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("HF Left PGA", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("HF Right PGA", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DPGA1L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DPGA1R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DPGA2L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DPGA2R", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DPGA3L", SND_SOC_NOPM, 0, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("DPGA3R", SND_SOC_NOPM, 0, 0, शून्य, 0),

	/* Analog Playback Mux */
	SND_SOC_DAPM_MUX("RX1 Playback", ISABELLE_ALU_RX_EN_REG, 5, 0,
			&rx1_mux_controls),
	SND_SOC_DAPM_MUX("RX2 Playback", ISABELLE_ALU_RX_EN_REG, 4, 0,
			&rx2_mux_controls),

	/* TX Select */
	SND_SOC_DAPM_MUX("ATX Select", ISABELLE_TX_INPUT_CFG_REG,
			7, 0, &atx_mux_controls),
	SND_SOC_DAPM_MUX("VTX Select", ISABELLE_TX_INPUT_CFG_REG,
			6, 0, &vtx_mux_controls),

	SND_SOC_DAPM_SWITCH("Earphone Playback", SND_SOC_NOPM, 0, 0,
			&ep_path_enable_control),

	/* Output Drivers */
	SND_SOC_DAPM_OUT_DRV("HS Left Driver", ISABELLE_HSDRV_CFG2_REG,
			1, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("HS Right Driver", ISABELLE_HSDRV_CFG2_REG,
			0, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("LINEOUT1 Left Driver", ISABELLE_LINEAMP_CFG_REG,
			1, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("LINEOUT2 Right Driver", ISABELLE_LINEAMP_CFG_REG,
			0, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("Earphone Driver", ISABELLE_EARDRV_CFG2_REG,
			1, 0, शून्य, 0),

	SND_SOC_DAPM_OUT_DRV("HF Left Driver", ISABELLE_HFDRV_CFG_REG,
			1, 0, शून्य, 0),
	SND_SOC_DAPM_OUT_DRV("HF Right Driver", ISABELLE_HFDRV_CFG_REG,
			0, 0, शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route isabelle_पूर्णांकercon[] = अणु
	/* Interface mapping */
	अणु "DL1", "DL12 Playback Switch", "INTF1_SDI" पूर्ण,
	अणु "DL2", "DL12 Playback Switch", "INTF1_SDI" पूर्ण,
	अणु "DL3", "DL34 Playback Switch", "INTF1_SDI" पूर्ण,
	अणु "DL4", "DL34 Playback Switch", "INTF1_SDI" पूर्ण,
	अणु "DL5", "DL56 Playback Switch", "INTF1_SDI" पूर्ण,
	अणु "DL6", "DL56 Playback Switch", "INTF1_SDI" पूर्ण,

	अणु "DL1", "DL12 Playback Switch", "INTF2_SDI" पूर्ण,
	अणु "DL2", "DL12 Playback Switch", "INTF2_SDI" पूर्ण,
	अणु "DL3", "DL34 Playback Switch", "INTF2_SDI" पूर्ण,
	अणु "DL4", "DL34 Playback Switch", "INTF2_SDI" पूर्ण,
	अणु "DL5", "DL56 Playback Switch", "INTF2_SDI" पूर्ण,
	अणु "DL6", "DL56 Playback Switch", "INTF2_SDI" पूर्ण,

	/* Input side mapping */
	अणु "Sidetone Audio PGA", शून्य, "Sidetone Audio Playback" पूर्ण,
	अणु "Sidetone Voice PGA", शून्य, "Sidetone Voice Playback" पूर्ण,

	अणु "RX1 Mixer", "ST1 Playback Switch", "Sidetone Audio PGA" पूर्ण,

	अणु "RX1 Mixer", "ST1 Playback Switch", "Sidetone Voice PGA" पूर्ण,
	अणु "RX1 Mixer", "DL1 Playback Switch", "DL1" पूर्ण,

	अणु "RX2 Mixer", "ST2 Playback Switch", "Sidetone Audio PGA" पूर्ण,

	अणु "RX2 Mixer", "ST2 Playback Switch", "Sidetone Voice PGA" पूर्ण,
	अणु "RX2 Mixer", "DL2 Playback Switch", "DL2" पूर्ण,

	अणु "RX3 Mixer", "ST1 Playback Switch", "Sidetone Voice PGA" पूर्ण,
	अणु "RX3 Mixer", "DL3 Playback Switch", "DL3" पूर्ण,

	अणु "RX4 Mixer", "ST2 Playback Switch", "Sidetone Voice PGA" पूर्ण,
	अणु "RX4 Mixer", "DL4 Playback Switch", "DL4" पूर्ण,

	अणु "RX5 Mixer", "ST1 Playback Switch", "Sidetone Voice PGA" पूर्ण,
	अणु "RX5 Mixer", "DL5 Playback Switch", "DL5" पूर्ण,

	अणु "RX6 Mixer", "ST2 Playback Switch", "Sidetone Voice PGA" पूर्ण,
	अणु "RX6 Mixer", "DL6 Playback Switch", "DL6" पूर्ण,

	/* Capture path */
	अणु "Analog Left Capture Route", "Headset Mic", "HSMIC" पूर्ण,
	अणु "Analog Left Capture Route", "Main Mic", "MAINMIC" पूर्ण,
	अणु "Analog Left Capture Route", "Aux/FM Left", "LINEIN1" पूर्ण,

	अणु "Analog Right Capture Route", "Sub Mic", "SUBMIC" पूर्ण,
	अणु "Analog Right Capture Route", "Aux/FM Right", "LINEIN2" पूर्ण,

	अणु "MicAmp1", शून्य, "Analog Left Capture Route" पूर्ण,
	अणु "MicAmp2", शून्य, "Analog Right Capture Route" पूर्ण,

	अणु "ADC1", शून्य, "MicAmp1" पूर्ण,
	अणु "ADC2", शून्य, "MicAmp2" पूर्ण,

	अणु "ATX Select", "AMIC1", "ADC1" पूर्ण,
	अणु "ATX Select", "DMIC", "DMICDAT" पूर्ण,
	अणु "ATX Select", "AMIC2", "ADC2" पूर्ण,

	अणु "VTX Select", "AMIC1", "ADC1" पूर्ण,
	अणु "VTX Select", "DMIC", "DMICDAT" पूर्ण,
	अणु "VTX Select", "AMIC2", "ADC2" पूर्ण,

	अणु "ULATX1", "ATX1 Filter Enable Switch", "ATX Select" पूर्ण,
	अणु "ULATX1", "ATX1 Filter Bypass Switch", "ATX Select" पूर्ण,
	अणु "ULATX2", "ATX2 Filter Enable Switch", "ATX Select" पूर्ण,
	अणु "ULATX2", "ATX2 Filter Bypass Switch", "ATX Select" पूर्ण,

	अणु "ULVTX1", "VTX1 Filter Enable Switch", "VTX Select" पूर्ण,
	अणु "ULVTX1", "VTX1 Filter Bypass Switch", "VTX Select" पूर्ण,
	अणु "ULVTX2", "VTX2 Filter Enable Switch", "VTX Select" पूर्ण,
	अणु "ULVTX2", "VTX2 Filter Bypass Switch", "VTX Select" पूर्ण,

	अणु "INTF1_SDO", "ULATX12 Capture Switch", "ULATX1" पूर्ण,
	अणु "INTF1_SDO", "ULATX12 Capture Switch", "ULATX2" पूर्ण,
	अणु "INTF2_SDO", "ULATX12 Capture Switch", "ULATX1" पूर्ण,
	अणु "INTF2_SDO", "ULATX12 Capture Switch", "ULATX2" पूर्ण,

	अणु "INTF1_SDO", शून्य, "ULVTX1" पूर्ण,
	अणु "INTF1_SDO", शून्य, "ULVTX2" पूर्ण,
	अणु "INTF2_SDO", शून्य, "ULVTX1" पूर्ण,
	अणु "INTF2_SDO", शून्य, "ULVTX2" पूर्ण,

	/* AFM Path */
	अणु "APGA1", शून्य, "LINEIN1" पूर्ण,
	अणु "APGA2", शून्य, "LINEIN2" पूर्ण,

	अणु "RX1 Playback", "VRX1 Filter Bypass Switch", "RX1 Mixer" पूर्ण,
	अणु "RX1 Playback", "ARX1 Filter Bypass Switch", "RX1 Mixer" पूर्ण,
	अणु "RX1 Playback", "RX1 Filter Enable Switch", "RX1 Mixer" पूर्ण,

	अणु "RX2 Playback", "VRX2 Filter Bypass Switch", "RX2 Mixer" पूर्ण,
	अणु "RX2 Playback", "ARX2 Filter Bypass Switch", "RX2 Mixer" पूर्ण,
	अणु "RX2 Playback", "RX2 Filter Enable Switch", "RX2 Mixer" पूर्ण,

	अणु "RX3 Playback", "ARX3 Filter Bypass Switch", "RX3 Mixer" पूर्ण,
	अणु "RX3 Playback", "RX3 Filter Enable Switch", "RX3 Mixer" पूर्ण,

	अणु "RX4 Playback", "ARX4 Filter Bypass Switch", "RX4 Mixer" पूर्ण,
	अणु "RX4 Playback", "RX4 Filter Enable Switch", "RX4 Mixer" पूर्ण,

	अणु "RX5 Playback", "ARX5 Filter Bypass Switch", "RX5 Mixer" पूर्ण,
	अणु "RX5 Playback", "RX5 Filter Enable Switch", "RX5 Mixer" पूर्ण,

	अणु "RX6 Playback", "ARX6 Filter Bypass Switch", "RX6 Mixer" पूर्ण,
	अणु "RX6 Playback", "RX6 Filter Enable Switch", "RX6 Mixer" पूर्ण,

	अणु "DPGA1L Mixer", "RX1 Playback Switch", "RX1 Playback" पूर्ण,
	अणु "DPGA1L Mixer", "RX3 Playback Switch", "RX3 Playback" पूर्ण,
	अणु "DPGA1L Mixer", "RX5 Playback Switch", "RX5 Playback" पूर्ण,

	अणु "DPGA1R Mixer", "RX2 Playback Switch", "RX2 Playback" पूर्ण,
	अणु "DPGA1R Mixer", "RX4 Playback Switch", "RX4 Playback" पूर्ण,
	अणु "DPGA1R Mixer", "RX6 Playback Switch", "RX6 Playback" पूर्ण,

	अणु "DPGA1L", शून्य, "DPGA1L Mixer" पूर्ण,
	अणु "DPGA1R", शून्य, "DPGA1R Mixer" पूर्ण,

	अणु "DAC1L", शून्य, "DPGA1L" पूर्ण,
	अणु "DAC1R", शून्य, "DPGA1R" पूर्ण,

	अणु "DPGA2L Mixer", "RX1 Playback Switch", "RX1 Playback" पूर्ण,
	अणु "DPGA2L Mixer", "RX2 Playback Switch", "RX2 Playback" पूर्ण,
	अणु "DPGA2L Mixer", "RX3 Playback Switch", "RX3 Playback" पूर्ण,
	अणु "DPGA2L Mixer", "RX4 Playback Switch", "RX4 Playback" पूर्ण,
	अणु "DPGA2L Mixer", "RX5 Playback Switch", "RX5 Playback" पूर्ण,
	अणु "DPGA2L Mixer", "RX6 Playback Switch", "RX6 Playback" पूर्ण,

	अणु "DPGA2R Mixer", "RX2 Playback Switch", "RX2 Playback" पूर्ण,
	अणु "DPGA2R Mixer", "RX4 Playback Switch", "RX4 Playback" पूर्ण,
	अणु "DPGA2R Mixer", "RX6 Playback Switch", "RX6 Playback" पूर्ण,

	अणु "DPGA2L", शून्य, "DPGA2L Mixer" पूर्ण,
	अणु "DPGA2R", शून्य, "DPGA2R Mixer" पूर्ण,

	अणु "DAC2L", शून्य, "DPGA2L" पूर्ण,
	अणु "DAC2R", शून्य, "DPGA2R" पूर्ण,

	अणु "DPGA3L Mixer", "RX1 Playback Switch", "RX1 Playback" पूर्ण,
	अणु "DPGA3L Mixer", "RX3 Playback Switch", "RX3 Playback" पूर्ण,
	अणु "DPGA3L Mixer", "RX5 Playback Switch", "RX5 Playback" पूर्ण,

	अणु "DPGA3R Mixer", "RX2 Playback Switch", "RX2 Playback" पूर्ण,
	अणु "DPGA3R Mixer", "RX4 Playback Switch", "RX4 Playback" पूर्ण,
	अणु "DPGA3R Mixer", "RX6 Playback Switch", "RX6 Playback" पूर्ण,

	अणु "DPGA3L", शून्य, "DPGA3L Mixer" पूर्ण,
	अणु "DPGA3R", शून्य, "DPGA3R Mixer" पूर्ण,

	अणु "DAC3L", शून्य, "DPGA3L" पूर्ण,
	अणु "DAC3R", शून्य, "DPGA3R" पूर्ण,

	अणु "Headset Left Mixer", "DAC1L Playback Switch", "DAC1L" पूर्ण,
	अणु "Headset Left Mixer", "APGA1 Playback Switch", "APGA1" पूर्ण,

	अणु "Headset Right Mixer", "DAC1R Playback Switch", "DAC1R" पूर्ण,
	अणु "Headset Right Mixer", "APGA2 Playback Switch", "APGA2" पूर्ण,

	अणु "HS Left Driver", शून्य, "Headset Left Mixer" पूर्ण,
	अणु "HS Right Driver", शून्य, "Headset Right Mixer" पूर्ण,

	अणु "HSOL", शून्य, "HS Left Driver" पूर्ण,
	अणु "HSOR", शून्य, "HS Right Driver" पूर्ण,

	/* Earphone playback path */
	अणु "Earphone Mixer", "DAC2L Playback Switch", "DAC2L" पूर्ण,
	अणु "Earphone Mixer", "APGA1 Playback Switch", "APGA1" पूर्ण,

	अणु "Earphone Playback", "Switch", "Earphone Mixer" पूर्ण,
	अणु "Earphone Driver", शून्य, "Earphone Playback" पूर्ण,
	अणु "EP", शून्य, "Earphone Driver" पूर्ण,

	अणु "Handsfree Left Mixer", "DAC2L Playback Switch", "DAC2L" पूर्ण,
	अणु "Handsfree Left Mixer", "APGA1 Playback Switch", "APGA1" पूर्ण,

	अणु "Handsfree Right Mixer", "DAC2R Playback Switch", "DAC2R" पूर्ण,
	अणु "Handsfree Right Mixer", "APGA2 Playback Switch", "APGA2" पूर्ण,

	अणु "HF Left PGA", शून्य, "Handsfree Left Mixer" पूर्ण,
	अणु "HF Right PGA", शून्य, "Handsfree Right Mixer" पूर्ण,

	अणु "HF Left Driver", शून्य, "HF Left PGA" पूर्ण,
	अणु "HF Right Driver", शून्य, "HF Right PGA" पूर्ण,

	अणु "HFL", शून्य, "HF Left Driver" पूर्ण,
	अणु "HFR", शून्य, "HF Right Driver" पूर्ण,

	अणु "LINEOUT1 Mixer", "DAC3L Playback Switch", "DAC3L" पूर्ण,
	अणु "LINEOUT1 Mixer", "APGA1 Playback Switch", "APGA1" पूर्ण,

	अणु "LINEOUT2 Mixer", "DAC3R Playback Switch", "DAC3R" पूर्ण,
	अणु "LINEOUT2 Mixer", "APGA2 Playback Switch", "APGA2" पूर्ण,

	अणु "LINEOUT1 Driver", शून्य, "LINEOUT1 Mixer" पूर्ण,
	अणु "LINEOUT2 Driver", शून्य, "LINEOUT2 Mixer" पूर्ण,

	अणु "LINEOUT1", शून्य, "LINEOUT1 Driver" पूर्ण,
	अणु "LINEOUT2", शून्य, "LINEOUT2 Driver" पूर्ण,
पूर्ण;

अटल पूर्णांक isabelle_hs_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	snd_soc_component_update_bits(dai->component, ISABELLE_DAC1_SOFTRAMP_REG,
			BIT(4), (mute ? BIT(4) : 0));

	वापस 0;
पूर्ण

अटल पूर्णांक isabelle_hf_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	snd_soc_component_update_bits(dai->component, ISABELLE_DAC2_SOFTRAMP_REG,
			BIT(4), (mute ? BIT(4) : 0));

	वापस 0;
पूर्ण

अटल पूर्णांक isabelle_line_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	snd_soc_component_update_bits(dai->component, ISABELLE_DAC3_SOFTRAMP_REG,
			BIT(4), (mute ? BIT(4) : 0));

	वापस 0;
पूर्ण

अटल पूर्णांक isabelle_set_bias_level(काष्ठा snd_soc_component *component,
				क्रमागत snd_soc_bias_level level)
अणु
	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		snd_soc_component_update_bits(component, ISABELLE_PWR_EN_REG,
				ISABELLE_CHIP_EN, BIT(0));
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, ISABELLE_PWR_EN_REG,
				ISABELLE_CHIP_EN, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक isabelle_hw_params(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *params,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 aअगर = 0;
	अचिन्हित पूर्णांक fs_val = 0;

	चयन (params_rate(params)) अणु
	हाल 8000:
		fs_val = ISABELLE_FS_RATE_8;
		अवरोध;
	हाल 11025:
		fs_val = ISABELLE_FS_RATE_11;
		अवरोध;
	हाल 12000:
		fs_val = ISABELLE_FS_RATE_12;
		अवरोध;
	हाल 16000:
		fs_val = ISABELLE_FS_RATE_16;
		अवरोध;
	हाल 22050:
		fs_val = ISABELLE_FS_RATE_22;
		अवरोध;
	हाल 24000:
		fs_val = ISABELLE_FS_RATE_24;
		अवरोध;
	हाल 32000:
		fs_val = ISABELLE_FS_RATE_32;
		अवरोध;
	हाल 44100:
		fs_val = ISABELLE_FS_RATE_44;
		अवरोध;
	हाल 48000:
		fs_val = ISABELLE_FS_RATE_48;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, ISABELLE_FS_RATE_CFG_REG,
			ISABELLE_FS_RATE_MASK, fs_val);

	/* bit size */
	चयन (params_width(params)) अणु
	हाल 20:
		aअगर |= ISABELLE_AIF_LENGTH_20;
		अवरोध;
	हाल 32:
		aअगर |= ISABELLE_AIF_LENGTH_32;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, ISABELLE_INTF_CFG_REG,
			ISABELLE_AIF_LENGTH_MASK, aअगर);

	वापस 0;
पूर्ण

अटल पूर्णांक isabelle_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	अचिन्हित पूर्णांक aअगर_val = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		aअगर_val &= ~ISABELLE_AIF_MS;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		aअगर_val |= ISABELLE_AIF_MS;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		aअगर_val |= ISABELLE_I2S_MODE;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		aअगर_val |= ISABELLE_LEFT_J_MODE;
		अवरोध;
	हाल SND_SOC_DAIFMT_PDM:
		aअगर_val |= ISABELLE_PDM_MODE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, ISABELLE_INTF_CFG_REG,
			(ISABELLE_AIF_MS | ISABELLE_AIF_FMT_MASK), aअगर_val);

	वापस 0;
पूर्ण

/* Rates supported by Isabelle driver */
#घोषणा ISABELLE_RATES		SNDRV_PCM_RATE_8000_48000

/* Formates supported by Isabelle driver. */
#घोषणा ISABELLE_FORMATS (SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops isabelle_hs_dai_ops = अणु
	.hw_params	= isabelle_hw_params,
	.set_fmt	= isabelle_set_dai_fmt,
	.mute_stream	= isabelle_hs_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops isabelle_hf_dai_ops = अणु
	.hw_params	= isabelle_hw_params,
	.set_fmt	= isabelle_set_dai_fmt,
	.mute_stream	= isabelle_hf_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops isabelle_line_dai_ops = अणु
	.hw_params	= isabelle_hw_params,
	.set_fmt	= isabelle_set_dai_fmt,
	.mute_stream	= isabelle_line_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops isabelle_ul_dai_ops = अणु
	.hw_params	= isabelle_hw_params,
	.set_fmt	= isabelle_set_dai_fmt,
पूर्ण;

/* ISABELLE dai काष्ठाure */
अटल काष्ठा snd_soc_dai_driver isabelle_dai[] = अणु
	अणु
		.name = "isabelle-dl1",
		.playback = अणु
			.stream_name = "Headset Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = ISABELLE_RATES,
			.क्रमmats = ISABELLE_FORMATS,
		पूर्ण,
		.ops = &isabelle_hs_dai_ops,
	पूर्ण,
	अणु
		.name = "isabelle-dl2",
		.playback = अणु
			.stream_name = "Handsfree Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = ISABELLE_RATES,
			.क्रमmats = ISABELLE_FORMATS,
		पूर्ण,
		.ops = &isabelle_hf_dai_ops,
	पूर्ण,
	अणु
		.name = "isabelle-lineout",
		.playback = अणु
			.stream_name = "Lineout Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = ISABELLE_RATES,
			.क्रमmats = ISABELLE_FORMATS,
		पूर्ण,
		.ops = &isabelle_line_dai_ops,
	पूर्ण,
	अणु
		.name = "isabelle-ul",
		.capture = अणु
			.stream_name = "Capture",
			.channels_min = 1,
			.channels_max = 2,
			.rates = ISABELLE_RATES,
			.क्रमmats = ISABELLE_FORMATS,
		पूर्ण,
		.ops = &isabelle_ul_dai_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_isabelle = अणु
	.set_bias_level		= isabelle_set_bias_level,
	.controls		= isabelle_snd_controls,
	.num_controls		= ARRAY_SIZE(isabelle_snd_controls),
	.dapm_widमाला_लो		= isabelle_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(isabelle_dapm_widमाला_लो),
	.dapm_routes		= isabelle_पूर्णांकercon,
	.num_dapm_routes	= ARRAY_SIZE(isabelle_पूर्णांकercon),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config isabelle_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = ISABELLE_MAX_REGISTER,
	.reg_शेषs = isabelle_reg_defs,
	.num_reg_शेषs = ARRAY_SIZE(isabelle_reg_defs),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक isabelle_i2c_probe(काष्ठा i2c_client *i2c,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *isabelle_regmap;
	पूर्णांक ret = 0;

	isabelle_regmap = devm_regmap_init_i2c(i2c, &isabelle_regmap_config);
	अगर (IS_ERR(isabelle_regmap)) अणु
		ret = PTR_ERR(isabelle_regmap);
		dev_err(&i2c->dev, "Failed to allocate register map: %d\n",
			ret);
		वापस ret;
	पूर्ण
	i2c_set_clientdata(i2c, isabelle_regmap);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
				&soc_component_dev_isabelle, isabelle_dai,
				ARRAY_SIZE(isabelle_dai));
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to register component: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id isabelle_i2c_id[] = अणु
	अणु "isabelle", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, isabelle_i2c_id);

अटल काष्ठा i2c_driver isabelle_i2c_driver = अणु
	.driver = अणु
		.name = "isabelle",
	पूर्ण,
	.probe = isabelle_i2c_probe,
	.id_table = isabelle_i2c_id,
पूर्ण;

module_i2c_driver(isabelle_i2c_driver);

MODULE_DESCRIPTION("ASoC ISABELLE driver");
MODULE_AUTHOR("Vishwas A Deshpande <vishwas.a.deshpande@ti.com>");
MODULE_AUTHOR("M R Swami Reddy <MR.Swami.Reddy@ti.com>");
MODULE_LICENSE("GPL v2");
