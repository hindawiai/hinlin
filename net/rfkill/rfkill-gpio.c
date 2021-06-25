<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2011, NVIDIA Corporation.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/rfसमाप्त.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/gpio/consumer.h>

काष्ठा rfसमाप्त_gpio_data अणु
	स्थिर अक्षर		*name;
	क्रमागत rfसमाप्त_type	type;
	काष्ठा gpio_desc	*reset_gpio;
	काष्ठा gpio_desc	*shutकरोwn_gpio;

	काष्ठा rfसमाप्त		*rfसमाप्त_dev;
	काष्ठा clk		*clk;

	bool			clk_enabled;
पूर्ण;

अटल पूर्णांक rfसमाप्त_gpio_set_घातer(व्योम *data, bool blocked)
अणु
	काष्ठा rfसमाप्त_gpio_data *rfसमाप्त = data;

	अगर (!blocked && !IS_ERR(rfसमाप्त->clk) && !rfसमाप्त->clk_enabled)
		clk_enable(rfसमाप्त->clk);

	gpiod_set_value_cansleep(rfसमाप्त->shutकरोwn_gpio, !blocked);
	gpiod_set_value_cansleep(rfसमाप्त->reset_gpio, !blocked);

	अगर (blocked && !IS_ERR(rfसमाप्त->clk) && rfसमाप्त->clk_enabled)
		clk_disable(rfसमाप्त->clk);

	rfसमाप्त->clk_enabled = !blocked;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा rfसमाप्त_ops rfसमाप्त_gpio_ops = अणु
	.set_block = rfसमाप्त_gpio_set_घातer,
पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_params reset_gpios = अणु 0, 0, false पूर्ण;
अटल स्थिर काष्ठा acpi_gpio_params shutकरोwn_gpios = अणु 1, 0, false पूर्ण;

अटल स्थिर काष्ठा acpi_gpio_mapping acpi_rfसमाप्त_शेष_gpios[] = अणु
	अणु "reset-gpios", &reset_gpios, 1 पूर्ण,
	अणु "shutdown-gpios", &shutकरोwn_gpios, 1 पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल पूर्णांक rfसमाप्त_gpio_acpi_probe(काष्ठा device *dev,
				  काष्ठा rfसमाप्त_gpio_data *rfसमाप्त)
अणु
	स्थिर काष्ठा acpi_device_id *id;

	id = acpi_match_device(dev->driver->acpi_match_table, dev);
	अगर (!id)
		वापस -ENODEV;

	rfसमाप्त->type = (अचिन्हित)id->driver_data;

	वापस devm_acpi_dev_add_driver_gpios(dev, acpi_rfसमाप्त_शेष_gpios);
पूर्ण

अटल पूर्णांक rfसमाप्त_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rfसमाप्त_gpio_data *rfसमाप्त;
	काष्ठा gpio_desc *gpio;
	स्थिर अक्षर *type_name;
	पूर्णांक ret;

	rfसमाप्त = devm_kzalloc(&pdev->dev, माप(*rfसमाप्त), GFP_KERNEL);
	अगर (!rfसमाप्त)
		वापस -ENOMEM;

	device_property_पढ़ो_string(&pdev->dev, "name", &rfसमाप्त->name);
	device_property_पढ़ो_string(&pdev->dev, "type", &type_name);

	अगर (!rfसमाप्त->name)
		rfसमाप्त->name = dev_name(&pdev->dev);

	rfसमाप्त->type = rfसमाप्त_find_type(type_name);

	अगर (ACPI_HANDLE(&pdev->dev)) अणु
		ret = rfसमाप्त_gpio_acpi_probe(&pdev->dev, rfसमाप्त);
		अगर (ret)
			वापस ret;
	पूर्ण

	rfसमाप्त->clk = devm_clk_get(&pdev->dev, शून्य);

	gpio = devm_gpiod_get_optional(&pdev->dev, "reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(gpio))
		वापस PTR_ERR(gpio);

	rfसमाप्त->reset_gpio = gpio;

	gpio = devm_gpiod_get_optional(&pdev->dev, "shutdown", GPIOD_OUT_LOW);
	अगर (IS_ERR(gpio))
		वापस PTR_ERR(gpio);

	rfसमाप्त->shutकरोwn_gpio = gpio;

	/* Make sure at-least one GPIO is defined क्रम this instance */
	अगर (!rfसमाप्त->reset_gpio && !rfसमाप्त->shutकरोwn_gpio) अणु
		dev_err(&pdev->dev, "invalid platform data\n");
		वापस -EINVAL;
	पूर्ण

	rfसमाप्त->rfसमाप्त_dev = rfसमाप्त_alloc(rfसमाप्त->name, &pdev->dev,
					  rfसमाप्त->type, &rfसमाप्त_gpio_ops,
					  rfसमाप्त);
	अगर (!rfसमाप्त->rfसमाप्त_dev)
		वापस -ENOMEM;

	ret = rfसमाप्त_रेजिस्टर(rfसमाप्त->rfसमाप्त_dev);
	अगर (ret < 0)
		जाओ err_destroy;

	platक्रमm_set_drvdata(pdev, rfसमाप्त);

	dev_info(&pdev->dev, "%s device registered.\n", rfसमाप्त->name);

	वापस 0;

err_destroy:
	rfसमाप्त_destroy(rfसमाप्त->rfसमाप्त_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक rfसमाप्त_gpio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rfसमाप्त_gpio_data *rfसमाप्त = platक्रमm_get_drvdata(pdev);

	rfसमाप्त_unरेजिस्टर(rfसमाप्त->rfसमाप्त_dev);
	rfसमाप्त_destroy(rfसमाप्त->rfसमाप्त_dev);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id rfसमाप्त_acpi_match[] = अणु
	अणु "BCM4752", RFKILL_TYPE_GPS पूर्ण,
	अणु "LNV4752", RFKILL_TYPE_GPS पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, rfसमाप्त_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver rfसमाप्त_gpio_driver = अणु
	.probe = rfसमाप्त_gpio_probe,
	.हटाओ = rfसमाप्त_gpio_हटाओ,
	.driver = अणु
		.name = "rfkill_gpio",
		.acpi_match_table = ACPI_PTR(rfसमाप्त_acpi_match),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rfसमाप्त_gpio_driver);

MODULE_DESCRIPTION("gpio rfkill");
MODULE_AUTHOR("NVIDIA");
MODULE_LICENSE("GPL");
