<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Backlight Driver क्रम Intel-based Apples
 *
 *  Copyright (c) Red Hat <mjg@redhat.com>
 *  Based on code from Pommed:
 *  Copyright (C) 2006 Nicolas Boichat <nicolas @boichat.ch>
 *  Copyright (C) 2006 Felipe Alfaro Solana <felipe_alfaro @linuxmail.org>
 *  Copyright (C) 2007 Julien BLACHE <jb@jblache.org>
 *
 *  This driver triggers SMIs which cause the firmware to change the
 *  backlight brightness. This is icky in many ways, but it's impractical to
 *  get at the firmware code in order to figure out what it's actually करोing.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/backlight.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>
#समावेश <linux/pci.h>
#समावेश <linux/acpi.h>
#समावेश <linux/atomic.h>
#समावेश <linux/apple_bl.h>

अटल काष्ठा backlight_device *apple_backlight_device;

काष्ठा hw_data अणु
	/* I/O resource to allocate. */
	अचिन्हित दीर्घ iostart;
	अचिन्हित दीर्घ iolen;
	/* Backlight operations काष्ठाure. */
	स्थिर काष्ठा backlight_ops backlight_ops;
	व्योम (*set_brightness)(पूर्णांक);
पूर्ण;

अटल स्थिर काष्ठा hw_data *hw_data;

/* Module parameters. */
अटल पूर्णांक debug;
module_param_named(debug, debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Set to one to enable debugging messages.");

/*
 * Implementation क्रम machines with Intel chipset.
 */
अटल व्योम पूर्णांकel_chipset_set_brightness(पूर्णांक पूर्णांकensity)
अणु
	outb(0x04 | (पूर्णांकensity << 4), 0xb3);
	outb(0xbf, 0xb2);
पूर्ण

अटल पूर्णांक पूर्णांकel_chipset_send_पूर्णांकensity(काष्ठा backlight_device *bd)
अणु
	पूर्णांक पूर्णांकensity = bd->props.brightness;

	अगर (debug)
		pr_debug("setting brightness to %d\n", पूर्णांकensity);

	पूर्णांकel_chipset_set_brightness(पूर्णांकensity);
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_chipset_get_पूर्णांकensity(काष्ठा backlight_device *bd)
अणु
	पूर्णांक पूर्णांकensity;

	outb(0x03, 0xb3);
	outb(0xbf, 0xb2);
	पूर्णांकensity = inb(0xb3) >> 4;

	अगर (debug)
		pr_debug("read brightness of %d\n", पूर्णांकensity);

	वापस पूर्णांकensity;
पूर्ण

अटल स्थिर काष्ठा hw_data पूर्णांकel_chipset_data = अणु
	.iostart = 0xb2,
	.iolen = 2,
	.backlight_ops	= अणु
		.options	= BL_CORE_SUSPENDRESUME,
		.get_brightness	= पूर्णांकel_chipset_get_पूर्णांकensity,
		.update_status	= पूर्णांकel_chipset_send_पूर्णांकensity,
	पूर्ण,
	.set_brightness = पूर्णांकel_chipset_set_brightness,
पूर्ण;

/*
 * Implementation क्रम machines with Nvidia chipset.
 */
अटल व्योम nvidia_chipset_set_brightness(पूर्णांक पूर्णांकensity)
अणु
	outb(0x04 | (पूर्णांकensity << 4), 0x52f);
	outb(0xbf, 0x52e);
पूर्ण

अटल पूर्णांक nvidia_chipset_send_पूर्णांकensity(काष्ठा backlight_device *bd)
अणु
	पूर्णांक पूर्णांकensity = bd->props.brightness;

	अगर (debug)
		pr_debug("setting brightness to %d\n", पूर्णांकensity);

	nvidia_chipset_set_brightness(पूर्णांकensity);
	वापस 0;
पूर्ण

अटल पूर्णांक nvidia_chipset_get_पूर्णांकensity(काष्ठा backlight_device *bd)
अणु
	पूर्णांक पूर्णांकensity;

	outb(0x03, 0x52f);
	outb(0xbf, 0x52e);
	पूर्णांकensity = inb(0x52f) >> 4;

	अगर (debug)
		pr_debug("read brightness of %d\n", पूर्णांकensity);

	वापस पूर्णांकensity;
पूर्ण

अटल स्थिर काष्ठा hw_data nvidia_chipset_data = अणु
	.iostart = 0x52e,
	.iolen = 2,
	.backlight_ops		= अणु
		.options	= BL_CORE_SUSPENDRESUME,
		.get_brightness	= nvidia_chipset_get_पूर्णांकensity,
		.update_status	= nvidia_chipset_send_पूर्णांकensity
	पूर्ण,
	.set_brightness = nvidia_chipset_set_brightness,
पूर्ण;

अटल पूर्णांक apple_bl_add(काष्ठा acpi_device *dev)
अणु
	काष्ठा backlight_properties props;
	काष्ठा pci_dev *host;
	पूर्णांक पूर्णांकensity;

	host = pci_get_करोमुख्य_bus_and_slot(0, 0, 0);

	अगर (!host) अणु
		pr_err("unable to find PCI host\n");
		वापस -ENODEV;
	पूर्ण

	अगर (host->venकरोr == PCI_VENDOR_ID_INTEL)
		hw_data = &पूर्णांकel_chipset_data;
	अन्यथा अगर (host->venकरोr == PCI_VENDOR_ID_NVIDIA)
		hw_data = &nvidia_chipset_data;

	pci_dev_put(host);

	अगर (!hw_data) अणु
		pr_err("unknown hardware\n");
		वापस -ENODEV;
	पूर्ण

	/* Check that the hardware responds - this may not work under EFI */

	पूर्णांकensity = hw_data->backlight_ops.get_brightness(शून्य);

	अगर (!पूर्णांकensity) अणु
		hw_data->set_brightness(1);
		अगर (!hw_data->backlight_ops.get_brightness(शून्य))
			वापस -ENODEV;

		hw_data->set_brightness(0);
	पूर्ण

	अगर (!request_region(hw_data->iostart, hw_data->iolen,
			    "Apple backlight"))
		वापस -ENXIO;

	स_रखो(&props, 0, माप(काष्ठा backlight_properties));
	props.type = BACKLIGHT_PLATFORM;
	props.max_brightness = 15;
	apple_backlight_device = backlight_device_रेजिस्टर("apple_backlight",
				  शून्य, शून्य, &hw_data->backlight_ops, &props);

	अगर (IS_ERR(apple_backlight_device)) अणु
		release_region(hw_data->iostart, hw_data->iolen);
		वापस PTR_ERR(apple_backlight_device);
	पूर्ण

	apple_backlight_device->props.brightness =
		hw_data->backlight_ops.get_brightness(apple_backlight_device);
	backlight_update_status(apple_backlight_device);

	वापस 0;
पूर्ण

अटल पूर्णांक apple_bl_हटाओ(काष्ठा acpi_device *dev)
अणु
	backlight_device_unरेजिस्टर(apple_backlight_device);

	release_region(hw_data->iostart, hw_data->iolen);
	hw_data = शून्य;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id apple_bl_ids[] = अणु
	अणु"APP0002", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;

अटल काष्ठा acpi_driver apple_bl_driver = अणु
	.name = "Apple backlight",
	.ids = apple_bl_ids,
	.ops = अणु
		.add = apple_bl_add,
		.हटाओ = apple_bl_हटाओ,
	पूर्ण,
पूर्ण;

अटल atomic_t apple_bl_रेजिस्टरed = ATOMIC_INIT(0);

पूर्णांक apple_bl_रेजिस्टर(व्योम)
अणु
	अगर (atomic_xchg(&apple_bl_रेजिस्टरed, 1) == 0)
		वापस acpi_bus_रेजिस्टर_driver(&apple_bl_driver);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(apple_bl_रेजिस्टर);

व्योम apple_bl_unरेजिस्टर(व्योम)
अणु
	अगर (atomic_xchg(&apple_bl_रेजिस्टरed, 0) == 1)
		acpi_bus_unरेजिस्टर_driver(&apple_bl_driver);
पूर्ण
EXPORT_SYMBOL_GPL(apple_bl_unरेजिस्टर);

अटल पूर्णांक __init apple_bl_init(व्योम)
अणु
	वापस apple_bl_रेजिस्टर();
पूर्ण

अटल व्योम __निकास apple_bl_निकास(व्योम)
अणु
	apple_bl_unरेजिस्टर();
पूर्ण

module_init(apple_bl_init);
module_निकास(apple_bl_निकास);

MODULE_AUTHOR("Matthew Garrett <mjg@redhat.com>");
MODULE_DESCRIPTION("Apple Backlight Driver");
MODULE_LICENSE("GPL");
MODULE_DEVICE_TABLE(acpi, apple_bl_ids);
MODULE_ALIAS("mbp_nvidia_bl");
