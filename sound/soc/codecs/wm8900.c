<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8900.c  --  WM8900 ALSA Soc Audio driver
 *
 * Copyright 2007, 2008 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 *
 * TODO:
 *  - Tristating.
 *  - TDM.
 *  - Jack detect.
 *  - FLL source configuration, currently only MCLK is supported.
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "wm8900.h"

/* WM8900 रेजिस्टर space */
#घोषणा WM8900_REG_RESET	0x0
#घोषणा WM8900_REG_ID		0x0
#घोषणा WM8900_REG_POWER1	0x1
#घोषणा WM8900_REG_POWER2	0x2
#घोषणा WM8900_REG_POWER3	0x3
#घोषणा WM8900_REG_AUDIO1	0x4
#घोषणा WM8900_REG_AUDIO2	0x5
#घोषणा WM8900_REG_CLOCKING1    0x6
#घोषणा WM8900_REG_CLOCKING2    0x7
#घोषणा WM8900_REG_AUDIO3       0x8
#घोषणा WM8900_REG_AUDIO4       0x9
#घोषणा WM8900_REG_DACCTRL      0xa
#घोषणा WM8900_REG_LDAC_DV      0xb
#घोषणा WM8900_REG_RDAC_DV      0xc
#घोषणा WM8900_REG_SIDETONE     0xd
#घोषणा WM8900_REG_ADCCTRL      0xe
#घोषणा WM8900_REG_LADC_DV	0xf
#घोषणा WM8900_REG_RADC_DV      0x10
#घोषणा WM8900_REG_GPIO         0x12
#घोषणा WM8900_REG_INCTL	0x15
#घोषणा WM8900_REG_LINVOL	0x16
#घोषणा WM8900_REG_RINVOL	0x17
#घोषणा WM8900_REG_INBOOSTMIX1  0x18
#घोषणा WM8900_REG_INBOOSTMIX2  0x19
#घोषणा WM8900_REG_ADCPATH	0x1a
#घोषणा WM8900_REG_AUXBOOST	0x1b
#घोषणा WM8900_REG_ADDCTL       0x1e
#घोषणा WM8900_REG_FLLCTL1      0x24
#घोषणा WM8900_REG_FLLCTL2      0x25
#घोषणा WM8900_REG_FLLCTL3      0x26
#घोषणा WM8900_REG_FLLCTL4      0x27
#घोषणा WM8900_REG_FLLCTL5      0x28
#घोषणा WM8900_REG_FLLCTL6      0x29
#घोषणा WM8900_REG_LOUTMIXCTL1  0x2c
#घोषणा WM8900_REG_ROUTMIXCTL1  0x2d
#घोषणा WM8900_REG_BYPASS1	0x2e
#घोषणा WM8900_REG_BYPASS2	0x2f
#घोषणा WM8900_REG_AUXOUT_CTL   0x30
#घोषणा WM8900_REG_LOUT1CTL     0x33
#घोषणा WM8900_REG_ROUT1CTL     0x34
#घोषणा WM8900_REG_LOUT2CTL	0x35
#घोषणा WM8900_REG_ROUT2CTL	0x36
#घोषणा WM8900_REG_HPCTL1	0x3a
#घोषणा WM8900_REG_OUTBIASCTL   0x73

#घोषणा WM8900_MAXREG		0x80

#घोषणा WM8900_REG_ADDCTL_OUT1_DIS    0x80
#घोषणा WM8900_REG_ADDCTL_OUT2_DIS    0x40
#घोषणा WM8900_REG_ADDCTL_VMID_DIS    0x20
#घोषणा WM8900_REG_ADDCTL_BIAS_SRC    0x10
#घोषणा WM8900_REG_ADDCTL_VMID_SOFTST 0x04
#घोषणा WM8900_REG_ADDCTL_TEMP_SD     0x02

#घोषणा WM8900_REG_GPIO_TEMP_ENA   0x2

#घोषणा WM8900_REG_POWER1_STARTUP_BIAS_ENA 0x0100
#घोषणा WM8900_REG_POWER1_BIAS_ENA         0x0008
#घोषणा WM8900_REG_POWER1_VMID_BUF_ENA     0x0004
#घोषणा WM8900_REG_POWER1_FLL_ENA          0x0040

#घोषणा WM8900_REG_POWER2_SYSCLK_ENA  0x8000
#घोषणा WM8900_REG_POWER2_ADCL_ENA    0x0002
#घोषणा WM8900_REG_POWER2_ADCR_ENA    0x0001

#घोषणा WM8900_REG_POWER3_DACL_ENA    0x0002
#घोषणा WM8900_REG_POWER3_DACR_ENA    0x0001

#घोषणा WM8900_REG_AUDIO1_AIF_FMT_MASK 0x0018
#घोषणा WM8900_REG_AUDIO1_LRCLK_INV    0x0080
#घोषणा WM8900_REG_AUDIO1_BCLK_INV     0x0100

#घोषणा WM8900_REG_CLOCKING1_BCLK_सूची   0x1
#घोषणा WM8900_REG_CLOCKING1_MCLK_SRC   0x100
#घोषणा WM8900_REG_CLOCKING1_BCLK_MASK  0x01e
#घोषणा WM8900_REG_CLOCKING1_OPCLK_MASK 0x7000

#घोषणा WM8900_REG_CLOCKING2_ADC_CLKDIV 0xe0
#घोषणा WM8900_REG_CLOCKING2_DAC_CLKDIV 0x1c

#घोषणा WM8900_REG_DACCTRL_MUTE          0x004
#घोषणा WM8900_REG_DACCTRL_DAC_SB_FILT   0x100
#घोषणा WM8900_REG_DACCTRL_AIF_LRCLKRATE 0x400

#घोषणा WM8900_REG_AUDIO3_ADCLRC_सूची    0x0800

#घोषणा WM8900_REG_AUDIO4_DACLRC_सूची    0x0800

#घोषणा WM8900_REG_FLLCTL1_OSC_ENA    0x100

#घोषणा WM8900_REG_FLLCTL6_FLL_SLOW_LOCK_REF 0x100

#घोषणा WM8900_REG_HPCTL1_HP_IPSTAGE_ENA 0x80
#घोषणा WM8900_REG_HPCTL1_HP_OPSTAGE_ENA 0x40
#घोषणा WM8900_REG_HPCTL1_HP_CLAMP_IP    0x20
#घोषणा WM8900_REG_HPCTL1_HP_CLAMP_OP    0x10
#घोषणा WM8900_REG_HPCTL1_HP_SHORT       0x08
#घोषणा WM8900_REG_HPCTL1_HP_SHORT2      0x04

#घोषणा WM8900_LRC_MASK 0x03ff

काष्ठा wm8900_priv अणु
	काष्ठा regmap *regmap;

	u32 fll_in; /* FLL input frequency */
	u32 fll_out; /* FLL output frequency */
पूर्ण;

/*
 * wm8900 रेजिस्टर cache.  We can't पढ़ो the entire रेजिस्टर space and we
 * have slow control buses so we cache the रेजिस्टरs.
 */
अटल स्थिर काष्ठा reg_शेष wm8900_reg_शेषs[] = अणु
	अणु  1, 0x0000 पूर्ण,
	अणु  2, 0xc000 पूर्ण,
	अणु  3, 0x0000 पूर्ण,
	अणु  4, 0x4050 पूर्ण,
	अणु  5, 0x4000 पूर्ण,
	अणु  6, 0x0008 पूर्ण,
	अणु  7, 0x0000 पूर्ण,
	अणु  8, 0x0040 पूर्ण,
	अणु  9, 0x0040 पूर्ण,
	अणु 10, 0x1004 पूर्ण,
	अणु 11, 0x00c0 पूर्ण,
	अणु 12, 0x00c0 पूर्ण,
	अणु 13, 0x0000 पूर्ण,
	अणु 14, 0x0100 पूर्ण,
	अणु 15, 0x00c0 पूर्ण,
	अणु 16, 0x00c0 पूर्ण,
	अणु 17, 0x0000 पूर्ण,
	अणु 18, 0xb001 पूर्ण,
	अणु 19, 0x0000 पूर्ण,
	अणु 20, 0x0000 पूर्ण,
	अणु 21, 0x0044 पूर्ण,
	अणु 22, 0x004c पूर्ण,
	अणु 23, 0x004c पूर्ण,
	अणु 24, 0x0044 पूर्ण,
	अणु 25, 0x0044 पूर्ण,
	अणु 26, 0x0000 पूर्ण,
	अणु 27, 0x0044 पूर्ण,
	अणु 28, 0x0000 पूर्ण,
	अणु 29, 0x0000 पूर्ण,
	अणु 30, 0x0002 पूर्ण,
	अणु 31, 0x0000 पूर्ण,
	अणु 32, 0x0000 पूर्ण,
	अणु 33, 0x0000 पूर्ण,
	अणु 34, 0x0000 पूर्ण,
	अणु 35, 0x0000 पूर्ण,
	अणु 36, 0x0008 पूर्ण,
	अणु 37, 0x0000 पूर्ण,
	अणु 38, 0x0000 पूर्ण,
	अणु 39, 0x0008 पूर्ण,
	अणु 40, 0x0097 पूर्ण,
	अणु 41, 0x0100 पूर्ण,
	अणु 42, 0x0000 पूर्ण,
	अणु 43, 0x0000 पूर्ण,
	अणु 44, 0x0050 पूर्ण,
	अणु 45, 0x0050 पूर्ण,
	अणु 46, 0x0055 पूर्ण,
	अणु 47, 0x0055 पूर्ण,
	अणु 48, 0x0055 पूर्ण,
	अणु 49, 0x0000 पूर्ण,
	अणु 50, 0x0000 पूर्ण,
	अणु 51, 0x0079 पूर्ण,
	अणु 52, 0x0079 पूर्ण,
	अणु 53, 0x0079 पूर्ण,
	अणु 54, 0x0079 पूर्ण,
	अणु 55, 0x0000 पूर्ण,
पूर्ण;

अटल bool wm8900_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8900_REG_ID:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम wm8900_reset(काष्ठा snd_soc_component *component)
अणु
	snd_soc_component_ग_लिखो(component, WM8900_REG_RESET, 0);
पूर्ण

अटल पूर्णांक wm8900_hp_event(काष्ठा snd_soc_dapm_widget *w,
			   काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	u16 hpctl1 = snd_soc_component_पढ़ो(component, WM8900_REG_HPCTL1);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Clamp headphone outमाला_दो */
		hpctl1 = WM8900_REG_HPCTL1_HP_CLAMP_IP |
			WM8900_REG_HPCTL1_HP_CLAMP_OP;
		snd_soc_component_ग_लिखो(component, WM8900_REG_HPCTL1, hpctl1);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMU:
		/* Enable the input stage */
		hpctl1 &= ~WM8900_REG_HPCTL1_HP_CLAMP_IP;
		hpctl1 |= WM8900_REG_HPCTL1_HP_SHORT |
			WM8900_REG_HPCTL1_HP_SHORT2 |
			WM8900_REG_HPCTL1_HP_IPSTAGE_ENA;
		snd_soc_component_ग_लिखो(component, WM8900_REG_HPCTL1, hpctl1);

		msleep(400);

		/* Enable the output stage */
		hpctl1 &= ~WM8900_REG_HPCTL1_HP_CLAMP_OP;
		hpctl1 |= WM8900_REG_HPCTL1_HP_OPSTAGE_ENA;
		snd_soc_component_ग_लिखो(component, WM8900_REG_HPCTL1, hpctl1);

		/* Remove the लघुs */
		hpctl1 &= ~WM8900_REG_HPCTL1_HP_SHORT2;
		snd_soc_component_ग_लिखो(component, WM8900_REG_HPCTL1, hpctl1);
		hpctl1 &= ~WM8900_REG_HPCTL1_HP_SHORT;
		snd_soc_component_ग_लिखो(component, WM8900_REG_HPCTL1, hpctl1);
		अवरोध;

	हाल SND_SOC_DAPM_PRE_PMD:
		/* Short the output */
		hpctl1 |= WM8900_REG_HPCTL1_HP_SHORT;
		snd_soc_component_ग_लिखो(component, WM8900_REG_HPCTL1, hpctl1);

		/* Disable the output stage */
		hpctl1 &= ~WM8900_REG_HPCTL1_HP_OPSTAGE_ENA;
		snd_soc_component_ग_लिखो(component, WM8900_REG_HPCTL1, hpctl1);

		/* Clamp the outमाला_दो and घातer करोwn input */
		hpctl1 |= WM8900_REG_HPCTL1_HP_CLAMP_IP |
			WM8900_REG_HPCTL1_HP_CLAMP_OP;
		hpctl1 &= ~WM8900_REG_HPCTL1_HP_IPSTAGE_ENA;
		snd_soc_component_ग_लिखो(component, WM8900_REG_HPCTL1, hpctl1);
		अवरोध;

	हाल SND_SOC_DAPM_POST_PMD:
		/* Disable everything */
		snd_soc_component_ग_लिखो(component, WM8900_REG_HPCTL1, 0);
		अवरोध;

	शेष:
		WARN(1, "Invalid event %d\n", event);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(out_pga_tlv, -5700, 100, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(out_mix_tlv, -1500, 300, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(in_boost_tlv, -1200, 600, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(in_pga_tlv, -1200, 100, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(dac_boost_tlv, 0, 600, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(dac_tlv, -7200, 75, 1);

अटल स्थिर DECLARE_TLV_DB_SCALE(adc_svol_tlv, -3600, 300, 0);

अटल स्थिर DECLARE_TLV_DB_SCALE(adc_tlv, -7200, 75, 1);

अटल स्थिर अक्षर *mic_bias_level_txt[] = अणु "0.9*AVDD", "0.65*AVDD" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(mic_bias_level,
			    WM8900_REG_INCTL, 8, mic_bias_level_txt);

अटल स्थिर अक्षर *dac_mute_rate_txt[] = अणु "Fast", "Slow" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(dac_mute_rate,
			    WM8900_REG_DACCTRL, 7, dac_mute_rate_txt);

अटल स्थिर अक्षर *dac_deemphasis_txt[] = अणु
	"Disabled", "32kHz", "44.1kHz", "48kHz"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(dac_deemphasis,
			    WM8900_REG_DACCTRL, 4, dac_deemphasis_txt);

अटल स्थिर अक्षर *adc_hpf_cut_txt[] = अणु
	"Hi-fi mode", "Voice mode 1", "Voice mode 2", "Voice mode 3"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(adc_hpf_cut,
			    WM8900_REG_ADCCTRL, 5, adc_hpf_cut_txt);

अटल स्थिर अक्षर *lr_txt[] = अणु
	"Left", "Right"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(aअगरl_src,
			    WM8900_REG_AUDIO1, 15, lr_txt);

अटल SOC_ENUM_SINGLE_DECL(aअगरr_src,
			    WM8900_REG_AUDIO1, 14, lr_txt);

अटल SOC_ENUM_SINGLE_DECL(dacl_src,
			    WM8900_REG_AUDIO2, 15, lr_txt);

अटल SOC_ENUM_SINGLE_DECL(dacr_src,
			    WM8900_REG_AUDIO2, 14, lr_txt);

अटल स्थिर अक्षर *sidetone_txt[] = अणु
	"Disabled", "Left ADC", "Right ADC"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(dacl_sidetone,
			    WM8900_REG_SIDETONE, 2, sidetone_txt);

अटल SOC_ENUM_SINGLE_DECL(dacr_sidetone,
			    WM8900_REG_SIDETONE, 0, sidetone_txt);

अटल स्थिर काष्ठा snd_kcontrol_new wm8900_snd_controls[] = अणु
SOC_ENUM("Mic Bias Level", mic_bias_level),

SOC_SINGLE_TLV("Left Input PGA Volume", WM8900_REG_LINVOL, 0, 31, 0,
	       in_pga_tlv),
SOC_SINGLE("Left Input PGA Switch", WM8900_REG_LINVOL, 6, 1, 1),
SOC_SINGLE("Left Input PGA ZC Switch", WM8900_REG_LINVOL, 7, 1, 0),

SOC_SINGLE_TLV("Right Input PGA Volume", WM8900_REG_RINVOL, 0, 31, 0,
	       in_pga_tlv),
SOC_SINGLE("Right Input PGA Switch", WM8900_REG_RINVOL, 6, 1, 1),
SOC_SINGLE("Right Input PGA ZC Switch", WM8900_REG_RINVOL, 7, 1, 0),

SOC_SINGLE("DAC Soft Mute Switch", WM8900_REG_DACCTRL, 6, 1, 1),
SOC_ENUM("DAC Mute Rate", dac_mute_rate),
SOC_SINGLE("DAC Mono Switch", WM8900_REG_DACCTRL, 9, 1, 0),
SOC_ENUM("DAC Deemphasis", dac_deemphasis),
SOC_SINGLE("DAC Sigma-Delta Modulator Clock Switch", WM8900_REG_DACCTRL,
	   12, 1, 0),

SOC_SINGLE("ADC HPF Switch", WM8900_REG_ADCCTRL, 8, 1, 0),
SOC_ENUM("ADC HPF Cut-Off", adc_hpf_cut),
SOC_DOUBLE("ADC Invert Switch", WM8900_REG_ADCCTRL, 1, 0, 1, 0),
SOC_SINGLE_TLV("Left ADC Sidetone Volume", WM8900_REG_SIDETONE, 9, 12, 0,
	       adc_svol_tlv),
SOC_SINGLE_TLV("Right ADC Sidetone Volume", WM8900_REG_SIDETONE, 5, 12, 0,
	       adc_svol_tlv),
SOC_ENUM("Left Digital Audio Source", aअगरl_src),
SOC_ENUM("Right Digital Audio Source", aअगरr_src),

SOC_SINGLE_TLV("DAC Input Boost Volume", WM8900_REG_AUDIO2, 10, 4, 0,
	       dac_boost_tlv),
SOC_ENUM("Left DAC Source", dacl_src),
SOC_ENUM("Right DAC Source", dacr_src),
SOC_ENUM("Left DAC Sidetone", dacl_sidetone),
SOC_ENUM("Right DAC Sidetone", dacr_sidetone),
SOC_DOUBLE("DAC Invert Switch", WM8900_REG_DACCTRL, 1, 0, 1, 0),

SOC_DOUBLE_R_TLV("Digital Playback Volume",
		 WM8900_REG_LDAC_DV, WM8900_REG_RDAC_DV,
		 1, 96, 0, dac_tlv),
SOC_DOUBLE_R_TLV("Digital Capture Volume",
		 WM8900_REG_LADC_DV, WM8900_REG_RADC_DV, 1, 119, 0, adc_tlv),

SOC_SINGLE_TLV("LINPUT3 Bypass Volume", WM8900_REG_LOUTMIXCTL1, 4, 7, 0,
	       out_mix_tlv),
SOC_SINGLE_TLV("RINPUT3 Bypass Volume", WM8900_REG_ROUTMIXCTL1, 4, 7, 0,
	       out_mix_tlv),
SOC_SINGLE_TLV("Left AUX Bypass Volume", WM8900_REG_AUXOUT_CTL, 4, 7, 0,
	       out_mix_tlv),
SOC_SINGLE_TLV("Right AUX Bypass Volume", WM8900_REG_AUXOUT_CTL, 0, 7, 0,
	       out_mix_tlv),

SOC_SINGLE_TLV("LeftIn to RightOut Mixer Volume", WM8900_REG_BYPASS1, 0, 7, 0,
	       out_mix_tlv),
SOC_SINGLE_TLV("LeftIn to LeftOut Mixer Volume", WM8900_REG_BYPASS1, 4, 7, 0,
	       out_mix_tlv),
SOC_SINGLE_TLV("RightIn to LeftOut Mixer Volume", WM8900_REG_BYPASS2, 0, 7, 0,
	       out_mix_tlv),
SOC_SINGLE_TLV("RightIn to RightOut Mixer Volume", WM8900_REG_BYPASS2, 4, 7, 0,
	       out_mix_tlv),

SOC_SINGLE_TLV("IN2L Boost Volume", WM8900_REG_INBOOSTMIX1, 0, 3, 0,
	       in_boost_tlv),
SOC_SINGLE_TLV("IN3L Boost Volume", WM8900_REG_INBOOSTMIX1, 4, 3, 0,
	       in_boost_tlv),
SOC_SINGLE_TLV("IN2R Boost Volume", WM8900_REG_INBOOSTMIX2, 0, 3, 0,
	       in_boost_tlv),
SOC_SINGLE_TLV("IN3R Boost Volume", WM8900_REG_INBOOSTMIX2, 4, 3, 0,
	       in_boost_tlv),
SOC_SINGLE_TLV("Left AUX Boost Volume", WM8900_REG_AUXBOOST, 4, 3, 0,
	       in_boost_tlv),
SOC_SINGLE_TLV("Right AUX Boost Volume", WM8900_REG_AUXBOOST, 0, 3, 0,
	       in_boost_tlv),

SOC_DOUBLE_R_TLV("LINEOUT1 Volume", WM8900_REG_LOUT1CTL, WM8900_REG_ROUT1CTL,
	       0, 63, 0, out_pga_tlv),
SOC_DOUBLE_R("LINEOUT1 Switch", WM8900_REG_LOUT1CTL, WM8900_REG_ROUT1CTL,
	     6, 1, 1),
SOC_DOUBLE_R("LINEOUT1 ZC Switch", WM8900_REG_LOUT1CTL, WM8900_REG_ROUT1CTL,
	     7, 1, 0),

SOC_DOUBLE_R_TLV("LINEOUT2 Volume",
		 WM8900_REG_LOUT2CTL, WM8900_REG_ROUT2CTL,
		 0, 63, 0, out_pga_tlv),
SOC_DOUBLE_R("LINEOUT2 Switch",
	     WM8900_REG_LOUT2CTL, WM8900_REG_ROUT2CTL, 6, 1, 1),
SOC_DOUBLE_R("LINEOUT2 ZC Switch",
	     WM8900_REG_LOUT2CTL, WM8900_REG_ROUT2CTL, 7, 1, 0),
SOC_SINGLE("LINEOUT2 LP -12dB", WM8900_REG_LOUTMIXCTL1,
	   0, 1, 1),

पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8900_louपंचांगix_controls[] = अणु
SOC_DAPM_SINGLE("LINPUT3 Bypass Switch", WM8900_REG_LOUTMIXCTL1, 7, 1, 0),
SOC_DAPM_SINGLE("AUX Bypass Switch", WM8900_REG_AUXOUT_CTL, 7, 1, 0),
SOC_DAPM_SINGLE("Left Input Mixer Switch", WM8900_REG_BYPASS1, 7, 1, 0),
SOC_DAPM_SINGLE("Right Input Mixer Switch", WM8900_REG_BYPASS2, 3, 1, 0),
SOC_DAPM_SINGLE("DACL Switch", WM8900_REG_LOUTMIXCTL1, 8, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8900_rouपंचांगix_controls[] = अणु
SOC_DAPM_SINGLE("RINPUT3 Bypass Switch", WM8900_REG_ROUTMIXCTL1, 7, 1, 0),
SOC_DAPM_SINGLE("AUX Bypass Switch", WM8900_REG_AUXOUT_CTL, 3, 1, 0),
SOC_DAPM_SINGLE("Left Input Mixer Switch", WM8900_REG_BYPASS1, 3, 1, 0),
SOC_DAPM_SINGLE("Right Input Mixer Switch", WM8900_REG_BYPASS2, 7, 1, 0),
SOC_DAPM_SINGLE("DACR Switch", WM8900_REG_ROUTMIXCTL1, 8, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8900_linmix_controls[] = अणु
SOC_DAPM_SINGLE("LINPUT2 Switch", WM8900_REG_INBOOSTMIX1, 2, 1, 1),
SOC_DAPM_SINGLE("LINPUT3 Switch", WM8900_REG_INBOOSTMIX1, 6, 1, 1),
SOC_DAPM_SINGLE("AUX Switch", WM8900_REG_AUXBOOST, 6, 1, 1),
SOC_DAPM_SINGLE("Input PGA Switch", WM8900_REG_ADCPATH, 6, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8900_rinmix_controls[] = अणु
SOC_DAPM_SINGLE("RINPUT2 Switch", WM8900_REG_INBOOSTMIX2, 2, 1, 1),
SOC_DAPM_SINGLE("RINPUT3 Switch", WM8900_REG_INBOOSTMIX2, 6, 1, 1),
SOC_DAPM_SINGLE("AUX Switch", WM8900_REG_AUXBOOST, 2, 1, 1),
SOC_DAPM_SINGLE("Input PGA Switch", WM8900_REG_ADCPATH, 2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8900_linpga_controls[] = अणु
SOC_DAPM_SINGLE("LINPUT1 Switch", WM8900_REG_INCTL, 6, 1, 0),
SOC_DAPM_SINGLE("LINPUT2 Switch", WM8900_REG_INCTL, 5, 1, 0),
SOC_DAPM_SINGLE("LINPUT3 Switch", WM8900_REG_INCTL, 4, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wm8900_rinpga_controls[] = अणु
SOC_DAPM_SINGLE("RINPUT1 Switch", WM8900_REG_INCTL, 2, 1, 0),
SOC_DAPM_SINGLE("RINPUT2 Switch", WM8900_REG_INCTL, 1, 1, 0),
SOC_DAPM_SINGLE("RINPUT3 Switch", WM8900_REG_INCTL, 0, 1, 0),
पूर्ण;

अटल स्थिर अक्षर *wm8900_lp_mux[] = अणु "Disabled", "Enabled" पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(wm8900_lineout2_lp_mux,
			    WM8900_REG_LOUTMIXCTL1, 1, wm8900_lp_mux);

अटल स्थिर काष्ठा snd_kcontrol_new wm8900_lineout2_lp =
SOC_DAPM_ENUM("Route", wm8900_lineout2_lp_mux);

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8900_dapm_widमाला_लो[] = अणु

/* Externally visible pins */
SND_SOC_DAPM_OUTPUT("LINEOUT1L"),
SND_SOC_DAPM_OUTPUT("LINEOUT1R"),
SND_SOC_DAPM_OUTPUT("LINEOUT2L"),
SND_SOC_DAPM_OUTPUT("LINEOUT2R"),
SND_SOC_DAPM_OUTPUT("HP_L"),
SND_SOC_DAPM_OUTPUT("HP_R"),

SND_SOC_DAPM_INPUT("RINPUT1"),
SND_SOC_DAPM_INPUT("LINPUT1"),
SND_SOC_DAPM_INPUT("RINPUT2"),
SND_SOC_DAPM_INPUT("LINPUT2"),
SND_SOC_DAPM_INPUT("RINPUT3"),
SND_SOC_DAPM_INPUT("LINPUT3"),
SND_SOC_DAPM_INPUT("AUX"),

SND_SOC_DAPM_VMID("VMID"),

/* Input */
SND_SOC_DAPM_MIXER("Left Input PGA", WM8900_REG_POWER2, 3, 0,
		   wm8900_linpga_controls,
		   ARRAY_SIZE(wm8900_linpga_controls)),
SND_SOC_DAPM_MIXER("Right Input PGA", WM8900_REG_POWER2, 2, 0,
		   wm8900_rinpga_controls,
		   ARRAY_SIZE(wm8900_rinpga_controls)),

SND_SOC_DAPM_MIXER("Left Input Mixer", WM8900_REG_POWER2, 5, 0,
		   wm8900_linmix_controls,
		   ARRAY_SIZE(wm8900_linmix_controls)),
SND_SOC_DAPM_MIXER("Right Input Mixer", WM8900_REG_POWER2, 4, 0,
		   wm8900_rinmix_controls,
		   ARRAY_SIZE(wm8900_rinmix_controls)),

SND_SOC_DAPM_SUPPLY("Mic Bias", WM8900_REG_POWER1, 4, 0, शून्य, 0),

SND_SOC_DAPM_ADC("ADCL", "Left HiFi Capture", WM8900_REG_POWER2, 1, 0),
SND_SOC_DAPM_ADC("ADCR", "Right HiFi Capture", WM8900_REG_POWER2, 0, 0),

/* Output */
SND_SOC_DAPM_DAC("DACL", "Left HiFi Playback", WM8900_REG_POWER3, 1, 0),
SND_SOC_DAPM_DAC("DACR", "Right HiFi Playback", WM8900_REG_POWER3, 0, 0),

SND_SOC_DAPM_PGA_E("Headphone Amplifier", WM8900_REG_POWER3, 7, 0, शून्य, 0,
		   wm8900_hp_event,
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMU |
		   SND_SOC_DAPM_PRE_PMD | SND_SOC_DAPM_POST_PMD),

SND_SOC_DAPM_PGA("LINEOUT1L PGA", WM8900_REG_POWER2, 8, 0, शून्य, 0),
SND_SOC_DAPM_PGA("LINEOUT1R PGA", WM8900_REG_POWER2, 7, 0, शून्य, 0),

SND_SOC_DAPM_MUX("LINEOUT2 LP", SND_SOC_NOPM, 0, 0, &wm8900_lineout2_lp),
SND_SOC_DAPM_PGA("LINEOUT2L PGA", WM8900_REG_POWER3, 6, 0, शून्य, 0),
SND_SOC_DAPM_PGA("LINEOUT2R PGA", WM8900_REG_POWER3, 5, 0, शून्य, 0),

SND_SOC_DAPM_MIXER("Left Output Mixer", WM8900_REG_POWER3, 3, 0,
		   wm8900_louपंचांगix_controls,
		   ARRAY_SIZE(wm8900_louपंचांगix_controls)),
SND_SOC_DAPM_MIXER("Right Output Mixer", WM8900_REG_POWER3, 2, 0,
		   wm8900_rouपंचांगix_controls,
		   ARRAY_SIZE(wm8900_rouपंचांगix_controls)),
पूर्ण;

/* Target, Path, Source */
अटल स्थिर काष्ठा snd_soc_dapm_route wm8900_dapm_routes[] = अणु
/* Inमाला_दो */
अणु"Left Input PGA", "LINPUT1 Switch", "LINPUT1"पूर्ण,
अणु"Left Input PGA", "LINPUT2 Switch", "LINPUT2"पूर्ण,
अणु"Left Input PGA", "LINPUT3 Switch", "LINPUT3"पूर्ण,

अणु"Right Input PGA", "RINPUT1 Switch", "RINPUT1"पूर्ण,
अणु"Right Input PGA", "RINPUT2 Switch", "RINPUT2"पूर्ण,
अणु"Right Input PGA", "RINPUT3 Switch", "RINPUT3"पूर्ण,

अणु"Left Input Mixer", "LINPUT2 Switch", "LINPUT2"पूर्ण,
अणु"Left Input Mixer", "LINPUT3 Switch", "LINPUT3"पूर्ण,
अणु"Left Input Mixer", "AUX Switch", "AUX"पूर्ण,
अणु"Left Input Mixer", "Input PGA Switch", "Left Input PGA"पूर्ण,

अणु"Right Input Mixer", "RINPUT2 Switch", "RINPUT2"पूर्ण,
अणु"Right Input Mixer", "RINPUT3 Switch", "RINPUT3"पूर्ण,
अणु"Right Input Mixer", "AUX Switch", "AUX"पूर्ण,
अणु"Right Input Mixer", "Input PGA Switch", "Right Input PGA"पूर्ण,

अणु"ADCL", शून्य, "Left Input Mixer"पूर्ण,
अणु"ADCR", शून्य, "Right Input Mixer"पूर्ण,

/* Outमाला_दो */
अणु"LINEOUT1L", शून्य, "LINEOUT1L PGA"पूर्ण,
अणु"LINEOUT1L PGA", शून्य, "Left Output Mixer"पूर्ण,
अणु"LINEOUT1R", शून्य, "LINEOUT1R PGA"पूर्ण,
अणु"LINEOUT1R PGA", शून्य, "Right Output Mixer"पूर्ण,

अणु"LINEOUT2L PGA", शून्य, "Left Output Mixer"पूर्ण,
अणु"LINEOUT2 LP", "Disabled", "LINEOUT2L PGA"पूर्ण,
अणु"LINEOUT2 LP", "Enabled", "Left Output Mixer"पूर्ण,
अणु"LINEOUT2L", शून्य, "LINEOUT2 LP"पूर्ण,

अणु"LINEOUT2R PGA", शून्य, "Right Output Mixer"पूर्ण,
अणु"LINEOUT2 LP", "Disabled", "LINEOUT2R PGA"पूर्ण,
अणु"LINEOUT2 LP", "Enabled", "Right Output Mixer"पूर्ण,
अणु"LINEOUT2R", शून्य, "LINEOUT2 LP"पूर्ण,

अणु"Left Output Mixer", "LINPUT3 Bypass Switch", "LINPUT3"पूर्ण,
अणु"Left Output Mixer", "AUX Bypass Switch", "AUX"पूर्ण,
अणु"Left Output Mixer", "Left Input Mixer Switch", "Left Input Mixer"पूर्ण,
अणु"Left Output Mixer", "Right Input Mixer Switch", "Right Input Mixer"पूर्ण,
अणु"Left Output Mixer", "DACL Switch", "DACL"पूर्ण,

अणु"Right Output Mixer", "RINPUT3 Bypass Switch", "RINPUT3"पूर्ण,
अणु"Right Output Mixer", "AUX Bypass Switch", "AUX"पूर्ण,
अणु"Right Output Mixer", "Left Input Mixer Switch", "Left Input Mixer"पूर्ण,
अणु"Right Output Mixer", "Right Input Mixer Switch", "Right Input Mixer"पूर्ण,
अणु"Right Output Mixer", "DACR Switch", "DACR"पूर्ण,

/* Note that the headphone output stage needs to be connected
 * बाह्यally to LINEOUT2 via DC blocking capacitors.  Other
 * configurations are not supported.
 *
 * Note also that left and right headphone paths are treated as a
 * mono path.
 */
अणु"Headphone Amplifier", शून्य, "LINEOUT2 LP"पूर्ण,
अणु"Headphone Amplifier", शून्य, "LINEOUT2 LP"पूर्ण,
अणु"HP_L", शून्य, "Headphone Amplifier"पूर्ण,
अणु"HP_R", शून्य, "Headphone Amplifier"पूर्ण,
पूर्ण;

अटल पूर्णांक wm8900_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 reg;

	reg = snd_soc_component_पढ़ो(component, WM8900_REG_AUDIO1) & ~0x60;

	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		reg |= 0x20;
		अवरोध;
	हाल 24:
		reg |= 0x40;
		अवरोध;
	हाल 32:
		reg |= 0x60;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8900_REG_AUDIO1, reg);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		reg = snd_soc_component_पढ़ो(component, WM8900_REG_DACCTRL);

		अगर (params_rate(params) <= 24000)
			reg |= WM8900_REG_DACCTRL_DAC_SB_FILT;
		अन्यथा
			reg &= ~WM8900_REG_DACCTRL_DAC_SB_FILT;

		snd_soc_component_ग_लिखो(component, WM8900_REG_DACCTRL, reg);
	पूर्ण

	वापस 0;
पूर्ण

/* FLL भागisors */
काष्ठा _fll_भाग अणु
	u16 fll_ratio;
	u16 fllclk_भाग;
	u16 fll_slow_lock_ref;
	u16 n;
	u16 k;
पूर्ण;

/* The size in bits of the FLL भागide multiplied by 10
 * to allow rounding later */
#घोषणा FIXED_FLL_SIZE ((1 << 16) * 10)

अटल पूर्णांक fll_factors(काष्ठा _fll_भाग *fll_भाग, अचिन्हित पूर्णांक Fref,
		       अचिन्हित पूर्णांक Fout)
अणु
	u64 Kpart;
	अचिन्हित पूर्णांक K, Nभाग, Nmod, target;
	अचिन्हित पूर्णांक भाग;

	अगर (WARN_ON(!Fout))
		वापस -EINVAL;

	/* The FLL must run at 90-100MHz which is then scaled करोwn to
	 * the output value by FLLCLK_DIV. */
	target = Fout;
	भाग = 1;
	जबतक (target < 90000000) अणु
		भाग *= 2;
		target *= 2;
	पूर्ण

	अगर (target > 100000000)
		prपूर्णांकk(KERN_WARNING "wm8900: FLL rate %u out of range, Fref=%u"
		       " Fout=%u\n", target, Fref, Fout);
	अगर (भाग > 32) अणु
		prपूर्णांकk(KERN_ERR "wm8900: Invalid FLL division rate %u, "
		       "Fref=%u, Fout=%u, target=%u\n",
		       भाग, Fref, Fout, target);
		वापस -EINVAL;
	पूर्ण

	fll_भाग->fllclk_भाग = भाग >> 2;

	अगर (Fref < 48000)
		fll_भाग->fll_slow_lock_ref = 1;
	अन्यथा
		fll_भाग->fll_slow_lock_ref = 0;

	Nभाग = target / Fref;

	अगर (Fref < 1000000)
		fll_भाग->fll_ratio = 8;
	अन्यथा
		fll_भाग->fll_ratio = 1;

	fll_भाग->n = Nभाग / fll_भाग->fll_ratio;
	Nmod = (target / fll_भाग->fll_ratio) % Fref;

	/* Calculate fractional part - scale up so we can round. */
	Kpart = FIXED_FLL_SIZE * (दीर्घ दीर्घ)Nmod;

	करो_भाग(Kpart, Fref);

	K = Kpart & 0xFFFFFFFF;

	अगर ((K % 10) >= 5)
		K += 5;

	/* Move करोwn to proper range now rounding is करोne */
	fll_भाग->k = K / 10;

	अगर (WARN_ON(target != Fout * (fll_भाग->fllclk_भाग << 2)) ||
	    WARN_ON(!K && target != Fref * fll_भाग->fll_ratio * fll_भाग->n))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8900_set_fll(काष्ठा snd_soc_component *component,
	पूर्णांक fll_id, अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	काष्ठा wm8900_priv *wm8900 = snd_soc_component_get_drvdata(component);
	काष्ठा _fll_भाग fll_भाग;

	अगर (wm8900->fll_in == freq_in && wm8900->fll_out == freq_out)
		वापस 0;

	/* The digital side should be disabled during any change. */
	snd_soc_component_update_bits(component, WM8900_REG_POWER1,
			    WM8900_REG_POWER1_FLL_ENA, 0);

	/* Disable the FLL? */
	अगर (!freq_in || !freq_out) अणु
		snd_soc_component_update_bits(component, WM8900_REG_CLOCKING1,
				    WM8900_REG_CLOCKING1_MCLK_SRC, 0);
		snd_soc_component_update_bits(component, WM8900_REG_FLLCTL1,
				    WM8900_REG_FLLCTL1_OSC_ENA, 0);
		wm8900->fll_in = freq_in;
		wm8900->fll_out = freq_out;

		वापस 0;
	पूर्ण

	अगर (fll_factors(&fll_भाग, freq_in, freq_out) != 0)
		जाओ reenable;

	wm8900->fll_in = freq_in;
	wm8900->fll_out = freq_out;

	/* The osclilator *MUST* be enabled beक्रमe we enable the
	 * digital circuit. */
	snd_soc_component_ग_लिखो(component, WM8900_REG_FLLCTL1,
		     fll_भाग.fll_ratio | WM8900_REG_FLLCTL1_OSC_ENA);

	snd_soc_component_ग_लिखो(component, WM8900_REG_FLLCTL4, fll_भाग.n >> 5);
	snd_soc_component_ग_लिखो(component, WM8900_REG_FLLCTL5,
		     (fll_भाग.fllclk_भाग << 6) | (fll_भाग.n & 0x1f));

	अगर (fll_भाग.k) अणु
		snd_soc_component_ग_लिखो(component, WM8900_REG_FLLCTL2,
			     (fll_भाग.k >> 8) | 0x100);
		snd_soc_component_ग_लिखो(component, WM8900_REG_FLLCTL3, fll_भाग.k & 0xff);
	पूर्ण अन्यथा
		snd_soc_component_ग_लिखो(component, WM8900_REG_FLLCTL2, 0);

	अगर (fll_भाग.fll_slow_lock_ref)
		snd_soc_component_ग_लिखो(component, WM8900_REG_FLLCTL6,
			     WM8900_REG_FLLCTL6_FLL_SLOW_LOCK_REF);
	अन्यथा
		snd_soc_component_ग_लिखो(component, WM8900_REG_FLLCTL6, 0);

	snd_soc_component_update_bits(component, WM8900_REG_POWER1,
			    WM8900_REG_POWER1_FLL_ENA,
			    WM8900_REG_POWER1_FLL_ENA);

reenable:
	snd_soc_component_update_bits(component, WM8900_REG_CLOCKING1,
			    WM8900_REG_CLOCKING1_MCLK_SRC,
			    WM8900_REG_CLOCKING1_MCLK_SRC);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8900_set_dai_pll(काष्ठा snd_soc_dai *codec_dai, पूर्णांक pll_id,
		पूर्णांक source, अचिन्हित पूर्णांक freq_in, अचिन्हित पूर्णांक freq_out)
अणु
	वापस wm8900_set_fll(codec_dai->component, pll_id, freq_in, freq_out);
पूर्ण

अटल पूर्णांक wm8900_set_dai_clkभाग(काष्ठा snd_soc_dai *codec_dai,
				 पूर्णांक भाग_id, पूर्णांक भाग)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;

	चयन (भाग_id) अणु
	हाल WM8900_BCLK_DIV:
		snd_soc_component_update_bits(component, WM8900_REG_CLOCKING1,
				    WM8900_REG_CLOCKING1_BCLK_MASK, भाग);
		अवरोध;
	हाल WM8900_OPCLK_DIV:
		snd_soc_component_update_bits(component, WM8900_REG_CLOCKING1,
				    WM8900_REG_CLOCKING1_OPCLK_MASK, भाग);
		अवरोध;
	हाल WM8900_DAC_LRCLK:
		snd_soc_component_update_bits(component, WM8900_REG_AUDIO4,
				    WM8900_LRC_MASK, भाग);
		अवरोध;
	हाल WM8900_ADC_LRCLK:
		snd_soc_component_update_bits(component, WM8900_REG_AUDIO3,
				    WM8900_LRC_MASK, भाग);
		अवरोध;
	हाल WM8900_DAC_CLKDIV:
		snd_soc_component_update_bits(component, WM8900_REG_CLOCKING2,
				    WM8900_REG_CLOCKING2_DAC_CLKDIV, भाग);
		अवरोध;
	हाल WM8900_ADC_CLKDIV:
		snd_soc_component_update_bits(component, WM8900_REG_CLOCKING2,
				    WM8900_REG_CLOCKING2_ADC_CLKDIV, भाग);
		अवरोध;
	हाल WM8900_LRCLK_MODE:
		snd_soc_component_update_bits(component, WM8900_REG_DACCTRL,
				    WM8900_REG_DACCTRL_AIF_LRCLKRATE, भाग);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण


अटल पूर्णांक wm8900_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
			      अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	अचिन्हित पूर्णांक घड़ीing1, aअगर1, aअगर3, aअगर4;

	घड़ीing1 = snd_soc_component_पढ़ो(component, WM8900_REG_CLOCKING1);
	aअगर1 = snd_soc_component_पढ़ो(component, WM8900_REG_AUDIO1);
	aअगर3 = snd_soc_component_पढ़ो(component, WM8900_REG_AUDIO3);
	aअगर4 = snd_soc_component_पढ़ो(component, WM8900_REG_AUDIO4);

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		घड़ीing1 &= ~WM8900_REG_CLOCKING1_BCLK_सूची;
		aअगर3 &= ~WM8900_REG_AUDIO3_ADCLRC_सूची;
		aअगर4 &= ~WM8900_REG_AUDIO4_DACLRC_सूची;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		घड़ीing1 &= ~WM8900_REG_CLOCKING1_BCLK_सूची;
		aअगर3 |= WM8900_REG_AUDIO3_ADCLRC_सूची;
		aअगर4 |= WM8900_REG_AUDIO4_DACLRC_सूची;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		घड़ीing1 |= WM8900_REG_CLOCKING1_BCLK_सूची;
		aअगर3 |= WM8900_REG_AUDIO3_ADCLRC_सूची;
		aअगर4 |= WM8900_REG_AUDIO4_DACLRC_सूची;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		घड़ीing1 |= WM8900_REG_CLOCKING1_BCLK_सूची;
		aअगर3 &= ~WM8900_REG_AUDIO3_ADCLRC_सूची;
		aअगर4 &= ~WM8900_REG_AUDIO4_DACLRC_सूची;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
		aअगर1 |= WM8900_REG_AUDIO1_AIF_FMT_MASK;
		aअगर1 &= ~WM8900_REG_AUDIO1_LRCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		aअगर1 |= WM8900_REG_AUDIO1_AIF_FMT_MASK;
		aअगर1 |= WM8900_REG_AUDIO1_LRCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		aअगर1 &= ~WM8900_REG_AUDIO1_AIF_FMT_MASK;
		aअगर1 |= 0x10;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		aअगर1 &= ~WM8900_REG_AUDIO1_AIF_FMT_MASK;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		aअगर1 &= ~WM8900_REG_AUDIO1_AIF_FMT_MASK;
		aअगर1 |= 0x8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Clock inversion */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_DSP_A:
	हाल SND_SOC_DAIFMT_DSP_B:
		/* frame inversion not valid क्रम DSP modes */
		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			aअगर1 &= ~WM8900_REG_AUDIO1_BCLK_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			aअगर1 |= WM8900_REG_AUDIO1_BCLK_INV;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_RIGHT_J:
	हाल SND_SOC_DAIFMT_LEFT_J:
		चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
		हाल SND_SOC_DAIFMT_NB_NF:
			aअगर1 &= ~WM8900_REG_AUDIO1_BCLK_INV;
			aअगर1 &= ~WM8900_REG_AUDIO1_LRCLK_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_IF:
			aअगर1 |= WM8900_REG_AUDIO1_BCLK_INV;
			aअगर1 |= WM8900_REG_AUDIO1_LRCLK_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_IB_NF:
			aअगर1 |= WM8900_REG_AUDIO1_BCLK_INV;
			aअगर1 &= ~WM8900_REG_AUDIO1_LRCLK_INV;
			अवरोध;
		हाल SND_SOC_DAIFMT_NB_IF:
			aअगर1 &= ~WM8900_REG_AUDIO1_BCLK_INV;
			aअगर1 |= WM8900_REG_AUDIO1_LRCLK_INV;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8900_REG_CLOCKING1, घड़ीing1);
	snd_soc_component_ग_लिखो(component, WM8900_REG_AUDIO1, aअगर1);
	snd_soc_component_ग_लिखो(component, WM8900_REG_AUDIO3, aअगर3);
	snd_soc_component_ग_लिखो(component, WM8900_REG_AUDIO4, aअगर4);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8900_mute(काष्ठा snd_soc_dai *codec_dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 reg;

	reg = snd_soc_component_पढ़ो(component, WM8900_REG_DACCTRL);

	अगर (mute)
		reg |= WM8900_REG_DACCTRL_MUTE;
	अन्यथा
		reg &= ~WM8900_REG_DACCTRL_MUTE;

	snd_soc_component_ग_लिखो(component, WM8900_REG_DACCTRL, reg);

	वापस 0;
पूर्ण

#घोषणा WM8900_RATES (SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_11025 |\
		      SNDRV_PCM_RATE_16000 | SNDRV_PCM_RATE_22050 |\
		      SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000)

#घोषणा WM8900_PCM_FORMATS \
	(SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE | \
	 SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8900_dai_ops = अणु
	.hw_params	= wm8900_hw_params,
	.set_clkभाग	= wm8900_set_dai_clkभाग,
	.set_pll	= wm8900_set_dai_pll,
	.set_fmt	= wm8900_set_dai_fmt,
	.mute_stream	= wm8900_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8900_dai = अणु
	.name = "wm8900-hifi",
	.playback = अणु
		.stream_name = "HiFi Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8900_RATES,
		.क्रमmats = WM8900_PCM_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "HiFi Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8900_RATES,
		.क्रमmats = WM8900_PCM_FORMATS,
	 पूर्ण,
	.ops = &wm8900_dai_ops,
पूर्ण;

अटल पूर्णांक wm8900_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	u16 reg;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		/* Enable thermal shutकरोwn */
		snd_soc_component_update_bits(component, WM8900_REG_GPIO,
				    WM8900_REG_GPIO_TEMP_ENA,
				    WM8900_REG_GPIO_TEMP_ENA);
		snd_soc_component_update_bits(component, WM8900_REG_ADDCTL,
				    WM8900_REG_ADDCTL_TEMP_SD,
				    WM8900_REG_ADDCTL_TEMP_SD);
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		/* Charge capacitors अगर initial घातer up */
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			/* STARTUP_BIAS_ENA on */
			snd_soc_component_ग_लिखो(component, WM8900_REG_POWER1,
				     WM8900_REG_POWER1_STARTUP_BIAS_ENA);

			/* Startup bias mode */
			snd_soc_component_ग_लिखो(component, WM8900_REG_ADDCTL,
				     WM8900_REG_ADDCTL_BIAS_SRC |
				     WM8900_REG_ADDCTL_VMID_SOFTST);

			/* VMID 2x50k */
			snd_soc_component_ग_लिखो(component, WM8900_REG_POWER1,
				     WM8900_REG_POWER1_STARTUP_BIAS_ENA | 0x1);

			/* Allow capacitors to अक्षरge */
			schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(400));

			/* Enable bias */
			snd_soc_component_ग_लिखो(component, WM8900_REG_POWER1,
				     WM8900_REG_POWER1_STARTUP_BIAS_ENA |
				     WM8900_REG_POWER1_BIAS_ENA | 0x1);

			snd_soc_component_ग_लिखो(component, WM8900_REG_ADDCTL, 0);

			snd_soc_component_ग_लिखो(component, WM8900_REG_POWER1,
				     WM8900_REG_POWER1_BIAS_ENA | 0x1);
		पूर्ण

		reg = snd_soc_component_पढ़ो(component, WM8900_REG_POWER1);
		snd_soc_component_ग_लिखो(component, WM8900_REG_POWER1,
			     (reg & WM8900_REG_POWER1_FLL_ENA) |
			     WM8900_REG_POWER1_BIAS_ENA | 0x1);
		snd_soc_component_ग_लिखो(component, WM8900_REG_POWER2,
			     WM8900_REG_POWER2_SYSCLK_ENA);
		snd_soc_component_ग_लिखो(component, WM8900_REG_POWER3, 0);
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		/* Startup bias enable */
		reg = snd_soc_component_पढ़ो(component, WM8900_REG_POWER1);
		snd_soc_component_ग_लिखो(component, WM8900_REG_POWER1,
			     reg & WM8900_REG_POWER1_STARTUP_BIAS_ENA);
		snd_soc_component_ग_लिखो(component, WM8900_REG_ADDCTL,
			     WM8900_REG_ADDCTL_BIAS_SRC |
			     WM8900_REG_ADDCTL_VMID_SOFTST);

		/* Disअक्षरge caps */
		snd_soc_component_ग_लिखो(component, WM8900_REG_POWER1,
			     WM8900_REG_POWER1_STARTUP_BIAS_ENA);
		schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(500));

		/* Remove clamp */
		snd_soc_component_ग_लिखो(component, WM8900_REG_HPCTL1, 0);

		/* Power करोwn */
		snd_soc_component_ग_लिखो(component, WM8900_REG_ADDCTL, 0);
		snd_soc_component_ग_लिखो(component, WM8900_REG_POWER1, 0);
		snd_soc_component_ग_लिखो(component, WM8900_REG_POWER2, 0);
		snd_soc_component_ग_लिखो(component, WM8900_REG_POWER3, 0);

		/* Need to let things settle beक्रमe stopping the घड़ी
		 * to ensure that restart works, see "Stopping the
		 * master घड़ी" in the datasheet. */
		schedule_समयout_पूर्णांकerruptible(msecs_to_jअगरfies(1));
		snd_soc_component_ग_लिखो(component, WM8900_REG_POWER2,
			     WM8900_REG_POWER2_SYSCLK_ENA);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wm8900_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8900_priv *wm8900 = snd_soc_component_get_drvdata(component);
	पूर्णांक fll_out = wm8900->fll_out;
	पूर्णांक fll_in  = wm8900->fll_in;
	पूर्णांक ret;

	/* Stop the FLL in an orderly fashion */
	ret = wm8900_set_fll(component, 0, 0, 0);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to stop FLL\n");
		वापस ret;
	पूर्ण

	wm8900->fll_out = fll_out;
	wm8900->fll_in = fll_in;

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_OFF);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8900_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8900_priv *wm8900 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	wm8900_reset(component);

	ret = regcache_sync(wm8900->regmap);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to restore cache: %d\n", ret);
		वापस ret;
	पूर्ण

	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_STANDBY);

	/* Restart the FLL? */
	अगर (wm8900->fll_out) अणु
		पूर्णांक fll_out = wm8900->fll_out;
		पूर्णांक fll_in  = wm8900->fll_in;

		wm8900->fll_in = 0;
		wm8900->fll_out = 0;

		ret = wm8900_set_fll(component, 0, fll_in, fll_out);
		अगर (ret != 0) अणु
			dev_err(component->dev, "Failed to restart FLL\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm8900_probe(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक reg;

	reg = snd_soc_component_पढ़ो(component, WM8900_REG_ID);
	अगर (reg != 0x8900) अणु
		dev_err(component->dev, "Device is not a WM8900 - ID %x\n", reg);
		वापस -ENODEV;
	पूर्ण

	wm8900_reset(component);

	/* Turn the chip on */
	snd_soc_component_क्रमce_bias_level(component, SND_SOC_BIAS_STANDBY);

	/* Latch the volume update bits */
	snd_soc_component_update_bits(component, WM8900_REG_LINVOL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8900_REG_RINVOL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8900_REG_LOUT1CTL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8900_REG_ROUT1CTL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8900_REG_LOUT2CTL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8900_REG_ROUT2CTL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8900_REG_LDAC_DV, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8900_REG_RDAC_DV, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8900_REG_LADC_DV, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8900_REG_RADC_DV, 0x100, 0x100);

	/* Set the DAC and mixer output bias */
	snd_soc_component_ग_लिखो(component, WM8900_REG_OUTBIASCTL, 0x81);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8900 = अणु
	.probe			= wm8900_probe,
	.suspend		= wm8900_suspend,
	.resume			= wm8900_resume,
	.set_bias_level		= wm8900_set_bias_level,
	.controls		= wm8900_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8900_snd_controls),
	.dapm_widमाला_लो		= wm8900_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8900_dapm_widमाला_लो),
	.dapm_routes		= wm8900_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm8900_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config wm8900_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = WM8900_MAXREG,

	.reg_शेषs = wm8900_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8900_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,

	.अस्थिर_reg = wm8900_अस्थिर_रेजिस्टर,
पूर्ण;

#अगर defined(CONFIG_SPI_MASTER)
अटल पूर्णांक wm8900_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा wm8900_priv *wm8900;
	पूर्णांक ret;

	wm8900 = devm_kzalloc(&spi->dev, माप(काष्ठा wm8900_priv),
			      GFP_KERNEL);
	अगर (wm8900 == शून्य)
		वापस -ENOMEM;

	wm8900->regmap = devm_regmap_init_spi(spi, &wm8900_regmap);
	अगर (IS_ERR(wm8900->regmap))
		वापस PTR_ERR(wm8900->regmap);

	spi_set_drvdata(spi, wm8900);

	ret = devm_snd_soc_रेजिस्टर_component(&spi->dev,
			&soc_component_dev_wm8900, &wm8900_dai, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक wm8900_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा spi_driver wm8900_spi_driver = अणु
	.driver = अणु
		.name	= "wm8900",
	पूर्ण,
	.probe		= wm8900_spi_probe,
	.हटाओ		= wm8900_spi_हटाओ,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SPI_MASTER */

#अगर IS_ENABLED(CONFIG_I2C)
अटल पूर्णांक wm8900_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8900_priv *wm8900;
	पूर्णांक ret;

	wm8900 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8900_priv),
			      GFP_KERNEL);
	अगर (wm8900 == शून्य)
		वापस -ENOMEM;

	wm8900->regmap = devm_regmap_init_i2c(i2c, &wm8900_regmap);
	अगर (IS_ERR(wm8900->regmap))
		वापस PTR_ERR(wm8900->regmap);

	i2c_set_clientdata(i2c, wm8900);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_wm8900, &wm8900_dai, 1);

	वापस ret;
पूर्ण

अटल पूर्णांक wm8900_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8900_i2c_id[] = अणु
	अणु "wm8900", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8900_i2c_id);

अटल काष्ठा i2c_driver wm8900_i2c_driver = अणु
	.driver = अणु
		.name = "wm8900",
	पूर्ण,
	.probe =    wm8900_i2c_probe,
	.हटाओ =   wm8900_i2c_हटाओ,
	.id_table = wm8900_i2c_id,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init wm8900_modinit(व्योम)
अणु
	पूर्णांक ret = 0;
#अगर IS_ENABLED(CONFIG_I2C)
	ret = i2c_add_driver(&wm8900_i2c_driver);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to register wm8900 I2C driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	ret = spi_रेजिस्टर_driver(&wm8900_spi_driver);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to register wm8900 SPI driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
	वापस ret;
पूर्ण
module_init(wm8900_modinit);

अटल व्योम __निकास wm8900_निकास(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_I2C)
	i2c_del_driver(&wm8900_i2c_driver);
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	spi_unरेजिस्टर_driver(&wm8900_spi_driver);
#पूर्ण_अगर
पूर्ण
module_निकास(wm8900_निकास);

MODULE_DESCRIPTION("ASoC WM8900 driver");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfonmicro.com>");
MODULE_LICENSE("GPL");
