<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2019 MediaTek Inc.
 * Author: jitao.shi <jitao.shi@mediatek.com>
 */

#समावेश "phy-mtk-mipi-dsi.h"

#घोषणा MIPITX_DSI_CON		0x00
#घोषणा RG_DSI_LDOCORE_EN		BIT(0)
#घोषणा RG_DSI_CKG_LDOOUT_EN		BIT(1)
#घोषणा RG_DSI_BCLK_SEL			(3 << 2)
#घोषणा RG_DSI_LD_IDX_SEL		(7 << 4)
#घोषणा RG_DSI_PHYCLK_SEL		(2 << 8)
#घोषणा RG_DSI_DSICLK_FREQ_SEL		BIT(10)
#घोषणा RG_DSI_LPTX_CLMP_EN		BIT(11)

#घोषणा MIPITX_DSI_CLOCK_LANE	0x04
#घोषणा MIPITX_DSI_DATA_LANE0	0x08
#घोषणा MIPITX_DSI_DATA_LANE1	0x0c
#घोषणा MIPITX_DSI_DATA_LANE2	0x10
#घोषणा MIPITX_DSI_DATA_LANE3	0x14
#घोषणा RG_DSI_LNTx_LDOOUT_EN		BIT(0)
#घोषणा RG_DSI_LNTx_CKLANE_EN		BIT(1)
#घोषणा RG_DSI_LNTx_LPTX_IPLUS1		BIT(2)
#घोषणा RG_DSI_LNTx_LPTX_IPLUS2		BIT(3)
#घोषणा RG_DSI_LNTx_LPTX_IMINUS		BIT(4)
#घोषणा RG_DSI_LNTx_LPCD_IPLUS		BIT(5)
#घोषणा RG_DSI_LNTx_LPCD_IMINUS		BIT(6)
#घोषणा RG_DSI_LNTx_RT_CODE		(0xf << 8)

#घोषणा MIPITX_DSI_TOP_CON	0x40
#घोषणा RG_DSI_LNT_INTR_EN		BIT(0)
#घोषणा RG_DSI_LNT_HS_BIAS_EN		BIT(1)
#घोषणा RG_DSI_LNT_IMP_CAL_EN		BIT(2)
#घोषणा RG_DSI_LNT_TESTMODE_EN		BIT(3)
#घोषणा RG_DSI_LNT_IMP_CAL_CODE		(0xf << 4)
#घोषणा RG_DSI_LNT_AIO_SEL		(7 << 8)
#घोषणा RG_DSI_PAD_TIE_LOW_EN		BIT(11)
#घोषणा RG_DSI_DEBUG_INPUT_EN		BIT(12)
#घोषणा RG_DSI_PRESERVE			(7 << 13)

#घोषणा MIPITX_DSI_BG_CON	0x44
#घोषणा RG_DSI_BG_CORE_EN		BIT(0)
#घोषणा RG_DSI_BG_CKEN			BIT(1)
#घोषणा RG_DSI_BG_DIV			(0x3 << 2)
#घोषणा RG_DSI_BG_FAST_CHARGE		BIT(4)
#घोषणा RG_DSI_VOUT_MSK			(0x3ffff << 5)
#घोषणा RG_DSI_V12_SEL			(7 << 5)
#घोषणा RG_DSI_V10_SEL			(7 << 8)
#घोषणा RG_DSI_V072_SEL			(7 << 11)
#घोषणा RG_DSI_V04_SEL			(7 << 14)
#घोषणा RG_DSI_V032_SEL			(7 << 17)
#घोषणा RG_DSI_V02_SEL			(7 << 20)
#घोषणा RG_DSI_BG_R1_TRIM		(0xf << 24)
#घोषणा RG_DSI_BG_R2_TRIM		(0xf << 28)

#घोषणा MIPITX_DSI_PLL_CON0	0x50
#घोषणा RG_DSI_MPPLL_PLL_EN		BIT(0)
#घोषणा RG_DSI_MPPLL_DIV_MSK		(0x1ff << 1)
#घोषणा RG_DSI_MPPLL_PREDIV		(3 << 1)
#घोषणा RG_DSI_MPPLL_TXDIV0		(3 << 3)
#घोषणा RG_DSI_MPPLL_TXDIV1		(3 << 5)
#घोषणा RG_DSI_MPPLL_POSDIV		(7 << 7)
#घोषणा RG_DSI_MPPLL_MONVC_EN		BIT(10)
#घोषणा RG_DSI_MPPLL_MONREF_EN		BIT(11)
#घोषणा RG_DSI_MPPLL_VOD_EN		BIT(12)

#घोषणा MIPITX_DSI_PLL_CON1	0x54
#घोषणा RG_DSI_MPPLL_SDM_FRA_EN		BIT(0)
#घोषणा RG_DSI_MPPLL_SDM_SSC_PH_INIT	BIT(1)
#घोषणा RG_DSI_MPPLL_SDM_SSC_EN		BIT(2)
#घोषणा RG_DSI_MPPLL_SDM_SSC_PRD	(0xffff << 16)

#घोषणा MIPITX_DSI_PLL_CON2	0x58

#घोषणा MIPITX_DSI_PLL_TOP	0x64
#घोषणा RG_DSI_MPPLL_PRESERVE		(0xff << 8)

#घोषणा MIPITX_DSI_PLL_PWR	0x68
#घोषणा RG_DSI_MPPLL_SDM_PWR_ON		BIT(0)
#घोषणा RG_DSI_MPPLL_SDM_ISO_EN		BIT(1)
#घोषणा RG_DSI_MPPLL_SDM_PWR_ACK	BIT(8)

#घोषणा MIPITX_DSI_SW_CTRL	0x80
#घोषणा SW_CTRL_EN			BIT(0)

#घोषणा MIPITX_DSI_SW_CTRL_CON0	0x84
#घोषणा SW_LNTC_LPTX_PRE_OE		BIT(0)
#घोषणा SW_LNTC_LPTX_OE			BIT(1)
#घोषणा SW_LNTC_LPTX_P			BIT(2)
#घोषणा SW_LNTC_LPTX_N			BIT(3)
#घोषणा SW_LNTC_HSTX_PRE_OE		BIT(4)
#घोषणा SW_LNTC_HSTX_OE			BIT(5)
#घोषणा SW_LNTC_HSTX_ZEROCLK		BIT(6)
#घोषणा SW_LNT0_LPTX_PRE_OE		BIT(7)
#घोषणा SW_LNT0_LPTX_OE			BIT(8)
#घोषणा SW_LNT0_LPTX_P			BIT(9)
#घोषणा SW_LNT0_LPTX_N			BIT(10)
#घोषणा SW_LNT0_HSTX_PRE_OE		BIT(11)
#घोषणा SW_LNT0_HSTX_OE			BIT(12)
#घोषणा SW_LNT0_LPRX_EN			BIT(13)
#घोषणा SW_LNT1_LPTX_PRE_OE		BIT(14)
#घोषणा SW_LNT1_LPTX_OE			BIT(15)
#घोषणा SW_LNT1_LPTX_P			BIT(16)
#घोषणा SW_LNT1_LPTX_N			BIT(17)
#घोषणा SW_LNT1_HSTX_PRE_OE		BIT(18)
#घोषणा SW_LNT1_HSTX_OE			BIT(19)
#घोषणा SW_LNT2_LPTX_PRE_OE		BIT(20)
#घोषणा SW_LNT2_LPTX_OE			BIT(21)
#घोषणा SW_LNT2_LPTX_P			BIT(22)
#घोषणा SW_LNT2_LPTX_N			BIT(23)
#घोषणा SW_LNT2_HSTX_PRE_OE		BIT(24)
#घोषणा SW_LNT2_HSTX_OE			BIT(25)

अटल पूर्णांक mtk_mipi_tx_pll_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_mipi_tx *mipi_tx = mtk_mipi_tx_from_clk_hw(hw);
	u8 txभाग, txभाग0, txभाग1;
	u64 pcw;

	dev_dbg(mipi_tx->dev, "prepare: %u Hz\n", mipi_tx->data_rate);

	अगर (mipi_tx->data_rate >= 500000000) अणु
		txभाग = 1;
		txभाग0 = 0;
		txभाग1 = 0;
	पूर्ण अन्यथा अगर (mipi_tx->data_rate >= 250000000) अणु
		txभाग = 2;
		txभाग0 = 1;
		txभाग1 = 0;
	पूर्ण अन्यथा अगर (mipi_tx->data_rate >= 125000000) अणु
		txभाग = 4;
		txभाग0 = 2;
		txभाग1 = 0;
	पूर्ण अन्यथा अगर (mipi_tx->data_rate > 62000000) अणु
		txभाग = 8;
		txभाग0 = 2;
		txभाग1 = 1;
	पूर्ण अन्यथा अगर (mipi_tx->data_rate >= 50000000) अणु
		txभाग = 16;
		txभाग0 = 2;
		txभाग1 = 2;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	mtk_mipi_tx_update_bits(mipi_tx, MIPITX_DSI_BG_CON,
				RG_DSI_VOUT_MSK |
				RG_DSI_BG_CKEN | RG_DSI_BG_CORE_EN,
				(4 << 20) | (4 << 17) | (4 << 14) |
				(4 << 11) | (4 << 8) | (4 << 5) |
				RG_DSI_BG_CKEN | RG_DSI_BG_CORE_EN);

	usleep_range(30, 100);

	mtk_mipi_tx_update_bits(mipi_tx, MIPITX_DSI_TOP_CON,
				RG_DSI_LNT_IMP_CAL_CODE | RG_DSI_LNT_HS_BIAS_EN,
				(8 << 4) | RG_DSI_LNT_HS_BIAS_EN);

	mtk_mipi_tx_set_bits(mipi_tx, MIPITX_DSI_CON,
			     RG_DSI_CKG_LDOOUT_EN | RG_DSI_LDOCORE_EN);

	mtk_mipi_tx_update_bits(mipi_tx, MIPITX_DSI_PLL_PWR,
				RG_DSI_MPPLL_SDM_PWR_ON |
				RG_DSI_MPPLL_SDM_ISO_EN,
				RG_DSI_MPPLL_SDM_PWR_ON);

	mtk_mipi_tx_clear_bits(mipi_tx, MIPITX_DSI_PLL_CON0,
			       RG_DSI_MPPLL_PLL_EN);

	mtk_mipi_tx_update_bits(mipi_tx, MIPITX_DSI_PLL_CON0,
				RG_DSI_MPPLL_TXDIV0 | RG_DSI_MPPLL_TXDIV1 |
				RG_DSI_MPPLL_PREDIV,
				(txभाग0 << 3) | (txभाग1 << 5));

	/*
	 * PLL PCW config
	 * PCW bit 24~30 = पूर्णांकeger part of pcw
	 * PCW bit 0~23 = fractional part of pcw
	 * pcw = data_Rate*4*txभाग/(Ref_clk*2);
	 * Post DIV =4, so need data_Rate*4
	 * Ref_clk is 26MHz
	 */
	pcw = भाग_u64(((u64)mipi_tx->data_rate * 2 * txभाग) << 24,
		      26000000);
	ग_लिखोl(pcw, mipi_tx->regs + MIPITX_DSI_PLL_CON2);

	mtk_mipi_tx_set_bits(mipi_tx, MIPITX_DSI_PLL_CON1,
			     RG_DSI_MPPLL_SDM_FRA_EN);

	mtk_mipi_tx_set_bits(mipi_tx, MIPITX_DSI_PLL_CON0, RG_DSI_MPPLL_PLL_EN);

	usleep_range(20, 100);

	mtk_mipi_tx_clear_bits(mipi_tx, MIPITX_DSI_PLL_CON1,
			       RG_DSI_MPPLL_SDM_SSC_EN);

	mtk_mipi_tx_update_bits(mipi_tx, MIPITX_DSI_PLL_TOP,
				RG_DSI_MPPLL_PRESERVE,
				mipi_tx->driver_data->mppll_preserve);

	वापस 0;
पूर्ण

अटल व्योम mtk_mipi_tx_pll_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_mipi_tx *mipi_tx = mtk_mipi_tx_from_clk_hw(hw);

	dev_dbg(mipi_tx->dev, "unprepare\n");

	mtk_mipi_tx_clear_bits(mipi_tx, MIPITX_DSI_PLL_CON0,
			       RG_DSI_MPPLL_PLL_EN);

	mtk_mipi_tx_update_bits(mipi_tx, MIPITX_DSI_PLL_TOP,
				RG_DSI_MPPLL_PRESERVE, 0);

	mtk_mipi_tx_update_bits(mipi_tx, MIPITX_DSI_PLL_PWR,
				RG_DSI_MPPLL_SDM_ISO_EN |
				RG_DSI_MPPLL_SDM_PWR_ON,
				RG_DSI_MPPLL_SDM_ISO_EN);

	mtk_mipi_tx_clear_bits(mipi_tx, MIPITX_DSI_TOP_CON,
			       RG_DSI_LNT_HS_BIAS_EN);

	mtk_mipi_tx_clear_bits(mipi_tx, MIPITX_DSI_CON,
			       RG_DSI_CKG_LDOOUT_EN | RG_DSI_LDOCORE_EN);

	mtk_mipi_tx_clear_bits(mipi_tx, MIPITX_DSI_BG_CON,
			       RG_DSI_BG_CKEN | RG_DSI_BG_CORE_EN);

	mtk_mipi_tx_clear_bits(mipi_tx, MIPITX_DSI_PLL_CON0,
			       RG_DSI_MPPLL_DIV_MSK);
पूर्ण

अटल दीर्घ mtk_mipi_tx_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				       अचिन्हित दीर्घ *prate)
अणु
	वापस clamp_val(rate, 50000000, 1250000000);
पूर्ण

अटल स्थिर काष्ठा clk_ops mtk_mipi_tx_pll_ops = अणु
	.prepare = mtk_mipi_tx_pll_prepare,
	.unprepare = mtk_mipi_tx_pll_unprepare,
	.round_rate = mtk_mipi_tx_pll_round_rate,
	.set_rate = mtk_mipi_tx_pll_set_rate,
	.recalc_rate = mtk_mipi_tx_pll_recalc_rate,
पूर्ण;

अटल व्योम mtk_mipi_tx_घातer_on_संकेत(काष्ठा phy *phy)
अणु
	काष्ठा mtk_mipi_tx *mipi_tx = phy_get_drvdata(phy);
	u32 reg;

	क्रम (reg = MIPITX_DSI_CLOCK_LANE;
	     reg <= MIPITX_DSI_DATA_LANE3; reg += 4)
		mtk_mipi_tx_set_bits(mipi_tx, reg, RG_DSI_LNTx_LDOOUT_EN);

	mtk_mipi_tx_clear_bits(mipi_tx, MIPITX_DSI_TOP_CON,
			       RG_DSI_PAD_TIE_LOW_EN);
पूर्ण

अटल व्योम mtk_mipi_tx_घातer_off_संकेत(काष्ठा phy *phy)
अणु
	काष्ठा mtk_mipi_tx *mipi_tx = phy_get_drvdata(phy);
	u32 reg;

	mtk_mipi_tx_set_bits(mipi_tx, MIPITX_DSI_TOP_CON,
			     RG_DSI_PAD_TIE_LOW_EN);

	क्रम (reg = MIPITX_DSI_CLOCK_LANE;
	     reg <= MIPITX_DSI_DATA_LANE3; reg += 4)
		mtk_mipi_tx_clear_bits(mipi_tx, reg, RG_DSI_LNTx_LDOOUT_EN);
पूर्ण

स्थिर काष्ठा mtk_mipitx_data mt2701_mipitx_data = अणु
	.mppll_preserve = (3 << 8),
	.mipi_tx_clk_ops = &mtk_mipi_tx_pll_ops,
	.mipi_tx_enable_संकेत = mtk_mipi_tx_घातer_on_संकेत,
	.mipi_tx_disable_संकेत = mtk_mipi_tx_घातer_off_संकेत,
पूर्ण;

स्थिर काष्ठा mtk_mipitx_data mt8173_mipitx_data = अणु
	.mppll_preserve = (0 << 8),
	.mipi_tx_clk_ops = &mtk_mipi_tx_pll_ops,
	.mipi_tx_enable_संकेत = mtk_mipi_tx_घातer_on_संकेत,
	.mipi_tx_disable_संकेत = mtk_mipi_tx_घातer_off_संकेत,
पूर्ण;
