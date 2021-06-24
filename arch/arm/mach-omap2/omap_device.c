<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * omap_device implementation
 *
 * Copyright (C) 2009-2010 Nokia Corporation
 * Paul Walmsley, Kevin Hilman
 *
 * Developed in collaboration with (alphabetical order): Benoit
 * Cousson, Thara Gopinath, Tony Lindgren, Rajendra Nayak, Vikram
 * Pandita, Sakari Poussa, Anand Sawant, Santosh Shilimkar, Riअक्षरd
 * Woodruff
 *
 * This code provides a consistent पूर्णांकerface क्रम OMAP device drivers
 * to control घातer management and पूर्णांकerconnect properties of their
 * devices.
 *
 * In the medium- to दीर्घ-term, this code should be implemented as a
 * proper omap_bus/omap_device in Linux, no more platक्रमm_data func
 * poपूर्णांकers
 */
#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/notअगरier.h>

#समावेश "common.h"
#समावेश "soc.h"
#समावेश "omap_device.h"
#समावेश "omap_hwmod.h"

/* Private functions */

अटल व्योम _add_clkdev(काष्ठा omap_device *od, स्थिर अक्षर *clk_alias,
		       स्थिर अक्षर *clk_name)
अणु
	काष्ठा clk *r;
	पूर्णांक rc;

	अगर (!clk_alias || !clk_name)
		वापस;

	dev_dbg(&od->pdev->dev, "Creating %s -> %s\n", clk_alias, clk_name);

	r = clk_get_sys(dev_name(&od->pdev->dev), clk_alias);
	अगर (!IS_ERR(r)) अणु
		dev_dbg(&od->pdev->dev,
			 "alias %s already exists\n", clk_alias);
		clk_put(r);
		वापस;
	पूर्ण

	r = clk_get_sys(शून्य, clk_name);

	अगर (IS_ERR(r)) अणु
		काष्ठा of_phandle_args clkspec;

		clkspec.np = of_find_node_by_name(शून्य, clk_name);

		r = of_clk_get_from_provider(&clkspec);

		rc = clk_रेजिस्टर_clkdev(r, clk_alias,
					 dev_name(&od->pdev->dev));
	पूर्ण अन्यथा अणु
		rc = clk_add_alias(clk_alias, dev_name(&od->pdev->dev),
				   clk_name, शून्य);
	पूर्ण

	अगर (rc) अणु
		अगर (rc == -ENODEV || rc == -ENOMEM)
			dev_err(&od->pdev->dev,
				"clkdev_alloc for %s failed\n", clk_alias);
		अन्यथा
			dev_err(&od->pdev->dev,
				"clk_get for %s failed\n", clk_name);
	पूर्ण
पूर्ण

/**
 * _add_hwmod_घड़ीs_clkdev - Add clkdev entry क्रम hwmod optional घड़ीs
 * and मुख्य घड़ी
 * @od: काष्ठा omap_device *od
 * @oh: काष्ठा omap_hwmod *oh
 *
 * For the मुख्य घड़ी and every optional घड़ी present per hwmod per
 * omap_device, this function adds an entry in the clkdev table of the
 * क्रमm <dev-id=dev_name, con-id=role> अगर it करोes not exist alपढ़ोy.
 *
 * The function is called from inside omap_device_build_ss(), after
 * omap_device_रेजिस्टर.
 *
 * This allows drivers to get a poपूर्णांकer to its optional घड़ीs based on its role
 * by calling clk_get(<dev*>, <role>).
 * In the हाल of the मुख्य घड़ी, a "fck" alias is used.
 *
 * No वापस value.
 */
अटल व्योम _add_hwmod_घड़ीs_clkdev(काष्ठा omap_device *od,
				     काष्ठा omap_hwmod *oh)
अणु
	पूर्णांक i;

	_add_clkdev(od, "fck", oh->मुख्य_clk);

	क्रम (i = 0; i < oh->opt_clks_cnt; i++)
		_add_clkdev(od, oh->opt_clks[i].role, oh->opt_clks[i].clk);
पूर्ण


/**
 * omap_device_build_from_dt - build an omap_device with multiple hwmods
 * @pdev: The platक्रमm device to update.
 *
 * Function क्रम building an omap_device alपढ़ोy रेजिस्टरed from device-tree
 *
 * Returns 0 or PTR_ERR() on error.
 */
अटल पूर्णांक omap_device_build_from_dt(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_hwmod **hwmods;
	काष्ठा omap_device *od;
	काष्ठा omap_hwmod *oh;
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा resource res;
	स्थिर अक्षर *oh_name;
	पूर्णांक oh_cnt, i, ret = 0;
	bool device_active = false, skip_pm_करोमुख्य = false;

	oh_cnt = of_property_count_strings(node, "ti,hwmods");
	अगर (oh_cnt <= 0) अणु
		dev_dbg(&pdev->dev, "No 'hwmods' to build omap_device\n");
		वापस -ENODEV;
	पूर्ण

	/* SDMA still needs special handling क्रम omap_device_build() */
	ret = of_property_पढ़ो_string_index(node, "ti,hwmods", 0, &oh_name);
	अगर (!ret && (!म_भेदन("dma_system", oh_name, 10) ||
		     !म_भेदन("dma", oh_name, 3)))
		skip_pm_करोमुख्य = true;

	/* Use ti-sysc driver instead of omap_device? */
	अगर (!skip_pm_करोमुख्य &&
	    !omap_hwmod_parse_module_range(शून्य, node, &res))
		वापस -ENODEV;

	hwmods = kसुस्मृति(oh_cnt, माप(काष्ठा omap_hwmod *), GFP_KERNEL);
	अगर (!hwmods) अणु
		ret = -ENOMEM;
		जाओ odbfd_निकास;
	पूर्ण

	क्रम (i = 0; i < oh_cnt; i++) अणु
		of_property_पढ़ो_string_index(node, "ti,hwmods", i, &oh_name);
		oh = omap_hwmod_lookup(oh_name);
		अगर (!oh) अणु
			dev_err(&pdev->dev, "Cannot lookup hwmod '%s'\n",
				oh_name);
			ret = -EINVAL;
			जाओ odbfd_निकास1;
		पूर्ण
		hwmods[i] = oh;
		अगर (oh->flags & HWMOD_INIT_NO_IDLE)
			device_active = true;
	पूर्ण

	od = omap_device_alloc(pdev, hwmods, oh_cnt);
	अगर (IS_ERR(od)) अणु
		dev_err(&pdev->dev, "Cannot allocate omap_device for :%s\n",
			oh_name);
		ret = PTR_ERR(od);
		जाओ odbfd_निकास1;
	पूर्ण

	/* Fix up missing resource names */
	क्रम (i = 0; i < pdev->num_resources; i++) अणु
		काष्ठा resource *r = &pdev->resource[i];

		अगर (r->name == शून्य)
			r->name = dev_name(&pdev->dev);
	पूर्ण

	अगर (!skip_pm_करोमुख्य) अणु
		dev_pm_करोमुख्य_set(&pdev->dev, &omap_device_pm_करोमुख्य);
		अगर (device_active) अणु
			omap_device_enable(pdev);
			pm_runसमय_set_active(&pdev->dev);
		पूर्ण
	पूर्ण

odbfd_निकास1:
	kमुक्त(hwmods);
odbfd_निकास:
	/* अगर data/we are at fault.. load up a fail handler */
	अगर (ret)
		dev_pm_करोमुख्य_set(&pdev->dev, &omap_device_fail_pm_करोमुख्य);

	वापस ret;
पूर्ण

अटल पूर्णांक _omap_device_notअगरier_call(काष्ठा notअगरier_block *nb,
				      अचिन्हित दीर्घ event, व्योम *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा omap_device *od;
	पूर्णांक err;

	चयन (event) अणु
	हाल BUS_NOTIFY_REMOVED_DEVICE:
		अगर (pdev->archdata.od)
			omap_device_delete(pdev->archdata.od);
		अवरोध;
	हाल BUS_NOTIFY_UNBOUND_DRIVER:
		od = to_omap_device(pdev);
		अगर (od && (od->_state == OMAP_DEVICE_STATE_ENABLED)) अणु
			dev_info(dev, "enabled after unload, idling\n");
			err = omap_device_idle(pdev);
			अगर (err)
				dev_err(dev, "failed to idle\n");
		पूर्ण
		अवरोध;
	हाल BUS_NOTIFY_BIND_DRIVER:
		od = to_omap_device(pdev);
		अगर (od) अणु
			od->_driver_status = BUS_NOTIFY_BIND_DRIVER;
			अगर (od->_state == OMAP_DEVICE_STATE_ENABLED &&
			    pm_runसमय_status_suspended(dev)) अणु
				pm_runसमय_set_active(dev);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल BUS_NOTIFY_ADD_DEVICE:
		अगर (pdev->dev.of_node)
			omap_device_build_from_dt(pdev);
		omap_auxdata_legacy_init(dev);
		fallthrough;
	शेष:
		od = to_omap_device(pdev);
		अगर (od)
			od->_driver_status = event;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

/**
 * _omap_device_enable_hwmods - call omap_hwmod_enable() on all hwmods
 * @od: काष्ठा omap_device *od
 *
 * Enable all underlying hwmods.  Returns 0.
 */
अटल पूर्णांक _omap_device_enable_hwmods(काष्ठा omap_device *od)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < od->hwmods_cnt; i++)
		ret |= omap_hwmod_enable(od->hwmods[i]);

	वापस ret;
पूर्ण

/**
 * _omap_device_idle_hwmods - call omap_hwmod_idle() on all hwmods
 * @od: काष्ठा omap_device *od
 *
 * Idle all underlying hwmods.  Returns 0.
 */
अटल पूर्णांक _omap_device_idle_hwmods(काष्ठा omap_device *od)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < od->hwmods_cnt; i++)
		ret |= omap_hwmod_idle(od->hwmods[i]);

	वापस ret;
पूर्ण

/* Public functions क्रम use by core code */

/**
 * omap_device_get_context_loss_count - get lost context count
 * @pdev: The platक्रमm device to update.
 *
 * Using the primary hwmod, query the context loss count क्रम this
 * device.
 *
 * Callers should consider context क्रम this device lost any समय this
 * function वापसs a value dअगरferent than the value the caller got
 * the last समय it called this function.
 *
 * If any hwmods exist क्रम the omap_device associated with @pdev,
 * वापस the context loss counter क्रम that hwmod, otherwise वापस
 * zero.
 */
पूर्णांक omap_device_get_context_loss_count(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा omap_device *od;
	u32 ret = 0;

	od = to_omap_device(pdev);

	अगर (od->hwmods_cnt)
		ret = omap_hwmod_get_context_loss_count(od->hwmods[0]);

	वापस ret;
पूर्ण

/**
 * omap_device_alloc - allocate an omap_device
 * @pdev: platक्रमm_device that will be included in this omap_device
 * @ohs: ptr to the omap_hwmod क्रम this omap_device
 * @oh_cnt: the size of the ohs list
 *
 * Convenience function क्रम allocating an omap_device काष्ठाure and filling
 * hwmods, and resources.
 *
 * Returns an काष्ठा omap_device poपूर्णांकer or ERR_PTR() on error;
 */
काष्ठा omap_device *omap_device_alloc(काष्ठा platक्रमm_device *pdev,
					काष्ठा omap_hwmod **ohs, पूर्णांक oh_cnt)
अणु
	पूर्णांक ret = -ENOMEM;
	काष्ठा omap_device *od;
	पूर्णांक i;
	काष्ठा omap_hwmod **hwmods;

	od = kzalloc(माप(काष्ठा omap_device), GFP_KERNEL);
	अगर (!od)
		जाओ oda_निकास1;

	od->hwmods_cnt = oh_cnt;

	hwmods = kmemdup(ohs, माप(काष्ठा omap_hwmod *) * oh_cnt, GFP_KERNEL);
	अगर (!hwmods)
		जाओ oda_निकास2;

	od->hwmods = hwmods;
	od->pdev = pdev;
	pdev->archdata.od = od;

	क्रम (i = 0; i < oh_cnt; i++) अणु
		hwmods[i]->od = od;
		_add_hwmod_घड़ीs_clkdev(od, hwmods[i]);
	पूर्ण

	वापस od;

oda_निकास2:
	kमुक्त(od);
oda_निकास1:
	dev_err(&pdev->dev, "omap_device: build failed (%d)\n", ret);

	वापस ERR_PTR(ret);
पूर्ण

व्योम omap_device_delete(काष्ठा omap_device *od)
अणु
	अगर (!od)
		वापस;

	od->pdev->archdata.od = शून्य;
	kमुक्त(od->hwmods);
	kमुक्त(od);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक _od_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	पूर्णांक ret;

	ret = pm_generic_runसमय_suspend(dev);
	अगर (ret)
		वापस ret;

	वापस omap_device_idle(pdev);
पूर्ण

अटल पूर्णांक _od_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	पूर्णांक ret;

	ret = omap_device_enable(pdev);
	अगर (ret) अणु
		dev_err(dev, "use pm_runtime_put_sync_suspend() in driver?\n");
		वापस ret;
	पूर्ण

	वापस pm_generic_runसमय_resume(dev);
पूर्ण

अटल पूर्णांक _od_fail_runसमय_suspend(काष्ठा device *dev)
अणु
	dev_warn(dev, "%s: FIXME: missing hwmod/omap_dev info\n", __func__);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक _od_fail_runसमय_resume(काष्ठा device *dev)
अणु
	dev_warn(dev, "%s: FIXME: missing hwmod/omap_dev info\n", __func__);
	वापस -ENODEV;
पूर्ण

#पूर्ण_अगर

#अगर_घोषित CONFIG_SUSPEND
अटल पूर्णांक _od_suspend_noirq(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा omap_device *od = to_omap_device(pdev);
	पूर्णांक ret;

	/* Don't attempt late suspend on a driver that is not bound */
	अगर (od->_driver_status != BUS_NOTIFY_BOUND_DRIVER)
		वापस 0;

	ret = pm_generic_suspend_noirq(dev);

	अगर (!ret && !pm_runसमय_status_suspended(dev)) अणु
		अगर (pm_generic_runसमय_suspend(dev) == 0) अणु
			omap_device_idle(pdev);
			od->flags |= OMAP_DEVICE_SUSPENDED;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक _od_resume_noirq(काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा omap_device *od = to_omap_device(pdev);

	अगर (od->flags & OMAP_DEVICE_SUSPENDED) अणु
		od->flags &= ~OMAP_DEVICE_SUSPENDED;
		omap_device_enable(pdev);
		pm_generic_runसमय_resume(dev);
	पूर्ण

	वापस pm_generic_resume_noirq(dev);
पूर्ण
#अन्यथा
#घोषणा _od_suspend_noirq शून्य
#घोषणा _od_resume_noirq शून्य
#पूर्ण_अगर

काष्ठा dev_pm_करोमुख्य omap_device_fail_pm_करोमुख्य = अणु
	.ops = अणु
		SET_RUNTIME_PM_OPS(_od_fail_runसमय_suspend,
				   _od_fail_runसमय_resume, शून्य)
	पूर्ण
पूर्ण;

काष्ठा dev_pm_करोमुख्य omap_device_pm_करोमुख्य = अणु
	.ops = अणु
		SET_RUNTIME_PM_OPS(_od_runसमय_suspend, _od_runसमय_resume,
				   शून्य)
		USE_PLATFORM_PM_SLEEP_OPS
		SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(_od_suspend_noirq,
					      _od_resume_noirq)
	पूर्ण
पूर्ण;

/**
 * omap_device_रेजिस्टर - रेजिस्टर an omap_device with one omap_hwmod
 * @pdev: the platक्रमm device (omap_device) to रेजिस्टर.
 *
 * Register the omap_device काष्ठाure.  This currently just calls
 * platक्रमm_device_रेजिस्टर() on the underlying platक्रमm_device.
 * Returns the वापस value of platक्रमm_device_रेजिस्टर().
 */
पूर्णांक omap_device_रेजिस्टर(काष्ठा platक्रमm_device *pdev)
अणु
	pr_debug("omap_device: %s: registering\n", pdev->name);

	dev_pm_करोमुख्य_set(&pdev->dev, &omap_device_pm_करोमुख्य);
	वापस platक्रमm_device_add(pdev);
पूर्ण


/* Public functions क्रम use by device drivers through काष्ठा platक्रमm_data */

/**
 * omap_device_enable - fully activate an omap_device
 * @pdev: the platक्रमm device to activate
 *
 * Do whatever is necessary क्रम the hwmods underlying omap_device @od
 * to be accessible and पढ़ोy to operate.  This generally involves
 * enabling घड़ीs, setting SYSCONFIG रेजिस्टरs; and in the future may
 * involve remuxing pins.  Device drivers should call this function
 * indirectly via pm_runसमय_get*().  Returns -EINVAL अगर called when
 * the omap_device is alपढ़ोy enabled, or passes aदीर्घ the वापस
 * value of _omap_device_enable_hwmods().
 */
पूर्णांक omap_device_enable(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा omap_device *od;

	od = to_omap_device(pdev);

	अगर (od->_state == OMAP_DEVICE_STATE_ENABLED) अणु
		dev_warn(&pdev->dev,
			 "omap_device: %s() called from invalid state %d\n",
			 __func__, od->_state);
		वापस -EINVAL;
	पूर्ण

	ret = _omap_device_enable_hwmods(od);

	अगर (ret == 0)
		od->_state = OMAP_DEVICE_STATE_ENABLED;

	वापस ret;
पूर्ण

/**
 * omap_device_idle - idle an omap_device
 * @pdev: The platक्रमm_device (omap_device) to idle
 *
 * Idle omap_device @od.  Device drivers call this function indirectly
 * via pm_runसमय_put*().  Returns -EINVAL अगर the omap_device is not
 * currently enabled, or passes aदीर्घ the वापस value of
 * _omap_device_idle_hwmods().
 */
पूर्णांक omap_device_idle(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा omap_device *od;

	od = to_omap_device(pdev);

	अगर (od->_state != OMAP_DEVICE_STATE_ENABLED) अणु
		dev_warn(&pdev->dev,
			 "omap_device: %s() called from invalid state %d\n",
			 __func__, od->_state);
		वापस -EINVAL;
	पूर्ण

	ret = _omap_device_idle_hwmods(od);

	अगर (ret == 0)
		od->_state = OMAP_DEVICE_STATE_IDLE;

	वापस ret;
पूर्ण

/**
 * omap_device_निश्चित_hardreset - set a device's hardreset line
 * @pdev: काष्ठा platक्रमm_device * to reset
 * @name: स्थिर अक्षर * name of the reset line
 *
 * Set the hardreset line identअगरied by @name on the IP blocks
 * associated with the hwmods backing the platक्रमm_device @pdev.  All
 * of the hwmods associated with @pdev must have the same hardreset
 * line linked to them क्रम this to work.  Passes aदीर्घ the वापस value
 * of omap_hwmod_निश्चित_hardreset() in the event of any failure, or
 * वापसs 0 upon success.
 */
पूर्णांक omap_device_निश्चित_hardreset(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *name)
अणु
	काष्ठा omap_device *od = to_omap_device(pdev);
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < od->hwmods_cnt; i++) अणु
		ret = omap_hwmod_निश्चित_hardreset(od->hwmods[i], name);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * omap_device_deनिश्चित_hardreset - release a device's hardreset line
 * @pdev: काष्ठा platक्रमm_device * to reset
 * @name: स्थिर अक्षर * name of the reset line
 *
 * Release the hardreset line identअगरied by @name on the IP blocks
 * associated with the hwmods backing the platक्रमm_device @pdev.  All
 * of the hwmods associated with @pdev must have the same hardreset
 * line linked to them क्रम this to work.  Passes aदीर्घ the वापस
 * value of omap_hwmod_deनिश्चित_hardreset() in the event of any
 * failure, or वापसs 0 upon success.
 */
पूर्णांक omap_device_deनिश्चित_hardreset(काष्ठा platक्रमm_device *pdev,
				   स्थिर अक्षर *name)
अणु
	काष्ठा omap_device *od = to_omap_device(pdev);
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < od->hwmods_cnt; i++) अणु
		ret = omap_hwmod_deनिश्चित_hardreset(od->hwmods[i], name);
		अगर (ret)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * omap_device_get_by_hwmod_name() - convert a hwmod name to
 * device poपूर्णांकer.
 * @oh_name: name of the hwmod device
 *
 * Returns back a काष्ठा device * poपूर्णांकer associated with a hwmod
 * device represented by a hwmod_name
 */
काष्ठा device *omap_device_get_by_hwmod_name(स्थिर अक्षर *oh_name)
अणु
	काष्ठा omap_hwmod *oh;

	अगर (!oh_name) अणु
		WARN(1, "%s: no hwmod name!\n", __func__);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	oh = omap_hwmod_lookup(oh_name);
	अगर (!oh) अणु
		WARN(1, "%s: no hwmod for %s\n", __func__,
			oh_name);
		वापस ERR_PTR(-ENODEV);
	पूर्ण
	अगर (!oh->od) अणु
		WARN(1, "%s: no omap_device for %s\n", __func__,
			oh_name);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	वापस &oh->od->pdev->dev;
पूर्ण

अटल काष्ठा notअगरier_block platक्रमm_nb = अणु
	.notअगरier_call = _omap_device_notअगरier_call,
पूर्ण;

अटल पूर्णांक __init omap_device_init(व्योम)
अणु
	bus_रेजिस्टर_notअगरier(&platक्रमm_bus_type, &platक्रमm_nb);
	वापस 0;
पूर्ण
omap_postcore_initcall(omap_device_init);

/**
 * omap_device_late_idle - idle devices without drivers
 * @dev: काष्ठा device * associated with omap_device
 * @data: unused
 *
 * Check the driver bound status of this device, and idle it
 * अगर there is no driver attached.
 */
अटल पूर्णांक __init omap_device_late_idle(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा omap_device *od = to_omap_device(pdev);
	पूर्णांक i;

	अगर (!od)
		वापस 0;

	/*
	 * If omap_device state is enabled, but has no driver bound,
	 * idle it.
	 */

	/*
	 * Some devices (like memory controllers) are always kept
	 * enabled, and should not be idled even with no drivers.
	 */
	क्रम (i = 0; i < od->hwmods_cnt; i++)
		अगर (od->hwmods[i]->flags & HWMOD_INIT_NO_IDLE)
			वापस 0;

	अगर (od->_driver_status != BUS_NOTIFY_BOUND_DRIVER &&
	    od->_driver_status != BUS_NOTIFY_BIND_DRIVER) अणु
		अगर (od->_state == OMAP_DEVICE_STATE_ENABLED) अणु
			dev_warn(dev, "%s: enabled but no driver.  Idling\n",
				 __func__);
			omap_device_idle(pdev);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init omap_device_late_init(व्योम)
अणु
	bus_क्रम_each_dev(&platक्रमm_bus_type, शून्य, शून्य, omap_device_late_idle);

	वापस 0;
पूर्ण
omap_late_initcall_sync(omap_device_late_init);
