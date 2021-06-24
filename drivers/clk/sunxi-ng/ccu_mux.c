<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 Maxime Ripard
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>

#समावेश "ccu_gate.h"
#समावेश "ccu_mux.h"

अटल u16 ccu_mux_get_preभाग(काष्ठा ccu_common *common,
			      काष्ठा ccu_mux_पूर्णांकernal *cm,
			      पूर्णांक parent_index)
अणु
	u16 preभाग = 1;
	u32 reg;

	अगर (!((common->features & CCU_FEATURE_FIXED_PREDIV) ||
	      (common->features & CCU_FEATURE_VARIABLE_PREDIV) ||
	      (common->features & CCU_FEATURE_ALL_PREDIV)))
		वापस 1;

	अगर (common->features & CCU_FEATURE_ALL_PREDIV)
		वापस common->preभाग;

	reg = पढ़ोl(common->base + common->reg);
	अगर (parent_index < 0) अणु
		parent_index = reg >> cm->shअगरt;
		parent_index &= (1 << cm->width) - 1;
	पूर्ण

	अगर (common->features & CCU_FEATURE_FIXED_PREDIV) अणु
		पूर्णांक i;

		क्रम (i = 0; i < cm->n_preभागs; i++)
			अगर (parent_index == cm->fixed_preभागs[i].index)
				preभाग = cm->fixed_preभागs[i].भाग;
	पूर्ण

	अगर (common->features & CCU_FEATURE_VARIABLE_PREDIV) अणु
		पूर्णांक i;

		क्रम (i = 0; i < cm->n_var_preभागs; i++)
			अगर (parent_index == cm->var_preभागs[i].index) अणु
				u8 भाग;

				भाग = reg >> cm->var_preभागs[i].shअगरt;
				भाग &= (1 << cm->var_preभागs[i].width) - 1;
				preभाग = भाग + 1;
			पूर्ण
	पूर्ण

	वापस preभाग;
पूर्ण

अचिन्हित दीर्घ ccu_mux_helper_apply_preभाग(काष्ठा ccu_common *common,
					  काष्ठा ccu_mux_पूर्णांकernal *cm,
					  पूर्णांक parent_index,
					  अचिन्हित दीर्घ parent_rate)
अणु
	वापस parent_rate / ccu_mux_get_preभाग(common, cm, parent_index);
पूर्ण

अटल अचिन्हित दीर्घ ccu_mux_helper_unapply_preभाग(काष्ठा ccu_common *common,
					    काष्ठा ccu_mux_पूर्णांकernal *cm,
					    पूर्णांक parent_index,
					    अचिन्हित दीर्घ parent_rate)
अणु
	वापस parent_rate * ccu_mux_get_preभाग(common, cm, parent_index);
पूर्ण

पूर्णांक ccu_mux_helper_determine_rate(काष्ठा ccu_common *common,
				  काष्ठा ccu_mux_पूर्णांकernal *cm,
				  काष्ठा clk_rate_request *req,
				  अचिन्हित दीर्घ (*round)(काष्ठा ccu_mux_पूर्णांकernal *,
							 काष्ठा clk_hw *,
							 अचिन्हित दीर्घ *,
							 अचिन्हित दीर्घ,
							 व्योम *),
				  व्योम *data)
अणु
	अचिन्हित दीर्घ best_parent_rate = 0, best_rate = 0;
	काष्ठा clk_hw *best_parent, *hw = &common->hw;
	अचिन्हित पूर्णांक i;

	अगर (clk_hw_get_flags(hw) & CLK_SET_RATE_NO_REPARENT) अणु
		अचिन्हित दीर्घ adj_parent_rate;

		best_parent = clk_hw_get_parent(hw);
		best_parent_rate = clk_hw_get_rate(best_parent);
		adj_parent_rate = ccu_mux_helper_apply_preभाग(common, cm, -1,
							      best_parent_rate);

		best_rate = round(cm, best_parent, &adj_parent_rate,
				  req->rate, data);

		/*
		 * adj_parent_rate might have been modअगरied by our घड़ी.
		 * Unapply the pre-भागider अगर there's one, and give
		 * the actual frequency the parent needs to run at.
		 */
		best_parent_rate = ccu_mux_helper_unapply_preभाग(common, cm, -1,
								 adj_parent_rate);

		जाओ out;
	पूर्ण

	क्रम (i = 0; i < clk_hw_get_num_parents(hw); i++) अणु
		अचिन्हित दीर्घ पंचांगp_rate, parent_rate;
		काष्ठा clk_hw *parent;

		parent = clk_hw_get_parent_by_index(hw, i);
		अगर (!parent)
			जारी;

		parent_rate = ccu_mux_helper_apply_preभाग(common, cm, i,
							  clk_hw_get_rate(parent));

		पंचांगp_rate = round(cm, parent, &parent_rate, req->rate, data);

		/*
		 * parent_rate might have been modअगरied by our घड़ी.
		 * Unapply the pre-भागider अगर there's one, and give
		 * the actual frequency the parent needs to run at.
		 */
		parent_rate = ccu_mux_helper_unapply_preभाग(common, cm, i,
							    parent_rate);
		अगर (पंचांगp_rate == req->rate) अणु
			best_parent = parent;
			best_parent_rate = parent_rate;
			best_rate = पंचांगp_rate;
			जाओ out;
		पूर्ण

		अगर ((req->rate - पंचांगp_rate) < (req->rate - best_rate)) अणु
			best_rate = पंचांगp_rate;
			best_parent_rate = parent_rate;
			best_parent = parent;
		पूर्ण
	पूर्ण

	अगर (best_rate == 0)
		वापस -EINVAL;

out:
	req->best_parent_hw = best_parent;
	req->best_parent_rate = best_parent_rate;
	req->rate = best_rate;
	वापस 0;
पूर्ण

u8 ccu_mux_helper_get_parent(काष्ठा ccu_common *common,
			     काष्ठा ccu_mux_पूर्णांकernal *cm)
अणु
	u32 reg;
	u8 parent;

	reg = पढ़ोl(common->base + common->reg);
	parent = reg >> cm->shअगरt;
	parent &= (1 << cm->width) - 1;

	अगर (cm->table) अणु
		पूर्णांक num_parents = clk_hw_get_num_parents(&common->hw);
		पूर्णांक i;

		क्रम (i = 0; i < num_parents; i++)
			अगर (cm->table[i] == parent)
				वापस i;
	पूर्ण

	वापस parent;
पूर्ण

पूर्णांक ccu_mux_helper_set_parent(काष्ठा ccu_common *common,
			      काष्ठा ccu_mux_पूर्णांकernal *cm,
			      u8 index)
अणु
	अचिन्हित दीर्घ flags;
	u32 reg;

	अगर (cm->table)
		index = cm->table[index];

	spin_lock_irqsave(common->lock, flags);

	reg = पढ़ोl(common->base + common->reg);
	reg &= ~GENMASK(cm->width + cm->shअगरt - 1, cm->shअगरt);
	ग_लिखोl(reg | (index << cm->shअगरt), common->base + common->reg);

	spin_unlock_irqrestore(common->lock, flags);

	वापस 0;
पूर्ण

अटल व्योम ccu_mux_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_mux *cm = hw_to_ccu_mux(hw);

	वापस ccu_gate_helper_disable(&cm->common, cm->enable);
पूर्ण

अटल पूर्णांक ccu_mux_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_mux *cm = hw_to_ccu_mux(hw);

	वापस ccu_gate_helper_enable(&cm->common, cm->enable);
पूर्ण

अटल पूर्णांक ccu_mux_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_mux *cm = hw_to_ccu_mux(hw);

	वापस ccu_gate_helper_is_enabled(&cm->common, cm->enable);
पूर्ण

अटल u8 ccu_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा ccu_mux *cm = hw_to_ccu_mux(hw);

	वापस ccu_mux_helper_get_parent(&cm->common, &cm->mux);
पूर्ण

अटल पूर्णांक ccu_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा ccu_mux *cm = hw_to_ccu_mux(hw);

	वापस ccu_mux_helper_set_parent(&cm->common, &cm->mux, index);
पूर्ण

अटल अचिन्हित दीर्घ ccu_mux_recalc_rate(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा ccu_mux *cm = hw_to_ccu_mux(hw);

	वापस ccu_mux_helper_apply_preभाग(&cm->common, &cm->mux, -1,
					   parent_rate);
पूर्ण

स्थिर काष्ठा clk_ops ccu_mux_ops = अणु
	.disable	= ccu_mux_disable,
	.enable		= ccu_mux_enable,
	.is_enabled	= ccu_mux_is_enabled,

	.get_parent	= ccu_mux_get_parent,
	.set_parent	= ccu_mux_set_parent,

	.determine_rate	= __clk_mux_determine_rate,
	.recalc_rate	= ccu_mux_recalc_rate,
पूर्ण;

/*
 * This घड़ी notअगरier is called when the frequency of the of the parent
 * PLL घड़ी is to be changed. The idea is to चयन the parent to a
 * stable घड़ी, such as the मुख्य oscillator, जबतक the PLL frequency
 * stabilizes.
 */
अटल पूर्णांक ccu_mux_notअगरier_cb(काष्ठा notअगरier_block *nb,
			       अचिन्हित दीर्घ event, व्योम *data)
अणु
	काष्ठा ccu_mux_nb *mux = to_ccu_mux_nb(nb);
	पूर्णांक ret = 0;

	अगर (event == PRE_RATE_CHANGE) अणु
		mux->original_index = ccu_mux_helper_get_parent(mux->common,
								mux->cm);
		ret = ccu_mux_helper_set_parent(mux->common, mux->cm,
						mux->bypass_index);
	पूर्ण अन्यथा अगर (event == POST_RATE_CHANGE) अणु
		ret = ccu_mux_helper_set_parent(mux->common, mux->cm,
						mux->original_index);
	पूर्ण

	udelay(mux->delay_us);

	वापस notअगरier_from_त्रुटि_सं(ret);
पूर्ण

पूर्णांक ccu_mux_notअगरier_रेजिस्टर(काष्ठा clk *clk, काष्ठा ccu_mux_nb *mux_nb)
अणु
	mux_nb->clk_nb.notअगरier_call = ccu_mux_notअगरier_cb;

	वापस clk_notअगरier_रेजिस्टर(clk, &mux_nb->clk_nb);
पूर्ण
