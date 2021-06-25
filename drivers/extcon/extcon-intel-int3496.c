<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel INT3496 ACPI device extcon driver
 *
 * Copyright (c) 2016 Hans de Goede <hdegoede@redhat.com>
 *
 * Based on android x86 kernel code which is:
 *
 * Copyright (c) 2014, Intel Corporation.
 * Author: David Cohen <david.a.cohen@linux.पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/devm-helpers.h>
#समावेश <linux/extcon-provider.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा INT3496_GPIO_USB_ID	0
#घोषणा INT3496_GPIO_VBUS_EN	1
#घोषणा INT3496_GPIO_USB_MUX	2
#घोषणा DEBOUNCE_TIME		msecs_to_jअगरfies(50)

काष्ठा पूर्णांक3496_data अणु
	काष्ठा device *dev;
	काष्ठा extcon_dev *edev;
	काष्ठा delayed_work work;
	काष्ठा gpio_desc *gpio_usb_id;
	काष्ठा gpio_desc *gpio_vbus_en;
	काष्ठा gpio_desc *gpio_usb_mux;
	पूर्णांक usb_id_irq;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक पूर्णांक3496_cable[] = अणु
	EXTCON_USB_HOST,
	EXTCON_NONE,
पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_params id_gpios = अणु INT3496_GPIO_USB_ID, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params vbus_gpios = अणु INT3496_GPIO_VBUS_EN, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params mux_gpios = अणु INT3496_GPIO_USB_MUX, 0, false पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping acpi_पूर्णांक3496_शेष_gpios[] = अणु
	/*
	 * Some platक्रमms have a bug in ACPI GPIO description making IRQ
	 * GPIO to be output only. Ask the GPIO core to ignore this limit.
	 */
	अणु "id-gpios", &id_gpios, 1, ACPI_GPIO_QUIRK_NO_IO_RESTRICTION पूर्ण,
	अणु "vbus-gpios", &vbus_gpios, 1 पूर्ण,
	अणु "mux-gpios", &mux_gpios, 1 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल व्योम पूर्णांक3496_करो_usb_id(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा पूर्णांक3496_data *data =
		container_of(work, काष्ठा पूर्णांक3496_data, work.work);
	पूर्णांक id = gpiod_get_value_cansleep(data->gpio_usb_id);

	/* id == 1: PERIPHERAL, id == 0: HOST */
	dev_dbg(data->dev, "Connected %s cable\n", id ? "PERIPHERAL" : "HOST");

	/*
	 * Peripheral: set USB mux to peripheral and disable VBUS
	 * Host: set USB mux to host and enable VBUS
	 */
	अगर (!IS_ERR(data->gpio_usb_mux))
		gpiod_direction_output(data->gpio_usb_mux, id);

	अगर (!IS_ERR(data->gpio_vbus_en))
		gpiod_direction_output(data->gpio_vbus_en, !id);

	extcon_set_state_sync(data->edev, EXTCON_USB_HOST, !id);
पूर्ण

अटल irqवापस_t पूर्णांक3496_thपढ़ो_isr(पूर्णांक irq, व्योम *priv)
अणु
	काष्ठा पूर्णांक3496_data *data = priv;

	/* Let the pin settle beक्रमe processing it */
	mod_delayed_work(प्रणाली_wq, &data->work, DEBOUNCE_TIME);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक पूर्णांक3496_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा पूर्णांक3496_data *data;
	पूर्णांक ret;

	ret = devm_acpi_dev_add_driver_gpios(dev, acpi_पूर्णांक3496_शेष_gpios);
	अगर (ret) अणु
		dev_err(dev, "can't add GPIO ACPI mapping\n");
		वापस ret;
	पूर्ण

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->dev = dev;
	ret = devm_delayed_work_स्वतःcancel(dev, &data->work, पूर्णांक3496_करो_usb_id);
	अगर (ret)
		वापस ret;

	data->gpio_usb_id = devm_gpiod_get(dev, "id", GPIOD_IN);
	अगर (IS_ERR(data->gpio_usb_id)) अणु
		ret = PTR_ERR(data->gpio_usb_id);
		dev_err(dev, "can't request USB ID GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	data->usb_id_irq = gpiod_to_irq(data->gpio_usb_id);
	अगर (data->usb_id_irq < 0) अणु
		dev_err(dev, "can't get USB ID IRQ: %d\n", data->usb_id_irq);
		वापस data->usb_id_irq;
	पूर्ण

	data->gpio_vbus_en = devm_gpiod_get(dev, "vbus", GPIOD_ASIS);
	अगर (IS_ERR(data->gpio_vbus_en))
		dev_info(dev, "can't request VBUS EN GPIO\n");

	data->gpio_usb_mux = devm_gpiod_get(dev, "mux", GPIOD_ASIS);
	अगर (IS_ERR(data->gpio_usb_mux))
		dev_info(dev, "can't request USB MUX GPIO\n");

	/* रेजिस्टर extcon device */
	data->edev = devm_extcon_dev_allocate(dev, पूर्णांक3496_cable);
	अगर (IS_ERR(data->edev))
		वापस -ENOMEM;

	ret = devm_extcon_dev_रेजिस्टर(dev, data->edev);
	अगर (ret < 0) अणु
		dev_err(dev, "can't register extcon device: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(dev, data->usb_id_irq,
					शून्य, पूर्णांक3496_thपढ़ो_isr,
					IRQF_SHARED | IRQF_ONESHOT |
					IRQF_TRIGGER_RISING |
					IRQF_TRIGGER_FALLING,
					dev_name(dev), data);
	अगर (ret < 0) अणु
		dev_err(dev, "can't request IRQ for USB ID GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	/* process id-pin so that we start with the right status */
	queue_delayed_work(प्रणाली_wq, &data->work, 0);
	flush_delayed_work(&data->work);

	platक्रमm_set_drvdata(pdev, data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id पूर्णांक3496_acpi_match[] = अणु
	अणु "INT3496" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, पूर्णांक3496_acpi_match);

अटल काष्ठा platक्रमm_driver पूर्णांक3496_driver = अणु
	.driver = अणु
		.name = "intel-int3496",
		.acpi_match_table = पूर्णांक3496_acpi_match,
	पूर्ण,
	.probe = पूर्णांक3496_probe,
पूर्ण;

module_platक्रमm_driver(पूर्णांक3496_driver);

MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_DESCRIPTION("Intel INT3496 ACPI device extcon driver");
MODULE_LICENSE("GPL v2");
