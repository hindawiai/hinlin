<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * wm8400.c  --  WM8400 ALSA Soc Audio driver
 *
 * Copyright 2008-11 Wolfson Microelectronics PLC.
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/mfd/wm8400-audपन.स>
#समावेश <linux/mfd/wm8400-निजी.h>
#समावेश <linux/mfd/core.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "wm8400.h"

अटल काष्ठा regulator_bulk_data घातer[] = अणु
	अणु
		.supply = "I2S1VDD",
	पूर्ण,
	अणु
		.supply = "I2S2VDD",
	पूर्ण,
	अणु
		.supply = "DCVDD",
	पूर्ण,
	अणु
		.supply = "AVDD",
	पूर्ण,
	अणु
		.supply = "FLLVDD",
	पूर्ण,
	अणु
		.supply = "HPVDD",
	पूर्ण,
	अणु
		.supply = "SPKVDD",
	पूर्ण,
पूर्ण;

/* codec निजी data */
काष्ठा wm8400_priv अणु
	काष्ठा wm8400 *wm8400;
	u16 fake_रेजिस्टर;
	अचिन्हित पूर्णांक sysclk;
	अचिन्हित पूर्णांक pcmclk;
	पूर्णांक fll_in, fll_out;
पूर्ण;

अटल व्योम wm8400_component_reset(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8400_priv *wm8400 = snd_soc_component_get_drvdata(component);

	wm8400_reset_codec_reg_cache(wm8400->wm8400);
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(in_pga_tlv, -1650, 3000, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(out_mix_tlv, -2100, 0, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(out_pga_tlv, -7300, 600, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(out_dac_tlv, -7163, 0, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(in_adc_tlv, -7163, 1763, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(out_sidetone_tlv, -3600, 0, 0);

अटल पूर्णांक wm8400_outpga_put_volsw_vu(काष्ठा snd_kcontrol *kcontrol,
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

#घोषणा WM8400_OUTPGA_SINGLE_R_TLV(xname, reg, shअगरt, max, invert, tlv_array) \
	SOC_SINGLE_EXT_TLV(xname, reg, shअगरt, max, invert, \
		snd_soc_get_volsw, wm8400_outpga_put_volsw_vu, tlv_array)


अटल स्थिर अक्षर *wm8400_digital_sidetone[] =
	अणु"None", "Left ADC", "Right ADC", "Reserved"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(wm8400_left_digital_sidetone_क्रमागत,
			    WM8400_DIGITAL_SIDE_TONE,
			    WM8400_ADC_TO_DACL_SHIFT,
			    wm8400_digital_sidetone);

अटल SOC_ENUM_SINGLE_DECL(wm8400_right_digital_sidetone_क्रमागत,
			    WM8400_DIGITAL_SIDE_TONE,
			    WM8400_ADC_TO_DACR_SHIFT,
			    wm8400_digital_sidetone);

अटल स्थिर अक्षर *wm8400_adcmode[] =
	अणु"Hi-fi mode", "Voice mode 1", "Voice mode 2", "Voice mode 3"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(wm8400_right_adcmode_क्रमागत,
			    WM8400_ADC_CTRL,
			    WM8400_ADC_HPF_CUT_SHIFT,
			    wm8400_adcmode);

अटल स्थिर काष्ठा snd_kcontrol_new wm8400_snd_controls[] = अणु
/* INMIXL */
SOC_SINGLE("LIN12 PGA Boost", WM8400_INPUT_MIXER3, WM8400_L12MNBST_SHIFT,
	   1, 0),
SOC_SINGLE("LIN34 PGA Boost", WM8400_INPUT_MIXER3, WM8400_L34MNBST_SHIFT,
	   1, 0),
/* INMIXR */
SOC_SINGLE("RIN12 PGA Boost", WM8400_INPUT_MIXER3, WM8400_R12MNBST_SHIFT,
	   1, 0),
SOC_SINGLE("RIN34 PGA Boost", WM8400_INPUT_MIXER3, WM8400_R34MNBST_SHIFT,
	   1, 0),

/* LOMIX */
SOC_SINGLE_TLV("LOMIX LIN3 Bypass Volume", WM8400_OUTPUT_MIXER3,
	WM8400_LLI3LOVOL_SHIFT, 7, 0, out_mix_tlv),
SOC_SINGLE_TLV("LOMIX RIN12 PGA Bypass Volume", WM8400_OUTPUT_MIXER3,
	WM8400_LR12LOVOL_SHIFT, 7, 0, out_mix_tlv),
SOC_SINGLE_TLV("LOMIX LIN12 PGA Bypass Volume", WM8400_OUTPUT_MIXER3,
	WM8400_LL12LOVOL_SHIFT, 7, 0, out_mix_tlv),
SOC_SINGLE_TLV("LOMIX RIN3 Bypass Volume", WM8400_OUTPUT_MIXER5,
	WM8400_LRI3LOVOL_SHIFT, 7, 0, out_mix_tlv),
SOC_SINGLE_TLV("LOMIX AINRMUX Bypass Volume", WM8400_OUTPUT_MIXER5,
	WM8400_LRBLOVOL_SHIFT, 7, 0, out_mix_tlv),
SOC_SINGLE_TLV("LOMIX AINLMUX Bypass Volume", WM8400_OUTPUT_MIXER5,
	WM8400_LRBLOVOL_SHIFT, 7, 0, out_mix_tlv),

/* ROMIX */
SOC_SINGLE_TLV("ROMIX RIN3 Bypass Volume", WM8400_OUTPUT_MIXER4,
	WM8400_RRI3ROVOL_SHIFT, 7, 0, out_mix_tlv),
SOC_SINGLE_TLV("ROMIX LIN12 PGA Bypass Volume", WM8400_OUTPUT_MIXER4,
	WM8400_RL12ROVOL_SHIFT, 7, 0, out_mix_tlv),
SOC_SINGLE_TLV("ROMIX RIN12 PGA Bypass Volume", WM8400_OUTPUT_MIXER4,
	WM8400_RR12ROVOL_SHIFT, 7, 0, out_mix_tlv),
SOC_SINGLE_TLV("ROMIX LIN3 Bypass Volume", WM8400_OUTPUT_MIXER6,
	WM8400_RLI3ROVOL_SHIFT, 7, 0, out_mix_tlv),
SOC_SINGLE_TLV("ROMIX AINLMUX Bypass Volume", WM8400_OUTPUT_MIXER6,
	WM8400_RLBROVOL_SHIFT, 7, 0, out_mix_tlv),
SOC_SINGLE_TLV("ROMIX AINRMUX Bypass Volume", WM8400_OUTPUT_MIXER6,
	WM8400_RRBROVOL_SHIFT, 7, 0, out_mix_tlv),

/* LOUT */
WM8400_OUTPGA_SINGLE_R_TLV("LOUT Volume", WM8400_LEFT_OUTPUT_VOLUME,
	WM8400_LOUTVOL_SHIFT, WM8400_LOUTVOL_MASK, 0, out_pga_tlv),
SOC_SINGLE("LOUT ZC", WM8400_LEFT_OUTPUT_VOLUME, WM8400_LOZC_SHIFT, 1, 0),

/* ROUT */
WM8400_OUTPGA_SINGLE_R_TLV("ROUT Volume", WM8400_RIGHT_OUTPUT_VOLUME,
	WM8400_ROUTVOL_SHIFT, WM8400_ROUTVOL_MASK, 0, out_pga_tlv),
SOC_SINGLE("ROUT ZC", WM8400_RIGHT_OUTPUT_VOLUME, WM8400_ROZC_SHIFT, 1, 0),

/* LOPGA */
WM8400_OUTPGA_SINGLE_R_TLV("LOPGA Volume", WM8400_LEFT_OPGA_VOLUME,
	WM8400_LOPGAVOL_SHIFT, WM8400_LOPGAVOL_MASK, 0, out_pga_tlv),
SOC_SINGLE("LOPGA ZC Switch", WM8400_LEFT_OPGA_VOLUME,
	WM8400_LOPGAZC_SHIFT, 1, 0),

/* ROPGA */
WM8400_OUTPGA_SINGLE_R_TLV("ROPGA Volume", WM8400_RIGHT_OPGA_VOLUME,
	WM8400_ROPGAVOL_SHIFT, WM8400_ROPGAVOL_MASK, 0, out_pga_tlv),
SOC_SINGLE("ROPGA ZC Switch", WM8400_RIGHT_OPGA_VOLUME,
	WM8400_ROPGAZC_SHIFT, 1, 0),

SOC_SINGLE("LON Mute Switch", WM8400_LINE_OUTPUTS_VOLUME,
	WM8400_LONMUTE_SHIFT, 1, 0),
SOC_SINGLE("LOP Mute Switch", WM8400_LINE_OUTPUTS_VOLUME,
	WM8400_LOPMUTE_SHIFT, 1, 0),
SOC_SINGLE("LOP Attenuation Switch", WM8400_LINE_OUTPUTS_VOLUME,
	WM8400_LOATTN_SHIFT, 1, 0),
SOC_SINGLE("RON Mute Switch", WM8400_LINE_OUTPUTS_VOLUME,
	WM8400_RONMUTE_SHIFT, 1, 0),
SOC_SINGLE("ROP Mute Switch", WM8400_LINE_OUTPUTS_VOLUME,
	WM8400_ROPMUTE_SHIFT, 1, 0),
SOC_SINGLE("ROP Attenuation Switch", WM8400_LINE_OUTPUTS_VOLUME,
	WM8400_ROATTN_SHIFT, 1, 0),

SOC_SINGLE("OUT3 Mute Switch", WM8400_OUT3_4_VOLUME,
	WM8400_OUT3MUTE_SHIFT, 1, 0),
SOC_SINGLE("OUT3 Attenuation Switch", WM8400_OUT3_4_VOLUME,
	WM8400_OUT3ATTN_SHIFT, 1, 0),

SOC_SINGLE("OUT4 Mute Switch", WM8400_OUT3_4_VOLUME,
	WM8400_OUT4MUTE_SHIFT, 1, 0),
SOC_SINGLE("OUT4 Attenuation Switch", WM8400_OUT3_4_VOLUME,
	WM8400_OUT4ATTN_SHIFT, 1, 0),

SOC_SINGLE("Speaker Mode Switch", WM8400_CLASSD1,
	WM8400_CDMODE_SHIFT, 1, 0),

SOC_SINGLE("Speaker Output Attenuation Volume", WM8400_SPEAKER_VOLUME,
	WM8400_SPKATTN_SHIFT, WM8400_SPKATTN_MASK, 0),
SOC_SINGLE("Speaker DC Boost Volume", WM8400_CLASSD3,
	WM8400_DCGAIN_SHIFT, 6, 0),
SOC_SINGLE("Speaker AC Boost Volume", WM8400_CLASSD3,
	WM8400_ACGAIN_SHIFT, 6, 0),

WM8400_OUTPGA_SINGLE_R_TLV("Left DAC Digital Volume",
	WM8400_LEFT_DAC_DIGITAL_VOLUME, WM8400_DACL_VOL_SHIFT,
	127, 0, out_dac_tlv),

WM8400_OUTPGA_SINGLE_R_TLV("Right DAC Digital Volume",
	WM8400_RIGHT_DAC_DIGITAL_VOLUME, WM8400_DACR_VOL_SHIFT,
	127, 0, out_dac_tlv),

SOC_ENUM("Left Digital Sidetone", wm8400_left_digital_sidetone_क्रमागत),
SOC_ENUM("Right Digital Sidetone", wm8400_right_digital_sidetone_क्रमागत),

SOC_SINGLE_TLV("Left Digital Sidetone Volume", WM8400_DIGITAL_SIDE_TONE,
	WM8400_ADCL_DAC_SVOL_SHIFT, 15, 0, out_sidetone_tlv),
SOC_SINGLE_TLV("Right Digital Sidetone Volume", WM8400_DIGITAL_SIDE_TONE,
	WM8400_ADCR_DAC_SVOL_SHIFT, 15, 0, out_sidetone_tlv),

SOC_SINGLE("ADC Digital High Pass Filter Switch", WM8400_ADC_CTRL,
	WM8400_ADC_HPF_ENA_SHIFT, 1, 0),

SOC_ENUM("ADC HPF Mode", wm8400_right_adcmode_क्रमागत),

WM8400_OUTPGA_SINGLE_R_TLV("Left ADC Digital Volume",
	WM8400_LEFT_ADC_DIGITAL_VOLUME,
	WM8400_ADCL_VOL_SHIFT,
	WM8400_ADCL_VOL_MASK,
	0,
	in_adc_tlv),

WM8400_OUTPGA_SINGLE_R_TLV("Right ADC Digital Volume",
	WM8400_RIGHT_ADC_DIGITAL_VOLUME,
	WM8400_ADCR_VOL_SHIFT,
	WM8400_ADCR_VOL_MASK,
	0,
	in_adc_tlv),

WM8400_OUTPGA_SINGLE_R_TLV("LIN12 Volume",
	WM8400_LEFT_LINE_INPUT_1_2_VOLUME,
	WM8400_LIN12VOL_SHIFT,
	WM8400_LIN12VOL_MASK,
	0,
	in_pga_tlv),

SOC_SINGLE("LIN12 ZC Switch", WM8400_LEFT_LINE_INPUT_1_2_VOLUME,
	WM8400_LI12ZC_SHIFT, 1, 0),

SOC_SINGLE("LIN12 Mute Switch", WM8400_LEFT_LINE_INPUT_1_2_VOLUME,
	WM8400_LI12MUTE_SHIFT, 1, 0),

WM8400_OUTPGA_SINGLE_R_TLV("LIN34 Volume",
	WM8400_LEFT_LINE_INPUT_3_4_VOLUME,
	WM8400_LIN34VOL_SHIFT,
	WM8400_LIN34VOL_MASK,
	0,
	in_pga_tlv),

SOC_SINGLE("LIN34 ZC Switch", WM8400_LEFT_LINE_INPUT_3_4_VOLUME,
	WM8400_LI34ZC_SHIFT, 1, 0),

SOC_SINGLE("LIN34 Mute Switch", WM8400_LEFT_LINE_INPUT_3_4_VOLUME,
	WM8400_LI34MUTE_SHIFT, 1, 0),

WM8400_OUTPGA_SINGLE_R_TLV("RIN12 Volume",
	WM8400_RIGHT_LINE_INPUT_1_2_VOLUME,
	WM8400_RIN12VOL_SHIFT,
	WM8400_RIN12VOL_MASK,
	0,
	in_pga_tlv),

SOC_SINGLE("RIN12 ZC Switch", WM8400_RIGHT_LINE_INPUT_1_2_VOLUME,
	WM8400_RI12ZC_SHIFT, 1, 0),

SOC_SINGLE("RIN12 Mute Switch", WM8400_RIGHT_LINE_INPUT_1_2_VOLUME,
	WM8400_RI12MUTE_SHIFT, 1, 0),

WM8400_OUTPGA_SINGLE_R_TLV("RIN34 Volume",
	WM8400_RIGHT_LINE_INPUT_3_4_VOLUME,
	WM8400_RIN34VOL_SHIFT,
	WM8400_RIN34VOL_MASK,
	0,
	in_pga_tlv),

SOC_SINGLE("RIN34 ZC Switch", WM8400_RIGHT_LINE_INPUT_3_4_VOLUME,
	WM8400_RI34ZC_SHIFT, 1, 0),

SOC_SINGLE("RIN34 Mute Switch", WM8400_RIGHT_LINE_INPUT_3_4_VOLUME,
	WM8400_RI34MUTE_SHIFT, 1, 0),

पूर्ण;

/*
 * _DAPM_ Controls
 */

अटल पूर्णांक ouपंचांगixer_event (काष्ठा snd_soc_dapm_widget *w,
	काष्ठा snd_kcontrol * kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा soc_mixer_control *mc =
		(काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	u32 reg_shअगरt = mc->shअगरt;
	पूर्णांक ret = 0;
	u16 reg;

	चयन (reg_shअगरt) अणु
	हाल WM8400_SPEAKER_MIXER | (WM8400_LDSPK << 8) :
		reg = snd_soc_component_पढ़ो(component, WM8400_OUTPUT_MIXER1);
		अगर (reg & WM8400_LDLO) अणु
			prपूर्णांकk(KERN_WARNING
			"Cannot set as Output Mixer 1 LDLO Set\n");
			ret = -1;
		पूर्ण
		अवरोध;
	हाल WM8400_SPEAKER_MIXER | (WM8400_RDSPK << 8):
		reg = snd_soc_component_पढ़ो(component, WM8400_OUTPUT_MIXER2);
		अगर (reg & WM8400_RDRO) अणु
			prपूर्णांकk(KERN_WARNING
			"Cannot set as Output Mixer 2 RDRO Set\n");
			ret = -1;
		पूर्ण
		अवरोध;
	हाल WM8400_OUTPUT_MIXER1 | (WM8400_LDLO << 8):
		reg = snd_soc_component_पढ़ो(component, WM8400_SPEAKER_MIXER);
		अगर (reg & WM8400_LDSPK) अणु
			prपूर्णांकk(KERN_WARNING
			"Cannot set as Speaker Mixer LDSPK Set\n");
			ret = -1;
		पूर्ण
		अवरोध;
	हाल WM8400_OUTPUT_MIXER2 | (WM8400_RDRO << 8):
		reg = snd_soc_component_पढ़ो(component, WM8400_SPEAKER_MIXER);
		अगर (reg & WM8400_RDSPK) अणु
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
अटल स्थिर काष्ठा snd_kcontrol_new wm8400_dapm_lin12_pga_controls[] = अणु
SOC_DAPM_SINGLE("LIN1 Switch", WM8400_INPUT_MIXER2, WM8400_LMN1_SHIFT, 1, 0),
SOC_DAPM_SINGLE("LIN2 Switch", WM8400_INPUT_MIXER2, WM8400_LMP2_SHIFT, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8400_dapm_lin34_pga_controls[] = अणु
SOC_DAPM_SINGLE("LIN3 Switch", WM8400_INPUT_MIXER2, WM8400_LMN3_SHIFT, 1, 0),
SOC_DAPM_SINGLE("LIN4 Switch", WM8400_INPUT_MIXER2, WM8400_LMP4_SHIFT, 1, 0),
पूर्ण;

/* Right In PGA Connections */
अटल स्थिर काष्ठा snd_kcontrol_new wm8400_dapm_rin12_pga_controls[] = अणु
SOC_DAPM_SINGLE("RIN1 Switch", WM8400_INPUT_MIXER2, WM8400_RMN1_SHIFT, 1, 0),
SOC_DAPM_SINGLE("RIN2 Switch", WM8400_INPUT_MIXER2, WM8400_RMP2_SHIFT, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8400_dapm_rin34_pga_controls[] = अणु
SOC_DAPM_SINGLE("RIN3 Switch", WM8400_INPUT_MIXER2, WM8400_RMN3_SHIFT, 1, 0),
SOC_DAPM_SINGLE("RIN4 Switch", WM8400_INPUT_MIXER2, WM8400_RMP4_SHIFT, 1, 0),
पूर्ण;

/* INMIXL */
अटल स्थिर काष्ठा snd_kcontrol_new wm8400_dapm_inmixl_controls[] = अणु
SOC_DAPM_SINGLE_TLV("Record Left Volume", WM8400_INPUT_MIXER3,
	WM8400_LDBVOL_SHIFT, WM8400_LDBVOL_MASK, 0, in_mix_tlv),
SOC_DAPM_SINGLE_TLV("LIN2 Volume", WM8400_INPUT_MIXER5, WM8400_LI2BVOL_SHIFT,
	7, 0, in_mix_tlv),
SOC_DAPM_SINGLE("LINPGA12 Switch", WM8400_INPUT_MIXER3, WM8400_L12MNB_SHIFT,
		1, 0),
SOC_DAPM_SINGLE("LINPGA34 Switch", WM8400_INPUT_MIXER3, WM8400_L34MNB_SHIFT,
		1, 0),
पूर्ण;

/* INMIXR */
अटल स्थिर काष्ठा snd_kcontrol_new wm8400_dapm_inmixr_controls[] = अणु
SOC_DAPM_SINGLE_TLV("Record Right Volume", WM8400_INPUT_MIXER4,
	WM8400_RDBVOL_SHIFT, WM8400_RDBVOL_MASK, 0, in_mix_tlv),
SOC_DAPM_SINGLE_TLV("RIN2 Volume", WM8400_INPUT_MIXER6, WM8400_RI2BVOL_SHIFT,
	7, 0, in_mix_tlv),
SOC_DAPM_SINGLE("RINPGA12 Switch", WM8400_INPUT_MIXER3, WM8400_L12MNB_SHIFT,
	1, 0),
SOC_DAPM_SINGLE("RINPGA34 Switch", WM8400_INPUT_MIXER3, WM8400_L34MNB_SHIFT,
	1, 0),
पूर्ण;

/* AINLMUX */
अटल स्थिर अक्षर *wm8400_ainlmux[] =
	अणु"INMIXL Mix", "RXVOICE Mix", "DIFFINL Mix"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(wm8400_ainlmux_क्रमागत,
			    WM8400_INPUT_MIXER1,
			    WM8400_AINLMODE_SHIFT,
			    wm8400_ainlmux);

अटल स्थिर काष्ठा snd_kcontrol_new wm8400_dapm_ainlmux_controls =
SOC_DAPM_ENUM("Route", wm8400_ainlmux_क्रमागत);

/* DIFFINL */

/* AINRMUX */
अटल स्थिर अक्षर *wm8400_ainrmux[] =
	अणु"INMIXR Mix", "RXVOICE Mix", "DIFFINR Mix"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(wm8400_ainrmux_क्रमागत,
			    WM8400_INPUT_MIXER1,
			    WM8400_AINRMODE_SHIFT,
			    wm8400_ainrmux);

अटल स्थिर काष्ठा snd_kcontrol_new wm8400_dapm_ainrmux_controls =
SOC_DAPM_ENUM("Route", wm8400_ainrmux_क्रमागत);

/* LOMIX */
अटल स्थिर काष्ठा snd_kcontrol_new wm8400_dapm_lomix_controls[] = अणु
SOC_DAPM_SINGLE("LOMIX Right ADC Bypass Switch", WM8400_OUTPUT_MIXER1,
	WM8400_LRBLO_SHIFT, 1, 0),
SOC_DAPM_SINGLE("LOMIX Left ADC Bypass Switch", WM8400_OUTPUT_MIXER1,
	WM8400_LLBLO_SHIFT, 1, 0),
SOC_DAPM_SINGLE("LOMIX RIN3 Bypass Switch", WM8400_OUTPUT_MIXER1,
	WM8400_LRI3LO_SHIFT, 1, 0),
SOC_DAPM_SINGLE("LOMIX LIN3 Bypass Switch", WM8400_OUTPUT_MIXER1,
	WM8400_LLI3LO_SHIFT, 1, 0),
SOC_DAPM_SINGLE("LOMIX RIN12 PGA Bypass Switch", WM8400_OUTPUT_MIXER1,
	WM8400_LR12LO_SHIFT, 1, 0),
SOC_DAPM_SINGLE("LOMIX LIN12 PGA Bypass Switch", WM8400_OUTPUT_MIXER1,
	WM8400_LL12LO_SHIFT, 1, 0),
SOC_DAPM_SINGLE("LOMIX Left DAC Switch", WM8400_OUTPUT_MIXER1,
	WM8400_LDLO_SHIFT, 1, 0),
पूर्ण;

/* ROMIX */
अटल स्थिर काष्ठा snd_kcontrol_new wm8400_dapm_romix_controls[] = अणु
SOC_DAPM_SINGLE("ROMIX Left ADC Bypass Switch", WM8400_OUTPUT_MIXER2,
	WM8400_RLBRO_SHIFT, 1, 0),
SOC_DAPM_SINGLE("ROMIX Right ADC Bypass Switch", WM8400_OUTPUT_MIXER2,
	WM8400_RRBRO_SHIFT, 1, 0),
SOC_DAPM_SINGLE("ROMIX LIN3 Bypass Switch", WM8400_OUTPUT_MIXER2,
	WM8400_RLI3RO_SHIFT, 1, 0),
SOC_DAPM_SINGLE("ROMIX RIN3 Bypass Switch", WM8400_OUTPUT_MIXER2,
	WM8400_RRI3RO_SHIFT, 1, 0),
SOC_DAPM_SINGLE("ROMIX LIN12 PGA Bypass Switch", WM8400_OUTPUT_MIXER2,
	WM8400_RL12RO_SHIFT, 1, 0),
SOC_DAPM_SINGLE("ROMIX RIN12 PGA Bypass Switch", WM8400_OUTPUT_MIXER2,
	WM8400_RR12RO_SHIFT, 1, 0),
SOC_DAPM_SINGLE("ROMIX Right DAC Switch", WM8400_OUTPUT_MIXER2,
	WM8400_RDRO_SHIFT, 1, 0),
पूर्ण;

/* LONMIX */
अटल स्थिर काष्ठा snd_kcontrol_new wm8400_dapm_lonmix_controls[] = अणु
SOC_DAPM_SINGLE("LONMIX Left Mixer PGA Switch", WM8400_LINE_MIXER1,
	WM8400_LLOPGALON_SHIFT, 1, 0),
SOC_DAPM_SINGLE("LONMIX Right Mixer PGA Switch", WM8400_LINE_MIXER1,
	WM8400_LROPGALON_SHIFT, 1, 0),
SOC_DAPM_SINGLE("LONMIX Inverted LOP Switch", WM8400_LINE_MIXER1,
	WM8400_LOPLON_SHIFT, 1, 0),
पूर्ण;

/* LOPMIX */
अटल स्थिर काष्ठा snd_kcontrol_new wm8400_dapm_lopmix_controls[] = अणु
SOC_DAPM_SINGLE("LOPMIX Right Mic Bypass Switch", WM8400_LINE_MIXER1,
	WM8400_LR12LOP_SHIFT, 1, 0),
SOC_DAPM_SINGLE("LOPMIX Left Mic Bypass Switch", WM8400_LINE_MIXER1,
	WM8400_LL12LOP_SHIFT, 1, 0),
SOC_DAPM_SINGLE("LOPMIX Left Mixer PGA Switch", WM8400_LINE_MIXER1,
	WM8400_LLOPGALOP_SHIFT, 1, 0),
पूर्ण;

/* RONMIX */
अटल स्थिर काष्ठा snd_kcontrol_new wm8400_dapm_ronmix_controls[] = अणु
SOC_DAPM_SINGLE("RONMIX Right Mixer PGA Switch", WM8400_LINE_MIXER2,
	WM8400_RROPGARON_SHIFT, 1, 0),
SOC_DAPM_SINGLE("RONMIX Left Mixer PGA Switch", WM8400_LINE_MIXER2,
	WM8400_RLOPGARON_SHIFT, 1, 0),
SOC_DAPM_SINGLE("RONMIX Inverted ROP Switch", WM8400_LINE_MIXER2,
	WM8400_ROPRON_SHIFT, 1, 0),
पूर्ण;

/* ROPMIX */
अटल स्थिर काष्ठा snd_kcontrol_new wm8400_dapm_ropmix_controls[] = अणु
SOC_DAPM_SINGLE("ROPMIX Left Mic Bypass Switch", WM8400_LINE_MIXER2,
	WM8400_RL12ROP_SHIFT, 1, 0),
SOC_DAPM_SINGLE("ROPMIX Right Mic Bypass Switch", WM8400_LINE_MIXER2,
	WM8400_RR12ROP_SHIFT, 1, 0),
SOC_DAPM_SINGLE("ROPMIX Right Mixer PGA Switch", WM8400_LINE_MIXER2,
	WM8400_RROPGAROP_SHIFT, 1, 0),
पूर्ण;

/* OUT3MIX */
अटल स्थिर काष्ठा snd_kcontrol_new wm8400_dapm_out3mix_controls[] = अणु
SOC_DAPM_SINGLE("OUT3MIX LIN4/RXP Bypass Switch", WM8400_OUT3_4_MIXER,
	WM8400_LI4O3_SHIFT, 1, 0),
SOC_DAPM_SINGLE("OUT3MIX Left Out PGA Switch", WM8400_OUT3_4_MIXER,
	WM8400_LPGAO3_SHIFT, 1, 0),
पूर्ण;

/* OUT4MIX */
अटल स्थिर काष्ठा snd_kcontrol_new wm8400_dapm_out4mix_controls[] = अणु
SOC_DAPM_SINGLE("OUT4MIX Right Out PGA Switch", WM8400_OUT3_4_MIXER,
	WM8400_RPGAO4_SHIFT, 1, 0),
SOC_DAPM_SINGLE("OUT4MIX RIN4/RXP Bypass Switch", WM8400_OUT3_4_MIXER,
	WM8400_RI4O4_SHIFT, 1, 0),
पूर्ण;

/* SPKMIX */
अटल स्थिर काष्ठा snd_kcontrol_new wm8400_dapm_spkmix_controls[] = अणु
SOC_DAPM_SINGLE("SPKMIX LIN2 Bypass Switch", WM8400_SPEAKER_MIXER,
	WM8400_LI2SPK_SHIFT, 1, 0),
SOC_DAPM_SINGLE("SPKMIX LADC Bypass Switch", WM8400_SPEAKER_MIXER,
	WM8400_LB2SPK_SHIFT, 1, 0),
SOC_DAPM_SINGLE("SPKMIX Left Mixer PGA Switch", WM8400_SPEAKER_MIXER,
	WM8400_LOPGASPK_SHIFT, 1, 0),
SOC_DAPM_SINGLE("SPKMIX Left DAC Switch", WM8400_SPEAKER_MIXER,
	WM8400_LDSPK_SHIFT, 1, 0),
SOC_DAPM_SINGLE("SPKMIX Right DAC Switch", WM8400_SPEAKER_MIXER,
	WM8400_RDSPK_SHIFT, 1, 0),
SOC_DAPM_SINGLE("SPKMIX Right Mixer PGA Switch", WM8400_SPEAKER_MIXER,
	WM8400_ROPGASPK_SHIFT, 1, 0),
SOC_DAPM_SINGLE("SPKMIX RADC Bypass Switch", WM8400_SPEAKER_MIXER,
	WM8400_RL12ROP_SHIFT, 1, 0),
SOC_DAPM_SINGLE("SPKMIX RIN2 Bypass Switch", WM8400_SPEAKER_MIXER,
	WM8400_RI2SPK_SHIFT, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8400_dapm_widमाला_लो[] = अणु
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

/* DACs */
SND_SOC_DAPM_ADC("Left ADC", "Left Capture", WM8400_POWER_MANAGEMENT_2,
	WM8400_ADCL_ENA_SHIFT, 0),
SND_SOC_DAPM_ADC("Right ADC", "Right Capture", WM8400_POWER_MANAGEMENT_2,
	WM8400_ADCR_ENA_SHIFT, 0),

/* Input PGAs */
SND_SOC_DAPM_MIXER("LIN12 PGA", WM8400_POWER_MANAGEMENT_2,
		   WM8400_LIN12_ENA_SHIFT,
		   0, &wm8400_dapm_lin12_pga_controls[0],
		   ARRAY_SIZE(wm8400_dapm_lin12_pga_controls)),
SND_SOC_DAPM_MIXER("LIN34 PGA", WM8400_POWER_MANAGEMENT_2,
		   WM8400_LIN34_ENA_SHIFT,
		   0, &wm8400_dapm_lin34_pga_controls[0],
		   ARRAY_SIZE(wm8400_dapm_lin34_pga_controls)),
SND_SOC_DAPM_MIXER("RIN12 PGA", WM8400_POWER_MANAGEMENT_2,
		   WM8400_RIN12_ENA_SHIFT,
		   0, &wm8400_dapm_rin12_pga_controls[0],
		   ARRAY_SIZE(wm8400_dapm_rin12_pga_controls)),
SND_SOC_DAPM_MIXER("RIN34 PGA", WM8400_POWER_MANAGEMENT_2,
		   WM8400_RIN34_ENA_SHIFT,
		   0, &wm8400_dapm_rin34_pga_controls[0],
		   ARRAY_SIZE(wm8400_dapm_rin34_pga_controls)),

SND_SOC_DAPM_SUPPLY("INL", WM8400_POWER_MANAGEMENT_2, WM8400_AINL_ENA_SHIFT,
		    0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("INR", WM8400_POWER_MANAGEMENT_2, WM8400_AINR_ENA_SHIFT,
		    0, शून्य, 0),

/* INMIXL */
SND_SOC_DAPM_MIXER("INMIXL", SND_SOC_NOPM, 0, 0,
	&wm8400_dapm_inmixl_controls[0],
	ARRAY_SIZE(wm8400_dapm_inmixl_controls)),

/* AINLMUX */
SND_SOC_DAPM_MUX("AILNMUX", SND_SOC_NOPM, 0, 0, &wm8400_dapm_ainlmux_controls),

/* INMIXR */
SND_SOC_DAPM_MIXER("INMIXR", SND_SOC_NOPM, 0, 0,
	&wm8400_dapm_inmixr_controls[0],
	ARRAY_SIZE(wm8400_dapm_inmixr_controls)),

/* AINRMUX */
SND_SOC_DAPM_MUX("AIRNMUX", SND_SOC_NOPM, 0, 0, &wm8400_dapm_ainrmux_controls),

/* Output Side */
/* DACs */
SND_SOC_DAPM_DAC("Left DAC", "Left Playback", WM8400_POWER_MANAGEMENT_3,
	WM8400_DACL_ENA_SHIFT, 0),
SND_SOC_DAPM_DAC("Right DAC", "Right Playback", WM8400_POWER_MANAGEMENT_3,
	WM8400_DACR_ENA_SHIFT, 0),

/* LOMIX */
SND_SOC_DAPM_MIXER_E("LOMIX", WM8400_POWER_MANAGEMENT_3,
		     WM8400_LOMIX_ENA_SHIFT,
		     0, &wm8400_dapm_lomix_controls[0],
		     ARRAY_SIZE(wm8400_dapm_lomix_controls),
		     ouपंचांगixer_event, SND_SOC_DAPM_PRE_REG),

/* LONMIX */
SND_SOC_DAPM_MIXER("LONMIX", WM8400_POWER_MANAGEMENT_3, WM8400_LON_ENA_SHIFT,
		   0, &wm8400_dapm_lonmix_controls[0],
		   ARRAY_SIZE(wm8400_dapm_lonmix_controls)),

/* LOPMIX */
SND_SOC_DAPM_MIXER("LOPMIX", WM8400_POWER_MANAGEMENT_3, WM8400_LOP_ENA_SHIFT,
		   0, &wm8400_dapm_lopmix_controls[0],
		   ARRAY_SIZE(wm8400_dapm_lopmix_controls)),

/* OUT3MIX */
SND_SOC_DAPM_MIXER("OUT3MIX", WM8400_POWER_MANAGEMENT_1, WM8400_OUT3_ENA_SHIFT,
		   0, &wm8400_dapm_out3mix_controls[0],
		   ARRAY_SIZE(wm8400_dapm_out3mix_controls)),

/* SPKMIX */
SND_SOC_DAPM_MIXER_E("SPKMIX", WM8400_POWER_MANAGEMENT_1, WM8400_SPK_ENA_SHIFT,
		     0, &wm8400_dapm_spkmix_controls[0],
		     ARRAY_SIZE(wm8400_dapm_spkmix_controls), ouपंचांगixer_event,
		     SND_SOC_DAPM_PRE_REG),

/* OUT4MIX */
SND_SOC_DAPM_MIXER("OUT4MIX", WM8400_POWER_MANAGEMENT_1, WM8400_OUT4_ENA_SHIFT,
	0, &wm8400_dapm_out4mix_controls[0],
	ARRAY_SIZE(wm8400_dapm_out4mix_controls)),

/* ROPMIX */
SND_SOC_DAPM_MIXER("ROPMIX", WM8400_POWER_MANAGEMENT_3, WM8400_ROP_ENA_SHIFT,
		   0, &wm8400_dapm_ropmix_controls[0],
		   ARRAY_SIZE(wm8400_dapm_ropmix_controls)),

/* RONMIX */
SND_SOC_DAPM_MIXER("RONMIX", WM8400_POWER_MANAGEMENT_3, WM8400_RON_ENA_SHIFT,
		   0, &wm8400_dapm_ronmix_controls[0],
		   ARRAY_SIZE(wm8400_dapm_ronmix_controls)),

/* ROMIX */
SND_SOC_DAPM_MIXER_E("ROMIX", WM8400_POWER_MANAGEMENT_3,
		     WM8400_ROMIX_ENA_SHIFT,
		     0, &wm8400_dapm_romix_controls[0],
		     ARRAY_SIZE(wm8400_dapm_romix_controls),
		     ouपंचांगixer_event, SND_SOC_DAPM_PRE_REG),

/* LOUT PGA */
SND_SOC_DAPM_PGA("LOUT PGA", WM8400_POWER_MANAGEMENT_1, WM8400_LOUT_ENA_SHIFT,
		 0, शून्य, 0),

/* ROUT PGA */
SND_SOC_DAPM_PGA("ROUT PGA", WM8400_POWER_MANAGEMENT_1, WM8400_ROUT_ENA_SHIFT,
		 0, शून्य, 0),

/* LOPGA */
SND_SOC_DAPM_PGA("LOPGA", WM8400_POWER_MANAGEMENT_3, WM8400_LOPGA_ENA_SHIFT, 0,
	शून्य, 0),

/* ROPGA */
SND_SOC_DAPM_PGA("ROPGA", WM8400_POWER_MANAGEMENT_3, WM8400_ROPGA_ENA_SHIFT, 0,
	शून्य, 0),

/* MICBIAS */
SND_SOC_DAPM_SUPPLY("MICBIAS", WM8400_POWER_MANAGEMENT_1,
		    WM8400_MIC1BIAS_ENA_SHIFT, 0, शून्य, 0),

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

अटल स्थिर काष्ठा snd_soc_dapm_route wm8400_dapm_routes[] = अणु
	/* Make DACs turn on when playing even अगर not mixed पूर्णांकo any outमाला_दो */
	अणु"Internal DAC Sink", शून्य, "Left DAC"पूर्ण,
	अणु"Internal DAC Sink", शून्य, "Right DAC"पूर्ण,

	/* Make ADCs turn on when recording
	 * even अगर not mixed from any inमाला_दो */
	अणु"Left ADC", शून्य, "Internal ADC Source"पूर्ण,
	अणु"Right ADC", शून्य, "Internal ADC Source"पूर्ण,

	/* Input Side */
	/* LIN12 PGA */
	अणु"LIN12 PGA", "LIN1 Switch", "LIN1"पूर्ण,
	अणु"LIN12 PGA", "LIN2 Switch", "LIN2"पूर्ण,
	/* LIN34 PGA */
	अणु"LIN34 PGA", "LIN3 Switch", "LIN3"पूर्ण,
	अणु"LIN34 PGA", "LIN4 Switch", "LIN4/RXN"पूर्ण,
	/* INMIXL */
	अणु"INMIXL", शून्य, "INL"पूर्ण,
	अणु"INMIXL", "Record Left Volume", "LOMIX"पूर्ण,
	अणु"INMIXL", "LIN2 Volume", "LIN2"पूर्ण,
	अणु"INMIXL", "LINPGA12 Switch", "LIN12 PGA"पूर्ण,
	अणु"INMIXL", "LINPGA34 Switch", "LIN34 PGA"पूर्ण,
	/* AILNMUX */
	अणु"AILNMUX", शून्य, "INL"पूर्ण,
	अणु"AILNMUX", "INMIXL Mix", "INMIXL"पूर्ण,
	अणु"AILNMUX", "DIFFINL Mix", "LIN12 PGA"पूर्ण,
	अणु"AILNMUX", "DIFFINL Mix", "LIN34 PGA"पूर्ण,
	अणु"AILNMUX", "RXVOICE Mix", "LIN4/RXN"पूर्ण,
	अणु"AILNMUX", "RXVOICE Mix", "RIN4/RXP"पूर्ण,
	/* ADC */
	अणु"Left ADC", शून्य, "AILNMUX"पूर्ण,

	/* RIN12 PGA */
	अणु"RIN12 PGA", "RIN1 Switch", "RIN1"पूर्ण,
	अणु"RIN12 PGA", "RIN2 Switch", "RIN2"पूर्ण,
	/* RIN34 PGA */
	अणु"RIN34 PGA", "RIN3 Switch", "RIN3"पूर्ण,
	अणु"RIN34 PGA", "RIN4 Switch", "RIN4/RXP"पूर्ण,
	/* INMIXR */
	अणु"INMIXR", शून्य, "INR"पूर्ण,
	अणु"INMIXR", "Record Right Volume", "ROMIX"पूर्ण,
	अणु"INMIXR", "RIN2 Volume", "RIN2"पूर्ण,
	अणु"INMIXR", "RINPGA12 Switch", "RIN12 PGA"पूर्ण,
	अणु"INMIXR", "RINPGA34 Switch", "RIN34 PGA"पूर्ण,
	/* AIRNMUX */
	अणु"AIRNMUX", शून्य, "INR"पूर्ण,
	अणु"AIRNMUX", "INMIXR Mix", "INMIXR"पूर्ण,
	अणु"AIRNMUX", "DIFFINR Mix", "RIN12 PGA"पूर्ण,
	अणु"AIRNMUX", "DIFFINR Mix", "RIN34 PGA"पूर्ण,
	अणु"AIRNMUX", "RXVOICE Mix", "LIN4/RXN"पूर्ण,
	अणु"AIRNMUX", "RXVOICE Mix", "RIN4/RXP"पूर्ण,
	/* ADC */
	अणु"Right ADC", शून्य, "AIRNMUX"पूर्ण,

	/* LOMIX */
	अणु"LOMIX", "LOMIX RIN3 Bypass Switch", "RIN3"पूर्ण,
	अणु"LOMIX", "LOMIX LIN3 Bypass Switch", "LIN3"पूर्ण,
	अणु"LOMIX", "LOMIX LIN12 PGA Bypass Switch", "LIN12 PGA"पूर्ण,
	अणु"LOMIX", "LOMIX RIN12 PGA Bypass Switch", "RIN12 PGA"पूर्ण,
	अणु"LOMIX", "LOMIX Right ADC Bypass Switch", "AIRNMUX"पूर्ण,
	अणु"LOMIX", "LOMIX Left ADC Bypass Switch", "AILNMUX"पूर्ण,
	अणु"LOMIX", "LOMIX Left DAC Switch", "Left DAC"पूर्ण,

	/* ROMIX */
	अणु"ROMIX", "ROMIX RIN3 Bypass Switch", "RIN3"पूर्ण,
	अणु"ROMIX", "ROMIX LIN3 Bypass Switch", "LIN3"पूर्ण,
	अणु"ROMIX", "ROMIX LIN12 PGA Bypass Switch", "LIN12 PGA"पूर्ण,
	अणु"ROMIX", "ROMIX RIN12 PGA Bypass Switch", "RIN12 PGA"पूर्ण,
	अणु"ROMIX", "ROMIX Right ADC Bypass Switch", "AIRNMUX"पूर्ण,
	अणु"ROMIX", "ROMIX Left ADC Bypass Switch", "AILNMUX"पूर्ण,
	अणु"ROMIX", "ROMIX Right DAC Switch", "Right DAC"पूर्ण,

	/* SPKMIX */
	अणु"SPKMIX", "SPKMIX LIN2 Bypass Switch", "LIN2"पूर्ण,
	अणु"SPKMIX", "SPKMIX RIN2 Bypass Switch", "RIN2"पूर्ण,
	अणु"SPKMIX", "SPKMIX LADC Bypass Switch", "AILNMUX"पूर्ण,
	अणु"SPKMIX", "SPKMIX RADC Bypass Switch", "AIRNMUX"पूर्ण,
	अणु"SPKMIX", "SPKMIX Left Mixer PGA Switch", "LOPGA"पूर्ण,
	अणु"SPKMIX", "SPKMIX Right Mixer PGA Switch", "ROPGA"पूर्ण,
	अणु"SPKMIX", "SPKMIX Right DAC Switch", "Right DAC"पूर्ण,
	अणु"SPKMIX", "SPKMIX Left DAC Switch", "Right DAC"पूर्ण,

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

/*
 * Clock after FLL and भागiders
 */
अटल पूर्णांक wm8400_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा wm8400_priv *wm8400 = snd_soc_component_get_drvdata(component);

	wm8400->sysclk = freq;
	वापस 0;
पूर्ण

काष्ठा fll_factors अणु
	u16 n;
	u16 k;
	u16 outभाग;
	u16 fratio;
	u16 freq_ref;
पूर्ण;

#घोषणा FIXED_FLL_SIZE ((1 << 16) * 10)

अटल पूर्णांक fll_factors(काष्ठा wm8400_priv *wm8400, काष्ठा fll_factors *factors,
		       अचिन्हित पूर्णांक Fref, अचिन्हित पूर्णांक Fout)
अणु
	u64 Kpart;
	अचिन्हित पूर्णांक K, Nmod, target;

	factors->outभाग = 2;
	जबतक (Fout * factors->outभाग <  90000000 ||
	       Fout * factors->outभाग > 100000000) अणु
		factors->outभाग *= 2;
		अगर (factors->outभाग > 32) अणु
			dev_err(wm8400->wm8400->dev,
				"Unsupported FLL output frequency %uHz\n",
				Fout);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	target = Fout * factors->outभाग;
	factors->outभाग = factors->outभाग >> 2;

	अगर (Fref < 48000)
		factors->freq_ref = 1;
	अन्यथा
		factors->freq_ref = 0;

	अगर (Fref < 1000000)
		factors->fratio = 9;
	अन्यथा
		factors->fratio = 0;

	/* Ensure we have a fractional part */
	करो अणु
		अगर (Fref < 1000000)
			factors->fratio--;
		अन्यथा
			factors->fratio++;

		अगर (factors->fratio < 1 || factors->fratio > 8) अणु
			dev_err(wm8400->wm8400->dev,
				"Unable to calculate FRATIO\n");
			वापस -EINVAL;
		पूर्ण

		factors->n = target / (Fref * factors->fratio);
		Nmod = target % (Fref * factors->fratio);
	पूर्ण जबतक (Nmod == 0);

	/* Calculate fractional part - scale up so we can round. */
	Kpart = FIXED_FLL_SIZE * (दीर्घ दीर्घ)Nmod;

	करो_भाग(Kpart, (Fref * factors->fratio));

	K = Kpart & 0xFFFFFFFF;

	अगर ((K % 10) >= 5)
		K += 5;

	/* Move करोwn to proper range now rounding is करोne */
	factors->k = K / 10;

	dev_dbg(wm8400->wm8400->dev,
		"FLL: Fref=%u Fout=%u N=%x K=%x, FRATIO=%x OUTDIV=%x\n",
		Fref, Fout,
		factors->n, factors->k, factors->fratio, factors->outभाग);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8400_set_dai_pll(काष्ठा snd_soc_dai *codec_dai, पूर्णांक pll_id,
			      पूर्णांक source, अचिन्हित पूर्णांक freq_in,
			      अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा wm8400_priv *wm8400 = snd_soc_component_get_drvdata(component);
	काष्ठा fll_factors factors;
	पूर्णांक ret;
	u16 reg;

	अगर (freq_in == wm8400->fll_in && freq_out == wm8400->fll_out)
		वापस 0;

	अगर (freq_out) अणु
		ret = fll_factors(wm8400, &factors, freq_in, freq_out);
		अगर (ret != 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		/* Bodge GCC 4.4.0 uninitialised variable warning - it
		 * करोesn't seem capable of working out that we निकास अगर
		 * freq_out is 0 beक्रमe any of the uses. */
		स_रखो(&factors, 0, माप(factors));
	पूर्ण

	wm8400->fll_out = freq_out;
	wm8400->fll_in = freq_in;

	/* We *must* disable the FLL beक्रमe any changes */
	reg = snd_soc_component_पढ़ो(component, WM8400_POWER_MANAGEMENT_2);
	reg &= ~WM8400_FLL_ENA;
	snd_soc_component_ग_लिखो(component, WM8400_POWER_MANAGEMENT_2, reg);

	reg = snd_soc_component_पढ़ो(component, WM8400_FLL_CONTROL_1);
	reg &= ~WM8400_FLL_OSC_ENA;
	snd_soc_component_ग_लिखो(component, WM8400_FLL_CONTROL_1, reg);

	अगर (!freq_out)
		वापस 0;

	reg &= ~(WM8400_FLL_REF_FREQ | WM8400_FLL_FRATIO_MASK);
	reg |= WM8400_FLL_FRAC | factors.fratio;
	reg |= factors.freq_ref << WM8400_FLL_REF_FREQ_SHIFT;
	snd_soc_component_ग_लिखो(component, WM8400_FLL_CONTROL_1, reg);

	snd_soc_component_ग_लिखो(component, WM8400_FLL_CONTROL_2, factors.k);
	snd_soc_component_ग_लिखो(component, WM8400_FLL_CONTROL_3, factors.n);

	reg = snd_soc_component_पढ़ो(component, WM8400_FLL_CONTROL_4);
	reg &= ~WM8400_FLL_OUTDIV_MASK;
	reg |= factors.outभाग;
	snd_soc_component_ग_लिखो(component, WM8400_FLL_CONTROL_4, reg);

	वापस 0;
पूर्ण

/*
 * Sets ADC and Voice DAC क्रमmat.
 */
अटल पूर्णांक wm8400_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 audio1, audio3;

	audio1 = snd_soc_component_पढ़ो(component, WM8400_AUDIO_INTERFACE_1);
	audio3 = snd_soc_component_पढ़ो(component, WM8400_AUDIO_INTERFACE_3);

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		audio3 &= ~WM8400_AIF_MSTR1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		audio3 |= WM8400_AIF_MSTR1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	audio1 &= ~WM8400_AIF_FMT_MASK;

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		audio1 |= WM8400_AIF_FMT_I2S;
		audio1 &= ~WM8400_AIF_LRCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		audio1 |= WM8400_AIF_FMT_RIGHTJ;
		audio1 &= ~WM8400_AIF_LRCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		audio1 |= WM8400_AIF_FMT_LEFTJ;
		audio1 &= ~WM8400_AIF_LRCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		audio1 |= WM8400_AIF_FMT_DSP;
		audio1 &= ~WM8400_AIF_LRCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		audio1 |= WM8400_AIF_FMT_DSP | WM8400_AIF_LRCLK_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8400_AUDIO_INTERFACE_1, audio1);
	snd_soc_component_ग_लिखो(component, WM8400_AUDIO_INTERFACE_3, audio3);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8400_set_dai_clkभाग(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक भाग_id, पूर्णांक भाग)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 reg;

	चयन (भाग_id) अणु
	हाल WM8400_MCLK_DIV:
		reg = snd_soc_component_पढ़ो(component, WM8400_CLOCKING_2) &
			~WM8400_MCLK_DIV_MASK;
		snd_soc_component_ग_लिखो(component, WM8400_CLOCKING_2, reg | भाग);
		अवरोध;
	हाल WM8400_DACCLK_DIV:
		reg = snd_soc_component_पढ़ो(component, WM8400_CLOCKING_2) &
			~WM8400_DAC_CLKDIV_MASK;
		snd_soc_component_ग_लिखो(component, WM8400_CLOCKING_2, reg | भाग);
		अवरोध;
	हाल WM8400_ADCCLK_DIV:
		reg = snd_soc_component_पढ़ो(component, WM8400_CLOCKING_2) &
			~WM8400_ADC_CLKDIV_MASK;
		snd_soc_component_ग_लिखो(component, WM8400_CLOCKING_2, reg | भाग);
		अवरोध;
	हाल WM8400_BCLK_DIV:
		reg = snd_soc_component_पढ़ो(component, WM8400_CLOCKING_1) &
			~WM8400_BCLK_DIV_MASK;
		snd_soc_component_ग_लिखो(component, WM8400_CLOCKING_1, reg | भाग);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Set PCM DAI bit size and sample rate.
 */
अटल पूर्णांक wm8400_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 audio1 = snd_soc_component_पढ़ो(component, WM8400_AUDIO_INTERFACE_1);

	audio1 &= ~WM8400_AIF_WL_MASK;
	/* bit size */
	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		audio1 |= WM8400_AIF_WL_20BITS;
		अवरोध;
	हाल 24:
		audio1 |= WM8400_AIF_WL_24BITS;
		अवरोध;
	हाल 32:
		audio1 |= WM8400_AIF_WL_32BITS;
		अवरोध;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8400_AUDIO_INTERFACE_1, audio1);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8400_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 val = snd_soc_component_पढ़ो(component, WM8400_DAC_CTRL) & ~WM8400_DAC_MUTE;

	अगर (mute)
		snd_soc_component_ग_लिखो(component, WM8400_DAC_CTRL, val | WM8400_DAC_MUTE);
	अन्यथा
		snd_soc_component_ग_लिखो(component, WM8400_DAC_CTRL, val);

	वापस 0;
पूर्ण

/* TODO: set bias क्रम best perक्रमmance at standby */
अटल पूर्णांक wm8400_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8400_priv *wm8400 = snd_soc_component_get_drvdata(component);
	u16 val;
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		/* VMID=2*50k */
		val = snd_soc_component_पढ़ो(component, WM8400_POWER_MANAGEMENT_1) &
			~WM8400_VMID_MODE_MASK;
		snd_soc_component_ग_लिखो(component, WM8400_POWER_MANAGEMENT_1, val | 0x2);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			ret = regulator_bulk_enable(ARRAY_SIZE(घातer),
						    &घातer[0]);
			अगर (ret != 0) अणु
				dev_err(wm8400->wm8400->dev,
					"Failed to enable regulators: %d\n",
					ret);
				वापस ret;
			पूर्ण

			snd_soc_component_ग_लिखो(component, WM8400_POWER_MANAGEMENT_1,
				     WM8400_CODEC_ENA | WM8400_SYSCLK_ENA);

			/* Enable POBCTRL, SOFT_ST, VMIDTOG and BUFDCOPEN */
			snd_soc_component_ग_लिखो(component, WM8400_ANTIPOP2, WM8400_SOFTST |
				     WM8400_BUFDCOPEN | WM8400_POBCTRL);

			msleep(50);

			/* Enable VREF & VMID at 2x50k */
			val = snd_soc_component_पढ़ो(component, WM8400_POWER_MANAGEMENT_1);
			val |= 0x2 | WM8400_VREF_ENA;
			snd_soc_component_ग_लिखो(component, WM8400_POWER_MANAGEMENT_1, val);

			/* Enable BUFIOEN */
			snd_soc_component_ग_लिखो(component, WM8400_ANTIPOP2, WM8400_SOFTST |
				     WM8400_BUFDCOPEN | WM8400_POBCTRL |
				     WM8400_BUFIOEN);

			/* disable POBCTRL, SOFT_ST and BUFDCOPEN */
			snd_soc_component_ग_लिखो(component, WM8400_ANTIPOP2, WM8400_BUFIOEN);
		पूर्ण

		/* VMID=2*300k */
		val = snd_soc_component_पढ़ो(component, WM8400_POWER_MANAGEMENT_1) &
			~WM8400_VMID_MODE_MASK;
		snd_soc_component_ग_लिखो(component, WM8400_POWER_MANAGEMENT_1, val | 0x4);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		/* Enable POBCTRL and SOFT_ST */
		snd_soc_component_ग_लिखो(component, WM8400_ANTIPOP2, WM8400_SOFTST |
			WM8400_POBCTRL | WM8400_BUFIOEN);

		/* Enable POBCTRL, SOFT_ST and BUFDCOPEN */
		snd_soc_component_ग_लिखो(component, WM8400_ANTIPOP2, WM8400_SOFTST |
			WM8400_BUFDCOPEN | WM8400_POBCTRL |
			WM8400_BUFIOEN);

		/* mute DAC */
		val = snd_soc_component_पढ़ो(component, WM8400_DAC_CTRL);
		snd_soc_component_ग_लिखो(component, WM8400_DAC_CTRL, val | WM8400_DAC_MUTE);

		/* Enable any disabled outमाला_दो */
		val = snd_soc_component_पढ़ो(component, WM8400_POWER_MANAGEMENT_1);
		val |= WM8400_SPK_ENA | WM8400_OUT3_ENA |
			WM8400_OUT4_ENA | WM8400_LOUT_ENA |
			WM8400_ROUT_ENA;
		snd_soc_component_ग_लिखो(component, WM8400_POWER_MANAGEMENT_1, val);

		/* Disable VMID */
		val &= ~WM8400_VMID_MODE_MASK;
		snd_soc_component_ग_लिखो(component, WM8400_POWER_MANAGEMENT_1, val);

		msleep(300);

		/* Enable all output disअक्षरge bits */
		snd_soc_component_ग_लिखो(component, WM8400_ANTIPOP1, WM8400_DIS_LLINE |
			WM8400_DIS_RLINE | WM8400_DIS_OUT3 |
			WM8400_DIS_OUT4 | WM8400_DIS_LOUT |
			WM8400_DIS_ROUT);

		/* Disable VREF */
		val &= ~WM8400_VREF_ENA;
		snd_soc_component_ग_लिखो(component, WM8400_POWER_MANAGEMENT_1, val);

		/* disable POBCTRL, SOFT_ST and BUFDCOPEN */
		snd_soc_component_ग_लिखो(component, WM8400_ANTIPOP2, 0x0);

		ret = regulator_bulk_disable(ARRAY_SIZE(घातer),
					     &घातer[0]);
		अगर (ret != 0)
			वापस ret;

		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा WM8400_RATES SNDRV_PCM_RATE_8000_96000

#घोषणा WM8400_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
	SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8400_dai_ops = अणु
	.hw_params = wm8400_hw_params,
	.mute_stream = wm8400_mute,
	.set_fmt = wm8400_set_dai_fmt,
	.set_clkभाग = wm8400_set_dai_clkभाग,
	.set_sysclk = wm8400_set_dai_sysclk,
	.set_pll = wm8400_set_dai_pll,
	.no_capture_mute = 1,
पूर्ण;

/*
 * The WM8400 supports 2 dअगरferent and mutually exclusive DAI
 * configurations.
 *
 * 1. ADC/DAC on Primary Interface
 * 2. ADC on Primary Interface/DAC on secondary
 */
अटल काष्ठा snd_soc_dai_driver wm8400_dai = अणु
/* ADC/DAC on primary */
	.name = "wm8400-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8400_RATES,
		.क्रमmats = WM8400_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8400_RATES,
		.क्रमmats = WM8400_FORMATS,
	पूर्ण,
	.ops = &wm8400_dai_ops,
पूर्ण;

अटल पूर्णांक wm8400_component_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8400 *wm8400 = dev_get_platdata(component->dev);
	काष्ठा wm8400_priv *priv;
	पूर्णांक ret;
	u16 reg;

	priv = devm_kzalloc(component->dev, माप(काष्ठा wm8400_priv),
			    GFP_KERNEL);
	अगर (priv == शून्य)
		वापस -ENOMEM;

	snd_soc_component_init_regmap(component, wm8400->regmap);
	snd_soc_component_set_drvdata(component, priv);
	priv->wm8400 = wm8400;

	ret = devm_regulator_bulk_get(wm8400->dev,
				 ARRAY_SIZE(घातer), &घातer[0]);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to get regulators: %d\n", ret);
		वापस ret;
	पूर्ण

	wm8400_component_reset(component);

	reg = snd_soc_component_पढ़ो(component, WM8400_POWER_MANAGEMENT_1);
	snd_soc_component_ग_लिखो(component, WM8400_POWER_MANAGEMENT_1, reg | WM8400_CODEC_ENA);

	/* Latch volume update bits */
	reg = snd_soc_component_पढ़ो(component, WM8400_LEFT_LINE_INPUT_1_2_VOLUME);
	snd_soc_component_ग_लिखो(component, WM8400_LEFT_LINE_INPUT_1_2_VOLUME,
		     reg & WM8400_IPVU);
	reg = snd_soc_component_पढ़ो(component, WM8400_RIGHT_LINE_INPUT_1_2_VOLUME);
	snd_soc_component_ग_लिखो(component, WM8400_RIGHT_LINE_INPUT_1_2_VOLUME,
		     reg & WM8400_IPVU);

	snd_soc_component_ग_लिखो(component, WM8400_LEFT_OUTPUT_VOLUME, 0x50 | (1<<8));
	snd_soc_component_ग_लिखो(component, WM8400_RIGHT_OUTPUT_VOLUME, 0x50 | (1<<8));

	वापस 0;
पूर्ण

अटल व्योम  wm8400_component_हटाओ(काष्ठा snd_soc_component *component)
अणु
	u16 reg;

	reg = snd_soc_component_पढ़ो(component, WM8400_POWER_MANAGEMENT_1);
	snd_soc_component_ग_लिखो(component, WM8400_POWER_MANAGEMENT_1,
		     reg & (~WM8400_CODEC_ENA));
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8400 = अणु
	.probe			= wm8400_component_probe,
	.हटाओ			= wm8400_component_हटाओ,
	.set_bias_level		= wm8400_set_bias_level,
	.controls		= wm8400_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8400_snd_controls),
	.dapm_widमाला_लो		= wm8400_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8400_dapm_widमाला_लो),
	.dapm_routes		= wm8400_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm8400_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक wm8400_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&soc_component_dev_wm8400,
			&wm8400_dai, 1);
पूर्ण

अटल काष्ठा platक्रमm_driver wm8400_codec_driver = अणु
	.driver = अणु
		   .name = "wm8400-codec",
		   पूर्ण,
	.probe = wm8400_probe,
पूर्ण;

module_platक्रमm_driver(wm8400_codec_driver);

MODULE_DESCRIPTION("ASoC WM8400 driver");
MODULE_AUTHOR("Mark Brown");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:wm8400-codec");
