<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 Fuzhou Rockchip Electronics Co., Ltd
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश "clk.h"

#घोषणा भाग_mask(width)	((1 << (width)) - 1)

अटल bool _is_best_half_भाग(अचिन्हित दीर्घ rate, अचिन्हित दीर्घ now,
			      अचिन्हित दीर्घ best, अचिन्हित दीर्घ flags)
अणु
	अगर (flags & CLK_DIVIDER_ROUND_CLOSEST)
		वापस असल(rate - now) < असल(rate - best);

	वापस now <= rate && now > best;
पूर्ण

अटल अचिन्हित दीर्घ clk_half_भागider_recalc_rate(काष्ठा clk_hw *hw,
						  अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_भागider *भागider = to_clk_भागider(hw);
	अचिन्हित पूर्णांक val;

	val = पढ़ोl(भागider->reg) >> भागider->shअगरt;
	val &= भाग_mask(भागider->width);
	val = val * 2 + 3;

	वापस DIV_ROUND_UP_ULL(((u64)parent_rate * 2), val);
पूर्ण

अटल पूर्णांक clk_half_भागider_bestभाग(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				    अचिन्हित दीर्घ *best_parent_rate, u8 width,
				    अचिन्हित दीर्घ flags)
अणु
	अचिन्हित पूर्णांक i, bestभाग = 0;
	अचिन्हित दीर्घ parent_rate, best = 0, now, maxभाग;
	अचिन्हित दीर्घ parent_rate_saved = *best_parent_rate;

	अगर (!rate)
		rate = 1;

	maxभाग = भाग_mask(width);

	अगर (!(clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT)) अणु
		parent_rate = *best_parent_rate;
		bestभाग = DIV_ROUND_UP_ULL(((u64)parent_rate * 2), rate);
		अगर (bestभाग < 3)
			bestभाग = 0;
		अन्यथा
			bestभाग = (bestभाग - 3) / 2;
		bestभाग = bestभाग > maxभाग ? maxभाग : bestभाग;
		वापस bestभाग;
	पूर्ण

	/*
	 * The maximum भागider we can use without overflowing
	 * अचिन्हित दीर्घ in rate * i below
	 */
	maxभाग = min(अच_दीर्घ_उच्च / rate, maxभाग);

	क्रम (i = 0; i <= maxभाग; i++) अणु
		अगर (((u64)rate * (i * 2 + 3)) == ((u64)parent_rate_saved * 2)) अणु
			/*
			 * It's the most ideal हाल अगर the requested rate can be
			 * भागided from parent घड़ी without needing to change
			 * parent rate, so वापस the भागider immediately.
			 */
			*best_parent_rate = parent_rate_saved;
			वापस i;
		पूर्ण
		parent_rate = clk_hw_round_rate(clk_hw_get_parent(hw),
						((u64)rate * (i * 2 + 3)) / 2);
		now = DIV_ROUND_UP_ULL(((u64)parent_rate * 2),
				       (i * 2 + 3));

		अगर (_is_best_half_भाग(rate, now, best, flags)) अणु
			bestभाग = i;
			best = now;
			*best_parent_rate = parent_rate;
		पूर्ण
	पूर्ण

	अगर (!bestभाग) अणु
		bestभाग = भाग_mask(width);
		*best_parent_rate = clk_hw_round_rate(clk_hw_get_parent(hw), 1);
	पूर्ण

	वापस bestभाग;
पूर्ण

अटल दीर्घ clk_half_भागider_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
					अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_भागider *भागider = to_clk_भागider(hw);
	पूर्णांक भाग;

	भाग = clk_half_भागider_bestभाग(hw, rate, prate,
				       भागider->width,
				       भागider->flags);

	वापस DIV_ROUND_UP_ULL(((u64)*prate * 2), भाग * 2 + 3);
पूर्ण

अटल पूर्णांक clk_half_भागider_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				     अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_भागider *भागider = to_clk_भागider(hw);
	अचिन्हित पूर्णांक value;
	अचिन्हित दीर्घ flags = 0;
	u32 val;

	value = DIV_ROUND_UP_ULL(((u64)parent_rate * 2), rate);
	value = (value - 3) / 2;
	value =  min_t(अचिन्हित पूर्णांक, value, भाग_mask(भागider->width));

	अगर (भागider->lock)
		spin_lock_irqsave(भागider->lock, flags);
	अन्यथा
		__acquire(भागider->lock);

	अगर (भागider->flags & CLK_DIVIDER_HIWORD_MASK) अणु
		val = भाग_mask(भागider->width) << (भागider->shअगरt + 16);
	पूर्ण अन्यथा अणु
		val = पढ़ोl(भागider->reg);
		val &= ~(भाग_mask(भागider->width) << भागider->shअगरt);
	पूर्ण
	val |= value << भागider->shअगरt;
	ग_लिखोl(val, भागider->reg);

	अगर (भागider->lock)
		spin_unlock_irqrestore(भागider->lock, flags);
	अन्यथा
		__release(भागider->lock);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_half_भागider_ops = अणु
	.recalc_rate = clk_half_भागider_recalc_rate,
	.round_rate = clk_half_भागider_round_rate,
	.set_rate = clk_half_भागider_set_rate,
पूर्ण;

/*
 * Register a घड़ी branch.
 * Most घड़ी branches have a क्रमm like
 *
 * src1 --|--\
 *        |M |--[GATE]-[DIV]-
 * src2 --|--/
 *
 * someबार without one of those components.
 */
काष्ठा clk *rockchip_clk_रेजिस्टर_halfभाग(स्थिर अक्षर *name,
					  स्थिर अक्षर *स्थिर *parent_names,
					  u8 num_parents, व्योम __iomem *base,
					  पूर्णांक muxभाग_offset, u8 mux_shअगरt,
					  u8 mux_width, u8 mux_flags,
					  u8 भाग_shअगरt, u8 भाग_width,
					  u8 भाग_flags, पूर्णांक gate_offset,
					  u8 gate_shअगरt, u8 gate_flags,
					  अचिन्हित दीर्घ flags,
					  spinlock_t *lock)
अणु
	काष्ठा clk_hw *hw = ERR_PTR(-ENOMEM);
	काष्ठा clk_mux *mux = शून्य;
	काष्ठा clk_gate *gate = शून्य;
	काष्ठा clk_भागider *भाग = शून्य;
	स्थिर काष्ठा clk_ops *mux_ops = शून्य, *भाग_ops = शून्य,
			     *gate_ops = शून्य;

	अगर (num_parents > 1) अणु
		mux = kzalloc(माप(*mux), GFP_KERNEL);
		अगर (!mux)
			वापस ERR_PTR(-ENOMEM);

		mux->reg = base + muxभाग_offset;
		mux->shअगरt = mux_shअगरt;
		mux->mask = BIT(mux_width) - 1;
		mux->flags = mux_flags;
		mux->lock = lock;
		mux_ops = (mux_flags & CLK_MUX_READ_ONLY) ? &clk_mux_ro_ops
							: &clk_mux_ops;
	पूर्ण

	अगर (gate_offset >= 0) अणु
		gate = kzalloc(माप(*gate), GFP_KERNEL);
		अगर (!gate)
			जाओ err_gate;

		gate->flags = gate_flags;
		gate->reg = base + gate_offset;
		gate->bit_idx = gate_shअगरt;
		gate->lock = lock;
		gate_ops = &clk_gate_ops;
	पूर्ण

	अगर (भाग_width > 0) अणु
		भाग = kzalloc(माप(*भाग), GFP_KERNEL);
		अगर (!भाग)
			जाओ err_भाग;

		भाग->flags = भाग_flags;
		भाग->reg = base + muxभाग_offset;
		भाग->shअगरt = भाग_shअगरt;
		भाग->width = भाग_width;
		भाग->lock = lock;
		भाग_ops = &clk_half_भागider_ops;
	पूर्ण

	hw = clk_hw_रेजिस्टर_composite(शून्य, name, parent_names, num_parents,
				       mux ? &mux->hw : शून्य, mux_ops,
				       भाग ? &भाग->hw : शून्य, भाग_ops,
				       gate ? &gate->hw : शून्य, gate_ops,
				       flags);
	अगर (IS_ERR(hw))
		जाओ err_भाग;

	वापस hw->clk;
err_भाग:
	kमुक्त(gate);
err_gate:
	kमुक्त(mux);
	वापस ERR_CAST(hw);
पूर्ण
