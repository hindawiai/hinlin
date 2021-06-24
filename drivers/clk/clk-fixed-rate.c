<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2010-2011 Canonical Ltd <jeremy.kerr@canonical.com>
 * Copyright (C) 2011-2012 Mike Turquette, Linaro Ltd <mturquette@linaro.org>
 *
 * Fixed rate घड़ी implementation
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

/*
 * DOC: basic fixed-rate घड़ी that cannot gate
 *
 * Traits of this घड़ी:
 * prepare - clk_(un)prepare only ensures parents are prepared
 * enable - clk_enable only ensures parents are enabled
 * rate - rate is always a fixed value.  No clk_set_rate support
 * parent - fixed parent.  No clk_set_parent support
 */

#घोषणा to_clk_fixed_rate(_hw) container_of(_hw, काष्ठा clk_fixed_rate, hw)

अटल अचिन्हित दीर्घ clk_fixed_rate_recalc_rate(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_rate)
अणु
	वापस to_clk_fixed_rate(hw)->fixed_rate;
पूर्ण

अटल अचिन्हित दीर्घ clk_fixed_rate_recalc_accuracy(काष्ठा clk_hw *hw,
		अचिन्हित दीर्घ parent_accuracy)
अणु
	काष्ठा clk_fixed_rate *fixed = to_clk_fixed_rate(hw);

	अगर (fixed->flags & CLK_FIXED_RATE_PARENT_ACCURACY)
		वापस parent_accuracy;

	वापस fixed->fixed_accuracy;
पूर्ण

स्थिर काष्ठा clk_ops clk_fixed_rate_ops = अणु
	.recalc_rate = clk_fixed_rate_recalc_rate,
	.recalc_accuracy = clk_fixed_rate_recalc_accuracy,
पूर्ण;
EXPORT_SYMBOL_GPL(clk_fixed_rate_ops);

काष्ठा clk_hw *__clk_hw_रेजिस्टर_fixed_rate(काष्ठा device *dev,
		काष्ठा device_node *np, स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, स्थिर काष्ठा clk_hw *parent_hw,
		स्थिर काष्ठा clk_parent_data *parent_data, अचिन्हित दीर्घ flags,
		अचिन्हित दीर्घ fixed_rate, अचिन्हित दीर्घ fixed_accuracy,
		अचिन्हित दीर्घ clk_fixed_flags)
अणु
	काष्ठा clk_fixed_rate *fixed;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init = अणुपूर्ण;
	पूर्णांक ret = -EINVAL;

	/* allocate fixed-rate घड़ी */
	fixed = kzalloc(माप(*fixed), GFP_KERNEL);
	अगर (!fixed)
		वापस ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &clk_fixed_rate_ops;
	init.flags = flags;
	init.parent_names = parent_name ? &parent_name : शून्य;
	init.parent_hws = parent_hw ? &parent_hw : शून्य;
	init.parent_data = parent_data;
	अगर (parent_name || parent_hw || parent_data)
		init.num_parents = 1;
	अन्यथा
		init.num_parents = 0;

	/* काष्ठा clk_fixed_rate assignments */
	fixed->flags = clk_fixed_flags;
	fixed->fixed_rate = fixed_rate;
	fixed->fixed_accuracy = fixed_accuracy;
	fixed->hw.init = &init;

	/* रेजिस्टर the घड़ी */
	hw = &fixed->hw;
	अगर (dev || !np)
		ret = clk_hw_रेजिस्टर(dev, hw);
	अन्यथा अगर (np)
		ret = of_clk_hw_रेजिस्टर(np, hw);
	अगर (ret) अणु
		kमुक्त(fixed);
		hw = ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण
EXPORT_SYMBOL_GPL(__clk_hw_रेजिस्टर_fixed_rate);

काष्ठा clk *clk_रेजिस्टर_fixed_rate(काष्ठा device *dev, स्थिर अक्षर *name,
		स्थिर अक्षर *parent_name, अचिन्हित दीर्घ flags,
		अचिन्हित दीर्घ fixed_rate)
अणु
	काष्ठा clk_hw *hw;

	hw = clk_hw_रेजिस्टर_fixed_rate_with_accuracy(dev, name, parent_name,
						      flags, fixed_rate, 0);
	अगर (IS_ERR(hw))
		वापस ERR_CAST(hw);
	वापस hw->clk;
पूर्ण
EXPORT_SYMBOL_GPL(clk_रेजिस्टर_fixed_rate);

व्योम clk_unरेजिस्टर_fixed_rate(काष्ठा clk *clk)
अणु
	काष्ठा clk_hw *hw;

	hw = __clk_get_hw(clk);
	अगर (!hw)
		वापस;

	clk_unरेजिस्टर(clk);
	kमुक्त(to_clk_fixed_rate(hw));
पूर्ण
EXPORT_SYMBOL_GPL(clk_unरेजिस्टर_fixed_rate);

व्योम clk_hw_unरेजिस्टर_fixed_rate(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_fixed_rate *fixed;

	fixed = to_clk_fixed_rate(hw);

	clk_hw_unरेजिस्टर(hw);
	kमुक्त(fixed);
पूर्ण
EXPORT_SYMBOL_GPL(clk_hw_unरेजिस्टर_fixed_rate);

#अगर_घोषित CONFIG_OF
अटल काष्ठा clk_hw *_of_fixed_clk_setup(काष्ठा device_node *node)
अणु
	काष्ठा clk_hw *hw;
	स्थिर अक्षर *clk_name = node->name;
	u32 rate;
	u32 accuracy = 0;
	पूर्णांक ret;

	अगर (of_property_पढ़ो_u32(node, "clock-frequency", &rate))
		वापस ERR_PTR(-EIO);

	of_property_पढ़ो_u32(node, "clock-accuracy", &accuracy);

	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);

	hw = clk_hw_रेजिस्टर_fixed_rate_with_accuracy(शून्य, clk_name, शून्य,
						    0, rate, accuracy);
	अगर (IS_ERR(hw))
		वापस hw;

	ret = of_clk_add_hw_provider(node, of_clk_hw_simple_get, hw);
	अगर (ret) अणु
		clk_hw_unरेजिस्टर_fixed_rate(hw);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस hw;
पूर्ण

/**
 * of_fixed_clk_setup() - Setup function क्रम simple fixed rate घड़ी
 * @node:	device node क्रम the घड़ी
 */
व्योम __init of_fixed_clk_setup(काष्ठा device_node *node)
अणु
	_of_fixed_clk_setup(node);
पूर्ण
CLK_OF_DECLARE(fixed_clk, "fixed-clock", of_fixed_clk_setup);

अटल पूर्णांक of_fixed_clk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_hw *hw = platक्रमm_get_drvdata(pdev);

	of_clk_del_provider(pdev->dev.of_node);
	clk_hw_unरेजिस्टर_fixed_rate(hw);

	वापस 0;
पूर्ण

अटल पूर्णांक of_fixed_clk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा clk_hw *hw;

	/*
	 * This function is not executed when of_fixed_clk_setup
	 * succeeded.
	 */
	hw = _of_fixed_clk_setup(pdev->dev.of_node);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);

	platक्रमm_set_drvdata(pdev, hw);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_fixed_clk_ids[] = अणु
	अणु .compatible = "fixed-clock" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver of_fixed_clk_driver = अणु
	.driver = अणु
		.name = "of_fixed_clk",
		.of_match_table = of_fixed_clk_ids,
	पूर्ण,
	.probe = of_fixed_clk_probe,
	.हटाओ = of_fixed_clk_हटाओ,
पूर्ण;
builtin_platक्रमm_driver(of_fixed_clk_driver);
#पूर्ण_अगर
