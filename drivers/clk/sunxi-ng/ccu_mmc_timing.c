<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2017 Chen-Yu Tsai. All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/clk/sunxi-ng.h>
#समावेश <linux/पन.स>

#समावेश "ccu_common.h"

/**
 * sunxi_ccu_set_mmc_timing_mode: Configure the MMC घड़ी timing mode
 * @clk: घड़ी to be configured
 * @new_mode: true क्रम new timing mode पूर्णांकroduced in A83T and later
 *
 * Returns 0 on success, -ENOTSUPP अगर the घड़ी करोes not support
 * चयनing modes.
 */
पूर्णांक sunxi_ccu_set_mmc_timing_mode(काष्ठा clk *clk, bool new_mode)
अणु
	काष्ठा clk_hw *hw = __clk_get_hw(clk);
	काष्ठा ccu_common *cm = hw_to_ccu_common(hw);
	अचिन्हित दीर्घ flags;
	u32 val;

	अगर (!(cm->features & CCU_FEATURE_MMC_TIMING_SWITCH))
		वापस -ENOTSUPP;

	spin_lock_irqsave(cm->lock, flags);

	val = पढ़ोl(cm->base + cm->reg);
	अगर (new_mode)
		val |= CCU_MMC_NEW_TIMING_MODE;
	अन्यथा
		val &= ~CCU_MMC_NEW_TIMING_MODE;
	ग_लिखोl(val, cm->base + cm->reg);

	spin_unlock_irqrestore(cm->lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sunxi_ccu_set_mmc_timing_mode);

/**
 * sunxi_ccu_set_mmc_timing_mode: Get the current MMC घड़ी timing mode
 * @clk: घड़ी to query
 *
 * Returns 0 अगर the घड़ी is in old timing mode, > 0 अगर it is in
 * new timing mode, and -ENOTSUPP अगर the घड़ी करोes not support
 * this function.
 */
पूर्णांक sunxi_ccu_get_mmc_timing_mode(काष्ठा clk *clk)
अणु
	काष्ठा clk_hw *hw = __clk_get_hw(clk);
	काष्ठा ccu_common *cm = hw_to_ccu_common(hw);

	अगर (!(cm->features & CCU_FEATURE_MMC_TIMING_SWITCH))
		वापस -ENOTSUPP;

	वापस !!(पढ़ोl(cm->base + cm->reg) & CCU_MMC_NEW_TIMING_MODE);
पूर्ण
EXPORT_SYMBOL_GPL(sunxi_ccu_get_mmc_timing_mode);
