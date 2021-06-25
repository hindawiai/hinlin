<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 MediaTek Inc.
 * Author: Chunhui Dai <chunhui.dai@mediatek.com>
 */

#समावेश "phy-mtk-hdmi.h"

#घोषणा HDMI_CON0	0x00
#घोषणा RG_HDMITX_DRV_IBIAS		0
#घोषणा RG_HDMITX_DRV_IBIAS_MASK	(0x3f << 0)
#घोषणा RG_HDMITX_EN_SER		12
#घोषणा RG_HDMITX_EN_SER_MASK		(0x0f << 12)
#घोषणा RG_HDMITX_EN_SLDO		16
#घोषणा RG_HDMITX_EN_SLDO_MASK		(0x0f << 16)
#घोषणा RG_HDMITX_EN_PRED		20
#घोषणा RG_HDMITX_EN_PRED_MASK		(0x0f << 20)
#घोषणा RG_HDMITX_EN_IMP		24
#घोषणा RG_HDMITX_EN_IMP_MASK		(0x0f << 24)
#घोषणा RG_HDMITX_EN_DRV		28
#घोषणा RG_HDMITX_EN_DRV_MASK		(0x0f << 28)

#घोषणा HDMI_CON1	0x04
#घोषणा RG_HDMITX_PRED_IBIAS		18
#घोषणा RG_HDMITX_PRED_IBIAS_MASK	(0x0f << 18)
#घोषणा RG_HDMITX_PRED_IMP		(0x01 << 22)
#घोषणा RG_HDMITX_DRV_IMP		26
#घोषणा RG_HDMITX_DRV_IMP_MASK		(0x3f << 26)

#घोषणा HDMI_CON2	0x08
#घोषणा RG_HDMITX_EN_TX_CKLDO		(0x01 << 0)
#घोषणा RG_HDMITX_EN_TX_POSDIV		(0x01 << 1)
#घोषणा RG_HDMITX_TX_POSDIV		3
#घोषणा RG_HDMITX_TX_POSDIV_MASK	(0x03 << 3)
#घोषणा RG_HDMITX_EN_MBIAS		(0x01 << 6)
#घोषणा RG_HDMITX_MBIAS_LPF_EN		(0x01 << 7)

#घोषणा HDMI_CON4	0x10
#घोषणा RG_HDMITX_RESERVE_MASK		(0xffffffff << 0)

#घोषणा HDMI_CON6	0x18
#घोषणा RG_HTPLL_BR			0
#घोषणा RG_HTPLL_BR_MASK		(0x03 << 0)
#घोषणा RG_HTPLL_BC			2
#घोषणा RG_HTPLL_BC_MASK		(0x03 << 2)
#घोषणा RG_HTPLL_BP			4
#घोषणा RG_HTPLL_BP_MASK		(0x0f << 4)
#घोषणा RG_HTPLL_IR			8
#घोषणा RG_HTPLL_IR_MASK		(0x0f << 8)
#घोषणा RG_HTPLL_IC			12
#घोषणा RG_HTPLL_IC_MASK		(0x0f << 12)
#घोषणा RG_HTPLL_POSDIV			16
#घोषणा RG_HTPLL_POSDIV_MASK		(0x03 << 16)
#घोषणा RG_HTPLL_PREDIV			18
#घोषणा RG_HTPLL_PREDIV_MASK		(0x03 << 18)
#घोषणा RG_HTPLL_FBKSEL			20
#घोषणा RG_HTPLL_FBKSEL_MASK		(0x03 << 20)
#घोषणा RG_HTPLL_RLH_EN			(0x01 << 22)
#घोषणा RG_HTPLL_FBKDIV			24
#घोषणा RG_HTPLL_FBKDIV_MASK		(0x7f << 24)
#घोषणा RG_HTPLL_EN			(0x01 << 31)

#घोषणा HDMI_CON7	0x1c
#घोषणा RG_HTPLL_AUTOK_EN		(0x01 << 23)
#घोषणा RG_HTPLL_DIVEN			28
#घोषणा RG_HTPLL_DIVEN_MASK		(0x07 << 28)

अटल पूर्णांक mtk_hdmi_pll_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);

	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON7, RG_HTPLL_AUTOK_EN);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON6, RG_HTPLL_RLH_EN);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON6, RG_HTPLL_POSDIV_MASK);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON2, RG_HDMITX_EN_MBIAS);
	usleep_range(80, 100);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON6, RG_HTPLL_EN);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON2, RG_HDMITX_EN_TX_CKLDO);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_EN_SLDO_MASK);
	usleep_range(80, 100);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON2, RG_HDMITX_MBIAS_LPF_EN);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_EN_SER_MASK);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_EN_PRED_MASK);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_EN_DRV_MASK);
	usleep_range(80, 100);
	वापस 0;
पूर्ण

अटल व्योम mtk_hdmi_pll_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);

	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_EN_DRV_MASK);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_EN_PRED_MASK);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_EN_SER_MASK);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON2, RG_HDMITX_MBIAS_LPF_EN);
	usleep_range(80, 100);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_EN_SLDO_MASK);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON2, RG_HDMITX_EN_TX_CKLDO);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON6, RG_HTPLL_EN);
	usleep_range(80, 100);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON2, RG_HDMITX_EN_MBIAS);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON6, RG_HTPLL_POSDIV_MASK);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON6, RG_HTPLL_RLH_EN);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON7, RG_HTPLL_AUTOK_EN);
	usleep_range(80, 100);
पूर्ण

अटल दीर्घ mtk_hdmi_pll_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ *parent_rate)
अणु
	वापस rate;
पूर्ण

अटल पूर्णांक mtk_hdmi_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);
	u32 pos_भाग;

	अगर (rate <= 64000000)
		pos_भाग = 3;
	अन्यथा अगर (rate <= 128000000)
		pos_भाग = 2;
	अन्यथा
		pos_भाग = 1;

	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON6, RG_HTPLL_PREDIV_MASK);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON6, RG_HTPLL_POSDIV_MASK);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON2, RG_HDMITX_EN_TX_POSDIV);
	mtk_hdmi_phy_mask(hdmi_phy, HDMI_CON6, (0x1 << RG_HTPLL_IC),
			  RG_HTPLL_IC_MASK);
	mtk_hdmi_phy_mask(hdmi_phy, HDMI_CON6, (0x1 << RG_HTPLL_IR),
			  RG_HTPLL_IR_MASK);
	mtk_hdmi_phy_mask(hdmi_phy, HDMI_CON2, (pos_भाग << RG_HDMITX_TX_POSDIV),
			  RG_HDMITX_TX_POSDIV_MASK);
	mtk_hdmi_phy_mask(hdmi_phy, HDMI_CON6, (1 << RG_HTPLL_FBKSEL),
			  RG_HTPLL_FBKSEL_MASK);
	mtk_hdmi_phy_mask(hdmi_phy, HDMI_CON6, (19 << RG_HTPLL_FBKDIV),
			  RG_HTPLL_FBKDIV_MASK);
	mtk_hdmi_phy_mask(hdmi_phy, HDMI_CON7, (0x2 << RG_HTPLL_DIVEN),
			  RG_HTPLL_DIVEN_MASK);
	mtk_hdmi_phy_mask(hdmi_phy, HDMI_CON6, (0xc << RG_HTPLL_BP),
			  RG_HTPLL_BP_MASK);
	mtk_hdmi_phy_mask(hdmi_phy, HDMI_CON6, (0x2 << RG_HTPLL_BC),
			  RG_HTPLL_BC_MASK);
	mtk_hdmi_phy_mask(hdmi_phy, HDMI_CON6, (0x1 << RG_HTPLL_BR),
			  RG_HTPLL_BR_MASK);

	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON1, RG_HDMITX_PRED_IMP);
	mtk_hdmi_phy_mask(hdmi_phy, HDMI_CON1, (0x3 << RG_HDMITX_PRED_IBIAS),
			  RG_HDMITX_PRED_IBIAS_MASK);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_EN_IMP_MASK);
	mtk_hdmi_phy_mask(hdmi_phy, HDMI_CON1, (0x28 << RG_HDMITX_DRV_IMP),
			  RG_HDMITX_DRV_IMP_MASK);
	mtk_hdmi_phy_mask(hdmi_phy, HDMI_CON4, 0x28, RG_HDMITX_RESERVE_MASK);
	mtk_hdmi_phy_mask(hdmi_phy, HDMI_CON0, (0xa << RG_HDMITX_DRV_IBIAS),
			  RG_HDMITX_DRV_IBIAS_MASK);
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ mtk_hdmi_pll_recalc_rate(काष्ठा clk_hw *hw,
					      अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा mtk_hdmi_phy *hdmi_phy = to_mtk_hdmi_phy(hw);
	अचिन्हित दीर्घ out_rate, val;

	val = (पढ़ोl(hdmi_phy->regs + HDMI_CON6)
	       & RG_HTPLL_PREDIV_MASK) >> RG_HTPLL_PREDIV;
	चयन (val) अणु
	हाल 0x00:
		out_rate = parent_rate;
		अवरोध;
	हाल 0x01:
		out_rate = parent_rate / 2;
		अवरोध;
	शेष:
		out_rate = parent_rate / 4;
		अवरोध;
	पूर्ण

	val = (पढ़ोl(hdmi_phy->regs + HDMI_CON6)
	       & RG_HTPLL_FBKDIV_MASK) >> RG_HTPLL_FBKDIV;
	out_rate *= (val + 1) * 2;
	val = (पढ़ोl(hdmi_phy->regs + HDMI_CON2)
	       & RG_HDMITX_TX_POSDIV_MASK);
	out_rate >>= (val >> RG_HDMITX_TX_POSDIV);

	अगर (पढ़ोl(hdmi_phy->regs + HDMI_CON2) & RG_HDMITX_EN_TX_POSDIV)
		out_rate /= 5;

	वापस out_rate;
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
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON7, RG_HTPLL_AUTOK_EN);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON6, RG_HTPLL_RLH_EN);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON6, RG_HTPLL_POSDIV_MASK);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON2, RG_HDMITX_EN_MBIAS);
	usleep_range(80, 100);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON6, RG_HTPLL_EN);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON2, RG_HDMITX_EN_TX_CKLDO);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_EN_SLDO_MASK);
	usleep_range(80, 100);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON2, RG_HDMITX_MBIAS_LPF_EN);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_EN_SER_MASK);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_EN_PRED_MASK);
	mtk_hdmi_phy_set_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_EN_DRV_MASK);
	usleep_range(80, 100);
पूर्ण

अटल व्योम mtk_hdmi_phy_disable_पंचांगds(काष्ठा mtk_hdmi_phy *hdmi_phy)
अणु
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_EN_DRV_MASK);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_EN_PRED_MASK);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_EN_SER_MASK);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON2, RG_HDMITX_MBIAS_LPF_EN);
	usleep_range(80, 100);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON0, RG_HDMITX_EN_SLDO_MASK);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON2, RG_HDMITX_EN_TX_CKLDO);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON6, RG_HTPLL_EN);
	usleep_range(80, 100);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON2, RG_HDMITX_EN_MBIAS);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON6, RG_HTPLL_POSDIV_MASK);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON6, RG_HTPLL_RLH_EN);
	mtk_hdmi_phy_clear_bits(hdmi_phy, HDMI_CON7, RG_HTPLL_AUTOK_EN);
	usleep_range(80, 100);
पूर्ण

काष्ठा mtk_hdmi_phy_conf mtk_hdmi_phy_2701_conf = अणु
	.flags = CLK_SET_RATE_GATE,
	.pll_शेष_off = true,
	.hdmi_phy_clk_ops = &mtk_hdmi_phy_pll_ops,
	.hdmi_phy_enable_पंचांगds = mtk_hdmi_phy_enable_पंचांगds,
	.hdmi_phy_disable_पंचांगds = mtk_hdmi_phy_disable_पंचांगds,
पूर्ण;

MODULE_AUTHOR("Chunhui Dai <chunhui.dai@mediatek.com>");
MODULE_DESCRIPTION("MediaTek HDMI PHY Driver");
MODULE_LICENSE("GPL v2");
