<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  OLPC XO-1.5 ebook चयन driver
 *  (based on generic ACPI button driver)
 *
 *  Copyright (C) 2009 Paul Fox <pgf@laptop.org>
 *  Copyright (C) 2010 One Laptop per Child
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/input.h>
#समावेश <linux/acpi.h>

#घोषणा MODULE_NAME "xo15-ebook"

#घोषणा XO15_EBOOK_CLASS		MODULE_NAME
#घोषणा XO15_EBOOK_TYPE_UNKNOWN	0x00
#घोषणा XO15_EBOOK_NOTIFY_STATUS	0x80

#घोषणा XO15_EBOOK_SUBCLASS		"ebook"
#घोषणा XO15_EBOOK_HID			"XO15EBK"
#घोषणा XO15_EBOOK_DEVICE_NAME		"EBook Switch"

MODULE_DESCRIPTION("OLPC XO-1.5 ebook switch driver");
MODULE_LICENSE("GPL");

अटल स्थिर काष्ठा acpi_device_id ebook_device_ids[] = अणु
	अणु XO15_EBOOK_HID, 0 पूर्ण,
	अणु "", 0 पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, ebook_device_ids);

काष्ठा ebook_चयन अणु
	काष्ठा input_dev *input;
	अक्षर phys[32];			/* क्रम input device */
पूर्ण;

अटल पूर्णांक ebook_send_state(काष्ठा acpi_device *device)
अणु
	काष्ठा ebook_चयन *button = acpi_driver_data(device);
	अचिन्हित दीर्घ दीर्घ state;
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(device->handle, "EBK", शून्य, &state);
	अगर (ACPI_FAILURE(status))
		वापस -EIO;

	/* input layer checks अगर event is redundant */
	input_report_चयन(button->input, SW_TABLET_MODE, !state);
	input_sync(button->input);
	वापस 0;
पूर्ण

अटल व्योम ebook_चयन_notअगरy(काष्ठा acpi_device *device, u32 event)
अणु
	चयन (event) अणु
	हाल ACPI_FIXED_HARDWARE_EVENT:
	हाल XO15_EBOOK_NOTIFY_STATUS:
		ebook_send_state(device);
		अवरोध;
	शेष:
		acpi_handle_debug(device->handle,
				  "Unsupported event [0x%x]\n", event);
		अवरोध;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ebook_चयन_resume(काष्ठा device *dev)
अणु
	वापस ebook_send_state(to_acpi_device(dev));
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(ebook_चयन_pm, शून्य, ebook_चयन_resume);

अटल पूर्णांक ebook_चयन_add(काष्ठा acpi_device *device)
अणु
	काष्ठा ebook_चयन *button;
	काष्ठा input_dev *input;
	स्थिर अक्षर *hid = acpi_device_hid(device);
	अक्षर *name, *class;
	पूर्णांक error;

	button = kzalloc(माप(काष्ठा ebook_चयन), GFP_KERNEL);
	अगर (!button)
		वापस -ENOMEM;

	device->driver_data = button;

	button->input = input = input_allocate_device();
	अगर (!input) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_button;
	पूर्ण

	name = acpi_device_name(device);
	class = acpi_device_class(device);

	अगर (म_भेद(hid, XO15_EBOOK_HID)) अणु
		pr_err("Unsupported hid [%s]\n", hid);
		error = -ENODEV;
		जाओ err_मुक्त_input;
	पूर्ण

	म_नकल(name, XO15_EBOOK_DEVICE_NAME);
	प्र_लिखो(class, "%s/%s", XO15_EBOOK_CLASS, XO15_EBOOK_SUBCLASS);

	snम_लिखो(button->phys, माप(button->phys), "%s/button/input0", hid);

	input->name = name;
	input->phys = button->phys;
	input->id.bustype = BUS_HOST;
	input->dev.parent = &device->dev;

	input->evbit[0] = BIT_MASK(EV_SW);
	set_bit(SW_TABLET_MODE, input->swbit);

	error = input_रेजिस्टर_device(input);
	अगर (error)
		जाओ err_मुक्त_input;

	ebook_send_state(device);

	अगर (device->wakeup.flags.valid) अणु
		/* Button's GPE is run-wake GPE */
		acpi_enable_gpe(device->wakeup.gpe_device,
				device->wakeup.gpe_number);
		device_set_wakeup_enable(&device->dev, true);
	पूर्ण

	वापस 0;

 err_मुक्त_input:
	input_मुक्त_device(input);
 err_मुक्त_button:
	kमुक्त(button);
	वापस error;
पूर्ण

अटल पूर्णांक ebook_चयन_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा ebook_चयन *button = acpi_driver_data(device);

	input_unरेजिस्टर_device(button->input);
	kमुक्त(button);
	वापस 0;
पूर्ण

अटल काष्ठा acpi_driver xo15_ebook_driver = अणु
	.name = MODULE_NAME,
	.class = XO15_EBOOK_CLASS,
	.ids = ebook_device_ids,
	.ops = अणु
		.add = ebook_चयन_add,
		.हटाओ = ebook_चयन_हटाओ,
		.notअगरy = ebook_चयन_notअगरy,
	पूर्ण,
	.drv.pm = &ebook_चयन_pm,
पूर्ण;
module_acpi_driver(xo15_ebook_driver);
