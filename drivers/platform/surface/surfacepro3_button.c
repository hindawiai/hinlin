<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * घातer/home/volume button support क्रम
 * Microsoft Surface Pro 3/4 tablet.
 *
 * Copyright (c) 2015 Intel Corporation.
 * All rights reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/input.h>
#समावेश <linux/acpi.h>
#समावेश <acpi/button.h>

#घोषणा SURFACE_PRO3_BUTTON_HID		"MSHW0028"
#घोषणा SURFACE_PRO4_BUTTON_HID		"MSHW0040"
#घोषणा SURFACE_BUTTON_OBJ_NAME		"VGBI"
#घोषणा SURFACE_BUTTON_DEVICE_NAME	"Surface Pro 3/4 Buttons"

#घोषणा MSHW0040_DSM_REVISION		0x01
#घोषणा MSHW0040_DSM_GET_OMPR		0x02	// get OEM Platक्रमm Revision
अटल स्थिर guid_t MSHW0040_DSM_UUID =
	GUID_INIT(0x6fd05c69, 0xcde3, 0x49f4, 0x95, 0xed, 0xab, 0x16, 0x65,
		  0x49, 0x80, 0x35);

#घोषणा SURFACE_BUTTON_NOTIFY_TABLET_MODE	0xc8

#घोषणा SURFACE_BUTTON_NOTIFY_PRESS_POWER	0xc6
#घोषणा SURFACE_BUTTON_NOTIFY_RELEASE_POWER	0xc7

#घोषणा SURFACE_BUTTON_NOTIFY_PRESS_HOME	0xc4
#घोषणा SURFACE_BUTTON_NOTIFY_RELEASE_HOME	0xc5

#घोषणा SURFACE_BUTTON_NOTIFY_PRESS_VOLUME_UP	0xc0
#घोषणा SURFACE_BUTTON_NOTIFY_RELEASE_VOLUME_UP	0xc1

#घोषणा SURFACE_BUTTON_NOTIFY_PRESS_VOLUME_DOWN		0xc2
#घोषणा SURFACE_BUTTON_NOTIFY_RELEASE_VOLUME_DOWN	0xc3

MODULE_AUTHOR("Chen Yu");
MODULE_DESCRIPTION("Surface Pro3 Button Driver");
MODULE_LICENSE("GPL v2");

/*
 * Power button, Home button, Volume buttons support is supposed to
 * be covered by drivers/input/misc/soc_button_array.c, which is implemented
 * according to "Windows ACPI Design Guide for SoC Platforms".
 * However surface pro3 seems not to obey the specs, instead it uses
 * device VGBI(MSHW0028) क्रम dispatching the events.
 * We choose acpi_driver rather than platक्रमm_driver/i2c_driver because
 * although VGBI has an i2c resource connected to i2c controller, it
 * is not embedded in any i2c controller's scope, thus neither platक्रमm_device
 * will be created, nor i2c_client will be क्रमागतerated, we have to use
 * acpi_driver.
 */
अटल स्थिर काष्ठा acpi_device_id surface_button_device_ids[] = अणु
	अणुSURFACE_PRO3_BUTTON_HID,    0पूर्ण,
	अणुSURFACE_PRO4_BUTTON_HID,    0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, surface_button_device_ids);

काष्ठा surface_button अणु
	अचिन्हित पूर्णांक type;
	काष्ठा input_dev *input;
	अक्षर phys[32];			/* क्रम input device */
	अचिन्हित दीर्घ pushed;
	bool suspended;
पूर्ण;

अटल व्योम surface_button_notअगरy(काष्ठा acpi_device *device, u32 event)
अणु
	काष्ठा surface_button *button = acpi_driver_data(device);
	काष्ठा input_dev *input;
	पूर्णांक key_code = KEY_RESERVED;
	bool pressed = false;

	चयन (event) अणु
	/* Power button press,release handle */
	हाल SURFACE_BUTTON_NOTIFY_PRESS_POWER:
		pressed = true;
		fallthrough;
	हाल SURFACE_BUTTON_NOTIFY_RELEASE_POWER:
		key_code = KEY_POWER;
		अवरोध;
	/* Home button press,release handle */
	हाल SURFACE_BUTTON_NOTIFY_PRESS_HOME:
		pressed = true;
		fallthrough;
	हाल SURFACE_BUTTON_NOTIFY_RELEASE_HOME:
		key_code = KEY_LEFTMETA;
		अवरोध;
	/* Volume up button press,release handle */
	हाल SURFACE_BUTTON_NOTIFY_PRESS_VOLUME_UP:
		pressed = true;
		fallthrough;
	हाल SURFACE_BUTTON_NOTIFY_RELEASE_VOLUME_UP:
		key_code = KEY_VOLUMEUP;
		अवरोध;
	/* Volume करोwn button press,release handle */
	हाल SURFACE_BUTTON_NOTIFY_PRESS_VOLUME_DOWN:
		pressed = true;
		fallthrough;
	हाल SURFACE_BUTTON_NOTIFY_RELEASE_VOLUME_DOWN:
		key_code = KEY_VOLUMEDOWN;
		अवरोध;
	हाल SURFACE_BUTTON_NOTIFY_TABLET_MODE:
		dev_warn_once(&device->dev, "Tablet mode is not supported\n");
		अवरोध;
	शेष:
		dev_info_ratelimited(&device->dev,
				     "Unsupported event [0x%x]\n", event);
		अवरोध;
	पूर्ण
	input = button->input;
	अगर (key_code == KEY_RESERVED)
		वापस;
	अगर (pressed)
		pm_wakeup_dev_event(&device->dev, 0, button->suspended);
	अगर (button->suspended)
		वापस;
	input_report_key(input, key_code, pressed?1:0);
	input_sync(input);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक surface_button_suspend(काष्ठा device *dev)
अणु
	काष्ठा acpi_device *device = to_acpi_device(dev);
	काष्ठा surface_button *button = acpi_driver_data(device);

	button->suspended = true;
	वापस 0;
पूर्ण

अटल पूर्णांक surface_button_resume(काष्ठा device *dev)
अणु
	काष्ठा acpi_device *device = to_acpi_device(dev);
	काष्ठा surface_button *button = acpi_driver_data(device);

	button->suspended = false;
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Surface Pro 4 and Surface Book 2 / Surface Pro 2017 use the same device
 * ID (MSHW0040) क्रम the घातer/volume buttons. Make sure this is the right
 * device by checking क्रम the _DSM method and OEM Platक्रमm Revision.
 *
 * Returns true अगर the driver should bind to this device, i.e. the device is
 * either MSWH0028 (Pro 3) or MSHW0040 on a Pro 4 or Book 1.
 */
अटल bool surface_button_check_MSHW0040(काष्ठा acpi_device *dev)
अणु
	acpi_handle handle = dev->handle;
	जोड़ acpi_object *result;
	u64 oem_platक्रमm_rev = 0;	// valid revisions are nonzero

	// get OEM platक्रमm revision
	result = acpi_evaluate_dsm_typed(handle, &MSHW0040_DSM_UUID,
					 MSHW0040_DSM_REVISION,
					 MSHW0040_DSM_GET_OMPR,
					 शून्य, ACPI_TYPE_INTEGER);

	/*
	 * If evaluating the _DSM fails, the method is not present. This means
	 * that we have either MSHW0028 or MSHW0040 on Pro 4 or Book 1, so we
	 * should use this driver. We use revision 0 indicating it is
	 * unavailable.
	 */

	अगर (result) अणु
		oem_platक्रमm_rev = result->पूर्णांकeger.value;
		ACPI_FREE(result);
	पूर्ण

	dev_dbg(&dev->dev, "OEM Platform Revision %llu\n", oem_platक्रमm_rev);

	वापस oem_platक्रमm_rev == 0;
पूर्ण


अटल पूर्णांक surface_button_add(काष्ठा acpi_device *device)
अणु
	काष्ठा surface_button *button;
	काष्ठा input_dev *input;
	स्थिर अक्षर *hid = acpi_device_hid(device);
	अक्षर *name;
	पूर्णांक error;

	अगर (म_भेदन(acpi_device_bid(device), SURFACE_BUTTON_OBJ_NAME,
	    म_माप(SURFACE_BUTTON_OBJ_NAME)))
		वापस -ENODEV;

	अगर (!surface_button_check_MSHW0040(device))
		वापस -ENODEV;

	button = kzalloc(माप(काष्ठा surface_button), GFP_KERNEL);
	अगर (!button)
		वापस -ENOMEM;

	device->driver_data = button;
	button->input = input = input_allocate_device();
	अगर (!input) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_button;
	पूर्ण

	name = acpi_device_name(device);
	म_नकल(name, SURFACE_BUTTON_DEVICE_NAME);
	snम_लिखो(button->phys, माप(button->phys), "%s/buttons", hid);

	input->name = name;
	input->phys = button->phys;
	input->id.bustype = BUS_HOST;
	input->dev.parent = &device->dev;
	input_set_capability(input, EV_KEY, KEY_POWER);
	input_set_capability(input, EV_KEY, KEY_LEFTMETA);
	input_set_capability(input, EV_KEY, KEY_VOLUMEUP);
	input_set_capability(input, EV_KEY, KEY_VOLUMEDOWN);

	error = input_रेजिस्टर_device(input);
	अगर (error)
		जाओ err_मुक्त_input;

	device_init_wakeup(&device->dev, true);
	dev_info(&device->dev,
			"%s [%s]\n", name, acpi_device_bid(device));
	वापस 0;

 err_मुक्त_input:
	input_मुक्त_device(input);
 err_मुक्त_button:
	kमुक्त(button);
	वापस error;
पूर्ण

अटल पूर्णांक surface_button_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा surface_button *button = acpi_driver_data(device);

	input_unरेजिस्टर_device(button->input);
	kमुक्त(button);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(surface_button_pm,
		surface_button_suspend, surface_button_resume);

अटल काष्ठा acpi_driver surface_button_driver = अणु
	.name = "surface_pro3_button",
	.class = "SurfacePro3",
	.ids = surface_button_device_ids,
	.ops = अणु
		.add = surface_button_add,
		.हटाओ = surface_button_हटाओ,
		.notअगरy = surface_button_notअगरy,
	पूर्ण,
	.drv.pm = &surface_button_pm,
पूर्ण;

module_acpi_driver(surface_button_driver);
