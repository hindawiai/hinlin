<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2013 - 2014 Texas Instruments Incorporated - https://www.ti.com
 *
 * Authors:
 *    Jyri Sarha <jsarha@ti.com>
 *    Sergej Sawazki <ce3a@gmx.de>
 *
 * Gpio controlled घड़ी implementation
 */

#समावेश <linux/clk-provider.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_device.h>

/**
 * DOC: basic gpio gated घड़ी which can be enabled and disabled
 *      with gpio output
 * Traits of this घड़ी:
 * prepare - clk_(un)prepare only ensures parent is (un)prepared
 * enable - clk_enable and clk_disable are functional & control gpio
 * rate - inherits rate from parent.  No clk_set_rate support
 * parent - fixed parent.  No clk_set_parent support
 */

/**
 * काष्ठा clk_gpio - gpio gated घड़ी
 *
 * @hw:		handle between common and hardware-specअगरic पूर्णांकerfaces
 * @gpiod:	gpio descriptor
 *
 * Clock with a gpio control क्रम enabling and disabling the parent घड़ी
 * or चयनing between two parents by निश्चितing or deनिश्चितing the gpio.
 *
 * Implements .enable, .disable and .is_enabled or
 * .get_parent, .set_parent and .determine_rate depending on which clk_ops
 * is used.
 */
काष्ठा clk_gpio अणु
	काष्ठा clk_hw	hw;
	काष्ठा gpio_desc *gpiod;
पूर्ण;

#घोषणा to_clk_gpio(_hw) container_of(_hw, काष्ठा clk_gpio, hw)

अटल पूर्णांक clk_gpio_gate_enable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gpio *clk = to_clk_gpio(hw);

	gpiod_set_value(clk->gpiod, 1);

	वापस 0;
पूर्ण

अटल व्योम clk_gpio_gate_disable(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gpio *clk = to_clk_gpio(hw);

	gpiod_set_value(clk->gpiod, 0);
पूर्ण

अटल पूर्णांक clk_gpio_gate_is_enabled(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gpio *clk = to_clk_gpio(hw);

	वापस gpiod_get_value(clk->gpiod);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_gpio_gate_ops = अणु
	.enable = clk_gpio_gate_enable,
	.disable = clk_gpio_gate_disable,
	.is_enabled = clk_gpio_gate_is_enabled,
पूर्ण;

अटल पूर्णांक clk_sleeping_gpio_gate_prepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gpio *clk = to_clk_gpio(hw);

	gpiod_set_value_cansleep(clk->gpiod, 1);

	वापस 0;
पूर्ण

अटल व्योम clk_sleeping_gpio_gate_unprepare(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gpio *clk = to_clk_gpio(hw);

	gpiod_set_value_cansleep(clk->gpiod, 0);
पूर्ण

अटल पूर्णांक clk_sleeping_gpio_gate_is_prepared(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gpio *clk = to_clk_gpio(hw);

	वापस gpiod_get_value_cansleep(clk->gpiod);
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_sleeping_gpio_gate_ops = अणु
	.prepare = clk_sleeping_gpio_gate_prepare,
	.unprepare = clk_sleeping_gpio_gate_unprepare,
	.is_prepared = clk_sleeping_gpio_gate_is_prepared,
पूर्ण;

/**
 * DOC: basic घड़ी multiplexer which can be controlled with a gpio output
 * Traits of this घड़ी:
 * prepare - clk_prepare only ensures that parents are prepared
 * rate - rate is only affected by parent चयनing.  No clk_set_rate support
 * parent - parent is adjustable through clk_set_parent
 */

अटल u8 clk_gpio_mux_get_parent(काष्ठा clk_hw *hw)
अणु
	काष्ठा clk_gpio *clk = to_clk_gpio(hw);

	वापस gpiod_get_value_cansleep(clk->gpiod);
पूर्ण

अटल पूर्णांक clk_gpio_mux_set_parent(काष्ठा clk_hw *hw, u8 index)
अणु
	काष्ठा clk_gpio *clk = to_clk_gpio(hw);

	gpiod_set_value_cansleep(clk->gpiod, index);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा clk_ops clk_gpio_mux_ops = अणु
	.get_parent = clk_gpio_mux_get_parent,
	.set_parent = clk_gpio_mux_set_parent,
	.determine_rate = __clk_mux_determine_rate,
पूर्ण;

अटल काष्ठा clk_hw *clk_रेजिस्टर_gpio(काष्ठा device *dev, u8 num_parents,
					काष्ठा gpio_desc *gpiod,
					स्थिर काष्ठा clk_ops *clk_gpio_ops)
अणु
	काष्ठा clk_gpio *clk_gpio;
	काष्ठा clk_hw *hw;
	काष्ठा clk_init_data init = अणुपूर्ण;
	पूर्णांक err;
	स्थिर काष्ठा clk_parent_data gpio_parent_data[] = अणु
		अणु .index = 0 पूर्ण,
		अणु .index = 1 पूर्ण,
	पूर्ण;

	clk_gpio = devm_kzalloc(dev, माप(*clk_gpio),	GFP_KERNEL);
	अगर (!clk_gpio)
		वापस ERR_PTR(-ENOMEM);

	init.name = dev->of_node->name;
	init.ops = clk_gpio_ops;
	init.parent_data = gpio_parent_data;
	init.num_parents = num_parents;
	init.flags = CLK_SET_RATE_PARENT;

	clk_gpio->gpiod = gpiod;
	clk_gpio->hw.init = &init;

	hw = &clk_gpio->hw;
	err = devm_clk_hw_रेजिस्टर(dev, hw);
	अगर (err)
		वापस ERR_PTR(err);

	वापस hw;
पूर्ण

अटल काष्ठा clk_hw *clk_hw_रेजिस्टर_gpio_gate(काष्ठा device *dev,
						पूर्णांक num_parents,
						काष्ठा gpio_desc *gpiod)
अणु
	स्थिर काष्ठा clk_ops *ops;

	अगर (gpiod_cansleep(gpiod))
		ops = &clk_sleeping_gpio_gate_ops;
	अन्यथा
		ops = &clk_gpio_gate_ops;

	वापस clk_रेजिस्टर_gpio(dev, num_parents, gpiod, ops);
पूर्ण

अटल काष्ठा clk_hw *clk_hw_रेजिस्टर_gpio_mux(काष्ठा device *dev,
					       काष्ठा gpio_desc *gpiod)
अणु
	वापस clk_रेजिस्टर_gpio(dev, 2, gpiod, &clk_gpio_mux_ops);
पूर्ण

अटल पूर्णांक gpio_clk_driver_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	स्थिर अक्षर *gpio_name;
	अचिन्हित पूर्णांक num_parents;
	काष्ठा gpio_desc *gpiod;
	काष्ठा clk_hw *hw;
	bool is_mux;
	पूर्णांक ret;

	is_mux = of_device_is_compatible(node, "gpio-mux-clock");

	num_parents = of_clk_get_parent_count(node);
	अगर (is_mux && num_parents != 2) अणु
		dev_err(dev, "mux-clock must have 2 parents\n");
		वापस -EINVAL;
	पूर्ण

	gpio_name = is_mux ? "select" : "enable";
	gpiod = devm_gpiod_get(dev, gpio_name, GPIOD_OUT_LOW);
	अगर (IS_ERR(gpiod)) अणु
		ret = PTR_ERR(gpiod);
		अगर (ret == -EPROBE_DEFER)
			pr_debug("%pOFn: %s: GPIOs not yet available, retry later\n",
					node, __func__);
		अन्यथा
			pr_err("%pOFn: %s: Can't get '%s' named GPIO property\n",
					node, __func__,
					gpio_name);
		वापस ret;
	पूर्ण

	अगर (is_mux)
		hw = clk_hw_रेजिस्टर_gpio_mux(dev, gpiod);
	अन्यथा
		hw = clk_hw_रेजिस्टर_gpio_gate(dev, num_parents, gpiod);
	अगर (IS_ERR(hw))
		वापस PTR_ERR(hw);

	वापस devm_of_clk_add_hw_provider(dev, of_clk_hw_simple_get, hw);
पूर्ण

अटल स्थिर काष्ठा of_device_id gpio_clk_match_table[] = अणु
	अणु .compatible = "gpio-mux-clock" पूर्ण,
	अणु .compatible = "gpio-gate-clock" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver gpio_clk_driver = अणु
	.probe		= gpio_clk_driver_probe,
	.driver		= अणु
		.name	= "gpio-clk",
		.of_match_table = gpio_clk_match_table,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(gpio_clk_driver);
