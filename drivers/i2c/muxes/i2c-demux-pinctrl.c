<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Pinctrl based I2C DeMultiplexer
 *
 * Copyright (C) 2015-16 by Wolfram Sang, Sang Engineering <wsa@sang-engineering.com>
 * Copyright (C) 2015-16 by Renesas Electronics Corporation
 *
 * See the bindings करोc क्रम DTS setup and the sysfs करोc क्रम usage inक्रमmation.
 * (look क्रम filenames containing 'i2c-demux-pinctrl' in Documentation/)
 */

#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>

काष्ठा i2c_demux_pinctrl_chan अणु
	काष्ठा device_node *parent_np;
	काष्ठा i2c_adapter *parent_adap;
	काष्ठा of_changeset chgset;
पूर्ण;

काष्ठा i2c_demux_pinctrl_priv अणु
	पूर्णांक cur_chan;
	पूर्णांक num_chan;
	काष्ठा device *dev;
	स्थिर अक्षर *bus_name;
	काष्ठा i2c_adapter cur_adap;
	काष्ठा i2c_algorithm algo;
	काष्ठा i2c_demux_pinctrl_chan chan[];
पूर्ण;

अटल पूर्णांक i2c_demux_master_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg msgs[], पूर्णांक num)
अणु
	काष्ठा i2c_demux_pinctrl_priv *priv = adap->algo_data;
	काष्ठा i2c_adapter *parent = priv->chan[priv->cur_chan].parent_adap;

	वापस __i2c_transfer(parent, msgs, num);
पूर्ण

अटल u32 i2c_demux_functionality(काष्ठा i2c_adapter *adap)
अणु
	काष्ठा i2c_demux_pinctrl_priv *priv = adap->algo_data;
	काष्ठा i2c_adapter *parent = priv->chan[priv->cur_chan].parent_adap;

	वापस parent->algo->functionality(parent);
पूर्ण

अटल पूर्णांक i2c_demux_activate_master(काष्ठा i2c_demux_pinctrl_priv *priv, u32 new_chan)
अणु
	काष्ठा i2c_adapter *adap;
	काष्ठा pinctrl *p;
	पूर्णांक ret;

	ret = of_changeset_apply(&priv->chan[new_chan].chgset);
	अगर (ret)
		जाओ err;

	adap = of_find_i2c_adapter_by_node(priv->chan[new_chan].parent_np);
	अगर (!adap) अणु
		ret = -ENODEV;
		जाओ err_with_revert;
	पूर्ण

	/*
	 * Check अगर there are pinctrl states at all. Note: we cant' use
	 * devm_pinctrl_get_select() because we need to distinguish between
	 * the -ENODEV from devm_pinctrl_get() and pinctrl_lookup_state().
	 */
	p = devm_pinctrl_get(adap->dev.parent);
	अगर (IS_ERR(p)) अणु
		ret = PTR_ERR(p);
		/* जारी अगर just no pinctrl states (e.g. i2c-gpio), otherwise निकास */
		अगर (ret != -ENODEV)
			जाओ err_with_put;
	पूर्ण अन्यथा अणु
		/* there are states. check and use them */
		काष्ठा pinctrl_state *s = pinctrl_lookup_state(p, priv->bus_name);

		अगर (IS_ERR(s)) अणु
			ret = PTR_ERR(s);
			जाओ err_with_put;
		पूर्ण
		ret = pinctrl_select_state(p, s);
		अगर (ret < 0)
			जाओ err_with_put;
	पूर्ण

	priv->chan[new_chan].parent_adap = adap;
	priv->cur_chan = new_chan;

	/* Now fill out current adapter काष्ठाure. cur_chan must be up to date */
	priv->algo.master_xfer = i2c_demux_master_xfer;
	अगर (adap->algo->master_xfer_atomic)
		priv->algo.master_xfer_atomic = i2c_demux_master_xfer;
	priv->algo.functionality = i2c_demux_functionality;

	snम_लिखो(priv->cur_adap.name, माप(priv->cur_adap.name),
		 "i2c-demux (master i2c-%d)", i2c_adapter_id(adap));
	priv->cur_adap.owner = THIS_MODULE;
	priv->cur_adap.algo = &priv->algo;
	priv->cur_adap.algo_data = priv;
	priv->cur_adap.dev.parent = &adap->dev;
	priv->cur_adap.class = adap->class;
	priv->cur_adap.retries = adap->retries;
	priv->cur_adap.समयout = adap->समयout;
	priv->cur_adap.quirks = adap->quirks;
	priv->cur_adap.dev.of_node = priv->dev->of_node;
	ret = i2c_add_adapter(&priv->cur_adap);
	अगर (ret < 0)
		जाओ err_with_put;

	वापस 0;

 err_with_put:
	i2c_put_adapter(adap);
 err_with_revert:
	of_changeset_revert(&priv->chan[new_chan].chgset);
 err:
	dev_err(priv->dev, "failed to setup demux-adapter %d (%d)\n", new_chan, ret);
	priv->cur_chan = -EINVAL;
	वापस ret;
पूर्ण

अटल पूर्णांक i2c_demux_deactivate_master(काष्ठा i2c_demux_pinctrl_priv *priv)
अणु
	पूर्णांक ret, cur = priv->cur_chan;

	अगर (cur < 0)
		वापस 0;

	i2c_del_adapter(&priv->cur_adap);
	i2c_put_adapter(priv->chan[cur].parent_adap);

	ret = of_changeset_revert(&priv->chan[cur].chgset);

	priv->chan[cur].parent_adap = शून्य;
	priv->cur_chan = -EINVAL;

	वापस ret;
पूर्ण

अटल पूर्णांक i2c_demux_change_master(काष्ठा i2c_demux_pinctrl_priv *priv, u32 new_chan)
अणु
	पूर्णांक ret;

	अगर (new_chan == priv->cur_chan)
		वापस 0;

	ret = i2c_demux_deactivate_master(priv);
	अगर (ret)
		वापस ret;

	वापस i2c_demux_activate_master(priv, new_chan);
पूर्ण

अटल sमाप_प्रकार available_masters_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा i2c_demux_pinctrl_priv *priv = dev_get_drvdata(dev);
	पूर्णांक count = 0, i;

	क्रम (i = 0; i < priv->num_chan && count < PAGE_SIZE; i++)
		count += scnम_लिखो(buf + count, PAGE_SIZE - count, "%d:%pOF%c",
				   i, priv->chan[i].parent_np,
				   i == priv->num_chan - 1 ? '\n' : ' ');

	वापस count;
पूर्ण
अटल DEVICE_ATTR_RO(available_masters);

अटल sमाप_प्रकार current_master_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा i2c_demux_pinctrl_priv *priv = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", priv->cur_chan);
पूर्ण

अटल sमाप_प्रकार current_master_store(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_demux_pinctrl_priv *priv = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 0, &val);
	अगर (ret < 0)
		वापस ret;

	अगर (val >= priv->num_chan)
		वापस -EINVAL;

	ret = i2c_demux_change_master(priv, val);

	वापस ret < 0 ? ret : count;
पूर्ण
अटल DEVICE_ATTR_RW(current_master);

अटल पूर्णांक i2c_demux_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा i2c_demux_pinctrl_priv *priv;
	काष्ठा property *props;
	पूर्णांक num_chan, i, j, err;

	num_chan = of_count_phandle_with_args(np, "i2c-parent", शून्य);
	अगर (num_chan < 2) अणु
		dev_err(&pdev->dev, "Need at least two I2C masters to switch\n");
		वापस -EINVAL;
	पूर्ण

	priv = devm_kzalloc(&pdev->dev, काष्ठा_size(priv, chan, num_chan),
			    GFP_KERNEL);

	props = devm_kसुस्मृति(&pdev->dev, num_chan, माप(*props), GFP_KERNEL);

	अगर (!priv || !props)
		वापस -ENOMEM;

	err = of_property_पढ़ो_string(np, "i2c-bus-name", &priv->bus_name);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < num_chan; i++) अणु
		काष्ठा device_node *adap_np;

		adap_np = of_parse_phandle(np, "i2c-parent", i);
		अगर (!adap_np) अणु
			dev_err(&pdev->dev, "can't get phandle for parent %d\n", i);
			err = -ENOENT;
			जाओ err_rollback;
		पूर्ण
		priv->chan[i].parent_np = adap_np;

		props[i].name = devm_kstrdup(&pdev->dev, "status", GFP_KERNEL);
		props[i].value = devm_kstrdup(&pdev->dev, "ok", GFP_KERNEL);
		props[i].length = 3;

		of_changeset_init(&priv->chan[i].chgset);
		of_changeset_update_property(&priv->chan[i].chgset, adap_np, &props[i]);
	पूर्ण

	priv->num_chan = num_chan;
	priv->dev = &pdev->dev;

	platक्रमm_set_drvdata(pdev, priv);

	pm_runसमय_no_callbacks(&pdev->dev);

	/* चयन to first parent as active master */
	i2c_demux_activate_master(priv, 0);

	err = device_create_file(&pdev->dev, &dev_attr_available_masters);
	अगर (err)
		जाओ err_rollback;

	err = device_create_file(&pdev->dev, &dev_attr_current_master);
	अगर (err)
		जाओ err_rollback_available;

	वापस 0;

err_rollback_available:
	device_हटाओ_file(&pdev->dev, &dev_attr_available_masters);
err_rollback:
	i2c_demux_deactivate_master(priv);
	क्रम (j = 0; j < i; j++) अणु
		of_node_put(priv->chan[j].parent_np);
		of_changeset_destroy(&priv->chan[j].chgset);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक i2c_demux_pinctrl_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_demux_pinctrl_priv *priv = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	device_हटाओ_file(&pdev->dev, &dev_attr_current_master);
	device_हटाओ_file(&pdev->dev, &dev_attr_available_masters);

	i2c_demux_deactivate_master(priv);

	क्रम (i = 0; i < priv->num_chan; i++) अणु
		of_node_put(priv->chan[i].parent_np);
		of_changeset_destroy(&priv->chan[i].chgset);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id i2c_demux_pinctrl_of_match[] = अणु
	अणु .compatible = "i2c-demux-pinctrl", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, i2c_demux_pinctrl_of_match);

अटल काष्ठा platक्रमm_driver i2c_demux_pinctrl_driver = अणु
	.driver	= अणु
		.name = "i2c-demux-pinctrl",
		.of_match_table = i2c_demux_pinctrl_of_match,
	पूर्ण,
	.probe	= i2c_demux_pinctrl_probe,
	.हटाओ	= i2c_demux_pinctrl_हटाओ,
पूर्ण;
module_platक्रमm_driver(i2c_demux_pinctrl_driver);

MODULE_DESCRIPTION("pinctrl-based I2C demux driver");
MODULE_AUTHOR("Wolfram Sang <wsa@sang-engineering.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:i2c-demux-pinctrl");
