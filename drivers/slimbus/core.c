<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2011-2017, The Linux Foundation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/idr.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slimbus.h>
#समावेश "slimbus.h"

अटल DEFINE_IDA(ctrl_ida);

अटल स्थिर काष्ठा slim_device_id *slim_match(स्थिर काष्ठा slim_device_id *id,
					       स्थिर काष्ठा slim_device *sbdev)
अणु
	जबतक (id->manf_id != 0 || id->prod_code != 0) अणु
		अगर (id->manf_id == sbdev->e_addr.manf_id &&
		    id->prod_code == sbdev->e_addr.prod_code &&
		    id->dev_index == sbdev->e_addr.dev_index &&
		    id->instance == sbdev->e_addr.instance)
			वापस id;
		id++;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक slim_device_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा slim_device *sbdev = to_slim_device(dev);
	काष्ठा slim_driver *sbdrv = to_slim_driver(drv);

	/* Attempt an OF style match first */
	अगर (of_driver_match_device(dev, drv))
		वापस 1;

	वापस !!slim_match(sbdrv->id_table, sbdev);
पूर्ण

अटल व्योम slim_device_update_status(काष्ठा slim_device *sbdev,
				      क्रमागत slim_device_status status)
अणु
	काष्ठा slim_driver *sbdrv;

	अगर (sbdev->status == status)
		वापस;

	sbdev->status = status;
	अगर (!sbdev->dev.driver)
		वापस;

	sbdrv = to_slim_driver(sbdev->dev.driver);
	अगर (sbdrv->device_status)
		sbdrv->device_status(sbdev, sbdev->status);
पूर्ण

अटल पूर्णांक slim_device_probe(काष्ठा device *dev)
अणु
	काष्ठा slim_device	*sbdev = to_slim_device(dev);
	काष्ठा slim_driver	*sbdrv = to_slim_driver(dev->driver);
	पूर्णांक ret;

	ret = sbdrv->probe(sbdev);
	अगर (ret)
		वापस ret;

	/* try getting the logical address after probe */
	ret = slim_get_logical_addr(sbdev);
	अगर (!ret) अणु
		slim_device_update_status(sbdev, SLIM_DEVICE_STATUS_UP);
	पूर्ण अन्यथा अणु
		dev_err(&sbdev->dev, "Failed to get logical address\n");
		ret = -EPROBE_DEFER;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक slim_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा slim_device *sbdev = to_slim_device(dev);
	काष्ठा slim_driver *sbdrv;

	अगर (dev->driver) अणु
		sbdrv = to_slim_driver(dev->driver);
		अगर (sbdrv->हटाओ)
			sbdrv->हटाओ(sbdev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक slim_device_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	काष्ठा slim_device *sbdev = to_slim_device(dev);

	वापस add_uevent_var(env, "MODALIAS=slim:%s", dev_name(&sbdev->dev));
पूर्ण

काष्ठा bus_type slimbus_bus = अणु
	.name		= "slimbus",
	.match		= slim_device_match,
	.probe		= slim_device_probe,
	.हटाओ		= slim_device_हटाओ,
	.uevent		= slim_device_uevent,
पूर्ण;
EXPORT_SYMBOL_GPL(slimbus_bus);

/*
 * __slim_driver_रेजिस्टर() - Client driver registration with SLIMbus
 *
 * @drv:Client driver to be associated with client-device.
 * @owner: owning module/driver
 *
 * This API will रेजिस्टर the client driver with the SLIMbus
 * It is called from the driver's module-init function.
 */
पूर्णांक __slim_driver_रेजिस्टर(काष्ठा slim_driver *drv, काष्ठा module *owner)
अणु
	/* ID table and probe are mandatory */
	अगर (!(drv->driver.of_match_table || drv->id_table) || !drv->probe)
		वापस -EINVAL;

	drv->driver.bus = &slimbus_bus;
	drv->driver.owner = owner;

	वापस driver_रेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(__slim_driver_रेजिस्टर);

/*
 * slim_driver_unरेजिस्टर() - Unकरो effect of slim_driver_रेजिस्टर
 *
 * @drv: Client driver to be unरेजिस्टरed
 */
व्योम slim_driver_unरेजिस्टर(काष्ठा slim_driver *drv)
अणु
	driver_unरेजिस्टर(&drv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(slim_driver_unरेजिस्टर);

अटल व्योम slim_dev_release(काष्ठा device *dev)
अणु
	काष्ठा slim_device *sbdev = to_slim_device(dev);

	kमुक्त(sbdev);
पूर्ण

अटल पूर्णांक slim_add_device(काष्ठा slim_controller *ctrl,
			   काष्ठा slim_device *sbdev,
			   काष्ठा device_node *node)
अणु
	sbdev->dev.bus = &slimbus_bus;
	sbdev->dev.parent = ctrl->dev;
	sbdev->dev.release = slim_dev_release;
	sbdev->dev.driver = शून्य;
	sbdev->ctrl = ctrl;
	INIT_LIST_HEAD(&sbdev->stream_list);
	spin_lock_init(&sbdev->stream_list_lock);
	sbdev->dev.of_node = of_node_get(node);
	sbdev->dev.fwnode = of_fwnode_handle(node);

	dev_set_name(&sbdev->dev, "%x:%x:%x:%x",
				  sbdev->e_addr.manf_id,
				  sbdev->e_addr.prod_code,
				  sbdev->e_addr.dev_index,
				  sbdev->e_addr.instance);

	वापस device_रेजिस्टर(&sbdev->dev);
पूर्ण

अटल काष्ठा slim_device *slim_alloc_device(काष्ठा slim_controller *ctrl,
					     काष्ठा slim_eaddr *eaddr,
					     काष्ठा device_node *node)
अणु
	काष्ठा slim_device *sbdev;
	पूर्णांक ret;

	sbdev = kzalloc(माप(*sbdev), GFP_KERNEL);
	अगर (!sbdev)
		वापस शून्य;

	sbdev->e_addr = *eaddr;
	ret = slim_add_device(ctrl, sbdev, node);
	अगर (ret) अणु
		put_device(&sbdev->dev);
		वापस शून्य;
	पूर्ण

	वापस sbdev;
पूर्ण

अटल व्योम of_रेजिस्टर_slim_devices(काष्ठा slim_controller *ctrl)
अणु
	काष्ठा device *dev = ctrl->dev;
	काष्ठा device_node *node;

	अगर (!ctrl->dev->of_node)
		वापस;

	क्रम_each_child_of_node(ctrl->dev->of_node, node) अणु
		काष्ठा slim_device *sbdev;
		काष्ठा slim_eaddr e_addr;
		स्थिर अक्षर *compat = शून्य;
		पूर्णांक reg[2], ret;
		पूर्णांक manf_id, prod_code;

		compat = of_get_property(node, "compatible", शून्य);
		अगर (!compat)
			जारी;

		ret = माला_पूछो(compat, "slim%x,%x", &manf_id, &prod_code);
		अगर (ret != 2) अणु
			dev_err(dev, "Manf ID & Product code not found %s\n",
				compat);
			जारी;
		पूर्ण

		ret = of_property_पढ़ो_u32_array(node, "reg", reg, 2);
		अगर (ret) अणु
			dev_err(dev, "Device and Instance id not found:%d\n",
				ret);
			जारी;
		पूर्ण

		e_addr.dev_index = reg[0];
		e_addr.instance = reg[1];
		e_addr.manf_id = manf_id;
		e_addr.prod_code = prod_code;

		sbdev = slim_alloc_device(ctrl, &e_addr, node);
		अगर (!sbdev)
			जारी;
	पूर्ण
पूर्ण

/*
 * slim_रेजिस्टर_controller() - Controller bring-up and registration.
 *
 * @ctrl: Controller to be रेजिस्टरed.
 *
 * A controller is रेजिस्टरed with the framework using this API.
 * If devices on a controller were रेजिस्टरed beक्रमe controller,
 * this will make sure that they get probed when controller is up
 */
पूर्णांक slim_रेजिस्टर_controller(काष्ठा slim_controller *ctrl)
अणु
	पूर्णांक id;

	id = ida_simple_get(&ctrl_ida, 0, 0, GFP_KERNEL);
	अगर (id < 0)
		वापस id;

	ctrl->id = id;

	अगर (!ctrl->min_cg)
		ctrl->min_cg = SLIM_MIN_CLK_GEAR;
	अगर (!ctrl->max_cg)
		ctrl->max_cg = SLIM_MAX_CLK_GEAR;

	ida_init(&ctrl->laddr_ida);
	idr_init(&ctrl->tid_idr);
	mutex_init(&ctrl->lock);
	mutex_init(&ctrl->sched.m_reconf);
	init_completion(&ctrl->sched.छोड़ो_comp);
	spin_lock_init(&ctrl->txn_lock);

	dev_dbg(ctrl->dev, "Bus [%s] registered:dev:%p\n",
		ctrl->name, ctrl->dev);

	of_रेजिस्टर_slim_devices(ctrl);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(slim_रेजिस्टर_controller);

/* slim_हटाओ_device: Remove the effect of slim_add_device() */
अटल व्योम slim_हटाओ_device(काष्ठा slim_device *sbdev)
अणु
	of_node_put(sbdev->dev.of_node);
	device_unरेजिस्टर(&sbdev->dev);
पूर्ण

अटल पूर्णांक slim_ctrl_हटाओ_device(काष्ठा device *dev, व्योम *null)
अणु
	slim_हटाओ_device(to_slim_device(dev));
	वापस 0;
पूर्ण

/**
 * slim_unरेजिस्टर_controller() - Controller tear-करोwn.
 *
 * @ctrl: Controller to tear-करोwn.
 */
पूर्णांक slim_unरेजिस्टर_controller(काष्ठा slim_controller *ctrl)
अणु
	/* Remove all clients */
	device_क्रम_each_child(ctrl->dev, शून्य, slim_ctrl_हटाओ_device);
	ida_simple_हटाओ(&ctrl_ida, ctrl->id);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(slim_unरेजिस्टर_controller);

/**
 * slim_report_असलent() - Controller calls this function when a device
 *	reports असलent, OR when the device cannot be communicated with
 *
 * @sbdev: Device that cannot be reached, or sent report असलent
 */
व्योम slim_report_असलent(काष्ठा slim_device *sbdev)
अणु
	काष्ठा slim_controller *ctrl = sbdev->ctrl;

	अगर (!ctrl)
		वापस;

	/* invalidate logical addresses */
	mutex_lock(&ctrl->lock);
	sbdev->is_laddr_valid = false;
	mutex_unlock(&ctrl->lock);
	अगर (!ctrl->get_laddr)
		ida_simple_हटाओ(&ctrl->laddr_ida, sbdev->laddr);
	slim_device_update_status(sbdev, SLIM_DEVICE_STATUS_DOWN);
पूर्ण
EXPORT_SYMBOL_GPL(slim_report_असलent);

अटल bool slim_eaddr_equal(काष्ठा slim_eaddr *a, काष्ठा slim_eaddr *b)
अणु
	वापस (a->manf_id == b->manf_id &&
		a->prod_code == b->prod_code &&
		a->dev_index == b->dev_index &&
		a->instance == b->instance);
पूर्ण

अटल पूर्णांक slim_match_dev(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा slim_eaddr *e_addr = data;
	काष्ठा slim_device *sbdev = to_slim_device(dev);

	वापस slim_eaddr_equal(&sbdev->e_addr, e_addr);
पूर्ण

अटल काष्ठा slim_device *find_slim_device(काष्ठा slim_controller *ctrl,
					    काष्ठा slim_eaddr *eaddr)
अणु
	काष्ठा slim_device *sbdev;
	काष्ठा device *dev;

	dev = device_find_child(ctrl->dev, eaddr, slim_match_dev);
	अगर (dev) अणु
		sbdev = to_slim_device(dev);
		वापस sbdev;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * slim_get_device() - get handle to a device.
 *
 * @ctrl: Controller on which this device will be added/queried
 * @e_addr: Enumeration address of the device to be queried
 *
 * Return: poपूर्णांकer to a device अगर it has alपढ़ोy reported. Creates a new
 * device and वापसs poपूर्णांकer to it अगर the device has not yet क्रमागतerated.
 */
काष्ठा slim_device *slim_get_device(काष्ठा slim_controller *ctrl,
				    काष्ठा slim_eaddr *e_addr)
अणु
	काष्ठा slim_device *sbdev;

	sbdev = find_slim_device(ctrl, e_addr);
	अगर (!sbdev) अणु
		sbdev = slim_alloc_device(ctrl, e_addr, शून्य);
		अगर (!sbdev)
			वापस ERR_PTR(-ENOMEM);
	पूर्ण

	वापस sbdev;
पूर्ण
EXPORT_SYMBOL_GPL(slim_get_device);

अटल पूर्णांक of_slim_match_dev(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा device_node *np = data;
	काष्ठा slim_device *sbdev = to_slim_device(dev);

	वापस (sbdev->dev.of_node == np);
पूर्ण

अटल काष्ठा slim_device *of_find_slim_device(काष्ठा slim_controller *ctrl,
					       काष्ठा device_node *np)
अणु
	काष्ठा slim_device *sbdev;
	काष्ठा device *dev;

	dev = device_find_child(ctrl->dev, np, of_slim_match_dev);
	अगर (dev) अणु
		sbdev = to_slim_device(dev);
		वापस sbdev;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * of_slim_get_device() - get handle to a device using dt node.
 *
 * @ctrl: Controller on which this device will be added/queried
 * @np: node poपूर्णांकer to device
 *
 * Return: poपूर्णांकer to a device अगर it has alपढ़ोy reported. Creates a new
 * device and वापसs poपूर्णांकer to it अगर the device has not yet क्रमागतerated.
 */
काष्ठा slim_device *of_slim_get_device(काष्ठा slim_controller *ctrl,
				       काष्ठा device_node *np)
अणु
	वापस of_find_slim_device(ctrl, np);
पूर्ण
EXPORT_SYMBOL_GPL(of_slim_get_device);

अटल पूर्णांक slim_device_alloc_laddr(काष्ठा slim_device *sbdev,
				   bool report_present)
अणु
	काष्ठा slim_controller *ctrl = sbdev->ctrl;
	u8 laddr;
	पूर्णांक ret;

	mutex_lock(&ctrl->lock);
	अगर (ctrl->get_laddr) अणु
		ret = ctrl->get_laddr(ctrl, &sbdev->e_addr, &laddr);
		अगर (ret < 0)
			जाओ err;
	पूर्ण अन्यथा अगर (report_present) अणु
		ret = ida_simple_get(&ctrl->laddr_ida,
				     0, SLIM_LA_MANAGER - 1, GFP_KERNEL);
		अगर (ret < 0)
			जाओ err;

		laddr = ret;
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	अगर (ctrl->set_laddr) अणु
		ret = ctrl->set_laddr(ctrl, &sbdev->e_addr, laddr);
		अगर (ret) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण
	पूर्ण

	sbdev->laddr = laddr;
	sbdev->is_laddr_valid = true;
	mutex_unlock(&ctrl->lock);

	slim_device_update_status(sbdev, SLIM_DEVICE_STATUS_UP);

	dev_dbg(ctrl->dev, "setting slimbus l-addr:%x, ea:%x,%x,%x,%x\n",
		laddr, sbdev->e_addr.manf_id, sbdev->e_addr.prod_code,
		sbdev->e_addr.dev_index, sbdev->e_addr.instance);

	वापस 0;

err:
	mutex_unlock(&ctrl->lock);
	वापस ret;

पूर्ण

/**
 * slim_device_report_present() - Report क्रमागतerated device.
 *
 * @ctrl: Controller with which device is क्रमागतerated.
 * @e_addr: Enumeration address of the device.
 * @laddr: Return logical address (अगर valid flag is false)
 *
 * Called by controller in response to REPORT_PRESENT. Framework will assign
 * a logical address to this क्रमागतeration address.
 * Function वापसs -EXFULL to indicate that all logical addresses are alपढ़ोy
 * taken.
 */
पूर्णांक slim_device_report_present(काष्ठा slim_controller *ctrl,
			       काष्ठा slim_eaddr *e_addr, u8 *laddr)
अणु
	काष्ठा slim_device *sbdev;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(ctrl->dev);

	अगर (ctrl->sched.clk_state != SLIM_CLK_ACTIVE) अणु
		dev_err(ctrl->dev, "slim ctrl not active,state:%d, ret:%d\n",
				    ctrl->sched.clk_state, ret);
		जाओ slimbus_not_active;
	पूर्ण

	sbdev = slim_get_device(ctrl, e_addr);
	अगर (IS_ERR(sbdev))
		वापस -ENODEV;

	अगर (sbdev->is_laddr_valid) अणु
		*laddr = sbdev->laddr;
		वापस 0;
	पूर्ण

	ret = slim_device_alloc_laddr(sbdev, true);

slimbus_not_active:
	pm_runसमय_mark_last_busy(ctrl->dev);
	pm_runसमय_put_स्वतःsuspend(ctrl->dev);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(slim_device_report_present);

/**
 * slim_get_logical_addr() - get/allocate logical address of a SLIMbus device.
 *
 * @sbdev: client handle requesting the address.
 *
 * Return: zero अगर a logical address is valid or a new logical address
 * has been asचिन्हित. error code in हाल of error.
 */
पूर्णांक slim_get_logical_addr(काष्ठा slim_device *sbdev)
अणु
	अगर (!sbdev->is_laddr_valid)
		वापस slim_device_alloc_laddr(sbdev, false);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(slim_get_logical_addr);

अटल व्योम __निकास slimbus_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&slimbus_bus);
पूर्ण
module_निकास(slimbus_निकास);

अटल पूर्णांक __init slimbus_init(व्योम)
अणु
	वापस bus_रेजिस्टर(&slimbus_bus);
पूर्ण
postcore_initcall(slimbus_init);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("SLIMbus core");
