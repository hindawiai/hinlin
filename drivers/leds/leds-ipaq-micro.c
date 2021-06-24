<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * h3xxx aपंचांगel micro companion support, notअगरication LED subdevice
 *
 * Author : Linus Walleij <linus.walleij@linaro.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/ipaq-micro.h>
#समावेश <linux/leds.h>

#घोषणा LED_YELLOW	0x00
#घोषणा LED_GREEN	0x01

#घोषणा LED_EN       (1 << 4) /* LED ON/OFF 0:off, 1:on                       */
#घोषणा LED_AUTOSTOP (1 << 5) /* LED ON/OFF स्वतः stop set 0:disable, 1:enable */
#घोषणा LED_ALWAYS   (1 << 6) /* LED Interrupt Mask 0:No mask, 1:mask         */

अटल पूर्णांक micro_leds_brightness_set(काष्ठा led_classdev *led_cdev,
				      क्रमागत led_brightness value)
अणु
	काष्ठा ipaq_micro *micro = dev_get_drvdata(led_cdev->dev->parent->parent);
	/*
	 * In this message:
	 * Byte 0 = LED color: 0 = yellow, 1 = green
	 *          yellow LED is always ~30 blinks per minute
	 * Byte 1 = duration (flags?) appears to be ignored
	 * Byte 2 = green onसमय in 1/10 sec (deciseconds)
	 *          1 = 1/10 second
	 *          0 = 256/10 second
	 * Byte 3 = green offसमय in 1/10 sec (deciseconds)
	 *          1 = 1/10 second
	 *          0 = 256/10 seconds
	 */
	काष्ठा ipaq_micro_msg msg = अणु
		.id = MSG_NOTIFY_LED,
		.tx_len = 4,
	पूर्ण;

	msg.tx_data[0] = LED_GREEN;
	msg.tx_data[1] = 0;
	अगर (value) अणु
		msg.tx_data[2] = 0; /* Duty cycle 256 */
		msg.tx_data[3] = 1;
	पूर्ण अन्यथा अणु
		msg.tx_data[2] = 1;
		msg.tx_data[3] = 0; /* Duty cycle 256 */
	पूर्ण
	वापस ipaq_micro_tx_msg_sync(micro, &msg);
पूर्ण

/* Maximum duty cycle in ms 256/10 sec = 25600 ms */
#घोषणा IPAQ_LED_MAX_DUTY 25600

अटल पूर्णांक micro_leds_blink_set(काष्ठा led_classdev *led_cdev,
				अचिन्हित दीर्घ *delay_on,
				अचिन्हित दीर्घ *delay_off)
अणु
	काष्ठा ipaq_micro *micro = dev_get_drvdata(led_cdev->dev->parent->parent);
	/*
	 * In this message:
	 * Byte 0 = LED color: 0 = yellow, 1 = green
	 *          yellow LED is always ~30 blinks per minute
	 * Byte 1 = duration (flags?) appears to be ignored
	 * Byte 2 = green onसमय in 1/10 sec (deciseconds)
	 *          1 = 1/10 second
	 *          0 = 256/10 second
	 * Byte 3 = green offसमय in 1/10 sec (deciseconds)
	 *          1 = 1/10 second
	 *          0 = 256/10 seconds
	 */
	काष्ठा ipaq_micro_msg msg = अणु
		.id = MSG_NOTIFY_LED,
		.tx_len = 4,
	पूर्ण;

	msg.tx_data[0] = LED_GREEN;
	अगर (*delay_on > IPAQ_LED_MAX_DUTY ||
	    *delay_off > IPAQ_LED_MAX_DUTY)
		वापस -EINVAL;

	अगर (*delay_on == 0 && *delay_off == 0) अणु
		*delay_on = 100;
		*delay_off = 100;
	पूर्ण

	msg.tx_data[1] = 0;
	अगर (*delay_on >= IPAQ_LED_MAX_DUTY)
		msg.tx_data[2] = 0;
	अन्यथा
		msg.tx_data[2] = (u8) DIV_ROUND_CLOSEST(*delay_on, 100);
	अगर (*delay_off >= IPAQ_LED_MAX_DUTY)
		msg.tx_data[3] = 0;
	अन्यथा
		msg.tx_data[3] = (u8) DIV_ROUND_CLOSEST(*delay_off, 100);
	वापस ipaq_micro_tx_msg_sync(micro, &msg);
पूर्ण

अटल काष्ठा led_classdev micro_led = अणु
	.name			= "led-ipaq-micro",
	.brightness_set_blocking = micro_leds_brightness_set,
	.blink_set		= micro_leds_blink_set,
	.flags			= LED_CORE_SUSPENDRESUME,
पूर्ण;

अटल पूर्णांक micro_leds_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	ret = devm_led_classdev_रेजिस्टर(&pdev->dev, &micro_led);
	अगर (ret) अणु
		dev_err(&pdev->dev, "registering led failed: %d\n", ret);
		वापस ret;
	पूर्ण
	dev_info(&pdev->dev, "iPAQ micro notification LED driver\n");

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver micro_leds_device_driver = अणु
	.driver = अणु
		.name    = "ipaq-micro-leds",
	पूर्ण,
	.probe   = micro_leds_probe,
पूर्ण;
module_platक्रमm_driver(micro_leds_device_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("driver for iPAQ Atmel micro leds");
MODULE_ALIAS("platform:ipaq-micro-leds");
