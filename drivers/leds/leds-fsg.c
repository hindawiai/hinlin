<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * LED Driver क्रम the Freecom FSG-3
 *
 * Copyright (c) 2008 Rod Whitby <rod@whitby.id.au>
 *
 * Author: Rod Whitby <rod@whitby.id.au>
 *
 * Based on leds-spitz.c
 * Copyright 2005-2006 Openedhand Ltd.
 * Author: Riअक्षरd Purdie <rpurdie@खोलोedhand.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/leds.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <mach/hardware.h>

#घोषणा FSG_LED_WLAN_BIT	0
#घोषणा FSG_LED_WAN_BIT		1
#घोषणा FSG_LED_SATA_BIT	2
#घोषणा FSG_LED_USB_BIT		4
#घोषणा FSG_LED_RING_BIT	5
#घोषणा FSG_LED_SYNC_BIT	7

अटल लघु __iomem *latch_address;
अटल अचिन्हित लघु latch_value;


अटल व्योम fsg_led_wlan_set(काष्ठा led_classdev *led_cdev,
			     क्रमागत led_brightness value)
अणु
	अगर (value) अणु
		latch_value &= ~(1 << FSG_LED_WLAN_BIT);
		*latch_address = latch_value;
	पूर्ण अन्यथा अणु
		latch_value |=  (1 << FSG_LED_WLAN_BIT);
		*latch_address = latch_value;
	पूर्ण
पूर्ण

अटल व्योम fsg_led_wan_set(काष्ठा led_classdev *led_cdev,
			    क्रमागत led_brightness value)
अणु
	अगर (value) अणु
		latch_value &= ~(1 << FSG_LED_WAN_BIT);
		*latch_address = latch_value;
	पूर्ण अन्यथा अणु
		latch_value |=  (1 << FSG_LED_WAN_BIT);
		*latch_address = latch_value;
	पूर्ण
पूर्ण

अटल व्योम fsg_led_sata_set(काष्ठा led_classdev *led_cdev,
			     क्रमागत led_brightness value)
अणु
	अगर (value) अणु
		latch_value &= ~(1 << FSG_LED_SATA_BIT);
		*latch_address = latch_value;
	पूर्ण अन्यथा अणु
		latch_value |=  (1 << FSG_LED_SATA_BIT);
		*latch_address = latch_value;
	पूर्ण
पूर्ण

अटल व्योम fsg_led_usb_set(काष्ठा led_classdev *led_cdev,
			    क्रमागत led_brightness value)
अणु
	अगर (value) अणु
		latch_value &= ~(1 << FSG_LED_USB_BIT);
		*latch_address = latch_value;
	पूर्ण अन्यथा अणु
		latch_value |=  (1 << FSG_LED_USB_BIT);
		*latch_address = latch_value;
	पूर्ण
पूर्ण

अटल व्योम fsg_led_sync_set(काष्ठा led_classdev *led_cdev,
			     क्रमागत led_brightness value)
अणु
	अगर (value) अणु
		latch_value &= ~(1 << FSG_LED_SYNC_BIT);
		*latch_address = latch_value;
	पूर्ण अन्यथा अणु
		latch_value |=  (1 << FSG_LED_SYNC_BIT);
		*latch_address = latch_value;
	पूर्ण
पूर्ण

अटल व्योम fsg_led_ring_set(काष्ठा led_classdev *led_cdev,
			     क्रमागत led_brightness value)
अणु
	अगर (value) अणु
		latch_value &= ~(1 << FSG_LED_RING_BIT);
		*latch_address = latch_value;
	पूर्ण अन्यथा अणु
		latch_value |=  (1 << FSG_LED_RING_BIT);
		*latch_address = latch_value;
	पूर्ण
पूर्ण


अटल काष्ठा led_classdev fsg_wlan_led = अणु
	.name			= "fsg:blue:wlan",
	.brightness_set		= fsg_led_wlan_set,
	.flags			= LED_CORE_SUSPENDRESUME,
पूर्ण;

अटल काष्ठा led_classdev fsg_wan_led = अणु
	.name			= "fsg:blue:wan",
	.brightness_set		= fsg_led_wan_set,
	.flags			= LED_CORE_SUSPENDRESUME,
पूर्ण;

अटल काष्ठा led_classdev fsg_sata_led = अणु
	.name			= "fsg:blue:sata",
	.brightness_set		= fsg_led_sata_set,
	.flags			= LED_CORE_SUSPENDRESUME,
पूर्ण;

अटल काष्ठा led_classdev fsg_usb_led = अणु
	.name			= "fsg:blue:usb",
	.brightness_set		= fsg_led_usb_set,
	.flags			= LED_CORE_SUSPENDRESUME,
पूर्ण;

अटल काष्ठा led_classdev fsg_sync_led = अणु
	.name			= "fsg:blue:sync",
	.brightness_set		= fsg_led_sync_set,
	.flags			= LED_CORE_SUSPENDRESUME,
पूर्ण;

अटल काष्ठा led_classdev fsg_ring_led = अणु
	.name			= "fsg:blue:ring",
	.brightness_set		= fsg_led_ring_set,
	.flags			= LED_CORE_SUSPENDRESUME,
पूर्ण;


अटल पूर्णांक fsg_led_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	/* Map the LED chip select address space */
	latch_address = (अचिन्हित लघु *) devm_ioremap(&pdev->dev,
						IXP4XX_EXP_BUS_BASE(2), 512);
	अगर (!latch_address)
		वापस -ENOMEM;

	latch_value = 0xffff;
	*latch_address = latch_value;

	ret = devm_led_classdev_रेजिस्टर(&pdev->dev, &fsg_wlan_led);
	अगर (ret < 0)
		वापस ret;

	ret = devm_led_classdev_रेजिस्टर(&pdev->dev, &fsg_wan_led);
	अगर (ret < 0)
		वापस ret;

	ret = devm_led_classdev_रेजिस्टर(&pdev->dev, &fsg_sata_led);
	अगर (ret < 0)
		वापस ret;

	ret = devm_led_classdev_रेजिस्टर(&pdev->dev, &fsg_usb_led);
	अगर (ret < 0)
		वापस ret;

	ret = devm_led_classdev_रेजिस्टर(&pdev->dev, &fsg_sync_led);
	अगर (ret < 0)
		वापस ret;

	ret = devm_led_classdev_रेजिस्टर(&pdev->dev, &fsg_ring_led);
	अगर (ret < 0)
		वापस ret;

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver fsg_led_driver = अणु
	.probe		= fsg_led_probe,
	.driver		= अणु
		.name		= "fsg-led",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(fsg_led_driver);

MODULE_AUTHOR("Rod Whitby <rod@whitby.id.au>");
MODULE_DESCRIPTION("Freecom FSG-3 LED driver");
MODULE_LICENSE("GPL");
