<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2020 Intel Corporation.
 * Zhu YiXin <yixin.zhu@पूर्णांकel.com>
 * Rahul Tanwar <rahul.tanwar@पूर्णांकel.com>
 */
#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/of.h>

#समावेश "clk-cgu.h"

#घोषणा GATE_HW_REG_STAT(reg)	((reg) + 0x0)
#घोषणा GATE_HW_REG_EN(reg)	((reg) + 0x4)
#घोषणा GATE_HW_REG_DIS(reg)	((reg) + 0x8)
#घोषणा MAX_DDIV_REG	8
#घोषणा MAX_DIVIDER_VAL 64

#घोषणा to_lgm_clk_mux(_hw) container_of(_hw, काष्ठा lgm_clk_mux, hw)
#घोषणा to_lgm_clk_भागider(_hw) container_of(_hw, काष्ठा lgm_clk_भागider, hw)
#घोषणा to_lgm_clk_gate(_hw) container_of(_hw, काष्ठा lgm_clk_gate, hw)
#घोषणा to_lgm_clk_dभाग(_hw) container_of(_hw, काष्ठा lgm_clk_dभाग, hw)

अटल काष्ठा clk_hw *lgm_clk_रेजिस्टर_fixed(काष्ठा lgm_clk_provider *ctx,
					     स्थिर काष्ठा lgm_clk_branch *list)
अणु
	अचिन्हित दीर्घ flags;

	अगर (list->भाग_flags & CLOCK_FLAG_VAL_INIT) अणु
		spin_lock_irqsave(&ctx->lock, flags);
		lgm_set_clk_val(ctx->membase, list->भाग_off, list->भाग_shअगरt,
				list->भाग_width, list->भाग_val);
		spin_unlock_irqrestore(&ctx->lock, flags);
	पूर्ण

	वापस clk_hw_रेजिस्टर_fixed_rate(शून्य, list->name,
					  list->parent_data[0].name,
					  list->flags, list->mux_flags);
पूर्ण

अटल u8 lgm_clk_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा lgm_clk_mux *mux = to_lgm_clk_mux(hw);
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&mux->lock, flags);
	अगर (mux->flags & MUX_CLK_SW)
		val = mux->reg;
	अन्यथा
		val = lgm_get_clk_val(mux->membase, mux->reg, mux->shअगरt,
				      mux->width);
	spin_unlock_irqrestore(&mux->lock, flags);
	वापस clk_mux_val_to_index(hw, शून्य, mux->flags, val);
पूर्ण

अटल पूर्णांक lgm_clk_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा lgm_clk_mux *mux = to_lgm_clk_mux(hw);
	अचिन्हित दीर्घ flags;
	u32 val;

	val = clk_mux_index_to_val(शून्य, mux->flags, index);
	spin_lock_irqsave(&mux->lock, flags);
	अगर (mux->flags & MUX_CLK_SW)
		mux->reg = val;
	अन्यथा
		lgm_set_clk_val(mux->membase, mux->reg, mux->shअगरt,
				mux->width, val);
	spin_unlock_irqrestore(&mux->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक lgm_clk_mux_determine_rate(काष्ठा clk_hw *hw,
				      काष्ठा clk_rate_request *req)
अणु
	काष्ठा lgm_clk_mux *mux = to_lgm_clk_mux(hw);

	वापस clk_mux_determine_rate_flags(hw, req, mux->flags);
पूर्ण

अटल स्थिर काष्ठा clk_ops lgm_clk_mux_ops = अणु
	.get_parent = lgm_clk_mux_get_parent,
	.set_parent = lgm_clk_mux_set_parent,
	.determine_rate = lgm_clk_mux_determine_rate,
पूर्ण;

अटल काष्ठा clk_hw *
lgm_clk_रेजिस्टर_mux(काष्ठा lgm_clk_provider *ctx,
		     स्थिर काष्ठा lgm_clk_branch *list)
अणु
	अचिन्हित दीर्घ flags, cflags = list->mux_flags;
	काष्ठा device *dev = ctx->dev;
	u8 shअगरt = list->mux_shअगरt;
	u8 width = list->mux_width;
	काष्ठा clk_init_data init = अणुपूर्ण;
	काष्ठा lgm_clk_mux *mux;
	u32 reg = list->mux_off;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	mux = devm_kzalloc(dev, माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस ERR_PTR(-ENOMEM);

	init.name = list->name;
	init.ops = &lgm_clk_mux_ops;
	init.flags = list->flags;
	init.parent_data = list->parent_data;
	init.num_parents = list->num_parents;

	mux->membase = ctx->membase;
	mux->lock = ctx->lock;
	mux->reg = reg;
	mux->shअगरt = shअगरt;
	mux->width = width;
	mux->flags = cflags;
	mux->hw.init = &init;

	hw = &mux->hw;
	ret = devm_clk_hw_रेजिस्टर(dev, hw);
	अगर (ret)
		वापस ERR_PTR(ret);

	अगर (cflags & CLOCK_FLAG_VAL_INIT) अणु
		spin_lock_irqsave(&mux->lock, flags);
		lgm_set_clk_val(mux->membase, reg, shअगरt, width, list->mux_val);
		spin_unlock_irqrestore(&mux->lock, flags);
	पूर्ण

	वापस hw;
पूर्ण

अटल अचिन्हित दीर्घ
lgm_clk_भागider_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा lgm_clk_भागider *भागider = to_lgm_clk_भागider(hw);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक val;

	spin_lock_irqsave(&भागider->lock, flags);
	val = lgm_get_clk_val(भागider->membase, भागider->reg,
			      भागider->shअगरt, भागider->width);
	spin_unlock_irqrestore(&भागider->lock, flags);

	वापस भागider_recalc_rate(hw, parent_rate, val, भागider->table,
				   भागider->flags, भागider->width);
पूर्ण

अटल दीर्घ
lgm_clk_भागider_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			   अचिन्हित दीर्घ *prate)
अणु
	काष्ठा lgm_clk_भागider *भागider = to_lgm_clk_भागider(hw);

	वापस भागider_round_rate(hw, rate, prate, भागider->table,
				  भागider->width, भागider->flags);
पूर्ण

अटल पूर्णांक
lgm_clk_भागider_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			 अचिन्हित दीर्घ prate)
अणु
	काष्ठा lgm_clk_भागider *भागider = to_lgm_clk_भागider(hw);
	अचिन्हित दीर्घ flags;
	पूर्णांक value;

	value = भागider_get_val(rate, prate, भागider->table,
				भागider->width, भागider->flags);
	अगर (value < 0)
		वापस value;

	spin_lock_irqsave(&भागider->lock, flags);
	lgm_set_clk_val(भागider->membase, भागider->reg,
			भागider->shअगरt, भागider->width, value);
	spin_unlock_irqrestore(&भागider->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक lgm_clk_भागider_enable_disable(काष्ठा clk_hw *hw, पूर्णांक enable)
अणु
	काष्ठा lgm_clk_भागider *भाग = to_lgm_clk_भागider(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&भाग->lock, flags);
	lgm_set_clk_val(भाग->membase, भाग->reg, भाग->shअगरt_gate,
			भाग->width_gate, enable);
	spin_unlock_irqrestore(&भाग->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक lgm_clk_भागider_enable(काष्ठा clk_hw *hw)
अणु
	वापस lgm_clk_भागider_enable_disable(hw, 1);
पूर्ण

अटल व्योम lgm_clk_भागider_disable(काष्ठा clk_hw *hw)
अणु
	lgm_clk_भागider_enable_disable(hw, 0);
पूर्ण

अटल स्थिर काष्ठा clk_ops lgm_clk_भागider_ops = अणु
	.recalc_rate = lgm_clk_भागider_recalc_rate,
	.round_rate = lgm_clk_भागider_round_rate,
	.set_rate = lgm_clk_भागider_set_rate,
	.enable = lgm_clk_भागider_enable,
	.disable = lgm_clk_भागider_disable,
पूर्ण;

अटल काष्ठा clk_hw *
lgm_clk_रेजिस्टर_भागider(काष्ठा lgm_clk_provider *ctx,
			 स्थिर काष्ठा lgm_clk_branch *list)
अणु
	अचिन्हित दीर्घ flags, cflags = list->भाग_flags;
	काष्ठा device *dev = ctx->dev;
	काष्ठा lgm_clk_भागider *भाग;
	काष्ठा clk_init_data init = अणुपूर्ण;
	u8 shअगरt = list->भाग_shअगरt;
	u8 width = list->भाग_width;
	u8 shअगरt_gate = list->भाग_shअगरt_gate;
	u8 width_gate = list->भाग_width_gate;
	u32 reg = list->भाग_off;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	भाग = devm_kzalloc(dev, माप(*भाग), GFP_KERNEL);
	अगर (!भाग)
		वापस ERR_PTR(-ENOMEM);

	init.name = list->name;
	init.ops = &lgm_clk_भागider_ops;
	init.flags = list->flags;
	init.parent_data = list->parent_data;
	init.num_parents = 1;

	भाग->membase = ctx->membase;
	भाग->lock = ctx->lock;
	भाग->reg = reg;
	भाग->shअगरt = shअगरt;
	भाग->width = width;
	भाग->shअगरt_gate	= shअगरt_gate;
	भाग->width_gate	= width_gate;
	भाग->flags = cflags;
	भाग->table = list->भाग_प्रकारable;
	भाग->hw.init = &init;

	hw = &भाग->hw;
	ret = devm_clk_hw_रेजिस्टर(dev, hw);
	अगर (ret)
		वापस ERR_PTR(ret);

	अगर (cflags & CLOCK_FLAG_VAL_INIT) अणु
		spin_lock_irqsave(&भाग->lock, flags);
		lgm_set_clk_val(भाग->membase, reg, shअगरt, width, list->भाग_val);
		spin_unlock_irqrestore(&भाग->lock, flags);
	पूर्ण

	वापस hw;
पूर्ण

अटल काष्ठा clk_hw *
lgm_clk_रेजिस्टर_fixed_factor(काष्ठा lgm_clk_provider *ctx,
			      स्थिर काष्ठा lgm_clk_branch *list)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा clk_hw *hw;

	hw = clk_hw_रेजिस्टर_fixed_factor(ctx->dev, list->name,
					  list->parent_data[0].name, list->flags,
					  list->mult, list->भाग);
	अगर (IS_ERR(hw))
		वापस ERR_CAST(hw);

	अगर (list->भाग_flags & CLOCK_FLAG_VAL_INIT) अणु
		spin_lock_irqsave(&ctx->lock, flags);
		lgm_set_clk_val(ctx->membase, list->भाग_off, list->भाग_shअगरt,
				list->भाग_width, list->भाग_val);
		spin_unlock_irqrestore(&ctx->lock, flags);
	पूर्ण

	वापस hw;
पूर्ण

अटल पूर्णांक lgm_clk_gate_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा lgm_clk_gate *gate = to_lgm_clk_gate(hw);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक reg;

	spin_lock_irqsave(&gate->lock, flags);
	reg = GATE_HW_REG_EN(gate->reg);
	lgm_set_clk_val(gate->membase, reg, gate->shअगरt, 1, 1);
	spin_unlock_irqrestore(&gate->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम lgm_clk_gate_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा lgm_clk_gate *gate = to_lgm_clk_gate(hw);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक reg;

	spin_lock_irqsave(&gate->lock, flags);
	reg = GATE_HW_REG_DIS(gate->reg);
	lgm_set_clk_val(gate->membase, reg, gate->shअगरt, 1, 1);
	spin_unlock_irqrestore(&gate->lock, flags);
पूर्ण

अटल पूर्णांक lgm_clk_gate_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा lgm_clk_gate *gate = to_lgm_clk_gate(hw);
	अचिन्हित पूर्णांक reg, ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gate->lock, flags);
	reg = GATE_HW_REG_STAT(gate->reg);
	ret = lgm_get_clk_val(gate->membase, reg, gate->shअगरt, 1);
	spin_unlock_irqrestore(&gate->lock, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा clk_ops lgm_clk_gate_ops = अणु
	.enable = lgm_clk_gate_enable,
	.disable = lgm_clk_gate_disable,
	.is_enabled = lgm_clk_gate_is_enabled,
पूर्ण;

अटल काष्ठा clk_hw *
lgm_clk_रेजिस्टर_gate(काष्ठा lgm_clk_provider *ctx,
		      स्थिर काष्ठा lgm_clk_branch *list)
अणु
	अचिन्हित दीर्घ flags, cflags = list->gate_flags;
	स्थिर अक्षर *pname = list->parent_data[0].name;
	काष्ठा device *dev = ctx->dev;
	u8 shअगरt = list->gate_shअगरt;
	काष्ठा clk_init_data init = अणुपूर्ण;
	काष्ठा lgm_clk_gate *gate;
	u32 reg = list->gate_off;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	gate = devm_kzalloc(dev, माप(*gate), GFP_KERNEL);
	अगर (!gate)
		वापस ERR_PTR(-ENOMEM);

	init.name = list->name;
	init.ops = &lgm_clk_gate_ops;
	init.flags = list->flags;
	init.parent_names = pname ? &pname : शून्य;
	init.num_parents = pname ? 1 : 0;

	gate->membase = ctx->membase;
	gate->lock = ctx->lock;
	gate->reg = reg;
	gate->shअगरt = shअगरt;
	gate->flags = cflags;
	gate->hw.init = &init;

	hw = &gate->hw;
	ret = devm_clk_hw_रेजिस्टर(dev, hw);
	अगर (ret)
		वापस ERR_PTR(ret);

	अगर (cflags & CLOCK_FLAG_VAL_INIT) अणु
		spin_lock_irqsave(&gate->lock, flags);
		lgm_set_clk_val(gate->membase, reg, shअगरt, 1, list->gate_val);
		spin_unlock_irqrestore(&gate->lock, flags);
	पूर्ण

	वापस hw;
पूर्ण

पूर्णांक lgm_clk_रेजिस्टर_branches(काष्ठा lgm_clk_provider *ctx,
			      स्थिर काष्ठा lgm_clk_branch *list,
			      अचिन्हित पूर्णांक nr_clk)
अणु
	काष्ठा clk_hw *hw;
	अचिन्हित पूर्णांक idx;

	क्रम (idx = 0; idx < nr_clk; idx++, list++) अणु
		चयन (list->type) अणु
		हाल CLK_TYPE_FIXED:
			hw = lgm_clk_रेजिस्टर_fixed(ctx, list);
			अवरोध;
		हाल CLK_TYPE_MUX:
			hw = lgm_clk_रेजिस्टर_mux(ctx, list);
			अवरोध;
		हाल CLK_TYPE_DIVIDER:
			hw = lgm_clk_रेजिस्टर_भागider(ctx, list);
			अवरोध;
		हाल CLK_TYPE_FIXED_FACTOR:
			hw = lgm_clk_रेजिस्टर_fixed_factor(ctx, list);
			अवरोध;
		हाल CLK_TYPE_GATE:
			hw = lgm_clk_रेजिस्टर_gate(ctx, list);
			अवरोध;
		शेष:
			dev_err(ctx->dev, "invalid clk type\n");
			वापस -EINVAL;
		पूर्ण

		अगर (IS_ERR(hw)) अणु
			dev_err(ctx->dev,
				"register clk: %s, type: %u failed!\n",
				list->name, list->type);
			वापस -EIO;
		पूर्ण
		ctx->clk_data.hws[list->id] = hw;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ
lgm_clk_dभाग_recalc_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा lgm_clk_dभाग *dभाग = to_lgm_clk_dभाग(hw);
	अचिन्हित पूर्णांक भाग0, भाग1, exभाग;
	u64 prate;

	भाग0 = lgm_get_clk_val(dभाग->membase, dभाग->reg,
			       dभाग->shअगरt0, dभाग->width0) + 1;
	भाग1 = lgm_get_clk_val(dभाग->membase, dभाग->reg,
			       dभाग->shअगरt1, dभाग->width1) + 1;
	exभाग = lgm_get_clk_val(dभाग->membase, dभाग->reg,
				dभाग->shअगरt2, dभाग->width2);
	prate = (u64)parent_rate;
	करो_भाग(prate, भाग0);
	करो_भाग(prate, भाग1);

	अगर (exभाग) अणु
		करो_भाग(prate, dभाग->भाग);
		prate *= dभाग->mult;
	पूर्ण

	वापस prate;
पूर्ण

अटल पूर्णांक lgm_clk_dभाग_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा lgm_clk_dभाग *dभाग = to_lgm_clk_dभाग(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dभाग->lock, flags);
	lgm_set_clk_val(dभाग->membase, dभाग->reg, dभाग->shअगरt_gate,
			dभाग->width_gate, 1);
	spin_unlock_irqrestore(&dभाग->lock, flags);
	वापस 0;
पूर्ण

अटल व्योम lgm_clk_dभाग_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा lgm_clk_dभाग *dभाग = to_lgm_clk_dभाग(hw);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dभाग->lock, flags);
	lgm_set_clk_val(dभाग->membase, dभाग->reg, dभाग->shअगरt_gate,
			dभाग->width_gate, 0);
	spin_unlock_irqrestore(&dभाग->lock, flags);
पूर्ण

अटल पूर्णांक
lgm_clk_get_dभाग_val(u32 भाग, u32 *dभाग1, u32 *dभाग2)
अणु
	u32 idx, temp;

	*dभाग1 = 1;
	*dभाग2 = 1;

	अगर (भाग > MAX_DIVIDER_VAL)
		भाग = MAX_DIVIDER_VAL;

	अगर (भाग > 1) अणु
		क्रम (idx = 2; idx <= MAX_DDIV_REG; idx++) अणु
			temp = DIV_ROUND_UP_ULL((u64)भाग, idx);
			अगर (भाग % idx == 0 && temp <= MAX_DDIV_REG)
				अवरोध;
		पूर्ण

		अगर (idx > MAX_DDIV_REG)
			वापस -EINVAL;

		*dभाग1 = temp;
		*dभाग2 = idx;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
lgm_clk_dभाग_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
		      अचिन्हित दीर्घ prate)
अणु
	काष्ठा lgm_clk_dभाग *dभाग = to_lgm_clk_dभाग(hw);
	u32 भाग, dभाग1, dभाग2;
	अचिन्हित दीर्घ flags;

	भाग = DIV_ROUND_CLOSEST_ULL((u64)prate, rate);

	spin_lock_irqsave(&dभाग->lock, flags);
	अगर (lgm_get_clk_val(dभाग->membase, dभाग->reg, dभाग->shअगरt2, 1)) अणु
		भाग = DIV_ROUND_CLOSEST_ULL((u64)भाग, 5);
		भाग = भाग * 2;
	पूर्ण

	अगर (भाग <= 0) अणु
		spin_unlock_irqrestore(&dभाग->lock, flags);
		वापस -EINVAL;
	पूर्ण

	अगर (lgm_clk_get_dभाग_val(भाग, &dभाग1, &dभाग2)) अणु
		spin_unlock_irqrestore(&dभाग->lock, flags);
		वापस -EINVAL;
	पूर्ण

	lgm_set_clk_val(dभाग->membase, dभाग->reg, dभाग->shअगरt0, dभाग->width0,
			dभाग1 - 1);

	lgm_set_clk_val(dभाग->membase, dभाग->reg,  dभाग->shअगरt1, dभाग->width1,
			dभाग2 - 1);
	spin_unlock_irqrestore(&dभाग->lock, flags);

	वापस 0;
पूर्ण

अटल दीर्घ
lgm_clk_dभाग_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			अचिन्हित दीर्घ *prate)
अणु
	काष्ठा lgm_clk_dभाग *dभाग = to_lgm_clk_dभाग(hw);
	u32 भाग, dभाग1, dभाग2;
	अचिन्हित दीर्घ flags;
	u64 rate64;

	भाग = DIV_ROUND_CLOSEST_ULL((u64)*prate, rate);

	/* अगर preभागide bit is enabled, modअगरy भाग by factor of 2.5 */
	spin_lock_irqsave(&dभाग->lock, flags);
	अगर (lgm_get_clk_val(dभाग->membase, dभाग->reg, dभाग->shअगरt2, 1)) अणु
		भाग = भाग * 2;
		भाग = DIV_ROUND_CLOSEST_ULL((u64)भाग, 5);
	पूर्ण
	spin_unlock_irqrestore(&dभाग->lock, flags);

	अगर (भाग <= 0)
		वापस *prate;

	अगर (lgm_clk_get_dभाग_val(भाग, &dभाग1, &dभाग2) != 0)
		अगर (lgm_clk_get_dभाग_val(भाग + 1, &dभाग1, &dभाग2) != 0)
			वापस -EINVAL;

	rate64 = *prate;
	करो_भाग(rate64, dभाग1);
	करो_भाग(rate64, dभाग2);

	/* अगर preभागide bit is enabled, modअगरy rounded rate by factor of 2.5 */
	spin_lock_irqsave(&dभाग->lock, flags);
	अगर (lgm_get_clk_val(dभाग->membase, dभाग->reg, dभाग->shअगरt2, 1)) अणु
		rate64 = rate64 * 2;
		rate64 = DIV_ROUND_CLOSEST_ULL(rate64, 5);
	पूर्ण
	spin_unlock_irqrestore(&dभाग->lock, flags);

	वापस rate64;
पूर्ण

अटल स्थिर काष्ठा clk_ops lgm_clk_dभाग_ops = अणु
	.recalc_rate = lgm_clk_dभाग_recalc_rate,
	.enable	= lgm_clk_dभाग_enable,
	.disable = lgm_clk_dभाग_disable,
	.set_rate = lgm_clk_dभाग_set_rate,
	.round_rate = lgm_clk_dभाग_round_rate,
पूर्ण;

पूर्णांक lgm_clk_रेजिस्टर_dभाग(काष्ठा lgm_clk_provider *ctx,
			  स्थिर काष्ठा lgm_clk_dभाग_data *list,
			  अचिन्हित पूर्णांक nr_clk)
अणु
	काष्ठा device *dev = ctx->dev;
	काष्ठा clk_hw *hw;
	अचिन्हित पूर्णांक idx;
	पूर्णांक ret;

	क्रम (idx = 0; idx < nr_clk; idx++, list++) अणु
		काष्ठा clk_init_data init = अणुपूर्ण;
		काष्ठा lgm_clk_dभाग *dभाग;

		dभाग = devm_kzalloc(dev, माप(*dभाग), GFP_KERNEL);
		अगर (!dभाग)
			वापस -ENOMEM;

		init.name = list->name;
		init.ops = &lgm_clk_dभाग_ops;
		init.flags = list->flags;
		init.parent_data = list->parent_data;
		init.num_parents = 1;

		dभाग->membase = ctx->membase;
		dभाग->lock = ctx->lock;
		dभाग->reg = list->reg;
		dभाग->shअगरt0 = list->shअगरt0;
		dभाग->width0 = list->width0;
		dभाग->shअगरt1 = list->shअगरt1;
		dभाग->width1 = list->width1;
		dभाग->shअगरt_gate = list->shअगरt_gate;
		dभाग->width_gate = list->width_gate;
		dभाग->shअगरt2 = list->ex_shअगरt;
		dभाग->width2 = list->ex_width;
		dभाग->flags = list->भाग_flags;
		dभाग->mult = 2;
		dभाग->भाग = 5;
		dभाग->hw.init = &init;

		hw = &dभाग->hw;
		ret = devm_clk_hw_रेजिस्टर(dev, hw);
		अगर (ret) अणु
			dev_err(dev, "register clk: %s failed!\n", list->name);
			वापस ret;
		पूर्ण
		ctx->clk_data.hws[list->id] = hw;
	पूर्ण

	वापस 0;
पूर्ण
