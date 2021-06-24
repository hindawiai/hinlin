<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * INT3402 thermal driver क्रम memory temperature reporting
 *
 * Copyright (C) 2014, Intel Corporation
 * Authors: Aaron Lu <aaron.lu@पूर्णांकel.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/acpi.h>
#समावेश <linux/thermal.h>
#समावेश "int340x_thermal_zone.h"

#घोषणा INT3402_PERF_CHANGED_EVENT	0x80
#घोषणा INT3402_THERMAL_EVENT		0x90

काष्ठा पूर्णांक3402_thermal_data अणु
	acpi_handle *handle;
	काष्ठा पूर्णांक34x_thermal_zone *पूर्णांक340x_zone;
पूर्ण;

अटल व्योम पूर्णांक3402_notअगरy(acpi_handle handle, u32 event, व्योम *data)
अणु
	काष्ठा पूर्णांक3402_thermal_data *priv = data;

	अगर (!priv)
		वापस;

	चयन (event) अणु
	हाल INT3402_PERF_CHANGED_EVENT:
		अवरोध;
	हाल INT3402_THERMAL_EVENT:
		पूर्णांक340x_thermal_zone_device_update(priv->पूर्णांक340x_zone,
						   THERMAL_TRIP_VIOLATED);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांक3402_thermal_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	काष्ठा पूर्णांक3402_thermal_data *d;
	पूर्णांक ret;

	अगर (!acpi_has_method(adev->handle, "_TMP"))
		वापस -ENODEV;

	d = devm_kzalloc(&pdev->dev, माप(*d), GFP_KERNEL);
	अगर (!d)
		वापस -ENOMEM;

	d->पूर्णांक340x_zone = पूर्णांक340x_thermal_zone_add(adev, शून्य);
	अगर (IS_ERR(d->पूर्णांक340x_zone))
		वापस PTR_ERR(d->पूर्णांक340x_zone);

	ret = acpi_install_notअगरy_handler(adev->handle,
					  ACPI_DEVICE_NOTIFY,
					  पूर्णांक3402_notअगरy,
					  d);
	अगर (ret) अणु
		पूर्णांक340x_thermal_zone_हटाओ(d->पूर्णांक340x_zone);
		वापस ret;
	पूर्ण

	d->handle = adev->handle;
	platक्रमm_set_drvdata(pdev, d);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांक3402_thermal_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा पूर्णांक3402_thermal_data *d = platक्रमm_get_drvdata(pdev);

	acpi_हटाओ_notअगरy_handler(d->handle,
				   ACPI_DEVICE_NOTIFY, पूर्णांक3402_notअगरy);
	पूर्णांक340x_thermal_zone_हटाओ(d->पूर्णांक340x_zone);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id पूर्णांक3402_thermal_match[] = अणु
	अणु"INT3402", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, पूर्णांक3402_thermal_match);

अटल काष्ठा platक्रमm_driver पूर्णांक3402_thermal_driver = अणु
	.probe = पूर्णांक3402_thermal_probe,
	.हटाओ = पूर्णांक3402_thermal_हटाओ,
	.driver = अणु
		   .name = "int3402 thermal",
		   .acpi_match_table = पूर्णांक3402_thermal_match,
		   पूर्ण,
पूर्ण;

module_platक्रमm_driver(पूर्णांक3402_thermal_driver);

MODULE_DESCRIPTION("INT3402 Thermal driver");
MODULE_LICENSE("GPL");
