<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DA9055 ALSA Soc codec driver
 *
 * Copyright (c) 2012 Dialog Semiconductor
 *
 * Tested on (Samsung SMDK6410 board + DA9055 EVB) using I2S and I2C
 * Written by David Chen <david.chen@diasemi.com> and
 * Ashish Chavan <ashish.chavan@kpitcummins.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश <sound/da9055.h>

/* DA9055 रेजिस्टर space */

/* Status Registers */
#घोषणा DA9055_STATUS1			0x02
#घोषणा DA9055_PLL_STATUS		0x03
#घोषणा DA9055_AUX_L_GAIN_STATUS	0x04
#घोषणा DA9055_AUX_R_GAIN_STATUS	0x05
#घोषणा DA9055_MIC_L_GAIN_STATUS	0x06
#घोषणा DA9055_MIC_R_GAIN_STATUS	0x07
#घोषणा DA9055_MIXIN_L_GAIN_STATUS	0x08
#घोषणा DA9055_MIXIN_R_GAIN_STATUS	0x09
#घोषणा DA9055_ADC_L_GAIN_STATUS	0x0A
#घोषणा DA9055_ADC_R_GAIN_STATUS	0x0B
#घोषणा DA9055_DAC_L_GAIN_STATUS	0x0C
#घोषणा DA9055_DAC_R_GAIN_STATUS	0x0D
#घोषणा DA9055_HP_L_GAIN_STATUS		0x0E
#घोषणा DA9055_HP_R_GAIN_STATUS		0x0F
#घोषणा DA9055_LINE_GAIN_STATUS		0x10

/* System Initialisation Registers */
#घोषणा DA9055_CIF_CTRL			0x20
#घोषणा DA9055_DIG_ROUTING_AIF		0X21
#घोषणा DA9055_SR			0x22
#घोषणा DA9055_REFERENCES		0x23
#घोषणा DA9055_PLL_FRAC_TOP		0x24
#घोषणा DA9055_PLL_FRAC_BOT		0x25
#घोषणा DA9055_PLL_INTEGER		0x26
#घोषणा DA9055_PLL_CTRL			0x27
#घोषणा DA9055_AIF_CLK_MODE		0x28
#घोषणा DA9055_AIF_CTRL			0x29
#घोषणा DA9055_DIG_ROUTING_DAC		0x2A
#घोषणा DA9055_ALC_CTRL1		0x2B

/* Input - Gain, Select and Filter Registers */
#घोषणा DA9055_AUX_L_GAIN		0x30
#घोषणा DA9055_AUX_R_GAIN		0x31
#घोषणा DA9055_MIXIN_L_SELECT		0x32
#घोषणा DA9055_MIXIN_R_SELECT		0x33
#घोषणा DA9055_MIXIN_L_GAIN		0x34
#घोषणा DA9055_MIXIN_R_GAIN		0x35
#घोषणा DA9055_ADC_L_GAIN		0x36
#घोषणा DA9055_ADC_R_GAIN		0x37
#घोषणा DA9055_ADC_FILTERS1		0x38
#घोषणा DA9055_MIC_L_GAIN		0x39
#घोषणा DA9055_MIC_R_GAIN		0x3A

/* Output - Gain, Select and Filter Registers */
#घोषणा DA9055_DAC_FILTERS5		0x40
#घोषणा DA9055_DAC_FILTERS2		0x41
#घोषणा DA9055_DAC_FILTERS3		0x42
#घोषणा DA9055_DAC_FILTERS4		0x43
#घोषणा DA9055_DAC_FILTERS1		0x44
#घोषणा DA9055_DAC_L_GAIN		0x45
#घोषणा DA9055_DAC_R_GAIN		0x46
#घोषणा DA9055_CP_CTRL			0x47
#घोषणा DA9055_HP_L_GAIN		0x48
#घोषणा DA9055_HP_R_GAIN		0x49
#घोषणा DA9055_LINE_GAIN		0x4A
#घोषणा DA9055_MIXOUT_L_SELECT		0x4B
#घोषणा DA9055_MIXOUT_R_SELECT		0x4C

/* System Controller Registers */
#घोषणा DA9055_SYSTEM_MODES_INPUT	0x50
#घोषणा DA9055_SYSTEM_MODES_OUTPUT	0x51

/* Control Registers */
#घोषणा DA9055_AUX_L_CTRL		0x60
#घोषणा DA9055_AUX_R_CTRL		0x61
#घोषणा DA9055_MIC_BIAS_CTRL		0x62
#घोषणा DA9055_MIC_L_CTRL		0x63
#घोषणा DA9055_MIC_R_CTRL		0x64
#घोषणा DA9055_MIXIN_L_CTRL		0x65
#घोषणा DA9055_MIXIN_R_CTRL		0x66
#घोषणा DA9055_ADC_L_CTRL		0x67
#घोषणा DA9055_ADC_R_CTRL		0x68
#घोषणा DA9055_DAC_L_CTRL		0x69
#घोषणा DA9055_DAC_R_CTRL		0x6A
#घोषणा DA9055_HP_L_CTRL		0x6B
#घोषणा DA9055_HP_R_CTRL		0x6C
#घोषणा DA9055_LINE_CTRL		0x6D
#घोषणा DA9055_MIXOUT_L_CTRL		0x6E
#घोषणा DA9055_MIXOUT_R_CTRL		0x6F

/* Configuration Registers */
#घोषणा DA9055_LDO_CTRL			0x90
#घोषणा DA9055_IO_CTRL			0x91
#घोषणा DA9055_GAIN_RAMP_CTRL		0x92
#घोषणा DA9055_MIC_CONFIG		0x93
#घोषणा DA9055_PC_COUNT			0x94
#घोषणा DA9055_CP_VOL_THRESHOLD1	0x95
#घोषणा DA9055_CP_DELAY			0x96
#घोषणा DA9055_CP_DETECTOR		0x97
#घोषणा DA9055_AIF_OFFSET		0x98
#घोषणा DA9055_DIG_CTRL			0x99
#घोषणा DA9055_ALC_CTRL2		0x9A
#घोषणा DA9055_ALC_CTRL3		0x9B
#घोषणा DA9055_ALC_NOISE		0x9C
#घोषणा DA9055_ALC_TARGET_MIN		0x9D
#घोषणा DA9055_ALC_TARGET_MAX		0x9E
#घोषणा DA9055_ALC_GAIN_LIMITS		0x9F
#घोषणा DA9055_ALC_ANA_GAIN_LIMITS	0xA0
#घोषणा DA9055_ALC_ANTICLIP_CTRL	0xA1
#घोषणा DA9055_ALC_ANTICLIP_LEVEL	0xA2
#घोषणा DA9055_ALC_OFFSET_OP2M_L	0xA6
#घोषणा DA9055_ALC_OFFSET_OP2U_L	0xA7
#घोषणा DA9055_ALC_OFFSET_OP2M_R	0xAB
#घोषणा DA9055_ALC_OFFSET_OP2U_R	0xAC
#घोषणा DA9055_ALC_CIC_OP_LVL_CTRL	0xAD
#घोषणा DA9055_ALC_CIC_OP_LVL_DATA	0xAE
#घोषणा DA9055_DAC_NG_SETUP_TIME	0xAF
#घोषणा DA9055_DAC_NG_OFF_THRESHOLD	0xB0
#घोषणा DA9055_DAC_NG_ON_THRESHOLD	0xB1
#घोषणा DA9055_DAC_NG_CTRL		0xB2

/* SR bit fields */
#घोषणा DA9055_SR_8000			(0x1 << 0)
#घोषणा DA9055_SR_11025			(0x2 << 0)
#घोषणा DA9055_SR_12000			(0x3 << 0)
#घोषणा DA9055_SR_16000			(0x5 << 0)
#घोषणा DA9055_SR_22050			(0x6 << 0)
#घोषणा DA9055_SR_24000			(0x7 << 0)
#घोषणा DA9055_SR_32000			(0x9 << 0)
#घोषणा DA9055_SR_44100			(0xA << 0)
#घोषणा DA9055_SR_48000			(0xB << 0)
#घोषणा DA9055_SR_88200			(0xE << 0)
#घोषणा DA9055_SR_96000			(0xF << 0)

/* REFERENCES bit fields */
#घोषणा DA9055_BIAS_EN			(1 << 3)
#घोषणा DA9055_VMID_EN			(1 << 7)

/* PLL_CTRL bit fields */
#घोषणा DA9055_PLL_INDIV_10_20_MHZ	(1 << 2)
#घोषणा DA9055_PLL_SRM_EN		(1 << 6)
#घोषणा DA9055_PLL_EN			(1 << 7)

/* AIF_CLK_MODE bit fields */
#घोषणा DA9055_AIF_BCLKS_PER_WCLK_32	(0 << 0)
#घोषणा DA9055_AIF_BCLKS_PER_WCLK_64	(1 << 0)
#घोषणा DA9055_AIF_BCLKS_PER_WCLK_128	(2 << 0)
#घोषणा DA9055_AIF_BCLKS_PER_WCLK_256	(3 << 0)
#घोषणा DA9055_AIF_CLK_EN_SLAVE_MODE	(0 << 7)
#घोषणा DA9055_AIF_CLK_EN_MASTER_MODE	(1 << 7)

/* AIF_CTRL bit fields */
#घोषणा DA9055_AIF_FORMAT_I2S_MODE	(0 << 0)
#घोषणा DA9055_AIF_FORMAT_LEFT_J	(1 << 0)
#घोषणा DA9055_AIF_FORMAT_RIGHT_J	(2 << 0)
#घोषणा DA9055_AIF_FORMAT_DSP		(3 << 0)
#घोषणा DA9055_AIF_WORD_S16_LE		(0 << 2)
#घोषणा DA9055_AIF_WORD_S20_3LE		(1 << 2)
#घोषणा DA9055_AIF_WORD_S24_LE		(2 << 2)
#घोषणा DA9055_AIF_WORD_S32_LE		(3 << 2)

/* MIC_L_CTRL bit fields */
#घोषणा DA9055_MIC_L_MUTE_EN		(1 << 6)

/* MIC_R_CTRL bit fields */
#घोषणा DA9055_MIC_R_MUTE_EN		(1 << 6)

/* MIXIN_L_CTRL bit fields */
#घोषणा DA9055_MIXIN_L_MIX_EN		(1 << 3)

/* MIXIN_R_CTRL bit fields */
#घोषणा DA9055_MIXIN_R_MIX_EN		(1 << 3)

/* ADC_L_CTRL bit fields */
#घोषणा DA9055_ADC_L_EN			(1 << 7)

/* ADC_R_CTRL bit fields */
#घोषणा DA9055_ADC_R_EN			(1 << 7)

/* DAC_L_CTRL bit fields */
#घोषणा DA9055_DAC_L_MUTE_EN		(1 << 6)

/* DAC_R_CTRL bit fields */
#घोषणा DA9055_DAC_R_MUTE_EN		(1 << 6)

/* HP_L_CTRL bit fields */
#घोषणा DA9055_HP_L_AMP_OE		(1 << 3)

/* HP_R_CTRL bit fields */
#घोषणा DA9055_HP_R_AMP_OE		(1 << 3)

/* LINE_CTRL bit fields */
#घोषणा DA9055_LINE_AMP_OE		(1 << 3)

/* MIXOUT_L_CTRL bit fields */
#घोषणा DA9055_MIXOUT_L_MIX_EN		(1 << 3)

/* MIXOUT_R_CTRL bit fields */
#घोषणा DA9055_MIXOUT_R_MIX_EN		(1 << 3)

/* MIC bias select bit fields */
#घोषणा DA9055_MICBIAS2_EN		(1 << 6)

/* ALC_CIC_OP_LEVEL_CTRL bit fields */
#घोषणा DA9055_ALC_DATA_MIDDLE		(2 << 0)
#घोषणा DA9055_ALC_DATA_TOP		(3 << 0)
#घोषणा DA9055_ALC_CIC_OP_CHANNEL_LEFT	(0 << 7)
#घोषणा DA9055_ALC_CIC_OP_CHANNEL_RIGHT	(1 << 7)

#घोषणा DA9055_AIF_BCLK_MASK		(3 << 0)
#घोषणा DA9055_AIF_CLK_MODE_MASK	(1 << 7)
#घोषणा DA9055_AIF_FORMAT_MASK		(3 << 0)
#घोषणा DA9055_AIF_WORD_LENGTH_MASK	(3 << 2)
#घोषणा DA9055_GAIN_RAMPING_EN		(1 << 5)
#घोषणा DA9055_MICBIAS_LEVEL_MASK	(3 << 4)

#घोषणा DA9055_ALC_OFFSET_15_8		0x00FF00
#घोषणा DA9055_ALC_OFFSET_17_16		0x030000
#घोषणा DA9055_ALC_AVG_ITERATIONS	5

काष्ठा pll_भाग अणु
	पूर्णांक fref;
	पूर्णांक fout;
	u8 frac_top;
	u8 frac_bot;
	u8 पूर्णांकeger;
	u8 mode;	/* 0 = slave, 1 = master */
पूर्ण;

/* PLL भागisor table */
अटल स्थिर काष्ठा pll_भाग da9055_pll_भाग[] = अणु
	/* क्रम MASTER mode, fs = 44.1Khz and its harmonics */
	अणु11289600, 2822400, 0x00, 0x00, 0x20, 1पूर्ण,	/* MCLK=11.2896Mhz */
	अणु12000000, 2822400, 0x03, 0x61, 0x1E, 1पूर्ण,	/* MCLK=12Mhz */
	अणु12288000, 2822400, 0x0C, 0xCC, 0x1D, 1पूर्ण,	/* MCLK=12.288Mhz */
	अणु13000000, 2822400, 0x19, 0x45, 0x1B, 1पूर्ण,	/* MCLK=13Mhz */
	अणु13500000, 2822400, 0x18, 0x56, 0x1A, 1पूर्ण,	/* MCLK=13.5Mhz */
	अणु14400000, 2822400, 0x02, 0xD0, 0x19, 1पूर्ण,	/* MCLK=14.4Mhz */
	अणु19200000, 2822400, 0x1A, 0x1C, 0x12, 1पूर्ण,	/* MCLK=19.2Mhz */
	अणु19680000, 2822400, 0x0B, 0x6D, 0x12, 1पूर्ण,	/* MCLK=19.68Mhz */
	अणु19800000, 2822400, 0x07, 0xDD, 0x12, 1पूर्ण,	/* MCLK=19.8Mhz */
	/* क्रम MASTER mode, fs = 48Khz and its harmonics */
	अणु11289600, 3072000, 0x1A, 0x8E, 0x22, 1पूर्ण,	/* MCLK=11.2896Mhz */
	अणु12000000, 3072000, 0x18, 0x93, 0x20, 1पूर्ण,	/* MCLK=12Mhz */
	अणु12288000, 3072000, 0x00, 0x00, 0x20, 1पूर्ण,	/* MCLK=12.288Mhz */
	अणु13000000, 3072000, 0x07, 0xEA, 0x1E, 1पूर्ण,	/* MCLK=13Mhz */
	अणु13500000, 3072000, 0x04, 0x11, 0x1D, 1पूर्ण,	/* MCLK=13.5Mhz */
	अणु14400000, 3072000, 0x09, 0xD0, 0x1B, 1पूर्ण,	/* MCLK=14.4Mhz */
	अणु19200000, 3072000, 0x0F, 0x5C, 0x14, 1पूर्ण,	/* MCLK=19.2Mhz */
	अणु19680000, 3072000, 0x1F, 0x60, 0x13, 1पूर्ण,	/* MCLK=19.68Mhz */
	अणु19800000, 3072000, 0x1B, 0x80, 0x13, 1पूर्ण,	/* MCLK=19.8Mhz */
	/* क्रम SLAVE mode with SRM */
	अणु11289600, 2822400, 0x0D, 0x47, 0x21, 0पूर्ण,	/* MCLK=11.2896Mhz */
	अणु12000000, 2822400, 0x0D, 0xFA, 0x1F, 0पूर्ण,	/* MCLK=12Mhz */
	अणु12288000, 2822400, 0x16, 0x66, 0x1E, 0पूर्ण,	/* MCLK=12.288Mhz */
	अणु13000000, 2822400, 0x00, 0x98, 0x1D, 0पूर्ण,	/* MCLK=13Mhz */
	अणु13500000, 2822400, 0x1E, 0x33, 0x1B, 0पूर्ण,	/* MCLK=13.5Mhz */
	अणु14400000, 2822400, 0x06, 0x50, 0x1A, 0पूर्ण,	/* MCLK=14.4Mhz */
	अणु19200000, 2822400, 0x14, 0xBC, 0x13, 0पूर्ण,	/* MCLK=19.2Mhz */
	अणु19680000, 2822400, 0x05, 0x66, 0x13, 0पूर्ण,	/* MCLK=19.68Mhz */
	अणु19800000, 2822400, 0x01, 0xAE, 0x13, 0पूर्ण,	/* MCLK=19.8Mhz  */
पूर्ण;

क्रमागत clk_src अणु
	DA9055_CLKSRC_MCLK
पूर्ण;

/* Gain and Volume */

अटल स्थिर DECLARE_TLV_DB_RANGE(aux_vol_tlv,
	0x0, 0x10, TLV_DB_SCALE_ITEM(-5400, 0, 0),
	/* -54dB to 15dB */
	0x11, 0x3f, TLV_DB_SCALE_ITEM(-5400, 150, 0)
);

अटल स्थिर DECLARE_TLV_DB_RANGE(digital_gain_tlv,
	0x0, 0x07, TLV_DB_SCALE_ITEM(TLV_DB_GAIN_MUTE, 0, 1),
	/* -78dB to 12dB */
	0x08, 0x7f, TLV_DB_SCALE_ITEM(-7800, 75, 0)
);

अटल स्थिर DECLARE_TLV_DB_RANGE(alc_analog_gain_tlv,
	0x0, 0x0, TLV_DB_SCALE_ITEM(TLV_DB_GAIN_MUTE, 0, 1),
	/* 0dB to 36dB */
	0x01, 0x07, TLV_DB_SCALE_ITEM(0, 600, 0)
);

अटल स्थिर DECLARE_TLV_DB_SCALE(mic_vol_tlv, -600, 600, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(mixin_gain_tlv, -450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(eq_gain_tlv, -1050, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(hp_vol_tlv, -5700, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(lineout_vol_tlv, -4800, 100, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(alc_threshold_tlv, -9450, 150, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(alc_gain_tlv, 0, 600, 0);

/* ADC and DAC high pass filter cutoff value */
अटल स्थिर अक्षर * स्थिर da9055_hpf_cutoff_txt[] = अणु
	"Fs/24000", "Fs/12000", "Fs/6000", "Fs/3000"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da9055_dac_hpf_cutoff,
			    DA9055_DAC_FILTERS1, 4, da9055_hpf_cutoff_txt);

अटल SOC_ENUM_SINGLE_DECL(da9055_adc_hpf_cutoff,
			    DA9055_ADC_FILTERS1, 4, da9055_hpf_cutoff_txt);

/* ADC and DAC voice mode (8kHz) high pass cutoff value */
अटल स्थिर अक्षर * स्थिर da9055_vf_cutoff_txt[] = अणु
	"2.5Hz", "25Hz", "50Hz", "100Hz", "150Hz", "200Hz", "300Hz", "400Hz"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da9055_dac_vf_cutoff,
			    DA9055_DAC_FILTERS1, 0, da9055_vf_cutoff_txt);

अटल SOC_ENUM_SINGLE_DECL(da9055_adc_vf_cutoff,
			    DA9055_ADC_FILTERS1, 0, da9055_vf_cutoff_txt);

/* Gain ramping rate value */
अटल स्थिर अक्षर * स्थिर da9055_gain_ramping_txt[] = अणु
	"nominal rate", "nominal rate * 4", "nominal rate * 8",
	"nominal rate / 8"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da9055_gain_ramping_rate,
			    DA9055_GAIN_RAMP_CTRL, 0, da9055_gain_ramping_txt);

/* DAC noise gate setup समय value */
अटल स्थिर अक्षर * स्थिर da9055_dac_ng_setup_समय_प्रकारxt[] = अणु
	"256 samples", "512 samples", "1024 samples", "2048 samples"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da9055_dac_ng_setup_समय,
			    DA9055_DAC_NG_SETUP_TIME, 0,
			    da9055_dac_ng_setup_समय_प्रकारxt);

/* DAC noise gate rampup rate value */
अटल स्थिर अक्षर * स्थिर da9055_dac_ng_rampup_txt[] = अणु
	"0.02 ms/dB", "0.16 ms/dB"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da9055_dac_ng_rampup_rate,
			    DA9055_DAC_NG_SETUP_TIME, 2,
			    da9055_dac_ng_rampup_txt);

/* DAC noise gate rampकरोwn rate value */
अटल स्थिर अक्षर * स्थिर da9055_dac_ng_rampकरोwn_txt[] = अणु
	"0.64 ms/dB", "20.48 ms/dB"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da9055_dac_ng_rampकरोwn_rate,
			    DA9055_DAC_NG_SETUP_TIME, 3,
			    da9055_dac_ng_rampकरोwn_txt);

/* DAC soft mute rate value */
अटल स्थिर अक्षर * स्थिर da9055_dac_soft_mute_rate_txt[] = अणु
	"1", "2", "4", "8", "16", "32", "64"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da9055_dac_soft_mute_rate,
			    DA9055_DAC_FILTERS5, 4,
			    da9055_dac_soft_mute_rate_txt);

/* DAC routing select */
अटल स्थिर अक्षर * स्थिर da9055_dac_src_txt[] = अणु
	"ADC output left", "ADC output right", "AIF input left",
	"AIF input right"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da9055_dac_l_src,
			    DA9055_DIG_ROUTING_DAC, 0, da9055_dac_src_txt);

अटल SOC_ENUM_SINGLE_DECL(da9055_dac_r_src,
			    DA9055_DIG_ROUTING_DAC, 4, da9055_dac_src_txt);

/* MIC PGA Left source select */
अटल स्थिर अक्षर * स्थिर da9055_mic_l_src_txt[] = अणु
	"MIC1_P_N", "MIC1_P", "MIC1_N", "MIC2_L"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da9055_mic_l_src,
			    DA9055_MIXIN_L_SELECT, 4, da9055_mic_l_src_txt);

/* MIC PGA Right source select */
अटल स्थिर अक्षर * स्थिर da9055_mic_r_src_txt[] = अणु
	"MIC2_R_L", "MIC2_R", "MIC2_L"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da9055_mic_r_src,
			    DA9055_MIXIN_R_SELECT, 4, da9055_mic_r_src_txt);

/* ALC Input Signal Tracking rate select */
अटल स्थिर अक्षर * स्थिर da9055_संकेत_tracking_rate_txt[] = अणु
	"1/4", "1/16", "1/256", "1/65536"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da9055_पूर्णांकeg_attack_rate,
			    DA9055_ALC_CTRL3, 4,
			    da9055_संकेत_tracking_rate_txt);

अटल SOC_ENUM_SINGLE_DECL(da9055_पूर्णांकeg_release_rate,
			    DA9055_ALC_CTRL3, 6,
			    da9055_संकेत_tracking_rate_txt);

/* ALC Attack Rate select */
अटल स्थिर अक्षर * स्थिर da9055_attack_rate_txt[] = अणु
	"44/fs", "88/fs", "176/fs", "352/fs", "704/fs", "1408/fs", "2816/fs",
	"5632/fs", "11264/fs", "22528/fs", "45056/fs", "90112/fs", "180224/fs"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da9055_attack_rate,
			    DA9055_ALC_CTRL2, 0, da9055_attack_rate_txt);

/* ALC Release Rate select */
अटल स्थिर अक्षर * स्थिर da9055_release_rate_txt[] = अणु
	"176/fs", "352/fs", "704/fs", "1408/fs", "2816/fs", "5632/fs",
	"11264/fs", "22528/fs", "45056/fs", "90112/fs", "180224/fs"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da9055_release_rate,
			    DA9055_ALC_CTRL2, 4, da9055_release_rate_txt);

/* ALC Hold Time select */
अटल स्थिर अक्षर * स्थिर da9055_hold_समय_प्रकारxt[] = अणु
	"62/fs", "124/fs", "248/fs", "496/fs", "992/fs", "1984/fs", "3968/fs",
	"7936/fs", "15872/fs", "31744/fs", "63488/fs", "126976/fs",
	"253952/fs", "507904/fs", "1015808/fs", "2031616/fs"
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(da9055_hold_समय,
			    DA9055_ALC_CTRL3, 0, da9055_hold_समय_प्रकारxt);

अटल पूर्णांक da9055_get_alc_data(काष्ठा snd_soc_component *component, u8 reg_val)
अणु
	पूर्णांक mid_data, top_data;
	पूर्णांक sum = 0;
	u8 iteration;

	क्रम (iteration = 0; iteration < DA9055_ALC_AVG_ITERATIONS;
	     iteration++) अणु
		/* Select the left or right channel and capture data */
		snd_soc_component_ग_लिखो(component, DA9055_ALC_CIC_OP_LVL_CTRL, reg_val);

		/* Select middle 8 bits क्रम पढ़ो back from data रेजिस्टर */
		snd_soc_component_ग_लिखो(component, DA9055_ALC_CIC_OP_LVL_CTRL,
			      reg_val | DA9055_ALC_DATA_MIDDLE);
		mid_data = snd_soc_component_पढ़ो(component, DA9055_ALC_CIC_OP_LVL_DATA);

		/* Select top 8 bits क्रम पढ़ो back from data रेजिस्टर */
		snd_soc_component_ग_लिखो(component, DA9055_ALC_CIC_OP_LVL_CTRL,
			      reg_val | DA9055_ALC_DATA_TOP);
		top_data = snd_soc_component_पढ़ो(component, DA9055_ALC_CIC_OP_LVL_DATA);

		sum += ((mid_data << 8) | (top_data << 16));
	पूर्ण

	वापस sum / DA9055_ALC_AVG_ITERATIONS;
पूर्ण

अटल पूर्णांक da9055_put_alc_sw(काष्ठा snd_kcontrol *kcontrol,
			     काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	u8 reg_val, adc_left, adc_right, mic_left, mic_right;
	पूर्णांक avg_left_data, avg_right_data, offset_l, offset_r;

	अगर (ucontrol->value.पूर्णांकeger.value[0]) अणु
		/*
		 * While enabling ALC (or ALC sync mode), calibration of the DC
		 * offsets must be करोne first
		 */

		/* Save current values from Mic control रेजिस्टरs */
		mic_left = snd_soc_component_पढ़ो(component, DA9055_MIC_L_CTRL);
		mic_right = snd_soc_component_पढ़ो(component, DA9055_MIC_R_CTRL);

		/* Mute Mic PGA Left and Right */
		snd_soc_component_update_bits(component, DA9055_MIC_L_CTRL,
				    DA9055_MIC_L_MUTE_EN, DA9055_MIC_L_MUTE_EN);
		snd_soc_component_update_bits(component, DA9055_MIC_R_CTRL,
				    DA9055_MIC_R_MUTE_EN, DA9055_MIC_R_MUTE_EN);

		/* Save current values from ADC control रेजिस्टरs */
		adc_left = snd_soc_component_पढ़ो(component, DA9055_ADC_L_CTRL);
		adc_right = snd_soc_component_पढ़ो(component, DA9055_ADC_R_CTRL);

		/* Enable ADC Left and Right */
		snd_soc_component_update_bits(component, DA9055_ADC_L_CTRL,
				    DA9055_ADC_L_EN, DA9055_ADC_L_EN);
		snd_soc_component_update_bits(component, DA9055_ADC_R_CTRL,
				    DA9055_ADC_R_EN, DA9055_ADC_R_EN);

		/* Calculate average क्रम Left and Right data */
		/* Left Data */
		avg_left_data = da9055_get_alc_data(component,
				DA9055_ALC_CIC_OP_CHANNEL_LEFT);
		/* Right Data */
		avg_right_data = da9055_get_alc_data(component,
				 DA9055_ALC_CIC_OP_CHANNEL_RIGHT);

		/* Calculate DC offset */
		offset_l = -avg_left_data;
		offset_r = -avg_right_data;

		reg_val = (offset_l & DA9055_ALC_OFFSET_15_8) >> 8;
		snd_soc_component_ग_लिखो(component, DA9055_ALC_OFFSET_OP2M_L, reg_val);
		reg_val = (offset_l & DA9055_ALC_OFFSET_17_16) >> 16;
		snd_soc_component_ग_लिखो(component, DA9055_ALC_OFFSET_OP2U_L, reg_val);

		reg_val = (offset_r & DA9055_ALC_OFFSET_15_8) >> 8;
		snd_soc_component_ग_लिखो(component, DA9055_ALC_OFFSET_OP2M_R, reg_val);
		reg_val = (offset_r & DA9055_ALC_OFFSET_17_16) >> 16;
		snd_soc_component_ग_लिखो(component, DA9055_ALC_OFFSET_OP2U_R, reg_val);

		/* Restore original values of ADC control रेजिस्टरs */
		snd_soc_component_ग_लिखो(component, DA9055_ADC_L_CTRL, adc_left);
		snd_soc_component_ग_लिखो(component, DA9055_ADC_R_CTRL, adc_right);

		/* Restore original values of Mic control रेजिस्टरs */
		snd_soc_component_ग_लिखो(component, DA9055_MIC_L_CTRL, mic_left);
		snd_soc_component_ग_लिखो(component, DA9055_MIC_R_CTRL, mic_right);
	पूर्ण

	वापस snd_soc_put_volsw(kcontrol, ucontrol);
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new da9055_snd_controls[] = अणु

	/* Volume controls */
	SOC_DOUBLE_R_TLV("Mic Volume",
			 DA9055_MIC_L_GAIN, DA9055_MIC_R_GAIN,
			 0, 0x7, 0, mic_vol_tlv),
	SOC_DOUBLE_R_TLV("Aux Volume",
			 DA9055_AUX_L_GAIN, DA9055_AUX_R_GAIN,
			 0, 0x3f, 0, aux_vol_tlv),
	SOC_DOUBLE_R_TLV("Mixin PGA Volume",
			 DA9055_MIXIN_L_GAIN, DA9055_MIXIN_R_GAIN,
			 0, 0xf, 0, mixin_gain_tlv),
	SOC_DOUBLE_R_TLV("ADC Volume",
			 DA9055_ADC_L_GAIN, DA9055_ADC_R_GAIN,
			 0, 0x7f, 0, digital_gain_tlv),

	SOC_DOUBLE_R_TLV("DAC Volume",
			 DA9055_DAC_L_GAIN, DA9055_DAC_R_GAIN,
			 0, 0x7f, 0, digital_gain_tlv),
	SOC_DOUBLE_R_TLV("Headphone Volume",
			 DA9055_HP_L_GAIN, DA9055_HP_R_GAIN,
			 0, 0x3f, 0, hp_vol_tlv),
	SOC_SINGLE_TLV("Lineout Volume", DA9055_LINE_GAIN, 0, 0x3f, 0,
		       lineout_vol_tlv),

	/* DAC Equalizer controls */
	SOC_SINGLE("DAC EQ Switch", DA9055_DAC_FILTERS4, 7, 1, 0),
	SOC_SINGLE_TLV("DAC EQ1 Volume", DA9055_DAC_FILTERS2, 0, 0xf, 0,
		       eq_gain_tlv),
	SOC_SINGLE_TLV("DAC EQ2 Volume", DA9055_DAC_FILTERS2, 4, 0xf, 0,
		       eq_gain_tlv),
	SOC_SINGLE_TLV("DAC EQ3 Volume", DA9055_DAC_FILTERS3, 0, 0xf, 0,
		       eq_gain_tlv),
	SOC_SINGLE_TLV("DAC EQ4 Volume", DA9055_DAC_FILTERS3, 4, 0xf, 0,
		       eq_gain_tlv),
	SOC_SINGLE_TLV("DAC EQ5 Volume", DA9055_DAC_FILTERS4, 0, 0xf, 0,
		       eq_gain_tlv),

	/* High Pass Filter and Voice Mode controls */
	SOC_SINGLE("ADC HPF Switch", DA9055_ADC_FILTERS1, 7, 1, 0),
	SOC_ENUM("ADC HPF Cutoff", da9055_adc_hpf_cutoff),
	SOC_SINGLE("ADC Voice Mode Switch", DA9055_ADC_FILTERS1, 3, 1, 0),
	SOC_ENUM("ADC Voice Cutoff", da9055_adc_vf_cutoff),

	SOC_SINGLE("DAC HPF Switch", DA9055_DAC_FILTERS1, 7, 1, 0),
	SOC_ENUM("DAC HPF Cutoff", da9055_dac_hpf_cutoff),
	SOC_SINGLE("DAC Voice Mode Switch", DA9055_DAC_FILTERS1, 3, 1, 0),
	SOC_ENUM("DAC Voice Cutoff", da9055_dac_vf_cutoff),

	/* Mute controls */
	SOC_DOUBLE_R("Mic Switch", DA9055_MIC_L_CTRL,
		     DA9055_MIC_R_CTRL, 6, 1, 0),
	SOC_DOUBLE_R("Aux Switch", DA9055_AUX_L_CTRL,
		     DA9055_AUX_R_CTRL, 6, 1, 0),
	SOC_DOUBLE_R("Mixin PGA Switch", DA9055_MIXIN_L_CTRL,
		     DA9055_MIXIN_R_CTRL, 6, 1, 0),
	SOC_DOUBLE_R("ADC Switch", DA9055_ADC_L_CTRL,
		     DA9055_ADC_R_CTRL, 6, 1, 0),
	SOC_DOUBLE_R("Headphone Switch", DA9055_HP_L_CTRL,
		     DA9055_HP_R_CTRL, 6, 1, 0),
	SOC_SINGLE("Lineout Switch", DA9055_LINE_CTRL, 6, 1, 0),
	SOC_SINGLE("DAC Soft Mute Switch", DA9055_DAC_FILTERS5, 7, 1, 0),
	SOC_ENUM("DAC Soft Mute Rate", da9055_dac_soft_mute_rate),

	/* Zero Cross controls */
	SOC_DOUBLE_R("Aux ZC Switch", DA9055_AUX_L_CTRL,
		     DA9055_AUX_R_CTRL, 4, 1, 0),
	SOC_DOUBLE_R("Mixin PGA ZC Switch", DA9055_MIXIN_L_CTRL,
		     DA9055_MIXIN_R_CTRL, 4, 1, 0),
	SOC_DOUBLE_R("Headphone ZC Switch", DA9055_HP_L_CTRL,
		     DA9055_HP_R_CTRL, 4, 1, 0),
	SOC_SINGLE("Lineout ZC Switch", DA9055_LINE_CTRL, 4, 1, 0),

	/* Gain Ramping controls */
	SOC_DOUBLE_R("Aux Gain Ramping Switch", DA9055_AUX_L_CTRL,
		     DA9055_AUX_R_CTRL, 5, 1, 0),
	SOC_DOUBLE_R("Mixin Gain Ramping Switch", DA9055_MIXIN_L_CTRL,
		     DA9055_MIXIN_R_CTRL, 5, 1, 0),
	SOC_DOUBLE_R("ADC Gain Ramping Switch", DA9055_ADC_L_CTRL,
		     DA9055_ADC_R_CTRL, 5, 1, 0),
	SOC_DOUBLE_R("DAC Gain Ramping Switch", DA9055_DAC_L_CTRL,
		     DA9055_DAC_R_CTRL, 5, 1, 0),
	SOC_DOUBLE_R("Headphone Gain Ramping Switch", DA9055_HP_L_CTRL,
		     DA9055_HP_R_CTRL, 5, 1, 0),
	SOC_SINGLE("Lineout Gain Ramping Switch", DA9055_LINE_CTRL, 5, 1, 0),
	SOC_ENUM("Gain Ramping Rate", da9055_gain_ramping_rate),

	/* DAC Noise Gate controls */
	SOC_SINGLE("DAC NG Switch", DA9055_DAC_NG_CTRL, 7, 1, 0),
	SOC_SINGLE("DAC NG ON Threshold", DA9055_DAC_NG_ON_THRESHOLD,
		   0, 0x7, 0),
	SOC_SINGLE("DAC NG OFF Threshold", DA9055_DAC_NG_OFF_THRESHOLD,
		   0, 0x7, 0),
	SOC_ENUM("DAC NG Setup Time", da9055_dac_ng_setup_समय),
	SOC_ENUM("DAC NG Rampup Rate", da9055_dac_ng_rampup_rate),
	SOC_ENUM("DAC NG Rampdown Rate", da9055_dac_ng_rampकरोwn_rate),

	/* DAC Invertion control */
	SOC_SINGLE("DAC Left Invert", DA9055_DIG_CTRL, 3, 1, 0),
	SOC_SINGLE("DAC Right Invert", DA9055_DIG_CTRL, 7, 1, 0),

	/* DMIC controls */
	SOC_DOUBLE_R("DMIC Switch", DA9055_MIXIN_L_SELECT,
		     DA9055_MIXIN_R_SELECT, 7, 1, 0),

	/* ALC Controls */
	SOC_DOUBLE_EXT("ALC Switch", DA9055_ALC_CTRL1, 3, 7, 1, 0,
		       snd_soc_get_volsw, da9055_put_alc_sw),
	SOC_SINGLE_EXT("ALC Sync Mode Switch", DA9055_ALC_CTRL1, 1, 1, 0,
		       snd_soc_get_volsw, da9055_put_alc_sw),
	SOC_SINGLE("ALC Offset Switch", DA9055_ALC_CTRL1, 0, 1, 0),
	SOC_SINGLE("ALC Anticlip Mode Switch", DA9055_ALC_ANTICLIP_CTRL,
		   7, 1, 0),
	SOC_SINGLE("ALC Anticlip Level", DA9055_ALC_ANTICLIP_LEVEL,
		   0, 0x7f, 0),
	SOC_SINGLE_TLV("ALC Min Threshold Volume", DA9055_ALC_TARGET_MIN,
		       0, 0x3f, 1, alc_threshold_tlv),
	SOC_SINGLE_TLV("ALC Max Threshold Volume", DA9055_ALC_TARGET_MAX,
		       0, 0x3f, 1, alc_threshold_tlv),
	SOC_SINGLE_TLV("ALC Noise Threshold Volume", DA9055_ALC_NOISE,
		       0, 0x3f, 1, alc_threshold_tlv),
	SOC_SINGLE_TLV("ALC Max Gain Volume", DA9055_ALC_GAIN_LIMITS,
		       4, 0xf, 0, alc_gain_tlv),
	SOC_SINGLE_TLV("ALC Max Attenuation Volume", DA9055_ALC_GAIN_LIMITS,
		       0, 0xf, 0, alc_gain_tlv),
	SOC_SINGLE_TLV("ALC Min Analog Gain Volume",
		       DA9055_ALC_ANA_GAIN_LIMITS,
		       0, 0x7, 0, alc_analog_gain_tlv),
	SOC_SINGLE_TLV("ALC Max Analog Gain Volume",
		       DA9055_ALC_ANA_GAIN_LIMITS,
		       4, 0x7, 0, alc_analog_gain_tlv),
	SOC_ENUM("ALC Attack Rate", da9055_attack_rate),
	SOC_ENUM("ALC Release Rate", da9055_release_rate),
	SOC_ENUM("ALC Hold Time", da9055_hold_समय),
	/*
	 * Rate at which input संकेत envelope is tracked as the संकेत माला_लो
	 * larger
	 */
	SOC_ENUM("ALC Integ Attack Rate", da9055_पूर्णांकeg_attack_rate),
	/*
	 * Rate at which input संकेत envelope is tracked as the संकेत माला_लो
	 * smaller
	 */
	SOC_ENUM("ALC Integ Release Rate", da9055_पूर्णांकeg_release_rate),
पूर्ण;

/* DAPM Controls */

/* Mic PGA Left Source */
अटल स्थिर काष्ठा snd_kcontrol_new da9055_mic_l_mux_controls =
SOC_DAPM_ENUM("Route", da9055_mic_l_src);

/* Mic PGA Right Source */
अटल स्थिर काष्ठा snd_kcontrol_new da9055_mic_r_mux_controls =
SOC_DAPM_ENUM("Route", da9055_mic_r_src);

/* In Mixer Left */
अटल स्थिर काष्ठा snd_kcontrol_new da9055_dapm_mixinl_controls[] = अणु
	SOC_DAPM_SINGLE("Aux Left Switch", DA9055_MIXIN_L_SELECT, 0, 1, 0),
	SOC_DAPM_SINGLE("Mic Left Switch", DA9055_MIXIN_L_SELECT, 1, 1, 0),
	SOC_DAPM_SINGLE("Mic Right Switch", DA9055_MIXIN_L_SELECT, 2, 1, 0),
पूर्ण;

/* In Mixer Right */
अटल स्थिर काष्ठा snd_kcontrol_new da9055_dapm_mixinr_controls[] = अणु
	SOC_DAPM_SINGLE("Aux Right Switch", DA9055_MIXIN_R_SELECT, 0, 1, 0),
	SOC_DAPM_SINGLE("Mic Right Switch", DA9055_MIXIN_R_SELECT, 1, 1, 0),
	SOC_DAPM_SINGLE("Mic Left Switch", DA9055_MIXIN_R_SELECT, 2, 1, 0),
	SOC_DAPM_SINGLE("Mixin Left Switch", DA9055_MIXIN_R_SELECT, 3, 1, 0),
पूर्ण;

/* DAC Left Source */
अटल स्थिर काष्ठा snd_kcontrol_new da9055_dac_l_mux_controls =
SOC_DAPM_ENUM("Route", da9055_dac_l_src);

/* DAC Right Source */
अटल स्थिर काष्ठा snd_kcontrol_new da9055_dac_r_mux_controls =
SOC_DAPM_ENUM("Route", da9055_dac_r_src);

/* Out Mixer Left */
अटल स्थिर काष्ठा snd_kcontrol_new da9055_dapm_mixoutl_controls[] = अणु
	SOC_DAPM_SINGLE("Aux Left Switch", DA9055_MIXOUT_L_SELECT, 0, 1, 0),
	SOC_DAPM_SINGLE("Mixin Left Switch", DA9055_MIXOUT_L_SELECT, 1, 1, 0),
	SOC_DAPM_SINGLE("Mixin Right Switch", DA9055_MIXOUT_L_SELECT, 2, 1, 0),
	SOC_DAPM_SINGLE("DAC Left Switch", DA9055_MIXOUT_L_SELECT, 3, 1, 0),
	SOC_DAPM_SINGLE("Aux Left Invert Switch", DA9055_MIXOUT_L_SELECT,
			4, 1, 0),
	SOC_DAPM_SINGLE("Mixin Left Invert Switch", DA9055_MIXOUT_L_SELECT,
			5, 1, 0),
	SOC_DAPM_SINGLE("Mixin Right Invert Switch", DA9055_MIXOUT_L_SELECT,
			6, 1, 0),
पूर्ण;

/* Out Mixer Right */
अटल स्थिर काष्ठा snd_kcontrol_new da9055_dapm_mixoutr_controls[] = अणु
	SOC_DAPM_SINGLE("Aux Right Switch", DA9055_MIXOUT_R_SELECT, 0, 1, 0),
	SOC_DAPM_SINGLE("Mixin Right Switch", DA9055_MIXOUT_R_SELECT, 1, 1, 0),
	SOC_DAPM_SINGLE("Mixin Left Switch", DA9055_MIXOUT_R_SELECT, 2, 1, 0),
	SOC_DAPM_SINGLE("DAC Right Switch", DA9055_MIXOUT_R_SELECT, 3, 1, 0),
	SOC_DAPM_SINGLE("Aux Right Invert Switch", DA9055_MIXOUT_R_SELECT,
			4, 1, 0),
	SOC_DAPM_SINGLE("Mixin Right Invert Switch", DA9055_MIXOUT_R_SELECT,
			5, 1, 0),
	SOC_DAPM_SINGLE("Mixin Left Invert Switch", DA9055_MIXOUT_R_SELECT,
			6, 1, 0),
पूर्ण;

/* Headphone Output Enable */
अटल स्थिर काष्ठा snd_kcontrol_new da9055_dapm_hp_l_control =
SOC_DAPM_SINGLE("Switch", DA9055_HP_L_CTRL, 3, 1, 0);

अटल स्थिर काष्ठा snd_kcontrol_new da9055_dapm_hp_r_control =
SOC_DAPM_SINGLE("Switch", DA9055_HP_R_CTRL, 3, 1, 0);

/* Lineout Output Enable */
अटल स्थिर काष्ठा snd_kcontrol_new da9055_dapm_lineout_control =
SOC_DAPM_SINGLE("Switch", DA9055_LINE_CTRL, 3, 1, 0);

/* DAPM widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget da9055_dapm_widमाला_लो[] = अणु
	/* Input Side */

	/* Input Lines */
	SND_SOC_DAPM_INPUT("MIC1"),
	SND_SOC_DAPM_INPUT("MIC2"),
	SND_SOC_DAPM_INPUT("AUXL"),
	SND_SOC_DAPM_INPUT("AUXR"),

	/* MUXs क्रम Mic PGA source selection */
	SND_SOC_DAPM_MUX("Mic Left Source", SND_SOC_NOPM, 0, 0,
			 &da9055_mic_l_mux_controls),
	SND_SOC_DAPM_MUX("Mic Right Source", SND_SOC_NOPM, 0, 0,
			 &da9055_mic_r_mux_controls),

	/* Input PGAs */
	SND_SOC_DAPM_PGA("Mic Left", DA9055_MIC_L_CTRL, 7, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Mic Right", DA9055_MIC_R_CTRL, 7, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Aux Left", DA9055_AUX_L_CTRL, 7, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Aux Right", DA9055_AUX_R_CTRL, 7, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("MIXIN Left", DA9055_MIXIN_L_CTRL, 7, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("MIXIN Right", DA9055_MIXIN_R_CTRL, 7, 0, शून्य, 0),

	SND_SOC_DAPM_SUPPLY("Mic Bias", DA9055_MIC_BIAS_CTRL, 7, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("AIF", DA9055_AIF_CTRL, 7, 0, शून्य, 0),
	SND_SOC_DAPM_SUPPLY("Charge Pump", DA9055_CP_CTRL, 7, 0, शून्य, 0),

	/* Input Mixers */
	SND_SOC_DAPM_MIXER("In Mixer Left", SND_SOC_NOPM, 0, 0,
			   &da9055_dapm_mixinl_controls[0],
			   ARRAY_SIZE(da9055_dapm_mixinl_controls)),
	SND_SOC_DAPM_MIXER("In Mixer Right", SND_SOC_NOPM, 0, 0,
			   &da9055_dapm_mixinr_controls[0],
			   ARRAY_SIZE(da9055_dapm_mixinr_controls)),

	/* ADCs */
	SND_SOC_DAPM_ADC("ADC Left", "Capture", DA9055_ADC_L_CTRL, 7, 0),
	SND_SOC_DAPM_ADC("ADC Right", "Capture", DA9055_ADC_R_CTRL, 7, 0),

	/* Output Side */

	/* MUXs क्रम DAC source selection */
	SND_SOC_DAPM_MUX("DAC Left Source", SND_SOC_NOPM, 0, 0,
			 &da9055_dac_l_mux_controls),
	SND_SOC_DAPM_MUX("DAC Right Source", SND_SOC_NOPM, 0, 0,
			 &da9055_dac_r_mux_controls),

	/* AIF input */
	SND_SOC_DAPM_AIF_IN("AIFIN Left", "Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("AIFIN Right", "Playback", 0, SND_SOC_NOPM, 0, 0),

	/* DACs */
	SND_SOC_DAPM_DAC("DAC Left", "Playback", DA9055_DAC_L_CTRL, 7, 0),
	SND_SOC_DAPM_DAC("DAC Right", "Playback", DA9055_DAC_R_CTRL, 7, 0),

	/* Output Mixers */
	SND_SOC_DAPM_MIXER("Out Mixer Left", SND_SOC_NOPM, 0, 0,
			   &da9055_dapm_mixoutl_controls[0],
			   ARRAY_SIZE(da9055_dapm_mixoutl_controls)),
	SND_SOC_DAPM_MIXER("Out Mixer Right", SND_SOC_NOPM, 0, 0,
			   &da9055_dapm_mixoutr_controls[0],
			   ARRAY_SIZE(da9055_dapm_mixoutr_controls)),

	/* Output Enable Switches */
	SND_SOC_DAPM_SWITCH("Headphone Left Enable", SND_SOC_NOPM, 0, 0,
			    &da9055_dapm_hp_l_control),
	SND_SOC_DAPM_SWITCH("Headphone Right Enable", SND_SOC_NOPM, 0, 0,
			    &da9055_dapm_hp_r_control),
	SND_SOC_DAPM_SWITCH("Lineout Enable", SND_SOC_NOPM, 0, 0,
			    &da9055_dapm_lineout_control),

	/* Output PGAs */
	SND_SOC_DAPM_PGA("MIXOUT Left", DA9055_MIXOUT_L_CTRL, 7, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("MIXOUT Right", DA9055_MIXOUT_R_CTRL, 7, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Lineout", DA9055_LINE_CTRL, 7, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Headphone Left", DA9055_HP_L_CTRL, 7, 0, शून्य, 0),
	SND_SOC_DAPM_PGA("Headphone Right", DA9055_HP_R_CTRL, 7, 0, शून्य, 0),

	/* Output Lines */
	SND_SOC_DAPM_OUTPUT("HPL"),
	SND_SOC_DAPM_OUTPUT("HPR"),
	SND_SOC_DAPM_OUTPUT("LINE"),
पूर्ण;

/* DAPM audio route definition */
अटल स्थिर काष्ठा snd_soc_dapm_route da9055_audio_map[] = अणु
	/* Dest       Connecting Widget    source */

	/* Input path */
	अणु"Mic Left Source", "MIC1_P_N", "MIC1"पूर्ण,
	अणु"Mic Left Source", "MIC1_P", "MIC1"पूर्ण,
	अणु"Mic Left Source", "MIC1_N", "MIC1"पूर्ण,
	अणु"Mic Left Source", "MIC2_L", "MIC2"पूर्ण,

	अणु"Mic Right Source", "MIC2_R_L", "MIC2"पूर्ण,
	अणु"Mic Right Source", "MIC2_R", "MIC2"पूर्ण,
	अणु"Mic Right Source", "MIC2_L", "MIC2"पूर्ण,

	अणु"Mic Left", शून्य, "Mic Left Source"पूर्ण,
	अणु"Mic Right", शून्य, "Mic Right Source"पूर्ण,

	अणु"Aux Left", शून्य, "AUXL"पूर्ण,
	अणु"Aux Right", शून्य, "AUXR"पूर्ण,

	अणु"In Mixer Left", "Mic Left Switch", "Mic Left"पूर्ण,
	अणु"In Mixer Left", "Mic Right Switch", "Mic Right"पूर्ण,
	अणु"In Mixer Left", "Aux Left Switch", "Aux Left"पूर्ण,

	अणु"In Mixer Right", "Mic Right Switch", "Mic Right"पूर्ण,
	अणु"In Mixer Right", "Mic Left Switch", "Mic Left"पूर्ण,
	अणु"In Mixer Right", "Aux Right Switch", "Aux Right"पूर्ण,
	अणु"In Mixer Right", "Mixin Left Switch", "MIXIN Left"पूर्ण,

	अणु"MIXIN Left", शून्य, "In Mixer Left"पूर्ण,
	अणु"ADC Left", शून्य, "MIXIN Left"पूर्ण,

	अणु"MIXIN Right", शून्य, "In Mixer Right"पूर्ण,
	अणु"ADC Right", शून्य, "MIXIN Right"पूर्ण,

	अणु"ADC Left", शून्य, "AIF"पूर्ण,
	अणु"ADC Right", शून्य, "AIF"पूर्ण,

	/* Output path */
	अणु"AIFIN Left", शून्य, "AIF"पूर्ण,
	अणु"AIFIN Right", शून्य, "AIF"पूर्ण,

	अणु"DAC Left Source", "ADC output left", "ADC Left"पूर्ण,
	अणु"DAC Left Source", "ADC output right", "ADC Right"पूर्ण,
	अणु"DAC Left Source", "AIF input left", "AIFIN Left"पूर्ण,
	अणु"DAC Left Source", "AIF input right", "AIFIN Right"पूर्ण,

	अणु"DAC Right Source", "ADC output left", "ADC Left"पूर्ण,
	अणु"DAC Right Source", "ADC output right", "ADC Right"पूर्ण,
	अणु"DAC Right Source", "AIF input left", "AIFIN Left"पूर्ण,
	अणु"DAC Right Source", "AIF input right", "AIFIN Right"पूर्ण,

	अणु"DAC Left", शून्य, "DAC Left Source"पूर्ण,
	अणु"DAC Right", शून्य, "DAC Right Source"पूर्ण,

	अणु"Out Mixer Left", "Aux Left Switch", "Aux Left"पूर्ण,
	अणु"Out Mixer Left", "Mixin Left Switch", "MIXIN Left"पूर्ण,
	अणु"Out Mixer Left", "Mixin Right Switch", "MIXIN Right"पूर्ण,
	अणु"Out Mixer Left", "Aux Left Invert Switch", "Aux Left"पूर्ण,
	अणु"Out Mixer Left", "Mixin Left Invert Switch", "MIXIN Left"पूर्ण,
	अणु"Out Mixer Left", "Mixin Right Invert Switch", "MIXIN Right"पूर्ण,
	अणु"Out Mixer Left", "DAC Left Switch", "DAC Left"पूर्ण,

	अणु"Out Mixer Right", "Aux Right Switch", "Aux Right"पूर्ण,
	अणु"Out Mixer Right", "Mixin Right Switch", "MIXIN Right"पूर्ण,
	अणु"Out Mixer Right", "Mixin Left Switch", "MIXIN Left"पूर्ण,
	अणु"Out Mixer Right", "Aux Right Invert Switch", "Aux Right"पूर्ण,
	अणु"Out Mixer Right", "Mixin Right Invert Switch", "MIXIN Right"पूर्ण,
	अणु"Out Mixer Right", "Mixin Left Invert Switch", "MIXIN Left"पूर्ण,
	अणु"Out Mixer Right", "DAC Right Switch", "DAC Right"पूर्ण,

	अणु"MIXOUT Left", शून्य, "Out Mixer Left"पूर्ण,
	अणु"Headphone Left Enable", "Switch", "MIXOUT Left"पूर्ण,
	अणु"Headphone Left", शून्य, "Headphone Left Enable"पूर्ण,
	अणु"Headphone Left", शून्य, "Charge Pump"पूर्ण,
	अणु"HPL", शून्य, "Headphone Left"पूर्ण,

	अणु"MIXOUT Right", शून्य, "Out Mixer Right"पूर्ण,
	अणु"Headphone Right Enable", "Switch", "MIXOUT Right"पूर्ण,
	अणु"Headphone Right", शून्य, "Headphone Right Enable"पूर्ण,
	अणु"Headphone Right", शून्य, "Charge Pump"पूर्ण,
	अणु"HPR", शून्य, "Headphone Right"पूर्ण,

	अणु"MIXOUT Right", शून्य, "Out Mixer Right"पूर्ण,
	अणु"Lineout Enable", "Switch", "MIXOUT Right"पूर्ण,
	अणु"Lineout", शून्य, "Lineout Enable"पूर्ण,
	अणु"LINE", शून्य, "Lineout"पूर्ण,
पूर्ण;

/* Codec निजी data */
काष्ठा da9055_priv अणु
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक mclk_rate;
	पूर्णांक master;
	काष्ठा da9055_platक्रमm_data *pdata;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष da9055_reg_शेषs[] = अणु
	अणु 0x21, 0x10 पूर्ण,
	अणु 0x22, 0x0A पूर्ण,
	अणु 0x23, 0x00 पूर्ण,
	अणु 0x24, 0x00 पूर्ण,
	अणु 0x25, 0x00 पूर्ण,
	अणु 0x26, 0x00 पूर्ण,
	अणु 0x27, 0x0C पूर्ण,
	अणु 0x28, 0x01 पूर्ण,
	अणु 0x29, 0x08 पूर्ण,
	अणु 0x2A, 0x32 पूर्ण,
	अणु 0x2B, 0x00 पूर्ण,
	अणु 0x30, 0x35 पूर्ण,
	अणु 0x31, 0x35 पूर्ण,
	अणु 0x32, 0x00 पूर्ण,
	अणु 0x33, 0x00 पूर्ण,
	अणु 0x34, 0x03 पूर्ण,
	अणु 0x35, 0x03 पूर्ण,
	अणु 0x36, 0x6F पूर्ण,
	अणु 0x37, 0x6F पूर्ण,
	अणु 0x38, 0x80 पूर्ण,
	अणु 0x39, 0x01 पूर्ण,
	अणु 0x3A, 0x01 पूर्ण,
	अणु 0x40, 0x00 पूर्ण,
	अणु 0x41, 0x88 पूर्ण,
	अणु 0x42, 0x88 पूर्ण,
	अणु 0x43, 0x08 पूर्ण,
	अणु 0x44, 0x80 पूर्ण,
	अणु 0x45, 0x6F पूर्ण,
	अणु 0x46, 0x6F पूर्ण,
	अणु 0x47, 0x61 पूर्ण,
	अणु 0x48, 0x35 पूर्ण,
	अणु 0x49, 0x35 पूर्ण,
	अणु 0x4A, 0x35 पूर्ण,
	अणु 0x4B, 0x00 पूर्ण,
	अणु 0x4C, 0x00 पूर्ण,
	अणु 0x60, 0x44 पूर्ण,
	अणु 0x61, 0x44 पूर्ण,
	अणु 0x62, 0x00 पूर्ण,
	अणु 0x63, 0x40 पूर्ण,
	अणु 0x64, 0x40 पूर्ण,
	अणु 0x65, 0x40 पूर्ण,
	अणु 0x66, 0x40 पूर्ण,
	अणु 0x67, 0x40 पूर्ण,
	अणु 0x68, 0x40 पूर्ण,
	अणु 0x69, 0x48 पूर्ण,
	अणु 0x6A, 0x40 पूर्ण,
	अणु 0x6B, 0x41 पूर्ण,
	अणु 0x6C, 0x40 पूर्ण,
	अणु 0x6D, 0x40 पूर्ण,
	अणु 0x6E, 0x10 पूर्ण,
	अणु 0x6F, 0x10 पूर्ण,
	अणु 0x90, 0x80 पूर्ण,
	अणु 0x92, 0x02 पूर्ण,
	अणु 0x93, 0x00 पूर्ण,
	अणु 0x99, 0x00 पूर्ण,
	अणु 0x9A, 0x00 पूर्ण,
	अणु 0x9B, 0x00 पूर्ण,
	अणु 0x9C, 0x3F पूर्ण,
	अणु 0x9D, 0x00 पूर्ण,
	अणु 0x9E, 0x3F पूर्ण,
	अणु 0x9F, 0xFF पूर्ण,
	अणु 0xA0, 0x71 पूर्ण,
	अणु 0xA1, 0x00 पूर्ण,
	अणु 0xA2, 0x00 पूर्ण,
	अणु 0xA6, 0x00 पूर्ण,
	अणु 0xA7, 0x00 पूर्ण,
	अणु 0xAB, 0x00 पूर्ण,
	अणु 0xAC, 0x00 पूर्ण,
	अणु 0xAD, 0x00 पूर्ण,
	अणु 0xAF, 0x08 पूर्ण,
	अणु 0xB0, 0x00 पूर्ण,
	अणु 0xB1, 0x00 पूर्ण,
	अणु 0xB2, 0x00 पूर्ण,
पूर्ण;

अटल bool da9055_अस्थिर_रेजिस्टर(काष्ठा device *dev,
				     अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल DA9055_STATUS1:
	हाल DA9055_PLL_STATUS:
	हाल DA9055_AUX_L_GAIN_STATUS:
	हाल DA9055_AUX_R_GAIN_STATUS:
	हाल DA9055_MIC_L_GAIN_STATUS:
	हाल DA9055_MIC_R_GAIN_STATUS:
	हाल DA9055_MIXIN_L_GAIN_STATUS:
	हाल DA9055_MIXIN_R_GAIN_STATUS:
	हाल DA9055_ADC_L_GAIN_STATUS:
	हाल DA9055_ADC_R_GAIN_STATUS:
	हाल DA9055_DAC_L_GAIN_STATUS:
	हाल DA9055_DAC_R_GAIN_STATUS:
	हाल DA9055_HP_L_GAIN_STATUS:
	हाल DA9055_HP_R_GAIN_STATUS:
	हाल DA9055_LINE_GAIN_STATUS:
	हाल DA9055_ALC_CIC_OP_LVL_DATA:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/* Set DAI word length */
अटल पूर्णांक da9055_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा da9055_priv *da9055 = snd_soc_component_get_drvdata(component);
	u8 aअगर_ctrl, fs;
	u32 sysclk;

	चयन (params_width(params)) अणु
	हाल 16:
		aअगर_ctrl = DA9055_AIF_WORD_S16_LE;
		अवरोध;
	हाल 20:
		aअगर_ctrl = DA9055_AIF_WORD_S20_3LE;
		अवरोध;
	हाल 24:
		aअगर_ctrl = DA9055_AIF_WORD_S24_LE;
		अवरोध;
	हाल 32:
		aअगर_ctrl = DA9055_AIF_WORD_S32_LE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Set AIF क्रमmat */
	snd_soc_component_update_bits(component, DA9055_AIF_CTRL, DA9055_AIF_WORD_LENGTH_MASK,
			    aअगर_ctrl);

	चयन (params_rate(params)) अणु
	हाल 8000:
		fs		= DA9055_SR_8000;
		sysclk		= 3072000;
		अवरोध;
	हाल 11025:
		fs		= DA9055_SR_11025;
		sysclk		= 2822400;
		अवरोध;
	हाल 12000:
		fs		= DA9055_SR_12000;
		sysclk		= 3072000;
		अवरोध;
	हाल 16000:
		fs		= DA9055_SR_16000;
		sysclk		= 3072000;
		अवरोध;
	हाल 22050:
		fs		= DA9055_SR_22050;
		sysclk		= 2822400;
		अवरोध;
	हाल 32000:
		fs		= DA9055_SR_32000;
		sysclk		= 3072000;
		अवरोध;
	हाल 44100:
		fs		= DA9055_SR_44100;
		sysclk		= 2822400;
		अवरोध;
	हाल 48000:
		fs		= DA9055_SR_48000;
		sysclk		= 3072000;
		अवरोध;
	हाल 88200:
		fs		= DA9055_SR_88200;
		sysclk		= 2822400;
		अवरोध;
	हाल 96000:
		fs		= DA9055_SR_96000;
		sysclk		= 3072000;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (da9055->mclk_rate) अणु
		/* PLL Mode, Write actual FS */
		snd_soc_component_ग_लिखो(component, DA9055_SR, fs);
	पूर्ण अन्यथा अणु
		/*
		 * Non-PLL Mode
		 * When PLL is bypassed, chip assumes स्थिरant MCLK of
		 * 12.288MHz and uses sample rate value to भागide this MCLK
		 * to derive its sys clk. As sys clk has to be 256 * Fs, we
		 * need to ग_लिखो स्थिरant sample rate i.e. 48KHz.
		 */
		snd_soc_component_ग_लिखो(component, DA9055_SR, DA9055_SR_48000);
	पूर्ण

	अगर (da9055->mclk_rate && (da9055->mclk_rate != sysclk)) अणु
		/* PLL Mode */
		अगर (!da9055->master) अणु
			/* PLL slave mode, enable PLL and also SRM */
			snd_soc_component_update_bits(component, DA9055_PLL_CTRL,
					    DA9055_PLL_EN | DA9055_PLL_SRM_EN,
					    DA9055_PLL_EN | DA9055_PLL_SRM_EN);
		पूर्ण अन्यथा अणु
			/* PLL master mode, only enable PLL */
			snd_soc_component_update_bits(component, DA9055_PLL_CTRL,
					    DA9055_PLL_EN, DA9055_PLL_EN);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Non PLL Mode, disable PLL */
		snd_soc_component_update_bits(component, DA9055_PLL_CTRL, DA9055_PLL_EN, 0);
	पूर्ण

	वापस 0;
पूर्ण

/* Set DAI mode and Format */
अटल पूर्णांक da9055_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा da9055_priv *da9055 = snd_soc_component_get_drvdata(component);
	u8 aअगर_clk_mode, aअगर_ctrl, mode;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		/* DA9055 in I2S Master Mode */
		mode = 1;
		aअगर_clk_mode = DA9055_AIF_CLK_EN_MASTER_MODE;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		/* DA9055 in I2S Slave Mode */
		mode = 0;
		aअगर_clk_mode = DA9055_AIF_CLK_EN_SLAVE_MODE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Don't allow change of mode अगर PLL is enabled */
	अगर ((snd_soc_component_पढ़ो(component, DA9055_PLL_CTRL) & DA9055_PLL_EN) &&
	    (da9055->master != mode))
		वापस -EINVAL;

	da9055->master = mode;

	/* Only I2S is supported */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		aअगर_ctrl = DA9055_AIF_FORMAT_I2S_MODE;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		aअगर_ctrl = DA9055_AIF_FORMAT_LEFT_J;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		aअगर_ctrl = DA9055_AIF_FORMAT_RIGHT_J;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		aअगर_ctrl = DA9055_AIF_FORMAT_DSP;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* By शेष only 32 BCLK per WCLK is supported */
	aअगर_clk_mode |= DA9055_AIF_BCLKS_PER_WCLK_32;

	snd_soc_component_update_bits(component, DA9055_AIF_CLK_MODE,
			    (DA9055_AIF_CLK_MODE_MASK | DA9055_AIF_BCLK_MASK),
			    aअगर_clk_mode);
	snd_soc_component_update_bits(component, DA9055_AIF_CTRL, DA9055_AIF_FORMAT_MASK,
			    aअगर_ctrl);
	वापस 0;
पूर्ण

अटल पूर्णांक da9055_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	अगर (mute) अणु
		snd_soc_component_update_bits(component, DA9055_DAC_L_CTRL,
				    DA9055_DAC_L_MUTE_EN, DA9055_DAC_L_MUTE_EN);
		snd_soc_component_update_bits(component, DA9055_DAC_R_CTRL,
				    DA9055_DAC_R_MUTE_EN, DA9055_DAC_R_MUTE_EN);
	पूर्ण अन्यथा अणु
		snd_soc_component_update_bits(component, DA9055_DAC_L_CTRL,
				    DA9055_DAC_L_MUTE_EN, 0);
		snd_soc_component_update_bits(component, DA9055_DAC_R_CTRL,
				    DA9055_DAC_R_MUTE_EN, 0);
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा DA9055_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल पूर्णांक da9055_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
				 पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा da9055_priv *da9055 = snd_soc_component_get_drvdata(component);

	चयन (clk_id) अणु
	हाल DA9055_CLKSRC_MCLK:
		चयन (freq) अणु
		हाल 11289600:
		हाल 12000000:
		हाल 12288000:
		हाल 13000000:
		हाल 13500000:
		हाल 14400000:
		हाल 19200000:
		हाल 19680000:
		हाल 19800000:
			da9055->mclk_rate = freq;
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

/*
 * da9055_set_dai_pll	: Configure the codec PLL
 * @param codec_dai	: Poपूर्णांकer to codec DAI
 * @param pll_id	: da9055 has only one pll, so pll_id is always zero
 * @param fref		: Input MCLK frequency
 * @param fout		: FsDM value
 * @वापस पूर्णांक		: Zero क्रम success, negative error code क्रम error
 *
 * Note: Supported PLL input frequencies are 11.2896MHz, 12MHz, 12.288MHz,
 *	 13MHz, 13.5MHz, 14.4MHz, 19.2MHz, 19.6MHz and 19.8MHz
 */
अटल पूर्णांक da9055_set_dai_pll(काष्ठा snd_soc_dai *codec_dai, पूर्णांक pll_id,
			      पूर्णांक source, अचिन्हित पूर्णांक fref, अचिन्हित पूर्णांक fout)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा da9055_priv *da9055 = snd_soc_component_get_drvdata(component);

	u8 pll_frac_top, pll_frac_bot, pll_पूर्णांकeger, cnt;

	/* Disable PLL beक्रमe setting the भागisors */
	snd_soc_component_update_bits(component, DA9055_PLL_CTRL, DA9055_PLL_EN, 0);

	/* In slave mode, there is only one set of भागisors */
	अगर (!da9055->master && (fout != 2822400))
		जाओ pll_err;

	/* Search pll भाग array क्रम correct भागisors */
	क्रम (cnt = 0; cnt < ARRAY_SIZE(da9055_pll_भाग); cnt++) अणु
		/* Check fref, mode  and fout */
		अगर ((fref == da9055_pll_भाग[cnt].fref) &&
		    (da9055->master ==  da9055_pll_भाग[cnt].mode) &&
		    (fout == da9055_pll_भाग[cnt].fout)) अणु
			/* All match, pick up भागisors */
			pll_frac_top = da9055_pll_भाग[cnt].frac_top;
			pll_frac_bot = da9055_pll_भाग[cnt].frac_bot;
			pll_पूर्णांकeger = da9055_pll_भाग[cnt].पूर्णांकeger;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (cnt >= ARRAY_SIZE(da9055_pll_भाग))
		जाओ pll_err;

	/* Write PLL भागiders */
	snd_soc_component_ग_लिखो(component, DA9055_PLL_FRAC_TOP, pll_frac_top);
	snd_soc_component_ग_लिखो(component, DA9055_PLL_FRAC_BOT, pll_frac_bot);
	snd_soc_component_ग_लिखो(component, DA9055_PLL_INTEGER, pll_पूर्णांकeger);

	वापस 0;
pll_err:
	dev_err(codec_dai->dev, "Error in setting up PLL\n");
	वापस -EINVAL;
पूर्ण

/* DAI operations */
अटल स्थिर काष्ठा snd_soc_dai_ops da9055_dai_ops = अणु
	.hw_params	= da9055_hw_params,
	.set_fmt	= da9055_set_dai_fmt,
	.set_sysclk	= da9055_set_dai_sysclk,
	.set_pll	= da9055_set_dai_pll,
	.mute_stream	= da9055_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver da9055_dai = अणु
	.name = "da9055-hifi",
	/* Playback Capabilities */
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = DA9055_FORMATS,
	पूर्ण,
	/* Capture Capabilities */
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_96000,
		.क्रमmats = DA9055_FORMATS,
	पूर्ण,
	.ops = &da9055_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल पूर्णांक da9055_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			/* Enable VMID reference & master bias */
			snd_soc_component_update_bits(component, DA9055_REFERENCES,
					    DA9055_VMID_EN | DA9055_BIAS_EN,
					    DA9055_VMID_EN | DA9055_BIAS_EN);
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		/* Disable VMID reference & master bias */
		snd_soc_component_update_bits(component, DA9055_REFERENCES,
				    DA9055_VMID_EN | DA9055_BIAS_EN, 0);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक da9055_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा da9055_priv *da9055 = snd_soc_component_get_drvdata(component);

	/* Enable all Gain Ramps */
	snd_soc_component_update_bits(component, DA9055_AUX_L_CTRL,
			    DA9055_GAIN_RAMPING_EN, DA9055_GAIN_RAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_AUX_R_CTRL,
			    DA9055_GAIN_RAMPING_EN, DA9055_GAIN_RAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_MIXIN_L_CTRL,
			    DA9055_GAIN_RAMPING_EN, DA9055_GAIN_RAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_MIXIN_R_CTRL,
			    DA9055_GAIN_RAMPING_EN, DA9055_GAIN_RAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_ADC_L_CTRL,
			    DA9055_GAIN_RAMPING_EN, DA9055_GAIN_RAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_ADC_R_CTRL,
			    DA9055_GAIN_RAMPING_EN, DA9055_GAIN_RAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_DAC_L_CTRL,
			    DA9055_GAIN_RAMPING_EN, DA9055_GAIN_RAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_DAC_R_CTRL,
			    DA9055_GAIN_RAMPING_EN, DA9055_GAIN_RAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_HP_L_CTRL,
			    DA9055_GAIN_RAMPING_EN, DA9055_GAIN_RAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_HP_R_CTRL,
			    DA9055_GAIN_RAMPING_EN, DA9055_GAIN_RAMPING_EN);
	snd_soc_component_update_bits(component, DA9055_LINE_CTRL,
			    DA9055_GAIN_RAMPING_EN, DA9055_GAIN_RAMPING_EN);

	/*
	 * There are two separate control bits क्रम input and output mixers.
	 * One to enable corresponding amplअगरier and other to enable its
	 * output. As amplअगरier bits are related to घातer control, they are
	 * being managed by DAPM जबतक other (non घातer related) bits are
	 * enabled here
	 */
	snd_soc_component_update_bits(component, DA9055_MIXIN_L_CTRL,
			    DA9055_MIXIN_L_MIX_EN, DA9055_MIXIN_L_MIX_EN);
	snd_soc_component_update_bits(component, DA9055_MIXIN_R_CTRL,
			    DA9055_MIXIN_R_MIX_EN, DA9055_MIXIN_R_MIX_EN);

	snd_soc_component_update_bits(component, DA9055_MIXOUT_L_CTRL,
			    DA9055_MIXOUT_L_MIX_EN, DA9055_MIXOUT_L_MIX_EN);
	snd_soc_component_update_bits(component, DA9055_MIXOUT_R_CTRL,
			    DA9055_MIXOUT_R_MIX_EN, DA9055_MIXOUT_R_MIX_EN);

	/* Set this as per your प्रणाली configuration */
	snd_soc_component_ग_लिखो(component, DA9055_PLL_CTRL, DA9055_PLL_INDIV_10_20_MHZ);

	/* Set platक्रमm data values */
	अगर (da9055->pdata) अणु
		/* set mic bias source */
		अगर (da9055->pdata->micbias_source) अणु
			snd_soc_component_update_bits(component, DA9055_MIXIN_R_SELECT,
					    DA9055_MICBIAS2_EN,
					    DA9055_MICBIAS2_EN);
		पूर्ण अन्यथा अणु
			snd_soc_component_update_bits(component, DA9055_MIXIN_R_SELECT,
					    DA9055_MICBIAS2_EN, 0);
		पूर्ण
		/* set mic bias voltage */
		चयन (da9055->pdata->micbias) अणु
		हाल DA9055_MICBIAS_2_2V:
		हाल DA9055_MICBIAS_2_1V:
		हाल DA9055_MICBIAS_1_8V:
		हाल DA9055_MICBIAS_1_6V:
			snd_soc_component_update_bits(component, DA9055_MIC_CONFIG,
					    DA9055_MICBIAS_LEVEL_MASK,
					    (da9055->pdata->micbias) << 4);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_da9055 = अणु
	.probe			= da9055_probe,
	.set_bias_level		= da9055_set_bias_level,
	.controls		= da9055_snd_controls,
	.num_controls		= ARRAY_SIZE(da9055_snd_controls),
	.dapm_widमाला_लो		= da9055_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(da9055_dapm_widमाला_लो),
	.dapm_routes		= da9055_audio_map,
	.num_dapm_routes	= ARRAY_SIZE(da9055_audio_map),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config da9055_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.reg_शेषs = da9055_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(da9055_reg_शेषs),
	.अस्थिर_reg = da9055_अस्थिर_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक da9055_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा da9055_priv *da9055;
	काष्ठा da9055_platक्रमm_data *pdata = dev_get_platdata(&i2c->dev);
	पूर्णांक ret;

	da9055 = devm_kzalloc(&i2c->dev, माप(काष्ठा da9055_priv),
			      GFP_KERNEL);
	अगर (!da9055)
		वापस -ENOMEM;

	अगर (pdata)
		da9055->pdata = pdata;

	i2c_set_clientdata(i2c, da9055);

	da9055->regmap = devm_regmap_init_i2c(i2c, &da9055_regmap_config);
	अगर (IS_ERR(da9055->regmap)) अणु
		ret = PTR_ERR(da9055->regmap);
		dev_err(&i2c->dev, "regmap_init() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_da9055, &da9055_dai, 1);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to register da9055 component: %d\n",
			ret);
	पूर्ण
	वापस ret;
पूर्ण

/*
 * DO NOT change the device Ids. The naming is पूर्णांकentionally specअगरic as both
 * the CODEC and PMIC parts of this chip are instantiated separately as I2C
 * devices (both have configurable I2C addresses, and are to all पूर्णांकents and
 * purposes separate). As a result there are specअगरic DA9055 Ids क्रम CODEC
 * and PMIC, which must be dअगरferent to operate together.
 */
अटल स्थिर काष्ठा i2c_device_id da9055_i2c_id[] = अणु
	अणु "da9055-codec", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, da9055_i2c_id);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id da9055_of_match[] = अणु
	अणु .compatible = "dlg,da9055-codec", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, da9055_of_match);
#पूर्ण_अगर

/* I2C codec control layer */
अटल काष्ठा i2c_driver da9055_i2c_driver = अणु
	.driver = अणु
		.name = "da9055-codec",
		.of_match_table = of_match_ptr(da9055_of_match),
	पूर्ण,
	.probe		= da9055_i2c_probe,
	.id_table	= da9055_i2c_id,
पूर्ण;

module_i2c_driver(da9055_i2c_driver);

MODULE_DESCRIPTION("ASoC DA9055 Codec driver");
MODULE_AUTHOR("David Chen, Ashish Chavan");
MODULE_LICENSE("GPL");
