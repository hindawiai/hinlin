<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  Copyright 2013 Matthew Garrett <mjg59@srcf.ucam.org>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>

MODULE_LICENSE("GPL");

अटल पूर्णांक smartconnect_acpi_init(काष्ठा acpi_device *acpi)
अणु
	अचिन्हित दीर्घ दीर्घ value;
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(acpi->handle, "GAOS", शून्य, &value);
	अगर (ACPI_FAILURE(status))
		वापस -EINVAL;

	अगर (value & 0x1) अणु
		dev_info(&acpi->dev, "Disabling Intel Smart Connect\n");
		status = acpi_execute_simple_method(acpi->handle, "SAOS", 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id smartconnect_ids[] = अणु
	अणु"INT33A0", 0पूर्ण,
	अणु"", 0पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, smartconnect_ids);

अटल काष्ठा acpi_driver smartconnect_driver = अणु
	.owner = THIS_MODULE,
	.name = "intel_smart_connect",
	.class = "intel_smart_connect",
	.ids = smartconnect_ids,
	.ops = अणु
		.add = smartconnect_acpi_init,
	पूर्ण,
पूर्ण;

module_acpi_driver(smartconnect_driver);
