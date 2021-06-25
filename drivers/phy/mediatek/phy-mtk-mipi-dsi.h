<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2019 MediaTek Inc.
 * Author: Jitao Shi <jitao.shi@mediatek.com>
 */

#अगर_अघोषित _MTK_MIPI_TX_H
#घोषणा _MTK_MIPI_TX_H

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/nvmem-consumer.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/slab.h>

काष्ठा mtk_mipitx_data अणु
	स्थिर u32 mppll_preserve;
	स्थिर काष्ठा clk_ops *mipi_tx_clk_ops;
	व्योम (*mipi_tx_enable_संकेत)(काष्ठा phy *phy);
	व्योम (*mipi_tx_disable_संकेत)(काष्ठा phy *phy);
पूर्ण;

काष्ठा mtk_mipi_tx अणु
	काष्ठा device *dev;
	व्योम __iomem *regs;
	u32 data_rate;
	u32 mipitx_drive;
	u32 rt_code[5];
	स्थिर काष्ठा mtk_mipitx_data *driver_data;
	काष्ठा clk_hw pll_hw;
	काष्ठा clk *pll;
पूर्ण;

काष्ठा mtk_mipi_tx *mtk_mipi_tx_from_clk_hw(काष्ठा clk_hw *hw);
व्योम mtk_mipi_tx_clear_bits(काष्ठा mtk_mipi_tx *mipi_tx, u32 offset, u32 bits);
व्योम mtk_mipi_tx_set_bits(काष्ठा mtk_mipi_tx *mipi_tx, u32 offset, u32 bits);
व्योम mtk_mipi_tx_update_bits(काष्ठा mtk_mipi_tx *mipi_tx, u32 offset, u32 mask,
			     u32 data);
पूर्णांक mtk_mipi_tx_pll_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			     अचिन्हित दीर्घ parent_rate);
अचिन्हित दीर्घ mtk_mipi_tx_pll_recalc_rate(काष्ठा clk_hw *hw,
					  अचिन्हित दीर्घ parent_rate);

बाह्य स्थिर काष्ठा mtk_mipitx_data mt2701_mipitx_data;
बाह्य स्थिर काष्ठा mtk_mipitx_data mt8173_mipitx_data;
बाह्य स्थिर काष्ठा mtk_mipitx_data mt8183_mipitx_data;

#पूर्ण_अगर
