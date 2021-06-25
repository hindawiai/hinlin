<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * General Purpose I2C multiplexer
 *
 * Copyright (C) 2017 Axentia Technologies AB
 *
 * Author: Peter Rosin <peda@axentia.se>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/i2c-mux.h>
#समावेश <linux/module.h>
#समावेश <linux/mux/consumer.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

काष्ठा mux अणु
	काष्ठा mux_control *control;

	bool करो_not_deselect;
पूर्ण;

अटल पूर्णांक i2c_mux_select(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा mux *mux = i2c_mux_priv(muxc);
	पूर्णांक ret;

	ret = mux_control_select(mux->control, chan);
	mux->करो_not_deselect = ret < 0;

	वापस ret;
पूर्ण

अटल पूर्णांक i2c_mux_deselect(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा mux *mux = i2c_mux_priv(muxc);

	अगर (mux->करो_not_deselect)
		वापस 0;

	वापस mux_control_deselect(mux->control);
पूर्ण

अटल काष्ठा i2c_adapter *mux_parent_adapter(काष्ठा device *dev)
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

अटल स्थिर काष्ठा of_device_id i2c_mux_of_match[] = अणु
	अणु .compatible = "i2c-mux", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, i2c_mux_of_match);

अटल पूर्णांक i2c_mux_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *child;
	काष्ठा i2c_mux_core *muxc;
	काष्ठा mux *mux;
	काष्ठा i2c_adapter *parent;
	पूर्णांक children;
	पूर्णांक ret;

	अगर (!np)
		वापस -ENODEV;

	mux = devm_kzalloc(dev, माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस -ENOMEM;

	mux->control = devm_mux_control_get(dev, शून्य);
	अगर (IS_ERR(mux->control))
		वापस dev_err_probe(dev, PTR_ERR(mux->control),
				     "failed to get control-mux\n");

	parent = mux_parent_adapter(dev);
	अगर (IS_ERR(parent))
		वापस dev_err_probe(dev, PTR_ERR(parent),
				     "failed to get i2c-parent adapter\n");

	children = of_get_child_count(np);

	muxc = i2c_mux_alloc(parent, dev, children, 0, 0,
			     i2c_mux_select, i2c_mux_deselect);
	अगर (!muxc) अणु
		ret = -ENOMEM;
		जाओ err_parent;
	पूर्ण
	muxc->priv = mux;

	platक्रमm_set_drvdata(pdev, muxc);

	muxc->mux_locked = of_property_पढ़ो_bool(np, "mux-locked");

	क्रम_each_child_of_node(np, child) अणु
		u32 chan;

		ret = of_property_पढ़ो_u32(child, "reg", &chan);
		अगर (ret < 0) अणु
			dev_err(dev, "no reg property for node '%pOFn'\n",
				child);
			जाओ err_children;
		पूर्ण

		अगर (chan >= mux_control_states(mux->control)) अणु
			dev_err(dev, "invalid reg %u\n", chan);
			ret = -EINVAL;
			जाओ err_children;
		पूर्ण

		ret = i2c_mux_add_adapter(muxc, 0, chan, 0);
		अगर (ret)
			जाओ err_children;
	पूर्ण

	dev_info(dev, "%d-port mux on %s adapter\n", children, parent->name);

	वापस 0;

err_children:
	i2c_mux_del_adapters(muxc);
err_parent:
	i2c_put_adapter(parent);

	वापस ret;
पूर्ण

अटल पूर्णांक i2c_mux_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_mux_core *muxc = platक्रमm_get_drvdata(pdev);

	i2c_mux_del_adapters(muxc);
	i2c_put_adapter(muxc->parent);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver i2c_mux_driver = अणु
	.probe	= i2c_mux_probe,
	.हटाओ	= i2c_mux_हटाओ,
	.driver	= अणु
		.name	= "i2c-mux-gpmux",
		.of_match_table = i2c_mux_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(i2c_mux_driver);

MODULE_DESCRIPTION("General Purpose I2C multiplexer driver");
MODULE_AUTHOR("Peter Rosin <peda@axentia.se>");
MODULE_LICENSE("GPL v2");
