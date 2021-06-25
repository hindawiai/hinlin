<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2015, The Linux Foundation. All rights reserved.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/idr.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spmi.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <dt-bindings/spmi/spmi.h>
#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/spmi.h>

अटल bool is_रेजिस्टरed;
अटल DEFINE_IDA(ctrl_ida);

अटल व्योम spmi_dev_release(काष्ठा device *dev)
अणु
	काष्ठा spmi_device *sdev = to_spmi_device(dev);

	kमुक्त(sdev);
पूर्ण

अटल स्थिर काष्ठा device_type spmi_dev_type = अणु
	.release	= spmi_dev_release,
पूर्ण;

अटल व्योम spmi_ctrl_release(काष्ठा device *dev)
अणु
	काष्ठा spmi_controller *ctrl = to_spmi_controller(dev);

	ida_simple_हटाओ(&ctrl_ida, ctrl->nr);
	kमुक्त(ctrl);
पूर्ण

अटल स्थिर काष्ठा device_type spmi_ctrl_type = अणु
	.release	= spmi_ctrl_release,
पूर्ण;

अटल पूर्णांक spmi_device_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	अगर (of_driver_match_device(dev, drv))
		वापस 1;

	अगर (drv->name)
		वापस म_भेदन(dev_name(dev), drv->name,
			       SPMI_NAME_SIZE) == 0;

	वापस 0;
पूर्ण

/**
 * spmi_device_add() - add a device previously स्थिरructed via spmi_device_alloc()
 * @sdev:	spmi_device to be added
 */
पूर्णांक spmi_device_add(काष्ठा spmi_device *sdev)
अणु
	काष्ठा spmi_controller *ctrl = sdev->ctrl;
	पूर्णांक err;

	dev_set_name(&sdev->dev, "%d-%02x", ctrl->nr, sdev->usid);

	err = device_add(&sdev->dev);
	अगर (err < 0) अणु
		dev_err(&sdev->dev, "Can't add %s, status %d\n",
			dev_name(&sdev->dev), err);
		जाओ err_device_add;
	पूर्ण

	dev_dbg(&sdev->dev, "device %s registered\n", dev_name(&sdev->dev));

err_device_add:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(spmi_device_add);

/**
 * spmi_device_हटाओ(): हटाओ an SPMI device
 * @sdev:	spmi_device to be हटाओd
 */
व्योम spmi_device_हटाओ(काष्ठा spmi_device *sdev)
अणु
	device_unरेजिस्टर(&sdev->dev);
पूर्ण
EXPORT_SYMBOL_GPL(spmi_device_हटाओ);

अटल अंतरभूत पूर्णांक
spmi_cmd(काष्ठा spmi_controller *ctrl, u8 opcode, u8 sid)
अणु
	पूर्णांक ret;

	अगर (!ctrl || !ctrl->cmd || ctrl->dev.type != &spmi_ctrl_type)
		वापस -EINVAL;

	ret = ctrl->cmd(ctrl, opcode, sid);
	trace_spmi_cmd(opcode, sid, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक spmi_पढ़ो_cmd(काष्ठा spmi_controller *ctrl, u8 opcode,
				u8 sid, u16 addr, u8 *buf, माप_प्रकार len)
अणु
	पूर्णांक ret;

	अगर (!ctrl || !ctrl->पढ़ो_cmd || ctrl->dev.type != &spmi_ctrl_type)
		वापस -EINVAL;

	trace_spmi_पढ़ो_begin(opcode, sid, addr);
	ret = ctrl->पढ़ो_cmd(ctrl, opcode, sid, addr, buf, len);
	trace_spmi_पढ़ो_end(opcode, sid, addr, ret, len, buf);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक spmi_ग_लिखो_cmd(काष्ठा spmi_controller *ctrl, u8 opcode,
				 u8 sid, u16 addr, स्थिर u8 *buf, माप_प्रकार len)
अणु
	पूर्णांक ret;

	अगर (!ctrl || !ctrl->ग_लिखो_cmd || ctrl->dev.type != &spmi_ctrl_type)
		वापस -EINVAL;

	trace_spmi_ग_लिखो_begin(opcode, sid, addr, len, buf);
	ret = ctrl->ग_लिखो_cmd(ctrl, opcode, sid, addr, buf, len);
	trace_spmi_ग_लिखो_end(opcode, sid, addr, ret);
	वापस ret;
पूर्ण

/**
 * spmi_रेजिस्टर_पढ़ो() - रेजिस्टर पढ़ो
 * @sdev:	SPMI device.
 * @addr:	slave रेजिस्टर address (5-bit address).
 * @buf:	buffer to be populated with data from the Slave.
 *
 * Reads 1 byte of data from a Slave device रेजिस्टर.
 */
पूर्णांक spmi_रेजिस्टर_पढ़ो(काष्ठा spmi_device *sdev, u8 addr, u8 *buf)
अणु
	/* 5-bit रेजिस्टर address */
	अगर (addr > 0x1F)
		वापस -EINVAL;

	वापस spmi_पढ़ो_cmd(sdev->ctrl, SPMI_CMD_READ, sdev->usid, addr,
			     buf, 1);
पूर्ण
EXPORT_SYMBOL_GPL(spmi_रेजिस्टर_पढ़ो);

/**
 * spmi_ext_रेजिस्टर_पढ़ो() - extended रेजिस्टर पढ़ो
 * @sdev:	SPMI device.
 * @addr:	slave रेजिस्टर address (8-bit address).
 * @buf:	buffer to be populated with data from the Slave.
 * @len:	the request number of bytes to पढ़ो (up to 16 bytes).
 *
 * Reads up to 16 bytes of data from the extended रेजिस्टर space on a
 * Slave device.
 */
पूर्णांक spmi_ext_रेजिस्टर_पढ़ो(काष्ठा spmi_device *sdev, u8 addr, u8 *buf,
			   माप_प्रकार len)
अणु
	/* 8-bit रेजिस्टर address, up to 16 bytes */
	अगर (len == 0 || len > 16)
		वापस -EINVAL;

	वापस spmi_पढ़ो_cmd(sdev->ctrl, SPMI_CMD_EXT_READ, sdev->usid, addr,
			     buf, len);
पूर्ण
EXPORT_SYMBOL_GPL(spmi_ext_रेजिस्टर_पढ़ो);

/**
 * spmi_ext_रेजिस्टर_पढ़ोl() - extended रेजिस्टर पढ़ो दीर्घ
 * @sdev:	SPMI device.
 * @addr:	slave रेजिस्टर address (16-bit address).
 * @buf:	buffer to be populated with data from the Slave.
 * @len:	the request number of bytes to पढ़ो (up to 8 bytes).
 *
 * Reads up to 8 bytes of data from the extended रेजिस्टर space on a
 * Slave device using 16-bit address.
 */
पूर्णांक spmi_ext_रेजिस्टर_पढ़ोl(काष्ठा spmi_device *sdev, u16 addr, u8 *buf,
			    माप_प्रकार len)
अणु
	/* 16-bit रेजिस्टर address, up to 8 bytes */
	अगर (len == 0 || len > 8)
		वापस -EINVAL;

	वापस spmi_पढ़ो_cmd(sdev->ctrl, SPMI_CMD_EXT_READL, sdev->usid, addr,
			     buf, len);
पूर्ण
EXPORT_SYMBOL_GPL(spmi_ext_रेजिस्टर_पढ़ोl);

/**
 * spmi_रेजिस्टर_ग_लिखो() - रेजिस्टर ग_लिखो
 * @sdev:	SPMI device
 * @addr:	slave रेजिस्टर address (5-bit address).
 * @data:	buffer containing the data to be transferred to the Slave.
 *
 * Writes 1 byte of data to a Slave device रेजिस्टर.
 */
पूर्णांक spmi_रेजिस्टर_ग_लिखो(काष्ठा spmi_device *sdev, u8 addr, u8 data)
अणु
	/* 5-bit रेजिस्टर address */
	अगर (addr > 0x1F)
		वापस -EINVAL;

	वापस spmi_ग_लिखो_cmd(sdev->ctrl, SPMI_CMD_WRITE, sdev->usid, addr,
			      &data, 1);
पूर्ण
EXPORT_SYMBOL_GPL(spmi_रेजिस्टर_ग_लिखो);

/**
 * spmi_रेजिस्टर_zero_ग_लिखो() - रेजिस्टर zero ग_लिखो
 * @sdev:	SPMI device.
 * @data:	the data to be written to रेजिस्टर 0 (7-bits).
 *
 * Writes data to रेजिस्टर 0 of the Slave device.
 */
पूर्णांक spmi_रेजिस्टर_zero_ग_लिखो(काष्ठा spmi_device *sdev, u8 data)
अणु
	वापस spmi_ग_लिखो_cmd(sdev->ctrl, SPMI_CMD_ZERO_WRITE, sdev->usid, 0,
			      &data, 1);
पूर्ण
EXPORT_SYMBOL_GPL(spmi_रेजिस्टर_zero_ग_लिखो);

/**
 * spmi_ext_रेजिस्टर_ग_लिखो() - extended रेजिस्टर ग_लिखो
 * @sdev:	SPMI device.
 * @addr:	slave रेजिस्टर address (8-bit address).
 * @buf:	buffer containing the data to be transferred to the Slave.
 * @len:	the request number of bytes to पढ़ो (up to 16 bytes).
 *
 * Writes up to 16 bytes of data to the extended रेजिस्टर space of a
 * Slave device.
 */
पूर्णांक spmi_ext_रेजिस्टर_ग_लिखो(काष्ठा spmi_device *sdev, u8 addr, स्थिर u8 *buf,
			    माप_प्रकार len)
अणु
	/* 8-bit रेजिस्टर address, up to 16 bytes */
	अगर (len == 0 || len > 16)
		वापस -EINVAL;

	वापस spmi_ग_लिखो_cmd(sdev->ctrl, SPMI_CMD_EXT_WRITE, sdev->usid, addr,
			      buf, len);
पूर्ण
EXPORT_SYMBOL_GPL(spmi_ext_रेजिस्टर_ग_लिखो);

/**
 * spmi_ext_रेजिस्टर_ग_लिखोl() - extended रेजिस्टर ग_लिखो दीर्घ
 * @sdev:	SPMI device.
 * @addr:	slave रेजिस्टर address (16-bit address).
 * @buf:	buffer containing the data to be transferred to the Slave.
 * @len:	the request number of bytes to पढ़ो (up to 8 bytes).
 *
 * Writes up to 8 bytes of data to the extended रेजिस्टर space of a
 * Slave device using 16-bit address.
 */
पूर्णांक spmi_ext_रेजिस्टर_ग_लिखोl(काष्ठा spmi_device *sdev, u16 addr, स्थिर u8 *buf,
			     माप_प्रकार len)
अणु
	/* 4-bit Slave Identअगरier, 16-bit रेजिस्टर address, up to 8 bytes */
	अगर (len == 0 || len > 8)
		वापस -EINVAL;

	वापस spmi_ग_लिखो_cmd(sdev->ctrl, SPMI_CMD_EXT_WRITEL, sdev->usid,
			      addr, buf, len);
पूर्ण
EXPORT_SYMBOL_GPL(spmi_ext_रेजिस्टर_ग_लिखोl);

/**
 * spmi_command_reset() - sends RESET command to the specअगरied slave
 * @sdev:	SPMI device.
 *
 * The Reset command initializes the Slave and क्रमces all रेजिस्टरs to
 * their reset values. The Slave shall enter the STARTUP state after
 * receiving a Reset command.
 */
पूर्णांक spmi_command_reset(काष्ठा spmi_device *sdev)
अणु
	वापस spmi_cmd(sdev->ctrl, SPMI_CMD_RESET, sdev->usid);
पूर्ण
EXPORT_SYMBOL_GPL(spmi_command_reset);

/**
 * spmi_command_sleep() - sends SLEEP command to the specअगरied SPMI device
 * @sdev:	SPMI device.
 *
 * The Sleep command causes the Slave to enter the user defined SLEEP state.
 */
पूर्णांक spmi_command_sleep(काष्ठा spmi_device *sdev)
अणु
	वापस spmi_cmd(sdev->ctrl, SPMI_CMD_SLEEP, sdev->usid);
पूर्ण
EXPORT_SYMBOL_GPL(spmi_command_sleep);

/**
 * spmi_command_wakeup() - sends WAKEUP command to the specअगरied SPMI device
 * @sdev:	SPMI device.
 *
 * The Wakeup command causes the Slave to move from the SLEEP state to
 * the ACTIVE state.
 */
पूर्णांक spmi_command_wakeup(काष्ठा spmi_device *sdev)
अणु
	वापस spmi_cmd(sdev->ctrl, SPMI_CMD_WAKEUP, sdev->usid);
पूर्ण
EXPORT_SYMBOL_GPL(spmi_command_wakeup);

/**
 * spmi_command_shutकरोwn() - sends SHUTDOWN command to the specअगरied SPMI device
 * @sdev:	SPMI device.
 *
 * The Shutकरोwn command causes the Slave to enter the SHUTDOWN state.
 */
पूर्णांक spmi_command_shutकरोwn(काष्ठा spmi_device *sdev)
अणु
	वापस spmi_cmd(sdev->ctrl, SPMI_CMD_SHUTDOWN, sdev->usid);
पूर्ण
EXPORT_SYMBOL_GPL(spmi_command_shutकरोwn);

अटल पूर्णांक spmi_drv_probe(काष्ठा device *dev)
अणु
	स्थिर काष्ठा spmi_driver *sdrv = to_spmi_driver(dev->driver);
	काष्ठा spmi_device *sdev = to_spmi_device(dev);
	पूर्णांक err;

	pm_runसमय_get_noresume(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);

	err = sdrv->probe(sdev);
	अगर (err)
		जाओ fail_probe;

	वापस 0;

fail_probe:
	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);
	pm_runसमय_put_noidle(dev);
	वापस err;
पूर्ण

अटल पूर्णांक spmi_drv_हटाओ(काष्ठा device *dev)
अणु
	स्थिर काष्ठा spmi_driver *sdrv = to_spmi_driver(dev->driver);

	pm_runसमय_get_sync(dev);
	sdrv->हटाओ(to_spmi_device(dev));
	pm_runसमय_put_noidle(dev);

	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);
	pm_runसमय_put_noidle(dev);
	वापस 0;
पूर्ण

अटल व्योम spmi_drv_shutकरोwn(काष्ठा device *dev)
अणु
	स्थिर काष्ठा spmi_driver *sdrv = to_spmi_driver(dev->driver);

	अगर (sdrv && sdrv->shutकरोwn)
		sdrv->shutकरोwn(to_spmi_device(dev));
पूर्ण

अटल पूर्णांक spmi_drv_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	पूर्णांक ret;

	ret = of_device_uevent_modalias(dev, env);
	अगर (ret != -ENODEV)
		वापस ret;

	वापस 0;
पूर्ण

अटल काष्ठा bus_type spmi_bus_type = अणु
	.name		= "spmi",
	.match		= spmi_device_match,
	.probe		= spmi_drv_probe,
	.हटाओ		= spmi_drv_हटाओ,
	.shutकरोwn	= spmi_drv_shutकरोwn,
	.uevent		= spmi_drv_uevent,
पूर्ण;

/**
 * spmi_controller_alloc() - Allocate a new SPMI device
 * @ctrl:	associated controller
 *
 * Caller is responsible क्रम either calling spmi_device_add() to add the
 * newly allocated controller, or calling spmi_device_put() to discard it.
 */
काष्ठा spmi_device *spmi_device_alloc(काष्ठा spmi_controller *ctrl)
अणु
	काष्ठा spmi_device *sdev;

	sdev = kzalloc(माप(*sdev), GFP_KERNEL);
	अगर (!sdev)
		वापस शून्य;

	sdev->ctrl = ctrl;
	device_initialize(&sdev->dev);
	sdev->dev.parent = &ctrl->dev;
	sdev->dev.bus = &spmi_bus_type;
	sdev->dev.type = &spmi_dev_type;
	वापस sdev;
पूर्ण
EXPORT_SYMBOL_GPL(spmi_device_alloc);

/**
 * spmi_controller_alloc() - Allocate a new SPMI controller
 * @parent:	parent device
 * @size:	size of निजी data
 *
 * Caller is responsible क्रम either calling spmi_controller_add() to add the
 * newly allocated controller, or calling spmi_controller_put() to discard it.
 * The allocated निजी data region may be accessed via
 * spmi_controller_get_drvdata()
 */
काष्ठा spmi_controller *spmi_controller_alloc(काष्ठा device *parent,
					      माप_प्रकार size)
अणु
	काष्ठा spmi_controller *ctrl;
	पूर्णांक id;

	अगर (WARN_ON(!parent))
		वापस शून्य;

	ctrl = kzalloc(माप(*ctrl) + size, GFP_KERNEL);
	अगर (!ctrl)
		वापस शून्य;

	device_initialize(&ctrl->dev);
	ctrl->dev.type = &spmi_ctrl_type;
	ctrl->dev.bus = &spmi_bus_type;
	ctrl->dev.parent = parent;
	ctrl->dev.of_node = parent->of_node;
	spmi_controller_set_drvdata(ctrl, &ctrl[1]);

	id = ida_simple_get(&ctrl_ida, 0, 0, GFP_KERNEL);
	अगर (id < 0) अणु
		dev_err(parent,
			"unable to allocate SPMI controller identifier.\n");
		spmi_controller_put(ctrl);
		वापस शून्य;
	पूर्ण

	ctrl->nr = id;
	dev_set_name(&ctrl->dev, "spmi-%d", id);

	dev_dbg(&ctrl->dev, "allocated controller 0x%p id %d\n", ctrl, id);
	वापस ctrl;
पूर्ण
EXPORT_SYMBOL_GPL(spmi_controller_alloc);

अटल व्योम of_spmi_रेजिस्टर_devices(काष्ठा spmi_controller *ctrl)
अणु
	काष्ठा device_node *node;
	पूर्णांक err;

	अगर (!ctrl->dev.of_node)
		वापस;

	क्रम_each_available_child_of_node(ctrl->dev.of_node, node) अणु
		काष्ठा spmi_device *sdev;
		u32 reg[2];

		dev_dbg(&ctrl->dev, "adding child %pOF\n", node);

		err = of_property_पढ़ो_u32_array(node, "reg", reg, 2);
		अगर (err) अणु
			dev_err(&ctrl->dev,
				"node %pOF err (%d) does not have 'reg' property\n",
				node, err);
			जारी;
		पूर्ण

		अगर (reg[1] != SPMI_USID) अणु
			dev_err(&ctrl->dev,
				"node %pOF contains unsupported 'reg' entry\n",
				node);
			जारी;
		पूर्ण

		अगर (reg[0] >= SPMI_MAX_SLAVE_ID) अणु
			dev_err(&ctrl->dev, "invalid usid on node %pOF\n", node);
			जारी;
		पूर्ण

		dev_dbg(&ctrl->dev, "read usid %02x\n", reg[0]);

		sdev = spmi_device_alloc(ctrl);
		अगर (!sdev)
			जारी;

		sdev->dev.of_node = node;
		sdev->usid = (u8)reg[0];

		err = spmi_device_add(sdev);
		अगर (err) अणु
			dev_err(&sdev->dev,
				"failure adding device. status %d\n", err);
			spmi_device_put(sdev);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * spmi_controller_add() - Add an SPMI controller
 * @ctrl:	controller to be रेजिस्टरed.
 *
 * Register a controller previously allocated via spmi_controller_alloc() with
 * the SPMI core.
 */
पूर्णांक spmi_controller_add(काष्ठा spmi_controller *ctrl)
अणु
	पूर्णांक ret;

	/* Can't रेजिस्टर until after driver model init */
	अगर (WARN_ON(!is_रेजिस्टरed))
		वापस -EAGAIN;

	ret = device_add(&ctrl->dev);
	अगर (ret)
		वापस ret;

	अगर (IS_ENABLED(CONFIG_OF))
		of_spmi_रेजिस्टर_devices(ctrl);

	dev_dbg(&ctrl->dev, "spmi-%d registered: dev:%p\n",
		ctrl->nr, &ctrl->dev);

	वापस 0;
पूर्ण;
EXPORT_SYMBOL_GPL(spmi_controller_add);

/* Remove a device associated with a controller */
अटल पूर्णांक spmi_ctrl_हटाओ_device(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा spmi_device *spmidev = to_spmi_device(dev);

	अगर (dev->type == &spmi_dev_type)
		spmi_device_हटाओ(spmidev);
	वापस 0;
पूर्ण

/**
 * spmi_controller_हटाओ(): हटाओ an SPMI controller
 * @ctrl:	controller to हटाओ
 *
 * Remove a SPMI controller.  Caller is responsible क्रम calling
 * spmi_controller_put() to discard the allocated controller.
 */
व्योम spmi_controller_हटाओ(काष्ठा spmi_controller *ctrl)
अणु
	अगर (!ctrl)
		वापस;

	device_क्रम_each_child(&ctrl->dev, शून्य, spmi_ctrl_हटाओ_device);
	device_del(&ctrl->dev);
पूर्ण
EXPORT_SYMBOL_GPL(spmi_controller_हटाओ);

/**
 * spmi_driver_रेजिस्टर() - Register client driver with SPMI core
 * @sdrv:	client driver to be associated with client-device.
 *
 * This API will रेजिस्टर the client driver with the SPMI framework.
 * It is typically called from the driver's module-init function.
 */
पूर्णांक __spmi_driver_रेजिस्टर(काष्ठा spmi_driver *sdrv, काष्ठा module *owner)
अणु
	sdrv->driver.bus = &spmi_bus_type;
	sdrv->driver.owner = owner;
	वापस driver_रेजिस्टर(&sdrv->driver);
पूर्ण
EXPORT_SYMBOL_GPL(__spmi_driver_रेजिस्टर);

अटल व्योम __निकास spmi_निकास(व्योम)
अणु
	bus_unरेजिस्टर(&spmi_bus_type);
पूर्ण
module_निकास(spmi_निकास);

अटल पूर्णांक __init spmi_init(व्योम)
अणु
	पूर्णांक ret;

	ret = bus_रेजिस्टर(&spmi_bus_type);
	अगर (ret)
		वापस ret;

	is_रेजिस्टरed = true;
	वापस 0;
पूर्ण
postcore_initcall(spmi_init);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("SPMI module");
MODULE_ALIAS("platform:spmi");
