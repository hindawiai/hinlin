<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2014 Philipp Zabel, Pengutronix
 *
 * PWM (mis)used as घड़ी output
 */
#समावेश <linux/clk-provider.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>

काष्ठा clk_pwm अणु
	काष्ठा clk_hw hw;
	काष्ठा pwm_device *pwm;
	u32 fixed_rate;
पूर्ण;

अटल अंतरभूत काष्ठा clk_pwm *to_clk_pwm(काष्ठा clk_hw *hw)
अणु
	वापस container_of(hw, काष्ठा clk_pwm, hw);
पूर्ण

अटल पूर्णांक clk_pwm_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pwm *clk_pwm = to_clk_pwm(hw);

	वापस pwm_enable(clk_pwm->pwm);
पूर्ण

अटल व्योम clk_pwm_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_pwm *clk_pwm = to_clk_pwm(hw);

	pwm_disable(clk_pwm->pwm);
पूर्ण

अटल अचिन्हित दीर्घ clk_pwm_recalc_rate(काष्ठा clk_hw *hw,
					 अचिन्हित दीर्घ parent_rate)
अणु
	काष्ठा clk_pwm *clk_pwm = to_clk_pwm(hw);

	वापस clk_pwm->fixed_rate;
पूर्ण

अटल पूर्णांक clk_pwm_get_duty_cycle(काष्ठा clk_hw *hw, काष्ठा clk_duty *duty)
अणु
	काष्ठा clk_pwm *clk_pwm = to_clk_pwm(hw);
	काष्ठा pwm_state state;

	pwm_get_state(clk_pwm->pwm, &state);

	duty->num = state.duty_cycle;
	duty->den = state.period;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_pwm_ops = अणु
	.prepare = clk_pwm_prepare,
	.unprepare = clk_pwm_unprepare,
	.recalc_rate = clk_pwm_recalc_rate,
	.get_duty_cycle = clk_pwm_get_duty_cycle,
पूर्ण;

अटल पूर्णांक clk_pwm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा clk_init_data init;
	काष्ठा clk_pwm *clk_pwm;
	काष्ठा pwm_device *pwm;
	काष्ठा pwm_args pargs;
	स्थिर अक्षर *clk_name;
	पूर्णांक ret;

	clk_pwm = devm_kzalloc(&pdev->dev, माप(*clk_pwm), GFP_KERNEL);
	अगर (!clk_pwm)
		वापस -ENOMEM;

	pwm = devm_pwm_get(&pdev->dev, शून्य);
	अगर (IS_ERR(pwm))
		वापस PTR_ERR(pwm);

	pwm_get_args(pwm, &pargs);
	अगर (!pargs.period) अणु
		dev_err(&pdev->dev, "invalid PWM period\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32(node, "clock-frequency", &clk_pwm->fixed_rate))
		clk_pwm->fixed_rate = भाग64_u64(NSEC_PER_SEC, pargs.period);

	अगर (!clk_pwm->fixed_rate) अणु
		dev_err(&pdev->dev, "fixed_rate cannot be zero\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pargs.period != NSEC_PER_SEC / clk_pwm->fixed_rate &&
	    pargs.period != DIV_ROUND_UP(NSEC_PER_SEC, clk_pwm->fixed_rate)) अणु
		dev_err(&pdev->dev,
			"clock-frequency does not match PWM period\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * FIXME: pwm_apply_args() should be हटाओd when चयनing to the
	 * atomic PWM API.
	 */
	pwm_apply_args(pwm);
	ret = pwm_config(pwm, (pargs.period + 1) >> 1, pargs.period);
	अगर (ret < 0)
		वापस ret;

	clk_name = node->name;
	of_property_पढ़ो_string(node, "clock-output-names", &clk_name);

	init.name = clk_name;
	init.ops = &clk_pwm_ops;
	init.flags = 0;
	init.num_parents = 0;

	clk_pwm->pwm = pwm;
	clk_pwm->hw.init = &init;
	ret = devm_clk_hw_रेजिस्टर(&pdev->dev, &clk_pwm->hw);
	अगर (ret)
		वापस ret;

	वापस of_clk_add_hw_provider(node, of_clk_hw_simple_get, &clk_pwm->hw);
पूर्ण

अटल पूर्णांक clk_pwm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	of_clk_del_provider(pdev->dev.of_node);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id clk_pwm_dt_ids[] = अणु
	अणु .compatible = "pwm-clock" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, clk_pwm_dt_ids);

अटल काष्ठा platक्रमm_driver clk_pwm_driver = अणु
	.probe = clk_pwm_probe,
	.हटाओ = clk_pwm_हटाओ,
	.driver = अणु
		.name = "pwm-clock",
		.of_match_table = clk_pwm_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(clk_pwm_driver);

MODULE_AUTHOR("Philipp Zabel <p.zabel@pengutronix.de>");
MODULE_DESCRIPTION("PWM clock driver");
MODULE_LICENSE("GPL");
