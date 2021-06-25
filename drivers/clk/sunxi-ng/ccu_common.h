<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2016 Maxime Ripard. All rights reserved.
 */

#अगर_अघोषित _COMMON_H_
#घोषणा _COMMON_H_

#समावेश <linux/compiler.h>
#समावेश <linux/clk-provider.h>

#घोषणा CCU_FEATURE_FRACTIONAL		BIT(0)
#घोषणा CCU_FEATURE_VARIABLE_PREDIV	BIT(1)
#घोषणा CCU_FEATURE_FIXED_PREDIV	BIT(2)
#घोषणा CCU_FEATURE_FIXED_POSTDIV	BIT(3)
#घोषणा CCU_FEATURE_ALL_PREDIV		BIT(4)
#घोषणा CCU_FEATURE_LOCK_REG		BIT(5)
#घोषणा CCU_FEATURE_MMC_TIMING_SWITCH	BIT(6)
#घोषणा CCU_FEATURE_SIGMA_DELTA_MOD	BIT(7)

/* MMC timing mode चयन bit */
#घोषणा CCU_MMC_NEW_TIMING_MODE		BIT(30)

काष्ठा device_node;

काष्ठा ccu_common अणु
	व्योम __iomem	*base;
	u16		reg;
	u16		lock_reg;
	u32		preभाग;

	अचिन्हित दीर्घ	features;
	spinlock_t	*lock;
	काष्ठा clk_hw	hw;
पूर्ण;

अटल अंतरभूत काष्ठा ccu_common *hw_to_ccu_common(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा ccu_common, hw);
पूर्ण

काष्ठा sunxi_ccu_desc अणु
	काष्ठा ccu_common		**ccu_clks;
	अचिन्हित दीर्घ			num_ccu_clks;

	काष्ठा clk_hw_onecell_data	*hw_clks;

	काष्ठा ccu_reset_map		*resets;
	अचिन्हित दीर्घ			num_resets;
पूर्ण;

व्योम ccu_helper_रुको_क्रम_lock(काष्ठा ccu_common *common, u32 lock);

काष्ठा ccu_pll_nb अणु
	काष्ठा notअगरier_block	clk_nb;
	काष्ठा ccu_common	*common;

	u32	enable;
	u32	lock;
पूर्ण;

#घोषणा to_ccu_pll_nb(_nb) container_of(_nb, काष्ठा ccu_pll_nb, clk_nb)

पूर्णांक ccu_pll_notअगरier_रेजिस्टर(काष्ठा ccu_pll_nb *pll_nb);

पूर्णांक sunxi_ccu_probe(काष्ठा device_node *node, व्योम __iomem *reg,
		    स्थिर काष्ठा sunxi_ccu_desc *desc);

#पूर्ण_अगर /* _COMMON_H_ */
