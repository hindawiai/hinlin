<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2013 NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>

अटल u8 clk_composite_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_composite *composite = to_clk_composite(hw);
	स्थिर काष्ठा clk_ops *mux_ops = composite->mux_ops;
	काष्ठा clk_hw *mux_hw = composite->mux_hw;

	__clk_hw_set_clk(mux_hw, hw);

	वापस mux_ops->get_parent(mux_hw);
पूर्ण

अटल पूर्णांक clk_composite_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_composite *composite = to_clk_composite(hw);
	स्थिर काष्ठा clk_ops *mux_ops = composite->mux_ops;
	काष्ठा clk_hw *mux_hw = composite->mux_hw;

	__clk_hw_set_clk(mux_hw, hw);

	वापस mux_ops->set_parent(mux_hw, index);
पूर्ण

अटल अचिन्हित दीर्घ clk_composite_recalc_rate(काष्ठा clk_hw *hw,
					    अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_composite *composite = to_clk_composite(hw);
	स्थिर काष्ठा clk_ops *rate_ops = composite->rate_ops;
	काष्ठा clk_hw *rate_hw = composite->rate_hw;

	__clk_hw_set_clk(rate_hw, hw);

	वापस rate_ops->recalc_rate(rate_hw, parent_rate);
पूर्ण

अटल पूर्णांक clk_composite_determine_rate(काष्ठा clk_hw *hw,
					काष्ठा clk_rate_request *req)
अणु
	काष्ठा clk_composite *composite = to_clk_composite(hw);
	स्थिर काष्ठा clk_ops *rate_ops = composite->rate_ops;
	स्थिर काष्ठा clk_ops *mux_ops = composite->mux_ops;
	काष्ठा clk_hw *rate_hw = composite->rate_hw;
	काष्ठा clk_hw *mux_hw = composite->mux_hw;
	काष्ठा clk_hw *parent;
	अचिन्हित दीर्घ parent_rate;
	दीर्घ पंचांगp_rate, best_rate = 0;
	अचिन्हित दीर्घ rate_dअगरf;
	अचिन्हित दीर्घ best_rate_dअगरf = अच_दीर्घ_उच्च;
	दीर्घ rate;
	पूर्णांक i;

	अगर (rate_hw && rate_ops && rate_ops->determine_rate) अणु
		__clk_hw_set_clk(rate_hw, hw);
		वापस rate_ops->determine_rate(rate_hw, req);
	पूर्ण अन्यथा अगर (rate_hw && rate_ops && rate_ops->round_rate &&
		   mux_hw && mux_ops && mux_ops->set_parent) अणु
		req->best_parent_hw = शून्य;

		अगर (clk_hw_get_flags(hw) & CLK_SET_RATE_NO_REPARENT) अणु
			parent = clk_hw_get_parent(mux_hw);
			req->best_parent_hw = parent;
			req->best_parent_rate = clk_hw_get_rate(parent);

			rate = rate_ops->round_rate(rate_hw, req->rate,
						    &req->best_parent_rate);
			अगर (rate < 0)
				वापस rate;

			req->rate = rate;
			वापस 0;
		पूर्ण

		क्रम (i = 0; i < clk_hw_get_num_parents(mux_hw); i++) अणु
			parent = clk_hw_get_parent_by_index(mux_hw, i);
			अगर (!parent)
				जारी;

			parent_rate = clk_hw_get_rate(parent);

			पंचांगp_rate = rate_ops->round_rate(rate_hw, req->rate,
							&parent_rate);
			अगर (पंचांगp_rate < 0)
				जारी;

			rate_dअगरf = असल(req->rate - पंचांगp_rate);

			अगर (!rate_dअगरf || !req->best_parent_hw
				       || best_rate_dअगरf > rate_dअगरf) अणु
				req->best_parent_hw = parent;
				req->best_parent_rate = parent_rate;
				best_rate_dअगरf = rate_dअगरf;
				best_rate = पंचांगp_rate;
			पूर्ण

			अगर (!rate_dअगरf)
				वापस 0;
		पूर्ण

		req->rate = best_rate;
		वापस 0;
	पूर्ण अन्यथा अगर (mux_hw && mux_ops && mux_ops->determine_rate) अणु
		__clk_hw_set_clk(mux_hw, hw);
		वापस mux_ops->determine_rate(mux_hw, req);
	पूर्ण अन्यथा अणु
		pr_err("clk: clk_composite_determine_rate function called, but no mux or rate callback set!\n");
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल दीर्घ clk_composite_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				  अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_composite *composite = to_clk_composite(hw);
	स्थिर काष्ठा clk_ops *rate_ops = composite->rate_ops;
	काष्ठा clk_hw *rate_hw = composite->rate_hw;

	__clk_hw_set_clk(rate_hw, hw);

	वापस rate_ops->round_rate(rate_hw, rate, prate);
पूर्ण

अटल पूर्णांक clk_composite_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
			       अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_composite *composite = to_clk_composite(hw);
	स्थिर काष्ठा clk_ops *rate_ops = composite->rate_ops;
	काष्ठा clk_hw *rate_hw = composite->rate_hw;

	__clk_hw_set_clk(rate_hw, hw);

	वापस rate_ops->set_rate(rate_hw, rate, parent_rate);
पूर्ण

अटल पूर्णांक clk_composite_set_rate_and_parent(काष्ठा clk_hw *hw,
					     अचिन्हित दीर्घ rate,
					     अचिन्हित दीर्घ parent_rate,
					     u8 index)
अणु
	काष्ठा clk_composite *composite = to_clk_composite(hw);
	स्थिर काष्ठा clk_ops *rate_ops = composite->rate_ops;
	स्थिर काष्ठा clk_ops *mux_ops = composite->mux_ops;
	काष्ठा clk_hw *rate_hw = composite->rate_hw;
	काष्ठा clk_hw *mux_hw = composite->mux_hw;
	अचिन्हित दीर्घ temp_rate;

	__clk_hw_set_clk(rate_hw, hw);
	__clk_hw_set_clk(mux_hw, hw);

	temp_rate = rate_ops->recalc_rate(rate_hw, parent_rate);
	अगर (temp_rate > rate) अणु
		rate_ops->set_rate(rate_hw, rate, parent_rate);
		mux_ops->set_parent(mux_hw, index);
	पूर्ण अन्यथा अणु
		mux_ops->set_parent(mux_hw, index);
		rate_ops->set_rate(rate_hw, rate, parent_rate);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक clk_composite_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_composite *composite = to_clk_composite(hw);
	स्थिर काष्ठा clk_ops *gate_ops = composite->gate_ops;
	काष्ठा clk_hw *gate_hw = composite->gate_hw;

	__clk_hw_set_clk(gate_hw, hw);

	वापस gate_ops->is_enabled(gate_hw);
पूर्ण

अटल पूर्णांक clk_composite_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_composite *composite = to_clk_composite(hw);
	स्थिर काष्ठा clk_ops *gate_ops = composite->gate_ops;
	काष्ठा clk_hw *gate_hw = composite->gate_hw;

	__clk_hw_set_clk(gate_hw, hw);

	वापस gate_ops->enable(gate_hw);
पूर्ण

अटल व्योम clk_composite_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_composite *composite = to_clk_composite(hw);
	स्थिर काष्ठा clk_ops *gate_ops = composite->gate_ops;
	काष्ठा clk_hw *gate_hw = composite->gate_hw;

	__clk_hw_set_clk(gate_hw, hw);

	gate_ops->disable(gate_hw);
पूर्ण

अटल काष्ठा clk_hw *__clk_hw_रेजिस्टर_composite(काष्ठा device *dev,
			स्थिर अक्षर *name, स्थिर अक्षर * स्थिर *parent_names,
			स्थिर काष्ठा clk_parent_data *pdata, पूर्णांक num_parents,
			काष्ठा clk_hw *mux_hw, स्थिर काष्ठा clk_ops *mux_ops,
			काष्ठा clk_hw *rate_hw, स्थिर काष्ठा clk_ops *rate_ops,
			काष्ठा clk_hw *gate_hw, स्थिर काष्ठा clk_ops *gate_ops,
			अचिन्हित दीर्घ flags)
अणु
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init = अणुपूर्ण;
	काष्ठा clk_composite *composite;
	काष्ठा clk_ops *clk_composite_ops;
	पूर्णांक ret;

	composite = kzalloc(माप(*composite), GFP_KERNEL);
	अगर (!composite)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.flags = flags;
	अगर (parent_names)
		init.parent_names = parent_names;
	अन्यथा
		init.parent_data = pdata;
	init.num_parents = num_parents;
	hw = &composite->hw;

	clk_composite_ops = &composite->ops;

	अगर (mux_hw && mux_ops) अणु
		अगर (!mux_ops->get_parent) अणु
			hw = ERR_PTR(-EINVAL);
			जाओ err;
		पूर्ण

		composite->mux_hw = mux_hw;
		composite->mux_ops = mux_ops;
		clk_composite_ops->get_parent = clk_composite_get_parent;
		अगर (mux_ops->set_parent)
			clk_composite_ops->set_parent = clk_composite_set_parent;
		अगर (mux_ops->determine_rate)
			clk_composite_ops->determine_rate = clk_composite_determine_rate;
	पूर्ण

	अगर (rate_hw && rate_ops) अणु
		अगर (!rate_ops->recalc_rate) अणु
			hw = ERR_PTR(-EINVAL);
			जाओ err;
		पूर्ण
		clk_composite_ops->recalc_rate = clk_composite_recalc_rate;

		अगर (rate_ops->determine_rate)
			clk_composite_ops->determine_rate =
				clk_composite_determine_rate;
		अन्यथा अगर (rate_ops->round_rate)
			clk_composite_ops->round_rate =
				clk_composite_round_rate;

		/* .set_rate requires either .round_rate or .determine_rate */
		अगर (rate_ops->set_rate) अणु
			अगर (rate_ops->determine_rate || rate_ops->round_rate)
				clk_composite_ops->set_rate =
						clk_composite_set_rate;
			अन्यथा
				WARN(1, "%s: missing round_rate op is required\n",
						__func__);
		पूर्ण

		composite->rate_hw = rate_hw;
		composite->rate_ops = rate_ops;
	पूर्ण

	अगर (mux_hw && mux_ops && rate_hw && rate_ops) अणु
		अगर (mux_ops->set_parent && rate_ops->set_rate)
			clk_composite_ops->set_rate_and_parent =
			clk_composite_set_rate_and_parent;
	पूर्ण

	अगर (gate_hw && gate_ops) अणु
		अगर (!gate_ops->is_enabled || !gate_ops->enable ||
		    !gate_ops->disable) अणु
			hw = ERR_PTR(-EINVAL);
			जाओ err;
		पूर्ण

		composite->gate_hw = gate_hw;
		composite->gate_ops = gate_ops;
		clk_composite_ops->is_enabled = clk_composite_is_enabled;
		clk_composite_ops->enable = clk_composite_enable;
		clk_composite_ops->disable = clk_composite_disable;
	पूर्ण

	init.ops = clk_composite_ops;
	composite->hw.init = &init;

	ret = clk_hw_रेजिस्टर(dev, hw);
	अगर (ret) अणु
		hw = ERR_PTR(ret);
		जाओ err;
	पूर्ण

	अगर (composite->mux_hw)
		composite->mux_hw->clk = hw->clk;

	अगर (composite->rate_hw)
		composite->rate_hw->clk = hw->clk;

	अगर (composite->gate_hw)
		composite->gate_hw->clk = hw->clk;

	वापस hw;

err:
	kमुक्त(composite);
	वापस hw;
पूर्ण

काष्ठा clk_hw *clk_hw_रेजिस्टर_composite(काष्ठा device *dev, स्थिर अक्षर *name,
			स्थिर अक्षर * स्थिर *parent_names, पूर्णांक num_parents,
			काष्ठा clk_hw *mux_hw, स्थिर काष्ठा clk_ops *mux_ops,
			काष्ठा clk_hw *rate_hw, स्थिर काष्ठा clk_ops *rate_ops,
			काष्ठा clk_hw *gate_hw, स्थिर काष्ठा clk_ops *gate_ops,
			अचिन्हित दीर्घ flags)
अणु
	वापस __clk_hw_रेजिस्टर_composite(dev, name, parent_names, शून्य,
					   num_parents, mux_hw, mux_ops,
					   rate_hw, rate_ops, gate_hw,
					   gate_ops, flags);
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_रेजिस्टर_composite);

काष्ठा clk_hw *clk_hw_रेजिस्टर_composite_pdata(काष्ठा device *dev,
			स्थिर अक्षर *name,
			स्थिर काष्ठा clk_parent_data *parent_data,
			पूर्णांक num_parents,
			काष्ठा clk_hw *mux_hw, स्थिर काष्ठा clk_ops *mux_ops,
			काष्ठा clk_hw *rate_hw, स्थिर काष्ठा clk_ops *rate_ops,
			काष्ठा clk_hw *gate_hw, स्थिर काष्ठा clk_ops *gate_ops,
			अचिन्हित दीर्घ flags)
अणु
	वापस __clk_hw_रेजिस्टर_composite(dev, name, शून्य, parent_data,
					   num_parents, mux_hw, mux_ops,
					   rate_hw, rate_ops, gate_hw,
					   gate_ops, flags);
पूर्ण

काष्ठा clk *clk_रेजिस्टर_composite(काष्ठा device *dev, स्थिर अक्षर *name,
			स्थिर अक्षर * स्थिर *parent_names, पूर्णांक num_parents,
			काष्ठा clk_hw *mux_hw, स्थिर काष्ठा clk_ops *mux_ops,
			काष्ठा clk_hw *rate_hw, स्थिर काष्ठा clk_ops *rate_ops,
			काष्ठा clk_hw *gate_hw, स्थिर काष्ठा clk_ops *gate_ops,
			अचिन्हित दीर्घ flags)
अणु
	काष्ठा clk_hw *hw;

	hw = clk_hw_रेजिस्टर_composite(dev, name, parent_names, num_parents,
			mux_hw, mux_ops, rate_hw, rate_ops, gate_hw, gate_ops,
			flags);
	अगर (IS_ERR(hw))
		वापस ERR_CAST(hw);
	वापस hw->clk;
पूर्ण

काष्ठा clk *clk_रेजिस्टर_composite_pdata(काष्ठा device *dev, स्थिर अक्षर *name,
			स्थिर काष्ठा clk_parent_data *parent_data,
			पूर्णांक num_parents,
			काष्ठा clk_hw *mux_hw, स्थिर काष्ठा clk_ops *mux_ops,
			काष्ठा clk_hw *rate_hw, स्थिर काष्ठा clk_ops *rate_ops,
			काष्ठा clk_hw *gate_hw, स्थिर काष्ठा clk_ops *gate_ops,
			अचिन्हित दीर्घ flags)
अणु
	काष्ठा clk_hw *hw;

	hw = clk_hw_रेजिस्टर_composite_pdata(dev, name, parent_data,
			num_parents, mux_hw, mux_ops, rate_hw, rate_ops,
			gate_hw, gate_ops, flags);
	अगर (IS_ERR(hw))
		वापस ERR_CAST(hw);
	वापस hw->clk;
पूर्ण

व्योम clk_unरेजिस्टर_composite(काष्ठा clk *clk)
अणु
	काष्ठा clk_composite *composite;
	काष्ठा clk_hw *hw;

	hw = __clk_get_hw(clk);
	अगर (!hw)
		वापस;

	composite = to_clk_composite(hw);

	clk_unरेजिस्टर(clk);
	kमुक्त(composite);
पूर्ण

व्योम clk_hw_unरेजिस्टर_composite(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_composite *composite;

	composite = to_clk_composite(hw);

	clk_hw_unरेजिस्टर(hw);
	kमुक्त(composite);
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_unरेजिस्टर_composite);

अटल व्योम devm_clk_hw_release_composite(काष्ठा device *dev, व्योम *res)
अणु
	clk_hw_unरेजिस्टर_composite(*(काष्ठा clk_hw **)res);
पूर्ण

अटल काष्ठा clk_hw *__devm_clk_hw_रेजिस्टर_composite(काष्ठा device *dev,
			स्थिर अक्षर *name, स्थिर अक्षर * स्थिर *parent_names,
			स्थिर काष्ठा clk_parent_data *pdata, पूर्णांक num_parents,
			काष्ठा clk_hw *mux_hw, स्थिर काष्ठा clk_ops *mux_ops,
			काष्ठा clk_hw *rate_hw, स्थिर काष्ठा clk_ops *rate_ops,
			काष्ठा clk_hw *gate_hw, स्थिर काष्ठा clk_ops *gate_ops,
			अचिन्हित दीर्घ flags)
अणु
	काष्ठा clk_hw **ptr, *hw;

	ptr = devres_alloc(devm_clk_hw_release_composite, माप(*ptr),
			   GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	hw = __clk_hw_रेजिस्टर_composite(dev, name, parent_names, pdata,
					 num_parents, mux_hw, mux_ops, rate_hw,
					 rate_ops, gate_hw, gate_ops, flags);

	अगर (!IS_ERR(hw)) अणु
		*ptr = hw;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस hw;
पूर्ण

काष्ठा clk_hw *devm_clk_hw_रेजिस्टर_composite_pdata(काष्ठा device *dev,
			स्थिर अक्षर *name,
			स्थिर काष्ठा clk_parent_data *parent_data,
			पूर्णांक num_parents,
			काष्ठा clk_hw *mux_hw, स्थिर काष्ठा clk_ops *mux_ops,
			काष्ठा clk_hw *rate_hw, स्थिर काष्ठा clk_ops *rate_ops,
			काष्ठा clk_hw *gate_hw, स्थिर काष्ठा clk_ops *gate_ops,
			अचिन्हित दीर्घ flags)
अणु
	वापस __devm_clk_hw_रेजिस्टर_composite(dev, name, शून्य, parent_data,
						num_parents, mux_hw, mux_ops,
						rate_hw, rate_ops, gate_hw,
						gate_ops, flags);
पूर्ण
