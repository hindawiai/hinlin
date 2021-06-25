<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Backlight Driver क्रम the KB3886 Backlight
 *
 *  Copyright (c) 2007-2008 Claudio Nieder
 *
 *  Based on corgi_bl.c by Riअक्षरd Purdie and kb3886 driver by Robert Woerle
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/fb.h>
#समावेश <linux/backlight.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmi.h>

#घोषणा KB3886_PARENT 0x64
#घोषणा KB3886_IO 0x60
#घोषणा KB3886_ADC_DAC_PWM 0xC4
#घोषणा KB3886_PWM0_WRITE 0x81
#घोषणा KB3886_PWM0_READ 0x41

अटल DEFINE_MUTEX(bl_mutex);

अटल व्योम kb3886_bl_set_पूर्णांकensity(पूर्णांक पूर्णांकensity)
अणु
	mutex_lock(&bl_mutex);
	पूर्णांकensity = पूर्णांकensity&0xff;
	outb(KB3886_ADC_DAC_PWM, KB3886_PARENT);
	usleep_range(10000, 11000);
	outb(KB3886_PWM0_WRITE, KB3886_IO);
	usleep_range(10000, 11000);
	outb(पूर्णांकensity, KB3886_IO);
	mutex_unlock(&bl_mutex);
पूर्ण

काष्ठा kb3886bl_machinfo अणु
	पूर्णांक max_पूर्णांकensity;
	पूर्णांक शेष_पूर्णांकensity;
	पूर्णांक limit_mask;
	व्योम (*set_bl_पूर्णांकensity)(पूर्णांक पूर्णांकensity);
पूर्ण;

अटल काष्ठा kb3886bl_machinfo kb3886_bl_machinfo = अणु
	.max_पूर्णांकensity = 0xff,
	.शेष_पूर्णांकensity = 0xa0,
	.limit_mask = 0x7f,
	.set_bl_पूर्णांकensity = kb3886_bl_set_पूर्णांकensity,
पूर्ण;

अटल काष्ठा platक्रमm_device kb3886bl_device = अणु
	.name		= "kb3886-bl",
	.dev		= अणु
		.platक्रमm_data	= &kb3886_bl_machinfo,
	पूर्ण,
	.id		= -1,
पूर्ण;

अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&kb3886bl_device,
पूर्ण;

/*
 * Back to driver
 */

अटल पूर्णांक kb3886bl_पूर्णांकensity;
अटल काष्ठा backlight_device *kb3886_backlight_device;
अटल काष्ठा kb3886bl_machinfo *bl_machinfo;

अटल अचिन्हित दीर्घ kb3886bl_flags;
#घोषणा KB3886BL_SUSPENDED     0x01

अटल स्थिर काष्ठा dmi_प्रणाली_id kb3886bl_device_table[] __initस्थिर = अणु
	अणु
		.ident = "Sahara Touch-iT",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "SDV"),
			DMI_MATCH(DMI_PRODUCT_NAME, "iTouch T201"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक kb3886bl_send_पूर्णांकensity(काष्ठा backlight_device *bd)
अणु
	पूर्णांक पूर्णांकensity = backlight_get_brightness(bd);

	अगर (kb3886bl_flags & KB3886BL_SUSPENDED)
		पूर्णांकensity = 0;

	bl_machinfo->set_bl_पूर्णांकensity(पूर्णांकensity);

	kb3886bl_पूर्णांकensity = पूर्णांकensity;
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक kb3886bl_suspend(काष्ठा device *dev)
अणु
	काष्ठा backlight_device *bd = dev_get_drvdata(dev);

	kb3886bl_flags |= KB3886BL_SUSPENDED;
	backlight_update_status(bd);
	वापस 0;
पूर्ण

अटल पूर्णांक kb3886bl_resume(काष्ठा device *dev)
अणु
	काष्ठा backlight_device *bd = dev_get_drvdata(dev);

	kb3886bl_flags &= ~KB3886BL_SUSPENDED;
	backlight_update_status(bd);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(kb3886bl_pm_ops, kb3886bl_suspend, kb3886bl_resume);

अटल पूर्णांक kb3886bl_get_पूर्णांकensity(काष्ठा backlight_device *bd)
अणु
	वापस kb3886bl_पूर्णांकensity;
पूर्ण

अटल स्थिर काष्ठा backlight_ops kb3886bl_ops = अणु
	.get_brightness = kb3886bl_get_पूर्णांकensity,
	.update_status  = kb3886bl_send_पूर्णांकensity,
पूर्ण;

अटल पूर्णांक kb3886bl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा backlight_properties props;
	काष्ठा kb3886bl_machinfo *machinfo = dev_get_platdata(&pdev->dev);

	bl_machinfo = machinfo;
	अगर (!machinfo->limit_mask)
		machinfo->limit_mask = -1;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_RAW;
	props.max_brightness = machinfo->max_पूर्णांकensity;
	kb3886_backlight_device = devm_backlight_device_रेजिस्टर(&pdev->dev,
							"kb3886-bl", &pdev->dev,
							शून्य, &kb3886bl_ops,
							&props);
	अगर (IS_ERR(kb3886_backlight_device))
		वापस PTR_ERR(kb3886_backlight_device);

	platक्रमm_set_drvdata(pdev, kb3886_backlight_device);

	kb3886_backlight_device->props.घातer = FB_BLANK_UNBLANK;
	kb3886_backlight_device->props.brightness = machinfo->शेष_पूर्णांकensity;
	backlight_update_status(kb3886_backlight_device);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver kb3886bl_driver = अणु
	.probe		= kb3886bl_probe,
	.driver		= अणु
		.name	= "kb3886-bl",
		.pm	= &kb3886bl_pm_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init kb3886_init(व्योम)
अणु
	अगर (!dmi_check_प्रणाली(kb3886bl_device_table))
		वापस -ENODEV;

	platक्रमm_add_devices(devices, ARRAY_SIZE(devices));
	वापस platक्रमm_driver_रेजिस्टर(&kb3886bl_driver);
पूर्ण

अटल व्योम __निकास kb3886_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&kb3886bl_driver);
पूर्ण

module_init(kb3886_init);
module_निकास(kb3886_निकास);

MODULE_AUTHOR("Claudio Nieder <private@claudio.ch>");
MODULE_DESCRIPTION("Tabletkiosk Sahara Touch-iT Backlight Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("dmi:*:svnSDV:pniTouchT201:*");
