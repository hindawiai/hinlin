<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (c) 2014, The Linux Foundation. All rights reserved. */

#अगर_अघोषित __QCOM_CLK_REGMAP_H__
#घोषणा __QCOM_CLK_REGMAP_H__

#समावेश <linux/clk-provider.h>

काष्ठा regmap;

/**
 * काष्ठा clk_regmap - regmap supporting घड़ी
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @regmap:	regmap to use क्रम regmap helpers and/or by providers
 * @enable_reg: रेजिस्टर when using regmap enable/disable ops
 * @enable_mask: mask when using regmap enable/disable ops
 * @enable_is_inverted: flag to indicate set enable_mask bits to disable
 *                      when using घड़ी_enable_regmap and मित्रs APIs.
 */
काष्ठा clk_regmap अणु
	काष्ठा clk_hw hw;
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक enable_reg;
	अचिन्हित पूर्णांक enable_mask;
	bool enable_is_inverted;
पूर्ण;

अटल अंतरभूत काष्ठा clk_regmap *to_clk_regmap(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा clk_regmap, hw);
पूर्ण

पूर्णांक clk_is_enabled_regmap(काष्ठा clk_hw *hw);
पूर्णांक clk_enable_regmap(काष्ठा clk_hw *hw);
व्योम clk_disable_regmap(काष्ठा clk_hw *hw);
पूर्णांक devm_clk_रेजिस्टर_regmap(काष्ठा device *dev, काष्ठा clk_regmap *rclk);

#पूर्ण_अगर
