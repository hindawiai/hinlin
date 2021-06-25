<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * rt1019.h  --  RT1019 ALSA SoC audio amplअगरier driver
 *
 * Copyright(c) 2021 Realtek Semiconductor Corp.
 */

#अगर_अघोषित __RT1019_H__
#घोषणा __RT1019_H__

#घोषणा RT1019_DEVICE_ID_VAL			0x1019
#घोषणा RT1019_DEVICE_ID_VAL2			0x6731

#घोषणा RT1019_RESET				0x0000
#घोषणा RT1019_IDS_CTRL				0x0011
#घोषणा RT1019_ASEL_CTRL			0x0013
#घोषणा RT1019_PWR_STRP_2			0x0019
#घोषणा RT1019_BEEP_TONE			0x001b
#घोषणा RT1019_VER_ID				0x005c
#घोषणा RT1019_VEND_ID_1			0x005e
#घोषणा RT1019_VEND_ID_2			0x005f
#घोषणा RT1019_DEV_ID_1				0x0061
#घोषणा RT1019_DEV_ID_2				0x0062
#घोषणा RT1019_SDB_CTRL				0x0066
#घोषणा RT1019_CLK_TREE_1			0x0100
#घोषणा RT1019_CLK_TREE_2			0x0101
#घोषणा RT1019_CLK_TREE_3			0x0102
#घोषणा RT1019_PLL_1				0x0311
#घोषणा RT1019_PLL_2				0x0312
#घोषणा RT1019_PLL_3				0x0313
#घोषणा RT1019_TDM_1				0x0400
#घोषणा RT1019_TDM_2				0x0401
#घोषणा RT1019_TDM_3				0x0402
#घोषणा RT1019_DMIX_MONO_1			0x0504
#घोषणा RT1019_DMIX_MONO_2			0x0505
#घोषणा RT1019_BEEP_1				0x0b00
#घोषणा RT1019_BEEP_2				0x0b01

/* 0x0019 Power On Strap Control-2 */
#घोषणा RT1019_AUTO_BITS_SEL_MASK		(0x1 << 5)
#घोषणा RT1019_AUTO_BITS_SEL_AUTO		(0x1 << 5)
#घोषणा RT1019_AUTO_BITS_SEL_MANU		(0x0 << 5)
#घोषणा RT1019_AUTO_CLK_SEL_MASK		(0x1 << 4)
#घोषणा RT1019_AUTO_CLK_SEL_AUTO		(0x1 << 4)
#घोषणा RT1019_AUTO_CLK_SEL_MANU		(0x0 << 4)

/* 0x0100 Clock Tree Control-1 */
#घोषणा RT1019_CLK_SYS_PRE_SEL_MASK		(0x1 << 7)
#घोषणा RT1019_CLK_SYS_PRE_SEL_SFT		7
#घोषणा RT1019_CLK_SYS_PRE_SEL_BCLK		(0x0 << 7)
#घोषणा RT1019_CLK_SYS_PRE_SEL_PLL		(0x1 << 7)
#घोषणा RT1019_PLL_SRC_MASK				(0x1 << 4)
#घोषणा RT1019_PLL_SRC_SFT				4
#घोषणा RT1019_PLL_SRC_SEL_BCLK			(0x0 << 4)
#घोषणा RT1019_PLL_SRC_SEL_RC			(0x1 << 4)
#घोषणा RT1019_SEL_FIFO_MASK			(0x3 << 2)
#घोषणा RT1019_SEL_FIFO_DIV1			(0x0 << 2)
#घोषणा RT1019_SEL_FIFO_DIV2			(0x1 << 2)
#घोषणा RT1019_SEL_FIFO_DIV4			(0x2 << 2)

/* 0x0101 घड़ी tree control-2 */
#घोषणा RT1019_SYS_DIV_DA_FIL_MASK		(0x7 << 5)
#घोषणा RT1019_SYS_DIV_DA_FIL_DIV1		(0x2 << 5)
#घोषणा RT1019_SYS_DIV_DA_FIL_DIV2		(0x3 << 5)
#घोषणा RT1019_SYS_DIV_DA_FIL_DIV4		(0x4 << 5)
#घोषणा RT1019_SYS_DA_OSR_MASK			(0x3 << 2)
#घोषणा RT1019_SYS_DA_OSR_DIV1			(0x0 << 2)
#घोषणा RT1019_SYS_DA_OSR_DIV2			(0x1 << 2)
#घोषणा RT1019_SYS_DA_OSR_DIV4			(0x2 << 2)
#घोषणा RT1019_ASRC_256FS_MASK			0x3
#घोषणा RT1019_ASRC_256FS_DIV1			0x0
#घोषणा RT1019_ASRC_256FS_DIV2			0x1
#घोषणा RT1019_ASRC_256FS_DIV4			0x2

/* 0x0102 घड़ी tree control-3 */
#घोषणा RT1019_SEL_CLK_CAL_MASK			(0x3 << 6)
#घोषणा RT1019_SEL_CLK_CAL_DIV1			(0x0 << 6)
#घोषणा RT1019_SEL_CLK_CAL_DIV2			(0x1 << 6)
#घोषणा RT1019_SEL_CLK_CAL_DIV4			(0x2 << 6)

/* 0x0311 PLL-1 */
#घोषणा RT1019_PLL_M_MASK			(0xf << 4)
#घोषणा RT1019_PLL_M_SFT			4
#घोषणा RT1019_PLL_M_BP_MASK		(0x1 << 1)
#घोषणा RT1019_PLL_M_BP_SFT			1
#घोषणा RT1019_PLL_Q_8_8_MASK		(0x1)

/* 0x0312 PLL-2 */
#घोषणा RT1019_PLL_Q_7_0_MASK		0xff

/* 0x0313 PLL-3 */
#घोषणा RT1019_PLL_K_MASK		0x1f

/* 0x0400 TDM Control-1 */
#घोषणा RT1019_TDM_BCLK_MASK		(0x1 << 6)
#घोषणा RT1019_TDM_BCLK_NORM		(0x0 << 6)
#घोषणा RT1019_TDM_BCLK_INV			(0x1 << 6)

/* 0x0401 TDM Control-2 */
#घोषणा RT1019_I2S_CH_TX_MASK		(0x3 << 6)
#घोषणा RT1019_I2S_CH_TX_SFT		6
#घोषणा RT1019_I2S_TX_2CH			(0x0 << 6)
#घोषणा RT1019_I2S_TX_4CH			(0x1 << 6)
#घोषणा RT1019_I2S_TX_6CH			(0x2 << 6)
#घोषणा RT1019_I2S_TX_8CH			(0x3 << 6)
#घोषणा RT1019_I2S_DF_MASK			(0x7 << 3)
#घोषणा RT1019_I2S_DF_SFT			3
#घोषणा RT1019_I2S_DF_I2S			(0x0 << 3)
#घोषणा RT1019_I2S_DF_LEFT			(0x1 << 3)
#घोषणा RT1019_I2S_DF_PCM_A_R		(0x2 << 3)
#घोषणा RT1019_I2S_DF_PCM_B_R		(0x3 << 3)
#घोषणा RT1019_I2S_DF_PCM_A_F		(0x6 << 3)
#घोषणा RT1019_I2S_DF_PCM_B_F		(0x7 << 3)
#घोषणा RT1019_I2S_DL_MASK			0x7
#घोषणा RT1019_I2S_DL_SFT			0
#घोषणा RT1019_I2S_DL_16			0x0
#घोषणा RT1019_I2S_DL_20			0x1
#घोषणा RT1019_I2S_DL_24			0x2
#घोषणा RT1019_I2S_DL_32			0x3
#घोषणा RT1019_I2S_DL_8				0x4

/* TDM1 Control-3 (0x0402) */
#घोषणा RT1019_TDM_I2S_TX_L_DAC1_1_MASK		(0x7 << 4)
#घोषणा RT1019_TDM_I2S_TX_R_DAC1_1_MASK		0x7
#घोषणा RT1019_TDM_I2S_TX_L_DAC1_1_SFT		4
#घोषणा RT1019_TDM_I2S_TX_R_DAC1_1_SFT		0

/* System Clock Source */
क्रमागत अणु
	RT1019_SCLK_S_BCLK,
	RT1019_SCLK_S_PLL,
पूर्ण;

/* PLL1 Source */
क्रमागत अणु
	RT1019_PLL_S_BCLK,
	RT1019_PLL_S_RC25M,
पूर्ण;

क्रमागत अणु
	RT1019_AIF1,
	RT1019_AIFS
पूर्ण;

काष्ठा rt1019_priv अणु
	काष्ठा snd_soc_component *component;
	काष्ठा regmap *regmap;
	पूर्णांक sysclk;
	पूर्णांक sysclk_src;
	पूर्णांक lrck;
	पूर्णांक bclk;
	पूर्णांक pll_src;
	पूर्णांक pll_in;
	पूर्णांक pll_out;
	अचिन्हित पूर्णांक bclk_ratio;
पूर्ण;

#पूर्ण_अगर /* __RT1019_H__ */
