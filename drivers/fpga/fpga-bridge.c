<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * FPGA Bridge Framework Driver
 *
 *  Copyright (C) 2013-2016 Altera Corporation, All Rights Reserved.
 *  Copyright (C) 2017 Intel Corporation
 */
#समावेश <linux/fpga/fpga-bridge.h>
#समावेश <linux/idr.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

अटल DEFINE_IDA(fpga_bridge_ida);
अटल काष्ठा class *fpga_bridge_class;

/* Lock क्रम adding/removing bridges to linked lists*/
अटल DEFINE_SPINLOCK(bridge_list_lock);

/**
 * fpga_bridge_enable - Enable transactions on the bridge
 *
 * @bridge: FPGA bridge
 *
 * Return: 0 क्रम success, error code otherwise.
 */
पूर्णांक fpga_bridge_enable(काष्ठा fpga_bridge *bridge)
अणु
	dev_dbg(&bridge->dev, "enable\n");

	अगर (bridge->br_ops && bridge->br_ops->enable_set)
		वापस bridge->br_ops->enable_set(bridge, 1);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fpga_bridge_enable);

/**
 * fpga_bridge_disable - Disable transactions on the bridge
 *
 * @bridge: FPGA bridge
 *
 * Return: 0 क्रम success, error code otherwise.
 */
पूर्णांक fpga_bridge_disable(काष्ठा fpga_bridge *bridge)
अणु
	dev_dbg(&bridge->dev, "disable\n");

	अगर (bridge->br_ops && bridge->br_ops->enable_set)
		वापस bridge->br_ops->enable_set(bridge, 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fpga_bridge_disable);

अटल काष्ठा fpga_bridge *__fpga_bridge_get(काष्ठा device *dev,
					     काष्ठा fpga_image_info *info)
अणु
	काष्ठा fpga_bridge *bridge;
	पूर्णांक ret = -ENODEV;

	bridge = to_fpga_bridge(dev);

	bridge->info = info;

	अगर (!mutex_trylock(&bridge->mutex)) अणु
		ret = -EBUSY;
		जाओ err_dev;
	पूर्ण

	अगर (!try_module_get(dev->parent->driver->owner))
		जाओ err_ll_mod;

	dev_dbg(&bridge->dev, "get\n");

	वापस bridge;

err_ll_mod:
	mutex_unlock(&bridge->mutex);
err_dev:
	put_device(dev);
	वापस ERR_PTR(ret);
पूर्ण

/**
 * of_fpga_bridge_get - get an exclusive reference to a fpga bridge
 *
 * @np: node poपूर्णांकer of a FPGA bridge
 * @info: fpga image specअगरic inक्रमmation
 *
 * Return fpga_bridge काष्ठा अगर successful.
 * Return -EBUSY अगर someone alपढ़ोy has a reference to the bridge.
 * Return -ENODEV अगर @np is not a FPGA Bridge.
 */
काष्ठा fpga_bridge *of_fpga_bridge_get(काष्ठा device_node *np,
				       काष्ठा fpga_image_info *info)
अणु
	काष्ठा device *dev;

	dev = class_find_device_by_of_node(fpga_bridge_class, np);
	अगर (!dev)
		वापस ERR_PTR(-ENODEV);

	वापस __fpga_bridge_get(dev, info);
पूर्ण
EXPORT_SYMBOL_GPL(of_fpga_bridge_get);

अटल पूर्णांक fpga_bridge_dev_match(काष्ठा device *dev, स्थिर व्योम *data)
अणु
	वापस dev->parent == data;
पूर्ण

/**
 * fpga_bridge_get - get an exclusive reference to a fpga bridge
 * @dev:	parent device that fpga bridge was रेजिस्टरed with
 * @info:	fpga manager info
 *
 * Given a device, get an exclusive reference to a fpga bridge.
 *
 * Return: fpga bridge काष्ठा or IS_ERR() condition containing error code.
 */
काष्ठा fpga_bridge *fpga_bridge_get(काष्ठा device *dev,
				    काष्ठा fpga_image_info *info)
अणु
	काष्ठा device *bridge_dev;

	bridge_dev = class_find_device(fpga_bridge_class, शून्य, dev,
				       fpga_bridge_dev_match);
	अगर (!bridge_dev)
		वापस ERR_PTR(-ENODEV);

	वापस __fpga_bridge_get(bridge_dev, info);
पूर्ण
EXPORT_SYMBOL_GPL(fpga_bridge_get);

/**
 * fpga_bridge_put - release a reference to a bridge
 *
 * @bridge: FPGA bridge
 */
व्योम fpga_bridge_put(काष्ठा fpga_bridge *bridge)
अणु
	dev_dbg(&bridge->dev, "put\n");

	bridge->info = शून्य;
	module_put(bridge->dev.parent->driver->owner);
	mutex_unlock(&bridge->mutex);
	put_device(&bridge->dev);
पूर्ण
EXPORT_SYMBOL_GPL(fpga_bridge_put);

/**
 * fpga_bridges_enable - enable bridges in a list
 * @bridge_list: list of FPGA bridges
 *
 * Enable each bridge in the list.  If list is empty, करो nothing.
 *
 * Return 0 क्रम success or empty bridge list; वापस error code otherwise.
 */
पूर्णांक fpga_bridges_enable(काष्ठा list_head *bridge_list)
अणु
	काष्ठा fpga_bridge *bridge;
	पूर्णांक ret;

	list_क्रम_each_entry(bridge, bridge_list, node) अणु
		ret = fpga_bridge_enable(bridge);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fpga_bridges_enable);

/**
 * fpga_bridges_disable - disable bridges in a list
 *
 * @bridge_list: list of FPGA bridges
 *
 * Disable each bridge in the list.  If list is empty, करो nothing.
 *
 * Return 0 क्रम success or empty bridge list; वापस error code otherwise.
 */
पूर्णांक fpga_bridges_disable(काष्ठा list_head *bridge_list)
अणु
	काष्ठा fpga_bridge *bridge;
	पूर्णांक ret;

	list_क्रम_each_entry(bridge, bridge_list, node) अणु
		ret = fpga_bridge_disable(bridge);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fpga_bridges_disable);

/**
 * fpga_bridges_put - put bridges
 *
 * @bridge_list: list of FPGA bridges
 *
 * For each bridge in the list, put the bridge and हटाओ it from the list.
 * If list is empty, करो nothing.
 */
व्योम fpga_bridges_put(काष्ठा list_head *bridge_list)
अणु
	काष्ठा fpga_bridge *bridge, *next;
	अचिन्हित दीर्घ flags;

	list_क्रम_each_entry_safe(bridge, next, bridge_list, node) अणु
		fpga_bridge_put(bridge);

		spin_lock_irqsave(&bridge_list_lock, flags);
		list_del(&bridge->node);
		spin_unlock_irqrestore(&bridge_list_lock, flags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(fpga_bridges_put);

/**
 * of_fpga_bridge_get_to_list - get a bridge, add it to a list
 *
 * @np: node poपूर्णांकer of a FPGA bridge
 * @info: fpga image specअगरic inक्रमmation
 * @bridge_list: list of FPGA bridges
 *
 * Get an exclusive reference to the bridge and and it to the list.
 *
 * Return 0 क्रम success, error code from of_fpga_bridge_get() othewise.
 */
पूर्णांक of_fpga_bridge_get_to_list(काष्ठा device_node *np,
			       काष्ठा fpga_image_info *info,
			       काष्ठा list_head *bridge_list)
अणु
	काष्ठा fpga_bridge *bridge;
	अचिन्हित दीर्घ flags;

	bridge = of_fpga_bridge_get(np, info);
	अगर (IS_ERR(bridge))
		वापस PTR_ERR(bridge);

	spin_lock_irqsave(&bridge_list_lock, flags);
	list_add(&bridge->node, bridge_list);
	spin_unlock_irqrestore(&bridge_list_lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_fpga_bridge_get_to_list);

/**
 * fpga_bridge_get_to_list - given device, get a bridge, add it to a list
 *
 * @dev: FPGA bridge device
 * @info: fpga image specअगरic inक्रमmation
 * @bridge_list: list of FPGA bridges
 *
 * Get an exclusive reference to the bridge and and it to the list.
 *
 * Return 0 क्रम success, error code from fpga_bridge_get() othewise.
 */
पूर्णांक fpga_bridge_get_to_list(काष्ठा device *dev,
			    काष्ठा fpga_image_info *info,
			    काष्ठा list_head *bridge_list)
अणु
	काष्ठा fpga_bridge *bridge;
	अचिन्हित दीर्घ flags;

	bridge = fpga_bridge_get(dev, info);
	अगर (IS_ERR(bridge))
		वापस PTR_ERR(bridge);

	spin_lock_irqsave(&bridge_list_lock, flags);
	list_add(&bridge->node, bridge_list);
	spin_unlock_irqrestore(&bridge_list_lock, flags);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fpga_bridge_get_to_list);

अटल sमाप_प्रकार name_show(काष्ठा device *dev,
			 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fpga_bridge *bridge = to_fpga_bridge(dev);

	वापस प्र_लिखो(buf, "%s\n", bridge->name);
पूर्ण

अटल sमाप_प्रकार state_show(काष्ठा device *dev,
			  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fpga_bridge *bridge = to_fpga_bridge(dev);
	पूर्णांक enable = 1;

	अगर (bridge->br_ops && bridge->br_ops->enable_show)
		enable = bridge->br_ops->enable_show(bridge);

	वापस प्र_लिखो(buf, "%s\n", enable ? "enabled" : "disabled");
पूर्ण

अटल DEVICE_ATTR_RO(name);
अटल DEVICE_ATTR_RO(state);

अटल काष्ठा attribute *fpga_bridge_attrs[] = अणु
	&dev_attr_name.attr,
	&dev_attr_state.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(fpga_bridge);

/**
 * fpga_bridge_create - create and initialize a काष्ठा fpga_bridge
 * @dev:	FPGA bridge device from pdev
 * @name:	FPGA bridge name
 * @br_ops:	poपूर्णांकer to काष्ठाure of fpga bridge ops
 * @priv:	FPGA bridge निजी data
 *
 * The caller of this function is responsible क्रम मुक्तing the bridge with
 * fpga_bridge_मुक्त().  Using devm_fpga_bridge_create() instead is recommended.
 *
 * Return: काष्ठा fpga_bridge or शून्य
 */
काष्ठा fpga_bridge *fpga_bridge_create(काष्ठा device *dev, स्थिर अक्षर *name,
				       स्थिर काष्ठा fpga_bridge_ops *br_ops,
				       व्योम *priv)
अणु
	काष्ठा fpga_bridge *bridge;
	पूर्णांक id, ret;

	अगर (!name || !म_माप(name)) अणु
		dev_err(dev, "Attempt to register with no name!\n");
		वापस शून्य;
	पूर्ण

	bridge = kzalloc(माप(*bridge), GFP_KERNEL);
	अगर (!bridge)
		वापस शून्य;

	id = ida_simple_get(&fpga_bridge_ida, 0, 0, GFP_KERNEL);
	अगर (id < 0)
		जाओ error_kमुक्त;

	mutex_init(&bridge->mutex);
	INIT_LIST_HEAD(&bridge->node);

	bridge->name = name;
	bridge->br_ops = br_ops;
	bridge->priv = priv;

	device_initialize(&bridge->dev);
	bridge->dev.groups = br_ops->groups;
	bridge->dev.class = fpga_bridge_class;
	bridge->dev.parent = dev;
	bridge->dev.of_node = dev->of_node;
	bridge->dev.id = id;

	ret = dev_set_name(&bridge->dev, "br%d", id);
	अगर (ret)
		जाओ error_device;

	वापस bridge;

error_device:
	ida_simple_हटाओ(&fpga_bridge_ida, id);
error_kमुक्त:
	kमुक्त(bridge);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(fpga_bridge_create);

/**
 * fpga_bridge_मुक्त - मुक्त a fpga bridge created by fpga_bridge_create()
 * @bridge:	FPGA bridge काष्ठा
 */
व्योम fpga_bridge_मुक्त(काष्ठा fpga_bridge *bridge)
अणु
	ida_simple_हटाओ(&fpga_bridge_ida, bridge->dev.id);
	kमुक्त(bridge);
पूर्ण
EXPORT_SYMBOL_GPL(fpga_bridge_मुक्त);

अटल व्योम devm_fpga_bridge_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा fpga_bridge *bridge = *(काष्ठा fpga_bridge **)res;

	fpga_bridge_मुक्त(bridge);
पूर्ण

/**
 * devm_fpga_bridge_create - create and init a managed काष्ठा fpga_bridge
 * @dev:	FPGA bridge device from pdev
 * @name:	FPGA bridge name
 * @br_ops:	poपूर्णांकer to काष्ठाure of fpga bridge ops
 * @priv:	FPGA bridge निजी data
 *
 * This function is पूर्णांकended क्रम use in a FPGA bridge driver's probe function.
 * After the bridge driver creates the काष्ठा with devm_fpga_bridge_create(), it
 * should रेजिस्टर the bridge with fpga_bridge_रेजिस्टर().  The bridge driver's
 * हटाओ function should call fpga_bridge_unरेजिस्टर().  The bridge काष्ठा
 * allocated with this function will be मुक्तd स्वतःmatically on driver detach.
 * This includes the हाल of a probe function वापसing error beक्रमe calling
 * fpga_bridge_रेजिस्टर(), the काष्ठा will still get cleaned up.
 *
 *  Return: काष्ठा fpga_bridge or शून्य
 */
काष्ठा fpga_bridge
*devm_fpga_bridge_create(काष्ठा device *dev, स्थिर अक्षर *name,
			 स्थिर काष्ठा fpga_bridge_ops *br_ops, व्योम *priv)
अणु
	काष्ठा fpga_bridge **ptr, *bridge;

	ptr = devres_alloc(devm_fpga_bridge_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस शून्य;

	bridge = fpga_bridge_create(dev, name, br_ops, priv);
	अगर (!bridge) अणु
		devres_मुक्त(ptr);
	पूर्ण अन्यथा अणु
		*ptr = bridge;
		devres_add(dev, ptr);
	पूर्ण

	वापस bridge;
पूर्ण
EXPORT_SYMBOL_GPL(devm_fpga_bridge_create);

/**
 * fpga_bridge_रेजिस्टर - रेजिस्टर a FPGA bridge
 *
 * @bridge: FPGA bridge काष्ठा
 *
 * Return: 0 क्रम success, error code otherwise.
 */
पूर्णांक fpga_bridge_रेजिस्टर(काष्ठा fpga_bridge *bridge)
अणु
	काष्ठा device *dev = &bridge->dev;
	पूर्णांक ret;

	ret = device_add(dev);
	अगर (ret)
		वापस ret;

	of_platक्रमm_populate(dev->of_node, शून्य, शून्य, dev);

	dev_info(dev->parent, "fpga bridge [%s] registered\n", bridge->name);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fpga_bridge_रेजिस्टर);

/**
 * fpga_bridge_unरेजिस्टर - unरेजिस्टर a FPGA bridge
 *
 * @bridge: FPGA bridge काष्ठा
 *
 * This function is पूर्णांकended क्रम use in a FPGA bridge driver's हटाओ function.
 */
व्योम fpga_bridge_unरेजिस्टर(काष्ठा fpga_bridge *bridge)
अणु
	/*
	 * If the low level driver provides a method क्रम putting bridge पूर्णांकo
	 * a desired state upon unरेजिस्टर, करो it.
	 */
	अगर (bridge->br_ops && bridge->br_ops->fpga_bridge_हटाओ)
		bridge->br_ops->fpga_bridge_हटाओ(bridge);

	device_unरेजिस्टर(&bridge->dev);
पूर्ण
EXPORT_SYMBOL_GPL(fpga_bridge_unरेजिस्टर);

अटल व्योम fpga_bridge_dev_release(काष्ठा device *dev)
अणु
पूर्ण

अटल पूर्णांक __init fpga_bridge_dev_init(व्योम)
अणु
	fpga_bridge_class = class_create(THIS_MODULE, "fpga_bridge");
	अगर (IS_ERR(fpga_bridge_class))
		वापस PTR_ERR(fpga_bridge_class);

	fpga_bridge_class->dev_groups = fpga_bridge_groups;
	fpga_bridge_class->dev_release = fpga_bridge_dev_release;

	वापस 0;
पूर्ण

अटल व्योम __निकास fpga_bridge_dev_निकास(व्योम)
अणु
	class_destroy(fpga_bridge_class);
	ida_destroy(&fpga_bridge_ida);
पूर्ण

MODULE_DESCRIPTION("FPGA Bridge Driver");
MODULE_AUTHOR("Alan Tull <atull@kernel.org>");
MODULE_LICENSE("GPL v2");

subsys_initcall(fpga_bridge_dev_init);
module_निकास(fpga_bridge_dev_निकास);
