<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * I2C multiplexer using a single रेजिस्टर
 *
 * Copyright 2015 Freescale Semiconductor
 * York Sun  <yorksun@मुक्तscale.com>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/i2c-mux.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/platक्रमm_data/i2c-mux-reg.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

काष्ठा regmux अणु
	काष्ठा i2c_mux_reg_platक्रमm_data data;
पूर्ण;

अटल पूर्णांक i2c_mux_reg_set(स्थिर काष्ठा regmux *mux, अचिन्हित पूर्णांक chan_id)
अणु
	अगर (!mux->data.reg)
		वापस -EINVAL;

	/*
	 * Write to the रेजिस्टर, followed by a पढ़ो to ensure the ग_लिखो is
	 * completed on a "posted" bus, क्रम example PCI or ग_लिखो buffers.
	 * The endianness of पढ़ोing करोesn't matter and the वापस data
	 * is not used.
	 */
	चयन (mux->data.reg_size) अणु
	हाल 4:
		अगर (mux->data.little_endian)
			ioग_लिखो32(chan_id, mux->data.reg);
		अन्यथा
			ioग_लिखो32be(chan_id, mux->data.reg);
		अगर (!mux->data.ग_लिखो_only)
			ioपढ़ो32(mux->data.reg);
		अवरोध;
	हाल 2:
		अगर (mux->data.little_endian)
			ioग_लिखो16(chan_id, mux->data.reg);
		अन्यथा
			ioग_लिखो16be(chan_id, mux->data.reg);
		अगर (!mux->data.ग_लिखो_only)
			ioपढ़ो16(mux->data.reg);
		अवरोध;
	हाल 1:
		ioग_लिखो8(chan_id, mux->data.reg);
		अगर (!mux->data.ग_लिखो_only)
			ioपढ़ो8(mux->data.reg);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक i2c_mux_reg_select(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा regmux *mux = i2c_mux_priv(muxc);

	वापस i2c_mux_reg_set(mux, chan);
पूर्ण

अटल पूर्णांक i2c_mux_reg_deselect(काष्ठा i2c_mux_core *muxc, u32 chan)
अणु
	काष्ठा regmux *mux = i2c_mux_priv(muxc);

	अगर (mux->data.idle_in_use)
		वापस i2c_mux_reg_set(mux, mux->data.idle);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल पूर्णांक i2c_mux_reg_probe_dt(काष्ठा regmux *mux,
				काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *adapter_np, *child;
	काष्ठा i2c_adapter *adapter;
	काष्ठा resource res;
	अचिन्हित *values;
	पूर्णांक i = 0;

	अगर (!np)
		वापस -ENODEV;

	adapter_np = of_parse_phandle(np, "i2c-parent", 0);
	अगर (!adapter_np) अणु
		dev_err(&pdev->dev, "Cannot parse i2c-parent\n");
		वापस -ENODEV;
	पूर्ण
	adapter = of_find_i2c_adapter_by_node(adapter_np);
	of_node_put(adapter_np);
	अगर (!adapter)
		वापस -EPROBE_DEFER;

	mux->data.parent = i2c_adapter_id(adapter);
	put_device(&adapter->dev);

	mux->data.n_values = of_get_child_count(np);
	अगर (of_property_पढ़ो_bool(np, "little-endian")) अणु
		mux->data.little_endian = true;
	पूर्ण अन्यथा अगर (of_property_पढ़ो_bool(np, "big-endian")) अणु
		mux->data.little_endian = false;
	पूर्ण अन्यथा अणु
#अगर defined(__BYTE_ORDER) ? __BYTE_ORDER == __LITTLE_ENDIAN : \
	defined(__LITTLE_ENDIAN)
		mux->data.little_endian = true;
#या_अगर defined(__BYTE_ORDER) ? __BYTE_ORDER == __BIG_ENDIAN : \
	defined(__BIG_ENDIAN)
		mux->data.little_endian = false;
#अन्यथा
#त्रुटि Endianness not defined?
#पूर्ण_अगर
	पूर्ण
	mux->data.ग_लिखो_only = of_property_पढ़ो_bool(np, "write-only");

	values = devm_kसुस्मृति(&pdev->dev,
			      mux->data.n_values, माप(*mux->data.values),
			      GFP_KERNEL);
	अगर (!values)
		वापस -ENOMEM;

	क्रम_each_child_of_node(np, child) अणु
		of_property_पढ़ो_u32(child, "reg", values + i);
		i++;
	पूर्ण
	mux->data.values = values;

	अगर (!of_property_पढ़ो_u32(np, "idle-state", &mux->data.idle))
		mux->data.idle_in_use = true;

	/* map address from "reg" अगर exists */
	अगर (of_address_to_resource(np, 0, &res) == 0) अणु
		mux->data.reg_size = resource_size(&res);
		mux->data.reg = devm_ioremap_resource(&pdev->dev, &res);
		अगर (IS_ERR(mux->data.reg))
			वापस PTR_ERR(mux->data.reg);
	पूर्ण

	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक i2c_mux_reg_probe_dt(काष्ठा regmux *mux,
				काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक i2c_mux_reg_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_mux_core *muxc;
	काष्ठा regmux *mux;
	काष्ठा i2c_adapter *parent;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक class;
	पूर्णांक i, ret, nr;

	mux = devm_kzalloc(&pdev->dev, माप(*mux), GFP_KERNEL);
	अगर (!mux)
		वापस -ENOMEM;

	अगर (dev_get_platdata(&pdev->dev)) अणु
		स_नकल(&mux->data, dev_get_platdata(&pdev->dev),
			माप(mux->data));
	पूर्ण अन्यथा अणु
		ret = i2c_mux_reg_probe_dt(mux, pdev);
		अगर (ret < 0)
			वापस dev_err_probe(&pdev->dev, ret,
					     "Error parsing device tree");
	पूर्ण

	parent = i2c_get_adapter(mux->data.parent);
	अगर (!parent)
		वापस -EPROBE_DEFER;

	अगर (!mux->data.reg) अणु
		dev_info(&pdev->dev,
			"Register not set, using platform resource\n");
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
		mux->data.reg_size = resource_size(res);
		mux->data.reg = devm_ioremap_resource(&pdev->dev, res);
		अगर (IS_ERR(mux->data.reg)) अणु
			ret = PTR_ERR(mux->data.reg);
			जाओ err_put_parent;
		पूर्ण
	पूर्ण

	अगर (mux->data.reg_size != 4 && mux->data.reg_size != 2 &&
	    mux->data.reg_size != 1) अणु
		dev_err(&pdev->dev, "Invalid register size\n");
		ret = -EINVAL;
		जाओ err_put_parent;
	पूर्ण

	muxc = i2c_mux_alloc(parent, &pdev->dev, mux->data.n_values, 0, 0,
			     i2c_mux_reg_select, शून्य);
	अगर (!muxc) अणु
		ret = -ENOMEM;
		जाओ err_put_parent;
	पूर्ण
	muxc->priv = mux;

	platक्रमm_set_drvdata(pdev, muxc);

	अगर (mux->data.idle_in_use)
		muxc->deselect = i2c_mux_reg_deselect;

	क्रम (i = 0; i < mux->data.n_values; i++) अणु
		nr = mux->data.base_nr ? (mux->data.base_nr + i) : 0;
		class = mux->data.classes ? mux->data.classes[i] : 0;

		ret = i2c_mux_add_adapter(muxc, nr, mux->data.values[i], class);
		अगर (ret)
			जाओ err_del_mux_adapters;
	पूर्ण

	dev_dbg(&pdev->dev, "%d port mux on %s adapter\n",
		 mux->data.n_values, muxc->parent->name);

	वापस 0;

err_del_mux_adapters:
	i2c_mux_del_adapters(muxc);
err_put_parent:
	i2c_put_adapter(parent);

	वापस ret;
पूर्ण

अटल पूर्णांक i2c_mux_reg_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_mux_core *muxc = platक्रमm_get_drvdata(pdev);

	i2c_mux_del_adapters(muxc);
	i2c_put_adapter(muxc->parent);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id i2c_mux_reg_of_match[] = अणु
	अणु .compatible = "i2c-mux-reg", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, i2c_mux_reg_of_match);

अटल काष्ठा platक्रमm_driver i2c_mux_reg_driver = अणु
	.probe	= i2c_mux_reg_probe,
	.हटाओ	= i2c_mux_reg_हटाओ,
	.driver	= अणु
		.name	= "i2c-mux-reg",
		.of_match_table = of_match_ptr(i2c_mux_reg_of_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(i2c_mux_reg_driver);

MODULE_DESCRIPTION("Register-based I2C multiplexer driver");
MODULE_AUTHOR("York Sun <yorksun@freescale.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:i2c-mux-reg");
