<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2016-2017 Linaro Ltd., Rob Herring <robh@kernel.org>
 *
 * Based on drivers/spmi/spmi.c:
 * Copyright (c) 2012-2015, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/idr.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sched.h>
#समावेश <linux/serdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_data/x86/apple.h>

अटल bool is_रेजिस्टरed;
अटल DEFINE_IDA(ctrl_ida);

अटल sमाप_प्रकार modalias_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक len;

	len = acpi_device_modalias(dev, buf, PAGE_SIZE - 1);
	अगर (len != -ENODEV)
		वापस len;

	वापस of_device_modalias(dev, buf, PAGE_SIZE);
पूर्ण
अटल DEVICE_ATTR_RO(modalias);

अटल काष्ठा attribute *serdev_device_attrs[] = अणु
	&dev_attr_modalias.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(serdev_device);

अटल पूर्णांक serdev_device_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	पूर्णांक rc;

	/* TODO: platक्रमm modalias */

	rc = acpi_device_uevent_modalias(dev, env);
	अगर (rc != -ENODEV)
		वापस rc;

	वापस of_device_uevent_modalias(dev, env);
पूर्ण

अटल व्योम serdev_device_release(काष्ठा device *dev)
अणु
	काष्ठा serdev_device *serdev = to_serdev_device(dev);
	kमुक्त(serdev);
पूर्ण

अटल स्थिर काष्ठा device_type serdev_device_type = अणु
	.groups		= serdev_device_groups,
	.uevent		= serdev_device_uevent,
	.release	= serdev_device_release,
पूर्ण;

अटल bool is_serdev_device(स्थिर काष्ठा device *dev)
अणु
	वापस dev->type == &serdev_device_type;
पूर्ण

अटल व्योम serdev_ctrl_release(काष्ठा device *dev)
अणु
	काष्ठा serdev_controller *ctrl = to_serdev_controller(dev);
	ida_simple_हटाओ(&ctrl_ida, ctrl->nr);
	kमुक्त(ctrl);
पूर्ण

अटल स्थिर काष्ठा device_type serdev_ctrl_type = अणु
	.release	= serdev_ctrl_release,
पूर्ण;

अटल पूर्णांक serdev_device_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	अगर (!is_serdev_device(dev))
		वापस 0;

	/* TODO: platक्रमm matching */
	अगर (acpi_driver_match_device(dev, drv))
		वापस 1;

	वापस of_driver_match_device(dev, drv);
पूर्ण

/**
 * serdev_device_add() - add a device previously स्थिरructed via serdev_device_alloc()
 * @serdev:	serdev_device to be added
 */
पूर्णांक serdev_device_add(काष्ठा serdev_device *serdev)
अणु
	काष्ठा serdev_controller *ctrl = serdev->ctrl;
	काष्ठा device *parent = serdev->dev.parent;
	पूर्णांक err;

	dev_set_name(&serdev->dev, "%s-%d", dev_name(parent), serdev->nr);

	/* Only a single slave device is currently supported. */
	अगर (ctrl->serdev) अणु
		dev_err(&serdev->dev, "controller busy\n");
		वापस -EBUSY;
	पूर्ण
	ctrl->serdev = serdev;

	err = device_add(&serdev->dev);
	अगर (err < 0) अणु
		dev_err(&serdev->dev, "Can't add %s, status %pe\n",
			dev_name(&serdev->dev), ERR_PTR(err));
		जाओ err_clear_serdev;
	पूर्ण

	dev_dbg(&serdev->dev, "device %s registered\n", dev_name(&serdev->dev));

	वापस 0;

err_clear_serdev:
	ctrl->serdev = शून्य;
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(serdev_device_add);

/**
 * serdev_device_हटाओ(): हटाओ an serdev device
 * @serdev:	serdev_device to be हटाओd
 */
व्योम serdev_device_हटाओ(काष्ठा serdev_device *serdev)
अणु
	काष्ठा serdev_controller *ctrl = serdev->ctrl;

	device_unरेजिस्टर(&serdev->dev);
	ctrl->serdev = शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(serdev_device_हटाओ);

पूर्णांक serdev_device_खोलो(काष्ठा serdev_device *serdev)
अणु
	काष्ठा serdev_controller *ctrl = serdev->ctrl;
	पूर्णांक ret;

	अगर (!ctrl || !ctrl->ops->खोलो)
		वापस -EINVAL;

	ret = ctrl->ops->खोलो(ctrl);
	अगर (ret)
		वापस ret;

	ret = pm_runसमय_get_sync(&ctrl->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(&ctrl->dev);
		जाओ err_बंद;
	पूर्ण

	वापस 0;

err_बंद:
	अगर (ctrl->ops->बंद)
		ctrl->ops->बंद(ctrl);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(serdev_device_खोलो);

व्योम serdev_device_बंद(काष्ठा serdev_device *serdev)
अणु
	काष्ठा serdev_controller *ctrl = serdev->ctrl;

	अगर (!ctrl || !ctrl->ops->बंद)
		वापस;

	pm_runसमय_put(&ctrl->dev);

	ctrl->ops->बंद(ctrl);
पूर्ण
EXPORT_SYMBOL_GPL(serdev_device_बंद);

अटल व्योम devm_serdev_device_release(काष्ठा device *dev, व्योम *dr)
अणु
	serdev_device_बंद(*(काष्ठा serdev_device **)dr);
पूर्ण

पूर्णांक devm_serdev_device_खोलो(काष्ठा device *dev, काष्ठा serdev_device *serdev)
अणु
	काष्ठा serdev_device **dr;
	पूर्णांक ret;

	dr = devres_alloc(devm_serdev_device_release, माप(*dr), GFP_KERNEL);
	अगर (!dr)
		वापस -ENOMEM;

	ret = serdev_device_खोलो(serdev);
	अगर (ret) अणु
		devres_मुक्त(dr);
		वापस ret;
	पूर्ण

	*dr = serdev;
	devres_add(dev, dr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_serdev_device_खोलो);

व्योम serdev_device_ग_लिखो_wakeup(काष्ठा serdev_device *serdev)
अणु
	complete(&serdev->ग_लिखो_comp);
पूर्ण
EXPORT_SYMBOL_GPL(serdev_device_ग_लिखो_wakeup);

/**
 * serdev_device_ग_लिखो_buf() - ग_लिखो data asynchronously
 * @serdev:	serdev device
 * @buf:	data to be written
 * @count:	number of bytes to ग_लिखो
 *
 * Write data to the device asynchronously.
 *
 * Note that any accepted data has only been buffered by the controller; use
 * serdev_device_रुको_until_sent() to make sure the controller ग_लिखो buffer
 * has actually been emptied.
 *
 * Return: The number of bytes written (less than count अगर not enough room in
 * the ग_लिखो buffer), or a negative त्रुटि_सं on errors.
 */
पूर्णांक serdev_device_ग_लिखो_buf(काष्ठा serdev_device *serdev,
			    स्थिर अचिन्हित अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा serdev_controller *ctrl = serdev->ctrl;

	अगर (!ctrl || !ctrl->ops->ग_लिखो_buf)
		वापस -EINVAL;

	वापस ctrl->ops->ग_लिखो_buf(ctrl, buf, count);
पूर्ण
EXPORT_SYMBOL_GPL(serdev_device_ग_लिखो_buf);

/**
 * serdev_device_ग_लिखो() - ग_लिखो data synchronously
 * @serdev:	serdev device
 * @buf:	data to be written
 * @count:	number of bytes to ग_लिखो
 * @समयout:	समयout in jअगरfies, or 0 to रुको indefinitely
 *
 * Write data to the device synchronously by repeatedly calling
 * serdev_device_ग_लिखो() until the controller has accepted all data (unless
 * पूर्णांकerrupted by a समयout or a संकेत).
 *
 * Note that any accepted data has only been buffered by the controller; use
 * serdev_device_रुको_until_sent() to make sure the controller ग_लिखो buffer
 * has actually been emptied.
 *
 * Note that this function depends on serdev_device_ग_लिखो_wakeup() being
 * called in the serdev driver ग_लिखो_wakeup() callback.
 *
 * Return: The number of bytes written (less than count अगर पूर्णांकerrupted),
 * -ETIMEDOUT or -ERESTARTSYS अगर पूर्णांकerrupted beक्रमe any bytes were written, or
 * a negative त्रुटि_सं on errors.
 */
पूर्णांक serdev_device_ग_लिखो(काष्ठा serdev_device *serdev,
			स्थिर अचिन्हित अक्षर *buf, माप_प्रकार count,
			दीर्घ समयout)
अणु
	काष्ठा serdev_controller *ctrl = serdev->ctrl;
	पूर्णांक written = 0;
	पूर्णांक ret;

	अगर (!ctrl || !ctrl->ops->ग_लिखो_buf || !serdev->ops->ग_लिखो_wakeup)
		वापस -EINVAL;

	अगर (समयout == 0)
		समयout = MAX_SCHEDULE_TIMEOUT;

	mutex_lock(&serdev->ग_लिखो_lock);
	करो अणु
		reinit_completion(&serdev->ग_लिखो_comp);

		ret = ctrl->ops->ग_लिखो_buf(ctrl, buf, count);
		अगर (ret < 0)
			अवरोध;

		written += ret;
		buf += ret;
		count -= ret;

		अगर (count == 0)
			अवरोध;

		समयout = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&serdev->ग_लिखो_comp,
								    समयout);
	पूर्ण जबतक (समयout > 0);
	mutex_unlock(&serdev->ग_लिखो_lock);

	अगर (ret < 0)
		वापस ret;

	अगर (समयout <= 0 && written == 0) अणु
		अगर (समयout == -ERESTARTSYS)
			वापस -ERESTARTSYS;
		अन्यथा
			वापस -ETIMEDOUT;
	पूर्ण

	वापस written;
पूर्ण
EXPORT_SYMBOL_GPL(serdev_device_ग_लिखो);

व्योम serdev_device_ग_लिखो_flush(काष्ठा serdev_device *serdev)
अणु
	काष्ठा serdev_controller *ctrl = serdev->ctrl;

	अगर (!ctrl || !ctrl->ops->ग_लिखो_flush)
		वापस;

	ctrl->ops->ग_लिखो_flush(ctrl);
पूर्ण
EXPORT_SYMBOL_GPL(serdev_device_ग_लिखो_flush);

पूर्णांक serdev_device_ग_लिखो_room(काष्ठा serdev_device *serdev)
अणु
	काष्ठा serdev_controller *ctrl = serdev->ctrl;

	अगर (!ctrl || !ctrl->ops->ग_लिखो_room)
		वापस 0;

	वापस serdev->ctrl->ops->ग_लिखो_room(ctrl);
पूर्ण
EXPORT_SYMBOL_GPL(serdev_device_ग_लिखो_room);

अचिन्हित पूर्णांक serdev_device_set_baudrate(काष्ठा serdev_device *serdev, अचिन्हित पूर्णांक speed)
अणु
	काष्ठा serdev_controller *ctrl = serdev->ctrl;

	अगर (!ctrl || !ctrl->ops->set_baudrate)
		वापस 0;

	वापस ctrl->ops->set_baudrate(ctrl, speed);

पूर्ण
EXPORT_SYMBOL_GPL(serdev_device_set_baudrate);

व्योम serdev_device_set_flow_control(काष्ठा serdev_device *serdev, bool enable)
अणु
	काष्ठा serdev_controller *ctrl = serdev->ctrl;

	अगर (!ctrl || !ctrl->ops->set_flow_control)
		वापस;

	ctrl->ops->set_flow_control(ctrl, enable);
पूर्ण
EXPORT_SYMBOL_GPL(serdev_device_set_flow_control);

पूर्णांक serdev_device_set_parity(काष्ठा serdev_device *serdev,
			     क्रमागत serdev_parity parity)
अणु
	काष्ठा serdev_controller *ctrl = serdev->ctrl;

	अगर (!ctrl || !ctrl->ops->set_parity)
		वापस -ENOTSUPP;

	वापस ctrl->ops->set_parity(ctrl, parity);
पूर्ण
EXPORT_SYMBOL_GPL(serdev_device_set_parity);

व्योम serdev_device_रुको_until_sent(काष्ठा serdev_device *serdev, दीर्घ समयout)
अणु
	काष्ठा serdev_controller *ctrl = serdev->ctrl;

	अगर (!ctrl || !ctrl->ops->रुको_until_sent)
		वापस;

	ctrl->ops->रुको_until_sent(ctrl, समयout);
पूर्ण
EXPORT_SYMBOL_GPL(serdev_device_रुको_until_sent);

पूर्णांक serdev_device_get_tiocm(काष्ठा serdev_device *serdev)
अणु
	काष्ठा serdev_controller *ctrl = serdev->ctrl;

	अगर (!ctrl || !ctrl->ops->get_tiocm)
		वापस -ENOTSUPP;

	वापस ctrl->ops->get_tiocm(ctrl);
पूर्ण
EXPORT_SYMBOL_GPL(serdev_device_get_tiocm);

पूर्णांक serdev_device_set_tiocm(काष्ठा serdev_device *serdev, पूर्णांक set, पूर्णांक clear)
अणु
	काष्ठा serdev_controller *ctrl = serdev->ctrl;

	अगर (!ctrl || !ctrl->ops->set_tiocm)
		वापस -ENOTSUPP;

	वापस ctrl->ops->set_tiocm(ctrl, set, clear);
पूर्ण
EXPORT_SYMBOL_GPL(serdev_device_set_tiocm);

अटल पूर्णांक serdev_drv_probe(काष्ठा device *dev)
अणु
	स्थिर काष्ठा serdev_device_driver *sdrv = to_serdev_device_driver(dev->driver);
	पूर्णांक ret;

	ret = dev_pm_करोमुख्य_attach(dev, true);
	अगर (ret)
		वापस ret;

	ret = sdrv->probe(to_serdev_device(dev));
	अगर (ret)
		dev_pm_करोमुख्य_detach(dev, true);

	वापस ret;
पूर्ण

अटल पूर्णांक serdev_drv_हटाओ(काष्ठा device *dev)
अणु
	स्थिर काष्ठा serdev_device_driver *sdrv = to_serdev_device_driver(dev->driver);
	अगर (sdrv->हटाओ)
		sdrv->हटाओ(to_serdev_device(dev));

	dev_pm_करोमुख्य_detach(dev, true);

	वापस 0;
पूर्ण

अटल काष्ठा bus_type serdev_bus_type = अणु
	.name		= "serial",
	.match		= serdev_device_match,
	.probe		= serdev_drv_probe,
	.हटाओ		= serdev_drv_हटाओ,
पूर्ण;

/**
 * serdev_device_alloc() - Allocate a new serdev device
 * @ctrl:	associated controller
 *
 * Caller is responsible क्रम either calling serdev_device_add() to add the
 * newly allocated controller, or calling serdev_device_put() to discard it.
 */
काष्ठा serdev_device *serdev_device_alloc(काष्ठा serdev_controller *ctrl)
अणु
	काष्ठा serdev_device *serdev;

	serdev = kzalloc(माप(*serdev), GFP_KERNEL);
	अगर (!serdev)
		वापस शून्य;

	serdev->ctrl = ctrl;
	device_initialize(&serdev->dev);
	serdev->dev.parent = &ctrl->dev;
	serdev->dev.bus = &serdev_bus_type;
	serdev->dev.type = &serdev_device_type;
	init_completion(&serdev->ग_लिखो_comp);
	mutex_init(&serdev->ग_लिखो_lock);
	वापस serdev;
पूर्ण
EXPORT_SYMBOL_GPL(serdev_device_alloc);

/**
 * serdev_controller_alloc() - Allocate a new serdev controller
 * @parent:	parent device
 * @size:	size of निजी data
 *
 * Caller is responsible क्रम either calling serdev_controller_add() to add the
 * newly allocated controller, or calling serdev_controller_put() to discard it.
 * The allocated निजी data region may be accessed via
 * serdev_controller_get_drvdata()
 */
काष्ठा serdev_controller *serdev_controller_alloc(काष्ठा device *parent,
					      माप_प्रकार size)
अणु
	काष्ठा serdev_controller *ctrl;
	पूर्णांक id;

	अगर (WARN_ON(!parent))
		वापस शून्य;

	ctrl = kzalloc(माप(*ctrl) + size, GFP_KERNEL);
	अगर (!ctrl)
		वापस शून्य;

	id = ida_simple_get(&ctrl_ida, 0, 0, GFP_KERNEL);
	अगर (id < 0) अणु
		dev_err(parent,
			"unable to allocate serdev controller identifier.\n");
		जाओ err_मुक्त;
	पूर्ण

	ctrl->nr = id;

	device_initialize(&ctrl->dev);
	ctrl->dev.type = &serdev_ctrl_type;
	ctrl->dev.bus = &serdev_bus_type;
	ctrl->dev.parent = parent;
	ctrl->dev.of_node = parent->of_node;
	serdev_controller_set_drvdata(ctrl, &ctrl[1]);

	dev_set_name(&ctrl->dev, "serial%d", id);

	pm_runसमय_no_callbacks(&ctrl->dev);
	pm_suspend_ignore_children(&ctrl->dev, true);

	dev_dbg(&ctrl->dev, "allocated controller 0x%p id %d\n", ctrl, id);
	वापस ctrl;

err_मुक्त:
	kमुक्त(ctrl);

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(serdev_controller_alloc);

अटल पूर्णांक of_serdev_रेजिस्टर_devices(काष्ठा serdev_controller *ctrl)
अणु
	काष्ठा device_node *node;
	काष्ठा serdev_device *serdev = शून्य;
	पूर्णांक err;
	bool found = false;

	क्रम_each_available_child_of_node(ctrl->dev.of_node, node) अणु
		अगर (!of_get_property(node, "compatible", शून्य))
			जारी;

		dev_dbg(&ctrl->dev, "adding child %pOF\n", node);

		serdev = serdev_device_alloc(ctrl);
		अगर (!serdev)
			जारी;

		serdev->dev.of_node = node;

		err = serdev_device_add(serdev);
		अगर (err) अणु
			dev_err(&serdev->dev,
				"failure adding device. status %pe\n",
				ERR_PTR(err));
			serdev_device_put(serdev);
		पूर्ण अन्यथा
			found = true;
	पूर्ण
	अगर (!found)
		वापस -ENODEV;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI

#घोषणा SERDEV_ACPI_MAX_SCAN_DEPTH 32

काष्ठा acpi_serdev_lookup अणु
	acpi_handle device_handle;
	acpi_handle controller_handle;
	पूर्णांक n;
	पूर्णांक index;
पूर्ण;

अटल पूर्णांक acpi_serdev_parse_resource(काष्ठा acpi_resource *ares, व्योम *data)
अणु
	काष्ठा acpi_serdev_lookup *lookup = data;
	काष्ठा acpi_resource_uart_serialbus *sb;
	acpi_status status;

	अगर (ares->type != ACPI_RESOURCE_TYPE_SERIAL_BUS)
		वापस 1;

	अगर (ares->data.common_serial_bus.type != ACPI_RESOURCE_SERIAL_TYPE_UART)
		वापस 1;

	अगर (lookup->index != -1 && lookup->n++ != lookup->index)
		वापस 1;

	sb = &ares->data.uart_serial_bus;

	status = acpi_get_handle(lookup->device_handle,
				 sb->resource_source.string_ptr,
				 &lookup->controller_handle);
	अगर (ACPI_FAILURE(status))
		वापस 1;

	/*
	 * NOTE: Ideally, we would also want to retreive other properties here,
	 * once setting them beक्रमe खोलोing the device is supported by serdev.
	 */

	वापस 1;
पूर्ण

अटल पूर्णांक acpi_serdev_करो_lookup(काष्ठा acpi_device *adev,
                                 काष्ठा acpi_serdev_lookup *lookup)
अणु
	काष्ठा list_head resource_list;
	पूर्णांक ret;

	lookup->device_handle = acpi_device_handle(adev);
	lookup->controller_handle = शून्य;
	lookup->n = 0;

	INIT_LIST_HEAD(&resource_list);
	ret = acpi_dev_get_resources(adev, &resource_list,
				     acpi_serdev_parse_resource, lookup);
	acpi_dev_मुक्त_resource_list(&resource_list);

	अगर (ret < 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_serdev_check_resources(काष्ठा serdev_controller *ctrl,
				       काष्ठा acpi_device *adev)
अणु
	काष्ठा acpi_serdev_lookup lookup;
	पूर्णांक ret;

	अगर (acpi_bus_get_status(adev) || !adev->status.present)
		वापस -EINVAL;

	/* Look क्रम UARTSerialBusV2 resource */
	lookup.index = -1;	// we only care क्रम the last device

	ret = acpi_serdev_करो_lookup(adev, &lookup);
	अगर (ret)
		वापस ret;

	/*
	 * Apple machines provide an empty resource ढाँचा, so on those
	 * machines just look क्रम immediate children with a "baud" property
	 * (from the _DSM method) instead.
	 */
	अगर (!lookup.controller_handle && x86_apple_machine &&
	    !acpi_dev_get_property(adev, "baud", ACPI_TYPE_BUFFER, शून्य))
		acpi_get_parent(adev->handle, &lookup.controller_handle);

	/* Make sure controller and ResourceSource handle match */
	अगर (ACPI_HANDLE(ctrl->dev.parent) != lookup.controller_handle)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल acpi_status acpi_serdev_रेजिस्टर_device(काष्ठा serdev_controller *ctrl,
					       काष्ठा acpi_device *adev)
अणु
	काष्ठा serdev_device *serdev;
	पूर्णांक err;

	serdev = serdev_device_alloc(ctrl);
	अगर (!serdev) अणु
		dev_err(&ctrl->dev, "failed to allocate serdev device for %s\n",
			dev_name(&adev->dev));
		वापस AE_NO_MEMORY;
	पूर्ण

	ACPI_COMPANION_SET(&serdev->dev, adev);
	acpi_device_set_क्रमागतerated(adev);

	err = serdev_device_add(serdev);
	अगर (err) अणु
		dev_err(&serdev->dev,
			"failure adding ACPI serdev device. status %pe\n",
			ERR_PTR(err));
		serdev_device_put(serdev);
	पूर्ण

	वापस AE_OK;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id serdev_acpi_devices_blacklist[] = अणु
	अणु "INT3511", 0 पूर्ण,
	अणु "INT3512", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल acpi_status acpi_serdev_add_device(acpi_handle handle, u32 level,
					  व्योम *data, व्योम **वापस_value)
अणु
	काष्ठा serdev_controller *ctrl = data;
	काष्ठा acpi_device *adev;

	अगर (acpi_bus_get_device(handle, &adev))
		वापस AE_OK;

	अगर (acpi_device_क्रमागतerated(adev))
		वापस AE_OK;

	/* Skip अगर black listed */
	अगर (!acpi_match_device_ids(adev, serdev_acpi_devices_blacklist))
		वापस AE_OK;

	अगर (acpi_serdev_check_resources(ctrl, adev))
		वापस AE_OK;

	वापस acpi_serdev_रेजिस्टर_device(ctrl, adev);
पूर्ण


अटल पूर्णांक acpi_serdev_रेजिस्टर_devices(काष्ठा serdev_controller *ctrl)
अणु
	acpi_status status;

	अगर (!has_acpi_companion(ctrl->dev.parent))
		वापस -ENODEV;

	status = acpi_walk_namespace(ACPI_TYPE_DEVICE, ACPI_ROOT_OBJECT,
				     SERDEV_ACPI_MAX_SCAN_DEPTH,
				     acpi_serdev_add_device, शून्य, ctrl, शून्य);
	अगर (ACPI_FAILURE(status))
		dev_warn(&ctrl->dev, "failed to enumerate serdev slaves\n");

	अगर (!ctrl->serdev)
		वापस -ENODEV;

	वापस 0;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक acpi_serdev_रेजिस्टर_devices(काष्ठा serdev_controller *ctrl)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI */

/**
 * serdev_controller_add() - Add an serdev controller
 * @ctrl:	controller to be रेजिस्टरed.
 *
 * Register a controller previously allocated via serdev_controller_alloc() with
 * the serdev core.
 */
पूर्णांक serdev_controller_add(काष्ठा serdev_controller *ctrl)
अणु
	पूर्णांक ret_of, ret_acpi, ret;

	/* Can't रेजिस्टर until after driver model init */
	अगर (WARN_ON(!is_रेजिस्टरed))
		वापस -EAGAIN;

	ret = device_add(&ctrl->dev);
	अगर (ret)
		वापस ret;

	pm_runसमय_enable(&ctrl->dev);

	ret_of = of_serdev_रेजिस्टर_devices(ctrl);
	ret_acpi = acpi_serdev_रेजिस्टर_devices(ctrl);
	अगर (ret_of && ret_acpi) अणु
		dev_dbg(&ctrl->dev, "no devices registered: of:%pe acpi:%pe\n",
			ERR_PTR(ret_of), ERR_PTR(ret_acpi));
		ret = -ENODEV;
		जाओ err_rpm_disable;
	पूर्ण

	dev_dbg(&ctrl->dev, "serdev%d registered: dev:%p\n",
		ctrl->nr, &ctrl->dev);
	वापस 0;

err_rpm_disable:
	pm_runसमय_disable(&ctrl->dev);
	device_del(&ctrl->dev);
	वापस ret;
पूर्ण;
EXPORT_SYMBOL_GPL(serdev_controller_add);

/* Remove a device associated with a controller */
अटल पूर्णांक serdev_हटाओ_device(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा serdev_device *serdev = to_serdev_device(dev);
	अगर (dev->type == &serdev_device_type)
		serdev_device_हटाओ(serdev);
	वापस 0;
पूर्ण

/**
 * serdev_controller_हटाओ(): हटाओ an serdev controller
 * @ctrl:	controller to हटाओ
 *
 * Remove a serdev controller.  Caller is responsible क्रम calling
 * serdev_controller_put() to discard the allocated controller.
 */
व्योम serdev_controller_हटाओ(काष्ठा serdev_controller *ctrl)
अणु
	अगर (!ctrl)
		वापस;

	device_क्रम_each_child(&ctrl->dev, शून्य, serdev_हटाओ_device);
	pm_runसमय_disable(&ctrl->dev);
	device_del(&ctrl->dev);
पूर्ण
EXPORT_SYMBOL_GPL(serdev_controller_हटाओ);

/**
 * serdev_driver_रेजिस्टर() - Register client driver with serdev core
 * @sdrv:	client driver to be associated with client-device.
 * @owner:	client driver owner to set.
 *
 * This API will रेजिस्टर the client driver with the serdev framework.
 * It is typically called from the driver's module-init function.
 */
पूर्णांक __serdev_device_driver_रेजिस्टर(काष्ठा serdev_device_driver *sdrv, काष्ठा module *owner)
अणु
	sdrv->driver.bus = &serdev_bus_type;
	sdrv->driver.owner = owner;

	/* क्रमce drivers to async probe so I/O is possible in probe */
        sdrv->driver.probe_type = PROBE_PREFER_ASYNCHRONOUS;

	वापस driver_रेजिस्टर(&sdrv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(__serdev_device_driver_रेजिस्टर);

अटल व्योम __निकास serdev_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&serdev_bus_type);
	ida_destroy(&ctrl_ida);
पूर्ण
module_निकास(serdev_निकास);

अटल पूर्णांक __init serdev_init(व्योम)
अणु
	पूर्णांक ret;

	ret = bus_रेजिस्टर(&serdev_bus_type);
	अगर (ret)
		वापस ret;

	is_रेजिस्टरed = true;
	वापस 0;
पूर्ण
/* Must be beक्रमe serial drivers रेजिस्टर */
postcore_initcall(serdev_init);

MODULE_AUTHOR("Rob Herring <robh@kernel.org>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Serial attached device bus");
