<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ACPI support क्रम पूर्णांक340x thermal drivers
 *
 * Copyright (C) 2014, Intel Corporation
 * Authors: Zhang Rui <rui.zhang@पूर्णांकel.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>

#समावेश "../internal.h"

#घोषणा INT3401_DEVICE 0X01
अटल स्थिर काष्ठा acpi_device_id पूर्णांक340x_thermal_device_ids[] = अणु
	अणु"INT3400"पूर्ण,
	अणु"INT3401", INT3401_DEVICEपूर्ण,
	अणु"INT3402"पूर्ण,
	अणु"INT3403"पूर्ण,
	अणु"INT3404"पूर्ण,
	अणु"INT3406"पूर्ण,
	अणु"INT3407"पूर्ण,
	अणु"INT3408"पूर्ण,
	अणु"INT3409"पूर्ण,
	अणु"INT340A"पूर्ण,
	अणु"INT340B"पूर्ण,
	अणु"INTC1040"पूर्ण,
	अणु"INTC1041"पूर्ण,
	अणु"INTC1043"पूर्ण,
	अणु"INTC1044"पूर्ण,
	अणु"INTC1045"पूर्ण,
	अणु"INTC1046"पूर्ण,
	अणु"INTC1047"पूर्ण,
	अणु"INTC1048"पूर्ण,
	अणु"INTC1049"पूर्ण,
	अणु"INTC1060"पूर्ण,
	अणु"INTC1061"पूर्ण,
	अणु""पूर्ण,
पूर्ण;

अटल पूर्णांक पूर्णांक340x_thermal_handler_attach(काष्ठा acpi_device *adev,
					स्थिर काष्ठा acpi_device_id *id)
अणु
	अगर (IS_ENABLED(CONFIG_INT340X_THERMAL))
		acpi_create_platक्रमm_device(adev, शून्य);
	/* Intel SoC DTS thermal driver needs INT3401 to set IRQ descriptor */
	अन्यथा अगर (IS_ENABLED(CONFIG_INTEL_SOC_DTS_THERMAL) &&
		 id->driver_data == INT3401_DEVICE)
		acpi_create_platक्रमm_device(adev, शून्य);
	वापस 1;
पूर्ण

अटल काष्ठा acpi_scan_handler पूर्णांक340x_thermal_handler = अणु
	.ids = पूर्णांक340x_thermal_device_ids,
	.attach = पूर्णांक340x_thermal_handler_attach,
पूर्ण;

व्योम __init acpi_पूर्णांक340x_thermal_init(व्योम)
अणु
	acpi_scan_add_handler(&पूर्णांक340x_thermal_handler);
पूर्ण
