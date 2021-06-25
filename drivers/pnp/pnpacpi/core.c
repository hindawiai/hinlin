<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * pnpacpi -- PnP ACPI driver
 *
 * Copyright (c) 2004 Matthieu Castet <castet.matthieu@मुक्त.fr>
 * Copyright (c) 2004 Li Shaohua <shaohua.li@पूर्णांकel.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pnp.h>
#समावेश <linux/slab.h>
#समावेश <linux/mod_devicetable.h>

#समावेश "../base.h"
#समावेश "pnpacpi.h"

अटल पूर्णांक num;

/*
 * Compatible Device IDs
 */
#घोषणा TEST_HEX(c) \
	अगर (!(('0' <= (c) && (c) <= '9') || ('A' <= (c) && (c) <= 'F'))) \
		वापस 0
#घोषणा TEST_ALPHA(c) \
	अगर (!('A' <= (c) && (c) <= 'Z')) \
		वापस 0
अटल पूर्णांक __init ispnpidacpi(स्थिर अक्षर *id)
अणु
	TEST_ALPHA(id[0]);
	TEST_ALPHA(id[1]);
	TEST_ALPHA(id[2]);
	TEST_HEX(id[3]);
	TEST_HEX(id[4]);
	TEST_HEX(id[5]);
	TEST_HEX(id[6]);
	अगर (id[7] != '\0')
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक pnpacpi_get_resources(काष्ठा pnp_dev *dev)
अणु
	pnp_dbg(&dev->dev, "get resources\n");
	वापस pnpacpi_parse_allocated_resource(dev);
पूर्ण

अटल पूर्णांक pnpacpi_set_resources(काष्ठा pnp_dev *dev)
अणु
	काष्ठा acpi_device *acpi_dev;
	acpi_handle handle;
	पूर्णांक ret = 0;

	pnp_dbg(&dev->dev, "set resources\n");

	acpi_dev = ACPI_COMPANION(&dev->dev);
	अगर (!acpi_dev) अणु
		dev_dbg(&dev->dev, "ACPI device not found in %s!\n", __func__);
		वापस -ENODEV;
	पूर्ण

	अगर (WARN_ON_ONCE(acpi_dev != dev->data))
		dev->data = acpi_dev;

	handle = acpi_dev->handle;
	अगर (acpi_has_method(handle, METHOD_NAME__SRS)) अणु
		काष्ठा acpi_buffer buffer;

		ret = pnpacpi_build_resource_ढाँचा(dev, &buffer);
		अगर (ret)
			वापस ret;

		ret = pnpacpi_encode_resources(dev, &buffer);
		अगर (!ret) अणु
			acpi_status status;

			status = acpi_set_current_resources(handle, &buffer);
			अगर (ACPI_FAILURE(status))
				ret = -EIO;
		पूर्ण
		kमुक्त(buffer.poपूर्णांकer);
	पूर्ण
	अगर (!ret && acpi_device_घातer_manageable(acpi_dev))
		ret = acpi_device_set_घातer(acpi_dev, ACPI_STATE_D0);

	वापस ret;
पूर्ण

अटल पूर्णांक pnpacpi_disable_resources(काष्ठा pnp_dev *dev)
अणु
	काष्ठा acpi_device *acpi_dev;
	acpi_status status;

	dev_dbg(&dev->dev, "disable resources\n");

	acpi_dev = ACPI_COMPANION(&dev->dev);
	अगर (!acpi_dev) अणु
		dev_dbg(&dev->dev, "ACPI device not found in %s!\n", __func__);
		वापस 0;
	पूर्ण

	/* acpi_unरेजिस्टर_gsi(pnp_irq(dev, 0)); */
	अगर (acpi_device_घातer_manageable(acpi_dev))
		acpi_device_set_घातer(acpi_dev, ACPI_STATE_D3_COLD);

	/* जारी even अगर acpi_device_set_घातer() fails */
	status = acpi_evaluate_object(acpi_dev->handle, "_DIS", शून्य, शून्य);
	अगर (ACPI_FAILURE(status) && status != AE_NOT_FOUND)
		वापस -ENODEV;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI_SLEEP
अटल bool pnpacpi_can_wakeup(काष्ठा pnp_dev *dev)
अणु
	काष्ठा acpi_device *acpi_dev = ACPI_COMPANION(&dev->dev);

	अगर (!acpi_dev) अणु
		dev_dbg(&dev->dev, "ACPI device not found in %s!\n", __func__);
		वापस false;
	पूर्ण

	वापस acpi_bus_can_wakeup(acpi_dev->handle);
पूर्ण

अटल पूर्णांक pnpacpi_suspend(काष्ठा pnp_dev *dev, pm_message_t state)
अणु
	काष्ठा acpi_device *acpi_dev = ACPI_COMPANION(&dev->dev);
	पूर्णांक error = 0;

	अगर (!acpi_dev) अणु
		dev_dbg(&dev->dev, "ACPI device not found in %s!\n", __func__);
		वापस 0;
	पूर्ण

	अगर (device_can_wakeup(&dev->dev)) अणु
		error = acpi_pm_set_device_wakeup(&dev->dev,
					      device_may_wakeup(&dev->dev));
		अगर (error)
			वापस error;
	पूर्ण

	अगर (acpi_device_घातer_manageable(acpi_dev)) अणु
		पूर्णांक घातer_state = acpi_pm_device_sleep_state(&dev->dev, शून्य,
							ACPI_STATE_D3_COLD);
		अगर (घातer_state < 0)
			घातer_state = (state.event == PM_EVENT_ON) ?
					ACPI_STATE_D0 : ACPI_STATE_D3_COLD;

		/*
		 * acpi_device_set_घातer() can fail (keyboard port can't be
		 * घातered-करोwn?), and in any हाल, our वापस value is ignored
		 * by pnp_bus_suspend().  Hence we करोn't revert the wakeup
		 * setting अगर the set_घातer fails.
		 */
		error = acpi_device_set_घातer(acpi_dev, घातer_state);
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक pnpacpi_resume(काष्ठा pnp_dev *dev)
अणु
	काष्ठा acpi_device *acpi_dev = ACPI_COMPANION(&dev->dev);
	पूर्णांक error = 0;

	अगर (!acpi_dev) अणु
		dev_dbg(&dev->dev, "ACPI device not found in %s!\n", __func__);
		वापस -ENODEV;
	पूर्ण

	अगर (device_may_wakeup(&dev->dev))
		acpi_pm_set_device_wakeup(&dev->dev, false);

	अगर (acpi_device_घातer_manageable(acpi_dev))
		error = acpi_device_set_घातer(acpi_dev, ACPI_STATE_D0);

	वापस error;
पूर्ण
#पूर्ण_अगर

काष्ठा pnp_protocol pnpacpi_protocol = अणु
	.name	 = "Plug and Play ACPI",
	.get	 = pnpacpi_get_resources,
	.set	 = pnpacpi_set_resources,
	.disable = pnpacpi_disable_resources,
#अगर_घोषित CONFIG_ACPI_SLEEP
	.can_wakeup = pnpacpi_can_wakeup,
	.suspend = pnpacpi_suspend,
	.resume = pnpacpi_resume,
#पूर्ण_अगर
पूर्ण;
EXPORT_SYMBOL(pnpacpi_protocol);

अटल स्थिर अक्षर *__init pnpacpi_get_id(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_hardware_id *id;

	list_क्रम_each_entry(id, &device->pnp.ids, list) अणु
		अगर (ispnpidacpi(id->id))
			वापस id->id;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक __init pnpacpi_add_device(काष्ठा acpi_device *device)
अणु
	काष्ठा pnp_dev *dev;
	स्थिर अक्षर *pnpid;
	काष्ठा acpi_hardware_id *id;
	पूर्णांक error;

	/* Skip devices that are alपढ़ोy bound */
	अगर (device->physical_node_count)
		वापस 0;

	/*
	 * If a PnPacpi device is not present , the device
	 * driver should not be loaded.
	 */
	अगर (!acpi_has_method(device->handle, "_CRS"))
		वापस 0;

	pnpid = pnpacpi_get_id(device);
	अगर (!pnpid)
		वापस 0;

	अगर (!device->status.present)
		वापस 0;

	dev = pnp_alloc_dev(&pnpacpi_protocol, num, pnpid);
	अगर (!dev)
		वापस -ENOMEM;

	ACPI_COMPANION_SET(&dev->dev, device);
	dev->data = device;
	/* .enabled means the device can decode the resources */
	dev->active = device->status.enabled;
	अगर (acpi_has_method(device->handle, "_SRS"))
		dev->capabilities |= PNP_CONFIGURABLE;
	dev->capabilities |= PNP_READ;
	अगर (device->flags.dynamic_status && (dev->capabilities & PNP_CONFIGURABLE))
		dev->capabilities |= PNP_WRITE;
	अगर (device->flags.removable)
		dev->capabilities |= PNP_REMOVABLE;
	अगर (acpi_has_method(device->handle, "_DIS"))
		dev->capabilities |= PNP_DISABLE;

	अगर (म_माप(acpi_device_name(device)))
		म_नकलन(dev->name, acpi_device_name(device), माप(dev->name));
	अन्यथा
		म_नकलन(dev->name, acpi_device_bid(device), माप(dev->name));

	अगर (dev->active)
		pnpacpi_parse_allocated_resource(dev);

	अगर (dev->capabilities & PNP_CONFIGURABLE)
		pnpacpi_parse_resource_option_data(dev);

	list_क्रम_each_entry(id, &device->pnp.ids, list) अणु
		अगर (!म_भेद(id->id, pnpid))
			जारी;
		अगर (!ispnpidacpi(id->id))
			जारी;
		pnp_add_id(dev, id->id);
	पूर्ण

	/* clear out the damaged flags */
	अगर (!dev->active)
		pnp_init_resources(dev);

	error = pnp_add_device(dev);
	अगर (error) अणु
		put_device(&dev->dev);
		वापस error;
	पूर्ण

	num++;

	वापस 0;
पूर्ण

अटल acpi_status __init pnpacpi_add_device_handler(acpi_handle handle,
						     u32 lvl, व्योम *context,
						     व्योम **rv)
अणु
	काष्ठा acpi_device *device;

	अगर (acpi_bus_get_device(handle, &device))
		वापस AE_CTRL_DEPTH;
	अगर (acpi_is_pnp_device(device))
		pnpacpi_add_device(device);
	वापस AE_OK;
पूर्ण

पूर्णांक pnpacpi_disabled __initdata;
अटल पूर्णांक __init pnpacpi_init(व्योम)
अणु
	अगर (acpi_disabled || pnpacpi_disabled) अणु
		prपूर्णांकk(KERN_INFO "pnp: PnP ACPI: disabled\n");
		वापस 0;
	पूर्ण
	prपूर्णांकk(KERN_INFO "pnp: PnP ACPI init\n");
	pnp_रेजिस्टर_protocol(&pnpacpi_protocol);
	acpi_get_devices(शून्य, pnpacpi_add_device_handler, शून्य, शून्य);
	prपूर्णांकk(KERN_INFO "pnp: PnP ACPI: found %d devices\n", num);
	pnp_platक्रमm_devices = 1;
	वापस 0;
पूर्ण

fs_initcall(pnpacpi_init);

अटल पूर्णांक __init pnpacpi_setup(अक्षर *str)
अणु
	अगर (str == शून्य)
		वापस 1;
	अगर (!म_भेदन(str, "off", 3))
		pnpacpi_disabled = 1;
	वापस 1;
पूर्ण

__setup("pnpacpi=", pnpacpi_setup);
