<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * devfreq-event: a framework to provide raw data and events of devfreq devices
 *
 * Copyright (C) 2015 Samsung Electronics
 * Author: Chanwoo Choi <cw00.choi@samsung.com>
 *
 * This driver is based on drivers/devfreq/devfreq.c.
 */

#समावेश <linux/devfreq-event.h>
#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/of.h>

अटल काष्ठा class *devfreq_event_class;

/* The list of all devfreq event list */
अटल LIST_HEAD(devfreq_event_list);
अटल DEFINE_MUTEX(devfreq_event_list_lock);

#घोषणा to_devfreq_event(DEV) container_of(DEV, काष्ठा devfreq_event_dev, dev)

/**
 * devfreq_event_enable_edev() - Enable the devfreq-event dev and increase
 *				 the enable_count of devfreq-event dev.
 * @edev	: the devfreq-event device
 *
 * Note that this function increase the enable_count and enable the
 * devfreq-event device. The devfreq-event device should be enabled beक्रमe
 * using it by devfreq device.
 */
पूर्णांक devfreq_event_enable_edev(काष्ठा devfreq_event_dev *edev)
अणु
	पूर्णांक ret = 0;

	अगर (!edev || !edev->desc)
		वापस -EINVAL;

	mutex_lock(&edev->lock);
	अगर (edev->desc->ops && edev->desc->ops->enable
			&& edev->enable_count == 0) अणु
		ret = edev->desc->ops->enable(edev);
		अगर (ret < 0)
			जाओ err;
	पूर्ण
	edev->enable_count++;
err:
	mutex_unlock(&edev->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devfreq_event_enable_edev);

/**
 * devfreq_event_disable_edev() - Disable the devfreq-event dev and decrease
 *				  the enable_count of the devfreq-event dev.
 * @edev	: the devfreq-event device
 *
 * Note that this function decrease the enable_count and disable the
 * devfreq-event device. After the devfreq-event device is disabled,
 * devfreq device can't use the devfreq-event device क्रम get/set/reset
 * operations.
 */
पूर्णांक devfreq_event_disable_edev(काष्ठा devfreq_event_dev *edev)
अणु
	पूर्णांक ret = 0;

	अगर (!edev || !edev->desc)
		वापस -EINVAL;

	mutex_lock(&edev->lock);
	अगर (edev->enable_count <= 0) अणु
		dev_warn(&edev->dev, "unbalanced enable_count\n");
		ret = -EIO;
		जाओ err;
	पूर्ण

	अगर (edev->desc->ops && edev->desc->ops->disable
			&& edev->enable_count == 1) अणु
		ret = edev->desc->ops->disable(edev);
		अगर (ret < 0)
			जाओ err;
	पूर्ण
	edev->enable_count--;
err:
	mutex_unlock(&edev->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devfreq_event_disable_edev);

/**
 * devfreq_event_is_enabled() - Check whether devfreq-event dev is enabled or
 *				not.
 * @edev	: the devfreq-event device
 *
 * Note that this function check whether devfreq-event dev is enabled or not.
 * If वापस true, the devfreq-event dev is enabeld. If वापस false, the
 * devfreq-event dev is disabled.
 */
bool devfreq_event_is_enabled(काष्ठा devfreq_event_dev *edev)
अणु
	bool enabled = false;

	अगर (!edev || !edev->desc)
		वापस enabled;

	mutex_lock(&edev->lock);

	अगर (edev->enable_count > 0)
		enabled = true;

	mutex_unlock(&edev->lock);

	वापस enabled;
पूर्ण
EXPORT_SYMBOL_GPL(devfreq_event_is_enabled);

/**
 * devfreq_event_set_event() - Set event to devfreq-event dev to start.
 * @edev	: the devfreq-event device
 *
 * Note that this function set the event to the devfreq-event device to start
 * क्रम getting the event data which could be various event type.
 */
पूर्णांक devfreq_event_set_event(काष्ठा devfreq_event_dev *edev)
अणु
	पूर्णांक ret;

	अगर (!edev || !edev->desc)
		वापस -EINVAL;

	अगर (!edev->desc->ops || !edev->desc->ops->set_event)
		वापस -EINVAL;

	अगर (!devfreq_event_is_enabled(edev))
		वापस -EPERM;

	mutex_lock(&edev->lock);
	ret = edev->desc->ops->set_event(edev);
	mutex_unlock(&edev->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devfreq_event_set_event);

/**
 * devfreq_event_get_event() - Get अणुload|totalपूर्ण_count from devfreq-event dev.
 * @edev	: the devfreq-event device
 * @edata	: the calculated data of devfreq-event device
 *
 * Note that this function get the calculated event data from devfreq-event dev
 * after stoping the progress of whole sequence of devfreq-event dev.
 */
पूर्णांक devfreq_event_get_event(काष्ठा devfreq_event_dev *edev,
			    काष्ठा devfreq_event_data *edata)
अणु
	पूर्णांक ret;

	अगर (!edev || !edev->desc)
		वापस -EINVAL;

	अगर (!edev->desc->ops || !edev->desc->ops->get_event)
		वापस -EINVAL;

	अगर (!devfreq_event_is_enabled(edev))
		वापस -EINVAL;

	edata->total_count = edata->load_count = 0;

	mutex_lock(&edev->lock);
	ret = edev->desc->ops->get_event(edev, edata);
	अगर (ret < 0)
		edata->total_count = edata->load_count = 0;
	mutex_unlock(&edev->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devfreq_event_get_event);

/**
 * devfreq_event_reset_event() - Reset all opeations of devfreq-event dev.
 * @edev	: the devfreq-event device
 *
 * Note that this function stop all operations of devfreq-event dev and reset
 * the current event data to make the devfreq-event device पूर्णांकo initial state.
 */
पूर्णांक devfreq_event_reset_event(काष्ठा devfreq_event_dev *edev)
अणु
	पूर्णांक ret = 0;

	अगर (!edev || !edev->desc)
		वापस -EINVAL;

	अगर (!devfreq_event_is_enabled(edev))
		वापस -EPERM;

	mutex_lock(&edev->lock);
	अगर (edev->desc->ops && edev->desc->ops->reset)
		ret = edev->desc->ops->reset(edev);
	mutex_unlock(&edev->lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devfreq_event_reset_event);

/**
 * devfreq_event_get_edev_by_phandle() - Get the devfreq-event dev from
 *					 devicetree.
 * @dev		: the poपूर्णांकer to the given device
 * @phandle_name: name of property holding a phandle value
 * @index	: the index पूर्णांकo list of devfreq-event device
 *
 * Note that this function वापस the poपूर्णांकer of devfreq-event device.
 */
काष्ठा devfreq_event_dev *devfreq_event_get_edev_by_phandle(काष्ठा device *dev,
					स्थिर अक्षर *phandle_name, पूर्णांक index)
अणु
	काष्ठा device_node *node;
	काष्ठा devfreq_event_dev *edev;

	अगर (!dev->of_node || !phandle_name)
		वापस ERR_PTR(-EINVAL);

	node = of_parse_phandle(dev->of_node, phandle_name, index);
	अगर (!node)
		वापस ERR_PTR(-ENODEV);

	mutex_lock(&devfreq_event_list_lock);
	list_क्रम_each_entry(edev, &devfreq_event_list, node) अणु
		अगर (edev->dev.parent && edev->dev.parent->of_node == node)
			जाओ out;
	पूर्ण

	list_क्रम_each_entry(edev, &devfreq_event_list, node) अणु
		अगर (of_node_name_eq(node, edev->desc->name))
			जाओ out;
	पूर्ण
	edev = शून्य;
out:
	mutex_unlock(&devfreq_event_list_lock);

	अगर (!edev) अणु
		of_node_put(node);
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	of_node_put(node);

	वापस edev;
पूर्ण
EXPORT_SYMBOL_GPL(devfreq_event_get_edev_by_phandle);

/**
 * devfreq_event_get_edev_count() - Get the count of devfreq-event dev
 * @dev		: the poपूर्णांकer to the given device
 * @phandle_name: name of property holding a phandle value
 *
 * Note that this function वापस the count of devfreq-event devices.
 */
पूर्णांक devfreq_event_get_edev_count(काष्ठा device *dev, स्थिर अक्षर *phandle_name)
अणु
	पूर्णांक count;

	अगर (!dev->of_node || !phandle_name) अणु
		dev_err(dev, "device does not have a device node entry\n");
		वापस -EINVAL;
	पूर्ण

	count = of_property_count_elems_of_size(dev->of_node, phandle_name,
						माप(u32));
	अगर (count < 0) अणु
		dev_err(dev,
			"failed to get the count of devfreq-event in %pOF node\n",
			dev->of_node);
		वापस count;
	पूर्ण

	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(devfreq_event_get_edev_count);

अटल व्योम devfreq_event_release_edev(काष्ठा device *dev)
अणु
	काष्ठा devfreq_event_dev *edev = to_devfreq_event(dev);

	kमुक्त(edev);
पूर्ण

/**
 * devfreq_event_add_edev() - Add new devfreq-event device.
 * @dev		: the device owning the devfreq-event device being created
 * @desc	: the devfreq-event device's descriptor which include essential
 *		  data क्रम devfreq-event device.
 *
 * Note that this function add new devfreq-event device to devfreq-event class
 * list and रेजिस्टर the device of the devfreq-event device.
 */
काष्ठा devfreq_event_dev *devfreq_event_add_edev(काष्ठा device *dev,
						काष्ठा devfreq_event_desc *desc)
अणु
	काष्ठा devfreq_event_dev *edev;
	अटल atomic_t event_no = ATOMIC_INIT(-1);
	पूर्णांक ret;

	अगर (!dev || !desc)
		वापस ERR_PTR(-EINVAL);

	अगर (!desc->name || !desc->ops)
		वापस ERR_PTR(-EINVAL);

	अगर (!desc->ops->set_event || !desc->ops->get_event)
		वापस ERR_PTR(-EINVAL);

	edev = kzalloc(माप(काष्ठा devfreq_event_dev), GFP_KERNEL);
	अगर (!edev)
		वापस ERR_PTR(-ENOMEM);

	mutex_init(&edev->lock);
	edev->desc = desc;
	edev->enable_count = 0;
	edev->dev.parent = dev;
	edev->dev.class = devfreq_event_class;
	edev->dev.release = devfreq_event_release_edev;

	dev_set_name(&edev->dev, "event%d", atomic_inc_वापस(&event_no));
	ret = device_रेजिस्टर(&edev->dev);
	अगर (ret < 0) अणु
		put_device(&edev->dev);
		वापस ERR_PTR(ret);
	पूर्ण
	dev_set_drvdata(&edev->dev, edev);

	INIT_LIST_HEAD(&edev->node);

	mutex_lock(&devfreq_event_list_lock);
	list_add(&edev->node, &devfreq_event_list);
	mutex_unlock(&devfreq_event_list_lock);

	वापस edev;
पूर्ण
EXPORT_SYMBOL_GPL(devfreq_event_add_edev);

/**
 * devfreq_event_हटाओ_edev() - Remove the devfreq-event device रेजिस्टरed.
 * @edev	: the devfreq-event device
 *
 * Note that this function हटाओs the रेजिस्टरed devfreq-event device.
 */
पूर्णांक devfreq_event_हटाओ_edev(काष्ठा devfreq_event_dev *edev)
अणु
	अगर (!edev)
		वापस -EINVAL;

	WARN_ON(edev->enable_count);

	mutex_lock(&devfreq_event_list_lock);
	list_del(&edev->node);
	mutex_unlock(&devfreq_event_list_lock);

	device_unरेजिस्टर(&edev->dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devfreq_event_हटाओ_edev);

अटल पूर्णांक devm_devfreq_event_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा devfreq_event_dev **r = res;

	अगर (WARN_ON(!r || !*r))
		वापस 0;

	वापस *r == data;
पूर्ण

अटल व्योम devm_devfreq_event_release(काष्ठा device *dev, व्योम *res)
अणु
	devfreq_event_हटाओ_edev(*(काष्ठा devfreq_event_dev **)res);
पूर्ण

/**
 * devm_devfreq_event_add_edev() - Resource-managed devfreq_event_add_edev()
 * @dev		: the device owning the devfreq-event device being created
 * @desc	: the devfreq-event device's descriptor which include essential
 *		  data क्रम devfreq-event device.
 *
 * Note that this function manages स्वतःmatically the memory of devfreq-event
 * device using device resource management and simplअगरy the मुक्त operation
 * क्रम memory of devfreq-event device.
 */
काष्ठा devfreq_event_dev *devm_devfreq_event_add_edev(काष्ठा device *dev,
						काष्ठा devfreq_event_desc *desc)
अणु
	काष्ठा devfreq_event_dev **ptr, *edev;

	ptr = devres_alloc(devm_devfreq_event_release, माप(*ptr),
				GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	edev = devfreq_event_add_edev(dev, desc);
	अगर (IS_ERR(edev)) अणु
		devres_मुक्त(ptr);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	*ptr = edev;
	devres_add(dev, ptr);

	वापस edev;
पूर्ण
EXPORT_SYMBOL_GPL(devm_devfreq_event_add_edev);

/**
 * devm_devfreq_event_हटाओ_edev()- Resource-managed devfreq_event_हटाओ_edev()
 * @dev		: the device owning the devfreq-event device being created
 * @edev	: the devfreq-event device
 *
 * Note that this function manages स्वतःmatically the memory of devfreq-event
 * device using device resource management.
 */
व्योम devm_devfreq_event_हटाओ_edev(काष्ठा device *dev,
				काष्ठा devfreq_event_dev *edev)
अणु
	WARN_ON(devres_release(dev, devm_devfreq_event_release,
			       devm_devfreq_event_match, edev));
पूर्ण
EXPORT_SYMBOL_GPL(devm_devfreq_event_हटाओ_edev);

/*
 * Device attributes क्रम devfreq-event class.
 */
अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा devfreq_event_dev *edev = to_devfreq_event(dev);

	अगर (!edev || !edev->desc)
		वापस -EINVAL;

	वापस प्र_लिखो(buf, "%s\n", edev->desc->name);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल sमाप_प्रकार enable_count_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा devfreq_event_dev *edev = to_devfreq_event(dev);

	अगर (!edev || !edev->desc)
		वापस -EINVAL;

	वापस प्र_लिखो(buf, "%d\n", edev->enable_count);
पूर्ण
अटल DEVICE_ATTR_RO(enable_count);

अटल काष्ठा attribute *devfreq_event_attrs[] = अणु
	&dev_attr_name.attr,
	&dev_attr_enable_count.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(devfreq_event);

अटल पूर्णांक __init devfreq_event_init(व्योम)
अणु
	devfreq_event_class = class_create(THIS_MODULE, "devfreq-event");
	अगर (IS_ERR(devfreq_event_class)) अणु
		pr_err("%s: couldn't create class\n", __खाता__);
		वापस PTR_ERR(devfreq_event_class);
	पूर्ण

	devfreq_event_class->dev_groups = devfreq_event_groups;

	वापस 0;
पूर्ण
subsys_initcall(devfreq_event_init);
