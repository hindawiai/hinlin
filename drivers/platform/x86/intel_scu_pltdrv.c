<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Platक्रमm driver क्रम the Intel SCU.
 *
 * Copyright (C) 2019, Intel Corporation
 * Authors: Divya Sasidharan <भागya.s.sasidharan@पूर्णांकel.com>
 *	    Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 *	    Rajmohan Mani <rajmohan.mani@पूर्णांकel.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/पूर्णांकel_scu_ipc.h>

अटल पूर्णांक पूर्णांकel_scu_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_scu_ipc_data scu_data = अणुपूर्ण;
	काष्ठा पूर्णांकel_scu_ipc_dev *scu;
	स्थिर काष्ठा resource *res;

	scu_data.irq = platक्रमm_get_irq_optional(pdev, 0);
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENOMEM;

	scu_data.mem = *res;

	scu = devm_पूर्णांकel_scu_ipc_रेजिस्टर(&pdev->dev, &scu_data);
	अगर (IS_ERR(scu))
		वापस PTR_ERR(scu);

	platक्रमm_set_drvdata(pdev, scu);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id पूर्णांकel_scu_acpi_ids[] = अणु
	अणु "INTC1026" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, पूर्णांकel_scu_acpi_ids);

अटल काष्ठा platक्रमm_driver पूर्णांकel_scu_platक्रमm_driver = अणु
	.probe = पूर्णांकel_scu_platक्रमm_probe,
	.driver = अणु
		.name = "intel_scu",
		.acpi_match_table = पूर्णांकel_scu_acpi_ids,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(पूर्णांकel_scu_platक्रमm_driver);

MODULE_AUTHOR("Divya Sasidharan <divya.s.sasidharan@intel.com>");
MODULE_AUTHOR("Mika Westerberg <mika.westerberg@linux.intel.com");
MODULE_AUTHOR("Rajmohan Mani <rajmohan.mani@intel.com>");
MODULE_DESCRIPTION("Intel SCU platform driver");
MODULE_LICENSE("GPL v2");
