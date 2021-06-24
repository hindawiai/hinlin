<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Common code क्रम Intel Cherry Trail ACPI INT33FE pseuकरो device drivers
 * (USB Micro-B and Type-C connector variants).
 *
 * Copyright (c) 2019 Yauhen Kharuzhy <jekhor@gmail.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "intel_cht_int33fe_common.h"

#घोषणा EXPECTED_PTYPE		4

अटल पूर्णांक cht_पूर्णांक33fe_i2c_res_filter(काष्ठा acpi_resource *ares, व्योम *data)
अणु
	काष्ठा acpi_resource_i2c_serialbus *sb;
	पूर्णांक *count = data;

	अगर (i2c_acpi_get_i2c_resource(ares, &sb))
		(*count)++;

	वापस 1;
पूर्ण

अटल पूर्णांक cht_पूर्णांक33fe_count_i2c_clients(काष्ठा device *dev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);
	LIST_HEAD(resource_list);
	पूर्णांक count = 0;
	पूर्णांक ret;

	ret = acpi_dev_get_resources(adev, &resource_list,
				     cht_पूर्णांक33fe_i2c_res_filter, &count);
	acpi_dev_मुक्त_resource_list(&resource_list);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल पूर्णांक cht_पूर्णांक33fe_check_hw_type(काष्ठा device *dev)
अणु
	अचिन्हित दीर्घ दीर्घ ptyp;
	acpi_status status;
	पूर्णांक ret;

	status = acpi_evaluate_पूर्णांकeger(ACPI_HANDLE(dev), "PTYP", शून्य, &ptyp);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(dev, "Error getting PTYPE\n");
		वापस -ENODEV;
	पूर्ण

	/*
	 * The same ACPI HID is used क्रम dअगरferent configurations check PTYP
	 * to ensure that we are dealing with the expected config.
	 */
	अगर (ptyp != EXPECTED_PTYPE)
		वापस -ENODEV;

	/* Check presence of INT34D3 (hardware-rev 3) expected क्रम ptype == 4 */
	अगर (!acpi_dev_present("INT34D3", "1", 3)) अणु
		dev_err(dev, "Error PTYPE == %d, but no INT34D3 device\n",
			EXPECTED_PTYPE);
		वापस -ENODEV;
	पूर्ण

	ret = cht_पूर्णांक33fe_count_i2c_clients(dev);
	अगर (ret < 0)
		वापस ret;

	चयन (ret) अणु
	हाल 2:
		वापस INT33FE_HW_MICROB;
	हाल 4:
		वापस INT33FE_HW_TYPEC;
	शेष:
		वापस -ENODEV;
	पूर्ण
पूर्ण

अटल पूर्णांक cht_पूर्णांक33fe_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cht_पूर्णांक33fe_data *data;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक ret;

	ret = cht_पूर्णांक33fe_check_hw_type(dev);
	अगर (ret < 0)
		वापस ret;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->dev = dev;

	चयन (ret) अणु
	हाल INT33FE_HW_MICROB:
		data->probe = cht_पूर्णांक33fe_microb_probe;
		data->हटाओ = cht_पूर्णांक33fe_microb_हटाओ;
		अवरोध;

	हाल INT33FE_HW_TYPEC:
		data->probe = cht_पूर्णांक33fe_typec_probe;
		data->हटाओ = cht_पूर्णांक33fe_typec_हटाओ;
		अवरोध;
	पूर्ण

	platक्रमm_set_drvdata(pdev, data);

	वापस data->probe(data);
पूर्ण

अटल पूर्णांक cht_पूर्णांक33fe_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cht_पूर्णांक33fe_data *data = platक्रमm_get_drvdata(pdev);

	वापस data->हटाओ(data);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id cht_पूर्णांक33fe_acpi_ids[] = अणु
	अणु "INT33FE", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, cht_पूर्णांक33fe_acpi_ids);

अटल काष्ठा platक्रमm_driver cht_पूर्णांक33fe_driver = अणु
	.driver	= अणु
		.name = "Intel Cherry Trail ACPI INT33FE driver",
		.acpi_match_table = ACPI_PTR(cht_पूर्णांक33fe_acpi_ids),
	पूर्ण,
	.probe = cht_पूर्णांक33fe_probe,
	.हटाओ = cht_पूर्णांक33fe_हटाओ,
पूर्ण;

module_platक्रमm_driver(cht_पूर्णांक33fe_driver);

MODULE_DESCRIPTION("Intel Cherry Trail ACPI INT33FE pseudo device driver");
MODULE_AUTHOR("Yauhen Kharuzhy <jekhor@gmail.com>");
MODULE_LICENSE("GPL v2");
