<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  atlas_btns.c - Atlas Wallmount Touchscreen ACPI Extras
 *
 *  Copyright (C) 2006 Jaya Kumar
 *  Based on Toshiba ACPI by John Belmonte and ASUS ACPI
 *  This work was sponsored by CIS(M) Sdn Bhd.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/types.h>
#समावेश <linux/acpi.h>
#समावेश <linux/uaccess.h>

#घोषणा ACPI_ATLAS_NAME		"Atlas ACPI"
#घोषणा ACPI_ATLAS_CLASS	"Atlas"

अटल अचिन्हित लघु atlas_keymap[16];
अटल काष्ठा input_dev *input_dev;

/* button handling code */
अटल acpi_status acpi_atlas_button_setup(acpi_handle region_handle,
		    u32 function, व्योम *handler_context, व्योम **वापस_context)
अणु
	*वापस_context =
		(function != ACPI_REGION_DEACTIVATE) ? handler_context : शून्य;

	वापस AE_OK;
पूर्ण

अटल acpi_status acpi_atlas_button_handler(u32 function,
		      acpi_physical_address address,
		      u32 bit_width, u64 *value,
		      व्योम *handler_context, व्योम *region_context)
अणु
	acpi_status status;

	अगर (function == ACPI_WRITE) अणु
		पूर्णांक code = address & 0x0f;
		पूर्णांक key_करोwn = !(address & 0x10);

		input_event(input_dev, EV_MSC, MSC_SCAN, code);
		input_report_key(input_dev, atlas_keymap[code], key_करोwn);
		input_sync(input_dev);

		status = AE_OK;
	पूर्ण अन्यथा अणु
		pr_warn("shrugged on unexpected function: function=%x,address=%lx,value=%x\n",
			function, (अचिन्हित दीर्घ)address, (u32)*value);
		status = AE_BAD_PARAMETER;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक atlas_acpi_button_add(काष्ठा acpi_device *device)
अणु
	acpi_status status;
	पूर्णांक i;
	पूर्णांक err;

	input_dev = input_allocate_device();
	अगर (!input_dev) अणु
		pr_err("unable to allocate input device\n");
		वापस -ENOMEM;
	पूर्ण

	input_dev->name = "Atlas ACPI button driver";
	input_dev->phys = "ASIM0000/atlas/input0";
	input_dev->id.bustype = BUS_HOST;
	input_dev->keycode = atlas_keymap;
	input_dev->keycodesize = माप(अचिन्हित लघु);
	input_dev->keycodemax = ARRAY_SIZE(atlas_keymap);

	input_set_capability(input_dev, EV_MSC, MSC_SCAN);
	__set_bit(EV_KEY, input_dev->evbit);
	क्रम (i = 0; i < ARRAY_SIZE(atlas_keymap); i++) अणु
		अगर (i < 9) अणु
			atlas_keymap[i] = KEY_F1 + i;
			__set_bit(KEY_F1 + i, input_dev->keybit);
		पूर्ण अन्यथा
			atlas_keymap[i] = KEY_RESERVED;
	पूर्ण

	err = input_रेजिस्टर_device(input_dev);
	अगर (err) अणु
		pr_err("couldn't register input device\n");
		input_मुक्त_device(input_dev);
		वापस err;
	पूर्ण

	/* hookup button handler */
	status = acpi_install_address_space_handler(device->handle,
				0x81, &acpi_atlas_button_handler,
				&acpi_atlas_button_setup, device);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("error installing addr spc handler\n");
		input_unरेजिस्टर_device(input_dev);
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक atlas_acpi_button_हटाओ(काष्ठा acpi_device *device)
अणु
	acpi_status status;

	status = acpi_हटाओ_address_space_handler(device->handle,
				0x81, &acpi_atlas_button_handler);
	अगर (ACPI_FAILURE(status))
		pr_err("error removing addr spc handler\n");

	input_unरेजिस्टर_device(input_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id atlas_device_ids[] = अणु
	अणु"ASIM0000", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, atlas_device_ids);

अटल काष्ठा acpi_driver atlas_acpi_driver = अणु
	.name	= ACPI_ATLAS_NAME,
	.class	= ACPI_ATLAS_CLASS,
	.owner	= THIS_MODULE,
	.ids	= atlas_device_ids,
	.ops	= अणु
		.add	= atlas_acpi_button_add,
		.हटाओ	= atlas_acpi_button_हटाओ,
	पूर्ण,
पूर्ण;
module_acpi_driver(atlas_acpi_driver);

MODULE_AUTHOR("Jaya Kumar");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Atlas button driver");

