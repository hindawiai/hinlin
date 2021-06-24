<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  HID driver क्रम Retrode 2 controller adapter and plug-in extensions
 *
 *  Copyright (c) 2017 Bastien Nocera <hadess@hadess.net>
 */

/*
 */

#समावेश <linux/input.h>
#समावेश <linux/slab.h>
#समावेश <linux/hid.h>
#समावेश <linux/module.h>
#समावेश "hid-ids.h"

#घोषणा CONTROLLER_NAME_BASE "Retrode"

अटल पूर्णांक retrode_input_configured(काष्ठा hid_device *hdev,
					काष्ठा hid_input *hi)
अणु
	काष्ठा hid_field *field = hi->report->field[0];
	स्थिर अक्षर *suffix;
	पूर्णांक number = 0;
	अक्षर *name;

	चयन (field->report->id) अणु
	हाल 0:
		suffix = "SNES Mouse";
		अवरोध;
	हाल 1:
	हाल 2:
		suffix = "SNES / N64";
		number = field->report->id;
		अवरोध;
	हाल 3:
	हाल 4:
		suffix = "Mega Drive";
		number = field->report->id - 2;
		अवरोध;
	शेष:
		hid_err(hdev, "Got unhandled report id %d\n", field->report->id);
		suffix = "Unknown";
	पूर्ण

	अगर (number)
		name = devm_kaप्र_लिखो(&hdev->dev, GFP_KERNEL,
				"%s %s #%d", CONTROLLER_NAME_BASE,
				suffix, number);
	अन्यथा
		name = devm_kaप्र_लिखो(&hdev->dev, GFP_KERNEL,
				"%s %s", CONTROLLER_NAME_BASE, suffix);

	अगर (!name)
		वापस -ENOMEM;

	hi->input->name = name;

	वापस 0;
पूर्ण

अटल पूर्णांक retrode_probe(काष्ठा hid_device *hdev,
			स्थिर काष्ठा hid_device_id *id)
अणु

	पूर्णांक ret;

	/* Has no effect on the mouse device */
	hdev->quirks |= HID_QUIRK_MULTI_INPUT;

	ret = hid_parse(hdev);
	अगर (ret)
		वापस ret;

	ret = hid_hw_start(hdev, HID_CONNECT_DEFAULT);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hid_device_id retrode_devices[] = अणु
	अणु HID_USB_DEVICE(USB_VENDOR_ID_FUTURE_TECHNOLOGY, USB_DEVICE_ID_RETRODE2) पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(hid, retrode_devices);

अटल काष्ठा hid_driver retrode_driver = अणु
	.name             = "hid-retrode",
	.id_table         = retrode_devices,
	.input_configured = retrode_input_configured,
	.probe            = retrode_probe,
पूर्ण;

module_hid_driver(retrode_driver);

MODULE_LICENSE("GPL");
