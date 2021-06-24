<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2018 MediaTek Inc.
 * Author: Chunhui Dai <chunhui.dai@mediatek.com>
 */

#अगर_अघोषित _MTK_HDMI_PHY_H
#घोषणा _MTK_HDMI_PHY_H
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/types.h>

काष्ठा mtk_hdmi_phy;

काष्ठा mtk_hdmi_phy_conf अणु
	अचिन्हित दीर्घ flags;
	bool pll_शेष_off;
	स्थिर काष्ठा clk_ops *hdmi_phy_clk_ops;
	व्योम (*hdmi_phy_enable_पंचांगds)(काष्ठा mtk_hdmi_phy *hdmi_phy);
	व्योम (*hdmi_phy_disable_पंचांगds)(काष्ठा mtk_hdmi_phy *hdmi_phy);
पूर्ण;

काष्ठा mtk_hdmi_phy अणु
	व्योम __iomem *regs;
	काष्ठा device *dev;
	काष्ठा mtk_hdmi_phy_conf *conf;
	काष्ठा clk *pll;
	काष्ठा clk_hw pll_hw;
	अचिन्हित दीर्घ pll_rate;
	अचिन्हित अक्षर drv_imp_clk;
	अचिन्हित अक्षर drv_imp_d2;
	अचिन्हित अक्षर drv_imp_d1;
	अचिन्हित अक्षर drv_imp_d0;
	अचिन्हित पूर्णांक ibias;
	अचिन्हित पूर्णांक ibias_up;
पूर्ण;

व्योम mtk_hdmi_phy_clear_bits(काष्ठा mtk_hdmi_phy *hdmi_phy, u32 offset,
			     u32 bits);
व्योम mtk_hdmi_phy_set_bits(काष्ठा mtk_hdmi_phy *hdmi_phy, u32 offset,
			   u32 bits);
व्योम mtk_hdmi_phy_mask(काष्ठा mtk_hdmi_phy *hdmi_phy, u32 offset,
		       u32 val, u32 mask);
काष्ठा mtk_hdmi_phy *to_mtk_hdmi_phy(काष्ठा clk_hw *hw);

बाह्य काष्ठा mtk_hdmi_phy_conf mtk_hdmi_phy_8173_conf;
बाह्य काष्ठा mtk_hdmi_phy_conf mtk_hdmi_phy_2701_conf;

#पूर्ण_अगर /* _MTK_HDMI_PHY_H */
