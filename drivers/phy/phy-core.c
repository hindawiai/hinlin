<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * phy-core.c  --  Generic Phy framework.
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com
 *
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/of.h>
#समावेश <linux/phy/phy.h>
#समावेश <linux/idr.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regulator/consumer.h>

अटल काष्ठा class *phy_class;
अटल DEFINE_MUTEX(phy_provider_mutex);
अटल LIST_HEAD(phy_provider_list);
अटल LIST_HEAD(phys);
अटल DEFINE_IDA(phy_ida);

अटल व्योम devm_phy_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा phy *phy = *(काष्ठा phy **)res;

	phy_put(dev, phy);
पूर्ण

अटल व्योम devm_phy_provider_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा phy_provider *phy_provider = *(काष्ठा phy_provider **)res;

	of_phy_provider_unरेजिस्टर(phy_provider);
पूर्ण

अटल व्योम devm_phy_consume(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा phy *phy = *(काष्ठा phy **)res;

	phy_destroy(phy);
पूर्ण

अटल पूर्णांक devm_phy_match(काष्ठा device *dev, व्योम *res, व्योम *match_data)
अणु
	काष्ठा phy **phy = res;

	वापस *phy == match_data;
पूर्ण

/**
 * phy_create_lookup() - allocate and रेजिस्टर PHY/device association
 * @phy: the phy of the association
 * @con_id: connection ID string on device
 * @dev_id: the device of the association
 *
 * Creates and रेजिस्टरs phy_lookup entry.
 */
पूर्णांक phy_create_lookup(काष्ठा phy *phy, स्थिर अक्षर *con_id, स्थिर अक्षर *dev_id)
अणु
	काष्ठा phy_lookup *pl;

	अगर (!phy || !dev_id || !con_id)
		वापस -EINVAL;

	pl = kzalloc(माप(*pl), GFP_KERNEL);
	अगर (!pl)
		वापस -ENOMEM;

	pl->dev_id = dev_id;
	pl->con_id = con_id;
	pl->phy = phy;

	mutex_lock(&phy_provider_mutex);
	list_add_tail(&pl->node, &phys);
	mutex_unlock(&phy_provider_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(phy_create_lookup);

/**
 * phy_हटाओ_lookup() - find and हटाओ PHY/device association
 * @phy: the phy of the association
 * @con_id: connection ID string on device
 * @dev_id: the device of the association
 *
 * Finds and unरेजिस्टरs phy_lookup entry that was created with
 * phy_create_lookup().
 */
व्योम phy_हटाओ_lookup(काष्ठा phy *phy, स्थिर अक्षर *con_id, स्थिर अक्षर *dev_id)
अणु
	काष्ठा phy_lookup *pl;

	अगर (!phy || !dev_id || !con_id)
		वापस;

	mutex_lock(&phy_provider_mutex);
	list_क्रम_each_entry(pl, &phys, node)
		अगर (pl->phy == phy && !म_भेद(pl->dev_id, dev_id) &&
		    !म_भेद(pl->con_id, con_id)) अणु
			list_del(&pl->node);
			kमुक्त(pl);
			अवरोध;
		पूर्ण
	mutex_unlock(&phy_provider_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(phy_हटाओ_lookup);

अटल काष्ठा phy *phy_find(काष्ठा device *dev, स्थिर अक्षर *con_id)
अणु
	स्थिर अक्षर *dev_id = dev_name(dev);
	काष्ठा phy_lookup *p, *pl = शून्य;

	mutex_lock(&phy_provider_mutex);
	list_क्रम_each_entry(p, &phys, node)
		अगर (!म_भेद(p->dev_id, dev_id) && !म_भेद(p->con_id, con_id)) अणु
			pl = p;
			अवरोध;
		पूर्ण
	mutex_unlock(&phy_provider_mutex);

	वापस pl ? pl->phy : ERR_PTR(-ENODEV);
पूर्ण

अटल काष्ठा phy_provider *of_phy_provider_lookup(काष्ठा device_node *node)
अणु
	काष्ठा phy_provider *phy_provider;
	काष्ठा device_node *child;

	list_क्रम_each_entry(phy_provider, &phy_provider_list, list) अणु
		अगर (phy_provider->dev->of_node == node)
			वापस phy_provider;

		क्रम_each_child_of_node(phy_provider->children, child)
			अगर (child == node)
				वापस phy_provider;
	पूर्ण

	वापस ERR_PTR(-EPROBE_DEFER);
पूर्ण

पूर्णांक phy_pm_runसमय_get(काष्ठा phy *phy)
अणु
	पूर्णांक ret;

	अगर (!phy)
		वापस 0;

	अगर (!pm_runसमय_enabled(&phy->dev))
		वापस -ENOTSUPP;

	ret = pm_runसमय_get(&phy->dev);
	अगर (ret < 0 && ret != -EINPROGRESS)
		pm_runसमय_put_noidle(&phy->dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phy_pm_runसमय_get);

पूर्णांक phy_pm_runसमय_get_sync(काष्ठा phy *phy)
अणु
	पूर्णांक ret;

	अगर (!phy)
		वापस 0;

	अगर (!pm_runसमय_enabled(&phy->dev))
		वापस -ENOTSUPP;

	ret = pm_runसमय_get_sync(&phy->dev);
	अगर (ret < 0)
		pm_runसमय_put_sync(&phy->dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phy_pm_runसमय_get_sync);

पूर्णांक phy_pm_runसमय_put(काष्ठा phy *phy)
अणु
	अगर (!phy)
		वापस 0;

	अगर (!pm_runसमय_enabled(&phy->dev))
		वापस -ENOTSUPP;

	वापस pm_runसमय_put(&phy->dev);
पूर्ण
EXPORT_SYMBOL_GPL(phy_pm_runसमय_put);

पूर्णांक phy_pm_runसमय_put_sync(काष्ठा phy *phy)
अणु
	अगर (!phy)
		वापस 0;

	अगर (!pm_runसमय_enabled(&phy->dev))
		वापस -ENOTSUPP;

	वापस pm_runसमय_put_sync(&phy->dev);
पूर्ण
EXPORT_SYMBOL_GPL(phy_pm_runसमय_put_sync);

व्योम phy_pm_runसमय_allow(काष्ठा phy *phy)
अणु
	अगर (!phy)
		वापस;

	अगर (!pm_runसमय_enabled(&phy->dev))
		वापस;

	pm_runसमय_allow(&phy->dev);
पूर्ण
EXPORT_SYMBOL_GPL(phy_pm_runसमय_allow);

व्योम phy_pm_runसमय_क्रमbid(काष्ठा phy *phy)
अणु
	अगर (!phy)
		वापस;

	अगर (!pm_runसमय_enabled(&phy->dev))
		वापस;

	pm_runसमय_क्रमbid(&phy->dev);
पूर्ण
EXPORT_SYMBOL_GPL(phy_pm_runसमय_क्रमbid);

पूर्णांक phy_init(काष्ठा phy *phy)
अणु
	पूर्णांक ret;

	अगर (!phy)
		वापस 0;

	ret = phy_pm_runसमय_get_sync(phy);
	अगर (ret < 0 && ret != -ENOTSUPP)
		वापस ret;
	ret = 0; /* Override possible ret == -ENOTSUPP */

	mutex_lock(&phy->mutex);
	अगर (phy->init_count == 0 && phy->ops->init) अणु
		ret = phy->ops->init(phy);
		अगर (ret < 0) अणु
			dev_err(&phy->dev, "phy init failed --> %d\n", ret);
			जाओ out;
		पूर्ण
	पूर्ण
	++phy->init_count;

out:
	mutex_unlock(&phy->mutex);
	phy_pm_runसमय_put(phy);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phy_init);

पूर्णांक phy_निकास(काष्ठा phy *phy)
अणु
	पूर्णांक ret;

	अगर (!phy)
		वापस 0;

	ret = phy_pm_runसमय_get_sync(phy);
	अगर (ret < 0 && ret != -ENOTSUPP)
		वापस ret;
	ret = 0; /* Override possible ret == -ENOTSUPP */

	mutex_lock(&phy->mutex);
	अगर (phy->init_count == 1 && phy->ops->निकास) अणु
		ret = phy->ops->निकास(phy);
		अगर (ret < 0) अणु
			dev_err(&phy->dev, "phy exit failed --> %d\n", ret);
			जाओ out;
		पूर्ण
	पूर्ण
	--phy->init_count;

out:
	mutex_unlock(&phy->mutex);
	phy_pm_runसमय_put(phy);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phy_निकास);

पूर्णांक phy_घातer_on(काष्ठा phy *phy)
अणु
	पूर्णांक ret = 0;

	अगर (!phy)
		जाओ out;

	अगर (phy->pwr) अणु
		ret = regulator_enable(phy->pwr);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = phy_pm_runसमय_get_sync(phy);
	अगर (ret < 0 && ret != -ENOTSUPP)
		जाओ err_pm_sync;

	ret = 0; /* Override possible ret == -ENOTSUPP */

	mutex_lock(&phy->mutex);
	अगर (phy->घातer_count == 0 && phy->ops->घातer_on) अणु
		ret = phy->ops->घातer_on(phy);
		अगर (ret < 0) अणु
			dev_err(&phy->dev, "phy poweron failed --> %d\n", ret);
			जाओ err_pwr_on;
		पूर्ण
	पूर्ण
	++phy->घातer_count;
	mutex_unlock(&phy->mutex);
	वापस 0;

err_pwr_on:
	mutex_unlock(&phy->mutex);
	phy_pm_runसमय_put_sync(phy);
err_pm_sync:
	अगर (phy->pwr)
		regulator_disable(phy->pwr);
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phy_घातer_on);

पूर्णांक phy_घातer_off(काष्ठा phy *phy)
अणु
	पूर्णांक ret;

	अगर (!phy)
		वापस 0;

	mutex_lock(&phy->mutex);
	अगर (phy->घातer_count == 1 && phy->ops->घातer_off) अणु
		ret =  phy->ops->घातer_off(phy);
		अगर (ret < 0) अणु
			dev_err(&phy->dev, "phy poweroff failed --> %d\n", ret);
			mutex_unlock(&phy->mutex);
			वापस ret;
		पूर्ण
	पूर्ण
	--phy->घातer_count;
	mutex_unlock(&phy->mutex);
	phy_pm_runसमय_put(phy);

	अगर (phy->pwr)
		regulator_disable(phy->pwr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(phy_घातer_off);

पूर्णांक phy_set_mode_ext(काष्ठा phy *phy, क्रमागत phy_mode mode, पूर्णांक submode)
अणु
	पूर्णांक ret;

	अगर (!phy || !phy->ops->set_mode)
		वापस 0;

	mutex_lock(&phy->mutex);
	ret = phy->ops->set_mode(phy, mode, submode);
	अगर (!ret)
		phy->attrs.mode = mode;
	mutex_unlock(&phy->mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phy_set_mode_ext);

पूर्णांक phy_set_media(काष्ठा phy *phy, क्रमागत phy_media media)
अणु
	पूर्णांक ret;

	अगर (!phy || !phy->ops->set_media)
		वापस 0;

	mutex_lock(&phy->mutex);
	ret = phy->ops->set_media(phy, media);
	mutex_unlock(&phy->mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phy_set_media);

पूर्णांक phy_set_speed(काष्ठा phy *phy, पूर्णांक speed)
अणु
	पूर्णांक ret;

	अगर (!phy || !phy->ops->set_speed)
		वापस 0;

	mutex_lock(&phy->mutex);
	ret = phy->ops->set_speed(phy, speed);
	mutex_unlock(&phy->mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phy_set_speed);

पूर्णांक phy_reset(काष्ठा phy *phy)
अणु
	पूर्णांक ret;

	अगर (!phy || !phy->ops->reset)
		वापस 0;

	ret = phy_pm_runसमय_get_sync(phy);
	अगर (ret < 0 && ret != -ENOTSUPP)
		वापस ret;

	mutex_lock(&phy->mutex);
	ret = phy->ops->reset(phy);
	mutex_unlock(&phy->mutex);

	phy_pm_runसमय_put(phy);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phy_reset);

/**
 * phy_calibrate() - Tunes the phy hw parameters क्रम current configuration
 * @phy: the phy वापसed by phy_get()
 *
 * Used to calibrate phy hardware, typically by adjusting some parameters in
 * runसमय, which are otherwise lost after host controller reset and cannot
 * be applied in phy_init() or phy_घातer_on().
 *
 * Returns: 0 अगर successful, an negative error code otherwise
 */
पूर्णांक phy_calibrate(काष्ठा phy *phy)
अणु
	पूर्णांक ret;

	अगर (!phy || !phy->ops->calibrate)
		वापस 0;

	mutex_lock(&phy->mutex);
	ret = phy->ops->calibrate(phy);
	mutex_unlock(&phy->mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phy_calibrate);

/**
 * phy_configure() - Changes the phy parameters
 * @phy: the phy वापसed by phy_get()
 * @opts: New configuration to apply
 *
 * Used to change the PHY parameters. phy_init() must have been called
 * on the phy. The configuration will be applied on the current phy
 * mode, that can be changed using phy_set_mode().
 *
 * Returns: 0 अगर successful, an negative error code otherwise
 */
पूर्णांक phy_configure(काष्ठा phy *phy, जोड़ phy_configure_opts *opts)
अणु
	पूर्णांक ret;

	अगर (!phy)
		वापस -EINVAL;

	अगर (!phy->ops->configure)
		वापस -EOPNOTSUPP;

	mutex_lock(&phy->mutex);
	ret = phy->ops->configure(phy, opts);
	mutex_unlock(&phy->mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phy_configure);

/**
 * phy_validate() - Checks the phy parameters
 * @phy: the phy वापसed by phy_get()
 * @mode: phy_mode the configuration is applicable to.
 * @submode: PHY submode the configuration is applicable to.
 * @opts: Configuration to check
 *
 * Used to check that the current set of parameters can be handled by
 * the phy. Implementations are मुक्त to tune the parameters passed as
 * arguments अगर needed by some implementation detail or
 * स्थिरraपूर्णांकs. It will not change any actual configuration of the
 * PHY, so calling it as many बार as deemed fit will have no side
 * effect.
 *
 * Returns: 0 अगर successful, an negative error code otherwise
 */
पूर्णांक phy_validate(काष्ठा phy *phy, क्रमागत phy_mode mode, पूर्णांक submode,
		 जोड़ phy_configure_opts *opts)
अणु
	पूर्णांक ret;

	अगर (!phy)
		वापस -EINVAL;

	अगर (!phy->ops->validate)
		वापस -EOPNOTSUPP;

	mutex_lock(&phy->mutex);
	ret = phy->ops->validate(phy, mode, submode, opts);
	mutex_unlock(&phy->mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(phy_validate);

/**
 * _of_phy_get() - lookup and obtain a reference to a phy by phandle
 * @np: device_node क्रम which to get the phy
 * @index: the index of the phy
 *
 * Returns the phy associated with the given phandle value,
 * after getting a refcount to it or -ENODEV अगर there is no such phy or
 * -EPROBE_DEFER अगर there is a phandle to the phy, but the device is
 * not yet loaded. This function uses of_xlate call back function provided
 * जबतक रेजिस्टरing the phy_provider to find the phy instance.
 */
अटल काष्ठा phy *_of_phy_get(काष्ठा device_node *np, पूर्णांक index)
अणु
	पूर्णांक ret;
	काष्ठा phy_provider *phy_provider;
	काष्ठा phy *phy = शून्य;
	काष्ठा of_phandle_args args;

	ret = of_parse_phandle_with_args(np, "phys", "#phy-cells",
		index, &args);
	अगर (ret)
		वापस ERR_PTR(-ENODEV);

	/* This phy type handled by the usb-phy subप्रणाली क्रम now */
	अगर (of_device_is_compatible(args.np, "usb-nop-xceiv"))
		वापस ERR_PTR(-ENODEV);

	mutex_lock(&phy_provider_mutex);
	phy_provider = of_phy_provider_lookup(args.np);
	अगर (IS_ERR(phy_provider) || !try_module_get(phy_provider->owner)) अणु
		phy = ERR_PTR(-EPROBE_DEFER);
		जाओ out_unlock;
	पूर्ण

	अगर (!of_device_is_available(args.np)) अणु
		dev_warn(phy_provider->dev, "Requested PHY is disabled\n");
		phy = ERR_PTR(-ENODEV);
		जाओ out_put_module;
	पूर्ण

	phy = phy_provider->of_xlate(phy_provider->dev, &args);

out_put_module:
	module_put(phy_provider->owner);

out_unlock:
	mutex_unlock(&phy_provider_mutex);
	of_node_put(args.np);

	वापस phy;
पूर्ण

/**
 * of_phy_get() - lookup and obtain a reference to a phy using a device_node.
 * @np: device_node क्रम which to get the phy
 * @con_id: name of the phy from device's poपूर्णांक of view
 *
 * Returns the phy driver, after getting a refcount to it; or
 * -ENODEV अगर there is no such phy. The caller is responsible क्रम
 * calling phy_put() to release that count.
 */
काष्ठा phy *of_phy_get(काष्ठा device_node *np, स्थिर अक्षर *con_id)
अणु
	काष्ठा phy *phy = शून्य;
	पूर्णांक index = 0;

	अगर (con_id)
		index = of_property_match_string(np, "phy-names", con_id);

	phy = _of_phy_get(np, index);
	अगर (IS_ERR(phy))
		वापस phy;

	अगर (!try_module_get(phy->ops->owner))
		वापस ERR_PTR(-EPROBE_DEFER);

	get_device(&phy->dev);

	वापस phy;
पूर्ण
EXPORT_SYMBOL_GPL(of_phy_get);

/**
 * of_phy_put() - release the PHY
 * @phy: the phy वापसed by of_phy_get()
 *
 * Releases a refcount the caller received from of_phy_get().
 */
व्योम of_phy_put(काष्ठा phy *phy)
अणु
	अगर (!phy || IS_ERR(phy))
		वापस;

	mutex_lock(&phy->mutex);
	अगर (phy->ops->release)
		phy->ops->release(phy);
	mutex_unlock(&phy->mutex);

	module_put(phy->ops->owner);
	put_device(&phy->dev);
पूर्ण
EXPORT_SYMBOL_GPL(of_phy_put);

/**
 * phy_put() - release the PHY
 * @dev: device that wants to release this phy
 * @phy: the phy वापसed by phy_get()
 *
 * Releases a refcount the caller received from phy_get().
 */
व्योम phy_put(काष्ठा device *dev, काष्ठा phy *phy)
अणु
	device_link_हटाओ(dev, &phy->dev);
	of_phy_put(phy);
पूर्ण
EXPORT_SYMBOL_GPL(phy_put);

/**
 * devm_phy_put() - release the PHY
 * @dev: device that wants to release this phy
 * @phy: the phy वापसed by devm_phy_get()
 *
 * destroys the devres associated with this phy and invokes phy_put
 * to release the phy.
 */
व्योम devm_phy_put(काष्ठा device *dev, काष्ठा phy *phy)
अणु
	पूर्णांक r;

	अगर (!phy)
		वापस;

	r = devres_destroy(dev, devm_phy_release, devm_phy_match, phy);
	dev_WARN_ONCE(dev, r, "couldn't find PHY resource\n");
पूर्ण
EXPORT_SYMBOL_GPL(devm_phy_put);

/**
 * of_phy_simple_xlate() - वापसs the phy instance from phy provider
 * @dev: the PHY provider device
 * @args: of_phandle_args (not used here)
 *
 * Intended to be used by phy provider क्रम the common हाल where #phy-cells is
 * 0. For other हालs where #phy-cells is greater than '0', the phy provider
 * should provide a custom of_xlate function that पढ़ोs the *args* and वापसs
 * the appropriate phy.
 */
काष्ठा phy *of_phy_simple_xlate(काष्ठा device *dev, काष्ठा of_phandle_args
	*args)
अणु
	काष्ठा phy *phy;
	काष्ठा class_dev_iter iter;

	class_dev_iter_init(&iter, phy_class, शून्य, शून्य);
	जबतक ((dev = class_dev_iter_next(&iter))) अणु
		phy = to_phy(dev);
		अगर (args->np != phy->dev.of_node)
			जारी;

		class_dev_iter_निकास(&iter);
		वापस phy;
	पूर्ण

	class_dev_iter_निकास(&iter);
	वापस ERR_PTR(-ENODEV);
पूर्ण
EXPORT_SYMBOL_GPL(of_phy_simple_xlate);

/**
 * phy_get() - lookup and obtain a reference to a phy.
 * @dev: device that requests this phy
 * @string: the phy name as given in the dt data or the name of the controller
 * port क्रम non-dt हाल
 *
 * Returns the phy driver, after getting a refcount to it; or
 * -ENODEV अगर there is no such phy.  The caller is responsible क्रम
 * calling phy_put() to release that count.
 */
काष्ठा phy *phy_get(काष्ठा device *dev, स्थिर अक्षर *string)
अणु
	पूर्णांक index = 0;
	काष्ठा phy *phy;
	काष्ठा device_link *link;

	अगर (string == शून्य) अणु
		dev_WARN(dev, "missing string\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (dev->of_node) अणु
		index = of_property_match_string(dev->of_node, "phy-names",
			string);
		phy = _of_phy_get(dev->of_node, index);
	पूर्ण अन्यथा अणु
		phy = phy_find(dev, string);
	पूर्ण
	अगर (IS_ERR(phy))
		वापस phy;

	अगर (!try_module_get(phy->ops->owner))
		वापस ERR_PTR(-EPROBE_DEFER);

	get_device(&phy->dev);

	link = device_link_add(dev, &phy->dev, DL_FLAG_STATELESS);
	अगर (!link)
		dev_dbg(dev, "failed to create device link to %s\n",
			dev_name(phy->dev.parent));

	वापस phy;
पूर्ण
EXPORT_SYMBOL_GPL(phy_get);

/**
 * phy_optional_get() - lookup and obtain a reference to an optional phy.
 * @dev: device that requests this phy
 * @string: the phy name as given in the dt data or the name of the controller
 * port क्रम non-dt हाल
 *
 * Returns the phy driver, after getting a refcount to it; or
 * शून्य अगर there is no such phy.  The caller is responsible क्रम
 * calling phy_put() to release that count.
 */
काष्ठा phy *phy_optional_get(काष्ठा device *dev, स्थिर अक्षर *string)
अणु
	काष्ठा phy *phy = phy_get(dev, string);

	अगर (PTR_ERR(phy) == -ENODEV)
		phy = शून्य;

	वापस phy;
पूर्ण
EXPORT_SYMBOL_GPL(phy_optional_get);

/**
 * devm_phy_get() - lookup and obtain a reference to a phy.
 * @dev: device that requests this phy
 * @string: the phy name as given in the dt data or phy device name
 * क्रम non-dt हाल
 *
 * Gets the phy using phy_get(), and associates a device with it using
 * devres. On driver detach, release function is invoked on the devres data,
 * then, devres data is मुक्तd.
 */
काष्ठा phy *devm_phy_get(काष्ठा device *dev, स्थिर अक्षर *string)
अणु
	काष्ठा phy **ptr, *phy;

	ptr = devres_alloc(devm_phy_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	phy = phy_get(dev, string);
	अगर (!IS_ERR(phy)) अणु
		*ptr = phy;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस phy;
पूर्ण
EXPORT_SYMBOL_GPL(devm_phy_get);

/**
 * devm_phy_optional_get() - lookup and obtain a reference to an optional phy.
 * @dev: device that requests this phy
 * @string: the phy name as given in the dt data or phy device name
 * क्रम non-dt हाल
 *
 * Gets the phy using phy_get(), and associates a device with it using
 * devres. On driver detach, release function is invoked on the devres
 * data, then, devres data is मुक्तd. This dअगरfers to devm_phy_get() in
 * that अगर the phy करोes not exist, it is not considered an error and
 * -ENODEV will not be वापसed. Instead the शून्य phy is वापसed,
 * which can be passed to all other phy consumer calls.
 */
काष्ठा phy *devm_phy_optional_get(काष्ठा device *dev, स्थिर अक्षर *string)
अणु
	काष्ठा phy *phy = devm_phy_get(dev, string);

	अगर (PTR_ERR(phy) == -ENODEV)
		phy = शून्य;

	वापस phy;
पूर्ण
EXPORT_SYMBOL_GPL(devm_phy_optional_get);

/**
 * devm_of_phy_get() - lookup and obtain a reference to a phy.
 * @dev: device that requests this phy
 * @np: node containing the phy
 * @con_id: name of the phy from device's poपूर्णांक of view
 *
 * Gets the phy using of_phy_get(), and associates a device with it using
 * devres. On driver detach, release function is invoked on the devres data,
 * then, devres data is मुक्तd.
 */
काष्ठा phy *devm_of_phy_get(काष्ठा device *dev, काष्ठा device_node *np,
			    स्थिर अक्षर *con_id)
अणु
	काष्ठा phy **ptr, *phy;
	काष्ठा device_link *link;

	ptr = devres_alloc(devm_phy_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	phy = of_phy_get(np, con_id);
	अगर (!IS_ERR(phy)) अणु
		*ptr = phy;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
		वापस phy;
	पूर्ण

	link = device_link_add(dev, &phy->dev, DL_FLAG_STATELESS);
	अगर (!link)
		dev_dbg(dev, "failed to create device link to %s\n",
			dev_name(phy->dev.parent));

	वापस phy;
पूर्ण
EXPORT_SYMBOL_GPL(devm_of_phy_get);

/**
 * devm_of_phy_get_by_index() - lookup and obtain a reference to a phy by index.
 * @dev: device that requests this phy
 * @np: node containing the phy
 * @index: index of the phy
 *
 * Gets the phy using _of_phy_get(), then माला_लो a refcount to it,
 * and associates a device with it using devres. On driver detach,
 * release function is invoked on the devres data,
 * then, devres data is मुक्तd.
 *
 */
काष्ठा phy *devm_of_phy_get_by_index(काष्ठा device *dev, काष्ठा device_node *np,
				     पूर्णांक index)
अणु
	काष्ठा phy **ptr, *phy;
	काष्ठा device_link *link;

	ptr = devres_alloc(devm_phy_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	phy = _of_phy_get(np, index);
	अगर (IS_ERR(phy)) अणु
		devres_मुक्त(ptr);
		वापस phy;
	पूर्ण

	अगर (!try_module_get(phy->ops->owner)) अणु
		devres_मुक्त(ptr);
		वापस ERR_PTR(-EPROBE_DEFER);
	पूर्ण

	get_device(&phy->dev);

	*ptr = phy;
	devres_add(dev, ptr);

	link = device_link_add(dev, &phy->dev, DL_FLAG_STATELESS);
	अगर (!link)
		dev_dbg(dev, "failed to create device link to %s\n",
			dev_name(phy->dev.parent));

	वापस phy;
पूर्ण
EXPORT_SYMBOL_GPL(devm_of_phy_get_by_index);

/**
 * phy_create() - create a new phy
 * @dev: device that is creating the new phy
 * @node: device node of the phy
 * @ops: function poपूर्णांकers क्रम perक्रमming phy operations
 *
 * Called to create a phy using phy framework.
 */
काष्ठा phy *phy_create(काष्ठा device *dev, काष्ठा device_node *node,
		       स्थिर काष्ठा phy_ops *ops)
अणु
	पूर्णांक ret;
	पूर्णांक id;
	काष्ठा phy *phy;

	अगर (WARN_ON(!dev))
		वापस ERR_PTR(-EINVAL);

	phy = kzalloc(माप(*phy), GFP_KERNEL);
	अगर (!phy)
		वापस ERR_PTR(-ENOMEM);

	id = ida_simple_get(&phy_ida, 0, 0, GFP_KERNEL);
	अगर (id < 0) अणु
		dev_err(dev, "unable to get id\n");
		ret = id;
		जाओ मुक्त_phy;
	पूर्ण

	device_initialize(&phy->dev);
	mutex_init(&phy->mutex);

	phy->dev.class = phy_class;
	phy->dev.parent = dev;
	phy->dev.of_node = node ?: dev->of_node;
	phy->id = id;
	phy->ops = ops;

	ret = dev_set_name(&phy->dev, "phy-%s.%d", dev_name(dev), id);
	अगर (ret)
		जाओ put_dev;

	/* phy-supply */
	phy->pwr = regulator_get_optional(&phy->dev, "phy");
	अगर (IS_ERR(phy->pwr)) अणु
		ret = PTR_ERR(phy->pwr);
		अगर (ret == -EPROBE_DEFER)
			जाओ put_dev;

		phy->pwr = शून्य;
	पूर्ण

	ret = device_add(&phy->dev);
	अगर (ret)
		जाओ put_dev;

	अगर (pm_runसमय_enabled(dev)) अणु
		pm_runसमय_enable(&phy->dev);
		pm_runसमय_no_callbacks(&phy->dev);
	पूर्ण

	वापस phy;

put_dev:
	put_device(&phy->dev);  /* calls phy_release() which मुक्तs resources */
	वापस ERR_PTR(ret);

मुक्त_phy:
	kमुक्त(phy);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(phy_create);

/**
 * devm_phy_create() - create a new phy
 * @dev: device that is creating the new phy
 * @node: device node of the phy
 * @ops: function poपूर्णांकers क्रम perक्रमming phy operations
 *
 * Creates a new PHY device adding it to the PHY class.
 * While at that, it also associates the device with the phy using devres.
 * On driver detach, release function is invoked on the devres data,
 * then, devres data is मुक्तd.
 */
काष्ठा phy *devm_phy_create(काष्ठा device *dev, काष्ठा device_node *node,
			    स्थिर काष्ठा phy_ops *ops)
अणु
	काष्ठा phy **ptr, *phy;

	ptr = devres_alloc(devm_phy_consume, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	phy = phy_create(dev, node, ops);
	अगर (!IS_ERR(phy)) अणु
		*ptr = phy;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस phy;
पूर्ण
EXPORT_SYMBOL_GPL(devm_phy_create);

/**
 * phy_destroy() - destroy the phy
 * @phy: the phy to be destroyed
 *
 * Called to destroy the phy.
 */
व्योम phy_destroy(काष्ठा phy *phy)
अणु
	pm_runसमय_disable(&phy->dev);
	device_unरेजिस्टर(&phy->dev);
पूर्ण
EXPORT_SYMBOL_GPL(phy_destroy);

/**
 * devm_phy_destroy() - destroy the PHY
 * @dev: device that wants to release this phy
 * @phy: the phy वापसed by devm_phy_get()
 *
 * destroys the devres associated with this phy and invokes phy_destroy
 * to destroy the phy.
 */
व्योम devm_phy_destroy(काष्ठा device *dev, काष्ठा phy *phy)
अणु
	पूर्णांक r;

	r = devres_destroy(dev, devm_phy_consume, devm_phy_match, phy);
	dev_WARN_ONCE(dev, r, "couldn't find PHY resource\n");
पूर्ण
EXPORT_SYMBOL_GPL(devm_phy_destroy);

/**
 * __of_phy_provider_रेजिस्टर() - create/रेजिस्टर phy provider with the framework
 * @dev: काष्ठा device of the phy provider
 * @children: device node containing children (अगर dअगरferent from dev->of_node)
 * @owner: the module owner containing of_xlate
 * @of_xlate: function poपूर्णांकer to obtain phy instance from phy provider
 *
 * Creates काष्ठा phy_provider from dev and of_xlate function poपूर्णांकer.
 * This is used in the हाल of dt boot क्रम finding the phy instance from
 * phy provider.
 *
 * If the PHY provider करोesn't nest children directly but uses a separate
 * child node to contain the inभागidual children, the @children parameter
 * can be used to override the शेष. If शून्य, the शेष (dev->of_node)
 * will be used. If non-शून्य, the device node must be a child (or further
 * descendant) of dev->of_node. Otherwise an ERR_PTR()-encoded -EINVAL
 * error code is वापसed.
 */
काष्ठा phy_provider *__of_phy_provider_रेजिस्टर(काष्ठा device *dev,
	काष्ठा device_node *children, काष्ठा module *owner,
	काष्ठा phy * (*of_xlate)(काष्ठा device *dev,
				 काष्ठा of_phandle_args *args))
अणु
	काष्ठा phy_provider *phy_provider;

	/*
	 * If specअगरied, the device node containing the children must itself
	 * be the provider's device node or a child (or further descendant)
	 * thereof.
	 */
	अगर (children) अणु
		काष्ठा device_node *parent = of_node_get(children), *next;

		जबतक (parent) अणु
			अगर (parent == dev->of_node)
				अवरोध;

			next = of_get_parent(parent);
			of_node_put(parent);
			parent = next;
		पूर्ण

		अगर (!parent)
			वापस ERR_PTR(-EINVAL);

		of_node_put(parent);
	पूर्ण अन्यथा अणु
		children = dev->of_node;
	पूर्ण

	phy_provider = kzalloc(माप(*phy_provider), GFP_KERNEL);
	अगर (!phy_provider)
		वापस ERR_PTR(-ENOMEM);

	phy_provider->dev = dev;
	phy_provider->children = of_node_get(children);
	phy_provider->owner = owner;
	phy_provider->of_xlate = of_xlate;

	mutex_lock(&phy_provider_mutex);
	list_add_tail(&phy_provider->list, &phy_provider_list);
	mutex_unlock(&phy_provider_mutex);

	वापस phy_provider;
पूर्ण
EXPORT_SYMBOL_GPL(__of_phy_provider_रेजिस्टर);

/**
 * __devm_of_phy_provider_रेजिस्टर() - create/रेजिस्टर phy provider with the
 * framework
 * @dev: काष्ठा device of the phy provider
 * @children: device node containing children (अगर dअगरferent from dev->of_node)
 * @owner: the module owner containing of_xlate
 * @of_xlate: function poपूर्णांकer to obtain phy instance from phy provider
 *
 * Creates काष्ठा phy_provider from dev and of_xlate function poपूर्णांकer.
 * This is used in the हाल of dt boot क्रम finding the phy instance from
 * phy provider. While at that, it also associates the device with the
 * phy provider using devres. On driver detach, release function is invoked
 * on the devres data, then, devres data is मुक्तd.
 */
काष्ठा phy_provider *__devm_of_phy_provider_रेजिस्टर(काष्ठा device *dev,
	काष्ठा device_node *children, काष्ठा module *owner,
	काष्ठा phy * (*of_xlate)(काष्ठा device *dev,
				 काष्ठा of_phandle_args *args))
अणु
	काष्ठा phy_provider **ptr, *phy_provider;

	ptr = devres_alloc(devm_phy_provider_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	phy_provider = __of_phy_provider_रेजिस्टर(dev, children, owner,
						  of_xlate);
	अगर (!IS_ERR(phy_provider)) अणु
		*ptr = phy_provider;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
	पूर्ण

	वापस phy_provider;
पूर्ण
EXPORT_SYMBOL_GPL(__devm_of_phy_provider_रेजिस्टर);

/**
 * of_phy_provider_unरेजिस्टर() - unरेजिस्टर phy provider from the framework
 * @phy_provider: phy provider वापसed by of_phy_provider_रेजिस्टर()
 *
 * Removes the phy_provider created using of_phy_provider_रेजिस्टर().
 */
व्योम of_phy_provider_unरेजिस्टर(काष्ठा phy_provider *phy_provider)
अणु
	अगर (IS_ERR(phy_provider))
		वापस;

	mutex_lock(&phy_provider_mutex);
	list_del(&phy_provider->list);
	of_node_put(phy_provider->children);
	kमुक्त(phy_provider);
	mutex_unlock(&phy_provider_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(of_phy_provider_unरेजिस्टर);

/**
 * devm_of_phy_provider_unरेजिस्टर() - हटाओ phy provider from the framework
 * @dev: काष्ठा device of the phy provider
 * @phy_provider: phy provider वापसed by of_phy_provider_रेजिस्टर()
 *
 * destroys the devres associated with this phy provider and invokes
 * of_phy_provider_unरेजिस्टर to unरेजिस्टर the phy provider.
 */
व्योम devm_of_phy_provider_unरेजिस्टर(काष्ठा device *dev,
	काष्ठा phy_provider *phy_provider)
अणु
	पूर्णांक r;

	r = devres_destroy(dev, devm_phy_provider_release, devm_phy_match,
		phy_provider);
	dev_WARN_ONCE(dev, r, "couldn't find PHY provider device resource\n");
पूर्ण
EXPORT_SYMBOL_GPL(devm_of_phy_provider_unरेजिस्टर);

/**
 * phy_release() - release the phy
 * @dev: the dev member within phy
 *
 * When the last reference to the device is हटाओd, it is called
 * from the embedded kobject as release method.
 */
अटल व्योम phy_release(काष्ठा device *dev)
अणु
	काष्ठा phy *phy;

	phy = to_phy(dev);
	dev_vdbg(dev, "releasing '%s'\n", dev_name(dev));
	regulator_put(phy->pwr);
	ida_simple_हटाओ(&phy_ida, phy->id);
	kमुक्त(phy);
पूर्ण

अटल पूर्णांक __init phy_core_init(व्योम)
अणु
	phy_class = class_create(THIS_MODULE, "phy");
	अगर (IS_ERR(phy_class)) अणु
		pr_err("failed to create phy class --> %ld\n",
			PTR_ERR(phy_class));
		वापस PTR_ERR(phy_class);
	पूर्ण

	phy_class->dev_release = phy_release;

	वापस 0;
पूर्ण
device_initcall(phy_core_init);
