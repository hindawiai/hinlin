<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Driver क्रम Samsung Q10 and related laptops: controls the backlight
 *
 *  Copyright (c) 2011 Frederick van der Wyck <fvanderwyck@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/backlight.h>
#समावेश <linux/dmi.h>
#समावेश <linux/acpi.h>

#घोषणा SAMSUNGQ10_BL_MAX_INTENSITY 7

अटल acpi_handle ec_handle;

अटल bool क्रमce;
module_param(क्रमce, bool, 0);
MODULE_PARM_DESC(क्रमce,
		"Disable the DMI check and force the driver to be loaded");

अटल पूर्णांक samsungq10_bl_set_पूर्णांकensity(काष्ठा backlight_device *bd)
अणु

	acpi_status status;
	पूर्णांक i;

	क्रम (i = 0; i < SAMSUNGQ10_BL_MAX_INTENSITY; i++) अणु
		status = acpi_evaluate_object(ec_handle, "_Q63", शून्य, शून्य);
		अगर (ACPI_FAILURE(status))
			वापस -EIO;
	पूर्ण
	क्रम (i = 0; i < bd->props.brightness; i++) अणु
		status = acpi_evaluate_object(ec_handle, "_Q64", शून्य, शून्य);
		अगर (ACPI_FAILURE(status))
			वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा backlight_ops samsungq10_bl_ops = अणु
	.update_status	= samsungq10_bl_set_पूर्णांकensity,
पूर्ण;

अटल पूर्णांक samsungq10_probe(काष्ठा platक्रमm_device *pdev)
अणु

	काष्ठा backlight_properties props;
	काष्ठा backlight_device *bd;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = SAMSUNGQ10_BL_MAX_INTENSITY;
	bd = backlight_device_रेजिस्टर("samsung", &pdev->dev, शून्य,
				       &samsungq10_bl_ops, &props);
	अगर (IS_ERR(bd))
		वापस PTR_ERR(bd);

	platक्रमm_set_drvdata(pdev, bd);

	वापस 0;
पूर्ण

अटल पूर्णांक samsungq10_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु

	काष्ठा backlight_device *bd = platक्रमm_get_drvdata(pdev);

	backlight_device_unरेजिस्टर(bd);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver samsungq10_driver = अणु
	.driver		= अणु
		.name	= KBUILD_MODNAME,
	पूर्ण,
	.probe		= samsungq10_probe,
	.हटाओ		= samsungq10_हटाओ,
पूर्ण;

अटल काष्ठा platक्रमm_device *samsungq10_device;

अटल पूर्णांक __init dmi_check_callback(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	prपूर्णांकk(KERN_INFO KBUILD_MODNAME ": found model '%s'\n", id->ident);
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id samsungq10_dmi_table[] __initस्थिर = अणु
	अणु
		.ident = "Samsung Q10",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Samsung"),
			DMI_MATCH(DMI_PRODUCT_NAME, "SQ10"),
		पूर्ण,
		.callback = dmi_check_callback,
	पूर्ण,
	अणु
		.ident = "Samsung Q20",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG Electronics"),
			DMI_MATCH(DMI_PRODUCT_NAME, "SENS Q20"),
		पूर्ण,
		.callback = dmi_check_callback,
	पूर्ण,
	अणु
		.ident = "Samsung Q25",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG Electronics"),
			DMI_MATCH(DMI_PRODUCT_NAME, "NQ25"),
		पूर्ण,
		.callback = dmi_check_callback,
	पूर्ण,
	अणु
		.ident = "Dell Latitude X200",
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Dell Computer Corporation"),
			DMI_MATCH(DMI_PRODUCT_NAME, "X200"),
		पूर्ण,
		.callback = dmi_check_callback,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(dmi, samsungq10_dmi_table);

अटल पूर्णांक __init samsungq10_init(व्योम)
अणु
	अगर (!क्रमce && !dmi_check_प्रणाली(samsungq10_dmi_table))
		वापस -ENODEV;

	ec_handle = ec_get_handle();

	अगर (!ec_handle)
		वापस -ENODEV;

	samsungq10_device = platक्रमm_create_bundle(&samsungq10_driver,
						   samsungq10_probe,
						   शून्य, 0, शून्य, 0);

	वापस PTR_ERR_OR_ZERO(samsungq10_device);
पूर्ण

अटल व्योम __निकास samsungq10_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(samsungq10_device);
	platक्रमm_driver_unरेजिस्टर(&samsungq10_driver);
पूर्ण

module_init(samsungq10_init);
module_निकास(samsungq10_निकास);

MODULE_AUTHOR("Frederick van der Wyck <fvanderwyck@gmail.com>");
MODULE_DESCRIPTION("Samsung Q10 Driver");
MODULE_LICENSE("GPL");
