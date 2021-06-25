<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * I2C multiplexer using pinctrl API
 *
 * Copyright (c) 2012, NVIDIA CORPORATION.  All rights reserved.
 */

#समावेश <linux/i2c.h>
#समावेश <linux/i2c-mux.h>
#समावेश <linux/module.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश "../../pinctrl/core.h"

काष्ठा i2c_mux_pinctrl अणु
	काष्ठा pinctrl *pinctrl;
	काष्ठा pinctrl_state *states[];
पूर्ण;

अटल पूर्णांक i2c_mux_pinctrl_select(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा i2c_mux_pinctrl *mux = i2c_mux_priv(muxc);

	वापस pinctrl_select_state(mux->pinctrl, mux->states[chan]);
पूर्ण

अटल पूर्णांक i2c_mux_pinctrl_deselect(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	वापस i2c_mux_pinctrl_select(muxc, muxc->num_adapters);
पूर्ण

अटल काष्ठा i2c_adapter *i2c_mux_pinctrl_root_adapter(
	काष्ठा pinctrl_state *state)
अणु
	काष्ठा i2c_adapter *root = शून्य;
	काष्ठा pinctrl_setting *setting;
	काष्ठा i2c_adapter *pin_root;

	list_क्रम_each_entry(setting, &state->settings, node) अणु
		pin_root = i2c_root_adapter(setting->pctldev->dev);
		अगर (!pin_root)
			वापस शून्य;
		अगर (!root)
			root = pin_root;
		अन्यथा अगर (root != pin_root)
			वापस शून्य;
	पूर्ण

	वापस root;
पूर्ण

अटल काष्ठा i2c_adapter *i2c_mux_pinctrl_parent_adapter(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *parent_np;
	काष्ठा i2c_adapter *parent;

	parent_np = of_parse_phandle(np, "i2c-parent", 0);
	अगर (!parent_np) अणु
		dev_err(dev, "Cannot parse i2c-parent\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण
	parent = of_find_i2c_adapter_by_node(parent_np);
	of_node_put(parent_np);
	अगर (!parent)
		वापस ERR_PTR(-EPROBE_DEFER);

	वापस parent;
पूर्ण

अटल पूर्णांक i2c_mux_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा i2c_mux_core *muxc;
	काष्ठा i2c_mux_pinctrl *mux;
	काष्ठा i2c_adapter *parent;
	काष्ठा i2c_adapter *root;
	पूर्णांक num_names, i, ret;
	स्थिर अक्षर *name;

	num_names = of_property_count_strings(np, "pinctrl-names");
	अगर (num_names < 0) अणु
		dev_err(dev, "Cannot parse pinctrl-names: %d\n",
			num_names);
		वापस num_names;
	पूर्ण

	parent = i2c_mux_pinctrl_parent_adapter(dev);
	अगर (IS_ERR(parent))
		वापस PTR_ERR(parent);

	muxc = i2c_mux_alloc(parent, dev, num_names,
			     काष्ठा_size(mux, states, num_names),
			     0, i2c_mux_pinctrl_select, शून्य);
	अगर (!muxc) अणु
		ret = -ENOMEM;
		जाओ err_put_parent;
	पूर्ण
	mux = i2c_mux_priv(muxc);

	platक्रमm_set_drvdata(pdev, muxc);

	mux->pinctrl = devm_pinctrl_get(dev);
	अगर (IS_ERR(mux->pinctrl)) अणु
		ret = PTR_ERR(mux->pinctrl);
		dev_err(dev, "Cannot get pinctrl: %d\n", ret);
		जाओ err_put_parent;
	पूर्ण

	क्रम (i = 0; i < num_names; i++) अणु
		ret = of_property_पढ़ो_string_index(np, "pinctrl-names", i,
						    &name);
		अगर (ret < 0) अणु
			dev_err(dev, "Cannot parse pinctrl-names: %d\n", ret);
			जाओ err_put_parent;
		पूर्ण

		mux->states[i] = pinctrl_lookup_state(mux->pinctrl, name);
		अगर (IS_ERR(mux->states[i])) अणु
			ret = PTR_ERR(mux->states[i]);
			dev_err(dev, "Cannot look up pinctrl state %s: %d\n",
				name, ret);
			जाओ err_put_parent;
		पूर्ण

		अगर (म_भेद(name, "idle"))
			जारी;

		अगर (i != num_names - 1) अणु
			dev_err(dev, "idle state must be last\n");
			ret = -EINVAL;
			जाओ err_put_parent;
		पूर्ण
		muxc->deselect = i2c_mux_pinctrl_deselect;
	पूर्ण

	root = i2c_root_adapter(&muxc->parent->dev);

	muxc->mux_locked = true;
	क्रम (i = 0; i < num_names; i++) अणु
		अगर (root != i2c_mux_pinctrl_root_adapter(mux->states[i])) अणु
			muxc->mux_locked = false;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (muxc->mux_locked)
		dev_info(dev, "mux-locked i2c mux\n");

	/* Do not add any adapter क्रम the idle state (अगर it's there at all). */
	क्रम (i = 0; i < num_names - !!muxc->deselect; i++) अणु
		ret = i2c_mux_add_adapter(muxc, 0, i, 0);
		अगर (ret)
			जाओ err_del_adapter;
	पूर्ण

	वापस 0;

err_del_adapter:
	i2c_mux_del_adapters(muxc);
err_put_parent:
	i2c_put_adapter(parent);

	वापस ret;
पूर्ण

अटल पूर्णांक i2c_mux_pinctrl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_mux_core *muxc = platक्रमm_get_drvdata(pdev);

	i2c_mux_del_adapters(muxc);
	i2c_put_adapter(muxc->parent);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id i2c_mux_pinctrl_of_match[] = अणु
	अणु .compatible = "i2c-mux-pinctrl", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, i2c_mux_pinctrl_of_match);

अटल काष्ठा platक्रमm_driver i2c_mux_pinctrl_driver = अणु
	.driver	= अणु
		.name	= "i2c-mux-pinctrl",
		.of_match_table = of_match_ptr(i2c_mux_pinctrl_of_match),
	पूर्ण,
	.probe	= i2c_mux_pinctrl_probe,
	.हटाओ	= i2c_mux_pinctrl_हटाओ,
पूर्ण;
module_platक्रमm_driver(i2c_mux_pinctrl_driver);

MODULE_DESCRIPTION("pinctrl-based I2C multiplexer driver");
MODULE_AUTHOR("Stephen Warren <swarren@nvidia.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:i2c-mux-pinctrl");
