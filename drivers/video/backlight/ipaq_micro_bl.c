<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * iPAQ microcontroller backlight support
 * Author : Linus Walleij <linus.walleij@linaro.org>
 */

#समावेश <linux/backlight.h>
#समावेश <linux/err.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/mfd/ipaq-micro.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

अटल पूर्णांक micro_bl_update_status(काष्ठा backlight_device *bd)
अणु
	काष्ठा ipaq_micro *micro = dev_get_drvdata(&bd->dev);
	पूर्णांक पूर्णांकensity = bd->props.brightness;
	काष्ठा ipaq_micro_msg msg = अणु
		.id = MSG_BACKLIGHT,
		.tx_len = 3,
	पूर्ण;

	अगर (bd->props.घातer != FB_BLANK_UNBLANK)
		पूर्णांकensity = 0;
	अगर (bd->props.state & (BL_CORE_FBBLANK | BL_CORE_SUSPENDED))
		पूर्णांकensity = 0;

	/*
	 * Message क्रमmat:
	 * Byte 0: backlight instance (usually 1)
	 * Byte 1: on/off
	 * Byte 2: पूर्णांकensity, 0-255
	 */
	msg.tx_data[0] = 0x01;
	msg.tx_data[1] = पूर्णांकensity > 0 ? 1 : 0;
	msg.tx_data[2] = पूर्णांकensity;
	वापस ipaq_micro_tx_msg_sync(micro, &msg);
पूर्ण

अटल स्थिर काष्ठा backlight_ops micro_bl_ops = अणु
	.options = BL_CORE_SUSPENDRESUME,
	.update_status  = micro_bl_update_status,
पूर्ण;

अटल स्थिर काष्ठा backlight_properties micro_bl_props = अणु
	.type = BACKLIGHT_RAW,
	.max_brightness = 255,
	.घातer = FB_BLANK_UNBLANK,
	.brightness = 64,
पूर्ण;

अटल पूर्णांक micro_backlight_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा backlight_device *bd;
	काष्ठा ipaq_micro *micro = dev_get_drvdata(pdev->dev.parent);

	bd = devm_backlight_device_रेजिस्टर(&pdev->dev, "ipaq-micro-backlight",
					    &pdev->dev, micro, &micro_bl_ops,
					    &micro_bl_props);
	अगर (IS_ERR(bd))
		वापस PTR_ERR(bd);

	platक्रमm_set_drvdata(pdev, bd);
	backlight_update_status(bd);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver micro_backlight_device_driver = अणु
	.driver = अणु
		.name    = "ipaq-micro-backlight",
	पूर्ण,
	.probe   = micro_backlight_probe,
पूर्ण;
module_platक्रमm_driver(micro_backlight_device_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("driver for iPAQ Atmel micro backlight");
MODULE_ALIAS("platform:ipaq-micro-backlight");
