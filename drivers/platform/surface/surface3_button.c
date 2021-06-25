<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Supports क्रम the button array on the Surface tablets.
 *
 * (C) Copyright 2016 Red Hat, Inc
 *
 * Based on soc_button_array.c:
 *
 * अणुCपूर्ण Copyright 2014 Intel Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/input.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/platक्रमm_device.h>


#घोषणा SURFACE_BUTTON_OBJ_NAME		"TEV2"
#घोषणा MAX_NBUTTONS			4

/*
 * Some of the buttons like volume up/करोwn are स्वतः repeat, जबतक others
 * are not. To support both, we रेजिस्टर two platक्रमm devices, and put
 * buttons पूर्णांकo them based on whether the key should be स्वतः repeat.
 */
#घोषणा BUTTON_TYPES			2

/*
 * Power button, Home button, Volume buttons support is supposed to
 * be covered by drivers/input/misc/soc_button_array.c, which is implemented
 * according to "Windows ACPI Design Guide for SoC Platforms".
 * However surface 3 seems not to obey the specs, instead it uses
 * device TEV2(MSHW0028) क्रम declaring the GPIOs. The gpios are also slightly
 * dअगरferent in which the Home button is active high.
 * Compared to surfacepro3_button.c which also handles MSHW0028, the Surface 3
 * is a reduce platक्रमm and thus uses GPIOs, not ACPI events.
 * We choose an I2C driver here because we need to access the resources
 * declared under the device node, जबतक surfacepro3_button.c only needs
 * the ACPI companion node.
 */
अटल स्थिर काष्ठा acpi_device_id surface3_acpi_match[] = अणु
	अणु "MSHW0028", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, surface3_acpi_match);

काष्ठा surface3_button_info अणु
	स्थिर अक्षर *name;
	पूर्णांक acpi_index;
	अचिन्हित पूर्णांक event_type;
	अचिन्हित पूर्णांक event_code;
	bool स्वतःrepeat;
	bool wakeup;
	bool active_low;
पूर्ण;

काष्ठा surface3_button_data अणु
	काष्ठा platक्रमm_device *children[BUTTON_TYPES];
पूर्ण;

/*
 * Get the Nth GPIO number from the ACPI object.
 */
अटल पूर्णांक surface3_button_lookup_gpio(काष्ठा device *dev, पूर्णांक acpi_index)
अणु
	काष्ठा gpio_desc *desc;
	पूर्णांक gpio;

	desc = gpiod_get_index(dev, शून्य, acpi_index, GPIOD_ASIS);
	अगर (IS_ERR(desc))
		वापस PTR_ERR(desc);

	gpio = desc_to_gpio(desc);

	gpiod_put(desc);

	वापस gpio;
पूर्ण

अटल काष्ठा platक्रमm_device *
surface3_button_device_create(काष्ठा i2c_client *client,
			      स्थिर काष्ठा surface3_button_info *button_info,
			      bool स्वतःrepeat)
अणु
	स्थिर काष्ठा surface3_button_info *info;
	काष्ठा platक्रमm_device *pd;
	काष्ठा gpio_keys_button *gpio_keys;
	काष्ठा gpio_keys_platक्रमm_data *gpio_keys_pdata;
	पूर्णांक n_buttons = 0;
	पूर्णांक gpio;
	पूर्णांक error;

	gpio_keys_pdata = devm_kzalloc(&client->dev,
				       माप(*gpio_keys_pdata) +
				       माप(*gpio_keys) * MAX_NBUTTONS,
				       GFP_KERNEL);
	अगर (!gpio_keys_pdata)
		वापस ERR_PTR(-ENOMEM);

	gpio_keys = (व्योम *)(gpio_keys_pdata + 1);

	क्रम (info = button_info; info->name; info++) अणु
		अगर (info->स्वतःrepeat != स्वतःrepeat)
			जारी;

		gpio = surface3_button_lookup_gpio(&client->dev,
						   info->acpi_index);
		अगर (!gpio_is_valid(gpio))
			जारी;

		gpio_keys[n_buttons].type = info->event_type;
		gpio_keys[n_buttons].code = info->event_code;
		gpio_keys[n_buttons].gpio = gpio;
		gpio_keys[n_buttons].active_low = info->active_low;
		gpio_keys[n_buttons].desc = info->name;
		gpio_keys[n_buttons].wakeup = info->wakeup;
		n_buttons++;
	पूर्ण

	अगर (n_buttons == 0) अणु
		error = -ENODEV;
		जाओ err_मुक्त_mem;
	पूर्ण

	gpio_keys_pdata->buttons = gpio_keys;
	gpio_keys_pdata->nbuttons = n_buttons;
	gpio_keys_pdata->rep = स्वतःrepeat;

	pd = platक्रमm_device_alloc("gpio-keys", PLATFORM_DEVID_AUTO);
	अगर (!pd) अणु
		error = -ENOMEM;
		जाओ err_मुक्त_mem;
	पूर्ण

	error = platक्रमm_device_add_data(pd, gpio_keys_pdata,
					 माप(*gpio_keys_pdata));
	अगर (error)
		जाओ err_मुक्त_pdev;

	error = platक्रमm_device_add(pd);
	अगर (error)
		जाओ err_मुक्त_pdev;

	वापस pd;

err_मुक्त_pdev:
	platक्रमm_device_put(pd);
err_मुक्त_mem:
	devm_kमुक्त(&client->dev, gpio_keys_pdata);
	वापस ERR_PTR(error);
पूर्ण

अटल पूर्णांक surface3_button_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा surface3_button_data *priv = i2c_get_clientdata(client);

	पूर्णांक i;

	क्रम (i = 0; i < BUTTON_TYPES; i++)
		अगर (priv->children[i])
			platक्रमm_device_unरेजिस्टर(priv->children[i]);

	वापस 0;
पूर्ण

अटल काष्ठा surface3_button_info surface3_button_surface3[] = अणु
	अणु "power", 0, EV_KEY, KEY_POWER, false, true, true पूर्ण,
	अणु "home", 1, EV_KEY, KEY_LEFTMETA, false, true, false पूर्ण,
	अणु "volume_up", 2, EV_KEY, KEY_VOLUMEUP, true, false, true पूर्ण,
	अणु "volume_down", 3, EV_KEY, KEY_VOLUMEDOWN, true, false, true पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक surface3_button_probe(काष्ठा i2c_client *client,
				 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा surface3_button_data *priv;
	काष्ठा platक्रमm_device *pd;
	पूर्णांक i;
	पूर्णांक error;

	अगर (म_भेदन(acpi_device_bid(ACPI_COMPANION(&client->dev)),
		    SURFACE_BUTTON_OBJ_NAME,
		    म_माप(SURFACE_BUTTON_OBJ_NAME)))
		वापस -ENODEV;

	error = gpiod_count(dev, शून्य);
	अगर (error < 0) अणु
		dev_dbg(dev, "no GPIO attached, ignoring...\n");
		वापस error;
	पूर्ण

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	i2c_set_clientdata(client, priv);

	क्रम (i = 0; i < BUTTON_TYPES; i++) अणु
		pd = surface3_button_device_create(client,
						   surface3_button_surface3,
						   i == 0);
		अगर (IS_ERR(pd)) अणु
			error = PTR_ERR(pd);
			अगर (error != -ENODEV) अणु
				surface3_button_हटाओ(client);
				वापस error;
			पूर्ण
			जारी;
		पूर्ण

		priv->children[i] = pd;
	पूर्ण

	अगर (!priv->children[0] && !priv->children[1])
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id surface3_id[] = अणु
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, surface3_id);

अटल काष्ठा i2c_driver surface3_driver = अणु
	.probe = surface3_button_probe,
	.हटाओ = surface3_button_हटाओ,
	.id_table = surface3_id,
	.driver = अणु
		.name = "surface3",
		.acpi_match_table = ACPI_PTR(surface3_acpi_match),
	पूर्ण,
पूर्ण;
module_i2c_driver(surface3_driver);

MODULE_AUTHOR("Benjamin Tissoires <benjamin.tissoires@gmail.com>");
MODULE_DESCRIPTION("surface3 button array driver");
MODULE_LICENSE("GPL v2");
