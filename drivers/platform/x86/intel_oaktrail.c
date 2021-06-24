<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Intel OakTrail Platक्रमm support
 *
 * Copyright (C) 2010-2011 Intel Corporation
 * Author: Yin Kangkai (kangkai.yin@पूर्णांकel.com)
 *
 * based on Compal driver, Copyright (C) 2008 Cezary Jackiewicz
 * <cezary.jackiewicz (at) gmail.com>, based on MSI driver
 * Copyright (C) 2006 Lennart Poettering <mzxreary (at) 0poपूर्णांकer (करोt) de>
 *
 * This driver करोes below things:
 * 1. रेजिस्टरs itself in the Linux backlight control in
 *    /sys/class/backlight/पूर्णांकel_oaktrail/
 *
 * 2. रेजिस्टरs in the rfसमाप्त subप्रणाली here: /sys/class/rfसमाप्त/rfसमाप्तX/
 *    क्रम these components: wअगरi, bluetooth, wwan (3g), gps
 *
 * This driver might work on other products based on Oaktrail. If you
 * want to try it you can pass क्रमce=1 as argument to the module which
 * will क्रमce it to load even when the DMI data करोesn't identअगरy the
 * product as compatible.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/backlight.h>
#समावेश <linux/dmi.h>
#समावेश <linux/err.h>
#समावेश <linux/fb.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/rfसमाप्त.h>

#समावेश <acpi/video.h>

#घोषणा DRIVER_NAME	"intel_oaktrail"
#घोषणा DRIVER_VERSION	"0.4ac1"

/*
 * This is the devices status address in EC space, and the control bits
 * definition:
 *
 * (1 << 0):	Camera enable/disable, RW.
 * (1 << 1):	Bluetooth enable/disable, RW.
 * (1 << 2):	GPS enable/disable, RW.
 * (1 << 3):	WiFi enable/disable, RW.
 * (1 << 4):	WWAN (3G) enable/disable, RW.
 * (1 << 5):	Touchscreen enable/disable, Read Only.
 */
#घोषणा OT_EC_DEVICE_STATE_ADDRESS	0xD6

#घोषणा OT_EC_CAMERA_MASK	(1 << 0)
#घोषणा OT_EC_BT_MASK		(1 << 1)
#घोषणा OT_EC_GPS_MASK		(1 << 2)
#घोषणा OT_EC_WIFI_MASK		(1 << 3)
#घोषणा OT_EC_WWAN_MASK		(1 << 4)
#घोषणा OT_EC_TS_MASK		(1 << 5)

/*
 * This is the address in EC space and commands used to control LCD backlight:
 *
 * Two steps needed to change the LCD backlight:
 *   1. ग_लिखो the backlight percentage पूर्णांकo OT_EC_BL_BRIGHTNESS_ADDRESS;
 *   2. ग_लिखो OT_EC_BL_CONTROL_ON_DATA पूर्णांकo OT_EC_BL_CONTROL_ADDRESS.
 *
 * To पढ़ो the LCD back light, just पढ़ो out the value from
 * OT_EC_BL_BRIGHTNESS_ADDRESS.
 *
 * LCD backlight brightness range: 0 - 100 (OT_EC_BL_BRIGHTNESS_MAX)
 */
#घोषणा OT_EC_BL_BRIGHTNESS_ADDRESS	0x44
#घोषणा OT_EC_BL_BRIGHTNESS_MAX		100
#घोषणा OT_EC_BL_CONTROL_ADDRESS	0x3A
#घोषणा OT_EC_BL_CONTROL_ON_DATA	0x1A


अटल bool क्रमce;
module_param(क्रमce, bool, 0);
MODULE_PARM_DESC(क्रमce, "Force driver load, ignore DMI data");

अटल काष्ठा platक्रमm_device *oaktrail_device;
अटल काष्ठा backlight_device *oaktrail_bl_device;
अटल काष्ठा rfसमाप्त *bt_rfसमाप्त;
अटल काष्ठा rfसमाप्त *gps_rfसमाप्त;
अटल काष्ठा rfसमाप्त *wअगरi_rfसमाप्त;
अटल काष्ठा rfसमाप्त *wwan_rfसमाप्त;


/* rfसमाप्त */
अटल पूर्णांक oaktrail_rfसमाप्त_set(व्योम *data, bool blocked)
अणु
	u8 value;
	u8 result;
	अचिन्हित दीर्घ radio = (अचिन्हित दीर्घ) data;

	ec_पढ़ो(OT_EC_DEVICE_STATE_ADDRESS, &result);

	अगर (!blocked)
		value = (u8) (result | radio);
	अन्यथा
		value = (u8) (result & ~radio);

	ec_ग_लिखो(OT_EC_DEVICE_STATE_ADDRESS, value);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops oaktrail_rfसमाप्त_ops = अणु
	.set_block = oaktrail_rfसमाप्त_set,
पूर्ण;

अटल काष्ठा rfसमाप्त *oaktrail_rfसमाप्त_new(अक्षर *name, क्रमागत rfसमाप्त_type type,
					  अचिन्हित दीर्घ mask)
अणु
	काष्ठा rfसमाप्त *rfसमाप्त_dev;
	u8 value;
	पूर्णांक err;

	rfसमाप्त_dev = rfसमाप्त_alloc(name, &oaktrail_device->dev, type,
				  &oaktrail_rfसमाप्त_ops, (व्योम *)mask);
	अगर (!rfसमाप्त_dev)
		वापस ERR_PTR(-ENOMEM);

	ec_पढ़ो(OT_EC_DEVICE_STATE_ADDRESS, &value);
	rfसमाप्त_init_sw_state(rfसमाप्त_dev, (value & mask) != 1);

	err = rfसमाप्त_रेजिस्टर(rfसमाप्त_dev);
	अगर (err) अणु
		rfसमाप्त_destroy(rfसमाप्त_dev);
		वापस ERR_PTR(err);
	पूर्ण

	वापस rfसमाप्त_dev;
पूर्ण

अटल अंतरभूत व्योम __oaktrail_rfसमाप्त_cleanup(काष्ठा rfसमाप्त *rf)
अणु
	अगर (rf) अणु
		rfसमाप्त_unरेजिस्टर(rf);
		rfसमाप्त_destroy(rf);
	पूर्ण
पूर्ण

अटल व्योम oaktrail_rfसमाप्त_cleanup(व्योम)
अणु
	__oaktrail_rfसमाप्त_cleanup(wअगरi_rfसमाप्त);
	__oaktrail_rfसमाप्त_cleanup(bt_rfसमाप्त);
	__oaktrail_rfसमाप्त_cleanup(gps_rfसमाप्त);
	__oaktrail_rfसमाप्त_cleanup(wwan_rfसमाप्त);
पूर्ण

अटल पूर्णांक oaktrail_rfसमाप्त_init(व्योम)
अणु
	पूर्णांक ret;

	wअगरi_rfसमाप्त = oaktrail_rfसमाप्त_new("oaktrail-wifi",
					  RFKILL_TYPE_WLAN,
					  OT_EC_WIFI_MASK);
	अगर (IS_ERR(wअगरi_rfसमाप्त)) अणु
		ret = PTR_ERR(wअगरi_rfसमाप्त);
		wअगरi_rfसमाप्त = शून्य;
		जाओ cleanup;
	पूर्ण

	bt_rfसमाप्त = oaktrail_rfसमाप्त_new("oaktrail-bluetooth",
					RFKILL_TYPE_BLUETOOTH,
					OT_EC_BT_MASK);
	अगर (IS_ERR(bt_rfसमाप्त)) अणु
		ret = PTR_ERR(bt_rfसमाप्त);
		bt_rfसमाप्त = शून्य;
		जाओ cleanup;
	पूर्ण

	gps_rfसमाप्त = oaktrail_rfसमाप्त_new("oaktrail-gps",
					 RFKILL_TYPE_GPS,
					 OT_EC_GPS_MASK);
	अगर (IS_ERR(gps_rfसमाप्त)) अणु
		ret = PTR_ERR(gps_rfसमाप्त);
		gps_rfसमाप्त = शून्य;
		जाओ cleanup;
	पूर्ण

	wwan_rfसमाप्त = oaktrail_rfसमाप्त_new("oaktrail-wwan",
					  RFKILL_TYPE_WWAN,
					  OT_EC_WWAN_MASK);
	अगर (IS_ERR(wwan_rfसमाप्त)) अणु
		ret = PTR_ERR(wwan_rfसमाप्त);
		wwan_rfसमाप्त = शून्य;
		जाओ cleanup;
	पूर्ण

	वापस 0;

cleanup:
	oaktrail_rfसमाप्त_cleanup();
	वापस ret;
पूर्ण


/* backlight */
अटल पूर्णांक get_backlight_brightness(काष्ठा backlight_device *b)
अणु
	u8 value;
	ec_पढ़ो(OT_EC_BL_BRIGHTNESS_ADDRESS, &value);

	वापस value;
पूर्ण

अटल पूर्णांक set_backlight_brightness(काष्ठा backlight_device *b)
अणु
	u8 percent = (u8) b->props.brightness;
	अगर (percent < 0 || percent > OT_EC_BL_BRIGHTNESS_MAX)
		वापस -EINVAL;

	ec_ग_लिखो(OT_EC_BL_BRIGHTNESS_ADDRESS, percent);
	ec_ग_लिखो(OT_EC_BL_CONTROL_ADDRESS, OT_EC_BL_CONTROL_ON_DATA);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops oaktrail_bl_ops = अणु
	.get_brightness = get_backlight_brightness,
	.update_status	= set_backlight_brightness,
पूर्ण;

अटल पूर्णांक oaktrail_backlight_init(व्योम)
अणु
	काष्ठा backlight_device *bd;
	काष्ठा backlight_properties props;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = OT_EC_BL_BRIGHTNESS_MAX;
	bd = backlight_device_रेजिस्टर(DRIVER_NAME,
				       &oaktrail_device->dev, शून्य,
				       &oaktrail_bl_ops,
				       &props);

	अगर (IS_ERR(bd)) अणु
		oaktrail_bl_device = शून्य;
		pr_warn("Unable to register backlight device\n");
		वापस PTR_ERR(bd);
	पूर्ण

	oaktrail_bl_device = bd;

	bd->props.brightness = get_backlight_brightness(bd);
	bd->props.घातer = FB_BLANK_UNBLANK;
	backlight_update_status(bd);

	वापस 0;
पूर्ण

अटल व्योम oaktrail_backlight_निकास(व्योम)
अणु
	backlight_device_unरेजिस्टर(oaktrail_bl_device);
पूर्ण

अटल पूर्णांक oaktrail_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक oaktrail_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver oaktrail_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
	पूर्ण,
	.probe	= oaktrail_probe,
	.हटाओ	= oaktrail_हटाओ,
पूर्ण;

अटल पूर्णांक dmi_check_cb(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	pr_info("Identified model '%s'\n", id->ident);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id oaktrail_dmi_table[] __initस्थिर = अणु
	अणु
		.ident = "OakTrail platform",
		.matches = अणु
			DMI_MATCH(DMI_PRODUCT_NAME, "OakTrail platform"),
		पूर्ण,
		.callback = dmi_check_cb
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(dmi, oaktrail_dmi_table);

अटल पूर्णांक __init oaktrail_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (acpi_disabled) अणु
		pr_err("ACPI needs to be enabled for this driver to work!\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!क्रमce && !dmi_check_प्रणाली(oaktrail_dmi_table)) अणु
		pr_err("Platform not recognized (You could try the module's force-parameter)");
		वापस -ENODEV;
	पूर्ण

	ret = platक्रमm_driver_रेजिस्टर(&oaktrail_driver);
	अगर (ret) अणु
		pr_warn("Unable to register platform driver\n");
		जाओ err_driver_reg;
	पूर्ण

	oaktrail_device = platक्रमm_device_alloc(DRIVER_NAME, -1);
	अगर (!oaktrail_device) अणु
		pr_warn("Unable to allocate platform device\n");
		ret = -ENOMEM;
		जाओ err_device_alloc;
	पूर्ण

	ret = platक्रमm_device_add(oaktrail_device);
	अगर (ret) अणु
		pr_warn("Unable to add platform device\n");
		जाओ err_device_add;
	पूर्ण

	अगर (acpi_video_get_backlight_type() == acpi_backlight_venकरोr) अणु
		ret = oaktrail_backlight_init();
		अगर (ret)
			जाओ err_backlight;
	पूर्ण

	ret = oaktrail_rfसमाप्त_init();
	अगर (ret) अणु
		pr_warn("Setup rfkill failed\n");
		जाओ err_rfसमाप्त;
	पूर्ण

	pr_info("Driver "DRIVER_VERSION" successfully loaded\n");
	वापस 0;

err_rfसमाप्त:
	oaktrail_backlight_निकास();
err_backlight:
	platक्रमm_device_del(oaktrail_device);
err_device_add:
	platक्रमm_device_put(oaktrail_device);
err_device_alloc:
	platक्रमm_driver_unरेजिस्टर(&oaktrail_driver);
err_driver_reg:

	वापस ret;
पूर्ण

अटल व्योम __निकास oaktrail_cleanup(व्योम)
अणु
	oaktrail_backlight_निकास();
	oaktrail_rfसमाप्त_cleanup();
	platक्रमm_device_unरेजिस्टर(oaktrail_device);
	platक्रमm_driver_unरेजिस्टर(&oaktrail_driver);

	pr_info("Driver unloaded\n");
पूर्ण

module_init(oaktrail_init);
module_निकास(oaktrail_cleanup);

MODULE_AUTHOR("Yin Kangkai (kangkai.yin@intel.com)");
MODULE_DESCRIPTION("Intel Oaktrail Platform ACPI Extras");
MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL");
