<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 MediaTek Inc.
 * Author: Jie Qiu <jie.qiu@mediatek.com>
 */

#समावेश "phy-mtk-hdmi.h"

#घोषणा HDMI_CON0		0x00
#घोषणा RG_HDMITX_PLL_EN		BIT(31)
#घोषणा RG_HDMITX_PLL_FBKDIV		(0x7f << 24)
#घोषणा PLL_FBKDIV_SHIFT		24
#घोषणा RG_HDMITX_PLL_FBKSEL		(0x3 << 22)
#घोषणा PLL_FBKSEL_SHIFT		22
#घोषणा RG_HDMITX_PLL_PREDIV		(0x3 << 20)
#घोषणा PREDIV_SHIFT			20
#घोषणा RG_HDMITX_PLL_POSDIV		(0x3 << 18)
#घोषणा POSDIV_SHIFT			18
#घोषणा RG_HDMITX_PLL_RST_DLY		(0x3 << 16)
#घोषणा RG_HDMITX_PLL_IR		(0xf << 12)
#घोषणा PLL_IR_SHIFT			12
#घोषणा RG_HDMITX_PLL_IC		(0xf << 8)
#घोषणा PLL_IC_SHIFT			8
#घोषणा RG_HDMITX_PLL_BP		(0xf << 4)
#घोषणा PLL_BP_SHIFT			4
#घोषणा RG_HDMITX_PLL_BR		(0x3 << 2)
#घोषणा PLL_BR_SHIFT			2
#घोषणा RG_HDMITX_PLL_BC		(0x3 << 0)
#घोषणा PLL_BC_SHIFT			0
#घोषणा HDMI_CON1		0x04
#घोषणा RG_HDMITX_PLL_DIVEN		(0x7 << 29)
#घोषणा PLL_DIVEN_SHIFT			29
#घोषणा RG_HDMITX_PLL_AUTOK_EN		BIT(28)
#घोषणा RG_HDMITX_PLL_AUTOK_KF		(0x3 << 26)
#घोषणा RG_HDMITX_PLL_AUTOK_KS		(0x3 << 24)
#घोषणा RG_HDMITX_PLL_AUTOK_LOAD	BIT(23)
#घोषणा RG_HDMITX_PLL_BAND		(0x3f << 16)
#घोषणा RG_HDMITX_PLL_REF_SEL		BIT(15)
#घोषणा RG_HDMITX_PLL_BIAS_EN		BIT(14)
#घोषणा RG_HDMITX_PLL_BIAS_LPF_EN	BIT(13)
#घोषणा RG_HDMITX_PLL_TXDIV_EN		BIT(12)
#घोषणा RG_HDMITX_PLL_TXDIV		(0x3 << 10)
#घोषणा PLL_TXDIV_SHIFT			10
#घोषणा RG_HDMITX_PLL_LVROD_EN		BIT(9)
#घोषणा RG_HDMITX_PLL_MONVC_EN		BIT(8)
#घोषणा RG_HDMITX_PLL_MONCK_EN		BIT(7)
#घोषणा RG_HDMITX_PLL_MONREF_EN		BIT(6)
#घोषणा RG_HDMITX_PLL_TST_EN		BIT(5)
#घोषणा RG_HDMITX_PLL_TST_CK_EN		BIT(4)
#घोषणा RG_HDMITX_PLL_TST_SEL		(0xf << 0)
#घोषणा HDMI_CON2		0x08
#घोषणा RGS_HDMITX_PLL_AUTOK_BAND	(0x7f << 8)
#घोषणा RGS_HDMITX_PLL_AUTOK_FAIL	BIT(1)
#घोषणा RG_HDMITX_EN_TX_CKLDO		BIT(0)
#घोषणा HDMI_CON3		0x0c
#घोषणा RG_HDMITX_SER_EN		(0xf << 28)
#घोषणा RG_HDMITX_PRD_EN		(0xf << 24)
#घोषणा RG_HDMITX_PRD_IMP_EN		(0xf << 20)
#घोषणा RG_HDMITX_DRV_EN		(0xf << 16)
#घोषणा RG_HDMITX_DRV_IMP_EN		(0xf << 12)
#घोषणा DRV_IMP_EN_SHIFT		12
#घोषणा RG_HDMITX_MHLCK_FORCE		BIT(10)
#घोषणा RG_HDMITX_MHLCK_PPIX_EN		BIT(9)
#घोषणा RG_HDMITX_MHLCK_EN		BIT(8)
#घोषणा RG_HDMITX_SER_DIN_SEL		(0xf << 4)
#घोषणा RG_HDMITX_SER_5T1_BIST_EN	BIT(3)
#घोषणा RG_HDMITX_SER_BIST_TOG		BIT(2)
#घोषणा RG_HDMITX_SER_DIN_TOG		BIT(1)
#घोषणा RG_HDMITX_SER_CLKDIG_INV	BIT(0)
#घोषणा HDMI_CON4		0x10
#घोषणा RG_HDMITX_PRD_IBIAS_CLK		(0xf << 24)
#घोषणा RG_HDMITX_PRD_IBIAS_D2		(0xf << 16)
#घोषणा RG_HDMITX_PRD_IBIAS_D1		(0xf << 8)
#घोषणा RG_HDMITX_PRD_IBIAS_D0		(0xf << 0)
#घोषणा PRD_IBIAS_CLK_SHIFT		24
#घोषणा PRD_IBIAS_D2_SHIFT		16
#घोषणा PRD_IBIAS_D1_SHIFT		8
#घोषणा PRD_IBIAS_D0_SHIFT		0
#घोषणा HDMI_CON5		0x14
#घोषणा RG_HDMITX_DRV_IBIAS_CLK		(0x3f << 24)
#घोषणा RG_HDMITX_DRV_IBIAS_D2		(0x3f << 16)
#घोषणा RG_HDMITX_DRV_IBIAS_D1		(0x3f << 8)
#घोषणा RG_HDMITX_DRV_IBIAS_D0		(0x3f << 0)
#घोषणा DRV_IBIAS_CLK_SHIFT		24
#घोषणा DRV_IBIAS_D2_SHIFT		16
#घोषणा DRV_IBIAS_D1_SHIFT		8
#घोषणा DRV_IBIAS_D0_SHIFT		0
#घोषणा HDMI_CON6		0x18
#घोषणा RG_HDMITX_DRV_IMP_CLK		(0x3f << 24)
#घोषणा RG_HDMITX_DRV_IMP_D2		(0x3f << 16)
#घोषणा RG_HDMITX_DRV_IMP_D1		(0x3f << 8)
#घोषणा RG_HDMITX_DRV_IMP_D0		(0x3f << 0)
#घोषणा DRV_IMP_CLK_SHIFT		24
#घोषणा DRV_IMP_D2_SHIFT		16
#घोषणा DRV_IMP_D1_SHIFT		8
#घोषणा DRV_IMP_D0_SHIFT		0
#घोषणा HDMI_CON7		0x1c
#घोषणा RG_HDMITX_MHLCK_DRV_IBIAS	(0x1f << 27)
#घोषणा RG_HDMITX_SER_DIN		(0x3ff << 16)
#घोषणा RG_HDMITX_CHLDC_TST		(0xf << 12)
#घोषणा RG_HDMITX_CHLCK_TST		(0xf << 8)
#घोषणा RG_HDMITX_RESERVE		(0xff << 0)
#घोषणा HDMI_CON8		0x20
#घोषणा RGS_HDMITX_2T1_LEV		(0xf << 16)
#घोषणा RGS_HDMITX_2T1_EDG		(0xf << 12)
#घोषणा RGS_HDMITX_5T1_LEV		(0xf << 8)
#घोषणा RGS_HDMITX_5T1_EDG		(0xf << 4)
#घोषणा RGS_HDMITX_PLUG_TST		BIT(0)

अटल पूर्णांक mtk_hdmi_pll_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);

	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON1, RG_HDMITX_PLL_AUTOK_EN);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_PLL_POSDIV);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON3, RG_HDMITX_MHLCK_EN);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON1, RG_HDMITX_PLL_BIAS_EN);
	usleep_range(100, 150);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_PLL_EN);
	usleep_range(100, 150);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON1, RG_HDMITX_PLL_BIAS_LPF_EN);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON1, RG_HDMITX_PLL_TXDIV_EN);

	वापस 0;
पूर्ण

अटल व्योम mtk_hdmi_pll_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);

	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON1, RG_HDMITX_PLL_TXDIV_EN);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON1, RG_HDMITX_PLL_BIAS_LPF_EN);
	usleep_range(100, 150);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_PLL_EN);
	usleep_range(100, 150);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON1, RG_HDMITX_PLL_BIAS_EN);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_PLL_POSDIV);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON1, RG_HDMITX_PLL_AUTOK_EN);
	usleep_range(100, 150);
पूर्ण

अटल दीर्घ mtk_hdmi_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ *parent_rate)
अणु
	काष्ठा mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);

	hdmi_phy->pll_rate = rate;
	अगर (rate <= 74250000)
		*parent_rate = rate;
	अन्यथा
		*parent_rate = rate / 2;

	वापस rate;
पूर्ण

अटल पूर्णांक mtk_hdmi_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);
	अचिन्हित पूर्णांक pre_भाग;
	अचिन्हित पूर्णांक भाग;
	अचिन्हित पूर्णांक pre_ibias;
	अचिन्हित पूर्णांक hdmi_ibias;
	अचिन्हित पूर्णांक imp_en;

	dev_dbg(hdmi_phy->dev, "%s: %lu Hz, parent: %lu Hz\n", __func__,
		rate, parent_rate);

	अगर (rate <= 27000000) अणु
		pre_भाग = 0;
		भाग = 3;
	पूर्ण अन्यथा अगर (rate <= 74250000) अणु
		pre_भाग = 1;
		भाग = 2;
	पूर्ण अन्यथा अणु
		pre_भाग = 1;
		भाग = 1;
	पूर्ण

	mtk_hdmi_phy_mask(hdmi_phy, HDMI_CON0,
			  (pre_भाग << PREDIV_SHIFT), RG_HDMITX_PLL_PREDIV);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_PLL_POSDIV);
	mtk_hdmi_phy_mask(hdmi_phy, HDMI_CON0,
			  (0x1 << PLL_IC_SHIFT) | (0x1 << PLL_IR_SHIFT),
			  RG_HDMITX_PLL_IC | RG_HDMITX_PLL_IR);
	mtk_hdmi_phy_mask(hdmi_phy, HDMI_CON1,
			  (भाग << PLL_TXDIV_SHIFT), RG_HDMITX_PLL_TXDIV);
	mtk_hdmi_phy_mask(hdmi_phy, HDMI_CON0,
			  (0x1 << PLL_FBKSEL_SHIFT) | (19 << PLL_FBKDIV_SHIFT),
			  RG_HDMITX_PLL_FBKSEL | RG_HDMITX_PLL_FBKDIV);
	mtk_hdmi_phy_mask(hdmi_phy, HDMI_CON1,
			  (0x2 << PLL_DIVEN_SHIFT), RG_HDMITX_PLL_DIVEN);
	mtk_hdmi_phy_mask(hdmi_phy, HDMI_CON0,
			  (0xc << PLL_BP_SHIFT) | (0x2 << PLL_BC_SHIFT) |
			  (0x1 << PLL_BR_SHIFT),
			  RG_HDMITX_PLL_BP | RG_HDMITX_PLL_BC |
			  RG_HDMITX_PLL_BR);
	अगर (rate < 165000000) अणु
		mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON3,
					RG_HDMITX_PRD_IMP_EN);
		pre_ibias = 0x3;
		imp_en = 0x0;
		hdmi_ibias = hdmi_phy->ibias;
	पूर्ण अन्यथा अणु
		mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON3,
				      RG_HDMITX_PRD_IMP_EN);
		pre_ibias = 0x6;
		imp_en = 0xf;
		hdmi_ibias = hdmi_phy->ibias_up;
	पूर्ण
	mtk_hdmi_phy_mask(hdmi_phy, HDMI_CON4,
			  (pre_ibias << PRD_IBIAS_CLK_SHIFT) |
			  (pre_ibias << PRD_IBIAS_D2_SHIFT) |
			  (pre_ibias << PRD_IBIAS_D1_SHIFT) |
			  (pre_ibias << PRD_IBIAS_D0_SHIFT),
			  RG_HDMITX_PRD_IBIAS_CLK |
			  RG_HDMITX_PRD_IBIAS_D2 |
			  RG_HDMITX_PRD_IBIAS_D1 |
			  RG_HDMITX_PRD_IBIAS_D0);
	mtk_hdmi_phy_mask(hdmi_phy, HDMI_CON3,
			  (imp_en << DRV_IMP_EN_SHIFT),
			  RG_HDMITX_DRV_IMP_EN);
	mtk_hdmi_phy_mask(hdmi_phy, HDMI_CON6,
			  (hdmi_phy->drv_imp_clk << DRV_IMP_CLK_SHIFT) |
			  (hdmi_phy->drv_imp_d2 << DRV_IMP_D2_SHIFT) |
			  (hdmi_phy->drv_imp_d1 << DRV_IMP_D1_SHIFT) |
			  (hdmi_phy->drv_imp_d0 << DRV_IMP_D0_SHIFT),
			  RG_HDMITX_DRV_IMP_CLK | RG_HDMITX_DRV_IMP_D2 |
			  RG_HDMITX_DRV_IMP_D1 | RG_HDMITX_DRV_IMP_D0);
	mtk_hdmi_phy_mask(hdmi_phy, HDMI_CON5,
			  (hdmi_ibias << DRV_IBIAS_CLK_SHIFT) |
			  (hdmi_ibias << DRV_IBIAS_D2_SHIFT) |
			  (hdmi_ibias << DRV_IBIAS_D1_SHIFT) |
			  (hdmi_ibias << DRV_IBIAS_D0_SHIFT),
			  RG_HDMITX_DRV_IBIAS_CLK |
			  RG_HDMITX_DRV_IBIAS_D2 |
			  RG_HDMITX_DRV_IBIAS_D1 |
			  RG_HDMITX_DRV_IBIAS_D0);
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ mtk_hdmi_pll_recalc_rate(काष्ठा clk_hw *hw,
					      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);

	वापस hdmi_phy->pll_rate;
पूर्ण

अटल स्थिर काष्ठा clk_ops mtk_hdmi_phy_pll_ops = अणु
	.prepare = mtk_hdmi_pll_prepare,
	.unprepare = mtk_hdmi_pll_unprepare,
	.set_rate = mtk_hdmi_pll_set_rate,
	.round_rate = mtk_hdmi_pll_round_rate,
	.recalc_rate = mtk_hdmi_pll_recalc_rate,
पूर्ण;

अटल व्योम mtk_hdmi_phy_enable_पंचांगds(काष्ठा mtk_hdmi_phy *hdmi_phy)
अणु
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON3,
			      RG_HDMITX_SER_EN | RG_HDMITX_PRD_EN |
			      RG_HDMITX_DRV_EN);
	usleep_range(100, 150);
पूर्ण

अटल व्योम mtk_hdmi_phy_disable_पंचांगds(काष्ठा mtk_hdmi_phy *hdmi_phy)
अणु
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON3,
				RG_HDMITX_DRV_EN | RG_HDMITX_PRD_EN |
				RG_HDMITX_SER_EN);
पूर्ण

काष्ठा mtk_hdmi_phy_conf mtk_hdmi_phy_8173_conf = अणु
	.flags = CLK_SET_RATE_PARENT | CLK_SET_RATE_GATE,
	.hdmi_phy_clk_ops = &mtk_hdmi_phy_pll_ops,
	.hdmi_phy_enable_पंचांगds = mtk_hdmi_phy_enable_पंचांगds,
	.hdmi_phy_disable_पंचांगds = mtk_hdmi_phy_disable_पंचांगds,
पूर्ण;

MODULE_AUTHOR("Jie Qiu <jie.qiu@mediatek.com>");
MODULE_DESCRIPTION("MediaTek MT8173 HDMI PHY Driver");
MODULE_LICENSE("GPL v2");
