<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * I2C multi-instantiate driver, pseuकरो driver to instantiate multiple
 * i2c-clients from a single fwnode.
 *
 * Copyright 2018 Hans de Goede <hdegoede@redhat.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/bits.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/property.h>
#समावेश <linux/types.h>

#घोषणा IRQ_RESOURCE_TYPE	GENMASK(1, 0)
#घोषणा IRQ_RESOURCE_NONE	0
#घोषणा IRQ_RESOURCE_GPIO	1
#घोषणा IRQ_RESOURCE_APIC	2

काष्ठा i2c_inst_data अणु
	स्थिर अक्षर *type;
	अचिन्हित पूर्णांक flags;
	पूर्णांक irq_idx;
पूर्ण;

काष्ठा i2c_multi_inst_data अणु
	पूर्णांक num_clients;
	काष्ठा i2c_client *clients[];
पूर्ण;

अटल पूर्णांक i2c_multi_inst_count(काष्ठा acpi_resource *ares, व्योम *data)
अणु
	काष्ठा acpi_resource_i2c_serialbus *sb;
	पूर्णांक *count = data;

	अगर (i2c_acpi_get_i2c_resource(ares, &sb))
		*count = *count + 1;

	वापस 1;
पूर्ण

अटल पूर्णांक i2c_multi_inst_count_resources(काष्ठा acpi_device *adev)
अणु
	LIST_HEAD(r);
	पूर्णांक count = 0;
	पूर्णांक ret;

	ret = acpi_dev_get_resources(adev, &r, i2c_multi_inst_count, &count);
	अगर (ret < 0)
		वापस ret;

	acpi_dev_मुक्त_resource_list(&r);
	वापस count;
पूर्ण

अटल पूर्णांक i2c_multi_inst_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_multi_inst_data *multi;
	स्थिर काष्ठा i2c_inst_data *inst_data;
	काष्ठा i2c_board_info board_info = अणुपूर्ण;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा acpi_device *adev;
	अक्षर name[32];
	पूर्णांक i, ret;

	inst_data = device_get_match_data(dev);
	अगर (!inst_data) अणु
		dev_err(dev, "Error ACPI match data is missing\n");
		वापस -ENODEV;
	पूर्ण

	adev = ACPI_COMPANION(dev);

	/* Count number of clients to instantiate */
	ret = i2c_multi_inst_count_resources(adev);
	अगर (ret < 0)
		वापस ret;

	multi = devm_kदो_स्मृति(dev, काष्ठा_size(multi, clients, ret), GFP_KERNEL);
	अगर (!multi)
		वापस -ENOMEM;

	multi->num_clients = ret;

	क्रम (i = 0; i < multi->num_clients && inst_data[i].type; i++) अणु
		स_रखो(&board_info, 0, माप(board_info));
		strlcpy(board_info.type, inst_data[i].type, I2C_NAME_SIZE);
		snम_लिखो(name, माप(name), "%s-%s.%d", dev_name(dev),
			 inst_data[i].type, i);
		board_info.dev_name = name;
		चयन (inst_data[i].flags & IRQ_RESOURCE_TYPE) अणु
		हाल IRQ_RESOURCE_GPIO:
			ret = acpi_dev_gpio_irq_get(adev, inst_data[i].irq_idx);
			अगर (ret < 0) अणु
				dev_err(dev, "Error requesting irq at index %d: %d\n",
					inst_data[i].irq_idx, ret);
				जाओ error;
			पूर्ण
			board_info.irq = ret;
			अवरोध;
		हाल IRQ_RESOURCE_APIC:
			ret = platक्रमm_get_irq(pdev, inst_data[i].irq_idx);
			अगर (ret < 0) अणु
				dev_dbg(dev, "Error requesting irq at index %d: %d\n",
					inst_data[i].irq_idx, ret);
				जाओ error;
			पूर्ण
			board_info.irq = ret;
			अवरोध;
		शेष:
			board_info.irq = 0;
			अवरोध;
		पूर्ण
		multi->clients[i] = i2c_acpi_new_device(dev, i, &board_info);
		अगर (IS_ERR(multi->clients[i])) अणु
			ret = dev_err_probe(dev, PTR_ERR(multi->clients[i]),
					    "Error creating i2c-client, idx %d\n", i);
			जाओ error;
		पूर्ण
	पूर्ण
	अगर (i < multi->num_clients) अणु
		dev_err(dev, "Error finding driver, idx %d\n", i);
		ret = -ENODEV;
		जाओ error;
	पूर्ण

	platक्रमm_set_drvdata(pdev, multi);
	वापस 0;

error:
	जबतक (--i >= 0)
		i2c_unरेजिस्टर_device(multi->clients[i]);

	वापस ret;
पूर्ण

अटल पूर्णांक i2c_multi_inst_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा i2c_multi_inst_data *multi = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	क्रम (i = 0; i < multi->num_clients; i++)
		i2c_unरेजिस्टर_device(multi->clients[i]);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_inst_data bsg1160_data[]  = अणु
	अणु "bmc150_accel", IRQ_RESOURCE_GPIO, 0 पूर्ण,
	अणु "bmc150_magn" पूर्ण,
	अणु "bmg160" पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा i2c_inst_data bsg2150_data[]  = अणु
	अणु "bmc150_accel", IRQ_RESOURCE_GPIO, 0 पूर्ण,
	अणु "bmc150_magn" पूर्ण,
	/* The resources describe a 3th client, but it is not really there. */
	अणु "bsg2150_dummy_dev" पूर्ण,
	अणुपूर्ण
पूर्ण;

/*
 * Device with _HID INT3515 (TI PD controllers) has some unresolved पूर्णांकerrupt
 * issues. The most common problem seen is पूर्णांकerrupt flood.
 *
 * There are at least two known causes. Firstly, on some boards, the
 * I2CSerialBus resource index करोes not match the Interrupt resource, i.e. they
 * are not one-to-one mapped like in the array below. Secondly, on some boards
 * the IRQ line from the PD controller is not actually connected at all. But the
 * पूर्णांकerrupt flood is also seen on some boards where those are not a problem, so
 * there are some other problems as well.
 *
 * Because of the issues with the पूर्णांकerrupt, the device is disabled क्रम now. If
 * you wish to debug the issues, uncomment the below, and add an entry क्रम the
 * INT3515 device to the i2c_multi_instance_ids table.
 *
 * अटल स्थिर काष्ठा i2c_inst_data पूर्णांक3515_data[]  = अणु
 *	अणु "tps6598x", IRQ_RESOURCE_APIC, 0 पूर्ण,
 *	अणु "tps6598x", IRQ_RESOURCE_APIC, 1 पूर्ण,
 *	अणु "tps6598x", IRQ_RESOURCE_APIC, 2 पूर्ण,
 *	अणु "tps6598x", IRQ_RESOURCE_APIC, 3 पूर्ण,
 *	अणु पूर्ण
 * पूर्ण;
 */

/*
 * Note new device-ids must also be added to i2c_multi_instantiate_ids in
 * drivers/acpi/scan.c: acpi_device_क्रमागतeration_by_parent().
 */
अटल स्थिर काष्ठा acpi_device_id i2c_multi_inst_acpi_ids[] = अणु
	अणु "BSG1160", (अचिन्हित दीर्घ)bsg1160_data पूर्ण,
	अणु "BSG2150", (अचिन्हित दीर्घ)bsg2150_data पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, i2c_multi_inst_acpi_ids);

अटल काष्ठा platक्रमm_driver i2c_multi_inst_driver = अणु
	.driver	= अणु
		.name = "I2C multi instantiate pseudo device driver",
		.acpi_match_table = i2c_multi_inst_acpi_ids,
	पूर्ण,
	.probe = i2c_multi_inst_probe,
	.हटाओ = i2c_multi_inst_हटाओ,
पूर्ण;
module_platक्रमm_driver(i2c_multi_inst_driver);

MODULE_DESCRIPTION("I2C multi instantiate pseudo device driver");
MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_LICENSE("GPL");
