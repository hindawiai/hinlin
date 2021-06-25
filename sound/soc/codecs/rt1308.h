<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * rt1308.h  --  RT1308 ALSA SoC amplअगरier component driver
 *
 * Copyright 2019 Realtek Semiconductor Corp.
 * Author: Derek Fang <derek.fang@realtek.com>
 *
 */

#अगर_अघोषित _RT1308_H_
#घोषणा _RT1308_H_

#घोषणा RT1308_DEVICE_ID_NUM			0x10ec1300

#घोषणा RT1308_RESET				0x00
#घोषणा RT1308_RESET_N				0x01
#घोषणा RT1308_CLK_GATING			0x02
#घोषणा RT1308_PLL_1				0x03
#घोषणा RT1308_PLL_2				0x04
#घोषणा RT1308_PLL_INT				0x05
#घोषणा RT1308_CLK_1				0x06
#घोषणा RT1308_DATA_PATH			0x07
#घोषणा RT1308_CLK_2				0x08
#घोषणा RT1308_SIL_DET				0x09
#घोषणा RT1308_CLK_DET				0x0a
#घोषणा RT1308_DC_DET				0x0b
#घोषणा RT1308_DC_DET_THRES			0x0c
#घोषणा RT1308_DAC_SET				0x10
#घोषणा RT1308_SRC_SET				0x11
#घोषणा RT1308_DAC_BUF				0x12
#घोषणा RT1308_ADC_SET				0x13
#घोषणा RT1308_ADC_SET_INT			0x14
#घोषणा RT1308_I2S_SET_1			0x15
#घोषणा RT1308_I2S_SET_2			0x16
#घोषणा RT1308_I2C_I2S_SDW_SET			0x17
#घोषणा RT1308_SDW_REG_RW			0x18
#घोषणा RT1308_SDW_REG_RDATA			0x19
#घोषणा RT1308_IV_SENSE				0x1a
#घोषणा RT1308_I2S_TX_DAC_SET			0x1b
#घोषणा RT1308_AD_FILTER_SET			0x1c
#घोषणा RT1308_DC_CAL_1				0x20
#घोषणा RT1308_DC_CAL_2				0x21
#घोषणा RT1308_DC_CAL_L_OFFSET			0x22
#घोषणा RT1308_DC_CAL_R_OFFSET			0x23
#घोषणा RT1308_PVDD_OFFSET_CTL			0x24
#घोषणा RT1308_PVDD_OFFSET_L			0x25
#घोषणा RT1308_PVDD_OFFSET_R			0x26
#घोषणा RT1308_PVDD_OFFSET_PBTL			0x27
#घोषणा RT1308_PVDD_OFFSET_PVDD			0x28
#घोषणा RT1308_CAL_OFFSET_DAC_PBTL		0x29
#घोषणा RT1308_CAL_OFFSET_DAC_L			0x2a
#घोषणा RT1308_CAL_OFFSET_DAC_R			0x2b
#घोषणा RT1308_CAL_OFFSET_PWM_L			0x2c
#घोषणा RT1308_CAL_OFFSET_PWM_R			0x2d
#घोषणा RT1308_CAL_PWM_VOS_ADC_L		0x2e
#घोषणा RT1308_CAL_PWM_VOS_ADC_R		0x2f
#घोषणा RT1308_CLASS_D_SET_1			0x30
#घोषणा RT1308_CLASS_D_SET_2			0x31
#घोषणा RT1308_POWER				0x32
#घोषणा RT1308_LDO				0x33
#घोषणा RT1308_VREF				0x34
#घोषणा RT1308_MBIAS				0x35
#घोषणा RT1308_POWER_STATUS			0x36
#घोषणा RT1308_POWER_INT			0x37
#घोषणा RT1308_SINE_TONE_GEN_1			0x50
#घोषणा RT1308_SINE_TONE_GEN_2			0x51
#घोषणा RT1308_BQ_SET				0x54
#घोषणा RT1308_BQ_PARA_UPDATE			0x55
#घोषणा RT1308_BQ_PRE_VOL_L			0x56
#घोषणा RT1308_BQ_PRE_VOL_R			0x57
#घोषणा RT1308_BQ_POST_VOL_L			0x58
#घोषणा RT1308_BQ_POST_VOL_R			0x59
#घोषणा RT1308_BQ1_L_H0				0x5b
#घोषणा RT1308_BQ1_L_B1				0x5c
#घोषणा RT1308_BQ1_L_B2				0x5d
#घोषणा RT1308_BQ1_L_A1				0x5e
#घोषणा RT1308_BQ1_L_A2				0x5f
#घोषणा RT1308_BQ1_R_H0				0x60
#घोषणा RT1308_BQ1_R_B1				0x61
#घोषणा RT1308_BQ1_R_B2				0x62
#घोषणा RT1308_BQ1_R_A1				0x63
#घोषणा RT1308_BQ1_R_A2				0x64
#घोषणा RT1308_BQ2_L_H0				0x65
#घोषणा RT1308_BQ2_L_B1				0x66
#घोषणा RT1308_BQ2_L_B2				0x67
#घोषणा RT1308_BQ2_L_A1				0x68
#घोषणा RT1308_BQ2_L_A2				0x69
#घोषणा RT1308_BQ2_R_H0				0x6a
#घोषणा RT1308_BQ2_R_B1				0x6b
#घोषणा RT1308_BQ2_R_B2				0x6c
#घोषणा RT1308_BQ2_R_A1				0x6d
#घोषणा RT1308_BQ2_R_A2				0x6e
#घोषणा RT1308_VEN_DEV_ID			0x70
#घोषणा RT1308_VERSION_ID			0x71
#घोषणा RT1308_SPK_BOUND			0x72
#घोषणा RT1308_BQ1_EQ_L_1			0x73
#घोषणा RT1308_BQ1_EQ_L_2			0x74
#घोषणा RT1308_BQ1_EQ_L_3			0x75
#घोषणा RT1308_BQ1_EQ_R_1			0x76
#घोषणा RT1308_BQ1_EQ_R_2			0x77
#घोषणा RT1308_BQ1_EQ_R_3			0x78
#घोषणा RT1308_BQ2_EQ_L_1			0x79
#घोषणा RT1308_BQ2_EQ_L_2			0x7a
#घोषणा RT1308_BQ2_EQ_L_3			0x7b
#घोषणा RT1308_BQ2_EQ_R_1			0x7c
#घोषणा RT1308_BQ2_EQ_R_2			0x7d
#घोषणा RT1308_BQ2_EQ_R_3			0x7e
#घोषणा RT1308_EFUSE_1				0x7f
#घोषणा RT1308_EFUSE_2				0x80
#घोषणा RT1308_EFUSE_PROG_PVDD_L		0x81
#घोषणा RT1308_EFUSE_PROG_PVDD_R		0x82
#घोषणा RT1308_EFUSE_PROG_R0_L			0x83
#घोषणा RT1308_EFUSE_PROG_R0_R			0x84
#घोषणा RT1308_EFUSE_PROG_DEV			0x85
#घोषणा RT1308_EFUSE_READ_PVDD_L		0x86
#घोषणा RT1308_EFUSE_READ_PVDD_R		0x87
#घोषणा RT1308_EFUSE_READ_PVDD_PTBL		0x88
#घोषणा RT1308_EFUSE_READ_DEV			0x89
#घोषणा RT1308_EFUSE_READ_R0			0x8a
#घोषणा RT1308_EFUSE_READ_ADC_L			0x8b
#घोषणा RT1308_EFUSE_READ_ADC_R			0x8c
#घोषणा RT1308_EFUSE_READ_ADC_PBTL		0x8d
#घोषणा RT1308_EFUSE_RESERVE			0x8e
#घोषणा RT1308_PADS_1				0x90
#घोषणा RT1308_PADS_2				0x91
#घोषणा RT1308_TEST_MODE			0xa0
#घोषणा RT1308_TEST_1				0xa1
#घोषणा RT1308_TEST_2				0xa2
#घोषणा RT1308_TEST_3				0xa3
#घोषणा RT1308_TEST_4				0xa4
#घोषणा RT1308_EFUSE_DATA_0_MSB			0xb0
#घोषणा RT1308_EFUSE_DATA_0_LSB			0xb1
#घोषणा RT1308_EFUSE_DATA_1_MSB			0xb2
#घोषणा RT1308_EFUSE_DATA_1_LSB			0xb3
#घोषणा RT1308_EFUSE_DATA_2_MSB			0xb4
#घोषणा RT1308_EFUSE_DATA_2_LSB			0xb5
#घोषणा RT1308_EFUSE_DATA_3_MSB			0xb6
#घोषणा RT1308_EFUSE_DATA_3_LSB			0xb7
#घोषणा RT1308_EFUSE_DATA_TEST_MSB		0xb8
#घोषणा RT1308_EFUSE_DATA_TEST_LSB		0xb9
#घोषणा RT1308_EFUSE_STATUS_1			0xba
#घोषणा RT1308_EFUSE_STATUS_2			0xbb
#घोषणा RT1308_TCON_1				0xc0
#घोषणा RT1308_TCON_2				0xc1
#घोषणा RT1308_DUMMY_REG			0xf0
#घोषणा RT1308_MAX_REG				0xff

/* PLL1 M/N/K Code-1 (0x03) */
#घोषणा RT1308_PLL1_K_SFT			24
#घोषणा RT1308_PLL1_K_MASK			(0x1f << 24)
#घोषणा RT1308_PLL1_M_BYPASS_MASK		(0x1 << 23)
#घोषणा RT1308_PLL1_M_BYPASS_SFT		23
#घोषणा RT1308_PLL1_M_BYPASS			(0x1 << 23)
#घोषणा RT1308_PLL1_M_MASK			(0x3f << 16)
#घोषणा RT1308_PLL1_M_SFT			16
#घोषणा RT1308_PLL1_N_MASK			(0x7f << 8)
#घोषणा RT1308_PLL1_N_SFT			8

/* CLOCK-1 (0x06) */
#घोषणा RT1308_DIV_FS_SYS_MASK			(0xf << 28)
#घोषणा RT1308_DIV_FS_SYS_SFT			28
#घोषणा RT1308_SEL_FS_SYS_MASK			(0x7 << 24)
#घोषणा RT1308_SEL_FS_SYS_SFT			24
#घोषणा RT1308_SEL_FS_SYS_SRC_MCLK		(0x0 << 24)
#घोषणा RT1308_SEL_FS_SYS_SRC_BCLK		(0x1 << 24)
#घोषणा RT1308_SEL_FS_SYS_SRC_PLL		(0x2 << 24)
#घोषणा RT1308_SEL_FS_SYS_SRC_RCCLK		(0x4 << 24)

/* CLOCK-2 (0x08) */
#घोषणा RT1308_DIV_PRE_PLL_MASK			(0xf << 28)
#घोषणा RT1308_DIV_PRE_PLL_SFT			28
#घोषणा RT1308_SEL_PLL_SRC_MASK			(0x7 << 24)
#घोषणा RT1308_SEL_PLL_SRC_SFT			24
#घोषणा RT1308_SEL_PLL_SRC_MCLK			(0x0 << 24)
#घोषणा RT1308_SEL_PLL_SRC_BCLK			(0x1 << 24)
#घोषणा RT1308_SEL_PLL_SRC_RCCLK		(0x4 << 24)

/* Clock Detect (0x0a) */
#घोषणा RT1308_MCLK_DET_EN_MASK			(0x1 << 25)
#घोषणा RT1308_MCLK_DET_EN_SFT			25
#घोषणा RT1308_MCLK_DET_EN			(0x1 << 25)
#घोषणा RT1308_BCLK_DET_EN_MASK			(0x1 << 24)
#घोषणा RT1308_BCLK_DET_EN_SFT			24
#घोषणा RT1308_BCLK_DET_EN			(0x1 << 24)

/* DAC Setting (0x10) */
#घोषणा RT1308_DVOL_MUTE_R_EN_SFT		7
#घोषणा RT1308_DVOL_MUTE_L_EN_SFT		6

/* I2S Setting-1 (0x15) */
#घोषणा RT1308_I2S_DF_SEL_MASK			(0x3 << 12)
#घोषणा RT1308_I2S_DF_SEL_SFT			12
#घोषणा RT1308_I2S_DF_SEL_I2S			(0x0 << 12)
#घोषणा RT1308_I2S_DF_SEL_LEFT			(0x1 << 12)
#घोषणा RT1308_I2S_DF_SEL_PCM_A			(0x2 << 12)
#घोषणा RT1308_I2S_DF_SEL_PCM_B			(0x3 << 12)
#घोषणा RT1308_I2S_DL_RX_SEL_MASK		(0x7 << 4)
#घोषणा RT1308_I2S_DL_RX_SEL_SFT		4
#घोषणा RT1308_I2S_DL_RX_SEL_16B		(0x0 << 4)
#घोषणा RT1308_I2S_DL_RX_SEL_20B		(0x1 << 4)
#घोषणा RT1308_I2S_DL_RX_SEL_24B		(0x2 << 4)
#घोषणा RT1308_I2S_DL_RX_SEL_32B		(0x3 << 4)
#घोषणा RT1308_I2S_DL_RX_SEL_8B			(0x4 << 4)
#घोषणा RT1308_I2S_DL_TX_SEL_MASK		(0x7 << 0)
#घोषणा RT1308_I2S_DL_TX_SEL_SFT		0
#घोषणा RT1308_I2S_DL_TX_SEL_16B		(0x0 << 0)
#घोषणा RT1308_I2S_DL_TX_SEL_20B		(0x1 << 0)
#घोषणा RT1308_I2S_DL_TX_SEL_24B		(0x2 << 0)
#घोषणा RT1308_I2S_DL_TX_SEL_32B		(0x3 << 0)
#घोषणा RT1308_I2S_DL_TX_SEL_8B			(0x4 << 0)

/* I2S Setting-2 (0x16) */
#घोषणा RT1308_I2S_DL_SEL_MASK			(0x7 << 24)
#घोषणा RT1308_I2S_DL_SEL_SFT			24
#घोषणा RT1308_I2S_DL_SEL_16B			(0x0 << 24)
#घोषणा RT1308_I2S_DL_SEL_20B			(0x1 << 24)
#घोषणा RT1308_I2S_DL_SEL_24B			(0x2 << 24)
#घोषणा RT1308_I2S_DL_SEL_32B			(0x3 << 24)
#घोषणा RT1308_I2S_DL_SEL_8B			(0x4 << 24)
#घोषणा RT1308_I2S_BCLK_MASK			(0x1 << 14)
#घोषणा RT1308_I2S_BCLK_SFT			14
#घोषणा RT1308_I2S_BCLK_NORMAL			(0x0 << 14)
#घोषणा RT1308_I2S_BCLK_INV			(0x1 << 14)

/* Power Control-1 (0x32) */
#घोषणा RT1308_POW_MBIAS20U			(0x1 << 31)
#घोषणा RT1308_POW_MBIAS20U_BIT			31
#घोषणा RT1308_POW_ALDO				(0x1 << 30)
#घोषणा RT1308_POW_ALDO_BIT			30
#घोषणा RT1308_POW_DBG				(0x1 << 29)
#घोषणा RT1308_POW_DBG_BIT			29
#घोषणा RT1308_POW_DACL				(0x1 << 28)
#घोषणा RT1308_POW_DACL_BIT			28
#घोषणा RT1308_POW_DAC1				(0x1 << 27)
#घोषणा RT1308_POW_DAC1_BIT			27
#घोषणा RT1308_POW_CLK25M			(0x1 << 26)
#घोषणा RT1308_POW_CLK25M_BIT			26
#घोषणा RT1308_POW_ADC_R			(0x1 << 25)
#घोषणा RT1308_POW_ADC_R_BIT			25
#घोषणा RT1308_POW_ADC_L			(0x1 << 24)
#घोषणा RT1308_POW_ADC_L_BIT			24
#घोषणा RT1308_POW_DLDO				(0x1 << 21)
#घोषणा RT1308_POW_DLDO_BIT			21
#घोषणा RT1308_POW_VREF				(0x1 << 20)
#घोषणा RT1308_POW_VREF_BIT			20
#घोषणा RT1308_POW_MIXER_R			(0x1 << 18)
#घोषणा RT1308_POW_MIXER_R_BIT			18
#घोषणा RT1308_POW_MIXER_L			(0x1 << 17)
#घोषणा RT1308_POW_MIXER_L_BIT			17
#घोषणा RT1308_POW_MBIAS4U			(0x1 << 16)
#घोषणा RT1308_POW_MBIAS4U_BIT			16
#घोषणा RT1308_POW_PLL2_LDO_EN			(0x1 << 12)
#घोषणा RT1308_POW_PLL2_LDO_EN_BIT		12
#घोषणा RT1308_POW_PLL2B_EN			(0x1 << 11)
#घोषणा RT1308_POW_PLL2B_EN_BIT			11
#घोषणा RT1308_POW_PLL2F_EN			(0x1 << 10)
#घोषणा RT1308_POW_PLL2F_EN_BIT			10
#घोषणा RT1308_POW_PLL2F2_EN			(0x1 << 9)
#घोषणा RT1308_POW_PLL2F2_EN_BIT		9
#घोषणा RT1308_POW_PLL2B2_EN			(0x1 << 8)
#घोषणा RT1308_POW_PLL2B2_EN_BIT		8

/* Power Control-2 (0x36) */
#घोषणा RT1308_POW_PDB_SRC_BIT			(0x1 << 27)
#घोषणा RT1308_POW_PDB_MN_BIT			(0x1 << 25)
#घोषणा RT1308_POW_PDB_REG_BIT			(0x1 << 24)


/* System Clock Source */
क्रमागत अणु
	RT1308_FS_SYS_S_MCLK,
	RT1308_FS_SYS_S_BCLK,
	RT1308_FS_SYS_S_PLL,
	RT1308_FS_SYS_S_RCCLK,	/* 25.0 MHz */
पूर्ण;

/* PLL Source */
क्रमागत अणु
	RT1308_PLL_S_MCLK,
	RT1308_PLL_S_BCLK,
	RT1308_PLL_S_RCCLK,
पूर्ण;

क्रमागत अणु
	RT1308_AIF1,
	RT1308_AIFS
पूर्ण;

#पूर्ण_अगर		/* end of _RT1308_H_ */
