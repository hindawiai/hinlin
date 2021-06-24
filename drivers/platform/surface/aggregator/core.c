<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Surface Serial Hub (SSH) driver क्रम communication with the Surface/System
 * Aggregator Module (SSAM/SAM).
 *
 * Provides access to a SAM-over-SSH connected EC via a controller device.
 * Handles communication via requests as well as enabling, disabling, and
 * relaying of events.
 *
 * Copyright (C) 2019-2020 Maximilian Luz <luzmaximilian@gmail.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/atomic.h>
#समावेश <linux/completion.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/module.h>
#समावेश <linux/pm.h>
#समावेश <linux/serdev.h>
#समावेश <linux/sysfs.h>

#समावेश <linux/surface_aggregator/controller.h>

#समावेश "bus.h"
#समावेश "controller.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "trace.h"


/* -- Static controller reference. ------------------------------------------ */

/*
 * Main controller reference. The corresponding lock must be held जबतक
 * accessing (पढ़ोing/writing) the reference.
 */
अटल काष्ठा ssam_controller *__ssam_controller;
अटल DEFINE_SPINLOCK(__ssam_controller_lock);

/**
 * ssam_get_controller() - Get reference to SSAM controller.
 *
 * Returns a reference to the SSAM controller of the प्रणाली or %शून्य अगर there
 * is none, it hasn't been set up yet, or it has alपढ़ोy been unरेजिस्टरed.
 * This function स्वतःmatically increments the reference count of the
 * controller, thus the calling party must ensure that ssam_controller_put()
 * is called when it करोesn't need the controller any more.
 */
काष्ठा ssam_controller *ssam_get_controller(व्योम)
अणु
	काष्ठा ssam_controller *ctrl;

	spin_lock(&__ssam_controller_lock);

	ctrl = __ssam_controller;
	अगर (!ctrl)
		जाओ out;

	अगर (WARN_ON(!kref_get_unless_zero(&ctrl->kref)))
		ctrl = शून्य;

out:
	spin_unlock(&__ssam_controller_lock);
	वापस ctrl;
पूर्ण
EXPORT_SYMBOL_GPL(ssam_get_controller);

/**
 * ssam_try_set_controller() - Try to set the मुख्य controller reference.
 * @ctrl: The controller to which the reference should poपूर्णांक.
 *
 * Set the मुख्य controller reference to the given poपूर्णांकer अगर the reference
 * hasn't been set alपढ़ोy.
 *
 * Return: Returns zero on success or %-EEXIST अगर the reference has alपढ़ोy
 * been set.
 */
अटल पूर्णांक ssam_try_set_controller(काष्ठा ssam_controller *ctrl)
अणु
	पूर्णांक status = 0;

	spin_lock(&__ssam_controller_lock);
	अगर (!__ssam_controller)
		__ssam_controller = ctrl;
	अन्यथा
		status = -EEXIST;
	spin_unlock(&__ssam_controller_lock);

	वापस status;
पूर्ण

/**
 * ssam_clear_controller() - Remove/clear the मुख्य controller reference.
 *
 * Clears the मुख्य controller reference, i.e. sets it to %शून्य. This function
 * should be called beक्रमe the controller is shut करोwn.
 */
अटल व्योम ssam_clear_controller(व्योम)
अणु
	spin_lock(&__ssam_controller_lock);
	__ssam_controller = शून्य;
	spin_unlock(&__ssam_controller_lock);
पूर्ण

/**
 * ssam_client_link() - Link an arbitrary client device to the controller.
 * @c: The controller to link to.
 * @client: The client device.
 *
 * Link an arbitrary client device to the controller by creating a device link
 * between it as consumer and the controller device as provider. This function
 * can be used क्रम non-SSAM devices (or SSAM devices not रेजिस्टरed as child
 * under the controller) to guarantee that the controller is valid क्रम as दीर्घ
 * as the driver of the client device is bound, and that proper suspend and
 * resume ordering is guaranteed.
 *
 * The device link करोes not have to be deकाष्ठाed manually. It is हटाओd
 * स्वतःmatically once the driver of the client device unbinds.
 *
 * Return: Returns zero on success, %-ENODEV अगर the controller is not पढ़ोy or
 * going to be हटाओd soon, or %-ENOMEM अगर the device link could not be
 * created क्रम other reasons.
 */
पूर्णांक ssam_client_link(काष्ठा ssam_controller *c, काष्ठा device *client)
अणु
	स्थिर u32 flags = DL_FLAG_PM_RUNTIME | DL_FLAG_AUTOREMOVE_CONSUMER;
	काष्ठा device_link *link;
	काष्ठा device *ctrldev;

	ssam_controller_statelock(c);

	अगर (c->state != SSAM_CONTROLLER_STARTED) अणु
		ssam_controller_stateunlock(c);
		वापस -ENODEV;
	पूर्ण

	ctrldev = ssam_controller_device(c);
	अगर (!ctrldev) अणु
		ssam_controller_stateunlock(c);
		वापस -ENODEV;
	पूर्ण

	link = device_link_add(client, ctrldev, flags);
	अगर (!link) अणु
		ssam_controller_stateunlock(c);
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Return -ENODEV अगर supplier driver is on its way to be हटाओd. In
	 * this हाल, the controller won't be around क्रम much दीर्घer and the
	 * device link is not going to save us any more, as unbinding is
	 * alपढ़ोy in progress.
	 */
	अगर (READ_ONCE(link->status) == DL_STATE_SUPPLIER_UNBIND) अणु
		ssam_controller_stateunlock(c);
		वापस -ENODEV;
	पूर्ण

	ssam_controller_stateunlock(c);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ssam_client_link);

/**
 * ssam_client_bind() - Bind an arbitrary client device to the controller.
 * @client: The client device.
 *
 * Link an arbitrary client device to the controller by creating a device link
 * between it as consumer and the मुख्य controller device as provider. This
 * function can be used क्रम non-SSAM devices to guarantee that the controller
 * वापसed by this function is valid क्रम as दीर्घ as the driver of the client
 * device is bound, and that proper suspend and resume ordering is guaranteed.
 *
 * This function करोes essentially the same as ssam_client_link(), except that
 * it first fetches the मुख्य controller reference, then creates the link, and
 * finally वापसs this reference. Note that this function करोes not increment
 * the reference counter of the controller, as, due to the link, the
 * controller lअगरeसमय is assured as दीर्घ as the driver of the client device
 * is bound.
 *
 * It is not valid to use the controller reference obtained by this method
 * outside of the driver bound to the client device at the समय of calling
 * this function, without first incrementing the reference count of the
 * controller via ssam_controller_get(). Even after करोing this, care must be
 * taken that requests are only submitted and notअगरiers are only
 * (un-)रेजिस्टरed when the controller is active and not suspended. In other
 * words: The device link only lives as दीर्घ as the client driver is bound and
 * any guarantees enक्रमced by this link (e.g. active controller state) can
 * only be relied upon as दीर्घ as this link exists and may need to be enक्रमced
 * in other ways afterwards.
 *
 * The created device link करोes not have to be deकाष्ठाed manually. It is
 * हटाओd स्वतःmatically once the driver of the client device unbinds.
 *
 * Return: Returns the controller on success, an error poपूर्णांकer with %-ENODEV
 * अगर the controller is not present, not पढ़ोy or going to be हटाओd soon, or
 * %-ENOMEM अगर the device link could not be created क्रम other reasons.
 */
काष्ठा ssam_controller *ssam_client_bind(काष्ठा device *client)
अणु
	काष्ठा ssam_controller *c;
	पूर्णांक status;

	c = ssam_get_controller();
	अगर (!c)
		वापस ERR_PTR(-ENODEV);

	status = ssam_client_link(c, client);

	/*
	 * Note that we can drop our controller reference in both success and
	 * failure हालs: On success, we have bound the controller lअगरeसमय
	 * inherently to the client driver lअगरeसमय, i.e. it the controller is
	 * now guaranteed to outlive the client driver. On failure, we're not
	 * going to use the controller any more.
	 */
	ssam_controller_put(c);

	वापस status >= 0 ? c : ERR_PTR(status);
पूर्ण
EXPORT_SYMBOL_GPL(ssam_client_bind);


/* -- Glue layer (serdev_device -> ssam_controller). ------------------------ */

अटल पूर्णांक ssam_receive_buf(काष्ठा serdev_device *dev, स्थिर अचिन्हित अक्षर *buf,
			    माप_प्रकार n)
अणु
	काष्ठा ssam_controller *ctrl;

	ctrl = serdev_device_get_drvdata(dev);
	वापस ssam_controller_receive_buf(ctrl, buf, n);
पूर्ण

अटल व्योम ssam_ग_लिखो_wakeup(काष्ठा serdev_device *dev)
अणु
	ssam_controller_ग_लिखो_wakeup(serdev_device_get_drvdata(dev));
पूर्ण

अटल स्थिर काष्ठा serdev_device_ops ssam_serdev_ops = अणु
	.receive_buf = ssam_receive_buf,
	.ग_लिखो_wakeup = ssam_ग_लिखो_wakeup,
पूर्ण;


/* -- SysFS and misc. ------------------------------------------------------- */

अटल पूर्णांक ssam_log_firmware_version(काष्ठा ssam_controller *ctrl)
अणु
	u32 version, a, b, c;
	पूर्णांक status;

	status = ssam_get_firmware_version(ctrl, &version);
	अगर (status)
		वापस status;

	a = (version >> 24) & 0xff;
	b = ((version >> 8) & 0xffff);
	c = version & 0xff;

	ssam_info(ctrl, "SAM firmware version: %u.%u.%u\n", a, b, c);
	वापस 0;
पूर्ण

अटल sमाप_प्रकार firmware_version_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ssam_controller *ctrl = dev_get_drvdata(dev);
	u32 version, a, b, c;
	पूर्णांक status;

	status = ssam_get_firmware_version(ctrl, &version);
	अगर (status < 0)
		वापस status;

	a = (version >> 24) & 0xff;
	b = ((version >> 8) & 0xffff);
	c = version & 0xff;

	वापस sysfs_emit(buf, "%u.%u.%u\n", a, b, c);
पूर्ण
अटल DEVICE_ATTR_RO(firmware_version);

अटल काष्ठा attribute *ssam_sam_attrs[] = अणु
	&dev_attr_firmware_version.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ssam_sam_group = अणु
	.name = "sam",
	.attrs = ssam_sam_attrs,
पूर्ण;


/* -- ACPI based device setup. ---------------------------------------------- */

अटल acpi_status ssam_serdev_setup_via_acpi_crs(काष्ठा acpi_resource *rsc,
						  व्योम *ctx)
अणु
	काष्ठा serdev_device *serdev = ctx;
	काष्ठा acpi_resource_common_serialbus *serial;
	काष्ठा acpi_resource_uart_serialbus *uart;
	bool flow_control;
	पूर्णांक status = 0;

	अगर (rsc->type != ACPI_RESOURCE_TYPE_SERIAL_BUS)
		वापस AE_OK;

	serial = &rsc->data.common_serial_bus;
	अगर (serial->type != ACPI_RESOURCE_SERIAL_TYPE_UART)
		वापस AE_OK;

	uart = &rsc->data.uart_serial_bus;

	/* Set up serdev device. */
	serdev_device_set_baudrate(serdev, uart->शेष_baud_rate);

	/* serdev currently only supports RTSCTS flow control. */
	अगर (uart->flow_control & (~((u8)ACPI_UART_FLOW_CONTROL_HW))) अणु
		dev_warn(&serdev->dev, "setup: unsupported flow control (value: %#04x)\n",
			 uart->flow_control);
	पूर्ण

	/* Set RTSCTS flow control. */
	flow_control = uart->flow_control & ACPI_UART_FLOW_CONTROL_HW;
	serdev_device_set_flow_control(serdev, flow_control);

	/* serdev currently only supports EVEN/ODD parity. */
	चयन (uart->parity) अणु
	हाल ACPI_UART_PARITY_NONE:
		status = serdev_device_set_parity(serdev, SERDEV_PARITY_NONE);
		अवरोध;
	हाल ACPI_UART_PARITY_EVEN:
		status = serdev_device_set_parity(serdev, SERDEV_PARITY_EVEN);
		अवरोध;
	हाल ACPI_UART_PARITY_ODD:
		status = serdev_device_set_parity(serdev, SERDEV_PARITY_ODD);
		अवरोध;
	शेष:
		dev_warn(&serdev->dev, "setup: unsupported parity (value: %#04x)\n",
			 uart->parity);
		अवरोध;
	पूर्ण

	अगर (status) अणु
		dev_err(&serdev->dev, "setup: failed to set parity (value: %#04x, error: %d)\n",
			uart->parity, status);
		वापस AE_ERROR;
	पूर्ण

	/* We've found the resource and are करोne. */
	वापस AE_CTRL_TERMINATE;
पूर्ण

अटल acpi_status ssam_serdev_setup_via_acpi(acpi_handle handle,
					      काष्ठा serdev_device *serdev)
अणु
	वापस acpi_walk_resources(handle, METHOD_NAME__CRS,
				   ssam_serdev_setup_via_acpi_crs, serdev);
पूर्ण


/* -- Power management. ----------------------------------------------------- */

अटल व्योम ssam_serial_hub_shutकरोwn(काष्ठा device *dev)
अणु
	काष्ठा ssam_controller *c = dev_get_drvdata(dev);
	पूर्णांक status;

	/*
	 * Try to disable notअगरiers, संकेत display-off and D0-निकास, ignore any
	 * errors.
	 *
	 * Note: It has not been established yet अगर this is actually
	 * necessary/useful क्रम shutकरोwn.
	 */

	status = ssam_notअगरier_disable_रेजिस्टरed(c);
	अगर (status) अणु
		ssam_err(c, "pm: failed to disable notifiers for shutdown: %d\n",
			 status);
	पूर्ण

	status = ssam_ctrl_notअगर_display_off(c);
	अगर (status)
		ssam_err(c, "pm: display-off notification failed: %d\n", status);

	status = ssam_ctrl_notअगर_d0_निकास(c);
	अगर (status)
		ssam_err(c, "pm: D0-exit notification failed: %d\n", status);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक ssam_serial_hub_pm_prepare(काष्ठा device *dev)
अणु
	काष्ठा ssam_controller *c = dev_get_drvdata(dev);
	पूर्णांक status;

	/*
	 * Try to संकेत display-off, This will quiesce events.
	 *
	 * Note: Signaling display-off/display-on should normally be करोne from
	 * some sort of display state notअगरier. As that is not available,
	 * संकेत it here.
	 */

	status = ssam_ctrl_notअगर_display_off(c);
	अगर (status)
		ssam_err(c, "pm: display-off notification failed: %d\n", status);

	वापस status;
पूर्ण

अटल व्योम ssam_serial_hub_pm_complete(काष्ठा device *dev)
अणु
	काष्ठा ssam_controller *c = dev_get_drvdata(dev);
	पूर्णांक status;

	/*
	 * Try to संकेत display-on. This will restore events.
	 *
	 * Note: Signaling display-off/display-on should normally be करोne from
	 * some sort of display state notअगरier. As that is not available,
	 * संकेत it here.
	 */

	status = ssam_ctrl_notअगर_display_on(c);
	अगर (status)
		ssam_err(c, "pm: display-on notification failed: %d\n", status);
पूर्ण

अटल पूर्णांक ssam_serial_hub_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा ssam_controller *c = dev_get_drvdata(dev);
	पूर्णांक status;

	/*
	 * Try to संकेत D0-निकास, enable IRQ wakeup अगर specअगरied. Abort on
	 * error.
	 */

	status = ssam_ctrl_notअगर_d0_निकास(c);
	अगर (status) अणु
		ssam_err(c, "pm: D0-exit notification failed: %d\n", status);
		जाओ err_notअगर;
	पूर्ण

	status = ssam_irq_arm_क्रम_wakeup(c);
	अगर (status)
		जाओ err_irq;

	WARN_ON(ssam_controller_suspend(c));
	वापस 0;

err_irq:
	ssam_ctrl_notअगर_d0_entry(c);
err_notअगर:
	ssam_ctrl_notअगर_display_on(c);
	वापस status;
पूर्ण

अटल पूर्णांक ssam_serial_hub_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा ssam_controller *c = dev_get_drvdata(dev);
	पूर्णांक status;

	WARN_ON(ssam_controller_resume(c));

	/*
	 * Try to disable IRQ wakeup (अगर specअगरied) and संकेत D0-entry. In
	 * हाल of errors, log them and try to restore normal operation state
	 * as far as possible.
	 *
	 * Note: Signaling display-off/display-on should normally be करोne from
	 * some sort of display state notअगरier. As that is not available,
	 * संकेत it here.
	 */

	ssam_irq_disarm_wakeup(c);

	status = ssam_ctrl_notअगर_d0_entry(c);
	अगर (status)
		ssam_err(c, "pm: D0-entry notification failed: %d\n", status);

	वापस 0;
पूर्ण

अटल पूर्णांक ssam_serial_hub_pm_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा ssam_controller *c = dev_get_drvdata(dev);
	पूर्णांक status;

	/*
	 * During hibernation image creation, we only have to ensure that the
	 * EC करोesn't send us any events. This is करोne via the display-off
	 * and D0-निकास notअगरications. Note that this sets up the wakeup IRQ
	 * on the EC side, however, we have disabled it by शेष on our side
	 * and won't enable it here.
	 *
	 * See ssam_serial_hub_घातeroff() क्रम more details on the hibernation
	 * process.
	 */

	status = ssam_ctrl_notअगर_d0_निकास(c);
	अगर (status) अणु
		ssam_err(c, "pm: D0-exit notification failed: %d\n", status);
		ssam_ctrl_notअगर_display_on(c);
		वापस status;
	पूर्ण

	WARN_ON(ssam_controller_suspend(c));
	वापस 0;
पूर्ण

अटल पूर्णांक ssam_serial_hub_pm_thaw(काष्ठा device *dev)
अणु
	काष्ठा ssam_controller *c = dev_get_drvdata(dev);
	पूर्णांक status;

	WARN_ON(ssam_controller_resume(c));

	status = ssam_ctrl_notअगर_d0_entry(c);
	अगर (status)
		ssam_err(c, "pm: D0-exit notification failed: %d\n", status);

	वापस status;
पूर्ण

अटल पूर्णांक ssam_serial_hub_pm_घातeroff(काष्ठा device *dev)
अणु
	काष्ठा ssam_controller *c = dev_get_drvdata(dev);
	पूर्णांक status;

	/*
	 * When entering hibernation and घातering off the प्रणाली, the EC, at
	 * least on some models, may disable events. Without us taking care of
	 * that, this leads to events not being enabled/restored when the
	 * प्रणाली resumes from hibernation, resulting SAM-HID subप्रणाली devices
	 * (i.e. keyboard, touchpad) not working, AC-plug/AC-unplug events being
	 * gone, etc.
	 *
	 * To aव्योम these issues, we disable all रेजिस्टरed events here (this is
	 * likely not actually required) and restore them during the drivers PM
	 * restore callback.
	 *
	 * Wakeup from the EC पूर्णांकerrupt is not supported during hibernation,
	 * so करोn't arm the IRQ here.
	 */

	status = ssam_notअगरier_disable_रेजिस्टरed(c);
	अगर (status) अणु
		ssam_err(c, "pm: failed to disable notifiers for hibernation: %d\n",
			 status);
		वापस status;
	पूर्ण

	status = ssam_ctrl_notअगर_d0_निकास(c);
	अगर (status) अणु
		ssam_err(c, "pm: D0-exit notification failed: %d\n", status);
		ssam_notअगरier_restore_रेजिस्टरed(c);
		वापस status;
	पूर्ण

	WARN_ON(ssam_controller_suspend(c));
	वापस 0;
पूर्ण

अटल पूर्णांक ssam_serial_hub_pm_restore(काष्ठा device *dev)
अणु
	काष्ठा ssam_controller *c = dev_get_drvdata(dev);
	पूर्णांक status;

	/*
	 * Ignore but log errors, try to restore state as much as possible in
	 * हाल of failures. See ssam_serial_hub_घातeroff() क्रम more details on
	 * the hibernation process.
	 */

	WARN_ON(ssam_controller_resume(c));

	status = ssam_ctrl_notअगर_d0_entry(c);
	अगर (status)
		ssam_err(c, "pm: D0-entry notification failed: %d\n", status);

	ssam_notअगरier_restore_रेजिस्टरed(c);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ssam_serial_hub_pm_ops = अणु
	.prepare  = ssam_serial_hub_pm_prepare,
	.complete = ssam_serial_hub_pm_complete,
	.suspend  = ssam_serial_hub_pm_suspend,
	.resume   = ssam_serial_hub_pm_resume,
	.मुक्तze   = ssam_serial_hub_pm_मुक्तze,
	.thaw     = ssam_serial_hub_pm_thaw,
	.घातeroff = ssam_serial_hub_pm_घातeroff,
	.restore  = ssam_serial_hub_pm_restore,
पूर्ण;

#अन्यथा /* CONFIG_PM_SLEEP */

अटल स्थिर काष्ठा dev_pm_ops ssam_serial_hub_pm_ops = अणु पूर्ण;

#पूर्ण_अगर /* CONFIG_PM_SLEEP */


/* -- Device/driver setup. -------------------------------------------------- */

अटल स्थिर काष्ठा acpi_gpio_params gpio_ssam_wakeup_पूर्णांक = अणु 0, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params gpio_ssam_wakeup     = अणु 1, 0, false पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping ssam_acpi_gpios[] = अणु
	अणु "ssam_wakeup-int-gpio", &gpio_ssam_wakeup_पूर्णांक, 1 पूर्ण,
	अणु "ssam_wakeup-gpio",     &gpio_ssam_wakeup,     1 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक ssam_serial_hub_probe(काष्ठा serdev_device *serdev)
अणु
	काष्ठा ssam_controller *ctrl;
	acpi_handle *ssh = ACPI_HANDLE(&serdev->dev);
	acpi_status astatus;
	पूर्णांक status;

	अगर (gpiod_count(&serdev->dev, शून्य) < 0)
		वापस -ENODEV;

	status = devm_acpi_dev_add_driver_gpios(&serdev->dev, ssam_acpi_gpios);
	अगर (status)
		वापस status;

	/* Allocate controller. */
	ctrl = kzalloc(माप(*ctrl), GFP_KERNEL);
	अगर (!ctrl)
		वापस -ENOMEM;

	/* Initialize controller. */
	status = ssam_controller_init(ctrl, serdev);
	अगर (status)
		जाओ err_ctrl_init;

	ssam_controller_lock(ctrl);

	/* Set up serdev device. */
	serdev_device_set_drvdata(serdev, ctrl);
	serdev_device_set_client_ops(serdev, &ssam_serdev_ops);
	status = serdev_device_खोलो(serdev);
	अगर (status)
		जाओ err_devखोलो;

	astatus = ssam_serdev_setup_via_acpi(ssh, serdev);
	अगर (ACPI_FAILURE(astatus)) अणु
		status = -ENXIO;
		जाओ err_devinit;
	पूर्ण

	/* Start controller. */
	status = ssam_controller_start(ctrl);
	अगर (status)
		जाओ err_devinit;

	ssam_controller_unlock(ctrl);

	/*
	 * Initial SAM requests: Log version and notअगरy शेष/init घातer
	 * states.
	 */
	status = ssam_log_firmware_version(ctrl);
	अगर (status)
		जाओ err_initrq;

	status = ssam_ctrl_notअगर_d0_entry(ctrl);
	अगर (status)
		जाओ err_initrq;

	status = ssam_ctrl_notअगर_display_on(ctrl);
	अगर (status)
		जाओ err_initrq;

	status = sysfs_create_group(&serdev->dev.kobj, &ssam_sam_group);
	अगर (status)
		जाओ err_initrq;

	/* Set up IRQ. */
	status = ssam_irq_setup(ctrl);
	अगर (status)
		जाओ err_irq;

	/* Finally, set मुख्य controller reference. */
	status = ssam_try_set_controller(ctrl);
	अगर (WARN_ON(status))	/* Currently, we're the only provider. */
		जाओ err_मुख्यref;

	/*
	 * TODO: The EC can wake up the प्रणाली via the associated GPIO पूर्णांकerrupt
	 *       in multiple situations. One of which is the reमुख्यing battery
	 *       capacity falling below a certain threshold. Normally, we should
	 *       use the device_init_wakeup function, however, the EC also seems
	 *       to have other reasons क्रम waking up the प्रणाली and it seems
	 *       that Winकरोws has additional checks whether the प्रणाली should be
	 *       resumed. In लघु, this causes some spurious unwanted wake-ups.
	 *       For now let's thus शेष घातer/wakeup to false.
	 */
	device_set_wakeup_capable(&serdev->dev, true);
	acpi_walk_dep_device_list(ssh);

	वापस 0;

err_मुख्यref:
	ssam_irq_मुक्त(ctrl);
err_irq:
	sysfs_हटाओ_group(&serdev->dev.kobj, &ssam_sam_group);
err_initrq:
	ssam_controller_lock(ctrl);
	ssam_controller_shutकरोwn(ctrl);
err_devinit:
	serdev_device_बंद(serdev);
err_devखोलो:
	ssam_controller_destroy(ctrl);
	ssam_controller_unlock(ctrl);
err_ctrl_init:
	kमुक्त(ctrl);
	वापस status;
पूर्ण

अटल व्योम ssam_serial_hub_हटाओ(काष्ठा serdev_device *serdev)
अणु
	काष्ठा ssam_controller *ctrl = serdev_device_get_drvdata(serdev);
	पूर्णांक status;

	/* Clear अटल reference so that no one अन्यथा can get a new one. */
	ssam_clear_controller();

	/* Disable and मुक्त IRQ. */
	ssam_irq_मुक्त(ctrl);

	sysfs_हटाओ_group(&serdev->dev.kobj, &ssam_sam_group);
	ssam_controller_lock(ctrl);

	/* Remove all client devices. */
	ssam_controller_हटाओ_clients(ctrl);

	/* Act as अगर suspending to silence events. */
	status = ssam_ctrl_notअगर_display_off(ctrl);
	अगर (status) अणु
		dev_err(&serdev->dev, "display-off notification failed: %d\n",
			status);
	पूर्ण

	status = ssam_ctrl_notअगर_d0_निकास(ctrl);
	अगर (status) अणु
		dev_err(&serdev->dev, "D0-exit notification failed: %d\n",
			status);
	पूर्ण

	/* Shut करोwn controller and हटाओ serdev device reference from it. */
	ssam_controller_shutकरोwn(ctrl);

	/* Shut करोwn actual transport. */
	serdev_device_रुको_until_sent(serdev, 0);
	serdev_device_बंद(serdev);

	/* Drop our controller reference. */
	ssam_controller_unlock(ctrl);
	ssam_controller_put(ctrl);

	device_set_wakeup_capable(&serdev->dev, false);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id ssam_serial_hub_match[] = अणु
	अणु "MSHW0084", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ssam_serial_hub_match);

अटल काष्ठा serdev_device_driver ssam_serial_hub = अणु
	.probe = ssam_serial_hub_probe,
	.हटाओ = ssam_serial_hub_हटाओ,
	.driver = अणु
		.name = "surface_serial_hub",
		.acpi_match_table = ssam_serial_hub_match,
		.pm = &ssam_serial_hub_pm_ops,
		.shutकरोwn = ssam_serial_hub_shutकरोwn,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;


/* -- Module setup. --------------------------------------------------------- */

अटल पूर्णांक __init ssam_core_init(व्योम)
अणु
	पूर्णांक status;

	status = ssam_bus_रेजिस्टर();
	अगर (status)
		जाओ err_bus;

	status = ssh_ctrl_packet_cache_init();
	अगर (status)
		जाओ err_cpkg;

	status = ssam_event_item_cache_init();
	अगर (status)
		जाओ err_evitem;

	status = serdev_device_driver_रेजिस्टर(&ssam_serial_hub);
	अगर (status)
		जाओ err_रेजिस्टर;

	वापस 0;

err_रेजिस्टर:
	ssam_event_item_cache_destroy();
err_evitem:
	ssh_ctrl_packet_cache_destroy();
err_cpkg:
	ssam_bus_unरेजिस्टर();
err_bus:
	वापस status;
पूर्ण
module_init(ssam_core_init);

अटल व्योम __निकास ssam_core_निकास(व्योम)
अणु
	serdev_device_driver_unरेजिस्टर(&ssam_serial_hub);
	ssam_event_item_cache_destroy();
	ssh_ctrl_packet_cache_destroy();
	ssam_bus_unरेजिस्टर();
पूर्ण
module_निकास(ssam_core_निकास);

MODULE_AUTHOR("Maximilian Luz <luzmaximilian@gmail.com>");
MODULE_DESCRIPTION("Subsystem and Surface Serial Hub driver for Surface System Aggregator Module");
MODULE_LICENSE("GPL");
