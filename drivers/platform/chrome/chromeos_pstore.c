<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Driver to instantiate Chromebook ramoops device.
//
// Copyright (C) 2013 Google, Inc.

#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pstore_ram.h>

अटल स्थिर काष्ठा dmi_प्रणाली_id chromeos_pstore_dmi_table[] __initस्थिर = अणु
	अणु
		/*
		 * Today all Chromebooks/boxes ship with Google_* as version and
		 * coreboot as bios venकरोr. No other प्रणालीs with this
		 * combination are known to date.
		 */
		.matches = अणु
			DMI_MATCH(DMI_BIOS_VENDOR, "coreboot"),
			DMI_MATCH(DMI_BIOS_VERSION, "Google_"),
		पूर्ण,
	पूर्ण,
	अणु
		/* x86-alex, the first Samsung Chromebook. */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "SAMSUNG ELECTRONICS CO., LTD."),
			DMI_MATCH(DMI_PRODUCT_NAME, "Alex"),
		पूर्ण,
	पूर्ण,
	अणु
		/* x86-mario, the Cr-48 pilot device from Google. */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "IEC"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Mario"),
		पूर्ण,
	पूर्ण,
	अणु
		/* x86-zgb, the first Acer Chromebook. */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "ACER"),
			DMI_MATCH(DMI_PRODUCT_NAME, "ZGB"),
		पूर्ण,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(dmi, chromeos_pstore_dmi_table);

/*
 * On x86 chromebooks/boxes, the firmware will keep the legacy VGA memory
 * range untouched across reboots, so we use that to store our pstore
 * contents क्रम panic logs, etc.
 */
अटल काष्ठा ramoops_platक्रमm_data chromeos_ramoops_data = अणु
	.mem_size	= 0x100000,
	.mem_address	= 0xf00000,
	.record_size	= 0x40000,
	.console_size	= 0x20000,
	.ftrace_size	= 0x20000,
	.pmsg_size	= 0x20000,
	.max_reason	= KMSG_DUMP_OOPS,
पूर्ण;

अटल काष्ठा platक्रमm_device chromeos_ramoops = अणु
	.name = "ramoops",
	.dev = अणु
		.platक्रमm_data = &chromeos_ramoops_data,
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id cros_ramoops_acpi_match[] = अणु
	अणु "GOOG9999", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, cros_ramoops_acpi_match);

अटल काष्ठा platक्रमm_driver chromeos_ramoops_acpi = अणु
	.driver		= अणु
		.name	= "chromeos_pstore",
		.acpi_match_table = ACPI_PTR(cros_ramoops_acpi_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init chromeos_probe_acpi(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	resource_माप_प्रकार len;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENOMEM;

	len = resource_size(res);
	अगर (!res->start || !len)
		वापस -ENOMEM;

	pr_info("chromeos ramoops using acpi device.\n");

	chromeos_ramoops_data.mem_size = len;
	chromeos_ramoops_data.mem_address = res->start;

	वापस 0;
पूर्ण

अटल bool __init chromeos_check_acpi(व्योम)
अणु
	अगर (!platक्रमm_driver_probe(&chromeos_ramoops_acpi, chromeos_probe_acpi))
		वापस true;
	वापस false;
पूर्ण
#अन्यथा
अटल अंतरभूत bool chromeos_check_acpi(व्योम) अणु वापस false; पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init chromeos_pstore_init(व्योम)
अणु
	bool acpi_dev_found;

	/* First check ACPI क्रम non-hardcoded values from firmware. */
	acpi_dev_found = chromeos_check_acpi();

	अगर (acpi_dev_found || dmi_check_प्रणाली(chromeos_pstore_dmi_table))
		वापस platक्रमm_device_रेजिस्टर(&chromeos_ramoops);

	वापस -ENODEV;
पूर्ण

अटल व्योम __निकास chromeos_pstore_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(&chromeos_ramoops);
पूर्ण

module_init(chromeos_pstore_init);
module_निकास(chromeos_pstore_निकास);

MODULE_DESCRIPTION("ChromeOS pstore module");
MODULE_LICENSE("GPL v2");
