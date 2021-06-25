<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ALSA SoC TLV320AIC3X codec driver
 *
 * Author:      Vladimir Barinov, <vbarinov@embeddedalley.com>
 * Copyright:   (C) 2007 MontaVista Software, Inc., <source@mvista.com>
 */

#अगर_अघोषित _AIC3X_H
#घोषणा _AIC3X_H

काष्ठा device;
काष्ठा regmap_config;

बाह्य स्थिर काष्ठा regmap_config aic3x_regmap;
पूर्णांक aic3x_probe(काष्ठा device *dev, काष्ठा regmap *regmap, kernel_uदीर्घ_t driver_data);
पूर्णांक aic3x_हटाओ(काष्ठा device *dev);

#घोषणा AIC3X_MODEL_3X 0
#घोषणा AIC3X_MODEL_33 1
#घोषणा AIC3X_MODEL_3007 2
#घोषणा AIC3X_MODEL_3104 3
#घोषणा AIC3X_MODEL_3106 4

/* AIC3X रेजिस्टर space */
#घोषणा AIC3X_CACHEREGNUM		110

/* Page select रेजिस्टर */
#घोषणा AIC3X_PAGE_SELECT		0
/* Software reset रेजिस्टर */
#घोषणा AIC3X_RESET			1
/* Codec Sample rate select रेजिस्टर */
#घोषणा AIC3X_SAMPLE_RATE_SEL_REG	2
/* PLL progrramming रेजिस्टर A */
#घोषणा AIC3X_PLL_PROGA_REG		3
/* PLL progrramming रेजिस्टर B */
#घोषणा AIC3X_PLL_PROGB_REG		4
/* PLL progrramming रेजिस्टर C */
#घोषणा AIC3X_PLL_PROGC_REG		5
/* PLL progrramming रेजिस्टर D */
#घोषणा AIC3X_PLL_PROGD_REG		6
/* Codec datapath setup रेजिस्टर */
#घोषणा AIC3X_CODEC_DATAPATH_REG	7
/* Audio serial data पूर्णांकerface control रेजिस्टर A */
#घोषणा AIC3X_ASD_INTF_CTRLA		8
/* Audio serial data पूर्णांकerface control रेजिस्टर B */
#घोषणा AIC3X_ASD_INTF_CTRLB		9
/* Audio serial data पूर्णांकerface control रेजिस्टर C */
#घोषणा AIC3X_ASD_INTF_CTRLC		10
/* Audio overflow status and PLL R value programming रेजिस्टर */
#घोषणा AIC3X_OVRF_STATUS_AND_PLLR_REG	11
/* Audio codec digital filter control रेजिस्टर */
#घोषणा AIC3X_CODEC_DFILT_CTRL		12
/* Headset/button press detection रेजिस्टर */
#घोषणा AIC3X_HEADSET_DETECT_CTRL_A	13
#घोषणा AIC3X_HEADSET_DETECT_CTRL_B	14
/* ADC PGA Gain control रेजिस्टरs */
#घोषणा LADC_VOL			15
#घोषणा RADC_VOL			16
/* MIC3 control रेजिस्टरs */
#घोषणा MIC3LR_2_LADC_CTRL		17
#घोषणा MIC3LR_2_RADC_CTRL		18
/* Line1 Input control रेजिस्टरs */
#घोषणा LINE1L_2_LADC_CTRL		19
#घोषणा LINE1R_2_LADC_CTRL		21
#घोषणा LINE1R_2_RADC_CTRL		22
#घोषणा LINE1L_2_RADC_CTRL		24
/* Line2 Input control रेजिस्टरs */
#घोषणा LINE2L_2_LADC_CTRL		20
#घोषणा LINE2R_2_RADC_CTRL		23
/* MICBIAS Control Register */
#घोषणा MICBIAS_CTRL			25

/* AGC Control Registers A, B, C */
#घोषणा LAGC_CTRL_A			26
#घोषणा LAGC_CTRL_B			27
#घोषणा LAGC_CTRL_C			28
#घोषणा RAGC_CTRL_A			29
#घोषणा RAGC_CTRL_B			30
#घोषणा RAGC_CTRL_C			31

/* DAC Power and Left High Power Output control रेजिस्टरs */
#घोषणा DAC_PWR				37
#घोषणा HPLCOM_CFG			37
/* Right High Power Output control रेजिस्टरs */
#घोषणा HPRCOM_CFG			38
/* High Power Output Stage Control Register */
#घोषणा HPOUT_SC			40
/* DAC Output Switching control रेजिस्टरs */
#घोषणा DAC_LINE_MUX			41
/* High Power Output Driver Pop Reduction रेजिस्टरs */
#घोषणा HPOUT_POP_REDUCTION		42
/* DAC Digital control रेजिस्टरs */
#घोषणा LDAC_VOL			43
#घोषणा RDAC_VOL			44
/* Left High Power Output control रेजिस्टरs */
#घोषणा LINE2L_2_HPLOUT_VOL		45
#घोषणा PGAL_2_HPLOUT_VOL		46
#घोषणा DACL1_2_HPLOUT_VOL		47
#घोषणा LINE2R_2_HPLOUT_VOL		48
#घोषणा PGAR_2_HPLOUT_VOL		49
#घोषणा DACR1_2_HPLOUT_VOL		50
#घोषणा HPLOUT_CTRL			51
/* Left High Power COM control रेजिस्टरs */
#घोषणा LINE2L_2_HPLCOM_VOL		52
#घोषणा PGAL_2_HPLCOM_VOL		53
#घोषणा DACL1_2_HPLCOM_VOL		54
#घोषणा LINE2R_2_HPLCOM_VOL		55
#घोषणा PGAR_2_HPLCOM_VOL		56
#घोषणा DACR1_2_HPLCOM_VOL		57
#घोषणा HPLCOM_CTRL			58
/* Right High Power Output control रेजिस्टरs */
#घोषणा LINE2L_2_HPROUT_VOL		59
#घोषणा PGAL_2_HPROUT_VOL		60
#घोषणा DACL1_2_HPROUT_VOL		61
#घोषणा LINE2R_2_HPROUT_VOL		62
#घोषणा PGAR_2_HPROUT_VOL		63
#घोषणा DACR1_2_HPROUT_VOL		64
#घोषणा HPROUT_CTRL			65
/* Right High Power COM control रेजिस्टरs */
#घोषणा LINE2L_2_HPRCOM_VOL		66
#घोषणा PGAL_2_HPRCOM_VOL		67
#घोषणा DACL1_2_HPRCOM_VOL		68
#घोषणा LINE2R_2_HPRCOM_VOL		69
#घोषणा PGAR_2_HPRCOM_VOL		70
#घोषणा DACR1_2_HPRCOM_VOL		71
#घोषणा HPRCOM_CTRL			72
/* Mono Line Output Plus/Minus control रेजिस्टरs */
#घोषणा LINE2L_2_MONOLOPM_VOL		73
#घोषणा PGAL_2_MONOLOPM_VOL		74
#घोषणा DACL1_2_MONOLOPM_VOL		75
#घोषणा LINE2R_2_MONOLOPM_VOL		76
#घोषणा PGAR_2_MONOLOPM_VOL		77
#घोषणा DACR1_2_MONOLOPM_VOL		78
#घोषणा MONOLOPM_CTRL			79
/* Class-D speaker driver on tlv320aic3007 */
#घोषणा CLASSD_CTRL			73
/* Left Line Output Plus/Minus control रेजिस्टरs */
#घोषणा LINE2L_2_LLOPM_VOL		80
#घोषणा PGAL_2_LLOPM_VOL		81
#घोषणा DACL1_2_LLOPM_VOL		82
#घोषणा LINE2R_2_LLOPM_VOL		83
#घोषणा PGAR_2_LLOPM_VOL		84
#घोषणा DACR1_2_LLOPM_VOL		85
#घोषणा LLOPM_CTRL			86
/* Right Line Output Plus/Minus control रेजिस्टरs */
#घोषणा LINE2L_2_RLOPM_VOL		87
#घोषणा PGAL_2_RLOPM_VOL		88
#घोषणा DACL1_2_RLOPM_VOL		89
#घोषणा LINE2R_2_RLOPM_VOL		90
#घोषणा PGAR_2_RLOPM_VOL		91
#घोषणा DACR1_2_RLOPM_VOL		92
#घोषणा RLOPM_CTRL			93
/* GPIO/IRQ रेजिस्टरs */
#घोषणा AIC3X_STICKY_IRQ_FLAGS_REG	96
#घोषणा AIC3X_RT_IRQ_FLAGS_REG		97
#घोषणा AIC3X_GPIO1_REG			98
#घोषणा AIC3X_GPIO2_REG			99
#घोषणा AIC3X_GPIOA_REG			100
#घोषणा AIC3X_GPIOB_REG			101
/* Clock generation control रेजिस्टर */
#घोषणा AIC3X_CLKGEN_CTRL_REG		102
/* New AGC रेजिस्टरs */
#घोषणा LAGCN_ATTACK			103
#घोषणा LAGCN_DECAY			104
#घोषणा RAGCN_ATTACK			105
#घोषणा RAGCN_DECAY			106
/* New Programmable ADC Digital Path and I2C Bus Condition Register */
#घोषणा NEW_ADC_DIGITALPATH		107
/* Passive Analog Signal Bypass Selection During Powerकरोwn Register */
#घोषणा PASSIVE_BYPASS			108
/* DAC Quiescent Current Adjusपंचांगent Register */
#घोषणा DAC_ICC_ADJ			109

/* Page select रेजिस्टर bits */
#घोषणा PAGE0_SELECT		0
#घोषणा PAGE1_SELECT		1

/* Audio serial data पूर्णांकerface control रेजिस्टर A bits */
#घोषणा BIT_CLK_MASTER          0x80
#घोषणा WORD_CLK_MASTER         0x40
#घोषणा DOUT_TRISTATE		0x20

/* Codec Datapath setup रेजिस्टर 7 */
#घोषणा FSREF_44100		(1 << 7)
#घोषणा FSREF_48000		(0 << 7)
#घोषणा DUAL_RATE_MODE		((1 << 5) | (1 << 6))
#घोषणा LDAC2LCH		(0x1 << 3)
#घोषणा RDAC2RCH		(0x1 << 1)
#घोषणा LDAC2RCH		(0x2 << 3)
#घोषणा RDAC2LCH		(0x2 << 1)
#घोषणा LDAC2MONOMIX		(0x3 << 3)
#घोषणा RDAC2MONOMIX		(0x3 << 1)

/* PLL रेजिस्टरs bitfields */
#घोषणा PLLP_SHIFT		0
#घोषणा PLLP_MASK		7
#घोषणा PLLQ_SHIFT		3
#घोषणा PLLR_SHIFT		0
#घोषणा PLLJ_SHIFT		2
#घोषणा PLLD_MSB_SHIFT		0
#घोषणा PLLD_LSB_SHIFT		2

/* Clock generation रेजिस्टर bits */
#घोषणा CODEC_CLKIN_PLLDIV	0
#घोषणा CODEC_CLKIN_CLKDIV	1
#घोषणा PLL_CLKIN_SHIFT		4
#घोषणा MCLK_SOURCE		0x0
#घोषणा PLL_CLKDIV_SHIFT	0
#घोषणा PLLCLK_IN_MASK		0x30
#घोषणा PLLCLK_IN_SHIFT		4
#घोषणा CLKDIV_IN_MASK		0xc0
#घोषणा CLKDIV_IN_SHIFT		6
/* घड़ी in source */
#घोषणा CLKIN_MCLK		0
#घोषणा CLKIN_GPIO2		1
#घोषणा CLKIN_BCLK		2

/* Software reset रेजिस्टर bits */
#घोषणा SOFT_RESET		0x80

/* PLL progrramming रेजिस्टर A bits */
#घोषणा PLL_ENABLE		0x80

/* Route bits */
#घोषणा ROUTE_ON		0x80

/* Mute bits */
#घोषणा UNMUTE			0x08
#घोषणा MUTE_ON			0x80

/* Power bits */
#घोषणा LADC_PWR_ON		0x04
#घोषणा RADC_PWR_ON		0x04
#घोषणा LDAC_PWR_ON		0x80
#घोषणा RDAC_PWR_ON		0x40
#घोषणा HPLOUT_PWR_ON		0x01
#घोषणा HPROUT_PWR_ON		0x01
#घोषणा HPLCOM_PWR_ON		0x01
#घोषणा HPRCOM_PWR_ON		0x01
#घोषणा MONOLOPM_PWR_ON		0x01
#घोषणा LLOPM_PWR_ON		0x01
#घोषणा RLOPM_PWR_ON	0x01

#घोषणा INVERT_VOL(val)   (0x7f - val)

/* Default output volume (inverted) */
#घोषणा DEFAULT_VOL     INVERT_VOL(0x50)
/* Default input volume */
#घोषणा DEFAULT_GAIN    0x20

/* MICBIAS Control Register */
#घोषणा MICBIAS_LEVEL_SHIFT	(6)
#घोषणा MICBIAS_LEVEL_MASK	(3 << 6)

/* HPOUT_SC */
#घोषणा HPOUT_SC_OCMV_MASK	(3 << 6)
#घोषणा HPOUT_SC_OCMV_SHIFT	(6)
#घोषणा HPOUT_SC_OCMV_1_35V	0
#घोषणा HPOUT_SC_OCMV_1_5V	1
#घोषणा HPOUT_SC_OCMV_1_65V	2
#घोषणा HPOUT_SC_OCMV_1_8V	3

/* headset detection / button API */

/* The AIC3x supports detection of stereo headsets (GND + left + right संकेत)
 * and cellular headsets (GND + speaker output + microphone input).
 * It is recommended to enable MIC bias क्रम this function to work properly.
 * For more inक्रमmation, please refer to the datasheet. */
क्रमागत अणु
	AIC3X_HEADSET_DETECT_OFF	= 0,
	AIC3X_HEADSET_DETECT_STEREO	= 1,
	AIC3X_HEADSET_DETECT_CELLULAR   = 2,
	AIC3X_HEADSET_DETECT_BOTH	= 3
पूर्ण;

क्रमागत अणु
	AIC3X_HEADSET_DEBOUNCE_16MS	= 0,
	AIC3X_HEADSET_DEBOUNCE_32MS	= 1,
	AIC3X_HEADSET_DEBOUNCE_64MS	= 2,
	AIC3X_HEADSET_DEBOUNCE_128MS	= 3,
	AIC3X_HEADSET_DEBOUNCE_256MS	= 4,
	AIC3X_HEADSET_DEBOUNCE_512MS	= 5
पूर्ण;

क्रमागत अणु
	AIC3X_BUTTON_DEBOUNCE_0MS	= 0,
	AIC3X_BUTTON_DEBOUNCE_8MS	= 1,
	AIC3X_BUTTON_DEBOUNCE_16MS	= 2,
	AIC3X_BUTTON_DEBOUNCE_32MS	= 3
पूर्ण;

#घोषणा AIC3X_HEADSET_DETECT_ENABLED	0x80
#घोषणा AIC3X_HEADSET_DETECT_SHIFT	5
#घोषणा AIC3X_HEADSET_DETECT_MASK	3
#घोषणा AIC3X_HEADSET_DEBOUNCE_SHIFT	2
#घोषणा AIC3X_HEADSET_DEBOUNCE_MASK	7
#घोषणा AIC3X_BUTTON_DEBOUNCE_SHIFT 	0
#घोषणा AIC3X_BUTTON_DEBOUNCE_MASK	3

#पूर्ण_अगर /* _AIC3X_H */
