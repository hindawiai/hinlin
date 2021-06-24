<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  adv_swbutton.c - Software Button Interface Driver.
 *
 *  (C) Copyright 2020 Advantech Corporation, Inc
 *
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/acpi.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा ACPI_BUTTON_HID_SWBTN               "AHC0310"

#घोषणा ACPI_BUTTON_NOTIFY_SWBTN_RELEASE    0x86
#घोषणा ACPI_BUTTON_NOTIFY_SWBTN_PRESSED    0x85

काष्ठा adv_swbutton अणु
	काष्ठा input_dev *input;
	अक्षर phys[32];
पूर्ण;

/*-------------------------------------------------------------------------
 *                               Driver Interface
 *--------------------------------------------------------------------------
 */
अटल व्योम adv_swbutton_notअगरy(acpi_handle handle, u32 event, व्योम *context)
अणु
	काष्ठा platक्रमm_device *device = context;
	काष्ठा adv_swbutton *button = dev_get_drvdata(&device->dev);

	चयन (event) अणु
	हाल ACPI_BUTTON_NOTIFY_SWBTN_RELEASE:
		input_report_key(button->input, KEY_PROG1, 0);
		input_sync(button->input);
		अवरोध;
	हाल ACPI_BUTTON_NOTIFY_SWBTN_PRESSED:
		input_report_key(button->input, KEY_PROG1, 1);
		input_sync(button->input);
		अवरोध;
	शेष:
		dev_dbg(&device->dev, "Unsupported event [0x%x]\n", event);
	पूर्ण
पूर्ण

अटल पूर्णांक adv_swbutton_probe(काष्ठा platक्रमm_device *device)
अणु
	काष्ठा adv_swbutton *button;
	काष्ठा input_dev *input;
	acpi_handle handle = ACPI_HANDLE(&device->dev);
	acpi_status status;
	पूर्णांक error;

	button = devm_kzalloc(&device->dev, माप(*button), GFP_KERNEL);
	अगर (!button)
		वापस -ENOMEM;

	dev_set_drvdata(&device->dev, button);

	input = devm_input_allocate_device(&device->dev);
	अगर (!input)
		वापस -ENOMEM;

	button->input = input;
	snम_लिखो(button->phys, माप(button->phys), "%s/button/input0", ACPI_BUTTON_HID_SWBTN);

	input->name = "Advantech Software Button";
	input->phys = button->phys;
	input->id.bustype = BUS_HOST;
	input->dev.parent = &device->dev;
	set_bit(EV_REP, input->evbit);
	input_set_capability(input, EV_KEY, KEY_PROG1);

	error = input_रेजिस्टर_device(input);
	अगर (error)
		वापस error;

	device_init_wakeup(&device->dev, true);

	status = acpi_install_notअगरy_handler(handle,
					     ACPI_DEVICE_NOTIFY,
					     adv_swbutton_notअगरy,
					     device);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(&device->dev, "Error installing notify handler\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adv_swbutton_हटाओ(काष्ठा platक्रमm_device *device)
अणु
	acpi_handle handle = ACPI_HANDLE(&device->dev);

	acpi_हटाओ_notअगरy_handler(handle, ACPI_DEVICE_NOTIFY,
				   adv_swbutton_notअगरy);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id button_device_ids[] = अणु
	अणुACPI_BUTTON_HID_SWBTN, 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, button_device_ids);

अटल काष्ठा platक्रमm_driver adv_swbutton_driver = अणु
	.driver = अणु
		.name = "adv_swbutton",
		.acpi_match_table = button_device_ids,
	पूर्ण,
	.probe = adv_swbutton_probe,
	.हटाओ = adv_swbutton_हटाओ,
पूर्ण;
module_platक्रमm_driver(adv_swbutton_driver);

MODULE_AUTHOR("Andrea Ho");
MODULE_DESCRIPTION("Advantech ACPI SW Button Driver");
MODULE_LICENSE("GPL v2");
