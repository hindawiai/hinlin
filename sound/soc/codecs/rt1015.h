<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// rt1015.h  --  RT1015 ALSA SoC audio amplअगरier driver
//
// Copyright 2019 Realtek Semiconductor Corp.
// Author: Jack Yu <jack.yu@realtek.com>
//
// This program is मुक्त software; you can redistribute it and/or modअगरy
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//

#अगर_अघोषित __RT1015_H__
#घोषणा __RT1015_H__
#समावेश <sound/rt1015.h>

#घोषणा RT1015_DEVICE_ID_VAL			0x1011
#घोषणा RT1015_DEVICE_ID_VAL2			0x1015

#घोषणा RT1015_RESET				0x0000
#घोषणा RT1015_CLK2				0x0004
#घोषणा RT1015_CLK3				0x0006
#घोषणा RT1015_PLL1				0x000a
#घोषणा RT1015_PLL2				0x000c
#घोषणा RT1015_DUM_RW1				0x000e
#घोषणा RT1015_DUM_RW2				0x0010
#घोषणा RT1015_DUM_RW3				0x0012
#घोषणा RT1015_DUM_RW4				0x0014
#घोषणा RT1015_DUM_RW5				0x0016
#घोषणा RT1015_DUM_RW6				0x0018
#घोषणा RT1015_CLK_DET				0x0020
#घोषणा RT1015_SIL_DET				0x0022
#घोषणा RT1015_CUSTOMER_ID			0x0076
#घोषणा RT1015_PCODE_FWVER			0x0078
#घोषणा RT1015_VER_ID				0x007a
#घोषणा RT1015_VENDOR_ID			0x007c
#घोषणा RT1015_DEVICE_ID			0x007d
#घोषणा RT1015_PAD_DRV1				0x00f0
#घोषणा RT1015_PAD_DRV2				0x00f2
#घोषणा RT1015_GAT_BOOST			0x00f3
#घोषणा RT1015_PRO_ALT				0x00f4
#घोषणा RT1015_OSCK_STA				0x00f6
#घोषणा RT1015_MAN_I2C				0x0100
#घोषणा RT1015_DAC1				0x0102
#घोषणा RT1015_DAC2				0x0104
#घोषणा RT1015_DAC3				0x0106
#घोषणा RT1015_ADC1				0x010c
#घोषणा RT1015_ADC2				0x010e
#घोषणा RT1015_TDM_MASTER			0x0111
#घोषणा RT1015_TDM_TCON				0x0112
#घोषणा RT1015_TDM1_1				0x0114
#घोषणा RT1015_TDM1_2				0x0116
#घोषणा RT1015_TDM1_3				0x0118
#घोषणा RT1015_TDM1_4				0x011a
#घोषणा RT1015_TDM1_5				0x011c
#घोषणा RT1015_MIXER1				0x0300
#घोषणा RT1015_MIXER2				0x0302
#घोषणा RT1015_ANA_PROTECT1			0x0311
#घोषणा RT1015_ANA_CTRL_SEQ1			0x0313
#घोषणा RT1015_ANA_CTRL_SEQ2			0x0314
#घोषणा RT1015_VBAT_DET_DEB			0x031a
#घोषणा RT1015_VBAT_VOLT_DET1			0x031c
#घोषणा RT1015_VBAT_VOLT_DET2			0x031d
#घोषणा RT1015_VBAT_TEST_OUT1			0x031e
#घोषणा RT1015_VBAT_TEST_OUT2			0x031f
#घोषणा RT1015_VBAT_PROT_ATT			0x0320
#घोषणा RT1015_VBAT_DET_CODE			0x0321
#घोषणा RT1015_PWR1				0x0322
#घोषणा RT1015_PWR4				0x0328
#घोषणा RT1015_PWR5				0x0329
#घोषणा RT1015_PWR6				0x032a
#घोषणा RT1015_PWR7				0x032b
#घोषणा RT1015_PWR8				0x032c
#घोषणा RT1015_PWR9				0x032d
#घोषणा RT1015_CLASSD_SEQ			0x032e
#घोषणा RT1015_SMART_BST_CTRL1			0x0330
#घोषणा RT1015_SMART_BST_CTRL2			0x0332
#घोषणा RT1015_ANA_CTRL1			0x0334
#घोषणा RT1015_ANA_CTRL2			0x0336
#घोषणा RT1015_PWR_STATE_CTRL			0x0338
#घोषणा RT1015_MONO_DYNA_CTRL			0x04fa
#घोषणा RT1015_MONO_DYNA_CTRL1			0x04fc
#घोषणा RT1015_MONO_DYNA_CTRL2			0x04fe
#घोषणा RT1015_MONO_DYNA_CTRL3			0x0500
#घोषणा RT1015_MONO_DYNA_CTRL4			0x0502
#घोषणा RT1015_MONO_DYNA_CTRL5			0x0504
#घोषणा RT1015_SPK_VOL					0x0506
#घोषणा RT1015_SHORT_DETTOP1			0x0508
#घोषणा RT1015_SHORT_DETTOP2			0x050a
#घोषणा RT1015_SPK_DC_DETECT1			0x0519
#घोषणा RT1015_SPK_DC_DETECT2			0x051a
#घोषणा RT1015_SPK_DC_DETECT3			0x051b
#घोषणा RT1015_SPK_DC_DETECT4			0x051d
#घोषणा RT1015_SPK_DC_DETECT5			0x051f
#घोषणा RT1015_BAT_RPO_STEP1			0x0536
#घोषणा RT1015_BAT_RPO_STEP2			0x0538
#घोषणा RT1015_BAT_RPO_STEP3			0x053a
#घोषणा RT1015_BAT_RPO_STEP4			0x053c
#घोषणा RT1015_BAT_RPO_STEP5			0x053d
#घोषणा RT1015_BAT_RPO_STEP6			0x053e
#घोषणा RT1015_BAT_RPO_STEP7			0x053f
#घोषणा RT1015_BAT_RPO_STEP8			0x0540
#घोषणा RT1015_BAT_RPO_STEP9			0x0541
#घोषणा RT1015_BAT_RPO_STEP10			0x0542
#घोषणा RT1015_BAT_RPO_STEP11			0x0543
#घोषणा RT1015_BAT_RPO_STEP12			0x0544
#घोषणा RT1015_SPREAD_SPEC1			0x0568
#घोषणा RT1015_SPREAD_SPEC2			0x056a
#घोषणा RT1015_PAD_STATUS			0x1000
#घोषणा RT1015_PADS_PULLING_CTRL1		0x1002
#घोषणा RT1015_PADS_DRIVING			0x1006
#घोषणा RT1015_SYS_RST1				0x1007
#घोषणा RT1015_SYS_RST2				0x1009
#घोषणा RT1015_SYS_GATING1			0x100a
#घोषणा RT1015_TEST_MODE1			0x100c
#घोषणा RT1015_TEST_MODE2			0x100d
#घोषणा RT1015_TIMING_CTRL1			0x100e
#घोषणा RT1015_PLL_INT				0x1010
#घोषणा RT1015_TEST_OUT1			0x1020
#घोषणा RT1015_DC_CALIB_CLSD1			0x1200
#घोषणा RT1015_DC_CALIB_CLSD2			0x1202
#घोषणा RT1015_DC_CALIB_CLSD3			0x1204
#घोषणा RT1015_DC_CALIB_CLSD4			0x1206
#घोषणा RT1015_DC_CALIB_CLSD5			0x1208
#घोषणा RT1015_DC_CALIB_CLSD6			0x120a
#घोषणा RT1015_DC_CALIB_CLSD7			0x120c
#घोषणा RT1015_DC_CALIB_CLSD8			0x120e
#घोषणा RT1015_DC_CALIB_CLSD9			0x1210
#घोषणा RT1015_DC_CALIB_CLSD10			0x1212
#घोषणा RT1015_CLSD_INTERNAL1			0x1300
#घोषणा RT1015_CLSD_INTERNAL2			0x1302
#घोषणा RT1015_CLSD_INTERNAL3			0x1304
#घोषणा RT1015_CLSD_INTERNAL4			0x1305
#घोषणा RT1015_CLSD_INTERNAL5			0x1306
#घोषणा RT1015_CLSD_INTERNAL6			0x1308
#घोषणा RT1015_CLSD_INTERNAL7			0x130a
#घोषणा RT1015_CLSD_INTERNAL8			0x130c
#घोषणा RT1015_CLSD_INTERNAL9			0x130e
#घोषणा RT1015_CLSD_OCP_CTRL			0x130f
#घोषणा RT1015_VREF_LV				0x1310
#घोषणा RT1015_MBIAS1				0x1312
#घोषणा RT1015_MBIAS2				0x1314
#घोषणा RT1015_MBIAS3				0x1316
#घोषणा RT1015_MBIAS4				0x1318
#घोषणा RT1015_VREF_LV1				0x131a
#घोषणा RT1015_S_BST_TIMING_INTER1		0x1322
#घोषणा RT1015_S_BST_TIMING_INTER2		0x1323
#घोषणा RT1015_S_BST_TIMING_INTER3		0x1324
#घोषणा RT1015_S_BST_TIMING_INTER4		0x1325
#घोषणा RT1015_S_BST_TIMING_INTER5		0x1326
#घोषणा RT1015_S_BST_TIMING_INTER6		0x1327
#घोषणा RT1015_S_BST_TIMING_INTER7		0x1328
#घोषणा RT1015_S_BST_TIMING_INTER8		0x1329
#घोषणा RT1015_S_BST_TIMING_INTER9		0x132a
#घोषणा RT1015_S_BST_TIMING_INTER10		0x132b
#घोषणा RT1015_S_BST_TIMING_INTER11		0x1330
#घोषणा RT1015_S_BST_TIMING_INTER12		0x1331
#घोषणा RT1015_S_BST_TIMING_INTER13		0x1332
#घोषणा RT1015_S_BST_TIMING_INTER14		0x1333
#घोषणा RT1015_S_BST_TIMING_INTER15		0x1334
#घोषणा RT1015_S_BST_TIMING_INTER16		0x1335
#घोषणा RT1015_S_BST_TIMING_INTER17		0x1336
#घोषणा RT1015_S_BST_TIMING_INTER18		0x1337
#घोषणा RT1015_S_BST_TIMING_INTER19		0x1338
#घोषणा RT1015_S_BST_TIMING_INTER20		0x1339
#घोषणा RT1015_S_BST_TIMING_INTER21		0x133a
#घोषणा RT1015_S_BST_TIMING_INTER22		0x133b
#घोषणा RT1015_S_BST_TIMING_INTER23		0x133c
#घोषणा RT1015_S_BST_TIMING_INTER24		0x133d
#घोषणा RT1015_S_BST_TIMING_INTER25		0x133e
#घोषणा RT1015_S_BST_TIMING_INTER26		0x133f
#घोषणा RT1015_S_BST_TIMING_INTER27		0x1340
#घोषणा RT1015_S_BST_TIMING_INTER28		0x1341
#घोषणा RT1015_S_BST_TIMING_INTER29		0x1342
#घोषणा RT1015_S_BST_TIMING_INTER30		0x1343
#घोषणा RT1015_S_BST_TIMING_INTER31		0x1344
#घोषणा RT1015_S_BST_TIMING_INTER32		0x1345
#घोषणा RT1015_S_BST_TIMING_INTER33		0x1346
#घोषणा RT1015_S_BST_TIMING_INTER34		0x1347
#घोषणा RT1015_S_BST_TIMING_INTER35		0x1348
#घोषणा RT1015_S_BST_TIMING_INTER36		0x1349

/* 0x0004 */
#घोषणा RT1015_CLK_SYS_PRE_SEL_MASK		(0x3 << 14)
#घोषणा RT1015_CLK_SYS_PRE_SEL_SFT		14
#घोषणा RT1015_CLK_SYS_PRE_SEL_MCLK		(0x0 << 14)
#घोषणा RT1015_CLK_SYS_PRE_SEL_PLL		(0x2 << 14)
#घोषणा RT1015_PLL_SEL_MASK			(0x1 << 13)
#घोषणा RT1015_PLL_SEL_SFT			13
#घोषणा RT1015_PLL_SEL_PLL_SRC2			(0x0 << 13)
#घोषणा RT1015_PLL_SEL_BCLK			(0x1 << 13)
#घोषणा RT1015_FS_PD_MASK			(0x7 << 4)
#घोषणा RT1015_FS_PD_SFT			4

/* 0x000a */
#घोषणा RT1015_PLL_M_MAX			0xf
#घोषणा RT1015_PLL_M_MASK			(RT1015_PLL_M_MAX << 12)
#घोषणा RT1015_PLL_M_SFT			12
#घोषणा RT1015_PLL_M_BP				(0x1 << 11)
#घोषणा RT1015_PLL_M_BP_SFT			11
#घोषणा RT1015_PLL_N_MAX			0x1ff
#घोषणा RT1015_PLL_N_MASK			(RT1015_PLL_N_MAX << 0)
#घोषणा RT1015_PLL_N_SFT			0

/* 0x000c */
#घोषणा RT1015_PLL_BPK_MASK			(0x1 << 5)
#घोषणा RT1015_PLL_BPK				(0x0 << 5)
#घोषणा RT1015_PLL_K_MAX			0x1f
#घोषणा RT1015_PLL_K_MASK			(RT1015_PLL_K_MAX)
#घोषणा RT1015_PLL_K_SFT			0

/* 0x0020 */
#घोषणा RT1015_EN_BCLK_DET_MASK			(0x1 << 15)
#घोषणा RT1015_EN_BCLK_DET				(0x1 << 15)
#घोषणा RT1015_DIS_BCLK_DET				(0x0 << 15)

/* 0x007a */
#घोषणा RT1015_ID_MASK				0xff
#घोषणा RT1015_ID_VERA				0x0
#घोषणा RT1015_ID_VERB				0x1

/* 0x00f2 */
#घोषणा RT1015_MONO_LR_SEL_MASK			(0x3 << 4)
#घोषणा RT1015_MONO_L_CHANNEL			(0x0 << 4)
#घोषणा RT1015_MONO_R_CHANNEL			(0x1 << 4)
#घोषणा RT1015_MONO_LR_MIX_CHANNEL			(0x2 << 4)

/* 0x0102 */
#घोषणा RT1015_DAC_VOL_MASK			(0x7f << 9)
#घोषणा RT1015_DAC_VOL_SFT			9

/* 0x0104 */
#घोषणा RT1015_DAC_CLK				(0x1 << 13)
#घोषणा RT1015_DAC_CLK_BIT			13

/* 0x0106 */
#घोषणा RT1015_DAC_MUTE_MASK			(0x1 << 15)
#घोषणा RT1015_DA_MUTE_SFT			15
#घोषणा RT1015_DVOL_MUTE_FLAG_SFT		12

/* 0x0111 */
#घोषणा RT1015_TCON_TDM_MS_MASK			(0x1 << 14)
#घोषणा RT1015_TCON_TDM_MS_SFT			14
#घोषणा RT1015_TCON_TDM_MS_S			(0x0 << 14)
#घोषणा RT1015_TCON_TDM_MS_M			(0x1 << 14)
#घोषणा RT1015_I2S_DL_MASK			(0x7 << 8)
#घोषणा RT1015_I2S_DL_SFT			8
#घोषणा RT1015_I2S_DL_16			(0x0 << 8)
#घोषणा RT1015_I2S_DL_20			(0x1 << 8)
#घोषणा RT1015_I2S_DL_24			(0x2 << 8)
#घोषणा RT1015_I2S_DL_8				(0x3 << 8)
#घोषणा RT1015_I2S_M_DF_MASK			(0x7 << 0)
#घोषणा RT1015_I2S_M_DF_SFT			0
#घोषणा RT1015_I2S_M_DF_I2S			(0x0)
#घोषणा RT1015_I2S_M_DF_LEFT			(0x1)
#घोषणा RT1015_I2S_M_DF_PCM_A			(0x2)
#घोषणा RT1015_I2S_M_DF_PCM_B			(0x3)
#घोषणा RT1015_I2S_M_DF_PCM_A_N			(0x6)
#घोषणा RT1015_I2S_M_DF_PCM_B_N			(0x7)

/* TDM_tcon Setting (0x0112) */
#घोषणा RT1015_I2S_TCON_DF_MASK			(0x7 << 13)
#घोषणा RT1015_I2S_TCON_DF_SFT			13
#घोषणा RT1015_I2S_TCON_DF_I2S			(0x0 << 13)
#घोषणा RT1015_I2S_TCON_DF_LEFT			(0x1 << 13)
#घोषणा RT1015_I2S_TCON_DF_PCM_A		(0x2 << 13)
#घोषणा RT1015_I2S_TCON_DF_PCM_B		(0x3 << 13)
#घोषणा RT1015_I2S_TCON_DF_PCM_A_N		(0x6 << 13)
#घोषणा RT1015_I2S_TCON_DF_PCM_B_N		(0x7 << 13)
#घोषणा RT1015_TCON_BCLK_SEL_MASK		(0x3 << 10)
#घोषणा RT1015_TCON_BCLK_SEL_SFT		10
#घोषणा RT1015_TCON_BCLK_SEL_32FS		(0x0 << 10)
#घोषणा RT1015_TCON_BCLK_SEL_64FS		(0x1 << 10)
#घोषणा RT1015_TCON_BCLK_SEL_128FS		(0x2 << 10)
#घोषणा RT1015_TCON_BCLK_SEL_256FS		(0x3 << 10)
#घोषणा RT1015_TCON_CH_LEN_MASK			(0x3 << 5)
#घोषणा RT1015_TCON_CH_LEN_SFT			5
#घोषणा RT1015_TCON_CH_LEN_16B			(0x0 << 5)
#घोषणा RT1015_TCON_CH_LEN_20B			(0x1 << 5)
#घोषणा RT1015_TCON_CH_LEN_24B			(0x2 << 5)
#घोषणा RT1015_TCON_CH_LEN_32B			(0x3 << 5)
#घोषणा RT1015_TCON_BCLK_MST_MASK			(0x1 << 4)
#घोषणा RT1015_TCON_BCLK_MST_SFT			4
#घोषणा RT1015_TCON_BCLK_MST_INV		(0x1 << 4)

/* TDM1 Setting-1 (0x0114) */
#घोषणा RT1015_TDM_INV_BCLK_MASK		(0x1 << 15)
#घोषणा RT1015_TDM_INV_BCLK_SFT			15
#घोषणा RT1015_TDM_INV_BCLK			(0x1 << 15)
#घोषणा RT1015_I2S_CH_TX_MASK			(0x3 << 10)
#घोषणा RT1015_I2S_CH_TX_SFT			10
#घोषणा RT1015_I2S_TX_2CH			(0x0 << 10)
#घोषणा RT1015_I2S_TX_4CH			(0x1 << 10)
#घोषणा RT1015_I2S_TX_6CH			(0x2 << 10)
#घोषणा RT1015_I2S_TX_8CH			(0x3 << 10)
#घोषणा RT1015_I2S_CH_RX_MASK			(0x3 << 8)
#घोषणा RT1015_I2S_CH_RX_SFT			8
#घोषणा RT1015_I2S_RX_2CH			(0x0 << 8)
#घोषणा RT1015_I2S_RX_4CH			(0x1 << 8)
#घोषणा RT1015_I2S_RX_6CH			(0x2 << 8)
#घोषणा RT1015_I2S_RX_8CH			(0x3 << 8)
#घोषणा RT1015_I2S_LR_CH_SEL_MASK			(0x1 << 7)
#घोषणा RT1015_I2S_LR_CH_SEL_SFT			7
#घोषणा RT1015_I2S_LEFT_CH_SEL			(0x0 << 7)
#घोषणा RT1015_I2S_RIGHT_CH_SEL			(0x1 << 7)
#घोषणा RT1015_I2S_CH_TX_LEN_MASK			(0x7 << 4)
#घोषणा RT1015_I2S_CH_TX_LEN_SFT			4
#घोषणा RT1015_I2S_CH_TX_LEN_16B			(0x0 << 4)
#घोषणा RT1015_I2S_CH_TX_LEN_20B			(0x1 << 4)
#घोषणा RT1015_I2S_CH_TX_LEN_24B			(0x2 << 4)
#घोषणा RT1015_I2S_CH_TX_LEN_32B			(0x3 << 4)
#घोषणा RT1015_I2S_CH_TX_LEN_8B			(0x4 << 4)
#घोषणा RT1015_I2S_CH_RX_LEN_MASK			(0x7 << 0)
#घोषणा RT1015_I2S_CH_RX_LEN_SFT			0
#घोषणा RT1015_I2S_CH_RX_LEN_16B			(0x0 << 0)
#घोषणा RT1015_I2S_CH_RX_LEN_20B			(0x1 << 0)
#घोषणा RT1015_I2S_CH_RX_LEN_24B			(0x2 << 0)
#घोषणा RT1015_I2S_CH_RX_LEN_32B			(0x3 << 0)
#घोषणा RT1015_I2S_CH_RX_LEN_8B			(0x4 << 0)

/* TDM1 Setting-4 (0x011a) */
#घोषणा RT1015_TDM_I2S_TX_L_DAC1_1_MASK			(0x7 << 12)
#घोषणा RT1015_TDM_I2S_TX_R_DAC1_1_MASK			(0x7 << 8)
#घोषणा RT1015_TDM_I2S_TX_L_DAC1_1_SFT 12
#घोषणा RT1015_TDM_I2S_TX_R_DAC1_1_SFT 8

/* 0x0330 */
#घोषणा RT1015_ABST_AUTO_EN_MASK		(0x1 << 13)
#घोषणा RT1015_ABST_AUTO_MODE			(0x1 << 13)
#घोषणा RT1015_ABST_REG_MODE			(0x0 << 13)
#घोषणा RT1015_ABST_FIX_TGT_MASK		(0x1 << 12)
#घोषणा RT1015_ABST_FIX_TGT_EN			(0x1 << 12)
#घोषणा RT1015_ABST_FIX_TGT_DIS			(0x0 << 12)
#घोषणा RT1015_BYPASS_SWR_REG_MASK		(0x1 << 7)
#घोषणा RT1015_BYPASS_SWRREG_BYPASS		(0x1 << 7)
#घोषणा RT1015_BYPASS_SWRREG_PASS		(0x0 << 7)

/* 0x0322 */
#घोषणा RT1015_PWR_LDO2				(0x1 << 15)
#घोषणा RT1015_PWR_LDO2_BIT			15
#घोषणा RT1015_PWR_DAC				(0x1 << 14)
#घोषणा RT1015_PWR_DAC_BIT			14
#घोषणा RT1015_PWR_INTCLK			(0x1 << 13)
#घोषणा RT1015_PWR_INTCLK_BIT			13
#घोषणा RT1015_PWR_ISENSE			(0x1 << 12)
#घोषणा RT1015_PWR_ISENSE_BIT			12
#घोषणा RT1015_PWR_VSENSE			(0x1 << 10)
#घोषणा RT1015_PWR_VSENSE_BIT			10
#घोषणा RT1015_PWR_PLL				(0x1 << 9)
#घोषणा RT1015_PWR_PLL_BIT			9
#घोषणा RT1015_PWR_BG_1_2			(0x1 << 8)
#घोषणा RT1015_PWR_BG_1_2_BIT			8
#घोषणा RT1015_PWR_MBIAS_BG			(0x1 << 7)
#घोषणा RT1015_PWR_MBIAS_BG_BIT			7
#घोषणा RT1015_PWR_VBAT				(0x1 << 6)
#घोषणा RT1015_PWR_VBAT_BIT			6
#घोषणा RT1015_PWR_MBIAS			(0x1 << 4)
#घोषणा RT1015_PWR_MBIAS_BIT			4
#घोषणा RT1015_PWR_ADCV				(0x1 << 3)
#घोषणा RT1015_PWR_ADCV_BIT			3
#घोषणा RT1015_PWR_MIXERV			(0x1 << 2)
#घोषणा RT1015_PWR_MIXERV_BIT			2
#घोषणा RT1015_PWR_SUMV				(0x1 << 1)
#घोषणा RT1015_PWR_SUMV_BIT			1
#घोषणा RT1015_PWR_VREFLV			(0x1 << 0)
#घोषणा RT1015_PWR_VREFLV_BIT			0

/* 0x0324 */
#घोषणा RT1015_PWR_BASIC			(0x1 << 15)
#घोषणा RT1015_PWR_BASIC_BIT			15
#घोषणा RT1015_PWR_SD				(0x1 << 14)
#घोषणा RT1015_PWR_SD_BIT			14
#घोषणा RT1015_PWR_IBIAS			(0x1 << 13)
#घोषणा RT1015_PWR_IBIAS_BIT			13
#घोषणा RT1015_PWR_VCM				(0x1 << 11)
#घोषणा RT1015_PWR_VCM_BIT			11

/* 0x0328 */
#घोषणा RT1015_PWR_SWR				(0x1 << 12)
#घोषणा RT1015_PWR_SWR_BIT			12

/* 0x0519 */
#घोषणा RT1015_EN_CLA_D_DC_DET_MASK	(0x1 << 12)
#घोषणा RT1015_EN_CLA_D_DC_DET		(0x1 << 12)
#घोषणा RT1015_DIS_CLA_D_DC_DET		(0x0 << 12)

/* 0x1300 */
#घोषणा RT1015_PWR_CLSD				(0x1 << 12)
#घोषणा RT1015_PWR_CLSD_BIT			12

/* 0x007a */
#घोषणा RT1015_ID_MASK				0xff
#घोषणा RT1015_ID_VERA				0x0
#घोषणा RT1015_ID_VERB				0x1

/* System Clock Source */
क्रमागत अणु
	RT1015_SCLK_S_MCLK,
	RT1015_SCLK_S_PLL,
पूर्ण;

/* PLL1 Source */
क्रमागत अणु
	RT1015_PLL_S_MCLK,
	RT1015_PLL_S_BCLK,
पूर्ण;

क्रमागत अणु
	RT1015_AIF1,
	RT1015_AIFS,
पूर्ण;

क्रमागत अणु
	RT1015_VERA,
	RT1015_VERB,
पूर्ण;

क्रमागत अणु
	BYPASS,
	ADAPTIVE,
	FIXED_ADAPTIVE,
पूर्ण;

क्रमागत अणु
	RT1015_Enable_Boost = 0,
	RT1015_Bypass_Boost,
पूर्ण;

क्रमागत अणु
	RT1015_HW_28 = 0,
	RT1015_HW_29,
पूर्ण;

काष्ठा rt1015_priv अणु
	काष्ठा snd_soc_component *component;
	काष्ठा rt1015_platक्रमm_data pdata;
	काष्ठा regmap *regmap;
	पूर्णांक sysclk;
	पूर्णांक sysclk_src;
	पूर्णांक pll_src;
	पूर्णांक pll_in;
	पूर्णांक pll_out;
	पूर्णांक boost_mode;
	पूर्णांक bypass_boost;
	पूर्णांक dac_is_used;
	पूर्णांक cali_करोne;
	पूर्णांक hw_config;
	काष्ठा delayed_work flush_work;
पूर्ण;

#पूर्ण_अगर /* __RT1015_H__ */
