<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// DA7210 ALSA Soc codec driver
//
// Copyright (c) 2009 Dialog Semiconductor
// Written by David Chen <Dajun.chen@diasemi.com>
//
// Copyright (C) 2009 Renesas Solutions Corp.
// Cleanups by Kuninori Morimoto <morimoto.kuninori@renesas.com>
//
// Tested on SuperH Ecovec24 board with S16/S24 LE in 48KHz using I2S

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

/* DA7210 रेजिस्टर space */
#घोषणा DA7210_PAGE_CONTROL		0x00
#घोषणा DA7210_CONTROL			0x01
#घोषणा DA7210_STATUS			0x02
#घोषणा DA7210_STARTUP1			0x03
#घोषणा DA7210_STARTUP2			0x04
#घोषणा DA7210_STARTUP3			0x05
#घोषणा DA7210_MIC_L			0x07
#घोषणा DA7210_MIC_R			0x08
#घोषणा DA7210_AUX1_L			0x09
#घोषणा DA7210_AUX1_R			0x0A
#घोषणा DA7210_AUX2			0x0B
#घोषणा DA7210_IN_GAIN			0x0C
#घोषणा DA7210_INMIX_L			0x0D
#घोषणा DA7210_INMIX_R			0x0E
#घोषणा DA7210_ADC_HPF			0x0F
#घोषणा DA7210_ADC			0x10
#घोषणा DA7210_ADC_EQ1_2		0X11
#घोषणा DA7210_ADC_EQ3_4		0x12
#घोषणा DA7210_ADC_EQ5			0x13
#घोषणा DA7210_DAC_HPF			0x14
#घोषणा DA7210_DAC_L			0x15
#घोषणा DA7210_DAC_R			0x16
#घोषणा DA7210_DAC_SEL			0x17
#घोषणा DA7210_SOFTMUTE			0x18
#घोषणा DA7210_DAC_EQ1_2		0x19
#घोषणा DA7210_DAC_EQ3_4		0x1A
#घोषणा DA7210_DAC_EQ5			0x1B
#घोषणा DA7210_OUTMIX_L			0x1C
#घोषणा DA7210_OUTMIX_R			0x1D
#घोषणा DA7210_OUT1_L			0x1E
#घोषणा DA7210_OUT1_R			0x1F
#घोषणा DA7210_OUT2			0x20
#घोषणा DA7210_HP_L_VOL			0x21
#घोषणा DA7210_HP_R_VOL			0x22
#घोषणा DA7210_HP_CFG			0x23
#घोषणा DA7210_ZERO_CROSS		0x24
#घोषणा DA7210_DAI_SRC_SEL		0x25
#घोषणा DA7210_DAI_CFG1			0x26
#घोषणा DA7210_DAI_CFG3			0x28
#घोषणा DA7210_PLL_DIV1			0x29
#घोषणा DA7210_PLL_DIV2			0x2A
#घोषणा DA7210_PLL_DIV3			0x2B
#घोषणा DA7210_PLL			0x2C
#घोषणा DA7210_ALC_MAX			0x83
#घोषणा DA7210_ALC_MIN			0x84
#घोषणा DA7210_ALC_NOIS			0x85
#घोषणा DA7210_ALC_ATT			0x86
#घोषणा DA7210_ALC_REL			0x87
#घोषणा DA7210_ALC_DEL			0x88
#घोषणा DA7210_A_HID_UNLOCK		0x8A
#घोषणा DA7210_A_TEST_UNLOCK		0x8B
#घोषणा DA7210_A_PLL1			0x90
#घोषणा DA7210_A_CP_MODE		0xA7

/* STARTUP1 bit fields */
#घोषणा DA7210_SC_MST_EN		(1 << 0)

/* MIC_L bit fields */
#घोषणा DA7210_MICBIAS_EN		(1 << 6)
#घोषणा DA7210_MIC_L_EN			(1 << 7)

/* MIC_R bit fields */
#घोषणा DA7210_MIC_R_EN			(1 << 7)

/* INMIX_L bit fields */
#घोषणा DA7210_IN_L_EN			(1 << 7)

/* INMIX_R bit fields */
#घोषणा DA7210_IN_R_EN			(1 << 7)

/* ADC bit fields */
#घोषणा DA7210_ADC_ALC_EN		(1 << 0)
#घोषणा DA7210_ADC_L_EN			(1 << 3)
#घोषणा DA7210_ADC_R_EN			(1 << 7)

/* DAC/ADC HPF fields */
#घोषणा DA7210_VOICE_F0_MASK		(0x7 << 4)
#घोषणा DA7210_VOICE_F0_25		(1 << 4)
#घोषणा DA7210_VOICE_EN			(1 << 7)

/* DAC_SEL bit fields */
#घोषणा DA7210_DAC_L_SRC_DAI_L		(4 << 0)
#घोषणा DA7210_DAC_L_EN			(1 << 3)
#घोषणा DA7210_DAC_R_SRC_DAI_R		(5 << 4)
#घोषणा DA7210_DAC_R_EN			(1 << 7)

/* OUTMIX_L bit fields */
#घोषणा DA7210_OUT_L_EN			(1 << 7)

/* OUTMIX_R bit fields */
#घोषणा DA7210_OUT_R_EN			(1 << 7)

/* HP_CFG bit fields */
#घोषणा DA7210_HP_2CAP_MODE		(1 << 1)
#घोषणा DA7210_HP_SENSE_EN		(1 << 2)
#घोषणा DA7210_HP_L_EN			(1 << 3)
#घोषणा DA7210_HP_MODE			(1 << 6)
#घोषणा DA7210_HP_R_EN			(1 << 7)

/* DAI_SRC_SEL bit fields */
#घोषणा DA7210_DAI_OUT_L_SRC		(6 << 0)
#घोषणा DA7210_DAI_OUT_R_SRC		(7 << 4)

/* DAI_CFG1 bit fields */
#घोषणा DA7210_DAI_WORD_S16_LE		(0 << 0)
#घोषणा DA7210_DAI_WORD_S20_3LE		(1 << 0)
#घोषणा DA7210_DAI_WORD_S24_LE		(2 << 0)
#घोषणा DA7210_DAI_WORD_S32_LE		(3 << 0)
#घोषणा DA7210_DAI_FLEN_64BIT		(1 << 2)
#घोषणा DA7210_DAI_MODE_SLAVE		(0 << 7)
#घोषणा DA7210_DAI_MODE_MASTER		(1 << 7)

/* DAI_CFG3 bit fields */
#घोषणा DA7210_DAI_FORMAT_I2SMODE	(0 << 0)
#घोषणा DA7210_DAI_FORMAT_LEFT_J	(1 << 0)
#घोषणा DA7210_DAI_FORMAT_RIGHT_J	(2 << 0)
#घोषणा DA7210_DAI_OE			(1 << 3)
#घोषणा DA7210_DAI_EN			(1 << 7)

/*PLL_DIV3 bit fields */
#घोषणा DA7210_PLL_DIV_L_MASK		(0xF << 0)
#घोषणा DA7210_MCLK_RANGE_10_20_MHZ	(1 << 4)
#घोषणा DA7210_PLL_BYP			(1 << 6)

/* PLL bit fields */
#घोषणा DA7210_PLL_FS_MASK		(0xF << 0)
#घोषणा DA7210_PLL_FS_8000		(0x1 << 0)
#घोषणा DA7210_PLL_FS_11025		(0x2 << 0)
#घोषणा DA7210_PLL_FS_12000		(0x3 << 0)
#घोषणा DA7210_PLL_FS_16000		(0x5 << 0)
#घोषणा DA7210_PLL_FS_22050		(0x6 << 0)
#घोषणा DA7210_PLL_FS_24000		(0x7 << 0)
#घोषणा DA7210_PLL_FS_32000		(0x9 << 0)
#घोषणा DA7210_PLL_FS_44100		(0xA << 0)
#घोषणा DA7210_PLL_FS_48000		(0xB << 0)
#घोषणा DA7210_PLL_FS_88200		(0xE << 0)
#घोषणा DA7210_PLL_FS_96000		(0xF << 0)
#घोषणा DA7210_MCLK_DET_EN		(0x1 << 5)
#घोषणा DA7210_MCLK_SRM_EN		(0x1 << 6)
#घोषणा DA7210_PLL_EN			(0x1 << 7)

/* SOFTMUTE bit fields */
#घोषणा DA7210_RAMP_EN			(1 << 6)

/* CONTROL bit fields */
#घोषणा DA7210_REG_EN			(1 << 0)
#घोषणा DA7210_BIAS_EN			(1 << 2)
#घोषणा DA7210_NOISE_SUP_EN		(1 << 3)

/* IN_GAIN bit fields */
#घोषणा DA7210_INPGA_L_VOL		(0x0F << 0)
#घोषणा DA7210_INPGA_R_VOL		(0xF0 << 0)

/* ZERO_CROSS bit fields */
#घोषणा DA7210_AUX1_L_ZC		(1 << 0)
#घोषणा DA7210_AUX1_R_ZC		(1 << 1)
#घोषणा DA7210_HP_L_ZC			(1 << 6)
#घोषणा DA7210_HP_R_ZC			(1 << 7)

/* AUX1_L bit fields */
#घोषणा DA7210_AUX1_L_VOL		(0x3F << 0)
#घोषणा DA7210_AUX1_L_EN		(1 << 7)

/* AUX1_R bit fields */
#घोषणा DA7210_AUX1_R_VOL		(0x3F << 0)
#घोषणा DA7210_AUX1_R_EN		(1 << 7)

/* AUX2 bit fields */
#घोषणा DA7210_AUX2_EN			(1 << 3)

/* Minimum INPGA and AUX1 volume to enable noise suppression */
#घोषणा DA7210_INPGA_MIN_VOL_NS		0x0A  /* 10.5dB */
#घोषणा DA7210_AUX1_MIN_VOL_NS		0x35  /* 6dB */

/* OUT1_L bit fields */
#घोषणा DA7210_OUT1_L_EN		(1 << 7)

/* OUT1_R bit fields */
#घोषणा DA7210_OUT1_R_EN		(1 << 7)

/* OUT2 bit fields */
#घोषणा DA7210_OUT2_OUTMIX_R		(1 << 5)
#घोषणा DA7210_OUT2_OUTMIX_L		(1 << 6)
#घोषणा DA7210_OUT2_EN			(1 << 7)

काष्ठा pll_भाग अणु
	पूर्णांक fref;
	पूर्णांक fout;
	u8 भाग1;
	u8 भाग2;
	u8 भाग3;
	u8 mode;	/* 0 = slave, 1 = master */
पूर्ण;

/* PLL भागiders table */
अटल स्थिर काष्ठा pll_भाग da7210_pll_भाग[] = अणु
	/* क्रम MASTER mode, fs = 44.1Khz */
	अणु 12000000, 2822400, 0xE8, 0x6C, 0x2, 1पूर्ण,	/* MCLK=12Mhz */
	अणु 13000000, 2822400, 0xDF, 0x28, 0xC, 1पूर्ण,	/* MCLK=13Mhz */
	अणु 13500000, 2822400, 0xDB, 0x0A, 0xD, 1पूर्ण,	/* MCLK=13.5Mhz */
	अणु 14400000, 2822400, 0xD4, 0x5A, 0x2, 1पूर्ण,	/* MCLK=14.4Mhz */
	अणु 19200000, 2822400, 0xBB, 0x43, 0x9, 1पूर्ण,	/* MCLK=19.2Mhz */
	अणु 19680000, 2822400, 0xB9, 0x6D, 0xA, 1पूर्ण,	/* MCLK=19.68Mhz */
	अणु 19800000, 2822400, 0xB8, 0xFB, 0xB, 1पूर्ण,	/* MCLK=19.8Mhz */
	/* क्रम MASTER mode, fs = 48Khz */
	अणु 12000000, 3072000, 0xF3, 0x12, 0x7, 1पूर्ण,	/* MCLK=12Mhz */
	अणु 13000000, 3072000, 0xE8, 0xFD, 0x5, 1पूर्ण,	/* MCLK=13Mhz */
	अणु 13500000, 3072000, 0xE4, 0x82, 0x3, 1पूर्ण,	/* MCLK=13.5Mhz */
	अणु 14400000, 3072000, 0xDD, 0x3A, 0x0, 1पूर्ण,	/* MCLK=14.4Mhz */
	अणु 19200000, 3072000, 0xC1, 0xEB, 0x8, 1पूर्ण,	/* MCLK=19.2Mhz */
	अणु 19680000, 3072000, 0xBF, 0xEC, 0x0, 1पूर्ण,	/* MCLK=19.68Mhz */
	अणु 19800000, 3072000, 0xBF, 0x70, 0x0, 1पूर्ण,	/* MCLK=19.8Mhz */
	/* क्रम SLAVE mode with SRM */
	अणु 12000000, 2822400, 0xED, 0xBF, 0x5, 0पूर्ण,	/* MCLK=12Mhz */
	अणु 13000000, 2822400, 0xE4, 0x13, 0x0, 0पूर्ण,	/* MCLK=13Mhz */
	अणु 13500000, 2822400, 0xDF, 0xC6, 0x8, 0पूर्ण,	/* MCLK=13.5Mhz */
	अणु 14400000, 2822400, 0xD8, 0xCA, 0x1, 0पूर्ण,	/* MCLK=14.4Mhz */
	अणु 19200000, 2822400, 0xBE, 0x97, 0x9, 0पूर्ण,	/* MCLK=19.2Mhz */
	अणु 19680000, 2822400, 0xBC, 0xAC, 0xD, 0पूर्ण,	/* MCLK=19.68Mhz */
	अणु 19800000, 2822400, 0xBC, 0x35, 0xE, 0पूर्ण,	/* MCLK=19.8Mhz  */
पूर्ण;

क्रमागत clk_src अणु
	DA7210_CLKSRC_MCLK
पूर्ण;

#घोषणा DA7210_VERSION "0.0.1"

/*
 * Playback Volume
 *
 * max		: 0x3F (+15.0 dB)
 *		   (1.5 dB step)
 * min		: 0x11 (-54.0 dB)
 * mute		: 0x10
 * reserved	: 0x00 - 0x0F
 *
 * Reserved area are considered as "mute".
 */
अटल स्थिर DECLARE_TLV_DB_RANGE(hp_out_tlv,
	0x0, 0x10, TLV_DB_SCALE_ITEM(TLV_DB_GAIN_MUTE, 0, 1),
	/* -54 dB to +15 dB */
	0x11, 0x3f, TLV_DB_SCALE_ITEM(-5400, 150, 0)
);

अटल स्थिर DECLARE_TLV_DB_RANGE(lineout_vol_tlv,
	0x0, 0x10, TLV_DB_SCALE_ITEM(TLV_DB_GAIN_MUTE, 0, 1),
	/* -54dB to 15dB */
	0x11, 0x3f, TLV_DB_SCALE_ITEM(-5400, 150, 0)
);

अटल स्थिर DECLARE_TLV_DB_RANGE(mono_vol_tlv,
	0x0, 0x2, TLV_DB_SCALE_ITEM(-1800, 0, 1),
	/* -18dB to 6dB */
	0x3, 0x7, TLV_DB_SCALE_ITEM(-1800, 600, 0)
);

अटल स्थिर DECLARE_TLV_DB_RANGE(aux1_vol_tlv,
	0x0, 0x10, TLV_DB_SCALE_ITEM(TLV_DB_GAIN_MUTE, 0, 1),
	/* -48dB to 21dB */
	0x11, 0x3f, TLV_DB_SCALE_ITEM(-4800, 150, 0)
);

अटल स्थिर DECLARE_TLV_DB_SCALE(eq_gain_tlv, -1050, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_eq_master_gain_tlv, -1800, 600, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(dac_gain_tlv, -7725, 75, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(mic_vol_tlv, -600, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(aux2_vol_tlv, -600, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(inpga_gain_tlv, -450, 150, 0);

/* ADC and DAC high pass filter f0 value */
अटल स्थिर अक्षर * स्थिर da7210_hpf_cutoff_txt[] = अणु
	"Fs/8192*pi", "Fs/4096*pi", "Fs/2048*pi", "Fs/1024*pi"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da7210_dac_hpf_cutoff,
			    DA7210_DAC_HPF, 0, da7210_hpf_cutoff_txt);

अटल SOC_ENUM_SINGLE_DECL(da7210_adc_hpf_cutoff,
			    DA7210_ADC_HPF, 0, da7210_hpf_cutoff_txt);

/* ADC and DAC voice (8kHz) high pass cutoff value */
अटल स्थिर अक्षर * स्थिर da7210_vf_cutoff_txt[] = अणु
	"2.5Hz", "25Hz", "50Hz", "100Hz", "150Hz", "200Hz", "300Hz", "400Hz"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da7210_dac_vf_cutoff,
			    DA7210_DAC_HPF, 4, da7210_vf_cutoff_txt);

अटल SOC_ENUM_SINGLE_DECL(da7210_adc_vf_cutoff,
			    DA7210_ADC_HPF, 4, da7210_vf_cutoff_txt);

अटल स्थिर अक्षर *da7210_hp_mode_txt[] = अणु
	"Class H", "Class G"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da7210_hp_mode_sel,
			    DA7210_HP_CFG, 0, da7210_hp_mode_txt);

/* ALC can be enabled only अगर noise suppression is disabled */
अटल पूर्णांक da7210_put_alc_sw(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);

	अगर (ucontrol->value.पूर्णांकeger.value[0]) अणु
		/* Check अगर noise suppression is enabled */
		अगर (snd_soc_component_पढ़ो(component, DA7210_CONTROL) & DA7210_NOISE_SUP_EN) अणु
			dev_dbg(component->dev,
				"Disable noise suppression to enable ALC\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	/* If all conditions are met or we are actually disabling ALC */
	वापस snd_soc_put_volsw(kcontrol, ucontrol);
पूर्ण

/* Noise suppression can be enabled only अगर following conditions are met
 *  ALC disabled
 *  ZC enabled क्रम HP and AUX1 PGA
 *  INPGA_L_VOL and INPGA_R_VOL >= 10.5 dB
 *  AUX1_L_VOL and AUX1_R_VOL >= 6 dB
 */
अटल पूर्णांक da7210_put_noise_sup_sw(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	u8 val;

	अगर (ucontrol->value.पूर्णांकeger.value[0]) अणु
		/* Check अगर ALC is enabled */
		अगर (snd_soc_component_पढ़ो(component, DA7210_ADC) & DA7210_ADC_ALC_EN)
			जाओ err;

		/* Check ZC क्रम HP and AUX1 PGA */
		अगर ((snd_soc_component_पढ़ो(component, DA7210_ZERO_CROSS) &
			(DA7210_AUX1_L_ZC | DA7210_AUX1_R_ZC | DA7210_HP_L_ZC |
			DA7210_HP_R_ZC)) != (DA7210_AUX1_L_ZC |
			DA7210_AUX1_R_ZC | DA7210_HP_L_ZC | DA7210_HP_R_ZC))
			जाओ err;

		/* Check INPGA_L_VOL and INPGA_R_VOL */
		val = snd_soc_component_पढ़ो(component, DA7210_IN_GAIN);
		अगर (((val & DA7210_INPGA_L_VOL) < DA7210_INPGA_MIN_VOL_NS) ||
			(((val & DA7210_INPGA_R_VOL) >> 4) <
			DA7210_INPGA_MIN_VOL_NS))
			जाओ err;

		/* Check AUX1_L_VOL and AUX1_R_VOL */
		अगर (((snd_soc_component_पढ़ो(component, DA7210_AUX1_L) & DA7210_AUX1_L_VOL) <
		    DA7210_AUX1_MIN_VOL_NS) ||
		    ((snd_soc_component_पढ़ो(component, DA7210_AUX1_R) & DA7210_AUX1_R_VOL) <
		    DA7210_AUX1_MIN_VOL_NS))
			जाओ err;
	पूर्ण
	/* If all conditions are met or we are actually disabling Noise sup */
	वापस snd_soc_put_volsw(kcontrol, ucontrol);

err:
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new da7210_snd_controls[] = अणु

	SOC_DOUBLE_R_TLV("HeadPhone Playback Volume",
			 DA7210_HP_L_VOL, DA7210_HP_R_VOL,
			 0, 0x3F, 0, hp_out_tlv),
	SOC_DOUBLE_R_TLV("Digital Playback Volume",
			 DA7210_DAC_L, DA7210_DAC_R,
			 0, 0x77, 1, dac_gain_tlv),
	SOC_DOUBLE_R_TLV("Lineout Playback Volume",
			 DA7210_OUT1_L, DA7210_OUT1_R,
			 0, 0x3f, 0, lineout_vol_tlv),
	SOC_SINGLE_TLV("Mono Playback Volume", DA7210_OUT2, 0, 0x7, 0,
		       mono_vol_tlv),

	SOC_DOUBLE_R_TLV("Mic Capture Volume",
			 DA7210_MIC_L, DA7210_MIC_R,
			 0, 0x5, 0, mic_vol_tlv),
	SOC_DOUBLE_R_TLV("Aux1 Capture Volume",
			 DA7210_AUX1_L, DA7210_AUX1_R,
			 0, 0x3f, 0, aux1_vol_tlv),
	SOC_SINGLE_TLV("Aux2 Capture Volume", DA7210_AUX2, 0, 0x3, 0,
		       aux2_vol_tlv),
	SOC_DOUBLE_TLV("In PGA Capture Volume", DA7210_IN_GAIN, 0, 4, 0xF, 0,
		       inpga_gain_tlv),

	/* DAC Equalizer  controls */
	SOC_SINGLE("DAC EQ Switch", DA7210_DAC_EQ5, 7, 1, 0),
	SOC_SINGLE_TLV("DAC EQ1 Volume", DA7210_DAC_EQ1_2, 0, 0xf, 1,
		       eq_gain_tlv),
	SOC_SINGLE_TLV("DAC EQ2 Volume", DA7210_DAC_EQ1_2, 4, 0xf, 1,
		       eq_gain_tlv),
	SOC_SINGLE_TLV("DAC EQ3 Volume", DA7210_DAC_EQ3_4, 0, 0xf, 1,
		       eq_gain_tlv),
	SOC_SINGLE_TLV("DAC EQ4 Volume", DA7210_DAC_EQ3_4, 4, 0xf, 1,
		       eq_gain_tlv),
	SOC_SINGLE_TLV("DAC EQ5 Volume", DA7210_DAC_EQ5, 0, 0xf, 1,
		       eq_gain_tlv),

	/* ADC Equalizer  controls */
	SOC_SINGLE("ADC EQ Switch", DA7210_ADC_EQ5, 7, 1, 0),
	SOC_SINGLE_TLV("ADC EQ Master Volume", DA7210_ADC_EQ5, 4, 0x3,
		       1, adc_eq_master_gain_tlv),
	SOC_SINGLE_TLV("ADC EQ1 Volume", DA7210_ADC_EQ1_2, 0, 0xf, 1,
		       eq_gain_tlv),
	SOC_SINGLE_TLV("ADC EQ2 Volume", DA7210_ADC_EQ1_2, 4, 0xf, 1,
		       eq_gain_tlv),
	SOC_SINGLE_TLV("ADC EQ3 Volume", DA7210_ADC_EQ3_4, 0, 0xf, 1,
		       eq_gain_tlv),
	SOC_SINGLE_TLV("ADC EQ4 Volume", DA7210_ADC_EQ3_4, 4, 0xf, 1,
		       eq_gain_tlv),
	SOC_SINGLE_TLV("ADC EQ5 Volume", DA7210_ADC_EQ5, 0, 0xf, 1,
		       eq_gain_tlv),

	SOC_SINGLE("DAC HPF Switch", DA7210_DAC_HPF, 3, 1, 0),
	SOC_ENUM("DAC HPF Cutoff", da7210_dac_hpf_cutoff),
	SOC_SINGLE("DAC Voice Mode Switch", DA7210_DAC_HPF, 7, 1, 0),
	SOC_ENUM("DAC Voice Cutoff", da7210_dac_vf_cutoff),

	SOC_SINGLE("ADC HPF Switch", DA7210_ADC_HPF, 3, 1, 0),
	SOC_ENUM("ADC HPF Cutoff", da7210_adc_hpf_cutoff),
	SOC_SINGLE("ADC Voice Mode Switch", DA7210_ADC_HPF, 7, 1, 0),
	SOC_ENUM("ADC Voice Cutoff", da7210_adc_vf_cutoff),

	/* Mute controls */
	SOC_DOUBLE_R("Mic Capture Switch", DA7210_MIC_L, DA7210_MIC_R, 3, 1, 0),
	SOC_SINGLE("Aux2 Capture Switch", DA7210_AUX2, 2, 1, 0),
	SOC_DOUBLE("ADC Capture Switch", DA7210_ADC, 2, 6, 1, 0),
	SOC_SINGLE("Digital Soft Mute Switch", DA7210_SOFTMUTE, 7, 1, 0),
	SOC_SINGLE("Digital Soft Mute Rate", DA7210_SOFTMUTE, 0, 0x7, 0),

	/* Zero cross controls */
	SOC_DOUBLE("Aux1 ZC Switch", DA7210_ZERO_CROSS, 0, 1, 1, 0),
	SOC_DOUBLE("In PGA ZC Switch", DA7210_ZERO_CROSS, 2, 3, 1, 0),
	SOC_DOUBLE("Lineout ZC Switch", DA7210_ZERO_CROSS, 4, 5, 1, 0),
	SOC_DOUBLE("Headphone ZC Switch", DA7210_ZERO_CROSS, 6, 7, 1, 0),

	SOC_ENUM("Headphone Class", da7210_hp_mode_sel),

	/* ALC controls */
	SOC_SINGLE_EXT("ALC Enable Switch", DA7210_ADC, 0, 1, 0,
		       snd_soc_get_volsw, da7210_put_alc_sw),
	SOC_SINGLE("ALC Capture Max Volume", DA7210_ALC_MAX, 0, 0x3F, 0),
	SOC_SINGLE("ALC Capture Min Volume", DA7210_ALC_MIN, 0, 0x3F, 0),
	SOC_SINGLE("ALC Capture Noise Volume", DA7210_ALC_NOIS, 0, 0x3F, 0),
	SOC_SINGLE("ALC Capture Attack Rate", DA7210_ALC_ATT, 0, 0xFF, 0),
	SOC_SINGLE("ALC Capture Release Rate", DA7210_ALC_REL, 0, 0xFF, 0),
	SOC_SINGLE("ALC Capture Release Delay", DA7210_ALC_DEL, 0, 0xFF, 0),

	SOC_SINGLE_EXT("Noise Suppression Enable Switch", DA7210_CONTROL, 3, 1,
		       0, snd_soc_get_volsw, da7210_put_noise_sup_sw),
पूर्ण;

/*
 * DAPM Controls
 *
 * Current DAPM implementation covers almost all codec components e.g. IOs,
 * mixers, PGAs,ADC and DAC.
 */
/* In Mixer Left */
अटल स्थिर काष्ठा snd_kcontrol_new da7210_dapm_inmixl_controls[] = अणु
	SOC_DAPM_SINGLE("Mic Left Switch", DA7210_INMIX_L, 0, 1, 0),
	SOC_DAPM_SINGLE("Mic Right Switch", DA7210_INMIX_L, 1, 1, 0),
	SOC_DAPM_SINGLE("Aux1 Left Switch", DA7210_INMIX_L, 2, 1, 0),
	SOC_DAPM_SINGLE("Aux2 Switch", DA7210_INMIX_L, 3, 1, 0),
	SOC_DAPM_SINGLE("Outmix Left Switch", DA7210_INMIX_L, 4, 1, 0),
पूर्ण;

/* In Mixer Right */
अटल स्थिर काष्ठा snd_kcontrol_new da7210_dapm_inmixr_controls[] = अणु
	SOC_DAPM_SINGLE("Mic Right Switch", DA7210_INMIX_R, 0, 1, 0),
	SOC_DAPM_SINGLE("Mic Left Switch", DA7210_INMIX_R, 1, 1, 0),
	SOC_DAPM_SINGLE("Aux1 Right Switch", DA7210_INMIX_R, 2, 1, 0),
	SOC_DAPM_SINGLE("Aux2 Switch", DA7210_INMIX_R, 3, 1, 0),
	SOC_DAPM_SINGLE("Outmix Right Switch", DA7210_INMIX_R, 4, 1, 0),
पूर्ण;

/* Out Mixer Left */
अटल स्थिर काष्ठा snd_kcontrol_new da7210_dapm_ouपंचांगixl_controls[] = अणु
	SOC_DAPM_SINGLE("Aux1 Left Switch", DA7210_OUTMIX_L, 0, 1, 0),
	SOC_DAPM_SINGLE("Aux2 Switch", DA7210_OUTMIX_L, 1, 1, 0),
	SOC_DAPM_SINGLE("INPGA Left Switch", DA7210_OUTMIX_L, 2, 1, 0),
	SOC_DAPM_SINGLE("INPGA Right Switch", DA7210_OUTMIX_L, 3, 1, 0),
	SOC_DAPM_SINGLE("DAC Left Switch", DA7210_OUTMIX_L, 4, 1, 0),
पूर्ण;

/* Out Mixer Right */
अटल स्थिर काष्ठा snd_kcontrol_new da7210_dapm_ouपंचांगixr_controls[] = अणु
	SOC_DAPM_SINGLE("Aux1 Right Switch", DA7210_OUTMIX_R, 0, 1, 0),
	SOC_DAPM_SINGLE("Aux2 Switch", DA7210_OUTMIX_R, 1, 1, 0),
	SOC_DAPM_SINGLE("INPGA Left Switch", DA7210_OUTMIX_R, 2, 1, 0),
	SOC_DAPM_SINGLE("INPGA Right Switch", DA7210_OUTMIX_R, 3, 1, 0),
	SOC_DAPM_SINGLE("DAC Right Switch", DA7210_OUTMIX_R, 4, 1, 0),
पूर्ण;

/* Mono Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new da7210_dapm_monomix_controls[] = अणु
	SOC_DAPM_SINGLE("INPGA Right Switch", DA7210_OUT2, 3, 1, 0),
	SOC_DAPM_SINGLE("INPGA Left Switch", DA7210_OUT2, 4, 1, 0),
	SOC_DAPM_SINGLE("Outmix Right Switch", DA7210_OUT2, 5, 1, 0),
	SOC_DAPM_SINGLE("Outmix Left Switch", DA7210_OUT2, 6, 1, 0),
पूर्ण;

/* DAPM widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget da7210_dapm_widमाला_लो[] = अणु
	/* Input Side */
	/* Input Lines */
	SND_SOC_DAPM_INPUT("MICL"),
	SND_SOC_DAPM_INPUT("MICR"),
	SND_SOC_DAPM_INPUT("AUX1L"),
	SND_SOC_DAPM_INPUT("AUX1R"),
	SND_SOC_DAPM_INPUT("AUX2"),

	/* Input PGAs */
	SND_SOC_DAPM_PGA("Mic Left", DA7210_STARTUP3, 0, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("Mic Right", DA7210_STARTUP3, 1, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("Aux1 Left", DA7210_STARTUP3, 2, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("Aux1 Right", DA7210_STARTUP3, 3, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("Aux2 Mono", DA7210_STARTUP3, 4, 1, शून्य, 0),

	SND_SOC_DAPM_PGA("INPGA Left", DA7210_INMIX_L, 7, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("INPGA Right", DA7210_INMIX_R, 7, 0, शून्य, 0),

	/* MICBIAS */
	SND_SOC_DAPM_SUPPLY("Mic Bias", DA7210_MIC_L, 6, 0, शून्य, 0),

	/* Input Mixers */
	SND_SOC_DAPM_MIXER("In Mixer Left", SND_SOC_NOPM, 0, 0,
		&da7210_dapm_inmixl_controls[0],
		ARRAY_SIZE(da7210_dapm_inmixl_controls)),

	SND_SOC_DAPM_MIXER("In Mixer Right", SND_SOC_NOPM, 0, 0,
		&da7210_dapm_inmixr_controls[0],
		ARRAY_SIZE(da7210_dapm_inmixr_controls)),

	/* ADCs */
	SND_SOC_DAPM_ADC("ADC Left", "Capture", DA7210_STARTUP3, 5, 1),
	SND_SOC_DAPM_ADC("ADC Right", "Capture", DA7210_STARTUP3, 6, 1),

	/* Output Side */
	/* DACs */
	SND_SOC_DAPM_DAC("DAC Left", "Playback", DA7210_STARTUP2, 5, 1),
	SND_SOC_DAPM_DAC("DAC Right", "Playback", DA7210_STARTUP2, 6, 1),

	/* Output Mixers */
	SND_SOC_DAPM_MIXER("Out Mixer Left", SND_SOC_NOPM, 0, 0,
		&da7210_dapm_ouपंचांगixl_controls[0],
		ARRAY_SIZE(da7210_dapm_ouपंचांगixl_controls)),

	SND_SOC_DAPM_MIXER("Out Mixer Right", SND_SOC_NOPM, 0, 0,
		&da7210_dapm_ouपंचांगixr_controls[0],
		ARRAY_SIZE(da7210_dapm_ouपंचांगixr_controls)),

	SND_SOC_DAPM_MIXER("Mono Mixer", SND_SOC_NOPM, 0, 0,
		&da7210_dapm_monomix_controls[0],
		ARRAY_SIZE(da7210_dapm_monomix_controls)),

	/* Output PGAs */
	SND_SOC_DAPM_PGA("OUTPGA Left Enable", DA7210_OUTMIX_L, 7, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("OUTPGA Right Enable", DA7210_OUTMIX_R, 7, 0, शून्य, 0),

	SND_SOC_DAPM_PGA("Out1 Left", DA7210_STARTUP2, 0, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("Out1 Right", DA7210_STARTUP2, 1, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("Out2 Mono", DA7210_STARTUP2, 2, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("Headphone Left", DA7210_STARTUP2, 3, 1, शून्य, 0),
	SND_SOC_DAPM_PGA("Headphone Right", DA7210_STARTUP2, 4, 1, शून्य, 0),

	/* Output Lines */
	SND_SOC_DAPM_OUTPUT("OUT1L"),
	SND_SOC_DAPM_OUTPUT("OUT1R"),
	SND_SOC_DAPM_OUTPUT("HPL"),
	SND_SOC_DAPM_OUTPUT("HPR"),
	SND_SOC_DAPM_OUTPUT("OUT2"),
पूर्ण;

/* DAPM audio route definition */
अटल स्थिर काष्ठा snd_soc_dapm_route da7210_audio_map[] = अणु
	/* Dest       Connecting Widget    source */
	/* Input path */
	अणु"Mic Left", शून्य, "MICL"पूर्ण,
	अणु"Mic Right", शून्य, "MICR"पूर्ण,
	अणु"Aux1 Left", शून्य, "AUX1L"पूर्ण,
	अणु"Aux1 Right", शून्य, "AUX1R"पूर्ण,
	अणु"Aux2 Mono", शून्य, "AUX2"पूर्ण,

	अणु"In Mixer Left", "Mic Left Switch", "Mic Left"पूर्ण,
	अणु"In Mixer Left", "Mic Right Switch", "Mic Right"पूर्ण,
	अणु"In Mixer Left", "Aux1 Left Switch", "Aux1 Left"पूर्ण,
	अणु"In Mixer Left", "Aux2 Switch", "Aux2 Mono"पूर्ण,
	अणु"In Mixer Left", "Outmix Left Switch", "Out Mixer Left"पूर्ण,

	अणु"In Mixer Right", "Mic Right Switch", "Mic Right"पूर्ण,
	अणु"In Mixer Right", "Mic Left Switch", "Mic Left"पूर्ण,
	अणु"In Mixer Right", "Aux1 Right Switch", "Aux1 Right"पूर्ण,
	अणु"In Mixer Right", "Aux2 Switch", "Aux2 Mono"पूर्ण,
	अणु"In Mixer Right", "Outmix Right Switch", "Out Mixer Right"पूर्ण,

	अणु"INPGA Left", शून्य, "In Mixer Left"पूर्ण,
	अणु"ADC Left", शून्य, "INPGA Left"पूर्ण,

	अणु"INPGA Right", शून्य, "In Mixer Right"पूर्ण,
	अणु"ADC Right", शून्य, "INPGA Right"पूर्ण,

	/* Output path */
	अणु"Out Mixer Left", "Aux1 Left Switch", "Aux1 Left"पूर्ण,
	अणु"Out Mixer Left", "Aux2 Switch", "Aux2 Mono"पूर्ण,
	अणु"Out Mixer Left", "INPGA Left Switch", "INPGA Left"पूर्ण,
	अणु"Out Mixer Left", "INPGA Right Switch", "INPGA Right"पूर्ण,
	अणु"Out Mixer Left", "DAC Left Switch", "DAC Left"पूर्ण,

	अणु"Out Mixer Right", "Aux1 Right Switch", "Aux1 Right"पूर्ण,
	अणु"Out Mixer Right", "Aux2 Switch", "Aux2 Mono"पूर्ण,
	अणु"Out Mixer Right", "INPGA Right Switch", "INPGA Right"पूर्ण,
	अणु"Out Mixer Right", "INPGA Left Switch", "INPGA Left"पूर्ण,
	अणु"Out Mixer Right", "DAC Right Switch", "DAC Right"पूर्ण,

	अणु"Mono Mixer", "INPGA Right Switch", "INPGA Right"पूर्ण,
	अणु"Mono Mixer", "INPGA Left Switch", "INPGA Left"पूर्ण,
	अणु"Mono Mixer", "Outmix Right Switch", "Out Mixer Right"पूर्ण,
	अणु"Mono Mixer", "Outmix Left Switch", "Out Mixer Left"पूर्ण,

	अणु"OUTPGA Left Enable", शून्य, "Out Mixer Left"पूर्ण,
	अणु"OUTPGA Right Enable", शून्य, "Out Mixer Right"पूर्ण,

	अणु"Out1 Left", शून्य, "OUTPGA Left Enable"पूर्ण,
	अणु"OUT1L", शून्य, "Out1 Left"पूर्ण,

	अणु"Out1 Right", शून्य, "OUTPGA Right Enable"पूर्ण,
	अणु"OUT1R", शून्य, "Out1 Right"पूर्ण,

	अणु"Headphone Left", शून्य, "OUTPGA Left Enable"पूर्ण,
	अणु"HPL", शून्य, "Headphone Left"पूर्ण,

	अणु"Headphone Right", शून्य, "OUTPGA Right Enable"पूर्ण,
	अणु"HPR", शून्य, "Headphone Right"पूर्ण,

	अणु"Out2 Mono", शून्य, "Mono Mixer"पूर्ण,
	अणु"OUT2", शून्य, "Out2 Mono"पूर्ण,
पूर्ण;

/* Codec निजी data */
काष्ठा da7210_priv अणु
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक mclk_rate;
	पूर्णांक master;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष da7210_reg_शेषs[] = अणु
	अणु 0x00, 0x00 पूर्ण,
	अणु 0x01, 0x11 पूर्ण,
	अणु 0x03, 0x00 पूर्ण,
	अणु 0x04, 0x00 पूर्ण,
	अणु 0x05, 0x00 पूर्ण,
	अणु 0x06, 0x00 पूर्ण,
	अणु 0x07, 0x00 पूर्ण,
	अणु 0x08, 0x00 पूर्ण,
	अणु 0x09, 0x00 पूर्ण,
	अणु 0x0a, 0x00 पूर्ण,
	अणु 0x0b, 0x00 पूर्ण,
	अणु 0x0c, 0x00 पूर्ण,
	अणु 0x0d, 0x00 पूर्ण,
	अणु 0x0e, 0x00 पूर्ण,
	अणु 0x0f, 0x08 पूर्ण,
	अणु 0x10, 0x00 पूर्ण,
	अणु 0x11, 0x00 पूर्ण,
	अणु 0x12, 0x00 पूर्ण,
	अणु 0x13, 0x00 पूर्ण,
	अणु 0x14, 0x08 पूर्ण,
	अणु 0x15, 0x10 पूर्ण,
	अणु 0x16, 0x10 पूर्ण,
	अणु 0x17, 0x54 पूर्ण,
	अणु 0x18, 0x40 पूर्ण,
	अणु 0x19, 0x00 पूर्ण,
	अणु 0x1a, 0x00 पूर्ण,
	अणु 0x1b, 0x00 पूर्ण,
	अणु 0x1c, 0x00 पूर्ण,
	अणु 0x1d, 0x00 पूर्ण,
	अणु 0x1e, 0x00 पूर्ण,
	अणु 0x1f, 0x00 पूर्ण,
	अणु 0x20, 0x00 पूर्ण,
	अणु 0x21, 0x00 पूर्ण,
	अणु 0x22, 0x00 पूर्ण,
	अणु 0x23, 0x02 पूर्ण,
	अणु 0x24, 0x00 पूर्ण,
	अणु 0x25, 0x76 पूर्ण,
	अणु 0x26, 0x00 पूर्ण,
	अणु 0x27, 0x00 पूर्ण,
	अणु 0x28, 0x04 पूर्ण,
	अणु 0x29, 0x00 पूर्ण,
	अणु 0x2a, 0x00 पूर्ण,
	अणु 0x2b, 0x30 पूर्ण,
	अणु 0x2c, 0x2A पूर्ण,
	अणु 0x83, 0x00 पूर्ण,
	अणु 0x84, 0x00 पूर्ण,
	अणु 0x85, 0x00 पूर्ण,
	अणु 0x86, 0x00 पूर्ण,
	अणु 0x87, 0x00 पूर्ण,
	अणु 0x88, 0x00 पूर्ण,
पूर्ण;

अटल bool da7210_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल DA7210_A_HID_UNLOCK:
	हाल DA7210_A_TEST_UNLOCK:
	हाल DA7210_A_PLL1:
	हाल DA7210_A_CP_MODE:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल bool da7210_अस्थिर_रेजिस्टर(काष्ठा device *dev,
				    अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल DA7210_STATUS:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * Set PCM DAI word length.
 */
अटल पूर्णांक da7210_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा da7210_priv *da7210 = snd_soc_component_get_drvdata(component);
	u32 dai_cfg1;
	u32 fs, sysclk;

	/* set DAI source to Left and Right ADC */
	snd_soc_component_ग_लिखो(component, DA7210_DAI_SRC_SEL,
		     DA7210_DAI_OUT_R_SRC | DA7210_DAI_OUT_L_SRC);

	/* Enable DAI */
	snd_soc_component_ग_लिखो(component, DA7210_DAI_CFG3, DA7210_DAI_OE | DA7210_DAI_EN);

	dai_cfg1 = 0xFC & snd_soc_component_पढ़ो(component, DA7210_DAI_CFG1);

	चयन (params_width(params)) अणु
	हाल 16:
		dai_cfg1 |= DA7210_DAI_WORD_S16_LE;
		अवरोध;
	हाल 20:
		dai_cfg1 |= DA7210_DAI_WORD_S20_3LE;
		अवरोध;
	हाल 24:
		dai_cfg1 |= DA7210_DAI_WORD_S24_LE;
		अवरोध;
	हाल 32:
		dai_cfg1 |= DA7210_DAI_WORD_S32_LE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, DA7210_DAI_CFG1, dai_cfg1);

	चयन (params_rate(params)) अणु
	हाल 8000:
		fs		= DA7210_PLL_FS_8000;
		sysclk		= 3072000;
		अवरोध;
	हाल 11025:
		fs		= DA7210_PLL_FS_11025;
		sysclk		= 2822400;
		अवरोध;
	हाल 12000:
		fs		= DA7210_PLL_FS_12000;
		sysclk		= 3072000;
		अवरोध;
	हाल 16000:
		fs		= DA7210_PLL_FS_16000;
		sysclk		= 3072000;
		अवरोध;
	हाल 22050:
		fs		= DA7210_PLL_FS_22050;
		sysclk		= 2822400;
		अवरोध;
	हाल 32000:
		fs		= DA7210_PLL_FS_32000;
		sysclk		= 3072000;
		अवरोध;
	हाल 44100:
		fs		= DA7210_PLL_FS_44100;
		sysclk		= 2822400;
		अवरोध;
	हाल 48000:
		fs		= DA7210_PLL_FS_48000;
		sysclk		= 3072000;
		अवरोध;
	हाल 88200:
		fs		= DA7210_PLL_FS_88200;
		sysclk		= 2822400;
		अवरोध;
	हाल 96000:
		fs		= DA7210_PLL_FS_96000;
		sysclk		= 3072000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Disable active mode */
	snd_soc_component_update_bits(component, DA7210_STARTUP1, DA7210_SC_MST_EN, 0);

	snd_soc_component_update_bits(component, DA7210_PLL, DA7210_PLL_FS_MASK, fs);

	अगर (da7210->mclk_rate && (da7210->mclk_rate != sysclk)) अणु
		/* PLL mode, disable PLL bypass */
		snd_soc_component_update_bits(component, DA7210_PLL_DIV3, DA7210_PLL_BYP, 0);

		अगर (!da7210->master) अणु
			/* PLL slave mode, also enable SRM */
			snd_soc_component_update_bits(component, DA7210_PLL,
						   (DA7210_MCLK_SRM_EN |
						    DA7210_MCLK_DET_EN),
						   (DA7210_MCLK_SRM_EN |
						    DA7210_MCLK_DET_EN));
		पूर्ण
	पूर्ण अन्यथा अणु
		/* PLL bypass mode, enable PLL bypass and Auto Detection */
		snd_soc_component_update_bits(component, DA7210_PLL, DA7210_MCLK_DET_EN,
						       DA7210_MCLK_DET_EN);
		snd_soc_component_update_bits(component, DA7210_PLL_DIV3, DA7210_PLL_BYP,
							    DA7210_PLL_BYP);
	पूर्ण
	/* Enable active mode */
	snd_soc_component_update_bits(component, DA7210_STARTUP1,
			    DA7210_SC_MST_EN, DA7210_SC_MST_EN);

	वापस 0;
पूर्ण

/*
 * Set DAI mode and Format
 */
अटल पूर्णांक da7210_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai, u32 fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा da7210_priv *da7210 = snd_soc_component_get_drvdata(component);
	u32 dai_cfg1;
	u32 dai_cfg3;

	dai_cfg1 = 0x7f & snd_soc_component_पढ़ो(component, DA7210_DAI_CFG1);
	dai_cfg3 = 0xfc & snd_soc_component_पढ़ो(component, DA7210_DAI_CFG3);

	अगर ((snd_soc_component_पढ़ो(component, DA7210_PLL) & DA7210_PLL_EN) &&
		(!(snd_soc_component_पढ़ो(component, DA7210_PLL_DIV3) & DA7210_PLL_BYP)))
		वापस -EINVAL;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		da7210->master = 1;
		dai_cfg1 |= DA7210_DAI_MODE_MASTER;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		da7210->master = 0;
		dai_cfg1 |= DA7210_DAI_MODE_SLAVE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* FIXME
	 *
	 * It support I2S only now
	 */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		dai_cfg3 |= DA7210_DAI_FORMAT_I2SMODE;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		dai_cfg3 |= DA7210_DAI_FORMAT_LEFT_J;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		dai_cfg3 |= DA7210_DAI_FORMAT_RIGHT_J;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* FIXME
	 *
	 * It support 64bit data transmission only now
	 */
	dai_cfg1 |= DA7210_DAI_FLEN_64BIT;

	snd_soc_component_ग_लिखो(component, DA7210_DAI_CFG1, dai_cfg1);
	snd_soc_component_ग_लिखो(component, DA7210_DAI_CFG3, dai_cfg3);

	वापस 0;
पूर्ण

अटल पूर्णांक da7210_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u8 mute_reg = snd_soc_component_पढ़ो(component, DA7210_DAC_HPF) & 0xFB;

	अगर (mute)
		snd_soc_component_ग_लिखो(component, DA7210_DAC_HPF, mute_reg | 0x4);
	अन्यथा
		snd_soc_component_ग_लिखो(component, DA7210_DAC_HPF, mute_reg);
	वापस 0;
पूर्ण

#घोषणा DA7210_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल पूर्णांक da7210_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
				 पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा da7210_priv *da7210 = snd_soc_component_get_drvdata(component);

	चयन (clk_id) अणु
	हाल DA7210_CLKSRC_MCLK:
		चयन (freq) अणु
		हाल 12000000:
		हाल 13000000:
		हाल 13500000:
		हाल 14400000:
		हाल 19200000:
		हाल 19680000:
		हाल 19800000:
			da7210->mclk_rate = freq;
			वापस 0;
		शेष:
			dev_err(codec_dai->dev, "Unsupported MCLK value %d\n",
				freq);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(codec_dai->dev, "Unknown clock source %d\n", clk_id);
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * da7210_set_dai_pll	:Configure the codec PLL
 * @codec_dai: poपूर्णांकer to codec DAI
 * @pll_id: da7210 has only one pll, so pll_id is always zero
 * @source: घड़ी source
 * @fref: MCLK frequency, should be < 20MHz
 * @fout: FsDM value, Refer page 44 & 45 of datasheet
 *
 * Note: Supported PLL input frequencies are 12MHz, 13MHz, 13.5MHz, 14.4MHz,
 *       19.2MHz, 19.6MHz and 19.8MHz
 *
 * Return: Zero क्रम success, negative error code क्रम error
 */
अटल पूर्णांक da7210_set_dai_pll(काष्ठा snd_soc_dai *codec_dai, पूर्णांक pll_id,
			      पूर्णांक source, अचिन्हित पूर्णांक fref, अचिन्हित पूर्णांक fout)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा da7210_priv *da7210 = snd_soc_component_get_drvdata(component);

	u8 pll_भाग1, pll_भाग2, pll_भाग3, cnt;

	/* In slave mode, there is only one set of भागisors */
	अगर (!da7210->master)
		fout = 2822400;

	/* Search pll भाग array क्रम correct भागisors */
	क्रम (cnt = 0; cnt < ARRAY_SIZE(da7210_pll_भाग); cnt++) अणु
		/* check fref, mode  and fout */
		अगर ((fref == da7210_pll_भाग[cnt].fref) &&
		    (da7210->master ==  da7210_pll_भाग[cnt].mode) &&
		    (fout == da7210_pll_भाग[cnt].fout)) अणु
			/* all match, pick up भागisors */
			pll_भाग1 = da7210_pll_भाग[cnt].भाग1;
			pll_भाग2 = da7210_pll_भाग[cnt].भाग2;
			pll_भाग3 = da7210_pll_भाग[cnt].भाग3;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (cnt >= ARRAY_SIZE(da7210_pll_भाग))
		जाओ err;

	/* Disable active mode */
	snd_soc_component_update_bits(component, DA7210_STARTUP1, DA7210_SC_MST_EN, 0);
	/* Write PLL भागiders */
	snd_soc_component_ग_लिखो(component, DA7210_PLL_DIV1, pll_भाग1);
	snd_soc_component_ग_लिखो(component, DA7210_PLL_DIV2, pll_भाग2);
	snd_soc_component_update_bits(component, DA7210_PLL_DIV3,
				   DA7210_PLL_DIV_L_MASK, pll_भाग3);

	/* Enable PLL */
	snd_soc_component_update_bits(component, DA7210_PLL, DA7210_PLL_EN, DA7210_PLL_EN);

	/* Enable active mode */
	snd_soc_component_update_bits(component, DA7210_STARTUP1, DA7210_SC_MST_EN,
						    DA7210_SC_MST_EN);
	वापस 0;
err:
	dev_err(codec_dai->dev, "Unsupported PLL input frequency %d\n", fref);
	वापस -EINVAL;
पूर्ण

/* DAI operations */
अटल स्थिर काष्ठा snd_soc_dai_ops da7210_dai_ops = अणु
	.hw_params	= da7210_hw_params,
	.set_fmt	= da7210_set_dai_fmt,
	.set_sysclk	= da7210_set_dai_sysclk,
	.set_pll	= da7210_set_dai_pll,
	.mute_stream	= da7210_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver da7210_dai = अणु
	.name = "da7210-hifi",
	/* playback capabilities */
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = DA7210_FORMATS,
	पूर्ण,
	/* capture capabilities */
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = DA7210_FORMATS,
	पूर्ण,
	.ops = &da7210_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल पूर्णांक da7210_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा da7210_priv *da7210 = snd_soc_component_get_drvdata(component);

	dev_info(component->dev, "DA7210 Audio Codec %s\n", DA7210_VERSION);

	da7210->mclk_rate       = 0;    /* This will be set from set_sysclk() */
	da7210->master          = 0;    /* This will be set from set_fmt() */

	/* Enable पूर्णांकernal regulator & bias current */
	snd_soc_component_ग_लिखो(component, DA7210_CONTROL, DA7210_REG_EN | DA7210_BIAS_EN);

	/*
	 * ADC settings
	 */

	/* Enable Left & Right MIC PGA and Mic Bias */
	snd_soc_component_ग_लिखो(component, DA7210_MIC_L, DA7210_MIC_L_EN | DA7210_MICBIAS_EN);
	snd_soc_component_ग_लिखो(component, DA7210_MIC_R, DA7210_MIC_R_EN);

	/* Enable Left and Right input PGA */
	snd_soc_component_ग_लिखो(component, DA7210_INMIX_L, DA7210_IN_L_EN);
	snd_soc_component_ग_लिखो(component, DA7210_INMIX_R, DA7210_IN_R_EN);

	/* Enable Left and Right ADC */
	snd_soc_component_ग_लिखो(component, DA7210_ADC, DA7210_ADC_L_EN | DA7210_ADC_R_EN);

	/*
	 * DAC settings
	 */

	/* Enable Left and Right DAC */
	snd_soc_component_ग_लिखो(component, DA7210_DAC_SEL,
		     DA7210_DAC_L_SRC_DAI_L | DA7210_DAC_L_EN |
		     DA7210_DAC_R_SRC_DAI_R | DA7210_DAC_R_EN);

	/* Enable Left and Right out PGA */
	snd_soc_component_ग_लिखो(component, DA7210_OUTMIX_L, DA7210_OUT_L_EN);
	snd_soc_component_ग_लिखो(component, DA7210_OUTMIX_R, DA7210_OUT_R_EN);

	/* Enable Left and Right HeadPhone PGA */
	snd_soc_component_ग_लिखो(component, DA7210_HP_CFG,
		     DA7210_HP_2CAP_MODE | DA7210_HP_SENSE_EN |
		     DA7210_HP_L_EN | DA7210_HP_MODE | DA7210_HP_R_EN);

	/* Enable ramp mode क्रम DAC gain update */
	snd_soc_component_ग_लिखो(component, DA7210_SOFTMUTE, DA7210_RAMP_EN);

	/*
	 * For DA7210 codec, there are two ways to enable/disable analog IOs
	 * and ADC/DAC,
	 * (1) Using "Enable Bit" of रेजिस्टर associated with that IO
	 * (or ADC/DAC)
	 *	e.g. Mic Left can be enabled using bit 7 of MIC_L(0x7) reg
	 *
	 * (2) Using "Standby Bit" of STARTUP2 or STARTUP3 रेजिस्टर
	 *	e.g. Mic left can be put to STANDBY using bit 0 of STARTUP3(0x5)
	 *
	 * Out of these two methods, the one using STANDBY bits is preferred
	 * way to enable/disable inभागidual blocks. This is because STANDBY
	 * रेजिस्टरs are part of प्रणाली controller which allows प्रणाली घातer
	 * up/करोwn in a controlled, pop-मुक्त manner. Also, as per application
	 * note of DA7210, STANDBY रेजिस्टर bits are only effective अगर a
	 * particular IO (or ADC/DAC) is alपढ़ोy enabled using enable/disable
	 * रेजिस्टर bits. Keeping these things in mind, current DAPM
	 * implementation manipulates only STANDBY bits.
	 *
	 * Overall implementation can be outlined as below,
	 *
	 * - "Enable bit" of an IO or ADC/DAC is used to enable it in probe()
	 * - "STANDBY bit" is controlled by DAPM
	 */

	/* Enable Line out amplअगरiers */
	snd_soc_component_ग_लिखो(component, DA7210_OUT1_L, DA7210_OUT1_L_EN);
	snd_soc_component_ग_लिखो(component, DA7210_OUT1_R, DA7210_OUT1_R_EN);
	snd_soc_component_ग_लिखो(component, DA7210_OUT2, DA7210_OUT2_EN |
		     DA7210_OUT2_OUTMIX_L | DA7210_OUT2_OUTMIX_R);

	/* Enable Aux1 */
	snd_soc_component_ग_लिखो(component, DA7210_AUX1_L, DA7210_AUX1_L_EN);
	snd_soc_component_ग_लिखो(component, DA7210_AUX1_R, DA7210_AUX1_R_EN);
	/* Enable Aux2 */
	snd_soc_component_ग_लिखो(component, DA7210_AUX2, DA7210_AUX2_EN);

	/* Set PLL Master घड़ी range 10-20 MHz, enable PLL bypass */
	snd_soc_component_ग_लिखो(component, DA7210_PLL_DIV3, DA7210_MCLK_RANGE_10_20_MHZ |
					      DA7210_PLL_BYP);

	/* Diable PLL and bypass it */
	snd_soc_component_ग_लिखो(component, DA7210_PLL, DA7210_PLL_FS_48000);

	/* Activate all enabled subप्रणाली */
	snd_soc_component_ग_लिखो(component, DA7210_STARTUP1, DA7210_SC_MST_EN);

	dev_info(component->dev, "DA7210 Audio Codec %s\n", DA7210_VERSION);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_da7210 = अणु
	.probe			= da7210_probe,
	.controls		= da7210_snd_controls,
	.num_controls		= ARRAY_SIZE(da7210_snd_controls),
	.dapm_widमाला_लो		= da7210_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(da7210_dapm_widमाला_लो),
	.dapm_routes		= da7210_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(da7210_audio_map),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

#अगर IS_ENABLED(CONFIG_I2C)

अटल स्थिर काष्ठा reg_sequence da7210_regmap_i2c_patch[] = अणु

	/* System controller master disable */
	अणु DA7210_STARTUP1, 0x00 पूर्ण,
	/* Set PLL Master घड़ी range 10-20 MHz */
	अणु DA7210_PLL_DIV3, DA7210_MCLK_RANGE_10_20_MHZ पूर्ण,

	/* to unlock */
	अणु DA7210_A_HID_UNLOCK, 0x8Bपूर्ण,
	अणु DA7210_A_TEST_UNLOCK, 0xB4पूर्ण,
	अणु DA7210_A_PLL1, 0x01पूर्ण,
	अणु DA7210_A_CP_MODE, 0x7Cपूर्ण,
	/* to re-lock */
	अणु DA7210_A_HID_UNLOCK, 0x00पूर्ण,
	अणु DA7210_A_TEST_UNLOCK, 0x00पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config da7210_regmap_config_i2c = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.reg_शेषs = da7210_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(da7210_reg_शेषs),
	.अस्थिर_reg = da7210_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = da7210_पढ़ोable_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक da7210_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा da7210_priv *da7210;
	पूर्णांक ret;

	da7210 = devm_kzalloc(&i2c->dev, माप(काष्ठा da7210_priv),
			      GFP_KERNEL);
	अगर (!da7210)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, da7210);

	da7210->regmap = devm_regmap_init_i2c(i2c, &da7210_regmap_config_i2c);
	अगर (IS_ERR(da7210->regmap)) अणु
		ret = PTR_ERR(da7210->regmap);
		dev_err(&i2c->dev, "regmap_init() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_रेजिस्टर_patch(da7210->regmap, da7210_regmap_i2c_patch,
				    ARRAY_SIZE(da7210_regmap_i2c_patch));
	अगर (ret != 0)
		dev_warn(&i2c->dev, "Failed to apply regmap patch: %d\n", ret);

	ret =  devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_da7210, &da7210_dai, 1);
	अगर (ret < 0)
		dev_err(&i2c->dev, "Failed to register component: %d\n", ret);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id da7210_i2c_id[] = अणु
	अणु "da7210", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, da7210_i2c_id);

/* I2C codec control layer */
अटल काष्ठा i2c_driver da7210_i2c_driver = अणु
	.driver = अणु
		.name = "da7210",
	पूर्ण,
	.probe		= da7210_i2c_probe,
	.id_table	= da7210_i2c_id,
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_SPI_MASTER)

अटल स्थिर काष्ठा reg_sequence da7210_regmap_spi_patch[] = अणु
	/* Dummy पढ़ो to give two pulses over nCS क्रम SPI */
	अणु DA7210_AUX2, 0x00 पूर्ण,
	अणु DA7210_AUX2, 0x00 पूर्ण,

	/* System controller master disable */
	अणु DA7210_STARTUP1, 0x00 पूर्ण,
	/* Set PLL Master घड़ी range 10-20 MHz */
	अणु DA7210_PLL_DIV3, DA7210_MCLK_RANGE_10_20_MHZ पूर्ण,

	/* to set PAGE1 of SPI रेजिस्टर space */
	अणु DA7210_PAGE_CONTROL, 0x80 पूर्ण,
	/* to unlock */
	अणु DA7210_A_HID_UNLOCK, 0x8Bपूर्ण,
	अणु DA7210_A_TEST_UNLOCK, 0xB4पूर्ण,
	अणु DA7210_A_PLL1, 0x01पूर्ण,
	अणु DA7210_A_CP_MODE, 0x7Cपूर्ण,
	/* to re-lock */
	अणु DA7210_A_HID_UNLOCK, 0x00पूर्ण,
	अणु DA7210_A_TEST_UNLOCK, 0x00पूर्ण,
	/* to set back PAGE0 of SPI रेजिस्टर space */
	अणु DA7210_PAGE_CONTROL, 0x00 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config da7210_regmap_config_spi = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.पढ़ो_flag_mask = 0x01,
	.ग_लिखो_flag_mask = 0x00,

	.reg_शेषs = da7210_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(da7210_reg_शेषs),
	.अस्थिर_reg = da7210_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg = da7210_पढ़ोable_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक da7210_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा da7210_priv *da7210;
	पूर्णांक ret;

	da7210 = devm_kzalloc(&spi->dev, माप(काष्ठा da7210_priv),
			      GFP_KERNEL);
	अगर (!da7210)
		वापस -ENOMEM;

	spi_set_drvdata(spi, da7210);
	da7210->regmap = devm_regmap_init_spi(spi, &da7210_regmap_config_spi);
	अगर (IS_ERR(da7210->regmap)) अणु
		ret = PTR_ERR(da7210->regmap);
		dev_err(&spi->dev, "Failed to register regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_रेजिस्टर_patch(da7210->regmap, da7210_regmap_spi_patch,
				    ARRAY_SIZE(da7210_regmap_spi_patch));
	अगर (ret != 0)
		dev_warn(&spi->dev, "Failed to apply regmap patch: %d\n", ret);

	ret = devm_snd_soc_रेजिस्टर_component(&spi->dev,
			&soc_component_dev_da7210, &da7210_dai, 1);

	वापस ret;
पूर्ण

अटल काष्ठा spi_driver da7210_spi_driver = अणु
	.driver = अणु
		.name = "da7210",
	पूर्ण,
	.probe = da7210_spi_probe,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init da7210_modinit(व्योम)
अणु
	पूर्णांक ret = 0;
#अगर IS_ENABLED(CONFIG_I2C)
	ret = i2c_add_driver(&da7210_i2c_driver);
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	ret = spi_रेजिस्टर_driver(&da7210_spi_driver);
	अगर (ret) अणु
		prपूर्णांकk(KERN_ERR "Failed to register da7210 SPI driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
	वापस ret;
पूर्ण
module_init(da7210_modinit);

अटल व्योम __निकास da7210_निकास(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_I2C)
	i2c_del_driver(&da7210_i2c_driver);
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	spi_unरेजिस्टर_driver(&da7210_spi_driver);
#पूर्ण_अगर
पूर्ण
module_निकास(da7210_निकास);

MODULE_DESCRIPTION("ASoC DA7210 driver");
MODULE_AUTHOR("David Chen, Kuninori Morimoto");
MODULE_LICENSE("GPL");
