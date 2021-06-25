<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
#समावेश <linux/module.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/acpi.h>
#समावेश <acpi/button.h>

MODULE_AUTHOR("Josh Triplett");
MODULE_DESCRIPTION("ACPI Tiny Power Button Driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक घातer_संकेत __पढ़ो_mostly = CONFIG_ACPI_TINY_POWER_BUTTON_SIGNAL;
module_param(घातer_संकेत, पूर्णांक, 0644);
MODULE_PARM_DESC(घातer_संकेत, "Power button sends this signal to init");

अटल स्थिर काष्ठा acpi_device_id tiny_घातer_button_device_ids[] = अणु
	अणु ACPI_BUTTON_HID_POWER, 0 पूर्ण,
	अणु ACPI_BUTTON_HID_POWERF, 0 पूर्ण,
	अणु "", 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, tiny_घातer_button_device_ids);

अटल पूर्णांक acpi_noop_add_हटाओ(काष्ठा acpi_device *device)
अणु
	वापस 0;
पूर्ण

अटल व्योम acpi_tiny_घातer_button_notअगरy(काष्ठा acpi_device *device, u32 event)
अणु
	समाप्त_cad_pid(घातer_संकेत, 1);
पूर्ण

अटल काष्ठा acpi_driver acpi_tiny_घातer_button_driver = अणु
	.name = "tiny-power-button",
	.class = "tiny-power-button",
	.ids = tiny_घातer_button_device_ids,
	.ops = अणु
		.add = acpi_noop_add_हटाओ,
		.हटाओ = acpi_noop_add_हटाओ,
		.notअगरy = acpi_tiny_घातer_button_notअगरy,
	पूर्ण,
पूर्ण;

module_acpi_driver(acpi_tiny_घातer_button_driver);
