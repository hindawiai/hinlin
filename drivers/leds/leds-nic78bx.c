<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2016 National Instruments Corp.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>

#घोषणा NIC78BX_USER1_LED_MASK		0x3
#घोषणा NIC78BX_USER1_GREEN_LED		BIT(0)
#घोषणा NIC78BX_USER1_YELLOW_LED	BIT(1)

#घोषणा NIC78BX_USER2_LED_MASK		0xC
#घोषणा NIC78BX_USER2_GREEN_LED		BIT(2)
#घोषणा NIC78BX_USER2_YELLOW_LED	BIT(3)

#घोषणा NIC78BX_LOCK_REG_OFFSET		1
#घोषणा NIC78BX_LOCK_VALUE		0xA5
#घोषणा NIC78BX_UNLOCK_VALUE		0x5A

#घोषणा NIC78BX_USER_LED_IO_SIZE	2

काष्ठा nic78bx_led_data अणु
	u16 io_base;
	spinlock_t lock;
	काष्ठा platक्रमm_device *pdev;
पूर्ण;

काष्ठा nic78bx_led अणु
	u8 bit;
	u8 mask;
	काष्ठा nic78bx_led_data *data;
	काष्ठा led_classdev cdev;
पूर्ण;

अटल अंतरभूत काष्ठा nic78bx_led *to_nic78bx_led(काष्ठा led_classdev *cdev)
अणु
	वापस container_of(cdev, काष्ठा nic78bx_led, cdev);
पूर्ण

अटल व्योम nic78bx_brightness_set(काष्ठा led_classdev *cdev,
				  क्रमागत led_brightness brightness)
अणु
	काष्ठा nic78bx_led *nled = to_nic78bx_led(cdev);
	अचिन्हित दीर्घ flags;
	u8 value;

	spin_lock_irqsave(&nled->data->lock, flags);
	value = inb(nled->data->io_base);

	अगर (brightness) अणु
		value &= ~nled->mask;
		value |= nled->bit;
	पूर्ण अन्यथा अणु
		value &= ~nled->bit;
	पूर्ण

	outb(value, nled->data->io_base);
	spin_unlock_irqrestore(&nled->data->lock, flags);
पूर्ण

अटल क्रमागत led_brightness nic78bx_brightness_get(काष्ठा led_classdev *cdev)
अणु
	काष्ठा nic78bx_led *nled = to_nic78bx_led(cdev);
	अचिन्हित दीर्घ flags;
	u8 value;

	spin_lock_irqsave(&nled->data->lock, flags);
	value = inb(nled->data->io_base);
	spin_unlock_irqrestore(&nled->data->lock, flags);

	वापस (value & nled->bit) ? 1 : LED_OFF;
पूर्ण

अटल काष्ठा nic78bx_led nic78bx_leds[] = अणु
	अणु
		.bit = NIC78BX_USER1_GREEN_LED,
		.mask = NIC78BX_USER1_LED_MASK,
		.cdev = अणु
			.name = "nilrt:green:user1",
			.max_brightness = 1,
			.brightness_set = nic78bx_brightness_set,
			.brightness_get = nic78bx_brightness_get,
		पूर्ण
	पूर्ण,
	अणु
		.bit = NIC78BX_USER1_YELLOW_LED,
		.mask = NIC78BX_USER1_LED_MASK,
		.cdev = अणु
			.name = "nilrt:yellow:user1",
			.max_brightness = 1,
			.brightness_set = nic78bx_brightness_set,
			.brightness_get = nic78bx_brightness_get,
		पूर्ण
	पूर्ण,
	अणु
		.bit = NIC78BX_USER2_GREEN_LED,
		.mask = NIC78BX_USER2_LED_MASK,
		.cdev = अणु
			.name = "nilrt:green:user2",
			.max_brightness = 1,
			.brightness_set = nic78bx_brightness_set,
			.brightness_get = nic78bx_brightness_get,
		पूर्ण
	पूर्ण,
	अणु
		.bit = NIC78BX_USER2_YELLOW_LED,
		.mask = NIC78BX_USER2_LED_MASK,
		.cdev = अणु
			.name = "nilrt:yellow:user2",
			.max_brightness = 1,
			.brightness_set = nic78bx_brightness_set,
			.brightness_get = nic78bx_brightness_get,
		पूर्ण
	पूर्ण
पूर्ण;

अटल पूर्णांक nic78bx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा nic78bx_led_data *led_data;
	काष्ठा resource *io_rc;
	पूर्णांक ret, i;

	led_data = devm_kzalloc(dev, माप(*led_data), GFP_KERNEL);
	अगर (!led_data)
		वापस -ENOMEM;

	led_data->pdev = pdev;
	platक्रमm_set_drvdata(pdev, led_data);

	io_rc = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!io_rc) अणु
		dev_err(dev, "missing IO resources\n");
		वापस -EINVAL;
	पूर्ण

	अगर (resource_size(io_rc) < NIC78BX_USER_LED_IO_SIZE) अणु
		dev_err(dev, "IO region too small\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!devm_request_region(dev, io_rc->start, resource_size(io_rc),
				 KBUILD_MODNAME)) अणु
		dev_err(dev, "failed to get IO region\n");
		वापस -EBUSY;
	पूर्ण

	led_data->io_base = io_rc->start;
	spin_lock_init(&led_data->lock);

	क्रम (i = 0; i < ARRAY_SIZE(nic78bx_leds); i++) अणु
		nic78bx_leds[i].data = led_data;

		ret = devm_led_classdev_रेजिस्टर(dev, &nic78bx_leds[i].cdev);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Unlock LED रेजिस्टर */
	outb(NIC78BX_UNLOCK_VALUE,
	     led_data->io_base + NIC78BX_LOCK_REG_OFFSET);

	वापस ret;
पूर्ण

अटल पूर्णांक nic78bx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा nic78bx_led_data *led_data = platक्रमm_get_drvdata(pdev);

	/* Lock LED रेजिस्टर */
	outb(NIC78BX_LOCK_VALUE,
	     led_data->io_base + NIC78BX_LOCK_REG_OFFSET);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id led_device_ids[] = अणु
	अणु"NIC78B3", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, led_device_ids);

अटल काष्ठा platक्रमm_driver led_driver = अणु
	.probe = nic78bx_probe,
	.हटाओ = nic78bx_हटाओ,
	.driver = अणु
		.name = KBUILD_MODNAME,
		.acpi_match_table = ACPI_PTR(led_device_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(led_driver);

MODULE_DESCRIPTION("National Instruments PXI User LEDs driver");
MODULE_AUTHOR("Hui Chun Ong <hui.chun.ong@ni.com>");
MODULE_LICENSE("GPL");
