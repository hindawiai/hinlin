<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * mt8192-afe-clk.h  --  Mediatek 8192 afe घड़ी ctrl definition
 *
 * Copyright (c) 2020 MediaTek Inc.
 * Author: Shane Chien <shane.chien@mediatek.com>
 */

#अगर_अघोषित _MT8192_AFE_CLOCK_CTRL_H_
#घोषणा _MT8192_AFE_CLOCK_CTRL_H_

#घोषणा AP_PLL_CON3 0x0014
#घोषणा APLL1_CON0 0x0318
#घोषणा APLL1_CON1 0x031c
#घोषणा APLL1_CON2 0x0320
#घोषणा APLL1_CON4 0x0328
#घोषणा APLL1_TUNER_CON0 0x0040

#घोषणा APLL2_CON0 0x032c
#घोषणा APLL2_CON1 0x0330
#घोषणा APLL2_CON2 0x0334
#घोषणा APLL2_CON4 0x033c
#घोषणा APLL2_TUNER_CON0 0x0044

#घोषणा CLK_CFG_7 0x0080
#घोषणा CLK_CFG_8 0x0090
#घोषणा CLK_CFG_11 0x00c0
#घोषणा CLK_CFG_12 0x00d0
#घोषणा CLK_CFG_13 0x00e0
#घोषणा CLK_CFG_15 0x0100

#घोषणा CLK_AUDDIV_0 0x0320
#घोषणा CLK_AUDDIV_2 0x0328
#घोषणा CLK_AUDDIV_3 0x0334
#घोषणा CLK_AUDDIV_4 0x0338
#घोषणा CKSYS_AUD_TOP_CFG 0x032c
#घोषणा CKSYS_AUD_TOP_MON 0x0330

#घोषणा PERI_BUS_DCM_CTRL 0x0074
#घोषणा MODULE_SW_CG_1_STA 0x0094
#घोषणा MODULE_SW_CG_2_STA 0x00ac

/* CLK_AUDDIV_0 */
#घोषणा APLL12_DIV0_PDN_SFT                0
#घोषणा APLL12_DIV0_PDN_MASK               0x1
#घोषणा APLL12_DIV0_PDN_MASK_SFT           (0x1 << 0)
#घोषणा APLL12_DIV1_PDN_SFT                1
#घोषणा APLL12_DIV1_PDN_MASK               0x1
#घोषणा APLL12_DIV1_PDN_MASK_SFT           (0x1 << 1)
#घोषणा APLL12_DIV2_PDN_SFT                2
#घोषणा APLL12_DIV2_PDN_MASK               0x1
#घोषणा APLL12_DIV2_PDN_MASK_SFT           (0x1 << 2)
#घोषणा APLL12_DIV3_PDN_SFT                3
#घोषणा APLL12_DIV3_PDN_MASK               0x1
#घोषणा APLL12_DIV3_PDN_MASK_SFT           (0x1 << 3)
#घोषणा APLL12_DIV4_PDN_SFT                4
#घोषणा APLL12_DIV4_PDN_MASK               0x1
#घोषणा APLL12_DIV4_PDN_MASK_SFT           (0x1 << 4)
#घोषणा APLL12_DIVB_PDN_SFT                5
#घोषणा APLL12_DIVB_PDN_MASK               0x1
#घोषणा APLL12_DIVB_PDN_MASK_SFT           (0x1 << 5)
#घोषणा APLL12_DIV5_PDN_SFT                6
#घोषणा APLL12_DIV5_PDN_MASK               0x1
#घोषणा APLL12_DIV5_PDN_MASK_SFT           (0x1 << 6)
#घोषणा APLL12_DIV6_PDN_SFT                7
#घोषणा APLL12_DIV6_PDN_MASK               0x1
#घोषणा APLL12_DIV6_PDN_MASK_SFT           (0x1 << 7)
#घोषणा APLL12_DIV7_PDN_SFT                8
#घोषणा APLL12_DIV7_PDN_MASK               0x1
#घोषणा APLL12_DIV7_PDN_MASK_SFT           (0x1 << 8)
#घोषणा APLL12_DIV8_PDN_SFT                9
#घोषणा APLL12_DIV8_PDN_MASK               0x1
#घोषणा APLL12_DIV8_PDN_MASK_SFT           (0x1 << 9)
#घोषणा APLL12_DIV9_PDN_SFT                10
#घोषणा APLL12_DIV9_PDN_MASK               0x1
#घोषणा APLL12_DIV9_PDN_MASK_SFT           (0x1 << 10)
#घोषणा APLL_I2S0_MCK_SEL_SFT              16
#घोषणा APLL_I2S0_MCK_SEL_MASK             0x1
#घोषणा APLL_I2S0_MCK_SEL_MASK_SFT         (0x1 << 16)
#घोषणा APLL_I2S1_MCK_SEL_SFT              17
#घोषणा APLL_I2S1_MCK_SEL_MASK             0x1
#घोषणा APLL_I2S1_MCK_SEL_MASK_SFT         (0x1 << 17)
#घोषणा APLL_I2S2_MCK_SEL_SFT              18
#घोषणा APLL_I2S2_MCK_SEL_MASK             0x1
#घोषणा APLL_I2S2_MCK_SEL_MASK_SFT         (0x1 << 18)
#घोषणा APLL_I2S3_MCK_SEL_SFT              19
#घोषणा APLL_I2S3_MCK_SEL_MASK             0x1
#घोषणा APLL_I2S3_MCK_SEL_MASK_SFT         (0x1 << 19)
#घोषणा APLL_I2S4_MCK_SEL_SFT              20
#घोषणा APLL_I2S4_MCK_SEL_MASK             0x1
#घोषणा APLL_I2S4_MCK_SEL_MASK_SFT         (0x1 << 20)
#घोषणा APLL_I2S5_MCK_SEL_SFT              21
#घोषणा APLL_I2S5_MCK_SEL_MASK             0x1
#घोषणा APLL_I2S5_MCK_SEL_MASK_SFT         (0x1 << 21)
#घोषणा APLL_I2S6_MCK_SEL_SFT              22
#घोषणा APLL_I2S6_MCK_SEL_MASK             0x1
#घोषणा APLL_I2S6_MCK_SEL_MASK_SFT         (0x1 << 22)
#घोषणा APLL_I2S7_MCK_SEL_SFT              23
#घोषणा APLL_I2S7_MCK_SEL_MASK             0x1
#घोषणा APLL_I2S7_MCK_SEL_MASK_SFT         (0x1 << 23)
#घोषणा APLL_I2S8_MCK_SEL_SFT              24
#घोषणा APLL_I2S8_MCK_SEL_MASK             0x1
#घोषणा APLL_I2S8_MCK_SEL_MASK_SFT         (0x1 << 24)
#घोषणा APLL_I2S9_MCK_SEL_SFT              25
#घोषणा APLL_I2S9_MCK_SEL_MASK             0x1
#घोषणा APLL_I2S9_MCK_SEL_MASK_SFT         (0x1 << 25)

/* CLK_AUDDIV_2 */
#घोषणा APLL12_CK_DIV0_SFT                 0
#घोषणा APLL12_CK_DIV0_MASK                0xff
#घोषणा APLL12_CK_DIV0_MASK_SFT            (0xff << 0)
#घोषणा APLL12_CK_DIV1_SFT                 8
#घोषणा APLL12_CK_DIV1_MASK                0xff
#घोषणा APLL12_CK_DIV1_MASK_SFT            (0xff << 8)
#घोषणा APLL12_CK_DIV2_SFT                 16
#घोषणा APLL12_CK_DIV2_MASK                0xff
#घोषणा APLL12_CK_DIV2_MASK_SFT            (0xff << 16)
#घोषणा APLL12_CK_DIV3_SFT                 24
#घोषणा APLL12_CK_DIV3_MASK                0xff
#घोषणा APLL12_CK_DIV3_MASK_SFT            (0xff << 24)

/* CLK_AUDDIV_3 */
#घोषणा APLL12_CK_DIV4_SFT                 0
#घोषणा APLL12_CK_DIV4_MASK                0xff
#घोषणा APLL12_CK_DIV4_MASK_SFT            (0xff << 0)
#घोषणा APLL12_CK_DIVB_SFT                 8
#घोषणा APLL12_CK_DIVB_MASK                0xff
#घोषणा APLL12_CK_DIVB_MASK_SFT            (0xff << 8)
#घोषणा APLL12_CK_DIV5_SFT                 16
#घोषणा APLL12_CK_DIV5_MASK                0xff
#घोषणा APLL12_CK_DIV5_MASK_SFT            (0xff << 16)
#घोषणा APLL12_CK_DIV6_SFT                 24
#घोषणा APLL12_CK_DIV6_MASK                0xff
#घोषणा APLL12_CK_DIV6_MASK_SFT            (0xff << 24)

/* CLK_AUDDIV_4 */
#घोषणा APLL12_CK_DIV7_SFT                 0
#घोषणा APLL12_CK_DIV7_MASK                0xff
#घोषणा APLL12_CK_DIV7_MASK_SFT            (0xff << 0)
#घोषणा APLL12_CK_DIV8_SFT                 8
#घोषणा APLL12_CK_DIV8_MASK                0xff
#घोषणा APLL12_CK_DIV8_MASK_SFT            (0xff << 0)
#घोषणा APLL12_CK_DIV9_SFT                 16
#घोषणा APLL12_CK_DIV9_MASK                0xff
#घोषणा APLL12_CK_DIV9_MASK_SFT            (0xff << 0)

/* AUD_TOP_CFG */
#घोषणा AUD_TOP_CFG_SFT                    0
#घोषणा AUD_TOP_CFG_MASK                   0xffffffff
#घोषणा AUD_TOP_CFG_MASK_SFT               (0xffffffff << 0)

/* AUD_TOP_MON */
#घोषणा AUD_TOP_MON_SFT                    0
#घोषणा AUD_TOP_MON_MASK                   0xffffffff
#घोषणा AUD_TOP_MON_MASK_SFT               (0xffffffff << 0)

/* CLK_AUDDIV_3 */
#घोषणा APLL12_CK_DIV5_MSB_SFT             0
#घोषणा APLL12_CK_DIV5_MSB_MASK            0xf
#घोषणा APLL12_CK_DIV5_MSB_MASK_SFT        (0xf << 0)
#घोषणा RESERVED0_SFT                      4
#घोषणा RESERVED0_MASK                     0xfffffff
#घोषणा RESERVED0_MASK_SFT                 (0xfffffff << 4)

/* APLL */
#घोषणा APLL1_W_NAME "APLL1"
#घोषणा APLL2_W_NAME "APLL2"
क्रमागत अणु
	MT8192_APLL1 = 0,
	MT8192_APLL2,
पूर्ण;

क्रमागत अणु
	CLK_AFE = 0,
	CLK_TML,
	CLK_APLL22M,
	CLK_APLL24M,
	CLK_APLL1_TUNER,
	CLK_APLL2_TUNER,
	CLK_NLE,
	CLK_INFRA_SYS_AUDIO,
	CLK_INFRA_AUDIO_26M,
	CLK_MUX_AUDIO,
	CLK_MUX_AUDIOINTBUS,
	CLK_TOP_MAINPLL_D4_D4,
	/* apll related mux */
	CLK_TOP_MUX_AUD_1,
	CLK_TOP_APLL1_CK,
	CLK_TOP_MUX_AUD_2,
	CLK_TOP_APLL2_CK,
	CLK_TOP_MUX_AUD_ENG1,
	CLK_TOP_APLL1_D4,
	CLK_TOP_MUX_AUD_ENG2,
	CLK_TOP_APLL2_D4,
	CLK_TOP_MUX_AUDIO_H,
	CLK_TOP_I2S0_M_SEL,
	CLK_TOP_I2S1_M_SEL,
	CLK_TOP_I2S2_M_SEL,
	CLK_TOP_I2S3_M_SEL,
	CLK_TOP_I2S4_M_SEL,
	CLK_TOP_I2S5_M_SEL,
	CLK_TOP_I2S6_M_SEL,
	CLK_TOP_I2S7_M_SEL,
	CLK_TOP_I2S8_M_SEL,
	CLK_TOP_I2S9_M_SEL,
	CLK_TOP_APLL12_DIV0,
	CLK_TOP_APLL12_DIV1,
	CLK_TOP_APLL12_DIV2,
	CLK_TOP_APLL12_DIV3,
	CLK_TOP_APLL12_DIV4,
	CLK_TOP_APLL12_DIVB,
	CLK_TOP_APLL12_DIV5,
	CLK_TOP_APLL12_DIV6,
	CLK_TOP_APLL12_DIV7,
	CLK_TOP_APLL12_DIV8,
	CLK_TOP_APLL12_DIV9,
	CLK_CLK26M,
	CLK_NUM
पूर्ण;

काष्ठा mtk_base_afe;

पूर्णांक mt8192_init_घड़ी(काष्ठा mtk_base_afe *afe);
पूर्णांक mt8192_afe_enable_घड़ी(काष्ठा mtk_base_afe *afe);
व्योम mt8192_afe_disable_घड़ी(काष्ठा mtk_base_afe *afe);

पूर्णांक mt8192_apll1_enable(काष्ठा mtk_base_afe *afe);
व्योम mt8192_apll1_disable(काष्ठा mtk_base_afe *afe);

पूर्णांक mt8192_apll2_enable(काष्ठा mtk_base_afe *afe);
व्योम mt8192_apll2_disable(काष्ठा mtk_base_afe *afe);

पूर्णांक mt8192_get_apll_rate(काष्ठा mtk_base_afe *afe, पूर्णांक apll);
पूर्णांक mt8192_get_apll_by_rate(काष्ठा mtk_base_afe *afe, पूर्णांक rate);
पूर्णांक mt8192_get_apll_by_name(काष्ठा mtk_base_afe *afe, स्थिर अक्षर *name);

/* these will be replaced by using CCF */
पूर्णांक mt8192_mck_enable(काष्ठा mtk_base_afe *afe, पूर्णांक mck_id, पूर्णांक rate);
व्योम mt8192_mck_disable(काष्ठा mtk_base_afe *afe, पूर्णांक mck_id);

पूर्णांक mt8192_set_audio_पूर्णांक_bus_parent(काष्ठा mtk_base_afe *afe,
				    पूर्णांक clk_id);

#पूर्ण_अगर
