<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2018 NXP
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#समावेश "clk.h"

#घोषणा PCG_PREDIV_SHIFT	16
#घोषणा PCG_PREDIV_WIDTH	3
#घोषणा PCG_PREDIV_MAX		8

#घोषणा PCG_DIV_SHIFT		0
#घोषणा PCG_CORE_DIV_WIDTH	3
#घोषणा PCG_DIV_WIDTH		6
#घोषणा PCG_DIV_MAX		64

#घोषणा PCG_PCS_SHIFT		24
#घोषणा PCG_PCS_MASK		0x7

#घोषणा PCG_CGC_SHIFT		28

अटल अचिन्हित दीर्घ imx8m_clk_composite_भागider_recalc_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_भागider *भागider = to_clk_भागider(hw);
	अचिन्हित दीर्घ preभाग_rate;
	अचिन्हित पूर्णांक preभाग_value;
	अचिन्हित पूर्णांक भाग_value;

	preभाग_value = पढ़ोl(भागider->reg) >> भागider->shअगरt;
	preभाग_value &= clk_भाग_mask(भागider->width);

	preभाग_rate = भागider_recalc_rate(hw, parent_rate, preभाग_value,
						शून्य, भागider->flags,
						भागider->width);

	भाग_value = पढ़ोl(भागider->reg) >> PCG_DIV_SHIFT;
	भाग_value &= clk_भाग_mask(PCG_DIV_WIDTH);

	वापस भागider_recalc_rate(hw, preभाग_rate, भाग_value, शून्य,
				   भागider->flags, PCG_DIV_WIDTH);
पूर्ण

अटल पूर्णांक imx8m_clk_composite_compute_भागiders(अचिन्हित दीर्घ rate,
						अचिन्हित दीर्घ parent_rate,
						पूर्णांक *preभाग, पूर्णांक *postभाग)
अणु
	पूर्णांक भाग1, भाग2;
	पूर्णांक error = पूर्णांक_उच्च;
	पूर्णांक ret = -EINVAL;

	*preभाग = 1;
	*postभाग = 1;

	क्रम (भाग1 = 1; भाग1 <= PCG_PREDIV_MAX; भाग1++) अणु
		क्रम (भाग2 = 1; भाग2 <= PCG_DIV_MAX; भाग2++) अणु
			पूर्णांक new_error = ((parent_rate / भाग1) / भाग2) - rate;

			अगर (असल(new_error) < असल(error)) अणु
				*preभाग = भाग1;
				*postभाग = भाग2;
				error = new_error;
				ret = 0;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल दीर्घ imx8m_clk_composite_भागider_round_rate(काष्ठा clk_hw *hw,
						अचिन्हित दीर्घ rate,
						अचिन्हित दीर्घ *prate)
अणु
	पूर्णांक preभाग_value;
	पूर्णांक भाग_value;

	imx8m_clk_composite_compute_भागiders(rate, *prate,
						&preभाग_value, &भाग_value);
	rate = DIV_ROUND_UP(*prate, preभाग_value);

	वापस DIV_ROUND_UP(rate, भाग_value);

पूर्ण

अटल पूर्णांक imx8m_clk_composite_भागider_set_rate(काष्ठा clk_hw *hw,
					अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_भागider *भागider = to_clk_भागider(hw);
	अचिन्हित दीर्घ flags;
	पूर्णांक preभाग_value;
	पूर्णांक भाग_value;
	पूर्णांक ret;
	u32 val;

	ret = imx8m_clk_composite_compute_भागiders(rate, parent_rate,
						&preभाग_value, &भाग_value);
	अगर (ret)
		वापस -EINVAL;

	spin_lock_irqsave(भागider->lock, flags);

	val = पढ़ोl(भागider->reg);
	val &= ~((clk_भाग_mask(भागider->width) << भागider->shअगरt) |
			(clk_भाग_mask(PCG_DIV_WIDTH) << PCG_DIV_SHIFT));

	val |= (u32)(preभाग_value  - 1) << भागider->shअगरt;
	val |= (u32)(भाग_value - 1) << PCG_DIV_SHIFT;
	ग_लिखोl(val, भागider->reg);

	spin_unlock_irqrestore(भागider->lock, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops imx8m_clk_composite_भागider_ops = अणु
	.recalc_rate = imx8m_clk_composite_भागider_recalc_rate,
	.round_rate = imx8m_clk_composite_भागider_round_rate,
	.set_rate = imx8m_clk_composite_भागider_set_rate,
पूर्ण;

अटल u8 imx8m_clk_composite_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	वापस clk_mux_ops.get_parent(hw);
पूर्ण

अटल पूर्णांक imx8m_clk_composite_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_mux *mux = to_clk_mux(hw);
	u32 val = clk_mux_index_to_val(mux->table, mux->flags, index);
	अचिन्हित दीर्घ flags = 0;
	u32 reg;

	अगर (mux->lock)
		spin_lock_irqsave(mux->lock, flags);

	reg = पढ़ोl(mux->reg);
	reg &= ~(mux->mask << mux->shअगरt);
	val = val << mux->shअगरt;
	reg |= val;
	/*
	 * ग_लिखो twice to make sure non-target पूर्णांकerface
	 * SEL_A/B poपूर्णांक the same clk input.
	 */
	ग_लिखोl(reg, mux->reg);
	ग_लिखोl(reg, mux->reg);

	अगर (mux->lock)
		spin_unlock_irqrestore(mux->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
imx8m_clk_composite_mux_determine_rate(काष्ठा clk_hw *hw,
				       काष्ठा clk_rate_request *req)
अणु
	वापस clk_mux_ops.determine_rate(hw, req);
पूर्ण


अटल स्थिर काष्ठा clk_ops imx8m_clk_composite_mux_ops = अणु
	.get_parent = imx8m_clk_composite_mux_get_parent,
	.set_parent = imx8m_clk_composite_mux_set_parent,
	.determine_rate = imx8m_clk_composite_mux_determine_rate,
पूर्ण;

काष्ठा clk_hw *imx8m_clk_hw_composite_flags(स्थिर अक्षर *name,
					स्थिर अक्षर * स्थिर *parent_names,
					पूर्णांक num_parents, व्योम __iomem *reg,
					u32 composite_flags,
					अचिन्हित दीर्घ flags)
अणु
	काष्ठा clk_hw *hw = ERR_PTR(-ENOMEM), *mux_hw;
	काष्ठा clk_hw *भाग_hw, *gate_hw;
	काष्ठा clk_भागider *भाग = शून्य;
	काष्ठा clk_gate *gate = शून्य;
	काष्ठा clk_mux *mux = शून्य;
	स्थिर काष्ठा clk_ops *भागider_ops;
	स्थिर काष्ठा clk_ops *mux_ops;

	mux = kzalloc(माप(*mux), GFP_KERNEL);
	अगर (!mux)
		जाओ fail;

	mux_hw = &mux->hw;
	mux->reg = reg;
	mux->shअगरt = PCG_PCS_SHIFT;
	mux->mask = PCG_PCS_MASK;
	mux->lock = &imx_ccm_lock;

	भाग = kzalloc(माप(*भाग), GFP_KERNEL);
	अगर (!भाग)
		जाओ fail;

	भाग_hw = &भाग->hw;
	भाग->reg = reg;
	अगर (composite_flags & IMX_COMPOSITE_CORE) अणु
		भाग->shअगरt = PCG_DIV_SHIFT;
		भाग->width = PCG_CORE_DIV_WIDTH;
		भागider_ops = &clk_भागider_ops;
		mux_ops = &imx8m_clk_composite_mux_ops;
	पूर्ण अन्यथा अगर (composite_flags & IMX_COMPOSITE_BUS) अणु
		भाग->shअगरt = PCG_PREDIV_SHIFT;
		भाग->width = PCG_PREDIV_WIDTH;
		भागider_ops = &imx8m_clk_composite_भागider_ops;
		mux_ops = &imx8m_clk_composite_mux_ops;
	पूर्ण अन्यथा अणु
		भाग->shअगरt = PCG_PREDIV_SHIFT;
		भाग->width = PCG_PREDIV_WIDTH;
		भागider_ops = &imx8m_clk_composite_भागider_ops;
		mux_ops = &clk_mux_ops;
		flags |= CLK_SET_PARENT_GATE;
	पूर्ण

	भाग->lock = &imx_ccm_lock;
	भाग->flags = CLK_DIVIDER_ROUND_CLOSEST;

	gate = kzalloc(माप(*gate), GFP_KERNEL);
	अगर (!gate)
		जाओ fail;

	gate_hw = &gate->hw;
	gate->reg = reg;
	gate->bit_idx = PCG_CGC_SHIFT;
	gate->lock = &imx_ccm_lock;

	hw = clk_hw_रेजिस्टर_composite(शून्य, name, parent_names, num_parents,
			mux_hw, mux_ops, भाग_hw,
			भागider_ops, gate_hw, &clk_gate_ops, flags);
	अगर (IS_ERR(hw))
		जाओ fail;

	वापस hw;

fail:
	kमुक्त(gate);
	kमुक्त(भाग);
	kमुक्त(mux);
	वापस ERR_CAST(hw);
पूर्ण
EXPORT_SYMBOL_GPL(imx8m_clk_hw_composite_flags);
