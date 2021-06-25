<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm8990.c  --  WM8990 ALSA Soc Audio driver
 *
 * Copyright 2008 Wolfson Microelectronics PLC.
 * Author: Liam Girdwood <lrg@slimlogic.co.uk>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <यंत्र/भाग64.h>

#समावेश "wm8990.h"

/* codec निजी data */
काष्ठा wm8990_priv अणु
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक sysclk;
	अचिन्हित पूर्णांक pcmclk;
पूर्ण;

#घोषणा wm8990_reset(c) snd_soc_component_ग_लिखो(c, WM8990_RESET, 0)

अटल स्थिर DECLARE_TLV_DB_SCALE(in_pga_tlv, -1650, 3000, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(out_mix_tlv, 0, -2100, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(out_pga_tlv, -7300, 600, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(out_dac_tlv, -7163, 0, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(in_adc_tlv, -7163, 1763, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(out_sidetone_tlv, -3600, 0, 0);

अटल पूर्णांक wm899x_outpga_put_volsw_vu(काष्ठा snd_kcontrol *kcontrol,
	काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	पूर्णांक reg = mc->reg;
	पूर्णांक ret;
	u16 val;

	ret = snd_soc_put_volsw(kcontrol, ucontrol);
	अगर (ret < 0)
		वापस ret;

	/* now hit the volume update bits (always bit 8) */
	val = snd_soc_component_पढ़ो(component, reg);
	वापस snd_soc_component_ग_लिखो(component, reg, val | 0x0100);
पूर्ण

#घोषणा SOC_WM899X_OUTPGA_SINGLE_R_TLV(xname, reg, shअगरt, max, invert,\
	tlv_array) \
	SOC_SINGLE_EXT_TLV(xname, reg, shअगरt, max, invert, \
		snd_soc_get_volsw, wm899x_outpga_put_volsw_vu, tlv_array)


अटल स्थिर अक्षर *wm8990_digital_sidetone[] =
	अणु"None", "Left ADC", "Right ADC", "Reserved"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(wm8990_left_digital_sidetone_क्रमागत,
			    WM8990_DIGITAL_SIDE_TONE,
			    WM8990_ADC_TO_DACL_SHIFT,
			    wm8990_digital_sidetone);

अटल SOC_ENUM_SINGLE_DECL(wm8990_right_digital_sidetone_क्रमागत,
			    WM8990_DIGITAL_SIDE_TONE,
			    WM8990_ADC_TO_DACR_SHIFT,
			    wm8990_digital_sidetone);

अटल स्थिर अक्षर *wm8990_adcmode[] =
	अणु"Hi-fi mode", "Voice mode 1", "Voice mode 2", "Voice mode 3"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(wm8990_right_adcmode_क्रमागत,
			    WM8990_ADC_CTRL,
			    WM8990_ADC_HPF_CUT_SHIFT,
			    wm8990_adcmode);

अटल स्थिर काष्ठा snd_kcontrol_new wm8990_snd_controls[] = अणु
/* INMIXL */
SOC_SINGLE("LIN12 PGA Boost", WM8990_INPUT_MIXER3, WM8990_L12MNBST_BIT, 1, 0),
SOC_SINGLE("LIN34 PGA Boost", WM8990_INPUT_MIXER3, WM8990_L34MNBST_BIT, 1, 0),
/* INMIXR */
SOC_SINGLE("RIN12 PGA Boost", WM8990_INPUT_MIXER3, WM8990_R12MNBST_BIT, 1, 0),
SOC_SINGLE("RIN34 PGA Boost", WM8990_INPUT_MIXER3, WM8990_R34MNBST_BIT, 1, 0),

/* LOMIX */
SOC_SINGLE_TLV("LOMIX LIN3 Bypass Volume", WM8990_OUTPUT_MIXER3,
	WM8990_LLI3LOVOL_SHIFT, WM8990_LLI3LOVOL_MASK, 1, out_mix_tlv),
SOC_SINGLE_TLV("LOMIX RIN12 PGA Bypass Volume", WM8990_OUTPUT_MIXER3,
	WM8990_LR12LOVOL_SHIFT, WM8990_LR12LOVOL_MASK, 1, out_mix_tlv),
SOC_SINGLE_TLV("LOMIX LIN12 PGA Bypass Volume", WM8990_OUTPUT_MIXER3,
	WM8990_LL12LOVOL_SHIFT, WM8990_LL12LOVOL_MASK, 1, out_mix_tlv),
SOC_SINGLE_TLV("LOMIX RIN3 Bypass Volume", WM8990_OUTPUT_MIXER5,
	WM8990_LRI3LOVOL_SHIFT, WM8990_LRI3LOVOL_MASK, 1, out_mix_tlv),
SOC_SINGLE_TLV("LOMIX AINRMUX Bypass Volume", WM8990_OUTPUT_MIXER5,
	WM8990_LRBLOVOL_SHIFT, WM8990_LRBLOVOL_MASK, 1, out_mix_tlv),
SOC_SINGLE_TLV("LOMIX AINLMUX Bypass Volume", WM8990_OUTPUT_MIXER5,
	WM8990_LRBLOVOL_SHIFT, WM8990_LRBLOVOL_MASK, 1, out_mix_tlv),

/* ROMIX */
SOC_SINGLE_TLV("ROMIX RIN3 Bypass Volume", WM8990_OUTPUT_MIXER4,
	WM8990_RRI3ROVOL_SHIFT, WM8990_RRI3ROVOL_MASK, 1, out_mix_tlv),
SOC_SINGLE_TLV("ROMIX LIN12 PGA Bypass Volume", WM8990_OUTPUT_MIXER4,
	WM8990_RL12ROVOL_SHIFT, WM8990_RL12ROVOL_MASK, 1, out_mix_tlv),
SOC_SINGLE_TLV("ROMIX RIN12 PGA Bypass Volume", WM8990_OUTPUT_MIXER4,
	WM8990_RR12ROVOL_SHIFT, WM8990_RR12ROVOL_MASK, 1, out_mix_tlv),
SOC_SINGLE_TLV("ROMIX LIN3 Bypass Volume", WM8990_OUTPUT_MIXER6,
	WM8990_RLI3ROVOL_SHIFT, WM8990_RLI3ROVOL_MASK, 1, out_mix_tlv),
SOC_SINGLE_TLV("ROMIX AINLMUX Bypass Volume", WM8990_OUTPUT_MIXER6,
	WM8990_RLBROVOL_SHIFT, WM8990_RLBROVOL_MASK, 1, out_mix_tlv),
SOC_SINGLE_TLV("ROMIX AINRMUX Bypass Volume", WM8990_OUTPUT_MIXER6,
	WM8990_RRBROVOL_SHIFT, WM8990_RRBROVOL_MASK, 1, out_mix_tlv),

/* LOUT */
SOC_WM899X_OUTPGA_SINGLE_R_TLV("LOUT Volume", WM8990_LEFT_OUTPUT_VOLUME,
	WM8990_LOUTVOL_SHIFT, WM8990_LOUTVOL_MASK, 0, out_pga_tlv),
SOC_SINGLE("LOUT ZC", WM8990_LEFT_OUTPUT_VOLUME, WM8990_LOZC_BIT, 1, 0),

/* ROUT */
SOC_WM899X_OUTPGA_SINGLE_R_TLV("ROUT Volume", WM8990_RIGHT_OUTPUT_VOLUME,
	WM8990_ROUTVOL_SHIFT, WM8990_ROUTVOL_MASK, 0, out_pga_tlv),
SOC_SINGLE("ROUT ZC", WM8990_RIGHT_OUTPUT_VOLUME, WM8990_ROZC_BIT, 1, 0),

/* LOPGA */
SOC_WM899X_OUTPGA_SINGLE_R_TLV("LOPGA Volume", WM8990_LEFT_OPGA_VOLUME,
	WM8990_LOPGAVOL_SHIFT, WM8990_LOPGAVOL_MASK, 0, out_pga_tlv),
SOC_SINGLE("LOPGA ZC Switch", WM8990_LEFT_OPGA_VOLUME,
	WM8990_LOPGAZC_BIT, 1, 0),

/* ROPGA */
SOC_WM899X_OUTPGA_SINGLE_R_TLV("ROPGA Volume", WM8990_RIGHT_OPGA_VOLUME,
	WM8990_ROPGAVOL_SHIFT, WM8990_ROPGAVOL_MASK, 0, out_pga_tlv),
SOC_SINGLE("ROPGA ZC Switch", WM8990_RIGHT_OPGA_VOLUME,
	WM8990_ROPGAZC_BIT, 1, 0),

SOC_SINGLE("LON Mute Switch", WM8990_LINE_OUTPUTS_VOLUME,
	WM8990_LONMUTE_BIT, 1, 0),
SOC_SINGLE("LOP Mute Switch", WM8990_LINE_OUTPUTS_VOLUME,
	WM8990_LOPMUTE_BIT, 1, 0),
SOC_SINGLE("LOP Attenuation Switch", WM8990_LINE_OUTPUTS_VOLUME,
	WM8990_LOATTN_BIT, 1, 0),
SOC_SINGLE("RON Mute Switch", WM8990_LINE_OUTPUTS_VOLUME,
	WM8990_RONMUTE_BIT, 1, 0),
SOC_SINGLE("ROP Mute Switch", WM8990_LINE_OUTPUTS_VOLUME,
	WM8990_ROPMUTE_BIT, 1, 0),
SOC_SINGLE("ROP Attenuation Switch", WM8990_LINE_OUTPUTS_VOLUME,
	WM8990_ROATTN_BIT, 1, 0),

SOC_SINGLE("OUT3 Mute Switch", WM8990_OUT3_4_VOLUME,
	WM8990_OUT3MUTE_BIT, 1, 0),
SOC_SINGLE("OUT3 Attenuation Switch", WM8990_OUT3_4_VOLUME,
	WM8990_OUT3ATTN_BIT, 1, 0),

SOC_SINGLE("OUT4 Mute Switch", WM8990_OUT3_4_VOLUME,
	WM8990_OUT4MUTE_BIT, 1, 0),
SOC_SINGLE("OUT4 Attenuation Switch", WM8990_OUT3_4_VOLUME,
	WM8990_OUT4ATTN_BIT, 1, 0),

SOC_SINGLE("Speaker Mode Switch", WM8990_CLASSD1,
	WM8990_CDMODE_BIT, 1, 0),

SOC_SINGLE("Speaker Output Attenuation Volume", WM8990_SPEAKER_VOLUME,
	WM8990_SPKATTN_SHIFT, WM8990_SPKATTN_MASK, 0),
SOC_SINGLE("Speaker DC Boost Volume", WM8990_CLASSD3,
	WM8990_DCGAIN_SHIFT, WM8990_DCGAIN_MASK, 0),
SOC_SINGLE("Speaker AC Boost Volume", WM8990_CLASSD3,
	WM8990_ACGAIN_SHIFT, WM8990_ACGAIN_MASK, 0),
SOC_SINGLE_TLV("Speaker Volume", WM8990_CLASSD4,
	WM8990_SPKVOL_SHIFT, WM8990_SPKVOL_MASK, 0, out_pga_tlv),
SOC_SINGLE("Speaker ZC Switch", WM8990_CLASSD4,
	WM8990_SPKZC_SHIFT, WM8990_SPKZC_MASK, 0),

SOC_WM899X_OUTPGA_SINGLE_R_TLV("Left DAC Digital Volume",
	WM8990_LEFT_DAC_DIGITAL_VOLUME,
	WM8990_DACL_VOL_SHIFT,
	WM8990_DACL_VOL_MASK,
	0,
	out_dac_tlv),

SOC_WM899X_OUTPGA_SINGLE_R_TLV("Right DAC Digital Volume",
	WM8990_RIGHT_DAC_DIGITAL_VOLUME,
	WM8990_DACR_VOL_SHIFT,
	WM8990_DACR_VOL_MASK,
	0,
	out_dac_tlv),

SOC_ENUM("Left Digital Sidetone", wm8990_left_digital_sidetone_क्रमागत),
SOC_ENUM("Right Digital Sidetone", wm8990_right_digital_sidetone_क्रमागत),

SOC_SINGLE_TLV("Left Digital Sidetone Volume", WM8990_DIGITAL_SIDE_TONE,
	WM8990_ADCL_DAC_SVOL_SHIFT, WM8990_ADCL_DAC_SVOL_MASK, 0,
	out_sidetone_tlv),
SOC_SINGLE_TLV("Right Digital Sidetone Volume", WM8990_DIGITAL_SIDE_TONE,
	WM8990_ADCR_DAC_SVOL_SHIFT, WM8990_ADCR_DAC_SVOL_MASK, 0,
	out_sidetone_tlv),

SOC_SINGLE("ADC Digital High Pass Filter Switch", WM8990_ADC_CTRL,
	WM8990_ADC_HPF_ENA_BIT, 1, 0),

SOC_ENUM("ADC HPF Mode", wm8990_right_adcmode_क्रमागत),

SOC_WM899X_OUTPGA_SINGLE_R_TLV("Left ADC Digital Volume",
	WM8990_LEFT_ADC_DIGITAL_VOLUME,
	WM8990_ADCL_VOL_SHIFT,
	WM8990_ADCL_VOL_MASK,
	0,
	in_adc_tlv),

SOC_WM899X_OUTPGA_SINGLE_R_TLV("Right ADC Digital Volume",
	WM8990_RIGHT_ADC_DIGITAL_VOLUME,
	WM8990_ADCR_VOL_SHIFT,
	WM8990_ADCR_VOL_MASK,
	0,
	in_adc_tlv),

SOC_WM899X_OUTPGA_SINGLE_R_TLV("LIN12 Volume",
	WM8990_LEFT_LINE_INPUT_1_2_VOLUME,
	WM8990_LIN12VOL_SHIFT,
	WM8990_LIN12VOL_MASK,
	0,
	in_pga_tlv),

SOC_SINGLE("LIN12 ZC Switch", WM8990_LEFT_LINE_INPUT_1_2_VOLUME,
	WM8990_LI12ZC_BIT, 1, 0),

SOC_SINGLE("LIN12 Mute Switch", WM8990_LEFT_LINE_INPUT_1_2_VOLUME,
	WM8990_LI12MUTE_BIT, 1, 0),

SOC_WM899X_OUTPGA_SINGLE_R_TLV("LIN34 Volume",
	WM8990_LEFT_LINE_INPUT_3_4_VOLUME,
	WM8990_LIN34VOL_SHIFT,
	WM8990_LIN34VOL_MASK,
	0,
	in_pga_tlv),

SOC_SINGLE("LIN34 ZC Switch", WM8990_LEFT_LINE_INPUT_3_4_VOLUME,
	WM8990_LI34ZC_BIT, 1, 0),

SOC_SINGLE("LIN34 Mute Switch", WM8990_LEFT_LINE_INPUT_3_4_VOLUME,
	WM8990_LI34MUTE_BIT, 1, 0),

SOC_WM899X_OUTPGA_SINGLE_R_TLV("RIN12 Volume",
	WM8990_RIGHT_LINE_INPUT_1_2_VOLUME,
	WM8990_RIN12VOL_SHIFT,
	WM8990_RIN12VOL_MASK,
	0,
	in_pga_tlv),

SOC_SINGLE("RIN12 ZC Switch", WM8990_RIGHT_LINE_INPUT_1_2_VOLUME,
	WM8990_RI12ZC_BIT, 1, 0),

SOC_SINGLE("RIN12 Mute Switch", WM8990_RIGHT_LINE_INPUT_1_2_VOLUME,
	WM8990_RI12MUTE_BIT, 1, 0),

SOC_WM899X_OUTPGA_SINGLE_R_TLV("RIN34 Volume",
	WM8990_RIGHT_LINE_INPUT_3_4_VOLUME,
	WM8990_RIN34VOL_SHIFT,
	WM8990_RIN34VOL_MASK,
	0,
	in_pga_tlv),

SOC_SINGLE("RIN34 ZC Switch", WM8990_RIGHT_LINE_INPUT_3_4_VOLUME,
	WM8990_RI34ZC_BIT, 1, 0),

SOC_SINGLE("RIN34 Mute Switch", WM8990_RIGHT_LINE_INPUT_3_4_VOLUME,
	WM8990_RI34MUTE_BIT, 1, 0),

पूर्ण;

/*
 * _DAPM_ Controls
 */

अटल पूर्णांक ouपंचांगixer_event(काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u32 reg_shअगरt = kcontrol->निजी_value & 0xfff;
	पूर्णांक ret = 0;
	u16 reg;

	चयन (reg_shअगरt) अणु
	हाल WM8990_SPEAKER_MIXER | (WM8990_LDSPK_BIT << 8) :
		reg = snd_soc_component_पढ़ो(component, WM8990_OUTPUT_MIXER1);
		अगर (reg & WM8990_LDLO) अणु
			prपूर्णांकk(KERN_WARNING
			"Cannot set as Output Mixer 1 LDLO Set\n");
			ret = -1;
		पूर्ण
		अवरोध;
	हाल WM8990_SPEAKER_MIXER | (WM8990_RDSPK_BIT << 8):
		reg = snd_soc_component_पढ़ो(component, WM8990_OUTPUT_MIXER2);
		अगर (reg & WM8990_RDRO) अणु
			prपूर्णांकk(KERN_WARNING
			"Cannot set as Output Mixer 2 RDRO Set\n");
			ret = -1;
		पूर्ण
		अवरोध;
	हाल WM8990_OUTPUT_MIXER1 | (WM8990_LDLO_BIT << 8):
		reg = snd_soc_component_पढ़ो(component, WM8990_SPEAKER_MIXER);
		अगर (reg & WM8990_LDSPK) अणु
			prपूर्णांकk(KERN_WARNING
			"Cannot set as Speaker Mixer LDSPK Set\n");
			ret = -1;
		पूर्ण
		अवरोध;
	हाल WM8990_OUTPUT_MIXER2 | (WM8990_RDRO_BIT << 8):
		reg = snd_soc_component_पढ़ो(component, WM8990_SPEAKER_MIXER);
		अगर (reg & WM8990_RDSPK) अणु
			prपूर्णांकk(KERN_WARNING
			"Cannot set as Speaker Mixer RDSPK Set\n");
			ret = -1;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/* INMIX dB values */
अटल स्थिर DECLARE_TLV_DB_SCALE(in_mix_tlv, -1200, 600, 0);

/* Left In PGA Connections */
अटल स्थिर काष्ठा snd_kcontrol_new wm8990_dapm_lin12_pga_controls[] = अणु
SOC_DAPM_SINGLE("LIN1 Switch", WM8990_INPUT_MIXER2, WM8990_LMN1_BIT, 1, 0),
SOC_DAPM_SINGLE("LIN2 Switch", WM8990_INPUT_MIXER2, WM8990_LMP2_BIT, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8990_dapm_lin34_pga_controls[] = अणु
SOC_DAPM_SINGLE("LIN3 Switch", WM8990_INPUT_MIXER2, WM8990_LMN3_BIT, 1, 0),
SOC_DAPM_SINGLE("LIN4 Switch", WM8990_INPUT_MIXER2, WM8990_LMP4_BIT, 1, 0),
पूर्ण;

/* Right In PGA Connections */
अटल स्थिर काष्ठा snd_kcontrol_new wm8990_dapm_rin12_pga_controls[] = अणु
SOC_DAPM_SINGLE("RIN1 Switch", WM8990_INPUT_MIXER2, WM8990_RMN1_BIT, 1, 0),
SOC_DAPM_SINGLE("RIN2 Switch", WM8990_INPUT_MIXER2, WM8990_RMP2_BIT, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8990_dapm_rin34_pga_controls[] = अणु
SOC_DAPM_SINGLE("RIN3 Switch", WM8990_INPUT_MIXER2, WM8990_RMN3_BIT, 1, 0),
SOC_DAPM_SINGLE("RIN4 Switch", WM8990_INPUT_MIXER2, WM8990_RMP4_BIT, 1, 0),
पूर्ण;

/* INMIXL */
अटल स्थिर काष्ठा snd_kcontrol_new wm8990_dapm_inmixl_controls[] = अणु
SOC_DAPM_SINGLE_TLV("Record Left Volume", WM8990_INPUT_MIXER3,
	WM8990_LDBVOL_SHIFT, WM8990_LDBVOL_MASK, 0, in_mix_tlv),
SOC_DAPM_SINGLE_TLV("LIN2 Volume", WM8990_INPUT_MIXER5, WM8990_LI2BVOL_SHIFT,
	7, 0, in_mix_tlv),
SOC_DAPM_SINGLE("LINPGA12 Switch", WM8990_INPUT_MIXER3, WM8990_L12MNB_BIT,
	1, 0),
SOC_DAPM_SINGLE("LINPGA34 Switch", WM8990_INPUT_MIXER3, WM8990_L34MNB_BIT,
	1, 0),
पूर्ण;

/* INMIXR */
अटल स्थिर काष्ठा snd_kcontrol_new wm8990_dapm_inmixr_controls[] = अणु
SOC_DAPM_SINGLE_TLV("Record Right Volume", WM8990_INPUT_MIXER4,
	WM8990_RDBVOL_SHIFT, WM8990_RDBVOL_MASK, 0, in_mix_tlv),
SOC_DAPM_SINGLE_TLV("RIN2 Volume", WM8990_INPUT_MIXER6, WM8990_RI2BVOL_SHIFT,
	7, 0, in_mix_tlv),
SOC_DAPM_SINGLE("RINPGA12 Switch", WM8990_INPUT_MIXER3, WM8990_L12MNB_BIT,
	1, 0),
SOC_DAPM_SINGLE("RINPGA34 Switch", WM8990_INPUT_MIXER3, WM8990_L34MNB_BIT,
	1, 0),
पूर्ण;

/* AINLMUX */
अटल स्थिर अक्षर *wm8990_ainlmux[] =
	अणु"INMIXL Mix", "RXVOICE Mix", "DIFFINL Mix"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(wm8990_ainlmux_क्रमागत,
			    WM8990_INPUT_MIXER1, WM8990_AINLMODE_SHIFT,
			    wm8990_ainlmux);

अटल स्थिर काष्ठा snd_kcontrol_new wm8990_dapm_ainlmux_controls =
SOC_DAPM_ENUM("Route", wm8990_ainlmux_क्रमागत);

/* DIFFINL */

/* AINRMUX */
अटल स्थिर अक्षर *wm8990_ainrmux[] =
	अणु"INMIXR Mix", "RXVOICE Mix", "DIFFINR Mix"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(wm8990_ainrmux_क्रमागत,
			    WM8990_INPUT_MIXER1, WM8990_AINRMODE_SHIFT,
			    wm8990_ainrmux);

अटल स्थिर काष्ठा snd_kcontrol_new wm8990_dapm_ainrmux_controls =
SOC_DAPM_ENUM("Route", wm8990_ainrmux_क्रमागत);

/* LOMIX */
अटल स्थिर काष्ठा snd_kcontrol_new wm8990_dapm_lomix_controls[] = अणु
SOC_DAPM_SINGLE("LOMIX Right ADC Bypass Switch", WM8990_OUTPUT_MIXER1,
	WM8990_LRBLO_BIT, 1, 0),
SOC_DAPM_SINGLE("LOMIX Left ADC Bypass Switch", WM8990_OUTPUT_MIXER1,
	WM8990_LLBLO_BIT, 1, 0),
SOC_DAPM_SINGLE("LOMIX RIN3 Bypass Switch", WM8990_OUTPUT_MIXER1,
	WM8990_LRI3LO_BIT, 1, 0),
SOC_DAPM_SINGLE("LOMIX LIN3 Bypass Switch", WM8990_OUTPUT_MIXER1,
	WM8990_LLI3LO_BIT, 1, 0),
SOC_DAPM_SINGLE("LOMIX RIN12 PGA Bypass Switch", WM8990_OUTPUT_MIXER1,
	WM8990_LR12LO_BIT, 1, 0),
SOC_DAPM_SINGLE("LOMIX LIN12 PGA Bypass Switch", WM8990_OUTPUT_MIXER1,
	WM8990_LL12LO_BIT, 1, 0),
SOC_DAPM_SINGLE("LOMIX Left DAC Switch", WM8990_OUTPUT_MIXER1,
	WM8990_LDLO_BIT, 1, 0),
पूर्ण;

/* ROMIX */
अटल स्थिर काष्ठा snd_kcontrol_new wm8990_dapm_romix_controls[] = अणु
SOC_DAPM_SINGLE("ROMIX Left ADC Bypass Switch", WM8990_OUTPUT_MIXER2,
	WM8990_RLBRO_BIT, 1, 0),
SOC_DAPM_SINGLE("ROMIX Right ADC Bypass Switch", WM8990_OUTPUT_MIXER2,
	WM8990_RRBRO_BIT, 1, 0),
SOC_DAPM_SINGLE("ROMIX LIN3 Bypass Switch", WM8990_OUTPUT_MIXER2,
	WM8990_RLI3RO_BIT, 1, 0),
SOC_DAPM_SINGLE("ROMIX RIN3 Bypass Switch", WM8990_OUTPUT_MIXER2,
	WM8990_RRI3RO_BIT, 1, 0),
SOC_DAPM_SINGLE("ROMIX LIN12 PGA Bypass Switch", WM8990_OUTPUT_MIXER2,
	WM8990_RL12RO_BIT, 1, 0),
SOC_DAPM_SINGLE("ROMIX RIN12 PGA Bypass Switch", WM8990_OUTPUT_MIXER2,
	WM8990_RR12RO_BIT, 1, 0),
SOC_DAPM_SINGLE("ROMIX Right DAC Switch", WM8990_OUTPUT_MIXER2,
	WM8990_RDRO_BIT, 1, 0),
पूर्ण;

/* LONMIX */
अटल स्थिर काष्ठा snd_kcontrol_new wm8990_dapm_lonmix_controls[] = अणु
SOC_DAPM_SINGLE("LONMIX Left Mixer PGA Switch", WM8990_LINE_MIXER1,
	WM8990_LLOPGALON_BIT, 1, 0),
SOC_DAPM_SINGLE("LONMIX Right Mixer PGA Switch", WM8990_LINE_MIXER1,
	WM8990_LROPGALON_BIT, 1, 0),
SOC_DAPM_SINGLE("LONMIX Inverted LOP Switch", WM8990_LINE_MIXER1,
	WM8990_LOPLON_BIT, 1, 0),
पूर्ण;

/* LOPMIX */
अटल स्थिर काष्ठा snd_kcontrol_new wm8990_dapm_lopmix_controls[] = अणु
SOC_DAPM_SINGLE("LOPMIX Right Mic Bypass Switch", WM8990_LINE_MIXER1,
	WM8990_LR12LOP_BIT, 1, 0),
SOC_DAPM_SINGLE("LOPMIX Left Mic Bypass Switch", WM8990_LINE_MIXER1,
	WM8990_LL12LOP_BIT, 1, 0),
SOC_DAPM_SINGLE("LOPMIX Left Mixer PGA Switch", WM8990_LINE_MIXER1,
	WM8990_LLOPGALOP_BIT, 1, 0),
पूर्ण;

/* RONMIX */
अटल स्थिर काष्ठा snd_kcontrol_new wm8990_dapm_ronmix_controls[] = अणु
SOC_DAPM_SINGLE("RONMIX Right Mixer PGA Switch", WM8990_LINE_MIXER2,
	WM8990_RROPGARON_BIT, 1, 0),
SOC_DAPM_SINGLE("RONMIX Left Mixer PGA Switch", WM8990_LINE_MIXER2,
	WM8990_RLOPGARON_BIT, 1, 0),
SOC_DAPM_SINGLE("RONMIX Inverted ROP Switch", WM8990_LINE_MIXER2,
	WM8990_ROPRON_BIT, 1, 0),
पूर्ण;

/* ROPMIX */
अटल स्थिर काष्ठा snd_kcontrol_new wm8990_dapm_ropmix_controls[] = अणु
SOC_DAPM_SINGLE("ROPMIX Left Mic Bypass Switch", WM8990_LINE_MIXER2,
	WM8990_RL12ROP_BIT, 1, 0),
SOC_DAPM_SINGLE("ROPMIX Right Mic Bypass Switch", WM8990_LINE_MIXER2,
	WM8990_RR12ROP_BIT, 1, 0),
SOC_DAPM_SINGLE("ROPMIX Right Mixer PGA Switch", WM8990_LINE_MIXER2,
	WM8990_RROPGAROP_BIT, 1, 0),
पूर्ण;

/* OUT3MIX */
अटल स्थिर काष्ठा snd_kcontrol_new wm8990_dapm_out3mix_controls[] = अणु
SOC_DAPM_SINGLE("OUT3MIX LIN4/RXP Bypass Switch", WM8990_OUT3_4_MIXER,
	WM8990_LI4O3_BIT, 1, 0),
SOC_DAPM_SINGLE("OUT3MIX Left Out PGA Switch", WM8990_OUT3_4_MIXER,
	WM8990_LPGAO3_BIT, 1, 0),
पूर्ण;

/* OUT4MIX */
अटल स्थिर काष्ठा snd_kcontrol_new wm8990_dapm_out4mix_controls[] = अणु
SOC_DAPM_SINGLE("OUT4MIX Right Out PGA Switch", WM8990_OUT3_4_MIXER,
	WM8990_RPGAO4_BIT, 1, 0),
SOC_DAPM_SINGLE("OUT4MIX RIN4/RXP Bypass Switch", WM8990_OUT3_4_MIXER,
	WM8990_RI4O4_BIT, 1, 0),
पूर्ण;

/* SPKMIX */
अटल स्थिर काष्ठा snd_kcontrol_new wm8990_dapm_spkmix_controls[] = अणु
SOC_DAPM_SINGLE("SPKMIX LIN2 Bypass Switch", WM8990_SPEAKER_MIXER,
	WM8990_LI2SPK_BIT, 1, 0),
SOC_DAPM_SINGLE("SPKMIX LADC Bypass Switch", WM8990_SPEAKER_MIXER,
	WM8990_LB2SPK_BIT, 1, 0),
SOC_DAPM_SINGLE("SPKMIX Left Mixer PGA Switch", WM8990_SPEAKER_MIXER,
	WM8990_LOPGASPK_BIT, 1, 0),
SOC_DAPM_SINGLE("SPKMIX Left DAC Switch", WM8990_SPEAKER_MIXER,
	WM8990_LDSPK_BIT, 1, 0),
SOC_DAPM_SINGLE("SPKMIX Right DAC Switch", WM8990_SPEAKER_MIXER,
	WM8990_RDSPK_BIT, 1, 0),
SOC_DAPM_SINGLE("SPKMIX Right Mixer PGA Switch", WM8990_SPEAKER_MIXER,
	WM8990_ROPGASPK_BIT, 1, 0),
SOC_DAPM_SINGLE("SPKMIX RADC Bypass Switch", WM8990_SPEAKER_MIXER,
	WM8990_RL12ROP_BIT, 1, 0),
SOC_DAPM_SINGLE("SPKMIX RIN2 Bypass Switch", WM8990_SPEAKER_MIXER,
	WM8990_RI2SPK_BIT, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8990_dapm_widमाला_लो[] = अणु
/* Input Side */
/* Input Lines */
SND_SOC_DAPM_INPUT("LIN1"),
SND_SOC_DAPM_INPUT("LIN2"),
SND_SOC_DAPM_INPUT("LIN3"),
SND_SOC_DAPM_INPUT("LIN4/RXN"),
SND_SOC_DAPM_INPUT("RIN3"),
SND_SOC_DAPM_INPUT("RIN4/RXP"),
SND_SOC_DAPM_INPUT("RIN1"),
SND_SOC_DAPM_INPUT("RIN2"),
SND_SOC_DAPM_INPUT("Internal ADC Source"),

SND_SOC_DAPM_SUPPLY("INL", WM8990_POWER_MANAGEMENT_2, WM8990_AINL_ENA_BIT, 0,
		    शून्य, 0),
SND_SOC_DAPM_SUPPLY("INR", WM8990_POWER_MANAGEMENT_2, WM8990_AINR_ENA_BIT, 0,
		    शून्य, 0),

/* DACs */
SND_SOC_DAPM_ADC("Left ADC", "Left Capture", WM8990_POWER_MANAGEMENT_2,
	WM8990_ADCL_ENA_BIT, 0),
SND_SOC_DAPM_ADC("Right ADC", "Right Capture", WM8990_POWER_MANAGEMENT_2,
	WM8990_ADCR_ENA_BIT, 0),

/* Input PGAs */
SND_SOC_DAPM_MIXER("LIN12 PGA", WM8990_POWER_MANAGEMENT_2, WM8990_LIN12_ENA_BIT,
	0, &wm8990_dapm_lin12_pga_controls[0],
	ARRAY_SIZE(wm8990_dapm_lin12_pga_controls)),
SND_SOC_DAPM_MIXER("LIN34 PGA", WM8990_POWER_MANAGEMENT_2, WM8990_LIN34_ENA_BIT,
	0, &wm8990_dapm_lin34_pga_controls[0],
	ARRAY_SIZE(wm8990_dapm_lin34_pga_controls)),
SND_SOC_DAPM_MIXER("RIN12 PGA", WM8990_POWER_MANAGEMENT_2, WM8990_RIN12_ENA_BIT,
	0, &wm8990_dapm_rin12_pga_controls[0],
	ARRAY_SIZE(wm8990_dapm_rin12_pga_controls)),
SND_SOC_DAPM_MIXER("RIN34 PGA", WM8990_POWER_MANAGEMENT_2, WM8990_RIN34_ENA_BIT,
	0, &wm8990_dapm_rin34_pga_controls[0],
	ARRAY_SIZE(wm8990_dapm_rin34_pga_controls)),

/* INMIXL */
SND_SOC_DAPM_MIXER("INMIXL", SND_SOC_NOPM, 0, 0,
	&wm8990_dapm_inmixl_controls[0],
	ARRAY_SIZE(wm8990_dapm_inmixl_controls)),

/* AINLMUX */
SND_SOC_DAPM_MUX("AINLMUX", SND_SOC_NOPM, 0, 0, &wm8990_dapm_ainlmux_controls),

/* INMIXR */
SND_SOC_DAPM_MIXER("INMIXR", SND_SOC_NOPM, 0, 0,
	&wm8990_dapm_inmixr_controls[0],
	ARRAY_SIZE(wm8990_dapm_inmixr_controls)),

/* AINRMUX */
SND_SOC_DAPM_MUX("AINRMUX", SND_SOC_NOPM, 0, 0, &wm8990_dapm_ainrmux_controls),

/* Output Side */
/* DACs */
SND_SOC_DAPM_DAC("Left DAC", "Left Playback", WM8990_POWER_MANAGEMENT_3,
	WM8990_DACL_ENA_BIT, 0),
SND_SOC_DAPM_DAC("Right DAC", "Right Playback", WM8990_POWER_MANAGEMENT_3,
	WM8990_DACR_ENA_BIT, 0),

/* LOMIX */
SND_SOC_DAPM_MIXER_E("LOMIX", WM8990_POWER_MANAGEMENT_3, WM8990_LOMIX_ENA_BIT,
	0, &wm8990_dapm_lomix_controls[0],
	ARRAY_SIZE(wm8990_dapm_lomix_controls),
	ouपंचांगixer_event, SND_SOC_DAPM_PRE_REG),

/* LONMIX */
SND_SOC_DAPM_MIXER("LONMIX", WM8990_POWER_MANAGEMENT_3, WM8990_LON_ENA_BIT, 0,
	&wm8990_dapm_lonmix_controls[0],
	ARRAY_SIZE(wm8990_dapm_lonmix_controls)),

/* LOPMIX */
SND_SOC_DAPM_MIXER("LOPMIX", WM8990_POWER_MANAGEMENT_3, WM8990_LOP_ENA_BIT, 0,
	&wm8990_dapm_lopmix_controls[0],
	ARRAY_SIZE(wm8990_dapm_lopmix_controls)),

/* OUT3MIX */
SND_SOC_DAPM_MIXER("OUT3MIX", WM8990_POWER_MANAGEMENT_1, WM8990_OUT3_ENA_BIT, 0,
	&wm8990_dapm_out3mix_controls[0],
	ARRAY_SIZE(wm8990_dapm_out3mix_controls)),

/* SPKMIX */
SND_SOC_DAPM_MIXER_E("SPKMIX", WM8990_POWER_MANAGEMENT_1, WM8990_SPK_ENA_BIT, 0,
	&wm8990_dapm_spkmix_controls[0],
	ARRAY_SIZE(wm8990_dapm_spkmix_controls), ouपंचांगixer_event,
	SND_SOC_DAPM_PRE_REG),

/* OUT4MIX */
SND_SOC_DAPM_MIXER("OUT4MIX", WM8990_POWER_MANAGEMENT_1, WM8990_OUT4_ENA_BIT, 0,
	&wm8990_dapm_out4mix_controls[0],
	ARRAY_SIZE(wm8990_dapm_out4mix_controls)),

/* ROPMIX */
SND_SOC_DAPM_MIXER("ROPMIX", WM8990_POWER_MANAGEMENT_3, WM8990_ROP_ENA_BIT, 0,
	&wm8990_dapm_ropmix_controls[0],
	ARRAY_SIZE(wm8990_dapm_ropmix_controls)),

/* RONMIX */
SND_SOC_DAPM_MIXER("RONMIX", WM8990_POWER_MANAGEMENT_3, WM8990_RON_ENA_BIT, 0,
	&wm8990_dapm_ronmix_controls[0],
	ARRAY_SIZE(wm8990_dapm_ronmix_controls)),

/* ROMIX */
SND_SOC_DAPM_MIXER_E("ROMIX", WM8990_POWER_MANAGEMENT_3, WM8990_ROMIX_ENA_BIT,
	0, &wm8990_dapm_romix_controls[0],
	ARRAY_SIZE(wm8990_dapm_romix_controls),
	ouपंचांगixer_event, SND_SOC_DAPM_PRE_REG),

/* LOUT PGA */
SND_SOC_DAPM_PGA("LOUT PGA", WM8990_POWER_MANAGEMENT_1, WM8990_LOUT_ENA_BIT, 0,
	शून्य, 0),

/* ROUT PGA */
SND_SOC_DAPM_PGA("ROUT PGA", WM8990_POWER_MANAGEMENT_1, WM8990_ROUT_ENA_BIT, 0,
	शून्य, 0),

/* LOPGA */
SND_SOC_DAPM_PGA("LOPGA", WM8990_POWER_MANAGEMENT_3, WM8990_LOPGA_ENA_BIT, 0,
	शून्य, 0),

/* ROPGA */
SND_SOC_DAPM_PGA("ROPGA", WM8990_POWER_MANAGEMENT_3, WM8990_ROPGA_ENA_BIT, 0,
	शून्य, 0),

/* MICBIAS */
SND_SOC_DAPM_SUPPLY("MICBIAS", WM8990_POWER_MANAGEMENT_1,
		    WM8990_MICBIAS_ENA_BIT, 0, शून्य, 0),

SND_SOC_DAPM_OUTPUT("LON"),
SND_SOC_DAPM_OUTPUT("LOP"),
SND_SOC_DAPM_OUTPUT("OUT3"),
SND_SOC_DAPM_OUTPUT("LOUT"),
SND_SOC_DAPM_OUTPUT("SPKN"),
SND_SOC_DAPM_OUTPUT("SPKP"),
SND_SOC_DAPM_OUTPUT("ROUT"),
SND_SOC_DAPM_OUTPUT("OUT4"),
SND_SOC_DAPM_OUTPUT("ROP"),
SND_SOC_DAPM_OUTPUT("RON"),

SND_SOC_DAPM_OUTPUT("Internal DAC Sink"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8990_dapm_routes[] = अणु
	/* Make DACs turn on when playing even अगर not mixed पूर्णांकo any outमाला_दो */
	अणु"Internal DAC Sink", शून्य, "Left DAC"पूर्ण,
	अणु"Internal DAC Sink", शून्य, "Right DAC"पूर्ण,

	/* Make ADCs turn on when recording even अगर not mixed from any inमाला_दो */
	अणु"Left ADC", शून्य, "Internal ADC Source"पूर्ण,
	अणु"Right ADC", शून्य, "Internal ADC Source"पूर्ण,

	अणु"AINLMUX", शून्य, "INL"पूर्ण,
	अणु"INMIXL", शून्य, "INL"पूर्ण,
	अणु"AINRMUX", शून्य, "INR"पूर्ण,
	अणु"INMIXR", शून्य, "INR"पूर्ण,

	/* Input Side */
	/* LIN12 PGA */
	अणु"LIN12 PGA", "LIN1 Switch", "LIN1"पूर्ण,
	अणु"LIN12 PGA", "LIN2 Switch", "LIN2"पूर्ण,
	/* LIN34 PGA */
	अणु"LIN34 PGA", "LIN3 Switch", "LIN3"पूर्ण,
	अणु"LIN34 PGA", "LIN4 Switch", "LIN4/RXN"पूर्ण,
	/* INMIXL */
	अणु"INMIXL", "Record Left Volume", "LOMIX"पूर्ण,
	अणु"INMIXL", "LIN2 Volume", "LIN2"पूर्ण,
	अणु"INMIXL", "LINPGA12 Switch", "LIN12 PGA"पूर्ण,
	अणु"INMIXL", "LINPGA34 Switch", "LIN34 PGA"पूर्ण,
	/* AINLMUX */
	अणु"AINLMUX", "INMIXL Mix", "INMIXL"पूर्ण,
	अणु"AINLMUX", "DIFFINL Mix", "LIN12 PGA"पूर्ण,
	अणु"AINLMUX", "DIFFINL Mix", "LIN34 PGA"पूर्ण,
	अणु"AINLMUX", "RXVOICE Mix", "LIN4/RXN"पूर्ण,
	अणु"AINLMUX", "RXVOICE Mix", "RIN4/RXP"पूर्ण,
	/* ADC */
	अणु"Left ADC", शून्य, "AINLMUX"पूर्ण,

	/* RIN12 PGA */
	अणु"RIN12 PGA", "RIN1 Switch", "RIN1"पूर्ण,
	अणु"RIN12 PGA", "RIN2 Switch", "RIN2"पूर्ण,
	/* RIN34 PGA */
	अणु"RIN34 PGA", "RIN3 Switch", "RIN3"पूर्ण,
	अणु"RIN34 PGA", "RIN4 Switch", "RIN4/RXP"पूर्ण,
	/* INMIXL */
	अणु"INMIXR", "Record Right Volume", "ROMIX"पूर्ण,
	अणु"INMIXR", "RIN2 Volume", "RIN2"पूर्ण,
	अणु"INMIXR", "RINPGA12 Switch", "RIN12 PGA"पूर्ण,
	अणु"INMIXR", "RINPGA34 Switch", "RIN34 PGA"पूर्ण,
	/* AINRMUX */
	अणु"AINRMUX", "INMIXR Mix", "INMIXR"पूर्ण,
	अणु"AINRMUX", "DIFFINR Mix", "RIN12 PGA"पूर्ण,
	अणु"AINRMUX", "DIFFINR Mix", "RIN34 PGA"पूर्ण,
	अणु"AINRMUX", "RXVOICE Mix", "LIN4/RXN"पूर्ण,
	अणु"AINRMUX", "RXVOICE Mix", "RIN4/RXP"पूर्ण,
	/* ADC */
	अणु"Right ADC", शून्य, "AINRMUX"पूर्ण,

	/* LOMIX */
	अणु"LOMIX", "LOMIX RIN3 Bypass Switch", "RIN3"पूर्ण,
	अणु"LOMIX", "LOMIX LIN3 Bypass Switch", "LIN3"पूर्ण,
	अणु"LOMIX", "LOMIX LIN12 PGA Bypass Switch", "LIN12 PGA"पूर्ण,
	अणु"LOMIX", "LOMIX RIN12 PGA Bypass Switch", "RIN12 PGA"पूर्ण,
	अणु"LOMIX", "LOMIX Right ADC Bypass Switch", "AINRMUX"पूर्ण,
	अणु"LOMIX", "LOMIX Left ADC Bypass Switch", "AINLMUX"पूर्ण,
	अणु"LOMIX", "LOMIX Left DAC Switch", "Left DAC"पूर्ण,

	/* ROMIX */
	अणु"ROMIX", "ROMIX RIN3 Bypass Switch", "RIN3"पूर्ण,
	अणु"ROMIX", "ROMIX LIN3 Bypass Switch", "LIN3"पूर्ण,
	अणु"ROMIX", "ROMIX LIN12 PGA Bypass Switch", "LIN12 PGA"पूर्ण,
	अणु"ROMIX", "ROMIX RIN12 PGA Bypass Switch", "RIN12 PGA"पूर्ण,
	अणु"ROMIX", "ROMIX Right ADC Bypass Switch", "AINRMUX"पूर्ण,
	अणु"ROMIX", "ROMIX Left ADC Bypass Switch", "AINLMUX"पूर्ण,
	अणु"ROMIX", "ROMIX Right DAC Switch", "Right DAC"पूर्ण,

	/* SPKMIX */
	अणु"SPKMIX", "SPKMIX LIN2 Bypass Switch", "LIN2"पूर्ण,
	अणु"SPKMIX", "SPKMIX RIN2 Bypass Switch", "RIN2"पूर्ण,
	अणु"SPKMIX", "SPKMIX LADC Bypass Switch", "AINLMUX"पूर्ण,
	अणु"SPKMIX", "SPKMIX RADC Bypass Switch", "AINRMUX"पूर्ण,
	अणु"SPKMIX", "SPKMIX Left Mixer PGA Switch", "LOPGA"पूर्ण,
	अणु"SPKMIX", "SPKMIX Right Mixer PGA Switch", "ROPGA"पूर्ण,
	अणु"SPKMIX", "SPKMIX Right DAC Switch", "Right DAC"पूर्ण,
	अणु"SPKMIX", "SPKMIX Left DAC Switch", "Left DAC"पूर्ण,

	/* LONMIX */
	अणु"LONMIX", "LONMIX Left Mixer PGA Switch", "LOPGA"पूर्ण,
	अणु"LONMIX", "LONMIX Right Mixer PGA Switch", "ROPGA"पूर्ण,
	अणु"LONMIX", "LONMIX Inverted LOP Switch", "LOPMIX"पूर्ण,

	/* LOPMIX */
	अणु"LOPMIX", "LOPMIX Right Mic Bypass Switch", "RIN12 PGA"पूर्ण,
	अणु"LOPMIX", "LOPMIX Left Mic Bypass Switch", "LIN12 PGA"पूर्ण,
	अणु"LOPMIX", "LOPMIX Left Mixer PGA Switch", "LOPGA"पूर्ण,

	/* OUT3MIX */
	अणु"OUT3MIX", "OUT3MIX LIN4/RXP Bypass Switch", "LIN4/RXN"पूर्ण,
	अणु"OUT3MIX", "OUT3MIX Left Out PGA Switch", "LOPGA"पूर्ण,

	/* OUT4MIX */
	अणु"OUT4MIX", "OUT4MIX Right Out PGA Switch", "ROPGA"पूर्ण,
	अणु"OUT4MIX", "OUT4MIX RIN4/RXP Bypass Switch", "RIN4/RXP"पूर्ण,

	/* RONMIX */
	अणु"RONMIX", "RONMIX Right Mixer PGA Switch", "ROPGA"पूर्ण,
	अणु"RONMIX", "RONMIX Left Mixer PGA Switch", "LOPGA"पूर्ण,
	अणु"RONMIX", "RONMIX Inverted ROP Switch", "ROPMIX"पूर्ण,

	/* ROPMIX */
	अणु"ROPMIX", "ROPMIX Left Mic Bypass Switch", "LIN12 PGA"पूर्ण,
	अणु"ROPMIX", "ROPMIX Right Mic Bypass Switch", "RIN12 PGA"पूर्ण,
	अणु"ROPMIX", "ROPMIX Right Mixer PGA Switch", "ROPGA"पूर्ण,

	/* Out Mixer PGAs */
	अणु"LOPGA", शून्य, "LOMIX"पूर्ण,
	अणु"ROPGA", शून्य, "ROMIX"पूर्ण,

	अणु"LOUT PGA", शून्य, "LOMIX"पूर्ण,
	अणु"ROUT PGA", शून्य, "ROMIX"पूर्ण,

	/* Output Pins */
	अणु"LON", शून्य, "LONMIX"पूर्ण,
	अणु"LOP", शून्य, "LOPMIX"पूर्ण,
	अणु"OUT3", शून्य, "OUT3MIX"पूर्ण,
	अणु"LOUT", शून्य, "LOUT PGA"पूर्ण,
	अणु"SPKN", शून्य, "SPKMIX"पूर्ण,
	अणु"ROUT", शून्य, "ROUT PGA"पूर्ण,
	अणु"OUT4", शून्य, "OUT4MIX"पूर्ण,
	अणु"ROP", शून्य, "ROPMIX"पूर्ण,
	अणु"RON", शून्य, "RONMIX"पूर्ण,
पूर्ण;

/* PLL भागisors */
काष्ठा _pll_भाग अणु
	u32 भाग2;
	u32 n;
	u32 k;
पूर्ण;

/* The size in bits of the pll भागide multiplied by 10
 * to allow rounding later */
#घोषणा FIXED_PLL_SIZE ((1 << 16) * 10)

अटल व्योम pll_factors(काष्ठा _pll_भाग *pll_भाग, अचिन्हित पूर्णांक target,
	अचिन्हित पूर्णांक source)
अणु
	u64 Kpart;
	अचिन्हित पूर्णांक K, Nभाग, Nmod;


	Nभाग = target / source;
	अगर (Nभाग < 6) अणु
		source >>= 1;
		pll_भाग->भाग2 = 1;
		Nभाग = target / source;
	पूर्ण अन्यथा
		pll_भाग->भाग2 = 0;

	अगर ((Nभाग < 6) || (Nभाग > 12))
		prपूर्णांकk(KERN_WARNING
		"WM8990 N value outwith recommended range! N = %u\n", Nभाग);

	pll_भाग->n = Nभाग;
	Nmod = target % source;
	Kpart = FIXED_PLL_SIZE * (दीर्घ दीर्घ)Nmod;

	करो_भाग(Kpart, source);

	K = Kpart & 0xFFFFFFFF;

	/* Check अगर we need to round */
	अगर ((K % 10) >= 5)
		K += 5;

	/* Move करोwn to proper range now rounding is करोne */
	K /= 10;

	pll_भाग->k = K;
पूर्ण

अटल पूर्णांक wm8990_set_dai_pll(काष्ठा snd_soc_dai *codec_dai, पूर्णांक pll_id,
		पूर्णांक source, अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा _pll_भाग pll_भाग;

	अगर (freq_in && freq_out) अणु
		pll_factors(&pll_भाग, freq_out * 4, freq_in);

		/* Turn on PLL */
		snd_soc_component_update_bits(component, WM8990_POWER_MANAGEMENT_2,
				    WM8990_PLL_ENA, WM8990_PLL_ENA);

		/* sysclk comes from PLL */
		snd_soc_component_update_bits(component, WM8990_CLOCKING_2,
				    WM8990_SYSCLK_SRC, WM8990_SYSCLK_SRC);

		/* set up N , fractional mode and pre-भागisor अगर necessary */
		snd_soc_component_ग_लिखो(component, WM8990_PLL1, pll_भाग.n | WM8990_SDM |
			(pll_भाग.भाग2?WM8990_PRESCALE:0));
		snd_soc_component_ग_लिखो(component, WM8990_PLL2, (u8)(pll_भाग.k>>8));
		snd_soc_component_ग_लिखो(component, WM8990_PLL3, (u8)(pll_भाग.k & 0xFF));
	पूर्ण अन्यथा अणु
		/* Turn off PLL */
		snd_soc_component_update_bits(component, WM8990_POWER_MANAGEMENT_2,
				    WM8990_PLL_ENA, 0);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Clock after PLL and भागiders
 */
अटल पूर्णांक wm8990_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा wm8990_priv *wm8990 = snd_soc_component_get_drvdata(component);

	wm8990->sysclk = freq;
	वापस 0;
पूर्ण

/*
 * Set's ADC and Voice DAC क्रमmat.
 */
अटल पूर्णांक wm8990_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 audio1, audio3;

	audio1 = snd_soc_component_पढ़ो(component, WM8990_AUDIO_INTERFACE_1);
	audio3 = snd_soc_component_पढ़ो(component, WM8990_AUDIO_INTERFACE_3);

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		audio3 &= ~WM8990_AIF_MSTR1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		audio3 |= WM8990_AIF_MSTR1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	audio1 &= ~WM8990_AIF_FMT_MASK;

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		audio1 |= WM8990_AIF_TMF_I2S;
		audio1 &= ~WM8990_AIF_LRCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		audio1 |= WM8990_AIF_TMF_RIGHTJ;
		audio1 &= ~WM8990_AIF_LRCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		audio1 |= WM8990_AIF_TMF_LEFTJ;
		audio1 &= ~WM8990_AIF_LRCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		audio1 |= WM8990_AIF_TMF_DSP;
		audio1 &= ~WM8990_AIF_LRCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		audio1 |= WM8990_AIF_TMF_DSP | WM8990_AIF_LRCLK_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8990_AUDIO_INTERFACE_1, audio1);
	snd_soc_component_ग_लिखो(component, WM8990_AUDIO_INTERFACE_3, audio3);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8990_set_dai_clkभाग(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक भाग_id, पूर्णांक भाग)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;

	चयन (भाग_id) अणु
	हाल WM8990_MCLK_DIV:
		snd_soc_component_update_bits(component, WM8990_CLOCKING_2,
				    WM8990_MCLK_DIV_MASK, भाग);
		अवरोध;
	हाल WM8990_DACCLK_DIV:
		snd_soc_component_update_bits(component, WM8990_CLOCKING_2,
				    WM8990_DAC_CLKDIV_MASK, भाग);
		अवरोध;
	हाल WM8990_ADCCLK_DIV:
		snd_soc_component_update_bits(component, WM8990_CLOCKING_2,
				    WM8990_ADC_CLKDIV_MASK, भाग);
		अवरोध;
	हाल WM8990_BCLK_DIV:
		snd_soc_component_update_bits(component, WM8990_CLOCKING_1,
				    WM8990_BCLK_DIV_MASK, भाग);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Set PCM DAI bit size and sample rate.
 */
अटल पूर्णांक wm8990_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 audio1 = snd_soc_component_पढ़ो(component, WM8990_AUDIO_INTERFACE_1);

	audio1 &= ~WM8990_AIF_WL_MASK;
	/* bit size */
	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		audio1 |= WM8990_AIF_WL_20BITS;
		अवरोध;
	हाल 24:
		audio1 |= WM8990_AIF_WL_24BITS;
		अवरोध;
	हाल 32:
		audio1 |= WM8990_AIF_WL_32BITS;
		अवरोध;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8990_AUDIO_INTERFACE_1, audio1);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8990_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 val;

	val  = snd_soc_component_पढ़ो(component, WM8990_DAC_CTRL) & ~WM8990_DAC_MUTE;

	अगर (mute)
		snd_soc_component_ग_लिखो(component, WM8990_DAC_CTRL, val | WM8990_DAC_MUTE);
	अन्यथा
		snd_soc_component_ग_लिखो(component, WM8990_DAC_CTRL, val);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8990_set_bias_level(काष्ठा snd_soc_component *component,
	क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8990_priv *wm8990 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		/* VMID=2*50k */
		snd_soc_component_update_bits(component, WM8990_POWER_MANAGEMENT_1,
				    WM8990_VMID_MODE_MASK, 0x2);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			ret = regcache_sync(wm8990->regmap);
			अगर (ret < 0) अणु
				dev_err(component->dev, "Failed to sync cache: %d\n", ret);
				वापस ret;
			पूर्ण

			/* Enable all output disअक्षरge bits */
			snd_soc_component_ग_लिखो(component, WM8990_ANTIPOP1, WM8990_DIS_LLINE |
				WM8990_DIS_RLINE | WM8990_DIS_OUT3 |
				WM8990_DIS_OUT4 | WM8990_DIS_LOUT |
				WM8990_DIS_ROUT);

			/* Enable POBCTRL, SOFT_ST, VMIDTOG and BUFDCOPEN */
			snd_soc_component_ग_लिखो(component, WM8990_ANTIPOP2, WM8990_SOFTST |
				     WM8990_BUFDCOPEN | WM8990_POBCTRL |
				     WM8990_VMIDTOG);

			/* Delay to allow output caps to disअक्षरge */
			msleep(300);

			/* Disable VMIDTOG */
			snd_soc_component_ग_लिखो(component, WM8990_ANTIPOP2, WM8990_SOFTST |
				     WM8990_BUFDCOPEN | WM8990_POBCTRL);

			/* disable all output disअक्षरge bits */
			snd_soc_component_ग_लिखो(component, WM8990_ANTIPOP1, 0);

			/* Enable outमाला_दो */
			snd_soc_component_ग_लिखो(component, WM8990_POWER_MANAGEMENT_1, 0x1b00);

			msleep(50);

			/* Enable VMID at 2x50k */
			snd_soc_component_ग_लिखो(component, WM8990_POWER_MANAGEMENT_1, 0x1f02);

			msleep(100);

			/* Enable VREF */
			snd_soc_component_ग_लिखो(component, WM8990_POWER_MANAGEMENT_1, 0x1f03);

			msleep(600);

			/* Enable BUFIOEN */
			snd_soc_component_ग_लिखो(component, WM8990_ANTIPOP2, WM8990_SOFTST |
				     WM8990_BUFDCOPEN | WM8990_POBCTRL |
				     WM8990_BUFIOEN);

			/* Disable outमाला_दो */
			snd_soc_component_ग_लिखो(component, WM8990_POWER_MANAGEMENT_1, 0x3);

			/* disable POBCTRL, SOFT_ST and BUFDCOPEN */
			snd_soc_component_ग_लिखो(component, WM8990_ANTIPOP2, WM8990_BUFIOEN);

			/* Enable workaround क्रम ADC घड़ीing issue. */
			snd_soc_component_ग_लिखो(component, WM8990_EXT_ACCESS_ENA, 0x2);
			snd_soc_component_ग_लिखो(component, WM8990_EXT_CTL1, 0xa003);
			snd_soc_component_ग_लिखो(component, WM8990_EXT_ACCESS_ENA, 0);
		पूर्ण

		/* VMID=2*250k */
		snd_soc_component_update_bits(component, WM8990_POWER_MANAGEMENT_1,
				    WM8990_VMID_MODE_MASK, 0x4);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		/* Enable POBCTRL and SOFT_ST */
		snd_soc_component_ग_लिखो(component, WM8990_ANTIPOP2, WM8990_SOFTST |
			WM8990_POBCTRL | WM8990_BUFIOEN);

		/* Enable POBCTRL, SOFT_ST and BUFDCOPEN */
		snd_soc_component_ग_लिखो(component, WM8990_ANTIPOP2, WM8990_SOFTST |
			WM8990_BUFDCOPEN | WM8990_POBCTRL |
			WM8990_BUFIOEN);

		/* mute DAC */
		snd_soc_component_update_bits(component, WM8990_DAC_CTRL,
				    WM8990_DAC_MUTE, WM8990_DAC_MUTE);

		/* Enable any disabled outमाला_दो */
		snd_soc_component_ग_लिखो(component, WM8990_POWER_MANAGEMENT_1, 0x1f03);

		/* Disable VMID */
		snd_soc_component_ग_लिखो(component, WM8990_POWER_MANAGEMENT_1, 0x1f01);

		msleep(300);

		/* Enable all output disअक्षरge bits */
		snd_soc_component_ग_लिखो(component, WM8990_ANTIPOP1, WM8990_DIS_LLINE |
			WM8990_DIS_RLINE | WM8990_DIS_OUT3 |
			WM8990_DIS_OUT4 | WM8990_DIS_LOUT |
			WM8990_DIS_ROUT);

		/* Disable VREF */
		snd_soc_component_ग_लिखो(component, WM8990_POWER_MANAGEMENT_1, 0x0);

		/* disable POBCTRL, SOFT_ST and BUFDCOPEN */
		snd_soc_component_ग_लिखो(component, WM8990_ANTIPOP2, 0x0);

		regcache_mark_dirty(wm8990->regmap);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा WM8990_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_11025 |\
	SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_22050 | SNDRV_PCM_RATE_44100 | \
	SNDRV_PCM_RATE_48000)

#घोषणा WM8990_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
	SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

/*
 * The WM8990 supports 2 dअगरferent and mutually exclusive DAI
 * configurations.
 *
 * 1. ADC/DAC on Primary Interface
 * 2. ADC on Primary Interface/DAC on secondary
 */
अटल स्थिर काष्ठा snd_soc_dai_ops wm8990_dai_ops = अणु
	.hw_params	= wm8990_hw_params,
	.mute_stream	= wm8990_mute,
	.set_fmt	= wm8990_set_dai_fmt,
	.set_clkभाग	= wm8990_set_dai_clkभाग,
	.set_pll	= wm8990_set_dai_pll,
	.set_sysclk	= wm8990_set_dai_sysclk,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8990_dai = अणु
/* ADC/DAC on primary */
	.name = "wm8990-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8990_RATES,
		.क्रमmats = WM8990_FORMATS,पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8990_RATES,
		.क्रमmats = WM8990_FORMATS,पूर्ण,
	.ops = &wm8990_dai_ops,
पूर्ण;

/*
 * initialise the WM8990 driver
 * रेजिस्टर the mixer and dsp पूर्णांकerfaces with the kernel
 */
अटल पूर्णांक wm8990_probe(काष्ठा snd_soc_component *component)
अणु
	wm8990_reset(component);

	/* अक्षरge output caps */
	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_STANDBY);

	snd_soc_component_update_bits(component, WM8990_AUDIO_INTERFACE_4,
			    WM8990_ALRCGPIO1, WM8990_ALRCGPIO1);

	snd_soc_component_update_bits(component, WM8990_GPIO1_GPIO2,
			    WM8990_GPIO1_SEL_MASK, 1);

	snd_soc_component_update_bits(component, WM8990_POWER_MANAGEMENT_2,
			    WM8990_OPCLK_ENA, WM8990_OPCLK_ENA);

	snd_soc_component_ग_लिखो(component, WM8990_LEFT_OUTPUT_VOLUME, 0x50 | (1<<8));
	snd_soc_component_ग_लिखो(component, WM8990_RIGHT_OUTPUT_VOLUME, 0x50 | (1<<8));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8990 = अणु
	.probe			= wm8990_probe,
	.set_bias_level		= wm8990_set_bias_level,
	.controls		= wm8990_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8990_snd_controls),
	.dapm_widमाला_लो		= wm8990_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8990_dapm_widमाला_लो),
	.dapm_routes		= wm8990_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm8990_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक wm8990_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8990_priv *wm8990;
	पूर्णांक ret;

	wm8990 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8990_priv),
			      GFP_KERNEL);
	अगर (wm8990 == शून्य)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, wm8990);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_wm8990, &wm8990_dai, 1);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8990_i2c_id[] = अणु
	अणु "wm8990", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8990_i2c_id);

अटल काष्ठा i2c_driver wm8990_i2c_driver = अणु
	.driver = अणु
		.name = "wm8990",
	पूर्ण,
	.probe =    wm8990_i2c_probe,
	.id_table = wm8990_i2c_id,
पूर्ण;

module_i2c_driver(wm8990_i2c_driver);

MODULE_DESCRIPTION("ASoC WM8990 driver");
MODULE_AUTHOR("Liam Girdwood");
MODULE_LICENSE("GPL");
