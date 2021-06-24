<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/device.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/regmap.h>
#समावेश <linux/export.h>

#समावेश "clk-regmap.h"

/**
 * clk_is_enabled_regmap - standard is_enabled() क्रम regmap users
 *
 * @hw: clk to operate on
 *
 * Clocks that use regmap क्रम their रेजिस्टर I/O can set the
 * enable_reg and enable_mask fields in their काष्ठा clk_regmap and then use
 * this as their is_enabled operation, saving some code.
 */
पूर्णांक clk_is_enabled_regmap(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_regmap *rclk = to_clk_regmap(hw);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(rclk->regmap, rclk->enable_reg, &val);
	अगर (ret != 0)
		वापस ret;

	अगर (rclk->enable_is_inverted)
		वापस (val & rclk->enable_mask) == 0;
	अन्यथा
		वापस (val & rclk->enable_mask) != 0;
पूर्ण
EXPORT_SYMBOL_GPL(clk_is_enabled_regmap);

/**
 * clk_enable_regmap - standard enable() क्रम regmap users
 *
 * @hw: clk to operate on
 *
 * Clocks that use regmap क्रम their रेजिस्टर I/O can set the
 * enable_reg and enable_mask fields in their काष्ठा clk_regmap and then use
 * this as their enable() operation, saving some code.
 */
पूर्णांक clk_enable_regmap(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_regmap *rclk = to_clk_regmap(hw);
	अचिन्हित पूर्णांक val;

	अगर (rclk->enable_is_inverted)
		val = 0;
	अन्यथा
		val = rclk->enable_mask;

	वापस regmap_update_bits(rclk->regmap, rclk->enable_reg,
				  rclk->enable_mask, val);
पूर्ण
EXPORT_SYMBOL_GPL(clk_enable_regmap);

/**
 * clk_disable_regmap - standard disable() क्रम regmap users
 *
 * @hw: clk to operate on
 *
 * Clocks that use regmap क्रम their रेजिस्टर I/O can set the
 * enable_reg and enable_mask fields in their काष्ठा clk_regmap and then use
 * this as their disable() operation, saving some code.
 */
व्योम clk_disable_regmap(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_regmap *rclk = to_clk_regmap(hw);
	अचिन्हित पूर्णांक val;

	अगर (rclk->enable_is_inverted)
		val = rclk->enable_mask;
	अन्यथा
		val = 0;

	regmap_update_bits(rclk->regmap, rclk->enable_reg, rclk->enable_mask,
			   val);
पूर्ण
EXPORT_SYMBOL_GPL(clk_disable_regmap);

/**
 * devm_clk_रेजिस्टर_regmap - रेजिस्टर a clk_regmap घड़ी
 *
 * @dev: reference to the caller's device
 * @rclk: clk to operate on
 *
 * Clocks that use regmap क्रम their रेजिस्टर I/O should रेजिस्टर their
 * clk_regmap काष्ठा via this function so that the regmap is initialized
 * and so that the घड़ी is रेजिस्टरed with the common घड़ी framework.
 */
पूर्णांक devm_clk_रेजिस्टर_regmap(काष्ठा device *dev, काष्ठा clk_regmap *rclk)
अणु
	अगर (dev && dev_get_regmap(dev, शून्य))
		rclk->regmap = dev_get_regmap(dev, शून्य);
	अन्यथा अगर (dev && dev->parent)
		rclk->regmap = dev_get_regmap(dev->parent, शून्य);

	वापस devm_clk_hw_रेजिस्टर(dev, &rclk->hw);
पूर्ण
EXPORT_SYMBOL_GPL(devm_clk_रेजिस्टर_regmap);
