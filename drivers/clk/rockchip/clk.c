<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2014 MunकरोReader S.L.
 * Author: Heiko Stuebner <heiko@sntech.de>
 *
 * Copyright (c) 2016 Rockchip Electronics Co. Ltd.
 * Author: Xing Zheng <zhengxing@rock-chips.com>
 *
 * based on
 *
 * samsung/clk.c
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 * Copyright (c) 2013 Linaro Ltd.
 * Author: Thomas Abraham <thomas.ab@samsung.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reboot.h>
#समावेश <linux/rational.h>
#समावेश "clk.h"

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
अटल काष्ठा clk *rockchip_clk_रेजिस्टर_branch(स्थिर अक्षर *name,
		स्थिर अक्षर *स्थिर *parent_names, u8 num_parents,
		व्योम __iomem *base,
		पूर्णांक muxभाग_offset, u8 mux_shअगरt, u8 mux_width, u8 mux_flags,
		पूर्णांक भाग_offset, u8 भाग_shअगरt, u8 भाग_width, u8 भाग_flags,
		काष्ठा clk_भाग_प्रकारable *भाग_प्रकारable, पूर्णांक gate_offset,
		u8 gate_shअगरt, u8 gate_flags, अचिन्हित दीर्घ flags,
		spinlock_t *lock)
अणु
	काष्ठा clk_hw *hw;
	काष्ठा clk_mux *mux = शून्य;
	काष्ठा clk_gate *gate = शून्य;
	काष्ठा clk_भागider *भाग = शून्य;
	स्थिर काष्ठा clk_ops *mux_ops = शून्य, *भाग_ops = शून्य,
			     *gate_ops = शून्य;
	पूर्णांक ret;

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
		अगर (!gate) अणु
			ret = -ENOMEM;
			जाओ err_gate;
		पूर्ण

		gate->flags = gate_flags;
		gate->reg = base + gate_offset;
		gate->bit_idx = gate_shअगरt;
		gate->lock = lock;
		gate_ops = &clk_gate_ops;
	पूर्ण

	अगर (भाग_width > 0) अणु
		भाग = kzalloc(माप(*भाग), GFP_KERNEL);
		अगर (!भाग) अणु
			ret = -ENOMEM;
			जाओ err_भाग;
		पूर्ण

		भाग->flags = भाग_flags;
		अगर (भाग_offset)
			भाग->reg = base + भाग_offset;
		अन्यथा
			भाग->reg = base + muxभाग_offset;
		भाग->shअगरt = भाग_shअगरt;
		भाग->width = भाग_width;
		भाग->lock = lock;
		भाग->table = भाग_प्रकारable;
		भाग_ops = (भाग_flags & CLK_DIVIDER_READ_ONLY)
						? &clk_भागider_ro_ops
						: &clk_भागider_ops;
	पूर्ण

	hw = clk_hw_रेजिस्टर_composite(शून्य, name, parent_names, num_parents,
				       mux ? &mux->hw : शून्य, mux_ops,
				       भाग ? &भाग->hw : शून्य, भाग_ops,
				       gate ? &gate->hw : शून्य, gate_ops,
				       flags);
	अगर (IS_ERR(hw)) अणु
		kमुक्त(भाग);
		kमुक्त(gate);
		वापस ERR_CAST(hw);
	पूर्ण

	वापस hw->clk;
err_भाग:
	kमुक्त(gate);
err_gate:
	kमुक्त(mux);
	वापस ERR_PTR(ret);
पूर्ण

काष्ठा rockchip_clk_frac अणु
	काष्ठा notअगरier_block			clk_nb;
	काष्ठा clk_fractional_भागider		भाग;
	काष्ठा clk_gate				gate;

	काष्ठा clk_mux				mux;
	स्थिर काष्ठा clk_ops			*mux_ops;
	पूर्णांक					mux_frac_idx;

	bool					rate_change_remuxed;
	पूर्णांक					rate_change_idx;
पूर्ण;

#घोषणा to_rockchip_clk_frac_nb(nb) \
			container_of(nb, काष्ठा rockchip_clk_frac, clk_nb)

अटल पूर्णांक rockchip_clk_frac_notअगरier_cb(काष्ठा notअगरier_block *nb,
					 अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा clk_notअगरier_data *ndata = data;
	काष्ठा rockchip_clk_frac *frac = to_rockchip_clk_frac_nb(nb);
	काष्ठा clk_mux *frac_mux = &frac->mux;
	पूर्णांक ret = 0;

	pr_debug("%s: event %lu, old_rate %lu, new_rate: %lu\n",
		 __func__, event, ndata->old_rate, ndata->new_rate);
	अगर (event == PRE_RATE_CHANGE) अणु
		frac->rate_change_idx =
				frac->mux_ops->get_parent(&frac_mux->hw);
		अगर (frac->rate_change_idx != frac->mux_frac_idx) अणु
			frac->mux_ops->set_parent(&frac_mux->hw,
						  frac->mux_frac_idx);
			frac->rate_change_remuxed = 1;
		पूर्ण
	पूर्ण अन्यथा अगर (event == POST_RATE_CHANGE) अणु
		/*
		 * The POST_RATE_CHANGE notअगरier runs directly after the
		 * भागider घड़ी is set in clk_change_rate, so we'll have
		 * remuxed back to the original parent beक्रमe clk_change_rate
		 * reaches the mux itself.
		 */
		अगर (frac->rate_change_remuxed) अणु
			frac->mux_ops->set_parent(&frac_mux->hw,
						  frac->rate_change_idx);
			frac->rate_change_remuxed = 0;
		पूर्ण
	पूर्ण

	वापस notअगरier_from_त्रुटि_सं(ret);
पूर्ण

/*
 * fractional भागider must set that denominator is 20 बार larger than
 * numerator to generate precise घड़ी frequency.
 */
अटल व्योम rockchip_fractional_approximation(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ rate, अचिन्हित दीर्घ *parent_rate,
		अचिन्हित दीर्घ *m, अचिन्हित दीर्घ *n)
अणु
	काष्ठा clk_fractional_भागider *fd = to_clk_fd(hw);
	अचिन्हित दीर्घ p_rate, p_parent_rate;
	काष्ठा clk_hw *p_parent;
	अचिन्हित दीर्घ scale;

	p_rate = clk_hw_get_rate(clk_hw_get_parent(hw));
	अगर ((rate * 20 > p_rate) && (p_rate % rate != 0)) अणु
		p_parent = clk_hw_get_parent(clk_hw_get_parent(hw));
		p_parent_rate = clk_hw_get_rate(p_parent);
		*parent_rate = p_parent_rate;
	पूर्ण

	/*
	 * Get rate बंदr to *parent_rate to guarantee there is no overflow
	 * क्रम m and n. In the result it will be the nearest rate left shअगरted
	 * by (scale - fd->nwidth) bits.
	 */
	scale = fls_दीर्घ(*parent_rate / rate - 1);
	अगर (scale > fd->nwidth)
		rate <<= scale - fd->nwidth;

	rational_best_approximation(rate, *parent_rate,
			GENMASK(fd->mwidth - 1, 0), GENMASK(fd->nwidth - 1, 0),
			m, n);
पूर्ण

अटल काष्ठा clk *rockchip_clk_रेजिस्टर_frac_branch(
		काष्ठा rockchip_clk_provider *ctx, स्थिर अक्षर *name,
		स्थिर अक्षर *स्थिर *parent_names, u8 num_parents,
		व्योम __iomem *base, पूर्णांक muxभाग_offset, u8 भाग_flags,
		पूर्णांक gate_offset, u8 gate_shअगरt, u8 gate_flags,
		अचिन्हित दीर्घ flags, काष्ठा rockchip_clk_branch *child,
		spinlock_t *lock)
अणु
	काष्ठा clk_hw *hw;
	काष्ठा rockchip_clk_frac *frac;
	काष्ठा clk_gate *gate = शून्य;
	काष्ठा clk_fractional_भागider *भाग = शून्य;
	स्थिर काष्ठा clk_ops *भाग_ops = शून्य, *gate_ops = शून्य;

	अगर (muxभाग_offset < 0)
		वापस ERR_PTR(-EINVAL);

	अगर (child && child->branch_type != branch_mux) अणु
		pr_err("%s: fractional child clock for %s can only be a mux\n",
		       __func__, name);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	frac = kzalloc(माप(*frac), GFP_KERNEL);
	अगर (!frac)
		वापस ERR_PTR(-ENOMEM);

	अगर (gate_offset >= 0) अणु
		gate = &frac->gate;
		gate->flags = gate_flags;
		gate->reg = base + gate_offset;
		gate->bit_idx = gate_shअगरt;
		gate->lock = lock;
		gate_ops = &clk_gate_ops;
	पूर्ण

	भाग = &frac->भाग;
	भाग->flags = भाग_flags;
	भाग->reg = base + muxभाग_offset;
	भाग->mshअगरt = 16;
	भाग->mwidth = 16;
	भाग->mmask = GENMASK(भाग->mwidth - 1, 0) << भाग->mshअगरt;
	भाग->nshअगरt = 0;
	भाग->nwidth = 16;
	भाग->nmask = GENMASK(भाग->nwidth - 1, 0) << भाग->nshअगरt;
	भाग->lock = lock;
	भाग->approximation = rockchip_fractional_approximation;
	भाग_ops = &clk_fractional_भागider_ops;

	hw = clk_hw_रेजिस्टर_composite(शून्य, name, parent_names, num_parents,
				       शून्य, शून्य,
				       &भाग->hw, भाग_ops,
				       gate ? &gate->hw : शून्य, gate_ops,
				       flags | CLK_SET_RATE_UNGATE);
	अगर (IS_ERR(hw)) अणु
		kमुक्त(frac);
		वापस ERR_CAST(hw);
	पूर्ण

	अगर (child) अणु
		काष्ठा clk_mux *frac_mux = &frac->mux;
		काष्ठा clk_init_data init;
		काष्ठा clk *mux_clk;
		पूर्णांक ret;

		frac->mux_frac_idx = match_string(child->parent_names,
						  child->num_parents, name);
		frac->mux_ops = &clk_mux_ops;
		frac->clk_nb.notअगरier_call = rockchip_clk_frac_notअगरier_cb;

		frac_mux->reg = base + child->muxभाग_offset;
		frac_mux->shअगरt = child->mux_shअगरt;
		frac_mux->mask = BIT(child->mux_width) - 1;
		frac_mux->flags = child->mux_flags;
		frac_mux->lock = lock;
		frac_mux->hw.init = &init;

		init.name = child->name;
		init.flags = child->flags | CLK_SET_RATE_PARENT;
		init.ops = frac->mux_ops;
		init.parent_names = child->parent_names;
		init.num_parents = child->num_parents;

		mux_clk = clk_रेजिस्टर(शून्य, &frac_mux->hw);
		अगर (IS_ERR(mux_clk)) अणु
			kमुक्त(frac);
			वापस mux_clk;
		पूर्ण

		rockchip_clk_add_lookup(ctx, mux_clk, child->id);

		/* notअगरier on the fraction भागider to catch rate changes */
		अगर (frac->mux_frac_idx >= 0) अणु
			pr_debug("%s: found fractional parent in mux at pos %d\n",
				 __func__, frac->mux_frac_idx);
			ret = clk_notअगरier_रेजिस्टर(hw->clk, &frac->clk_nb);
			अगर (ret)
				pr_err("%s: failed to register clock notifier for %s\n",
						__func__, name);
		पूर्ण अन्यथा अणु
			pr_warn("%s: could not find %s as parent of %s, rate changes may not work\n",
				__func__, name, child->name);
		पूर्ण
	पूर्ण

	वापस hw->clk;
पूर्ण

अटल काष्ठा clk *rockchip_clk_रेजिस्टर_factor_branch(स्थिर अक्षर *name,
		स्थिर अक्षर *स्थिर *parent_names, u8 num_parents,
		व्योम __iomem *base, अचिन्हित पूर्णांक mult, अचिन्हित पूर्णांक भाग,
		पूर्णांक gate_offset, u8 gate_shअगरt, u8 gate_flags,
		अचिन्हित दीर्घ flags, spinlock_t *lock)
अणु
	काष्ठा clk_hw *hw;
	काष्ठा clk_gate *gate = शून्य;
	काष्ठा clk_fixed_factor *fix = शून्य;

	/* without gate, रेजिस्टर a simple factor घड़ी */
	अगर (gate_offset == 0) अणु
		वापस clk_रेजिस्टर_fixed_factor(शून्य, name,
				parent_names[0], flags, mult,
				भाग);
	पूर्ण

	gate = kzalloc(माप(*gate), GFP_KERNEL);
	अगर (!gate)
		वापस ERR_PTR(-ENOMEM);

	gate->flags = gate_flags;
	gate->reg = base + gate_offset;
	gate->bit_idx = gate_shअगरt;
	gate->lock = lock;

	fix = kzalloc(माप(*fix), GFP_KERNEL);
	अगर (!fix) अणु
		kमुक्त(gate);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	fix->mult = mult;
	fix->भाग = भाग;

	hw = clk_hw_रेजिस्टर_composite(शून्य, name, parent_names, num_parents,
				       शून्य, शून्य,
				       &fix->hw, &clk_fixed_factor_ops,
				       &gate->hw, &clk_gate_ops, flags);
	अगर (IS_ERR(hw)) अणु
		kमुक्त(fix);
		kमुक्त(gate);
		वापस ERR_CAST(hw);
	पूर्ण

	वापस hw->clk;
पूर्ण

काष्ठा rockchip_clk_provider *rockchip_clk_init(काष्ठा device_node *np,
						व्योम __iomem *base,
						अचिन्हित दीर्घ nr_clks)
अणु
	काष्ठा rockchip_clk_provider *ctx;
	काष्ठा clk **clk_table;
	पूर्णांक i;

	ctx = kzalloc(माप(काष्ठा rockchip_clk_provider), GFP_KERNEL);
	अगर (!ctx)
		वापस ERR_PTR(-ENOMEM);

	clk_table = kसुस्मृति(nr_clks, माप(काष्ठा clk *), GFP_KERNEL);
	अगर (!clk_table)
		जाओ err_मुक्त;

	क्रम (i = 0; i < nr_clks; ++i)
		clk_table[i] = ERR_PTR(-ENOENT);

	ctx->reg_base = base;
	ctx->clk_data.clks = clk_table;
	ctx->clk_data.clk_num = nr_clks;
	ctx->cru_node = np;
	spin_lock_init(&ctx->lock);

	ctx->grf = syscon_regmap_lookup_by_phandle(ctx->cru_node,
						   "rockchip,grf");

	वापस ctx;

err_मुक्त:
	kमुक्त(ctx);
	वापस ERR_PTR(-ENOMEM);
पूर्ण
EXPORT_SYMBOL_GPL(rockchip_clk_init);

व्योम rockchip_clk_of_add_provider(काष्ठा device_node *np,
				  काष्ठा rockchip_clk_provider *ctx)
अणु
	अगर (of_clk_add_provider(np, of_clk_src_onecell_get,
				&ctx->clk_data))
		pr_err("%s: could not register clk provider\n", __func__);
पूर्ण
EXPORT_SYMBOL_GPL(rockchip_clk_of_add_provider);

व्योम rockchip_clk_add_lookup(काष्ठा rockchip_clk_provider *ctx,
			     काष्ठा clk *clk, अचिन्हित पूर्णांक id)
अणु
	अगर (ctx->clk_data.clks && id)
		ctx->clk_data.clks[id] = clk;
पूर्ण
EXPORT_SYMBOL_GPL(rockchip_clk_add_lookup);

व्योम rockchip_clk_रेजिस्टर_plls(काष्ठा rockchip_clk_provider *ctx,
				काष्ठा rockchip_pll_घड़ी *list,
				अचिन्हित पूर्णांक nr_pll, पूर्णांक grf_lock_offset)
अणु
	काष्ठा clk *clk;
	पूर्णांक idx;

	क्रम (idx = 0; idx < nr_pll; idx++, list++) अणु
		clk = rockchip_clk_रेजिस्टर_pll(ctx, list->type, list->name,
				list->parent_names, list->num_parents,
				list->con_offset, grf_lock_offset,
				list->lock_shअगरt, list->mode_offset,
				list->mode_shअगरt, list->rate_table,
				list->flags, list->pll_flags);
		अगर (IS_ERR(clk)) अणु
			pr_err("%s: failed to register clock %s\n", __func__,
				list->name);
			जारी;
		पूर्ण

		rockchip_clk_add_lookup(ctx, clk, list->id);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rockchip_clk_रेजिस्टर_plls);

व्योम rockchip_clk_रेजिस्टर_branches(काष्ठा rockchip_clk_provider *ctx,
				    काष्ठा rockchip_clk_branch *list,
				    अचिन्हित पूर्णांक nr_clk)
अणु
	काष्ठा clk *clk = शून्य;
	अचिन्हित पूर्णांक idx;
	अचिन्हित दीर्घ flags;

	क्रम (idx = 0; idx < nr_clk; idx++, list++) अणु
		flags = list->flags;

		/* catch simple muxes */
		चयन (list->branch_type) अणु
		हाल branch_mux:
			clk = clk_रेजिस्टर_mux(शून्य, list->name,
				list->parent_names, list->num_parents,
				flags, ctx->reg_base + list->muxभाग_offset,
				list->mux_shअगरt, list->mux_width,
				list->mux_flags, &ctx->lock);
			अवरोध;
		हाल branch_muxgrf:
			clk = rockchip_clk_रेजिस्टर_muxgrf(list->name,
				list->parent_names, list->num_parents,
				flags, ctx->grf, list->muxभाग_offset,
				list->mux_shअगरt, list->mux_width,
				list->mux_flags);
			अवरोध;
		हाल branch_भागider:
			अगर (list->भाग_प्रकारable)
				clk = clk_रेजिस्टर_भागider_table(शून्य,
					list->name, list->parent_names[0],
					flags,
					ctx->reg_base + list->muxभाग_offset,
					list->भाग_shअगरt, list->भाग_width,
					list->भाग_flags, list->भाग_प्रकारable,
					&ctx->lock);
			अन्यथा
				clk = clk_रेजिस्टर_भागider(शून्य, list->name,
					list->parent_names[0], flags,
					ctx->reg_base + list->muxभाग_offset,
					list->भाग_shअगरt, list->भाग_width,
					list->भाग_flags, &ctx->lock);
			अवरोध;
		हाल branch_fraction_भागider:
			clk = rockchip_clk_रेजिस्टर_frac_branch(ctx, list->name,
				list->parent_names, list->num_parents,
				ctx->reg_base, list->muxभाग_offset,
				list->भाग_flags,
				list->gate_offset, list->gate_shअगरt,
				list->gate_flags, flags, list->child,
				&ctx->lock);
			अवरोध;
		हाल branch_half_भागider:
			clk = rockchip_clk_रेजिस्टर_halfभाग(list->name,
				list->parent_names, list->num_parents,
				ctx->reg_base, list->muxभाग_offset,
				list->mux_shअगरt, list->mux_width,
				list->mux_flags, list->भाग_shअगरt,
				list->भाग_width, list->भाग_flags,
				list->gate_offset, list->gate_shअगरt,
				list->gate_flags, flags, &ctx->lock);
			अवरोध;
		हाल branch_gate:
			flags |= CLK_SET_RATE_PARENT;

			clk = clk_रेजिस्टर_gate(शून्य, list->name,
				list->parent_names[0], flags,
				ctx->reg_base + list->gate_offset,
				list->gate_shअगरt, list->gate_flags, &ctx->lock);
			अवरोध;
		हाल branch_composite:
			clk = rockchip_clk_रेजिस्टर_branch(list->name,
				list->parent_names, list->num_parents,
				ctx->reg_base, list->muxभाग_offset,
				list->mux_shअगरt,
				list->mux_width, list->mux_flags,
				list->भाग_offset, list->भाग_shअगरt, list->भाग_width,
				list->भाग_flags, list->भाग_प्रकारable,
				list->gate_offset, list->gate_shअगरt,
				list->gate_flags, flags, &ctx->lock);
			अवरोध;
		हाल branch_mmc:
			clk = rockchip_clk_रेजिस्टर_mmc(
				list->name,
				list->parent_names, list->num_parents,
				ctx->reg_base + list->muxभाग_offset,
				list->भाग_shअगरt
			);
			अवरोध;
		हाल branch_inverter:
			clk = rockchip_clk_रेजिस्टर_inverter(
				list->name, list->parent_names,
				list->num_parents,
				ctx->reg_base + list->muxभाग_offset,
				list->भाग_shअगरt, list->भाग_flags, &ctx->lock);
			अवरोध;
		हाल branch_factor:
			clk = rockchip_clk_रेजिस्टर_factor_branch(
				list->name, list->parent_names,
				list->num_parents, ctx->reg_base,
				list->भाग_shअगरt, list->भाग_width,
				list->gate_offset, list->gate_shअगरt,
				list->gate_flags, flags, &ctx->lock);
			अवरोध;
		हाल branch_ddrclk:
			clk = rockchip_clk_रेजिस्टर_ddrclk(
				list->name, list->flags,
				list->parent_names, list->num_parents,
				list->muxभाग_offset, list->mux_shअगरt,
				list->mux_width, list->भाग_shअगरt,
				list->भाग_width, list->भाग_flags,
				ctx->reg_base, &ctx->lock);
			अवरोध;
		पूर्ण

		/* none of the हालs above matched */
		अगर (!clk) अणु
			pr_err("%s: unknown clock type %d\n",
			       __func__, list->branch_type);
			जारी;
		पूर्ण

		अगर (IS_ERR(clk)) अणु
			pr_err("%s: failed to register clock %s: %ld\n",
			       __func__, list->name, PTR_ERR(clk));
			जारी;
		पूर्ण

		rockchip_clk_add_lookup(ctx, clk, list->id);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rockchip_clk_रेजिस्टर_branches);

व्योम rockchip_clk_रेजिस्टर_armclk(काष्ठा rockchip_clk_provider *ctx,
				  अचिन्हित पूर्णांक lookup_id,
				  स्थिर अक्षर *name, स्थिर अक्षर *स्थिर *parent_names,
				  u8 num_parents,
				  स्थिर काष्ठा rockchip_cpuclk_reg_data *reg_data,
				  स्थिर काष्ठा rockchip_cpuclk_rate_table *rates,
				  पूर्णांक nrates)
अणु
	काष्ठा clk *clk;

	clk = rockchip_clk_रेजिस्टर_cpuclk(name, parent_names, num_parents,
					   reg_data, rates, nrates,
					   ctx->reg_base, &ctx->lock);
	अगर (IS_ERR(clk)) अणु
		pr_err("%s: failed to register clock %s: %ld\n",
		       __func__, name, PTR_ERR(clk));
		वापस;
	पूर्ण

	rockchip_clk_add_lookup(ctx, clk, lookup_id);
पूर्ण
EXPORT_SYMBOL_GPL(rockchip_clk_रेजिस्टर_armclk);

व्योम rockchip_clk_protect_critical(स्थिर अक्षर *स्थिर घड़ीs[],
				   पूर्णांक nघड़ीs)
अणु
	पूर्णांक i;

	/* Protect the घड़ीs that needs to stay on */
	क्रम (i = 0; i < nघड़ीs; i++) अणु
		काष्ठा clk *clk = __clk_lookup(घड़ीs[i]);

		clk_prepare_enable(clk);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rockchip_clk_protect_critical);

अटल व्योम __iomem *rst_base;
अटल अचिन्हित पूर्णांक reg_restart;
अटल व्योम (*cb_restart)(व्योम);
अटल पूर्णांक rockchip_restart_notअगरy(काष्ठा notअगरier_block *this,
				   अचिन्हित दीर्घ mode, व्योम *cmd)
अणु
	अगर (cb_restart)
		cb_restart();

	ग_लिखोl(0xfdb9, rst_base + reg_restart);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block rockchip_restart_handler = अणु
	.notअगरier_call = rockchip_restart_notअगरy,
	.priority = 128,
पूर्ण;

व्योम
rockchip_रेजिस्टर_restart_notअगरier(काष्ठा rockchip_clk_provider *ctx,
				   अचिन्हित पूर्णांक reg,
				   व्योम (*cb)(व्योम))
अणु
	पूर्णांक ret;

	rst_base = ctx->reg_base;
	reg_restart = reg;
	cb_restart = cb;
	ret = रेजिस्टर_restart_handler(&rockchip_restart_handler);
	अगर (ret)
		pr_err("%s: cannot register restart handler, %d\n",
		       __func__, ret);
पूर्ण
EXPORT_SYMBOL_GPL(rockchip_रेजिस्टर_restart_notअगरier);
