<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2011 Sascha Hauer, Pengutronix <s.hauer@pengutronix.de>
 */
#समावेश <linux/module.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

/*
 * DOC: basic fixed multiplier and भागider घड़ी that cannot gate
 *
 * Traits of this घड़ी:
 * prepare - clk_prepare only ensures that parents are prepared
 * enable - clk_enable only ensures that parents are enabled
 * rate - rate is fixed.  clk->rate = parent->rate / भाग * mult
 * parent - fixed parent.  No clk_set_parent support
 */

अटल अचिन्हित दीर्घ clk_factor_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_fixed_factor *fix = to_clk_fixed_factor(hw);
	अचिन्हित दीर्घ दीर्घ पूर्णांक rate;

	rate = (अचिन्हित दीर्घ दीर्घ पूर्णांक)parent_rate * fix->mult;
	करो_भाग(rate, fix->भाग);
	वापस (अचिन्हित दीर्घ)rate;
पूर्ण

अटल दीर्घ clk_factor_round_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ *prate)
अणु
	काष्ठा clk_fixed_factor *fix = to_clk_fixed_factor(hw);

	अगर (clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT) अणु
		अचिन्हित दीर्घ best_parent;

		best_parent = (rate / fix->mult) * fix->भाग;
		*prate = clk_hw_round_rate(clk_hw_get_parent(hw), best_parent);
	पूर्ण

	वापस (*prate / fix->भाग) * fix->mult;
पूर्ण

अटल पूर्णांक clk_factor_set_rate(काष्ठा clk_hw *hw, अचिन्हित दीर्घ rate,
				अचिन्हित दीर्घ parent_rate)
अणु
	/*
	 * We must report success but we can करो so unconditionally because
	 * clk_factor_round_rate वापसs values that ensure this call is a
	 * nop.
	 */

	वापस 0;
पूर्ण

स्थिर काष्ठा clk_ops clk_fixed_factor_ops = अणु
	.round_rate = clk_factor_round_rate,
	.set_rate = clk_factor_set_rate,
	.recalc_rate = clk_factor_recalc_rate,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_fixed_factor_ops);

अटल व्योम devm_clk_hw_रेजिस्टर_fixed_factor_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा clk_fixed_factor *fix = res;

	/*
	 * We can not use clk_hw_unरेजिस्टर_fixed_factor, since it will kमुक्त()
	 * the hw, resulting in द्विगुन मुक्त. Just unरेजिस्टर the hw and let
	 * devres code kमुक्त() it.
	 */
	clk_hw_unरेजिस्टर(&fix->hw);
पूर्ण

अटल काष्ठा clk_hw *
__clk_hw_रेजिस्टर_fixed_factor(काष्ठा device *dev, काष्ठा device_node *np,
		स्थिर अक्षर *name, स्थिर अक्षर *parent_name, पूर्णांक index,
		अचिन्हित दीर्घ flags, अचिन्हित पूर्णांक mult, अचिन्हित पूर्णांक भाग,
		bool devm)
अणु
	काष्ठा clk_fixed_factor *fix;
	काष्ठा clk_init_data init = अणु पूर्ण;
	काष्ठा clk_parent_data pdata = अणु .index = index पूर्ण;
	काष्ठा clk_hw *hw;
	पूर्णांक ret;

	/* You can't use devm without a dev */
	अगर (devm && !dev)
		वापस ERR_PTR(-EINVAL);

	अगर (devm)
		fix = devres_alloc(devm_clk_hw_रेजिस्टर_fixed_factor_release,
				माप(*fix), GFP_KERNEL);
	अन्यथा
		fix = kदो_स्मृति(माप(*fix), GFP_KERNEL);
	अगर (!fix)
		वापस ERR_PTR(-ENOMEM);

	/* काष्ठा clk_fixed_factor assignments */
	fix->mult = mult;
	fix->भाग = भाग;
	fix->hw.init = &init;

	init.name = name;
	init.ops = &clk_fixed_factor_ops;
	init.flags = flags;
	अगर (parent_name)
		init.parent_names = &parent_name;
	अन्यथा
		init.parent_data = &pdata;
	init.num_parents = 1;

	hw = &fix->hw;
	अगर (dev)
		ret = clk_hw_रेजिस्टर(dev, hw);
	अन्यथा
		ret = of_clk_hw_रेजिस्टर(np, hw);
	अगर (ret) अणु
		अगर (devm)
			devres_मुक्त(fix);
		अन्यथा
			kमुक्त(fix);
		hw = ERR_PTR(ret);
	पूर्ण अन्यथा अगर (devm)
		devres_add(dev, fix);

	वापस hw;
पूर्ण

काष्ठा clk_hw *clk_hw_रेजिस्टर_fixed_factor(काष्ठा device *dev,
		स्थिर अक्षर *name, स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		अचिन्हित पूर्णांक mult, अचिन्हित पूर्णांक भाग)
अणु
	वापस __clk_hw_रेजिस्टर_fixed_factor(dev, शून्य, name, parent_name, -1,
					      flags, mult, भाग, false);
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_रेजिस्टर_fixed_factor);

काष्ठा clk *clk_रेजिस्टर_fixed_factor(काष्ठा device *dev, स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		अचिन्हित पूर्णांक mult, अचिन्हित पूर्णांक भाग)
अणु
	काष्ठा clk_hw *hw;

	hw = clk_hw_रेजिस्टर_fixed_factor(dev, name, parent_name, flags, mult,
					  भाग);
	अगर (IS_ERR(hw))
		वापस ERR_CAST(hw);
	वापस hw->clk;
पूर्ण
EXPORT_SYMBOL_GPL(clk_रेजिस्टर_fixed_factor);

व्योम clk_unरेजिस्टर_fixed_factor(काष्ठा clk *clk)
अणु
	काष्ठा clk_hw *hw;

	hw = __clk_get_hw(clk);
	अगर (!hw)
		वापस;

	clk_unरेजिस्टर(clk);
	kमुक्त(to_clk_fixed_factor(hw));
पूर्ण
EXPORT_SYMBOL_GPL(clk_unरेजिस्टर_fixed_factor);

व्योम clk_hw_unरेजिस्टर_fixed_factor(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_fixed_factor *fix;

	fix = to_clk_fixed_factor(hw);

	clk_hw_unरेजिस्टर(hw);
	kमुक्त(fix);
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_unरेजिस्टर_fixed_factor);

काष्ठा clk_hw *devm_clk_hw_रेजिस्टर_fixed_factor(काष्ठा device *dev,
		स्थिर अक्षर *name, स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		अचिन्हित पूर्णांक mult, अचिन्हित पूर्णांक भाग)
अणु
	वापस __clk_hw_रेजिस्टर_fixed_factor(dev, शून्य, name, parent_name, -1,
			flags, mult, भाग, true);
पूर्ण
EXPORT_SYMBOL_GPL(devm_clk_hw_रेजिस्टर_fixed_factor);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id set_rate_parent_matches[] = अणु
	अणु .compatible = "allwinner,sun4i-a10-pll3-2x-clk" पूर्ण,
	अणु /* Sentinel */ पूर्ण,
पूर्ण;

अटल काष्ठा clk_hw *_of_fixed_factor_clk_setup(काष्ठा device_node *node)
अणु
	काष्ठा clk_hw *hw;
	स्थिर अक्षर *clk_name = node->name;
	अचिन्हित दीर्घ flags = 0;
	u32 भाग, mult;
	पूर्णांक ret;

	अगर (of_property_पढ़ो_u32(node, "clock-div", &भाग)) अणु
		pr_err("%s Fixed factor clock <%pOFn> must have a clock-div property\n",
			__func__, node);
		वापस ERR_PTR(-EIO);
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "clock-mult", &mult)) अणु
		pr_err("%s Fixed factor clock <%pOFn> must have a clock-mult property\n",
			__func__, node);
		वापस ERR_PTR(-EIO);
	पूर्ण

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);

	अगर (of_match_node(set_rate_parent_matches, node))
		flags |= CLK_SET_RATE_PARENT;

	hw = __clk_hw_रेजिस्टर_fixed_factor(शून्य, node, clk_name, शून्य, 0,
					    flags, mult, भाग, false);
	अगर (IS_ERR(hw)) अणु
		/*
		 * Clear OF_POPULATED flag so that घड़ी registration can be
		 * attempted again from probe function.
		 */
		of_node_clear_flag(node, OF_POPULATED);
		वापस ERR_CAST(hw);
	पूर्ण

	ret = of_clk_add_hw_provider(node, of_clk_hw_simple_get, hw);
	अगर (ret) अणु
		clk_hw_unरेजिस्टर_fixed_factor(hw);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

/**
 * of_fixed_factor_clk_setup() - Setup function क्रम simple fixed factor घड़ी
 * @node:	device node क्रम the घड़ी
 */
व्योम __init of_fixed_factor_clk_setup(काष्ठा device_node *node)
अणु
	_of_fixed_factor_clk_setup(node);
पूर्ण
CLK_OF_DECLARE(fixed_factor_clk, "fixed-factor-clock",
		of_fixed_factor_clk_setup);

अटल पूर्णांक of_fixed_factor_clk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_hw *clk = platक्रमm_get_drvdata(pdev);

	of_clk_del_provider(pdev->dev.of_node);
	clk_hw_unरेजिस्टर_fixed_factor(clk);

	वापस 0;
पूर्ण

अटल पूर्णांक of_fixed_factor_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_hw *clk;

	/*
	 * This function is not executed when of_fixed_factor_clk_setup
	 * succeeded.
	 */
	clk = _of_fixed_factor_clk_setup(pdev->dev.of_node);
	अगर (IS_ERR(clk))
		वापस PTR_ERR(clk);

	platक्रमm_set_drvdata(pdev, clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_fixed_factor_clk_ids[] = अणु
	अणु .compatible = "fixed-factor-clock" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, of_fixed_factor_clk_ids);

अटल काष्ठा platक्रमm_driver of_fixed_factor_clk_driver = अणु
	.driver = अणु
		.name = "of_fixed_factor_clk",
		.of_match_table = of_fixed_factor_clk_ids,
	पूर्ण,
	.probe = of_fixed_factor_clk_probe,
	.हटाओ = of_fixed_factor_clk_हटाओ,
पूर्ण;
builtin_platक्रमm_driver(of_fixed_factor_clk_driver);
#पूर्ण_अगर
