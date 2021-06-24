<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * cs35l35.h -- CS35L35 ALSA SoC audio driver
 *
 * Copyright 2016 Cirrus Logic, Inc.
 *
 * Author: Brian Austin <brian.austin@cirrus.com>
 */

#अगर_अघोषित __CS35L35_H__
#घोषणा __CS35L35_H__

#घोषणा CS35L35_FIRSTREG		0x01
#घोषणा CS35L35_LASTREG			0x7E
#घोषणा CS35L35_CHIP_ID			0x00035A35
#घोषणा CS35L35_DEVID_AB		0x01	/* Device ID A & B [RO] */
#घोषणा CS35L35_DEVID_CD		0x02    /* Device ID C & D [RO] */
#घोषणा CS35L35_DEVID_E			0x03    /* Device ID E [RO] */
#घोषणा CS35L35_FAB_ID			0x04	/* Fab ID [RO] */
#घोषणा CS35L35_REV_ID			0x05	/* Revision ID [RO] */
#घोषणा CS35L35_PWRCTL1			0x06    /* Power Ctl 1 */
#घोषणा CS35L35_PWRCTL2			0x07    /* Power Ctl 2 */
#घोषणा CS35L35_PWRCTL3			0x08	/* Power Ctl 3 */
#घोषणा CS35L35_CLK_CTL1		0x0A	/* Clocking Ctl 1 */
#घोषणा CS35L35_CLK_CTL2		0x0B	/* Clocking Ctl 2 */
#घोषणा CS35L35_CLK_CTL3		0x0C	/* Clocking Ctl 3 */
#घोषणा CS35L35_SP_FMT_CTL1		0x0D	/* Serial Port Format CTL1 */
#घोषणा CS35L35_SP_FMT_CTL2		0x0E	/* Serial Port Format CTL2 */
#घोषणा CS35L35_SP_FMT_CTL3		0x0F	/* Serial Port Format CTL3 */
#घोषणा CS35L35_MAG_COMP_CTL		0x13	/* Magnitude Comp CTL */
#घोषणा CS35L35_AMP_INP_DRV_CTL		0x14	/* Amp Input Drive Ctl */
#घोषणा CS35L35_AMP_DIG_VOL_CTL		0x15	/* Amplअगरier Dig Volume Ctl */
#घोषणा CS35L35_AMP_DIG_VOL		0x16	/* Amplअगरier Dig Volume */
#घोषणा CS35L35_ADV_DIG_VOL		0x17	/* Advisory Digital Volume */
#घोषणा CS35L35_PROTECT_CTL		0x18	/* Amp Gain - Prot Ctl Param */
#घोषणा CS35L35_AMP_GAIN_AUD_CTL	0x19	/* Amp Serial Port Gain Ctl */
#घोषणा CS35L35_AMP_GAIN_PDM_CTL	0x1A	/* Amplअगरier Gain PDM Ctl */
#घोषणा CS35L35_AMP_GAIN_ADV_CTL	0x1B	/* Amplअगरier Gain Ctl */
#घोषणा CS35L35_GPI_CTL			0x1C	/* GPI Ctl */
#घोषणा CS35L35_BST_CVTR_V_CTL		0x1D	/* Boost Conv Voltage Ctl */
#घोषणा CS35L35_BST_PEAK_I		0x1E	/* Boost Conv Peak Current */
#घोषणा CS35L35_BST_RAMP_CTL		0x20	/* Boost Conv Soft Ramp Ctl */
#घोषणा CS35L35_BST_CONV_COEF_1		0x21	/* Boost Conv Coefficients 1 */
#घोषणा CS35L35_BST_CONV_COEF_2		0x22	/* Boost Conv Coefficients 2 */
#घोषणा CS35L35_BST_CONV_SLOPE_COMP	0x23	/* Boost Conv Slope Comp */
#घोषणा CS35L35_BST_CONV_SW_FREQ	0x24	/* Boost Conv L BST SW Freq */
#घोषणा CS35L35_CLASS_H_CTL		0x30	/* CLS H Control */
#घोषणा CS35L35_CLASS_H_HEADRM_CTL	0x31	/* CLS H Headroom Ctl */
#घोषणा CS35L35_CLASS_H_RELEASE_RATE	0x32	/* CLS H Release Rate */
#घोषणा CS35L35_CLASS_H_FET_DRIVE_CTL	0x33	/* CLS H Weak FET Drive Ctl */
#घोषणा CS35L35_CLASS_H_VP_CTL		0x34	/* CLS H VP Ctl */
#घोषणा CS35L35_CLASS_H_STATUS		0x38	/* CLS H Status */
#घोषणा CS35L35_VPBR_CTL		0x3A	/* VPBR Ctl */
#घोषणा CS35L35_VPBR_VOL_CTL		0x3B	/* VPBR Volume Ctl */
#घोषणा CS35L35_VPBR_TIMING_CTL		0x3C	/* VPBR Timing Ctl */
#घोषणा CS35L35_VPBR_MODE_VOL_CTL	0x3D	/* VPBR Mode/Attack Vol Ctl */
#घोषणा CS35L35_VPBR_ATTEN_STATUS	0x4B	/* VPBR Attenuation Status */
#घोषणा CS35L35_SPKR_MON_CTL		0x4E	/* Speaker Monitoring Ctl */
#घोषणा CS35L35_IMON_SCALE_CTL		0x51	/* IMON Scale Ctl */
#घोषणा CS35L35_AUDIN_RXLOC_CTL		0x52	/* Audio Input RX Loc Ctl */
#घोषणा CS35L35_ADVIN_RXLOC_CTL		0x53	/* Advisory Input RX Loc Ctl */
#घोषणा CS35L35_VMON_TXLOC_CTL		0x54	/* VMON TX Loc Ctl */
#घोषणा CS35L35_IMON_TXLOC_CTL		0x55	/* IMON TX Loc Ctl */
#घोषणा CS35L35_VPMON_TXLOC_CTL		0x56	/* VPMON TX Loc Ctl */
#घोषणा CS35L35_VBSTMON_TXLOC_CTL	0x57	/* VBSTMON TX Loc Ctl */
#घोषणा CS35L35_VPBR_STATUS_TXLOC_CTL	0x58	/* VPBR Status TX Loc Ctl */
#घोषणा CS35L35_ZERO_FILL_LOC_CTL	0x59	/* Zero Fill Loc Ctl */
#घोषणा CS35L35_AUDIN_DEPTH_CTL		0x5A	/* Audio Input Depth Ctl */
#घोषणा CS35L35_SPKMON_DEPTH_CTL	0x5B	/* SPK Mon Output Depth Ctl */
#घोषणा CS35L35_SUPMON_DEPTH_CTL	0x5C	/* Supply Mon Out Depth Ctl */
#घोषणा CS35L35_ZEROFILL_DEPTH_CTL	0x5D	/* Zero Fill Mon Output Ctl */
#घोषणा CS35L35_MULT_DEV_SYNCH1		0x62	/* Multidevice Synch */
#घोषणा CS35L35_MULT_DEV_SYNCH2		0x63	/* Multidevice Synch 2 */
#घोषणा CS35L35_PROT_RELEASE_CTL	0x64	/* Protection Release Ctl */
#घोषणा CS35L35_DIAG_MODE_REG_LOCK	0x68	/* Diagnostic Mode Reg Lock */
#घोषणा CS35L35_DIAG_MODE_CTL_1		0x69	/* Diagnostic Mode Ctl 1 */
#घोषणा CS35L35_DIAG_MODE_CTL_2		0x6A	/* Diagnostic Mode Ctl 2 */
#घोषणा CS35L35_INT_MASK_1		0x70	/* Interrupt Mask 1 */
#घोषणा CS35L35_INT_MASK_2		0x71	/* Interrupt Mask 2 */
#घोषणा CS35L35_INT_MASK_3		0x72	/* Interrupt Mask 3 */
#घोषणा CS35L35_INT_MASK_4		0x73	/* Interrupt Mask 4 */
#घोषणा CS35L35_INT_STATUS_1		0x74	/* Interrupt Status 1 */
#घोषणा CS35L35_INT_STATUS_2		0x75	/* Interrupt Status 2 */
#घोषणा CS35L35_INT_STATUS_3		0x76	/* Interrupt Status 3 */
#घोषणा CS35L35_INT_STATUS_4		0x77	/* Interrupt Status 4 */
#घोषणा CS35L35_PLL_STATUS		0x78	/* PLL Status */
#घोषणा CS35L35_OTP_TRIM_STATUS		0x7E	/* OTP Trim Status */

#घोषणा CS35L35_MAX_REGISTER		0x7F

/* CS35L35_PWRCTL1 */
#घोषणा CS35L35_SFT_RST			0x80
#घोषणा CS35L35_DISCHG_FLT		0x02
#घोषणा CS35L35_PDN_ALL			0x01

/* CS35L35_PWRCTL2 */
#घोषणा CS35L35_PDN_VMON		0x80
#घोषणा CS35L35_PDN_IMON		0x40
#घोषणा CS35L35_PDN_CLASSH		0x20
#घोषणा CS35L35_PDN_VPBR		0x10
#घोषणा CS35L35_PDN_BST			0x04
#घोषणा CS35L35_PDN_AMP			0x01

/* CS35L35_PWRCTL3 */
#घोषणा CS35L35_PDN_VBSTMON_OUT		0x10
#घोषणा CS35L35_PDN_VMON_OUT		0x08

#घोषणा CS35L35_AUDIN_DEPTH_MASK	0x03
#घोषणा CS35L35_AUDIN_DEPTH_SHIFT	0
#घोषणा CS35L35_ADVIN_DEPTH_MASK	0x0C
#घोषणा CS35L35_ADVIN_DEPTH_SHIFT	2
#घोषणा CS35L35_SDIN_DEPTH_8		0x01
#घोषणा CS35L35_SDIN_DEPTH_16		0x02
#घोषणा CS35L35_SDIN_DEPTH_24		0x03

#घोषणा CS35L35_SDOUT_DEPTH_8		0x01
#घोषणा CS35L35_SDOUT_DEPTH_12		0x02
#घोषणा CS35L35_SDOUT_DEPTH_16		0x03

#घोषणा CS35L35_AUD_IN_LR_MASK		0x80
#घोषणा CS35L35_AUD_IN_LR_SHIFT		7
#घोषणा CS35L35_ADV_IN_LR_MASK		0x80
#घोषणा CS35L35_ADV_IN_LR_SHIFT		7
#घोषणा CS35L35_AUD_IN_LOC_MASK		0x0F
#घोषणा CS35L35_AUD_IN_LOC_SHIFT	0
#घोषणा CS35L35_ADV_IN_LOC_MASK		0x0F
#घोषणा CS35L35_ADV_IN_LOC_SHIFT	0

#घोषणा CS35L35_IMON_DEPTH_MASK		0x03
#घोषणा CS35L35_IMON_DEPTH_SHIFT	0
#घोषणा CS35L35_VMON_DEPTH_MASK		0x0C
#घोषणा CS35L35_VMON_DEPTH_SHIFT	2
#घोषणा CS35L35_VBSTMON_DEPTH_MASK	0x03
#घोषणा CS35L35_VBSTMON_DEPTH_SHIFT	0
#घोषणा CS35L35_VPMON_DEPTH_MASK	0x0C
#घोषणा CS35L35_VPMON_DEPTH_SHIFT	2
#घोषणा CS35L35_VPBRSTAT_DEPTH_MASK	0x30
#घोषणा CS35L35_VPBRSTAT_DEPTH_SHIFT	4
#घोषणा CS35L35_ZEROFILL_DEPTH_MASK	0x03
#घोषणा CS35L35_ZEROFILL_DEPTH_SHIFT	0x00

#घोषणा CS35L35_MON_TXLOC_MASK		0x3F
#घोषणा CS35L35_MON_TXLOC_SHIFT		0
#घोषणा CS35L35_MON_FRM_MASK		0x80
#घोषणा CS35L35_MON_FRM_SHIFT		7

#घोषणा CS35L35_IMON_SCALE_MASK		0xF8
#घोषणा CS35L35_IMON_SCALE_SHIFT	3

#घोषणा CS35L35_MS_MASK			0x80
#घोषणा CS35L35_MS_SHIFT		7
#घोषणा CS35L35_SPMODE_MASK		0x40
#घोषणा CS35L35_SP_DRV_MASK		0x10
#घोषणा CS35L35_SP_DRV_SHIFT		4
#घोषणा CS35L35_CLK_CTL2_MASK		0xFF
#घोषणा CS35L35_PDM_MODE_MASK		0x40
#घोषणा CS35L35_PDM_MODE_SHIFT		6
#घोषणा CS35L35_CLK_SOURCE_MASK		0x03
#घोषणा CS35L35_CLK_SOURCE_SHIFT	0
#घोषणा CS35L35_CLK_SOURCE_MCLK		0
#घोषणा CS35L35_CLK_SOURCE_SCLK		1
#घोषणा CS35L35_CLK_SOURCE_PDM		2

#घोषणा CS35L35_SP_SCLKS_MASK		0x0F
#घोषणा CS35L35_SP_SCLKS_SHIFT		0x00
#घोषणा CS35L35_SP_SCLKS_16FS		0x03
#घोषणा CS35L35_SP_SCLKS_32FS		0x07
#घोषणा CS35L35_SP_SCLKS_48FS		0x0B
#घोषणा CS35L35_SP_SCLKS_64FS		0x0F
#घोषणा CS35L35_SP_RATE_MASK		0xC0

#घोषणा CS35L35_PDN_BST_MASK		0x06
#घोषणा CS35L35_PDN_BST_FETON_SHIFT	1
#घोषणा CS35L35_PDN_BST_FETOFF_SHIFT	2
#घोषणा CS35L35_PWR2_PDN_MASK		0xE0
#घोषणा CS35L35_PWR3_PDN_MASK		0x1E
#घोषणा CS35L35_PDN_ALL_MASK		0x01
#घोषणा CS35L35_DISCHG_FILT_MASK	0x02
#घोषणा CS35L35_DISCHG_FILT_SHIFT	1
#घोषणा CS35L35_MCLK_DIS_MASK		0x04
#घोषणा CS35L35_MCLK_DIS_SHIFT		2

#घोषणा CS35L35_BST_CTL_MASK		0x7F
#घोषणा CS35L35_BST_CTL_SHIFT		0
#घोषणा CS35L35_BST_IPK_MASK		0x1F
#घोषणा CS35L35_BST_IPK_SHIFT		0
#घोषणा CS35L35_AMP_MUTE_MASK		0x20
#घोषणा CS35L35_AMP_MUTE_SHIFT		5
#घोषणा CS35L35_AMP_GAIN_ZC_MASK	0x10
#घोषणा CS35L35_AMP_GAIN_ZC_SHIFT	4

#घोषणा CS35L35_AMP_DIGSFT_MASK		0x02
#घोषणा CS35L35_AMP_DIGSFT_SHIFT	1

/* CS35L35_SP_FMT_CTL3 */
#घोषणा CS35L35_SP_I2S_DRV_MASK		0x03
#घोषणा CS35L35_SP_I2S_DRV_SHIFT	0

/* Boost Converter Config */
#घोषणा CS35L35_BST_CONV_COEFF_MASK	0xFF
#घोषणा CS35L35_BST_CONV_SLOPE_MASK	0xFF
#घोषणा CS35L35_BST_CONV_LBST_MASK	0x03
#घोषणा CS35L35_BST_CONV_SWFREQ_MASK	0xF0

/* Class H Algorithm Control */
#घोषणा CS35L35_CH_STEREO_MASK		0x40
#घोषणा CS35L35_CH_STEREO_SHIFT		6
#घोषणा CS35L35_CH_BST_OVR_MASK		0x04
#घोषणा CS35L35_CH_BST_OVR_SHIFT	2
#घोषणा CS35L35_CH_BST_LIM_MASK		0x08
#घोषणा CS35L35_CH_BST_LIM_SHIFT	3
#घोषणा CS35L35_CH_MEM_DEPTH_MASK	0x01
#घोषणा CS35L35_CH_MEM_DEPTH_SHIFT	0
#घोषणा CS35L35_CH_HDRM_CTL_MASK	0x3F
#घोषणा CS35L35_CH_HDRM_CTL_SHIFT	0
#घोषणा CS35L35_CH_REL_RATE_MASK	0xFF
#घोषणा CS35L35_CH_REL_RATE_SHIFT	0
#घोषणा CS35L35_CH_WKFET_DIS_MASK	0x80
#घोषणा CS35L35_CH_WKFET_DIS_SHIFT	7
#घोषणा CS35L35_CH_WKFET_DEL_MASK	0x70
#घोषणा CS35L35_CH_WKFET_DEL_SHIFT	4
#घोषणा CS35L35_CH_WKFET_THLD_MASK	0x0F
#घोषणा CS35L35_CH_WKFET_THLD_SHIFT	0
#घोषणा CS35L35_CH_VP_AUTO_MASK		0x80
#घोषणा CS35L35_CH_VP_AUTO_SHIFT	7
#घोषणा CS35L35_CH_VP_RATE_MASK		0x60
#घोषणा CS35L35_CH_VP_RATE_SHIFT	5
#घोषणा CS35L35_CH_VP_MAN_MASK		0x1F
#घोषणा CS35L35_CH_VP_MAN_SHIFT		0

/* CS35L35_PROT_RELEASE_CTL */
#घोषणा CS35L35_CAL_ERR_RLS		0x80
#घोषणा CS35L35_SHORT_RLS		0x04
#घोषणा CS35L35_OTW_RLS			0x02
#घोषणा CS35L35_OTE_RLS			0x01

/* INT Mask Registers */
#घोषणा CS35L35_INT1_CRIT_MASK		0x38
#घोषणा CS35L35_INT2_CRIT_MASK		0xEF
#घोषणा CS35L35_INT3_CRIT_MASK		0xEE
#घोषणा CS35L35_INT4_CRIT_MASK		0xFF

/* PDN DONE Masks */
#घोषणा CS35L35_M_PDN_DONE_SHIFT	4
#घोषणा CS35L35_M_PDN_DONE_MASK		0x10

/* CS35L35_INT_1 */
#घोषणा CS35L35_CAL_ERR			0x80
#घोषणा CS35L35_OTP_ERR			0x40
#घोषणा CS35L35_LRCLK_ERR		0x20
#घोषणा CS35L35_SPCLK_ERR		0x10
#घोषणा CS35L35_MCLK_ERR		0x08
#घोषणा CS35L35_AMP_SHORT		0x04
#घोषणा CS35L35_OTW			0x02
#घोषणा CS35L35_OTE			0x01

/* CS35L35_INT_2 */
#घोषणा CS35L35_PDN_DONE		0x10
#घोषणा CS35L35_VPBR_ERR		0x02
#घोषणा CS35L35_VPBR_CLR		0x01

/* CS35L35_INT_3 */
#घोषणा CS35L35_BST_HIGH		0x10
#घोषणा CS35L35_BST_HIGH_FLAG		0x08
#घोषणा CS35L35_BST_IPK_FLAG		0x04
#घोषणा CS35L35_LBST_SHORT		0x01

/* CS35L35_INT_4 */
#घोषणा CS35L35_VMON_OVFL		0x08
#घोषणा CS35L35_IMON_OVFL		0x04

#घोषणा CS35L35_FORMATS (SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE | \
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

काष्ठा  cs35l35_निजी अणु
	काष्ठा device *dev;
	काष्ठा cs35l35_platक्रमm_data pdata;
	काष्ठा regmap *regmap;
	काष्ठा regulator_bulk_data supplies[2];
	पूर्णांक num_supplies;
	पूर्णांक sysclk;
	पूर्णांक sclk;
	bool pdm_mode;
	bool i2s_mode;
	bool slave_mode;
	/* GPIO क्रम /RST */
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा completion pdn_करोne;
पूर्ण;

अटल स्थिर अक्षर * स्थिर cs35l35_supplies[] = अणु
	"VA",
	"VP",
पूर्ण;

#पूर्ण_अगर
