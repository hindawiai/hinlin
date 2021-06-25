<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Surface GPE/Lid driver to enable wakeup from suspend via the lid by
 * properly configuring the respective GPEs. Required क्रम wakeup via lid on
 * newer Intel-based Microsoft Surface devices.
 *
 * Copyright (C) 2020 Maximilian Luz <luzmaximilian@gmail.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

/*
 * Note: The GPE numbers क्रम the lid devices found below have been obtained
 *       from ACPI/the DSDT table, specअगरically from the GPE handler क्रम the
 *       lid.
 */

अटल स्थिर काष्ठा property_entry lid_device_props_l17[] = अणु
	PROPERTY_ENTRY_U32("gpe", 0x17),
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा property_entry lid_device_props_l4D[] = अणु
	PROPERTY_ENTRY_U32("gpe", 0x4D),
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा property_entry lid_device_props_l4F[] = अणु
	PROPERTY_ENTRY_U32("gpe", 0x4F),
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा property_entry lid_device_props_l57[] = अणु
	PROPERTY_ENTRY_U32("gpe", 0x57),
	अणुपूर्ण,
पूर्ण;

/*
 * Note: When changing this, करोn't क्रमget to check that the MODULE_ALIAS below
 *       still fits.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id dmi_lid_device_table[] = अणु
	अणु
		.ident = "Surface Pro 4",
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Microsoft Corporation"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Surface Pro 4"),
		पूर्ण,
		.driver_data = (व्योम *)lid_device_props_l17,
	पूर्ण,
	अणु
		.ident = "Surface Pro 5",
		.matches = अणु
			/*
			 * We match क्रम SKU here due to generic product name
			 * "Surface Pro".
			 */
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Microsoft Corporation"),
			DMI_EXACT_MATCH(DMI_PRODUCT_SKU, "Surface_Pro_1796"),
		पूर्ण,
		.driver_data = (व्योम *)lid_device_props_l4F,
	पूर्ण,
	अणु
		.ident = "Surface Pro 5 (LTE)",
		.matches = अणु
			/*
			 * We match क्रम SKU here due to generic product name
			 * "Surface Pro"
			 */
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Microsoft Corporation"),
			DMI_EXACT_MATCH(DMI_PRODUCT_SKU, "Surface_Pro_1807"),
		पूर्ण,
		.driver_data = (व्योम *)lid_device_props_l4F,
	पूर्ण,
	अणु
		.ident = "Surface Pro 6",
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Microsoft Corporation"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Surface Pro 6"),
		पूर्ण,
		.driver_data = (व्योम *)lid_device_props_l4F,
	पूर्ण,
	अणु
		.ident = "Surface Pro 7",
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Microsoft Corporation"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Surface Pro 7"),
		पूर्ण,
		.driver_data = (व्योम *)lid_device_props_l4D,
	पूर्ण,
	अणु
		.ident = "Surface Book 1",
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Microsoft Corporation"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Surface Book"),
		पूर्ण,
		.driver_data = (व्योम *)lid_device_props_l17,
	पूर्ण,
	अणु
		.ident = "Surface Book 2",
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Microsoft Corporation"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Surface Book 2"),
		पूर्ण,
		.driver_data = (व्योम *)lid_device_props_l17,
	पूर्ण,
	अणु
		.ident = "Surface Book 3",
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Microsoft Corporation"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Surface Book 3"),
		पूर्ण,
		.driver_data = (व्योम *)lid_device_props_l4D,
	पूर्ण,
	अणु
		.ident = "Surface Laptop 1",
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Microsoft Corporation"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Surface Laptop"),
		पूर्ण,
		.driver_data = (व्योम *)lid_device_props_l57,
	पूर्ण,
	अणु
		.ident = "Surface Laptop 2",
		.matches = अणु
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Microsoft Corporation"),
			DMI_EXACT_MATCH(DMI_PRODUCT_NAME, "Surface Laptop 2"),
		पूर्ण,
		.driver_data = (व्योम *)lid_device_props_l57,
	पूर्ण,
	अणु
		.ident = "Surface Laptop 3 (Intel 13\")",
		.matches = अणु
			/*
			 * We match क्रम SKU here due to dअगरferent variants: The
			 * AMD (15") version करोes not rely on GPEs.
			 */
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Microsoft Corporation"),
			DMI_EXACT_MATCH(DMI_PRODUCT_SKU, "Surface_Laptop_3_1867:1868"),
		पूर्ण,
		.driver_data = (व्योम *)lid_device_props_l4D,
	पूर्ण,
	अणु
		.ident = "Surface Laptop 3 (Intel 15\")",
		.matches = अणु
			/*
			 * We match क्रम SKU here due to dअगरferent variants: The
			 * AMD (15") version करोes not rely on GPEs.
			 */
			DMI_EXACT_MATCH(DMI_SYS_VENDOR, "Microsoft Corporation"),
			DMI_EXACT_MATCH(DMI_PRODUCT_SKU, "Surface_Laptop_3_1872"),
		पूर्ण,
		.driver_data = (व्योम *)lid_device_props_l4D,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

काष्ठा surface_lid_device अणु
	u32 gpe_number;
पूर्ण;

अटल पूर्णांक surface_lid_enable_wakeup(काष्ठा device *dev, bool enable)
अणु
	स्थिर काष्ठा surface_lid_device *lid = dev_get_drvdata(dev);
	पूर्णांक action = enable ? ACPI_GPE_ENABLE : ACPI_GPE_DISABLE;
	acpi_status status;

	status = acpi_set_gpe_wake_mask(शून्य, lid->gpe_number, action);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(dev, "failed to set GPE wake mask: %s\n",
			acpi_क्रमmat_exception(status));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused surface_gpe_suspend(काष्ठा device *dev)
अणु
	वापस surface_lid_enable_wakeup(dev, true);
पूर्ण

अटल पूर्णांक __maybe_unused surface_gpe_resume(काष्ठा device *dev)
अणु
	वापस surface_lid_enable_wakeup(dev, false);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(surface_gpe_pm, surface_gpe_suspend, surface_gpe_resume);

अटल पूर्णांक surface_gpe_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा surface_lid_device *lid;
	u32 gpe_number;
	acpi_status status;
	पूर्णांक ret;

	ret = device_property_पढ़ो_u32(&pdev->dev, "gpe", &gpe_number);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to read 'gpe' property: %d\n", ret);
		वापस ret;
	पूर्ण

	lid = devm_kzalloc(&pdev->dev, माप(*lid), GFP_KERNEL);
	अगर (!lid)
		वापस -ENOMEM;

	lid->gpe_number = gpe_number;
	platक्रमm_set_drvdata(pdev, lid);

	status = acpi_mark_gpe_क्रम_wake(शून्य, gpe_number);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(&pdev->dev, "failed to mark GPE for wake: %s\n",
			acpi_क्रमmat_exception(status));
		वापस -EINVAL;
	पूर्ण

	status = acpi_enable_gpe(शून्य, gpe_number);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(&pdev->dev, "failed to enable GPE: %s\n",
			acpi_क्रमmat_exception(status));
		वापस -EINVAL;
	पूर्ण

	ret = surface_lid_enable_wakeup(&pdev->dev, false);
	अगर (ret)
		acpi_disable_gpe(शून्य, gpe_number);

	वापस ret;
पूर्ण

अटल पूर्णांक surface_gpe_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा surface_lid_device *lid = dev_get_drvdata(&pdev->dev);

	/* restore शेष behavior without this module */
	surface_lid_enable_wakeup(&pdev->dev, false);
	acpi_disable_gpe(शून्य, lid->gpe_number);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver surface_gpe_driver = अणु
	.probe = surface_gpe_probe,
	.हटाओ = surface_gpe_हटाओ,
	.driver = अणु
		.name = "surface_gpe",
		.pm = &surface_gpe_pm,
		.probe_type = PROBE_PREFER_ASYNCHRONOUS,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *surface_gpe_device;

अटल पूर्णांक __init surface_gpe_init(व्योम)
अणु
	स्थिर काष्ठा dmi_प्रणाली_id *match;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा fwnode_handle *fwnode;
	पूर्णांक status;

	match = dmi_first_match(dmi_lid_device_table);
	अगर (!match) अणु
		pr_info("no compatible Microsoft Surface device found, exiting\n");
		वापस -ENODEV;
	पूर्ण

	status = platक्रमm_driver_रेजिस्टर(&surface_gpe_driver);
	अगर (status)
		वापस status;

	fwnode = fwnode_create_software_node(match->driver_data, शून्य);
	अगर (IS_ERR(fwnode)) अणु
		status = PTR_ERR(fwnode);
		जाओ err_node;
	पूर्ण

	pdev = platक्रमm_device_alloc("surface_gpe", PLATFORM_DEVID_NONE);
	अगर (!pdev) अणु
		status = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	pdev->dev.fwnode = fwnode;

	status = platक्रमm_device_add(pdev);
	अगर (status)
		जाओ err_add;

	surface_gpe_device = pdev;
	वापस 0;

err_add:
	platक्रमm_device_put(pdev);
err_alloc:
	fwnode_हटाओ_software_node(fwnode);
err_node:
	platक्रमm_driver_unरेजिस्टर(&surface_gpe_driver);
	वापस status;
पूर्ण
module_init(surface_gpe_init);

अटल व्योम __निकास surface_gpe_निकास(व्योम)
अणु
	काष्ठा fwnode_handle *fwnode = surface_gpe_device->dev.fwnode;

	platक्रमm_device_unरेजिस्टर(surface_gpe_device);
	platक्रमm_driver_unरेजिस्टर(&surface_gpe_driver);
	fwnode_हटाओ_software_node(fwnode);
पूर्ण
module_निकास(surface_gpe_निकास);

MODULE_AUTHOR("Maximilian Luz <luzmaximilian@gmail.com>");
MODULE_DESCRIPTION("Surface GPE/Lid Driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("dmi:*:svnMicrosoftCorporation:pnSurface*:*");
