<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Surface Book (2 and later) hot-plug driver.
 *
 * Surface Book devices (can) have a hot-pluggable discrete GPU (dGPU). This
 * driver is responsible क्रम out-of-band hot-plug event संकेतing on these
 * devices. It is specअगरically required when the hot-plug device is in D3cold
 * and can thus not generate PCIe hot-plug events itself.
 *
 * Event संकेतing is handled via ACPI, which will generate the appropriate
 * device-check notअगरications to be picked up by the PCIe hot-plug driver.
 *
 * Copyright (C) 2019-2021 Maximilian Luz <luzmaximilian@gmail.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>

अटल स्थिर काष्ठा acpi_gpio_params shps_base_presence_पूर्णांक   = अणु 0, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params shps_base_presence       = अणु 1, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params shps_device_घातer_पूर्णांक    = अणु 2, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params shps_device_घातer        = अणु 3, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params shps_device_presence_पूर्णांक = अणु 4, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params shps_device_presence     = अणु 5, 0, false पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping shps_acpi_gpios[] = अणु
	अणु "base_presence-int-gpio",   &shps_base_presence_पूर्णांक,   1 पूर्ण,
	अणु "base_presence-gpio",       &shps_base_presence,       1 पूर्ण,
	अणु "device_power-int-gpio",    &shps_device_घातer_पूर्णांक,    1 पूर्ण,
	अणु "device_power-gpio",        &shps_device_घातer,        1 पूर्ण,
	अणु "device_presence-int-gpio", &shps_device_presence_पूर्णांक, 1 पूर्ण,
	अणु "device_presence-gpio",     &shps_device_presence,     1 पूर्ण,
	अणु पूर्ण,
पूर्ण;

/* 5515a847-ed55-4b27-8352-cd320e10360a */
अटल स्थिर guid_t shps_dsm_guid =
	GUID_INIT(0x5515a847, 0xed55, 0x4b27, 0x83, 0x52, 0xcd, 0x32, 0x0e, 0x10, 0x36, 0x0a);

#घोषणा SHPS_DSM_REVISION		1

क्रमागत shps_dsm_fn अणु
	SHPS_DSM_FN_PCI_NUM_ENTRIES	= 0x01,
	SHPS_DSM_FN_PCI_GET_ENTRIES	= 0x02,
	SHPS_DSM_FN_IRQ_BASE_PRESENCE	= 0x03,
	SHPS_DSM_FN_IRQ_DEVICE_POWER	= 0x04,
	SHPS_DSM_FN_IRQ_DEVICE_PRESENCE	= 0x05,
पूर्ण;

क्रमागत shps_irq_type अणु
	/* NOTE: Must be in order of क्रमागत shps_dsm_fn above. */
	SHPS_IRQ_TYPE_BASE_PRESENCE	= 0,
	SHPS_IRQ_TYPE_DEVICE_POWER	= 1,
	SHPS_IRQ_TYPE_DEVICE_PRESENCE	= 2,
	SHPS_NUM_IRQS,
पूर्ण;

अटल स्थिर अक्षर *स्थिर shps_gpio_names[] = अणु
	[SHPS_IRQ_TYPE_BASE_PRESENCE]	= "base_presence",
	[SHPS_IRQ_TYPE_DEVICE_POWER]	= "device_power",
	[SHPS_IRQ_TYPE_DEVICE_PRESENCE]	= "device_presence",
पूर्ण;

काष्ठा shps_device अणु
	काष्ठा mutex lock[SHPS_NUM_IRQS];  /* Protects update in shps_dsm_notअगरy_irq() */
	काष्ठा gpio_desc *gpio[SHPS_NUM_IRQS];
	अचिन्हित पूर्णांक irq[SHPS_NUM_IRQS];
पूर्ण;

#घोषणा SHPS_IRQ_NOT_PRESENT		((अचिन्हित पूर्णांक)-1)

अटल क्रमागत shps_dsm_fn shps_dsm_fn_क्रम_irq(क्रमागत shps_irq_type type)
अणु
	वापस SHPS_DSM_FN_IRQ_BASE_PRESENCE + type;
पूर्ण

अटल व्योम shps_dsm_notअगरy_irq(काष्ठा platक्रमm_device *pdev, क्रमागत shps_irq_type type)
अणु
	काष्ठा shps_device *sdev = platक्रमm_get_drvdata(pdev);
	acpi_handle handle = ACPI_HANDLE(&pdev->dev);
	जोड़ acpi_object *result;
	जोड़ acpi_object param;
	पूर्णांक value;

	mutex_lock(&sdev->lock[type]);

	value = gpiod_get_value_cansleep(sdev->gpio[type]);
	अगर (value < 0) अणु
		mutex_unlock(&sdev->lock[type]);
		dev_err(&pdev->dev, "failed to get gpio: %d (irq=%d)\n", type, value);
		वापस;
	पूर्ण

	dev_dbg(&pdev->dev, "IRQ notification via DSM (irq=%d, value=%d)\n", type, value);

	param.type = ACPI_TYPE_INTEGER;
	param.पूर्णांकeger.value = value;

	result = acpi_evaluate_dsm(handle, &shps_dsm_guid, SHPS_DSM_REVISION,
				   shps_dsm_fn_क्रम_irq(type), &param);

	अगर (!result) अणु
		dev_err(&pdev->dev, "IRQ notification via DSM failed (irq=%d, gpio=%d)\n",
			type, value);

	पूर्ण अन्यथा अगर (result->type != ACPI_TYPE_BUFFER) अणु
		dev_err(&pdev->dev,
			"IRQ notification via DSM failed: unexpected result type (irq=%d, gpio=%d)\n",
			type, value);

	पूर्ण अन्यथा अगर (result->buffer.length != 1 || result->buffer.poपूर्णांकer[0] != 0) अणु
		dev_err(&pdev->dev,
			"IRQ notification via DSM failed: unexpected result value (irq=%d, gpio=%d)\n",
			type, value);
	पूर्ण

	mutex_unlock(&sdev->lock[type]);

	अगर (result)
		ACPI_FREE(result);
पूर्ण

अटल irqवापस_t shps_handle_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = data;
	काष्ठा shps_device *sdev = platक्रमm_get_drvdata(pdev);
	पूर्णांक type;

	/* Figure out which IRQ we're handling. */
	क्रम (type = 0; type < SHPS_NUM_IRQS; type++)
		अगर (irq == sdev->irq[type])
			अवरोध;

	/* We should have found our पूर्णांकerrupt, अगर not: this is a bug. */
	अगर (WARN(type >= SHPS_NUM_IRQS, "invalid IRQ number: %d\n", irq))
		वापस IRQ_HANDLED;

	/* Forward पूर्णांकerrupt to ACPI via DSM. */
	shps_dsm_notअगरy_irq(pdev, type);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक shps_setup_irq(काष्ठा platक्रमm_device *pdev, क्रमागत shps_irq_type type)
अणु
	अचिन्हित दीर्घ flags = IRQF_ONESHOT | IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING;
	काष्ठा shps_device *sdev = platक्रमm_get_drvdata(pdev);
	काष्ठा gpio_desc *gpiod;
	acpi_handle handle = ACPI_HANDLE(&pdev->dev);
	स्थिर अक्षर *irq_name;
	स्थिर पूर्णांक dsm = shps_dsm_fn_क्रम_irq(type);
	पूर्णांक status, irq;

	/*
	 * Only set up पूर्णांकerrupts that we actually need: The Surface Book 3
	 * करोes not have a DSM क्रम base presence, so करोn't set up an पूर्णांकerrupt
	 * क्रम that.
	 */
	अगर (!acpi_check_dsm(handle, &shps_dsm_guid, SHPS_DSM_REVISION, BIT(dsm))) अणु
		dev_dbg(&pdev->dev, "IRQ notification via DSM not present (irq=%d)\n", type);
		वापस 0;
	पूर्ण

	gpiod = devm_gpiod_get(&pdev->dev, shps_gpio_names[type], GPIOD_ASIS);
	अगर (IS_ERR(gpiod))
		वापस PTR_ERR(gpiod);

	irq = gpiod_to_irq(gpiod);
	अगर (irq < 0)
		वापस irq;

	irq_name = devm_kaप्र_लिखो(&pdev->dev, GFP_KERNEL, "shps-irq-%d", type);
	अगर (!irq_name)
		वापस -ENOMEM;

	status = devm_request_thपढ़ोed_irq(&pdev->dev, irq, शून्य, shps_handle_irq,
					   flags, irq_name, pdev);
	अगर (status)
		वापस status;

	dev_dbg(&pdev->dev, "set up irq %d as type %d\n", irq, type);

	sdev->gpio[type] = gpiod;
	sdev->irq[type] = irq;

	वापस 0;
पूर्ण

अटल पूर्णांक surface_hotplug_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा shps_device *sdev = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	/* Ensure that IRQs have been fully handled and won't trigger any more. */
	क्रम (i = 0; i < SHPS_NUM_IRQS; i++) अणु
		अगर (sdev->irq[i] != SHPS_IRQ_NOT_PRESENT)
			disable_irq(sdev->irq[i]);

		mutex_destroy(&sdev->lock[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक surface_hotplug_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा shps_device *sdev;
	पूर्णांक status, i;

	/*
	 * The MSHW0153 device is also present on the Surface Laptop 3,
	 * however that करोesn't have a hot-pluggable PCIe device. It also
	 * करोesn't have any GPIO पूर्णांकerrupts/pins under the MSHW0153, so filter
	 * it out here.
	 */
	अगर (gpiod_count(&pdev->dev, शून्य) < 0)
		वापस -ENODEV;

	status = devm_acpi_dev_add_driver_gpios(&pdev->dev, shps_acpi_gpios);
	अगर (status)
		वापस status;

	sdev = devm_kzalloc(&pdev->dev, माप(*sdev), GFP_KERNEL);
	अगर (!sdev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, sdev);

	/*
	 * Initialize IRQs so that we can safely call surface_hotplug_हटाओ()
	 * on errors.
	 */
	क्रम (i = 0; i < SHPS_NUM_IRQS; i++)
		sdev->irq[i] = SHPS_IRQ_NOT_PRESENT;

	/* Set up IRQs. */
	क्रम (i = 0; i < SHPS_NUM_IRQS; i++) अणु
		mutex_init(&sdev->lock[i]);

		status = shps_setup_irq(pdev, i);
		अगर (status) अणु
			dev_err(&pdev->dev, "failed to set up IRQ %d: %d\n", i, status);
			जाओ err;
		पूर्ण
	पूर्ण

	/* Ensure everything is up-to-date. */
	क्रम (i = 0; i < SHPS_NUM_IRQS; i++)
		अगर (sdev->irq[i] != SHPS_IRQ_NOT_PRESENT)
			shps_dsm_notअगरy_irq(pdev, i);

	वापस 0;

err:
	surface_hotplug_हटाओ(pdev);
	वापस status;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id surface_hotplug_acpi_match[] = अणु
	अणु "MSHW0153", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, surface_hotplug_acpi_match);

अटल काष्ठा platक्रमm_driver surface_hotplug_driver = अणु
	.probe = surface_hotplug_probe,
	.हटाओ = surface_hotplug_हटाओ,
	.driver = अणु
		.name = "surface_hotplug",
		.acpi_match_table = surface_hotplug_acpi_match,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(surface_hotplug_driver);

MODULE_AUTHOR("Maximilian Luz <luzmaximilian@gmail.com>");
MODULE_DESCRIPTION("Surface Hot-Plug Signaling Driver for Surface Book Devices");
MODULE_LICENSE("GPL");
