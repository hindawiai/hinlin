<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Intel(R) Trace Hub ACPI driver
 *
 * Copyright (C) 2017 Intel Corporation.
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/acpi.h>

#समावेश "intel_th.h"

#घोषणा DRIVER_NAME "intel_th_acpi"

अटल स्थिर काष्ठा पूर्णांकel_th_drvdata पूर्णांकel_th_acpi_pch = अणु
	.host_mode_only	= 1,
पूर्ण;

अटल स्थिर काष्ठा पूर्णांकel_th_drvdata पूर्णांकel_th_acpi_uncore = अणु
	.host_mode_only	= 1,
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id पूर्णांकel_th_acpi_ids[] = अणु
	अणु "INTC1000",	(kernel_uदीर्घ_t)&पूर्णांकel_th_acpi_uncore पूर्ण,
	अणु "INTC1001",	(kernel_uदीर्घ_t)&पूर्णांकel_th_acpi_pch पूर्ण,
	अणु "",		0 पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(acpi, पूर्णांकel_th_acpi_ids);

अटल पूर्णांक पूर्णांकel_th_acpi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	काष्ठा resource resource[TH_MMIO_END];
	स्थिर काष्ठा acpi_device_id *id;
	काष्ठा पूर्णांकel_th *th;
	पूर्णांक i, r;

	id = acpi_match_device(पूर्णांकel_th_acpi_ids, &pdev->dev);
	अगर (!id)
		वापस -ENODEV;

	क्रम (i = 0, r = 0; i < pdev->num_resources && r < TH_MMIO_END; i++)
		अगर (pdev->resource[i].flags &
		    (IORESOURCE_IRQ | IORESOURCE_MEM))
			resource[r++] = pdev->resource[i];

	th = पूर्णांकel_th_alloc(&pdev->dev, (व्योम *)id->driver_data, resource, r);
	अगर (IS_ERR(th))
		वापस PTR_ERR(th);

	adev->driver_data = th;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_th_acpi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांकel_th *th = platक्रमm_get_drvdata(pdev);

	पूर्णांकel_th_मुक्त(th);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver पूर्णांकel_th_acpi_driver = अणु
	.probe		= पूर्णांकel_th_acpi_probe,
	.हटाओ		= पूर्णांकel_th_acpi_हटाओ,
	.driver		= अणु
		.name			= DRIVER_NAME,
		.acpi_match_table	= पूर्णांकel_th_acpi_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(पूर्णांकel_th_acpi_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Intel(R) Trace Hub ACPI controller driver");
MODULE_AUTHOR("Alexander Shishkin <alexander.shishkin@intel.com>");
