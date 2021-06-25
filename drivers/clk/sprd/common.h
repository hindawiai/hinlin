<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
//
// Spपढ़ोtrum घड़ी infraकाष्ठाure
//
// Copyright (C) 2017 Spपढ़ोtrum, Inc.
// Author: Chunyan Zhang <chunyan.zhang@spपढ़ोtrum.com>

#अगर_अघोषित _SPRD_CLK_COMMON_H_
#घोषणा _SPRD_CLK_COMMON_H_

#समावेश <linux/clk-provider.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/regmap.h>

काष्ठा device_node;

काष्ठा sprd_clk_common अणु
	काष्ठा regmap	*regmap;
	u32		reg;
	काष्ठा clk_hw	hw;
पूर्ण;

काष्ठा sprd_clk_desc अणु
	काष्ठा sprd_clk_common		**clk_clks;
	अचिन्हित दीर्घ			num_clk_clks;
	काष्ठा clk_hw_onecell_data      *hw_clks;
पूर्ण;

अटल अंतरभूत काष्ठा sprd_clk_common *
	hw_to_sprd_clk_common(स्थिर काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा sprd_clk_common, hw);
पूर्ण
पूर्णांक sprd_clk_regmap_init(काष्ठा platक्रमm_device *pdev,
			 स्थिर काष्ठा sprd_clk_desc *desc);
पूर्णांक sprd_clk_probe(काष्ठा device *dev, काष्ठा clk_hw_onecell_data *clkhw);

#पूर्ण_अगर /* _SPRD_CLK_COMMON_H_ */
