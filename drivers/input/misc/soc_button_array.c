<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Supports क्रम the button array on SoC tablets originally running
 * Winकरोws 8.
 *
 * (C) Copyright 2014 Intel Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/acpi.h>
#समावेश <linux/dmi.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/platक्रमm_device.h>

काष्ठा soc_button_info अणु
	स्थिर अक्षर *name;
	पूर्णांक acpi_index;
	अचिन्हित पूर्णांक event_type;
	अचिन्हित पूर्णांक event_code;
	bool स्वतःrepeat;
	bool wakeup;
	bool active_low;
पूर्ण;

काष्ठा soc_device_data अणु
	स्थिर काष्ठा soc_button_info *button_info;
	पूर्णांक (*check)(काष्ठा device *dev);
पूर्ण;

/*
 * Some of the buttons like volume up/करोwn are स्वतः repeat, जबतक others
 * are not. To support both, we रेजिस्टर two platक्रमm devices, and put
 * buttons पूर्णांकo them based on whether the key should be स्वतः repeat.
 */
#घोषणा BUTTON_TYPES	2

काष्ठा soc_button_data अणु
	काष्ठा platक्रमm_device *children[BUTTON_TYPES];
पूर्ण;

/*
 * Some 2-in-1s which use the soc_button_array driver have this ugly issue in
 * their DSDT where the _LID method modअगरies the irq-type settings of the GPIOs
 * used क्रम the घातer and home buttons. The पूर्णांकend of this AML code is to
 * disable these buttons when the lid is बंदd.
 * The AML करोes this by directly poking the GPIO controllers रेजिस्टरs. This is
 * problematic because when re-enabling the irq, which happens whenever _LID
 * माला_लो called with the lid खोलो (e.g. on boot and on resume), it sets the
 * irq-type to IRQ_TYPE_LEVEL_LOW. Where as the gpio-keys driver programs the
 * type to, and expects it to be, IRQ_TYPE_EDGE_BOTH.
 * To work around this we करोn't set gpio_keys_button.gpio on these 2-in-1s,
 * instead we get the irq क्रम the GPIO ourselves, configure it as
 * IRQ_TYPE_LEVEL_LOW (to match how the _LID AML code configures it) and pass
 * the irq in gpio_keys_button.irq. Below is a list of affected devices.
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id dmi_use_low_level_irq[] = अणु
	अणु
		/*
		 * Acer Switch 10 SW5-012. _LID method messes with home- and
		 * घातer-button GPIO IRQ settings. When (re-)enabling the irq
		 * it ors in its own flags without clearing the previous set
		 * ones, leading to an irq-type of IRQ_TYPE_LEVEL_LOW |
		 * IRQ_TYPE_LEVEL_HIGH causing a continuous पूर्णांकerrupt storm.
		 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "Aspire SW5-012"),
		पूर्ण,
	पूर्ण,
	अणु
		/*
		 * Acer One S1003. _LID method messes with घातer-button GPIO
		 * IRQ settings, leading to a non working घातer-button.
		 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "Acer"),
			DMI_MATCH(DMI_PRODUCT_NAME, "One S1003"),
		पूर्ण,
	पूर्ण,
	अणु
		/*
		 * Lenovo Yoga Tab2 1051L, something messes with the home-button
		 * IRQ settings, leading to a non working home-button.
		 */
		.matches = अणु
			DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
			DMI_MATCH(DMI_PRODUCT_NAME, "60073"),
			DMI_MATCH(DMI_PRODUCT_VERSION, "1051L"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण /* Terminating entry */
पूर्ण;

/*
 * Get the Nth GPIO number from the ACPI object.
 */
अटल पूर्णांक soc_button_lookup_gpio(काष्ठा device *dev, पूर्णांक acpi_index,
				  पूर्णांक *gpio_ret, पूर्णांक *irq_ret)
अणु
	काष्ठा gpio_desc *desc;

	desc = gpiod_get_index(dev, शून्य, acpi_index, GPIOD_ASIS);
	अगर (IS_ERR(desc))
		वापस PTR_ERR(desc);

	*gpio_ret = desc_to_gpio(desc);
	*irq_ret = gpiod_to_irq(desc);

	gpiod_put(desc);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_device *
soc_button_device_create(काष्ठा platक्रमm_device *pdev,
			 स्थिर काष्ठा soc_button_info *button_info,
			 bool स्वतःrepeat)
अणु
	स्थिर काष्ठा soc_button_info *info;
	काष्ठा platक्रमm_device *pd;
	काष्ठा gpio_keys_button *gpio_keys;
	काष्ठा gpio_keys_platक्रमm_data *gpio_keys_pdata;
	पूर्णांक error, gpio, irq;
	पूर्णांक n_buttons = 0;

	क्रम (info = button_info; info->name; info++)
		अगर (info->स्वतःrepeat == स्वतःrepeat)
			n_buttons++;

	gpio_keys_pdata = devm_kzalloc(&pdev->dev,
				       माप(*gpio_keys_pdata) +
					माप(*gpio_keys) * n_buttons,
				       GFP_KERNEL);
	अगर (!gpio_keys_pdata)
		वापस ERR_PTR(-ENOMEM);

	gpio_keys = (व्योम *)(gpio_keys_pdata + 1);
	n_buttons = 0;

	क्रम (info = button_info; info->name; info++) अणु
		अगर (info->स्वतःrepeat != स्वतःrepeat)
			जारी;

		error = soc_button_lookup_gpio(&pdev->dev, info->acpi_index, &gpio, &irq);
		अगर (error || irq < 0) अणु
			/*
			 * Skip GPIO अगर not present. Note we deliberately
			 * ignore -EPROBE_DEFER errors here. On some devices
			 * Intel is using so called भव GPIOs which are not
			 * GPIOs at all but some way क्रम AML code to check some
			 * अक्रमom status bits without need a custom opregion.
			 * In some हालs the resources table we parse poपूर्णांकs to
			 * such a भव GPIO, since these are not real GPIOs
			 * we करो not have a driver क्रम these so they will never
			 * show up, thereक्रमe we ignore -EPROBE_DEFER.
			 */
			जारी;
		पूर्ण

		/* See dmi_use_low_level_irq[] comment */
		अगर (!स्वतःrepeat && dmi_check_प्रणाली(dmi_use_low_level_irq)) अणु
			irq_set_irq_type(irq, IRQ_TYPE_LEVEL_LOW);
			gpio_keys[n_buttons].irq = irq;
			gpio_keys[n_buttons].gpio = -ENOENT;
		पूर्ण अन्यथा अणु
			gpio_keys[n_buttons].gpio = gpio;
		पूर्ण

		gpio_keys[n_buttons].type = info->event_type;
		gpio_keys[n_buttons].code = info->event_code;
		gpio_keys[n_buttons].active_low = info->active_low;
		gpio_keys[n_buttons].desc = info->name;
		gpio_keys[n_buttons].wakeup = info->wakeup;
		/* These devices often use cheap buttons, use 50 ms debounce */
		gpio_keys[n_buttons].debounce_पूर्णांकerval = 50;
		n_buttons++;
	पूर्ण

	अगर (n_buttons == 0) अणु
		error = -ENODEV;
		जाओ err_मुक्त_mem;
	पूर्ण

	gpio_keys_pdata->buttons = gpio_keys;
	gpio_keys_pdata->nbuttons = n_buttons;
	gpio_keys_pdata->rep = स्वतःrepeat;

	pd = platक्रमm_device_रेजिस्टर_resndata(&pdev->dev, "gpio-keys",
					       PLATFORM_DEVID_AUTO, शून्य, 0,
					       gpio_keys_pdata,
					       माप(*gpio_keys_pdata));
	error = PTR_ERR_OR_ZERO(pd);
	अगर (error) अणु
		dev_err(&pdev->dev,
			"failed registering gpio-keys: %d\n", error);
		जाओ err_मुक्त_mem;
	पूर्ण

	वापस pd;

err_मुक्त_mem:
	devm_kमुक्त(&pdev->dev, gpio_keys_pdata);
	वापस ERR_PTR(error);
पूर्ण

अटल पूर्णांक soc_button_get_acpi_object_पूर्णांक(स्थिर जोड़ acpi_object *obj)
अणु
	अगर (obj->type != ACPI_TYPE_INTEGER)
		वापस -1;

	वापस obj->पूर्णांकeger.value;
पूर्ण

/* Parse a single ACPI0011 _DSD button descriptor */
अटल पूर्णांक soc_button_parse_btn_desc(काष्ठा device *dev,
				     स्थिर जोड़ acpi_object *desc,
				     पूर्णांक collection_uid,
				     काष्ठा soc_button_info *info)
अणु
	पूर्णांक upage, usage;

	अगर (desc->type != ACPI_TYPE_PACKAGE ||
	    desc->package.count != 5 ||
	    /* First byte should be 1 (control) */
	    soc_button_get_acpi_object_पूर्णांक(&desc->package.elements[0]) != 1 ||
	    /* Third byte should be collection uid */
	    soc_button_get_acpi_object_पूर्णांक(&desc->package.elements[2]) !=
							    collection_uid) अणु
		dev_err(dev, "Invalid ACPI Button Descriptor\n");
		वापस -ENODEV;
	पूर्ण

	info->event_type = EV_KEY;
	info->active_low = true;
	info->acpi_index =
		soc_button_get_acpi_object_पूर्णांक(&desc->package.elements[1]);
	upage = soc_button_get_acpi_object_पूर्णांक(&desc->package.elements[3]);
	usage = soc_button_get_acpi_object_पूर्णांक(&desc->package.elements[4]);

	/*
	 * The UUID: fa6bd625-9ce8-470d-a2c7-b3ca36c4282e descriptors use HID
	 * usage page and usage codes, but otherwise the device is not HID
	 * compliant: it uses one irq per button instead of generating HID
	 * input reports and some buttons should generate wakeups where as
	 * others should not, so we cannot use the HID subप्रणाली.
	 *
	 * Luckily all devices only use a few usage page + usage combinations,
	 * so we can simply check क्रम the known combinations here.
	 */
	अगर (upage == 0x01 && usage == 0x81) अणु
		info->name = "power";
		info->event_code = KEY_POWER;
		info->wakeup = true;
	पूर्ण अन्यथा अगर (upage == 0x01 && usage == 0xca) अणु
		info->name = "rotation lock switch";
		info->event_type = EV_SW;
		info->event_code = SW_ROTATE_LOCK;
	पूर्ण अन्यथा अगर (upage == 0x07 && usage == 0xe3) अणु
		info->name = "home";
		info->event_code = KEY_LEFTMETA;
		info->wakeup = true;
	पूर्ण अन्यथा अगर (upage == 0x0c && usage == 0xe9) अणु
		info->name = "volume_up";
		info->event_code = KEY_VOLUMEUP;
		info->स्वतःrepeat = true;
	पूर्ण अन्यथा अगर (upage == 0x0c && usage == 0xea) अणु
		info->name = "volume_down";
		info->event_code = KEY_VOLUMEDOWN;
		info->स्वतःrepeat = true;
	पूर्ण अन्यथा अणु
		dev_warn(dev, "Unknown button index %d upage %02x usage %02x, ignoring\n",
			 info->acpi_index, upage, usage);
		info->name = "unknown";
		info->event_code = KEY_RESERVED;
	पूर्ण

	वापस 0;
पूर्ण

/* ACPI0011 _DSD btns descriptors UUID: fa6bd625-9ce8-470d-a2c7-b3ca36c4282e */
अटल स्थिर u8 btns_desc_uuid[16] = अणु
	0x25, 0xd6, 0x6b, 0xfa, 0xe8, 0x9c, 0x0d, 0x47,
	0xa2, 0xc7, 0xb3, 0xca, 0x36, 0xc4, 0x28, 0x2e
पूर्ण;

/* Parse ACPI0011 _DSD button descriptors */
अटल काष्ठा soc_button_info *soc_button_get_button_info(काष्ठा device *dev)
अणु
	काष्ठा acpi_buffer buf = अणु ACPI_ALLOCATE_BUFFER पूर्ण;
	स्थिर जोड़ acpi_object *desc, *el0, *uuid, *btns_desc = शून्य;
	काष्ठा soc_button_info *button_info;
	acpi_status status;
	पूर्णांक i, btn, collection_uid = -1;

	status = acpi_evaluate_object_typed(ACPI_HANDLE(dev), "_DSD", शून्य,
					    &buf, ACPI_TYPE_PACKAGE);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(dev, "ACPI _DSD object not found\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	/* Look क्रम the Button Descriptors UUID */
	desc = buf.poपूर्णांकer;
	क्रम (i = 0; (i + 1) < desc->package.count; i += 2) अणु
		uuid = &desc->package.elements[i];

		अगर (uuid->type != ACPI_TYPE_BUFFER ||
		    uuid->buffer.length != 16 ||
		    desc->package.elements[i + 1].type != ACPI_TYPE_PACKAGE) अणु
			अवरोध;
		पूर्ण

		अगर (स_भेद(uuid->buffer.poपूर्णांकer, btns_desc_uuid, 16) == 0) अणु
			btns_desc = &desc->package.elements[i + 1];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!btns_desc) अणु
		dev_err(dev, "ACPI Button Descriptors not found\n");
		button_info = ERR_PTR(-ENODEV);
		जाओ out;
	पूर्ण

	/* The first package describes the collection */
	el0 = &btns_desc->package.elements[0];
	अगर (el0->type == ACPI_TYPE_PACKAGE &&
	    el0->package.count == 5 &&
	    /* First byte should be 0 (collection) */
	    soc_button_get_acpi_object_पूर्णांक(&el0->package.elements[0]) == 0 &&
	    /* Third byte should be 0 (top level collection) */
	    soc_button_get_acpi_object_पूर्णांक(&el0->package.elements[2]) == 0) अणु
		collection_uid = soc_button_get_acpi_object_पूर्णांक(
						&el0->package.elements[1]);
	पूर्ण
	अगर (collection_uid == -1) अणु
		dev_err(dev, "Invalid Button Collection Descriptor\n");
		button_info = ERR_PTR(-ENODEV);
		जाओ out;
	पूर्ण

	/* There are package.count - 1 buttons + 1 terminating empty entry */
	button_info = devm_kसुस्मृति(dev, btns_desc->package.count,
				   माप(*button_info), GFP_KERNEL);
	अगर (!button_info) अणु
		button_info = ERR_PTR(-ENOMEM);
		जाओ out;
	पूर्ण

	/* Parse the button descriptors */
	क्रम (i = 1, btn = 0; i < btns_desc->package.count; i++, btn++) अणु
		अगर (soc_button_parse_btn_desc(dev,
					      &btns_desc->package.elements[i],
					      collection_uid,
					      &button_info[btn])) अणु
			button_info = ERR_PTR(-ENODEV);
			जाओ out;
		पूर्ण
	पूर्ण

out:
	kमुक्त(buf.poपूर्णांकer);
	वापस button_info;
पूर्ण

अटल पूर्णांक soc_button_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा soc_button_data *priv = platक्रमm_get_drvdata(pdev);

	पूर्णांक i;

	क्रम (i = 0; i < BUTTON_TYPES; i++)
		अगर (priv->children[i])
			platक्रमm_device_unरेजिस्टर(priv->children[i]);

	वापस 0;
पूर्ण

अटल पूर्णांक soc_button_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा soc_device_data *device_data;
	स्थिर काष्ठा soc_button_info *button_info;
	काष्ठा soc_button_data *priv;
	काष्ठा platक्रमm_device *pd;
	पूर्णांक i;
	पूर्णांक error;

	device_data = acpi_device_get_match_data(dev);
	अगर (device_data && device_data->check) अणु
		error = device_data->check(dev);
		अगर (error)
			वापस error;
	पूर्ण

	अगर (device_data && device_data->button_info) अणु
		button_info = device_data->button_info;
	पूर्ण अन्यथा अणु
		button_info = soc_button_get_button_info(dev);
		अगर (IS_ERR(button_info))
			वापस PTR_ERR(button_info);
	पूर्ण

	error = gpiod_count(dev, शून्य);
	अगर (error < 0) अणु
		dev_dbg(dev, "no GPIO attached, ignoring...\n");
		वापस -ENODEV;
	पूर्ण

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, priv);

	क्रम (i = 0; i < BUTTON_TYPES; i++) अणु
		pd = soc_button_device_create(pdev, button_info, i == 0);
		अगर (IS_ERR(pd)) अणु
			error = PTR_ERR(pd);
			अगर (error != -ENODEV) अणु
				soc_button_हटाओ(pdev);
				वापस error;
			पूर्ण
			जारी;
		पूर्ण

		priv->children[i] = pd;
	पूर्ण

	अगर (!priv->children[0] && !priv->children[1])
		वापस -ENODEV;

	अगर (!device_data || !device_data->button_info)
		devm_kमुक्त(dev, button_info);

	वापस 0;
पूर्ण

/*
 * Definition of buttons on the tablet. The ACPI index of each button
 * is defined in section 2.8.7.2 of "Winकरोws ACPI Design Guide क्रम SoC
 * Platक्रमms"
 */
अटल स्थिर काष्ठा soc_button_info soc_button_PNP0C40[] = अणु
	अणु "power", 0, EV_KEY, KEY_POWER, false, true, true पूर्ण,
	अणु "home", 1, EV_KEY, KEY_LEFTMETA, false, true, true पूर्ण,
	अणु "volume_up", 2, EV_KEY, KEY_VOLUMEUP, true, false, true पूर्ण,
	अणु "volume_down", 3, EV_KEY, KEY_VOLUMEDOWN, true, false, true पूर्ण,
	अणु "rotation_lock", 4, EV_KEY, KEY_ROTATE_LOCK_TOGGLE, false, false, true पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा soc_device_data soc_device_PNP0C40 = अणु
	.button_info = soc_button_PNP0C40,
पूर्ण;

अटल स्थिर काष्ठा soc_button_info soc_button_INT33D3[] = अणु
	अणु "tablet_mode", 0, EV_SW, SW_TABLET_MODE, false, false, false पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा soc_device_data soc_device_INT33D3 = अणु
	.button_info = soc_button_INT33D3,
पूर्ण;

/*
 * Special device check क्रम Surface Book 2 and Surface Pro (2017).
 * Both, the Surface Pro 4 (surfacepro3_button.c) and the above mentioned
 * devices use MSHW0040 क्रम घातer and volume buttons, however the way they
 * have to be addressed dअगरfers. Make sure that we only load this drivers
 * क्रम the correct devices by checking the OEM Platक्रमm Revision provided by
 * the _DSM method.
 */
#घोषणा MSHW0040_DSM_REVISION		0x01
#घोषणा MSHW0040_DSM_GET_OMPR		0x02	// get OEM Platक्रमm Revision
अटल स्थिर guid_t MSHW0040_DSM_UUID =
	GUID_INIT(0x6fd05c69, 0xcde3, 0x49f4, 0x95, 0xed, 0xab, 0x16, 0x65,
		  0x49, 0x80, 0x35);

अटल पूर्णांक soc_device_check_MSHW0040(काष्ठा device *dev)
अणु
	acpi_handle handle = ACPI_HANDLE(dev);
	जोड़ acpi_object *result;
	u64 oem_platक्रमm_rev = 0;	// valid revisions are nonzero

	// get OEM platक्रमm revision
	result = acpi_evaluate_dsm_typed(handle, &MSHW0040_DSM_UUID,
					 MSHW0040_DSM_REVISION,
					 MSHW0040_DSM_GET_OMPR, शून्य,
					 ACPI_TYPE_INTEGER);

	अगर (result) अणु
		oem_platक्रमm_rev = result->पूर्णांकeger.value;
		ACPI_FREE(result);
	पूर्ण

	/*
	 * If the revision is zero here, the _DSM evaluation has failed. This
	 * indicates that we have a Pro 4 or Book 1 and this driver should not
	 * be used.
	 */
	अगर (oem_platक्रमm_rev == 0)
		वापस -ENODEV;

	dev_dbg(dev, "OEM Platform Revision %llu\n", oem_platक्रमm_rev);

	वापस 0;
पूर्ण

/*
 * Button infos क्रम Microsoft Surface Book 2 and Surface Pro (2017).
 * Obtained from DSDT/testing.
 */
अटल स्थिर काष्ठा soc_button_info soc_button_MSHW0040[] = अणु
	अणु "power", 0, EV_KEY, KEY_POWER, false, true, true पूर्ण,
	अणु "volume_up", 2, EV_KEY, KEY_VOLUMEUP, true, false, true पूर्ण,
	अणु "volume_down", 4, EV_KEY, KEY_VOLUMEDOWN, true, false, true पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा soc_device_data soc_device_MSHW0040 = अणु
	.button_info = soc_button_MSHW0040,
	.check = soc_device_check_MSHW0040,
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id soc_button_acpi_match[] = अणु
	अणु "PNP0C40", (अचिन्हित दीर्घ)&soc_device_PNP0C40 पूर्ण,
	अणु "INT33D3", (अचिन्हित दीर्घ)&soc_device_INT33D3 पूर्ण,
	अणु "ID9001", (अचिन्हित दीर्घ)&soc_device_INT33D3 पूर्ण,
	अणु "ACPI0011", 0 पूर्ण,

	/* Microsoft Surface Devices (5th and 6th generation) */
	अणु "MSHW0040", (अचिन्हित दीर्घ)&soc_device_MSHW0040 पूर्ण,

	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, soc_button_acpi_match);

अटल काष्ठा platक्रमm_driver soc_button_driver = अणु
	.probe          = soc_button_probe,
	.हटाओ		= soc_button_हटाओ,
	.driver		= अणु
		.name = KBUILD_MODNAME,
		.acpi_match_table = ACPI_PTR(soc_button_acpi_match),
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(soc_button_driver);

MODULE_LICENSE("GPL");
