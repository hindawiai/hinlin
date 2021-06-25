<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * cs35l33.h -- CS35L33 ALSA SoC audio driver
 *
 * Copyright 2016 Cirrus Logic, Inc.
 *
 * Author: Paul Handrigan <paul.handrigan@cirrus.com>
 */

#अगर_अघोषित __CS35L33_H__
#घोषणा __CS35L33_H__

#घोषणा CS35L33_CHIP_ID		0x00035A33
#घोषणा CS35L33_DEVID_AB	0x01	/* Device ID A & B [RO] */
#घोषणा CS35L33_DEVID_CD	0x02	/* Device ID C & D [RO] */
#घोषणा CS35L33_DEVID_E		0x03	/* Device ID E [RO] */
#घोषणा CS35L33_FAB_ID		0x04	/* Fab ID [RO] */
#घोषणा CS35L33_REV_ID		0x05	/* Revision ID [RO] */
#घोषणा CS35L33_PWRCTL1		0x06	/* Power Ctl 1 */
#घोषणा CS35L33_PWRCTL2		0x07	/* Power Ctl 2 */
#घोषणा CS35L33_CLK_CTL		0x08	/* Clock Ctl */
#घोषणा CS35L33_BST_PEAK_CTL	0x09	/* Max Current क्रम Boost */
#घोषणा CS35L33_PROTECT_CTL	0x0A	/* Amp Protection Parameters */
#घोषणा CS35L33_BST_CTL1	0x0B	/* Boost Converter CTL1 */
#घोषणा CS35L33_BST_CTL2	0x0C	/* Boost Converter CTL2 */
#घोषणा CS35L33_ADSP_CTL	0x0D	/* Serial Port Control */
#घोषणा CS35L33_ADC_CTL		0x0E	/* ADC Control */
#घोषणा CS35L33_DAC_CTL		0x0F	/* DAC Control */
#घोषणा CS35L33_DIG_VOL_CTL	0x10	/* Digital Volume CTL */
#घोषणा CS35L33_CLASSD_CTL	0x11	/* Class D Amp CTL */
#घोषणा CS35L33_AMP_CTL		0x12	/* Amp Gain/Protecton Release CTL */
#घोषणा CS35L33_INT_MASK_1	0x13	/* Interrupt Mask 1 */
#घोषणा CS35L33_INT_MASK_2	0x14	/* Interrupt Mask 2 */
#घोषणा CS35L33_INT_STATUS_1	0x15	/* Interrupt Status 1 [RO] */
#घोषणा CS35L33_INT_STATUS_2	0x16	/* Interrupt Status 2 [RO] */
#घोषणा CS35L33_DIAG_LOCK	0x17	/* Diagnostic Mode Register Lock */
#घोषणा CS35L33_DIAG_CTRL_1	0x18	/* Diagnostic Mode Register Control */
#घोषणा CS35L33_DIAG_CTRL_2	0x19	/* Diagnostic Mode Register Control 2 */
#घोषणा CS35L33_HG_MEMLDO_CTL	0x23	/* H/G Memory/LDO CTL */
#घोषणा CS35L33_HG_REL_RATE	0x24	/* H/G Release Rate */
#घोषणा CS35L33_LDO_DEL		0x25	/* LDO Entry Delay/VPhg Control 1 */
#घोषणा CS35L33_HG_HEAD		0x29	/* H/G Headroom */
#घोषणा CS35L33_HG_EN		0x2A	/* H/G Enable/VPhg CNT2 */
#घोषणा CS35L33_TX_VMON		0x2D	/* TDM TX Control 1 (VMON) */
#घोषणा CS35L33_TX_IMON		0x2E	/* TDM TX Control 2 (IMON) */
#घोषणा CS35L33_TX_VPMON	0x2F	/* TDM TX Control 3 (VPMON) */
#घोषणा CS35L33_TX_VBSTMON	0x30	/* TDM TX Control 4 (VBSTMON) */
#घोषणा CS35L33_TX_FLAG		0x31	/* TDM TX Control 5 (FLAG) */
#घोषणा CS35L33_TX_EN1		0x32	/* TDM TX Enable 1 */
#घोषणा CS35L33_TX_EN2		0x33	/* TDM TX Enable 2 */
#घोषणा CS35L33_TX_EN3		0x34	/* TDM TX Enable 3 */
#घोषणा CS35L33_TX_EN4		0x35	/* TDM TX Enable 4 */
#घोषणा CS35L33_RX_AUD		0x36	/* TDM RX Control 1 */
#घोषणा CS35L33_RX_SPLY		0x37	/* TDM RX Control 2 */
#घोषणा CS35L33_RX_ALIVE	0x38	/* TDM RX Control 3 */
#घोषणा CS35L33_BST_CTL4	0x39	/* Boost Converter Control 4 */
#घोषणा CS35L33_HG_STATUS	0x3F	/* H/G Status */
#घोषणा CS35L33_MAX_REGISTER	0x59

#घोषणा CS35L33_MCLK_5644	5644800
#घोषणा CS35L33_MCLK_6144	6144000
#घोषणा CS35L33_MCLK_6		6000000
#घोषणा CS35L33_MCLK_11289	11289600
#घोषणा CS35L33_MCLK_12		12000000
#घोषणा CS35L33_MCLK_12288	12288000

/* CS35L33_PWRCTL1 */
#घोषणा CS35L33_PDN_AMP			(1 << 7)
#घोषणा CS35L33_PDN_BST			(1 << 2)
#घोषणा CS35L33_PDN_ALL			1

/* CS35L33_PWRCTL2 */
#घोषणा CS35L33_PDN_VMON_SHIFT		7
#घोषणा CS35L33_PDN_VMON		(1 << CS35L33_PDN_VMON_SHIFT)
#घोषणा CS35L33_PDN_IMON_SHIFT		6
#घोषणा CS35L33_PDN_IMON		(1 << CS35L33_PDN_IMON_SHIFT)
#घोषणा CS35L33_PDN_VPMON_SHIFT		5
#घोषणा CS35L33_PDN_VPMON		(1 << CS35L33_PDN_VPMON_SHIFT)
#घोषणा CS35L33_PDN_VBSTMON_SHIFT	4
#घोषणा CS35L33_PDN_VBSTMON		(1 << CS35L33_PDN_VBSTMON_SHIFT)
#घोषणा CS35L33_SDOUT_3ST_I2S_SHIFT	3
#घोषणा CS35L33_SDOUT_3ST_I2S		(1 << CS35L33_SDOUT_3ST_I2S_SHIFT)
#घोषणा CS35L33_PDN_SDIN_SHIFT		2
#घोषणा CS35L33_PDN_SDIN		(1 << CS35L33_PDN_SDIN_SHIFT)
#घोषणा CS35L33_PDN_TDM_SHIFT		1
#घोषणा CS35L33_PDN_TDM			(1 << CS35L33_PDN_TDM_SHIFT)

/* CS35L33_CLK_CTL */
#घोषणा CS35L33_MCLKDIS			(1 << 7)
#घोषणा CS35L33_MCLKDIV2		(1 << 6)
#घोषणा CS35L33_SDOUT_3ST_TDM		(1 << 5)
#घोषणा CS35L33_INT_FS_RATE		(1 << 4)
#घोषणा CS35L33_ADSP_FS			0xF

/* CS35L33_PROTECT_CTL */
#घोषणा CS35L33_ALIVE_WD_DIS		(3 << 2)

/* CS35L33_BST_CTL1 */
#घोषणा CS35L33_BST_CTL_SRC		(1 << 6)
#घोषणा CS35L33_BST_CTL_SHIFT		(1 << 5)
#घोषणा CS35L33_BST_CTL_MASK		0x3F

/* CS35L33_BST_CTL2 */
#घोषणा CS35L33_TDM_WD_SEL		(1 << 4)
#घोषणा CS35L33_ALIVE_WD_DIS2		(1 << 3)
#घोषणा CS35L33_VBST_SR_STEP		0x3

/* CS35L33_ADSP_CTL */
#घोषणा CS35L33_ADSP_DRIVE		(1 << 7)
#घोषणा CS35L33_MS_MASK			(1 << 6)
#घोषणा CS35L33_SDIN_LOC		(3 << 4)
#घोषणा CS35L33_ALIVE_RATE		0x3

/* CS35L33_ADC_CTL */
#घोषणा CS35L33_INV_VMON		(1 << 7)
#घोषणा CS35L33_INV_IMON		(1 << 6)
#घोषणा CS35L33_ADC_NOTCH_DIS		(1 << 5)
#घोषणा CS35L33_IMON_SCALE		0xF

/* CS35L33_DAC_CTL */
#घोषणा CS35L33_INV_DAC			(1 << 7)
#घोषणा CS35L33_DAC_NOTCH_DIS		(1 << 5)
#घोषणा CS35L33_DIGSFT			(1 << 4)
#घोषणा CS35L33_DSR_RATE		0xF

/* CS35L33_CLASSD_CTL */
#घोषणा CS35L33_AMP_SD			(1 << 6)
#घोषणा CS35L33_AMP_DRV_SEL_SRC		(1 << 5)
#घोषणा CS35L33_AMP_DRV_SEL_MASK	0x10
#घोषणा CS35L33_AMP_DRV_SEL_SHIFT	4
#घोषणा CS35L33_AMP_CAL			(1 << 3)
#घोषणा CS35L33_GAIN_CHG_ZC_MASK	0x04
#घोषणा CS35L33_GAIN_CHG_ZC_SHIFT	2
#घोषणा CS35L33_CLASS_D_CTL_MASK	0x3F

/* CS35L33_AMP_CTL */
#घोषणा CS35L33_AMP_GAIN		0xF0
#घोषणा CS35L33_CAL_ERR_RLS		(1 << 3)
#घोषणा CS35L33_AMP_SHORT_RLS		(1 << 2)
#घोषणा CS35L33_OTW_RLS			(1 << 1)
#घोषणा CS35L33_OTE_RLS			1

/* CS35L33_INT_MASK_1 */
#घोषणा CS35L33_M_CAL_ERR_SHIFT		6
#घोषणा CS35L33_M_CAL_ERR		(1 << CS35L33_M_CAL_ERR_SHIFT)
#घोषणा CS35L33_M_ALIVE_ERR_SHIFT	5
#घोषणा CS35L33_M_ALIVE_ERR		(1 << CS35L33_M_ALIVE_ERR_SHIFT)
#घोषणा CS35L33_M_AMP_SHORT_SHIFT	2
#घोषणा CS35L33_M_AMP_SHORT		(1 << CS35L33_M_AMP_SHORT_SHIFT)
#घोषणा CS35L33_M_OTW_SHIFT		1
#घोषणा CS35L33_M_OTW			(1 << CS35L33_M_OTW_SHIFT)
#घोषणा CS35L33_M_OTE_SHIFT		0
#घोषणा CS35L33_M_OTE			(1 << CS35L33_M_OTE_SHIFT)

/* CS35L33_INT_STATUS_1 */
#घोषणा CS35L33_CAL_ERR			(1 << 6)
#घोषणा CS35L33_ALIVE_ERR		(1 << 5)
#घोषणा CS35L33_ADSPCLK_ERR		(1 << 4)
#घोषणा CS35L33_MCLK_ERR		(1 << 3)
#घोषणा CS35L33_AMP_SHORT		(1 << 2)
#घोषणा CS35L33_OTW			(1 << 1)
#घोषणा CS35L33_OTE			(1 << 0)

/* CS35L33_INT_STATUS_2 */
#घोषणा CS35L33_VMON_OVFL		(1 << 7)
#घोषणा CS35L33_IMON_OVFL		(1 << 6)
#घोषणा CS35L33_VPMON_OVFL		(1 << 5)
#घोषणा CS35L33_VBSTMON_OVFL		(1 << 4)
#घोषणा CS35L33_PDN_DONE		1

/* CS35L33_BST_CTL4 */
#घोषणा CS35L33_BST_RGS			0x70
#घोषणा CS35L33_BST_COEFF3		0xF

/* CS35L33_HG_MEMLDO_CTL */
#घोषणा CS35L33_MEM_DEPTH_SHIFT		5
#घोषणा CS35L33_MEM_DEPTH_MASK		(0x3 << CS35L33_MEM_DEPTH_SHIFT)
#घोषणा CS35L33_LDO_THLD_SHIFT		1
#घोषणा CS35L33_LDO_THLD_MASK		(0xF << CS35L33_LDO_THLD_SHIFT)
#घोषणा CS35L33_LDO_DISABLE_SHIFT	0
#घोषणा CS35L33_LDO_DISABLE_MASK	(0x1 << CS35L33_LDO_DISABLE_SHIFT)

/* CS35L33_LDO_DEL */
#घोषणा CS35L33_VP_HG_VA_SHIFT		5
#घोषणा CS35L33_VP_HG_VA_MASK		(0x7 << CS35L33_VP_HG_VA_SHIFT)
#घोषणा CS35L33_LDO_ENTRY_DELAY_SHIFT	2
#घोषणा CS35L33_LDO_ENTRY_DELAY_MASK	(0x7 << CS35L33_LDO_ENTRY_DELAY_SHIFT)
#घोषणा CS35L33_VP_HG_RATE_SHIFT	0
#घोषणा CS35L33_VP_HG_RATE_MASK		(0x3 << CS35L33_VP_HG_RATE_SHIFT)

/* CS35L33_HG_HEAD */
#घोषणा CS35L33_HD_RM_SHIFT		0
#घोषणा CS35L33_HD_RM_MASK		(0x7F << CS35L33_HD_RM_SHIFT)

/* CS35L33_HG_EN */
#घोषणा CS35L33_CLASS_HG_ENA_SHIFT	7
#घोषणा CS35L33_CLASS_HG_EN_MASK	(0x1 << CS35L33_CLASS_HG_ENA_SHIFT)
#घोषणा CS35L33_VP_HG_AUTO_SHIFT	6
#घोषणा CS35L33_VP_HG_AUTO_MASK		(0x1 << 6)
#घोषणा CS35L33_VP_HG_SHIFT		0
#घोषणा CS35L33_VP_HG_MASK		(0x1F << CS35L33_VP_HG_SHIFT)

#घोषणा CS35L33_RATES (SNDRV_PCM_RATE_8000_48000)
#घोषणा CS35L33_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | \
			SNDRV_PCM_FMTBIT_S24_LE)

/* CS35L33_अणुRX,TXपूर्ण_X */
#घोषणा CS35L33_X_STATE_SHIFT		7
#घोषणा CS35L33_X_STATE			(1 << CS35L33_X_STATE_SHIFT)
#घोषणा CS35L33_X_LOC_SHIFT		0
#घोषणा CS35L33_X_LOC			(0x1F << CS35L33_X_LOC_SHIFT)

/* CS35L33_RX_AUD */
#घोषणा CS35L33_AUDIN_RX_DEPTH_SHIFT	5
#घोषणा CS35L33_AUDIN_RX_DEPTH		(0x7 << CS35L33_AUDIN_RX_DEPTH_SHIFT)

#पूर्ण_अगर
