<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PRCC घड़ी implementation क्रम ux500 platक्रमm.
 *
 * Copyright (C) 2012 ST-Ericsson SA
 * Author: Ulf Hansson <ulf.hansson@linaro.org>
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/types.h>

#समावेश "clk.h"

#घोषणा PRCC_PCKEN			0x000
#घोषणा PRCC_PCKDIS			0x004
#घोषणा PRCC_KCKEN			0x008
#घोषणा PRCC_KCKDIS			0x00C
#घोषणा PRCC_PCKSR			0x010
#घोषणा PRCC_KCKSR			0x014

#घोषणा to_clk_prcc(_hw) container_of(_hw, काष्ठा clk_prcc, hw)

काष्ठा clk_prcc अणु
	काष्ठा clk_hw hw;
	व्योम __iomem *base;
	u32 cg_sel;
	पूर्णांक is_enabled;
पूर्ण;

/* PRCC घड़ी operations. */

अटल पूर्णांक clk_prcc_pclk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_prcc *clk = to_clk_prcc(hw);

	ग_लिखोl(clk->cg_sel, (clk->base + PRCC_PCKEN));
	जबतक (!(पढ़ोl(clk->base + PRCC_PCKSR) & clk->cg_sel))
		cpu_relax();

	clk->is_enabled = 1;
	वापस 0;
पूर्ण

अटल व्योम clk_prcc_pclk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_prcc *clk = to_clk_prcc(hw);

	ग_लिखोl(clk->cg_sel, (clk->base + PRCC_PCKDIS));
	clk->is_enabled = 0;
पूर्ण

अटल पूर्णांक clk_prcc_kclk_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_prcc *clk = to_clk_prcc(hw);

	ग_लिखोl(clk->cg_sel, (clk->base + PRCC_KCKEN));
	जबतक (!(पढ़ोl(clk->base + PRCC_KCKSR) & clk->cg_sel))
		cpu_relax();

	clk->is_enabled = 1;
	वापस 0;
पूर्ण

अटल व्योम clk_prcc_kclk_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_prcc *clk = to_clk_prcc(hw);

	ग_लिखोl(clk->cg_sel, (clk->base + PRCC_KCKDIS));
	clk->is_enabled = 0;
पूर्ण

अटल पूर्णांक clk_prcc_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_prcc *clk = to_clk_prcc(hw);
	वापस clk->is_enabled;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_prcc_pclk_ops = अणु
	.enable = clk_prcc_pclk_enable,
	.disable = clk_prcc_pclk_disable,
	.is_enabled = clk_prcc_is_enabled,
पूर्ण;

अटल स्थिर काष्ठा clk_ops clk_prcc_kclk_ops = अणु
	.enable = clk_prcc_kclk_enable,
	.disable = clk_prcc_kclk_disable,
	.is_enabled = clk_prcc_is_enabled,
पूर्ण;

अटल काष्ठा clk *clk_reg_prcc(स्थिर अक्षर *name,
				स्थिर अक्षर *parent_name,
				resource_माप_प्रकार phy_base,
				u32 cg_sel,
				अचिन्हित दीर्घ flags,
				स्थिर काष्ठा clk_ops *clk_prcc_ops)
अणु
	काष्ठा clk_prcc *clk;
	काष्ठा clk_init_data clk_prcc_init;
	काष्ठा clk *clk_reg;

	अगर (!name) अणु
		pr_err("clk_prcc: %s invalid arguments passed\n", __func__);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	clk = kzalloc(माप(*clk), GFP_KERNEL);
	अगर (!clk)
		वापस ERR_PTR(-ENOMEM);

	clk->base = ioremap(phy_base, SZ_4K);
	अगर (!clk->base)
		जाओ मुक्त_clk;

	clk->cg_sel = cg_sel;
	clk->is_enabled = 1;

	clk_prcc_init.name = name;
	clk_prcc_init.ops = clk_prcc_ops;
	clk_prcc_init.flags = flags;
	clk_prcc_init.parent_names = (parent_name ? &parent_name : शून्य);
	clk_prcc_init.num_parents = (parent_name ? 1 : 0);
	clk->hw.init = &clk_prcc_init;

	clk_reg = clk_रेजिस्टर(शून्य, &clk->hw);
	अगर (IS_ERR_OR_शून्य(clk_reg))
		जाओ unmap_clk;

	वापस clk_reg;

unmap_clk:
	iounmap(clk->base);
मुक्त_clk:
	kमुक्त(clk);
	pr_err("clk_prcc: %s failed to register clk\n", __func__);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

काष्ठा clk *clk_reg_prcc_pclk(स्थिर अक्षर *name,
			      स्थिर अक्षर *parent_name,
			      resource_माप_प्रकार phy_base,
			      u32 cg_sel,
			      अचिन्हित दीर्घ flags)
अणु
	वापस clk_reg_prcc(name, parent_name, phy_base, cg_sel, flags,
			&clk_prcc_pclk_ops);
पूर्ण

काष्ठा clk *clk_reg_prcc_kclk(स्थिर अक्षर *name,
			      स्थिर अक्षर *parent_name,
			      resource_माप_प्रकार phy_base,
			      u32 cg_sel,
			      अचिन्हित दीर्घ flags)
अणु
	वापस clk_reg_prcc(name, parent_name, phy_base, cg_sel, flags,
			&clk_prcc_kclk_ops);
पूर्ण
